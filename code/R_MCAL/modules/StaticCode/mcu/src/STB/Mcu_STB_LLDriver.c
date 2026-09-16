/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_STB_LLDriver.c                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 * 2.1.1:  30/09/2024   : As part of ARDAACJ-595 (ARDAACL-50520), following changes are made:
 *                        - Update function Mcu_STBSetMode to stop DMON and stop CLMA before CPU System Clock Setting
 *                        in case MCU_DEEPSTOP_MODE
 *         30/08/2024   : Update SW-VERSION to 2.1.1
 *                        As part of U2Cx device support, following changes are made:
 *                        - Update function Mcu_STBSetMode to set RRAM_SDM and AWOPSM register in case MCU_DEEPSTOP_MODE
 * 2.0.1:  10/10/2023   : Update function Mcu_STBSetMode to set Power Good Counter Register in case MCU_DEEPSTOP_MODE
 * 2.0.0:  04/08/2023   : Add QAC message 0857, 1006, 2963, 2844
 *                        Remove redundant QAC message 0857, 0791
 *         10/07/2023   : Remove redundant QAC message 0857, 0303
 *         21/04/2023   : Reduce STCYC <=20 for API Mcu_STBSetMode
 * 1.5.0:  28/03/2023   : Remove 'if' statement when MOSC stop operation in chip standby mode.
 * 1.4.5:  01/02/2023   : Initial Version as new Mcu Structure
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
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : MISRA C:2012 Rule-18.4, CERTCCM EXP08, CWE Rule CWE-188, CWE-398, CWE-569                    */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0686)    : Array has fewer initializers than its declared size. Default initialization is applied to    */
/*                       the remainder of the array elements.                                                         */
/* Rule                : MISRA C:2012 Rule-9.3, CWE Rule CWE-665, CWE-452                                             */
/* JV-01 Justification : This initialization to avoid passing address of uninitialized object. This can be accepted.  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : This in-line assembler construct is a language extension. The code has been ignored.         */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTCCM MSC14                                       */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object '%1s' is only referenced in the translation unit where it is defined.             */
/* Rule                : MISRA C:2012 Rule-8.7, CERTCCM DCL15, DCL19, CWE Rule CWE-398, CWE-569                       */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
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
/* Message (3:3387)    : A full expression containing an increment (++) or decrement (--) operator should have no     */
/*                       potential side effects other than that caused by the increment or decrement operator.        */
/* Rule                : MISRA C:2012 Rule-13.3                                                                       */
/* JV-01 Justification : An increment/decrement is created as a side effect. In this case, it's accessing a volatile  */
/*                       object. This can be accepted.                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : '%s' has external linkage and is being defined without any previous declaration.             */
/* Rule                : MISRA C:2012 Rule-8.4, CERTCCM DCL07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
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
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for module version information */
#include "Mcu.h"

/* Included for RAM variable declarations */
#include "Mcu_Ram.h"

#include "Dem.h"

#include "Det.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define MCU_STB_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    MCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define MCU_STB_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    MCU_AR_RELEASE_MINOR_VERSION_VALUE
#define MCU_STB_LLDRIVER_C_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MCU_STB_LLDRIVER_C_SW_MAJOR_VERSION            MCU_SW_MAJOR_VERSION_VALUE
#define MCU_STB_LLDRIVER_C_SW_MINOR_VERSION            MCU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (MCU_STB_LLDRIVER_AR_RELEASE_MAJOR_VERSION != MCU_STB_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "MCU_STB_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (MCU_STB_LLDRIVER_AR_RELEASE_MINOR_VERSION != MCU_STB_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "MCU_STB_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (MCU_STB_LLDRIVER_AR_RELEASE_REVISION_VERSION != MCU_STB_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "MCU_STB_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (MCU_STB_LLDRIVER_SW_MAJOR_VERSION != MCU_STB_LLDRIVER_C_SW_MAJOR_VERSION)
#error "MCU_STB_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (MCU_STB_LLDRIVER_SW_MINOR_VERSION != MCU_STB_LLDRIVER_C_SW_MINOR_VERSION)
#error "MCU_STB_LLDriver.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

#if (MCU_DEV_ERROR_DETECT == STD_ON)
#define MCU_START_SEC_VAR_INIT_8
#include "Mcu_MemMap.h"
/* Golbal variable to store status of wake up setting of MCU Driver */
volatile VAR(uint8, MCU_VAR_INIT) Mcu_GucStopModeWakeUpStatus = MCU_NO_WAKEUP_SET;                                      /* PRQA S 1504, 3408 # JV-01, JV-01 */
volatile VAR(uint8, MCU_VAR_INIT) Mcu_GucCylicStopModeWakeUpStatus = MCU_NO_WAKEUP_SET;                                 /* PRQA S 1504, 3408 # JV-01, JV-01 */
volatile VAR(uint8, MCU_VAR_INIT) Mcu_GucDeepStopModeWakeUpStatus = MCU_NO_WAKEUP_SET;                                  /* PRQA S 1504, 3408 # JV-01, JV-01 */
#define MCU_STOP_SEC_VAR_INIT_8
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

/**********************************************************************************************************************/
/**                                             Internal Function Prototypes                                         **/
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name      : Mcu_STBSetMode
**
** Service ID         : None
**
** Description        : This service activates the MCU power modes.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Reentrant
**
** Input Parameters   : LddMode - Id for power mode setting
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GpConfigPtr, Mcu_GucStopModeWakeUpStatus, Mcu_GucCylicStopModeWakeUpStatus
**                      Mcu_GucDeepStopModeWakeUpStatus, Mcu_GpClockSetting
**
** Function Invoked   : Det_ReportError, Mcu_VMNStopDelayMonitor, Mcu_CLMStop, Mcu_CLMRestart, 
**                      Mcu_VMNRestartDelayMonitor, Mcu_CLKShiftCpuSys
**
** Registers Used     : CKSC_CPUS, CLKD_PLLC, CLKD_PLLS, MOSCS, STBCKCPROT, STBC0STPT, STBC0PSC, PWRGD_CNT
**
** Reference ID       : MCU_DUD_ACT_071, MCU_DUD_ACT_071_ERR001, MCU_DUD_ACT_071_ERR002, MCU_DUD_ACT_071_ERR003
** Reference ID       : MCU_DUD_ACT_071_ERR004, MCU_DUD_ACT_071_ERR005, MCU_DUD_ACT_071_REG001, MCU_DUD_ACT_071_REG002
** Reference ID       : MCU_DUD_ACT_071_REG003, MCU_DUD_ACT_071_REG004, MCU_DUD_ACT_071_REG005, MCU_DUD_ACT_071_REG006
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_STBSetMode(Mcu_ModeType LddMode)                                                       /* PRQA S 3006 # JV-01 */
{
  P2CONST(Mcu_ModeSettingType, MCU_VAR_NO_INIT, MCU_CONFIG_CONST) LpModeSetting;
  Mcu_StandbyModeType LenMode;

  #if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
  volatile uint32 LulCount;
  uint8 LucClockStatus;
  uint8 LucModeTransitionStatus;
  uint32 aaCKSSBeforeValue[MCU_CLK_SRC_NUM] = {MCU_ZERO};                                                               /* PRQA S 0686 # JV-01 */
  uint32 aaCLKDCBeforeValue[MCU_CLK_SRC_NUM] = {MCU_ZERO};                                                              /* PRQA S 0686 # JV-01 */
  #if (MCU_CLMA_OPERATION == STD_ON)
  uint32 LulMOSCSBeforeValue;
  uint32 aaCLKDSBeforeValue[MCU_CLK_SRC_NUM] = {MCU_ZERO};                                                              /* PRQA S 0686 # JV-01 */
  #endif /* MCU_CLMA_OPERATION == STD_ON */
  uint8 LucIndex;
  P2CONST(Mcu_ClockShiftSettingType, MCU_CONST, MCU_CONFIG_DATA) LpClockShiftSetting;
  P2CONST(Mcu_ClockModeSettingType, AUTOMATIC, MCU_CONFIG_DATA) LpClockModeSetting;

  /* Set initial status for mode transition */
  LulCount = (uint32)MCU_MODE_TRANSITION_WAIT_CNT_NUM;
  LucModeTransitionStatus = E_OK;
  LucClockStatus = E_OK;
  LpClockShiftSetting = Mcu_GpClockSetting->pClockShiftSetting;
  LpClockModeSetting = Mcu_GpClockSetting->pClockModeSetting;

  #if (MCU_CLMA_OPERATION == STD_ON)
  /* Get status of clock source before enter to standby mode */
  LulMOSCSBeforeValue = (*Mcu_GpClockHwInfo->pMainOscSReg & MCU_MOSCS_CLK_STABLE);                                      /* PRQA S 0404 # JV-01 */
  #endif /* MCU_CLMA_OPERATION == STD_ON */

  for (LucIndex = MCU_ZERO; LucIndex < Mcu_GpClockHwInfo->ucNoOfClkSrc; LucIndex++)
  {
    /* Get current system clock source */
    aaCKSSBeforeValue[LucIndex] = *(LpClockModeSetting[LucIndex].pCKSSAddr) & MCU_CKSC_MASK;
    /* Get the current system clock divider control */
    aaCLKDCBeforeValue[LucIndex] = *(LpClockModeSetting[LucIndex].pCLKDCAddr) & MCU_CKDC_MASK;
    #if (MCU_CLMA_OPERATION == STD_ON)
    /* Get the current system clock divider status */
    aaCLKDSBeforeValue[LucIndex] = *(LpClockModeSetting[LucIndex].pCLKDSAddr) & MCU_CKDS_SYNCMASK;
    #endif /* MCU_CLMA_OPERATION == STD_ON */
  }
  #endif /* MCU_MODE_TRANSITION_SUPPORT == STD_ON */

  LpModeSetting =
  ((P2CONST(Mcu_ModeSettingType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))(Mcu_GpConfigPtr->pModeSetting) + LddMode);          /* PRQA S 0316, 0488 # JV-01, JV-01 */

  /* Get the value of selected mode type */
  LenMode = LpModeSetting->enModeType;

  #if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  if (((MCU_STOP_WAKEUP_SET != Mcu_GucStopModeWakeUpStatus) && (MCU_STOP_MODE == LenMode)) ||                           /* PRQA S 3416 # JV-01 */
      ((MCU_CYCLICSTOP_WAKEUP_SET != Mcu_GucCylicStopModeWakeUpStatus) && (MCU_CYCLICSTOP_MODE == LenMode)) ||          /* PRQA S 3415, 3416 # JV-01, JV-01 */
      ((MCU_DEEPSTOP_WAKEUP_SET != Mcu_GucDeepStopModeWakeUpStatus) && (MCU_DEEPSTOP_MODE == LenMode)))                 /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_SETMODE_SID, MCU_E_INVALID_MODE_SEQUENCE);
  }
  else
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  #endif /* MCU_MODE_TRANSITION_SUPPORT == STD_ON */
  {
    switch (LenMode)
    {
    case MCU_HALT_MODE:
      ASM_HALT();                                                                                                       /* PRQA S 1006 # JV-01 */
      break;
    #if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
    case MCU_STOP_MODE:
    case MCU_CYCLICSTOP_MODE:
      #if (MCU_DMON_DIAG_OPERATION == STD_ON)
      /* STOP DMON */
      Mcu_VMNStopDelayMonitor();
      #endif /* MCU_DMON_DIAG_OPERATION == STD_ON */

      #if (MCU_CLMA_OPERATION == STD_ON)
      /* STOP CLMA3-9 */
      Mcu_CLMStop();
      #endif /* MCU_CLMA_OPERATION == STD_ON */
      for (LucIndex = MCU_ZERO; LucIndex < Mcu_GpClockHwInfo->ucNoOfClkSrc; LucIndex++)
      {
        /*
         * CLK_PLLO is selected as the clock source for the System clock,
         * and No division is selected as the division ratio of clock source PLL.
         */
        if ((MCU_CKSC_PLLO == aaCKSSBeforeValue[LucIndex]) && (MCU_CKDC_DIV1 == aaCLKDCBeforeValue[LucIndex]))
        {
          /* System clock gear down before standby mode */
          LucClockStatus = Mcu_CLKShiftCpuSys(MCU_STANDBY_MODE, LucIndex, MCU_CLK_GEAR_DOWN, LpClockShiftSetting);
        } /* else No action is required */
      }

      if (E_NOT_OK == LucClockStatus)
      {
        #ifdef MCU_E_CLOCK_FAILURE
        /* Report to DEM */
        /* Clock Source is Failed. */
        MCU_DEM_REPORT_ERROR(MCU_E_CLOCK_FAILURE, DEM_EVENT_STATUS_FAILED);
        #endif /* MCU_E_CLOCK_FAILURE */
      }
      else
      {
        /* Access Protection Disable */
        *Mcu_GpStbHwInfo->pSTBCKCPROTReg = MCU_STB_DISABLE_REG_PROTECT_VALUE;
        /* Transition to STOP */
        *Mcu_GpStbHwInfo->pSTBC0STPTReg = MCU_STBC0STPT_TRANSITION_TO_STOP_VALUE;
        /* Access Protection Enable */
        *Mcu_GpStbHwInfo->pSTBCKCPROTReg = MCU_STB_ENABLE_REG_PROTECT_VALUE;

        while (((*Mcu_GpStbHwInfo->pSTBC0STPTReg) == MCU_STBC0STPT_TRANSITION_TO_STOP_VALUE)                            /* PRQA S 0404 # JV-01 */
                && (LulCount > (uint32)MCU_ZERO))                                                                       /* PRQA S 3415, 3416 # JV-01, JV-01 */
        {
          LulCount--;                                                                                                   /* PRQA S 3384, 3387 # JV-01, JV-01 */
          EXECUTE_SYNCP();                                                                                              /* PRQA S 1006 # JV-01 */
        }
        /* Check if wait time is out and can not transition to standby mode */
        if (LulCount <= (uint32)MCU_ZERO)                                                                               /* PRQA S 3416 # JV-01 */
        {
          LucModeTransitionStatus = E_NOT_OK;
        } /* else No action is required */

        /* Return to RUN mode at the generation of wakeup factor */
        if (E_OK == LucModeTransitionStatus)
        {
          for (LucIndex = MCU_ZERO; LucIndex < Mcu_GpClockHwInfo->ucNoOfClkSrc; LucIndex++)
          {
            if ((MCU_CKSC_PLLO == aaCKSSBeforeValue[LucIndex]) && (MCU_CKDC_DIV1 == aaCLKDCBeforeValue[LucIndex]))
            {
              /* System clock gear up after wake up */
              LucClockStatus = Mcu_CLKShiftCpuSys(MCU_STANDBY_MODE, LucIndex, MCU_CLK_GEAR_UP, LpClockShiftSetting);
            } /* else No action is required */
          }

          #if (MCU_CLMA_OPERATION == STD_ON)
          if ((E_OK == LucClockStatus) && (MCU_ZERO != Mcu_GpClockSetting->ucNoOfClm))                                  /* PRQA S 3415, 3416 # JV-01, JV-01 */
          {
            /* Restart CLMA */
            LucClockStatus = Mcu_CLMRestart(LulMOSCSBeforeValue, aaCKSSBeforeValue, aaCLKDSBeforeValue);
          } /* else No action is required */
          #endif /* MCU_CLMA_OPERATION == STD_ON */

          #if (MCU_DMON_DIAG_OPERATION == STD_ON)
          if (E_OK == LucClockStatus)
          {
            /* Restart DMON */
            Mcu_VMNRestartDelayMonitor();
          } /* else No action is required */
          #endif /* MCU_DMON_DIAG_OPERATION == STD_ON */
        }
        else
        {
          /* Mode transition failed */
          #ifdef MCU_E_MODE_TRANSITION_FAILURE
          MCU_DEM_REPORT_ERROR(MCU_E_MODE_TRANSITION_FAILURE, DEM_EVENT_STATUS_FAILED);
          #endif /* MCU_E_MODE_TRANSITION_FAILURE */
        }
      }
      break;
    case MCU_DEEPSTOP_MODE:
      #if (MCU_DMON_DIAG_OPERATION == STD_ON)
      /* STOP DMON */
      Mcu_VMNStopDelayMonitor();
      #endif /* MCU_DMON_DIAG_OPERATION == STD_ON */

      #if (MCU_CLMA_OPERATION == STD_ON)
      /* STOP CLMA3-9 */
      Mcu_CLMStop();
      #endif /* MCU_CLMA_OPERATION == STD_ON */
      for (LucIndex = MCU_ZERO; LucIndex < Mcu_GpClockHwInfo->ucNoOfClkSrc; LucIndex++)
      {
        /*
         * CLK_PLLO is selected as the clock source for the System clock,
         * and No division is selected as the division ratio of clock source PLL.
         */
        if ((MCU_CKSC_PLLO == aaCKSSBeforeValue[LucIndex]) && (MCU_CKDC_DIV1 == aaCLKDCBeforeValue[LucIndex]))
        {
          /* System clock gear down before standby mode */
          LucClockStatus = Mcu_CLKShiftCpuSys(MCU_STANDBY_MODE, LucIndex, MCU_CLK_GEAR_DOWN, LpClockShiftSetting);
        } /* else No action is required */
      }

      if (E_NOT_OK == LucClockStatus)
      {
        #ifdef MCU_E_CLOCK_FAILURE
        /* Report to DEM */
        /* Clock Source is Failed. */
        MCU_DEM_REPORT_ERROR(MCU_E_CLOCK_FAILURE, DEM_EVENT_STATUS_FAILED);
        #endif /* MCU_E_CLOCK_FAILURE */
      }
      else
      {
        #if (MCU_POWER_SUPPLY_MODE_SELECTION == STD_ON)
        /* Access Protection Disable */
        *Mcu_GpStbHwInfo->pSTBCKCPROTReg = MCU_STB_DISABLE_REG_PROTECT_VALUE;

        /* Select the power supply mode of AWOVDD */
        *Mcu_GpStbHwInfo->pAWOPSMReg = (uint32)MCU_POWER_SUPPLY_MODE_VALUE;

        /* Access Protection Enable */
        *Mcu_GpStbHwInfo->pSTBCKCPROTReg = MCU_STB_ENABLE_REG_PROTECT_VALUE;
        #endif /* MCU_POWER_SUPPLY_MODE_SELECTION == STD_ON */

        #if (MCU_SHUT_DOWN_SELECTION == STD_ON)
        /* Access Protection Disable */
        *Mcu_GpStbHwInfo->pSTBCKCPROTReg = MCU_STB_DISABLE_REG_PROTECT_VALUE;

        /* Select the RetentionRAM shutdown mode during DeepSTOP */
        *Mcu_GpStbHwInfo->pRRAM_SDMReg = (uint32)MCU_SELECT_SHUTDOWN_MODE_VALUE;

        /* Access Protection Enable */
        *Mcu_GpStbHwInfo->pSTBCKCPROTReg = MCU_STB_ENABLE_REG_PROTECT_VALUE;
        #endif /* MCU_SHUT_DOWN_SELECTION == STD_ON */

        /* Access Protection Disable */
        *Mcu_GpStbHwInfo->pSTBCKCPROTReg = MCU_STB_DISABLE_REG_PROTECT_VALUE;

        /* Set PWRGD_CNT */
        #ifdef MCU_POWER_GOOD_COUNTER_VALUE
        *Mcu_GpStbHwInfo->pPWRGD_CNTReg = (uint32)MCU_POWER_GOOD_COUNTER_VALUE;
        #endif

        /* Transition to DeepSTOP */
        *Mcu_GpStbHwInfo->pSTBC0PSCReg = MCU_STBC0PSC_TRANSITION_TO_DEEPSTOP_VALUE;

        /* Access Protection Enable */
        *Mcu_GpStbHwInfo->pSTBCKCPROTReg = MCU_STB_ENABLE_REG_PROTECT_VALUE;

        LulCount = (uint32)MCU_MODE_TRANSITION_WAIT_CNT_NUM;
        do
        {
          LulCount--;                                                                                                   /* PRQA S 3384, 3387 # JV-01, JV-01 */
          EXECUTE_SYNCP();                                                                                              /* PRQA S 1006 # JV-01 */
        }
        while (((*Mcu_GpStbHwInfo->pSTBC0PSCReg) == MCU_STBC0PSC_TRANSITION_TO_DEEPSTOP_VALUE)                          /* PRQA S 0404 # JV-01 */
                && (LulCount > (uint32)MCU_ZERO));                                                                      /* PRQA S 3415, 3416 # JV-01, JV-01 */
        /* If wait time is out and can not transition to standby mode, report DEM error */
        #ifdef MCU_E_MODE_TRANSITION_FAILURE
        /* Report to DEM */
        /* Mode transition is Failed. */
        MCU_DEM_REPORT_ERROR(MCU_E_MODE_TRANSITION_FAILURE, DEM_EVENT_STATUS_FAILED);
        #endif /* MCU_E_MODE_TRANSITION_FAILURE */
      }
      break;
    #endif /* MCU_MODE_TRANSITION_SUPPORT == STD_ON */
    default:
      /* No action required */
      break;
    }
  }
  return;
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_STBClearWakeUpFactor
**
** Service ID         : None
**
** Description        : This service to clear wakeup factor
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : WUFC0_A0, WUFC0_A1, WUFC0_A2, WUFC1_A0, WUFC1_A1, WUFC1_A2, WUFC0_I0, WUFC0_I1, WUFC0_I0,
**                      WUFC1_I0, WUFC0_I1.
**
** Reference ID       : MCU_DUD_ACT_073, MCU_DUD_ACT_073_REG001
** Reference ID       : MCU_DUD_ACT_073_CRT001, MCU_DUD_ACT_073_CRT002
***********************************************************************************************************************/
#if (MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_STBClearWakeUpFactor (void)
{
  P2CONST(volatile Mcu_WakeUpHwInfoType, TYPEDEF, REGSPACE) LpWakeUpReg;
  uint8 LucCount;
  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  /* Set WUFC0_Ax/WUFC1_Ax */
  for(LucCount = MCU_ZERO; LucCount < MCU_NUMBER_WAKEUP_FACTOR; LucCount++)
  {
    LpWakeUpReg = &Mcu_GpWakeUpHwInfo[LucCount];
    *LpWakeUpReg->pWUFCRegsAddr = MCU_CLEAR_WAKE_UP_FACTOR;
  }
  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_STBSetWakeUpFactor
**
** Service ID         : None
**
** Description        : This service to set wakeup factor
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LddMode
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GpConfigPtr, Mcu_GucStopModeWakeUpStatus, Mcu_GucCylicStopModeWakeUpStatus,
**                      Mcu_GucDeepStopModeWakeUpStatus
**
** Function Invoked   : Det_ReportError
**
** Registers Used     : WUFMSK0_A0, WUFMSK0_A1, WUFMSK0_A2, WUFMSK1_A0, WUFMSK1_A1, WUFMSK1_A2, WUFMSK0_I0, WUFMSK0_I1,
**                      WUFMSK1_I0, WUFMSK1_I1, WUFMSK0_I2, WUFMSK0_I3, WUFMSK1_I2, WUFMSK1_I3
**
** Reference ID       : MCU_DUD_ACT_074, MCU_DUD_ACT_074_REG001
** Reference ID       : MCU_DUD_ACT_074_ERR001,
** Reference ID       : MCU_DUD_ACT_074_CRT001,
** Reference ID       : MCU_DUD_ACT_074_CRT002
***********************************************************************************************************************/
#if (MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_STBSetWakeUpFactor (Mcu_ModeType LddMode)
{
  P2CONST(Mcu_ModeSettingType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) LpModeSetting;
  P2CONST(volatile Mcu_WakeUpHwInfoType, TYPEDEF, REGSPACE) LpWakeUpReg;
  Std_ReturnType LucReturnValue;
  uint8 LucCount;
  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  Mcu_StandbyModeType LenMode;
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */

  /* Initialize return value with E_OK */
  LucReturnValue = E_OK;

  /* Get the address to mode configuration structure */
  LpModeSetting = ((P2CONST(Mcu_ModeSettingType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))                                     /* PRQA S 0316 # JV-01 */
                  (Mcu_GpConfigPtr->pModeSetting) + LddMode);                                                           /* PRQA S 0488 # JV-01 */
  #if (MCU_DEV_ERROR_DETECT == STD_ON)
  LenMode = LpModeSetting->enModeType;
  if ((MCU_STOP_MODE != LenMode) && (MCU_CYCLICSTOP_MODE != LenMode) && (MCU_DEEPSTOP_MODE != LenMode))
  {
    (void)Det_ReportError(MCU_MODULE_ID, MCU_INSTANCE_ID, MCU_CLEARANDSETWAKEUPFACTOR_SID, MCU_E_PARAM_MODE);
    /* Set return value to E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  else
  #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
  {
    MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
    /* Set WUFMSK0_Ax/WUFMSK1_Ax */
    for(LucCount = MCU_ZERO; LucCount < MCU_NUMBER_WAKEUP_FACTOR; LucCount++)
    {
      LpWakeUpReg = &Mcu_GpWakeUpHwInfo[LucCount];
      *LpWakeUpReg->pWUFMSKRegsAddr = LpModeSetting->aaWakeUpFactor[LucCount];
    }
    #if (MCU_DEV_ERROR_DETECT == STD_ON)
    /* Set status of global wakeup variable */
    switch (LenMode)
    {
    case MCU_STOP_MODE:
      Mcu_GucStopModeWakeUpStatus = MCU_STOP_WAKEUP_SET;
      break;
    case MCU_CYCLICSTOP_MODE:
      Mcu_GucCylicStopModeWakeUpStatus = MCU_CYCLICSTOP_WAKEUP_SET;
      break;
    case MCU_DEEPSTOP_MODE:
      Mcu_GucDeepStopModeWakeUpStatus = MCU_DEEPSTOP_WAKEUP_SET;
      break;
    default:
      /* Do nothing */
      break;
    }
    #endif /* MCU_DEV_ERROR_DETECT == STD_ON */
    MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  }
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_STBGetWakeUpFactor
**
** Service ID         : None
**
** Description        : This service to get wakeup factor
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LpMcuWakeupfactorinfo
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : WUFMON, WUF0_A0, WUF0_A1, WUF0_A2, WUF1_A0, WUF1_A1
**                      WUF1_A2, WUF0_I0, WUF0_I1, WUF1_I0, WUF0_I1,
**                      WUF0_I2, WUF0_I3, WUF1_I2, WUF1_I3
**
** Reference ID       : MCU_DUD_ACT_075, MCU_DUD_ACT_075_REG001
** Reference ID       : MCU_DUD_ACT_075_REG002
**
***********************************************************************************************************************/
#if (MCU_GETWAKEUPFACTOR_API == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_STBGetWakeUpFactor(
  P2VAR(Mcu_WakeUpFactorInfoType, AUTOMATIC, MCU_APPL_DATA) LpMcuWakeupfactorinfo)                                      /* PRQA S 3432 # JV-01 */
{
  P2CONST(volatile Mcu_WakeUpHwInfoType, TYPEDEF, REGSPACE) LpWakeUpReg;
  uint8 LucCount;

  /* Read & Save WUFMON register */
  LpMcuWakeupfactorinfo->ulWufMonValue = *Mcu_GpWUFMONHwInfo->pWUFMONRegsAddr;                                          /* PRQA S 0404 # JV-01 */
  /* WUFMON == 0 */
  if(MCU_LONG_WORD_ZERO == LpMcuWakeupfactorinfo->ulWufMonValue)
  {
    /* No Detail WUF */
    for(LucCount = MCU_ZERO; LucCount < MCU_NUMBER_WAKEUP_FACTOR; LucCount++)
    {
      LpMcuWakeupfactorinfo->aaWufDetail[LucCount] = MCU_LONG_WORD_ZERO;
    }
  }
  else
  {
    /* Read Detail WUF Register */
    for(LucCount = MCU_ZERO; LucCount < MCU_NUMBER_WAKEUP_FACTOR; LucCount++)
    {
      LpWakeUpReg = &Mcu_GpWakeUpHwInfo[LucCount];
      LpMcuWakeupfactorinfo->aaWufDetail[LucCount] = *LpWakeUpReg->pWUFRegsAddr;                                        /* PRQA S 0404 # JV-01 */
    }
  }
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_GETWAKEUPFACTOR_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_STBReleaseIoBufferHold
**
** Service ID         : None
**
** Description        : This service support to release the I/O hold state after the wake-up
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : IOHOLD0, IOHOLD2
**
** Reference ID       : MCU_DUD_ACT_076,
** Reference ID       : MCU_DUD_ACT_076_CRT001, MCU_DUD_ACT_076_CRT002,
** Reference ID       : MCU_DUD_ACT_076_REG001, MCU_DUD_ACT_076_REG002,
** Reference ID       : MCU_DUD_ACT_076_REG003
***********************************************************************************************************************/
#if (MCU_RELEASEIOBUFFERHOLD_API == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_STBReleaseIoBufferHold (void)
{
  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  /* Access Protection Disable */
  *Mcu_GpStbHwInfo->pSTBCKCPROTReg = MCU_STB_DISABLE_REG_PROTECT_VALUE;

  /* Release IOHOLD1 */
  if (NULL_PTR != Mcu_GpIOBufferHoldHwInfo->pIOBufHoldReg)
  {
    /* Release IOHOLD */
    *Mcu_GpIOBufferHoldHwInfo->pIOBufHoldReg = MCU_LONG_WORD_ZERO;
  } /* else No action is required */

  /* Release IOHOLD1 */
  if (NULL_PTR != Mcu_GpIOBufferHoldHwInfo->pIOBufHold1Reg)
  {
    *Mcu_GpIOBufferHoldHwInfo->pIOBufHold1Reg = MCU_LONG_WORD_ZERO;
  } /* else No action is required */

  /* Release IOHOLD2 */
  if (NULL_PTR != Mcu_GpIOBufferHoldHwInfo->pIOBufHold2Reg)
  {
    *Mcu_GpIOBufferHoldHwInfo->pIOBufHold2Reg = MCU_LONG_WORD_ZERO;
  } /* else No action is required */

  /* Access Protection Enable */
  *Mcu_GpStbHwInfo->pSTBCKCPROTReg = MCU_STB_ENABLE_REG_PROTECT_VALUE;
  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_RELEASEIOBUFFERHOLD_API == STD_ON */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
