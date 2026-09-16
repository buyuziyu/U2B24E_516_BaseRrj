/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_sDMAC_LLDriver.h                                                                                */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Private functions declarations.                                                                                    */
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
 * 2.5.0: 30/06/2025 : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.4.0: 31/05/2025 : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.1: 28/02/2025 : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : As part of ARDAACJ-591 support, following changes are made:
 *                     1.Add macro ADC_DIR_IDEF_WFLAG to check Adc data buffer
 *                     As part of ARDAACJ-572 support, following changes are made:
 *                     1.Added macro ADC_DMA_TMR_DTS_4 to support DMA destination transaction 4-byte
 *                     2.Add preprocessor directive ADC_RESULT_DATA_TYPE to support DMA transfer 4-byte data
 * 2.1.3: 31/10/2024 : Update SW-VERSION 2.1.3
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 *                   : As part of U2Cx support, following changes are made:
 *                     1.Add the condition of macro ADC_IP_C_ADCK to generate macros for handling DMA transfer request 
 * 2.0.1: 18/10/2023 : Support QAC Amendment 2, add message 1534, 1536
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define. Change Adc_Mapping.h to Adc_Memmap.h
 * 1.4.4: 08/09/2022 : Removed macros ADC_DMA_TMR_DM_INC, ADC_DMA_TMR_SM_INC, ADC_DMA_CHCR_IE, ADC_DMA_CHCR_CAIE,
 *                     ADC_DMA_CHFCR_DPEC, ADC_DMA_DPPTR_PTR_MASK.
 *                     Added macros ADC_DMA_TMR_STS_2, ADC_DMA_CHCR_CAEE, ADC_DMA_CHFCR_CAEC
 * 1.4.3: 18/05/2022 : Fixed the typos in comments.
 * 1.4.1: 25/11/2021 : Added macros for handling DMA Transfer Request Group Selection Register.
 *                     Added instance 4 to the suppression of duplicate inclusion.
 * 1.4.0: 13/10/2021 : Removed macro ADC_DMA_SG_OUTER_HALF and ADC_DMA_RS_TL_DTS.
 *                     Added macro ADC_DMA_RS_TL_TSR.
 * 1.3.2: 16/09/2021 : Changed macros for DMA transfer settings.
 *        09/09/2021 : Added structures for storing DMA descriptors.
 *                     Changed the names of macros for handling DMA.
 *        06/09/2021 : Update header file macro to call file multiple times.
 * 1.3.1: 17/07/2021 : Removed unnecessary macro.
 *        07/07/2021 : Added QAC message 9.5.0
 *                     Changed comment format to 120 columns
 *                     Changed violation tag from START/END
 *        24/06/2021 : Removed the macro that not using.
 *        24/05/2021 : Added "extern" to external functions.
 *                     Change the position of an external function declaration.
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.3.0: 23/12/2020 : Change return type of Adc_DmaDisable to boolean
 * 1.2.0: 14/07/2020 : Release
 *        27/07/2020 : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020 : Release
 * 1.0.2: 18/06/2020 : Add macro ADC_DMA_CLEAR_CHANNEL_CONTROL
 * 1.0.1: 09/04/2020 : Add const qualifier for arguments of internal functions
 *                     that are never changed
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ADC_SDMAC_LLDRIVER_H
#define ADC_SDMAC_LLDRIVER_H


/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ADC_SDMAC_LLDRIVER_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION
#define ADC_SDMAC_LLDRIVER_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION
#define ADC_SDMAC_LLDRIVER_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ADC_SDMAC_LLDRIVER_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION
#define ADC_SDMAC_LLDRIVER_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
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
/* DMA function setting value */

/* Macros for register initialization */
#define ADC_DMA_SAR_INIT                     (uint32)0x00000000UL
#define ADC_DMA_DAR_INIT                     (uint32)0x00000000UL
#define ADC_DMA_TSR_INIT                     (uint32)0x00000000UL
#define ADC_DMA_GIAI_INIT                    (uint32)0x00000000UL
#define ADC_DMA_GOAI_INIT                    (uint32)0x00000000UL
#define ADC_DMA_SIAI_INIT                    (uint32)0x00000000UL
#define ADC_DMA_SOAI_INIT                    (uint32)0x00000000UL
#define ADC_DMA_SGCR_INIT                    (uint32)0x00000000UL
#define ADC_DMA_RS_INIT                      (uint32)0x00000000UL
#define ADC_DMA_DPPTR_INIT                   (uint32)0x00000000UL
#define ADC_DMA_DPCR_INIT                    (uint32)0x00000000UL
#define ADC_DMACSEL0_INIT                    (uint32)0x00000000UL                                                       /* PRQA S 1534 # JV-01 */
#define ADC_DMACSEL1_INIT                    (uint32)0x55555555UL

/* Macros for handling DMA transfer request group selection register */
#define ADC_DMA_CSEL_SHIFT_MASK              (uint32)0x0000000FUL                                                       /* PRQA S 1534 # JV-01 */
#if (ADC_IP_C_ADCK == STD_OFF)
#define ADC_DMA_CSEL_MASK                    (uint32)0x00000003UL
#else
#define ADC_DMA_CSEL_MASK                    (uint32)0x00000001UL
#endif

/* Channel request priority setting mask */
#define ADC_DMA_TMR_PRI_MASK                 (uint32)(0x0FUL << 16U)
/* Transfer request source (1: Hardware request) */
#define ADC_DMA_TMR_TRS                      (uint32)(1UL << 12U)
/* DMA destination transaction size (1:2-byte, 2:4-byte,...) */
#define ADC_DMA_TMR_DTS_2                    (uint32)(1UL << 4U)
/* DMA destination transaction size (1:2-byte, 2:4-byte,...) */
#define ADC_DMA_TMR_DTS_4                    (uint32)(2UL << 4U)
/* DMA source transaction size (1:2-byte, 2:4-byte,...) */
#define ADC_DMA_TMR_STS_2                    (uint32)(1UL << 0U)
/* DMA source transaction size (1:2-byte, 2:4-byte,...) */
#define ADC_DMA_TMR_STS_4                    (uint32)(2UL << 0U)                                                        /* PRQA S 1534 # JV-01 */

/* DMA enable */
#define ADC_DMA_CHCR_DE                      (uint16)(1UL << 0U)
/* Descriptor step end interrupt enable */
#define ADC_DMA_CHCR_DSIE                    (uint16)(1UL << 2U)
/* Channel address error interrupt INTSDMACERR enable */
#define ADC_DMA_CHCR_CAEE                    (uint16)(1UL << 4U)
/* Descriptor start */
#define ADC_DMA_CHCR_DPB                     (uint16)(1UL << 8U)
/* Descriptor enable */
#define ADC_DMA_CHCR_DPE                     (uint16)(1UL << 9U)

/* Channel busy flag */
#define ADC_DMA_CHSTA_BUSY                   (uint32)(1UL << 0U)
/* Transfer end flag */
#define ADC_DMA_CHSTA_TE                     (uint32)(1UL << 1U)
/* Descriptor step end flag */
#define ADC_DMA_CHSTA_DSE                    (uint32)(1UL << 2U)

/* DMA enable clear */
#define ADC_DMA_CHFCR_DEC                    (uint32)(1UL << 0U)
/* Transfer end flag clear */
#define ADC_DMA_CHFCR_TEC                    (uint32)(1UL << 1U)
/* Descriptor step end flag clear */
#define ADC_DMA_CHFCR_DSEC                   (uint32)(1UL << 2U)
/* Address error flag clear */
#define ADC_DMA_CHFCR_CAEC                   (uint32)(1UL << 3U)
/* Hardware transfer request clear */
#define ADC_DMA_CHFCR_DRQC                   (uint32)(1UL << 12U)
/* Hardware transfer request overflow flag clear */
#define ADC_DMA_CHFCR_OVFC                   (uint32)(1UL << 13U)

/* Scatter enable on source side */
#define ADC_DMA_SGCR_SEN                     (uint32)(1UL << 31U)
/* Gather enable on destination side*/
#define ADC_DMA_SGCR_GEN                     (uint32)(1UL << 15U)
/* Number of shifts to set the SIRPT bits */
#define ADC_DMA_SGCR_SIRPT_SFT               16U

/* Number of shifts to set the TC bits */
#define ADC_DMA_RS_TC_SFT                    16U
/* Transfer limit per hardware request (0:STS*TC, 1:DTS*TC, 2:TSR, 3:DSE, 4:TE) */
#define ADC_DMA_RS_TL_TSR                    (uint32)(2UL << 12U)                                                       /* PRQA S 1534 # JV-01 */

/* Descriptor interrupt enable */
#define ADC_DMA_DPPTR_DIE                    (uint32)(1UL << 1U)
/* Continuation flag of descriptor */
#define ADC_DMA_DPPTR_CF                     (uint32)(1UL << 0U)

/* Update flag of descriptor */
#define ADC_DMA_DPCR_UPF_SAR                 (uint32)(1UL << 0UL)
#define ADC_DMA_DPCR_UPF_DAR                 (uint32)(1UL << 1UL)
#define ADC_DMA_DPCR_UPF_TSR                 (uint32)(1UL << 2UL)

/* Transfer data size (sizeof Adc_ValueGroupType */
#if (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS)
#define ADC_DMA_DATA_SIZE                    (uint32)0x00000002UL
#else
#define ADC_DMA_DATA_SIZE                    (uint32)0x00000004UL
#endif /* (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS) */

/* Source transaction size (sizeof ADCXnDRj * 2 or sizeof ADCXnDIRj) */
#define ADC_DMA_STS_SIZE                     (uint32)0x00000004UL

/* Number of descriptor in descriptor set */
#define ADC_DMA_DESC_NUM                     2U

/* ID Error and Write Flag in ADCXnDIRj */
#define ADC_DIR_IDEF_WFLAG                   (uint32)(3UL << 25U)

/* Macro for DMA channel */
#define ADC_DMA_CHANNEL_0                    (uint8)0x00U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_1                    (uint8)0x01U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_2                    (uint8)0x02U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_3                    (uint8)0x03U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_4                    (uint8)0x04U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_5                    (uint8)0x05U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_6                    (uint8)0x06U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_7                    (uint8)0x07U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_8                    (uint8)0x08U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_9                    (uint8)0x09U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_10                   (uint8)0x0AU                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_11                   (uint8)0x0BU                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_12                   (uint8)0x0CU                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_13                   (uint8)0x0DU                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_14                   (uint8)0x0EU                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_15                   (uint8)0x0FU                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_16                   (uint8)0x10U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_17                   (uint8)0x11U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_18                   (uint8)0x12U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_19                   (uint8)0x13U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_20                   (uint8)0x14U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_21                   (uint8)0x15U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_22                   (uint8)0x16U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_23                   (uint8)0x17U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_24                   (uint8)0x18U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_25                   (uint8)0x19U                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_26                   (uint8)0x1AU                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_27                   (uint8)0x1BU                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_28                   (uint8)0x1CU                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_29                   (uint8)0x1DU                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_30                   (uint8)0x1EU                                                               /* PRQA S 1534 # JV-01 */
#define ADC_DMA_CHANNEL_31                   (uint8)0x1FU                                                               /* PRQA S 1534 # JV-01 */

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Structure for sDMAC Registers, which are used to read or write                                                     **
** the status or configured values for proper working of the sDMAC                                                    **
***********************************************************************************************************************/
#if (ADC_ENABLE_DMA_MODE == STD_ON)
typedef struct STag_Adc_DmaRegisters                                                                                    /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* DMA source address register */
  volatile uint32 ulDMAjSARn;                                        /* 00H */
  /* DMA destination address register */
  volatile uint32 ulDMAjDARn;                                        /* 04H */
  /* DMA transfer size register */
  volatile uint32 ulDMAjTSRn;                                        /* 08H */
  /* DMA transfer size register B */
  volatile uint32 ulDMAjTSRBn;                                       /* 0CH */
  /* DMA transfer mode register */
  volatile uint32 ulDMAjTMRn;                                        /* 10H */
  /* DMA channel control register */
  volatile uint16 usDMAjCHCRn;                                       /* 14H */
  /* DMA channel stop register */
  volatile uint16 usDMAjCHSTPn;                                      /* 16H */
  /* DMA channel status register */
  volatile uint32 ulDMAjCHSTAn;                                      /* 18H */
  /* DMA channel flag clear register */
  volatile uint32 ulDMAjCHFCRn;                                      /* 1CH */
  /* DMA gather inner address increment register */
  volatile uint32 ulDMAjGIAIn;                                       /* 20H */
  /* DMA gather outer address increment register */
  volatile uint32 ulDMAjGOAIn;                                       /* 24H */
  /* DMA scatter inner address increment register */
  volatile uint32 ulDMAjSIAIn;                                       /* 28H */
  /* DMA scatter outer address increment register */
  volatile uint32 ulDMAjSOAIn;                                       /* 2CH */
  volatile uint32 aaReserved1[2];
  /* DMA scatter gather status register */
  volatile uint32 ulDMAjSGSTn;                                       /* 38H */
  /* DMA scatter gather control register */
  volatile uint32 ulDMAjSGCRn;                                       /* 3CH */
  /* DMA resource select register */
  volatile uint32 ulDMAjRSn;                                         /* 40H */
  volatile uint32 aaReserved2;
  /* DMA buffer control registers */
  volatile uint32 ulDMAjBUFCRn;                                      /* 48H */
  volatile uint32 aaReserved3;
  /* DMA descriptor pointer register */
  volatile uint32 ulDMAjDPPTRn;                                      /* 50H */
  /* DMA descriptor control register */
  volatile uint32 ulDMAjDPCRn;                                       /* 54H */
} Adc_DmaRegisters;

/* Structure for DMA descriptor */
typedef struct STag_Adc_DmaDescType                                                                                     /* PRQA S 1536 # JV-01 */
{
  /* DMA source address register */
  volatile uint32 ulDMAjSARn;                                        /* 00H */
  /* DMA destination address register */
  volatile uint32 ulDMAjDARn;                                        /* 04H */
  /* DMA transfer size register */
  volatile uint32 ulDMAjTSRn;                                        /* 08H */
  /* DMA descriptor pointer register */
  volatile uint32 ulDMAjDPPTRn;                                      /* 0CH */
} Adc_DmaDescType;

/* Structure for DMA descriptor set */
typedef struct STag_Adc_DmaDescSetType                                                                                  /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* Two descriptors that are used alternately in a continuous transfer */
  Adc_DmaDescType aaDmaDesc[ADC_DMA_DESC_NUM];
} Adc_DmaDescSetType;

#endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#if (ADC_ENABLE_DMA_MODE == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"

extern FUNC(void, ADC_PRIVATE_CODE) Adc_DmaInit(void);

#if (ADC_DEINIT_API == STD_ON)
extern FUNC(void, ADC_PRIVATE_CODE) Adc_DmaDeInit(void);
#endif /* (ADC_DEINIT_API == STD_ON) */

extern FUNC(void, ADC_PRIVATE_CODE) Adc_DmaEnable(const Adc_GroupType LddGroup);
extern FUNC(boolean, ADC_PRIVATE_CODE) Adc_DmaDisable(const Adc_GroupType LddGroup);
extern FUNC(boolean, ADC_PRIVATE_CODE) Adc_DmaGetTransferStatus(const Adc_GroupType LddGroup);
extern FUNC(void, ADC_PRIVATE_CODE) Adc_DmaClearInterruptFlag(const Adc_GroupType LddGroup);

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"

#endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
#endif /* ADC_SDMAC_LLDRIVER_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
