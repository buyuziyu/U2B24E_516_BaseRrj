/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_CLM_LLDriver.h                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* The header file of Mcu_CLM_LLDriver.c                                                                              */
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
 * 2.0.0:  10/07/2023   : Remove redundant QAC message 3432
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

#ifndef MCU_CLM_LLDRIVER_H
#define MCU_CLM_LLDRIVER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* Functionality related to R4.0 */
/* AUTOSAR release version information */
#define MCU_CLM_LLDRIVER_AR_RELEASE_MAJOR_VERSION MCU_AR_RELEASE_MAJOR_VERSION
#define MCU_CLM_LLDRIVER_AR_RELEASE_MINOR_VERSION MCU_AR_RELEASE_MINOR_VERSION
#define MCU_CLM_LLDRIVER_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION

/*  Module software version information */
#define MCU_CLM_LLDRIVER_SW_MAJOR_VERSION   MCU_SW_MAJOR_VERSION
#define MCU_CLM_LLDRIVER_SW_MINOR_VERSION   MCU_SW_MINOR_VERSION

/* CLMA Controller KeyCode Protection */
#define MCU_CLMA_DISABLE_REG_PROTECT_VALUE                 (uint32)0xA5A5A501UL
#define MCU_CLMA_ENABLE_REG_PROTECT_VALUE                  (uint32)0xA5A5A500UL

/* Clock Monitor Test Register Setting */
#define MCU_CLMERRMASK_BIT                                 (uint32)0x00000004UL
#define MCU_CLM3TESEN_BIT                                  (uint32)0x00000040UL
#define MCU_CLMRESCLM_BIT                                  (uint32)0x00000001UL

#define MCU_ENABLE_CLMA                                    (uint8)0x01U

#define MCU_ENABLE_BACKUP_CLOCK_SWITCH                     (uint8)0x01U

#define MCU_ECM_ECMSSTR1_CLM3ERR_MASK                       (uint32)0x00080000UL
/***********************************************************************************************************************
**                                         Structure for CLM registers                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                            Global Data Types                                                       **
***********************************************************************************************************************/

typedef struct STag_Mcu_ClmSettingType
{
  /* Pointer to CLMA Control Register  */
  volatile P2VAR(uint8, TYPEDEF, REGSPACE) pCLMACTLRegs;                                                                /* PRQA S 3432 # JV-01 */
  /* Pointer to CLMA Comparison Register L */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pCLMACMPLRegs;                                                              /* PRQA S 3432 # JV-01 */
  /* Pointer to CLMA Comparison Register H */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pCLMACMPHRegs;                                                              /* PRQA S 3432 # JV-01 */
  /* Element containing value of CLMA0CMPL register */
  uint16 usClmCmpLvalue;
  /* Element containing value of CLMA0CMPH register */
  uint16 usClmCmpHvalue;
  #if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
  /* Element to check whether CLMn should be stop in Standby mode */
  boolean blClmStopInStandby;
  /* Element containing CLMn test enable/disable value */
  uint32 ulClmTestEnableBit;
  #endif
  #if (MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_ON)
  /* Element to check whether CLMn support backup clock enable */
  boolean blClmBackupEnable;
  /* Pointer to CLMA Backup Clock Enable */
  volatile P2VAR(uint8, TYPEDEF, REGSPACE) pCLMABCERegs;                                                                /* PRQA S 3432 # JV-01 */
  #endif
  #if (MCU_DMON_DIAG_OPERATION == STD_ON)
  /* Element to check whether CLMn used for DMON Start-Up */
  boolean blClmMOSC;
  #endif
} Mcu_ClmSettingType;

typedef struct STag_Mcu_ClmHwInfoType                                                                                   /* PRQA S 3630 # JV-01 */
{
  /* Pointer to Clock Monitor Register Key Code Protecion */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCLMAKCPROTRegs;                                                            /* PRQA S 3432 # JV-01 */
  /* Pointer to Clock Monitor Test Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCLMATESTRegs;                                                              /* PRQA S 3432 # JV-01 */
  /* Pointer to Clock Monitor Test Status Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCLMATESTSRegs;                                                             /* PRQA S 3432 # JV-01 */
  #if (MCU_CLMA_BACKUP_CLOCK_ENABLE_SUPPORT == STD_OFF)
  /* Pointer to Clock Monitor 3 Control Register */
  volatile P2VAR(uint8, TYPEDEF, REGSPACE) pCLMA3CTLRegs;                                                               /* PRQA S 3432 # JV-01 */
  #endif
}Mcu_ClmHwInfoType;

/***********************************************************************************************************************
**                                           Function Prototypes                                                      **
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"
extern FUNC(void, MCU_PRIVATE_CODE) Mcu_CLMStart(void);
extern FUNC(void, MCU_PRIVATE_CODE) Mcu_CLMInit(void);

#if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
#if (MCU_CLMA_OPERATION == STD_ON)
extern FUNC(void, MCU_PRIVATE_CODE) Mcu_CLMStop(void);
extern FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLMRestart(uint32 LulMoscsValue, const uint32 aaSystemClockValue[],
                                                                                     const uint32 aaPllDivisionValue[]);
#endif
#endif

#if (MCU_DMON_DIAG_OPERATION == STD_ON)
#if (MCU_CLMA_OPERATION == STD_ON)
extern FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLMEnable(void);
#endif
#endif

#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

#endif  /* MCU_CLM_LLDRIVER_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
