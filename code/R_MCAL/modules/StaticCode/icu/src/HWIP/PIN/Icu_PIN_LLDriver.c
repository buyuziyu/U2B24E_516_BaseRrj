/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_PIN_LLDriver.c                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Low Level function implementations of ICU Driver Component                                      */
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
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01 Release
 * 2.3.1:  31/03/2025  : As part of support QAC 11.6.0, following changes are made:
                         1. Add 3415, 3416 and remove 2844
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : As part of support QAC 9.5.0, following changes are made:
 *                       1. Remove redundant QAC message.
*                        As part of support GTM HWIP into common code, following changes are made:
 *                       1. Remove Icu_HW_Pin_SetMode, update pre-compile condition
 *                       Update SW-VERSION for Ver22.01.02 Beta2 Release 
 * 2.0.1:  18/10/2023  : Remove QAC messages 0857, 1532, 2814, 2844. Add message 3006, 4304, 3415, 3416, 1881.
 *         14/10/2023  : Remove pre-compile parameter ICU_E_INT_INCONSISTENT_CONFIGURED for ICU_DEM_REPORT_ERROR
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 *                       Update the global critical section 
 *                       Improve code sequence of function Icu_HW_Pin_SetActivation
 *                       Icu_HW_Pin_SetMode add preprocessor before access LucWakeupStatus
 *                       Icu_HW_Pin_ExternalInterruptIsr: add preprocessor before access LpChannelConfig
 *                       Update preprocessor condition of report wakeup
 * 1.4.4:  17/11/2022  : Update "Input Parameters", "Global Variables", 
 *                       "Functions invoked" for all functions.
 *                       Add IDs ICU_DUD_ACT_057_CRT001, ICU_DUD_ACT_057_CRT002 for Icu_HW_Pin_ExternalInterruptIsr
 *         16/06/2022  : Update QAC message and QAC header
 *         09/06/2022  : Update access register FCLAnCTLm from 16 to 8 bit
 * 1.4.3:  23/05/2022  : Fix QAC header and message.
 *         09/05/2022  : Remove "else" statement when no action required; add QAC message 2004.
 *         17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 * 1.4.2:  02/03/2022  : Fix QAC header and message
 * 1.4.1:  18/10/2021  : Add QAC message 9.5.0
 *         16/09/2021  : Correct preprocessor directives
 *                       Correct name, data type of used variables
 *                       Correct indents, comments
 * 1.3.2:  30/08/2021  : Change from #include "Icu_MemMap.h" to #include "Icu_Mapping.h".
 *                       Update pre-compile parameter ICU_E_INT_INCONSISTENT_CONFIGURED for ICU_DEM_REPORT_ERROR
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.2.0:  24/08/2020  : Release
 * 1.1.1:  14/08/2020  : Corrected the resetting of EXINTCTL in
 *                       Icu_HW_Pin_ChannelDeInit().
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0317)    : Implicit conversion from a pointer to void to a pointer to object type.                      */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : This is done as per implementation requirement.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact               */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
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
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3, CWE Rule CWE-398, CWE-569                                              */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : MISRA C:2012 Rule-13.5, CERTCCM EXP02, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it does not have direct access to the HW register, and     */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifiers. There is no impact on the functionality    */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:4304)    : An expression of 'essentially Boolean' type (%1s) is being cast to unsigned type '%2s'.      */
/* Rule                : MISRA C:2012 Rule-10.5                                                                       */
/* JV-01 Justification : This is accepted. This casting from boolean to unsigned type for values 0 and 1 does not     */
/*                       make data conflict.                                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4342)    : An expression of 'essentially unsigned' type (%1s) is being cast to enum type '%2s'.         */
/* Rule                : MISRA C:2012 Rule-10.5, CWE Rule CWE-704                                                     */
/* JV-01 Justification : It is assigned to a variable with no conflict in the data.                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/* Included for Header file inclusion */
#include "Icu_PIN_LLDriver.h"
/* Included for RAM variable declarations */
#include "Icu_Ram.h"

#if (ICU_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
/* Include for interrupt consistency check */
#include "Dem.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_PIN_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_PIN_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_PIN_LLDRIVER_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ICU_PIN_LLDRIVER_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_PIN_LLDRIVER_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ICU_PIN_LLDRIVER_AR_RELEASE_MAJOR_VERSION != ICU_PIN_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Icu_PIN_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (ICU_PIN_LLDRIVER_AR_RELEASE_MINOR_VERSION != ICU_PIN_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Icu_PIN_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (ICU_PIN_LLDRIVER_AR_RELEASE_REVISION_VERSION != ICU_PIN_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Icu_PIN_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (ICU_PIN_LLDRIVER_SW_MAJOR_VERSION != ICU_PIN_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Icu_PIN_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (ICU_PIN_LLDRIVER_SW_MINOR_VERSION != ICU_PIN_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Icu_PIN_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#if ((STD_ON == ICU_IRQ_EDGE_DETECT) || (STD_ON == ICU_INTP_EDGE_DETECT))
/***********************************************************************************************************************
** Function Name        : Icu_HW_Pin_ChannelInit
**
** Service ID           : None
**
** Description          : This service initializes the hardware for all the
**                        configured channels based on the measurement mode.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Non Reentrant
**
** Input Parameters     : LddChannelIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Icu_GpChannelConfig, Icu_GpChannelRamData, Icu_GpChannelUserRegConfig.
**
** Functions invoked    : Icu_HW_Pin_SetActivation
**
** Registers Used       : EICn
**
** Reference ID         : ICU_DUD_ACT_058, ICU_DUD_ACT_058_GBL001
** Reference ID         : ICU_DUD_ACT_058_GBL004, ICU_DUD_ACT_058_GBL002, ICU_DUD_ACT_058_GBL005
** Reference ID         : ICU_DUD_ACT_058_GBL003, ICU_DUD_ACT_058_REG002, ICU_DUD_ACT_058_REG003
** Reference ID         : ICU_DUD_ACT_058_REG004, ICU_DUD_ACT_058_REG005, ICU_DUD_ACT_058_REG001
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Pin_ChannelInit(const Icu_ChannelType LddChannelIndex)                              /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* Defining a pointer to the Channel Ram Data */
  P2VAR(volatile Icu_ChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpRamData;
  /* INTP */
  #if ((ICU_INTP_EDGE_DETECT == STD_ON) && (ICU_EDGE_DETECT_API == STD_ON))
  /* Local variable to store the measurement mode of a channel */
  Icu_MeasurementModeType LenMeasurementMode;
  #endif /* End of (ICU_INTP_EDGE_DETECT == STD_ON) && (ICU_EDGE_DETECT_API == STD_ON)) */
  /* IRQ */
  #if (ICU_IRQ_EDGE_DETECT == STD_ON)
  /* Defining a pointer to point to the External Interrupt registers */
  P2VAR(volatile uint16, AUTOMATIC, ICU_CONFIG_DATA) LpExtIntpcntRegs;
  /* Defining a pointer to point to the External Interrupt registers */
  P2VAR(volatile uint8, AUTOMATIC, ICU_CONFIG_DATA) LpEXINTSTCRegs;
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_PINChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpPINChannelUserRegConfig;
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_PINChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpPinChannelConfig;
  #endif

  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannelIndex];

  /* Update the global pointer with the first channel's ram address */
  LpRamData = &Icu_GpChannelRamData[LddChannelIndex];
  /* Disable notification for each channel */
  LpRamData->ucNotificationEnable = (uint8)ICU_FALSE;                                                                   /* PRQA S 4304 # JV-01 */
  /* Initialize each channel status as idle */
  LpRamData->ucChannelStatus = (uint8)ICU_IDLE;

  /* IRQ */
  #if (ICU_IRQ_EDGE_DETECT == STD_ON)

  LpPinChannelConfig = Icu_GpChannelConfig[LddChannelIndex].pHWIPChannelConfig;
  /* Update the PIN channel configuration pointer to point to the current channel */
  LpPINChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannelIndex].pHWChannelUserRegConfig;
  /* Initialize all the configured Icu Channels */
  if (ICU_HW_EXT_IRQ == LpChannelConfig->ucIcuChannelType)
  {
    LpExtIntpcntRegs = LpChannelConfig->pCntlRegs;
    LpEXINTSTCRegs = LpPinChannelConfig->pEXINSTCRegsAddress;

    if ((uint8)ICU_RISING_EDGE == LpChannelConfig->ucIcuDefaultStartEdge)
    {
      *(LpExtIntpcntRegs) = (uint16)(*(LpExtIntpcntRegs) & (LpPINChannelUserRegConfig->ddChannelModeUserRegSettings)) |
                         (uint16)((uint16)ICU_IRQ_RISING_EDGE_MASK << (LpChannelConfig->usChannelMaskValue * ICU_TWO));
    }
    else if ((uint8)ICU_FALLING_EDGE == LpChannelConfig->ucIcuDefaultStartEdge)
    {
      *(LpExtIntpcntRegs) = (uint16)(*(LpExtIntpcntRegs) & (LpPINChannelUserRegConfig->ddChannelModeUserRegSettings)) |
                      ((uint16)((uint16)ICU_IRQ_FALLING_EDGE_MASK << (LpChannelConfig->usChannelMaskValue * ICU_TWO)));
    } /* else No action required */

    /* Clear the IRQ status flag */
    *(LpEXINTSTCRegs) = (uint8)(ICU_ONE << (uint8)LpChannelConfig->usChannelMaskValue);
  } /* else No action required */

  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disable interrupts */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);
  } /* else No action required */
  #endif /* End of ICU_IRQ_EDGE_DETECT == STD_ON */
  /* INTP */
  #if (ICU_INTP_EDGE_DETECT == STD_ON)
  /* Initialize all the configured Icu Channels */
  #if ((ICU_DISABLE_WAKEUP_API == STD_ON) || (ICU_ENABLE_WAKEUP_API == STD_ON) || \
                                                                               (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON))
  /* Disable each channel wakeup from sleep mode */
  LpRamData->ucWakeupEnable = (uint8)ICU_FALSE;                                                                         /* PRQA S 4304 # JV-01 */
  /* Initialize wakeup occurrence for each channel */
  LpRamData->blWakeupOccurrence = ICU_FALSE;
  #endif
  #if (STD_ON == ICU_SET_MODE_API)
  /* Initialize running status for each channel */
  LpRamData->ucChannelRunning = (uint8)ICU_FALSE;                                                                       /* PRQA S 4304 # JV-01 */
  #endif

  #if (ICU_EDGE_DETECT_API == STD_ON)
  /* Read the channel's measurement mode */
  LenMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */

  #endif /* End of (ICU_EDGE_DETECT_API == STD_ON) */

  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disable the Interrupt processing of the current channel */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);                              /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */

  #if (ICU_EDGE_DETECT_API == STD_ON)
  if (ICU_MODE_SIGNAL_EDGE_DETECT == LenMeasurementMode)
  {
    /* Configure external interrupt for the active edge */
    Icu_HW_Pin_SetActivation((Icu_ChannelType)LddChannelIndex,
                                                           (Icu_ActivationType)LpChannelConfig->ucIcuDefaultStartEdge); /* PRQA S 4342 # JV-01 */
  } /* else No action required */
  /* End of ICU_MODE_SIGNAL_EDGE_DETECT == LenMeasurementMode */
  #endif /* End of (ICU_EDGE_DETECT_API == STD_ON) */

  #endif /* ICU_INTP_EDGE_DETECT == STD_ON */
} /* End of Internal function Icu_HW_Pin_ChannelInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Icu_HW_Pin_ChannelDeInit
**
** Service ID           : None
**
** Description          : This service De-Initializes the hardware for all the
**                        configured channels based on the measurement mode.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Non Reentrant
**
** Input Parameters     : LddChannelIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Icu_GpChannelConfig, Icu_GpChannelRamData, Icu_GpChannelUserRegConfig.
**
** Functions invoked    : RH850_SV_MODE_REG_READ_ONLY, RH850_SV_CLEAR_ICR_SYNCP, EXECUTE_SYNCP.
**
** Registers Used       : EICn, FCLAnCTLm.
**
** Reference ID         : ICU_DUD_ACT_059, ICU_DUD_ACT_059_REG001, ICU_DUD_ACT_059_REG003
** Reference ID         : ICU_DUD_ACT_059_GBL002, ICU_DUD_ACT_059_GBL001, ICU_DUD_ACT_059_GBL004
** Reference ID         : ICU_DUD_ACT_059_GBL003, ICU_DUD_ACT_059_GBL006, ICU_DUD_ACT_059_REG002
***********************************************************************************************************************/
#if (ICU_DE_INIT_API == STD_ON)

#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Pin_ChannelDeInit(const Icu_ChannelType LddChannelIndex)                            /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  /* Defining a pointer to the Timer registers */
  P2VAR(volatile Icu_ChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpRamData;

  /* INTP */
  #if ((ICU_EDGE_DETECT_API == STD_ON) && (ICU_INTP_EDGE_DETECT == STD_ON))
  /* Defining a pointer to point to the External Interrupt registers */
  P2VAR(volatile uint8, AUTOMATIC, ICU_CONFIG_DATA) LpFCLAnCTLAddress;
  #endif /* End of (ICU_EDGE_DETECT_API == STD_ON) */

  #if (ICU_EDGE_DETECT_API == STD_ON)
  #if (ICU_IRQ_EDGE_DETECT == STD_ON)
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_PINChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpPINChannelUserRegConfig;
  /* Defining a pointer to point to the External Interrupt registers */
  P2VAR(volatile uint16, AUTOMATIC, ICU_CONFIG_DATA) LpExtIntpcntRegs;
  #endif
  /* Local variable to store the measurement mode of a channel */
  Icu_MeasurementModeType LenMeasurementMode;
  #endif

  /* Load the channel data pointer */
  LpRamData = &Icu_GpChannelRamData[LddChannelIndex];
  /* Disable notification for each channel */
  LpRamData->ucNotificationEnable = (uint8)ICU_FALSE;                                                                   /* PRQA S 4304 # JV-01 */

  /* Initialize each channel status as idle */
  LpRamData->ucChannelStatus = (uint8)ICU_IDLE;

  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannelIndex];
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disabling the Interrupt processing */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);                              /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */
  /* INTP */
  #if (ICU_INTP_EDGE_DETECT == STD_ON)

  #if ((ICU_DISABLE_WAKEUP_API == STD_ON) || (ICU_ENABLE_WAKEUP_API == STD_ON) || \
                                                                               (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON))
  /* Disable each channel wakeup from sleep mode */
  LpRamData->ucWakeupEnable = (uint8)ICU_FALSE;                                                                         /* PRQA S 4304 # JV-01 */

  /* Initialize wakeup occurrence for each channel */
  LpRamData->blWakeupOccurrence = ICU_FALSE;
  #endif

  #if (STD_ON == ICU_SET_MODE_API)
  /* Initialize running status for each channel */
  LpRamData->ucChannelRunning = (uint8)ICU_FALSE;                                                                       /* PRQA S 4304 # JV-01 */
  #endif

  #endif /* End of (ICU_INTP_EDGE_DETECT == STD_ON) */

  #if (ICU_EDGE_DETECT_API == STD_ON)
  /* Read the channel's measurement mode */
  LenMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  /* Edge Detection Mode */
  if (ICU_MODE_SIGNAL_EDGE_DETECT == LenMeasurementMode)
  {
    /* E2x - IRQ */
    #if (ICU_IRQ_EDGE_DETECT == STD_ON)
    if (ICU_HW_EXT_IRQ == LpChannelConfig->ucIcuChannelType)
    {
      /* Update the PIN channel configuration pointer to point to the current channel */
      LpPINChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannelIndex].pHWChannelUserRegConfig;
      /* Read the base configuration interrupt address */
      LpExtIntpcntRegs = LpChannelConfig->pCntlRegs;
      /* Set EXINTCTL register to the reset value */
      RH850_SV_CLEAR_ICR_SYNCP(16, LpExtIntpcntRegs, (LpPINChannelUserRegConfig->ddChannelModeUserRegSettings));
    } /* else No action required */
    #endif /* End of ICU_IRQ_EDGE_DETECT == STD_ON */
    /* INTP */
    #if (ICU_INTP_EDGE_DETECT == STD_ON)
    /* Read the base configuration interrupt address */
    LpFCLAnCTLAddress = LpChannelConfig->pCntlRegs;                                                                     /* PRQA S 0317 # JV-01 */
    /* Set FCLAnCTLm register to the reset value */
    *(LpFCLAnCTLAddress) = ICU_FCLA_CTL_RESET_VAL;
    /* DummyRead & SYNCP */
    RH850_SV_MODE_REG_READ_ONLY(8, LpFCLAnCTLAddress);
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
    #endif /* ENd of (ICU_INTP_EDGE_DETECT == STD_ON) */
  } /* else No action required */
  /* End of ICU_MODE_SIGNAL_EDGE_DETECT == LenMeasurementMode */
  #endif /* End of (ICU_EDGE_DETECT_API == STD_ON) */

} /* End of Internal function Icu_HW_Pin_ChannelDeInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_DE_INIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Icu_HW_Pin_SetActivation
**
** Service ID           : None
**
** Description          : This service configures the hardware to the active edges of the requested channel.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : LddChannel, LenActiveEdge
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : NA
**
** Global Variables     : Icu_GpChannelConfig, Icu_GpChannelRamData, Icu_GpChannelUserRegConfig.
**
** Functions invoked    : RH850_SV_CLEAR_ICR_SYNCP, RH850_SV_MODE_REG_READ_ONLY, EXECUTE_SYNCP.
**
** Registers Used       : FCLAnCTLm
**
** Reference ID         : ICU_DUD_ACT_060
** Reference ID         : ICU_DUD_ACT_060_REG001
** Reference ID         : ICU_DUD_ACT_060_REG003, ICU_DUD_ACT_060_REG004, ICU_DUD_ACT_060_GBL001
** Reference ID         : ICU_DUD_ACT_060_REG005, ICU_DUD_ACT_060_REG006, ICU_DUD_ACT_060_REG009
** Reference ID         : ICU_DUD_ACT_060_REG007, ICU_DUD_ACT_060_REG008, ICU_DUD_ACT_060_REG002
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE)
                     Icu_HW_Pin_SetActivation(const Icu_ChannelType LddChannel, const Icu_ActivationType LenActiveEdge) /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  /* INTP */
  #if (STD_ON == ICU_INTP_EDGE_DETECT)
  /* Defining a pointer to point to the External Interrupt registers */
  P2VAR(volatile uint8, AUTOMATIC, ICU_CONFIG_DATA) LpFCLAnCTLAddress;
  #endif /* End of U2Ax - INTP */

  /* E2x - IRQ */
  #if (STD_ON == ICU_IRQ_EDGE_DETECT)
  /* Defining a pointer to the PIN timer channel configuration parameters */
  P2CONST(Icu_PINChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpPINChannelUserRegConfig;
  /* Defining a pointer to point to the External Interrupt registers */
  P2VAR(volatile uint16, AUTOMATIC, ICU_CONFIG_DATA) LpExtIntpcntRegs;

  #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
  /* Defining a pointer point to the External Interrupt Status clear Register */
  P2VAR(volatile uint8, AUTOMATIC, ICU_CONFIG_DATA) LpEXINTSTCRegs;
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_PINChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpPinChannelConfig;
  LpPinChannelConfig = Icu_GpChannelConfig[LddChannel].pHWIPChannelConfig;
  #endif /* End of (ICU_CLEAR_PENDING_INTERRUPT == STD_ON) */
  #endif /* End of ((STD_ON == ICU_IRQ_EDGE_DETECT) */

  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  /* IRQ */
  #if (STD_ON == ICU_IRQ_EDGE_DETECT)
  /* Update the PIN Timer channel configuration pointer to point to the current channel */
  LpPINChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannel].pHWChannelUserRegConfig;

  if (ICU_HW_EXT_IRQ == LpChannelConfig->ucIcuChannelType)
  {
    /* Read the address of EXINTCTL control register */
    LpExtIntpcntRegs = LpChannelConfig->pCntlRegs;

    if (ICU_FALLING_EDGE == LenActiveEdge)
    {
      /* Set the edge detection bits in the EXINTCTL control register as per mask */
      *(LpExtIntpcntRegs) = (uint16)(*(LpExtIntpcntRegs) & (LpPINChannelUserRegConfig->ddChannelModeUserRegSettings))
                  | ((uint16)((uint16)ICU_IRQ_FALLING_EDGE_MASK << (LpChannelConfig->usChannelMaskValue * ICU_TWO)));
    } /* End of (LenActiveEdge == ICU_FALLING_EDGE) */
    else if (ICU_RISING_EDGE == LenActiveEdge)
    {
      /* Set the edge detection bits in the EXINTCTL control register as per mask */
      *(LpExtIntpcntRegs) = (uint16)(*(LpExtIntpcntRegs) & (LpPINChannelUserRegConfig->ddChannelModeUserRegSettings))
                    | ((uint16)((uint16)ICU_IRQ_RISING_EDGE_MASK << (LpChannelConfig->usChannelMaskValue * ICU_TWO)));
    } /* else No action required */
    /* End of (LenActiveEdge == ICU_RISING_EDGE) */
    #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
    /* Clear the IRQ status flag */
    LpEXINTSTCRegs = LpPinChannelConfig->pEXINSTCRegsAddress;
    *(LpEXINTSTCRegs) = (uint8)(ICU_ONE << (uint8)LpChannelConfig->usChannelMaskValue);
    #endif /* End of (ICU_CLEAR_PENDING_INTERRUPT == STD_ON) */
  } /* else No action required */
  #endif /* End of IRQ */

  /* INTP */
  #if (STD_ON == ICU_INTP_EDGE_DETECT)
  /* Updating the channel config parameter to the current channel */
  /* Read the address of filter control register */
  LpFCLAnCTLAddress = LpChannelConfig->pCntlRegs;                                                                       /* PRQA S 0317 # JV-01 */
  /* Mask the bypass bits of filter control register */
  *(LpFCLAnCTLAddress) = (*(LpFCLAnCTLAddress) & ICU_BYPASS_MASK);
  /* DummyRead & SYNCP */
  RH850_SV_MODE_REG_READ_ONLY(8, LpFCLAnCTLAddress);
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */

  if (ICU_BOTH_EDGES == LenActiveEdge)
  {
    /* Set the edge detection bits in the filter control register as per mask */
    *(LpFCLAnCTLAddress) = (*(LpFCLAnCTLAddress) | ICU_BOTH_EDGES_MASK);
  } /* End of ICU_BOTH_EDGES == LenActiveEdge */

  else if (ICU_FALLING_EDGE == LenActiveEdge)
  {
    /* Set the edge detection bits in the filter control register as per mask */
    *(LpFCLAnCTLAddress) = (*(LpFCLAnCTLAddress) | ICU_FALLING_EDGE_MASK);
  } /* End of ICU_FALLING_EDGE == LenActiveEdge */

  else /* (ICU_RISING_EDGE == LenActiveEdge) */
  {
    /* Set the edge detection bits in the filter control register as per mask */
    *(LpFCLAnCTLAddress) = (*(LpFCLAnCTLAddress) | ICU_RISING_EDGE_MASK);
  } /* End of ICU_RISING_EDGE == LenActiveEdge */
  /* DummyRead & SYNCP */
  RH850_SV_MODE_REG_READ_ONLY(8, LpFCLAnCTLAddress);
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  #endif /* End of STD_ON == ICU_INTP_EDGE_DETECT */

  /* Initialize channel status as idle */
  Icu_GpChannelRamData[LddChannel].ucChannelStatus = (uint8)ICU_IDLE;

  #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
  /* Check if the Interrupt register is present for particular channel */
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Clear the pending interrupts */
    RH850_SV_CLEAR_ICR_SYNCP(16, LpChannelConfig->pIntrCntlAddress, ICU_CLEAR_PENDING_INTR_MASK);                       /* PRQA S 1006 # JV-01 */
  } /* else No action required */
  #endif /* End of ICU_CLEAR_PENDING_INTERRUPT == STD_ON */
} /* End of Internal function Icu_HW_Pin_SetActivation */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Icu_HW_Pin_EnableEdgeDetection
**
** Service ID           : None
**
** Description          : This service routine starts the count measurement for starting edge counting or
**                        signal measurement or timestamp measurement.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : LddChannel
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Icu_GpChannelConfig, Icu_GpChannelRamData, Icu_GenModuleMode.
**
** Functions invoked    : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION, RH850_SV_CLEAR_ICR_SYNCP.
**
** Registers Used       : EXINTSTC
**
** Reference ID         : ICU_DUD_ACT_063, ICU_DUD_ACT_063_CRT001,
** Reference ID         : ICU_DUD_ACT_063_CRT002, ICU_DUD_ACT_063_GBL001, ICU_DUD_ACT_063_REG001
** Reference ID         : ICU_DUD_ACT_063_REG002, ICU_DUD_ACT_063_REG003, ICU_DUD_ACT_063_REG004
***********************************************************************************************************************/
#if (ICU_EDGE_DETECT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Pin_EnableEdgeDetection(const Icu_ChannelType LddChannel)                           /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* IRQ */
  #if (ICU_IRQ_EDGE_DETECT == STD_ON)
  #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
  /* Defining a pointer to point to the External */
  /* Interrupt status clear registers */
  P2VAR(volatile uint8, AUTOMATIC, ICU_CONFIG_DATA) LpEXINTSTCRegs;
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_PINChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpPinChannelConfig;
  #endif /* End of #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON) */
  #endif /* End of #if (ICU_IRQ_EDGE_DETECT == STD_ON) */

  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Get the spinlock */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  /* IRQ */
  #if (ICU_IRQ_EDGE_DETECT == STD_ON)
  if (ICU_HW_EXT_IRQ == LpChannelConfig->ucIcuChannelType)
  {
    #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
    LpPinChannelConfig = Icu_GpChannelConfig[LddChannel].pHWIPChannelConfig;
    #endif
    #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
    /* Clear the IRQ status flag */
    LpEXINTSTCRegs = LpPinChannelConfig->pEXINSTCRegsAddress;
    *(LpEXINTSTCRegs) = (uint8)(ICU_ONE << (uint8)LpChannelConfig->usChannelMaskValue);
    #endif /* End of #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON) */
    /* Check if the Interrupt register is present for particular channel */
    if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
    {
      /* Enable interrupts */
      RH850_SV_CLEAR_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_ENABLE_EIMK_MASK);
    } /* else No action required */
  } /* else No action required */
  #endif /* End of ICU_HW_EXT_IRQ == STD_ON */
  /* INTP */
  #if (ICU_INTP_EDGE_DETECT == STD_ON)
  #if (STD_ON == ICU_SET_MODE_API)
  /* Set the bit status running of channel is ICU_TRUE*/
  Icu_GpChannelRamData[LddChannel].ucChannelRunning = (uint8)ICU_TRUE;                                                  /* PRQA S 4304 # JV-01 */
  #endif
  /* Check if the Interrupt register is present for particular channel */
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
    /* Clear the pending interrupts */
    RH850_SV_CLEAR_ICR_SYNCP(16, LpChannelConfig->pIntrCntlAddress, ICU_CLEAR_PENDING_INTR_MASK);                       /* PRQA S 1006 # JV-01 */
    #endif /* End of ICU_CLEAR_PENDING_INTERRUPT == STD_ON */

    /* Enabling the Interrupt processing */
    #if ((ICU_ENABLE_WAKEUP_API == STD_ON) || (ICU_NOTIFY_WAKEUP_INTERRUPT == STD_ON))
    if ((ICU_MODE_SLEEP == Icu_GenModuleMode) && ((uint8)ICU_FALSE == Icu_GpChannelRamData[LddChannel].ucWakeupEnable)) /* PRQA S 0404, 3415, 3416, 4304 # JV-01, JV-01, JV-01, JV-01 */
    {
      /* No action required */
    }
    else
    #endif
    {
      /* Enable the Interrupt processing */
      RH850_SV_CLEAR_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_ENABLE_EIMK_MASK);                           /* PRQA S 0751, 1006 # JV-01, JV-01 */
    }
  } /* else No action required */
  #endif /* End of ICU_INTP_EDGE_DETECT == STD_ON */
  /* Release the spinlock */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
} /* End of Internal function Icu_HW_Pin_EnableEdgeDetection */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_EDGE_DETECT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Icu_HW_Pin_DisableEdgeDetection
**
** Service ID           : None
**
** Description          : This service routine stops the count measurement for starting edge counting or signal 
**                        measurement or timestamp measurement.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : LddChannel
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Icu_GpChannelConfig, Icu_GpChannelRamData.
**
** Functions invoked    : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION, RH850_SV_SET_ICR_SYNCP.
**
** Registers Used       : EICn.
**
** Reference ID         : ICU_DUD_ACT_064, ICU_DUD_ACT_064_CRT001, ICU_DUD_ACT_064_CRT004
** Reference ID         : ICU_DUD_ACT_064_GBL001, ICU_DUD_ACT_064_REG001, ICU_DUD_ACT_064_REG002
***********************************************************************************************************************/
#if (ICU_EDGE_DETECT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Pin_DisableEdgeDetection(const Icu_ChannelType LddChannel)                          /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  /* Enter local critical section */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

  /* INTP */
  #if (STD_ON == ICU_SET_MODE_API)
  /* Set bit flag channel running is ICU_FALSE */
  Icu_GpChannelRamData[LddChannel].ucChannelRunning = (uint8)ICU_FALSE;                                                 /* PRQA S 4304 # JV-01 */
  #endif

  #if (ICU_IRQ_EDGE_DETECT == STD_ON)
  if (ICU_HW_EXT_IRQ == LpChannelConfig->ucIcuChannelType)
  {
    /* Check if the Interrupt register is present for particular channel */
    if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
    {
      /* Disable interrupts */
      RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);
    } /* else No action required */
  } /* else No action required */
  #endif /* End of ICU_IRQ_EDGE_DETECT == STD_ON */
  /* INTP */
  #if (ICU_INTP_EDGE_DETECT == STD_ON)
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disable the Interrupt processing */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);                              /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */
  #endif /* End of ICU_INTP_EDGE_DETECT == STD_ON */
  /* Exit local critical section */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

} /* End of Internal function Icu_HW_Pin_DisableEdgeDetection */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_EDGE_DETECT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Icu_HW_Pin_ExternalInterruptIsr
**
** Service ID           : None
**
** Description          : This service routine is invoked from all the external
**                        interrupts which takes care of calling the notification functions.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Non-Reentrant
**
** Input Parameters     : LddChannel
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Icu_GpChannelConfig, Icu_GenModuleMode, Icu_GpChannelRamData.
**
** Functions invoked    : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION, EcuM_CheckWakeup,
**                        pIcuNotificationPointer, ICU_DEM_REPORT_ERROR.
**
** Registers Used       : EXINTSTC
**
** Reference ID         : ICU_DUD_ACT_057, ICU_DUD_ACT_057_GBL001
** Reference ID         : ICU_DUD_ACT_057_GBL002, ICU_DUD_ACT_057_REG001, ICU_DUD_ACT_057_ERR001
** Reference ID         : ICU_DUD_ACT_057_CRT001, ICU_DUD_ACT_057_CRT002
** Reference ID         : ICU_DUD_ACT_057_CRT003, ICU_DUD_ACT_057_CRT004
***********************************************************************************************************************/
#if (ICU_EDGE_DETECT_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_CODE_FAST) Icu_HW_Pin_ExternalInterruptIsr(const Icu_ChannelType LddChannel)
{
  /* Defining a pointer to point to the channel configuration parameters */
  #if (ICU_IRQ_EDGE_DETECT == STD_ON) || (ICU_INTERRUPT_CONSISTENCY_CHECK == STD_ON) || \
  (ICU_NOTIFICATION_CONFIG == STD_ON) || ((ICU_REPORT_WAKEUP_SOURCE == STD_ON) && \
  (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON))
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  #endif

  /* IRQ */
  #if (ICU_IRQ_EDGE_DETECT == STD_ON)
  /* Defining a pointer to point to the External Interrupt */
  /* Status clear registers */
  P2VAR(volatile uint8, AUTOMATIC, ICU_CONFIG_DATA) LpEXINTSTCRegs;
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_PINChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpPinChannelConfig;
  LpPinChannelConfig = Icu_GpChannelConfig[LddChannel].pHWIPChannelConfig;
  #endif

  #if (ICU_IRQ_EDGE_DETECT == STD_ON) || (ICU_INTERRUPT_CONSISTENCY_CHECK == STD_ON) || \
  (ICU_NOTIFICATION_CONFIG == STD_ON) || ((ICU_REPORT_WAKEUP_SOURCE == STD_ON) && \
  (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON))
  /* Update the channel pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  #endif

  #if (ICU_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  if ((uint16)ICU_ZERO != (uint16)(*LpChannelConfig->pIntrCntlAddress & ICU_EIC_EIMK_MASK))
  {
    ICU_DEM_REPORT_ERROR(ICU_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
    /* IRQ */
    #if (ICU_IRQ_EDGE_DETECT == STD_ON)
    /* Enter local critical section */
    ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION);
    /* Clear the IRQ status flag */
    LpEXINTSTCRegs = LpPinChannelConfig->pEXINSTCRegsAddress;
    *(LpEXINTSTCRegs) = (uint8)(ICU_ONE << (uint8)LpChannelConfig->usChannelMaskValue);
    /* Exit Protected area */
    /* Exit local critical section */
    ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION);
    #endif /* End of ICU_IRQ_EDGE_DETECT == STD_ON */
    /* INTP */
    #if (ICU_INTP_EDGE_DETECT == STD_ON)
    #if ((ICU_REPORT_WAKEUP_SOURCE == STD_ON) && (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON))
    /* If Module was in SLEEP mode and reporting wakeup is enabled */
    if ((ICU_MODE_SLEEP == Icu_GenModuleMode) && ((uint8)ICU_TRUE == Icu_GpChannelRamData[LddChannel].ucWakeupEnable))  /* PRQA S 0404, 3415, 3416, 4304 # JV-01, JV-01, JV-01, JV-01 */
    {
      if (((uint8)ICU_FALSE == LpChannelConfig->ucIcuDisableEcumWakeupNotification) &&                                  /* PRQA S 4304 # JV-01 */
                                                           (ICU_NOWAKEUP != LpChannelConfig->ucEcuMChannelWakeupInfo))
      {
        /* Set the wakeup status to true */
        Icu_GpChannelRamData[LddChannel].blWakeupOccurrence = ICU_TRUE;
        /* Report Wakeup Event to EcuM */
        EcuM_CheckWakeup((EcuM_WakeupSourceType)(ICU_DOUBLE_ONE << (LpChannelConfig->ucEcuMChannelWakeupInfo)));
      } /* else No action required */
    } /* else No action required */
    #endif
    #endif /* End of ICU_INTP_EDGE_DETECT == STD_ON */

    /* Get the spinlock since ucChannelStatus be updated by satellite core */
    ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
    /* Set channel input status as active */
    Icu_GpChannelRamData[LddChannel].ucChannelStatus = (uint8)ICU_ACTIVE;
    /* Release the spinlock */
    ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);

    #if (ICU_NOTIFICATION_CONFIG == STD_ON)
    /* Check if notification is enabled */
    if ((uint8)ICU_TRUE == (Icu_GpChannelRamData[LddChannel].ucNotificationEnable))                                     /* PRQA S 0404, 3416, 4304 # JV-01, JV-01, JV-01 */
    {
      /* Check if the function pointer address is present for particular channel */
      if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
      {
        /* callback notification */
        LpChannelConfig->pIcuNotificationPointer();
      } /* else No action required */
    } /* else No action required */
    #endif /* End of ICU_NOTIFICATION_CONFIG */
  }
} /* End of Internal function Icu_HW_Pin_ExternalInterruptIsr */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (ICU_EDGE_DETECT_API == STD_ON) */

#endif /* End of ((STD_ON == ICU_IRQ_EDGE_DETECT) || (STD_ON == ICU_INTP_EDGE_DETECT)) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
