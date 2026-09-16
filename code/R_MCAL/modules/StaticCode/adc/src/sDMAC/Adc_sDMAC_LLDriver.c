/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_sDMAC_LLDriver.c                                                                                */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 * 2.5.0: 30/06/2025 : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.4.0: 31/05/2025 : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.1: 28/02/2025 : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : As part of ARDAACJ-591 support, following changes are made:
 *                     1.Disable DMA Interrupt When configure Adc result data type selection is 4-byte
 *                       and DMA Polling Mode at function Adc_DmaEnable()
 *                     2.Check data of the last element of Adc data buffer instead of DMAjCHSTAn register
 *                       When configure Adc result data type selection is 4-byte at function Adc_DmaGetTransferStatus()
 *                     3.Added QAC Message PRQA (2:3678), (2:2844)
 *                     As part of ARDAACJ-572 support, following changes are made:
 *                     1.Add preprocessor directive ADC_RESULT_DATA_TYPE to support DMA transfer 4-byte data
 *                     2.Remove specified code of ADCJ in function Adc_DmaEnable()
 * 2.1.3: 31/10/2024 : As part of QAC 9.5.0 support, following changes are made:
 *                     1.Added QAC Message (2:0303)
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 * 2.0.1: 18/10/2023 : Support QAC Amendment 2, add message 3006
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define. Change Adc_Mapping.h to Adc_Memmap.h
 *        03/08/2023 : Add new QAC message PRQA (2:1006),(7:2755).
 * 1.4.5: 16/09/2022 : Updated QAC messages according to QAC analysis results.
 *                     Updated Reference IDs.
 *                     Treated new exceeded value in function metrics to be below target values.
 *        12/09/2022 : Removed Adc_DmaEnableForStreaming as its implementation was merged into Adc_DmaEnable.
 *                     Changed Adc_DmaEnable to always use descriptors for DMA transfers for implementation uniformity.
 *                     Changed the DMA transfer source to use ADCXnDIR except for U2Ax
 *                     in order to reduce the rounding up of the number of channels to an even number.
 *                     Changed Adc_DmaDeInit to also clear the DMA error flag.
 *                     Updated Adc_DmaDeInit and Adc_DmaDisable to clear all but the CAEE bit in the DMAjCHCR register.
 *                     Replaced the empty else blocks, not from else if, with comments.
 *                     Fixed comments about 'No action required' and 'end of'.
 *                     Unified the flag to be cleared in Adc_DmaClearInterruptFlag to the descriptor step end flag
 *                     as DMA transfers always use descriptors.
 *                     Removed unnecessary use of register read macro in Adc_DmaClearInterruptFlag.
 *                     Separated each bit of ucGroupSettings into independent variables.
 * 1.4.4: 24/08/2022 : Updated information in function header comments.
 *        21/07/2022 : Updated Re-entrancy, Global Variables, Functions invoked, and Registers Used in function header
 *                     comments.
 * 1.4.3: 25/05/2022 : Removed unnecessary coding rule messages in header comment.
 *                     Fixed the typos in comments.
 * 1.4.1: 24/11/2021 : Removed the inclusion of unnecessary header.
 *                     Added the initialization of DMATRGSEL for ADCK.
 * 1.4.0: 13/10/2021 : Changed the transfer limit setting from DTS to TSR for single and STS for streaming.
 *                     Changed to round up the number of channels transferred to an even number for streaming due to
 *                     DMA restrictions.
 * 1.3.2: 16/09/2021 : Changed the source transaction size for DMA transfers to 4 bytes.
 *        09/09/2021 : Added synchronization after handling each bus group.
 *                     Changed the DMA descriptor setting to use a structure.
 *        06/09/2021 : Changed to Adc_Mapping.h from Adc_MemMap.h
 * 1.3.1: 17/07/2021 : Added the CONST qualifier to pointers that have not changed their reference.
 *        08/07/2021 : Removed unnecessary header include.
 *                     Removed unnecessary typecasts.
 *        07/07/2021 : Added QAC message 9.5.0
 *                     Changed comment format to 120 columns
 *                     Changed violation tag from START/END
 *        16/06/2021 : Add casts to calculation processing.
 *                     Removed redundant initialization.
 *                     Optimization of calculation process for make a point-up.
 *        01/06/2021 : Changed to the appropriate memory classes and pointer classes.
 *        24/05/2021 : Removed unnecessary include headers.
 *                     Moved "Adc_DmaIsr()" from "Adc_sDMAC_LLDriver.c" to Adc_LLDriver.c
 *                     Moved the function declaration of the internal function from the header to the source code.
 *                     Changed function name to "Adc_DmaEnableForStreaming" from "Adc_ConfigureDMAForStreaming".
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.3.0: 05/12/2020 : Report DEM error ADC_E_TIMEOUT in Adc_DmaIsr in case
 *                     cannot stop DMA channel
 * 1.2.0: 14/07/2020 : Release
 *        27/07/2020 : Add QAC 9.3.1 comment.
 * 1.1.1: 02/07/2020 : - Update the value write to register DPPTR in Adc_DmaEnable
 *                     and Adc_ConfigureDMAForStreaming
 *                     - Remove parameter LucHwUnitIndex in function
 *                     Adc_PopFromQueue
 * 1.1.0: 19/06/2020 : Release
 * 1.0.3: 18/06/2020 : - Avoid access to bit CAIE and CAEE, CAEC when accessing
 *                     to register DMAjCHCR_n, DMAjCHFCR_n
 *                     - Check if first half samples equal
 *                     LpGroupData->ucSamplesCompleted, descriptor 0 is not
 *                     configured in Adc_ConfigureDMAForStreaming
 * 1.0.2: 24/04/2020 : Remove critical section protection in Adc_DmaIsr
 * 1.0.1: 09/04/2020 : Add const qualifier for arguments of internal functions
 *                     that are never changed
 * 1.0.0: 09/01/2020 : Initial Version
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
#include "Adc_sDMAC_LLDriver.h"

/* Included for the macro declaration of supervisor mode(SV) write enabled Registers IMR & ICxxx */
#include "rh850_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define ADC_SDMAC_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION_VALUE
#define ADC_SDMAC_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION_VALUE
#define ADC_SDMAC_LLDRIVER_C_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ADC_SDMAC_LLDRIVER_C_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION_VALUE
#define ADC_SDMAC_LLDRIVER_C_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ADC_SDMAC_LLDRIVER_AR_RELEASE_MAJOR_VERSION != ADC_SDMAC_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Adc_sDMAC_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (ADC_SDMAC_LLDRIVER_AR_RELEASE_MINOR_VERSION != ADC_SDMAC_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Adc_sDMAC_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (ADC_SDMAC_LLDRIVER_AR_RELEASE_REVISION_VERSION != ADC_SDMAC_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Adc_sDMAC_LLDriver.c : Mismatch in Release Patch Version"
#endif

#if (ADC_SDMAC_LLDRIVER_SW_MAJOR_VERSION != ADC_SDMAC_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Adc_sDMAC_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (ADC_SDMAC_LLDRIVER_SW_MINOR_VERSION != ADC_SDMAC_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Adc_sDMAC_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : MISRA C:2012 Rule-11.4, CERTCCM INT36, CWE Rule CWE-398, CWE-569, CWE-738                    */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP39, EXP11, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
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
/* Message (7:2755)    : Analysis time of function '%1s' has exceeded the configured maximum: '%2sms'. Dataflow       */
/*                       analysis continues with the next function.                                                   */
/* Rule                : MISRA C:2012 CMN-0.4, CERTCCM CMN-0.4, CWE Rule CMN-0.4                                      */
/* JV-01 Justification : This is depends on Hardware Specification for each module                                    */
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
/* Message (4:2986)    : This operation is redundant. The value of the result is always that of the right-hand        */
/*                       operand.                                                                                     */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-398, CWE-561, CWE-569, CWE-633     */
/* JV-01 Justification : The operation is correct                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
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
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : MISRA C:2012 Rule-11.4, CERTCCM INT36, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2844)    : Possible: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127,       */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : It is specific for device register accessing and confirmed has no issue in software behavior.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : This is accepted. It is just advice for improve safety by reducing the possibility that the  */
/*                       referenced data is unintentionally modified through an unexpected alias and improves         */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

#if (ADC_ENABLE_DMA_MODE == STD_ON)

/***********************************************************************************************************************
** Function Name        : Adc_DmaInit
**
** Service ID           : NA
**
** Description          : This internal function initializes all configured DMA units.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpDmaUnitConfig, Adc_GucMaxDmaChannels, Adc_GpHwUnitConfig, Adc_GpSgUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : DMACSELj_m, EIC
**
** Reference ID         : ADC_DUD_ACT_059, ADC_DUD_ACT_059_REG001, ADC_DUD_ACT_059_REG002, ADC_DUD_ACT_059_REG003
***********************************************************************************************************************/

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"
FUNC(void, ADC_PRIVATE_CODE) Adc_DmaInit(void)                                                                          /* PRQA S 1532, 2755, 3006 # JV-01, JV-01, JV-01 */
{
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
  P2CONST(Adc_DmaConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpSGmDmaConfig;
  uint8 LucLoopCount;
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  uint8 LucSgUnitCount;
  uint8 LucSgLoopCount;
  uint8 LucInitialPosition;
  #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */
  #if (ADC_IP_ADCK == STD_ON)
  uint32 LulLoopCount;
  uint32 LulShift;
  uint32 LulGroupSelect;
  #endif /* (ADC_IP_ADCK == STD_ON) */

  #if ((ADC_IP_ADCH == STD_ON) || (ADC_IP_ADCJ == STD_ON))
  /* Set DMA Transfer Request Group Selection */
  ADC_DMACSEL0_0 &= ~ADC_REQUESTGROUP00_MASK;                                                                           /* PRQA S 0303 # JV-01 */
  ADC_DMACSEL0_1 &= ~ADC_REQUESTGROUP01_MASK;                                                                           /* PRQA S 0303 # JV-01 */
  ADC_DMACSEL1_0 &= ~ADC_REQUESTGROUP10_MASK;                                                                           /* PRQA S 0303 # JV-01 */
  ADC_DMACSEL1_1 &= ~ADC_REQUESTGROUP11_MASK;                                                                           /* PRQA S 0303 # JV-01 */

  /* Perform synchronization for DMATRGSEL */
  (void)ADC_DMACSEL1_1;                                                                                                 /* PRQA S 0303 # JV-01 */
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  #endif /* ((ADC_IP_ADCH == STD_ON) || (ADC_IP_ADCJ == STD_ON)) */

  #if (ADC_IP_ADCK == STD_ON)
  for (LulLoopCount = 0UL; LulLoopCount < (uint32)Adc_GucMaxDmaChannels; LulLoopCount++)
  {
    /* Get the pointer to DMA configuration */
    LpSGmDmaConfig = &Adc_GpDmaUnitConfig[LulLoopCount];                                                                /* PRQA S 2824 # JV-01 */

    /* Configure the DMA Transfer Request Group Selection Register */
    LulShift = (LpSGmDmaConfig->ulDmaResourceValue & ADC_DMA_CSEL_SHIFT_MASK) << 1U;                                    /* PRQA S 2814 # JV-01 */
    LulGroupSelect = *LpSGmDmaConfig->pDMACSEL;                                                                         /* PRQA S 2814 # JV-01 */
    LulGroupSelect &= ~(ADC_DMA_CSEL_MASK << LulShift);
    LulGroupSelect |= (uint32)LpSGmDmaConfig->ucDmaRequestGroup << LulShift;
    *LpSGmDmaConfig->pDMACSEL = LulGroupSelect;
  } /* end of for (LulLoopCount = 0UL; LulLoopCount < (uint32)Adc_GucMaxDmaChannels; LulLoopCount++) */

  /* Perform dummy read and synchronization for DMATRGSEL */
  (void)*Adc_GpDmaUnitConfig[0].pDMACSEL;                                                                               /* PRQA S 2814 # JV-01 */
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  #endif /* (ADC_IP_ADCK == STD_ON) */

  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
  LucInitialPosition = ADC_VAL_BYTE_INIT;
  for (LucLoopCount = ADC_COUNT_BYTE_INIT; LucLoopCount < (uint8)ADC_MAX_HW_UNITS; LucLoopCount++)
  {
    /* Initialize the local variable for HW unit configuration */
    LpHwUnitConfig = &Adc_GpHwUnitConfig[LucLoopCount];                                                                 /* PRQA S 2824 # JV-01 */
    /* Get the SG unit count */
    LucSgUnitCount = LpHwUnitConfig->ucSgUnitCount;                                                                     /* PRQA S 2814 # JV-01 */
    for (LucSgLoopCount = ADC_COUNT_BYTE_INIT; LucSgLoopCount < LucSgUnitCount; LucSgLoopCount++)
    {
      LpSgUnitConfig = &Adc_GpSgUnitConfig[LucInitialPosition];                                                         /* PRQA S 2824 # JV-01 */
      /* Check SG use DMA and interrupt mode or not */
      if ((ADC_INTERRUPT_MODE == LpSgUnitConfig->enFunctionalityModeType) &&                                            /* PRQA S 2814 # JV-01 */
          (ADC_DMA_CHANNEL_OFF != LpSgUnitConfig->ucDmaChannelIndex))
      {
        /* Get the pointer to DMA configuration */
        LpSGmDmaConfig = &Adc_GpDmaUnitConfig[LpSgUnitConfig->ucDmaChannelIndex];                                       /* PRQA S 2824 # JV-01 */
        /* Enable DMA channel interrupt and perform synchronization for INTC2 */
        RH850_SV_CLEAR_ICR_SYNCP(8, LpSGmDmaConfig->pDmaEicRegaddress, (uint8)~ADC_EIC_EIMK);                           /* PRQA S 0751, 1006, 2814 # JV-01, JV-01, JV-01 */
      } /* else: No action required */
      /* InitPosition is incrementation */
      LucInitialPosition++;                                                                                             /* PRQA S 3383 # JV-01 */
    } /* end of for (LucSgLoopCount = ADC_COUNT_BYTE_INIT; LucSgLoopCount < LucSgUnitCount; LucSgLoopCount++) */
  } /* end of for (LucLoopCount = ADC_COUNT_BYTE_INIT; LucLoopCount < (uint8)ADC_MAX_HW_UNITS; LucLoopCount++) */
  #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_DmaDeInit
**
** Service ID           : NA
**
** Description          : This internal function de-initializes all configured DMA units.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpDmaUnitConfig, Adc_GucMaxDmaChannels, Adc_GpHwUnitConfig, Adc_GpSgUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : DMAjCHFCR_n, DMAjCHCR_n, DMAjSAR_n, DMAjDAR_n, DMAjTSR_n, DMAjTMR_n, DMAjGIAI_n, DMAjGOAI_n,
**                        DMAjSIAI_n, DMAjSOAI_n, DMAjSGCR_n, DMAjRS_n, DMAjDPPTR_n, DMAjDPCR_n, DMACSELj_m, EIC
**
** Reference ID         : ADC_DUD_ACT_060, ADC_DUD_ACT_060_REG001, ADC_DUD_ACT_060_REG002,
** Reference ID         : ADC_DUD_ACT_060_REG003, ADC_DUD_ACT_060_REG004, ADC_DUD_ACT_060_REG005,
** Reference ID         : ADC_DUD_ACT_060_REG006, ADC_DUD_ACT_060_REG007, ADC_DUD_ACT_060_REG008,
** Reference ID         : ADC_DUD_ACT_060_REG009, ADC_DUD_ACT_060_REG010, ADC_DUD_ACT_060_REG011,
** Reference ID         : ADC_DUD_ACT_060_REG012, ADC_DUD_ACT_060_REG013, ADC_DUD_ACT_060_REG014,
** Reference ID         : ADC_DUD_ACT_060_REG015, ADC_DUD_ACT_060_REG016, ADC_DUD_ACT_060_REG017
***********************************************************************************************************************/
#if (ADC_DEINIT_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_DmaDeInit(void)                                                                        /* PRQA S 1532, 2755, 3006 # JV-01, JV-01, JV-01 */
{
  P2CONST(Adc_DmaConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpSGmDmaConfig;
  P2VAR(volatile Adc_DmaRegisters, AUTOMATIC, REGSPACE) LpDmaRegisters;
  uint8 LucLoopCount;
  #if (ADC_IP_ADCK == STD_ON)
  uint32 LulLoopCount;
  uint32 LulShift;
  uint32 LulGroupSelect;
  #endif /* (ADC_IP_ADCK == STD_ON) */
  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  uint8 LucSgLoopCount;
  uint8 LucSgUnitCount;
  uint8 LucDeInitPosition;

  LucDeInitPosition = ADC_VAL_BYTE_INIT;
  #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

  for (LucLoopCount = ADC_COUNT_BYTE_INIT; LucLoopCount < Adc_GucMaxDmaChannels; LucLoopCount++)
  {
    /* Get the pointer to DMA configuration */
    LpSGmDmaConfig = &Adc_GpDmaUnitConfig[LucLoopCount];                                                                /* PRQA S 2824 # JV-01 */
    LpDmaRegisters = LpSGmDmaConfig->pDmaRegBaseaddress;                                                                /* PRQA S 2814 # JV-01 */

    /* De-initialize DMA registers */
    LpDmaRegisters->ulDMAjCHFCRn =                                                                                      /* PRQA S 2814 # JV-01 */
      ADC_DMA_CHFCR_TEC | ADC_DMA_CHFCR_DSEC | ADC_DMA_CHFCR_CAEC | ADC_DMA_CHFCR_DRQC | ADC_DMA_CHFCR_OVFC;
    LpDmaRegisters->usDMAjCHCRn &= ADC_DMA_CHCR_CAEE;
    LpDmaRegisters->ulDMAjSARn   = ADC_DMA_SAR_INIT;
    LpDmaRegisters->ulDMAjDARn   = ADC_DMA_DAR_INIT;
    LpDmaRegisters->ulDMAjTSRn   = ADC_DMA_TSR_INIT;
    LpDmaRegisters->ulDMAjTMRn  &= ADC_DMA_TMR_PRI_MASK;
    LpDmaRegisters->ulDMAjGIAIn  = ADC_DMA_GIAI_INIT;
    LpDmaRegisters->ulDMAjGOAIn  = ADC_DMA_GOAI_INIT;
    LpDmaRegisters->ulDMAjSIAIn  = ADC_DMA_SIAI_INIT;
    LpDmaRegisters->ulDMAjSOAIn  = ADC_DMA_SOAI_INIT;
    LpDmaRegisters->ulDMAjSGCRn  = ADC_DMA_SGCR_INIT;
    LpDmaRegisters->ulDMAjRSn    = ADC_DMA_RS_INIT;
    LpDmaRegisters->ulDMAjDPPTRn = ADC_DMA_DPPTR_INIT;
    LpDmaRegisters->ulDMAjDPCRn  = ADC_DMA_DPCR_INIT;

    /* Perform synchronization for SDMAC */
    (void)LpDmaRegisters->ulDMAjDPCRn;
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  } /* end of for (LucLoopCount = ADC_COUNT_BYTE_INIT; LucLoopCount < Adc_GucMaxDmaChannels; LucLoopCount++) */

  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
  for (LucLoopCount = ADC_COUNT_BYTE_INIT; LucLoopCount < (uint8)ADC_MAX_HW_UNITS; LucLoopCount++)
  {
    /* Initialize the local variable for HW unit configuration */
    LpHwUnitConfig = &Adc_GpHwUnitConfig[LucLoopCount];                                                                 /* PRQA S 2824 # JV-01 */
    /* Get the SG unit count */
    LucSgUnitCount = LpHwUnitConfig->ucSgUnitCount;                                                                     /* PRQA S 2814 # JV-01 */
    for (LucSgLoopCount = ADC_COUNT_BYTE_INIT; LucSgLoopCount < LucSgUnitCount; LucSgLoopCount++)
    {
      LpSgUnitConfig = &Adc_GpSgUnitConfig[LucDeInitPosition];                                                          /* PRQA S 2824 # JV-01 */
      /* Check SG use DMA and interrupt mode or not */
      if ((ADC_INTERRUPT_MODE == LpSgUnitConfig->enFunctionalityModeType) &&                                            /* PRQA S 2814 # JV-01 */
          (ADC_DMA_CHANNEL_OFF != LpSgUnitConfig->ucDmaChannelIndex))
      {
        /* Get the pointer to the DMA configuration */
        LpSGmDmaConfig = &Adc_GpDmaUnitConfig[LpSgUnitConfig->ucDmaChannelIndex];                                       /* PRQA S 2824 # JV-01 */
        /* Disable DMA interrupt for SG unit and perform synchronization for INTC2 */
        RH850_SV_SET_ICR_SYNCP(8, LpSGmDmaConfig->pDmaEicRegaddress, ADC_EIC_EIMK);                                     /* PRQA S 0751, 1006, 2814 # JV-01, JV-01, JV-01 */
      } /* else: No action required */
      /* DeInitPosition is increase */
      LucDeInitPosition++;                                                                                              /* PRQA S 3383 # JV-01 */
    } /* end of for (LucSgLoopCount = ADC_COUNT_BYTE_INIT; LucSgLoopCount < LucSgUnitCount; LucSgLoopCount++) */
  } /* end of for (LucLoopCount = ADC_COUNT_BYTE_INIT; LucLoopCount < (uint8)ADC_MAX_HW_UNITS; LucLoopCount++) */
  #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

  #if ((ADC_IP_ADCH == STD_ON) || (ADC_IP_ADCJ == STD_ON))
  /* Clear DMA Transfer Request Group Selection */
  ADC_DMACSEL0_0 = ADC_DMACSEL0_INIT;                                                                                   /* PRQA S 0303 # JV-01 */
  ADC_DMACSEL0_1 = ADC_DMACSEL0_INIT;                                                                                   /* PRQA S 0303 # JV-01 */
  ADC_DMACSEL1_0 = ADC_DMACSEL1_INIT;                                                                                   /* PRQA S 0303 # JV-01 */
  ADC_DMACSEL1_1 = ADC_DMACSEL1_INIT;                                                                                   /* PRQA S 0303 # JV-01 */

  /* Perform synchronization for DMATRGSEL */
  (void)ADC_DMACSEL1_1;                                                                                                 /* PRQA S 0303 # JV-01 */
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  #endif /* ((ADC_IP_ADCH == STD_ON) || (ADC_IP_ADCJ == STD_ON)) */

  #if (ADC_IP_ADCK == STD_ON)
  for (LulLoopCount = 0UL; LulLoopCount < (uint32)Adc_GucMaxDmaChannels; LulLoopCount++)
  {
    /* Get the pointer to DMA configuration */
    LpSGmDmaConfig = &Adc_GpDmaUnitConfig[LulLoopCount];                                                                /* PRQA S 2824 # JV-01 */

    /* De-initialize the DMA transfer request selection register */
    LulShift = (LpSGmDmaConfig->ulDmaResourceValue & ADC_DMA_CSEL_SHIFT_MASK) << 1U;                                    /* PRQA S 2814 # JV-01 */
    LulGroupSelect = *LpSGmDmaConfig->pDMACSEL;                                                                         /* PRQA S 2814 # JV-01 */
    LulGroupSelect &= ~(ADC_DMA_CSEL_MASK << LulShift);
    if (ADC_BYTE_ZERO != LpSGmDmaConfig->ucDmaUnit)
    {
      LulGroupSelect |= ADC_DMACSEL1_INIT & (ADC_DMA_CSEL_MASK << LulShift);                                            /* PRQA S 2986 # JV-01 */
    } /* else: No action required */
    *LpSGmDmaConfig->pDMACSEL = LulGroupSelect;
  } /* end of for (LulLoopCount = 0UL; LulLoopCount < (uint32)Adc_GucMaxDmaChannels; LulLoopCount++) */

  /* Perform dummy read and synchronization for DMATRGSEL */
  (void)*Adc_GpDmaUnitConfig[0].pDMACSEL;                                                                               /* PRQA S 2814 # JV-01 */
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  #endif /* (ADC_IP_ADCK == STD_ON) */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_DEINIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_DmaEnable
**
** Service ID           : NA
**
** Description          : This internal function configures DMA transfer in DMA channel register for requested group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different DMA channels, Non-Reentrant for the same DMA channel
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
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpDmaUnitConfig, Adc_GpGroupRamData
**
** Functions invoked    : None
**
** Registers Used       : DMAjCHCR_n, DMAjTMR_n, DMAjRS_n, DMAjSGCR_n, DMAjGIAI_n, DMAjSIAI_n, DMAjGOAI_n, DMAjSOAI_n,
**                        DMAjDPCR_n, DMAjDPPTR_n, DMAjCHFCR_n
**
** Reference ID         : ADC_DUD_ACT_061, ADC_DUD_ACT_061_REG001, ADC_DUD_ACT_061_REG002,
** Reference ID         : ADC_DUD_ACT_061_REG004, ADC_DUD_ACT_061_REG006, ADC_DUD_ACT_061_REG009,
** Reference ID         : ADC_DUD_ACT_061_REG010, ADC_DUD_ACT_061_REG012, ADC_DUD_ACT_061_REG013,
** Reference ID         : ADC_DUD_ACT_061_REG014, ADC_DUD_ACT_061_REG015, ADC_DUD_ACT_061_REG016,
** Reference ID         : ADC_DUD_ACT_061_REG017, ADC_DUD_ACT_061_REG018, ADC_DUD_ACT_061_REG019,
** Reference ID         : ADC_DUD_ACT_061_REG020, ADC_DUD_ACT_061_REG021, ADC_DUD_ACT_061_REG023,
** Reference ID         : ADC_DUD_ACT_061_REG024, ADC_DUD_ACT_061_REG025, ADC_DUD_ACT_061_REG026,
** Reference ID         : ADC_DUD_ACT_061_REG027, ADC_DUD_ACT_061_REG028, ADC_DUD_ACT_061_REG029,
** Reference ID         : ADC_DUD_ACT_061_REG030, ADC_DUD_ACT_061_REG031, ADC_DUD_ACT_061_REG032
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_DmaEnable(const Adc_GroupType LddGroup)                                                /* PRQA S 1532, 3006 # JV-01, JV-01 */
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_DmaRegisters, AUTOMATIC, REGSPACE) LpDmaRegisters;
  P2CONST(Adc_DmaConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpDmaUnitConfig;
  P2VAR(volatile Adc_DmaDescSetType, AUTOMATIC, REGSPACE) LpDmaDescSet;
  P2CONST(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  uint32 LulChannelCount;
  uint32 LulDescPtr;
  uint32 LulTransferMode;
  uint32 LulResourceSelect;
  uint32 LulGatherRepeat;
  uint32 LulScatterRepeat;
  #if (ADC_ENABLE_STREAMING == STD_ON)
  uint32 LulFirstHalf;
  uint32 LulLatterHalf;
  #endif /* (ADC_ENABLE_STREAMING == STD_ON) */

  /* Get the pointer to requested group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the SG unit which is configured for this group */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex];                                                         /* PRQA S 2814, 2824 # JV-01, JV-01 */
  /* Get the pointer to DMA configuration */
  LpDmaUnitConfig = &Adc_GpDmaUnitConfig[LpSgUnitConfig->ucDmaChannelIndex];                                            /* PRQA S 2814, 2824 # JV-01, JV-01 */
  /* Initialize Group RAM data to a local pointer */
  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */

  /* Get the base address of DMA register */
  LpDmaRegisters = LpDmaUnitConfig->pDmaRegBaseaddress;                                                                 /* PRQA S 2814 # JV-01 */

  /* Clear all enable bits except global DMA error and disable DMA transfer */
  LpDmaRegisters->usDMAjCHCRn &= ADC_DMA_CHCR_CAEE;                                                                     /* PRQA S 2814 # JV-01 */

  /* Get the number of channels configured for the requested group */
  LulChannelCount = (uint32)LpGroupData->ucChannelCount;                                                                /* PRQA S 2814 # JV-01 */

  /* Get the channel request priority setting to hold its value */
  #if (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS)
  LulTransferMode = (LpDmaRegisters->ulDMAjTMRn & ADC_DMA_TMR_PRI_MASK) | ADC_DMA_TMR_TRS | ADC_DMA_TMR_DTS_2;
  #else
  LulTransferMode = (LpDmaRegisters->ulDMAjTMRn & ADC_DMA_TMR_PRI_MASK) | ADC_DMA_TMR_TRS | ADC_DMA_TMR_DTS_4;
  #endif /* (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS) */

  /* Set the repeat count of the inner DMA loop for gather */
  LulGatherRepeat = LulChannelCount - 1UL;                                                                              /* PRQA S 3383 # JV-01 */

  #if (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS) 
  /* Select the source transfer size of 2-byte for 16-bit access to ADCXnDIR register */
  LulTransferMode |= ADC_DMA_TMR_STS_2;
  #else
  /* Select the source transfer size of 4-byte for 32-bit access to ADCXnDIR register */
  LulTransferMode |= ADC_DMA_TMR_STS_4;
  #endif /* (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS) */
  /* Set the transfer count per request and the trigger request source for ADC SG unit */
  LulResourceSelect = LulChannelCount << ADC_DMA_RS_TC_SFT;

  /* Set the repeat count of the inner DMA loop for scatter */
  LulScatterRepeat = LulChannelCount - 1UL;                                                                             /* PRQA S 3383 # JV-01 */

  /* Set the transfer mode register */
  LpDmaRegisters->ulDMAjTMRn = LulTransferMode;

  /* Set the resource select register */
  LpDmaRegisters->ulDMAjRSn = LulResourceSelect | LpDmaUnitConfig->ulDmaResourceValue;

  /* Set the scatter gather control register */
  LpDmaRegisters->ulDMAjSGCRn =
    ADC_DMA_SGCR_SEN | (LulScatterRepeat << ADC_DMA_SGCR_SIRPT_SFT) | ADC_DMA_SGCR_GEN | LulGatherRepeat;

  /* Set the gather/scatter inner address increment registers */
  LpDmaRegisters->ulDMAjGIAIn = ADC_DMA_STS_SIZE;
  LpDmaRegisters->ulDMAjSIAIn = (uint32)LpGroup->ddNumberofSamples * ADC_DMA_DATA_SIZE;                                 /* PRQA S 3383, 3384 # JV-01, JV-01 */

  /* Set the descriptor control register */
  LpDmaRegisters->ulDMAjDPCRn = ADC_DMA_DPCR_UPF_SAR | ADC_DMA_DPCR_UPF_DAR | ADC_DMA_DPCR_UPF_TSR;
  #if (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_32_BITS)
  if (ADC_POLLING_MODE == LpSgUnitConfig->enFunctionalityModeType)
  {
    /* Get descriptor pointer for SG unit and set descriptor step interrupt disable */
    LulDescPtr = (uint32)LpDmaUnitConfig->usDmaDescriptorPointer & ~ADC_DMA_DPPTR_DIE;
  }
  else
  #endif /* (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_32_BITS) */
  {
    /* Get descriptor pointer for SG unit and set descriptor step interrupt enable */
    LulDescPtr = (uint32)LpDmaUnitConfig->usDmaDescriptorPointer | ADC_DMA_DPPTR_DIE;
  }

  /* Check whether group belongs to non-implicitly stopped group or not */
  if (ADC_FALSE == LpGroup->blImplicitlyStopped)
  {
    /* Set the continuation flag to the descriptor pointer */
    LulDescPtr |= ADC_DMA_DPPTR_CF;
  } /* else: No action required */

  /* Get the descriptor address of the SG unit */
  LpDmaDescSet = LpDmaUnitConfig->pDmaDescriptoraddress;

  /* Set the source/destination addresses to the descriptor 0 */
  LpDmaDescSet->aaDmaDesc[0].ulDMAjSARn = LpSgUnitConfig->ulDmaSourceAddress;                                           /* PRQA S 2814 # JV-01 */
  LpDmaDescSet->aaDmaDesc[0].ulDMAjDARn = (uint32)LpGroupData->pChannelBuffer;                                          /* PRQA S 0306 # JV-01 */

  #if (ADC_ENABLE_STREAMING == STD_ON)
  if (ADC_ACCESS_MODE_STREAMING == LpGroup->enGroupAccessMode)
  {
    /* Set the gather/scatter outer address increment registers */
    LpDmaRegisters->ulDMAjGOAIn = 0UL - (LulGatherRepeat * ADC_DMA_STS_SIZE);                                           /* PRQA S 2986, 3383 # JV-01, JV-01 */
    LpDmaRegisters->ulDMAjSOAIn =
      0UL - ((uint32)LpGroup->ddNumberofSamples * LulScatterRepeat * ADC_DMA_DATA_SIZE) + ADC_DMA_DATA_SIZE;            /* PRQA S 2986, 3383, 3384 # JV-01, JV-01, JV-01 */

    /* The latter half for descriptor 1 is the number obtained by rounding down half the number of samples */
    LulLatterHalf = (uint32)LpGroup->ddNumberofSamples >> 1U;
    /* The first half for descriptor 0 is the number obtained by rounding up half the number of samples */
    LulFirstHalf = (uint32)LpGroup->ddNumberofSamples - LulLatterHalf;                                                  /* PRQA S 3383, 3384 # JV-01, JV-01 */

    /* Check if the transfer is half complete */
    if ((uint32)LpGroupData->ucSamplesCompleted == LulFirstHalf)
    {
      /* Set the descriptor 1 pointer as the first descriptor */
      LpDmaRegisters->ulDMAjDPPTRn = LulDescPtr + (uint32)sizeof(Adc_DmaDescType);                                      /* PRQA S 3383 # JV-01 */
    }
    else
    {
      /* Set the descriptor 0 pointer as the first descriptor */
      LpDmaRegisters->ulDMAjDPPTRn = LulDescPtr;
    }

    /* Set the transfer size to the descriptor 0 */
    LpDmaDescSet->aaDmaDesc[0].ulDMAjTSRn = ADC_DMA_DATA_SIZE * LulChannelCount * LulFirstHalf;                         /* PRQA S 3383, 3384 # JV-01, JV-01 */
    /* Set next descriptor pointer to the descriptor 1 */
    LpDmaDescSet->aaDmaDesc[0].ulDMAjDPPTRn =
      (LulDescPtr + (uint32)sizeof(Adc_DmaDescType)) | ADC_DMA_DPPTR_DIE | ADC_DMA_DPPTR_CF;                            /* PRQA S 3383 # JV-01 */

    /* Set the source/destination addresses and transfer size to the descriptor 1 */
    LpDmaDescSet->aaDmaDesc[1].ulDMAjSARn = LpSgUnitConfig->ulDmaSourceAddress;
    LpDmaDescSet->aaDmaDesc[1].ulDMAjDARn = (uint32)&LpGroupData->pChannelBuffer[LulFirstHalf];                         /* PRQA S 0306 # JV-01 */
    LpDmaDescSet->aaDmaDesc[1].ulDMAjTSRn = ADC_DMA_DATA_SIZE * LulChannelCount * LulLatterHalf;                        /* PRQA S 3383, 3384 # JV-01, JV-01 */
    /* Set next descriptor pointer to the descriptor 0 */
    LpDmaDescSet->aaDmaDesc[1].ulDMAjDPPTRn = LulDescPtr;
  } /* end of if (ADC_ACCESS_MODE_STREAMING == LpGroup->enGroupAccessMode) */
  else
  #endif /* (ADC_ENABLE_STREAMING == STD_ON) */
  {
    /* Clear the gather/scatter outer address increment registers */
    LpDmaRegisters->ulDMAjGOAIn = 0UL;
    LpDmaRegisters->ulDMAjSOAIn = 0UL;

    /* Set first descriptor pointer */
    LpDmaRegisters->ulDMAjDPPTRn = LulDescPtr;

    /* Set the transfer size to the descriptor 0 */
    LpDmaDescSet->aaDmaDesc[0].ulDMAjTSRn = ADC_DMA_DATA_SIZE * LulChannelCount;                                        /* PRQA S 3383 # JV-01 */
    /* Set next descriptor pointer to the descriptor 0 */
    LpDmaDescSet->aaDmaDesc[0].ulDMAjDPPTRn = LulDescPtr;
  }

  /* Set the clear flags for clearing DMA transfer status */
  LpDmaRegisters->ulDMAjCHFCRn =
    ADC_DMA_CHFCR_TEC | ADC_DMA_CHFCR_DSEC | ADC_DMA_CHFCR_CAEC | ADC_DMA_CHFCR_DRQC | ADC_DMA_CHFCR_OVFC;

  #if (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_32_BITS)
  if (ADC_POLLING_MODE == LpSgUnitConfig->enFunctionalityModeType)
  {
    /* Set the descriptor enable and start bits and DMA enable bit for enabling DMA */
    LpDmaRegisters->usDMAjCHCRn |= (uint16)(ADC_DMA_CHCR_DPE | ADC_DMA_CHCR_DPB | ADC_DMA_CHCR_DE);
  }
  else
  #endif /* (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_32_BITS) */
  {
    /* Set the descriptor enable and start bits and enable DMA interrupt and DMA enable bit for enabling DMA */
    LpDmaRegisters->usDMAjCHCRn |= (uint16)(ADC_DMA_CHCR_DPE | ADC_DMA_CHCR_DPB | ADC_DMA_CHCR_DSIE | ADC_DMA_CHCR_DE);
  }

  /* Perform synchronization for SDMAC */
  (void)LpDmaRegisters->usDMAjCHCRn;
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
}

#define ADC_STOP_SEC_PRIVATE_CODE 
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_DmaDisable
**
** Service ID           : NA
**
** Description          : This internal function shall disable DMA transfer
**                        in the DMA channel register of requested group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
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
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpDmaUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : DMAjCHFCR_n, DMAjCHSTA_n, DMAjCHCR_n
**
** Reference ID         : ADC_DUD_ACT_062, ADC_DUD_ACT_062_REG001, ADC_DUD_ACT_062_REG002, ADC_DUD_ACT_062_REG003
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(boolean, ADC_PRIVATE_CODE) Adc_DmaDisable(const Adc_GroupType LddGroup)                                            /* PRQA S 1532, 3006 # JV-01, JV-01 */
{
  /* Check if DMA is disabled correctly? */
  boolean LblDmaTimedOut;
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_DmaRegisters, AUTOMATIC, REGSPACE) LpDmaRegisters;
  P2CONST(Adc_DmaConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpSGmDmaConfig;
  uint32 LulCount;

  /* Get the pointer to requested group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the SG unit which is configured for this group */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex];                                                         /* PRQA S 2814, 2824 # JV-01, JV-01 */
  /* Get the pointer to DMA configuration */
  LpSGmDmaConfig = &Adc_GpDmaUnitConfig[LpSgUnitConfig->ucDmaChannelIndex];                                             /* PRQA S 2814, 2824 # JV-01, JV-01 */

  LpDmaRegisters = LpSGmDmaConfig->pDmaRegBaseaddress;                                                                  /* PRQA S 2814 # JV-01 */

  /* Disable DMA transfer */
  LpDmaRegisters->ulDMAjCHFCRn = ADC_DMA_CHFCR_DEC;                                                                     /* PRQA S 2814 # JV-01 */

  /* Wait until the DMAjHSTA.BUSY bit is cleared. */
  LulCount = ADC_DMA_TIMEOUT_COUNT;
  while ((LulCount > 0UL) && (0UL != (LpDmaRegisters->ulDMAjCHSTAn & ADC_DMA_CHSTA_BUSY)))
  {
    /* Perform SYNCP to stabilize the operation cycle. */
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
    LulCount--;
  }

  /* Clear transfer end flag */
  LpDmaRegisters->ulDMAjCHFCRn = ADC_DMA_CHFCR_TEC;                                                                     /* PRQA S 2814 # JV-01 */
  /* Disable DMA control bits */
  LpDmaRegisters->usDMAjCHCRn &= ADC_DMA_CHCR_CAEE;

  /* Perform synchronization for SDMAC */
  (void)LpDmaRegisters->usDMAjCHCRn;
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */

  if (ADC_COUNT_DWORD_INIT == LulCount)
  {
    /* DMA is NOT stopped */
    LblDmaTimedOut = ADC_TRUE;
  }
  else
  {
    /* DMA is stopped */
    LblDmaTimedOut = ADC_FALSE;
  }
  return LblDmaTimedOut;
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_DmaGetTransferStatus
**
** Service ID           : NA
**
** Description          : This internal function gets DMA transfer status.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
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
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpDmaUnitConfig, Adc_GpGroupRamData
**
** Functions invoked    : None
**
** Registers Used       : DMAjCHSTA_n
**
** Reference ID         : ADC_DUD_ACT_063
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(boolean, ADC_PRIVATE_CODE) Adc_DmaGetTransferStatus(const Adc_GroupType LddGroup)                                  /* PRQA S 1532 # JV-01 */
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  volatile P2CONST(Adc_DmaRegisters, AUTOMATIC, REGSPACE) LpDmaRegisters;
  P2CONST(Adc_DmaConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpSGmDmaConfig;
  volatile boolean LblTransferflag;
  #if (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_32_BITS)
  volatile P2CONST(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) LpChannelBuffer;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;                                      /* PRQA S 3678 # JV-01 */
  uint32 LulNumOfSamples;
  #endif /* (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_32_BITS) */

  /* Get the pointer to requested group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the SG unit which is configured for this group */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex];                                                         /* PRQA S 2814, 2824 # JV-01, JV-01 */
  /* Get the pointer to DMA configuration */
  LpSGmDmaConfig = &Adc_GpDmaUnitConfig[LpSgUnitConfig->ucDmaChannelIndex];                                             /* PRQA S 2814, 2824 # JV-01, JV-01 */
  LpDmaRegisters = LpSGmDmaConfig->pDmaRegBaseaddress;                                                                  /* PRQA S 2814 # JV-01 */
  LblTransferflag = ADC_FALSE;

  #if (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_32_BITS)
  /* Check if the Group is mapped for HW configured for interrupt mode */
  if (ADC_POLLING_MODE == LpSgUnitConfig->enFunctionalityModeType)
  {
    /* Get the number of samples configured for the group */
    LulNumOfSamples = LpGroup->ddNumberofSamples;
    /* Get the pointer to group ram data */
    LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                        /* PRQA S 2824 # JV-01 */
    /* Get the base address of the Group buffer */
    LpChannelBuffer = LpGroupData->pChannelBuffer;                                                                      /* PRQA S 2814 # JV-01 */
    /* Check no Error and Write Flag at the last converted value */
    if (0UL != (LpChannelBuffer[LulNumOfSamples - ADC_BYTE_ONE] & ADC_DIR_IDEF_WFLAG))                                  /* PRQA S 2814, 2824, 2844, 3383 # JV-01, JV-01, JV-01, JV-01 */
    {
      /* Set the transfer flag is ADC_TRUE*/
      LblTransferflag = ADC_TRUE;
    } /* else: No action required */
  }
  else
  #endif /* (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_32_BITS) */
  {
    /* Check if the Descriptor Step has finished */
    if (0UL != (LpDmaRegisters->ulDMAjCHSTAn & (ADC_DMA_CHSTA_TE | ADC_DMA_CHSTA_DSE)))                                   /* PRQA S 2814 # JV-01 */
    {
      /* Set the transfer flag is ADC_TRUE */
      LblTransferflag = ADC_TRUE;
    } /* else: No action required */
  }
  return LblTransferflag;
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_DmaClearInterruptFlag
**
** Service ID           : NA
**
** Description          : This internal function clears DMA interrupt flag.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
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
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpDmaUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : DMAjCHFCR_n, DMAjCHSTA_n
**
** Reference ID         : ADC_DUD_ACT_064, ADC_DUD_ACT_064_REG003
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_DmaClearInterruptFlag(const Adc_GroupType LddGroup)                                    /* PRQA S 1532, 3006 # JV-01, JV-01 */
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_DmaRegisters, AUTOMATIC, REGSPACE) LpDmaRegisters;
  P2CONST(Adc_DmaConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpSGmDmaConfig;

  /* Get the pointer to requested group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the SG unit which is configured for this group */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex];                                                         /* PRQA S 2814, 2824 # JV-01, JV-01 */
  /* Get the pointer to DMA configuration */
  LpSGmDmaConfig = &Adc_GpDmaUnitConfig[LpSgUnitConfig->ucDmaChannelIndex];                                             /* PRQA S 2814, 2824 # JV-01, JV-01 */
  LpDmaRegisters = LpSGmDmaConfig->pDmaRegBaseaddress;                                                                  /* PRQA S 2814 # JV-01 */

  /* Clear descriptor step end flag */
  LpDmaRegisters->ulDMAjCHFCRn = ADC_DMA_CHFCR_DSEC;                                                                    /* PRQA S 2814 # JV-01 */

  /* Perform synchronization for SDMAC */
  (void)LpDmaRegisters->ulDMAjCHSTAn;
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
