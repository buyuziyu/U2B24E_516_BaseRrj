/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_MSPI_LLDriver.h                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the type definitions for link time parameters                                                   */
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
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s) and/or */
/* the Application.                                                                                                   */
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
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.4.0:  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) Release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                       Add new QAC msg: 4641 to support QAC 11.6.0
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 * 2.1.1:  31/10/2024  : Support AR2211: update macro file definition.
 * 2.1.1:  30/07/2024  : Update to support for ored interrupt:
 *                       + Add new macro "SPI_MSPI_ORED_DISABLED", "SPI_MSPI_ORED_UNITS"
 *                       + Add new struct "Spi_MSPIHwOredISR"
 *                     : Add new macro SPI_MSPI_STR0_CSF
 *                     : Add new macro SPI_MSPI_FOUR_CHANNELS, SPI_MSPI_NINE_CHANNELS, SPI_MSPI_THREE
 *                     : Change SPI_START_SEC_CONFIG_DATA_UNSPECIFIED to
 *                       SPI_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
 *                     : Change SPI_STOP_SEC_CONFIG_DATA_UNSPECIFIED to
 *                       SPI_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
 *                     : Update Memmory class for Spi_GaaMSPIOredISRRegs from SPI_CONST to SPI_CONFIG_DATA
 *                     : Remove QAC messages (2:0841) to fix redundant QAC messages
 *                     : Increase SW-VERSION up to 2.0.3
 *                     : Add Spi_GaaMSPIOredISRRegs, Spi_MSPIOredISRRegisterSetType and Update Spi_MSPIRegisterSetType
 *                       to support ORed interrupt function
 *                     : Remove QAC message 1534, 1536
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  22/10/2023  : Update QAC message 1534, 1536 support Amendment 2
 *                       Update SW-VERSION to 2.0.1
 * 2.0.0:  28/08/2023  : Remove SPI_INSTANCE_INDEX 
 *         25/07/2023  : Update from "Spi_Mapping.h to "Spi_MemMap.h".
 * 1.4.3:  19/04/2022  : Update uint8 ucCFCNT to uint16 usCFCNT 
 *                       Update uint8 aaReserved17[3] to uint8 aaReserved17[2]
 *                       Change ulTRGCTL to ulTGCTL, ulTRGCTLi to ulTGCTL in struct STag_Spi_MSPITrgGenRegType
 *                       Change SPI_MSPI_NUM_TRGCTLI to SPI_MSPI_NUM_TGCTLI
 *         20/05/2022  : Remove redundant macro
 * 1.4.2:  07/03/2022  : Merge QAC
 *                       Added macro SPI_MSPI_CONFIGURED for items is using SPI_MSPI_MAX_CHANNEL
 * 1.4.1:  09/09/2021  : Remove the definition of SPI_MSPI_MAX_CHANNEL, this value will be GenTool-handled.
 *                       Remove macro unused SPI_MSPI_TGSEL_*, SPI_MSPI_HWTS_*, SPI_MSPI_SSTX_*, SPI_MSPI_INTFC*,
 *                       SPI_MSPI_TGDMAALT_DEFAULT, and SPI_MSPI_TGDTSALT_DEFAULT.
 *                       Add element global variable ulTRGCTLi[3] to struct Spi_MSPITrgGenRegType.
 *                       Add macro SPI_MSPI_NUM_TRGCTLI, SPI_MSPI_MAX_CHANNEL_DEFAULT, and 
 *                       SPI_MSPI_MIN_CHANNEL_DEFAULT for the number of MSPITRGCTLi registers.
 *                       Update SW-VERSION to 1.4.1 
 * 1.3.2:  06/09/2021  : Update QAC contents
 *         04/09/2021  : Add pre-compile condition for defining multiple files base on instance index
 *                       Replace the inclusion of Spi_MemMap.h with Spi_Mapping.h
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END) 
 * 1.2.1:  02/10/2020  : Add macro for defining dummy read count variable.
 * 1.2.0:  30/07/2020  : Release
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.1:  14/04/2020  : aaRam is removed in Spi_MSPIRegType
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:4641)    : The identifier '%1s' could conflict in the future with the name of a macro in '<%2s>'.       */
/* Rule                : CERTC 3.6.0 Rule DCL37, CWE 3.6.0 Rule CWE-398, CWE-569                                      */
/* JV-01 Justification : This message is just a notice to avoid using this identifier as a macro in standard library  */
/*                       in the future.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#ifndef SPI_MSPI_LLDRIVER_H
#define SPI_MSPI_LLDRIVER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Spi.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define SPI_MSPI_LLDRIVER_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION
#define SPI_MSPI_LLDRIVER_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION
#define SPI_MSPI_LLDRIVER_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION

/* File version information */
#define SPI_MSPI_LLDRIVER_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION
#define SPI_MSPI_LLDRIVER_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Maximum number of MSPI */
#define SPI_MSPI_MAX_HWUNIT                           10U

/* The number of MSPITGCTLi registers */
#define SPI_MSPI_NUM_TGCTLI                           3U

/* Maximum/Minimum number of transfer channels */
#define SPI_MSPI_MAX_CHANNEL_DEFAULT                  12U
#define SPI_MSPI_MIN_CHANNEL_DEFAULT                  1U
#define SPI_MSPI_FOUR_CHANNELS                        4U
#define SPI_MSPI_NINE_CHANNELS                        9U
#define SPI_MSPI_THREE                                3U

/* Define the half of minimum of of stage size of FIFO buffer */
#define SPI_MSPI_HALF_MIN_STAGE                       4U

/* MSPInCTL0 */
#define SPI_MSPI_CTL0_DEFAULT                         (uint8)0x00U
#define SPI_MSPI_EN                                   (uint8)0x01U
#define SPI_MSPI_TURNOFF                              (uint8)0x00U
#define SPI_MSPI_DUMMY_READ_12T                       (uint32)0x0000000CU

/* MSPInCTL1 */
#define SPI_MSPI_CTL1_DEFAULT                         0x00000000UL
#define SPI_MSPI_CSP(x)                               (uint32)(x)

/* MSPInCTL2 */
#define SPI_MSPI_CTL2_DEFAULT                         (uint8)0x00U

/* MSPInCSTSm */
#define SPI_MSPI_ACTFS                                (uint8)0x02U
#define SPI_MSPI_CHENS                                (uint8)0x01U

/* MSPInCSTCm */
#define SPI_MSPI_CHENC                                (uint8)0x01U

/* MSPInCFGm0 */
#define SPI_MSPI_CFG0_DEFAULT                         0x00700000UL
#define SPI_MSPI_PRIO(x)                              ((uint32)(x) << 20UL)
#define SPI_MSPI_IFEE                                 0x00000004UL
#define SPI_MSPI_IRXE                                 0x00000002UL
#define SPI_MSPI_ITXE                                 0x00000001UL

/* MSPInCFGm1 */
#define SPI_MSPI_CFG1_DEFAULT                         0x01000000UL
#define SPI_MSPI_DIR                                  0x00100000UL

/* MSPInCFGm2 */
#define SPI_MSPI_CFG2_DEFAULT                         (uint16)0x0020U

/* MSPInCFGm3 */
#define SPI_MSPI_CFG3_DEFAULT                         (uint16)0x0001U
#define SPI_MSPI_PRCS_DIV1                            (uint16)0x0000U
#define SPI_MSPI_CDIV_DIV2                            (uint16)0x0001U
#define SPI_MSPI_CDIV_DIV4                            (uint16)0x0002U
#define SPI_MSPI_CDIV_DIV6                            (uint16)0x0003U

/* MSPInCFGm4 */
#define SPI_MSPI_CFG4_DEFAULT                         0x00000000UL
#define SPI_MSPI_SIZE_MASK                            0x00000003UL
#define SPI_MSPI_HWTS_MASK                            0x003F0000UL

/* MSPInRASTADm */
#define SPI_MSPI_RASTAD_DEFAULT                       (uint16)0x0000U

/* MSPInSEUPm */
#define SPI_MSPI_SEUP_DEFAULT                         (uint16)0x0001U

/* MSPInHOLDm */
#define SPI_MSPI_HOLD_DEFAULT                         (uint16)0x0001U

/* MSPInIDLEm */
#define SPI_MSPI_IDLE_DEFAULT                         (uint16)0x0001U

/* MSPInINDAm */
#define SPI_MSPI_INDA_DEFAULT                         (uint16)0x0001U

/* MSPInCFSETm */
#define SPI_MSPI_CFSET_DEFAULT                        (uint16)0x0001U

/* MSPInFRERSTm */
#define SPI_MSPI_DCEFST                               (uint8)0x10U
#define SPI_MSPI_CEFST                                (uint8)0x02U
#define SPI_MSPI_PEFST                                (uint8)0x01U

/* MSPInFRERSTCm */
#define SPI_MSPI_DCEFSC                               (uint8)0x10U  
#define SPI_MSPI_CEFSC                                (uint8)0x02U  
#define SPI_MSPI_PEFSC                                (uint8)0x01U  

/* MSPInCESTm */
#define SPI_MSPI_OVREE                                (uint8)0x80U  
#define SPI_MSPI_OVWRE                                (uint8)0x40U  
#define SPI_MSPI_OVRUE                                (uint8)0x20U  
#define SPI_MSPI_DCE                                  (uint8)0x10U  
#define SPI_MSPI_CE                                   (uint8)0x02U  
#define SPI_MSPI_PE                                   (uint8)0x01U  
#define SPI_MSPI_NO_ERR                               (uint8)0x00U  

/* MSPInCESTCm */
#define SPI_MSPI_OVREEC                               (uint8)0x80U
#define SPI_MSPI_OVWREC                               (uint8)0x40U
#define SPI_MSPI_OVRUEC                               (uint8)0x20U
#define SPI_MSPI_DCEC                                 (uint8)0x10U
#define SPI_MSPI_CEC                                  (uint8)0x02U
#define SPI_MSPI_PEC                                  (uint8)0x01U

/* MSPInINTFk */
#define SPI_MSPI_INTF(x)                              (uint32)(x)

/* MSPITGCTLn */
#define SPI_MSPI_TGSEL_TG12TX0RX0                     0x0000000EUL
#define SPI_MSPI_TGSEL_TG12TX0RX1                     0x000000E0UL
#define SPI_MSPI_TGSEL_TG12TX0RX2                     0x00000E00UL
#define SPI_MSPI_TGSEL_TG12TX0RX3                     0x0000E000UL
#define SPI_MSPI_TGSEL_TG12TX0RX4                     0x000E0000UL
#define SPI_MSPI_TGSEL_TG12TX0RX5                     0x00E00000UL
#define SPI_MSPI_TGSEL_TG12TX0RX6                     0x0E000000UL
#define SPI_MSPI_TGSEL_TG12TX0RX7                     0xE0000000UL

/* MSPInSTR0 */
#define SPI_MSPI_STR0_CSF                             (uint8)0x01U

/* ORED */
#define SPI_MSPI_ORED_DISABLED                        (uint16)0x0000U
#define SPI_MSPI_ORED_UNITS                           4U

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* IO mapping structure for Channel register */
typedef struct STag_Spi_MSPIChannelRegType
{
  uint32 ulCFG0; /* +0000H           */
  uint32 ulCFG1; /* +0004H           */
  uint16 usCFG2; /* +0008H           */
  uint8 aaReserved1[2]; /* Reserved         */
  uint16 usCFG3; /* +000CH           */
  uint8 aaReserved2[2]; /* Reserved         */
  uint32 ulCFG4; /* +0010H           */
  uint8 aaReserved3[4]; /* Reserved         */
  uint16 usSEUP; /* +0018H           */
  uint8 aaReserved4[2]; /* Reserved         */
  uint16 usHOLD; /* +001CH           */
  uint8 aaReserved5[2]; /* Reserved         */
  uint16 usIDLE; /* +0020H           */
  uint8 aaReserved6[2]; /* Reserved         */
  uint16 usINDA; /* +0024H           */
  uint8 aaReserved7[2]; /* Reserved         */
  uint16 usRASTAD; /* +0028H           */
  uint8 aaReserved8[2]; /* Reserved         */
  uint16 usCFSET; /* +002CH           */
  uint8 aaReserved9[2]; /* Reserved         */
  uint32 ulSSTX; /* +0030H           */
  uint8 ucCSTS;  /* +0034H           */
  uint8 aaReserved10[3]; /* Reserved         */
  uint8 ucCSTC; /* +0038H           */
  uint8 aaReserved11[3]; /* Reserved         */
  uint16 usSSEL; /* +003CH           */
  uint8 aaReserved12[2]; /* Reserved         */
  uint32 ulTXDA0; /* +0040H           */
  uint8 aaReserved13[8]; /* Reserved         */
  uint8 ucFRERST; /* +004CH           */
  uint8 aaReserved14[3]; /* Reserved         */
  uint32 ulRXDA0; /* +0050H           */
  uint8 aaReserved15[4]; /* Reserved         */
  uint16 usCSTR; /* +0058H           */
  uint8 aaReserved16[2]; /* Reserved         */
  uint16 usCFCNT; /* +005CH           */
  uint8 aaReserved17[2]; /* Reserved         */
  uint32 ulFSRX;   /* +0060H           */
  uint8 ucFRERSTC; /* +0064H           */
  uint8 aaReserved18[3]; /* Reserved         */
  uint8 ucCEST; /* +0068H           */
  uint8 aaReserved19[3]; /* Reserved         */
  uint8 ucCESTC; /* +006CH           */
  uint8 aaReserved20[19]; /* Reserved         */
} Spi_MSPIChannelRegType;

/* IO mapping structure for MSPI registers */
typedef struct STag_Spi_MSPIRegType                                                                                     /* PRQA S 3630 # JV-01 */
{
  uint8 ucCTL0; /* +0000H           */
  uint8 aaReserved0[3]; /* Reserved         */
  uint32 ulCTL1; /* +0004H           */
  uint8 ucCTL2;  /* +0008H           */
  uint8 aaReserved1[7]; /* Reserved         */
  uint8 ucSTR0; /* +0010H           */
  uint8 aaReserved2[111]; /* Reserved         */
  #if (SPI_MSPI_CONFIGURED == STD_ON)
  Spi_MSPIChannelRegType aaCH[SPI_MSPI_MAX_CHANNEL]; /* +0080H           */
  #endif /* (SPI_MSPI_CONFIGURED == STD_ON) */
} Spi_MSPIRegType;

/* IO mapping structure for MSPI Interrupt registers */
typedef struct STag_Spi_MSPIIntfRegType                                                                                 /* PRQA S 3630 # JV-01 */
{
  uint32 ulINTF0;   /* +0000H           */
  uint32 ulINTMSK0; /* +0004H           */
  uint32 ulINTFC0;  /* +0008H           */
  uint8 aaReserved0[36]; /* Reserved         */
  uint32 ulINTF1;   /* +0030H           */
  uint32 ulINTMSK1; /* +0034H           */
  uint32 ulINTFC1;  /* +0038H           */
  uint8 aaReserved1[36]; /* Reserved         */
  uint32 ulINTF2;   /* +0060H           */
  uint32 ulINTMSK2; /* +0064H           */
  uint32 ulINTFC2;  /* +0068H           */
  uint8 aaReserved2[36]; /* Reserved         */
  uint32 ulINTF3;   /* +0090H           */
  uint32 ulINTMSK3; /* +0094H           */
  uint32 ulINTFC3;  /* +0098H           */
  uint8 aaReserved3[36]; /* Reserved         */
} Spi_MSPIIntfRegType;

/* IO mapping structure for MSPI Trigger Generator registers */
typedef struct STag_Spi_MSPITrgGenRegType                                                                               /* PRQA S 3630 # JV-01 */
{
#if (SPI_MSPI_CONFIGURED == STD_ON)
#if (SPI_MSPI_MAX_CHANNEL == SPI_MSPI_MAX_CHANNEL_DEFAULT)
  uint32 ulTGCTL[SPI_MSPI_MAX_HWUNIT];    /* +0000H+(n*4)     */
  uint32 ulTGDMAALT;                      /* +0028H           */
  uint32 ulTGDTSALT;                      /* +002CH           */
  uint32 ulTGCTLi[SPI_MSPI_NUM_TGCTLI];   /* +0030H+(i*4)     */
#else
  uint32 ulTGCTL[SPI_MSPI_MAX_HWUNIT];    /* +0000H+(n*4)     */
  uint32 ulTGDMAALT;                      /* +0028H           */
  uint32 ulTGDTSALT;                      /* +002CH           */
#endif
#endif /* (SPI_MSPI_CONFIGURED == STD_ON) */
} Spi_MSPITrgGenRegType;

/* Structure for the register information for each MSPI unit */
typedef struct STag_Spi_MSPIRegisterSetType
{
  /* Base address of MSPI registers */
  volatile P2VAR(Spi_MSPIRegType, TYPEDEF, REGSPACE) pRegs;                                                             /* PRQA S 3432 # JV-01 */
  /* Base address of MSPI Interrupt registers */
  volatile P2VAR(Spi_MSPIIntfRegType, TYPEDEF, REGSPACE) pIntfRegs;                                                     /* PRQA S 3432 # JV-01 */
  /* Base address of MSPI Trigger Generator registers */
  volatile P2VAR(Spi_MSPITrgGenRegType, TYPEDEF, REGSPACE) pTrgGenRegs;                                                 /* PRQA S 3432 # JV-01 */
#if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
  /* EIC register address for INTMSPInTXm interrupt */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pICTX;                                                                      /* PRQA S 3432 # JV-01 */
  /* EIC register address for INTMSPInRXm interrupt */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pICRX;                                                                      /* PRQA S 3432 # JV-01 */
  /* EIC reigster address for INTMSPInFEm interrupt */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pICFE;                                                                      /* PRQA S 3432 # JV-01 */
  /* EIC reigster address for INTMSPInERRm interrupt */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pICERR;                                                                     /* PRQA S 3432 # JV-01 */
  /* The channel number of MSPIn */
  uint8 ucPhyChannelMax;
#else
  /* value of interrupt selection index*/
  uint8 ucPhyChannelMax;
  /* value of interrupt selection index*/
  VAR(uint8, SPI_CONFIG_DATA) ucInterruptSel;
#endif
} Spi_MSPIRegisterSetType;

#if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
/* Structure for the register information for each MSPI Ored unit */
typedef struct STag_Spi_MSPIOredISRRegisterSetType
{
  /* EIC register address for INTMSPInTXm interrupt */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pICTX;                                                                      /* PRQA S 3432 # JV-01 */
  /* EIC register address for INTMSPInRXm interrupt */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pICRX;                                                                      /* PRQA S 3432 # JV-01 */
  /* EIC reigster address for INTMSPInFEm interrupt */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pICFE;                                                                      /* PRQA S 3432 # JV-01 */
  /* EIC reigster address for INTMSPInERRm interrupt */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pICERR;                                                                     /* PRQA S 3432 # JV-01 */
  /* EIC register address for INTMSPICTSMONn interrupt */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pICTSMON;                                                                   /* PRQA S 3432 # JV-01 */
  /* EIC register address for INTMSPICTSMSKn interrupt */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pICTSMSK;                                                                   /* PRQA S 3432 # JV-01 */
  /* EIC register address for INTMSPICTRSMONn interrupt */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pICRSMON;                                                                   /* PRQA S 3432 # JV-01 */
  /* EIC register address for INTMSPICRSMSKn interrupt */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pICRSMSK;                                                                   /* PRQA S 3432 # JV-01 */
  /* EIC register address for INTMSPICFCMONn interrupt */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pICFCMON;                                                                   /* PRQA S 3432 # JV-01 */
  /* EIC register address for INTMSPICFCMSKn interrupt */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pICFCMSK;                                                                   /* PRQA S 3432 # JV-01 */
  /* EIC register address for INTMSPICERMONn interrupt */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pICERMON;                                                                   /* PRQA S 3432 # JV-01 */
  /* EIC register address for INTMSPICERMSKn interrupt */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pICERMSK;                                                                   /* PRQA S 3432 # JV-01 */    
} Spi_MSPIOredISRRegisterSetType ;
#endif

/* Definition of MemoryMode for MSPI */
typedef enum ETag_Spi_MemoryModeType                                                                                    /* PRQA S 4641 # JV-01 */
{
  /* Direct memory mode */
  SPI_MEMORYMODE_DIRECT = 0,
  /* Fixed buffer memory mode */
  SPI_MEMORYMODE_FIXED_BUFFER,
  /* Fixed FIFO memory mode */
  SPI_MEMORYMODE_FIXED_FIFO
} Spi_MemoryModeType;

/* Structure for HW-dependent Job configuration */
typedef struct STag_Spi_MSPIDeviceConfigType
{
  /* The physical index of HWUnit channel. 'm' of MSPInCFGmx, Other */
  uint8 ucPhyChannelIndex;
  /* Memory mode when macro is MSPI */
  Spi_MemoryModeType enMemoryMode;
  /* Value of MSPInCTL1 register */
  uint32 ulMSPICTL1;
  /* Value of MSPInCTL2 register */
  uint8 ucMSPICTL2;
  /* Value of MSPInCFGm0 register */
  uint32 ulMSPICFG0;
  /* Value of MSPInCFGm1 register except MSPInDIRm fields */
  uint32 ulMSPICFG1;
  /* Value of MSPInCFGm3 register */
  uint16 usMSPICFG3;
  /* Value of MSPInCFGm4 register */
  uint32 ulMSPICFG4;
  /* Value of MSPInSEUPm register */
  uint16 usMSPISEUP;
  /* Value of MSPInHOLDm register */
  uint16 usMSPIHOLD;
  /* Value of MSPInIDLEm register */
  uint16 usMSPIIDLE;
  /* Value of MSPInINDAm register */
  uint16 usMSPIINDA;
  /* Value of MSPInRASTADm register */
  uint16 usMSPIRASTAD;
} Spi_MSPIDeviceConfigType;

#if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
/* Structure for Bit array indicates active HW unit index in Ored interrupt */
typedef struct STag_Spi_MSPIHwOredISR
{
  /* Bit array indicates active HW unit index in TX Ored interrupt */
  uint16 usHwOredTxIsr;
  /* Bit array indicates active HW unit index in RX Ored interrupt */
  uint16 usHwOredRxIsr;
  /* Bit array indicates active HW unit index in FE Ored interrupt */
  uint16 usHwOredFeIsr;
} Spi_MSPIHwOredISR;
#endif /* #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON) */

#define SPI_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Spi_MemMap.h"

/* The instance is declared in Spi_Lcfg.c */
extern CONST(Spi_MSPIRegisterSetType, SPI_CONFIG_DATA) Spi_GaaMSPIRegs[];                                               /* PRQA S 3684 # JV-01 */

#if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
extern CONST(Spi_MSPIOredISRRegisterSetType, SPI_CONFIG_DATA) Spi_GaaMSPIOredISRRegs[];                                 /* PRQA S 3684 # JV-01 */
#endif

#define SPI_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Spi_MemMap.h"

#define SPI_START_SEC_CONST_UNSPECIFIED
#include "Spi_MemMap.h"

/* HW-dependent function pointer table */
extern CONST(Spi_HwFuncTableType, SPI_CONST) Spi_GstMSPIFunc;

#define SPI_STOP_SEC_CONST_UNSPECIFIED
#include "Spi_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define SPI_START_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"

#if (SPI_MSPI_CONFIGURED == STD_ON)
#if ((SPI_DIRECT_ACCESS_MODE == STD_ON) || (SPI_FIXED_FIFO_MODE == STD_ON))
extern FUNC(void, SPI_PRIVATE_CODE) Spi_MSPITransmitISR(const uint32 LulHWUnitIndex);
extern FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIReceiveISR(const uint32 LulHWUnitIndex);
#endif
#if (SPI_FIXED_BUFFER_MODE == STD_ON)
extern FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIFrameEndISR(const uint32 LulHWUnitIndex);
#endif
#endif /* (SPI_MSPI_CONFIGURED == STD_ON) */

#define SPI_STOP_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"

#endif /* SPI_MSPI_LLDRIVER_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
