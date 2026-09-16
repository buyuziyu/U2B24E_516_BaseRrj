/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_ADCK_PBTypes.h                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2021-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the type definitions of Post-build Time Parameters                                              */
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
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.5.1: 30/06/2025 : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                     Remove SW-VERSION in file header
 * 2.4.0: 31/05/2025 : Update SW-VERSION for RH850/Ver22.01.02 U2Cx release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3: 31/10/2024 : Update SW-VERSION 2.1.3
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 * 2.1.1: 30/08/2024 : As part of U2Bx-E support, following changes are made:
 *                     1.Add structure Adc_TrackHoldChannelValueType
 *                     2.Update structure Adc_TrackHoldSelectType
 *                     3.Remove macros ADC_NUM_OF_PIC_SELECT, ADC_NUM_OF_PIC_CONTROL
 *                     4.Add macro ADC_NUM_OF_TH_CHANNEL_SELECT
 *                     5.Add structure Adc_TrackHoldSelectType
 *                     As part of U2Cx support, following changes are made:
 *                     1.Add macros ADC1_ERR_EIC_OFFSET, ADC2_ERR_EIC_OFFSET, ADCA_ERR_EIC_OFFSET for U2Cx
 *                     2.Add PWWM-Diag elements in Adc_ConfigRegisters structure
 *                     3.Add the condition of macro ADC_IP_C_ADCK for handling PIC and PWM-Diag register
 * 2.0.1: 18/10/2023 : Support QAC Amendment 2, add message 1534, 1536
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define. Change Adc_Mapping.h to Adc_Memmap.h
 * 1.4.4: 20/07/2022 : Changed the type of ADC_NUM_OF_TH_GROUP to uint32.
 *                     Renamed the member aaADCKnSGTSELx in the struct Adc_SgTriggRegType to aaADCXnSGTSELx.
 * 1.4.3: 24/05/2022 : Removed the prototypes of Adc_GaaTriggOutConfigType and Adc_GaaTriggOutConfigRegister.
 *        18/05/2022 : Removed macros ADC_ENABLE_ASMPMSK, ADC_DISABLE_ASMPMSK, and ADC_ADCX_THXCR_HLDCTE.
 *                     Fixed the typos in comments.
 *        28/04/2022 : Changed the structure of SG start trigger control register.
 *                     Added the macros for the number of PIC registers.
 *                     Changed the type of value of ADC_NUM_SCANGROUP to uint32.
 * 1.4.1: 24/11/2021 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ADC_ADCK_PBTYPES_H
#define ADC_ADCK_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0639)    : Number of members in 'struct' or 'union' exceeds 127 - program does not conform strictly to  */
/*                       ISO:C90.                                                                                     */
/* Rule                : MISRA C:2012 Dir-1.1                                                                         */
/* JV-01 Justification : This warning does not indicate a mistake in the code, it is a message to call attention to   */
/*                       the processing power of the compiler. Because the compiler in use has been confirmed to      */
/*                       have the ability to handle this, no problem.                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1534)    : The macro '%1s' is declared but not used within this project.                                */
/* Rule                : MISRA C:2012 Rule-2.5                                                                        */
/* JV-01 Justification : This is accepted. This macro is used by other file.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1536)    : The tag '%1s' is declared but not used within this project.                                  */
/* Rule                : MISRA C:2012 Rule-2.4                                                                        */
/* JV-01 Justification : This is accepted. This tag is used by other file.                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Macros for Limit Check Registers */
#define ADC_NUM_OF_LIMIT_REG             2U
#define ADC_ADCX_VCLMSCR2_ALL_MASK       (uint32)0xFFFFFFFFUL                                                           /* PRQA S 1534 # JV-01 */
#define ADC_ADCX_VCULLMTBR_INIT_VALUE    (uint32)0x7FFF0000UL                                                           /* PRQA S 1534 # JV-01 */

/* Macro for Parity Error Register */
#define ADC_ADCX_PER_PECAP               (uint8)0x7FU

/* Macros for ID Error Register */
#define ADC_ADCX_IDER_IDECAP             (uint8)0x7FU
#define ADC_ADCX_IDER_IDE                (uint8)(1U << 7U)

/* Macro for Trigger Overlap Check Error Status Register */
#define ADC_ADCX_TOCER_TOCESG_LSB        (uint8)(1U << 1U)

/* Macros for Error Clear Register */
#define ADC_ADCX_ECR_IDEC                (Adc_ErrClearRegType)(1UL << 0U)
#define ADC_ADCX_ECR_TOCESGC_LSB         (Adc_ErrClearRegType)(1UL << 9U)
#define ADC_ADCX_ECR_CLEAR_ALL           (Adc_ErrClearRegType)0x3E05U

/* Macro for Wiring Break Detection Control Register */
#define ADC_ADCX_ODCR_INIT_VALUE         (Adc_WireBreakRegType)0x0000U                                                  /* PRQA S 1534 # JV-01 */

/* Macro for Scan Group Common Status Register */
#define ADC_ADCX_SGSTR_SHACT             (uint16)(1UL << 7U)                                                            /* PRQA S 1534 # JV-01 */

/* Macro for Scan Group Start Trigger Control Register */
#define ADC_ADCX_SGTSEL_INIT             (uint32)0x00000000UL                                                           /* PRQA S 1534 # JV-01 */

/* Macro for ECM Register (ECM100) */
#define ADC_ECM_CFG_ADC_PARITY_ERR       (uint32)(1UL << 4U)

#if (ADC_TRACK_AND_HOLD == STD_ON)
/* Macro to stop all T&H */
#define ADC_ADCX_THSTPCR_THSTP           (uint8)0x01U
/* Macro to set the bit SMPST */
#define ADC_ADCX_THSMPSTCR_SMPST         (uint8)0x01U
/* Macro to set the bit HLDST */
#define ADC_ADCX_THXHLDSTCR_HLDST        (uint8)0x01U
/* Macro to indicate Track and Hold Group */
#define ADC_TH_DISABLED                  (uint8)0xFFU
#define ADC_TH_GROUPA                    (uint8)0x00U
#define ADC_TH_GROUPB                    (uint8)0x01U

/* Macros for T&H Group A Control Register */
#define ADC_ADCX_THXCR_HLDTE             (uint8)(1U << 4U)
#endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

/* Number of wait time registers */
#define ADC_NUM_OF_WAITTIME              8UL

/* Number of limit check registers */
#define ADC_NUM_OF_LIMIT_TABLE           8UL

/* Macro for EIC error register offset value */
#if (ADC_IP_C_ADCK == STD_OFF)
#define ADC1_ERR_EIC_OFFSET              2U    /* EIC463 - 461 */
#define ADC2_ERR_EIC_OFFSET              1U    /* EIC462 - 461 */
#define ADC3_ERR_EIC_OFFSET              3U    /* EIC464 - 461 */
#define ADCA_ERR_EIC_OFFSET              521U  /* EIC982 - 461 */
#else /*(ADC_IP_C_ADCK == STD_ON) */
#define ADC1_ERR_EIC_OFFSET              302U   /* EIC370 - 68 */
#define ADC2_ERR_EIC_OFFSET              490U  /* EIC558 - 68 */
#define ADCA_ERR_EIC_OFFSET              0U   /* EIC68 - 68 */
#endif /* ADC_IP_C_ADCK = STD_OFF) */

/* Number of scan group */
#define ADC_NUM_SCANGROUP                5UL

/* Number of virtual channel registers */
#define ADC_NUM_OF_VCR                   64U

/* Number of Track and Hold groups */
#define ADC_NUM_OF_TH_GROUP              2UL

/* Number of Track and Hold Physical IO channel select */
#define ADC_NUM_OF_TH_CHANNEL_SELECT     4UL

/* Number of PIC register groups */
#define ADC_NUM_OF_TRIGG_SELECT          2UL

#define ADC_NUM_OF_PIC_CONFIG            10UL

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
typedef uint16 Adc_WireBreakRegType;
typedef uint16 Adc_ErrClearRegType;

/***********************************************************************************************************************
** Structure for HW Unit Registers, which are used to read or write                                                   **
** the status or configured values for proper working of the ADC driver                                               **
***********************************************************************************************************************/
/* Structure for registers of Scan Group */
typedef struct STag_Adc_SGRegType                                                                                       /* PRQA S 1536 # JV-01 */
{
  volatile uint8  ucADCXnSGSTCRx;                                    /* 00H */
  volatile uint8  aaReserved0[3];
  volatile uint8  ucADCXnSGSTPCRx;                                   /* 04H */
  volatile uint8  aaReserved1[3];
  volatile uint8  ucADCXnADTSTCRx;                                   /* 08H */
  volatile uint8  aaReserved2[3];
  volatile uint8  ucADCXnADTENDCRx;                                  /* 0CH */
  volatile uint8  aaReserved3[3];
  volatile uint8  ucADCXnSGCRx;                                      /* 10H */
  volatile uint8  aaReserved4[3];
  volatile uint16 usADCXnSGVCPRx;                                    /* 14H */
  volatile uint8  aaReserved5[2];
  volatile uint8  ucADCXnSGMCYCRx;                                   /* 18H */
  volatile uint8  aaReserved6[7];
  volatile uint8  ucADCXnSGSRx;                                      /* 20H */
  volatile uint8  aaReserved7[3];
  volatile uint32 ulADCXnADTIPRx;                                    /* 24H */
  volatile uint32 ulADCXnADTPRRx;                                    /* 28H */
  volatile uint8  aaReserved8[20];
} Adc_SGRegType;                                                     /* size 40H */

/* Structure for registers of Wait Time */
typedef struct STag_Adc_WaitTimeRegType                                                                                 /* PRQA S 1536 # JV-01 */
{
  volatile uint16 usADCXnWAITTRy;                                    /* 00H */
  volatile uint8  aaReserved0[2];
} Adc_WaitTimeRegType;                                               /* size 04H */

/* Structure for T&H Group X Hold Start Control Register */
typedef struct STag_Adc_TrackHoldStartType                                                                              /* PRQA S 1536 # JV-01 */
{
  volatile uint8 ucADCXnTHxHLDSTCR;
  volatile uint8 aaReserved0[3];
} Adc_TrackHoldStartType;

/* Structure for T&H Group A Control Register */
typedef struct STag_Adc_TrackHoldGroupType                                                                              /* PRQA S 1536 # JV-01 */
{
  volatile uint8 ucADCXnTHxCR;
  volatile uint8 aaReserved0[3];
} Adc_TrackHoldGroupType;

/* Structure for ADCK registers */
typedef struct STag_Adc_ConfigRegisters                                                                                 /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
#if (ADC_IP_C_ADCK == STD_OFF)
  volatile uint32 aaADCXnVCR[ADC_NUM_OF_VCR];                        /* 000H */
  volatile uint8  aaReserved0[132];
  volatile uint8  ucADCXnSGDIAGVCR0;                                 /* 184H */
  volatile uint8  aaReserved1[3];
  volatile uint8  ucADCXnSGDIAGVCR1;                                 /* 188H */
  volatile uint8  aaReserved2[3];
  volatile uint8  ucADCXnSGDIAGVCR2;                                 /* 18CH */
  volatile uint8  aaReserved3[19];
  volatile uint16 aaADCXnDR[ADC_NUM_OF_VCR];                         /* 1A0H */
  volatile uint8  aaReserved4[68];
  volatile uint16 aaADCXnSGDIAGDR[3];                                /* 264H */
  volatile uint8  aaReserved5[2];
  volatile uint32 ulADCXnSGDIAGSRR;                                  /* 26CH */
  volatile uint8  aaReserved6[16];
  volatile uint32 aaADCXnDIR[ADC_NUM_OF_VCR];                        /* 280H */
  volatile uint8  aaReserved7[132];
  volatile uint32 aaADCXnSGDIAGDIR[3];                               /* 404H */
  volatile uint8  aaReserved8[48];
  volatile Adc_SGRegType aaADCXnSG[ADC_NUM_SCANGROUP];               /* 440H */
  volatile uint8  aaReserved9[64];
  volatile uint8  ucADCXnSGDIAGSTCR;                                 /* 5C0H */
  volatile uint8  aaReserved10[3];
  volatile uint8  ucADCXnSGDIAGSTPCR;                                /* 5C4H */
  volatile uint8  aaReserved11[11];
  volatile uint32 ulADCXnSGDIAGCR;                                   /* 5D0H */
  volatile uint8  aaReserved12[12];
  volatile uint32 ulADCXnSGDIAGPCCR0;                                /* 5E0H */
  volatile uint32 ulADCXnSGDIAGPCCR1;                                /* 5E4H */
  volatile uint8  aaReserved13[8];
  volatile uint8  ucADCXnSGDIAGSR;                                   /* 5F0H */
  volatile uint8  aaReserved14[15];
  volatile uint16 usADCXnSGSTR;                                      /* 600H */
  volatile uint8  aaReserved15[14];
  volatile uint8  ucADCXnADSYNSTCR;                                  /* 610H */
  volatile uint8  aaReserved16[3];
  volatile uint8  ucADCXnADTSYNSTCR;                                 /* 614H */
  volatile uint8  aaReserved17[43];
  volatile uint8  ucADCXnADHALTR;                                    /* 640H */
  volatile uint8  aaReserved18[3];
  volatile uint8  ucADCXnADCR1;                                      /* 644H */
  volatile uint8  aaReserved19[3];
  volatile uint8  ucADCXnADCR2;                                      /* 648H */
  volatile uint8  aaReserved20[3];
  volatile uint32 ulADCXnSMPCR;                                      /* 64CH */
  volatile uint8  ucADCXnMPXCURCR;                                   /* 650H */
  volatile uint8  aaReserved21[3];
  volatile uint8  ucADCXnMPXINTER;                                   /* 654H */
  volatile uint8  aaReserved22[3];
  volatile uint32 ulADCXnMPXCURR1;                                   /* 658H */
  volatile uint8  ucADCXnMPXCURR2;                                   /* 65CH */
  volatile uint8  aaReserved23[3];
  volatile uint8  ucADCXnMPXCMDR;                                    /* 660H */
  volatile uint8  aaReserved24[15];
  volatile uint16 usADCXnDFASENTSGER;                                /* 670H */
  volatile uint8  aaReserved25[2];
  volatile uint8  ucADCXnADENDP0;                                    /* 674H */
  volatile uint8  aaReserved26[3];
  volatile uint8  ucADCXnADENDP1;                                    /* 678H */
  volatile uint8  aaReserved27[3];
  volatile uint8  ucADCXnADENDP2;                                    /* 67CH */
  volatile uint8  aaReserved28[3];
  volatile uint8  ucADCXnADENDP3;                                    /* 680H */
  volatile uint8  aaReserved29[3];
  volatile uint8  ucADCXnADENDP4;                                    /* 684H */
  volatile uint8  aaReserved30[11];
  volatile uint8  ucADCXnTHSMPSTCR;                                  /* 690H */
  volatile uint8  aaReserved31[3];
  volatile uint8  ucADCXnTHSTPCR;                                    /* 694H */
  volatile uint8  aaReserved32[3];
  volatile uint8  ucADCXnTHCR;                                       /* 698H */
  volatile uint8  aaReserved33[7];
  volatile Adc_TrackHoldStartType aaTHxHLDSTCR[ADC_NUM_OF_TH_GROUP]; /* 6A0H */
  volatile uint8  aaReserved35[8];
  volatile uint16 usADCXnTHGSR;                                      /* 6B0H */
  volatile uint8  aaReserved36[2];
  volatile uint8  ucADCXnTHER;                                       /* 6B4H */
  volatile uint8  aaReserved37[11];
  volatile Adc_TrackHoldGroupType aaTHxCR[ADC_NUM_OF_TH_GROUP];      /* 6C0H */
  volatile uint8  aaReserved39[56];
  volatile Adc_WaitTimeRegType aaWAITTR[ADC_NUM_OF_WAITTIME];        /* 700H */
  volatile uint8  aaReserved40[32];
  volatile uint8  ucADCXnVMONVDCR1;                                  /* 740H */
  volatile uint8  aaReserved41[3];
  volatile uint8  ucADCXnVMONVDCR2;                                  /* 744H */
  volatile uint8  aaReserved42[27];
  volatile uint8  ucADCXnTDCR;                                       /* 760H */
  volatile uint8  aaReserved43[3];
  volatile Adc_WireBreakRegType ddADCXnODCR;                         /* 764H */
  volatile uint8  aaReserved44[10];
  volatile uint8  ucADCXnSFTCR;                                      /* 770H */
  volatile uint8  aaReserved45[3];
  volatile uint8  ucADCXnTOCCR;                                      /* 774H */
  volatile uint8  aaReserved46[27];
  volatile uint8  ucADCXnTOCER;                                      /* 790H */
  volatile uint8  aaReserved47[11];
  volatile uint8  ucADCXnOWER;                                       /* 79CH */
  volatile uint8  aaReserved48[3];
  volatile uint8  ucADCXnPER;                                        /* 7A0H */
  volatile uint8  aaReserved49[3];
  volatile uint8  ucADCXnIDER;                                       /* 7A4H */
  volatile uint8  aaReserved50[3];
  volatile Adc_ErrClearRegType ddADCXnECR;                           /* 7A8H */
  volatile uint8  aaReserved51[6];
  volatile uint8  ucADCXnSTPDCR0;                                    /* 7B0H */
  volatile uint8  aaReserved52[3];
  volatile uint8  ucADCXnSTPDCR1;                                    /* 7B4H */
  volatile uint8  aaReserved53[3];
  volatile uint8  ucADCXnSTPDCR2;                                    /* 7B8H */
  volatile uint8  aaReserved54[71];
  volatile uint32 aaADCXnVCULLMTBRy[ADC_NUM_OF_LIMIT_TABLE];         /* 800H */
  volatile uint8  aaReserved55[32];
  volatile uint32 aaADCXnVCLMINTER[ADC_NUM_OF_LIMIT_REG];            /* 840H */
  volatile uint8  aaReserved56[8];
  volatile uint8  ucADCXnSDVCLMINTER;                                /* 850H */
  volatile uint8  aaReserved57[15];
  volatile uint32 aaADCXnVCLMSR[ADC_NUM_OF_LIMIT_REG];               /* 860H */
  volatile uint8  aaReserved58[8];
  volatile uint32 ulADCXnSDVCLMSR;                                   /* 870H */
  volatile uint8  aaReserved59[12];
  volatile uint16 usADCXnSGULCR0;                                    /* 880H */
  volatile uint8  aaReserved60[2];
  volatile uint16 usADCXnSGULCR1;                                    /* 884H */
  volatile uint8  aaReserved61[2];
  volatile uint16 usADCXnSGULCR2;                                    /* 888H */
  volatile uint8  aaReserved62[2];
  volatile uint16 usADCXnSGULCR3;                                    /* 88CH */
  volatile uint8  aaReserved63[2];
  volatile uint16 usADCXnSGULCR4;                                    /* 890H */
  volatile uint8  aaReserved64[2];
  volatile uint16 usADCXnSGDIAGULCR;                                 /* 894H */
  volatile uint8  aaReserved65[10];
  volatile uint32 aaADCXnVCLMSCR[ADC_NUM_OF_LIMIT_REG];              /* 8A0H */
  volatile uint8  aaReserved66[8];
  volatile uint8  ucADCXnSDVCLMSCR;                                  /* 8B0H */
  volatile uint8  aaReserved67[3];
  volatile uint8  ucADCXnSGULCCR;                                    /* 8B4H */
  volatile uint8  aaReserved68[3];
  volatile uint8  ucADCXnVCLMASCR;                                   /* 8B8H */
  volatile uint8  aaReserved69[3];
#else /* (ADC_IP_C_ADCK == STD_ON) */
  volatile uint32 aaADCXnVCR[ADC_NUM_OF_VCR];                        /* 000H */
  volatile uint8  aaReserved0[128];
  volatile uint32 ulADCXnPWDVCR;                                     /* 180H */
  volatile uint8  ucADCXnSGDIAGVCR0;                                 /* 184H */
  volatile uint8  aaReserved1[3];
  volatile uint8  ucADCXnSGDIAGVCR1;                                 /* 188H */
  volatile uint8  aaReserved2[3];
  volatile uint8  ucADCXnSGDIAGVCR2;                                 /* 18CH */
  volatile uint8  aaReserved3[19];
  volatile uint16 aaADCXnDR[ADC_NUM_OF_VCR];                         /* 1A0H */
  volatile uint8  aaReserved4[64];
  volatile uint16 usADCXnPWDDR;                                      /* 260H */
  volatile uint8  aaReserved5[2];
  volatile uint16 aaADCXnSGDIAGDR[3];                                /* 264H */
  volatile uint8  aaReserved6[2];
  volatile uint32 ulADCXnSGDIAGSRR;                                  /* 26CH */
  volatile uint8  aaReserved7[16];
  volatile uint32 aaADCXnDIR[ADC_NUM_OF_VCR];                        /* 280H */
  volatile uint8  aaReserved8[128];
  volatile uint32 ulADCXnPWDDIR;                                     /* 400H */
  volatile uint32 aaADCXnSGDIAGDIR[3];                               /* 404H */
  volatile uint8  aaReserved9[48];
  volatile Adc_SGRegType aaADCXnSG[ADC_NUM_SCANGROUP];               /* 440H */
  volatile uint8  ucADCXnPWDCR;                                      /* 580H */
  volatile uint8  aaReserved11[3];
  volatile uint8  ucADCXnPWDSGCR;                                    /* 584H */
  volatile uint8  aaReserved12[59];
  volatile uint8  ucADCXnSGDIAGSTCR;                                 /* 5C0H */
  volatile uint8  aaReserved13[3];
  volatile uint8  ucADCXnSGDIAGSTPCR;                                /* 5C4H */
  volatile uint8  aaReserved14[11];
  volatile uint32 ulADCXnSGDIAGCR;                                   /* 5D0H */
  volatile uint8  aaReserved17[12];
  volatile uint32 ulADCXnSGDIAGPCCR0;                                /* 5E0H */
  volatile uint32 ulADCXnSGDIAGPCCR1;                                /* 5E4H */
  volatile uint8  aaReserved18[8];
  volatile uint8  ucADCXnSGDIAGSR;                                   /* 5F0H */
  volatile uint8  aaReserved19[15];
  volatile uint16 usADCXnSGSTR;                                      /* 600H */
  volatile uint8  aaReserved20[14];
  volatile uint8  ucADCXnADSYNSTCR;                                  /* 610H */
  volatile uint8  aaReserved21[3];
  volatile uint8  ucADCXnADTSYNSTCR;                                 /* 614H */
  volatile uint8  aaReserved22[43];
  volatile uint8  ucADCXnADHALTR;                                    /* 640H */
  volatile uint8  aaReserved23[3];
  volatile uint8  ucADCXnADCR1;                                      /* 644H */
  volatile uint8  aaReserved24[3];
  volatile uint8  ucADCXnADCR2;                                      /* 648H */
  volatile uint8  aaReserved25[3];
  volatile uint32 ulADCXnSMPCR;                                      /* 64CH */
  volatile uint8  ucADCXnMPXCURCR;                                   /* 650H */
  volatile uint8  aaReserved26[3];
  volatile uint8  ucADCXnMPXINTER;                                   /* 654H */
  volatile uint8  aaReserved27[3];
  volatile uint32 ulADCXnMPXCURR1;                                   /* 658H */
  volatile uint8  ucADCXnMPXCURR2;                                   /* 65CH */
  volatile uint8  aaReserved28[3];
  volatile uint8  ucADCXnMPXCMDR;                                    /* 660H */
  volatile uint8  aaReserved29[15];
  volatile uint16 usADCXnGTMENTSGER;                                 /* 670H */
  volatile uint8  aaReserved30[2];
  volatile uint8  ucADCXnADENDP0;                                    /* 674H */
  volatile uint8  aaReserved31[3];
  volatile uint8  ucADCXnADENDP1;                                    /* 678H */
  volatile uint8  aaReserved32[3];
  volatile uint8  ucADCXnADENDP2;                                    /* 67CH */
  volatile uint8  aaReserved33[3];
  volatile uint8  ucADCXnADENDP3;                                    /* 680H */
  volatile uint8  aaReserved34[3];
  volatile uint8  ucADCXnADENDP4;                                    /* 684H */
  volatile uint8  aaReserved35[11];
  volatile uint8  ucADCXnTHSMPSTCR;                                  /* 690H */
  volatile uint8  aaReserved36[3];
  volatile uint8  ucADCXnTHSTPCR;                                    /* 694H */
  volatile uint8  aaReserved37[3];
  volatile uint8  ucADCXnTHCR;                                       /* 698H */
  volatile uint8  aaReserved38[7];
  volatile Adc_TrackHoldStartType aaTHxHLDSTCR[ADC_NUM_OF_TH_GROUP]; /* 6A0H */
  volatile uint8  aaReserved39[7];
  volatile uint16 usADCXnTHGSR;                                      /* 6B0H */
  volatile uint8  aaReserved40[2];
  volatile uint8  ucADCXnTHER;                                       /* 6B4H */
  volatile uint8  aaReserved41[11];
  volatile Adc_TrackHoldGroupType aaTHxCR[ADC_NUM_OF_TH_GROUP];      /* 6C0H */
  volatile uint8  aaReserved42[55];
  volatile Adc_WaitTimeRegType aaWAITTR[ADC_NUM_OF_WAITTIME];        /* 700H */
  volatile uint8  aaReserved43[32];
  volatile uint8  ucADCXnVMONVDCR1;                                  /* 740H */
  volatile uint8  aaReserved44[3];
  volatile uint8  ucADCXnVMONVDCR2;                                  /* 744H */
  volatile uint8  aaReserved45[27];
  volatile uint8  ucADCXnTDCR;                                       /* 760H */
  volatile uint8  aaReserved46[3];
  volatile Adc_WireBreakRegType ddADCXnODCR;                         /* 764H */
  volatile uint8  aaReserved47[10];
  volatile uint8  ucADCXnSFTCR;                                      /* 770H */
  volatile uint8  aaReserved48[3];
  volatile uint8  ucADCXnTOCCR;                                      /* 774H */
  volatile uint8  aaReserved49[27];
  volatile uint8  ucADCXnTOCER;                                      /* 790H */
  volatile uint8  aaReserved50[11];
  volatile uint8  ucADCXnOWER;                                       /* 79CH */
  volatile uint8  aaReserved51[3];
  volatile uint8  ucADCXnPER;                                        /* 7A0H */
  volatile uint8  aaReserved52[3];
  volatile uint8  ucADCXnIDER;                                       /* 7A4H */
  volatile uint8  aaReserved53[3];
  volatile Adc_ErrClearRegType ddADCXnECR;                           /* 7A8H */
  volatile uint8  aaReserved54[86];
  volatile uint32 aaADCXnVCULLMTBRy[ADC_NUM_OF_LIMIT_TABLE];         /* 800H */
  volatile uint8  aaReserved55[32];
  volatile uint32 aaADCXnVCLMINTER[ADC_NUM_OF_LIMIT_REG];            /* 840H */
  volatile uint8  aaReserved56[4];
  volatile uint8  ucADCXnPWVCLMINTER;                                /* 84CH */
  volatile uint8  aaReserved57[3];
  volatile uint8  ucADCXnSDVCLMINTER;                                /* 850H */
  volatile uint8  aaReserved58[15];
  volatile uint32 aaADCXnVCLMSR[ADC_NUM_OF_LIMIT_REG];               /* 860H */
  volatile uint8  aaReserved59[4];
  volatile uint32 ulADCXnPWVCLMSR;                                   /* 86CH */
  volatile uint32 ulADCXnSDVCLMSR;                                   /* 870H */
  volatile uint8  aaReserved61[12];
  volatile uint16 usADCXnSGULCR0;                                    /* 880H */
  volatile uint8  aaReserved62[2];
  volatile uint16 usADCXnSGULCR1;                                    /* 884H */
  volatile uint8  aaReserved63[2];
  volatile uint16 usADCXnSGULCR2;                                    /* 888H */
  volatile uint8  aaReserved64[2];
  volatile uint16 usADCXnSGULCR3;                                    /* 88CH */
  volatile uint8  aaReserved65[2];
  volatile uint16 usADCXnSGULCR4;                                    /* 890H */
  volatile uint8  aaReserved66[2];
  volatile uint16 usADCXnSGDIAGULCR;                                 /* 894H */
  volatile uint8  aaReserved67[10];
  volatile uint32 aaADCXnVCLMSCR[ADC_NUM_OF_LIMIT_REG];              /* 8A0H */
  volatile uint8  aaReserved68[4];
  volatile uint8  ucADCXnPWVCLMSCR;                                  /* 8ACH */
  volatile uint8  aaReserved69[3];
  volatile uint8  ucADCXnSDVCLMSCR;                                  /* 8B0H */
  volatile uint8  aaReserved70[3];
  volatile uint8  ucADCXnSGULCCR;                                    /* 8B4H */
  volatile uint8  aaReserved71[3];
  volatile uint8  ucADCXnVCLMASCR;                                   /* 8B8H */
  volatile uint8  aaReserved72[3];

#endif /* (ADC_IP_C_ADCK == STD_OFF) */
} Adc_ConfigRegisters;                                                                                                  /* PRQA S 0639 # JV-01 */

/***********************************************************************************************************************
** Structure for Scan Group Start Trigger Control Registers                                                           **
***********************************************************************************************************************/
#if (ADC_ENABLE_ADC_TSEL == STD_ON)
typedef struct STag_Adc_SgTriggRegType                                                                                  /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* Scan Group x Start Trigger Control Register */
  volatile uint32 aaADCXnSGTSELx[ADC_NUM_SCANGROUP];
} Adc_SgTriggRegType;
#endif /* (ADC_ENABLE_ADC_TSEL == STD_ON) */

#if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
/***********************************************************************************************************************
** Structure for T&H Channel Select Registers                                                                         **
***********************************************************************************************************************/
typedef struct STag_Adc_TrackHoldSelectType                                                                             /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  volatile uint32 aaADCXnTHCHSz[ADC_NUM_OF_TH_CHANNEL_SELECT];
} Adc_TrackHoldSelectType;

/***********************************************************************************************************************
** Structure for T&H Channel Select Register Value                                                                    **
***********************************************************************************************************************/
typedef struct STag_Adc_TrackHoldChannelValueType                                                                       /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* T&H Channel Select Register Value */
  uint32 aaTnHChannelSelectValue[ADC_NUM_OF_TH_CHANNEL_SELECT];                                                         /* PRQA S 1039 # JV-01 */
} Adc_TrackHoldChannelValueType;
#endif /*(ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON) */

/***********************************************************************************************************************
** Structure for wait time configuration                                                                              **
***********************************************************************************************************************/
typedef struct STag_Adc_WaitTimeConfigType                                                                              /* PRQA S 1536 # JV-01 */
{
  /* Store value of ADCKnWAITTRy */
  uint16 usWAITTRy[ADC_NUM_OF_WAITTIME];
} Adc_WaitTimeConfigType;

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* ADC_ADCK_PBTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
