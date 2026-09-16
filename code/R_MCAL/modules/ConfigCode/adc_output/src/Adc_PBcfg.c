/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_PBcfg.c                                                                                         */
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
/* TOOL VERSION:  AdcU2Bx-E.dll version: 2.5.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\adc\generator\U2B24-E\R2211_adc_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_adc.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_adc.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_adc.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:49:17
 */


/***********************************************************************************************************************
**                      Instance Index                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Adc.h"
#include "Adc_Ram.h"
#include "Adc_Cbk.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/**********************************************************************************************************************/
/* Message (2:0303)    : [I] Cast between a pointer to volatile object and an integral type.                          */
/* Rule                : MISRA C:2012 Rule-11.4,  CERT-C:1.2.4 CERTCCM INT36, CWE Rule CWE-398, CWE-569               */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : [I] Cast between a pointer to object and an integral type.                                   */
/* Rule                : MISRA-C:2012 Rule-11.4, CERT-C:1.2.4 CERTCCM INT36, CWE Rule CWE-398, CWE-569, CWE-738       */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0314)    : [I] Cast from a pointer to object type to a pointer to void.                                 */
/* Rule                : MISRA-C:2012 Dir-1.1, CWE-188, CWE-398, CWE-569                                              */
/* JV-01 Justification : Pointer to a void is a generic pointer type which can be use cast to any other pointer type. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0315)    : [I] Implicit conversion from a pointer to object type to a pointer to void.                  */
/* Rule                : MISRA-C:2012 Dir-1.1, CWE-188, CWE-398, CWE-569                                              */
/* JV-01 Justification : Pointer to a void is a generic pointer type which can be use cast to any other pointer type. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object 'name' is only referenced in the translation unit where it is defined.            */
/* Rule                : MISRA-C:2012 Rule-8.7, CERT-C:1.2.4 CERTCCM DCL15, DCL19, CWE-398, CWE-569                   */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other    */
/*                       C source files                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE-398, CWE-569                                                     */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
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
/* AUTOSAR release version information */
#define ADC_PBCFG_C_AR_RELEASE_MAJOR_VERSION                                    4U
#define ADC_PBCFG_C_AR_RELEASE_MINOR_VERSION                                    8U
#define ADC_PBCFG_C_AR_RELEASE_REVISION_VERSION                                 0U
/* File version information */
#define ADC_PBCFG_C_SW_MAJOR_VERSION                                            2U
#define ADC_PBCFG_C_SW_MINOR_VERSION                                            5U

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/
#if (ADC_ADCX_PBTYPES_AR_RELEASE_MAJOR_VERSION != ADC_PBCFG_C_AR_RELEASE_MAJOR_VERSION)
 #error "Adc_PBcfg.c : Mismatch in Release Major Version"
#endif

#if (ADC_ADCX_PBTYPES_AR_RELEASE_MINOR_VERSION != ADC_PBCFG_C_AR_RELEASE_MINOR_VERSION)
 #error "Adc_PBcfg.c : Mismatch in Release Minor Version"
#endif

#if (ADC_ADCX_PBTYPES_AR_RELEASE_REVISION_VERSION != ADC_PBCFG_C_AR_RELEASE_REVISION_VERSION)
 #error "Adc_PBcfg.c : Mismatch in Release Revision Version"
#endif

#if (ADC_ADCX_PBTYPES_SW_MAJOR_VERSION != ADC_PBCFG_C_SW_MAJOR_VERSION)
  #error "Adc_PBcfg.c : Mismatch in Software Major Version"
#endif

#if (ADC_ADCX_PBTYPES_SW_MINOR_VERSION != ADC_PBCFG_C_SW_MINOR_VERSION)
  #error "Adc_PBcfg.c : Mismatch in Software Minor Version"
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/

#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"

/* RAM Allocation of Channel group data */
volatile VAR(Adc_ChannelGroupRamData, ADC_VAR_NO_INIT) Adc_GaaGroupRamData[8];                                          /* PRQA S 1504 # JV-01 */
/* RAM Allocation of Scan group unit data */
volatile VAR(Adc_SgUnitRamData, ADC_VAR_NO_INIT) Adc_GaaSgUnitRamData[4];                                               /* PRQA S 1504 # JV-01 */
/* Structure for A/D Converter Trigger Output Selection Control Current Value */
STATIC volatile VAR(Adc_PicTriggSelectValueType, ADC_VAR_NO_INIT) Adc_GaaPicTriggSelectCurrent[ADC_NUM_SCANGROUP];

#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ADC_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* RAM Allocation to store channel enable or disable status */
volatile VAR(boolean, ADC_VAR_NO_INIT) Adc_GaaChannelToDisableEnable[32];                                               /* PRQA S 1504 # JV-01 */

#define ADC_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_PTR
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Structure for A/D Converter Trigger Output Selection Control Register Group */
STATIC CONST(Adc_PicTriggSelectRegGroupType, ADC_CONFIG_DATA) Adc_GaaPicTriggSelectReg[] =
{
  /* Index: 0 - */
  {
    /* Index: 0 - aaPicTriggSelectRegs */
    {
      /* PIC20ADTEN400 */
      (P2VAR(volatile Adc_PicTriggSelectRegsType, ADC_CONFIG_DATA, REGSPACE))0xFFBFC080UL,                              /* PRQA S 0303 # JV-01 */

      /* PIC20ADTEN410 */
      (P2VAR(volatile Adc_PicTriggSelectRegsType, ADC_CONFIG_DATA, REGSPACE))0xFFBFC0A0UL,                              /* PRQA S 0303 # JV-01 */

      /* PIC20ADTEN420 */
      (P2VAR(volatile Adc_PicTriggSelectRegsType, ADC_CONFIG_DATA, REGSPACE))0xFFBFC0C0UL,                              /* PRQA S 0303 # JV-01 */

      /* PIC21ADTEN400 */
      (P2VAR(volatile Adc_PicTriggSelectRegsType, ADC_CONFIG_DATA, REGSPACE))0xFFBFC880UL,                              /* PRQA S 0303 # JV-01 */

      /* PIC21ADTEN410 */
      (P2VAR(volatile Adc_PicTriggSelectRegsType, ADC_CONFIG_DATA, REGSPACE))0xFFBFC8A0UL                               /* PRQA S 0303 # JV-01 */
    }
  }
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_32
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Channel list */
CONST(uint32, ADC_CONFIG_DATA) Adc_GaaChannelToGroup[] =                                                                /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - Group Id 0 */
  0x00000004UL, 0x00000005UL, 0x00000007UL, 0x0000000DUL,
  /* Index: 4 - Group Id 1 */
  0x01000004UL, 0x01000005UL, 0x01000007UL, 0x0100000DUL,
  /* Index: 8 - Group Id 2 */
  0x01000004UL, 0x01000005UL, 0x01000007UL, 0x0100000DUL,
  /* Index: 12 - Group Id 3 */
  0x00000006UL, 0x00000007UL, 0x0000000CUL, 0x0000000FUL,
  /* Index: 16 - Group Id 4 */
  0x01000006UL, 0x01000007UL, 0x0100000CUL, 0x0100000FUL,
  /* Index: 20 - Group Id 5 */
  0x00000006UL, 0x00000007UL, 0x0000000CUL, 0x0000000FUL,
  /* Index: 24 - Group Id 6 */
  0x01000006UL, 0x01000007UL, 0x0100000CUL, 0x0100000FUL,
  /* Index: 28 - Group Id 7 */
  0x00000004UL, 0x00000005UL, 0x00000007UL, 0x0000000DUL
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_32
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_16
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Structure for wait time configuration */
CONST(Adc_WaitTimeConfigType, ADC_CONFIG_DATA) Adc_GaaWaitTimeConfig[] =                                                /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - ADC_HWUNIT_0 */
  {
    /* Index: 0 - usWAITTRy */
    {
      /* usWAITTR0 */
      0x0028U,

      /* usWAITTR1 */
      0x0000U,

      /* usWAITTR2 */
      0x0000U,

      /* usWAITTR3 */
      0x0000U,

      /* usWAITTR4 */
      0x0000U,

      /* usWAITTR5 */
      0x0000U,

      /* usWAITTR6 */
      0x0000U,

      /* usWAITTR7 */
      0x0000U
    }
  },
  /* Index: 1 - ADC_HWUNIT_1 */
  {
    /* Index: 0 - usWAITTRy */
    {
      /* usWAITTR0 */
      0x0028U,

      /* usWAITTR1 */
      0x0000U,

      /* usWAITTR2 */
      0x0000U,

      /* usWAITTR3 */
      0x0000U,

      /* usWAITTR4 */
      0x0000U,

      /* usWAITTR5 */
      0x0000U,

      /* usWAITTR6 */
      0x0000U,

      /* usWAITTR7 */
      0x0000U
    }
  }
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_16
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_8
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Hardware Index Mapping array */
CONST(uint8, ADC_CONFIG_DATA) Adc_GaaHwUnitIndex[] =                                                                    /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - ADC_HWUNIT_0 */
  0x00U,
  /* Index: 1 - ADC_HWUNIT_1 */
  0x01U
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_8
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Scan Group Index Mapping array */
CONST(uint8, ADC_CONFIG_DATA) Adc_GaaSgUnitIndex[] =                                                                    /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 */
  0xFFU,
  /* Index: 1 */
  0x00U,
  /* Index: 2 */
  0xFFU,
  /* Index: 3 */
  0xFFU,
  /* Index: 4 */
  0x01U,
  /* Index: 5 */
  0xFFU,
  /* Index: 6 */
  0x02U,
  /* Index: 7 */
  0xFFU,
  /* Index: 8 */
  0xFFU,
  /* Index: 9 */
  0x03U
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_8
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Mapping of DMA channel Id to the HW unit */
CONST(uint8, ADC_CONFIG_DATA) Adc_GaaHwUnit[] =                                                                         /* PRQA S 1504 # JV-01 */
{
  /* DMA Channel Id: 0 */
  0x00U,
  /* DMA Channel Id: 1 */
  0x00U,
  /* DMA Channel Id: 2 */
  0xFFU,
  /* DMA Channel Id: 3 */
  0xFFU,
  /* DMA Channel Id: 4 */
  0xFFU,
  /* DMA Channel Id: 5 */
  0x01U,
  /* DMA Channel Id: 6 */
  0x01U
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_8
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Mapping of DMA channel Id to the SGm unit */
CONST(uint8, ADC_CONFIG_DATA) Adc_GaaSGUnit[] =                                                                         /* PRQA S 1504 # JV-01 */
{
  /* DMA Channel Id: 0 */
  0x00U,
  /* DMA Channel Id: 1 */
  0x01U,
  /* DMA Channel Id: 2 */
  0xFFU,
  /* DMA Channel Id: 3 */
  0xFFU,
  /* DMA Channel Id: 4 */
  0xFFU,
  /* DMA Channel Id: 5 */
  0x02U,
  /* DMA Channel Id: 6 */
  0x03U
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Structure for A/D Converter n Trigger Control Register Value */
STATIC CONST(Adc_TriggConfigType, ADC_CONFIG_DATA) Adc_GaaTriggConfig[] =
{
  /* Index: 0 - AdcConfigSet_000 - AdcHwUnit_00 - AdcGroup_003 */
  {
    /* Index: 0 - aaTriggSelect */
    {
      /* PIC20ADCX0TSEL1 */
      0x00000001UL,

      /* PIC21ADCX0TSEL1 */
      0x00000000UL
    },
    /* usTriggEdge */
    0x0000U
  }
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Structure for A/D Converter Trigger Output Selection Control Register Value */
STATIC CONST(Adc_PicTriggSelectValueType, ADC_CONFIG_DATA) Adc_GaaPicTriggSelectValue[] =
{
  /* Index: 0 - AdcConfigSet_000 - AdcHwUnit_00 - AdcGroup_003 */
  {
    /* Index: 0 - aaPicTriggSelectValue */
    {
      /* PIC20ADTEN401 */
      0x0100U,

      /* PIC20ADTEN411 */
      0x0000U,

      /* PIC20ADTEN421 */
      0x0000U,

      /* PIC21ADTEN401 */
      0x0000U,

      /* PIC21ADTEN411 */
      0x0000U
    },
    /* ucPicTriggSelectUsed */
    0x01U
  }
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Structure for HW trigger configuration */
STATIC CONST(Adc_HwTriggConfigType, ADC_CONFIG_DATA) Adc_GaaHwTriggConfig[] =
{
  /* Index: 0 - */
  {
    /* pTriggConfig */
    &Adc_GaaTriggConfig[0],

    /* pPicTriggControlValue */
    NULL_PTR,

    /* pPicTriggSelectReg */
    &Adc_GaaPicTriggSelectReg[0],

    /* pPicTriggSelectValue */
    &Adc_GaaPicTriggSelectValue[0],

    /* pPicTriggSelectCurrent */
    &Adc_GaaPicTriggSelectCurrent[0],

    /* pPicTriggConfigReg */
    NULL_PTR,

    /* pPicTriggConfigValue */
    NULL_PTR,

    /* ulPicTriggConfigUsed */
    0x00000000UL
  }
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Structure for HW Unit configuration */
CONST(Adc_HwUnitConfigType, ADC_CONFIG_DATA) Adc_GaaHWUnitConfig[] =                                                    /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - AdcConfigSet_000 - AdcHwUnit_00 */
  {
    /* pErrorNotificationPointer */
    NULL_PTR,

    /* pErrorNotificationPointerSG */
    NULL_PTR,

    /* pHwUnitBaseAddress */
    (P2VAR(Adc_ConfigRegisters, ADC_CONFIG_DATA, REGSPACE))0xFFCA0000UL,                                                /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pEicRegAddress */
    (P2VAR(uint16, ADC_CONFIG_DATA, REGSPACE))0xFFF80372UL,                                                             /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pErrEicRegAddress */
    (P2VAR(uint32, ADC_CONFIG_DATA, REGSPACE))0xFFF8039AUL,                                                             /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* Index: 5 - aaPicTriggReg */
    {
      /* PIC20ADCX0TSEL0 */
      (P2VAR(volatile Adc_PicTriggRegType, ADC_CONFIG_DATA, REGSPACE))0xFFBFC000UL,                                     /* PRQA S 0303 # JV-01 */

      /* PIC21ADCX0TSEL0 */
      (P2VAR(volatile Adc_PicTriggRegType, ADC_CONFIG_DATA, REGSPACE))0xFFBFC800UL                                      /* PRQA S 0303 # JV-01 */
    },
    /* pPicTriggControlRegs */
    NULL_PTR,

    /* pTnHChSelectReg */
    NULL_PTR,

    /* ucSgUnitOffset */
    0x00U,

    /* ucSgUnitCount */
    0x02U,

    /* blInterruptErr */
    ADC_TRUE,

    /* ucWaitTimeIndex */
    0x00U,

    /* ucMaxVirtualChannel */
    0x08U
  },
  /* Index: 1 - AdcConfigSet_000 - AdcHwUnit_01 */
  {
    /* pErrorNotificationPointer */
    NULL_PTR,

    /* pErrorNotificationPointerSG */
    NULL_PTR,

    /* pHwUnitBaseAddress */
    (P2VAR(Adc_ConfigRegisters, ADC_CONFIG_DATA, REGSPACE))0xFFF20000UL,                                                /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pEicRegAddress */
    (P2VAR(uint16, ADC_CONFIG_DATA, REGSPACE))0xFFF80386UL,                                                             /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pErrEicRegAddress */
    (P2VAR(uint32, ADC_CONFIG_DATA, REGSPACE))0xFFF8039EUL,                                                             /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* Index: 5 - aaPicTriggReg */
    {
      /* Reserved */
      NULL_PTR,

      /* Reserved */
      NULL_PTR
    },
    /* pPicTriggControlRegs */
    NULL_PTR,

    /* pTnHChSelectReg */
    NULL_PTR,

    /* ucSgUnitOffset */
    0x02U,

    /* ucSgUnitCount */
    0x02U,

    /* blInterruptErr */
    ADC_TRUE,

    /* ucWaitTimeIndex */
    0x01U,

    /* ucMaxVirtualChannel */
    0x08U
  }
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Structure for SG Unit configuration */
CONST(Adc_HwSgUnitType, ADC_CONFIG_DATA) Adc_GaaSgUnitConfig[] =                                                        /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - AdcConfigSet_000 - AdcHwUnit_00 - AdcHwScanGroup_000 */
  {
    /* enFunctionalityModeType */
    ADC_INTERRUPT_MODE,

    /* ucSgUnitId */
    0x01U,

    /* ucDmaChannelIndex */
    0x00U,

    /* ulVcrProcessWait */
    0x00000014UL,

    /* ulDmaSourceAddress */
    0xFFCA0280UL
  },
  /* Index: 1 - AdcConfigSet_000 - AdcHwUnit_00 - AdcHwScanGroup_001 */
  {
    /* enFunctionalityModeType */
    ADC_POLLING_MODE,

    /* ucSgUnitId */
    0x04U,

    /* ucDmaChannelIndex */
    0x01U,

    /* ulVcrProcessWait */
    0x00000022UL,

    /* ulDmaSourceAddress */
    0xFFCA0290UL
  },
  /* Index: 2 - AdcConfigSet_000 - AdcHwUnit_01 - AdcHwScanGroup_000 */
  {
    /* enFunctionalityModeType */
    ADC_INTERRUPT_MODE,

    /* ucSgUnitId */
    0x01U,

    /* ucDmaChannelIndex */
    0x02U,

    /* ulVcrProcessWait */
    0x00000014UL,

    /* ulDmaSourceAddress */
    0xFFF20280UL
  },
  /* Index: 3 - AdcConfigSet_000 - AdcHwUnit_01 - AdcHwScanGroup_001 */
  {
    /* enFunctionalityModeType */
    ADC_POLLING_MODE,

    /* ucSgUnitId */
    0x04U,

    /* ucDmaChannelIndex */
    0x03U,

    /* ulVcrProcessWait */
    0x00000022UL,

    /* ulDmaSourceAddress */
    0xFFF20290UL
  }
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Structure for Group configuration */
CONST(Adc_GroupConfigType, ADC_CONFIG_DATA) Adc_GaaGroupConfig[] =                                                      /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - AdcConfigSet_000 - AdcHwUnit_00 - AdcGroup_000 */
  {
    /* pGroupNotificationPointer */
    NULL_PTR,

    /* enAdcSelfDiagMode */
    ADC_SELF_DIAG_OFF,

    /* ulAdcTimerPeriod */
    0x00000000UL,

    /* ulAdcTimerPhaseDelay */
    0x00000000UL,

    /* ucStartVirChPtr */
    0x00U,

    /* ddNumberofSamples */
    0x01U,

    /* ucHwUnitIndex */
    0x00U,

    /* ucSgUnitIndex */
    0x00U,

    /* ucChannelToGroupIndex */
    0x00U,

    /* ucScanMode */
    0x00U,

    /* blEnableDmaTransfer */
    ADC_FALSE,

    /* enGroupAccessMode */
    ADC_ACCESS_MODE_SINGLE,

    /* enStreamBufferMode */
    ADC_STREAM_BUFFER_LINEAR,

    /* enGroupConvMode */
    ADC_CONV_MODE_ONESHOT,

    /* blImplicitlyStopped */
    ADC_TRUE,

    /* ucChannelCount */
    0x04U,

    /* blAdcEnableAdTimerTriggMode */
    ADC_FALSE,

    /* ucTriggConfigIndex */
    0xFFU,

    /* ucPicTriggControlIndex */
    0xFFU,

    /* ucPicTriggSelectIndex */
    0xFFU
  },
  /* Index: 1 - AdcConfigSet_000 - AdcHwUnit_00 - AdcGroup_001 */
  {
    /* pGroupNotificationPointer */
    NULL_PTR,

    /* enAdcSelfDiagMode */
    ADC_SELF_DIAG_OFF,

    /* ulAdcTimerPeriod */
    0x00000000UL,

    /* ulAdcTimerPhaseDelay */
    0x00000000UL,

    /* ucStartVirChPtr */
    0x04U,

    /* ddNumberofSamples */
    0x04U,

    /* ucHwUnitIndex */
    0x00U,

    /* ucSgUnitIndex */
    0x01U,

    /* ucChannelToGroupIndex */
    0x04U,

    /* ucScanMode */
    0x00U,

    /* blEnableDmaTransfer */
    ADC_FALSE,

    /* enGroupAccessMode */
    ADC_ACCESS_MODE_STREAMING,

    /* enStreamBufferMode */
    ADC_STREAM_BUFFER_LINEAR,

    /* enGroupConvMode */
    ADC_CONV_MODE_CONTINUOUS,

    /* blImplicitlyStopped */
    ADC_TRUE,

    /* ucChannelCount */
    0x04U,

    /* blAdcEnableAdTimerTriggMode */
    ADC_FALSE,

    /* ucTriggConfigIndex */
    0xFFU,

    /* ucPicTriggControlIndex */
    0xFFU,

    /* ucPicTriggSelectIndex */
    0xFFU
  },
  /* Index: 2 - AdcConfigSet_000 - AdcHwUnit_00 - AdcGroup_002 */
  {
    /* pGroupNotificationPointer */
    NULL_PTR,

    /* enAdcSelfDiagMode */
    ADC_SELF_DIAG_OFF,

    /* ulAdcTimerPeriod */
    0x00000000UL,

    /* ulAdcTimerPhaseDelay */
    0x00000000UL,

    /* ucStartVirChPtr */
    0x04U,

    /* ddNumberofSamples */
    0x01U,

    /* ucHwUnitIndex */
    0x00U,

    /* ucSgUnitIndex */
    0x01U,

    /* ucChannelToGroupIndex */
    0x08U,

    /* ucScanMode */
    0x20U,

    /* blEnableDmaTransfer */
    ADC_TRUE,

    /* enGroupAccessMode */
    ADC_ACCESS_MODE_SINGLE,

    /* enStreamBufferMode */
    ADC_STREAM_BUFFER_LINEAR,

    /* enGroupConvMode */
    ADC_CONV_MODE_CONTINUOUS,

    /* blImplicitlyStopped */
    ADC_FALSE,

    /* ucChannelCount */
    0x04U,

    /* blAdcEnableAdTimerTriggMode */
    ADC_FALSE,

    /* ucTriggConfigIndex */
    0xFFU,

    /* ucPicTriggControlIndex */
    0xFFU,

    /* ucPicTriggSelectIndex */
    0xFFU
  },
  /* Index: 3 - AdcConfigSet_000 - AdcHwUnit_01 - AdcGroup_100 */
  {
    /* pGroupNotificationPointer */
    NULL_PTR,

    /* enAdcSelfDiagMode */
    ADC_SELF_DIAG_OFF,

    /* ulAdcTimerPeriod */
    0x00000000UL,

    /* ulAdcTimerPhaseDelay */
    0x00000000UL,

    /* ucStartVirChPtr */
    0x00U,

    /* ddNumberofSamples */
    0x01U,

    /* ucHwUnitIndex */
    0x01U,

    /* ucSgUnitIndex */
    0x02U,

    /* ucChannelToGroupIndex */
    0x0CU,

    /* ucScanMode */
    0x00U,

    /* blEnableDmaTransfer */
    ADC_FALSE,

    /* enGroupAccessMode */
    ADC_ACCESS_MODE_SINGLE,

    /* enStreamBufferMode */
    ADC_STREAM_BUFFER_LINEAR,

    /* enGroupConvMode */
    ADC_CONV_MODE_ONESHOT,

    /* blImplicitlyStopped */
    ADC_TRUE,

    /* ucChannelCount */
    0x04U,

    /* blAdcEnableAdTimerTriggMode */
    ADC_FALSE,

    /* ucTriggConfigIndex */
    0xFFU,

    /* ucPicTriggControlIndex */
    0xFFU,

    /* ucPicTriggSelectIndex */
    0xFFU
  },
  /* Index: 4 - AdcConfigSet_000 - AdcHwUnit_01 - AdcGroup_101 */
  {
    /* pGroupNotificationPointer */
    NULL_PTR,

    /* enAdcSelfDiagMode */
    ADC_SELF_DIAG_OFF,

    /* ulAdcTimerPeriod */
    0x00000000UL,

    /* ulAdcTimerPhaseDelay */
    0x00000000UL,

    /* ucStartVirChPtr */
    0x04U,

    /* ddNumberofSamples */
    0x04U,

    /* ucHwUnitIndex */
    0x01U,

    /* ucSgUnitIndex */
    0x03U,

    /* ucChannelToGroupIndex */
    0x10U,

    /* ucScanMode */
    0x00U,

    /* blEnableDmaTransfer */
    ADC_FALSE,

    /* enGroupAccessMode */
    ADC_ACCESS_MODE_STREAMING,

    /* enStreamBufferMode */
    ADC_STREAM_BUFFER_LINEAR,

    /* enGroupConvMode */
    ADC_CONV_MODE_CONTINUOUS,

    /* blImplicitlyStopped */
    ADC_TRUE,

    /* ucChannelCount */
    0x04U,

    /* blAdcEnableAdTimerTriggMode */
    ADC_FALSE,

    /* ucTriggConfigIndex */
    0xFFU,

    /* ucPicTriggControlIndex */
    0xFFU,

    /* ucPicTriggSelectIndex */
    0xFFU
  },
  /* Index: 5 - AdcConfigSet_000 - AdcHwUnit_01 - AdcGroup_102 */
  {
    /* pGroupNotificationPointer */
    NULL_PTR,

    /* enAdcSelfDiagMode */
    ADC_SELF_DIAG_OFF,

    /* ulAdcTimerPeriod */
    0x00000000UL,

    /* ulAdcTimerPhaseDelay */
    0x00000000UL,

    /* ucStartVirChPtr */
    0x00U,

    /* ddNumberofSamples */
    0x01U,

    /* ucHwUnitIndex */
    0x01U,

    /* ucSgUnitIndex */
    0x02U,

    /* ucChannelToGroupIndex */
    0x14U,

    /* ucScanMode */
    0x20U,

    /* blEnableDmaTransfer */
    ADC_TRUE,

    /* enGroupAccessMode */
    ADC_ACCESS_MODE_SINGLE,

    /* enStreamBufferMode */
    ADC_STREAM_BUFFER_LINEAR,

    /* enGroupConvMode */
    ADC_CONV_MODE_CONTINUOUS,

    /* blImplicitlyStopped */
    ADC_FALSE,

    /* ucChannelCount */
    0x04U,

    /* blAdcEnableAdTimerTriggMode */
    ADC_FALSE,

    /* ucTriggConfigIndex */
    0xFFU,

    /* ucPicTriggControlIndex */
    0xFFU,

    /* ucPicTriggSelectIndex */
    0xFFU
  },
  /* Index: 6 - AdcConfigSet_000 - AdcHwUnit_01 - AdcGroup_103 */
  {
    /* pGroupNotificationPointer */
    NULL_PTR,

    /* enAdcSelfDiagMode */
    ADC_SELF_DIAG_OFF,

    /* ulAdcTimerPeriod */
    0x00000000UL,

    /* ulAdcTimerPhaseDelay */
    0x00000000UL,

    /* ucStartVirChPtr */
    0x04U,

    /* ddNumberofSamples */
    0x01U,

    /* ucHwUnitIndex */
    0x01U,

    /* ucSgUnitIndex */
    0x03U,

    /* ucChannelToGroupIndex */
    0x18U,

    /* ucScanMode */
    0x00U,

    /* blEnableDmaTransfer */
    ADC_TRUE,

    /* enGroupAccessMode */
    ADC_ACCESS_MODE_SINGLE,

    /* enStreamBufferMode */
    ADC_STREAM_BUFFER_LINEAR,

    /* enGroupConvMode */
    ADC_CONV_MODE_ONESHOT,

    /* blImplicitlyStopped */
    ADC_TRUE,

    /* ucChannelCount */
    0x04U,

    /* blAdcEnableAdTimerTriggMode */
    ADC_FALSE,

    /* ucTriggConfigIndex */
    0xFFU,

    /* ucPicTriggControlIndex */
    0xFFU,

    /* ucPicTriggSelectIndex */
    0xFFU
  },
  /* Index: 7 - AdcConfigSet_000 - AdcHwUnit_00 - AdcGroup_003 */
  {
    /* pGroupNotificationPointer */
    NULL_PTR,

    /* enAdcSelfDiagMode */
    ADC_SELF_DIAG_OFF,

    /* ulAdcTimerPeriod */
    0x00000000UL,

    /* ulAdcTimerPhaseDelay */
    0x00000000UL,

    /* ucStartVirChPtr */
    0x00U,

    /* ddNumberofSamples */
    0x01U,

    /* ucHwUnitIndex */
    0x00U,

    /* ucSgUnitIndex */
    0x00U,

    /* ucChannelToGroupIndex */
    0x1CU,

    /* ucScanMode */
    0x00U,

    /* blEnableDmaTransfer */
    ADC_TRUE,

    /* enGroupAccessMode */
    ADC_ACCESS_MODE_SINGLE,

    /* enStreamBufferMode */
    ADC_STREAM_BUFFER_LINEAR,

    /* enGroupConvMode */
    ADC_CONV_MODE_ONESHOT,

    /* blImplicitlyStopped */
    ADC_FALSE,

    /* ucChannelCount */
    0x04U,

    /* blAdcEnableAdTimerTriggMode */
    ADC_FALSE,

    /* ucTriggConfigIndex */
    0x00U,

    /* ucPicTriggControlIndex */
    0xFFU,

    /* ucPicTriggSelectIndex */
    0x00U
  }
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Structure for DMA channel configuration for SGm unit */
CONST(Adc_DmaConfigType, ADC_CONFIG_DATA) Adc_GaaDmaUnitConfig[] =                                                      /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - AdcConfigSet_000 - AdcHwUnit_00 - AdcHwScanGroup_000 */
  {
    /* pDmaRegBaseaddress */
    (P2VAR(Adc_DmaRegisters, ADC_CONFIG_DATA, REGSPACE))0xFFF92000UL,                                                   /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pDmaEicRegaddress */
    (P2VAR(uint16, ADC_CONFIG_DATA, REGSPACE))0xFFF8008CUL,                                                             /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pDmaDescriptoraddress */
    (P2VAR(Adc_DmaDescSetType, ADC_CONFIG_DATA, REGSPACE))0xFFF94000UL,                                                 /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ulDmaResourceValue */
    0x00000005UL,

    /* usDmaDescriptorPointer */
    0x0000U,

    /* pDMACSEL */
    (P2VAR(uint32, ADC_CONFIG_DATA, REGSPACE))0xFF090400UL,                                                             /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ucDmaUnit */
    0x00U,

    /* ucDmaRequestGroup */
    0x02U
  },
  /* Index: 1 - AdcConfigSet_000 - AdcHwUnit_00 - AdcHwScanGroup_001 */
  {
    /* pDmaRegBaseaddress */
    (P2VAR(Adc_DmaRegisters, ADC_CONFIG_DATA, REGSPACE))0xFFF92080UL,                                                   /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pDmaEicRegaddress */
    (P2VAR(uint16, ADC_CONFIG_DATA, REGSPACE))0xFFF8008EUL,                                                             /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pDmaDescriptoraddress */
    (P2VAR(Adc_DmaDescSetType, ADC_CONFIG_DATA, REGSPACE))0xFFF94020UL,                                                 /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ulDmaResourceValue */
    0x00000008UL,

    /* usDmaDescriptorPointer */
    0x0020U,

    /* pDMACSEL */
    (P2VAR(uint32, ADC_CONFIG_DATA, REGSPACE))0xFF090400UL,                                                             /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ucDmaUnit */
    0x00U,

    /* ucDmaRequestGroup */
    0x02U
  },
  /* Index: 2 - AdcConfigSet_000 - AdcHwUnit_01 - AdcHwScanGroup_000 */
  {
    /* pDmaRegBaseaddress */
    (P2VAR(Adc_DmaRegisters, ADC_CONFIG_DATA, REGSPACE))0xFFF92280UL,                                                   /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pDmaEicRegaddress */
    (P2VAR(uint16, ADC_CONFIG_DATA, REGSPACE))0xFFF80096UL,                                                             /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pDmaDescriptoraddress */
    (P2VAR(Adc_DmaDescSetType, ADC_CONFIG_DATA, REGSPACE))0xFFF94040UL,                                                 /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ulDmaResourceValue */
    0x0000000FUL,

    /* usDmaDescriptorPointer */
    0x0040U,

    /* pDMACSEL */
    (P2VAR(uint32, ADC_CONFIG_DATA, REGSPACE))0xFF090400UL,                                                             /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ucDmaUnit */
    0x00U,

    /* ucDmaRequestGroup */
    0x02U
  },
  /* Index: 3 - AdcConfigSet_000 - AdcHwUnit_01 - AdcHwScanGroup_001 */
  {
    /* pDmaRegBaseaddress */
    (P2VAR(Adc_DmaRegisters, ADC_CONFIG_DATA, REGSPACE))0xFFF92300UL,                                                   /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pDmaEicRegaddress */
    (P2VAR(uint16, ADC_CONFIG_DATA, REGSPACE))0xFFF80098UL,                                                             /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* pDmaDescriptoraddress */
    (P2VAR(Adc_DmaDescSetType, ADC_CONFIG_DATA, REGSPACE))0xFFF94060UL,                                                 /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ulDmaResourceValue */
    0x00000012UL,

    /* usDmaDescriptorPointer */
    0x0060U,

    /* pDMACSEL */
    (P2VAR(uint32, ADC_CONFIG_DATA, REGSPACE))0xFF090404UL,                                                             /* PRQA S 0306, 3432 # JV-01, JV-01 */

    /* ucDmaUnit */
    0x00U,

    /* ucDmaRequestGroup */
    0x02U
  }
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* RAM Initialization of ADC Channel Configuration */
CONST(Adc_ConfigType, ADC_CONFIG_DATA) Adc_GaaConfiguration[] =                                                         /* PRQA S 1502 # JV-01 */
{
  /* Index: 0 - AdcConfigSet_000 */
  {
    /* ulStartOfDbToc */
    0x0EDEC228UL,

    /* pHWUnitConfig */
    &Adc_GaaHWUnitConfig[0],                                                                                            /* PRQA S 0315 # JV-01 */

    /* pSgUnitConfig */
    &Adc_GaaSgUnitConfig[0],                                                                                            /* PRQA S 0315 # JV-01 */

    /* pGroupConfig */
    &Adc_GaaGroupConfig[0],                                                                                             /* PRQA S 0315 # JV-01 */

    /* pHwTriggConfig */
    (P2CONST(void, ADC_CONFIG_DATA, ADC_CONFIG_DATA))&Adc_GaaHwTriggConfig[0],                                          /* PRQA S 0314 # JV-01 */

    /* pDmaUnitConfig */
    &Adc_GaaDmaUnitConfig[0],                                                                                           /* PRQA S 0315 # JV-01 */

    /* pDmaHWUnitMapping */
    &Adc_GaaHwUnit[0],                                                                                                  /* PRQA S 0315 # JV-01 */

    /* pDmaSGUnitMapping */
    &Adc_GaaSGUnit[0],                                                                                                  /* PRQA S 0315 # JV-01 */

    /* pChannelToGroup */
    &Adc_GaaChannelToGroup[0],                                                                                          /* PRQA S 0315 # JV-01 */

    /* pHwUnitIndex */
    &Adc_GaaHwUnitIndex[0],                                                                                             /* PRQA S 0315 # JV-01 */

    /* pSgUnitIndex */
    &Adc_GaaSgUnitIndex[0],                                                                                             /* PRQA S 0315 # JV-01 */

    /* pGroupRamData */
    &Adc_GaaGroupRamData[0],                                                                                            /* PRQA S 0315 # JV-01 */

    /* pSgUnitRamData */
    &Adc_GaaSgUnitRamData[0],                                                                                           /* PRQA S 0315 # JV-01 */

    /* pChannelToDisableEnable */
    &Adc_GaaChannelToDisableEnable[0],                                                                                  /* PRQA S 0315 # JV-01 */

    /* pWaittimeConfig */
    &Adc_GaaWaitTimeConfig[0],                                                                                          /* PRQA S 0315 # JV-01 */

    /* pTnHChannelSelectValue */
    NULL_PTR,

    /* ucMaxSwTriggGroups */
    0x07U,

    /* ucNoOfGroups */
    0x08U,

    /* ucMaxDmaChannels */
    0x04U,

    /* ucNoOfChannels */
    0x20U,

    /* ucCoreIndex */
    0x00U
  }
};

#define ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */



/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

