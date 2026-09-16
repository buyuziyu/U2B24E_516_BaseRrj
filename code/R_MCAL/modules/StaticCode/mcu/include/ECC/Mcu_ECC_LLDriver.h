/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_ECC_LLDriver.h                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* The header file of Mcu_ECC_LLDriver.c                                                                              */
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
/*              Devices:        X2X                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025   : Update SW-VERSION for U2Bx Ver22.02.00.001 Release
 * 2.5.0:  30/06/2025   : Update SW-VERSION for U2Ax Ver22.01.00(D) Release
 * 2.4.0:  31/05/2025   : Update SW-VERSION for U2Cx Ver21.01.01 Release
 * 2.3.2:  29/04/2025   : Update SW-VERSION for U2Ax Ver22.00.03 Release
 * 2.3.1:  31/03/2025   : Update SW-VERSION for U2BxE Ver22.00.02 Release
 * 2.3.0:  28/02/2025   : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Release
 * 2.1.2:  31/10/2024   : Update SW-VERSION to 2.1.2
 * 2.1.1:  30/08/2024   : Update SW-VERSION to 2.1.1
 *         16/07/2024   : As part of ARDAACL-47932 (ARDAACL-47792), following changes are made:
 *                        - Update Mcu_EccHwInfoType to add pRRAMECCKCPROTReg and pRRAMECCCTLReg
 *                        - Add marco MCU_ECC_ECER1F_MASK, MCU_ECC_ECER2F_MASK and MCU_ECC_ECOVFF_MASK
 *                        - Add marco MCU_RRAM_SST_CLR_VALUE and MCU_RRAM_ECCCTL_ENABLE_VALUE
 *                        As part of QAC 9.5.0 support, following changes are made:
 *                        - Remove redundant QAC message 1534 and 1536
 * 1.4.5:  10/01/2023   : Initial Version as new Mcu structure
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#ifndef MCU_ECC_LLDRIVER_H
#define MCU_ECC_LLDRIVER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* Functionality related to R4.0 */
/* AUTOSAR release version information */
#define MCU_ECC_LLDRIVER_AR_RELEASE_MAJOR_VERSION MCU_AR_RELEASE_MAJOR_VERSION
#define MCU_ECC_LLDRIVER_AR_RELEASE_MINOR_VERSION MCU_AR_RELEASE_MINOR_VERSION
#define MCU_ECC_LLDRIVER_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION

/*  Module software version information */
#define MCU_ECC_LLDRIVER_SW_MAJOR_VERSION   MCU_SW_MAJOR_VERSION
#define MCU_ECC_LLDRIVER_SW_MINOR_VERSION   MCU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                     Global Symbols                                                 **
***********************************************************************************************************************/
#define MCU_ECC_DISABLE_REG_PROTECT_VALUE                   (uint32)0xA5A5A501UL
#define MCU_ECC_ENABLE_REG_PROTECT_VALUE                    (uint32)0xA5A5A500UL

#define MCU_ECC_ECER1F_MASK                                 (uint32)0x00000002UL
#define MCU_ECC_ECER2F_MASK                                 (uint32)0x00000004UL
#define MCU_ECC_ECOVFF_MASK                                 (uint32)0x00000800UL
#define MCU_RRAM_SST_CLR_VALUE                              (uint32)0x00000600UL
#define MCU_RRAM_ECCCTL_ENABLE_VALUE                        (uint32)0x00000018UL

#define MCU_LRAM_SST_CLR_VALUE                              (uint8)0xFF
#define MCU_LRAM_DST_CLR_VALUE                              (uint8)0x01
#define MCU_LRAM_OVF_CLR_VALUE                              (uint8)0x03
#define MCU_CRAM_SST_CLR_VALUE                              (uint8)0xFF
#define MCU_CRAM_DST_CLR_VALUE                              (uint8)0x01
#define MCU_CRAM_OVF_CLR_VALUE                              (uint8)0x03

#if (MCU_PROVIDE_RAM_STATE_ISR == STD_ON)
  /* LR0_ERRINT */
  #define MCU_LR0_ERRINT_ENABLE_VALUE                       (uint8)0x8BU
  /* LR1_ERRINT */
  #define MCU_LR1_ERRINT_ENABLE_VALUE                       (uint8)0x83U
  /* CR_ERRINT */
  #define MCU_CR_ERRINT_ENABLE_VALUE                        (uint8)0x8BU
#endif /* (MCU_PROVIDE_RAM_STATE_ISR == STD_ON) */

#define MCU_RAM_ECCECM_INIT_NOT_DONE                        (uint8)0x00U
#define MCU_RAM_ECCECM_INIT_DONE                            (uint8)0x01U

/***********************************************************************************************************************
**                                            Global Data Types                                                       **
***********************************************************************************************************************/


/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"
extern FUNC(void, MCU_PRIVATE_CODE) Mcu_ECCSetLramEccInt(void);

extern FUNC(void, MCU_PRIVATE_CODE) Mcu_ECCSetCramEccInt(void);

#if (MCU_RETENTION_RAM_SETTING == STD_ON)
extern FUNC(void, MCU_PRIVATE_CODE) Mcu_ECCSetRramEccInt(void);
#endif /* MCU_RETENTION_RAM_SETTING == STD_ON */

#if (MCU_GET_RAM_STATE_API == STD_ON)
#if (MCU_PROVIDE_RAM_STATE_ISR != STD_ON)
extern FUNC(Mcu_RamStateType, MCU_PRIVATE_CODE) Mcu_ECCGetRamState(void);
#endif /* (MCU_PROVIDE_RAM_STATE_ISR != STD_ON) */
#endif /* (MCU_GET_RAM_STATE_API == STD_ON) */

#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

/***********************************************************************************************************************
**                                   ECC Hardware Information Structure                                               **
***********************************************************************************************************************/
typedef struct STag_Mcu_EccHwInfoType                                                                                   /* PRQA S 3630 # JV-01 */
{
  /* The address of ECCKCPROT Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECCKCPROTReg;                                                              /* PRQA S 3432 # JV-01 */
  #if (MCU_RETENTION_RAM_SETTING == STD_ON)
  /* The address of RRAMECCKCPROT Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pRRAMECCKCPROTReg;                                                          /* PRQA S 3432 # JV-01 */
  /* The address of RRAMECCCTL Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pRRAMECCCTLReg;                                                             /* PRQA S 3432 # JV-01 */
  #endif /* MCU_RETENTION_RAM_SETTING == STD_ON */
  /* The address of CR_SSTCLR Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCR_SSTCLRReg;                                                              /* PRQA S 3432 # JV-01 */
  /* The address of CR_DSTCLR Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCR_DSTCLRReg;                                                              /* PRQA S 3432 # JV-01 */
  /* The address of CR_OVFCLR Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCR_OVFCLRReg;                                                              /* PRQA S 3432 # JV-01 */
  /* The address of MCU_CR_ERRINT Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCR_ERRINTReg;                                                              /* PRQA S 3432 # JV-01 */
  /* The address of pCR_SERSTR Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCR_SERSTRReg;                                                              /* PRQA S 3432 # JV-01 */
  /* The address of CR_DERSTR Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCR_DERSTRReg;                                                              /* PRQA S 3432 # JV-01 */
  /* The address of CR_OVFSTR Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCR_OVFSTRReg;                                                              /* PRQA S 3432 # JV-01 */
  /* The address of LR1_SSTCLR Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pLR1_SSTCLRReg;                                                             /* PRQA S 3432 # JV-01 */
  /* The address of LR1_DSTCLR Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pLR1_DSTCLRReg;                                                             /* PRQA S 3432 # JV-01 */
  /* The address of LR1_OVFCLR Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pLR1_OVFCLRReg;                                                             /* PRQA S 3432 # JV-01 */
  /* The address of LR1_ERRINT Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pLR1_ERRINTReg;                                                             /* PRQA S 3432 # JV-01 */
  /* The address of LR0_ERRINT_PE0 Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pLR0_ERRINT_PE0Reg;                                                         /* PRQA S 3432 # JV-01 */
  /* The address of LR1_SERSTR Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pLR1_SERSTRReg;                                                             /* PRQA S 3432 # JV-01 */
  /* The address of LR1_DERSTR Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pLR1_DERSTRReg;                                                             /* PRQA S 3432 # JV-01 */
  /* The address of LR1_OVFSTR Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pLR1_OVFSTRReg;                                                             /* PRQA S 3432 # JV-01 */
  /* The offset of address of LR_PEn Register */
  uint32 ulLR0PEnOffset;
  /* The offset of address of LR0_SSTCLR Register */
  uint32 ulLR0SSTCLROffset;
  /* The offset of address of LR0_DSTCLR Register */
  uint32 ulLR0DSTCLROffset;
  /* The offset of address of LR0_OVFCLR Register */
  uint32 ulLR0OVFCLROffset;
  /* The offset of address of LR0_SERSTR Register */
  uint32 ulLR0SERSTROffset;
  /* The offset of address of LR0_DERSTR Register */
  uint32 ulLR0DERSTROffset;
  /* The offset of address of LR0_OVFSTR Register */
  uint32 ulLR0OVFSTROffset;
} Mcu_EccHwInfoType;

#endif  /* MCU_ECC_LLDRIVER_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
