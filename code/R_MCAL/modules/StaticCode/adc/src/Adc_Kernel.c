/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = ADC_Kernel.c                                                                                        */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains kernel code for ADC                                                                             */
/* Driver                                                                                                             */
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
 * 2.1.3: 31/10/2024 : Update SW-VERSION 2.1.3
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 *                     As part of Multicore support, following changes are made:
 *                     1.Update to change ADC_KERNEL_COREID macro to global variable Adc_GucCoreIndex
 *                     2.Update to change ADC_MAX_SW_TRIGGER macro to global variable Adc_GucMaxSwTriggGroups
 * 2.0.1: 18/10/2023 : Fix acceptance findings by removing #include "Det.h"
 *                     Fix QAC Amendment 2, add message 0404
 * 2.0.0: 25/07/2023 : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Adc_Kernel.h"
#include "Adc.h"
#include "Adc_Ram.h"
#include "SchM_Adc.h"
#include "Adc_LLDriver.h"
#include "Adc_Cfg.h"
#if (ADC_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ADC_KERNEL_C_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION_VALUE
#define ADC_KERNEL_C_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION_VALUE
#define ADC_KERNEL_C_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ADC_KERNEL_C_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION_VALUE
#define ADC_KERNEL_C_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ADC_AR_RELEASE_MAJOR_VERSION != ADC_KERNEL_C_AR_RELEASE_MAJOR_VERSION)
  #error "Adc_Kernel.c : Mismatch in Release Major Version"
#endif

#if (ADC_AR_RELEASE_MINOR_VERSION != ADC_KERNEL_C_AR_RELEASE_MINOR_VERSION)
  #error "Adc_Kernel.c : Mismatch in Release Minor Version"
#endif

#if (ADC_AR_RELEASE_REVISION_VERSION != ADC_KERNEL_C_AR_RELEASE_REVISION_VERSION)
  #error "Adc_Kernel.c : Mismatch in Release Revision Version"
#endif

#if (ADC_SW_MAJOR_VERSION != ADC_KERNEL_C_SW_MAJOR_VERSION)
  #error "Adc_Kernel.c : Mismatch in Software Major Version"
#endif

#if (ADC_SW_MINOR_VERSION != ADC_KERNEL_C_SW_MINOR_VERSION)
  #error "Adc.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1503)    : The function 'name' is defined but is not used within this project.                          */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3387)    : A full expression containing an increment (++) or decrement (--) operator should have no     */
/*                       potential side effects other than that caused by the increment or decrement operator.        */
/* Rule                : MISRA C:2012 Rule-13.3                                                                       */
/* JV-01 Justification : An increment/decrement is created as a side effect. In this case, it's accessing a volatile  */
/*                       object. This can be accepted.                                                                */
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
/* Message (4:4461)    : A non-constant expression of 'essentially unsigned' type (%1s) is being converted to         */
/*                       narrower unsigned type, '%2s' on assignment.                                                 */
/* Rule                : MISRA C:2012 Rule-10.3, CERTCCM INT02, CWE Rule CWE-681, CWE-136, CWE-192                    */
/* JV-01 Justification : This operation is necessary to offset a 32-bit address on RAM to a 16-bit buffer address.    */
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
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (ADC_MULTI_CORE_SUPPORT == STD_ON)
/* Global scope - share among cores */
#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"

/* Globale scope - share among cores */

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
volatile VAR(Adc_GroupConfig_RequestType, ADC_VAR_NO_INIT) Adc_StartGroupConversionInfo[ADC_MAX_SW_TRIGGER];
volatile VAR(Adc_GroupConfig_RequestType, ADC_VAR_NO_INIT) Adc_StopGroupConversionInfo[ADC_MAX_SW_TRIGGER];
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
volatile VAR(Adc_GroupConfig_RequestType, ADC_VAR_NO_INIT) Adc_EnableHardwareTriggerInfo[ADC_MAX_HW_TRIGGER];
volatile VAR(Adc_GroupConfig_RequestType, ADC_VAR_NO_INIT) Adc_DisableHardwareTriggerInfo[ADC_MAX_HW_TRIGGER];
#endif

#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_MULTI_CORE_SUPPORT == STD_ON) */
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name         : Adc_Kernel_StartGroupConversion
**
** Service ID            : None
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
** Preconditions         : 1. Adc Driver should be initialized.
**                         2. The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Adc_GucMaxSwTriggGroups, Adc_GblDriverStatus, Adc_GucCoreIndex
**
** Functions invoked     : Adc_CheckingRequest, Adc_UnLockedStatus, Adc_LockProcess, Adc_HwStartGroupConversion, 
**                         Adc_UnLockProcess, ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
**
** Reference ID          : ADC_DUD_ACT_100
***********************************************************************************************************************/
#if (ADC_MULTI_CORE_SUPPORT == STD_ON)
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
#define ADC_START_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, ADC_PUBLIC_CODE) Adc_Kernel_StartGroupConversion(void)                                                       /* PRQA S 1503 # JV-01 */
{
  /* Declare a local variable for the current group ID */
  VAR(volatile uint8, AUTOMATIC) LucGroupIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by the OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */
  /* Check the kernel is called with valid core and module is initialize */
  if ((Adc_GucCoreIndex == LucCoreID) && (ADC_INITIALIZED == Adc_GblDriverStatus))                                     /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    for (LucGroupIndex = 0U; LucGroupIndex < Adc_GucMaxSwTriggGroups; LucGroupIndex++)                                  /* PRQA S 3387, 3416 # JV-01, JV-01 */
    {
      /* If request is a new request */
      if (Adc_CheckingRequest(Adc_StartGroupConversionInfo[LucGroupIndex].blSetRequest))                                /* PRQA S 3432, 0404, 3416 # JV-01, JV-01, JV-01 */
      {
        /* Get the spinlock */
        ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
        /* Check bufferlock status */
        if (Adc_UnLockedStatus(Adc_StartGroupConversionInfo[LucGroupIndex].blBufferLock))                               /* PRQA S 3432, 0404, 3416 # JV-01, JV-01, JV-01 */
        {
          /* Lock processing - notify the master is proceed the request */
          Adc_LockProcess(Adc_StartGroupConversionInfo[LucGroupIndex].blBufferLock);                                    /* PRQA S 3432 # JV-01 */
          /* Release the spinlock */
          ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
          /* Start the conversion */
          Adc_HwStartGroupConversion(LucGroupIndex);

          /* Clean request */
          Adc_StartGroupConversionInfo[LucGroupIndex].blSetRequest = ADC_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          Adc_UnLockProcess(Adc_StartGroupConversionInfo[LucGroupIndex].blBufferLock);                                  /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the sprinlock */
          ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
        }
      } /* else: no action required */
    }
  } /* else: no action required */
}
#define ADC_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Adc_Kernel_StopGroupConversion
**
** Service ID            : None
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
** Preconditions         : 1. Adc Driver should be initialized.
**                         2. The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Adc_GucMaxSwTriggGroups, Adc_GblDriverStatus, Adc_GucCoreIndex
**
** Functions invoked     : Adc_CheckingRequest, Adc_UnLockedStatus, Adc_LockProcess, Adc_HwStopGroupConversion,
**                         Adc_UnLockProcess, ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION 
**
** Registers Used        : None
**
** Reference ID          : ADC_DUD_ACT_101
***********************************************************************************************************************/
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
#define ADC_START_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, ADC_PUBLIC_CODE) Adc_Kernel_StopGroupConversion(void)                                                        /* PRQA S 1503 # JV-01 */
{
  VAR(volatile uint8, AUTOMATIC) LucGroupIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by the OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */
  /* Check the kernel is called with valid core and module is initialize */
  if ((Adc_GucCoreIndex == LucCoreID) && (ADC_INITIALIZED == Adc_GblDriverStatus))                                     /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    for (LucGroupIndex = 0U; LucGroupIndex < Adc_GucMaxSwTriggGroups; LucGroupIndex++)                                  /* PRQA S 3387, 3416 # JV-01, JV-01 */
    {
      /* If request is a new request */
      if (Adc_CheckingRequest(Adc_StopGroupConversionInfo[LucGroupIndex].blSetRequest))                                 /* PRQA S 3432, 0404, 3416 # JV-01, JV-01, JV-01 */
      {
        /* Get the spinlock */
        ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
        /*  Check bufferlock status */
        if (Adc_UnLockedStatus(Adc_StopGroupConversionInfo[LucGroupIndex].blBufferLock))                                /* PRQA S 3432, 0404, 3416 # JV-01, JV-01, JV-01 */
        {
          /* Lock processing - notify the master is proceed the request */
          Adc_LockProcess(Adc_StopGroupConversionInfo[LucGroupIndex].blBufferLock);                                     /* PRQA S 3432 # JV-01 */
          /* Release the spinlock */
          ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);

          /* Start the conversion */
          Adc_HwStopGroupConversion(LucGroupIndex);

          /* Clean request */
          Adc_StopGroupConversionInfo[LucGroupIndex].blSetRequest = ADC_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          Adc_UnLockProcess(Adc_StopGroupConversionInfo[LucGroupIndex].blBufferLock);                                   /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the sprinlock */
          ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
        }
      }
    }
  }
}
#define ADC_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Adc_Kernel_EnableHardwareTrigger
**
** Service ID            : None
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
** Preconditions         : 1. Adc Driver should be initialized first by working.
**                         2. The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Adc_GucNoOfGroups, Adc_GblDriverStatus, Adc_GucMaxSwTriggGroups, Adc_GucCoreIndex
**
** Functions invoked     : Adc_HwEnableHardwareTrigger, Adc_CheckingRequest, Adc_UnLockedStatus, Adc_LockProcess,
**                         Adc_UnLockProcess, ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
**
** Reference ID          : ADC_DUD_ACT_102
***********************************************************************************************************************/
#if (ADC_HW_TRIGGER_API == STD_ON)
#define ADC_START_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, ADC_PUBLIC_CODE) Adc_Kernel_EnableHardwareTrigger(void)                                                      /* PRQA S 1503 # JV-01 */
{
  VAR(volatile uint8, AUTOMATIC) LucGroupIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by the OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */
  /* Check the kernel is called with valid core and module is initialize */
  if ((Adc_GucCoreIndex == LucCoreID) && (ADC_INITIALIZED == Adc_GblDriverStatus))                                      /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    for (LucGroupIndex = Adc_GucMaxSwTriggGroups; LucGroupIndex < Adc_GucNoOfGroups; LucGroupIndex++)                   /* PRQA S 3387, 3416 # JV-01, JV-01 */
    {
      /* If request is a new request */
      if (Adc_CheckingRequest(Adc_EnableHardwareTriggerInfo[LucGroupIndex - Adc_GucMaxSwTriggGroups].blSetRequest))     /* PRQA S 3384, 3432, 0404, 3416 # JV-01, JV-01, JV-01, JV-01 */
      {
        /* Get the spinlock */
        #if (ADC_CRITICAL_SECTION_PROTECTION == STD_ON)
        /* Enter protect data */
        ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
        #endif
        /*  Check bufferlock status */
        if (Adc_UnLockedStatus(Adc_EnableHardwareTriggerInfo[LucGroupIndex - Adc_GucMaxSwTriggGroups].blBufferLock))    /* PRQA S 3384, 3432, 0404, 3416 # JV-01, JV-01, JV-01, JV-01 */
        {
          /* Lock processing - notify the master is proceed the request */
          Adc_LockProcess(Adc_EnableHardwareTriggerInfo[LucGroupIndex - Adc_GucMaxSwTriggGroups].blBufferLock);         /* PRQA S 3384, 3432 # JV-01, JV-01 */
          /* Release the spinlock */
          ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);

          /* Start the conversion */
          Adc_HwEnableHardwareTrigger(LucGroupIndex);

          /* Clean request */
          Adc_EnableHardwareTriggerInfo[LucGroupIndex - Adc_GucMaxSwTriggGroups].blSetRequest = ADC_FALSE;              /* PRQA S 3384 # JV-01 */
          /* Lock processing - notify that master is proceeded the request */
          Adc_UnLockProcess(Adc_EnableHardwareTriggerInfo[LucGroupIndex - Adc_GucMaxSwTriggGroups].blBufferLock);       /* PRQA S 3384, 3432 # JV-01, JV-01 */
        }
        else
        {
          /* Release the sprinlock */
          ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
        }
      }
    }
  }
}
#define ADC_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* ADC_HW_TRIGGER_API == STD_ON */

/***********************************************************************************************************************
** Function Name         : Adc_Kernel_DisableHardwareTrigger
**
** Service ID            : None
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
** Preconditions         : 1. Adc Driver should be initialized first by working.
**                         2. The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Adc_GucNoOfGroups, Adc_GblDriverStatus, Adc_GucMaxSwTriggGroups, Adc_GucCoreIndex
**
** Functions invoked     : Adc_HwDisableHardwareTrigger, Adc_CheckingRequest, Adc_UnLockedStatus, Adc_LockProcess,
**                         Adc_UnLockProcess, ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION 
**
** Registers Used        : None
**
** Reference ID          : ADC_DUD_ACT_103, ADC_DUD_ACT_007
***********************************************************************************************************************/
#if (ADC_HW_TRIGGER_API == STD_ON)
#define ADC_START_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, ADC_PUBLIC_CODE) Adc_Kernel_DisableHardwareTrigger(void)                                                     /* PRQA S 1503 # JV-01 */
{
  VAR(volatile uint8, AUTOMATIC) LucGroupIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by the OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */
  /* Check the kernel is called with valid core and module is initialize */
  if ((Adc_GucCoreIndex == LucCoreID) && (ADC_INITIALIZED == Adc_GblDriverStatus))                                      /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    for (LucGroupIndex = Adc_GucMaxSwTriggGroups; LucGroupIndex < Adc_GucNoOfGroups; LucGroupIndex++)                   /* PRQA S 3387, 3416 # JV-01, JV-01 */
    {
      /* If request is a new request */
      if (Adc_CheckingRequest(Adc_DisableHardwareTriggerInfo[LucGroupIndex - Adc_GucMaxSwTriggGroups].blSetRequest))    /* PRQA S 3384, 3432, 0404, 3416 # JV-01, JV-01, JV-01, JV-01 */
      {
        /* Get the spinlock */
        ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
        /*  Check bufferlock status */
        if (Adc_UnLockedStatus(Adc_DisableHardwareTriggerInfo[LucGroupIndex - Adc_GucMaxSwTriggGroups].blBufferLock))   /* PRQA S 3384, 3432, 0404, 3416 # JV-01, JV-01, JV-01, JV-01 */
        {
          /* Lock processing - notify the master is proceed the request */
          Adc_LockProcess(Adc_DisableHardwareTriggerInfo[LucGroupIndex - Adc_GucMaxSwTriggGroups].blBufferLock);        /* PRQA S 3384, 3432 # JV-01, JV-01 */
          /* Release the spinlock */
          ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);

          /* Start the conversion */
          Adc_HwDisableHardwareTrigger(LucGroupIndex);

          /* Clean request */
          Adc_DisableHardwareTriggerInfo[LucGroupIndex - Adc_GucMaxSwTriggGroups].blSetRequest = ADC_FALSE;             /* PRQA S 3384 # JV-01 */
          /* Lock processing - notify that master is proceeded the request */
          Adc_UnLockProcess(Adc_DisableHardwareTriggerInfo[LucGroupIndex - Adc_GucMaxSwTriggGroups].blBufferLock);      /* PRQA S 3384, 3432 # JV-01, JV-01 */
        }
        else
        {
          /* Release the sprinlock */
          ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
        }
      }
    }
  }
}
#define ADC_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* ADC_HW_TRIGGER_API == STD_ON */
#endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
