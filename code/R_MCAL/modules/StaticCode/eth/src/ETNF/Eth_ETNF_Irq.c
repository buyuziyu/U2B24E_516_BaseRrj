/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_ETNF_Irq.c                                                                                      */
/*====================================================================================================================*/
/*                                             COPYRIGHT                                                              */
/*====================================================================================================================*/
/* (c) 2023 - 2025 Renesas Electronics Corporation. All rights reserved.                                              */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Interrupt Service Routine for  Ethernet Driver Component                                        */
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
/* associated with its exercise of rights under this Agreement, including, but not limited to the risks and costs     */
/* of program errors, compliance with applicable laws, damage to or loss of data, programs or equipment,              */
/* and unavailability or interruption of operations.                                                                  */
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
/*                                      Devices:        X2x                                                           */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                       Revision Control History                                                     **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/05/2025    : Update SW-VERSION for RH850/Ver22.01.02 U2Cx release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 22/07/2024    : Update QAC message
 * 2.0.4: 28/03/2024    : Change variable name 
 *                        from Eth_GaaDemEventIntInconsistent to Eth_GpDemEventIntInconsistent,
 *                        from Eth_GaaDemEventDmaError to Eth_GpDemEventDmaError.
 *        26/12/2023    : Update QAC message.
 *        19/12/2023    : Initial Version
 */
/******************************************************************************/

/***********************************************************************************************************************
**                                       Include Section                                                              **
***********************************************************************************************************************/
#include "Eth.h"
#include "Eth_Ram.h"
#include "Eth_ETNF_Irq.h"
#include "Eth_ETNF_Dma.h"
#include "Eth_ETNF_Ram.h"
/* Included for declaration of the function Dem_ReportErrorStatus() */
#include "Dem.h"
/***********************************************************************************************************************
**                                      Version Information                                                           **
***********************************************************************************************************************/
#if (ETH_MACRO_ETNF == STD_ON)
/* AUTOSAR release version information */
#define ETH_ETNF_IRQ_C_AR_RELEASE_MAJOR_VERSION ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETH_ETNF_IRQ_C_AR_RELEASE_MINOR_VERSION ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETH_ETNF_IRQ_C_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ETH_ETNF_IRQ_C_SW_MAJOR_VERSION    ETH_SW_MAJOR_VERSION_VALUE
#define ETH_ETNF_IRQ_C_SW_MINOR_VERSION    ETH_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                      Version Check                                                                 **
***********************************************************************************************************************/

/* Functionality related to R4.0 */
#if (ETH_AR_RELEASE_MAJOR_VERSION != ETH_ETNF_IRQ_C_AR_RELEASE_MAJOR_VERSION)
  #error "Eth_ETNF_Irq.c : Mismatch in Release Major Version"
#endif
#if (ETH_AR_RELEASE_MINOR_VERSION != ETH_ETNF_IRQ_C_AR_RELEASE_MINOR_VERSION)
  #error "Eth_ETNF_Irq.c : Mismatch in Release Minor Version"
#endif
#if (ETH_AR_RELEASE_REVISION_VERSION != ETH_ETNF_IRQ_C_AR_RELEASE_REVISION_VERSION)
  #error "Eth_ETNF_Irq.c : Mismatch in Release Revision Version"
#endif

#if (ETH_SW_MAJOR_VERSION != ETH_ETNF_IRQ_C_SW_MAJOR_VERSION)
  #error "Eth_ETNF_Irq.c : Mismatch in Software Major Version"
#endif
#if (ETH_SW_MINOR_VERSION != ETH_ETNF_IRQ_C_SW_MINOR_VERSION)
  #error "Eth_ETNF_Irq.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3408)    : %s' has external linkage and is being defined without any previous declaration.              */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4                                                         */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function 'name' is defined but is not used within this project.                          */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1                                                         */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/*                       REFERENCE - ISO:C90-6.3.1 Primary Expressions                                                */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is           */
/*                       accepted.                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to call a function         */
/*                       here for such a small operation.                                                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add     */
/*                       a wraparound guard here.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : (4:5087) #include statements in a file should only be preceded by other preprocessor         */
/*                       directives or comments.                                                                      */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is accepted, due to implementation for include memmap is following AUTOSAR rule.        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : MISRA C:2012 Rule-13.5, CERTCCM EXP02, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it does not have direct access to the HW register, and     */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with possible side effects.                        */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : This is necessary for suppressing optimization by dummy loop.                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3, CWE Rule CWE-398, CWE-569                                              */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : [E] This in-line assembler construct is a language extension. The code has been ignored.     */
/* Rule                : MISRA-C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTC 1.2.4 MSC14                                   */
/* JV-01 Justification : Inline assembler support for syncp instruction.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2844)    : Possible: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127        */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2824)    : Possible: Arithmetic operation on NULL pointer.                                              */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-468, CWE-476, CWE-465, CWE-737                                   */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1532)    : The function '%1s' is only referenced in one translation unit - but not the one in which it  */
/*                       is defined.                                                                                  */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the specific coding rule, function of each hardware unit is         */
/*                       implemented in separated files for this hardware unit. Could not be static function.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2934)    : Possible: Computing an invalid pointer value.                                                */
/* Rule                : CERTCCM ARR30, ARR37, ARR38, EXP08                                                           */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-476, CWE-465, CWE-737, CWE-690                                   */
/* JV-01 Justification : This is accepted, due to the implementation following hardware specification.                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                              Global Data                                                           **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                              Function Definitions                                                  **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name         : ETH_AVB0DATAISR
**
** Service ID            : NA
**
** Description           : Data Interrupt Service Handler
**
** Sync/Async            : NA
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
** Global Variable(s)    : Eth_GaaETNFEICRegs, Eth_GpDemEventIntInconsistent
**
** Function(s) invoked   : Eth_DemConfigCheck, Eth_ETNF_HwTxConfirmation, Eth_Hw_ETNF_RxIrqHdlr
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_437,
** Reference ID          : ETH_DUD_ACT_437_ERR001
***********************************************************************************************************************/
#define ETH_START_SEC_CODE_FAST
#include "Eth_MemMap.h"

#if (ETH_AVB0_DATA_ISR == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ETH_AVB0DATAISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
ISR(ETH_AVB0DATAISR_CAT2)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
#else
_INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_AVB0DATAISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  #if (ETH_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  if (((ETH_EIC_CONSISTENCY_MASK & ~ETH_EIC_EIMK_MASK) !=
      (Eth_GaaETNFEICRegs[ETHAVB0]->usDATA & ETH_EIC_CONSISTENCY_MASK))                                                 

  #if (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)
    || ((0UL != (Eth_GaaETNFRegs[ETHAVB0]->ulRIS0 & (uint32)(~ETH_RX_QUEUE_CONFIG_0)))                                  
    && (ETH_ENABLE == Eth_GpEthConfigPtr[ETHAVB0].enRxInterruptMode))                                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  #endif
  #if (ETH_CTRL_ENABLE_TX_INTERRUPT == STD_ON)
    || ((0UL != (Eth_GaaETNFRegs[ETHAVB0]->ulDIS & (uint16)(~ETH_TX_QUEUE_CONFIG_0)))
    && (ETH_ENABLE == Eth_GpEthConfigPtr[ETHAVB0].enTxInterruptMode))                                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  #endif
    )
  {
    Eth_DemConfigCheck(Eth_GpDemEventIntInconsistent[ETHAVB0], DEM_EVENT_STATUS_FAILED);                                
  }
  else
#endif
  {
    if (ETH_ENABLE == Eth_GpEthConfigPtr[ETHAVB0].enTxInterruptMode)                                                    /* PRQA S 3416 # JV-01 */
    {
      Eth_ETNF_HwTxConfirmation(ETHAVB0);
    }
    else
    {
      /* No action required */
    }

    #if (ETH_CTRL_ENABLE_RX_INTERRUPT == STD_ON)
    if (ETH_ENABLE == Eth_GpEthConfigPtr[ETHAVB0].enRxInterruptMode)                                                    /* PRQA S 3416 # JV-01 */
    {
      Eth_Hw_ETNF_RxIrqHdlr(ETHAVB0);
    }
    else
    {
      /* No action required */
    }
    #endif
  }
}
#endif /* (ETH_AVB0_DATA_ISR == STD_ON) */

/***********************************************************************************************************************
** Function Name         : ETH_AVB0ERRISR
**
** Service ID            : NA
**
** Description           : Error Interrupt Service Handler
**
** Sync/Async            : NA
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
** Global Variable(s)    : Eth_GaaETNFEICRegs, Eth_GpDemEventIntInconsistent,
**                         Eth_GpDemEventDmaError, Eth_GaaETNFRegs
**
** Function(s) invoked   : Eth_DemConfigCheck
**
** Registers Used        : EIC, ETNFnESR, ETNFnEIS
**
** Reference ID          : ETH_DUD_ACT_438,
** Reference ID          : ETH_DUD_ACT_438_ERR001, ETH_DUD_ACT_438_ERR002
** Reference ID          : ETH_DUD_ACT_438_REG001
***********************************************************************************************************************/
#if (ETH_AVB0_ERR_ISR == STD_ON)
#if defined (Os_ETH_AVB0ERRISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
ISR(ETH_AVB0ERRISR_CAT2)                                                                                                /* PRQA S 1503, 3408, 3006 # JV-01, JV-01, JV-01 */
#else
_INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_AVB0ERRISR(void)                                                              /* PRQA S 1503, 3006 # JV-01, JV-01 */
#endif
{
  uint32 LulRegVal;
  #if (ETH_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  if (((ETH_EIC_CONSISTENCY_MASK & ~ETH_EIC_EIMK_MASK) !=
      (Eth_GaaETNFEICRegs[ETHAVB0]->usERR & ETH_EIC_CONSISTENCY_MASK)) ||                                               
      (0UL == (Eth_GaaETNFRegs[ETHAVB0]->ulEIS & ETH_EIS_QEF_MASK)))                                                    
  {
    Eth_DemConfigCheck(Eth_GpDemEventIntInconsistent[ETHAVB0], DEM_EVENT_STATUS_FAILED);                                
  }
  else
  #endif
  {
    LulRegVal = Eth_GaaETNFRegs[ETHAVB0]->ulESR & ETH_ETNF_ESR_ERROR_MASK;                                              
    if (ETH_ETNF_ESR_ERROR_TX_BUFFER != LulRegVal)
    {
      /* No action required */
    }
    else
    {
      /* Critical error detection on the MAC controller */
      Eth_DemConfigCheck(Eth_GpDemEventDmaError[ETHAVB0], DEM_EVENT_STATUS_FAILED);                                     
    }

    /* Clear Error Flag */
    LulRegVal = Eth_GaaETNFRegs[ETHAVB0]->ulEIS;
    Eth_GaaETNFRegs[ETHAVB0]->ulEIS = ~(LulRegVal & ETH_ETNF_EIC_ERROR);
    /* Execute the pipeline to avoid multiple interrupts */
    (void)Eth_GaaETNFRegs[ETHAVB0]->ulEIS;
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  }
}

#endif /* (ETH_AVB0_ERR_ISR == STD_ON) */

/***********************************************************************************************************************
** Function Name         : ETH_AVB0MNGISR
**
** Service ID            : NA
**
** Description           : Other Management Interrupt
**
** Sync/Async            : NA
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
** Global Variable(s)    : Eth_GaaETNFRegs, Eth_GaaTxBufferIndex, Eth_GaaETNFEICRegs
**
** Function(s) invoked   : None
**
** Registers Used        : ETNFnTFA2, ETNFnTFA0, ETNFnTFA1, ETNFnTCCR, ETNFnTSR,
**                         ETNFnTIS
**
** Reference ID          : ETH_DUD_ACT_439,
** Reference ID          : ETH_DUD_ACT_439_ERR001, ETH_DUD_ACT_439_GLB001
** Reference ID          : ETH_DUD_ACT_439_GLB002, ETH_DUD_ACT_439_REG004
***********************************************************************************************************************/
#if (ETH_AVB0_MNG_ISR == STD_ON)
#if defined (Os_ETH_AVB0MNGISR_CAT2) || (ETH_ISR_CATEGORY_2 == STD_ON)
ISR(ETH_AVB0MNGISR_CAT2)                                                                                                /* PRQA S 3408, 1503, 3006 # JV-01, JV-01, JV-01 */
#else
_INTERRUPT_ FUNC(void, ETH_CODE_FAST) ETH_AVB0MNGISR(void)                                                              /* PRQA S 1503, 3006 # JV-01, JV-01 */
#endif
{
  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  uint8 LucFifoCount;
  uint16 LusTxBufferIdx;
  P2VAR(Eth_TxBufferType, AUTOMATIC, ETH_APPL_DATA) LpTxBuffer;                                                         /* PRQA S 3432 # JV-01 */
  #endif

  #if (ETH_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  if (((ETH_EIC_CONSISTENCY_MASK & ~ETH_EIC_EIMK_MASK) !=
      (Eth_GaaETNFEICRegs[ETHAVB0]->usMNG & ETH_EIC_CONSISTENCY_MASK)) ||                                               
      (0UL == (Eth_GaaETNFRegs[ETHAVB0]->ulTIS & ETH_TIS_TFUF_MASK)))                                                   
  {
    Eth_DemConfigCheck(Eth_GpDemEventIntInconsistent[ETHAVB0], DEM_EVENT_STATUS_FAILED);                                
  }
  else
  #endif
  {
    #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
    if (0UL != (Eth_GaaETNFRegs[ETHAVB0]->ulTIS & ETH_TIS_TFUF_MASK))
    {
      /* Get timestamp fifo counter */
      /* ETNFnTSR.TFFL is 8-10bit. so, casting to uint8 does no problem. */
      LucFifoCount = (uint8)(ETH_ETNF_GET_TFFL(Eth_GaaETNFRegs[ETHAVB0]->ulTSR));                                       /* PRQA S 3469 # JV-01 */

      do
      {
        /* Read buffer index from ETNFnTFA2.TST */
        LusTxBufferIdx = (uint16)(ETH_ETNF_GET_TST(Eth_GaaETNFRegs[ETHAVB0]->ulTFA2));                                  /* PRQA S 3469 # JV-01 */

        /* Initialize pointer to timestamp buffer */
        LpTxBuffer = (Eth_TxBufferType *)&Eth_GaaTxBufferIndex[ETHAVB0][LusTxBufferIdx];                                

        /* Read timestamp value to Tx buffer */
        LpTxBuffer->stTimeStamp.nanoseconds = Eth_GaaETNFRegs[ETHAVB0]->ulTFA0;                                         
        LpTxBuffer->stTimeStamp.seconds = Eth_GaaETNFRegs[ETHAVB0]->ulTFA1;
        LpTxBuffer->stTimeStamp.secondsHi = (uint16)(Eth_GaaETNFRegs[ETHAVB0]->ulTFA2 & ETH_TFA2_TSV_MASK);

        /* Release oldest entry in Timestamp FIFO - TCCR.TFR = 1 */
        Eth_GaaETNFRegs[ETHAVB0]->ulTCCR |= ETH_ETNF_TCCR_TFR;

        /* Set timestamp quality information as ETH_VALID */
        LpTxBuffer->enTimeQual = ETH_VALID;

        LucFifoCount--;                                                                                                 /* PRQA S 3383 # JV-01 */
      } while (0U < LucFifoCount);

      /* Execute the pipeline to avoid multiple interrupts */
      (void)Eth_GaaETNFRegs[ETHAVB0]->ulTCCR;
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */
    }
    else
    #endif
    {
      /* No action */
    }
  }
}
#endif /* (ETH_AVB0_ERR_ISR == STD_ON) */

#define ETH_STOP_SEC_CODE_FAST
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* ETH_MACRO_ETNF == STD_ON */
/***********************************************************************************************************************
**                                           End of File                                                              **
***********************************************************************************************************************/
