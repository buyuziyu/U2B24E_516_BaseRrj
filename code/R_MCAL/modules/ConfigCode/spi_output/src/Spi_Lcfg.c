/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_Lcfg.c                                                                                          */
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
/* TOOL VERSION:  SpiU2Bx-E.dll version: 2.5.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\spi\generator\U2B24-E\R2211_spi_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_spi.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_spi.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_spi.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:50:04
 */


/***********************************************************************************************************************
**                      Instance Index                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Spi.h"

#include "Spi_Ram.h"

#include "Spi_MSPI_LLDriver.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/**********************************************************************************************************************/
/* Message (2:0306)    : [I] Cast between a pointer to object and an integral type.                                   */
/* Rule                : MISRA-C:2012 Rule 11.4, CERT-C:1.2.4 CERTCMM INT36, CWE Rule CWE-398, CWE-569, CWE-738       */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule 20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
/* AUTOSAR specification version information */
#define SPI_LCFG_C_AR_RELEASE_MAJOR_VERSION                                     4U
#define SPI_LCFG_C_AR_RELEASE_MINOR_VERSION                                     8U
#define SPI_LCFG_C_AR_RELEASE_REVISION_VERSION                                  0U
/* File version information */
#define SPI_LCFG_C_SW_MAJOR_VERSION                                             2U
#define SPI_LCFG_C_SW_MINOR_VERSION                                             5U

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/
#if (SPI_LTTYPES_AR_RELEASE_MAJOR_VERSION != SPI_LCFG_C_AR_RELEASE_MAJOR_VERSION)
  #error "Spi_Lcfg.c : Mismatch in Release Major Version"
#endif

#if (SPI_LTTYPES_AR_RELEASE_MINOR_VERSION != SPI_LCFG_C_AR_RELEASE_MINOR_VERSION)
  #error "Spi_Lcfg.c : Mismatch in Release Minor Version"
#endif

#if (SPI_LTTYPES_AR_RELEASE_REVISION_VERSION != SPI_LCFG_C_AR_RELEASE_REVISION_VERSION)
  #error "Spi_Lcfg.c : Mismatch in Release Revision Version"
#endif

#if (SPI_LTTYPES_SW_MAJOR_VERSION != SPI_LCFG_C_SW_MAJOR_VERSION)
  #error "Spi_Lcfg.c : Mismatch in Software Major Version"
#endif

#if (SPI_LTTYPES_SW_MINOR_VERSION != SPI_LCFG_C_SW_MINOR_VERSION)
  #error "Spi_Lcfg.c : Mismatch in Software Minor Version"
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/
#define SPI_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Spi_MemMap.h"


/* MSPI Register set information */
CONST(Spi_MSPIRegisterSetType, SPI_CONFIG_DATA) Spi_GaaMSPIRegs[] =
{
  /* Index: 0 - MSPI0 */
  {
    /* pRegs */
    (Spi_MSPIRegType*)0xFFC76000UL,                                                                                     /* PRQA S 0306 # JV-01 */

    /* pIntfRegs */
    (Spi_MSPIIntfRegType*)0xFFC75740UL,                                                                                 /* PRQA S 0306 # JV-01 */

    /* pTrgGenRegs */
    (Spi_MSPITrgGenRegType*)0xFFC75D00UL,                                                                               /* PRQA S 0306 # JV-01 */

    /* pICTX */
    (uint16*)0xFFF80480UL,                                                                                              /* PRQA S 0306 # JV-01 */

    /* pICRX */
    (uint16*)0xFFF80482UL,                                                                                              /* PRQA S 0306 # JV-01 */

    /* pICFE */
    (uint16*)0xFFF80484UL,                                                                                              /* PRQA S 0306 # JV-01 */

    /* pICERR */
    (uint16*)0xFFF80486UL,                                                                                              /* PRQA S 0306 # JV-01 */

    /* ucPhyChannelMax */
    0x0CU
  },
  /* Index: 1 - MSPI1 */
  {
    /* pRegs */
    (Spi_MSPIRegType*)0xFFD5E000UL,                                                                                     /* PRQA S 0306 # JV-01 */

    /* pIntfRegs */
    (Spi_MSPIIntfRegType*)0xFFD68740UL,                                                                                 /* PRQA S 0306 # JV-01 */

    /* pTrgGenRegs */
    (Spi_MSPITrgGenRegType*)0xFFC75D00UL,                                                                               /* PRQA S 0306 # JV-01 */

    /* pICTX */
    (uint16*)0xFFF80488UL,                                                                                              /* PRQA S 0306 # JV-01 */

    /* pICRX */
    (uint16*)0xFFF8048AUL,                                                                                              /* PRQA S 0306 # JV-01 */

    /* pICFE */
    (uint16*)0xFFF8048CUL,                                                                                              /* PRQA S 0306 # JV-01 */

    /* pICERR */
    (uint16*)0xFFF8048EUL,                                                                                              /* PRQA S 0306 # JV-01 */

    /* ucPhyChannelMax */
    0x0CU
  }
};

#define SPI_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */



/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

