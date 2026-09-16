/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Wdg_PBcfg.c                                                                                         */
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
/* TOOL VERSION:  WdgU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\wdg\generator\U2B24-E\R2211_wdg_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_wdg.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_wdg.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_wdg.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:50:08
 */


/***********************************************************************************************************************
**                      Instance Index                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Wdg.h"

#include "Wdg_Ram.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment..                                              */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping ).      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object 'name' is only referenced in the translation unit where it is defined.            */
/* Rule                : MISRA-C:2012 Rule-8.7, CERT-C:1.2.4 CERTCCM DCL15, DCL19, CWE Rule CWE-398, CWE-569          */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other    */
/*                       C source files                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : '%s' has external linkage and is being defined without any previous declaration.             */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0303)    : [I] Cast between a pointer to volatile object and an integral type.                          */
/* Rule                : MISRA C:2012 Rule-11.4,  CERT-C:1.2.4 CERTCCM INT36, CWE Rule CWE-398, CWE-569               */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/*                       REFERENCE - ISO:C90-6.3.1 Primary Expressions                                                */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is           */
/*                       accepted.                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : [I] Cast between a pointer to object and an integral type.                                   */
/* Rule                : MISRA-C:2012 Rule-11.4, CERT-C:1.2.4 CERTCCM INT36, CWE Rule CWE-398, CWE-569, CWE-738       */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1502)    : The object '%1s' is defined but is not used within this project.                             */
/* Rule                : MISRA C:2012 Rule-2.8, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : This is accepted, due to the module's object is exported for usage.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/




/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
/* AUTOSAR release version information. */
#define WDG_PBCFG_C_AR_RELEASE_MAJOR_VERSION                                    4U

#define WDG_PBCFG_C_AR_RELEASE_MINOR_VERSION                                    8U

#define WDG_PBCFG_C_AR_RELEASE_REVISION_VERSION                                 0U

/* File version information. */
#define WDG_PBCFG_C_SW_MAJOR_VERSION                                            2U

#define WDG_PBCFG_C_SW_MINOR_VERSION                                            4U


/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/

#if (WDG_PBTYPES_AR_RELEASE_MAJOR_VERSION != WDG_PBCFG_C_AR_RELEASE_MAJOR_VERSION)
      #error "Wdg_PBcfg.c : Mismatch in Release Major Version" 
#endif
#if (WDG_PBTYPES_AR_RELEASE_MINOR_VERSION != WDG_PBCFG_C_AR_RELEASE_MINOR_VERSION)
      #error "Wdg_PBcfg.c : Mismatch in Release Minor Version" 
#endif
#if (WDG_PBTYPES_AR_RELEASE_REVISION_VERSION != WDG_PBCFG_C_AR_RELEASE_REVISION_VERSION)
      #error "Wdg_PBcfg.c : Mismatch in Release Revision Version" 
#endif
#if (WDG_PBTYPES_SW_MAJOR_VERSION != WDG_PBCFG_C_SW_MAJOR_VERSION)
      #error "Wdg_PBcfg.c : Mismatch in Software Major Version" 
#endif
#if (WDG_PBTYPES_SW_MINOR_VERSION != WDG_PBCFG_C_SW_MINOR_VERSION)
      #error "Wdg_PBcfg.c : Mismatch in Software Minor Version" 
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/


#define WDG_CORE0_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
#include "Wdg_MemMap.h"

/* Global variable to store the current watchdog driver mode */
static volatile VAR(WdgIf_ModeType, WDG_VAR_NO_INIT) Wdg_GddCurrentMode_Core0;


#define WDG_CORE0_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define WDG_CORE1_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
#include "Wdg_MemMap.h"

/* Global variable to store the current watchdog driver mode */
static volatile VAR(WdgIf_ModeType, WDG_VAR_NO_INIT) Wdg_GddCurrentMode_Core1;


#define WDG_CORE1_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define WDG_CORE0_START_SEC_VAR_NO_INIT_32_LOCAL
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Global variable to store the trigger counter value */
static volatile VAR(uint32, WDG_VAR_NO_INIT) Wdg_GulTriggerCounter_Core0;


#define WDG_CORE0_STOP_SEC_VAR_NO_INIT_32_LOCAL
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define WDG_CORE1_START_SEC_VAR_NO_INIT_32_LOCAL
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Global variable to store the trigger counter value */
static volatile VAR(uint32, WDG_VAR_NO_INIT) Wdg_GulTriggerCounter_Core1;


#define WDG_CORE1_STOP_SEC_VAR_NO_INIT_32_LOCAL
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define WDG_START_SEC_CONST_8
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Core Id to index table */
const uint8 Wdg_GaaGetCoreId2Index[WDG_SUPPORTED_CORE_MAX_NUM] = {0x0U, 0x1U, 0xFFU, 0xFFU, 0xFFU, 0xFFU};

#define WDG_STOP_SEC_CONST_8
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define WDG_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* This array contains unit specific information for all configured unit */
CONST(Wdg_ConfigUnit, WDG_CONFIG_DATA) Wdg_GaaConfigUnit_Core0 =                                                        /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* blArbitraryTimingInterruptMode */
  WDG_TRUE,
  /* blEnableDelayTimerStart */
  WDG_TRUE,
  /* blErrorOutputMask */
  WDG_TRUE,
  /* usInterruptOutputTimingSetting */
  20000U,
  /* usWindowOpenPeriodSetting */
  10000U,
  /* ddWdtbUnitNumber */
  WDG_WDTB0,
  /* ddErrorModeSet */
  WDG_RESET_MODE,
  /* ulImrMask */
  (uint32)0xFFBFFFFFUL,
  /* ulEcmincfgEInt */
  0x00U,
  /* ulEnableResetMode */
  (uint32)0x00000010UL,
  /* ulDisableResetMode */
  (uint32)0xFFFFFFEFUL,
  /* ulInitTimerCountValue */
  0x00000010UL,
  /* ulSlowTimeValue */
  0x00026666UL,
  /* ulFastTimeValue */
  0x000004CDUL,
  /* ulSettingTimeValue */
  0x0000FA00UL,
  /* ucWdtbmdSlowValue */
  0x7CU,
  /* ucWdtbmdFastValue */
  0x0CU,
  /* ucWdtbmdDefaultValue */
  0x7CU,
  /* ddWdtbmdDefaultMode */
  WDGIF_SLOW_MODE,
  /* ddActivationCodeMode */
  WDG_FIXED_ACTIVATION_CODE_MODE
};

/* This array contains unit specific information for all configured unit */
CONST(Wdg_ConfigUnit, WDG_CONFIG_DATA) Wdg_GaaConfigUnit_Core1 =                                                        /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* blArbitraryTimingInterruptMode */
  WDG_TRUE,
  /* blEnableDelayTimerStart */
  WDG_TRUE,
  /* blErrorOutputMask */
  WDG_TRUE,
  /* usInterruptOutputTimingSetting */
  20000U,
  /* usWindowOpenPeriodSetting */
  10000U,
  /* ddWdtbUnitNumber */
  WDG_WDTB1,
  /* ddErrorModeSet */
  WDG_FE_LEVEL_INTERRUPT_MODE,
  /* ulImrMask */
  (uint32)0xFFBFFFFFUL,
  /* ulEcmincfgEInt */
  (uint32)0x00000010UL,
  /* ulEnableResetMode */
  (uint32)0x00000010UL,
  /* ulDisableResetMode */
  (uint32)0xFFFFFFEFUL,
  /* ulInitTimerCountValue */
  0x00000010UL,
  /* ulSlowTimeValue */
  0x00026666UL,
  /* ulFastTimeValue */
  0x000004CDUL,
  /* ulSettingTimeValue */
  0x0000FA00UL,
  /* ucWdtbmdSlowValue */
  0x7CU,
  /* ucWdtbmdFastValue */
  0x0CU,
  /* ucWdtbmdDefaultValue */
  0x7CU,
  /* ddWdtbmdDefaultMode */
  WDGIF_SLOW_MODE,
  /* ddActivationCodeMode */
  WDG_FIXED_ACTIVATION_CODE_MODE
};

/* This array contains unit specific information for all registers in the unit. */
CONST(Wdg_UnitRegister, WDG_CONFIG_DATA) Wdg_GaaUnitRegister_Core0 =                                                    /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* WDTBAddress */
  (P2VAR(volatile Wdg_WDTBAddress, TYPEDEF, REGSPACE))0xFFBF1000UL,                                                     /* PRQA S 0303 # JV-01 */
  /* ECMAddress */
  (P2VAR(volatile Wdg_ECMAddress, TYPEDEF, REGSPACE))0xFFCCD020UL,                                                      /* PRQA S 0303 # JV-01 */
  /* FEINTAddress */
  (P2VAR(volatile Wdg_FEINTAddress, TYPEDEF, REGSPACE))0xFF9A3B00UL,                                                    /* PRQA S 0303 # JV-01 */
  /* pEcmINCFG */
  (P2VAR(uint32, TYPEDEF, REGSPACE))0xFFCCD05CUL,                                                                       /* PRQA S 0306, 3432 # JV-01, JV-01 */
  /* pEcmMESSTR */
  NULL_PTR,
  /* pImr */
  (P2VAR(uint32, TYPEDEF, REGSPACE))0xFFFC40F0UL,                                                                       /* PRQA S 0306, 3432 # JV-01, JV-01 */
  /* pEic */
  (P2VAR(uint16, TYPEDEF, REGSPACE))0xFFFC402CUL                                                                        /* PRQA S 0306, 3432 # JV-01, JV-01 */
};

/* This array contains unit specific information for all registers in the unit. */
CONST(Wdg_UnitRegister, WDG_CONFIG_DATA) Wdg_GaaUnitRegister_Core1 =                                                    /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* WDTBAddress */
  (P2VAR(volatile Wdg_WDTBAddress, TYPEDEF, REGSPACE))0xFF899000UL,                                                     /* PRQA S 0303 # JV-01 */
  /* ECMAddress */
  (P2VAR(volatile Wdg_ECMAddress, TYPEDEF, REGSPACE))0xFFCCD024UL,                                                      /* PRQA S 0303 # JV-01 */
  /* FEINTAddress */
  (P2VAR(volatile Wdg_FEINTAddress, TYPEDEF, REGSPACE))0xFF9A3C00UL,                                                    /* PRQA S 0303 # JV-01 */
  /* pEcmINCFG */
  (P2VAR(uint32, TYPEDEF, REGSPACE))0xFFCCD09CUL,                                                                       /* PRQA S 0306, 3432 # JV-01, JV-01 */
  /* pEcmMESSTR */
  (P2VAR(uint32, TYPEDEF, REGSPACE))0xFFCCE068UL,                                                                       /* PRQA S 0306, 3432 # JV-01, JV-01 */
  /* pImr */
  (P2VAR(uint32, TYPEDEF, REGSPACE))0xFFFC80F0UL,                                                                       /* PRQA S 0306, 3432 # JV-01, JV-01 */
  /* pEic */
  (P2VAR(uint16, TYPEDEF, REGSPACE))0xFFFC802CUL                                                                        /* PRQA S 0306, 3432 # JV-01, JV-01 */
};

#define WDG_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define WDG_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Wdg_MemMap.h"


/* Structure for Watchdog Unit init configuration */
CONST(Wdg_ConfigType, WDG_CONFIG_DATA) Wdg_GstConfiguration[] =                                                         /* PRQA S 1502 # JV-01 */
{
  /* Index: 0 - Wdg_GstConfiguration */
  {
    /* ulStartOfDbToc */
    0x0ED98220UL,

    /* Index: 1 - ConfigUnit */
    {
      /* UnitConfig_Core0 */
      &Wdg_GaaConfigUnit_Core0,

      /* UnitConfig_Core1 */
      &Wdg_GaaConfigUnit_Core1
    },
    /* Index: 2 - UnitRegister */
    {
      /* UnitConfigRegister_Core0 */
      &Wdg_GaaUnitRegister_Core0,

      /* UnitConfigRegister_Core1 */
      &Wdg_GaaUnitRegister_Core1
    }
  }
};

#define WDG_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Wdg_MemMap.h"


#define WDG_START_SEC_CONST_32
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Common access point to each core data */
CONST(Wdg_GlobalAccessPointType, WDG_CONFIG_DATA) Wdg_GaaGlobalAccPoint[WDG_SUPPORTED_CORE_CONFIGURED_NUM] =
{
  /* Index: 0 - Core_0 */
  {
    /* pCurrentMode */
    &Wdg_GddCurrentMode_Core0,

    /* pTriggerCounter */
    &Wdg_GulTriggerCounter_Core0
  },
  /* Index: 1 - Core_1 */
  {
    /* pCurrentMode */
    &Wdg_GddCurrentMode_Core1,

    /* pTriggerCounter */
    &Wdg_GulTriggerCounter_Core1
  }
};

#define WDG_STOP_SEC_CONST_32
#include "Wdg_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */



/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

