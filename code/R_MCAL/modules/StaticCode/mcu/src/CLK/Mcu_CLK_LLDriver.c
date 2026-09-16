/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_CLK_LLDriver.c                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains API function implementations of MCU Driver                                                      */
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
/*              Devices:        X2X                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025   : Update SW-VERSION for U2Bx Ver22.02.00.001 Release
 * 2.5.0:  30/06/2025   : Update SW-VERSION for U2Ax Ver22.01.00(D) Release
 * 2.4.0:  31/05/2025   : Update SW-VERSION for U2Cx Ver21.01.01 Release
 *                        As part of ARDAACL-55064, following changes are made:
 *                        - Update function Mcu_CLKSetCMUClock to check if CMU is used for the current clock setting
 * 2.3.2:  29/04/2025   : Update SW-VERSION for U2Ax Ver22.00.03 Release
 * 2.3.1:  31/03/2025   : Update SW-VERSION for U2BxE Ver22.00.02 Release
 * 2.3.0:  28/02/2025   : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D Release
 *                        As part of GTM HWIP support, following changes are made:
 *                        - Update function Mcu_CLKSetCCMClock to check NULL_PTR for pCCMnFXCLKCFGReg
 * 2.2.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Release
 * 2.1.2:  31/10/2024   : Update SW-VERSION to 2.1.2
 *                        As part of GTM HWIP support, following changes are made:
 *                        - Add function Mcu_CLKSetCCMClock, Mcu_CLKSetCMUClock
 *                        - Update function Mcu_CLKDistributeClocks to invoke Mcu_CLKSetCMUClock
 * 2.1.1:  30/08/2024   : Update SW-VERSION to 2.1.1
 *                        As part of U2Cx device support, following changes are made:
 *                        - Update function Mcu_CLKTrimming to add critical section for operation setting HSOSC Trimming
 *                        Period and start the HSOSC Trimming Function
 *                        - Update function Mcu_CLKStartSubOsc to add critical section for operation setting the Sub OSC
 *                        Stabilization Time Register and start the Sub OSC
 *                        - Add function Mcu_CLKTrimming and Mcu_CLKSetTrimmingCode
 *                        - Update function Mcu_CLKInitClock to invoke function Mcu_CLKTrimming
 *                        - Add function Mcu_CLKStartSubOsc and Mcu_CLKStopSubOsc
 *                        - Update function Mcu_CLKInitClock to invoke function Mcu_CLKStartSubOsc and Mcu_CLKStopSubOsc
 *                        As part of QAC 9.5.0 support, following changes are made:
 *                        - Remove redundant QAC message 1534
 * 2.0.1:  22/10/2023   : Update function Mcu_CLKInitClock:
 *                        - Remove the clock source setting for System Clock when blPllUsed is MCU_FALSE.
 *                        - Invoke function Mcu_CLKSetPFD and Mcu_CLKDistributeClocks
 *                        Update function Mcu_CLKDistributeClocks to add the Clock Gear Down process if the configured
 *                        system clock is not PLLO.
 *         19/10/2023   : Add function Mcu_CLKSetPFD
 * 2.0.0:  04/08/2023   : Add QAC message 1006, 2814
 *                        Remove redundant QAC message 0791, 2982
 *         10/07/2023   : Remove redundant QAC message 1505, 2962
 * 1.4.5:  06/01/2023   : As new Mcu structure:
 *                        - Update functions: Mcu_CLKSetFout, Mcu_CLKSetModuleClocks, Mcu_CLKStopMask, Mcu_CLKInitClock,
 *                          Mcu_CLKDistributeClocks, Mcu_CLKGetPllStatus, 
 *                        - Add functions: Mcu_CLKValidateSR, Mcu_CLKWriteCR, Mcu_CLKShiftWriteCR, Mcu_CLKShiftCpuSys
 *                        - Remove functions: Mcu_HW_SetClockGenerator, Mcu_HW_SetClockGearUp, Mcu_HW_SetClockGearDown,
 *                          Mcu_HW_SetStandbyClockGearUp, Mcu_HW_SetStandbyClockGearDown, Mcu_HW_StartMainOsc,
 *                          Mcu_HW_StartPLL, Mcu_HW_StopMainOsc, Mcu_HW_StopPLL
 *                        - Add QAC Messages
 * 1.4.4:  01/09/2022   : Add QAC Message (3:2469)
 *         31/08/2022   : Update Mcu_HW_SetClockGenerator, Mcu_HW_SetClockGearUp, Mcu_HW_SetClockGearDown
 *                        to check PLL, SSCG, SSCG1 domain
 *         15/07/2022   : Add QAC msg 2996, 2992, 0306, 2880, 0303
 *         11/07/2022   : Remove MCU_SSCG_ENABLE in Mcu_HW_SetClockMonitor
 * 1.4.3:  23/06/2022   : Update description of QAC Message (2:0857), (7:0791), (1:1532), (2:2982), (2:0303), (4:5087),
 *                        (3:3416), (1:3384), (3:3387), (1:1505), (2:3432), (2:0316), (2:0306), (6:2992), (2:3678),
 *                        (3:3415), (8:2810)
 *                        Remove QAC Message (6:2991), (6:2995), (2:1051)
 *                        Add QAC Message (3:2004)
 *         18/06/2022   : Update Mcu_HW_RestartClockMonitor to support check PLL, SSCG, SSCG1 domain
 *                        Remove LulCurrentSscg1SysClk in Mcu_HW_SetClockGenerator
 *         14/06/2022   : Remove macro MCU_DEVICE_U2X, MCU_DEVICE_E2X, MCU_DEVICE_U2AX and code inside for
 *                        Mcu_HW_SetClockGearUp, Mcu_HW_SetClockGearDown, Mcu_HW_SetStandbyClockGearDown
 *                        and Mcu_HW_SetStandbyClockGearUp
 *         24/05/2022   : Update QAC msg 2987
 *         20/05/2022   : Update Mcu_HW_SetExternalClockOut() by move process select clock before clock divider setting
 *                        and check Clock Divider Synchronized is stable
 *         19/05/2022   : Removed macro MCU_CLM_RESET_WAIT_CNT_NUM
 *                        Remove while loop for action Wait Clock Monitor Reset Time of function
 *                        Mcu_HW_StopClockMonitor, Mcu_HW_RestartClockMonitor and Mcu_HW_InitClockMonitor
 *         14/05/2022   : In internal function Mcu_HW_SetClockGearUp and Mcu_HW_SetClockGearDown, add while loop to
 *                        check CLKD_PLLS and verify that the value of PLLCLKDSYNC is 1
 *         13/05/2022   : Correct Ref ID in Mcu_HW_SetClockGenerator, Mcu_HW_SetClockGearUp, Mcu_HW_EnableCLMA
 *                        Mcu_HW_ClockValidation, Mcu_HW_SetStandbyClockGearDown
 *         11/05/2022   : Removed "else" statement don't use when no action required
 *         13/04/2022   : Update SW-VERSION to 1.4.3
 * 1.3.2:  17/10/2021   : + Update sequence Mcu_HW_SetClockGenerator to support
 *                        set clock SSCG and SSCG1 clock for U2Bx device
 *                        + Update sequence Mcu_HW_SetClockGearUp, Mcu_HW_SetClockGearDown,
 *                        Mcu_HW_SetStandbyClockGearUp, Mcu_HW_SetStandbyClockGearDown
 *                        with new hardware flow support commonize U2Ax and U2Bx
 * 1.3.1:  02/07/2021   : Add QAC message 9.5.0
 *                        Format source code to 120 characters
 *                        Improve Violation tag (remove START/END)
 *         12/05/2020   : + Removed space of  "LulCount --" in function
 *                        Mcu_HW_SetStandbyClockGearDown and
 *                        Mcu_HW_SetStandbyClockGearUp
 *                        As per ARDAACL-207,
 *                        + Add internal function support clock source change
 *                        Mcu_HW_StartMainOsc, Mcu_HW_SetClockGearDown
 *                        Mcu_HW_StartPLL, Mcu_HW_SetClockStopMask
 *                        Mcu_HW_StopMainOsc, Mcu_HW_StopPLL
 *                        Mcu_HW_InitClockMonitor, Mcu_HW_SetDomainClock
 *                        + Update sequence for Mcu_HW_SetClockGenerator to support
 *                        multiple clock config
 *                        + Update sequence for Mcu_HW_SetClockGearUp to support
 *                        multiple clock config
 *                        + Update Mcu_HW_EnableCLMA to call Mcu_HW_StartMainOsc
 *                        incase Main OSC is stop for U2Ax device, add break
 *                        loop condition to reduce redundant loop
 *                        + Update Mcu_HW_RestartClockMonitor, to corret the mask
 *                        value for stable state of Main Osc
 *                        + Update Mcu_HW_ClockValidation to correct mask value
 *                        for clock register
 *         07/05/2021   : As per ARDAACL-145, Update preprocessor in definition
 *                        of Mcu_HW_SetClockGearUp function
 * 1.2.1:  15/12/2020   : Updated condition when write to "MCU_MOSCE" and
 *                        "MCU_PLLS" registers
 *                        Moved MCU_CLKKCPROT1 out of branch of conditional
 *                        checking "MCU_CKSC_CPU_CLKEMG_SELECT"
 * 1.2.0:  17/07/2020   : Release
 * 1.1.0:  19/06/2020   : Release
 * 1.0.10: 16/06/2020   : As per ticket #267934
 *                       Update to add QAC message for lastest MCU driver code
 *                       Related msg 2982
 * 1.0.9:  15/06/2020   : As per #274628
 *                       Mcu_HW_EnableCLMA, Update intial value of return value
 *                       Update pre-compile marcro
 * 1.0.8:  09/06/2020   : As per #270097
 *                       Fix Critical section protection in
 *                       Mcu_HW_SetClockGearUp due to Critical section
 *                       timming violation.
 * 1.0.7:  08/06/2020   : As per #261032
 *                       Update return value of Mcu_HW_RestartClockMonitor
 *                       in case LucOscStatus is E_NOT_OK.
 *                       Update to add return value for Mcu_HW_EnableCLMA
 * 1.0.6:  07/06/2020   : Update header note for Mcu_HW_SetStandbyClockGearDown
 *                       Mcu_HW_SetStandbyClockGearUp
 * 1.0.5:  03/06/2020   : As per ticket #253269
 *                       Update to add EXECUTE_SYNCP() in while count loop in
 *                       Mcu_HW_SetExternalClockOut, Mcu_HW_ClockValidation
 * 1.0.4:  21/05/2020   : As per ticket #270989
 *                       Update to check status of clock generator for E2x
 *                       in Mcu_HW_SetClockGenerator
 * 1.0.3:  18/05/2020   : As per ticket #268957
 *                       Update Critical section 's name in MCU driver to unify
 *                       with other MCAL modules
 * 1.0.2:  18/05/2020   : As per #267934
 *                       + Add 2 internal function
 *                       Mcu_HW_SetStandbyClockGearDown and
 *                       Mcu_HW_SetStandbyClockGearUp to HW version up U2x
 *                       0.7 to 0.9
 *                       for Mcu_HW_RestartClockMonitor
 * 1.0.1:  23/04/2020   : As per #261032
 *                       + Update to check clock gear up and OSC status
 *                       for Mcu_HW_RestartClockMonitor
 *                       Update traceability UD-CD
 *                       As per #261010
 *                       + Update function header for Mcu_HW_StopClockMonitor
 * 1.0.0:  10/01/2020   : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:0311)    : Dangerous pointer cast results in loss of const qualification.                               */
/* Rule                : MISRA C:2012 Rule-11.8, CERTCCM EXP05                                                        */
/* JV-01 Justification : This is to achieve throughput in the code.                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
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
/* Message (2:1006)    : This in-line assembler construct is a language extension. The code has been ignored.         */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTCCM MSC14                                       */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
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
/* Message (2:2834)    : Possible: Division by zero.                                                                  */
/* Rule                : CERTCCM INT33, CWE Rule CWE-128, CWE-369, CWE-738, CWE-680                                   */
/* JV-01 Justification : Value generated by generation tool is always different from zero.                            */
/*       Verification  : It's not impact to driver source code implementation                                         */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for module version information */
#include "Mcu.h"

/* Included for RAM variable declarations */
#include "Mcu_Ram.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define MCU_CLK_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    MCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define MCU_CLK_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    MCU_AR_RELEASE_MINOR_VERSION_VALUE
#define MCU_CLK_LLDRIVER_C_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MCU_CLK_LLDRIVER_C_SW_MAJOR_VERSION            MCU_SW_MAJOR_VERSION_VALUE
#define MCU_CLK_LLDRIVER_C_SW_MINOR_VERSION            MCU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (MCU_CLK_LLDRIVER_AR_RELEASE_MAJOR_VERSION != MCU_CLK_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "Mcu_CLK_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (MCU_CLK_LLDRIVER_AR_RELEASE_MINOR_VERSION != MCU_CLK_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "Mcu_CLK_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (MCU_CLK_LLDRIVER_AR_RELEASE_REVISION_VERSION != MCU_CLK_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "Mcu_CLK_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (MCU_CLK_LLDRIVER_SW_MAJOR_VERSION != MCU_CLK_LLDRIVER_C_SW_MAJOR_VERSION)
#error "Mcu_CLK_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (MCU_CLK_LLDRIVER_SW_MINOR_VERSION != MCU_CLK_LLDRIVER_C_SW_MINOR_VERSION)
#error "Mcu_CLK_LLDriver.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                             Internal Function Prototypes                                           **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                         Static Function Definitions                                                **
***********************************************************************************************************************/

#if (MCU_INIT_CLOCK == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"

STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKSetFout(uint8 LucIdx);
#if ((MCU_SSCG_ENABLE == STD_ON)||(MCU_SSCG1_ENABLE == STD_ON))
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKSetPFD(void);
#endif  /* (MCU_SSCG_ENABLE == STD_ON)||(MCU_SSCG1_ENABLE == STD_ON) */
#if (MCU_CLOCK_TRIMMING_SUPPORT == STD_ON)
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKTrimming(void);

STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKSetTrimmingCode(void);
#endif /* MCU_CLOCK_TRIMMING_SUPPORT == STD_ON */

#if (MCU_SOSC_SUPPORT == STD_ON)
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKStartSubOsc(void);

STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKStopSubOsc(void);
#endif /* MCU_SOSC_SUPPORT == STD_ON */

#if ((MCU_GTM_SETTING == STD_ON) && (MCU_INIT_CLOCK == STD_ON))
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKSetCCMClock(void);
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKSetCMUClock(void);
#endif /* (MCU_GTM_SETTING == STD_ON) && (MCU_INIT_CLOCK == STD_ON) */

STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKSetModuleClocks(void);

STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKValidateSR(
  volatile P2CONST(uint32, TYPEDEF, REGSPACE) LpCLKSReg,
  const uint32 LulRegValue,
  const uint32 LulRegMask,
  const uint32 LulMaxCount);

STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKWriteCR(
  volatile CONSTP2CONST(uint32, TYPEDEF, REGSPACE) LpCLKCReg,
  volatile P2CONST(uint32, TYPEDEF, REGSPACE) LpCLKSReg,
  uint32 ulCRVal,
  uint32 ulSRVal,
  uint32 ulSRMask);

STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKShiftWriteCR(
  Mcu_ClkModeType LenClkMode,
  volatile CONSTP2CONST(uint32, TYPEDEF, REGSPACE) LpCLKCReg,
  volatile P2CONST(uint32, TYPEDEF, REGSPACE) LpCLKSReg,
  uint32 ulCRVal,
  uint32 ulSRVal,
  uint32 ulSRMask);

#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_INIT_CLOCK == STD_ON */

#if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, MCU_PRIVATE_CODE) Mcu_CLKStopMask(void);
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_MODE_TRANSITION_SUPPORT == STD_ON */


/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name      : Mcu_CLKInitClock
**
** Service ID         : None
**
** Description        : This service initializes the PLL and other MCU specific clock options.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GpClockSetting, Mcu_GpClockHwInfo
**
** Function Invoked   : Mcu_CLKValidateSR, Mcu_CLKWriteCR, Mcu_CLKStartSubOsc, Mcu_CLKStopSubOsc, 
** Function Invoked   : Mcu_CLKDistributeClocks, Mcu_CLKTrimming
**
** Registers Used     : MOSCE, PLLE
**
** Reference ID       : MCU_DUD_ACT_055, MCU_DUD_ACT_055_REG001, MCU_DUD_ACT_055_REG002,
** Reference ID       : MCU_DUD_ACT_055_REG003, MCU_DUD_ACT_055_REG004
***********************************************************************************************************************/
#if (MCU_INIT_CLOCK == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKInitClock(void)
{
  Std_ReturnType LucReturnValue;
  uint8 LucPllStatus;
  uint8 LucMainOscStatus;
  LucReturnValue = E_OK;

  /* Check if HS IntOSC is used for the current clock setting */
  if (MCU_TRUE == Mcu_GpClockSetting->blHSOscUsed)                                                                      /* PRQA S 3416 # JV-01 */
  {
    /* Check if HS IntOSC is stable */
    LucReturnValue = Mcu_CLKValidateSR(                                                                                 /* PRQA S 0404 # JV-01 */
      Mcu_GpClockHwInfo->pHSOscSReg,
      MCU_HSOSC_CLK_STABLE,
      MCU_HSOSC_CLK_STABLE,
      Mcu_GpClockSetting->ulClkStbCount);
  } /* else No action is required */
  #if (MCU_CLOCK_TRIMMING_SUPPORT == STD_ON)
  /* Check if HS IntOSC is unstable */
  if ((E_NOT_OK == LucReturnValue) && (MCU_TRUE == Mcu_GpClockSetting->blClkTrimmingSupported))                         /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Adjust the HS IntOSC clock source frequency */
    LucReturnValue = Mcu_CLKTrimming();
  }
  #endif /* MCU_CLOCK_TRIMMING_SUPPORT == STD_ON */

  /* Check if Main OSC is used for the current clock setting */
  if ((E_OK == LucReturnValue) && (MCU_TRUE == Mcu_GpClockSetting->blMainOscUsed))                                      /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Confirm that the Main OSC is inactive */
    LucMainOscStatus = Mcu_CLKValidateSR(                                                                               /* PRQA S 0404 # JV-01 */
      Mcu_GpClockHwInfo->pMainOscSReg,
      MCU_MOSCS_CLK_STABLE,
      MCU_MOSCS_CLK_STABLE,
      Mcu_GpClockSetting->ulClkStbCount);
    if ((E_NOT_OK == LucMainOscStatus) && (MCU_TRUE == Mcu_GpClockSetting->blClkGenSupported))                          /* PRQA S 3415, 3416 # JV-01, JV-01 */
    {
      /* Enable the Main OSC (MOSCE.MOSCENTRG = 1) */
      LucReturnValue = Mcu_CLKWriteCR(                                                                                  /* PRQA S 0404 # JV-01 */
        Mcu_GpClockHwInfo->pMainOscEReg,
        Mcu_GpClockHwInfo->pMainOscSReg,
        MCU_MOSCE_ENABLE_TRIGGER,
        MCU_MOSCS_CLK_STABLE,
        MCU_MOSCS_CLK_STABLE);
    } /* else No action is required */
  } /* else No action is required */

  #if (MCU_SOSC_SUPPORT == STD_ON)
  /* Check if Sub OSC is used for the current clock setting */
  if ((E_OK == LucReturnValue) && (MCU_TRUE == Mcu_GpClockSetting->blSubOscUsed))                                       /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Enable Sub OSC */
    LucReturnValue = Mcu_CLKStartSubOsc();
  } /* else No action is required */
  #endif /* MCU_SOSC_SUPPORT == STD_ON */

  if (E_OK == LucReturnValue)
  {
    /* Check if the system clock is selected as PLLO */
    if (MCU_TRUE == Mcu_GpClockSetting->blPllUsed)                                                                      /* PRQA S 3416 # JV-01 */
    {
      /* Confirm the status of PLL */
      LucPllStatus = Mcu_CLKValidateSR(                                                                                 /* PRQA S 0404 # JV-01 */
        Mcu_GpClockHwInfo->pPllSReg,
        MCU_PLLS_CLK_STABLE,
        MCU_PLLS_CLK_STABLE,
        Mcu_GpClockSetting->ulClkStbCount);
      if ((E_NOT_OK == LucPllStatus) && (MCU_TRUE == Mcu_GpClockSetting->blClkGenSupported))                            /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        /* Start PLL */
        LucReturnValue = Mcu_CLKWriteCR(                                                                                /* PRQA S 0404 # JV-01 */
          Mcu_GpClockHwInfo->pPllEReg,
          Mcu_GpClockHwInfo->pPllSReg,
          MCU_PLLE_ENABLE_TRIGGER,
          MCU_PLLS_CLK_STABLE,
          MCU_PLLS_CLK_STABLE);
      } /* else No action is required */
    } /* else No action is required */

    if ((E_OK == LucReturnValue) && (MCU_TRUE == Mcu_GpClockSetting->blClkGenSupported))                                /* PRQA S 3415, 3416 # JV-01, JV-01 */
    {
      #if ((MCU_SSCG_ENABLE == STD_ON)||(MCU_SSCG1_ENABLE == STD_ON))
      /* Set the modulation depth of SSCGC/SSCG1 domain clock */
      LucReturnValue = Mcu_CLKSetPFD();
      if (E_OK == LucReturnValue)
      #endif
      {
        /* Distribute module clocks */
        LucReturnValue = Mcu_CLKDistributeClocks();
      } /* else No action is required */
      if ((E_OK == LucReturnValue) && (MCU_FALSE == Mcu_GpClockSetting->blPllUsed))                                     /* PRQA S 3415, 3416 # JV-01, JV-01 */
      {
        /* Confirm that the PLL is stable (PLLS.PLLCLKEN = 1 & PLLS.PLLCLKSTAB = 1) */
        LucPllStatus = Mcu_CLKValidateSR(                                                                               /* PRQA S 0404 # JV-01 */
          Mcu_GpClockHwInfo->pPllSReg,
          MCU_PLLS_CLK_STABLE,
          MCU_PLLS_CLK_STABLE,
          Mcu_GpClockSetting->ulClkStbCount);
        if (E_OK == LucPllStatus)
        {
          /* Stop PLL */
          LucReturnValue = Mcu_CLKWriteCR(                                                                              /* PRQA S 0404 # JV-01 */
            Mcu_GpClockHwInfo->pPllEReg,
            Mcu_GpClockHwInfo->pPllSReg,
            MCU_PLLE_DISABLE_TRIGGER,
            MCU_PLLS_CLK_STOPPED,
            MCU_CKSC_ALLMASK);
        } /* else No action is required */
      } /* else No action is required */
    } /* else No action is required */
  } /* else No action is required */

  /* Check if Main OSC is not selected as clock source for any clock domain */
  if ((E_OK == LucReturnValue) && (MCU_FALSE == Mcu_GpClockSetting->blMainOscUsed))                                     /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Confirm that the Main OSC is active */
    LucMainOscStatus = Mcu_CLKValidateSR(                                                                               /* PRQA S 0404 # JV-01 */
      Mcu_GpClockHwInfo->pMainOscSReg,
      MCU_MOSCS_CLK_STABLE,
      MCU_MOSCS_CLK_STABLE,
      Mcu_GpClockSetting->ulClkStbCount);
    if (E_OK == LucMainOscStatus)
    {
      /* Disable Main OSC */
      LucReturnValue = Mcu_CLKWriteCR(                                                                                  /* PRQA S 0404 # JV-01 */
        Mcu_GpClockHwInfo->pMainOscEReg,
        Mcu_GpClockHwInfo->pMainOscSReg,
        MCU_MOSCE_DISABLE_TRIGGER,
        MCU_MOSCS_STOPPED,
        MCU_CKSC_ALLMASK);
    } /* else No action is required */
  } /* else No action is required */

  #if (MCU_SOSC_SUPPORT == STD_ON)
  /* Check if Sub OSC is not selected as clock source for any clock domain */
  if ((E_OK == LucReturnValue) && (MCU_FALSE == Mcu_GpClockSetting->blSubOscUsed))                                      /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Disable Sub OSC */
    LucReturnValue = Mcu_CLKStopSubOsc();
  } /* else No action is required */
  #endif /* MCU_SOSC_SUPPORT == STD_ON */

  /* Return the value of clock initialization result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_INIT_CLOCK == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKDistributeClocks
**
** Service ID         : None
**
** Description        : This function activates the PLL clock to the MCU clock
**                      distribution and config module clocks.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpClockSetting, Mcu_GpClockHwInfo
**
** Function Invoked   : Mcu_CLKShiftCpuSys, Mcu_CLKSetCMUClock, Mcu_CLKSetModuleClocks, Mcu_CLMInit
**                      Mcu_CLMAStart, Mcu_CLKStopMask
**
** Registers Used     : CKSC_CPUC, CLKD_PLLC, CLK_PLLC, CKD_PLLC, CKD_SSCGC, CKD_SSCG1C
**
** Reference ID       : MCU_DUD_ACT_053, MCU_DUD_ACT_053_REG001, MCU_DUD_ACT_053_REG002
***********************************************************************************************************************/
#if (MCU_NO_PLL == STD_OFF)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKDistributeClocks(void)
{
  Std_ReturnType LucReturnValue;
  uint8 LucClkSrcStatus;
  uint8 LucIndex;
  uint32 LulSysClk;
  uint32 LulClkDivC;
  uint32 LulClkDivS;
  P2CONST(Mcu_ClockShiftSettingType, MCU_CONST, MCU_CONFIG_DATA) LpClockShiftSetting;
  P2CONST(Mcu_ClockModeSettingType, AUTOMATIC, MCU_CONFIG_DATA) LpClockModeSetting;

  LucReturnValue = E_OK;
  LpClockShiftSetting = Mcu_GpClockSetting->pClockShiftSetting;
  LpClockModeSetting = Mcu_GpClockSetting->pClockModeSetting;

  #if (MCU_CLMA_OPERATION == STD_ON)
  /* Initialize CLMA before clock gear up */
  Mcu_CLMInit();
  #endif /* MCU_CLMA_OPERATION == STD_ON */

  for (LucIndex = MCU_ZERO; LucIndex < Mcu_GpClockHwInfo->ucNoOfClkSrc; LucIndex++)
  {
    /* Check if the configured system clock is PLLO */
    if (MCU_CKSC_PLLO == LpClockModeSetting[LucIndex].ulCKSC)
    {
      /* Check current system clock source to prevent unnecessary Gear Up */
      LulSysClk = *(LpClockModeSetting[LucIndex].pCKSSAddr) & MCU_CKSC_MASK;
      if (MCU_CKSC_PLLO != LulSysClk)
      {
        /* Clock Gear Up */
        LucClkSrcStatus = Mcu_CLKShiftCpuSys(MCU_CLOCK_MODE, LucIndex, MCU_CLK_GEAR_UP, LpClockShiftSetting);
        if (E_NOT_OK == LucClkSrcStatus)
        {
          LucReturnValue = E_NOT_OK;
        } /* else No action is required */
      } /* else No action is required */
    }
    else
    {
      /* Check current system clock source */
      LulSysClk = *(LpClockModeSetting[LucIndex].pCKSSAddr) & MCU_CKSC_MASK;
      /* Check the current system clock divider control */
      LulClkDivC = *(LpClockModeSetting[LucIndex].pCLKDCAddr) & MCU_CKDC_MASK;
      /* Check the current system clock divider synchronized */
      LulClkDivS = *(LpClockModeSetting[LucIndex].pCLKDSAddr) & MCU_CKDS_SYNCMASK;
      /*
        * CLK_PLLO is selected as the clock source for the System clock,
        * and No division is selected as the division ratio of clock source PLL.
        */
      if ((MCU_CKSC_PLLO == LulSysClk) && (MCU_CKDC_DIV1 == LulClkDivC) && (MCU_CKDS_SRCCLKDSYNC_OK == LulClkDivS))
      {
        /* Clock Gear Down */
        LucClkSrcStatus = Mcu_CLKShiftCpuSys(MCU_CLOCK_MODE, LucIndex, MCU_CLK_GEAR_DOWN, LpClockShiftSetting);
        if (E_NOT_OK == LucClkSrcStatus)
        {
          LucReturnValue = E_NOT_OK;
        } /* else No action is required */
      } /* else No action is required */
    }
  }

  if (E_OK == LucReturnValue)
  {
    #if (MCU_GTM_SETTING == STD_ON)
    /* Set CMU sub unit */
    LucReturnValue = Mcu_CLKSetCMUClock();
    if (E_OK == LucReturnValue)
    #endif /* MCU_GTM_SETTING == STD_ON */
    {
      /* Set clock selector and clock divider for module clocks */
      LucReturnValue = Mcu_CLKSetModuleClocks();
    } /* else No action is required */
    if (E_OK == LucReturnValue)
    {
      #if (MCU_CLMA_OPERATION == STD_ON)
      /* Set clock monitor */
      Mcu_CLMStart();
      #endif /* MCU_CLMA_OPERATION == STD_ON */
      #if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
      /* Set clock stop mask */
      Mcu_CLKStopMask();
      #endif /* MCU_MODE_TRANSITION_SUPPORT == STD_ON */
    } /* else No action is required */
  } /* else No action is required */
  /* Return the value of setting the PLL clock result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* MCU_NO_PLL == STD_OFF */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKGetPllStatus
**
** Service ID         : None
**
** Description        : This service provides the lock status of the PLL.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Mcu_PllStatusType
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : PLLS, PLLCLKS
**
** Reference ID       : MCU_DUD_ACT_054
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Mcu_PllStatusType, MCU_PRIVATE_CODE) Mcu_CLKGetPllStatus(void)
{
  uint8 LucCount;
  Mcu_PllStatusType LenPllLockStatus;
  LenPllLockStatus = MCU_PLL_LOCKED;                                                                                    /* PRQA S 2982 # JV-01 */

  if (MCU_PLLS_CLK_STABLE == (*Mcu_GpClockHwInfo->pPllSReg & MCU_PLLS_CLK_STABLE))                                      /* PRQA S 0404 # JV-01 */
  {
    /* Read the PLLS.PLLCLKSTAB = 1 four times, get latest status */
    for (LucCount = MCU_ZERO ; LucCount <= MCU_PLLS_READ_COUNT; LucCount++)                                             /* PRQA S 2877 # JV-01 */
    {
      if (MCU_PLLCLKSTAB_MASK == (*Mcu_GpClockHwInfo->pPllSReg & MCU_PLLCLKSTAB_MASK))                                  /* PRQA S 0404 # JV-01 */
      {
        LenPllLockStatus = MCU_PLL_LOCKED;
      }
      else
      {
        LenPllLockStatus = MCU_PLL_UNLOCKED;
      }
    }
  }
  else
  {
    LenPllLockStatus = MCU_PLL_UNLOCKED;
  }

  return (LenPllLockStatus);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKSetModuleClocks
**
** Service ID         : None
**
** Description        : This service support to set clock selector and clock
**                      divider for all domain clock
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpClockSetting, Mcu_GpClockHwInfo
**
** Function Invoked   : Mcu_CLKValidateSR, Mcu_CLKSetFout
**
** Registers Used     : CKSC_RLINC, CKSC_RLINS, CKSC_RCANC, CKSC_RCANS,
**                      CKSC_MSPIC, CKSC_MSPIS, CKSC_AWDTC, CKSC_AWDTS,
**                      CKSC_ATAUJC, CKSC_ATAUJS, CKSC_ARTCAS, CKSC_ARTCAC,
**                      CKSC_FOUT0C, CKSC_FOUT0S, CLKD_FOUT0C, CLKD_FOUT0S,
**                      CKSC_WDTC, CKSC_WDTS, CLKKCPROT1
**
** Reference ID       : MCU_DUD_ACT_057, MCU_DUD_ACT_057_REG001
** Reference ID       : MCU_DUD_ACT_057_REG002, MCU_DUD_ACT_057_REG003
** Reference ID       : MCU_DUD_ACT_057_CRT001, MCU_DUD_ACT_057_CRT002
***********************************************************************************************************************/
#if (MCU_INIT_CLOCK == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKSetModuleClocks(void)
{
  /* Pointer to clock module setting */
  P2CONST(Mcu_ClockModuleSettingType, AUTOMATIC, MCU_CONFIG_DATA) LpClockModuleSetting;
  Std_ReturnType LucReturnValue;
  uint8 LucIdx;

  LucReturnValue = E_OK;
  LucIdx = MCU_ZERO;
  LpClockModuleSetting = Mcu_GpClockSetting->pClockModuleSetting;

  /* Disable interrupt to avoid access shared registers across APIs and re-entrant API */
  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  MCU_ADDR_WRITE32(Mcu_GpClockHwInfo->pPReg, MCU_CKSC_DISABLE_REG_PROTECT_VALUE);                                       /* PRQA S 3469 # JV-01 */

  /* Loop for setting all module clock */
  while ((E_OK == LucReturnValue) && (LucIdx < Mcu_GpClockSetting->ucNoOfClkModule))                                    /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    if (MCU_CLK_EXTCLKO == LpClockModuleSetting[LucIdx].enClkModuleType)
    {
      /* Set FOUT */
      LucReturnValue = Mcu_CLKSetFout(LucIdx);
    }
    else if (MCU_CLKA_ADC == LpClockModuleSetting[LucIdx].enClkModuleType)
    {
      /* Set CLKA_ADC clock */
      /* Set clock module selector */
      *((volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKSCAddr) = LpClockModuleSetting[LucIdx].ulCKSCValue;
      /* Verify setting */
      LucReturnValue = Mcu_CLKValidateSR(                                                                               /* PRQA S 2982 # JV-01 */
        (volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKSSAddr,
        LpClockModuleSetting[LucIdx].ulCKSCValue,
        MCU_CKSC_ALLMASK,
        Mcu_GpClockSetting->ulClkStbCount);
      /* Set clock module didiver */
      *((volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKDCAddr) = LpClockModuleSetting[LucIdx].ulCKDCValue;
      /* Verify setting */
      LucReturnValue = Mcu_CLKValidateSR(
        (volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKDSAddr,
        LpClockModuleSetting[LucIdx].ulCKDCValue,
        MCU_CKSC_ALLMASK,
        Mcu_GpClockSetting->ulClkStbCount);
    }
    else
    {
      /* Set clock module selector */
      *((volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKSCAddr) = LpClockModuleSetting[LucIdx].ulCKSCValue;
      /* Verify setting */
      LucReturnValue = Mcu_CLKValidateSR(
        (volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKSSAddr,
        LpClockModuleSetting[LucIdx].ulCKSCValue,
        MCU_CKSC_ALLMASK,
        Mcu_GpClockSetting->ulClkStbCount);
      /* Next module clock index */
    }
    LucIdx++;
  }

  MCU_ADDR_WRITE32(Mcu_GpClockHwInfo->pPReg, MCU_CKSC_ENABLE_REG_PROTECT_VALUE);                                        /* PRQA S 3469 # JV-01 */

  /* Enable interrupts after write */
  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  /* Return the value of setting module clock result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif  /* MCU_INIT_CLOCK == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKSetFout
**
** Service ID         : None
**
** Description        : This service set divider and selector for
**                      external clock out.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LucIdx - Module clock ID 
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : CKSC_FOUT0C, CKSC_FOUT0S, CLKD_FOUT0C, CLKD_FOUT0S
**
** Reference ID       : MCU_DUD_ACT_058, MCU_DUD_ACT_058_REG001
** Reference ID       : MCU_DUD_ACT_058_REG002, MCU_DUD_ACT_058_REG003
***********************************************************************************************************************/
#if (MCU_INIT_CLOCK == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKSetFout(uint8 LucIdx)
{
  /* Pointer to clock module setting */
  P2CONST(Mcu_ClockModuleSettingType, AUTOMATIC, MCU_CONFIG_DATA) LpClockModuleSetting;

  Std_ReturnType LucReturnValue;
  LucReturnValue = E_OK;
  LpClockModuleSetting = Mcu_GpClockSetting->pClockModuleSetting;
  /*
   * Do specific setting for FOUT Clock (EXTCLK0O/EXTCLK1O)
   */
  /* Check if external clock is stopped */
  if (MCU_FOUTDIVS_STOPPED != (*((volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKDSAddr) & MCU_CKSC_ALLMASK))
  {
    /* Check if external clock is stable */
    LucReturnValue = Mcu_CLKValidateSR(
      (volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKDSAddr,
      MCU_FOUTDIVS_STOPPED,
      MCU_CLKD_SYNCMASK,
      Mcu_GpClockSetting->ulClkStbCount);
    if (E_OK == LucReturnValue)
    {
      /* Stop external clock */
      *((volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKDCAddr) = MCU_FOUTDIVC_STOPPED;
      /* Verify the external clock status */
      LucReturnValue = Mcu_CLKValidateSR(
        (volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKDSAddr,
        MCU_FOUTDIVS_STOPPED,
        MCU_CKSC_ALLMASK,
        Mcu_GpClockSetting->ulClkStbCount);
    } /* else No action is required */

  } /* else No action is required */

  if (E_OK == LucReturnValue)
  {
    /* Set external clock selector */
    *((volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKSCAddr) = LpClockModuleSetting[LucIdx].ulCKSCValue;
    /* Verify the selector setting */
    LucReturnValue = Mcu_CLKValidateSR(
      (volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKSSAddr,
      LpClockModuleSetting[LucIdx].ulCKSCValue,
      MCU_CKSC_ALLMASK,
      Mcu_GpClockSetting->ulClkStbCount);
  } /* else No action is required */

  if ((E_OK == LucReturnValue)
      && (MCU_FOUTDIVC_STOPPED != (*((volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKDSAddr) & MCU_CLKD_SYNCMASK))
      && (MCU_FOUTDIVC_STOPPED != LpClockModuleSetting[LucIdx].ulCKDCValue))
  {
    /* Set external clock divider */
    *((volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKDCAddr) = LpClockModuleSetting[LucIdx].ulCKDCValue;
    /* Verify the divider setting */
    LucReturnValue = Mcu_CLKValidateSR(
      (volatile uint32 *)LpClockModuleSetting[LucIdx].pCLKDSAddr,
      MCU_FOUTDIVS_SYNC,
      MCU_CKSC_ALLMASK,
      Mcu_GpClockSetting->ulClkStbCount);
  } /* else No action is required */
  /* Return the value of setting external clock out result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif  /* MCU_INIT_CLOCK == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKStopMask
**
** Service ID         : None
**
** Description        : This service to set clock stop mask for specify
**                      whether to oscillate or stop each clock source in
**                      standby mode
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
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
** Global Variables   : Mcu_GpClockSetting, Mcu_GpClockHwInfo
**
** Function Invoked   : None
**
** Registers Used     : CLKKCPROT1, PLLSTPM, MOSCSTPM, HSOSCSTPM
**
** Reference ID       : MCU_DUD_ACT_077, MCU_DUD_ACT_077_CRT001
** Reference ID       : MCU_DUD_ACT_077_CRT002, MCU_DUD_ACT_077_REG001
** Reference ID       : MCU_DUD_ACT_077_REG002, MCU_DUD_ACT_077_REG003
** Reference ID       : MCU_DUD_ACT_077_REG004, MCU_DUD_ACT_077_REG005
***********************************************************************************************************************/
#if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, MCU_PRIVATE_CODE) Mcu_CLKStopMask(void)
{
  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  *Mcu_GpClockHwInfo->pPReg = MCU_CKSC_DISABLE_REG_PROTECT_VALUE;

  /* Check if PLLSTPM register need to be masked */
  if(NULL_PTR != Mcu_GpClockHwInfo->pPLLSTPMReg)
  {
    *Mcu_GpClockHwInfo->pPLLSTPMReg = Mcu_GpClockSetting->ulPLLSTPM;                                                    /* PRQA S 0404 # JV-01 */
  } /* else No action is required */

  *Mcu_GpClockHwInfo->pMainOscSTPMReg = Mcu_GpClockSetting->ulMOSCSTPM;                                                 /* PRQA S 0404 # JV-01 */
  *Mcu_GpClockHwInfo->pHSOscSTPMReg = Mcu_GpClockSetting->ulHSOSCSTPM;                                                  /* PRQA S 0404 # JV-01 */

  *Mcu_GpClockHwInfo->pPReg = MCU_CKSC_ENABLE_REG_PROTECT_VALUE;

  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  return;
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_MODE_TRANSITION_SUPPORT == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKShiftCpuSys
**
** Service ID         : None
**
** Description        : This service setting for clock gear up or gear down to change system clock source to PLL.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LenClkMode          - Enum for clock mode when shifting
**                      LucSrcIndex         - The index of clock source
**                      LenClkShift         - The Gear Up/Gear Down shifting type
**                      LpClockShiftSetting - The pointer to Clock Shift Setting
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : Mcu_CLKShiftWriteCR
**
** Registers Used     : CLKKCPROT0, CKSC0C, CKSC0S, CLKD0DIV, CLKD0STAT, CKSC2C
**                      CLKD2DIV, CLKD_PLLS, CKSC_CPUS, CLKKCPROT1, CLKD_PLLC
**
** Reference ID       : MCU_DUD_ACT_056, MCU_DUD_ACT_056_REG001
***********************************************************************************************************************/
#if (MCU_INIT_CLOCK == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKShiftCpuSys(Mcu_ClkModeType LenClkMode, uint8 LucSrcIndex,
Mcu_ClkShiftType LenClkShift, P2CONST(Mcu_ClockShiftSettingType, MCU_CONST, MCU_CONFIG_DATA) LpClockShiftSetting)
{
  Std_ReturnType LucReturnValue;
  uint8 LucIndex;
  uint8 LucNoOfRep;
  P2CONST(Mcu_ClockShiftRepetitionType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) LpClockShiftRepetition;
  LucReturnValue = E_OK;
  LucIndex = MCU_ZERO;

  if (MCU_CLK_GEAR_UP == LenClkShift)
  {
    LucNoOfRep = MCU_NUMBER_CLOCK_GEAR_UP_REPETITION;
  }
  else
  {
    LucNoOfRep = MCU_NUMBER_CLOCK_GEAR_DOWN_REPETITION;
  }

  /* Loop for all repetition */
  while ((E_OK == LucReturnValue) && (LucIndex < LucNoOfRep))
  {
    #if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
    if ((MCU_STANDBY_MODE == LenClkMode) && (MCU_ONE == LucIndex) && (MCU_CLK_GEAR_UP == LenClkShift))
    {
      /* Skip this repetition */
      LucIndex++;
    }
    else
    {
      if ((MCU_STANDBY_MODE == LenClkMode) &&
          ((LucNoOfRep - MCU_ONE) == LucIndex) && (MCU_CLK_GEAR_DOWN == LenClkShift))
      {
        /* Increase index for the last repetition */
        LucIndex++;                                                                                                     /* PRQA S 3383 # JV-01 */
      } /* else Do nothing */
    #endif /* MCU_MODE_TRANSITION_SUPPORT == STD_ON */  
      if (MCU_ZERO == LucSrcIndex)
      {
        /* PLL */
        LpClockShiftRepetition = LpClockShiftSetting->aaClockShiftRepetitionPLL[LenClkShift][LucIndex];
      }
      else if (MCU_ONE == LucSrcIndex)
      {
        /* SSCG */
        LpClockShiftRepetition = LpClockShiftSetting->aaClockShiftRepetitionSSCG[LenClkShift][LucIndex];
      }
      else
      {
        /* SSCG1 */
        LpClockShiftRepetition = LpClockShiftSetting->aaClockShiftRepetitionSSCG1[LenClkShift][LucIndex];
      }
      if (NULL_PTR != LpClockShiftRepetition->pCKSCCLKDCReg)
      {
        LucReturnValue = Mcu_CLKShiftWriteCR(
          LenClkMode,
          LpClockShiftRepetition->pCKSCCLKDCReg,
          LpClockShiftRepetition->pCKSSCLKDSReg,
          LpClockShiftRepetition->ulCKSCCLKDCValue,
          LpClockShiftRepetition->ulCKSSCLKDSValue,
          LpClockShiftRepetition->ulCKSSCLKDSMaskValue);
      } /* else No action is required */
      LucIndex++;                                                                                                       /* PRQA S 3383 # JV-01 */
    #if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
    }
    #endif /* MCU_MODE_TRANSITION_SUPPORT == STD_ON */
  }
  /* Return the value of setting shift clock result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif  /* MCU_INIT_CLOCK == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKWriteCR
**
** Service ID         : None
**
** Description        : This service to write clock control registers and
**                      and validate them after writing
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LpCLKCReg - The pointer to control register
**                      LpCLKSReg - The pointer to status register
**                      ulCRVal   - The written value to control register
**                      ulSRVal   - The expected value of status register
**                      ulSRMask  - The status register mask value
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : Mcu_CLKValidateSR
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_059, MCU_DUD_ACT_059_CRT001, MCU_DUD_ACT_059_CRT002
***********************************************************************************************************************/
#if (MCU_INIT_CLOCK == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKWriteCR(
  volatile CONSTP2CONST(uint32, TYPEDEF, REGSPACE) LpCLKCReg,
  volatile P2CONST(uint32, TYPEDEF, REGSPACE) LpCLKSReg,
  uint32 ulCRVal,
  uint32 ulSRVal,
  uint32 ulSRMask)
{
  Std_ReturnType LucReturnValue;
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */

  /* Disable interrupt to avoid access shared registers across APIs
   * and re-entrant API
   */
  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  /* Write control register */
  MCU_REG_WRITE_PROTECTION(                                                                                             /* PRQA S 0311 # JV-01 */
    Mcu_GpClockHwInfo->pPReg,
    MCU_CKSC_DISABLE_REG_PROTECT_VALUE,
    MCU_CKSC_ENABLE_REG_PROTECT_VALUE,
    LpCLKCReg, ulCRVal);
  /* Enable interrupts after write */
  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  /*
   * Confirm stability of the setting control register by checking
   * the reflected value of the corresponding status register
   */
  LucReturnValue = Mcu_CLKValidateSR(LpCLKSReg, ulSRVal, ulSRMask, Mcu_GpClockSetting->ulClkStbCount);

  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif  /* MCU_INIT_CLOCK == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKShiftWriteCR
**
** Service ID         : None
**
** Description        : This service to write clock control registers and validate them after writing
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LenClkMode - The clock mode type
**                      LpCLKCReg  - The pointer to control register
**                      LpCLKSReg  - The pointer to status register
**                      ulCRVal    - The written value to control register
**                      ulSRVal    - The expected value of status register
**                      ulSRMask   - The status register mask value

** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : Mcu_CLKValidateSR
**
** Registers Used     : CLKKCPROT1
**
** Reference ID       : MCU_DUD_ACT_104, MCU_DUD_ACT_104_CRT001, MCU_DUD_ACT_104_CRT002, MCU_DUD_ACT_104_REG001
***********************************************************************************************************************/
#if (MCU_INIT_CLOCK == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKShiftWriteCR(                                                      /* PRQA S 3006 # JV-01 */
  Mcu_ClkModeType LenClkMode,
  volatile CONSTP2CONST(uint32, TYPEDEF, REGSPACE) LpCLKCReg,
  volatile P2CONST(uint32, TYPEDEF, REGSPACE) LpCLKSReg,
  uint32 ulCRVal,
  uint32 ulSRVal,
  uint32 ulSRMask)
{
  Std_ReturnType LucReturnValue;
  uint32 LulCount;
  LucReturnValue = E_OK;

  if (MCU_CLOCK_MODE == LenClkMode)
  {
    /* Disable interrupt to avoid access shared registers across APIs
     * and re-entrant API
     */
    MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  } /* else No action is required */
  /* Write control register */
  MCU_REG_WRITE_PROTECTION(                                                                                             /* PRQA S 0311 # JV-01 */
    Mcu_GpClockHwInfo->pPReg,
    MCU_CKSC_DISABLE_REG_PROTECT_VALUE,
    MCU_CKSC_ENABLE_REG_PROTECT_VALUE,
    LpCLKCReg, ulCRVal);

  if (MCU_CLOCK_MODE == LenClkMode)
  {
    /* Enable interrupts after write */
    MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  } /* else No action is required */

  /* Wait for reflect the register */
  LulCount = MCU_CLOCK_REFLECT_WAIT_CNT_NUM;
  while (LulCount > MCU_LONG_WORD_ZERO)
  {
    LulCount--;
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  }

  /*
   * Confirm stability of the setting control register by checking
   * the reflected value of the corresponding status register
   */
  LucReturnValue = Mcu_CLKValidateSR(LpCLKSReg, ulSRVal, ulSRMask, Mcu_GpClockSetting->ulClkStbCount);

  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif  /* MCU_INIT_CLOCK == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKValidateSR
**
** Service ID         : None
**
** Description        : This service support to confirm status of target clock
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LpCLKSReg   - The pointer to status register
**                      LulRegValue - The expected value of status register
**                      LulRegMask  - The status register mask value
**                      LulMaxCount - The max count waiting for status register set
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_060
***********************************************************************************************************************/
#if (MCU_INIT_CLOCK == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKValidateSR(                                                        /* PRQA S 3006 # JV-01 */
  volatile P2CONST(uint32, TYPEDEF, REGSPACE) LpCLKSReg,
  const uint32 LulRegValue,
  const uint32 LulRegMask,
  const uint32 LulMaxCount)
{
  Std_ReturnType LucReturnValue;
  volatile uint32 LulCount;

  LucReturnValue = E_OK;

  /* Setting clock stable wait time */
  LulCount = LulMaxCount;
  /* Process to check status of target clock */
  while ((((*LpCLKSReg) & LulRegMask) != LulRegValue) && (LulCount > MCU_ZERO))                                         /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    LulCount--;                                                                                                         /* PRQA S 3384, 3387 # JV-01, JV-01 */
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  }
  if (((*LpCLKSReg) & LulRegMask) != LulRegValue)
  {
    LucReturnValue = E_NOT_OK;
  } /* else Clock status is as expectation */

  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif  /* MCU_INIT_CLOCK == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKSetPFD
**
** Service ID         : None
**
** Description        : This service support to set the modulation depth of SSCGC/SSCG1 domain clock
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpClockSetting, Mcu_GpClockHwInfo
**
** Function Invoked   : Mcu_CLKShiftWriteCR
**
** Registers Used     : SSCGC, SSCG1C
**
** Reference ID       : MCU_DUD_ACT_061
** Reference ID       : MCU_DUD_ACT_061_REG001
** Reference ID       : MCU_DUD_ACT_061_REG002
***********************************************************************************************************************/
#if (MCU_INIT_CLOCK == STD_ON)
#if ((MCU_SSCG_ENABLE == STD_ON)||(MCU_SSCG1_ENABLE == STD_ON))
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKSetPFD(void)
{
  Std_ReturnType LucReturnValue;
  #if (MCU_SSCG_ENABLE == STD_ON)
  uint32 LulSscgcValue;
  #endif
  #if (MCU_SSCG1_ENABLE == STD_ON)
  uint32 LulSscg1cValue;
  #endif
  LucReturnValue = E_OK;
  #if (MCU_SSCG_ENABLE == STD_ON)
  /* Check if SSCGC is used for the current clock setting */
  if(NULL_PTR != Mcu_GpClockHwInfo->pSSCGCReg)
  {
    /* Check if bit SSMODE1 is "1" */
    LulSscgcValue = *(Mcu_GpClockHwInfo->pSSCGCReg) & MCU_SSCG_SSMODE1_MASK;                                            /* PRQA S 0404 # JV-01 */
    if (MCU_LONG_WORD_ZERO != LulSscgcValue)
    {
      /* Set bit SSMODE1 to "0" */
      LucReturnValue = Mcu_CLKShiftWriteCR(                                                                             /* PRQA S 0404 # JV-01 */
        MCU_CLOCK_MODE,
        Mcu_GpClockHwInfo->pSSCGCReg,
        Mcu_GpClockHwInfo->pSSCGCReg,
        MCU_LONG_WORD_ZERO,
        MCU_LONG_WORD_ZERO,
        MCU_SSCG_SSMODE1_MASK);
    } /* else No action is required */
    if(E_OK == LucReturnValue)
    {
      /* Setting SSCGC register */
      LucReturnValue = Mcu_CLKShiftWriteCR(                                                                             /* PRQA S 0404 # JV-01 */
        MCU_CLOCK_MODE,
        Mcu_GpClockHwInfo->pSSCGCReg,
        Mcu_GpClockHwInfo->pSSCGCReg,
        Mcu_GpClockSetting->ulSSCGC,
        Mcu_GpClockSetting->ulSSCGC,
        MCU_CKSC_ALLMASK);
    } /* else No action is required */
  } /* else No action is required */
  #endif /* MCU_SSCG_ENABLE == STD_ON */

  /* Check if SSCG1C is used for the current clock setting */
  #if (MCU_SSCG1_ENABLE == STD_ON)
  if((E_OK == LucReturnValue) && (NULL_PTR != Mcu_GpClockHwInfo->pSSCG1CReg))
  {
    /* Check if bit SSMODE1 is "1" */
    LulSscg1cValue = *(Mcu_GpClockHwInfo->pSSCG1CReg) & MCU_SSCG_SSMODE1_MASK;                                          /* PRQA S 0404 # JV-01 */
    if (MCU_LONG_WORD_ZERO != LulSscg1cValue)
    {
      /* Set bit SSMODE1 to "0" */
      LucReturnValue = Mcu_CLKShiftWriteCR(                                                                             /* PRQA S 0404 # JV-01 */
        MCU_CLOCK_MODE,
        Mcu_GpClockHwInfo->pSSCG1CReg,
        Mcu_GpClockHwInfo->pSSCG1CReg,
        MCU_LONG_WORD_ZERO,
        MCU_LONG_WORD_ZERO,
        MCU_SSCG_SSMODE1_MASK);
    } /* else No action is required */
    if(E_OK == LucReturnValue)
    {
      /* Setting SSCG1C register */
      LucReturnValue = Mcu_CLKShiftWriteCR(                                                                             /* PRQA S 0404 # JV-01 */
        MCU_CLOCK_MODE,
        Mcu_GpClockHwInfo->pSSCG1CReg,
        Mcu_GpClockHwInfo->pSSCG1CReg,
        Mcu_GpClockSetting->ulSSCG1C,
        Mcu_GpClockSetting->ulSSCG1C,
        MCU_CKSC_ALLMASK);
    }
  } /* else No action is required */
  #endif /* MCU_SSCG1_ENABLE == STD_ON */

  /* Return the value of setting result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif  /*(MCU_SSCG_ENABLE == STD_ON)||(MCU_SSCG1_ENABLE == STD_ON) */
#endif  /* MCU_INIT_CLOCK == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKStartSubOsc
**
** Service ID         : None
**
** Description        : This service to start Sub OSC clock source
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpClockSetting, Mcu_GpClockHwInfo
**
** Function Invoked   : Mcu_CLKValidateSR, Mcu_CLKWriteCR
**
** Registers Used     : SOSCE, SOSCST, CLKKCPROT1
**
** Reference ID       : MCU_DUD_ACT_062, MCU_DUD_ACT_062_REG001, MCU_DUD_ACT_062_REG002, MCU_DUD_ACT_062_REG003
***********************************************************************************************************************/
#if (MCU_INIT_CLOCK == STD_ON)
#if (MCU_SOSC_SUPPORT == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKStartSubOsc(void)
{
  Std_ReturnType LucReturnValue;
  uint32 LulCount;
  uint8 LucSubOscStatus;
  LucReturnValue = E_OK;
  LulCount = Mcu_GpClockSetting->ulSubOscStbCount;

  /* Confirm that the Sub OSC is inactive */
  LucSubOscStatus = Mcu_CLKValidateSR(
    Mcu_GpClockHwInfo->pSubOscSReg,
    MCU_SOSCS_CLK_STABLE,
    MCU_SOSCS_CLK_STABLE,
    LulCount);
  if ((E_NOT_OK == LucSubOscStatus) && (MCU_TRUE == Mcu_GpClockSetting->blClkGenSupported))                             /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Disable interrupt to avoid access shared registers across APIs and re-entrant API */
    MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
    /* Release Register Access protection */
    *Mcu_GpClockHwInfo->pPReg = MCU_CKSC_DISABLE_REG_PROTECT_VALUE;
    /* Set the Sub OSC Stabilization Time Register */
    *Mcu_GpClockHwInfo->pSubOscSTReg = LulCount;
    /* Start the Sub OSC (SOSCE.SOSCENTRG = 1) */
    *Mcu_GpClockHwInfo->pSubOscEReg = MCU_SOSCE_ENABLE_TRIGGER;
    /* Hold Register Access protection */
    *Mcu_GpClockHwInfo->pPReg = MCU_CKSC_ENABLE_REG_PROTECT_VALUE;
    /* Enable interrupts after write */
    MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
    /* Check stability of Sub OSC */
    LucReturnValue = Mcu_CLKValidateSR(
      Mcu_GpClockHwInfo->pSubOscSReg,
      MCU_SOSCS_CLK_STABLE,
      MCU_SOSCS_CLK_STABLE,
      LulCount);
  } /* else No action is required */
  /* Return the value of setting result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_SOSC_SUPPORT == STD_ON */
#endif /* MCU_INIT_CLOCK == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKStopSubOsc
**
** Service ID         : None
**
** Description        : This service to stop Sub OSC clock source
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpClockSetting, Mcu_GpClockHwInfo
**
** Function Invoked   : Mcu_CLKValidateSR, Mcu_CLKWriteCR
**
** Registers Used     : SOSCE
**
** Reference ID       : MCU_DUD_ACT_063, MCU_DUD_ACT_063_REG001
***********************************************************************************************************************/
#if (MCU_INIT_CLOCK == STD_ON)
#if (MCU_SOSC_SUPPORT == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKStopSubOsc(void)
{
  Std_ReturnType LucReturnValue;
  uint32 LulCount;
  uint8 LucSubOscStatus;
  LucReturnValue = E_OK;
  LulCount = Mcu_GpClockSetting->ulSubOscStbCount;

  /* Confirm that the Sub OSC is active */
  LucSubOscStatus = Mcu_CLKValidateSR(
    Mcu_GpClockHwInfo->pSubOscSReg,
    MCU_SOSCS_CLK_STABLE,
    MCU_SOSCS_CLK_STABLE,
    LulCount);
  if (E_OK == LucSubOscStatus)
  {
    /* Disable Sub OSC */
    LucReturnValue = Mcu_CLKWriteCR(                                                                                    /* PRQA S 0404 # JV-01 */
      Mcu_GpClockHwInfo->pSubOscEReg,
      Mcu_GpClockHwInfo->pSubOscSReg,
      MCU_SOSCE_DISABLE_TRIGGER,
      MCU_SOSCS_STOPPED,
      MCU_CKSC_ALLMASK);
  } /* else No action is required */
  /* Return the value of setting result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_SOSC_SUPPORT == STD_ON */
#endif /* MCU_INIT_CLOCK == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKTrimming
**
** Service ID         : None
**
** Description        : This service to adjust the HS IntOSC clock source frequency (Frequency accuracy correction)
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpClockSetting, Mcu_GpClockHwInfo
**
** Function Invoked   : Mcu_CLKValidateSR, Mcu_CLKWriteCR, Mcu_CLKSetTrimmingCode
**
** Registers Used     : MOSCE, HSOSCTRMPRODC, HSOSCTRMEN, CLKKCPROT4
**
** Reference ID       : MCU_DUD_ACT_064, MCU_DUD_ACT_064_CRT001, MCU_DUD_ACT_064_CRT002, MCU_DUD_ACT_064_REG001, 
** Reference ID       : MCU_DUD_ACT_064_REG002, MCU_DUD_ACT_064_REG003, MCU_DUD_ACT_064_REG004
***********************************************************************************************************************/
#if (MCU_INIT_CLOCK == STD_ON)
#if (MCU_CLOCK_TRIMMING_SUPPORT == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKTrimming(void)                                                     /* PRQA S 3006 # JV-01 */
{
  Std_ReturnType LucReturnValue;
  uint32 LulCount;
  uint8 LucClkTrimmingStatus;
  LucReturnValue = E_OK;
  LucClkTrimmingStatus = E_NOT_OK;

  /* Check if Main OSC is used for the current clock setting */
  if (MCU_TRUE == Mcu_GpClockSetting->blMainOscUsed)                                                                    /* PRQA S 3416 # JV-01 */
  {
    /* Check if Main OSC is stable */
    LucReturnValue = Mcu_CLKValidateSR(                                                                                 /* PRQA S 0404 # JV-01 */
      Mcu_GpClockHwInfo->pMainOscSReg,
      MCU_MOSCS_CLK_STABLE,
      MCU_MOSCS_CLK_STABLE,
      Mcu_GpClockSetting->ulClkStbCount);
    if (E_NOT_OK == LucReturnValue)
    {
      /* Enable the Main OSC (MOSCE.MOSCENTRG = 1) */
      LucReturnValue = Mcu_CLKWriteCR(                                                                                  /* PRQA S 0404 # JV-01 */
        Mcu_GpClockHwInfo->pMainOscEReg,
        Mcu_GpClockHwInfo->pMainOscSReg,
        MCU_MOSCE_ENABLE_TRIGGER,
        MCU_MOSCS_CLK_STABLE,
        MCU_MOSCS_CLK_STABLE);
    } /* else No action is required */
  } /* else No action is required */
  /* If Main OSC is stable */
  if (E_OK == LucReturnValue)
  {
    /* Disable interrupt to avoid access shared registers across APIs and re-entrant API */
    MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
    /* Release Register Access protection */
    *Mcu_GpClockHwInfo->pPROT4Reg = MCU_CKSC_DISABLE_REG_PROTECT_VALUE;
    /* Set HSOSC Trimming Period (HSOSCTRMPRODC.PROD) */
    *Mcu_GpClockHwInfo->pHSOSCTRMPRODCReg = Mcu_GpClockSetting->ulHSOSCTRMPRODC;                                        /* PRQA S 0404 # JV-01 */
    /* Hold Register Access protection */
    *Mcu_GpClockHwInfo->pPROT4Reg = MCU_CKSC_ENABLE_REG_PROTECT_VALUE;
    /* Enable interrupts after write */
    MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
    /* Confirm stability of the setting HSOSCTRMPRODC.PROD */
    LucReturnValue = Mcu_CLKValidateSR(                                                                                 /* PRQA S 0404 # JV-01 */
      Mcu_GpClockHwInfo->pHSOSCTRMPRODCReg,
      Mcu_GpClockSetting->ulHSOSCTRMPRODC,
      MCU_HSOSCTRMPRODC_PROD_MASK,
      Mcu_GpClockSetting->ulClkStbCount);
  } /* else No action is required */

  if (E_OK == LucReturnValue)
  {
    /* Set the target clock stable wait time */
    LulCount = Mcu_GpClockSetting->ulClkStbCount;
    /* Loop for setting the trimming code in case the frequency accuracy correction is necessary */
    while ((E_NOT_OK == LucClkTrimmingStatus) && (LulCount > MCU_ZERO))
    {
      /* Disable interrupt to avoid access shared registers across APIs and re-entrant API */
      MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
      /* Release Register Access protection */
      *Mcu_GpClockHwInfo->pPROT4Reg = MCU_CKSC_DISABLE_REG_PROTECT_VALUE;
      /* Start the HSOSC Trimming Function (HSOSCTRMEN.ENTRG = 1) */
      *Mcu_GpClockHwInfo->pHSOSCTRMENReg = MCU_HSOSCTRMEN_ENABLE_TRIGGER;
      /* Hold Register Access protection */
      *Mcu_GpClockHwInfo->pPROT4Reg = MCU_CKSC_ENABLE_REG_PROTECT_VALUE;
      /* Enable interrupts after write */
      MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
      /* Verify the trimming status (HSOSCFRETRMS.TRMST = 0) */
      LucClkTrimmingStatus = Mcu_CLKValidateSR(                                                                         /* PRQA S 0404 # JV-01 */
        Mcu_GpClockHwInfo->pHSOSCFRETRMSReg,
        MCU_HSOSCFRETRMS_TRMST_END,
        MCU_HSOSCFRETRMS_TRMST_MASK,
        Mcu_GpClockSetting->ulClkStbCount);
      if (E_OK == LucClkTrimmingStatus)
      {
        /* Set the trimming code */
        LucClkTrimmingStatus = Mcu_CLKSetTrimmingCode();
      } /* else No action is required */
      LulCount--;
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */
    }
    /* Check if the trimming code is not set */
    if (E_NOT_OK == LucClkTrimmingStatus)
    {
      LucReturnValue = E_NOT_OK;
    } /* else No action is required */
  } /* else No action is required */

  /* Return the value of setting result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_CLOCK_TRIMMING_SUPPORT == STD_ON */
#endif /* MCU_INIT_CLOCK == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKSetTrimmingCode
**
** Service ID         : None
**
** Description        : This service calculate and set the trimming code data
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : HSOSCUSERTRMSET, CLKKCPROT4
**
** Reference ID       : MCU_DUD_ACT_065, MCU_DUD_ACT_065_REG001, MCU_DUD_ACT_065_REG002
***********************************************************************************************************************/
#if (MCU_INIT_CLOCK == STD_ON)
#if (MCU_CLOCK_TRIMMING_SUPPORT == STD_ON)
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE)Mcu_CLKSetTrimmingCode(void)
{
  Std_ReturnType LucReturnValue;
  uint32 LulTrimmingCounter;
  uint32 LulTrimmingFrequency;
  uint32 LulCurrentTrimmingCode;

  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */

  /* Get the Trimming counter value from HSOSCTRMCNT Register */
  LulTrimmingCounter = *(Mcu_GpClockHwInfo->pHSOSCTRMCNTReg) & MCU_HSOSCTRMCNT_CNT_MASK;                                /* PRQA S 0404 # JV-01 */

  /* Calculate the Trimming frequency by dividing Trimming counter and Trimming period */
  LulTrimmingFrequency = LulTrimmingCounter / Mcu_GpClockSetting->ulClkTrimmingPeriod;                                  /* PRQA S 2834 # JV-01 */

  /* Get the Trimming code value from HSOSCTRMCODE Register */
  LulCurrentTrimmingCode = *(Mcu_GpClockHwInfo->pHSOSCTRMCODEReg) & MCU_HSOSCTRMCODE_TCODE_MASK;                        /* PRQA S 0404 # JV-01 */

  /* Disable interrupt to avoid access shared registers across APIs and re-entrant API */
  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  /* Release Register Access protection */
  *Mcu_GpClockHwInfo->pPROT4Reg = MCU_CKSC_DISABLE_REG_PROTECT_VALUE;

  /* Check if the frequency accuracy correction is necessary (adjustment is required) */
  if (LulTrimmingFrequency > MCU_HSOSC_MAX_FREQUENCY_VALUE)
  {
    LucReturnValue = E_NOT_OK;
    /* Set new trimming code (HSOSCUSERTRMSET.TRMSET) */
    *Mcu_GpClockHwInfo->pHSOSCUSERTRMSETReg = LulCurrentTrimmingCode - 1UL;                                             /* PRQA S 3383 # JV-01 */
  }
  else if (LulTrimmingFrequency < MCU_HSOSC_MIN_FREQUENCY_VALUE)
  {
    LucReturnValue = E_NOT_OK;
    /* Set new trimming code (HSOSCUSERTRMSET.TRMSET) */
    *Mcu_GpClockHwInfo->pHSOSCUSERTRMSETReg = LulCurrentTrimmingCode + 1UL;                                             /* PRQA S 3383 # JV-01 */
  }
  else /* If the frequency is from min to max of the target frequency */
  {
    /* No adjustment is required */
    LucReturnValue = E_OK;
  }

  /* Hold Register Access protection */
  *Mcu_GpClockHwInfo->pPROT4Reg = MCU_CKSC_ENABLE_REG_PROTECT_VALUE;
  /* Enable interrupts after write */
  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  /* Return the value of setting result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* MCU_CLOCK_TRIMMING_SUPPORT == STD_ON */
#endif /* MCU_INIT_CLOCK == STD_ON */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKSetCMUClock
**
** Service ID         : None
**
** Description        : This service support to set CMU sub unit of GTM clock
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpClockSetting, Mcu_GpClockHwInfo
**
** Function Invoked   : Mcu_CLKSetCCMClock, Mcu_CLKValidateSR
**
** Registers Used     : CMU_CLK_EN, CMU_GCLK_NUM, CMU_GCLK_DEN, CMU_CLK_x_CTRL, CMU_ECLK_z_NUM, CMU_ECLK_z_DEN
**                      CMU_FXCLK_CTRL, CMU_CLK_CTRL
**
** Reference ID       : MCU_DUD_ACT_051, MCU_DUD_ACT_051_CRT001, MCU_DUD_ACT_051_CRT002
** Reference ID       : MCU_DUD_ACT_051_REG001, MCU_DUD_ACT_051_REG002, MCU_DUD_ACT_051_REG003
** Reference ID       : MCU_DUD_ACT_051_REG004, MCU_DUD_ACT_051_REG005, MCU_DUD_ACT_051_REG006
***********************************************************************************************************************/
#if ((MCU_GTM_SETTING == STD_ON) && (MCU_INIT_CLOCK == STD_ON))
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKSetCMUClock(void)
{
  /* Pointer to CMU configuration setting */
  P2CONST(Mcu_CMUSettingType, AUTOMATIC, MCU_CONFIG_DATA) LpCmuSetting;
  Std_ReturnType LucReturnValue;
  uint8 LucIndex;
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  LucIndex = MCU_ZERO;

  /* Disable interrupt to avoid access shared registers across APIs and re-entrant API */
  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  /* Set CCM sub unit clock */
  LucReturnValue = Mcu_CLKSetCCMClock();
  /* Check if CMU sub unit is used for the current clock setting */
  if ((E_OK == LucReturnValue) && (MCU_ZERO != Mcu_GpClockSetting->ucNoOfCcmCfg))                                       /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Disable all clock resolution signals by CMU_CLK_EN register */
    *Mcu_GpClockHwInfo->pCMUCLKENReg = MCU_CMUCLKEN_DISABLE_REG_TRIGGER;
    /* Verify setting */
    LucReturnValue = Mcu_CLKValidateSR(                                                                                 /* PRQA S 0404 # JV-01 */
      (volatile uint32 *)Mcu_GpClockHwInfo->pCMUCLKENReg,
      MCU_CMUCLKEN_DISABLE_VALUE,
      MCU_CMUCLKEN_MASK,
      Mcu_GpClockSetting->ulClkStbCount);

    if (E_OK == LucReturnValue)
    {
      /* Release Register Access Protection */
      *Mcu_GpClockHwInfo->pGTMCTRLReg &= ~MCU_LONG_WORD_ONE;                                                            /* PRQA S 0404 # JV-01 */
      /* Setting value of GTM_CLS_CLK_CFG register */
      *Mcu_GpClockHwInfo->pGTMCLSCLKCFGReg = Mcu_GpClockSetting->ulClsClkCfgValue;                                      /* PRQA S 0404 # JV-01 */
      /* Hold Register Access protection */
      *Mcu_GpClockHwInfo->pGTMCTRLReg |= MCU_LONG_WORD_ONE;                                                             /* PRQA S 0404 # JV-01 */
      /* Verify setting */
      LucReturnValue = Mcu_CLKValidateSR(                                                                               /* PRQA S 0404 # JV-01 */
        (volatile uint32 *)Mcu_GpClockHwInfo->pGTMCLSCLKCFGReg,
        Mcu_GpClockSetting->ulClsClkCfgValue,
        MCU_GTM_CLS_CLK_CFG_MASK,
        Mcu_GpClockSetting->ulClkStbCount);
    } /* else No action is required */

    /* Loop for all CMU configured registers */
    while ((E_OK == LucReturnValue) && (LucIndex < MCU_TOTAL_CMU_CONFIG))
    { 
      /* Get the pointer to CMU configuration structure */
      LpCmuSetting =
        ((P2CONST(Mcu_CMUSettingType, AUTOMATIC, MCU_CONFIG_DATA))(Mcu_GpClockSetting->pCmuSetting) + LucIndex);        /* PRQA S 0488 # JV-01 */
        /* Setting value of CMU configuration register */
        *((volatile uint32 *)LpCmuSetting->pCmuCfgRegAddr) = LpCmuSetting->ulCmuUnitRegValue;
        /* Verify setting */
        LucReturnValue = Mcu_CLKValidateSR(
          (volatile uint32 *)LpCmuSetting->pCmuCfgRegAddr,
          LpCmuSetting->ulCmuUnitRegValue,
          LpCmuSetting->ulCmuUnitRegMaskValue,
          Mcu_GpClockSetting->ulClkStbCount);
    LucIndex++;
    } /* else No action is required */

    /* Enable all clock resolution signals by CMU_CLK_EN register */
    *Mcu_GpClockHwInfo->pCMUCLKENReg = MCU_CMUCLKEN_ENABLE_REG_TRIGGER;
    if (E_OK == LucReturnValue)
    {
      /* Verify setting */
      LucReturnValue = Mcu_CLKValidateSR(                                                                               /* PRQA S 0404 # JV-01 */
        (volatile uint32 *)Mcu_GpClockHwInfo->pCMUCLKENReg,
        MCU_CMUCLKEN_ENABLE_VALUE,
        MCU_CMUCLKEN_MASK,
        Mcu_GpClockSetting->ulClkStbCount);
    } /* else No action is required */
  } /* else No action is required */
  /* Enable interrupts after write */
  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
  /* Return the value of setting result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif  /* (MCU_GTM_SETTING == STD_ON) && (MCU_INIT_CLOCK == STD_ON) */

/***********************************************************************************************************************
** Function Name      : Mcu_CLKSetCCMClock
**
** Service ID         : None
**
** Description        : This service support to set CCM sub unit of GTM clock
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : LucReturnValue
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpClockSetting, Mcu_GpClockHwInfo
**
** Function Invoked   : Mcu_CLKValidateSR
**
** Registers Used     : CCMi_PROT, CCMi_CMU_CLK_CFG, CCMi_CMU_FXCLK_CFG
**
** Reference ID       : MCU_DUD_ACT_052, MCU_DUD_ACT_052_REG001, MCU_DUD_ACT_052_REG002, MCU_DUD_ACT_052_REG003
***********************************************************************************************************************/
#if ((MCU_GTM_SETTING == STD_ON) && (MCU_INIT_CLOCK == STD_ON))
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_CLKSetCCMClock(void)
{
  /* Pointer to CCM configuration setting */
  P2CONST(Mcu_CCMSettingType, AUTOMATIC, MCU_CONFIG_DATA) LpCcmSetting;
  Std_ReturnType LucReturnValue;
  uint8 LucCount;
  LucReturnValue = E_OK;

  /* Get the pointer to CCM configuration structure */
  LpCcmSetting = (P2CONST(Mcu_CCMSettingType, MCU_CONST, MCU_CONFIG_DATA))(Mcu_GpClockSetting->pCcmSetting);

  /* Loop for all CCM configured registers */
  for (LucCount = MCU_ZERO; LucCount < Mcu_GpClockSetting->ucNoOfCcmCfg; LucCount++)                                    /* PRQA S 3416 # JV-01 */
  {
    if((E_OK == LucReturnValue) && (NULL_PTR != LpCcmSetting))
    {
      /* Release Register Access Protection by CCMi_PROT register */
      *((volatile uint32 *)LpCcmSetting[LucCount].pCCMnPROTRegs) = MCU_CCMPROT_DISABLE_REG_TRIGGER;

      /* Setting value of CCMi_CMU_CLK_CFG register */
      *((volatile uint32 *)LpCcmSetting[LucCount].pCCMnCLKCFGReg) = LpCcmSetting[LucCount].ulCcmClkCfgValue;
      /* Verify setting */
      LucReturnValue = Mcu_CLKValidateSR(
        (volatile uint32 *)LpCcmSetting[LucCount].pCCMnCLKCFGReg,
        LpCcmSetting[LucCount].ulCcmClkCfgValue,
        MCU_CCM_CMU_CLK_CFG_MASK,
        Mcu_GpClockSetting->ulClkStbCount);
      if ((E_OK == LucReturnValue) && (NULL_PTR != LpCcmSetting[LucCount].pCCMnFXCLKCFGReg))
      {
        /* Setting value of CCMi_CMU_FXCLK_CFG register */
        *((volatile uint32 *)LpCcmSetting[LucCount].pCCMnFXCLKCFGReg) = LpCcmSetting[LucCount].ulCcmFxClkCtrlValue;
        /* Verify setting */
        LucReturnValue = Mcu_CLKValidateSR(
          (volatile uint32 *)LpCcmSetting[LucCount].pCCMnFXCLKCFGReg,
          LpCcmSetting[LucCount].ulCcmFxClkCtrlValue,
          MCU_CCM_CMU_FXCLK_CFG_MASK,
          Mcu_GpClockSetting->ulClkStbCount);
      } /* else No action is required */

      /* Hold Register Access protection by CCMi_PROT register */
      *((volatile uint32 *)LpCcmSetting[LucCount].pCCMnPROTRegs) = MCU_CCMPROT_ENABLE_REG_TRIGGER;
    } /* else No action is required */
  }
  /* Return the value of setting result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif  /* (MCU_GTM_SETTING == STD_ON) && (MCU_INIT_CLOCK == STD_ON) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
