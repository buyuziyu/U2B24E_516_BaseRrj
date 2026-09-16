/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_Kernel.c                                                                                        */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Kernel function implementations of PWM Driver                                                   */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
** 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                                                            **
** 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                        **
** 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                           **
** 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                            **
** 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                           **
** 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
** 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
** 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.01.02 U2Bx, Ver22.00.05 U2Cx Beta2 Release                         **
** 2.1.1: 30/08/2024 : As part of U2Cx Diag support, following changes are made                                       **
**                     1. Add QAC message 1503, 3416, 3415, 3432, 0404 for function Pwm_Kernel_SetTriggerDelay        **
**                     As part of ARDAACL-40198 support, following changes are made                                   **
**                     1. Change macro PWM_KERNEL_COREID to global variable Pwm_GucKernelCoreId                       **
**                     2. Remove QAC message 1881                                                                     **
** 2.0.1: 21/10/2023 : Follow rule QAC 10.3.0, add new QAC message 0404 and remove QAC message 2814                   **
**                     Add QAC comment 3416                                                                           **
**        18/10/2023 : Add QAC message 1881                                                                           **
** 2.0.0: 28/06/2023 : Initial Version.                                                                               **
**                                                                                                                    */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
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
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* internal type */
#include "Pwm.h"
#include "Pwm_Ram.h"
#if (PWM_MULTI_CORE_SUPPORT == STD_ON)
#if (PWM_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Pwm.h"
#endif
/* Kernel header */
#include "Pwm_Kernel.h"
/* Os header */
#include "Os.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define PWM_KERNEL_C_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION_VALUE
#define PWM_KERNEL_C_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION_VALUE
#define PWM_KERNEL_C_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define PWM_KERNEL_C_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION_VALUE
#define PWM_KERNEL_C_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (PWM_AR_RELEASE_MAJOR_VERSION != PWM_KERNEL_C_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm_Kernel.c : Mismatch in Release Major Version"
#endif
#if (PWM_AR_RELEASE_MINOR_VERSION != PWM_KERNEL_C_AR_RELEASE_MINOR_VERSION)
  #error "Pwm_Kernel.c : Mismatch in Release Minor Version"
#endif
#if (PWM_AR_RELEASE_REVISION_VERSION != PWM_KERNEL_C_AR_RELEASE_REVISION_VERSION)
  #error "Pwm_Kernel.c : Mismatch in Release Revision Version"
#endif
#if (PWM_SW_MAJOR_VERSION != PWM_KERNEL_C_SW_MAJOR_VERSION)
  #error "Pwm_Kernel.c : Mismatch in Software Major Version"
#endif
#if (PWM_SW_MINOR_VERSION != PWM_KERNEL_C_SW_MINOR_VERSION)
  #error "Pwm_Kernel.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (PWM_MULTI_CORE_SUPPORT == STD_ON)
/* Globale scope - share among cores */
#define PWM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Pwm_MemMap.h"

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
volatile VAR(Pwm_SetDutyCycle_RequestType, PWM_VAR_NO_INIT) Pwm_GaaSetDutyCycleBuffer[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
volatile VAR(Pwm_SetPeriodAndDuty_RequestType, PWM_VAR_NO_INIT) 
                                                              Pwm_GaaSetPeriodAndDutyBuffer[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
volatile VAR(Pwm_Channel_RequestType, PWM_VAR_NO_INIT) Pwm_GaaSetOutputToIdleBuffer[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
volatile VAR(Pwm_SelectChannelClk_RequestType, PWM_VAR_NO_INIT) 
                                                              Pwm_GaaSelectChannelClkBuffer[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
volatile VAR(Pwm_SetChannelOutput_RequestType, PWM_VAR_NO_INIT) 
                                                              Pwm_GaaSetChannelOutputBuffer[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#if (PWM_SET_TRIGGER_DELAY_API == STD_ON)
volatile VAR(Pwm_SetTriggerDelay_RequestType, PWM_VAR_NO_INIT) Pwm_GaaSetTriggerDelayBuffer[PWM_TOTAL_CHANNELS_CONFIG];
#endif

#define PWM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

#define PWM_START_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
/***********************************************************************************************************************
** Function Name        : Pwm_Kernel_SetDutyCycle
**
** Service ID           : None
**
** Description          : This kernel function will check all request from sattelite core, and proceed the request to
**                        hardware IP respectively.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None.
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1. PWM Driver should be initialized.
**                        2. This function is available only if the pre-compile option PWM_SET_DUTY_CYCLE_API is STD_ON.
**                        3. The Kernel is scheduled function, which will be mapped to a period task
**
** Global Variables     : Pwm_GpChannelConfig
**
** Functions invoked    : Pwm_<HW-IP>_SetDutyCycle, Pwm_CheckDetErrors
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_108, PWM_DUD_ACT_108_CRT001, PWM_DUD_ACT_108_CRT002, PWM_DUD_ACT_108_CRT003
** Reference ID         : PWM_DUD_ACT_108_GBL001
***********************************************************************************************************************/
FUNC(void, PWM_PUBLIC_CODE) Pwm_Kernel_SetDutyCycle(void)                                                               /* PRQA S 1503 # JV-01 */
{
    /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucIndex;
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();

  /* Check if the PWM Driver is initialized properly */
  if ((Pwm_GucKernelCoreId == LucCoreID) && (PWM_INITIALIZED == Pwm_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucIndex = 0U; LucIndex < PWM_TOTAL_CHANNELS_CONFIG; LucIndex++)
    {
      /* If request is not on going by Satellite */
      if(Pwm_CheckingRequest(Pwm_GaaSetDutyCycleBuffer[LucIndex].blSetReq))                                             /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

        /* Check if the buffer is locked */
        if(Pwm_UnLockedStatus(Pwm_GaaSetDutyCycleBuffer[LucIndex].blBufferLock))                                        /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          Pwm_LockProcess(Pwm_GaaSetDutyCycleBuffer[LucIndex].blBufferLock);                                            /* PRQA S 3432 # JV-01 */

          /* Release the spinlock */
          PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

          /* Updating the channel config parameter to the current channel */
          LucTimerUnitType = Pwm_GpChannelConfig[LucIndex].ucTimerUnitType;
          /* Check against null pointer */
          if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetDutyCycle)                                             /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low level driver for initializing the hardware */
            Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetDutyCycle(LucIndex,                                                  /* PRQA S 0404 # JV-01 */
                                                                Pwm_GaaSetDutyCycleBuffer[LucIndex].lusDutyCycle);
          } /* else No action required */

          /* Clean request */
          Pwm_GaaSetDutyCycleBuffer[LucIndex].blSetReq = PWM_FALSE;

          /* Lock processing - notify that master is proceeded the request */
          Pwm_UnLockProcess(Pwm_GaaSetDutyCycleBuffer[LucIndex].blBufferLock);                                          /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    }
  } /* else No action required */
}
#endif /* #if (PWM_SET_DUTY_CYCLE_API == STD_ON) */

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
/***********************************************************************************************************************
** Function Name        : Pwm_Kernel_SetPeriodAndDuty
**
** Service ID           : None
**
** Description          : This kernel function will check all request from sattelite core, and proceed the request to
**                        hardware IP respectively.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None.
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1. PWM Driver should be initialized.
**                        2. This function is available only if the pre-compile option PWM_SET_PERIOD_AND_DUTY_API is 
**                        STD_ON.
**                        3. The Kernel is scheduled function, which will be mapped to a period task.
**
** Global Variables     : Pwm_GpChannelConfig
**
** Functions invoked    : Pwm_<HW-IP>_SetPeriodAndDuty
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_109, PWM_DUD_ACT_109_CRT001, PWM_DUD_ACT_109_CRT002, PWM_DUD_ACT_109_CRT003
** Reference ID         : PWM_DUD_ACT_109_GBL001
***********************************************************************************************************************/
FUNC(void, PWM_PUBLIC_CODE) Pwm_Kernel_SetPeriodAndDuty(void)                                                           /* PRQA S 1503 # JV-01 */
{
    /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucIndex;
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();

  if ((Pwm_GucKernelCoreId == LucCoreID) && (PWM_INITIALIZED == Pwm_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucIndex = 0U; LucIndex < PWM_TOTAL_CHANNELS_CONFIG; LucIndex++)
    {
      /* If request is not on going by Satellite */
      if(Pwm_CheckingRequest(Pwm_GaaSetPeriodAndDutyBuffer[LucIndex].blSetReq))                                         /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

        /* Check if the buffer is locked */
        if(Pwm_UnLockedStatus(Pwm_GaaSetPeriodAndDutyBuffer[LucIndex].blBufferLock))                                    /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          Pwm_LockProcess(Pwm_GaaSetPeriodAndDutyBuffer[LucIndex].blBufferLock);                                        /* PRQA S 3432 # JV-01 */

          /* Release the spinlock */
          PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

          /* Updating the channel config parameter to the current channel */
          LucTimerUnitType = Pwm_GpChannelConfig[LucIndex].ucTimerUnitType;
          /* Check against null pointer */
          if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetPeriodAndDuty)                                         /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low level driver for initializing the hardware */
            Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetPeriodAndDuty                                                        /* PRQA S 0404 # JV-01 */
                                                     (LucIndex, Pwm_GaaSetPeriodAndDutyBuffer[LucIndex].lddPeriod, 
                                                        Pwm_GaaSetPeriodAndDutyBuffer[LucIndex].lusDutyCycle);
          } /* else No action required */

          /* Clean request */
          Pwm_GaaSetPeriodAndDutyBuffer[LucIndex].blSetReq = PWM_FALSE;

          /* Lock processing - notify that master is proceeded the request */
          Pwm_UnLockProcess(Pwm_GaaSetPeriodAndDutyBuffer[LucIndex].blBufferLock);                                      /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    }
  } /* else No action required */
}
#endif /* #if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON) */

#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
/***********************************************************************************************************************
** Function Name        : Pwm_Kernel_SetOutputToIdle
**
** Service ID           : None
**
** Description          : This kernel function will check all request from sattelite core, and proceed the request to
**                        hardware IP respectively.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None.
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1. PWM Driver should be initialized.
**                        2. This function is available only if the pre-compile option PWM_SET_OUTPUT_TO_IDLE_API is
**                        STD_ON.
**                        3. The Kernel is scheduled function, which will be mapped to a period task
**
** Global Variables     : Pwm_GpChannelConfig
**
** Functions invoked    : Pwm_<HW-IP>_SetOutputToIdle
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_110, PWM_DUD_ACT_110_CRT001, PWM_DUD_ACT_110_CRT002, PWM_DUD_ACT_110_CRT003
** Reference ID         : PWM_DUD_ACT_110_GBL001
***********************************************************************************************************************/
FUNC(void, PWM_PUBLIC_CODE) Pwm_Kernel_SetOutputToIdle(void)                                                            /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucIndex;
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();

  if ((Pwm_GucKernelCoreId == LucCoreID) && (PWM_INITIALIZED == Pwm_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucIndex = 0U; LucIndex < PWM_TOTAL_CHANNELS_CONFIG; LucIndex++)
    {
      /* If request is not on going by Satellite */
      if(Pwm_CheckingRequest(Pwm_GaaSetOutputToIdleBuffer[LucIndex].blSetReq))                                          /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

        /* Check if the buffer is locked */
        if(Pwm_UnLockedStatus(Pwm_GaaSetOutputToIdleBuffer[LucIndex].blBufferLock))                                     /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          Pwm_LockProcess(Pwm_GaaSetOutputToIdleBuffer[LucIndex].blBufferLock);                                         /* PRQA S 3432 # JV-01 */

          /* Release the spinlock */
          PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

          /* Updating the channel config parameter to the current channel */
          LucTimerUnitType = Pwm_GpChannelConfig[LucIndex].ucTimerUnitType;
          /* Check against null pointer */
          if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetOutputToIdle)                                          /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low level driver for initializing the hardware */
            Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetOutputToIdle(LucIndex);
          } /* else No action required */

          /* Clean request */
          Pwm_GaaSetOutputToIdleBuffer[LucIndex].blSetReq = PWM_FALSE;

          /* Lock processing - notify that master is proceeded the request */
          Pwm_UnLockProcess(Pwm_GaaSetOutputToIdleBuffer[LucIndex].blBufferLock);                                       /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    }
  } /* else No action required */
}
#endif /* #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON) */

#if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
/***********************************************************************************************************************
** Function Name        : Pwm_Kernel_SelectChannelClk
**
** Service ID           : None
**
** Description          : This kernel function will check all request from sattelite core, and proceed the request to
**                        hardware IP respectively.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None.
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1. PWM Driver should be initialized.
**                        2. This function is available only if the pre-compile option PWM_SELECT_CHANNEL_CLK_API is
**                        STD_ON.
**                        3. The Kernel is scheduled function, which will be mapped to a period task
**
** Global Variables     : Pwm_GpChannelConfig
**
** Functions invoked    : Pwm_<HW-IP>_SelectChannelClk
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_111, PWM_DUD_ACT_111_CRT001, PWM_DUD_ACT_111_CRT002, PWM_DUD_ACT_111_CRT003
** Reference ID         : PWM_DUD_ACT_111_GBL001
***********************************************************************************************************************/
FUNC(void, PWM_PUBLIC_CODE) Pwm_Kernel_SelectChannelClk(void)                                                           /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucIndex;
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();

  if ((Pwm_GucKernelCoreId == LucCoreID) && (PWM_INITIALIZED == Pwm_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucIndex = 0U; LucIndex < PWM_TOTAL_CHANNELS_CONFIG; LucIndex++)
    {
      /* If request is not on going by Satellite */
      if(Pwm_CheckingRequest(Pwm_GaaSelectChannelClkBuffer[LucIndex].blSetReq))                                         /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

        /* Check if the buffer is locked */
        if(Pwm_UnLockedStatus(Pwm_GaaSelectChannelClkBuffer[LucIndex].blBufferLock))                                    /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          Pwm_LockProcess(Pwm_GaaSelectChannelClkBuffer[LucIndex].blBufferLock);                                        /* PRQA S 3432 # JV-01 */

          /* Release the spinlock */
          PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

          /* Updating the channel config parameter to the current channel */
          LucTimerUnitType = Pwm_GpChannelConfig[LucIndex].ucTimerUnitType;
          /* Check against null pointer */
          if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWSelectChannelClk)                                         /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low level driver for initializing the hardware */
            Pwm_GaaHwFunc[LucTimerUnitType]->pHWSelectChannelClk(LucIndex,                                              /* PRQA S 0404 # JV-01 */
                                                            Pwm_GaaSelectChannelClkBuffer[LucIndex].lddClockSource);
          } /* else No action required */

          /* Clean request */
          Pwm_GaaSelectChannelClkBuffer[LucIndex].blSetReq = PWM_FALSE;

          /* Lock processing - notify that master is proceeded the request */
          Pwm_UnLockProcess(Pwm_GaaSelectChannelClkBuffer[LucIndex].blBufferLock);                                      /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    } 
  } /* else No action required */
}
#endif /* #if (PWM_SELECT_CHANNEL_CLK_API == STD_ON) */

#if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
/***********************************************************************************************************************
** Function Name        : Pwm_Kernel_SetChannelOutput
**
** Service ID           : None
**
** Description          : This kernel function will check all request from sattelite core, and proceed the request to
**                        hardware IP respectively.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None.
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1. PWM Driver should be initialized.
**                        2. This function is available only if the pre-compile option PWM_SET_CHANNEL_OUTPUT_API is
**                        STD_ON.
**                        3. The Kernel is scheduled function, which will be mapped to a period task
**
** Global Variables     : Pwm_GpChannelConfig
**
** Functions invoked    : Pwm_<HW-IP>_SetChannelOutput
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_112, PWM_DUD_ACT_112_CRT001, PWM_DUD_ACT_112_CRT002, PWM_DUD_ACT_112_CRT003
** Reference ID         : PWM_DUD_ACT_112_GBL001
***********************************************************************************************************************/
FUNC(void, PWM_PUBLIC_CODE) Pwm_Kernel_SetChannelOutput(void)                                                           /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucIndex;
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();

  if ((Pwm_GucKernelCoreId == LucCoreID) && (PWM_INITIALIZED == Pwm_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucIndex = 0U; LucIndex < PWM_TOTAL_CHANNELS_CONFIG; LucIndex++)
    {
      /* If request is not on going by Satellite */
      if(Pwm_CheckingRequest(Pwm_GaaSetChannelOutputBuffer[LucIndex].blSetReq))                                         /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

        /* Check if the buffer is locked */
        if(Pwm_UnLockedStatus(Pwm_GaaSetChannelOutputBuffer[LucIndex].blBufferLock))                                    /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          Pwm_LockProcess(Pwm_GaaSetChannelOutputBuffer[LucIndex].blBufferLock);                                        /* PRQA S 3432 # JV-01 */

          /* Release the spinlock */
          PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

          /* Updating the channel config parameter to the current channel */
          LucTimerUnitType = Pwm_GpChannelConfig[LucIndex].ucTimerUnitType;
          /* Check against null pointer */
          if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetChannelOutput)                                         /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low level driver for initializing the hardware */
            Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetChannelOutput(LucIndex,                                              /* PRQA S 0404 # JV-01 */
                                                                    Pwm_GaaSetChannelOutputBuffer[LucIndex].lddState);
          } /* else No action required */

          /* Clean request */
          Pwm_GaaSetChannelOutputBuffer[LucIndex].blSetReq = PWM_FALSE;

          /* Lock processing - notify that master is proceeded the request */
          Pwm_UnLockProcess(Pwm_GaaSetChannelOutputBuffer[LucIndex].blBufferLock);                                      /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    }
  } /* else No action required */
}
#endif /* #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON) */

#if (PWM_SET_TRIGGER_DELAY_API == STD_ON)
/***********************************************************************************************************************
** Function Name        : Pwm_Kernel_SetTriggerDelay
**
** Service ID           : None
**
** Description          : This kernel function will check all request from sattelite core, and proceed the request to
**                        hardware IP respectively.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None.
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : 1. PWM Driver should be initialized.
**                        2. This function is available only if the pre-compile option PWM_SET_TRIGGER_DELAY_API is
**                        STD_ON.
**                        3. The Kernel is scheduled function, which will be mapped to a period task
**
** Global Variables     : Pwm_GpChannelConfig
**
** Functions invoked    : Pwm_<HW-IP>_SetTriggerDelay
**
** Registers Used       : None
**
** Reference ID         : PWM_DUD_ACT_113, PWM_DUD_ACT_113_CRT001, PWM_DUD_ACT_113_CRT002, PWM_DUD_ACT_113_CRT003
** Reference ID         : PWM_DUD_ACT_113_GBL001
***********************************************************************************************************************/
FUNC(void, PWM_PUBLIC_CODE) Pwm_Kernel_SetTriggerDelay(void)                                                            /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucIndex;
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();

  if ((Pwm_GucKernelCoreId == LucCoreID) && (PWM_INITIALIZED == Pwm_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucIndex = 0U; LucIndex < PWM_TOTAL_CHANNELS_CONFIG; LucIndex++)
    {
      /* If request is not on going by Satellite */
      if(Pwm_CheckingRequest(Pwm_GaaSetTriggerDelayBuffer[LucIndex].blSetReq))                                          /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

        /* Check if the buffer is locked */
        if(Pwm_UnLockedStatus(Pwm_GaaSetTriggerDelayBuffer[LucIndex].blBufferLock))                                     /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          Pwm_LockProcess(Pwm_GaaSetTriggerDelayBuffer[LucIndex].blBufferLock);                                         /* PRQA S 3432 # JV-01 */

          /* Release the spinlock */
          PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

          /* Updating the channel config parameter to the current channel */
          LucTimerUnitType = Pwm_GpChannelConfig[LucIndex].ucTimerUnitType;
          /* Check against null pointer */
          if (NULL_PTR != Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetTriggerDelay)                                          /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low level driver for initializing the hardware */
            Pwm_GaaHwFunc[LucTimerUnitType]->pHWSetTriggerDelay(LucIndex,                                               /* PRQA S 0404 # JV-01 */
                                                          Pwm_GaaSetTriggerDelayBuffer[LucIndex].lusTriggerDelay);
          } /* else No action required */

          /* Clean request */
          Pwm_GaaSetTriggerDelayBuffer[LucIndex].blSetReq = PWM_FALSE;

          /* Lock processing - notify that master is proceeded the request */
          Pwm_UnLockProcess(Pwm_GaaSetTriggerDelayBuffer[LucIndex].blBufferLock);                                       /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    }
  } /* else No action required */
}
#endif /* #if (PWM_SET_TRIGGER_DELAY_API == STD_ON) */

#define PWM_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* PWM_MULTI_CORE_SUPPORT == STD_ON */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
