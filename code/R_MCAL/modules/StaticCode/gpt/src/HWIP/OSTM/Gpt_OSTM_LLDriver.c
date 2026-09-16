/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_OSTM_LLDriver.c                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2024 Renesas Electronics Corporation. All rights reserved.                                                */
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
 *  2.4.0  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) release
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *                       Add QAC messages 3384 in Gpt_HW_Ostm_StartTimer function
 *  2.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : Update SW-VERSION for U2Bx Beta2 release
 *  2.0.1  17/10/2023  : Add QAC messages 3006; Remove QAC message 2814, 2824, 2844, 2934, 1532, 0312
 *                       In all functions, change type of LpRamData from Gpt_ChannelRamDataType
 *                       to volatile Gpt_ChannelRamDataType
 *                       In Gpt_HW_Ostm_StartTimer, change critical section from GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL
 *                       to GPT_INTERRUPT_CONTROL_PROTECTION
 *                       Update comment in all APIs
 *         21/09/2023  : Gpt_HW_Ostm_ChannelInit, Gpt_HW_Ostm_ChannelDeInit, Gpt_HW_Ostm_GetTimeElapsed,
 *                       Gpt_HW_Ostm_GetTimeRemaining, Gpt_HW_Ostm_StartTimer, Gpt_HW_Ostm_StopTimer,
 *                       Gpt_HW_Ostm_EnableInterrupt, Gpt_HW_Ostm_DisableInterrupt, Gpt_HW_Ostm_CbkNotification:
 *                       add preprocessor GPT_TYPE_II_SUPPORT for code block containing assigning pChannelRamData
 *                       to LpRamData; Update QAC message comment, remove 0857 QAC message header
 *  2.0.0  24/08/2023  : Remove cast type in Gpt_HW_Ostm_ChannelInit due to supported in generator output
 *         26/07/2023  : Change access approach to multi-core and single-core: Access Gpt_GpChannelConfig,
 *                       Gpt_GblDriverStatus via Gpt_GaaGlobalAccPoint for each core;
 *                       Gpt_GpChannelRamData access to channels data via Gpt_GaaChannelRamData
 *                       Add Os.h in case multi-core, add qac messages, Change Gpt_Mapping.h to Gpt_MemMap.h
 *                       Remove Gpt_HW_Ostm_UnitInit API because the action in Gpt_HW_Ostm_UnitInit is duplicate with
 *                       action in Gpt_HW_Ostm_ChannelInit, Add CWE QAC header
 *         12/05/2023  : Update SW version 2.0.0
 *                       Update description for all APIs
 *  1.4.4  13/07/2022  : Remove QAC message 1006
 *         21/06/2022  : Add QAC message 9.5.0
 *  1.4.3  09/05/2022  : Remove "else" statement when no action required; Logic in if-else statement is reversed
 *                       in the way that GPT_DEM_NOT_ERROR condition is checked prior to GPT_DEM_ERROR condition.
 *         08/05/2022  : Remove condition check NULL pointer for LpChannel->pEICReg in callback function
 *                       Gpt_HW_Ostm_CbkNotification().
 *         17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 *         12/04/2022  : Corrected error content from "Mismatch in Release Patch Version" to
 *                       "Mismatch in Release Revision Version".
 *  1.4.2  22/02/2022  : Added disable interrupt in case of one-shot and expired channel for function call back
 *                       Gpt_HW_Ostm_CbkNotification()and added Reference ID GPT_DUD_ACT_038_REG001.
 *  1.3.2  22/08/2021  : Following Changes were made:
 *                       1. Changed Gpt_MemMap.h to Gpt_MemMap.h.
 *                       2. Removed #if defined(GPT_E_INT_INCONSISTENT) in Gpt_HW_Ostm_CbkNotification.
 *  1.3.1  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 *         24/05/2021  : Removed QAC Msg 3214, 1006.
 *         15/05/2021  : Fixed Coding Rule and tailor space.
 *         06/05/2021  : Add version check of SW version
 *  1.2.0  17/07/2020  : Release
 *         15/07/2020  : Fixed Gpt_HW_Ostm_ChannelInit() and Gpt_HW_Ostm_ChannelDeInit() should get multiple channel
 *  1.1.0  19/06/2020  : Release
 *         04/06/2020  : Add condition to check continuous mode in
 *                       Gpt_HW_Ostm_GetTimeElapsed() to implement SWS_Gpt_00361
 *         16/03/2020  : Implement "GPT_INTERRUPT_CONSISTENCY_CHECK" for interrupt OSTMmn_CH0_ISR
 *  1.0.0  01/01/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
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
/* Included for declaration of the functions */
#include "Gpt_OSTM_LLDriver.h"
/* Included for RAM variable declarations */
#include "Gpt_Ram.h"
#include "Gpt_OSTM_Ram.h"
#include "Gpt_OSTM_PBTypes.h"
/* For include SV_MODE Macro */
#include "rh850_Types.h"
/* Include for interrupt consistency check */
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
#define GPT_OSTM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_OSTM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_OSTM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define GPT_OSTM_LLDRIVER_C_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION_VALUE
#define GPT_OSTM_LLDRIVER_C_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (GPT_OSTM_LLDRIVER_AR_RELEASE_MAJOR_VERSION != GPT_OSTM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Gpt_OSTM_LLDriver.c : Mismatch in Release Major Version"
#endif
#if (GPT_OSTM_LLDRIVER_AR_RELEASE_MINOR_VERSION != GPT_OSTM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Gpt_OSTM_LLDriver.c : Mismatch in Release Minor Version"
#endif
#if (GPT_OSTM_LLDRIVER_AR_RELEASE_REVISION_VERSION != GPT_OSTM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Gpt_OSTM_LLDriver.c : Mismatch in Release Revision Version"
#endif
#if (GPT_OSTM_LLDRIVER_SW_MAJOR_VERSION != GPT_OSTM_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Gpt_OSTM_LLDriver.c : Mismatch in Software Major Version"
#endif
#if (GPT_OSTM_LLDRIVER_SW_MINOR_VERSION != GPT_OSTM_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Gpt_OSTM_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (GPT_TIMER_IP_OSTM == STD_ON)
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name         : Gpt_HW_Ostm_ChannelInit
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function select the clock source,
**                         timer mode. This function also disables the interrupts and resets
**                         the interrupt request pending flags.
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GaaCoreId2Index
**
** Functions invoked     : Gpt_HW_Ostm_DisableInterrupt
**
** Registers Used        : OSTMnCTL, OSTMnCNT, OSTMnCMP, OSTMnTOE, OSTMnTT
**
** Reference ID          : GPT_DUD_ACT_030, GPT_DUD_ACT_030_GBL001
** Reference ID          : GPT_DUD_ACT_030_GBL002, GPT_DUD_ACT_030_GBL003, GPT_DUD_ACT_030_GBL004
** Reference ID          : GPT_DUD_ACT_030_GBL006, GPT_DUD_ACT_030_GBL007, GPT_DUD_ACT_030_GBL005
** Reference ID          : GPT_DUD_ACT_030_MUI001, GPT_DUD_ACT_030_MUI002
** Reference ID          : GPT_DUD_ACT_030_MUI004, GPT_DUD_ACT_030_GLB030
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Ostm_ChannelInit(Gpt_ChannelType LddChannel)
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Defining a local pointer to point to the Channel Ram Data */
  P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_VAR_NO_INIT) LpRamData;
  /* Pointer to the OSTM Unit registers */
  P2VAR(Gpt_OSTMnUnitRegs, AUTOMATIC, REGSPACE) LpOSTMUnitReg;                                                          /* PRQA S 3432 # JV-01 */
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;

  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if (GPT_TYPE_II_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK);
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_VAR_NO_INIT))
                            &(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelRamData)[(LpChannel->ucRamDataIndex)];
  #endif
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA))
                                     &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
  #endif

  /* Check the Notification is configured for the current channel */
  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  LpRamData->blNotifyStatus = GPT_FALSE;
  #endif
  /* Disable Interrupt */
  Gpt_HW_Ostm_DisableInterrupt(LddChannel);
  /* Assign the timer status to the Channel */
  LpRamData->ucChannelStatus = GPT_CH_NOTSTARTED;
  /* Initialize the pointer to register base address */
  LpOSTMUnitReg = LpChannel->pOSTMUnitRegs;
  /* Stop the timer counter */
  LpOSTMUnitReg->ucOSTMnTT = GPT_OSTM_STOP_MASK;
  /* Initialize the OSTMnCTL register */
  LpOSTMUnitReg->ucOSTMnCTL = GPT_RESET_OSTMCTL;
  /* Initialize the OSTMnCNT register */
  LpOSTMUnitReg->ulOSTMnCNT = GPT_RESET_OSTMCNT;
  /* Initialise the OSTMnCMP register */
  LpOSTMUnitReg->ulOSTMnCMP = GPT_RESET_OSTMCMP;
  /* Initialise the OSTMnTOE register */
  LpOSTMUnitReg->ucOSTMnTOE = GPT_RESET_OSTMTOE;

} /* End of API Gpt_Ostm_HW_Channel Init */
#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Ostm_ChannelDeInit
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GaaCoreId2Index
**
** Functions invoked     : Gpt_HW_Ostm_DisableInterrupt
**
** Registers used        : OSTMnTT, OSTMnCTL, OSTMnCMP, OSTMnCNT, OSTMnTOE
**
** Reference ID          : GPT_DUD_ACT_031, GPT_DUD_ACT_031_GBL001
** Reference ID          : GPT_DUD_ACT_031_GBL002, GPT_DUD_ACT_031_GBL003, GPT_DUD_ACT_031_GBL004
** Reference ID          : GPT_DUD_ACT_031_GBL006, GPT_DUD_ACT_031_GBL007, GPT_DUD_ACT_031_GBL005
** Reference ID          : GPT_DUD_ACT_031_MUI001, GPT_DUD_ACT_031_MUI002
** Reference ID          : GPT_DUD_ACT_031_MUI004, GPT_DUD_ACT_031_GLB030
***********************************************************************************************************************/
#if (GPT_DE_INIT_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Ostm_ChannelDeInit(Gpt_ChannelType LddChannel)
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Defining a local pointer to point to the Channel Ram Data */
  P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_VAR_NO_INIT) LpRamData;
  /* Pointer pointing to the OSTM Unit registers */
  P2VAR(Gpt_OSTMnUnitRegs, AUTOMATIC, REGSPACE) LpOSTMUnitReg;                                                          /* PRQA S 3432 # JV-01 */

  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if (GPT_TYPE_II_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK);
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_VAR_NO_INIT))
                                &(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelRamData)[(LpChannel->ucRamDataIndex)];
  #endif
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA))
                                     &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
  #endif

  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* Set the Notification status as GPT_FALSE */
  LpRamData->blNotifyStatus = GPT_FALSE;
  #endif
  /* Disable Interrupt */
  Gpt_HW_Ostm_DisableInterrupt(LddChannel);
  /* Assign the timer status to the Channel */
  LpRamData->ucChannelStatus = GPT_CH_NOTSTARTED;
  /* load current channel OSTM Register base address to local pointer */
  LpOSTMUnitReg = LpChannel->pOSTMUnitRegs;
  /* Load the reset value of stop register */
  LpOSTMUnitReg->ucOSTMnTT = GPT_OSTM_STOP_MASK;
  /* Reset the mode of OSTM timer by writing to control register */
  LpOSTMUnitReg->ucOSTMnCTL = GPT_RESET_OSTMCTL;
  /* Reset the CMP register of the configured channel */
  LpOSTMUnitReg->ulOSTMnCMP = GPT_RESET_OSTMCMP;
  /* Reset the CNT register of the configured channel */
  LpOSTMUnitReg->ulOSTMnCNT = GPT_RESET_OSTMCNT;
  /* Reset the OSTMnTOE register */
  LpOSTMUnitReg->ucOSTMnTOE = GPT_RESET_OSTMTOE;

} /* End of API Gpt_HW_Ostm_ChannelDeInit */
#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of GPT_DE_INIT_API == STD_ON */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Ostm_GetTimeElapsed
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GaaCoreId2Index
**
** Functions invoked     : SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**
** Registers used        : OSTMnCMP, OSTMnCNT, EICn
**
** Reference ID          : GPT_DUD_ACT_032, GPT_DUD_ACT_032_CRT001, GPT_DUD_ACT_032_CRT002
** Reference ID          : GPT_DUD_ACT_032_MUI001, GPT_DUD_ACT_032_MUI002
** Reference ID          : GPT_DUD_ACT_032_MUI004, GPT_DUD_ACT_032_GLB030
***********************************************************************************************************************/
#if (GPT_TIME_ELAPSED_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Gpt_ValueType, GPT_PRIVATE_CODE) Gpt_HW_Ostm_GetTimeElapsed(Gpt_ChannelType LddChannel)
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Defining a pointer to point to the Channel Ram Data */
  P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA) LpRamData;                                         /* PRQA S 3678 # JV-01 */
  /* Variable to hold timer Elapsed time */
  VAR(Gpt_ValueType, AUTOMATIC) LddTimeElapsed;
  /* Pointer to the OSTM Unit registers */
  P2VAR(Gpt_OSTMnUnitRegs, AUTOMATIC, REGSPACE) LpOSTMUnitReg;                                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;

  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if (GPT_TYPE_II_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK);
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA))
                            &(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelRamData)[(LpChannel->ucRamDataIndex)];
  #endif
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA))
                                     &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
  #endif

  /* Initialize Return Value to zero */
  LddTimeElapsed = (uint32)GPT_ZERO;

  if (GPT_CH_NOTSTARTED != LpRamData->ucChannelStatus)
  {
    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter Protected area  */
    GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
    #endif
    /* load  current channel OSTM Register base address to local pointer */
    LpOSTMUnitReg = LpChannel->pOSTMUnitRegs;
    /* Assign the final return value */
    LddTimeElapsed = (LpOSTMUnitReg->ulOSTMnCMP - LpOSTMUnitReg->ulOSTMnCNT);                                           /* PRQA S 0404, 3384 # JV-01, JV-01 */

    if ((GPT_CH_EXPIRED == LpRamData->ucChannelStatus) ||
        ((uint16)(RH850_SV_MODE_REG_READ_ONLY(16, (LpChannel->pEICReg)) & GPT_CHECK_INTR_REQUEST_MASK) !=
                                                                                                      (uint16)GPT_ZERO))
    {
      /* Expired Check of current channel */
      if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
      {
        /* Assign the final return value */
        /* The target value is decreased 1 in Gpt_HW_Ostm_StartTimer */
        /* Thus Elapsed Timer is increased 1 */
        LddTimeElapsed = (LpOSTMUnitReg->ulOSTMnCMP + (uint32)GPT_ONE);                                                 /* PRQA S 3383 # JV-01 */
      } /* else No action required */
    } /* else No action required */

    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit Protected area */
    GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
    #endif
  } /* else No action required */
  /* End of (GPT_CH_NOTSTARTED != LpRamData->ucChannelStatus) */

  return (LddTimeElapsed);
} /* End of API Gpt_HW_Ostm_GetTimeElapsed */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of GPT_TIME_ELAPSED_API == STD_ON */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Ostm_GetTimeRemaining
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GaaCoreId2Index
**
** Functions invoked     : SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**
** Registers used        : OSTMnCNT, EIC
**
** Reference ID          : GPT_DUD_ACT_033, GPT_DUD_ACT_033_CRT001, GPT_DUD_ACT_033_CRT002
** Reference ID          : GPT_DUD_ACT_033_MUI001, GPT_DUD_ACT_033_MUI002
** Reference ID          : GPT_DUD_ACT_033_MUI004, GPT_DUD_ACT_033_GLB030
***********************************************************************************************************************/
#if (GPT_TIME_REMAINING_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Gpt_ValueType, GPT_PRIVATE_CODE) Gpt_HW_Ostm_GetTimeRemaining(Gpt_ChannelType LddChannel)
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Defining a pointer to point to the Channel Ram Data */
  P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA) LpRamData;                                         /* PRQA S 3678 # JV-01 */
  /* Variable to hold timer remaining time */
  VAR(Gpt_ValueType, AUTOMATIC) LddTimeRemaining;
  /* Pointer pointing to the OSTM Unit registers */
  P2VAR(Gpt_OSTMnUnitRegs, AUTOMATIC, REGSPACE) LpOSTMUnitReg;                                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;

  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if (GPT_TYPE_II_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK);
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA))
                           &(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelRamData)[(LpChannel->ucRamDataIndex)];
  #endif
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA))
                                     &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
  #endif

  /* Initialize Return Value to zero */
  LddTimeRemaining = (uint32)GPT_ZERO;

  if (GPT_CH_NOTSTARTED != LpRamData->ucChannelStatus)
  {
    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter Protected area */
    GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
    #endif
    /* load  current channel OSTM Register base address to local pointer */
    LpOSTMUnitReg = LpChannel->pOSTMUnitRegs;
    /* Assign the final return value */
    /* The target value is decreased 1 in Gpt_HW_Ostm_StartTimer */
    /* Thus Remaining Time is increased 1 */
    LddTimeRemaining = (LpOSTMUnitReg->ulOSTMnCNT + (uint32)GPT_ONE);                                                   /* PRQA S 3383 # JV-01 */

    /* Expired Chack of current channel */
    if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
    {
      if ((GPT_CH_EXPIRED == LpRamData->ucChannelStatus) ||
          ((uint16)(RH850_SV_MODE_REG_READ_ONLY(16, (LpChannel->pEICReg)) & GPT_CHECK_INTR_REQUEST_MASK) !=
                                                                                                      (uint16)GPT_ZERO))
      {
        /* Set the return value to zero */
        LddTimeRemaining = (uint32)GPT_ZERO;
      } /* else No action required */
    } /* else No action required */

    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit Protected area */
    GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
    #endif
  } /* else No action required */
  /* End of (GPT_CH_NOTSTARTED != LpRamData->ucChannelStatus) */

  return (LddTimeRemaining);
} /* End of API Gpt_HW_Ostm_GetTimeRemaining */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_TIME_REMAINING_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Ostm_StartTimer
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GaaCoreId2Index
**
** Functions invoked     : SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**                         Gpt_HW_Ostm_EnableInterrupt
**
** Registers used        : OSTMnTOE, OSTMnTT, OSTMnCMP, OSTMnCNT, OSTMnTS, OSTMnCTL, EICn
**
** Reference ID          : GPT_DUD_ACT_034, GPT_DUD_ACT_034_CRT001,
** Reference ID          : GPT_DUD_ACT_034_CRT002, GPT_DUD_ACT_034_GBL001, GPT_DUD_ACT_034_GBL002
** Reference ID          : GPT_DUD_ACT_034_GBL003, GPT_DUD_ACT_034_GBL004, GPT_DUD_ACT_034_GBL005
** Reference ID          : GPT_DUD_ACT_034_GBL006, GPT_DUD_ACT_034_GBL007, GPT_DUD_ACT_034_REG001
** Reference ID          : GPT_DUD_ACT_034_MUI001, GPT_DUD_ACT_034_MUI002
** Reference ID          : GPT_DUD_ACT_034_MUI004, GPT_DUD_ACT_034_GLB030
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Ostm_StartTimer(Gpt_ChannelType LddChannel, Gpt_ValueType LddValue)                 /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Defining a pointer to point to the Channel Ram Data */
  P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA) LpRamData;
  /* Pointer pointing to the OSTM Unit registers */
  P2VAR(Gpt_OSTMnUnitRegs, AUTOMATIC, REGSPACE) LpOSTMUnitReg;                                                          /* PRQA S 3432 # JV-01 */

  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if (GPT_TYPE_II_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK);
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA))
                            &(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelRamData)[(LpChannel->ucRamDataIndex)];
  #endif
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA))
                                     &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
  #endif

  #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enter Protected area  */
  GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
  #endif
  /* load current channel OSTM Register base address to local pointer */
  LpOSTMUnitReg = LpChannel->pOSTMUnitRegs;
  /* Stopping tiner counter */
  LpOSTMUnitReg->ucOSTMnTT = GPT_OSTM_STOP_MASK;

  if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
  {
    /* Enable Interrupt */
    Gpt_HW_Ostm_EnableInterrupt(LddChannel);
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
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */
    } /* else No action required */
    #endif
  }
  /* End of LpChannel->ucGptChannelMode == GPT_CH_MODE_ONESHOT */

  /* Load the value into the Compare register */
  LpOSTMUnitReg->ulOSTMnCMP = (uint32)LddValue - (uint32)GPT_ONE;                                                       /* PRQA S 3384 # JV-01 */
  /* Set OSTMnTOE register to default value  */
  LpOSTMUnitReg->ucOSTMnTOE = GPT_RESET_OSTMTOE;
  /* Enable interrupt and select interval timer mode */
  LpOSTMUnitReg->ucOSTMnCTL = GPT_OSTMCTL_SETTING_VALUE;
  /* Reset the CNT register of the configured channel */
  LpOSTMUnitReg->ulOSTMnCNT = GPT_RESET_OSTMCNT;
  /* Start the timer counter */
  LpOSTMUnitReg->ucOSTMnTS = GPT_OSTM_START_MASK;
  /* Assign the timer status to the Channel */
  LpRamData->ucChannelStatus = GPT_CH_RUNNING;

  #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Exit Protected area */
  GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
  #endif

} /* End of API Gpt_HW_Ostm_StartTimer */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Ostm_StopTimer
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GaaCoreId2Index
**
** Functions invoked     : Gpt_HW_Ostm_DisableInterrupt
**
** Registers used        : OSTMnTT
**
** Reference ID          : GPT_DUD_ACT_035, GPT_DUD_ACT_035_GBL001, GPT_DUD_ACT_035_GBL002
** Reference ID          : GPT_DUD_ACT_035_MUI001, GPT_DUD_ACT_035_MUI002
** Reference ID          : GPT_DUD_ACT_035_MUI004, GPT_DUD_ACT_035_GLB030
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Ostm_StopTimer(Gpt_ChannelType LddChannel)
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Defining a pointer to point to the Channel Ram Data */
  P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA) LpRamData;
  /* Pointer pointing to the OSTM Unit registers */
  P2VAR(Gpt_OSTMnUnitRegs, AUTOMATIC, REGSPACE) LpOSTMUnitReg;                                                          /* PRQA S 3432 # JV-01 */

  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if (GPT_TYPE_II_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK);
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA))
                              &(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelRamData)[(LpChannel->ucRamDataIndex)];
  #endif
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA))
                                     &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
  #endif

  /* load start register start mask of configured sub block */
  LpOSTMUnitReg = LpChannel->pOSTMUnitRegs;
  /* Stop the timer counter */
  LpOSTMUnitReg->ucOSTMnTT = GPT_OSTM_STOP_MASK;
  /* Disable Interrupt */
  Gpt_HW_Ostm_DisableInterrupt(LddChannel);
  /* Assign the timer status to the Channel */
  LpRamData->ucChannelStatus = GPT_CH_STOPPED;
} /* End of API Gpt_HW_Ostm_StopTimer */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Ostm_EnableInterrupt
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaCoreId2Index
**
** Functions invoked     : None
**
** Registers used        : EICn
**
** Reference ID          : GPT_DUD_ACT_036, GPT_DUD_ACT_036_REG001, GPT_DUD_ACT_036_REG002
** Reference ID          : GPT_DUD_ACT_036_MUI001, GPT_DUD_ACT_036_MUI002
** Reference ID          : GPT_DUD_ACT_036_MUI004, GPT_DUD_ACT_036_GLB030
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Ostm_EnableInterrupt(Gpt_ChannelType LddChannel)                                    /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;

  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if (GPT_TYPE_II_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK);
  #endif
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

} /* End of API Gpt_HW_Ostm_EnableInterrupt */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Ostm_DisableInterrupt
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaCoreId2Index
**
** Functions invoked     : None
**
** Registers used        : EICn
**
** Reference ID          : GPT_DUD_ACT_037, GPT_DUD_ACT_037_REG001, GPT_DUD_ACT_037_REG002
** Reference ID          : GPT_DUD_ACT_037_MUI001, GPT_DUD_ACT_037_MUI002
** Reference ID          : GPT_DUD_ACT_037_MUI004, GPT_DUD_ACT_037_GLB030
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PRIVATE_CODE) Gpt_HW_Ostm_DisableInterrupt(Gpt_ChannelType LddChannel)                                   /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;

  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if (GPT_TYPE_II_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK);
  #endif
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

} /* End of API Gpt_HW_Ostm_DisableInterrupt */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Ostm_CbkNotification
**
** Service ID            : NA
**
** Description           : This routine is used to invoke the callback
**                         notification or wakeup notification based on timer mode.
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GaaCoreId2Index
**
** Functions invoked     : GPT_DEM_REPORT_ERROR, pGptNotificationPointer
**
** Registers used        : OSTMnTT, EICn
**
** Reference ID          : GPT_DUD_ACT_038, GPT_DUD_ACT_038_ERR001, GPT_DUD_ACT_038_GBL001, GPT_DUD_ACT_038_GBL002
** Reference ID          : GPT_DUD_ACT_038_REG001
** Reference ID          : GPT_DUD_ACT_038_MUI001, GPT_DUD_ACT_038_MUI002
** Reference ID          : GPT_DUD_ACT_038_MUI004, GPT_DUD_ACT_038_GLB030
***********************************************************************************************************************/
#define GPT_START_SEC_CODE_FAST
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_CODE_FAST) Gpt_HW_Ostm_CbkNotification(uint8 LucChannelIdx)                                              /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Defining a pointer to point to the Channel Ram Data */
  P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA) LpRamData;
  /* Pointer pointing to the OSTM Unit registers */
  P2VAR(Gpt_OSTMnUnitRegs, AUTOMATIC, REGSPACE) LpOSTMUnitReg;                                                          /* PRQA S 3432 # JV-01 */
  #if (GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* DEM Error Status */
  VAR(uint8, AUTOMATIC) LucDemErrorStatus;
  #endif /* End of GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON */

  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if (GPT_TYPE_II_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK);
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LucChannelIdx];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA))
                                 &(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelRamData)[(LpChannel->ucRamDataIndex)];
  #endif
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LucChannelIdx];
  /* Updating the channel RAM data pointer to the current channel */
  LpRamData = (P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_CONFIG_DATA))
                                     &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
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
      /* load start register start mask of configured unit */
      LpOSTMUnitReg = LpChannel->pOSTMUnitRegs;
      /* Stop the timer OSTM */
      LpOSTMUnitReg->ucOSTMnTT = GPT_OSTM_STOP_MASK;
      /* Assign the timer status to the One-shot Channel */
      LpRamData->ucChannelStatus = GPT_CH_EXPIRED;
    } /* else No action required */
    /* End of LpChannel->ucGptChannelMode == GPT_CH_MODE_ONESHOT */

    #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
    /* Invoke callback notification if notification is enabled */
    if (GPT_TRUE == LpRamData->blNotifyStatus)
    {
      if (NULL_PTR != LpChannel->pGptNotificationPointer)
      {
        /* Invoke the callback function */
        LpChannel->pGptNotificationPointer();
      } /* else No action required */
    } /* else No action required */
    #endif

  #if (GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  } /* else No action required */
  #endif
} /* End of API Gpt_HW_Ostm_CbkNotification */

#define GPT_STOP_SEC_CODE_FAST
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* GPT_TIMER_IP_OSTM == STD_ON */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
