/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt.c                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains API function implementations of GPT Driver                                                      */
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
 *  2.4.1  30/06/2025  : As part of QAC 11.6.0 support, following changes are made:
 *                       + Add QAC message 2982
 *  2.4.0  30/06/2025  : As part of QAC 11.6.0 support, following changes are made:
 *                       + Remove message header 2812
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *                        As part of QAC 11.6.0 support, following changes are made:
 *                        1. Remove QAC message 2962
 *                        2. Add QAC message 2813, 2812, 2997.
 *                        3. Remove QAC message 3415 from condition check kernel core and OSTM unit in Gpt_Init and
 *                        Gpt_DeInit, QAC message 2982 from get core index in Gpt_DeInit
 *  2.3.0  28/02/2025   : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024   : Update SW-VERSION for U2Bx Beta2 release
 *  2.1.1  30/08/2024   : As part of QAC 9.5.0 support, following changes are made
 *                        1.Update to support QAC 9.5.0
 *                      : As part of ARDAACL-47288, following changes are made
 *                        1.Add pre-compile condition for the local variable LucCoreId in Gpt_StartTimer, Gpt_StopTimer,
 *                        Gpt_EnableNotification, Gpt_DisableNotification
 *                      : As part of Post Build multiple varriant support, following changes are made
 *                        1.In Gpt_SetMode: Remove DET check for GPT_E_UNINIT due to duplicate with Gpt_CheckDetErrors
 *                        2.In Gpt_SetMode, Gpt_CheckWakeup, Gpt_GetPredefTimerValue, add condition check for variable
 *                        Gpt_GucKernelCoreId before using it as an index of Gpt_GaaCoreId2Index
 *                        only using for reporting DET and not for returning value
 *                        3.In Gpt_DeInit, Gpt_CheckWakeup, Gpt_GetPredefTimerValue, Gpt_CheckDetErrors:
 *                        - Add condition check for Gpt_GucKernelCoreId for DET GPT_E_UNINIT
 *                        4.Change using from marco GPT_KERNEL_CORE_ID to global variable Gpt_GucKernelCoreId
 *                        5.In Gpt_Init:
 *                        - Add step to assign the value of configured Kernel core ID to Gpt_GucKernelCoreId
 *                        - Move check DET check for GPT_E_INIT_FAILED to the top before using Gpt_GucKernelCoreId
 *                        As part of ARDAACL-42219, following changes are made
 *                        1.In Gpt_GetPredefTimerValue, correct position of condition GPT_DEV_ERROR_DETECT == STD_ON
 *                      : As part of QAC 9.5.0 support, following changes are made
 *                        1.Add QAC message 3415, 3416, 2962, 3432, 2991, 2995
 *  2.0.1  17/10/2023   : In Gpt_DeInit, Gpt_CheckWakeup, Gpt_GetPredefTimerValue, Gpt_CheckDetErrors:
 *                        move error check for GPT_E_UNINIT to be performed firstly;
 *                        In Gpt_SetMode, add condition to LpRamData branching in case of multicore;
 *                        Update preprocessor GPT_AR_R21_11_VERSION to GPT_AR_R22_11_VERSION
 *                        Update QAC message: remove 2844, 2814, 2824, 2934 and add 0404
 *                        In Gpt_EnableNotification, Gpt_DisableNotification, Gpt_StopTimer, Gpt_SetMode, seperate
 *                        critical section for multicore type II, type III and singlecore support
 *                        Move DET check of GPT_E_INVALID_CORE, GPT_E_UNINIT in Gpt_SetMode to Gpt_CheckDetErrors
 *                        Update comment description in all APIs
 *         21/09/2023   : In Gpt_GetPredefTimerValue, change position of LucChannelID initilization
 *                        Gpt_Init: remove condition for statement to set the Driver Mode to Normal,
 *                        add preprocessor GPT_TYPE_III_SUPPORT == STD_ON for HWUnitInit initialization.
 *                        Gpt_DeInit, Gpt_StartTimer, Gpt_StopTimer, Gpt_EnableNotification, Gpt_DisableNotification:
 *                        add preprocessor GPT_TYPE_II_SUPPORT for code block containing assigning pChannelRamData to
 *                        LpRamData; Update QAC message comment; Remove 2996, 2985 QAC message header;
 *                        In Gpt_CheckWakeup(), remove LddReturnValue and re-arrange position of variable initialization
 *                        In Gpt_SetMode, update value of LucAccPointIdx in case of multicore
 *  2.0.0  20/08/2023   : In Gpt_DeInit, change LucCount to LucChannelID in do while loop
 *                        In Gpt_GetPredefTimerValue, change (LucAccPointIdx & GPT_CORE_MASK) to GPT_KERNEL_CORE_ID
 *                        in DET check
 *                        Remove redundant assignment in Gpt_StartTimer, Gpt_StopTimer, Gpt_StartTimer,
 *                        Gpt_DisableNotification, Gpt_EnableNotification
 *                        Update SID report DET in Gpt_DeInit, Gpt_SetMode, Gpt_CheckWakeup, Gpt_GetPredefTimerValue
 *         26/07/2023   : Update to support multi-core as below:
 *                        - In all API: update Global Variables, comment, Add new det check for error GPT_E_INVALID_CORE
 *                        - Change access approach: Access Gpt_GpChannelConfig, Gpt_GblDriverStatus via
 *                          Gpt_GaaGlobalAccPoint for each core; Gpt_GpChannelRamData is seperated into type II,
 *                          type III and single core: in case of multi-core, access to data of OSTM, access via
 *                          Gpt_GaaGlobalAccPoint to Gpt_GaaChannelRamData_CoreX(X is core id) and access to data of
 *                          ATU/TAUD/TAUJ channel directly via Gpt_GaaChannelRamData; in case of single-core,
 *                          access to all channels data via Gpt_GaaChannelRamData
 *                        - add Os.h in case multi-core
 *                        - change Gpt_Mapping.h to Gpt_MemMap.h
 *                        - Gpt_CheckDetErrors: add new input parameter: LucCoreId
 *                        - Gpt_SetStatus: add new input parameter LucAccPointIdx
 *                        - Gpt_Init: Remove det check for GPT_E_PARAM_POINTER due to redundant checking
 *                        - add qac messages, Change Gpt_Mapping.h to Gpt_MemMap.h, Add CWE QAC header
 *         12/06/2023   : Update pre-processor GPT_AR_VERSION == GPT_AR_R21_11_VERSION
 *         12/05/2023   : Update description for all APIs
 *                        Update API Gpt_Setmode() to reduce STCYC<=20
 *  1.4.5  02/12/2022   : Add pre-processor GPT_AR_VERSION == GPT_AR_2111_VERSION for support AR21-11,
 *                        Update SW-VERSION to 1.4.5
 *         08/06/2022   : Update the Channel No. with maximum number of Channel configured to break loop when reaching
 *                        channel which is wake up source in Gpt_CheckWakeup();
 *                        Update SW-VERSION to 1.4.4
 *  1.4.3  06/05/2022   : Remove "else" statement when no action required; add QAC message 2004.
 *         17/04/2022   : Merge QAC message from U2Ax, E2x and U2Bx
 *  1.3.2  22/08/2021   : Changed Gpt_MemMap.h to Gpt_Mapping.h.
 *  1.3.1  02/07/2021   : Add QAC message 9.5.0
 *                        Format source code to 120 characters
 *                        Improve Violation tag (remove START/END)
 *         15/05/2021   : Fixed Coding Rule and tailor space.
 *  1.3.0  21/01/2021   : Change argument name in Gpt_GetPredefTimerValue(): from TimerValuePtr to TimeValuePtr
 *         20/01/2021   : Change Compiler abstraction symbols of argument in 2 APIs follow AUTOSAR requirement:
 *                        1. VersionInfoPtr in Gpt_GetVersionInfo(): from CONSTP2VAR to P2VAR
 *                        2. ConfigPtr in Gpt_Init(): from CONSTP2CONST to P2CONST
 *  1.2.0  17/07/2020   : Release
 *  1.1.0  19/06/2020   : Release
 *         02/06/2020   : Fix in Gpt_CheckWakeup(), change order of Critical Section
 *         27/05/2020   : Unify pre-compile macro in all Api [Det_ReportError]
 *         25/05/2020   : 1.Change Condition in API Gpt_DisableWakeup() from pDisableInterrupt to pDisableWakeup
 *                        2.Remove Redundant Critical Section in Gpt_CheckWakeup() in #270097
 *         14/05/2020   : 1.Add Condition to Report invalid Predef Timer Type if Gentool output config 100US but
 *                          input 1US in Gpt_GetPredefTimerValue(), ticket #259857
 *                        2.Define Unspecified Section in boundary Gpt_GaaHwFunc[]
 *                          Change Gpt_GaaHwFunc[] into file Gpt_Ram.h
 *         12/05/2020   : Add volatile when define local variable #263778
 *         18/03/2020   : 1.Change use increment pointer to use local variable increment by loop in
 *                          Gpt_DeInit/Gpt_SetMode/ Gpt_CheckWakeup
 *                        2.Add condition of GPT_DEV_ERROR_DETECT == STD_ON
 *                          on the last curly brackets in Gpt_GetPredefTimerValue
 *         16/03/2020   : 1.Add Function: SetStatus
 *                        2.Change do/while loop into for loop in 3 function Gpt_DeInit/Gpt_SetMode/Gpt_CheckWakeup
 *         10/03/2020   : 1.As per Redmine #259284, update in API Gpt_GetPredefTimerValue move the return value return
 *                          E_NOT_OK out of condition  error detection is enabled
 *                        2.As per Redmine #259267, Remove redundant of Critical section protection in Gpt_EnableWakeup
 *                          and Gpt_DisableWakeup APIs.
 *                        3.As per Redmine #259261, Add Critical section protection GPT_INTERRUPT_CONTROL_PROTECTION
 *                          in APISetMode before calling Gpt_<HWIP>_EnableInterrupt and Gpt_<HWIP>_DisableInterrupt.
 *                        4.As per Redmine #255925, update in Included Det.h
 *                          for the declaration of Det_ReportRuntimeError()
 *  1.0.0  01/01/2020   : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
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
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : MISRA C:2012 Rule-15.7, CERTCCM MSC01, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2962)    : Apparent: Using value of uninitialized automatic object '%s'.                                */
/* Rule                : CERTCCM EXP33, MISRA C:2012 Rule-9.1                                                         */
/* JV-01 Justification : It will be initialized based on scope of 'if' statements  where at least an 'if' statement   */
/*                       will be executed that will initialize the variable.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563,     */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2991)    : The value of this 'if' controlling expression is always 'true'.                              */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2995)    : The result of this logical operation is always 'true'.                                       */
/* Rule                : MISRA C:2012 Rule-2.2, CWE Rule CWE-561, CWE-633                                             */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3206)    : The parameter '%s' is not used in this function.                                             */
/* Rule                : MISRA C:2012 Rule-2.7, CERTCCM MSC07, MSC13, CWE Rule CWE-398, CWE-563, CWE-569              */
/* JV-01 Justification : This is done as per implementation requirement                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
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
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : This is accepted. It is just advice for improve safety by reducing the possibility that the  */
/*                       referenced data is unintentionally modified through an unexpected alias and improves         */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it                                                               */
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
/* Included for macro definitions (e.g. Service IDs)*/
#include "Gpt.h"
/* Included for Global Data Types */
#include "Gpt_Ram.h"
/* Included for the declaration of Det_ReportError(), Det_ReportRuntimeError()*/
#if ((GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_AR_VERSION == GPT_AR_431_VERSION)|| \
  (GPT_AR_VERSION == GPT_AR_R22_11_VERSION))
#include "Det.h"
#endif
#if (GPT_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define GPT_C_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_C_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_C_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define GPT_C_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION_VALUE
#define GPT_C_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (GPT_AR_RELEASE_MAJOR_VERSION != GPT_C_AR_RELEASE_MAJOR_VERSION)
  #error "Gpt.c : Mismatch in Release Major Version"
#endif
#if (GPT_AR_RELEASE_MINOR_VERSION != GPT_C_AR_RELEASE_MINOR_VERSION)
  #error "Gpt.c : Mismatch in Release Minor Version"
#endif
#if (GPT_AR_RELEASE_REVISION_VERSION != GPT_C_AR_RELEASE_REVISION_VERSION)
  #error "Gpt.c : Mismatch in Release Revision Version"
#endif
#if (GPT_SW_MAJOR_VERSION != GPT_C_SW_MAJOR_VERSION)
  #error "Gpt.c : Mismatch in Software Major Version"
#endif
#if (GPT_SW_MINOR_VERSION != GPT_C_SW_MINOR_VERSION)
  #error "Gpt.c : Mismatch in Software Minor Version"
#endif

/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"
#if (GPT_DEV_ERROR_DETECT == STD_ON)
STATIC FUNC(Std_ReturnType, GPT_PRIVATE_CODE)
                                  Gpt_CheckDetErrors(Gpt_ChannelType LddChannel, uint8 LucApi_SID, uint8 LucCoreId);
#endif

STATIC FUNC(void, GPT_PRIVATE_CODE) Gpt_SetStatus(boolean LblStatusType, uint8 LucAccPointIdx);
#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Gpt_GetVersionInfo
**
** Service ID            : 0x00
**
** Description           : This API returns the version information of GPT
**                         driver component.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : VersionInfoPtr
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : None
**
** Functions invoked     : Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_001, GPT_DUD_ACT_001_ERR001
***********************************************************************************************************************/
#if (GPT_VERSION_INFO_API == STD_ON)
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PUBLIC_CODE) Gpt_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, GPT_APPL_DATA) VersionInfoPtr)     /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == VersionInfoPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_VERSION_INFO_SID, GPT_E_PARAM_POINTER);
  }
  else
  #endif
  {
    VersionInfoPtr->vendorID = (uint16)GPT_VENDOR_ID;
    VersionInfoPtr->moduleID = (uint16)GPT_MODULE_ID;
    VersionInfoPtr->sw_major_version = (uint8)GPT_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = (uint8)GPT_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = (uint8)GPT_SW_PATCH_VERSION;
  }
}
#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (GPT_VERSION_INFO_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_Init
**
** Service ID            : 0x01
**
** Description           : This API performs the initialization of GPT Driver component.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non Reentrant
**
** Input Parameters      : ConfigPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GpPredefTimerConfig, Gpt_GucDriverMode
**                         Gpt_GaaHWIP, Gpt_GaaHwFunc, Gpt_GaaCoreId2Index, Gpt_GaaChannel2IpType, Gpt_GucKernelCoreId
**
** Functions invoked     : Gpt_HW_Atu_UnitInit, Gpt_HW_Taud_UnitInit, Gpt_HW_Tauj_UnitInit
**                         Gpt_HW_Atu_ChannelInit, Gpt_HW_Ostm_ChannelInit, Gpt_HW_Taud_ChannelInit
**                         Gpt_HW_Tauj_ChannelInit, Gpt_HW_Atu_StartPredefTimer, Gpt_HW_Tauj_StartPredefTimer
**                         Det_ReportError, Gpt_SetStatus
**                         Gpt_HW_Gtm_UnitInit, Gpt_HW_Gtm_ChannelInit, Gpt_HW_Gtm_StartPredefTimer
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_002, GPT_DUD_ACT_002_ERR001, GPT_DUD_ACT_002_ERR002
** Reference ID          : GPT_DUD_ACT_002_ERR003, GPT_DUD_ACT_002_ERR004, GPT_DUD_ACT_002_GBL001
** Reference ID          : GPT_DUD_ACT_002_GBL002, GPT_DUD_ACT_002_GBL003, GPT_DUD_ACT_002_GBL004
** Reference ID          : GPT_DUD_ACT_002_MUI001, GPT_DUD_ACT_002_MUI002, GPT_DUD_ACT_002_MUI003
** Reference ID          : GPT_DUD_ACT_002_MUI004, GPT_DUD_ACT_002_GLB030, GPT_DUD_ACT_002_GLB005
***********************************************************************************************************************/
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PUBLIC_CODE) Gpt_Init(P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_APPL_CONST) ConfigPtr)                      /* PRQA S 1503 # JV-01 */
{
  /* Index of loop count */
  VAR(volatile uint8, AUTOMATIC) LucCount;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Variable to access global access point */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Assigned cores of a particular channel */
  VAR(uint8, AUTOMATIC) LucCoreIndexPerChannel;
  /* Variable to get core id */
  VAR(uint8, AUTOMATIC) LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucAccPointIdx = Gpt_GaaCoreId2Index[LucCoreId];
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif

  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Check if configure pointer is NULL pointer */
  if (NULL_PTR == ConfigPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_INIT_SID, GPT_E_INIT_FAILED);
  } /* else No action required */
  else
  #endif /* End of GPT_DEV_ERROR_DETECT == STD_ON */
  {
    #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
    /* Get the configured Kernel core ID */
    Gpt_GucKernelCoreId = ConfigPtr->ucKernelCoreId;
    #endif /* End of (GPT_MULTI_CORE_SUPPORT == STD_ON) */

    #if (GPT_DEV_ERROR_DETECT == STD_ON)
    #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
    /* Check if core is invalid */
    if(GPT_INVALID_CORE == LucAccPointIdx)
    {
      /* Report to DET */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_INIT_SID, GPT_E_INVALID_CORE);
    }
    /* Check if current core is not kernel core and not exist any OSTM channel on current core */
    else if ((Gpt_GucKernelCoreId != LucCoreId) && (GPT_ZERO == (LucAccPointIdx & (~GPT_CORE_MASK))))
    {
      /* Report to DET */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_INIT_SID, GPT_E_INVALID_CORE);
    }
    else
    #endif /* End of GPT_MULTI_CORE_SUPPORT == STD_ON */
    #if (GPT_ALREADY_INIT_DET_CHECK == STD_ON)
    /* Check if the GPT Driver is already Initialized */
    if (GPT_INITIALIZED == *(Gpt_GaaGlobalAccPoint[(LucAccPointIdx & GPT_CORE_MASK)].pDriverState))
    {
      /* Report to DET */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_INIT_SID, GPT_E_ALREADY_INITIALIZED);
    } /* else No action required */
    else
    #endif /* End of GPT_ALREADY_INIT_DET_CHECK == STD_ON */
    #endif /* End of GPT_DEV_ERROR_DETECT == STD_ON */
    {
      /* Check whether the existing database is correct */
      if (GPT_DBTOC_VALUE == ConfigPtr->ulStartOfDbToc)
      {
        /* Get the access point index */
        LucAccPointIdx &= GPT_CORE_MASK;
        /* Store the global pointer to first Channel Configuration */
        *(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig) =
                    (P2CONST(Gpt_ChannelConfigType, GPT_VAR_NO_INIT, GPT_CONFIG_CONST))ConfigPtr->pChannelConfig;       /* PRQA S 0316 # JV-01 */

        /* Predef is available on kernel core - type III only */
        #if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
        #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
        if(Gpt_GucKernelCoreId == LucCoreId)
        #endif
        {
          /* Store the global pointer to first Predef Timer Configuration */
          Gpt_GpPredefTimerConfig =
              (P2CONST(Gpt_PredefTimerConfigType, GPT_VAR_NO_INIT, GPT_CONFIG_CONST))ConfigPtr->pPredefTimerConfig;     /* PRQA S 0316 # JV-01 */
        }/* else No action required */
        #endif
        for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_HW_IP_CONFIG; LucCount++)                          /* PRQA S 3387, 3416 # JV-01, JV-01 */
        {
          /* Get unit type */
          LucHWIPType = Gpt_GaaHWIP[LucCount].ucIndex;
          if (NULL_PTR != Gpt_GaaHwFunc[LucHWIPType]->pHWUnitInit)                                                      /* PRQA S 3416 # JV-01 */
          {
            /* If kernel core - for other than OSTM, OSTM has not UnitInit function */
            #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
            #if (GPT_TYPE_III_SUPPORT == STD_ON)
            if (Gpt_GucKernelCoreId == LucCoreId)
            #endif
            #endif
            {
              /* Invoke low level driver for initializing the hardware */
              Gpt_GaaHwFunc[LucHWIPType]->pHWUnitInit(ConfigPtr);
            } /* else No action required */
          } /* else No action required */
        }

        for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_CHANNELS_CONFIG; LucCount++)                       /* PRQA S 3387, 3416 # JV-01, JV-01 */
        {
          /* Read the Timer Type for given channel */
          LucHWIPType = Gpt_GaaChannel2IpType[LucCount];
          #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
          /* Get core index as per channel */
          LucCoreIndexPerChannel = (*(Gpt_GaaGlobalAccPoint[LucAccPointIdx]).pChannelConfig)[LucCount].ucCoreIndex;

          /* If kernel core - for other than OSTM, OSTM has not UnitInit function */
          /* Not OSTM - init all in kernel core */
          if (((GPT_HWIP_OSTM != LucHWIPType) && (Gpt_GucKernelCoreId == LucCoreId))                                    /* PRQA S 3416 # JV-01 */
              /* OSTM - Init follow channel assignment for each core */
              || ((GPT_HWIP_OSTM == LucHWIPType) && (LucCoreIndexPerChannel == (GPT_ONE << LucCoreId))))                /* PRQA S 3415, 3416 # JV-01, JV-01 */
          #endif
          {
            if (NULL_PTR != Gpt_GaaHwFunc[LucHWIPType]->pHWChannelInit)                                                 /* PRQA S 3416 # JV-01 */
            {
              /* Invoke low level driver for initializing the hardware */
              Gpt_GaaHwFunc[LucHWIPType]->pHWChannelInit((Gpt_ChannelType)LucCount);                                    /* PRQA S 0404 # JV-01 */
            } /* else No action required */
          } /* else No action required */
        }

        #if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
        /* Predef is available for kernel core only (OSTM does not support predef) */
        #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
        if(Gpt_GucKernelCoreId == LucCoreId)
        #endif
        {
          for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_PREDEF_CHANNELS_CONFIG; LucCount++)              /* PRQA S 3387, 3416 # JV-01, JV-01 */
          {
            if (NULL_PTR != Gpt_GaaHwFunc[Gpt_GpPredefTimerConfig[LucCount].ucPredefTimerType]->pStartPredefTimer)      /* PRQA S 3416 # JV-01 */
            {
            /* Invoke low level driver for Initializing the GPT PreDef registers */
              Gpt_GaaHwFunc[Gpt_GpPredefTimerConfig[LucCount].ucPredefTimerType]->pStartPredefTimer();
            } /* else No action required */
          }
        }/* else No action required */
        #endif
        /* Set Driver state to Initialized */
        Gpt_SetStatus(GPT_INITIALIZED, LucAccPointIdx);
        /* Set the Driver Mode to Normal */
        Gpt_GucDriverMode = GPT_MODE_NORMAL;
      } /* End of ConfigPtr->ulStartOfDbToc) == GPT_DBTOC_VALUE */
      else
      {
        #if (GPT_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_INIT_SID, GPT_E_INVALID_DATABASE);
        #endif
      }
    } /* End of if (GPT_INITIALIZED == *(Gpt_GaaGlobalAccPoint[(LucAccPointIdx & GPT_CORE_MASK)].pDriverState)) */
  } /* End of (NULL_PTR == ConfigPtr) */
} /* End of API Gpt_Init */

#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_DeInit
**
** Service ID            : 0x02
**
** Description           : This service performs de-initialization of the GPT Driver component.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Gpt_Init must be called before this function.
**
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GpPredefTimerConfig, Gpt_GaaHWIP, Gpt_GucKernelCoreId
**                         Gpt_GaaHwFunc, Gpt_GaaCoreId2Index, Gpt_GaaChannel2IpType, Gpt_GaaChannelRamData
**
** Functions invoked     : Gpt_HW_Atu_StopPredefTimer, Gpt_HW_Tauj_StopPredefTimer, Gpt_HW_Taud_UnitDeInit
**                         Gpt_HW_Tauj_UnitDeInit, Gpt_HW_Atu_ChannelDeInit, Gpt_HW_Ostm_ChannelDeInit
**                         Gpt_HW_Taud_ChannelDeInit, Gpt_HW_Tauj_ChannelDeInit, Det_ReportError, Gpt_SetStatus,
**                         GPT_DET_REPORT_ERROR
**                         Gpt_HW_Gtm_UnitDeInit, pt_HW_Gtm_ChannelDeInit, Gpt_HW_Gtm_StopPredefTimer
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_003, GPT_DUD_ACT_003_ERR001, GPT_DUD_ACT_003_ERR002, GPT_DUD_ACT_003_ERR003
** Reference ID          : GPT_DUD_ACT_003_GLB030, GPT_DUD_ACT_003_MUI001, GPT_DUD_ACT_003_MUI002,
** Reference ID          : GPT_DUD_ACT_003_MUI003, GPT_DUD_ACT_003_MUI004, GPT_DUD_ACT_003_ERR004,
** Reference ID          : GPT_DUD_ACT_003_GLB001
***********************************************************************************************************************/
#if (GPT_DE_INIT_API == STD_ON)
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PUBLIC_CODE) Gpt_DeInit(void)                                                                            /* PRQA S 1503 # JV-01 */
{
  /* Index of loop count */
  VAR(volatile uint8, AUTOMATIC) LucCount;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  #if ((GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_AR_VERSION == GPT_AR_431_VERSION) || \
    (GPT_AR_VERSION == GPT_AR_R22_11_VERSION))
  /* Defining a local pointer to point to the Channel Ram Data */
  P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_VAR_NO_INIT) LpRamData;                                         /* PRQA S 3678 # JV-01 */
    /* Declare a local pointer to point to the Channel Config Data */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Initialize local variable to first Channel */
  VAR(uint8, AUTOMATIC) LucChannelID;
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnValue;
  #endif
  /* Variable to access global access point */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  /* Variable to access channel RAM data */
  VAR(uint8, AUTOMATIC) LucChannelIndex;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Variable to get core id */
  VAR(uint8, AUTOMATIC) LucCoreId;
  /* Assigned cores of a particular channel */
  VAR(uint8, AUTOMATIC) LucCoreIndexPerChannel;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucAccPointIdx = Gpt_GaaCoreId2Index[LucCoreId];
  #else
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif

  /* Initialize for loop count variable */
  LucCount = GPT_ZERO;

  #if ((GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_AR_VERSION == GPT_AR_431_VERSION) || \
    (GPT_AR_VERSION == GPT_AR_R22_11_VERSION))
  /* Initialize return value */
  LddReturnValue = E_OK;
  /* Initialize Channel ID */
  LucChannelID = (uint8)GPT_ZERO;
  #endif /* (GPT_DEV_ERROR_DETECT == STD_ON) ||(GPT_AR_VERSION == GPT_AR_431_VERSION) || \
    (GPT_AR_VERSION == GPT_AR_R22_11_VERSION) */
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Check if core is invalid */
  if((GPT_INVALID_CORE == LucAccPointIdx) ||
  /* Check if current core is not kernel core and not exist any OSTM channel on current core and the*/
    ((Gpt_GucKernelCoreId != LucCoreId) && (GPT_ZERO == (LucAccPointIdx & (~GPT_CORE_MASK))) && 
    (GPT_INVALID_CORE != Gpt_GucKernelCoreId)))
  {
    /* Report to DET */
    (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DEINIT_SID, GPT_E_INVALID_CORE);
    /* Set Return value */
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  /* Check if the GPT Driver is Initialized properly */
  if ((GPT_INITIALIZED != *(Gpt_GaaGlobalAccPoint[(LucAccPointIdx & GPT_CORE_MASK)].pDriverState))
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
      || (GPT_INVALID_CORE == Gpt_GucKernelCoreId)
  #endif /* (GPT_MULTI_CORE_SUPPORT == STD_ON) */
  ) 
  {
    /* Report to DET */
    (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DEINIT_SID, GPT_E_UNINIT);
    /* Set return value */
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif /* (GPT_DEV_ERROR_DETECT == STD_ON) */
  #if ((GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_AR_VERSION == GPT_AR_431_VERSION) || \
      (GPT_AR_VERSION == GPT_AR_R22_11_VERSION))
  {
    #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
    /* Get index of accesspoint by value of 4 low bits*/
    LucAccPointIdx &= GPT_CORE_MASK;
    #endif
    do
    {
      /* Read the Timer Type for given channel */
      LucHWIPType = Gpt_GaaChannel2IpType[LucChannelID];
      /* Update the local pointer to Channel config */
      LpChannel = *(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig);
      /* Get the index of channel */
      LucChannelIndex = LpChannel[LucChannelID].ucRamDataIndex;
      #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
      /* Get core index as per channel */
      LucCoreIndexPerChannel = LpChannel[LucChannelID].ucCoreIndex;                                                     /* PRQA S 2982 # JV-01 */
      #if (GPT_TYPE_II_SUPPORT == STD_ON)
      /* If channel type is OSTM and is mapped to current core */
      if ((GPT_HWIP_OSTM == LucHWIPType) && (LucCoreIndexPerChannel == (GPT_ONE << LucCoreId)))                         /* PRQA S 3416 # JV-01 */
      {
        /* Load the global pointer to local pointer */
        LpRamData = &(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelRamData)[LucChannelIndex];
      }/* else No action required */
      #endif
      #if (GPT_TYPE_III_SUPPORT == STD_ON)
      /* If channel type is not OSTM */
      if (GPT_HWIP_OSTM != LucHWIPType)                                                                                 /* PRQA S 3416 # JV-01 */
      {
        /* Load the global pointer to local pointer */
        LpRamData = &Gpt_GaaChannelRamData[LucChannelIndex];
      } /* else No action required */
      #endif
      #else
      /* Load the global pointer to local pointer */
      LpRamData = &Gpt_GaaChannelRamData[LucChannelIndex];
      #endif
      /* Check if the Channel is in Running State */
      if (GPT_CH_RUNNING == LpRamData->ucChannelStatus)                                                                 /* PRQA S 2962 # JV-01 */
      {
        /* Set return value */
        LddReturnValue = E_NOT_OK;
      }/* else No action required */
      /* Increment the Channel ID count */
      LucChannelID++;                                                                                                   /* PRQA S 3383 # JV-01 */
    } while (((uint8)GPT_TOTAL_CHANNELS_CONFIG != LucChannelID) && (E_OK == LddReturnValue));

    /* Check if the Channel is in Running State */
    if (E_NOT_OK == LddReturnValue)
    {
      /* Report to Development Errors */
      GPT_DET_REPORT_ERROR(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DEINIT_SID, GPT_E_BUSY);
    } /* else No action required */
  }
  /* Check if any DET error was reported */
  if (E_OK == LddReturnValue)
  #endif /* (GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_AR_VERSION == GPT_AR_431_VERSION) || \
    (GPT_AR_VERSION == GPT_AR_R22_11_VERSION)*/
  {
    /* Set Driver state to uninitialized */
    Gpt_SetStatus(GPT_UNINITIALIZED, LucAccPointIdx);

    #if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
    /* Predef is available for kernel core only (OSTM does not support predef) */
    #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
    if(Gpt_GucKernelCoreId == LucCoreId)
    #endif
    {
      for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_PREDEF_CHANNELS_CONFIG; LucCount++)                  /* PRQA S 3387, 3416 # JV-01, JV-01 */
      {
        if (NULL_PTR != Gpt_GaaHwFunc[Gpt_GpPredefTimerConfig[LucCount].ucPredefTimerType]->pStopPredefTimer)           /* PRQA S 3416 # JV-01 */
        {
          /* Invoke low level driver for De-Initializing the GPT PreDef registers */
          Gpt_GaaHwFunc[Gpt_GpPredefTimerConfig[LucCount].ucPredefTimerType]->pStopPredefTimer();
        } /* else No action required */
      }
    }/* else No action required */
    #endif

    for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_HW_IP_CONFIG; LucCount++)                              /* PRQA S 3387, 3416 # JV-01, JV-01 */
    {
      /* Get unit type */
      LucHWIPType = Gpt_GaaHWIP[LucCount].ucIndex;
      if (NULL_PTR != Gpt_GaaHwFunc[LucHWIPType]->pHWUnitDeInit)                                                        /* PRQA S 3416 # JV-01 */
      {
        /* If kernel core - for other than OSTM, note: OSTM has not UnitInit function */
        #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
        if (Gpt_GucKernelCoreId == LucCoreId)
        #endif
        {
          /* Invoke low level driver for De-initializing the hardware */
          Gpt_GaaHwFunc[LucHWIPType]->pHWUnitDeInit();
        } /* else No action required */
      } /* else No action required */
    }

    for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_CHANNELS_CONFIG; LucCount++)                           /* PRQA S 3387, 3416 # JV-01, JV-01 */
    {
      /* Read the Timer Type for given channel */
      LucHWIPType = Gpt_GaaChannel2IpType[LucCount];
      if (NULL_PTR != Gpt_GaaHwFunc[LucHWIPType]->pHWChannelDeInit)                                                     /* PRQA S 3416 # JV-01 */
      {
        #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
        /* Get core index as per channel */
        LucCoreIndexPerChannel = LpChannel[LucCount].ucCoreIndex;
        /* If kernel core - for other than OSTM, note: OSTM has not UnitInit function */
        /* Not OSTM - init all in kernel core */
        if (((GPT_HWIP_OSTM != LucHWIPType) && (Gpt_GucKernelCoreId == LucCoreId)) ||                                   /* PRQA S 3416 # JV-01 */
        /* OSTM - Init follow channel assignment for each core */
           ((GPT_HWIP_OSTM == LucHWIPType) && (LucCoreIndexPerChannel == (GPT_ONE << LucCoreId))))                      /* PRQA S 3415, 3416 # JV-01, JV-01 */
        #endif
        {
          /* Invoke low level driver for De-initializing the hardware */
          Gpt_GaaHwFunc[LucHWIPType]->pHWChannelDeInit((Gpt_ChannelType)LucCount);                                      /* PRQA S 0404 # JV-01 */
        } /* else No action required */
      } /* else No action required */
    }
  } /* else No action required */
} /* End of API Gpt_DeInit */

#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of GPT_DE_INIT_API == STD_ON */

/***********************************************************************************************************************
** Function Name         : Gpt_GetTimeElapsed
**
** Service ID            : 0x03
**
** Description           : This API is used to read the time elapsed for a particular Channel from the start of Channel.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Gpt_ValueType
**
** Preconditions         : Gpt_Init must be called before this function.
**
** Global Variables      : Gpt_GaaHwFunc, Gpt_GaaChannel2IpType
**
** Functions invoked     : Gpt_HW_Atu_GetTimeElapsed, Gpt_HW_Ostm_GetTimeElapsed, Gpt_HW_Taud_GetTimeElapsed
**                         Gpt_HW_Tauj_GetTimeElapsed, Gpt_CheckDetErrors
**                         Gpt_HW_Gtm_GetTimeElapsed
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_004, GPT_DUD_ACT_004_MUI004, GPT_DUD_ACT_004_MUI003
** Reference ID          : GPT_DUD_ACT_004_MUI002, GPT_DUD_ACT_004_MUI001, GPT_DUD_ACT_004_GLB030
***********************************************************************************************************************/
#if (GPT_TIME_ELAPSED_API == STD_ON)
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Gpt_ValueType, GPT_PUBLIC_CODE) Gpt_GetTimeElapsed(Gpt_ChannelType Channel)                                        /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  VAR(Gpt_ValueType, AUTOMATIC) LddTimeElapsed;
  /* Declare a Local variable to Timer Type */
  VAR(uint8, AUTOMATIC) LucCheckTimerType;
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnValue;
  /* Id of current core */
  VAR(uint8, AUTOMATIC) LucCoreId;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #else
  /* If multi-core is not configured, default Id is zero */
  LucCoreId = GPT_ZERO;
  #endif
  #endif

  /* Initialize the return value as zero */
  LddTimeElapsed = (uint32)GPT_ZERO;
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Initialize return value */
  LddReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  /* Check if the GPT Driver is initialized properly */
  LddReturnValue = Gpt_CheckDetErrors(Channel, GPT_GET_TIME_ELAPSED_SID, LucCoreId);
  /* Check if any DET error was reported */
  if (E_OK == LddReturnValue)
  #endif
  {
    /* Read the Timer Type for given channel */
    LucCheckTimerType = Gpt_GaaChannel2IpType[Channel];

    if (NULL_PTR != Gpt_GaaHwFunc[LucCheckTimerType]->pGetTimeElapsed)
    {
      /* Invoke low level driver for getting the Elapsed Time */
      LddTimeElapsed = Gpt_GaaHwFunc[LucCheckTimerType]->pGetTimeElapsed(Channel);
    } /* else No action required */
  } /* else No action required */

  /* Return the Elapsed Time */
  return (LddTimeElapsed);
} /* End of API Gpt_GetTimeElapsed */

#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of GPT_TIME_ELAPSED_API == STD_ON */

/***********************************************************************************************************************
** Function Name         : Gpt_GetTimeRemaining
**
** Service ID            : 0x04
**
** Description           : This API is used to read the remaining time for the Channel to reach timeout.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Gpt_ValueType
**
** Preconditions         : Gpt_Init must be called before this function.
**
** Global Variables      : Gpt_GaaHwFunc, Gpt_GaaChannel2IpType
**
** Functions invoked     : Gpt_HW_Atu_GetTimeRemaining, Gpt_HW_Ostm_GetTimeRemaining, Gpt_HW_Taud_GetTimeRemaining
**                         Gpt_HW_Tauj_GetTimeRemaining, Gpt_CheckDetErrors
**                         Gpt_HW_Gtm_GetTimeRemaining
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_005, GPT_DUD_ACT_005_MUI001, GPT_DUD_ACT_005_MUI002, GPT_DUD_ACT_005_MUI003
** Reference ID          : GPT_DUD_ACT_005_MUI004, GPT_DUD_ACT_005_GLB030
***********************************************************************************************************************/
#if (GPT_TIME_REMAINING_API == STD_ON)
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Gpt_ValueType, GPT_PUBLIC_CODE) Gpt_GetTimeRemaining(Gpt_ChannelType Channel)                                      /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the return value */
  VAR(Gpt_ValueType, AUTOMATIC) LddTimeRemaining;
  /* Declare a Local variable to Timer Type */
  VAR(uint8, AUTOMATIC) LucCheckTimerType;
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnValue;
  /* Variable to get core id */
  VAR(uint8, AUTOMATIC) LucCoreId;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #else
  /* If multi-core is not configured, default Id is zero */
  LucCoreId = GPT_ZERO;
  #endif
  #endif

  /* Initialize the return value as zero */
  LddTimeRemaining = (uint32)GPT_ZERO;
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Initialize return value */
  LddReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  /* Check if the GPT Driver is initialized properly */
  LddReturnValue = Gpt_CheckDetErrors(Channel, GPT_GET_TIME_REMAINING_SID, LucCoreId);
  /* Check if any DET error was reported */
  if (E_OK == LddReturnValue)
  #endif /* End of GPT_DEV_ERROR_DETECT == STD_ON */
  {
    /* Read the Timer Type for given channel */
    LucCheckTimerType = Gpt_GaaChannel2IpType[Channel];

    if (NULL_PTR != Gpt_GaaHwFunc[LucCheckTimerType]->pGetTimeRemaining)
    {
      /* Invoke low level driver for getting Remaining Time */
      LddTimeRemaining = Gpt_GaaHwFunc[LucCheckTimerType]->pGetTimeRemaining(Channel);
    } /* else No action required */
  } /* else No action required */
  /* End of E_OK == LddReturnValue */

  /* Return the Remaining Time */
  return (LddTimeRemaining);
} /* End of API Gpt_GetTimeRemaining */

#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of GPT_TIME_REMAINING_API == STD_ON */

/***********************************************************************************************************************
** Function Name         : Gpt_StartTimer
**
** Service ID            : 0x05
**
** Description           : This API starts the particular timer Channel.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant (but not for the same timer channel)
**
** Input Parameters      : Channel, value
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Gpt_Init must be called before this function.
**
** Global Variables      : Gpt_GaaChannelRamData, Gpt_GaaGlobalAccPoint, Gpt_GaaHwFunc,
**                         Gpt_GaaChannel2IpType, Gpt_GaaCoreId2Index, Gpt_GucKernelCoreId
**
** Functions invoked     : Gpt_HW_Atu_StartTimer, Gpt_HW_Ostm_StartTimer, Gpt_HW_Taud_StartTimer
**                         Gpt_HW_Tauj_StartTimer, Gpt_CheckDetErrors, GPT_DET_REPORT_ERROR, Det_ReportError
**                         Gpt_HW_Gtm_StartTimer
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_006, GPT_DUD_ACT_006_ERR001, GPT_DUD_ACT_006_ERR002, GPT_DUD_ACT_006_ERR003
** Reference ID          : GPT_DUD_ACT_006_GLB030, GPT_DUD_ACT_006_MUI001, GPT_DUD_ACT_006_MUI002
** Reference ID          : GPT_DUD_ACT_006_MUI003, GPT_DUD_ACT_006_MUI004
***********************************************************************************************************************/
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PUBLIC_CODE) Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)                                /* PRQA S 1503 # JV-01 */
{
  /* Declare a local pointer to point to the Channel Config Data */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Defining a local pointer to point to the Channel Ram Data */
  P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_VAR_NO_INIT) LpRamData;                                         /* PRQA S 3678 # JV-01 */
  /* Declare a Local variable to Timer Type */
  VAR(uint8, AUTOMATIC) LucCheckTimerType;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if ((GPT_DEV_ERROR_DETECT == STD_ON) || ((GPT_MULTI_CORE_SUPPORT == STD_ON) && (GPT_TYPE_II_SUPPORT == STD_ON)))
  /* Declare the variable to store the core ID */
  VAR(uint8, AUTOMATIC) LucCoreId;
  #endif

  #if ((GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_AR_VERSION == GPT_AR_431_VERSION) || \
    (GPT_AR_VERSION == GPT_AR_R22_11_VERSION))
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnValue;
  LddReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  #endif /* (GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_AR_VERSION == GPT_AR_431_VERSION) || \
    (GPT_AR_VERSION == GPT_AR_R22_11_VERSION)*/

  #if ((GPT_DEV_ERROR_DETECT == STD_OFF) && (GPT_MULTI_CORE_SUPPORT == STD_OFF))
  /* if Multicore is not configured, default value is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #elif (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if ((GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_TYPE_II_SUPPORT == STD_ON))
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif
  #else
  /* If multi-core is not configured, default Id is zero */
  LucCoreId = GPT_ZERO;
  LucAccPointIdx = GPT_ZERO;
  #endif

  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Check the Det error */
  LddReturnValue = Gpt_CheckDetErrors(Channel, GPT_START_TIMER_SID, LucCoreId);
  /* Check if any DET error was reported */
  if (E_OK == LddReturnValue)
  #endif
  {
    /* Read the Timer Type for given channel */
    LucCheckTimerType = Gpt_GaaChannel2IpType[Channel];

    #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
    #if (GPT_TYPE_II_SUPPORT == STD_ON)
    /* If channel type is OSTM */
    if (GPT_HWIP_OSTM == LucCheckTimerType)
    {
      /* Access point index is value of 4 low bits */
      LucAccPointIdx = Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK;
      /* Updating the channel config parameter to the current channel */
      LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel];
      /* Updating the channel RAM data parameter to the current channel */
      LpRamData = &(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelRamData)[(LpChannel->ucRamDataIndex)];
    }/* else No action required */
    #endif
    #if (GPT_TYPE_III_SUPPORT == STD_ON)
    /* If channel type is not OSTM */
    if (GPT_HWIP_OSTM != LucCheckTimerType)
    {
      /* Access point index is value of 4 low bits */
      LucAccPointIdx = Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK;
      /* Updating the channel config parameter to the current channel */
      LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel];
      /* Updating the RAM data parameter to the current channel */
      LpRamData = &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
    }/* else No action required */
    #endif
    #else
      /* Updating the channel config parameter to the current channel */
      LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel];
      /* Updating the RAM data parameter to the current channel */
      LpRamData = &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
    #endif /* End of if (GPT_MULTI_CORE_SUPPORT == STD_ON) */

    #if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Channel value is more than Max count value or ZERO */
    if ((LpChannel->ulMaxTickValue < Value) || ((uint32)GPT_ZERO == Value))                                             /* PRQA S 2962 # JV-01 */
    {
      /* Report to DET */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_SID, GPT_E_PARAM_VALUE);
      /* Set Return value */
      LddReturnValue = E_NOT_OK;
    } /* else No action required */
    #endif /* (GPT_DEV_ERROR_DETECT == STD_ON) */

    /* Check if the timer is already running */
    #if ((GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_AR_VERSION == GPT_AR_431_VERSION)||\
      (GPT_AR_VERSION == GPT_AR_R22_11_VERSION))
    /* if channel status is running */
    if (GPT_CH_RUNNING == LpRamData->ucChannelStatus)                                                                   /* PRQA S 2962 # JV-01 */
    {
      /* Report to Development Errors */
      GPT_DET_REPORT_ERROR(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_START_TIMER_SID, GPT_E_BUSY);
      /* Set Return value */
      LddReturnValue = E_NOT_OK;
    } /* else No action required */

    if (E_OK == LddReturnValue)
    #endif /* (GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_AR_VERSION == GPT_AR_431_VERSION) || \
      (GPT_AR_VERSION == GPT_AR_R22_11_VERSION)*/
    {
      if (NULL_PTR != Gpt_GaaHwFunc[LucCheckTimerType]->pStartTimer)
      {
        /* Invoke low level driver for starting the Channel */
        Gpt_GaaHwFunc[LucCheckTimerType]->pStartTimer(Channel, Value);
      } /* else No action required */
    } /* else No action required */
  } /* else No action required */
  /* End of (E_OK == LddReturnValue) */
} /* End of API Gpt_StartTimer */

#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_StopTimer
**
** Service ID            : 0x06
**
** Description           : This API stops the particular timer Channel
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant (but not for the same timer channel)
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Gpt_Init must be called before this function.
**
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GaaHwFunc, Gpt_GaaCoreId2Index,
**                         Gpt_GaaChannel2IpType, Gpt_GaaChannelRamData, Gpt_GucKernelCoreId
**
** Functions invoked     : Gpt_HW_Atu_StopTimer, Gpt_HW_Ostm_StopTimer, Gpt_HW_Taud_StopTimer
**                         Gpt_HW_Tauj_StopTimer, Gpt_CheckDetErrors, SchM_Enter_Gpt_##Exclusive_Area,
**                         SchM_Exit_Gpt_##Exclusive_Area
**                         Gpt_HW_Gtm_StopTimer
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_007, GPT_DUD_ACT_007_CRT001, GPT_DUD_ACT_007_CRT002, GPT_DUD_ACT_007_GLB030
** Reference ID          : GPT_DUD_ACT_007_MUI001, GPT_DUD_ACT_007_MUI002, GPT_DUD_ACT_007_MUI003
** Reference ID          : GPT_DUD_ACT_007_MUI004
***********************************************************************************************************************/
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PUBLIC_CODE) Gpt_StopTimer(Gpt_ChannelType Channel)                                                      /* PRQA S 1503 # JV-01 */
{
  /* Declare a local pointer to point to the Channel Config Data */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Defining a local pointer to point to the Channel Ram Data */
  P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_VAR_NO_INIT) LpRamData;                                         /* PRQA S 3678 # JV-01 */
  /* Declare a Local variable to Timer Type */
  VAR(uint8, AUTOMATIC) LucCheckTimerType;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnValue;
  #endif
  #if ((GPT_DEV_ERROR_DETECT == STD_ON) || ((GPT_MULTI_CORE_SUPPORT == STD_ON) && (GPT_TYPE_II_SUPPORT == STD_ON)))
  /* Declare the variable to store the core ID */
  VAR(uint8, AUTOMATIC) LucCoreId;
  #endif

  #if ((GPT_DEV_ERROR_DETECT == STD_OFF) && (GPT_MULTI_CORE_SUPPORT == STD_OFF))
  /* if Multicore is not configured, default value is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #elif (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if ((GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_TYPE_II_SUPPORT == STD_ON))
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif
  #else
  /* If multi-core is not configured, default Id is zero */
  LucCoreId = GPT_ZERO;
  LucAccPointIdx = GPT_ZERO;
  #endif

  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Initialize return value */
  LddReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */

  /* Check the DET error */
  LddReturnValue = Gpt_CheckDetErrors(Channel, GPT_STOP_TIMER_SID, LucCoreId);
  /* Check if any DET error was reported */
  if (E_OK == LddReturnValue)
  #endif /* End of GPT_DEV_ERROR_DETECT == STD_ON */
  {
    /* Read the Timer Type for given channel */
    LucCheckTimerType = Gpt_GaaChannel2IpType[Channel];

    #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
    #if (GPT_TYPE_II_SUPPORT == STD_ON)
    /* If channel type is OSTM */
    if (GPT_HWIP_OSTM == LucCheckTimerType)
    {
      /* Access point index is value of 4 low bits */
      LucAccPointIdx = Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK;
      /* Updating the channel config parameter to the current channel */
      LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel];
      /* Updating the channel RAM data parameter to the current channel */
      LpRamData = &(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelRamData)[(LpChannel->ucRamDataIndex)];
    } /* else No action required */
    #endif
    #if (GPT_TYPE_III_SUPPORT == STD_ON)
    /* If channel type is not OSTM */
    if (GPT_HWIP_OSTM != LucCheckTimerType)
    {
      /* Access point index is value of 4 low bits */
      LucAccPointIdx = Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK;
      /* Updating the channel config parameter to the current channel */
      LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel];
      /* Updating the RAM data parameter to the current channel */
      LpRamData = &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
    } /* else No action required */
    #endif
    #else
      /* Updating the channel config parameter to the current channel */
      LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel];
      /* Updating the RAM data parameter to the current channel */
      LpRamData = &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
    #endif /* End of if (GPT_MULTI_CORE_SUPPORT == STD_ON) */

    /* Check if the timer is started */
    if (GPT_CH_RUNNING == LpRamData->ucChannelStatus)                                                                   /* PRQA S 2962 # JV-01 */
    {
      if (NULL_PTR != Gpt_GaaHwFunc[LucCheckTimerType]->pStopTimer)
      {
        /* Enter Protected area  */
        #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
        #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
        GPT_ENTER_CRITICAL_SECTION_FROM_TYPE(LucCheckTimerType);                                                        /* PRQA S 3432 # JV-01 */
        #else
        GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
        #endif
        #endif

        /* Invoke low level driver to Stop the particular Channel */
        Gpt_GaaHwFunc[LucCheckTimerType]->pStopTimer(Channel);

        /* Exit Protected area  */
        #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
        #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
        GPT_EXIT_CRITICAL_SECTION_FROM_TYPE(LucCheckTimerType);                                                         /* PRQA S 3432 # JV-01 */
        #else
        GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
        #endif
        #endif
      } /* else No action required */
    } /* else No action required */
  } /* End of LddReturnValue == E_OK */
} /* End of API Gpt_StopTimer */

#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Gpt_EnableNotification
**
** Service ID            : 0x07
**
** Description           : This API enables the notification for particular Channel
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant (but not for the same timer channel)
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Gpt_Init must be called before this function and
**                         GPT_ENABLE_DISABLE_NOTIFICATION_API must be STD_ON
**
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GaaHwFunc, Gpt_GaaCoreId2Index, Gpt_GaaChannel2IpType,
**                         Gpt_GaaChannelRamData, Gpt_GucDriverMode, Gpt_GucKernelCoreId
**
** Functions invoked     : Gpt_HW_Atu_EnableInterrupt, Gpt_HW_Ostm_EnableInterrupt, Gpt_HW_Taud_EnableInterrupt
**                         Gpt_HW_Tauj_EnableInterrupt, Gpt_CheckDetErrors, Det_ReportError,
**                         SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**                         Gpt_HW_Gtm_EnableInterrupt
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_008, GPT_DUD_ACT_008_CRT001, GPT_DUD_ACT_008_CRT002
** Reference ID          : GPT_DUD_ACT_008_ERR001, GPT_DUD_ACT_008_ERR002, GPT_DUD_ACT_008_GBL001
** Reference ID          : GPT_DUD_ACT_008_GLB030, GPT_DUD_ACT_008_MUI001, GPT_DUD_ACT_008_MUI002
** Reference ID          : GPT_DUD_ACT_008_MUI003, GPT_DUD_ACT_008_MUI004
***********************************************************************************************************************/
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PUBLIC_CODE) Gpt_EnableNotification(Gpt_ChannelType Channel)                                             /* PRQA S 1503 # JV-01 */
{
  /* Declare a local pointer to point to the Channel Config Data */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Defining a local pointer to point to the Channel Ram Data */
  P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_VAR_NO_INIT) LpRamData;
  /* Declare a Local variable to Timer Type */
  VAR(uint8, AUTOMATIC) LucCheckTimerType;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;

  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnValue;
  #endif
  #if ((GPT_DEV_ERROR_DETECT == STD_ON) || ((GPT_MULTI_CORE_SUPPORT == STD_ON) && (GPT_TYPE_II_SUPPORT == STD_ON)))
  /* Declare the variable to store the core ID */
  VAR(uint8, AUTOMATIC) LucCoreId;
  #endif

  #if ((GPT_DEV_ERROR_DETECT == STD_OFF) && (GPT_MULTI_CORE_SUPPORT == STD_OFF))
  /* if Multicore is not configured, default value is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #elif (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if ((GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_TYPE_II_SUPPORT == STD_ON))
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif
  #else
  /* If multi-core is not configured, default Id is zero */
  LucCoreId = GPT_ZERO;
  LucAccPointIdx = GPT_ZERO;
  #endif

  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Initialize return value */
  LddReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  /* Check the DET Error */
  LddReturnValue = Gpt_CheckDetErrors(Channel, GPT_ENABLE_NOTIFY_SID, LucCoreId);

  /* Check if any DET error was reported */
  if (E_OK == LddReturnValue)
  #endif
  {
    /* Read the Timer Type for given channel */
    LucCheckTimerType = Gpt_GaaChannel2IpType[Channel];
    #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
    #if (GPT_TYPE_II_SUPPORT == STD_ON)
    /* If channel type is OSTM */
    if (GPT_HWIP_OSTM == LucCheckTimerType)
    {
      /* Access point index is value of 4 low bits */
      LucAccPointIdx = Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK;
      /* Updating the channel config parameter to the current channel */
      LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel];
      /* Updating the channel RAM data parameter to the current channel */
      LpRamData = &(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelRamData)[(LpChannel->ucRamDataIndex)];
    } /* else No action required */
    #endif
    #if (GPT_TYPE_III_SUPPORT == STD_ON)
    /* If channel type is not OSTM */
    if (GPT_HWIP_OSTM != LucCheckTimerType)
    {
      /* Access point index is value of 4 low bits */
      LucAccPointIdx = Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK;
      /* Updating the channel config parameter to the current channel */
      LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel];
      /* Updating the RAM data parameter to the current channel */
      LpRamData = &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
    } /* else No action required */
    #endif
    #else
      /* Updating the channel config parameter to the current channel */
      LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel];
      /* Updating the RAM data parameter to the current channel */
      LpRamData = &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
    #endif /* End of if (GPT_MULTI_CORE_SUPPORT == STD_ON) */

    /* Check if the pointer is valid before accessing it */
    #if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Notification Function is configured */
    if (NULL_PTR == LpChannel->pGptNotificationPointer)                                                                 /* PRQA S 2962 # JV-01 */
    {
      /* Report Error to Det */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFY_SID, GPT_E_PARAM_CHANNEL);
    }
    /* Check if the Notification Flag is already Enabled */
    else if (GPT_TRUE == LpRamData->blNotifyStatus)                                                                     /* PRQA S 2962 # JV-01 */
    {
      /* Report Error to DET */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_NOTIFY_SID, GPT_E_ALREADY_ENABLED);
    }
    else
    #endif /* #if (GPT_DEV_ERROR_DETECT == STD_ON) */
    {
      /* Enter Protected area  */
      #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
      #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
      GPT_ENTER_CRITICAL_SECTION_FROM_TYPE(LucCheckTimerType);                                                          /* PRQA S 3432 # JV-01 */
      #else
      GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
      #endif
      #endif

      /* Set the Notification Status Flag to GPT_TRUE */
      LpRamData->blNotifyStatus = GPT_TRUE;                                                                             /* PRQA S 2962 # JV-01 */

      if ((GPT_CH_MODE_CONTINUOUS == LpChannel->ucGptChannelMode)                                                       /* PRQA S 2962 # JV-01 */
          && (GPT_MODE_NORMAL == Gpt_GucDriverMode)                                                                     /* PRQA S 3415, 3416 # JV-01, JV-01 */
          && (NULL_PTR != Gpt_GaaHwFunc[LucCheckTimerType]->pEnableInterrupt))
      {
        /* Enabling interrupt for using channel */
        Gpt_GaaHwFunc[LucCheckTimerType]->pEnableInterrupt(Channel);
      } /* else No action required */

      /* Exit Protected area  */
      #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
      #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
      GPT_EXIT_CRITICAL_SECTION_FROM_TYPE(LucCheckTimerType);                                                           /* PRQA S 3432 # JV-01 */
      #else
      GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
      #endif
      #endif
    }
  } /* End of E_OK == LddReturnValue */
} /* End of API Gpt_EnableNotification */

#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON */

/***********************************************************************************************************************
** Function Name         : Gpt_DisableNotification
**
** Service ID            : 0x08
**
** Description           : This API disables the notification for particular
**                         Channel
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant (but not for the same timer channel)
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Gpt_Init must be called before this function and
**                         GPT_ENABLE_DISABLE_NOTIFICATION_API must be STD_ON
**
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GaaHwFunc, Gpt_GaaChannelRamData, Gpt_GaaCoreId2Index,
**                         Gpt_GaaChannel2IpType, Gpt_GucDriverMode, Gpt_GucKernelCoreId
**
** Functions invoked     : Gpt_HW_Atu_DisableInterrupt, Gpt_HW_Ostm_DisableInterrupt, Gpt_HW_Taud_DisableInterrupt
**                         Gpt_HW_Tauj_DisableInterrupt, Gpt_CheckDetErrors, Det_ReportError,
**                         SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**                         Gpt_HW_Gtm_DisableInterrupt
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_009, GPT_DUD_ACT_009_CRT001, GPT_DUD_ACT_009_CRT002
** Reference ID          : GPT_DUD_ACT_009_ERR001, GPT_DUD_ACT_009_ERR002, GPT_DUD_ACT_009_GBL001
** Reference ID          : GPT_DUD_ACT_009_GLB030, GPT_DUD_ACT_009_MUI001, GPT_DUD_ACT_009_MUI002
** Reference ID          : GPT_DUD_ACT_009_MUI003, GPT_DUD_ACT_009_MUI004
***********************************************************************************************************************/
#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PUBLIC_CODE) Gpt_DisableNotification(Gpt_ChannelType Channel)                                            /* PRQA S 1503 # JV-01 */
{
  /* Declare a local pointer to point to the Channel Config Data */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Defining a local pointer to point to the Channel Ram Data */
  P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_VAR_NO_INIT)  LpRamData;
  /* Declare a Local variable to Timer Type */
  VAR(uint8, AUTOMATIC) LucCheckTimerType;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;

  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnValue;
  #endif
  #if ((GPT_DEV_ERROR_DETECT == STD_ON) || ((GPT_MULTI_CORE_SUPPORT == STD_ON) && (GPT_TYPE_II_SUPPORT == STD_ON)))
  /* Declare the variable to store the core ID */
  VAR(uint8, AUTOMATIC) LucCoreId;
  #endif

  #if ((GPT_DEV_ERROR_DETECT == STD_OFF) && (GPT_MULTI_CORE_SUPPORT == STD_OFF))
  /* if Multicore is not configured, default value is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #elif (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if ((GPT_DEV_ERROR_DETECT == STD_ON) || (GPT_TYPE_II_SUPPORT == STD_ON))
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #endif
  #else
  /* If multi-core is not configured, default Id is zero */
  LucCoreId = GPT_ZERO;
  LucAccPointIdx = GPT_ZERO;
  #endif

  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Initialize return value */
  LddReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */

  /* Check DET error */
  LddReturnValue = Gpt_CheckDetErrors(Channel, GPT_DISABLE_NOTIFY_SID, LucCoreId);
  /* Check if any DET error was reported */
  if (E_OK == LddReturnValue)
  #endif
  {
    /* Read the Timer Type for given channel */
    LucCheckTimerType = Gpt_GaaChannel2IpType[Channel];
    #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
    #if (GPT_TYPE_II_SUPPORT == STD_ON)
    /* If channel type is OSTM */
    if (GPT_HWIP_OSTM == LucCheckTimerType)
    {
      /* Access point index is value of 4 low bits */
      LucAccPointIdx = Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK;
      /* Updating the channel config parameter to the current channel */
      LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel];
      /* Updating the channel RAM data parameter to the current channel */
      LpRamData = &(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelRamData)[(LpChannel->ucRamDataIndex)];
    }/* else No action required */
    #endif
    #if (GPT_TYPE_III_SUPPORT == STD_ON)
    /* If channel type is not OSTM */
    if (GPT_HWIP_OSTM != LucCheckTimerType)
    {
      /* Access point index is value of 4 low bits */
      LucAccPointIdx = Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK;
      /* Updating the channel config parameter to the current channel */
      LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel];
      /* Updating the RAM data parameter to the current channel */
      LpRamData = &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
    }/* else No action required */
    #endif
    #else
      /* Updating the channel config parameter to the current channel */
      LpChannel = &(*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel];
      /* Updating the RAM data parameter to the current channel */
      LpRamData = &Gpt_GaaChannelRamData[(LpChannel->ucRamDataIndex)];
    #endif /* End of if (GPT_MULTI_CORE_SUPPORT == STD_ON) */

    #if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Notification Function is configured */
    if (NULL_PTR == LpChannel->pGptNotificationPointer)                                                                 /* PRQA S 2962 # JV-01 */
    {
      /* Report Error to DET */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DISABLE_NOTIFY_SID, GPT_E_PARAM_CHANNEL);
    }
    /* Check if the Notification Flag is already Disabled */
    else if (GPT_FALSE == LpRamData->blNotifyStatus)                                                                    /* PRQA S 2962 # JV-01 */
    {
      /* Report Error to DET */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DISABLE_NOTIFY_SID, GPT_E_ALREADY_DISABLED);
    }
    else
    #endif /* End of GPT_DEV_ERROR_DETECT == STD_ON */
    {
      /* Enter Protected area  */
      #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
      #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
      GPT_ENTER_CRITICAL_SECTION_FROM_TYPE(LucCheckTimerType);                                                          /* PRQA S 3432 # JV-01 */
      #else
      GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
      #endif
      #endif

      /* Set the Notification Status Flag to GPT_FALSE */
      LpRamData->blNotifyStatus = GPT_FALSE;                                                                            /* PRQA S 2962 # JV-01 */

      if ((GPT_CH_MODE_CONTINUOUS == LpChannel->ucGptChannelMode) && (GPT_MODE_NORMAL == Gpt_GucDriverMode)             /* PRQA S 2962, 3415, 3416 # JV-01, JV-01, JV-01 */
        && (NULL_PTR != Gpt_GaaHwFunc[LucCheckTimerType]->pDisableInterrupt))
      {
        /* Disabling interrupt for using channel */
        Gpt_GaaHwFunc[LucCheckTimerType]->pDisableInterrupt(Channel);
      } /* else No action required */

      /* Exit Protected area  */
      #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
      #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
      GPT_EXIT_CRITICAL_SECTION_FROM_TYPE(LucCheckTimerType);                                                           /* PRQA S 3432 # JV-01 */
      #else
      GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
      #endif
      #endif
    } /* else No action required */
  } /* End of E_OK == LddReturnValue */  
} /* End of API Gpt_DisableNotification */

#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON */

/***********************************************************************************************************************
** Function Name         : Gpt_SetMode
**
** Service ID            : 0x09
**
** Description           : This API is used to set the GPT Driver mode
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non Reentrant
**
** Input Parameters      : Mode
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Gpt_Init must be called before this function, GPT_REPORT_WAKEUP_SOURCE and
**                         GPT_WAKEUP_FUNCTIONALITY_API must be STD_ON
**
** Global Variables      : Gpt_GucDriverMode, Gpt_GaaGlobalAccPoint, Gpt_GaaHwFunc,
**                         Gpt_GpPredefTimerConfig, Gpt_GaaCoreId2Index, Gpt_GaaChannelRamData,
**                         Gpt_GaaChannel2IpType, Gpt_GucKernelCoreId
**
** Functions invoked     : Gpt_HW_Tauj_StopTimer, Gpt_HW_Tauj_DisableWakeup, Gpt_HW_Tauj_EnableWakeup,
**                         Gpt_HW_Tauj_StopPredefTimer, Gpt_HW_Tauj_StartPredefTimer, Gpt_HW_Tauj_EnableInterrupt,
**                         Gpt_HW_Tauj_DisableInterrupt, Det_ReportError, Gpt_CheckDetErrors,
**                         SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_010
** Reference ID          : GPT_DUD_ACT_010_CRT001, GPT_DUD_ACT_010_CRT002
** Reference ID          : GPT_DUD_ACT_010_CRT003, GPT_DUD_ACT_010_CRT004
** Reference ID          : GPT_DUD_ACT_010_ERR001, GPT_DUD_ACT_010_ERR002
** Reference ID          : GPT_DUD_ACT_010_GBL001, GPT_DUD_ACT_010_GBL002, GPT_DUD_ACT_010_GLB030
** Reference ID          : GPT_DUD_ACT_010_MUI001, GPT_DUD_ACT_010_MUI002
** Reference ID          : GPT_DUD_ACT_010_MUI003, GPT_DUD_ACT_010_MUI004
***********************************************************************************************************************/
#if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PUBLIC_CODE) Gpt_SetMode(Gpt_ModeType Mode)                                                              /* PRQA S 1503 # JV-01 */
{
  /* Declare a local pointer to point to the Channel Config Data */
  P2CONST(volatile Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Defining a local pointer to point to the Channel Ram Data */
  P2VAR(volatile Gpt_ChannelRamDataType, AUTOMATIC, GPT_VAR_NO_INIT) LpRamData;                                         /* PRQA S 3678 # JV-01 */
  /* Declare a Local variable to Timer Type */
  VAR(uint8, AUTOMATIC) LucCheckTimerType;
  /* Declare a Local variable to store Wakeup status */
  VAR(boolean, AUTOMATIC) LucWakeupStatus;
  /* Declare a Local variable to store Channel Index */
  VAR(uint8, AUTOMATIC) LucChannelID;
  /* Declare the variable to store the index of channel in RAM Data */
  VAR(uint8, AUTOMATIC)  LucChannelIndex;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;

  #if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
  VAR(volatile uint8, AUTOMATIC) LucCount;
  #endif

  #if ((GPT_MULTI_CORE_SUPPORT == STD_ON) && (GPT_TYPE_II_SUPPORT == STD_ON))
  /* Access point index of a specific channel */
  VAR(uint8, AUTOMATIC) LucChannelAccPointIdx;
  #endif

  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnValue;
  /* Id of current core */
  VAR(uint8, AUTOMATIC) LucCoreId;

  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #else
  /* If multi-core is not configured, default Id is zero */
  LucCoreId = GPT_ZERO;
  #endif /* End of (GPT_MULTI_CORE_SUPPORT == STD_ON) */

  LddReturnValue = Gpt_CheckDetErrors((Gpt_ChannelType)GPT_ZERO, GPT_SET_MODE_SID, LucCoreId);

  /* if DET check return E_OK */
  if (E_OK == LddReturnValue)
  #endif /* End of GPT_DEV_ERROR_DETECT == STD_ON */
  {
    #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
    /* Access point index of kernel core */
    LucAccPointIdx = Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK;
    #else
    /* if Multicore is not configured, default value is GPT_ZERO */
    LucAccPointIdx = GPT_ZERO;
    #endif /* End of (GPT_MULTI_CORE_SUPPORT == STD_ON) */

    #if (GPT_DEV_ERROR_DETECT == STD_ON)
    if ((GPT_MODE_NORMAL != Mode) && (GPT_MODE_SLEEP != Mode))
    {
      /* Report to DET */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SET_MODE_SID, GPT_E_PARAM_MODE);
    }
    else
    #endif /* End of GPT_DEV_ERROR_DETECT == STD_ON */
    {
      /* Updating the local pointer to Channel config data */
      LpChannel = *(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig);

      /* Check if the Mode is Sleep Mode */
      if (GPT_MODE_SLEEP == Mode)
      {
        for (LucChannelID = (uint8)GPT_ZERO; LucChannelID < (uint8)GPT_TOTAL_CHANNELS_CONFIG; LucChannelID++)
        {
          /* Get the index of channel */
          LucChannelIndex = LpChannel[LucChannelID].ucRamDataIndex;
          /* Read the Timer Type for given channel */
          LucCheckTimerType = Gpt_GaaChannel2IpType[LucChannelID];

          #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
          #if (GPT_TYPE_II_SUPPORT == STD_ON)
          /* If channel type is OSTM */
          if (GPT_HWIP_OSTM == LucCheckTimerType)
          {
            /* Get the core the channel is assigned to */
            LucChannelAccPointIdx = (LpChannel[LucChannelID].ucCoreIndex) >> (uint8) GPT_ONE;
            /* Load the global pointer to current channel RAM data pointer */
            LpRamData = &(Gpt_GaaGlobalAccPoint[LucChannelAccPointIdx].pChannelRamData)[LucChannelIndex];
          }/* else No action required */
          #endif
          #if (GPT_TYPE_III_SUPPORT == STD_ON)
          /* If channel type is not OSTM */
          if (GPT_HWIP_OSTM != LucCheckTimerType)
          {
            /* Load the global pointer to current channel RAM data pointer */
            LpRamData = &Gpt_GaaChannelRamData[LucChannelIndex];
          }/* else No action required */
          #endif
          #else
            /* Load the global pointer to current channel RAM data pointer */
            LpRamData = &Gpt_GaaChannelRamData[LucChannelIndex];
          #endif
          /* Get the wakeup status of channel */
          LucWakeupStatus = LpRamData->blWakeupStatus;                                                                  /* PRQA S 2962 # JV-01 */

          /* Check for disable wakeup status of a Channel */
          if ((GPT_CH_RUNNING == LpRamData->ucChannelStatus) &&                                                         /* PRQA S 2962 # JV-01 */
            ((GPT_FALSE == (LpChannel[LucChannelID].blGptWakeupSupport)) || (GPT_FALSE == LucWakeupStatus)) &&
            (NULL_PTR != Gpt_GaaHwFunc[LucCheckTimerType]->pStopTimer))
          {
            /* Enter Protected area  */
            #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
            #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
            GPT_ENTER_CRITICAL_SECTION_FROM_TYPE(LucCheckTimerType);                                                    /* PRQA S 3432 # JV-01 */
            #else
            GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
            #endif
            #endif

            /* Invoke low level driver to Stop the Particular Channel */
            Gpt_GaaHwFunc[LucCheckTimerType]->pStopTimer(LucChannelID);

            /* Exit Protected area  */
            #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
            #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
            GPT_EXIT_CRITICAL_SECTION_FROM_TYPE(LucCheckTimerType);                                                     /* PRQA S 3432 # JV-01 */
            #else
            GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
            #endif
            #endif
          } /* else No action required */

          /* Check for disable wakeup status */
          if ((GPT_FALSE == LucWakeupStatus) && (NULL_PTR != Gpt_GaaHwFunc[LucCheckTimerType]->pDisableWakeup))
          {
              /* Disable wake-up for the channel */
              Gpt_GaaHwFunc[LucCheckTimerType]->pDisableWakeup(LucChannelID);
          }
          /* LucWakeupStatus is GPT_TRUE */
          else if ((GPT_TRUE == LucWakeupStatus) && (NULL_PTR != Gpt_GaaHwFunc[LucCheckTimerType]->pEnableWakeup))      /* PRQA S 2004 # JV-01 */
          {
            /* Enable wake-up for the channel */
            Gpt_GaaHwFunc[LucCheckTimerType]->pEnableWakeup(LucChannelID);
          } /* else No action required */
        }

        #if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
        for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_PREDEF_CHANNELS_CONFIG; LucCount++)                /* PRQA S 3387, 3416 # JV-01, JV-01 */
        {
          if (NULL_PTR != Gpt_GaaHwFunc[Gpt_GpPredefTimerConfig[LucCount].ucPredefTimerType]->pStopPredefTimer)         /* PRQA S 3416 # JV-01 */
          {
              #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
              /* Enter Protected area  */
              GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
              #endif
              /* Invoke low level driver for Initializing the GPT PreDef registers */
              Gpt_GaaHwFunc[Gpt_GpPredefTimerConfig[LucCount].ucPredefTimerType]->pStopPredefTimer();
              #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
              /* Exit Protected area */
              GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
              #endif
          } /* else No action required */
        }
        #endif /* End of (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON) */
      } /* In case of Mode == GPT_MODE_NORMAL */
      else
      {
        #if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
        /* Only If the driver is in sleep mode, the function shall
          restart all enabled GPT PreDef Timers */
        if (GPT_MODE_SLEEP == Gpt_GucDriverMode)                                                                        /* PRQA S 3416 # JV-01 */
        {
          for (LucCount = (uint8)GPT_ZERO; LucCount < (uint8)GPT_TOTAL_PREDEF_CHANNELS_CONFIG; LucCount++)              /* PRQA S 3387, 3416 # JV-01, JV-01 */
          {
            if (NULL_PTR != Gpt_GaaHwFunc[Gpt_GpPredefTimerConfig[LucCount].ucPredefTimerType]->pStartPredefTimer)      /* PRQA S 3416 # JV-01 */
            {
              #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
              /* Enter Protected area  */
              GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
              #endif
              /* Invoke low level driver for Initializing the GPT PreDef registers */
              Gpt_GaaHwFunc[Gpt_GpPredefTimerConfig[LucCount].ucPredefTimerType]->pStartPredefTimer();
              #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
              /* Exit Protected area */
              GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
              #endif
            } /* else No action required */
          }
        } /* else No action required */
        #endif /* End of (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON) */

        #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
        for (LucChannelID = (uint8)GPT_ZERO; LucChannelID < (uint8)GPT_TOTAL_CHANNELS_CONFIG; LucChannelID++)
        {
          /* Get the index of channel */
          LucChannelIndex = LpChannel[LucChannelID].ucRamDataIndex;
          /* Read the Timer Type for given channel */
          LucCheckTimerType = Gpt_GaaChannel2IpType[LucChannelID];

          #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
          #if (GPT_TYPE_II_SUPPORT == STD_ON)
          /* If channel type is OSTM */
          if (GPT_HWIP_OSTM == LucCheckTimerType)
          {
            /* Get the core the channel is assigned to */
            LucChannelAccPointIdx = (LpChannel[LucChannelID].ucCoreIndex) >> (uint8) GPT_ONE;
            /* Load the global pointer to current channel RAM data pointer */
            LpRamData = &(Gpt_GaaGlobalAccPoint[LucChannelAccPointIdx].pChannelRamData)[LucChannelIndex];
          }/* else No action required */
          #endif
          #if (GPT_TYPE_III_SUPPORT == STD_ON)
          /* If channel type is not OSTM */
          if (GPT_HWIP_OSTM != LucCheckTimerType)
          {
            /* Load the global pointer to current channel RAM data pointer */
            LpRamData = &Gpt_GaaChannelRamData[LucChannelIndex];
          }/* else No action required */
          #endif
          #else
            /* Load the global pointer to current channel RAM data pointer */
            LpRamData = &Gpt_GaaChannelRamData[LucChannelIndex];
          #endif

          /* Check for status of a Channel */
          if (((NULL_PTR != LpChannel[LucChannelID].pGptNotificationPointer) &&
            (GPT_TRUE == LpRamData->blNotifyStatus)) &&                                                                 /* PRQA S 2962 # JV-01 */
              (GPT_CH_MODE_CONTINUOUS == LpChannel[LucChannelID].ucGptChannelMode) &&
                (NULL_PTR != Gpt_GaaHwFunc[LucCheckTimerType]->pEnableInterrupt))
          {
            /* Enter Protected area  */
            #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
            #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
            GPT_ENTER_CRITICAL_SECTION_FROM_TYPE(LucCheckTimerType);                                                    /* PRQA S 3432 # JV-01 */
            #else
            GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
            #endif
            #endif

            /* Invoke low level driver to enable interrupt of particular channel */
            Gpt_GaaHwFunc[LucCheckTimerType]->pEnableInterrupt(LucChannelID);

            /* Exit Protected area  */
            #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
            #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
            GPT_EXIT_CRITICAL_SECTION_FROM_TYPE(LucCheckTimerType);                                                     /* PRQA S 3432 # JV-01 */
            #else
            GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
            #endif
            #endif
          }
          else
          {
            /* Disable interrupt for using channel */
            if (NULL_PTR != Gpt_GaaHwFunc[LucCheckTimerType]->pDisableInterrupt)
            {
              /* Enter Protected area  */
              #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
              #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
              GPT_ENTER_CRITICAL_SECTION_FROM_TYPE(LucCheckTimerType);                                                  /* PRQA S 3432 # JV-01 */
              #else
              GPT_ENTER_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
              #endif
              #endif

              /* Invoke low level driver to disable interrupt of particular channel */
              Gpt_GaaHwFunc[LucCheckTimerType]->pDisableInterrupt(LucChannelID);

              /* Exit Protected area  */
              #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
              #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
              GPT_EXIT_CRITICAL_SECTION_FROM_TYPE(LucCheckTimerType);                                                   /* PRQA S 3432 # JV-01 */
              #else
              GPT_EXIT_CRITICAL_SECTION(GPT_INTERRUPT_CONTROL_PROTECTION);
              #endif
              #endif
            } /* else No action required */
          }
        }/* End of for (LucChannelID = (uint8)GPT_ZERO;
            LucChannelID < (uint8)GPT_TOTAL_CHANNELS_CONFIG; LucChannelID++)*/
        #endif /* end of GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON */
      }
      /* Set the Mode to the Global variable */
      Gpt_GucDriverMode = Mode;
    } /* End of if ((GPT_MODE_NORMAL != Mode) && (GPT_MODE_SLEEP != Mode)) */
  }/* End of if (E_OK == LddReturnValue) */
} /* End of API Gpt_SetMode */

#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif
/* End of ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)) */

/***********************************************************************************************************************
** Function Name         : Gpt_DisableWakeup
**
** Service ID            : 0x0A
**
** Description           : This API disables the wakeup notification for a particular Channel
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant (but not for the same timer channel)
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Gpt_Init must be called before this function, GPT_REPORT_WAKEUP_SOURCE and
**                         GPT_WAKEUP_FUNCTIONALITY_API must be STD_ON
**
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GaaHwFunc, Gpt_GucDriverMode,
**                         Gpt_GaaChannel2IpType
**                         SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**
** Functions invoked     : Gpt_CheckDetErrors, Det_ReportError, Gpt_HW_Tauj_DisableWakeup
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_011, GPT_DUD_ACT_011_ERR001, GPT_DUD_ACT_011_GBL001
** Reference ID          : GPT_DUD_ACT_011_GLB030, GPT_DUD_ACT_011_MUI001, GPT_DUD_ACT_011_MUI002
** Reference ID          : GPT_DUD_ACT_011_MUI003, GPT_DUD_ACT_011_MUI004
***********************************************************************************************************************/
#if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PUBLIC_CODE) Gpt_DisableWakeup(Gpt_ChannelType Channel)                                                  /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  VAR(uint8, AUTOMATIC) LucCheckTimerType;
  /* Declare the variable to store the index of channel in RAM Data */
  VAR(uint8, AUTOMATIC)  LucChannelIndex;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnValue;
  #endif
  #if ((GPT_DEV_ERROR_DETECT == STD_OFF) && (GPT_MULTI_CORE_SUPPORT == STD_OFF))
  /* if Multicore is not configured, default value is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #elif (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Id of current core */
  VAR(uint8, AUTOMATIC) LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK);
  #else
  /* Id of current core */
  VAR(uint8, AUTOMATIC) LucCoreId;
  /* If multi-core is not configured, default Id is zero */
  LucCoreId = GPT_ZERO;
  /* Default ccess point index is zero*/
  LucAccPointIdx = GPT_ZERO;
  #endif

  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Initialize return value */
  LddReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  /* Check the DET Error */
  LddReturnValue = Gpt_CheckDetErrors(Channel, GPT_DISABLE_WAKEUP_SID, LucCoreId);

  /* Check if any DET error was reported */
  if (E_OK == LddReturnValue)
  {
    if (GPT_FALSE == (*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel].blGptWakeupSupport)
    {
      /* Report to DET */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_DISABLE_WAKEUP_SID, GPT_E_PARAM_CHANNEL);
    }
    else
    #endif /* End of GPT_DEV_ERROR_DETECT == STD_ON */
    {
      /* Read the Timer Type for given channel */
      LucCheckTimerType = Gpt_GaaChannel2IpType[Channel];
      /* Check if the GPT driver is in sleep mode */
      if (GPT_MODE_SLEEP == Gpt_GucDriverMode)                                                                          /* PRQA S 3416 # JV-01 */
      {
        if (NULL_PTR != Gpt_GaaHwFunc[LucCheckTimerType]->pDisableWakeup)
        {
          /* Disable wake-up for the channel */
          Gpt_GaaHwFunc[LucCheckTimerType]->pDisableWakeup(Channel);
        } /* else No action required */
      } /* else No action required */

      /* Get the index of channel */
      LucChannelIndex = (*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel].ucRamDataIndex;
      #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enter Protected area */
      GPT_ENTER_CRITICAL_SECTION(GPT_RAM_DATA_PROTECTION_GLOBAL);
      #endif
      /* Storing Wakeup Notification in Normal Mode */
      Gpt_GaaChannelRamData[LucChannelIndex].blWakeupStatus = GPT_FALSE;
      #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Exit Protected area */
      GPT_EXIT_CRITICAL_SECTION(GPT_RAM_DATA_PROTECTION_GLOBAL);
      #endif
    }
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  } /* else No action required */
  #endif
  /* End of LddReturnValue == E_OK */
} /* End of API Gpt_DisableWakeup */

#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif
/* End of ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)  && (GPT_REPORT_WAKEUP_SOURCE == STD_ON)) */

/***********************************************************************************************************************
** Function Name         : Gpt_EnableWakeup
**
** Service ID            : 0x0B
**
** Description           : This API enables the wakeup notification for a particular Channel
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant (but not for the same timer channel)
**
** Input Parameters      : Channel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Gpt_Init must be called before this function, GPT_REPORT_WAKEUP_SOURCE and
**                         GPT_WAKEUP_FUNCTIONALITY_API must be STD_ON
**
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GaaCoreId2Index
**
** Functions invoked     : Gpt_CheckDetErrors, Det_ReportError
**                         SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_012, GPT_DUD_ACT_012_ERR001, GPT_DUD_ACT_012_GBL001
** Reference ID          : GPT_DUD_ACT_012_GLB030, GPT_DUD_ACT_012_MUI001, GPT_DUD_ACT_012_MUI002
** Reference ID          : GPT_DUD_ACT_012_MUI003, GPT_DUD_ACT_012_MUI004
***********************************************************************************************************************/
#if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PUBLIC_CODE) Gpt_EnableWakeup(Gpt_ChannelType Channel)                                                   /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to store the index of channel in RAM Data */
  VAR(uint8, AUTOMATIC)  LucChannelIndex;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnValue;
  #endif

  #if ((GPT_DEV_ERROR_DETECT == STD_OFF) && (GPT_MULTI_CORE_SUPPORT == STD_OFF))
  /* if Multicore is not configured, default value is GPT_ZERO */
  LucAccPointIdx = (uint8)GPT_ZERO;
  #elif (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Id of current core */
  VAR(uint8, AUTOMATIC) LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucAccPointIdx = (Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK);
  #else
  /* Id of current core */
  VAR(uint8, AUTOMATIC) LucCoreId;
  /* Default ccess point index is zero*/
  LucAccPointIdx = (uint8)GPT_ZERO;
  /* If multi-core is not configured, default Id is zero */
  LucCoreId = (uint8)GPT_ZERO;
  #endif

  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Initialize return value */
  LddReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  /* Check the DET Error */
  LddReturnValue = Gpt_CheckDetErrors(Channel, GPT_ENABLE_WAKEUP_SID, LucCoreId);
  /* Check if any DET error was reported */
  if (E_OK == LddReturnValue)
  {
    /* Check if the wake up status if GPT_FALSE */
    if (GPT_FALSE == (*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel].blGptWakeupSupport)
    {
      /* Report to DET */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_ENABLE_WAKEUP_SID, GPT_E_PARAM_CHANNEL);
    }
    else
    #endif /* End of GPT_DEV_ERROR_DETECT == STD_ON */
    {
      /* Get the index of channel */
      LucChannelIndex = (*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[Channel].ucRamDataIndex;
      #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enter Protected area */
      GPT_ENTER_CRITICAL_SECTION(GPT_RAM_DATA_PROTECTION_GLOBAL);
      #endif
      /* Storing Notification in sleep mode */
      Gpt_GaaChannelRamData[LucChannelIndex].blWakeupStatus = GPT_TRUE;
      #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Exit Protected area */
      GPT_EXIT_CRITICAL_SECTION(GPT_RAM_DATA_PROTECTION_GLOBAL);
      #endif
    }
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  } /* else No action required */
  #endif
} /* End of API Gpt_EnableWakeup */

#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif
/* End of ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && (GPT_REPORT_WAKEUP_SOURCE == STD_ON)) */

/***********************************************************************************************************************
** Function Name         : Gpt_CheckWakeup
**
** Service ID            : 0x0C
**
** Description           : This API checks the wakeup notification for a particular Channel
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant
**
** Input Parameters      : WakeupSource
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Gpt_Init must be called before this function, GPT_REPORT_WAKEUP_SOURCE and
**                         GPT_WAKEUP_FUNCTIONALITY_API must be STD_ON
**
** Global Variables      : Gpt_GaaGlobalAccPoint, Gpt_GaaChannelRamData, Gpt_GaaCoreId2Index, Gpt_GaaChannel2IpType
**                         Gpt_GucKernelCoreId
**
** Functions invoked     : EcuM_SetWakeupEvent, Det_ReportError,
**                         SchM_Enter_Gpt_##Exclusive_Area, SchM_Exit_Gpt_##Exclusive_Area
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_013, GPT_DUD_ACT_013_CRT001, GPT_DUD_ACT_013_CRT002
** Reference ID          : GPT_DUD_ACT_013_CRT003, GPT_DUD_ACT_013_ERR001, GPT_DUD_ACT_013_GBL001
** Reference ID          : GPT_DUD_ACT_013_GLB030, GPT_DUD_ACT_013_MUI001, GPT_DUD_ACT_013_MUI002
** Reference ID          : GPT_DUD_ACT_013_MUI003, GPT_DUD_ACT_013_MUI004
***********************************************************************************************************************/
#if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, GPT_PUBLIC_CODE) Gpt_CheckWakeup(EcuM_WakeupSourceType WakeupSource)                                         /* PRQA S 1503 # JV-01 */
{
  /* Declare a local pointer to point to the Channel Config Data */
  P2CONST(Gpt_ChannelConfigType, AUTOMATIC, GPT_CONFIG_DATA) LpChannel;
  /* Flags of wakeup function */
  VAR(boolean, AUTOMATIC) LblWakeupFlag;
  /* Index of channel ID */
  VAR(uint8, AUTOMATIC) LucChannelID;
  /* Declare the variable to store the index of channel in RAM Data */
  VAR(uint8, AUTOMATIC)  LucChannelIndex;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;

  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnValue;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Index convert from core id */
  VAR(uint8, AUTOMATIC) LucCoreId2Index;
  /* Id of current core */
  VAR(uint8, AUTOMATIC) LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  LucCoreId2Index = Gpt_GaaCoreId2Index[LucCoreId];
  #endif /* End of (GPT_MULTI_CORE_SUPPORT == STD_ON) */
  /* Initialize return value */
  LddReturnValue = E_OK;
  #endif /* End of (GPT_DEV_ERROR_DETECT == STD_ON) */

  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  if (GPT_INVALID_CORE == Gpt_GucKernelCoreId)
  {
    /* Report to DET module */
    (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_CHECK_WAKEUP_SID, GPT_E_UNINIT);
    /* Set Return value */
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif /* End of (GPT_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Access point index of kernel core */
    LucAccPointIdx = Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK;
  }
  #else
  /* if Multicore is not configured, default value is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif

  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  if (E_OK == LddReturnValue)                                                                                           /* PRQA S 2991, 2995 # JV-01, JV-01 */
  {
    /* Check if the Kernel core is initialized properly */
    if (GPT_INITIALIZED != *(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pDriverState))
    {
      /* Report to DET */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_CHECK_WAKEUP_SID, GPT_E_UNINIT);
    }
    else
    #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
    /* Check invalid core for init API */
    if ((GPT_INVALID_CORE == LucCoreId2Index) || (Gpt_GucKernelCoreId != LucCoreId))
    {
      /* Report to DET */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_CHECK_WAKEUP_SID, GPT_E_INVALID_CORE);
    }
    else
    #endif
    #endif /* End of GPT_DEV_ERROR_DETECT == STD_ON */
    {
      /* Initialize Channel ID */
      LucChannelID = (uint8)GPT_ZERO;
      /* Update the local pointer to Channel config */
      LpChannel = *(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig);

      do
      {
        #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
        /* Enter Protected area */
        GPT_ENTER_CRITICAL_SECTION(GPT_RAM_DATA_PROTECTION_GLOBAL);
        #endif /* End of GPT_CRITICAL_SECTION_PROTECTION == STD_ON */

        if (GPT_HWIP_OSTM != Gpt_GaaChannel2IpType[LucChannelID])
        {
          /* Get the index of channel */
          LucChannelIndex = LpChannel[LucChannelID].ucRamDataIndex;
          /* Save the Wakeup status into the local variable */
          LblWakeupFlag = Gpt_GaaChannelRamData[LucChannelIndex].blWakeupOccurrence;

          if ((GPT_TRUE == LblWakeupFlag) &&
                    (((EcuM_WakeupSourceType)GPT_ONE << (LpChannel[LucChannelID].ucWakeupSourceId)) == WakeupSource))
          {
            /* Reset wakeup flag for Channel */
            Gpt_GaaChannelRamData[LucChannelIndex].blWakeupOccurrence = GPT_FALSE;
            #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
            /* Enter Protected area */
            GPT_EXIT_CRITICAL_SECTION(GPT_RAM_DATA_PROTECTION_GLOBAL);
            #endif
            /* Invoke the EcuM Set Wakeup API */
            EcuM_SetWakeupEvent(WakeupSource);
            /* Update the ChannelID with maximum number of Channel configured to break loop */
            LucChannelID = (uint8)GPT_TOTAL_CHANNELS_CONFIG;
          }
          else
          {
            #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
            /* Enter Protected area */
            GPT_EXIT_CRITICAL_SECTION(GPT_RAM_DATA_PROTECTION_GLOBAL);
            #endif /* End of GPT_CRITICAL_SECTION_PROTECTION == STD_ON */
            /* Increment Channel ID count */
            LucChannelID++;                                                                                             /* PRQA S 3383 # JV-01 */
          }
        }
        else
        {
          #if (GPT_CRITICAL_SECTION_PROTECTION == STD_ON)
          /* Enter Protected area */
          GPT_EXIT_CRITICAL_SECTION(GPT_RAM_DATA_PROTECTION_GLOBAL);
          #endif /* End of GPT_CRITICAL_SECTION_PROTECTION == STD_ON */
          /* Increment Channel ID count */
          LucChannelID++;                                                                                               /* PRQA S 3383 # JV-01 */
        }
      } while (GPT_TOTAL_CHANNELS_CONFIG != LucChannelID);
    } /* End of if ((GPT_INVALID_CORE == LucAccPointIdx) || (Gpt_GucKernelCoreId != LucCoreId))*/
  #if (GPT_DEV_ERROR_DETECT == STD_ON)
  } /* End of if (E_OK = LddReturnValue) */
  #endif
} /* End of API Gpt_CheckWakeup */

#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif
/* End of ((GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) && (GPT_REPORT_WAKEUP_SOURCE == STD_ON)) */

/***********************************************************************************************************************
** Function Name        : Gpt_GetPredefTimerValue
**
** Service ID           : 0x0D
**
** Description          : This API is used to get the GPT predef timer value for
**                        the current value of the desired GPT Predef Timer.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : PredefTimer
**
** Output Parameters    : TimeValuePtr
**
** InOut Parameters     : None
**
** Return parameter     : Std_ReturnType
**
** Preconditions        : Gpt_Init must be called before this function, GPT_GET_PREDEF_TIMER_VALUE_API must be STD_ON
**
** Global Variables     : Gpt_GucDriverMode, Gpt_GpPredefTimerConfig, Gpt_GaaHwFunc,
**                        Gpt_GaaCoreId2Index, Gpt_GaaGlobalAccPoint, Gpt_GucKernelCoreId
**
** Functions invoked    : Gpt_HW_Atu_GetPredefTimerValue, Gpt_HW_Tauj_GetPredefTimerValue
**                        Det_ReportError, GPT_DET_REPORT_ERROR
**                        Gpt_HW_Gtm_GetPredefTimerValue
**
** Registers Used       : None
**
** Reference ID         : GPT_DUD_ACT_014, GPT_DUD_ACT_014_ERR001, GPT_DUD_ACT_014_ERR002
** Reference ID         : GPT_DUD_ACT_014_ERR004, GPT_DUD_ACT_014_ERR005, GPT_DUD_ACT_014_ERR003
** Reference ID         : GPT_DUD_ACT_014_GLB030, GPT_DUD_ACT_014_MUI001, GPT_DUD_ACT_014_MUI002
** Reference ID         : GPT_DUD_ACT_014_MUI003, GPT_DUD_ACT_014_MUI004
***********************************************************************************************************************/
#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
#define GPT_START_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Std_ReturnType, GPT_PUBLIC_CODE) Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32 *TimeValuePtr)    /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucCheckTimerType;
  /* Declare a Local variable channel for predef timer */
  VAR(volatile uint8, AUTOMATIC) LucChannelID;
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnValue;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Index convert from core id */
  VAR(uint8, AUTOMATIC) LucCoreId2Index;
  /* Declare the variable to store the core ID */
  VAR(uint8, AUTOMATIC) LucCoreId;
  #endif
  /* Declare the variable to store index to access global data */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  /* Initialized return value to E_OK */
  LddReturnValue = E_OK;

  /* Initialize Channel ID */
  LucChannelID = GPT_ZERO;

  #if (GPT_MULTI_CORE_SUPPORT == STD_OFF)
  /* if Multicore is not configured, default coreid is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #else
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreId2Index = Gpt_GaaCoreId2Index[LucCoreId];

  if (GPT_INVALID_CORE == Gpt_GucKernelCoreId)
  {
    #if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET module */
    (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_PREDEFTIMRVALUE_SID, GPT_E_UNINIT);
    #endif /* End of (GPT_DEV_ERROR_DETECT == STD_ON) */
    /* Set Return value */
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /*Get access point index of kernel core */
    LucAccPointIdx = Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK;
  }
  #endif

  if (E_OK == LddReturnValue)                                                                                           /* PRQA S 2991, 2995 # JV-01, JV-01 */
  {
    /* Check if the GPT Driver is initialized properly */
    if (GPT_INITIALIZED != *(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pDriverState))
    {
      #if (GPT_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET module */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_PREDEFTIMRVALUE_SID, GPT_E_UNINIT);
      #endif /* End of (GPT_DEV_ERROR_DETECT == STD_ON) */
      /* Set Return value */
      LddReturnValue = E_NOT_OK;
    }
    else
    #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
    /* Check invalid core */
    if(GPT_INVALID_CORE == LucCoreId2Index)
    {
      #if (GPT_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_PREDEFTIMRVALUE_SID, GPT_E_INVALID_CORE);
      #endif /* End of (GPT_DEV_ERROR_DETECT == STD_ON) */
      /* Set Return value */
      LddReturnValue = E_NOT_OK;
    }
    else
    #endif /* End of (GPT_MULTI_CORE_SUPPORT == STD_ON) */
    {
      #if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
      /* Check that driver is not in Sleep Mode */
      if (GPT_MODE_SLEEP == Gpt_GucDriverMode)                                                                          /* PRQA S 3416 # JV-01 */
      {
        #if ((GPT_AR_VERSION == GPT_AR_431_VERSION) || (GPT_DEV_ERROR_DETECT == STD_ON)||\
          (GPT_AR_VERSION == GPT_AR_R22_11_VERSION))
        /* Report to Development Errors */
        /* Implements SWS_Gpt_00401 */
        GPT_DET_REPORT_ERROR(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_PREDEFTIMRVALUE_SID, GPT_E_MODE);
        #endif /* (GPT_AR_VERSION == GPT_AR_431_VERSION) || (GPT_DEV_ERROR_DETECT == STD_ON)|| \
          (GPT_AR_VERSION == GPT_AR_R22_11_VERSION)*/
        /* Implements SWS_Gpt_00402 */
        LddReturnValue = E_NOT_OK;
      } /* else No action required */
      /* Check that a valid pointer is passed as a parameter */
      #endif /* ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)) */

      /* Check if the PredefTimer is invalid */
      if ((GPT_PREDEF_TIMER_1US_16BIT == PredefTimer) || (GPT_PREDEF_TIMER_1US_24BIT == PredefTimer) ||
                                                                          (GPT_PREDEF_TIMER_1US_32BIT == PredefTimer))
      {
        /* Report invalid Predef Timer Type if Gentool output config 100US but input 1US */
        if ((uint8)GPT_PREDEF_TIMER_100US_32BIT == Gpt_GpPredefTimerConfig[LucChannelID].ucPredefTimerCounterType)      /* PRQA S 3416 # JV-01 */
        {
          #if (GPT_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET module */
          (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_PREDEFTIMRVALUE_SID, GPT_E_PARAM_PREDEF_TIMER);
          #endif /* End of (GPT_DEV_ERROR_DETECT == STD_ON) */
          /* Set Return value */
          LddReturnValue = E_NOT_OK;
        } /* else No action required */
      }
      else if (GPT_PREDEF_TIMER_100US_32BIT == PredefTimer)
      {
        /* Report invalid Predef Timer Type if Gentool output config 1US but input 100US */
        if ((uint8)GPT_PREDEF_TIMER_100US_32BIT != Gpt_GpPredefTimerConfig[LucChannelID].ucPredefTimerCounterType)      /* PRQA S 3416 # JV-01 */
        {
          #if (GPT_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET module */
          (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_PREDEFTIMRVALUE_SID, GPT_E_PARAM_PREDEF_TIMER);
          #endif /* End of (GPT_DEV_ERROR_DETECT == STD_ON) */
          /* Set Return value */
          LddReturnValue = E_NOT_OK;
        } /* else No action required */
      }
      else
      {
        /* Report invalid Predef Timer Type */
        #if (GPT_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET module */
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_PREDEFTIMRVALUE_SID, GPT_E_PARAM_PREDEF_TIMER);
        #endif /* End of (GPT_DEV_ERROR_DETECT == STD_ON) */
        /* Set Return value */
        LddReturnValue = E_NOT_OK;
      }

      /* Check if the TimerValue is configured */
      if (NULL_PTR == TimeValuePtr)
      {
        #if (GPT_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_GET_PREDEFTIMRVALUE_SID, GPT_E_PARAM_POINTER);
        #endif /* End of (GPT_DEV_ERROR_DETECT == STD_ON) */
        /* Set Return value */
        LddReturnValue = E_NOT_OK;
      } /* else No action required */
    }
  }

  if (E_OK == LddReturnValue)
  {
    LucCheckTimerType = Gpt_GpPredefTimerConfig[LucChannelID].ucPredefTimerType;
    if (NULL_PTR != Gpt_GaaHwFunc[LucCheckTimerType]->pGetPredefTimerValue)                                             /* PRQA S 3416 # JV-01 */
    {
      /* Invoke low level driver for get value the Gpt_PredefTimer */
      LddReturnValue = Gpt_GaaHwFunc[LucCheckTimerType]->pGetPredefTimerValue(PredefTimer, TimeValuePtr);
    }
    else
    {
      /* An error occurred. Time variable is not updated */
      LddReturnValue = E_NOT_OK;
    }
  } /* else No action required */
  /* Return the value */
  return (LddReturnValue);
} /* End of API Gpt_GetPredefTimerValue */

#define GPT_STOP_SEC_PUBLIC_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Gpt_CheckDetErrors
**
** Service ID           : None
**
** Description          : This API is used to report DET for invalid initialization and invalid Channel in this file.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LddChannel, LucApi_SID
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : Std_ReturnType
**
** Preconditions        : NA
**
** Global Variables     : Gpt_GaaGlobalAccPoint, Gpt_GaaCoreId2Index, Gpt_GaaChannel2IpType, Gpt_GucKernelCoreId
**
** Functions invoked    : Det_ReportError
**
** Registers Used       : None
**
** Reference ID         : GPT_DUD_ACT_015, GPT_DUD_ACT_015_ERR001, GPT_DUD_ACT_015_ERR002, GPT_DUD_ACT_015_ERR003
** Reference ID         : GPT_DUD_ACT_015_MUI001, GPT_DUD_ACT_015_MUI002, GPT_DUD_ACT_015_MUI003, GPT_DUD_ACT_015_MUI004
***********************************************************************************************************************/
#if (GPT_DEV_ERROR_DETECT == STD_ON)
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(Std_ReturnType, GPT_PRIVATE_CODE)
  Gpt_CheckDetErrors(Gpt_ChannelType LddChannel, uint8 LucApi_SID, uint8 LucCoreId)                                     /* PRQA S 3206 # JV-01 */
{
  /* Declare the variable to store the DET return value */
  VAR(Std_ReturnType, AUTOMATIC) LddReturnValue;
  /* Index to access data of core */
  VAR(uint8, AUTOMATIC) LucAccPointIdx;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Index convert from core id */
  VAR(uint8, AUTOMATIC) LucCoreId2Index;
  /* Index of HW IP Type */
  VAR(uint8, AUTOMATIC) LucHwIpType;
  /* Covert Core Id to access point Index */
  LucCoreId2Index = Gpt_GaaCoreId2Index[LucCoreId];
  #else
  /* if Multicore is not configured, default access index is GPT_ZERO */
  LucAccPointIdx = GPT_ZERO;
  #endif
  /* Initialized return value to E_OK */
  LddReturnValue = E_OK;

  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core */
  if(GPT_INVALID_CORE == LucCoreId2Index)
  {
    /* Report to DET */
    (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, LucApi_SID, GPT_E_INVALID_CORE);
    /* Set Return value */
    LddReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
    /* DET check for API different than Gpt_SetMode*/
    if (GPT_SET_MODE_SID != LucApi_SID)
    {
      /* Check channel is in the valid range */
      if ((Gpt_ChannelType)GPT_MAX_CHANNEL_ID_CONFIGURED < LddChannel)
      {
        /* Report to DET module */
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, LucApi_SID, GPT_E_PARAM_CHANNEL);
        /* Set Return value */
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
        /* If driver is not init yet, Gpt_GucKernelCoreId is not assigned with corrected value */
        if (GPT_INVALID_CORE == Gpt_GucKernelCoreId)
        {
          /* Report to DET module */
          (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, LucApi_SID, GPT_E_UNINIT);
          /* Set Return value */
          LddReturnValue = E_NOT_OK;
        }
        else
        {
          /* Get the hw ip type  */
          LucHwIpType = Gpt_GaaChannel2IpType[LddChannel];

          /* If type of channel is not OSTM, get kernel core value */
          if (GPT_HWIP_OSTM != LucHwIpType)
          {
            /* Access point index of kernel core */
            LucAccPointIdx = Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK;
          }
          /* else type of channel is OSTM, mask 4 low bit to get core value */
          else
          {
            /* Access point index of current core */
            LucAccPointIdx = Gpt_GaaCoreId2Index[LucCoreId] & GPT_CORE_MASK;
          }
          #endif /* End of GPT_MULTI_CORE_SUPPORT == STD_ON */

          /* Check driver state of core is invalid */
          if (GPT_INITIALIZED != *(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pDriverState))
          {
            /* Report to DET module */
            (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, LucApi_SID, GPT_E_UNINIT);
            /* Set Return value */
            LddReturnValue = E_NOT_OK;
          }
          else
          {
            #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
            /* Checking if Service API is invoked within correct core */
            if (GPT_ZERO == ((GPT_ONE << LucCoreId) &
              (*(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pChannelConfig))[LddChannel].ucCoreIndex))
            {
              /* Report to DET */
              (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, LucApi_SID, GPT_E_INVALID_CORE);
              /* Set Return value */
              LddReturnValue = E_NOT_OK;
            } /* else No action required */
            #endif
          }
        #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
        }
        #endif /* End of GPT_MULTI_CORE_SUPPORT == STD_ON */
      }
    }
    else
    {
      #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
      /* If driver is not init yet, Gpt_GucKernelCoreId is not assigned with corrected value */
      if (GPT_INVALID_CORE == Gpt_GucKernelCoreId)
      {
        /* Report to DET module */
        (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, LucApi_SID, GPT_E_UNINIT);
        /* Set Return value */
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        /* Access point index of kernel core */
        LucAccPointIdx = Gpt_GaaCoreId2Index[Gpt_GucKernelCoreId] & GPT_CORE_MASK;

        /* Check invalid core for init API */
        if (Gpt_GucKernelCoreId != LucCoreId)
        {
          /* Report to DET */
          (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SET_MODE_SID, GPT_E_INVALID_CORE);
          /* Set Return value */
          LddReturnValue = E_NOT_OK;
        }/* else No action required */
        else
        #endif
        {
          /* Check if the Kernel core is initialized properly */
          if (GPT_INITIALIZED != *(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pDriverState))
          {
            /* Report to DET */
            (void)Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID, GPT_SET_MODE_SID, GPT_E_UNINIT);
            /* Set Return value */
            LddReturnValue = E_NOT_OK;
          } /* else No action required */
        }
      #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
      }
      #endif
    }
  }
  return (LddReturnValue);
}

#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (GPT_DEV_ERROR_DETECT == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Gpt_SetStatus
**
** Service ID            : Not Applicable
**
** Description           : This service change satatus of GPT.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : LblStatusType
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Gpt_GaaGlobalAccPoint
**
** Functions Invoked     : None
**
** Registers Used        : None
**
** Reference ID          : GPT_DUD_ACT_070, GPT_DUD_ACT_070_GBL001
***********************************************************************************************************************/
#define GPT_START_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, GPT_PRIVATE_CODE) Gpt_SetStatus(boolean LblStatusType, uint8 LucAccPointIdx)
{
  /* Set the state of core */
  *(Gpt_GaaGlobalAccPoint[LucAccPointIdx].pDriverState) = LblStatusType;
}
#define GPT_STOP_SEC_PRIVATE_CODE
#include "Gpt_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
