/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22.11 X2x MCAL Components                                                          */
/* Module       = App_FEE_Common_Sample.h                                                                             */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application for FEE Component                                                            */
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
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header
 * 1.1.0:  30/06/2025:  Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 1.0.1:  28/02/2025:  Add FEE_MEM_DATA2_END_ADDRESS support Device U2Cx.
 * 1.0.0:  31/12/2024:  Update SW-VERSION 1.0.0.
 * 0.0.2:  31/10/2024:  Update SW-VERSION 0.0.2.
 * 0.0.1:  30/08/2024:  Initial Version. 
 */
/**********************************************************************************************************************/

#ifndef APP_FEE_COMMON_SAMPLE_H
#define APP_FEE_COMMON_SAMPLE_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Fee.h"
#include "Fee_Ram.h"

#include "MemAcc.h"
#include "MemAcc_Ram.h"
#include "MemAcc_Types.h"
#include "MemAcc_PBTypes.h"
#include "SchM_MemAcc.h"

#include "Mem_59_Renesas.h"
#include "Mem_59_Renesas_Ram.h"
#include "Mem_59_Renesas_Cfg.h"
#include "SchM_Mem_59_Renesas.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Global Symbols                                                      **
***********************************************************************************************************************/

#define FEE_SAMPLE_ZERO                                                         0
#define FEE_SAMPLE_ONE                                                          1
#define FEE_DELAY_TIME                                                          0x000111FFUL


#define FEE_MEM_DATA0_START_ADDRESS                                             0xFF200000UL
#define FEE_MEM_DATA0_END_ADDRESS                                               0xFF210000UL
#define FEE_MEM_DATA1_END_ADDRESS                                               0xFF220000UL
#define FEE_MEM_DATA2_END_ADDRESS                                               0xFF240000UL
#define FEE_SAMPLE_TRUE                                                         1
#define FEE_SAMPLE_FALSE                                                        0

/***********************************************************************************************************************
**                                                Global Data Types                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
extern Std_ReturnType GddReturnValue;

#endif /* #ifndef APP_FEE_COMMON_SAMPLE_H */

/***********************************************************************************************************************
**                                                End of File                                                         **
***********************************************************************************************************************/
