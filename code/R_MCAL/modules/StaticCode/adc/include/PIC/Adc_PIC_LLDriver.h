/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_PIC_LLDriver.h                                                                                  */
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
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3: 31/10/2024 : Update SW-VERSION 2.1.3
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 *                   : As part of QAC 10.3.0 support, following changes are made:
 *                     1.Add MISRA Msg (2:1039)
 * 2.0.1: 18/10/2023 : Support QAC Amendment 2, add message 1536
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define. Change Adc_Mapping.h to Adc_Memmap.h
 * 1.4.4: 21/06/2022 : Added structs of PIC2 registers except PIC2ADTCFGx register in U2Bx to U2Ax.
 * 1.4.3: 23/05/2022 : Updated QAC comments for U2Bx.
 *        11/05/2022 : Added the structures Adc_TriggConfigType and Adc_HwTriggConfigType.
 *        15/04/2022 : Added the macros for register initialization.
 *                     Added the structures for U2Bx HW triggers.
 * 1.4.1: 24/11/2021 : Changed the condition of compile switch to ADC_ENABLE_PIC_TSEL and ADC_ENABLE_PIC_COMMON.
 *                     Added instance 4 to the suppression of duplicate inclusion.
 * 1.3.2: 09/09/2021 : Changed the macros for register initialization.
 *        06/09/2021 : Update header file macro to call file multiple times.
 * 1.3.1: 07/07/2021 : Added QAC message 9.5.0
 *                     Changed comment format to 120 columns
 *                     Changed violation tag from START/END
 *        24/05/2021 : Added "extern" to external functions.
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.3.0: 06/12/2020 : Add new declaration of function Adc_PicInit
 *                     Remove type Adc_PicTriggOutConfigRegisters
 * 1.2.0: 14/07/2020 : Release
 *        27/07/2020 : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020 : Release
 * 1.0.1: 09/04/2020 : Add const qualifier for arguments of internal functions
 *                     that are never changed
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ADC_PIC_LLDRIVER_H
#define ADC_PIC_LLDRIVER_H


/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ADC_PIC_LLDRIVER_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION
#define ADC_PIC_LLDRIVER_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION
#define ADC_PIC_LLDRIVER_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ADC_PIC_LLDRIVER_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION
#define ADC_PIC_LLDRIVER_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1536)    : The tag '%1s' is declared but not used within this project.                                  */
/* Rule                : MISRA C:2012 Rule-2.4                                                                        */
/* JV-01 Justification : This is accepted. This tag is used by other file.                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1039)    : Treating array of length one as potentially flexible member.                                 */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2, CERTCCM DCL38                                                */
/* JV-01 Justification : Use array of length as the final member has no problem by manual reviewing.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Each function disable flag in conversion group */
#define ADC_HWTRIGG_OFF           (uint8)0xFFU

/* Flag/status clear value */
#define ADC_PIC2_ADCX_TSEL_INIT   (uint32)0x00000000UL
#define ADC_PIC2_ADCX_EDGSEL_INIT (uint16)0x0000U
#define ADC_PIC2_TRG_CTL_INIT     (uint32)0x00000000UL
#define ADC_PIC2_TRG_SEL_INIT     (uint16)0x0000U
#define ADC_PIC2_TRG_CFG_INIT     (uint32)0x00000000UL
#define ADC_PIC2_NOT_USED         (uint8)0x00U
#if (ADC_IP_ADCH == STD_ON)
#define ADC_PIC2_ADTEN_INIT       (Adc_Pic2ADTenType)0U
#endif /* (ADC_IP_ADCH == STD_ON) */

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

#if (ADC_ENABLE_PIC_TSEL == STD_ON)
#if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
/***********************************************************************************************************************
** Structure for A/D Converter Trigger Configuration Registers                                                        **
***********************************************************************************************************************/
typedef struct STag_Adc_PicTriggRegType                                                                                 /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* Trigger Selection Control Register */
  volatile uint32 aaPIC2ADCXnTSELj[ADC_NUM_SCANGROUP];
  volatile uint32 aaReserved0[2];
  /* Trigger Edge Selection Control Register */
  volatile uint16 usPIC2ADCXnEDGSEL;
} Adc_PicTriggRegType;

/***********************************************************************************************************************
** Structure for A/D Converter Trigger Output Control Register                                                        **
***********************************************************************************************************************/
typedef struct STag_Adc_PicTriggControlRegType                                                                          /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* Trigger Output Control Register */
  volatile uint32 aaPIC2ADTENxnj[ADC_NUM_SCANGROUP];
} Adc_PicTriggControlRegType;

/***********************************************************************************************************************
** Structure for A/D Converter Trigger Output Control Registers                                                       **
***********************************************************************************************************************/
typedef struct STag_Adc_PicTriggControlRegsType                                                                         /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* Trigger Output Control Registers */
  P2VAR(volatile Adc_PicTriggControlRegType, TYPEDEF, REGSPACE) aaPicTriggControlRegs[ADC_NUM_OF_PIC_CONTROL];          /* PRQA S 1039 # JV-01 */
} Adc_PicTriggControlRegsType;

/***********************************************************************************************************************
** Structure for A/D Converter Trigger Output Control Register Value                                                  **
***********************************************************************************************************************/
typedef struct STag_Adc_PicTriggControlValueType                                                                        /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* Trigger Output Control Register Value */
  uint32 aaPicTriggControlValue[ADC_NUM_OF_PIC_CONTROL];                                                                /* PRQA S 1039 # JV-01 */
  /* Flags that indicate which triggers are used */
  uint8 ucPicTriggControlUsed;
} Adc_PicTriggControlValueType;

/***********************************************************************************************************************
** Structure for A/D Converter Trigger Output Selection Control Register                                              **
***********************************************************************************************************************/
typedef struct STag_Adc_PicTriggSelectRegType                                                                           /* PRQA S 1536 # JV-01 */
{
  /* Trigger Output Selection Control Register */
  volatile uint16 usPIC2ADTENxnj;
  volatile uint8  aaReserved0[2];
} Adc_PicTriggSelectRegType;

/***********************************************************************************************************************
** Structure for A/D Converter Trigger Output Selection Control Registers                                             **
***********************************************************************************************************************/
typedef struct STag_Adc_PicTriggSelectRegsType                                                                          /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* Trigger Output Selection Control Registers */
  volatile Adc_PicTriggSelectRegType aaPicTriggSelectReg[ADC_NUM_SCANGROUP];
} Adc_PicTriggSelectRegsType;

/***********************************************************************************************************************
** Structure for A/D Converter Trigger Output Selection Control Register Group                                        **
***********************************************************************************************************************/
typedef struct STag_Adc_PicTriggSelectRegGroupType                                                                      /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* Trigger Output Selection Control Register Group */
  P2VAR(volatile Adc_PicTriggSelectRegsType, TYPEDEF, REGSPACE) aaPicTriggSelectRegs[ADC_NUM_OF_PIC_SELECT];
} Adc_PicTriggSelectRegGroupType;

/***********************************************************************************************************************
** Structure for A/D Converter Trigger Output Selection Control Register Value                                        **
***********************************************************************************************************************/
typedef struct STag_Adc_PicTriggSelectValueType                                                                         /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* Trigger Output Selection Control Register Value*/
  uint16 aaPicTriggSelectValue[ADC_NUM_OF_PIC_SELECT];
  /* Flags that indicate which triggers are used */
  uint8 ucPicTriggSelectUsed;
} Adc_PicTriggSelectValueType;

/***********************************************************************************************************************
** Structure for A/D Converter Trigger Output Configuration Register                                                  **
***********************************************************************************************************************/
#if (ADC_IP_ADCK == STD_ON)
typedef struct STag_Adc_PicTriggConfigRegType                                                                           /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* Trigger Output Configuration Register */
  volatile uint32 aaPIC2ADTCFGk[ADC_NUM_OF_PIC_CONFIG];
} Adc_PicTriggConfigRegType;
#endif /* (ADC_IP_ADCK == STD_ON) */

/***********************************************************************************************************************
** Structure for A/D Converter n Trigger Control Register Value                                                       **
***********************************************************************************************************************/
typedef struct STag_Adc_TriggConfigType                                                                                 /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* A/D Converter n Trigger Selection Control Register Value */
  uint32 aaTriggSelect[ADC_NUM_OF_TRIGG_SELECT];
  /* A/D Converter n Trigger Edge Selection Control Register Value */
  uint16 usTriggEdge;
} Adc_TriggConfigType;

/***********************************************************************************************************************
** Structure for A/D Converter Trigger Configuration                                                                  **
***********************************************************************************************************************/
typedef struct STag_Adc_HwTriggConfigType                                                                               /* PRQA S 3630, 1536 # JV-01, JV-01 */
{
  /* Structure for A/D Converter n Trigger Control Register Value */
  P2CONST(Adc_TriggConfigType, TYPEDEF, ADC_CONFIG_DATA) pTriggConfig;

  /* Structure for A/D Converter Trigger Output Control Register Value */
  P2CONST(Adc_PicTriggControlValueType, TYPEDEF, ADC_CONFIG_DATA) pPicTriggControlValue;

  /* Structure for A/D Converter Trigger Output Selection Control Register Group */
  P2CONST(Adc_PicTriggSelectRegGroupType, TYPEDEF, ADC_CONFIG_DATA) pPicTriggSelectReg;

  /* Structure for A/D Converter Trigger Output Selection Control Register Value */
  P2CONST(Adc_PicTriggSelectValueType, TYPEDEF, ADC_CONFIG_DATA) pPicTriggSelectValue;

  /* Structure for A/D Converter Trigger Output Selection Control Current Value */
  P2VAR(volatile Adc_PicTriggSelectValueType, TYPEDEF, ADC_VAR_NO_INIT) pPicTriggSelectCurrent;

  #if (ADC_IP_ADCK == STD_ON)
  /* Structure for A/D Converter Trigger Output Configuration Register */
  P2VAR(volatile Adc_PicTriggConfigRegType, TYPEDEF, REGSPACE) pPicTriggConfigReg;

  /* Structure for A/D Converter Trigger Output Configuration Register Value */
  P2CONST(uint32, TYPEDEF, ADC_CONFIG_DATA) pPicTriggConfigValue;

  /* Flags used in A/D Converter Trigger Output Configuration Register */
  uint32 ulPicTriggConfigUsed;
  #endif /* (ADC_IP_ADCK == STD_ON) */
} Adc_HwTriggConfigType;

#endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
#if (ADC_IP_ADCH == STD_ON)
/***********************************************************************************************************************
** Structure for SG Unit PIC Trigger registers                                                                        **
***********************************************************************************************************************/
typedef struct STag_Adc_PicRegisters
{
  /* PIC register for AD converter trigger selection control */
  volatile uint32 ulPIC2ADCnTSELx[5];
  volatile uint32 aaReserved0[2];
  /* PIC register for AD converter trigger selection control */
  volatile uint16 usPIC2ADCnEDGSEL;
} Adc_PicRegisters;

/***********************************************************************************************************************
** Structure for PIC2ADTEN Registers, which are used to read or write                                                 **
** the status or configured values for proper working of the ADC driver                                               **
***********************************************************************************************************************/
typedef struct STag_Adc_PicTenRegisters
{
  /* PIC register for AD converter trigger output control */
  volatile uint32 ulPIC2ADTENnx[5];
} Adc_PicTenRegisters;

/***********************************************************************************************************************
** Structure for SG Unit Trigger values                                                                               **
***********************************************************************************************************************/
typedef struct STag_Adc_PicConfigType
{
  /* Mask value for AD converter HW trigger register */
  Adc_Pic2ADTenType ddPICADTENxMask[ADC_NUM_OF_TEN_GROUP];
} Adc_PicConfigType;

#endif /* (ADC_IP_ADCH == STD_ON) */
#endif /* (ADC_ENABLE_PIC_TSEL == STD_ON) */

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#if (ADC_ENABLE_PIC_TSEL == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"

#if ((ADC_ENABLE_PIC_COMMON == STD_ON) || (ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
extern FUNC(void, ADC_PRIVATE_CODE) Adc_PicInit(void);
#endif /* ((ADC_ENABLE_PIC_COMMON == STD_ON) || (ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */

#if (ADC_DEINIT_API == STD_ON)
extern FUNC(void, ADC_PRIVATE_CODE) Adc_PicDeInit(void);
#endif /* (ADC_DEINIT_API == STD_ON) */

extern FUNC(void, ADC_PRIVATE_CODE) Adc_PicClearHwTrigger(const Adc_GroupType LddGroup);
extern FUNC(void, ADC_PRIVATE_CODE) Adc_PicEnableHwTrigger(const Adc_GroupType LddGroup);
extern FUNC(void, ADC_PRIVATE_CODE) Adc_PicDisableHwTrigger(const Adc_GroupType LddGroup);

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"

#endif /* (ADC_ENABLE_PIC_TSEL == STD_ON) */

#endif /* ADC_PIC_LLDRIVER_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
