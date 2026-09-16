/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_TAU_LLDriver.c                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Define common Internal Function for TAU Timer Unit.                                                                */
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
                         1. Add 0404, 3006, 3415, 3416 and remove 1532, 2814, 2844, 4304
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : As part of support QAC 9.5.0, following changes are made:
 *                       1. Update QAC message and QAC header
 *                       As part of support GTM HWIP into common code, following changes are made:
 *                       1.Update precompile condition
 *                       Update SW-VERSION for Ver22.01.02 Beta2 Release 
 * 2.0.1:  25/10/2023  : Update SW-VERSION to 2.0.1
 *         19/10/2023  : Remove QAC messages 0857, 1532, 2814, 2844. Add QAC messages 3415, 3416, 0404, 3006.
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 * 1.4.3:  09/05/2022  : Remove "else" statement when no action required.
 *         17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 *         08/04/2022  : Add version information and version check for AUTOSAR release version, Module Software version.
 * 1.4.2:  02/03/2022  : Fix QAC header and message
 * 1.4.1:  20/11/2021  : Add QAC message 9.5.0
 *         16/09/2021  : Correct names, datatypes of used variables
 *                       Correct preprocessor directives
 * 1.3.2:  30/08/2021  : Change from #include "Icu_MemMap.h" to #include "Icu_Mapping.h".
 *         24/08/2021  : Add pre-compile parameters (ICU_EDGE_DETECT_API == STD_ON) for Icu_HW_Tau_StartCountMeasurement
 *                       and Icu_HW_Tau_StopCountMeasurement
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
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
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
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
/* Included for macro definitions */
#include "Icu_TAU_LLDriver.h"
/* Included for RAM variable declarations */
#include "Icu_Ram.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_TAU_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_TAU_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_TAU_LLDRIVER_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ICU_TAU_LLDRIVER_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_TAU_LLDRIVER_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ICU_TAU_LLDRIVER_AR_RELEASE_MAJOR_VERSION != ICU_TAU_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "Icu_TAU_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (ICU_TAU_LLDRIVER_AR_RELEASE_MINOR_VERSION != ICU_TAU_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "Icu_TAU_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (ICU_TAU_LLDRIVER_AR_RELEASE_REVISION_VERSION != ICU_TAU_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "Icu_TAU_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (ICU_TAU_LLDRIVER_SW_MAJOR_VERSION != ICU_TAU_LLDRIVER_C_SW_MAJOR_VERSION)
#error "Icu_TAU_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (ICU_TAU_LLDRIVER_SW_MINOR_VERSION != ICU_TAU_LLDRIVER_C_SW_MINOR_VERSION)
#error "Icu_TAU_LLDriver.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#if (ICU_TAU_UNIT_USED == STD_ON)
/***********************************************************************************************************************
** Function Name        : Icu_HW_Tau_StartCountMeasurement
**
** Service ID           : None
**
** Description          : This service routine starts the count measurement
**                        for starting edge counting or signal measurement or timestamp measurement.
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
** Global Variables     : Icu_GpChannelUserRegConfig, Icu_GpChannelConfig, Icu_GenModuleMode, Icu_GpChannelRamData.
**
** Functions invoked    : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION, RH850_SV_SET_ICR_SYNCP.
**
** Registers Used       : EICn
**
** Reference ID         : ICU_DUD_ACT_091, ICU_DUD_ACT_091_CRT001, ICU_DUD_ACT_091_CRT002,
** Reference ID         : ICU_DUD_ACT_091_REG001, ICU_DUD_ACT_091_REG002, ICU_DUD_ACT_091_REG003, ICU_DUD_ACT_091_REG004
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Tau_StartCountMeasurement(const Icu_ChannelType LddChannel)                         /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  /* Local variable to store the measurement mode of a channel */
  Icu_MeasurementModeType LenMeasurementMode;
  /* Read channel configuration pointer */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Read timer channel configuration pointer */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannel];

  /* Check if the Interrupt register is present for particular channel */
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
    /* Clear the pending interrupts */
    RH850_SV_CLEAR_ICR_SYNCP(16, LpChannelConfig->pIntrCntlAddress, ICU_CLEAR_PENDING_INTR_MASK);                       /* PRQA S 1006 # JV-01 */
    #endif
    /* Enabling the Interrupt processing */
    #if ((ICU_ENABLE_WAKEUP_API == STD_ON) || (ICU_NOTIFY_WAKEUP_INTERRUPT == STD_ON))
    if ((ICU_MODE_SLEEP == Icu_GenModuleMode) && ((uint8)ICU_FALSE == Icu_GpChannelRamData[LddChannel].ucWakeupEnable)) /* PRQA S 0404, 3415, 3416, 4304 # JV-01, JV-01, JV-01, JV-01 */
    {
      /* No action required */
    }
    else
    #endif
    {
      RH850_SV_CLEAR_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_ENABLE_EIMK_MASK);                           /* PRQA S 0751, 1006 # JV-01, JV-01 */
    }
  } /* else No action required */

  /* Read the channel's measurement mode */
  LenMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  if (ICU_MODE_SIGNAL_MEASUREMENT == LenMeasurementMode)
  {
    /* If the channel is duty cycle channel, then enable interrupt for the next channel also */
    if (ICU_DUTY_PERIOD_ENABLED_MASK == (uint8)(LpChannelUserRegConfig->ucChannelProperties &
                                                                                          ICU_DUTY_PERIOD_ENABLED_MASK))
    {
      /* Read channel configuration pointer */
      LpChannelConfig = &Icu_GpChannelConfig[LddChannel + (uint32)ICU_ONE];                                             /* PRQA S 3383 # JV-01 */

      /* Check if the Interrupt register is present for particular channel */
      if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
      {
        #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
        /* Clear the pending interrupts */
        RH850_SV_CLEAR_ICR_SYNCP(16, LpChannelConfig->pIntrCntlAddress, ICU_CLEAR_PENDING_INTR_MASK);                   /* PRQA S 1006 # JV-01 */
        #endif

        /* Enabling the Interrupt processing */
        #if ((ICU_ENABLE_WAKEUP_API == STD_ON) || (ICU_NOTIFY_WAKEUP_INTERRUPT == STD_ON))
        if ((ICU_MODE_SLEEP == Icu_GenModuleMode) &&                                                                    /* PRQA S 0404 # JV-01 */
                                                  ((uint8)ICU_FALSE == Icu_GpChannelRamData[LddChannel].ucWakeupEnable))/* PRQA S 3415, 3416, 4304 # JV-01, JV-01, JV-01 */
        {
          /* No action required */
        }
        else
        #endif
        {
          RH850_SV_CLEAR_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_ENABLE_EIMK_MASK);                       /* PRQA S 0751, 1006 # JV-01, JV-01 */
        }
      } /* else No action required */
    } /* else No action required */
  } /* else No action required */
} /* End of Internal function Icu_HW_Tau_StartCountMeasurement */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Tau_StopCountMeasurement
**
** Service ID           : None
**
** Description          : This service routine stops the count measurement
**                        for starting edge counting or signal measurement or timestamp measurement.
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
** Global Variables     : Icu_GpChannelUserRegConfig, Icu_GpChannelConfig.
**
** Functions invoked    : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION, RH850_SV_SET_ICR_SYNCP.
**
** Registers Used       : EICn
**
** Reference ID         : ICU_DUD_ACT_090, ICU_DUD_ACT_090_CRT001
** Reference ID         : ICU_DUD_ACT_090_REG001, ICU_DUD_ACT_090_REG002, ICU_DUD_ACT_090_CRT002
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Tau_StopCountMeasurement(const Icu_ChannelType LddChannel)                          /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  /* Local variable to store the measurement mode of a channel */
  Icu_MeasurementModeType LenMeasurementMode;

  /* Read channel configuration pointer */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  /* Read timer channel configuration pointer */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannel];

  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disabling the Interrupt processing */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress),  ICU_DISABLE_EIMK_MASK);                             /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */

  /* Read the channel's measurement mode */
  LenMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  if (ICU_MODE_SIGNAL_MEASUREMENT == LenMeasurementMode)
  {
    /* If the channel is duty cycle channel, then disable interrupt for the next channel also */
    if (ICU_DUTY_PERIOD_ENABLED_MASK == (uint8)(LpChannelUserRegConfig->ucChannelProperties &
                                                                                          ICU_DUTY_PERIOD_ENABLED_MASK))
    {
      /* Read channel configuration pointer */
      LpChannelConfig = &Icu_GpChannelConfig[LddChannel + (uint32)ICU_ONE];                                             /* PRQA S 3383 # JV-01 */
      if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
      {
        /* Disabling the Interrupt processing */
        RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);                          /* PRQA S 0751, 1006 # JV-01, JV-01 */
      } /* else No action required */
    } /* else No action required */
  } /* else No action required */
} /* End of Internal function Icu_HW_Tau_StopCountMeasurement */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* Edn of #if (ICU_TAU_UNIT_USED == STD_ON)*/
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
