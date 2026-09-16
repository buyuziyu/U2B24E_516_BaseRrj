/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Lin_RLIN3_LLDriver.h                                                                                */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Header file for Lin_RLIN3_LLDriver.c.                                                                              */
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
 *
 * 2.4.0:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION to 2.1.2
 * 2.0.1:  14/09/2023  : Update to correct memory section for Lin_ErrorReport
 * 2.0.0:  23/08/2023  : Update to remove unused argument "LucApiId" for function Lin_HwSetMasterMode
 *         18/07/2023  : Update argument in function "Lin_HwInit", "Lin_SetStatus" to support for multi core.
 *                       Add new function "Lin_ErrorReport" to correct critical section in Lin_HWSetMasterMode
 *         27/06/2023  : Remove redundant QAC message (7:0791)
 * 1.5.0:  05/04/2023  : Update for support AR21-11
 * 1.4.3:  14/04/2022  : Update SW-VERSION to 1.4.3
 * 1.3.2:  04/03/2022  : Update SW-VERSION
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 * 1.2.0:  26/08/2020  : Release.
 * 1.1.0:  19/06/2020  : Release.
 * 1.0.1:  16/04/2020  : Modified #include heading files.
 *         19/03/2019  : Fix QAC
 *                         1. Update "MISRA C Rule Violations" and "QAC warning"
 *                            message from MISRA-C:2004 to MISRA-C:2012.
 *                         2. Move static function prototypes from header file
 *                            to source file.
 * 1.0.0:  12/03/2019  : Initial Version.
 *
 */
/**********************************************************************************************************************/

#ifndef LIN_RLIN3_LLDRIVER_H
#define LIN_RLIN3_LLDRIVER_H

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define LIN_RLIN3_LLDRIVER_AR_RELEASE_MAJOR_VERSION    LIN_AR_RELEASE_MAJOR_VERSION
#define LIN_RLIN3_LLDRIVER_AR_RELEASE_MINOR_VERSION    LIN_AR_RELEASE_MINOR_VERSION
#define LIN_RLIN3_LLDRIVER_AR_RELEASE_REVISION_VERSION LIN_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define LIN_RLIN3_LLDRIVER_SW_MAJOR_VERSION            LIN_SW_MAJOR_VERSION
#define LIN_RLIN3_LLDRIVER_SW_MINOR_VERSION            LIN_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                             Global Function Prototypes                                             **
***********************************************************************************************************************/

#define LIN_START_SEC_CODE_FAST
#include "Lin_MemMap.h"

/* Interrupt handler function of transmition interrupt for channels */
extern FUNC(void, LIN_CODE_FAST) Lin_TxIsr(const uint8 LucChannel);

/* Interrupt handler function of reception interrupt for channels */
extern FUNC(void, LIN_CODE_FAST) Lin_RxIsr(const uint8 LucChannel);

/* Interrupt handler function of error interrupt for channels */
extern FUNC(void, LIN_CODE_FAST) Lin_ErrIsr(const uint8 LucChannel);

extern FUNC(Std_ReturnType, LIN_CODE_FAST)
    Lin_HwSetMasterMode(const uint8 LucChannel, const Lin_ModeType LenModeType);

extern FUNC(void, LIN_CODE_FAST)
    Lin_HwScheduleInterrupt(const uint8 LucChannel, const Lin_InterruptScheduleType LenInterruptScheduleType);

extern FUNC(Std_ReturnType, LIN_CODE_FAST)
    Lin_HwHandleWakeupRequest(const uint8 LucChannel, const Lin_WakeupType LenWakeupType, const uint8 LucApiId);

#if defined(LIN_E_TIMEOUT) || (LIN_DEV_ERROR_DETECT == STD_ON)
extern FUNC(Std_ReturnType, LIN_CODE_FAST) Lin_ErrorReport(const uint8 LucApiId);
#endif

#define LIN_STOP_SEC_CODE_FAST
#include "Lin_MemMap.h"

#define LIN_START_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"

#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
extern FUNC(void, LIN_PRIVATE_CODE) Lin_HwSlaveStartHeaderReception(const uint8 LucChannel);
#endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */

#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, LIN_PRIVATE_CODE)
    Lin_HwSendHeaderInternal(const uint8 LucChannel,
                             CONSTP2CONST(Lin_PduType, AUTOMATIC, LIN_PRIVATE_CONST) LpPduInfoPtr,
                             const uint8 LucApiId);
#endif /* #if (LIN_MASTER_MODE_SUPPORT ==STD_ON) */

extern FUNC(Std_ReturnType, LIN_PRIVATE_CODE) Lin_HwInit(const uint8 LucChannel, const uint8 LucCoreIndex);

extern FUNC(void, LIN_PRIVATE_CODE) Lin_SetStatus(const boolean LblStatus, const uint8 LucCoreIndex);

#define LIN_STOP_SEC_PRIVATE_CODE
#include "Lin_MemMap.h"

#endif /* #define LIN_RLIN3_LLDRIVER_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
