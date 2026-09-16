/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_ECM_Irq.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains API function implementations of MCU Driver                                                      */
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
/*              Devices:        X2X                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025   : Update SW-VERSION for U2Bx Ver22.02.00.001 Release
 * 2.5.0:  30/06/2025   : Update SW-VERSION for U2Ax Ver22.01.00(D) Release
 * 2.4.0:  31/05/2025   : Update SW-VERSION for U2Cx Ver21.01.01 Release
 * 2.3.2:  29/04/2025   : Update SW-VERSION for U2Ax Ver22.00.03 Release
 * 2.3.1:  31/03/2025   : Update SW-VERSION for U2BxE Ver22.00.02 Release
 * 2.3.0:  28/02/2025   : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Release
 * 2.1.2:  31/10/2024   : Update SW-VERSION to 2.1.2
 * 2.1.1:  30/08/2024   : Update SW-VERSION to 2.1.1
 * 2.0.0:  04/08/2023   : Remove redundant QAC message 0857
 *         10/07/2023   : Remove redundant QAC message 3469, 2880, 2877, 2986, 2741, 2983
 *         01/07/2023   : Update to clear the FE interrupt flag before the for loop of ECMMESSTRj registers
 *                        in function MCU_FEINT_ISR.
 *                        Remove the check status of ECMmESSTRj registers before the Interrupt Consistency Check
 *                        in function MCU_FEINT_ISR, MCU_ECM_EIC9_ISR and MCU_ECM_EIC8_ISR.
 * 1.4.5:  06/01/2023   : As new Mcu structure:
 *                        - Update functions: MCU_FEINT_ISR() , MCU_ECM_EIC9_ISR() and MCU_ECM_EIC8_ISR()
 *                        - Add QAC Messages
 * 1.4.4:  18/07/2022   : Update QAC message 9.5.0
 *         06/07/2022   : Add condition "MCU_PROCESSOR_ELEMENT_4 == STD_ON" when selected U2B20/U2B24
 *                        into function MCU_FEINT_ISR() , MCU_ECM_EIC9_ISR() and MCU_ECM_EIC8_ISR()
 * 1.4.3:  24/05/2022   : Update QAC msg 3408, 1503
 *         11/05/2022   : Removed "else" statement don't use when no action required, updated QAC message
 *         13/04/2022   : Update SW-VERSION to 1.4.3
 * 1.3.1:  02/07/2021   : Add QAC message 9.5.0
 *                        Format source code to 120 characters
 *                        Improve Violation tag (remove START/END)
 *         12/05/2021   : Insert space before and after a binary operator
 *                        with the emphasis on readability.
 *         07/05/2021   : As per ARDAACL-145
 *                        Add preprocessor for PE2, PE3 Status Clear in function
 *                        MCU_FEINT_ISR
 *                        Fix typo: LpFeiNotfyFuncPtr -> LpFeiNotifyFuncPtr,
 *                        LpEiNotfyFuncPtr -> LpEiNotifyFuncPtr,
 *                        LpEiDCLSNotfyFuncPtr -> LpEiDCLSNotifyFuncPtr
 * 1.3.0:  25/11/2020   : Release
 * 1.2.0:  17/07/2020   : Release
 * 1.1.0:  19/06/2020   : Release
 * 1.0.5:  16/06/2020   : As per ticket #267934
 *                        Update to add QAC message for lastest MCU driver code
 *                        Related msg 0303, 3204, 1031
 * 1.0.4:  05/06/2020   : As per ticket #273546
 *                        In function MCU_FEINT_ISR, update to check status flag of register FEINTF before checking for
 *                        interrupt consistency.
 * 1.0.3:  26/05/2020   : As per ticket #270238
 *                        Fix and add message for QAC
 * 1.0.2:  20/05/2020   : As per #270992
 *                        Mask DCLS MCU_ECM_ESSTR_DCLS_MASK error for the appropriate core for E2x
 * 1.0.1:  26/04/2020   : As per #266147
 *                        Mask DCLS error for the appropriate core for U2x (ISR8 and ISR9)
 * 1.0.0:  10/01/2020   : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : MISRA C:2012 Rule-15.7, CERTCCM MSC01, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2742)    : This 'if' controlling expression is a constant expression and its value is 'false'.          */
/* Rule                : MISRA C:2012 Rule-14.3, CWE Rule CWE-570, CWE-569                                            */
/* JV-01 Justification : It is specific for device and confirmed has no issue in software behavior.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (8:2841)    : Definite: Dereference of an invalid pointer value.                                           */
/* Rule                : MISRA C:2012 Rule-21.18, Rule-18.1, Dir-4.1, CERTCCM ARR30, CWE Rule CWE-120, CWE-121,       */
/*                       CWE-122, CWE-124, CWE-125, CWE-126, CWE-127, CWE-129, CWE-131, CWE-466, CWE-786, CWE-787,    */
/*                       CWE-788, CWE-805, CWE-465, CWE-633, CWE-740                                                  */
/* JV-01 Justification : This is the buffer pool array used for the entire system this module.                        */
/*       Verification  : There is no problem because it is an intended design considering the space-time tradeoff,    */
/*                       that is, scalability.                                                                        */
/**********************************************************************************************************************/
/* Message (6:2880)    : This code is unreachable.                                                                    */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-670                                       */
/* JV-01 Justification : Part of the code is manually check and confirmed to be executable depending on the           */
/*                       configuration                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2962)    : Apparent: Using value of uninitialized automatic object '%s'.                                */
/* Rule                : MISRA C:2012 Rule-9.1, CERTCCM EXP33, CWE Rule CWE-457, CWE-824, CWE-908, CWE-452, CWE-465,  */
/*                       CWE-737                                                                                      */
/* JV-01 Justification : It will be initialized based on scope of 'if' statements where at least an 'if' statement    */
/*                       will be executed that will initialize the variable.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563,     */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2992)    : The value of this 'if' controlling expression is always 'false'.                             */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : This is to support different configuration, macro value can be generated so that such        */
/*                       conditional statement can be either true or false                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : '%s' has external linkage and is being defined without any previous declaration.             */
/* Rule                : MISRA C:2012 Rule-8.4, CERTCCM DCL07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used following AUTOSAR standard rule. It is accepted.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : This is accepted. It is just advice for improve safety by reducing the possibility that the  */
/*                       referenced data is unintentionally modified through an unexpected alias and improves         */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4391)    : A composite expression of 'essentially unsigned' type (%1s) is being cast to a wider         */
/*                       unsigned type, '%2s'.                                                                        */
/* Rule                : MISRA C:2012 Rule-10.8, CWE Rule CWE-136                                                     */
/* JV-01 Justification : This casting is for the lower operator which requires wider type.                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/* Included for module version information definitions required for Mcu_Irq.c                                         */
#include "Mcu.h"

/* Included for ISR functions declaration */
#include "Mcu_ECM_Irq.h"

/* Included for ram variable declaration */
#include "Mcu_Ram.h"

/* Included for declaration of the function Dem_ReportErrorStatus() and Dem_SetEventStatus() */
#include "Dem.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define MCU_ECM_IRQ_C_AR_RELEASE_MAJOR_VERSION    MCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define MCU_ECM_IRQ_C_AR_RELEASE_MINOR_VERSION    MCU_AR_RELEASE_MINOR_VERSION_VALUE
#define MCU_ECM_IRQ_C_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MCU_ECM_IRQ_C_SW_MAJOR_VERSION            MCU_SW_MAJOR_VERSION_VALUE
#define MCU_ECM_IRQ_C_SW_MINOR_VERSION            MCU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (MCU_ECM_IRQ_AR_RELEASE_MAJOR_VERSION != MCU_ECM_IRQ_C_AR_RELEASE_MAJOR_VERSION)
#error "Mcu_ECM_Irq.c : Mismatch in Release Major Version"
#endif

#if (MCU_ECM_IRQ_AR_RELEASE_MINOR_VERSION != MCU_ECM_IRQ_C_AR_RELEASE_MINOR_VERSION)
#error "Mcu_ECM_Irq.c : Mismatch in Release Minor Version"
#endif

#if (MCU_ECM_IRQ_AR_RELEASE_REVISION_VERSION != MCU_ECM_IRQ_C_AR_RELEASE_REVISION_VERSION)
#error "Mcu_ECM_Irq.c : Mismatch in Release Revision Version"
#endif

#if (MCU_ECM_IRQ_SW_MAJOR_VERSION != MCU_ECM_IRQ_C_SW_MAJOR_VERSION)
#error "Mcu_ECM_Irq.c : Mismatch in Software Major Version"
#endif
#if (MCU_ECM_IRQ_SW_MINOR_VERSION != MCU_ECM_IRQ_C_SW_MINOR_VERSION)
#error "Mcu_ECM_Irq.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (MCU_ECM_OPERATION == STD_ON)
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name      : MCU_FEINT_ISR
**
** Service ID         : None
**
** Description        : Interrupt service routine for ECM NMI(FEINT)
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpConfigPtr, Mcu_GblRAMInitStatus
**
** Functions Invoked  : MCU_DEM_REPORT_ERROR, ECM notification function
**
** Registers Used     : ECMMESSTR0, ECMESSTC0, ECMMESSTR1, ECMESSTC1, MCU_FEINTF0, MCU_FEINTF1, MCU_FEINTF2,
**                      MCU_FEINTF3, MCU_FEINTC0, MCU_FEINTC1, MCU_FEINTC2, MCU_FEINTC3, MCU_FEINTC4, MCU_FEINTC5,
**                      ECMKCPROT
**
** Reference ID       : MCU_DUD_ACT_035, MCU_DUD_ACT_035_ERR001, MCU_DUD_ACT_035_GBL001,
** Reference ID       : MCU_DUD_ACT_035_REG001, MCU_DUD_ACT_035_REG002,
** Reference ID       : MCU_DUD_ACT_035_REG003, MCU_DUD_ACT_035_REG004
***********************************************************************************************************************/
#if (MCU_FEINT_ISR_API == STD_ON)
#define MCU_START_SEC_CODE_FAST
#include "Mcu_MemMap.h"
/* Defines the CAT2 interrupt mapping */
#if defined(Os_MCU_FEINT_CAT2_ISR) || (MCU_ISR_CATEGORY_2 == STD_ON)
ISR(MCU_FEINT_CAT2_ISR)                                                                                                 /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_FE_ FUNC(void, MCU_CODE_FAST) MCU_FEINT_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif /* defined(Os_MCU_FEINT_CAT2_ISR) || (MCU_ISR_CATEGORY_2 == STD_ON) */
{
  P2FUNC(void, AUTOMATIC, LpFeiNotifyFuncPtr)(uint16 LusEcmNotificationErrorNumber);                                    /* PRQA S 3432 # JV-01 */
  P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_CONST) LpEcmSetting;
  P2CONST(volatile Mcu_EcmHwInfoType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmHwInfo;
  P2CONST(Mcu_EcmFEINTRegType, MCU_CONST, MCU_CONFIG_CONST) LpEcmFEINTRegsAddr;
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmStatusRegAddr;                                                /* PRQA S 3678 # JV-01 */
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmStatusClearRegAddr;
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmFEINTCRegAddr;
  #if (MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  uint32 LulFEINTstatus;
  #endif /* MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON */
  uint32 LulEcmStatusData;
  uint16 LusEcmNotificationErrorNumber;
  uint8 LucCount;
  uint8 LucEcmCount;
  uint8 LucPeNum;

  /* Initialize the local variable */
  LusEcmNotificationErrorNumber = (uint16)MCU_ZERO;
  LulEcmStatusData = MCU_LONG_WORD_ZERO;                                                                                /* PRQA S 2982 # JV-01 */
  /* Get the pointer to FE notification callback function */
  LpFeiNotifyFuncPtr = Mcu_GpConfigPtr->pFeintNotificationPtr;
  /* Get the address to ECM configuration structure  */
  LpEcmSetting = (P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_CONST))(Mcu_GpConfigPtr->pEcmSetting);              /* PRQA S 0316 # JV-01 */
  LpEcmHwInfo = (P2CONST(Mcu_EcmHwInfoType, AUTOMATIC, MCU_CONFIG_DATA)) (Mcu_GpConfigPtr->pEcmHwInfo);                 /* PRQA S 0316 # JV-01 */

  if (NULL_PTR != LpEcmHwInfo->pFIBD0Reg)
  {
    /* Get the pointer to FEINTF register address */
    LpEcmFEINTRegsAddr = LpEcmSetting->pEcmFEINTRegsAddr;
    /* Get the PE number */
    LucPeNum = (uint8)(*LpEcmHwInfo->pFIBD0Reg & MCU_ECM_FIBD0_PEID_MASK);                                              /* PRQA S 0404 # JV-01 */

    #if (MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
    /* Get FE interrupt flag for the approriate core */
    LulFEINTstatus = *LpEcmFEINTRegsAddr[LucPeNum].pFEINTFReg & MCU_ECM_INT_MASK_FE_VALUE;
    #endif /* MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON */

    /* Set FEINTC register address */
    LpEcmFEINTCRegAddr = LpEcmFEINTRegsAddr[LucPeNum].pFEINTCReg;
  }
  else
  {
    LucPeNum = MCU_ZERO;
    #if (MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
    LulFEINTstatus = MCU_ECM_INT_MASK_FE_VALUE;
    #endif /* MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON */
  }

  /* ECM Interrupt consistency check */
  #if (MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Interrupt status not found */
  if (MCU_ECM_INT_MASK_FE_VALUE != LulFEINTstatus)
  {
    #if defined(MCU_E_ECM_INT_INCONSISTENT)
    MCU_DEM_REPORT_ERROR(MCU_E_ECM_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
    #endif /* defined(MCU_E_ECM_INT_INCONSISTENT) */
  }
  else
  {
  #endif /* MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON */
    if (NULL_PTR != LpEcmHwInfo->pFIBD0Reg)
    {
      /* Clear the FE interrupt flag */
      *LpEcmFEINTCRegAddr = MCU_ECM_INT_MASK_FE_VALUE;                                                                  /* PRQA S 2962 # JV-01 */
    } /* else No action is required */

    /* Set ECMMESSTR0 register address */
    LpEcmStatusRegAddr = LpEcmHwInfo->pECMMESSTR0Reg;
    /* Set ECMESSTC0 register address */
    LpEcmStatusClearRegAddr = LpEcmHwInfo->pECMESSTC0Reg;
    /* Check ECMMESSTR0..j */
    for (LucEcmCount = MCU_ZERO; LucEcmCount < MCU_ECM_COMMON_REG_NUM; LucEcmCount++)
    {
      /* Get the ECM error status data value of interrupt */
      LulEcmStatusData = (*LpEcmStatusRegAddr & (LpEcmSetting->aaEcmFEIntTypeSettingValue[LucPeNum][LucEcmCount]));

      for (LucCount = MCU_ZERO; LucCount < MCU_THIRTYTWO; LucCount++)
      {
        /* Find the  notification index for the particular ecm source.
         * Step1.Find the total number of configured ecm error sources for MI upto this current source.
         * Step2.Find the notification index for current ecm source = "value in step1- MCU_ONE"
         */

        /* When Check DCLS error */
        if ((MCU_ZERO == MCU_ECM_STATUS_REG_SIZE) && (MCU_ZERO == LucEcmCount) && (LucCount < MCU_SIXTEEN))             /* PRQA S 2992 # JV-01 */
        {
          /* LucCount is even value (0,2,4,6,8,10,12,14) */
          if (MCU_ZERO == (uint8)(LucCount & MCU_EVEN_ODD_MASK))                                                        /* PRQA S 2880 # JV-01 */
          {
            /* Notify index should check 2bit */
            if (MCU_LONG_WORD_ZERO !=
                                  (((LpEcmSetting->aaEcmFEIntSettingValue[MCU_ZERO][MCU_LONG_WORD_ZERO]) >> LucCount) &
                                    MCU_ECM_DCLS_ERROR_FACTOR_MASK))
            {
              /* In case ECM error number in range 0..7 */
              /* Calculate the ECM Error number */
              LusEcmNotificationErrorNumber = (uint16)(LucCount / MCU_TWO);                                             /* PRQA S 4391 # JV-01 */
            } /* else No action required */
          } /* else No action required */
        }
        else if (MCU_LONG_WORD_ONE ==                                                                                   /* PRQA S 2004 # JV-01 */
          (((LpEcmSetting->aaEcmFEIntSettingValue[LucPeNum][LucEcmCount]) >> LucCount) & MCU_LONG_WORD_ONE))
        {
         /* Calculate the ECM Error number */
          if (MCU_ZERO == MCU_ECM_STATUS_REG_SIZE)                                                                      /* PRQA S 2742 # JV-01 */
          {
            if (MCU_ZERO == LucEcmCount)                                                                                /* PRQA S 2880 # JV-01 */
            {
              /* In case ECM error number in range 8..23 */
              /* Calculate the ECM Error number */
              LusEcmNotificationErrorNumber = (uint16)(LucCount - MCU_EIGHT);                                           /* PRQA S 4391 # JV-01 */
            }
            else
            {
              /* In case ECM error number */
              /* Calculate the ECM Error number */
              LusEcmNotificationErrorNumber =
                  (uint16)(((LucEcmCount - MCU_ONE) * MCU_ECM_STATUS_REG_SIZE) + MCU_TWENTYFOUR + LucCount);            /* PRQA S 4391 # JV-01 */
            }
          }
          else
          {
            LusEcmNotificationErrorNumber = (uint16)((MCU_ECM_STATUS_REG_SIZE * LucEcmCount) + LucCount);               /* PRQA S 4391 # JV-01 */
          }
        } /* else No action required */

        /* Find which ECM error source caused this interrupt */
        if (MCU_LONG_WORD_ONE == ((LulEcmStatusData >> LucCount) & MCU_LONG_WORD_ONE))
        {
          /* Check whether notification function  configured or not */
          if (NULL_PTR != LpFeiNotifyFuncPtr)
          {
            /* Invoke the configured notification function */
            LpFeiNotifyFuncPtr((uint16)LusEcmNotificationErrorNumber);
          } /* else No action required */

          /* Release Register Access Protection */
          *LpEcmHwInfo->pECMKCPROTReg = MCU_ECM_DISABLE_REG_PROTECT_VALUE;

          /* Clear status for ECM interrupt */
          *LpEcmStatusClearRegAddr = (uint32)(MCU_LONG_WORD_ONE << (uint32)LucCount);

          /* Hold Register Access protection */
          *LpEcmHwInfo->pECMKCPROTReg = MCU_ECM_ENABLE_REG_PROTECT_VALUE;

          #if ((MCU_GET_RAM_STATE_API == STD_ON) && (MCU_PROVIDE_RAM_STATE_ISR == STD_ON))
          /* Check LRAM and CRAM errors */
          if (MCU_LONG_WORD_ZERO != (LulEcmStatusData & LpEcmSetting->aaEcmRamErrMask[LucEcmCount]))
          {
            /* Set the value of RAM errors */
            Mcu_GblRAMInitStatus = MCU_RAMSTATE_INVALID;
          } /* else No action required */
          #endif /* (MCU_GET_RAM_STATE_API == STD_ON) && (MCU_PROVIDE_RAM_STATE_ISR == STD_ON) */
        } /* else No action required */
      }
      /* Increment the value of index */
      LpEcmStatusRegAddr++;
      LpEcmStatusClearRegAddr++;
    }
  #if (MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  }
  #endif /* MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON */
  return;
}
#define MCU_STOP_SEC_CODE_FAST
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_FEINT_ISR_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : MCU_ECM_EIC9_ISR
**
** Service ID         : None
**
** Description        : Interrupt service routine for ECM EIC9 INT
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpConfigPtr
**
** Functions Invoked  : MCU_DEM_REPORT_ERROR, ECM notification function
**
** Registers Used     : ECMMESSTRn, ECMMICFGn, ECMMESSTRj, IMR0, ECMCESSTRj, ECMESSTCn, ECMESSTCj, ECMKCPROT.
**
** Reference ID       : MCU_DUD_ACT_036, MCU_DUD_ACT_036_ERR001, MCU_DUD_ACT_036_REG001,
** Reference ID       : MCU_DUD_ACT_036_REG002, MCU_DUD_ACT_036_REG003
***********************************************************************************************************************/
#if (MCU_EIINT_EIC9_ISR_API == STD_ON)
#define MCU_START_SEC_CODE_FAST
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_MCU_ECM_EIC9_CAT2_ISR) || (MCU_ISR_CATEGORY_2 == STD_ON)
ISR(MCU_ECM_EIC9_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, MCU_CODE_FAST) MCU_ECM_EIC9_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif /* defined(Os_MCU_ECM_EIC9_CAT2_ISR) || (MCU_ISR_CATEGORY_2 == STD_ON) */
{
  P2FUNC(void, AUTOMATIC, LpEiDCLSNotifyFuncPtr)(uint16 LusEcmNotificationErrorNumber);                                 /* PRQA S 3432 # JV-01 */
  P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_CONST) LpEcmSetting;
  P2CONST(volatile Mcu_EcmHwInfoType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmHwInfo;
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmStatusClearRegAddr;
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmStatusRegAddr;                                                /* PRQA S 3678 # JV-01 */
  uint32 LulEcmStatusData;
  uint16 LusEcmNotificationErrorNumber;
  uint8 LucCount;
  uint8 LucEcmCount;
  uint8 LucPeNum;

  /* Initialize the local variable */
  LulEcmStatusData = MCU_LONG_WORD_ZERO;                                                                                /* PRQA S 2982 # JV-01 */
  /* Get the pointer to EI DCLS notification callback function */
  LpEiDCLSNotifyFuncPtr = Mcu_GpConfigPtr->pEiintDCLSNotificationPtr;
  /* Get the address to ECM configuration structure  */
  LpEcmSetting = (P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_CONST))(Mcu_GpConfigPtr->pEcmSetting);              /* PRQA S 0316 # JV-01 */
  LpEcmHwInfo = (P2CONST(Mcu_EcmHwInfoType, MCU_CONST, MCU_CONFIG_DATA)) (Mcu_GpConfigPtr->pEcmHwInfo);                 /* PRQA S 0316 # JV-01 */
  /* Get the PE number */
  LucPeNum = (uint8)(*LpEcmHwInfo->pEIBD9Reg & MCU_ECM_EIBD9_PEID_MASK);                                                /* PRQA S 0404 # JV-01 */

  /* ECM Interrupt consistency check */
  #if (MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Interrupt status not found */
  if (MCU_LONG_WORD_ZERO != (*LpEcmHwInfo->pIMR0Reg & MCU_ECM_INT_MASK_EIC9_VALUE))                                     /* PRQA S 0404 # JV-01 */
  {
    #ifdef MCU_E_ECM_INT_INCONSISTENT
    MCU_DEM_REPORT_ERROR(MCU_E_ECM_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
    #endif /* MCU_E_ECM_INT_INCONSISTENT */
  }
  else
  {
  #endif /* MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON */
    /* Set ECMMESSTR0 register address */
    LpEcmStatusRegAddr = LpEcmHwInfo->pECMMESSTR0Reg;
    /* Set ECMESSTC0 register address */
    LpEcmStatusClearRegAddr = LpEcmHwInfo->pECMESSTC0Reg;
    /* Check ECMMESSTR0..j */
    for (LucEcmCount = MCU_ZERO; LucEcmCount < MCU_ECM_COMMON_REG_NUM_EIC9; LucEcmCount++)
    {
      /* Get the value of ECM error status data of maskable interrupt */
      LulEcmStatusData = (*LpEcmStatusRegAddr & (LpEcmSetting->aaEcmEIC9IntTypeSettingValue[LucPeNum][LucEcmCount]));   /* PRQA S 2841 # JV-01 */

      for (LucCount = MCU_ZERO; LucCount < MCU_ECM_EIC9_REG_NUM; LucCount += MCU_ECM_EIC9_UNIT_NUM)
      {
        /* Find the notification index for the particular ecm source.
        * Step1.Find the total number of configured ecm error sources for MI upto this current source.
        * Step2.Find the notification index for current ecm source = "value in step1- MCU_ONE"
        */
        if (MCU_LONG_WORD_ZERO !=
       (((LpEcmSetting->aaEcmEIC9IntSettingValue[LucPeNum][LucEcmCount]) >> LucCount) & MCU_ECM_DCLS_ERROR_FACTOR_MASK))/* PRQA S 2841 # JV-01 */
        {
          /* Calculate the error number */
          LusEcmNotificationErrorNumber =
                    (uint16)(((MCU_ECM_STATUS_REG_SIZE * LucEcmCount) + LucCount) / MCU_ECM_STATUS_REG_DIV);            /* PRQA S 4391 # JV-01 */
        } /* else No action required */

        /* Find which ECM error source caused this interrupt */
        if (MCU_LONG_WORD_ZERO != ((LulEcmStatusData >> LucCount) & MCU_ECM_DCLS_ERROR_FACTOR_MASK))
        {
          /* Check whether notification function configured or not */
          if (NULL_PTR != LpEiDCLSNotifyFuncPtr)
          {
            /* Invoke the configured notification function */
            LpEiDCLSNotifyFuncPtr((uint16)LusEcmNotificationErrorNumber);                                               /* PRQA S 2962 # JV-01 */
          } /* else No action required */

          /* Release Register Access Protection */
          *LpEcmHwInfo->pECMKCPROTReg = MCU_ECM_DISABLE_REG_PROTECT_VALUE;

          /* Clear status for ECM interrupt */
          *LpEcmStatusClearRegAddr = (uint32)(MCU_ECM_DCLS_ERROR_FACTOR_MASK << (uint32)LucCount);

          /* Hold Register Access protection */
          *LpEcmHwInfo->pECMKCPROTReg = MCU_ECM_ENABLE_REG_PROTECT_VALUE;
        } /* else No action required */
      /* Increment the value of index */
      }
      /* Increment the value of index */
      LpEcmStatusRegAddr++;
      LpEcmStatusClearRegAddr++;
    }
  #if (MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  }
  #endif /* MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON */
  return;
}
#define MCU_STOP_SEC_CODE_FAST
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* MCU_EIINT_EIC9_ISR_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : MCU_ECM_EIC8_ISR
**
** Service ID         : None
**
** Description        : Interrupt service routine for ECM EIC8 INT
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpConfigPtr, Mcu_GblRAMInitStatus
**
** Functions Invoked  : MCU_DEM_REPORT_ERROR, ECM notification function
**
** Registers Used     : ECMMESSTRn, ECMMICFGn, ECMMESSTRj, IMR0, ECMCESSTRj, ECMESSTCn, ECMESSTCj, ECMKCPROT.
**
** Reference ID       : MCU_DUD_ACT_037, MCU_DUD_ACT_037_ERR001,
** Reference ID       : MCU_DUD_ACT_037_GBL001, MCU_DUD_ACT_037_REG001, 
** Reference ID       : MCU_DUD_ACT_037_REG002, MCU_DUD_ACT_037_REG003
***********************************************************************************************************************/
#if (MCU_EIINT_EIC8_ISR_API == STD_ON)
#define MCU_START_SEC_CODE_FAST
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* Defines the CAT2 interrupt mapping */
#if defined(Os_MCU_ECM_EIC8_CAT2_ISR) || (MCU_ISR_CATEGORY_2 == STD_ON)
ISR(MCU_ECM_EIC8_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, MCU_CODE_FAST) MCU_ECM_EIC8_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif /* defined(Os_MCU_ECM_EIC8_CAT2_ISR) || (MCU_ISR_CATEGORY_2 == STD_ON) */
{
  P2FUNC(void, AUTOMATIC, LpEiNotifyFuncPtr)(uint16 LusEcmNotificationErrorNumber);                                     /* PRQA S 3432 # JV-01 */
  P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_CONST) LpEcmSetting;
  P2CONST(volatile Mcu_EcmHwInfoType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmHwInfo;
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmStatusRegAddr;                                                /* PRQA S 3678 # JV-01 */
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmStatusClearRegAddr;
  uint32 LulEcmStatusData;
  uint16 LusEcmNotificationErrorNumber;
  uint8 LucCount;
  uint8 LucEcmCount;
  uint8 LucPeNum;

  /* Initialize the local variable */
  LulEcmStatusData = MCU_LONG_WORD_ZERO;                                                                                /* PRQA S 2982 # JV-01 */

  /* Get the pointer to EI notification callback function */
  LpEiNotifyFuncPtr = Mcu_GpConfigPtr->pEiintNotificationPtr;

  /* Get the address to ECM configuration structure  */
  LpEcmSetting = (P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_CONST))(Mcu_GpConfigPtr->pEcmSetting);              /* PRQA S 0316 # JV-01 */
  LpEcmHwInfo = (P2CONST(Mcu_EcmHwInfoType, MCU_CONST, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pEcmHwInfo;                    /* PRQA S 0316 # JV-01 */

  /* Get the PE number */
  LucPeNum = (uint8)(*LpEcmHwInfo->pEIBD8Reg & MCU_ECM_EIBD8_PEID_MASK);                                                /* PRQA S 0404 # JV-01 */

  /* ECM Interrupt consistency check */
  #if (MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Interrupt status not found */
  if (MCU_LONG_WORD_ZERO != (*LpEcmHwInfo->pIMR0Reg & MCU_ECM_INT_MASK_EIC8_VALUE))                                     /* PRQA S 0404 # JV-01 */
  {
    #ifdef MCU_E_ECM_INT_INCONSISTENT
    MCU_DEM_REPORT_ERROR(MCU_E_ECM_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
    #endif /* MCU_E_ECM_INT_INCONSISTENT */
  }
  else
  {
  #endif /* MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON */
    /* Set ECMMESSTR0 register address */
    LpEcmStatusRegAddr = LpEcmHwInfo->pECMMESSTR0Reg;
    /* Set ECMESSTC0 register address */
    LpEcmStatusClearRegAddr = LpEcmHwInfo->pECMESSTC0Reg;
    /* Check ECMMESSTR0..j */
    for (LucEcmCount = MCU_ZERO; LucEcmCount < MCU_ECM_COMMON_REG_NUM; LucEcmCount++)
    {
      /* Get the value of ECM error status data of maskable interrupt */
      LulEcmStatusData = (*LpEcmStatusRegAddr & (LpEcmSetting->aaEcmEIC8IntTypeSettingValue[LucPeNum][LucEcmCount]));

      for (LucCount = MCU_ZERO; LucCount < MCU_THIRTYTWO; LucCount++)
      {
        /* Find the notification index for the particular ecm source.
        * Step1.Find the total number of configured ecm error sources for MI upto this current source.
        * Step2.Find the notification index for current ecm source = "value in step1- MCU_ONE"
        */
        /* When Check DCLS error */
        if ((MCU_LONG_WORD_ZERO != MCU_ECM_ESSTR_DCLS_MASK) && (MCU_ZERO == LucEcmCount) && (LucCount < MCU_SIXTEEN))   /* PRQA S 2992 # JV-01 */
        {
          /* LucCount is even value (0,2,4,6,8,10,12,14) */
          if (MCU_ZERO == (uint8)(LucCount & MCU_EVEN_ODD_MASK))                                                        /* PRQA S 2880 # JV-01 */
          {
            /* Notify index should check 2bit */
            if (MCU_LONG_WORD_ZERO != (((LpEcmSetting->aaEcmEIC8IntSettingValue[LucPeNum][MCU_ZERO]) >> LucCount) &
                                       MCU_ECM_DCLS_ERROR_FACTOR_MASK))
            {
              /* Calculate ECM error number */
              LusEcmNotificationErrorNumber = (uint16)(LucCount / MCU_TWO);                                             /* PRQA S 4391 # JV-01 */
            } /* else No action required */
          } /* else No action required */
        }
        else if (MCU_LONG_WORD_ONE ==                                                                                   /* PRQA S 2004 # JV-01 */
                 (((LpEcmSetting->aaEcmEIC8IntSettingValue[LucPeNum][LucEcmCount]) >> LucCount) & MCU_LONG_WORD_ONE))
        {
          if(MCU_LONG_WORD_ZERO != MCU_ECM_ESSTR_DCLS_MASK)                                                             /* PRQA S 2742 # JV-01 */
          {
            if (MCU_ZERO == LucEcmCount)                                                                                /* PRQA S 2880 # JV-01 */
            {
              /* In case ECM error number in range 8..23 */
              /* Calculate the ECM Error number */
              LusEcmNotificationErrorNumber = (uint16)(LucCount - MCU_EIGHT);                                           /* PRQA S 4391 # JV-01 */
            }
            else /* MCU_ZERO != LucEcmCount */
            {
              /* In case ECM error number */
              /* Calculate the ECM Error number */
              LusEcmNotificationErrorNumber =
                  (uint16)(((LucEcmCount - MCU_ONE) * MCU_ECM_STATUS_REG_SIZE) + MCU_TWENTYFOUR + LucCount);            /* PRQA S 4391 # JV-01 */
            }
          }
          else
          {
            LusEcmNotificationErrorNumber = (uint16)((MCU_ECM_STATUS_REG_SIZE * LucEcmCount) + LucCount);               /* PRQA S 4391 # JV-01 */
          }
        } /* else No action required */

        /* Find which ECM error source caused this interrupt */
        if (MCU_LONG_WORD_ONE == ((LulEcmStatusData >> LucCount) & MCU_LONG_WORD_ONE))
        {
          /* Check whether notification function configured or not */
          if (NULL_PTR != LpEiNotifyFuncPtr)
          {
            /* Invoke the configured notification function */
            LpEiNotifyFuncPtr((uint16)LusEcmNotificationErrorNumber);                                                   /* PRQA S 2962 # JV-01 */
          } /* else No action required */

          /* Release Register Access Protection */
          *LpEcmHwInfo->pECMKCPROTReg = MCU_ECM_DISABLE_REG_PROTECT_VALUE;

          /* Clear status for ECM interrupt */
          *LpEcmStatusClearRegAddr = (uint32)(MCU_LONG_WORD_ONE << (uint32)LucCount);

          /* Hold Register Access protection */
          *LpEcmHwInfo->pECMKCPROTReg = MCU_ECM_ENABLE_REG_PROTECT_VALUE;

          #if ((MCU_GET_RAM_STATE_API == STD_ON) && (MCU_PROVIDE_RAM_STATE_ISR == STD_ON))
          /* Check LRAM and CRAM errors */
          if (MCU_LONG_WORD_ZERO != (LulEcmStatusData & LpEcmSetting->aaEcmRamErrMask[LucEcmCount]))
          {
            /* Set the value of RAM errors */
            Mcu_GblRAMInitStatus = MCU_RAMSTATE_INVALID;
          } /* else No action required */
          #endif /* (MCU_GET_RAM_STATE_API == STD_ON) && (MCU_PROVIDE_RAM_STATE_ISR == STD_ON) */
        } /* else No action required */
      }
      /* Increment the value of index */
      LpEcmStatusRegAddr++;
      LpEcmStatusClearRegAddr++;
    }
  #if (MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  }
  #endif /* MCU_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON */
  return;
}
#define MCU_STOP_SEC_CODE_FAST
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* MCU_EIINT_EIC8_ISR_API == STD_ON */
#endif /* End of (MCU_ECM_OPERATION == STD_ON) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
