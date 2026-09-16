/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_VMN_LLDriver.h                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* The header file of Mcu_VMN_LLDriver.c                                                                              */
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
 *                        - Remove the redundant message 1534 and 1536
 * 2.0.1:  10/10/2023   : Change "MCU_START/STOP_SEC_DBTOC_DATA_UNSPECIFIED"
 *                        to "MCU_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED"
 * 2.0.0:  04/08/2023   : Remove redundant QAC message 0791
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
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#ifndef MCU_VMN_LLDRIVER_H
#define MCU_VMN_LLDRIVER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* Functionality related to R4.0 */
/* AUTOSAR release version information */
#define MCU_VMN_LLDRIVER_AR_RELEASE_MAJOR_VERSION MCU_AR_RELEASE_MAJOR_VERSION
#define MCU_VMN_LLDRIVER_AR_RELEASE_MINOR_VERSION MCU_AR_RELEASE_MINOR_VERSION
#define MCU_VMN_LLDRIVER_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION

/*  Module software version information */
#define MCU_VMN_LLDRIVER_SW_MAJOR_VERSION   MCU_SW_MAJOR_VERSION
#define MCU_VMN_LLDRIVER_SW_MINOR_VERSION   MCU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                     Global Symbols                                                 **
***********************************************************************************************************************/

/* VMN,DMON Controller KeyCode Protection */
#define MCU_VMON_DISABLE_REG_PROTECT_VALUE              (uint32)0xA5A5A501UL
#define MCU_VMON_ENABLE_REG_PROTECT_VALUE               (uint32)0xA5A5A500UL
#define MCU_DMON_DISABLE_REG_PROTECT_VALUE              (uint32)0xA5A5A501UL
#define MCU_DMON_ENABLE_REG_PROTECT_VALUE               (uint32)0xA5A5A500UL

#define MCU_VMON_VMONF_NO_VIOLATION                     (uint8)0x00
#define MCU_VMON_VMONDMASK_ALL_CLEAR_VALUE              (uint8)0x00
#define MCU_VMON_VMONDIAG_NO_DETECTION_ENABLE_VALUE     (uint8)0x00
#define MCU_VMON_VMONDIAGME_CANNOT_ENABLE_VALUE         (uint8)0x01

#define MCU_DMON_DMONF_NO_ERROR_OCCURRED                (uint32)0x00000000
#define MCU_DMON_DMONF_ERROR_OCCURRED                   (uint32)0x00000001
#define MCU_DMON_DMONFC_CLEAR_VALUE                     (uint32)0x00000001
#define MCU_DMON_DMONDELOWDELAY_DETECTION_ENABLE        (uint32)0x00000001
#define MCU_DMON_DMONDIAG_ERROR_INJECTION_ENABLE        (uint32)0x00000001
#define MCU_DMON_DMONDIAG_ERROR_INJECTION_DISABLE       (uint32)0x00000000
#define MCU_DMON_DMONDIAGME_CANNOT_ENABLE_VALUE         (uint32)0x00000001
#define MCU_DMON_DMONDIAGME_CAN_ENABLE_VALUE            (uint32)0x00000000

#define MCU_DMONCIRREN_BIT_MASK                         (uint32)0x000000A0

#define MCU_DMON_DMONDE_FILTER_LOWDELAY_DETECTION_ENABLE (uint32)0x00000009

#define MCU_DMONTEST_RESET_ASSERT_VALUE                 (uint32)0x00000001
#define MCU_DMONTEST_RESET_RELEASE_VALUE                (uint32)0x00000000

/* Number of re-try to clear MCU_VMONF using MCU_VMNFC */
#define MCU_VMONDIAG_CLEARRETRY_MAX                     (uint16)0xFFFFU
#define MCU_DMONDIAG_CLEARRETRY_MAX                     (uint16)0xFFFFU

/***********************************************************************************************************************
**                                            Global Data Types                                                       **
***********************************************************************************************************************/

#if (MCU_VMON_DIAG_OPERATION == STD_ON)
typedef struct STag_Mcu_VmonOPBT4SettingType                                                                            /* PRQA S 3630 # JV-01 */
{
  /* OPBT4 detection enable bit position */
  uint32 ulVmonOPBT4BitPosition;
  /* VMONF detection flag bit position */
  uint8 ucVmonVMONFBitPosition;
} Mcu_VmonOPBT4SettingType;

typedef struct STag_Mcu_VmonSettingType
{
  /* ISOVDD/VDD Detection Enable Register Setting Value */
  uint8 ucVMONISOVDDDEValue;
  /* AWOVDD/ISOVDD2 Detection Enable Register Setting Value */
  uint8 ucVMONVDD2DEValue;
  /* VCC Detection Enable Register Setting Value */
  uint8 ucVMONVCCDEValue;
  /* E0VCC/EVCC Detection Enable Register Setting Value */
  uint8 ucVMONE0VCCDEValue;
  /* Pointer to VmonOPBT4Setting */
  P2CONST(Mcu_VmonOPBT4SettingType, AUTOMATIC, MCU_CONFIG_DATA) pVmonOPBT4Setting;
} Mcu_VmonSettingType;

typedef struct STag_Mcu_VmonHwInfoType                                                                                  /* PRQA S 3630 # JV-01 */
{
  /* The address of VMON Register Key Code Protection Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pVMONKCPROTReg;                                                             /* PRQA S 3432 # JV-01 */
  /* The address of VMONF Clear Register */
  volatile P2VAR(uint8, TYPEDEF, REGSPACE) pVMONFCReg;                                                                  /* PRQA S 3432 # JV-01 */
  /* The address of VMON Factor Register */
  volatile P2VAR(uint8, TYPEDEF, REGSPACE) pVMONFReg;                                                                   /* PRQA S 3432 # JV-01 */
  /* The address of VMON DIAG Monitor Enable Register */
  volatile P2VAR(uint8, TYPEDEF, REGSPACE) pVMONDIAGMEReg;                                                              /* PRQA S 3432 # JV-01 */
  /* The address of VMON DIAG Monitor Enable Write Register */
  volatile P2VAR(uint8, TYPEDEF, REGSPACE) pVMONDIAGMEWReg;                                                             /* PRQA S 3432 # JV-01 */
  /* The address of VMON Detection Output Diagnosis Mask Register */
  volatile P2VAR(uint8, TYPEDEF, REGSPACE) pVMONDMASKReg;                                                               /* PRQA S 3432 # JV-01 */
  /* The address of VMONDIAG Mode Setting Register */
  volatile P2VAR(uint8, TYPEDEF, REGSPACE) pVMONDIAGReg;                                                                /* PRQA S 3432 # JV-01 */
  /* The address of ISOVDD/VDD Detection Enable Register */
  volatile P2VAR(uint8, TYPEDEF, REGSPACE) pISOVDDDEReg;                                                                /* PRQA S 3432 # JV-01 */
  /* The address of AWOVDD/ISOVDD2 Detection Enable Register */
  volatile P2VAR(uint8, TYPEDEF, REGSPACE) pVDD2DEReg;                                                                  /* PRQA S 3432 # JV-01 */
  /* The address of VCC Detection Enable Register */
  volatile P2VAR(uint8, TYPEDEF, REGSPACE) pVCCDEReg;                                                                   /* PRQA S 3432 # JV-01 */
  /* The address of E0VCC/EVCC Detection Enable Register */
  volatile P2VAR(uint8, TYPEDEF, REGSPACE) pE0VCCDEReg;                                                                 /* PRQA S 3432 # JV-01 */
  /* The address of Option Byte 4 Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pOPBT4Reg;                                                                  /* PRQA S 3432 # JV-01 */
} Mcu_VmonHwInfoType;
#endif /* MCU_VMON_DIAG_OPERATION == STD_ON */

#if (MCU_DMON_DIAG_OPERATION == STD_ON)
typedef struct STag_Mcu_DmonSettingType
{
  /* DMON DMONDE Register setting Value */
  uint32 ulDmonDMONDEValue;
  /* DMON DMONDE Register setting Value */
  uint32 ulDmonDMONFCRValue;
} Mcu_DmonSettingType;

typedef struct STag_Mcu_DmonHwInfoType                                                                                  /* PRQA S 3630 # JV-01 */
{
  /* The address of pDMONFReg Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pDMONFReg;                                                                  /* PRQA S 3432 # JV-01 */
  /* The address of DMONF Clear Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pDMONFCReg;                                                                 /* PRQA S 3432 # JV-01 */
  /* The address of  DMON DIAG Monitor Enable Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pDMONDIAGMEReg;                                                             /* PRQA S 3432 # JV-01 */
  /* The address of DMONDIAGME Write Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pDMONDIAGMEWReg;                                                            /* PRQA S 3432 # JV-01 */
  /* The address of DMON Detection Output Diagnosis Mask Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pDMONDMASKReg;                                                              /* PRQA S 3432 # JV-01 */
  /* The address of DMONDIAG Mode Setting Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pDMONDIAGReg;                                                               /* PRQA S 3432 # JV-01 */
  /* The address of DMON Detection Enable Registe Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pDMONDEReg;                                                                 /* PRQA S 3432 # JV-01 */
  /* The address of DMON Filter Control Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pDMONFCRReg;                                                                /* PRQA S 3432 # JV-01 */
  /* The address of Delay Monitor Test Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pDMONTESTReg;                                                               /* PRQA S 3432 # JV-01 */
  /* The address of DMON Register 0 Key Code Protection Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pDMONKCPROT0Reg;                                                            /* PRQA S 3432 # JV-01 */
  /* The address of DMON Register 2 Key Code Protection Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pDMONKCPROT2Reg;                                                            /* PRQA S 3432 # JV-01 */
} Mcu_DmonHwInfoType;
#endif /* MCU_DMON_DIAG_OPERATION == STD_ON */

/***********************************************************************************************************************
**                                     Extern declarations for Global Data                                            **
***********************************************************************************************************************/
#define MCU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Mcu_MemMap.h"

#if (MCU_VMON_DIAG_OPERATION == STD_ON)
/* Global array for the VMON setting configuration */
extern CONST(Mcu_VmonSettingType, MCU_CONFIG_DATA) Mcu_GaaVmonSetting[];                                                /* PRQA S 3684 # JV-01 */
#endif /* MCU_VMON_DIAG_OPERATION */

#if (MCU_DMON_DIAG_OPERATION == STD_ON)
/* Global array for the DMON setting configuration */
extern CONST(Mcu_DmonSettingType, MCU_CONFIG_DATA) Mcu_GaaDmonSetting[];                                                /* PRQA S 3684 # JV-01 */
#endif /* MCU_DMON_DIAG_OPERATION */

#define MCU_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Mcu_MemMap.h"


/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

#if (MCU_VMON_DIAG_OPERATION == STD_ON)
extern FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_VMNSetVoltageMonitorDiag(void);
#endif /* End of (MCU_VMON_DIAG_OPERATION == STD_ON) */

#if (MCU_DMON_DIAG_OPERATION == STD_ON)
extern FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_VMNSetDelayMonitorDiag(void);
#endif /* End of (MCU_DMON_DIAG_OPERATION == STD_ON) */


#if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
#if (MCU_DMON_DIAG_OPERATION == STD_ON)
extern FUNC(void, MCU_PRIVATE_CODE) Mcu_VMNStopDelayMonitor(void);
extern FUNC(void, MCU_PRIVATE_CODE) Mcu_VMNRestartDelayMonitor(void);
#endif /* End of (MCU_DMON_DIAG_OPERATION == STD_ON) */
#endif /* End of (MCU_MODE_TRANSITION_SUPPORT == STD_ON) */

#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"
#endif  /* MCU_VMN_LLDRIVER_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
