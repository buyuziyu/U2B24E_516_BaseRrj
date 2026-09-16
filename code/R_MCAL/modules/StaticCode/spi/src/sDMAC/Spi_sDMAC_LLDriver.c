/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_sDMAC_LLDriver.c                                                                                */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Low level driver function definitions of the SPI Driver                                         */
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
 *                     : Remove QAC messages (2:0857), (1:1532), (2:2814), (2:2844), (2:2824) 
 *                       to fix redundant QAC messages
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  18/01/2024  : Add Dummy read & SYNCP in Spi_DMAStart
 *         12/01/2024  : Update SW-VERSION to 2.0.2
 * 2.0.1:  23/10/2023  : Update QAC message 3006, 0404 support Amendment 2
 *                       Update SW-VERSION to 2.0.1
 * 2.0.0:  03/08/2023  : Update QAC message 1006, 0791
 *         25/07/2023  : Update from "Spi_Mapping.h to "Spi_MemMap.h".
 *         20/06/2023  : Added SPI_LEVEL_DELIVERED == SPI_LEVEL_1 in function Spi_DMAStart
 * 1.5.0:  07/04/2023  : Update
 *                       Spi_DMAInit: Remove Spi_GaaCSIHRegs, Spi_GaaMSPIRegs in Global variable field
 *                       Spi_DMAGetInterruptFlag: Change the Return parameter from interrupt flag to uint32
 *                       in description field
 * 1.4.4:  08/07/2022  : Add DummyRead & SYNCP in functions: Spi_DMAMaskHWUnitInterrupts
 * 1.4.3:  10/05/2022  : Remove else do nothing
 * 1.3.2:  06/09/2021  : Update QAC contents
 *         04/09/2021  : Replace the inclusion of Spi_MemMap.h with Spi_Mapping.h
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END) 
 *         19/05/2021  : Update QAC contents.
 * 1.2.0:  30/07/2020  : Release
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.2:  22/05/2020  : Update QAC message and MISRA-C Rule violation.
 * 1.0.1:  27/04/2020  : The following changes are made:
 *                       1. Remove interrupt enable and add TE interrupt flag in Spi_DMAInit.
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Spi.h"
#include "Spi_Ram.h"
#include "Spi_Irq.h"
#include "rh850_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define SPI_SDMAC_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION_VALUE
#define SPI_SDMAC_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION_VALUE
#define SPI_SDMAC_LLDRIVER_C_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define SPI_SDMAC_LLDRIVER_C_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION_VALUE
#define SPI_SDMAC_LLDRIVER_C_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (SPI_SDMAC_LLDRIVER_AR_RELEASE_MAJOR_VERSION != SPI_SDMAC_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "Spi_sDMAC_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (SPI_SDMAC_LLDRIVER_AR_RELEASE_MINOR_VERSION != SPI_SDMAC_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "Spi_sDMAC_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (SPI_SDMAC_LLDRIVER_AR_RELEASE_REVISION_VERSION != SPI_SDMAC_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "Spi_sDMAC_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (SPI_SDMAC_LLDRIVER_SW_MAJOR_VERSION != SPI_SDMAC_LLDRIVER_C_SW_MAJOR_VERSION)
#error "Spi_sDMAC_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (SPI_SDMAC_LLDRIVER_SW_MINOR_VERSION != SPI_SDMAC_LLDRIVER_C_SW_MINOR_VERSION)
#error "Spi_sDMAC_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there. (Other uses of  */
/*                       the macro may not necessarily be suitable for replacement.)                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2985)    : This operation is redundant. The value of the result is always that of the left-hand operand.*/
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-398, CWE-561, CWE-569, CWE-633     */
/* JV-01 Justification : For readability, setting to registers will used redundant macros and is based on hardware    */
/*                       user's manual                                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0326)    : Cast between a pointer to void and an integral type.                                         */
/* Rule                : CERTCCM EXP36, INT36, MISRA C:2012 Rule-11.6, CWE Rule CWE-398, CWE-569, CWE-738             */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped.          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3464)    : Argument to macro '%s' contains a side effect that will be evaluated more than once.         */
/* Rule                : CERTCCM PRE31                                                                                */
/* JV-01 Justification : This message is only emitted for expressions expanded from argument tokens written out at    */
/*                       the top level, that did not themselves originate from a macro expansion.                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : [E] This in-line assembler construct is a language extension. The code has been ignored.     */
/* Rule                : MISRA-C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTC 1.2.4 MSC14                                   */
/* JV-01 Justification : Inline assembler support for syncp instruction.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
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
#if (SPI_DMA_CONFIGURED == STD_ON)

#define SPI_START_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"

/***********************************************************************************************************************
** Function Name      : Spi_DMAInit
**
** Service ID         : Not Applicable
**
** Description        : This function initializes all configured DMA units
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variable    : Spi_GpConfigPtr, Spi_GpFirstDMAUnit
**
** Function invoked   : Spi_DMAClearInterruptFlag
**
** Registers Used     : DMACSELj_m, MSPInTXDAm, MSPInRXDAm, CSIXnRX0H, CSIXnTX0H, DMAjSGCR_n, DMAjCHSTP_n,
**                      DMAjCHCR_n, DMAjCHFCR_n, DMAjRS_n, DMAjBUFCR_n, DMAjSAR_n, DMAjDAR_n, EIC(SDMACjCHn)
**
** Reference ID       : SPI_DUD_ACT_080, SPI_DUD_ACT_080_REG001, SPI_DUD_ACT_080_REG002, SPI_DUD_ACT_080_REG003,
** Reference ID       : SPI_DUD_ACT_080_REG004, SPI_DUD_ACT_080_REG005, SPI_DUD_ACT_080_REG006, SPI_DUD_ACT_080_REG007
***********************************************************************************************************************/
FUNC(void, SPI_PRIVATE_CODE) Spi_DMAInit(void)                                                                          /* PRQA S 3006 # JV-01 */
{
  uint32 LulDmaIndex;
  uint32 LulCSEL;
  P2CONST(Spi_DmaConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpDmaConfig;

  for (LulDmaIndex = 0UL; LulDmaIndex < Spi_GpConfigPtr->ucNoOfDMAChannels; LulDmaIndex++)                              /* PRQA S 3416 # JV-01 */
  {
    LpDmaConfig = &Spi_GpFirstDMAUnit[LulDmaIndex];
    /* Stop DMA and clear all flags */
    LpDmaConfig->pDmaRegs->ulCHFCR =
        (uint32)(SPI_DMA_OVF | SPI_DMA_DRQ | SPI_DMA_DPE | SPI_DMA_CAE | SPI_DMA_DSE | SPI_DMA_TE | SPI_DMA_DE);
    /* Set/Reset TriggerGroup bit */
    LulCSEL = LpDmaConfig->pDMACSEL[SPI_DMA_SEL_INDEX(LpDmaConfig->ucTriggerNumber)];                                   /* PRQA S 3469 # JV-01 */
    LulCSEL &= ~(1UL << SPI_DMA_SEL_SHIFT(LpDmaConfig->ucTriggerNumber));                                               /* PRQA S 3469 # JV-01 */
    LulCSEL |= ((uint32)LpDmaConfig->ucTriggerGroup << SPI_DMA_SEL_SHIFT(LpDmaConfig->ucTriggerNumber));                /* PRQA S 3469 # JV-01 */
    LpDmaConfig->pDMACSEL[SPI_DMA_SEL_INDEX(LpDmaConfig->ucTriggerNumber)] = LulCSEL;                                   /* PRQA S 3469 # JV-01 */
    /* Set trigger number */
    LpDmaConfig->pDmaRegs->ulRS = SPI_DMA_RS(LpDmaConfig->ucTriggerNumber);                                             /* PRQA S 3469 # JV-01 */
    /* Set pre-fetch buffer length as default (128) */
    LpDmaConfig->pDmaRegs->ulBUFCR = SPI_DMA_ULB_DEFAULT;
    /* Scatter/Gather features are not used */
    LpDmaConfig->pDmaRegs->ulSGCR = 0UL;
    /* Reset STP bit */
    LpDmaConfig->pDmaRegs->usCHSTP = 0U;
    /* Set source/destination address of register side */
    if (SPI_TRUE == LpDmaConfig->blRxSide)
    {
      LpDmaConfig->pDmaRegs->ulSAR = LpDmaConfig->ulRegAddress;
      /* Clear TE interrupt flag */
      Spi_DMAClearInterruptFlag(LulDmaIndex);
    }
    else
    {
      LpDmaConfig->pDmaRegs->ulDAR = LpDmaConfig->ulRegAddress;
    }
    /* Set interrupt mask */
    RH850_SV_MODE_ICR_OR(8, LpDmaConfig->pICDma, (uint8)SPI_EIC_EIMK_MASK);                                             /* PRQA S 0751 # JV-01 */
  }
  /* Dummy read & SYNCP */
  if (0U < Spi_GpConfigPtr->ucNoOfDMAChannels)                                                                          /* PRQA S 3416 # JV-01 */
  {
    LpDmaConfig = &Spi_GpFirstDMAUnit[0];
    LpDmaConfig->pDmaRegs->usCHCR;
    RH850_SV_MODE_REG_READ_ONLY(16, LpDmaConfig->pICDma);
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  } /* else No action required */
}

/***********************************************************************************************************************
** Function Name      : Spi_DMADeInit
**
** Service ID         : Not Applicable
**
** Description        : This function de-initializes all configured DMA units
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Spi_Init should have been invoked.
**
** Global Variable    : Spi_GpConfigPtr, Spi_GpFirstDMAUnit
**
** Function invoked   : None
** 
** Registers Used     : DMAjCHCR_n, DMAjCHFCR_n, EIC(SDMACjCHn), DMAjSAR_n, DMAjDAR_n, DMAjTSR_n, DMAjTMR_n,
**                      DMAjRS_n, DMAjBUFCR_n, DMACSELj_m
**
** Reference ID       : SPI_DUD_ACT_081, SPI_DUD_ACT_081_REG001, SPI_DUD_ACT_081_REG002, SPI_DUD_ACT_081_REG003,
** Reference ID       : SPI_DUD_ACT_081_REG004, SPI_DUD_ACT_081_REG005, SPI_DUD_ACT_081_REG006, SPI_DUD_ACT_081_REG007,
** Reference ID       : SPI_DUD_ACT_081_REG008, SPI_DUD_ACT_081_REG009, SPI_DUD_ACT_081_REG010, SPI_DUD_ACT_081_REG011
***********************************************************************************************************************/
FUNC(void, SPI_PRIVATE_CODE) Spi_DMADeInit(void)                                                                        /* PRQA S 3006 # JV-01 */
{
  uint32 LulDmaIndex;
  uint32 LulCSEL;
  P2CONST(Spi_DmaConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpDmaConfig;

  for (LulDmaIndex = 0UL; LulDmaIndex < Spi_GpConfigPtr->ucNoOfDMAChannels; LulDmaIndex++)                              /* PRQA S 3416 # JV-01 */
  {
    LpDmaConfig = &Spi_GpFirstDMAUnit[LulDmaIndex];
    /* Stop DMA and clear all flags */
    LpDmaConfig->pDmaRegs->ulCHFCR =
        (uint32)(SPI_DMA_OVF | SPI_DMA_DRQ | SPI_DMA_DPE | SPI_DMA_CAE | SPI_DMA_DSE | SPI_DMA_TE | SPI_DMA_DE);
    /* Restore all used registers as the reset default value */
    LpDmaConfig->pDmaRegs->ulSAR = 0UL;
    LpDmaConfig->pDmaRegs->ulDAR = 0UL;
    LpDmaConfig->pDmaRegs->ulTSR = 0UL;
    LpDmaConfig->pDmaRegs->ulTMR = SPI_DMA_TMR_DEFAULT;
    LpDmaConfig->pDmaRegs->usCHCR = SPI_DMA_CHCR_DEFAULT;
    LpDmaConfig->pDmaRegs->ulRS = SPI_DMA_RS_DEFAULT;
    LpDmaConfig->pDmaRegs->ulBUFCR = SPI_DMA_ULB_DEFAULT;
    LulCSEL = LpDmaConfig->pDMACSEL[SPI_DMA_SEL_INDEX(LpDmaConfig->ucTriggerNumber)];                                   /* PRQA S 3469 # JV-01 */
    LulCSEL &= ~(1UL << SPI_DMA_SEL_SHIFT(LpDmaConfig->ucTriggerNumber));                                               /* PRQA S 3469 # JV-01 */
    LpDmaConfig->pDMACSEL[SPI_DMA_SEL_INDEX(LpDmaConfig->ucTriggerNumber)] = LulCSEL;                                   /* PRQA S 3469 # JV-01 */
    /* Set interrupt mask */
    RH850_SV_MODE_ICR_OR(8, LpDmaConfig->pICDma, (uint8)SPI_EIC_EIMK_MASK);                                             /* PRQA S 0751 # JV-01 */
    /* Clear pending interrupt */
    RH850_SV_MODE_ICR_AND(16, LpDmaConfig->pICDma, (uint16)(~SPI_EIC_EIRF_MASK));
  }
  /* Dummy read & SYNCP */
  if (0U < Spi_GpConfigPtr->ucNoOfDMAChannels)                                                                          /* PRQA S 3416 # JV-01 */
  {
    LpDmaConfig = &Spi_GpFirstDMAUnit[0];
    LpDmaConfig->pDmaRegs->usCHCR;
    RH850_SV_MODE_REG_READ_ONLY(16, LpDmaConfig->pICDma);
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  } /* else No action required */
}

/***********************************************************************************************************************
** Function Name      : Spi_DMAStart
**
** Service ID         : Not Applicable
**
** Description        : This function starts DMA transfer
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HW. Non-Reentrant for same HW
**
** Input Parameters   : LulDmaIndex   - Index of DMAUnit
**                      LpMemAddress  - Address of memory side
**                      LulCount      - Number of data elements
**                      LulAttributes - Transfer attributes
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Spi_Init should have been invoked.
**
** Global Variable    : Spi_GpFirstDMAUnit, Spi_GenAsyncMode
**
** Function invoked   : None
**
** Registers Used     : DMAjTMR_n, DMAjTSR_n, DMAjSAR_n, DMAjDAR_n, DMAjCHFCR_n, DMAjCHCR_n, DMAjRS_n
**
** Reference ID       : SPI_DUD_ACT_082, SPI_DUD_ACT_082_REG001, SPI_DUD_ACT_082_REG002, SPI_DUD_ACT_082_REG003,
** Reference ID       : SPI_DUD_ACT_082_REG004, SPI_DUD_ACT_082_REG005, SPI_DUD_ACT_082_REG006, SPI_DUD_ACT_082_REG007,
** Reference ID       : SPI_DUD_ACT_082_REG008
***********************************************************************************************************************/
FUNC(void, SPI_PRIVATE_CODE)
Spi_DMAStart(const uint32 LulDmaIndex, volatile CONSTP2CONST(void, AUTOMATIC, SPI_APPL_DATA) LpMemAddress,              /* PRQA S 3006 # JV-01 */
             const uint32 LulCount, const uint32 LulAttributes)
{
  P2CONST(Spi_DmaConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpDmaConfig;
  uint32 LulTMR;
  uint32 LulTSR;

  LpDmaConfig = &Spi_GpFirstDMAUnit[LulDmaIndex];

  /* Setup size of transfer count per hardware request */
  LpDmaConfig->pDmaRegs->ulRS &= ~SPI_DMA_TC_MASK;
  LpDmaConfig->pDmaRegs->ulRS |= LulAttributes & SPI_DMA_TC_MASK;

  /* Keep priority setting by user */
  LulTMR = LpDmaConfig->pDmaRegs->ulTMR & SPI_DMA_PRI_MASK;
  /* Setup normal mode and hardware request source */
  LulTMR = LulTMR | SPI_DMA_SLM_NORMAL | SPI_DMA_TRS;                                                                   /* PRQA S 2985 # JV-01 */
  /* Setup transaction size in TMR register */
  switch (LulAttributes & SPI_DMA_DTS_STS_MASK)
  {
  case SPI_DMA_32BIT:
    LulTMR = LulTMR | SPI_DMA_DTS_4 | SPI_DMA_STS_4;
    LulTSR = LulCount * (uint32)(sizeof(uint32));                                                                       /* PRQA S 3383 # JV-01 */
    break;
  case SPI_DMA_16BIT:
    LulTMR = LulTMR | SPI_DMA_DTS_2 | SPI_DMA_STS_2;
    LulTSR = LulCount * (uint32)(sizeof(uint16));                                                                       /* PRQA S 3383 # JV-01 */
    break;
  default:
    LulTSR = LulCount;
    break;
  }

  if (SPI_TRUE == LpDmaConfig->blRxSide)
  {
    LpDmaConfig->pDmaRegs->ulDAR = (uint32)LpMemAddress;                                                                /* PRQA S 0326 # JV-01 */
    if (0UL != (LulAttributes & SPI_DMA_INCDST))
    {
      LulTMR = LulTMR | SPI_DMA_DM_INC | SPI_DMA_SM_FIXED;                                                              /* PRQA S 2985 # JV-01 */
    }
    else
    {
      LulTMR = LulTMR | SPI_DMA_DM_FIXED | SPI_DMA_SM_FIXED;                                                            /* PRQA S 2985 # JV-01 */
    }
  }
  else
  {
    LpDmaConfig->pDmaRegs->ulSAR = (uint32)LpMemAddress;                                                                /* PRQA S 0326 # JV-01 */
    if (0UL != (LulAttributes & SPI_DMA_INCSRC))
    {
      LulTMR = LulTMR | SPI_DMA_DM_FIXED | SPI_DMA_SM_INC;                                                              /* PRQA S 2985 # JV-01 */
    }
    else
    {
      LulTMR = LulTMR | SPI_DMA_DM_FIXED | SPI_DMA_SM_FIXED;                                                            /* PRQA S 2985 # JV-01 */
    }
  }
  LpDmaConfig->pDmaRegs->ulTMR = LulTMR;
  /* Setup transfer count for TSR register*/
  LpDmaConfig->pDmaRegs->ulTSR = LulTSR;
  /* Clear flags */
  LpDmaConfig->pDmaRegs->ulCHFCR =
      (uint32)(SPI_DMA_OVF | SPI_DMA_DRQ | SPI_DMA_DPE | SPI_DMA_CAE | SPI_DMA_DSE | SPI_DMA_TE);
  /* Start DMA */
  if (
      #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)
      (SPI_INTERRUPT_MODE == Spi_GenAsyncMode) &&                                                                       /* PRQA S 3416 # JV-01 */
      #endif
      (0UL != (LulAttributes & SPI_DMA_INTERRUPT)))
  {
    LpDmaConfig->pDmaRegs->usCHCR = SPI_DMA_IE | SPI_DMA_DE;
  }
  else
  {
    LpDmaConfig->pDmaRegs->usCHCR = SPI_DMA_DE;
  }
  /* DummyRead & SYNCP */
  LpDmaConfig->pDmaRegs->usCHCR;
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
}

/***********************************************************************************************************************
** Function Name      : Spi_DMAStop
**
** Service ID         : Not Applicable
**
** Description        : This function stops DMA unit unconditionally
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HW. Non-Reentrant for same HW
**
** Input Parameters   : LulDMAIndex - Index of DMAUnit
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Assigned SPI unit must be stopped
**
** Global Variable    : Spi_GpFirstDMAUnit, Spi_GpConfigPtr
**
** Function invoked   : None
**
** Registers Used     : DMAjCHFCR_n, DMAjCHSTA_n
**
** Reference ID       : SPI_DUD_ACT_083, SPI_DUD_ACT_083_REG001, SPI_DUD_ACT_083_REG002
***********************************************************************************************************************/
#if (SPI_FORCE_CANCEL_API == STD_ON)
FUNC(void, SPI_PRIVATE_CODE) Spi_DMAStop(const uint32 LulDmaIndex)                                                      /* PRQA S 3006 # JV-01 */
{
  P2CONST(Spi_DmaConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpDmaConfig;
  uint32 LulCount;

  LpDmaConfig = &Spi_GpFirstDMAUnit[LulDmaIndex];

  /* Stop DMA */
  LpDmaConfig->pDmaRegs->ulCHFCR = SPI_DMA_BUSY_DEC;

  /* Wait until DMAjCHSTA.BUSY bit is cleared.
     This loop will finish in a moment unless a DMA malfunctions. */
  LulCount = 0UL;
  while ((LulCount < Spi_GpConfigPtr->ulTimeoutCount) && (0UL != (LpDmaConfig->pDmaRegs->ulCHSTA & SPI_DMA_BUSY_DEC)))  /* PRQA S 3416 # JV-01 */
  {
    LulCount++;
  }

  /* Clear all flags */
  LpDmaConfig->pDmaRegs->ulCHFCR =
      (uint32)(SPI_DMA_OVF | SPI_DMA_DRQ | SPI_DMA_DPE | SPI_DMA_CAE | SPI_DMA_DSE | SPI_DMA_TE);

  /* Do DummyRead & SYNCP */
  LpDmaConfig->pDmaRegs->ulCHSTA;
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
}
#endif /* (SPI_FORCE_CANCEL_SPI == STD_ON) */

/***********************************************************************************************************************
** Function Name      : Spi_DMAMaskHWUnitInterrupts
**
** Service ID         : NA
**
** Description        : This function manipulates interrupt masks of a HWUnit.
**                      This function modifies EIMK bit only, EIRF bit is not affected.
**                      This function doesn't perform disabling interruption, dummy read & SYNCP. These should be done 
**                      in a caller.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HWUnit. Non-Reentrant for same HWUnit
**
** Input Parameters   : LulDmaIndex - Index of HW
**                      LblMask     - TRUE: set mask FALSE: reset mask
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Global variables must be initialized
**
** Global Variable    : Spi_GpFirstDMAUnit
**
** Function invoked   : None
**
** Registers Used     : EIC(SDMACjCHn)
**
** Reference ID       : SPI_DUD_ACT_084, SPI_DUD_ACT_084_REG001, SPI_DUD_ACT_084_REG002
***********************************************************************************************************************/
FUNC(void, SPI_PRIVATE_CODE) Spi_DMAMaskHWUnitInterrupts(const uint32 LulDmaIndex, const boolean LblMask)               /* PRQA S 3006 # JV-01 */
{
  /* Check if request to mask interrupt */
  if (SPI_TRUE == LblMask)
  {
    /* Write the lower byte of EIC registers to avoid modifying EIRF bit */
    RH850_SV_MODE_ICR_OR(8, Spi_GpFirstDMAUnit[LulDmaIndex].pICDma, (uint8)SPI_EIC_EIMK_MASK);                          /* PRQA S 0751, 3464, 0404 # JV-01, JV-01, JV-01 */
  }
  else
  {
    /* Write the lower byte of EIC registers to avoid modifying EIRF bit */
    RH850_SV_MODE_ICR_AND(8, Spi_GpFirstDMAUnit[LulDmaIndex].pICDma, (uint8)(~SPI_EIC_EIMK_MASK));                      /* PRQA S 0751, 3464, 0404 # JV-01, JV-01, JV-01 */
  }

  /* DummyRead & SYNCP */
  RH850_SV_MODE_REG_READ_ONLY(16, Spi_GpFirstDMAUnit[LulDmaIndex].pICDma);                                              /* PRQA S 0404 # JV-01 */
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
}

/***********************************************************************************************************************
** Function Name      : Spi_DMAClearInterruptFlag
**
** Service ID         : NA
**
** Description        : This function clears interrupt flag.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HWUnit. Non-Reentrant for same HWUnit
**
** Input Parameters   : LulDmaIndex - Index of HW
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Global variables must be initialized
**
** Global Variable    : Spi_GpFirstDMAUnit
**
** Function invoked   : None
**
** Registers Used     : DMAjCHFCR_n, DMAjCHSTA_n
**
** Reference ID       : SPI_DUD_ACT_085, SPI_DUD_ACT_085_REG001
***********************************************************************************************************************/
FUNC(void, SPI_PRIVATE_CODE) Spi_DMAClearInterruptFlag(const uint32 LulDmaIndex)                                        /* PRQA S 3006 # JV-01 */
{
  /* Clear pending interrupt flag */
  Spi_GpFirstDMAUnit[LulDmaIndex].pDmaRegs->ulCHFCR = SPI_DMA_TE;

  /* Do DummyRead & SYNCP */
  Spi_GpFirstDMAUnit[LulDmaIndex].pDmaRegs->ulCHSTA;                                                                    /* PRQA S 0404 # JV-01 */
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
}

/***********************************************************************************************************************
** Function Name      : Spi_DMAGetInterruptFlag
**
** Service ID         : NA
**
** Description        : This function gets the transfer end flag.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant
**
** Input Parameters   : LulDmaIndex - Index of HW
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : uint32
**
** Preconditions      : Global variables must be initialized
**
** Global Variable    : Spi_GpFirstDMAUnit
**
** Function invoked   : None
**
** Registers Used     : DMAjCHSTA_n
**
** Reference ID       : SPI_DUD_ACT_086, SPI_DUD_ACT_086_GBL001
***********************************************************************************************************************/
FUNC(uint32, SPI_PRIVATE_CODE) Spi_DMAGetInterruptFlag(const uint32 LulDmaIndex)
{
  uint32 LulReturnValue;

  LulReturnValue = (Spi_GpFirstDMAUnit[LulDmaIndex].pDmaRegs->ulCHSTA & SPI_DMA_TE);                                    /* PRQA S 0404 # JV-01 */

  return LulReturnValue;
}

#define SPI_STOP_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (SPI_DMA_CONFIGURED == STD_ON) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
