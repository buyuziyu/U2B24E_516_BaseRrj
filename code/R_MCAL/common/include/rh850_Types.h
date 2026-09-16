/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* File name    = rh850_Types.h                                               */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2017-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision for platform dependent types                                     */
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
/*  2.4.1:  30/06/2025  : Remove the SW-VERSION from header of file
 *  2.3.0:  28/02/2025  : Update SW-VERSION for
 *                        Ver22.01.00/Ver22.01.00.D U2Cx Release
 *  2.2.1:  31/12/2024  : Update SW-VERSION for Ver22.00.01 U2Ax Release
 *  2.2.0:  31/12/2024  : Update SW-VERSION
 *                        for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.1:  27/06/2024  : Update SW-VERSION to 2.1.1
 *  2.1.0   23/02/2024  : Update SW-VERSION to 2.1.0
 *  2.0.3:  15/04/2024  : Update SW-VERSION to 2.0.3
 *  2.0.0:  27/04/2023  : Update SW-VERSION
 *  1.2.0:  26/08/2020  : Release
 *  1.1.0:  19/06/2020  : Release
 *  1.0.3:  23/10/2018  : Add macro RH850_SV_SET_ICR_SYNCP,
 *                         RH850_SV_CLEAR_ICR_SYNCP, RH850_SET_IOREG_SYNCP,
 *                         RH850_CLEAR_IOREG_SYNCP.
 *
 *  1.0.2:  27/02/2018   : Change Comment of RH850_SV_MODE_REG_READ_ONLY.
 *
 *  1.0.1:  04/04/2017  : Added MISRA C Rule Violations comments
 *                         removed the macros WriteIORegBit and ReadIORegBit.
 *
 *  1.0.0:  05/01/2017  : Initial Version.
 */
/******************************************************************************/

#ifndef RH850_TYPES_H
#define RH850_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*
 * File version information
 */
#define RH850_TYPES_SW_MAJOR_VERSION  2
#define RH850_TYPES_SW_MINOR_VERSION  3
#define RH850_TYPES_SW_PATCH_VERSION  0

/*******************************************************************************
**                      MISRA C Rule Violations                               **
*******************************************************************************/

/* 1. MISRA C RULE VIOLATION:                                                 */
/* Message       : (2:0881) Using multiple ## operators in the same macro     */
/*                 definition.                                                */
/* Rule          : MISRA-C:2004 Rule 19.12                                    */
/*                 REFERENCE - ISO:C90-6.8.3.3 ##Operator - Semantics         */
/* Justification : Multiple ## implemented has been verified. Removing the    */
/*                 same will affect the intended functionality.               */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:0881)-1 and                           */
/*                 END Msg(2:0881)-1 tags in the code.                        */
/******************************************************************************/

/* 2. MISRA C RULE VIOLATION:                                                 */
/* Message       : (2:3412) Macro defines an unrecognized code-fragment.      */
/* Rule          : MISRA-C:2004 Rule 19.4                                     */
/*                 REFERENCE - None                                           */
/* Justification : Macro definition as multi-line operation hence multi-line  */
/*                 macro is used.                                             */
/* Verification  : However, part of the code is verified manually and it is   */
/*                 not having any impact.                                     */
/* Reference     : Look for START Msg(2:3412)-2 and                           */
/*                 END Msg(2:4312)-2 tags in the code.                        */
/******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

typedef unsigned int        uinteger;       /*           0 .. 65535           */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/*******************************************************************************
**                      Macro                                                 **
*******************************************************************************/

/*  Macro definition for supervisor mode(SV) write enabled Registers
 *  IMR & ICxxx .
 */
/*******************************************************************************
** Macro Name            : RH850_SV_MODE_ICR_OR
**
** Description           : This Macro performs supervisor mode(SV)
**                         write enabled Register ICxxx register
**                         writing which involves an OR operation.
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size
**                         ADDR : Register address
**                         VAL  : Value to be written to the register
*******************************************************************************/
/* MISRA Violation: START Msg(2:0881)-1 */
#define RH850_SV_MODE_ICR_OR(SIZE, ADDR, VAL) \
                                    (*((volatile uint##SIZE*)(ADDR)) = \
                                    ((*((volatile uint##SIZE*)(ADDR)))|(VAL)))
/* END Msg(2:0881)-1 */
/*******************************************************************************
** Macro Name            : RH850_SV_MODE_ICR_AND
**
** Description           : This Macro performs supervisor mode(SV)
**                         write enabled Register ICxxx register
**                         writing which involves an AND operation.
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size
**                         ADDR : Register address
**                         VAL  : Value to be written to the register
*******************************************************************************/
/* MISRA Violation: START Msg(2:0881)-1 */
#define RH850_SV_MODE_ICR_AND(SIZE, ADDR, VAL) \
                                    (*((volatile uint##SIZE*)(ADDR)) = \
                                    ((*((volatile uint##SIZE*)(ADDR)))&(VAL)))
/* END Msg(2:0881)-1 */
/*******************************************************************************
** Macro Name            : RH850_SV_MODE_ICR_WRITE_ONLY
**
** Description           : This Macro performs supervisor mode(SV)
**                         write enabled Register ICxxx register
**                         direct writing operation.
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size
**                         ADDR : Register address
**                         VAL  : Value to be written to the register
*******************************************************************************/
#define RH850_SV_MODE_ICR_WRITE_ONLY(SIZE, ADDR, VAL) \
                                 (*((volatile uint##SIZE*)(ADDR)) = \
                                 (VAL))

/*******************************************************************************
** Macro Name            : RH850_SV_MODE_IMR_OR
**
** Description           : This Macro performs supervisor mode(SV)
**                         write enabled Register IMR register
**                         writing which involves an OR operation.
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size
**                         ADDR : Register address
**                         VAL  : Value to be written to the register
*******************************************************************************/
/* MISRA Violation: START Msg(2:0881)-1 */
#define RH850_SV_MODE_IMR_OR(SIZE, ADDR, VAL) \
                                    (*((volatile uint##SIZE*)(ADDR)) = \
                                    ((*((volatile uint##SIZE*)(ADDR)))|(VAL)))
/* END Msg(2:0881)-1 */
/*******************************************************************************
** Macro Name            : RH850_SV_MODE_IMR_AND
**
** Description           : This Macro performs supervisor mode(SV)
**                         write enabled Register IMR register
**                         writing which involves an AND operation.
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size
**                         ADDR : Register address
**                         VAL  : Value to be written to the register
*******************************************************************************/
/* MISRA Violation: START Msg(2:0881)-1 */
#define RH850_SV_MODE_IMR_AND(SIZE, ADDR, VAL) \
                                    (*((volatile uint##SIZE*)(ADDR)) = \
                                    ((*((volatile uint##SIZE*)(ADDR)))&(VAL)))
/* END Msg(2:0881)-1 */
/*******************************************************************************
** Macro Name            : RH850_SV_MODE_IMR_WRITE_ONLY
**
** Description           : This Macro performs supervisor mode(SV)
**                         write enabled Register IMR register
**                         direct writing operation.
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size
**                         ADDR : Register address
**                         VAL  : Value to be written to the register
*******************************************************************************/
#define RH850_SV_MODE_IMR_WRITE_ONLY(SIZE, ADDR, VAL) \
                                 (*((volatile uint##SIZE*)(ADDR)) = \
                                 (VAL))

/*******************************************************************************
** Macro Name            : RH850_SV_MODE_REG_READ_ONLY
**
** Description           : This Macro performs a read a register
**
** Input Parameters      : SIZE, ADDR
**                         SIZE : Register Access Size
**                         ADDR : Register address
*******************************************************************************/
#define RH850_SV_MODE_REG_READ_ONLY(SIZE, ADDR) \
                                    (*((volatile uint##SIZE*)(ADDR)))

/*******************************************************************************
** Macro Name            : RH850_SV_MODE_REG_WRITE_ONLY
**
** Description           : This Macro performs supervisor mode(SV)
**                         write register.
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size
**                         ADDR : Register address
**                         VAL  : Value to be written to the register
*******************************************************************************/
#define RH850_SV_MODE_REG_WRITE_ONLY(SIZE, ADDR, VAL) \
                                 (*((volatile uint##SIZE*)(ADDR)) = \
                                 (VAL))

/*******************************************************************************
** Macro Name            : RH850_SV_MODE_REG_OR
**
** Description           : This Macro performs supervisor mode(SV)
**                         write enabled Register writing which
**                         involves an OR operation.
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size
**                         ADDR : Register address
**                         VAL  : Value to be written to the register
*******************************************************************************/
#define RH850_SV_MODE_REG_OR(SIZE, ADDR, VAL) \
                                    (*((volatile uint##SIZE*)(ADDR)) = \
                                    ((*((volatile uint##SIZE*)(ADDR)))|(VAL)))

/*******************************************************************************
** Macro Name            : RH850_SV_MODE_REG_AND
**
** Description           : This Macro performs supervisor mode(SV)
**                         write enabled Register writing which
**                         involves an AND operation.
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size
**                         ADDR : Register address
**                         VAL  : Value to be written to the register
*******************************************************************************/
/* MISRA Violation: START Msg(2:0881)-1 */
#define RH850_SV_MODE_REG_AND(SIZE, ADDR, VAL) \
                                    (*((volatile uint##SIZE*)(ADDR)) = \
                                    ((*((volatile uint##SIZE*)(ADDR)))&(VAL)))
/* END Msg(2:0881)-1 */

/*******************************************************************************
** Macro Name            : SetIORegSyncpDummyRead
**
** Description           : This Macro executes:
**                          1) set bits in a register by bitwise operator OR.
**                          2) dummy read on the register.
**                          3) SYNCP
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size
**                         ADDR : Register Address
**                         VAL  : Value to be written to the register
*******************************************************************************/
/* MISRA Violation: START Msg(2:0881)-1 */
/* MISRA Violation: START Msg(2:3412)-2 */
#define SetIORegSyncpDummyRead(SIZE, ADDR, VAL) \
  *((volatile uint##SIZE*)(ADDR)) = (*((volatile uint##SIZE*)(ADDR))) | (VAL); \
  *((volatile uint##SIZE*)(ADDR)); \
  EXECUTE_SYNCP()
/* END Msg(2:3412)-2 */
/* END Msg(2:0881)-1 */
/*******************************************************************************
** Macro Name            : ClrIORegSyncpDummyRead
**
** Description           : This Macro executes:
**                          1) clear bits in a register by bitwise operator AND.
**                          2) dummy read on the register.
**                          3) SYNCP
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size
**                         ADDR : Register Address
**                         VAL  : Value to be written to the register
*******************************************************************************/
/* MISRA Violation: START Msg(2:0881)-1 */
/* MISRA Violation: START Msg(2:3412)-2 */
#define ClrIORegSyncpDummyRead(SIZE, ADDR, VAL) \
  *((volatile uint##SIZE*)(ADDR)) = (*((volatile uint##SIZE*)(ADDR))) & (VAL); \
  *((volatile uint##SIZE*)(ADDR)); \
  EXECUTE_SYNCP()
/* END Msg(2:3412)-2 */
/* END Msg(2:0881)-1 */


/*******************************************************************************
** Macro Name            : RH850_SV_SET_ICR_SYNCP
**
** Description           : This Macro executes:
**                          1) set bits in a EIC register by bitwise operator
**                             OR.
**                          2) dummy read on the register.
**                          3) SYNCP
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size.
**                         ADDR : Register Address.
**                         VAL  : Value to be written to the register.
*******************************************************************************/
#define RH850_SV_SET_ICR_SYNCP(SIZE, ADDR, VAL) \
  *((volatile uint##SIZE*)(ADDR)) = (*((volatile uint##SIZE*)(ADDR))) | (VAL); \
  *((volatile uint##SIZE*)(ADDR)); \
  EXECUTE_SYNCP()
  
  
/*******************************************************************************
** Macro Name            : RH850_SV_CLEAR_ICR_SYNCP
**
** Description           : This Macro executes:
**                          1) clear bits in a EIC register by bitwise operator
**                             AND.
**                          2) dummy read on the register.
**                          3) SYNCP
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size.
**                         ADDR : Register Address.
**                         VAL  : Value to be written to the register.
*******************************************************************************/
#define RH850_SV_CLEAR_ICR_SYNCP(SIZE, ADDR, VAL) \
  *((volatile uint##SIZE*)(ADDR)) = (*((volatile uint##SIZE*)(ADDR))) & (VAL); \
  *((volatile uint##SIZE*)(ADDR)); \
  EXECUTE_SYNCP()
 

/*******************************************************************************
** Macro Name            : RH850_SET_IOREG_SYNCP
**
** Description           : This Macro executes:
**                          1) set bits in a register by bitwise operator OR.
**                          2) dummy read on the register.
**                          3) SYNCP
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size.
**                         ADDR : Register Address.
**                         VAL  : Value to be written to the register.
*******************************************************************************/
#define RH850_SET_IOREG_SYNCP(SIZE, ADDR, VAL) \
  *((volatile uint##SIZE*)(ADDR)) = (*((volatile uint##SIZE*)(ADDR))) | (VAL); \
  *((volatile uint##SIZE*)(ADDR)); \
  EXECUTE_SYNCP()

/*******************************************************************************
** Macro Name            : RH850_CLEAR_IOREG_SYNCP
**
** Description           : This Macro executes:
**                          1) clear bits in a register by bitwise operator AND.
**                          2) dummy read on the register.
**                          3) SYNCP
**
** Input Parameters      : SIZE, ADDR, VAL
**                         SIZE : Register Access Size.
**                         ADDR : Register Address.
**                         VAL  : Value to be written to the register.
*******************************************************************************/
#define RH850_CLEAR_IOREG_SYNCP(SIZE, ADDR, VAL) \
  *((volatile uint##SIZE*)(ADDR)) = (*((volatile uint##SIZE*)(ADDR))) & (VAL); \
  *((volatile uint##SIZE*)(ADDR)); \
  EXECUTE_SYNCP()

#endif /* RH850_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
