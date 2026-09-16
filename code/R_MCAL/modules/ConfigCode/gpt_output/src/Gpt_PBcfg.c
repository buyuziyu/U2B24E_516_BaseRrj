/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_PBcfg.c                                                                                         */
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
/* TOOL VERSION:  GptU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\gpt\generator\U2B24-E\R2211_gpt_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_gpt.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuM\xml\EcuM_gpt.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_gpt.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_gpt.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  13 Jul 2026 - 15:38:56
 */


/***********************************************************************************************************************
**                      Instance Index                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Gpt.h"

#include "Gpt_PBTypes.h"

#include "Gpt_TAU_PBTypes.h"

#include "Gpt_OSTM_PBTypes.h"

#include "Gpt_OSTM_Ram.h"

#include "Gpt_TAUJ_PBTypes.h"

#include "Gpt_TAUJ_Ram.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0315)    : Implicit conversion from a pointer to object type to a pointer to void.                      */
/* Rule                : MISRA C:2012 Dir-1.1, CWE Rule CWE-188, CWE-398, CWE-569                                     */
/* JV-01 Justification : Pointer to a void is a generic pointer type which can be use cast to any other pointer type. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0326)    : Cast between a pointer to void and an integral type.                                         */
/* Rule                : CERTCCM EXP36, INT36, MISRA C:2012 Rule-11.6, CWE Rule CWE-398, CWE-569, CWE-738             */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped.          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0778)    : Identifier matches other identifier(s) (e.g. '%s') in first 31 characters - program does     */
/*                       not conform strictly to ISO:C90.                                                             */
/* Rule                : CERTCCM DCL23, DCL40, MISRA C:2012 Dir-1.1, CWE Rule CWE-736                                 */
/* JV-01 Justification : Compiler will distinguish numerous characters, so this is accepted.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0777)    : External identifier does not differ from other identifier(s) (e.g. '%s') within the          */
/*                       specified number of significant characters.                                                  */
/* Rule                : CERTCCM DCL23, DCL40, MISRA C:2012 Dir-1.1, CWE Rule CWE-736                                 */
/* JV-01 Justification : Compiler will distinguish numerous characters, so this is accepted.                          */
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
/* Message (1:1531)    : The object '%1s' is referenced in only one translation unit - but not the one in which it    */
/*                       is defined.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.7, CERTCCM DCL15, DCL19, CWE Rule CWE-398, CWE-569                       */
/* JV-01 Justification : Followed coding rules, the objects (global variable/const) is define in separated source     */
/*                       file, so this could be accepted                                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1502)    : The object 'name' is defined but is not used within this project.                            */
/* Rule                : MISRA C:2012 Rule-2.8, CWE Rule CWE-398, CWE-569, CERTC Rule MSC13                           */
/* JV-01 Justification : Array is used in another part of driver code. There is no problem in use                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
#define GPT_PBCFG_C_AR_RELEASE_MAJOR_VERSION                                    4U
#define GPT_PBCFG_C_AR_RELEASE_MINOR_VERSION                                    8U
#define GPT_PBCFG_C_AR_RELEASE_REVISION_VERSION                                 0U
#define GPT_PBCFG_C_SW_MAJOR_VERSION                                            2U
#define GPT_PBCFG_C_SW_MINOR_VERSION                                            4U

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/
#if (GPT_PBTYPES_AR_RELEASE_MAJOR_VERSION != GPT_PBCFG_C_AR_RELEASE_MAJOR_VERSION)
   #error "Gpt_PBcfg.c : Mismatch in Release Major Version"
#endif

  #if (GPT_PBTYPES_AR_RELEASE_MINOR_VERSION != GPT_PBCFG_C_AR_RELEASE_MINOR_VERSION)
   #error "Gpt_PBcfg.c : Mismatch in Release Minor Version"
#endif

  #if (GPT_PBTYPES_AR_RELEASE_REVISION_VERSION != GPT_PBCFG_C_AR_RELEASE_REVISION_VERSION)
   #error "Gpt_PBcfg.c : Mismatch in Release Revision Version"
#endif

  #if (GPT_PBTYPES_SW_MAJOR_VERSION != GPT_PBCFG_C_SW_MAJOR_VERSION)
   #error "Gpt_PBcfg.c : Mismatch in Software Major Version"
#endif

  #if (GPT_PBTYPES_SW_MINOR_VERSION != GPT_PBCFG_C_SW_MINOR_VERSION)
   #error "Gpt_PBcfg.c : Mismatch in Software Minor Version"
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/
#define GPT_START_SEC_VAR_INIT_BOOLEAN
#include "Gpt_MemMap.h"

/* Indicate the status of Initialization */
VAR(volatile boolean, GPT_VAR_INIT) Gpt_GblDriverStatus = GPT_UNINITIALIZED;                                            /* PRQA S 1504, 3408 # JV-01, JV-01 */

#define GPT_STOP_SEC_VAR_INIT_BOOLEAN
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define GPT_START_SEC_VAR_NO_INIT_PTR
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Global pointer variable for channel configuration */
P2CONST(Gpt_ChannelConfigType, GPT_VAR_NO_INIT, GPT_CONFIG_CONST) Gpt_GpChannelConfig;                                  /* PRQA S 1504, 3408 # JV-01, JV-01 */

#define GPT_STOP_SEC_VAR_NO_INIT_PTR
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define GPT_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RAM allocation for all active Channels */
VAR(volatile Gpt_ChannelRamDataType, GPT_VAR_NO_INIT) Gpt_GaaChannelRamData[GPT_TOTAL_CHANNELS_CONFIG];                 /* PRQA S 3408 # JV-01 */

#define GPT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */



#define GPT_START_SEC_VAR_INIT_PTR
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Pointer to function table for all timer IP */
P2CONST(Gpt_HwFuncTableType, GPT_VAR_INIT, GPT_CONFIG_DATA) Gpt_GaaHwFunc[] =                                           /* PRQA S 3408, 1531 # JV-01, JV-01 */
{
  /* GPT_HWIP_OSTM */
  &Gpt_OstmFunc,
  /* GPT_HWIP_TAUD */
  NULL_PTR,
  /* GPT_HWIP_TAUJ */
  &Gpt_TaujFunc,
  /* GPT_HWIP_ATU */
  NULL_PTR,
  /* GPT_HWIP_GTM */
  NULL_PTR
};

#define GPT_STOP_SEC_VAR_INIT_PTR
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define GPT_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Structure for Hardware IP configuration */
CONST(Gpt_HWIPType, GPT_CONFIG_DATA) Gpt_GaaHWIP[] =
{
  /* Index: 0 - ucIndex */
  {
    /* GPT_HWIP_OSTM */
    GPT_HWIP_OSTM
  },
  /* Index: 1 - ucIndex */
  {
    /* GPT_HWIP_TAUJ */
    GPT_HWIP_TAUJ
  }
};

/* Structure for each TAU Unit Configuration set */
CONST(Gpt_TAUUnitConfigType, GPT_CONFIG_DATA) Gpt_GaaTAUUnitConfig[] =                                                  /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* Index: 0 - TAUJ2 */
  {
    /* pTAUUnitUserCntlRegs */
    (P2VAR(void, TYPEDEF, REGSPACE)) 0xFFE80050UL,                                                                      /* PRQA S 0326 # JV-01 */

    /* pTAUUnitOsCntlRegs */
    (P2VAR(void, TYPEDEF, REGSPACE)) 0xFFE80090UL,                                                                      /* PRQA S 0326 # JV-01 */

    /* ucTimerType */
    GPT_HW_TAUJ,

    /* usTAUConfiguredChannelsValue */
    0x0008U,

    /* usPrescaler */
    0x0000U,

    /* ucBaudRate */
    0x4FU,

    /* blConfigurePrescaler */
    GPT_TRUE
  }
};

/* Structure for TAUJ Predef unit configuration */
CONST(Gpt_PredefTimerTAUJUnitConfigType, GPT_CONFIG_DATA) Gpt_GaaPT_TAUJUnitConfig[] =                                  /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - TAUJ2 */
  {
    /* pPT_TAUJUnitUserCntlRegs */
    (P2VAR(void, TYPEDEF, REGSPACE)) 0xFFE80050UL                                                                       /* PRQA S 0326 # JV-01 */
  }
};

/* Structure for TAUJ Predef channel configuration */
CONST(Gpt_PredefTimerTAUJChannelConfigType, GPT_CONFIG_DATA) Gpt_GaaPT_TAUJChannelConfig[] =                            /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* Index: 0 - GptPredefTimer1Us32BitConfiguration */
  {
    /* pPT_CDRReg */
    (P2VAR(void, TYPEDEF, REGSPACE)) 0xFFE8000CUL,                                                                      /* PRQA S 0326 # JV-01 */

    /* pPT_CMORReg */
    (P2VAR(void, TYPEDEF, REGSPACE)) 0xFFE8008CUL,                                                                      /* PRQA S 0326 # JV-01 */

    /* ucPT_ChannelBitValue */
    0x0008U,

    /* usPT_ModeSettingValue */
    0xC000U
  }
};

/* Structure for PreDef Timer Configuration set */
CONST(Gpt_PredefTimerConfigType, GPT_CONFIG_DATA) Gpt_GaaPredefTimerConfig[] =                                          /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* Index: 0 - (uint8)GPT_PREDEF_TIMER_1US_32BIT */
  {
    /* ucPredefTimerCounterType */
    (uint8)GPT_PREDEF_TIMER_1US_32BIT,

    /* ucPredefTimerType */
    GPT_HWIP_TAUJ,

    /* pPT_UnitConfig */
    &Gpt_GaaPT_TAUJUnitConfig[0],                                                                                       /* PRQA S 0315 # JV-01 */

    /* pPT_ChannelConfig */
    &Gpt_GaaPT_TAUJChannelConfig[0]                                                                                     /* PRQA S 0315 # JV-01 */
  }
};

/* Initialization of GPT Channel Configuration */
CONST(Gpt_ChannelConfigType, GPT_CONFIG_DATA) Gpt_GaaChannelConfig[] =                                                  /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* Index: 0 - GPT_OSTM0 */
  {
    /* ucTimerUnitIndex */
    0x00U,

    /* ucTimerType */
    (uint8)GPT_HW_OSTM,

    /* ucGptChannelMode */
    (uint8)GPT_CH_MODE_CONTINUOUS,

    /* pEICReg */
    (P2VAR(volatile uint16, TYPEDEF, REGSPACE))0xFFF802D0UL,                                                            /* PRQA S 0303 # JV-01 */

    /* pGptNotificationPointer */
    &Gpt_Notification_OSTM0,

    /* blGptWakeupSupport */
    GPT_FALSE,

    /* ucWakeupSourceId */
    GPT_NOWAKEUP,

    /* pHWIPChannelConfig */
    NULL_PTR,

    /* pOSTMUnitRegs */
    (P2VAR(Gpt_OSTMnUnitRegs, AUTOMATIC, REGSPACE)) 0xFFBF0000UL,                                                       /* PRQA S 0303, 3432 # JV-01, JV-01 */

    /* ucRamDataIndex */
    0x00U
  }
};

/* Structure for each Configuration Set */
CONST(Gpt_ConfigType, GPT_CONFIG_DATA) Gpt_GaaConfiguration[] =                                                         /* PRQA S 1502 # JV-01 */
{
  /* Index: 0 - Gpt_GaaConfiguration */
  {
    /* ulStartOfDbToc */
    0x0ED90220UL,

    /* pChannelConfig */
    &Gpt_GaaChannelConfig[0],                                                                                           /* PRQA S 0315 # JV-01 */

    /* pPredefTimerConfig */
    &Gpt_GaaPredefTimerConfig[0],                                                                                       /* PRQA S 0315 # JV-01 */

    /* Index: 3 - aaTimerUnitConfig */
    {
      /* Index: 0 - aaTimerUnitConfig[0] */
      {
        /* OSTMUnitConfig */
        NULL_PTR
      },
      /* Index: 1 - aaTimerUnitConfig[1] */
      {
        /* TAUJUnitConfig */
        &Gpt_GaaTAUUnitConfig[0]                                                                                        /* PRQA S 0315 # JV-01 */
      }
    }
  }
};

#define GPT_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define GPT_START_SEC_CONST_32
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Struct for Global Access Point to global variables */
CONST(Gpt_GlobalAccessPointType, GPT_CONST) Gpt_GaaGlobalAccPoint[] =                                                   /* PRQA S 3408 # JV-01 */
{
  /* Index: 0 - Core_0 */
  {
    /* pDriverState */
    &Gpt_GblDriverStatus,

    /* pChannelConfig */
    &Gpt_GpChannelConfig                                                                                                /* PRQA S 0315 # JV-01 */
  }
};

#define GPT_STOP_SEC_CONST_32
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define GPT_START_SEC_CONST_8
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Struct for GPT channel ID to HWIP */
CONST(uint8, GPT_CONST) Gpt_GaaChannel2IpType[] =                                                                       /* PRQA S 3408, 1531 # JV-01, JV-01 */
{
  /* GPT_OSTM0 */
  GPT_HWIP_OSTM
};

#define GPT_STOP_SEC_CONST_8
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */



/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

