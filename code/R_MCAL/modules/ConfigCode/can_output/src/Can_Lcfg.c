/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can_Lcfg.c                                                                                          */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2023, 2024 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains link time parameters.                                                                           */
/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                                         */
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
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s)        */
/* and/or the Application.                                                                                            */
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
/*              Devices:        R7F7025BxFABC                                                                         */
/*====================================================================================================================*/


/***********************************************************************************************************************
**                      Revision Control History                                                                      **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Generation Tool Version                                                                       **
***********************************************************************************************************************/
/*                                                                                                                    */
/* TOOL VERSION:  CanU2Bx-E.dll version: 2.5.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\can\generator\U2B24-E\R2211_can_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_can.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuM\xml\EcuM_can.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_can.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_can.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:49:20
 */


/***********************************************************************************************************************
**                      Instance Index                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
/* CAN Link-time configuration header */
#include "Can.h"
#include "Can_LTTypes.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/* Message (2:0303)    : [I] Cast between a pointer to volatile object and an integral type.                          */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569                             */
/*                       REFERENCE - ISO-6.3.4 Semantics                                                              */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : #include directives should only be preceded by preprocessor directives or comments           */
/* Rule                : MISRA C:2012 Rule 20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1531)    : The object 'name' is referenced in only one translation unit - but not the one in which      */
/*                       it is defined.                                                                               */
/* Rule                : CERTCCM DCL15, CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569               */
/* JV-01 Justification : Followed coding rules, the objects (global variable/const) is define in seperated source     */
/*                       file, so this could be accepted                                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1502)    : The object 'name' is defined but is not used within this project.                            */
/* Rule                : MISRA C:2012 Rule-2.8, CWE Rule CWE-398, CWE-569, CERTC Rule MSC13                           */
/* JV-01 Justification : Array is used in another part of driver code. There is no problem in use                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
#define CAN_LCFG_C_AR_RELEASE_MAJOR_VERSION                                     4U
#define CAN_LCFG_C_AR_RELEASE_MINOR_VERSION                                     8U
#define CAN_LCFG_C_AR_RELEASE_REVISION_VERSION                                  0U
#define CAN_LCFG_C_SW_MAJOR_VERSION                                             2U
#define CAN_LCFG_C_SW_MINOR_VERSION                                             4U

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/
#if (CAN_LTTYPES_AR_RELEASE_MAJOR_VERSION != CAN_LCFG_C_AR_RELEASE_MAJOR_VERSION)
 #error "Can_Lcfg.c : Mismatch in Release Major Version"
#endif

#if (CAN_LTTYPES_AR_RELEASE_MINOR_VERSION != CAN_LCFG_C_AR_RELEASE_MINOR_VERSION)
 #error "Can_Lcfg.c : Mismatch in Release Minor Version"
#endif

#if (CAN_LTTYPES_AR_RELEASE_REVISION_VERSION != CAN_LCFG_C_AR_RELEASE_REVISION_VERSION)
 #error "Can_Lcfg.c : Mismatch in Release Revision Version"
#endif

#if (CAN_LTTYPES_SW_MAJOR_VERSION != CAN_LCFG_C_SW_MAJOR_VERSION)
  #error "Can_Lcfg.c : Mismatch in Software Major Version"
#endif

#if (CAN_LTTYPES_SW_MINOR_VERSION != CAN_LCFG_C_SW_MINOR_VERSION)
  #error "Can_Lcfg.c : Mismatch in Software Minor Version"
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/
#define CAN_START_SEC_CONFIG_DATA_PREBUILD_8
#include "Can_MemMap.h"



/* Table to acquire index of config table from physical controller number */
CONST(uint8, CAN_CONST) Can_GaaPhysicalControllerToIndex0[] =
{
  /* Index 0 */
  0x00U,

  /* Index 1 */
  0x00U,

  /* Index 2 */
  0x00U,

  /* Index 3 */
  0x00U,

  /* Index 4 */
  0x00U,

  /* Index 5 */
  0x00U,

  /* Index 6 */
  0x00U,

  /* Index 7 */
  0x00U,

  /* Index 8 */
  0x00U,

  /* Index 9 */
  0x00U,

  /* Index 10 */
  0x00U,

  /* Index 11 */
  0x00U,

  /* Index 12 */
  0x00U,

  /* Index 13 */
  0x00U,

  /* Index 14 */
  0x00U,

  /* Index 15 */
  0x00U,

  /* Index 16 */
  0x01U
};
/* Table to acquire index of config table from physical controller number */
CONST(uint8, CAN_CONST) CanXL_GaaPhysicalControllerToIndex0[] =                                                         /* PRQA S 1502 # JV-01 */
{
  /* Index 0 */
  0x00U
};
/* Table to acquire index of config table from physical controller number */
CONST(uint8, CAN_CONST) CanXL_GaaSecondPhysicalControllerToIndex0[] =                                                   /* PRQA S 1502 # JV-01 */
{
  /* Index 0 */
  0x00U
};


#define CAN_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Global array for ControllerConfigType structure */
CONST(Can_ControllerPCConfigType, CAN_CONFIG_DATA) Can_GaaControllerPCConfig0[] =
{
  /* Index: 0 - CanController0 */
  {
    /* blActivation */
    CAN_TRUE,

    /* ucUnit */
    0x00U,

    /* ucCh */
    0x00U,

    /* ucIntEnable */
    CAN_INT_DISABLED,

    /* ulCTR */
    CAN_RSCAN_BOM_HALT_BUSOFF_ENTRY,

    /* ulTHLCC */
    CAN_RSCAN_THLDTE,

    /* pICRec */
    (P2VAR(volatile uint16, CAN_CONFIG_DATA, REGSPACE))0xFFF80526UL,                                                    /* PRQA S 0303 # JV-01 */

    /* pICTx */
    (P2VAR(volatile uint16, CAN_CONFIG_DATA, REGSPACE))0xFFF80528UL,                                                    /* PRQA S 0303 # JV-01 */

    /* pICErr */
    (P2VAR(volatile uint16, CAN_CONFIG_DATA, REGSPACE))0xFFF80524UL                                                     /* PRQA S 0303 # JV-01 */
  },
  /* Index: 1 - CanController1 */
  {
    /* blActivation */
    CAN_TRUE,

    /* ucUnit */
    0x02U,

    /* ucCh */
    0x00U,

    /* ucIntEnable */
    CAN_CHECK_INT_TX | CAN_CHECK_INT_RX,

    /* ulCTR */
    CAN_RSCAN_BOM_HALT_BUSOFF_ENTRY,

    /* ulTHLCC */
    CAN_RSCAN_THLDTE,

    /* pICRec */
    (P2VAR(volatile uint16, CAN_CONFIG_DATA, REGSPACE))0xFFF804CAUL,                                                    /* PRQA S 0303 # JV-01 */

    /* pICTx */
    (P2VAR(volatile uint16, CAN_CONFIG_DATA, REGSPACE))0xFFF804CCUL,                                                    /* PRQA S 0303 # JV-01 */

    /* pICErr */
    (P2VAR(volatile uint16, CAN_CONFIG_DATA, REGSPACE))0xFFF804C8UL                                                     /* PRQA S 0303 # JV-01 */
  }
};

/* Register Address Configuration of CanXL */

/* Register Address Configuration */
CONST(Can_RegisterSetType, CAN_CONFIG_DATA) Can_GaaRegs[] =
{
  /* Index: 0 - RSCANFD0 */
  {
    /* enMacroType */
    CAN_MACRO_RSCANFD,

    /* pCmn */
    (P2VAR(volatile Can_CommonRegType, CAN_CONFIG_DATA, REGSPACE))0xFF800000UL,                                         /* PRQA S 0303 # JV-01 */

    /* pRR */
    (P2VAR(volatile Can_RRuleRegType, CAN_CONFIG_DATA, REGSPACE))0xFF801800UL,                                          /* PRQA S 0303 # JV-01 */

    /* pFD */
    (P2VAR(volatile Can_FDRegType, CAN_CONFIG_DATA, REGSPACE))0xFF801400UL                                              /* PRQA S 0303 # JV-01 */
  },
  /* Index: 1 - RSCANFD1 */
  {
    /* enMacroType */
    CAN_MACRO_RSCANFD,

    /* pCmn */
    (P2VAR(volatile Can_CommonRegType, CAN_CONFIG_DATA, REGSPACE))0xFF820000UL,                                         /* PRQA S 0303 # JV-01 */

    /* pRR */
    (P2VAR(volatile Can_RRuleRegType, CAN_CONFIG_DATA, REGSPACE))0xFF821800UL,                                          /* PRQA S 0303 # JV-01 */

    /* pFD */
    (P2VAR(volatile Can_FDRegType, CAN_CONFIG_DATA, REGSPACE))0xFF821400UL                                              /* PRQA S 0303 # JV-01 */
  },
  /* Index: 2 - RSCANFD2 */
  {
    /* enMacroType */
    CAN_MACRO_RSCANFD,

    /* pCmn */
    (P2VAR(volatile Can_CommonRegType, CAN_CONFIG_DATA, REGSPACE))0xFF840000UL,                                         /* PRQA S 0303 # JV-01 */

    /* pRR */
    (P2VAR(volatile Can_RRuleRegType, CAN_CONFIG_DATA, REGSPACE))0xFF841800UL,                                          /* PRQA S 0303 # JV-01 */

    /* pFD */
    (P2VAR(volatile Can_FDRegType, CAN_CONFIG_DATA, REGSPACE))0xFF841400UL                                              /* PRQA S 0303 # JV-01 */
  }
};

#define CAN_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */



/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

