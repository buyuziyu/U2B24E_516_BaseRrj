/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_PBcfg.c                                                                                         */
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
#include "Spi_sDMAC_LLDriver.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule 20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : MISRA-C:2012 Rule 11.4, CERT-C:1.2.4 CERTCMM INT36, CWE Rule CWE-398, CWE-569                */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (5:0488)    : Performing Pointer arithmetic.                                                               */
/* Rule                : MISRA-C:2012 Rule 18.4, CERT-C:1.2.4 CERTCMM EXP08 , CWE Rule CWE-188, CWE-398, CWE-569      */
/* JV-01 Justification : This addresses pointed by the pointers needs to be incremented after each cycle.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : [I] Cast between a pointer to object and an integral type.                                   */
/* Rule                : MISRA-C:2012 Rule 11.4, CERT-C:1.2.4 CERTCMM INT36, CWE Rule CWE-398, CWE-569, CWE-738       */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERT-C:1.2.4 CERTCCM EXP11, EXP39, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465,     */
/*                       CWE-569, CWE-737                                                                             */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped.          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0489)    : Increment or decrement operation performed on pointer                                        */
/* Rule                : CWE-188, CWE-398, CWE-468, CWE-465, CWE-569                                                  */
/* JV-01 Justification : To access these pointers in optimized way in this function                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0778)    : Identifier matches other identifier(s) (e.g. '%s') in first 31 characters - program does     */
/*                       not conform strictly to ISO:C90.                                                             */
/* Rule                : CERTCCM DCL23, DCL40, MISRA C:2012 Dir-1.1, CWE Rule CWE-736                                 */
/* JV-01 Justification : Compiler will distinguish numerous characters, so this is accepted.                          */
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
/* AUTOSAR specification version information */
#define SPI_PBCFG_C_AR_RELEASE_MAJOR_VERSION                                    4U
#define SPI_PBCFG_C_AR_RELEASE_MINOR_VERSION                                    8U
#define SPI_PBCFG_C_AR_RELEASE_REVISION_VERSION                                 0U
/* File version information */
#define SPI_PBCFG_C_SW_MAJOR_VERSION                                            2U
#define SPI_PBCFG_C_SW_MINOR_VERSION                                            5U

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/
#if (SPI_PBTYPES_AR_RELEASE_MAJOR_VERSION != SPI_PBCFG_C_AR_RELEASE_MAJOR_VERSION)
  #error "Spi_PBcfg.c : Mismatch in Release Major Version"
#endif

#if (SPI_PBTYPES_AR_RELEASE_MINOR_VERSION != SPI_PBCFG_C_AR_RELEASE_MINOR_VERSION)
  #error "Spi_PBcfg.c : Mismatch in Release Minor Version"
#endif

#if (SPI_PBTYPES_AR_RELEASE_REVISION_VERSION != SPI_PBCFG_C_AR_RELEASE_REVISION_VERSION)
  #error "Spi_PBcfg.c : Mismatch in Release Revision Version"
#endif

#if (SPI_PBTYPES_SW_MAJOR_VERSION != SPI_PBCFG_C_SW_MAJOR_VERSION)
  #error "Spi_PBcfg.c : Mismatch in Software Major Version"
#endif

#if (SPI_PBTYPES_SW_MINOR_VERSION != SPI_PBCFG_C_SW_MINOR_VERSION)
  #error "Spi_PBcfg.c : Mismatch in Software Minor Version"
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/
#define SPI_START_SEC_CONFIG_DATA_POSTBUILD_8
#include "Spi_MemMap.h"


/* This array map hardware unit MSPI to hardware unit info array */
STATIC CONST(uint8, SPI_CONFIG_DATA) Spi_GaaMSPIToHWUnit[] =
{
  /* Index: 0 */
  0x00U, 0x01U
};

#define SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define SPI_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Array for hardware unit information */
STATIC CONST(Spi_HWUnitInfoType, SPI_CONFIG_DATA) Spi_GaaHWUnitInfo[] =
{
  /* Index: 0 - MSPI0 */
  {
    /* ucCoreMask */
    0x02U,

    /* ucMacroIndex */
    SPI_MACRO_MSPI,

    /* ucPhyUnitIndex */
    0x00U
  },
  /* Index: 1 - MSPI1 */
  {
    /* ucCoreMask */
    0x01U,

    /* ucMacroIndex */
    SPI_MACRO_MSPI,

    /* ucPhyUnitIndex */
    0x01U
  }
};

/* This array contains list of JobIds that used in sequence */
STATIC CONST(Spi_JobType, SPI_CONFIG_DATA) Spi_GaaJobList_0_1[] =
{
  /* Index: 0 - SpiSequence */
  0x00U
};

/* This array contains list of JobIds that used in sequence */
STATIC CONST(Spi_JobType, SPI_CONFIG_DATA) Spi_GaaJobList_1_2[] =
{
  /* Index: 1 - SpiSequence_001 */
  0x01U
};

/* This array contains list of JobIds that used in sequence */
STATIC CONST(Spi_JobType, SPI_CONFIG_DATA) Spi_GaaJobList_0_0[] =
{
  /* Index: 0 - SpiSequence */
  0x00U
};

/* This array contains list of JobIds that used in sequence */
STATIC CONST(Spi_JobType, SPI_CONFIG_DATA) Spi_GaaJobList_1_0[] =
{
  /* Index: 1 - SpiSequence_001 */
  0x01U
};

/* This array contains list of ChannelIds that used in job */
STATIC CONST(Spi_ChannelType, SPI_CONFIG_DATA) Spi_GaaChannelList0[] =
{
  /* Index: 0 - SpiJob */
  0x00U
};

/* This array contains list of ChannelIds that used in job */
STATIC CONST(Spi_ChannelType, SPI_CONFIG_DATA) Spi_GaaChannelList1[] =
{
  /* Index: 1 - SpiJob_001 */
  0x01U
};

/* This array contains device configuration for MSPI */
STATIC CONST(Spi_MSPIDeviceConfigType, SPI_CONFIG_DATA) Spi_GaaMSPIDeviceConfig[] =
{
  /* Index: 0 - SpiJob */
  {
    /* ucPhyChannelIndex */
    0x00U,

    /* enMemoryMode */
    SPI_MEMORYMODE_DIRECT,

    /* ulMSPICTL1 */
    0x00000000UL,

    /* ucMSPICTL2 */
    0x00U,

    /* ulMSPICFG0 */
    0x30010003UL,

    /* ulMSPICFG1 */
    0x01030000UL,

    /* usMSPICFG3 */
    0x0301U,

    /* ulMSPICFG4 */
    0x00000000UL,

    /* usMSPISEUP */
    0x0001U,

    /* usMSPIHOLD */
    0x0001U,

    /* usMSPIIDLE */
    0x0001U,

    /* usMSPIINDA */
    0x0000U,

    /* usMSPIRASTAD */
    0x0000U
  },
  /* Index: 1 - SpiJob_001 */
  {
    /* ucPhyChannelIndex */
    0x00U,

    /* enMemoryMode */
    SPI_MEMORYMODE_DIRECT,

    /* ulMSPICTL1 */
    0xA0000000UL,

    /* ucMSPICTL2 */
    0x00U,

    /* ulMSPICFG0 */
    0x30700003UL,

    /* ulMSPICFG1 */
    0x01000000UL,

    /* usMSPICFG3 */
    0x0001U,

    /* ulMSPICFG4 */
    0x00000000UL,

    /* usMSPISEUP */
    0x0001U,

    /* usMSPIHOLD */
    0x0001U,

    /* usMSPIIDLE */
    0x0001U,

    /* usMSPIINDA */
    0x0000U,

    /* usMSPIRASTAD */
    0x0000U
  }
};

/* HW-dependent configuration */
STATIC CONST(Spi_HwConfigType, SPI_CONFIG_DATA) Spi_GaaHwConfig[] =
{
  /* Index: 0 - MSPI */
  {
    /* pHwDepFunc */
    &Spi_GstMSPIFunc,

    /* pPhyToHWUnit */
    &Spi_GaaMSPIToHWUnit[0]
  }
};

/* This array contains configuration details for Channels */
STATIC CONST(Spi_ChannelConfigType, SPI_CONFIG_DATA) Spi_GaaChannelConfig[] =
{
  /* Index: 0 - SpiChannel */
  {
    /* ucCoreMask */
    0x02U,

    /* ucDataWidth */
    0x10U,

    /* ucByteSize */
    0x02U,

    /* enTransferStart */
    SPI_TRANSFER_START_MSB,

    /* ulDefaultData */
    0x00000000UL,

    /* enChannelBufferType */
    SPI_BUFFER_TYPE_EB,

    /* usNoOfBuffers */
    0x0003U,

    /* pTxBuffer */
    NULL_PTR,

    /* pRxBuffer */
    NULL_PTR,

    /* pEBData */
    &Spi_GaaEBData[0]
  },
  /* Index: 1 - SpiChannel_001 */
  {
    /* ucCoreMask */
    0x01U,

    /* ucDataWidth */
    0x10U,

    /* ucByteSize */
    0x02U,

    /* enTransferStart */
    SPI_TRANSFER_START_MSB,

    /* ulDefaultData */
    0x00000000UL,

    /* enChannelBufferType */
    SPI_BUFFER_TYPE_IB,

    /* usNoOfBuffers */
    0x0002U,

    /* pTxBuffer */
    (volatile Spi_DataBufferType*)Spi_GaaChannelBuffer + 0U,                                                            /* PRQA S 0303, 0751, 0488, 0489 # JV-01, JV-01, JV-01, JV-01 */

    /* pRxBuffer */
    (volatile Spi_DataBufferType*)Spi_GaaChannelBuffer + 4U,                                                            /* PRQA S 0303, 0751, 0488, 0489 # JV-01, JV-01, JV-01, JV-01 */

    /* pEBData */
    NULL_PTR
  }
};

/* This array contains configuration details for Jobs */
STATIC CONST(Spi_JobConfigType, SPI_CONFIG_DATA) Spi_GaaJobConfig[] =
{
  /* Index: 0 - SpiJob */
  {
    /* ucCoreMask */
    0x02U,

    /* ucNoOfChannels */
    0x01U,

    /* usCSInfo */
    0x0001U,

    /* pChannelList */
    &Spi_GaaChannelList0[0],

    /* pJobEndNotification */
    NULL_PTR,

    /* ucJobPriority */
    0x03U,

    /* ucHWUnitIndex */
    0x00U,

    /* enCSType */
    SPI_PERIPHERAL_ENGINE_CS,

    /* blChannelPropertySame */
    SPI_TRUE,

    /* pHWDevConfig */
    &Spi_GaaMSPIDeviceConfig[0]
  },
  /* Index: 1 - SpiJob_001 */
  {
    /* ucCoreMask */
    0x01U,

    /* ucNoOfChannels */
    0x01U,

    /* usCSInfo */
    0x0000U,

    /* pChannelList */
    &Spi_GaaChannelList1[0],

    /* pJobEndNotification */
    NULL_PTR,

    /* ucJobPriority */
    0x03U,

    /* ucHWUnitIndex */
    0x01U,

    /* enCSType */
    SPI_DISABLE_CS,

    /* blChannelPropertySame */
    SPI_TRUE,

    /* pHWDevConfig */
    &Spi_GaaMSPIDeviceConfig[1]
  }
};

/* This array contains configuration details for Sequences */
STATIC CONST(Spi_SeqConfigType, SPI_CONFIG_DATA) Spi_GaaSeqConfig[] =
{
  /* Index: 0 - SpiSequence */
  {
    /* ucCoreMask */
    0x02U,

    /* ulUsingHWUnits */
    0x00000001UL,

    /* pSeqEndNotification */
    NULL_PTR,

    /* pSeqStartNotification */
    NULL_PTR,

    /* blInterruptible */
    SPI_TRUE,

    /* aaJobSharedSequences */
    { 0x00000000UL },

    /* Index: 6 - aaSubSeqs */
    {
      /* Index: 0 - 0 */
      {
        /* ucUsingPriorities */
        0x08U,

        /* usNoOfJobs */
        0x0001U,

        /* pJobList */
        &Spi_GaaJobList_0_0[0]
      },
      /* Index: 1 - MSPI0 */
      {
        /* ucUsingPriorities */
        0x08U,

        /* usNoOfJobs */
        0x0001U,

        /* pJobList */
        &Spi_GaaJobList_0_1[0]
      },
      /* Index: 2 - MSPI1 */
      {
        /* ucUsingPriorities */
        0x00U,

        /* usNoOfJobs */
        0x0000U,

        /* pJobList */
        NULL_PTR
      }
    }
  },
  /* Index: 1 - SpiSequence_001 */
  {
    /* ucCoreMask */
    0x01U,

    /* ulUsingHWUnits */
    0x00000002UL,

    /* pSeqEndNotification */
    NULL_PTR,

    /* pSeqStartNotification */
    NULL_PTR,

    /* blInterruptible */
    SPI_FALSE,

    /* aaJobSharedSequences */
    { 0x00000000UL },

    /* Index: 6 - aaSubSeqs */
    {
      /* Index: 0 - 0 */
      {
        /* ucUsingPriorities */
        0x08U,

        /* usNoOfJobs */
        0x0001U,

        /* pJobList */
        &Spi_GaaJobList_1_0[0]
      },
      /* Index: 1 - MSPI0 */
      {
        /* ucUsingPriorities */
        0x00U,

        /* usNoOfJobs */
        0x0000U,

        /* pJobList */
        NULL_PTR
      },
      /* Index: 2 - MSPI1 */
      {
        /* ucUsingPriorities */
        0x08U,

        /* usNoOfJobs */
        0x0001U,

        /* pJobList */
        &Spi_GaaJobList_1_2[0]
      }
    }
  }
};

/* Structure for SPI Init configuration */
CONST(Spi_ConfigType, SPI_CONFIG_DATA) Spi_GaaConfiguration[] =                                                         /* PRQA S 1502 # JV-01 */
{
  /* Index: 0 - SpiDriver */
  {
    /* ulStartOfDbToc */
    0x0ED4C228UL,

    /* ucNoOfHWUnits */
    0x02U,

    /* ucNoOfQueues */
    0x03U,

    /* ucNoOfChannels */
    0x02U,

    /* usNoOfJobs */
    0x0002U,

    /* ucNoOfSequences */
    0x02U,

    /* ucKernelCoreId */
    0,

    /* pHWUnitInfo */
    &Spi_GaaHWUnitInfo[0],

    /* pChannelConfig */
    &Spi_GaaChannelConfig[0],

    /* pJobConfig */
    &Spi_GaaJobConfig[0],

    /* pSequenceConfig */
    &Spi_GaaSeqConfig[0],

    /* ulTimeoutCount */
    0x04C4B400UL,

    /* pHwConfig */
    &Spi_GaaHwConfig[0]
  }
};

#define SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */



/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

