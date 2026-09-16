/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_TAUD_LLDriver.c                                                                                 */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Low level Driver code of the PWM Driver Component                                                                  */
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
/*                                              Devices:       X2x                                                    */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*                                                                                                                    **
** 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                                                            **
** 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                        **
** 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                           **
** 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                            **
** 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                           **
**                     Function Pwm_HW_TAUD_Callback: Remove QAC message 3678                                         **
** 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
** 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
** 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.01.02 U2Bx, Ver22.00.05 U2Cx Beta2 Release                         **
** 2.1.1: 30/08/2024 : Update SW-VERSION for Ver22.01.01 U2Bx Beta Release                                            **
**                     As part of U2Cx support, following changes are made                                            **
**                     1. Update QAC message for lines 596, 2577, 2752, 2758, 2882, 2888                              **
**                     2. Remove QAC message 1534                                                                     **
**                     3. Update QAC message 3678                                                                     **
** 2.0.1: 28/10/2023 : Added the IF ELSE condition to check whether the variable Pwm_GaaChannelIdleStatus is TRUE     **
**                     or PWM_FALSE when the variable Pwm_GaaChannelConstantStatus is TRUE in Pwm_HW_TAUD_Callback    **
**        24/10/2023 : Cast PWM_FALSE, PWM_TRUE to uint8, add QAC message 4304                                        **
**                     Add the checking global variable Pwm_GaaChannelIdleStatus as PWM_FALSE in Pwm_HW_TAUD_Callback **
**        21/10/2023 : Follow rule QAC 10.3.0, add new QAC message 1534, 3006 and add QAC comment 1006                **
**                     Remove QAC message 1532, 2814, 2824, 2844, 2934, 4399                                          **
**        18/10/2023 : Add QAC message 1881                                                                           **
**        15/10/2023 : Change critical section PWM_RAM_DATA_PROTECTION_GLOBAL to                                      **
**                     PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL in function Pwm_HW_TAUD_SetOutputToIdle,               **
**                     Pwm_HW_TAUD_SetDutyCycle, Pwm_HW_TAUD_SetPeriodAndDuty, Pwm_HW_TAUD_GetOutputState,            **
**                     Pwm_HW_TAUD_Callback, Pwm_HW_TAUD_DisableNotification, Pwm_HW_TAUD_SetChannelOutput,           **
**                     Pwm_HW_TAUD_SetDuty_FixedPeriodShifted                                                         **
**                     Remove critical section in Pwm_HW_TAUD_GetOutputState                                          **
** 2.0.0: 05/07/2023 : - Update from "Pwm_Mapping.h to "Pwm_MemMap.h".                                                **
**                     - Update Exclusive_Area of PWM_ENTER_CRITICAL_SECTION/PWM_EXIT_CRITICAL_SECTION                **
**                     - Remove redundant implementation of Pwm_GaaNotifStatus[LddChannelId] = PWM_TRUE; in           **
**                     Pwm_HW_TAUD_EnableNotification                                                                 **
**                     - Change from Pwm_GblOutputState to LenRetOutputState in Pwm_HW_TAUD_GetOutputState            **
**                     - Remove pre-compile condition check for PWM_ENTER_CRITICAL_SECTION/PWM_EXIT_CRITICAL_SECTION  **
**                     - Update QAC message                                                                           **
**                     - Change ptrclass from PWM_CONFIG_DATA to REGSPACE for all local pointers that have ptrtype is **
**                     Pwm_TAUDUnitUserRegs, Pwm_TAUDUnitOsRegs, Pwm_TAUDChannelUserRegs                              **
**        11/05/2023 : Update header description for all function                                                     **
** 1.4.4: 13/07/2022 : Remove QAC message 1006                                                                        **
**        22/06/2022 : Added QAC message and header for message 1006                                                  **
**        08/06/2022 : Changed register access size of RH850_SV_SET_ICR_SYNCP from 16 bits to 8 bits                  **
** 1.4.3: 23/05/2022 : Remove redundant QAC header of message 1281                                                    **
**        18/05/2022 : Added new process to reset value for TAUD3 Interrupt Number Selection register in              **
**                     Pwm_HW_TAUD_DeInitChannel                                                                      **
**                     Added new process to initialize value for TAUD3 Interrupt Number Selection register in         **
**                     Pwm_HW_TAUD_InitChannel, Pwm_HW_TAUD_SynchronousInit                                           **
**        09/05/2022 : Removed "else" statement don't use when no action required                                     **
**        18/04/2022 : Changed MAX_DUTY_CYCLE to PWM_MAX_DUTY_CYCLE_VALUE and                                         **
**                             MIN_DUTY_CYCLE to PWM_MIN_DUTY_CYCLE_VALUE                                             **
** 1.4.2: 26/02/2022 : Replace variable LulIndex with LucHWIPType on aaTimerUnitConfig array in Pwm_HW_TAUD_InitUnit  **
**        22/02/2022 : Added Coding rule violation header for message (2:2982) and updated PRQA comment.              **
** 1.4.1: 11/12/2021 : Added loop for check  HWIPType before call HWUnit in function Pwm_HW_TAUD_InitUnit             **
**        21/11/2021 : Update QAC message for U2Bx                                                                    **
**        13/11/2021 : Added feature interrupt selection for TAUD3                                                    **
**        07/10/2021 : Added a process to disable TAUDnTOE and set TAUDnTO to default Idle State for channel in       **
**                     Pwm_HW_TAUD_SynchronousStop.                                                                   **
** 1.3.2: 21/09/2021 : Updated compile switch of Pwm_HW_TAUD_SetDuty_FixedPeriodShifted.                              **
**        06/09/2021 : Removed Critical Section in Pwm_HW_TAUD_SynchronousStart, Pwm_HW_TAUD_SynchronousStop.         **
**        28/08/2021 : Corrected #if defined(PWM_E_REWRITE_FAILED) to #if(STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)  **
**        12/08/2021 : Reverted the setting Disable Count Operation in Pwm_HW_TAUD_InitUnit.                          **
**        04/08/2021 : Device specific implementation moved from Pwm common file.                                     **
**                     Error checking at Pwm_HW_TAUD_SetPeriodAndDuty move to Pwm_SetPeriodAndDuty API.               **
**                     Format source code unified within module.                                                      **
** 1.3.1: 02/07/2021 : Add QAC message 9.5.0                                                                          **
**                     Format source code to 120 characters                                                           **
**                     Improve Violation tag (remove START/END)                                                       **
**        14/06/2021 : Updated declaration of LpTAUDChannelConfigData in                                              **
**                     Pwm_HW_TAUD_DisableNotification                                                                **
**        22/05/2021 : Removed redundant variable in                                                                  **
**                     Pwm_HW_TAUD_SetPeriodAndDuty                                                                   **
**        21/05/2021 : Updated the setting value of Pwm_GaaChannelIdleStatus                                          **
**                     in Pwm_HW_TAUD_SynchronousStop                                                                 **
**                     Removed the LucTimerUnitType in DET checking in                                                **
**                     Pwm_HW_TAUD_SetPeriodAndDuty                                                                   **
**        19/05/2021 : Updated to remove redundant check and replace check use                                        **
**                     ucPwmTauType by ucTimerUnitType:                                                               **
**                     Pwm_HW_TAUD_InitChannel, Pwm_HW_TAUD_DeInitChannel,                                            **
**                     Pwm_HW_TAUD_SetDutyCycle, Pwm_HW_TAUD_SynchronousStart,                                        **
**                     Pwm_HW_TAUD_SetOutputToIdle, Pwm_HW_TAUD_GetOutputState                                        **
**                     Pwm_HW_TAUD_EnableNotification,                                                                **
**                     Pwm_HW_TAUD_DisableNotification,                                                               **
**                     Pwm_HW_TAUD_SelectChannelClk,                                                                  **
**                     Pwm_HW_TAUD_SetChannelOutput,                                                                  **
**                     Pwm_HW_TAUD_SynchronousInit,                                                                   **
**                     Pwm_HW_TAUD_SynchronousStart,                                                                  **
**                     Pwm_HW_TAUD_SetPeriodAndDuty                                                                   **
**        15/05/2021 : Fixed Coding Rule and tailor space                                                             **
**        12/05/2021 : Changed PWM_HW_TAUD to PWM_TAUD_UNIT_INDEX                                                     **
**        10/05/2021 : Added the setting value of Pwm_GaaChannelIdleStatus                                            **
**                     in Pwm_HW_TAUD_InitChannel, Pwm_HW_TAUD_SynchronousStop                                        **
**        05/05/2021 : Updated to use LusChannelMask instead of                                                       **
**                     LpTAUDProperties->usChannelMask in                                                             **
**                     Pwm_HW_TAUD_SetDuty_FixedPeriodShifted                                                         **
** 1.3.0: 17/11/2020 : Updated Pwm_HW_TAUD_StartOutput to mask correctly the                                          **
**                     bits value in the Output Registers.                                                            **
**        05/12/2020 : Removed Initialized Output Registers and corrected                                             **
**                     masking values in Pwm_HW_TAUD_StartOutput.                                                     **
** 1.2.0: 22/08/2020 : Release                                                                                        **
** 1.1.2: 22/08/2020 : Added "(PWM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)"                                            **
**                     Dem.h condition for Dem.h                                                                      **
** 1.1.1: 03/08/2020 : Check ucPwmTAUType for Pwm_HW_TAUD_SynchronousStart                                            **
** 1.1.0: 19/06/2020 : Release                                                                                        **
** 1.0.4: 05/06/2020 : Fixed CS in Pwm_HW_TAUD_SetDutyCycle and Callback func                                         **
**                     and Pwm_HW_TAUD_SetDuty_FixedPeriodShifted                                                     **
** 1.0.3: 27/05/2020 : removed redundant assignment "LpTAUDChannelConfigData"                                         **
**                     in Pwm_HW_TAUD_Callback function and                                                           **
** 1.0.2: 20/05/2020 : removed CRITICAL_SECTION                                                                       **
**                      in Pwm_HW_TAUD_SynchronousInit func                                                           **
** 1.0.1: 19/05/2020 : Changed "uinteger uiPolarity;" to "uint8 ucPolarity;"                                          **
**                     Changed "uiIdleLevel" to "ucIdleLevel"                                                         **
**                     Changed "uinteger uiPwmTAUType;"                                                               **
**                                 to "uint8 ucPwmTAUType;"                                                           **
**                     Changed "uiTimerMode" to "ucTimerMode"                                                         **
** 1.0.0: 30/03/2020 : Initial Version.                                                                               **
**                                                                                                                    */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for module version information and other types declarations */
#include "Pwm.h"
#include "Pwm_Ram.h"
#if (PWM_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Pwm.h"
#endif
/* Included for DEM */
#if ((STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED) || (STD_ON == PWM_INTERRUPT_CONSISTENCY_CHECK))
#include "Dem.h"
#endif
#if (PWM_DEV_ERROR_DETECT == STD_ON)
/* Included for the declaration of Det_ReportError() */
#include "Det.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_TAUD_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION_VALUE
#define PWM_TAUD_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION_VALUE
#define PWM_TAUD_LLDRIVER_C_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION_VALUE
/* Module software version information */
#define PWM_TAUD_LLDRIVER_C_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION_VALUE
#define PWM_TAUD_LLDRIVER_C_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION_VALUE
#define PWM_TAUD_LLDRIVER_C_SW_PATCH_VERSION            PWM_SW_PATCH_VERSION_VALUE


#if (PWM_TAUD_UNIT_USED == STD_ON)
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (PWM_TAUD_LLDRIVER_AR_RELEASE_MAJOR_VERSION != PWM_TAUD_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm_TAUD_LLDriver.c : Mismatch in Release Major Version"
#endif
#if (PWM_TAUD_LLDRIVER_AR_RELEASE_MINOR_VERSION != PWM_TAUD_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Pwm_TAUD_LLDriver.c : Mismatch in Release Minor Version"
#endif
#if (PWM_TAUD_LLDRIVER_AR_RELEASE_REVISION_VERSION != PWM_TAUD_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Pwm_TAUD_LLDriver.c : Mismatch in Release Revision Version"
#endif
#if (PWM_TAUD_LLDRIVER_SW_MAJOR_VERSION != PWM_TAUD_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Pwm_TAUD_LLDriver.c : Mismatch in Software Major Version"
#endif
#if (PWM_TAUD_LLDRIVER_SW_MINOR_VERSION != PWM_TAUD_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Pwm_TAUD_LLDriver.c : Mismatch in Software Minor Version"
#endif
#if (PWM_TAUD_LLDRIVER_SW_PATCH_VERSION != PWM_TAUD_LLDRIVER_C_SW_PATCH_VERSION)
  #error "Pwm_TAUD_LLDriver.c : Mismatch in Software Patch Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:0311)    : Dangerous pointer cast results in loss of const qualification.                               */
/* Rule                : MISRA C:2012 Rule-11.8, CERTCCM EXP05                                                        */
/* JV-01 Justification : This is to achieve throughput in the code.                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
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
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : MISRA C:2012 Rule-18.4, CERTCCM EXP08, CWE Rule CWE-188, CWE-398, CWE-569                    */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0499)    : Right operand of shift operator is greater than or equal to the width of the essential type  */
/*                       of the left operand.                                                                         */
/* Rule                : MISRA C:2012 Rule-12.2, CERTCCM INT34, CWE Rule CWE-681, CWE-682, CWE-738                    */
/* JV-01 Justification : The result has been ensured by casting to the same Type                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP39, EXP11, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:4304)    : An expression of 'essentially Boolean' type (%1s) is being cast to unsigned type '%2s'.      */
/* Rule                : MISRA C:2012 Rule-10.5, CWE Rule CWE-704                                                     */
/* JV-01 Justification : This is accepted. This casting from boolean to unsigned type for values 0 and 1 does not     */
/*                       make data conflict.                                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : This in-line assembler construct is a language extension. The code has been ignored.         */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTCCM MSC14                                       */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1338)    : The parameter '%s' is being modified.                                                        */
/* Rule                : MISRA C:2012 Rule-17.8                                                                       */
/* JV-01 Justification : This in case, parameter is not const, it could be accepted for modification                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : MISRA C:2012 Rule-8.7, CERTCCM DCL19, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : MISRA C:2012 Dir-4.1, CERTCCM MSC07, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563,     */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2983)    : This assignment is redundant. The value of this object is never subsequently used.           */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563,     */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The value is to increment the pointer to the next item.                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3214)    : The macro '%s' is not used and could be removed.                                             */
/* Rule                : MISRA C:2012 Rule-2.5                                                                        */
/* JV-01 Justification : This can be accepted, it will be used in some case of configuration.                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
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
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
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
/* Message (4:1881)    : The operands of this equality operator are expressions of different 'essential type'         */
/*                       categories (enum and unsigned).                                                              */
/* Rule                : CERTCCM INT02, MISRA C:2012 Rule-10.4                                                        */
/* JV-01 Justification : All are unsigned long type variables and do not correspond to the pointed out contents.      */
/*                       No problem.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/***********************************************************************************************************************
**                                             Local Function Prototypes                                              **
***********************************************************************************************************************/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"

static FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_IntNotification(Pwm_ChannelType LddChannelId);

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_InitUnit
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function. This function sets the clock pre-scaler,
**                         PWM mode, Period, Duty cycle and polarity for all configured channels.
**                         This function also disables the interrupts (Notifications) and resets the interrupt request
**                         pending flags.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddConfigPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpTAUDUnitConfig, Pwm_GaaHWIP_Used
**
** Functions invoked     : None
**
** Registers Used        : TAUDnTPS, TAUDnBRS, TAUDnTT.
**
** Reference ID          : PWM_DUD_ACT_017, PWM_DUD_ACT_017_REG001, PWM_DUD_ACT_017_REG002, PWM_DUD_ACT_017_REG003,
** Reference ID          : PWM_DUD_ACT_017_REG004, PWM_DUD_ACT_017_REG005, PWM_DUD_ACT_017_GBL001
***********************************************************************************************************************/
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_InitUnit(P2CONST (Pwm_ConfigType, AUTOMATIC, PWM_CONFIG_DATA) LddConfigPtr)
{
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpTAUDUnitConfig;
  /* Pointer pointing to the TAU Unit user control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  #if (PWM_TAUD_PRESCALER == STD_ON)
  /* Pointer pointing to the TAU Unit OS control registers */
  P2VAR(volatile Pwm_TAUDUnitOsRegs, AUTOMATIC, REGSPACE) LpTAUDUnitOsReg;
  #endif
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  VAR(uint32, AUTOMATIC) LulCount;

  for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_HW_IP_CONFIG; LulCount++)                              /* PRQA S 2877 # JV-01 */
  {
    LucHWIPType = Pwm_GaaHWIP_Used[LulCount].ucIndex;
    if (PWM_HWIP_TAUD == LucHWIPType)                                                                                   /* PRQA S 3416 # JV-01 */
    {
      /* Save the start of TAUD Unit Configuration in the global pointer */
      Pwm_GpTAUDUnitConfig = (P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA))                        /* PRQA S 0316 # JV-01 */
      (LddConfigPtr->aaTimerUnitConfig[LucHWIPType]);
    } /* else No action required */
  }

  /* Update the TAU config pointer to point to the current TAU */
  LpTAUDUnitConfig = Pwm_GpTAUDUnitConfig;
  /* Loop to set the configured pre-scaler for the TAU units */
  for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_TAUD_UNITS_CONFIG; LulCount++)                         /* PRQA S 2877 # JV-01 */
  {
    /* Get the pointer to the TAU unit registers */
    LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
    #if (PWM_TAUD_PRESCALER == STD_ON)
    /* Get the pointer to the TAU OS control registers */
    LpTAUDUnitOsReg = LpTAUDUnitConfig->pOsCntlRegs;
    /* Check for Prescaler setting by the PWM module for TAU Unit */
    if (PWM_TRUE == LpTAUDUnitConfig->blConfigurePrescaler)
    {
      /* Set all channels bits of TAU unit to disable the count operation */
      LpTAUDUnitUserReg->usTAUDnTT = PWM_STOP_TAUD_ALL_CH;
      /* Load the configured pre-scaler value */
      LpTAUDUnitOsReg->usTAUDnTPS = LpTAUDUnitConfig->usPrescaler;
      /* Load the configured baudrate value */
      LpTAUDUnitOsReg->ucTAUDnBRS = LpTAUDUnitConfig->ucBaudRate;
    }
    else
    {
      /* Set the configured channel bits to disable the count operation */
      LpTAUDUnitUserReg->usTAUDnTT = LpTAUDUnitConfig->usTAUChannelMask;
    }
    #else
    /* Set the configured channel bits to disable the count operation */
    LpTAUDUnitUserReg->usTAUDnTT = LpTAUDUnitConfig->usTAUChannelMask;
    #endif
    /* Increment the pointer to the next TAU Unit */
    LpTAUDUnitConfig++;                                                                                                 /* PRQA S 2983 # JV-01 */
  } /* End of PWM_TOTAL_TAUD_UNITS_CONFIG for loop */
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_StartOutput
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function. This function sets the clock pre-scaler,
**                         PWM mode, Period, Duty cycle and polarity for all configured channels.
**                         This function also disables the interrupts (Notifications) and resets the interrupt request
**                         pending flags.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpTAUDUnitConfig
**
** Functions invoked     : None.
**
** Registers Used        : TAUDnTOM, TAUDnTOC, TAUDnTOL, TAUDnTDE, TAUDnTRE, TAUDnTME, TAUDnTDM,
**                         TAUDnTO, TAUDnTOE, TAUDnRDE, TAUDnTS.
**
** Reference ID          : PWM_DUD_ACT_018, PWM_DUD_ACT_018_REG008, PWM_DUD_ACT_018_REG009, PWM_DUD_ACT_018_REG010,
** Reference ID          : PWM_DUD_ACT_018_REG011, PWM_DUD_ACT_018_REG012, PWM_DUD_ACT_018_REG013,
** Reference ID          : PWM_DUD_ACT_018_REG014, PWM_DUD_ACT_018_REG015, PWM_DUD_ACT_018_REG016,
** Reference ID          : PWM_DUD_ACT_018_REG017, PWM_DUD_ACT_018_REG018, PWM_DUD_ACT_018_REG019,
** Reference ID          : PWM_DUD_ACT_018_REG020
***********************************************************************************************************************/
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_StartOutput(void)
{
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpTAUDUnitConfig;
  /* Pointer pointing to the TAU Unit user control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  /* Pointer pointing to the TAU Unit OS control registers */
  P2VAR(volatile Pwm_TAUDUnitOsRegs, AUTOMATIC, REGSPACE) LpTAUDUnitOsReg;
  VAR(uint32, AUTOMATIC) LulCount;

  /* Update the TAU Unit config pointer */
  LpTAUDUnitConfig = Pwm_GpTAUDUnitConfig;
  for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_TAUD_UNITS_CONFIG; LulCount++)                         /* PRQA S 2877 # JV-01 */
  {
    /* Update the pointer for the base address of the TAU unit registers */
    LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
    LpTAUDUnitOsReg = LpTAUDUnitConfig->pOsCntlRegs;
    /* Set the corresponding bits to disable TOm operation */
    LpTAUDUnitUserReg->usTAUDnTOE = (LpTAUDUnitUserReg->usTAUDnTOE & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask));
    /* Set the corresponding bits as per the configured Idle state */
    LpTAUDUnitUserReg->usTAUDnTO =
      ((LpTAUDUnitUserReg->usTAUDnTO & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask)) | LpTAUDUnitConfig->usTOMask);
    /* Set the Mode (Synchronous/Independent channel operation mode)*/
    LpTAUDUnitOsReg->usTAUDnTOM =
      ((LpTAUDUnitOsReg->usTAUDnTOM & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask)) | LpTAUDUnitConfig->usTOMMask);
    /* Set the corresponding bits to specify the TOm (channel output bit) operation mode */
    LpTAUDUnitOsReg->usTAUDnTOC =
      ((LpTAUDUnitOsReg->usTAUDnTOC & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask)) | LpTAUDUnitConfig->usTOCMask);
    /* Set the corresponding bits to disable Dead time operation */
    LpTAUDUnitOsReg->usTAUDnTDE = (LpTAUDUnitOsReg->usTAUDnTDE & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask));
    /* Set the corresponding bits to disable Real-time output */
    LpTAUDUnitOsReg->usTAUDnTRE = (LpTAUDUnitOsReg->usTAUDnTRE & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask));
    /* Set the corresponding bits to disable Modulated output */
    LpTAUDUnitUserReg->usTAUDnTME = (LpTAUDUnitUserReg->usTAUDnTME & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask));
    /* Set the Mode (Dead time output mode) */
    LpTAUDUnitOsReg->usTAUDnTDM = (LpTAUDUnitOsReg->usTAUDnTDM & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask));
    /* Set the corresponding bits to enable/disable TOm operation */
    LpTAUDUnitUserReg->usTAUDnTOE =
      ((LpTAUDUnitUserReg->usTAUDnTOE & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask)) | LpTAUDUnitConfig->usTOEMask);
    /* Set the corresponding bits as per the configured Polarity */
    LpTAUDUnitUserReg->usTAUDnTOL =
      ((LpTAUDUnitUserReg->usTAUDnTOL & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask)) | LpTAUDUnitConfig->usTOLMask);
    /* Set the corresponding bits to Enable simultaneous rewrite of the data register */
    LpTAUDUnitOsReg->usTAUDnRDE = (LpTAUDUnitOsReg->usTAUDnRDE | LpTAUDUnitConfig->usTAUChannelMask);
    #if (PWM_SYNC_START_SUPPORT == STD_ON)
    /* Set the channel bits that are not configured for synchronous start to enable the count operation */
    LpTAUDUnitUserReg->usTAUDnTS = (LpTAUDUnitConfig->usTAUChannelMask ^ LpTAUDUnitConfig->usSyncInitMask);
    #else
    /* Set the corresponding channel bit to enable the count operation */
    LpTAUDUnitUserReg->usTAUDnTS = LpTAUDUnitConfig->usTAUChannelMask;
    #endif
    /* Increment the pointer for the next TAU Unit */
    LpTAUDUnitConfig++;                                                                                                 /* PRQA S 2983 # JV-01 */
  } /* End of TAU Units for loop */
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_InitChannel
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function. This function sets the clock pre-scaler,
**                         PWM mode, Period, Duty cycle and polarity for all configured channels.
**                         This function also disables the interrupts (Notifications) and resets the interrupt request
**                         pending flags.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpChannelConfig, Pwm_GaaChannelIdleStatus, Pwm_GaaChannelConstantStatus,
**                         Pwm_GaaNotifStatus
**
** Functions invoked     : Pwm_HW_TAUD_CalculateDuty.
**
** Registers Used        : TAUDnCDRm, TAUDnCMORm, TAUD3INTNOSELn.
**
** Reference ID          : PWM_DUD_ACT_019, PWM_DUD_ACT_019_REG001, PWM_DUD_ACT_019_REG002, PWM_DUD_ACT_019_REG003,
** Reference ID          : PWM_DUD_ACT_019_REG004, PWM_DUD_ACT_019_REG005, PWM_DUD_ACT_019_REG006,
** Reference ID          : PWM_DUD_ACT_019_GBL001, PWM_DUD_ACT_019_GBL002, PWM_DUD_ACT_019_GBL003,
** Reference ID          : PWM_DUD_ACT_019_GBL004, PWM_DUD_ACT_019_REG007
***********************************************************************************************************************/
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_InitChannel(void)                                                              /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDProperties;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Pointer to the TAU Master Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDMasterProperties;                                    /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Pointer used for TAU channel control registers */
  P2VAR(volatile Pwm_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;
  /* Pointer used for TAU Master channel control registers */
  P2VAR(volatile Pwm_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDMasterChannelReg;                                  /* PRQA S 3678 # JV-01 */
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  VAR(Pwm_PeriodType, AUTOMATIC) LddMasterPeriod;
  VAR(Pwm_PeriodType, AUTOMATIC) LddSlaveDuty;
  VAR(uint8, AUTOMATIC) LucVar;
  VAR(uint32, AUTOMATIC) LulCount;
  /* Loop to set the attributes of TAU channels */
  LpChannelConfig = Pwm_GpChannelConfig;
  /* Initialize all PWM channels configured to support synchronous start/stop of timers,
     this excludes initialization of channels that will be handled by complex drivers */
  for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_CHANNELS_CONFIG; LulCount++)
  {
    /* Set TAU channel config data pointer */
    LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                      /* PRQA S 0317 # JV-01 */
    /* Get the Timer Unit Type*/
    LucTimerUnitType = LpChannelConfig->ucTimerUnitType;
    if ((uint8)PWM_HWIP_TAUD == LucTimerUnitType)                                                                       /* PRQA S 3416 # JV-01 */
    {
      #if (PWM_SYNC_START_SUPPORT == STD_ON)
      /* Set attributes of TAU channels which are not to be started synchronously */
      if ((PWM_FALSE == LpChannelConfig->blSyncStartReq)
        && (PWM_FALSE == LpTAUDChannelConfigData->blComplexDriverInit))
      #endif
      {
        /* Get the pointer to the TAU channel properties */
        LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;   /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
        /* Get the pointer to the TAU channel control registers */
        LpTAUDChannelReg = LpTAUDProperties->pCntlRegs;
        /* Initialize value for TAUD3 Interrupt Number Selection register */
        #if (STD_ON == PWM_TAUD3_UNIT_USED)
        /* Check the TAUD3 Interrupt Number Selection register is configured for the current channel */
        if (NULL_PTR != LpTAUDProperties->pTAUD3INTNOSELxReg)
        {
          RH850_SET_IOREG_SYNCP(32, LpTAUDProperties->pTAUD3INTNOSELxReg,                                               /* PRQA S 1006 # JV-01 */
                                LpTAUDProperties->ulTAUD3InterruptSelectionMask);
        } /* else No action required */
        #endif
        /* Check for channel in the Master Mode */
        if ((uint8)PWM_MASTER_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)
        {
          /* Update the CMORm register of Master with the usCMORRegSettingsMask based on the configuration */
          *LpTAUDProperties->pCMORReg = LpTAUDProperties->usCMORRegSettingsMask;
          if ((Pwm_PeriodType)PWM_TAUD_MIN_PERIOD_VAL != LpTAUDProperties->ddDefaultPeriodOrDuty)
          {
            LpTAUDChannelReg->usTAUDnCDRm = (uint16)(LpTAUDProperties->ddDefaultPeriodOrDuty) - (uint16)PWM_ONE;
          }
          else
          {
            LpTAUDChannelReg->usTAUDnCDRm = PWM_TAUD_MIN_PERIOD_VAL;
          }
        }
        /* Channel in Slave Mode */
        else
        {
          /* Master offset from the slave channel */
          LucVar = LpTAUDChannelConfigData->ucMasterOffset;
          /* Get the pointer to the TAU Master channel properties */
          LpTAUDMasterProperties =
            (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))(LpChannelConfig - LucVar)->pChannelProp;       /* PRQA S 0311, 0316, 0488, 3432 # JV-01, JV-01, JV-01, JV-01 */
          /* if Default Period of Master of the slave channel is not zero */
          if ((Pwm_PeriodType)PWM_TAUD_MIN_PERIOD_VAL != LpTAUDMasterProperties->ddDefaultPeriodOrDuty)
          {
            /* Pointer to the Master channel registers */
            LpTAUDMasterChannelReg = LpTAUDMasterProperties->pCntlRegs;
            /* Get Master's period */
            LddMasterPeriod = LpTAUDMasterChannelReg->usTAUDnCDRm;
            /* Get Slave's Duty */
            LddSlaveDuty = LpTAUDProperties->ddDefaultPeriodOrDuty;
            /* Load the Absolute duty value in to the CDR Register */
            LpTAUDChannelReg->usTAUDnCDRm = (uint16)Pwm_HW_TAUD_CalculateDuty(LddMasterPeriod, LddSlaveDuty);
          }
          else
          {
            /* Load the zero in to the CDR Register */
            LpTAUDChannelReg->usTAUDnCDRm = PWM_TAUD_MIN_PERIOD_VAL;
          }
          /* Update the CMORm register of Slave with the usCMORRegSettingsMask based on the configuration */
          *LpTAUDProperties->pCMORReg = LpTAUDProperties->usCMORRegSettingsMask;
        } /* End of Channel in Slave Mode */
        /* Initialize the Idle state of normal channel as PWM_FALSE */
        Pwm_GaaChannelIdleStatus[LulCount] = (uint8)PWM_FALSE;                                                          /* PRQA S 4304 # JV-01 */
        #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
        /* Initialize the Constant state status of normal channel as PWM_FALSE */
        Pwm_GaaChannelConstantStatus[LulCount] = (uint8)PWM_FALSE;                                                      /* PRQA S 4304 # JV-01 */
        #endif
      } /* else No action required */
      /* End of if ((PWM_FALSE == LpChannelConfig->blSyncStartReq)
                 && (PWM_FALSE == LpTAUDChannelConfigData->blComplexDriverInit)) */
      #if (PWM_SYNC_START_SUPPORT == STD_ON)
      /* Set attributes of TAU channels which are started synchronously */
      if ((PWM_TRUE == LpChannelConfig->blSyncStartReq) && (PWM_FALSE == LpTAUDChannelConfigData->blComplexDriverInit))
      {
        /* Initialize the Idle state of Synchronous channel to Idle */
        Pwm_GaaChannelIdleStatus[LulCount] = (uint8)PWM_TRUE;                                                           /* PRQA S 4304 # JV-01 */
      } /* else No action required */
      #endif /* End of PWM_SYNC_START_SUPPORT == STD_ON*/
      #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
      /* Set the Notification status as PWM_FALSE */
      Pwm_GaaNotifStatus[LulCount] = (uint8)PWM_FALSE;                                                                  /* PRQA S 4304 # JV-01 */
      #endif
    } /* else No action required */
    /* End of LucTimerUnitType checking */
    /* Increment the pointer to the next channel */
    LpChannelConfig++;
  } /* End of for loop channels */
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_TAUD_DeInitUnit
**
** Service ID           : NA
**
** Description          : This is PWM Driver Component support function. This function de-initializes all the PWM
**                        channels by setting to their configured Idle state, disabling the notifications,
**                        resetting all the registers and stopping the PWM mode of operation of corresponding timer.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Pre-conditions       : NA
**
** Global Variable used : Pwm_GpTAUDUnitConfig
**
** Function(s) invoked  : None
**
** Registers Used       : TAUDnTT, TAUDnTOM, TAUDnTOC, TAUDnTOL, TAUDnTOE, TAUDnTO, TAUDnRDE.
**
** Reference ID         : PWM_DUD_ACT_020, PWM_DUD_ACT_020_REG001, PWM_DUD_ACT_020_REG002, PWM_DUD_ACT_020_REG003,
** Reference ID         : PWM_DUD_ACT_020_REG004, PWM_DUD_ACT_020_REG005, PWM_DUD_ACT_020_REG006,
** Reference ID         : PWM_DUD_ACT_020_REG007
***********************************************************************************************************************/
#if (PWM_TAUD_UNIT_USED == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_DeInitUnit(void)
{
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpTAUDUnitConfig;
  /* Pointer pointing to the TAU Unit user control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  /* Pointer pointing to the TAU Unit OS control registers */
  P2VAR(volatile Pwm_TAUDUnitOsRegs, AUTOMATIC, REGSPACE) LpTAUDUnitOsReg;
  VAR(uint32, AUTOMATIC) LulCount;

  /* Update the TAU config pointer to point to the current TAU */
  LpTAUDUnitConfig = Pwm_GpTAUDUnitConfig;
  for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_TAUD_UNITS_CONFIG; LulCount++)                         /* PRQA S 2877 # JV-01 */
  {
    /* Update the pointer for the base address of the TAU unit registers */
    LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
    /* Update the pointer for base address of the TAU Unit OS control registers */
    LpTAUDUnitOsReg = LpTAUDUnitConfig->pOsCntlRegs;
    /* Set the configured channel bits to disable the count operation */
    LpTAUDUnitUserReg->usTAUDnTT = LpTAUDUnitConfig->usTAUChannelMask;
    /* Reset all the configured channels registers */
    LpTAUDUnitUserReg->usTAUDnTOE = (LpTAUDUnitUserReg->usTAUDnTOE & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask));
    /* Set the PWM output to its corresponding idle state */
    LpTAUDUnitUserReg->usTAUDnTO = (LpTAUDUnitUserReg->usTAUDnTO & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask))
                                    | (LpTAUDUnitConfig->usTOMask);
    LpTAUDUnitOsReg->usTAUDnTOM = LpTAUDUnitOsReg->usTAUDnTOM & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask);
    LpTAUDUnitOsReg->usTAUDnTOC = (LpTAUDUnitOsReg->usTAUDnTOC & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask));
    LpTAUDUnitUserReg->usTAUDnTOL = (LpTAUDUnitUserReg->usTAUDnTOL & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask));
    LpTAUDUnitOsReg->usTAUDnRDE = (LpTAUDUnitOsReg->usTAUDnRDE & (uint16)(~LpTAUDUnitConfig->usTAUChannelMask));
    /* Increment the pointer to the next TAU unit */
    LpTAUDUnitConfig++;                                                                                                 /* PRQA S 2983 # JV-01 */
  } /* End of TAU units for loop */
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_DE_INIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_TAUD_DeInitChannel
**
** Service ID           : NA
**
** Description          : This is PWM Driver Component support function. This function de-initializes all the PWM
**                        channels by setting to their configured Idle state, disabling the notifications, resetting
**                        all the registers and stopping the PWM mode of operation of corresponding timer.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Pre-conditions       : NA
**
** Global Variable used : Pwm_GpChannelConfig, Pwm_GaaNotifStatus, Pwm_GaaChannelIdleStatus,
**                        Pwm_GaaChannelConstantStatus
**
** Function(s) invoked  : None
**
** Registers Used       : TAUDnCDRm, TAUDnCMORm, TAUD3INTNOSELn.
**
** Reference ID         : PWM_DUD_ACT_021, PWM_DUD_ACT_021_REG001, PWM_DUD_ACT_021_REG002, PWM_DUD_ACT_021_REG003
** Reference ID         : PWM_DUD_ACT_021_GBL001, PWM_DUD_ACT_021_GBL002, PWM_DUD_ACT_021_GBL003
** Reference ID         : PWM_DUD_ACT_021_REG004
***********************************************************************************************************************/
#if (PWM_DE_INIT_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_DeInitChannel(void)                                                            /* PRQA S 3006 # JV-01 */
{
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDProperties;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Pointer used for TAUD channel control registers */
  P2VAR(volatile Pwm_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  VAR(uint32, AUTOMATIC) LulCount;

  /* Loop to reset the attributes of TAUD channels */
  LpChannelConfig = Pwm_GpChannelConfig;
  for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_CHANNELS_CONFIG; LulCount++)
  {
    /* Get the Timer Unit Type*/
    LucTimerUnitType = LpChannelConfig->ucTimerUnitType;
    if ((uint8)PWM_HWIP_TAUD == LucTimerUnitType)                                                                       /* PRQA S 3416 # JV-01 */
    {
      /* Get the pointer to the TAUD channel properties */
      LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;     /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
      /*Reset value for TAUD3 Interrupt Number Selection register*/
      #if (STD_ON == PWM_TAUD3_UNIT_USED)
      /* Check the TAUD3 Interrupt Number Selection register is configured for the current channel */
      if (NULL_PTR != LpTAUDProperties->pTAUD3INTNOSELxReg)
      {
        RH850_CLEAR_IOREG_SYNCP(32, LpTAUDProperties->pTAUD3INTNOSELxReg, PWM_RESET_TAUD3INTNOSEL_REG);                 /* PRQA S 1006 # JV-01 */
      } /* else No action required */
      #endif
      /* Disabling the Interrupt processing of the current channel with dummy read and execute syncp instruction */
      #if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) || (PWM_SET_CHANNEL_OUTPUT_API == STD_ON))
      if (NULL_PTR != LpTAUDProperties->pEICReg)
      {
        RH850_SV_SET_ICR_SYNCP(8, LpTAUDProperties->pEICReg, PWM_DISABLE_INTR_MASK);                                    /* PRQA S 0751, 1006 # JV-01, JV-01 */
      } /* else No action required */
      #endif
      /* Get the pointer to the TAUD channel control registers */
      LpTAUDChannelReg = LpTAUDProperties->pCntlRegs;
      /* Reset the CMORm register of the configured channel*/
      *LpTAUDProperties->pCMORReg = PWM_TAUD_RESET_CMOR_REG;
      /* Reset the CDRm register of the configured channel */
      LpTAUDChannelReg->usTAUDnCDRm = PWM_RESET_TAUDCDR_REG;
      #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
      /* Notification status of this channel to PWM_FALSE */
      Pwm_GaaNotifStatus[LulCount] = (uint8)PWM_FALSE;                                                                  /* PRQA S 4304 # JV-01 */
      #endif
      /* Set the Idle state status of this channel as PWM_TRUE */
      Pwm_GaaChannelIdleStatus[LulCount] = (uint8)PWM_TRUE;                                                             /* PRQA S 4304 # JV-01 */
      #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
      Pwm_GaaChannelConstantStatus[LulCount] = (uint8)PWM_FALSE;                                                        /* PRQA S 4304 # JV-01 */
      #endif
    } /* else No action required */
    /* End of LucTimerUnitType checking */
    /* Increment the pointer to the next channel */
    LpChannelConfig++;
  } /* End of for loop */
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_DE_INIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_TAUD_SetDutyCycle
**
** Service ID           : NA
**
** Description          : This is PWM Driver Component support function.
**                        This function updates the duty cycle counter value in the hardware registers.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : LddChannelId and LusDutyCycle
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Pre-conditions       : NA
**
** Global Variable used : Pwm_GpTAUDUnitConfig,
**                        Pwm_GpChannelConfig, Pwm_GaaChannelIdleStatus,
**
** Functions invoked    : Det_ReportError, Pwm_HW_TAUD_CalculateDuty, Pwm_HW_TAUD_SetDuty_FixedPeriodShifted.
**                        PWM_DEM_REPORT_ERROR
**
** Registers Used       : TAUDnTOE, TAUDnCDRm, TAUDnRDT, TAUDnRSF.
**
** Reference ID         : PWM_DUD_ACT_023, PWM_DUD_ACT_023_CRT001, PWM_DUD_ACT_023_CRT002, PWM_DUD_ACT_023_CRT003,
** Reference ID         : PWM_DUD_ACT_023_CRT004, PWM_DUD_ACT_023_ERR001, PWM_DUD_ACT_023_ERR002,
** Reference ID         : PWM_DUD_ACT_023_ERR003, PWM_DUD_ACT_023_GBL001, PWM_DUD_ACT_023_GBL002
** Reference ID         : PWM_DUD_ACT_023_REG001, PWM_DUD_ACT_023_REG002, PWM_DUD_ACT_023_REG003,
** Reference ID         : PWM_DUD_ACT_023_REG004, PWM_DUD_ACT_023_REG005, PWM_DUD_ACT_023_REG006
***********************************************************************************************************************/
#if ((PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SET_PERIOD_AND_DUTY_API == STD_ON))
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_SetDutyCycle(Pwm_ChannelType LddChannelId, uint16 LusDutyCycle)
{
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpTAUDUnitConfig;
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Pointer pointing to the TAU Unit control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  /* Pointer used for TAU channel control registers */
  P2VAR(volatile Pwm_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(volatile Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDProperties;                                 /* PRQA S 3678 # JV-01 */
  /* Pointer to the TAU Master Channel Properties structure */
  P2VAR(volatile Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDMasterProperties;                           /* PRQA S 3678 # JV-01 */
  VAR(Pwm_PeriodType, AUTOMATIC) LddMasterPeriod;
  VAR(uint16, AUTOMATIC) LusTAUDSlavechannelMask;
  VAR(uint8, AUTOMATIC) LucVar;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  #endif
  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  VAR(boolean, AUTOMATIC) blDemReport;

  /* Initialize DEM report status */
  blDemReport = PWM_FALSE;
  #endif
  /* Initialize a pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  /* Set TAU channel config data pointer */
  LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                        /* PRQA S 0317 # JV-01 */
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  LucDetErrFlag = E_OK;
  if ((PWM_MAX_DUTY_CYCLE_VALUE == LusDutyCycle) && (PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
    && (PWM_TWO == LpTAUDChannelConfigData->ucMasterOffset))
  {
    /* Report to DET module */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_DUTYCYCLE_SID, PWM_E_PARAM_VALUE);
    LucDetErrFlag = E_NOT_OK;
  } /* else No action required */

  if (E_OK == LucDetErrFlag)
  #endif
  {
    /* Check for the channel Class Type */
    if (PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
    {
      /* Set Duty cycle for the required channel in FixedPeriodShifted Class Type */
      Pwm_HW_TAUD_SetDuty_FixedPeriodShifted(LddChannelId, LusDutyCycle);
    }
    else
    {
      /* Check for the channel in Master Mode */
      if ((uint8)PWM_MASTER_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)
      {
        /* Get the pointer to the TAU channel properties */
        LpTAUDProperties =
          (P2VAR(volatile Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;           /* PRQA S 0311, 0316 # JV-01, JV-01 */
        /* Initialize a pointer to the Master's control register configuration of TAU */
        LpTAUDChannelReg = LpTAUDProperties->pCntlRegs;
        /* Fetch the pointer to the current TAU Unit config */
        LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
        /* Fetch the pointer to the current TAU Unit Registers */
        LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
        /* Initialize slave channel mask */
        LusTAUDSlavechannelMask = PWM_TAUD_MASK_16BIT_INIT;
        /* Increment the channel Id */
        LddChannelId++;                                                                                                 /* PRQA S 1338, 3383 # JV-01, JV-01 */
        /* Increment the pointer to the slave channel */
        LpChannelConfig++;

        /* Enter Protected area */
        PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

        /* Get the master's period */
        LddMasterPeriod = LpTAUDChannelReg->usTAUDnCDRm;
        do
        {
          /* Get the pointer to the TAUD channel properties */
          LpTAUDProperties =
            (P2VAR(volatile Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;         /* PRQA S 0311, 0316 # JV-01, JV-01 */
          /* Initialize a pointer to the slave's control register configuration of TAU */
          LpTAUDChannelReg = LpTAUDProperties->pCntlRegs;
          /* Check whether the channel is set to its Idle state */
          if (PWM_TRUE == Pwm_GaaChannelIdleStatus[LddChannelId])                                                       /* PRQA S 1881 # JV-01 */
          {
            /* Enable the output of the current channel */
            LpTAUDUnitUserReg->usTAUDnTOE = (LpTAUDUnitUserReg->usTAUDnTOE | LpTAUDProperties->usChannelMask);          /* PRQA S 0404 # JV-01 */
            /* Set the Idle state of the channel to PWM_FALSE */
            Pwm_GaaChannelIdleStatus[LddChannelId] = (uint8)PWM_FALSE;                                                  /* PRQA S 4304 # JV-01 */
          } /* else No action required */

          /* Check whether simultaneous rewrite has been completed */
          if (PWM_TAUD_RESET_16BIT_REG ==                                                                               /* PRQA S 0404 # JV-01 */
            (uint16)(LpTAUDProperties->usChannelMask & LpTAUDUnitUserReg->usTAUDnRSF))
          {
            /* Load the Absolute duty value in to the CDR Register */
            LpTAUDChannelReg->usTAUDnCDRm =
              (uint16)Pwm_HW_TAUD_CalculateDuty(LddMasterPeriod, (Pwm_PeriodType)LusDutyCycle);
            /* Get the Slave channels mask */
            LusTAUDSlavechannelMask = LusTAUDSlavechannelMask | LpTAUDProperties->usChannelMask;
          }
          #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
          else
          {
            /* Set Dem error flag */
            blDemReport = PWM_TRUE;
          }
          #endif
          /* Increment the channel Id */
          LddChannelId++;                                                                                               /* PRQA S 1338, 3383 # JV-01, JV-01 */
          /* Increment the pointer to the next channel */
          LpChannelConfig++;
          if (PWM_TOTAL_CHANNELS_CONFIG > LddChannelId)
          {
            /* Set TAU channel config data pointer */
            LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                              /* PRQA S 0317 # JV-01 */
          } /* else No action required */
        } while ((PWM_TOTAL_CHANNELS_CONFIG > LddChannelId)
             && ((uint8)PWM_MASTER_CHANNEL != LpTAUDChannelConfigData->ucTimerMode));

        /* Set the corresponding channel Trigger bit to specifies the channel
           for which simultaneous rewrite is executed */
        LpTAUDUnitUserReg->usTAUDnRDT = LusTAUDSlavechannelMask;

        /* Exit Protected area */
        PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

        #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
        if (PWM_TRUE == blDemReport)
        {
          /*Report to DEM module*/
          PWM_DEM_REPORT_ERROR(PWM_E_REWRITE_FAILED, DEM_EVENT_STATUS_FAILED);
        } /* else No action required */
        #endif
      }
      /* In case of Slave Mode */
      else
      {
        /* Fetch the pointer to the current TAU Unit config */
        LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
        /* Get the pointer to the TAU channel properties */
        LpTAUDProperties =
          (P2VAR(volatile Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;           /* PRQA S 0311, 0316 # JV-01, JV-01 */
        /* Fetch the pointer to the current TAU Unit Registers */
        LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
        /* Get the offset of the Master from the slave channel */
        LucVar = LpTAUDChannelConfigData->ucMasterOffset;
        /* Get the pointer to the TAU Master channel properties */
        LpTAUDMasterProperties =
        (P2VAR(volatile Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))(LpChannelConfig - LucVar)->pChannelProp;  /* PRQA S 0311, 0316, 0488 # JV-01, JV-01, JV-01 */
        /* Initialize a pointer to the Master's control register configuration of TAU */
        LpTAUDChannelReg = LpTAUDMasterProperties->pCntlRegs;

        /* Enter Protected area */
        PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

        /* Get the master's period */
        LddMasterPeriod = LpTAUDChannelReg->usTAUDnCDRm;
        /* Initialize a pointer to the slave's control register configuration of TAU */
        LpTAUDChannelReg = LpTAUDProperties->pCntlRegs;
        /* Check whether the channel is set to its Idle state */
        if (PWM_TRUE == Pwm_GaaChannelIdleStatus[LddChannelId])                                                         /* PRQA S 1881 # JV-01 */
        {
          /* Enable the output of the current channel */
          LpTAUDUnitUserReg->usTAUDnTOE =                                                                               /* PRQA S 0404 # JV-01 */
            (LpTAUDUnitUserReg->usTAUDnTOE | LpTAUDProperties->usChannelMask);
          /* Set the Idle state of the channel to PWM_FALSE */
          Pwm_GaaChannelIdleStatus[LddChannelId] = (uint8)PWM_FALSE;                                                    /* PRQA S 4304 # JV-01 */
        } /* else No action required */

        /* Check whether simultaneous rewrite has been completed */
        if (PWM_TAUD_RESET_16BIT_REG == (uint16)(LpTAUDProperties->usChannelMask & LpTAUDUnitUserReg->usTAUDnRSF))      /* PRQA S 0404 # JV-01 */
        {
          /* Load the Absolute duty value in to the CDR Register */
          LpTAUDChannelReg->usTAUDnCDRm =
            (uint16)Pwm_HW_TAUD_CalculateDuty(LddMasterPeriod, (Pwm_PeriodType)LusDutyCycle);
          /* Set the corresponding channel Trigger bit to specifies the channel
             for which simultaneous rewrite is executed */
          LpTAUDUnitUserReg->usTAUDnRDT = LpTAUDProperties->usChannelMask;
        }
        #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
        else
        {
          /* Set Dem error flag */
          blDemReport = PWM_TRUE;
        }
        #endif

        /* Exit Protected area */
        PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

        #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
        if (PWM_TRUE == blDemReport)
        {
          PWM_DEM_REPORT_ERROR(PWM_E_REWRITE_FAILED, DEM_EVENT_STATUS_FAILED);
        } /* else No action required */
        #endif
      } /* End of the Slave channel */
    } /* End of (PWM_FIXED_PERIOD_SHIFTED != LpChannelConfig->enClassType) */
  } /* else No action required */
  /* End of if (E_OK == LucDetErrFlag) */
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* ((PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)) */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_TAUD_SetPeriodAndDuty
**
** Service ID           : NA
**
** Description          : This is PWM Driver Component support function.
**                        This function updates the Period and Duty cycle counter value in the hardware registers.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : LddChannelId, LddPeriod and LusDutyCycle
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Pre-conditions       : NA
**
** Global Variable used : Pwm_GpTAUDUnitConfig, Pwm_GpChannelConfig, Pwm_GaaChannelIdleStatus
**
** Function invoked     : Det_ReportError, Pwm_HW_TAUD_SetDutyCycle, Pwm_HW_TAUD_CalculateDuty, PWM_DEM_REPORT_ERROR
**
** Registers Used       : TAUDnTOE, TAUDnCDRm, TAUDnRDT, TAUDnRSF.
**
** Reference ID         : PWM_DUD_ACT_024, PWM_DUD_ACT_024_CRT001, PWM_DUD_ACT_024_CRT002, PWM_DUD_ACT_024_CRT003,
** Reference ID         : PWM_DUD_ACT_024_CRT004, PWM_DUD_ACT_024_ERR002, PWM_DUD_ACT_024_ERR004,
** Reference ID         : PWM_DUD_ACT_024_ERR005, PWM_DUD_ACT_024_GBL001, PWM_DUD_ACT_024_REG001,
** Reference ID         : PWM_DUD_ACT_024_REG002, PWM_DUD_ACT_024_REG003, PWM_DUD_ACT_024_REG004,
** Reference ID         : PWM_DUD_ACT_024_REG005, PWM_DUD_ACT_024_REG006
***********************************************************************************************************************/
#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_SetPeriodAndDuty(
  Pwm_ChannelType LddChannelId, Pwm_PeriodType LddPeriod, uint16 LusDutyCycle)
{
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpTAUDUnitConfig;
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  /* Pointer pointing to the TAU Unit control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  /* Pointer used for TAU channel control registers */
  P2VAR(volatile Pwm_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDProperties;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  VAR(uint16, AUTOMATIC) LusMasterChannelMask;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  #endif
  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  VAR(boolean, AUTOMATIC) blDemReport;

  /* Initialize DEM report status */
  blDemReport = PWM_FALSE;
  #endif
  /* Initialize a pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  /* Set TAU channel config data pointer */
  LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                        /* PRQA S 0317 # JV-01 */
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Initialize DET error flag */
  LucDetErrFlag = E_OK;
  if ((uint8)PWM_MASTER_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)
  {
    if ((Pwm_PeriodType)PWM_TAUD_MAX_PERIOD_VAL < LddPeriod)
    {
      /* Report to DET module */
      (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_PERIODANDDUTY_SID, PWM_E_PARAM_VALUE);
      LucDetErrFlag = E_NOT_OK;
    } /* else No action required */
  } /* else No action required */
  /* End of if PWM_MASTER_CHANNEL == LpTAUDChannelConfigData->ucTimerMode */

  if (E_OK == LucDetErrFlag)
  #endif /* (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Set the period if the channel is master and set the duty of all the slaves of that master */
    if ((uint8)PWM_MASTER_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)
    {
      /* Fetch the pointer to the current TAUD Unit config */
      LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
      /* Fetch the pointer to the current TAUD Unit Registers */
      LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
      /* Get the pointer to the TAUD channel properties */
      LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;     /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
      /* Initialize a pointer to the control register configuration of TAUD */
      LpTAUDChannelReg = LpTAUDProperties->pCntlRegs;
      /* Get the Channel Mask of the Master channel for RDT register */
      LusMasterChannelMask = LpTAUDProperties->usChannelMask;

      /* Enter Protected area */
      PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

      /* Check whether simultaneous rewrite has been completed */
      if (PWM_TAUD_RESET_16BIT_REG == (uint16)(LpTAUDProperties->usChannelMask & LpTAUDUnitUserReg->usTAUDnRSF))
      {
        if ((Pwm_PeriodType)PWM_TAUD_MIN_PERIOD_VAL != LddPeriod)
        {
          /* Decrement the period value */
          LddPeriod--;                                                                                                  /* PRQA S 1338 # JV-01 */
          /* Load the period value in to the CDR register of master channel */
          LpTAUDChannelReg->usTAUDnCDRm = (uint16)LddPeriod;
        }
        else
        {
          /* Set 0 in to the CDR Register */
          LpTAUDChannelReg->usTAUDnCDRm = PWM_TAUD_MIN_PERIOD_VAL;
        }
      }
      #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
      else
      {
        /* Set Dem error flag */
        blDemReport = PWM_TRUE;
      }
      #endif

      /* Exit Protected area */
      PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

      /* Increment the channel Id */
      LddChannelId++;                                                                                                   /* PRQA S 1338, 3383 # JV-01, JV-01 */
      /* Increment the pointer to the next channel*/
      LpChannelConfig++;

      /* Enter Protected area */
      PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

      do
      {
        /* Get the pointer to the TAU channel properties */
        LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;   /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
        /* Initialize a pointer to the slave's control register configuration of TAU */
        LpTAUDChannelReg = LpTAUDProperties->pCntlRegs;
        /* Check whether the channel is set to its Idle state */
        if (PWM_TRUE == Pwm_GaaChannelIdleStatus[LddChannelId])                                                         /* PRQA S 1881 # JV-01 */
        {
          /* Enable the output of the current channel */
          LpTAUDUnitUserReg->usTAUDnTOE = (LpTAUDUnitUserReg->usTAUDnTOE | LpTAUDProperties->usChannelMask);
          /* Set the Idle state of the channel to PWM_FALSE */
          Pwm_GaaChannelIdleStatus[LddChannelId] = (uint8)PWM_FALSE;                                                    /* PRQA S 4304 # JV-01 */
        } /* else No action required */

        /* Check whether simultaneous rewrite has been completed */
        if (PWM_TAUD_RESET_16BIT_REG == (uint16)(LpTAUDProperties->usChannelMask & LpTAUDUnitUserReg->usTAUDnRSF))
        {
          if ((Pwm_PeriodType)PWM_TAUD_MIN_PERIOD_VAL != LddPeriod)
          {
            /* Load the Absolute duty value in to the CDR Register */
            LpTAUDChannelReg->usTAUDnCDRm = (uint16)Pwm_HW_TAUD_CalculateDuty(LddPeriod, (Pwm_PeriodType)LusDutyCycle);
          }
          else
          {
            /* Set 0 in to the CDR Register */
            LpTAUDChannelReg->usTAUDnCDRm = PWM_TAUD_MIN_PERIOD_VAL;
          }
        }
        else
        {
          LusMasterChannelMask = LusMasterChannelMask & (uint16)(~LpTAUDProperties->usChannelMask);
          #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
          /* Set Dem error flag */
          blDemReport = PWM_TRUE;
          #endif
        }
        /* Increment the channel */
        LddChannelId++;                                                                                                 /* PRQA S 1338, 3383 # JV-01, JV-01 */
        /* Increment the pointer to the next channel*/
        LpChannelConfig++;
        if (PWM_TOTAL_CHANNELS_CONFIG > LddChannelId)
        {
          /* Set TAU channel config data pointer */
          LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                /* PRQA S 0317 # JV-01 */
        } /* else No action required */
      } while ((PWM_TOTAL_CHANNELS_CONFIG > LddChannelId)
           && ((uint8)PWM_MASTER_CHANNEL != LpTAUDChannelConfigData->ucTimerMode));
      /* Set the corresponding channels Trigger bits to specifies the channels
         for which simultaneous rewrite is executed */
      LpTAUDUnitUserReg->usTAUDnRDT = LusMasterChannelMask;

      /* Exit Protected area */
      PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

      #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
      if (PWM_TRUE == blDemReport)
      {
        PWM_DEM_REPORT_ERROR(PWM_E_REWRITE_FAILED, DEM_EVENT_STATUS_FAILED);
      } /* else No action required */
      #endif
    } /* End of if (PWM_MASTER_CHANNEL == LpTAUDChannelConfigData->ucTimerMode) */
    /* Set the Duty cycle of the requested channel if Slave */
    else
    {
      /* Set the Duty cycle for the slave channel */
      Pwm_HW_TAUD_SetDutyCycle(LddChannelId, LusDutyCycle);
    }
  } /* else No action required */
  /* End of if (E_OK == LucDetErrFlag) */
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_SET_PERIOD_AND_DUTY_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_SetOutputToIdle
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This function sets the output of a required channel to its configured Idle state.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpTAUDUnitConfig, Pwm_GpChannelConfig, Pwm_GaaChannelIdleStatus,
**
** Functions invoked     : None
**
** Registers Used        : TAUDnTOE, TAUDnTO.
**
** Reference ID          : PWM_DUD_ACT_022, PWM_DUD_ACT_022_CRT001, PWM_DUD_ACT_022_CRT002, PWM_DUD_ACT_022_CRT003,
** Reference ID          : PWM_DUD_ACT_022_CRT004, PWM_DUD_ACT_022_CRT005, PWM_DUD_ACT_022_CRT006,
** Reference ID          : PWM_DUD_ACT_022_GBL001, PWM_DUD_ACT_022_GBL002, PWM_DUD_ACT_022_GBL003,
** Reference ID          : PWM_DUD_ACT_022_REG001, PWM_DUD_ACT_022_REG002, PWM_DUD_ACT_022_REG003,
** Reference ID          : PWM_DUD_ACT_022_REG004, PWM_DUD_ACT_022_REG005, PWM_DUD_ACT_022_REG006,
** Reference ID          : PWM_DUD_ACT_022_REG007, PWM_DUD_ACT_022_REG008, PWM_DUD_ACT_022_REG009
***********************************************************************************************************************/
#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_SetOutputToIdle(Pwm_ChannelType LddChannelId)
{
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpTAUDUnitConfig;
  /* Pointer pointing to the TAU Unit control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDProperties;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  VAR(uint32, AUTOMATIC) LulCount;

  /* Get the pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  /* Set TAU channel config data pointer */
  LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                        /* PRQA S 0317 # JV-01 */
  /* Fetch the pointer to the current TAU Unit config */
  LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
  /* Fetch the pointer to the current TAU Unit Registers */
  LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
  /* Check whether the channel is in Slave Mode */
  if ((uint8)PWM_SLAVE_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)
  {
    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

    /* Get the pointer to the TAU channel properties */
    LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;       /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
    /* Set the corresponding channel bit to disable TOm operation */
    LpTAUDUnitUserReg->usTAUDnTOE = (LpTAUDUnitUserReg->usTAUDnTOE & (uint16)(~LpTAUDProperties->usChannelMask));
    if ((uint8)PWM_LOW == LpChannelConfig->ucIdleLevel)
    {
      /* Reset the corresponding bit if Idle state is LOW */
      LpTAUDUnitUserReg->usTAUDnTO = (LpTAUDUnitUserReg->usTAUDnTO & (uint16)(~LpTAUDProperties->usChannelMask));
    }
    else
    {
      /* Set the corresponding bit if Idle state is HIGH */
      LpTAUDUnitUserReg->usTAUDnTO = (LpTAUDUnitUserReg->usTAUDnTO | LpTAUDProperties->usChannelMask);
    }
    /* Set the Idle state status of this channel as PWM_TRUE */
    Pwm_GaaChannelIdleStatus[LddChannelId] = (uint8)PWM_TRUE;                                                           /* PRQA S 4304 # JV-01 */

    /* Exit Protected area */
    PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  }
  /* Incase of Master Mode */
  else
  {
    /* Check for the current channel Class Type is in Fixed Period Shifted */
    if (PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
    {

      /* Enter Protected area */
      PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

      for (LulCount = (uint32)PWM_ONE; (uint32)PWM_THREE >= LulCount; LulCount++)
      {
        /* Increment the channel Id */
        LddChannelId++;                                                                                                 /* PRQA S 1338, 3383 # JV-01, JV-01 */
        /* Increment the pointer to the next channel */
        LpChannelConfig++;
        /* Get the pointer to the TAUD channel properties */
        LpTAUDProperties =
          (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;                    /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
        if (((uint32)PWM_ONE == LulCount) || ((uint32)PWM_THREE == LulCount))
        {
          /* Set the corresponding channel bit to disable TOm operation */
          LpTAUDUnitUserReg->usTAUDnTOE = (LpTAUDUnitUserReg->usTAUDnTOE & (uint16)(~LpTAUDProperties->usChannelMask));
          if ((uint8)PWM_LOW == LpChannelConfig->ucIdleLevel)
          {
            /* Reset the corresponding bit if Idle state is LOW */
            LpTAUDUnitUserReg->usTAUDnTO = (LpTAUDUnitUserReg->usTAUDnTO & (uint16)(~LpTAUDProperties->usChannelMask));
          }
          else
          {
            /* Set the corresponding bit if Idle state is HIGH */
            LpTAUDUnitUserReg->usTAUDnTO = (LpTAUDUnitUserReg->usTAUDnTO | LpTAUDProperties->usChannelMask);
          }
          /* Set the Idle state status of this channel as PWM_TRUE */
          Pwm_GaaChannelIdleStatus[LddChannelId] = (uint8)PWM_TRUE;                                                     /* PRQA S 4304 # JV-01 */
        } /* else No action required */
        /* End of if ((PWM_ONE == LulCount) || (PWM_THREE == LulCount)) */
      } /* End of for loop */

      /* Exit Protected area */
      PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

    } /* End of if (PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType) */
    /* Is the current channel Class Type is in Fixed / Variable Period */
    else
    {
      /* Increment the pointer to the next channel */
      LpChannelConfig++;
      LddChannelId++;                                                                                                   /* PRQA S 1338, 3383 # JV-01, JV-01 */

      /* Enter Protected area */
      PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

      do
      {
        /* Get the pointer to the TAUD channel properties */
        LpTAUDProperties =
          (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;                    /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
        /* Set corresponding channel bit to disable TOm operation */
        LpTAUDUnitUserReg->usTAUDnTOE = (LpTAUDUnitUserReg->usTAUDnTOE & (uint16)(~LpTAUDProperties->usChannelMask));
        if ((uint8)PWM_LOW == LpChannelConfig->ucIdleLevel)
        {
          /* Reset the corresponding bit if Idle state is LOW */
          LpTAUDUnitUserReg->usTAUDnTO = (LpTAUDUnitUserReg->usTAUDnTO & (uint16)(~LpTAUDProperties->usChannelMask));
        }
        else
        {
          /* Set the corresponding bit if Idle state is HIGH */
          LpTAUDUnitUserReg->usTAUDnTO = (LpTAUDUnitUserReg->usTAUDnTO | LpTAUDProperties->usChannelMask);
        }

        /* Set the Idle state status of this channel as PWM_TRUE */
        Pwm_GaaChannelIdleStatus[LddChannelId] = (uint8)PWM_TRUE;                                                       /* PRQA S 4304 # JV-01 */
        /* Increment the channel Id */
        LddChannelId++;                                                                                                 /* PRQA S 1338, 3383 # JV-01, JV-01 */
        /* Increment the pointer to the next channel */
        LpChannelConfig++;
        if (PWM_TOTAL_CHANNELS_CONFIG > LddChannelId)
        {
          /* Set TAU channel config data pointer */
          LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                /* PRQA S 0317 # JV-01 */
        } /* else No action required */
      } while ((PWM_TOTAL_CHANNELS_CONFIG > LddChannelId)
            && ((uint8)PWM_MASTER_CHANNEL != LpTAUDChannelConfigData->ucTimerMode));

      /* Exit Protected area */
      PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    } /* End of if (PWM_FIXED_PERIOD_SHIFTED != LpChannelConfig->enClassType) */
  } /* End of if channel is in Master Mode */
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_GetOutputState
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This function gets the output state of a PWM channel. (only Active and Slave)
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Pwm_OutputStateType
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpTAUDUnitConfig, Pwm_GpChannelConfig
**
** Functions invoked     : None
**
** Registers Used        : TAUDnTO.
**
** Reference ID          : PWM_DUD_ACT_033, PWM_DUD_ACT_033_CRT001,  PWM_DUD_ACT_033_CRT002, PWM_DUD_ACT_033_GBL001,
** Reference ID          : PWM_DUD_ACT_033_GBL002
***********************************************************************************************************************/
#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Pwm_OutputStateType, PWM_PRIVATE_CODE) Pwm_HW_TAUD_GetOutputState(Pwm_ChannelType LddChannelId)
{
  VAR(Pwm_OutputStateType, AUTOMATIC) LenRetOutputState;
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpTAUDUnitConfig;
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  /* Pointer pointing to the TAU Unit control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;                                          /* PRQA S 3678 # JV-01 */
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDProperties;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */

  /* Initialize a pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  /* Set TAU channel config data pointer */
  LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                        /* PRQA S 0317 # JV-01 */
  /* Initialize the return value in case of DET error */
  LenRetOutputState = PWM_LOW;
  /* Check whether the channel is in Slave Mode */
  if ((uint8)PWM_SLAVE_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)
  {
    /* Fetch the pointer to the current TAU Unit config */
    LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
    /* Fetch the pointer to the current TAU Unit Registers */
    LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
    /* Get the pointer to the TAU channel properties */
    LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;       /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */

    /* Condition to check the current output state of the slave channel */
    if (((LpTAUDUnitUserReg->usTAUDnTO) & (LpTAUDProperties->usChannelMask)) == LpTAUDProperties->usChannelMask)
    {
      LenRetOutputState = PWM_HIGH;
    } /* else No action required */
  } /* else No action required */
  /* End of ucTimerMode is PWM_SLAVE_CHANNEL */

  return LenRetOutputState;
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_GET_OUTPUT_STATE_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_CalculateDuty
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This function Calculates Absolute duty for the PWM channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddAbsolutePeriod, LddRelativeDuty
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Pwm_PeriodType
**
** Pre-conditions        : NA
**
** Global Variables used : None
**
** Functions invoked     : None
**
** Registers Used        : None
**
** Reference ID          : PWM_DUD_ACT_029
***********************************************************************************************************************/
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Pwm_PeriodType, PWM_PRIVATE_CODE) Pwm_HW_TAUD_CalculateDuty(Pwm_PeriodType LddAbsolutePeriod,                      /* PRQA S 1505 # JV-01 */
                                                                 Pwm_PeriodType LddRelativeDuty)
{
  VAR(Pwm_PeriodType, AUTOMATIC) LddAbsoluteDuty;

  if ((Pwm_PeriodType)PWM_MAX_DUTY_CYCLE_VALUE == LddRelativeDuty)
  {
    /* If Duty is 100%, Update (CDRm (master channel) setting value + 1) value in the CDRm register */
    LddAbsoluteDuty = (Pwm_PeriodType)LddAbsolutePeriod + (Pwm_PeriodType)PWM_ONE;                                      /* PRQA S 3383 # JV-01 */
  }
  else if ((Pwm_PeriodType)PWM_MIN_DUTY_CYCLE_VALUE == LddRelativeDuty)
  {
    /* If Duty is 0%, Update 0x0000 value in the CDRm register */
    LddAbsoluteDuty = (Pwm_PeriodType)PWM_MIN_DUTY_CYCLE_VALUE;
  }
  else
  {
    /* Increment the period values since the CDR(master) was loaded with 1 less */
    LddAbsolutePeriod++;                                                                                                /* PRQA S 1338, 3383 # JV-01, JV-01 */
    /* If Duty is between 0x0000 and 0x8000, AbsoluteDutyCycle = (AbsolutePeriodTime * RelativeDutyCycle) >> 15 */
    LddAbsoluteDuty = (Pwm_PeriodType)((LddAbsolutePeriod * LddRelativeDuty) >> (Pwm_PeriodType)PWM_DUTY_CALC_DIV);     /* PRQA S 3383 # JV-01 */
  }

  return LddAbsoluteDuty;
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_Callback
**
** Service ID            : NA
**
** Description           : This routine is used to invoke the callback notification.
**                         This routine also supports PwmSetChannelOutput functionality for TAU channels.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpChannelConfig, Pwm_GaaNotifStatus, Pwm_GaaChannelConstantStatus, Pwm_GpTAUDUnitConfig
**
** Functions invoked     : PWM_DEM_REPORT_ERROR, Pwm_HW_TAUD_SetOutputToIdle
**
** Registers Used        : EICm, TAUDnTOE, TAUDnTO.
**
** Reference ID          : PWM_DUD_ACT_028, PWM_DUD_ACT_028_CRT001, PWM_DUD_ACT_028_CRT002, PWM_DUD_ACT_028_CRT003,
** Reference ID          : PWM_DUD_ACT_028_CRT004, PWM_DUD_ACT_028_CRT005, PWM_DUD_ACT_028_CRT006,
** Reference ID          : PWM_DUD_ACT_028_CRT007, PWM_DUD_ACT_028_ERR001, PWM_DUD_ACT_028_GBL001,
** Reference ID          : PWM_DUD_ACT_028_GBL002, PWM_DUD_ACT_028_REG001, PWM_DUD_ACT_028_REG002
***********************************************************************************************************************/
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_CODE_FAST) Pwm_HW_TAUD_Callback(Pwm_ChannelType LddChannelId)                                            /* PRQA S 3006 # JV-01 */
{
  #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON || PWM_NOTIFICATION_SUPPORTED == STD_ON)
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONST) LpChannelConfig;
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONST) LpTAUDUnitConfig;
  /* Pointer pointing to the TAU Unit control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;                                          /* PRQA S 3678 # JV-01 */
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_VAR_FAST_NO_INIT) LpTAUDProperties;                                     /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #if ((PWM_SET_CHANNEL_OUTPUT_API == STD_ON) && (PWM_NOTIFICATION_SUPPORTED == STD_ON))
  VAR(Pwm_ChannelType, AUTOMATIC) LddTempChannelId;
  #endif

  #if (PWM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Initialize a pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  /* Get the pointer to the TAU channel properties */
  LpTAUDProperties =
    (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;                          /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
  if ((uint16)PWM_ZERO != (*LpTAUDProperties->pEICReg & (uint16)PWM_EIC_EIMK_MASK))
  {
    PWM_DEM_REPORT_ERROR(PWM_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif /* (PWM_INTERRUPT_CONSISTENCY_CHECK == STD_ON) */
  #endif /* (PWM_SET_CHANNEL_OUTPUT_API == STD_ON || PWM_NOTIFICATION_SUPPORTED == STD_ON) */
  {
    #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
    /* Initialize a pointer to the channel configuration */
    LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
    /* Set TAU channel config data pointer */
    LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                      /* PRQA S 0317 # JV-01 */
    if ((uint8)PWM_MASTER_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)
    {
      /* Enter Protected area */
      PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

      if (PWM_TRUE == Pwm_GaaChannelConstantStatus[LddChannelId])                                                       /* PRQA S 1881 # JV-01 */
      {
        #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /* Store the current value of LddChannelId */
        LddTempChannelId = LddChannelId;
        #endif
        /* Set the Constant state of the master channel to PWM_FALSE */
        Pwm_GaaChannelConstantStatus[LddChannelId] = (uint8)PWM_FALSE;                                                  /* PRQA S 4304 # JV-01 */

        /* Exit Protected area */
        PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

        /* Initialize a pointer to the Master's control register configuration of TAUD */
        /* Fetch the pointer to the current TAU Unit config */
        LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
        /* Get the pointer to the TAU channel properties */
        LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;   /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
        /* Fetch the pointer to the current TAU Unit Registers */
        LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;

        #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /* Disable TAUD master channel interrupt if Pwm_GaaNotifStatus is false */
        if (PWM_FALSE == Pwm_GaaNotifStatus[LddChannelId])                                                              /* PRQA S 1881 # JV-01 */
        #endif
        {
          /* Enter Protected area */
          PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

          /* Disabling the Interrupt processing of the current channel with dummy read and execute syncp instruction */
          RH850_SV_SET_ICR_SYNCP(8, LpTAUDProperties->pEICReg, PWM_DISABLE_INTR_MASK);                                  /* PRQA S 0751, 1006 # JV-01, JV-01 */

          /* Exit Protected area */
          PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
        } /* else No action required */

        /* Increment the pointer to the slave channel */
        LpChannelConfig++;
        /* Increment the channel Id */
        LddChannelId++;                                                                                                 /* PRQA S 1338, 3383 # JV-01, JV-01 */

        /* Enter Protected area */
        PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

        do
        {
          if (PWM_TRUE == Pwm_GaaChannelConstantStatus[LddChannelId])                                                   /* PRQA S 1881 # JV-01 */
          {
            /* Check whether the channel is Constant state and not in Idle state */
            if (PWM_FALSE == Pwm_GaaChannelIdleStatus[LddChannelId])                                                    /* PRQA S 1881 # JV-01 */
            {
              /* Get the pointer to the TAU channel properties */
              LpTAUDProperties =
                (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;              /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
              /* Enable the output of the current channel */
              LpTAUDUnitUserReg->usTAUDnTOE = (LpTAUDUnitUserReg->usTAUDnTOE | LpTAUDProperties->usChannelMask);
            } /* Check whether the channel is Constant state and in Idle state */
            else
            {
              #if (STD_ON == PWM_SET_OUTPUT_TO_IDLE_API)
              /* Set the PWM Output back to Idle state*/
              Pwm_HW_TAUD_SetOutputToIdle(LddChannelId);
              #endif
            }
            /* Set the Constant state of the channel to PWM_FALSE */
            Pwm_GaaChannelConstantStatus[LddChannelId] = (uint8)PWM_FALSE;                                              /* PRQA S 4304 # JV-01 */
          }/* else No action required */

          /* Increment the channel Id */
          LddChannelId++;                                                                                               /* PRQA S 1338, 3383 # JV-01, JV-01 */
          /* Increment the pointer to the next channel */
          LpChannelConfig++;

          if (PWM_TOTAL_CHANNELS_CONFIG > LddChannelId)
          {
            /* Set TAU channel config data pointer */
            LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                              /* PRQA S 0317 # JV-01 */
          } /* else No action required */
        } while ((PWM_TOTAL_CHANNELS_CONFIG > LddChannelId)
             && ((uint8)PWM_MASTER_CHANNEL != LpTAUDChannelConfigData->ucTimerMode));

        /* Exit Protected area */
        PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

        #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /* Restore the value of LddChannelId */
        LddChannelId = LddTempChannelId;                                                                                /* PRQA S 1338 # JV-01 */
        #endif
      }
      else
      {
        /* Exit Protected area */
        PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);
      } /* End of if (PWM_TRUE == Pwm_GaaChannelConstantStatus[LddChannelId]) */
    } /* else No action required */
    /* End of ucTimerMode is PWM_MASTER_CHANNEL */
    #endif /* End of (PWM_SET_CHANNEL_OUTPUT_API == STD_ON) */

    #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
    /* check if Notification status is enabled for this channel */
    if (PWM_TRUE == Pwm_GaaNotifStatus[LddChannelId])                                                                   /* PRQA S 1881 # JV-01 */
    {
      /* Fetch the pointer to the current channel configuration */
      LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
      /* Set TAU channel config data pointer */
      LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                    /* PRQA S 0317 # JV-01 */
      /* Check whether this channel is slave channel 3 of PWM_FIXED_PERIOD_SHIFTED channels set */
      if ((PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
        && (PWM_THREE == LpTAUDChannelConfigData->ucMasterOffset))
      {
        /* Fetch the pointer to the current TAUD Unit config */
        LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
        /* Get the pointer to the TAUD channel properties */
        LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;   /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
        /* Fetch the pointer to the current TAUD Unit Registers */
        LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
        if ((LpTAUDProperties->usChannelMask != (LpTAUDUnitUserReg->usTAUDnTO & LpTAUDProperties->usChannelMask))
                                               && ((uint8)PWM_POLARITY_HIGH == LpChannelConfig->ucPolarity))
        {
          /* Invoke the Notification function */
          LpChannelConfig->pPwmEdgeNotifPtr();
        } /* else No action required */
        if ((LpTAUDProperties->usChannelMask == (LpTAUDUnitUserReg->usTAUDnTO & LpTAUDProperties->usChannelMask))
                                               && ((uint8)PWM_POLARITY_LOW == LpChannelConfig->ucPolarity))
        {
          /* Invoke the Notification function */
          LpChannelConfig->pPwmEdgeNotifPtr();
        } /* else No action required */
      } /* End of if ((PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
                   && (PWM_THREE == LpTAUDChannelConfigData->ucMasterOffset)) */
      else
      {
        /* Invoke the Notification function */
        LpChannelConfig->pPwmEdgeNotifPtr();
      }
    } /* else No action required */
    /* End of if (PWM_TRUE == Pwm_GaaNotifStatus[LddChannelId]) */
    #endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) */
  }
}

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_IntNotification
**
** Service ID            : NA
**
** Description           : This routine is used to disable pending interrupts and enable Interrupt processing.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpChannelConfig, Pwm_GaaNotifStatus
**
** Functions invoked     : None
**
** Registers Used        : EICm
**
** Reference ID          : PWM_DUD_ACT_026, PWM_DUD_ACT_026_CRT001, PWM_DUD_ACT_026_CRT004,
** Reference ID          : PWM_DUD_ACT_026_REG001, PWM_DUD_ACT_026_REG002, PWM_DUD_ACT_026_GBL001
***********************************************************************************************************************/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

static FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_IntNotification(Pwm_ChannelType LddChannelId)                           /* PRQA S 3006 # JV-01 */
{
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_VAR_FAST_NO_INIT) LpTAUDProperties;                                     /* PRQA S 3432, 3678 # JV-01, JV-01 */

  /* Initialize a pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  /* Get the pointer to the TAUD channel properties */
  LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;         /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */

  /* Enter Protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

  #if (PWM_CLEAR_PENDING_INTERRUPT == STD_ON)
  /* Check if the Interrupt register is present for particular channel */
  if (NULL_PTR != LpTAUDProperties->pEICReg)
  {
    /* Clear pending interrupts with dummy read and execute syncp instruction */
    RH850_SV_CLEAR_ICR_SYNCP(16, LpTAUDProperties->pEICReg, PWM_CLEAR_PENDING_INTR_MASK);                               /* PRQA S 0499, 1006 # JV-01, JV-01 */
  } /* else No action required */
  #endif /* (PWM_CLEAR_PENDING_INTERRUPT == STD_ON) */

  /* Check the Notification is configured for the current channel */
  if (NULL_PTR != LpChannelConfig->pPwmEdgeNotifPtr)
  {
    /* Set Notification enable status as PWM_TRUE for this channel */
    Pwm_GaaNotifStatus[LddChannelId] = (uint8)PWM_TRUE;                                                                 /* PRQA S 4304 # JV-01 */
    /* Enable the Interrupt processing of the current channel with dummy read and execute syncp instruction */
    RH850_SV_CLEAR_ICR_SYNCP(8, LpTAUDProperties->pEICReg, PWM_ENABLE_INTR_MASK);                                       /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */

  /* Exit Protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_EnableNotification
**
** Service ID            : NA
**
** Description           : This routine is used to disable pending interrupts and enable Interrupt processing.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId, LenNotification
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpChannelConfig, Pwm_GaaNotifStatus
**
** Functions invoked     : Det_ReportError, Pwm_HW_TAUD_IntNotification
**
** Registers Used        : EICm
**
** Reference ID          : PWM_DUD_ACT_025, PWM_DUD_ACT_025_ERR001, PWM_DUD_ACT_025_ERR002, PWM_DUD_ACT_025_ERR003
***********************************************************************************************************************/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_EnableNotification(Pwm_ChannelType LddChannelId,
                                                            Pwm_EdgeNotificationType LenNotification)
{
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Pointer to channel configuration of master channel*/
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpMasterChannelConfig;
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  #endif

  /* Initialize a pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  /* Set TAU channel config data pointer */
  LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                        /* PRQA S 0317 # JV-01 */
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Initialize DET error flag */
  LucDetErrFlag = E_OK;
  if ((uint8)PWM_SLAVE_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)
  {
    LpMasterChannelConfig = &Pwm_GpChannelConfig[LddChannelId - LpTAUDChannelConfigData->ucMasterOffset];
    /* Check notification is PWM_BOTH_EDGES */
    if (PWM_BOTH_EDGES == LenNotification)
    {
      if ((NULL_PTR == LpMasterChannelConfig->pPwmEdgeNotifPtr) || (NULL_PTR == LpChannelConfig->pPwmEdgeNotifPtr))
      {
        /* Report to DET module */
        (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ENABLENOTIFICATION_SID, PWM_E_NOTIFY_NOTCONFIG);
        LucDetErrFlag = E_NOT_OK;
      } /* else No action required */
    }
    /* For notification is PWM_RISING_EDGE */
    else if (PWM_RISING_EDGE == LenNotification)
    {
      if ((((uint8)PWM_POLARITY_HIGH == LpChannelConfig->ucPolarity) &&
         (NULL_PTR == LpMasterChannelConfig->pPwmEdgeNotifPtr)) ||
        (((uint8)PWM_POLARITY_LOW == LpChannelConfig->ucPolarity) &&
         (NULL_PTR == LpChannelConfig->pPwmEdgeNotifPtr)))
      {
        /* Report to DET module */
        (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ENABLENOTIFICATION_SID, PWM_E_NOTIFY_NOTCONFIG);
        LucDetErrFlag = E_NOT_OK;
      } /* else No action required */
    }
    /* For notification is PWM_FALLING_EDGE */
    else
    {
      if ((((uint8)PWM_POLARITY_HIGH == LpChannelConfig->ucPolarity) &&
           (NULL_PTR == LpChannelConfig->pPwmEdgeNotifPtr)) ||
          (((uint8)PWM_POLARITY_LOW == LpChannelConfig->ucPolarity) &&
           (NULL_PTR == LpMasterChannelConfig->pPwmEdgeNotifPtr)))
      {
        /* Report to DET module */
        (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_ENABLENOTIFICATION_SID, PWM_E_NOTIFY_NOTCONFIG);
        LucDetErrFlag = E_NOT_OK;
      } /* else No action required */
    }
  } /* else No action required */
  /* End of if (PWM_SLAVE_CHANNEL == LpChannelConfig->ucTimerMode) */

  if (E_OK == LucDetErrFlag)
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if this channel is in the Slave mode and isn't Delay channel */
    if (((uint8)PWM_MASTER_CHANNEL != LpTAUDChannelConfigData->ucTimerMode) &&
      ((PWM_FIXED_PERIOD_SHIFTED != LpChannelConfig->enClassType) ||
        ((PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType) &&
          (PWM_TWO != LpTAUDChannelConfigData->ucMasterOffset))))
    {
      if (PWM_BOTH_EDGES == LenNotification)
      {
        /* Clear the Pending Interrupts and Enable Interrupt Processing for Slave */
        Pwm_HW_TAUD_IntNotification(LddChannelId);

        if ((PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
         && (PWM_THREE == LpTAUDChannelConfigData->ucMasterOffset))
        {
          /* Get Delay's channel ID */
          LddChannelId = (LddChannelId - PWM_ONE);                                                                      /* PRQA S 1338 # JV-01 */
        }
        else
        {
          /* Get Master's channel ID */
          LddChannelId = (LddChannelId - (LpTAUDChannelConfigData->ucMasterOffset));                                    /* PRQA S 1338 # JV-01 */
        }
        /* Get Master's channel Config */
        LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];                                                           /* PRQA S 2983 # JV-01 */
        /* Clear the Pending Interrupts and Enable Interrupt Processing for Master */
        Pwm_HW_TAUD_IntNotification(LddChannelId);
      }
      else if (((PWM_RISING_EDGE == LenNotification) && ((uint8)PWM_POLARITY_HIGH == LpChannelConfig->ucPolarity)) ||
               ((PWM_FALLING_EDGE == LenNotification) && ((uint8)PWM_POLARITY_LOW == LpChannelConfig->ucPolarity)))
      {
        /* Check whether this channel is channel slave 3 of Pwm period shifted set */
        if ((PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
         && (PWM_THREE == LpTAUDChannelConfigData->ucMasterOffset))
        {
          /* Get the channel number of delay channel */
          LddChannelId = LddChannelId - PWM_ONE;                                                                        /* PRQA S 1338 # JV-01 */
        }
        else
        {
          /* Get Master's channel ID */
          LddChannelId = (LddChannelId - (LpTAUDChannelConfigData->ucMasterOffset));                                    /* PRQA S 1338 # JV-01 */
        }

        /* Get Delay's channel Config */
        LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];                                                           /* PRQA S 2983 # JV-01 */
        /* Clear the Pending Interrupts and Enable Interrupt Processing for Delay channel */
        Pwm_HW_TAUD_IntNotification(LddChannelId);
      }
      /* For FALLING EDGE Notification with polarity PWM_HIGH or RISING EDGE Notification with polarity PWM_LOW */
      else
      {
        /* Clear the Pending Interrupts and Enable Interrupt Processing for Slave */
        Pwm_HW_TAUD_IntNotification(LddChannelId);
      }
    } /* else No action required */
    /*End of if(PWM_MASTER_CHANNEL != LpTAUDChannelConfigData->ucTimerMode)*/
  } /* else No action required */
  /* End of LucDetErrFlag is E_OK */
}

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_DisableNotification
**
** Service ID            : NA
**
** Description           : This routine is used to disable Interrupt processing.
**                         This routine also supports PwmSetChannelOutput functionality for TAU channels.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpChannelConfig, Pwm_GaaChannelConstantStatus, Pwm_GpTAUDUnitConfig
**
** Functions invoked     : None
**
** Registers Used        : EICm, TAUDnTOE.
**
** Reference ID          : PWM_DUD_ACT_027, PWM_DUD_ACT_027_CRT001, PWM_DUD_ACT_027_CRT002, PWM_DUD_ACT_027_CRT005,
** Reference ID          : PWM_DUD_ACT_027_CRT006, PWM_DUD_ACT_027_GBL001, PWM_DUD_ACT_027_GBL002,
** Reference ID          : PWM_DUD_ACT_027_REG001, PWM_DUD_ACT_027_REG002, PWM_DUD_ACT_026_GBL001
***********************************************************************************************************************/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_DisableNotification(Pwm_ChannelType LddChannelId)                              /* PRQA S 3006 # JV-01 */
{
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_VAR_FAST_NO_INIT) LpTAUDProperties;                                     /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONST) LpTAUDUnitConfig;
  /* Pointer pointing to the TAU Unit control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  #endif

  /* Initialize a pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  /* Get the pointer to the TAUD channel properties */
  LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;         /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
  #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
  /* Set TAU channel config data pointer */
  LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                        /* PRQA S 0317 # JV-01 */
  #endif
  /* Check the Notification is configured for the current channel */
  if (NULL_PTR != LpChannelConfig->pPwmEdgeNotifPtr)
  {
    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

    /* Disabling the Interrupt processing of the current channel with dummy read and execute syncp instruction */
    RH850_SV_SET_ICR_SYNCP(8, LpTAUDProperties->pEICReg, PWM_DISABLE_INTR_MASK);                                        /* PRQA S 0751, 1006 # JV-01, JV-01 */

    /* Exit Protected area */
    PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  } /* else No action required */

  #if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
  if ((uint8)PWM_MASTER_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)
  {
    if (PWM_TRUE == Pwm_GaaChannelConstantStatus[LddChannelId])                                                         /* PRQA S 1881 # JV-01 */
    {
      /* Enter Protected area */
      PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

      /* Set the constant state of the Master channel to PWM_FALSE */
      Pwm_GaaChannelConstantStatus[LddChannelId] = (uint8)PWM_FALSE;                                                    /* PRQA S 4304 # JV-01 */
      /* Initialize a pointer to the Master's control register configuration of TAU */
      /* Fetch the pointer to the current TAU Unit Configuration */
      LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
      /* Fetch the pointer to the current TAU Unit Registers */
      LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
      /* Increment the pointer to the Slave channel */
      LpChannelConfig++;
      /* Increment the channel Id to the Slave channel */
      LddChannelId++;                                                                                                   /* PRQA S 1338, 3383 # JV-01, JV-01 */

      do
      {
        /* Check whether the Slave channel is set to constant state */
        if (PWM_TRUE == Pwm_GaaChannelConstantStatus[LddChannelId])                                                     /* PRQA S 1881 # JV-01 */
        {
          /* Get the pointer to the TAU channel properties */
          LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp; /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
          /* Enable the output of the current channel */
          LpTAUDUnitUserReg->usTAUDnTOE = (LpTAUDUnitUserReg->usTAUDnTOE | LpTAUDProperties->usChannelMask);
          /* Set the constant state of the Slave channel to PWM_FALSE */
          Pwm_GaaChannelConstantStatus[LddChannelId] = (uint8)PWM_FALSE;                                                /* PRQA S 4304 # JV-01 */
        } /* else No action required */

        /* Increment the channel Id */
        LddChannelId++;                                                                                                 /* PRQA S 1338, 3383 # JV-01, JV-01 */
        /* Increment the pointer to the next channel */
        LpChannelConfig++;

        if (PWM_TOTAL_CHANNELS_CONFIG > LddChannelId)
        {
          /* Set TAU channel config data pointer */
          LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                /* PRQA S 0317 # JV-01 */
        } /* else No action required */
      } while ((PWM_TOTAL_CHANNELS_CONFIG > LddChannelId)
           && ((uint8)PWM_MASTER_CHANNEL != LpTAUDChannelConfigData->ucTimerMode));

      /* Exit Protected area */
      PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    } /* else No action required */
    /* End of Pwm_GaaChannelConstantStatus is PWM_TRUE */
  } /* else No action required */
  #endif /* End of (PWM_SET_CHANNEL_OUTPUT_API == STD_ON) */
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_TAUD_SelectChannelClk
**
** Service ID           : NA
**
** Description          : This function updates the clock source select value in hardware register.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : LddChannelId
                          LenClockSource
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Pre-conditions       : NA
**
** Global Variable used : Pwm_GpChannelConfig, Pwm_GpTAUDUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : TAUDnTE, TAUDnTT, TAUDnTS, TAUDnCMORm.
**
** Reference ID         : PWM_DUD_ACT_030, PWM_DUD_ACT_030_CRT001, PWM_DUD_ACT_030_CRT002, PWM_DUD_ACT_030_REG001,
** Reference ID         : PWM_DUD_ACT_030_REG002, PWM_DUD_ACT_030_REG003, PWM_DUD_ACT_030_REG004
***********************************************************************************************************************/
#if (PWM_SELECT_CHANNEL_CLK_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_SelectChannelClk(Pwm_ChannelType LddChannelId,
                                                          Pwm_ClockSourceType LenClockSource)
{
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpTAUDUnitConfig;
  /* Pointer pointing to the TAU Unit user control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDProperties;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  VAR(uint16, AUTOMATIC) LusCMORVal;
  VAR(uint16, AUTOMATIC) LusClockSource;
  VAR(uint16, AUTOMATIC) LusChannelMask;
  VAR(uint8, AUTOMATIC) LucState;

  /* Get the pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  /* Set TAU channel config data pointer */
  LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                        /* PRQA S 0317 # JV-01 */
  if ((uint8)PWM_MASTER_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)
  {
    LucState = PWM_NOTSTARTED_CH;
    /* Update the TAU config pointer to point to the current TAU */
    LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
    /* Get the pointer to the TAU unit registers */
    LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
    /* Get the pointer to the TAU channel properties */
    LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;       /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
    /* Save the existing CMOR register value */
    LusCMORVal = ((*LpTAUDProperties->pCMORReg) & PWM_TAUD_CMOR_MASK);
    LusClockSource = (uint16)LenClockSource;
    /* Set clock source */
    LusClockSource = (uint16)(LusClockSource << PWM_CKS_BITS_POSITION);
    /* Modify only 14 and 15 bit of variable */
    LusCMORVal = LusCMORVal | LusClockSource;

    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);

    /* If channel is already working */
    LusChannelMask = LpTAUDProperties->usChannelMask;
    if ((uint16)((LpTAUDUnitUserReg->usTAUDnTE) & LusChannelMask) != (uint16)PWM_ZERO)
    {
      /* Stop this master channel and respective slaves channel */
      LpTAUDUnitUserReg->usTAUDnTT = LusChannelMask;
      LucState = PWM_STOPPED_CH;
    } /* else No action required */

    /* Update the CMORm register of Master with new clock source */
    *LpTAUDProperties->pCMORReg = LusCMORVal;
    /* Increment the channel Id */
    LddChannelId++;                                                                                                     /* PRQA S 1338, 3383 # JV-01, JV-01 */
    /* Increment the pointer to the slave channel */
    LpChannelConfig++;

    do
    {
      /* Get the pointer to the TAU channel properties */
      LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;     /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
      /* Save the existing CMOR register value */
      LusCMORVal = ((*LpTAUDProperties->pCMORReg) & PWM_TAUD_CMOR_MASK);
      /* Set clock source */
      LusClockSource = (uint16)LenClockSource;
      LusClockSource = (uint16)(LusClockSource << PWM_CKS_BITS_POSITION);
      /* Modify only 14 and 15 bit of variable */
      LusCMORVal = LusCMORVal | LusClockSource;
      /* Update the CMORm register of Slave with new clock source */
      *LpTAUDProperties->pCMORReg = LusCMORVal;
      /* Increment the channel Id */
      LddChannelId++;                                                                                                   /* PRQA S 1338, 3383 # JV-01, JV-01 */
      /* Increment the pointer to the next channel */
      LpChannelConfig++;

      if (PWM_TOTAL_CHANNELS_CONFIG > LddChannelId)
      {
        /* Set TAU channel config data pointer */
        LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                  /* PRQA S 0317 # JV-01 */
      } /* else No action required */
    } while ((PWM_TOTAL_CHANNELS_CONFIG > LddChannelId)
         && ((uint8)PWM_MASTER_CHANNEL != LpTAUDChannelConfigData->ucTimerMode));

    if (PWM_STOPPED_CH == LucState)
    {
      /* Start this master channel and respective slaves channel */
      LpTAUDUnitUserReg->usTAUDnTS = LusChannelMask;
    } /* else No action required */

    /* Exit Protected area */
    PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);
  } /* else No action required */
  /* End of if (PWM_MASTER_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)*/
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_SELECT_CHANNEL_CLK_API == STD_ON) */

#if (PWM_SET_CHANNEL_OUTPUT_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_SetChannelOutput
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This function sets the output of a channel to constant signal for current period.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannelId
**                         LenState
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpTAUDUnitConfig, Pwm_GaaNotifStatus, Pwm_GpChannelConfig, Pwm_GaaChannelConstantStatus.
**
** Functions invoked     : Det_ReportError
**
** Registers Used        : TAUDnTOE, TAUDnTO, EICm.
**
** Reference ID          : PWM_DUD_ACT_034, PWM_DUD_ACT_034_CRT001, PWM_DUD_ACT_034_CRT002, PWM_DUD_ACT_034_CRT003,
** Reference ID          : PWM_DUD_ACT_034_CRT004, PWM_DUD_ACT_034_GBL001, PWM_DUD_ACT_034_GBL002,
** Reference ID          : PWM_DUD_ACT_034_REG001, PWM_DUD_ACT_034_REG002, PWM_DUD_ACT_034_REG003,
** Reference ID          : PWM_DUD_ACT_034_REG004, PWM_DUD_ACT_034_REG005, PWM_DUD_ACT_034_ERR001
***********************************************************************************************************************/

#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_SetChannelOutput(Pwm_ChannelType LddChannelId, Pwm_OutputStateType LenState)   /* PRQA S 3006 # JV-01 */
{
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpTAUDUnitConfig;
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  /* Pointer pointing to the TAU Unit control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDProperties;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  VAR(uint8, AUTOMATIC) LucVar;
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  VAR(uint8, AUTOMATIC) LucDetErrFlag;
  #endif

  /* Get the pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  /* Set TAU channel config data pointer */
  LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                        /* PRQA S 0317 # JV-01 */
  #if (PWM_DEV_ERROR_DETECT == STD_ON)
  /* Declare the variable to store the DET return value */
  LucDetErrFlag = E_OK;

  if ((PWM_FIXED_PERIOD_SHIFTED == LpChannelConfig->enClassType)
    && (PWM_TWO == LpTAUDChannelConfigData->ucMasterOffset))
  {
    /* Report to DET module */
    (void)Det_ReportError(PWM_MODULE_ID, PWM_INSTANCE_ID, PWM_SET_CHANNEL_OUTPUT_SID, PWM_E_PARAM_CHANNEL);
    LucDetErrFlag = E_NOT_OK;
  } /* else No action required */

  if (E_OK == LucDetErrFlag)
  #endif /* End of (PWM_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Fetch the pointer to the current TAUD Unit config */
    LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
    /* Fetch the pointer to the current TAUD Unit Registers */
    LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
    /* Check whether the channel is in Slave Mode */
    if ((uint8)PWM_SLAVE_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)
    {
      /* Get the offset of the Master from the slave channel */
      LucVar = LpTAUDChannelConfigData->ucMasterOffset;

      /* Enter Protected area */
      PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

      /* Set the Constant state status of this channel as PWM_TRUE */
      Pwm_GaaChannelConstantStatus[LddChannelId] = (uint8)PWM_TRUE;                                                     /* PRQA S 4304 # JV-01 */
      /* Set the Constant state status of master channel as PWM_TRUE */
      Pwm_GaaChannelConstantStatus[LddChannelId - LucVar] = (uint8)PWM_TRUE;                                            /* PRQA S 4304 # JV-01 */
      /* Get the pointer to TAUD channel properties */
      LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))(LpChannelConfig->pChannelProp);   /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
      /* Set the corresponding channel bit to disable TOm operation */
      LpTAUDUnitUserReg->usTAUDnTOE = (LpTAUDUnitUserReg->usTAUDnTOE & (uint16)(~LpTAUDProperties->usChannelMask));

      if (PWM_LOW == LenState)
      {
        /* Reset the corresponding bit if Constant state is LOW */
        LpTAUDUnitUserReg->usTAUDnTO = (LpTAUDUnitUserReg->usTAUDnTO & (uint16)(~LpTAUDProperties->usChannelMask));
      }
      else
      {
        /* Set the corresponding bit if Idle state is HIGH */
        LpTAUDUnitUserReg->usTAUDnTO = (LpTAUDUnitUserReg->usTAUDnTO | LpTAUDProperties->usChannelMask);
      }

      /* Exit Protected area */
      PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

      /* Enable TAUD master channel interrupt only if interrupt disabled */
      #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
      if (PWM_FALSE == Pwm_GaaNotifStatus[LddChannelId - LucVar])                                                       /* PRQA S 1881 # JV-01 */
      #endif
      {
        /* Get the pointer to the master channel configuration */
        LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId - LucVar];
        /* Get the pointer to TAUD channel properties */
        LpTAUDProperties =
         (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))(LpChannelConfig->pChannelProp);                   /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */

        /* Enter Protected area */
        PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

        /* Check if the Interrupt register is present for particular channel */
        if (NULL_PTR != LpTAUDProperties->pEICReg)
        {
          #if (PWM_CLEAR_PENDING_INTERRUPT == STD_ON)
          /* Check if the Interrupt register is present for particular channel */
          RH850_SV_MODE_ICR_AND(16, LpTAUDProperties->pEICReg, PWM_CLEAR_PENDING_INTR_MASK);                            /* PRQA S 0499 # JV-01 */
          #endif
          /* Enable the Interrupt processing of the current channel with dummy read and execute syncp instruction */
          RH850_SV_CLEAR_ICR_SYNCP(8, LpTAUDProperties->pEICReg, PWM_ENABLE_INTR_MASK);                                 /* PRQA S 0751, 1006 # JV-01, JV-01 */
        } /* else No action required */
        /* End of LpTAUDProperties->pEICReg != NULL_PTR */

        /* Exit Protected area */
        PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
      } /* else No action required */
    } /* else No action required */
    /* End of if (PWM_SLAVE_CHANNEL == LpTAUDChannelConfigData->ucTimerMode) */
  } /* else No action required */
  /* End of LucDetErrFlag is E_OK */
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_SET_CHANNEL_OUTPUT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_SynchronousInit
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This routine starts all PWM channels configured to synchronous start/stop of timers.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpChannelConfig
**
** Functions invoked     : Pwm_HW_TAUD_CalculateDuty
**
** Registers Used        : TAUDnTS, TAUD3INTNOSELn.
**
** Reference ID          : PWM_DUD_ACT_037, PWM_DUD_ACT_037_REG001, PWM_DUD_ACT_037_REG002, PWM_DUD_ACT_037_REG003,
** Reference ID          : PWM_DUD_ACT_037_REG004, PWM_DUD_ACT_037_REG005, PWM_DUD_ACT_037_REG006
** Reference ID          : PWM_DUD_ACT_037_REG007
***********************************************************************************************************************/
#if (PWM_SYNC_START_SUPPORT == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_SynchronousInit(void)                                                          /* PRQA S 3006 # JV-01 */
{
  /* Pointer to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDProperties;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Pointer to the TAU Master Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDMasterProperties;                                    /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Pointer used for TAU channel control registers */
  P2VAR(volatile Pwm_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;
  /* Pointer used for TAU Master channel control registers */
  P2VAR(volatile Pwm_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDMasterChannelReg;                                  /* PRQA S 3678 # JV-01 */
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  VAR(Pwm_PeriodType, AUTOMATIC) LddMasterPeriod;
  VAR(Pwm_PeriodType, AUTOMATIC) LddSlaveDuty;
  VAR(uint8, AUTOMATIC) LucVar;
  VAR(uint32, AUTOMATIC) LulCount;

  /* Initialize all PWM channels configured to support synchronous start/stop of timers,
     this excludes initialization of channels that willbe handled by complex drivers */

  /* Loop to set the attributes of TAU channels */
  LpChannelConfig = Pwm_GpChannelConfig;
  for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_CHANNELS_CONFIG; LulCount++)
  {
    /* Set TAU channel config data pointer */
    LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                      /* PRQA S 0317 # JV-01 */
    /* Get the Timer Unit Type*/
    LucTimerUnitType = LpChannelConfig->ucTimerUnitType;

    if ((uint8)PWM_HWIP_TAUD == LucTimerUnitType)                                                                       /* PRQA S 3416 # JV-01 */
    {
      if ((PWM_TRUE == LpChannelConfig->blSyncStartReq) && (PWM_FALSE == LpTAUDChannelConfigData->blComplexDriverInit))
      {
        /* Get the pointer to the TAU channel properties */
        LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;   /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
        /* Get the pointer to the TAU channel control registers */
        LpTAUDChannelReg = LpTAUDProperties->pCntlRegs;
        /* Initialize value for TAUD3 Interrupt Number Selection register */
        #if (STD_ON == PWM_TAUD3_UNIT_USED)
        /* Check the TAUD3 Interrupt Number Selection register is configured for the current channel */
        if (NULL_PTR != LpTAUDProperties->pTAUD3INTNOSELxReg)
        {
          RH850_SET_IOREG_SYNCP(32, LpTAUDProperties->pTAUD3INTNOSELxReg,                                               /* PRQA S 1006 # JV-01 */
                                LpTAUDProperties->ulTAUD3InterruptSelectionMask);
        } /* else No action required */
        #endif

        /* Check for channel in the Master Mode */
        if ((uint8)PWM_MASTER_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)
        {
          /* Update the CMORm register of Master with the usCMORRegSettingsMask based on the configuration */
          *LpTAUDProperties->pCMORReg = LpTAUDProperties->usCMORRegSettingsMask;
          if ((Pwm_PeriodType)PWM_TAUD_MIN_PERIOD_VAL != LpTAUDProperties->ddDefaultPeriodOrDuty)
          {
            LpTAUDChannelReg->usTAUDnCDRm = (uint16)(LpTAUDProperties->ddDefaultPeriodOrDuty) - (uint16)PWM_ONE;
          }
          else
          {
            LpTAUDChannelReg->usTAUDnCDRm = PWM_TAUD_MIN_PERIOD_VAL;
          }
        }
        /* Channel in Slave Mode */
        else
        {
          /* Master offset from the slave channel */
          LucVar = LpTAUDChannelConfigData->ucMasterOffset;
          /* Get the pointer to the TAU Master channel properties */
          LpTAUDMasterProperties =
            (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))(LpChannelConfig - LucVar)->pChannelProp;       /* PRQA S 0311, 0316, 0488, 3432 # JV-01, JV-01, JV-01, JV-01 */
          /* if Default Period of Master of the slave channel is not zero */
          if ((Pwm_PeriodType)PWM_TAUD_MIN_PERIOD_VAL != LpTAUDMasterProperties->ddDefaultPeriodOrDuty)
          {
            /* Pointer to the Master channel registers */
            LpTAUDMasterChannelReg = LpTAUDMasterProperties->pCntlRegs;
            /* Get Master's period */
            LddMasterPeriod = LpTAUDMasterChannelReg->usTAUDnCDRm;
            /* Get Slave's Duty */
            LddSlaveDuty = LpTAUDProperties->ddDefaultPeriodOrDuty;
            /* Load the Absolute duty value in to the CDR Register */
            LpTAUDChannelReg->usTAUDnCDRm = (uint16)Pwm_HW_TAUD_CalculateDuty(LddMasterPeriod, LddSlaveDuty);
          }
          else
          {
            /* Load the zero in to the CDR Register */
            LpTAUDChannelReg->usTAUDnCDRm = PWM_TAUD_MIN_PERIOD_VAL;
          }
          /* Update the CMORm register of Slave with the usCMORRegSettingsMask based on the configuration */
          *LpTAUDProperties->pCMORReg = LpTAUDProperties->usCMORRegSettingsMask;
        } /* End of Channel in Slave Mode */
      } /* else No action required */
      /* End of if ((PWM_TRUE == LpChannelConfig->blSyncStartReq)
                 && (PWM_FALSE == LpTAUDChannelConfigData->blComplexDriverInit)) */
    } /* else No action required */
    /* End of if ((uint8)PWM_HWIP_TAUD == LucTimerUnitType) */
    /* Increment the pointer to the next channel */
    LpChannelConfig++;
  } /* End of for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_CHANNELS_CONFIG; LulCount++) */
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_SYNC_START_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_SynchronousStart
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This routine starts all PWM channels configured to support synchronous start/stop of timers.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpChannelConfig, Pwm_GpTAUDUnitConfig, Pwm_GaaChannelIdleStatus
**
** Functions invoked     : Pwm_HW_TAUD_SetOutputEnable
**
** Registers Used        : TAUDnTS.
**
** Reference ID          : PWM_DUD_ACT_031, PWM_DUD_ACT_031_REG001
** Reference ID          : PWM_DUD_ACT_031_GBL001
***********************************************************************************************************************/
#if (PWM_SYNC_START_SUPPORT == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_SynchronousStart(void)
{
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpTAUDUnitConfig;
  /* Pointer to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Pointer pointing to the TAU Unit control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  VAR(uint32, AUTOMATIC) LulCount;

  /* Start all PWM channels configured to support synchronous start/stop of timers,
     this excludes stopping of channels that will be handled by complex drivers */
  LpChannelConfig = Pwm_GpChannelConfig;
  for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_CHANNELS_CONFIG; LulCount++)
  {
    /* Get the Timer Unit Type*/
    LucTimerUnitType = LpChannelConfig->ucTimerUnitType;
    if ((uint8)PWM_HWIP_TAUD == LucTimerUnitType)                                                                       /* PRQA S 3416 # JV-01 */
    {
      /* Check whether the channel is started synchronously and set to its Idle state or not */
      if ((PWM_TRUE == LpChannelConfig->blSyncStartReq) && (PWM_TRUE == Pwm_GaaChannelIdleStatus[LulCount]))            /* PRQA S 1881 # JV-01 */
      {
        Pwm_HW_TAUD_SetOutputEnable(LpChannelConfig);
        /* Set the Idle state status of channel to PWM_FALSE */
        Pwm_GaaChannelIdleStatus[LulCount] = (uint8)PWM_FALSE;                                                          /* PRQA S 4304 # JV-01 */
      } /* else No action required */
    } /* else No action required */
    /* Increment the pointer to the next channel */
    LpChannelConfig++;
  } /* End of TAU Channels for loop */
  /* Update the TAUD unit config pointer */
  LpTAUDUnitConfig = Pwm_GpTAUDUnitConfig;
  for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_TAUD_UNITS_CONFIG; LulCount++)                         /* PRQA S 2877 # JV-01 */
  {
    /* Update the pointer for the base address of the TAUD unit registers */
    LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
    /* Set the channel bits that are configured for synchronous start to enable the count operation */
    LpTAUDUnitUserReg->usTAUDnTS = LpTAUDUnitConfig->usSyncInitMask;
    LpTAUDUnitConfig++;                                                                                                 /* PRQA S 2983 # JV-01 */
  }
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_SYNC_START_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_SetOutputEnable
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This routine starts all PWM channels configured to support synchronous start/stop of timers.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpTAUDUnitConfig
**
** Functions invoked     : None
**
** Registers Used        : TAUDnTOE.
**
** Reference ID          : PWM_DUD_ACT_036, PWM_DUD_ACT_036_REG001
***********************************************************************************************************************/
#if (PWM_SYNC_START_SUPPORT == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_SetOutputEnable(                                                               /* PRQA S 1505 # JV-01 */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig)
{
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpTAUDUnitConfig;
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  /* Pointer pointing to the TAU Unit user control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDProperties;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */

  /* Set TAU channel config data pointer */
  LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                        /* PRQA S 0317 # JV-01 */
  /* Fetch the pointer to the current TAU Unit config */
  LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
  /* Get the pointer to the TAU unit registers */
  LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
  /* Get the pointer to the TAU channel properties */
  LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;         /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
  /* Enable the output of the current channel */
  LpTAUDUnitUserReg->usTAUDnTOE = LpTAUDUnitUserReg->usTAUDnTOE | LpTAUDProperties->usChannelMask;
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_SYNC_START_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Pwm_HW_TAUD_SynchronousStop
**
** Service ID            : NA
**
** Description           : This is PWM Driver Component support function.
**                         This function stops PWM channels configured synchronous, support stop timers and set the
**                         synchronous channels to idle state.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Pre-conditions        : NA
**
** Global Variables used : Pwm_GpTAUDUnitConfig, Pwm_GpChannelConfig, Pwm_GaaChannelIdleStatus
**
** Functions invoked     : None
**
** Registers Used        : TAUDnTT.
**
** Reference ID          : PWM_DUD_ACT_032, PWM_DUD_ACT_032_REG001, PWM_DUD_ACT_032_REG002, PWM_DUD_ACT_032_REG003
** Reference ID          : PWM_DUD_ACT_032_REG004, PWM_DUD_ACT_032_GBL001
***********************************************************************************************************************/
#if (PWM_SYNC_START_SUPPORT == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_SynchronousStop(void)
{
  /* Pointer to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Pointer pointing to the TAU Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpTAUDUnitConfig;
  /* Pointer to the TAU Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDProperties;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Pointer pointing to the TAU Unit user control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerUnitType;
  VAR(uint32, AUTOMATIC) LulCount;

  /* Update the TAU unit config pointer */
  LpTAUDUnitConfig = Pwm_GpTAUDUnitConfig;
  /* Get the configuration of TAU channels */
  LpChannelConfig = Pwm_GpChannelConfig;
  /* Loop to set the attributes of TAU channels */
  for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_TAUD_UNITS_CONFIG; LulCount++)                         /* PRQA S 2877 # JV-01 */
  {
    /* Update the pointer for the base address of the TAU unit registers */
    LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
    /* Set the channel bits that are configured for synchronous start, to disable the count operation */
    LpTAUDUnitUserReg->usTAUDnTT = LpTAUDUnitConfig->usSyncInitMask;
    LpTAUDUnitConfig++;                                                                                                 /* PRQA S 2982 # JV-01 */
  }
  /* Set the Channel Idle State to Idle for all synchronous channels*/
  for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_CHANNELS_CONFIG; LulCount++)
  {
    /* Get the Timer Unit Type*/
    LucTimerUnitType = LpChannelConfig->ucTimerUnitType;
    /* Set TAU channel config data pointer */
    LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                      /* PRQA S 0317 # JV-01 */
    if ((uint8)PWM_HWIP_TAUD == LucTimerUnitType)                                                                       /* PRQA S 3416 # JV-01 */
    {
      if ((PWM_TRUE == LpChannelConfig->blSyncStartReq) && (PWM_FALSE == LpTAUDChannelConfigData->blComplexDriverInit)
          && ((uint8)PWM_SLAVE_CHANNEL == LpTAUDChannelConfigData->ucTimerMode))
      {
        /* Fetch the pointer to the current TAU Unit config */
        LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
        /* Update the pointer for the base address of the TAU unit registers */
        LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
        /* Set TAUD channel properties pointer */
        LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;   /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
        /* Set the corresponding channel bit to disable TOEm operation */
        LpTAUDUnitUserReg->usTAUDnTOE = ((LpTAUDUnitUserReg->usTAUDnTOE) & (uint16)(~LpTAUDProperties->usChannelMask));
        if ((uint8)PWM_LOW == LpChannelConfig->ucIdleLevel)
        {
          /* Reset the corresponding bit if Idle state is LOW */
          LpTAUDUnitUserReg->usTAUDnTO = (LpTAUDUnitUserReg->usTAUDnTO & (uint16)(~LpTAUDProperties->usChannelMask));
        }
        else
        {
          /* Set the corresponding bit if Idle state is HIGH */
          LpTAUDUnitUserReg->usTAUDnTO = (LpTAUDUnitUserReg->usTAUDnTO | (uint16)LpTAUDProperties->usChannelMask);
        }
        /* Set the Idle state of Synchronous channel to Idle */
        Pwm_GaaChannelIdleStatus[LulCount] = (uint8)PWM_TRUE;                                                           /* PRQA S 4304 # JV-01 */
      } /* else No action required */
    } /* else No action required */
    /* Increment the pointer to the next channel */
    LpChannelConfig++;
  } /*End of for (LulCount = (uint32)PWM_ZERO; LulCount < (uint32)PWM_TOTAL_CHANNELS_CONFIG; LulCount++)*/
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_SYNC_START_SUPPORT == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_TAUD_SetDuty_FixedPeriodShifted
**
** Service ID           : NA
**
** Description          : This is PWM Driver Component support function.
**                        This function updates the duty cycle for
**                        FixedPeriodShifted ClassType channels of TAUD Units.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : LddChannelId and LusDutyCycle
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Pre-conditions       : NA
**
** Global Variable used : Pwm_GpTAUDUnitConfig, Pwm_GpChannelConfig, Pwm_GaaChannelIdleStatus
**
** Functions invoked    : Pwm_HW_TAUD_CalculateDuty, PWM_DEM_REPORT_ERROR
**
** Registers Used       : TAUDnTOE, TAUDnCDRm, TAUDnRDT, TAUDnRSF.
**
** Reference ID         : PWM_DUD_ACT_035, PWM_DUD_ACT_034_CRT001, PWM_DUD_ACT_035_CRT002, PWM_DUD_ACT_035_CRT003,
** Reference ID         : PWM_DUD_ACT_035_CRT004, PWM_DUD_ACT_035_ERR001, PWM_DUD_ACT_035_ERR002,
** Reference ID         : PWM_DUD_ACT_035_GBL001, PWM_DUD_ACT_035_GBL002, PWM_DUD_ACT_035_REG001,
** Reference ID         : PWM_DUD_ACT_035_REG002, PWM_DUD_ACT_035_REG003, PWM_DUD_ACT_035_REG004,
** Reference ID         : PWM_DUD_ACT_035_REG005, PWM_DUD_ACT_035_REG006
***********************************************************************************************************************/
#if ((PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SET_PERIOD_AND_DUTY_API == STD_ON))
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_TAUD_SetDuty_FixedPeriodShifted(Pwm_ChannelType LddChannelId, uint16 LusDutyCycle)  /* PRQA S 1505 # JV-01 */
{
  /* Pointer pointing to the TAUD Unit configuration */
  P2CONST(Pwm_TAUDUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpTAUDUnitConfig;
  /* Pointer pointing to the channel configuration */
  P2CONST(Pwm_ChannelConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA) LpChannelConfig;
  /* Local pointer to the each Timer-E channel configuration */
  P2CONST(Pwm_TAUChannelConfigType, AUTOMATIC, PWM_CONFIG_CONST) LpTAUDChannelConfigData;
  /* Pointer pointing to the TAUD Unit control registers */
  P2VAR(volatile Pwm_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  /* Pointer used for TAUD channel control registers */
  P2VAR(volatile Pwm_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;
  /* Pointer to the TAUD Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDProperties;                                          /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Pointer to the TAUD Master Channel Properties structure */
  P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA) LpTAUDMasterProperties;                                    /* PRQA S 3432, 3678 # JV-01, JV-01 */
  VAR(Pwm_PeriodType, AUTOMATIC) LddMasterPeriod;
  VAR(uint32, AUTOMATIC) LulCount;
  VAR(uint16, AUTOMATIC) LusChannelMask;
  VAR(uint8, AUTOMATIC) LucVar;
  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  VAR(boolean, AUTOMATIC) blDemReport;

  blDemReport = PWM_FALSE;
  #endif
  /* Initialize a pointer to the channel configuration */
  LpChannelConfig = &Pwm_GpChannelConfig[LddChannelId];
  /* Set TAU channel config data pointer */
  LpTAUDChannelConfigData = LpChannelConfig->pHWIPChannelConfig;                                                        /* PRQA S 0317 # JV-01 */
  /* Get the pointer to the TAUD channel properties */
  LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;         /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
  /* Check whether the channel in Master mode */
  if ((uint8)PWM_MASTER_CHANNEL == LpTAUDChannelConfigData->ucTimerMode)
  {
    /* Get the channel mask for the particular channel */
    LusChannelMask = LpTAUDProperties->usChannelMask;
    /* Fetch the pointer to the current TAUD Unit config */
    LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
    /* Fetch the pointer to the current TAUD Unit Registers */
    LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
    /* Initialize a pointer to the Master's control register configuration of TAUD */
    LpTAUDChannelReg = LpTAUDProperties->pCntlRegs;

    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

    /* Get the master's period */
    LddMasterPeriod = LpTAUDChannelReg->usTAUDnCDRm;
    for (LulCount = (uint32)PWM_ONE; (uint32)PWM_THREE >= LulCount; LulCount++)
    {
      /* Increment the channel Id */
      LddChannelId++;                                                                                                   /* PRQA S 1338, 3383 # JV-01, JV-01 */
      /* Increment the channel for the next channel */
      LpChannelConfig++;
      /* Get the pointer to the TAUD channel properties */
      LpTAUDProperties = (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;     /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
      /* Initialize a pointer to the slave's control register configuration of TAUD */
      LpTAUDChannelReg = LpTAUDProperties->pCntlRegs;
      /* Check for the Slave1 and Slave3 channels */
      if (((uint32)PWM_ONE == LulCount) || ((uint32)PWM_THREE == LulCount))
      {
        /* Check whether the channel is set to its Idle state */
        if (PWM_TRUE == Pwm_GaaChannelIdleStatus[LddChannelId])                                                         /* PRQA S 1881 # JV-01 */
        {
          /* Enable the output of the current channel */
          LpTAUDUnitUserReg->usTAUDnTOE = (LpTAUDUnitUserReg->usTAUDnTOE | LpTAUDProperties->usChannelMask);
          /* Set the Idle state of the channel to PWM_FALSE */
          Pwm_GaaChannelIdleStatus[LddChannelId] = (uint8)PWM_FALSE;                                                    /* PRQA S 4304 # JV-01 */
        } /* else No action required */
      } /* else No action required */
      /* Check whether simultaneous rewrite has been completed */
      if (PWM_TAUD_RESET_16BIT_REG == (uint16)(LusChannelMask & LpTAUDUnitUserReg->usTAUDnRSF))
      {
        /* Load the Absolute duty value in to the CDR Register */
        LpTAUDChannelReg->usTAUDnCDRm =
          (uint16)Pwm_HW_TAUD_CalculateDuty(LddMasterPeriod, (Pwm_PeriodType)LusDutyCycle);
      }
      else
      {
        LusChannelMask = LusChannelMask & (uint16)(~LpTAUDProperties->usChannelMask);
        #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
        /* Set Dem error flag */
        blDemReport = PWM_TRUE;
        #endif
      }
    } /*End of for (LulCount = (uint32)PWM_ONE; (uint32)PWM_THREE >= LulCount; LulCount++) */
    /* Set the corresponding channel Trigger bit to specifies the channel for which simultaneous rewrite is executed */
    LpTAUDUnitUserReg->usTAUDnRDT = LusChannelMask;

    /* Exit Protected area */
    PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

    #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
    if (PWM_TRUE == blDemReport)
    {
      PWM_DEM_REPORT_ERROR(PWM_E_REWRITE_FAILED, DEM_EVENT_STATUS_FAILED);
    } /* else No action required */
    #endif
  } /* End of if (PWM_MASTER_CHANNEL == LpTAUDChannelConfigData->ucTimerMode) */
  else
  {
    /* Get the offset of the Master from the slave channel */
    LucVar = LpTAUDChannelConfigData->ucMasterOffset;
    /* Get the pointer to the TAUD Master channel properties */
    LpTAUDMasterProperties =
      (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))(LpChannelConfig - LucVar)->pChannelProp;             /* PRQA S 0311, 0316, 0488, 3432 # JV-01, JV-01, JV-01, JV-01 */
    /* Fetch the pointer to the current TAUD Unit config */
    LpTAUDUnitConfig = &Pwm_GpTAUDUnitConfig[LpTAUDChannelConfigData->ucTimerUnitIndex];
    /* Fetch the pointer to the current TAUD Unit Registers */
    LpTAUDUnitUserReg = LpTAUDUnitConfig->pUserCntlRegs;
    /* Get the masters channel ID*/
    LddChannelId = (LddChannelId - (LpTAUDChannelConfigData->ucMasterOffset));                                          /* PRQA S 1338 # JV-01 */
    /* Get the Master channel config pointer*/
    LpChannelConfig = LpChannelConfig - LpTAUDChannelConfigData->ucMasterOffset;                                        /* PRQA S 0488 # JV-01 */
    /* Get the channel mask from the channel configuration */
    LusChannelMask = LpTAUDProperties->usChannelMask;
    /* Initialize a pointer to the Master's control register configuration of TAUD */
    LpTAUDChannelReg = LpTAUDMasterProperties->pCntlRegs;

    /* Enter Protected area */
    PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

    /* Get the master's period */
    LddMasterPeriod = LpTAUDChannelReg->usTAUDnCDRm;
    /* Initialize a pointer to the slave's control register configuration of TAUD */
    LpTAUDChannelReg = LpTAUDProperties->pCntlRegs;
    /* Loop to set slave 1 and slave 2 of the particular Master for the
       3 consecutive channels configured in fixed period shifted classtype */
    for (LulCount = (uint32)PWM_ONE; (uint32)PWM_THREE >= LulCount; LulCount++)
    {
      /* Increment the channel Id */
      LddChannelId++;                                                                                                   /* PRQA S 1338, 3383 # JV-01, JV-01 */
      /* Increment the pointer to the next channel */
      LpChannelConfig++;
      /* Get the pointer to the TAUD channel properties */
      LpTAUDProperties =
        (P2VAR(Pwm_TAUDChannelPropType, AUTOMATIC, PWM_CONFIG_DATA))LpChannelConfig->pChannelProp;                      /* PRQA S 0311, 0316, 3432 # JV-01, JV-01, JV-01 */
      /* Check for Salve 1 or Slave 3 of the Master */
      if (((uint32)PWM_ONE == LulCount) || ((uint32)PWM_THREE == LulCount))
      {
        /* Check whether the channel is set to its Idle state */
        if (PWM_TRUE == Pwm_GaaChannelIdleStatus[LddChannelId])                                                         /* PRQA S 1881 # JV-01 */
        {
          /* Enable the output of the current channel */
          LpTAUDUnitUserReg->usTAUDnTOE = (LpTAUDUnitUserReg->usTAUDnTOE | LpTAUDProperties->usChannelMask);
          /* Set the Idle state of the channel to PWM_FALSE */
          Pwm_GaaChannelIdleStatus[LddChannelId] = (uint8)PWM_FALSE;                                                    /* PRQA S 4304 # JV-01 */
        } /* else No action required */
      } /* else No action required */
    } /*End of for (LulCount = (uint8)PWM_ONE; (uint8)PWM_THREE >= LulCount; LulCount++)*/

    /* Check whether simultaneous rewrite has been completed */
    if (PWM_TAUD_RESET_16BIT_REG == (uint16)(LusChannelMask & LpTAUDUnitUserReg->usTAUDnRSF))
    {
      /* Load the Absolute duty value in to the CDR Register */
      LpTAUDChannelReg->usTAUDnCDRm = (uint16)Pwm_HW_TAUD_CalculateDuty(LddMasterPeriod, (Pwm_PeriodType)LusDutyCycle);
      /* Set the corresponding channel Trigger bit to specifies the channel
         for which simultaneous rewrite is executed */
      LpTAUDUnitUserReg->usTAUDnRDT = LusChannelMask;
    }
    #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
    else
    {
      /* Set Dem error flag */
      blDemReport = PWM_TRUE;
    }
    #endif

    /* Exit Protected area */
    PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

    #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
    if (PWM_TRUE == blDemReport)
    {
      PWM_DEM_REPORT_ERROR(PWM_E_REWRITE_FAILED, DEM_EVENT_STATUS_FAILED);
    } /* else No action required */
    #endif
  } /* End of if (PWM_MASTER_CHANNEL != LpTAUDChannelConfigData->ucTimerMode) */
}
#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (PWM_SET_DUTY_CYCLE_API == STD_ON) or (PWM_SET_PERIOD_AND_DUTY_API == STD_ON) */

#endif /* (PWM_TAUD_UNIT_USED == STD_ON) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
