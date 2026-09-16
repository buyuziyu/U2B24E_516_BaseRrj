/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Lin_PBcfg.c                                                                                         */
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
/* TOOL VERSION:  LinU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\lin\generator\U2B24-E\R2211_lin_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_lin.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuM\xml\EcuM_lin.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_lin.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_lin.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:49:41
 */


/***********************************************************************************************************************
**                      Instance Index                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
/* LIN post-build configuration header */
#include "Lin.h"
#include "Lin_Ram.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/**********************************************************************************************************************/
/* Message(2:0306)     : Cast between a pointer to object and an integral type.                                       */
/* Rule                : MISRA-C:2012 Rule 11.4, 11.6, CERT-C:1.2.4 CERTCCM INT36, CWE Rule CWE-398, CWE-569          */
/* JV-01 Justification : Void pointer is used in order to typecast to different channel structures later.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message(2:3432)     : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA-C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message(1:1504)     : The object 'name' is only referenced in the translation unit where it is defined.            */
/* Rule                : MISRA C:2012 Rule-8.7, CERT-C:1.2.4 CERTCCM DCL15, CWE Rule CWE-398, CWE-569                 */
/* JV-01 Justification : This is accepted since there is no problem with the software behavior.                       */
/*                       It is retained for future usage.                                                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message(4:5087)     : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA-C:2012 Rule-20.1, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : This is accepted, due to implementation for include memmap is following AUTOSAR rule.        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : %s' has external linkage and is being defined without any previous declaration.              */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1502)    : The object '%1s' is defined but is not used within this project.                             */
/* Rule                : MISRA-C:2012 Rule 2.8, CERTC 3.6.0 Rule MSC13, CWE 3.6.0 Rule CWE-398, CWE-569               */
/* JV-01 Justification : This is accepted, due to the module's object is exported for usage.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/



/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define LIN_PBCFG_C_AR_RELEASE_MAJOR_VERSION                                    4U
#define LIN_PBCFG_C_AR_RELEASE_MINOR_VERSION                                    8U
#define LIN_PBCFG_C_AR_RELEASE_REVISION_VERSION                                 0U

/* File version information */
#define LIN_PBCFG_C_SW_MAJOR_VERSION                                            2U
#define LIN_PBCFG_C_SW_MINOR_VERSION                                            4U

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/
/* Specification Major Version Check */
#if (LIN_PBTYPES_AR_RELEASE_MAJOR_VERSION != \
LIN_PBCFG_C_AR_RELEASE_MAJOR_VERSION)
#error "Lin_PBcfg.c : Mismatch in Release Major Version"
#endif

#if (LIN_PBTYPES_AR_RELEASE_MINOR_VERSION != \
LIN_PBCFG_C_AR_RELEASE_MINOR_VERSION)
#error "Lin_PBcfg.c : Mismatch in Release Minor Version"
#endif

#if (LIN_PBTYPES_AR_RELEASE_REVISION_VERSION != \
LIN_PBCFG_C_AR_RELEASE_REVISION_VERSION)
#error "Lin_PBcfg.c : Mismatch in Release Revision Version"
#endif

#if (LIN_PBTYPES_SW_MAJOR_VERSION != LIN_PBCFG_C_SW_MAJOR_VERSION)
#error "Lin_PBcfg.c : Mismatch in Software Major Version"
#endif

#if (LIN_PBTYPES_SW_MINOR_VERSION != LIN_PBCFG_C_SW_MINOR_VERSION)
#error "Lin_PBcfg.c : Mismatch in Software Minor Version"
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/
#define LIN_CORE0_START_SEC_VAR_INIT_BOOLEAN_LOCAL
#include "Lin_MemMap.h"

/* Global variable to store Initialization status of LIN Driver */
static volatile VAR(boolean, LIN_VAR_INIT) Lin_GblDriverState_Core0 = LIN_UNINIT;
#define LIN_CORE0_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define LIN_CORE1_START_SEC_VAR_INIT_BOOLEAN_LOCAL
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Global variable to store Initialization status of LIN Driver */
static volatile VAR(boolean, LIN_VAR_INIT) Lin_GblDriverState_Core1 = LIN_UNINIT;
#define LIN_CORE1_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define LIN_CORE0_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RAM allocation for all active Channels */
static volatile VAR(Lin_RamData, LIN_VAR_NO_INIT) Lin_GaaChannelRamData_Core0[3];
#define LIN_CORE0_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define LIN_CORE1_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RAM allocation for all active Channels */
static volatile VAR(Lin_RamData, LIN_VAR_NO_INIT) Lin_GaaChannelRamData_Core1[3];
#define LIN_CORE1_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define LIN_CORE0_START_SEC_VAR_NO_INIT_PTR_LOCAL
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Global pointer to hold first channel data structure */
static volatile P2CONST(Lin_ChannelInfo, LIN_VAR_NO_INIT, LIN_APPL_CONST) Lin_GpChannelConfig_Core0;
/* Global pointer to hold first RLin3 channel data structure address */
static volatile P2CONST(Lin3_ChannelConfigType, LIN_VAR_NO_INIT, LIN_APPL_CONST) Lin_GpRLIN3Properties_Core0;
#define LIN_CORE0_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define LIN_CORE1_START_SEC_VAR_NO_INIT_PTR_LOCAL
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Global pointer to hold first channel data structure */
static volatile P2CONST(Lin_ChannelInfo, LIN_VAR_NO_INIT, LIN_APPL_CONST) Lin_GpChannelConfig_Core1;
/* Global pointer to hold first RLin3 channel data structure address */
static volatile P2CONST(Lin3_ChannelConfigType, LIN_VAR_NO_INIT, LIN_APPL_CONST) Lin_GpRLIN3Properties_Core1;
#define LIN_CORE1_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define LIN_START_SEC_CONST_8
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Core Id to index table */
const uint8 Lin_GaaGetCoreId2Index[LIN_SUPPORTED_CORE_MAX_NUM] = {0x0U, 0x1U, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
/* Covert channel id to core index */
const uint8 Lin_GaaChannelId2CoreIndex[LIN_NO_OF_CHANNELS] = {0x0U, 0x1U, 0x0U, 0x0U, 0x1U, 0x1U};
#define LIN_STOP_SEC_CONST_8
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define LIN_START_SEC_CONST_32
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Common access point to each core data */
const Lin_GlobalAccessPointType Lin_GaaGlobalAccPoint[LIN_CONFIGURED_CORE_NUM] =
{
  {
    /* pDriverState */
    &Lin_GblDriverState_Core0,
    /* pChannelConfig */
    &Lin_GpChannelConfig_Core0,
    /* pRLIN3Properties */
    &Lin_GpRLIN3Properties_Core0,
    /* pChannelRamData */
    &Lin_GaaChannelRamData_Core0[0]
  },
  {
    /* pDriverState */
    &Lin_GblDriverState_Core1,
    /* pChannelConfig */
    &Lin_GpChannelConfig_Core1,
    /* pRLIN3Properties */
    &Lin_GpRLIN3Properties_Core1,
    /* pChannelRamData */
    &Lin_GaaChannelRamData_Core1[0]
  }
};
#define LIN_STOP_SEC_CONST_32
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define LIN_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* This array contains channel specific information for all active channels */
CONST(Lin_ChannelInfo, LIN_CONFIG_DATA) Lin_GaaChannelConfig[] =                                                        /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - LinChannel */
  {
    /* ucWakeupSourceId */
    EcuMConf_EcuMWakeupSource_EcuMWakeupSource,

    /* ucModReg */
    0x00U,

    /* blWakeupSupport */
    LIN_TRUE,

    /* ucRLINBreakfieldwidth */
    0x06U,

    /* ucRLINInterbytespace */
    0x22U,

    /* enNodeType */
    LIN_MASTER_NODE,

    /* ucChannelRamIndex */
    0x00U
  },
  /* Index: 1 - LinChannel_001 */
  {
    /* ucWakeupSourceId */
    EcuMConf_EcuMWakeupSource_EcuMWakeupSource,

    /* ucModReg */
    0x00U,

    /* blWakeupSupport */
    LIN_TRUE,

    /* ucRLINBreakfieldwidth */
    0x11U,

    /* ucRLINInterbytespace */
    0x11U,

    /* enNodeType */
    LIN_MASTER_NODE,

    /* ucChannelRamIndex */
    0x00U
  },
  /* Index: 2 - LinChannel_002 */
  {
    /* ucWakeupSourceId */
    EcuMConf_EcuMWakeupSource_EcuMWakeupSource,

    /* ucModReg */
    0x00U,

    /* blWakeupSupport */
    LIN_TRUE,

    /* ucRLINBreakfieldwidth */
    0x22U,

    /* ucRLINInterbytespace */
    0x22U,

    /* enNodeType */
    LIN_MASTER_NODE,

    /* ucChannelRamIndex */
    0x01U
  },
  /* Index: 3 - LinChannel_003 */
  {
    /* ucWakeupSourceId */
    EcuMConf_EcuMWakeupSource_EcuMWakeupSource,

    /* ucModReg */
    0x00U,

    /* blWakeupSupport */
    LIN_TRUE,

    /* ucRLINBreakfieldwidth */
    0x12U,

    /* ucRLINInterbytespace */
    0x33U,

    /* enNodeType */
    LIN_MASTER_NODE,

    /* ucChannelRamIndex */
    0x02U
  },
  /* Index: 4 - LinChannel_004 */
  {
    /* ucWakeupSourceId */
    EcuMConf_EcuMWakeupSource_EcuMWakeupSource,

    /* ucModReg */
    0x00U,

    /* blWakeupSupport */
    LIN_TRUE,

    /* ucRLINBreakfieldwidth */
    0x12U,

    /* ucRLINInterbytespace */
    0x33U,

    /* enNodeType */
    LIN_MASTER_NODE,

    /* ucChannelRamIndex */
    0x01U
  },
  /* Index: 5 - LinChannel_005 */
  {
    /* ucWakeupSourceId */
    EcuMConf_EcuMWakeupSource_EcuMWakeupSource,

    /* ucModReg */
    0x00U,

    /* blWakeupSupport */
    LIN_TRUE,

    /* ucRLINBreakfieldwidth */
    0x12U,

    /* ucRLINInterbytespace */
    0x32U,

    /* enNodeType */
    LIN_SLAVE_NODE,

    /* ucChannelRamIndex */
    0x02U
  }
};

/* This array contains RLIN3 channel specific information for all active channels */
CONST(Lin3_ChannelConfigType, LIN_CONFIG_DATA) Lin_GaaRLIN3Properties[] =                                               /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - LinChannel */
  {
    /* pLn3ChanlBaseAddress */
    (P2VAR(RLin3_UartRegs, TYPEDEF, REGSPACE)) 0xFFC7C001UL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ucBaudRate */
    0x0FU,

    /* ucBaudRate1 */
    0x00U,

    /* ucPrescalerClk_Select */
    0x01U,

    /* ucBitSamples */
    0x00U,

    /* blLinSpec_Select */
    LIN_FALSE,

    /* pLin3IntTxEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF804DAUL,                                                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pLin3IntRxEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF804DCUL,                                                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pLin3IntStEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF804DEUL                                                                     /* PRQA S 0306, 3432 # JV-01, JV-01 */
  },
  /* Index: 1 - LinChannel_001 */
  {
    /* pLn3ChanlBaseAddress */
    (P2VAR(RLin3_UartRegs, TYPEDEF, REGSPACE)) 0xFF89B101UL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ucBaudRate */
    0x0FU,

    /* ucBaudRate1 */
    0x00U,

    /* ucPrescalerClk_Select */
    0x01U,

    /* ucBitSamples */
    0x00U,

    /* blLinSpec_Select */
    LIN_TRUE,

    /* pLin3IntTxEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF804E4UL,                                                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pLin3IntRxEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF804E6UL,                                                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pLin3IntStEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF804E8UL                                                                     /* PRQA S 0306, 3432 # JV-01, JV-01 */
  },
  /* Index: 2 - LinChannel_002 */
  {
    /* pLn3ChanlBaseAddress */
    (P2VAR(RLin3_UartRegs, TYPEDEF, REGSPACE)) 0xFFC7C201UL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ucBaudRate */
    0x0FU,

    /* ucBaudRate1 */
    0x00U,

    /* ucPrescalerClk_Select */
    0x01U,

    /* ucBitSamples */
    0x00U,

    /* blLinSpec_Select */
    LIN_TRUE,

    /* pLin3IntTxEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF804EEUL,                                                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pLin3IntRxEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF804F0UL,                                                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pLin3IntStEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF804F2UL                                                                     /* PRQA S 0306, 3432 # JV-01, JV-01 */
  },
  /* Index: 3 - LinChannel_003 */
  {
    /* pLn3ChanlBaseAddress */
    (P2VAR(RLin3_UartRegs, TYPEDEF, REGSPACE)) 0xFF89B301UL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ucBaudRate */
    0x07U,

    /* ucBaudRate1 */
    0x00U,

    /* ucPrescalerClk_Select */
    0x01U,

    /* ucBitSamples */
    0x00U,

    /* blLinSpec_Select */
    LIN_TRUE,

    /* pLin3IntTxEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF804F8UL,                                                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pLin3IntRxEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF804FAUL,                                                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pLin3IntStEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF804FCUL                                                                     /* PRQA S 0306, 3432 # JV-01, JV-01 */
  },
  /* Index: 4 - LinChannel_004 */
  {
    /* pLn3ChanlBaseAddress */
    (P2VAR(RLin3_UartRegs, TYPEDEF, REGSPACE)) 0xFFC7C401UL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ucBaudRate */
    0x0FU,

    /* ucBaudRate1 */
    0x00U,

    /* ucPrescalerClk_Select */
    0x01U,

    /* ucBitSamples */
    0x00U,

    /* blLinSpec_Select */
    LIN_FALSE,

    /* pLin3IntTxEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF80502UL,                                                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pLin3IntRxEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF80504UL,                                                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pLin3IntStEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF80506UL                                                                     /* PRQA S 0306, 3432 # JV-01, JV-01 */
  },
  /* Index: 5 - LinChannel_005 */
  {
    /* pLn3ChanlBaseAddress */
    (P2VAR(RLin3_UartRegs, TYPEDEF, REGSPACE)) 0xFF89B501UL,                                                            /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ucBaudRate */
    0x0FU,

    /* ucBaudRate1 */
    0x00U,

    /* ucPrescalerClk_Select */
    0x01U,

    /* ucBitSamples */
    0x00U,

    /* blLinSpec_Select */
    LIN_FALSE,

    /* pLin3IntTxEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF8050AUL,                                                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pLin3IntRxEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF8050CUL,                                                                    /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pLin3IntStEicReg */
    (P2VAR(uint16, TYPEDEF, REGSPACE)) 0xFFF8050EUL                                                                     /* PRQA S 0306, 3432 # JV-01, JV-01 */
  }
};

/* This structure contains module specific parameters */
CONST(Lin_ConfigType, LIN_CONFIG_DATA) Lin_GaaConfiguration[] =                                                         /* PRQA S 1502 # JV-01 */
{
  /* Index: 0 - Lin_GaaConfiguration */
  {
    /* ulStartOfDbToc */
    0x0ED48220UL,

    /* pFirstChannel */
    &Lin_GaaChannelConfig[0],

    /* pRLIN3Properties */
    &Lin_GaaRLIN3Properties[0]
  }
};

#define LIN_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Lin_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

