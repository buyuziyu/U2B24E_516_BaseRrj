/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Can_PBcfg.c                                                                                         */
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
/* CAN Post Build configuration header */
#include "Can.h"
#include "Can_PBTypes.h"
#include "Can_LTTypes.h"
#include "Can_Externals.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/* Message (2:0315)    : Implicit conversion from a pointer to object type to a pointer to void.                      */
/*                       REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics                                         */
/* Rule                : MISRA C:2012 Dir1.1, CWE Rule CWE-188, CWE-398, CWE-569                                      */
/* JV-01 Justification : Void pointer is used in order to typecast to different channel structures later.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : #include directives should only be preceded by preprocessor directives or comments           */
/* Rule                : MISRA C:2012 Rule 20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0857)    : Number of macro definitions exceeds 1024 - program does not conform strictly to ISO:C90.     */
/* Rule                : MISRA C:2012 Dir-1.1                                                                         */
/* JV-01 Justification : The number of macro depend on module code size. There is no issue when number of macro is    */
/*                       over 1024                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object '%1s' is only referenced in the translation unit where it is defined.             */
/* Rule                : MISRA C:2012 Rule 8.7, CERTCCM DCL15, DCL19                                                  */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : '%s' has external linkage and is being defined without any previous declaration.             */
/* Rule                : MISRA C:2012 Rule 8.4, CERTCCM DCL07                                                         */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0791)    : [U] Macro identifier does not differ from other macro identifier(s) (e.g. '%s') within the   */
/*                       specified number of significant characters.                                                  */
/*                       REFERENCE - ISO:C90-6.1.2 Identifiers - Implementation Limits                                */
/* Rule                : MISRA C:2012 Rule 5.4, CERTCCM DCL23                                                         */
/* JV-01 Justification : This macro identifier is following AUTOSAR standard rule (Symbolic Name or Published Macro's */
/*                       name), so this is accepted.                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0613)    : [L] Size of object '%1s' exceeds 65535 bytes - program does not conform strictly to ISO:C99. */
/* Rule                : MISRA C:2012 Dir-1.1-C99                                                                     */
/* JV-01 Justification : This object define a section memory which is adequate for hardware and application usages    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0303)    : [I] Cast between a pointer to volatile object and an integral type.                          */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569                             */
/*                       REFERENCE - ISO-6.3.4 Semantics                                                              */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
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
#define CAN_PBCFG_C_AR_RELEASE_MAJOR_VERSION                                    4U
#define CAN_PBCFG_C_AR_RELEASE_MINOR_VERSION                                    8U
#define CAN_PBCFG_C_AR_RELEASE_REVISION_VERSION                                 0U
#define CAN_PBCFG_C_SW_MAJOR_VERSION                                            2U
#define CAN_PBCFG_C_SW_MINOR_VERSION                                            4U

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/
#if (CAN_PBTYPES_AR_RELEASE_MAJOR_VERSION != CAN_PBCFG_C_AR_RELEASE_MAJOR_VERSION)
 #error "Can_PBcfg.c : Mismatch in Release Major Version"
#endif

#if (CAN_PBTYPES_AR_RELEASE_MINOR_VERSION != CAN_PBCFG_C_AR_RELEASE_MINOR_VERSION)
 #error "Can_PBcfg.c : Mismatch in Release Minor Version"
#endif

#if (CAN_PBTYPES_AR_RELEASE_REVISION_VERSION != CAN_PBCFG_C_AR_RELEASE_REVISION_VERSION)
 #error "Can_PBcfg.c : Mismatch in Release Revision Version"
#endif

#if (CAN_PBTYPES_SW_MAJOR_VERSION != CAN_PBCFG_C_SW_MAJOR_VERSION)
  #error "Can_PBcfg.c : Mismatch in Software Major Version"
#endif

#if (CAN_PBTYPES_SW_MINOR_VERSION != CAN_PBCFG_C_SW_MINOR_VERSION)
  #error "Can_PBcfg.c : Mismatch in Software Minor Version"
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/
#define CAN_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Can_MemMap.h"                                                                                                

static CONST(uint32, CAN_CONFIG_DATA) Can_GaaGAFLCFGConfig00[] =
{
  /* Index 0 */
  0x00010000UL,

  /* Index 1 */
  0x00000000UL,

  /* Index 2 */
  0x00000000UL,

  /* Index 3 */
  0x00000000UL
};
static CONST(uint32, CAN_CONFIG_DATA) Can_GaaGAFLCFGConfig01[] =
{
  /* Index 0 */
  0x00000000UL,

  /* Index 1 */
  0x00000000UL,

  /* Index 2 */
  0x00000000UL,

  /* Index 3 */
  0x00000000UL
};
static CONST(uint32, CAN_CONFIG_DATA) Can_GaaGAFLCFGConfig02[] =
{
  /* Index 0 */
  0x00010000UL,

  /* Index 1 */
  0x00000000UL
};
static CONST(uint32, CAN_CONFIG_DATA) Can_GaaTMIEConfig00[] =
{
  /* Index 0 */
  0x00000000UL,

  /* Index 1 */
  0x00000000UL,

  /* Index 2 */
  0x00000000UL,

  /* Index 3 */
  0x00000000UL,

  /* Index 4 */
  0x00000000UL,

  /* Index 5 */
  0x00000000UL,

  /* Index 6 */
  0x00000000UL,

  /* Index 7 */
  0x00000000UL,

  /* Index 8 */
  0x00000000UL,

  /* Index 9 */
  0x00000000UL,

  /* Index 10 */
  0x00000000UL,

  /* Index 11 */
  0x00000000UL,

  /* Index 12 */
  0x00000000UL,

  /* Index 13 */
  0x00000000UL,

  /* Index 14 */
  0x00000000UL,

  /* Index 15 */
  0x00000000UL
};
static CONST(uint32, CAN_CONFIG_DATA) Can_GaaTMIEConfig01[] =
{
  /* Index 0 */
  0x00000000UL,

  /* Index 1 */
  0x00000000UL,

  /* Index 2 */
  0x00000000UL,

  /* Index 3 */
  0x00000000UL,

  /* Index 4 */
  0x00000000UL,

  /* Index 5 */
  0x00000000UL,

  /* Index 6 */
  0x00000000UL,

  /* Index 7 */
  0x00000000UL,

  /* Index 8 */
  0x00000000UL,

  /* Index 9 */
  0x00000000UL,

  /* Index 10 */
  0x00000000UL,

  /* Index 11 */
  0x00000000UL,

  /* Index 12 */
  0x00000000UL,

  /* Index 13 */
  0x00000000UL,

  /* Index 14 */
  0x00000000UL,

  /* Index 15 */
  0x00000000UL
};
static CONST(uint32, CAN_CONFIG_DATA) Can_GaaTMIEConfig02[] =
{
  /* Index 0 */
  0x00000001UL,

  /* Index 1 */
  0x00000000UL,

  /* Index 2 */
  0x00000000UL,

  /* Index 3 */
  0x00000000UL,

  /* Index 4 */
  0x00000000UL,

  /* Index 5 */
  0x00000000UL,

  /* Index 6 */
  0x00000000UL,

  /* Index 7 */
  0x00000000UL
};
#define CAN_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define CAN_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Can_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Array for Baudrate Configuration */
STATIC CONST(Can_BaudrateConfigType, CAN_CONFIG_DATA) Can_GaaBaudrateConfig00[] =
{
  /* Index: 0 - CanControllerBaudrateConfig0 */
  {
    /* usBaudrateConfigID */
    0x0000U,

    /* ulCFG */
    CAN_RSCAN_NSJW(1) | CAN_RSCAN_NTSEG1(13) | CAN_RSCAN_NTSEG2(6) | CAN_RSCAN_NBRP(15),

    /* ulDCFG */
    CAN_RSCAN_SJW(1) | CAN_RSCAN_TSEG1(6) | CAN_RSCAN_TSEG2(3) | CAN_RSCAN_BRP(15),

    /* ulFDCFG */
    0UL,

    /* blBRS */
    CAN_TRUE,

    /* blFdConfigured */
    CAN_TRUE
  },
  /* Index: 1 - CanControllerBaudrateConfig1 */
  {
    /* usBaudrateConfigID */
    0x0001U,

    /* ulCFG */
    CAN_RSCAN_NSJW(1) | CAN_RSCAN_NTSEG1(13) | CAN_RSCAN_NTSEG2(6) | CAN_RSCAN_NBRP(7),

    /* ulDCFG */
    CAN_RSCAN_SJW(1) | CAN_RSCAN_TSEG1(13) | CAN_RSCAN_TSEG2(6) | CAN_RSCAN_BRP(7),

    /* ulFDCFG */
    0UL,

    /* blBRS */
    CAN_FALSE,

    /* blFdConfigured */
    CAN_FALSE
  }
};

STATIC CONST(Can_BaudrateConfigType, CAN_CONFIG_DATA) Can_GaaBaudrateConfig01[] =
{
  /* Index: 0 - CanControllerBaudrateConfig0 */
  {
    /* usBaudrateConfigID */
    0x0000U,

    /* ulCFG */
    CAN_RSCAN_NSJW(1) | CAN_RSCAN_NTSEG1(13) | CAN_RSCAN_NTSEG2(6) | CAN_RSCAN_NBRP(15),

    /* ulDCFG */
    CAN_RSCAN_SJW(1) | CAN_RSCAN_TSEG1(6) | CAN_RSCAN_TSEG2(3) | CAN_RSCAN_BRP(15),

    /* ulFDCFG */
    0UL,

    /* blBRS */
    CAN_TRUE,

    /* blFdConfigured */
    CAN_TRUE
  },
  /* Index: 1 - CanControllerBaudrateConfig1 */
  {
    /* usBaudrateConfigID */
    0x0001U,

    /* ulCFG */
    CAN_RSCAN_NSJW(1) | CAN_RSCAN_NTSEG1(13) | CAN_RSCAN_NTSEG2(6) | CAN_RSCAN_NBRP(7),

    /* ulDCFG */
    CAN_RSCAN_SJW(1) | CAN_RSCAN_TSEG1(13) | CAN_RSCAN_TSEG2(6) | CAN_RSCAN_BRP(7),

    /* ulFDCFG */
    0UL,

    /* blBRS */
    CAN_FALSE,

    /* blFdConfigured */
    CAN_FALSE
  }
};

/* Array for Controller Configuration (Post-build time) */
STATIC CONST(Can_ControllerPBConfigType, CAN_CONFIG_DATA) Can_GaaControllerPBConfig0[] =
{
  /* Index: 0 - CanController0 */
  {
    /* ucMainFunctionWIndex */
    0U,

    /* usNoOfBaudrate */
    0x0002U,

    /* ucCoreId */
    0x00U,

    /* pBaudrateConfig */
    &Can_GaaBaudrateConfig00[0]
  },
  /* Index: 1 - CanController1 */
  {
    /* ucMainFunctionWIndex */
    0U,

    /* usNoOfBaudrate */
    0x0002U,

    /* ucCoreId */
    0x01U,

    /* pBaudrateConfig */
    &Can_GaaBaudrateConfig01[0]
  }
};

/* Array for Hardware Object Handle */
STATIC CONST(Can_HohConfigType, CAN_CONFIG_DATA) Can_GaaHohConfig0[] =
{
  /* Index: 0 - CanHardwareObject0 -> RXBUFFER[0] */
  {
    /* enHoh */
    CAN_HOH_HRH,

    /* ucMainFunctionRIndex */
    0U,

    /* ucController */
    0x00U,

    /* ucTMDLC */
    0x00U,

    /* usHohId */
    0x0000U,

    /* enBufferType */
    CAN_BUFFERTYPE_BUFFER,

    /* usBufferIndex */
    0x0000U,

    /* ucPaddingValue */
    0x00U,

    /* ulXXCCRegValue */
    0UL,

    /* ulXXCCERegValue */
    0UL,

    /* blObjectUsesPolling */
    CAN_TRUE
  },
  /* Index: 1 - CanHardwareObject1 -> TXRXBUFFER(RX)[0] */
  {
    /* enHoh */
    CAN_HOH_HRH,

    /* ucMainFunctionRIndex */
    0U,

    /* ucController */
    0x01U,

    /* ucTMDLC */
    0x00U,

    /* usHohId */
    0x0001U,

    /* enBufferType */
    CAN_BUFFERTYPE_TXRXFIFO,

    /* usBufferIndex */
    0x0000U,

    /* ucPaddingValue */
    0x00U,

    /* ulXXCCRegValue */
    CAN_RSCAN_CFM_RX | CAN_RSCAN_CFIM | CAN_RSCAN_CFRXIE | CAN_RSCAN_CFDC_4 | CAN_RSCAN_CFPLS_8,

    /* ulXXCCERegValue */
    0UL,

    /* blObjectUsesPolling */
    CAN_FALSE
  },
  /* Index: 2 - CanHardwareObject2 -> TXBUFFER[0] */
  {
    /* enHoh */
    CAN_HOH_HTH,

    /* ucMainFunctionRIndex */
    0U,

    /* ucController */
    0x00U,

    /* ucTMDLC */
    0x40U,

    /* usHohId */
    0x0002U,

    /* enBufferType */
    CAN_BUFFERTYPE_BUFFER,

    /* usBufferIndex */
    0x0000U,

    /* ucPaddingValue */
    0x00U,

    /* ulXXCCRegValue */
    0UL,

    /* ulXXCCERegValue */
    0UL,

    /* blObjectUsesPolling */
    CAN_FALSE
  },
  /* Index: 3 - CanHardwareObject3 -> TXBUFFER[0] */
  {
    /* enHoh */
    CAN_HOH_HTH,

    /* ucMainFunctionRIndex */
    0U,

    /* ucController */
    0x01U,

    /* ucTMDLC */
    0x40U,

    /* usHohId */
    0x0003U,

    /* enBufferType */
    CAN_BUFFERTYPE_BUFFER,

    /* usBufferIndex */
    0x0000U,

    /* ucPaddingValue */
    0x00U,

    /* ulXXCCRegValue */
    0UL,

    /* ulXXCCERegValue */
    0UL,

    /* blObjectUsesPolling */
    CAN_FALSE
  }
};

/* Array for Acceptance Filter Receive Rule Configuration */
STATIC CONST(Can_FilterType, CAN_CONFIG_DATA) Can_GaaFilterConfig0[] =
{
  /* Index: 0 - CanHardwareObject0/CanHwFilter: RSCANFD00 -> RXBUFFER[0] */
  {
    /* ulGAFLID */
    0x00000101UL,

    /* ulGAFLM */
    0xC00007FFUL,

    /* aaGAFLP */
    { CAN_RSCAN_GAFLRMV | CAN_RSCAN_GAFLRMDP(0) | CAN_RSCAN_GAFLDLC_0, 0UL }
  },
  /* Index: 1 - CanHardwareObject1/CanHwFilter: RSCANFD20 -> TXRXFIFO[0] */
  {
    /* ulGAFLID */
    0x00000068UL,

    /* ulGAFLM */
    0xC00007FFUL,

    /* aaGAFLP */
    { CAN_RSCAN_GAFLDLC_0, CAN_RSCAN_GAFLFDP_TXRXFIFO(0) }
  }
};

/* Array for Can Hardware Configuration Table */
STATIC CONST(Can_HWUnitInfoType, CAN_CONFIG_DATA) Can_GaaHWUnitInfo0[] =
{
  /* Index: 0 - Registers for RSCAN unit 0 */
  {
    /* ucNoOfTMIEC */
    0x10U,

    /* ucNoOfGAFLCFG */
    0x04U,

    /* usNoOfFilters */
    0x0001U,

    /* ulRMNB */
    0x00000000UL,

    /* ulGCFG */
    CAN_RSCAN_ITRCP(8) | CAN_RSCAN_DCE,

    /* pGAFLCFG */
    &Can_GaaGAFLCFGConfig00[0],

    /* pTMIEC */
    &Can_GaaTMIEConfig00[0],

    /* pFilterConfig */
    &Can_GaaFilterConfig0[0]
  },
  /* Index: 1 - Registers for RSCAN unit 1 */
  {
    /* ucNoOfTMIEC */
    0x10U,

    /* ucNoOfGAFLCFG */
    0x04U,

    /* usNoOfFilters */
    0x0000U,

    /* ulRMNB */
    0x00000000UL,

    /* ulGCFG */
    CAN_RSCAN_ITRCP(8) | CAN_RSCAN_DCE,

    /* pGAFLCFG */
    &Can_GaaGAFLCFGConfig01[0],

    /* pTMIEC */
    &Can_GaaTMIEConfig01[0],

    /* pFilterConfig */
    &Can_GaaFilterConfig0[1]
  },
  /* Index: 2 - Registers for RSCAN unit 2 */
  {
    /* ucNoOfTMIEC */
    0x08U,

    /* ucNoOfGAFLCFG */
    0x02U,

    /* usNoOfFilters */
    0x0001U,

    /* ulRMNB */
    0x00000000UL,

    /* ulGCFG */
    CAN_RSCAN_ITRCP(8) | CAN_RSCAN_DCE,

    /* pGAFLCFG */
    &Can_GaaGAFLCFGConfig02[0],

    /* pTMIEC */
    &Can_GaaTMIEConfig02[0],

    /* pFilterConfig */
    &Can_GaaFilterConfig0[1]
  }
};

/* Array Index of HRH ID */
STATIC CONST(uint16, CAN_CONFIG_DATA) Can_GusHrhIndex2Id[] =
{
  /* Index 0 - COMFIFO type - CanHardwareObject1 */
  0x0001U,
  /* Index 1 - BUFFER type - CanHardwareObject0 */
  0x0000U
};

/* Global array for Config Structure */
CONST(Can_ConfigType, CAN_CONFIG_DATA) Can_GaaConfig[] =                                                                /* PRQA S 1502 # JV-01 */
{
  /* Index: 0 - CanConfigSet0 */
  {
    /* ulStartOfDbToc */
    0x0ED40220UL,

    /* ucNoOfUnits */
    0x03U,

    /* ucNoOfControllers */
    0x02U,

    /* usNoOfHohs */
    0x0004U,

    /* pHWUnitInfo */
    &Can_GaaHWUnitInfo0[0],

    /* pControllerPCConfig */
    &Can_GaaControllerPCConfig0[0],

    /* pControllerPBConfig */
    &Can_GaaControllerPBConfig0[0],

    /* pHohConfig */
    &Can_GaaHohConfig0[0],

    /* pPhysicalControllerToIndex */
    &Can_GaaPhysicalControllerToIndex0[0],

    /* Can_GusHrhIndex2Id */
    &Can_GusHrhIndex2Id[0],

    /* pLpduCalloutReceiveFunction */
    NULL_PTR,

    /* ucTotalHrhRxFIFO */
    0x00U,

    /* ucTotalHrhComFIFO0 */
    0x00U,

    /* ucTotalHrhComFIFO1 */
    0x00U,

    /* ucTotalHrhComFIFO */
    0x01U,

    /* ucTotalHrhBuffer0 */
    0x02U,

    /* ucTotalHrhBuffer1 */
    0x02U,

    /* ucTotalHrhBuffer */
    0x02U
  }
};

#define CAN_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
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

