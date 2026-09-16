/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu_TAUD_LLDriver.c                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Low level Driver code of the OCU Driver Component                                                                  */
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
 *  1.4.0  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01
 *  1.3.1  27/02/2025  : As part of QAC message 11.6.0 support, following changes are made:
 *                       1. Remove message 3883
 *                       2. Add message 3884
 *  1.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  1.1.1  30/08/2024  : As part of Multi Variant support, following changes are made:
 *                       1. Change the way of comparison from using macro OCU_COUNT_UP to using global variable 
 *                          Ocu_GblCountingDirection in internal function: Ocu_HW_Taud_ChannelInit, 
 *                          Ocu_HW_Taud_GetCounter, Ocu_HW_Taud_StartRestartChannel, Ocu_HW_Taud_SetThreshold.
 *  1.0.1  25/10/2023  : Add comment in Register Used: TAUDnTO, TAUDnTOE in Ocu_HW_Taud_ChannelInit and 
                         Ocu_HW_Taud_ChannelDeInit, TAUDnTS in Ocu_HW_Taud_CbkNotification
                         Add comment in Functions invoked: OCU_ENTER_CRITICAL_SECTION, OCU_EXIT_CRITICAL_SECTION, 
                         Ocu_Notification_<Channel> in Ocu_HW_Taud_CbkNotification
                         Remove ID OCU_DUD_ACT_018_CRT001 and OCU_DUD_ACT_018_CRT002 in Ocu_HW_Taud_SetPinState
                         Remove ID OCU_DUD_ACT_020_CRT001 and OCU_DUD_ACT_020_CRT002 in Ocu_HW_Taud_SetPinAction
                         Remove Functions invoked RH850_SV_CLEAR_ICR_SYNCP, Registers used EICn in 
                         Ocu_HW_Taud_StartRestartChannel
                         Remove Registers used TAUDnTS, TAUDnCDRm, TAUDnCNTm, add comment in Functions invoked
                         OCU_ENTER_CRITICAL_SECTION, OCU_EXIT_CRITICAL_SECTION in Ocu_HW_Taud_StopChannel
                         Remove Functions invoked RH850_SV_CLEAR_ICR_SYNCP in Ocu_HW_Taud_EnableInterrupt 
           17/10/2023  : Remove condition check OCU_E_INT_INCONSISTENT_CONFIGURED for Dem_SetEventStatus in function
                         Ocu_HW_Tauj_CbkNotification
                         QAC message: add new 3006, 3415, 3416 and delete 1532, 2814, 2824, 2834, 2844
           09/10/2023  : Update QAC messages for Ocu_HW_Taud_ChannelInit, Ocu_HW_Taud_StartRestartChannel,
                         and Ocu_HW_Taud_CbkNotification
           25/09/2023  : In Ocu_HW_Taud_ChannelInit change the OCU driver mode for the slave channel to interval timer
                         mode, from now on the 2 channels no longer run in Synchronous Channel Operation
                         In Ocu_HW_Taud_SetPinAction move the updated ram status of ddPinActionState to the bottom
                         In Ocu_HW_Taud_StartRestartChannel and Ocu_HW_Taud_CbkNotification update the code sequence
                         since the slave channel now running independently and doesn't depend on the master channel
                         In Ocu_HW_Taud_SetThreshold update the brand condition coding rule
 *  1.0.0  29/03/2023  : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
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
/* Message (2:0317)    : Implicit conversion from a pointer to void to a pointer to object type.                      */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : This is done as per implementation requirement.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact               */
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
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
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
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Ocu.h inclusion and macro definitions */
#include "Ocu.h"
/* Included for declaration of the Callback functions Configuration */
#include "Ocu_TAUD_LLDriver.h"
/* Included for RAM variable declarations */
#include "Ocu_Ram.h"
#include "Ocu_TAU_Ram.h"
#include "Ocu_TAUD_Ram.h"
/* Included for macro definitions */
#include "Ocu_TAUD_PBTypes.h"
/* For include SV_MODE Macro */
#include "rh850_Types.h"
/* Include for interrupt consistency check */
#if (OCU_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
#include "Dem.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define OCU_TAUD_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define OCU_TAUD_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION_VALUE
#define OCU_TAUD_LLDRIVER_C_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define OCU_TAUD_LLDRIVER_C_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION_VALUE
#define OCU_TAUD_LLDRIVER_C_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (OCU_TAUD_LLDRIVER_AR_RELEASE_MAJOR_VERSION != OCU_TAUD_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Ocu_TAUD_LLDriver.c : Mismatch in Release Major Version"
#endif
#if (OCU_TAUD_LLDRIVER_AR_RELEASE_MINOR_VERSION != OCU_TAUD_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Ocu_TAUD_LLDriver.c : Mismatch in Release Minor Version"
#endif
#if (OCU_TAUD_LLDRIVER_AR_RELEASE_REVISION_VERSION != OCU_TAUD_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Ocu_TAUD_LLDriver.c : Mismatch in Release Revision Version"
#endif
#if (OCU_TAUD_LLDRIVER_SW_MAJOR_VERSION != OCU_TAUD_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Ocu_TAUD_LLDriver.c : Mismatch in Software Major Version"
#endif
#if (OCU_TAUD_LLDRIVER_SW_MINOR_VERSION != OCU_TAUD_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Ocu_TAUD_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (OCU_TIMER_IP_TAUD == STD_ON)
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name         : Ocu_HW_Taud_UnitInit
**
** Service ID            : NA
**
** Description           : This is OCU Driver component support function. This function initialize configured Units.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : Ocu_ConfigType* LpConfigPtr
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Pre-condition         : None
**
** Global Variables used : Ocu_GpTAUUnitConfig, Ocu_GaaHWIP
**
** Functions invoked     : None
**
** Registers Used        : TAUDnTPS, TAUDnBRS
**
** Reference ID          : OCU_DUD_ACT_015, OCU_DUD_ACT_015_GBL001, OCU_DUD_ACT_015_GBL002
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Taud_UnitInit(P2CONST(Ocu_ConfigType, AUTOMATIC, OCU_APPL_CONST) LpConfigPtr)
{
  #if (OCU_TAUD_CONFIG_PRESCALER_SUPPORTED == STD_ON)
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Ocu_TAUUnitConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpTAUUnitConfig;
  /* Pointer pointing to the TAUD Unit os control registers */
  P2VAR(Ocu_TAUDUnitOsRegs, AUTOMATIC, REGSPACE) LpTAUDUnitOsReg;                                                       /* PRQA S 3432 # JV-01 */
  /* Declare a Local variable to Timer Type */
  VAR(uint8, AUTOMATIC) LucTimerType;
  #endif
  /* Declare a Local variable to counting loop */
  VAR(uint8, AUTOMATIC) LucCount;
  /* Index of HWIP */
  VAR(uint8, AUTOMATIC) LucHWIPCount;

  /* Loop for all configured timer units */
  for (LucCount = (uint8)OCU_ZERO; LucCount < (uint8)OCU_TOTAL_HW_IP_CONFIG; LucCount++)
  {
    /* Load index of HWIP */
    LucHWIPCount = Ocu_GaaHWIP[LucCount].ucIndex;
    /* If HWIP is TAUD */
    if (OCU_HWIP_TAUD == LucHWIPCount)
    {
      /* Store the global pointer to the first Unit Configuration */
      Ocu_GpTAUUnitConfig =
               (P2CONST(Ocu_TAUUnitConfigType, OCU_VAR_INIT, OCU_CONFIG_DATA))LpConfigPtr->aaTimerUnitConfig[LucCount]; /* PRQA S 0316 # JV-01 */
    } /* else No action required */
  }

  #if (OCU_TAUD_CONFIG_PRESCALER_SUPPORTED == STD_ON)
  /* Update the TAU configuration pointer to point to the current TAU */
  LpTAUUnitConfig = Ocu_GpTAUUnitConfig;
  /* Loop for all configured TAU units */
  for (LucCount = (uint8)OCU_ZERO; LucCount < (uint8)OCU_TOTAL_TAU_UNITS_CONFIGURED; LucCount++)
  {
    /* Read the Timer Type for the given channel */
    LucTimerType = LpTAUUnitConfig[LucCount].ucTimerType;
    /* If HWIP is TAUD */
    if (OCU_HW_TAUD == LucTimerType)
    {
      /* Initialize the pointer to OS register base address */
      LpTAUDUnitOsReg = (P2VAR(Ocu_TAUDUnitOsRegs, AUTOMATIC, REGSPACE))(LpTAUUnitConfig[LucCount].pTAUUnitOsCntlRegs); /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Load the configured pre-scaler value */
      LpTAUDUnitOsReg->usTAUDnTPS = LpTAUUnitConfig[LucCount].usPrescaler;
      /* Load the configured baud rate value */
      LpTAUDUnitOsReg->ucTAUDnBRS = LpTAUUnitConfig[LucCount].ucBaudRate;
    } /* else No action required */
  } /* End of LucCount < (uint8)OCU_TOTAL_TAU_UNITS_CONFIGURED */
  #endif /* End of (OCU_TAUD_CONFIG_PRESCALER_SUPPORTED == STD_ON) */
} /* End of API Ocu_HW_Taud_UnitInit */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Ocu_HW_Taud_ChannelInit
**
** Service ID            : NA
**
** Description           : This is OCU Driver component support function. This function sets the clock prescaler,
**                         timer mode. This function also disables the interrupts and resets the interrupt
**                         request pending flags.
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
** Return Parameter      : None
**
** Pre-condition         : None
**
** Global Variables used : Ocu_GpChannelConfig, Ocu_GpChannelRamData, Ocu_GpTAUUnitConfig, Ocu_GblCountingDirection
**
** Functions invoked     : Ocu_HW_Taud_DisableInterrupt, RH850_SV_SET_ICR_SYNCP
**
** Registers Used        : TAUDnCDRm, TAUDnCMORm, TAUD3INTNOSEL0, TAUD3INTNOSEL1, TAUDnTS, TAUDnTO, TAUDnTOE
**
** Reference ID          : OCU_DUD_ACT_016, OCU_DUD_ACT_016_GBL001, OCU_DUD_ACT_016_GBL002 OCU_DUD_ACT_016_GBL003
** Reference ID          : OCU_DUD_ACT_016_GBL004, OCU_DUD_ACT_016_GBL005 OCU_DUD_ACT_016_GBL006, OCU_DUD_ACT_016_GBL007
** Reference ID          : OCU_DUD_ACT_016_GBL008 OCU_DUD_ACT_016_GBL009, OCU_DUD_ACT_016_GBL010, OCU_DUD_ACT_016_GBL011
** Reference ID          : OCU_DUD_ACT_016_GBL012
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Taud_ChannelInit(Ocu_ChannelType LddChannel)                                        /* PRQA S 3006 # JV-01 */
{
  /* TAU unit config data */
  P2CONST(Ocu_TAUChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpTAUChannelConfigData;
  /* Pointer to the channel configuration */
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpChannelConfig;
  /* Pointer used for TAUD master channel control registers */
  P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDMasterChannelRegs;                                          /* PRQA S 3432 # JV-01 */
  /* Pointer pointing to the TAUD Unit control registers */
  P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserRegs;                                                  /* PRQA S 3432 # JV-01 */
  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  /* Set TAU channel config data pointer */
  LpTAUChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                         /* PRQA S 0317 # JV-01 */

  #if (OCU_TAUD3_UNIT_USED == STD_ON)
  if(NULL_PTR != LpTAUChannelConfigData->pTAUD3INTNOSELxReg)
  {
    /* Assign interrupt number for channels was configured in TAUD3 for both master and slave channels. */
    RH850_SV_SET_ICR_SYNCP(32, LpTAUChannelConfigData->pTAUD3INTNOSELxReg,                                              /* PRQA S 1006 # JV-01 */
                                                      LpTAUChannelConfigData->ulTAUD3SelectInterruptMask);
  } /* else No action required */
  #endif

  /* Initialize Timer Channels */
  /* Set the mode of Master TAUD (slave channel - 1) timer mode to interval mode */
  *((volatile uint16 *)(LpTAUChannelConfigData->pMasterCMORReg)) = LpTAUChannelConfigData->usClockSelection;            /* PRQA S 0316 # JV-01 */
  /* Set the mode of Slave TAUD timer mode to interval mode */
  *((volatile uint16 *)(LpTAUChannelConfigData->pCMORReg)) = LpTAUChannelConfigData->usClockSelection;                  /* PRQA S 0316 # JV-01 */
  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  /* Set the Notification status as OCU_FALSE */
  Ocu_GpChannelRamData[LddChannel].blNotifyStatus = OCU_FALSE;
  #endif
  /* Disable the Interrupt processing of the current channel */
  Ocu_HW_Taud_DisableInterrupt(LddChannel);
  /* Assign the timer status to the Channel */
  Ocu_GpChannelRamData[LddChannel].blChannelStatus = OCU_CH_STOPPED;
  /* Disable rewrite the count value for the slave channel data register in the next cycle */
  Ocu_GpChannelRamData[LddChannel].blRequireRewriteCountValue = OCU_FALSE;
  /* Check the counting direction */
  if (OCU_UPCOUNTING == Ocu_GblCountingDirection)                                                                       /* PRQA S 3416 # JV-01 */
  {
    /* Load the last HW threshold data to the local */
    Ocu_GpChannelRamData[LddChannel].ddHwLastThreshold =
                            (LpChannelConfig->ulDefaultThreshold) * (uint32)(LpChannelConfig->usChannelTickDuration);   /* PRQA S 3384 # JV-01 */
  }
  else /* Else OCU_DOWNCOUNTING */
  {
    Ocu_GpChannelRamData[LddChannel].ddHwLastThreshold = (((LpChannelConfig->ulDefaultThreshold + (uint32)OCU_ONE) *    /* PRQA S 3383, 3384 # JV-01, JV-01 */
                                                  (uint32)(LpChannelConfig->usChannelTickDuration)) - (uint32)OCU_ONE); /* PRQA S 3384 # JV-01 */
  } /* OCU_UPCOUNTING == Ocu_GblCountingDirection */

  /* Assign the pin action state value into ram */
  #if (OCU_SET_PIN_ACTION_API == STD_ON)
  Ocu_GpChannelRamData[LddChannel].ddPinActionState = OCU_DISABLE;
  #endif
  /* Set the pointer to TAU register base address of Master Channel */
  LpTAUDMasterChannelRegs = (P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE))LpTAUChannelConfigData->pMasterCDRReg; /* PRQA S 0316, 3432 # JV-01, JV-01 */

  /* Set default max HW counter tick value Master channel */
  LpTAUDMasterChannelRegs->usTAUDnCDRm = (uint16)((LpChannelConfig->ulMaxCounterValue *                                 /* PRQA S 3384 # JV-01 */
                                          (uint32)LpChannelConfig->usChannelTickDuration) +                             /* PRQA S 3384 # JV-01 */
                                          ((uint32)LpChannelConfig->usChannelTickDuration - (uint32)OCU_ONE));          /* PRQA S 3384 # JV-01 */

  /* Initialize pointer to the base address of the current timer user control registers */
  LpTAUDUnitUserRegs = (P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE))                                               /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                          Ocu_GpTAUUnitConfig[LpChannelConfig->ucTimerUnitIndex].pTAUUnitUserCntlRegs;
  /* Set the default pin level if enabled parameter OcuOutputPinUsed */
  if (OCU_TRUE == LpChannelConfig->blOutputPinUsed)
  {
    /* Reset the Channel Output Enable Register for slave channel, pin level will be controlled by software */
    LpTAUDUnitUserRegs->usTAUDnTOE &= ~(LpTAUChannelConfigData->usChannelBitValue);
    /* Check that the default pin state is a high level for the slave channel */
    if (OCU_HIGH == LpChannelConfig->enOutputPinDefaultState)
    {
      /* Set the pin level for the associated TAUDnOm pin for the slave channel */
      LpTAUDUnitUserRegs->usTAUDnTO |= LpTAUChannelConfigData->usChannelBitValue;
    }
    else
    {
      /* Set the pin level for the associated TAUDnOm pin for the slave channel */
      LpTAUDUnitUserRegs->usTAUDnTO &= ~(LpTAUChannelConfigData->usChannelBitValue);
    }
  } /* else No action required */
  /* Start the master channel */
  LpTAUDUnitUserRegs->usTAUDnTS = LpTAUChannelConfigData->usChannelBitValue >> OCU_ONE;
} /* End of API Ocu_HW_Taud_ChannelInit */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Ocu_HW_Taud_ChannelDeInit
**
** Service ID            : NA
**
** Description           : This is OCU Driver component support function. This function resets all the HW Registers.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
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
** Global Variables      : Ocu_GpChannelConfig, Ocu_GpChannelRamData, Ocu_GpTAUUnitConfig
**
** Functions invoked     : Ocu_HW_Taud_DisableInterrupt
**
** Registers used        : TAUDnCDRm, TAUDnCMORm, TAUD3INTNOSEL0, TAUD3INTNOSEL1, TAUDnTT, TAUDnTO, TAUDnTOE
**
** Reference ID          : OCU_DUD_ACT_017, OCU_DUD_ACT_017_GBL001, OCU_DUD_ACT_017_GBL002
** Reference ID          : OCU_DUD_ACT_017_GBL003, OCU_DUD_ACT_017_GBL004, OCU_DUD_ACT_017_GBL005
** Reference ID          : OCU_DUD_ACT_017_GBL006, OCU_DUD_ACT_017_GBL007
** Reference ID          : OCU_DUD_ACT_017_GBL008, OCU_DUD_ACT_017_GBL009
** Reference ID          : OCU_DUD_ACT_017_GBL010, OCU_DUD_ACT_017_GBL011
** Reference ID          : OCU_DUD_ACT_017_GBL012, OCU_DUD_ACT_017_GBL013
***********************************************************************************************************************/

#if (OCU_DE_INIT_API == STD_ON)
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Taud_ChannelDeInit(Ocu_ChannelType LddChannel)                                      /* PRQA S 3006 # JV-01 */
{
  /* TAU unit config data */
  P2CONST(Ocu_TAUChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpTAUChannelConfigData;
  /* Pointer to the channel configuration */
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpChannelConfig;
  /* Pointer used for TAUD Slave channel control registers */
  P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;                                                 /* PRQA S 3432 # JV-01 */
  /* Pointer used for TAUD Master channel control registers */
  P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDMasterChannelReg;                                           /* PRQA S 3432 # JV-01 */
  /* Pointer pointing to the TAUD Unit control registers */
  P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserRegs;                                                  /* PRQA S 3432 # JV-01 */
  /* Update the channel configuration pointer to point to the current slave channel */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  /* Set TAU channel config data pointer */
  LpTAUChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                         /* PRQA S 0317 # JV-01 */

  /* Initialize pointer to the base address of the current timer user control registers */
  LpTAUDUnitUserRegs = (P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE))                                               /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                           Ocu_GpTAUUnitConfig[LpChannelConfig->ucTimerUnitIndex].pTAUUnitUserCntlRegs;
  /* Reset the default pin level if enabled parameter OcuOutputPinUsed */
  if (OCU_TRUE == LpChannelConfig->blOutputPinUsed)
  {
    /* Reset the output the Channel Output Enable Register - slave channel */
    LpTAUDUnitUserRegs->usTAUDnTOE &= ~(LpTAUChannelConfigData->usChannelBitValue);
    /* Reset the output level to the default value - slave channel */
    LpTAUDUnitUserRegs->usTAUDnTO &= ~(LpTAUChannelConfigData->usChannelBitValue);
  } /* else No action required */
  /* Stop the master as well as the configured slave timer. */
  LpTAUDUnitUserRegs->usTAUDnTT = (LpTAUChannelConfigData->usChannelBitValue) |
                                                                (LpTAUChannelConfigData->usChannelBitValue >> OCU_ONE);

  #if (OCU_TAUD3_UNIT_USED == STD_ON)
  if(NULL_PTR != LpTAUChannelConfigData->pTAUD3INTNOSELxReg)
  {
    /* Disable interrupt number selection for channels was configured in TAUD3 - master and slave channel. */
    RH850_SV_CLEAR_ICR_SYNCP(32, LpTAUChannelConfigData->pTAUD3INTNOSELxReg,                                            /* PRQA S 1006 # JV-01 */
                                                      ~LpTAUChannelConfigData->ulTAUD3SelectInterruptMask);
  } /* else No action required */
  #endif

  /* De-initialize Timer Channels */
  /* Reset the CMORm register of the configured channel - Slave channel */
  *((volatile uint16 *)(LpTAUChannelConfigData->pCMORReg)) = (uint16)OCU_ZERO;                                          /* PRQA S 0316 # JV-01 */
  /* Reset the CMORm register of the configured channel - Master channel */
  *((volatile uint16 *)(LpTAUChannelConfigData->pMasterCMORReg)) = (uint16)OCU_ZERO;                                    /* PRQA S 0316 # JV-01 */

  /* Set the pointer to TAU register base address - Slave channel */
  LpTAUDChannelReg = (P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE))LpTAUChannelConfigData->pCDRReg;              /* PRQA S 0316, 3432 # JV-01, JV-01 */
  /* Set the pointer to TAU register base address - Master channel */
  LpTAUDMasterChannelReg = (P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE))LpTAUChannelConfigData->pMasterCDRReg;  /* PRQA S 0316, 3432 # JV-01, JV-01 */
  /* Reset the CDRm register of the configured channel - Slave channel  */
  LpTAUDChannelReg->usTAUDnCDRm = OCU_SET_16BIT;
  /* Reset the CDRm register of the configured channel - Master channel  */
  LpTAUDMasterChannelReg->usTAUDnCDRm = OCU_SET_16BIT;

  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  /* Set the Notification status as OCU_FALSE */
  Ocu_GpChannelRamData[LddChannel].blNotifyStatus = OCU_FALSE;
  #endif
  /* Clear the default threshold value into ram */
  Ocu_GpChannelRamData[LddChannel].ddHwLastThreshold = (uint32)OCU_ZERO;
  /* Disable the Interrupt processing of the current channel */
  Ocu_HW_Taud_DisableInterrupt(LddChannel);
  /* Assign the timer status to the Channel */
  Ocu_GpChannelRamData[LddChannel].blChannelStatus = OCU_CH_STOPPED;
  /* Disable rewrite the count value for the slave channel data register in the next cycle */
  Ocu_GpChannelRamData[LddChannel].blRequireRewriteCountValue = OCU_FALSE;
  #if (OCU_SET_PIN_ACTION_API == STD_ON)
  /* Assign the pin action state value into ram */
  Ocu_GpChannelRamData[LddChannel].ddPinActionState = OCU_DISABLE;
  #endif
} /* End of API Ocu_HW_Taud_ChannelDeInit */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (OCU_DE_INIT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Ocu_HW_Taud_SetPinState
**
** Service ID            : NA
**
** Description           : This is OCU Low Layer Driver component support API Ocu_SetPinState.
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
** Pre-condition         : Ocu_Init was invoked before and OCU_SET_PIN_STATE_API must be STD_ON
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GpTAUUnitConfig
**
** Functions invoked     : OCU_ENTER_CRITICAL_SECTION, OCU_EXIT_CRITICAL_SECTION
**
** Registers used        : TAUDnTOE, TAUDnTO
**
** Reference ID          : OCU_DUD_ACT_018, OCU_DUD_ACT_018_GBL001, OCU_DUD_ACT_018_GBL002
***********************************************************************************************************************/
#if (OCU_SET_PIN_STATE_API == STD_ON)
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Taud_SetPinState(Ocu_ChannelType LddChannel, Ocu_PinStateType LddPinState)
{
  /* TAU unit config data */
  P2CONST(Ocu_TAUChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpTAUChannelConfigData;
  /* Pointer to the channel configuration */
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpChannelConfig;
  /* Pointer pointing to the TAUD Unit control registers */
  P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserRegs;                                                  /* PRQA S 3432 # JV-01 */
  /* Declare a Local variable to store the current setting value of TAUDnTOE - TAUDn Channel Output Enable Register */
  VAR(uint16, AUTOMATIC) LusLastToeValue;
  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  /* Set TAU channel config data pointer */
  LpTAUChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                         /* PRQA S 0317 # JV-01 */
  /* Initialize pointer to the base address of the current timer user control registers */
  LpTAUDUnitUserRegs = (P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE))                                               /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                          Ocu_GpTAUUnitConfig[LpChannelConfig->ucTimerUnitIndex].pTAUUnitUserCntlRegs;
  /* Save the current value of the TAUDnTOE register for the selected slave channel */
  LusLastToeValue = LpTAUDUnitUserRegs->usTAUDnTOE & LpTAUChannelConfigData->usChannelBitValue;
  /* Disable the independent timer output function (to be controlled by software) */
  LpTAUDUnitUserRegs->usTAUDnTOE &= ~(LpTAUChannelConfigData->usChannelBitValue);
  /* Set the current output level of the associate pin with the current channel */
  if (OCU_HIGH == LddPinState)
  {
    /* Set one into the corresponding bit of TAUDnTO register */
    LpTAUDUnitUserRegs->usTAUDnTO |= LpTAUChannelConfigData->usChannelBitValue;
  }
  else /* LddPinState == OCU_LOW */
  {
    /* Set zero into the corresponding bit of TAUDnTO register */
    LpTAUDUnitUserRegs->usTAUDnTO &= ~(LpTAUChannelConfigData->usChannelBitValue);
  } /* End of Set the current output level */
  /* Write back the saved value of the TAUDnTOE register for the selected slave channel */
  LpTAUDUnitUserRegs->usTAUDnTOE |= LusLastToeValue;
} /* End of API Ocu_HW_Taud_SetPinState */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* OCU_SET_PIN_STATE_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Ocu_HW_Taud_GetCounter
**
** Service ID            : NA
**
** Description           : This is OCU Low Layer Driver component support API Ocu_GetCounter.
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
** Return Value          : Ocu_ValueType
**
** Pre-condition         : Ocu_Init was invoked before and OCU_GET_COUNTER_API
**                       : OCU_SET_ABSOLUTE_THRESHOLD_API, OCU_SET_RELATIVE_THRESHOLD_API must be STD_ON
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GblCountingDirection
**
** Functions invoked     : None
**
** Registers used        : TAUDnCDRm, TAUDnCNTm
**
** Reference ID          : OCU_DUD_ACT_019, OCU_DUD_ACT_019_GBL001
***********************************************************************************************************************/
#if (((OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)) \
                                                                                || (OCU_GET_COUNTER_API == STD_ON))
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Ocu_ValueType, OCU_PRIVATE_CODE) Ocu_HW_Taud_GetCounter(Ocu_ChannelType LddChannel)
{
  /* Pointer to the channel configuration */
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpChannel;
  /* TAU unit config data */
  P2CONST(Ocu_TAUChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpTAUChannelConfigData;
  /* Defining a pointer to point to the TAUD master registers */
  P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDMasterChannelRegs;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Variable to hold the max tick from free-running counter */
  VAR(Ocu_ValueType, AUTOMATIC) LddHwMasterCDRCounterValue;
  /* Variable to hold the current counter value of master free-running counter */
  VAR(Ocu_ValueType, AUTOMATIC) LddHwMasterCNTCounterValue;
  /* Variable to hold timer Elapsed time */
  VAR(Ocu_ValueType, AUTOMATIC) LddTimeElapsed;
  /* Updating the channel configuration parameter to the current channel */
  LpChannel = &Ocu_GpChannelConfig[LddChannel];
  /* Set TAU channel config data pointer */
  LpTAUChannelConfigData = LpChannel->pHWIPChannelConfig;                                                               /* PRQA S 0317 # JV-01 */

  /* Set the pointer to TAU register base address of Master channel */
  LpTAUDMasterChannelRegs = (P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE))LpTAUChannelConfigData->pMasterCDRReg; /* PRQA S 0316, 3432 # JV-01, JV-01 */
  /* Read the max counter value from the master free-running counter */
  LddHwMasterCDRCounterValue = (uint32)LpTAUDMasterChannelRegs->usTAUDnCDRm;
  /* Read the current value from the master free-running counter */
  LddHwMasterCNTCounterValue = (uint32)LpTAUDMasterChannelRegs->usTAUDnCNTm;

    /* Check the counting direction */
  if (OCU_UPCOUNTING == Ocu_GblCountingDirection)                                                                       /* PRQA S 3416 # JV-01 */
  {
    if (LddHwMasterCDRCounterValue >= LddHwMasterCNTCounterValue)
    {
      /* Read the elapsed time on the master channel */
      LddTimeElapsed = (LddHwMasterCDRCounterValue - LddHwMasterCNTCounterValue)
                                                                        / (uint32)(LpChannel->usChannelTickDuration);
    }
    else
    {
      /* The master channel is not started yet, return zero */
      LddTimeElapsed = (uint32)OCU_ZERO;
    }
  }
  else /* Else OCU_DOWNCOUNTING */
  {
    if (LddHwMasterCDRCounterValue >= LddHwMasterCNTCounterValue)
    {
      /* Read the elapsed time on the master channel */
      LddTimeElapsed = LddHwMasterCNTCounterValue / (uint32)(LpChannel->usChannelTickDuration);
    }
    else
    {
      /* The master channel is not started yet, return counter max value */
      LddTimeElapsed = LpChannel->ulMaxCounterValue;
    }
  } /* OCU_UPCOUNTING == Ocu_GblCountingDirection */
  
  return (LddTimeElapsed);
} /* End of API Ocu_HW_Taud_GetCounter */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of precompile condition */
/***********************************************************************************************************************
** Function Name         : Ocu_HW_Taud_SetPinAction
**
** Service ID            : NA
**
** Description           : This is OCU Low Layer Driver component support API Ocu_SetPinAction.
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
** Pre-condition         : Ocu_Init was invoked before and OCU_SET_PIN_ACTION_API must be STD_ON
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GpChannelRamData, Ocu_GpTAUUnitConfig
**
** Functions invoked     : Ocu_HW_Taud_EnableInterrupt, Ocu_HW_Taud_DisableInterrupt
**
** Registers used        : TAUDnTOE
**
** Reference ID          : OCU_DUD_ACT_020, OCU_DUD_ACT_020_GBL001
***********************************************************************************************************************/
#if (OCU_SET_PIN_ACTION_API == STD_ON)
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Taud_SetPinAction(Ocu_ChannelType LddChannel, Ocu_PinActionType LddPinAction)
{
  /* TAU unit config data */
  P2CONST(Ocu_TAUChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpTAUChannelConfigData;
  /* Pointer to the channel configuration */
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpChannelConfig;
  /* Pointer pointing to the TAUD Unit control registers */
  P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserRegs;                                                  /* PRQA S 3432 # JV-01 */
  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  /* Set TAU channel config data pointer */
  LpTAUChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                         /* PRQA S 0317 # JV-01 */
  /* Initialize pointer to the base address of the current timer user control registers */
  LpTAUDUnitUserRegs = (P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE))                                               /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                           Ocu_GpTAUUnitConfig[LpChannelConfig->ucTimerUnitIndex].pTAUUnitUserCntlRegs;
  /* Check the input LddPinAction */
  if ((OCU_SET_HIGH == LddPinAction) || (OCU_SET_LOW == LddPinAction))
  {
    /* Disable the independent timer output function (to be controlled by software) */
    LpTAUDUnitUserRegs->usTAUDnTOE &= ~(LpTAUChannelConfigData->usChannelBitValue);
    /* Enable interrupt in case of set high and low time - high low action handle by interrupt of slave channel */
    Ocu_HW_Taud_EnableInterrupt(LddChannel);
  }
  else if (OCU_TOGGLE == LddPinAction)
  {
    /* Enables the independent timer output function (to be controlled by hardware) */
    LpTAUDUnitUserRegs->usTAUDnTOE |= LpTAUChannelConfigData->usChannelBitValue;
    /* Disable the interrupt if the channel notification was not enabled and no need to rewrite the slave
    channel data register at the next cycle */
    if ((OCU_FALSE == Ocu_GpChannelRamData[LddChannel].blRequireRewriteCountValue)                                      /* PRQA S 3416 # JV-01 */
    #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
    && (OCU_FALSE == Ocu_GpChannelRamData[LddChannel].blNotifyStatus)                                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
    #endif
    )
    {
      Ocu_HW_Taud_DisableInterrupt(LddChannel);
    } /* else No action required */
  }
  else
  {
    /* Disable the independent timer output function (to be controlled by software) */
    LpTAUDUnitUserRegs->usTAUDnTOE &= ~(LpTAUChannelConfigData->usChannelBitValue);
    /* Disable the interrupt if the channel notification was not enabled and no need to rewrite the slave
    channel data register at the next cycle */
    if ((OCU_FALSE == Ocu_GpChannelRamData[LddChannel].blRequireRewriteCountValue)                                      /* PRQA S 3416 # JV-01 */
    #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
    && (OCU_FALSE == Ocu_GpChannelRamData[LddChannel].blNotifyStatus)                                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
    #endif
    )
    {
      Ocu_HW_Taud_DisableInterrupt(LddChannel);
    } /* else No action required */
  } /* Check the input LddPinAction */
} /* End of API Ocu_HW_Taud_SetPinAction */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* OCU_SET_PIN_ACTION_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Ocu_HW_Taud_StartRestartChannel
**
** Service ID            : NA
**
** Description           : This routine service sets the new threshold into hardware, note that every value used
**                         in this function is hardware value
**
** Sync/Async            : Synchronous
**
** Reentrancy            : None Reentrant
**
** Input Parameters      : LddChannel, LddHwNewThreshold
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : Ocu_Init was invoked before
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GpTAUUnitConfig, Ocu_GpChannelRamData, Ocu_GblCountingDirection
**
** Functions invoked     : Ocu_HW_Taud_EnableInterrupt
**
** Registers used        : TAUDnTS, TAUDnCNTm, TAUDnCDRm, TAUDnTT
**
** Reference ID          : OCU_DUD_ACT_022, OCU_DUD_ACT_022_GBL001, OCU_DUD_ACT_022_GBL002
** Reference ID          : OCU_DUD_ACT_022_GBL003, OCU_DUD_ACT_022_GBL004, OCU_DUD_ACT_022_GBL005
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE)Ocu_HW_Taud_StartRestartChannel(Ocu_ChannelType LddChannel,Ocu_ValueType LddHwNewThreshold)
{
  /* TAU unit config data */
  P2CONST(Ocu_TAUChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpTAUChannelConfigData;
  /* Pointer to the channel configuration */
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpChannelConfig;
  /* Pointer used for master TAUD channel control registers */
  P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelMasterRegs;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Pointer used for slave TAUD channel control registers */
  P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelSlaveRegs;                                           /* PRQA S 3432 # JV-01 */
  /* Pointer pointing to the TAUD Unit control registers */
  P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserRegs;                                                  /* PRQA S 3432 # JV-01 */
  /* Variable to hold the current time based on count up or count down */
  VAR(Ocu_ValueType, AUTOMATIC) LddHwCounterValue;
  /* Variable to hold the max tick from free-running counter */
  VAR(Ocu_ValueType, AUTOMATIC) LddHwMasterCDRCounterValue;
  /* Variable to hold the current counter value of master free-running counter */
  VAR(Ocu_ValueType, AUTOMATIC) LddHwMasterCNTCounterValue;
  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];
  /* Set TAU channel config data pointer */
  LpTAUChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                         /* PRQA S 0317 # JV-01 */
  /* Initialize pointer to the base address of the current timer user control registers */
  LpTAUDUnitUserRegs = (P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE))                                               /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                          Ocu_GpTAUUnitConfig[LpChannelConfig->ucTimerUnitIndex].pTAUUnitUserCntlRegs;
  /* Set the pointer to TAU register base address of Slave Channel */
  LpTAUDChannelSlaveRegs = (P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE))LpTAUChannelConfigData->pCDRReg;        /* PRQA S 0316, 3432 # JV-01, JV-01 */
  /* Set the pointer to TAU register base address of Master Channel */
  LpTAUDChannelMasterRegs = (P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE))LpTAUChannelConfigData->pMasterCDRReg; /* PRQA S 0316, 3432 # JV-01, JV-01 */
  /* Read the max counter value from the master free-running counter */
  LddHwMasterCDRCounterValue = (uint32)LpTAUDChannelMasterRegs->usTAUDnCDRm;
  /* Read the current counter value from the master free-running counter */
  LddHwMasterCNTCounterValue = (uint32)LpTAUDChannelMasterRegs->usTAUDnCNTm;
  /* Check the counting direction */
  if (OCU_UPCOUNTING == Ocu_GblCountingDirection)                                                                       /* PRQA S 3416 # JV-01 */
  {
    /* Check if the master channel is started or not */
    if (LddHwMasterCDRCounterValue >= LddHwMasterCNTCounterValue)
    {
      /* Calculate the current counter value based on configured counting direction */
      LddHwCounterValue = LddHwMasterCDRCounterValue - LddHwMasterCNTCounterValue;
      /* Check that the new threshold is > current master counter value interrupt will occur inside this cycle */
      if (LddHwNewThreshold > LddHwCounterValue)
      {
        /* The slave counter starts to count down from the next tick
        -> The minimum value of LddHwNewThreshold - LddHwCounterValue must be >= 2 */
        if ((LddHwNewThreshold - LddHwCounterValue) >= (uint32)OCU_TWO)                                                 /* PRQA S 3383 # JV-01 */
        {
          /* Let the slave channel count from the remaining time to the next compare match */
          LpTAUDChannelSlaveRegs->usTAUDnCDRm = (uint16)(LddHwNewThreshold - LddHwCounterValue - (uint32)OCU_TWO);      /* PRQA S 3383, 3384 # JV-01, JV-01 */
        }
        /* If the new threshold minus the current is equal to 1 the first compare match event after setting the new
        threshold will be caused by one tick of delay */
        else
        {
          /* In this case the tolerant will be plus one hardware tick */
          LpTAUDChannelSlaveRegs->usTAUDnCDRm = (uint16)OCU_ZERO;
        }
      }
      else /* Interrupt for new threshold will not occur inside this cycle */
      {
        /* Check that the master channel reaches the last tick and the new threshold = 0 */
        if (((uint32)OCU_ZERO == LddHwMasterCNTCounterValue) && ((uint32)OCU_ZERO == LddHwNewThreshold))
        {
          /* The slave timer counts down from 0 */
          LpTAUDChannelSlaveRegs->usTAUDnCDRm = (uint16)OCU_ZERO;
        }
        else
        {
          /* Set the count down value = next threshold + current timer counter */
          LpTAUDChannelSlaveRegs->usTAUDnCDRm =
                          (uint16)(LddHwMasterCNTCounterValue + LddHwNewThreshold - (uint32)OCU_ONE);                   /* PRQA S 3383, 3384 # JV-01, JV-01 */
        } /* End of check corner case */
      } /* End of checking inside/outside current cycle */
    }
    else /* Else the master channel has not been started */
    {
      /* Check if the new threshold is different from zero */
      if ((uint32)OCU_ZERO != LddHwNewThreshold)
      {
        /* Let the timer slave count from the new threshold */
        LpTAUDChannelSlaveRegs->usTAUDnCDRm = (uint16)(LddHwNewThreshold - (uint32)OCU_ONE);
      }
      else /* case of new threshold is 0 */
      {
        /* Let the timer slave count from max HW tick */
        LpTAUDChannelSlaveRegs->usTAUDnCDRm = (uint16)LddHwMasterCDRCounterValue;
      }
      /* Start the slave timer counter */
      LpTAUDUnitUserRegs->usTAUDnTS = LpTAUChannelConfigData->usChannelBitValue;
    } /* End of UPCOUNTING section */
  }
  else /* Else OCU_DOWNCOUNTING */
  {
    /* Check if the master channel is started or not */
    if (LddHwMasterCDRCounterValue >= LddHwMasterCNTCounterValue)
    {
      /* Calculate the current counter value based on configured counting direction */
      LddHwCounterValue = LddHwMasterCNTCounterValue;
      /* Check that the new threshold is < current master counter value interrupt will occur inside this cycle */
      if (LddHwNewThreshold < LddHwCounterValue)
      {
        /* The slave counter starts to count down from the next tick
        -> The minimum value of LddHwNewThreshold - LddHwCounterValue must be >= 2 */
        if ((LddHwCounterValue - LddHwNewThreshold) >= (uint32)OCU_TWO)                                                 /* PRQA S 3383 # JV-01 */
        {
          /* Let the timer slave count the remaining time to next compare match event */
          LpTAUDChannelSlaveRegs->usTAUDnCDRm = (uint16)(LddHwCounterValue - LddHwNewThreshold - (uint32)OCU_TWO);      /* PRQA S 3383, 3384 # JV-01, JV-01 */
        }
        /* If the new threshold minus the current is equal to 1 the first compare match event after setting the new
        threshold will be caused by one tick of delay */
        else
        {
          /* In this case the tolerant will be plus one hardware tick */
          LpTAUDChannelSlaveRegs->usTAUDnCDRm = (uint16)OCU_ZERO;
        }
      }
      else /* Interrupt for new threshold will not occur inside this cycle */
      {
        /* Check that the master channel reaches the last tick and the new threshold = max tick */
        if (((uint32)OCU_ZERO == LddHwMasterCNTCounterValue) && (LddHwMasterCDRCounterValue == LddHwNewThreshold))
        {
          /* The slave timer counts down from 0 */
          LpTAUDChannelSlaveRegs->usTAUDnCDRm = (uint16)OCU_ZERO;
        }
        else
        {
          /* Set the count down value = next threshold + current timer counter */
          LpTAUDChannelSlaveRegs->usTAUDnCDRm =
                (uint16)(LddHwMasterCNTCounterValue + LddHwMasterCDRCounterValue - LddHwNewThreshold - (uint32)OCU_ONE);/* PRQA S 3383, 3384 # JV-01, JV-01 */
        } /* End of check corner case */
      } /* End of checking inside/outside current cycle */
    }
    else /* Else the master channel has not been started */
    {
      /* Check if the new threshold is different from the max tick */
      if (LddHwMasterCDRCounterValue != LddHwNewThreshold)
      {
        /* Let the timer slave count from the new threshold */
        LpTAUDChannelSlaveRegs->usTAUDnCDRm = 
                (uint16)(LddHwMasterCDRCounterValue - LddHwNewThreshold - (uint32)OCU_ONE);                             /* PRQA S 3383, 3384 # JV-01, JV-01 */
      }
      else /* In case of new threshold is max tick */
      {
        /* Let the timer slave count from max HW tick */
        LpTAUDChannelSlaveRegs->usTAUDnCDRm = (uint16)LddHwMasterCDRCounterValue;
      }
      /* Start the slave timer counter */
      LpTAUDUnitUserRegs->usTAUDnTS = LpTAUChannelConfigData->usChannelBitValue;
    } /* End of DOWNCOUNTING section */
  } /* OCU_UPCOUNTING == Ocu_GblCountingDirection */
  /* Stop the slave timer counter */
  LpTAUDUnitUserRegs->usTAUDnTT = LpTAUChannelConfigData->usChannelBitValue;
  /* Start the slave timer counter */
  LpTAUDUnitUserRegs->usTAUDnTS = LpTAUChannelConfigData->usChannelBitValue;
  /* Enable rewrite of the slave channel count value at the first interrupt */
  Ocu_GpChannelRamData[LddChannel].blRequireRewriteCountValue = OCU_TRUE;
  /* Enable interrupt in case of blRequireRewriteCountValue == OCU_TRUE */
  Ocu_HW_Taud_EnableInterrupt(LddChannel);
} /* End of API Ocu_HW_Taud_StartRestartChannel */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Ocu_HW_Taud_StopChannel
**
** Service ID            : NA
**
** Description           : This is OCU Low Layer Driver component support API Ocu_StopChannel.
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
** Pre-condition         : Ocu_Init was invoked before
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GpChannelRamData, Ocu_GpTAUUnitConfig
**
** Functions invoked     : OCU_ENTER_CRITICAL_SECTION, OCU_EXIT_CRITICAL_SECTION
**
** Registers used        : TAUDnTT
**
** Reference ID          : OCU_DUD_ACT_023, OCU_DUD_ACT_023_GBL001, OCU_DUD_ACT_023_GBL002
** Reference ID          : OCU_DUD_ACT_023_GBL003, OCU_DUD_ACT_023_CRT001, OCU_DUD_ACT_023_CRT002
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Taud_StopChannel(Ocu_ChannelType LddChannel)
{
  /* Pointer to the channel configuration */
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpChannel;
  /* Pointer to the unit configuration */
  P2CONST(Ocu_TAUChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpTAUChannelConfigData;
  /* Pointer pointing to the TAUD Unit control registers */
  P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserRegs;                                                  /* PRQA S 3432 # JV-01 */
  /* Defining a pointer to point to the Channel Ram Data */
  P2VAR(Ocu_ChannelRamDataType, AUTOMATIC, OCU_CONFIG_DATA) LpRamData;                                                  /* PRQA S 3432 # JV-01 */
  /* Updating the channel config parameter to the current channel */
  LpChannel = &Ocu_GpChannelConfig[LddChannel];
  /* load the channel RAM data to the local */
  LpRamData = &Ocu_GpChannelRamData[LddChannel];
  /* Set TAU channel config data pointer */
  LpTAUChannelConfigData = LpChannel->pHWIPChannelConfig;                                                               /* PRQA S 0317 # JV-01 */
  /* Initialize pointer to the base address of the current timer user control registers */
  LpTAUDUnitUserRegs = (P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE))                                               /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                                 Ocu_GpTAUUnitConfig[LpChannel->ucTimerUnitIndex].pTAUUnitUserCntlRegs;
  /* Enter local critical section */
  OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION);
  /* Stop the Slave channel */
  LpTAUDUnitUserRegs->usTAUDnTT = LpTAUChannelConfigData->usChannelBitValue;
  /* Assign the timer status to the Channel */
  LpRamData->blChannelStatus = OCU_CH_STOPPED;
  /* Disable rewrite of the slave channel data register at the next cycle */
  LpRamData->blRequireRewriteCountValue = OCU_FALSE;
  /* Exit local critical section */
  OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION);
} /* End of API Ocu_HW_Taud_StopChannel */
#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Ocu_HW_Taud_SetThreshold
**
** Service ID            : NA
**
** Description           : This is OCU Low Layer Driver component support API Ocu_SetAbsoluteThreshold
**                         Ocu_SetRelativeThreshold
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
** Pre-condition         : Ocu_Init was invoked before and
**                       : OCU_SET_ABSOLUTE_THRESHOLD_API or OCU_SET_RELATIVE_THRESHOLD_API must be STD_ON
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GpChannelRamData, Ocu_GblCountingDirection
**
** Functions invoked     : Ocu_HW_Taud_StartRestartChannel
**
** Registers used        : None
**
** Reference ID          : OCU_DUD_ACT_024, OCU_DUD_ACT_024_GBL001
***********************************************************************************************************************/
#if ((OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON))
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Taud_SetThreshold(Ocu_ChannelType LddChannel, Ocu_ValueType LddSwThresholdValue)
{
  /* Defining a pointer to point to the Channel Ram Data */
  P2VAR(Ocu_ChannelRamDataType, AUTOMATIC, OCU_CONFIG_DATA) LpRamData;                                                  /* PRQA S 3432 # JV-01 */
  /* Pointer to the channel configuration */
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpChannelConfig;
  /* Load the channel RAM data to the local */
  LpRamData = &Ocu_GpChannelRamData[LddChannel];
  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Ocu_GpChannelConfig[LddChannel];

  /* Check the counting direction */
  if (OCU_UPCOUNTING == Ocu_GblCountingDirection)                                                                       /* PRQA S 3416 # JV-01 */
  {
    /* Load the last threshold data to the local */
    LpRamData->ddHwLastThreshold = LddSwThresholdValue * (uint32)(LpChannelConfig->usChannelTickDuration);              /* PRQA S 3384 # JV-01 */
  }
  else /* Else OCU_DOWNCOUNTING */
  {
    LpRamData->ddHwLastThreshold = (((LddSwThresholdValue + (uint32)OCU_ONE) *                                          /* PRQA S 3383, 3384 # JV-01, JV-01 */
                                                  (uint32)(LpChannelConfig->usChannelTickDuration)) - (uint32)OCU_ONE); /* PRQA S 3384 # JV-01 */
  } /* OCU_UPCOUNTING == Ocu_GblCountingDirection */
  /* Let the slave timer counter run with the new threshold if the channel is in running status */
  if (OCU_CH_RUNNING == LpRamData->blChannelStatus)
  {
    /* Restart the slave timer with the new threshold */
    Ocu_HW_Taud_StartRestartChannel(LddChannel, LpRamData->ddHwLastThreshold);
  } /* else No action required */
} /* End of API Ocu_HW_Taud_SetThreshold */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* ((OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)) */
/***********************************************************************************************************************
** Function Name         : Ocu_HW_Taud_EnableInterrupt
**
** Service ID            : NA
**
** Description           : This is OCU Driver component support function. This function Enables Interrupt.
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
** Global Variables used : Ocu_GpChannelConfig
**
** Functions invoked     : RH850_SV_CLEAR_ICR_SYNCP
**
** Registers used        : EICn
**
** Reference ID          : OCU_DUD_ACT_026, OCU_DUD_ACT_026_GBL001, OCU_DUD_ACT_026_GBL002
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Taud_EnableInterrupt(Ocu_ChannelType LddChannel)                                    /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpChannel;

  /* Updating the channel config parameter to the current channel */
  LpChannel = &Ocu_GpChannelConfig[LddChannel];
  #if (OCU_CLEAR_PENDING_INTERRUPT == STD_ON)
  /* Check that the target register address is not null */
  if (NULL_PTR != LpChannel->pEICReg)
  {
    /* Clear the Interrupt flag of the Interrupt control register */
    RH850_SV_CLEAR_ICR_SYNCP(16, (LpChannel->pEICReg), OCU_CLEAR_PENDING_INTR_MASK);                                    /* PRQA S 1006 # JV-01 */
  } /* else No action required */
  #endif /* End of (OCU_CLEAR_PENDING_INTERRUPT == STD_ON) */

  /* Check that the target register address is not null */
  if (NULL_PTR != LpChannel->pEICReg)
  {
    /* Enable Interrupt */
    RH850_SV_CLEAR_ICR_SYNCP(8, (LpChannel->pEICReg), OCU_EIMK_ENABLE_MASK);                                            /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */
} /* End of API Ocu_HW_Taud_EnableInterrupt */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Ocu_HW_Taud_DisableInterrupt
**
** Service ID            : NA
**
** Description           : This is OCU Driver component support function. This function Disable Interrupt.
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
** Functions invoked     : RH850_SV_SET_ICR_SYNCP, RH850_SV_CLEAR_ICR_SYNCP
**
** Registers used        : EICn
**
** Reference ID          : OCU_DUD_ACT_027, OCU_DUD_ACT_027_GBL001, OCU_DUD_ACT_027_GBL002
***********************************************************************************************************************/
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Taud_DisableInterrupt(Ocu_ChannelType LddChannel)                                   /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpChannel;
  /* Updating the channel config parameter to the current channel */
  LpChannel = &Ocu_GpChannelConfig[LddChannel];
  /* Check that the target register address is not null */
  if (NULL_PTR != LpChannel->pEICReg)
  {
    /* Disable Interrupt */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannel->pEICReg), OCU_EIMK_DISABLE_MASK);                                             /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */

  #if (OCU_CLEAR_PENDING_INTERRUPT == STD_ON)
  /* Check that the target register address is not null */
  if (NULL_PTR != LpChannel->pEICReg)
  {
    /* Clear the Interrupt flag of the Slave Interrupt control register */
    RH850_SV_CLEAR_ICR_SYNCP(16, (LpChannel->pEICReg), OCU_CLEAR_PENDING_INTR_MASK);                                    /* PRQA S 1006 # JV-01 */
  } /* else No action required */
  #endif
} /* End of API Ocu_HW_Taud_DisableInterrupt */

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Ocu_HW_Taud_CbkNotification
**
** Service ID            : NA
**
** Description           : This routine is used to invoke the callback notification notification
**                         and switch the pin level.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LucChannelIdx
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variable(s)    : Ocu_GpChannelConfig, Ocu_GpChannelRamData, Ocu_GpTAUUnitConfig
**
** Function(s) invoked   : Dem_SetEventStatus, Ocu_HW_Tauj_DisableInterrupt, OCU_ENTER_CRITICAL_SECTION,
**                         OCU_EXIT_CRITICAL_SECTION, Ocu_Notification_<Channel>
**
** Registers Used        : EICn, TAUDnTO, ulTAUDnCDRm, TAUDnTS
**
** Reference ID          : OCU_DUD_ACT_028, OCU_DUD_ACT_028_ERR001
** Reference ID          : OCU_DUD_ACT_028_GBL003, OCU_DUD_ACT_028_CRT001, OCU_DUD_ACT_028_CRT002
** Reference ID          : OCU_DUD_ACT_028_CRT003, OCU_DUD_ACT_028_CRT004, OCU_DUD_ACT_028_CRT005
** Reference ID          : OCU_DUD_ACT_028_CRT006, OCU_DUD_ACT_028_GBL001, OCU_DUD_ACT_028_GBL002
** Reference ID          : OCU_DUD_ACT_028_GBL004
***********************************************************************************************************************/
#define OCU_START_SEC_CODE_FAST
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, OCU_CODE_FAST) Ocu_HW_Taud_CbkNotification(uint8 LucChannelIdx)
{
  /* Pointer to the channel configuration */
  P2CONST(Ocu_ChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpChannel;
  /* Defining a pointer to point to the Channel Ram Data */
  P2VAR(Ocu_ChannelRamDataType, AUTOMATIC, OCU_CONFIG_DATA) LpRamData;                                                  /* PRQA S 3432 # JV-01 */
  /* Pointer to the unit configuration */
  P2CONST(Ocu_TAUChannelConfigType, AUTOMATIC, OCU_CONFIG_DATA) LpTAUChannelConfigData;
  /* Pointer used for master TAUD channel control registers */
  P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelMasterRegs;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Pointer used for slave TAUD channel control registers */
  P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelSlaveRegs;                                           /* PRQA S 3432 # JV-01 */
  /* Pointer pointing to the TAUD Unit user control registers */
  P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserRegs;                                                  /* PRQA S 3432 # JV-01 */
  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  /* Variable to hold the notification status on the current channel */
  VAR(boolean, AUTOMATIC) LblNotifyStatus;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &Ocu_GpChannelConfig[LucChannelIdx];
  /* Updating the channel ram data to the current channel */
  LpRamData = &Ocu_GpChannelRamData[LucChannelIdx];

  #if (OCU_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Implement Interrupt consistency check */
  if ((uint8)OCU_ZERO != (uint8)(*LpChannel->pEICReg & OCU_EIC_EIMK_MASK))
  {
    (void)Dem_SetEventStatus(OCU_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* End of OCU_INTERRUPT_CONSISTENCY_CHECK == STD_ON */
  {
    #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
    /* Read the notification status */
    LblNotifyStatus = LpRamData->blNotifyStatus;
    #endif /* End of OCU_NOTIFICATION_SUPPORTED == STD_ON */
    /* Set TAU unit config data pointer */
    LpTAUDUnitUserRegs =
        (P2VAR(Ocu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE))Ocu_GpTAUUnitConfig[LpChannel->ucTimerUnitIndex]              /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                                                                              .pTAUUnitUserCntlRegs;
    /* Set TAU channel config data pointer */
    LpTAUChannelConfigData = LpChannel->pHWIPChannelConfig;                                                             /* PRQA S 0317 # JV-01 */
    /* Check the need of rewriting the new slave channel data register at the next cycle */
    if (OCU_TRUE == LpRamData->blRequireRewriteCountValue)
    {
      /* Set the pointer to TAU register base address of Slave Channel */
      LpTAUDChannelSlaveRegs = (P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE))LpTAUChannelConfigData->pCDRReg;    /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Set the pointer to TAU register base address of Master Channel */
      LpTAUDChannelMasterRegs = (P2VAR(Ocu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE))                                   /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                                                                 LpTAUChannelConfigData->pMasterCDRReg; 
      /* The slave channel will count down from the max tick */
      LpTAUDChannelSlaveRegs->usTAUDnCDRm = LpTAUDChannelMasterRegs->usTAUDnCDRm;
      /* Restart the slave timer counter */
      LpTAUDUnitUserRegs->usTAUDnTS = LpTAUChannelConfigData->usChannelBitValue;
      /* Disable rewrite slave channel data register at the next cycle */
      LpRamData->blRequireRewriteCountValue = OCU_FALSE;
      /* Disable the interrupt if it isn't used for notification */
      #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
      if (OCU_FALSE == LblNotifyStatus)
      #endif
      {
        /* Enter global critical section */
        OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
        /* Disable the interrupt */
        Ocu_HW_Taud_DisableInterrupt(LucChannelIdx);
        /* Exit global critical section */
        OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
      } /* else No action required */
    }

    #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
    /* Invoke callback notification if notification is enabled */
    if (OCU_TRUE == LblNotifyStatus)
    {
      if (NULL_PTR != LpChannel->pOcuNotificationPointer)
      {
        /* Invoke the callback function */
        LpChannel->pOcuNotificationPointer();
      } /* else No action required */
    } /* else No action required */
    #endif

    #if (OCU_SET_PIN_ACTION_API == STD_ON)
    /* Set the default pin level if enabled parameter OcuOutputPinUsed and pin action was activated */
    if (OCU_TRUE == LpChannel->blOutputPinUsed)
    {
      /* If OCU_SET_HIGH was set by Ocu_SetPinAction before */
      if (OCU_SET_HIGH == LpRamData->ddPinActionState)
      {
        /* Set the corresponding bit of TAUDnTO register */
        LpTAUDUnitUserRegs->usTAUDnTO |= LpTAUChannelConfigData->usChannelBitValue;
        /* Disable the interrupt if it isn't used for notification */
        #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
        if (OCU_FALSE == LblNotifyStatus)
        #endif
        {
          /* Enter global critical section */
          OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
          /* Disable the interrupt */
          Ocu_HW_Taud_DisableInterrupt(LucChannelIdx);
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
        } /* else No action required */
      } /* else No action required */
      /* If OCU_SET_LOW was set by Ocu_SetPinAction before */
      else if (OCU_SET_LOW == LpRamData->ddPinActionState)                                                              /* PRQA S 2004 # JV-01 */
      {
        /* Reset the corresponding bit of TAUDnTO register */
        LpTAUDUnitUserRegs->usTAUDnTO &= ~(LpTAUChannelConfigData->usChannelBitValue);
        /* Disable the interrupt if it isn't used for notification */
        #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
        if (OCU_FALSE == LblNotifyStatus)
        #endif
        {
          /* Enter global critical section */
          OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
          /* Disable the interrupt */
          Ocu_HW_Taud_DisableInterrupt(LucChannelIdx);
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
        } /* else No action required */
      } /* else No action required */
    } /* else No action required */
    #endif /* OCU_SET_PIN_ACTION_API == STD_ON */
  } /* else No action required */
} /* End of API Ocu_HW_Taud_CbkNotification */

#define OCU_STOP_SEC_CODE_FAST
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* OCU_TIMER_IP_TAUD == STD_ON */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
