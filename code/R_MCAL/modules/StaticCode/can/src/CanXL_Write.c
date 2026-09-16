/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = CanXL_Write.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
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
/*              Devices:                  X2x                                                                         */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                                  Revision History                                                  **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025  : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025  : Update SW-VERSION for RH850/Ver22.01.01 U2Cx Release
 * 2.3.1: 31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                    : Add message 0404, 0489, 3415 to support QA-C version 11.6.0
 * 2.3.0: 28/02/2025  : As part of ARDAACL-52560: Update CanXL_Write, CanXL_CheckBusyQueue, CanXL_PrepareTxDescWrite
 * 2.2.0: 31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                      As part of CANXL driver support, following changes are made:
 *                      1. Update CanXL_PrepareTxDescWrite, CanXL_Write
 * 2.1.2: 31/10/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Fixing QAC message. Remove messages: 3415, 0489. Add message 3384
 *                      2. Add precompile conditon for CanXL_Write, CanXL_PrepareTxDescWrite
 *                      3. Change ucTMDLC to usTMDLC
 *                      4. Update CanXL_PrepareTxDescWrite to fix findings
 * 2.1.1: 06/08/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update CanXL_Write, CanXL_PrepareTxDescWrite
 *        29/07/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Fix QAC messages
 *        25/06/2024  : As part of CANXL driver support, following changes are made:
 *                      1. Update API CanXL_PrepareTxDescWrite  to fix issue related to RX_FQ_INT_STS, 
 *                      TX_FQ_INT_STS register
 *        29/05/2024  : As part of CANXL driver support, following changes are made:
 *                      1. In API CanXL_Write, support multicore for CANXL to check CANXL_E_INVALID_CORE
 *                      2. Add QAC message 0404
 *                      3. Update CanXL_CheckBusyQueue to fix issue FIFO QUEUE
 * 2.0.3: 13/04/2024  : Update CanXL_CheckBusyQueue, CanXL_CheckBusyQueue, CanXL_PrepareTxDescWrite
 *        12/04/2024  : Update CanXL_Write function and add header message 1505
 * 2.0.2: 23/02/2024  : Add macro CAN_CANXL_SUPPORTED to cover CANXL RegStruct
 *        19/01/2024  : Update reference ID to support CANXL
 *        09/01/2024  : Add reference ID for CanXL_Write, CanXL_ComputeCRC, CanXL_CheckBusyQueue, 
 *                      CanXL_PrepareTxDescWrite
 *        02/01/2024  : Initial version.
 */
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* CanXL.h */
#include "CanXL.h"
/* Included for RAM variable declarations */
#include "Can_Ram.h"
#if (CAN_CANXL_SUPPORTED == STD_ON)
/* Register structure */
#include "CanXL_RegStruct.h"
#endif
/* Scheduler */
#include "SchM_Can.h"
/* including DEM header file */
#include "Dem.h"
#if (CAN_AR_VERSION == CAN_AR_R22_11_VERSION)
#include "CanIf_Can.h"
#else
#include "CanIf_Cbk.h"                                                                                                  
#endif
/* Included for the declaration of Det_ReportError() */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define CANXL_WRITE_C_AR_RELEASE_MAJOR_VERSION    CAN_AR_RELEASE_MAJOR_VERSION_VALUE
#define CANXL_WRITE_C_AR_RELEASE_MINOR_VERSION    CAN_AR_RELEASE_MINOR_VERSION_VALUE
#define CANXL_WRITE_C_AR_RELEASE_REVISION_VERSION CAN_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define CANXL_WRITE_C_SW_MAJOR_VERSION            CAN_SW_MAJOR_VERSION_VALUE
#define CANXL_WRITE_C_SW_MINOR_VERSION            CAN_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (CAN_AR_RELEASE_MAJOR_VERSION != CANXL_WRITE_C_AR_RELEASE_MAJOR_VERSION)
  #error "CanXL_Write.c : Mismatch in Release Major Version"
#endif
#if (CAN_AR_RELEASE_MINOR_VERSION != CANXL_WRITE_C_AR_RELEASE_MINOR_VERSION)
  #error "CanXL_Write.c : Mismatch in Release Minor Version"
#endif
#if (CAN_AR_RELEASE_REVISION_VERSION != CANXL_WRITE_C_AR_RELEASE_REVISION_VERSION)
  #error "CanXL_Write.c : Mismatch in Release Revision Version"
#endif

#if (CANXL_WRITE_C_SW_MAJOR_VERSION != CAN_SW_MAJOR_VERSION)
  #error "CanXL_Write.c : Mismatch in Software Major Version"
#endif
#if (CANXL_WRITE_C_SW_MINOR_VERSION != CAN_SW_MINOR_VERSION)
  #error "CanXL_Write.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4                                                        */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1                                                         */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39                                                                         */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2985)    : This operation is redundant. The value of the result is always that of the left-hand operand.*/
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : For readability, setting to registers will used redundant macros and is based on hardware    */
/*                       user's manual                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1338)    : The parameter '%s' is being modified.                                                        */
/* Rule                : MISRA C:2012 Rule-17.8                                                                       */
/* JV-01 Justification : This in case, parameter is not const, it could be accepted for modification                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : This is accepted. It just an advise for improve safety by reducing the possibility that the  */
/*                       referenced data is unintentionally modified through an unexpected alias and improves         */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4                                                        */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
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
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : CERTCCM EXP11, EXP39, MISRA C:2012 Rule-11.3                                                 */
/* JV-01 Justification : For accessing 8-bit and 16-bit PNOT and JPNOT register respectively, the 32-bit pointer is   */
/*                       typecasted.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2986)    : This operation is redundant. The value of the result is always that of the right-hand        */
/*                       operand.                                                                                     */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2                                                  */
/* JV-01 Justification : This operation is an important operation for calculating the decrement value as the          */
/*                       increment value, so it is necessary and not redundant.                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5                                                                       */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4391)    : A composite expression of 'essentially unsigned' type (%1s) is being cast to a wider         */
/*                       unsigned type, '%2s'.                                                                        */
/* Rule                : MISRA C:2012 Rule-10.8                                                                       */
/* JV-01 Justification : This casting is for the lower operator which requires wider type.                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45                                                                                */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7                                                         */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
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

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#if (CAN_CANXL_SUPPORTED == STD_ON)
#define CAN_START_SEC_PRIVATE_CODE
#include "Can_MemMap.h"
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_PrepareTxDescWrite(Can_HwHandleType Hth, const CanXL_PduType* PduInfo, 
                        P2CONST(uint8, AUTOMATIC, CAN_APPL_DATA) LpSduPtr, uint16 LusSduLength,
                        P2VAR(Can_TxDescriptorsType, AUTOMATIC, RECAN_APPL_DATAGSPACE) Descriptor);                     /* PRQA S 3432 # JV-01 */
#define CAN_STOP_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : CanXL_Write
**
** Service ID            : 0x10
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
**                         (CAN_COMMON_OK / CAN_COMMON_NOT_OK / CAN_BUSY)
**
** Preconditions         : The CAN Driver must be initialized.
**
** Global Variables Used : Can_GblInitialized, Can_GpConfig, Can_GpPCController, CanXL_GaaRegs
**
** Functions Invoked     : CanXL_CheckBusyQueue, CanXL_PrepareTxDescWrite
**
** Reference ID          : CAN_DUD_ACT_077
** Reference ID          : CAN_DUD_ACT_077_ERR001, CAN_DUD_ACT_077_ERR002
** Reference ID          : CAN_DUD_ACT_077_ERR003, CAN_DUD_ACT_077_ERR004
** Reference ID          : CAN_DUD_ACT_077_ERR005, CAN_DUD_ACT_077_ERR006
** Reference ID          : CAN_DUD_ACT_077_CRT001, CAN_DUD_ACT_077_CRT002
** Reference ID          : CAN_DUD_ACT_077_GBL001, CAN_DUD_ACT_077_GBL002
** Reference ID          : CAN_DUD_ACT_077_GBL003, CAN_DUD_ACT_077_GBL004
** Reference ID          : CAN_DUD_ACT_077_GBL005, CAN_DUD_ACT_077_REG001
** Reference ID          : CAN_DUD_ACT_077_REG002, CAN_DUD_ACT_077_REG003
** Reference ID          : CAN_DUD_ACT_077_REG004
***********************************************************************************************************************/
#define CAN_START_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Can_CommonReturnType, CAN_PUBLIC_CODE) CanXL_Write(VAR(Can_HwHandleType, AUTOMATIC) Hth,                           /* PRQA S 1503 # JV-01 */
                                      P2CONST(CanXL_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfo)
{
  /* SduType is expected 
  - 01h (content based CAN XL frames)
  - 03h (tunneled CAN 2.0/FD frames) 
  */
  VAR(Can_CommonReturnType, AUTOMATIC) LenReturnValue;
  boolean LblHohAccessFlag;
  #if (CAN_CANXL_TRIGGER_TRANSMIT_FUNCTION == STD_ON)
  VAR(PduInfoType, AUTOMATIC) LstTTPduInfo;
  VAR(uint32, AUTOMATIC) LaaTTSduData[CANXL_LOCALBUFFER_SIZE_32];
  VAR(Std_ReturnType, AUTOMATIC) LenCanIfResult;
  #endif
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpTargetDesc;                                                /* PRQA S 3432 # JV-01 */
  VAR(uint16, AUTOMATIC) LusSduLength;
  P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA) LpSduPtr;                                                                      /* PRQA S 3678, 3432 # JV-01, JV-01 */
  P2CONST(Can_HohConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpHoh;
  VAR(uint32, AUTOMATIC) LucController;
  VAR(uint32, AUTOMATIC) LucCtrlInfoIndex;
  #if ((CAN_MULTI_CORE_SUPPORT == STD_ON) && (CAN_DEV_ERROR_DETECT == STD_ON))
  VAR(uint8, AUTOMATIC) LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif /* #if (CAN_MULTI_CORE_SUPPORT == STD_ON) */

  #if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* CP_SWS_CanXL_00106 - CanXL.CANXL_E_UNINIT */
  if (CAN_FALSE == Can_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_WRITE_SID, CANXL_E_UNINIT);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  /* CP_SWS_CanXL_00107 - not CANXL Hardware Object - usCanXLNoOfHohs/CanXL_GpHohConfig is HTH for CAN XL specificly */
  else if ((Can_GpConfig->usCanXLNoOfHohs <= Hth) || (CAN_HOH_HTH != CanXL_GpHohConfig[Hth].enHoh))                     /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_WRITE_SID, CANXL_E_PARAM_HANDLE);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  #if (CAN_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core */
  else if (LucCoreId !=  Can_GpPBController[CanXL_GpHohConfig[Hth].ucController].ucCoreId)                              /* PRQA S 3416, 0404 # JV-01, JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_WRITE_SID, CANXL_E_INVALID_CORE);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  #endif /* CAN_MULTI_CORE_SUPPORT == STD_ON */
  /* CP_SWS_CanXL_00110 - Pdu is null */
  /* CP_SWS_CanXL_00112 - XLParams is null */
  else if ((NULL_PTR == PduInfo) || ((NULL_PTR == PduInfo->XLParams)))
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_WRITE_SID, CANXL_E_PARAM_POINTER);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  /* NULL for Sdu and Transmit trigger */
  /* CP_SWS_CanXL_00109 - SDU type is 0x05U - ETH tunneled frame */
  else if (CANXL_SDU_TYPE_ETH_MAPPED_TUNELLING == PduInfo->XLParams->SduType)
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_WRITE_SID, CANXL_E_INV_PARAM);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  /* CP_SWS_CanXL_00108 - violated LENG for other CANXL frame */
  else if ((CANXL_SDU_TYPE_CANFD_FRAME != PduInfo->XLParams->SduType) &&
           ((0x00U == PduInfo->length) || (CanXL_GpHohConfig[Hth].usTMDLC < PduInfo->length)))                          /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_WRITE_SID, CANXL_E_PARAM_DATA_LENGTH);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  else if ((CANXL_SDU_TYPE_CANFD_FRAME == PduInfo->XLParams->SduType) &&
           ((CanXL_GpHohConfig[Hth].usTMDLC < PduInfo->length) || (CAN_CANFD_MAX_PAYLOAD < PduInfo->length)))           /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_WRITE_SID, CANXL_E_PARAM_DATA_LENGTH);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  /* CP_SWS_CanXL_00119 - if PduInfo->XLParams->Vcid (uint16) is larger than 255 */
  else if ((uint16)0x00FFU < PduInfo->XLParams->Vcid)
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_WRITE_SID, CANXL_E_INV_PARAM);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  else if ((CANXL_SDU_TYPE_CANFD_FRAME == PduInfo->XLParams->SduType) && 
          (((0UL != (PduInfo->XLParams->AcceptanceField & 0x1FFFF800UL)) 
          && (0UL == (PduInfo->XLParams->AcceptanceField & 0x20000000UL))) || 
          ((0UL == (PduInfo->XLParams->AcceptanceField >> 31)) && (CAN_STD_MAX_PAYLOAD < PduInfo->length))))
  {
    (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_WRITE_SID, CANXL_E_INV_PARAM);
    LenReturnValue = CAN_COMMON_NOT_OK;
  }
  else
  #endif /* (CAN_DEV_ERROR_DETECT == STD_ON) */
  {
    LpHoh = &CanXL_GpHohConfig[Hth];
    /* Initial local Hoh access flag */
    LblHohAccessFlag = CAN_FALSE;
    #if (CAN_CANXL_NO_OF_HOHS > CANXL_ZERO)
    /* CP_SWS_CanXL_00103/CP_SWS_CanXL_00104 - checking if pre-empted CanXL_Write for same Hth */
    /* Critical section is required in case of the reentant call on same HTH */
    CAN_ENTER_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
    /* Check whether global flag for other hardware is already set or not */
    
    if (CAN_TRUE != CanXL_GaaHwAccessFlag[LpHoh->usHohId])
    {
      /* Set the global flag which indicates HOH is being accessed to true */
      CanXL_GaaHwAccessFlag[LpHoh->usHohId] = CAN_TRUE;
      LblHohAccessFlag = CAN_TRUE;
    } /* else no action required*/
    CAN_EXIT_CRITICAL_SECTION(CAN_RAM_DATA_PROTECTION);
    #endif
    if (CAN_TRUE == LblHohAccessFlag)
    {
      /**************************************************************************************************************/
      /**                                       Check whether device is busy                                       **/
      /**************************************************************************************************************/
      LenReturnValue = CanXL_CheckBusyQueue(&LpTargetDesc, LpHoh);
      /**************************************************************************************************************/
      /**                                           Trigger Transmission                                           **/
      /**************************************************************************************************************/
      LusSduLength = PduInfo->length;
      LpSduPtr = PduInfo->sdu;
      #if (CAN_CANXL_TRIGGER_TRANSMIT_FUNCTION == STD_ON)
      /* Checking trigger transmit if sdu is not provided */
      if ((NULL_PTR == PduInfo->sdu) && (CAN_COMMON_OK == LenReturnValue))
      {
        /* CP_SWS_CanXL_00126/CP_SWS_CanXL_00127 - If transmit trigger is enable */
        if (CAN_TRUE == CanXL_GpHohConfig[Hth].blTriggerTransmitEnable)                                                 /* PRQA S 3416 # JV-01 */
        {
          /* To be updated with more specificly as CAN XL */
          LstTTPduInfo.SduDataPtr = (P2VAR(uint8, AUTOMATIC, CAN_APPL_DATA))LaaTTSduData;                               /* PRQA S 0751, 3432 # JV-01, JV-01 */               
          LstTTPduInfo.SduLength = PduInfo->length;
          LenCanIfResult = CanIf_TriggerTransmit(PduInfo->swPduHandle, &LstTTPduInfo);
          if (E_OK == LenCanIfResult)
          {
            /* Use LstTTPduInfo instead of the original parameter */
            LusSduLength = (uint16)LstTTPduInfo.SduLength;
            LpSduPtr = LstTTPduInfo.SduDataPtr;
          }
          else
          {
            #if (CAN_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_WRITE_SID, CANXL_E_PARAM_POINTER);
            #endif
            LenReturnValue = CAN_COMMON_NOT_OK;
          }
        }
        else
        {
          #if (CAN_DEV_ERROR_DETECT == STD_ON)
          (void)Det_ReportError(CANXL_MODULE_ID, CANXL_INSTANCE_ID, CANXL_WRITE_SID, CANXL_E_PARAM_POINTER);
          #endif
          LenReturnValue = CAN_COMMON_NOT_OK;
        }
      } /* else no action required*/
      #endif /* (CAN_CANXL_TRIGGER_TRANSMIT_FUNCTION == STD_ON) */
      /* if no issue occured */
      /**************************************************************************************************************/
      /**                                  Prepare Tx descriptor and start TX queue                                **/
      /**************************************************************************************************************/
      if (CAN_COMMON_OK == LenReturnValue)
      {
        LucController = Can_GpPCController[LpHoh->ucController].ucCh;
        LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucController];
        CanXL_PrepareTxDescWrite(Hth, PduInfo, LpSduPtr, LusSduLength,  LpTargetDesc);

        if (CANXL_QUEUETYPE_TXPRIORITY == LpHoh->enBufferType)
        {
          /* Check if Queue Slot was matched */
          if(1UL != (((uint32)CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQSTS0 >> (LpHoh->usBufferIndex)) & 1UL))
          {
            /* Start trigger transmit */
            CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQCTRL2 |= 1UL << (LpHoh->usBufferIndex);
            CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQCTRL0 |= 1UL << (LpHoh->usBufferIndex);
          } /* else no action required*/
        }
        else
        {
          /* Start trigger transmit */
          CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQCTRL2 |= 1UL << (LpHoh->usBufferIndex);
          CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXFQCTRL0 |= 1UL << (LpHoh->usBufferIndex);
        }
      } /* else no action required*/
      /* Release this HTH */
      /* Clear the global flag which indicates HOH is being accessed to false */
      #if (CAN_CANXL_NO_OF_HOHS > CANXL_ZERO)
      CanXL_GaaHwAccessFlag[LpHoh->usHohId] = CAN_FALSE;
      #endif
    }
    else
    {
      /* return busy */
      LenReturnValue = (Can_CommonReturnType)CAN_BUSY;
    }
  } /* if (DET check) */
  return LenReturnValue;
}
#define CAN_STOP_SEC_PUBLIC_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : CanXL_PrepareTxDescWrite
**
** Service ID            : Not Applicable
**
** Description           : This function prepate data for a descriptor
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
** Global Variables Used : Can_GpPCController, CanXL_GaaRegs, Can_GaaDLCFromPayloadTable, CanXL_GaaCtrlStat
**
** Functions Invoked     : CanXL_ComputeCRC
**
** Reference ID          : CAN_DUD_ACT_080
** Reference ID          : CAN_DUD_ACT_080_GBL001, CAN_DUD_ACT_080_GBL002
** Reference ID          : CAN_DUD_ACT_080_GBL003, CAN_DUD_ACT_080_GBL004
** Reference ID          : CAN_DUD_ACT_080_GBL005, CAN_DUD_ACT_080_GBL006
** Reference ID          : CAN_DUD_ACT_080_GBL007, CAN_DUD_ACT_080_GBL008
** Reference ID          : CAN_DUD_ACT_080_GBL009, CAN_DUD_ACT_080_GBL010
** Reference ID          : CAN_DUD_ACT_080_REG001
***********************************************************************************************************************/
STATIC FUNC(void, CAN_PRIVATE_CODE) CanXL_PrepareTxDescWrite(Can_HwHandleType Hth, const CanXL_PduType* PduInfo, 
                        P2CONST(uint8, AUTOMATIC, CAN_APPL_DATA) LpSduPtr, uint16 LusSduLength,
                        P2VAR(Can_TxDescriptorsType, AUTOMATIC, RECAN_APPL_DATAGSPACE) Descriptor)                      /* PRQA S 3432 # JV-01 */
{
  VAR(uint8, AUTOMATIC) LucDLC;
  VAR(uint8, AUTOMATIC) LucControllerID;
  VAR(uint8, AUTOMATIC) LucController;
  VAR(uint8, AUTOMATIC) LucSec;
  VAR(uint8, AUTOMATIC) LucPaddingValue;
  VAR(uint8, AUTOMATIC) LucSdt;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint8, AUTOMATIC) LucDescIndex;
  VAR(uint16, AUTOMATIC) LucVcid;
  VAR(uint16, AUTOMATIC) LusQueue;
  VAR(uint16, AUTOMATIC) LucByteCount;
  VAR(uint16, AUTOMATIC) LusCRC;
  VAR(uint16, AUTOMATIC) LusPayloadSize;
  VAR(uint16, AUTOMATIC) LusPriority;
  VAR(uint16, AUTOMATIC) LusActualLength;
  VAR(uint16, AUTOMATIC) LusPayload;

  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpStartDec;                                                  /* PRQA S 3432, 3678 # JV-01, JV-01 */
  P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA) LpCanXLHWInfo;
  P2VAR(uint8, AUTOMATIC, CAN_CONFIG_DATA) LpDataContainer;                                                             /* PRQA S 3432 # JV-01 */
  P2VAR(PduIdType, AUTOMATIC, CAN_CONFIG_DATA) LpSwPduHandle;                                                           /* PRQA S 3432 # JV-01 */

  /* DMA Info Ctrl 1 */
  LusQueue = CanXL_GpHohConfig[Hth].usBufferIndex;
  LucControllerID = CanXL_GpHohConfig[Hth].ucController;
  LucController = Can_GpPCController[LucControllerID].ucCh;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucController];
  LucPaddingValue = CanXL_GpHohConfig[Hth].ucPaddingValue;
  LusPriority = PduInfo->XLParams->PriorityId;
  LucSec = PduInfo->XLParams->Sec;
  LucSdt = PduInfo->XLParams->SduType;
  LucVcid = PduInfo->XLParams->Vcid;
  LpCanXLHWInfo = (P2CONST(Can_CanXLHWUnitInfoType, AUTOMATIC, CAN_CONFIG_DATA))Can_GpConfig->pCanXLHWUnitInfo;         /* PRQA S 0316 # JV-01 */
  /* Setting payload length to align 32-bit */
  if(3UL == LucSdt)
  {
    LucDLC = Can_GaaDLCFromPayloadTable[LusSduLength];
    LusActualLength = (uint16)(Can_GaaPayloadFromDLCTable[LucDLC] + 1U);                                                /* PRQA S 3383, 4391 # JV-01, JV-01 */
  }
  else
  {
    LusActualLength = LusSduLength;
  }
  LusPayloadSize = ((LusActualLength - 1U) / 4U) + 1U;                                                                  /* PRQA S 3383 # JV-01 */
  /* Re-initialize descriptor */
  Descriptor->ulElement0 &= CAN_DMA1_RESET_VALUE;
  Descriptor->ulElement1 &= CAN_DMA2_RESET_VALUE;
  /* Update for element 0 */
  Descriptor->ulElement0 |= (uint32)CANXL_BIT_VALID(1U);                                                                /* PRQA S 3469 # JV-01 */
  /* Update for element 1 */
  Descriptor->ulElement1 |= (uint32)CANXL_BIT_SIZE(LusPayloadSize) | CANXL_BIT_PLSRC(1U);                               /* PRQA S 3469 # JV-01 */
  /* Check for Tx Priority Queue HTH */
  if (CANXL_QUEUETYPE_TXPRIORITY == CanXL_GpHohConfig[Hth].enBufferType)                                                /* PRQA S 3416 # JV-01 */
  {
    LucDescIndex = LpCanXLHWInfo[LucCtrlInfoIndex].pTxPriorityQueueConfig->aaDescIndex[LusQueue];
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
    LusPayload = LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LusQueue].usPayloadSize;
    LpStartDec = (Can_TxDescriptorsType *)(CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LusQueue].ulTXSTADD);         /* PRQA S 0306 # JV-01 */
    /* Get data container pointer */
    LpDataContainer = &LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LusQueue].
                          pDataContainer[(uint16)(Descriptor - LpStartDec) * LusPayload];                               /* PRQA S 0488 # JV-01 */
    /* Get swPduHandle pointer */
    LpSwPduHandle = &LpCanXLHWInfo[LucCtrlInfoIndex].pTxFIFOQueueConfig[LusQueue].pSwPduHandle[0];
    /* Save swPduHandle to global data */
    *(LpSwPduHandle + (Descriptor - LpStartDec))= PduInfo->swPduHandle;                                                 /* PRQA S 0488 # JV-01 */
  }
  /* Update for element 2 */
  Descriptor->ulElement2TS0 = 0UL;
  /* Update for element 3 */
  Descriptor->ulElement3TS1 = 0UL;
  /* Update for element 4 */
  Descriptor->ulElement4T0 = (uint32)(CANXL_T0_FIXED | CANXL_BIT_PRID(LusPriority & CANXL_PRIORITY_IDMASK)              /* PRQA S 3469 # JV-01 */
                                      | CANXL_BIT_SEC(LucSec) | CANXL_BIT_SDT((uint32)LucSdt)                           /* PRQA S 3469 # JV-01 */
                                      | CANXL_BIT_VCID((uint32)LucVcid));                                               /* PRQA S 3469 # JV-01 */
  Descriptor->ulElement5T1 = (uint32)(CANXL_T1_FIXED | CANXL_BIT_DLCXL(LusActualLength - 1U));                          /* PRQA S 2986, 3383, 4391 # JV-01, JV-01, JV-01 */
  Descriptor->ulElement6T2TD0 = PduInfo->XLParams->AcceptanceField;
  /* Update for element 7 */
  Descriptor->ulElement7TX_APTD1 = (uint32)LpDataContainer;                                                             /* PRQA S 0306 # JV-01 */
  /* Add byte-1 data if frame's SDT equal to 3 */
  if(3UL == LucSdt)
  {
    *LpDataContainer = LucDLC;
    LpDataContainer++;
  } /* else no action required*/
  /* Add input payload to data container */
  for(LucByteCount = 0U; LucByteCount < LusSduLength; LucByteCount++)
  {
    *(LpDataContainer + LucByteCount) = *(LpSduPtr + LucByteCount);                                                     /* PRQA S 0488 # JV-01 */
  }
  /* Add padding value to payload if neccessary */
  if((0U != (LusActualLength - LusSduLength - 1U)) && (3UL == LucSdt))                                                  /* PRQA S 3384 # JV-01 */
  {
    for(LucByteCount = LusSduLength; LucByteCount < (LusActualLength - 1U) ; LucByteCount++)                            /* PRQA S 3383 # JV-01 */
    {
      *(LpDataContainer + LucByteCount) = LucPaddingValue;                                                              /* PRQA S 0488 # JV-01 */
    }
  } /* else no action required*/
  /* Calculate CRC for TX descriptor */
  LusCRC = CanXL_ComputeCRC((uint32 *)Descriptor, CANXL_TX_DESC);                                                       /* PRQA S 0310 # JV-01 */
  /* Update CRC value to TX descriptor */
  Descriptor->ulElement0 |= (uint32)(CANXL_BIT_CRC(LusCRC));                                                            /* PRQA S 3469 # JV-01 */
}
#define CAN_STOP_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : CanXL_CheckBusyQueue
**
** Service ID            : Not Applicable
**
** Description           : This function check busy Queue and point to vacancy for descriptor
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LpHoh : Pointer to Hth need to perform transmission
**                         LpTargetDesc: Pointer to invalid descriptor
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Can_GpPCController, Can_GaaRegs
**
** Functions Invoked     : None
**
** Reference ID          : CAN_DUD_ACT_079
** Reference ID          : CAN_DUD_ACT_079_REG001, CAN_DUD_ACT_079_REG002
** Reference ID          : CAN_DUD_ACT_079_REG003, CAN_DUD_ACT_079_REG004
** Reference ID          : CAN_DUD_ACT_079_GBL001
***********************************************************************************************************************/
FUNC(Can_CommonReturnType, CAN_PRIVATE_CODE) CanXL_CheckBusyQueue(                                                      /* PRQA S 1505 # JV-01 */                     
  P2VAR(Can_TxDescriptorsType *, AUTOMATIC, ETH_APPL_DATA) LpTargetDesc,                                                /* PRQA S 3432 # JV-01 */
  P2CONST(Can_HohConfigType, AUTOMATIC, CAN_CONFIG_DATA) LpHoh)
                                                        
{
  VAR(Can_CommonReturnType, AUTOMATIC) LenRetValue;
  VAR(uint8, AUTOMATIC) LucController;
  VAR(uint8, AUTOMATIC) LucCtrlInfoIndex;
  VAR(uint32, AUTOMATIC) LulSize;
  VAR(uint16, AUTOMATIC) LusQueue;
  VAR(uint16, AUTOMATIC) LusDecIndex;
  VAR(Can_BufferType, AUTOMATIC) LenBufferType;
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpCurrentDec;                                                /* PRQA S 3432 # JV-01 */
  P2VAR(Can_TxDescriptorsType, AUTOMATIC, CAN_CONFIG_DATA) LpStartDec;                                                  /* PRQA S 3432 # JV-01 */

  LenRetValue = CAN_COMMON_OK;
  
  LusQueue = (uint8)(LpHoh->usBufferIndex);
  LucController = Can_GpPCController[LpHoh->ucController].ucCh;
  LucCtrlInfoIndex = Can_GpConfig->pCanXLSecondPhysicalControllerToIndex[LucController];
  LenBufferType = LpHoh->enBufferType;
  /* Check for Tx Priority Queue HTH */
  if (CANXL_QUEUETYPE_TXPRIORITY == LenBufferType)
  {
    /* If Tx Priority Queue slot is full, return CAN_BUSY */
    if (0U != ((1UL << (LusQueue)) & CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQSTS0))
    {
      LenRetValue = (Can_CommonReturnType)CAN_BUSY;
    }
    else
    {
      *LpTargetDesc = (Can_TxDescriptorsType *)(CanXL_GaaRegs[LucCtrlInfoIndex].pMH->ulTXPQSTADD) + LusQueue;          /* PRQA S 0488, 0306 # JV-01, JV-01 */
    }
  }
  /* Check for Tx FIFO Queue HTH */
  else
  {
    LulSize = CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LusQueue].ulTXSIZE;
    LpStartDec = (Can_TxDescriptorsType *)(CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LusQueue].ulTXSTADD);         /* PRQA S 0306 # JV-01 */
    LpCurrentDec =(Can_TxDescriptorsType *)(CanXL_GaaRegs[LucCtrlInfoIndex].pMH->aaTXFQReg[LusQueue].ulTXADDPT);        /* PRQA S 0306 # JV-01 */
    if(NULL_PTR == LpCurrentDec)
    {
      LpCurrentDec = LpStartDec;
    } /* else no action required */
    LusDecIndex = 0;
    /* look for a invalid descriptor among all descriptors of seletected queue */
    while (LusDecIndex <= LulSize)
    {
      if (0UL == ((uint32)(LpCurrentDec->ulElement0) & (CANXL_BIT_VALID(1U))))                                          /* PRQA S 3469 # JV-01 */
      {
        /* Set the found vacancy as the descriptor place for this Tx messsage */
        *LpTargetDesc = LpCurrentDec;
        break;
      }
      /* If it is not reach last descriptor yet, move to next descriptor */
      if (LpCurrentDec != CanXL_GaaCtrlStat[LucCtrlInfoIndex].stHwStatFixed.aaLastTxDesc[LusQueue])
      {
        LpCurrentDec = LpCurrentDec + 1;                                                                                /* PRQA S 0489 # JV-01 */
      }
      /* Or wrap to first descriptor if reach the last one */
      else
      {
        LpCurrentDec = LpStartDec;
      } /* else no action required */
      LusDecIndex++;
    }
    /* If Tx FIFO Queue is full, return CAN_BUSY */
    if (LusDecIndex > LulSize)
    {
      LenRetValue = (Can_CommonReturnType)CAN_BUSY;
    }
  }
  return LenRetValue;
}
/***********************************************************************************************************************
** Function Name         : CanXL_ComputeCRC
**
** Service ID            : Not Applicable
**
** Description           : This function compute CRC for a descriptor
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : Descriptor :Pointer to a Descriptor
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
** Functions Invoked     : None
**
** Reference ID          : CAN_DUD_ACT_078
***********************************************************************************************************************/
FUNC(uint16, CAN_PRIVATE_CODE) CanXL_ComputeCRC(P2CONST(uint32, AUTOMATIC, RECAN_APPL_DATAGSPACE)
                                                                      Descriptor, uint8 DescType)
{
  VAR(uint8, AUTOMATIC)  LucElementIndex;
  VAR(uint8, AUTOMATIC)  LucMaxElementIndex;
  VAR(uint8, AUTOMATIC)  LucBitIndex;
  VAR(uint8, AUTOMATIC)  LucLoopIndex;
  VAR(uint8, AUTOMATIC)  LucTargetBit;
  VAR(uint16, AUTOMATIC) LusRem9Old;
  VAR(uint16, AUTOMATIC) LusRem9 = 0x1FF;
  VAR(uint16, AUTOMATIC) LusPoly = 0x167;
  /* Get number of descriptor element */
  if(DescType == CANXL_TX_DESC)
  {
    LucMaxElementIndex = 8U;
  }
  else
  {
    LucMaxElementIndex = 2U;
  }
  /* Loop all descriptor element */
  for(LucElementIndex = 0U; LucElementIndex < LucMaxElementIndex; LucElementIndex++)
  {
    /* Loop all element bit */
    for (LucBitIndex = 32U; LucBitIndex >= 1U; LucBitIndex--)
    {
      /* Save the current value */
      LusRem9Old = LusRem9;
      /* Right-shift current value */
      LusRem9 = (uint16)(LusRem9 << 1U);
      LusRem9 &= 0x1FFU;
      LucTargetBit = (uint8)(*(Descriptor) >> (LucBitIndex - 1U)) & 1U;                                                 /* PRQA S 3383 # JV-01 */
      /* Check the value of current bit of element and update current value*/
      if(1U == LucTargetBit)
      {
        LusRem9 |= 0x001U;
      }
      else
      {
        LusRem9 &= 0x1FEU;                                                                                              /* PRQA S 2985 # JV-01 */       
      }
      if (1U == ((LusRem9Old >> 8U) & 1U))
      {
        /* XOR with poly */
        LusRem9 = LusRem9 ^ LusPoly;
      }
    }
    /* Move to next element */
    Descriptor ++;                                                                                                      /* PRQA S 1338 # JV-01 */
  }

  /* Re-calculate the descriptor */
  for(LucLoopIndex = 0U; LucLoopIndex < 9U; LucLoopIndex++)
  {
    LusRem9Old = LusRem9;
    LusRem9 = (uint16)(LusRem9 << 1UL);
    LusRem9 &= 0x1FEU;
    if (1U == ((LusRem9Old >> 8U) & 1U))
    {
      LusRem9 = LusRem9 ^ LusPoly;
    }
  }
  return (LusRem9);
}
#define CAN_STOP_SEC_PRIVATE_CODE
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (CAN_CANXL_SUPPORTED == STD_ON) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/

