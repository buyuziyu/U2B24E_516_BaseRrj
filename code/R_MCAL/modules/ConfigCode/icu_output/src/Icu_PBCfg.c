/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_PBCfg.c                                                                                         */
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
/* TOOL VERSION:  IcuU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\icu\generator\U2B24-E\R2211_icu_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_icu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuM\xml\EcuM_icu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_icu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_icu.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:49:38
 */


/***********************************************************************************************************************
**                      Instance Index                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Icu_PBTypes.h"
#include "Icu_Externals.h"
#include "Icu_GTM_Ram.h"



/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/**********************************************************************************************************************/
/* Message (2:0303)    : [I] Cast between a pointer to volatile object and an integral type.                          */
/* Rule                : MISRA-C:2012 Rule-11.4, CERTCMM INT36, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : [I] Cast between a pointer to object and an integral type.                                   */
/* Rule                : MISRA-C:2012 Rule-11.4, CERTCMM INT36, CWE Rule CWE-398, CWE-569, CWE-738                    */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0326)    : [I] Cast between a pointer to void and an integral type.                                     */
/* Rule                : MISRA C:2012 Rule-11.6, CERTCCM EXP36, INT36, CWE Rule CWE-398, CWE-569, CWE-738             */
/* JV-01 Justification : Using void due to specific requirment of input parameter. So, this can be skipped            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0777)    : External identifier does not differ from other identifier(s) (e.g. '%s') within the          */
/*                       specified number of significant characters.                                                  */
/* Rule                : MISRA C:2012 Rule-5.1, CERTCCM DCL23, MSC15, CWE Rule CWE-682, CWE-758                       */
/* JV-01 Justification : Compiler will distinguish numerous characters, so this is accepted.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message(1:1502)     : The object '%1s' is defined but is not used within this project.                             */
/* Rule                : MISRA C:2012 Rule-2.8, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : This is accepted since there is no problem with the software behavior.                       */
/*                       This variable is intended for user use, so it will not be used within the module scope       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object 'name' is only referenced in the translation unit where it is defined.            */
/* Rule                : MISRA-C:2012 Rule-8.7, CERTCCM DCL15, DCL19, CWE Rule CWE-398, CWE-569                       */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other    */
/*                       C source files                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1533)    : The object 'entity' is only referenced by function 'func'.                                   */
/* Rule                : MISRA C:2012 Rule-8.9, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : This is accepted, due to the object is defined in seperated cource C file to followed        */
/*                       coding rule                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : '%s' has external linkage and is being defined without any previous declaration.             */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : #include statements in a file should only be preceded by other preprocessor                  */
/*                       directives or comments.                                                                      */
/* Rule                : MISRA-C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping ).      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:4304)    : An expression of 'essentially Boolean' type (%1s) is being cast to unsigned type '%2s'.      */
/* Rule                : MISRA C:2012 Rule-10.5, CWE Rule CWE-704                                                     */
/* JV-01 Justification : This is accepted. This casting from boolean to unsigned type for values 0 and 1 does not     */
/*                       make data conflict.                                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_PBCFG_C_AR_RELEASE_MAJOR_VERSION                                    4U
#define ICU_PBCFG_C_AR_RELEASE_MINOR_VERSION                                    8U
#define ICU_PBCFG_C_AR_RELEASE_REVISION_VERSION                                 0U

/* File version information */
#define ICU_PBCFG_C_SW_MAJOR_VERSION                                            2U
#define ICU_PBCFG_C_SW_MINOR_VERSION                                            4U

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/

#if (ICU_PBTYPES_AR_RELEASE_MAJOR_VERSION != ICU_PBCFG_C_AR_RELEASE_MAJOR_VERSION)
#error "Icu_PBCfg.c : Mismatch in Release Major Version"
#endif

#if (ICU_PBTYPES_AR_RELEASE_MINOR_VERSION != ICU_PBCFG_C_AR_RELEASE_MINOR_VERSION)
#error "Icu_PBCfg.c : Mismatch in Release Minor Version"
#endif

#if (ICU_PBTYPES_AR_RELEASE_REVISION_VERSION != ICU_PBCFG_C_AR_RELEASE_REVISION_VERSION)
#error "Icu_PBCfg.c : Mismatch in Release Revision Version"
#endif

#if (ICU_PBTYPES_SW_MAJOR_VERSION != ICU_PBCFG_C_SW_MAJOR_VERSION)
#error "Icu_PBCfg.c : Mismatch in Software Major Version"
#endif

#if (ICU_PBTYPES_SW_MINOR_VERSION != ICU_PBCFG_C_SW_MINOR_VERSION)
#error "Icu_PBCfg.c : Mismatch in Software Minor Version"
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/

#define ICU_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Icu_MemMap.h"

/* RAM Allocation of Channel data */
volatile VAR(Icu_ChannelRamDataType, ICU_VAR_NO_INIT) Icu_GaaChannelRamData[1];                                         /* PRQA S 1504, 3408 # JV-01, JV-01 */

/* RAM Allocation of Signal Measure Channel data */
/* volatile VAR(Icu_SignalMeasurementModeRamDataType, ICU_VAR_NO_INIT) Icu_GaaSignalMeasureRamData[]; */

/* RAM Allocation of Timestamp channel data */
/* volatile VAR(Icu_TimeStampChannelRamDataType, ICU_VAR_NO_INIT) Icu_GaaTimestampRamData[]; */

/* RAM Allocation of Edge Counting Channel data */
/* volatile VAR(Icu_EdgeCountModeRamDatatype, ICU_VAR_NO_INIT) Icu_GaaEdgeCountRamData[]; */

#define ICU_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ICU_START_SEC_VAR_INIT_PTR
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Function pointer table for all HW IP */
P2CONST(Icu_HwFuncTableType, ICU_VAR_INIT, ICU_CONFIG_DATA) Icu_GaaHwDepFunc[] =                                        /* PRQA S 3408 # JV-01 */
{
  /* IRQ */
  NULL_PTR,
  /* INTP */
  NULL_PTR,
  /* TAUD */
  NULL_PTR,
  /* TAUJ */
  NULL_PTR,
  /* ATU6A */
  NULL_PTR,
  /* ATU6C */
  NULL_PTR,
  /* TIM */
  &Icu_GtmFunc
};
#define ICU_STOP_SEC_VAR_INIT_PTR
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ICU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Array of structures for Hardware TAU Configuration */

/* Array of structures for Hardware Configuration */

/* Configuration for Hardware IP */
CONST(Icu_HWIPType, ICU_CONFIG_DATA) Icu_GaaHWIPConfig[] =
{
  /* Index: 0 - TIM */
  {
    /* ucIndex */
    ICU_HW_GTM_TIM
  }
};

/* Array of structures for Hardware PIN Configuration */

/* Configuration for TAU Channel configuration */

/* Configuration of each ICU Channel */
CONST(Icu_ChannelConfigType, ICU_CONFIG_DATA) Icu_GaaChannelConfig[] =                                                  /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* Index: 0 - IcuChannel_TIM00 */
  {
    /* pCntlRegs */
    (P2VAR(void, TYPEDEF, REGSPACE))0xFF600800UL,                                                                       /* PRQA S 0326 # JV-01 */

    /* pPPRAddress */
    (P2VAR(volatile uint16, TYPEDEF, REGSPACE))0xFFD9000CUL,                                                            /* PRQA S 0303 # JV-01 */

    /* pIntrCntlAddress */
    NULL_PTR,

    /* usChannelMaskValue */
    0x0001U,

    /* usPortMaskValue */
    0x0001U,

    /* ucIcuPortType */
    ICU_NORMAL_PORT,

    /* ucIcuMeasurementMode */
    (uint8)ICU_MODE_SIGNAL_EDGE_DETECT,

    /* ucIcuDefaultStartEdge */
    (uint8)ICU_RISING_EDGE,

    /* ucIcuChannelType */
    (uint8)ICU_HW_GTM_TIM,

    /* ucIcuWakeupCapability */
    (uint8)ICU_FALSE,                                                                                                   /* PRQA S 4304 # JV-01 */

    /* ucIcuDisableEcumWakeupNotification */
    (uint8)ICU_TRUE,                                                                                                    /* PRQA S 4304 # JV-01 */

    /* pHWIPChannelConfig */
    NULL_PTR
  }
};

/* GTM GTM TIM channel configured data */
CONST(Icu_GtmChannelConfigType, ICU_CONFIG_DATA) Icu_GaaGTMChannelUserRegConfig[] =                                     /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* Index: 0 - IcuChannel_TIM00 */
  {
    /* ulCtrlRegsChannelSettings */
    0x00002004UL,

    /* pGTM_IRQ_SELij */
    (P2VAR(volatile uint32, TYPEDEF, REGSPACE))0xFFF5803CUL,                                                            /* PRQA S 0303 # JV-01 */

    /* ulGTM_IRQ_SELijEnableValue */
    0x00000001UL
  }
};

/* Configuration of each ICU Channel */
CONST(Icu_ChannelUserRegConfigType, ICU_CONFIG_DATA) Icu_GaaChannelUserRegConfig[] =                                    /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* Index: 0 - IcuChannel_TIM00 */
  {
    /* ucRamDataIndex */
    0x00U,

    /* ucChannelProperties */
    0x00U,

    /* pHWChannelUserRegConfig */
    &Icu_GaaGTMChannelUserRegConfig[0]
  }
};

/* GTM TBU unit configured data */
CONST(Icu_GtmTbuUnitConfigType, ICU_CONFIG_DATA) Icu_GaaTBUUnitConfig[] =                                               /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* Index: 0 - IcuConfigSet */
  {
    /* pTBUCHENRegs */
    (P2VAR(volatile uint32, TYPEDEF, REGSPACE))0xFF600100UL,                                                            /* PRQA S 0303 # JV-01 */

    /* ulTBUCHENValue */
    0x00000002UL,

    /* pTBU0CTRLRegs */
    (P2VAR(volatile uint32, TYPEDEF, REGSPACE))0xFF600104UL,                                                            /* PRQA S 0303 # JV-01 */

    /* ulTBU0CTRLValue */
    0x00000000UL
  }
};

/* Structure for each Config Set */
CONST(Icu_ConfigType, ICU_CONFIG_DATA) Icu_GaaConfiguration[] =                                                         /* PRQA S 1502 # JV-01 */
{
  /* Index: 0 - IcuConfigSet */
  {
    /* ulStartOfDbToc */
    0x0EDE8220UL,

    /* pChannelConfig */
    (P2CONST(void, TYPEDEF, ICU_CONFIG_CONST)) &Icu_GaaChannelConfig[0],

    /* pChannelUserRegConfig */
    (P2CONST(void, TYPEDEF, ICU_CONFIG_CONST)) &Icu_GaaChannelUserRegConfig[0],

    /* pRamAddress */
    (P2VAR(volatile void, TYPEDEF, ICU_CONFIG_CONST)) &Icu_GaaChannelRamData[0],

    /* pGtmTbuUnitConfig */
    &Icu_GaaTBUUnitConfig[0]
  }
};

#define ICU_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

