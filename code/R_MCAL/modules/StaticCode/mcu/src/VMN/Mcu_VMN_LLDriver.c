/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_VMN_LLDriver.c                                                                                  */
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
 *                        - Update Mcu_VMNSetVoltageMonitorDiag to add MCU_VMON_VMONF_BIT_MASK
 * 2.0.1:  10/12/2023   : Update Mcu_VMNSetDelayMonitorDiag to add step Reset DMON
 * 2.0.0:  04/08/2023   : Add QAC message 1006, 2814
 *                        Remove redundant QAC message 0791
 * 1.5.0:  28/03/2023   : Update Mcu_VMNStopDelayMonitor to check MOSC stop operation in chip standby mode
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
#define MCU_VMN_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    MCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define MCU_VMN_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    MCU_AR_RELEASE_MINOR_VERSION_VALUE
#define MCU_VMN_LLDRIVER_C_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MCU_VMN_LLDRIVER_C_SW_MAJOR_VERSION            MCU_SW_MAJOR_VERSION_VALUE
#define MCU_VMN_LLDRIVER_C_SW_MINOR_VERSION            MCU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (MCU_VMN_LLDRIVER_AR_RELEASE_MAJOR_VERSION != MCU_VMN_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "MCU_VMN_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (MCU_VMN_LLDRIVER_AR_RELEASE_MINOR_VERSION != MCU_VMN_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "MCU_VMN_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (MCU_VMN_LLDRIVER_AR_RELEASE_REVISION_VERSION != MCU_VMN_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "MCU_VMN_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (MCU_VMN_LLDRIVER_SW_MAJOR_VERSION != MCU_VMN_LLDRIVER_C_SW_MAJOR_VERSION)
#error "MCU_VMN_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (MCU_VMN_LLDRIVER_SW_MINOR_VERSION != MCU_VMN_LLDRIVER_C_SW_MINOR_VERSION)
#error "MCU_VMN_LLDriver.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/**********************************************************************************************************************/
/**                                             Internal Function Prototypes                                         **/
/**********************************************************************************************************************/
#if (MCU_VMON_DIAG_OPERATION == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

STATIC FUNC(uint8, MCU_PRIVATE_CODE) Mcu_VMNGetVmonDiagExpectValue(void);

#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_VMON_DIAG_OPERATION == STD_ON */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name      : Mcu_VMNSetVoltageMonitorDiag
**
** Service ID         : None
**
** Description        : This service set Voltage Monitor Diagnosis Function
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
** Return parameter   : Std_ReturnType (E_OK, E_NOT_OK)
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpConfigPtr
**
** Function Invoked   : Mcu_VMNGetVmonDiagExpectValue
**
** Registers Used     : VMONKCPROT, VMONF, VMONFC, VMONDIAGME, VMONDMASK,
**                      VMONDIAG, OPBT4, ISOVDDDE, AWOVDDDE, VMONDIAGMEW
**
** Reference ID       : MCU_DUD_ACT_030,
** Reference ID       : MCU_DUD_ACT_030_REG001, MCU_DUD_ACT_030_REG002, MCU_DUD_ACT_030_REG003,
** Reference ID       : MCU_DUD_ACT_030_REG004, MCU_DUD_ACT_030_REG005, MCU_DUD_ACT_030_REG006,
** Reference ID       : MCU_DUD_ACT_030_REG007, MCU_DUD_ACT_030_REG008, MCU_DUD_ACT_030_REG009,
** Reference ID       : MCU_DUD_ACT_030_REG010, MCU_DUD_ACT_030_REG011, MCU_DUD_ACT_030_REG012
***********************************************************************************************************************/
#if (MCU_VMON_DIAG_OPERATION == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_VMNSetVoltageMonitorDiag(void)                                               /* PRQA S 3006 # JV-01 */
{
  Std_ReturnType LucReturnValue;
  P2CONST(Mcu_VmonSettingType, MCU_CONST, MCU_CONFIG_DATA) LpVmonSetting;
  volatile uint32 LulCount;
  volatile uint8 LucVmonDiagExpectValue;
  LucVmonDiagExpectValue = MCU_ZERO;
  /* Get the address to Voltage monitor configuration structure */
  LpVmonSetting = (P2CONST(Mcu_VmonSettingType, MCU_CONST, MCU_CONFIG_DATA))(Mcu_GpConfigPtr->pVmonSetting);            /* PRQA S 0316 # JV-01 */

  /* Initialize the following variables */
  LucReturnValue = E_OK;

  *Mcu_GpVmonHwInfo->pVMONKCPROTReg = MCU_VMON_DISABLE_REG_PROTECT_VALUE;

  /* Check VMONF register value */
  LulCount = (uint32)MCU_VMONDIAG_CLEARRETRY_MAX;
  while ((MCU_VMON_VMONF_NO_VIOLATION != (*Mcu_GpVmonHwInfo->pVMONFReg))  && (LulCount > (uint32)MCU_ZERO))             /* PRQA S 0404, 3415, 3416 # JV-01, JV-01, JV-01 */
  {
    /* Clear VMONF violation */
    *Mcu_GpVmonHwInfo->pVMONFCReg = MCU_VMON_VMONFC_ALL_CLEAR_VALUE;
    LulCount--;                                                                                                         /* PRQA S 3384, 3387 # JV-01, JV-01 */
  }
  /* VMONF check */
  if (MCU_VMON_VMONF_NO_VIOLATION != (*Mcu_GpVmonHwInfo->pVMONFReg))                                                    /* PRQA S 0404 # JV-01 */
  {
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Check VMONDIAGME register value */
    if (MCU_VMON_VMONDIAGME_CANNOT_ENABLE_VALUE != *Mcu_GpVmonHwInfo->pVMONDIAGMEReg)                                   /* PRQA S 0404 # JV-01 */
    {
      /* Set VMONDMASK to all reset request masked */
      *Mcu_GpVmonHwInfo->pVMONDMASKReg = MCU_VMON_VMONDMASK_ALL_MASK_VALUE;

      /* Set VMONDIAG to all detection enable */
      *Mcu_GpVmonHwInfo->pVMONDIAGReg = MCU_VMON_VMONDIAG_ALL_DETECTION_ENABLE_VALUE;

      /* Wait specific time */
      /* Wait for switching clock sources */
      LulCount = (uint32)MCU_VMON_FILTER_WAIT_CNT_NUM;
      while (MCU_LONG_WORD_ZERO < LulCount)                                                                             /* PRQA S 3416 # JV-01 */
      {
        LulCount--;                                                                                                     /* PRQA S 3384, 3387 # JV-01, JV-01 */
        EXECUTE_SYNCP();                                                                                                /* PRQA S 1006 # JV-01 */
      }
      /* Check VMONF register expected value */
      LucVmonDiagExpectValue = Mcu_VMNGetVmonDiagExpectValue();
      if (LucVmonDiagExpectValue != (*Mcu_GpVmonHwInfo->pVMONFReg & MCU_VMON_VMONF_BIT_MASK))                           /* PRQA S 0404, 3416 # JV-01, JV-01 */
      {
        LucReturnValue = E_NOT_OK;
      }
      else
      {
        /* Set VMONDIAG to all detection disable */
        *Mcu_GpVmonHwInfo->pVMONDIAGReg = MCU_VMON_VMONDIAG_NO_DETECTION_ENABLE_VALUE;

        /* Wait specific time */
        /* Wait for switching clock sources */
        LulCount = (uint32)MCU_VMON_WAIT_CNT_NUM;
        while (LulCount > MCU_LONG_WORD_ZERO)                                                                           /* PRQA S 3416 # JV-01 */
        {
          LulCount--;                                                                                                   /* PRQA S 3384, 3387 # JV-01, JV-01 */
          EXECUTE_SYNCP();                                                                                              /* PRQA S 1006 # JV-01 */
        }

        LulCount = (uint32)MCU_VMONDIAG_CLEARRETRY_MAX;
        /* Clear VMONF violation */
        do {
          /* Set MCU_VMONFC until MCU_VMONF all clear */
          *Mcu_GpVmonHwInfo->pVMONFCReg = MCU_VMON_VMONFC_ALL_CLEAR_VALUE;
           EXECUTE_SYNCP();                                                                                             /* PRQA S 1006 # JV-01 */
          LulCount--;                                                                                                   /* PRQA S 3384, 3387 # JV-01, JV-01 */
        } while ((MCU_VMON_VMONF_NO_VIOLATION != (*Mcu_GpVmonHwInfo->pVMONFReg)) && (LulCount > (uint32)MCU_ZERO));     /* PRQA S 0404, 3415, 3416 # JV-01, JV-01, JV-01 */
        if (MCU_VMON_VMONF_NO_VIOLATION != (*Mcu_GpVmonHwInfo->pVMONFReg))                                              /* PRQA S 0404 # JV-01 */
        {
          LucReturnValue = E_NOT_OK;
        }
        else
        {
          if (NULL_PTR != Mcu_GpVmonHwInfo->pVMONDMASKReg)
          {
            /* Clear MCU_VMONDMASK */
            (*Mcu_GpVmonHwInfo->pVMONDMASKReg) = MCU_VMON_VMONDMASK_ALL_CLEAR_VALUE;
          } /* else No action is required */

          /* Set ISOVDDDE.ISOVDDCIRREN  */
          (*Mcu_GpVmonHwInfo->pISOVDDDEReg) |= LpVmonSetting->ucVMONISOVDDDEValue;                                      /* PRQA S 0404 # JV-01 */

          if (NULL_PTR != Mcu_GpVmonHwInfo->pVDD2DEReg)
          {
            /* Set VDD2DE.VDD2CIRREN  */
            (*Mcu_GpVmonHwInfo->pVDD2DEReg) |= LpVmonSetting->ucVMONVDD2DEValue;                                        /* PRQA S 0404 # JV-01 */
          } /* else No action is required */

          /* Set VCCDE.VCCCIRREN */
          (*Mcu_GpVmonHwInfo->pVCCDEReg) |= LpVmonSetting->ucVMONVCCDEValue;                                            /* PRQA S 0404 # JV-01 */

          /* Set E0VCCDE.E0VCCCIRREN */
          (*Mcu_GpVmonHwInfo->pE0VCCDEReg) |= LpVmonSetting->ucVMONE0VCCDEValue;                                        /* PRQA S 0404 # JV-01 */

          /* VMONDIAGME set to "VMON DIAG cannot enable" */
          (*Mcu_GpVmonHwInfo->pVMONDIAGMEWReg) = MCU_VMON_VMONDIAGME_CANNOT_ENABLE_VALUE;
        }
      }
    } /* else Already done VMONDIAG */
  }
  (*Mcu_GpVmonHwInfo->pVMONKCPROTReg) = MCU_VMON_ENABLE_REG_PROTECT_VALUE;

  return(LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_VMON_DIAG_OPERATION == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_VMNGetVmonDiagExpectValue
**
** Service ID         : None
**
** Description        : Get VMON Diagnostic expected value for VMONF register
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
** Return parameter   : LucVmonDiagExpectValue
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : OPBT4
**
** Reference ID       : MCU_DUD_ACT_101, MCU_DUD_ACT_101_REG001
***********************************************************************************************************************/
#if (MCU_VMON_DIAG_OPERATION == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(uint8, MCU_PRIVATE_CODE) Mcu_VMNGetVmonDiagExpectValue(void)
{
  uint8 LucVmonDiagExpectValue;
  uint8 LucCount;
  P2CONST(Mcu_VmonSettingType, MCU_CONST, MCU_CONFIG_DATA) LpVmonSetting;

  /* Set init and disable expect value */
  LucVmonDiagExpectValue = MCU_VMON_VMONF_DIAG_DEFAULT_VALUE;
  /* Get the address to Voltage monitor configuration structure */
  LpVmonSetting = (P2CONST(Mcu_VmonSettingType, MCU_CONST, MCU_CONFIG_DATA))(Mcu_GpConfigPtr->pVmonSetting);            /* PRQA S 0316 # JV-01 */
  for (LucCount = MCU_ZERO; LucCount < MCU_OPBT4_NUMBER_BIT_CHECK; LucCount++)
  {
    /* Get the address to Voltage monitor configuration structure */
    /* Check dectection enable bit */
    if (LpVmonSetting->pVmonOPBT4Setting[LucCount].ulVmonOPBT4BitPosition ==                                            /* PRQA S 0404 # JV-01 */
                  (*(Mcu_GpVmonHwInfo->pOPBT4Reg) & LpVmonSetting->pVmonOPBT4Setting[LucCount].ulVmonOPBT4BitPosition))
    {
      LucVmonDiagExpectValue |= LpVmonSetting->pVmonOPBT4Setting[LucCount].ucVmonVMONFBitPosition;
    } /* else No action required */
  }

  return (LucVmonDiagExpectValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_VMON_DIAG_OPERATION == STD_ON */

#if (MCU_DMON_DIAG_OPERATION == STD_ON)
/***********************************************************************************************************************
** Function Name      : Mcu_VMNSetDelayMonitorDiag
**
** Service ID         : None
**
** Description        : This service set Delay Monitor Diag Function and Enable Delay Monitor
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
** Return parameter   : Std_ReturnType (E_OK, E_NOT_OK)
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpConfigPtr
**
** Function Invoked   : Mcu_CLMEnable
**
** Registers Used     : DMONKCPROT0, DMONKCPROT2, DMONTEST, DMONF, DMONFC, DMONFCR, DMONDE, DMONDIAG, DMONDIAGMEW
**
** Reference ID       : MCU_DUD_ACT_031,
** Reference ID       : MCU_DUD_ACT_031_REG001, MCU_DUD_ACT_031_REG002, MCU_DUD_ACT_031_REG003,
** Reference ID       : MCU_DUD_ACT_031_REG004, MCU_DUD_ACT_031_REG005, MCU_DUD_ACT_031_REG006,
** Reference ID       : MCU_DUD_ACT_031_REG007, MCU_DUD_ACT_031_REG008, MCU_DUD_ACT_031_REG009,
** Reference ID       : MCU_DUD_ACT_031_REG010, MCU_DUD_ACT_031_REG011, MCU_DUD_ACT_031_REG012
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_VMNSetDelayMonitorDiag(void)                                                 /* PRQA S 3006 # JV-01 */
{
  Std_ReturnType LucReturnValue;
  P2CONST(Mcu_DmonSettingType, MCU_CONST, MCU_CONFIG_DATA) LpDmonSetting;
  volatile uint32 LulCount;

  /* Get the address to DMON configuration structure */
  LpDmonSetting = (P2CONST(Mcu_DmonSettingType, MCU_CONST, MCU_CONFIG_DATA))(Mcu_GpConfigPtr->pDmonSetting);            /* PRQA S 0316 # JV-01 */

  /* Initialize the following variables */
  LucReturnValue = E_OK;

  /* Check DMONDIAGME register value */
  if (MCU_DMON_DMONDIAGME_CAN_ENABLE_VALUE == (*Mcu_GpDmonHwInfo->pDMONDIAGMEReg))                                      /* PRQA S 0404 # JV-01 */
  {
    #if (MCU_CLMA_OPERATION == STD_ON)
    /* When Main OSC is stable */
    /* Enable CLMA1 for E2x devices or CLMA0 for U2Ax devices */
    LucReturnValue = Mcu_CLMEnable();
    #endif /* MCU_CLMA_OPERATION == STD_ON */

    /* Disable key code protection */
    *Mcu_GpDmonHwInfo->pDMONKCPROT2Reg = MCU_DMON_DISABLE_REG_PROTECT_VALUE;
    /* Reset Delay Monitor */
    *Mcu_GpDmonHwInfo->pDMONTESTReg = MCU_DMONTEST_RESET_ASSERT_VALUE;
    /* Release Delay Monitor */
    *Mcu_GpDmonHwInfo->pDMONTESTReg = MCU_DMONTEST_RESET_RELEASE_VALUE;
    /* Enable key code protection */
    *Mcu_GpDmonHwInfo->pDMONKCPROT2Reg = MCU_DMON_ENABLE_REG_PROTECT_VALUE;

    if (E_NOT_OK == LucReturnValue)
    {
      /* Clock source Main OSC is not stable and do nothing */
    }
    else
    {
      *Mcu_GpDmonHwInfo->pDMONKCPROT0Reg = MCU_DMON_DISABLE_REG_PROTECT_VALUE;
      #if (MCU_VMON_DIAG_OPERATION == STD_ON)
      if (MCU_VMON_ISOVDDDE_LOWVOLTAGE_DETECTION_ENABLE ==                                                              /* PRQA S 0404 # JV-01 */
          (uint8)(MCU_VMON_ISOVDDDE_LOWVOLTAGE_DETECTION_ENABLE & (*Mcu_GpVmonHwInfo->pISOVDDDEReg)))
      {
      #endif /* MCU_VMON_DIAG_OPERATION == STD_ON */
        /* Start DMON DIAG */
        /* Check DMONF register value */
        LulCount = (uint32)MCU_DMONDIAG_CLEARRETRY_MAX;
        while ((MCU_DMON_DMONF_NO_ERROR_OCCURRED != (*Mcu_GpDmonHwInfo->pDMONFReg)) && (LulCount > (uint32)MCU_ZERO))   /* PRQA S 0404, 3415, 3416 # JV-01, JV-01, JV-01 */
        {
          /* Clear DMONF violation */
          *Mcu_GpDmonHwInfo->pDMONFCReg = MCU_DMON_DMONFC_CLEAR_VALUE;
          LulCount--;                                                                                                   /* PRQA S 3384, 3387 # JV-01, JV-01 */
        }

        if (MCU_DMON_DMONF_NO_ERROR_OCCURRED != (*Mcu_GpDmonHwInfo->pDMONFReg))                                         /* PRQA S 0404 # JV-01 */
        {
          LucReturnValue = E_NOT_OK;
        }
        else
        {
          /* Check digital noise filter */
          #if (MCU_DMON_DIAG_FILTER_OPERATION == STD_ON)
          /* Set DMONFCR */
          *Mcu_GpDmonHwInfo->pDMONFCRReg = LpDmonSetting->ulDmonDMONFCRValue;
          /* Set DMONDE to 0x00000009 */
          *Mcu_GpDmonHwInfo->pDMONDEReg = MCU_DMON_DMONDE_FILTER_LOWDELAY_DETECTION_ENABLE;
          #else
          /* Set DMONDE to 0x00000001 */
          *Mcu_GpDmonHwInfo->pDMONDEReg = MCU_DMON_DMONDELOWDELAY_DETECTION_ENABLE;
          #endif /* MCU_DMON_DIAG_FILTER_OPERATION == STD_ON */
          /* Set DMONDIAG */
          *Mcu_GpDmonHwInfo->pDMONDIAGReg = MCU_DMON_DMONDIAG_ERROR_INJECTION_ENABLE;
          /* Wait specified time */
          /* Wait for switching clock sources */
          LulCount = (uint32)MCU_DMON_WAIT_CNT_NUM;
          while (LulCount > (uint32)MCU_ZERO)                                                                           /* PRQA S 3416 # JV-01 */
          {
            LulCount--;                                                                                                 /* PRQA S 3384, 3387 # JV-01, JV-01 */
            EXECUTE_SYNCP();                                                                                            /* PRQA S 1006 # JV-01 */
          }
          /* Check DMONF register value */
          if (MCU_DMON_DMONF_ERROR_OCCURRED != (*Mcu_GpDmonHwInfo->pDMONFReg))                                          /* PRQA S 0404 # JV-01 */
          {
            LucReturnValue = E_NOT_OK;
          }
          else
          {
            /* Set DMONDIAG to 0x00000000 */
            *Mcu_GpDmonHwInfo->pDMONDIAGReg = MCU_DMON_DMONDIAG_ERROR_INJECTION_DISABLE;

            LulCount = (uint32)MCU_DMONDIAG_CLEARRETRY_MAX;
            do
            {
              /* Set DMONFC to 0x00000001 and check until MCU_DMONF is set to 0x00000000 */
              *Mcu_GpDmonHwInfo->pDMONFCReg = MCU_DMON_DMONFC_CLEAR_VALUE;
              LulCount--;                                                                                               /* PRQA S 3384, 3387 # JV-01, JV-01 */
            } while ((MCU_DMON_DMONF_NO_ERROR_OCCURRED !=                                                               /* PRQA S 0404 # JV-01 */
                      (*Mcu_GpDmonHwInfo->pDMONFReg)) && (LulCount > (uint32)MCU_ZERO));                                /* PRQA S 3415, 3416 # JV-01, JV-01 */
            if (MCU_DMON_DMONF_NO_ERROR_OCCURRED != (*Mcu_GpDmonHwInfo->pDMONFReg))                                     /* PRQA S 0404 # JV-01 */
            {
              LucReturnValue = E_NOT_OK;
            } /* else No action required */
          }
          /* End DMON Diagnosis */
        }
      #if (MCU_VMON_DIAG_OPERATION == STD_ON)
      }
      else
      {
       /* ISOVDDDE.ISOVDDLDE = 0 is prohibited when DMONDE.DMONLDE = 1 */
       /* No action required */
      }
      #endif /* MCU_VMON_DIAG_OPERATION == STD_ON */

      if (E_OK == LucReturnValue)
      {
        /* Reset permission  */
        /* Check if ISOVDDE.ISOVDDCIRREN[2:0]! = 110B or 111B */
        #if (MCU_VMON_DIAG_OPERATION == STD_ON)
        if (((uint8)((*Mcu_GpVmonHwInfo->pISOVDDDEReg) & MCU_ISOVDDCIRREN_BIT_MASK) ==                                  /* PRQA S 0404 # JV-01 */
              MCU_ISOVDDCIRREN_LOW_DETECTION_ID111) ||
              ((uint8)((*Mcu_GpVmonHwInfo->pISOVDDDEReg) & MCU_ISOVDDCIRREN_BIT_MASK) ==
              MCU_ISOVDDCIRREN_LOW_DETECTION_ID110))
        {
          *Mcu_GpDmonHwInfo->pDMONDEReg |= LpDmonSetting->ulDmonDMONDEValue;                                            /* PRQA S 0404 # JV-01 */
        }
        else
        #endif /* MCU_VMON_DIAG_OPERATION == STD_ON */
        {
          /* Setting for DMONCIRREN is not permitted */
          /* Setting for DMONDE except Permit DMON_REQRESET notification */
          *Mcu_GpDmonHwInfo->pDMONDEReg |= (LpDmonSetting->ulDmonDMONDEValue & (~MCU_DMONCIRREN_BIT_MASK));             /* PRQA S 0404 # JV-01 */
        }
        /* Set Digital Noise Filter */
        #if (MCU_DMON_DIAG_FILTER_OPERATION == STD_ON)
        *Mcu_GpDmonHwInfo->pDMONFCRReg |= LpDmonSetting->ulDmonDMONFCRValue;                                            /* PRQA S 0404 # JV-01 */
        #endif /* MCU_DMON_DIAG_FILTER_OPERATION == STD_ON */
        /* Delay Monitor Start */
        *Mcu_GpDmonHwInfo->pDMONDIAGMEWReg = MCU_DMON_DMONDIAGME_CANNOT_ENABLE_VALUE;
      } /* else No action required */
      *Mcu_GpDmonHwInfo->pDMONKCPROT0Reg = MCU_DMON_ENABLE_REG_PROTECT_VALUE;
    }
  } /* else No action required */
  /* Return the value of setting Delay Monitor Diag Function result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_VMNStopDelayMonitor
**
** Service ID         : None
**
** Description        : This service to stop DMON before enter standby mode
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
** Registers Used     : DMONTEST, DMONKCPROT2
**
** Reference ID       : MCU_DUD_ACT_032, MCU_DUD_ACT_032_REG001
** Reference ID       : MCU_DUD_ACT_032_REG002, MCU_DUD_ACT_032_REG003
***********************************************************************************************************************/
#if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_VMNStopDelayMonitor(void)
{
  /* When MOSC stop operation in chip standby mode*/
  if (MCU_MOSC_STOP_IN_STANDBYMODE == (*(Mcu_GpClockHwInfo->pMainOscSTPMReg) & MCU_MOSCSTPM_MOSCSTPMASK))               /* PRQA S 0404 # JV-01 */
  {
  /* Disable key code protection */
  *Mcu_GpDmonHwInfo->pDMONKCPROT2Reg = MCU_DMON_DISABLE_REG_PROTECT_VALUE;
  /* Stop the DMON operation by resetting DMON */
  *Mcu_GpDmonHwInfo->pDMONTESTReg = MCU_DMONTEST_RESET_ASSERT_VALUE;
  /* Enable key code protection */
  *Mcu_GpDmonHwInfo->pDMONKCPROT2Reg = MCU_DMON_ENABLE_REG_PROTECT_VALUE;
  } /* else No action required */
  /* Main OSC is not stop in chip standby mode */
  /* No need to stop DMON */
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_MODE_TRANSITION_SUPPORT */

/***********************************************************************************************************************
** Function Name      : Mcu_VMNRestartDelayMonitor
**
** Service ID         : None
**
** Description        : This service to restart DMON after wake-up from standby mode
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
** Registers Used     : DMONTEST, DMONKCPROT2
**
** Reference ID       : MCU_DUD_ACT_103, MCU_DUD_ACT_103_REG001, MCU_DUD_ACT_103_REG002, MCU_DUD_ACT_103_REG003
***********************************************************************************************************************/
#if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, MCU_PRIVATE_CODE) Mcu_VMNRestartDelayMonitor(void)
{
  /* Disable key code protection */
  *Mcu_GpDmonHwInfo->pDMONKCPROT2Reg = MCU_DMON_DISABLE_REG_PROTECT_VALUE;
  /* Reset Delay Monitor */
  *Mcu_GpDmonHwInfo->pDMONTESTReg = MCU_DMONTEST_RESET_RELEASE_VALUE;
  /* Enable key code protection */
  *Mcu_GpDmonHwInfo->pDMONKCPROT2Reg = MCU_DMON_ENABLE_REG_PROTECT_VALUE;
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_MODE_TRANSITION_SUPPORT == STD_ON */

#endif /* MCU_DMON_DIAG_OPERATION == STD_ON */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
