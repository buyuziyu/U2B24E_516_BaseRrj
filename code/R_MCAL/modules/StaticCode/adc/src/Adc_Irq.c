/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_Irq.c                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* ISR functions of the ADC Driver Component                                                                          */
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
 * 2.1.3: 31/10/2024 : As part of U2Ax support, following changes are made:
 *                     1.Add the condition to implement interrupt in U2Ax
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 *                     As part of U2Cx support, following changes are made:
 *                     1.Add the condition of macro ADC_IP_C_ADCK to implement interrupt in U2Cx
 * 2.0.0: 28/08/2023 : Removed Multi-Instance define. Change Adc_Mapping.h to Adc_Memmap.h
 * 1.4.5: 14/09/2022 : Updated QAC messages according to QAC analysis results.
 * 1.4.4: 21/07/2022 : Updated Global Variables, Functions invoked and Registers Used in function header comments.
 * 1.4.3: 23/05/2022 : Updated QAC comments for U2Bx.
 * 1.4.1: 24/11/2021 : Added SG and ERR ISRs for ADCKA.
 *                     Changed the parity error ISR to support ADCK.
 * 1.3.2: 09/09/2021 : Changed the name of macros for EIC and ECM.
 *        06/09/2021 : Changed to Adc_Mapping.h from Adc_MemMap.h
 * 1.3.1: 17/07/2021 : Changed pointer arithmetic to access as an array.
 *        07/07/2021 : Added QAC message 9.5.0
 *                     Changed comment format to 120 columns
 *                     Changed violation tag from START/END
 *        24/05/2021 : Removed unnecessary include header.
 *                     Separated "ADCn_ISR" function headers to "ADCn_SGx_ISR" and "ADCn_ERR_ISR".
 *                     Changed "Adc_DmaIsrn" function header to "ADC_DMAn_CHm_ISR".
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.2.0: 04/08/2020 : Release
 *                     Add QAC 9.3.1 comment.
 *                     Checking ECM error factors after ECM interrupt in
 *                     ADC_PARITY_ERR_ISR.
 *                     Update offset value when checking interrupt consistency
 *                     in ADCn_ERR_ISR.
 * 1.1.0: 19/06/2020 : Release
 * 1.0.2: 24/04/2020 : Add critical section protection before calling Adc_DmaIsr
 *                     in ADC_DMA0_CH01_ISR, ADC_DMA0_CH02_ISR
 * 1.0.1: 13/04/2020 : Update software version definition.
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for version check macro definitions and type definitions */
#include "Adc.h"

/* Included for the declaration of DMA global pointer declarations */
#include "Adc_Ram.h"
/* Included for the declaration of Adc_Isr() */
#include "Adc_LLDriver.h"

#include ADC_HWIP_PBTYPES_H_FILE

/* Included for the declaration of ISR prototypes */
#include "Adc_Irq.h"

/* Included for declaration of the function DEM_REPORT_ERROR() */
#include "Dem.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ADC_IRQ_C_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION_VALUE
#define ADC_IRQ_C_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION_VALUE
#define ADC_IRQ_C_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ADC_IRQ_C_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION_VALUE
#define ADC_IRQ_C_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ADC_IRQ_AR_RELEASE_MAJOR_VERSION != ADC_IRQ_C_AR_RELEASE_MAJOR_VERSION)
  #error "Adc_Irq.c : Mismatch in Release Major Version"
#endif

#if (ADC_IRQ_AR_RELEASE_MINOR_VERSION != ADC_IRQ_C_AR_RELEASE_MINOR_VERSION)
  #error "Adc_Irq.c : Mismatch in Release Minor Version"
#endif

#if (ADC_IRQ_AR_RELEASE_REVISION_VERSION != ADC_IRQ_C_AR_RELEASE_REVISION_VERSION)
  #error "Adc_Irq.c : Mismatch in Release Patch Version"
#endif

#if (ADC_IRQ_SW_MAJOR_VERSION != ADC_IRQ_C_SW_MAJOR_VERSION)
  #error "Adc_Irq.c : Mismatch in Software Major Version"
#endif

#if (ADC_IRQ_SW_MINOR_VERSION != ADC_IRQ_C_SW_MINOR_VERSION)
  #error "Adc_Irq.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : MISRA C:2012 Rule-11.4, CERTCCM INT36, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2824)    : Possible: Arithmetic operation on NULL pointer.                                              */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-468, CWE-476, CWE-465, CWE-737                                   */
/* JV-01 Justification : This is accepted, due to the implementation following hardware specification.                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : '%s' has external linkage and is being defined without any previous declaration.             */
/* Rule                : MISRA C:2012 Rule-8.4, CERTCCM DCL07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name        : ADCn_SGx_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt Service routines for the ADC
**                        where n represents an instance of the hardware unit.
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
** Global Variables     : Adc_GpHwUnitIndex, Adc_GpSgUnitIndex
**
** Functions invoked    : Adc_Isr, ADC_DEM_REPORT_ERROR
**
** Registers Used       : EIC
**
** Reference ID         : ADC_DUD_ACT_016, ADC_DUD_ACT_016_ERR001
***********************************************************************************************************************/
#if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"

#if (ADC_IP_C_ADCK == STD_OFF)
#if (ADC0_SG0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC0_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC0_SG0_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC0_SG0_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC0_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC0_BASEADDR)[ADC_SCANGROUP_0] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 0 and SGx unit 0 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_0], Adc_GpSgUnitIndex[(ADC_HWUNIT_0 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_0]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC0_SG0_ISR_API == STD_ON) */

#if (ADC0_SG1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC0_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC0_SG1_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC0_SG1_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC0_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC0_BASEADDR)[ADC_SCANGROUP_1] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 0 and SGx unit 1 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_0], Adc_GpSgUnitIndex[(ADC_HWUNIT_0 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_1]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC0_SG1_ISR_API == STD_ON) */

#if (ADC0_SG2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC0_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC0_SG2_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC0_SG2_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC0_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC0_BASEADDR)[ADC_SCANGROUP_2] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 0 and SGx unit 2 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_0], Adc_GpSgUnitIndex[(ADC_HWUNIT_0 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_2]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC0_SG2_ISR_API == STD_ON) */

#if (ADC0_SG3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC0_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC0_SG3_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC0_SG3_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC0_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC0_BASEADDR)[ADC_SCANGROUP_3] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 0 and SGx unit 3 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_0], Adc_GpSgUnitIndex[(ADC_HWUNIT_0 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_3]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC0_SG3_ISR_API == STD_ON) */

#if (ADC0_SG4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC0_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC0_SG4_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC0_SG4_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC0_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC0_BASEADDR)[ADC_SCANGROUP_4] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 0 and SGx unit 4 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_0], Adc_GpSgUnitIndex[(ADC_HWUNIT_0 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_4]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC0_SG4_ISR_API == STD_ON) */
#endif /* (ADC_IP_C_ADCK == STD_OFF) */

#if (ADC1_SG0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC1_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC1_SG0_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC1_SG0_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC1_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC1_BASEADDR)[ADC_SCANGROUP_0] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 1 and SGx unit 0 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_1], Adc_GpSgUnitIndex[(ADC_HWUNIT_1 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_0]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC1_SG0_ISR_API == STD_ON) */

#if (ADC1_SG1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC1_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC1_SG1_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC1_SG1_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC1_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC1_BASEADDR)[ADC_SCANGROUP_1] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 1 and SGx unit 1 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_1], Adc_GpSgUnitIndex[(ADC_HWUNIT_1 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_1]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC1_SG1_ISR_API == STD_ON) */

#if (ADC1_SG2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC1_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC1_SG2_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC1_SG2_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC1_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC1_BASEADDR)[ADC_SCANGROUP_2] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 1 and SGx unit 2 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_1], Adc_GpSgUnitIndex[(ADC_HWUNIT_1 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_2]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC1_SG2_ISR_API == STD_ON) */

#if (ADC1_SG3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC1_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC1_SG3_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC1_SG3_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC1_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC1_BASEADDR)[ADC_SCANGROUP_3] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 1 and SGx unit 3 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_1], Adc_GpSgUnitIndex[(ADC_HWUNIT_1 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_3]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC1_SG3_ISR_API == STD_ON) */

#if (ADC1_SG4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC1_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC1_SG4_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC1_SG4_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC1_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC1_BASEADDR)[ADC_SCANGROUP_4] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 1 and SGx unit 4 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_1], Adc_GpSgUnitIndex[(ADC_HWUNIT_1 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_4]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC1_SG4_ISR_API == STD_ON) */

#if (ADC2_SG0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC2_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC2_SG0_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC2_SG0_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC2_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC2_BASEADDR)[ADC_SCANGROUP_0] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 2 and SGx unit 0 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_2], Adc_GpSgUnitIndex[(ADC_HWUNIT_2 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_0]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC2_SG0_ISR_API == STD_ON) */

#if (ADC2_SG1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC2_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC2_SG1_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC2_SG1_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC2_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC2_BASEADDR)[ADC_SCANGROUP_1] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 2 and SGx unit 1 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_2], Adc_GpSgUnitIndex[(ADC_HWUNIT_2 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_1]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC2_SG1_ISR_API == STD_ON) */

#if (ADC2_SG2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC2_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC2_SG2_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC2_SG2_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC2_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC2_BASEADDR)[ADC_SCANGROUP_2] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 2 and SGx unit 2 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_2], Adc_GpSgUnitIndex[(ADC_HWUNIT_2 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_2]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC2_SG2_ISR_API == STD_ON) */

#if (ADC2_SG3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC2_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC2_SG3_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC2_SG3_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC2_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC2_BASEADDR)[ADC_SCANGROUP_3] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 2 and SGx unit 3 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_2], Adc_GpSgUnitIndex[(ADC_HWUNIT_2 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_3]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC2_SG3_ISR_API == STD_ON) */

#if (ADC2_SG4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC2_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC2_SG4_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC2_SG4_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC2_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC2_BASEADDR)[ADC_SCANGROUP_4] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 2 and SGx unit 4 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_2], Adc_GpSgUnitIndex[(ADC_HWUNIT_2 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_4]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC2_SG4_ISR_API == STD_ON) */

#if (ADC_IP_ADCK == STD_ON && ADC_IP_C_ADCK == STD_OFF)
#if (ADC3_SG0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC3_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC3_SG0_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC3_SG0_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC3_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC3_BASEADDR)[ADC_SCANGROUP_0] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 3 and SGx unit 0 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_3], Adc_GpSgUnitIndex[(ADC_HWUNIT_3 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_0]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC3_SG0_ISR_API == STD_ON) */

#if (ADC3_SG1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC3_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC3_SG1_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC3_SG1_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC3_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC3_BASEADDR)[ADC_SCANGROUP_1] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 3 and SGx unit 1 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_3], Adc_GpSgUnitIndex[(ADC_HWUNIT_3 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_1]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC3_SG1_ISR_API == STD_ON) */

#if (ADC3_SG2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC3_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC3_SG2_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC3_SG2_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC3_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC3_BASEADDR)[ADC_SCANGROUP_2] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 3 and SGx unit 2 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_3], Adc_GpSgUnitIndex[(ADC_HWUNIT_3 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_2]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC3_SG2_ISR_API == STD_ON) */

#if (ADC3_SG3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC3_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC3_SG3_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC3_SG3_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC3_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC3_BASEADDR)[ADC_SCANGROUP_3] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 3 and SGx unit 3 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_3], Adc_GpSgUnitIndex[(ADC_HWUNIT_3 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_3]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC3_SG3_ISR_API == STD_ON) */

#if (ADC3_SG4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC3_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC3_SG4_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC3_SG4_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC3_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADC3_BASEADDR)[ADC_SCANGROUP_4] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 3 and SGx unit 4 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_3], Adc_GpSgUnitIndex[(ADC_HWUNIT_3 * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_4]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC3_SG4_ISR_API == STD_ON) */
#endif /*(ADC_IP_ADCK == STD_ON && ADC_IP_C_ADCK == STD_OFF)*/

#if ((ADC_IP_ADCK == STD_ON) || (ADC_IP_C_ADCK == STD_ON))
#if (ADCA_SG0_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADCA_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADCA_SG0_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADCA_SG0_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADCA_SG0_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADCA_BASEADDR)[ADC_SCANGROUP_0] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit A and SGx unit 0 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_A], Adc_GpSgUnitIndex[(ADC_HWUNIT_A * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_0]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADCA_SG0_ISR_API == STD_ON) */

#if (ADCA_SG1_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADCA_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADCA_SG1_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADCA_SG1_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADCA_SG1_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADCA_BASEADDR)[ADC_SCANGROUP_1] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit A and SGx unit 1 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_A], Adc_GpSgUnitIndex[(ADC_HWUNIT_A * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_1]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADCA_SG1_ISR_API == STD_ON) */

#if (ADCA_SG2_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADCA_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADCA_SG2_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADCA_SG2_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADCA_SG2_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADCA_BASEADDR)[ADC_SCANGROUP_2] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit A and SGx unit 2 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_A], Adc_GpSgUnitIndex[(ADC_HWUNIT_A * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_2]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADCA_SG2_ISR_API == STD_ON) */

#if (ADCA_SG3_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADCA_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADCA_SG3_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADCA_SG3_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADCA_SG3_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADCA_BASEADDR)[ADC_SCANGROUP_3] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit A and SGx unit 3 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_A], Adc_GpSgUnitIndex[(ADC_HWUNIT_A * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_3]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADCA_SG3_ISR_API == STD_ON) */

#if (ADCA_SG4_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADCA_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADCA_SG4_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADCA_SG4_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADCA_SG4_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADCA_BASEADDR)[ADC_SCANGROUP_4] & ADC_EIC_EIMK))                                 /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit A and SGx unit 4 */
    Adc_Isr(Adc_GpHwUnitIndex[ADC_HWUNIT_A], Adc_GpSgUnitIndex[(ADC_HWUNIT_A * ADC_NUM_SCANGROUP) + ADC_SCANGROUP_4]);  /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADCA_SG4_ISR_API == STD_ON) */
#endif /* ((ADC_IP_ADCK == STD_ON) || (ADC_IP_C_ADCK == STD_ON)) */

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

/***********************************************************************************************************************
** Function Name        : ADCn_ERR_ISR
**
** Service ID           : NA
**
** Description          : These are Error Interrupt Service routines for the ADC
**                        where n represents an instance of the hardware unit.
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
** Global Variables     : Adc_GpHwUnitIndex
**
** Functions invoked    : Adc_ErrIsr, ADC_DEM_REPORT_ERROR
**
** Registers Used       : EIC
**
** Reference ID         : ADC_DUD_ACT_017, ADC_DUD_ACT_017_ERR001
***********************************************************************************************************************/
#if (ADC_ENABLE_ERR_INT == STD_ON)
#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (ADC_IP_C_ADCK == STD_OFF)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC0_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC0_ERR_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC0_ERR_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC0_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((*(ADC_EIC_ADE_BASEADDR)) & ADC_EIC_EIMK))                                                /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 0 */
    Adc_ErrIsr(Adc_GpHwUnitIndex[ADC_HWUNIT_0]);                                                                        /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_IP_C_ADCK == STD_OFF) */

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC1_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC1_ERR_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC1_ERR_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC1_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADE_BASEADDR)[ADC1_ERR_EIC_OFFSET] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 1 */
    Adc_ErrIsr(Adc_GpHwUnitIndex[ADC_HWUNIT_1]);                                                                        /* PRQA S 2824 # JV-01 */
  }
}

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC2_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC2_ERR_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC2_ERR_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC2_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADE_BASEADDR)[ADC2_ERR_EIC_OFFSET] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 2 */
    Adc_ErrIsr(Adc_GpHwUnitIndex[ADC_HWUNIT_2]);                                                                        /* PRQA S 2824 # JV-01 */
  }
}

#if ((ADC_IP_ADCH == STD_ON) || (ADC_IP_ADCK == STD_ON) && (ADC_IP_C_ADCK == STD_OFF))
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC3_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC3_ERR_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC3_ERR_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC3_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADE_BASEADDR)[ADC3_ERR_EIC_OFFSET] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit 3 */
    Adc_ErrIsr(Adc_GpHwUnitIndex[ADC_HWUNIT_3]);                                                                        /* PRQA S 2824 # JV-01 */
  }
}
#endif /* ((ADC_IP_ADCH == STD_ON) || (ADC_IP_ADCK == STD_ON) && (ADC_IP_C_ADCK == STD_OFF)) */

#if (ADC_IP_ADCK == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADCA_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADCA_ERR_CAT2_ISR)                                                                                                  /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADCA_ERR_ISR(void)                                                                /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADCA_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_ADE_BASEADDR)[ADCA_ERR_EIC_OFFSET] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    /* HW unit A */
    Adc_ErrIsr(Adc_GpHwUnitIndex[ADC_HWUNIT_A]);                                                                        /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_IP_ADCK == STD_ON) */

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (ADC_ENABLE_ERR_INT == STD_ON) */

/***********************************************************************************************************************
** Function Name        : ADC_DMAn_CHm_ISR
**
** Service ID           : NA
**
** Description          : These are DMA Interrupt Service routines for the ADC
**                        where n represents an instance of the DMA unit and
**                        m represents the index of the channel.
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
** Global Variables     : Adc_GpDmaHWUnitMapping, Adc_GpDmaSGUnitMapping
**
** Functions invoked    : Adc_DmaIsr, ADC_DEM_REPORT_ERROR
**
** Registers Used       : EIC
**
** Reference ID         : ADC_DUD_ACT_018, ADC_DUD_ACT_018_ERR001
***********************************************************************************************************************/
#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (ADC_DMA0_ISR_CH00_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH00_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH00_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH00_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH00_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_0] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_0], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_0]);                   /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH00_API == STD_ON) */

#if (ADC_DMA0_ISR_CH01_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH01_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH01_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH01_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH01_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_1] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_1], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_1]);                   /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH01_API == STD_ON) */

#if (ADC_DMA0_ISR_CH02_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH02_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH02_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH02_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH02_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_2] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_2], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_2]);                   /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH02_API == STD_ON) */

#if (ADC_DMA0_ISR_CH03_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH03_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH03_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH03_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH03_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_3] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_3], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_3]);                   /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH03_API == STD_ON) */

#if (ADC_DMA0_ISR_CH04_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH04_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH04_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH04_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH04_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_4] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_4], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_4]);                   /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH04_API == STD_ON) */

#if (ADC_DMA0_ISR_CH05_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH05_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH05_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH05_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH05_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_5] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_5], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_5]);                   /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH05_API == STD_ON) */

#if (ADC_DMA0_ISR_CH06_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH06_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH06_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH06_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH06_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_6] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_6], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_6]);                   /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH06_API == STD_ON) */

#if (ADC_DMA0_ISR_CH07_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH07_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH07_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH07_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH07_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_7] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_7], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_7]);                   /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH07_API == STD_ON) */

#if (ADC_DMA0_ISR_CH08_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH08_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH08_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH08_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH08_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_8] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_8], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_8]);                   /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH08_API == STD_ON) */

#if (ADC_DMA0_ISR_CH09_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH09_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH09_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH09_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH09_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_9] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_9], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_9]);                   /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH09_API == STD_ON) */

#if (ADC_DMA0_ISR_CH10_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH10_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH10_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH10_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH10_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_10] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_10], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_10]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH10_API == STD_ON) */

#if (ADC_DMA0_ISR_CH11_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH11_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH11_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH11_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH11_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_11] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_11], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_11]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH11_API == STD_ON) */

#if (ADC_DMA0_ISR_CH12_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH12_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH12_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH12_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH12_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_12] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_12], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_12]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH12_API == STD_ON) */

#if (ADC_DMA0_ISR_CH13_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH13_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH13_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH13_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH13_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_13] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_13], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_13]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH13_API == STD_ON) */

#if (ADC_DMA0_ISR_CH14_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH14_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH14_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH14_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH14_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_14] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_14], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_14]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH14_API == STD_ON) */

#if (ADC_DMA0_ISR_CH15_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA0_CH15_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA0_CH15_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA0_CH15_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA0_CH15_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA0_BASEADDR)[ADC_DMA_CHANNEL_15] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_15], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_15]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA0_ISR_CH15_API == STD_ON) */

#if (ADC_DMA1_ISR_CH00_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH00_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH00_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH00_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH00_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_0] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_16], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_16]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH00_API == STD_ON) */

#if (ADC_DMA1_ISR_CH01_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH01_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH01_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH01_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH01_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_1] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_17], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_17]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH01_API == STD_ON) */

#if (ADC_DMA1_ISR_CH02_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH02_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH02_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH02_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH02_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_2] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_18], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_18]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH02_API == STD_ON) */

#if (ADC_DMA1_ISR_CH03_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH03_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH03_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH03_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH03_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_3] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_19], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_19]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH03_API == STD_ON) */

#if (ADC_DMA1_ISR_CH04_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH04_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH04_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH04_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH04_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_4] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_20], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_20]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH04_API == STD_ON) */

#if (ADC_DMA1_ISR_CH05_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH05_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH05_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH05_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH05_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_5] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_21], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_21]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH05_API == STD_ON) */

#if (ADC_DMA1_ISR_CH06_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH06_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH06_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH06_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH06_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_6] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_22], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_22]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH06_API == STD_ON) */

#if (ADC_DMA1_ISR_CH07_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH07_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH07_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH07_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH07_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_7] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_23], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_23]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH07_API == STD_ON) */

#if (ADC_DMA1_ISR_CH08_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH08_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH08_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH08_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH08_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_8] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_24], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_24]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH08_API == STD_ON) */

#if (ADC_DMA1_ISR_CH09_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH09_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH09_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH09_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH09_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_9] & ADC_EIC_EIMK))                               /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_25], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_25]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH09_API == STD_ON) */

#if (ADC_DMA1_ISR_CH10_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH10_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH10_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH10_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH10_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_10] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_26], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_26]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH10_API == STD_ON) */

#if (ADC_DMA1_ISR_CH11_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH11_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH11_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH11_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH11_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_11] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_27], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_27]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH11_API == STD_ON) */

#if (ADC_DMA1_ISR_CH12_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH12_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH12_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH12_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH12_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_12] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_28], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_28]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH12_API == STD_ON) */

#if (ADC_DMA1_ISR_CH13_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH13_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH13_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH13_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH13_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_13] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_29], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_29]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH13_API == STD_ON) */

#if (ADC_DMA1_ISR_CH14_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH14_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH14_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH14_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH14_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_14] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_30], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_30]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH14_API == STD_ON) */

#if (ADC_DMA1_ISR_CH15_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_DMA1_CH15_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_DMA1_CH15_CAT2_ISR)                                                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_DMA1_CH15_ISR(void)                                                           /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_DMA1_CH15_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Check whether the EIMK bit of EIC is set */
  if (ADC_EIC_EIMK == (uint8)((ADC_EIC_DMA1_BASEADDR)[ADC_DMA_CHANNEL_15] & ADC_EIC_EIMK))                              /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_DmaIsr(Adc_GpDmaHWUnitMapping[ADC_DMA_CHANNEL_31], Adc_GpDmaSGUnitMapping[ADC_DMA_CHANNEL_31]);                 /* PRQA S 2824 # JV-01 */
  }
}
#endif /* (ADC_DMA1_ISR_CH15_API == STD_ON) */

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : ADC_PARITY_ERR_ISR
**
** Service ID           : NA
**
** Description          : These are Interrupt Service routines for the ADC
**                        parity error.
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
** Global Variables     : None
**
** Functions invoked    : Adc_ParityErrIsr, ADC_DEM_REPORT_ERROR
**
** Registers Used       : EIC, ECMINCFGi_j, ECMISCFGj, ECMMESSTRj, ECMMICFGn
**
** Reference ID         : ADC_DUD_ACT_019, ADC_DUD_ACT_019_ERR001
***********************************************************************************************************************/
#if (ADC_ENABLE_PARITY_ERR_INT == STD_ON)

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Defines the CAT2 interrupt mapping */
#if defined (Os_ADC_PARITY_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON)
ISR(ADC_PARITY_ERR_CAT2_ISR)                                                                                            /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, ADC_CODE_FAST) ADC_PARITY_ERR_ISR(void)                                                          /* PRQA S 1503 # JV-01 */
#endif /* defined (Os_ADC_PARITY_ERR_CAT2_ISR) || (ADC_ISR_CATEGORY_2 == STD_ON) */
{
  #if (ADC_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  if ((ADC_EIC_EIMK == (uint8)(*((volatile uint8*)ADC_ECM_EIC8) & ADC_EIC_EIMK)) ||                                     /* PRQA S 0303 # JV-01 */
  #if (ADC_IP_ADCH == STD_ON)
      (ADC_DWORD_ZERO == (ADC_ECMMICFG_REG & ADC_ECM_CFG_ADC_PARITY_ERR)) ||
  #else
      (ADC_DWORD_ZERO == (ADC_ECMINCFG_REG & ADC_ECM_CFG_ADC_PARITY_ERR)) ||                                            /* PRQA S 0303 # JV-01 */
      (ADC_ECM_CFG_ADC_PARITY_ERR == (ADC_ECMISCFG_REG & ADC_ECM_CFG_ADC_PARITY_ERR)) ||                                /* PRQA S 0303 # JV-01 */
  #endif /* (ADC_IP_ADCH == STD_ON) */
      (ADC_DWORD_ZERO == (ADC_ECMMESSTR_REG & ADC_ECM_CFG_ADC_PARITY_ERR)))                                             /* PRQA S 0303 # JV-01 */
  {
    /* Reporting to DEM that interrupt from unknown source */
    ADC_DEM_REPORT_ERROR(ADC_E_ECM_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (ADC_ECM_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  {
    Adc_ParityErrIsr();
  }
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_PARITY_ERR_INT == STD_ON) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
