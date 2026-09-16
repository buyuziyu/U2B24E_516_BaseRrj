/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu_Kernel.c                                                                                        */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains kernel API function implementations of OCU Driver                                               */
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
 *  1.4.0  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01
 *  1.3.1  31/03/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *  1.3.0  28/02/2025   : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  1.1.1  30/08/2024   : As part of Multi Variant support, following changes are made:
 *                        1. Change the way of comparison from using macro OCU_KERNEL_COREID to using global variable 
 *                           Ocu_GucKernelCoreId in internal function: Ocu_Kernel_StartChannel, Ocu_Kernel_StopChannel, 
 *                           Ocu_Kernel_SetPinState, Ocu_Kernel_SetPinAction, Ocu_Kernel_SetAbsoluteThreshold, 
 *                           Ocu_Kernel_SetRelativeThreshold
 *                        2. Change the way of comparison from using macro OCU_COUNT_UP to using global variable 
 *                           Ocu_GblCountingDirection in internal function: Ocu_Kernel_SetRelativeThreshold
 *  1.0.1  25/10/2023   : Add comment in Sevice ID and change from Synchronous to Asynchronous for 
                          Ocu_Kernel_StartChannel, Ocu_Kernel_StopChannel, Ocu_Kernel_SetPinState,
                          Ocu_Kernel_SetPinAction, Ocu_Kernel_SetAbsoluteThreshold, Ocu_Kernel_SetRelativeThreshold,
                          Remove in Functions invoked: Ocu_GblDriverStatus, Ocu_GaaStopChannelBuffer,
                          Ocu_GpChannelConfig, Ocu_GaaHwFunc, add Ocu_HW_Tauj_StopChannel, Ocu_HW_Taud_StopChannel for 
                          Ocu_Kernel_StopChannel
                          Change comment in Functions invoked: from Ocu_HW_Tauj_SGetCounter, Ocu_HW_Taud_SGetCounter to 
                          Ocu_HW_Tauj_GetCounter, Ocu_HW_Taud_GetCounter
                          Change comment in Functions invoked from Ocu_HW_Taud_SetRelativeThreshold,
                          Ocu_HW_Tauj_SetRelativeThreshold to Ocu_HW_Taud_SetThreshold, Ocu_HW_Tauj_SetThreshold
           23/10/2023   : Change from OCU_AR_RELEASE_MAJOR_VERSION to OCU_KERNEL_AR_RELEASE_MAJOR_VERSION, 
                          from OCU_AR_RELEASE_MINOR_VERSION to OCU_KERNEL_AR_RELEASE_MINOR_VERSION,
                          from OCU_AR_RELEASE_REVISION_VERSION to OCU_KERNEL_AR_RELEASE_REVISION_VERSION
                          from OCU_SW_MAJOR_VERSION to OCU_KERNEL_SW_MAJOR_VERSION
                          from OCU_SW_MINOR_VERSION to OCU_KERNEL_SW_MINOR_VERSION
                          Update include section: Ocu_Kernel.c always include Ocu_Kernel.h
           17/10/2023   : QAC messages: Add new 0404 and delete 2814, 2844
           25/09/2023   : Remove fix number "0" in code, update it into OCU_ZERO
 *  1.0.0  04/04/2023   : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
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
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used following AUTOSAR standard rule. It is accepted.*/
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
/* Internal type */
#include "Ocu.h"
#include "Ocu_Ram.h"
/* Kernel header */
#include "Ocu_Kernel.h"
#if (OCU_MULTI_CORE_SUPPORT == STD_ON)
/* Os header */
#include "Os.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define OCU_KERNEL_C_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define OCU_KERNEL_C_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION_VALUE
#define OCU_KERNEL_C_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define OCU_KERNEL_C_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION_VALUE
#define OCU_KERNEL_C_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (OCU_KERNEL_AR_RELEASE_MAJOR_VERSION != OCU_KERNEL_C_AR_RELEASE_MAJOR_VERSION)
  #error "Ocu_Kernel.c : Mismatch in Release Major Version"
#endif
#if (OCU_KERNEL_AR_RELEASE_MINOR_VERSION != OCU_KERNEL_C_AR_RELEASE_MINOR_VERSION)
  #error "Ocu_Kernel.c : Mismatch in Release Minor Version"
#endif
#if (OCU_KERNEL_AR_RELEASE_REVISION_VERSION != OCU_KERNEL_C_AR_RELEASE_REVISION_VERSION)
  #error "Ocu_Kernel.c : Mismatch in Release Revision Version"
#endif
#if (OCU_KERNEL_SW_MAJOR_VERSION != OCU_KERNEL_C_SW_MAJOR_VERSION)
  #error "Ocu_Kernel.c : Mismatch in Software Major Version"
#endif
#if (OCU_KERNEL_SW_MINOR_VERSION != OCU_KERNEL_C_SW_MINOR_VERSION)
  #error "Ocu_Kernel.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (OCU_MULTI_CORE_SUPPORT == STD_ON)
/* Globale scope - share among cores */
/* Start and stop channel request */
#define OCU_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Ocu_MemMap.h"

volatile VAR(Ocu_Channel_RequestType, OCU_VAR_NO_INIT) Ocu_GaaStartChannelBuffer[OCU_TOTAL_CHANNELS_CONFIG];
volatile VAR(Ocu_Channel_RequestType, OCU_VAR_NO_INIT) Ocu_GaaStopChannelBuffer[OCU_TOTAL_CHANNELS_CONFIG];

/* Set pin state request */
#if (OCU_SET_PIN_STATE_API == STD_ON)
volatile VAR(Ocu_SetPinState_RequestType, OCU_VAR_NO_INIT) Ocu_GaaSetPinStateBuffer[OCU_TOTAL_CHANNELS_CONFIG];
#endif

/* Set pin action request */
#if (OCU_SET_PIN_ACTION_API == STD_ON)
volatile VAR(Ocu_SetPinAction_RequestType, OCU_VAR_NO_INIT) Ocu_GaaSetPinActionBuffer[OCU_TOTAL_CHANNELS_CONFIG];
#endif

/* Set absolute threshold request */
#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
volatile VAR(Ocu_SetAbsoluteThreshold_RequestType, OCU_VAR_NO_INIT)
                                                          Ocu_GaaSetAbsoluteThresholdBuffer[OCU_TOTAL_CHANNELS_CONFIG];
#endif

/* Set relative threshold request */
#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
volatile VAR(Ocu_SetRelativeThreshold_RequestType, OCU_VAR_NO_INIT)
                                                          Ocu_GaaSetRelativeThresholdBuffer[OCU_TOTAL_CHANNELS_CONFIG];
#endif

#define OCU_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

#define OCU_START_SEC_PUBLIC_CODE_LOCAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Ocu_Kernel_StartChannel
**
** Service ID            : 0x0C
**
** Description           : This kernel function will check all requests from the satellite core, and proceed the request
**                         to hardware IP respectively.
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : 1. OCU Driver should be initialized.
**                         2. The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Ocu_GblDriverStatus, Ocu_GaaStartChannelBuffer, Ocu_GpChannelRamData, Ocu_GpChannelConfig
**                         Ocu_GaaHwFunc, Ocu_GucKernelCoreId
**
** Functions invoked     : Ocu_HW_Taud_StartRestartChannel, Ocu_HW_Tauj_StartRestartChannel
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_048, OCU_DUD_ACT_048_CRT001
** Reference ID          : OCU_DUD_ACT_048_CRT002, OCU_DUD_ACT_048_CRT003
** Reference ID          : OCU_DUD_ACT_048_CRT004, OCU_DUD_ACT_048_CRT005, OCU_DUD_ACT_048_GBL001
***********************************************************************************************************************/
FUNC(void, OCU_PUBLIC_CODE) Ocu_Kernel_StartChannel(void)                                                               /* PRQA S 1503 # JV-01 */
{
  /* Defining a local pointer to point to the Buffer Ram Data */
  P2VAR(volatile Ocu_Channel_RequestType, AUTOMATIC, OCU_VAR_NO_INIT) LpBufferData;
  /* Defining a pointer to point to the Channel Ram Data */
  P2VAR(Ocu_ChannelRamDataType, AUTOMATIC, OCU_CONFIG_DATA) LpRamData;                                                  /* PRQA S 3432 # JV-01 */
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check the valid kernel core and module initialization */
  if ((Ocu_GucKernelCoreId == LucCoreID) && (OCU_INITIALIZED == Ocu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucIndex = OCU_ZERO; LucIndex < OCU_TOTAL_CHANNELS_CONFIG; LucIndex++)
    {
      /* Load buffer pointer */
      LpBufferData = &Ocu_GaaStartChannelBuffer[LucIndex];
      /* Checking if any request from Satellite */
      if(OCU_CHECKINGREQUEST(LpBufferData->blSetRequest))                                                               /* PRQA S 3432 # JV-01 */
      {
        /* Enter global critical section */
        OCU_ENTER_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the buffer isn't locked */
        if(OCU_UNLOCKEDSTATUS(LpBufferData->blBufferLock))                                                              /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          OCU_LOCKPROCESS(LpBufferData->blBufferLock);                                                                  /* PRQA S 3432 # JV-01 */
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
          /* Load the channel RAM data to the local */
          LpRamData = &Ocu_GpChannelRamData[LucIndex];
          /* Read the Timer Type for the given channel */
          LucCheckTimerType = Ocu_GpChannelConfig[LucIndex].ucTimerUnitType;
          /* Exit global critical section */
          OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
          /* Check against null pointer */
          if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pStartRestartChannel)                                       /* PRQA S 3416 # JV-01 */
          {
            /* Restart the slave timer with the new threshold */
            Ocu_GaaHwFunc[LucCheckTimerType]->pStartRestartChannel(LucIndex, LpRamData->ddHwLastThreshold);
          } /* else No action required */
          /* Assign the timer status to the Channel */
          LpRamData->blChannelStatus = OCU_CH_RUNNING;
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
          /* Clean request */
          LpBufferData->blSetRequest = OCU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          OCU_UNLOCKPROCESS(LpBufferData->blBufferLock);                                                                /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        } /* End of Check if the buffer is locked */
      } /* Else No action required */
    } /* End of looping all channels */
  } /* End of check the valid kernel core and module initialization */
} /* End of API Ocu_Kernel_StartChannel */
/***********************************************************************************************************************
** Function Name         : Ocu_Kernel_StopChannel
**
** Service ID            : 0x0D
**
** Description           : This kernel function will check all requests from the satellite core, and proceed the request
**                         to hardware IP respectively.
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : 1. OCU Driver should be initialized.
**                         2. The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Ocu_GpChannelConfig, Ocu_GaaHwFunc, Ocu_GaaStopChannelBuffer, Ocu_GucKernelCoreId
**
** Functions invoked     : Ocu_HW_Tauj_StopChannel, Ocu_HW_Taud_StopChannel
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_049, OCU_DUD_ACT_049_CRT001
** Reference ID          : OCU_DUD_ACT_049_CRT002, OCU_DUD_ACT_049_CRT003, OCU_DUD_ACT_049_GBL001
***********************************************************************************************************************/
FUNC(void, OCU_PUBLIC_CODE) Ocu_Kernel_StopChannel(void)                                                                /* PRQA S 1503 # JV-01 */
{
  /* Defining a local pointer to point to the Buffer Ram Data */
  P2VAR(volatile Ocu_Channel_RequestType, AUTOMATIC, OCU_VAR_NO_INIT) LpBufferData;
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check the kernel core and module initialization */
  if ((Ocu_GucKernelCoreId == LucCoreID) && (OCU_INITIALIZED == Ocu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucIndex = OCU_ZERO; LucIndex < OCU_TOTAL_CHANNELS_CONFIG; LucIndex++)
    {
      /* Load buffer pointer */
      LpBufferData = &Ocu_GaaStopChannelBuffer[LucIndex];
      /* Checking if any request from Satellite */
      if(OCU_CHECKINGREQUEST(LpBufferData->blSetRequest))                                                               /* PRQA S 3432 # JV-01 */
      {
        /* Enter global critical section */
        OCU_ENTER_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the buffer isn't locked */
        if(OCU_UNLOCKEDSTATUS(LpBufferData->blBufferLock))                                                              /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          OCU_LOCKPROCESS(LpBufferData->blBufferLock);                                                                  /* PRQA S 3432 # JV-01 */
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
          /* Read the Timer Type for the given channel */
          LucCheckTimerType = Ocu_GpChannelConfig[LucIndex].ucTimerUnitType;
          /* Check against null pointer */
          if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pStopChannel)                                               /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low-level driver to Stop the particular Channel */
            Ocu_GaaHwFunc[LucCheckTimerType]->pStopChannel(LucIndex);
          } /* Else No action required */

          /* Clean request */
          LpBufferData->blSetRequest = OCU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          OCU_UNLOCKPROCESS(LpBufferData->blBufferLock);                                                                /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        } /* End of Check if the buffer is locked */
      } /* Else No action required */
    } /* End of looping all channels */
  } /* End of check the valid kernel core and module initialization */
} /* End of API Ocu_Kernel_StopChannel */
/***********************************************************************************************************************
** Function Name         : Ocu_Kernel_SetPinState
**
** Service ID            : 0x0E
**
** Description           : This kernel function will check all requests from the satellite core, and proceed the request
**                         to hardware IP respectively.
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Reentrant for different channel numbers
**
** Input Parameters      : Non-Reentrant
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Ocu_Init must be called before this function and
**                         OCU_SET_PIN_STATE_API must be STD_ON
**                         The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Ocu_GblDriverStatus, Ocu_GaaSetPinStateBuffer, Ocu_GpChannelConfig, Ocu_GaaHwFunc,
**                       : Ocu_GucKernelCoreId
**
** Functions invoked     : Ocu_HW_Taud_SetPinState, Ocu_HW_Tauj_SetPinState
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_050, OCU_DUD_ACT_050_CRT001
** Reference ID          : OCU_DUD_ACT_050_CRT002, OCU_DUD_ACT_050_CRT003
** Reference ID          : OCU_DUD_ACT_050_CRT004, OCU_DUD_ACT_050_CRT005, OCU_DUD_ACT_050_GBL001
***********************************************************************************************************************/
#if (OCU_SET_PIN_STATE_API == STD_ON)
FUNC(void, OCU_PUBLIC_CODE) Ocu_Kernel_SetPinState(void)                                                                /* PRQA S 1503 # JV-01 */
{
  /* Defining a local pointer to point to the Buffer Ram Data */
  P2VAR(volatile Ocu_SetPinState_RequestType, AUTOMATIC, OCU_VAR_NO_INIT) LpBufferData;
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check the kernel core and module initialization */
  if ((Ocu_GucKernelCoreId == LucCoreID) && (OCU_INITIALIZED == Ocu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucIndex = OCU_ZERO; LucIndex < OCU_TOTAL_CHANNELS_CONFIG; LucIndex++)
    {
      /* Load buffer pointer */
      LpBufferData = &Ocu_GaaSetPinStateBuffer[LucIndex];
      /* Checking if any request from Satellite */
      if(OCU_CHECKINGREQUEST(LpBufferData->blSetRequest))                                                               /* PRQA S 3432 # JV-01 */
      {
        /* Enter global critical section */
        OCU_ENTER_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the buffer isn't locked */
        if(OCU_UNLOCKEDSTATUS(LpBufferData->blBufferLock))                                                              /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          OCU_LOCKPROCESS(LpBufferData->blBufferLock);                                                                  /* PRQA S 3432 # JV-01 */
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
          /* Read the Timer Type for the given channel */
          LucCheckTimerType = Ocu_GpChannelConfig[LucIndex].ucTimerUnitType;
          /* Check against null pointer */
          if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pSetPinState)                                               /* PRQA S 3416 # JV-01 */
          {
            /* Exit global critical section */
            OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
            /* Invoke low-level driver to set the pin state for the particular Channel */
            Ocu_GaaHwFunc[LucCheckTimerType]->pSetPinState(LucIndex, LpBufferData->lddPinState);                        /* PRQA S 0404 # JV-01 */
            /* Exit global critical section */
            OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
          } /* Else No action required */
          /* Clean request */
          LpBufferData->blSetRequest = OCU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          OCU_UNLOCKPROCESS(LpBufferData->blBufferLock);                                                                /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        } /* End of Check if the buffer is locked */
      } /* Else No action required */
    } /* End of looping all channels */
  } /* End of check the valid kernel core and module initialization */
} /* End of API Ocu_Kernel_SetPinState */
#endif /* End of OCU_SET_PIN_STATE_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Ocu_Kernel_SetPinAction
**
** Service ID            : 0x0F
**
** Description           : This kernel function will check all requests from the satellite core, and proceed the request
**                         to hardware IP respectively.
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Ocu_Init must be called before this function and
**                         OCU_SET_PIN_ACTION_API must be STD_ON
**                         The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Ocu_GblDriverStatus, Ocu_GaaSetPinActionBuffer, Ocu_GpChannelConfig, Ocu_GaaHwFunc,
**                       : Ocu_GucKernelCoreId
**
** Functions invoked     : Ocu_HW_Taud_SetPinAction, Ocu_HW_Tauj_SetPinAction
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_046, OCU_DUD_ACT_046_CRT001
** Reference ID          : OCU_DUD_ACT_046_CRT002, OCU_DUD_ACT_046_CRT003, OCU_DUD_ACT_046_GBL002
** Reference ID          : OCU_DUD_ACT_046_CRT004, OCU_DUD_ACT_046_CRT005, OCU_DUD_ACT_046_GBL001
***********************************************************************************************************************/
#if (OCU_SET_PIN_ACTION_API == STD_ON)
FUNC(void, OCU_PUBLIC_CODE) Ocu_Kernel_SetPinAction(void)                                                               /* PRQA S 1503 # JV-01 */
{
  /* Defining a local pointer to point to the Buffer Ram Data */
  P2VAR(volatile Ocu_SetPinAction_RequestType, AUTOMATIC, OCU_VAR_NO_INIT) LpBufferData;
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check the kernel core and module initialization */
  if ((Ocu_GucKernelCoreId == LucCoreID) && (OCU_INITIALIZED == Ocu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucIndex = OCU_ZERO; LucIndex < OCU_TOTAL_CHANNELS_CONFIG; LucIndex++)
    {
      /* Load buffer pointer */
      LpBufferData = &Ocu_GaaSetPinActionBuffer[LucIndex];
      /* Checking if any request from Satellite */
      if(OCU_CHECKINGREQUEST(LpBufferData->blSetRequest))                                                               /* PRQA S 3432 # JV-01 */
      {
        /* Enter global critical section */
        OCU_ENTER_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the buffer isn't locked */
        if(OCU_UNLOCKEDSTATUS(LpBufferData->blBufferLock))                                                              /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          OCU_LOCKPROCESS(LpBufferData->blBufferLock);                                                                  /* PRQA S 3432 # JV-01 */
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
          /* Read the Timer Type for the given channel */
          LucCheckTimerType = Ocu_GpChannelConfig[LucIndex].ucTimerUnitType;
          /* Exit global critical section */
          OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
          /* Check against null pointer */
          if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pSetPinAction)                                              /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low-level driver to set the pin action for the particular Channel */
            Ocu_GaaHwFunc[LucCheckTimerType]->pSetPinAction(LucIndex, LpBufferData->lddPinAction);                      /* PRQA S 0404 # JV-01 */
          }
          /* Save the new pin action state into ram */
          Ocu_GpChannelRamData[LucIndex].ddPinActionState =  LpBufferData->lddPinAction;                                /* PRQA S 0404 # JV-01 */
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
          /* Clean request */
          LpBufferData->blSetRequest = OCU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          OCU_UNLOCKPROCESS(LpBufferData->blBufferLock);                                                                /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        } /* End of Check if the buffer is locked */
      } /* Else No action required */
    } /* End of looping all channels */
  } /* End of check the valid kernel core and module initialization */
} /* End of API Ocu_Kernel_SetPinAction */
#endif /* End of OCU_SET_PIN_ACTION_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Ocu_Kernel_SetAbsoluteThreshold
**
** Service ID            : 0x10
**
** Description           : This kernel function will check all requests from the satellite core, and proceed the request
**                         to hardware IP respectively.
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Ocu_Init must be called before this function and
**                         OCU_SET_ABSOLUTE_THRESHOLD_API must be STD_ON
**                         The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Ocu_GblDriverStatus, Ocu_GaaSetAbsoluteThresholdBuffer, Ocu_GpChannelConfig, Ocu_GaaHwFunc,
**                       : Ocu_GucKernelCoreId
**
** Functions invoked     : Ocu_HW_Tauj_SetThreshold, Ocu_HW_Taud_SetThreshold
**                       : Ocu_HW_Tauj_GetCounter, Ocu_HW_Taud_GetCounter
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_045, OCU_DUD_ACT_045_CRT001
** Reference ID          : OCU_DUD_ACT_045_CRT002, OCU_DUD_ACT_045_CRT003
** Reference ID          : OCU_DUD_ACT_045_CRT004, OCU_DUD_ACT_045_CRT005, OCU_DUD_ACT_045_GBL001
***********************************************************************************************************************/
#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
FUNC(void, OCU_PUBLIC_CODE) Ocu_Kernel_SetAbsoluteThreshold(void)                                                       /* PRQA S 1503 # JV-01 */
{
  /* Defining a local pointer to point to the Buffer Ram Data */
  P2VAR(volatile Ocu_SetAbsoluteThreshold_RequestType, AUTOMATIC, OCU_VAR_NO_INIT) LpBufferData;
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check the kernel core and module initialization */
  if ((Ocu_GucKernelCoreId == LucCoreID) && (OCU_INITIALIZED == Ocu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucIndex = OCU_ZERO; LucIndex < OCU_TOTAL_CHANNELS_CONFIG; LucIndex++)
    {
      /* Load buffer pointer */
      LpBufferData = &Ocu_GaaSetAbsoluteThresholdBuffer[LucIndex];
      /* Checking if any request from Satellite */
      if(OCU_CHECKINGREQUEST(LpBufferData->blSetRequest))                                                               /* PRQA S 3432 # JV-01 */
      {
        /* Enter global critical section */
        OCU_ENTER_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the buffer isn't locked */
        if(OCU_UNLOCKEDSTATUS(LpBufferData->blBufferLock))                                                              /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          OCU_LOCKPROCESS(LpBufferData->blBufferLock);                                                                  /* PRQA S 3432 # JV-01 */
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
          /* Read the Timer Type for the given channel */
          LucCheckTimerType = Ocu_GpChannelConfig[LucIndex].ucTimerUnitType;
          /* Enter global critical section */
          OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
          /* Check that the low-layer function is valid */
          if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pSetThreshold)                                              /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low-level driver to set the new threshold using absolute value */
            Ocu_GaaHwFunc[LucCheckTimerType]->pSetThreshold(LucIndex, LpBufferData->lddSwAbsoluteValue);                /* PRQA S 0404 # JV-01 */
          } /* Else No action required */
          /* Check that the low-layer function is valid */
          if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter)                                                /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low-level driver to get the current counter value again after setting the new threshold */
            LpBufferData->lddSwCounterValue = Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter(LucIndex);
          } /* Else No action required */
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
          /* Clean request */
          LpBufferData->blSetRequest = OCU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          OCU_UNLOCKPROCESS(LpBufferData->blBufferLock);                                                                /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        } /* End of Check if the buffer is locked */
      } /* Else No action required */
    } /* End of looping all channels */
  } /* End of check the valid kernel core and module initialization */
} /* End of API Ocu_Kernel_SetAbsoluteThreshold */
#endif /* End of OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Ocu_Kernel_SetRelativeThreshold
**
** Service ID            : 0x11
**
** Description           : This kernel function will check all requests from the satellite core, and proceed the request
**                         to hardware IP respectively.
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Ocu_Init must be called before this function and
**                         OCU_SET_RELATIVE_THRESHOLD_API must be STD_ON
**                         The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Ocu_GblDriverStatus, Ocu_GaaSetRelativeThresholdBuffer, Ocu_GpChannelConfig, Ocu_GaaHwFunc,
**                       : Ocu_GblCountingDirection, Ocu_GucKernelCoreId
**
** Functions invoked     : Ocu_HW_Tauj_SetThreshold, Ocu_HW_Taud_SetThreshold
**
** Registers Used        : None
**
** Reference ID          : OCU_DUD_ACT_047, OCU_DUD_ACT_047_CRT001
** Reference ID          : OCU_DUD_ACT_047_CRT002, OCU_DUD_ACT_047_CRT003
** Reference ID          : OCU_DUD_ACT_047_CRT004, OCU_DUD_ACT_047_CRT005, OCU_DUD_ACT_047_GBL001
***********************************************************************************************************************/
#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
FUNC(void, OCU_PUBLIC_CODE) Ocu_Kernel_SetRelativeThreshold(void)                                                       /* PRQA S 1503 # JV-01 */
{
  /* Defining a local pointer to point to the Buffer Ram Data */
  P2VAR(volatile Ocu_SetRelativeThreshold_RequestType, AUTOMATIC, OCU_VAR_NO_INIT) LpBufferData;
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  /* Variable to hold the current SW time */
  VAR(volatile Ocu_ValueType, AUTOMATIC) LddSwCounterValue;
  /* Local variable holds the new reference SW tick */
  VAR(Ocu_ValueType, AUTOMATIC) LddSwRelativeValue;
  /* Local variable holds the new absolute threshold - SW tick */
  VAR(Ocu_ValueType, AUTOMATIC) LddSwThresholdValue;
  /* Local variable holds the rest SW tick until the counter overflow */
  VAR(Ocu_ValueType, AUTOMATIC) LddSwOverFlowValue;
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check the kernel core and module initialization */
  if ((Ocu_GucKernelCoreId == LucCoreID) && (OCU_INITIALIZED == Ocu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucIndex = OCU_ZERO; LucIndex < OCU_TOTAL_CHANNELS_CONFIG; LucIndex++)
    {
      /* Load buffer pointer */
      LpBufferData = &Ocu_GaaSetRelativeThresholdBuffer[LucIndex];
      /* Checking if any request from Satellite */
      if(OCU_CHECKINGREQUEST(LpBufferData->blSetRequest))                                                               /* PRQA S 3432 # JV-01 */
      {
        /* Enter global critical section */
        OCU_ENTER_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the buffer isn't locked */
        if(OCU_UNLOCKEDSTATUS(LpBufferData->blBufferLock))                                                              /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          OCU_LOCKPROCESS(LpBufferData->blBufferLock);                                                                  /* PRQA S 3432 # JV-01 */
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
            /* Initial value */
          LddSwCounterValue = (uint32)OCU_ZERO;
          LddSwRelativeValue = LpBufferData->lddSwRelativeValue;
          /* Read the Timer Type for the given channel */
          LucCheckTimerType = Ocu_GpChannelConfig[LucIndex].ucTimerUnitType;
          /* Enter global critical section */
          OCU_ENTER_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
          /* Check that the low-layer function is valid */
          if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter)                                                /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low-level driver to get the current counter value */
            LddSwCounterValue = Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter(LucIndex);
            LpBufferData->lddSwReferenceValue = LddSwCounterValue;
          } /* else No action required */
          /* Check the counting direction */
          if (OCU_UPCOUNTING == Ocu_GblCountingDirection)                                                               /* PRQA S 3416 # JV-01 */
          {
            /* Read the remaining tick until overflow occurs on the master channel */
            LddSwOverFlowValue = Ocu_GpChannelConfig[LucIndex].ulMaxCounterValue - LddSwCounterValue;                   /* PRQA S 0404, 3384 # JV-01, JV-01 */
            /* Check that is there any capable of overflowing the master counter */
            if (LddSwOverFlowValue >= LddSwRelativeValue)
            {
              /* Set new absolute threshold value equal to last counter + relative time */
              LddSwThresholdValue = LddSwCounterValue + LddSwRelativeValue;                                             /* PRQA S 3383 # JV-01 */
            }
            else /* The master channel will overflow */
            {
              /* Set new absolute threshold value */
              LddSwThresholdValue = (LddSwRelativeValue - LddSwOverFlowValue) - (uint32)OCU_ONE;                        /* PRQA S 3383, 3384 # JV-01, JV-01 */
            }
          }
          else /* Else OCU_DOWNCOUNTING */
          {
            /* Check that is there any capable of overflowing the master counter */
            if (LddSwCounterValue >= LddSwRelativeValue)                                                                /* PRQA S 3416 # JV-01 */
            {
              /* Set new absolute threshold value equal to last counter - relative time */
              LddSwThresholdValue = LddSwCounterValue - LddSwRelativeValue;                                             /* PRQA S 3384 # JV-01 */
            }
            else /* The master channel will overflow */
            {
              /* Read the max Sw counter value */
              LddSwOverFlowValue = Ocu_GpChannelConfig[LucIndex].ulMaxCounterValue;
              /* Set new absolute threshold value */
              LddSwThresholdValue = LddSwOverFlowValue - (LddSwRelativeValue - LddSwCounterValue - (uint32)OCU_ONE);    /* PRQA S 3383, 3384 # JV-01, JV-01 */
            }
          } /* OCU_UPCOUNTING == Ocu_GblCountingDirection */
          /* Save the calculated new SW threshold */
          LpBufferData->lddSwThresholdValue = LddSwThresholdValue;
          /* Check against null pointer */
          if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pSetThreshold)                                              /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low-level driver to set the new threshold using relative value */
            Ocu_GaaHwFunc[LucCheckTimerType]->pSetThreshold(LucIndex, LddSwThresholdValue);
          } /* Else No action required */
          /* Check that the low-layer function is valid */
          if (NULL_PTR != Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter)                                                /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low-level driver to get the current counter value */
            LpBufferData->lddSwCounterValue = Ocu_GaaHwFunc[LucCheckTimerType]->pGetCounter(LucIndex);
          } /* else No action required */
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
          /* Clean request */
          LpBufferData->blSetRequest = OCU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          OCU_UNLOCKPROCESS(LpBufferData->blBufferLock);                                                                /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Exit global critical section */
          OCU_EXIT_CRITICAL_SECTION(OCU_RAM_DATA_PROTECTION_GLOBAL);
        } /* End of Check if the buffer is locked */
      } /* Else No action required */
    } /* End of looping all channels */
  } /* End of check the valid kernel core and module initialization */
} /* End of API Ocu_Kernel_SetRelativeThreshold */
#endif /* End of OCU_SET_RELATIVE_THRESHOLD_API == STD_ON */

#define OCU_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Ocu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* OCU_MULTI_CORE_SUPPORT == STD_ON */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
