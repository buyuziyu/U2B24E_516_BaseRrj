/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_STB_LLDriver.h                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* The header file of Mcu_STB_LLDriver.c                                                                              */
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
 *                        As part of U2Cx device support, following changes are made:
 *                        - Change MCU_START/STOP_SEC_CONFIG_DATA_32 to 
 *                        MCU_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
 *                        - Update Mcu_StbHwInfoType to add pRRAM_SDMReg and pAWOPSMReg
 *                        As part of QAC 9.5.0 support, following changes are made:
 *                        - Remove the redundant message 1534 and 1536
 * 2.0.1:  10/10/2023   : Add pPWRGD_CNTReg to Mcu_StbHwInfoType
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

#ifndef MCU_STB_LLDRIVER_H
#define MCU_STB_LLDRIVER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* Functionality related to R4.0 */
/* AUTOSAR release version information */
#define MCU_STB_LLDRIVER_AR_RELEASE_MAJOR_VERSION MCU_AR_RELEASE_MAJOR_VERSION
#define MCU_STB_LLDRIVER_AR_RELEASE_MINOR_VERSION MCU_AR_RELEASE_MINOR_VERSION
#define MCU_STB_LLDRIVER_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION

/*  Module software version information */
#define MCU_STB_LLDRIVER_SW_MAJOR_VERSION   MCU_SW_MAJOR_VERSION
#define MCU_STB_LLDRIVER_SW_MINOR_VERSION   MCU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                     Global Symbols                                                 **
***********************************************************************************************************************/
/*Wake-Up Factor Clear Registers*/
#define MCU_CLEAR_WAKE_UP_FACTOR                            (uint32)0xFFFFFFFFUL

/* Wakeup setting status before transition to standby mode */
#define MCU_NO_WAKEUP_SET                                   (uint8)0x00

#define MCU_STOP_WAKEUP_SET                                 (uint8)0x01

#define MCU_CYCLICSTOP_WAKEUP_SET                           (uint8)0x02

#define MCU_DEEPSTOP_WAKEUP_SET                             (uint8)0x03

#define MCU_STBC0STPT_TRANSITION_TO_STOP_VALUE              (uint32)0x00000001UL
#define MCU_STBC0PSC_TRANSITION_TO_DEEPSTOP_VALUE           (uint32)0x00000002UL

/* Number of re-try times to enter standby mode */
#define MCU_MODE_TRANSITION_WAIT_CNT_NUM                    (uint16)0xFFFFU

#define MCU_MOSC_STOP_IN_STANDBYMODE                        (uint32)0x00000000UL

#define MCU_STB_DISABLE_REG_PROTECT_VALUE                   (uint32)0xA5A5A501UL
#define MCU_STB_ENABLE_REG_PROTECT_VALUE                    (uint32)0xA5A5A500UL

/***********************************************************************************************************************
**                                            Global Data Types                                                       **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                      Power Mode Setting Data Structure                                             **
***********************************************************************************************************************/
/* Structure for  wake-up factor registers */
typedef struct STag_Mcu_WakeUpHwInfoType                                                                                /* PRQA S 3630 # JV-01 */
{
  /* Pointer to wake-up factor registers (WUF) */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pWUFRegsAddr;                                                               /* PRQA S 3432 # JV-01 */
  /* Pointer to Wake-up Factors Mark registers (WUFMSK) */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pWUFMSKRegsAddr;                                                            /* PRQA S 3432 # JV-01 */
  /* Pointer to wake-up factor clear registers (WUFC) */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pWUFCRegsAddr;                                                              /* PRQA S 3432 # JV-01 */
} Mcu_WakeUpHwInfoType;

typedef struct STag_Mcu_StbHwInfoType                                                                                   /* PRQA S 3630 # JV-01 */
{
  /* Pointer to Standby controller Register Key Code Protection Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pSTBCKCPROTReg;                                                             /* PRQA S 3432 # JV-01 */
  /* Pointer to Power Stop Trigger Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pSTBC0STPTReg;                                                              /* PRQA S 3432 # JV-01 */
  /* Pointer to Power Save Control Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pSTBC0PSCReg;                                                               /* PRQA S 3432 # JV-01 */
  /* Pointer to Power Good Counter Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pPWRGD_CNTReg;                                                              /* PRQA S 3432 # JV-01 */
  /* Pointer to Shutdown selection Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pRRAM_SDMReg;                                                               /* PRQA S 3432 # JV-01 */
  /* Pointer to Power supply mode selection Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pAWOPSMReg;                                                                 /* PRQA S 3432 # JV-01 */
  } Mcu_StbHwInfoType;

typedef struct STag_Mcu_WUFMONHwInfoType                                                                                /* PRQA S 3630 # JV-01 */
{
  /* Pointer to Wake-Up Factor Monitor Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pWUFMONRegsAddr;                                                            /* PRQA S 3432 # JV-01 */
} Mcu_WUFMONHwInfoType;

#if (MCU_RELEASEIOBUFFERHOLD_API == STD_ON)
typedef struct STag_Mcu_IOBufferHoldHwInfoType                                                                          /* PRQA S 3630 # JV-01 */
{
  /* Pointer to I/O Buffer Hold Control Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pIOBufHoldReg;                                                              /* PRQA S 3432 # JV-01 */
  /* Pointer to I/O Buffer Hold Control Register 1 */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pIOBufHold1Reg;                                                             /* PRQA S 3432 # JV-01 */
  /* Pointer to I/O Buffer Hold Control Register 2 */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pIOBufHold2Reg;                                                             /* PRQA S 3432 # JV-01 */
} Mcu_IOBufferHoldHwInfoType;
#endif /* MCU_RELEASEIOBUFFERHOLD_API == STD_ON */

typedef struct STag_Mcu_ModeSettingType
{
  /* Power down modes macro types*/
  Mcu_StandbyModeType enModeType;
  #if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
  uint32 aaWakeUpFactor[MCU_NUMBER_WAKEUP_FACTOR];
  #endif /* MCU_MODE_TRANSITION_SUPPORT == STD_ON */
} Mcu_ModeSettingType;

/***********************************************************************************************************************
**                                        Extern declarations for Global Data                                         **
***********************************************************************************************************************/
#define MCU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Mcu_MemMap.h"
/* Global array for MCU Mode Setting Configuration */
extern CONST(Mcu_ModeSettingType, MCU_CONFIG_DATA) Mcu_GaaModeSetting[];                                                /* PRQA S 3684 # JV-01 */
#define MCU_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Mcu_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

extern FUNC(void, MCU_PRIVATE_CODE) Mcu_STBSetMode (Mcu_ModeType LddMode);

#if (MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON)
extern FUNC(void, MCU_PRIVATE_CODE) Mcu_STBClearWakeUpFactor (void);

extern FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_STBSetWakeUpFactor (Mcu_ModeType LddMode);
#endif /* MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON */

#if (MCU_GETWAKEUPFACTOR_API == STD_ON)
extern FUNC(void, MCU_PRIVATE_CODE) Mcu_STBGetWakeUpFactor
  (P2VAR(Mcu_WakeUpFactorInfoType, AUTOMATIC, MCU_APPL_DATA) LpMcuWakeupfactorinfo);                                    /* PRQA S 3432 # JV-01 */
#endif /* MCU_GETWAKEUPFACTOR_API == STD_ON */

#if (MCU_RELEASEIOBUFFERHOLD_API == STD_ON)
extern FUNC(void, MCU_PRIVATE_CODE) Mcu_STBReleaseIoBufferHold (void);
#endif /* MCU_RELEASEIOBUFFERHOLD_API == STD_ON */

#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

#endif  /* MCU_STB_LLDRIVER_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
