/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mcu_PBcfg.c                                                                                         */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2023, 2024 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains post-build time parameters.                                                                     */
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
/* TOOL VERSION:  McuU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\mcu\generator\U2B24-E\R2211_mcu_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_mcu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_mcu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  13 Jul 2026 - 15:38:52
 */


/***********************************************************************************************************************
**                      Instance Index                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Mcu.h"

#include "Mcu_PBTypes.h"

#include "Mcu_CLK_LLDriver.h"

#include "Mcu_RST_LLDriver.h"

#include "Mcu_RAM_LLDriver.h"

#include "Mcu_STB_LLDriver.h"

#include "Mcu_CLM_LLDriver.h"

#include "Mcu_VMN_LLDriver.h"

#include "Mcu_ECM_LLDriver.h"

#include "Mcu_ECC_LLDriver.h"

#include "Mcu_ECM_Irq.h"

#include "Mcu_Cbk.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/

/**********************************************************************************************************************/
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569, CWE-738                    */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:0311)    : Dangerous pointer cast results in loss of const qualification.                               */
/* Rule                : CERTCCM EXP05, MISRA C:2012 Rule-11.8                                                        */
/* JV-01 Justification : This is to achieve throughput in the code.                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0777)    : [U] External identifier does not differ from other identifier(s) (e.g. '%s') within the      */
/*                       specified number of significant characters.                                                  */
/* Rule                : CERTCCM DCL23, MSC15, MISRA C:2012 Rule-5.1, CWE-682, CWE-758                                */
/* JV-01 Justification : Compiler will distinguish numerous characters, so this is accepted.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0778)    : Identifier matches other identifier(s) (e.g. '%s') in first 31 characters - program does     */
/*                       not conform strictly to ISO:C90.                                                             */
/* Rule                : CERTCCM DCL23, DCL40, MISRA C:2012 Dir-1.1, CWE Rule CWE-736                                 */
/* JV-01 Justification : Compiler will distinguish numerous characters, so this is accepted.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0779)    : Identifier does not differ from other identifier(s) (e.g. '%s') within the specified number  */
/*                       of significant characters.                                                                   */
/* Rule                : CERTCCM DCL23, DCL40, MSC15, MISRA C:2012 Rule-5.2, CWE Rule CWE-682, CWE-758, CWE-736       */
/* JV-01 Justification : Compiler will distinguish numerous characters, so this is accepted.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1502)    : The object 'name' is defined but is not used within this project.                            */
/* Rule                : MISRA C:2012 Rule-2.8, CWE Rule CWE-398, CWE-569, CERTC Rule MSC13                           */
/* JV-01 Justification : Array is used in another part of driver code. There is no problem in use                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object 'name' is only referenced in the translation unit where it is defined.            */
/* Rule                : MISRA-C:2012 Rule-8.7, CERT-C:1.2.4 CERTCCM DCL15, DCL19, CWE Rule CWE-398, CWE-569          */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other    */
/*                       C source files                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1533)    : The object '%1s' is only referenced by function '%2s'.                                       */
/* Rule                : MISRA C:2012 Rule-8.9, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : This is accepted, due to the object is defined in separated source C file to followed        */
/*                       coding rule                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1534)    : The macro '%1s' is declared but not used within this project.                                */
/* Rule                : MISRA C:2012 Rule-2.5                                                                        */
/* JV-01 Justification : These macros are used for version checking in precompile or in user application.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : %s' has external linkage and is being defined without any previous declaration.              */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MCU_PBCFG_C_AR_RELEASE_MAJOR_VERSION                                    4U                                      /* PRQA S 1534 # JV-01 */
#define MCU_PBCFG_C_AR_RELEASE_MINOR_VERSION                                    8U                                      /* PRQA S 1534 # JV-01 */
#define MCU_PBCFG_C_AR_RELEASE_REVISION_VERSION                                 0U                                      /* PRQA S 1534 # JV-01 */

/* File version information */
#define MCU_PBCFG_C_SW_MAJOR_VERSION                                            2U                                      /* PRQA S 1534 # JV-01 */
#define MCU_PBCFG_C_SW_MINOR_VERSION                                            5U                                      /* PRQA S 1534 # JV-01 */

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/
/* Specification Major Version Check */
#if (MCU_PBTYPES_AR_RELEASE_MAJOR_VERSION != MCU_PBCFG_C_AR_RELEASE_MAJOR_VERSION)
  #error "Mcu_PBcfg.c :Mismatch in Release Major Version"
#endif

#if (MCU_PBTYPES_AR_RELEASE_MINOR_VERSION != MCU_PBCFG_C_AR_RELEASE_MINOR_VERSION)
  #error "Mcu_PBcfg.c :Mismatch in Release Minor Version"
#endif

#if (MCU_PBTYPES_AR_RELEASE_REVISION_VERSION != MCU_PBCFG_C_AR_RELEASE_REVISION_VERSION)
  #error "Mcu_PBcfg.c :Mismatch in Release Revision Version"
#endif

#if (MCU_PBTYPES_SW_MAJOR_VERSION != MCU_PBCFG_C_SW_MAJOR_VERSION)
  #error "Mcu_PBcfg.c :Mismatch in Software Major Version"
#endif

#if (MCU_PBTYPES_SW_MINOR_VERSION != MCU_PBCFG_C_SW_MINOR_VERSION)
  #error "Mcu_PBcfg.c :Mismatch in Software Minor Version"
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/
#define MCU_START_SEC_BURAM_VAR_NO_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

#define MCU_STOP_SEC_BURAM_VAR_NO_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"


#define MCU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


CONST(Mcu_ModeSettingType, MCU_CONFIG_DATA) Mcu_GaaModeSetting[] =                                                      /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - McuModeSettingConf */
  {
    /* enModeType */
    MCU_RUN_MODE,


  },
  /* Index: 1 - McuModeSettingConf_001 */
  {
    /* enModeType */
    MCU_STOP_MODE,

    /* Index: 1 - aaWakeUpFactor */
    {
      0xFFFFFF9FUL,

      0xFFFFFFFEUL,

      0xFFFFFFF7UL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL
    }
  },
  /* Index: 2 - McuModeSettingConf_002 */
  {
    /* enModeType */
    MCU_DEEPSTOP_MODE,

    /* Index: 1 - aaWakeUpFactor */
    {
      0xFFFFFF9FUL,

      0xFFFFFFFEUL,

      0xFFFFFFF7UL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL,

      0xFFFFFFFFUL
    }
  }
};

/* Data Array of RAM setting Configuration */
CONST(Mcu_RamSettingType, MCU_CONFIG_DATA) Mcu_GaaRamSetting[] =                                                        /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - McuRamSectorSettingConf */
  {
    /* pRamSectionBaseAddress */
    (P2VAR(uint32, AUTOMATIC, MCU_CONFIG_DATA))0xFDC0DFFCUL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ulRamSectionSize */
    0x00000100UL,

    /* ucRamDefaultValue */
    0xFFU,

    /* ucRamSectionType */
    0x00U,

    /* ulRamSectionWriteSize */
    0x00000004UL
  },
  /* Index: 1 - McuRamSectorSettingConf_001 */
  {
    /* pRamSectionBaseAddress */
    (P2VAR(uint32, AUTOMATIC, MCU_CONFIG_DATA))0xFDA0EFFCUL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ulRamSectionSize */
    0x00000100UL,

    /* ucRamDefaultValue */
    0xFFU,

    /* ucRamSectionType */
    0x00U,

    /* ulRamSectionWriteSize */
    0x00000004UL
  },
  /* Index: 2 - McuRamSectorSettingConf_002 */
  {
    /* pRamSectionBaseAddress */
    (P2VAR(uint32, AUTOMATIC, MCU_CONFIG_DATA))0xFD80EFFCUL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ulRamSectionSize */
    0x00000100UL,

    /* ucRamDefaultValue */
    0xFFU,

    /* ucRamSectionType */
    0x00U,

    /* ulRamSectionWriteSize */
    0x00000004UL
  },
  /* Index: 3 - McuRamSectorSettingConf_003 */
  {
    /* pRamSectionBaseAddress */
    (P2VAR(uint32, AUTOMATIC, MCU_CONFIG_DATA))0xFD60EFFCUL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ulRamSectionSize */
    0x00000100UL,

    /* ucRamDefaultValue */
    0xFFU,

    /* ucRamSectionType */
    0x00U,

    /* ulRamSectionWriteSize */
    0x00000004UL
  },
  /* Index: 4 - McuRamSectorSettingConf_004 */
  {
    /* pRamSectionBaseAddress */
    (P2VAR(uint32, AUTOMATIC, MCU_CONFIG_DATA))0xFD40EFFCUL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ulRamSectionSize */
    0x00000100UL,

    /* ucRamDefaultValue */
    0xFFU,

    /* ucRamSectionType */
    0x00U,

    /* ulRamSectionWriteSize */
    0x00000004UL
  },
  /* Index: 5 - McuRamSectorSettingConf_005 */
  {
    /* pRamSectionBaseAddress */
    (P2VAR(uint32, AUTOMATIC, MCU_CONFIG_DATA))0xFD20EFFCUL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ulRamSectionSize */
    0x00000100UL,

    /* ucRamDefaultValue */
    0xFFU,

    /* ucRamSectionType */
    0x00U,

    /* ulRamSectionWriteSize */
    0x00000004UL
  },
  /* Index: 6 - McuRamSectorSettingConf_006 */
  {
    /* pRamSectionBaseAddress */
    (P2VAR(uint32, AUTOMATIC, MCU_CONFIG_DATA))0xFD01EFFCUL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ulRamSectionSize */
    0x00000100UL,

    /* ucRamDefaultValue */
    0xFFU,

    /* ucRamSectionType */
    0x00U,

    /* ulRamSectionWriteSize */
    0x00000004UL
  },
  /* Index: 7 - McuRamSectorSettingConf_007 */
  {
    /* pRamSectionBaseAddress */
    (P2VAR(uint32, AUTOMATIC, MCU_CONFIG_DATA))0xFDE0EFFCUL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ulRamSectionSize */
    0x00000100UL,

    /* ucRamDefaultValue */
    0xFFU,

    /* ucRamSectionType */
    0x00U,

    /* ulRamSectionWriteSize */
    0x00000004UL
  },
  /* Index: 8 - McuRamSectorSettingConf_008 */
  {
    /* pRamSectionBaseAddress */
    (P2VAR(uint32, AUTOMATIC, MCU_CONFIG_DATA))0xFE07EFFCUL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ulRamSectionSize */
    0x00000100UL,

    /* ucRamDefaultValue */
    0xFFU,

    /* ucRamSectionType */
    0x01U,

    /* ulRamSectionWriteSize */
    0x00000004UL
  }
};

STATIC CONST(Mcu_ClockHwInfoType, MCU_CONFIG_DATA) Mcu_GstClockHwInfo =                                                 /* PRQA S 1504 # JV-01 */
{
  /* pPReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980700UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pPllEReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980000UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pPllSReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980004UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pMainOscEReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988000UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pMainOscSReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988004UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pHSOscSReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988100UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pMainOscSTPMReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98800cUL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pHSOscSTPMReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988104UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pPLLSTPMReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98000cUL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pSSCGCReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98002cUL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pSSCG1CReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98004cUL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pPROT4Reg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980730UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pHSOSCTRMPRODCReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98810cUL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pHSOSCTRMENReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988128UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pHSOSCFRETRMSReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988130UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pHSOSCTRMCNTReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988134UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pHSOSCTRMCODEReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988138UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pHSOSCUSERTRMSETReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988148UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* ucNoOfClkSrc */
  (uint8)0x03U,
  /* pCMUCLKENReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff600080UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pGTMCTRLReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff600008UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pGTMCLSCLKCFGReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff60002cUL                                                               /* PRQA S 0303, 3432 # JV-01, JV-01 */
};

STATIC CONST(Mcu_CCMSettingType, MCU_CONFIG_DATA) Mcu_GaaCCMSetting0[] =                                                /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - CCM Cluster 0 */
  {
    /* pCCMnPROTRegs */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6041fcUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCCMnCLKCFGReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6041f0UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCCMnFXCLKCFGReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6041f4UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCcmClkCfgValue */
    (uint32)0x00000000UL,

    /* ulCcmFxClkCtrlValue */
    (uint32)0x00000000UL
  }
};

STATIC CONST(Mcu_CMUSettingType, MCU_CONFIG_DATA) Mcu_GaaCMUSetting0[] =                                                /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - CMU_GCLK_NUM register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff600084UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000001UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 1 - CMU_GCLK_DEN register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff600088UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000001UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 2 - CMU_CLK_0_CTRL register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff60008cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000000UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 3 - CMU_CLK_1_CTRL register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff600090UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000000UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 4 - CMU_CLK_2_CTRL register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff600094UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000000UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 5 - CMU_CLK_3_CTRL register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff600098UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000000UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 6 - CMU_CLK_4_CTRL register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff60009cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000000UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 7 - CMU_CLK_5_CTRL register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6000a0UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000000UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 8 - CMU_CLK_6_CTRL register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6000a4UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000000UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 9 - CMU_CLK_7_CTRL register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6000a8UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000000UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 10 - CMU_ECLK_0_NUM register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6000acUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000001UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 11 - CMU_ECLK_0_DEN register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6000b0UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000001UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 12 - CMU_ECLK_1_NUM register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6000b4UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000001UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 13 - CMU_ECLK_1_DEN register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6000b8UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000001UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 14 - CMU_ECLK_2_NUM register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6000bcUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000001UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 15 - CMU_ECLK_2_DEN register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6000c0UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000001UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x00FFFFFFUL
  },
  /* Index: 16 - CMU_FXCLK_CTRL register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6000c4UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000000UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x0000000FUL
  },
  /* Index: 17 - CMU_CLK_CTRL register */
  {
    /* pCmuCfgRegAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff6000ccUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCmuUnitRegValue */
    (uint32)0x00000000UL,

    /* ulCmuUnitRegMaskValue */
    (uint32)0x000001FFUL
  }
};

STATIC CONST(Mcu_ClockModeSettingType, MCU_CONFIG_DATA) Mcu_GaaClockModeSetting0[] =                                    /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - Clk Source No 0 */
  {
    /* ulCKSC */
    (uint32)0x00000000UL,

    /* pCKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980108UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980120UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980128UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 1 - Clk Source No 1 */
  {
    /* ulCKSC */
    (uint32)0x00000000UL,

    /* pCKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980114UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980130UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980134UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 2 - Clk Source No 2 */
  {
    /* ulCKSC */
    (uint32)0x00000000UL,

    /* pCKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98011cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980138UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98013cUL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  }
};

STATIC CONST(Mcu_ClockModuleSettingType, MCU_CONFIG_DATA) Mcu_GaaClockModuleSetting0[] =                                /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - McuWDTClk */
  {
    /* pCLKSCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988300UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988308UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    NULL_PTR,

    /* pCLKDSAddr */
    NULL_PTR,

    /* ulCKSCValue */
    (uint32)0x00000001UL,

    /* ulCKDCValue */
    (uint32)0x00000000UL,

    /* enClkModuleType */
    (Mcu_ClockModuleType)MCU_CLK_SEL
  },
  /* Index: 1 - McuWDTClkA */
  {
    /* pCLKSCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988200UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988208UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    NULL_PTR,

    /* pCLKDSAddr */
    NULL_PTR,

    /* ulCKSCValue */
    (uint32)0x00000001UL,

    /* ulCKDCValue */
    (uint32)0x00000000UL,

    /* enClkModuleType */
    (Mcu_ClockModuleType)MCU_CLK_SEL
  },
  /* Index: 2 - McuRLINClk */
  {
    /* pCLKSCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980140UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980148UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    NULL_PTR,

    /* pCLKDSAddr */
    NULL_PTR,

    /* ulCKSCValue */
    (uint32)0x00020003UL,

    /* ulCKDCValue */
    (uint32)0x00000000UL,

    /* enClkModuleType */
    (Mcu_ClockModuleType)MCU_CLK_SEL
  },
  /* Index: 3 - McuTAUJClk */
  {
    /* pCLKSCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988210UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988218UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    NULL_PTR,

    /* pCLKDSAddr */
    NULL_PTR,

    /* ulCKSCValue */
    (uint32)0x00000004UL,

    /* ulCKDCValue */
    (uint32)0x00000000UL,

    /* enClkModuleType */
    (Mcu_ClockModuleType)MCU_CLK_SEL
  },
  /* Index: 4 - McuRCANClk */
  {
    /* pCLKSCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980150UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980158UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    NULL_PTR,

    /* pCLKDSAddr */
    NULL_PTR,

    /* ulCKSCValue */
    (uint32)0x00010001UL,

    /* ulCKDCValue */
    (uint32)0x00000000UL,

    /* enClkModuleType */
    (Mcu_ClockModuleType)MCU_CLK_SEL
  },
  /* Index: 5 - McuMSPIClk */
  {
    /* pCLKSCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980170UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980178UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    NULL_PTR,

    /* pCLKDSAddr */
    NULL_PTR,

    /* ulCKSCValue */
    (uint32)0x00000002UL,

    /* ulCKDCValue */
    (uint32)0x00000000UL,

    /* enClkModuleType */
    (Mcu_ClockModuleType)MCU_CLK_SEL
  },
  /* Index: 6 - McuRTCClk */
  {
    /* pCLKSCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988220UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988228UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    NULL_PTR,

    /* pCLKDSAddr */
    NULL_PTR,

    /* ulCKSCValue */
    (uint32)0x00000001UL,

    /* ulCKDCValue */
    (uint32)0x00000000UL,

    /* enClkModuleType */
    (Mcu_ClockModuleType)MCU_CLK_SEL
  },
  /* Index: 7 - McuSWDTClk */
  {
    /* pCLKSCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980190UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980198UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    NULL_PTR,

    /* pCLKDSAddr */
    NULL_PTR,

    /* ulCKSCValue */
    (uint32)0x00000000UL,

    /* ulCKDCValue */
    (uint32)0x00000000UL,

    /* enClkModuleType */
    (Mcu_ClockModuleType)MCU_CLK_SEL
  },
  /* Index: 8 - McuEXTCLK0OClk */
  {
    /* pCLKSCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988250UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988258UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988260UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988268UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCKSCValue */
    (uint32)0x00000002UL,

    /* ulCKDCValue */
    (uint32)0x00000001UL,

    /* enClkModuleType */
    (Mcu_ClockModuleType)MCU_CLK_EXTCLKO
  },
  /* Index: 9 - McuEXTCLK1OClk */
  {
    /* pCLKSCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988270UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988278UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988280UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988288UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulCKSCValue */
    (uint32)0x00000002UL,

    /* ulCKDCValue */
    (uint32)0x00000001UL,

    /* enClkModuleType */
    (Mcu_ClockModuleType)MCU_CLK_EXTCLKO
  },
  /* Index: 10 - McuOSPIClk */
  {
    /* pCLKSCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9802e0UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9802e8UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    NULL_PTR,

    /* pCLKDSAddr */
    NULL_PTR,

    /* ulCKSCValue */
    (uint32)0x00000000UL,

    /* ulCKDCValue */
    (uint32)0x00000000UL,

    /* enClkModuleType */
    (Mcu_ClockModuleType)MCU_CLK_SEL
  },
  /* Index: 11 - McuCANXL0Clk */
  {
    /* pCLKSCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9801a0UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9801a8UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    NULL_PTR,

    /* pCLKDSAddr */
    NULL_PTR,

    /* ulCKSCValue */
    (uint32)0x00000001UL,

    /* ulCKDCValue */
    (uint32)0x00000000UL,

    /* enClkModuleType */
    (Mcu_ClockModuleType)MCU_CLK_SEL
  },
  /* Index: 12 - McuCANXL1Clk */
  {
    /* pCLKSCAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9801b0UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKSSAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9801b8UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCLKDCAddr */
    NULL_PTR,

    /* pCLKDSAddr */
    NULL_PTR,

    /* ulCKSCValue */
    (uint32)0x00000001UL,

    /* ulCKDCValue */
    (uint32)0x00000000UL,

    /* enClkModuleType */
    (Mcu_ClockModuleType)MCU_CLK_SEL
  }
};

STATIC CONST(Mcu_ClockShiftRepetitionType, MCU_CONFIG_DATA)                                                             
   Mcu_GaaClockShiftRepetitionSetting0[2][MCU_NUMBER_CLOCK_GEAR_UP_REPETITION] =                                        /* PRQA S 0777, 0778, 0779, 1504 # JV-01, JV-01, JV-01, JV-01 */
{
  /* Index: 0 - Gear Up */
  {
    /* Index: 0 - Repetition No.1 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000006UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980120UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980128UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 1 - Repetition No.2 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000000UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980100UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000000UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980108UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000001UL
    },
    /* Index: 2 - Repetition No.3 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000008UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980120UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980128UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 3 - Repetition No.4 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000AUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980120UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980128UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 4 - Repetition No.5 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000CUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980120UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980128UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 5 - Repetition No.6 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000EUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980120UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980128UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 6 - Repetition No.7 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000000UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980120UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980128UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    }
  },
  /* Index: 1 - Gear Down */
  {
    /* Index: 0 - Repetition No.1 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000EUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980120UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980128UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 1 - Repetition No.2 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000CUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980120UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980128UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 2 - Repetition No.3 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000AUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980120UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980128UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 3 - Repetition No.4 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000008UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980120UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980128UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 4 - Repetition No.5 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000006UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980120UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980128UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 5 - Repetition No.6 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000001UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980100UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000001UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980108UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000001UL
    },
    /* Index: 6 - Repetition No.7 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000004UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980120UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980128UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    }
  }
};

STATIC CONST(Mcu_ClockShiftRepetitionType, MCU_CONFIG_DATA)                                                             
   Mcu_GaaClockShiftRepetitionSetting1[2][MCU_NUMBER_CLOCK_GEAR_UP_REPETITION] =                                        /* PRQA S 0777, 0778, 0779, 1504 # JV-01, JV-01, JV-01, JV-01 */
{
  /* Index: 0 - Gear Up */
  {
    /* Index: 0 - Repetition No.1 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000006UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980130UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980134UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 1 - Repetition No.2 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000000UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980110UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000000UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980114UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000001UL
    },
    /* Index: 2 - Repetition No.3 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000008UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980130UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980134UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 3 - Repetition No.4 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000AUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980130UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980134UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 4 - Repetition No.5 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000CUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980130UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980134UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 5 - Repetition No.6 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000EUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980130UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980134UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 6 - Repetition No.7 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000000UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980130UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980134UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    }
  },
  /* Index: 1 - Gear Down */
  {
    /* Index: 0 - Repetition No.1 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000EUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980130UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980134UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 1 - Repetition No.2 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000CUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980130UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980134UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 2 - Repetition No.3 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000AUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980130UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980134UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 3 - Repetition No.4 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000008UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980130UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980134UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 4 - Repetition No.5 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000006UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980130UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980134UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 5 - Repetition No.6 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000001UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980110UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000001UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980114UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000001UL
    },
    /* Index: 6 - Repetition No.7 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000004UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980130UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980134UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    }
  }
};

STATIC CONST(Mcu_ClockShiftRepetitionType, MCU_CONFIG_DATA)                                                             
   Mcu_GaaClockShiftRepetitionSetting2[2][MCU_NUMBER_CLOCK_GEAR_UP_REPETITION] =                                        /* PRQA S 0777, 0778, 0779, 1504 # JV-01, JV-01, JV-01, JV-01 */
{
  /* Index: 0 - Gear Up */
  {
    /* Index: 0 - Repetition No.1 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000006UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980138UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98013cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 1 - Repetition No.2 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000000UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980118UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000000UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98011cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000001UL
    },
    /* Index: 2 - Repetition No.3 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000008UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980138UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98013cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 3 - Repetition No.4 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000AUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980138UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98013cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 4 - Repetition No.5 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000CUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980138UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98013cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 5 - Repetition No.6 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000EUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980138UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98013cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 6 - Repetition No.7 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000000UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980138UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98013cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    }
  },
  /* Index: 1 - Gear Down */
  {
    /* Index: 0 - Repetition No.1 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000EUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980138UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98013cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 1 - Repetition No.2 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000CUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980138UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98013cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 2 - Repetition No.3 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x0000000AUL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980138UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98013cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 3 - Repetition No.4 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000008UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980138UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98013cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 4 - Repetition No.5 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000006UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980138UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98013cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    },
    /* Index: 5 - Repetition No.6 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000001UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980118UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000001UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98011cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000001UL
    },
    /* Index: 6 - Repetition No.7 */
    {
      /* ulCKSCCLKDCValue */
      (uint32)0x00000004UL,

      /* pCKSCCLKDCReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980138UL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSValue */
      (uint32)0x00000002UL,

      /* pCKSSCLKDSReg */
      (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98013cUL,                                                          /* PRQA S 0303, 3432 # JV-01, JV-01 */

      /* ulCKSSCLKDSMaskValue */
      (uint32)0x00000002UL
    }
  }
};

STATIC CONST(Mcu_ClockShiftSettingType, MCU_CONFIG_DATA) Mcu_GaaClockShiftSetting =                                     /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - PLL */
  {
    /* Index: 0 - Gear Up */
    {
      /* aaClockShiftRepetition[0][0] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[0][0], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][1] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[0][1], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][2] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[0][2], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][3] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[0][3], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][4] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[0][4], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][5] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[0][5], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][6] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[0][6] /* PRQA S 0311, 3432 # JV-01, JV-01 */
    },
    /* Index: 1 - Gear Down */
    {
      /* aaClockShiftRepetition[1][0] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[1][0], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][1] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[1][1], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][2] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[1][2], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][3] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[1][3], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][4] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[1][4], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][5] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[1][5], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][6] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting0[1][6] /* PRQA S 0311, 3432 # JV-01, JV-01 */
    }
  },
  /* Index: 1 - SSCG */
  {
    /* Index: 0 - Gear Up */
    {
      /* aaClockShiftRepetition[0][0] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[0][0], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][1] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[0][1], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][2] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[0][2], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][3] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[0][3], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][4] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[0][4], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][5] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[0][5], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][6] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[0][6] /* PRQA S 0311, 3432 # JV-01, JV-01 */
    },
    /* Index: 1 - Gear Down */
    {
      /* aaClockShiftRepetition[1][0] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[1][0], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][1] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[1][1], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][2] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[1][2], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][3] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[1][3], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][4] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[1][4], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][5] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[1][5], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][6] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting1[1][6] /* PRQA S 0311, 3432 # JV-01, JV-01 */
    }
  },
  /* Index: 2 - SSCG1 */
  {
    /* Index: 0 - Gear Up */
    {
      /* aaClockShiftRepetition[0][0] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[0][0], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][1] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[0][1], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][2] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[0][2], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][3] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[0][3], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][4] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[0][4], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][5] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[0][5], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[0][6] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[0][6] /* PRQA S 0311, 3432 # JV-01, JV-01 */
    },
    /* Index: 1 - Gear Down */
    {
      /* aaClockShiftRepetition[1][0] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[1][0], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][1] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[1][1], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][2] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[1][2], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][3] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[1][3], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][4] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[1][4], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][5] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[1][5], /* PRQA S 0311, 3432 # JV-01, JV-01 */

      /* aaClockShiftRepetition[1][6] */
      (P2VAR(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))&Mcu_GaaClockShiftRepetitionSetting2[1][6] /* PRQA S 0311, 3432 # JV-01, JV-01 */
    }
  }
};

/* Array for MCU clock setting configuration */
CONST(Mcu_ClockSettingType, MCU_CONFIG_DATA) Mcu_GaaClockSetting[] =                                                    /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - McuClockSettingConfig */
  {
    /* blMainOscUsed */
    MCU_TRUE,

    /* blPllUsed */
    MCU_TRUE,

    /* blHSOscUsed */
    MCU_TRUE,

    /* blClkGenSupported */
    MCU_TRUE,

    /* blClkTrimmingSupported */
    MCU_FALSE,

    /* pClockModeSetting */
    &Mcu_GaaClockModeSetting0[0],

    /* pClockModuleSetting */
    &Mcu_GaaClockModuleSetting0[0],

    /* ucNoOfClkModule */
    (uint8)0x0DU,

    /* pCcmSetting */
    &Mcu_GaaCCMSetting0[0],                                                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pCmuSetting */
    &Mcu_GaaCMUSetting0[0],                                                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ucNoOfCcmCfg */
    (uint8)0x01U,

    /* ulClsClkCfgValue */
    (uint32)0x00000001UL,

    /* ulPLLSTPM */
    (uint32)0x00000001UL,

    /* ulMOSCSTPM */
    (uint32)0x00000001UL,

    /* ulHSOSCSTPM */
    (uint32)0x00000000UL,

    /* ulSSCGC */
    (uint32)0x000000A8UL,

    /* ulSSCG1C */
    (uint32)0x000000A8UL,

    /* ulHSOSCTRMPRODC */
    (uint32)0x00000002UL,

    /* ulClkTrimmingPeriod */
    (uint32)0x00000032UL,

    /* ulClkStbCount */
    (uint32)0x00004000UL,

    /* pClockShiftSetting */
    &Mcu_GaaClockShiftSetting
  }
};

STATIC CONST(Mcu_ResetType, MCU_CONFIG_DATA) Mcu_GaaRstRsnTable[] =                                                     /* PRQA S 1504 # JV-01 */
{
  /* Bit 0 */
  MCU_POWER_ON_RESET,
  /* Bit 1 */
  MCU_STANDBY_RST,
  /* Bit 2 */
  MCU_EXT_RST,
  /* Bit 3 */
  MCU_VMON_RST,
  /* Bit 4 */
  MCU_SW_SYS_RST,
  /* Bit 5 */
  MCU_RESERVED_RST,
  /* Bit 6 */
  MCU_ECM_SYS_RST,
  /* Bit 7 */
  MCU_WDTBA_SYS_RST,
  /* Bit 8 */
  MCU_SW_APP_RST,
  /* Bit 9 */
  MCU_RESERVED_RST,
  /* Bit 10 */
  MCU_ECM_APP_RST,
  /* Bit 11 */
  MCU_RESERVED_RST,
  /* Bit 12 */
  MCU_RESERVED_RST,
  /* Bit 13 */
  MCU_RESERVED_RST,
  /* Bit 14 */
  MCU_RESERVED_RST,
  /* Bit 15 */
  MCU_DEEPSTOP_RST,
  /* Bit 16 */
  MCU_ICUM_SW_SYS_RST,
  /* Bit 17 */
  MCU_ICUM_SW_APP_RST,
  /* Bit 18 */
  MCU_RESERVED_RST,
  /* Bit 19 */
  MCU_RESERVED_RST,
  /* Bit 20 */
  MCU_RESERVED_RST,
  /* Bit 21 */
  MCU_RESERVED_RST,
  /* Bit 22 */
  MCU_RESERVED_RST,
  /* Bit 23 */
  MCU_RESERVED_RST,
  /* Bit 24 */
  MCU_RESERVED_RST,
  /* Bit 25 */
  MCU_RESERVED_RST,
  /* Bit 26 */
  MCU_RESERVED_RST,
  /* Bit 27 */
  MCU_RESERVED_RST,
  /* Bit 28 */
  MCU_RESERVED_RST,
  /* Bit 29 */
  MCU_RESERVED_RST,
  /* Bit 30 */
  MCU_RESERVED_RST,
  /* Bit 31 */
  MCU_RESERVED_RST
};

STATIC CONST(Mcu_ResetHwInfoType, MCU_CONFIG_DATA) Mcu_GstResetHwInfo =                                                 /* PRQA S 1504 # JV-01 */
{
  /* pPReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980f00UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pRESFCReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff980c00UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pRESCReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988414UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pRESFReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988500UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pSWARESAReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988410UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pRstRsnTable */
  &Mcu_GaaRstRsnTable[0]
};

STATIC CONST(Mcu_EccHwInfoType, MCU_CONFIG_DATA) Mcu_GstEccHwInfo =                                                     /* PRQA S 1504 # JV-01 */
{
  /* pECCKCPROTReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xfffb2800UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pCR_SSTCLRReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55210UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pCR_DSTCLRReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55214UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pCR_OVFCLRReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55218UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pCR_ERRINTReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55200UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pCR_SERSTRReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55220UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pCR_DERSTRReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55224UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pCR_OVFSTRReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55228UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pLR1_SSTCLRReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55010UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pLR1_DSTCLRReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55014UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pLR1_OVFCLRReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55018UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pLR1_ERRINTReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55000UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pLR0_ERRINT_PE0Reg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc52000UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pLR1_SERSTRReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55020UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pLR1_DERSTRReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55024UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pLR1_OVFSTRReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffc55028UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* ulLR0PEnOffset */
  (uint32)0x00000080UL,
  /* ulLR0SSTCLROffset */
  (uint32)0x00000004UL,
  /* ulLR0DSTCLROffset */
  (uint32)0x00000005UL,
  /* ulLR0OVFCLROffset */
  (uint32)0x00000006UL,
  /* ulLR0SERSTROffset */
  (uint32)0x00000008UL,
  /* ulLR0DERTROffset */
  (uint32)0x00000009UL,
  /* ulLR0OVFSTROffset */
  (uint32)0x0000000aUL
};

STATIC CONST(Mcu_WakeUpHwInfoType, MCU_CONFIG_DATA) Mcu_GaaWakeUpRegsAddr[] =                                           /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - WUF0A0 */
  {
    /* pWUFRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e000UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFMSKRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e004UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFCRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e008UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 1 - WUF0A1 */
  {
    /* pWUFRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e010UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFMSKRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e014UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFCRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e018UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 2 - WUF0A2 */
  {
    /* pWUFRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e020UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFMSKRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e024UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFCRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e028UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 3 - WUF1A0 */
  {
    /* pWUFRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e120UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFMSKRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e124UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFCRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e128UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 4 - WUF1A1 */
  {
    /* pWUFRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e130UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFMSKRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e134UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFCRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e138UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 5 - WUF1A2 */
  {
    /* pWUFRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e140UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFMSKRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e144UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFCRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e148UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 6 - WUF0I0 */
  {
    /* pWUFRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e200UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFMSKRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e204UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFCRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e208UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 7 - WUF0I1 */
  {
    /* pWUFRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e210UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFMSKRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e214UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFCRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e218UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 8 - WUF0I2 */
  {
    /* pWUFRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e220UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFMSKRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e224UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFCRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e228UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 9 - WUF0I3 */
  {
    /* pWUFRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e230UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFMSKRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e234UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFCRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e238UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 10 - WUF1I1 */
  {
    /* pWUFRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e330UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFMSKRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e334UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pWUFCRegsAddr */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e338UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  }
};

STATIC CONST(Mcu_WUFMONHwInfoType, MCU_CONFIG_DATA) Mcu_GstWUFMONHwInfo =                                               /* PRQA S 1504 # JV-01 */
{
  /* pWUFMONRegsAddr */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff98e1a0UL                                                               /* PRQA S 0303, 3432 # JV-01, JV-01 */
};

CONST(Mcu_IOBufferHoldHwInfoType, MCU_CONFIG_DATA) Mcu_GstIOBufferHoldHwInfo =                                          /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* pIOBufHoldReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988d00UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pIOBufHold1Reg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988d04UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pIOBufHold2Reg */
  NULL_PTR
};

STATIC CONST(Mcu_StbHwInfoType, MCU_CONFIG_DATA) Mcu_GstStbHwInfo =                                                     /* PRQA S 1504 # JV-01 */
{
  /* pSTBCKCPROTReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff981700UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pSTBC0STPTReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988c04UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pSTBC0PSCReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988c00UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pPWRGD_CNTReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff988c08UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pRRAM_SDMReg */
  NULL_PTR,
  /* pAWOPSMReg */
  NULL_PTR
};

STATIC CONST(Mcu_EcmHwInfoType, MCU_CONFIG_DATA) Mcu_GstEcmHwInfo =                                                     /* PRQA S 1504 # JV-01 */
{
  /* pEIC8Reg */
  NULL_PTR,
  /* pEIC9Reg */
  NULL_PTR,
  /* pIMR0Reg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xfffc00f0UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pEIBD8Reg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xfffc0120UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pEIBD9Reg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xfffc0124UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pFIBD0Reg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xfffc01c0UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pFEINTMSK0Reg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a3b04UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pECMEPCFGReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd000UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pECMEMK0Reg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd25cUL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pECMESSTC0Reg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd478UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pECMKCPROTReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd4b4UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pECMDTMCTLReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd4f4UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pECMDTMCMPReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd4fcUL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pECMEOCCFGReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd71cUL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pECMETCCFG0Reg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd720UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pECMPEMReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd740UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pECMMESSTR0Reg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffcce048UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pECMCESSTR0Reg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccf048UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pECMMESSTRjReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffcce048UL,                                                              /* PRQA S 0303, 3432 # JV-01, JV-01 */
  /* pECMCESSTRjReg */
  (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccf048UL                                                               /* PRQA S 0303, 3432 # JV-01, JV-01 */
};

STATIC CONST(Mcu_EcmCommonRegType, MCU_CONFIG_DATA) Mcu_GaaEcmCommonRegInitSetting[] =                                  /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - ECM interrupt notification configuration PE0 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd040UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 1 - ECM interrupt notification configuration PE1 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd07cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 2 - ECM interrupt notification configuration PE2 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd0b8UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 3 - ECM interrupt notification configuration PE3 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd0f4UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 4 - ECM interrupt notification configuration PE4 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd130UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 5 - ECM interrupt notification configuration PE5 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd16cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 6 - ECM interrupt notification configuration PE6 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd1a8UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 7 - ECM interrupt type selection configuration */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd004UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 8 - ECM internal reset configuration */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd220UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000010UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 9 - ECM error mask */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd25cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 10 - ECM error trigger 0 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd298UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x80EFFFFFUL,

      0x800000E8UL,

      0x07C05000UL,

      0x80000040UL,

      0x7C0C0F00UL,

      0x000FF078UL,

      0xC6240080UL,

      0x7FFCE8C4UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8E3UL,

      0x7FFEE8C0UL
    }
  },
  /* Index: 11 - ECM error trigger 1 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd2d4UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x80EFFFFFUL,

      0x800000E8UL,

      0x07C05000UL,

      0x80000040UL,

      0x7C0C0F00UL,

      0x000FF078UL,

      0xC6240080UL,

      0x7FFCE8C4UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8E3UL,

      0x7FFEE8C0UL
    }
  },
  /* Index: 12 - ECM error trigger 2 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd310UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x80EFFFFFUL,

      0x800000E8UL,

      0x07C05000UL,

      0x80000040UL,

      0x7C0C0F00UL,

      0x000FF078UL,

      0xC6240080UL,

      0x7FFCE8C4UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8E3UL,

      0x7FFEE8C0UL
    }
  },
  /* Index: 13 - ECM error trigger 3 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd34cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x80EFFFFFUL,

      0x800000E8UL,

      0x07C05000UL,

      0x80000040UL,

      0x7C0C0F00UL,

      0x000FF078UL,

      0xC6240080UL,

      0x7FFCE8C4UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8E3UL,

      0x7FFEE8C0UL
    }
  },
  /* Index: 14 - ECM error trigger 4 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd388UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x80EFFFFFUL,

      0x800000E8UL,

      0x07C05000UL,

      0x80000040UL,

      0x7C0C0F00UL,

      0x000FF078UL,

      0xC6240080UL,

      0x7FFCE8C4UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8E3UL,

      0x7FFEE8C0UL
    }
  },
  /* Index: 15 - ECM error trigger 5 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd3c4UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x80EFFFFFUL,

      0x800000E8UL,

      0x07C05000UL,

      0x80000040UL,

      0x7C0C0F00UL,

      0x000FF078UL,

      0xC6240080UL,

      0x7FFCE8C4UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8E3UL,

      0x7FFEE8C0UL
    }
  },
  /* Index: 16 - ECM error trigger 6 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd400UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x80EFFFFFUL,

      0x800000E8UL,

      0x07C05000UL,

      0x80000040UL,

      0x7C0C0F00UL,

      0x000FF078UL,

      0xC6240080UL,

      0x7FFCE8C4UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8C0UL,

      0x7FFCE8E3UL,

      0x7FFEE8C0UL
    }
  }
};

STATIC CONST(Mcu_EcmCommonRegType, MCU_CONFIG_DATA) Mcu_GaaEcmCommonRegAfterInitLramSetting[] =                         /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - ECM interrupt notification configuration PE0 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd040UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 1 - ECM interrupt notification configuration PE1 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd07cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 2 - ECM interrupt notification configuration PE2 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd0b8UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 3 - ECM interrupt notification configuration PE3 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd0f4UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 4 - ECM interrupt notification configuration PE4 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd130UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 5 - ECM interrupt notification configuration PE5 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd16cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 6 - ECM interrupt notification configuration PE6 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd1a8UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 7 - ECM interrupt type selection configuration */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd004UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 8 - ECM internal reset configuration */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd220UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 9 - ECM error mask */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd25cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 10 - ECM error trigger 0 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd298UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 11 - ECM error trigger 1 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd2d4UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 12 - ECM error trigger 2 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd310UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 13 - ECM error trigger 3 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd34cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 14 - ECM error trigger 4 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd388UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 15 - ECM error trigger 5 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd3c4UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 16 - ECM error trigger 6 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd400UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  }
};

STATIC CONST(Mcu_EcmCommonRegType, MCU_CONFIG_DATA) Mcu_GaaEcmCommonRegAfterInitCramSetting[] =                         /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - ECM interrupt notification configuration PE0 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd040UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 1 - ECM interrupt notification configuration PE1 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd07cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 2 - ECM interrupt notification configuration PE2 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd0b8UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 3 - ECM interrupt notification configuration PE3 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd0f4UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 4 - ECM interrupt notification configuration PE4 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd130UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 5 - ECM interrupt notification configuration PE5 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd16cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 6 - ECM interrupt notification configuration PE6 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd1a8UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 7 - ECM interrupt type selection configuration */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd004UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 8 - ECM internal reset configuration */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd220UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 9 - ECM error mask */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd25cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 10 - ECM error trigger 0 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd298UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 11 - ECM error trigger 1 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd2d4UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 12 - ECM error trigger 2 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd310UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 13 - ECM error trigger 3 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd34cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 14 - ECM error trigger 4 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd388UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 15 - ECM error trigger 5 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd3c4UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  },
  /* Index: 16 - ECM error trigger 6 */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd400UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  }
};

STATIC CONST(Mcu_EcmCommonRegType, MCU_CONFIG_DATA) Mcu_GaaEcmCommonDelayTimerRegInitSetting[] =                        /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - ECM delay timer configuration */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd500UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  }
};

STATIC CONST(Mcu_EcmCommonRegType, MCU_CONFIG_DATA) Mcu_GaaEcmCommonDelayTimerRegAfterInitLramSetting[] =               /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - ECM delay timer configuration */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd500UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  }
};

STATIC CONST(Mcu_EcmCommonRegType, MCU_CONFIG_DATA) Mcu_GaaEcmCommonDelayTimerRegAfterInitCramSetting[] =               /* PRQA S 0777, 0778, 0779, 1504 # JV-01, JV-01, JV-01, JV-01 */
{
  /* Index: 0 - ECM delay timer configuration */
  {
    /* pECMCommonReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd500UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  }
};

STATIC CONST(Mcu_EcmErrorOutClrConfigRegType, MCU_CONFIG_DATA) Mcu_GaaEcmErrorOutClrConfigRegSetting[] =                /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - */
  {
    /* pEcmErrorOutClrConfigReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd720UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* Index: 1 - aaEcmRegisterValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    }
  }
};

STATIC CONST(Mcu_EcmErrorOutClearRegType, MCU_CONFIG_DATA) Mcu_GaaEcmErrorOutClearRegTypeSetting[] =                    /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - */
  {
    /* pEcmErrorOutClearReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd298UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulEcmErrorOutClearValue */
    (uint32)0xFFFFFFFFUL,

    /* ulEcmErrorOutClearOffset */
    (uint32)0x0000000FUL,

    /* ucEcmErrorOutZNum */
    (uint8)0x07U,

    /* ucEcmCommonRegNum */
    (uint8)0x0DU,

    /* blEcmDisableInt */
    MCU_FALSE
  },
  /* Index: 1 - */
  {
    /* pEcmErrorOutClearReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd040UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulEcmErrorOutClearValue */
    (uint32)0xFFEFFFFFUL,

    /* ulEcmErrorOutClearOffset */
    (uint32)0x0000000FUL,

    /* ucEcmErrorOutZNum */
    (uint8)0x07U,

    /* ucEcmCommonRegNum */
    (uint8)0x01U,

    /* blEcmDisableInt */
    MCU_TRUE
  },
  /* Index: 2 - */
  {
    /* pEcmErrorOutClearReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccd220UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulEcmErrorOutClearValue */
    (uint32)0xFFEFFFFFUL,

    /* ulEcmErrorOutClearOffset */
    (uint32)0x00000000UL,

    /* ucEcmErrorOutZNum */
    (uint8)0x01U,

    /* ucEcmCommonRegNum */
    (uint8)0x01U,

    /* blEcmDisableInt */
    MCU_TRUE
  },
  /* Index: 3 - */
  {
    /* pEcmErrorOutClearReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffcce004UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulEcmErrorOutClearValue */
    (uint32)0x00000001UL,

    /* ulEcmErrorOutClearOffset */
    (uint32)0x00000000UL,

    /* ucEcmErrorOutZNum */
    (uint8)0x01U,

    /* ucEcmCommonRegNum */
    (uint8)0x01U,

    /* blEcmDisableInt */
    MCU_FALSE
  },
  /* Index: 4 - */
  {
    /* pEcmErrorOutClearReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffcce00cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulEcmErrorOutClearValue */
    (uint32)0x00000001UL,

    /* ulEcmErrorOutClearOffset */
    (uint32)0x00000002UL,

    /* ucEcmErrorOutZNum */
    (uint8)0x07U,

    /* ucEcmCommonRegNum */
    (uint8)0x01U,

    /* blEcmDisableInt */
    MCU_FALSE
  },
  /* Index: 5 - */
  {
    /* pEcmErrorOutClearReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccf004UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulEcmErrorOutClearValue */
    (uint32)0x00000001UL,

    /* ulEcmErrorOutClearOffset */
    (uint32)0x00000000UL,

    /* ucEcmErrorOutZNum */
    (uint8)0x01U,

    /* ucEcmCommonRegNum */
    (uint8)0x01U,

    /* blEcmDisableInt */
    MCU_FALSE
  },
  /* Index: 6 - */
  {
    /* pEcmErrorOutClearReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xffccf00cUL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ulEcmErrorOutClearValue */
    (uint32)0x00000001UL,

    /* ulEcmErrorOutClearOffset */
    (uint32)0x00000002UL,

    /* ucEcmErrorOutZNum */
    (uint8)0x07U,

    /* ucEcmCommonRegNum */
    (uint8)0x01U,

    /* blEcmDisableInt */
    MCU_FALSE
  }
};

STATIC CONST(Mcu_EcmFEINTRegType, MCU_CONFIG_DATA) Mcu_GaaEcmFEINTRegsAddr[] =                                          /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - */
  {
    /* pFEINTFReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a3b00UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pFEINTCReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a3b08UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 1 - */
  {
    /* pFEINTFReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a3c00UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pFEINTCReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a3c08UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 2 - */
  {
    /* pFEINTFReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a3d00UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pFEINTCReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a3d08UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 3 - */
  {
    /* pFEINTFReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a3e00UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pFEINTCReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a3e08UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 4 - */
  {
    /* pFEINTFReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a3f00UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pFEINTCReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a3f08UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 5 - */
  {
    /* pFEINTFReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a4000UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pFEINTCReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a4008UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  },
  /* Index: 6 - */
  {
    /* pFEINTFReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a4100UL,                                                            /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* pFEINTCReg */
    (volatile P2VAR(uint32, TYPEDEF, REGSPACE))0xff9a4108UL                                                             /* PRQA S 0303, 3432 # JV-01, JV-01 */
  }
};

CONST(Mcu_EcmStatusType, MCU_CONFIG_DATA) Mcu_GaaMcuEcmErrMapTable[14][32] =                                            /* PRQA S 1533 # JV-01 */
{
  /* Index: 0 - ECMMESSTR register 0 */
  {
    {MCU_ZERO_BIT, MCU_RESERVED_RST},

    {MCU_ONE_BIT, MCU_RESERVED_RST},

    {MCU_TWO_BIT, MCU_RESERVED_RST},

    {MCU_THREE_BIT, MCU_RESERVED_RST},

    {MCU_FOUR_BIT, MCU_RESERVED_RST},

    {MCU_FIVE_BIT, MCU_RESERVED_RST},

    {MCU_SIX_BIT, MCU_RESERVED_RST},

    {MCU_SEVEN_BIT, MCU_RESERVED_RST},

    {MCU_EIGHT_BIT, MCU_RESERVED_RST},

    {MCU_NINE_BIT, MCU_RESERVED_RST},

    {MCU_TEN_BIT, MCU_RESERVED_RST},

    {MCU_ELEVEN_BIT, MCU_ECM_DLY_TIMER_OFLOW_RST},

    {MCU_TWELVE_BIT, MCU_RESERVED_RST},

    {MCU_THIRTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FOURTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FIFTEEN_BIT, MCU_RESERVED_RST},

    {MCU_SIXTEEN_BIT, MCU_RESERVED_RST},

    {MCU_SEVENTEEN_BIT, MCU_RESERVED_RST},

    {MCU_EIGHTEEN_BIT, MCU_RESERVED_RST},

    {MCU_NINETEEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTY_BIT, MCU_ECM_COMP_ERR_RST},

    {MCU_TWENTYONE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTWO_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTHREE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFOUR_BIT, MCU_MODE_ERR_0_RST},

    {MCU_TWENTYFIVE_BIT, MCU_MODE_ERR_1_RST},

    {MCU_TWENTYSIX_BIT, MCU_MODE_ERR_2_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_MODE_ERR_3_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_MODE_ERR_4_RST},

    {MCU_TWENTYNINE_BIT, MCU_MODE_ERR_5_RST},

    {MCU_THIRTY_BIT, MCU_MODE_ERR_6_RST},

    {MCU_THIRTYONE_BIT, MCU_RESERVED_RST}
  },
  /* Index: 1 - ECMMESSTR register 1 */
  {
    {MCU_ZERO_BIT, MCU_FLASH_ACCESS_ERR_RST},

    {MCU_ONE_BIT, MCU_RESERVED_RST},

    {MCU_TWO_BIT, MCU_RESERVED_RST},

    {MCU_THREE_BIT, MCU_RESERVED_RST},

    {MCU_FOUR_BIT, MCU_DTS_COMP_ERR_RST},

    {MCU_FIVE_BIT, MCU_RESERVED_RST},

    {MCU_SIX_BIT, MCU_RESERVED_RST},

    {MCU_SEVEN_BIT, MCU_RESERVED_RST},

    {MCU_EIGHT_BIT, MCU_RDC0_ERR_RST},

    {MCU_NINE_BIT, MCU_RDC1_ERR_RST},

    {MCU_TEN_BIT, MCU_SDMAC0_CHANNEL0_ERR_RST},

    {MCU_ELEVEN_BIT, MCU_SDMAC0_CHANNEL1_ERR_RST},

    {MCU_TWELVE_BIT, MCU_SDMAC0_CHANNEL2_ERR_RST},

    {MCU_THIRTEEN_BIT, MCU_SDMAC0_CHANNEL3_ERR_RST},

    {MCU_FOURTEEN_BIT, MCU_SDMAC0_CHANNEL4_ERR_RST},

    {MCU_FIFTEEN_BIT, MCU_SDMAC0_CHANNEL5_ERR_RST},

    {MCU_SIXTEEN_BIT, MCU_SDMAC0_CHANNEL6_ERR_RST},

    {MCU_SEVENTEEN_BIT, MCU_SDMAC0_CHANNEL7_ERR_RST},

    {MCU_EIGHTEEN_BIT, MCU_SDMAC1_CHANNEL0_ERR_RST},

    {MCU_NINETEEN_BIT, MCU_SDMAC1_CHANNEL1_ERR_RST},

    {MCU_TWENTY_BIT, MCU_SDMAC1_CHANNEL2_ERR_RST},

    {MCU_TWENTYONE_BIT, MCU_SDMAC1_CHANNEL3_ERR_RST},

    {MCU_TWENTYTWO_BIT, MCU_SDMAC1_CHANNEL4_ERR_RST},

    {MCU_TWENTYTHREE_BIT, MCU_SDMAC1_CHANNEL5_ERR_RST},

    {MCU_TWENTYFOUR_BIT, MCU_SDMAC1_CHANNEL6_ERR_RST},

    {MCU_TWENTYFIVE_BIT, MCU_SDMAC1_CHANNEL7_ERR_RST},

    {MCU_TWENTYSIX_BIT, MCU_BUS_BRIDGE_SDMC0_ERR_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_BUS_BRIDGE_SDMC1_ERR_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_BUS_BRIDGECOMP_ERROR_RST},

    {MCU_TWENTYNINE_BIT, MCU_GTM_COMPARE_ERR_RST},

    {MCU_THIRTY_BIT, MCU_GTM_ERR_ISR_RST},

    {MCU_THIRTYONE_BIT, MCU_RESERVED_RST}
  },
  /* Index: 2 - ECMMESSTR register 2 */
  {
    {MCU_ZERO_BIT, MCU_INTER_PROC_ELEMENT_BUS_RST},

    {MCU_ONE_BIT, MCU_INTER_CLUSTER_BUS_RST},

    {MCU_TWO_BIT, MCU_PHERIPHERAL_BUS_RST},

    {MCU_THREE_BIT, MCU_CRAM_BUS_RST},

    {MCU_FOUR_BIT, MCU_SYSTEM_BUS_RST},

    {MCU_FIVE_BIT, MCU_GLOBAL_FLASH_BUS_RST},

    {MCU_SIX_BIT, MCU_LOCAL_FLASH_BUS_RST},

    {MCU_SEVEN_BIT, MCU_CLMA_MOSC_ERR_RST},

    {MCU_EIGHT_BIT, MCU_CLMA_HOSC_ERR_RST},

    {MCU_NINE_BIT, MCU_CLMA_LOSC_ERR_RST},

    {MCU_TEN_BIT, MCU_CLMA_LSB_ERR_RST},

    {MCU_ELEVEN_BIT, MCU_CLMA_UHSB_ERR_RST},

    {MCU_TWELVE_BIT, MCU_RESERVED_RST},

    {MCU_THIRTEEN_BIT, MCU_CLMA_CLKC_LSB_ERR_RST},

    {MCU_FOURTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FIFTEEN_BIT, MCU_CLMA_SBUS_ERR_RST},

    {MCU_SIXTEEN_BIT, MCU_OSTM1_INT_RST},

    {MCU_SEVENTEEN_BIT, MCU_OSTM2_INT_RST},

    {MCU_EIGHTEEN_BIT, MCU_OSTM3_INT_RST},

    {MCU_NINETEEN_BIT, MCU_OSTM4_INT_RST},

    {MCU_TWENTY_BIT, MCU_OSTM5_INT_RST},

    {MCU_TWENTYONE_BIT, MCU_OSTM6_INT_RST},

    {MCU_TWENTYTWO_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTHREE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFOUR_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFIVE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSIX_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_OSPI_ERR_ISR_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_CANXL0_INT_RST},

    {MCU_TWENTYNINE_BIT, MCU_CANXL1_INT_RST},

    {MCU_THIRTY_BIT, MCU_DSMIF0_COMP_ERR_RST},

    {MCU_THIRTYONE_BIT, MCU_DSMIF1_COMP_ERR_RST}
  },
  /* Index: 3 - ECMMESSTR register 3 */
  {
    {MCU_ZERO_BIT, MCU_TSG30_ERR_ISR_RST},

    {MCU_ONE_BIT, MCU_TSG31_ERR_ISR_RST},

    {MCU_TWO_BIT, MCU_TSG32_ERR_ISR_RST},

    {MCU_THREE_BIT, MCU_SEC_POWER_SUPP_ERR_RST},

    {MCU_FOUR_BIT, MCU_AD_PARITY_ERR_RST},

    {MCU_FIVE_BIT, MCU_FAST_COMP_ERR_RST},

    {MCU_SIX_BIT, MCU_RESOLVE_CONV_ERR_RST},

    {MCU_SEVEN_BIT, MCU_TEMP_SENSORERR_RST},

    {MCU_EIGHT_BIT, MCU_CFLH_ERR_ADR_PRTY_ERR_RST},

    {MCU_NINE_BIT, MCU_CFLH_ECC2BIT_ERR_RST},

    {MCU_TEN_BIT, MCU_CFLH_ECC1BIT_ERR_RST},

    {MCU_ELEVEN_BIT, MCU_CFLH_ERR_ADR_OFLOW_RST},

    {MCU_TWELVE_BIT, MCU_DFLH_ECC2BIT_ERR_RST},

    {MCU_THIRTEEN_BIT, MCU_DFLH_ECC1BIT_ERR_RST},

    {MCU_FOURTEEN_BIT, MCU_DFLH_ERR_ADR_OFLOW_RST},

    {MCU_FIFTEEN_BIT, MCU_LRAM_ECC2BIT_ERR_RST},

    {MCU_SIXTEEN_BIT, MCU_LRAM_ECC1BIT_ERR_RST},

    {MCU_SEVENTEEN_BIT, MCU_LRAM_ERR_ADR_OFLOW_RST},

    {MCU_EIGHTEEN_BIT, MCU_CRAM_ADR_OR_ECC2_ERR_RST},

    {MCU_NINETEEN_BIT, MCU_CRAM_ECC1BIT_ERR_RST},

    {MCU_TWENTY_BIT, MCU_CRAM_ERR_ADR_OFLOW_RST},

    {MCU_TWENTYONE_BIT, MCU_DTSRAM_ECC2BIT_ERR_RST},

    {MCU_TWENTYTWO_BIT, MCU_DTSRAM_ECC1BIT_ERR_RST},

    {MCU_TWENTYTHREE_BIT, MCU_DTSRAM_ERR_ADR_OFLOW_RST},

    {MCU_TWENTYFOUR_BIT, MCU_SDMAC0_RAM_ECC2BIT_ERR_RST},

    {MCU_TWENTYFIVE_BIT, MCU_SDMAC0_RAM_ECC1BIT_ERR_RST},

    {MCU_TWENTYSIX_BIT, MCU_SDMAC1_RAM_ECC2BIT_ERR_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_SDMAC1_RAM_ECC1BIT_ERR_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_EX_CRAM_ECC2BIT_ERR_RST},

    {MCU_TWENTYNINE_BIT, MCU_EX_CRAM_ECC1BIT_ERR_RST},

    {MCU_THIRTY_BIT, MCU_EXCRAM_ERR_ADR_OFLOW_RST},

    {MCU_THIRTYONE_BIT, MCU_RESERVED_RST}
  },
  /* Index: 4 - ECMMESSTR register 4 */
  {
    {MCU_ZERO_BIT, MCU_FRRAM_ECC2BIT_ERR_RST},

    {MCU_ONE_BIT, MCU_FRRAM_ECC1BIT_ERR_RST},

    {MCU_TWO_BIT, MCU_CANRAM_ECC2BIT_ERR_RST},

    {MCU_THREE_BIT, MCU_CANRAM_ECC1BIT_ERR_RST},

    {MCU_FOUR_BIT, MCU_MSPIRAM_ECC2BIT_ERR_RST},

    {MCU_FIVE_BIT, MCU_MSPIRAM_ECC1BIT_ERR_RST},

    {MCU_SIX_BIT, MCU_GTMRAM_ECC2BIT_ERR_RST},

    {MCU_SEVEN_BIT, MCU_GTMRAM_ECC1BIT_ERR_RST},

    {MCU_EIGHT_BIT, MCU_RESERVED_RST},

    {MCU_NINE_BIT, MCU_RESERVED_RST},

    {MCU_TEN_BIT, MCU_RESERVED_RST},

    {MCU_ELEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWELVE_BIT, MCU_MMCARAM_ECC2BIT_ERR_RST},

    {MCU_THIRTEEN_BIT, MCU_MMCARAM_ECC1BIT_ERR_RST},

    {MCU_FOURTEEN_BIT, MCU_DFE0_RAM_ERR_2BIT_RST},

    {MCU_FIFTEEN_BIT, MCU_DFE0_RAM_ERR_1BIT_RST},

    {MCU_SIXTEEN_BIT, MCU_RSWITCH_ECC_2BIT_ERR_RST},

    {MCU_SEVENTEEN_BIT, MCU_RSWITCH_ECC_1BIT_ERR_RST},

    {MCU_EIGHTEEN_BIT, MCU_RESERVED_RST},

    {MCU_NINETEEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTY_BIT, MCU_CANXL_RAM_ECC2BIT_ERR_RST},

    {MCU_TWENTYONE_BIT, MCU_CANXL_RAM_ECC1BIT_ERR_RST},

    {MCU_TWENTYTWO_BIT, MCU_ETNF_FIFO_ECC2BIT_ERR_RST},

    {MCU_TWENTYTHREE_BIT, MCU_ETNF_FIFO_ECC1BIT_ERR_RST},

    {MCU_TWENTYFOUR_BIT, MCU_OSPI_ECC2BIT_ERR_RST},

    {MCU_TWENTYFIVE_BIT, MCU_OSPI_ECC1BIT_ERR_RST},

    {MCU_TWENTYSIX_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYNINE_BIT, MCU_RESERVED_RST},

    {MCU_THIRTY_BIT, MCU_RESERVED_RST},

    {MCU_THIRTYONE_BIT, MCU_PERIRAM_ECC_OFLOW_ERR_RST}
  },
  /* Index: 5 - ECMMESSTR register 5 */
  {
    {MCU_ZERO_BIT, MCU_ADRBUS_EDC_ECC_ERR_RST},

    {MCU_ONE_BIT, MCU_DATABUS_ECC2BIT_ERR_RST},

    {MCU_TWO_BIT, MCU_DATABUS_ECC1BIT_ERR_RST},

    {MCU_THREE_BIT, MCU_RESERVED_RST},

    {MCU_FOUR_BIT, MCU_RESERVED_RST},

    {MCU_FIVE_BIT, MCU_RESERVED_RST},

    {MCU_SIX_BIT, MCU_RESERVED_RST},

    {MCU_SEVEN_BIT, MCU_EXCRAM_GUARD_ERR_RST},

    {MCU_EIGHT_BIT, MCU_CRAM_GUARD_ERR_RST},

    {MCU_NINE_BIT, MCU_IBUS_GUARD_ERR_RST},

    {MCU_TEN_BIT, MCU_PBUS_GUARD_ERR_RST},

    {MCU_ELEVEN_BIT, MCU_HBUS_GUARD_ERR_RST},

    {MCU_TWELVE_BIT, MCU_RESERVED_RST},

    {MCU_THIRTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FOURTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FIFTEEN_BIT, MCU_RESERVED_RST},

    {MCU_SIXTEEN_BIT, MCU_RESERVED_RST},

    {MCU_SEVENTEEN_BIT, MCU_RESERVED_RST},

    {MCU_EIGHTEEN_BIT, MCU_RESERVED_RST},

    {MCU_NINETEEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTY_BIT, MCU_ICUM_DMAC_RAM_ECC2BIT_ERR_RST},

    {MCU_TWENTYONE_BIT, MCU_ICUM_DMAC_RAM_ECC1BIT_ERR_RST},

    {MCU_TWENTYTWO_BIT, MCU_DATA_TRANS_DMA_OR_DTS_ERR_RST},

    {MCU_TWENTYTHREE_BIT, MCU_DATA_TRANS_HBUS_ERR_RST},

    {MCU_TWENTYFOUR_BIT, MCU_EXT_ERRIN0_RST},

    {MCU_TWENTYFIVE_BIT, MCU_EXT_ERRIN1_RST},

    {MCU_TWENTYSIX_BIT, MCU_EXT_ERRIN2_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_EXT_ERRIN3_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_EXT_ERRIN4_RST},

    {MCU_TWENTYNINE_BIT, MCU_EXT_ERRIN5_RST},

    {MCU_THIRTY_BIT, MCU_EXT_ERRIN6_RST},

    {MCU_THIRTYONE_BIT, MCU_EXT_ERRIN7_RST}
  },
  /* Index: 6 - ECMMESSTR register 6 */
  {
    {MCU_ZERO_BIT, MCU_SW_ALARM0_RST},

    {MCU_ONE_BIT, MCU_SW_ALARM1_RST},

    {MCU_TWO_BIT, MCU_SW_ALARM2_RST},

    {MCU_THREE_BIT, MCU_SW_ALARM3_RST},

    {MCU_FOUR_BIT, MCU_SW_ALARM4_RST},

    {MCU_FIVE_BIT, MCU_SW_ALARM5_RST},

    {MCU_SIX_BIT, MCU_SW_ALARM6_RST},

    {MCU_SEVEN_BIT, MCU_RESERVED_RST},

    {MCU_EIGHT_BIT, MCU_ICUMHB_COMP_ERR_RST},

    {MCU_NINE_BIT, MCU_ACE0_COMPARE_ERR_RST},

    {MCU_TEN_BIT, MCU_ACE1_COMPARE_ERR_RST},

    {MCU_ELEVEN_BIT, MCU_ICUMHB_BUS_ROUTING_ERR_RST},

    {MCU_TWELVE_BIT, MCU_BUS_SECURITY_ECC_2BIT_ERR_RST},

    {MCU_THIRTEEN_BIT, MCU_BUS_SECURITY_ECC_1BIT_ERR_RST},

    {MCU_FOURTEEN_BIT, MCU_BUS_SECURITY_GUARD_ERR_RST},

    {MCU_FIFTEEN_BIT, MCU_BUS_SECURITY_DR_TRANS_ERR_RST},

    {MCU_SIXTEEN_BIT, MCU_ACE2_COMPARE_ERR_RST},

    {MCU_SEVENTEEN_BIT, MCU_ACE3_COMPARE_ERR_RST},

    {MCU_EIGHTEEN_BIT, MCU_RESERVED_RST},

    {MCU_NINETEEN_BIT, MCU_DFA_CRITICAL_ERR_RST},

    {MCU_TWENTY_BIT, MCU_DFA_NON_CRITICAL_ERR_RST},

    {MCU_TWENTYONE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTWO_BIT, MCU_CLMA_DFA_ERR_RST},

    {MCU_TWENTYTHREE_BIT, MCU_LRAM_DFA_ECC2_ERR_PE0_RST},

    {MCU_TWENTYFOUR_BIT, MCU_LRAM_DFA_ECC1_ERR_PE0_RST},

    {MCU_TWENTYFIVE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSIX_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_DFA_ECC_ERR_OFLOW_ERR_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_DFA_PARITY_ERR_RST},

    {MCU_TWENTYNINE_BIT, MCU_DFA_GUARD_ERR_RST},

    {MCU_THIRTY_BIT, MCU_RESERVED_RST},

    {MCU_THIRTYONE_BIT, MCU_RESERVED_RST}
  },
  /* Index: 7 - ECMMESSTR register 7 */
  {
    {MCU_ZERO_BIT, MCU_DCLS_COMP_ERR_PE0_RST},

    {MCU_ONE_BIT, MCU_DCLS_MODE_PE0_ERR_RST},

    {MCU_TWO_BIT, MCU_RESERVED_RST},

    {MCU_THREE_BIT, MCU_MODE_UNINT_DEBUG_ENABLE_PE0_RST},

    {MCU_FOUR_BIT, MCU_WDT_ERR_PE0_RST},

    {MCU_FIVE_BIT, MCU_CLMA_ERR_PE0_RST},

    {MCU_SIX_BIT, MCU_RESERVED_RST},

    {MCU_SEVEN_BIT, MCU_RESERVED_RST},

    {MCU_EIGHT_BIT, MCU_LRAM_ADR_OR_ECC2_ERR_PE0_RST},

    {MCU_NINE_BIT, MCU_LRAM_ECC1_ERR_PE0_RST},

    {MCU_TEN_BIT, MCU_LRAM_ERRADR_OFLOW_PE0_RST},

    {MCU_ELEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWELVE_BIT, MCU_ICACHE_ADR_OR_EDC_ERR_PE0_RST},

    {MCU_THIRTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FOURTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FIFTEEN_BIT, MCU_RESERVED_RST},

    {MCU_SIXTEEN_BIT, MCU_PEGUARD_ERR_PE0_RST},

    {MCU_SEVENTEEN_BIT, MCU_PEG_OTHER_LRAMREQ_PE0_RST},

    {MCU_EIGHTEEN_BIT, MCU_RESERVED_RST},

    {MCU_NINETEEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTY_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYONE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTWO_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTHREE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFOUR_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFIVE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSIX_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYNINE_BIT, MCU_RESERVED_RST},

    {MCU_THIRTY_BIT, MCU_RESERVED_RST},

    {MCU_THIRTYONE_BIT, MCU_DATA_ACCESS_ERR_PE0_RST}
  },
  /* Index: 8 - ECMMESSTR register 8 */
  {
    {MCU_ZERO_BIT, MCU_DCLS_COMP_ERR_PE1_RST},

    {MCU_ONE_BIT, MCU_DCLS_MODE_PE1_ERR_RST},

    {MCU_TWO_BIT, MCU_UNINT_DETECTION_PE1_RST},

    {MCU_THREE_BIT, MCU_MODE_UNINT_DEBUG_ENABLE_PE1_RST},

    {MCU_FOUR_BIT, MCU_WDT_ERR_PE1_RST},

    {MCU_FIVE_BIT, MCU_CLMA_ERR_PE1_RST},

    {MCU_SIX_BIT, MCU_RESERVED_RST},

    {MCU_SEVEN_BIT, MCU_RESERVED_RST},

    {MCU_EIGHT_BIT, MCU_LRAM_ADR_OR_ECC2_ERR_PE1_RST},

    {MCU_NINE_BIT, MCU_LRAM_ECC1_ERR_PE1_RST},

    {MCU_TEN_BIT, MCU_LRAM_ERRADR_OFLOW_PE1_RST},

    {MCU_ELEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWELVE_BIT, MCU_ICACHE_ADR_OR_EDC_ERR_PE1_RST},

    {MCU_THIRTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FOURTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FIFTEEN_BIT, MCU_RESERVED_RST},

    {MCU_SIXTEEN_BIT, MCU_PEGUARD_ERR_PE1_RST},

    {MCU_SEVENTEEN_BIT, MCU_PEG_OTHER_LRAMREQ_PE1_RST},

    {MCU_EIGHTEEN_BIT, MCU_RESERVED_RST},

    {MCU_NINETEEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTY_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYONE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTWO_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTHREE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFOUR_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFIVE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSIX_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYNINE_BIT, MCU_RESERVED_RST},

    {MCU_THIRTY_BIT, MCU_RESERVED_RST},

    {MCU_THIRTYONE_BIT, MCU_DATA_ACCESS_ERR_PE1_RST}
  },
  /* Index: 9 - ECMMESSTR register 9 */
  {
    {MCU_ZERO_BIT, MCU_DCLS_COMP_ERR_PE2_RST},

    {MCU_ONE_BIT, MCU_DCLS_MODE_PE2_ERR_RST},

    {MCU_TWO_BIT, MCU_UNINT_DETECTION_PE2_RST},

    {MCU_THREE_BIT, MCU_MODE_UNINT_DEBUG_ENABLE_PE2_RST},

    {MCU_FOUR_BIT, MCU_WDT_ERR_PE2_RST},

    {MCU_FIVE_BIT, MCU_CLMA_ERR_PE2_RST},

    {MCU_SIX_BIT, MCU_RESERVED_RST},

    {MCU_SEVEN_BIT, MCU_RESERVED_RST},

    {MCU_EIGHT_BIT, MCU_LRAM_ADR_OR_ECC2_ERR_PE2_RST},

    {MCU_NINE_BIT, MCU_LRAM_ECC1_ERR_PE2_RST},

    {MCU_TEN_BIT, MCU_LRAM_ERRADR_OFLOW_PE2_RST},

    {MCU_ELEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWELVE_BIT, MCU_ICACHE_ADR_OR_EDC_ERR_PE2_RST},

    {MCU_THIRTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FOURTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FIFTEEN_BIT, MCU_RESERVED_RST},

    {MCU_SIXTEEN_BIT, MCU_PEGUARD_ERR_PE2_RST},

    {MCU_SEVENTEEN_BIT, MCU_PEG_OTHER_LRAMREQ_PE2_RST},

    {MCU_EIGHTEEN_BIT, MCU_RESERVED_RST},

    {MCU_NINETEEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTY_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYONE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTWO_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTHREE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFOUR_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFIVE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSIX_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYNINE_BIT, MCU_RESERVED_RST},

    {MCU_THIRTY_BIT, MCU_RESERVED_RST},

    {MCU_THIRTYONE_BIT, MCU_DATA_ACCESS_ERR_PE2_RST}
  },
  /* Index: 10 - ECMMESSTR register 10 */
  {
    {MCU_ZERO_BIT, MCU_DCLS_COMP_ERR_PE3_RST},

    {MCU_ONE_BIT, MCU_DCLS_MODE_PE3_ERR_RST},

    {MCU_TWO_BIT, MCU_UNINT_DETECTION_PE3_RST},

    {MCU_THREE_BIT, MCU_MODE_UNINT_DEBUG_ENABLE_PE3_RST},

    {MCU_FOUR_BIT, MCU_WDT_ERR_PE3_RST},

    {MCU_FIVE_BIT, MCU_CLMA_ERR_PE3_RST},

    {MCU_SIX_BIT, MCU_RESERVED_RST},

    {MCU_SEVEN_BIT, MCU_RESERVED_RST},

    {MCU_EIGHT_BIT, MCU_LRAM_ADR_OR_ECC2_ERR_PE3_RST},

    {MCU_NINE_BIT, MCU_LRAM_ECC1_ERR_PE3_RST},

    {MCU_TEN_BIT, MCU_LRAM_ERRADR_OFLOW_PE3_RST},

    {MCU_ELEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWELVE_BIT, MCU_ICACHE_ADR_OR_EDC_ERR_PE3_RST},

    {MCU_THIRTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FOURTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FIFTEEN_BIT, MCU_RESERVED_RST},

    {MCU_SIXTEEN_BIT, MCU_PEGUARD_ERR_PE3_RST},

    {MCU_SEVENTEEN_BIT, MCU_PEG_OTHER_LRAMREQ_PE3_RST},

    {MCU_EIGHTEEN_BIT, MCU_RESERVED_RST},

    {MCU_NINETEEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTY_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYONE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTWO_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTHREE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFOUR_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFIVE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSIX_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYNINE_BIT, MCU_RESERVED_RST},

    {MCU_THIRTY_BIT, MCU_RESERVED_RST},

    {MCU_THIRTYONE_BIT, MCU_DATA_ACCESS_ERR_PE3_RST}
  },
  /* Index: 11 - ECMMESSTR register 11 */
  {
    {MCU_ZERO_BIT, MCU_DCLS_COMP_ERR_PE4_RST},

    {MCU_ONE_BIT, MCU_DCLS_MODE_PE4_ERR_RST},

    {MCU_TWO_BIT, MCU_UNINT_DETECTION_PE4_RST},

    {MCU_THREE_BIT, MCU_MODE_UNINT_DEBUG_ENABLE_PE4_RST},

    {MCU_FOUR_BIT, MCU_WDT_ERR_PE4_RST},

    {MCU_FIVE_BIT, MCU_CLMA_ERR_PE4_RST},

    {MCU_SIX_BIT, MCU_RESERVED_RST},

    {MCU_SEVEN_BIT, MCU_RESERVED_RST},

    {MCU_EIGHT_BIT, MCU_LRAM_ADR_OR_ECC2_ERR_PE4_RST},

    {MCU_NINE_BIT, MCU_LRAM_ECC1_ERR_PE4_RST},

    {MCU_TEN_BIT, MCU_LRAM_ERRADR_OFLOW_PE4_RST},

    {MCU_ELEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWELVE_BIT, MCU_ICACHE_ADR_OR_EDC_ERR_PE4_RST},

    {MCU_THIRTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FOURTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FIFTEEN_BIT, MCU_RESERVED_RST},

    {MCU_SIXTEEN_BIT, MCU_PEGUARD_ERR_PE4_RST},

    {MCU_SEVENTEEN_BIT, MCU_PEG_OTHER_LRAMREQ_PE4_RST},

    {MCU_EIGHTEEN_BIT, MCU_RESERVED_RST},

    {MCU_NINETEEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTY_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYONE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTWO_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTHREE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFOUR_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFIVE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSIX_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYNINE_BIT, MCU_RESERVED_RST},

    {MCU_THIRTY_BIT, MCU_RESERVED_RST},

    {MCU_THIRTYONE_BIT, MCU_DATA_ACCESS_ERR_PE4_RST}
  },
  /* Index: 12 - ECMMESSTR register 12 */
  {
    {MCU_ZERO_BIT, MCU_RESERVED_RST},

    {MCU_ONE_BIT, MCU_RESERVED_RST},

    {MCU_TWO_BIT, MCU_UNINT_DETECTION_PE5_RST},

    {MCU_THREE_BIT, MCU_MODE_UNINT_DEBUG_ENABLE_PE5_RST},

    {MCU_FOUR_BIT, MCU_WDT_ERR_PE5_RST},

    {MCU_FIVE_BIT, MCU_RESERVED_RST},

    {MCU_SIX_BIT, MCU_RESERVED_RST},

    {MCU_SEVEN_BIT, MCU_RESERVED_RST},

    {MCU_EIGHT_BIT, MCU_LRAM_ADR_OR_ECC2_ERR_PE5_RST},

    {MCU_NINE_BIT, MCU_LRAM_ECC1_ERR_PE5_RST},

    {MCU_TEN_BIT, MCU_LRAM_ERRADR_OFLOW_PE5_RST},

    {MCU_ELEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWELVE_BIT, MCU_ICACHE_ADR_OR_EDC_ERR_PE5_RST},

    {MCU_THIRTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FOURTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FIFTEEN_BIT, MCU_RESERVED_RST},

    {MCU_SIXTEEN_BIT, MCU_PEGUARD_ERR_PE5_RST},

    {MCU_SEVENTEEN_BIT, MCU_PEG_OTHER_LRAMREQ_PE5_RST},

    {MCU_EIGHTEEN_BIT, MCU_RESERVED_RST},

    {MCU_NINETEEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTY_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYONE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTWO_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTHREE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFOUR_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFIVE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSIX_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYNINE_BIT, MCU_RESERVED_RST},

    {MCU_THIRTY_BIT, MCU_RESERVED_RST},

    {MCU_THIRTYONE_BIT, MCU_DATA_ACCESS_ERR_PE5_RST}
  },
  /* Index: 13 - ECMMESSTR register 13 */
  {
    {MCU_ZERO_BIT, MCU_DCLS_COMP_ERR_PE6_RST},

    {MCU_ONE_BIT, MCU_DCLS_MODE_PE6_ERR_RST},

    {MCU_TWO_BIT, MCU_UNINT_DETECTION_PE6_RST},

    {MCU_THREE_BIT, MCU_MODE_UNINT_DEBUG_ENABLE_PE6_RST},

    {MCU_FOUR_BIT, MCU_WDT_ERR_PE6_RST},

    {MCU_FIVE_BIT, MCU_CLMA_ERR_PE6_RST},

    {MCU_SIX_BIT, MCU_RESERVED_RST},

    {MCU_SEVEN_BIT, MCU_RESERVED_RST},

    {MCU_EIGHT_BIT, MCU_LRAM_ADR_OR_ECC2_ERR_PE6_RST},

    {MCU_NINE_BIT, MCU_LRAM_ECC1_ERR_PE6_RST},

    {MCU_TEN_BIT, MCU_LRAM_ERRADR_OFLOW_PE6_RST},

    {MCU_ELEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWELVE_BIT, MCU_ICACHE_ADR_OR_EDC_ERR_PE6_RST},

    {MCU_THIRTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FOURTEEN_BIT, MCU_RESERVED_RST},

    {MCU_FIFTEEN_BIT, MCU_RESERVED_RST},

    {MCU_SIXTEEN_BIT, MCU_PEGUARD_ERR_PE6_RST},

    {MCU_SEVENTEEN_BIT, MCU_RESERVED_RST},

    {MCU_EIGHTEEN_BIT, MCU_RESERVED_RST},

    {MCU_NINETEEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTY_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYONE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTWO_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYTHREE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFOUR_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYFIVE_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSIX_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYSEVEN_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYEIGHT_BIT, MCU_RESERVED_RST},

    {MCU_TWENTYNINE_BIT, MCU_RESERVED_RST},

    {MCU_THIRTY_BIT, MCU_RESERVED_RST},

    {MCU_THIRTYONE_BIT, MCU_DATA_ACCESS_ERR_PE6_RST}
  }
};

/* Array for MCU ecm setting configuration */
CONST(Mcu_EcmSettingType, MCU_CONFIG_DATA) Mcu_GaaEcmSetting[] =                                                        /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - */
  {
    /* ucEcmErrorOutputMode */
    (uint8)0x00U,

    /* ucEcmDelayTimerCtrl */
    0x00U,

    /* ulEcmDelayTimerOverflowValue */
    0x0000FFFFUL,

    /* ulEcmErrorOutClrMaskCntValue */
    0x00000000UL,

    /* Index: 4 - aaEcmInternalResetRegValue */
    {
      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000010UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL,

      0x00000000UL
    },
    /* Index: 5 - aaFEIntEnable */
    {
      /* Index: 0 - */
      {
        MCU_FALSE,

        MCU_FALSE,

        MCU_FALSE
      },
      /* Index: 1 - */
      {
        MCU_FALSE,

        MCU_FALSE,

        MCU_FALSE
      },
      /* Index: 2 - */
      {
        MCU_FALSE,

        MCU_FALSE,

        MCU_FALSE
      },
      /* Index: 3 - */
      {
        MCU_FALSE,

        MCU_FALSE,

        MCU_FALSE
      },
      /* Index: 4 - */
      {
        MCU_FALSE,

        MCU_FALSE,

        MCU_FALSE
      },
      /* Index: 5 - */
      {
        MCU_FALSE,

        MCU_FALSE,

        MCU_FALSE
      },
      /* Index: 6 - */
      {
        MCU_FALSE,

        MCU_FALSE,

        MCU_FALSE
      }
    },
    /* Index: 6 - aaEIIntEnable */
    {
      MCU_FALSE,

      MCU_FALSE,

      MCU_FALSE
    },
    /* Index: 7 - aaEIDCLSIntEnable */
    {
      MCU_FALSE,

      MCU_FALSE,

      MCU_FALSE
    },
    /* Index: 8 - aaEIC8IntEnable */
    {
      MCU_FALSE,

      MCU_FALSE,

      MCU_FALSE
    },
    /* pEcmCommonRegInitSetting */
    &Mcu_GaaEcmCommonRegInitSetting[0],

    /* pEcmCommonRegAfterInitLramSetting */
    &Mcu_GaaEcmCommonRegAfterInitLramSetting[0],

    /* pEcmCommonRegAfterInitCramSetting */
    &Mcu_GaaEcmCommonRegAfterInitCramSetting[0],

    /* pEcmCommonDelayTimerRegInitSetting */
    &Mcu_GaaEcmCommonDelayTimerRegInitSetting[0],

    /* pEcmCommonDelayTimerRegAfterInitLramSetting */
    &Mcu_GaaEcmCommonDelayTimerRegAfterInitLramSetting[0],

    /* pEcmCommonDelayTimerRegAfterInitCramSetting */
    &Mcu_GaaEcmCommonDelayTimerRegAfterInitCramSetting[0],

    /* pEcmErrorOutClrConfigRegSetting */
    &Mcu_GaaEcmErrorOutClrConfigRegSetting[0],

    /* pEcmErrorOutClearRegTypeSetting */
    &Mcu_GaaEcmErrorOutClearRegTypeSetting[0],

    /* Index: 17 - aaEcmRamErrMask */
    {
      (uint32)0x00000000UL,

      (uint32)0x00000000UL,

      (uint32)0x00000000UL,

      (uint32)0x00000707UL,

      (uint32)0x00000000UL,

      (uint32)0x00000000UL,

      (uint32)0x00000000UL,

      (uint32)0x00000700UL,

      (uint32)0x00000700UL,

      (uint32)0x00000700UL,

      (uint32)0x00000700UL,

      (uint32)0x00000700UL,

      (uint32)0x00000700UL,

      (uint32)0x00000700UL
    },
    /* pEcmFEINTRegsAddr */
    &Mcu_GaaEcmFEINTRegsAddr[0],

    /* Index: 19 - aaEcmFEIntTypeSettingValue */
    {
      /* Index: 0 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 1 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 2 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 3 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 4 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 5 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 6 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      }
    },
    /* Index: 20 - aaEcmFEIntSettingValue */
    {
      /* Index: 0 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 1 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 2 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 3 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 4 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 5 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 6 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      }
    },
    /* Index: 21 - aaEcmEIC8IntTypeSettingValue */
    {
      /* Index: 0 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 1 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 2 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 3 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 4 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 5 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 6 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      }
    },
    /* Index: 22 - aaEcmEIC8IntSettingValue */
    {
      /* Index: 0 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 1 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 2 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 3 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 4 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 5 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 6 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      }
    },
    /* Index: 23 - aaEcmEIC9IntTypeSettingValue */
    {
      /* Index: 0 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 1 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 2 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 3 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 4 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 5 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 6 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      }
    },
    /* Index: 24 - aaEcmEIC9IntSettingValue */
    {
      /* Index: 0 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 1 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 2 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 3 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 4 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 5 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      },
      /* Index: 6 - */
      {
        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL,

        0x00000000UL
      }
    }
  }
};

/* Array for MCU Init configuration */
CONST(Mcu_ConfigType, MCU_CONFIG_DATA) Mcu_GaaConfiguration[] =                                                         /* PRQA S 1502 # JV-01 */
{
  /* Index: 0 - McuModuleConfiguration */
  {
    /* ulStartOfDbToc */
    0x0ED94228UL,

    /* ucNofClockSettings */
    (uint8)0x01,

    /* pClockSetting */
    &Mcu_GaaClockSetting[0],

    /* pRamSetting */
    &Mcu_GaaRamSetting[0],

    /* pEcmSetting */
    &Mcu_GaaEcmSetting[0],

    /* pFeintNotificationPtr */
    &Mcu_EcmNotification,

    /* pEiintDCLSNotificationPtr */
    &Mcu_EcmNotification,

    /* pEiintNotificationPtr */
    &Mcu_EcmNotification,

    /* pModeSetting */
    &Mcu_GaaModeSetting[0],

    /* pClockHwInfo */
    &Mcu_GstClockHwInfo,

    /* pRstHwInfo */
    &Mcu_GstResetHwInfo,

    /* pStbHwInfo */
    &Mcu_GstStbHwInfo,

    /* pWUFMONHwInfo */
    &Mcu_GstWUFMONHwInfo,

    /* pWUFHwInfo */
    &Mcu_GaaWakeUpRegsAddr,

    /* pIOBufferHoldHwInfo */
    &Mcu_GstIOBufferHoldHwInfo,

    /* pEccHwInfo */
    &Mcu_GstEccHwInfo,

    /* pEcmHwInfo */
    &Mcu_GstEcmHwInfo
  }
};

#define MCU_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */



/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

