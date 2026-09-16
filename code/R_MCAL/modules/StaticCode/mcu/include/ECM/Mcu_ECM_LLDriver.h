/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_ECM_LLDriver.h                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* The header file of Mcu_ECM_LLDriver.c                                                                              */
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
 *                        - Update range of array aaFEIntEnable, aaEIIntEnable, aaEIDCLSIntEnable, aaEIC8IntEnable
 *                        - Add pEcmCommonRegAfterInitRramSetting and pEcmCommonDelayTimerRegAfterInitRramSetting
 *                        to Mcu_EcmSettingType
 *                        - Add marco MCU_ECM_SETTING_AFTER_RAMINIT_RRAM
 *                        - Change aaEcmRegisterValue[MCU_ECM_CORE_NUM] to aaEcmRegisterValue[MCU_ECM_ERROR_TRIGGER_NUM]
 *                        As part of QAC 9.5.0 support, following changes are made:
 *                        - Remove redundant QAC message 1534 and 1536
 * 2.0.1:  10/10/2023   : Change "MCU_START/STOP_SEC_DBTOC_DATA_UNSPECIFIED"
 *                        to "MCU_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED"
 * 2.0.0:  04/08/2023   : Remove redundant QAC message 0779
 *         10/07/2023   : Remove redundant QAC message 3630, 1039
 * 1.4.5:  06/01/2023   : As new Mcu structure:
 *                        - Add Global Data Types Mcu_EcmCommonRegType, Mcu_EcmErrorOutClrConfigRegType,
 *                          Mcu_EcmFEINTRegType, Mcu_EcmErrorOutClearRegType, Mcu_EcmHwInfoType
 *                        - Update Global Data Types Mcu_EcmSettingType
 * 1.4.3:  13/04/2022   : Update SW-VERSION to 1.4.3
 * 1.3.1:  02/07/2021   : Add QAC message 9.5.0
 *                        Format source code to 120 characters
 *                        Improve Violation tag (remove START/END) 
 *         12/05/2021   : Insert space before and after a binary operator
 *                        with the emphasis on readability.
 *         07/05/2021   : As per ARDAACL-145, Remove redundant declaration of Mcu_HW_CheckEcmClmaErrors,
 *                        Mcu_HW_ClearErrorGroupStatus, Mcu_HW_GetMasterErrorGroupStatus,
 *                        Mcu_HW_GetCheckerErrorGroupStatus
 * 1.3.0:  25/11/2020   : Release
 * 1.2.0:  17/07/2020   : Release
 * 1.1.0:  19/06/2020   : Release
 * 1.0.0:  10/01/2020   : Initial Version
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

#ifndef MCU_ECM_LLDRIVER_H
#define MCU_ECM_LLDRIVER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* Functionality related to R4.0 */
/* AUTOSAR release version information */
#define MCU_ECM_LLDRIVER_AR_RELEASE_MAJOR_VERSION MCU_AR_RELEASE_MAJOR_VERSION
#define MCU_ECM_LLDRIVER_AR_RELEASE_MINOR_VERSION MCU_AR_RELEASE_MINOR_VERSION
#define MCU_ECM_LLDRIVER_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION

/*  Module software version information */
#define MCU_ECM_LLDRIVER_SW_MAJOR_VERSION   MCU_SW_MAJOR_VERSION
#define MCU_ECM_LLDRIVER_SW_MINOR_VERSION   MCU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                     Global Symbols                                                 **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                            Global Data Types                                                       **
***********************************************************************************************************************/
/* IMR0 register EIC8 */
#define MCU_ECM_INT_MASK_EIC8_VALUE                         (uint32)0x00000100UL
/* IMR0 register EIC9 */
#define MCU_ECM_INT_MASK_EIC9_VALUE                         (uint32)0x00000200UL
/* ECM Controller KeyCode Protection */
#define MCU_ECM_DISABLE_REG_PROTECT_VALUE                   (uint32)0xA5A5A501UL
#define MCU_ECM_ENABLE_REG_PROTECT_VALUE                    (uint32)0xA5A5A500UL

#define MCU_ECM_DTMCTL_DELAYTIMER_WR_STATUS_MASK            (uint32)0x00000011UL
#define MCU_ECM_DTMCTL_DELAYTIMER_NOT_STARTED               (uint32)0x00000000UL
#define MCU_ECM_DTMCTL_DELAYTIMER_STARTED                   (uint32)0x00000011UL

/* MCU_SetEcmRegister */
#define MCU_ECM_SETTING_INIT                                (uint8)0x00U
#define MCU_ECM_SETTING_AFTER_RAMINIT_LRAM                  (uint8)0x01U
#define MCU_ECM_SETTING_AFTER_RAMINIT_CRAM                  (uint8)0x02U
#define MCU_ECM_SETTING_AFTER_RAMINIT_RRAM                  (uint8)0x03U

#define MCU_ECM_ECMPEM_ERROR_MASK_VALUE                     (uint32)0x00000003UL
#define MCU_ECM_ECMIRCFG_ECM_COMPERR_MASK                   (uint32)0x00100000UL
#define MCU_ECM_ECMEMK_ALL_MASK                             (uint32)0xFFFFFFFFUL

#define MCU_ECM_DTMCTL_DELAYTIMER_ENABLE_VALUE              (uint32)0x00000001UL

#define MCU_ECM_ESSTR_COUNT                                 (uint8)0x05U

/* EIC register EIMK mask value */
#define MCU_ECM_EIC_L_EIMK_MASK                             (uint8)0x80U

/* ECM PEx FEINT mask */
#define MCU_ECM_INT_MASK_FE_VALUE                           (uint32)0x00000004UL

/* ECM PEID bit mask in EIBD8 register */
#define MCU_ECM_EIBD8_PEID_MASK                             (uint32)0x00000007UL

/* ECM PEID bit mask in EIBD9 register */
#define MCU_ECM_EIBD9_PEID_MASK                             (uint32)0x00000007UL

/* ECM PEID bit mask in FIBD0 register */
#define MCU_ECM_FIBD0_PEID_MASK                             (uint32)0x00000007UL

#define MCU_ECM_ETCCFG_COUNTER_UPDATING                     (uint32)0x01000000UL
#define MCU_ECM_ETCCFG_COUNTER_CMPW_MASK                    (uint32)0x01000000UL

/* ECM read ECMEOCCFG register max try value */
#define MCU_ECM_EOCCFG_CHECK_RETRY_MAX                      (uint8)0xFFU

/* ECM read ECMETCCFGn register max try value */
#define MCU_ECM_ETCCFG_CHECK_RETRY_MAX                      (uint8)0xFFU

#define MCU_ECM_FEINTMSK_OFFSET                             (uint32)0x00000040UL

/***********************************************************************************************************************
**                                      Error Control Module Structure                                                **
***********************************************************************************************************************/
/* Structure for MCU Status */
typedef struct STag_Mcu_EcmStatusType
{
  uint32 ulEcmBit;
  Mcu_ResetType enMcuRst;
} Mcu_EcmStatusType;

typedef struct STag_Mcu_EcmCommonRegType                                                                                /* PRQA S 3630 # JV-01 */
{
  /* Pointer to address of ECM Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pEcmCommonReg;                                                              /* PRQA S 3432 # JV-01 */

  /* ECM Register Value */
  uint32 aaEcmRegisterValue[MCU_ECM_COMMON_REG_NUM];
} Mcu_EcmCommonRegType;

typedef struct STag_Mcu_EcmErrorOutClrConfigRegType                                                                     /* PRQA S 3630 # JV-01 */
{
  /* Pointer to address of ECM Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pEcmErrorOutClrConfigReg;                                                   /* PRQA S 3432 # JV-01 */

  /* ECM Register Value */
  uint32 aaEcmRegisterValue[MCU_ECM_ERROR_TRIGGER_NUM];
} Mcu_EcmErrorOutClrConfigRegType;

typedef struct STag_Mcu_EcmFEINTRegType                                                                                 /* PRQA S 3630 # JV-01 */
{
  /* Pointer to address of FEINT Status Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pFEINTFReg;                                                                 /* PRQA S 3432 # JV-01 */

  /* Pointer to address of FEINT Status Clear Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pFEINTCReg;                                                                 /* PRQA S 3432 # JV-01 */

} Mcu_EcmFEINTRegType;

typedef struct STag_Mcu_EcmErrorOutClearRegType                                                                         /* PRQA S 3630 # JV-01 */
{
  /* Pointer to address of ECM Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pEcmErrorOutClearReg;                                                       /* PRQA S 3432 # JV-01 */

  /* ECM Error Out Clear Value */
  uint32 ulEcmErrorOutClearValue;

  /* ECM Error Out Clear Register Offset */
  uint32 ulEcmErrorOutClearOffset;

  /* ECM Error Out Z number */
  uint8 ucEcmErrorOutZNum;

  /* ECM Common Register number */
  uint8 ucEcmCommonRegNum;

  /* Indicate whether Disable Interrupt is needed */
  boolean blEcmDisableInt;

} Mcu_EcmErrorOutClearRegType;

typedef struct STag_Mcu_EcmHwInfoType                                                                                   /* PRQA S 3630 # JV-01 */
{
  /* Pointer to address of EI Level Interrupt Control Register 8 */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pEIC8Reg;                                                                   /* PRQA S 3432 # JV-01 */

  /* Pointer to address of EI Level Interrupt Control Register 9 */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pEIC9Reg;                                                                   /* PRQA S 3432 # JV-01 */

  /* Pointer to address of EI level Interrupt Mask Register 0 */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pIMR0Reg;                                                                   /* PRQA S 3432 # JV-01 */

  /* Pointer to address of EI Level Interrupt Mask Register 8 */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pEIBD8Reg;                                                                  /* PRQA S 3432 # JV-01 */

  /* Pointer to address of EI Level Interrupt Mask Register 9 */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pEIBD9Reg;                                                                  /* PRQA S 3432 # JV-01 */

  /* Pointer to address of FE level Interrupt Bind Register 0 */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pFIBD0Reg;                                                                  /* PRQA S 3432 # JV-01 */

  /* Pointer to address of FEINT Event Mask  Register PE0 */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pFEINTMSK0Reg;                                                              /* PRQA S 3432 # JV-01 */

  /* Pointer to address of ECM Error Pulse Configuration Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECMEPCFGReg;                                                               /* PRQA S 3432 # JV-01 */

  /* Pointer to address of ECM Error Mask Register 0 */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECMEMK0Reg;                                                                /* PRQA S 3432 # JV-01 */

  /* Pointer to address of ECM Error Source Status Clear Trigger Register 0 */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECMESSTC0Reg;                                                              /* PRQA S 3432 # JV-01 */

  /* Pointer to address of ECM Key Code Protection Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECMKCPROTReg;                                                              /* PRQA S 3432 # JV-01 */

  /* Pointer to address of ECM Delay Timer Control Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECMDTMCTLReg;                                                              /* PRQA S 3432 # JV-01 */

  /* Pointer to address of ECM Delay Timer Compare Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECMDTMCMPReg;                                                              /* PRQA S 3432 # JV-01 */

  /* Pointer to address of ECM Error Output Clear Invalidation Configuration Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECMEOCCFGReg;                                                              /* PRQA S 3432 # JV-01 */

  /* Pointer to address of ECM Error Trigger n0 Clear Invalidation Configuration Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECMETCCFG0Reg;                                                             /* PRQA S 3432 # JV-01 */

  /* Pointer to address of ECM Pseudo Error Mask  Register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECMPEMReg;                                                                 /* PRQA S 3432 # JV-01 */

  /* Pointer to address of ECM Master Error Source Status Register 0 */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECMMESSTR0Reg;                                                             /* PRQA S 3432 # JV-01 */

  /* Pointer to address of ECM Checker Error Source Status Register 0 */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECMCESSTR0Reg;                                                             /* PRQA S 3432 # JV-01 */

  /* Pointer to address of ECM Master Error Source Status Register j */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECMMESSTRjReg;                                                             /* PRQA S 3432 # JV-01 */

  /* Pointer to address of ECM Checker Error Source Status Register j */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pECMCESSTRjReg;                                                             /* PRQA S 3432 # JV-01 */

} Mcu_EcmHwInfoType;

typedef struct STag_Mcu_EcmSettingType
{
  /* ECM Error Output Mode setting value */
  uint8 ucEcmErrorOutputMode;

  /* ECM delay timer control value */
  uint8 ucEcmDelayTimerCtrl;

  /* ECM delay timer overflow setting value */
  uint32 ulEcmDelayTimerOverflowValue;

  /* ECM ErrorOutput Clear invalidation Register value */
  uint32 ulEcmErrorOutClrMaskCntValue;

  /* ECM Internal Reset setting for ECMIRCFGn register value */
  uint32 aaEcmInternalResetRegValue[MCU_ECM_COMMON_REG_NUM];

  /* Indicate whether FE Level Interrupt is Enable */
  boolean aaFEIntEnable[MCU_ECM_CORE_NUM][MCU_ECM_SETTING_NUM];

  /* Indicate whether EI Level Interrupt is Enable */
  boolean aaEIIntEnable[MCU_ECM_SETTING_NUM];

  /* Indicate whether EI DCLS Level Interrupt is Enable */
  boolean aaEIDCLSIntEnable[MCU_ECM_SETTING_NUM];

  /* Indicate whether EIC8 Interrupt is Enable */
  boolean aaEIC8IntEnable[MCU_ECM_SETTING_NUM];

  /* Pointer to ECM Common Register Setting */
  P2CONST(Mcu_EcmCommonRegType, AUTOMATIC, MCU_CONFIG_DATA) pEcmCommonRegInitSetting;

  /* Pointer to ECM Common Register Setting after Init LRAM */
  P2CONST(Mcu_EcmCommonRegType, AUTOMATIC, MCU_CONFIG_DATA) pEcmCommonRegAfterInitLramSetting;

  /* Pointer to ECM Common Register Setting after Init CRAM */
  P2CONST(Mcu_EcmCommonRegType, AUTOMATIC, MCU_CONFIG_DATA) pEcmCommonRegAfterInitCramSetting;

  #if (MCU_RETENTION_RAM_SETTING == STD_ON)
  /* Pointer to ECM Common Register Setting after Init Retention RAM */
  P2CONST(Mcu_EcmCommonRegType, AUTOMATIC, MCU_CONFIG_DATA) pEcmCommonRegAfterInitRramSetting;
  #endif /* MCU_RETENTION_RAM_SETTING == STD_ON */

  /* Pointer to ECM Common Delay Timer Register Setting */
  P2CONST(Mcu_EcmCommonRegType, AUTOMATIC, MCU_CONFIG_DATA) pEcmCommonDelayTimerRegInitSetting;

  /* Pointer to ECM Common Delay Timer Register Setting after Init LRAM */
  P2CONST(Mcu_EcmCommonRegType, AUTOMATIC, MCU_CONFIG_DATA) pEcmCommonDelayTimerRegAfterInitLramSetting;

  /* Pointer to ECM Common Delay Timer Register Setting after Init CRAM */
  P2CONST(Mcu_EcmCommonRegType, AUTOMATIC, MCU_CONFIG_DATA) pEcmCommonDelayTimerRegAfterInitCramSetting;

  #if (MCU_RETENTION_RAM_SETTING == STD_ON)
  /* Pointer to ECM Common Delay Timer Register Setting after Init Retention RAM */
  P2CONST(Mcu_EcmCommonRegType, AUTOMATIC, MCU_CONFIG_DATA) pEcmCommonDelayTimerRegAfterInitRramSetting;
  #endif /* MCU_RETENTION_RAM_SETTING == STD_ON */

  /* Pointer to ECM Error Out Clear Config Register Setting */
  P2CONST(Mcu_EcmErrorOutClrConfigRegType, AUTOMATIC, MCU_CONFIG_DATA) pEcmErrorOutClrConfigRegSetting;

  /* Pointer to ECM Error Out Clear Register Type Setting */
  P2CONST(Mcu_EcmErrorOutClearRegType, AUTOMATIC, MCU_CONFIG_DATA) pEcmErrorOutClearRegTypeSetting;

  /* Pointer to Ram error mask */
  uint32 aaEcmRamErrMask[MCU_ECM_COMMON_REG_NUM];

  /* Pointer to ECM FEINT register address */
  P2CONST(Mcu_EcmFEINTRegType, AUTOMATIC, MCU_CONFIG_DATA) pEcmFEINTRegsAddr;

  /* Pointer to ECM FEINT type setting */
  uint32 aaEcmFEIntTypeSettingValue[MCU_ECM_CORE_NUM][MCU_ECM_COMMON_REG_NUM];

  /* Pointer to ECM FEINT setting */
  uint32 aaEcmFEIntSettingValue[MCU_ECM_CORE_NUM][MCU_ECM_COMMON_REG_NUM];

  /* Pointer to ECM EIC8 Interrupt type setting */
  uint32 aaEcmEIC8IntTypeSettingValue[MCU_ECM_CORE_NUM][MCU_ECM_COMMON_REG_NUM];

  /* Pointer to ECM EIC8 Interrupt setting */
  uint32 aaEcmEIC8IntSettingValue[MCU_ECM_CORE_NUM][MCU_ECM_COMMON_REG_NUM];

  /* Pointer to ECM EIC9 Interrupt type setting */
  uint32 aaEcmEIC9IntTypeSettingValue[MCU_ECM_CORE_NUM][MCU_ECM_COMMON_REG_NUM];

  /* Pointer to ECM EIC9 Interrupt setting */
  uint32 aaEcmEIC9IntSettingValue[MCU_ECM_CORE_NUM][MCU_ECM_COMMON_REG_NUM];

} Mcu_EcmSettingType;

/***********************************************************************************************************************
**                                          Extern declarations for Global Data                                       **
***********************************************************************************************************************/
#if (MCU_ECM_OPERATION == STD_ON)
#define MCU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Mcu_MemMap.h"
/* Global array for the Ecm setting configuration */
extern CONST(Mcu_EcmSettingType, MCU_CONFIG_DATA)Mcu_GaaEcmSetting[];                                                   /* PRQA S 3684 # JV-01 */
extern CONST(Mcu_EcmStatusType, MCU_CONFIG_DATA)Mcu_GaaMcuEcmErrMapTable[MCU_ECM_COMMON_REG_NUM][32];
#define MCU_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Mcu_MemMap.h"
#endif /* End of (MCU_ECM_OPERATION == STD_ON) */

/***********************************************************************************************************************
**                                         Function Prototypes                                                        **
***********************************************************************************************************************/
#if (MCU_ECM_OPERATION == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

extern FUNC(Std_ReturnType, MCU_PRIVATE_CODE)Mcu_ECMSetEcmRegister(CONST(uint8, MCU_CONST) LucEcmSetType);

extern FUNC(Mcu_ResetType, MCU_PRIVATE_CODE)Mcu_ECMGetEcmResetReasonValue(void);

#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"
#endif /* End of (MCU_ECM_OPERATION == STD_ON) */
#endif  /* MCU_ECM_LLDRIVER_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
