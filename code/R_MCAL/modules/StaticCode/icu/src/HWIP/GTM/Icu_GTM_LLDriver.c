/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_GTM_LLDriver.c                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Low Level function implementations of ICU Driver Component                                      */
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
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01 Release
 * 2.3.1:  31/03/2025  : As part of support QAC 11.6.0, following changes are made:
                         1. Add 3415, 3006, 3416 and remove 1532, 2814, 2824, 2844, 3432, 4304
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : As part of ARDAACL-51879, following changes are made:
 *                       1. Add GTM TIM NEWVAL concurrency check in the function Icu_HW_Gtm_GetPulseData
 * 2.1.2:  31/10/2024  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Header file inclusion */
#include "Icu_GTM_LLDriver.h"
/* Included for RAM variable declarations */
#include "Icu_Ram.h"
#if (ICU_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
/* Include for interrupt consistency check */
#include "Dem.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#if (ICU_GTM_TIMER_UNIT_USED == STD_ON)
/* AUTOSAR release version information */
#define ICU_GTM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_GTM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_GTM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ICU_GTM_LLDRIVER_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_GTM_LLDRIVER_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ICU_GTM_LLDRIVER_AR_RELEASE_MAJOR_VERSION != ICU_GTM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "Icu_GTM_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (ICU_GTM_LLDRIVER_AR_RELEASE_MINOR_VERSION != ICU_GTM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "Icu_GTM_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (ICU_GTM_LLDRIVER_AR_RELEASE_REVISION_VERSION != ICU_GTM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "Icu_GTM_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (ICU_GTM_LLDRIVER_SW_MAJOR_VERSION != ICU_GTM_LLDRIVER_C_SW_MAJOR_VERSION)
#error "Icu_GTM_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (ICU_GTM_LLDRIVER_SW_MINOR_VERSION != ICU_GTM_LLDRIVER_C_SW_MINOR_VERSION)
#error "Icu_GTM_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
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
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : MISRA C:2012 Rule-18.4, CERTCCM EXP08, CWE Rule CWE-188, CWE-398, CWE-569                    */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
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
/* Message (3:3387)    : A full expression containing an increment (++) or decrement (--) operator should have no     */
/*                       potential side effects other than that caused by the increment or decrement operator.        */
/* Rule                : MISRA C:2012 Rule-13.3                                                                       */
/* JV-01 Justification : An increment/decrement is created as a side effect. In this case, it's accessing a volatile  */
/*                       object. This can be accepted.                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : MISRA C:2012 Rule-13.5, CERTCCM EXP02, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it does not have direct access to the HW register, and     */
/*                       there is no side effect.                                                                     */
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
/* Message (3:4304)    : An expression of 'essentially Boolean' type (%1s) is being cast to unsigned type '%2s'.      */
/* Rule                : MISRA C:2012 Rule-10.5                                                                       */
/* JV-01 Justification : This is accepted. This casting from boolean to unsigned type for values 0 and 1 does not     */
/*                       make data conflict.                                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4342)    : An expression of 'essentially unsigned' type (%1s) is being cast to enum type '%2s'.         */
/* Rule                : MISRA C:2012 Rule-10.5, CWE Rule CWE-704                                                     */
/* JV-01 Justification : It is assigned to a variable with no conflict in the data.                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name         : Icu_HW_Gtm_UnitInit
**
** Service ID            : None
**
** Description           : This service initializes the hardware for TBU configured unit.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : ConfigPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : IcuGtmTbuUnit container is configured
**
** Global Variables      : Icu_GpGtmTbuConfig
**
** Functions invoked     : None
**
** Registers Used        : TBU_CHEN, TBU_CH0_CTRL, TBU_CH1_CTRL, TBU_CH2_CTRL
**
** Reference ID          : ICU_DUD_ACT_108, ICU_DUD_ACT_108_GBL001, ICU_DUD_ACT_108_REG001, ICU_DUD_ACT_108_REG002
** Reference ID          : ICU_DUD_ACT_108_REG003, ICU_DUD_ACT_108_REG004
***********************************************************************************************************************/
#if (ICU_GTM_TBU_UNIT_USED == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_UnitInit(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST) ConfigPtr)
{
  /* Defining a pointer to TBU configuration structure */
  P2CONST(Icu_GtmTbuUnitConfigType, AUTOMATIC, ICU_CONFIG_CONST) LpTBUUnitConfig;
  /* Get the TBU configured unit setting */
  Icu_GpGtmTbuConfig = ConfigPtr->pGtmTbuUnitConfig;                                                                    /* PRQA S 0317 # JV-01 */
  /* Get the configured unit setting */
  LpTBUUnitConfig = &Icu_GpGtmTbuConfig[ICU_ZERO];
  #if (ICU_GTM_TBU0_UNIT_CONFIGURED == STD_ON)
  /* Set the TBU0 clock setting */
  *(volatile uint32 *)LpTBUUnitConfig->pTBU0CTRLRegs = LpTBUUnitConfig->ulTBU0CTRLValue;
  #endif
  #if (ICU_GTM_TBU1_UNIT_CONFIGURED == STD_ON)
  /* Set the TBU1 clock setting */
  *(volatile uint32 *)LpTBUUnitConfig->pTBU1CTRLRegs = LpTBUUnitConfig->ulTBU1CTRLValue;
  #endif
  #if (ICU_GTM_TBU2_UNIT_CONFIGURED == STD_ON)
  /* Set the TBU2 clock setting */
  *(volatile uint32 *)LpTBUUnitConfig->pTBU2CTRLRegs = LpTBUUnitConfig->ulTBU2CTRLValue;
  #endif
  /* Start TBUx timer */
  *(volatile uint32 *)LpTBUUnitConfig->pTBUCHENRegs = LpTBUUnitConfig->ulTBUCHENValue;
} /* End of Internal function Icu_HW_Gtm_UnitInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of TBU timer setting */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Gtm_ChannelInit
**
** Service ID            : None
**
** Description           : This service initializes the hardware for all the
**                         configured channels based on the measurement mode.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpChannelUserRegConfig, Icu_GpChannelConfig, Icu_GpChannelRamData
**                         Icu_GpTimeStampData, Icu_GpSignalMeasurementData, Icu_GpEdgeCountData
**
** Functions invoked     : RH850_SV_SET_ICR_SYNCP
**
** Registers Used        : TIM[i]_CH[x]_CTRL, TIM[i]_CH[x]_ECTRL, TIM[i]_CH[x]_FLT_RE, TIM[i]_CH[x]_FLT_FE
**                         TIM[i]_CH[x]_IRQ_EN, EICn, pGTM_IRQ_SELij, TIM[i]_CH[x]_IRQ_MODE
**
** Reference ID          : ICU_DUD_ACT_109, ICU_DUD_ACT_109_REG001, ICU_DUD_ACT_109_REG002
** Reference ID          : ICU_DUD_ACT_109_REG003, ICU_DUD_ACT_109_REG004, ICU_DUD_ACT_109_REG005
** Reference ID          : ICU_DUD_ACT_109_REG006, ICU_DUD_ACT_109_REG007, ICU_DUD_ACT_109_GLB001
** Reference ID          : ICU_DUD_ACT_109_GLB002, ICU_DUD_ACT_109_GLB003, ICU_DUD_ACT_109_GLB004
** Reference ID          : ICU_DUD_ACT_109_GLB005, ICU_DUD_ACT_109_GLB006, ICU_DUD_ACT_109_GLB007
** Reference ID          : ICU_DUD_ACT_109_GLB008, ICU_DUD_ACT_109_GLB009
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_ChannelInit(Icu_ChannelType LddChannel)                                         /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_CONST) LpChannelConfig;
  /* Defining a pointer to point to the GTM Timer TIM registers */
  P2VAR(Icu_GtmTimerTimRegs, AUTOMATIC, ICU_CONFIG_DATA) LpGtmTimerTimRegs;                                             /* PRQA S 3432 # JV-01 */
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_GtmChannelConfigType, AUTOMATIC, ICU_CONFIG_CONST) LpGtmChannelConfig;
  /* Defining a pointer to the Channel Ram Data */
  P2VAR(volatile Icu_ChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpRamData;
  /* Local variable to store the measurement mode of a channel */
  Icu_MeasurementModeType LddMeasurementMode;
  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON) || (ICU_TIMESTAMP_API == STD_ON) || (ICU_EDGE_COUNT_API == STD_ON)
  /* Local variable used to store the Timer ram index */
  uint8 LucIndex;
  /* Read the Signal Measurement Channel ram index */
  LucIndex = Icu_GpChannelUserRegConfig[LddChannel].ucRamDataIndex;
  #endif
  /* Update the channel pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Load the base register address */
  LpGtmChannelConfig = Icu_GpChannelUserRegConfig[LddChannel].pHWChannelUserRegConfig;                                  /* PRQA S 0317 # JV-01 */
  LpGtmTimerTimRegs = LpChannelConfig->pCntlRegs;                                                                       /* PRQA S 0317 # JV-01 */

  /* Load the address of GTM IRQ select registers */
  if(NULL_PTR != LpGtmChannelConfig->pGTM_IRQ_SELij)
  {
    *(volatile uint32 *)LpGtmChannelConfig->pGTM_IRQ_SELij |= LpGtmChannelConfig->ulGTM_IRQ_SELijEnableValue;
  }/* Else no action */

  /* GTM TIMnCTRL register initialization */
  LpGtmTimerTimRegs->ulTIMCTRLRegs = LpGtmChannelConfig->ulCtrlRegsChannelSettings;
  /* Setting IRQ mode to Pulse-Notify mode */
  LpGtmTimerTimRegs->ulIRQMODERegs = (uint32)ICU_TWO;

  #if (ICU_GTM_TIM_FILTER_USED == STD_ON)
  /* GTM TIMnECTRL register initialization */
  LpGtmTimerTimRegs->ulTIMECTRLRegs = LpGtmChannelConfig->ulECtrlRegsChannelSettings;

  /* Check if the TIM channel enabled filter function */
  if (ICU_FLT_CONFIG == (LpGtmChannelConfig->ulCtrlRegsChannelSettings & ICU_FLT_CONFIG))
  {
    /* Set the filter rising and falling edge */
    LpGtmTimerTimRegs->ulFLTRERegs = LpGtmChannelConfig->ulFilterRisingEdgeMask;
    LpGtmTimerTimRegs->ulFLTFERegs = LpGtmChannelConfig->ulFilterFallingEdgeMask;
  } /* No action required */
  #endif /* End of (ICU_GTM_TIM_FILTER_USED == STD_ON)*/

  /* Disable interrupt of the TIM LddChannel outside the GTM-IP */
  LpGtmTimerTimRegs->ulIRQENRegs = TIM_IRQ_CLEAR;
  /* Read the channel's measurement mode */
  LddMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  /* Update the global pointer with the first channel's ram address */
  LpRamData = &Icu_GpChannelRamData[LddChannel];
  /* Initialize each channel status as idle */
  LpRamData->ucChannelStatus = (uint8)ICU_IDLE;
  #if (STD_ON == ICU_SET_MODE_API)
  /* Initialize running status for each channel */
  LpRamData->ucChannelRunning = (uint8)ICU_FALSE;                                                                       /* PRQA S 4304 # JV-01 */
  #endif

  #if ((ICU_DISABLE_WAKEUP_API == STD_ON) || (ICU_ENABLE_WAKEUP_API == STD_ON) || \
                                                                              (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON))
  /* Disable each channel wakeup from sleep mode */
  LpRamData->ucWakeupEnable = (uint8)ICU_FALSE;                                                                         /* PRQA S 4304 # JV-01 */
  /* Initialize wakeup occurrence for each channel */
  LpRamData->blWakeupOccurrence = ICU_FALSE;
  #endif
  /* Disable notification for each channel */
  LpRamData->ucNotificationEnable = (uint8)ICU_FALSE;                                                                   /* PRQA S 4304 # JV-01 */
  /* Initialize the status of result channel as False */
  LpRamData->blResultComplete = ICU_FALSE;

  if (ICU_MODE_TIMESTAMP == LddMeasurementMode)
  {
    #if(ICU_TIMESTAMP_API == STD_ON)
    /* Reset buffer pointer and index */
    Icu_GpTimeStampData[LucIndex].usTimestampIndex = (uint16)ICU_BUFFER_IDX_INIT_VAL;
    #endif
  }
  else if (ICU_MODE_SIGNAL_MEASUREMENT == LddMeasurementMode)
  {
    #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
    /* Initialize the Signal Active time to zero */
    Icu_GpSignalMeasurementData[LucIndex].ulSignalActiveTime = (uint32)ICU_ACTIVE_TIME_INIT_VAL;
    /* Initialize the Signal Period time to zero */
    Icu_GpSignalMeasurementData[LucIndex].ulSignalPeriodTime = (uint32)ICU_SIGNAL_PERIOD_TIME_INIT_VAL;
    #endif
  }
  else if (ICU_MODE_EDGE_COUNTER == LddMeasurementMode)                                                                 /* PRQA S 2004 # JV-01 */
  {
    #if (ICU_EDGE_COUNT_API == STD_ON)
    /* Reset buffer pointer and index */
    Icu_GpEdgeCountData[LucIndex].ulIcuEdgeCount = ICU_DOUBLE_ZERO;
    #endif
  } /* Else no action */

  /* Interrupt disable */
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disable interrupts */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);                              /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */

} /* End of Internal function Icu_HW_Gtm_ChannelInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Gtm_UnitDeInit
**
** Service ID            : None
**
** Description           : This service stop all free-run TBU channel
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
** Preconditions         : ICU_DE_INIT_API is STD_ON and IcuGtmTbuUnit container is configured
**
** Global Variables      : Icu_GpGtmTbuConfig
**
** Functions invoked     : None
**
** Registers Used        : TBU_CHEN
**
** Reference ID          : ICU_DUD_ACT_110, ICU_DUD_ACT_110_REG001
***********************************************************************************************************************/
#if (ICU_DE_INIT_API == STD_ON) && (ICU_GTM_TBU_UNIT_USED == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_UnitDeInit(void)
{
  /* Defining a pointer to TBU configuration structure */
  P2CONST(Icu_GtmTbuUnitConfigType, AUTOMATIC, ICU_CONFIG_CONST) LpTBUUnitConfig;
  /* Get the configured unit setting */
  LpTBUUnitConfig = &Icu_GpGtmTbuConfig[ICU_ZERO];
  /* Stop TBU timer */
  *(volatile uint32 *)LpTBUUnitConfig->pTBUCHENRegs = ~(LpTBUUnitConfig->ulTBUCHENValue);
} /* End of Internal function Icu_HW_Gtm_UnitDeInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_DE_INIT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Gtm_ChannelDeInit
**
** Service ID            : None
**
** Description           : This service De-Initializes the hardware for all the
**                         configured channels based on the measurement mode.
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
** Global Variables      : Icu_GpChannelUserRegConfig, Icu_GpChannelConfig, Icu_GpChannelRamData
**
** Functions invoked     : RH850_SV_SET_ICR_SYNCP
**
** Registers Used        : TIM[i]_CH[x]_CTRL, TIM[i]_CH[x]_ECTRL, TIM[i]_CH[x]_FLT_RE, TIM[i]_CH[x]_FLT_FE
**                         TIM[i]_CH[x]_IRQ_EN, EICn, GTM_IRQ_SELij
**
** Reference ID          : ICU_DUD_ACT_111, ICU_DUD_ACT_111_REG001, ICU_DUD_ACT_111_REG002
** Reference ID          : ICU_DUD_ACT_111_REG003, ICU_DUD_ACT_111_REG004, ICU_DUD_ACT_111_REG005
** Reference ID          : ICU_DUD_ACT_111_REG006, ICU_DUD_ACT_111_REG007
** Reference ID          : ICU_DUD_ACT_111_GBL001, ICU_DUD_ACT_111_GBL002, ICU_DUD_ACT_111_GBL003
** Reference ID          : ICU_DUD_ACT_111_GBL004, ICU_DUD_ACT_111_GBL005, ICU_DUD_ACT_111_GBL006
***********************************************************************************************************************/
#if (ICU_DE_INIT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_ChannelDeInit(Icu_ChannelType LddChannel)                                       /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_CONST) LpChannelConfig;
  /* Defining a pointer to the channel Ram data */
  P2VAR(volatile Icu_ChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpRamData;
  /* Defining a pointer to point to the GTM Timer TIM registers */
  P2VAR(Icu_GtmTimerTimRegs, AUTOMATIC, ICU_CONFIG_DATA) LpGtmTimerTimRegs;                                             /* PRQA S 3432 # JV-01 */
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_GtmChannelConfigType, AUTOMATIC, ICU_CONFIG_CONST) LpGtmChannelConfig;
  /* Update the channel pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Load the base register address */
  LpGtmChannelConfig = Icu_GpChannelUserRegConfig[LddChannel].pHWChannelUserRegConfig;                                  /* PRQA S 0317 # JV-01 */
  LpGtmTimerTimRegs = LpChannelConfig->pCntlRegs;                                                                       /* PRQA S 0317 # JV-01 */

  /* Load the channel data pointer */
  LpRamData = &Icu_GpChannelRamData[LddChannel];
  /* Initialize each channel status as idle */
  LpRamData->ucChannelStatus = (uint8)ICU_IDLE;
  #if ((ICU_DISABLE_WAKEUP_API == STD_ON) || (ICU_ENABLE_WAKEUP_API == STD_ON) || \
                                                                               (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON))
  /* Disable each channel wakeup from sleep mode */
  LpRamData->ucWakeupEnable = (uint8)ICU_FALSE;                                                                         /* PRQA S 4304 # JV-01 */
  /* Initialize wakeup occurrence for each channel */
  LpRamData->blWakeupOccurrence = ICU_FALSE;
  #endif
  /* Disable notification for each channel */
  LpRamData->ucNotificationEnable = (uint8)ICU_FALSE;                                                                   /* PRQA S 4304 # JV-01 */
  /* Initialize the status of result channel as False */
  LpRamData->blResultComplete = ICU_FALSE;
  #if (STD_ON == ICU_SET_MODE_API)
  /* Initialize running status for each channel */
  LpRamData->ucChannelRunning = (uint8)ICU_FALSE;                                                                       /* PRQA S 4304 # JV-01 */
  #endif

  /* Load the address of GTM IRQ select registers */
  if(NULL_PTR != LpGtmChannelConfig->pGTM_IRQ_SELij)
  {
    *(volatile uint32 *)LpGtmChannelConfig->pGTM_IRQ_SELij &= ~(LpGtmChannelConfig->ulGTM_IRQ_SELijEnableValue);
  }/* Else no action */

  /* GTM TIMnCTRL register initialization */
  LpGtmTimerTimRegs->ulTIMCTRLRegs = ICU_DOUBLE_ZERO;

  #if (ICU_GTM_TIM_FILTER_USED == STD_ON)
  /* GTM TIMnECTRL register initialization */
  LpGtmTimerTimRegs->ulTIMECTRLRegs = ICU_DOUBLE_ZERO;
  /* Check if the TIM channel enabled filter function */
  if (ICU_FLT_CONFIG == (LpGtmChannelConfig->ulCtrlRegsChannelSettings & ICU_FLT_CONFIG))
  {
    /* Reset the filter rising and falling edge */
    LpGtmTimerTimRegs->ulFLTRERegs = ICU_DOUBLE_ZERO;
    LpGtmTimerTimRegs->ulFLTFERegs = ICU_DOUBLE_ZERO;
  } /* No action required */
  #endif

  /* Disable interrupt of the TIM LddChannel outside the GTM-IP */
  LpGtmTimerTimRegs->ulIRQENRegs = TIM_IRQ_CLEAR;
  /* Interrupt disable */
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disable interrupts */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);                              /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */
} /* End of Internal function Icu_HW_Gtm_ChannelDeInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_DE_INIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_HW_Gtm_SetActivation
**
** Service ID            : None
**
** Description           : This service configures the hardware to the active
**                         edges of the requested channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel, ActiveEdge
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : NA
**
** Global Variables      : Icu_GpChannelConfig.
**
** Functions invoked     : RH850_SV_MODE_ICR_AND
**
** Registers Used        : TIM[i]_CH[x]_CTRL, TIM[i]_CH[x]_IRQ_NOTIFY, EICn
**
** Reference ID          : ICU_DUD_ACT_112, ICU_DUD_ACT_112_REG001, ICU_DUD_ACT_112_REG002
** Reference ID          : ICU_DUD_ACT_112_REG003
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_SetActivation(Icu_ChannelType LddChannel, Icu_ActivationType ActiveEdge)
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_CONST) LpChannelConfig;
  /* Defining a pointer to point to the GTM Timer TIM registers */
  P2VAR(Icu_GtmTimerTimRegs, AUTOMATIC, ICU_CONFIG_DATA) LpGtmTimerTimRegs;                                             /* PRQA S 3432 # JV-01 */
  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Get base address of GTM channel configured */
  LpGtmTimerTimRegs = LpChannelConfig->pCntlRegs;                                                                       /* PRQA S 0317 # JV-01 */
  /* Check active request */
  if (ICU_RISING_EDGE == ActiveEdge)
  {
    LpGtmTimerTimRegs->ulTIMCTRLRegs &= TIM_ISL_RISING_EDGE;
    LpGtmTimerTimRegs->ulTIMCTRLRegs |= TIM_DSL_RISING_EDGE;
  }
  else if (ICU_FALLING_EDGE == ActiveEdge)
  {
    LpGtmTimerTimRegs->ulTIMCTRLRegs &= TIM_ISL_DSL_FALLING_EDGE;
  }
  else
  {
    LpGtmTimerTimRegs->ulTIMCTRLRegs |= TIM_ISL_BOTH_EDGES;
  }
  #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
  /* Check if the Interrupt register is present for particular channel */
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Clear the pending interrupts */
    RH850_SV_MODE_ICR_AND(16, (LpChannelConfig->pIntrCntlAddress), (uint16)ICU_CLEAR_PENDING_INTR_MASK);
  } /* No action required */
  /* Clear any unwanted flag for interrupt occurrence */
  LpGtmTimerTimRegs->ulIRQNOTIFYRegs = TIM_IRQ_NOTIF_CLEAR;
  #endif
} /* End of Internal function Icu_HW_SetActivation */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Icu_HW_StartCountMeasurement
**
** Service ID            : None
**
** Description           : This service routine starts the count measurement.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelRamData
**
** Functions invoked     : RH850_SV_MODE_ICR_AND, ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION
**                         RH850_SV_CLEAR_ICR_SYNCP
**
** Registers Used        : TIM[i]_CH[x]_CTRL, TIM[i]_CH[x]_IRQ_EN, EICn
**
** Reference ID          : ICU_DUD_ACT_113, ICU_DUD_ACT_113_REG001, ICU_DUD_ACT_113_REG002
** Reference ID          : ICU_DUD_ACT_113_REG003, ICU_DUD_ACT_113_REG004, ICU_DUD_ACT_113_GLB001
** Reference ID          : ICU_DUD_ACT_113_CRT001, ICU_DUD_ACT_113_CRT002
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_StartCountMeasurement(Icu_ChannelType LddChannel)                               /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_CONST) LpChannelConfig;
  /* Defining a pointer to point to the GTM Timer TIM registers */
  P2VAR(Icu_GtmTimerTimRegs, AUTOMATIC, ICU_CONFIG_DATA) LpGtmTimerTimRegs;                                             /* PRQA S 3432 # JV-01 */
  /* Local variable to store the measurement mode of a channel */
  Icu_MeasurementModeType LddMeasurementMode;
  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Get base address of GTM channel configured */
  LpGtmTimerTimRegs = LpChannelConfig->pCntlRegs;                                                                       /* PRQA S 0317 # JV-01 */
  /* Read the channel's measurement mode */
  LddMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  /* Enter Critical Section */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

  #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
  /* Check if the Interrupt register is present for particular channel */
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Clear the pending interrupts */
    RH850_SV_MODE_ICR_AND(16, (LpChannelConfig->pIntrCntlAddress), ((uint16)ICU_CLEAR_PENDING_INTR_MASK));
  } /* No action required */
  /* Clear any unwanted flag for interrupt occurrence */
  LpGtmTimerTimRegs->ulIRQNOTIFYRegs = TIM_IRQ_NOTIF_CLEAR;
  #endif /* End of #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON) */

  /* Check if the Interrupt register is present for particular channel */
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Enabling the Interrupt processing */
    #if ((ICU_ENABLE_WAKEUP_API == STD_ON) || (ICU_NOTIFY_WAKEUP_INTERRUPT == STD_ON))
    if (ICU_MODE_SLEEP == Icu_GenModuleMode)
    {
      /* No action required */
    }
    else
    #endif
    {
      RH850_SV_CLEAR_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_ENABLE_EIMK_MASK);                           /* PRQA S 0751, 1006 # JV-01, JV-01 */
    }
  } /* else No action required */

  /* Enable new value detect ISR incase of timestamp and edge detect */
  if (((Icu_MeasurementModeType)ICU_MODE_TIMESTAMP == LddMeasurementMode) ||
      ((Icu_MeasurementModeType)ICU_MODE_SIGNAL_EDGE_DETECT == LddMeasurementMode))
  {
    /* Enabling the Interrupt processing in the GTMTIMixIRQEN register */
    LpGtmTimerTimRegs->ulIRQENRegs |= ICU_NEWVAL_IRQ_EN;
  }
  else /* Enable overflow CNTOFL ISR detect */
  {
    /* Enabling the Overflow Interrupt processing in the GTMTIMixIRQEN register */
    LpGtmTimerTimRegs->ulIRQENRegs |= ICU_CNTOFL_IRQ_EN;
  }
  /* Enabling the TIM channel configured */
  LpGtmTimerTimRegs->ulTIMCTRLRegs |= ICU_DOUBLE_ONE;

  #if (STD_ON == ICU_SET_MODE_API)
  /* Initialize running status for each channel */
  Icu_GpChannelRamData[LddChannel].ucChannelRunning = (uint8)ICU_TRUE;                                                  /* PRQA S 4304 # JV-01 */
  #endif
  /* EXIT Critical Section */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
} /* End of Internal function Icu_HW_StartCountMeasurement */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Icu_HW_Gtm_StopCountMeasurement
**
** Service ID            : None
**
** Description           : This service routine stops the count measurement.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelRamData
**
** Functions invoked     : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION, RH850_SV_CLEAR_ICR_SYNCP
**
** Registers Used        : TIM[i]_CH[x]_CTRL, TIM[i]_CH[x]_IRQ_EN, EICn
**
** Reference ID          : ICU_DUD_ACT_114, ICU_DUD_ACT_114_REG001, ICU_DUD_ACT_114_REG002
** Reference ID          : ICU_DUD_ACT_114_REG003, ICU_DUD_ACT_114_GLB001
** Reference ID          : ICU_DUD_ACT_114_CRT001, ICU_DUD_ACT_114_CRT002
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_StopCountMeasurement(Icu_ChannelType LddChannel)                                /* PRQA S 3006 # JV-01 */

{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_CONST) LpChannelConfig;
  /* Defining a pointer to point to the GTM Timer TIM registers */
  P2VAR(Icu_GtmTimerTimRegs, AUTOMATIC, ICU_CONFIG_DATA) LpGtmTimerTimRegs;                                             /* PRQA S 3432 # JV-01 */
  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Get base address of GTM channel configured */
  LpGtmTimerTimRegs = LpChannelConfig->pCntlRegs;                                                                       /* PRQA S 0317 # JV-01 */
  /* Enter Critical Section */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

  /* Disabling the Interrupt processing */
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disable interrupts */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);                              /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */

  /* Disabling the Interrupt processing in the GTMTIMixIRQEN register */
  LpGtmTimerTimRegs->ulIRQENRegs = ICU_DOUBLE_ZERO;
  /* Disabling the TIM channel configured */
  LpGtmTimerTimRegs->ulTIMCTRLRegs &= ~(ICU_DOUBLE_ONE);

  #if (STD_ON == ICU_SET_MODE_API)
  /* Initialize running status for each channel */
  Icu_GpChannelRamData[LddChannel].ucChannelRunning = (uint8)ICU_FALSE;                                                 /* PRQA S 4304 # JV-01 */
  #endif

  /* Exit Critical Section */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
} /* End of Internal function Icu_HW_StopCountMeasurement */
#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Icu_HW_Gtm_ResetEdgeCount
**
** Service ID            : None
**
** Description           : This service resets the Timer Counter of the channel
**                         which is configured in Edge Counting Mode.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : ICU_EDGE_COUNT_API is STD_ON
**
** Global Variables      : Icu_GpChannelConfig.
**
** Functions invoked     : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION
**
** Registers Used        : TIM[i]_CH[x]_CTRL
**
** Reference ID          : ICU_DUD_ACT_115, ICU_DUD_ACT_115_REG001, ICU_DUD_ACT_115_CRT001, ICU_DUD_ACT_115_CRT002
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_ResetEdgeCount(Icu_ChannelType LddChannel)
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_CONST) LpChannelConfig;
  /* Defining a pointer to point to the GTM Timer TIM registers */
  P2VAR(Icu_GtmTimerTimRegs, AUTOMATIC, ICU_CONFIG_DATA) LpGtmTimerTimRegs;                                             /* PRQA S 3432 # JV-01 */
  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Get base address of GTM channel configured */
  LpGtmTimerTimRegs = LpChannelConfig->pCntlRegs;                                                                       /* PRQA S 0317 # JV-01 */
  /* Enter Critical Section */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  /* If the channel is in running then restarting the channel */
  if (ICU_DOUBLE_ONE == ((LpGtmTimerTimRegs->ulTIMCTRLRegs) & ICU_DOUBLE_ONE))
  {
    /* Disabling the TIM channel configured */
    LpGtmTimerTimRegs->ulTIMCTRLRegs &= ~(ICU_DOUBLE_ONE);
    /* Enabling the TIM channel configured */
    LpGtmTimerTimRegs->ulTIMCTRLRegs |= ICU_DOUBLE_ONE;
  }
  else /* If the channel is stopped */
  {
    /* Enabling the TIM channel configured */
    LpGtmTimerTimRegs->ulTIMCTRLRegs |= ICU_DOUBLE_ONE;
    /* Disabling the TIM channel configured */
    LpGtmTimerTimRegs->ulTIMCTRLRegs &= ~(ICU_DOUBLE_ONE);
  }
  /* Exit Critical Section */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
} /* End of Internal function Icu_HW_ResetEdgeCount */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_EDGE_COUNT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_HW_Gtm_GetEdgeNumbers
**
** Service ID            : None
**
** Description           : This service get perform hardware checking for APIs Icu_GetEdgeNumbers function
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : NA
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelUserRegConfig, Icu_GpEdgeCountData
**
** Functions invoked     : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION
**
** Registers Used        : TIMiCNTS
**
** Reference ID          : ICU_DUD_ACT_116, ICU_DUD_ACT_116_GLB001, ICU_DUD_ACT_116_CRT001, ICU_DUD_ACT_116_CRT002
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_GetEdgeNumbers(Icu_ChannelType LddChannel)
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_CONST) LpChannelConfig;
  /* Defining a pointer to point to the GTM Timer TIM registers */
  P2VAR(Icu_GtmTimerTimRegs, AUTOMATIC, ICU_CONFIG_DATA) LpGtmTimerTimRegs;                                             /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Local variable contains the channel RAM index */
  uint8 LucRamIndex;
  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Get base address of GTM channel configured */
  LpGtmTimerTimRegs = LpChannelConfig->pCntlRegs;                                                                       /* PRQA S 0317 # JV-01 */
  /* Read channel ram index */
  LucRamIndex = Icu_GpChannelUserRegConfig[LddChannel].ucRamDataIndex;
  /* Enter Critical Section */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION);
  /* Get the edge count data */
  Icu_GpEdgeCountData[LucRamIndex].ulIcuEdgeCount = LpGtmTimerTimRegs->ulCNTRegs & ICU_DOUBLE_CNTX;                     /* PRQA S 0404 # JV-01 */
  /* EXIT Critical Section */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION);
} /* End of Internal function Icu_HW_Gtm_GetEdgeNumbers */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of Icu_HW_Gtm_GetEdgeNumbers */
/***********************************************************************************************************************
** Function Name         : Icu_Gtm_TimerIsr
**
** Service ID            : None
**
** Description           : This service routine invokes the required function
**                         based on the channel configuration for further calculations.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelRamData
**
** Functions invoked     : pIcuNotificationPointer, ICU_DEM_REPORT_ERROR, Icu_Gtm_ServiceTimestamp
**                         ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION
**
** Registers Used        : TIM[i]_CH[x]_IRQ_NOTIFY, EICn, TIM[i]_CH[x]_GPR0, TIM[i]_CH[x]_CTRL
**
** Reference ID          : ICU_DUD_ACT_117, ICU_DUD_ACT_117_ERR001, ICU_DUD_ACT_117_ERR002, ICU_DUD_ACT_117_REG001
** Reference ID          : ICU_DUD_ACT_117_REG002, ICU_DUD_ACT_117_CRT001, ICU_DUD_ACT_117_CRT002
** Reference ID          : ICU_DUD_ACT_117_CRT003, ICU_DUD_ACT_117_CRT004, ICU_DUD_ACT_117_CRT005
** Reference ID          : ICU_DUD_ACT_117_CRT006
***********************************************************************************************************************/
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_CODE_FAST) Icu_Gtm_TimerIsr(Icu_ChannelType LddChannel)
{
  /* Defining a pointer to point to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_CONST) LpChannelConfig;
  /* Defining a pointer to point to the GTM Timer TIM registers */
  P2VAR(Icu_GtmTimerTimRegs, AUTOMATIC, ICU_CONFIG_DATA) LpGtmTimerTimRegs;                                             /* PRQA S 3432 # JV-01 */
  /* Local variable contains channel configured mode */
  Icu_MeasurementModeType LddMeasurementMode;
  /* Update the channel pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Get base address of GTM channel configured */
  LpGtmTimerTimRegs = LpChannelConfig->pCntlRegs;                                                                       /* PRQA S 0317 # JV-01 */
  /* Read the channel's mode */
  LddMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */

  #if (ICU_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check if the right EIC interrupt is configured in ICU module */
  if (NULL_PTR == LpChannelConfig->pIntrCntlAddress)
  {
    ICU_DEM_REPORT_ERROR(ICU_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  /* Check if the right EIC interrupt is reported */
  else if ((uint16)ICU_ZERO != (uint16)(*LpChannelConfig->pIntrCntlAddress & ICU_EIC_EIMK_MASK))
  {
    ICU_DEM_REPORT_ERROR(ICU_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
    /* Check if interrupt occurs on time stamp */
    #if (ICU_TIMESTAMP_API == STD_ON)
    if ((ICU_MODE_TIMESTAMP == LddMeasurementMode) &&                                                                   /* PRQA S 0404 # JV-01 */
        ((uint8)ICU_ACTIVE == Icu_GpChannelRamData[LddChannel].ucChannelStatus) &&                                      /* PRQA S 3415, 3416 # JV-01, JV-01 */
        (ICU_NEWVAL_IRQ_EN == (LpGtmTimerTimRegs->ulIRQNOTIFYRegs & ICU_NEWVAL_IRQ_EN)))
    {
      /* Process capture timestamp data */
      Icu_Gtm_ServiceTimestamp(LddChannel, (LpGtmTimerTimRegs->ulGPR0Regs & ICU_DOUBLE_CNTX));
      /* Enter Critical Section */
      ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
      /* Clear any unwanted flag for interrupt occurrence */
      LpGtmTimerTimRegs->ulIRQNOTIFYRegs = TIM_IRQ_NOTIF_CLEAR;
      /* Exit Critical Section */
      ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    } /* Else no action */
    #endif

    /* If edge detect interrupt */
    #if (ICU_EDGE_DETECT_API == STD_ON)
    if ((ICU_MODE_SIGNAL_EDGE_DETECT == LddMeasurementMode) &&                                                          /* PRQA S 0404 # JV-01 */
        ((uint8)ICU_TRUE == Icu_GpChannelRamData[LddChannel].ucNotificationEnable) &&                                   /* PRQA S 3415, 3416, 4304 # JV-01, JV-01, JV-01 */
        ((ICU_NEWVAL_IRQ_EN == (LpGtmTimerTimRegs->ulIRQNOTIFYRegs & ICU_NEWVAL_IRQ_EN)) ||
        ((uint8)ICU_ACTIVE == Icu_GpChannelRamData[LddChannel].ucChannelStatus)))                                       /* PRQA S 3415, 3416 # JV-01, JV-01 */
    {
      /* Clear interrupt flag manually by Icu_GetInputState */
      #if (ICU_NOTIFICATION_CONFIG == STD_ON)
      /* Checking NULL of Notification function pointer */
      if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
      {
        /* callback notification */
        LpChannelConfig->pIcuNotificationPointer();
      } /* No action required */
      #endif
    } /* No action required */
    #endif

    #if (ICU_EDGE_COUNT_API == STD_ON)
    /* If edge count overflow interrupt */
    if ((ICU_MODE_EDGE_COUNTER == LddMeasurementMode) &&
        (ICU_CNTOFL_IRQ_EN == (LpGtmTimerTimRegs->ulIRQNOTIFYRegs & ICU_CNTOFL_IRQ_EN)))
    {
      #if (ICU_NOTIFICATION_CONFIG == STD_ON)
      /* Checking NULL of Notification function pointer */
      if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
      {
        /* callback notification */
        LpChannelConfig->pIcuNotificationPointer();
      } /* No action required */
      #endif
      /* Enter Critical Section */
      ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
      /* Perform hardware reset edge counter channel to prevent infinity interrupt */
      LpGtmTimerTimRegs->ulTIMCTRLRegs &= ~(ICU_DOUBLE_ONE);
      /* Enabling the TIM channel configured */
      LpGtmTimerTimRegs->ulTIMCTRLRegs |= ICU_DOUBLE_ONE;
      /* Clear any unwanted flag for interrupt occurrence */
      LpGtmTimerTimRegs->ulIRQNOTIFYRegs = TIM_IRQ_NOTIF_CLEAR;
      /* Exit Critical Section */
      ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    } /* No action required */
    #endif

    #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
    /* If signal measurement overflow interrupt */
    if ((ICU_MODE_SIGNAL_MEASUREMENT == LddMeasurementMode) &&
        (ICU_CNTOFL_IRQ_EN == (LpGtmTimerTimRegs->ulIRQNOTIFYRegs & ICU_CNTOFL_IRQ_EN)))
    {
      #if (ICU_NOTIFICATION_CONFIG == STD_ON)
      /* Checking NULL of Notification function pointer */
      if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
      {
        /* callback notification */
        LpChannelConfig->pIcuNotificationPointer();
      } /* No action required */
      #endif
      /* Enter Critical Section */
      ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
      /* Clear overflow interrupt occurrence */
      LpGtmTimerTimRegs->ulIRQNOTIFYRegs = ICU_CNTOFL_IRQ_EN;
      /* Exit Critical Section */
      ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    } /* No action required */
    #endif
  }
} /* End of Check if the right EIC interrupt */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Icu_Gtm_ServiceTimestamp
**
** Service ID            : None
**
** Description           : This service routine captures the channel's Timestamp
**                         data based on its active edge configuration.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel, LulCapturedTimestampVal
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : ICU_TIMESTAMP_API in STD_ON
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelUserRegConfig, Icu_GpChannelRamData
**                         Icu_GpTimeStampData
**
** Functions invoked     : Icu_HW_Gtm_StopCountMeasurement, pIcuNotificationPointer
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_118, ICU_DUD_ACT_118_GLB001, ICU_DUD_ACT_118_GLB002, ICU_DUD_ACT_118_GLB003
***********************************************************************************************************************/
#if (ICU_TIMESTAMP_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_CODE_FAST) Icu_Gtm_ServiceTimestamp(Icu_ChannelType LddChannel, uint32 LulCapturedTimestampVal)          /* PRQA S 1505 # JV-01 */
{
  #if (ICU_NOTIFICATION_CONFIG == STD_ON)
  /* Defining a pointer to point to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  #endif /* End of #if (ICU_NOTIFICATION_CONFIG == STD_ON) */
  /* Defining a pointer to point to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  /* Defining a pointer to point to the time stamp data */
  P2VAR(volatile Icu_TimeStampChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpTimestampdata;
  /* Local variable used to store the ram index of the channel */
  uint8 LucRamIndex;

  #if (ICU_NOTIFICATION_CONFIG == STD_ON)
  /* Update the channel pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  #endif /* End of #if (ICU_NOTIFICATION_CONFIG == STD_ON) */
  /* Load timer channel configuration pointer and channel properties */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannel];
  /* Read channel ram index */
  LucRamIndex = LpChannelUserRegConfig->ucRamDataIndex;
  /* Read the Timestamp channel data pointer */
  LpTimestampdata = &Icu_GpTimeStampData[LucRamIndex];
  /* Check if timestamp capturing reached end of the buffer */
  if ((LpTimestampdata->usTimestampIndex) < (LpTimestampdata->usBufferSize))                                            /* PRQA S 0404 # JV-01 */
  {
    /* Update the buffer pointer with current timestamp */
    *(LpTimestampdata->pBufferPointer) = LulCapturedTimestampVal;
    /* Update the timstamp index */
    (LpTimestampdata->usTimestampIndex)++;                                                                              /* PRQA S 3383, 3387 # JV-01, JV-01 */
    /* Update the buffer index */
    (LpTimestampdata->pBufferPointer)++;                                                                                /* PRQA S 3387 # JV-01 */

    /* Check whether the timestamp index has reached the end of buffer */
    if ((LpTimestampdata->usTimestampIndex) >= (LpTimestampdata->usBufferSize))                                         /* PRQA S 0404 # JV-01 */
    {
      /*  Check if buffer is configured as circular */
      if (((uint8)(LpChannelUserRegConfig->ucChannelProperties & ICU_TS_CIRCULAR_BUFFER_MASK)) ==
                                                                                          ICU_TS_CIRCULAR_BUFFER_MASK)
      {
        /* Reset buffer pointer and index */
        LpTimestampdata->usTimestampIndex = (uint16)ICU_BUFFER_IDX_INIT_VAL;
        LpTimestampdata->pBufferPointer = LpTimestampdata->pBufferPointer - LpTimestampdata->usBufferSize;              /* PRQA S 0404, 0488 # JV-01, JV-01 */
      }
      else
      {
        /* Stop the hardware channel */
        Icu_HW_Gtm_StopCountMeasurement(LddChannel);
      }
    } /* else No action required */
    /* End of ((LpTimestampdata->usTimestampIndex) >= (LpTimestampdata->usBufferSize)) */
    /* Notify if the configured number of timestamps are captured and notification is enabled */
    #if (ICU_NOTIFICATION_CONFIG == STD_ON)
    if ((uint8)ICU_TRUE == Icu_GpChannelRamData[LddChannel].ucNotificationEnable)                                       /* PRQA S 0404, 3416, 4304 # JV-01, JV-01, JV-01 */
    {
      (LpTimestampdata->usTimestampsCounter)++;                                                                         /* PRQA S 3383, 3387 # JV-01, JV-01 */

      if ((LpTimestampdata->usTimestampsCounter) == (LpTimestampdata->usNotifyInterval))                                /* PRQA S 0404 # JV-01 */
      {
        /* Reset the number of timestamp captured counter */
        LpTimestampdata->usTimestampsCounter = (uint16)ICU_ZERO;

        /* Check if the function pointer address is present for particular channel */
        if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
        {
          /* callback notification */
          LpChannelConfig->pIcuNotificationPointer();
        } /* else No action required */
      } /* else No action required */
    } /* else No action required */
    #endif /* if (ICU_NOTIFICATION_CONFIG == STD_ON) */
  } /* else No action required */
} /* End of Internal function Icu_ServiceTimestamp */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name         : Icu_HW_Gtm_GetPulseData
**
** Service ID            : None
**
** Description           : This service get perform hardware checking for APIs
**                         Icu_GetInputState, Icu_GetTimeElapsed and Icu_GetDutyCycleValues function
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : ICU_SIGNAL_MEASUREMENT_API and ICU_EDGE_DETECT_API = STD_ON
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelUserRegConfig
**                         Icu_GpSignalMeasurementData, Icu_GpChannelRamData
**
** Functions invoked     : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION
**
** Registers Used        : TIM[i]_CH[x]_IRQ_NOTIFY, TIM[i]_CH[x]_GPR0, TIM[i]_CH[x]_GPR1
**
** Reference ID          : ICU_DUD_ACT_119, ICU_DUD_ACT_119_REG001, ICU_DUD_ACT_119_GLB001
** Reference ID          : ICU_DUD_ACT_119_GLB002, ICU_DUD_ACT_119_GLB003
** Reference ID          : ICU_DUD_ACT_119_CRT001, ICU_DUD_ACT_119_CRT002
***********************************************************************************************************************/
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON) || (ICU_EDGE_DETECT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Gtm_GetPulseData(Icu_ChannelType LddChannel)
{
  /* Defining a pointer to point to the GTM Timer TIM registers */
  P2VAR(Icu_GtmTimerTimRegs, AUTOMATIC, ICU_CONFIG_DATA) LpGtmTimerTimRegs;                                             /* PRQA S 3432 # JV-01 */
  /* Defining a pointer to point to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* Local variable contains channel configured mode */
  Icu_MeasurementModeType LddMeasurementMode;
  /* Local variable contains the channel RAM index */
  volatile uint8 LucRamIndex;
  /* Update the channel pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Read the channel's mode */
  LddMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  /* Get base address of GTM channel configured */
  LpGtmTimerTimRegs = LpChannelConfig->pCntlRegs;                                                                       /* PRQA S 0317 # JV-01 */
  /* Enter Critical Section */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  /* Check if a period has been elapse */
  if (ICU_NEWVAL_IRQ_EN == (LpGtmTimerTimRegs->ulIRQNOTIFYRegs & ICU_NEWVAL_IRQ_EN))
  {
    /* Set channel input status as active */
    Icu_GpChannelRamData[LddChannel].ucChannelStatus = (uint8)ICU_ACTIVE;
    /* Reset the completed flag */
    LpGtmTimerTimRegs->ulIRQNOTIFYRegs = ICU_NEWVAL_IRQ_EN;
    /* Dummy read */
    LpGtmTimerTimRegs->ulIRQNOTIFYRegs;
    /* If mode ICU_MODE_SIGNAL_MEASUREMENT */
    if (ICU_MODE_SIGNAL_MEASUREMENT == LddMeasurementMode)
    {
      #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
      /* Read channel ram index */
      LucRamIndex = (&Icu_GpChannelUserRegConfig[LddChannel])->ucRamDataIndex;
      /* Read Active time */
      Icu_GpSignalMeasurementData[LucRamIndex].ulSignalActiveTime = (LpGtmTimerTimRegs->ulGPR0Regs & ICU_DOUBLE_CNTX);  /* PRQA S 0404 # JV-01 */
      /* Read Period time */
      Icu_GpSignalMeasurementData[LucRamIndex].ulSignalPeriodTime = (LpGtmTimerTimRegs->ulGPR1Regs & ICU_DOUBLE_CNTX);  /* PRQA S 0404 # JV-01 */
      /* Check if NEWVAL occur during this operation */
      if (ICU_NEWVAL_IRQ_EN == (LpGtmTimerTimRegs->ulIRQNOTIFYRegs & ICU_NEWVAL_IRQ_EN))
      {
        /* Read again the new Active time */
        Icu_GpSignalMeasurementData[LucRamIndex].ulSignalActiveTime =                                                   /* PRQA S 0404 # JV-01 */
                                                                    (LpGtmTimerTimRegs->ulGPR0Regs & ICU_DOUBLE_CNTX);
        /* Read again the new Period time */
        Icu_GpSignalMeasurementData[LucRamIndex].ulSignalPeriodTime =                                                   /* PRQA S 0404 # JV-01 */
                                                                    (LpGtmTimerTimRegs->ulGPR1Regs & ICU_DOUBLE_CNTX);
        /* Reset the completed flag */
        LpGtmTimerTimRegs->ulIRQNOTIFYRegs = ICU_NEWVAL_IRQ_EN;
      } /* No require action */
      /* Set the blResultComplete as TRUE */
      Icu_GpChannelRamData[LddChannel].blResultComplete = ICU_TRUE;
      #endif
    } /* else no action */
  } /* else no action */
  /* EXIT Critical Section */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
} /* End of Internal function Icu_HW_Gtm_GetPulseData */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of Icu_HW_Gtm_GetPulseData */
#endif /* End of ICU_GTM_TIMER_UNIT_USED == STD_ON */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
