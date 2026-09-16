/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_RST_LLDriver.h                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* The header file of Mcu_RST_LLDriver.c                                                                              */
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

#ifndef MCU_RST_LLDRIVER_H
#define MCU_RST_LLDRIVER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* Functionality related to R4.0 */
/* AUTOSAR release version information */
#define MCU_RST_LLDRIVER_AR_RELEASE_MAJOR_VERSION MCU_AR_RELEASE_MAJOR_VERSION
#define MCU_RST_LLDRIVER_AR_RELEASE_MINOR_VERSION MCU_AR_RELEASE_MINOR_VERSION
#define MCU_RST_LLDRIVER_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION

/*  Module software version information */
#define MCU_RST_LLDRIVER_SW_MAJOR_VERSION   MCU_SW_MAJOR_VERSION
#define MCU_RST_LLDRIVER_SW_MINOR_VERSION   MCU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                     Global Symbols                                                 **
***********************************************************************************************************************/

/* Definition of uninitialized RESET value */
#define MCU_RESET_UNINIT              (uint32)0xFFFFFFFFUL

#define MCU_SW_RESET_ENABLE_VALUE     (uint32)0x00000001UL

/* RESF register bit12 indicate HW BIST Execution Flag */
#define MCU_HWBISTF                   (uint32)0x00007000UL

/* Reset Controller KeyCode Protection */
#define MCU_RST_DISABLE_REG_PROTECT_VALUE   (uint32)0xA5A5A501UL
#define MCU_RST_ENABLE_REG_PROTECT_VALUE    (uint32)0xA5A5A500UL

/***********************************************************************************************************************
**                                            Global Data Types                                                       **
***********************************************************************************************************************/
/* Structure for the register information for clock conctroller */
typedef struct STag_Mcu_ResetHwInfoType                                                                                 /* PRQA S 3630 # JV-01 */
{
  /* The address of address of RESKCPROT0 register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pPReg;                                                                      /* PRQA S 3432 # JV-01 */
  /* The address of address of RESFC register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pRESFCReg;                                                                  /* PRQA S 3432 # JV-01 */
  /* The address of address of RESC register */
  volatile P2CONST(uint32, TYPEDEF, REGSPACE) pRESCReg;
  /* The address of address of RESF register */
  volatile P2CONST(uint32, TYPEDEF, REGSPACE) pRESFReg;
  #if (MCU_SWRESET_APPLICATION_RESET == STD_ON)
  /* The address of address of SWSRESA register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pSWARESAReg;                                                                /* PRQA S 3432 # JV-01 */
  #else
  /* The address of address of SWSRESA register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pSWSRESAReg;                                                                /* PRQA S 3432 # JV-01 */
  #endif /* MCU_SWRESET_APPLICATION_RESET == STD_ON */
  /* Reset Factor Flag position value */
  P2CONST(Mcu_ResetType, AUTOMATIC, MCU_CONFIG_DATA) pRstRsnTable;
} Mcu_ResetHwInfoType;

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

extern FUNC(Mcu_ResetType, MCU_PRIVATE_CODE) Mcu_RSTGetResetReason (void);

extern FUNC(Mcu_RawResetType, MCU_PRIVATE_CODE) Mcu_RSTGetResetRawValue (void);

extern FUNC(void, MCU_PRIVATE_CODE) Mcu_RSTSetEcmReset (void);

#if (MCU_PERFORM_RESET_API == STD_ON)
extern FUNC(void, MCU_PRIVATE_CODE) Mcu_RSTPerformReset (void);
#endif

#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

#endif  /* MCU_RST_LLDRIVER_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
