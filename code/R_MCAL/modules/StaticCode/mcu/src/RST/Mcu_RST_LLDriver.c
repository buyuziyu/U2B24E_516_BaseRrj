/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_RST_LLDriver.c                                                                                  */
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
 * 2.1.1:  30/08/2024   : Update SW-VERSION to 2.1.1
 *                        As part of U2Cx device support, following changes are made:
 *                        - Update function Mcu_RSTSetEcmReset to check NULL_PTR for pRESFCReg
 *                        - Add macro MCU_ECMRESET_APPLICATION_RESET to function Mcu_RSTGetResetReason
 * 2.0.0:  04/08/2023   : Remove redundant QAC message 0791
 * 1.4.5:  01/02/2023   : Initial Version as new Mcu Structure
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:0311)    : Dangerous pointer cast results in loss of const qualification.                               */
/* Rule                : MISRA C:2012 Rule-11.8, CERTCCM EXP05                                                        */
/* JV-01 Justification : This is to achieve throughput in the code.                                                   */
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
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563,     */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3218)    : File scope static, '%s', is only accessed in one function.                                   */
/* Rule                : MISRA C:2012 Rule-8.9, CERTCCM DCL19, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : By moving the array into the function, the stack size used will be more, hence this is       */
/*                       defined outside.                                                                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifiers. There is no impact on the functionality    */
/*                       due to this conditional check for mode change.                                               */
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
#define MCU_RST_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    MCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define MCU_RST_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    MCU_AR_RELEASE_MINOR_VERSION_VALUE
#define MCU_RST_LLDRIVER_C_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MCU_RST_LLDRIVER_C_SW_MAJOR_VERSION            MCU_SW_MAJOR_VERSION_VALUE
#define MCU_RST_LLDRIVER_C_SW_MINOR_VERSION            MCU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (MCU_RST_LLDRIVER_AR_RELEASE_MAJOR_VERSION != MCU_RST_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "MCU_RST_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (MCU_RST_LLDRIVER_AR_RELEASE_MINOR_VERSION != MCU_RST_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "MCU_RST_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (MCU_RST_LLDRIVER_AR_RELEASE_REVISION_VERSION != MCU_RST_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "MCU_RST_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (MCU_RST_LLDRIVER_SW_MAJOR_VERSION != MCU_RST_LLDRIVER_C_SW_MAJOR_VERSION)
#error "MCU_RST_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (MCU_RST_LLDRIVER_SW_MINOR_VERSION != MCU_RST_LLDRIVER_C_SW_MINOR_VERSION)
#error "MCU_RST_LLDriver.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define MCU_START_SEC_VAR_INIT_BOOLEAN
#include "Mcu_MemMap.h"
/* Global variable to Reset reasonvalue call of MCU Driver */
STATIC volatile VAR(boolean, MCU_VAR_INIT) Mcu_GblMulRstReasonCall = MCU_FALSE;
/* Global variable to Reset rawvalue call of MCU Driver */
STATIC volatile VAR(boolean, MCU_VAR_INIT) Mcu_GblMulRstRawValCall = MCU_FALSE;
#define MCU_STOP_SEC_VAR_INIT_BOOLEAN
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define MCU_START_SEC_VAR_NO_INIT_32
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/* Global variable to store Last Reset rawvalue of MCU Driver */
STATIC volatile VAR(uint32, MCU_VAR_NO_INIT) Mcu_GulLastResetRawValue;                                                  /* PRQA S 3218 # JV-01 */
/* Global variable to store Last Reset reason status of MCU Driver */
STATIC volatile VAR(uint32, MCU_VAR_NO_INIT) Mcu_GulLastResetReason;                                                    /* PRQA S 3218 # JV-01 */
/* Global variable to save RESF status of MCU Driver */
STATIC volatile VAR(uint32, MCU_VAR_NO_INIT) Mcu_GulSavedResfStatus;
#define MCU_STOP_SEC_VAR_NO_INIT_32
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/**********************************************************************************************************************/
/**                                             Internal Function Prototypes                                         **/
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name      : Mcu_RSTGetResetReason
**
** Service ID         : None
**
** Description        : The service return reset type value from the hardware register
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
** Return parameter   : Mcu_ResetType
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GpResetHwInfo, Mcu_GblMulRstReasonCall, Mcu_GblMulRstRawValCall,
**                      Mcu_GulSavedResfStatus, Mcu_GulLastResetReason
**
** Function Invoked   : Mcu_ECMGetEcmResetReasonValue
**
** Registers Used     : RESF, RESFC
**
** Reference ID       : MCU_DUD_ACT_069, MCU_DUD_ACT_069_CRT001, MCU_DUD_ACT_069_CRT002, MCU_DUD_ACT_069_GBL001,
** Reference ID       : MCU_DUD_ACT_069_GBL002, MCU_DUD_ACT_069_GBL003, MCU_DUD_ACT_069_REG001
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Mcu_ResetType, MCU_PRIVATE_CODE) Mcu_RSTGetResetReason(void)
{
  uint32 LulResfStatus;
  Mcu_ResetType LenResetSource;
  uint8 LucResBitPos;
  uint32 LulResfStatusCheck;

  LucResBitPos = MCU_ZERO;
  LenResetSource = MCU_NON_RST;

  MCU_ENTER_CRITICAL_SECTION(MCU_RAM_DATA_PROTECTION);

  /* Check whether reset reason api called first time or not */
  if (MCU_FALSE == Mcu_GblMulRstReasonCall)                                                                             /* PRQA S 3416 # JV-01 */
  {
    /* Check whether reset rawvalue api called first time or not */
    if (MCU_FALSE == Mcu_GblMulRstRawValCall)                                                                           /* PRQA S 3416 # JV-01 */
    {
      /* Get the value of reset reason register */
      LulResfStatus = *Mcu_GpResetHwInfo->pRESFReg;                                                                     /* PRQA S 0404 # JV-01 */
    }
    else
    {
      /* Get the value of reset reason from global variable */
      LulResfStatus = Mcu_GulSavedResfStatus;
    }

    LulResfStatus &= (uint32)(~MCU_HWBISTF);

    /* Check if any reset factor is present */
    if (MCU_ZERO != LulResfStatus)
    {
      /* Check if the reset factor is power on reset*/
      if ((MCU_POWER_ON_RESET_BIT | MCU_EXTERNAL_RESET_BIT) == LulResfStatus)
      {
        LenResetSource = MCU_POWER_ON_RESET;
      }
      #if (MCU_STANDBY_RST_ENABLE == STD_ON)
      else if (MCU_STANDBY_RESET_BIT == LulResfStatus)
      {
        LenResetSource = MCU_STANDBY_RST;
      }
      #endif /* MCU_STANDBY_RST_ENABLE == STD_ON */
      else
      {
        /* Check if multiple resets */
        if (MCU_ZERO != ((LulResfStatus) & (LulResfStatus - MCU_ONE)))
        {
          LenResetSource = MCU_MULTI_RST;
        }
        else
        {
          /* Find the position of bit set in reset factor register */
          while (MCU_THIRTYTWO > LucResBitPos)
          {
            /* Left shift bit position, scan all bits from 0 to 31 */
            LulResfStatusCheck = (uint32)MCU_ONE << LucResBitPos;
            /* Check if any reset source is found */
            if (MCU_ZERO != (LulResfStatusCheck & LulResfStatus))
            {
              /* Map reset factor bit to reset reason configured */
              LenResetSource = Mcu_GpResetHwInfo->pRstRsnTable[LucResBitPos];
              #if (MCU_ECM_OPERATION == STD_ON)
              /* Get the exact ECM reset reason in case ECM is configured */
              #if (MCU_ECMRESET_APPLICATION_RESET == STD_ON)
              if ((MCU_SIX == LucResBitPos) || (MCU_TEN == LucResBitPos))
              #else
              if (MCU_SIX == LucResBitPos)
              #endif /* MCU_ECMRESET_APPLICATION_RESET == STD_ON */
              {
                LenResetSource = Mcu_ECMGetEcmResetReasonValue();
              } /* else No action required */
              #endif /* MCU_ECM_OPERATION == STD_ON */
              /* Exit the loop because of correct search the reset source */
              LucResBitPos = MCU_THIRTYTWO;
            } /* else No action required */
            else
            {
              /* Increase next bit postiion until 31 */
              LucResBitPos++;
            }
          }
        }
      }
    } /* else No action required */

    /* Get the value of reset reason register */
    Mcu_GulSavedResfStatus = (uint32)(*Mcu_GpResetHwInfo->pRESFReg);                                                    /* PRQA S 0404 # JV-01 */

    /* Clear the reset factor register */
    *Mcu_GpResetHwInfo->pRESFCReg = MCU_RESF_CLEAR;

    /* Set the value of reset reason to global variable */
    Mcu_GulLastResetReason = (uint32)LenResetSource;

    /* Set the value of call flag for Mcu_GetResetReason */
    Mcu_GblMulRstReasonCall = MCU_TRUE;
  }
  else
  {
    /* Get the value of reset reason from global variables */
    LenResetSource = (Mcu_ResetType)Mcu_GulLastResetReason;                                                             /* PRQA S 4342 # JV-01 */
  }

  MCU_EXIT_CRITICAL_SECTION(MCU_RAM_DATA_PROTECTION);

  return (LenResetSource);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_RSTGetResetRawValue
**
** Service ID         : None
**
** Description        : The service return reset type value from the hardware register
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
** Return parameter   : Mcu_RawResetType
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GpResetHwInfo, Mcu_GblMulRstReasonCall, Mcu_GblMulRstRawValCall, Mcu_GulLastResetRawValue,
**                      Mcu_GulSavedResfStatus
**
** Function Invoked   : None
**
** Registers Used     : RESF, RESFC
**
** Reference ID       : MCU_DUD_ACT_068, MCU_DUD_ACT_068_CRT001, MCU_DUD_ACT_068_CRT002, MCU_DUD_ACT_068_GBL001,
** Reference ID       : MCU_DUD_ACT_068_GBL002, MCU_DUD_ACT_068_GBL003, MCU_DUD_ACT_068_GBL004, MCU_DUD_ACT_068_GBL005,
** Reference ID       : MCU_DUD_ACT_068_REG001
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Mcu_RawResetType, MCU_PRIVATE_CODE) Mcu_RSTGetResetRawValue(void)
{
  Mcu_RawResetType LddResetValue;

  /* Initialize the local variable */
  LddResetValue = MCU_LONG_WORD_ZERO;                                                                                   /* PRQA S 2982 # JV-01 */

  MCU_ENTER_CRITICAL_SECTION(MCU_RAM_DATA_PROTECTION);
  if (MCU_FALSE == Mcu_GblMulRstRawValCall)                                                                             /* PRQA S 3416 # JV-01 */
  {
    if (MCU_FALSE == Mcu_GblMulRstReasonCall)                                                                           /* PRQA S 3416 # JV-01 */
    {
      /* Get the value of reset reason register */
      LddResetValue = (Mcu_RawResetType)(*Mcu_GpResetHwInfo->pRESFReg);                                                 /* PRQA S 0404 # JV-01 */

      /* Set the value of reset reason to global variable */
      Mcu_GulLastResetRawValue = LddResetValue;
      /* Set the value of reset reason to global variable */
      Mcu_GulSavedResfStatus = LddResetValue;

      /* Clear Reset factor register */
      *Mcu_GpResetHwInfo->pRESFCReg = MCU_RESF_CLEAR;

      /* Set the value of call flag for Mcu_GetResetRawValue */
      Mcu_GblMulRstRawValCall = MCU_TRUE;
    }
    else
    {
      /* Get the value of reset reason from global variable */
      LddResetValue = Mcu_GulSavedResfStatus;
      /* Set the value of reset reason to global variable */
      Mcu_GulLastResetRawValue = LddResetValue;
      /* Set the value of call flag for Mcu_GetResetRawValue */
      Mcu_GblMulRstRawValCall = MCU_TRUE;
    }
  }
  else
  {
    /* Return the last clear reset raw status. */
    LddResetValue = Mcu_GulLastResetRawValue;
  }

  MCU_EXIT_CRITICAL_SECTION(MCU_RAM_DATA_PROTECTION);

  return (LddResetValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_RSTPerformReset
**
** Service ID         : None
**
** Description        : This service provides microcontroller reset by accessing the Software reset register.
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
** Global Variables   : Mcu_GpResetHwInfo
**
** Function Invoked   : None
**
** Registers Used     : RESKCPROT, RESKCPROT0, SWARESA, SWSRESA
**
** Reference ID       : MCU_DUD_ACT_070, MCU_DUD_ACT_070_CRT001,
** Reference ID       : MCU_DUD_ACT_070_CRT002, MCU_DUD_ACT_070_REG001
***********************************************************************************************************************/
#if (MCU_PERFORM_RESET_API == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_RSTPerformReset(void)                                                                  /* PRQA S 1503 # JV-01 */
{
  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  #if (MCU_SWRESET_APPLICATION_RESET == STD_ON)
  /* Generate Application Reset */
  MCU_REG_WRITE_PROTECTION(
    Mcu_GpResetHwInfo->pPReg,
    MCU_RST_DISABLE_REG_PROTECT_VALUE,
    MCU_RST_ENABLE_REG_PROTECT_VALUE,
    Mcu_GpResetHwInfo->pSWARESAReg,
    MCU_SW_RESET_ENABLE_VALUE);
  #else
  /* Generate System Reset 2 */
  MCU_REG_WRITE_PROTECTION(
    Mcu_GpResetHwInfo->pPReg,
    MCU_RST_DISABLE_REG_PROTECT_VALUE,
    MCU_RST_ENABLE_REG_PROTECT_VALUE,
    Mcu_GpResetHwInfo->pSWSRESAReg,
    MCU_SW_RESET_ENABLE_VALUE);
  #endif /* MCU_SWRESET_APPLICATION_RESET == STD_ON */
  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  return;
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_PERFORMRESET_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_RSTSetEcmReset
**
** Service ID         : None
**
** Description        : This service provides settings for the behavior of the device during reset
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
** Global Variables   : Mcu_GpResetHwInfo
**
** Function Invoked   : None
**
** Registers Used     : RESKCPROT, RESC.
**
** Reference ID       : MCU_DUD_ACT_100, MCU_DUD_ACT_100_REG001, MCU_DUD_ACT_100_CRT001, MCU_DUD_ACT_100_CRT002
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_RSTSetEcmReset(void)
{
  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  /* Set SWDT/ECM Reset Configuration */
  if(NULL_PTR != Mcu_GpResetHwInfo->pRESCReg)
  {
  MCU_REG_WRITE_PROTECTION(                                                                                             /* PRQA S 0311 # JV-01 */
    Mcu_GpResetHwInfo->pPReg,
    MCU_RST_DISABLE_REG_PROTECT_VALUE,
    MCU_RST_ENABLE_REG_PROTECT_VALUE,
    Mcu_GpResetHwInfo->pRESCReg,
    MCU_RESC_SET_VALUE);
  } /* else No action is required */
  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  return;
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
