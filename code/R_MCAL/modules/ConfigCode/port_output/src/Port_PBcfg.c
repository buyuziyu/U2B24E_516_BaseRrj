/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Port_PBcfg.c                                                                                        */
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
/* TOOL VERSION:  PortU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                       */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\port\generator\U2B24-E\R2211_port_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_port.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_port.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_port.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:49:57
 */


/***********************************************************************************************************************
**                      Instance Index                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Port.h"

#include "Port_PBTypes.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/* Message (2:3408)    : Has external linkage and is being defined without any previous declaration.                  */
/* Rule                : MISRA C:2012 Rule 8.4, CERT-C:1.2.4 CERTCCM DCL07, CWE Rule CWE-398, CWE-569                 */
/* JV-01 Justification : Since number or names of symbols in this file is according to a configuration,               */
/*                       this can't be declared in a header file statically.                                          */
/*       Verification  : This symbol is referred by an auto-generated file only. It is verified by the evaluation     */
/*                       of the Generation Tool.                                                                      */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object 'name' is only referenced in the translation unit where it is defined.            */
/* Rule                : MISRA C:2012 Rule 8.7, CERT-C:1.2.4 CERTCCM DCL15, CWE Rule CWE-398, CWE-569                 */
/* JV-01 Justification : This is accepted since there is no problem with the software behavior.                       */
/*                       It is retained for future usage.                                                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : #include directives should only be preceded by preprocessor directives or comments           */
/* Rule                : MISRA C:2012 Rule 20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
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
#define PORT_PBCFG_C_AR_RELEASE_MAJOR_VERSION                                   4U
#define PORT_PBCFG_C_AR_RELEASE_MINOR_VERSION                                   8U
#define PORT_PBCFG_C_AR_RELEASE_REVISION_VERSION                                0U
#define PORT_PBCFG_C_SW_MAJOR_VERSION                                           2U
#define PORT_PBCFG_C_SW_MINOR_VERSION                                           4U

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/
#if (PORT_PBTYPES_AR_RELEASE_MAJOR_VERSION != PORT_PBCFG_C_AR_RELEASE_MAJOR_VERSION)
  #error "Port_PBcfg.c : Mismatch in Release Major Version"
#endif

#if (PORT_PBTYPES_AR_RELEASE_MINOR_VERSION != PORT_PBCFG_C_AR_RELEASE_MINOR_VERSION)
  #error "Port_PBcfg.c : Mismatch in Release Minor Version"
#endif

#if (PORT_PBTYPES_AR_RELEASE_REVISION_VERSION != PORT_PBCFG_C_AR_RELEASE_REVISION_VERSION)
  #error "Port_PBcfg.c : Mismatch in Release Revision Version"
#endif

#if (PORT_PBTYPES_SW_MAJOR_VERSION != PORT_PBCFG_C_SW_MAJOR_VERSION)
  #error "Port_PBcfg.c : Mismatch in Software Major Version"
#endif

#if (PORT_PBTYPES_SW_MINOR_VERSION != PORT_PBCFG_C_SW_MINOR_VERSION)
  #error "Port_PBcfg.c : Mismatch in Software Minor Version"
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/
#define PORT_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Port_MemMap.h"                                                                                               


/* Array of structures of port pin configration */
CONST(Port_Pin_Config, PORT_CONFIG_DATA) Port_GaaPinConfig[] =                                                          /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* Index: 0 - PortConfigSet_0_PortGroup0_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x013BU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 1 - PortConfigSet_0_PortGroup0_PortPin1 */
  {
    /* usChangeable */
    0x0005U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0xBFFFU,

    /* usModeDirIn */
    0x27FFU,

    /* usModeDirOut */
    0xBFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 2 - PortConfigSet_0_PortGroup0_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x03F3U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 3 - PortConfigSet_0_PortGroup0_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x83FFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 4 - PortConfigSet_0_PortGroup0_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x7FFFU,

    /* usModeDirIn */
    0x1309U,

    /* usModeDirOut */
    0x7FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 5 - PortConfigSet_0_PortGroup0_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x0679U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 6 - PortConfigSet_0_PortGroup0_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x7FFFU,

    /* usModeDirIn */
    0x40F9U,

    /* usModeDirOut */
    0x7FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 7 - PortConfigSet_0_PortGroup0_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x7FFFU,

    /* usModeDirIn */
    0x409DU,

    /* usModeDirOut */
    0x7FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 8 - PortConfigSet_0_PortGroup0_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x08F7U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 9 - PortConfigSet_0_PortGroup0_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x3FFFU,

    /* usModeDirIn */
    0x2619U,

    /* usModeDirOut */
    0x3FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 10 - PortConfigSet_0_PortGroup0_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x5FFFU,

    /* usModeDirIn */
    0x05C9U,

    /* usModeDirOut */
    0x5BFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 11 - PortConfigSet_0_PortGroup0_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0FFFU,

    /* usModeDirIn */
    0x0999U,

    /* usModeDirOut */
    0x0FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 12 - PortConfigSet_0_PortGroup0_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x07FFU,

    /* usModeDirIn */
    0x044BU,

    /* usModeDirOut */
    0x07FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 13 - PortConfigSet_0_PortGroup0_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x09FFU,

    /* usModeDirIn */
    0x086CU,

    /* usModeDirOut */
    0x01FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 14 - PortConfigSet_0_PortGroup0_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0BFFU,

    /* usModeDirIn */
    0x08CCU,

    /* usModeDirOut */
    0x03FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 15 - PortConfigSet_0_PortGroup0_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0BFFU,

    /* usModeDirIn */
    0x011DU,

    /* usModeDirOut */
    0x0AFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 16 - PortConfigSet_0_PortGroup1_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x07FFU,

    /* usModeDirIn */
    0x07FBU,

    /* usModeDirOut */
    0x05FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 17 - PortConfigSet_0_PortGroup1_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x17FFU,

    /* usModeDirIn */
    0x023DU,

    /* usModeDirOut */
    0x17FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 18 - PortConfigSet_0_PortGroup1_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x33FFU,

    /* usModeDirIn */
    0x0007U,

    /* usModeDirOut */
    0x33FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 19 - PortConfigSet_0_PortGroup1_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x4FFFU,

    /* usModeDirIn */
    0x4C7DU,

    /* usModeDirOut */
    0x0FFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 20 - PortConfigSet_0_PortGroup1_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x7FFFU,

    /* usModeDirIn */
    0x7FFFU,

    /* usModeDirOut */
    0x37FFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 21 - PortConfigSet_0_PortGroup1_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x33FFU,

    /* usModeDirIn */
    0x1339U,

    /* usModeDirOut */
    0x33FFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 22 - PortConfigSet_0_PortGroup1_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x33FFU,

    /* usModeDirIn */
    0x02DCU,

    /* usModeDirOut */
    0x33FFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 23 - PortConfigSet_0_PortGroup1_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x02FFU,

    /* usModeDirIn */
    0x02DCU,

    /* usModeDirOut */
    0x02FFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 24 - PortConfigSet_0_PortGroup1_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x3FFFU,

    /* usModeDirIn */
    0x001FU,

    /* usModeDirOut */
    0x3FFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 25 - PortConfigSet_0_PortGroup1_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x011BU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 26 - PortConfigSet_0_PortGroup1_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x07FFU,

    /* usModeDirIn */
    0x0199U,

    /* usModeDirOut */
    0x07FFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 27 - PortConfigSet_0_PortGroup1_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0FFFU,

    /* usModeDirIn */
    0x0E9BU,

    /* usModeDirOut */
    0x01FFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 28 - PortConfigSet_0_PortGroup2_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x03FFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 29 - PortConfigSet_0_PortGroup2_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x85FFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 30 - PortConfigSet_0_PortGroup2_PortPin2 */
  {
    /* usChangeable */
    0x0005U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x00FBU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 31 - PortConfigSet_0_PortGroup2_PortPin3 */
  {
    /* usChangeable */
    0x0002U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0xDFFFU,

    /* usModeDirIn */
    0x1FFFU,

    /* usModeDirOut */
    0xDFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 32 - PortConfigSet_0_PortGroup2_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0xBFFFU,

    /* usModeDirIn */
    0x90FFU,

    /* usModeDirOut */
    0xBFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 33 - PortConfigSet_0_PortGroup2_PortPin5 */
  {
    /* usChangeable */
    0x0001U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x7FFFU,

    /* usModeDirIn */
    0x5FFFU,

    /* usModeDirOut */
    0x7FFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 34 - PortConfigSet_0_PortGroup2_PortPin6 */
  {
    /* usChangeable */
    0x0005U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xDFF1U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 35 - PortConfigSet_0_PortGroup2_PortPin7 */
  {
    /* usChangeable */
    0x0001U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xBFF9U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 36 - PortConfigSet_0_PortGroup2_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x03F7U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 37 - PortConfigSet_0_PortGroup2_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x16FFU,

    /* usModeDirIn */
    0x020FU,

    /* usModeDirOut */
    0x16FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 38 - PortConfigSet_0_PortGroup2_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x1EFFU,

    /* usModeDirIn */
    0x020FU,

    /* usModeDirOut */
    0x1EFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 39 - PortConfigSet_0_PortGroup2_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x017FU,

    /* usModeDirIn */
    0x007FU,

    /* usModeDirOut */
    0x017FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 40 - PortConfigSet_0_PortGroup2_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x7FFFU,

    /* usModeDirIn */
    0x1128U,

    /* usModeDirOut */
    0x7FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 41 - PortConfigSet_0_PortGroup3_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0003U,

    /* usModeDirIn */
    0x0003U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 42 - PortConfigSet_0_PortGroup3_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0003U,

    /* usModeDirIn */
    0x0003U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 43 - PortConfigSet_0_PortGroup3_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0003U,

    /* usModeDirIn */
    0x0003U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 44 - PortConfigSet_0_PortGroup10_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0xAFFFU,

    /* usModeDirIn */
    0xA07EU,

    /* usModeDirOut */
    0x8FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 45 - PortConfigSet_0_PortGroup10_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0xAFFFU,

    /* usModeDirIn */
    0xA7FFU,

    /* usModeDirOut */
    0xABFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 46 - PortConfigSet_0_PortGroup10_PortPin2 */
  {
    /* usChangeable */
    0x0005U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xBFFFU,

    /* usModeDirOut */
    0xE7FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 47 - PortConfigSet_0_PortGroup10_PortPin3 */
  {
    /* usChangeable */
    0x0002U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0xBFFFU,

    /* usModeDirIn */
    0x86D3U,

    /* usModeDirOut */
    0xBFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 48 - PortConfigSet_0_PortGroup10_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x67F7U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 49 - PortConfigSet_0_PortGroup10_PortPin5 */
  {
    /* usChangeable */
    0x0001U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x887FU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 50 - PortConfigSet_0_PortGroup10_PortPin6 */
  {
    /* usChangeable */
    0x0005U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xDEF4U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 51 - PortConfigSet_0_PortGroup10_PortPin7 */
  {
    /* usChangeable */
    0x0001U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x0E38U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 52 - PortConfigSet_0_PortGroup10_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0xBFFFU,

    /* usModeDirIn */
    0xB7FFU,

    /* usModeDirOut */
    0xAFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 53 - PortConfigSet_0_PortGroup10_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x02BFU,

    /* usModeDirIn */
    0x029FU,

    /* usModeDirOut */
    0x023FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 54 - PortConfigSet_0_PortGroup10_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x06BFU,

    /* usModeDirIn */
    0x020FU,

    /* usModeDirOut */
    0x06BFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 55 - PortConfigSet_0_PortGroup10_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x073FU,

    /* usModeDirIn */
    0x020FU,

    /* usModeDirOut */
    0x073FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 56 - PortConfigSet_0_PortGroup10_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0401U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0400U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 57 - PortConfigSet_0_PortGroup10_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x073FU,

    /* usModeDirIn */
    0x060FU,

    /* usModeDirOut */
    0x073FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 58 - PortConfigSet_0_PortGroup10_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x037FU,

    /* usModeDirIn */
    0x024BU,

    /* usModeDirOut */
    0x033FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 59 - PortConfigSet_0_PortGroup10_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0004U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x017FU,

    /* usModeDirIn */
    0x004BU,

    /* usModeDirOut */
    0x013FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 60 - PortConfigSet_0_PortGroup11_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0xBFFFU,

    /* usModeDirIn */
    0x1FF5U,

    /* usModeDirOut */
    0xAFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 61 - PortConfigSet_0_PortGroup11_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x6914U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 62 - PortConfigSet_0_PortGroup11_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x08D8U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 63 - PortConfigSet_0_PortGroup11_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x7FFFU,

    /* usModeDirIn */
    0x23FDU,

    /* usModeDirOut */
    0x7FFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 64 - PortConfigSet_0_PortGroup11_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x2FFFU,

    /* usModeDirIn */
    0x05EBU,

    /* usModeDirOut */
    0x2FFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 65 - PortConfigSet_0_PortGroup11_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0xEFFFU,

    /* usModeDirIn */
    0x03FEU,

    /* usModeDirOut */
    0xEFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 66 - PortConfigSet_0_PortGroup11_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x8BF8U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 67 - PortConfigSet_0_PortGroup11_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x27FFU,

    /* usModeDirIn */
    0x07FFU,

    /* usModeDirOut */
    0x27FFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 68 - PortConfigSet_0_PortGroup11_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x2FFFU,

    /* usModeDirIn */
    0x00FFU,

    /* usModeDirOut */
    0x2FFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 69 - PortConfigSet_0_PortGroup11_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x0FFFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 70 - PortConfigSet_0_PortGroup11_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xFFFFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 71 - PortConfigSet_0_PortGroup11_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xC1F8U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 72 - PortConfigSet_0_PortGroup11_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x003EU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 73 - PortConfigSet_0_PortGroup11_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x2FFFU,

    /* usModeDirIn */
    0x2FFFU,

    /* usModeDirOut */
    0x2B7FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 74 - PortConfigSet_0_PortGroup11_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x2FFFU,

    /* usModeDirIn */
    0x27FDU,

    /* usModeDirOut */
    0x2FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 75 - PortConfigSet_0_PortGroup11_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0005U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x283FU,

    /* usModeDirIn */
    0x001EU,

    /* usModeDirOut */
    0x283FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 76 - PortConfigSet_0_PortGroup12_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0006U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x6FFFU,

    /* usModeDirIn */
    0x07F7U,

    /* usModeDirOut */
    0x6DFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 77 - PortConfigSet_0_PortGroup12_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0006U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x6DFFU,

    /* usModeDirIn */
    0x40EFU,

    /* usModeDirOut */
    0x6DFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 78 - PortConfigSet_0_PortGroup13_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x3FFFU,

    /* usModeDirIn */
    0x007FU,

    /* usModeDirOut */
    0x3FFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 79 - PortConfigSet_0_PortGroup13_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x03F3U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 80 - PortConfigSet_0_PortGroup13_PortPin2 */
  {
    /* usChangeable */
    0x0001U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x2FFFU,

    /* usModeDirIn */
    0x23F3U,

    /* usModeDirOut */
    0x2FFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 81 - PortConfigSet_0_PortGroup13_PortPin3 */
  {
    /* usChangeable */
    0x0002U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x3FFFU,

    /* usModeDirIn */
    0x0178U,

    /* usModeDirOut */
    0x3FFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 82 - PortConfigSet_0_PortGroup13_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0xA1FFU,

    /* usModeDirIn */
    0x004FU,

    /* usModeDirOut */
    0xA1FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 83 - PortConfigSet_0_PortGroup13_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x83FFU,

    /* usModeDirIn */
    0x005FU,

    /* usModeDirOut */
    0x83FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 84 - PortConfigSet_0_PortGroup13_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x81FFU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x81FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 85 - PortConfigSet_0_PortGroup13_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x833FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x833FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 86 - PortConfigSet_0_PortGroup13_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0xBFFFU,

    /* usModeDirIn */
    0x880FU,

    /* usModeDirOut */
    0x3FFBU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 87 - PortConfigSet_0_PortGroup13_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x03FFU,

    /* usModeDirIn */
    0x03DBU,

    /* usModeDirOut */
    0x01FFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 88 - PortConfigSet_0_PortGroup13_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x91FFU,

    /* usModeDirIn */
    0x80BFU,

    /* usModeDirOut */
    0x91FFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 89 - PortConfigSet_0_PortGroup13_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x29FFU,

    /* usModeDirIn */
    0x29FFU,

    /* usModeDirOut */
    0x09FEU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 90 - PortConfigSet_0_PortGroup13_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0xA07FU,

    /* usModeDirIn */
    0xA07EU,

    /* usModeDirOut */
    0x000FU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 91 - PortConfigSet_0_PortGroup13_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x03FFU,

    /* usModeDirIn */
    0x008BU,

    /* usModeDirOut */
    0x03FFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 92 - PortConfigSet_0_PortGroup13_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0007U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0xF3FFU,

    /* usModeDirIn */
    0x803EU,

    /* usModeDirOut */
    0xF3FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 93 - PortConfigSet_0_PortGroup14_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0FFEU,

    /* usModeDirIn */
    0x0C3CU,

    /* usModeDirOut */
    0x0FFEU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 94 - PortConfigSet_0_PortGroup14_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x2FFEU,

    /* usModeDirIn */
    0x0C3CU,

    /* usModeDirOut */
    0x2BFEU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 95 - PortConfigSet_0_PortGroup14_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x4BFFU,

    /* usModeDirIn */
    0x00DAU,

    /* usModeDirOut */
    0x4BFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 96 - PortConfigSet_0_PortGroup14_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x3FFFU,

    /* usModeDirOut */
    0xFEFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 97 - PortConfigSet_0_PortGroup14_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x0007U,

    /* usModeDirIn */
    0x0003U,

    /* usModeDirOut */
    0x0004U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 98 - PortConfigSet_0_PortGroup14_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x3BFFU,

    /* usModeDirIn */
    0x20C3U,

    /* usModeDirOut */
    0x1BFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 99 - PortConfigSet_0_PortGroup14_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x811BU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 100 - PortConfigSet_0_PortGroup14_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x2FF8U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 101 - PortConfigSet_0_PortGroup14_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0xB7FFU,

    /* usModeDirIn */
    0x07FFU,

    /* usModeDirOut */
    0xB7FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 102 - PortConfigSet_0_PortGroup14_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x8302U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 103 - PortConfigSet_0_PortGroup14_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x00E2U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 104 - PortConfigSet_0_PortGroup14_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x07FFU,

    /* usModeDirIn */
    0x001BU,

    /* usModeDirOut */
    0x07FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 105 - PortConfigSet_0_PortGroup14_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x07FFU,

    /* usModeDirIn */
    0x069FU,

    /* usModeDirOut */
    0x05FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 106 - PortConfigSet_0_PortGroup14_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0BFFU,

    /* usModeDirIn */
    0x081DU,

    /* usModeDirOut */
    0x0BFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 107 - PortConfigSet_0_PortGroup14_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x3FFFU,

    /* usModeDirIn */
    0x28DFU,

    /* usModeDirOut */
    0x3FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 108 - PortConfigSet_0_PortGroup14_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0008U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x15FFU,

    /* usModeDirIn */
    0x11FFU,

    /* usModeDirOut */
    0x15BFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 109 - PortConfigSet_0_PortGroup15_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0009U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x3FFFU,

    /* usModeDirIn */
    0x34BBU,

    /* usModeDirOut */
    0x3FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 110 - PortConfigSet_0_PortGroup15_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0009U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x6FFFU,

    /* usModeDirIn */
    0x67FFU,

    /* usModeDirOut */
    0x0FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 111 - PortConfigSet_0_PortGroup15_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0009U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xE5FCU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 112 - PortConfigSet_0_PortGroup15_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0009U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xFFFFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 113 - PortConfigSet_0_PortGroup15_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0009U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xF1FBU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 114 - PortConfigSet_0_PortGroup15_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0009U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x621FU,

    /* usModeDirIn */
    0x021FU,

    /* usModeDirOut */
    0x6209U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 115 - PortConfigSet_0_PortGroup15_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0009U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xF277U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 116 - PortConfigSet_0_PortGroup15_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0009U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x603FU,

    /* usModeDirIn */
    0x003FU,

    /* usModeDirOut */
    0x600DU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 117 - PortConfigSet_0_PortGroup15_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0009U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x601FU,

    /* usModeDirIn */
    0x001FU,

    /* usModeDirOut */
    0x600BU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 118 - PortConfigSet_0_PortGroup15_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0009U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x307FU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 119 - PortConfigSet_0_PortGroup15_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0009U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x207FU,

    /* usModeDirIn */
    0x005FU,

    /* usModeDirOut */
    0x207FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 120 - PortConfigSet_0_PortGroup15_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0009U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xFFFFU,

    /* usModeDirOut */
    0x17FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 121 - PortConfigSet_0_PortGroup16_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000AU,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x09FFU,

    /* usModeDirIn */
    0x0819U,

    /* usModeDirOut */
    0x01FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 122 - PortConfigSet_0_PortGroup16_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000AU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0FFFU,

    /* usModeDirIn */
    0x080BU,

    /* usModeDirOut */
    0x0FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 123 - PortConfigSet_0_PortGroup16_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000AU,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x09FFU,

    /* usModeDirIn */
    0x014BU,

    /* usModeDirOut */
    0x09FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 124 - PortConfigSet_0_PortGroup16_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000AU,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0BFEU,

    /* usModeDirIn */
    0x08BEU,

    /* usModeDirOut */
    0x0BFEU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 125 - PortConfigSet_0_PortGroup20_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000BU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x61EBU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 126 - PortConfigSet_0_PortGroup20_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000BU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xC2DEU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 127 - PortConfigSet_0_PortGroup20_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000BU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0xAFFFU,

    /* usModeDirIn */
    0x88FEU,

    /* usModeDirOut */
    0x2FFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 128 - PortConfigSet_0_PortGroup20_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000BU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0xAFFFU,

    /* usModeDirIn */
    0x81FCU,

    /* usModeDirOut */
    0xAFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 129 - PortConfigSet_0_PortGroup20_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000BU,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x797FU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 130 - PortConfigSet_0_PortGroup20_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000BU,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x7FFFU,

    /* usModeDirIn */
    0x03FFU,

    /* usModeDirOut */
    0x7FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 131 - PortConfigSet_0_PortGroup20_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000BU,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xC198U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 132 - PortConfigSet_0_PortGroup20_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000BU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0xE9FFU,

    /* usModeDirIn */
    0x01DEU,

    /* usModeDirOut */
    0xE8FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 133 - PortConfigSet_0_PortGroup20_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000BU,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0xE3FFU,

    /* usModeDirIn */
    0xC2FFU,

    /* usModeDirOut */
    0xE3FFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 134 - PortConfigSet_0_PortGroup20_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000BU,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xC1FFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 135 - PortConfigSet_0_PortGroup20_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000BU,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x86FFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 136 - PortConfigSet_0_PortGroup21_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000CU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x8FFFU,

    /* usModeDirIn */
    0x8619U,

    /* usModeDirOut */
    0x8FFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 137 - PortConfigSet_0_PortGroup21_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000CU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0xAFFFU,

    /* usModeDirIn */
    0xAC31U,

    /* usModeDirOut */
    0xAFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 138 - PortConfigSet_0_PortGroup21_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000CU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xA739U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 139 - PortConfigSet_0_PortGroup21_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000CU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x857DU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 140 - PortConfigSet_0_PortGroup21_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000CU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0xBFFDU,

    /* usModeDirIn */
    0x8E08U,

    /* usModeDirOut */
    0xBFFDU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 141 - PortConfigSet_0_PortGroup21_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000CU,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0xFFFDU,

    /* usModeDirIn */
    0x0198U,

    /* usModeDirOut */
    0xFFFDU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 142 - PortConfigSet_0_PortGroup22_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000DU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0xB3FDU,

    /* usModeDirIn */
    0xB065U,

    /* usModeDirOut */
    0x83FDU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 143 - PortConfigSet_0_PortGroup22_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000DU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0xAFFDU,

    /* usModeDirIn */
    0xA161U,

    /* usModeDirOut */
    0x8FFDU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 144 - PortConfigSet_0_PortGroup22_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000DU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0FFFU,

    /* usModeDirIn */
    0x0271U,

    /* usModeDirOut */
    0x0FFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 145 - PortConfigSet_0_PortGroup22_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000DU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x8FFFU,

    /* usModeDirIn */
    0x0955U,

    /* usModeDirOut */
    0x8FFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 146 - PortConfigSet_0_PortGroup22_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000DU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xE0BFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 147 - PortConfigSet_0_PortGroup22_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000DU,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xFFFFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 148 - PortConfigSet_0_PortGroup22_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000DU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0xF7FFU,

    /* usModeDirIn */
    0xF03FU,

    /* usModeDirOut */
    0xF7FFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 149 - PortConfigSet_0_PortGroup22_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000DU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0xF7FFU,

    /* usModeDirIn */
    0xF23FU,

    /* usModeDirOut */
    0xF7FFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 150 - PortConfigSet_0_PortGroup22_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000DU,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x10C6U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 151 - PortConfigSet_0_PortGroup22_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000DU,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xB0FFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 152 - PortConfigSet_0_PortGroup22_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000DU,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xA87FU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 153 - PortConfigSet_0_PortGroup22_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000DU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xA83FU,

    /* usModeDirOut */
    0xDFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 154 - PortConfigSet_0_PortGroup23_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000EU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0xEFFFU,

    /* usModeDirIn */
    0xC6BEU,

    /* usModeDirOut */
    0xABFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 155 - PortConfigSet_0_PortGroup23_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000EU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x3FFFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 156 - PortConfigSet_0_PortGroup23_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000EU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xB03FU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 157 - PortConfigSet_0_PortGroup23_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000EU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0xEFFFU,

    /* usModeDirIn */
    0xA5FDU,

    /* usModeDirOut */
    0xEFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 158 - PortConfigSet_0_PortGroup23_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000EU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x01ACU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 159 - PortConfigSet_0_PortGroup23_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000EU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0xFBFFU,

    /* usModeDirIn */
    0x811FU,

    /* usModeDirOut */
    0xFBFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 160 - PortConfigSet_0_PortGroup23_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000EU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0xBBFFU,

    /* usModeDirIn */
    0x83BFU,

    /* usModeDirOut */
    0xBBFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 161 - PortConfigSet_0_PortGroup24_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x00BFU,

    /* usModeDirIn */
    0x00AFU,

    /* usModeDirOut */
    0x001FU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 162 - PortConfigSet_0_PortGroup24_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x009FU,

    /* usModeDirIn */
    0x009DU,

    /* usModeDirOut */
    0x001FU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 163 - PortConfigSet_0_PortGroup24_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x009FU,

    /* usModeDirIn */
    0x008FU,

    /* usModeDirOut */
    0x001FU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 164 - PortConfigSet_0_PortGroup24_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x009FU,

    /* usModeDirIn */
    0x008FU,

    /* usModeDirOut */
    0x001FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 165 - PortConfigSet_0_PortGroup24_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x019FU,

    /* usModeDirIn */
    0x008FU,

    /* usModeDirOut */
    0x011FU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 166 - PortConfigSet_0_PortGroup24_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x019FU,

    /* usModeDirIn */
    0x018FU,

    /* usModeDirOut */
    0x011FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 167 - PortConfigSet_0_PortGroup24_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x009FU,

    /* usModeDirIn */
    0x0007U,

    /* usModeDirOut */
    0x009FU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 168 - PortConfigSet_0_PortGroup24_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x00DFU,

    /* usModeDirIn */
    0x00DFU,

    /* usModeDirOut */
    0x001FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 169 - PortConfigSet_0_PortGroup24_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x008FU,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x008FU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 170 - PortConfigSet_0_PortGroup24_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x00CFU,

    /* usModeDirIn */
    0x008DU,

    /* usModeDirOut */
    0x004FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 171 - PortConfigSet_0_PortGroup24_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x004FU,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x004FU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 172 - PortConfigSet_0_PortGroup24_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x000FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 173 - PortConfigSet_0_PortGroup24_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0007U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0007U,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 174 - PortConfigSet_0_PortGroup24_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0007U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0007U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 175 - PortConfigSet_0_PortGroup24_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0087U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0087U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 176 - PortConfigSet_0_PortGroup24_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x000FU,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x009FU,

    /* usModeDirIn */
    0x009DU,

    /* usModeDirOut */
    0x0007U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 177 - PortConfigSet_0_PortGroup25_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x40BFU,

    /* usModeDirIn */
    0x0007U,

    /* usModeDirOut */
    0x40BFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 178 - PortConfigSet_0_PortGroup25_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x40FFU,

    /* usModeDirIn */
    0x0007U,

    /* usModeDirOut */
    0x40FFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 179 - PortConfigSet_0_PortGroup25_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x41BFU,

    /* usModeDirIn */
    0x0007U,

    /* usModeDirOut */
    0x41BFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 180 - PortConfigSet_0_PortGroup25_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x407FU,

    /* usModeDirIn */
    0x004FU,

    /* usModeDirOut */
    0x403FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 181 - PortConfigSet_0_PortGroup25_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x413FU,

    /* usModeDirIn */
    0x0007U,

    /* usModeDirOut */
    0x413FU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 182 - PortConfigSet_0_PortGroup25_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x407FU,

    /* usModeDirIn */
    0x0007U,

    /* usModeDirOut */
    0x407FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 183 - PortConfigSet_0_PortGroup25_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x40FFU,

    /* usModeDirIn */
    0x008FU,

    /* usModeDirOut */
    0x407FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 184 - PortConfigSet_0_PortGroup25_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x407FU,

    /* usModeDirIn */
    0x0007U,

    /* usModeDirOut */
    0x407FU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 185 - PortConfigSet_0_PortGroup25_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x400FU,

    /* usModeDirIn */
    0x000DU,

    /* usModeDirOut */
    0x400FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 186 - PortConfigSet_0_PortGroup25_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x405FU,

    /* usModeDirIn */
    0x405DU,

    /* usModeDirOut */
    0x000FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 187 - PortConfigSet_0_PortGroup25_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x400FU,

    /* usModeDirIn */
    0x400DU,

    /* usModeDirOut */
    0x000FU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 188 - PortConfigSet_0_PortGroup25_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x41CFU,

    /* usModeDirIn */
    0x414DU,

    /* usModeDirOut */
    0x008FU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 189 - PortConfigSet_0_PortGroup25_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x409FU,

    /* usModeDirIn */
    0x400DU,

    /* usModeDirOut */
    0x409FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 190 - PortConfigSet_0_PortGroup25_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x41DFU,

    /* usModeDirIn */
    0x400DU,

    /* usModeDirOut */
    0x01DFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 191 - PortConfigSet_0_PortGroup25_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x409FU,

    /* usModeDirIn */
    0x000DU,

    /* usModeDirOut */
    0x409FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 192 - PortConfigSet_0_PortGroup25_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0010U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x419FU,

    /* usModeDirIn */
    0x400DU,

    /* usModeDirOut */
    0x419FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 193 - PortConfigSet_0_PortGroup26_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0011U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x00BFU,

    /* usModeDirIn */
    0x00AFU,

    /* usModeDirOut */
    0x001FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 194 - PortConfigSet_0_PortGroup27_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0012U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 195 - PortConfigSet_0_PortGroup28_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0013U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 196 - PortConfigSet_0_PortGroup30_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0xC34FU,

    /* usModeDirIn */
    0x8305U,

    /* usModeDirOut */
    0xC04FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 197 - PortConfigSet_0_PortGroup30_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0xE14FU,

    /* usModeDirIn */
    0xA14DU,

    /* usModeDirOut */
    0xE00FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 198 - PortConfigSet_0_PortGroup30_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0xE11FU,

    /* usModeDirIn */
    0xA105U,

    /* usModeDirOut */
    0xC01FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 199 - PortConfigSet_0_PortGroup30_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0xE14FU,

    /* usModeDirIn */
    0xA105U,

    /* usModeDirOut */
    0xC04FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 200 - PortConfigSet_0_PortGroup30_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0xC12FU,

    /* usModeDirIn */
    0x8005U,

    /* usModeDirOut */
    0xC12FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 201 - PortConfigSet_0_PortGroup30_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0xE14FU,

    /* usModeDirIn */
    0xA005U,

    /* usModeDirOut */
    0xE14FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 202 - PortConfigSet_0_PortGroup30_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0xC01FU,

    /* usModeDirIn */
    0x8005U,

    /* usModeDirOut */
    0xC01FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 203 - PortConfigSet_0_PortGroup30_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0xE04FU,

    /* usModeDirIn */
    0x804DU,

    /* usModeDirOut */
    0xE00FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 204 - PortConfigSet_0_PortGroup30_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0xC00FU,

    /* usModeDirIn */
    0xC00FU,

    /* usModeDirOut */
    0x8007U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 205 - PortConfigSet_0_PortGroup30_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0xA0FFU,

    /* usModeDirIn */
    0x80FFU,

    /* usModeDirOut */
    0xA007U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 206 - PortConfigSet_0_PortGroup30_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x801FU,

    /* usModeDirIn */
    0x800FU,

    /* usModeDirOut */
    0x8017U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 207 - PortConfigSet_0_PortGroup30_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x809FU,

    /* usModeDirIn */
    0x800FU,

    /* usModeDirOut */
    0x8097U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 208 - PortConfigSet_0_PortGroup30_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x809FU,

    /* usModeDirIn */
    0x800FU,

    /* usModeDirOut */
    0x809FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 209 - PortConfigSet_0_PortGroup30_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0xA08FU,

    /* usModeDirIn */
    0x800DU,

    /* usModeDirOut */
    0xA08FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 210 - PortConfigSet_0_PortGroup30_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0xC08FU,

    /* usModeDirIn */
    0x800DU,

    /* usModeDirOut */
    0xC08FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 211 - PortConfigSet_0_PortGroup30_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0014U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0xE08FU,

    /* usModeDirIn */
    0x800DU,

    /* usModeDirOut */
    0xE08FU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 212 - PortConfigSet_0_PortGroup31_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x85FFU,

    /* usModeDirIn */
    0x853DU,

    /* usModeDirOut */
    0x81EFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 213 - PortConfigSet_0_PortGroup31_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x857FU,

    /* usModeDirIn */
    0x800DU,

    /* usModeDirOut */
    0x857FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 214 - PortConfigSet_0_PortGroup31_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x857FU,

    /* usModeDirIn */
    0x8579U,

    /* usModeDirOut */
    0x811FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 215 - PortConfigSet_0_PortGroup31_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x87BFU,

    /* usModeDirIn */
    0x8309U,

    /* usModeDirOut */
    0x87BFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 216 - PortConfigSet_0_PortGroup31_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x871FU,

    /* usModeDirIn */
    0x8709U,

    /* usModeDirOut */
    0x831FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 217 - PortConfigSet_0_PortGroup31_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x879FU,

    /* usModeDirIn */
    0x8309U,

    /* usModeDirOut */
    0x879FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 218 - PortConfigSet_0_PortGroup31_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x87FFU,

    /* usModeDirIn */
    0x8709U,

    /* usModeDirOut */
    0x83FFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 219 - PortConfigSet_0_PortGroup31_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x871FU,

    /* usModeDirIn */
    0x8309U,

    /* usModeDirOut */
    0x871FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 220 - PortConfigSet_0_PortGroup31_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x874FU,

    /* usModeDirIn */
    0x870BU,

    /* usModeDirOut */
    0x834FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 221 - PortConfigSet_0_PortGroup31_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x874FU,

    /* usModeDirIn */
    0x834FU,

    /* usModeDirOut */
    0x870FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 222 - PortConfigSet_0_PortGroup31_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0xC70FU,

    /* usModeDirIn */
    0x820BU,

    /* usModeDirOut */
    0xC70FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 223 - PortConfigSet_0_PortGroup31_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0xC72FU,

    /* usModeDirIn */
    0x820BU,

    /* usModeDirOut */
    0xC72FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 224 - PortConfigSet_0_PortGroup31_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0xC73FU,

    /* usModeDirIn */
    0x820BU,

    /* usModeDirOut */
    0xC73FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 225 - PortConfigSet_0_PortGroup31_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0xC11FU,

    /* usModeDirIn */
    0x810BU,

    /* usModeDirOut */
    0xC01FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 226 - PortConfigSet_0_PortGroup31_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0xC15FU,

    /* usModeDirIn */
    0x800BU,

    /* usModeDirOut */
    0xC15FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 227 - PortConfigSet_0_PortGroup31_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0015U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0xC15FU,

    /* usModeDirIn */
    0x814FU,

    /* usModeDirOut */
    0xC01FU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 228 - PortConfigSet_0_PortGroup32_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0016U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x83FFU,

    /* usModeDirIn */
    0x82FFU,

    /* usModeDirOut */
    0x837FU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 229 - PortConfigSet_0_PortGroup32_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0016U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0xBFFFU,

    /* usModeDirIn */
    0x800FU,

    /* usModeDirOut */
    0xBFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 230 - PortConfigSet_0_PortGroup32_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0016U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0xF5FFU,

    /* usModeDirIn */
    0x813FU,

    /* usModeDirOut */
    0xF5FFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 231 - PortConfigSet_0_PortGroup32_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0016U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0xF07FU,

    /* usModeDirIn */
    0x802FU,

    /* usModeDirOut */
    0xF079U,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 232 - PortConfigSet_0_PortGroup32_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0016U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0xB0EFU,

    /* usModeDirIn */
    0x8049U,

    /* usModeDirOut */
    0xB0EFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 233 - PortConfigSet_0_PortGroup33_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x9FFFU,

    /* usModeDirIn */
    0x182FU,

    /* usModeDirOut */
    0x9FFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 234 - PortConfigSet_0_PortGroup33_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0xBFFFU,

    /* usModeDirIn */
    0x11B9U,

    /* usModeDirOut */
    0xBFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 235 - PortConfigSet_0_PortGroup33_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xA279U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 236 - PortConfigSet_0_PortGroup33_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x2C77U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 237 - PortConfigSet_0_PortGroup33_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x21FFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 238 - PortConfigSet_0_PortGroup33_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x33F3U,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 239 - PortConfigSet_0_PortGroup33_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x203FU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 240 - PortConfigSet_0_PortGroup33_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xE47FU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 241 - PortConfigSet_0_PortGroup33_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xAA1FU,

    /* usModeDirOut */
    0xFDFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 242 - PortConfigSet_0_PortGroup33_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 243 - PortConfigSet_0_PortGroup33_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xE7FFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 244 - PortConfigSet_0_PortGroup33_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0xEFFFU,

    /* usModeDirIn */
    0xA3FFU,

    /* usModeDirOut */
    0xEFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 245 - PortConfigSet_0_PortGroup33_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xA8FFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 246 - PortConfigSet_0_PortGroup33_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0xA1FFU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 247 - PortConfigSet_0_PortGroup33_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0xFFFFU,

    /* usModeDirIn */
    0x82FEU,

    /* usModeDirOut */
    0xFFFFU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 248 - PortConfigSet_0_PortGroup33_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0017U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0xE4BFU,

    /* usModeDirIn */
    0x8013U,

    /* usModeDirOut */
    0xE4BEU,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 249 - PortConfigSet_0_PortGroup34_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0018U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 250 - PortConfigSet_0_PortGroup34_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0018U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0xEFFFU,

    /* usModeDirIn */
    0x03FFU,

    /* usModeDirOut */
    0xEFFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 251 - PortConfigSet_0_PortGroup34_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0018U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 252 - PortConfigSet_0_PortGroup34_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0018U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x3FFFU,

    /* usModeDirIn */
    0x055FU,

    /* usModeDirOut */
    0x3FFFU,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 253 - PortConfigSet_0_PortGroup34_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0018U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0xFA43U,

    /* usModeDirIn */
    0x8203U,

    /* usModeDirOut */
    0xFA43U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 254 - PortConfigSet_0_PortGroup34_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0018U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 255 - PortConfigSet_0_PortGroup34_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0018U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0003U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0003U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 256 - PortConfigSet_0_PortGroup36_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0003U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0003U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 257 - PortConfigSet_0_PortGroup36_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 258 - PortConfigSet_0_PortGroup36_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 259 - PortConfigSet_0_PortGroup36_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 260 - PortConfigSet_0_PortGroup36_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 261 - PortConfigSet_0_PortGroup36_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 262 - PortConfigSet_0_PortGroup36_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 263 - PortConfigSet_0_PortGroup36_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 264 - PortConfigSet_0_PortGroup36_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 265 - PortConfigSet_0_PortGroup36_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 266 - PortConfigSet_0_PortGroup36_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 267 - PortConfigSet_0_PortGroup36_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 268 - PortConfigSet_0_PortGroup36_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 269 - PortConfigSet_0_PortGroup36_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 270 - PortConfigSet_0_PortGroup36_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 271 - PortConfigSet_0_PortGroup36_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0019U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 272 - PortConfigSet_0_PortGroup37_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 273 - PortConfigSet_0_PortGroup37_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 274 - PortConfigSet_0_PortGroup37_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 275 - PortConfigSet_0_PortGroup37_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 276 - PortConfigSet_0_PortGroup37_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 277 - PortConfigSet_0_PortGroup37_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 278 - PortConfigSet_0_PortGroup37_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 279 - PortConfigSet_0_PortGroup37_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 280 - PortConfigSet_0_PortGroup37_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 281 - PortConfigSet_0_PortGroup37_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 282 - PortConfigSet_0_PortGroup37_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 283 - PortConfigSet_0_PortGroup37_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 284 - PortConfigSet_0_PortGroup37_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 285 - PortConfigSet_0_PortGroup37_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 286 - PortConfigSet_0_PortGroup37_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 287 - PortConfigSet_0_PortGroup37_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001AU,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 288 - PortConfigSet_0_PortGroup38_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000DU,

    /* usModeDirIn */
    0x000DU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 289 - PortConfigSet_0_PortGroup38_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000DU,

    /* usModeDirIn */
    0x000DU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 290 - PortConfigSet_0_PortGroup38_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000DU,

    /* usModeDirIn */
    0x000DU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 291 - PortConfigSet_0_PortGroup38_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000DU,

    /* usModeDirIn */
    0x000DU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 292 - PortConfigSet_0_PortGroup38_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000DU,

    /* usModeDirIn */
    0x000DU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 293 - PortConfigSet_0_PortGroup38_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000DU,

    /* usModeDirIn */
    0x000DU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 294 - PortConfigSet_0_PortGroup38_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000DU,

    /* usModeDirIn */
    0x000DU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 295 - PortConfigSet_0_PortGroup38_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000DU,

    /* usModeDirIn */
    0x000DU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 296 - PortConfigSet_0_PortGroup38_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 297 - PortConfigSet_0_PortGroup38_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 298 - PortConfigSet_0_PortGroup38_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 299 - PortConfigSet_0_PortGroup38_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 300 - PortConfigSet_0_PortGroup38_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 301 - PortConfigSet_0_PortGroup38_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 302 - PortConfigSet_0_PortGroup38_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 303 - PortConfigSet_0_PortGroup38_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001BU,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 304 - PortConfigSet_0_PortGroup39_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 305 - PortConfigSet_0_PortGroup39_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 306 - PortConfigSet_0_PortGroup39_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 307 - PortConfigSet_0_PortGroup39_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 308 - PortConfigSet_0_PortGroup39_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 309 - PortConfigSet_0_PortGroup39_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 310 - PortConfigSet_0_PortGroup39_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 311 - PortConfigSet_0_PortGroup39_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 312 - PortConfigSet_0_PortGroup39_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 313 - PortConfigSet_0_PortGroup39_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 314 - PortConfigSet_0_PortGroup39_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 315 - PortConfigSet_0_PortGroup39_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 316 - PortConfigSet_0_PortGroup39_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 317 - PortConfigSet_0_PortGroup39_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 318 - PortConfigSet_0_PortGroup39_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 319 - PortConfigSet_0_PortGroup39_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001CU,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0005U,

    /* usModeDirIn */
    0x0005U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 320 - PortConfigSet_0_PortGroup40_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 321 - PortConfigSet_0_PortGroup40_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 322 - PortConfigSet_0_PortGroup40_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 323 - PortConfigSet_0_PortGroup40_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 324 - PortConfigSet_0_PortGroup40_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x0003U,

    /* usModeDirIn */
    0x0003U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 325 - PortConfigSet_0_PortGroup40_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x0003U,

    /* usModeDirIn */
    0x0003U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 326 - PortConfigSet_0_PortGroup40_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x0003U,

    /* usModeDirIn */
    0x0003U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 327 - PortConfigSet_0_PortGroup40_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 328 - PortConfigSet_0_PortGroup40_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0007U,

    /* usModeDirIn */
    0x0007U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 329 - PortConfigSet_0_PortGroup40_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0003U,

    /* usModeDirIn */
    0x0003U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0002U
  },
  /* Index: 330 - PortConfigSet_0_PortGroup40_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 331 - PortConfigSet_0_PortGroup40_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 332 - PortConfigSet_0_PortGroup40_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 333 - PortConfigSet_0_PortGroup40_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 334 - PortConfigSet_0_PortGroup40_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001DU,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0007U,

    /* usModeDirIn */
    0x0007U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 335 - PortConfigSet_0_PortGroup41_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 336 - PortConfigSet_0_PortGroup41_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 337 - PortConfigSet_0_PortGroup41_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 338 - PortConfigSet_0_PortGroup41_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 339 - PortConfigSet_0_PortGroup41_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 340 - PortConfigSet_0_PortGroup41_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 341 - PortConfigSet_0_PortGroup41_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 342 - PortConfigSet_0_PortGroup41_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 343 - PortConfigSet_0_PortGroup41_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 344 - PortConfigSet_0_PortGroup41_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 345 - PortConfigSet_0_PortGroup41_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 346 - PortConfigSet_0_PortGroup41_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 347 - PortConfigSet_0_PortGroup41_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 348 - PortConfigSet_0_PortGroup41_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 349 - PortConfigSet_0_PortGroup41_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 350 - PortConfigSet_0_PortGroup41_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001EU,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 351 - PortConfigSet_0_PortGroup42_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 352 - PortConfigSet_0_PortGroup42_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 353 - PortConfigSet_0_PortGroup42_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 354 - PortConfigSet_0_PortGroup42_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 355 - PortConfigSet_0_PortGroup42_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 356 - PortConfigSet_0_PortGroup42_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 357 - PortConfigSet_0_PortGroup42_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 358 - PortConfigSet_0_PortGroup42_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 359 - PortConfigSet_0_PortGroup42_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 360 - PortConfigSet_0_PortGroup42_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 361 - PortConfigSet_0_PortGroup42_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 362 - PortConfigSet_0_PortGroup42_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 363 - PortConfigSet_0_PortGroup42_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 364 - PortConfigSet_0_PortGroup42_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 365 - PortConfigSet_0_PortGroup42_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 366 - PortConfigSet_0_PortGroup42_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x001FU,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 367 - PortConfigSet_0_PortGroup43_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 368 - PortConfigSet_0_PortGroup43_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 369 - PortConfigSet_0_PortGroup43_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 370 - PortConfigSet_0_PortGroup43_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 371 - PortConfigSet_0_PortGroup43_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 372 - PortConfigSet_0_PortGroup43_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 373 - PortConfigSet_0_PortGroup43_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 374 - PortConfigSet_0_PortGroup43_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 375 - PortConfigSet_0_PortGroup43_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 376 - PortConfigSet_0_PortGroup43_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 377 - PortConfigSet_0_PortGroup43_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 378 - PortConfigSet_0_PortGroup43_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 379 - PortConfigSet_0_PortGroup43_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 380 - PortConfigSet_0_PortGroup43_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 381 - PortConfigSet_0_PortGroup43_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 382 - PortConfigSet_0_PortGroup43_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0020U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 383 - PortConfigSet_0_PortGroup44_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 384 - PortConfigSet_0_PortGroup44_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 385 - PortConfigSet_0_PortGroup44_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 386 - PortConfigSet_0_PortGroup44_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 387 - PortConfigSet_0_PortGroup44_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 388 - PortConfigSet_0_PortGroup44_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 389 - PortConfigSet_0_PortGroup44_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 390 - PortConfigSet_0_PortGroup44_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 391 - PortConfigSet_0_PortGroup44_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 392 - PortConfigSet_0_PortGroup44_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 393 - PortConfigSet_0_PortGroup44_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 394 - PortConfigSet_0_PortGroup44_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 395 - PortConfigSet_0_PortGroup44_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 396 - PortConfigSet_0_PortGroup44_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 397 - PortConfigSet_0_PortGroup44_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 398 - PortConfigSet_0_PortGroup44_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0021U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 399 - PortConfigSet_0_PortGroup45_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 400 - PortConfigSet_0_PortGroup45_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 401 - PortConfigSet_0_PortGroup45_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 402 - PortConfigSet_0_PortGroup45_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 403 - PortConfigSet_0_PortGroup45_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 404 - PortConfigSet_0_PortGroup45_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 405 - PortConfigSet_0_PortGroup45_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 406 - PortConfigSet_0_PortGroup45_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 407 - PortConfigSet_0_PortGroup45_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 408 - PortConfigSet_0_PortGroup45_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 409 - PortConfigSet_0_PortGroup45_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 410 - PortConfigSet_0_PortGroup45_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 411 - PortConfigSet_0_PortGroup45_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 412 - PortConfigSet_0_PortGroup45_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 413 - PortConfigSet_0_PortGroup45_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 414 - PortConfigSet_0_PortGroup45_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0022U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 415 - PortConfigSet_0_PortGroup46_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 416 - PortConfigSet_0_PortGroup46_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 417 - PortConfigSet_0_PortGroup46_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 418 - PortConfigSet_0_PortGroup46_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 419 - PortConfigSet_0_PortGroup46_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 420 - PortConfigSet_0_PortGroup46_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 421 - PortConfigSet_0_PortGroup46_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 422 - PortConfigSet_0_PortGroup46_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 423 - PortConfigSet_0_PortGroup46_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 424 - PortConfigSet_0_PortGroup46_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 425 - PortConfigSet_0_PortGroup46_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 426 - PortConfigSet_0_PortGroup46_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 427 - PortConfigSet_0_PortGroup46_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 428 - PortConfigSet_0_PortGroup46_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 429 - PortConfigSet_0_PortGroup46_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 430 - PortConfigSet_0_PortGroup46_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0023U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 431 - PortConfigSet_0_PortGroup47_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 432 - PortConfigSet_0_PortGroup47_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 433 - PortConfigSet_0_PortGroup47_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 434 - PortConfigSet_0_PortGroup47_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 435 - PortConfigSet_0_PortGroup47_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 436 - PortConfigSet_0_PortGroup47_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 437 - PortConfigSet_0_PortGroup47_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 438 - PortConfigSet_0_PortGroup47_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 439 - PortConfigSet_0_PortGroup47_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 440 - PortConfigSet_0_PortGroup47_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 441 - PortConfigSet_0_PortGroup47_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 442 - PortConfigSet_0_PortGroup47_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 443 - PortConfigSet_0_PortGroup47_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 444 - PortConfigSet_0_PortGroup47_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 445 - PortConfigSet_0_PortGroup47_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 446 - PortConfigSet_0_PortGroup47_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0024U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 447 - PortConfigSet_0_PortGroup48_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 448 - PortConfigSet_0_PortGroup48_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 449 - PortConfigSet_0_PortGroup48_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 450 - PortConfigSet_0_PortGroup48_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 451 - PortConfigSet_0_PortGroup48_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 452 - PortConfigSet_0_PortGroup48_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 453 - PortConfigSet_0_PortGroup48_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 454 - PortConfigSet_0_PortGroup48_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 455 - PortConfigSet_0_PortGroup48_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 456 - PortConfigSet_0_PortGroup48_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 457 - PortConfigSet_0_PortGroup48_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 458 - PortConfigSet_0_PortGroup48_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 459 - PortConfigSet_0_PortGroup48_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 460 - PortConfigSet_0_PortGroup48_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 461 - PortConfigSet_0_PortGroup48_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 462 - PortConfigSet_0_PortGroup48_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0025U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 463 - PortConfigSet_0_PortGroup49_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 464 - PortConfigSet_0_PortGroup49_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 465 - PortConfigSet_0_PortGroup49_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 466 - PortConfigSet_0_PortGroup49_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 467 - PortConfigSet_0_PortGroup49_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 468 - PortConfigSet_0_PortGroup49_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 469 - PortConfigSet_0_PortGroup49_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 470 - PortConfigSet_0_PortGroup49_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 471 - PortConfigSet_0_PortGroup49_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 472 - PortConfigSet_0_PortGroup49_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 473 - PortConfigSet_0_PortGroup49_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 474 - PortConfigSet_0_PortGroup49_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 475 - PortConfigSet_0_PortGroup49_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 476 - PortConfigSet_0_PortGroup49_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 477 - PortConfigSet_0_PortGroup49_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 478 - PortConfigSet_0_PortGroup49_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0026U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 479 - PortConfigSet_0_PortGroup50_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 480 - PortConfigSet_0_PortGroup50_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 481 - PortConfigSet_0_PortGroup50_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 482 - PortConfigSet_0_PortGroup50_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 483 - PortConfigSet_0_PortGroup50_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 484 - PortConfigSet_0_PortGroup50_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 485 - PortConfigSet_0_PortGroup50_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 486 - PortConfigSet_0_PortGroup50_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 487 - PortConfigSet_0_PortGroup50_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 488 - PortConfigSet_0_PortGroup50_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 489 - PortConfigSet_0_PortGroup50_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 490 - PortConfigSet_0_PortGroup50_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 491 - PortConfigSet_0_PortGroup50_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 492 - PortConfigSet_0_PortGroup50_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 493 - PortConfigSet_0_PortGroup50_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 494 - PortConfigSet_0_PortGroup50_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0027U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 495 - PortConfigSet_0_PortGroup51_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 496 - PortConfigSet_0_PortGroup51_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 497 - PortConfigSet_0_PortGroup51_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 498 - PortConfigSet_0_PortGroup51_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 499 - PortConfigSet_0_PortGroup51_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 500 - PortConfigSet_0_PortGroup51_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 501 - PortConfigSet_0_PortGroup51_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 502 - PortConfigSet_0_PortGroup51_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 503 - PortConfigSet_0_PortGroup51_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 504 - PortConfigSet_0_PortGroup51_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 505 - PortConfigSet_0_PortGroup51_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 506 - PortConfigSet_0_PortGroup51_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 507 - PortConfigSet_0_PortGroup51_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 508 - PortConfigSet_0_PortGroup51_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 509 - PortConfigSet_0_PortGroup51_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 510 - PortConfigSet_0_PortGroup51_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0028U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 511 - PortConfigSet_0_PortGroup52_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 512 - PortConfigSet_0_PortGroup52_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 513 - PortConfigSet_0_PortGroup52_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 514 - PortConfigSet_0_PortGroup52_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 515 - PortConfigSet_0_PortGroup52_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 516 - PortConfigSet_0_PortGroup52_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 517 - PortConfigSet_0_PortGroup52_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 518 - PortConfigSet_0_PortGroup52_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 519 - PortConfigSet_0_PortGroup52_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 520 - PortConfigSet_0_PortGroup52_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 521 - PortConfigSet_0_PortGroup52_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 522 - PortConfigSet_0_PortGroup52_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 523 - PortConfigSet_0_PortGroup52_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 524 - PortConfigSet_0_PortGroup52_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 525 - PortConfigSet_0_PortGroup52_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 526 - PortConfigSet_0_PortGroup52_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x0029U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 527 - PortConfigSet_0_PortGroup53_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 528 - PortConfigSet_0_PortGroup53_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 529 - PortConfigSet_0_PortGroup53_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 530 - PortConfigSet_0_PortGroup53_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 531 - PortConfigSet_0_PortGroup53_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 532 - PortConfigSet_0_PortGroup53_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 533 - PortConfigSet_0_PortGroup53_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 534 - PortConfigSet_0_PortGroup53_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 535 - PortConfigSet_0_PortGroup53_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 536 - PortConfigSet_0_PortGroup53_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 537 - PortConfigSet_0_PortGroup53_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 538 - PortConfigSet_0_PortGroup53_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 539 - PortConfigSet_0_PortGroup53_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 540 - PortConfigSet_0_PortGroup53_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 541 - PortConfigSet_0_PortGroup53_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 542 - PortConfigSet_0_PortGroup53_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002AU,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 543 - PortConfigSet_0_PortGroup54_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 544 - PortConfigSet_0_PortGroup54_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 545 - PortConfigSet_0_PortGroup54_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 546 - PortConfigSet_0_PortGroup54_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 547 - PortConfigSet_0_PortGroup54_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 548 - PortConfigSet_0_PortGroup54_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 549 - PortConfigSet_0_PortGroup54_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 550 - PortConfigSet_0_PortGroup54_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 551 - PortConfigSet_0_PortGroup54_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 552 - PortConfigSet_0_PortGroup54_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 553 - PortConfigSet_0_PortGroup54_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 554 - PortConfigSet_0_PortGroup54_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 555 - PortConfigSet_0_PortGroup54_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 556 - PortConfigSet_0_PortGroup54_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 557 - PortConfigSet_0_PortGroup54_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 558 - PortConfigSet_0_PortGroup54_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002BU,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 559 - PortConfigSet_0_PortGroup55_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 560 - PortConfigSet_0_PortGroup55_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 561 - PortConfigSet_0_PortGroup55_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 562 - PortConfigSet_0_PortGroup55_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 563 - PortConfigSet_0_PortGroup55_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 564 - PortConfigSet_0_PortGroup55_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 565 - PortConfigSet_0_PortGroup55_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 566 - PortConfigSet_0_PortGroup55_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 567 - PortConfigSet_0_PortGroup55_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 568 - PortConfigSet_0_PortGroup55_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 569 - PortConfigSet_0_PortGroup55_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 570 - PortConfigSet_0_PortGroup55_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 571 - PortConfigSet_0_PortGroup55_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 572 - PortConfigSet_0_PortGroup55_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 573 - PortConfigSet_0_PortGroup55_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 574 - PortConfigSet_0_PortGroup55_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002CU,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 575 - PortConfigSet_0_PortGroup56_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 576 - PortConfigSet_0_PortGroup56_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 577 - PortConfigSet_0_PortGroup56_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 578 - PortConfigSet_0_PortGroup56_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 579 - PortConfigSet_0_PortGroup56_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 580 - PortConfigSet_0_PortGroup56_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 581 - PortConfigSet_0_PortGroup56_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 582 - PortConfigSet_0_PortGroup56_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 583 - PortConfigSet_0_PortGroup56_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 584 - PortConfigSet_0_PortGroup56_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 585 - PortConfigSet_0_PortGroup56_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 586 - PortConfigSet_0_PortGroup56_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 587 - PortConfigSet_0_PortGroup56_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 588 - PortConfigSet_0_PortGroup56_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 589 - PortConfigSet_0_PortGroup56_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 590 - PortConfigSet_0_PortGroup56_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0001U,

    /* usPortLoc */
    0x002DU,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 591 - PortConfigSet_0_PortGroup57_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 592 - PortConfigSet_0_PortGroup57_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 593 - PortConfigSet_0_PortGroup57_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 594 - PortConfigSet_0_PortGroup57_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 595 - PortConfigSet_0_PortGroup57_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 596 - PortConfigSet_0_PortGroup57_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 597 - PortConfigSet_0_PortGroup57_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 598 - PortConfigSet_0_PortGroup57_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000FU,

    /* usModeDirIn */
    0x000FU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 599 - PortConfigSet_0_PortGroup57_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 600 - PortConfigSet_0_PortGroup57_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 601 - PortConfigSet_0_PortGroup57_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 602 - PortConfigSet_0_PortGroup57_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 603 - PortConfigSet_0_PortGroup57_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 604 - PortConfigSet_0_PortGroup57_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 605 - PortConfigSet_0_PortGroup57_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 606 - PortConfigSet_0_PortGroup57_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 607 - PortConfigSet_0_PortGroup58_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 608 - PortConfigSet_0_PortGroup58_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 609 - PortConfigSet_0_PortGroup58_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 610 - PortConfigSet_0_PortGroup58_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 611 - PortConfigSet_0_PortGroup58_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 612 - PortConfigSet_0_PortGroup58_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 613 - PortConfigSet_0_PortGroup58_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 614 - PortConfigSet_0_PortGroup58_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 615 - PortConfigSet_0_PortGroup58_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 616 - PortConfigSet_0_PortGroup58_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 617 - PortConfigSet_0_PortGroup58_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 618 - PortConfigSet_0_PortGroup58_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 619 - PortConfigSet_0_PortGroup58_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 620 - PortConfigSet_0_PortGroup58_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 621 - PortConfigSet_0_PortGroup58_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 622 - PortConfigSet_0_PortGroup58_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0001U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x000BU,

    /* usModeDirIn */
    0x000BU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 623 - PortConfigSet_0_PortGroup59_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 624 - PortConfigSet_0_PortGroup59_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 625 - PortConfigSet_0_PortGroup59_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 626 - PortConfigSet_0_PortGroup59_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 627 - PortConfigSet_0_PortGroup59_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 628 - PortConfigSet_0_PortGroup59_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 629 - PortConfigSet_0_PortGroup59_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 630 - PortConfigSet_0_PortGroup59_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x000AU,

    /* usModeDirIn */
    0x000AU,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 631 - PortConfigSet_0_PortGroup59_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 632 - PortConfigSet_0_PortGroup59_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 633 - PortConfigSet_0_PortGroup59_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 634 - PortConfigSet_0_PortGroup59_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 635 - PortConfigSet_0_PortGroup59_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 636 - PortConfigSet_0_PortGroup59_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 637 - PortConfigSet_0_PortGroup59_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 638 - PortConfigSet_0_PortGroup59_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0002U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0008U,

    /* usModeDirIn */
    0x0008U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 639 - PortConfigSet_0_PortGroup60_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 640 - PortConfigSet_0_PortGroup60_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 641 - PortConfigSet_0_PortGroup60_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 642 - PortConfigSet_0_PortGroup60_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 643 - PortConfigSet_0_PortGroup60_PortPin4 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0010U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 644 - PortConfigSet_0_PortGroup60_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 645 - PortConfigSet_0_PortGroup60_PortPin6 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0040U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 646 - PortConfigSet_0_PortGroup60_PortPin7 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0080U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 647 - PortConfigSet_0_PortGroup60_PortPin8 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0100U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 648 - PortConfigSet_0_PortGroup60_PortPin9 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0200U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 649 - PortConfigSet_0_PortGroup60_PortPin10 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0400U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 650 - PortConfigSet_0_PortGroup60_PortPin11 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x0800U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 651 - PortConfigSet_0_PortGroup60_PortPin12 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x1000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 652 - PortConfigSet_0_PortGroup60_PortPin13 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x2000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 653 - PortConfigSet_0_PortGroup60_PortPin14 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x4000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 654 - PortConfigSet_0_PortGroup60_PortPin15 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0002U,

    /* usPortLoc */
    0x0003U,

    /* usBitLoc */
    0x8000U,

    /* usModeAvailable */
    0x0009U,

    /* usModeDirIn */
    0x0009U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 655 - PortConfigSet_0_PortGroupJtag0_PortPin0 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0000U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0001U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 656 - PortConfigSet_0_PortGroupJtag0_PortPin1 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0000U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0002U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0001U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 657 - PortConfigSet_0_PortGroupJtag0_PortPin2 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0000U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0004U,

    /* usModeAvailable */
    0x0001U,

    /* usModeDirIn */
    0x0001U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0001U
  },
  /* Index: 658 - PortConfigSet_0_PortGroupJtag0_PortPin3 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0000U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0008U,

    /* usModeAvailable */
    0x0000U,

    /* usModeDirIn */
    0x0000U,

    /* usModeDirOut */
    0x0000U,

    /* ucPortPinCoreIndex */
    0x0003U
  },
  /* Index: 659 - PortConfigSet_0_PortGroupJtag0_PortPin5 */
  {
    /* usChangeable */
    0x0000U,

    /* usPortType */
    0x0000U,

    /* usPortLoc */
    0x0000U,

    /* usBitLoc */
    0x0020U,

    /* usModeAvailable */
    0xEAFFU,

    /* usModeDirIn */
    0x8AAEU,

    /* usModeDirOut */
    0xE2FFU,

    /* ucPortPinCoreIndex */
    0x0003U
  }
};

/* Array of structures for Port DNF Config */
CONST(Port_DNF_Init, PORT_CONFIG_DATA) Port_GblDNFConfig =                                                              /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* Index: 0 - ucDNFP01_CTL_Init */
  {
    /* Index: 0 - PortFilterRLIN3 */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 1 - PortFilterRSCAN */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 2 - PortFilterFLXA */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 3 - PortFilterRSENT */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 4 - PortFilterRSENT1 */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 5 - PortFilterRSENT2 */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 6 - PortFilterRSENT3 */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 7 - PortFilterPSI5 */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 8 - PortFilterTAPA */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 9 - Reserve */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 10 - IRQ_0 */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 11 - IRQ_1 */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 12 - IRQ_2 */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 13 - IRQ_3 */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 14 - IRQ_4 */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 15 - IRQ_5 */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 16 - Reserve */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 17 - Reserve */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 18 - PortFilterTAUJ2 */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 19 - Reserve */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 20 - PortFilterESR0IRQ */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 21 - PortFilterESR0NMI */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    },
    /* Index: 22 - PortFilterESR1NMI */
    {
      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U,

      0x00U
    }
  },
  /* Index: 1 - ucDNFP02_CTL_Init */
  {
    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U
  },
  /* Index: 2 - ucDNFP03_CTL_Init */
  {
    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U,

    0x00U
  },
  /* Index: 3 - usDNFP02_EDC_Init */
  {
    /* Index: 0 - PortFilterRLIN3 */
    {
      0x0000U
    },
    /* Index: 1 - PortFilterRSCAN */
    {
      0x0000U
    },
    /* Index: 2 - PortFilterFLXA */
    {
      0x0000U
    },
    /* Index: 3 - PortFilterRSENT */
    {
      0x0000U
    },
    /* Index: 4 - PortFilterRSENT1 */
    {
      0x0000U
    },
    /* Index: 5 - PortFilterPSI5 */
    {
      0x0000U
    },
    /* Index: 6 - PortFilterTAPA */
    {
      0x0000U
    },
    /* Index: 7 - PortFilterADCK0 */
    {
      0x0000U
    },
    /* Index: 8 - PortFilterADCK1 */
    {
      0x0000U
    },
    /* Index: 9 - PortFilterADCK2 */
    {
      0x0000U
    },
    /* Index: 10 - PortFilterADCK3 */
    {
      0x0000U
    },
    /* Index: 11 - Reserve */
    {
      0x0000U
    },
    /* Index: 12 - PortFilterRHSB */
    {
      0x0000U
    },
    /* Index: 13 - PortFilterENCA */
    {
      0x0000U
    },
    /* Index: 14 - PortFilterTAUD0 */
    {
      0x0000U
    },
    /* Index: 15 - PortFilterTAUD1 */
    {
      0x0000U
    },
    /* Index: 16 - PortFilterTAUD2 */
    {
      0x0000U
    },
    /* Index: 17 - PortFilterTAUD3 */
    {
      0x0000U
    },
    /* Index: 18 - PortFilterTSG3 */
    {
      0x0000U
    },
    /* Index: 19 - PortFilterECM */
    {
      0x0000U
    },
    /* Index: 20 - Reserve */
    {
      0x0000U
    },
    /* Index: 21 - Reserve */
    {
      0x0000U
    },
    /* Index: 22 - PortFilterTAUJ2 */
    {
      0x0000U
    },
    /* Index: 23 - Reserve */
    {
      0x0000U
    },
    /* Index: 24 - PortFilterPIC */
    {
      0x0000U
    },
    /* Index: 25 - Reserve */
    {
      0x0000U
    },
    /* Index: 26 - PortFilterOSPI0 */
    {
      0x0000U
    },
    /* Index: 27 - PortFilterESR0IRQ */
    {
      0x0000U
    },
    /* Index: 28 - PortFilterESR0NMI */
    {
      0x0000U
    },
    /* Index: 29 - PortFilterESR1NMI */
    {
      0x0000U
    }
  },
  /* Index: 4 - usDNFP03_EDC_Init */
  {
    /* Index: 0 - DNFP020CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 1 - DNFP021CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 2 - DNFP022CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 3 - DNFP023CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 4 - DNFP024CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 5 - DNFP025CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 6 - DNFP026CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 7 - DNFP027CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 8 - DNFP028CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 9 - DNFP029CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 10 - DNFP0210CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 11 - DNFP0211CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 12 - DNFP0212CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 13 - DNFP0213CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 14 - DNFP0214CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 15 - DNFP0215CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 16 - DNFP0216CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 17 - DNFP0217CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 18 - DNFP0218CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 19 - DNFP0219CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 20 - DNFP0220CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 21 - DNFP0221CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 22 - DNFP0222CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 23 - DNFP0223CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 24 - DNFP0224CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 25 - DNFP0225CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 26 - DNFP0226CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 27 - DNFP0227CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 28 - DNFP0228CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 29 - DNFP0229CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 30 - DNFP0230CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 31 - DNFP0231CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 32 - DNFP0232CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 33 - DNFP0233CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 34 - DNFP0234CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 35 - DNFP0235CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 36 - DNFP0236CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 37 - DNFP0237CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 38 - DNFP0238CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 39 - DNFP0239CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    },
    /* Index: 40 - DNFP0240CTL */
    {
      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U,

      0x0000U
    }
  },
  /* ucDNFP02_CTL_Init2 */
  0x00U,
  /* Index: 5 - usDNFP02_EDC_Init2 */
  {
    0x0000U
  }
};

/* Array of structures for Port Config */
CONST(Port_Reg_Init, PORT_CONFIG_DATA) Port_GaaPortConfig[] =                                                           /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* Index: 0 - PortGroup0 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFF55U,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0055U,

      /* PD */
      0x00AAU,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0024U,

      /* PEIODC */
      0x0004U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x00B6U,

      /* PODCE */
      0x0024U,

      /* PDSC */
      0x00AAU,

      /* PUCC */
      0x00CCU,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x00AAU,

      /* PSFTSAE */
      0x0080U,

      /* PSFTSE */
      0x0020U,

      /* PSFTS */
      0x0088U,

      /* PSFC */
      0x00AAU
    }
  },
  /* Index: 1 - PortGroup1 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 2 - PortGroup2 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0080U,

      /* PM */
      0xFF43U,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0001U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0080U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0117U,

      /* PD */
      0x0068U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0024U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x01F2U,

      /* PODCE */
      0x0120U,

      /* PDSC */
      0x00AAU,

      /* PUCC */
      0x004CU,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x00E8U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x00A0U,

      /* PSFTS */
      0x0088U,

      /* PSFC */
      0x0068U
    }
  },
  /* Index: 3 - PortGroup3 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 4 - PortGroup10 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0080U,

      /* PM */
      0xFF43U,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0001U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0080U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0117U,

      /* PD */
      0x0068U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0024U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x01F2U,

      /* PODCE */
      0x0120U,

      /* PDSC */
      0x00EAU,

      /* PUCC */
      0x000CU,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x00E8U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0020U,

      /* PSFTS */
      0x00CAU,

      /* PSFC */
      0x0068U
    }
  },
  /* Index: 5 - PortGroup11 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFD55U,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0555U,

      /* PD */
      0x02AAU,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0124U,

      /* PEIODC */
      0x0080U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x05B6U,

      /* PODCE */
      0x0124U,

      /* PDSC */
      0x02AAU,

      /* PUCC */
      0x04CCU,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x02AAU,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x00A0U,

      /* PSFTS */
      0x0088U,

      /* PSFC */
      0x02AAU
    }
  },
  /* Index: 6 - PortGroup12 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFDU,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0001U,

      /* PD */
      0x0002U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0002U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0002U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0002U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0002U
    }
  },
  /* Index: 7 - PortGroup13 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0001U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0003U,

      /* PD */
      0x0008U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0008U
    }
  },
  /* Index: 8 - PortGroup14 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xC7FFU,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x3800U,

      /* PUCC */
      0x3800U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 9 - PortGroup15 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0040U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 10 - PortGroup16 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 11 - PortGroup20 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFF77U,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0041U,

      /* PD */
      0x0088U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0080U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0088U,

      /* PUCC */
      0x00C8U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0088U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0080U,

      /* PSFTS */
      0x0088U,

      /* PSFC */
      0x0088U
    }
  },
  /* Index: 12 - PortGroup21 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFD7U,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0014U,

      /* PD */
      0x0028U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0024U,

      /* PEIODC */
      0x0004U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0034U,

      /* PODCE */
      0x0024U,

      /* PDSC */
      0x0028U,

      /* PUCC */
      0x000CU,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0028U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0020U,

      /* PSFTS */
      0x0008U,

      /* PSFC */
      0x0028U
    }
  },
  /* Index: 13 - PortGroup22 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFF5U,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0015U,

      /* PD */
      0x000AU,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0008U,

      /* PEIODC */
      0x0001U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0016U,

      /* PODCE */
      0x0004U,

      /* PDSC */
      0x000AU,

      /* PUCC */
      0x000CU,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x000AU,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0008U,

      /* PSFC */
      0x000AU
    }
  },
  /* Index: 14 - PortGroup23 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFF75U,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0055U,

      /* PD */
      0x008AU,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0004U,

      /* PEIODC */
      0x0008U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0096U,

      /* PODCE */
      0x0004U,

      /* PDSC */
      0x008AU,

      /* PUCC */
      0x00CCU,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x008AU,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0080U,

      /* PSFTS */
      0x0088U,

      /* PSFC */
      0x008AU
    }
  },
  /* Index: 15 - PortGroup24 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 16 - PortGroup25 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 17 - PortGroup26 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 18 - PortGroup27 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 19 - PortGroup28 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 20 - PortGroup30 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 21 - PortGroup31 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 22 - PortGroup32 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0020U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 23 - PortGroup33 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 24 - PortGroup34 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 25 - PortGroup36 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 26 - PortGroup37 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 27 - PortGroup38 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 28 - PortGroup39 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 29 - PortGroup40 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0000U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* PEIODC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* PSFTSAE */
      0x0000U,

      /* PSFTSE */
      0x0000U,

      /* PSFTS */
      0x0000U,

      /* PSFC */
      0x0000U
    }
  },
  /* Index: 30 - PortGroup41 */
  {
    /* Index: 0 - Register Value */
    {
      /* Reserve */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 31 - PortGroup42 */
  {
    /* Index: 0 - Register Value */
    {
      /* Reserve */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 32 - PortGroup43 */
  {
    /* Index: 0 - Register Value */
    {
      /* Reserve */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 33 - PortGroup44 */
  {
    /* Index: 0 - Register Value */
    {
      /* Reserve */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 34 - PortGroup45 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 35 - PortGroup46 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 36 - PortGroup47 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 37 - PortGroup48 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 38 - PortGroup49 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 39 - PortGroup50 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 40 - PortGroup51 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 41 - PortGroup52 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 42 - PortGroup53 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 43 - PortGroup54 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 44 - PortGroup55 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 45 - PortGroup56 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 46 - PortGroup57 */
  {
    /* Index: 0 - Register Value */
    {
      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 47 - PortGroup58 */
  {
    /* Index: 0 - Register Value */
    {
      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 48 - PortGroup59 */
  {
    /* Index: 0 - Register Value */
    {
      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 49 - PortGroup60 */
  {
    /* Index: 0 - Register Value */
    {
      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  }
};


/* Array of structures for Port JTAG Config */
CONST(Port_Reg_Init, PORT_CONFIG_DATA) Port_GaaJPortConfig[] =                                                          /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* Index: 0 - PortGroupJtag0 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* PIPC */
      0x0000U,

      /* PIBC */
      0x0005U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* PFCAE */
      0x0000U,

      /* PFCEAE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PU */
      0x0005U,

      /* PD */
      0x0000U,

      /* PIS */
      0x0000U,

      /* PISA */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PODC */
      0x0000U,

      /* PODCE */
      0x0000U,

      /* PDSC */
      0x0000U,

      /* PUCC */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  }
};


/* Array of structures for Port Analog Config */
CONST(Port_Reg_Init, PORT_CONFIG_DATA) Port_GaaAPortConfig[] =                                                          /* PRQA S 1504, 3408 # JV-01, JV-01 */
{
  /* Index: 0 - PortGroup57 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 1 - PortGroup58 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 2 - PortGroup59 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  },
  /* Index: 3 - PortGroup60 */
  {
    /* Index: 0 - Register Value */
    {
      /* PMC */
      0x0000U,

      /* PM */
      0xFFFFU,

      /* Reserve */
      0x0000U,

      /* PIBC */
      0x0000U,

      /* PFC */
      0x0000U,

      /* PFCE */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* PINV */
      0x0000U,

      /* PBDC */
      0x0000U,

      /* P */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U,

      /* Reserve */
      0x0000U
    }
  }
};


/* The following structure indicates the starting point of database */
CONST(Port_ConfigType, PORT_CONFIG_DATA) Port_GaaConfiguration[] =                                                      /* PRQA S 1502 # JV-01 */
{
  /* Index: 0 - Global Data */
  {
    /* ulStartOfDbToc */
    0x0EDF0220UL,

    /* ulUsePinNumber */
    0x00000294UL,

    /* ucPortKernelCoreId */
    0U,

    /* pPortPinConfig */
    &Port_GaaPinConfig[0],

    /* pPortDNFConfig */
    &Port_GblDNFConfig,

    /* Index: 5 - pPortConfig */
    {
      /* JPort Configration */
      &Port_GaaJPortConfig[0],

      /* Port_Configration */
      &Port_GaaPortConfig[0],

      /* APort_Configration */
      &Port_GaaAPortConfig[0]
    }
  }
};

#define PORT_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */


/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

