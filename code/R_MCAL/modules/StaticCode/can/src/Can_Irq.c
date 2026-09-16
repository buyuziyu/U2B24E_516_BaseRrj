/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can_Irq.c                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Interrupt Service Routines Functionality.                                                             */
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
**                                                  Revision History                                                  **
***********************************************************************************************************************/
/* 
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025  : Update CanXL_ErrIsr, Can_SubErrorIsr, Can_ErrorIsr
 *                      Fixing QAC message
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                      Update CanXL_FuncIsr, CanXL_ErrIsr
 *                    : Add message 0404, 3384 to support QA-C version 11.6.0
 * 2.3.0: 28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D Final Release
 *                      As part of ARDAACL-52560: Update CanXL_FuncIsr, CanXL_ErrIsr
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                      Update CanXL_FuncIsr, CanXL_ErrIsr.
 *                      Include CanXLTrcv.h.
 * 2.1.2: 31/10/2024  : As part of CAN-XL driver support, following changes are made:
 *                      1. Fixing QAC message. Add messsage 2963
 *                      2. Update CanXL_FuncIsr, CanXL_ErrIsr to fix findings
 * 2.1.1: 30/08/2024  : As part of CAN-XL driver support, following changes are made:
 *                      1. Remove redundant variable in CanXL_ErrIsr
 *                      2. Update CanXL_ErrIsr
 *                      3. Add new function CANXL_CONTROLLER0_ERR_ISR, CANXL_CONTROLLER1_ERR_ISR, CanXL_ErrIsr
 *                      CANXL_CONTROLLER0_WAKEUP_ISR, CANXL_CONTROLLER1_WAKEUP_ISR
 *                      4. Update Can_WakeUpIsr to support CAN XL
 *                      5. Add new function CAN_RSCAN2_RXFIFO_ISR
 *                      6. Update CAN_CONTROLLERm_RX_ISR, CAN_CONTROLLERm_TX_ISR, CAN_CONTROLLERm_ERROR_ISR, 
 *                      CAN_CONTROLLERm_WAKEUP_ISR to support U2Bx-E
 *                      7. Change condition define of CanXL_FuncIsr function
 *                      8. Update QAC message
 *                      9. Update interrupt function to separate U2Bx and U2Cx device
 *                      11. Update macro name of Ored Interrupt function to support U2Cx version 0.50
 *                      12. Update reference ID to support CANXL
 *                      13. Update Can_SelRxIsr, Can_SelTxIsr, Can_SelErrIsr, Can_RxIsr, Can_TxIsr, 
 *                      Can_ErrorIsr to support interrupt for U2Cx version 0.40
 *                      14. Add reference ID for CanXL_FuncIsr, CANXL_CONTROLLER0_FUNC_ISR, CANXL_CONTROLLER1_FUNC_ISR
 *                      Can_SelRxIsr, CAN_RX_INTERRUPT_DES_SELECTION_n, Can_SubErrorIsr, Can_SelErrorIsr,
 *                      CAN_ERROR_INTERRUPT_DES_SELECTION_n
 *                      15. Add message header 3408, 2983, 1503, 3432
 *                      16. Update Can_SubErrorIsr
 *                      17. Remove message 1503, 3408
 *                      18. Invoke new function CanXL_RxQueueProcess for CanXl_RxIsr, Add new function CanXl_RxIsr, 
 *                      CANXL_CONTROLLER0_RX_ISR, CANXL_CONTROLLER1_RX_ISR
 *                      Add function Can_SelRxIsr, Can_SelTxIsr, Can_SelErrIsr, CAN_RX_INTERRUPT_DES_SELECTION_n,
 *                      CAN_TX_INTERRUPT_DES_SELECTION_n, CAN_ERROR_INTERRUPT_DES_SELECTION_n and updatr function  
 *                      Can_RxIsr, Can_TxIsr, Can_ErrorIsr to support Ored interrupt function for U2Cx version 0.40
 *                      19. Add message 3416
 * 2.0.1: 06/11/2023  : Add message 4424, 4342, remove header message 2963, update function Can_SubErrorIsr
 *        19/10/2023  : Remove message 2844, 2814
 *                      Add message 3006, 0404
 *        14/10/2023  : Change macro CAN_AR_R21_11_VERSION to CAN_AR_R22_11_VERSION
 * 2.0.0: 16/08/2023  : Add CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL to function Can_RxGlobalIsr, Can_RxIsr, Can_TxIsr,
 *                      Can_ErrorIsr
 *        02/08/2023  : In function Can_WakeupIsr: Change CAN_INTERRUPT_CONTROL_PROTECTION to 
 *                      CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL
 *                      Change from Can_Mapping.h to Can_MemMap.h
 *                      Add QAC message
 *                      Remove redundant QAC messages
 *                      Update description of function
 *                      Add CWE Rule
 *        17/07/2023  : Change Can_RxProcessing to Can_RxProcessingTxRxFIFO in Can_RxIsr and Can_RxProcessingRxFIFO in
 *                      Can_RxGlobalIsr
 *        28/06/2023  : Remove redundant QAC messages
 *        02/06/2023  : Update Can_ErrorIsr, Can_SubErrorIsr
 *        31/05/2023  : Remove reduntdant QAC messages, update Can_SubErrorIsr
 *                      Add QAC message 2963
 *        05/05/2023  : Add QAC message 1338
 *                      Change Can_BusoffIsr to Can_ErrorIsr, CAN_CONTROLLERm_BUSOFF_INTERRUPT to
 *                      CAN_CONTROLLERm_ERROR_INTERRUPT
 *                      Add Can_SubErrorIsr function
 * 1.4.3: 11/05/2022  : Change COMMON_STATE_STARTED to CAN_COMMON_STATE_STARTED;
 *                      COMMON_STATE_STOPPED to CAN_COMMON_STATE_STOPPED;
 *                      COMMON_STATE_SLEEP to CAN_COMMON_STATE_SLEEP
 *        10/05/2022  : Remove "else" statement don't use when no action required.
 *        12/04/2022  : Change LpPCController->ulWakeupSourceId to LpPCController->ucWakeupSourceId
 * 1.3.2: 30/08/2021  : Update to support multi-instance:
 *                      - Change include to Can_Mapping.h
 * 1.3.1: 02/07/2021  : Add QAC message 9.5.0
 *                      Format source code to 120 characters
 *                      Improve Violation tag (remove START/END)
 *        05/05/2021  : Update the memory section, memclass, ptrclass to change
 *                      the CAN_RSCAN prefix to CAN
 *        04/05/2021  : Update to change from SetIORegSyncpDummyRead to
 *                      RH850_SET_IOREG_SYNCP
 * 1.3.0: 12/03/2021  : Update to correct passed argument of EcuM_CheckWakeup
 *                      functions at Can_WakeupIsr.
 * 1.2.0: 09/07/2020  : Release.
 *        28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020  : Release.
 * 1.0.3: 08/05/2020  : As per #268953, Update Reentrancy information for ISR
 *                      functions.
 * 1.0.2: 16/04/2020  : As per #266253, Add CAN_CONTROLLER_OFFSET to
 *                      ControllerID when invoke to CanIf
 * 1.0.1: 27/03/2020  : Update to change bit-size passed from 16 to 8 when
 *                      access bit EIMK of EIC register.
 *        19/03/2020  : Updated Global Variables Used in function description.
 *                      Update Precondition in function description.
 *                      Fix QAC findings, add declaration for Can_TxIsr.
 *        04/03/2020  : Remove functionality of full and one frame interrupt.
 *                      Add null check for pFCLAReg.
 *        05/02/2020  : Use common macros for Dem report error API.
 *        20/01/2020  : Use common controller state macro for commonization of
 *                      AUTOSAR version 4.2.2 and 4.3.1 for the change of
 *                      controller state machine function.
 *        13/01/2019  : Use Dem_SetEventStatus for AUTOSAR version 4.3.1
 * 1.0.0: 09/12/2019  : Initial version.
 */
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* CAN module header file */
#include "Can.h"
/* Included for RAM variable declarations */
#include "Can_Ram.h"

/* CAN Interface call-back Header File */
#if (CAN_AR_VERSION == CAN_AR_R22_11_VERSION)
#if (CAN_CANXL_SUPPORTED == STD_ON)
#include "CanXLTrcv.h"
#endif
#include "CanIf_Can.h"
#else
#include "CanIf_Cbk.h"
#endif

#include "Can_Irq.h"
#include "Dem.h"
#include "rh850_Types.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define CAN_IRQ_C_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION_VALUE
#define CAN_IRQ_C_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION_VALUE
#define CAN_IRQ_C_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define CAN_IRQ_C_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION_VALUE
#define CAN_IRQ_C_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (CAN_IRQ_C_AR_RELEASE_MAJOR_VERSION != CAN_IRQ_AR_RELEASE_MAJOR_VERSION)
  #error "Can_Irq.c : Mismatch in Release Major Version"
#endif
#if (CAN_IRQ_C_AR_RELEASE_MINOR_VERSION != CAN_IRQ_AR_RELEASE_MINOR_VERSION)
  #error "Can_Irq.c : Mismatch in Release Minor Version"
#endif
#if (CAN_IRQ_C_AR_RELEASE_REVISION_VERSION != CAN_IRQ_AR_RELEASE_REVISION_VERSION)
  #error "Can_Irq.c : Mismatch in Release Revision Version"
#endif
#if (CAN_IRQ_SW_MAJOR_VERSION != CAN_IRQ_C_SW_MAJOR_VERSION)
  #error "Can_Irq.c : Mismatch in Software Major Version"
#endif
#if (CAN_IRQ_SW_MINOR_VERSION != CAN_IRQ_C_SW_MINOR_VERSION)
  #error "Can_Irq.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***************************************************************************************************************** *****/
/* Message (3:3206)    : The parameter '%s' is not used in this function.                                             */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.7, CWE Rule CWE-398, CWE-563, CWE-569              */
/* JV-01 Justification : This is done as per implementation requirement                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : [E] This in-line assembler construct is a language extension. The code has been ignored.     */
/* Rule                : MISRA-C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTC 1.2.4 MSC14                                   */
/* JV-01 Justification : Inline assembler support for syncp instruction.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there. (Other uses of  */
/*                       the macro may not necessarily be suitable for replacement.)                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3464)    : Argument to macro '%s' contains a side effect that will be evaluated more than once.         */
/* Rule                : CERTCCM PRE31                                                                                */
/* JV-01 Justification : This message is only emitted for expressions expanded from argument tokens written out at    */
/*                       the top level, that did not themselves originate from a macro expansion.                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : %s' has external linkage and is being defined without any previous declaration.              */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4                                                         */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2983)    : This assignment is redundant. The value of this object is never subsequently used.           */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : The value is to increment the pointer to the next item.                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1                                                         */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0777)    : Identifier does not differ from other identifier(s) (e.g. '%s') within the specified number  */
/*                       of significant characters.                                                                   */
/* Rule                : CERTCCM DCL23, DCL40, MSC15, MISRA C:2012 Rule-5.2, CWE Rule CWE-682, CWE-758, CWE-736       */
/* JV-01 Justification : Compiler will distinguish numerous characters, so this is accepted.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2985)    : This operation is redundant. The value of the result is always that of the left-hand operand.*/
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : For readability, setting to registers will used redundant macros and is based on hardware    */
/*                       user's manual                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

#define CAN_START_SEC_CODE_FAST
#include "Can_MemMap.h"

/* Prototypes for internal functions */
#if ((CAN_RSCAN0_RXFIFO_INTERRUPT == STD_ON) || (CAN_RSCAN1_RXFIFO_INTERRUPT == STD_ON) || \
     (CAN_RSCAN2_RXFIFO_INTERRUPT == STD_ON))
STATIC FUNC(void, CAN_CODE_FAST) Can_RxGlobalIsr(CONST(uint8, AUTOMATIC) LucUnit);
#endif

#if ((CAN_CONTROLLER0_RX_INTERRUPT == STD_ON) || (CAN_CONTROLLER1_RX_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER2_RX_INTERRUPT == STD_ON) || (CAN_CONTROLLER3_RX_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER4_RX_INTERRUPT == STD_ON) || (CAN_CONTROLLER5_RX_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER6_RX_INTERRUPT == STD_ON) || (CAN_CONTROLLER7_RX_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER8_RX_INTERRUPT == STD_ON) || (CAN_CONTROLLER9_RX_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER10_RX_INTERRUPT == STD_ON) || (CAN_CONTROLLER11_RX_INTERRUPT == STD_ON) || \
     (CAN_CONTROLLER12_RX_INTERRUPT == STD_ON) || (CAN_CONTROLLER13_RX_INTERRUPT == STD_ON) || \
     (CAN_CONTROLLER14_RX_INTERRUPT == STD_ON) || (CAN_CONTROLLER15_RX_INTERRUPT == STD_ON) || \
     (CAN_CONTROLLER16_RX_INTERRUPT == STD_ON) || (CAN_CONTROLLER17_RX_INTERRUPT == STD_ON) || \
     (CAN_CONTROLLER18_RX_INTERRUPT == STD_ON) || (CAN_CONTROLLER19_RX_INTERRUPT == STD_ON)) || \
    ((CAN_ORED_INTERRUPT_FUNCTION == STD_ON) && \
    ((CAN_RX_INTERRUPT_DES_SELECTION_0 == STD_ON) || (CAN_RX_INTERRUPT_DES_SELECTION_1 == STD_ON) || \
     (CAN_RX_INTERRUPT_DES_SELECTION_2 == STD_ON) || (CAN_RX_INTERRUPT_DES_SELECTION_3 == STD_ON)))
#define CAN_CONTROLLER_RX_INTERRUPT_ON
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
STATIC FUNC(void, CAN_CODE_FAST) Can_RxIsr(CONST(uint8, AUTOMATIC) LucController);
#else
STATIC FUNC(void, CAN_CODE_FAST) Can_RxIsr(CONST(uint8, AUTOMATIC) LucCtrlIndex);
#endif
#endif

#if (CAN_CONTROLLER0_TX_INTERRUPT == STD_ON) || (CAN_CONTROLLER1_TX_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER2_TX_INTERRUPT == STD_ON) || (CAN_CONTROLLER3_TX_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER4_TX_INTERRUPT == STD_ON) || (CAN_CONTROLLER5_TX_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER6_TX_INTERRUPT == STD_ON) || (CAN_CONTROLLER7_TX_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER8_TX_INTERRUPT == STD_ON) || (CAN_CONTROLLER9_TX_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER10_TX_INTERRUPT == STD_ON) || (CAN_CONTROLLER11_TX_INTERRUPT == STD_ON) || \
     (CAN_CONTROLLER12_TX_INTERRUPT == STD_ON) || (CAN_CONTROLLER13_TX_INTERRUPT == STD_ON) || \
     (CAN_CONTROLLER14_TX_INTERRUPT == STD_ON) || (CAN_CONTROLLER15_TX_INTERRUPT == STD_ON) || \
     (CAN_CONTROLLER16_TX_INTERRUPT == STD_ON) || (CAN_CONTROLLER17_TX_INTERRUPT == STD_ON) || \
     (CAN_CONTROLLER18_TX_INTERRUPT == STD_ON) || (CAN_CONTROLLER19_TX_INTERRUPT == STD_ON) || \
     ((CAN_ORED_INTERRUPT_FUNCTION == STD_ON) && \
      ((CAN_TX_INTERRUPT_DES_SELECTION_0 == STD_ON) || (CAN_TX_INTERRUPT_DES_SELECTION_1 == STD_ON) || \
       (CAN_TX_INTERRUPT_DES_SELECTION_2 == STD_ON) || (CAN_TX_INTERRUPT_DES_SELECTION_3 == STD_ON)))
#define CAN_CONTROLLER_TX_INTERRUPT_ON
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
STATIC FUNC(void, CAN_CODE_FAST) Can_TxIsr(CONST(uint8, AUTOMATIC) LucController);
#else
STATIC FUNC(void, CAN_CODE_FAST) Can_TxIsr(CONST(uint8, AUTOMATIC) LucCtrlIndex);
#endif
#endif

#if (CAN_CONTROLLER0_ERROR_INTERRUPT == STD_ON) || (CAN_CONTROLLER1_ERROR_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER2_ERROR_INTERRUPT == STD_ON) || (CAN_CONTROLLER3_ERROR_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER4_ERROR_INTERRUPT == STD_ON) || (CAN_CONTROLLER5_ERROR_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER6_ERROR_INTERRUPT == STD_ON) || (CAN_CONTROLLER7_ERROR_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER8_ERROR_INTERRUPT == STD_ON) || (CAN_CONTROLLER9_ERROR_INTERRUPT == STD_ON) ||   \
     (CAN_CONTROLLER10_ERROR_INTERRUPT == STD_ON) || (CAN_CONTROLLER11_ERROR_INTERRUPT == STD_ON) || \
     (CAN_CONTROLLER12_ERROR_INTERRUPT == STD_ON) || (CAN_CONTROLLER13_ERROR_INTERRUPT == STD_ON) || \
     (CAN_CONTROLLER14_ERROR_INTERRUPT == STD_ON) || (CAN_CONTROLLER15_ERROR_INTERRUPT == STD_ON) || \
     (CAN_CONTROLLER16_ERROR_INTERRUPT == STD_ON) || (CAN_CONTROLLER17_ERROR_INTERRUPT == STD_ON) || \
     (CAN_CONTROLLER18_ERROR_INTERRUPT == STD_ON) || (CAN_CONTROLLER19_ERROR_INTERRUPT == STD_ON) || \
     ((CAN_ORED_INTERRUPT_FUNCTION == STD_ON) && \
      ((CAN_ERROR_INTERRUPT_DES_SELECTION_0 == STD_ON) || (CAN_ERROR_INTERRUPT_DES_SELECTION_1 == STD_ON) || \
      (CAN_ERROR_INTERRUPT_DES_SELECTION_2 == STD_ON) || (CAN_ERROR_INTERRUPT_DES_SELECTION_3 == STD_ON)))
#define CAN_CONTROLLER_ERROR_INTERRUPT_ON
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
STATIC FUNC(void, CAN_CODE_FAST) Can_ErrorIsr(CONST(uint8, AUTOMATIC) LucController);
#else
STATIC FUNC(void, CAN_CODE_FAST) Can_ErrorIsr(CONST(uint8, AUTOMATIC) LucCtrlIndex);
#endif
#endif

#if ((CAN_WAKEUP_SUPPORT == STD_ON) &&                                                                  \
     ((CAN_CONTROLLER0_WAKEUP_INTERRUPT == STD_ON) || (CAN_CONTROLLER1_WAKEUP_INTERRUPT == STD_ON) ||   \
      (CAN_CONTROLLER2_WAKEUP_INTERRUPT == STD_ON) || (CAN_CONTROLLER3_WAKEUP_INTERRUPT == STD_ON) ||   \
      (CAN_CONTROLLER4_WAKEUP_INTERRUPT == STD_ON) || (CAN_CONTROLLER5_WAKEUP_INTERRUPT == STD_ON) ||   \
      (CAN_CONTROLLER6_WAKEUP_INTERRUPT == STD_ON) || (CAN_CONTROLLER7_WAKEUP_INTERRUPT == STD_ON) ||   \
      (CAN_CONTROLLER8_WAKEUP_INTERRUPT == STD_ON) || (CAN_CONTROLLER9_WAKEUP_INTERRUPT == STD_ON) ||   \
      (CAN_CONTROLLER10_WAKEUP_INTERRUPT == STD_ON) || (CAN_CONTROLLER11_WAKEUP_INTERRUPT == STD_ON) || \
      (CAN_CONTROLLER12_WAKEUP_INTERRUPT == STD_ON) || (CAN_CONTROLLER13_WAKEUP_INTERRUPT == STD_ON) || \
      (CAN_CONTROLLER14_WAKEUP_INTERRUPT == STD_ON) || (CAN_CONTROLLER15_WAKEUP_INTERRUPT == STD_ON) || \
      (CAN_CONTROLLER16_WAKEUP_INTERRUPT == STD_ON) || (CAN_CONTROLLER17_WAKEUP_INTERRUPT == STD_ON) || \
      (CAN_CONTROLLER18_WAKEUP_INTERRUPT == STD_ON) || (CAN_CONTROLLER19_WAKEUP_INTERRUPT == STD_ON) || \
      ((CAN_CANXL_SUPPORTED == STD_ON) && \
      ((CANXL_CONTROLLER0_WAKEUP_INTERRUPT == STD_ON) || (CANXL_CONTROLLER1_WAKEUP_INTERRUPT == STD_ON)))))

#define CAN_CONTROLLER_WAKEUP_INTERRUPT_ON
STATIC FUNC(void, CAN_CODE_FAST) Can_WakeupIsr(CONST(uint8, AUTOMATIC) LucController, 
                                                                   Can_ControllerType LenControllerType);
#endif
#if (CAN_CANXL_SUPPORTED == STD_ON)
#if ((CAN_CANXL_CONTROLLER0_FUNC_ISR == STD_ON) || (CAN_CANXL_CONTROLLER1_FUNC_ISR == STD_ON))
STATIC FUNC(void, CAN_CODE_FAST) CanXL_FuncIsr(CONST(uint8, AUTOMATIC) LucPhysController);
#endif

#if ((CAN_CANXL_CONTROLLER0_ERROR_ISR == STD_ON) || (CAN_CANXL_CONTROLLER1_ERROR_ISR == STD_ON))
STATIC FUNC(void, CAN_CODE_FAST) CanXL_ErrIsr(CONST(uint8, AUTOMATIC) LucPhysController);
#endif

/***********************************************************************************************************************
** Function Name         : CanXL_FuncIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each FUNC_ISR
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucPhysController : Physical number of Controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Preconditions         : The availability of the index must be guaranteed
**                         by the upper layer.
**
** Preconditions         : None
**
** Global Variables Used : Can_GpConfig, Can_GpPCController,
**                         CanXL_GaaRegs
**
** Functions Invoked     : Can_RxProcessing
**
** Registers Used        : (CFD)CFSTSk, (CFD)CFCCk, EICn
**                         (CFD)GSTS (for dummy read only)
**
** Reference ID          : CAN_DUD_ACT_066
** Reference ID          : CAN_DUD_ACT_066_ERR001, CAN_DUD_ACT_066_REG001
** Reference ID          : CAN_DUD_ACT_066_REG002, CAN_DUD_ACT_066_REG003
** Reference ID          : CAN_DUD_ACT_066_REG004, CAN_DUD_ACT_066_REG005
** Reference ID          : CAN_DUD_ACT_066_GBL001, CAN_DUD_ACT_066_GBL002
** Reference ID          : CAN_DUD_ACT_066_GBL003
***********************************************************************************************************************/
#if ((CAN_CANXL_CONTROLLER0_FUNC_ISR == STD_ON) || (CAN_CANXL_CONTROLLER1_FUNC_ISR == STD_ON))
STATIC FUNC(void, CAN_CODE_FAST) CanXL_FuncIsr(CONST(uint8, AUTOMATIC) LucPhysController)
{
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  #if (defined CANXL_CONTROLLER_RX_INTERRUPT_ON) || (defined CANXL_CONTROLLER_TX_INTERRUPT_ON)
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  #ifdef CANXL_CONTROLLER_TX_INTERRUPT_ON
  VAR(uint32, AUTOMATIC) LulTxFFIRQ;
  VAR(uint32, AUTOMATIC) LulTxPQIRQ;
  #endif
  #ifdef CANXL_CONTROLLER_RX_INTERRUPT_ON
  CanXL_ExtRxStatusType LenRetValue;
  VAR(uint32, AUTOMATIC) LulRxFFIRQ;
  VAR(uint8, AUTOMATIC) LucQueueId;
  VAR(uint32, AUTOMATIC) LulFuncRaw;
  LenRetValue = CANXL_EXT_NOT_RECEIVED;
  #endif
  #endif /* CANXL_CONTROLLER_RX_INTERRUPT_ON || CANXL_CONTROLLER_TX_INTERRUPT_ON */
  #if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;
  #endif
  
  /* Convert the physical Controller index to the config index */
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucPhysController];  
  #if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */
  /* If no irq exists, this interrupt is wrong */
  if ((0UL == ((CanXL_GaaRegs[LucCtrlInfoIndex].pIRC->ulFUNCENA) &                                                      /* PRQA S 0404 # JV-01 */
                (CanXL_GaaRegs[LucCtrlInfoIndex].pIRC->ulFUNCRAW))) ||
   ((uint16)(*LpCanXLHWInfo[LucCtrlInfoIndex].pICFunc & (CAN_EIC_EIMK_MASK | CAN_EIC_EIRF_MASK)) != CAN_EIC_EIRF_MASK))
  {
    CAN_DEM_REPORT_ERROR(CAN_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
  #if (defined CANXL_CONTROLLER_RX_INTERRUPT_ON) || (defined CANXL_CONTROLLER_TX_INTERRUPT_ON)
    LucCtrlIndex = Can_GpConfig->pCanXLPhysicalControllerToIndex[LucPhysController];
    LpPCController = &Can_GpPCController[LucCtrlIndex];
    #ifdef CANXL_CONTROLLER_RX_INTERRUPT_ON
    LulFuncRaw = CanXL_GaaRegs[LucCtrlInfoIndex].pIRC->ulFUNCRAW;
    LulRxFFIRQ = CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulRXFQINSTS;
    #endif
    #ifdef CANXL_CONTROLLER_TX_INTERRUPT_ON
    LulTxFFIRQ =  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQINSTS;
    LulTxPQIRQ =  CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQINSTS0;
    #endif

    #if defined CANXL_CONTROLLER_RX_INTERRUPT_ON
    if((0UL != ((uint32)LpPCController->ucIntEnable & (uint32)CAN_CHECK_INT_RX)) && \
       (0UL != (LulFuncRaw & CANXL_PRT_RXEVT_BIT)))
    {
      /* Get Queue index */
      for(LucQueueId = 0U; LucQueueId < CANXL_MAX_RXFIFOQUEUE; LucQueueId++)
      {
        if (0UL != (LulRxFFIRQ & (uint32)(1UL << (LucQueueId))))
        {
          /* Receive the specified queue */
          do
          {
            /* process receiption for CANXL Frame with SDT = 05 */
            LenRetValue = CanXL_RxQueueProcess(LucCtrlIndex, LucQueueId);
          } while ((CANXL_EXT_RECEIVED_MORE_DATA_AVAILABLE == LenRetValue) || \
                   (CANXL_EXT_NOT_RECEIVED_MORE_DATA_AVAILABLE == LenRetValue));
        } /* else no action required*/
      }
      /* Check if that Queue is not ETH Frame, then process CANXL Frame 01,03 */
      if (CANXL_EXT_NOT_RECEIVED == LenRetValue)
      {
        /* process receiption for CANXL Frame with SDT ={ 01, 03 } */
        CanXL_RxProcessing(LucCtrlIndex, CAN_CHECK_INT_RX, CAN_MAINFUNCTION_INSTANCE_0);
      } /* else no action required*/
    } /* else no action required*/
    #endif

    #if defined CANXL_CONTROLLER_TX_INTERRUPT_ON
    if((0UL != ((uint32)LpPCController->ucIntEnable & (uint32)CAN_CHECK_INT_TX)) && \
                    ((0UL != (LulTxFFIRQ & CANXL_FQ_ISR_BIT)) || (0UL != LulTxPQIRQ )))
    {
      /* Tx Confirmation Eth STD 05
       * Get Tx FIFO Queue index */
      CanXL_HwTxConfirmation(LucCtrlInfoIndex);
      /* Tx Confirmation Can STD 01,03 */
      Can_CanXLTxConfirmation(LucCtrlIndex);
    } /* else no action required*/
    #endif /* CANXL_CONTROLLER_TX_INTERRUPT_ON */
  #endif /* CANXL_CONTROLLER_RX_INTERRUPT_ON || CANXL_CONTROLLER_TX_INTERRUPT_ON */
  CanXL_GaaRegs[LucCtrlInfoIndex].pIRC->ulFUNCCLR |= 0xFFFFFFFFUL;
  }
}
#endif /* End of #ifdef CAN_CANXL_CONTROLLER0_FUNC_INTERRUPT == STD_ON */

/***********************************************************************************************************************
** Function Name         : CANXL_CONTROLLER0_FUNC_ISR
**
** Service ID            : Not Applicable
**
** Description           : This is Functional Interrupt Service routines for the CanXL
**                         controller 0.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : CanXL_FuncIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_067, CAN_DUD_ACT_190
***********************************************************************************************************************/
#if (CAN_CANXL_CONTROLLER0_FUNC_ISR == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CANXL_CONTROLLER0_FUNC_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)

ISR(CANXL_CONTROLLER0_FUNC_CAT2_ISR)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CANXL_CONTROLLER0_FUNC_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  CanXL_FuncIsr(CANXL_PHYIDX_CONTROLLER0);
}
#endif
/***********************************************************************************************************************
** Function Name         : CANXL_CONTROLLER1_FUNC_ISR
**
** Service ID            : Not Applicable
**
** Description           : This is Functional Interrupt Service routines for the CanXL
**                         controller 1.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : CanXL_FuncIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_067, CAN_DUD_ACT_190
***********************************************************************************************************************/
#if (CAN_CANXL_CONTROLLER1_FUNC_ISR == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CANXL_CONTROLLER1_FUNC_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)

ISR(CANXL_CONTROLLER1_FUNC_CAT2_ISR)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CANXL_CONTROLLER1_FUNC_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  CanXL_FuncIsr(CANXL_PHYIDX_CONTROLLER1); 
}
#endif
/***********************************************************************************************************************
** Function Name         : CanXL_ErrIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each ERR_ISR
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucPhysController : Physical number of Controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Preconditions         : The availability of the index must be guaranteed
**                         by the upper layer.
**
** Preconditions         : None
**
** Global Variables Used : Can_GpConfig, Can_GpPCController,
**                         Can_GaaRegs
**
** Functions Invoked     : Can_RxProcessing
**
** Registers Used        : (CFD)CFSTSk, (CFD)CFCCk, EICn
**                         (CFD)GSTS (for dummy read only)
**
** Reference ID          : CAN_DUD_ACT_182
** Reference ID          : CAN_DUD_ACT_182_ERR001, CAN_DUD_ACT_182_REG001
** Reference ID          : CAN_DUD_ACT_182_REG002, CAN_DUD_ACT_182_REG003
** Reference ID          : CAN_DUD_ACT_182_REG004, CAN_DUD_ACT_182_REG005
***********************************************************************************************************************/
#if ((CAN_CANXL_CONTROLLER0_ERROR_ISR == STD_ON) || (CAN_CANXL_CONTROLLER1_ERROR_ISR == STD_ON))
STATIC FUNC(void, CAN_CODE_FAST) CanXL_ErrIsr(CONST(uint8, AUTOMATIC) LucPhysController)
{
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  VAR(uint8, AUTOMATIC) LucCh;
  #if (CAN_BUSOFF_INTERRUPT == STD_ON) || (CAN_CHECK_SECURITY_EVENT_REPORTING == STD_ON)
  VAR(uint8, AUTOMATIC) LucSubCtrlIndex;
  VAR(uint8, AUTOMATIC) LucTransceiverID;
  #endif
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;
  #if (CAN_BUSOFF_INTERRUPT == STD_ON)
  uint32 LulCounter;
  P2CONST(CanXL_BufHandlerType, AUTOMATIC, CAN_APPL_DATA) LpBufHandlerPtr;
  VAR(boolean, AUTOMATIC) LblNotificationRequired;
  #endif
  #if (CAN_CHECK_SECURITY_EVENT_REPORTING == STD_ON)
  VAR(uint16, AUTOMATIC) LusTxErrorCounter;
  VAR(uint16, AUTOMATIC) LusRxErrorCounter;
  VAR(uint32, AUTOMATIC) LulRegEVNTMask;
  VAR(uint8, AUTOMATIC) LucFormIndex;
  const Can_ErrorType LaaErrorForm[CANXL_NUM_OF_BUS_ERROR] = 
  {
    CAN_ERROR_CHECK_CRC_FAILED,
    CAN_ERROR_BIT_MONITORING0,
    CAN_ERROR_BIT_MONITORING1,
    CAN_ERROR_CHECK_ACK_FAILED,
    CAN_ERROR_CHECK_FORM_FAILED,
    CAN_ERROR_CHECK_STUFFING_FAILED,
  };
  #endif
  LucCtrlIndex = Can_GpConfig->pCanXLPhysicalControllerToIndex[LucPhysController];
  LpPCController = &Can_GpPCController[LucCtrlIndex];
  LucCh = LpPCController->ucCh;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucCh];
  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316, 2983 # JV-01, JV-01 */
  #if ((CAN_BUSOFF_INTERRUPT == STD_ON) || (CAN_CHECK_SECURITY_EVENT_REPORTING == STD_ON))
  LucSubCtrlIndex = LucCtrlIndex + (uint8)CAN_CONTROLLER_OFFSET;                                                        /* PRQA S 2985 # JV-01 */
  LucTransceiverID = LpCanXLHWInfo[LucCtrlInfoIndex].ucTransceiverID;
  #endif
  #if (CAN_CHECK_SECURITY_EVENT_REPORTING == STD_ON)
  LulRegEVNTMask = 0UL;
  LucFormIndex = 0U;
  #endif
  #if (CAN_BUSOFF_INTERRUPT == STD_ON)
  LblNotificationRequired = CAN_FALSE;
  #endif
  #if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON) 
  /* If no irq exists, this interrupt is wrong */
  if ((0UL == ((CanXL_GaaRegs[LucCtrlInfoIndex].pIRC->ulERRENA) &                                                       /* PRQA S 0404 # JV-01 */
                (CanXL_GaaRegs[LucCtrlInfoIndex].pIRC->ulERRRAW))) ||
    ((uint16)(*LpCanXLHWInfo[LucCtrlInfoIndex].pICErr & (CAN_EIC_EIMK_MASK | CAN_EIC_EIRF_MASK)) != CAN_EIC_EIRF_MASK))
  {
    CAN_DEM_REPORT_ERROR(CAN_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
    #if (CAN_BUSOFF_INTERRUPT == STD_ON)
    /* Check whether Busoff event is occurred or not */
    if(0UL != ((uint32)LpPCController->ucIntEnable & (uint32)CAN_CHECK_INT_BUSOFF))
    {
      if (0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulSTAT & CAN_CANXL_BOEF))
      {
        if (CAN_TRUE == LpCanXLHWInfo[LucCtrlInfoIndex].blEthStackConfigured)
        {
          for(LulCounter = 0UL; LulCounter < CanXL_GaaTxBufferTotal[LucCtrlInfoIndex]; LulCounter++)
          {
            LpBufHandlerPtr = CanXL_GaaTxBufferMgrTable[LucCtrlInfoIndex][LulCounter].pBufferHdr;
            /* Check Buffer handler is not NULL */
            if (NULL_PTR != LpBufHandlerPtr)
            {
              /* Release all Tx buffer */
              CanXL_ReleaseTxBuffer(LucCtrlInfoIndex, LulCounter);
            } /* else no action required*/
          }
          if (ETH_MODE_ACTIVE == CanXL_GaaCtrlStat[LucCtrlInfoIndex].enMode)
          {
            CanXL_GaaCtrlStat[LucCtrlInfoIndex].enMode = ETH_MODE_DOWN;
            EthIf_TxConfirmation((uint8)(LucCtrlIndex + CAN_CONTROLLER_OFFSET), CANXL_BUSOFF_BUFFER_ID, E_NOT_OK);      /* PRQA S 3383, 2985 # JV-01, JV-01 */
          }
        }
        CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
        if ((CAN_COMMON_STATE_STARTED == Can_GaaCtrlState[LucCtrlIndex].enMode) &&
            (CAN_NO_PENDING_TRANSITION == Can_GaaCtrlState[LucCtrlIndex].enSubState))
        {
          /* Set bus-off flag */
          Can_GaaCtrlState[LucCtrlIndex].blBusOff = CAN_TRUE;
          /* XCAN IP use SW to stop controller completely */
          Can_GaaCtrlState[LucCtrlIndex].enSubState = CANXL_STOP_WAIT_TXRXQUEUE_STOP;
          /* Notification for CanIf is required */
          LblNotificationRequired = CAN_TRUE;
        } /* else no action required*/
        CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
        if (CAN_TRUE == LblNotificationRequired)
        {
          CanIf_ControllerBusOff((uint8)LucSubCtrlIndex);
          (void)(CanXLTrcv_ReportErrorState(LucTransceiverID, CAN_ERRORSTATE_BUSOFF));
          (void)CanXL_StopMode(LucCtrlIndex);
        } /* else No action required */
      }
    } /*else No action required */
    #endif
    #if (CAN_CHECK_SECURITY_EVENT_REPORTING == STD_ON)
    /* Check if Error Passive flag is set or not*/
    if(0UL != (CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulSTAT & CAN_CANXL_EPEF))
    {
      LusRxErrorCounter = (uint16)((CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulSTAT
                                     & CANXL_REC_MASK) >> CANXL_REC_OFFSET);
      LusTxErrorCounter = (uint16)((CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulSTAT
                                     & CANXL_TEC_MASK) >> CANXL_TEC_OFFSET);
      CanIf_ControllerErrorStatePassive(LucSubCtrlIndex, LusRxErrorCounter, LusTxErrorCounter);
      (void)(CanXLTrcv_ReportErrorState(LucTransceiverID, CAN_ERRORSTATE_PASSIVE));
    }/*else No action required */
    /* Check whether Can Bus Error event is occurred or not */
    
    while(CANXL_NUM_OF_BUS_ERROR > LucFormIndex)
    {
      /* Check if error bit is set or not*/
      if(0UL != ((CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulEVNT >> LucFormIndex) & CANXL_CHECK_BIT_SET))
      {
        CanIf_ErrorNotification(LucSubCtrlIndex, LaaErrorForm[LucFormIndex]);
        /* Mask Error bit to clear error flag */
        LulRegEVNTMask = LulRegEVNTMask | (CANXL_CHECK_BIT_SET << LucFormIndex);
      }
      LucFormIndex++;  
    }
    /* Clear all error flags */
    RH850_SV_MODE_REG_AND(32, &CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulEVNT, ~LulRegEVNTMask);                          /* PRQA S 3464 # JV-01 */
    #else
    CanXL_GaaRegs[LucCtrlInfoIndex].pPRT->ulEVNT &= ~(CANXL_BUS_ERROR_MASK);
    #endif 
    CanXL_GaaRegs[LucCtrlInfoIndex].pIRC->ulERRCLR |= 0xFFFFFFFFUL;
  }
}
#endif /* ((CAN_CANXL_CONTROLLER0_ERROR_ISR == STD_ON) || (CAN_CANXL_CONTROLLER1_ERROR_ISR == STD_ON)) */
/***********************************************************************************************************************
** Function Name         : CANXL_CONTROLLER0_ERR_ISR
**
** Service ID            : Not Applicable
**
** Description           : This is Error Interrupt Service routines for the CanXL
**                         controller 0.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : CanXL_ErrIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_187, CAN_DUD_ACT_189
***********************************************************************************************************************/
#if (CAN_CANXL_CONTROLLER0_ERROR_ISR == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CANXL_CONTROLLER0_FUNC_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)

ISR(CANXL_CONTROLLER0_ERR_CAT2_ISR)                                                                                     /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CANXL_CONTROLLER0_ERR_ISR(void)                                                   /* PRQA S 1503 # JV-01 */
#endif
{
  CanXL_ErrIsr(CANXL_PHYIDX_CONTROLLER0);
}
#endif
/***********************************************************************************************************************
** Function Name         : CANXL_CONTROLLER1_ERR_ISR
**
** Service ID            : Not Applicable
**
** Description           : This is Error Interrupt Service routines for the CanXL
**                         controller 1.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : CanXL_ErrIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_187, CAN_DUD_ACT_189
***********************************************************************************************************************/
#if (CAN_CANXL_CONTROLLER1_ERROR_ISR == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CANXL_CONTROLLER1_ERR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)

ISR(CANXL_CONTROLLER1_ERR_CAT2_ISR)                                                                                     /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CANXL_CONTROLLER1_ERR_ISR(void)                                                   /* PRQA S 1503 # JV-01 */
#endif
{
  CanXL_ErrIsr(CANXL_PHYIDX_CONTROLLER1); 
}
#endif
#endif
/***********************************************************************************************************************
** Function Name         : Can_RxGlobalIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each RXFIFO_ISR.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucUnit: Physical number of Unit
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of the index must be guaranteed
**                         by the upper layer.
**
** Global Variables Used : Can_GaaRegs, Can_GpConfig
**
** Functions Invoked     : Can_RxProcessingRxFIFO, CAN_DEM_REPORT_ERROR
**
** Registers Used        : (CFD)RFCC, (CFD)RFSTS, EICn
**                         (CFD)GSTS (for dummy read only)
**
** Reference ID          : CAN_DUD_ACT_057
** Reference ID          : CAN_DUD_ACT_057_ERR001, CAN_DUD_ACT_057_REG001
** Reference ID          : CAN_DUD_ACT_057_REG002
***********************************************************************************************************************/
#if ((CAN_RSCAN0_RXFIFO_INTERRUPT == STD_ON) || (CAN_RSCAN1_RXFIFO_INTERRUPT == STD_ON) || \
     (CAN_RSCAN2_RXFIFO_INTERRUPT == STD_ON))
STATIC FUNC(void, CAN_CODE_FAST) Can_RxGlobalIsr(CONST(uint8, AUTOMATIC) LucUnit)                                       /* PRQA S 3006 # JV-01 */
{
  #if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  VAR(uint32, AUTOMATIC) LulRxFIFOIndex;
  VAR(uint32, AUTOMATIC) LulIrqExist;
  #endif
  #if (CAN_WAKE_UP_FACTOR_CLEAR_ISR == STD_ON)
  VAR(uint32, AUTOMATIC) LulWUFMask;
  P2CONST(Can_HWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpHWInfo;
  #endif

  #if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  LulIrqExist = 0U;
  /* Accumurate all interrupt request flags of all RxFIFO */
  for (LulRxFIFOIndex = 0UL; LulRxFIFOIndex < CAN_RSCAN_RXFIFO_PER_UNIT; LulRxFIFOIndex++)
  {
    /* if (RFCCk.RFIE && RFSTSk.RFIF), it means that irq exists */
    LulIrqExist = LulIrqExist | (CAN_RSCAN_RFIE_GET(Can_GaaRegs[LucUnit].pCmn->aaRFCC[LulRxFIFOIndex]) &                /* PRQA S 3469, 0404 # JV-01, JV-01 */
                                 CAN_RSCAN_RFIF_GET(Can_GaaRegs[LucUnit].pCmn->aaRFSTS[LulRxFIFOIndex]));               /* PRQA S 3469 # JV-01 */
  }
  /* If no irq from RS-CAN or EIC is masked, this interrupt is wrong */
  if ((0UL == LulIrqExist) ||
      (CAN_EIC_EIRF_MASK != (uint16)(*Can_GaaRegs[LucUnit].pICRxFIFO & (CAN_EIC_EIMK_MASK | CAN_EIC_EIRF_MASK))))
  {
    CAN_DEM_REPORT_ERROR(CAN_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
    #if (CAN_WAKE_UP_FACTOR_CLEAR_ISR == STD_ON)
    LpHWInfo = (P2CONST(Can_HWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pHWUnitInfo;                      /* PRQA S 0316 # JV-01 */
    LpHWInfo = &LpHWInfo[LucUnit];
    LulWUFMask = LpHWInfo->ulRxFIFOWUFMask;
    if (LulWUFMask == (uint32)(*Can_GaaRegs[LucUnit].pWUF0Reg & LulWUFMask))
    {
      CAN_ENTER_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
      *Can_GaaRegs[LucUnit].pWUFC0Reg = LulWUFMask;
      CAN_EXIT_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    } /* else No action required */
    #endif
    /* Invoke Can_RxProcessing internal function for receive processing */
    Can_RxProcessingRxFIFO(CAN_RXPROC_RXFIFO(LucUnit), CAN_CHECK_INT_RX, CAN_MAINFUNCTION_INSTANCE_0);                  /* PRQA S 3469 # JV-01 */
    CAN_ENTER_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    /* DummyRead & SYNCP */
    RH850_SET_IOREG_SYNCP(32, &Can_GaaRegs[LucUnit].pCmn->ulGSTS, 0UL);                                                 /* PRQA S 1006, 3464 # JV-01, JV-01 */
    CAN_EXIT_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  }
}
#endif /* (CAN_RSCANx_RXFIFO_INTERRUP == STD_ON) */

/***********************************************************************************************************************
** Function Name         : CAN_RSCAN0_RXFIFO_ISR
**
** Service ID            : Not Applicable
**
** Description           : This is RXFIFO Interrupt Service routines for the Can
**                         hardware unit 0.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Can_RxGlobalIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_020
** Reference ID          : CAN_DUD_ACT_044
***********************************************************************************************************************/
#if (CAN_RSCAN0_RXFIFO_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(CAN_RSCAN0_RXFIFO_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_RSCAN0_RXFIFO_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_RSCAN0_RXFIFO_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxGlobalIsr(CAN_PHYIDX_UNIT0);
}
#endif /* (CAN_RSCAN0_RXFIFO_INTERRUPT == STD_ON) */

/***********************************************************************************************************************
** Function Name         : CAN_RSCAN1_RXFIFO_ISR
**
** Service ID            : Not Applicable
**
** Description           : This is RXFIFO Interrupt Service routines for the Can
**                         hardware unit 1.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Can_RxGlobalIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_020
** Reference ID          : CAN_DUD_ACT_044
***********************************************************************************************************************/
#if (CAN_RSCAN1_RXFIFO_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(CAN_RSCAN1_RXFIFO_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_RSCAN1_RXFIFO_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_RSCAN1_RXFIFO_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxGlobalIsr(CAN_PHYIDX_UNIT1);
}
#endif /* (CAN_RSCAN1_RXFIFO_INTERRUPT == STD_ON) */

/***********************************************************************************************************************
** Function Name         : CAN_RSCAN2_RXFIFO_ISR
**
** Service ID            : Not Applicable
**
** Description           : This is RXFIFO Interrupt Service routines for the Can
**                         hardware unit 2.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Can_RxGlobalIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_020
** Reference ID          : CAN_DUD_ACT_044
***********************************************************************************************************************/
#if (CAN_RSCAN2_RXFIFO_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(CAN_RSCAN2_RXFIFO_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_RSCAN2_RXFIFO_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_RSCAN2_RXFIFO_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxGlobalIsr(CAN_PHYIDX_UNIT2);
}
#endif /* (CAN_RSCAN2_RXFIFO_INTERRUPT == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Can_SelRxIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each RX_ISR Selection
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucInterruptSelId : Physical number of interrupt selection
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Preconditions         : The availability of the index must be guaranteed
**                         by the upper layer.
**
** Preconditions         : None
**
** Global Variables Used : Can_GpConfig, Can_GpPCController,
**                         Can_IntselGaaRegs
**
** Functions Invoked     : Can_RxIsr, CAN_DEM_REPORT_ERROR
**
** Registers Used        : (INTCANFD)RCMONn
**
** Reference ID          : CAN_DUD_ACT_068
** Reference ID          : CAN_DUD_ACT_068_ERR001, CAN_DUD_ACT_068_REG001
** Reference ID          : CAN_DUD_ACT_068_GBL001, CAN_DUD_ACT_068_GBL002
***********************************************************************************************************************/
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON)
#ifdef CAN_CONTROLLER_RX_INTERRUPT_ON
STATIC FUNC(void, CAN_CODE_FAST) Can_SelRxIsr(CONST(uint8, AUTOMATIC) LucInterruptSelId)
{
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  VAR(uint8, AUTOMATIC) LucUnit;
  VAR(uint8, AUTOMATIC) LucCh;
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;

  #if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* If no irq exists from RS-CAN, this interrupt is wrong */
  if (0UL == *Can_IntselGaaRegs[LucInterruptSelId].pRCMON)
  {
    CAN_DEM_REPORT_ERROR(CAN_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
    /* Loop for the number of Controllers configured */
    for (LucCtrlIndex = 0U; LucCtrlIndex < Can_GpConfig->ucNoOfControllers; LucCtrlIndex++)                             /* PRQA S 3416 # JV-01 */
    {
      LpPCController = &Can_GpPCController[LucCtrlIndex];
      /* Check controller activation bit */
      if(CAN_TRUE == LpPCController->blActivation)
      {
        LucUnit = LpPCController->ucUnit;
        LucCh = LpPCController->ucCh;
        if ((1UL == ((uint32)(*Can_IntselGaaRegs[LucInterruptSelId].pRCMON >>
            (LucCh + (LucUnit * CAN_MAX_CHANNEL_PER_UNIT))) & 1UL))                                                     /* PRQA S 3383 # JV-01 */
            && (0UL == ((uint32)(*Can_IntselGaaRegs[LucInterruptSelId].pRCMSK >> 
            (LucCh + (LucUnit * CAN_MAX_CHANNEL_PER_UNIT))) & 1UL)))                                                    /* PRQA S 3383 # JV-01 */
        {
          Can_RxIsr(LucCtrlIndex);
        } /* else No action required */
      } /* else No action required */
    }
  }
}
#endif /* #ifdef CAN_CONTROLLER_RX_INTERRUPT_ON */
#endif /* #if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Can_RxIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each RX_ISR
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucController (U2Bx, U2Bx-E) : Physical number of Controller
**                         LucCtrlIndex (U2Cx) : Physical number of Controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Preconditions         : The availability of the index must be guaranteed
**                         by the upper layer.
**
** Preconditions         : None
**
** Global Variables Used : Can_GpConfig, Can_GpPCController,
**                         Can_GaaRegs, Can_IntselGaaRegs
**
** Functions Invoked     : Can_RxProcessingTxRxFIFO, CAN_DEM_REPORT_ERROR
**
** Registers Used        : (CFD)CFSTSk, (CFD)CFCCk, EICn, (INTCANFD)TRMSKn
**                         (CFD)GSTS (for dummy read only), (INTCANFD)TRMONn
**
** Reference ID          : CAN_DUD_ACT_028
** Reference ID          : CAN_DUD_ACT_028_ERR001, CAN_DUD_ACT_028_REG001
** Reference ID          : CAN_DUD_ACT_028_REG002
***********************************************************************************************************************/
#ifdef CAN_CONTROLLER_RX_INTERRUPT_ON
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
STATIC FUNC(void, CAN_CODE_FAST) Can_RxIsr(CONST(uint8, AUTOMATIC) LucController)                                       /* PRQA S 3006 # JV-01 */
#else
STATIC FUNC(void, CAN_CODE_FAST) Can_RxIsr(CONST(uint8, AUTOMATIC) LucCtrlIndex)                                        /* PRQA S 3006 # JV-01 */
#endif
{
  VAR(uint8, AUTOMATIC) LucUnit;
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;
  #if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  #if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  VAR(uint32, AUTOMATIC) LulTxRxFIFOIndex;
  VAR(uint32, AUTOMATIC) LulLoop;
  VAR(uint32, AUTOMATIC) LulIrqExist;
  #endif /*#if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)*/
  #endif /*#if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)*/
  #if (CAN_WAKE_UP_FACTOR_CLEAR_ISR == STD_ON)
  VAR(uint32, AUTOMATIC) LulWUFMask;
  #endif

  #if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
  /* Convert the physical Controller index to the config index */
  LucCtrlIndex = Can_GpConfig->pPhysicalControllerToIndex[LucController];
  #endif
  LpPCController = &Can_GpPCController[LucCtrlIndex];
  LucUnit = LpPCController->ucUnit;

  #if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
  #if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  LulIrqExist = 0U;
  /* Accumurate all interrupt request flags of all TxRxFIFO */
  LulTxRxFIFOIndex = (uint32)LpPCController->ucCh * CAN_RSCAN_TXRXFIFO_PER_CH;                                          /* PRQA S 3384 # JV-01 */
  for (LulLoop = 0U; LulLoop < CAN_RSCAN_TXRXFIFO_PER_CH; LulLoop++)
  {
    /* if (CFCCk.CFRXIE && CFSTSk.CFRXIF), it means that irq exists */
    LulIrqExist = LulIrqExist | (CAN_RSCAN_CFRXIE_GET(Can_GaaRegs[LucUnit].pCmn->aaCFCC[LulTxRxFIFOIndex]) &            /* PRQA S 3469, 0404 # JV-01, JV-01 */
                                 CAN_RSCAN_CFRXIF_GET(Can_GaaRegs[LucUnit].pCmn->aaCFSTS[LulTxRxFIFOIndex]));           /* PRQA S 3469 # JV-01 */
    LulTxRxFIFOIndex++;                                                                                                 /* PRQA S 3383 # JV-01 */
  }
    /* If no irq exists from RS-CAN or EIC is masked, this interrupt is wrong */
  if ((0UL == LulIrqExist) ||
      (CAN_EIC_EIRF_MASK != (uint16)(*LpPCController->pICRec & (CAN_EIC_EIMK_MASK | CAN_EIC_EIRF_MASK))))
  {
    CAN_DEM_REPORT_ERROR(CAN_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  #endif
  {
    #if (CAN_WAKE_UP_FACTOR_CLEAR_ISR == STD_ON)
    LulWUFMask = LpPCController->ulWUFMask;
    if (LulWUFMask == (uint32)(*Can_GaaRegs[LucUnit].pWUF0Reg & LulWUFMask))
    {
      CAN_ENTER_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
       *Can_GaaRegs[LucUnit].pWUFC0Reg = LulWUFMask;
      CAN_EXIT_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    } /* else No action required */
    #endif
    /* Invoke Can_RxProcessing internal function for receive processing */
    Can_RxProcessingTxRxFIFO(CAN_RXPROC_TXRXFIFO(LucCtrlIndex), CAN_CHECK_INT_RX, CAN_MAINFUNCTION_INSTANCE_0);         /* PRQA S 3469 # JV-01 */
    CAN_ENTER_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    /* DummyRead & SYNCP */
    RH850_SET_IOREG_SYNCP(32, &Can_GaaRegs[LucUnit].pCmn->ulGSTS, 0UL);                                                 /* PRQA S 3464, 1006 # JV-01, JV-01 */
    CAN_EXIT_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  }
}
#endif /* End of #ifdef CAN_CONTROLLER_RX_INTERRUPT_ON */

/***********************************************************************************************************************
** Function Name         : CAN_CONTROLLERm_RX_ISR
**
** Service ID            : Not Applicable
**
** Description           : This is RX Interrupt Service routines for the Can
**                         hardware unit.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Can_RxIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_019
** Reference ID          : CAN_DUD_ACT_043
***********************************************************************************************************************/
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
#if (CAN_CONTROLLER0_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER0_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER0_RX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER0_RX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER0);
}
#endif

#if (CAN_CONTROLLER1_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER1_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER1_RX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER1_RX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER1);
}
#endif

#if (CAN_CONTROLLER2_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER2_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER2_RX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER2_RX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER2);
}
#endif

#if (CAN_CONTROLLER3_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER3_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER3_RX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER3_RX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER3);
}
#endif

#if (CAN_CONTROLLER4_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER4_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER4_RX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER4_RX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER4);
}
#endif

#if (CAN_CONTROLLER5_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER5_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER5_RX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER5_RX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER5);
}
#endif

#if (CAN_CONTROLLER6_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER6_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER6_RX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER6_RX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER6);
}
#endif

#if (CAN_CONTROLLER7_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER7_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER7_RX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER7_RX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER7);
}
#endif

#if (CAN_CONTROLLER8_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER8_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER8_RX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER8_RX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER8);
}
#endif

#if (CAN_CONTROLLER9_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER9_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER9_RX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER9_RX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER9);
}
#endif

#if (CAN_CONTROLLER10_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER10_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER10_RX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER10_RX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER10);
}
#endif

#if (CAN_CONTROLLER11_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER11_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER11_RX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER11_RX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER11);
}
#endif

#if (CAN_CONTROLLER12_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER12_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER12_RX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER12_RX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER12);
}
#endif

#if (CAN_CONTROLLER13_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER13_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER13_RX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER13_RX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER13);
}
#endif

#if (CAN_CONTROLLER14_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER14_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER14_RX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER14_RX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER14);
}
#endif

#if (CAN_CONTROLLER15_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER15_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER15_RX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER15_RX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER15);
}
#endif

#if (CAN_CONTROLLER16_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER16_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER16_RX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER16_RX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER16);
}
#endif

#if (CAN_CONTROLLER17_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER17_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER17_RX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER17_RX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER17);
}
#endif

#if (CAN_CONTROLLER18_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER18_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER18_RX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER18_RX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER18);
}
#endif

#if (CAN_CONTROLLER19_RX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER19_RX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER19_RX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER19_RX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_RxIsr(CAN_PHYIDX_CONTROLLER19);
}
#endif

#endif /* #if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF) */

/***********************************************************************************************************************
** Function Name         : CAN_CONTROLLER013_RX_ISR_n
**
** Service ID            : Not Applicable
**
** Description           : This is RX Interrupt Selection Service routines for the Can
**                         hardware unit.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Can_SelRxIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_069
** Reference ID          : CAN_DUD_ACT_185
***********************************************************************************************************************/
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON)
#if (CAN_RX_INTERRUPT_DES_SELECTION_0 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_RX_CAT2_ISR0) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER013_RX_CAT2_ISR_0)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_RX_ISR_0(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_SelRxIsr(CAN_PHYIDX_INTERRUPT_SELECTION0);
}
#endif

#if (CAN_RX_INTERRUPT_DES_SELECTION_1 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_RX_CAT2_ISR1) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER013_RX_CAT2_ISR_1)                                                                                    /* PRQA S 0777, 1503, 3408 # JV-01, JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_RX_ISR_1(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_SelRxIsr(CAN_PHYIDX_INTERRUPT_SELECTION1);
}
#endif

#if (CAN_RX_INTERRUPT_DES_SELECTION_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_RX_CAT2_ISR2) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER013_RX_CAT2_ISR_2)                                                                                    /* PRQA S 0777, 1503, 3408 # JV-01, JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_RX_ISR_2(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_SelRxIsr(CAN_PHYIDX_INTERRUPT_SELECTION2);
}
#endif

#if (CAN_RX_INTERRUPT_DES_SELECTION_3 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_RX_CAT2_ISR3) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER013_RX_CAT2_ISR_3)                                                                                    /* PRQA S 0777, 1503, 3408 # JV-01, JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_RX_ISR_3(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_SelRxIsr(CAN_PHYIDX_INTERRUPT_SELECTION3);
}
#endif
#endif /* #if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Can_SelTxIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each TX_ISR Selection
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucInterruptSelId : Physical number of interrupt selection
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Preconditions         : The availability of the index must be guaranteed
**                         by the upper layer.
**
** Preconditions         : None
**
** Global Variables Used : Can_GpConfig, Can_GpPCController,
**                         Can_IntselGaaRegs
**
** Functions Invoked     : Can_TxIsr, CAN_DEM_REPORT_ERROR
**
** Registers Used        : (INTCANFD)TRMONn
**
** Reference ID          : CAN_DUD_ACT_070
** Reference ID          : CAN_DUD_ACT_070_ERR001, CAN_DUD_ACT_070_REG001
** Reference ID          : CAN_DUD_ACT_070_GBL001, CAN_DUD_ACT_070_GBL002
***********************************************************************************************************************/
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON)
#ifdef CAN_CONTROLLER_TX_INTERRUPT_ON
STATIC FUNC(void, CAN_CODE_FAST) Can_SelTxIsr(CONST(uint8, AUTOMATIC) LucInterruptSelId)
{
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  VAR(uint8, AUTOMATIC) LucUnit;
  VAR(uint8, AUTOMATIC) LucCh;
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;

  #if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* If no irq exists from RS-CAN, this interrupt is wrong */
  if (0UL == *Can_IntselGaaRegs[LucInterruptSelId].pTRMON)
  {
    CAN_DEM_REPORT_ERROR(CAN_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
    /* Loop for the number of Controllers configured */
    for (LucCtrlIndex = 0U; LucCtrlIndex < Can_GpConfig->ucNoOfControllers; LucCtrlIndex++)                             /* PRQA S 3416 # JV-01 */
    {
      LpPCController = &Can_GpPCController[LucCtrlIndex];
    /* Check controller activation bit */
      if (CAN_TRUE == LpPCController->blActivation)
      {
        LucUnit = LpPCController->ucUnit;
        LucCh = LpPCController->ucCh;
        if ((1UL == ((*Can_IntselGaaRegs[LucInterruptSelId].pTRMON >> 
            (LucCh + (LucUnit * CAN_MAX_CHANNEL_PER_UNIT))) & 1UL))                                                     /* PRQA S 3383 # JV-01 */
            && (0UL == ((uint32)(*Can_IntselGaaRegs[LucInterruptSelId].pTRMSK >> 
                (LucCh + (LucUnit * CAN_MAX_CHANNEL_PER_UNIT))) & 1UL)))                                                /* PRQA S 3383 # JV-01 */
        {
          Can_TxIsr(LucCtrlIndex);
        } /* else No action required */
      } /* else No action required */
    }
  }
}
#endif /* #ifdef CAN_CONTROLLER_TX_INTERRUPT_ON*/
#endif /* #if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Can_TxIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each TX_ISR
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucController (U2Bx, U2Bx-E) : Physical number of Controller
**                         LucCtrlIndex (U2Cx) : Physical number of Controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of the index must be guaranteed
**                         by the upper layer.
**
** Global Variables Used : Can_GpConfig, Can_GpPCController,
**                         Can_GaaRegs, Can_IntselGaaRegs
**
** Functions Invoked     : Can_TxConfirmationProcessing, CAN_DEM_REPORT_ERROR
**
** Registers Used        : (CFD)GTINTSTSx, (CFD)GSTS (for dummy read only), (INTCANFD)TRMONn
**                         (INTCANFD)TRMSKn, EICn Register
**
** Reference ID          : CAN_DUD_ACT_029
** Reference ID          : CAN_DUD_ACT_029_ERR001, CAN_DUD_ACT_029_REG001
***********************************************************************************************************************/
#ifdef CAN_CONTROLLER_TX_INTERRUPT_ON
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
STATIC FUNC(void, CAN_CODE_FAST) Can_TxIsr(CONST(uint8, AUTOMATIC) LucController)                                       /* PRQA S 3006 # JV-01 */
#else
STATIC FUNC(void, CAN_CODE_FAST) Can_TxIsr(CONST(uint8, AUTOMATIC) LucCtrlIndex)                                        /* PRQA S 3006 # JV-01 */
#endif
{
  #if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  #endif
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;

  #if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
  /* Convert the physical Controller index to the config index */
  LucCtrlIndex = Can_GpConfig->pPhysicalControllerToIndex[LucController];
  #endif
  LpPCController = &Can_GpPCController[LucCtrlIndex];
  /* If no irq exists from RS-CAN or EIC is masked, this interrupt is wrong */
  #if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
  #if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* If no irq exists from RS-CAN or EIC is masked, this interrupt is wrong */
  if ((0U == Can_GaaRegs[LpPCController->ucUnit].pCmn->unGTINTSTS.aaGTINTSTSb[LpPCController->ucCh]) ||
      (CAN_EIC_EIRF_MASK != (uint16)(*LpPCController->pICTx & (CAN_EIC_EIMK_MASK | CAN_EIC_EIRF_MASK))))
  {
    CAN_DEM_REPORT_ERROR(CAN_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  #endif
  {
    #if ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON))

    Can_TxConfirmationProcessing(LucCtrlIndex);
    /* DummyRead & SYNCP */
    CAN_ENTER_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    RH850_SET_IOREG_SYNCP(32, &Can_GaaRegs[LpPCController->ucUnit].pCmn->ulGSTS, 0UL);                                  /* PRQA S 3464, 1006 # JV-01, JV-01 */
    CAN_EXIT_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
  }
}
#endif /* (CAN_CONTROLLERn_TX_INTERRUPT == STD_ON) */

/***********************************************************************************************************************
** Function Name         : CAN_CONTROLLERm_TX_ISR
**
** Service ID            : Not Applicable
**
** Description           : This is TX Interrupt Service routines for the Can
**                         hardware unit.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Can_TxIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_021
** Reference ID          : CAN_DUD_ACT_058
***********************************************************************************************************************/
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
#if (CAN_CONTROLLER0_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER0_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER0_TX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER0_TX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER0);
}
#endif

#if (CAN_CONTROLLER1_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER1_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER1_TX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER1_TX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER1);
}
#endif

#if (CAN_CONTROLLER2_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER2_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER2_TX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER2_TX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER2);
}
#endif

#if (CAN_CONTROLLER3_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER3_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER3_TX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER3_TX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER3);
}
#endif

#if (CAN_CONTROLLER4_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER4_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER4_TX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else 
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER4_TX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER4); 
}
#endif

#if (CAN_CONTROLLER5_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER5_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER5_TX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER5_TX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER5);
}
#endif

#if (CAN_CONTROLLER6_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER6_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER6_TX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER6_TX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER6);
}
#endif

#if (CAN_CONTROLLER7_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER7_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER7_TX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER7_TX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER7);
}
#endif

#if (CAN_CONTROLLER8_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER8_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER8_TX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER8_TX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER8);
}
#endif

#if (CAN_CONTROLLER9_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER9_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER9_TX_CAT2_ISR)                                                                                        /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER9_TX_ISR(void)                                                      /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER9);
}
#endif

#if (CAN_CONTROLLER10_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER10_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER10_TX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER10_TX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER10);
}
#endif

#if (CAN_CONTROLLER11_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER11_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER11_TX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER11_TX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER11);
}
#endif

#if (CAN_CONTROLLER12_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER12_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER12_TX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER12_TX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER12);
}
#endif

#if (CAN_CONTROLLER13_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER13_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER13_TX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER13_TX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER13);
}
#endif

#if (CAN_CONTROLLER14_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER14_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER14_TX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER14_TX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER14);
}
#endif

#if (CAN_CONTROLLER15_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER15_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER15_TX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER15_TX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER15);
}
#endif

#if (CAN_CONTROLLER16_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER16_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER16_TX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER16_TX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER16);
}
#endif

#if (CAN_CONTROLLER17_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER17_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER17_TX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER17_TX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER17);
}
#endif

#if (CAN_CONTROLLER18_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER18_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER18_TX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER18_TX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER18);
}
#endif

#if (CAN_CONTROLLER19_TX_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER19_TX_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER19_TX_CAT2_ISR)                                                                                       /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER19_TX_ISR(void)                                                     /* PRQA S 1503 # JV-01 */
#endif
{
  Can_TxIsr(CAN_PHYIDX_CONTROLLER19);
}
#endif

#endif /* #if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)*/

/***********************************************************************************************************************
** Function Name         : CAN_CONTROLLER013_TX_ISR_n
**
** Service ID            : Not Applicable
**
** Description           : This is TX Interrupt Selection Service routines for the Can
**                         hardware unit.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Can_SelTxIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_071
** Reference ID          : CAN_DUD_ACT_186
***********************************************************************************************************************/
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON)
#if (CAN_TX_INTERRUPT_DES_SELECTION_0 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_TX_CAT2_ISR0) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER013_TX_CAT2_ISR_0)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_TX_ISR_0(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_SelTxIsr(CAN_PHYIDX_INTERRUPT_SELECTION0);
}
#endif

#if (CAN_TX_INTERRUPT_DES_SELECTION_1 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_TX_CAT2_ISR1) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER013_TX_CAT2_ISR_1)                                                                                    /* PRQA S 0777, 1503, 3408 # JV-01, JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_TX_ISR_1(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_SelTxIsr(CAN_PHYIDX_INTERRUPT_SELECTION1);
}
#endif

#if (CAN_TX_INTERRUPT_DES_SELECTION_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_TX_CAT2_ISR2) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER013_TX_CAT2_ISR_2)                                                                                    /* PRQA S 0777, 1503, 3408 # JV-01, JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_TX_ISR_2(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_SelTxIsr(CAN_PHYIDX_INTERRUPT_SELECTION2);
}
#endif

#if (CAN_TX_INTERRUPT_DES_SELECTION_3 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_TX_CAT2_ISR3) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER013_TX_CAT2_ISR_3)                                                                                    /* PRQA S 0777, 1503, 3408 # JV-01, JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_TX_ISR_3(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_SelTxIsr(CAN_PHYIDX_INTERRUPT_SELECTION3);
}
#endif
#endif /* #if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON)*/

/***********************************************************************************************************************
** Function Name         : Can_SubErrorIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each Can_ErrorIsr.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucCtrlIndex, LucUnit, LucCh
**
** InOut Parameters      : LulRegERFLMask
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : CanEnableSecurityEventReporting is configured as true
**
** Global Variables Used : Can_GpConfig, Can_GpPCController,
**                         Can_GaaRegs, Can_GaaCtrlState
**
** Functions Invoked     : CanIf_ControllerErrorStatePassive, CanIf_ErrorNotification
**
** Registers Used        : (CFD)CmSTS, (CFD)CmERFL
**
** Reference ID          : CAN_DUD_ACT_063
***********************************************************************************************************************/
#if defined (CAN_CONTROLLER_ERROR_INTERRUPT_ON) && (CAN_CHECK_SECURITY_EVENT_REPORTING == STD_ON)
STATIC FUNC(uint32, CAN_CODE_FAST) Can_SubErrorIsr(VAR(uint8, AUTOMATIC) LucCtrlIndex, VAR(uint8, AUTOMATIC) LucUnit, 
                                                   VAR(uint8, AUTOMATIC) LucCh, VAR(uint32, AUTOMATIC) LulRegERFLMask)
{
  VAR(uint16, AUTOMATIC) LusTxErrorCounter;
  VAR(uint16, AUTOMATIC) LusRxErrorCounter;
  VAR(uint8, AUTOMATIC) LucFormIndex;
  VAR(uint32, AUTOMATIC) LusCheckErrBit;
  VAR(uint8, AUTOMATIC) LucSubCtrlIndex;
  VAR(uint32, AUTOMATIC) LulSubRegERFLMask;
  
  const Can_ErrorType LaaErrorForm[CAN_RSCAN_NUM_OF_BUS_ERROR] = 
  {
    CAN_ERROR_OVERLOAD, 
    CAN_ERROR_BUS_LOCK,
    CAN_ERROR_ARBITRATION_LOST,
    CAN_ERROR_CHECK_STUFFING_FAILED,
    CAN_ERROR_CHECK_FORM_FAILED,
    CAN_ERROR_CHECK_ACK_FAILED,
    CAN_ERROR_CHECK_CRC_FAILED,
    CAN_ERROR_BIT_MONITORING1,
    CAN_ERROR_BIT_MONITORING0,
    CAN_ERROR_ACK_DELIMITER
  };
  
  LucSubCtrlIndex = LucCtrlIndex;
  LulSubRegERFLMask = LulRegERFLMask;
  LucFormIndex = 0U;

  LucSubCtrlIndex = LucSubCtrlIndex + (uint8)CAN_CONTROLLER_OFFSET;                                                     /* PRQA S 2985 # JV-01 */
  
  /* Check if Error Passive flag is set or not*/
  if(0UL != (Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulERFL & CAN_RSCAN_EPF))
  {
    LusRxErrorCounter = (uint16)((Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulSTS
                        & CAN_RSCAN_REC_MASK) >> CAN_RSCAN_REC_OFFSET);
    LusTxErrorCounter = (uint16)((Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulSTS
                        & CAN_RSCAN_TEC_MASK) >> CAN_RSCAN_TEC_OFFSET);
    CanIf_ControllerErrorStatePassive(LucSubCtrlIndex, LusRxErrorCounter, LusTxErrorCounter);
    LulSubRegERFLMask = LulSubRegERFLMask | CAN_RSCAN_EPF;
  }/*else No action required */
  
  /* Check if Bus Error Flag is set or not */
  LusCheckErrBit = Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulERFL & CAN_RSCAN_BEF;
  LulSubRegERFLMask = LulSubRegERFLMask | LusCheckErrBit;

  while(CAN_RSCAN_NUM_OF_BUS_ERROR > LucFormIndex)
  {
    /* Check if error bit is set or not*/
    LusCheckErrBit = (Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulERFL >> CAN_RSCAN_BIT_ERROR_POS(LucFormIndex))        /* PRQA S 3383 # JV-01 */
                                                                                        & CAN_RSCAN_CHECK_BIT_SET;

    if(0UL != LusCheckErrBit)
    {
      CanIf_ErrorNotification(LucSubCtrlIndex, LaaErrorForm[LucFormIndex]);
      /* Mask Error bit to clear error flag */
      LulSubRegERFLMask = LulSubRegERFLMask | (LusCheckErrBit << CAN_RSCAN_BIT_ERROR_POS(LucFormIndex));                /* PRQA S 3383 # JV-01 */
    }
    LucFormIndex++;  
  }
  /* Mask Error Warning Flag and Bus-Off Recovery Flag */ 
  LulSubRegERFLMask = LulSubRegERFLMask | (CAN_RSCAN_EWF | CAN_RSCAN_BORF);
  return (LulSubRegERFLMask);
}
#endif

/***********************************************************************************************************************
** Function Name         : Can_SelErrorIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each ERROR_ISR Selection
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucInterruptSelId : Physical number of interrupt selection
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Preconditions         : The availability of the index must be guaranteed
**                         by the upper layer.
**
** Preconditions         : None
**
** Global Variables Used : Can_GpConfig, Can_GpPCController,
**                         Can_IntselGaaRegs
**
** Functions Invoked     : Can_ErrorIsr, CAN_DEM_REPORT_ERROR
**
** Registers Used        : INTCANFDERMONn
**
** Reference ID          : CAN_DUD_ACT_072
** Reference ID          : CAN_DUD_ACT_072_ERR001, CAN_DUD_ACT_072_REG001
** Reference ID          : CAN_DUD_ACT_072_GBL001
***********************************************************************************************************************/
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON)
#ifdef CAN_CONTROLLER_ERROR_INTERRUPT_ON
STATIC FUNC(void, CAN_CODE_FAST) Can_SelErrorIsr(CONST(uint8, AUTOMATIC) LucInterruptSelId)
{
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  VAR(uint8, AUTOMATIC) LucUnit;
  VAR(uint8, AUTOMATIC) LucCh;
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;

  #if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* If no irq exists from RS-CAN, this interrupt is wrong */
  if (0U == *Can_IntselGaaRegs[LucInterruptSelId].pERMON)
  {
    CAN_DEM_REPORT_ERROR(CAN_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
    /* Loop for the number of Controllers configured */
    for (LucCtrlIndex = 0U; LucCtrlIndex < Can_GpConfig->ucNoOfControllers; LucCtrlIndex++)                             /* PRQA S 3416 # JV-01 */
    {
      LpPCController = &Can_GpPCController[LucCtrlIndex];
      /* Check controller activation bit */
      if(CAN_TRUE == LpPCController->blActivation)
      {
        LucUnit = LpPCController->ucUnit;
        LucCh = LpPCController->ucCh;
        if ((1UL == ((*Can_IntselGaaRegs[LucInterruptSelId].pERMON >> 
                  (LucCh + (LucUnit * CAN_MAX_CHANNEL_PER_UNIT))) & 1UL))                                               /* PRQA S 3383 # JV-01 */
                  && (0UL == ((uint32)(*Can_IntselGaaRegs[LucInterruptSelId].pERMSK >> 
                  (LucCh + (LucUnit * CAN_MAX_CHANNEL_PER_UNIT))) & 1UL)))                                              /* PRQA S 3383 # JV-01 */
        {
          Can_ErrorIsr(LucCtrlIndex);
        } /* else No action required */
      } /* else No action required */
    }
  }
}
#endif /* #ifdef CAN_CONTROLLER_ERROR_INTERRUPT_ON */
#endif /* #if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON)*/

/***********************************************************************************************************************
** Function Name         : Can_ErrorIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each BUS_ERROR_ISR.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucController (U2Bx, U2Bx-E) : Physical number of Controller
**                         LucCtrlIndex (U2Cx) : Physical number of Controller
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of the index must be guaranteed
**                         by the upper layer.
**
** Global Variables Used : Can_GpConfig, Can_GpPCController,
**                         Can_GaaRegs, Can_GaaCtrlState
**
** Functions Invoked     : CanIf_ControllerBusOff, Can_SubErrorIsr, CAN_DEM_REPORT_ERROR
**
** Registers Used        : (CFD)CmCTR, (CFD)ERFL, EICn, (INTCANFD)ERMONn
**                         (CFD)GSTS (for dummy read only), (INTCANFD)ERMSKn
**
** Reference ID          : CAN_DUD_ACT_030
** Reference ID          : CAN_DUD_ACT_030_CRT001, CAN_DUD_ACT_030_CRT002,
** Reference ID          : CAN_DUD_ACT_030_ERR001, CAN_DUD_ACT_030_GBL001,
** Reference ID          : CAN_DUD_ACT_030_GBL002, CAN_DUD_ACT_030_GBL003,
** Reference ID          : CAN_DUD_ACT_030_REG001, CAN_DUD_ACT_030_REG002
***********************************************************************************************************************/
#ifdef CAN_CONTROLLER_ERROR_INTERRUPT_ON
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
STATIC FUNC(void, CAN_CODE_FAST) Can_ErrorIsr(CONST(uint8, AUTOMATIC) LucController)                                    /* PRQA S 3006 # JV-01 */
#else
STATIC FUNC(void, CAN_CODE_FAST) Can_ErrorIsr(CONST(uint8, AUTOMATIC) LucCtrlIndex)                                     /* PRQA S 3006 # JV-01 */
#endif
{
  #if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
  VAR(uint8, AUTOMATIC) LucCtrlIndex;
  #endif
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpPCController;
  VAR(uint8, AUTOMATIC) LucUnit;
  VAR(uint8, AUTOMATIC) LucCh;
  #if (CAN_BUSOFF_INTERRUPT == STD_ON)
  VAR(boolean, AUTOMATIC) LblNotificationRequired;
  #endif
  #if (CAN_CHECK_SECURITY_EVENT_REPORTING == STD_ON)
  VAR(uint32, AUTOMATIC) LulRegERFLMask;
  #endif

  #if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
  /* Convert the physical Controller index to the config index */
  LucCtrlIndex = Can_GpConfig->pPhysicalControllerToIndex[LucController];
  #endif
  LpPCController = &Can_GpPCController[LucCtrlIndex];
  LucUnit = LpPCController->ucUnit;
  LucCh = LpPCController->ucCh;
  #if (CAN_CHECK_SECURITY_EVENT_REPORTING == STD_ON)
  LulRegERFLMask = 0UL;
  #endif
  #if (CAN_BUSOFF_INTERRUPT == STD_ON)
  LblNotificationRequired = CAN_FALSE;
  #endif
  #if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
  #if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON) 
  /* If no irq exists from RS-CAN or EIC is masked, this interrupt is wrong */
  if ((0UL == (CAN_RSCAN_GET_EIEBITS(Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulCTR) &                                 /* PRQA S 3469, 0404 # JV-01, JV-01 */
                CAN_RSCAN_GET_EFBITS(Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulERFL))) ||                             /* PRQA S 3469 # JV-01 */
      ((uint16)(*LpPCController->pICErr & (CAN_EIC_EIMK_MASK | CAN_EIC_EIRF_MASK)) != CAN_EIC_EIRF_MASK))
  {
    CAN_DEM_REPORT_ERROR(CAN_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  #endif
  {
    #if (CAN_BUSOFF_INTERRUPT == STD_ON)
    /* Check whether Busoff event is occurred or not */
    if(0UL != ((uint32)LpPCController->ucIntEnable & (uint32)CAN_CHECK_INT_BUSOFF))
    {
      if (0UL != (Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulERFL & CAN_RSCAN_BOEF))
      {
        /*
          * The transition START to STOP is done by the following triggers:
          *  - Can_SetControllerMode(CAN_COMMON_STATE_STOPPED)
          *  - Busoff
          * To avoid the state transition is done twice by both of triggers,
          * the exclusive control is required.
          */
        CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
        if ((CAN_COMMON_STATE_STARTED == Can_GaaCtrlState[LucCtrlIndex].enMode) &&
            (CAN_NO_PENDING_TRANSITION == Can_GaaCtrlState[LucCtrlIndex].enSubState))
        {
          /* Set bus-off flag */
          Can_GaaCtrlState[LucCtrlIndex].blBusOff = CAN_TRUE;
          /* When busoff has been occured, HW is CHANNLE_HALT mode already.
              So no additional operation is required, just set the mode. */
          Can_GaaCtrlState[LucCtrlIndex].enMode = CAN_COMMON_STATE_STOPPED;
          Can_GaaCtrlState[LucCtrlIndex].enSubState = CAN_NO_PENDING_TRANSITION;
          /* Notification for CanIf is required */
          LblNotificationRequired = CAN_TRUE;
        } /* else no action required*/
        CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
        if (CAN_TRUE == LblNotificationRequired)
        {
          CanIf_ControllerBusOff((uint8)(LucCtrlIndex + CAN_CONTROLLER_OFFSET));                                        /* PRQA S 3383, 2985 # JV-01, JV-01 */
        } /* else No action required */
        /* Mask bus off error flag */
        #if (CAN_CHECK_SECURITY_EVENT_REPORTING == STD_ON)
        LulRegERFLMask = LulRegERFLMask | CAN_RSCAN_BOEF;
        #endif
      }  
    } /*else No action required */
    #endif
    /* Check whether Can Bus Error event is occurred or not */
    #if (CAN_CHECK_SECURITY_EVENT_REPORTING == STD_ON)
    LulRegERFLMask = Can_SubErrorIsr(LucCtrlIndex, LucUnit, LucCh, LulRegERFLMask);
    /* Clear all error flags */
    RH850_SV_MODE_REG_AND(32, &Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulERFL, ~LulRegERFLMask);                      /* PRQA S 3464 # JV-01 */
    #else
    Can_GaaRegs[LucUnit].pCmn->aaChReg[LucCh].ulERFL = CAN_RSCAN_ERFL_CLEAR;
    #endif
    CAN_ENTER_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    /* DummyRead & SYNCP */
    RH850_SET_IOREG_SYNCP(32, &Can_GaaRegs[LucUnit].pCmn->ulGSTS, 0UL);                                                 /* PRQA S 3464, 1006 # JV-01, JV-01 */
    CAN_EXIT_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  }
}
#endif /* (CAN_CONTROLLER_BUS_ERROR_INTERRUPT_ON) */

/***********************************************************************************************************************
** Function Name         : CAN_CONTROLLERm_ERROR_ISR
**
** Service ID            : Not Applicable
**
** Description           : This is BUS ERROR Interrupt Service routines for the Can
**                         hardware unit.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Can_ErrorIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_022
** Reference ID          : CAN_DUD_ACT_059
***********************************************************************************************************************/
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)
#if (CAN_CONTROLLER0_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER0_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER0_ERROR_CAT2_ISR)                                                                                     /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER0_ERROR_ISR(void)                                                   /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER0);
}
#endif

#if (CAN_CONTROLLER1_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER1_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER1_ERROR_CAT2_ISR)                                                                                     /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER1_ERROR_ISR(void)                                                   /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER1);
}
#endif

#if (CAN_CONTROLLER2_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER2_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER2_ERROR_CAT2_ISR)                                                                                     /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER2_ERROR_ISR(void)                                                   /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER2);
}
#endif

#if (CAN_CONTROLLER3_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER3_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER3_ERROR_CAT2_ISR)                                                                                     /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER3_ERROR_ISR(void)                                                   /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER3);
}
#endif

#if (CAN_CONTROLLER4_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER4_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER4_ERROR_CAT2_ISR)                                                                                     /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER4_ERROR_ISR(void)                                                   /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER4);
}
#endif

#if (CAN_CONTROLLER5_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER5_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER5_ERROR_CAT2_ISR)                                                                                     /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER5_ERROR_ISR(void)                                                   /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER5);
}
#endif

#if (CAN_CONTROLLER6_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER6_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER6_ERROR_CAT2_ISR)                                                                                     /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER6_ERROR_ISR(void)                                                   /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER6);
}
#endif

#if (CAN_CONTROLLER7_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER7_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER7_ERROR_CAT2_ISR)                                                                                     /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER7_ERROR_ISR(void)                                                   /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER7);
}
#endif

#if (CAN_CONTROLLER8_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER8_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER8_ERROR_CAT2_ISR)                                                                                     /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER8_ERROR_ISR(void)                                                   /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER8);
}
#endif

#if (CAN_CONTROLLER9_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER9_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER9_ERROR_CAT2_ISR)                                                                                     /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER9_ERROR_ISR(void)                                                   /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER9);
}
#endif

#if (CAN_CONTROLLER10_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER10_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER10_ERROR_CAT2_ISR)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER10_ERROR_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER10);
}
#endif

#if (CAN_CONTROLLER11_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER11_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER11_ERROR_CAT2_ISR)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER11_ERROR_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER11);
}
#endif

#if (CAN_CONTROLLER12_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER12_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER12_ERROR_CAT2_ISR)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER12_ERROR_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER12);
}
#endif

#if (CAN_CONTROLLER13_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER13_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER13_ERROR_CAT2_ISR)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER13_ERROR_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER13);
}
#endif

#if (CAN_CONTROLLER14_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER14_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER14_ERROR_CAT2_ISR)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER14_ERROR_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER14);
}
#endif

#if (CAN_CONTROLLER15_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER15_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER15_ERROR_CAT2_ISR)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER15_ERROR_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER15);
}
#endif

#if (CAN_CONTROLLER16_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER16_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER16_ERROR_CAT2_ISR)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER16_ERROR_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER16);
}
#endif

#if (CAN_CONTROLLER17_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER17_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER17_ERROR_CAT2_ISR)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER17_ERROR_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER17);
}
#endif

#if (CAN_CONTROLLER18_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER18_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER18_ERROR_CAT2_ISR)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER18_ERROR_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER18);
}
#endif

#if (CAN_CONTROLLER19_ERROR_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER19_ERROR_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER19_ERROR_CAT2_ISR)                                                                                    /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER19_ERROR_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_ErrorIsr(CAN_PHYIDX_CONTROLLER19);
}
#endif

#endif /* #if (CAN_ORED_INTERRUPT_FUNCTION == STD_OFF)*/

/***********************************************************************************************************************
** Function Name         : CAN_CONTROLLER013_ERROR_ISR_n
**
** Service ID            : Not Applicable
**
** Description           : This is BUS ERROR Interrupt Selection Service routines for the Can
**                         hardware unit.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Can_SelErrorIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_073
** Reference ID          : CAN_DUD_ACT_184
***********************************************************************************************************************/
#if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON)
#if (CAN_ERROR_INTERRUPT_DES_SELECTION_0 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_ERROR_CAT2_ISR0) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER013_ERROR_CAT2_ISR_0)                                                                                 /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_ERROR_ISR_0(void)                                               /* PRQA S 1503 # JV-01 */
#endif
{
  Can_SelErrorIsr(CAN_PHYIDX_INTERRUPT_SELECTION0);
}
#endif

#if (CAN_ERROR_INTERRUPT_DES_SELECTION_1 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_ERROR_CAT2_ISR1) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER013_ERROR_CAT2_ISR_1)                                                                                 /* PRQA S 0777, 1503, 3408 # JV-01, JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_ERROR_ISR_1(void)                                               /* PRQA S 1503 # JV-01 */
#endif
{
  Can_SelErrorIsr(CAN_PHYIDX_INTERRUPT_SELECTION1);
}
#endif

#if (CAN_ERROR_INTERRUPT_DES_SELECTION_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_ERROR_CAT2_ISR2) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER013_ERROR_CAT2_ISR_2)                                                                                 /* PRQA S 0777, 1503, 3408 # JV-01, JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_ERROR_ISR_2(void)                                               /* PRQA S 1503 # JV-01 */
#endif
{
  Can_SelErrorIsr(CAN_PHYIDX_INTERRUPT_SELECTION2);
}
#endif

#if (CAN_ERROR_INTERRUPT_DES_SELECTION_3 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER013_ERROR_CAT2_ISR3) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER013_ERROR_CAT2_ISR_3)                                                                                 /* PRQA S 0777, 1503, 3408 # JV-01, JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER013_ERROR_ISR_3(void)                                               /* PRQA S 1503 # JV-01 */
#endif
{
  Can_SelErrorIsr(CAN_PHYIDX_INTERRUPT_SELECTION3);
}
#endif
#endif /* #if (CAN_ORED_INTERRUPT_FUNCTION == STD_ON)*/

#if (CAN_WAKEUP_SUPPORT == STD_ON)
/***********************************************************************************************************************
** Function Name         : Can_WakeupIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each WAKEUP_ISR
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucController
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of the index must be guaranteed by
**                         the upper layer.
**
** Global Variables Used : Can_GpConfig, Can_GpPCController,
**                         Can_GaaCtrlState
**
** Functions Invoked     : EcuM_CheckWakeup(), Can_WakeupMode(), CAN_DEM_REPORT_ERROR
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_031
** Reference ID          : CAN_DUD_ACT_031_CRT001, CAN_DUD_ACT_031_CRT002,
** Reference ID          : CAN_DUD_ACT_031_ERR001, CAN_DUD_ACT_031_GBL001,
** Reference ID          : CAN_DUD_ACT_031_GBL002, CAN_DUD_ACT_031_REG001,
** Reference ID          : CAN_DUD_ACT_031_REG002
***********************************************************************************************************************/
#ifdef CAN_CONTROLLER_WAKEUP_INTERRUPT_ON
STATIC FUNC(void, CAN_CODE_FAST) Can_WakeupIsr(CONST(uint8, AUTOMATIC) LucController,                                   /* PRQA S 3006 # JV-01 */
                                                                   Can_ControllerType LenControllerType)                /* PRQA S 3006, 3206 # JV-01, JV-01 */
{
  P2CONST(Can_ControllerPCConfigType, AUTOMATIC, CAN_APPL_DATA) LpPCController;
  VAR(uint32, AUTOMATIC) LucCtrlIndex;
  VAR(boolean, AUTOMATIC) LblCheckWakeupRequired;

  /* Convert the physical Controller index to the config index */
  #if (CAN_CANXL_SUPPORTED == STD_ON)
  if(CAN_XL == LenControllerType)
  {
    LucCtrlIndex = Can_GpConfig->pCanXLPhysicalControllerToIndex[LucController];
  }
  else
  #endif
  {
    LucCtrlIndex = Can_GpConfig->pPhysicalControllerToIndex[LucController];
  }
  /* Getting the pointer to pre-compile controller structure*/
  LpPCController = &Can_GpPCController[LucCtrlIndex];

  #if (CAN_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* If the interrupt is masked, this interrupt is wrong */
  if ((NULL_PTR == LpPCController->pICWakeup) ||
      (0U != (*LpPCController->pICWakeup & (uint16)CAN_EIC_EIMK_MASK)))
  {
    CAN_DEM_REPORT_ERROR(CAN_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
    /* Critical section is required to avoid the conflict with
       Can_EnableControllerInterrupt and Can_SetControllerMode */
    CAN_ENTER_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    /*Disabling the interrupt*/
    RH850_SV_MODE_ICR_OR(8, LpPCController->pICWakeup, CAN_EIC_EIMK_MASK);                                              /* PRQA S 0751 # JV-01 */
    /* DummyRead & SYNCP */
    RH850_SV_MODE_REG_READ_ONLY(16, LpPCController->pICWakeup);
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
    #ifdef CAN_FILTER_CONTROL_SUPPORT
    if (NULL_PTR != LpPCController->pFCLAReg)
    {
      /* Clear the filter control register to reset value */
      *LpPCController->pFCLAReg = CAN_RSCAN_FCLA_DISABLE;
    } /* else No action required */
    #endif
    /* Confirm that state transition is not on-going by Can_SetControllerMode */
    if ((CAN_COMMON_STATE_SLEEP == Can_GaaCtrlState[LucCtrlIndex].enMode) &&
        (CAN_NO_PENDING_TRANSITION == Can_GaaCtrlState[LucCtrlIndex].enSubState))
    {
      /* The state transition takes a long time,
         the subsequent operation will be done in Can_MainFunction_Mode */
      Can_GaaCtrlState[LucCtrlIndex].enSubState = CAN_PENDING_WAKEUP_REQUESTED; 
      /* Store the wakeup event */
      Can_GaaCtrlState[LucCtrlIndex].blWakeupEventOccurred = CAN_TRUE;
      Can_GaaCtrlState[LucCtrlIndex].blWakeupByHW = CAN_TRUE;
      LblCheckWakeupRequired = CAN_TRUE;
    }
    else
    {
      /* If the state transition is already on-going, nothing to do */
      LblCheckWakeupRequired = CAN_FALSE;
    }
    CAN_EXIT_CRITICAL_SECTION(CAN_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

    if (CAN_TRUE == LblCheckWakeupRequired)
    {
      Can_WakeupMode((uint8)LucCtrlIndex);
      /* Invoke EcuM_CheckWakeup call-back function to give wakeup */
      /* notification */
      EcuM_CheckWakeup((EcuM_WakeupSourceType)(CAN_ONE << LpPCController->ucWakeupSourceId));
    } /* else No action required */
  }
}
#endif /* (CAN_CONTROLLERn_WAKEUP_INTERRUPT == STD_ON) */

/***********************************************************************************************************************
** Function Name         : CAN_CONTROLLERm_WAKEUP_ISR
**
** Service ID            : Not Applicable
**
** Description           :This is WAKEUPx Interrupt Service routines for the Can
**                         hardware unit.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Can_WakeupIsr
**
** Registers Used        : None
**
** Reference ID          : CAN_DUD_ACT_023
** Reference ID          : CAN_DUD_ACT_060
***********************************************************************************************************************/
#if (CAN_CONTROLLER0_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER0_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER0_WAKEUP_CAT2_ISR)                                                                                    /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER0_WAKEUP_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER0, CAN_FD);
}
#endif

#if (CAN_CONTROLLER1_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER1_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER1_WAKEUP_CAT2_ISR)                                                                                    /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER1_WAKEUP_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER1, CAN_FD);
}
#endif

#if (CAN_CONTROLLER2_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER2_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER2_WAKEUP_CAT2_ISR)                                                                                    /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER2_WAKEUP_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER2, CAN_FD);
}
#endif

#if (CAN_CONTROLLER3_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER3_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER3_WAKEUP_CAT2_ISR)                                                                                    /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER3_WAKEUP_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER3, CAN_FD);
}
#endif

#if (CAN_CONTROLLER4_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER4_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER4_WAKEUP_CAT2_ISR)                                                                                    /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER4_WAKEUP_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER4, CAN_FD);
}
#endif

#if (CAN_CONTROLLER5_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER5_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER5_WAKEUP_CAT2_ISR)                                                                                    /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER5_WAKEUP_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER5, CAN_FD);
}
#endif

#if (CAN_CONTROLLER6_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER6_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER6_WAKEUP_CAT2_ISR)                                                                                    /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER6_WAKEUP_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER6, CAN_FD);
}
#endif

#if (CAN_CONTROLLER7_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER7_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER7_WAKEUP_CAT2_ISR)                                                                                    /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER7_WAKEUP_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER7, CAN_FD);
}
#endif

#if (CAN_CONTROLLER8_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER8_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER8_WAKEUP_CAT2_ISR)                                                                                    /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER8_WAKEUP_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER8, CAN_FD);
}
#endif

#if (CAN_CONTROLLER9_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER9_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER9_WAKEUP_CAT2_ISR)                                                                                    /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER9_WAKEUP_ISR(void)                                                  /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER9, CAN_FD);
}
#endif

#if (CAN_CONTROLLER10_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER10_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER10_WAKEUP_CAT2_ISR)                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER10_WAKEUP_ISR(void)                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER10, CAN_FD);
}
#endif

#if (CAN_CONTROLLER11_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER11_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER11_WAKEUP_CAT2_ISR)                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER11_WAKEUP_ISR(void)                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER11, CAN_FD);
}
#endif

#if (CAN_CONTROLLER12_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER12_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER12_WAKEUP_CAT2_ISR)                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER12_WAKEUP_ISR(void)                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER12, CAN_FD);
}
#endif

#if (CAN_CONTROLLER13_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER13_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER13_WAKEUP_CAT2_ISR)                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER13_WAKEUP_ISR(void)                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER13, CAN_FD);
}
#endif

#if (CAN_CONTROLLER14_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER14_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER14_WAKEUP_CAT2_ISR)                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER14_WAKEUP_ISR(void)                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER14, CAN_FD);
}
#endif

#if (CAN_CONTROLLER15_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER15_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER15_WAKEUP_CAT2_ISR)                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER15_WAKEUP_ISR(void)                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER15, CAN_FD);
}
#endif

#if (CAN_CONTROLLER16_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER16_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER16_WAKEUP_CAT2_ISR)                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER16_WAKEUP_ISR(void)                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER16, CAN_FD);
}
#endif

#if (CAN_CONTROLLER17_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER17_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER17_WAKEUP_CAT2_ISR)                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER17_WAKEUP_ISR(void)                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER17, CAN_FD);
}
#endif

#if (CAN_CONTROLLER18_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER18_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER18_WAKEUP_CAT2_ISR)                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER18_WAKEUP_ISR(void)                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER18, CAN_FD);
}
#endif

#if (CAN_CONTROLLER19_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CAN_CONTROLLER19_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CAN_CONTROLLER19_WAKEUP_CAT2_ISR)                                                                                   /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CAN_CONTROLLER19_WAKEUP_ISR(void)                                                 /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER19, CAN_FD);
}
#endif

#if (CAN_CANXL_SUPPORTED == STD_ON)
#if (CANXL_CONTROLLER0_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CANXL_CONTROLLER0_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CANXL_CONTROLLER0_WAKEUP_CAT2_ISR)                                                                                  /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CANXL_CONTROLLER0_WAKEUP_ISR(void)                                                /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER0, CAN_XL);
}
#endif

#if (CANXL_CONTROLLER1_WAKEUP_INTERRUPT == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_CANXL_CONTROLLER1_WAKEUP_CAT2_ISR) || (CAN_ISR_CATEGORY_2 == STD_ON)
ISR(CANXL_CONTROLLER1_WAKEUP_CAT2_ISR)                                                                                  /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, CAN_CODE_FAST) CANXL_CONTROLLER1_WAKEUP_ISR(void)                                                /* PRQA S 1503 # JV-01 */
#endif
{
  Can_WakeupIsr(CAN_PHYIDX_CONTROLLER1, CAN_XL);
}
#endif
#endif

#endif /* (CAN_WAKEUP_SUPPORT == STD_ON) */

#define CAN_STOP_SEC_CODE_FAST
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
