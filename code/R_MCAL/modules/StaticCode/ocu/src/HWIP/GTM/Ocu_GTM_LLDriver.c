/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Ocu_GTM_LLDriver.c                                                                                  */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.                                                     */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of OCU Driver                                                                         */
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
/*                                              Devices:       X2x                                                    */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.4.0: 30/05/2025 : Initial Version.
 * 1.4.1: 30/06/2025 : Move reset of pGTM_IRQ_SELxy from Ocu_HW_Gtm_DisableInterrupt to channel init, deinit
 *                     Fix issue when setting new threshold = 0 while output is disabled
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included Ocu_GTM_LLDriver header */
#include "Ocu_GTM_LLDriver.h"
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : MISRA C:2012 Rule-11.3, CERTCCM EXP39, EXP11, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588,   */
/*                       CWE-465, CWE-569, CWE-737                                                                    */
/* JV-01 Justification : For accessing 8-bit and 16-bit PNOT and JPNOT register respectively, the 32-bit pointer is   */
/*                       typecasted.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:0312)    : Dangerous pointer cast results in loss of volatile qualification.                            */
/* Rule                : MISRA C:2012 Rule-11.8, CERTCCM EXP32, CWE Rule CWE-737                                      */
/* JV-01 Justification : According to the coding guide, all global variables must have volatile attribute, but        */
/*                       volatile must be removed when return these variables from APIs according to the AUTOSAR      */
/*                       specification.                                                                               */
/*       Verification  : Since these are normal memory objects, any problem doesn't occurs.                           */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0317)    : Implicit conversion from a pointer to void to a pointer to object type.                      */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : This is done as per implementation requirement.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact               */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0499)    : Right operand of shift operator is greater than or equal to the width of the essential type  */
/*                       of the left operand.                                                                         */
/* Rule                : MISRA C:2012 Rule-12.2, CERTCCM INT34, CWE Rule CWE-681, CWE-682, CWE-738                    */
/* JV-01 Justification : The result has been ensured by casting to the same Type                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP39, EXP11, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : This in-line assembler construct is a language extension. The code has been ignored.         */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTCCM MSC14                                       */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : MISRA C:2012 Rule-8.7, CERTCCM DCL19, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : MISRA C:2012 Rule-15.7, CERTCCM MSC01, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563,     */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3, CWE Rule CWE-398, CWE-569                                              */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifiers. There is no impact on the functionality    */
/*                       due to this conditional check for mode change.                                               */
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
**                                                Version Information                                                 **
***********************************************************************************************************************/
#if(OCU_TIMER_IP_GTM == STD_ON)
/* AUTOSAR release version information */
#define OCU_GTM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define OCU_GTM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION_VALUE
#define OCU_GTM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION_VALUE
/* Module software version information */
#define OCU_GTM_LLDRIVER_C_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION_VALUE
#define OCU_GTM_LLDRIVER_C_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION_VALUE
#define OCU_GTM_LLDRIVER_C_SW_PATCH_VERSION            OCU_SW_PATCH_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (OCU_GTM_LLDRIVER_AR_RELEASE_MAJOR_VERSION != OCU_GTM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Ocu_GTM_LLDriver.c : Mismatch in Release Major Version"
#endif
#if (OCU_GTM_LLDRIVER_AR_RELEASE_MINOR_VERSION != OCU_GTM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Ocu_GTM_LLDriver.c : Mismatch in Release Minor Version"
#endif
#if (OCU_GTM_LLDRIVER_AR_RELEASE_REVISION_VERSION != OCU_GTM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Ocu_GTM_LLDriver.c : Mismatch in Release Revision Version"
#endif
#if (OCU_GTM_LLDRIVER_SW_MAJOR_VERSION != OCU_GTM_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Ocu_GTM_LLDriver.c : Mismatch in Software Major Version"
#endif
#if (OCU_GTM_LLDRIVER_SW_MINOR_VERSION != OCU_GTM_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Ocu_GTM_LLDriver.c : Mismatch in Software Minor Version"
#endif
#if (OCU_GTM_LLDRIVER_SW_PATCH_VERSION != OCU_GTM_LLDRIVER_C_SW_PATCH_VERSION)
  #error "Ocu_GTM_LLDriver.c : Mismatch in Software Patch Version"
#endif
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_AtomTbuInit
**
** Description           : This function loops through all configured timer units, assigns the global
**                         pointer to the first unit configuration, and sets up the TBU channels based on the
**                         configuration provided.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LpConfigPtr
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GaaHWIP, Ocu_GpGtmTbuUnitConfig
**
** Functions invoked     : None
**
** Registers used        : TBUCHEN, TBU0BASE, TBU0CTRL, TBU1BASE, TBU1CTRL, TBU2BASE, TBU2CTRL
**
** Reference ID          : OCU_DUD_ACT_067, OCU_DUD_ACT_067_REG007
** Reference ID          : OCU_DUD_ACT_067_REG001, OCU_DUD_ACT_067_REG002, OCU_DUD_ACT_067_REG003,
** Reference ID          : OCU_DUD_ACT_067_REG004, OCU_DUD_ACT_067_REG005, OCU_DUD_ACT_067_REG006,
***********************************************************************************************************************/
#if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_AtomTbuInit(P2CONST(Ocu_ConfigType, AUTOMATIC, OCU_APPL_CONST) LpConfigPtr)
{
  /* Local Pointer used for TBU unit setting */
  P2VAR(Ocu_GTMTbuChannelRegs, AUTOMATIC, REGSPACE) LpTbuChRegs;                                                        /* PRQA S 3432 # JV-01 */
  /* Local variable for loop count */
  uint8 LucCount;
  /* Local variable to hold the enable channel value */
  uint32 LulEnableChannel;
  
  /* Initialize the enable channel variable to zero */
  LulEnableChannel = OCU_DOUBLE_ZERO;
  
  /* Loop through all configured timer units */
  for (LucCount = OCU_ZERO; LucCount < OCU_TOTAL_HW_IP_CONFIG; LucCount++)
  {
    /* If the current HW IP index matches GTM */
    if (OCU_HWIP_GTM == Ocu_GaaHWIP[LucCount].ucIndex)
    {
      /* Assign the global pointer to the first Unit Configuration */
      Ocu_GpGtmTbuUnitConfig = 
          (P2CONST(Ocu_GtmTbuUnitConfigType, OCU_VAR_INIT, OCU_CONFIG_DATA))LpConfigPtr->aaTimerUnitConfig[LucCount];   /* PRQA S 0316 # JV-01 */
    } /* If not GTM, no action required */
  }

  /* Update TBU channel pointer to the address from the first unit configuration */
  LpTbuChRegs = (P2VAR(Ocu_GTMTbuChannelRegs, AUTOMATIC, REGSPACE)) Ocu_GpGtmTbuUnitConfig[OCU_ZERO].pTBUCHENRegs;      /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */

  /* TBU0 setting */
  if (OCU_TBU_CHANNEL_NO_CONFIG != Ocu_GpGtmTbuUnitConfig[OCU_ZERO].ulTBU0CTRLValue)
  {
    /* Set the TBU0 clock selector value */
    LpTbuChRegs->ulTBU0CTRL = Ocu_GpGtmTbuUnitConfig[OCU_ZERO].ulTBU0CTRLValue;
    /* Set the base value for TBU0 */
    LpTbuChRegs->ulTBU0BASE = OCU_DOUBLE_ZERO;
    /* Enable and start the TBU0 counter */
    LulEnableChannel |= OCU_TBU0_CHANNEL_ENABLE;
  } /* Else block, no action needed if TBU0 is not configured */

  /* TBU1 setting */
  if (OCU_TBU_CHANNEL_NO_CONFIG != Ocu_GpGtmTbuUnitConfig[OCU_ZERO].ulTBU1CTRLValue)
  {
    /* Set the TBU1 clock selector value */
    LpTbuChRegs->ulTBU1CTRL = Ocu_GpGtmTbuUnitConfig[OCU_ZERO].ulTBU1CTRLValue;
    /* Set the base value for TBU1 */
    LpTbuChRegs->ulTBU1BASE = OCU_DOUBLE_ZERO;
    /* Enable and start the TBU1 counter */
    LulEnableChannel |= OCU_TBU1_CHANNEL_ENABLE;
  } /* Else block, no action needed if TBU1 is not configured */

  /* TBU2 setting */
  if (OCU_TBU_CHANNEL_NO_CONFIG != Ocu_GpGtmTbuUnitConfig[OCU_ZERO].ulTBU2CTRLValue)
  {
    /* Set the TBU2 clock selector value */
    LpTbuChRegs->ulTBU2CTRL = Ocu_GpGtmTbuUnitConfig[OCU_ZERO].ulTBU2CTRLValue;
    /* Set the base value for TBU2 */
    LpTbuChRegs->ulTBU2BASE = OCU_DOUBLE_ZERO;
    /* Enable and start the TBU2 counter */
    LulEnableChannel |= OCU_TBU2_CHANNEL_ENABLE;
  } /* Else block, no action needed if TBU2 is not configured */
  
  /* Enable all configured TBU channels */
  LpTbuChRegs->ulTBUCHEN = LulEnableChannel;
} /* End of Ocu_HW_Gtm_AtomTbuInit function */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of TBU timer setting */

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_UnitDeInit
**
** Description           : This function resets up the TBU channels based on the configuration provided.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpGtmTbuUnitConfig
**
** Functions invoked     : None
**
** Registers used        : TBUCHEN, TBU0CTRL, TBU1CTRL, TBU2CTRL
**
** Reference ID          : OCU_DUD_ACT_068_REG001, OCU_DUD_ACT_068_REG002, OCU_DUD_ACT_068_REG003,
** Reference ID          : OCU_DUD_ACT_068_REG004, OCU_DUD_ACT_068
***********************************************************************************************************************/
#if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON) && (OCU_DE_INIT_API == STD_ON)
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Function to de-initialize the GTM TBU unit */
FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_UnitDeInit(void)
{
  /* Local Pointer used for ATOM Channel control registers */
  P2VAR(Ocu_GTMTbuChannelRegs, AUTOMATIC, REGSPACE) LpTbuChRegs;                                                        /* PRQA S 3432 # JV-01 */
  /* Update TBU channel pointer address */
  LpTbuChRegs = (P2VAR(Ocu_GTMTbuChannelRegs, AUTOMATIC, REGSPACE)) Ocu_GpGtmTbuUnitConfig[OCU_ZERO].pTBUCHENRegs;      /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */

  /* De-initialize TBU0 if it is configured */
  /* TBU0 setting */
  if (OCU_TBU_CHANNEL_NO_CONFIG != Ocu_GpGtmTbuUnitConfig[OCU_ZERO].ulTBU0CTRLValue)
  {
    /* Reset the TBU0 clock select */
    LpTbuChRegs->ulTBU0CTRL = OCU_DOUBLE_ZERO;
    /* Stop the TBU0 counter */
    LpTbuChRegs->ulTBUCHEN = ~OCU_TBU0_CHANNEL_ENABLE;
  } /* Else no action */
  
  /* De-initialize TBU1 if it is configured */
  /* TBU1 setting */
  if (OCU_TBU_CHANNEL_NO_CONFIG != Ocu_GpGtmTbuUnitConfig[OCU_ZERO].ulTBU1CTRLValue)
  {
    /* Reset the TBU1 clock select */
    LpTbuChRegs->ulTBU1CTRL = OCU_DOUBLE_ZERO;
    /* Stop the TBU1 counter */
    LpTbuChRegs->ulTBUCHEN = ~OCU_TBU1_CHANNEL_ENABLE;
  } /* Else no action */
  
  /* De-initialize TBU2 if it is configured */
  /* TBU2 setting */
  if (OCU_TBU_CHANNEL_NO_CONFIG != Ocu_GpGtmTbuUnitConfig[OCU_ZERO].ulTBU2CTRLValue)
  {
    /* Reset the TBU2 clock select */
    LpTbuChRegs->ulTBU2CTRL = OCU_DOUBLE_ZERO;
    /* Stop the TBU2 counter */
    LpTbuChRegs->ulTBUCHEN = ~OCU_TBU2_CHANNEL_ENABLE;
  } /* Else no action */
} /* End of Internal function Ocu_HW_Gtm_UnitInit */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of TBU timer setting */

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_ChannelInit
**
** Description           : Initializes the specified OCU GTM (ATOM/TOM) channel
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LddChannel - The channel to be initialized
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GpChannelRamData, Ocu_GblCountingDirection
**
** Functions invoked     : RH850_SV_SET_ICR_SYNCP, Ocu_HW_Gtm_DisableInterrupt
**
** Registers used        : AGCGLBCTRL, TGCGLBCTRL, CHxCTRLSR, CHxCTRL, AGCOUTENSTAT, CHxCM0, CHxCM1,
**                         CHxSR0, CHxSR1, CHxCN0, AGCENDISSTAT, EICn, TGCOUTENSTAT, TGCENDISSTAT
**
** Reference ID          : OCU_DUD_ACT_052_GBL001, OCU_DUD_ACT_052_GBL002, OCU_DUD_ACT_052_GBL003,
** Reference ID          : OCU_DUD_ACT_052_GBL004, OCU_DUD_ACT_052_GBL005, OCU_DUD_ACT_052_REG001,
** Reference ID          : OCU_DUD_ACT_052_REG002, OCU_DUD_ACT_052_REG003, OCU_DUD_ACT_052_REG004,
** Reference ID          : OCU_DUD_ACT_052_REG005, OCU_DUD_ACT_052_REG006, OCU_DUD_ACT_052_REG007,
** Reference ID          : OCU_DUD_ACT_052_REG008, OCU_DUD_ACT_052_REG009, OCU_DUD_ACT_052_REG010,
** Reference ID          : OCU_DUD_ACT_052_REG011, OCU_DUD_ACT_052_REG012, OCU_DUD_ACT_052_REG013,
** Reference ID          : OCU_DUD_ACT_052_REG014, OCU_DUD_ACT_052_REG015, OCU_DUD_ACT_052_REG016,
** Reference ID          : OCU_DUD_ACT_052_REG017, OCU_DUD_ACT_052_REG018, OCU_DUD_ACT_052_REG019,
** Reference ID          : OCU_DUD_ACT_052_REG020, OCU_DUD_ACT_052_REG021, OCU_DUD_ACT_052,
** Reference ID          : OCU_DUD_ACT_052_REG022
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_ChannelInit(Ocu_ChannelType LddChannel)                                         /* PRQA S 3006 # JV-01 */
{
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_GTMChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpGtmChannelConfig;
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpChannelConfig;
  P2VAR(Ocu_ChannelRamDataType, AUTOMATIC, OCU_CONFIG_DATA) LpRamData;                                                  /* PRQA S 3432 # JV-01 */
  #if (OCU_GTM_ATOM_USED == STD_ON)
  P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  P2VAR(Ocu_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  #if (OCU_GTM_TOM_USED == STD_ON)
  P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  P2VAR(Ocu_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  
  /* Variables for bit shifts and max count values */
  uint32 LulChShiftNum;
  uint32 LulMaxHWCouter;

  /* Get the current channel configuration */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  LpGtmChannelConfig = LpChannelConfig->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */
  LpRamData = &Ocu_GpChannelRamData[LddChannel];
  /* Calculate the bit shift and max counter values */
  LulChShiftNum = (uint32)(LpGtmChannelConfig->usChannelBitValue << OCU_ONE);                                           /* PRQA S 4391 # JV-01 */
  LulMaxHWCouter = (uint32)((LpChannelConfig->ulMaxCounterValue + (uint32)OCU_ONE) *                                    /* PRQA S 3383, 3384 # JV-01, JV-01 */
                            (uint32)LpChannelConfig->usChannelTickDuration);

  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  /* Initialize notification status to false */
  LpRamData->blNotifyStatus = OCU_FALSE;
  #endif

  /* Set initial channel status */
  LpRamData->blChannelStatus = OCU_CH_STOPPED;

  #if (OCU_SET_PIN_ACTION_API == STD_ON)
  /* Initialize pin action state */
  LpRamData->ddPinActionState = OCU_DISABLE;
  #endif

  /* No threshold value rewrite required initially */
  LpRamData->blRequireRewriteCountValue = OCU_FALSE;

  /* Set the initial HW threshold based on counting direction */
  if (OCU_UPCOUNTING == Ocu_GblCountingDirection)                                                                       /* PRQA S 3416 # JV-01 */
  {
    LpRamData->ddHwLastThreshold = (LpChannelConfig->ulDefaultThreshold) *                                              /* PRQA S 3384 # JV-01 */
                                   (uint32)(LpChannelConfig->usChannelTickDuration);
  }
  else /* OCU_DOWNCOUNTING */
  {
    LpRamData->ddHwLastThreshold = LulMaxHWCouter - ((LpChannelConfig->ulDefaultThreshold + (uint32)OCU_ONE) *          /* PRQA S 3383, 3384 # JV-01, JV-01 */
                                                                (uint32)(LpChannelConfig->usChannelTickDuration));
  }

  /* If ATOM channel */
  #if (OCU_GTM_ATOM_USED == STD_ON)
  if(OCU_HWIP_GTM_ATOM == LpGtmChannelConfig->ucGtmUnitType)
  {
    /* Get control registers for the ATOM channel and cluster */
    LpAtomChCntrlRegs = (P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;/* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    LpAtomClusterRegs = (P2VAR(Ocu_GTMAtomClusterRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomClusterRegs;/* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    /* Reset the GTM ATOM channel */
    LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((OCU_ONE << LpGtmChannelConfig->usChannelBitValue) << OCU_SHIFT_8);      /* PRQA S 0499, 4391 # JV-01, JV-01 */
    /* Load initial value into the channel control shadow register */
    LpAtomChCntrlRegs->ulCHxCTRLSR = LpGtmChannelConfig->ulCTRLRegValue & ~OCU_TOM_ATOM_CTRL_CLKSRC_MASK;
    /* Enable synchronous update the channel via the global control register */
    LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((OCU_TOM_ATOM_CTRL_ENABLE << OCU_SHIFT_16) << LulChShiftNum);
    /* Load control register value */
    LpAtomChCntrlRegs->ulCHxCTRL = LpGtmChannelConfig->ulCTRLRegValue;
    /* Enable the output */
    LpAtomClusterRegs->ulAGCOUTENSTAT = OCU_TOM_ATOM_CTRL_ENABLE << LulChShiftNum;
    /* Check if the output pin is not used */
    if(OCU_FALSE == LpChannelConfig->blOutputPinUsed)
    {
      /* Set compare value with max counter */
      LpAtomChCntrlRegs->ulCHxCM0 = LulMaxHWCouter;
      /* Set max value to prevent CCU1 event */
      LpAtomChCntrlRegs->ulCHxCM1 = OCU_ATOM_MAX_COUNTER_VALUE;
      /* Set compare value with max counter */
      LpAtomChCntrlRegs->ulCHxSR0 = LulMaxHWCouter;
      /* Set max value to prevent CCU1 event */
      LpAtomChCntrlRegs->ulCHxSR1 = OCU_ATOM_MAX_COUNTER_VALUE;
       /* Initialize counter */
      LpAtomChCntrlRegs->ulCHxCN0 = LulMaxHWCouter;
      /* Start the counter */
      LpAtomClusterRegs->ulAGCENDISSTAT = OCU_TOM_ATOM_CTRL_ENABLE << LulChShiftNum;
    } /* Else case no action required */
  }
  else
  #endif
  {
    #if (OCU_GTM_TOM_USED == STD_ON)
    /* Get control registers for the TOM channel and cluster */
    LpTomChCntrlRegs = (P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    LpTomClusterRegs = (P2VAR(Ocu_GTMTomClusterRegs, AUTOMATIC, REGSPACE) )LpGtmChannelConfig->pGtmTomATomClusterRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    /* Reset the GTM TOM channel */
    LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((OCU_ONE << LpGtmChannelConfig->usChannelBitValue) << OCU_SHIFT_8);       /* PRQA S 0499, 4391 # JV-01, JV-01 */
    /* Load initial value into the channel control shadow register */
    LpTomChCntrlRegs->ulCHxCTRLSR = LpGtmChannelConfig->ulCTRLRegValue & ~OCU_TOM_ATOM_CTRL_CLKSRC_MASK;
    /* Enable synchronous update the channel via the global control register */
    LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((OCU_TOM_ATOM_CTRL_ENABLE << OCU_SHIFT_16) << LulChShiftNum);
    /* Load control register value */
    LpTomChCntrlRegs->ulCHxCTRL = LpGtmChannelConfig->ulCTRLRegValue;
    /* Enable the output */
    LpTomClusterRegs->ulTGCOUTENSTAT = OCU_TOM_ATOM_CTRL_ENABLE << LulChShiftNum;
    /* Set compare value with max counter */
    LpTomChCntrlRegs->ulCHxCM0 = LulMaxHWCouter;
    /* Set max value to prevent CCU1 event */
    LpTomChCntrlRegs->ulCHxCM1 = OCU_TOM_MAX_COUNTER_VALUE;
    /* Set compare value with max counter */
    LpTomChCntrlRegs->ulCHxSR0 = LulMaxHWCouter;
    /* Set max value to prevent CCU1 event */
    LpTomChCntrlRegs->ulCHxSR1 = OCU_TOM_MAX_COUNTER_VALUE;
    /* Initialize counter */
    LpTomChCntrlRegs->ulCHxCN0 = LulMaxHWCouter;
    /* Start the counter */
    LpTomClusterRegs->ulTGCENDISSTAT = OCU_TOM_ATOM_CTRL_ENABLE << LulChShiftNum;
    #endif
  }
  /* Disable any interrupts associated with this channel */
  Ocu_HW_Gtm_DisableInterrupt(LddChannel);

  /* Check and reset interrupt setting outside GTM TOM/ATOM cluster if applicable */
  if (NULL_PTR != LpGtmChannelConfig->pGTM_IRQ_SELxy)
  {
    /* Reset Interrupt setting */
    *(LpGtmChannelConfig->pGTM_IRQ_SELxy) &= ~(LpGtmChannelConfig->ulGTM_IRQ_SELxyEnableValue);
  }

  /* Check and disable interrupt outside GTM ATOM cluster if applicable */
  if (NULL_PTR != LpChannelConfig->pEICReg)
  {
    /* Disable Interrupt */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pEICReg), OCU_EIMK_DISABLE_MASK);                                       /* PRQA S 0751, 1006 # JV-01, JV-01 */
  }
}

/* Macro to specify the end of the private code section */
#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_ChannelDeInit
**
** Description           : This function de-initializes a GTM channel by resetting its state and disabling interrupts.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LddChannel - The channel index to be de-initialized.
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GpChannelRamData,
**
** Functions invoked     : RH850_SV_SET_ICR_SYNCP, Ocu_HW_Gtm_DisableInterrupt
**
** Registers used        : AGCGLBCTRL, TGCGLBCTRL, EICn
**
** Reference ID          : OCU_DUD_ACT_053, OCU_DUD_ACT_053_GBL001, OCU_DUD_ACT_053_GBL002,
** Reference ID          : OCU_DUD_ACT_053_GBL003, OCU_DUD_ACT_053_GBL004, OCU_DUD_ACT_053_GBL005,
** Reference ID          : OCU_DUD_ACT_053_REG001, OCU_DUD_ACT_053_REG002, OCU_DUD_ACT_053_REG003,
** Reference ID          : OCU_DUD_ACT_053_REG004
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_ChannelDeInit(Ocu_ChannelType LddChannel)                                       /* PRQA S 3006 # JV-01 */
{
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_GTMChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpGtmChannelConfig;
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpChannelConfig;
  P2VAR(Ocu_ChannelRamDataType, AUTOMATIC, OCU_CONFIG_DATA) LpRamData;                                                  /* PRQA S 3432 # JV-01 */
  #if (OCU_GTM_ATOM_USED == STD_ON)
  P2VAR(Ocu_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  #if (OCU_GTM_TOM_USED == STD_ON)
  P2VAR(Ocu_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif

  /* Get the current channel configuration */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  LpGtmChannelConfig = LpChannelConfig->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */
  LpRamData = &Ocu_GpChannelRamData[LddChannel];
  /* Check if is ATOM channel */
  #if (OCU_GTM_ATOM_USED == STD_ON)
  if(OCU_HWIP_GTM_ATOM == LpGtmChannelConfig->ucGtmUnitType)
  {
    /* Get the current channel configuration */
    LpAtomClusterRegs = (P2VAR(Ocu_GTMAtomClusterRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomClusterRegs;/* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    /* Reset the GTM ATOM channel by updating the AGC Global control register */
    LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((OCU_ONE << LpGtmChannelConfig->usChannelBitValue) << OCU_SHIFT_8);      /* PRQA S 0499, 4391 # JV-01, JV-01 */
  }
  else
  #endif
  {
    #if (OCU_GTM_TOM_USED == STD_ON)
    /* Get the current channel configuration */
    LpTomClusterRegs = (P2VAR(Ocu_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomClusterRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    /* Reset the GTM TOM channel by updating the TGC Global control register */
    LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((OCU_ONE << LpGtmChannelConfig->usChannelBitValue) << OCU_SHIFT_8);       /* PRQA S 0499, 4391 # JV-01, JV-01 */
    #endif
  }

  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  /* If notifications are supported, set the Notification status to OCU_FALSE */
  LpRamData->blNotifyStatus = OCU_FALSE;
  #endif
  /* Assign the timer status to the Channel as stopped */
  LpRamData->blChannelStatus = OCU_CH_STOPPED;
  #if (OCU_SET_PIN_ACTION_API == STD_ON)
  /* If the pin action API is supported, disable the pin action state */
  LpRamData->ddPinActionState = OCU_DISABLE;
  #endif
  
  /* Disable verification of actual threshold */
  LpRamData->blRequireRewriteCountValue = OCU_FALSE;
  /* Load the last HW threshold value to the local variable */
  LpRamData->ddHwLastThreshold = OCU_DOUBLE_ZERO;

  /* Disable the interrupt processing for the current channel */
  Ocu_HW_Gtm_DisableInterrupt(LddChannel);
  /* Check and reset interrupt setting outside GTM TOM/ATOM cluster if applicable */
  if (NULL_PTR != LpGtmChannelConfig->pGTM_IRQ_SELxy)
  {
    /* Reset Interrupt setting */
    *(LpGtmChannelConfig->pGTM_IRQ_SELxy) &= ~(LpGtmChannelConfig->ulGTM_IRQ_SELxyEnableValue);
  }
  /* Check and disable interrupt outside GTM ATOM cluster if applicable */
  if (NULL_PTR != LpChannelConfig->pEICReg)
  {
    /* Disable Interrupt */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pEICReg), OCU_EIMK_DISABLE_MASK);                                       /* PRQA S 0751, 1006 # JV-01, JV-01 */
  }
}

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_EnableInterrupt
**
** Description           : Enables the necessary interrupts for a given OCU channel, setting up the ATOM/TOM
**                         control registers, clearing pending interrupts and enabling them.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig
**
** Functions invoked     : RH850_SV_CLEAR_ICR_SYNCP,
**
** Registers used        : GTM_IRQ_SELxy, CHxIRQNOTIFY, EICn, CHxIRQEN
**
** Reference ID          : OCU_DUD_ACT_054, OCU_DUD_ACT_054_REG001, OCU_DUD_ACT_054_REG002,
** Reference ID          : OCU_DUD_ACT_054_REG003, OCU_DUD_ACT_054_REG004, OCU_DUD_ACT_054_REG005,
** Reference ID          : OCU_DUD_ACT_054_REG006
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_EnableInterrupt(Ocu_ChannelType LddChannel)                                     /* PRQA S 3006 # JV-01 */
{
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_GTMChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpGtmChannelConfig;
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpChannelConfig;
  #if (OCU_GTM_ATOM_USED == STD_ON)
  P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  #if (OCU_GTM_TOM_USED == STD_ON)
  P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif

  /* Get the current channel configuration */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  LpGtmChannelConfig = LpChannelConfig->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */

  /* Clear pending interrupt flag if the feature is enabled */
  #if (OCU_CLEAR_PENDING_INTERRUPT == STD_ON)
  /* Check if the Interrupt register is present for a particular channel */
  if (NULL_PTR != LpChannelConfig->pEICReg)
  {
    /* Clear pending interrupts with dummy read and execute syncp instruction */
    RH850_SV_CLEAR_ICR_SYNCP(16, LpChannelConfig->pEICReg, OCU_CLEAR_PENDING_INTR_MASK);                                /* PRQA S 1006 # JV-01 */
  }
  #endif

  /* Enable the interrupt selection register if present */
  if (NULL_PTR != LpGtmChannelConfig->pGTM_IRQ_SELxy)
  {
    /* Set Interrupt setting */
    *(LpGtmChannelConfig->pGTM_IRQ_SELxy) |= LpGtmChannelConfig->ulGTM_IRQ_SELxyEnableValue;
  }

  #if (OCU_GTM_ATOM_USED == STD_ON)
  if(OCU_HWIP_GTM_ATOM == LpGtmChannelConfig->ucGtmUnitType)
  {
    /* Get the current channel configuration */
    LpAtomChCntrlRegs = (P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;/* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    /* Clear interrupt inside GTM ATOM cluster */
    LpAtomChCntrlRegs->ulCHxIRQNOTIFY = OCU_TOM_ATOM_ISR_CCU01_ENABLE;
    /* Check if the output pin is enabled or not */
    if (OCU_FALSE == LpChannelConfig->blOutputPinUsed)
    {
      /* Enable CCU1 interrupt if output pin is not used */
      LpAtomChCntrlRegs->ulCHxIRQEN = OCU_TOM_ATOM_ISR_CCU1_ENABLE;
    }
    else
    {
      /* Enable CCU01 interrupt if the output pin is used */
      LpAtomChCntrlRegs->ulCHxIRQEN = OCU_TOM_ATOM_ISR_CCU01_ENABLE;
    }
  }
  else
  #endif
  {
    #if (OCU_GTM_TOM_USED == STD_ON)
    /* Get the current channel configuration */
    LpTomChCntrlRegs = (P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    /* Clear interrupt inside GTM TOM cluster */
    LpTomChCntrlRegs->ulCHxIRQNOTIFY = OCU_TOM_ATOM_ISR_CCU01_ENABLE;
    /* Enable CCU1 interrupt if output pin is not used */
    LpTomChCntrlRegs->ulCHxIRQEN = OCU_TOM_ATOM_ISR_CCU1_ENABLE;
    #endif
  }

  /* Enable interrupt in external interrupt controller register if present */
  if (NULL_PTR != LpChannelConfig->pEICReg)
  {
    /* Enable Interrupt */
    RH850_SV_CLEAR_ICR_SYNCP(8, (LpChannelConfig->pEICReg), OCU_EIMK_ENABLE_MASK);                                      /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */
}

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_DisableInterrupt
**
** Description           : This function disables the interrupt for a specified OCU channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig
**
** Functions invoked     : None
**
** Registers used        : CHxIRQEN
**
** Reference ID          : OCU_DUD_ACT_055, OCU_DUD_ACT_055_REG001, OCU_DUD_ACT_055_REG002
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_DisableInterrupt(Ocu_ChannelType LddChannel)
{
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_GTMChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpGtmChannelConfig;
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpChannelConfig;
  #if (OCU_GTM_ATOM_USED == STD_ON)
  P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  #if (OCU_GTM_TOM_USED == STD_ON)
  P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  
  /* Get the current channel configuration */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  LpGtmChannelConfig = LpChannelConfig->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */
  #if (OCU_GTM_ATOM_USED == STD_ON)
  if(OCU_HWIP_GTM_ATOM == LpGtmChannelConfig->ucGtmUnitType)
  {
    /* Get the current channel configuration */
    LpAtomChCntrlRegs = (P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;/* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    /* Disable interrupt inside GTM ATOM cluster */
    LpAtomChCntrlRegs->ulCHxIRQEN = OCU_DOUBLE_ZERO;
  }
  else
  #endif
  {
    #if (OCU_GTM_TOM_USED == STD_ON)
    /* Get the current channel configuration */
    LpTomChCntrlRegs = (P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    /* Disable interrupt inside GTM TOM cluster */
    LpTomChCntrlRegs->ulCHxIRQEN = OCU_DOUBLE_ZERO;
    #endif
  }
}

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_GetCounter
**
** Description           : This function retrieves the current counter value for a specified Ocu channel.
**                         It determines the counting direction and reads the appropriate counter register.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : Ocu_ValueType - The elapsed time based on the counter value.
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GblCountingDirection
**
** Functions invoked     : Ocu_HW_Gtm_GetTbuCounterVal
**
** Registers used        : CHxCM0, CHxCN0
**
** Reference ID          : OCU_DUD_ACT_057
***********************************************************************************************************************/
#if (((OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)) \
                                                                                || (OCU_GET_COUNTER_API == STD_ON))
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Ocu_ValueType, OCU_PRIVATE_CODE) Ocu_HW_Gtm_GetCounter(Ocu_ChannelType LddChannel)
{
  /* Variable to hold timer SW counter value */
  VAR(Ocu_ValueType, AUTOMATIC) LddTimeElapsed;
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_GTMChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpGtmChannelConfig;
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpChannelConfig;
  #if (OCU_GTM_ATOM_USED == STD_ON)
  P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #endif
  #if (OCU_GTM_TOM_USED == STD_ON)
  P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #endif
  
  /* Set initial value */
  LddTimeElapsed = OCU_ZERO;                                                                                            /* PRQA S 2982 # JV-01 */
  /* Get the current channel configuration */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  LpGtmChannelConfig = LpChannelConfig->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */
  #if (OCU_GTM_ATOM_USED == STD_ON)
  /* Get the current channel configuration */
  LpAtomChCntrlRegs = (P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
  if(OCU_HWIP_GTM_ATOM == LpGtmChannelConfig->ucGtmUnitType)
  {
    /* Check the counting direction */
    if (OCU_UPCOUNTING == Ocu_GblCountingDirection)                                                                     /* PRQA S 3416 # JV-01 */
    {
      /* Check if output pin is not used */
      if(OCU_FALSE == LpChannelConfig->blOutputPinUsed)
      {
        /* Read the counter value from the ATOM channel register */
        LddTimeElapsed = (LpAtomChCntrlRegs->ulCHxCN0 & OCU_ATOM_MAX_COUNTER_VALUE)
                          / (uint32)(LpChannelConfig->usChannelTickDuration);
      }
      else
      {
        #if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
        /* Read the counter value based on TBU counter */
        LddTimeElapsed = Ocu_HW_Gtm_GetTbuCounterVal(LddChannel);
        #endif
      }
    }
    else /* Else OCU_DOWNCOUNTING */
    {
      /* Check if output pin is not used */
      if(OCU_FALSE == LpChannelConfig->blOutputPinUsed)
      {
        /* Read the counter value from the ATOM channel register and adjust for downcounting */
        LddTimeElapsed = ((LpAtomChCntrlRegs->ulCHxCM0 - LpAtomChCntrlRegs->ulCHxCN0 - OCU_ONE)                         /* PRQA S 0404, 3384 # JV-01, JV-01 */
                    & OCU_ATOM_MAX_COUNTER_VALUE) / (uint32)(LpChannelConfig->usChannelTickDuration);
      }
      else
      {
        #if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
        /* Read the counter value based on TBU counter and adjust for downcounting */
        LddTimeElapsed = OCU_TBU_MAX_COUNTER_VALUE - Ocu_HW_Gtm_GetTbuCounterVal(LddChannel);                           /* PRQA S 3383 # JV-01 */
        #endif
      }
    }
  }
  else
  #endif
  {
    #if (OCU_GTM_TOM_USED == STD_ON)
    /* Get the current channel configuration */
    LpTomChCntrlRegs = (P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    /* Check the counting direction */
    if (OCU_UPCOUNTING == Ocu_GblCountingDirection)                                                                     /* PRQA S 3416 # JV-01 */
    {
      /* Read the counter value from the TOM channel register */
      LddTimeElapsed = (LpTomChCntrlRegs->ulCHxCN0 & OCU_TOM_MAX_COUNTER_VALUE)
                        / (uint32)(LpChannelConfig->usChannelTickDuration);
    }
    else /* Else OCU_DOWNCOUNTING */
    {
      /* Read the counter value from the ATOM channel register and adjust for downcounting */
      LddTimeElapsed = ((LpTomChCntrlRegs->ulCHxCM0 - LpTomChCntrlRegs->ulCHxCN0 - OCU_ONE)                             /* PRQA S 0404, 3384 # JV-01, JV-01 */
                  & OCU_TOM_MAX_COUNTER_VALUE) / (uint32)(LpChannelConfig->usChannelTickDuration);
    }
    #endif
  }

  /* Return the time elapsed value */
  return LddTimeElapsed;
}
#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_StartRestartChannel
**
** Description           : Initializes or restarts a given OCU channel with the specified threshold value.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LddChannel, LddHwNewThreshold
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig
**
** Functions invoked     : Ocu_HW_Gtm_EnableInterrupt, Ocu_HW_Gtm_CalCyclicEvent, Ocu_HW_Gtm_SetCyclicEvent
**
** Registers used        : CHxCM0, CHxCN0, AGCENDISSTAT, CHxCM1, CHxSR1, TGCGLBCTRL
**
** Reference ID          : OCU_DUD_ACT_058, OCU_DUD_ACT_058_REG007
** Reference ID          : OCU_DUD_ACT_058_REG001, OCU_DUD_ACT_058_REG002, OCU_DUD_ACT_058_REG003,
** Reference ID          : OCU_DUD_ACT_058_REG004, OCU_DUD_ACT_058_REG005, OCU_DUD_ACT_058_REG006,
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_CODE_FAST) Ocu_HW_Gtm_StartRestartChannel(Ocu_ChannelType LddChannel, Ocu_ValueType LddHwNewThreshold)
{
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_GTMChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpGtmChannelConfig;
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpChannelConfig;
  #if (OCU_GTM_ATOM_USED == STD_ON)
  P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  P2VAR(Ocu_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  #if (OCU_GTM_TOM_USED == STD_ON)
  P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  P2VAR(Ocu_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  /* Channel bit shift */
  uint32 LulChShiftNum;

  /* Get the current channel configuration */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  LpGtmChannelConfig = LpChannelConfig->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */
  LulChShiftNum = (uint32)(LpGtmChannelConfig->usChannelBitValue << OCU_ONE);                                           /* PRQA S 4391 # JV-01 */
  #if (OCU_GTM_ATOM_USED == STD_ON)
  /* Check if channel is ATOM */
  if(OCU_HWIP_GTM_ATOM == LpGtmChannelConfig->ucGtmUnitType)
  {
    /* Get the pointer to the ATOM cluster control registers */
    LpAtomClusterRegs = (P2VAR(Ocu_GTMAtomClusterRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomClusterRegs;/* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    LpAtomChCntrlRegs = (P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;/* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    #if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
    /* Check if the ATOM output pin used mode is SOMB */
    if (OCU_TRUE == LpChannelConfig->blOutputPinUsed)
    {
      /* Enable interrupt processing for the current channel */
      Ocu_HW_Gtm_EnableInterrupt(LddChannel);
      /* Split the TBU counter into 3 parts for adapting with TBU cyclic event compare */
      Ocu_HW_Gtm_CalCyclicEvent(LddChannel, LddHwNewThreshold);
      /* Set up the cyclic event for the given channel */
      Ocu_HW_Gtm_SetCyclicEvent(LddChannel);
      /* Start the counter by enabling the corresponding channel */
      LpAtomClusterRegs->ulAGCENDISSTAT = OCU_TOM_ATOM_CTRL_ENABLE << LulChShiftNum;
    }
    else
    #endif
    {
      /* Check if threshold is 0 */
      if ((uint32)OCU_ZERO != LddHwNewThreshold)
      {
        /* Load the default threshold value into the channel compare shadow register */
        LpAtomChCntrlRegs->ulCHxSR1 = LddHwNewThreshold;
      }
      else
      {
        /* Load value 1 into the channel compare shadow register */
        LpAtomChCntrlRegs->ulCHxSR1 = (uint32)OCU_ONE;
      }
      /* If current CN0 < ulCHxCM1 */
      if(LpAtomChCntrlRegs->ulCHxCN0 < LddHwNewThreshold)
      {
        /* Disable synchronous update channel via the global control register */
        LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((OCU_TOM_ATOM_CTRL_DISABLE << OCU_SHIFT_16) << LulChShiftNum);
        /* Load the default threshold value into the channel control register */
        LpAtomChCntrlRegs->ulCHxCM1 = LddHwNewThreshold;
        /* Enable synchronous update channel via the global control register */
        LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((OCU_TOM_ATOM_CTRL_ENABLE << OCU_SHIFT_16) << LulChShiftNum);
      }
    }
  }
  else
  #endif
  {
    #if (OCU_GTM_TOM_USED == STD_ON)
    /* Get the pointer to the TOM cluster control registers */
    LpTomClusterRegs = (P2VAR(Ocu_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomClusterRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    LpTomChCntrlRegs = (P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    /* Check if threshold is 0 */
    if ((uint32)OCU_ZERO != LddHwNewThreshold)
    {
      /* Load the default threshold value into the channel compare shadow register */
      LpTomChCntrlRegs->ulCHxSR1 = LddHwNewThreshold;
    }
    else
    {
      /* Load value 1 into the channel compare shadow register */
      LpTomChCntrlRegs->ulCHxSR1 = (uint32)OCU_ONE;
    }
    /* If current CN0 < ulCHxCM1 */
    if(LpTomChCntrlRegs->ulCHxCN0 < LddHwNewThreshold)
    {
      /* Disable synchronous update channel via the global control register */
      LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((OCU_TOM_ATOM_CTRL_DISABLE << OCU_SHIFT_16) << LulChShiftNum);
      /* Load the default threshold value into the channel control register */
      LpTomChCntrlRegs->ulCHxCM1 = LddHwNewThreshold;
      /* Enable synchronous update channel via the global control register */
      LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((OCU_TOM_ATOM_CTRL_ENABLE << OCU_SHIFT_16) << LulChShiftNum);
    }
    #endif
  }
}

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_StopChannel
**
** Description           : This function stops a specific OCU channel by disabling its counter and updating its status.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GpChannelRamData
**
** Functions invoked     : None
**
** Registers used        : AGCGLBCTRL, TGCGLBCTRL, CHxCM1, CHxSR1, AGCENDISSTAT
**
** Reference ID          : OCU_DUD_ACT_059_REG001, OCU_DUD_ACT_059_REG002, OCU_DUD_ACT_059_REG003,
** Reference ID          : OCU_DUD_ACT_059_REG004, OCU_DUD_ACT_059_REG005, OCU_DUD_ACT_059_REG006,
** Reference ID          : OCU_DUD_ACT_059_REG007, OCU_DUD_ACT_059_GBL001, OCU_DUD_ACT_059
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_CODE_FAST) Ocu_HW_Gtm_StopChannel(Ocu_ChannelType LddChannel)
{
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_GTMChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpGtmChannelConfig;
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpChannelConfig;
  #if (OCU_GTM_ATOM_USED == STD_ON)
  P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  P2VAR(Ocu_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  #if (OCU_GTM_TOM_USED == STD_ON)
  P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  P2VAR(Ocu_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  /* Channel bit shift */
  uint32 LulChShiftNum;

  /* Get the current channel configuration */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  LpGtmChannelConfig = LpChannelConfig->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */
  LulChShiftNum = (uint32)(LpGtmChannelConfig->usChannelBitValue << OCU_ONE);                                           /* PRQA S 4391 # JV-01 */
  #if (OCU_GTM_ATOM_USED == STD_ON)
  /* Check if channel is ATOM */
  if(OCU_HWIP_GTM_ATOM == LpGtmChannelConfig->ucGtmUnitType)
  {
  /* Get the current channel configuration */
    LpAtomChCntrlRegs = (P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;/* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    LpAtomClusterRegs = (P2VAR(Ocu_GTMAtomClusterRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomClusterRegs;/* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    /* Check if the output pin is not used */
    if (OCU_FALSE == LpChannelConfig->blOutputPinUsed)
    {
      /* Disable synchronous update channel via the global control register */
      LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((OCU_TOM_ATOM_CTRL_DISABLE << OCU_SHIFT_16) << LulChShiftNum);
      /* Load maximum counter value into CHxCM1 to simulate stopping the counter */
      LpAtomChCntrlRegs->ulCHxCM1 = OCU_ATOM_MAX_COUNTER_VALUE;
      /* Load maximum counter value into CHxSR1 to simulate stopping the counter */
      LpAtomChCntrlRegs->ulCHxSR1 = OCU_ATOM_MAX_COUNTER_VALUE;
      /* Enable synchronous update channel via the global control register */
      LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((OCU_TOM_ATOM_CTRL_ENABLE << OCU_SHIFT_16) << LulChShiftNum);
    }
    else
    {
      /* Disable the counter in the AGCENDISSTAT register */
      LpAtomClusterRegs->ulAGCENDISSTAT =
        ~(OCU_TOM_ATOM_CTRL_ENABLE << (LpGtmChannelConfig->usChannelBitValue << OCU_ONE));
    }
  }
  else
  #endif
  {
    #if (OCU_GTM_TOM_USED == STD_ON)
    /* Get the current channel configuration */
    LpTomChCntrlRegs = (P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    LpTomClusterRegs = (P2VAR(Ocu_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomClusterRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
    /* Disable synchronous update channel via the global control register */
    LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((OCU_TOM_ATOM_CTRL_DISABLE << OCU_SHIFT_16) << LulChShiftNum);
    /* Load maximum counter value into CHxCM1 to simulate stopping the counter */
    LpTomChCntrlRegs->ulCHxCM1 = OCU_TOM_MAX_COUNTER_VALUE;
    /* Load maximum counter value into CHxSR1 to simulate stopping the counter */
    LpTomChCntrlRegs->ulCHxSR1 = OCU_TOM_MAX_COUNTER_VALUE;
    /* Enable synchronous update channel via the global control register */
    LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((OCU_TOM_ATOM_CTRL_ENABLE << OCU_SHIFT_16) << LulChShiftNum);
    #endif
  }

  /* Set the channel status to stopped */
  Ocu_GpChannelRamData[LddChannel].blChannelStatus = OCU_CH_STOPPED;
}

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_SetPinState
**
** Description           : Sets the pin state for a given OCU channel. The pin state can be either HIGH
**                         or LOW.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel, LddPinState
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig
**
** Functions invoked     : None
**
** Registers used        : CHxCTRL
**
** Reference ID          : OCU_DUD_ACT_060_REG001, OCU_DUD_ACT_060
***********************************************************************************************************************/
#if (OCU_SET_PIN_STATE_API == STD_ON) && (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)

#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_SetPinState(Ocu_ChannelType LddChannel, Ocu_PinStateType LddPinState)
{
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_GTMChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpGtmChannelConfig;
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpChannelConfig;
  P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  
  /* Get the current channel configuration */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  LpGtmChannelConfig = LpChannelConfig->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */
  LpAtomChCntrlRegs = (P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
  
  /* Set the current output level of the associated pin with the current channel */
  if (OCU_HIGH == LddPinState)
  {
    /* Set the pin state to HIGH by loading the value into ulCHxCTRL register */
    LpAtomChCntrlRegs->ulCHxCTRL |= OCU_ATOM_CTRL_SL_MASK;
  }
  else
  {
    /* Set the pin state to LOW by loading the value into ulCHxCTRL register */
    LpAtomChCntrlRegs->ulCHxCTRL &= ~OCU_ATOM_CTRL_SL_MASK;
  }
}

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_SetThreshold
**
** Description           : This function sets the threshold for a specified OCU channel.
**                        It considers the counting direction (up or down) and updates the hardware with the new
**                        calculated threshold value.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel, LddSwThresholdValue
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GpChannelRamData, Ocu_GblCountingDirection
**
** Functions invoked     : Ocu_HW_Gtm_StartRestartChannel
**
** Registers used        : None
**
** Reference ID          : OCU_DUD_ACT_061, OCU_DUD_ACT_061_GBL001
***********************************************************************************************************************/
#if ((OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON))
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_SetThreshold(Ocu_ChannelType LddChannel, Ocu_ValueType LddSwThresholdValue)
{
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpChannelConfig;
  P2VAR(Ocu_ChannelRamDataType, AUTOMATIC, OCU_CONFIG_DATA) LpRamData;                                                  /* PRQA S 3432 # JV-01 */
  /* Max counter value */
  uint32 LulMaxHWCouter;

  /* Get the current channel configuration */
  LpRamData = &Ocu_GpChannelRamData[LddChannel];
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];

  /* Check the counting direction */
  if (OCU_UPCOUNTING == Ocu_GblCountingDirection)                                                                       /* PRQA S 3416 # JV-01 */
  {
    /* Calculate and update the last HW threshold for up-counting direction */
    LpRamData->ddHwLastThreshold = LddSwThresholdValue * (uint32)(LpChannelConfig->usChannelTickDuration);              /* PRQA S 3384 # JV-01 */
  }
  else /* Else OCU_DOWNCOUNTING */
  {
    /* Calculate the max counter value */
    LulMaxHWCouter = (uint32)((LpChannelConfig->ulMaxCounterValue + (uint32)OCU_ONE) *                                  /* PRQA S 3383, 3384 # JV-01, JV-01 */
                      (uint32)LpChannelConfig->usChannelTickDuration);
    /* Calculate and update the last HW threshold for down-counting direction */
    LpRamData->ddHwLastThreshold = LulMaxHWCouter -                                                                     /* PRQA S 3383 # JV-01 */
                      ((LddSwThresholdValue + (uint32)OCU_ONE) * (uint32)(LpChannelConfig->usChannelTickDuration));     /* PRQA S 3383, 3384 # JV-01, JV-01 */
  }

  /* If the channel is in running status, restart the slave timer with the new threshold */
  if (OCU_CH_RUNNING == LpRamData->blChannelStatus)
  {
    Ocu_HW_Gtm_StartRestartChannel(LddChannel, LpRamData->ddHwLastThreshold);
  } /* else No action required */
} /* End of function Ocu_HW_Gtm_SetThreshold */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* ((OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)) */

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_GetTbuCounterVal
**
** Description           : Retrieves the TBU counter value for the specified OCU channel.
**                         The function returns the counter value after applying a mask with the maximum counter value.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : uint32 - TBU counter value masked by OCU_TBU_MAX_COUNTER_VALUE.
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GpGtmTbuUnitConfig
**
** Functions invoked     : None
**
** Registers used        : TBU0BASE, TBU1BASE, TBU2BASE
**
** Reference ID          : OCU_DUD_ACT_062
***********************************************************************************************************************/
#if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(uint32, OCU_PRIVATE_CODE) Ocu_HW_Gtm_GetTbuCounterVal(Ocu_ChannelType LddChannel)                                  /* PRQA S 1505 # JV-01 */
{ 
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_GTMChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpGtmChannelConfig;
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpChannelConfig;
  P2VAR(Ocu_GTMTbuChannelRegs, AUTOMATIC, REGSPACE) LpTbuChRegs;                                                        /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Variable to store the TBU counter value */
  uint32 LulReturnVal = OCU_DOUBLE_ZERO;

  /* Get the current channel configuration */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  LpGtmChannelConfig = LpChannelConfig->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */
  LpTbuChRegs = (Ocu_GTMTbuChannelRegs *)Ocu_GpGtmTbuUnitConfig[OCU_ZERO].pTBUCHENRegs;                                 /* PRQA S 0310, 0312 # JV-01, JV-01 */

  /* Retrieve and mask the TBU counter value based on the TBU channel number */
  if (OCU_ZERO == LpGtmChannelConfig->ucTbuChannelNo) 
  {
    /* Get TBU_TS0 value */
    LulReturnVal = LpTbuChRegs->ulTBU0BASE & OCU_TBU_MAX_COUNTER_VALUE;
  } 
  else if (OCU_ONE == LpGtmChannelConfig->ucTbuChannelNo) 
  {
    /* Get TBU_TS1 value */
    LulReturnVal = LpTbuChRegs->ulTBU1BASE & OCU_TBU_MAX_COUNTER_VALUE;
  } 
  else 
  {
    /* Get TBU_TS2 value */
    LulReturnVal = LpTbuChRegs->ulTBU2BASE & OCU_TBU_MAX_COUNTER_VALUE;
  }
  /* Return value */
  return LulReturnVal;
} /* End of Ocu_HW_Gtm_GetTbuCounterVal */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_CalCyclicEvent
**
** Description           : This function calculates and sets cyclic event values for a specified OCU channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel, LddThresholdVal
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GaaCyclicRamData
**
** Functions invoked     : None
**
** Registers used        : TBU0BASE, TBU1BASE, TBU2BASE
**
** Reference ID          : OCU_DUD_ACT_063, OCU_DUD_ACT_063_GBL001, OCU_DUD_ACT_063_GBL002
** Reference ID          : OCU_DUD_ACT_063_GBL003, OCU_DUD_ACT_063_GBL004
***********************************************************************************************************************/
#if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_CalCyclicEvent(Ocu_ChannelType LddChannel, Ocu_ValueType LddThresholdVal)       /* PRQA S 1505 # JV-01 */
{
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_GTMChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpGtmChannelConfig;
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpChannelConfig;
  P2VAR(Ocu_GaaCyclicRamDataType, AUTOMATIC, OCU_CONFIG_DATA) LpTbuCyclicData;                                          /* PRQA S 3432 # JV-01 */
  /* Variable to store the relative value based on 1/3 TBU max counter */
  uint32 LulRelativeOnPart;

  /* Get the current channel configuration */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  /* Get the pointer to the OCU Channel properties */
  LpGtmChannelConfig = LpChannelConfig->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */
  /* Load the channel RAM data into the local pointer */
  LpTbuCyclicData = &Ocu_GaaCyclicRamData[LpGtmChannelConfig->ucTbuRamIndex];
  /* Calculate the relative value */
  LulRelativeOnPart = LddThresholdVal % OCU_TBU_DIVIDE_PART;

  /* Save the calculated cyclic values to RAM */
  LpTbuCyclicData->ulFirstCyclicValue = LulRelativeOnPart;
  LpTbuCyclicData->ulSecondCyclicValue = OCU_TBU_SECOND_PART + LulRelativeOnPart;                                       /* PRQA S 3383 # JV-01 */
  LpTbuCyclicData->ulThirdCyclicValue = OCU_TBU_THIRD_PART + LulRelativeOnPart;                                         /* PRQA S 3383 # JV-01 */
  LpTbuCyclicData->ulThresholdValue = LddThresholdVal;
} /* End of function Ocu_HW_Gtm_CalCyclicEvent */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_SetCyclicEvent
**
** Description           : Sets a cyclic event for the GTM.
**                         Determines the next threshold value based on the current TBU counter
**                         value and configured cyclic RAM data.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GaaCyclicRamData, Ocu_GpChannelRamData
**
** Functions invoked     : Ocu_HW_Gtm_GetTbuCounterVal, Ocu_HW_Gtm_SetCyclicPinAction
**
** Registers used        : CHxCM1, CHxCM0
**
** Reference ID          : OCU_DUD_ACT_064, OCU_DUD_ACT_064_REG001, OCU_DUD_ACT_064_REG002
** Reference ID          : OCU_DUD_ACT_064_GBL001
***********************************************************************************************************************/
#if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
#define OCU_START_SEC_CODE_FAST
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_SetCyclicEvent(Ocu_ChannelType LddChannel)                                      /* PRQA S 1505 # JV-01 */
{
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_GTMChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpGtmChannelConfig;
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpChannelConfig;
  P2VAR(Ocu_GaaCyclicRamDataType, AUTOMATIC, OCU_CONFIG_DATA) LpTbuCyclicData;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  /* Local variable */
  uint32 LulFirstPart;
  uint32 LulSecondPart;
  uint32 LulThirdPart;
  uint32 LulTbuCounterVal;
  uint32 LddNextThresholdVal;

  /* Get the current channel configuration */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  LpGtmChannelConfig = LpChannelConfig->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */
  LpTbuCyclicData = &Ocu_GaaCyclicRamData[LpGtmChannelConfig->ucTbuRamIndex];
  LpAtomChCntrlRegs = (P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */

  /* Set Local variable from TBU cyclic Ram data */
  LulFirstPart = LpTbuCyclicData->ulFirstCyclicValue;
  LulSecondPart = LpTbuCyclicData->ulSecondCyclicValue;
  LulThirdPart = LpTbuCyclicData->ulThirdCyclicValue;

  /* Get current TBU counter value */
  LulTbuCounterVal = Ocu_HW_Gtm_GetTbuCounterVal(LddChannel);

  /* Determine the next cyclic threshold value */
  if ((LulFirstPart <= LulTbuCounterVal) && (LulTbuCounterVal < LulSecondPart))
  {
    /* Set the next cyclic event to the second event */
    LddNextThresholdVal = LulSecondPart;
  }
  else if ((LulSecondPart <= LulTbuCounterVal) && (LulTbuCounterVal < LulThirdPart))
  {
    /* Set the next cyclic event to the third event */
    LddNextThresholdVal = LulThirdPart;
  }
  else
  {
    /* Set the next cyclic event to the first event */
    LddNextThresholdVal = LulFirstPart;
  }
  
  #if (OCU_SET_PIN_ACTION_API == STD_ON)
  /* Check if the cyclic value is an actual threshold value */
  if (LpTbuCyclicData->ulThresholdValue == LddNextThresholdVal)
  {
    /* Set the pin action for the next cycle */
    Ocu_HW_Gtm_SetCyclicPinAction(LddChannel, Ocu_GpChannelRamData[LddChannel].ddPinActionState);
    
    /* Indicate that the next cyclic event is the target OCU threshold */
    Ocu_GpChannelRamData[LddChannel].blRequireRewriteCountValue = OCU_TRUE;
  }
  else
  {
    /* Disable the pin action for the next cycle */
    Ocu_HW_Gtm_SetCyclicPinAction(LddChannel, OCU_DISABLE);

    /* Indicate that the next cyclic event is not the target OCU threshold */
    Ocu_GpChannelRamData[LddChannel].blRequireRewriteCountValue = FALSE;
  }
  #endif
  
  /* Load the calculated next threshold value to the channel control registers */
  LpAtomChCntrlRegs->ulCHxCM0 = LddNextThresholdVal;
  LpAtomChCntrlRegs->ulCHxCM1 = LddNextThresholdVal;

} /* End of function Ocu_HW_Gtm_SetCyclicEvent */

#define OCU_STOP_SEC_CODE_FAST
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_SetCyclicPinAction
**
** Description           : This function sets the cyclic pin action for the specified OCU channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel, LddPinAction
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig
**
** Functions invoked     : None
**
** Registers used        : CHxCTRL
**
** Reference ID          : OCU_DUD_ACT_065, OCU_DUD_ACT_065_REG001
***********************************************************************************************************************/
#if (OCU_SET_PIN_ACTION_API == STD_ON) && (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
#define OCU_START_SEC_CODE_FAST
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_SetCyclicPinAction(Ocu_ChannelType LddChannel, Ocu_PinActionType LddPinAction)  /* PRQA S 1505 # JV-01 */
{
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_GTMChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpGtmChannelConfig;
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpChannelConfig;
  P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  
  /* Get the current channel configuration */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  LpGtmChannelConfig = LpChannelConfig->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */
  LpAtomChCntrlRegs = (P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;  /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
  
  /* Reset pin action */
  LpAtomChCntrlRegs->ulCHxCTRL &= ~OCU_ATOM_CTRL_ACB10_TOGGLE;
  
  /* Check the desired pin action */
  if ((OCU_SET_HIGH == LddPinAction) || (OCU_SET_LOW == LddPinAction))
  {
    /* Checks if the "SL" control bit in the GTM ATOM channel control register is not set */
    if (OCU_ATOM_CTRL_SL_MASK != (LpAtomChCntrlRegs->ulCHxCTRL & OCU_ATOM_CTRL_SL_MASK))
    {
      /* Set the current output level of the associated pin with the current channel */
      if (OCU_SET_HIGH == LddPinAction)
      {
        /* Set pin high */
        LpAtomChCntrlRegs->ulCHxCTRL |= OCU_ATOM_CTRL_ACB10_LOW;
      }
      else
      {
        /* Set pin low */
        LpAtomChCntrlRegs->ulCHxCTRL |= OCU_ATOM_CTRL_ACB10_HIGH;
      }
    }
    /* if the "SL" control bit in the GTM ATOM channel control register is set */
    else
    {
      /* Set the current output level of the associated pin with the current channel */
      if (OCU_SET_HIGH == LddPinAction)
      {
        /* Inverted set pin low */
        LpAtomChCntrlRegs->ulCHxCTRL |= OCU_ATOM_CTRL_ACB10_HIGH;
      }
      else
      {
        /* Inverted set pin high */
        LpAtomChCntrlRegs->ulCHxCTRL |= OCU_ATOM_CTRL_ACB10_LOW;
      }
    }
  }
  else if (OCU_TOGGLE == LddPinAction)                                                                                  /* PRQA S 2004 # JV-01 */
  {
    /* Toggle the pin */
    LpAtomChCntrlRegs->ulCHxCTRL |= OCU_ATOM_CTRL_ACB10_TOGGLE;
  } /* Else no action */
} /* End of funtion Ocu_HW_Gtm_SetCyclicPinAction*/

#define OCU_STOP_SEC_CODE_FAST
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Gtm_CbkNotification
**
** Description           : This function handles the callback notification for the GTM channels.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GpChannelRamData,
**
** Functions invoked     : Dem_SetEventStatus, Ocu_Notification_<Channel>, Ocu_HW_Gtm_SetCyclicEvent
**
** Registers used        : CHxIRQEN, CHxIRQNOTIFY, EICn
**
** Reference ID          : OCU_DUD_ACT_066, OCU_DUD_ACT_066_REG001
***********************************************************************************************************************/
#define OCU_START_SEC_CODE_FAST
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, OCU_CODE_FAST) Ocu_HW_Gtm_CbkNotification(uint8 LucChannelIdx)
{
  /* Local pointers used for accessing channel-specific configuration and control registers */
  P2CONST(Ocu_GTMChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpGtmChannelConfig;
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_CONST) LpChannelConfig;
  P2VAR(Ocu_ChannelRamDataType, AUTOMATIC, OCU_CONFIG_DATA) LpRamData;                                                  /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #if (OCU_GTM_ATOM_USED == STD_ON)
  P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #endif
  #if (OCU_GTM_TOM_USED == STD_ON)
  P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #endif

  /* Get the current channel configuration */
  LpChannelConfig = &Ocu_GpChannelConfig[LucChannelIdx];
  LpGtmChannelConfig = LpChannelConfig->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */
  LpRamData = &Ocu_GpChannelRamData[LucChannelIdx];

  /* Safety interrupt check */
  #if (OCU_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* If the interrupt is configured */
  if (NULL_PTR == LpChannelConfig->pEICReg)
  {
    (void)Dem_SetEventStatus(OCU_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  /* Checks if the external interrupt mask in the EIC register is not enabled. */
  else if ((uint16)OCU_ZERO != (*LpChannelConfig->pEICReg & OCU_EIC_EIMK_MASK))
  {
    (void)Dem_SetEventStatus(OCU_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
    /* If channel is ATOM */
    #if (OCU_GTM_ATOM_USED == STD_ON)
    if(OCU_HWIP_GTM_ATOM == LpGtmChannelConfig->ucGtmUnitType)
    {
      /* Get the current channel configuration */
      LpAtomChCntrlRegs = 
            (P2VAR(Ocu_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;            /* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
      /* Check if the interrupt is reported through GTM TOM/ATOM IRQEN and IRQNOTIFY */
      if (OCU_DOUBLE_ZERO !=                                                                                            /* PRQA S 0404 # JV-01 */
                (LpAtomChCntrlRegs->ulCHxIRQEN & LpAtomChCntrlRegs->ulCHxIRQNOTIFY & OCU_TOM_ATOM_ISR_CCU01_ENABLE))
      {
        #if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
        /* Check if ATOM output enables SOMB mode */
        if (OCU_TRUE == LpChannelConfig->blOutputPinUsed)
        {
          /* Check if it is the target threshold */
          if (OCU_TRUE == LpRamData->blRequireRewriteCountValue)
          {
            #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
            /* Invoke callback notification if the notification is enabled */
            if (OCU_TRUE == LpRamData->blNotifyStatus)
            {
              if (NULL_PTR != LpChannelConfig->pOcuNotificationPointer)
              {
                /* Invoke the callback function */
                LpChannelConfig->pOcuNotificationPointer();
              } /* else: No action required */
            } /* else: No action required */
            #endif
          }
          /* Set the next cyclic compare event */
          Ocu_HW_Gtm_SetCyclicEvent(LucChannelIdx);
        }
        else /* Else ATOM SOMP mode or TOM Continuous Counting Up Mode */
        #endif
        {
          /* Check if the interrupt is reported through GTM ATOM IRQEN CCU1 and IRQNOTIFY */
          if (OCU_DOUBLE_ZERO !=                                                                                        /* PRQA S 0404 # JV-01 */
                    (LpAtomChCntrlRegs->ulCHxIRQEN & LpAtomChCntrlRegs->ulCHxIRQNOTIFY & OCU_TOM_ATOM_ISR_CCU1_ENABLE))
          {
            #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
            /* Invoke callback notification if the notification is enabled */
            if (OCU_TRUE == LpRamData->blNotifyStatus)
            {
              if (NULL_PTR != LpChannelConfig->pOcuNotificationPointer)
              {
                /* Invoke the callback function */
                LpChannelConfig->pOcuNotificationPointer();
              } /* else: No action required */
            } /* else: No action required */
            #endif
          }
        } /* End of Check if ATOM output enables SOMB mode */
        /* Clear GTM interrupt flag */
        LpAtomChCntrlRegs->ulCHxIRQNOTIFY = OCU_TOM_ATOM_ISR_CCU01_ENABLE;
      } /* End of Check if the interrupt is reported */
    }
    else
    #endif
    {
      /* If channel is TOM */
      #if (OCU_GTM_TOM_USED == STD_ON)
      
      LpTomChCntrlRegs = (P2VAR(Ocu_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpGtmChannelConfig->pGtmTomATomChannelRegs;/* PRQA S 0310, 0312, 3432 # JV-01, JV-01, JV-01 */
      /* Check if the interrupt is reported through GTM TOM/ATOM IRQEN and IRQNOTIFY */
      if (OCU_DOUBLE_ZERO !=                                                                                            /* PRQA S 0404 # JV-01 */
                  (LpTomChCntrlRegs->ulCHxIRQEN & LpTomChCntrlRegs->ulCHxIRQNOTIFY & OCU_TOM_ATOM_ISR_CCU1_ENABLE))
      {
        #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
        /* Invoke callback notification if the notification is enabled */
        if (OCU_TRUE == LpRamData->blNotifyStatus)
        {
          if (NULL_PTR != LpChannelConfig->pOcuNotificationPointer)
          {
            /* Invoke the callback function */
            LpChannelConfig->pOcuNotificationPointer();
          } /* else: No action required */
        } /* else: No action required */
        #endif
        /* Clear GTM interrupt flag */
        LpTomChCntrlRegs->ulCHxIRQNOTIFY = OCU_TOM_ATOM_ISR_CCU01_ENABLE;
      }
      #endif
    }
  } /* End of Safety interrupt check */
} /* End of function */

#define OCU_STOP_SEC_CODE_FAST
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* OCU_GTM_ATOM_USED/OCU_GTM_TOM_USED */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
