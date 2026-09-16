/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can_Write.c                                                                                         */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Transmission of L-PDU(s).                                                                                          */
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
/*              Devices:       X2x                                                                                    */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                                  Revision History                                                  **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025  : Update Can_PrepareCanFdTxDesc
 *                      Fixing QAC message
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                    : Add message 0404, 0489, 3415 to support QA-C version 11.6.0
 * 2.3.0: 28/02/2025  : Update SW-VERSION for RH850/Ver22.01.00/Ver22.01.00.D Final Release
 *                      As part of ARDAACL-52560: Update Can_PrepareCanFdTxDesc
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                      As part of CANXL driver support, following changes are made:
 *                      1. Update Can_Write, Can_PrepareCanFdTxDesc
 * 2.1.2: 31/10/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Fixing QAC message. Remove messages: 3416, 3415, 0404
 *                      2. Change ucTMDLC to usTMDLC
 * 2.1.1: 30/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update Can_PrepareCanFdTxDesc
 *                      2. Update API Can_Write
 *                      3. Update API Can_PrepareCanFdTxDesc to fix issue related to RX_FQ_INT_STS,
 *                      TX_FQ_INT_STS register 
 *                      4. Add macro for CANFD on CANXL bus.
 *                      5. Add Can_PrepareCanFdTxDesc.
 *                      6. Update Can_Write support CANFD on CANXL bus.
 *                      7. Add header message 2995, 0316, 0306, 0488, 2986, 0306, 0310, 0311, 3305, 0489
 *                      8. Change Can_GpConfig->pCoreID2Index[] to Can_GpPBController[].ucCoreId
 *                      9. Change Can_GpPCController[].ucCoreId to Can_GpConfig->pCoreID2Index[]
 *        01/06/2024  : Remove message 1534, 1536
 * 2.0.1: 19/10/2023  : Remove message 3214, 0857, 2844, 2814, 2914, 2916, 2824
 *                      Add message 3415, 3416, 0404, 1534, 1536
 *        14/10/2023  : Change macro CAN_AR_R21_11_VERSION to CAN_AR_R22_11_VERSION
 * 2.0.0: 16/08/2023  : Update LenReturnValue of Det_ReportError in Can_Write
 *        02/08/2023  : Update function Can_Write to support multi core
 *                      Change from Can_Mapping.h to Can_MemMap.h
 *                      Add QAC message 2962
 *                      Update description of function
 *                      Add CWE Rule
 *                      Remove redundant QAC messages
 *        28/06/2023  : Remove redundant QAC messages
 *        31/05/2023  : Remove redundant QAC messages
 * 1.5.0: 27/03/2023  : Add AUTOSAR release version information AUTOSAR R21-11
 * 1.4.3: 11/05/2022  : Change CTR_REG to CAN_CTR_REG; PTR_REG to CAN_PTR_REG; COMMON_OK to CAN_COMMON_OK;
 *                      COMMON_NOT_OK to CAN_COMMON_NOT_OK; Common_ReturnType to Can_CommonReturnType
 *                      Add QAC message
 *        10/05/2022  : Remove "else" statement don't use when no action required. 
 * 1.3.2: 30/08/2021  : Update to support multi-instance:
 *                      - Change include to Can_Mapping.h
 * 1.3.1: 02/07/2021  : Add QAC message 9.5.0
 *                      Format source code to 120 characters
 *                      Improve Violation tag (remove START/END)
 *        05/05/2021  : Update the memory section, memclass, ptrclass to change
 *                      the CAN_RSCAN prefix to CAN.
 *                      Add STag_Can_TxRegSetType for struct Can_TxRegSetType
 *                      Function Can_Write, create a local variable
 *                      Std_ReturnType LenCanIfResult, to store return value
 *                      of CanIf_TriggerTransmit.
 * 1.3.0: 23/01/2021  : Function Can_GetTxRegPointers:
 *                      + Change memclass of CONSTP2VAR input parameter from
 *                      CAN_RSCAN_PRIVATE_CONST to CAN_RSCAN_APPL_DATA.
 * 1.2.0: 09/07/2020  : Release.
 *        28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020  : Release.
 * 1.0.2: 26/05/2020  : As per #270097, Remove Critical Protection for single
 *                      instruction in Can_Write.
 *        16/04/2020  : As per #266255, Implement Mutex in Can_Write
 *        19/03/2020  : Updated Global Variables Used in function description.
 *                      Update QAC MISRA rule from 2004 to 2012.
 *                      Add Justification for QAC warning.
 * 1.0.1: 16/01/2020  : Update Can_Write function to not report to DET when
 *                      CanIf_TriggerTransmit returns E_NOT_OK to comply with
 *                      AUTOSAR version 4.3.1
 *        10/01/2020  : Update error code name CAN_E_PARAM_DLC to
 *                      CAN_E_PARAM_DATA_LENGTH to comply with AUTOSAR version
 *                      4.3.1
 *        09/01/2020  : Support AUTOSAR version 4.3.1
 *                      - Use Common_ReturnType as representative of
 *                        Can_ReturnType and Std_ReturnType depending on
 *                        AUTOSAR Version
 * 1.0.0: 09/12/2019  : Initial version.
 */
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* CAN module header file */
#include "Can.h"
/* Included for RAM variable declarations */
#include "Can_Ram.h"
#if (CAN_DEV_ERROR_DETECT == STD_ON)
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
#endif
/* CAN Interface call-back Header File */
#if (CAN_AR_VERSION == CAN_AR_R22_11_VERSION)
#include "CanIf_Can.h"
#else
#include "CanIf_Cbk.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define CAN_WRITE_C_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION_VALUE
#define CAN_WRITE_C_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION_VALUE
#define CAN_WRITE_C_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define CAN_WRITE_C_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION_VALUE
#define CAN_WRITE_C_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (CAN_AR_RELEASE_MAJOR_VERSION != CAN_WRITE_C_AR_RELEASE_MAJOR_VERSION)
  #error "Can_Write.c : Mismatch in Release Major Version"
#endif
#if (CAN_AR_RELEASE_MINOR_VERSION != CAN_WRITE_C_AR_RELEASE_MINOR_VERSION)
  #error "Can_Write.c : Mismatch in Release Minor Version"
#endif
#if (CAN_AR_RELEASE_REVISION_VERSION != CAN_WRITE_C_AR_RELEASE_REVISION_VERSION)
  #error "Can_Write.c : Mismatch in Release Revision Version"
#endif

#if (CAN_WRITE_C_SW_MAJOR_VERSION != CAN_SW_MAJOR_VERSION)
  #error "Can_Write.c : Mismatch in Software Major Version"
#endif
#if (CAN_WRITE_C_SW_MINOR_VERSION != CAN_SW_MINOR_VERSION)
  #error "Can_Write.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3206)    : The parameter '%s' is not used in this function.                                             */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.7, CWE Rule CWE-398, CWE-563, CWE-569              */
/* JV-01 Justification : This is done as per implementation requirement                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3213)    : The tag '%s' is not used and could be removed.                                               */
/* Rule                : MISRA C:2012 Rule-2.4                                                                        */
/* JV-01 Justification : According to the coding guide, all structure must be declared  with the tag "Stag". Since    */
/*                       these are normal type structure, there is no effect.                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : This is accepted. It just an advise for  improve safety by reducing the possibility that     */
/*                       the referenced data is unintentionally modified through an unexpected alias and improves     */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
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
/* Message (4:2985)    : This operation is redundant. The value of the result is always that of the left-hand operand.*/
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-398, CWE-561, CWE-569, CWE-633     */
/* JV-01 Justification : For readability, setting to registers will used redundant macros and is based on hardware    */
/*                       user's manual                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4                                                        */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5                                                                       */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4                                                        */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2986)    : This operation is redundant. The value of the result is always that of the right-hand        */
/*                       operand.                                                                                     */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : This operation is an important operation for calculating the decrement value as the          */
/*                       increment value, so it is necessary and not redundant.                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : CERTCCM EXP11, EXP39, MISRA C:2012 Rule-11.3                                                 */
/* JV-01 Justification : For accessing 8-bit and 16-bit PNOT and JPNOT register respectively, the 32-bit pointer is   */
/*                       typecasted.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:0311)    : Dangerous pointer cast results in loss of const qualification.                               */
/* Rule                : MISRA C:2012 Rule-11.8, CERTCCM EXP05                                                        */
/* JV-01 Justification : This is to achieve throughput in the code.                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:3305)    : Pointer cast to stricter alignment.                                                          */
/* Rule                : CERTCCM EXP36, EXP39, MISRA C:2012 Rule-11.3                                                 */
/* JV-01 Justification : It is an implementation required to manage heap memory. There is no problem because the      */
/*                       4-byte alignment boundary is guaranteed by the implementation of the heap memory             */
/*                       operation algorithm.                                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : MISRA C:2012 Rule-13.5, CERTCCM EXP02, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it does not have direct access to the HW register, and     */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0489)    : The integer value 1 is being added or subtracted from a pointer.                             */
/* Rule                : MISRA C:2012 Rule-18.4, CWE-188, CWE-468, CWE-398, CWE-465, CWE-569                          */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3473)    : This usage of a function-like setter macro looks like it could be replaced by a similar      */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message is an improvement to refactor function-like macros to be implemented as true C  */
/*                       functions. It not affect to driver operation and can be accepted                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
/* Byte offsets of SDU */
#define CAN_RSCAN_0_BYTE 0UL
#define CAN_RSCAN_1_BYTE 1UL
#define CAN_RSCAN_2_BYTE 2UL
#define CAN_RSCAN_3_BYTE 3UL

/* Structure to contain tx relevant registers */
#if ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON) || \
    (CANFD_ON_XL_BUS_SUPPORT == STD_ON))
typedef struct STag_Can_TxRegSetType                                                                                    /* PRQA S 3213 # JV-01 */
{
  #if (CAN_RSCANFD_CONFIGURED == STD_ON)
  /* Point CFDFDCSTS or CFDTMFDCTR */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pCTR;
  #endif
  /* Point (CFD)CFID or (CFD)TMID */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pID;
  /* Point (CFD)CFPTR or (CFD)TMPTR */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pPTR;
  /* Point (CFD)CFDF or (CFD)TMDF */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pDF;
  /* Point (CFD)CFPCTR or (CFD)TXQPCTR or (CFD)TMC */
  P2VAR(volatile uint8, TYPEDEF, REGSPACE) pTrig;
  /* When this value is written to pTrig, transmission is started */
  uint8 ucTrigValue;
} Can_TxRegSetType;
#endif

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#if ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON))
STATIC FUNC(Can_CommonReturnType, CAN_PRIVATE_CODE)
                              Can_GetTxRegPointers(CONSTP2VAR(Can_TxRegSetType, AUTOMATIC, CAN_APPL_DATA) LpRegSet,     /* PRQA S 3432 # JV-01 */
                                                  CONSTP2CONST(Can_HohConfigType, AUTOMATIC, CAN_PRIVATE_CONST) LpHoh);

STATIC FUNC(void, CAN_PRIVATE_CODE) Can_WriteDataReg(CONSTP2CONST(uint8, AUTOMATIC, CAN_PRIVATE_CONST) LpSrc,
                          CONSTP2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpDF, CONST(uint32, AUTOMATIC) LulSrcLength,
                          CONST(uint32, AUTOMATIC) LulDestLength, CONST(uint8, AUTOMATIC) LucPadding);
#endif
#if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_PrepareCanFdTxDesc(Can_HwHandleType Hth, const Can_PduType* PduInfo,
                        P2CONST(uint8, AUTOMATIC, CAN_APPL_DATA) LpSduPtr, uint16 LusSduLength,
                        P2VAR(Can_TxDescriptorsType, AUTOMATIC, RECAN_APPL_DATAGSPACE) Descriptor);                     /* PRQA S 3432 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Can_Write
**
** Service ID            : 0x06
**
** Description           : This function writes the L-PDU in an appropriate
**                         buffer inside the CAN Controller hardware. The CAN
**                         Driver stores the swPduhandle that is given inside
**                         parameter PduInfo until it calls the
**                         CanIf_TxConfirmation.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : HTH     : HOH ID
**                         PduInfo : Pointer to PDU information structure
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Can_CommonReturnType
**
** Preconditions         : The CAN Driver must be initialized.
**
** Global Variables Used : Can_GblInitialized, Can_GpConfig,
**                         Can_GpHohConfig, Can_GpPBController,
**                         Can_GaaCtrlState, Can_GaaRegs,
**                         Can_GpPCController, Can_GaaDLCFromPayloadTable,
**                         Can_GaaPayloadFromDLCTable, Can_GaaHwAccessFlag
**
** Functions Invoked     : Det_ReportError, CanXL_CheckBusyQueue, Can_PrepareCanFdTxDesc
**                         Can_GetTxRegPointers, Can_WriteDataReg,
**                         CAN_ENTER_CRITICAL_SECTION, CAN_EXIT_CRITICAL_SECTION
**
** Registers Used        : (CFD)CFFDCSTSk, (CFD)CFIDk, (CFD)CFPTRk,
**                         (CFD)CFPCTRk, (CFD)TMFDCTRp, (CFD)TMIDp,
**                         (CFD)TMPTRp, (CFD)TMCp, (CFD)TXQPCTRm,
**                         (CFD)TMSTSp
**
** Reference ID          : CAN_DUD_ACT_006
** Reference ID          : CAN_DUD_ACT_006_CRT001, CAN_DUD_ACT_006_CRT002,
** Reference ID          : CAN_DUD_ACT_006_ERR001, CAN_DUD_ACT_006_ERR002,
** Reference ID          : CAN_DUD_ACT_006_ERR003, CAN_DUD_ACT_006_ERR004,
** Reference ID          : CAN_DUD_ACT_006_ERR005, CAN_DUD_ACT_006_REG001,
** Reference ID          : CAN_DUD_ACT_006_REG002, CAN_DUD_ACT_006_REG003,
** Reference ID          : CAN_DUD_ACT_006_REG004, CAN_DUD_ACT_006_REG005,
** Reference ID          : CAN_DUD_ACT_006_REG006, CAN_DUD_ACT_006_REG007,
** Reference ID          : CAN_DUD_ACT_006_REG008, CAN_DUD_ACT_006_REG009,
** Reference ID          : CAN_DUD_ACT_006_GBL001, CAN_DUD_ACT_006_GBL002, CAN_DUD_ACT_006_GBL003
** Reference ID          : CAN_DUD_ACT_006_GBL004, CAN_DUD_ACT_006_ERR006
***********************************************************************************************************************/
#define CAN_START_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Can_CommonReturnType, CAN_PUBLIC_CODE)
            Can_Write(VAR(Can_HwHandleType, CAN_APPL_DATA) Hth, P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo) /* PRQA S 1503, 3206 # JV-01, JV-01 */
{
  VAR(Can_CommonReturnType, AUTOMATIC) LenReturnValue;
  #if ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON) || \
      (CANFD_ON_XL_BUS_SUPPORT == STD_ON))
  #if (CAN_TRIGGER_TRANSMIT_FUNCTION == STD_ON)
  VAR(PduInfoType, AUTOMATIC) LstTTPduInfo;
  VAR(uint32, AUTOMATIC) LaaTTSduData[CAN_LOCALBUFFER_SIZE_32];
  VAR(Std_ReturnType, AUTOMATIC) LenCanIfResult;
  #endif
  P2CONST(Can_HohConfigType, AUTOMATIC, CAN_APPL_DATA) LpHoh;
  VAR(uint8, AUTOMATIC) LucController;
  VAR(uint8, AUTOMATIC) LucSduLength;
  P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) LpSduPtr;                                                                      /* PRQA S 3432, 3678 # JV-01, JV-01 */
  VAR(boolean, AUTOMATIC) LblHohAccessFlag;
  #endif
  #if ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON))
  VAR(Can_TxRegSetType, AUTOMATIC) LstTxRegSet;
  VAR(uint32, AUTOMATIC) LulDLC;
  VAR(uint32, AUTOMATIC) LulActualLength;
  #endif
  #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpTargetDesc;                                                /* PRQA S 3432 # JV-01 */
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(Can_BufferType, AUTOMATIC) LenBufferType;
  #endif

  #if ((CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_MULTI_CORE_SUPPORT == STD_ON))
  VAR(uint8, AUTOMATIC) LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  #endif /* #if (CAN_MULTI_CORE_SUPPORT == STD_ON) */
  /**************************************************************************************************************/
  /**                                               DET Checking                                               **/
  /**************************************************************************************************************/
  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if module is not initialized */
  if (CAN_FALSE == Can_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_WRITE_SID, CAN_E_UNINIT);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  /* Report to DET, if HTH is out of range */
  else if ((Can_GpConfig->usNoOfHohs <= Hth) || (CAN_HOH_HTH != Can_GpHohConfig[Hth].enHoh))                            /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_WRITE_SID, CAN_E_PARAM_HANDLE);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core */
  else if (LucCoreId !=  Can_GpPBController[Can_GpHohConfig[Hth].ucController].ucCoreId)                                /* PRQA S 0404, 3416 # JV-01, JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_WRITE_SID, CAN_E_INVALID_CORE);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  #endif /* CAN_MULTI_CORE_SUPPORT == STD_ON */
  /* Report to DET, if PduInfo or SduPtr is  NULL */
  else if ((NULL_PTR == PduInfo) || ((NULL_PTR == PduInfo->sdu)
  #if (CAN_TRIGGER_TRANSMIT_FUNCTION == STD_ON)
                                     && (CAN_FALSE == Can_GpHohConfig[Hth].blTriggerTransmitEnable)                     /* PRQA S 3415, 3416 # JV-01, JV-01 */
  #endif
                                         ))
  {
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_WRITE_SID, CAN_E_PARAM_POINTER);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  /* Check payload length */
  else if ((Can_GpHohConfig[Hth].usTMDLC < PduInfo->length)                                                             /* PRQA S 0404, 3416 # JV-01, JV-01 */
  #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
           || (CAN_CANFD_MAX_PAYLOAD < PduInfo->length)
  #endif
  #if (CAN_RSCANFD_CONFIGURED == STD_ON) || (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
           || ((CAN_STD_MAX_PAYLOAD < PduInfo->length) && ((0UL == (uint32)(PduInfo->id & CAN_FD_FRAME_FORMAT)) ||
                (CAN_FALSE == Can_GpPBController[Can_GpHohConfig[Hth].ucController]                                     /* PRQA S 3415, 3416 # JV-01, JV-01 */
                .pBaudrateConfig[Can_GaaCtrlState[Can_GpHohConfig[Hth].ucController].ulBaudrateIndex].blFdConfigured))) /* PRQA S 3415, 3416 # JV-01, JV-01 */
  #endif
  )
  {
    (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_WRITE_SID,
  #if (CAN_AR_VERSION == CAN_AR_422_VERSION)
                          CAN_E_PARAM_DLC);
  #elif ((CAN_AR_VERSION == CAN_AR_431_VERSION) || (CAN_AR_VERSION == CAN_AR_R22_11_VERSION))
                          CAN_E_PARAM_DATA_LENGTH);
  #endif
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  else
  #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
  {
    #if ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON)|| \
         (CANFD_ON_XL_BUS_SUPPORT == STD_ON))
    /**************************************************************************************************************/
    /**                                               Prepare data                                               **/
    /**************************************************************************************************************/
    LpHoh = &Can_GpHohConfig[Hth];
    /* Getting the value of ucController Id*/
    LucController = LpHoh->ucController;
    /* Initial local Hoh access flag */
    LblHohAccessFlag = CAN_FALSE;
    /* Getting the value of enBufferType */
    #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
    LenBufferType = LpHoh->enBufferType;
    #endif
    /* Critical section is required in case of the reentant call on same HTH */
    CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
    /* Check whether global flag for other hardware is already set or not */
    if (CAN_TRUE != Can_GaaHwAccessFlag[LpHoh->usHohId])
    {
      /* Set the global flag which indicates HOH is being accessed to true */
      Can_GaaHwAccessFlag[LpHoh->usHohId] = CAN_TRUE;
      LblHohAccessFlag = CAN_TRUE;
    } /* else No action required */
    CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
    if (CAN_TRUE == LblHohAccessFlag)
    {
    /**************************************************************************************************************/
    /**                        Check whether device is busy and get address of registers                         **/
    /**************************************************************************************************************/
      #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
      if((CANXL_QUEUETYPE_TXPRIORITY == LenBufferType)
      || (CANXL_QUEUETYPE_TXFIFO == LenBufferType))
      {
        LenReturnValue = CanXL_CheckBusyQueue(&LpTargetDesc, LpHoh);
      }
      else
      #endif
      {
      #if ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON))

        LenReturnValue = Can_GetTxRegPointers(&LstTxRegSet, LpHoh);
      #endif
      }

    /**************************************************************************************************************/
    /**                                           Trigger Transmission                                           **/
    /**************************************************************************************************************/
      LucSduLength = PduInfo->length;
      LpSduPtr = PduInfo->sdu;
      #if (CAN_TRIGGER_TRANSMIT_FUNCTION == STD_ON)
      /* If SDU in the parameter is NULL, get SDU from CanIf */
      if ((CAN_COMMON_OK == LenReturnValue) && (NULL_PTR == PduInfo->sdu) && 
                                                                          (CAN_TRUE == LpHoh->blTriggerTransmitEnable))
      {
        LstTTPduInfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA))LaaTTSduData;                                 /* PRQA S 0751, 3432 # JV-01, JV-01 */
        LstTTPduInfo.SduLength = (PduLengthType)(CAN_LOCALBUFFER_SIZE_32 * sizeof(uint32));
        LenCanIfResult = CanIf_TriggerTransmit(PduInfo->swPduHandle, &LstTTPduInfo);
        if (E_OK == LenCanIfResult)
        {
          /* Use LstTTPduInfo instead of the original parameter */
          LucSduLength = (uint8)LstTTPduInfo.SduLength;
          LpSduPtr = LstTTPduInfo.SduDataPtr;
        }
        else
        {
          #if ((CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_AR_VERSION == CAN_AR_422_VERSION))
          (void)Det_ReportError(CAN_MODULE_ID, CAN_INSTANCE_ID, CAN_WRITE_SID, CAN_E_PARAM_POINTER);
          #endif
          LenReturnValue = CAN_COMMON_NOT_OK;
        }
      } /* else No action required */
      #endif /* (CAN_TRIGGER_TRANSMIT_FUNCTION == STD_ON) */

    /**************************************************************************************************************/
    /**                                                Send data                                                 **/
    /**************************************************************************************************************/
      if (CAN_COMMON_OK == LenReturnValue)
      { 
        #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
        if ((CANXL_QUEUETYPE_TXPRIORITY != LenBufferType) && (CANXL_QUEUETYPE_TXFIFO != LenBufferType))          
        {
        #endif
          #if ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON)) && \
              (CAN_RSCANFD_CONFIGURED == STD_ON)
          /* If EXTENDED ID format, set IDE bit */
          if (0UL != (uint32)(PduInfo->id & CAN_EXTENDED_FORMAT))
          {
            *LstTxRegSet.pID = (uint32)((PduInfo->id & CAN_ID_TYPE_IDMASK) | CAN_RSCAN_THLEN | CAN_RSCAN_IDE);
          }
          else
          {
            *LstTxRegSet.pID = (uint32)((PduInfo->id & CAN_ID_TYPE_IDMASK) | CAN_RSCAN_THLEN);
          }

          /* When classical CAN, DLC is as is */
          LulDLC = LucSduLength;
          LulActualLength = LulDLC;
          #if (CAN_RSCAN_CONFIGURED == STD_ON)
          if (CAN_MACRO_RSCAN == Can_GaaRegs[Can_GpPCController[LpHoh->ucController].ucUnit].enMacroType)
          {
            /* No pCTR for RSCAN */
          }
          else
          #endif
          {
            if (0UL != (uint32)(PduInfo->id & CAN_FD_FRAME_FORMAT))
            {
              if (CAN_TRUE == Can_GpPBController[LucController]                                                         /* PRQA S 0404, 3416 # JV-01, JV-01 */
                                  .pBaudrateConfig[Can_GaaCtrlState[LucController].ulBaudrateIndex].blBRS)
              {
                *LstTxRegSet.pCTR = CAN_RSCAN_XXFDF | CAN_RSCAN_XXBRS;
              }
              else
              {
                *LstTxRegSet.pCTR = CAN_RSCAN_XXFDF;
              }
              /* Convert payload length (0-64byte) to DLC value (0x0-0xF) */
              LulDLC = Can_GaaDLCFromPayloadTable[LucSduLength];
              LulActualLength = Can_GaaPayloadFromDLCTable[LulDLC];
            }
            else
            {
              *LstTxRegSet.pCTR = 0UL;
            }
            #if (CAN_LABEL_DATA_LOCATION == CAN_CTR_REG)
            /* Set CTR reg value with PduHandle as label data */
            *LstTxRegSet.pCTR |= CAN_RSCAN_XXPTR(PduInfo->swPduHandle);
            #endif
          }
          /* Set PTR reg value, including DLC  */
          *LstTxRegSet.pPTR =
              #if (CAN_LABEL_DATA_LOCATION == CAN_PTR_REG)
              CAN_RSCAN_XXPTR(PduInfo->swPduHandle) |
              #endif
              CAN_RSCAN_XXDLC(LulDLC);
          /* Copy payload data to data register */
          Can_WriteDataReg(LpSduPtr, LstTxRegSet.pDF, (uint32)LucSduLength, LulActualLength,
                          #if (CAN_RSCANFD_CONFIGURED == STD_ON)
                          LpHoh->ucPaddingValue
                          #else
                          0x00U
                          #endif
                          );
          /* Start transmission */
          *LstTxRegSet.pTrig = LstTxRegSet.ucTrigValue;
          #endif 
        #if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
        }
        else
        {
          Can_PrepareCanFdTxDesc(Hth, PduInfo, LpSduPtr, LucSduLength, LpTargetDesc);
          LucController = Can_GpPCController[LpHoh->ucController].ucCh;
          LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucController];
          if (CANXL_QUEUETYPE_TXPRIORITY == LenBufferType)
          {
            /* Check if Queue Slot was matched */
            if(1UL != (((uint32)CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQSTS0 >> (LpHoh->usBufferIndex)) & 1UL))
            {
              /* Start trigger transmit */
              CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQCTRL2 |= 1UL << (LpHoh->usBufferIndex);
              CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQCTRL0 |= 1UL << (LpHoh->usBufferIndex);
            }
            else
            {
              /* Do nothing */
            }
          }
          else
          {
            /* Start trigger transmit */
            CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQCTRL2 |= 1UL << (LpHoh->usBufferIndex);
            CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQCTRL0 |= 1UL << (LpHoh->usBufferIndex);
          }
        }
        #endif
      }  /* else no action required*/
      /* Release this HTH */
      /* Clear the global flag which indicates HOH is being accessed to false */
      Can_GaaHwAccessFlag[LpHoh->usHohId] = CAN_FALSE;
    }
    else /* if (CAN_TRUE == LblHohAccessFlag) */
    {
      LenReturnValue = (Can_CommonReturnType)CAN_BUSY;
    }
    #else
    /* Return CAN_BUSY when no TX hardware buffer available */
    LenReturnValue = (Can_CommonReturnType)CAN_BUSY;
  #endif /* ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || \
    (CAN_TX_QUEUE == STD_ON)) */
  }    /* if (DET check) */

  return (LenReturnValue);
}
#define CAN_STOP_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || (CAN_TX_QUEUE == STD_ON))
/***********************************************************************************************************************
** Function Name         : Can_GetTxRegPointers
**
** Service ID            : Not Applicable
**
** Description           : This function checks whether a target buffer is BUSY
**                         and retrieves the address of tx relevant registers
**                         according to the memory mode and the buffer index.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LpHoh    : Pointer to an HTH configuration
**                                    information
**
** InOut Parameters      : None
**
** Output Parameters     : LpRegSet : Pointer to a structure to store addresses
**
** Return parameter      : Can_CommonReturnType
**
** Preconditions         : The availability of parameters must be guaranteed
**                         by the upper layer.
**
** Global Variables Used : Can_GpPCController, Can_GaaRegs
**
** Functions Invoked     : None
**
** Registers Used        : (CFD)CFSTSk, (CFD)CFPCTR, CFDCFFDCSTSk,
**                         (CFD)CFID, (CFD)CFPTR, (CFD)CFDF,
**                         (CFD)TXQPCTRx, (CFD)TXQSTSx,(CFD)FDTMFDCTRp,
**                         (CFD)TMIDp, (CFD)TMPTRp, (CFD)TMDFb_p,
**                         (CFD)TMSTSp, (CFD)TMCp
**
** Reference ID          : CAN_DUD_ACT_053
** Reference ID          : CAN_DUD_ACT_053_REG001, CAN_DUD_ACT_053_REG002,
** Reference ID          : CAN_DUD_ACT_053_REG003, CAN_DUD_ACT_053_REG004,
** Reference ID          : CAN_DUD_ACT_053_REG005, CAN_DUD_ACT_053_REG006,
** Reference ID          : CAN_DUD_ACT_053_REG007, CAN_DUD_ACT_053_REG008,
** Reference ID          : CAN_DUD_ACT_053_REG009, CAN_DUD_ACT_053_REG010,
** Reference ID          : CAN_DUD_ACT_053_REG011, CAN_DUD_ACT_053_REG012,
** Reference ID          : CAN_DUD_ACT_053_REG013, CAN_DUD_ACT_053_REG014,
** Reference ID          : CAN_DUD_ACT_053_REG015, CAN_DUD_ACT_053_REG016,
** Reference ID          : CAN_DUD_ACT_053_REG017, CAN_DUD_ACT_053_REG018,
** Reference ID          : CAN_DUD_ACT_053_REG019, CAN_DUD_ACT_053_REG020,
** Reference ID          : CAN_DUD_ACT_053_REG021, CAN_DUD_ACT_053_REG022,
** Reference ID          : CAN_DUD_ACT_053_REG023, CAN_DUD_ACT_053_REG024,
** Reference ID          : CAN_DUD_ACT_053_REG025, CAN_DUD_ACT_053_REG026,
** Reference ID          : CAN_DUD_ACT_053_REG027
***********************************************************************************************************************/
STATIC FUNC(Can_CommonReturnType, CAN_PRIVATE_CODE)
                              Can_GetTxRegPointers(CONSTP2VAR(Can_TxRegSetType, AUTOMATIC, CAN_APPL_DATA) LpRegSet,     /* PRQA S 3432 # JV-01 */
                                                  CONSTP2CONST(Can_HohConfigType, AUTOMATIC, CAN_PRIVATE_CONST) LpHoh)
{
  VAR(Can_CommonReturnType, AUTOMATIC) LenRetValue;
  VAR(uint8, AUTOMATIC) LucUnit;
  VAR(uint16, AUTOMATIC) LusBufIdx;
  #if (CAN_TX_QUEUE == STD_ON)
  VAR(uint32, AUTOMATIC) LulQueueWindow;
  VAR(uint32, AUTOMATIC) LulTxQCh;
  VAR(uint32, AUTOMATIC) LulTxQIdx;
  #endif

  LenRetValue = CAN_COMMON_OK;
  LusBufIdx = LpHoh->usBufferIndex;
  LucUnit = Can_GpPCController[LpHoh->ucController].ucUnit;
  #if (CAN_TX_COMFIFO == STD_ON)
  if (CAN_BUFFERTYPE_TXRXFIFO == LpHoh->enBufferType)
  {
    /* If FIFO is full, return CAN_BUSY */
    if (0UL != (Can_GaaRegs[LucUnit].pCmn->aaCFSTS[LusBufIdx] & CAN_RSCAN_CFFLL))
    {
      LenRetValue = (Can_CommonReturnType)CAN_BUSY;
    }
    else
    {
      /* Get address of transmit trigger register.
      To unify trigger operation with other buffer types,
      cast pointer to uint8*. CFPCTR allows 8, 16, 32bit access. */
      LpRegSet->pTrig = (P2VAR(volatile uint8, AUTOMATIC, REGSPACE))                                                    /* PRQA S 0751 # JV-01 */
                        & Can_GaaRegs[LucUnit].pCmn->aaCFPCTR[LusBufIdx];
      LpRegSet->ucTrigValue = (uint8)CAN_RSCAN_CFPC_NEXT;

      #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
      if (CAN_MACRO_RSCANFD == Can_GaaRegs[LucUnit].enMacroType)
      #endif
      {
        #if (CAN_RSCANFD_CONFIGURED == STD_ON)
        LpRegSet->pCTR = &Can_GaaRegs[LucUnit].pFD->aaCFReg[LusBufIdx].ulFDCSTS;
        LpRegSet->pID = &Can_GaaRegs[LucUnit].pFD->aaCFReg[LusBufIdx].ulFDCFID;
        LpRegSet->pPTR = &Can_GaaRegs[LucUnit].pFD->aaCFReg[LusBufIdx].ulFDCFPTR;
        LpRegSet->pDF = &Can_GaaRegs[LucUnit].pFD->aaCFReg[LusBufIdx].aaFDCFDF[0];
        #endif
      }
      #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
      else
      #endif
      {
        #if (CAN_RSCAN_CONFIGURED == STD_ON)
        LpRegSet->pID = &Can_GaaRegs[LucUnit].pCmn->aaCFReg[LusBufIdx].ulCFID;
        LpRegSet->pPTR = &Can_GaaRegs[LucUnit].pCmn->aaCFReg[LusBufIdx].ulCFPTR;
        LpRegSet->pDF = &Can_GaaRegs[LucUnit].pCmn->aaCFReg[LusBufIdx].aaCFDF[0];
        #endif
      }
    }
  }
  else
  #endif /* (CAN_TX_COMFIFO == STD_ON) */
  #if (CAN_TX_QUEUE == STD_ON)
  if (CAN_BUFFERTYPE_TXQUEUE == LpHoh->enBufferType)
  {
    LulTxQCh = LusBufIdx / CAN_RSCAN_TXQUEUE_PER_CH;
    LulTxQIdx = LusBufIdx % CAN_RSCAN_TXQUEUE_PER_CH;
    /* If Queue is full, return CAN_BUSY */
    if (0UL != (Can_GaaRegs[LucUnit].pCmn->aaTQueueReg[LulTxQIdx].aaTXQSTS[LulTxQCh] & CAN_RSCAN_TXQFLL))
    {
      LenRetValue = (Can_CommonReturnType)CAN_BUSY;
    }
    else
    {
      /* Get index of tx buffer to access tx queue */
      #if (CAN_RSCAN_TXQUEUE_PER_CH > 1UL)
      switch (LulTxQIdx)
      {
      case CAN_ONE:
        LulQueueWindow = CAN_RSCAN_TXQUEUE1_WINDOW(LulTxQCh);                                                           /* PRQA S 3383 # JV-01 */
        break;
      case CAN_TWO:
        LulQueueWindow = CAN_RSCAN_TXQUEUE2_WINDOW(LulTxQCh);                                                           /* PRQA S 3383 # JV-01 */
        break;
      case CAN_THREE:
        LulQueueWindow = CAN_RSCAN_TXQUEUE3_WINDOW(LulTxQCh);                                                           /* PRQA S 3383 # JV-01 */
        break;
      default:
      #endif
        LulQueueWindow = CAN_RSCAN_TXQUEUE0_WINDOW(LulTxQCh);                                                           /* PRQA S 3383, 2985 # JV-01, JV-01 */
      #if (CAN_RSCAN_TXQUEUE_PER_CH > 1UL)
        break;
      }
      #endif
      /* Get address of transmit trigger register.
      To unify trigger operation with other buffer types,
      cast pointer to uint8*. CFPCTR allows 8, 16, 32bit access. */
      LpRegSet->pTrig = (P2VAR(volatile uint8, AUTOMATIC, REGSPACE))                                                    /* PRQA S 0751 # JV-01 */
                        & Can_GaaRegs[LucUnit].pCmn->aaTQueueReg[LulTxQIdx].aaTXQPCTR[LulTxQCh];
      LpRegSet->ucTrigValue = (uint8)CAN_RSCAN_TXQPC_NEXT;
      /* Clearing the transmission status register */
      Can_GaaRegs[LucUnit].pCmn->aaTMSTS[LulQueueWindow] = 0U;
      #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
      if (CAN_MACRO_RSCANFD == Can_GaaRegs[LucUnit].enMacroType)
      #endif
      {
        #if (CAN_RSCANFD_CONFIGURED == STD_ON)
        LpRegSet->pCTR = &Can_GaaRegs[LucUnit].pFD->aaHthReg[LulQueueWindow].ulFDTMFDCTR;
        LpRegSet->pID = &Can_GaaRegs[LucUnit].pFD->aaHthReg[LulQueueWindow].ulFDTMID;
        LpRegSet->pPTR = &Can_GaaRegs[LucUnit].pFD->aaHthReg[LulQueueWindow].ulFDTMPTR;
        LpRegSet->pDF = &Can_GaaRegs[LucUnit].pFD->aaHthReg[LulQueueWindow].aaFDTMDF[0];
        #endif
      }
      #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
      else
      #endif
      {
        #if (CAN_RSCAN_CONFIGURED == STD_ON)
        LpRegSet->pID = &Can_GaaRegs[LucUnit].pCmn->aaHthReg[LulQueueWindow].ulTMID;
        LpRegSet->pPTR = &Can_GaaRegs[LucUnit].pCmn->aaHthReg[LulQueueWindow].ulTMPTR;
        LpRegSet->pDF = &Can_GaaRegs[LucUnit].pCmn->aaHthReg[LulQueueWindow].aaTMDF[0];
        #endif
      }
    }
  }
  else
  #endif /* (CAN_TX_QUEUE == STD_ON) */
  {
    #if (CAN_TX_BUFFER == STD_ON)
    /* If TxBuffer is on-going, return CAN_BUSY */
    if (0U != (Can_GaaRegs[LucUnit].pCmn->aaTMSTS[LusBufIdx] & CAN_RSCAN_TMTRM))
    {
      LenRetValue = (Can_CommonReturnType)CAN_BUSY;
    }
    else
    {
      /* Get address of transmit trigger register */
      LpRegSet->pTrig = &Can_GaaRegs[LucUnit].pCmn->aaTMC[LusBufIdx];
      LpRegSet->ucTrigValue = (uint8)CAN_RSCAN_TMTR;
      /* Clearing the transmission status register */
      Can_GaaRegs[LucUnit].pCmn->aaTMSTS[LusBufIdx] = 0U;

      #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
      if (CAN_MACRO_RSCANFD == Can_GaaRegs[LucUnit].enMacroType)
      #endif
      {
        #if (CAN_RSCANFD_CONFIGURED == STD_ON)
        LpRegSet->pCTR = &Can_GaaRegs[LucUnit].pFD->aaHthReg[LusBufIdx].ulFDTMFDCTR;
        LpRegSet->pID = &Can_GaaRegs[LucUnit].pFD->aaHthReg[LusBufIdx].ulFDTMID;
        LpRegSet->pPTR = &Can_GaaRegs[LucUnit].pFD->aaHthReg[LusBufIdx].ulFDTMPTR;
        LpRegSet->pDF = &Can_GaaRegs[LucUnit].pFD->aaHthReg[LusBufIdx].aaFDTMDF[0];
        #endif /* (CAN_FD_SUPPORT == STD_ON) */
      }
      #if ((CAN_RSCAN_CONFIGURED == STD_ON) && (CAN_RSCANFD_CONFIGURED == STD_ON))
      else
      #endif
      {
        #if (CAN_RSCAN_CONFIGURED == STD_ON)
        LpRegSet->pID = &Can_GaaRegs[LucUnit].pCmn->aaHthReg[LusBufIdx].ulTMID;
        LpRegSet->pPTR = &Can_GaaRegs[LucUnit].pCmn->aaHthReg[LusBufIdx].ulTMPTR;
        LpRegSet->pDF = &Can_GaaRegs[LucUnit].pCmn->aaHthReg[LusBufIdx].aaTMDF[0];
        #endif
      }
    }
  #endif /* #if (CAN_TX_BUFFER == STD_ON) */
  }

  return (LenRetValue);
}

/***********************************************************************************************************************
** Function Name         : Can_WriteDataReg
**
** Service ID            : Not Applicable
**
** Description           : This function writes SDU to the tx data register.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LpSrc         : Pointer to SDU
**                         LpDF          : Pointer to the data register
**                         LulSrcLength  : Length of SDU
**                         LulDestLength : Length of data to be written to DF
**                         LucPadding    : Padding value to fill the surplus
**                                         area between SrcLength and DestLength
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The availability of parameters must be guaranteed
**                         by the upper layer.
**
** Global Variables Used : None
**
** Functions Invoked     : None
**
** Registers Used        : (CFD)CFDF, (CFD)TMDF
**
** Reference ID          : CAN_DUD_ACT_054
** Reference ID          : CAN_DUD_ACT_054_REG001, CAN_DUD_ACT_054_REG002,
** Reference ID          : CAN_DUD_ACT_054_REG003, CAN_DUD_ACT_054_REG004
** Reference ID          : CAN_DUD_ACT_054_REG005
***********************************************************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_WriteDataReg(CONSTP2CONST(uint8, AUTOMATIC, CAN_PRIVATE_CONST) LpSrc,
                     CONSTP2VAR(volatile uint32, AUTOMATIC, REGSPACE) LpDF, CONST(uint32, AUTOMATIC) LulSrcLength,
                     CONST(uint32, AUTOMATIC) LulDestLength, CONST(uint8, AUTOMATIC) LucPadding)
{
  VAR(uint32, AUTOMATIC) LulWordIndex;
  VAR(uint32, AUTOMATIC) LulDataRegValue;
  VAR(uint32, AUTOMATIC) LulByteIndex;
  CONST(uint32, AUTOMATIC) LulAvailableWords = LulSrcLength / (uint32)sizeof(uint32);
  CONST(uint32, AUTOMATIC) LulRemainedBytes = LulSrcLength % (uint32)sizeof(uint32);
  CONST(uint32, AUTOMATIC) LulTotalWords = LulDestLength / (uint32)sizeof(uint32);

  /* Copy user data to the data buffer by 4 bytes */
  LulByteIndex = 0U;
  for (LulWordIndex = 0U; LulWordIndex < LulAvailableWords; LulWordIndex++)
  {
    LulDataRegValue = CAN_RSCAN_CREATEWORD(LpSrc[LulByteIndex], LpSrc[LulByteIndex + CAN_RSCAN_1_BYTE],                 /* PRQA S 3469, 3383 # JV-01, JV-01 */
                                        LpSrc[LulByteIndex + CAN_RSCAN_2_BYTE], LpSrc[LulByteIndex + CAN_RSCAN_3_BYTE]);
    LulByteIndex = LulByteIndex + (uint32)sizeof(uint32);                                                               /* PRQA S 3383 # JV-01 */
    LpDF[LulWordIndex] = LulDataRegValue;
  }

  /* Copy ramained bytes to data buffer */
  switch (LulRemainedBytes)
  {
  case CAN_RSCAN_0_BYTE: /* LulSrcLength = 4n + 0 */
    /* No remaiend byte */
    break;
  case CAN_RSCAN_1_BYTE: /* LulSrcLength = 4n + 1 */
    LulDataRegValue = CAN_RSCAN_CREATEWORD(LpSrc[LulByteIndex], LucPadding, LucPadding, LucPadding);                    /* PRQA S 3469 # JV-01 */
    LpDF[LulWordIndex] = LulDataRegValue;
    LulWordIndex++;                                                                                                     /* PRQA S 3383 # JV-01 */
    break;
  case CAN_RSCAN_2_BYTE: /* LulSrcLength = 4n + 2 */
    LulDataRegValue =
        CAN_RSCAN_CREATEWORD(LpSrc[LulByteIndex], LpSrc[LulByteIndex + CAN_RSCAN_1_BYTE], LucPadding, LucPadding);      /* PRQA S 3469, 3383 # JV-01, JV-01 */
    LpDF[LulWordIndex] = LulDataRegValue;
    LulWordIndex++;                                                                                                     /* PRQA S 3383 # JV-01 */
    break;
  default: /* LulSrcLength = 4n + 3 */
    LulDataRegValue = CAN_RSCAN_CREATEWORD(LpSrc[LulByteIndex], LpSrc[LulByteIndex + CAN_RSCAN_1_BYTE],                 /* PRQA S 3383, 3469 # JV-01, JV-01 */
                                           LpSrc[LulByteIndex + CAN_RSCAN_2_BYTE], LucPadding);
    LpDF[LulWordIndex] = LulDataRegValue;
    LulWordIndex++;                                                                                                     /* PRQA S 3383 # JV-01 */
    break;
  }

  /* Fill padding to the surplus area */
  LulDataRegValue = CAN_RSCAN_CREATEWORD(LucPadding, LucPadding, LucPadding, LucPadding);                               /* PRQA S 3469 # JV-01 */
  for (; LulWordIndex < LulTotalWords; LulWordIndex++)
  {
    LpDF[LulWordIndex] = LulDataRegValue;
  }
}
#endif /* ((CAN_TX_BUFFER == STD_ON) || (CAN_TX_COMFIFO == STD_ON) || \
  (CAN_TX_QUEUE == STD_ON)) */
/***********************************************************************************************************************
** Function Name         : Can_PrepareCanFdTxDesc
**
** Service ID            : Not Applicable
**
** Description           : This function prepate data for a descriptor which is used for sending CAN-FD frame.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Hth : Hth index need to perform transmission
**                         PduInfo: Pointer to input data
**                         Descriptor: Pointer to written descriptor
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Can_GpPCController, Can_GaaDLCFromPayloadTable, CanXL_GaaRegs, Can_GpConfig,
**                         CanXL_GaaCtrlStat
**
** Functions Invoked     : CanXL_ComputeCRC
**
** Reference ID          : CAN_DUD_ACT_183
** Reference ID          : CAN_DUD_ACT_183_GBL001, CAN_DUD_ACT_183_GBL002
** Reference ID          : CAN_DUD_ACT_183_GBL003, CAN_DUD_ACT_183_GBL004
** Reference ID          : CAN_DUD_ACT_183_GBL005, CAN_DUD_ACT_183_GBL006
** Reference ID          : CAN_DUD_ACT_183_GBL007, CAN_DUD_ACT_183_GBL008,
** Reference ID          : CAN_DUD_ACT_183_REG001
***********************************************************************************************************************/
#if (CANFD_ON_XL_BUS_SUPPORT == STD_ON)
STATIC FUNC(void, CAN_PRIVATE_CODE) Can_PrepareCanFdTxDesc(Can_HwHandleType Hth, const Can_PduType* PduInfo,
                        P2CONST(uint8, AUTOMATIC, CAN_APPL_DATA) LpSduPtr, uint16 LusSduLength,
                        P2VAR(Can_TxDescriptorsType, AUTOMATIC, RECAN_APPL_DATAGSPACE) Descriptor)                      /* PRQA S 3432 # JV-01 */
{
  VAR(uint8, AUTOMATIC) LucDLC;
  VAR(uint8, AUTOMATIC) LucQueue;
  VAR(uint8, AUTOMATIC) LucControllerID;
  VAR(uint8, AUTOMATIC) LucController;
  VAR(uint8, AUTOMATIC) LucPaddingValue;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint8, AUTOMATIC) LucDescIndex;
  VAR(uint16, AUTOMATIC) LucByteCount;
  VAR(uint16, AUTOMATIC) LusCRC;
  VAR(uint16, AUTOMATIC) LusPayloadSize;
  VAR(uint16, AUTOMATIC) LusActualLength;
  VAR(uint16, AUTOMATIC) LusPayload;

  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpStartDec;                                                  /* PRQA S 3432, 3678 # JV-01, JV-01 */
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;
  P2VAR(uint8, AUTOMATIC, CAN_CONFIG_DATA) LpDataContainer;                                                             /* PRQA S 3432 # JV-01 */
  P2VAR(PduIdType, AUTOMATIC, CAN_CONFIG_DATA) LpSwPduHandle;                                                           /* PRQA S 3432 # JV-01 */

  /* DMA Info Ctrl 1 */
  LucQueue = (uint8)(Can_GpHohConfig[Hth].usBufferIndex);
  LucControllerID = Can_GpHohConfig[Hth].ucController;
  LucController = Can_GpPCController[LucControllerID].ucCh;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucController];
  LucPaddingValue = Can_GpHohConfig[Hth].ucPaddingValue;
  LucDLC = Can_GaaDLCFromPayloadTable[LusSduLength];

  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */
  
  /* Setting payload length to align 32-bit */
  LusActualLength = LusSduLength;
  while(0U != (LusActualLength % 4U))
  {
    LusActualLength ++;                                                                                                 /* PRQA S 3383 # JV-01 */
  }
  LusPayloadSize = ((LusActualLength - 1U) / 4U) + 1U;                                                                  /* PRQA S 3383 # JV-01 */
  /* Re-initialize descriptor */
  Descriptor->ulElement0 &= CAN_DMA1_RESET_VALUE;
  Descriptor->ulElement1 &= CAN_DMA2_RESET_VALUE;
  /* Update for element 0 */
  Descriptor->ulElement0 |= (uint32)CANXL_BIT_VALID(1U);                                                                /* PRQA S 3469 # JV-01 */
  /* Update for element 1 */
  Descriptor->ulElement1 |= (uint32)CANXL_BIT_SIZE(LusPayloadSize) | CANXL_BIT_PLSRC(0U);                               /* PRQA S 3469, 2985 # JV-01, JV-01 */
  /* Check for Tx Priority Queue HTH */
  if (CANXL_QUEUETYPE_TXPRIORITY == Can_GpHohConfig[Hth].enBufferType)                                                  /* PRQA S 3416 # JV-01 */
  {
    LucDescIndex = LpCanXLHWInfo[LucCtrlInfoIndex].pTxPriorityQueueConfig->aaDescIndex[LucQueue];
    LusPayload = LpCanXLHWInfo[LucCtrlInfoIndex].pTxPriorityQueueConfig->usPayloadSize;

    LpDataContainer = 
                    &LpCanXLHWInfo[LucCtrlInfoIndex].pTxPriorityQueueConfig->pDataContainer[LucDescIndex * LusPayload];
    /* Get swPduHandle pointer */
    LpSwPduHandle = &LpCanXLHWInfo[LucCtrlInfoIndex].pTxPriorityQueueConfig->pSwPduHandle[LucDescIndex];
    /* Save swPduHandle to global data */
    *(LpSwPduHandle)= PduInfo->swPduHandle;

  }
  /* Check for Tx FIFO Queue HTH */
  else
  {
    LusPayload = LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LucQueue].usPayloadSize;
    LpStartDec = (Can_TxDescriptorsType *)(CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LucQueue].ulTXSTADD);         /* PRQA S 0306 # JV-01 */
    /* Get data container pointer */
    LpDataContainer = &LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LucQueue].
                          pDataContainer[(uint16)(Descriptor - LpStartDec) * LusPayload];                               /* PRQA S 0488 # JV-01 */
    /* Get swPduHandle pointer */
    LpSwPduHandle = &LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LucQueue].pSwPduHandle[0];
    /* Save swPduHandle to global data */
    *(LpSwPduHandle + (Descriptor - LpStartDec))= PduInfo->swPduHandle;                                                 /* PRQA S 0488 # JV-01 */
  }
  /* Update for element 2 */
  Descriptor->ulElement2TS0 = 0UL;
  /* Update for element 3 */
  Descriptor->ulElement3TS1 = 0UL;
  /* Update for element 4 */

  if (0UL != (uint32)(PduInfo->id & CAN_EXTENDED_FORMAT))
  {
    Descriptor->ulElement4T0 = (uint32)(CANFD_T0_FIXED | CANFD_BIT_XTD(1U) | CANFD_BIT_BASEID(0U) |                     /* PRQA S 3469 # JV-01 */
                                      CANFD_BIT_EXTID(PduInfo->id & CAN_ID_TYPE_IDMASK));                               /* PRQA S 3469 # JV-01 */
  }
  else
  {
    Descriptor->ulElement4T0 = (uint32)(CANFD_T0_FIXED | CANFD_BIT_XTD(0U)  |                                           /* PRQA S 3469, 2986 # JV-01, JV-01 */
                                  CANFD_BIT_BASEID(PduInfo->id & CAN_ID_STANDARDTYPE_IDMASK) | CANFD_BIT_EXTID(0U));    /* PRQA S 3469, 2985 # JV-01, JV-01 */
  }
                                  
  Descriptor->ulElement5T1 = (uint32)(CANFD_T1_FIXED | CANFD_BIT_DLC(LucDLC));                                          /* PRQA S 2986 # JV-01 */
  
  CANXL_PACK_TX_DATA((CONST(uint8, AUTOMATIC) *)LpSduPtr, Descriptor->ulElement6T2TD0);                                 /* PRQA S 3473, 3432 # JV-01, JV-01 */
  
  if (0UL != (uint32)(PduInfo->id & CAN_FD_FRAME_FORMAT))
  {
    if (CAN_TRUE == Can_GpPBController[LucControllerID]                                                                 /* PRQA S 0404, 3416 # JV-01, JV-01 */
                                .pBaudrateConfig[Can_GaaCtrlState[LucControllerID].ulBaudrateIndex].blBRS)
    {
      Descriptor->ulElement5T1 |= CANFD_BIT_BRS(1U);                                                                    /* PRQA S 3469 # JV-01 */
    } /* else do nothing */ 
    Descriptor->ulElement4T0 |= CANFD_BIT_FDF(1U);                                                                      /* PRQA S 3469 # JV-01 */
    if(LucDLC > 4U)
    {
      /* Update for element 1 */
      Descriptor->ulElement1 |= CANXL_BIT_PLSRC(1U);                                                                    /* PRQA S 3469 # JV-01 */
      /* Update for element 7 */
      Descriptor->ulElement7TX_APTD1 = (uint32)LpDataContainer;                                                         /* PRQA S 0306 # JV-01 */
      /* Add input payload to data container */
      for(LucByteCount = 0U; LucByteCount < LusSduLength; LucByteCount++)
      {
        *(LpDataContainer + LucByteCount) = *(LpSduPtr + LucByteCount);                                                 /* PRQA S 0488 # JV-01 */
      }
      /* Add padding value to payload if neccessary */
      if(0U != (LusActualLength - LusSduLength))
      {
        for(LucByteCount = LusSduLength; LucByteCount < LusActualLength; LucByteCount++)
        {
          *(LpDataContainer + LucByteCount) = LucPaddingValue;                                                          /* PRQA S 0488 # JV-01 */
        }
      } /* else do nothing */ 
    }
    else
    {
      Descriptor->ulElement7TX_APTD1 = 0UL;
    }
  }
  else
  {
    if(LucDLC > 4U)
    {
      CANXL_PACK_TX_DATA((CONST(uint8, AUTOMATIC) *)(LpSduPtr + 4), Descriptor->ulElement7TX_APTD1);                    /* PRQA S 0488, 3473, 3432 # JV-01, JV-01, JV-01 */
    }
    else
    {
      Descriptor->ulElement7TX_APTD1 = 0UL;
    }
  }
  /* Calculate CRC for TX descriptor */
  LusCRC = CanXL_ComputeCRC((uint32 *)Descriptor, CANXL_TX_DESC);                                                       /* PRQA S 0310 # JV-01 */
  /* Update CRC value to TX descriptor */
  Descriptor->ulElement0 |= (uint32)(CANXL_BIT_CRC(LusCRC));                                                            /* PRQA S 3469 # JV-01 */
}
#endif /* CANFD_ON_XL_BUS_SUPPORT == STD_ON */
#define CAN_STOP_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
