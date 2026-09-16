/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_CLM_LLDriver.c                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2022-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 * 2.0.0:  04/08/2023   : Add QAC message 1006, 2814
 *                        Remove redundant QAC message 0791
 *         10/07/2023   : Remove redundant QAC message 0316, 2814, 0488, 2824, 0303
 * 1.4.5:  19/10/2022   : Initial Version as new Mcu structure
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
/* Message (2:1006)    : This in-line assembler construct is a language extension. The code has been ignored.         */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTCCM MSC14                                       */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
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
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifiers. There is no impact on the functionality    */
/*                       due to this conditional check for mode change.                                               */
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

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define MCU_CLM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION     MCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define MCU_CLM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION     MCU_AR_RELEASE_MINOR_VERSION_VALUE
#define MCU_CLM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION  MCU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MCU_CLM_LLDRIVER_C_SW_MAJOR_VERSION MCU_SW_MAJOR_VERSION_VALUE
#define MCU_CLM_LLDRIVER_C_SW_MINOR_VERSION MCU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (MCU_CLM_LLDRIVER_AR_RELEASE_MAJOR_VERSION != MCU_CLM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "Mcu_CLM_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (MCU_CLM_LLDRIVER_AR_RELEASE_MINOR_VERSION != MCU_CLM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "Mcu_CLM_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (MCU_CLM_LLDRIVER_AR_RELEASE_REVISION_VERSION != MCU_CLM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "Mcu_CLM_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (MCU_CLM_LLDRIVER_SW_MAJOR_VERSION != MCU_CLM_LLDRIVER_C_SW_MAJOR_VERSION)
#error "Mcu_CLM_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (MCU_CLM_LLDRIVER_SW_MINOR_VERSION != MCU_CLM_LLDRIVER_C_SW_MINOR_VERSION)
#error "Mcu_CLM_LLDriver.c : Mismatch in Software Minor Version"
#endif

#if (MCU_CLMA_OPERATION == STD_ON)
/***********************************************************************************************************************
**                                             Static Function Definitions                                            **
***********************************************************************************************************************/


#if ((MCU_DMON_DIAG_OPERATION == STD_ON) || (MCU_MODE_TRANSITION_SUPPORT == STD_ON))
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLMValidateCR(
    P2CONST(volatile uint32, AUTOMATIC, MCU_CONFIG_CONST) LpValidatedRegAdress,
    const uint32 LulClockExpectedValue,
    const uint32 LulWaitStableTime);
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

#if (MCU_DMON_DIAG_OPERATION == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLMStartMainOsc(const uint32 LulMaxCount);
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_DMON_DIAG_OPERATION == STD_ON */

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                             Internal Function Prototypes                                           **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name      : Mcu_CLMInit
**
** Service ID         : None
**
** Description        : This service to initialize clock monitor before change
**                      the sampling clock or monitored clock
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
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : CLMKCPROT, CLMTEST
**
** Reference ID       : MCU_DUD_ACT_078, MCU_DUD_ACT_078_CRT001, MCU_DUD_ACT_078_CRT002
** Reference ID       : MCU_DUD_ACT_078_REG001, MCU_DUD_ACT_078_REG002, MCU_DUD_ACT_078_REG003, MCU_DUD_ACT_078_REG004
** Reference ID       : MCU_DUD_ACT_078_REG005, MCU_DUD_ACT_078_REG006, MCU_DUD_ACT_078_REG007, MCU_DUD_ACT_078_REG008
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_CLMInit(void)                                                                          /* PRQA S 3006 # JV-01 */
{
  uint32 LusCount;
  LusCount = Mcu_GpClockSetting->ulClkStbCount;
  /* Disable interrupt to avoid access shared registers across APIs and re-entrant API */
  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  /* Release Register Access Protection */
  *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_DISABLE_REG_PROTECT_VALUE;
  /* Enable CLMn Reset */
  *Mcu_GpClmHwInfo->pCLMATESTRegs = MCU_CLMxTESEN_BIT;
  /* Mask the Error Notification */
  *Mcu_GpClmHwInfo->pCLMATESTRegs |= MCU_CLMERRMASK_BIT;                                                                /* PRQA S 0404 # JV-01 */
  /* Reset Clock Monitor */
  *Mcu_GpClmHwInfo->pCLMATESTRegs |= MCU_CLMRESCLM_BIT;                                                                 /* PRQA S 0404 # JV-01 */
  /* Wait Clock Monitor Reset Time */
  while (LusCount > (uint16)MCU_ZERO)
  {
    LusCount--;
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  }
  /* Release Clock Monitor Reset */
  *Mcu_GpClmHwInfo->pCLMATESTRegs &= ~MCU_CLMRESCLM_BIT;                                                                /* PRQA S 0404 # JV-01 */
  /* Release mask of the Error Notification */
  *Mcu_GpClmHwInfo->pCLMATESTRegs &= ~MCU_CLMERRMASK_BIT;                                                               /* PRQA S 0404 # JV-01 */
  /* Disable CLMn Reset */
  *Mcu_GpClmHwInfo->pCLMATESTRegs &= ~MCU_CLMxTESEN_BIT;                                                                /* PRQA S 0404 # JV-01 */
  /* Hold Register Access protection */
  *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_ENABLE_REG_PROTECT_VALUE;
  /* Enable interrupts after write */
  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_CLMStart
**
** Service ID         : None
**
** Description        : This service set Clock Monitor register
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
** Preconditions      : None
**
** Global Variables   : Mcu_GpConfigPtr
**
** Function Invoked   : None
**
** Registers Used     : CLMKCPROT, CLMnCMPL, CLMnCMPH, CLMnCTL
**                      MCU_ECMKCPROT, MCU_ECMESSTC1
**
** Reference ID       : MCU_DUD_ACT_079, MCU_DUD_ACT_079_CRT001, MCU_DUD_ACT_079_CRT002
** Reference ID       : MCU_DUD_ACT_079_REG001, MCU_DUD_ACT_079_REG002, MCU_DUD_ACT_079_REG003
** Reference ID       : MCU_DUD_ACT_079_REG004, MCU_DUD_ACT_079_REG005, MCU_DUD_ACT_079_REG006
** Reference ID       : MCU_DUD_ACT_079_REG007, MCU_DUD_ACT_079_REG008, MCU_DUD_ACT_079_REG009
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_CLMStart(void)
{
  P2CONST(Mcu_ClmSettingType, MCU_CONST, MCU_CONFIG_DATA) LpClmSetting;
  #if ((MCU_ECM_OPERATION == STD_ON) && (MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_OFF))
  P2CONST(Mcu_EcmHwInfoType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmHwInfo;
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmReg;
  #endif /* MCU_ECM_OPERATION == STD_ON && MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_OFF */
  uint8 LucIndex;

  LucIndex = MCU_ZERO;
  while (LucIndex < Mcu_GpClockSetting->ucNoOfClm)                                                                      /* PRQA S 3416 # JV-01 */
  {
    /* Get the address to CLM configuration structure */
    LpClmSetting =
      ((P2CONST(Mcu_ClmSettingType, MCU_CONST, MCU_CONFIG_DATA))(Mcu_GpClockSetting->pClmSetting) + LucIndex);          /* PRQA S 0316, 0488 # JV-01, JV-01 */
    if (NULL_PTR != LpClmSetting)
    {
      if (MCU_ZERO == (*LpClmSetting->pCLMACTLRegs & MCU_ZERO_BIT))
      {
        /* Disable interrupt to avoid access shared registers across APIs and re-entrant API */
        MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

        /* Release Register Access Protection */
        *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_DISABLE_REG_PROTECT_VALUE;

        /* Set the value of CLM lower limit of frequency */
        *LpClmSetting->pCLMACMPLRegs = LpClmSetting->usClmCmpLvalue;
        /* Set the value of CLM upper limit of frequency */
        *LpClmSetting->pCLMACMPHRegs = LpClmSetting->usClmCmpHvalue;

        #if (MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_ON)
        if (MCU_TRUE == LpClmSetting->blClmBackupEnable)
        {
          /* Set the value of CLMA Backup Clock Enable Register */
          *LpClmSetting->pCLMABCERegs = (uint8)MCU_ENABLE_BACKUP_CLOCK_SWITCH;
        } /* else No action is required */
        #else
        #if (MCU_ECM_OPERATION == STD_ON)
        /* CLMA3 error source status clear */
        if (Mcu_GpClmHwInfo->pCLMA3CTLRegs == LpClmSetting->pCLMACTLRegs)
        {
          /* Get the address to ECM configuration structure */
          LpEcmHwInfo = (P2CONST(Mcu_EcmHwInfoType, MCU_CONST, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pEcmHwInfo;            /* PRQA S 0316 # JV-01 */
          /* Release Register Access Protection */
          *Mcu_GpEcmHwInfo->pECMKCPROTReg = MCU_ECM_DISABLE_REG_PROTECT_VALUE;
          LpEcmReg = LpEcmHwInfo->pECMESSTC0Reg + (uint32)MCU_ONE;                                                      /* PRQA S 0488 # JV-01 */

          /* Clear status for ECM interrupt */
          *LpEcmReg &= ~MCU_ECM_ECMSSTR1_CLM3ERR_MASK;

          /* Hold Register Access protection */
          *Mcu_GpEcmHwInfo->pECMKCPROTReg = MCU_ECM_ENABLE_REG_PROTECT_VALUE;
        } /* else No action is required */
        #endif /* MCU_ECM_OPERATION == STD_ON */
        #endif /* MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_ON */

        /* Set the value of CLM Enable Register */
        *LpClmSetting->pCLMACTLRegs = MCU_ENABLE_CLMA;

        /* Hold Register Access protection */
        *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_ENABLE_REG_PROTECT_VALUE;

        /* Enable interrupts after write */
        MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
      } /* else No action is required */
    } /* else No action is required */
    /* Increment the value of index */
    LucIndex++;
  }
  return;
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_CLMStop
**
** Service ID         : None
**
** Description        : This service stop Clock Monitor before enter standby mode
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
** Preconditions      : None
**
** Global Variables   : Mcu_GpConfigPtr
**
** Function Invoked   : None
**
** Registers Used     : CLMKCPROT, CLMTEST,
**
** Reference ID       : MCU_DUD_ACT_080
** Reference ID       : MCU_DUD_ACT_080_REG001, MCU_DUD_ACT_080_REG002, MCU_DUD_ACT_080_REG003, MCU_DUD_ACT_080_REG004
** Reference ID       : MCU_DUD_ACT_080_REG005, MCU_DUD_ACT_080_REG006, MCU_DUD_ACT_080_REG007, MCU_DUD_ACT_080_REG008
***********************************************************************************************************************/
#if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_CLMStop(void)                                                                          /* PRQA S 3006 # JV-01 */
{
  P2CONST(Mcu_ClmSettingType, MCU_CONST, MCU_CONFIG_DATA) LpClmSetting;
  uint8 LucIndex;
  uint32 LulCount;
  uint32 LulClmTestEnableVal;

  LucIndex = MCU_ZERO;
  LulClmTestEnableVal = MCU_LONG_WORD_ZERO;
  /* Get value of stable clock wait time */
  LulCount = Mcu_GpClockSetting->ulClkStbCount;

  while (LucIndex < Mcu_GpClockSetting->ucNoOfClm)                                                                      /* PRQA S 3416 # JV-01 */
  {
    /* Get the address to CLM configuration structure */
    LpClmSetting =
      ((P2CONST(Mcu_ClmSettingType, MCU_CONST, MCU_CONFIG_DATA))(Mcu_GpClockSetting->pClmSetting) + LucIndex);          /* PRQA S 0316, 0488 # JV-01, JV-01 */

    if (NULL_PTR != LpClmSetting)
    {
      /* Check whether CLMn is enabling */
      if (MCU_ZERO != (*LpClmSetting->pCLMACTLRegs & MCU_ZERO_BIT))
      {
        /* Check whether CLMn should be stop in Standby mode (CLM3-4-6 are True) */
        if (MCU_TRUE == LpClmSetting->blClmStopInStandby)
        {
          /* Set the value of CLM Enable Register */
          LulClmTestEnableVal |= LpClmSetting->ulClmTestEnableBit;
        } /* else No action required */
      } /* else No action required */
    } /* else No action required */
    /* Increment the value of index */
    LucIndex++;
  }

  if (MCU_LONG_WORD_ZERO != LulClmTestEnableVal)
  {
    /* Release Register Access Protection */
    *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_DISABLE_REG_PROTECT_VALUE;

    /* Enable CLMn Reset */
    *Mcu_GpClmHwInfo->pCLMATESTRegs = LulClmTestEnableVal;
    /* Mask the Error Notification */
    *Mcu_GpClmHwInfo->pCLMATESTRegs |= MCU_CLMERRMASK_BIT;                                                              /* PRQA S 0404 # JV-01 */
    /* Reset Clock Monitor */
    *Mcu_GpClmHwInfo->pCLMATESTRegs |= MCU_CLMRESCLM_BIT;                                                               /* PRQA S 0404 # JV-01 */

    /*Wait Clock Monitor Reset Time */
    while (LulCount > (uint32)MCU_ZERO)
    {
      LulCount--;
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */
    }

    /* Release Clock Monitor Reset */
    *Mcu_GpClmHwInfo->pCLMATESTRegs &= ~MCU_CLMRESCLM_BIT;                                                              /* PRQA S 0404 # JV-01 */
    /* Release mask of the Error Notification */
    *Mcu_GpClmHwInfo->pCLMATESTRegs &= ~MCU_CLMERRMASK_BIT;                                                             /* PRQA S 0404 # JV-01 */
    /* Disable CLMn Reset */
    *Mcu_GpClmHwInfo->pCLMATESTRegs &= ~LulClmTestEnableVal;                                                            /* PRQA S 0404 # JV-01 */

    /* Hold Register Access protection */
    *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_ENABLE_REG_PROTECT_VALUE;
  } /* else No action required */
  return;
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_MODE_TRANSITION_SUPPORT == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLMEnable
**
** Service ID         : None
**
** Description        : This service enable CLMA0 support DMON process
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
** Return parameter   : LucOscStatus
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpConfigPtr
**
** Function Invoked   : Mcu_CLMValidateCR, Mcu_CLMStartMainOsc
**
** Registers Used     : CLMKCPROT, CLMnCMPL, CLMnCMPH, CLMnCTL
**                      MOSCS, HSOSCS, MOSCE
**
** Reference ID       : MCU_DUD_ACT_081, MCU_DUD_ACT_081_REG001,
** Reference ID       : MCU_DUD_ACT_081_REG002, MCU_DUD_ACT_081_REG003,
** Reference ID       : MCU_DUD_ACT_081_REG004, MCU_DUD_ACT_081_REG005
***********************************************************************************************************************/
#if (MCU_DMON_DIAG_OPERATION == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLMEnable(void)
{
  P2CONST(Mcu_ClockSettingType, MCU_CONST, MCU_CONFIG_DATA) LpClockSetting;
  P2CONST(Mcu_ClmSettingType, MCU_CONST, MCU_CONFIG_DATA) LpClmSetting;
  uint8 LucIndex;
  Std_ReturnType LucOscStatus;
  LpClockSetting = (P2CONST(Mcu_ClockSettingType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pClockSetting;     /* PRQA S 0316 # JV-01 */
  LucIndex = MCU_ZERO;
  LucOscStatus = E_OK;
  while (LucIndex < LpClockSetting->ucNoOfClm)
  {
    /* Get the address to CLM configuration structure */
    LpClmSetting = ((P2CONST(Mcu_ClmSettingType, MCU_CONST, MCU_CONFIG_DATA))LpClockSetting->pClmSetting + LucIndex);   /* PRQA S 0316, 0488 # JV-01, JV-01 */
    if (MCU_TRUE == LpClmSetting->blClmMOSC)
    {
      if (MCU_ZERO == (*LpClmSetting->pCLMACTLRegs & MCU_ONE))
      {
        /* Check if Main OSC is stable or not before enable CLM */
        LucOscStatus = Mcu_CLMValidateCR(Mcu_GpClockHwInfo->pMainOscSReg,
                                          MCU_MOSCS_CLK_STABLE, LpClockSetting->ulClkStbCount);
        if ((E_NOT_OK == LucOscStatus) && (MCU_TRUE == LpClockSetting->blClkGenSupported))
        {
          /* Start Main OSC */
          LucOscStatus = Mcu_CLMStartMainOsc(LpClockSetting->ulClkStbCount);
          if (E_OK == LucOscStatus)
          {
            /* Check if HS IntOSC is stable or not */
            LucOscStatus = Mcu_CLMValidateCR(Mcu_GpClockHwInfo->pHSOscSReg,
                                              MCU_HSOSC_CLK_STABLE,
                                              LpClockSetting->ulClkStbCount);
          } /* else No action is required */
        } /* else No action is required */
        /* Setting for CLM after checking OSC status */
        if (E_OK == LucOscStatus)
        {
          /* Release Register Access Protection */
          *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_DISABLE_REG_PROTECT_VALUE;
          /* Set the value of CLM lower limit of frequency */
          *LpClmSetting->pCLMACMPLRegs = LpClmSetting->usClmCmpLvalue;
          /* Set the value of CLM upper limit of frequency */
          *LpClmSetting->pCLMACMPHRegs = LpClmSetting->usClmCmpHvalue;
          /* Set the value of CLM Enable Register */
          *LpClmSetting->pCLMACTLRegs = (uint8)MCU_ENABLE_CLMA;
          /* Hold Register Access protection */
          *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_ENABLE_REG_PROTECT_VALUE;
        } /* else OSC is not stable, CLM is not enabled */
      } /* else No action is required */
      /* Break loop after setting for expected CLM */
      LucIndex = LpClockSetting->ucNoOfClm;
    } /* else No action is required */
    /* Increment the value of index */
    LucIndex++;
  }
  return LucOscStatus;
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_DMON_DIAG_OPERATION == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLMValidateCR
**
** Service ID         : None
**
** Description        : This service support to confirm status of target clock
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LpValidatedRegAdress, LulClockExpectedValue
**                      LulWaitStableTime
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_082

***********************************************************************************************************************/
#if ((MCU_DMON_DIAG_OPERATION == STD_ON) || (MCU_MODE_TRANSITION_SUPPORT == STD_ON))
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLMValidateCR(                                                        /* PRQA S 3006 # JV-01 */
    P2CONST(volatile uint32, AUTOMATIC, MCU_CONFIG_CONST) LpValidatedRegAdress,
    const uint32 LulClockExpectedValue,
    const uint32 LulWaitStableTime)
{
  Std_ReturnType LucReturnValue;
  uint32 LulCount;
  LucReturnValue = E_OK;
  /* Setting clock stable wait time */
  LulCount = LulWaitStableTime;
  /* Process to check status of target clock */
  while ((((*LpValidatedRegAdress) & MCU_CKSC_ALLMASK) != LulClockExpectedValue) && (LulCount > (uint32)MCU_ZERO))
  {
    LulCount--;
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  }
  if (((*LpValidatedRegAdress) & MCU_CKSC_ALLMASK) != LulClockExpectedValue)
  {
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Clock status is as expectation */
    /* Do nothing */
  }
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_DMON_DIAG_OPERATION == STD_ON || MCU_MODE_TRANSITION_SUPPORT == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLMStartMainOsc
**
** Service ID         : None
**
** Description        : This service to start Main Osc clock source
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LulMaxCount - The max count waiting for MOSCE register set
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : Mcu_CLMValidateCR
**
** Registers Used     : MOSCE, CLKKCPROT1
**
** Reference ID       : MCU_DUD_ACT_083, MCU_DUD_ACT_083_REG001,
** Reference ID       : MCU_DUD_ACT_083_REG002, MCU_DUD_ACT_083_REG003
**
***********************************************************************************************************************/
#if (MCU_DMON_DIAG_OPERATION == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLMStartMainOsc(const uint32 LulMaxCount)
{
  Std_ReturnType LucReturnValue;
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  /* Release Register Access protection */
  *Mcu_GpClockHwInfo->pPReg = MCU_CKSC_DISABLE_REG_PROTECT_VALUE;
  /* Start the MainOSC (MOSCE.MOSCENTRG = 1) */
  *Mcu_GpClockHwInfo->pMainOscEReg = MCU_MOSCE_ENABLE_TRIGGER;
  /* Hold Register Access protection */
  *Mcu_GpClockHwInfo->pPReg = MCU_CKSC_ENABLE_REG_PROTECT_VALUE;
  /* Check stability of MainOSC */
  LucReturnValue = Mcu_CLMValidateCR(Mcu_GpClockHwInfo->pMainOscSReg,
                                        MCU_MOSCS_CLK_STABLE,
                                        LulMaxCount);
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_DMON_DIAG_OPERATION == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLMRestart
**
** Service ID         : None
**
** Description        : This service restart Clock Monitor after wakeup from standby mode
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LulMoscsValue, aaSystemClockValue, aaPllDivisionValue
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpClockSetting
**
** Function Invoked   : Mcu_CLMValidateCR
**
** Registers Used     : CLMAKCPROT, CLMAnCMPL, CLMAnCMPH, CLMAnCTL, CKSC_CPUS, CLKD_PLLS, MOSCS, MCU_MOSCE, HSOSCS
**                      MCU_CLMATEST, MCU_ECMKCPROT, MCU_ECMESSTC1
**
** Reference ID       : MCU_DUD_ACT_102
** Reference ID       : MCU_DUD_ACT_102_REG001, MCU_DUD_ACT_102_REG002, MCU_DUD_ACT_102_REG003
** Reference ID       : MCU_DUD_ACT_102_REG004, MCU_DUD_ACT_102_REG005, MCU_DUD_ACT_102_REG006
***********************************************************************************************************************/
#if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PRIVATE_CODE)
Mcu_CLMRestart(uint32 LulMoscsValue, const uint32 aaSystemClockValue[], const uint32 aaPllDivisionValue[])              /* PRQA S 3006 # JV-01 */
{
  P2CONST(Mcu_ClmSettingType, MCU_CONST, MCU_CONFIG_CONST) LpClmSetting;
  P2CONST(Mcu_ClockModeSettingType, AUTOMATIC, MCU_CONFIG_DATA) LpClockModeSetting;
  uint8 LucIndex;
  uint32 LulCount;
  uint8 LucOscStatus;
  uint8 LucGearUpStatus;
  Std_ReturnType LucReturnValue;

  #if ((MCU_ECM_OPERATION == STD_ON) && (MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_OFF))
  P2CONST(Mcu_EcmHwInfoType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmHwInfo;
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmReg;
  #endif /* MCU_ECM_OPERATION == STD_ON && MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_OFF */

  LucIndex = MCU_ZERO;                                                                                                  /* PRQA S 2982 # JV-01 */
  LucOscStatus = E_NOT_OK;                                                                                              /* PRQA S 2982 # JV-01 */
  LucGearUpStatus = E_OK;
  LucReturnValue = E_OK;
  LpClockModeSetting = Mcu_GpClockSetting->pClockModeSetting;
  LulCount = Mcu_GpClockSetting->ulClkStbCount;
  for (LucIndex = MCU_ZERO; LucIndex < Mcu_GpClockHwInfo->ucNoOfClkSrc; LucIndex++)
  {
    if ((MCU_CKSC_PLLO == aaSystemClockValue[LucIndex])
        && (MCU_CKDS_SRCCLKDSYNC_OK == aaPllDivisionValue[LucIndex]))
    {
      /* Check Gear up procedure has been finished */
      if ((MCU_CKDS_SRCCLKDSYNC_OK != (*(LpClockModeSetting[LucIndex].pCLKDSAddr) & MCU_CKDS_SYNCMASK)) ||
          (MCU_CKSC_PLLO != (*(LpClockModeSetting[LucIndex].pCKSSAddr) & MCU_CKSC_MASK)))
      {
        /* Gear up procedure has not been finished */
        LucGearUpStatus = E_NOT_OK;
      } /* else No action is required */
    } /* else No action is required */
  } /* else No action is required */
  /* Gear up processing is not done before mode change */

  /* Check if Main OSC is stable or not before mode change */
  if (MCU_MOSCS_CLK_STABLE == LulMoscsValue)
  {
    /* Check if Main OSC is stable or not before enable CLMA */
    LucOscStatus = Mcu_CLMValidateCR(Mcu_GpClockHwInfo->pMainOscSReg,                                                   /* PRQA S 0404 # JV-01 */
                                        MCU_MOSCS_CLK_STABLE,
                                        Mcu_GpClockSetting->ulClkStbCount);
    if (E_NOT_OK == LucOscStatus)
    {
      /* Check MOSCS.MOSCEN == 0 & MOSCS.MOSCSTAB == 0).*/
      if (MCU_MOSCS_CONFIRMATION ==                                                                                     /* PRQA S 0404 # JV-01 */
          (*Mcu_GpClockHwInfo->pMainOscSReg & (MCU_MOSCS_MOSCSTAB_MASK | MCU_MOSCS_MOSCEN_MASK)))
      {
        /* Release Register Access protection */
        *Mcu_GpClockHwInfo->pPReg = MCU_CKSC_DISABLE_REG_PROTECT_VALUE;
        /* Start the MainOSC (MOSCE.MOSCENTRG = 1) */
        *Mcu_GpClockHwInfo->pMainOscEReg = MCU_MOSCE_ENABLE_TRIGGER;
        /* Hold Register Access protection */
        *Mcu_GpClockHwInfo->pPReg = MCU_CKSC_ENABLE_REG_PROTECT_VALUE;
        /* Check stability of MainOSC */
        LucOscStatus = Mcu_CLMValidateCR(Mcu_GpClockHwInfo->pMainOscSReg,                                               /* PRQA S 0404 # JV-01 */
                                              MCU_MOSCS_CLK_STABLE,
                                              Mcu_GpClockSetting->ulClkStbCount);
      }
      else
      {
        LucOscStatus = E_NOT_OK;
      }
    } /* else No action is required */
    /* Main OSC is stable */
  }
  else
  {
    /* Main OSC is not stable before mode change */
    LucOscStatus = E_NOT_OK;
  }

  LucIndex = MCU_ZERO;
  while (LucIndex < Mcu_GpClockSetting->ucNoOfClm)                                                                      /* PRQA S 3416 # JV-01 */
  {
    /* Get the address to CLMA configuration structure */
    LpClmSetting =
        ((P2CONST(Mcu_ClmSettingType, MCU_CONST, MCU_CONFIG_CONST))(Mcu_GpClockSetting->pClmSetting) + LucIndex);       /* PRQA S 0316, 0488 # JV-01, JV-01 */

    if (MCU_THREE == LucIndex)
    {
      /* Reset CLMA3 */
      /* Release Register Access protection */
      *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_DISABLE_REG_PROTECT_VALUE;
      /* Enable CLMn Reset */
      *Mcu_GpClmHwInfo->pCLMATESTRegs = MCU_CLM3TESEN_BIT;
      /* Mask the Error Notification */
      *Mcu_GpClmHwInfo->pCLMATESTRegs |= MCU_CLMERRMASK_BIT;                                                            /* PRQA S 0404 # JV-01 */
      /* Reset Clock Monitor */
      *Mcu_GpClmHwInfo->pCLMATESTRegs |= MCU_CLMRESCLM_BIT;                                                             /* PRQA S 0404 # JV-01 */
      /*Wait Clock Monitor Reset Time */
      while (LulCount > (uint32)MCU_ZERO)
      {
        LulCount--;
        EXECUTE_SYNCP();                                                                                                /* PRQA S 1006 # JV-01 */
      }
      /* Release Clock Monitor Reset */
      *Mcu_GpClmHwInfo->pCLMATESTRegs &= ~MCU_CLMRESCLM_BIT;                                                            /* PRQA S 0404 # JV-01 */
      /* Release mask of the Error Notification */
      *Mcu_GpClmHwInfo->pCLMATESTRegs &= ~MCU_CLMERRMASK_BIT;                                                           /* PRQA S 0404 # JV-01 */
      /* Disable CLMn Reset */
      *Mcu_GpClmHwInfo->pCLMATESTRegs &= ~MCU_CLM3TESEN_BIT;                                                            /* PRQA S 0404 # JV-01 */
      /* Hold Register Access protection */
      *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_ENABLE_REG_PROTECT_VALUE;
      /* Enable interrupts after write */

      #if ((MCU_ECM_OPERATION == STD_ON) && (MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_OFF))
      /* CLMA3 error source status clear */
      /* Get the address to ECM configuration structure */
      LpEcmHwInfo = (P2CONST(Mcu_EcmHwInfoType, MCU_CONST, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pEcmHwInfo;                /* PRQA S 0316 # JV-01 */
      /* Release Register Access Protection */
      *Mcu_GpEcmHwInfo->pECMKCPROTReg = MCU_ECM_DISABLE_REG_PROTECT_VALUE;
      LpEcmReg = LpEcmHwInfo->pECMESSTC0Reg + (uint32)MCU_ONE;                                                          /* PRQA S 0488 # JV-01 */

      /* Clear status for ECM interrupt */
      *LpEcmReg &= ~MCU_ECM_ECMSSTR1_CLM3ERR_MASK;

      /* Hold Register Access protection */
      *Mcu_GpEcmHwInfo->pECMKCPROTReg = MCU_ECM_ENABLE_REG_PROTECT_VALUE;
      #endif /* MCU_ECM_OPERATION == STD_ON && MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_OFF */

    } /* else No action is required */
    /* Check if HS IntOSC is stable or not for CLMA0/1/2/4 */
    if ((MCU_ZERO == LucIndex) || (MCU_ONE == LucIndex) || (MCU_TWO == LucIndex) || (MCU_FOUR == LucIndex))
    {
      if (E_OK == LucOscStatus)
      {
        /* Check if HS IntOSC is stable or not */
        LucOscStatus = Mcu_CLMValidateCR(Mcu_GpClockHwInfo->pHSOscSReg,                                                 /* PRQA S 0404 # JV-01 */
                                                    MCU_HSOSC_CLK_STABLE,
                                                    Mcu_GpClockSetting->ulClkStbCount);
      } /* else No action is required */
    } /* else No action is required */

    if (MCU_ZERO == (uint8)((*LpClmSetting->pCLMACTLRegs) & MCU_ZERO_BIT))
    {
      if (E_OK == LucOscStatus)
      {
        if (LucIndex >= MCU_THREE)
        {
          if (E_OK == LucGearUpStatus)
          {
            /* Release Register Access Protection */
            *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_DISABLE_REG_PROTECT_VALUE;
            /* Set the value of CLM lower limit of frequency */
            *LpClmSetting->pCLMACMPLRegs = LpClmSetting->usClmCmpLvalue;
            /* Set the value of CLM upper limit of frequency */
            *LpClmSetting->pCLMACMPHRegs = LpClmSetting->usClmCmpHvalue;
            #if (MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_ON)
            if (MCU_TRUE == LpClmSetting->blClmBackupEnable)
            {
              /* Set the value of CLMA Backup Clock Enable Register */
              *LpClmSetting->pCLMABCERegs = (uint8)MCU_ENABLE_BACKUP_CLOCK_SWITCH;
            } /* else No action is required */
            #endif /* MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_ON */
            /* Set the value of CLM Enable Register */
            *LpClmSetting->pCLMACTLRegs = (uint8)MCU_ENABLE_CLMA;
            /* Hold Register Access protection */
            *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_ENABLE_REG_PROTECT_VALUE;
          } /* else No action is required */
        }
        else
        {
          /* Release Register Access Protection */
          *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_DISABLE_REG_PROTECT_VALUE;
          /* Set the value of CLM lower limit of frequency */
          *LpClmSetting->pCLMACMPLRegs = LpClmSetting->usClmCmpLvalue;
          /* Set the value of CLM upper limit of frequency */
          *LpClmSetting->pCLMACMPHRegs = LpClmSetting->usClmCmpHvalue;
          #if (MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_ON)
          if (MCU_TRUE == LpClmSetting->blClmBackupEnable)
          {
            /* Set the value of CLMA Backup Clock Enable Register */
            *LpClmSetting->pCLMABCERegs = (uint8)MCU_ENABLE_BACKUP_CLOCK_SWITCH;
          } /* else No action is required */
          #endif /* MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_ON */
          /* Set the value of CLM Enable Register */
          *LpClmSetting->pCLMACTLRegs = (uint8)MCU_ENABLE_CLMA;
          /* Hold Register Access protection */
          *Mcu_GpClmHwInfo->pCLMAKCPROTRegs = MCU_CLMA_ENABLE_REG_PROTECT_VALUE;
        }
      } /* else No action is required */
    } /* else No action is required */
    /* Increment the value of index */
    LucIndex++;
  }

  /* Check status for gear up and clock source stability */
  if ((E_NOT_OK == LucGearUpStatus) || (E_NOT_OK == LucOscStatus))
  {
    LucReturnValue = E_NOT_OK;
  } /* else No action is required */

  return LucReturnValue;
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_MODE_TRANSITION_SUPPORT == STD_ON */

#endif /* MCU_CLMA_OPERATION == STD_ON */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
