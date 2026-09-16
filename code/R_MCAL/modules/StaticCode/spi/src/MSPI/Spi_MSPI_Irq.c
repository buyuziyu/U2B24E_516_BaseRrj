/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_MSPI_Irq.c                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the ISR implementations for SPI(MSPI)                                                           */
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
 *                     : Update functions: Spi_SelRxIsr, Spi_SelTxIsr, Spi_SelFeIsr to correct for checking 
 *                       the interrupt status register
 *                     : Remove QAC messages (2:0857), (2:3214), (2:2814), (2:2824) to fix redundant QAC messages
 *                     : Add new QAC message (3:3416)
 *                     : Change SPI_MAX_HWUNIT to Spi_GpConfigPtr->ucNoOfHWUnits in function Spi_SelFeIsr,
                         Spi_SelTxIsr, Spi_SelRxIsr
                       : Change the name of LucHwUnitIdx/LucHwUnitInfor variables to LulHwUnitIdx/LulHwUnitInfor in
                          Spi_SelRxIsr, Spi_SelTxIsr and Spi_SelFeIsr internal function.
                       : Change data type of LulHwUnitInfor variable from uint8 to uint32.
 *                     : Add Spi_SelTxIsr, Spi_SelRxIsr, Spi_SelFeIsr, SPI_MSPI_ORED0_FE_ISR, SPI_MSPI_ORED1_FE_ISR, 
 *                       SPI_MSPI_ORED2_FE_ISR, SPI_MSPI_ORED3_FE_ISR, SPI_MSPI_ORED0_TX_ISR, SPI_MSPI_ORED1_TX_ISR, 
 *                       SPI_MSPI_ORED2_TX_ISR, SPI_MSPI_ORED3_TX_ISR, SPI_MSPI_ORED0_RX_ISR, SPI_MSPI_ORED1_RX_ISR, 
 *                       SPI_MSPI_ORED2_RX_ISR, SPI_MSPI_ORED3_RX_ISR to support ORed Interrupt function
 *                       Remove QAC message 1534
 *                     : Update QAC message 1534 support Amendment 2
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  22/10/2023  : Update QAC message 1534 support Amendment 2
 *                       Update SW-VERSION to 2.0.1
 * 2.0.0:  25/07/2023  : Update from "Spi_Mapping.h to "Spi_MemMap.h".
 * 1.3.2:  04/09/2021  : Replace the inclusion of Spi_MemMap.h with Spi_Mapping.h
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 *         19/05/2021  : Update QAC contents.
 * 1.2.0:  30/07/2020  : Release
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Spi.h"
#include "Spi_Ram.h"
#include "Spi_Irq.h"
#include "Spi_MSPI_Irq.h"
#include "Spi_MSPI_LLDriver.h"
#include "Dem.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define SPI_MSPI_IRQ_C_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION_VALUE
#define SPI_MSPI_IRQ_C_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION_VALUE
#define SPI_MSPI_IRQ_C_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define SPI_MSPI_IRQ_C_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION_VALUE
#define SPI_MSPI_IRQ_C_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (SPI_MSPI_IRQ_AR_RELEASE_MAJOR_VERSION != SPI_MSPI_IRQ_C_AR_RELEASE_MAJOR_VERSION)
#error "Spi_MSPI_Irq.c : Mismatch in Release Major Version"
#endif

#if (SPI_MSPI_IRQ_AR_RELEASE_MINOR_VERSION != SPI_MSPI_IRQ_C_AR_RELEASE_MINOR_VERSION)
#error "Spi_MSPI_Irq.c : Mismatch in Release Minor Version"
#endif

#if (SPI_MSPI_IRQ_AR_RELEASE_REVISION_VERSION != SPI_MSPI_IRQ_C_AR_RELEASE_REVISION_VERSION)
#error "Spi_MSPI_Irq.c : Mismatch in Release Revision Version"
#endif

#if (SPI_MSPI_IRQ_SW_MAJOR_VERSION != SPI_MSPI_IRQ_C_SW_MAJOR_VERSION)
#error "Spi_MSPI_Irq.c : Mismatch in Software Major Version"
#endif

#if (SPI_MSPI_IRQ_SW_MINOR_VERSION != SPI_MSPI_IRQ_C_SW_MINOR_VERSION)
#error "Spi_MSPI_Irq.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : CERTCCM PRE05, MISRA C:2012 Rule-20.10                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
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

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define SPI_START_SEC_CODE_FAST
#include "Spi_MemMap.h"

#if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)

#if (SPI_MSPI_ORED0_TX_ISR_API == STD_ON) || (SPI_MSPI_ORED1_TX_ISR_API == STD_ON) || \
                                        (SPI_MSPI_ORED2_TX_ISR_API == STD_ON) || (SPI_MSPI_ORED3_TX_ISR_API == STD_ON)
STATIC FUNC(void, SPI_CODE_FAST) Spi_SelTxIsr(const uint8 LucInterruptSelId);
#endif /*(SPI_MSPI_ORED0_TX_ISR_API == STD_ON) || (SPI_MSPI_ORED1_TX_ISR_API == STD_ON) || \
                                        (SPI_MSPI_ORED2_TX_ISR_API == STD_ON) || (SPI_MSPI_ORED3_TX_ISR_API == STD_ON)*/

#if (SPI_MSPI_ORED0_RX_ISR_API == STD_ON) || (SPI_MSPI_ORED1_RX_ISR_API == STD_ON) || \
                                        (SPI_MSPI_ORED2_RX_ISR_API == STD_ON) || (SPI_MSPI_ORED3_RX_ISR_API == STD_ON)
STATIC FUNC(void, SPI_CODE_FAST) Spi_SelRxIsr(const uint8 LucInterruptSelId);
#endif /*(SPI_MSPI_ORED0_RX_ISR_API == STD_ON) || (SPI_MSPI_ORED1_RX_ISR_API == STD_ON) || \
                                        (SPI_MSPI_ORED2_RX_ISR_API == STD_ON) || (SPI_MSPI_ORED3_RX_ISR_API == STD_ON)*/

#if (SPI_MSPI_ORED0_FE_ISR_API == STD_ON) || (SPI_MSPI_ORED1_FE_ISR_API == STD_ON) || \
                                        (SPI_MSPI_ORED2_FE_ISR_API == STD_ON) || (SPI_MSPI_ORED3_FE_ISR_API == STD_ON)
STATIC FUNC(void, SPI_CODE_FAST) Spi_SelFeIsr(const uint8 LucInterruptSelId);
#endif /*(SPI_MSPI_ORED0_FE_ISR_API == STD_ON) || (SPI_MSPI_ORED1_FE_ISR_API == STD_ON) || \
                                        (SPI_MSPI_ORED2_FE_ISR_API == STD_ON) || (SPI_MSPI_ORED3_FE_ISR_API == STD_ON)*/

#endif/*(SPI_ORED_INTERRUPT_FUNCTION == STD_ON)*/
#define SPI_STOP_SEC_CODE_FAST
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Code snipet to perform interrupt consistency checking */
#if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
#if (SPI_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
#define SPI_MSPI_INT_ASSERTION(index, intname)                             \
  if (0U != (*Spi_GaaMSPIRegs[(index)].pIC##intname & SPI_EIC_EIMK_MASK))                                               /* PRQA S 0342 # JV-01 */ \
  {                                                                        \
    SPI_DEM_REPORT_ERROR(SPI_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED); \
  }                                                                        \
  else
#else
#define SPI_MSPI_INT_ASSERTION(index, intname)
#endif
#else
#if (SPI_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
#define SPI_MSPI_INT_ASSERTION(index, intname)                             \
  if (0U != (*Spi_GaaMSPIOredISRRegs[(index)].pIC##intname & SPI_EIC_EIMK_MASK))                                        /* PRQA S 0342 # JV-01 */ \
  {                                                                        \
    SPI_DEM_REPORT_ERROR(SPI_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED); \
  }                                                                        \
  else
#else
#define SPI_MSPI_INT_ASSERTION(index, intname)
#endif
#endif

/* All functions in this file have same attribute */
#define SPI_START_SEC_CODE_FAST
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : SPI_MSPI_OREDn_TX_ISR
**
** Service ID            : Not Applicable
**
** Description           : This is TX Interrupt Selection Service routines for the MSPI
**                         hardware unit.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Spi_SelTxIsr, SPI_DEM_REPORT_ERROR
**
** Registers Used        : None
**
** Reference ID          : SPI_DUD_ACT_108, SPI_DUD_ACT_108_ERR001
***********************************************************************************************************************/
/* ORED0 **************************************************************************************************************/
#if (SPI_MSPI_ORED0_TX_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_MSPI_ORED0_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI_ORED0_TX_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI_ORED0_TX_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI_ORED0, TX)
  {
      Spi_SelTxIsr(SPI_PHYIDX_MSPI_ORED0);
  }
}
#endif /* End of (SPI_MSPI_ORED0_TX_ISR_API == STD_ON) */
/* ORED1 **************************************************************************************************************/
#if (SPI_MSPI_ORED1_TX_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_MSPI_ORED1_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI_ORED1_TX_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI_ORED1_TX_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
 SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI_ORED1, TX)
 {
      Spi_SelTxIsr(SPI_PHYIDX_MSPI_ORED1);
  }
}
#endif /* End of (SPI_MSPI_ORED1_TX_ISR_API == STD_ON) */
/* ORED2 **************************************************************************************************************/
#if (SPI_MSPI_ORED2_TX_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_MSPI_ORED2_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI_ORED2_TX_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI_ORED2_TX_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI_ORED2, TX)
  {
      Spi_SelTxIsr(SPI_PHYIDX_MSPI_ORED2);
  }
}
#endif /* End of (SPI_MSPI_ORED2_TX_ISR_API == STD_ON) */
/* ORED3 **************************************************************************************************************/
#if (SPI_MSPI_ORED3_TX_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_MSPI_ORED3_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI_ORED3_TX_CAT2_ISR)                                                                                         /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI_ORED3_TX_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI_ORED3, TX)
  {
      Spi_SelTxIsr(SPI_PHYIDX_MSPI_ORED3);
  }
}
#endif /* End of (SPI_MSPI_ORED3_TX_ISR_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : SPI_MSPI_OREDn_RX_ISR
**
** Service ID            : Not Applicable
**
** Description           : This is RX Interrupt Selection Service routines for the MSPI
**                         hardware unit.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Spi_SelRxIsr, SPI_DEM_REPORT_ERROR
**
** Registers Used        : None
**
** Reference ID          : SPI_DUD_ACT_109, SPI_DUD_ACT_109_ERR001
***********************************************************************************************************************/
/* ORED0 **************************************************************************************************************/
#if (SPI_MSPI_ORED0_RX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI_ORED0_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI_ORED0_RX_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI_ORED0_RX_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI_ORED0, RX)
  {
      Spi_SelRxIsr(SPI_PHYIDX_MSPI_ORED0);
  }
}
#endif /* End of (SPI_MSPI_ORED0_RX_ISR_API == STD_ON) */
/* ORED1 **************************************************************************************************************/
#if (SPI_MSPI_ORED1_RX_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_MSPI_ORED1_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI_ORED1_RX_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI_ORED1_RX_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
 SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI_ORED1, RX)
 {
      Spi_SelRxIsr(SPI_PHYIDX_MSPI_ORED1);
 }
}
#endif /* End of (SPI_MSPI_ORED1_RX_ISR_API == STD_ON) */
/* ORED2 **************************************************************************************************************/
#if (SPI_MSPI_ORED2_RX_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_MSPI_ORED2_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI_ORED2_RX_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI_ORED2_RX_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI_ORED2, RX)
  {
      Spi_SelRxIsr(SPI_PHYIDX_MSPI_ORED2);
  }
}
#endif /* End of (SPI_MSPI_ORED2_RX_ISR_API == STD_ON) */
/* ORED3 **************************************************************************************************************/
#if (SPI_MSPI_ORED3_RX_ISR_API == STD_ON)
/* Defines the CAT2 interrupt mapping */
#if defined(Os_SPI_MSPI_ORED3_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI_ORED3_RX_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI_ORED3_RX_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI_ORED3, RX)
  {
      Spi_SelRxIsr(SPI_PHYIDX_MSPI_ORED3);
  }
}
#endif /* End of (SPI_MSPI_ORED3_RX_ISR_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : SPI_MSPI_OREDn_FE_ISR
**
** Service ID            : Not Applicable
**
** Description           : This is FE Interrupt Selection Service routines for the MSPI
**                         hardware unit.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Spi_SelFeIsr, SPI_DEM_REPORT_ERROR
**
** Registers Used        : None
**
** Reference ID          : SPI_DUD_ACT_110, SPI_DUD_ACT_110_ERR001
***********************************************************************************************************************/
/* ORED0 **************************************************************************************************************/
#if (SPI_MSPI_ORED0_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI_ORED0_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI_ORED0_FE_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI_ORED0_FE_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
 SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI_ORED0, FE)
 {
      Spi_SelFeIsr(SPI_PHYIDX_MSPI_ORED0);
 }
}
#endif /* End of (SPI_MSPI_ORED0_FE_ISR_API == STD_ON) */
/* ORED1 **************************************************************************************************************/
#if (SPI_MSPI_ORED1_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI_ORED1_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI_ORED1_FE_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI_ORED1_FE_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI_ORED1, FE)
  {
      Spi_SelFeIsr(SPI_PHYIDX_MSPI_ORED1);
  }
}
#endif /* End of (SPI_MSPI_ORED1_FE_ISR_API == STD_ON) */
/* ORED2 **************************************************************************************************************/
#if (SPI_MSPI_ORED2_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI_ORED2_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI_ORED2_FE_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI_ORED2_FE_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI_ORED2, FE)
  {
      Spi_SelFeIsr(SPI_PHYIDX_MSPI_ORED2);
  }
}
#endif /* End of (SPI_MSPI_ORED2_FE_ISR_API == STD_ON) */
/* ORED3 **************************************************************************************************************/
#if (SPI_MSPI_ORED3_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI_ORED3_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI_ORED3_FE_CAT2_ISR)                                                                                         /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI_ORED3_FE_ISR(void)                                                       /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI_ORED3, FE)
  {
      Spi_SelFeIsr(SPI_PHYIDX_MSPI_ORED3);
  }
}
#endif /* End of (SPI_MSPI_ORED3_FE_ISR_API == STD_ON) */

/***********************************************************************************************************************
** Function Name     : SPI_MSPIn_TX_ISR
**
** Service ID        : Not Applicable
**
** Description       : Interrupt Service Routine for MSPI transmit interrupt
**
** Sync/Async        : Synchronous
**
** Re-entrancy       : Non-Reentrant
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
** Global Variable   : None
**
** Function invoked  : Spi_MSPITransmitISR, SPI_DEM_REPORT_ERROR
**
** Registers Used    : None
**
** Reference ID      : SPI_DUD_ACT_025, SPI_DUD_ACT_025_ERR001
***********************************************************************************************************************/
/* CH0 ****************************************************************************************************************/
#if (SPI_MSPI0_TX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI0_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI0_TX_CAT2_ISR)                                                                                              /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI0_TX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI0, TX)
  {
    Spi_MSPITransmitISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI0]);
  }
}
#endif /* End of (SPI_MSPI0_TX_ISR_API == STD_ON) */

/* CH1 ****************************************************************************************************************/
#if (SPI_MSPI1_TX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI1_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI1_TX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI1_TX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI1, TX)
  {
    Spi_MSPITransmitISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI1]);
  }
}
#endif /* End of (SPI_MSPI1_TX_ISR_API == STD_ON) */

/* CH2 ****************************************************************************************************************/
#if (SPI_MSPI2_TX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI2_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI2_TX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI2_TX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI2, TX)
  {
    Spi_MSPITransmitISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI2]);
  }
}
#endif /* End of (SPI_MSPI2_TX_ISR_API == STD_ON) */

/* CH3 ****************************************************************************************************************/
#if (SPI_MSPI3_TX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI3_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI3_TX_CAT2_ISR)                                                                                              /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI3_TX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI3, TX)
  {
    Spi_MSPITransmitISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI3]);
  }
}
#endif /* End of (SPI_MSPI3_TX_ISR_API == STD_ON) */

/* CH4 ****************************************************************************************************************/
#if (SPI_MSPI4_TX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI4_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI4_TX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI4_TX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI4, TX)
  {
    Spi_MSPITransmitISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI4]);
  }
}
#endif /* End of (SPI_MSPI4_TX_ISR_API == STD_ON) */

/* CH5 ****************************************************************************************************************/
#if (SPI_MSPI5_TX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI5_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI5_TX_CAT2_ISR)                                                                                              /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI5_TX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI5, TX)
  {
    Spi_MSPITransmitISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI5]);
  }
}
#endif /* End of (SPI_MSPI5_TX_ISR_API == STD_ON) */

/* CH6 ****************************************************************************************************************/
#if (SPI_MSPI6_TX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI6_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI6_TX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI6_TX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI6, TX)
  {
    Spi_MSPITransmitISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI6]);
  }
}
#endif /* End of (SPI_MSPI6_TX_ISR_API == STD_ON) */

/* CH7 ****************************************************************************************************************/
#if (SPI_MSPI7_TX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI7_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI7_TX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI7_TX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI7, TX)
  {
    Spi_MSPITransmitISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI7]);
  }
}
#endif /* End of (SPI_MSPI7_TX_ISR_API == STD_ON) */

/* CH8 ****************************************************************************************************************/
#if (SPI_MSPI8_TX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI8_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI8_TX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI8_TX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI8, TX)
  {
    Spi_MSPITransmitISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI8]);
  }
}
#endif /* End of (SPI_MSPI8_TX_ISR_API == STD_ON) */

/* CH9 ****************************************************************************************************************/
#if (SPI_MSPI9_TX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI9_TX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI9_TX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI9_TX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI9, TX)
  {
    Spi_MSPITransmitISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI9]);
  }
}
#endif /* End of (SPI_MSPI9_TX_ISR_API == STD_ON) */

/***********************************************************************************************************************
** Function Name     : SPI_MSPIn_RX_ISR
**
** Service ID        : Not Applicable
**
** Description       : Interrupt Service Routine for MSPI receive interrupt
**
** Sync/Async        : Synchronous
**
** Re-entrancy       : Non-Reentrant
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
** Global Variable   : None
**
** Function invoked  : Spi_MSPIReceiveISR, SPI_DEM_REPORT_ERROR
**
** Registers Used    : None
**
** Reference ID      : SPI_DUD_ACT_026, SPI_DUD_ACT_026_ERR001
***********************************************************************************************************************/
/* CH0 ****************************************************************************************************************/
#if (SPI_MSPI0_RX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI0_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI0_RX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI0_RX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI0, RX)
  {
    Spi_MSPIReceiveISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI0]);
  }
}
#endif /* End of (SPI_MSPI0_RX_ISR_API == STD_ON) */

/* CH1 ****************************************************************************************************************/
#if (SPI_MSPI1_RX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI1_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI1_RX_CAT2_ISR)                                                                                              /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI1_RX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI1, RX)
  {
    Spi_MSPIReceiveISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI1]);
  }
}
#endif /* End of (SPI_MSPI1_RX_ISR_API == STD_ON) */

/* CH2 ****************************************************************************************************************/
#if (SPI_MSPI2_RX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI2_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI2_RX_CAT2_ISR)                                                                                              /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI2_RX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI2, RX)
  {
    Spi_MSPIReceiveISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI2]);
  }
}
#endif /* End of (SPI_MSPI2_RX_ISR_API == STD_ON) */

/* CH3 ****************************************************************************************************************/
#if (SPI_MSPI3_RX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI3_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI3_RX_CAT2_ISR)                                                                                              /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI3_RX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI3, RX)
  {
    Spi_MSPIReceiveISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI3]);
  }
}
#endif /* End of (SPI_MSPI3_RX_ISR_API == STD_ON) */

/* CH4 ****************************************************************************************************************/
#if (SPI_MSPI4_RX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI4_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI4_RX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI4_RX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI4, RX)
  {
    Spi_MSPIReceiveISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI4]);
  }
}
#endif /* End of (SPI_MSPI4_RX_ISR_API == STD_ON) */

/* CH5 ****************************************************************************************************************/
#if (SPI_MSPI5_RX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI5_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI5_RX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI5_RX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI5, RX)
  {
    Spi_MSPIReceiveISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI5]);
  }
}
#endif /* End of (SPI_MSPI5_RX_ISR_API == STD_ON) */

/* CH6 ****************************************************************************************************************/
#if (SPI_MSPI6_RX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI6_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI6_RX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI6_RX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI6, RX)
  {
    Spi_MSPIReceiveISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI6]);
  }
}
#endif /* End of (SPI_MSPI6_RX_ISR_API == STD_ON) */

/* CH7 ****************************************************************************************************************/
#if (SPI_MSPI7_RX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI7_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI7_RX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI7_RX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI7, RX)
  {
    Spi_MSPIReceiveISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI7]); 
  }
}
#endif /* End of (SPI_MSPI7_RX_ISR_API == STD_ON) */

/* CH8 ****************************************************************************************************************/
#if (SPI_MSPI8_RX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI8_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI8_RX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI8_RX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI8, RX)
  {
    Spi_MSPIReceiveISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI8]); 
  }
}
#endif /* End of (SPI_MSPI8_RX_ISR_API == STD_ON) */

/* CH9 ****************************************************************************************************************/
#if (SPI_MSPI9_RX_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI9_RX_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI9_RX_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI9_RX_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI9, RX)
  {
    Spi_MSPIReceiveISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI9]); 
  }
}
#endif /* End of (SPI_MSPI9_RX_ISR_API == STD_ON) */

/***********************************************************************************************************************
** Function Name     : SPI_MSPIn_FE_ISR
**
** Service ID        : Not Applicable
**
** Description       : Interrupt Service Routine for MSPI frame count end interrupt
**
** Sync/Async        : Synchronous
**
** Re-entrancy       : Non-Reentrant
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
** Global Variable   : None
**
** Function invoked  : Spi_MSPIFrameEndISR, SPI_DEM_REPORT_ERROR
**
** Registers Used    : None
**
** Reference ID      : SPI_DUD_ACT_027, SPI_DUD_ACT_027_ERR001
***********************************************************************************************************************/
/* CH0 ****************************************************************************************************************/
#if (SPI_MSPI0_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI0_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI0_FE_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI0_FE_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI0, FE)
  {
    Spi_MSPIFrameEndISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI0]);
  }
}
#endif /* End of (SPI_MSPI0_FE_ISR_API == STD_ON) */

/* CH1 ****************************************************************************************************************/
#if (SPI_MSPI1_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI1_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI1_FE_CAT2_ISR)                                                                                              /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI1_FE_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI1, FE)
  {
    Spi_MSPIFrameEndISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI1]);
  }
}
#endif /* End of (SPI_MSPI1_FE_ISR_API == STD_ON) */

/* CH2 ****************************************************************************************************************/
#if (SPI_MSPI2_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI2_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI2_FE_CAT2_ISR)                                                                                              /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI2_FE_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI2, FE)
  {
    Spi_MSPIFrameEndISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI2]);
  }
}
#endif /* End of (SPI_MSPI2_FE_ISR_API == STD_ON) */

/* CH3 ****************************************************************************************************************/
#if (SPI_MSPI3_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI3_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI3_FE_CAT2_ISR)                                                                                              /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI3_FE_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI3, FE)
  {
    Spi_MSPIFrameEndISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI3]);
  }
}
#endif /* End of (SPI_MSPI3_FE_ISR_API == STD_ON) */

/* CH4 ****************************************************************************************************************/
#if (SPI_MSPI4_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI4_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI4_FE_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI4_FE_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI4, FE)
  {
    Spi_MSPIFrameEndISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI4]);
  }
}
#endif /* End of (SPI_MSPI4_FE_ISR_API == STD_ON) */

/* CH5 ****************************************************************************************************************/
#if (SPI_MSPI5_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI5_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI5_FE_CAT2_ISR)                                                                                              /* PRQA S 3408, 1503 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI5_FE_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI5, FE)
  {
    Spi_MSPIFrameEndISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI5]);
  }
}
#endif /* End of (SPI_MSPI5_FE_ISR_API == STD_ON) */

/* CH6 ****************************************************************************************************************/
#if (SPI_MSPI6_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI6_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI6_FE_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI6_FE_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI6, FE)
  {
    Spi_MSPIFrameEndISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI6]);
  }
}
#endif /* End of (SPI_MSPI6_FE_ISR_API == STD_ON) */

/* CH7 ****************************************************************************************************************/
#if (SPI_MSPI7_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI7_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI7_FE_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI7_FE_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI7, FE)
  {
    Spi_MSPIFrameEndISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI7]);
  }
}
#endif /* End of (SPI_MSPI7_FE_ISR_API == STD_ON) */

/* CH8 ****************************************************************************************************************/
#if (SPI_MSPI8_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI8_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI8_FE_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI8_FE_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI8, FE)
  {
    Spi_MSPIFrameEndISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI8]);
  }
}
#endif /* End of (SPI_MSPI8_FE_ISR_API == STD_ON) */

/* CH9 ****************************************************************************************************************/
#if (SPI_MSPI9_FE_ISR_API == STD_ON)
/* Defines the CAT2interrupt mapping */
#if defined(Os_SPI_MSPI9_FE_CAT2_ISR) || (SPI_ISR_CATEGORY_2 == STD_ON)
ISR(SPI_MSPI9_FE_CAT2_ISR)                                                                                              /* PRQA S 1503, 3408 # JV-01, JV-01 */
/* Defines the CAT1 interrupt mapping */
#else
_INTERRUPT_ FUNC(void, SPI_CODE_FAST) SPI_MSPI9_FE_ISR(void)                                                            /* PRQA S 1503 # JV-01 */
#endif
{
  SPI_MSPI_INT_ASSERTION(SPI_PHYIDX_MSPI9, FE)
  {
    Spi_MSPIFrameEndISR((uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[SPI_PHYIDX_MSPI9]);
  }
}
#endif /* End of (SPI_MSPI9_FE_ISR_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Spi_SelRxIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each RX ISR Selection
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucInterruptSelId : Physical number of interrupt selection
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Preconditions         : The availability of the index must be guaranteed
**                         by the upper layer.
**
** Preconditions         : None
**
** Global Variables Used : Spi_GaaMSPIOredISRRegs, Spi_GpHwConfig, Spi_GpConfigPtr, Spi_GpFirstHWUnit
**
** Functions Invoked     : Spi_MSPIReceiveISR
**
** Registers Used        : INTMSPICRSMONn
**
** Reference ID          : SPI_DUD_ACT_112
***********************************************************************************************************************/
/* ORed RX*************************************************************************************************************/
#if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
#if (SPI_MSPI_ORED0_RX_ISR_API == STD_ON) || (SPI_MSPI_ORED1_RX_ISR_API == STD_ON) || \
                                        (SPI_MSPI_ORED2_RX_ISR_API == STD_ON) || (SPI_MSPI_ORED3_RX_ISR_API == STD_ON)
STATIC FUNC(void, SPI_CODE_FAST) Spi_SelRxIsr(const uint8 LucInterruptSelId)
{
    VAR(uint32, AUTOMATIC) LulHwUnitInfor;
    VAR(uint32, AUTOMATIC) LulHwUnitIdx;
    VAR(uint16, AUTOMATIC) LusHWPhyIndex;
    for (LulHwUnitInfor = 0U; LulHwUnitInfor < Spi_GpConfigPtr->ucNoOfHWUnits; LulHwUnitInfor++)                        /* PRQA S 3416 # JV-01 */
    {
        /* Get the physical of hardware unit */
        LusHWPhyIndex = (uint16)Spi_GpFirstHWUnit[LulHwUnitInfor].ucPhyUnitIndex;
        if (1U == ((uint16)(*Spi_GaaMSPIOredISRRegs[LucInterruptSelId].pICRSMON >> (LusHWPhyIndex)) & 1U))
        {
          /* Get the index of HW Unit in CFG */
          LulHwUnitIdx = (uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[LusHWPhyIndex];

          Spi_MSPIReceiveISR(LulHwUnitIdx);
        } /* else No action required */
   }
}
#endif /*SPI_MSPI_ORED0_RX_ISR_API == STD_ON) || (SPI_MSPI_ORED1_RX_ISR_API == STD_ON) || \
                                        (SPI_MSPI_ORED2_RX_ISR_API == STD_ON) || (SPI_MSPI_ORED3_RX_ISR_API == STD_ON)*/
#endif /* (SPI_ORED_INTERRUPT_FUNCTION == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Spi_SelTxIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each TX ISR Selection
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucInterruptSelId : Physical number of interrupt selection
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Preconditions         : The availability of the index must be guaranteed
**                         by the upper layer.
**
** Preconditions         : None
**
** Global Variables Used : Spi_GaaMSPIOredISRRegs, Spi_GpHwConfig, Spi_GpConfigPtr, Spi_GpFirstHWUnit
**
** Functions Invoked     : Spi_MSPITransmitISR
**
** Registers Used        : INTMSPICTSMONn
**
** Reference ID          : SPI_DUD_ACT_111
***********************************************************************************************************************/
/* ORed TX*************************************************************************************************************/
#if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
#if (SPI_MSPI_ORED0_TX_ISR_API == STD_ON) || (SPI_MSPI_ORED1_TX_ISR_API == STD_ON) || \
                                        (SPI_MSPI_ORED2_TX_ISR_API == STD_ON) || (SPI_MSPI_ORED3_TX_ISR_API == STD_ON)
STATIC FUNC(void, SPI_CODE_FAST) Spi_SelTxIsr(const uint8 LucInterruptSelId)
{
    VAR(uint32, AUTOMATIC) LulHwUnitInfor;
    VAR(uint32, AUTOMATIC) LulHwUnitIdx;
    VAR(uint16, AUTOMATIC) LusHWPhyIndex;
    for (LulHwUnitInfor = 0U; LulHwUnitInfor < Spi_GpConfigPtr->ucNoOfHWUnits; LulHwUnitInfor++)                        /* PRQA S 3416 # JV-01 */
    {
        /* Get the physical of hardware unit */
        LusHWPhyIndex = (uint16)Spi_GpFirstHWUnit[LulHwUnitInfor].ucPhyUnitIndex;
        if (1U == ((uint16)(*Spi_GaaMSPIOredISRRegs[LucInterruptSelId].pICTSMON >> (LusHWPhyIndex)) & 1U))
        {
          /* Get the index of HW Unit in CFG */
          LulHwUnitIdx = (uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[LusHWPhyIndex];

          Spi_MSPITransmitISR(LulHwUnitIdx);
        } /* else No action required */
    }
}
#endif /* (SPI_MSPI_ORED0_TX_ISR_API == STD_ON) || (SPI_MSPI_ORED1_TX_ISR_API == STD_ON) || \
                                       (SPI_MSPI_ORED2_TX_ISR_API == STD_ON) || (SPI_MSPI_ORED3_TX_ISR_API == STD_ON) */
#endif /* (SPI_ORED_INTERRUPT_FUNCTION == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Spi_SelFeIsr
**
** Service ID            : Not Applicable
**
** Description           : Common part of each FE ISR Selection
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters      : LucInterruptSelId : Physical number of interrupt selection
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Preconditions         : The availability of the index must be guaranteed
**                         by the upper layer.
**
** Preconditions         : None
**
** Global Variables Used : Spi_GaaMSPIOredISRRegs, Spi_GpHwConfig, Spi_GpConfigPtr, Spi_GpFirstHWUnit
**
** Functions Invoked     : Spi_MSPIFrameEndISR
**
** Registers Used        : INTMSPICFCMONn
**
** Reference ID          : SPI_DUD_ACT_113
***********************************************************************************************************************/
/* ORed FE*************************************************************************************************************/
#if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
#if (SPI_MSPI_ORED0_FE_ISR_API == STD_ON) || (SPI_MSPI_ORED1_FE_ISR_API == STD_ON) || \
                                        (SPI_MSPI_ORED2_FE_ISR_API == STD_ON) || (SPI_MSPI_ORED3_FE_ISR_API == STD_ON)
STATIC FUNC(void, SPI_CODE_FAST) Spi_SelFeIsr(const uint8 LucInterruptSelId)
{
    VAR(uint32, AUTOMATIC) LulHwUnitInfor;
    VAR(uint32, AUTOMATIC) LulHwUnitIdx;
    VAR(uint16, AUTOMATIC) LusHWPhyIndex;
    for (LulHwUnitInfor = 0U; LulHwUnitInfor < Spi_GpConfigPtr->ucNoOfHWUnits; LulHwUnitInfor++)                        /* PRQA S 3416 # JV-01 */
    {
        /* Get the physical of hardware unit */
        LusHWPhyIndex = (uint16)Spi_GpFirstHWUnit[LulHwUnitInfor].ucPhyUnitIndex;
        if (1U == ((uint16)(*Spi_GaaMSPIOredISRRegs[LucInterruptSelId].pICFCMON >> (LusHWPhyIndex)) & 1U))
        {
          /* Get the index of HW Unit in CFG */
          LulHwUnitIdx = (uint32)Spi_GpHwConfig[SPI_MACRO_MSPI].pPhyToHWUnit[LusHWPhyIndex];

          Spi_MSPIFrameEndISR(LulHwUnitIdx);
        } /* else No action required */
    }
}
#endif /* (SPI_MSPI_ORED0_FE_ISR_API == STD_ON) || (SPI_MSPI_ORED1_FE_ISR_API == STD_ON) || \
                                       (SPI_MSPI_ORED2_FE_ISR_API == STD_ON) || (SPI_MSPI_ORED3_FE_ISR_API == STD_ON) */
#endif /* (SPI_ORED_INTERRUPT_FUNCTION == STD_ON) */

#define SPI_STOP_SEC_CODE_FAST
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
