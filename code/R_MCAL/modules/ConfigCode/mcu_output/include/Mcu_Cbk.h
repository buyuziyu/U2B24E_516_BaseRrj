/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mcu_Cbk.h                                                                                           */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2023, 2024 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains callback notification parameters.                                                               */
/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                                         */
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
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s)        */
/* and/or the Application.                                                                                            */
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
/*              Devices:        R7F7025BxFABC                                                                         */
/*====================================================================================================================*/


/***********************************************************************************************************************
**                      Revision Control History                                                                      **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Generation Tool Version                                                                       **
***********************************************************************************************************************/
/*                                                                                                                    */
/* TOOL VERSION:  McuU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\mcu\generator\U2B24-E\R2211_mcu_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_mcu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_mcu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  13 Jul 2026 - 15:38:52
 */


#ifndef MCU_CBK_H
#define MCU_CBK_H


/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Dem.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/

/**********************************************************************************************************************/
/* Message (2:3449)    : Multiple declarations of external object or function.                                        */
/* Rule                : MISRA C:2012 Rule 8.5                                                                        */
/* JV-01 Justification : These extern function are not impact due to it was generated by same parameters name.        */
/*                       It's depend on user's configuration.                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1534)    : The macro '%1s' is declared but not used within this project.                                */
/* Rule                : MISRA C:2012 Rule-2.5                                                                        */
/* JV-01 Justification : These macros are used for version checking in precompile or in user application.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MCU_CBK_AR_RELEASE_MAJOR_VERSION                                        4U                                      /* PRQA S 1534 # JV-01 */
#define MCU_CBK_AR_RELEASE_MINOR_VERSION                                        8U                                      /* PRQA S 1534 # JV-01 */
#define MCU_CBK_AR_RELEASE_REVISION_VERSION                                     0U                                      /* PRQA S 1534 # JV-01 */

/* File version information */
#define MCU_CBK_SW_MAJOR_VERSION                                                2U                                      /* PRQA S 1534 # JV-01 */
#define MCU_CBK_SW_MINOR_VERSION                                                5U                                      /* PRQA S 1534 # JV-01 */

/***********************************************************************************************************************
**                      Global Symbols                                                                                **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/


#define MCU_START_SEC_APPL_CODE
#include "Mcu_MemMap.h"


extern FUNC(void, MCU_APPL_CODE) Mcu_EcmNotification(uint16 McuErrorNumber);                                            /* PRQA S 3449 # JV-01 */

extern FUNC(void, MCU_APPL_CODE) Mcu_EcmNotification(uint16 McuErrorNumber);                                            /* PRQA S 3449 # JV-01 */

extern FUNC(void, MCU_APPL_CODE) Mcu_EcmNotification(uint16 McuErrorNumber);                                            /* PRQA S 3449 # JV-01 */

#define MCU_STOP_SEC_APPL_CODE
#include "Mcu_MemMap.h"


#endif /* MCU_CBK_H */


/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

