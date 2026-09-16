/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_sDMAC_LLDriver.h                                                                                */
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
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.1:  31/12/2024  : Add new elements ulMSPITGCTLn and ulMSPITGCTLi in structure Spi_DmaConfigType 
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 * 2.1.1:  28/08/2024  : Support AR2211: update macro file definition.
 *                     : Remove QAC messages (2:0841) to fix redundant QAC messages
 *                     : Increase SW-VERSION up to 2.0.3
 *                     : Remove QAC message 1534, 1535, 1536
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  22/10/2023  : Update QAC message 1534, 1535, 1536 support Amendment 2
 *                       Update SW-VERSION to 2.0.1
 * 2.0.0:  28/08/2023  : Remove SPI_INSTANCE_INDEX
 *         03/08/2023  : Remove QAC message 0791 as redundant
 *         25/07/2023  : Update from "Spi_Mapping.h to "Spi_MemMap.h".
 * 1.4.3:  10/05/2022  : Remove redundant macro
 * 1.4.2:  02/03/2022  : Merge QAC
 * 1.3.2:  06/09/2021  : Update QAC contents
 *         04/09/2021  : Add pre-compile condition for defining multiple files base on instance index
 *                       Replace the inclusion of Spi_MemMap.h with Spi_Mapping.h
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.2.0:  30/07/2020  : Release
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
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

#ifndef SPI_SDMAC_LLDRIVER_H
#define SPI_SDMAC_LLDRIVER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define SPI_SDMAC_LLDRIVER_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION
#define SPI_SDMAC_LLDRIVER_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION
#define SPI_SDMAC_LLDRIVER_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION

/* File version information */
#define SPI_SDMAC_LLDRIVER_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION
#define SPI_SDMAC_LLDRIVER_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Attributes for Spi_DMAStart() */
#define SPI_DMA_16BIT                                  0x00000002UL
#define SPI_DMA_32BIT                                  0x00000004UL
#define SPI_DMA_INCSRC                                 0x00000008UL
#define SPI_DMA_INCDST                                 0x00000010UL
#define SPI_DMA_INTERRUPT                              0x00000100UL
#define SPI_DMA_DTS_STS_MASK                           0x00000007UL

/* Macros to calculate bit position of DMACSEL */
#define SPI_DMA_SEL_INDEX(number)                      ((uint32)(number) >> 4UL)                                        /* PRQA S 3472 # JV-01 */
#define SPI_DMA_SEL_SHIFT(number)                      (((uint32)(number)&0xFUL) << 1UL)                                /* PRQA S 3472 # JV-01 */

/* Bit definitions for DMAjTMR_n */
#define SPI_DMA_TMR_DEFAULT                            0x00000000UL
#define SPI_DMA_SLM_NORMAL                             0x00000000UL
#define SPI_DMA_PRI_MASK                               0x000F0000UL
#define SPI_DMA_TRS                                    0x00001000UL
#define SPI_DMA_DM_FIXED                               0x00000000UL
#define SPI_DMA_DM_INC                                 0x00000400UL
#define SPI_DMA_SM_FIXED                               0x00000000UL
#define SPI_DMA_SM_INC                                 0x00000100UL
#define SPI_DMA_DTS_2                                  0x00000010UL
#define SPI_DMA_DTS_4                                  0x00000020UL
#define SPI_DMA_STS_2                                  0x00000001UL
#define SPI_DMA_STS_4                                  0x00000002UL

/* Bit definitions for DMAjCHCR_n */
#define SPI_DMA_CHCR_DEFAULT                           (uint16)0x0000U
#define SPI_DMA_DPE                                    (uint16)0x0200U
#define SPI_DMA_IE                                     (uint16)0x0002U
#define SPI_DMA_DE                                     (uint16)0x0001U

/* Bit definitions for DMAjCHSTA_n and DMAjCHFCR_n */
#define SPI_DMA_OVF                                    0x00002000UL
#define SPI_DMA_DRQ                                    0x00001000UL
#define SPI_DMA_CAE                                    0x00000008UL
#define SPI_DMA_DSE                                    0x00000004UL
#define SPI_DMA_TE                                     0x00000002UL
#define SPI_DMA_BUSY_DEC                               0x00000001UL

/* Bit definition for DMAjRS_n */
#define SPI_DMA_RS_DEFAULT                             0x00000000UL
#define SPI_DMA_TC(count)                              ((uint32)(count) << 16U)                                         /* PRQA S 3472 # JV-01 */

#define SPI_DMA_TC_MASK                                0xFFFF0000UL
#define SPI_DMA_RS(rs)                                 ((uint32)(rs))                                                   /* PRQA S 3472 # JV-01 */

/* Bit definition for DMAjBUFCR_n */
#define SPI_DMA_ULB_DEFAULT                            0x00000080UL

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* IO mapping structure for SDMA register */
typedef struct STag_Spi_SDMAChRegType                                                                                   /* PRQA S 3630 # JV-01 */
{
  uint32 ulSAR;           /* +0000H SAR   */
  uint32 ulDAR;           /* +0004H DAR   */
  uint32 ulTSR;           /* +0008H TSR   */
  uint32 ulTSRB;          /* +000CH TSRB  */
  uint32 ulTMR;           /* +0010H TMR   */
  uint16 usCHCR;          /* +0014H CHCR  */
  uint16 usCHSTP;         /* +0016H CHSTP */
  uint32 ulCHSTA;         /* +0018H CHSTA */
  uint32 ulCHFCR;         /* +001CH CHFCR */
  uint32 ulGIAI;          /* +0020H GIAI  */
  uint32 ulGOAI;          /* +0024H GOAI  */
  uint32 ulSIAI;          /* +0028H SIAI  */
  uint32 ulSOAI;          /* +002CH SOAI  */
  uint32 aaReserved0[2];  /* Reserved     */
  uint32 ulSGST;          /* +0038H SGST  */
  uint32 ulSGCR;          /* +003CH SGCR  */
  uint32 ulRS;            /* +0040H RS    */
  uint32 ulReserved1;     /* Reserved     */
  uint32 ulBUFCR;         /* +0048H BUFCR */
  uint32 ulReserved2;     /* Reserved     */
  uint32 ulDPPTR;         /* +0050H DPPTR */
  uint32 ulDPCR;          /* +0054H DPCR  */
  uint32 aaReserved3[10]; /* Reserved     */
} Spi_SDMAChRegType;

/***********************************************************************************************************************
**                           Structure for DMAC Registers, which are used to read or write                            **
**                           the status or configured values for proper working of the DMAC                           **
***********************************************************************************************************************/
/* Structure for DMA channel configuration */
typedef struct STag_Spi_DmaConfigType                                                                                   /* PRQA S 3630 # JV-01 */
{
  /* Base address of DMA channel registers */
  volatile P2VAR(Spi_SDMAChRegType, TYPEDEF, REGSPACE) pDmaRegs;                                                        /* PRQA S 3432 # JV-01 */
  /* EIC register address for DMA interrupt */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pICDma;                                                                     /* PRQA S 3432 # JV-01 */
  /* Base address of DMA request source registers */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pDMACSEL;                                                                   /* PRQA S 3432 # JV-01 */
  /* Group No of DMA request source of assigned SPI unit */
  uint8 ucTriggerGroup;
  /* Trigger No of DMA request source of assigned SPI unit */
  uint8 ucTriggerNumber;
  /* Index of HWUnitInfo for assigned SPI unit */
  Spi_HWUnitType ucSPIHWUnit;
  /* Indicate this DMA assigned to Rx side or Tx side */
  boolean blRxSide;
  /* Address of transmission/reception register */
  uint32 ulRegAddress;
  #if (STD_ON == SPI_MSPI_CONFIGURED)
  /* Value of MSPITGCTLn register */
  uint32 ulMSPITGCTLn;
  /* Value of MSPITGCTLi register */
  uint32 ulMSPITGCTLi;
  #endif
} Spi_DmaConfigType;

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#define SPI_START_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"

#if (SPI_DMA_CONFIGURED == STD_ON)

extern FUNC(void, SPI_PRIVATE_CODE) Spi_DMAInit(void);
extern FUNC(void, SPI_PRIVATE_CODE) Spi_DMADeInit(void);

extern FUNC(void, SPI_PRIVATE_CODE)
    Spi_DMAStart(const uint32 LulDmaIndex, volatile CONSTP2CONST(void, AUTOMATIC, SPI_APPL_DATA) LpMemAddress,
                 const uint32 LulCount, const uint32 LulAttributes);

#if (SPI_FORCE_CANCEL_API == STD_ON)
extern FUNC(void, SPI_PRIVATE_CODE) Spi_DMAStop(const uint32 LulDmaIndex);
#endif

extern FUNC(void, SPI_PRIVATE_CODE) Spi_DMAMaskHWUnitInterrupts(const uint32 LulDmaIndex, const boolean LblMask);

extern FUNC(void, SPI_PRIVATE_CODE) Spi_DMAClearInterruptFlag(const uint32 LulDmaIndex);
extern FUNC(uint32, SPI_PRIVATE_CODE) Spi_DMAGetInterruptFlag(const uint32 LulDmaIndex);

#endif /* (SPI_DMA_CONFIGURED == STD_ON) */

#define SPI_STOP_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"

#endif /* SPI_SDMAC_LLDRIVER_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
