/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_ECC_LLDriver.c                                                                                  */
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
 *         16/07/2024   : As part of ARDAACL-47932 (ARDAACL-47792), following changes are made:
 *                        - Add function Mcu_ECCGetRramStatus and Mcu_ECCSetRramEccInt
 *                        - Update funtion Mcu_ECCGetRamState to invoke Mcu_ECCGetRramStatus
 *                        - Update function Mcu_ECCGetLramStatus and function Mcu_ECCSetLramEccInt to check NULL_PTR for
 *                        pLR1_SERSTRReg, pLR1_DERSTRReg, pLR1_OVFSTRReg,
 *                        pLR1_SSTCLRReg, pLR1_DSTCLRReg, pLR1_OVFCLRReg, pLR1_ERRINTReg
 * 2.0.0:  04/08/2023   : Remove redundant QAC message 0791
 *         21/06/2023   : Removed "else" statement don't use when no action required in function Mcu_ECCGetCramStatus
 * 1.4.5:  01/02/2023   : Initial Version as new Mcu Structure
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
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
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563,     */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
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
#define MCU_ECC_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    MCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define MCU_ECC_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    MCU_AR_RELEASE_MINOR_VERSION_VALUE
#define MCU_ECC_LLDRIVER_C_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MCU_ECC_LLDRIVER_C_SW_MAJOR_VERSION            MCU_SW_MAJOR_VERSION_VALUE
#define MCU_ECC_LLDRIVER_C_SW_MINOR_VERSION            MCU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (MCU_ECC_LLDRIVER_AR_RELEASE_MAJOR_VERSION != MCU_ECC_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "MCU_ECC_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (MCU_ECC_LLDRIVER_AR_RELEASE_MINOR_VERSION != MCU_ECC_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "MCU_ECC_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (MCU_ECC_LLDRIVER_AR_RELEASE_REVISION_VERSION != MCU_ECC_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "MCU_ECC_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (MCU_ECC_LLDRIVER_SW_MAJOR_VERSION != MCU_ECC_LLDRIVER_C_SW_MAJOR_VERSION)
#error "MCU_ECC_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (MCU_ECC_LLDRIVER_SW_MINOR_VERSION != MCU_ECC_LLDRIVER_C_SW_MINOR_VERSION)
#error "MCU_ECC_LLDriver.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/**********************************************************************************************************************/
/**                                             Internal Function Prototypes                                         **/
/**********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

STATIC FUNC(void, MCU_PRIVATE_CODE) Mcu_ECCSetLramEccIntPE(void);

#if (MCU_GET_RAM_STATE_API == STD_ON)
#if (MCU_PROVIDE_RAM_STATE_ISR != STD_ON)
STATIC FUNC(uint32, MCU_PRIVATE_CODE)Mcu_ECCGetLramStatusPE(void);

STATIC FUNC(Mcu_RamStateType, MCU_PRIVATE_CODE) Mcu_ECCGetLramStatus(void);

STATIC FUNC(Mcu_RamStateType, MCU_PRIVATE_CODE) Mcu_ECCGetCramStatus(void);

#if (MCU_RETENTION_RAM_SETTING == STD_ON)
STATIC FUNC(Mcu_RamStateType, MCU_PRIVATE_CODE) Mcu_ECCGetRramStatus(void);
#endif /* MCU_RETENTION_RAM_SETTING == STD_ON */
#endif /* MCU_PROVIDE_RAM_STATE_ISR != STD_ON */
#endif /* MCU_GET_RAM_STATE_API == STD_ON */

#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name      : Mcu_ECCSetLramEccInt
**
** Service ID         : None
**
** Description        : This service clear LRAM ECC Error and set ECC Error Interrupt
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
** Function Invoked   : Mcu_ECCSetLramEccIntPE
**
** Registers Used     : ECCKCPROT, LR1_SSTCLR, LR1_DSTCLR, LR1_OVFCLR, LR1_ERRINT
**
** Reference ID       : MCU_DUD_ACT_093, MCU_DUD_ACT_093_REG001,
** Reference ID       : MCU_DUD_ACT_093_REG002, MCU_DUD_ACT_093_REG003,
** Reference ID       : MCU_DUD_ACT_093_REG004, MCU_DUD_ACT_093_REG005,
** Reference ID       : MCU_DUD_ACT_093_REG006
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_ECCSetLramEccInt(void)
{
  /* LRAM status Clear */
  Mcu_ECCSetLramEccIntPE();

  /* Clear error flags in LR1_SERSTR */
  if(NULL_PTR != Mcu_GpEccHwInfo->pLR1_SSTCLRReg)
  {
    *Mcu_GpEccHwInfo->pLR1_SSTCLRReg = (uint32)MCU_LRAM_SST_CLR_VALUE;
  } /* else No action is required */

  /* Clear error flags in LR1_DERSTR */
  if(NULL_PTR != Mcu_GpEccHwInfo->pLR1_DSTCLRReg)
  {
    *Mcu_GpEccHwInfo->pLR1_DSTCLRReg = (uint32)MCU_LRAM_DST_CLR_VALUE;
  } /* else No action is required */

  /* Clear error flags in LR1_OVFSTR */
  if(NULL_PTR != Mcu_GpEccHwInfo->pLR1_OVFCLRReg)
  {
    *Mcu_GpEccHwInfo->pLR1_OVFCLRReg = (uint32)MCU_LRAM_OVF_CLR_VALUE;
  } /* else No action is required */

  /* LRAM Error control setting */
  #if (MCU_PROVIDE_RAM_STATE_ISR == STD_ON)
  /* Release Register Access Protection */
  *Mcu_GpEccHwInfo->pECCKCPROTReg = MCU_ECC_DISABLE_REG_PROTECT_VALUE;

  if(NULL_PTR != Mcu_GpEccHwInfo->pLR1_ERRINTReg)
  {
    *Mcu_GpEccHwInfo->pLR1_ERRINTReg = (uint32)MCU_LR1_ERRINT_ENABLE_VALUE;
  } /* else No action is required */

  /* Hold Register Access protection */
  *Mcu_GpEccHwInfo->pECCKCPROTReg = MCU_ECC_ENABLE_REG_PROTECT_VALUE;
  #endif /* MCU_PROVIDE_RAM_STATE_ISR == STD_ON */
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_ECCSetCramEccInt
**
** Service ID         : None
**
** Description        : This service clear CRAM ECC Error and set ECC Error Interrupt
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
** Registers Used     : ECCKCPROT, CR_SSTCLR, CR_DSTCLR, CR_OVFCLR, CR_ERRINT
**
** Reference ID       : MCU_DUD_ACT_094, MCU_DUD_ACT_094_REG001,
** Reference ID       : MCU_DUD_ACT_094_REG002, MCU_DUD_ACT_094_REG003,
** Reference ID       : MCU_DUD_ACT_094_REG004, MCU_DUD_ACT_094_REG005,
** Reference ID       : MCU_DUD_ACT_094_REG006
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_ECCSetCramEccInt(void)
{
  /* CRAM status Clear */
  *Mcu_GpEccHwInfo->pCR_SSTCLRReg = (uint32)MCU_CRAM_SST_CLR_VALUE;

  *Mcu_GpEccHwInfo->pCR_DSTCLRReg = (uint32)MCU_CRAM_DST_CLR_VALUE;

  *Mcu_GpEccHwInfo->pCR_OVFCLRReg = (uint32)MCU_CRAM_OVF_CLR_VALUE;

  /* CRAM Error control setting */
  #if (MCU_PROVIDE_RAM_STATE_ISR == STD_ON)
  /* Release Register Access Protection */
  *Mcu_GpEccHwInfo->pECCKCPROTReg = MCU_ECC_DISABLE_REG_PROTECT_VALUE;

  *Mcu_GpEccHwInfo->pCR_ERRINTReg = (uint32)MCU_CR_ERRINT_ENABLE_VALUE;

  /* Hold Register Access protection */
  *Mcu_GpEccHwInfo->pECCKCPROTReg = MCU_ECC_ENABLE_REG_PROTECT_VALUE;
  #endif /* MCU_PROVIDE_RAM_STATE_ISR == STD_ON */
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_ECCSetLramEccIntPE
**
** Service ID         : None
**
** Description        : This service set each PE's LRAM ECC register
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
** Registers Used     : LR0_SSTCLR_PEx, LR0_DSTCLR_PEx, LR0_OVFCLR_PEx, LR0_ERRINT_PEx
**
** Reference ID       : MCU_DUD_ACT_097, MCU_DUD_ACT_097_REG001,
** Reference ID       : MCU_DUD_ACT_097_REG002, MCU_DUD_ACT_097_REG003,
** Reference ID       : MCU_DUD_ACT_097_REG004, MCU_DUD_ACT_097_REG005,
** Reference ID       : MCU_DUD_ACT_097_REG006
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, MCU_PRIVATE_CODE) Mcu_ECCSetLramEccIntPE(void)
{
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pLR0_ERRINT_Reg;                                                            /* PRQA S 3432 # JV-01 */
  uint8 LucPeCount;

  for (LucPeCount = MCU_ZERO; LucPeCount < (uint8)MCU_TOTAL_PE_NUM; LucPeCount++)
  {
    /* Calculate LR0_ERRINT_PEn */
    pLR0_ERRINT_Reg =                                                                                                   /* PRQA S 0404 # JV-01 */
      (volatile uint32 *)(Mcu_GpEccHwInfo->pLR0_ERRINT_PE0Reg + (Mcu_GpEccHwInfo->ulLR0PEnOffset * (uint32)LucPeCount));/* PRQA S 0488, 3384 # JV-01, JV-01 */
    /* Clear RAM error status */
    /* LR0_SSTCLR_PEn */
    *(pLR0_ERRINT_Reg + Mcu_GpEccHwInfo->ulLR0SSTCLROffset) = (uint32)MCU_LRAM_SST_CLR_VALUE;                           /* PRQA S 0488 # JV-01 */
    /* LR0_DSTCLR_PEn */
    *(pLR0_ERRINT_Reg + Mcu_GpEccHwInfo->ulLR0DSTCLROffset) = (uint32)MCU_LRAM_DST_CLR_VALUE;                           /* PRQA S 0488 # JV-01 */
    /* LR0_OVFCLR_PEn */
    *(pLR0_ERRINT_Reg + Mcu_GpEccHwInfo->ulLR0OVFCLROffset) = (uint32)MCU_LRAM_OVF_CLR_VALUE;                           /* PRQA S 0488 # JV-01 */

    /* LRAM Error control setting */
    #if (MCU_PROVIDE_RAM_STATE_ISR == STD_ON)
    /* Release Register Access Protection */
    /* ECCKCPROT */
    *Mcu_GpEccHwInfo->pECCKCPROTReg = MCU_ECC_DISABLE_REG_PROTECT_VALUE;

    /* LR0_ERRINT_PEn */
    *pLR0_ERRINT_Reg = (uint32)MCU_LR0_ERRINT_ENABLE_VALUE;

    /* Hold Register Access protection */
    /* ECCKCPROT */
    *Mcu_GpEccHwInfo->pECCKCPROTReg = MCU_ECC_ENABLE_REG_PROTECT_VALUE;
    #endif /* MCU_PROVIDE_RAM_STATE_ISR == STD_ON */
  }
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_ECCGetRamState
**
** Service ID         : None
**
** Description        : This service provides the actual status of the microcontroller RAM area.
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
** Return parameter   : Mcu_RamStateType
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : None
**
** Functions Invoked  : Mcu_ECCGetLramStatus, Mcu_ECCGetCramStatus, Mcu_ECCGetRramStatus
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_099
***********************************************************************************************************************/
#if (MCU_GET_RAM_STATE_API == STD_ON)
#if (MCU_PROVIDE_RAM_STATE_ISR != STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Mcu_RamStateType, MCU_PRIVATE_CODE) Mcu_ECCGetRamState(void)
{
  Mcu_RamStateType LulLRAMErrStatusData;
  Mcu_RamStateType LulCRAMErrStatusData;
  #if (MCU_RETENTION_RAM_SETTING == STD_ON)
  Mcu_RamStateType LulRRAMErrStatusData;
  #endif
  Mcu_RamStateType LddRamStatus;

  LulLRAMErrStatusData = MCU_RAMSTATE_INVALID;                                                                          /* PRQA S 2982 # JV-01 */
  LulCRAMErrStatusData = MCU_RAMSTATE_INVALID;                                                                          /* PRQA S 2982 # JV-01 */
  #if (MCU_RETENTION_RAM_SETTING == STD_ON)
  LulRRAMErrStatusData = MCU_RAMSTATE_INVALID;                                                                          /* PRQA S 2982 # JV-01 */
  #endif
  LddRamStatus = MCU_RAMSTATE_INVALID;

  LulLRAMErrStatusData = Mcu_ECCGetLramStatus();
  LulCRAMErrStatusData = Mcu_ECCGetCramStatus();
  #if (MCU_RETENTION_RAM_SETTING == STD_ON)
  LulRRAMErrStatusData = Mcu_ECCGetRramStatus();
  #endif

  if ((MCU_RAMSTATE_VALID == LulLRAMErrStatusData) && (MCU_RAMSTATE_VALID == LulCRAMErrStatusData)
  #if (MCU_RETENTION_RAM_SETTING == STD_ON)
  && (MCU_RAMSTATE_VALID == LulRRAMErrStatusData)                                                                       /* PRQA S 2982 # JV-01 */
  #endif
  )
  {
    /* Set the value of RAM error status(not error) */
    LddRamStatus = MCU_RAMSTATE_VALID;
  } /* else No action required */

  /* Return the value of RAM status result */
  return (LddRamStatus);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_PROVIDE_RAM_STATE_ISR != STD_ON */
#endif /* MCU_GET_RAM_STATE_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_ECCGetLramStatusPE
**
** Service ID         : None
**
** Description        : This service return each PE's LRAM status and Clear Error status
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
** Return parameter   : uint32 (Logical OR of PE's LRAM status)
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : LR0_SERSTR_PEx, LR0_DERSTR_PEx, LR0_SSTCLR_PEx, LR0_DSTCLR_PEx, LR0_OVFCLR_PEx
**
** Reference ID       : MCU_DUD_ACT_098, MCU_DUD_ACT_098_CRT001,
** Reference ID       : MCU_DUD_ACT_098_CRT002, MCU_DUD_ACT_098_REG001,
** Reference ID       : MCU_DUD_ACT_098_REG002, MCU_DUD_ACT_098_REG003,
** Reference ID       : MCU_DUD_ACT_098_REG004, MCU_DUD_ACT_098_REG005,
** Reference ID       : MCU_DUD_ACT_098_REG006
***********************************************************************************************************************/
#if (MCU_GET_RAM_STATE_API == STD_ON)
#if (MCU_PROVIDE_RAM_STATE_ISR != STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(uint32, MCU_PRIVATE_CODE)Mcu_ECCGetLramStatusPE(void)
{
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pLR0_ERRINT_Reg;                                                            /* PRQA S 3432 # JV-01 */
  uint8 LucPeCount;
  uint32 LulLRAMErrStatusData;

  LulLRAMErrStatusData = MCU_LONG_WORD_ZERO;

  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  for (LucPeCount = MCU_ZERO; LucPeCount < (uint8)MCU_TOTAL_PE_NUM; LucPeCount++)
  {
    /* Calculate LR0_ERRINT_PEn */
    pLR0_ERRINT_Reg =                                                                                                   /* PRQA S 0404 # JV-01 */
      (volatile uint32 *)(Mcu_GpEccHwInfo->pLR0_ERRINT_PE0Reg + (Mcu_GpEccHwInfo->ulLR0PEnOffset * (uint32)LucPeCount));/* PRQA S 0488, 3384 # JV-01, JV-01 */
    /* Get the value of RAM error status */
    /* LR0_SERSTR_PEn */
    LulLRAMErrStatusData |= (*(pLR0_ERRINT_Reg + Mcu_GpEccHwInfo->ulLR0SERSTROffset));                                  /* PRQA S 0404, 0488 # JV-01, JV-01 */
    /* LR0_DERSTR_PEn */
    LulLRAMErrStatusData |= (*(pLR0_ERRINT_Reg + Mcu_GpEccHwInfo->ulLR0DERSTROffset));                                  /* PRQA S 0404, 0488 # JV-01, JV-01 */
    /* LR0_OVFSTR_PEn */
    LulLRAMErrStatusData |= (*(pLR0_ERRINT_Reg + Mcu_GpEccHwInfo->ulLR0OVFSTROffset));                                  /* PRQA S 0404, 0488 # JV-01, JV-01 */

    /* Clear RAM error status */
    /* LR0_SSTCLR_PEn */
    *(pLR0_ERRINT_Reg + Mcu_GpEccHwInfo->ulLR0SSTCLROffset) = (uint32)MCU_LRAM_SST_CLR_VALUE;                           /* PRQA S 0488 # JV-01 */
    /* LR0_DSTCLR_PEn */
    *(pLR0_ERRINT_Reg + Mcu_GpEccHwInfo->ulLR0DSTCLROffset) = (uint32)MCU_LRAM_DST_CLR_VALUE;                           /* PRQA S 0488 # JV-01 */
    /* LR0_OVFCLR_PEn */
    *(pLR0_ERRINT_Reg + Mcu_GpEccHwInfo->ulLR0OVFCLROffset) = (uint32)MCU_LRAM_OVF_CLR_VALUE;                           /* PRQA S 0488 # JV-01 */
  }

  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  return (LulLRAMErrStatusData);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_PROVIDE_RAM_STATE_ISR != STD_ON */
#endif /* MCU_GET_RAM_STATE_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_ECCGetLramStatus
**
** Service ID         : None
**
** Description        : This service return LRAM status and Clear Error status
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
** Return parameter   : Mcu_RamStateType (MCU_RAMSTATE_INVALID, MCU_RAMSTATE_VALID)
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : Mcu_ECCGetLramStatusPE
**
** Registers Used     : LR1_SERSTR, LR1_DERSTR, LR1_SSTCLR, LR1_DSTCLR, LR1_OVFCLR
**
** Reference ID       : MCU_DUD_ACT_095, MCU_DUD_ACT_095_CRT001, MCU_DUD_ACT_095_CRT002,
** Reference ID       : MCU_DUD_ACT_095_REG001,
** Reference ID       : MCU_DUD_ACT_095_REG002,
** Reference ID       : MCU_DUD_ACT_095_REG003
***********************************************************************************************************************/
#if (MCU_GET_RAM_STATE_API == STD_ON)
#if (MCU_PROVIDE_RAM_STATE_ISR != STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Mcu_RamStateType, MCU_PRIVATE_CODE) Mcu_ECCGetLramStatus(void)
{
  uint32 LulLRAMErrStatusData;
  Mcu_RamStateType LddRamStatus;


  LddRamStatus = MCU_RAMSTATE_INVALID;
  LulLRAMErrStatusData = Mcu_ECCGetLramStatusPE();

  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  if(NULL_PTR != Mcu_GpEccHwInfo->pLR1_SERSTRReg)
  {
    LulLRAMErrStatusData |= (*Mcu_GpEccHwInfo->pLR1_SERSTRReg);                                                         /* PRQA S 0404 # JV-01 */
  } /* else No action is required */

  if(NULL_PTR != Mcu_GpEccHwInfo->pLR1_DERSTRReg)
  {
    LulLRAMErrStatusData |= (*Mcu_GpEccHwInfo->pLR1_DERSTRReg);                                                         /* PRQA S 0404 # JV-01 */
  } /* else No action is required */

  if(NULL_PTR != Mcu_GpEccHwInfo->pLR1_OVFSTRReg)
  {
    LulLRAMErrStatusData |= (*Mcu_GpEccHwInfo->pLR1_OVFSTRReg);                                                         /* PRQA S 0404 # JV-01 */
  } /* else No action is required */

  if (MCU_LONG_WORD_ZERO == LulLRAMErrStatusData)
  {
    /* Set the value of RAM error status(not error) */
    LddRamStatus = MCU_RAMSTATE_VALID;
  } /* else No action required */

  /* Clear RAM error status */
  if(NULL_PTR != Mcu_GpEccHwInfo->pLR1_SSTCLRReg)
  {
    *Mcu_GpEccHwInfo->pLR1_SSTCLRReg = (uint32)MCU_LRAM_SST_CLR_VALUE;
  } /* else No action is required */

  if(NULL_PTR != Mcu_GpEccHwInfo->pLR1_DSTCLRReg)
  {
    *Mcu_GpEccHwInfo->pLR1_DSTCLRReg = (uint32)MCU_LRAM_DST_CLR_VALUE;
  } /* else No action is required */

  if(NULL_PTR != Mcu_GpEccHwInfo->pLR1_OVFCLRReg)
  {
    *Mcu_GpEccHwInfo->pLR1_OVFCLRReg = (uint32)MCU_LRAM_OVF_CLR_VALUE;
  } /* else No action is required */

  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  return (LddRamStatus);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_PROVIDE_RAM_STATE_ISR != STD_ON */
#endif /* MCU_GET_RAM_STATE_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_ECCGetCramStatus
**
** Service ID         : None
**
** Description        : This service return CRAM status and Clear Error status
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
** Return parameter   : Mcu_RamStateType (MCU_RAMSTATE_INVALID, MCU_RAMSTATE_VALID)
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : CR_SERSTR, CR_DERSTR, CR_SSTCLR, CR_DSTCLR, CR_OVFCLR
**
** Reference ID       : MCU_DUD_ACT_096, MCU_DUD_ACT_096_CRT001,
** Reference ID       : MCU_DUD_ACT_096_CRT002, MCU_DUD_ACT_096_REG001,
** Reference ID       : MCU_DUD_ACT_096_REG002, MCU_DUD_ACT_096_REG003,
** Reference ID       : MCU_DUD_ACT_096_REG004, MCU_DUD_ACT_096_REG005,
** Reference ID       : MCU_DUD_ACT_096_REG006
***********************************************************************************************************************/
#if (MCU_GET_RAM_STATE_API == STD_ON)
#if (MCU_PROVIDE_RAM_STATE_ISR != STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Mcu_RamStateType, MCU_PRIVATE_CODE) Mcu_ECCGetCramStatus(void)
{
  uint32 LulCRAMErrStatusData;

  Mcu_RamStateType LddRamStatus;

  LulCRAMErrStatusData = MCU_LONG_WORD_ZERO;
  LddRamStatus = MCU_RAMSTATE_INVALID;

  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  /* Get the value of RAM error status */
  LulCRAMErrStatusData |= (*Mcu_GpEccHwInfo->pCR_SERSTRReg);                                                            /* PRQA S 0404 # JV-01 */

  LulCRAMErrStatusData |= (*Mcu_GpEccHwInfo->pCR_DERSTRReg);                                                            /* PRQA S 0404 # JV-01 */

  LulCRAMErrStatusData |= (*Mcu_GpEccHwInfo->pCR_OVFSTRReg);                                                            /* PRQA S 0404 # JV-01 */

  if (MCU_LONG_WORD_ZERO == LulCRAMErrStatusData)
  {
    /* Set the value of RAM error status(not error) */
    LddRamStatus = MCU_RAMSTATE_VALID;
  } /* else No action is required */

  /* Clear RAM error status */
  *Mcu_GpEccHwInfo->pCR_SSTCLRReg = (uint32)MCU_CRAM_SST_CLR_VALUE;

  *Mcu_GpEccHwInfo->pCR_DSTCLRReg = (uint32)MCU_CRAM_DST_CLR_VALUE;

  *Mcu_GpEccHwInfo->pCR_OVFCLRReg = (uint32)MCU_CRAM_OVF_CLR_VALUE;

  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  return (LddRamStatus);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_PROVIDE_RAM_STATE_ISR != STD_ON */
#endif /* MCU_GET_RAM_STATE_API == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_ECCSetRramEccInt
**
** Service ID         : None
**
** Description        : This service clear Retention RAM ECC Error and set ECC Error Interrupt
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
** Registers Used     : RRAMECCKCPROT, RRAMECCCTL
**
** Reference ID       : MCU_DUD_ACT_091, MCU_DUD_ACT_091_REG001, MCU_DUD_ACT_091_REG002, MCU_DUD_ACT_091_REG003
***********************************************************************************************************************/
#if (MCU_RETENTION_RAM_SETTING == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_ECCSetRramEccInt(void)
{
  /* Release Register Access Protection */
  *Mcu_GpEccHwInfo->pRRAMECCKCPROTReg = MCU_ECC_DISABLE_REG_PROTECT_VALUE;

  /* Clear error flags in RRAMECCCTL */
  if(NULL_PTR != Mcu_GpEccHwInfo->pRRAMECCCTLReg)
  {
    *Mcu_GpEccHwInfo->pRRAMECCCTLReg = MCU_RRAM_SST_CLR_VALUE;
  } /* else No action is required */

  /* Hold Register Access protection */
  *Mcu_GpEccHwInfo->pRRAMECCKCPROTReg = MCU_ECC_ENABLE_REG_PROTECT_VALUE;

  #if (MCU_PROVIDE_RAM_STATE_ISR == STD_ON)
  /* Release Register Access Protection */
  *Mcu_GpEccHwInfo->pRRAMECCKCPROTReg = MCU_ECC_DISABLE_REG_PROTECT_VALUE;

  /* RRAM Error control setting */
  if(NULL_PTR != Mcu_GpEccHwInfo->pRRAMECCCTLReg)
  {
    *Mcu_GpEccHwInfo->pRRAMECCCTLReg = MCU_RRAM_ECCCTL_ENABLE_VALUE;
  } /* else No action is required */

  /* Hold Register Access protection */
  *Mcu_GpEccHwInfo->pRRAMECCKCPROTReg = MCU_ECC_ENABLE_REG_PROTECT_VALUE;
  #endif /* MCU_PROVIDE_RAM_STATE_ISR == STD_ON */
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_RETENTION_RAM_SETTING == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_ECCGetRramStatus
**
** Service ID         : None
**
** Description        : This service return Retention RAM status and Clear Error status
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
** Return parameter   : Mcu_RamStateType (MCU_RAMSTATE_INVALID, MCU_RAMSTATE_VALID)
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : RRAMECCKCPROT, RRAMECCCTL
**
** Reference ID       : MCU_DUD_ACT_092, MCU_DUD_ACT_092_CRT001, MCU_DUD_ACT_092_CRT002,
** Reference ID       : MCU_DUD_ACT_092_REG001, MCU_DUD_ACT_092_REG002, MCU_DUD_ACT_092_REG003
***********************************************************************************************************************/
#if ((MCU_GET_RAM_STATE_API == STD_ON) && (MCU_RETENTION_RAM_SETTING == STD_ON))
#if (MCU_PROVIDE_RAM_STATE_ISR != STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Mcu_RamStateType, MCU_PRIVATE_CODE) Mcu_ECCGetRramStatus(void)
{
  uint32 LulRRAMErrStatusData;

  Mcu_RamStateType LddRamStatus;

  LulRRAMErrStatusData = MCU_LONG_WORD_ZERO;
  LddRamStatus = MCU_RAMSTATE_INVALID;

  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  /* Indicates whether Data ECC 1-bit error has occurred. */
  LulRRAMErrStatusData |= ((*Mcu_GpEccHwInfo->pRRAMECCCTLReg) & MCU_ECC_ECER1F_MASK);                                   /* PRQA S 0404 # JV-01 */

  /* Indicates whether Data ECC 2-bit error has occurred. */
  LulRRAMErrStatusData |= ((*Mcu_GpEccHwInfo->pRRAMECCCTLReg) & MCU_ECC_ECER2F_MASK);                                   /* PRQA S 0404 # JV-01 */

  /* Indicates whether Data ECC overflow error has occurred. */
  LulRRAMErrStatusData |= ((*Mcu_GpEccHwInfo->pRRAMECCCTLReg) & MCU_ECC_ECOVFF_MASK);                                   /* PRQA S 0404 # JV-01 */

  if (MCU_LONG_WORD_ZERO == LulRRAMErrStatusData)
  {
    /* Set the value of RAM error status (not error) */
    LddRamStatus = MCU_RAMSTATE_VALID;
  } /* else No action is required */

  /* Release Register Access Protection */
  *Mcu_GpEccHwInfo->pRRAMECCKCPROTReg = MCU_ECC_DISABLE_REG_PROTECT_VALUE;

  /* Clear RAM error status */
  if(NULL_PTR != Mcu_GpEccHwInfo->pRRAMECCCTLReg)
  {
    *Mcu_GpEccHwInfo->pRRAMECCCTLReg = MCU_RRAM_SST_CLR_VALUE;
  } /* else No action is required */

  /* Hold Register Access protection */
  *Mcu_GpEccHwInfo->pRRAMECCKCPROTReg = MCU_ECC_ENABLE_REG_PROTECT_VALUE;

  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  return (LddRamStatus);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_PROVIDE_RAM_STATE_ISR != STD_ON */
#endif /* MCU_GET_RAM_STATE_API == STD_ON */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
