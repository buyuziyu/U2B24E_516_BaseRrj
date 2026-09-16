/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Dio_Lcfg.c                                                                                          */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2023, 2024 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains link time parameters                                                                            */
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
/* TOOL VERSION:  DioU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\dio\generator\U2B24-E\R2211_dio_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_dio.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_dio.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:49:23
 */


/***********************************************************************************************************************
**                      Instance Index                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Dio.h"

#include "Dio_LTTypes.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/**********************************************************************************************************************/
/* Message (5:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : MISRA C:2012 Rule 11.4, CERT-C:1.2.4 CERTCCM INT36                                           */
/* JV-01 Justification : This macro is used to write or read values from hardware addresses.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1533)    : The object 'name' is only referenced by function 'func'.                                     */
/* Rule                : MISRA C:2012 Rule-8.9                                                                        */
/* JV-01 Justification : This is accepted, due to the object is defined in seperated cource C file to                 */
/*                       followed coding rule                                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : #include directives should only be preceded by preprocessor directives or comments           */
/* Rule                : MISRA C:2012 Rule 20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
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
/* AUTOSAR release version information */
#define DIO_LCFG_C_AR_RELEASE_MAJOR_VERSION                                     4U
#define DIO_LCFG_C_AR_RELEASE_MINOR_VERSION                                     8U
#define DIO_LCFG_C_AR_RELEASE_REVISION_VERSION                                  0U
/* File version information */
#define DIO_LCFG_C_SW_MAJOR_VERSION                                             2U
#define DIO_LCFG_C_SW_MINOR_VERSION                                             4U

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/
#if (DIO_LTTYPES_AR_RELEASE_MAJOR_VERSION != DIO_LCFG_C_AR_RELEASE_MAJOR_VERSION)
    #error "Dio_Lcfg.c : Mismatch in Release Major Version"
#endif

#if (DIO_LTTYPES_AR_RELEASE_MINOR_VERSION != DIO_LCFG_C_AR_RELEASE_MINOR_VERSION)
    #error "Dio_Lcfg.c : Mismatch in Release Minor Version"
#endif

#if (DIO_LTTYPES_AR_RELEASE_REVISION_VERSION != DIO_LCFG_C_AR_RELEASE_REVISION_VERSION)
    #error "Dio_Lcfg.c : Mismatch in Release Revision Version"
#endif

#if (DIO_LTTYPES_SW_MAJOR_VERSION != DIO_LCFG_C_SW_MAJOR_VERSION)
    #error "Dio_Lcfg.c : Mismatch in Software Major Version"
#endif

#if (DIO_LTTYPES_SW_MINOR_VERSION != DIO_LCFG_C_SW_MINOR_VERSION)
    #error "Dio_Lcfg.c : Mismatch in Software Minor Version"
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/
#define DIO_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Dio_MemMap.h"


/* Structure of DIO Port Group Configuration */
CONST(Dio_PortGroupType, DIO_CONFIG_DATA) Dio_GaaPortGroup[] =
{
  /* Index: 0 - DioPort_P14 */
  {
    /* pPortAddress */
    (P2VAR(volatile uint32, TYPEDEF, REGSPACE))0xFFD90384UL,                                                            /* PRQA S 0303 # JV-01 */

    /* ucPortType */
    0x02U,

    /* ulModeMask */
    0xFFFF0000UL,

    /* ulPortGroupNum */
    14UL,

    /* ucGroupCoreIndex */
    0x01U
  }
};

/* Data Structure of DIO Port Channel Configuration */
CONST(Dio_PortChannelType, DIO_CONFIG_DATA) Dio_GaaPortChannel[] =
{
  /* Index: 0 - DioChannel_P14_11_LED9 */
  {
    /* usMask */
    0x0200U,

    /* ucPortIndex */
    0x00U,

    /* ucChannelCoreIndex */
    0x01U
  },
  /* Index: 1 - DioChannel_P14_12_LED10 */
  {
    /* usMask */
    0x1000U,

    /* ucPortIndex */
    0x00U,

    /* ucChannelCoreIndex */
    0x01U
  },
  /* Index: 2 - DioChannel_P14_13_LED11 */
  {
    /* usMask */
    0x2000U,

    /* ucPortIndex */
    0x00U,

    /* ucChannelCoreIndex */
    0x01U
  }
};

/* Structure of DIO PWE Data */
CONST(uint32, DIO_CONFIG_DATA) DIO_GaaPweData[] =                                                                       /* PRQA S 1533 # JV-01 */
{
  /* Index:0 */
  0x00000000UL,
  /* Index:1 */
  0x00000000UL,
  /* Index:2 */
  0x00000000UL,
  /* Index:3 */
  0x00000000UL,
  /* Index:4 */
  0x00000000UL,
  /* Index:5 */
  0x00000000UL,
  /* Index:6 */
  0x00000000UL,
  /* Index:7 */
  0x00000000UL,
  /* Index:8 */
  0x00000000UL,
  /* Index:9 */
  0x00000000UL,
  /* Index:10 */
  0x00000000UL,
  /* Index:11 */
  0x00000000UL,
  /* Index:12 */
  0x00000000UL,
  /* Index:13 */
  0x00000080UL,
  /* Index:14 */
  0x00000100UL,
  /* Index:15 */
  0x00000000UL,
  /* Index:16 */
  0x00000400UL,
  /* Index:17 */
  0x00000000UL,
  /* Index:18 */
  0x00000000UL,
  /* Index:19 */
  0x00000000UL,
  /* Index:20 */
  0x00000000UL,
  /* Index:21 */
  0x00001000UL,
  /* Index:22 */
  0x00002000UL,
  /* Index:23 */
  0x00000000UL,
  /* Index:24 */
  0x00000000UL,
  /* Index:25 */
  0x00000000UL,
  /* Index:26 */
  0x00000000UL,
  /* Index:27 */
  0x00040000UL,
  /* Index:28 */
  0x00080000UL,
  /* Index:29 */
  0x00000000UL,
  /* Index:30 */
  0x00000000UL,
  /* Index:31 */
  0x00000000UL,
  /* Index:32 */
  0x00000000UL,
  /* Index:33 */
  0x00000000UL,
  /* Index:34 */
  0x00000000UL,
  /* Index:35 */
  0x00000000UL,
  /* Index:36 */
  0x00000000UL,
  /* Index:37 */
  0x00000000UL,
  /* Index:38 */
  0x00000000UL,
  /* Index:39 */
  0x00000000UL,
  /* Index:40 */
  0x00000000UL,
  /* Index:41 */
  0x00000000UL,
  /* Index:42 */
  0x00000000UL,
  /* Index:43 */
  0x00000000UL,
  /* Index:44 */
  0x00000000UL,
  /* Index:45 */
  0x00000000UL,
  /* Index:46 */
  0x00000000UL,
  /* Index:47 */
  0x00000000UL,
  /* Index:48 */
  0x00000000UL,
  /* Index:49 */
  0x00000000UL,
  /* Index:50 */
  0x00000000UL,
  /* Index:51 */
  0x00000000UL,
  /* Index:52 */
  0x00000000UL,
  /* Index:53 */
  0x00000000UL,
  /* Index:54 */
  0x00000000UL,
  /* Index:55 */
  0x00000000UL,
  /* Index:56 */
  0x00000000UL,
  /* Index:57 */
  0x00000000UL,
  /* Index:58 */
  0x00000000UL,
  /* Index:59 */
  0x00000000UL,
  /* Index:60 */
  0x00000000UL
};

#define DIO_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Dio_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */



/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

