/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_GTM_LLDriver.c                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
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
 *  2.4.1  30/06/2025  : As part of QAC 11.6.0 support, following changes are made:
 *                       Add QAC message 2877 (U2Bx), 2962
 *                       As part of GTM HWIP support for U2Ax, following changes are made:
 *                       In Gpt_HW_Gtm_CbkNotification: Add sequence to stop channel with ONESHOT mode
 *  2.4.0  30/06/2025  : As part of QAC 11.6.0 support, following changes are made:
 *                       + Add message 2880
 *                       + Remove redundant message header
 *  2.3.2  25/04/2025  : As part of GTM HWIP support for U2Ax, following changes are made:
 *                       1. Add condtion to use TOMnCHmCTRLSR and ATOMnCHmCTRLSR registers for GTM U2Ax
 *                       2. Update for new aprroach interrupt:
 *                       Gpt_HW_Gtm_ChannelInit:
 *                       + Remove Gpt_HW_Gtm_DisableInterrupt
 *                       + Add Disable the interrupt processing EIC
 *                       Gpt_HW_Gtm_ChannelDeInit:
 *                       + Remove Gpt_HW_Gtm_DisableInterrupt
 *                       + Add disable the Interrupt processing EIC
 *                       Gpt_HW_Gtm_StartTimer:
 *                       + Remove Clear the Interrupt flag of EIC
 *                       + Add Disable the interrupt processing EIC
 *                       + Add Clear the interrupt flag for channel
 *                       + Remove Enable Interrupt of channel
 *                       Gpt_HW_Gtm_EnableInterrupt:
 *                       + Remove Enable Interrupt EIC
 *                       + Add Enable Interrupt of channel
 *                       Gpt_HW_Gtm_DisableInterrupt:
 *                       + Remove Disable Interrupt EIC
 *                       + Add Disable Interrupt of channel
 *                       Gpt_HW_Gtm_CbkNotification:
 *                       + Remove Disable Interrupt EIC
 *                       + Add Disable Interrupt of channel
 *  2.3.1  31/03/2025  : As part of ticket ARDAACL-54181:
 *                       1. Add setting TOMnCHmCTRLSR register in Gpt_HW_Gtm_ChannelInit and Gpt_HW_Gtm_StartPredefTimer
 *                       function
 *                       As part of QAC 11.6.0 support, following changes are made
 *                       1. Remove QAC message 0604
 *                       2. Add message 3006 and 2812
 *  2.3.0  28/02/2025  : As part of QAC 9.5.0 support, following changes are made
 *                       1.Add message 2991, 2995 to support QAC 9.5.0
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/

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
/* Message (4:0311)    : Dangerous pointer cast results in loss of const qualification.                               */
/* Rule                : MISRA C:2012 Rule-11.8, CERTCCM EXP05                                                        */
/* JV-01 Justification : This is to achieve throughput in the code.                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
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
/* Message (2:1006)    : This in-line assembler construct is a language extension. The code has been ignored.         */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTCCM MSC14                                       */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2962)    : Apparent: Using value of uninitialized automatic object '%s'.                                */
/* Rule                : CERTCCM EXP33, MISRA C:2012 Rule-9.1                                                         */
/* JV-01 Justification : It will be initialized based on scope of 'if' statements  where at least an 'if' statement   */
/*                       will be executed that will initialize the variable.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2812)    : Apparent: Dereference of NULL pointer.                                                       */
/* Rule                : MISRA C:2012 Rule-1.3                                                                        */
/* JV-01 Justification : This Msg is enabled because it is enforced by MISRA-C Mandatory/Required/Advisory Rule(s)    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : MISRA C:2012 Dir-4.1, CERTCCM MSC07, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/* Message (6:2880)    : This code is unreachable.                                                                    */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-670                                       */
/* JV-01 Justification : Part of the code is manually check and confirmed to be executable depending on the           */
/*                       configuration                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563,     */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2991)    : The value of this 'if' controlling expression is always 'true'.                              */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2995)    : The result of this logical operation is always 'true'.                                       */
/* Rule                : MISRA C:2012 Rule-2.2, CWE Rule CWE-561, CWE-633                                             */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3, CWE Rule CWE-398, CWE-569                                              */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
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
#include "Gpt_GTM_LLDriver.h"
/* Included for RAM variable declarations */
#include "Gpt_Ram.h"
#include "Gpt_GTM_Ram.h"
#include "Gpt_GTM_PBTypes.h"
/* For include SV_MODE Macro */
#include "rh850_Types.h"
/* Include for interrupt consistency check */
#if (GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
#include "Dem.h"
#endif
#if (GPT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define GPT_GTM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_GTM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_GTM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define GPT_GTM_LLDRIVER_C_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION_VALUE
#define GPT_GTM_LLDRIVER_C_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (GPT_GTM_LLDRIVER_AR_RELEASE_MAJOR_VERSION != GPT_GTM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Gpt_GTM_LLDriver.c : Mismatch in Release Major Version"
#endif
#if (GPT_GTM_LLDRIVER_AR_RELEASE_MINOR_VERSION != GPT_GTM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Gpt_GTM_LLDriver.c : Mismatch in Release Minor Version"
#endif
#if (GPT_GTM_LLDRIVER_AR_RELEASE_REVISION_VERSION != GPT_GTM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Gpt_GTM_LLDriver.c : Mismatch in Release Revision Version"
#endif
#if (GPT_GTM_LLDRIVER_SW_MAJOR_VERSION != GPT_GTM_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Gpt_GTM_LLDriver.c : Mismatch in Software Major Version"
#endif
#if (GPT_GTM_LLDRIVER_SW_MINOR_VERSION != GPT_GTM_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Gpt_GTM_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (GPT_TIMER_IP_GTM == STD_ON)
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#if ((GPT_TOM_UNIT_USED == STD_ON) || (GPT_ATOM_UNIT_USED == STD_ON))
/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_UnitInit
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function initialize ATOMUnit and
**                         TOMUnit
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
** Global Variables used : Gpt_GpGTMUnitConfig, Gpt_GaaHWIP
**
** Functions invoked     : None
**
** Registers Used        : TOM[i]_TGC[g]_GLB_CTRL, TOM[i]_TGC[g]_ENDIS_CTRL, TOM[i]_TGC[g]_ENDIS_STAT
**                         ATOM[i]_AGC_GLB_CTRL, ATOM[i]_AGC_ENDIS_CTRL, ATOM[i]_AGC_ENDIS_STAT
**
** Reference ID          : GPT_DUD_ACT_073
** Reference ID          : GPT_DUD_ACT_073_GLB001
** Reference ID          : GPT_DUD_ACT_073_REG001, GPT_DUD_ACT_073_REG002, GPT_DUD_ACT_073_REG003
** Reference ID          : GPT_DUD_ACT_073_REG004, GPT_DUD_ACT_073_REG005, GPT_DUD_ACT_073_REG006
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"

void Gpt_HW_Gtm_UnitInit(const Gpt_ConfigType* LpConfigPtr)
{
  /* Declare a Local variable to count loop */
  uint8 LucCount;
  /* Index of HWIP */
  uint8 LucHWIPCount;
  /* Pointer to Cluster configuration */
  const Gpt_GTMUnitConfigType* LpClusterConfig;
  #if (GPT_TOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the TGC Unit registers */
  Gpt_TOMnTGCmUnitRegs* LpTOMnTGCmUnitRegs;
  #endif
  #if (GPT_ATOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the AGC Unit registers */
  Gpt_ATOMnAGCUnitRegs* LpATOMnAGCUnitRegs;
  #endif

  for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_HW_IP_CONFIG; LucCount++)                                /* PRQA S 2877 # JV-01 */
  {
    LucHWIPCount = Gpt_GaaHWIP[LucCount].ucIndex;
    if (GPT_HWIP_GTM == LucHWIPCount)
    {
      Gpt_GpGTMUnitConfig = LpConfigPtr->aaTimerUnitConfig[LucCount];                                                   /* PRQA S 0317 # JV-01 */
    } /* else No action required */
  }
  for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_GTM_UNITS_CONFIG; LucCount++)
  {
    /* Update the configure pointer to point to the current Cluster */
    LpClusterConfig = &Gpt_GpGTMUnitConfig[LucCount];
    #if (GPT_TOM_UNIT_USED == STD_ON)
    if (GPT_HW_TOM == LpClusterConfig->ucTomAtomTypeChannel)
    {
      /* Set the TGC base register */
      LpTOMnTGCmUnitRegs = LpClusterConfig->pGtmTomAtomClusterRegs;                                                     /* PRQA S 0317 # JV-01 */
      /* Enable All channel update */
      LpTOMnTGCmUnitRegs->ulTOMnTGCmGLBCTRL = (uint32)LpClusterConfig->ucGtmTomATomClusterGlbCtrlRegVal;
      LpTOMnTGCmUnitRegs->ulTOMnTGCmENDISCTRL = (uint32)LpClusterConfig->ucGtmTomATomClusterEnDisCtrlRegVal;
      /* Disable the TOM Timer Start Register */
      LpTOMnTGCmUnitRegs->ulTOMnTGCmENDISSTAT = (uint32)LpClusterConfig->ucGtmTomATomClusterEnDisStsRegVal;
    }
    else
    #endif
    {
      #if (GPT_ATOM_UNIT_USED == STD_ON)
      /* Set the AGC bese register */
      LpATOMnAGCUnitRegs = LpClusterConfig->pGtmTomAtomClusterRegs;                                                     /* PRQA S 0317 # JV-01 */
      /* Enable All channel update */
      LpATOMnAGCUnitRegs->ulATOMnAGCGLBCTRL = (uint32)LpClusterConfig->ucGtmTomATomClusterGlbCtrlRegVal;
      LpATOMnAGCUnitRegs->ulATOMnAGCENDISCTRL = (uint32)LpClusterConfig->ucGtmTomATomClusterEnDisCtrlRegVal;
      /* Disable the ATOM Timer Start Register */
      LpATOMnAGCUnitRegs->ulATOMnAGCENDISSTAT = (uint32)LpClusterConfig->ucGtmTomATomClusterEnDisStsRegVal;
      #endif
    } /* else No action required */
  }
} /* End of API Gpt_HW_Gtm_UnitInit */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_ChannelInit
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData
**
** Functions invoked     : None
**
** Registers Used        : TOM[i]_CH[x]_SR0, TOM[i]_CH[x]_SR1, TOM[i]_CH[x]_CM0, TOM[i]_CH[x]_CM1, TOM[i]_CH[x]_CTRL,
**                         TOM[i]_CH[x]_CN0, TOM[i]_CH[x]_IRQ_MODE, TOM[i]_CH[x]_CTRL_SR, TOM[i]_CH[x]_IRQ_EN,
**                         ATOM[i]_CH[x]_SR0, ATOM[i]_CH[x]_SR1, ATOM[i]_CH[x]_CM0, ATOM[i]_CH[x]_CM1, 
**                         ATOM[i]_CH[x]_CTRL, ATOM[i]_CH[x]_CTRL_SR, ATOM[i]_CH[x]_CN0, ATOM[i]_CH[x]_IRQ_MODE, EICn,
**                         ATOM[i]_CH[x]_IRQ_EN
**
** Reference ID          : GPT_DUD_ACT_074
** Reference ID          : GPT_DUD_ACT_074_GLB001, GPT_DUD_ACT_074_GLB002
** Reference ID          : GPT_DUD_ACT_074_REG001, GPT_DUD_ACT_074_REG002, GPT_DUD_ACT_074_REG003
** Reference ID          : GPT_DUD_ACT_074_REG004, GPT_DUD_ACT_074_REG005, GPT_DUD_ACT_074_REG006
** Reference ID          : GPT_DUD_ACT_074_REG007, GPT_DUD_ACT_074_REG009, GPT_DUD_ACT_074_REG019
** Reference ID          : GPT_DUD_ACT_074_REG010, GPT_DUD_ACT_074_REG011, GPT_DUD_ACT_074_REG012
** Reference ID          : GPT_DUD_ACT_074_REG013, GPT_DUD_ACT_074_REG014, GPT_DUD_ACT_074_REG015
** Reference ID          : GPT_DUD_ACT_074_REG017, GPT_DUD_ACT_074_REG018
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

void Gpt_HW_Gtm_ChannelInit(Gpt_ChannelType LddChannel)                                                                 /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  const Gpt_ChannelConfigType* LpChannel;

  #if (GPT_TOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the TOM Unit registers */
  Gpt_TOMnCHmUnitRegs* LpTOMnCHmUnitRegs;
  #endif
  #if (GPT_ATOM_UNIT_USED == STD_ON)
  Gpt_ATOMnCHmUnitRegs* LpATOMnCHmUnitRegs;
  #endif
  /* Index to access data of core */
  uint8 LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Check the Notification is configured for the current channel */
  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* Set the Notification status as GPT_FALSE */
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blNotifyStatus = GPT_FALSE;
  #endif
  /* Disable the Interrupt processing EIC of the current channel */
  if (NULL_PTR != LpChannel->pEICReg)
  {
    /* Disable Interrupt */
    RH850_SV_MODE_ICR_OR(16, (LpChannel->pEICReg), GPT_EIMK_DISABLE_MASK);
    /* Dummy read */
    RH850_SV_MODE_REG_READ_ONLY(16, (LpChannel->pEICReg));
    /* Execute syncp */
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  } /* No action required */
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
  } /* No action required */
  #endif /* End of (GPT_CLEAR_PENDING_INTERRUPT == STD_ON) */
  /* Assign the timer status to the Channel */
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus = GPT_CH_NOTSTARTED;
  #if (GPT_TOM_UNIT_USED == STD_ON)
  if(GPT_HW_TOM == LpChannel->ucTimerType)
  {
    /* Set the TOM Channel base register */
    LpTOMnCHmUnitRegs = ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pTOMnCHmUnitRegs;                   /* PRQA S 0311, 0316 # JV-01, JV-01 */
    /* Initialized Compare shadow register 0 */
    LpTOMnCHmUnitRegs->ulTOMnCHmSR0 = GPT_DISABLETOMnCHmSR;
    /* Initialized Compare shadow register 1 */
    LpTOMnCHmUnitRegs->ulTOMnCHmSR1 = GPT_DISABLETOMnCHmSR;
    /* Initialized Compare register 0 */
    LpTOMnCHmUnitRegs->ulTOMnCHmCM0 = GPT_DISABLETOMnCHmCM;
    /* Initialized Compare register 1 */
    LpTOMnCHmUnitRegs->ulTOMnCHmCM1 = GPT_DISABLETOMnCHmCM;
    /* Set control register of counting mode  */
    LpTOMnCHmUnitRegs->ulTOMnCHmCTRL = GPT_TOM_PWM_MODE;
    /* Clear the clock select bit */
    LpTOMnCHmUnitRegs->ulTOMnCHmCTRL &= GPT_CLKSRCCLEARVALUE;
    /* Clock source select */
    LpTOMnCHmUnitRegs->ulTOMnCHmCTRL |= ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulClockselectValue; /* PRQA S 0311, 0316 # JV-01, JV-01 */
    #if(GPT_GTM_VERSION == GPT_GTM_410_VERSION)
    /* Clear the clock select bit */
    LpTOMnCHmUnitRegs->ulTOMnCHmCTRLSR &= GPT_CLKSRCCLEARVALUE;
    /* Clock source select */
    LpTOMnCHmUnitRegs->ulTOMnCHmCTRLSR |= \
                                        ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulClockselectValue; /* PRQA S 0311, 0316 # JV-01, JV-01 */
    #endif
    /* Reset counter value */
    LpTOMnCHmUnitRegs->ulTOMnCHmCN0 = GPT_RESET_GTM_COUNTER;
    /* Reset Channel interrupt mode register */
    LpTOMnCHmUnitRegs->ulTOMnCHmIRQMODE = GPT_RESET_TOMnCHm;
    /* Disable Interrupt */
    LpTOMnCHmUnitRegs->ulTOMnCHmIRQEN = GPT_DISABLEGTMCHmIRQEN;
  } /* else No action required */
  else
  #endif
  {
    #if (GPT_ATOM_UNIT_USED == STD_ON)
    /* Set the ATOM Channel base register */
    LpATOMnCHmUnitRegs = ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pATOMnCHmUnitRegs;                /* PRQA S 0311, 0316 # JV-01, JV-01 */
    /* Initialized Compare shadow register 0 */
    LpATOMnCHmUnitRegs->ulATOMnCHmSR0 = GPT_DISABLEATOMnCHmSR;
    /* Initialized Compare shadow register 1 */
    LpATOMnCHmUnitRegs->ulATOMnCHmSR1 = GPT_DISABLEATOMnCHmSR;
    /* Initialized Compare register 0 */
    LpATOMnCHmUnitRegs->ulATOMnCHmCM0 = GPT_DISABLEATOMnCHmCM;
    /* Initialized Compare register 1 */
    LpATOMnCHmUnitRegs->ulATOMnCHmCM1 = GPT_DISABLEATOMnCHmCM;
    /* Set control register of counting mode  */
    LpATOMnCHmUnitRegs->ulATOMnCHmCTRL = GPT_ATOM_PWM_MODE;
    /* Clear the clock select bit */
    LpATOMnCHmUnitRegs->ulATOMnCHmCTRL &= GPT_CLKSRCCLEARVALUE;
    /* Clock source select */
    LpATOMnCHmUnitRegs->ulATOMnCHmCTRL |= \
                                      ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulClockselectValue;  /* PRQA S 0311, 0316 # JV-01, JV-01 */
    #if(GPT_GTM_VERSION == GPT_GTM_410_VERSION)
    /* Clear the clock select bit in shadow register */
    LpATOMnCHmUnitRegs->ulATOMnCHmCTRLSR &= GPT_CLKSRCCLEARVALUE;
    /* Clock source select in shadow register */
    LpATOMnCHmUnitRegs->ulATOMnCHmCTRLSR |= \
                                      ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulClockselectValue;  /* PRQA S 0311, 0316 # JV-01, JV-01 */
    #endif
    /* Reset counter value */
    LpATOMnCHmUnitRegs->ulATOMnCHmCN0 = GPT_RESET_GTM_COUNTER;
    /* Reset Channel interrupt mode register */
    LpATOMnCHmUnitRegs->ulATOMnCHmIRQMODE = GPT_RESET_ATOMnCHm;
    /* Disable Interrupt */
    LpATOMnCHmUnitRegs->ulATOMnCHmIRQEN = GPT_DISABLEGTMCHmIRQEN;
    #endif
  } /* else No action required */
} /* End of API Gpt_HW_Gtm_ChannelInit */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_UnitDeInit
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
** Global Variables used : Gpt_GpGTMUnitConfig
**
** Functions invoked     : None
**
** Registers Used        : TOM[i]_TGC[g]_GLB_CTRL, ATOM[i]_AGC_GLB_CTRL
**
** Reference ID          : GPT_DUD_ACT_075
** Reference ID          : GPT_DUD_ACT_075_GLB001
** Reference ID          : GPT_DUD_ACT_075_REG001, GPT_DUD_ACT_075_REG002
***********************************************************************************************************************/
#if (GPT_DE_INIT_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

void Gpt_HW_Gtm_UnitDeInit(void)
{
  /* Declare a Local variable to count loop */
  uint8 LucCount;
  /* Pointer to Cluster configuration */
  const Gpt_GTMUnitConfigType* LpClusterConfig;
  #if (GPT_TOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the TGC Unit registers */
  Gpt_TOMnTGCmUnitRegs* LpTOMnTGCmUnitRegs;
  #endif
  #if (GPT_ATOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the AGC Unit registers */
  Gpt_ATOMnAGCUnitRegs* LpATOMnAGCUnitRegs;
  #endif
  for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_GTM_UNITS_CONFIG; LucCount++)
  {
    /* Update the configure pointer to point to the current Cluster */
    LpClusterConfig = &Gpt_GpGTMUnitConfig[LucCount];
    #if (GPT_TOM_UNIT_USED == STD_ON)
    if (GPT_HW_TOM == LpClusterConfig->ucTomAtomTypeChannel)
    {
      /* Set the TGC bese register */
      LpTOMnTGCmUnitRegs = LpClusterConfig->pGtmTomAtomClusterRegs;                                                     /* PRQA S 0317 # JV-01 */
      /* Disable the TOM Timer Start Register and reset all register of TOM channel */
      LpTOMnTGCmUnitRegs->ulTOMnTGCmGLBCTRL = GPT_UPPER_16BIT_CLEAR_MASK &
        (LpClusterConfig->ucGtmTomATomClusterGlbCtrlRegVal);
    } /* else No action required */
    else
    #endif
    {
      #if (GPT_ATOM_UNIT_USED == STD_ON)
      /* Set the TGC bese register */
      LpATOMnAGCUnitRegs = LpClusterConfig->pGtmTomAtomClusterRegs;                                                     /* PRQA S 0317 # JV-01 */
      /* Disable the ATOM Timer Start Register */
      LpATOMnAGCUnitRegs->ulATOMnAGCGLBCTRL = GPT_UPPER_16BIT_CLEAR_MASK &
        (LpClusterConfig->ucGtmTomATomClusterGlbCtrlRegVal);
      #endif
    } /* else No action required */
  }
} /* End of API Gpt_HW_Gtm_UnitDeInit */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_DE_INIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_ChannelDeInit
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
** Return Parameter      : None
**
** Pre-condition         : None
**
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData
**
** Functions invoked     : None
**
** Registers Used        : EICn
**
** Reference ID          : GPT_DUD_ACT_076
** Reference ID          : GPT_DUD_ACT_076_GBL001, GPT_DUD_ACT_076_GBL002
** Reference ID          : GPT_DUD_ACT_076_REG001
***********************************************************************************************************************/
#if (GPT_DE_INIT_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

void Gpt_HW_Gtm_ChannelDeInit(Gpt_ChannelType LddChannel)                                                               /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  const Gpt_ChannelConfigType* LpChannel;

  /* Index to access data of core */
  uint8 LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Check the Notification is configured for the current channel */
  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* Set the Notification status as GPT_FALSE */
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blNotifyStatus = GPT_FALSE;
  #endif
  /* Disable the Interrupt processing EIC of the current channel */
  if (NULL_PTR != LpChannel->pEICReg)
  {
    /* Disable Interrupt */
    RH850_SV_MODE_ICR_OR(16, (LpChannel->pEICReg), GPT_EIMK_DISABLE_MASK);
    /* Dummy read */
    RH850_SV_MODE_REG_READ_ONLY(16, (LpChannel->pEICReg));
    /* Execute syncp */
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  } /* No action required */
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
  } /* No action required */
  #endif /* End of (GPT_CLEAR_PENDING_INTERRUPT == STD_ON) */
  /* Assign the timer status to the Channel */
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus = GPT_CH_NOTSTARTED;
} /* End of API Gpt_HW_Gtm_ChannelDeInit */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_DE_INIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_GetTimeElapsed
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function returns the time elapsed for 
**                         a channel by accessing the respective timer registers.
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
** Return Value          : Returns the elapsed time value in ticks
**
** Pre-condition         : None
**
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData
**
** Functions invoked     : SchM_Enter_Gpt_##Exclusive_Area(), SchM_Exit_Gpt_##Exclusive_Area()
**
** Registers used        : TOM[i]_CH[x]_CM0, TOM[i]_CH[x]_CN0, TOM[i]_CH[x]_IRQ_NOTIFY,
**                         ATOM[i]_CH[x]_CM0, ATOM[i]_CH[x]_CN0, ATOM[i]_CH[x]_IRQ_NOTIFY
**
** Reference ID          : GPT_DUD_ACT_077
** Reference ID          : GPT_DUD_ACT_077_CRT001, GPT_DUD_ACT_077_CRT002
***********************************************************************************************************************/
#if (GPT_TIME_ELAPSED_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

Gpt_ValueType Gpt_HW_Gtm_GetTimeElapsed (Gpt_ChannelType LddChannel)
{
  /* Pointer to the channel configuration */
  const Gpt_ChannelConfigType* LpChannel;
  #if (GPT_TOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the TOM Unit registers */
  Gpt_TOMnCHmUnitRegs* LpTOMnCHmUnitRegs;                                                                               /* PRQA S 3678 # JV-01 */
  #endif
  #if (GPT_ATOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the ATOM Unit registers */
  Gpt_ATOMnCHmUnitRegs* LpATOMnCHmUnitRegs;                                                                             /* PRQA S 3678 # JV-01 */
  #endif
  /* Variable to hold timer Elapsed time*/
  Gpt_ValueType LddTimeElapsed;
  /* Index to access data of core */
  uint8 LucAccPointIdx;
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
  if (GPT_CH_NOTSTARTED != Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus)
  {
    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter Protected area  */
    GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
    #if (GPT_TOM_UNIT_USED == STD_ON)
    if(GPT_HW_TOM == LpChannel->ucTimerType)
    {
      /* Set the TOM Channel base register */
      LpTOMnCHmUnitRegs = ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pTOMnCHmUnitRegs;                 /* PRQA S 0311, 0316 # JV-01, JV-01 */
      /* Assign the final return value */
      LddTimeElapsed = (uint32)(LpTOMnCHmUnitRegs->ulTOMnCHmCN0);
      /* Expired Check of current channel */
      if((GPT_CH_EXPIRED == Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus)||
          ((uint32)GPT_ZERO != (LpTOMnCHmUnitRegs->ulTOMnCHmIRQNOTIFY & GPT_GTM_INTERRUPT_MATCH_MASK)))
      {
        if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
        {
          /* Assign the final return value */
          LddTimeElapsed = (uint32)(LpTOMnCHmUnitRegs->ulTOMnCHmCM0);
        } /* No action required */
      } /* No action required */
    } /* No action required */
    else
    #endif
    {
      #if (GPT_ATOM_UNIT_USED == STD_ON)
      /* Set the ATOM Channel base register */
      LpATOMnCHmUnitRegs = ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pATOMnCHmUnitRegs;              /* PRQA S 0311, 0316 # JV-01, JV-01 */
      /* Assign the final return value */
      LddTimeElapsed = (uint32)(LpATOMnCHmUnitRegs->ulATOMnCHmCN0);
      /* Expired Check of current channel */
      if((GPT_CH_EXPIRED == Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus)||
          ((uint32)GPT_ZERO != (LpATOMnCHmUnitRegs->ulATOMnCHmIRQNOTIFY & GPT_GTM_INTERRUPT_MATCH_MASK)))
      {
        if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
        {
          /* Assign the final return value */
          LddTimeElapsed = (uint32)(LpATOMnCHmUnitRegs->ulATOMnCHmCM0);
        } /* No action required */
      } /* No action required */
      #endif
    } /* No action required */
    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit Protected area */
    GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
  }
  return(LddTimeElapsed);
} /* End of API Gpt_HW_Gtm_GetTimeElapsed */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of GPT_TIME_ELAPSED_API == STD_ON */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_GetTimeRemaining
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function returns the time remaining for
**                         the channel's next timeout by accessing the respective timer registers.
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
** Return Value          : Returns the remaining time value in ticks
**
** Pre-condition         : None
**
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData
**
** Functions invoked     : SchM_Enter_Gpt_##Exclusive_Area(), SchM_Exit_Gpt_##Exclusive_Area()
**
** Registers used        : TOM[i]_CH[x]_CM0, TOM[i]_CH[x]_CN0, TOM[i]_CH[x]_IRQ_NOTIFY,
**                         ATOM[i]_CH[x]_CM0, ATOM[i]_CH[x]_CN0, ATOM[i]_CH[x]_IRQ_NOTIFY
**
** Reference ID          : GPT_DUD_ACT_078
** Reference ID          : GPT_DUD_ACT_078_CRT001, GPT_DUD_ACT_078_CRT002
***********************************************************************************************************************/
#if (GPT_TIME_REMAINING_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

Gpt_ValueType Gpt_HW_Gtm_GetTimeRemaining (Gpt_ChannelType LddChannel)
{
  #if (GPT_TOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the TOM Unit registers */
  Gpt_TOMnCHmUnitRegs* LpTOMnCHmUnitRegs;                                                                               /* PRQA S 3678 # JV-01 */
  #endif
  #if (GPT_ATOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the ATOM Unit registers */
  Gpt_ATOMnCHmUnitRegs* LpATOMnCHmUnitRegs;                                                                             /* PRQA S 3678 # JV-01 */
  #endif
 /* Pointer to the channel configuration */
  const Gpt_ChannelConfigType* LpChannel;
  /* Variable to hold timer remaining time */
  Gpt_ValueType LddTimeRemaining;
  /* Index to access data of core */
  uint8 LucAccPointIdx;
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
  if (GPT_CH_NOTSTARTED != Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus)
  {
    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter Protected area */
    GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
    /* Set the return value to zero */
    LddTimeRemaining = (uint32)GPT_ZERO;                                                                                /* PRQA S 2982 # JV-01 */
    #if (GPT_TOM_UNIT_USED == STD_ON)
    if(GPT_HW_TOM == LpChannel->ucTimerType)
    {
      /* Set the TOM Channel base register */
      LpTOMnCHmUnitRegs = ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pTOMnCHmUnitRegs;                 /* PRQA S 0311, 0316 # JV-01, JV-01 */
      /* Assign the final return value */
      LddTimeRemaining = (uint32)(LpTOMnCHmUnitRegs->ulTOMnCHmCM0) - (uint32)(LpTOMnCHmUnitRegs->ulTOMnCHmCN0);         /* PRQA S 0404, 3384 # JV-01, JV-01 */
      if((GPT_CH_EXPIRED == Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus)||
          ((uint32)GPT_ZERO != (LpTOMnCHmUnitRegs->ulTOMnCHmIRQNOTIFY & GPT_GTM_INTERRUPT_MATCH_MASK)))
      {
        /* Expired Chack of current channel */
        if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
        {
          /* Set the return value to zero */
          LddTimeRemaining = (uint32)GPT_ZERO;
        } /* No action required */
      } /* No action required */
    } /* No action required */
    else
    #endif
    {
      #if (GPT_ATOM_UNIT_USED == STD_ON)
      /* Set the ATOM Channel base register */
      LpATOMnCHmUnitRegs = ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pATOMnCHmUnitRegs;              /* PRQA S 0311, 0316 # JV-01, JV-01 */
      /* Assign the final return value */
      LddTimeRemaining = (uint32)(LpATOMnCHmUnitRegs->ulATOMnCHmCM0) - (uint32)(LpATOMnCHmUnitRegs->ulATOMnCHmCN0);     /* PRQA S 0404, 3384 # JV-01, JV-01 */
      /* Expired Chack of current channel */
      if((GPT_CH_EXPIRED == Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus)||
        ((uint32)GPT_ZERO != (LpATOMnCHmUnitRegs->ulATOMnCHmIRQNOTIFY & GPT_GTM_INTERRUPT_MATCH_MASK)))
      {
        if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
        {
          /* Set the return value to zero */
          LddTimeRemaining = (uint32)GPT_ZERO;
        } /* No action required */
      } /* No action required */
      #endif
    } /* No action required */
    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit Protected area */
    GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
  }
  return(LddTimeRemaining);
} /* End of API Gpt_HW_Gtm_GetTimeRemaining */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_TIME_REMAINING_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_StartTimer
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function starts the timer channel by
**                         loading the compare registers and enabling the clock.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GpTOMUnitConfig, Gpt_GpATOMUnitConfig
**
** Functions invoked     : SchM_Enter_Gpt_##Exclusive_Area(), SchM_Exit_Gpt_##Exclusive_Area()
**                         Gpt_HW_Gtm_EnableInterrupt
**
** Registers used        : TOM[i]_TGC[g]_ENDIS_STAT, TOM[i]_CH[x]_IRQ_MODE, TOM[i]_CH[x]_CM0, TOM[i]_CH[x]_SR0,
**                         TOM[i]_CH[x]_CTRL, TOM[i]_CH[x]_CN0, TOM[i]_CH[x]_IRQ_NOTIFY
**                         ATOM[i]_AGC_ENDIS_STAT, ATOM[i]_CH[x]_IRQ_MODE, ATOM[i]_CH[x]_CM0, ATOM[i]_CH[x]_SR0,
**                         ATOM[i]_CH[x]_CTRL, ATOM[i]_CH[x]_CN0, ATOM[i]_CH[x]_IRQ_NOTIFY
**                         GTM_IRQ_SELij, EICn
**
** Reference ID          : GPT_DUD_ACT_079
** Reference ID          : GPT_DUD_ACT_079_CRT001, GPT_DUD_ACT_079_CRT002
** Reference ID          : GPT_DUD_ACT_079_GLB001
** Reference ID          : GPT_DUD_ACT_079_REG001, GPT_DUD_ACT_079_REG002, GPT_DUD_ACT_079_REG003
** Reference ID          : GPT_DUD_ACT_079_REG004, GPT_DUD_ACT_079_REG005, GPT_DUD_ACT_079_REG006
** Reference ID          : GPT_DUD_ACT_079_REG007, GPT_DUD_ACT_079_REG008, GPT_DUD_ACT_079_REG009
** Reference ID          : GPT_DUD_ACT_079_REG010, GPT_DUD_ACT_079_REG011, GPT_DUD_ACT_079_REG012
** Reference ID          : GPT_DUD_ACT_079_REG013, GPT_DUD_ACT_079_REG014, GPT_DUD_ACT_079_REG015
** Reference ID          : GPT_DUD_ACT_079_REG016, GPT_DUD_ACT_079_REG017
** Reference ID          : GPT_DUD_ACT_079_ERR001
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

void Gpt_HW_Gtm_StartTimer (Gpt_ChannelType LddChannel, Gpt_ValueType LddValue)                                         /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  const Gpt_ChannelConfigType* LpChannel;
  /* Pointer to Cluster configuration */
  const Gpt_GTMUnitConfigType* LpClusterConfig;
  #if (GPT_TOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the TGC Unit registers */
  Gpt_TOMnTGCmUnitRegs* LpTOMnTGCmUnitRegs;
  /* Pointer pointing to the TOM Unit registers */
  Gpt_TOMnCHmUnitRegs* LpTOMnCHmUnitRegs;
  #endif
  #if (GPT_ATOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the AGC Unit registers */
  Gpt_ATOMnAGCUnitRegs* LpATOMnAGCUnitRegs;
  /* Pointer pointing to the ATOM Unit registers */
  Gpt_ATOMnCHmUnitRegs* LpATOMnCHmUnitRegs;
  #endif

  /* Declare the variable to store the DET return value */
  Std_ReturnType LddReturnValue;
  LddReturnValue = E_OK;
  /* Index to access data of core */
  uint8 LucAccPointIdx;
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Check if the Channel value is more than Max count value or ZERO */
  if (GPT_ONE >= LddValue)
  {
    /* Report to DET */
    (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_SID, GPT_E_PARAM_VALUE);
    /* Set Return value */
    LddReturnValue = E_NOT_OK;
  } /* else No action required */
  #endif /* (GPT_DEV_ERROR_DETECT == STD_ON) */
  /* Check if any DET error was reported */
  if(E_OK == LddReturnValue)                                                                                            /* PRQA S 2991, 2995 # JV-01, JV-01 */
  {
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
    if (GPT_MODE_NORMAL == Gpt_GucDriverMode)                                                                           /* PRQA S 3416 # JV-01 */
    {
      /* Update the configure pointer to point to the current Cluster */
      LpClusterConfig = &Gpt_GpGTMUnitConfig[LpChannel->ucTimerUnitIndex];
      #if (GPT_TOM_UNIT_USED == STD_ON)
      if(GPT_HW_TOM == LpChannel->ucTimerType)
      {
        /* Set the TOM Channel base register */
        LpTOMnCHmUnitRegs = ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pTOMnCHmUnitRegs;               /* PRQA S 0311, 0316 # JV-01, JV-01 */
        /* Set the TGC bese register */
        LpTOMnTGCmUnitRegs = LpClusterConfig->pGtmTomAtomClusterRegs;                                                   /* PRQA S 0317 # JV-01 */
        /* Stop Counter */
        LpTOMnTGCmUnitRegs->ulTOMnTGCmENDISSTAT =
                              ~(((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig) -> ulCounterStartMaskValue); /* PRQA S 0311, 0316 # JV-01, JV-01 */
      }
      else
      #endif
      {
        #if (GPT_ATOM_UNIT_USED == STD_ON)
        /* Set the ATOM Channel base register */
        LpATOMnCHmUnitRegs = ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pATOMnCHmUnitRegs;            /* PRQA S 0311, 0316 # JV-01, JV-01 */
        /* Set the AGC bese register */
        LpATOMnAGCUnitRegs = LpClusterConfig->pGtmTomAtomClusterRegs;                                                   /* PRQA S 0317 # JV-01 */
        /* Stop Counter */
        LpATOMnAGCUnitRegs->ulATOMnAGCENDISSTAT =
                             ~(((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig) -> ulCounterStartMaskValue); /* PRQA S 0311, 0316 # JV-01, JV-01 */
        #endif
      }

      if (GPT_CH_MODE_CONTINUOUS == LpChannel->ucGptChannelMode)
      {
        #if((GPT_CLEAR_PENDING_INTERRUPT == STD_ON) && (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON))
        #if (GPT_TOM_UNIT_USED == STD_ON)
        if(GPT_HW_TOM == LpChannel->ucTimerType)
        {
          /* Clear the interrupt flag */
          LpTOMnCHmUnitRegs->ulTOMnCHmIRQNOTIFY = GPT_CLEAR_INTERRUPT_GTM;                                              /* PRQA S 2962 # JV-01 */
        } /* else No action required */
        else
        #endif
        {
          #if (GPT_ATOM_UNIT_USED == STD_ON)
          if(GPT_HW_ATOM == LpChannel->ucTimerType)
          {
            /* Clear the interrupt flag */
            LpATOMnCHmUnitRegs->ulATOMnCHmIRQNOTIFY = GPT_CLEAR_INTERRUPT_GTM;                                          /* PRQA S 2962 # JV-01 */
          } /* else No action required */
          #endif
        }
        #endif
      } /* else No action required */
      else
      {
        #if(GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
        /* Enable Interrupt */
        Gpt_HW_Gtm_EnableInterrupt(LddChannel);
        #endif
      }

      /* Enable the interrupt processing EIC of the current channel, but disable interrupt processing of channel */
      if (NULL_PTR != LpChannel->pEICReg)
      {
        /* Enable Interrupt */
        RH850_SV_MODE_ICR_AND(16, (LpChannel->pEICReg), GPT_EIMK_ENABLE_MASK);
        /* Dummy read */
        RH850_SV_MODE_REG_READ_ONLY(16, (LpChannel->pEICReg));
        /* Execute syncp */
        EXECUTE_SYNCP();                                                                                                /* PRQA S 1006 # JV-01 */
      } /* No action required */

      /* End of LpChannel->ucGptChannelMode == GPT_CH_MODE_ONESHOT */
      #if (GPT_TOM_UNIT_USED == STD_ON)
      if(GPT_HW_TOM == LpChannel->ucTimerType)
      {
        /* Set Channel interrupt mode to pulse mode */
        LpTOMnCHmUnitRegs->ulTOMnCHmIRQMODE = GPT_CHANNEL_INT_PULSE_MODE;                                               /* PRQA S 2962 # JV-01 */
        #if(GPT_GTM_VERSION == GPT_GTM_410_VERSION)
        /* Enable Select interrupt */
        if(NULL_PTR != ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pGTM_IRQ_SELij)                      /* PRQA S 0311, 0316 # JV-01, JV-01 */
        {
          *(((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pGTM_IRQ_SELij) =                               /* PRQA S 0311, 0316 # JV-01, JV-01 */
                              ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulGTM_IRQ_SELijEnableValue;   /* PRQA S 0311, 0316 # JV-01, JV-01 */
        }
        #endif
        /* Set Compare register */
        LpTOMnCHmUnitRegs->ulTOMnCHmCM0 = LddValue;                                                                     /* PRQA S 2962 # JV-01 */
        LpTOMnCHmUnitRegs->ulTOMnCHmSR0 = LddValue;                                                                     /* PRQA S 2962 # JV-01 */
        if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
        {
          /* Set control register of counting mode  */
          LpTOMnCHmUnitRegs->ulTOMnCHmCTRL |= GPT_TOMATOM_ONE_SHOT;                                                     /* PRQA S 2962 # JV-01 */
          /* Start Counter */
          LpTOMnTGCmUnitRegs->ulTOMnTGCmENDISSTAT =                                                                     /* PRQA S 2812, 2962 # JV-01, JV-01 */
                                ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulCounterStartMaskValue;    /* PRQA S 0311, 0316 # JV-01, JV-01 */
          /* Reset counter value */
          LpTOMnCHmUnitRegs->ulTOMnCHmCN0 = GPT_RESET_GTM_COUNTER;                                                      /* PRQA S 2962 # JV-01 */
        }
        else
        {
          /* Reset counter value */
          LpTOMnCHmUnitRegs->ulTOMnCHmCN0 = GPT_RESET_GTM_COUNTER;
          /* Start Counter */
          LpTOMnTGCmUnitRegs->ulTOMnTGCmENDISSTAT =
                                ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulCounterStartMaskValue;    /* PRQA S 0311, 0316 # JV-01, JV-01 */
        }
      }/* No action required */
      else
      #endif
      {
        #if (GPT_ATOM_UNIT_USED == STD_ON)
        /* Set Channel interrupt mode to pulse mode */
        LpATOMnCHmUnitRegs->ulATOMnCHmIRQMODE = GPT_CHANNEL_INT_PULSE_MODE;                                             /* PRQA S 2962 # JV-01 */
        #if(GPT_GTM_VERSION == GPT_GTM_410_VERSION)
        /* Enable Select interrupt */
        if(NULL_PTR != ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pGTM_IRQ_SELij)                     /* PRQA S 0311, 0316 # JV-01, JV-01 */
        {
          *(((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pGTM_IRQ_SELij) =                              /* PRQA S 0311, 0316 # JV-01, JV-01 */
                            ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulGTM_IRQ_SELijEnableValue;    /* PRQA S 0311, 0316 # JV-01, JV-01 */
        }
        #endif
        /* Set Compare register */
        LpATOMnCHmUnitRegs->ulATOMnCHmCM0 = LddValue;                                                                   /* PRQA S 2962 # JV-01 */
        LpATOMnCHmUnitRegs->ulATOMnCHmSR0 = LddValue;                                                                   /* PRQA S 2962 # JV-01 */
        if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
        {
          /* Set control register of counting mode  */
          LpATOMnCHmUnitRegs->ulATOMnCHmCTRL |= GPT_TOMATOM_ONE_SHOT;                                                   /* PRQA S 2962 # JV-01 */
          /* Star Counter */
          LpATOMnAGCUnitRegs->ulATOMnAGCENDISSTAT =                                                                     /* PRQA S 2962 # JV-01 */
                                ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulCounterStartMaskValue;   /* PRQA S 0311, 0316 # JV-01, JV-01 */
          /* Reset counter value */
          LpATOMnCHmUnitRegs->ulATOMnCHmCN0 = GPT_RESET_GTM_COUNTER;                                                    /* PRQA S 2962 # JV-01 */
        }
        else
        {
          /* Reset counter value */
          LpATOMnCHmUnitRegs->ulATOMnCHmCN0 = GPT_RESET_GTM_COUNTER;
          /* Star Counter */
          LpATOMnAGCUnitRegs->ulATOMnAGCENDISSTAT =
                                ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulCounterStartMaskValue;   /* PRQA S 0311, 0316 # JV-01, JV-01 */
        }
        #endif
      } /* No action required */
      /* Assign the timer status to the Channel */
      Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus = GPT_CH_RUNNING;
    }

    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit Protected area */
    GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    #endif
  } /* No action required */
} /* End of API Gpt_HW_Gtm_StartTimer */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_StopTimer
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function stops the channel by disabling
**                         the interrupt and/or the clock.
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GpTOMUnitConfig, Gpt_GpATOMUnitConfig
**
** Functions invoked     : Gpt_HW_Gtm_DisableInterrupt
**
** Registers used        : TOM[i]_TGC[g]_ENDIS_STAT, ATOM[i]_AGC_ENDIS_STAT, TOM[i]_CH[x]_IRQ_EN, ATOM[i]_CH[x]_IRQ_EN
**
** Reference ID          : GPT_DUD_ACT_080
** Reference ID          : GPT_DUD_ACT_080_GLB001
** Reference ID          : GPT_DUD_ACT_080_REG001, GPT_DUD_ACT_080_REG002, GPT_DUD_ACT_080_REG003
** Reference ID          : GPT_DUD_ACT_080_REG004
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

void Gpt_HW_Gtm_StopTimer (Gpt_ChannelType LddChannel)
{
  /* Pointer to the channel configuration */
  const Gpt_ChannelConfigType* LpChannel;
  /* Pointer to Cluster configuration */
  const Gpt_GTMUnitConfigType* LpClusterConfig;
  #if (GPT_TOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the TGC Unit registers */
  Gpt_TOMnTGCmUnitRegs* LpTOMnTGCmUnitRegs;
  /* Pointer pointing to the TOM Unit registers */
  Gpt_TOMnCHmUnitRegs* LpTOMnCHmUnitRegs;
  #endif
  #if (GPT_ATOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the AGC Unit registers */
  Gpt_ATOMnAGCUnitRegs* LpATOMnAGCUnitRegs;
  /* Pointer pointing to the ATOM Unit registers */
  Gpt_ATOMnCHmUnitRegs* LpATOMnCHmUnitRegs;
  #endif
  /* Index to access data of core */
  uint8 LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];
  /* Update the configure pointer to point to the current Cluster */
  LpClusterConfig = &Gpt_GpGTMUnitConfig[LpChannel->ucTimerUnitIndex];
  #if (GPT_TOM_UNIT_USED == STD_ON)
  if(GPT_HW_TOM == LpChannel->ucTimerType)
  {
    /* Set the TGC bese register */
    LpTOMnTGCmUnitRegs = LpClusterConfig->pGtmTomAtomClusterRegs;                                                       /* PRQA S 0317 # JV-01 */
    /* Stop Counter */
    LpTOMnTGCmUnitRegs->ulTOMnTGCmENDISSTAT =
                      ~(((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulCounterStartMaskValue);           /* PRQA S 0311, 0316 # JV-01, JV-01 */
    /* Set the ATOM Channel base register */
    LpTOMnCHmUnitRegs = ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pTOMnCHmUnitRegs;                   /* PRQA S 0311, 0316 # JV-01, JV-01 */
    /* Disable Interrupt */
    LpTOMnCHmUnitRegs->ulTOMnCHmIRQEN = GPT_DISABLEGTMCHmIRQEN;
  }
  else
  #endif
  {
    #if (GPT_ATOM_UNIT_USED == STD_ON)
    /* Set the TGC bese register */
    LpATOMnAGCUnitRegs = LpClusterConfig->pGtmTomAtomClusterRegs;                                                       /* PRQA S 0317 # JV-01 */
    /* Stop Counter */
    LpATOMnAGCUnitRegs->ulATOMnAGCENDISSTAT =
                      ~(((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulCounterStartMaskValue);          /* PRQA S 0311, 0316 # JV-01, JV-01 */
    /* Set the ATOM Channel base register */
    LpATOMnCHmUnitRegs = ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pATOMnCHmUnitRegs;                /* PRQA S 0311, 0316 # JV-01, JV-01 */
    /* Disable Interrupt */
    LpATOMnCHmUnitRegs->ulATOMnCHmIRQEN = GPT_DISABLEGTMCHmIRQEN;
    #endif
  } /* No action required */
  /* Assign the timer status to the Channel */
  Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus = GPT_CH_STOPPED;
} /* End of API Gpt_HW_Gtm_StopTimer */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_EnableInterrupt
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function Enables the interrupt of channel
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
** Global Variables used : Gpt_GaaGlobalAccPoint
**
** Functions invoked     : None
**
** Registers used        : ATOM[i]_CH[x]_IRQ_EN, TOM[i]_CH[x]_IRQ_EN
**
** Reference ID          : GPT_DUD_ACT_081
** Reference ID          : GPT_DUD_ACT_081_REG001, GPT_DUD_ACT_081_REG002
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

void Gpt_HW_Gtm_EnableInterrupt (Gpt_ChannelType LddChannel)
{
  /* Pointer to the channel configuration */
  const Gpt_ChannelConfigType* LpChannel;
  /* Index to access data of core */
  uint8 LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  #if (GPT_TOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the TOM Unit registers */
  Gpt_TOMnCHmUnitRegs* LpTOMnCHmUnitRegs;
  #endif
  #if (GPT_ATOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the ATOM Unit registers */
  Gpt_ATOMnCHmUnitRegs* LpATOMnCHmUnitRegs;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];

  #if (GPT_TOM_UNIT_USED == STD_ON)
  if(GPT_HW_TOM == LpChannel->ucTimerType)
  {
    /* Set the TOM Channel base register */
    LpTOMnCHmUnitRegs = ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pTOMnCHmUnitRegs;                   /* PRQA S 0311, 0316 # JV-01, JV-01 */
    /* Enable Interrupt */
    LpTOMnCHmUnitRegs->ulTOMnCHmIRQEN = GPT_ENABLEGTMCHmIRQEN;
  }
  else
  #endif
  {
    #if (GPT_ATOM_UNIT_USED == STD_ON)
    /* Set the ATOM Channel base register */
    LpATOMnCHmUnitRegs = ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pATOMnCHmUnitRegs;                /* PRQA S 0311, 0316 # JV-01, JV-01 */
    /* Enable Interrupt */
    LpATOMnCHmUnitRegs->ulATOMnCHmIRQEN = GPT_ENABLEGTMCHmIRQEN;
    #endif
   } /* No action required */
} /* End of API Gpt_HW_Gtm_EnableInterrupt */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_DisableInterrupt
**
** Service ID            : NA
**
** Description           : This is GPT Driver component support function. This function Disables the interrupt of
**                         channel
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
** Global Variables used : Gpt_GaaGlobalAccPoint
**
** Functions invoked     : None
**
** Registers used        : ATOM[i]_CH[x]_IRQ_EN, TOM[i]_CH[x]_IRQ_EN
**
** Reference ID          : GPT_DUD_ACT_082
** Reference ID          : GPT_DUD_ACT_082_REG001, GPT_DUD_ACT_082_REG002
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

void Gpt_HW_Gtm_DisableInterrupt (Gpt_ChannelType LddChannel)
{
  /* Pointer to the channel configuration */
  const Gpt_ChannelConfigType* LpChannel;
  /* Index to access data of core */
  uint8 LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  #if (GPT_TOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the TOM Unit registers */
  Gpt_TOMnCHmUnitRegs* LpTOMnCHmUnitRegs;
  #endif
  #if (GPT_ATOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the ATOM Unit registers */
  Gpt_ATOMnCHmUnitRegs* LpATOMnCHmUnitRegs;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel];

  #if (GPT_TOM_UNIT_USED == STD_ON)
  if(GPT_HW_TOM == LpChannel->ucTimerType)
  {
    /* Set the TOM Channel base register */
    LpTOMnCHmUnitRegs = ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pTOMnCHmUnitRegs;                   /* PRQA S 0311, 0316 # JV-01, JV-01 */
    /* Disable Interrupt */
    LpTOMnCHmUnitRegs->ulTOMnCHmIRQEN = GPT_DISABLEGTMCHmIRQEN;
  }
  else
  #endif
  {
    #if (GPT_ATOM_UNIT_USED == STD_ON)
    /* Set the ATOM Channel base register */
    LpATOMnCHmUnitRegs = ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pATOMnCHmUnitRegs;                /* PRQA S 0311, 0316 # JV-01, JV-01 */
    /* Disable Interrupt */
    LpATOMnCHmUnitRegs->ulATOMnCHmIRQEN = GPT_DISABLEGTMCHmIRQEN;
    #endif
  }
} /* End of API Gpt_HW_Gtm_DisableInterrupt */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_CbkNotification
**
** Service ID            : NA
**
** Description           : This routine is used to invoke the callback notification or wakeup notification based on
**                         timer mode.
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
** Global Variables used : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GpTOMUnitConfig, Gpt_GpATOMUnitConfig
**
** Functions invoked     : Dem_ReportErrorStatus
**
** Registers used        : TOM[i]_CH[x]_IRQ_NOTIFY, ATOM[i]_CH[x]_IRQ_NOTIFY, ATOM[i]_CH[x]_IRQ_EN, TOM[i]_CH[x]_IRQ_EN
**                         TOM[i]_TGC[g]_ENDIS_STAT, ATOM[i]_AGC_ENDIS_STAT, EICn
**
** Reference ID          : GPT_DUD_ACT_083
** Reference ID          : GPT_DUD_ACT_083_ERR001
** Reference ID          : GPT_DUD_ACT_083_REG001, GPT_DUD_ACT_083_REG002, GPT_DUD_ACT_083_REG003
** Reference ID          : GPT_DUD_ACT_083_REG004, GPT_DUD_ACT_083_REG005, GPT_DUD_ACT_083_REG006
** Reference ID          : GPT_DUD_ACT_083_GLB001
***********************************************************************************************************************/
#define GPT_START_SEC_CODE_FAST
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

void  Gpt_HW_Gtm_CbkNotification(uint8 LucChannelIdx)
{
  /* Pointer to the channel configuration */
  const Gpt_ChannelConfigType* LpChannel;
  /* Pointer to Cluster configuration */
  const Gpt_GTMUnitConfigType* LpClusterConfig;
  #if (GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* DEM Error Status */
  uint8 LucDemErrorStatus;
  #endif /* End of GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON */
  /* Index to access data of core */
  uint8 LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK);
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  #if (GPT_TOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the TGC Unit registers */
  Gpt_TOMnTGCmUnitRegs* LpTOMnTGCmUnitRegs;
  /* Pointer pointing to the TOM Unit registers */
  Gpt_TOMnCHmUnitRegs* LpTOMnCHmUnitRegs;
  #endif
  #if (GPT_ATOM_UNIT_USED == STD_ON)
  /* Pointer pointing to the AGC Unit registers */
  Gpt_ATOMnAGCUnitRegs* LpATOMnAGCUnitRegs;
  /* Pointer pointing to the ATOM Unit registers */
  Gpt_ATOMnCHmUnitRegs* LpATOMnCHmUnitRegs;
  #endif
  /* Updating the channel config parameter to the current channel */
  LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LucChannelIdx];
  /* Update the configure pointer to point to the current Cluster */
  LpClusterConfig = &Gpt_GpGTMUnitConfig[LpChannel->ucTimerUnitIndex];
  #if (GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  LucDemErrorStatus = GPT_DEM_NOT_ERROR;
  if (NULL_PTR != LpChannel->pEICReg)
  {
    if (GPT_ZERO != (*LpChannel->pEICReg & GPT_EIC_EIMK_MASK))
    {
      GPT_DEM_REPORT_ERROR(GPT_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
      LucDemErrorStatus = GPT_DEM_ERROR;
    } /* No action required */
  }
  if (GPT_DEM_NOT_ERROR == LucDemErrorStatus)
  {
  #endif
    if (GPT_MODE_NORMAL == Gpt_GucDriverMode)                                                                           /* PRQA S 3416 # JV-01 */
    {
      #if (GPT_TOM_UNIT_USED == STD_ON)
      if(GPT_HW_TOM == LpChannel->ucTimerType)
      {
        LpTOMnCHmUnitRegs = ((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pTOMnCHmUnitRegs;               /* PRQA S 0311, 0316 # JV-01, JV-01 */
        if(GPT_ZERO != (LpTOMnCHmUnitRegs->ulTOMnCHmIRQNOTIFY & GPT_GTM_INTERRUPT_MATCH_MASK))
        {
          if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
          {
            /* Set the TGC bese register */
            LpTOMnTGCmUnitRegs = LpClusterConfig->pGtmTomAtomClusterRegs;                                               /* PRQA S 0317 # JV-01 */
            /* Stop Counter */
            LpTOMnTGCmUnitRegs->ulTOMnTGCmENDISSTAT =
                      ~(((Gpt_TOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulCounterStartMaskValue);           /* PRQA S 0311, 0316 # JV-01, JV-01 */
            /* Disable Interrupt */
            LpTOMnCHmUnitRegs->ulTOMnCHmIRQEN = GPT_DISABLEGTMCHmIRQEN;
            /* Assign the timer status to the One-shot Channel */
            Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus = GPT_CH_EXPIRED;
          } /* No action required */
          #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
          /* Invoke callback notification if notification is enabled */
          if (GPT_TRUE == Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blNotifyStatus)
          {
            if (NULL_PTR != LpChannel->pGptNotificationPointer)
            {
              /* Clear the interrupt flag */
              LpTOMnCHmUnitRegs->ulTOMnCHmIRQNOTIFY = GPT_CLEAR_INTERRUPT_GTM;
              /* Invoke the callback function */
              LpChannel->pGptNotificationPointer();
            } /* No action required*/
          } /* No action required*/
          #endif /* End of (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) */
        } /* No action required*/
      }
      else
      #endif
      {
        #if (GPT_ATOM_UNIT_USED == STD_ON)
        LpATOMnCHmUnitRegs = ((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->pATOMnCHmUnitRegs;            /* PRQA S 0311, 0316 # JV-01, JV-01 */
        if(GPT_ZERO != (LpATOMnCHmUnitRegs->ulATOMnCHmIRQNOTIFY & GPT_GTM_INTERRUPT_MATCH_MASK))
        {
          if (GPT_CH_MODE_ONESHOT == LpChannel->ucGptChannelMode)
          {
            /* Set the TGC bese register */
            LpATOMnAGCUnitRegs = LpClusterConfig->pGtmTomAtomClusterRegs;                                               /* PRQA S 0317 # JV-01 */
            /* Stop Counter */
            LpATOMnAGCUnitRegs->ulATOMnAGCENDISSTAT =
                      ~(((Gpt_ATOMChannelConfigType*)LpChannel->pHWIPChannelConfig)->ulCounterStartMaskValue);          /* PRQA S 0311, 0316 # JV-01, JV-01 */
            /* Disable Interrupt */
            LpATOMnCHmUnitRegs->ulATOMnCHmIRQEN = GPT_DISABLEGTMCHmIRQEN;
            /* Assign the timer status to the One-shot Channel */
            Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].ucChannelStatus = GPT_CH_EXPIRED;
          } /* No action required */
          #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
          /* Invoke callback notification if notification is enabled */
          if (GPT_TRUE == Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)].blNotifyStatus)
          {
            if (NULL_PTR != LpChannel->pGptNotificationPointer)
            {
              /* Clear the interrupt flag */
              LpATOMnCHmUnitRegs->ulATOMnCHmIRQNOTIFY = GPT_CLEAR_INTERRUPT_GTM;
              /* Invoke the callback function */
              LpChannel->pGptNotificationPointer();
            } /* No action required*/
          } /* No action required*/
          #endif /* End of (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON) */
        } /* No action required*/
        #endif
      } /* No action required*/
    } /* No action required */
    #if (GPT_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  }
  #endif
} /* End of API Gpt_HW_Gtm_CbkNotification */

#define GPT_STOP_SEC_CODE_FAST
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* End of ((GPT_TOM_UNIT_USED == STD_ON) || (GPT_ATOM_UNIT_USED == STD_ON)) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_StartPredefTimer
**
** Service ID            : NA
**
** Description           : This function starts for the hardware channel used by PreDef Timer function
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
** Global Variables used : Gpt_GpPredefTimerConfig
**
** Functions invoked     : None
**
** Registers used        : TOM[i]_TGC[g]_GLB_CTRL, TOM[i]_TGC[g]_ENDIS_CTRL, TOM[i]_CH[x]_SR0, TOM[i]_CH[x]_SR1
**                         TOM[i]_CH[x]_CM0, TOM[i]_CH[x]_CM1, TOM[i]_CH[x]_CTRL, TOM[i]_CH[x]_CN0, TOM[i]_CH[x]_IRQ_EN
**                         TOM[i]_TGC[g]_ENDIS_STAT, TOM[i]_CH[x]_CTRL_SR
**                         ATOM[i]_AGC_GLB_CTRL, ATOM[i]_AGC_ENDIS_CTRL, ATOM[i]_CH[x]_SR0, ATOM[i]_CH[x]_SR1
**                         ATOM[i]_CH[x]_CM0, ATOM[i]_CH[x]_CM1, ATOM[i]_CH[x]_CN0, ATOM[i]_CH[x]_CTRL
**                         ATOM[i]_CH[x]_CTRL_SR, ATOM[i]_CH[x]_IRQ_EN, ATOM[i]_AGC_ENDIS_STAT
**
** Reference ID          : GPT_DUD_ACT_084
** Reference ID          : GPT_DUD_ACT_084_REG001, GPT_DUD_ACT_084_REG002, GPT_DUD_ACT_084_REG003
** Reference ID          : GPT_DUD_ACT_084_REG004, GPT_DUD_ACT_084_REG005, GPT_DUD_ACT_084_REG006
** Reference ID          : GPT_DUD_ACT_084_REG007, GPT_DUD_ACT_084_REG008, GPT_DUD_ACT_084_REG009
** Reference ID          : GPT_DUD_ACT_084_REG010, GPT_DUD_ACT_084_REG011, GPT_DUD_ACT_084_REG012
** Reference ID          : GPT_DUD_ACT_084_REG013, GPT_DUD_ACT_084_REG014, GPT_DUD_ACT_084_REG015
** Reference ID          : GPT_DUD_ACT_084_REG016, GPT_DUD_ACT_084_REG017, GPT_DUD_ACT_084_REG018
** Reference ID          : GPT_DUD_ACT_084_REG019, GPT_DUD_ACT_084_REG020, GPT_DUD_ACT_084_REG021
** Reference ID          : GPT_DUD_ACT_084_REG022
***********************************************************************************************************************/
#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

void Gpt_HW_Gtm_StartPredefTimer(void)
{
  /* Pointer pointing to the TGC Unit registers */
  Gpt_TOMnTGCmUnitRegs* LpTOMnTGCmUnitRegs;
  /* Pointer pointing to the TOM Unit registers */
  Gpt_TOMnCHmUnitRegs* LpTOMnCHmUnitRegs;
  /* Pointer pointing to the AGC Unit registers */
  Gpt_ATOMnAGCUnitRegs* LpATOMnAGCUnitRegs;
  /* Pointer pointing to the ATOM Unit registers */
  Gpt_ATOMnCHmUnitRegs* LpATOMnCHmUnitRegs;
  /* Pointer pointing to the CCM Unit registers */
  uint8 ucPredefTimerType;
  ucPredefTimerType = \
      ((const Gpt_PredefTimerGTMChannelConfigType*) Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ucTomAtomTypeChannel;  /* PRQA S 0316 # JV-01 */
  /* Check which Type of PredefTimer */
  if (GPT_HW_TOM == ucPredefTimerType)
  {
    /* Load the Pointer for predef Timer channel */
    LpTOMnTGCmUnitRegs =  (Gpt_TOMnTGCmUnitRegs*)                                                                       /* PRQA S 0310 # JV-01 */
      ((const Gpt_PredefTimerGTMChannelConfigType*) Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->pPredefTimermUnitRegs; /* PRQA S 0316 # JV-01 */
    LpTOMnCHmUnitRegs = (Gpt_TOMnCHmUnitRegs*)                                                                          /* PRQA S 0310 # JV-01 */
      ((const Gpt_PredefTimerGTMChannelConfigType*)                                                                     /* PRQA S 0316 # JV-01 */
      Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->pPredefTimerChannelRegs;
    /* Enable Predef Timer */
    LpTOMnTGCmUnitRegs->ulTOMnTGCmGLBCTRL =
      ((const Gpt_PredefTimerGTMChannelConfigType*)                                                                     /* PRQA S 0316 # JV-01 */
      Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ucGtmTomATomClusterGlbCtrlRegVal;
    LpTOMnTGCmUnitRegs->ulTOMnTGCmENDISCTRL =
      ((const Gpt_PredefTimerGTMChannelConfigType*)                                                                     /* PRQA S 0316 # JV-01 */
      Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ulPredefTimerStartMaskValue;
    /* Initialized Compare shadow register 0 */
    LpTOMnCHmUnitRegs->ulTOMnCHmSR0 = GPT_DISABLETOMnCHmSR;
    /* Initialized Compare shadow register 1 */
    LpTOMnCHmUnitRegs->ulTOMnCHmSR1 = GPT_DISABLETOMnCHmSR;
    /* Initialized Compare register 0 */
    LpTOMnCHmUnitRegs->ulTOMnCHmCM0 = GPT_DISABLETOMnCHmCM;
    /* Initialized Compare register 1 */
    LpTOMnCHmUnitRegs->ulTOMnCHmCM1 = GPT_DISABLETOMnCHmCM;
    /* Reset counter value */
    LpTOMnCHmUnitRegs->ulTOMnCHmCN0 = GPT_RESET_GTM_COUNTER;
    /* Set control register for Continues Mode */
    LpTOMnCHmUnitRegs->ulTOMnCHmCTRL = GPT_TOM_PWM_MODE;
    /* Clear the clock select bit */
    LpTOMnCHmUnitRegs->ulTOMnCHmCTRL &= GPT_CLKSRCCLEARVALUE;
    /* Clock source select */
    LpTOMnCHmUnitRegs->ulTOMnCHmCTRL |= ((const Gpt_PredefTimerGTMChannelConfigType*)                                   /* PRQA S 0316 # JV-01 */
                                          Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ulPredefTimerClockselectValue;
    #if(GPT_GTM_VERSION == GPT_GTM_410_VERSION)
    /* Clear the clock select bit */
    LpTOMnCHmUnitRegs->ulTOMnCHmCTRLSR &= GPT_CLKSRCCLEARVALUE;
    /* Clock source select */
    LpTOMnCHmUnitRegs->ulTOMnCHmCTRLSR |= ((const Gpt_PredefTimerGTMChannelConfigType*)                                 /* PRQA S 0316 # JV-01 */
                                          Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ulPredefTimerClockselectValue;
    #endif
    /* Disable Interrupt */
    LpTOMnCHmUnitRegs->ulTOMnCHmIRQEN = GPT_DISABLEGTMCHmIRQEN;
    /* Start the Predef Timer */
    LpTOMnTGCmUnitRegs->ulTOMnTGCmENDISSTAT = ((const Gpt_PredefTimerGTMChannelConfigType*)                             /* PRQA S 0316 # JV-01 */
                                            Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ulPredefTimerStartMaskValue;
  }
  else /* (GPT_HW_ATOM == Gpt_GpPredefTimerConfig->ucPredefTimerType) */
  {
    /* Load the Pointer for predef Timer channel */
    LpATOMnAGCUnitRegs = (Gpt_ATOMnAGCUnitRegs*)                                                                        /* PRQA S 0310 # JV-01 */
      ((const Gpt_PredefTimerGTMChannelConfigType*) Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->pPredefTimermUnitRegs; /* PRQA S 0316 # JV-01 */
    LpATOMnCHmUnitRegs = (Gpt_ATOMnCHmUnitRegs*)                                                                        /* PRQA S 0310 # JV-01 */
     ((const Gpt_PredefTimerGTMChannelConfigType*) Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->pPredefTimerChannelRegs;/* PRQA S 0316 # JV-01 */
    /* Enable Predef Timer */
    LpATOMnAGCUnitRegs->ulATOMnAGCGLBCTRL =
      ((const Gpt_PredefTimerGTMChannelConfigType*)                                                                     /* PRQA S 0316 # JV-01 */
      Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ucGtmTomATomClusterGlbCtrlRegVal;
    LpATOMnAGCUnitRegs->ulATOMnAGCENDISCTRL =
      ((const Gpt_PredefTimerGTMChannelConfigType*)                                                                     /* PRQA S 0316 # JV-01 */
      Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ulPredefTimerStartMaskValue;
    /* Initialized Compare shadow register 0 */
    LpATOMnCHmUnitRegs->ulATOMnCHmSR0 = GPT_DISABLEATOMnCHmSR;
    /* Initialized Compare shadow register 1 */
    LpATOMnCHmUnitRegs->ulATOMnCHmSR1 = GPT_DISABLEATOMnCHmSR;
    /* Initialized Compare register 0 */
    LpATOMnCHmUnitRegs->ulATOMnCHmCM0 = GPT_DISABLEATOMnCHmCM;
    /* Initialized Compare register 1 */
    LpATOMnCHmUnitRegs->ulATOMnCHmCM1 = GPT_DISABLEATOMnCHmCM;
    /* Reset counter value */
    LpATOMnCHmUnitRegs->ulATOMnCHmCN0 = GPT_RESET_GTM_COUNTER;
    /* Set control register for Continues Mode */
    LpATOMnCHmUnitRegs->ulATOMnCHmCTRL = GPT_ATOM_PWM_MODE;
    /* Clear the clock select bit */
    LpATOMnCHmUnitRegs->ulATOMnCHmCTRL &= GPT_CLKSRCCLEARVALUE;
    /* Clock source serect */
    LpATOMnCHmUnitRegs->ulATOMnCHmCTRL |= ((const Gpt_PredefTimerGTMChannelConfigType*)                                 /* PRQA S 0316 # JV-01 */
                                          Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ulPredefTimerClockselectValue;
    #if(GPT_GTM_VERSION == GPT_GTM_410_VERSION)
    /* Clear the clock select bit in shadow register */
    LpATOMnCHmUnitRegs->ulATOMnCHmCTRLSR &= GPT_CLKSRCCLEARVALUE;
    /* Clock source serect in shadow register */
    LpATOMnCHmUnitRegs->ulATOMnCHmCTRLSR |= ((const Gpt_PredefTimerGTMChannelConfigType*)                               /* PRQA S 0316 # JV-01 */
                                          Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ulPredefTimerClockselectValue;
    #endif
    /* Disable Interrupt */
    LpATOMnCHmUnitRegs->ulATOMnCHmIRQEN = GPT_DISABLEGTMCHmIRQEN;
    /* Start the Predef Timer */
    LpATOMnAGCUnitRegs->ulATOMnAGCENDISSTAT = ((const Gpt_PredefTimerGTMChannelConfigType*)                             /* PRQA S 0316 # JV-01 */
                                            Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ulPredefTimerStartMaskValue;
  }
  /* End of (GPT_HW_TOM == Gpt_GpPredefTimerConfig->ucPredefTimerType) */
}/* End of API Gpt_HW_Gtm_StartPredefTimer */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_StopPredefTimer
**
** Service ID            : NA
**
** Description           : This function stops for the hardware channel used by PreDef Timer function
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
** Global Variables used : Gpt_GpPredefTimerConfig
**
** Functions invoked     : None
**
** Registers used        : TOM[i]_TGC[g]_GLB_CTRL, ATOM[i]_AGC_GLB_CTRL
**
** Reference ID          : GPT_DUD_ACT_085
** Reference ID          : GPT_DUD_ACT_085_REG001, GPT_DUD_ACT_085_REG002
***********************************************************************************************************************/
#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

void Gpt_HW_Gtm_StopPredefTimer(void)
{
  /* Pointer pointing to the TGC Unit registers */
  Gpt_TOMnTGCmUnitRegs* LpTOMnTGCmUnitRegs;
  /* Pointer pointing to the AGC Unit registers */
  Gpt_ATOMnAGCUnitRegs* LpATOMnAGCUnitRegs;
  /* Check which Type of PredefTimer */
  uint8 ucPredefTimerType;
  ucPredefTimerType =
      ((const Gpt_PredefTimerGTMChannelConfigType*) Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ucTomAtomTypeChannel;  /* PRQA S 0316 # JV-01 */
  if (GPT_HW_TOM == ucPredefTimerType)
  {
    /* Load the Pointer for predef Timer channel */
    LpTOMnTGCmUnitRegs = (Gpt_TOMnTGCmUnitRegs*)                                                                        /* PRQA S 0310 # JV-01 */
    ((const Gpt_PredefTimerGTMChannelConfigType*) Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->pPredefTimermUnitRegs;   /* PRQA S 0316 # JV-01 */
    /* Stop the Predef Timer */
    LpTOMnTGCmUnitRegs->ulTOMnTGCmGLBCTRL =
                    GPT_UPPER_16BIT_CLEAR_MASK & ((const Gpt_PredefTimerGTMChannelConfigType*)                          /* PRQA S 0316 # JV-01 */
                    Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ucGtmTomATomClusterGlbCtrlRegVal;
  }
  else /* (GPT_HW_ATOM == Gpt_GpPredefTimerConfig->ucPredefTimerType */
  {
    /* Load the Pointer for predef Timer channel */
    LpATOMnAGCUnitRegs = (Gpt_ATOMnAGCUnitRegs*)                                                                        /* PRQA S 0310 # JV-01 */
    ((const Gpt_PredefTimerGTMChannelConfigType*) Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->pPredefTimermUnitRegs;   /* PRQA S 0316 # JV-01 */
    /* Stop the Predef Timer */
    LpATOMnAGCUnitRegs->ulATOMnAGCGLBCTRL = GPT_UPPER_16BIT_CLEAR_MASK
                    & ((const Gpt_PredefTimerGTMChannelConfigType*)                                                     /* PRQA S 0316 # JV-01 */
                    Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ucGtmTomATomClusterGlbCtrlRegVal;
  }
  /* End of  (GPT_HW_TOM == LucPredefTimerType) */
}/* End of API Gpt_HW_Gtm_StopPredefTimer */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_HW_Gtm_GetPredefTimerValue
**
** Service ID            : NA
**
** Description           : This function is used to get the Gpt PredefTimer
**                         value for the current value of the desired Gpt
**                         PredefTimer.
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
** Return Value          : E_OK or E_NOT_OK
**
** Pre-condition         : None
**
** Global Variable(s)    : Gpt_GpPredefTimerConfig
**
** Functions invoked     : SchM_Enter_Gpt_##Exclusive_Area(), SchM_Exit_Gpt_##Exclusive_Area()
**
** Registers Used        : TOMnCHmCN0, ATOMnCHmCN0
**
** Reference ID          : GPT_DUD_ACT_086
** Reference ID          : GPT_DUD_ACT_086_CRT001, GPT_DUD_ACT_086_CRT002
** Reference ID          : GPT_DUD_ACT_086_ERR001
***********************************************************************************************************************/
#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

Std_ReturnType Gpt_HW_Gtm_GetPredefTimerValue (Gpt_PredefTimerType LddPredefTimer, uint32* LpTimerValuePtr)
{
  /* Variable to hold return value */
  Std_ReturnType LucReturnValue;
  /* variable to get predef timer value */
  uint32 LulPredefTimerValue;
  /* Set to initialize value */
  LucReturnValue = E_OK;
  /* Check which Type of PredefTimer */
  uint8 ucPredefTimerType;
  ucPredefTimerType = \
      ((const Gpt_PredefTimerGTMChannelConfigType*) Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->ucTomAtomTypeChannel;  /* PRQA S 0316 # JV-01 */
  /* Check which Type of PredefTimer */
  if ((uint8)GPT_HW_TOM == ucPredefTimerType)
  {
    /* Checking required predef timer counter type */
    if (GPT_PREDEF_TIMER_1US_16BIT != LddPredefTimer)
    {
      LucReturnValue = E_NOT_OK;
    } /* No action required */
  }
  else /* (GPT_HW_ATOM == Gpt_GpPredefTimerConfig->ucPredefTimerType) */
  {
    /* Checking required predef timer counter type */
    if ((GPT_PREDEF_TIMER_1US_16BIT != LddPredefTimer) && (GPT_PREDEF_TIMER_1US_24BIT != LddPredefTimer))
    {
      LucReturnValue = E_NOT_OK;
    } /* No action required */
  }
  if (LucReturnValue == E_OK)                                                                                           /* PRQA S 2991, 2995 # JV-01, JV-01 */
  {
    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enter Protected area  */
    GPT_ENTER_CRITICAL_SECTION(GPT_RAM_DATA_PROTECTION_GLOBAL);
    #endif
    /* Get PredefTimer Value*/
    LulPredefTimerValue =
  *(((const Gpt_PredefTimerGTMChannelConfigType*) Gpt_GpPredefTimerConfig->pPT_ChannelConfig)->pPredefTimerCounterReg); /* PRQA S 0316 # JV-01 */

    /* Checking Predef Timer need to masking upper bit */
    if (GPT_PREDEF_TIMER_1US_16BIT == LddPredefTimer)
    {
      LulPredefTimerValue &= (uint32)GPT_UPPER_16BIT_CLEAR_MASK;
    } /* No action required */
    /* Set PredefTimer Value*/
    *LpTimerValuePtr = LulPredefTimerValue;
    #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Exit Protected area */
    GPT_EXIT_CRITICAL_SECTION(GPT_RAM_DATA_PROTECTION_GLOBAL);
    #endif
  }
  else
  {
    #if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET module */
    (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_PREDEFTIMRVALUE_SID, GPT_E_PARAM_PREDEF_TIMER);       /* PRQA S 2880 # JV-01 */
    #endif /* End of GPT_DEV_ERROR_DETECT == STD_ON */
  }
  return (LucReturnValue);
} /* End of API Gpt_HW_Gtm_GetPredefTimerValue */

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON) */

#endif /* GPT_TIMER_IP_GTM == STD_ON */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
