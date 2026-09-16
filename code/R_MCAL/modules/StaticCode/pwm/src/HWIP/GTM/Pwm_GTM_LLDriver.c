/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_GTM_LLDriver.c                                                                                  */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2024,2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of PWM Driver                                                                         */
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
/*                                              Devices:       X2x                                                    */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*                                                                                                                    **
** 2.5.1: 30/06/2025 : Update macro name for elements of Pwm_ClockSourceType                                          **
** 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                        **
** 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                           **
**                     As part of GTM support, following changes are made:                                            **
**                     1. Improve function Pwm_HW_GTM_SetOutputToIdle: Add condition macro PWM_GTM_VERSION            **
** 2.3.2: 29/04/2025 : As part of GTM support, following changes are made                                             **
**                     1. Update function Pwm_HW_GTM_InitChannel, Pwm_HW_GTM_SetChannelOutput,                        **
**                        Pwm_HW_GTM_DeInitChannel, Pwm_HW_GTM_SynchronousInit, Pwm_HW_GTM_SelectChannelClk,          **
**                        Pwm_HW_GTM_EnableNotification, Pwm_HW_GTM_DisableNotification, Pwm_HW_GTM_SetDutyCycle,     **
**                        Pwm_HW_GTM_SetPeriodAndDuty, Pwm_HW_GTM_SetOutputToIdle to support GTM version 3.5          **
**                     2. Add message 2877                                                                            **
** 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                           **
**                     To support QAC 11.6.0: Add message 3432, 1863, 1505, 3678, 2004, 2877, 2962, 4304, 1991, 4391  **
**                     As part of ARDAACL-54064, following changes are made:                                          **
**                     1. Update condition in function Pwm_HW_GTM_SetChannelOutput                                    **
** 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
** 2.2.0: 31/12/2024 : As part of ARDAACL-51165, ARDAACL-51621, following changes are made:                           **
**                     1. Add registers AGCENDISSTAT, AGCOUTENSTAT, TGCENDISSTAT, TGCOUTENSTAT for function           **
**                        Pwm_HW_GTM_DeInitChannel                                                                    **
**                     2. Remove registers AGCENDISSTAT, AGCOUTENSTAT, TGCENDISSTAT, TGCOUTENSTAT and update          **
**                        the register values in fuction Pwm_HW_GTM_DeInitUnit                                        **
**                     3. Update way get the return value in Pwm_HW_GTM_GetOutputState                                **
**                     4. Update register values for AGCOUTENSTAT, TGCOUTENSTAT in function Pwm_HW_GTM_SynchronousStop**
**                     5. Update critical section in functions Pwm_HW_GTM_EnableNotification, Pwm_HW_GTM_Callback     **
**                     6. Remove redundant QAC message 3416, 2877 and update QAC message 0316, 3383                   **
** 2.1.2: 31/10/2024 : Initial Version.                                                                               **
**                                                                                                                    */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for module version information and other types declarations */
#include "Pwm.h"
/* Included for RAM variable declarations */
#include "Pwm_Ram.h"
#if (PWM_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Pwm.h"
#endif
#if (PWM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
/* Included for declaration of the function Dem_SetEventStGTMs() */
#include "Dem.h"
#endif
#if (PWM_DEV_ERROR_DETECT == STD_ON)
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#if (PWM_GTM_UNIT_USED == STD_ON)
/* AUTOSAR release version information */
#define PWM_GTM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION_VALUE
#define PWM_GTM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION_VALUE
#define PWM_GTM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION_VALUE
/* Module software version information */
#define PWM_GTM_LLDRIVER_C_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION_VALUE
#define PWM_GTM_LLDRIVER_C_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION_VALUE
#define PWM_GTM_LLDRIVER_C_SW_PATCH_VERSION            PWM_SW_PATCH_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (PWM_GTM_LLDRIVER_AR_RELEASE_MAJOR_VERSION != PWM_GTM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm_GTM_LLDriver.c : Mismatch in Release Major Version"
#endif
#if (PWM_GTM_LLDRIVER_AR_RELEASE_MINOR_VERSION != PWM_GTM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Pwm_GTM_LLDriver.c : Mismatch in Release Minor Version"
#endif
#if (PWM_GTM_LLDRIVER_AR_RELEASE_REVISION_VERSION != PWM_GTM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Pwm_GTM_LLDriver.c : Mismatch in Release Revision Version"
#endif
#if (PWM_GTM_LLDRIVER_SW_MAJOR_VERSION != PWM_GTM_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Pwm_GTM_LLDriver.c : Mismatch in Software Major Version"
#endif
#if (PWM_GTM_LLDRIVER_SW_MINOR_VERSION != PWM_GTM_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Pwm_GTM_LLDriver.c : Mismatch in Software Minor Version"
#endif
#if (PWM_GTM_LLDRIVER_SW_PATCH_VERSION != PWM_GTM_LLDRIVER_C_SW_PATCH_VERSION)
  #error "Pwm_GTM_LLDriver.c : Mismatch in Software Patch Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
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
/* Message (2:0499)    : Right operand of shift operator is greater than or equal to the width of the essential type  */
/*                       of the left operand.                                                                         */
/* Rule                : CERTCCM INT34, MISRA C:2012 Rule-12.2, CWE Rule CWE-681, CWE-682, CWE-738                    */
/* JV-01 Justification : The result has been ensured by casting to the same Type                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
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
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : This in-line assembler construct is a language extension. The code has been ignored.         */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTCCM MSC14                                       */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1863)    : The operands of this equality operator are of different 'essential signedness' but will both */
/*                       be promoted to 'signed int' for comparison.                                                  */
/* Rule                : MISRA C:2012 Rule-10.4, CWE Rule CWE-192, CWE-136                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
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
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : CERTCCM EXP02, MISRA C:2012 Rule-15.7, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else"statement with empty content is removed to improve readability.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Dir-4.1                                                          */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/* Message (6:2962)    : Apparent: Using value of uninitialized automatic object '%s'.                                */
/* Rule                : CERTCCM EXP33, MISRA C:2012 Rule-9.1                                                         */
/* JV-01 Justification : It will be initialized based on scope of 'if' statements  where at least an 'if' statement   */
/*                       will be executed that will initialize the variable.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:4304)    : An expression of 'essentially Boolean' type (%1s) is being cast to unsigned type '%2s'.      */
/* Rule                : MISRA C:2012 MISRA C:2012 Rule-10.5                                                          */
/* JV-01 Justification : This is accepted. This casting from boolean to unsigned type for values 0 and 1 does not     */
/*                       make data conflict.                                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:1881)    : The operands of this equality operator are expressions of different 'essential type'         */
/*                       categories (%1s and %2s).                                                                    */
/* Rule                : MISRA C:2012 Rule-10.4, CERTCCM INT02, CWE Rule CWE-136, CWE-192                             */
/* JV-01 Justification : The equality operator between enum and unsigned type can be accepted.                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4391)    : A composite expression of 'essentially unsigned' type (unsigned char) is being cast to a     */
/*                       wider unsigned type 'unsigned short'.                                                        */
/* Rule                : MISRA C:2012 Rule-10.8, CWE Rule CWE-136                                                     */
/* JV-01 Justification : This casting is necessary and is confirmed to be no problem.                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_InitChannel
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function. This function sets the clock pre-scaler,
**                         PWM mode, Period, Duty cycle and polarity for all configured channels.
**                         This function also disables the interrupts (Notifications) and resets the interrupt request
**                         pending flags.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpChannelConfig, Pwm_GaaNotifStatus
**
** Functions invoked     : Pwm_HW_GTM_CalculateDuty
**
** Registers Used        : ATOMiCHxCN0, ATOMiCHxSR0, ATOMiCHxSR1, ATOMiCHxCTRLSR, ATOMiCHxCTRL, ATOMiCHxIRQNOTIFY
** Registers Used        : TOMiCHxCN0, TOMiCHxSR0, TOMiCHxSR1, TOMiCHxCTRLSR, TOMiCHxCTRL, TOMiCHxIRQNOTIFY
**
** Reference ID          : PWM_DUD_ACT_100, PWM_DUD_ACT_100_REG001, PWM_DUD_ACT_100_REG002, PWM_DUD_ACT_100_REG003,
** Reference ID          : PWM_DUD_ACT_100_REG004, PWM_DUD_ACT_100_REG005, PWM_DUD_ACT_100_REG006,
** Reference ID          : PWM_DUD_ACT_100_REG007, PWM_DUD_ACT_100_REG008, PWM_DUD_ACT_100_REG009,
** Reference ID          : PWM_DUD_ACT_100_REG010, PWM_DUD_ACT_100_REG011, PWM_DUD_ACT_100_REG012,
** Reference ID          : PWM_DUD_ACT_100_GBL001, PWM_DUD_ACT_100_GBL002
***********************************************************************************************************************/
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_GTM_InitChannel(void)                                                               /* PRQA S 3006 # JV-01 */
{
  /* Local Pointer used for each ATOM/TOM channel control registers */
  P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelProp;
  /* Local pointer to the each Gtm channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Channel control registers */
  P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif /* End of #if (PWM_GTM_TOM_USED == STD_ON)*/
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Channel control registers */
  P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif /* End of #if (PWM_GTM_ATOM_USED == STD_ON)*/
  /* Local variable for period, duty and period shift */
  Pwm_PeriodType LddDefaultPeriod;
  Pwm_PeriodType LddDefaultduty;
  Pwm_PeriodType LddPeriodShift;
  /* Local variable for count */
  uint8 LucCount;
  /* Local variable for Reg write */
  uint32 LulTempRegValue;

  /* Loop to set the attributes of Gtm channels */
  for (LucCount = PWM_ZERO; LucCount < (uint8)PWM_TOTAL_CHANNELS_CONFIG; LucCount++)
  {
    if (PWM_HWIP_GTM == Pwm_GpChannelConfig[LucCount].ucTimerUnitType)                                                  /* PRQA S 3416 # JV-01 */
    {
      /* Update the configure pointer to point to the current Timer channel*/
      LpChannelConfig = &Pwm_GpChannelConfig[LucCount];
      /* Get the pointer to the PWM Channel properties */
      LpChannelProp = (P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST)) LpChannelConfig->pChannelProp;     /* PRQA S 0316 # JV-01 */
      /* TOM/ATOM Type */
      #if (PWM_GTM_ATOM_USED == STD_ON)
      if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                             /* PRQA S 1863 # JV-01 */
      {
        /* Get the pointer to the PWM Channel control registers */
        LpAtomChCntrlRegs = (P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
        /* Get value of the channel period in local variable */
        LddDefaultPeriod = LpChannelProp->ddDefault_Period;
        /* Get value of the channel duty in local variable */
        LddDefaultduty = LpChannelProp->ddDefault_Duty;
      
        #if (PWM_SYNC_START_SUPPORT == STD_ON)
        if (PWM_FALSE == LpChannelConfig->blSyncStartReq)
        #endif /* End of #if (PWM_SYNC_START_SUPPORT == STD_ON)*/
        {
          /* Set the output delay */
          if (PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
          {
            /* Calculate shift period */
            LddPeriodShift = Pwm_HW_GTM_CalculateDuty(LddDefaultPeriod, LpChannelProp->usPeriodShift);
            /* Initial the delay of the pulse */
            LpAtomChCntrlRegs->ulCHxCN0 = LddDefaultPeriod - LddPeriodShift;                                            /* PRQA S 3383 # JV-01 */
          }
          else
          {
            /* Output immediately after channel started */
            LpAtomChCntrlRegs->ulCHxCN0 = LddDefaultPeriod;
          }
          /* Load the period value to reload period register */
          LpAtomChCntrlRegs->ulCHxSR0 = (uint32)(LddDefaultPeriod);
          /* Assign the configured value of the channel duty in to register */
          LpAtomChCntrlRegs->ulCHxSR1 = Pwm_HW_GTM_CalculateDuty(LddDefaultPeriod, LddDefaultduty);
          LulTempRegValue = PWM_DOUBLE_ZERO;
          /* Set polarity */
          if ((uint8)PWM_POLARITY_HIGH == LpChannelConfig->ucPolarity)
          {
            LulTempRegValue |= PWM_GTM_POLARITY_HIGH_VALUE;
            #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
            /* Load value into CHxCTRLSR */
            LpAtomChCntrlRegs->ulCHxCTRLSR |= PWM_GTM_POLARITY_HIGH_VALUE;
          }
          else
          {
            /* Load value into CHxCTRLSR */
            LpAtomChCntrlRegs->ulCHxCTRLSR &= ~PWM_GTM_POLARITY_HIGH_VALUE;
            #endif
          }
          #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
          /* Load value into CHxCTRLSR */
          LpAtomChCntrlRegs->ulCHxCTRLSR |= ((uint32)LpChannelProp->ucChClockSelect << PWM_GTM_CLKSRC_SHIFT_NUM);
          #endif
          /* Channel Clock source select */
          LulTempRegValue |= ((uint32)LpChannelProp->ucChClockSelect << PWM_GTM_CLKSRC_SHIFT_NUM);
          /* MODE select */
          LulTempRegValue |= PWM_GTM_MODE_SOMP_VALUE; 
          /* Enable FREEZE */
          LulTempRegValue |= PWM_GTM_CTRL_FREEZE_ONE;
          /* Load value into CHxCTRL */
          LpAtomChCntrlRegs->ulCHxCTRL = LulTempRegValue;
        } /* Else no action required */
      }
      else
      #endif /* End of #if (PWM_GTM_ATOM_USED == STD_ON)*/
      {
        #if (PWM_GTM_TOM_USED == STD_ON)
        /* Get the pointer to the PWM Channel control registers */
        LpTomChCntrlRegs =(P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;    /* PRQA S 0316, 3432 # JV-01, JV-01 */
        /* Get value of the channel period in local variable */
        LddDefaultPeriod = LpChannelProp->ddDefault_Period;
        /* Get value of the channel duty in local variable */
        LddDefaultduty = LpChannelProp->ddDefault_Duty;
        #if (PWM_SYNC_START_SUPPORT == STD_ON)
        if (PWM_FALSE == LpChannelConfig->blSyncStartReq)
        #endif /* End of #if (PWM_SYNC_START_SUPPORT == STD_ON)*/
        {
          /* Set the output delay */
          if (PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
          {
            /* Calculate shift period */
            LddPeriodShift = Pwm_HW_GTM_CalculateDuty(LddDefaultPeriod, LpChannelProp->usPeriodShift);
            /* Initial the delay of the pulse */
            LpTomChCntrlRegs->ulCHxCN0 = LddDefaultPeriod - LddPeriodShift;                                             /* PRQA S 3383 # JV-01 */
          }
          else
          {
            /* Output immediately after channel started */
            LpTomChCntrlRegs->ulCHxCN0 = LddDefaultPeriod;
          }
          /* Assign the configured value of the channel period in to register */
          LpTomChCntrlRegs->ulCHxSR0 = (uint32)(LddDefaultPeriod);
          /* Assign the configured value of the channel duty in to register */
          LpTomChCntrlRegs->ulCHxSR1 = Pwm_HW_GTM_CalculateDuty(LddDefaultPeriod, LddDefaultduty);
          /* CTRL Register setting */
          LulTempRegValue = PWM_DOUBLE_ZERO;
          /* polarity setting */
          if ((uint8)PWM_POLARITY_HIGH == LpChannelConfig->ucPolarity)
          {
            LulTempRegValue |= PWM_GTM_POLARITY_HIGH_VALUE;
            /* Load value into TOMCHxCTRLSR */
            LpTomChCntrlRegs->ulCHxCTRLSR |= PWM_GTM_POLARITY_HIGH_VALUE;
          }
          else
          {
            /* Load value into TOMCHxCTRLSR */
            LpTomChCntrlRegs->ulCHxCTRLSR &= ~PWM_GTM_POLARITY_HIGH_VALUE;
          }
          /* Load value into TOMCHxCTRLSR */
          LpTomChCntrlRegs->ulCHxCTRLSR |= ((uint32)LpChannelProp->ucChClockSelect << PWM_GTM_CLKSRC_SHIFT_NUM);
          /* Channel Clock source select */
          LulTempRegValue |= ((uint32)LpChannelProp->ucChClockSelect << PWM_GTM_CLKSRC_SHIFT_NUM);
          /* Enable FREEZE */
          LulTempRegValue |= PWM_GTM_CTRL_FREEZE_ONE;
          /* Set the TOMCHxCTRL */
          LpTomChCntrlRegs->ulCHxCTRL = LulTempRegValue;
        }
        #endif /* (PWM_GTM_ATOM_USED == STD_ON) */
      }
      
      #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
      #if (PWM_CLEAR_PENDING_INTERRUPT == STD_ON)
      /* Check if the Interrupt register is present for particular channel */
      if (NULL_PTR != LpChannelProp->pEICx_Address)
      {
        /* Clear pending interrupts with dummy read and execute syncp instruction */
        RH850_SV_CLEAR_ICR_SYNCP(16, LpChannelProp->pEICx_Address, PWM_CLEAR_PENDING_INTR_MASK);                        /* PRQA S 1006, 0499 # JV-01, JV-01 */
      
        /* TOM/ATOM Type */
        #if (PWM_GTM_ATOM_USED == STD_ON)
        if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                           /* PRQA S 1863 # JV-01 */
        {
          /* Clear the pending ISR request */
          LpAtomChCntrlRegs->ulCHxIRQNOTIFY = (uint32)(PWM_GTM_CYCLE_MATCH_MASK | PWM_GTM_DUTY_MATCH_MASK);             /* PRQA S 2962 # JV-01 */
        }
        else
        #endif /* End of #if (PWM_GTM_ATOM_USED == STD_ON)*/
        {
          #if (PWM_GTM_TOM_USED == STD_ON)
          /* Clear the pending ISR request */
          LpTomChCntrlRegs->ulCHxIRQNOTIFY = (uint32)(PWM_GTM_CYCLE_MATCH_MASK | PWM_GTM_DUTY_MATCH_MASK);              /* PRQA S 2962 # JV-01 */
          #endif /* End of #if (PWM_GTM_TOM_USED == STD_ON)*/
        }
      } /* Else no action */
      #endif /* (PWM_CLEAR_PENDING_INTERRUPT == STD_ON) */

      /* Set the Notification status as PWM_FALSE */
      Pwm_GaaNotifStatus[LucCount] = (uint8)PWM_FALSE;                                                                  /* PRQA S 4304 # JV-01 */
      #endif /* End of #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)*/
    }
  } 
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_InitUnit
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function. This function sets the clock pre-scaler,
**                         PWM mode, Period, Duty cycle and polarity for all configured channels.
**                         This function also disables the interrupts (Notifications) and resets the interrupt request
**                         pending flags.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddConfigPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpGTMUnitConfig, Pwm_GaaHWIP_Used
**
** Functions invoked     : None
**
** Registers Used        : AGCFUPDCTRL, AGCENDISCTRL, AGCOUTENCTRL, TGCFUPDCTRL, TGCENDISCTRL, TGCFUPDCTRL
**
** Reference ID          : PWM_DUD_ACT_101, PWM_DUD_ACT_101_REG001, PWM_DUD_ACT_101_REG002, PWM_DUD_ACT_101_REG003,
** Reference ID          : PWM_DUD_ACT_101_REG004, PWM_DUD_ACT_101_REG005, PWM_DUD_ACT_101_REG006
** Reference ID          : PWM_DUD_ACT_101_GBL001, PWM_DUD_ACT_101_GBL002
***********************************************************************************************************************/
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_GTM_InitUnit(P2CONST (Pwm_ConfigType, AUTOMATIC, PWM_CONFIG_DATA) LddConfigPtr)
{
  /* Pointer to Cluster configuration */
  P2CONST(Pwm_GTMUnitConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpClusterConfig;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Cluster control registers */
  P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Cluster control registers */
  P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  /* Local variable */
  uint32 LulTempGblCtrlRegValue;
  uint8 LucCount;
  uint8 LucHWIPType;

  /* Set the global GTM pointer */
  for (LucCount = (uint8)PWM_ZERO; LucCount < (uint8)PWM_TOTAL_HW_IP_CONFIG; LucCount++)
  {
    LucHWIPType = Pwm_GaaHWIP_Used[LucCount].ucIndex;
    if (PWM_HWIP_GTM == LucHWIPType)
    {
      /* Save the start of GTM Sub-block Unit Configuration in the global pointer */
      Pwm_GpGTMUnitConfig = (P2CONST(Pwm_GTMUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA))                          /* PRQA S 0316 # JV-01 */
        (LddConfigPtr->aaTimerUnitConfig[LucHWIPType]);
      break;
    } /* else No action required */
  }

  /* Loop to Initialize Cluster related attributes */
  for (LucCount = PWM_ZERO; LucCount < PWM_TOTAL_GTM_UNITS_CONFIG; LucCount++)                                          /* PRQA S 2877 # JV-01 */
  {
    /* Update the configure pointer to point to the current Cluster */
    LpClusterConfig = &Pwm_GpGTMUnitConfig[LucCount];
    /* TOM/ATOM Type */
    #if (PWM_GTM_ATOM_USED == STD_ON)
    if (PWM_GTM_ATOMTYPE == LpClusterConfig->ucTomAtomType)                                                             /* PRQA S 1863 # JV-01 */
    {
      /* Get the pointer to the PWM sub block control registers */
      LpAtomClusterRegs = (P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Call Global Control Register setting value */
      LulTempGblCtrlRegValue = (uint32)LpClusterConfig->usEnableChannelValue;
      /* Bitwise operation from & operator */
      /* Force update the CM0, CM1 and CLK for the channel */
      LpAtomClusterRegs->ulAGCFUPDCTRL = (uint32)LulTempGblCtrlRegValue;
      /* Enable the channel by updating ATOMiAGCENDISCTRL register */
      LpAtomClusterRegs->ulAGCENDISCTRL = (uint32)LulTempGblCtrlRegValue;
      /* Enable the output of channel by updating the ATOMiAGCOUTENCTRL register */
      LpAtomClusterRegs->ulAGCOUTENCTRL = (uint32)LulTempGblCtrlRegValue;
    }
    else
    #endif
    {
      #if (PWM_GTM_TOM_USED == STD_ON)
      /* Get the pointer to the PWM sub block control registers */
      LpTomClusterRegs = (P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Call Global Control Register setting value */
      LulTempGblCtrlRegValue = (uint32)LpClusterConfig->usEnableChannelValue;
      /* Bitwise operation from & operator */
      /* Force update the CM0, CM1 and CLK for the channel */
      LpTomClusterRegs->ulTGCFUPDCTRL = (uint32)LulTempGblCtrlRegValue;
      /* Enable the channel by updating TOMiTGCENDISCTRL register */
      LpTomClusterRegs->ulTGCENDISCTRL = (uint32)LulTempGblCtrlRegValue;
      /* Enable the output of channel by updating the TOMiTGCOUTENCTRL register */
      LpTomClusterRegs->ulTGCOUTENCTRL = (uint32)LulTempGblCtrlRegValue;
      #endif /* (PWM_GTM_ATOM_USED == STD_ON) */
    }
  }
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_StartOutput
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function. This function sets the clock pre-scaler,
**                         PWM mode, Period, Duty cycle and polarity for all configured channels.
**                         This function also disables the interrupts (Notifications) and resets the interrupt request
**                         pending flags.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpGTMUnitConfig
**
** Functions invoked     : None.
**
** Registers Used        : AGCGLBCTRL, AGCFUPDCTRL, TGCGLBCTRL, TGCFUPDCTRL
**
** Reference ID          : PWM_DUD_ACT_102, PWM_DUD_ACT_102_REG001, PWM_DUD_ACT_102_REG002, PWM_DUD_ACT_102_REG003,
** Reference ID          : PWM_DUD_ACT_102_REG004, PWM_DUD_ACT_102_GBL001
***********************************************************************************************************************/
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_GTM_StartOutput(void)
{
  /* Pointer to Cluster configuration */
  P2CONST(Pwm_GTMUnitConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpClusterConfig;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Cluster control registers */
  P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Cluster control registers */
  P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  /* Local variable */
  uint32 LulTempGblCtrlRegValue;
  uint8 LucCount;

  /* Loop to Initialize Cluster related attributes */
  for (LucCount = PWM_ZERO; LucCount < PWM_TOTAL_GTM_UNITS_CONFIG; LucCount++)                                          /* PRQA S 2877 # JV-01 */
  {
    /* Update the configure pointer to point to the current Cluster */
    LpClusterConfig = &Pwm_GpGTMUnitConfig[LucCount];
    /* TOM/ATOM Type */
    #if (PWM_GTM_ATOM_USED == STD_ON)
    if (PWM_GTM_ATOMTYPE == LpClusterConfig->ucTomAtomType)                                                             /* PRQA S 1863 # JV-01 */
    {
      /* Get the pointer to the PWM sub block control registers */
      LpAtomClusterRegs = (P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Call Global Control Register setting value */
      LulTempGblCtrlRegValue = (uint32)LpClusterConfig->usEnableChannelValue;
      /* Bitwise operation from & operator */
      /* Do not enable(start) channel configured as sync */
      LpAtomClusterRegs->ulAGCGLBCTRL = (((LulTempGblCtrlRegValue & (~(uint32)LpClusterConfig->usSyncChannelMask))
                                        << PWM_GTM_SHIFT_16)) | PWM_GTM_GLB_CTRL_HOST_TRIG_VALUE;
      /* Disable the force update */
      LpAtomClusterRegs->ulAGCFUPDCTRL = ~(uint32)LulTempGblCtrlRegValue;
    }
    else
    #endif
    {
      #if (PWM_GTM_TOM_USED == STD_ON)
      /* Get the pointer to the PWM sub block control registers */
      LpTomClusterRegs = (P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Call Global Control Register setting value */
      LulTempGblCtrlRegValue = (uint32)LpClusterConfig->usEnableChannelValue;
      /* Do not enable(start) channel configured as sync */
      LpTomClusterRegs->ulTGCGLBCTRL = (((LulTempGblCtrlRegValue & (~(uint32)LpClusterConfig->usSyncChannelMask))
                                       << PWM_GTM_SHIFT_16)) | PWM_GTM_GLB_CTRL_HOST_TRIG_VALUE;
      /* Disable the force update */
      LpTomClusterRegs->ulTGCFUPDCTRL = ~(uint32)LulTempGblCtrlRegValue;
      #endif /* (PWM_GTM_ATOM_USED == STD_ON) */
    }
  }
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_DeInitChannel
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function. This function de-initializes all the PWM
**                         channels by setting to their configured Idle state, disabling the notifications, resetting
**                         all the registers and stopping the PWM mode of operation of corresponding timer.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variable used  : Pwm_GpChannelConfig, Pwm_GaaNotifStatus
**                      
** Function(s) invoked   : None
**                      
** Registers Used        : EICx, ATOMiCHxCTRL, ATOMiCHxCTRLSR, ATOMiCHxSR0, ATOMiCHxSR1, ATOMiCHxCM0,
** Registers Used        : ATOMiCHxCM1, ATOMiHxIRQEN, ATOMiCHxIRQNOTIFY, TOMiCHxCTRL, TOMiCHxCTRLSR, TOMiCHxSR0,
** Registers Used        : TOMiCHxSR1, TOMiCHxCM0, TOMiCHxCM1, TOMiCHxIRQEN, TOMiCHxIRQNOTIFY, GTM_IRQ_SELxy,
** Registers Used        : AGCENDISSTAT, AGCOUTENSTAT, TGCENDISSTAT, TGCOUTENSTAT
**                      
** Reference ID           : PWM_DUD_ACT_103, PWM_DUD_ACT_103_REG001, PWM_DUD_ACT_103_REG002, PWM_DUD_ACT_103_REG003,
** Reference ID           : PWM_DUD_ACT_103_REG004, PWM_DUD_ACT_103_REG005, PWM_DUD_ACT_103_REG006
** Reference ID           : PWM_DUD_ACT_103_REG007, PWM_DUD_ACT_103_REG008, PWM_DUD_ACT_103_REG009
** Reference ID           : PWM_DUD_ACT_103_REG010, PWM_DUD_ACT_103_REG011, PWM_DUD_ACT_103_REG012
** Reference ID           : PWM_DUD_ACT_103_REG013, PWM_DUD_ACT_103_REG014, PWM_DUD_ACT_103_REG015
** Reference ID           : PWM_DUD_ACT_103_REG016, PWM_DUD_ACT_103_REG017, PWM_DUD_ACT_103_REG018
** Reference ID           : PWM_DUD_ACT_103_REG019, PWM_DUD_ACT_103_REG020, PWM_DUD_ACT_103_REG021
** Reference ID           : PWM_DUD_ACT_103_REG022, PWM_DUD_ACT_103_GBL001, PWM_DUD_ACT_103_GBL002
***********************************************************************************************************************/
#if (PWM_DE_INIT_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_GTM_DeInitChannel(void)                                                             /* PRQA S 3006 # JV-01 */
{
  /* Pointer to Cluster configuration */
  P2CONST(Pwm_GTMUnitConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpClusterConfig;
  /* Local Pointer used for each ATOM/TOM channel control registers */
  P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelProp;
  /* Local pointer to the each Gtm channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Cluster control registers */
  P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  /* Local Pointer used for TOM Channel control registers */
  P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Cluster control registers */
  P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  /* Local Pointer used for ATOM Channel control registers */
  P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  /* Local pointer to the Interrupt select configuration */
  uint8 LucCount;
  uint32 LucChShiftNum;

  /* Reset all channel register */
  for (LucCount = PWM_ZERO; LucCount < (uint8)PWM_TOTAL_CHANNELS_CONFIG; LucCount++)
  {
    if (PWM_HWIP_GTM == Pwm_GpChannelConfig[LucCount].ucTimerUnitType)                                                  /* PRQA S 3416 # JV-01 */
    {
      /* Update the con-fig pointer to point to the current Timer channel*/
      LpChannelConfig = &Pwm_GpChannelConfig[LucCount];
      /* Get the pointer to the PWM Channel properties */
      LpChannelProp = (P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST)) LpChannelConfig->pChannelProp;     /* PRQA S 0316 # JV-01 */
      
      #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
      #if (PWM_CLEAR_PENDING_INTERRUPT == STD_ON)
      /* Check if the Interrupt register is present for particular channel */
      if (NULL_PTR != LpChannelProp->pEICx_Address)
      {
        /* Clear pending interrupts with dummy read and execute syncp instruction */
        RH850_SV_CLEAR_ICR_SYNCP(16, LpChannelProp->pEICx_Address, PWM_CLEAR_PENDING_INTR_MASK);                        /* PRQA S 1006, 0499 # JV-01, JV-01 */
      }
      #endif

      #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
      /* Cluster Interrupt Control setting */
      if (NULL_PTR != LpChannelProp->pGTM_IRQ_SELxy)
      {
        /* ReSet Interrupt setting */
        *(LpChannelProp->pGTM_IRQ_SELxy) &= ~(LpChannelProp->ulGTM_IRQ_SELxyEnableValue);
      } /* No action required */
      #endif
      if (NULL_PTR != LpChannelProp->pEICx_Address)
      {
        RH850_SV_SET_ICR_SYNCP(8, LpChannelProp->pEICx_Address, PWM_DISABLE_INTR_MASK);                                 /* PRQA S 0751, 1006 # JV-01, JV-01 */
      } /* No action */
      /* Set the Notification status as PWM_FALSE */
      Pwm_GaaNotifStatus[LucCount] = (uint8)PWM_FALSE;                                                                  /* PRQA S 4304 # JV-01 */
      #endif

      /* Update the con-fig pointer to point to the current Timer sub block*/
      LpClusterConfig = &Pwm_GpGTMUnitConfig[LpChannelProp->ucTimerUnitIndex];
      #if (PWM_GTM_ATOM_USED == STD_ON)
      if (PWM_GTM_ATOMTYPE == LpClusterConfig->ucTomAtomType)                                                           /* PRQA S 1863 # JV-01 */
      {
        /* Get the pointer to the PWM sub block control registers */
        LpAtomClusterRegs = (P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE))                                        /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                                                               LpClusterConfig->pGtmTomATomClusterRegs;
        /* Get the pointer to the PWM Channel control registers */
        LpAtomChCntrlRegs = (P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
        /* Set polarity as the invert of idle level */
        if (PWM_LOW == LpChannelConfig->ucIdleLevel)                                                                    /* PRQA S 1881 # JV-01 */
        {
          /* CHxCTRL will not be reset after deinit to set the output to idle level */
          LpAtomChCntrlRegs->ulCHxCTRL |= PWM_GTM_POLARITY_HIGH_VALUE;
        }
        else
        {
          /* CHxCTRL will not be reset after deinit to set the output to idle level */
          LpAtomChCntrlRegs->ulCHxCTRL &= ~PWM_GTM_POLARITY_HIGH_VALUE;
        }
        /* Get the bit shift */
        LucChShiftNum = (uint32)(LpChannelProp->ucChannelNumber << PWM_ONE);                                            /* PRQA S 4391 # JV-01 */
        /* Disable the output of channel by updating the AGCENDISSTAT register */
        LpAtomClusterRegs->ulAGCENDISSTAT = (uint32)(PWM_GTM_CTRL_DISABLE << LucChShiftNum);
        /* Disable the output of channel by updating the AGCOUTENSTAT register */
        LpAtomClusterRegs->ulAGCOUTENSTAT = (uint32)(PWM_GTM_CTRL_DISABLE << LucChShiftNum);
        /* Reset channel register */
        #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
        LpAtomChCntrlRegs->ulCHxCTRLSR = PWM_DOUBLE_ZERO;
        #endif
        LpAtomChCntrlRegs->ulCHxSR0 = PWM_DOUBLE_ZERO;
        LpAtomChCntrlRegs->ulCHxSR1 = PWM_DOUBLE_ZERO;
        LpAtomChCntrlRegs->ulCHxCM0 = PWM_DOUBLE_ZERO;
        LpAtomChCntrlRegs->ulCHxCM1 = PWM_DOUBLE_ZERO;
        LpAtomChCntrlRegs->ulCHxIRQEN = PWM_DOUBLE_ZERO;
        LpAtomChCntrlRegs->ulCHxIRQNOTIFY = PWM_GTM_DUTY_CYCLE_MATCH_MASK;
      }
      else
      #endif
      {
        #if (PWM_GTM_TOM_USED == STD_ON)
        /* Get the pointer to the PWM sub block control registers */
        LpTomClusterRegs = (P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
        /* Get the pointer to the PWM Channel control registers */
        LpTomChCntrlRegs = (P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
        /* Set polarity as the invert of idle level*/
        if (PWM_LOW == LpChannelConfig->ucIdleLevel)                                                                    /* PRQA S 1881 # JV-01 */
        {
          /* CHxCTRL will not be reset after deinit to set the output to idle level */
          LpTomChCntrlRegs->ulCHxCTRL |= PWM_GTM_POLARITY_HIGH_VALUE;
        }
        else
        {
          /* CHxCTRL will not be reset after deinit to set the output to idle level */
          LpTomChCntrlRegs->ulCHxCTRL &= ~PWM_GTM_POLARITY_HIGH_VALUE;
        }
        /* Get the bit shift */
        LucChShiftNum = (uint32)(LpChannelProp->ucChannelNumber << PWM_ONE);                                            /* PRQA S 4391 # JV-01 */
        /* Disable the output of channel by updating the TGCENDISSTAT register */
        LpTomClusterRegs->ulTGCENDISSTAT = (uint32)(PWM_GTM_CTRL_DISABLE << LucChShiftNum);
        /* Disable the output of channel by updating the TGCOUTENSTAT register */
        LpTomClusterRegs->ulTGCOUTENSTAT = (uint32)(PWM_GTM_CTRL_DISABLE << LucChShiftNum);
        /* Reset channel register */
        LpTomChCntrlRegs->ulCHxCTRLSR = PWM_DOUBLE_ZERO;
        LpTomChCntrlRegs->ulCHxSR0 = PWM_DOUBLE_ZERO;
        LpTomChCntrlRegs->ulCHxSR1 = PWM_DOUBLE_ZERO;
        LpTomChCntrlRegs->ulCHxCM0 = PWM_DOUBLE_ZERO;
        LpTomChCntrlRegs->ulCHxCM1 = PWM_DOUBLE_ZERO;
        LpTomChCntrlRegs->ulCHxIRQEN = PWM_DOUBLE_ZERO;
        LpTomChCntrlRegs->ulCHxIRQNOTIFY = PWM_GTM_DUTY_CYCLE_MATCH_MASK;
        #endif
      }
    }
  }
}

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif 
/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_DeInitUnit
**                       
** Service ID            : NA
**                       
** Description           : This is PWM Driver Component support function. This function de-initializes all the PWM
**                         channels by setting to their configured Idle state, disabling the notifications, resetting
**                         all the registers and stopping the PWM mode of operation of corresponding timer.
**                       
** Sync/Async            : Synchronous
**                       
** Reentrancy            : Reentrant
**                       
** Input Parameters      : None
**                       
** InOut Parameters      : None
**                       
** Output Parameters     : None
**                       
** Return parameter      : None
**                       
** Pre-conditions        : NA
**                       
** Global Variable used  : Pwm_GpChannelConfig, Pwm_GpGTMUnitConfig
**                       
** Function(s) invoked   : None
**                       
** Registers Used        : AGCGLBCTRL, AGCOUTENCTRL, AGCENDISCTRL
** Registers Used        : TGCGLBCTRL, TGCOUTENCTRL, TGCENDISCTRL
**
** Reference ID          : PWM_DUD_ACT_127, PWM_DUD_ACT_127_REG001, PWM_DUD_ACT_127_REG002, PWM_DUD_ACT_127_REG003
** Reference ID          : PWM_DUD_ACT_127_REG005, PWM_DUD_ACT_127_REG006, PWM_DUD_ACT_127_REG007
** Reference ID          : PWM_DUD_ACT_127_GBL001, PWM_DUD_ACT_127_GBL002
***********************************************************************************************************************/
#if (PWM_DE_INIT_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_GTM_DeInitUnit(void)
{
  /* Pointer to Cluster configuration */
  P2CONST(Pwm_GTMUnitConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpClusterConfig;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Cluster control registers */
  P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Cluster control registers */
  P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  /* Local variable */
  uint8 LucCount;
  uint16 LucChannelMark;

  /* Loop to Initialize Cluster related attributes */
  for (LucCount = PWM_ZERO; LucCount < PWM_TOTAL_GTM_UNITS_CONFIG; LucCount++)                                          /* PRQA S 2877 # JV-01 */
  {
    /* Update the configure pointer to point to the current Cluster */
    LpClusterConfig = &Pwm_GpGTMUnitConfig[LucCount];
    /* TOM/ATOM Type */
    #if (PWM_GTM_ATOM_USED == STD_ON)
    if (PWM_GTM_ATOMTYPE == LpClusterConfig->ucTomAtomType)                                                             /* PRQA S 1863 # JV-01 */
    {
      /* Get the pointer to the PWM sub block control registers */
      LpAtomClusterRegs = (P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE))                                          /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                                                            LpClusterConfig->pGtmTomATomClusterRegs;
      /* Get channel mark */
      LucChannelMark = (LpClusterConfig->usEnableChannelValue | (LpClusterConfig->usEnableChannelValue >> PWM_ONE));
      /* Disable the channel by updating the AGCGLBCTRL register */
      LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((LucChannelMark & PWM_GTM_AGC_TGC_DIS_VALUE) << PWM_GTM_SHIFT_16);
      /* Disable the channel by updating the AGCENDISCTRL register */
      LpAtomClusterRegs->ulAGCENDISCTRL = (uint32)(LucChannelMark & PWM_GTM_AGC_TGC_DIS_VALUE);
      /* Disable the channel by updating the AGCOUTENCTRL register */
      LpAtomClusterRegs->ulAGCOUTENCTRL = (uint32)(LucChannelMark & PWM_GTM_AGC_TGC_DIS_VALUE);
    }
    else
    #endif
    {
      #if (PWM_GTM_TOM_USED == STD_ON)
      /* Get the pointer to the PWM sub block control registers */
      LpTomClusterRegs = (P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Get channel mark */
      LucChannelMark = (LpClusterConfig->usEnableChannelValue | (LpClusterConfig->usEnableChannelValue >> PWM_ONE));
      /* Disable the channel by updating the TGCGLBCTRL register */
      LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((LucChannelMark & PWM_GTM_AGC_TGC_DIS_VALUE) << PWM_GTM_SHIFT_16);
      /* Disable the channel by updating the TGCENDISCTRL register */
      LpTomClusterRegs->ulTGCENDISCTRL = (uint32)(LucChannelMark & PWM_GTM_AGC_TGC_DIS_VALUE);
      /* Disable the channel by updating the TGCOUTENCTRL register */
      LpTomClusterRegs->ulTGCOUTENCTRL = (uint32)(LucChannelMark & PWM_GTM_AGC_TGC_DIS_VALUE);
      #endif /* (PWM_GTM_ATOM_USED == STD_ON) */
    }
  }
}

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (PWM_DE_INIT_API == STD_ON)*/
/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_EnableNotification
**
** Service ID            : NA
**
** Description           : This routine is used to disable pending interrupts and enable Interrupt processing.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId, LenNotification
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpChannelConfig, Pwm_GaaNotifStatus
**
** Functions invoked     : None
**
** Registers Used        : ATOMiCHxIRQEN, ATOMiCHxIRQNOTIFY, TOMiCHxIRQEN, TOMiCHxIRQNOTIFY, EICx, GTM_IRQ_SELxy
**
** Reference ID          : PWM_DUD_ACT_104, PWM_DUD_ACT_104_REG001, PWM_DUD_ACT_104_REG002, PWM_DUD_ACT_104_REG003,
** Reference ID          : PWM_DUD_ACT_104_REG004, PWM_DUD_ACT_104_REG005, PWM_DUD_ACT_104_REG006
** Reference ID          : PWM_DUD_ACT_104_GBL001, PWM_DUD_ACT_104_GBL002, PWM_DUD_ACT_104_ERR001
** Reference ID          : PWM_DUD_ACT_104_CRT001, PWM_DUD_ACT_104_CRT002
***********************************************************************************************************************/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE)
                Pwm_HW_GTM_EnableNotification(Pwm_ChannelType LddChannelId, Pwm_EdgeNotificationType LenNotification)   /* PRQA S 3006 # JV-01 */
{
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Local Pointer used for each ATOM/TOM channel control registers */
  P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelProp;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Channel control registers */
  P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Channel control registers */
  P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  #endif

  /* Load the configure pointer */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];

  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  LucDetErrFlag = E_OK;

  if (NULL_PTR == LpChannelConfig->pPwmEdgeNotifPtr)
  {
    /* Report to DET module */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ENABLENOTIFICATION_SID, PWM_E_NOTIFY_NOTCONFIG);
    LucDetErrFlag = E_NOT_OK;
  } /* else No action required */

  if (E_OK == LucDetErrFlag)
  #endif
  {
    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    /* Get the pointer to the PWM Channel properties */
    LpChannelProp = (P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST)) LpChannelConfig->pChannelProp;       /* PRQA S 0316 # JV-01 */
    #if (PWM_GTM_ATOM_USED == STD_ON)
    if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                               /* PRQA S 1863 # JV-01 */
    {
      /* Get the pointer to the PWM Channel control registers */
      LpAtomChCntrlRegs = (P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Clear duty/cycle match interrupt */
      LpAtomChCntrlRegs->ulCHxIRQEN = PWM_DOUBLE_ZERO;
    }
    else
    #endif
    {
      #if (PWM_GTM_TOM_USED == STD_ON)
      /* Get the pointer to the PWM Channel control registers */
      LpTomChCntrlRegs = (P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;     /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Clear duty/cycle match interrupt */
      LpTomChCntrlRegs->ulCHxIRQEN = PWM_DOUBLE_ZERO;
      #endif
    }
    
    /* Condition to enable the interrupt for Rising or Both or falling edge in normal PWM signal OR */
    if (((PWM_POLARITY_HIGH == LpChannelConfig->ucPolarity) && (PWM_RISING_EDGE == LenNotification))
       || ((PWM_POLARITY_LOW == LpChannelConfig->ucPolarity) && (PWM_FALLING_EDGE == LenNotification)))
    {
      #if (PWM_GTM_ATOM_USED == STD_ON)
      if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                             /* PRQA S 1863 # JV-01 */
      {
        /* Enable duty/cycle match interrupt */
        LpAtomChCntrlRegs->ulCHxIRQEN = PWM_GTM_CYCLE_MATCH_MASK;                                                       /* PRQA S 2962 # JV-01 */
      }
      else
      #endif
      {
        #if (PWM_GTM_TOM_USED == STD_ON)
        /* Enable duty/cycle match interrupt */
        LpTomChCntrlRegs->ulCHxIRQEN = PWM_GTM_CYCLE_MATCH_MASK;                                                        /* PRQA S 2962 # JV-01 */
        #endif
      }
    }
    /* Condition to enable the interrupt for Falling or Both or falling edge in normal PWM signal */
    else if (((PWM_POLARITY_HIGH == LpChannelConfig->ucPolarity) && (PWM_FALLING_EDGE == LenNotification))
            || ((PWM_POLARITY_LOW == LpChannelConfig->ucPolarity) && (PWM_RISING_EDGE == LenNotification)))
    {
      #if (PWM_GTM_ATOM_USED == STD_ON)
      if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                             /* PRQA S 1863 # JV-01 */
      {
        /* Enable duty/cycle match interrupt */
        LpAtomChCntrlRegs->ulCHxIRQEN = PWM_GTM_DUTY_MATCH_MASK;
      }
      else
      #endif
      {
        #if (PWM_GTM_TOM_USED == STD_ON)
        /* Enable duty/cycle match interrupt */
        LpTomChCntrlRegs->ulCHxIRQEN = PWM_GTM_DUTY_MATCH_MASK;
        #endif
      }
    }
    else
    {
      #if (PWM_GTM_ATOM_USED == STD_ON)
      if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                             /* PRQA S 1863 # JV-01 */
      {
        /* Enable duty/cycle match interrupt */
        LpAtomChCntrlRegs->ulCHxIRQEN = PWM_GTM_DUTY_CYCLE_MATCH_MASK;
      }
      else
      #endif
      {
        #if (PWM_GTM_TOM_USED == STD_ON)
        /* Enable duty/cycle match interrupt */
        LpTomChCntrlRegs->ulCHxIRQEN = PWM_GTM_DUTY_CYCLE_MATCH_MASK;
        #endif
      }
    }
    
    #if (PWM_CLEAR_PENDING_INTERRUPT == STD_ON)
    /* TOM/ATOM Type */
    #if (PWM_GTM_ATOM_USED == STD_ON)
    if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                               /* PRQA S 1863 # JV-01 */
    {
      /* Clear the pending ISR request */
      LpAtomChCntrlRegs->ulCHxIRQNOTIFY = (uint32)PWM_GTM_DUTY_CYCLE_MATCH_MASK;                                        /* PRQA S 2962 # JV-01 */
    }
    else
    #endif
    {
      #if (PWM_GTM_TOM_USED == STD_ON)
      /* Clear the pending ISR request */
      LpTomChCntrlRegs->ulCHxIRQNOTIFY = (uint32)PWM_GTM_DUTY_CYCLE_MATCH_MASK;                                         /* PRQA S 2962 # JV-01 */
      #endif
    }
    #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
    /* Cluster Interrupt Control setting */
    if (NULL_PTR != LpChannelProp->pGTM_IRQ_SELxy)
    {
      /* ReSet Interrupt setting */
      *(LpChannelProp->pGTM_IRQ_SELxy) |= LpChannelProp->ulGTM_IRQ_SELxyEnableValue;
    } /* No action required */
    #endif
    #endif /* PWM_CLEAR_PENDING_INTERRUPT == STD_ON */
    if (NULL_PTR != LpChannelProp->pEICx_Address)
    {
      /* Enable the Interrupt processing of the current channel with dummy read and execute syncp instruction */
      RH850_SV_CLEAR_ICR_SYNCP(8, LpChannelProp->pEICx_Address, PWM_ENABLE_INTR_MASK);                                  /* PRQA S 0751, 1006 # JV-01, JV-01 */
    }
    /* Set the Notification status as PWM_TRUE */
    Pwm_GaaNotifStatus[LddChannelId] = (uint8)PWM_TRUE;                                                                 /* PRQA S 4304 # JV-01 */
    /* Exit Protected area */
    PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  }
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)*/
/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_DisableNotification
**
** Service ID            : NA
**
** Description           : This routine is used to disable Interrupt processing.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpChannelConfig, Pwm_GaaNotifStatus
**
** Functions invoked     : None
**
** Registers Used        : ATOMiCHxIRQEN, TOMiCHxIRQEN, EICx, GTM_IRQ_SELxy
**
** Reference ID          : PWM_DUD_ACT_105, PWM_DUD_ACT_105_REG001, PWM_DUD_ACT_105_REG002, PWM_DUD_ACT_105_REG003,
** Reference ID          : PWM_DUD_ACT_105_REG004, PWM_DUD_ACT_105_GBL001, PWM_DUD_ACT_105_GBL002
** Reference ID          : PWM_DUD_ACT_105_CRT001, PWM_DUD_ACT_105_CRT002
***********************************************************************************************************************/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_GTM_DisableNotification(Pwm_ChannelType LddChannelId)                               /* PRQA S 3006 # JV-01 */
{
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Local Pointer used for each ATOM/TOM channel control registers */
  P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelProp;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Channel control registers */
  P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Channel control registers */
  P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  /* Get the pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  LpChannelProp = (P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST)) LpChannelConfig->pChannelProp;         /* PRQA S 0316 # JV-01 */

  /* Enter Protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  #if (PWM_GTM_ATOM_USED == STD_ON)
  if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                                 /* PRQA S 1863 # JV-01 */
  {
    /* Get the pointer to the PWM Channel control registers */
    LpAtomChCntrlRegs = (P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;     /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Disable interrupt */
    LpAtomChCntrlRegs->ulCHxIRQEN = PWM_DOUBLE_ZERO;
  }
  else
  #endif
  {
    #if (PWM_GTM_TOM_USED == STD_ON)
    /* Get the pointer to the PWM Channel control registers */
    LpTomChCntrlRegs = (P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;       /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Disable interrupt */
    LpTomChCntrlRegs->ulCHxIRQEN = PWM_DOUBLE_ZERO;
    #endif
  }
  #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
  /* Cluster Interrupt Control setting */
  if (NULL_PTR != LpChannelProp->pGTM_IRQ_SELxy)
  {
    /* ReSet Interrupt setting */
    *(LpChannelProp->pGTM_IRQ_SELxy) &= ~(LpChannelProp->ulGTM_IRQ_SELxyEnableValue);
  } /* No action */
  #endif
  /* Set the Notification status as PWM_FALSE */
  Pwm_GaaNotifStatus[LddChannelId] = (uint8)PWM_FALSE;                                                                  /* PRQA S 4304 # JV-01 */
  /* Exit Protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)*/
/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_CalculateDuty
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This function Calculates Absolute duty for the PWM channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddAbsolutePeriod, LddRelativeDuty
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Pwm_PeriodType
**
** Pre-conditions        : NA
**
** Global Variables used : None
**
** Functions invoked     : None
**
** Registers Used        : None
**
** Reference ID          : PWM_DUD_ACT_106
***********************************************************************************************************************/

#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Pwm_PeriodType, PWM_PRIVATE_CODE)
                            Pwm_HW_GTM_CalculateDuty(Pwm_PeriodType LddAbsolutePeriod, Pwm_PeriodType LddRelativeDuty)  /* PRQA S 1505 # JV-01 */
{
  /* Local variable return value */
  VAR(Pwm_PeriodType, AUTOMATIC) LddAbsoluteDuty;
  VAR(Pwm_PeriodType, AUTOMATIC) LddCorrectionPeriod;

  /* Check if max cycle */
  if ((Pwm_PeriodType)PWM_MAX_DUTY_CYCLE_VALUE == LddRelativeDuty)
  {
    /* If Duty is 100%, Update value with the Cycle-Setting Register */
    LddAbsoluteDuty = LddAbsolutePeriod;
  }
  else if ((Pwm_PeriodType)PWM_MIN_DUTY_CYCLE_VALUE == LddRelativeDuty)
  {
    /* If Duty is 0%, Update 0x0000 value in the CDRm register */
    LddAbsoluteDuty = (Pwm_PeriodType)PWM_MIN_DUTY_CYCLE_VALUE;
  }
  else
  {
    if ((Pwm_PeriodType)PWM_PERIOD_LIMIT < LddAbsolutePeriod)
    {
      /* If Period > 0xFFFF and Duty is between 0x0000 and 0x8000 */
      LddCorrectionPeriod = LddAbsolutePeriod & (Pwm_PeriodType)PWM_CORRECTION_MASK;

      /* Duty Cycle scaling */
      LddAbsoluteDuty = (Pwm_PeriodType)(((LddAbsolutePeriod >> (Pwm_PeriodType)PWM_DUTY_CALC_DIV) * LddRelativeDuty)   /* PRQA S 3384 # JV-01 */
                         + ((LddCorrectionPeriod * LddRelativeDuty) >> (Pwm_PeriodType)PWM_DUTY_CALC_DIV));             /* PRQA S 3383, 3384 # JV-01, JV-01 */
    }
    else
    {
      /* If Duty is between 0x0000 and 0x8000 */
      /* AbsoluteDutyCycle = ((uint32)AbsolutePeriodTime * RelativeDutyCycle) >> 15 */
      LddAbsoluteDuty = (Pwm_PeriodType)((LddAbsolutePeriod * LddRelativeDuty) >> (Pwm_PeriodType)PWM_DUTY_CALC_DIV);   /* PRQA S 3383 # JV-01 */
    }
  }

  /* Return the duty value */
  return LddAbsoluteDuty;
}

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_SetOutputToIdle
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This function sets the output of a required channel to its configured Idle state.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpGTMUnitConfig, Pwm_GpChannelConfig
**
** Functions invoked     : None
**
** Registers Used        : AGCGLBCTRL, TGCGLBCTRL, ATOMiCHxCM1, TOMiCHxCTRL, TOMiCHxCM1
**
** Reference ID          : PWM_DUD_ACT_107, PWM_DUD_ACT_107_REG001, PWM_DUD_ACT_107_REG002, PWM_DUD_ACT_107_REG003,
** Reference ID          : PWM_DUD_ACT_107_REG004, PWM_DUD_ACT_107_REG005
** Reference ID          : PWM_DUD_ACT_107_GBL001, PWM_DUD_ACT_107_GBL002
** Reference ID          : PWM_DUD_ACT_107_CRT001, PWM_DUD_ACT_107_CRT002
***********************************************************************************************************************/
#if ((PWM_SET_OUTPUT_TO_IDLE_API == STD_ON) || (PWM_SYNC_START_SUPPORT == STD_ON))
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_GTM_SetOutputToIdle(Pwm_ChannelType LddChannelId)
{
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Pointer to Cluster configuration */
  P2CONST(Pwm_GTMUnitConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpClusterConfig;
  /* Local Pointer used for each ATOM/TOM channel control registers */
  P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelProp;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Cluster control registers */
  P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  /* Local Pointer used for TOM Channel control registers */
  P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Cluster control registers */
  P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  /* Local Pointer used for ATOM Channel control registers */
  P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  /* Global variable */
  uint32 LucChShiftNum;
  /* Get the pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  LpChannelProp = (P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST)) LpChannelConfig->pChannelProp;         /* PRQA S 0316 # JV-01 */
  /* Update the configure pointer to point to the current Cluster */
  LpClusterConfig = &Pwm_GpGTMUnitConfig[LpChannelProp->ucTimerUnitIndex];
  /* Get the bit shift */
  LucChShiftNum = (uint32)(LpChannelProp->ucChannelNumber << PWM_ONE);                                                  /* PRQA S 4391 # JV-01 */
  /* Enter Protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  /* TOM/ATOM Type */
  #if (PWM_GTM_ATOM_USED == STD_ON)
  if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                                 /* PRQA S 1863 # JV-01 */
  {
    /* Get the pointer to the PWM Channel control registers */
    LpAtomChCntrlRegs = (P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;     /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Get the pointer to the PWM Cluster control registers */
    LpAtomClusterRegs = (P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Disable the channel by updating GLB_CTRL register */
    LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((PWM_GTM_CTRL_DISABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
    /* Set polarity */
    #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
    if (PWM_LOW == LpChannelConfig->ucIdleLevel)                                                                        /* PRQA S 1881 # JV-01 */
    {
      /* Set the invert polarity */
      LpAtomChCntrlRegs->ulCHxCTRL |= PWM_GTM_POLARITY_HIGH_VALUE;
    }
    else
    {
      /* Set the invert polarity */
      LpAtomChCntrlRegs->ulCHxCTRL &= ~PWM_GTM_POLARITY_HIGH_VALUE;
    }
    /* Load value for CM1 during this period */
    LpAtomChCntrlRegs->ulCHxCM1 = PWM_DOUBLE_ZERO;
    #elif (PWM_GTM_VERSION == PWM_GTM_3_5_VERSION)
    if ((PWM_HIGH == LpChannelConfig->ucIdleLevel) &&                                                                   /* PRQA S 1881 # JV-01 */
       (PWM_GTM_POLARITY_HIGH_VALUE == (LpAtomChCntrlRegs->ulCHxCTRL & PWM_GTM_POLARITY_HIGH_VALUE)))                   /* PRQA S 1881 # JV-01 */
    {
       /* Load value for CM1 during this period */
       LpAtomChCntrlRegs->ulCHxCM1 = LpAtomChCntrlRegs->ulCHxCM0;
    }
    else if ((PWM_LOW == LpChannelConfig->ucIdleLevel) &&                                                               /* PRQA S 1881 # JV-01 */
       !(PWM_GTM_POLARITY_HIGH_VALUE == (LpAtomChCntrlRegs->ulCHxCTRL & PWM_GTM_POLARITY_HIGH_VALUE)))                  /* PRQA S 1881 # JV-01 */
    {
        /* Load value for CM1 during this period */
       LpAtomChCntrlRegs->ulCHxCM1 = LpAtomChCntrlRegs->ulCHxCM0;
    }
    else
    {
       /* Load value for CM1 during this period */
       LpAtomChCntrlRegs->ulCHxCM1 = PWM_DOUBLE_ZERO;
    }
    #endif
  }
  else
  #endif
  {
    #if (PWM_GTM_TOM_USED == STD_ON)
    /* Get the pointer to the PWM Channel control registers */
    LpTomChCntrlRegs = (P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;       /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Get the pointer to the PWM Cluster control registers */
    LpTomClusterRegs = (P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs;     /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Disable the channel by updating GLB_CTRL register */
    LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((PWM_GTM_CTRL_DISABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
    /* Set polarity */
    if (PWM_LOW == LpChannelConfig->ucIdleLevel)                                                                        /* PRQA S 1881 # JV-01 */
    {
      /* Set the invert polarity */
      LpTomChCntrlRegs->ulCHxCTRL |= PWM_GTM_POLARITY_HIGH_VALUE;
    }
    else
    {
      /* Set the invert polarity */
      LpTomChCntrlRegs->ulCHxCTRL &= ~PWM_GTM_POLARITY_HIGH_VALUE;
    }
    /* Load value for CM1 during this period */
    LpTomChCntrlRegs->ulCHxCM1 = PWM_DOUBLE_ZERO;
    #endif
  }
  /* Exit Protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
}

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)*/
/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_GetOutputState
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This function gets the output state of a PWM channel. (only Active and Slave)
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Pwm_OutputStateType
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpChannelConfig
**
** Functions invoked     : None
**
** Registers Used        : CHxSTAT
**
** Reference ID          : PWM_DUD_ACT_118, PWM_DUD_ACT_118_GBL001
***********************************************************************************************************************/
#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Pwm_OutputStateType, PWM_PRIVATE_CODE) Pwm_HW_GTM_GetOutputState(Pwm_ChannelType LddChannelId)
{
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Local Pointer used for each ATOM/TOM channel control registers */
  P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelProp;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Channel control registers */
  P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #endif /* End of #if (PWM_GTM_TOM_USED == STD_ON)*/
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Channel control registers */
  P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #endif /* End of #if (PWM_GTM_ATOM_USED == STD_ON)*/
  Pwm_OutputStateType LenRetOutputState;
  /* Get the pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  LpChannelProp = (P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST)) LpChannelConfig->pChannelProp;         /* PRQA S 0316 # JV-01 */

  /* TOM/ATOM Type */
  #if (PWM_GTM_ATOM_USED == STD_ON)
  if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                                 /* PRQA S 1863 # JV-01 */
  {
    /* Get the pointer to the PWM Channel control registers */
    LpAtomChCntrlRegs = (P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;     /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Condition to check the current output state of the channel */
    if (PWM_GTM_STAT_OL_MASK == (LpAtomChCntrlRegs->ulCHxSTAT & PWM_GTM_STAT_OL_MASK))
    {
      /* Get the output level */
      LenRetOutputState = PWM_HIGH;
    }
    else
    {
      /* Get the output level */
      LenRetOutputState = PWM_LOW;
    }
  }
  else
  #endif /* End of #if (PWM_GTM_ATOM_USED == STD_ON)*/
  {
    #if (PWM_GTM_TOM_USED == STD_ON)
    /* Get the pointer to the PWM Channel control registers */
    LpTomChCntrlRegs = (P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;       /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Condition to check the current output state of the channel */
    if (PWM_GTM_STAT_OL_MASK == (LpTomChCntrlRegs->ulCHxSTAT & PWM_GTM_STAT_OL_MASK))
    {
      /* Get the output level */
      LenRetOutputState = PWM_HIGH;
    }
    else
    {
      /* Get the output level */
      LenRetOutputState = PWM_LOW;
    }
    #endif /* End of #if (PWM_GTM_TOM_USED == STD_ON)*/
  }
  return (LenRetOutputState);                                                                                           /* PRQA S 2962 # JV-01 */
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (PWM_GET_OUTPUT_STATE_API == STD_ON)*/

#if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_SetChannelOutput
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This function sets the output of a channel to constant signal for current period.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId
**                         LenState
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpGTMUnitConfig, Pwm_GpChannelConfig.
**
** Functions invoked     : None
**
** Registers Used        : AGCGLBCTRL, TGCGLBCTRL, ATOMiCHxCTRL,  ATOMiCHxCM1, TOMiCHxCTRL,  TOMiCHxCM1
**
** Reference ID          : PWM_DUD_ACT_126, PWM_DUD_ACT_126_REG001, PWM_DUD_ACT_126_REG002, PWM_DUD_ACT_126_REG003,
** Reference ID          : PWM_DUD_ACT_126_REG004, PWM_DUD_ACT_126_REG005, PWM_DUD_ACT_126_REG006, 
** Reference ID          : PWM_DUD_ACT_126_CRT001, PWM_DUD_ACT_126_CRT002,
** Reference ID          : PWM_DUD_ACT_126_GBL001, PWM_DUD_ACT_126_GBL002
***********************************************************************************************************************/
#if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_GTM_SetChannelOutput(Pwm_ChannelType LddChannelId, Pwm_OutputStateType LenState)
{
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Pointer to Cluster configuration */
  P2CONST(Pwm_GTMUnitConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpClusterConfig;
  /* Local Pointer used for each ATOM/TOM channel control registers */
  P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelProp;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Cluster control registers */
  P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  /* Local Pointer used for TOM Channel control registers */
  P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Cluster control registers */
  P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  /* Local Pointer used for ATOM Channel control registers */
  P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  /* Global variable */
  uint32 LucChShiftNum;
  /* Get the pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  LpChannelProp = (P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST)) LpChannelConfig->pChannelProp;         /* PRQA S 0316 # JV-01 */
  /* Update the configure pointer to point to the current Cluster */
  LpClusterConfig = &Pwm_GpGTMUnitConfig[LpChannelProp->ucTimerUnitIndex];
  /* Get the bit shift */
  LucChShiftNum = (uint32)(LpChannelProp->ucChannelNumber << PWM_ONE);                                                  /* PRQA S 4391 # JV-01 */
  /* Enter Protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  /* TOM/ATOM Type */
  #if (PWM_GTM_ATOM_USED == STD_ON)
  if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                                 /* PRQA S 1863 # JV-01 */
  {
    /* Get the pointer to the PWM Channel control registers */
    LpAtomChCntrlRegs = (P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;     /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Get the pointer to the PWM Cluster control registers */
    LpAtomClusterRegs = (P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Disable the channel by updating GLB_CTRL register */
    LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((PWM_GTM_CTRL_DISABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
    /* Set polarity */
    if (PWM_LOW == LenState)
    {
      /* Set the invert polarity */
      LpAtomChCntrlRegs->ulCHxCTRL |= PWM_GTM_POLARITY_HIGH_VALUE;
    }
    else
    {
      /* Set the invert polarity */
      LpAtomChCntrlRegs->ulCHxCTRL &= ~PWM_GTM_POLARITY_HIGH_VALUE;
    }
    /* Load value for CM1 during this period */
    LpAtomChCntrlRegs->ulCHxCM1 = PWM_DOUBLE_ZERO;
    /* Enable the channel by updating GLB_CTRL register */
    LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((PWM_GTM_CTRL_ENABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
  }
  else
  #endif /* End of #if (PWM_GTM_ATOM_USED == STD_ON)*/
  {
    #if (PWM_GTM_TOM_USED == STD_ON)
    /* Get the pointer to the PWM Channel control registers */
    LpTomChCntrlRegs = (P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;       /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Get the pointer to the PWM Cluster control registers */
    LpTomClusterRegs = (P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs;     /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Disable the channel by updating GLB_CTRL register */
    LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((PWM_GTM_CTRL_DISABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
    /* Set polarity */
    if (PWM_LOW == LenState)
    {
      /* Set the invert polarity */
      LpTomChCntrlRegs->ulCHxCTRL |= PWM_GTM_POLARITY_HIGH_VALUE;
    }
    else
    {
      /* Set the invert polarity */
      LpTomChCntrlRegs->ulCHxCTRL &= ~PWM_GTM_POLARITY_HIGH_VALUE;
    }
    /* Load value for CM1 during this period */
    LpTomChCntrlRegs->ulCHxCM1 = PWM_DOUBLE_ZERO;
    /* Enable the channel by updating GLB_CTRL register */
    LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((PWM_GTM_CTRL_ENABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
    #endif /* End of #if (PWM_GTM_TOM_USED == STD_ON)*/
  }
  /* Exit Protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)*/
#endif
/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_SetDutyCycle
**                      
** Service ID            : NA
**                      
** Description           : This is PWM Driver Component support function.
**                         This function updates the duty cycle counter value in the hardware registers.
**                      
** Sync/Async            : Synchronous
**                      
** Reentrancy            : Reentrant
**                      
** Input Parameters      : LddChannelId and LusDutyCycle
**                      
** InOut Parameters      : None
**                      
** Output Parameters     : None
**                      
** Return parameter      : None
**                      
** Pre-conditions        : NA
**                      
** Global Variable used  : Pwm_GpGTMUnitConfig, Pwm_GpChannelConfig
**                      
** Functions invoked     : Pwm_HW_GTM_CalculateDuty
**                      
** Registers Used        : AGCGLBCTRL, AGCENDISSTAT, TGCGLBCTRL, TGCENDISSTAT, ATOMiCHxSR1, ATOMiCHxCN0, GTM_IRQ_SELxy
** Registers Used        : TOMiCHxSR1, TOMiCHxCN0
**                      
** Reference ID           : PWM_DUD_ACT_124, PWM_DUD_ACT_124_REG001, PWM_DUD_ACT_124_REG002, PWM_DUD_ACT_124_REG003,
** Reference ID           : PWM_DUD_ACT_124_REG004, PWM_DUD_ACT_124_REG005, PWM_DUD_ACT_124_REG006
** Reference ID           : PWM_DUD_ACT_124_REG007, PWM_DUD_ACT_124_REG008, PWM_DUD_ACT_124_REG009
** Reference ID           : PWM_DUD_ACT_124_GBL001, PWM_DUD_ACT_124_GBL002
** Reference ID           : PWM_DUD_ACT_124_CRT001, PWM_DUD_ACT_124_CRT002
***********************************************************************************************************************/
#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_GTM_SetDutyCycle(Pwm_ChannelType LddChannelId, uint16 LusDutyCycle)
{
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Pointer to Cluster configuration */
  P2CONST(Pwm_GTMUnitConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpClusterConfig;
  /* Local Pointer used for each ATOM/TOM channel control registers */
  P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelProp;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Cluster control registers */
  P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  /* Local Pointer used for TOM Channel control registers */
  P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Cluster control registers */
  P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  /* Local Pointer used for ATOM Channel control registers */
  P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  /* local variable for shift value of AGC/TGC register value */
  uint8 LucChShiftNum;
  /* local variable for DefaultPeriod */
  Pwm_PeriodType LddDefaultPeriod;
  /* local variable for new Duty tick */
  Pwm_PeriodType LddDefaultDuty;
  /* local variable for period shift */
  Pwm_PeriodType LddPeriodShift;

  /* Get the pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  LpChannelProp = (P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST)) LpChannelConfig->pChannelProp;         /* PRQA S 0316 # JV-01 */
  LpClusterConfig = &Pwm_GpGTMUnitConfig[LpChannelProp->ucTimerUnitIndex];

  /* Enter Protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

  /* ATOM Type */
  #if (PWM_GTM_ATOM_USED == STD_ON)
  if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                                 /* PRQA S 1863 # JV-01 */
  {
    /* Get the pointer to the PWM Channel control registers */
    LpAtomChCntrlRegs = (P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;     /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Get the pointer to the PWM Cluster control registers */
    LpAtomClusterRegs = (P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Assign the configured value of the channel period in to register */
    LddDefaultPeriod = LpAtomChCntrlRegs->ulCHxSR0;
    /* Get the bit shift */
    LucChShiftNum = LpChannelProp->ucChannelNumber << PWM_ONE;
    /* Disable the channel by updating GLB_CTRL register */
    LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((PWM_GTM_CTRL_DISABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
    LddDefaultDuty = (uint32)Pwm_HW_GTM_CalculateDuty(LddDefaultPeriod, (Pwm_PeriodType)LusDutyCycle);
    /* Assign the relative duty cycle */
    LpAtomChCntrlRegs->ulCHxSR1 = LddDefaultDuty;
    /* Shift the period by the default configured value */
    if(PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
    {
      /* Stop the counter */
      LpAtomClusterRegs->ulAGCENDISSTAT = PWM_GTM_CTRL_DISABLE << LucChShiftNum;
      /* Calculate shift period */
      LddPeriodShift = Pwm_HW_GTM_CalculateDuty(LddDefaultPeriod, LpChannelProp->usPeriodShift);
      /* Shift the period by the default configured value */
      LpAtomChCntrlRegs->ulCHxCN0 = LddDefaultPeriod - LddPeriodShift;                                                  /* PRQA S 3383 # JV-01 */
      /* Start the counter */
      LpAtomClusterRegs->ulAGCENDISSTAT = PWM_GTM_CTRL_ENABLE << LucChShiftNum;
    } /* Else no require */
    /* Enable the channel by updating GLB_CTRL register */
    LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((PWM_GTM_CTRL_ENABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
  }
  else
  #endif
  {
    #if (PWM_GTM_TOM_USED == STD_ON)
    /* Get the pointer to the PWM Channel control registers */
    LpTomChCntrlRegs = (P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;       /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Assign the configured value of the channel period in to register */
    LddDefaultPeriod = LpTomChCntrlRegs->ulCHxSR0;
    /* Get the pointer to the PWM Cluster control registers */
    LpTomClusterRegs = (P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs;     /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Get the bit shift */
    LucChShiftNum = LpChannelProp->ucChannelNumber << PWM_ONE;
    /* Disable the channel by updating GLB_CTRL register */
    LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((PWM_GTM_CTRL_DISABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
    LddDefaultDuty = (uint32)Pwm_HW_GTM_CalculateDuty(LddDefaultPeriod, (Pwm_PeriodType)LusDutyCycle);
    /* Assign the relative duty cycle */
    LpTomChCntrlRegs->ulCHxSR1 = LddDefaultDuty;
    /* Shift the period by the default configured value */
    if(PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
    {
      /* Stop the counter */
      LpTomClusterRegs->ulTGCENDISSTAT = PWM_GTM_CTRL_DISABLE << LucChShiftNum;
      /* Calculate shift period */
      LddPeriodShift = Pwm_HW_GTM_CalculateDuty(LddDefaultPeriod, LpChannelProp->usPeriodShift);
      /* Shift the period by the default configured value */
      LpTomChCntrlRegs->ulCHxCN0 = LddDefaultPeriod - LddPeriodShift;                                                   /* PRQA S 3383 # JV-01 */
      /* Start the counter */
      LpTomClusterRegs->ulTGCENDISSTAT = PWM_GTM_CTRL_ENABLE << LucChShiftNum;
    } /* Else no require */
    /* Enable the channel by updating GLB_CTRL register */
    LpTomClusterRegs->ulTGCGLBCTRL =  (uint32)((PWM_GTM_CTRL_ENABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
    #endif /* End of #if (PWM_GTM_TOM_USED == STD_ON)*/
  }
  #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
  /* Re-enable notification after idle */
  #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
  /* Check if Notification status is enabled for this channel */
  if (PWM_TRUE == Pwm_GaaNotifStatus[LddChannelId])                                                                     /* PRQA S 1881 # JV-01 */
  {
    /* Cluster Interrupt Control setting */
    if (NULL_PTR != LpChannelProp->pGTM_IRQ_SELxy)
    {
      /* Reset Interrupt setting */
      *(LpChannelProp->pGTM_IRQ_SELxy) |= LpChannelProp->ulGTM_IRQ_SELxyEnableValue;
    } /* No action */
  } /* No action */
  #endif /* End of #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)*/
  #endif
  /* Exit Protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (PWM_SET_DUTY_CYCLE_API == STD_ON)*/
/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_SetPeriodAndDuty
**
** Service ID            : NA
**                      
** Description           : This is PWM Driver Component support function.
**                         This function updates the Period and Duty cycle counter value in the hardware registers.
**                      
** Sync/Async            : Synchronous
**                      
** Reentrancy            : Reentrant
**                      
** Input Parameters      : LddChannelId, LddSetPeriod and LusSetDutyCycle
**                      
** InOut Parameters      : None
**                      
** Output Parameters     : None
**                      
** Return parameter      : None
**                      
** Pre-conditions        : NA
**                      
** Global Variable used  : Pwm_GpGTMUnitConfig, Pwm_GpChannelConfig, Pwm_GaaNotifStatus
**                      
** Function invoked      : Det_ReportError, Pwm_HW_GTM_CalculateDuty
**                      
** Registers Used        : AGCGLBCTRL, TGCGLBCTRL, ATOMiCHxSR0, ATOMiCHxSR1, TOMiCHxSR0, TOMiCHxSR1, GTM_IRQ_SELxy
**
** Reference ID          : PWM_DUD_ACT_125, PWM_DUD_ACT_125_REG001, PWM_DUD_ACT_125_REG002, PWM_DUD_ACT_125_REG003,
** Reference ID          : PWM_DUD_ACT_125_REG004, PWM_DUD_ACT_125_REG005, PWM_DUD_ACT_125_REG006
** Reference ID          : PWM_DUD_ACT_125_GBL001, PWM_DUD_ACT_125_GBL002, PWM_DUD_ACT_125_GBL003
** Reference ID          : PWM_DUD_ACT_125_REG007, PWM_DUD_ACT_125_CRT001, PWM_DUD_ACT_125_CRT002
** Reference ID          : PWM_DUD_ACT_125_ERR001, PWM_DUD_ACT_125_ERR002
***********************************************************************************************************************/
#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE)
      Pwm_HW_GTM_SetPeriodAndDuty(Pwm_ChannelType LddChannelId, Pwm_PeriodType LddSetPeriod, uint16 LusSetDutyCycle)
{
  /* Local pointer to the each channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Local pointer to Cluster configuration */
  P2CONST(Pwm_GTMUnitConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpClusterConfig;
  /* Local Pointer used for each ATOM/TOM channel control registers */
  P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelProp;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Cluster control registers */
  P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
    /* Local Pointer used for TOM Channel control registers */
  P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif /* End of #if (PWM_GTM_TOM_USED == STD_ON)*/
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Cluster control registers */
  P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  /* Local Pointer used for ATOM Channel control registers */
  P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif /* End of #if (PWM_GTM_ATOM_USED == STD_ON)*/
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  #endif
  /* Local variable for shift value of AGC/TGC register value */
  uint8 LucChShiftNum;

  /* Update the configure pointer */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  LpChannelProp = (P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST)) LpChannelConfig->pChannelProp;         /* PRQA S 0316 # JV-01 */
  LpClusterConfig = &Pwm_GpGTMUnitConfig[LpChannelProp->ucTimerUnitIndex];
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Initialize DET error flag */
  LucDetErrFlag = E_OK;

  #if (PWM_GTM_ATOM_USED == STD_ON)
  if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                                 /* PRQA S 1863 # JV-01 */
  {
    if (((Pwm_PeriodType)PWM_TWO > LddSetPeriod) || ((Pwm_PeriodType)PWM_ATOM_MAX_COUNTER_VALUE < LddSetPeriod))
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_PERIODANDDUTY_SID, PWM_E_PARAM_VALUE);
      LucDetErrFlag = E_NOT_OK;
    }
  }
  else
  #endif /* End of #if (PWM_GTM_ATOM_USED == STD_ON)*/
  {
    #if (PWM_GTM_TOM_USED == STD_ON)
    if (((Pwm_PeriodType)PWM_TWO > LddSetPeriod) || ((Pwm_PeriodType)PWM_TOM_MAX_COUNTER_VALUE < LddSetPeriod))
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_PERIODANDDUTY_SID, PWM_E_PARAM_VALUE);
      LucDetErrFlag = E_NOT_OK;
    }
    #endif /* End of #if (PWM_GTM_TOM_USED == STD_ON)*/
  }

  if (E_OK == LucDetErrFlag)
  #endif /* (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    /* TOM/ATOM Type */
    #if (PWM_GTM_ATOM_USED == STD_ON)
    if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                               /* PRQA S 1863 # JV-01 */
    {
      /* Get the pointer to the PWM Channel control registers */
      LpAtomChCntrlRegs = (P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Get the pointer to the PWM Cluster control registers */
      LpAtomClusterRegs = (P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Get the bit shift */
      LucChShiftNum = LpChannelProp->ucChannelNumber << PWM_ONE;
      /* Disable the channel by updating GLB_CTRL register */
      LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((PWM_GTM_CTRL_DISABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
      /* Assign the relative period cycle */
      LpAtomChCntrlRegs->ulCHxSR0 = LddSetPeriod;
      /* Assign the relative duty cycle */
      LpAtomChCntrlRegs->ulCHxSR1 = (uint32)Pwm_HW_GTM_CalculateDuty(LddSetPeriod, (Pwm_PeriodType)LusSetDutyCycle);
      /* Enable the channel by updating GLB_CTRL register */
      LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((PWM_GTM_CTRL_ENABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
    }
    else
    #endif /* End of #if (PWM_GTM_ATOM_USED == STD_ON)*/
    {
      #if (PWM_GTM_TOM_USED == STD_ON)
      /* Get the pointer to the PWM Channel control registers */
      LpTomChCntrlRegs = (P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;     /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Get the pointer to the PWM Cluster control registers */
      LpTomClusterRegs = (P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Get the bit shift */
      LucChShiftNum = LpChannelProp->ucChannelNumber << PWM_ONE;
      /* Disable the channel by updating GLB_CTRL register */
      LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((PWM_GTM_CTRL_DISABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
      /* Assign the relative period cycle */
      LpTomChCntrlRegs->ulCHxSR0 = LddSetPeriod;
      /* Assign the relative duty cycle */
      LpTomChCntrlRegs->ulCHxSR1 = (uint32)Pwm_HW_GTM_CalculateDuty(LddSetPeriod, (Pwm_PeriodType)LusSetDutyCycle);
      /* Enable the channel by updating GLB_CTRL register */
      LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((PWM_GTM_CTRL_ENABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
      #endif /* End of #if (PWM_GTM_TOM_USED == STD_ON)*/
    }
    #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
    /* Re-enable notification after idle */
    #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
    /* Check if Notification status is enabled for this channel */
    if (PWM_TRUE == Pwm_GaaNotifStatus[LddChannelId])                                                                   /* PRQA S 1881 # JV-01 */
    {
        /* Cluster Interrupt Control setting */
      if (NULL_PTR != LpChannelProp->pGTM_IRQ_SELxy)
      {
        /* ReSet Interrupt setting */
        *(LpChannelProp->pGTM_IRQ_SELxy) |= LpChannelProp->ulGTM_IRQ_SELxyEnableValue;
      } /* No action */
    } /* No action */
    #endif /* End of #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)*/
    #endif
    /* Exit Protected area */
    PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  }
}

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)*/
/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_SynchronousInit
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This routine starts all PWM channels configured to synchronous start/stop of timers.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpChannelConfig
**
** Functions invoked     : Pwm_HW_GTM_CalculateDuty
**
** Registers Used        : ATOMiCHxCN0, ATOMiCHxSR0, ATOMiCHxSR1, ATOMiCHxCTRLSR, ATOMiCHxCTRL
** Registers Used        : TOMiCHxCN0, TOMiCHxSR0, TOMiCHxSR1, TOMiCHxCTRLSR, TOMiCHxCTRL
**
** Reference ID          : PWM_DUD_ACT_119, PWM_DUD_ACT_119_REG001, PWM_DUD_ACT_119_REG002, PWM_DUD_ACT_119_REG003,
** Reference ID          : PWM_DUD_ACT_119_REG004, PWM_DUD_ACT_119_REG005, PWM_DUD_ACT_119_REG006,
** Reference ID          : PWM_DUD_ACT_119_REG007, PWM_DUD_ACT_119_REG008, PWM_DUD_ACT_119_REG009,
** Reference ID          : PWM_DUD_ACT_119_REG010, PWM_DUD_ACT_119_GBL001, PWM_DUD_ACT_119_CRT001,
** Reference ID          : PWM_DUD_ACT_119_CRT002
***********************************************************************************************************************/
#if (PWM_SYNC_START_SUPPORT == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_GTM_SynchronousInit(void)
{
  /* Local pointer to the each Gtm channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Local Pointer used for each ATOM/TOM channel control registers */
  P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelProp;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Channel control registers */
  P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Channel control registers */
  P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  /* Local variable*/
  Pwm_PeriodType LddDefaultPeriod;
  Pwm_PeriodType LddDefaultduty;
  Pwm_PeriodType LddPeriodShift;
  uint8 LucCount;
  uint32 LulTempRegValue;

  /* Enter Protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);
  /* Loop to set the attributes of Gtm channels */
  for (LucCount = PWM_ZERO; LucCount < PWM_TOTAL_CHANNELS_CONFIG; LucCount++)
  {
    if (PWM_HWIP_GTM == Pwm_GpChannelConfig[LucCount].ucTimerUnitType)                                                  /* PRQA S 3416 # JV-01 */
    {
      /* Update channel configure data pointer */
      LpChannelConfig = &Pwm_GpChannelConfig[LucCount];
      /* Get the pointer to the PWM Channel properties */
      LpChannelProp = (P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST)) LpChannelConfig->pChannelProp;     /* PRQA S 0316 # JV-01 */
      /* TOM/ATOM Type */
      #if (PWM_GTM_ATOM_USED == STD_ON)
      if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                             /* PRQA S 1863 # JV-01 */
      {
        #if (PWM_SYNC_START_SUPPORT == STD_ON)
        if (PWM_TRUE == LpChannelConfig->blSyncStartReq)
        #endif
        {
          /* Get the pointer to the PWM Channel control registers */
          LpAtomChCntrlRegs =
                           (P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;  /* PRQA S 0316, 3432 # JV-01, JV-01 */
          /* Get value of the channel period in local variable */
          LddDefaultPeriod = LpChannelProp->ddDefault_Period;
          /* Get value of the channel duty in local variable */
          LddDefaultduty = LpChannelProp->ddDefault_Duty;
          /* Set the output delay */
          if (PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
          {
            /* Calculate shift period */
            LddPeriodShift = Pwm_HW_GTM_CalculateDuty(LddDefaultPeriod, LpChannelProp->usPeriodShift);
            /* Initial the delay of the pulse */
            LpAtomChCntrlRegs->ulCHxCN0 = LddDefaultPeriod - LddPeriodShift;                                            /* PRQA S 3383 # JV-01 */
          }
          else
          {
            /* Output immediately after channel started */
            LpAtomChCntrlRegs->ulCHxCN0 = LddDefaultPeriod;
          }
          /* Assign the configured value of the channel duty in to register */
          LpAtomChCntrlRegs->ulCHxSR1 = Pwm_HW_GTM_CalculateDuty(LddDefaultPeriod, LddDefaultduty);
          /* Load the period value to reload period register */
          LpAtomChCntrlRegs->ulCHxSR0 = (uint32)(LddDefaultPeriod);
          LulTempRegValue = PWM_DOUBLE_ZERO;
          /* Set polarity */
          if ((uint8)PWM_POLARITY_HIGH == LpChannelConfig->ucPolarity)
          {
            LulTempRegValue |= PWM_GTM_POLARITY_HIGH_VALUE;
            #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
            /* Load value into ATOMCHxCTRLSR */
            LpAtomChCntrlRegs->ulCHxCTRLSR |= PWM_GTM_POLARITY_HIGH_VALUE;
          }
          else
          {
            /* Load value into ATOMCHxCTRLSR */
            LpAtomChCntrlRegs->ulCHxCTRLSR &= ~PWM_GTM_POLARITY_HIGH_VALUE;
            #endif
          }
          #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
          /* Load value into ATOMCHxCTRLSR */
          LpAtomChCntrlRegs->ulCHxCTRLSR |= ((uint32)LpChannelProp->ucChClockSelect << PWM_GTM_CLKSRC_SHIFT_NUM);
          #endif
          /* Channel Clock source select */
          LulTempRegValue |= ((uint32)LpChannelProp->ucChClockSelect << PWM_GTM_CLKSRC_SHIFT_NUM);
          /* MODE select */
          LulTempRegValue |= PWM_GTM_MODE_SOMP_VALUE;
          /* Enable FREEZE */
          LulTempRegValue |= PWM_GTM_CTRL_FREEZE_ONE;
          /* Load value into ATOMCHxCTRL */
          LpAtomChCntrlRegs->ulCHxCTRL = LulTempRegValue;
        } /* Else no action required */
      }
      else
      #endif
      {
        #if (PWM_GTM_TOM_USED == STD_ON)
        #if (PWM_SYNC_START_SUPPORT == STD_ON)
        if (PWM_TRUE == LpChannelConfig->blSyncStartReq)
        #endif
        {
          /* Get the pointer to the PWM Channel control registers */
          LpTomChCntrlRegs = (P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
          /* Get value of the channel period in local variable */
          LddDefaultPeriod = LpChannelProp->ddDefault_Period;
          /* Get value of the channel duty in local variable */
          LddDefaultduty = LpChannelProp->ddDefault_Duty;
          /* Set the output delay */
          if (PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
          {
            /* Calculate shift period */
            LddPeriodShift = Pwm_HW_GTM_CalculateDuty(LddDefaultPeriod, LpChannelProp->usPeriodShift);
            /* Initial the delay of the pulse */
            LpTomChCntrlRegs->ulCHxCN0 = LddDefaultPeriod - LddPeriodShift;                                             /* PRQA S 3383 # JV-01 */
          }
          else
          {
            /* Output immediately after channel started */
            LpTomChCntrlRegs->ulCHxCN0 = LddDefaultPeriod;
          }
          /* Assign the configured value of the channel period in to register */
          LpTomChCntrlRegs->ulCHxSR0 = (uint32)(LddDefaultPeriod);
          /* Assign the configured value of the channel duty in to register */
          LpTomChCntrlRegs->ulCHxSR1 = Pwm_HW_GTM_CalculateDuty(LddDefaultPeriod, LddDefaultduty);
          /* CTRL Register setting */
          LulTempRegValue = PWM_DOUBLE_ZERO;
          /* polarity setting */
          if ((uint8)PWM_POLARITY_HIGH == LpChannelConfig->ucPolarity)
          {
            LulTempRegValue |= PWM_GTM_POLARITY_HIGH_VALUE;
            /* Load value into CHxCTRLSR */
            LpTomChCntrlRegs->ulCHxCTRLSR |= PWM_GTM_POLARITY_HIGH_VALUE;
          }
          else
          {
            /* Load value into CHxCTRLSR */
            LpTomChCntrlRegs->ulCHxCTRLSR &= ~PWM_GTM_POLARITY_HIGH_VALUE;
          }
          /* Load value into CHxCTRLSR */
          LpTomChCntrlRegs->ulCHxCTRLSR |= ((uint32)LpChannelProp->ucChClockSelect << PWM_GTM_CLKSRC_SHIFT_NUM);
          /* Channel Clock source select */
          LulTempRegValue |= ((uint32)LpChannelProp->ucChClockSelect << PWM_GTM_CLKSRC_SHIFT_NUM);
          /* Enable FREEZE */
          LulTempRegValue |= PWM_GTM_CTRL_FREEZE_ONE;
          /* Set the TOMCHxCTRL */
          LpTomChCntrlRegs->ulCHxCTRL = LulTempRegValue;
        }
        #endif /* (PWM_GTM_TOM_USED == STD_ON) */
      }
    }
  }
  /* Exit Protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);
}

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (PWM_SYNC_START_SUPPORT == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_SynchronousStart
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This routine starts all PWM channels configured to support synchronous start/stop of timers.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpGTMUnitConfig
**
** Functions invoked     : None
**
** Registers Used        : AGCGLBCTRL, TGCGLBCTRL
**
** Reference ID          : PWM_DUD_ACT_120, PWM_DUD_ACT_120_REG001, PWM_DUD_ACT_120_REG002, PWM_DUD_ACT_120_GBL001
** Reference ID          : PWM_DUD_ACT_120_CRT001, PWM_DUD_ACT_120_CRT002
***********************************************************************************************************************/
#if (PWM_SYNC_START_SUPPORT == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_GTM_SynchronousStart(void)
{
  /* Pointer to Cluster configuration */
  P2CONST(Pwm_GTMUnitConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpClusterConfig;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Cluster control registers */
  P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Cluster control registers */
  P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  uint8 LucCount;

  /* Enter Protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  /* Loop to Initialize Cluster related attributes */
  for (LucCount = PWM_ZERO; LucCount < PWM_TOTAL_GTM_UNITS_CONFIG; LucCount++)                                          /* PRQA S 2877 # JV-01 */
  {
    /* Update the configure pointer to point to the current Cluster */
    LpClusterConfig = &Pwm_GpGTMUnitConfig[LucCount];
    /* TOM/ATOM Type */
    #if (PWM_GTM_ATOM_USED == STD_ON)
    if (PWM_GTM_ATOMTYPE == LpClusterConfig->ucTomAtomType)                                                             /* PRQA S 1863 # JV-01 */
    {
      /* Get the pointer to the PWM sub block control registers */
      LpAtomClusterRegs = (P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Enable(start) the timer channel configured as sync */
      LpAtomClusterRegs->ulAGCGLBCTRL |= (((uint32)LpClusterConfig->usSyncChannelMask & PWM_GTM_AGC_TGC_EN_VALUE)
                                        << PWM_GTM_SHIFT_16) | PWM_GTM_GLB_CTRL_HOST_TRIG_VALUE;
    }
    else
    #endif
    {
      #if (PWM_GTM_TOM_USED == STD_ON)
      /* Get the pointer to the PWM sub block control registers */
      LpTomClusterRegs = (P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Enable(start) the timer channel configured as sync */
      LpTomClusterRegs->ulTGCGLBCTRL |= (((uint32)LpClusterConfig->usSyncChannelMask & PWM_GTM_AGC_TGC_EN_VALUE)
                                        << PWM_GTM_SHIFT_16) | PWM_GTM_GLB_CTRL_HOST_TRIG_VALUE;
      #endif
    }
  }
  /* Exit Protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
}

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (PWM_SYNC_START_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_SynchronousStop
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This function stops PWM channels configured synchronous, support stop timers and set the
**                         synchronous channels to idle state.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpGTMUnitConfig
**
** Functions invoked     : None
**
** Registers Used        : AGCOUTENSTAT, TGCOUTENSTAT
**
** Reference ID          : PWM_DUD_ACT_121, PWM_DUD_ACT_121_REG001, PWM_DUD_ACT_121_REG002, PWM_DUD_ACT_121_GBL001
***********************************************************************************************************************/
#if (PWM_SYNC_START_SUPPORT == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_GTM_SynchronousStop(void)
{
  /* Pointer to Cluster configuration */
  P2CONST(Pwm_GTMUnitConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpClusterConfig;
  /* Local Pointer used for each ATOM/TOM channel control registers */
  P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelProp;
  /* Local pointer to the each Gtm channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Cluster control registers */
  P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Cluster control registers */
  P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  uint8 LucCount;
  uint32 LucChShiftNum;

  /* Loop to Initialize Cluster related attributes */
  for (LucCount = PWM_ZERO; LucCount < PWM_TOTAL_CHANNELS_CONFIG; LucCount++)
  {
    /* Update the configure pointer to point to the current Timer channel*/
    LpChannelConfig = &Pwm_GpChannelConfig[LucCount];
    if (PWM_HWIP_GTM == Pwm_GpChannelConfig[LucCount].ucTimerUnitType)                                                  /* PRQA S 3416 # JV-01 */
    {
      #if (PWM_SYNC_START_SUPPORT == STD_ON)
      if (PWM_TRUE == LpChannelConfig->blSyncStartReq)
      #endif
      {
        /* Update the configure pointer to point to the current Cluster */
        LpChannelProp = (P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST)) LpChannelConfig->pChannelProp;   /* PRQA S 0316 # JV-01 */
        LpClusterConfig = &Pwm_GpGTMUnitConfig[LpChannelProp->ucTimerUnitIndex];
        /* TOM/ATOM Type */
        #if (PWM_GTM_ATOM_USED == STD_ON)
        if (PWM_GTM_ATOMTYPE == LpClusterConfig->ucTomAtomType)                                                         /* PRQA S 1863 # JV-01 */
        {
          /* Get the pointer to the PWM sub block control registers */
          LpAtomClusterRegs =
                           (P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs;/* PRQA S 0316, 3432 # JV-01, JV-01 */
          /* Set the output to idle level */
          Pwm_HW_GTM_SetOutputToIdle(LucCount);
          /* Get the bit shift */
          LucChShiftNum = (uint32)(LpChannelProp->ucChannelNumber << PWM_ONE);                                          /* PRQA S 4391 # JV-01 */
          /* Disable Sync-ch by AGCOUTENSTAT register */
          LpAtomClusterRegs->ulAGCOUTENSTAT = (uint32)(PWM_GTM_CTRL_DISABLE << LucChShiftNum);
        }
        else
        #endif
        {
          #if (PWM_GTM_TOM_USED == STD_ON)
          /* Get the pointer to the PWM sub block control registers */
          LpTomClusterRegs =
                           (P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
          /* Set the output to idle level */
          Pwm_HW_GTM_SetOutputToIdle(LucCount);
          /* Get the bit shift */
          LucChShiftNum = (uint32)(LpChannelProp->ucChannelNumber << PWM_ONE);                                          /* PRQA S 4391 # JV-01 */
          /* Disable Sync-ch by TGCOUTENSTAT register */
          LpTomClusterRegs->ulTGCOUTENSTAT = (uint32)(PWM_GTM_CTRL_DISABLE << LucChShiftNum);
          #endif /* (PWM_GTM_ATOM_USED == STD_ON) */
        }
      } /* Else no action required */
    } /* Else no action required */
  }
}

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_SYNC_START_SUPPORT == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_SelectChannelClk
**                       
** Service ID            : NA
**                       
** Description           : This function updates the clock source select value in hardware register.
**                       
** Sync/Async            : Synchronous
**                       
** Reentrancy            : Reentrant
**                       
** Input Parameters      : LddChannelId
**                         LenClockSource
**                       
** InOut Parameters      : None
**                       
** Output Parameters     : None
**                       
** Return parameter      : None
**                       
** Pre-conditions        : NA
**                       
** Global Variable used  : Pwm_GpChannelConfig, Pwm_GpGTMUnitConfig
**                       
** Functions invoked     : Det_ReportError
**                       
** Registers Used        : AGCGLBCTRL, ATOMiCHxCTRLSR, ATOMiCHxCTRL, TGCGLBCTRL, TOMiCHxCTRLSR, TOMiCHxCTRL
**
** Reference ID          : PWM_DUD_ACT_122, PWM_DUD_ACT_122_REG001, PWM_DUD_ACT_122_REG002, PWM_DUD_ACT_122_REG003
** Reference ID          : PWM_DUD_ACT_122_REG004, PWM_DUD_ACT_122_REG005, PWM_DUD_ACT_122_REG006, 
** Reference ID          : PWM_DUD_ACT_122_GBL001, PWM_DUD_ACT_122_GBL002
** Reference ID          : PWM_DUD_ACT_122_CRT001, PWM_DUD_ACT_122_CRT002
** Reference ID          : PWM_DUD_ACT_122_ERR001, PWM_DUD_ACT_122_ERR002
***********************************************************************************************************************/
#if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE)
                          Pwm_HW_GTM_SelectChannelClk(Pwm_ChannelType LddChannelId, Pwm_ClockSourceType LenClockSource)
{
  /* Local pointer to the each Gtm channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelConfig;
  /* Local Pointer used for each ATOM/TOM channel control registers */
  P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelProp;
  /* Pointer to Cluster configuration */
  P2CONST(Pwm_GTMUnitConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpClusterConfig;
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Channel control registers */
  P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  /* Local Pointer used for TOM Cluster control registers */
  P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE) LpTomClusterRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Channel control registers */
  P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  /* Local Pointer used for ATOM Cluster control registers */
  P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE) LpAtomClusterRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  /* Local variable */
  uint8 LucTempClockSourceVal;
  uint32 LucChShiftNum;

  /* Update the configure pointer to point to the current Timer channel*/
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  LpChannelProp = (P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST)) LpChannelConfig->pChannelProp;         /* PRQA S 0316 # JV-01 */
  LpClusterConfig = &Pwm_GpGTMUnitConfig[LpChannelProp->ucTimerUnitIndex];
  /* Get the bit shift */
  LucChShiftNum = (uint32)(LpChannelProp->ucChannelNumber << PWM_ONE);                                                  /* PRQA S 4391 # JV-01 */
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  if ((PWM_GTM_TOMTYPE == LpChannelProp->ucTomAtomType) &&                                                              /* PRQA S 1863 # JV-01 */
    ((PWM_CCM_FXCLK_RES0 > LenClockSource) || (PWM_CCM_FXCLK_RES4 < LenClockSource)))
  {
    /* Report to DET module */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SELECT_CHANNEL_CLK_SID, PWM_E_PARAM_VALUE);
  }
  else if ((PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType) &&                                                        /* PRQA S 1863 # JV-01 */
         ((PWM_CCM_CLK_RES_0 > LenClockSource)  || (PWM_CCM_CLK_RES_7 < LenClockSource)))
  {
    /* Report to DET module */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SELECT_CHANNEL_CLK_SID, PWM_E_PARAM_VALUE);
  }
  else
  #endif
  {
    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    /* TOM/ATOM Type */
    #if (PWM_GTM_ATOM_USED == STD_ON)
    if (PWM_GTM_ATOMTYPE == LpChannelProp->ucTomAtomType)                                                               /* PRQA S 1863 # JV-01 */
    {
      switch (LenClockSource)
      {
      case PWM_CCM_CLK_RES_0 :
        LucTempClockSourceVal = (uint8)PWM_GTM_CLKSRC_CMUCLK0_VALUE;
        break;
      case PWM_CCM_CLK_RES_1 :
        LucTempClockSourceVal = (uint8)PWM_GTM_CLKSRC_CMUCLK1_VALUE;
        break;
      case PWM_CCM_CLK_RES_2 :
        LucTempClockSourceVal = (uint8)PWM_GTM_CLKSRC_CMUCLK2_VALUE;
        break;
      case PWM_CCM_CLK_RES_3 :
        LucTempClockSourceVal = (uint8)PWM_GTM_CLKSRC_CMUCLK3_VALUE;
        break;
      case PWM_CCM_CLK_RES_4 :
        LucTempClockSourceVal = (uint8)PWM_GTM_CLKSRC_CMUCLK4_VALUE;
        break;
      case PWM_CCM_CLK_RES_5 :
        LucTempClockSourceVal = (uint8)PWM_GTM_CLKSRC_CMUCLK5_VALUE;
        break;
      case PWM_CCM_CLK_RES_6 :
        LucTempClockSourceVal = (uint8)PWM_GTM_CLKSRC_CMUCLK6_VALUE;
        break;
      default : 
        LucTempClockSourceVal = (uint8)PWM_GTM_CLKSRC_CMUCLK7_VALUE;
        break;
      }
      
      /* Get the pointer to the PWM Channel control registers */
      LpAtomChCntrlRegs = (P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Get the pointer to the PWM Cluster control registers */
      LpAtomClusterRegs = (P2VAR(Pwm_GTMAtomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Disable the channel by updating AGCGLBCTRL register */
      LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((PWM_GTM_CTRL_DISABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
      /* Load new value for CHxCTRLSR */
      #if (PWM_GTM_VERSION == PWM_GTM_4_1_VERSION)
      LpAtomChCntrlRegs->ulCHxCTRLSR &= ~PWM_GTM_CLK_SRC_MASK;
      LpAtomChCntrlRegs->ulCHxCTRLSR |= (uint32)LucTempClockSourceVal << PWM_GTM_CLKSRC_SHIFT_NUM;
      #endif
      /* Load new value for CHxCTRL */
      LpAtomChCntrlRegs->ulCHxCTRL &= ~PWM_GTM_CLK_SRC_MASK;
      LpAtomChCntrlRegs->ulCHxCTRL |= (uint32)LucTempClockSourceVal << PWM_GTM_CLKSRC_SHIFT_NUM;
      /* Enable the channel by updating AGCGLBCTRL register */
      LpAtomClusterRegs->ulAGCGLBCTRL = (uint32)((PWM_GTM_CTRL_ENABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
    }
    else
    #endif
    {
      #if (PWM_GTM_TOM_USED == STD_ON)
      switch (LenClockSource)
      {
      case PWM_CCM_FXCLK_RES0 :
        LucTempClockSourceVal = (uint8)PWM_GTM_CLKSRC_CMUFCLK0_VALUE;
        break;
      case PWM_CCM_FXCLK_RES1 :
        LucTempClockSourceVal = (uint8)PWM_GTM_CLKSRC_CMUFCLK1_VALUE;
        break;
      case PWM_CCM_FXCLK_RES2 :
        LucTempClockSourceVal = (uint8)PWM_GTM_CLKSRC_CMUFCLK2_VALUE;
        break;
      case PWM_CCM_FXCLK_RES3 :
        LucTempClockSourceVal = (uint8)PWM_GTM_CLKSRC_CMUFCLK3_VALUE;
        break;
      default : 
        LucTempClockSourceVal = (uint8)PWM_GTM_CLKSRC_CMUFCLK4_VALUE;
        break;
      }

      /* Get the pointer to the PWM Channel control registers */
      LpTomChCntrlRegs = (P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;     /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Get the pointer to the PWM Cluster control registers */
      LpTomClusterRegs = (P2VAR(Pwm_GTMTomClusterRegs, AUTOMATIC, REGSPACE)) LpClusterConfig->pGtmTomATomClusterRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Disable the channel by updating TGCGLBCTRL register */
      LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((PWM_GTM_CTRL_DISABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
      /* Load new value for CHxCTRLSR */
      LpTomChCntrlRegs->ulCHxCTRLSR &= ~PWM_GTM_CLK_SRC_MASK;
      LpTomChCntrlRegs->ulCHxCTRLSR |= (uint32)LucTempClockSourceVal << PWM_GTM_CLKSRC_SHIFT_NUM;
      /* Load new value for CHxCTRL */
      LpTomChCntrlRegs->ulCHxCTRL &= ~PWM_GTM_CLK_SRC_MASK;
      LpTomChCntrlRegs->ulCHxCTRL |= (uint32)LucTempClockSourceVal << PWM_GTM_CLKSRC_SHIFT_NUM;
      /* Enable the channel by updating TGCGLBCTRL register */
      LpTomClusterRegs->ulTGCGLBCTRL = (uint32)((PWM_GTM_CTRL_ENABLE << PWM_GTM_SHIFT_16) << LucChShiftNum);
      #endif
    }
    /* Exit Protected area */
    PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  }
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)*/

/***********************************************************************************************************************
** Function Name         : Pwm_HW_GTM_Callback
**
** Service ID            : NA
**
** Description           : This routine is used to invoke the callback notification.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpChannelConfig, Pwm_GaaNotifStatus
**
** Functions invoked     : PWM_DEM_REPORT_ERROR
**
** Registers Used        : CHxIRQEN, CHxIRQNOTIFY
**
** Reference ID          : PWM_DUD_ACT_123, PWM_DUD_ACT_123_REG001, PWM_DUD_ACT_123_ERR001, PWM_DUD_ACT_123_ERR002
** Reference ID          : PWM_DUD_ACT_123_GBL001, PWM_DUD_ACT_123_GBL002, PWM_DUD_ACT_123_REG002
** Reference ID          : PWM_DUD_ACT_123_CRT001, PWM_DUD_ACT_123_CRT002
***********************************************************************************************************************/
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_CODE_FAST) Pwm_HW_GTM_Callback(Pwm_ChannelType LddChannelId)
{
  #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
  #if (PWM_GTM_ATOM_USED == STD_ON)
  /* Local Pointer used for ATOM Channel control registers */
  P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE) LpAtomChCntrlRegs;                                                 /* PRQA S 3432 # JV-01 */
  #endif
  #if (PWM_GTM_TOM_USED == STD_ON)
  /* Local Pointer used for TOM Channel control registers */
  P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE) LpTomChCntrlRegs;                                                   /* PRQA S 3432 # JV-01 */
  #endif
  /* Local pointer to the each Gtm channel configuration */
  P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_FAST_CONST) LpChannelConfig;
  /* Local Pointer used for each ATOM/TOM channel control registers */
  P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST) LpChannelProp;

  /* Update the configure pointer to point to the current Timer channel*/
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  LpChannelProp = (P2CONST(Pwm_GTMChannelPropType, AUTOMATIC, PWM_CONFIG_CONST)) LpChannelConfig->pChannelProp;         /* PRQA S 0316 # JV-01 */
  #if (PWM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  if (NULL_PTR == LpChannelProp->pEICx_Address)
  {
    /* Channel interrupt Masked */
    PWM_DEM_REPORT_ERROR(PWM_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else if ((uint16)PWM_ZERO != (*LpChannelProp->pEICx_Address & PWM_EIC_EIMK_MASK))
  {
    /* Channel interrupt Masked */
    PWM_DEM_REPORT_ERROR(PWM_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
    /* Check if Notification status is enabled for this channel */
    if (PWM_TRUE == Pwm_GaaNotifStatus[LddChannelId])                                                                   /* PRQA S 1881 # JV-01 */
    {
      /* Enter Protected area */
      PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
      #if (PWM_GTM_TOM_USED == STD_ON)
      if (PWM_GTM_TOMTYPE == LpChannelProp->ucTomAtomType)                                                              /* PRQA S 1863 # JV-01 */
      {
        /* Get the pointer to the PWM Channel control registers */
        LpTomChCntrlRegs = (P2VAR(Pwm_GTMTomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */
        /* Check the right channel ISR is reported */
        if(PWM_DOUBLE_ZERO != (LpTomChCntrlRegs->ulCHxIRQEN & LpTomChCntrlRegs->ulCHxIRQNOTIFY &                        /* PRQA S 0404 # JV-01 */
                                                                                         PWM_GTM_DUTY_CYCLE_MATCH_MASK))
        {
          /* Clear the interrupt flag */
          LpTomChCntrlRegs->ulCHxIRQNOTIFY = PWM_GTM_DUTY_CYCLE_MATCH_MASK;
          /* Checking NULL of Notification function pointer */
          if (NULL_PTR != LpChannelConfig->pPwmEdgeNotifPtr)
          {
            /* Invoke the Notification function */
            LpChannelConfig->pPwmEdgeNotifPtr();
          } /* Else nothing */
        } /* Else nothing */
      }
      else
      #endif /* End of #if (PWM_GTM_TOM_USED == STD_ON)*/
      {
        #if (PWM_GTM_ATOM_USED == STD_ON)
        /* Get the pointer to the PWM Channel control registers */
        LpAtomChCntrlRegs = (P2VAR(Pwm_GTMAtomChCntrlRegs, AUTOMATIC, REGSPACE)) LpChannelProp->pGtmTomATomChannelRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
        /* Check the right channel ISR is reported */
        if(PWM_DOUBLE_ZERO != (LpAtomChCntrlRegs->ulCHxIRQEN & LpAtomChCntrlRegs->ulCHxIRQNOTIFY &                      /* PRQA S 0404 # JV-01 */
                                                                                         PWM_GTM_DUTY_CYCLE_MATCH_MASK))
        {
          /* Clear the interrupt flag */
          LpAtomChCntrlRegs->ulCHxIRQNOTIFY = PWM_GTM_DUTY_CYCLE_MATCH_MASK;
          /* Checking NULL of Notification function pointer */
          if (NULL_PTR != LpChannelConfig->pPwmEdgeNotifPtr)
          {
            /* Invoke the Notification function */
            LpChannelConfig->pPwmEdgeNotifPtr();
          } /* Else nothing */
        } /* Else nothing */
        #endif /* End of #if (PWM_GTM_ATOM_USED == STD_ON)*/
      }
      /* Exit Protected area */
      PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    } /* No action required */
  }
  #endif
}
#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (PWM_GTM_UNIT_USED == STD_ON)*/
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
