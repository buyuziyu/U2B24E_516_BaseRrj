/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_sDMAC_Irq.c                                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the ISR implementations for DMA                                                                 */
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
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 *                     : Remove QAC messages (2:3214) to fix redundant QAC messages
 *                     : Remove QAC message 2824, 2814 and fix QAC messages for U2Bx device
 *                     : Increase SW-VERSION up to 2.0.3
 *                     : Remove QAC message 1534
 *                     : Update QAC message 1534 support Amendment 2
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  23/10/2023  : Add message 1534, 3416, 3415, 0404 support Amendment 2.
 *                       Update SW-VERSION to 2.0.1
 * 2.0.0:  25/07/2023  : Update from "Spi_Mapping.h to "Spi_MemMap.h".
 * 1.4.4:  20/06/2022  : Update QAC message
 * 1.3.2:  04/09/2021  : Replace the inclusion of Spi_MemMap.h with Spi_Mapping.h
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 *         19/05/2021  : Update QAC contents.
 * 1.2.0:  30/07/2020  : Release
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.2:  22/05/2020  : Update QAC message and MISRA-C Rule violation.
 * 1.0.1:  18/04/2020  : Correct Unit macro index of SPI_DMA_ISR_TEMPLATE
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Spi.h"
#include "Spi_Ram.h"
#include "Spi_Irq.h"
#include "Spi_sDMAC_Irq.h"
#include "Dem.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define SPI_SDMAC_IRQ_C_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION_VALUE
#define SPI_SDMAC_IRQ_C_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION_VALUE
#define SPI_SDMAC_IRQ_C_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define SPI_SDMAC_IRQ_C_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION_VALUE
#define SPI_SDMAC_IRQ_C_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (SPI_SDMAC_IRQ_AR_RELEASE_MAJOR_VERSION != SPI_SDMAC_IRQ_C_AR_RELEASE_MAJOR_VERSION)
#error "Spi_sDMAC_Irq.c : Mismatch in Release Major Version"
#endif

#if (SPI_SDMAC_IRQ_AR_RELEASE_MINOR_VERSION != SPI_SDMAC_IRQ_C_AR_RELEASE_MINOR_VERSION)
#error "Spi_sDMAC_Irq.c : Mismatch in Release Minor Version"
#endif

#if (SPI_SDMAC_IRQ_AR_RELEASE_REVISION_VERSION != SPI_SDMAC_IRQ_C_AR_RELEASE_REVISION_VERSION)
#error "Spi_sDMAC_Irq.c : Mismatch in Release Revision Version"
#endif

#if (SPI_SDMAC_IRQ_SW_MAJOR_VERSION != SPI_SDMAC_IRQ_C_SW_MAJOR_VERSION)
#error "Spi_sDMAC_Irq.c : Mismatch in Software Major Version"
#endif

#if (SPI_SDMAC_IRQ_SW_MINOR_VERSION != SPI_SDMAC_IRQ_C_SW_MINOR_VERSION)
#error "Spi_sDMAC_Irq.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0857)    : Number of macro definitions exceeds 1024 - program does not conform strictly to ISO:C90.     */
/* Rule                : MISRA C:2012 Dir-1.1                                                                         */
/* JV-01 Justification : The number of macro depend on module code size. There is no issue when number of macro is    */
/*                       over 1024                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there. It not affect   */
/*                       to driver operation and can be accepted                                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : '%s' has external linkage and is being defined without any previous declaration.             */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there. (Other uses of  */
/*                       the macro may not necessarily be suitable for replacement.)                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with possible side effects.              */
/* Rule                : CERTCCM EXP02, MISRA C:2012 Rule-13.5, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it is not a direct access to the HW register, and          */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : CERTCCM EXP10, EXP30, MISRA C:2012 Rule-1.3, Rule-13.2, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get element in array of struct, volatile of counter variable of 'for' loop is     */
/*                       used to ensure no optimization. It is accepted                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
/* Code snippet to perform interrupt consistency checking */
#if (SPI_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
#define SPI_DMA_INT_ASSERTION(index) \
  if ((0U != (*Spi_GpFirstDMAUnit[Spi_GpConfigPtr->pDMAToHWUnit[(index)]].pICDma & SPI_EIC_EIMK_MASK)) ||   \
      (0U == (*Spi_GpFirstDMAUnit[Spi_GpConfigPtr->pDMAToHWUnit[(index)]].pICDma & SPI_EIC_EIRF_MASK)) ||   \
      (0U == (Spi_GpFirstDMAUnit[Spi_GpConfigPtr->pDMAToHWUnit[(index)]].pDmaRegs->usCHCR & SPI_DMA_IE)) || \
      (0UL == (Spi_GpFirstDMAUnit[Spi_GpConfigPtr->pDMAToHWUnit[(index)]].pDmaRegs->ulCHSTA & SPI_DMA_TE))) \
  {                                                                                                         \
    SPI_DEM_REPORT_ERROR(SPI_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);                                  \
  }                                                                                                         \
  else

#else
#define SPI_DMA_INT_ASSERTION(index)
#endif

/* All functions in this file have same attribute */
#define SPI_START_SEC_CODE_FAST
#include "Spi_MemMap.h"

/***********************************************************************************************************************
** Function Name     : SPI_DMAj_nn_ISR
**
** Service ID        : Not Applicable
**
** Description       : Interrupt Service Routine for DMA0 interrupt
**
** Sync/Async        : Synchronous
**
** Reentrancy        : Non-Reentrant
**
** Input Parameters  : None
**
** InOut Parameters  : None
**
** Output Parameters : None
**
** Return Value      : void
**
** Pre-condition     : Not Applicable
**
** Global Variable   : Spi_GpConfigPtr
**
** Function invoked  : Spi_CSIXDMACompleteISR or Spi_MSPIDMACompleteISR, SPI_DEM_REPORT_ERROR
**
** Registers Used    : None
**
** Reference ID      : SPI_DUD_ACT_021, SPI_DUD_ACT_021_ERR001, SPI_DUD_ACT_021_GBL001
***********************************************************************************************************************/
#define SPI_DMA_ISR_TEMPLATE(phyidx)                                                                                    /* PRQA S 3472 # JV-01 */ \
  do                                                                        \
  {                                                                         \
    uint32 LulHWUnitIndex;                                                  \
    uint32 LulIndex;                                                        \
    uint32 LulDMAindex;                                                     \
    SPI_DMA_INT_ASSERTION(phyidx)                                           \
    {                                                                       \
      LulDMAindex = Spi_GpConfigPtr->pDMAToHWUnit[phyidx];                  \
      LulHWUnitIndex = (uint32)Spi_GpFirstDMAUnit[LulDMAindex].ucSPIHWUnit; \
      LulIndex = (uint32)Spi_GpFirstHWUnit[LulHWUnitIndex].ucMacroIndex;    \
      Spi_GpHwConfig[LulIndex].pHwDepFunc->pHwDMACompleteISR(LulDMAindex);  \
    }                                                                       \
  } while (0)

/* CH0_00 *************************************************************************************************************/
#if (SPI_DMA0_00_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_00_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_00_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_00_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_00);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_00_ISR_API == STD_ON) */

/* CH0_01 *************************************************************************************************************/
#if (SPI_DMA0_01_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_01_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_01_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_01_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_01);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_01_ISR_API == STD_ON) */

/* CH0_02 *************************************************************************************************************/
#if (SPI_DMA0_02_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_02_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_02_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_02_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_02);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_02_ISR_API == STD_ON) */

/* CH0_03 *************************************************************************************************************/
#if (SPI_DMA0_03_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_03_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_03_CAT2_ISR)                                                                                               /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_03_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_03);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_03_ISR_API == STD_ON) */

/* CH0_04 *************************************************************************************************************/
#if (SPI_DMA0_04_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_04_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_04_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_04_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_04);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_04_ISR_API == STD_ON) */

/* CH0_05 *************************************************************************************************************/
#if (SPI_DMA0_05_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_05_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_05_CAT2_ISR)                                                                                               /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_05_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_05);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_05_ISR_API == STD_ON) */

/* CH0_06 *************************************************************************************************************/
#if (SPI_DMA0_06_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_06_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_06_CAT2_ISR)                                                                                               /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_06_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_06);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_06_ISR_API == STD_ON) */

/* CH0_07 *************************************************************************************************************/
#if (SPI_DMA0_07_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_07_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_07_CAT2_ISR)                                                                                               /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_07_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_07);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_07_ISR_API == STD_ON) */

/* CH0_08 *************************************************************************************************************/
#if (SPI_DMA0_08_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_08_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_08_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_08_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_08);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_08_ISR_API == STD_ON) */

/* CH0_09 *************************************************************************************************************/
#if (SPI_DMA0_09_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_09_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_09_CAT2_ISR)                                                                                               /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_09_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_09);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_09_ISR_API == STD_ON) */

/* CH0_10 *************************************************************************************************************/
#if (SPI_DMA0_10_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_10_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_10_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_10_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_10);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_10_ISR_API == STD_ON) */

/* CH0_11 *************************************************************************************************************/
#if (SPI_DMA0_11_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_11_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_11_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_11_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_11);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_11_ISR_API == STD_ON) */

/* CH0_12 *************************************************************************************************************/
#if (SPI_DMA0_12_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_12_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_12_CAT2_ISR)                                                                                               /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_12_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_12);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_12_ISR_API == STD_ON) */

/* CH0_13 *************************************************************************************************************/
#if (SPI_DMA0_13_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_13_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_13_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_13_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_13);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_13_ISR_API == STD_ON) */

/* CH0_14 *************************************************************************************************************/
#if (SPI_DMA0_14_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_14_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_14_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_14_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_14);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_14_ISR_API == STD_ON) */

/* CH0_15 *************************************************************************************************************/
#if (SPI_DMA0_15_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA0_15_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA0_15_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA0_15_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA0_15);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA0_15_ISR_API == STD_ON) */

/* CH1_00 *************************************************************************************************************/
#if (SPI_DMA1_00_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_00_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_00_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_00_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_00);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_00_ISR_API == STD_ON) */

/* CH1_01 *************************************************************************************************************/
#if (SPI_DMA1_01_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_01_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_01_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_01_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_01);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_01_ISR_API == STD_ON) */

/* CH1_02 *************************************************************************************************************/
#if (SPI_DMA1_02_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_02_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_02_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_02_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_02);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_02_ISR_API == STD_ON) */

/* CH1_03 *************************************************************************************************************/
#if (SPI_DMA1_03_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_03_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_03_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_03_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_03);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_03_ISR_API == STD_ON) */

/* CH1_04 *************************************************************************************************************/
#if (SPI_DMA1_04_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_04_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_04_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_04_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_04);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_04_ISR_API == STD_ON) */

/* CH1_05 *************************************************************************************************************/
#if (SPI_DMA1_05_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_05_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_05_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_05_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_05);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_05_ISR_API == STD_ON) */

/* CH1_06 *************************************************************************************************************/
#if (SPI_DMA1_06_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_06_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_06_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_06_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_06);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_06_ISR_API == STD_ON) */

/* CH1_07 *************************************************************************************************************/
#if (SPI_DMA1_07_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_07_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_07_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_07_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_07);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_07_ISR_API == STD_ON) */

/* CH1_08 *************************************************************************************************************/
#if (SPI_DMA1_08_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_08_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_08_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_08_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_08);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_08_ISR_API == STD_ON) */

/* CH1_09 *************************************************************************************************************/
#if (SPI_DMA1_09_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_09_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_09_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_09_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_09);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_09_ISR_API == STD_ON) */

/* CH1_10 *************************************************************************************************************/
#if (SPI_DMA1_10_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_10_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_10_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_10_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_10);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_10_ISR_API == STD_ON) */

/* CH1_11 *************************************************************************************************************/
#if (SPI_DMA1_11_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_11_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_11_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_11_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_11);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_11_ISR_API == STD_ON) */

/* CH1_12 *************************************************************************************************************/
#if (SPI_DMA1_12_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_12_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_12_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_12_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_12);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_12_ISR_API == STD_ON) */

/* CH1_13 *************************************************************************************************************/
#if (SPI_DMA1_13_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_13_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_13_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_13_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_13);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_13_ISR_API == STD_ON) */

/* CH1_14 *************************************************************************************************************/
#if (SPI_DMA1_14_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_14_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_14_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_14_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_14);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_14_ISR_API == STD_ON) */

/* CH1_15 *************************************************************************************************************/
#if (SPI_DMA1_15_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_DMA1_15_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_DMA1_15_CAT2_ISR)                                                                                               /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */                                                                                
#else                                                                                                                   
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_DMA1_15_ISR(void)                                                             /* PRQA S 1503 # JV-01 */
#endif                                                                                                                  
{                                                                                                                       
  SPI_DMA_ISR_TEMPLATE(SPI_PHYIDX_DMA1_15);                                                                             /* PRQA S 3469, 3416, 3415, 0404 # JV-01, JV-01, JV-01, JV-01 */
}
#endif /* End of (SPI_DMA1_15_ISR_API == STD_ON) */

#define SPI_STOP_SEC_CODE_FAST
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
