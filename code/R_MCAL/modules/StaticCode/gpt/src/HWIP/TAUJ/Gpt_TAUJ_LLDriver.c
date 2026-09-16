/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_TAUJ_LLDriver.c                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Low level Driver code of the GPT Driver Component                                                                  */
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
 *  2.4.0  30/06/2025  : As part of QAC 11.6.0 support, following changes are made:
 *                       + Remove redundant message header
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *                       Remove QAC messages 3383 from Gpt_HW_Tauj_GetTimeRemaining function
 *  2.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : Update SW-VERSION for U2Bx Beta2 release
 *  2.1.1  30/08/2024  : As part of ARDAACJ-565, following changes are made
 *                       1.In Gpt_HW_Tauj_GetTimeElapsed, Gpt_HW_Tauj_GetTimeRemaining: add a condition to check
 *                       register TAUJnCNTm before getting the return value.
 *                     : As part of Post Build multiple varriant support, following changes are made
 *                       1.Change using from marco GPT_KERNEL_CORE_ID to global variable Gpt_GucKernelCoreId
 *  2.0.1  17/10/2023  : Add QAC messages 3006, remove QAC messages 2814, 2824, 2844, 1532, 0317
 *                       Update comment in all APIs
 *         21/09/2023  : Update QAC message comment, remove 0857 QAC message header
 *  2.0.0  24/08/2023  : Update QAC message
 *         26/07/2023  : Change access approach to multi-core and single-core: Access Gpt_GpChannelConfig,
 *                       Gpt_GblDriverStatus via Gpt_GaaGlobalAccPoint for each core; Gpt_GpChannelRamData access
 *                       to channels data via Gpt_GaaChannelRamData, Add CWE QAC header
 *                       add Os.h in case multi-core, add qac messages, Change Gpt_Mapping.h to Gpt_MemMap.h
 *         12/05/2023  : Update SW version 2.0.0
 *                       Update description for all APIs
 *  1.4.4  13/07/2022  : Remove QAC message 1006
 *         21/06/2022  : Add QAC message 9.5.0
 *         08/06/2022  : Remove redundant dummy read and execute syncp statement in Gpt_HW_Tauj_DisableWakeup.
 *  1.4.3  09/05/2022  : Remove "else" statement when no action required; Logic in if-else statement is reversed
 *                       in the way that GPT_DEM_NOT_ERROR condition is checked prior to GPT_DEM_ERROR condition.
 *         08/05/2022  : Remove condition check NULL pointer for LpChannel->pEICReg in callback function
 *                       Gpt_HW_Tauj_CbkNotification().
 *         17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 *  1.4.2  22/02/2022  : Added disable interrupt in case of one-shot and expired channel for function call back
 *                       Gpt_HW_Tauj_CbkNotification()and added Reference ID GPT_DUD_ACT_060_REG001
 *  1.3.2  22/08/2021  : Following Changes were made:
 *                       1. Changed Gpt_MemMap.h to Gpt_Mapping.h.
 *                       2. Removed #if defined(GPT_E_INT_INCONSISTENT) in Gpt_HW_Tauj_CbkNotification.
 *  1.3.1  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 *         24/05/2021  : Removed QAC Msg 1006.
 *         15/05/2021  : Fixed Coding Rule and tailor space.
 *  1.2.0  17/07/2020  : Release
 *  1.1.0  19/06/2020  : Release
 *         04/06/2020  : Add condition to check continuous mode in
 *                       Gpt_HW_Tauj_GetTimeElapsed() to implement SWS_Gpt_00361
 *         25/05/2020  : Remove Redundant Critical Section in Gpt_HW_Tauj_CbkNotification() in #270097
 *         16/03/2020  : 1.Change return when LddPredefTimer = GPT_PREDEF_TIMER_100US_32BIT
 *                       2.Implement "GPT_INTERRUPT_CONSISTENCY_CHECK" for interrupt TAUJxCHmn_ISR
 *         12/03/2020  : 1.As per Redmine #259437, update in Gpt_HW_Tauj_GetPredefTimerValue handle and return
 *                         when LddPredefTimer = GPT_PREDEF_TIMER_100US_32BIT
 *  1.0.0  01/01/2020  : Initial Version
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
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : MISRA C:2012 Dir-4.1, CERTCCM MSC07, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
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
/* Included for Gpt.h inclusion and macro definitions */
#include "Gpt.h"
/* Included for declaration of the Callback functions Configuration */
#include "Gpt_TAUJ_LLDriver.h"
/* Included for RAM variable declarations */
#include "Gpt_Ram.h"
#include "Gpt_TAU_Ram.h"
#include "Gpt_TAUJ_Ram.h"
/* Included for macro definitions */
#include "Gpt_TAUJ_PBTypes.h"
/* For include SV_MODE Macro */
#include "rh850_Types.h"
#if (GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
#include "Dem.h"
#endif
#if (GPT_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define GPT_TAUJ_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_TAUJ_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_TAUJ_LLDRIVER_C_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define GPT_TAUJ_LLDRIVER_C_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION_VALUE
#define GPT_TAUJ_LLDRIVER_C_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (GPT_TAUJ_LLDRIVER_AR_RELEASE_MAJOR_VERSION != GPT_TAUJ_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Gpt_TAUJ_LLDriver.c : Mismatch in Release Major Version"
#endif
#if (GPT_TAUJ_LLDRIVER_AR_RELEASE_MINOR_VERSION != GPT_TAUJ_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Gpt_TAUJ_LLDriver.c : Mismatch in Release Minor Version"
#endif
#if (GPT_TAUJ_LLDRIVER_AR_RELEASE_REVISION_VERSION != GPT_TAUJ_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Gpt_TAUJ_LLDriver.c : Mismatch in Release Revision Version"
#endif
#if (GPT_TAUJ_LLDRIVER_SW_MAJOR_VERSION != GPT_TAUJ_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Gpt_TAUJ_LLDriver.c : Mismatch in Software Major Version"
#endif
#if (GPT_TAUJ_LLDRIVER_SW_MINOR_VERSION != GPT_TAUJ_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Gpt_TAUJ_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (GPT_TIMER_IP_TAUJ == STD_ON)
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_UnitInit
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function initialize Units
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : Gpt_ConfigType* LpConfigPtr
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Pre-condition         : None
**
** Global Variables used : Gpt_GpTAUUnitConfig, Gpt_GaaHWIP
**
** Functions invoked     : None
**
** Registers Used        : TAUJnTPS, TAUJnBRS, TAUJnTT
**
** Reference ID          : GPT_DUD_ACT_050, GPT_DUD_ACT_050_GBL001
** Reference ID          : GPT_DUD_ACT_050_GBL002, GPT_DUD_ACT_050_GBL003, GPT_DUD_ACT_050_GBL004
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Tauj_UnitInit(P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_APPL_CONST) LpConfigPtr)
{
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Gpt_TAUUnitConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpTAUUnitConfig;
  /* Pointer pointing to the TAUJ Unit os control registers */
  P2VAR(Gpt_TAUJUnitOsRegs, AUTOMATIC, REGSPACE) LpTAUJUnitOsReg;                                                       /* PRQA S 3432 # JV-01 */
  /* Pointer pointing to the TAUJ Unit control registers */
  P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUJUnitUserReg;                                                   /* PRQA S 3432 # JV-01 */
  /* Declare a Local variable to Timer Type */
  VAR(uint8, AUTOMATIC) LucTimerType;
  /* Declare a Local variable to counting loop */
  VAR(uint8, AUTOMATIC) LucCount;
  /* Index of HWIP */
  VAR(uint8, AUTOMATIC) LucHWIPCount;

  for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_HW_IP_CONFIG; LucCount++)
  {
    LucHWIPCount = Gpt_GaaHWIP[LucCount].ucIndex;
    if (GPT_HWIP_TAUJ == LucHWIPCount)
    {
      /* Store the global pointer to first Unit Configuration */
      Gpt_GpTAUUnitConfig =
               (P2CONST(Gpt_TAUUnitConfigType, GPT_VAR_INIT, GPT_CONFIG_DATA))LpConfigPtr->aaTimerUnitConfig[LucCount]; /* PRQA S 0316 # JV-01 */
    } /* else No action required */
  }


  for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_TAU_UNITS_CONFIGURED; LucCount++)                        /* PRQA S 2877 # JV-01 */
  {
    /* Update the TAU configuration pointer to point to the current TAU */
    LpTAUUnitConfig = &Gpt_GpTAUUnitConfig[LucCount];
    /* Read the Timer Type for given channel */
    LucTimerType = LpTAUUnitConfig->ucTimerType;
    if (GPT_HW_TAUJ == LucTimerType)
    {
      /* Set the configured channel bits to disable the count operation */
      LpTAUJUnitUserReg =
                    (P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE))(LpTAUUnitConfig->pTAUUnitUserCntlRegs);          /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Initialize the pointer to OS register base address */
      LpTAUJUnitOsReg = (P2VAR(Gpt_TAUJUnitOsRegs, AUTOMATIC, REGSPACE))(LpTAUUnitConfig->pTAUUnitOsCntlRegs);          /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Stop all channels of repective TAU unit */
      LpTAUJUnitUserReg->ucTAUJnTT = GPT_STOP_TAUJ_ALL_CH;
      /* Load the configured pre-scaler value */
      LpTAUJUnitOsReg->usTAUJnTPS = LpTAUUnitConfig->usPrescaler;
      /* Load the configured baud rate value */
      LpTAUJUnitOsReg->ucTAUJnBRS = LpTAUUnitConfig->ucBaudRate;
    } /* else No action required */
  }
} /* End of API Gpt_HW_Tauj_UnitInit */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_ChannelInit
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function sets the clock prescaler,
**                         timer mode. This function also disables the interrupts and resets the interrupt request
**                         pending flags.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Pre-condition         : None
**
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GaaCoreId2Index, Gpt_GucKernelCoreId
**
** Functions invoked     : Gpt_HW_Tauj_DisableInterrupt
**
** Registers Used        : TAUJnCDRm, TAUJnCMORm
**
** Reference ID          : GPT_DUD_ACT_051, GPT_DUD_ACT_051_GBL001
** Reference ID          : GPT_DUD_ACT_051_GBL002, GPT_DUD_ACT_051_GBL003
** Reference ID          : GPT_DUD_ACT_051_GBL004, GPT_DUD_ACT_051_GBL005
** Reference ID          : GPT_DUD_ACT_051_MUI001, GPT_DUD_ACT_051_MUI003, GPT_DUD_ACT_051_REG001
** Reference ID          : GPT_DUD_ACT_051_MUI004, GPT_DUD_ACT_051_GLB030
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Tauj_ChannelInit(Gpt_ChannelType LddChannel)
{
  /* TAU unit config data */
  P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpTAUChannelConfigData;
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Pointer used for TAUJ channel control registers */
  P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUJChannelReg;                                                 /* PRQA S 3432 # JV-01 */
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Set TAU channel config data pointer */
  LpTAUChannelConfigData =
    (P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA))LpChannel->pHWIPChannelConfig;                       /* PRQA S 0316 # JV-01 */

  /* Initialize Timer Channels */
  /* Set the mode of TAUJ timer by writing to CMOR register */
  *((volatile uint16 *)(LpTAUChannelConfigData->pCMORReg)) = LpTAUChannelConfigData->usModeSettingValue;                /* PRQA S 0316 # JV-01 */

  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* Set the Notification status as GPT_FALSE */
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blNotifyStatus = GPT_FALSE;
  #endif

  /* Disable the Interrupt processing of the current channel */
  Gpt_HW_Tauj_DisableInterrupt(LddChannel);
  #if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  /* Assign the Wakeup status to the Channel */
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blWakeupStatus = GPT_FALSE;
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blWakeupOccurrence = GPT_FALSE;
  #endif
  /* Assign the timer status to the Channel */
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus = GPT_CH_NOTSTARTED;
  /* Set the pointer to TAU register base address */
  LpTAUJChannelReg = (P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE))LpTAUChannelConfigData->pCDRReg;              /* PRQA S 0316, 3432 # JV-01, JV-01 */
  /* Reset the CDRm register of the configured channel */
  LpTAUJChannelReg->ulTAUJnCDRm = GPT_RESET_TAUJ_DATA_REG;
} /* End of API Gpt_HW_Tauj_ChannelInit */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_UnitDeInit
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function resets all the HW Registers.
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
** Global Variables      : Gpt_GpTAUUnitConfig
**
** Functions invoked     : None
**
** Registers used        : TAUJnTT
**
** Reference ID          : GPT_DUD_ACT_052, GPT_DUD_ACT_052_GBL001
***********************************************************************************************************************/
#if (GPT_DE_INIT_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Tauj_UnitDeInit(void)
{
  /* Pointer pointing to the TAUD/TAUJ Unit configuration */
  P2CONST(Gpt_TAUUnitConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpTAUUnitConfig;
  /* Pointer pointing to the TAUJ Unit control registers */
  P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUJUnitUserReg;                                                   /* PRQA S 3432 # JV-01 */
  /* Declare a Local variable to Timer Type */
  VAR(uint8, AUTOMATIC) LucTimerType;
  /* Declare a Local variable to counting loop */
  VAR(uint8, AUTOMATIC) LucCount;


  for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_TAU_UNITS_CONFIGURED; LucCount++)                        /* PRQA S 2877 # JV-01 */
  {
    /* Update the TAU configuration pointer to point to the current TAU */
    LpTAUUnitConfig = &Gpt_GpTAUUnitConfig[LucCount];
    /* Read the Timer Type for given channel */
    LucTimerType = LpTAUUnitConfig->ucTimerType;
    if (GPT_HW_TAUJ == LucTimerType)
    {
      /* Update pointer for user base address of the TAUJ unit registers */
      LpTAUJUnitUserReg =
                    (P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE))(LpTAUUnitConfig->pTAUUnitUserCntlRegs);          /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Set the all configured channel bits to disable the count operation */
      LpTAUJUnitUserReg->ucTAUJnTT = (uint8)(LpTAUUnitConfig->usTAUConfiguredChannelsValue);
    } /* else No action required */
  }
} /* End of API Gpt_HW_Tauj_UnitDeInit */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_DE_INIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_ChannelDeInit
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function resets all the HW Registers.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
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
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GaaCoreId2Index, Gpt_GucKernelCoreId
**
** Functions invoked     : Gpt_HW_Tauj_DisableInterrupt
**
** Registers used        : TAUJnCDRm, TAUJnCMORm
**
** Reference ID          : GPT_DUD_ACT_053, GPT_DUD_ACT_053_GBL002
** Reference ID          : GPT_DUD_ACT_053_GBL003, GPT_DUD_ACT_053_GBL004
** Reference ID          : GPT_DUD_ACT_053_GBL005, GPT_DUD_ACT_053_REG001, GPT_DUD_ACT_053_REG002
** Reference ID          : GPT_DUD_ACT_053_MUI001, GPT_DUD_ACT_053_MUI003
** Reference ID          : GPT_DUD_ACT_053_MUI004, GPT_DUD_ACT_053_GLB030
***********************************************************************************************************************/
#if (GPT_DE_INIT_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Tauj_ChannelDeInit(Gpt_ChannelType LddChannel)
{
  /* TAU unit config data */
  P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpTAUChannelConfigData;
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Pointer used for TAUJ channel control registers */
  P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUJChannelReg;                                                 /* PRQA S 3432 # JV-01 */
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Set TAU channel config data pointer */
  LpTAUChannelConfigData =
    (P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA))LpChannel->pHWIPChannelConfig;                       /* PRQA S 0316 # JV-01 */

  /* De-initialize Timer Channels */
  /* Set the pointer to TAU register base address */
  LpTAUJChannelReg = (P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE))LpTAUChannelConfigData->pCDRReg;              /* PRQA S 0316, 3432 # JV-01, JV-01 */
  /* Reset the CMORm register of the configured channel */
  *((volatile uint16 *)(LpTAUChannelConfigData->pCMORReg)) = GPT_RESET_TAUJ_CONTROL_MODE_REG;                           /* PRQA S 0316 # JV-01 */
  /* Reset the CDRm register of the configured channel */
  LpTAUJChannelReg->ulTAUJnCDRm = GPT_RESET_TAUJ_DATA_REG;

  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* Set the Notification status as GPT_FALSE */
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blNotifyStatus = GPT_FALSE;
  #endif

  /* Disable the Interrupt processing of the current channel */
  Gpt_HW_Tauj_DisableInterrupt(LddChannel);
  #if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  /* Assign the Wakeup status to the Channel */
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blWakeupStatus = GPT_FALSE;
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blWakeupOccurrence = GPT_FALSE;
  #endif
  /* Assign the timer status to the Channel */
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus = GPT_CH_NOTSTARTED;

} /* End of API Gpt_HW_Tauj_ChannelDeInit */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_DE_INIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_GetTimeElapsed
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function returns the time elapsed
**                         for a channel by accessing the respective timer registers.
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
** Return Parameter      : Gpt_ValueType
**
** Pre-condition         : None
**
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GaaCoreId2Index, Gpt_GucKernelCoreId
**
** Functions invoked     : SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**
** Registers used        : TAUJnCDRm, TAUJnCNTm
**
** Reference ID          : GPT_DUD_ACT_054, GPT_DUD_ACT_054_CRT001, GPT_DUD_ACT_054_CRT002
** Reference ID          : GPT_DUD_ACT_054_MUI001, GPT_DUD_ACT_054_MUI003
** Reference ID          : GPT_DUD_ACT_054_MUI004, GPT_DUD_ACT_054_GLB030
***********************************************************************************************************************/
#if (GPT_TIME_ELAPSED_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Gpt_ValueType, GPT_PRIVATE_CODE) Gpt_HW_Tauj_GetTimeElapsed(Gpt_ChannelType LddChannel)
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Variable to hold timer Elapsed time */
  VAR(Gpt_ValueType, AUTOMATIC) LddTimeElapsed;
  /* TAU unit config data */
  P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpTAUChannelConfigData;
  /* Defining a pointer to point to the TAUJ registers */
  P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUJChannelRegs;                                                /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  /* Variable to hold the max tick from free-running counter */
  VAR(Gpt_ValueType, AUTOMATIC) LddCDRCounterValue;
  /* Variable to hold the current counter value of master free-running counter */
  VAR(Gpt_ValueType, AUTOMATIC) LddCNTCounterValue;

  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Initialize Return Value to zero */
  LddTimeElapsed = (uint32)GPT_ZERO;
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Set TAU channel config data pointer */
  LpTAUChannelConfigData =
    (P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA))LpChannel->pHWIPChannelConfig;                       /* PRQA S 0316 # JV-01 */

  if (GPT_CH_NOTSTARTED != Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus)
  {
    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter Protected area  */
    GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
    /* Set the pointer to TAU register base address */
    LpTAUJChannelRegs = (P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE))LpTAUChannelConfigData->pCDRReg;           /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Read the current value from the Channel Data register */
    LddCDRCounterValue = (uint32)LpTAUJChannelRegs->ulTAUJnCDRm;
    /* Read the current value from the Channel Counter register */
    LddCNTCounterValue = (uint32)LpTAUJChannelRegs->ulTAUJnCNTm;

    /* Check if the value from TAUJnCDRm register is already loaded into TAUJnCNTm register */
    if (LddCDRCounterValue >= LddCNTCounterValue)
    {
      /* Assign the final return value and it is incremented by one to compensate the decrement done in start timer 
      function. */
      LddTimeElapsed = (LddCDRCounterValue - LddCNTCounterValue);
    }
    else
    {
      /* The Channel Counter register is not started yet, return ZERO */
      LddTimeElapsed = (uint32)GPT_ZERO;
    }

    /* Channel is configured in one-shot mode in state expired function
       shall return target time */
    if (NULL_PTR != LpChannel->pEICReg)
    {
      /* Expired Check of current channel */
      if ((GPT_CH_EXPIRED == Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus) ||
                        (GPT_CHECK_INTR_REQUEST_MASK == (uint16)(*(LpChannel->pEICReg) & GPT_CHECK_INTR_REQUEST_MASK)))
      {
        if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
        {
          /* Returns target time value when channel is expired in one-shot mode and it is incremented by one to
             compensate the decrement done in start timer function. */
          LddTimeElapsed = LddCDRCounterValue + (uint32)GPT_ONE;                                                        /* PRQA S 3383 # JV-01 */
        } /* else No action required */
      } /* else No action required */
    } /* else No action required */

    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit Protected area */
    GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
  } /* else No action required */
  /* End of (GPT_CH_NOTSTARTED != Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus) */

  return (LddTimeElapsed);
} /* End of API Gpt_HW_Tauj_GetTimeElapsed */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of GPT_TIME_ELAPSED_API == STD_ON */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_GetTimeRemaining
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function returns the time remaining
**                         for the channel's next timeout by accessing the respective timer registers.
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
** Return parameter      : Gpt_ValueType
**
** Pre-condition         : None
**
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GpTAUUnitConfig, Gpt_GaaCoreId2Index
**                         Gpt_GucKernelCoreId
**
** Functions invoked     : SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**
** Registers used        : TAUJnCNTm, TAUJnTT, TAUJnCDRm
**
** Reference ID          : GPT_DUD_ACT_055, GPT_DUD_ACT_055_CRT001, GPT_DUD_ACT_055_CRT002,
** Reference ID          : GPT_DUD_ACT_055_GBL001
** Reference ID          : GPT_DUD_ACT_055_MUI001, GPT_DUD_ACT_055_MUI003
** Reference ID          : GPT_DUD_ACT_055_MUI004, GPT_DUD_ACT_055_GLB030
***********************************************************************************************************************/
#if (GPT_TIME_REMAINING_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Gpt_ValueType, GPT_PRIVATE_CODE) Gpt_HW_Tauj_GetTimeRemaining(Gpt_ChannelType LddChannel)
{
  /* Pointer to the Unit configuration */
  P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpTAUChannelConfigData;
  /* Defining a pointer to point to the TAUJ registers */
  P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUJChannelRegs;                                                /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Defining a pointer to point to the TAUJ registers */
  P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUJUnitUserRegs;                                                  /* PRQA S 3432 # JV-01 */
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Variable to hold timer remaining time */
  VAR(Gpt_ValueType, AUTOMATIC) LddTimeRemaining;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  /* Variable to hold the max tick from free-running counter */
  VAR(Gpt_ValueType, AUTOMATIC) LddCDRCounterValue;
  /* Variable to hold the current counter value of master free-running counter */
  VAR(Gpt_ValueType, AUTOMATIC) LddCNTCounterValue;

  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Initialize Return Value to zero */
  LddTimeRemaining = (uint32)GPT_ZERO;
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Updating the unit configuration parameter to the current unit */
  LpTAUChannelConfigData =
    (P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA))LpChannel->pHWIPChannelConfig;                       /* PRQA S 0316 # JV-01 */

  if (GPT_CH_NOTSTARTED != Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus)
  {
    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter Protected area */
    GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif

    /* Set the pointer to TAU register base address */
    LpTAUJChannelRegs = (P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE))LpTAUChannelConfigData->pCDRReg;           /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Read the current value from the Channel Data register */
    LddCDRCounterValue = (uint32)LpTAUJChannelRegs->ulTAUJnCDRm;
    /* Read the current value from the Channel Counter register */
    LddCNTCounterValue = (uint32)LpTAUJChannelRegs->ulTAUJnCNTm;

    /* Check if the value from TAUJnCDRm register is already loaded into TAUJnCNTm register */
    if (LddCDRCounterValue >= LddCNTCounterValue)
    {
      /* Assign the final return value and it is incremented by one to compensate the decrement done in start timer 
      function. */
      LddTimeRemaining = LddCNTCounterValue + (uint32)GPT_ONE;                                                          /* PRQA S 3383 # JV-01 */
    }
    else
    {
      /* The Channel Counter register is not started yet, return the max counter value */
      LddTimeRemaining = LddCDRCounterValue + (uint32)GPT_ONE;
    }

    /* Channel is expired and is configured for one-shot mode will return zero value */
    if (GPT_CH_EXPIRED == Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus)
    {
      /* Return ZERO */
      LddTimeRemaining = (uint32)GPT_ZERO;
    } /* else No action required */

    /* GPT channel in one-shot mode shall return a value of 0 if timer expires */
    if (NULL_PTR != LpChannel->pEICReg)
    {
      /* Increment the pointer to next byte address of Interrupt control register */
      if ((GPT_CHECK_INTR_REQUEST_MASK == (uint16)(*(LpChannel->pEICReg) & GPT_CHECK_INTR_REQUEST_MASK)) &&
                                                                   (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode))
      {
        /* Return ZERO */
        LddTimeRemaining = (uint32)GPT_ZERO;

        /* Initialize pointer to the base address of the current timer user control registers */
        LpTAUJUnitUserRegs =
            (P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE))Gpt_GpTAUUnitConfig[LpChannel->ucTimerUnitIndex]          /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                                                                                  .pTAUUnitUserCntlRegs;

        /* Stop the timer TAUJ */
        LpTAUJUnitUserRegs->ucTAUJnTT = (uint8)LpTAUChannelConfigData->usChannelBitValue;
      } /* else No action required */
    } /* else No action required */

    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit Protected area */
    GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
  } /* else No action required */
  /* End of (GPT_CH_NOTSTARTED != Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus) */

  return (LddTimeRemaining);
} /* End of API Gpt_HW_Tauj_GetTimeRemaining */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_TIME_REMAINING_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_StartTimer
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function starts the timer channel
**                         by loading the compare registers and enabling the clock.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant (but not for the same timer channel)
**
** Input Parameters      : LddChannel, LddValue
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return Value          : None
**
** Pre-condition         : None
**
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GpTAUUnitConfig, Gpt_GucDriverMode,
**                         Gpt_GaaCoreId2Index, Gpt_GucKernelCoreId
**
** Functions invoked     : Gpt_HW_Tauj_EnableInterrupt, SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**
**Registers used         : TAUJnCDRm, TAUJnTS, TAUJnTT
**
** Reference ID          : GPT_DUD_ACT_056, GPT_DUD_ACT_056_CRT001
** Reference ID          : GPT_DUD_ACT_056_CRT002, GPT_DUD_ACT_056_GBL001, GPT_DUD_ACT_056_GBL002
** Reference ID          : GPT_DUD_ACT_056_GBL003, GPT_DUD_ACT_056_GBL004
** Reference ID          : GPT_DUD_ACT_056_MUI001, GPT_DUD_ACT_056_MUI003, GPT_DUD_ACT_056_REG001
** Reference ID          : GPT_DUD_ACT_056_MUI004, GPT_DUD_ACT_056_GLB030
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Tauj_StartTimer(Gpt_ChannelType LddChannel, Gpt_ValueType LddValue)                 /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Pointer to the unit configuration */
  P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpTAUChannelConfigData;
  /* Defining a pointer to point to the TAUJ registers */
  P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUJUnitUserRegs;                                                  /* PRQA S 3432 # JV-01 */
  /* Defining a pointer to point to the channel control registers of TAUJ */
  P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUJChannelRegs;                                                /* PRQA S 3432 # JV-01 */
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];

  #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enter Protected area  */
  GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  #endif
  if (GPT_MODE_NORMAL == Gpt_GucDriverMode)                                                                             /* PRQA S 3416 # JV-01 */
  {
    /* Set base address for unit registers */
    LpTAUJUnitUserRegs =
        (P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE))Gpt_GpTAUUnitConfig[LpChannel->ucTimerUnitIndex]              /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                                                                                  .pTAUUnitUserCntlRegs;
    /* Set TAU channel config data pointer */
    LpTAUChannelConfigData =
      (P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA))LpChannel->pHWIPChannelConfig;                     /* PRQA S 0316 # JV-01 */
    /* Stopping tiner counter */
    LpTAUJUnitUserRegs->ucTAUJnTT = (uint8)LpTAUChannelConfigData->usChannelBitValue;

    if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
    {
      /* Enable Interrupt */
      Gpt_HW_Tauj_EnableInterrupt(LddChannel);
    }
    else
    {
      #if (GPT_CLEAR_PENDING_INTERRUPT == STD_ON)
      if (NULL_PTR != LpChannel->pEICReg)
      {
        /* Clear the Interrupt flag of Interrupt control register */
        RH850_SV_MODE_ICR_AND(16, (LpChannel->pEICReg), GPT_CLEAR_PENDING_INTR_MASK);
        /* Dummy read */
        RH850_SV_MODE_REG_READ_ONLY(16, (LpChannel->pEICReg));
        /* Execute syncp */
        EXECUTE_SYNCP();                                                                                                /* PRQA S 1006 # JV-01 */
      } /* else No action required */
      #endif
    }
    /* End of LpChannel->ucGptChannelMode == GPT_CH_MODE_ONESHOT */

    /* Set base address for channel register */
    LpTAUJChannelRegs = (P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE))LpTAUChannelConfigData->pCDRReg;           /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Load the value into the Data register */
    LpTAUJChannelRegs->ulTAUJnCDRm = LddValue - (uint32)GPT_ONE;                                                        /* PRQA S 3383 # JV-01 */
    /* Start the timer counter */
    LpTAUJUnitUserRegs->ucTAUJnTS = (uint8)LpTAUChannelConfigData->usChannelBitValue;
    /* Assign the timer status to the Channel */
    Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus = GPT_CH_RUNNING;
  } /* else No action required */

  #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Exit Protected area */
  GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  #endif

} /* End of API Gpt_HW_Tauj_StartTimer */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_StopTimer
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function stops the channel
**                         by disabling the interrupt and/or the clock.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant (but not for the same timer channel)
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
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GpTAUUnitConfig, Gpt_GucKernelCoreId
**                         Gpt_GaaCoreId2Index
**
** Functions invoked     : Gpt_HW_Tauj_DisableInterrupt
**
** Registers used        : TAUJnTT
**
** Reference ID          : GPT_DUD_ACT_057, GPT_DUD_ACT_057_GBL001, GPT_DUD_ACT_057_GBL002
** Reference ID          : GPT_DUD_ACT_057_MUI001, GPT_DUD_ACT_057_MUI003
** Reference ID          : GPT_DUD_ACT_057_MUI004, GPT_DUD_ACT_057_GLB030
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Tauj_StopTimer(Gpt_ChannelType LddChannel)
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Pointer to the unit configuration */
  P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpTAUChannelConfigData;
  /* Defining a pointer to point to the TAUJ registers */
  P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUJUnitUserRegs;                                                  /* PRQA S 3432 # JV-01 */
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Set TAU channel config data pointer */
  LpTAUChannelConfigData =
    (P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA))LpChannel->pHWIPChannelConfig;                       /* PRQA S 0316 # JV-01 */
  /* Set TAU unit config data pointer */
  LpTAUJUnitUserRegs =
      (P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE))Gpt_GpTAUUnitConfig[LpChannel->ucTimerUnitIndex]                /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                                                                                  .pTAUUnitUserCntlRegs;
  /* Stop the timer counter */
  LpTAUJUnitUserRegs->ucTAUJnTT = (uint8)LpTAUChannelConfigData->usChannelBitValue;
  /* Disable Interrupt */
  Gpt_HW_Tauj_DisableInterrupt(LddChannel);
  /* Assign the timer status to the Channel */
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus = GPT_CH_STOPPED;
} /* End of API Gpt_HW_Tauj_StopTimer */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_EnableInterrupt
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function Enable Interrupt.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant (but not for the same timer channel)
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaCoreId2Index, Gpt_GucKernelCoreId
**
** Functions invoked     : None
**
** Registers used        : EICn
**
** Reference ID          : GPT_DUD_ACT_058, GPT_DUD_ACT_058_REG001, GPT_DUD_ACT_058_REG002
** Reference ID          : GPT_DUD_ACT_058_MUI001, GPT_DUD_ACT_058_MUI003
** Reference ID          : GPT_DUD_ACT_058_MUI004, GPT_DUD_ACT_058_GLB030
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Tauj_EnableInterrupt(Gpt_ChannelType LddChannel)                                    /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  #if (GPT_CLEAR_PENDING_INTERRUPT == STD_ON)
  if (NULL_PTR != LpChannel->pEICReg)
  {
    /* Clear the Interrupt flag of Interrupt control register */
    RH850_SV_MODE_ICR_AND(16, (LpChannel->pEICReg), GPT_CLEAR_PENDING_INTR_MASK);
    /* Dummy read */
    RH850_SV_MODE_REG_READ_ONLY(16, (LpChannel->pEICReg));
    /* Execute syncp */
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  } /* else No action required */
  #endif

  if (NULL_PTR != LpChannel->pEICReg)
  {
    /* Enable Interrupt */
    RH850_SV_MODE_ICR_AND(8, (LpChannel->pEICReg), GPT_EIMK_ENABLE_MASK);                                               /* PRQA S 0751 # JV-01 */
    /* Dummy read */
    RH850_SV_MODE_REG_READ_ONLY(8, (LpChannel->pEICReg));                                                               /* PRQA S 0751 # JV-01 */
    /* Execute syncp */
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  } /* else No action required */

} /* End of API Gpt_HW_Tauj_EnableInterrupt */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_DisableInterrupt
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function Disable Interrupt.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant (but not for the same timer channel)
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
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GaaCoreId2Index, Gpt_GucKernelCoreId
**
** Functions invoked     : None
**
** Registers used        : EICn
**
** Reference ID          : GPT_DUD_ACT_059, GPT_DUD_ACT_059_REG001, GPT_DUD_ACT_059_REG002
** Reference ID          : GPT_DUD_ACT_059_MUI001, GPT_DUD_ACT_059_MUI003
** Reference ID          : GPT_DUD_ACT_059_MUI004, GPT_DUD_ACT_059_GLB030
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Tauj_DisableInterrupt(Gpt_ChannelType LddChannel)                                   /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  if (NULL_PTR != LpChannel->pEICReg)
  {
    /* Disable Interrupt */
    RH850_SV_MODE_ICR_OR(8, (LpChannel->pEICReg), GPT_EIMK_DISABLE_MASK);                                               /* PRQA S 0751 # JV-01 */
    /* Dummy read */
    RH850_SV_MODE_REG_READ_ONLY(8, (LpChannel->pEICReg));                                                               /* PRQA S 0751 # JV-01 */
    /* Execute syncp */
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  } /* else No action required */

  #if (GPT_CLEAR_PENDING_INTERRUPT == STD_ON)
  if (NULL_PTR != LpChannel->pEICReg)
  {
    /* Increment the pointer to next byte address of
     * Interrupt control register */
    RH850_SV_MODE_ICR_AND(16, (LpChannel->pEICReg), GPT_CLEAR_PENDING_INTR_MASK);
    /* Dummy read */
    RH850_SV_MODE_REG_READ_ONLY(16, (LpChannel->pEICReg));
    /* Execute syncp */
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  } /* else No action required */
  #endif /* End of (GPT_CLEAR_PENDING_INTERRUPT == STD_ON) */

} /* End of API Gpt_HW_Tauj_DisableInterrupt */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_CbkNotification
**
** Service ID            : NA
**
** Description           : This routine is used to invoke the callback notification or wakeup notification based
**                         on timer mode.
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
** Global Variable(s)    : Gpt_GaaGlobalAccPoints, Gpt_GaaChannelRamData, Gpt_GucDriverMode, Gpt_GpTAUUnitConfig,
**                         Gpt_GaaCoreId2Index, Gpt_GucKernelCoreId
**
** Function(s) invoked   : EcuM_CheckWakeup, GPT_DEM_REPORT_ERROR
**
** Registers Used        : TAUJnTT, EICn
**
** Reference ID          : GPT_DUD_ACT_060, GPT_DUD_ACT_060_ERR001, GPT_DUD_ACT_060_REG001
** Reference ID          : GPT_DUD_ACT_060_GBL001, GPT_DUD_ACT_060_GBL002, GPT_DUD_ACT_060_GBL003
** Reference ID          : GPT_DUD_ACT_060_MUI001, GPT_DUD_ACT_060_MUI003
** Reference ID          : GPT_DUD_ACT_060_MUI004, GPT_DUD_ACT_060_GLB030
***********************************************************************************************************************/
#define GPT_START_SEC_CODE_FAST
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_CODE_FAST) Gpt_HW_Tauj_CbkNotification(uint8 LucChannelIdx)                                              /* PRQA S 1503, 3006 # JV-01, JV-01 */
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Pointer to the unit configuration */
  P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpTAUChannelConfigData;
  /* Pointer pointing to the TAUJ Unit user control registers */
  P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUJUnitUserRegs;                                                  /* PRQA S 3432 # JV-01 */
  #if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  VAR(EcuM_WakeupSourceType, AUTOMATIC) LulWakeupSource;
  #endif
  #if (GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* DEM Error Status */
  VAR(uint8, AUTOMATIC) LucDemErrorStatus;
  #endif /* End of GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON */
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LucChannelIdx];
  /* Set TAU channel config data pointer */
  LpTAUChannelConfigData =
    (P2CONST(Gpt_TAUChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA))LpChannel->pHWIPChannelConfig;                       /* PRQA S 0316 # JV-01 */
  #if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  LulWakeupSource = (EcuM_WakeupSourceType)(GPT_ONE) << (LpChannel->ucWakeupSourceId);
  #endif
  #if (GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  LucDemErrorStatus = GPT_DEM_NOT_ERROR;

  /* Implement Interrupt consistency check */
  if ((uint8)GPT_ZERO != (uint8)(*LpChannel->pEICReg & GPT_EIC_EIMK_MASK))
  {
    GPT_DEM_REPORT_ERROR(GPT_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
    LucDemErrorStatus = GPT_DEM_ERROR;
  } /* else No action required */

  if (GPT_DEM_NOT_ERROR == LucDemErrorStatus)
  {
    #endif /* End of GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON */
    if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
    {
      /* Disable Interrupt */
      RH850_SV_MODE_ICR_OR(8, (LpChannel->pEICReg), GPT_EIMK_DISABLE_MASK);                                             /* PRQA S 0751 # JV-01 */
      /* Dummy read */
      RH850_SV_MODE_REG_READ_ONLY(8, (LpChannel->pEICReg));                                                             /* PRQA S 0751 # JV-01 */
      /* Execute syncp */
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */
      /* Initialize pointer to the base address of the current timer unit */
      LpTAUJUnitUserRegs =
          (P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE))Gpt_GpTAUUnitConfig[LpChannel->ucTimerUnitIndex]            /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                                                                                  .pTAUUnitUserCntlRegs;
      /* Stop the timer TAUJ */
      LpTAUJUnitUserRegs->ucTAUJnTT = (uint8)LpTAUChannelConfigData->usChannelBitValue;
      /* Assign the timer status to the One-shot Channel */
      Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus = GPT_CH_EXPIRED;
    } /* else No action required */
    /* End of LpChannel->ucGptChannelMode == GPT_CH_MODE_ONESHOT */

    if (GPT_MODE_NORMAL == Gpt_GucDriverMode)                                                                           /* PRQA S 3416 # JV-01 */
    {
      #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
      /* Invoke callback notification if notification is enabled */
      if (GPT_TRUE == Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blNotifyStatus)
      {
        if (NULL_PTR != LpChannel->pGptNotificationPointer)
        {
          /* Invoke the callback function */
          LpChannel->pGptNotificationPointer();
        } /* else No action required */
      } /* else No action required */
      #endif
    }  /* End of Gpt_GucDriverMode == GPT_MODE_NORMAL */
    else
    {
      #if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
      if ((GPT_TRUE == LpChannel->blGptWakeupSupport) &&
                                        (GPT_TRUE == Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blWakeupStatus))
      {
        /* Set the wakeup status to true */
        Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blWakeupOccurrence = GPT_TRUE;

        /* If the driver is in Sleep mode and wakeup notification is enabled, invoke ECU Wakeup function */
        EcuM_CheckWakeup(LulWakeupSource);
      } /* else No action required */
      #endif
    }
  #if (GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  }
  #endif /* End of GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON */
} /* End of API Gpt_HW_Tauj_CbkNotification */

#define GPT_STOP_SEC_CODE_FAST
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_StartPredefTimer
**
** Service ID            : NA
**
** Description           : This API is used to get the Gpt PredefTimer value for start Gpt PredefTimer.
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
** Global Variable(s)    : Gpt_GpPredefTimerConfig
**
** Functions invoked     : None
**
** Registers Used        : TAUJnCNTm, TAUJnCDRm, TAUJnTS, TAUJnCMORm
**
** Reference ID          : GPT_DUD_ACT_061, GPT_DUD_ACT_061_GBL001
** Reference ID          : GPT_DUD_ACT_061_GBL002, GPT_DUD_ACT_061_GBL003, GPT_DUD_ACT_061_REG001
***********************************************************************************************************************/
#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Tauj_StartPredefTimer(void)
{
  /* Pointer to Predef Timer channel config */
  P2CONST(Gpt_PredefTimerTAUJChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpPT_ChConfig;
  /* Pointer to Predef Timer unit config */
  P2CONST(Gpt_PredefTimerTAUJUnitConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpPT_UnitConfig;
  /* Defining a pointer to point to the TAUJ registers */
  P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE) LpPT_TAUJUnitUserRegs;                                               /* PRQA S 3432 # JV-01 */
  /* Defining a pointer to point to the channel control registers of TAUJ */
  P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpPT_TAUJChannelRegs;                                             /* PRQA S 3432 # JV-01 */

  /* Initialize the PredefTimer */
  LpPT_UnitConfig =
    (P2CONST(Gpt_PredefTimerTAUJUnitConfigType, AUTOMATIC, GPT_CONFIG_DATA))Gpt_GpPredefTimerConfig->pPT_UnitConfig;    /* PRQA S 0316 # JV-01 */
  LpPT_ChConfig = (P2CONST(Gpt_PredefTimerTAUJChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA))                           /* PRQA S 0316 # JV-01 */
                      Gpt_GpPredefTimerConfig->pPT_ChannelConfig;
  LpPT_TAUJUnitUserRegs = (P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE))LpPT_UnitConfig->pPT_TAUJUnitUserCntlRegs;  /* PRQA S 0316, 3432 # JV-01, JV-01 */
  LpPT_TAUJChannelRegs = (P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE))LpPT_ChConfig->pPT_CDRReg;                /* PRQA S 0316, 3432 # JV-01, JV-01 */

  /* Set the mode of TAUJ timer by writing to CMOR register */
  /* Set TAUJnCKS to CK3 and TAUJnMD to Interval timer mode and INTTAUJnIm is not generated */
  *((volatile uint16 *)(LpPT_ChConfig->pPT_CMORReg)) = LpPT_ChConfig->usPT_ModeSettingValue;                            /* PRQA S 0316 # JV-01 */
  /* Initialize counter register */
  LpPT_TAUJChannelRegs->ulTAUJnCNTm = GPT_32BIT_MASK_VALUE;
  /* Load the value into the Data register */
  LpPT_TAUJChannelRegs->ulTAUJnCDRm = GPT_32BIT_MASK_VALUE;
  /* Start Predef Timer */
  LpPT_TAUJUnitUserRegs->ucTAUJnTS = LpPT_ChConfig->ucPT_ChannelBitValue;
}
#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_StopPredefTimer
**
** Service ID            : NA
**
** Description           : This API is used to get the Gpt PredefTimer value, for stop Gpt PredefTimer.
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
** Global Variable(s)    : Gpt_GpPredefTimerConfig
**
** Functions invoked     : None
**
** Registers Used        : TAUJnTT
**
** Reference ID          : GPT_DUD_ACT_062, GPT_DUD_ACT_062_GBL001
***********************************************************************************************************************/
#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Tauj_StopPredefTimer(void)
{
  /* Pointer to Predef Timer channel config */
  P2CONST(Gpt_PredefTimerTAUJChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpPT_ChConfig;
  /* Pointer to Predef Timer unit config */
  P2CONST(Gpt_PredefTimerTAUJUnitConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpPT_UnitConfig;

  /* Defining a pointer to point to the TAUJ registers */
  P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE) LpPT_TAUJUnitUserRegs;                                               /* PRQA S 3432 # JV-01 */

  /* Initialize the PredefTimer */
  LpPT_ChConfig = (P2CONST(Gpt_PredefTimerTAUJChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA))                           /* PRQA S 0316 # JV-01 */
                    Gpt_GpPredefTimerConfig->pPT_ChannelConfig;
  LpPT_UnitConfig = (P2CONST(Gpt_PredefTimerTAUJUnitConfigType, AUTOMATIC, GPT_CONFIG_DATA))                            /* PRQA S 0316 # JV-01 */
                      Gpt_GpPredefTimerConfig->pPT_UnitConfig;
  LpPT_TAUJUnitUserRegs = (P2VAR(Gpt_TAUJUnitUserRegs, AUTOMATIC, REGSPACE))LpPT_UnitConfig->pPT_TAUJUnitUserCntlRegs;  /* PRQA S 0316, 3432 # JV-01, JV-01 */

  /* Stop Predef Timer */
  LpPT_TAUJUnitUserRegs->ucTAUJnTT = LpPT_ChConfig->ucPT_ChannelBitValue;
}
#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_GetPredefTimerValue
**
** Service ID            : NA
**
** Description           : This API is used to get the Gpt PredefTimer value for the current value of the
**                         desired Gpt PredefTimer.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddPredefTimer, LpTimerValuePtr.
**
** InOut Parameter       : None
**
** Output Parameters     : None
**
** Return parameter     : Std_ReturnType
**
** Pre-condition         : None
**
** Global Variable(s)    : Gpt_GpPredefTimerConfig
**
** Functions invoked     : SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**
** Registers Used        : TAUJnCNTm, TAUJnCDRm
**
** Reference ID          : GPT_DUD_ACT_063, GPT_DUD_ACT_063_CRT001
** Reference ID          : GPT_DUD_ACT_063_CRT002, GPT_DUD_ACT_063_REG001, GPT_DUD_ACT_063_REG002
***********************************************************************************************************************/
#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Std_ReturnType, GPT_PRIVATE_CODE)
Gpt_HW_Tauj_GetPredefTimerValue(Gpt_PredefTimerType LddPredefTimer, uint32 *LpTimerValuePtr)
{
  /* Pointer to Predef Timer channel config */
  P2CONST(Gpt_PredefTimerTAUJChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpPT_ChConfig;
  /* Variable to hold return value */
  VAR(Std_ReturnType, AUTOMATIC) LucReturnValue;
  /* Defining a pointer to point to the channel control registers of TAUJ */
  P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpPT_TAUJChannelRegs;                                             /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Variable to hold predef Timer count value */
  VAR(uint32, AUTOMATIC) LulCountValue;

  /* Set to initialize value */
  LucReturnValue = E_OK;
  /* Update the PredefTimer configuration pointer to point to the current Predef Timer */
  LpPT_ChConfig = (P2CONST(Gpt_PredefTimerTAUJChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA))                           /* PRQA S 0316 # JV-01 */
    Gpt_GpPredefTimerConfig->pPT_ChannelConfig;
  LpPT_TAUJChannelRegs = (P2VAR(Gpt_TAUJChannelUserRegs, AUTOMATIC, REGSPACE))LpPT_ChConfig->pPT_CDRReg;                /* PRQA S 0316, 3432 # JV-01, JV-01 */

  #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enter Protected area  */
  GPT_ENTER_CRITICAL_SECTION(GPT_RAM_DATA_PROTECTION_GLOBAL);
  #endif

  LulCountValue = GPT_32BIT_MASK_VALUE - LpPT_TAUJChannelRegs->ulTAUJnCNTm;

  if ((GPT_PREDEF_TIMER_1US_32BIT == LddPredefTimer) || (GPT_PREDEF_TIMER_100US_32BIT == LddPredefTimer))
  {
    /* Get PredefTimer Value */
    *LpTimerValuePtr = LulCountValue;
  }
  else if (GPT_PREDEF_TIMER_1US_24BIT == LddPredefTimer)
  {
    /* Clear the upper 31-25bit and get PredefTimer Value */
    *LpTimerValuePtr = (GPT_UPPER_24BIT_CLEAR_MASK & LulCountValue);
  }
  else if (GPT_PREDEF_TIMER_1US_16BIT == LddPredefTimer)
  {
    /* Clear the upper 31-17bit and get PredefTimer Value */
    *LpTimerValuePtr = (GPT_UPPER_16BIT_CLEAR_MASK & LulCountValue);
  }
  else
  {
    LucReturnValue = E_NOT_OK;
  }

  #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Exit Protected area */
  GPT_EXIT_CRITICAL_SECTION(GPT_RAM_DATA_PROTECTION_GLOBAL);
  #endif

  return (LucReturnValue);

} /* End of API Gpt_HW_Get_Tauj_PredefTimerValue */
#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_DisableWakeup
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function disables the interrupt
**                         for the wakeup channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant (but not for the same timer channel)
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
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GaaCoreId2Index, Gpt_GucKernelCoreId
**
** Functions invoked     : SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**
** Registers used        : EICn
**
** Reference ID          : GPT_DUD_ACT_064, GPT_DUD_ACT_064_CRT001
** Reference ID          : GPT_DUD_ACT_064_CRT002, GPT_DUD_ACT_064_REG001, GPT_DUD_ACT_064_REG002
** Reference ID          : GPT_DUD_ACT_064_MUI001, GPT_DUD_ACT_064_MUI003
** Reference ID          : GPT_DUD_ACT_064_MUI004, GPT_DUD_ACT_064_GLB030
***********************************************************************************************************************/
#if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Tauj_DisableWakeup(Gpt_ChannelType LddChannel)                                      /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];

  #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enter Protected area */
  GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  #endif
  #if (GPT_CLEAR_PENDING_INTERRUPT == STD_ON)
  /* Increment the pointer to next byte address of
     Interrupt control register */
  RH850_SV_CLEAR_ICR_SYNCP(16, LpChannel->pEICReg, GPT_CLEAR_PENDING_INTR_MASK);                                        /* PRQA S 1006 # JV-01 */
  #endif

  /* Disabling the Interrupt processing of the current channel */
  RH850_SV_SET_ICR_SYNCP(8, (LpChannel->pEICReg), GPT_EIMK_DISABLE_MASK);                                               /* PRQA S 0751, 1006 # JV-01, JV-01 */

  #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Exit Protected area */
  GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  #endif

} /* End of API Gpt_HW_Tauj_DisableWakeup */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)  && (GPT_REPORT_WAKEUP_SOURCE == STD_ON)) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Tauj_EnableWakeup
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function enables the interrupt for
**                         the wakeup channel
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant (but not for the same timer channel)
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
** Global Variable(s)    : Gpt_GaaGlobalAccPoint, Gpt_GaaCoreId2Index, Gpt_GucKernelCoreId
**
** Function(s) invoked   : SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**
** Registers Used        : EICn
**
** Reference ID          : GPT_DUD_ACT_065, GPT_DUD_ACT_065_CRT001
** Reference ID          : GPT_DUD_ACT_065_CRT002, GPT_DUD_ACT_065_REG001, GPT_DUD_ACT_065_REG002
** Reference ID          : GPT_DUD_ACT_065_MUI001, GPT_DUD_ACT_065_MUI003
** Reference ID          : GPT_DUD_ACT_065_MUI004, GPT_DUD_ACT_065_GLB030
***********************************************************************************************************************/
#if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Tauj_EnableWakeup(Gpt_ChannelType LddChannel)                                       /* PRQA S 3006 # JV-01 */
{
  /* Updating the channel config parameter to the current channel */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enter Protected area  */
  GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  #endif
  #if (GPT_CLEAR_PENDING_INTERRUPT == STD_ON)
  /* Increment the pointer to next byte address of
     Interrupt control register */
  RH850_SV_CLEAR_ICR_SYNCP(16, LpChannel->pEICReg, GPT_CLEAR_PENDING_INTR_MASK);                                        /* PRQA S 1006 # JV-01 */
  #endif

  /* Enable the Interrupt processing of the current channel */
  RH850_SV_MODE_ICR_AND(8, (LpChannel->pEICReg), GPT_EIMK_ENABLE_MASK);                                                 /* PRQA S 0751 # JV-01 */
  /* Dummy read */
  RH850_SV_MODE_REG_READ_ONLY(8, (LpChannel->pEICReg));                                                                 /* PRQA S 0751 # JV-01 */
  /* Execute syncp */
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Exit Protected area */
  GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  #endif

} /* End of API Gpt_HW_Tauj_EnableWakeup */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && (GPT_REPORT_WAKEUP_SOURCE == STD_ON)) */

#endif /* GPT_TIMER_IP_TAUJ == STD_ON */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
