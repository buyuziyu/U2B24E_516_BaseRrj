/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_CLK_LLDriver.h                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* The header file of Mcu_CLK_LLDriver.c                                                                              */
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
 *                        As part of ARDAACL-53025, following changes are made:
 *                        - Remove marco MCU_CMUCLKEN_DISABLE_REG_TRIGGER, MCU_CMUCLKEN_ENABLE_REG_TRIGGER
 *                        - Remove marco MCU_CMUCLKEN_ENABLE_VALUE, MCU_CMUCLKEN_MASK
 * 2.3.1:  31/03/2025   : Update SW-VERSION for U2BxE Ver22.00.02 Release
 * 2.3.0:  28/02/2025   : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Release
 * 2.1.2:  31/10/2024   : Update SW-VERSION to 2.1.2
 *                        As part of GTM HWIP support, following changes are made:
 *                        - Add marco MCU_CCM_CMU_CLK_CFG_MASK, MCU_CCM_CMU_FXCLK_CFG_MASK, MCU_GTM_CLS_CLK_CFG_MASK
 *                        - Add marco MCU_CMUCLKEN_DISABLE_REG_TRIGGER, MCU_CMUCLKEN_ENABLE_REG_TRIGGER
 *                        - Add marco MCU_CMUCLKEN_MASK, MCU_CCMPROT_DISABLE_REG_TRIGGER, MCU_CCMPROT_ENABLE_REG_TRIGGER
 *                        - Add marco MCU_CMUCLKEN_DISABLE_VALUE, MCU_CMUCLKEN_ENABLE_VALUE
 *                        - Add Mcu_CCMSettingType and Mcu_CMUSettingType
 *                        - Update Mcu_ClockHwInfoType to add pCMUCLKENReg, pGTMCTRLReg, pGTMCLSCLKCFGReg
 *                        - Update Mcu_ClockSettingType to add pCcmSetting, pCmuSetting, ucNoOfCcmCfg, ulClsClkCfgValue
 * 2.1.1:  30/08/2024   : Update SW-VERSION to 2.1.1
 *                        As part of U2Cx device support, following changes are made:
 *                        - Add MCU_HSOSCTRMEN_ENABLE_TRIGGER, MCU_HSOSCFRETRMS_TRMST_MASK, MCU_HSOSCTRMCNT_CNT_MASK
 *                        - Add MCU_HSOSCFRETRMS_TRMST_END, MCU_HSOSCTRMPRODC_PROD_MASK, MCU_HSOSCTRMCODE_TCODE_MASK
 *                        - Update Mcu_ClockHwInfoType to add pPROT4Reg, pHSOSCTRMPRODCReg, pHSOSCTRMENReg,
 *                        MpHSOSCFRETRMSReg, pHSOSCTRMCNTReg, pHSOSCTRMCODEReg, pHSOSCUSERTRMSETReg
 *                        - Update Mcu_ClockSettingType to add blClkTrimmingSupported, ulHSOSCTRMPRODC,
 *                        ulClkTrimmingPeriod
 *                        - Add marco MCU_SOSCE_ENABLE_TRIGGER, MCU_SOSCE_DISABLE_TRIGGER, MCU_SOSCS_MOSCSTAB_MASK, 
 *                        MCU_SOSCS_MOSCEN_MASK, MCU_SOSCSTPM_MOSCSTPMASK, MCU_SOSCS_STOPPED
 *                        - Update Mcu_ClockHwInfoType to add pSubOscEReg and pSubOscSReg
 *                        - Update Mcu_ClockSettingType to add blSubOscUsed and ulSubOscStbCount
 *                        As part of QAC 9.5.0 support, following changes are made:
 *                        - Remove redundant QAC message 1536
 * 2.0.1:  20/10/2023   : Add marco "MCU_SSCG_SSMODE1_MASK"
 *                        Add pSSCGCReg and pSSCG1CReg to Mcu_ClockHwInfoType
 *                        Add ulSSCGC and ulSSCG1C to Mcu_ClockSettingType
 *         10/10/2023   : Change "MCU_START/STOP_SEC_DBTOC_DATA_UNSPECIFIED"
 *                        to "MCU_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED"
 * 2.0.0:  10/07/2023   : Remove redundant QAC message 3630
 * 1.4.5:  06/01/2023   : As new Mcu structure:
 *                        - Add Global Data Types Mcu_ClockHwInfoType, Mcu_ClockModeSettingType
 *                        - Update Global Data Types Mcu_ClockSettingType
 *                        - Add Function Prototypes Mcu_CLKShiftCpuSys
 * 1.4.3:  13/04/2022   : Update SW-VERSION to 1.4.3
 * 1.3.1:  02/07/2021   : Add QAC message 9.5.0
 *                        Format source code to 120 characters
 *                        Improve Violation tag (remove START/END)
 *         07/05/2021   : As per ARDAACL-145, Add preprocessor in declaration of Mcu_HW_SetClockGearUp function
 * 1.3.0:  25/11/2020   : Release
 * 1.2.0:  17/07/2020   : Release
 * 1.1.0:  19/06/2020   : Release
 * 1.0.3:  15/06/2020   : As per #274628 Mcu_HW_EnableCLMA, Update pre-compile macro
 * 1.0.2:  08/06/2020   : As per #261032 Update Mcu_HW_EnableCLMA to add return value
 * 1.0.1:  18/05/2020   : As per #267934
 *                        + Add 2 internal function
 *                        Mcu_HW_SetStandbyClockGearDown and Mcu_HW_SetStandbyClockGearUp to HW version up U2x 0.7
 *                        to 0.9
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

#ifndef MCU_CLK_LLDRIVER_H
#define MCU_CLK_LLDRIVER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* Functionality related to R4.0 */
/* AUTOSAR release version information */
#define MCU_CLK_LLDRIVER_AR_RELEASE_MAJOR_VERSION MCU_AR_RELEASE_MAJOR_VERSION
#define MCU_CLK_LLDRIVER_AR_RELEASE_MINOR_VERSION MCU_AR_RELEASE_MINOR_VERSION
#define MCU_CLK_LLDRIVER_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION

/*  Module software version information */
#define MCU_CLK_LLDRIVER_SW_MAJOR_VERSION   MCU_SW_MAJOR_VERSION
#define MCU_CLK_LLDRIVER_SW_MINOR_VERSION   MCU_SW_MINOR_VERSION

/* Clock Controller KeyCode Protection */
#define MCU_CKSC_DISABLE_REG_PROTECT_VALUE (uint32)0xA5A5A501UL
#define MCU_CKSC_ENABLE_REG_PROTECT_VALUE  (uint32)0xA5A5A500UL

/* Main OSC start/stop trigger */
#define MCU_MOSCE_ENABLE_TRIGGER           (uint32)0x00000001UL
#define MCU_MOSCE_DISABLE_TRIGGER          (uint32)0x00000002UL

/* Main OSC status */
#define MCU_MOSCS_MOSCSTAB_MASK            (uint32)0x00000002UL
#define MCU_MOSCS_MOSCEN_MASK              (uint32)0x00000001UL
#define MCU_MOSCSTPM_MOSCSTPMASK           (uint32)0x00000001UL
#define MCU_MOSCS_STOPPED                  (uint32)0x00000000UL

/* Sub OSC start/stop trigger */
#define MCU_SOSCE_ENABLE_TRIGGER           (uint32)0x00000001UL
#define MCU_SOSCE_DISABLE_TRIGGER          (uint32)0x00000002UL

/* Sub OSC status */
#define MCU_SOSCS_MOSCSTAB_MASK            (uint32)0x00000002UL
#define MCU_SOSCS_MOSCEN_MASK              (uint32)0x00000001UL
#define MCU_SOSCSTPM_MOSCSTPMASK           (uint32)0x00000001UL
#define MCU_SOSCS_STOPPED                  (uint32)0x00000000UL

/* PLL start/stop trigger */
#define MCU_PLLE_ENABLE_TRIGGER            (uint32)0x00000001UL
#define MCU_PLLE_DISABLE_TRIGGER           (uint32)0x00000002UL

/* PLL Status */
#define MCU_PLLS_CLK_STOPPED               (uint32)0x00000000UL
#define MCU_PLLCLKSTAB_MASK                (uint32)0x00000002UL

#define MCU_CKDS_SRCCLKDSYNC_OK            (uint32)0x00000002UL

/* HSIntOSC Status */
#define MCU_HSOSC_CLK_STABLE               (uint32)0x00000002UL

/* HSIntOSC Trimming Function Enable */
#define MCU_HSOSCTRMEN_ENABLE_TRIGGER      (uint32)0x00000001UL

/* HSIntOSC Trimming Function Status */
#define MCU_HSOSCFRETRMS_TRMST_MASK        (uint32)0x00000001UL
#define MCU_HSOSCFRETRMS_TRMST_END         (uint32)0x00000000UL

/* HSIntOSC Trimming Period Control */
#define MCU_HSOSCTRMPRODC_PROD_MASK        (uint32)0x00000003UL

/* HSIntOSC Trimming Counter */
#define MCU_HSOSCTRMCNT_CNT_MASK           (uint32)0x00007FFFUL

/* HSIntOSC Trimming Code */
#define MCU_HSOSCTRMCODE_TCODE_MASK        (uint32)0x000001FFUL

/* SSCG/SSC1G Status */
#define MCU_SSCG_SSMODE1_MASK              (uint32)0x00000200UL

/* Clock register mask */
#define MCU_CKSC_ALLMASK                   (uint32)0xFFFFFFFFUL
#define MCU_CKDS_SYNCMASK                  (uint32)0x00000002UL
#define MCU_CCM_CMU_CLK_CFG_MASK           (uint32)0x33333333UL
#define MCU_CCM_CMU_FXCLK_CFG_MASK         (uint32)0x0000000FUL
#define MCU_GTM_CLS_CLK_CFG_MASK           (uint32)0x00FFFFFFUL

/* Fout */
#define MCU_FOUTDIVS_SYNC                  (uint32)0x00000003UL
#define MCU_FOUTDIVC_STOPPED               (uint32)0x00000000UL

/* CMU clock enable/disable */
#define MCU_CMUCLKEN_DISABLE_VALUE         (uint32)0x00000000UL

/* CCM Controller KeyCode Protection */
#define MCU_CCMPROT_DISABLE_REG_TRIGGER   (uint32)0x00000000UL
#define MCU_CCMPROT_ENABLE_REG_TRIGGER    (uint32)0x00000001UL

/***********************************************************************************************************************
**                                            Global Data Types                                                       **
***********************************************************************************************************************/

/* Structure for the register information for clock controller */
typedef struct STag_Mcu_ClockHwInfoType                                                                                 /* PRQA S 3630 # JV-01 */
{
  /* The address of CLKKCPROT1 register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pPReg;                                                                      /* PRQA S 3432 # JV-01 */
  /* The address of PLLE register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pPllEReg;                                                                   /* PRQA S 3432 # JV-01 */
  /* The address of PLLS register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pPllSReg;                                                                   /* PRQA S 3432 # JV-01 */
  /* The address of MOSCE register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pMainOscEReg;                                                               /* PRQA S 3432 # JV-01 */
  /* The address of MOSCS register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pMainOscSReg;                                                               /* PRQA S 3432 # JV-01 */
  #if (MCU_SOSC_SUPPORT == STD_ON)
  /* The address of SOSCE register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pSubOscEReg;                                                                /* PRQA S 3432 # JV-01 */
  /* The address of SOSCS register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pSubOscSReg;                                                                /* PRQA S 3432 # JV-01 */
  /* The address of SOSCST register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pSubOscSTReg;                                                               /* PRQA S 3432 # JV-01 */
  #endif /* MCU_SOSC_SUPPORT == STD_ON */
  /* The address of HSOscS register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pHSOscSReg;                                                                 /* PRQA S 3432 # JV-01 */
  /* The address of Main OSC Stop Mask register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pMainOscSTPMReg;                                                            /* PRQA S 3432 # JV-01 */
  /* The address of HSOsc Stop Mask register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pHSOscSTPMReg;                                                              /* PRQA S 3432 # JV-01 */
  /* The address of PLL Stop Mask register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pPLLSTPMReg;                                                                /* PRQA S 3432 # JV-01 */
  #if (MCU_SSCG_ENABLE == STD_ON)
  /* The address of SSCG Control register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pSSCGCReg;                                                                  /* PRQA S 3432 # JV-01 */
  #endif /* MCU_SSCG_ENABLE == STD_ON */
  #if (MCU_SSCG1_ENABLE == STD_ON)
  /* The address of SSCG1 Control register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pSSCG1CReg;                                                                 /* PRQA S 3432 # JV-01 */
  #endif /* MCU_SSCG1_ENABLE == STD_ON */
  #if (MCU_CLOCK_TRIMMING_SUPPORT == STD_ON)
  /* The address of CLKKCPROT4 register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pPROT4Reg;                                                                  /* PRQA S 3432 # JV-01 */
  /* The address of HSOSCTRMPRODC register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pHSOSCTRMPRODCReg;                                                          /* PRQA S 3432 # JV-01 */
  /* The address of HSOSCTRMEN register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pHSOSCTRMENReg;                                                             /* PRQA S 3432 # JV-01 */
  /* The address of HSOSCFRETRMS register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pHSOSCFRETRMSReg;                                                           /* PRQA S 3432 # JV-01 */
  /* The address of HSOSCTRMCNT register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pHSOSCTRMCNTReg;                                                            /* PRQA S 3432 # JV-01 */
  /* The address of HSOSCTRMCODE register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pHSOSCTRMCODEReg;                                                           /* PRQA S 3432 # JV-01 */
  /* The address of HSOSCUSERTRMSET register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pHSOSCUSERTRMSETReg;                                                        /* PRQA S 3432 # JV-01 */
  #endif /* MCU_CLOCK_TRIMMING_SUPPORT == STD_ON */
  /* The number of clock source divider source */
  uint8 ucNoOfClkSrc;
  #if (MCU_GTM_SETTING == STD_ON)
  /* The address of CMU_CLK_EN register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCMUCLKENReg;                                                               /* PRQA S 3432 # JV-01 */
  /* The address of GTM_CTRL register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pGTMCTRLReg;                                                                /* PRQA S 3432 # JV-01 */
  /* The address of GTM_CLS_CLK_CFG register */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pGTMCLSCLKCFGReg;                                                           /* PRQA S 3432 # JV-01 */
  #endif /* MCU_GTM_SETTING == STD_ON */
} Mcu_ClockHwInfoType;

#if (MCU_GTM_SETTING == STD_ON)
/* Structure for CCM configuration registers */
typedef struct STag_Mcu_CCMSettingType                                                                                  /* PRQA S 3630 # JV-01 */
{
  /* The CCM protection register address */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCCMnPROTRegs;                                                              /* PRQA S 3432 # JV-01 */
  /* The CCM CMU clock configuration register address */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCCMnCLKCFGReg;                                                             /* PRQA S 3432 # JV-01 */
  /* The CCM CMU fixed clock configuration register address */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCCMnFXCLKCFGReg;                                                           /* PRQA S 3432 # JV-01 */
  /* The CCM CMU clock configuration register value */
  uint32 ulCcmClkCfgValue;
  /* The CCM CMU fixed clock configuration register value */
  uint32 ulCcmFxClkCtrlValue;
} Mcu_CCMSettingType;

/* Structure for CMU configuration registers */
typedef struct STag_Mcu_CMUSettingType                                                                                  /* PRQA S 3630 # JV-01 */
{
  /* The CMU configuration register address */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCmuCfgRegAddr;                                                             /* PRQA S 3432 # JV-01 */
  /* The CMU configuration register register value */
  uint32 ulCmuUnitRegValue;
  /* The CMU configuration register mask value */
  uint32 ulCmuUnitRegMaskValue;
} Mcu_CMUSettingType;
#endif /* MCU_GTM_SETTING == STD_ON */

/* Structure for system clock control and status registers */
typedef struct STag_Mcu_ClockModeSettingType                                                                            /* PRQA S 3630 # JV-01 */
{
  /* Clock Mode Select */
  uint32 ulCKSC;
  /* The address of system clock selector status registers */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCKSSAddr;                                                                  /* PRQA S 3432 # JV-01 */
  /* The address of system clock divider control registers */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCLKDCAddr;                                                                 /* PRQA S 3432 # JV-01 */
  /* The address of system clock divider status registers */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCLKDSAddr;                                                                 /* PRQA S 3432 # JV-01 */
} Mcu_ClockModeSettingType;

/* Structure for module clock selector/divider registers */
typedef struct STag_Mcu_ClockModuleSettingType                                                                          /* PRQA S 3630 # JV-01 */
{
  /* The address of clock selector control module registers */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCLKSCAddr;                                                                 /* PRQA S 3432 # JV-01 */
  /* The address of clock selector status module registers */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCLKSSAddr;                                                                 /* PRQA S 3432 # JV-01 */
  /* The address of clock divider control module registers */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCLKDCAddr;                                                                 /* PRQA S 3432 # JV-01 */
  /* The address of clock divider status module registers */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCLKDSAddr;                                                                 /* PRQA S 3432 # JV-01 */
  /* Clock selector control register Value */
  uint32 ulCKSCValue;
  /* Clock divider control register Value */
  uint32 ulCKDCValue;
  /* Clock module type */
  Mcu_ClockModuleType enClkModuleType;
} Mcu_ClockModuleSettingType;

typedef struct STag_Mcu_ClockShiftRepetitionType
{
  /* System clock selector/divider register control value */
  uint32 ulCKSCCLKDCValue;
  /* System clock selector/divider register control address */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCKSCCLKDCReg;                                                              /* PRQA S 3432 # JV-01 */
  /* System clock selector/divider register status value */
  uint32 ulCKSSCLKDSValue;
  /* System clock selector/divider register status address */
  volatile P2VAR(uint32, TYPEDEF, REGSPACE) pCKSSCLKDSReg;                                                              /* PRQA S 3432 # JV-01 */
  /* System clock selector/divider register status mask value */
  uint32 ulCKSSCLKDSMaskValue;
} Mcu_ClockShiftRepetitionType;

typedef struct STag_Mcu_ClockShiftSettingType                                                                           /* PRQA S 3630 # JV-01 */
{
  /* System clock selector/divider register control value for PLL */
  P2VAR(Mcu_ClockShiftRepetitionType, TYPEDEF, MCU_CONFIG_DATA)                                                         /* PRQA S 3432 # JV-01 */
    aaClockShiftRepetitionPLL[2][MCU_NUMBER_CLOCK_GEAR_UP_REPETITION];
  /* System clock selector/divider register control value for SSCG */
  P2VAR(Mcu_ClockShiftRepetitionType, TYPEDEF, MCU_CONFIG_DATA)                                                         /* PRQA S 3432 # JV-01 */
    aaClockShiftRepetitionSSCG[2][MCU_NUMBER_CLOCK_GEAR_UP_REPETITION];
  /* System clock selector/divider register control value for SSCG1 */
  P2VAR(Mcu_ClockShiftRepetitionType, TYPEDEF, MCU_CONFIG_DATA)                                                         /* PRQA S 3432 # JV-01 */
    aaClockShiftRepetitionSSCG1[2][MCU_NUMBER_CLOCK_GEAR_UP_REPETITION];
} Mcu_ClockShiftSettingType;

typedef struct STag_Mcu_ClockSettingType
{
  /* Indicate whether Main OSC is used for current config */
  boolean blMainOscUsed;
  #if (MCU_SOSC_SUPPORT == STD_ON)
  /* Indicate whether Sub OSC is used for current config */
  boolean blSubOscUsed;
  #endif /* MCU_SOSC_SUPPORT == STD_ON */
  /* Indicate whether PLL is used for current config */
  boolean blPllUsed;
  /* Indicate whether HSIntOSC is used for current config */
  boolean blHSOscUsed;
  /* Indicate whether clock generator setting is supported */
  boolean blClkGenSupported;
  #if (MCU_CLOCK_TRIMMING_SUPPORT == STD_ON)
  /* Indicate whether clock trimming setting is supported */
  boolean blClkTrimmingSupported;
  #endif /* MCU_CLOCK_TRIMMING_SUPPORT == STD_ON */
  /* System Clock select register setting value */
  P2CONST(Mcu_ClockModeSettingType, TYPEDEF, MCU_CONST) pClockModeSetting;
  /* Module Clock Selector/Divider setting value */
  P2CONST(Mcu_ClockModuleSettingType, AUTOMATIC, MCU_CONFIG_DATA) pClockModuleSetting;
  /* The number of clock module */
  uint8 ucNoOfClkModule;
  #if (MCU_GTM_SETTING == STD_ON)
  /* Pointer to CCM configuration register setting */
  P2CONST(Mcu_CCMSettingType, AUTOMATIC, MCU_CONFIG_DATA) pCcmSetting;
  /* Pointer to CMU configuration register setting */
  P2CONST(Mcu_CMUSettingType, AUTOMATIC, MCU_CONFIG_DATA) pCmuSetting;
  /* The number of CMU configuration register */
  uint8 ucNoOfCcmCfg;
  /* GTM_CLS_CLK_CFG register setting value */
  uint32 ulClsClkCfgValue;
  #endif /* MCU_GTM_SETTING == STD_ON */
  #if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
  /* PLLSTPM register setting value */
  uint32 ulPLLSTPM;
  /* MOSCSTPM register setting value */
  uint32 ulMOSCSTPM;
  /* HSOSCSTPM register setting value */
  uint32 ulHSOSCSTPM;
  #endif
  #if (MCU_SSCG_ENABLE == STD_ON)
  /* SSCGC register setting value */
  uint32 ulSSCGC;
  #endif /* MCU_SSCG_ENABLE == STD_ON */
  #if (MCU_SSCG1_ENABLE == STD_ON)
  /* SSCG1C register setting value */
  uint32 ulSSCG1C;
  #endif /* MCU_SSCG1_ENABLE == STD_ON */
  #if (MCU_CLOCK_TRIMMING_SUPPORT == STD_ON)
  /* HSOSCTRMPRODC register setting value */
  uint32 ulHSOSCTRMPRODC;
  /* Clock trimming period value */
  uint32 ulClkTrimmingPeriod;
  #endif /* MCU_CLOCK_TRIMMING_SUPPORT == STD_ON */
  #if (MCU_CLMA_OPERATION == STD_ON)
  /* Pointer to MCU Clock monitor configuration */
  P2CONST(void, AUTOMATIC, MCU_CONFIG_CONST) pClmSetting;
  /* Value of the number of Clock monitor setting */
  uint8 ucNoOfClm;
  #endif /* MCU_CLMA_OPERATION == STD_ON */
  /* Clock setting stablility max time-out count */
  uint32 ulClkStbCount;
  #if (MCU_SOSC_SUPPORT == STD_ON)
  /* Sub OSC clock setting stablility max time-out count */
  uint32 ulSubOscStbCount;
  #endif /* MCU_SOSC_SUPPORT == STD_ON */
  /* Clock shift setting setting value */
  P2CONST(Mcu_ClockShiftSettingType, TYPEDEF, MCU_CONST) pClockShiftSetting;
} Mcu_ClockSettingType;

/***********************************************************************************************************************
**                                        Extern declarations for Global Data                                         **
***********************************************************************************************************************/
#define MCU_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Mcu_MemMap.h"

/* Global array for Clock Setting Configuration */
extern CONST(Mcu_ClockSettingType, MCU_CONFIG_DATA) Mcu_GaaClockSetting[];                                              /* PRQA S 3684 # JV-01 */

#define MCU_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Mcu_MemMap.h"

/***********************************************************************************************************************
**                                           Function Prototypes                                                      **
***********************************************************************************************************************/

#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

#if (MCU_INIT_CLOCK == STD_ON)
extern FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKInitClock(void);

extern FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKShiftCpuSys(Mcu_ClkModeType LenClkMode, uint8 LucSrcIndex,
Mcu_ClkShiftType LenClkShift, P2CONST(Mcu_ClockShiftSettingType, MCU_CONST, MCU_CONFIG_DATA) LpClockShiftSetting);
#endif

#if (MCU_NO_PLL == STD_OFF)
extern FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKDistributeClocks(void);
#endif

extern FUNC(Mcu_PllStatusType, MCU_PRIVATE_CODE) Mcu_CLKGetPllStatus(void);

#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

#endif  /* MCU_CLK_LLDRIVER_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
