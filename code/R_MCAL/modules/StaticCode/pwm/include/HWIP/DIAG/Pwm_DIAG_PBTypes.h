/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_DIAG_PBTypes.h                                                                                  */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                              COPYRIGHT                                                             */
/*====================================================================================================================*/
/* (c) 2021-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the type definitions of Post Build time Parameters                                              */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*                                                                                                                    **
 * 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                        **
 * 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                           **
** 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                            **
** 2.3.1: 31/03/2025 : Update SW-VERSION for U2Ax Ver22.00.03 Beta2 Release                                           **
** 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
** 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
** 2.1.2: 31/10/2024 : As part of ARDAACL-47136, following changes are made:                                          **
**                     1. Update PWM_PWGC_INT_OFFSET to aaReserved0 of STag_Pwm_PWGC_INT_RegsType struct              **
** 2.1.1: 21/08/2024 : As part of ARDAACL-49187, following changes are made:                                          **
**                     1. Add macro define PWM_DIAG_AD_TRIGGER_RISING_EDGE and PWM_DIAG_AD_TRIGGER_FALLING_EDGE       **
**        16/07/2024 : As part of ARDAACL-49135, following changes are made:                                          **
**                     1. Add new macro PWM_DIAG_RESET_16BIT_RSF, PWM_DIAG_RESET_16BIT_RSFT, PWM_DIAG_RESET_16BIT     **
**        18/06/2024 : As part of ARDAACL-49135, following changes are made:                                          **
**                     1. Update offset of aaReserved0 for struct Pwm_PWGC_INT_RegsType                               **
** 2.0.2: 06/01/2024 : Remove QAC message 1534, 1535, 1536                                                            **
**        18/12/2023 : Add QAC message 1534, 1535, 1536                                                               **
**        14/12/2023 : Update version in header comment                                                               **
 * 2.0.1: 25/10/2023 : Update version in header comment                                                               **
 * 2.0.0: 05/07/2023 : Remove #ifdef PWM_INSTANCE_INDEX. Remove message 0841                                          **
 * 1.0.0: 23/08/2021 : Initial Version.                                                                               **
 *                                                                                                                    */
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

/***********************************************************************************************************************
**                                             Include Section                                                        **
***********************************************************************************************************************/
#ifndef PWM_DIAG_PBTYPES_H
#define PWM_DIAG_PBTYPES_H

/* Included for data type unsigned integer declaration */
#include "rh850_Types.h"

/***********************************************************************************************************************
**                                              Version Information                                                   **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define PWM_DIAG_PBTYPES_AR_RELEASE_MAJOR_VERSION       PWM_AR_RELEASE_MAJOR_VERSION
#define PWM_DIAG_PBTYPES_AR_RELEASE_MINOR_VERSION       PWM_AR_RELEASE_MINOR_VERSION
#define PWM_DIAG_PBTYPES_AR_RELEASE_REVISION_VERSION    PWM_AR_RELEASE_REVISION_VERSION

/* Software module version information */
#define PWM_DIAG_PBTYPES_SW_MAJOR_VERSION               PWM_SW_MAJOR_VERSION
#define PWM_DIAG_PBTYPES_SW_MINOR_VERSION               PWM_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                              Global Symbols                                                        **
***********************************************************************************************************************/

#define PWM_DIAG_GROUP0                                 0x00U
#define PWM_DIAG_GROUP1                                 0x01U
#define PWM_DIAG_GROUP2                                 0x02U
#define PWM_DIAG_NOTI_GR0                               0x00U
#define PWM_DIAG_NOTI_GR1                               0x01U
#define PWM_DIAG_NOTI_GR2                               0x02U
#define PWM_DIAG_NOTI_GR3                               0x03U
#define PWM_DIAG_REWRITE_REQUEST                        0x01U
#define PWM_DIAG_PWGC_RDTT                              0x02U
#define PWM_DIAG_ENABLE_OUTPUT                          0x01U
#define PWM_DIAG_DISABLE_OUTPUT                         0x00U
#define PWM_DIAG_PWGC_OCL                               ((uint8)0x01U << 7)
#define PWM_DIAG_PWSD_ARSE                              ((uint8)0x01U << 7)
#define PWM_DIAG_PWSD_ENBL                              0x01U
#define PWM_DIAG_RISING_EDGE                            ((uint16)0x0001U << 14)
#define PWM_DIAG_FALLING_EDGE                           ((uint16)0x0001U << 15)
#define PWM_DIAG_AD_TRIGGER_RISING_EDGE                 ((uint16)0x0001U << 4)
#define PWM_DIAG_AD_TRIGGER_FALLING_EDGE                ((uint16)0x0001U << 5)
#define PWM_DIAG_RESET_16BIT_RSF                        (uint16) 0x0001U
#define PWM_DIAG_RESET_16BIT_RSFT                       ((uint16)0x0001U << 1)
#define PWM_DIAG_RESET_16BIT                            (uint16)0x0000U
/***********************************************************************************************************************
**                                              Global Data Types                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                              Structure for Channel Properties                                      **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                              Structure for PWBA                                                    **
***********************************************************************************************************************/
typedef volatile struct STag_Pwm_PWBAnBRSm_RegsType
{
  uint16 usPWBAnBRSm;
  uint8  aaReserved0[2];
} Pwm_PWBAnBRSm_RegsType;

typedef volatile struct STag_Pwm_PWBA_RegsType                                                                          /* PRQA S 3630 # JV-01 */
{
  Pwm_PWBAnBRSm_RegsType aaPWBAnBRSm[4];
  uint8  ucPWBAnTE;
  uint8  aaReserved0[3];
  uint8  ucPWBAnTS;
  uint8  aaReserved1[3];
  uint8  ucPWBAnTT;
} Pwm_PWBA_RegsType;

/***********************************************************************************************************************
**                                              Structure for PWGC                                                    **
***********************************************************************************************************************/
typedef volatile struct STag_Pwm_PWGC_RegsType                                                                          /* PRQA S 3630 # JV-01 */
{
  uint16 usPWGCnCSDR;
  uint8  aaReserved0[2];
  uint32 ulPWGCnCRDR;
  uint16 usPWGCnCTDR;
  uint8  aaReserved1[2];
  uint8  ucPWGCnRDT;
  uint8  aaReserved2[3];
  uint16 usPWGCnST;
  uint8  aaReserved3[2];
  uint16 usPWGCnCNT;
  uint8  aaReserved4[2];
  uint8  ucPWGCnTCR;
  uint8  aaReserved5[2];
  uint8  ucPWGCnTCBR;
  uint8  aaReserved6[3];
  uint16 usPWGCnCTL;
  uint8  aaReserved7[2];
  uint16 usPWGCnCSBR;
  uint8  aaReserved8[2];
  uint32 ulPWGCnCRBR;
  uint16 usPWGCnCTBR;
  uint8  aaReserved9[2];
  uint8  ucPWGCnFOT;
} Pwm_PWGC_RegsType;

/***********************************************************************************************************************
**                                              Structure for SLPWGC                                                  **
***********************************************************************************************************************/
typedef volatile struct STag_Pwm_SLPWGCk_RegsType
{
  uint32 ulSLPWGCk;
} Pwm_SLPWGCk_RegsType;

typedef volatile struct STag_Pwm_PWGCPRDm_RegsType
{
  uint16 usPWGCPRDm;
  uint8  aaReserved0[2];
} Pwm_PWGCPRDm_RegsType;

typedef volatile struct STag_Pwm_PWGCPRDSLq_RegsType
{
  uint32 ulPWGCPRDSLq;
} Pwm_PWGCPRDSLq_RegsType;

typedef volatile struct STag_Pwm_SLPWG_RegsType                                                                         /* PRQA S 3630 # JV-01 */
{
  Pwm_SLPWGCk_RegsType    aaSLPWGCk[3];
  Pwm_PWGCPRDm_RegsType   aaPWGCPRDm[4];
  Pwm_PWGCPRDSLq_RegsType aaPWGCPRDSLq[6];
} Pwm_SLPWG_RegsType;

/***********************************************************************************************************************
**                                              Structure for PWSD                                                    **
***********************************************************************************************************************/
typedef volatile struct STag_Pwm_PWSDnQUEj_RegsType
{
  uint8  ucPWSDnQUEj;
  uint8  aaReserved0[3];
} Pwm_PWSDnQUEj_RegsType;

typedef volatile struct STag_Pwm_PWSDnPVCRx_RegsType
{
  uint32 ulPWSDnPVCRx;
} Pwm_PWSDnPVCRx_RegsType;

typedef volatile struct STag_Pwm_PWSDnPWDDIRx_RegsType
{
  uint32 ulPWSDnPWDDIRx;
} Pwm_PWSDnPWDDIRx_RegsType;

typedef volatile struct STag_Pwm_PWSD_RegsType                                                                          /* PRQA S 3630 # JV-01 */
{
  uint8  ucPWSDnCTL;
  uint8  aaReserved0[3];
  uint8  ucPWSDnSTR;
  uint8  aaReserved1[3];
  uint8  ucPWSDnSTC;
  uint8  aaReserved2[23];
  Pwm_PWSDnQUEj_RegsType aaPWSDnQUEj[8];
  uint8  aaReserved3[192];
  Pwm_PWSDnPVCRx_RegsType aaPWSDnPVCRx[96];
  uint8  aaReserved4[128];
  Pwm_PWSDnPWDDIRx_RegsType aaPWSDnPWDDIRx[96];
} Pwm_PWSD_RegsType;

/***********************************************************************************************************************
**                                              Structure for PWGC_INTF                                               **
***********************************************************************************************************************/
typedef volatile struct STag_Pwm_PWGC_INT_RegsType
{
  uint32 ulPWGCINTFhk;    /* R */
  uint32 ulPWGCINTMSKhk;  /* RW */
  uint32 ulPWGCINTFChk;   /* W */
  uint8  aaReserved0[500];
} Pwm_PWGC_INT_RegsType;

typedef volatile struct STag_Pwm_PWGC_INTF_RegsType                                                                     /* PRQA S 3630 # JV-01 */
{
  Pwm_PWGC_INT_RegsType aaPWGC_INTF[3];
} Pwm_PWGC_INTF_RegsType;

/***********************************************************************************************************************
**                                              Structure for Unit Config                                             **
***********************************************************************************************************************/
typedef struct STag_Pwm_DiagPeriodConfigType                                                                            /* PRQA S 3630 # JV-01 */
{
  /* Index of BRS tegister */
  uint8  ucPRDmIndex;
  /* Configured Value */
  uint16 usPRDmValue;
} Pwm_DiagPeriodConfigType;

/***********************************************************************************************************************
**                                              Structure for Unit Config                                             **
***********************************************************************************************************************/
typedef struct STag_Pwm_DiagPrescalerConfigType                                                                         /* PRQA S 3630 # JV-01 */
{
  /* Index of BRS tegister */
  uint8  ucBRSmIndex;
  /* Configured Value */
  uint16 usBSRmValue;
} Pwm_DiagPrescalerConfigType;


/***********************************************************************************************************************
**                                              Structure for Notification                                            **
***********************************************************************************************************************/
typedef struct STag_Pwm_DiagNotifyConfigType
{
  /* Notifi Ptr */
  P2FUNC(void, PWM_APPL_CODE, pNotifyFunc)(uint32 LulIntFactor);                                                        /* PRQA S 3432 # JV-01 */
  /* EIC Registers */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE) pEICn;
} Pwm_DiagNotifyConfigType;

typedef struct STag_Pwm_DiagNotiGrConfigType                                                                            /* PRQA S 3630 # JV-01 */
{
  P2VAR(Pwm_DiagNotifyConfigType, TYPEDEF, PWM_CONFIG_DATA) aaDiagNotifyConfig[4][3];                                   /* PRQA S 3432 # JV-01 */
} Pwm_DiagNotiGrConfigType;

/***********************************************************************************************************************
**                                              Structure for Select Period                                           **
***********************************************************************************************************************/
typedef struct STag_Pwm_DiagPeriodSelectConfigType                                                                      /* PRQA S 3630 # JV-01 */
{
  uint8  ucPWGCPRDSLqIndex;
  uint32 ulPWGCPRDSLqValue;
} Pwm_DiagPeriodSelectConfigType;

/***********************************************************************************************************************
**                                              Structure for Unit Config                                             **
***********************************************************************************************************************/
typedef struct STag_Pwm_DiagUnitConfigType                                                                              /* PRQA S 3630 # JV-01 */
{
  /* pointer to base address of PWBA */
  P2VAR(Pwm_PWBA_RegsType, TYPEDEF, REGSPACE) pPWBA;                                                                    /* PRQA S 3432 # JV-01 */
  /* pointer to base address of SLPWG */
  P2VAR(Pwm_SLPWG_RegsType, TYPEDEF, REGSPACE) pSLPWG;                                                                  /* PRQA S 3432 # JV-01 */
  /* pointer to base address of PWSD */
  P2VAR(Pwm_PWSD_RegsType, TYPEDEF, REGSPACE) pPWSD;                                                                    /* PRQA S 3432 # JV-01 */
  /* pointer to base address of PWGC_INTF */
  P2VAR(Pwm_PWGC_INTF_RegsType, TYPEDEF, REGSPACE) pPWGC_INTF;                                                          /* PRQA S 3432 # JV-01 */
  /* pointer to Period setting */
  P2VAR(Pwm_DiagPrescalerConfigType, TYPEDEF, PWM_CONFIG_DATA) pPrescalerConfig;                                        /* PRQA S 3432 # JV-01 */
  /* pointer to Period setting */
  P2VAR(Pwm_DiagPeriodConfigType, TYPEDEF, PWM_CONFIG_DATA) pPeriodConfig;                                              /* PRQA S 3432 # JV-01 */
  /* pointer to Notification group */
  P2VAR(Pwm_DiagNotiGrConfigType, TYPEDEF, PWM_CONFIG_DATA) pDiagNotiGrConfig;                                          /* PRQA S 3432 # JV-01 */
  /* pointer to Period Selection setting */
  P2VAR(Pwm_DiagPeriodSelectConfigType, TYPEDEF, PWM_CONFIG_DATA) pPeriodSelectConfig;                                  /* PRQA S 3432 # JV-01 */
} Pwm_DiagUnitConfigType;


/***********************************************************************************************************************
**                                              Structure for Channel Config                                          **
***********************************************************************************************************************/
typedef struct STag_Pwm_DIAGChannelConfigType
{
  /* pointer to base address of PWGC */
  P2VAR(Pwm_PWGC_RegsType, TYPEDEF, REGSPACE) pPWGC;                                                                    /* PRQA S 3432 # JV-01 */
  /* Group ID */
  uint8  ucGroupId;
  /* Channel No. */
  uint8  ucChNo;
  /* Period ID. */
  uint8  ucPeriodId;
  /* Notify Gr ID */
  uint8  ucNotifyGrId;
  /* pointer to base address of Interrupt Control Register */
  P2VAR(volatile uint16, TYPEDEF, REGSPACE)pEICx;
  /* Default PWGCnCTL value */
  uint16 usPWGCnCTL_Value;
  /* Default PWGCnCSDR value */
  uint16 usDefaultPWGCnCSDR;
  /* Default PWGCnCRDR value */
  uint32 ulDefaultPWGCnCRDR;
  /* Default PWGCnCTDR value */
  uint16 usDefaultPWGCnCTDR;
  /* Offset value */
  uint16 usOffset;
  /* TriggerAdjustOffset */
  boolean blTriggerAdjustOffset;
  /* Value of PWSDnRVCRx */
  uint32 ulPWSDnRVCRxValue;
} Pwm_DiagChannelConfigType;

#endif /* End of PWM_DIAG_PBTYPES_H */
/***********************************************************************************************************************
**                                              End of File                                                           **
***********************************************************************************************************************/
