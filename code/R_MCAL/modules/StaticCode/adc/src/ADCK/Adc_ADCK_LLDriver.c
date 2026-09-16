/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_ADCK_LLDriver.c                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2021-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Internal functions implementation of ADC Driver Component                                                          */
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
 *        24/05/2025 : Update Adc_TrackHoldEnable() about removing macro for variable LulCount
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                   : As part of ARDAACL-53492 and ARDAACL-53486, following changes are made to Adc_TrackHoldEnable():
 *                     1. Update the sequence setting for the T&H registers according to the HW's setting flow.
 *                     2. Add a condition to set ADCKnSGSTCRx to 0x01U to initiate conversion in SW trigger mode.
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3: 31/10/2024 : Update SW-VERSION 2.1.3
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 *                   : As part of U2Bx-E support, following changes are made:
 *                     1.Update function Adc_TrackHoldInit and Adc_TrackHoldDeInit,Adc_TrackHoldEnable,
 *                       Adc_TrackHoldDisable to support U2Bx-E
 *                   : As part of U2Cx support, following changes are made:
 *                     1.Add new functions to support PWM-Diag feature: Adc_PwmDiagInit, Adc_PwmDiagDeInit, 
 *                       Adc_PwmDiagReadData, Adc_PwmDiagEnable, Adc_PwmDiagDisable, Adc_PicDisableHwTrigger
 *                     2.Update function invoked for Adc_AdcDeInit, Adc_AdcInit
 *                     3.Add the condition of macro ADC_IP_C_ADCK in Adc_AdcDeInit, Adc_AdcInit
 * 2.0.1: 18/10/2023 : Fix QAC support Amendment 2
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define. Change Adc_Mapping.h to Adc_Memmap.h
 *        03/08/2023 : Add new QAC message PRQA (2:1006).
 * 1.4.5: 14/09/2022 : Updated QAC messages according to QAC analysis results.
 *        12/09/2022 : Replaced the empty else blocks, not from else if, with comments.
 *                     Fixed comments about 'No action required' and 'end of'.
 * 1.4.4: 31/08/2022 : Fixed typos in comments due to review findings.
 *        24/08/2022 : Updated information in function header comments.
 *        21/07/2022 : Updated PRQA comments based on the result of static analysis.
 *                     Fixed the index of aaTHxCR in Adc_TrackHoldDisable.
 *                     Renamed the member aaADCKnSGTSELx in the struct Adc_SgTriggRegType to aaADCXnSGTSELx.
 *                     Updated Re-entrancy and Reference IDs in function header comments.
 *        12/07/2022 : Added SG stop to function Adc_TrackHoldDisable.
 *                     Added T&H sampling status settings to function Adc_TrackHoldEnable.
 *        29/06/2022 : Added the branch condition of SW triggered to the start of T&H holding in Adc_TrackHoldEnable.
 *        16/06/2022 : Changed variable for judgement of T&H from blHasTrackHold to ucTrackHoldEnable.
 * 1.4.3: 25/05/2022 : Removed unnecessary coding rule messages in header comment.
 *                     Updated QAC comments for U2Bx..
 *        17/05/2022 : Added calls to Adc_TrackHoldInit and Adc_SetWaitTime to Adc_AdcInit and changed them to STATIC.
 *                     Added calls to Adc_TrackHoldDeInit and Adc_DeInitWaitTime to Adc_AdcDeInit and changed them to
 *                     STATIC.
 *                     Renamed ucSgUnitIndex in HW unit config to ucSgUnitOffset.
 *                     Renamed ucTrackHoldMask in HW unit config to ucTrackHoldEnable.
 *                     Changed the wait count at the start of T&H from macro to member of HW unit config.
 *        15/04/2022 : Fixed the argument of prototype for HW trigger init/deinit.
 *                     Changed the condition of whether to use ADC trigger selection to pointer check.
 *                     Changed the trigger configuration to the new structure.
 * 1.4.1: 24/11/2021 : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for version check macro definitions and type definitions */
#include "Adc.h"

/* Included for RAM variable declarations */
#include "Adc_Ram.h"
/* Included for the declaration of internal function prototypes */
#include "Adc_ADCK_LLDriver.h"
#include "Adc_ADCK_PBTypes.h"

/* Included for the macro declaration of supervisor mode(SV) write enabled Registers IMR & ICxxx */
#include "rh850_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define ADC_ADCK_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION_VALUE
#define ADC_ADCK_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION_VALUE
#define ADC_ADCK_LLDRIVER_C_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ADC_ADCK_LLDRIVER_C_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION_VALUE
#define ADC_ADCK_LLDRIVER_C_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ADC_ADCK_LLDRIVER_AR_RELEASE_MAJOR_VERSION != ADC_ADCK_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Adc_ADCK_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (ADC_ADCK_LLDRIVER_AR_RELEASE_MINOR_VERSION != ADC_ADCK_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Adc_ADCK_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (ADC_ADCK_LLDRIVER_AR_RELEASE_REVISION_VERSION != ADC_ADCK_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Adc_ADCK_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (ADC_ADCK_LLDRIVER_SW_MAJOR_VERSION != ADC_ADCK_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Adc_ADCK_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (ADC_ADCK_LLDRIVER_SW_MINOR_VERSION != ADC_ADCK_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Adc_ADCK_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : MISRA C:2012 Rule-11.4, CERTCCM INT36, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : This in-line assembler construct is a language extension. The code has been ignored.         */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTCCM MSC14                                       */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1532)    : The function '%1s' is only referenced in one translation unit - but not the one in which it  */
/*                       is defined.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.7, CERTCCM DCL19, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This macro identifier is following AUTOSAR standard rule  (Symbolic Name or Published        */
/*                       Macro's name), so this is accepted                                                           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-476, CWE-465, CWE-737, CWE-690                                   */
/* JV-01 Justification : This is accepted, due to the implementation following hardware specification.                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2824)    : Possible: Arithmetic operation on NULL pointer.                                              */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-468, CWE-476, CWE-465, CWE-737                                   */
/* JV-01 Justification : This is accepted, due to the implementation following hardware specification.                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2844)    : Possible: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127,       */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : It is specific for device register accessing and confirmed has no issue in software behavior.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2934)    : Possible: Computing an invalid pointer value.                                                */
/* Rule                : CERTCCM EXP08, ARR30, ARR37, ARR38, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125,    */
/*                       CWE-126, CWE-127, CWE-129, CWE-131, CWE-469, CWE-823, CWE-465, CWE-633, CWE-740              */
/* JV-01 Justification : This message prevents existing of an out-of-range pointer                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"

#if (ADC_ENABLE_ADC_TSEL == STD_ON)
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_HwTriggerInit(const uint8 LucHwUnitIndex);
#if (ADC_DEINIT_API == STD_ON)
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_HwTriggerDeInit(const uint8 LucHwUnitIndex);
#endif /* (ADC_DEINIT_API == STD_ON) */
#endif /* (ADC_ENABLE_ADC_TSEL == STD_ON) */

#if (ADC_TRACK_AND_HOLD == STD_ON)
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_TrackHoldInit(const uint8 LucHwUnitIndex);
#if (ADC_DEINIT_API == STD_ON)
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_TrackHoldDeInit(const uint8 LucHwUnitIndex);
#endif /* (ADC_DEINIT_API == STD_ON) */
#endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_SetWaitTime(const uint8 LucHwUnitIndex);
#if (ADC_DEINIT_API == STD_ON)
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_DeInitWaitTime(const uint8 LucHwUnitIndex);
#endif /* (ADC_DEINIT_API == STD_ON) */

#if (ADC_ENABLE_PWM_DIAG == STD_ON)
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_PwmDiagInit(const uint8 LucHwUnitIndex);
#if (ADC_DEINIT_API == STD_ON)
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_PwmDiagDeInit(const uint8 LucHwUnitIndex);
#endif /* (ADC_DEINIT_API == STD_ON) */
#endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name        : Adc_AdcInit
**
** Service ID           : NA
**
** Description          : This internal function performs the initialization of the device-specific hardware registers
**                        of the ADC.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : LucHwUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig
**
** Functions invoked    : Adc_HwTriggerInit, Adc_TrackHoldInit, Adc_SetWaitTime
**
** Registers Used       : ADCXnDFASENTSGER, ADCXnSDVCLMINTER, ADCXnSGDIAGPCCR0, ADCXnSGDIAGPCCR1, ADCXnSGDIAGVCR0,
**                        ADCXnSGDIAGVCR1, ADCXnSGDIAGVCR2, ADCXnSTPDCR0, ADCXnSTPDCR1, ADCXnSTPDCR2, ADCXnSGDIAGCR
**
** Reference ID         : ADC_DUD_ACT_084, ADC_DUD_ACT_084_REG001, ADC_DUD_ACT_084_REG002,
** Reference ID         : ADC_DUD_ACT_084_REG003, ADC_DUD_ACT_084_REG004, ADC_DUD_ACT_084_REG005,
** Reference ID         : ADC_DUD_ACT_084_REG006, ADC_DUD_ACT_084_REG007, ADC_DUD_ACT_084_REG008,
** Reference ID         : ADC_DUD_ACT_084_REG009, ADC_DUD_ACT_084_REG010, ADC_DUD_ACT_084_REG011
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_AdcInit(const uint8 LucHwUnitIndex)                                                    /* PRQA S 1532 # JV-01 */
{
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;

  /* Initialize the local variable for HW unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Read the user base configuration address of the HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */

  /* Initialize the device-specific hardware registers of the ADC */
  #if (ADC_IP_C_ADCK == STD_OFF)
  LpAdcRegisters->usADCXnDFASENTSGER = ADC_WORD_ZERO;                                                                   /* PRQA S 2814 # JV-01 */
  #else
  LpAdcRegisters->usADCXnGTMENTSGER = ADC_WORD_ZERO;                                                                    /* PRQA S 2814 # JV-01 */
  #endif /*(ADC_IP_C_ADCK == STD_OFF)*/
  LpAdcRegisters->ucADCXnSDVCLMINTER = ADC_BYTE_ZERO;
  LpAdcRegisters->ulADCXnSGDIAGPCCR0 = ADC_DWORD_ZERO;
  LpAdcRegisters->ulADCXnSGDIAGPCCR1 = ADC_DWORD_ZERO;
  LpAdcRegisters->ucADCXnSGDIAGVCR0  = ADC_BYTE_ZERO;
  LpAdcRegisters->ucADCXnSGDIAGVCR1  = ADC_BYTE_ZERO;
  LpAdcRegisters->ucADCXnSGDIAGVCR2  = ADC_BYTE_ZERO;
  #if (ADC_IP_C_ADCK == STD_OFF)
  LpAdcRegisters->ucADCXnSTPDCR0     = ADC_BYTE_ZERO;
  LpAdcRegisters->ucADCXnSTPDCR1     = ADC_BYTE_ZERO;
  LpAdcRegisters->ucADCXnSTPDCR2     = ADC_BYTE_ZERO;
  #endif /* (ADC_IP_C_ADCK == STD_OFF) */
  LpAdcRegisters->ulADCXnSGDIAGCR    = ADC_DWORD_ZERO;

  #if (ADC_ENABLE_ADC_TSEL == STD_ON)
  /* Check if HW unit has ADC trigger selection register */
  if (NULL_PTR != LpHwUnitConfig->pSgTriggReg)
  {
    /* Initialization of ADC trigger selection register */
    Adc_HwTriggerInit(LucHwUnitIndex);
  } /* else: No action required */
  #endif /* (ADC_ENABLE_ADC_TSEL == STD_ON) */

  #if (ADC_TRACK_AND_HOLD == STD_ON)
  /* Check if HW unit has Track and Hold groups */
  if ((uint8)0U != LpHwUnitConfig->ucTrackHoldEnable)
  {
    /* Initialization of Track and Hold */
    Adc_TrackHoldInit(LucHwUnitIndex);
  } /* else: No action required */
  #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

  /* Check if HW unit has wait time configuration */
  if (ADC_WAITTIME_DISABLED != LpHwUnitConfig->ucWaitTimeIndex)
  {
    /* Initialization of wait time configuration */
    Adc_SetWaitTime(LucHwUnitIndex);
  } /* else: No action required */

  #if (ADC_ENABLE_PWM_DIAG == STD_ON)
  /* Initialize PWM-Diag registers */
  Adc_PwmDiagInit(LucHwUnitIndex);
  #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_AdcDeInit
**
** Service ID           : NA
**
** Description          : This internal function performs the de-initialization of the device-specific ADC hardware
**                        registers.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : LucHwUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig
**
** Functions invoked    : Adc_HwTriggerDeInit, Adc_TrackHoldDeInit, Adc_DeInitWaitTime, Adc_PwmDiagDeInit
**
** Registers Used       : ADCXnDFASENTSGER, ADCXnSDVCLMINTER, ADCXnSGDIAGPCCR0, ADCXnSGDIAGPCCR1, ADCXnSGDIAGVCR0,
**                        ADCXnSGDIAGVCR1, ADCXnSGDIAGVCR2, ADCXnSTPDCR0, ADCXnSTPDCR1, ADCXnSTPDCR2, ADCXnSGDIAGCR
**
** Reference ID         : ADC_DUD_ACT_085, ADC_DUD_ACT_085_REG001, ADC_DUD_ACT_085_REG002,
** Reference ID         : ADC_DUD_ACT_085_REG003, ADC_DUD_ACT_085_REG004, ADC_DUD_ACT_085_REG005,
** Reference ID         : ADC_DUD_ACT_085_REG006, ADC_DUD_ACT_085_REG007, ADC_DUD_ACT_085_REG008,
** Reference ID         : ADC_DUD_ACT_085_REG009, ADC_DUD_ACT_085_REG010, ADC_DUD_ACT_085_REG011
***********************************************************************************************************************/
#if (ADC_DEINIT_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_AdcDeInit(const uint8 LucHwUnitIndex)                                                  /* PRQA S 1532 # JV-01 */
{
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;

  /* Initialize the local variable for HW unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Read the user base configuration address of the HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */

  /* Initialize the device-specific ADC hardware registers to their default values */
  #if (ADC_IP_C_ADCK == STD_OFF)
  LpAdcRegisters->usADCXnDFASENTSGER = ADC_WORD_ZERO;                                                                   /* PRQA S 2814 # JV-01 */
  #else
  LpAdcRegisters->usADCXnGTMENTSGER = ADC_WORD_ZERO;                                                                    /* PRQA S 2814 # JV-01 */
  #endif /* (ADC_IP_C_ADCK == STD_OFF) */
  LpAdcRegisters->ucADCXnSDVCLMINTER = ADC_BYTE_ZERO;
  LpAdcRegisters->ulADCXnSGDIAGPCCR0 = ADC_DWORD_ZERO;
  LpAdcRegisters->ulADCXnSGDIAGPCCR1 = ADC_DWORD_ZERO;
  LpAdcRegisters->ucADCXnSGDIAGVCR0  = ADC_BYTE_ZERO;
  LpAdcRegisters->ucADCXnSGDIAGVCR1  = ADC_BYTE_ZERO;
  LpAdcRegisters->ucADCXnSGDIAGVCR2  = ADC_BYTE_ZERO;
  #if (ADC_IP_C_ADCK == STD_OFF)
  LpAdcRegisters->ucADCXnSTPDCR0     = ADC_BYTE_ZERO;
  LpAdcRegisters->ucADCXnSTPDCR1     = ADC_BYTE_ZERO;
  LpAdcRegisters->ucADCXnSTPDCR2     = ADC_BYTE_ZERO;
  #endif /* (ADC_IP_C_ADCK == STD_OFF) */
  LpAdcRegisters->ulADCXnSGDIAGCR    = ADC_DWORD_ZERO;

  #if (ADC_ENABLE_ADC_TSEL == STD_ON)
  /* Check if HW unit has ADC trigger selection register */
  if (NULL_PTR != LpHwUnitConfig->pSgTriggReg)
  {
    /* De-initialization of ADC trigger selection register */
    Adc_HwTriggerDeInit(LucHwUnitIndex);
  } /* else: No action required */
  #endif /* (ADC_ENABLE_ADC_TSEL == STD_ON) */

  #if (ADC_TRACK_AND_HOLD == STD_ON)
  /* Check if HW unit has Track and Hold groups */
  if ((uint8)0U != LpHwUnitConfig->ucTrackHoldEnable)
  {
    /* De-initialization of Track and Hold */
    Adc_TrackHoldDeInit(LucHwUnitIndex);
  } /* else: No action required */
  #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

  #if (ADC_ENABLE_PWM_DIAG == STD_ON)
  /* De-initialize PWM-Diag registers */
  Adc_PwmDiagDeInit(LucHwUnitIndex);
  #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */

  /* Check if HW unit has wait time configuration */
  if (ADC_WAITTIME_DISABLED != LpHwUnitConfig->ucWaitTimeIndex)
  {
    /* De-initialization of wait time configuration */
    Adc_DeInitWaitTime(LucHwUnitIndex);
  } /* else: No action required */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_DEINIT_API == STD_ON) */

#if (ADC_TRACK_AND_HOLD == STD_ON)
/***********************************************************************************************************************
** Function Name        : Adc_TrackHoldInit
**
** Service ID           : NA
**
** Description          : This internal function initialize the Track and Hold registers.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : LucHwUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : ADCXnTHACR, ADCXnTHBCR, ADCXnTHER, ADCXnTHCR, ADCXnTHGSR, ADCXnTHSTPCR, ADCXnTHCHz
**
** Reference ID         : ADC_DUD_ACT_086, ADC_DUD_ACT_086_REG001, ADC_DUD_ACT_086_REG002,
** Reference ID         : ADC_DUD_ACT_086_REG003, ADC_DUD_ACT_086_REG004, ADC_DUD_ACT_086_REG005
** Reference ID         : ADC_DUD_ACT_086_REG006
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_TrackHoldInit(const uint8 LucHwUnitIndex)
{
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  #if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
  P2VAR(volatile Adc_TrackHoldSelectType, AUTOMATIC, REGSPACE) LpTrackHoldIOSelectReg;
  uint32 LulLoopCount;
  #endif

  /* Initialize the local variable for HW unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Read the user base configuration address of the HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */
  /* Initialize T&H group A/B control registers to disable Hold control and trigger */
  LpAdcRegisters->aaTHxCR[0].ucADCXnTHxCR = ADC_BYTE_ZERO;                                                              /* PRQA S 2814 # JV-01 */
  LpAdcRegisters->aaTHxCR[1].ucADCXnTHxCR = ADC_BYTE_ZERO;
  /* Initialize T&H enable register to disable all T&H channels */
  LpAdcRegisters->ucADCXnTHER = ADC_BYTE_ZERO;
  /* Initialize T&H automatic sampling mask to enable automatic sampling */
  LpAdcRegisters->ucADCXnTHCR = ADC_BYTE_ZERO;
  /* Initialize T&H group select register to select T&H group by configuration */
  LpAdcRegisters->usADCXnTHGSR = LpHwUnitConfig->usTrackHoldGroupSelect;
  /* Stop all T&H sampling */
  LpAdcRegisters->ucADCXnTHSTPCR = ADC_ADCX_THSTPCR_THSTP;

  #if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
  /* Get the pointer to T&H Physical IO Selection Register */
  LpTrackHoldIOSelectReg = LpHwUnitConfig->pTnHChSelectReg;
  /* Check if this HW unit has T&H Physical IO Selection Register */
  if (NULL_PTR != LpTrackHoldIOSelectReg)
  {
    for (LulLoopCount = 0UL; LulLoopCount < (uint8)ADC_NUM_OF_TH_CHANNEL_SELECT; LulLoopCount++)
    {
      /* Initialize T&H Physical IO select register to default value */
      LpTrackHoldIOSelectReg->aaADCXnTHCHSz[LulLoopCount] = ADC_BYTE_ZERO;
    }
  } /* end of if (NULL_PTR != LpTrackHoldIOSelectReg) */
  /* else: No action required */
  #endif /* (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON) */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_TrackHoldDeInit
**
** Service ID           : NA
**
** Description          : This internal function de-initialize the Track and Hold registers.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : LucHwUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : All SGs must be stopped using ADCXnADHALTR before calling this function.
**
** Global Variables     : Adc_GpHwUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : ADCXnTHSTPCR, ADCXnTHACR, ADCXnTHBCR, ADCXnTHER, ADCXnTHCR, ADCXnTHGSR, ADCXnTHCHz
**
** Reference ID         : ADC_DUD_ACT_087, ADC_DUD_ACT_087_REG001, ADC_DUD_ACT_087_REG002,
** Reference ID         : ADC_DUD_ACT_087_REG003, ADC_DUD_ACT_087_REG004, ADC_DUD_ACT_087_REG005
** Reference ID         : ADC_DUD_ACT_087_REG006
***********************************************************************************************************************/
#if (ADC_DEINIT_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_TrackHoldDeInit(const uint8 LucHwUnitIndex)
{
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  #if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
  P2VAR(volatile Adc_TrackHoldSelectType, AUTOMATIC, REGSPACE) LpTrackHoldIOSelectReg;
  uint32 LulLoopCount;
  #endif

  /* Initialize the local variable for HW unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Read the user base configuration address of the HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */

  /* Stop all T&H sampling */
  LpAdcRegisters->ucADCXnTHSTPCR = ADC_ADCX_THSTPCR_THSTP;                                                              /* PRQA S 2814 # JV-01 */
  /* Initialize T&H group A/B control registers to default value */
  LpAdcRegisters->aaTHxCR[0].ucADCXnTHxCR = ADC_BYTE_ZERO;
  LpAdcRegisters->aaTHxCR[1].ucADCXnTHxCR = ADC_BYTE_ZERO;
  /* Initialize T&H enable register to default value */
  LpAdcRegisters->ucADCXnTHER = ADC_BYTE_ZERO;
  /* Initialize T&H automatic sampling mask to default value */
  LpAdcRegisters->ucADCXnTHCR = ADC_BYTE_ZERO;
  /* Initialize T&H group select register to default value */
  LpAdcRegisters->usADCXnTHGSR = ADC_WORD_ZERO;

  #if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
  /* Get the pointer to T&H Physical IO Selection Register */
  LpTrackHoldIOSelectReg = LpHwUnitConfig->pTnHChSelectReg;
  /* Check if this HW unit has T&H Physical IO Selection Register */
  if (NULL_PTR != LpTrackHoldIOSelectReg)
  {
    for (LulLoopCount = 0UL; LulLoopCount < (uint8)ADC_NUM_OF_TH_CHANNEL_SELECT; LulLoopCount++)
    {
      /* Initialize T&H Physical IO select register to default value */
      LpTrackHoldIOSelectReg->aaADCXnTHCHSz[LulLoopCount] = ADC_BYTE_ZERO;                                              /* PRQA S 2814 # JV-01 */
    }
  } /* end of if (NULL_PTR != LpTrackHoldIOSelectReg) */
  #endif /* (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON) */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_DEINIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_TrackHoldEnable
**
** Service ID           : NA
**
** Description          : This internal function configures SG as T&H for the requested group and starts T&H sampling
**                        if it has not already started.
**                        If the requested group is a SW triggered, it starts the T&H hold. When it starts T&H sampling,
**                        it waits at least 10us before the first T&H hold.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : The SG associated with the requested group must be stopped before calling this function.
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpHwUnitConfig, Adc_GpSgUnitConfig, Adc_GaaHwUnitData,
**                        Adc_GucMaxSwTriggGroups, Adc_GpTnHChannelSelectValue
**
** Functions invoked    : None
**
** Registers Used       : ADCXnTHACR, ADCXnTHBCR, ADCXnTHER, ADCXnTHSMPSTCR, ADCXnTHAHLDSTCR, ADCXnTHBHLDSTCR,
**                        ADCXnSGCRx, ADCXnSGSTR, ADCXnTHCHz
**
** Reference ID         : ADC_DUD_ACT_088, ADC_DUD_ACT_088_REG001, ADC_DUD_ACT_088_REG002,
** Reference ID         : ADC_DUD_ACT_088_REG003, ADC_DUD_ACT_088_REG004, ADC_DUD_ACT_088_REG005,
** Reference ID         : ADC_DUD_ACT_088_REG006,
** Reference ID         : ADC_DUD_ACT_088_GBL001, ADC_DUD_ACT_088_GBL002
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_TrackHoldEnable(const Adc_GroupType LddGroup)                                          /* PRQA S 1532, 3006 # JV-01, JV-01 */
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_HwUnitDataType, AUTOMATIC, ADC_VAR_NO_INIT) LpHwUnitData;
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  P2VAR(volatile Adc_SGRegType, AUTOMATIC, REGSPACE) LpSGRegisters;
  uint32 LulCount;

  #if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
  P2VAR(volatile Adc_TrackHoldSelectType, AUTOMATIC, REGSPACE) LpTrackHoldIOSelectReg;
  /* Pointer to the T&H Channel Select Register Value */
  P2CONST(Adc_TrackHoldChannelValueType, AUTOMATIC, ADC_CONFIG_DATA) LpTrackHoldIOSelectValue;
  #endif /* (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON) */

  uint8 LucHwUnitIndex;
  uint8 LucSgUnitId;
  uint8 LucTrackHoldGroup;

  /* Get the pointer to the requested group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */

  /* Get the index of the HW unit to which the requested group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  /* Get the pointer to the configuration of the HW unit to which the requested group belongs */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the pointer to the configuration of the SG unit to which the requested group belongs */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex];                                                         /* PRQA S 2824 # JV-01 */
  /* Get the pointer to the runtime data of the HW unit to which the requested group belongs */
  LpHwUnitData = &Adc_GaaHwUnitData[LucHwUnitIndex];                                                                    /* PRQA S 2934 # JV-01 */
  /* Get the SG unit ID to which the requested group is configured */
  LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                             /* PRQA S 2814 # JV-01 */

  /* Get the pointer to the ADC registers of the HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */
  /* Get the pointer to the SG registers of the SG unit */
  LpSGRegisters = &LpAdcRegisters->aaADCXnSG[LucSgUnitId];                                                              /* PRQA S 2814, 2934 # JV-01, JV-01 */

  /* Get the T&H group of the requested group */
  LucTrackHoldGroup = LpGroup->ucTrackAndHoldGroup;

  /* Check if T&H is not in progress */
  if ((uint8)0U == LpHwUnitData->ucTrackHoldStatus)                                                                     /* PRQA S 2844 # JV-01 */
  {
    /* Enable the channels configured for Track and Hold functionality */
    LpAdcRegisters->ucADCXnTHER = LpHwUnitConfig->ucTrackHoldEnable;
  
    #if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
    /* Check if the T&H Channel Select Register used */
    if (ADC_TRACKHOLD_CHANNEL_SELECT_OFF != LpGroup->ucTnHChannelIndex)                                                 /* PRQA S 2814 # JV-01 */
    {
      /* Get the pointer to provide T&H physical IO select function, Configuration Value */
      LpTrackHoldIOSelectValue = &Adc_GpTnHChannelSelectValue[LpGroup->ucTnHChannelIndex];                              /* PRQA S 2824 # JV-01 */
      /* Get the pointer to T&H Physical IO Selection Register */                         
      LpTrackHoldIOSelectReg = LpHwUnitConfig->pTnHChSelectReg;                                                         /* PRQA S 2814 # JV-01 */
      /* Check if this HW unit has T&H Physical IO Selection Register */                  
      if (NULL_PTR != LpTrackHoldIOSelectReg)                                             
      {                                                                                   
        for (LulCount = 0UL; LulCount < (uint8)ADC_NUM_OF_TH_CHANNEL_SELECT; LulCount++)  
        {                                                                                 
          /* Setting T&H Physical IO select register to default value */                  
          LpTrackHoldIOSelectReg->aaADCXnTHCHSz[LulCount] = LpTrackHoldIOSelectValue->aaTnHChannelSelectValue[LulCount];/* PRQA S 2814 # JV-01 */
        }
      } /* end of if (NULL_PTR != LpTrackHoldIOSelectReg) */
    }/* end of if (ADC_TRACKHOLD_CHANNEL_SELECT_OFF != LpGroup->ucTnHChannelIndex) */
    /* else: No action required */
    #endif /* (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON) */

    /* Set T&H Group x Control register */
    LpAdcRegisters->aaTHxCR[LucTrackHoldGroup].ucADCXnTHxCR = LpGroup->ucTrackHoldControl;                              /* PRQA S 2844 # JV-01 */
  
    /* Start sampling of all the Track and Hold channels */
    LpAdcRegisters->ucADCXnTHSMPSTCR = ADC_ADCX_THSMPSTCR_SMPST;

    /* Wait at least 10us for the first hold start after the start of T&H sampling */
    for (LulCount = (uint32)LpHwUnitConfig->ucTrackHoldWait; LulCount != 0UL; LulCount--)
    {
      /* Execute dummy read and SYNCP to stabilize the waiting time. */
      (void)LpAdcRegisters->usADCXnSGSTR;                                                                               /* PRQA S 2814 # JV-01 */
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */
    }

    /* If the requested group is SW triggered */
    if (LddGroup < Adc_GucMaxSwTriggGroups)
    {
      /* Start T&H Group x Hold */
      LpAdcRegisters->aaTHxHLDSTCR[LucTrackHoldGroup].ucADCXnTHxHLDSTCR = ADC_ADCX_THXHLDSTCR_HLDST;                    /* PRQA S 2814, 2844 # JV-01, JV-01 */
      /* Initiate conversion for SW triggered group */
      LpSGRegisters->ucADCXnSGCRx = ADC_ADCX_SGCR_ADIE;                                                                 /* PRQA S 2844, 2814 # JV-01, JV-01 */
      LpSGRegisters->ucADCXnSGSTCRx = ADC_ADCX_SGSTCR_SGST;
    }
    else
    {
      /* Enable the trigger mode and scan end interrupt */
      LpSGRegisters->ucADCXnSGCRx = (uint8)(ADC_ADCX_SGCR_ADIE | ADC_ADCX_SGCR_TRGMD_HW);
    }

    /* Update the Track and Hold status of this SG to active */
    LpHwUnitData->ucTrackHoldStatus |= (uint8)(1U << LucSgUnitId) | ADC_TH_SAMPLING;                                    /* PRQA S 2814, 2844 # JV-01, JV-01 */
  } /* end of if ((uint8)0U == LpHwUnitData->ucTrackHoldStatus) */
    /* else: No action required */

}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_TrackHoldDisable
**
** Service ID           : NA
**
** Description          : This internal function disables the T&H of SG associated with the requested group.
**                        If all SGs are inactive, it stops T&H sampling.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpHwUnitConfig, Adc_GaaHwUnitData
**
** Functions invoked    : None
**
** Registers Used       : ADCXnTHACR, ADCXnTHBCR, ADCXnSGCRx, ADCXnADHALTR, ADCXnTHSTPCR, ADCXnTHER, ADCXnTHCHz
**
** Reference ID         : ADC_DUD_ACT_089, ADC_DUD_ACT_089_REG001, ADC_DUD_ACT_089_REG002,
** Reference ID         : ADC_DUD_ACT_089_REG003, ADC_DUD_ACT_089_REG004, ADC_DUD_ACT_089_REG005,
** Reference ID         : ADC_DUD_ACT_089_REG006, ADC_DUD_ACT_089_REG007
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_TrackHoldDisable(const Adc_GroupType LddGroup)                                         /* PRQA S 1532 # JV-01 */
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_HwUnitDataType, AUTOMATIC, ADC_VAR_NO_INIT) LpHwUnitData;
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  P2VAR(volatile Adc_SGRegType, AUTOMATIC, REGSPACE) LpSGRegisters;
  #if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
  P2VAR(volatile Adc_TrackHoldSelectType, AUTOMATIC, REGSPACE) LpTrackHoldIOSelectReg;
  #endif /* (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON) */
  uint32 LulCount;
  uint8 LucHwUnitIndex;
  uint8 LucSgUnitId;
  uint8 LucTrackHoldGroup;

  /* Get the pointer to the requested group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the index of the HW unit to which the requested group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  /* Get the pointer to the configuration of the HW unit to which the requested group belongs */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the pointer to the configuration of the SG unit to which the requested group belongs */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex];                                                         /* PRQA S 2824 # JV-01 */
  /* Get the pointer to the runtime data of the HW unit to which the requested group belongs */
  LpHwUnitData = &Adc_GaaHwUnitData[LucHwUnitIndex];                                                                    /* PRQA S 2934 # JV-01 */
  /* Get the SG unit ID to which the requested group is configured */
  LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                             /* PRQA S 2814 # JV-01 */
  /* Get the pointer to the ADC registers of the HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */

  /* Get the T&H group of the requested group */
  LucTrackHoldGroup = LpGroup->ucTrackAndHoldGroup;

  /* Check whether the Track and Hold is disabled or enabled */
  if (ADC_TH_DISABLED != LucTrackHoldGroup)
  {
    /* Disable T&H hold trigger */
    LpAdcRegisters->aaTHxCR[LucTrackHoldGroup].ucADCXnTHxCR &= (uint8)~ADC_ADCX_THXCR_HLDTE;                            /* PRQA S 2814, 2844 # JV-01, JV-01 */
  } /* else: No action required */

  #if (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON)
  /* Get the pointer to T&H Physical IO Selection Register */
  LpTrackHoldIOSelectReg = LpHwUnitConfig->pTnHChSelectReg;
  /* Check if this HW unit has T&H Physical IO Selection Register */
  if (NULL_PTR != LpTrackHoldIOSelectReg)
  {
    for (LulCount = 0UL; LulCount < (uint8)ADC_NUM_OF_TH_CHANNEL_SELECT; LulCount++)
    {
      /* Disable T&H Channel Select Register */
      LpTrackHoldIOSelectReg->aaADCXnTHCHSz[LulCount] = (uint8)0U;
    }
  } /* end of if (NULL_PTR != LpTrackHoldIOSelectReg) */
  #endif /* (ADC_TRACK_AND_HOLD_CHANNEL_IO_SELECT == STD_ON) */

  /* Check if the requested group is not stopped */
  if ((uint8)0U != (uint8)(LpHwUnitData->ucSgUnitStatus & (uint8)(1U << LucSgUnitId)))                                  /* PRQA S 2844 # JV-01 */
  {
    /* Get the pointer to SG register */
    LpSGRegisters = &LpAdcRegisters->aaADCXnSG[LucSgUnitId];                                                            /* PRQA S 2934 # JV-01 */
    /* Disable trigger mode and conversion end interrupt */
    LpSGRegisters->ucADCXnSGCRx &= (uint8)~(ADC_ADCX_SGCR_TRGMD_HW | ADC_ADCX_SGCR_ADIE);                               /* PRQA S 2844 # JV-01 */
  } /* else: No action required */

  /* Check if all other SGs are inactive */
  if ((uint8)0U == (uint8)(LpHwUnitData->ucSgUnitStatus & (uint8)~(1U << LucSgUnitId)))
  {
    /* Use HALT to stop the SG */
    LpAdcRegisters->ucADCXnADHALTR = ADC_ADCX_ADHALTR_HALT;
    /* Stop all T&H sampling */
    LpAdcRegisters->ucADCXnTHSTPCR = ADC_ADCX_THSTPCR_THSTP;
    /* Disable all T&H channels to prevent resampling by the automatic sampling function */
    LpAdcRegisters->ucADCXnTHER = (uint8)0U;

    for (LulCount = 0UL; LulCount < ADC_NUM_OF_TH_GROUP; LulCount++)
    {
      /* Disable T&H hold control and trigger */
      LpAdcRegisters->aaTHxCR[LulCount].ucADCXnTHxCR = (uint8)0U;
    }

    /* Update the Track and Hold status to inactive */
    LpHwUnitData->ucTrackHoldStatus = (uint8)0U;
  } /* end of if ((uint8)0U == (uint8)(LpHwUnitData->ucSgUnitStatus & (uint8)~(1U << LucSgUnitId))) */
    /* else: No action required */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_SetWaitTime
**
** Service ID           : NA
**
** Description          : This internal function set Software wait time to registers.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LucHwUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig, Adc_GpWaitTimeConfig
**
** Functions invoked    : None
**
** Registers Used       : ADCXnWAITTRy
**
** Reference ID         : ADC_DUD_ACT_090, ADC_DUD_ACT_090_REG001
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_SetWaitTime(const uint8 LucHwUnitIndex)
{
  P2CONST(Adc_WaitTimeConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpWaitTimeConfig;
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  uint32 LulCnt;

  /* Initialize the local variable for HW unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Read the user base configuration address of the HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */
  /* Read the wait time registers of the hardware unit */
  LpWaitTimeConfig = &Adc_GpWaitTimeConfig[LpHwUnitConfig->ucWaitTimeIndex];                                            /* PRQA S 2824 # JV-01 */

  /* Set the wait time registers */
  for (LulCnt = 0UL; LulCnt < ADC_NUM_OF_WAITTIME; LulCnt++)
  {
    LpAdcRegisters->aaWAITTR[LulCnt].usADCXnWAITTRy = LpWaitTimeConfig->usWAITTRy[LulCnt];                              /* PRQA S 2814 # JV-01 */
  }
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_DeInitWaitTime
**
** Service ID           : NA
**
** Description          : This internal function set Software wait time to registers.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LucHwUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : ADCXnWAITTRy
**
** Reference ID         : ADC_DUD_ACT_091, ADC_DUD_ACT_091_REG001
***********************************************************************************************************************/
#if (ADC_DEINIT_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_DeInitWaitTime(const uint8 LucHwUnitIndex)
{
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  uint32 LulCnt;

  /* Initialize the local variable for HW unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Read the user base configuration address of the HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */

  /* INITIALIZATION OF WAIT TIME CONFIGURATION */
  for (LulCnt = 0UL; LulCnt < ADC_NUM_OF_WAITTIME; LulCnt++)
  {
    /* Set to wait time for A/D convert time */
    LpAdcRegisters->aaWAITTR[LulCnt].usADCXnWAITTRy = ADC_WORD_ZERO;                                                    /* PRQA S 2814 # JV-01 */
  }
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_DEINIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_EcmErrorInterrupt
**
** Service ID           : NA
**
** Description          : This internal function enables or disables the ECM parity error interrupt.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : LblEnableInterrupt
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : None
**
** Functions invoked    : None
**
** Registers Used       : ECMKCPROT, ECMISCFGj, ECMINCFGi_j, EIC
**
** Reference ID         : ADC_DUD_ACT_092, ADC_DUD_ACT_092_REG001, ADC_DUD_ACT_092_REG002,
** Reference ID         : ADC_DUD_ACT_092_REG003, ADC_DUD_ACT_092_REG004, ADC_DUD_ACT_092_REG005,
** Reference ID         : ADC_DUD_ACT_092_REG006
***********************************************************************************************************************/
#if (ADC_ENABLE_PARITY_ERR_INT == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_EcmErrorInterrupt(const boolean LblEnableInterrupt)                                    /* PRQA S 1532, 3006 # JV-01, JV-01 */
{
  uint32 LulEcmIntSelect;
  uint32 LulEcmIntNotify;

  if (ADC_FALSE == LblEnableInterrupt)
  {
    /* Set ADC parity error type selection to default in ECMISCFG3 register (ECM100) */
    LulEcmIntSelect = ADC_ECMISCFG_REG & ~ADC_ECM_CFG_ADC_PARITY_ERR;                                                   /* PRQA S 0303 # JV-01 */
    /* Set ADC parity error notification to disable in ECMINCFGi_3 register (ECM100) */
    LulEcmIntNotify = ADC_ECMINCFG_REG & ~ADC_ECM_CFG_ADC_PARITY_ERR;                                                   /* PRQA S 0303 # JV-01 */

    /* Disable ECM interrupt and perform synchronization for INTC1 */
    RH850_SV_SET_ICR_SYNCP(8, ADC_ECM_EIC8, ADC_EIC_EIMK);                                                              /* PRQA S 0303, 1006 # JV-01, JV-01 */
  }
  else
  {
    /* Set ADC parity error type selection to EI level in ECMISCFG3 register (ECM100) */
    LulEcmIntSelect = ADC_ECMISCFG_REG & ~ADC_ECM_CFG_ADC_PARITY_ERR;                                                   /* PRQA S 0303 # JV-01 */
    /* Set ADC parity error notification to enable in ECMINCFGi_3 register (ECM100) */
    LulEcmIntNotify = ADC_ECMINCFG_REG | ADC_ECM_CFG_ADC_PARITY_ERR;                                                    /* PRQA S 0303 # JV-01 */
  }

  /* Enable write access of ECMMICFG register */
  ADC_ECMKCPROT_REG = ADC_ECM_KEYCODE_ENABLE;                                                                           /* PRQA S 0303 # JV-01 */

  /* Set ECM configuration register */
  ADC_ECMISCFG_REG = LulEcmIntSelect;                                                                                   /* PRQA S 0303 # JV-01 */
  ADC_ECMINCFG_REG = LulEcmIntNotify;                                                                                   /* PRQA S 0303 # JV-01 */

  /* Perform synchronization for ECM */
  (void)ADC_ECMINCFG_REG;                                                                                               /* PRQA S 0303 # JV-01 */
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */

  /* Disable write access of ECMMICFG register */
  ADC_ECMKCPROT_REG = ADC_ECM_KEYCODE_DISABLE;                                                                          /* PRQA S 0303 # JV-01 */

  if (ADC_TRUE == LblEnableInterrupt)
  {
    /* Enable ECM interrupt and perform synchronization for INTC1 */
    RH850_SV_CLEAR_ICR_SYNCP(8, ADC_ECM_EIC8, (uint8)~ADC_EIC_EIMK);                                                    /* PRQA S 0303, 1006 # JV-01, JV-01 */
  } /* else: No action required */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_PARITY_ERR_INT == STD_ON) */

#if (ADC_ENABLE_ADC_TSEL == STD_ON)
/***********************************************************************************************************************
** Function Name        : Adc_HwTriggerInit
**
** Service ID           : NA
**
** Description          : This internal function performs the initialization of the ADC trigger selection registers.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LucHwUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig, Adc_GpSgUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : ADCXnSGTSELx
**
** Reference ID         : ADC_DUD_ACT_093, ADC_DUD_ACT_093_REG001
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_HwTriggerInit(const uint8 LucHwUnitIndex)
{
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_SgTriggRegType, AUTOMATIC, REGSPACE) LpSgTriggReg;
  uint8 LucSgUnitIndex;
  uint32 LulLoopCount;

  /* Initialize the local variable for HW unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */

  /* Get the pointer to SG Start Trigger Selection Register */
  LpSgTriggReg = LpHwUnitConfig->pSgTriggReg;                                                                           /* PRQA S 2814 # JV-01 */

  /* Check if this HW unit has SG Start Trigger Selection Register */
  if (NULL_PTR != LpSgTriggReg)
  {
    /* Get the first index of SG unit in HW unit */
    LucSgUnitIndex = LpHwUnitConfig->ucSgUnitOffset;

    /* Scan all SG units configured in this HW unit */
    for (LulLoopCount = (uint32)LpHwUnitConfig->ucSgUnitCount; LulLoopCount > 0UL; LulLoopCount--)
    {
      /* Get the SG unit configuration */
      LpSgUnitConfig = &Adc_GpSgUnitConfig[LucSgUnitIndex];                                                             /* PRQA S 2824 # JV-01 */
      /* Configure for HW trigger value */
      LpSgTriggReg->aaADCXnSGTSELx[LpSgUnitConfig->ucSgUnitId] = LpSgUnitConfig->ulSgTriggValue;                        /* PRQA S 2814, 2844 # JV-01, JV-01 */

      LucSgUnitIndex++;                                                                                                 /* PRQA S 3383 # JV-01 */
    }
  } /* end of if (NULL_PTR != LpSgTriggReg) */
    /* else: No action required */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_HwTriggerDeInit
**
** Service ID           : NA
**
** Description          : This internal function performs the de-initialization of the ADC trigger selection registers.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LucHwUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpSgUnitConfig, Adc_GpHwUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : ADCXnSGTSELx
**
** Reference ID         : ADC_DUD_ACT_094, ADC_DUD_ACT_094_REG001
***********************************************************************************************************************/
#if (ADC_DEINIT_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_HwTriggerDeInit(const uint8 LucHwUnitIndex)
{
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_SgTriggRegType, AUTOMATIC, REGSPACE) LpSgTriggReg;
  uint8 LucSgUnitIndex;
  uint32 LulLoopCount;

  /* Initialize the local variable for HW unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */

  /* Get the pointer to SG Start Trigger Selection Register */
  LpSgTriggReg = LpHwUnitConfig->pSgTriggReg;                                                                           /* PRQA S 2814 # JV-01 */

  /* Check if this HW unit has SG Start Trigger Selection Register */
  if (NULL_PTR != LpSgTriggReg)
  {
    /* Get the first index of SG unit in HW unit */
    LucSgUnitIndex = LpHwUnitConfig->ucSgUnitOffset;

    /* Scan all SG units configured in this HW unit */
    for (LulLoopCount = (uint32)LpHwUnitConfig->ucSgUnitCount; LulLoopCount > 0UL; LulLoopCount--)
    {
      /* Get the SG unit configuration */
      LpSgUnitConfig = &Adc_GpSgUnitConfig[LucSgUnitIndex];                                                             /* PRQA S 2824 # JV-01 */
      /* Configure for HW trigger value */
      LpSgTriggReg->aaADCXnSGTSELx[LpSgUnitConfig->ucSgUnitId] = ADC_REG_DWORD_INIT;                                    /* PRQA S 2814, 2844 # JV-01, JV-01 */

      LucSgUnitIndex++;                                                                                                 /* PRQA S 3383 # JV-01 */
    }
  } /* end of if (NULL_PTR != LpSgTriggReg) */
    /* else: No action required */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_DEINIT_API == STD_ON) */
#endif /* (ADC_ENABLE_ADC_TSEL == STD_ON) */

#if (ADC_ENABLE_PWM_DIAG == STD_ON)
/***********************************************************************************************************************
** Function Name        : Adc_PwmDiagInit
**
** Service ID           : NA
**
** Description          : This function initializes the PWM-Diag register of the ADC hardware unit.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LucHwUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : ADCXnPWVCLMINTER, ADCXnPWDCR
**
** Reference ID         : ADC_DUD_ACT_110, ADC_DUD_ACT_110_REG001, ADC_DUD_ACT_110_REG002
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_PwmDiagInit(const uint8 LucHwUnitIndex)
{
  /* Pointer to ADC HW unit configuration */
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  /* Pointer to the base address of the ADC registers */
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;

  /* Get the pointer to the configuration of the specified ADC HW unit */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the register base address of the specified ADC HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */

  /* Disable Limit Check Interrupt of PWM-Diag */
  LpAdcRegisters->ucADCXnPWVCLMINTER = ADC_ADCX_PWVCLMINTER_DISABLE;                                                    /* PRQA S 2814 # JV-01 */
  /* Disable PWM-Diag of scan group */
  LpAdcRegisters->ucADCXnPWDCR = ADC_ADCX_PWDCR_DISABLE;
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_PwmDiagDeInit
**
** Service ID           : NA
**
** Description          : This function de-initializes the PWM-Diag register of the ADC hardware unit.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LucHwUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : ADCXnPWDCR, ADCXnPWVCLMINTER
**
** Reference ID         : ADC_DUD_ACT_111, ADC_DUD_ACT_111_REG001, ADC_DUD_ACT_111_REG002
***********************************************************************************************************************/
#if (ADC_DEINIT_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_PwmDiagDeInit(const uint8 LucHwUnitIndex)
{
  /* Pointer to ADC HW unit configuration */
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  /* Pointer to the base address of the ADC registers */
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;

  /* Get the pointer to the configuration of the specified ADC HW unit */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the register base address of the specified ADC HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */

  /* Disable PWM-Diag of scan group */
  LpAdcRegisters->ucADCXnPWDCR = ADC_ADCX_PWDCR_DISABLE;                                                                /* PRQA S 2814 # JV-01 */
  /* Disable Limit Check Interrupt of PWM-Diag */
  LpAdcRegisters->ucADCXnPWVCLMINTER = ADC_ADCX_PWVCLMINTER_DISABLE;
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_DEINIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_PwmDiagEnable
**
** Service ID           : NA
**
** Description          : This function enables the trigger from the PWM-Diag module.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpHwUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : ADCXnPWDCR, ADCXnPWDSGCR
**
** Reference ID         : ADC_DUD_ACT_112, ADC_DUD_ACT_112_REG001, ADC_DUD_ACT_112_REG002
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_PwmDiagEnable(const Adc_GroupType LddGroup)                                            /* PRQA S 1532 # JV-01 */
{
  /* Pointer to ADC group configuration */
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  /* Pointer to ADC HW unit configuration */
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  /* Pointer to the base address of the ADC registers */
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  /* Index of the ADC HW unit */
  uint8 LucHwUnitIndex;

  /* Get the pointer to the configuration of the specified ADC group */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the index of ADC HW unit to which the group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  /* Get the pointer to the configuration of the specified ADC HW unit */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the register base address of the specified ADC HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */

  /* Enable PWM-Diag on scan group */
  LpAdcRegisters->ucADCXnPWDCR = ADC_ADCX_PWDCR_PWE;                                                                    /* PRQA S 2814 # JV-01 */
  /* Enable the trigger from PWM-Diag module */
  LpAdcRegisters->ucADCXnPWDSGCR = ADC_ADCX_PWDSGCR_TRGMD;
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_PwmDiagDisable
**
** Service ID           : NA
**
** Description          : This function disables the trigger from the PWM-Diag module.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : boolean
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpHwUnitConfig, Adc_GpSgUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : ADCXnPWDSGCR, ADCXnSGSRx, ADCXnPWDCR
**
** Reference ID         : ADC_DUD_ACT_113, ADC_DUD_ACT_113_REG001, ADC_DUD_ACT_113_REG002
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(boolean, ADC_PRIVATE_CODE) Adc_PwmDiagDisable(const Adc_GroupType LddGroup)                                        /* PRQA S 1532 # JV-01 */
{
  /* Pointer to ADC group configuration */
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  /* Pointer to ADC HW unit configuration */
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  /* Pointer to ADC scan group unit configuration */
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  /* Pointer to the base address of the ADC registers */
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  /* Pointer to the base address of the ADC scan group registers */
  volatile P2CONST(Adc_SGRegType, AUTOMATIC, REGSPACE) LpSGRegisters;
  /* Index of the ADC HW unit */
  uint8 LucHwUnitIndex;
  /* Index of the ADC scan group unit */
  uint8 LucSgUnitIndex;
  /* ID of the ADC scan group unit */
  uint8 LucSgUnitId;
  /* Variable for counting the maximum wait processing time */
  uint32 LulWaitCount;
  /* Flag to store if a timeout occurred while stopping scan group */
  boolean LblHwTimedOut;

  /* Get the pointer to the configuration of the specified ADC group */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the index of ADC HW unit to which the group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  /* Get the pointer to the configuration of the specified ADC HW unit */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the index of ADC scan group unit to which the group belongs */
  LucSgUnitIndex = LpGroup->ucSgUnitIndex;
  /* Get the pointer to the configuration of the specified ADC scan group unit */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LucSgUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the ID of ADC scan group unit to which the group belongs */
  LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                             /* PRQA S 2814 # JV-01 */
  /* Get the register base address of the specified ADC HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */
  /* Get the register base address of the specified ADC scan group unit */
  LpSGRegisters = &LpAdcRegisters->aaADCXnSG[LucSgUnitId];                                                              /* PRQA S 2814, 2934 # JV-01, JV-01 */

  /* Initialize scan group stop timeout flag to ADC_FALSE */
  LblHwTimedOut = ADC_FALSE;
  /* Disable the trigger from PWM-Diag module */
  LpAdcRegisters->ucADCXnPWDSGCR = ADC_ADCX_PWDSGCR_DISABLE;

  /* Get the wait count for the scan group */
  LulWaitCount = LpSgUnitConfig->ulVcrProcessWait;
  /* Wait for the termination of the Scan Group x */
  while ((ADC_BYTE_ZERO != (uint8)(LpSGRegisters->ucADCXnSGSRx & ADC_SGACT_STATUS)) && (LulWaitCount != 0UL))           /* PRQA S 2844 # JV-01 */
  {
    LulWaitCount--;
  }
  /* Check if it has timed out */
  if (LulWaitCount != 0UL)
  {
    /* Disable PWM-Diag on scan group */
    LpAdcRegisters->ucADCXnPWDCR = ADC_ADCX_PWDCR_DISABLE;
  }
  else
  {
    /* Timeout, Can not stop scan group */
    LblHwTimedOut = ADC_TRUE;
  }

  return LblHwTimedOut;
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_PwmDiagReadData
**
** Service ID           : NA
**
** Description          : This function reads the value of PWM-Diag Data Supplementary Information Register.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : uint32
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpHwUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : ADCXnPWDDIR
**
** Reference ID         : ADC_DUD_ACT_114
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(uint32, ADC_PRIVATE_CODE) Adc_PwmDiagReadData(const Adc_GroupType LddGroup)                                        /* PRQA S 1532 # JV-01 */
{
  /* Pointer to ADC group configuration */
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  /* Pointer to ADC HW unit configuration */
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  /* Pointer to the base address of the ADC registers */
  volatile P2CONST(Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  /* Index of the ADC HW unit */
  uint8 LucHwUnitIndex;
  /* Variable to store the value of PWM-Diag Data Supplementary Information Register */
  uint32 LulDirValue;

  /* Get the pointer to the configuration of the specified ADC group */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the index of ADC HW unit to which the group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  /* Get the pointer to the configuration of the specified ADC HW unit */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the register base address of the specified ADC HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */

  /* Read the value of PWM-Diag Data Supplementary Information Register */
  LulDirValue = LpAdcRegisters->ulADCXnPWDDIR;                                                                          /* PRQA S 2814 # JV-01 */

  return LulDirValue;
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
