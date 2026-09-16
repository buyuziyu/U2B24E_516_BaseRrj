/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_LLDriver.c                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Internal functions implementation of ADC Driver Component                                                          */
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
 * 2.2.0: 31/12/2024 : As part of ARDAACJ-572, following changes are made:
 *                     1.Add preprocessor directive ADC_RESULT_DATA_TYPE to support DMA transfer 4-byte data
 *                     As part of ARDAACL-50888, following changes are made:
 *                     1.Update function Adc_ConfigureGroupForConversion to compliance STCYC metrics 
 * 2.1.3: 31/10/2024 : As part of QAC 9.5.0 support, following changes are made:
 *                     1.Updated QAC messages according to QAC analysis results.
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 * 2.1.1: 20/07/2024 : As part of ARDAACL-45823, following changes are made:
 *                     1.Update function Adc_ConfigureGroupForConversion to compliance STCYC metrics
 *                     As part of ARDAACL-50396, following changes are made:
 *                     1.Update to change ADC_MAX_SW_TRIGGER macro to global variable Adc_GucMaxSwTriggGroups
 *                     2.Update to change ADC_MAX_HW_TRIGGER macro to global variable
 *                       Adc_GucNoOfGroups - Adc_GucMaxSwTriggGroups
 *                     As part of ARDAACL-47005, following changes are made:
 *                     1.Add the condition of macro ADC_IP_C_ADCK in internal functions Adc_HwDeInit, Adc_HwInit
 *                     As part of U2Cx support, following changes are made:
 *                     1.Add the condition of macro ADC_IP_C_ADCK in internal functions Adc_EnableHwGroup and
 *                       Adc_DisableHwGroup
 * 2.0.1: 14/10/2023 : Support Autosar R22-11, fix acceptance findings
                       1. Change macro ADC_AR_R21_11_VERSION to ADC_AR_R22_11_VERSION support Autosar version.
                       2. Fix issue buffer out of range in Adc_HwInit, Adc_HwDeInit
                       3. Add message 3006 support Amendment 2
 * 2.0.0: 03/08/2023 : Add new QAC message PRQA (2:1006).
                       Add Kernel buffer into sequence of Adc_HwInit, Adc_HwDeInit to support multicore.
 *        11/06/2023 : Change macro ADC_AR_2111_VERSION to ADC_AR_R21_11_VERSION support Autosar version.
 * 1.5.0: 19/04/2023 : Added the ADC_AR_2111_VERSION compile switch area.
 * 1.4.5: 07/10/2022 : Fixed the variable enGroupConvMode to ucScanMode that was referenced in the conditional
 *                     expression in Adc_ConfigureGroupForConversion and Adc_HwStopScanGroup.
 *        15/09/2022 : Updated QAC messages according to QAC analysis results.
 *        12/09/2022 : Changed to use blLimitCheckEnabled instead of ulLimitCheckChannelMask1 and
 *                     ulLimitCheckChannelMask2 to check enablement in the following functions.
 *                       Adc_ErrIsr, Adc_CheckError
 *                     Replaced the empty else blocks, not from else if, with comments.
 *                     Fixed comments about 'No action required' and 'end of'.
 *                     Separated each bit of ucGroupSettings into independent variables.
 *                     Removed static variable Adc_GaaOperationMask.
 * 1.4.4: 31/08/2022 : Fixed typos in comments due to review findings.
 *        24/08/2022 : Updated information in function header comments.
 *        25/07/2022 : Changed Adc_SetStatus to static function.
 *                     Updated PRQA comments based on the result of static analysis.
 *                     Fixed inconsistency due to compile switch in variable definition and use in
 *                     Adc_CheckAndCopyResultData and Adc_DmaIsr.
 *                     Fixed the handling SG unit status in Adc_HwStopScanGroup.
 *                     Updated Re-entrancy, Global Variables, Functions invoked, Registers Used, and Reference IDs in
 *                     function header comments.
 *        12/07/2022 : Changed to call Adc_HwStopScanGroup even if the group is implicitly stopped in the functions
 *                     Adc_ChannelCompleteMode, Adc_GroupCompleteMode and Adc_DmaIsr.
 *                     Added support for T&H sampling stop to the function Adc_HwStopScanGroup, Adc_DisableHwGroup,
 *                     Adc_HwStopGroupConversion, and Adc_HwDisableHardwareTrigger.
 *                     Added the argument LblForced to the function Adc_HwStopScanGroup.
 *                     Moved status checks and transitions, DEM error reporting, and critical section containing them
 *                     in the function Adc_HwStopGroupConversion from the function Adc_StopGroupConversion.
 *                     Adjusted the condition to set the scan count for multicycle in the function
 *                     Adc_ConfigureGroupForConversion.
 *                     If the group is for T&H, the result is not discarded even when error is detected in function
 *                     Adc_CheckAndCopyResultData and Adc_DmaIsr.
 *        20/06/2022 : Unified the trigger control of Adc_EnableHwGroup and Adc_DisableHwGroup in U2Bx to U2Ax.
 *        15/06/2022 : Replaced the calls to init/de-init functions with Adc_AdcInit/Adc_AdcDeInit in
 *                     Adc_HwInit/Adc_HwDeInit for U2Ax.
 *                     Updated functions Adc_ConfigureGroupForConversion/Adc_DisableDetection to
 *                     change to use ADC_SELF_DIAG_WIRE_BRK_MODE1 with the same value instead of
 *                     ADC_SELF_DIAG_WIRE_BRK even for E2x.
 *                     Updated functions Adc_HwInit/Adc_HwDeInit to change the error interrupt control condition
 *                     from by ulErrImrMask to by blInterruptErr.
 *                     Updated function Adc_ConfigureGroupForConversion to change scan group start procedure to
 *                     the same as U2Bx when the requested group is T&H in U2Ax.
 * 1.4.3: 25/05/2022 : Updated QAC messages for U2Bx.
 *                     Fixed not to call Adc_TrackHoldEnable in Adc_ConfigureGroupForConversion when not T&H in U2Bx.
 *        18/05/2022 : Moved calls to Adc_TrackHoldInit and Adc_SetWaitTime in Adc_HwInit to Adc_AdcInit.
 *                     Moved calls to Adc_TrackHoldDeInit and Adc_DeInitWaitTime in Adc_HwDeInit to Adc_AdcDeInit.
 *                     Changed ucSgUnitIndex of HW unit data to ucSgUnitOffset of HW unit config in U2Bx.
 *                     Changed the filename of the SchM_Adc header to macro for multi-instances.
 *                     Fixed the typos in comments.
 *        15/04/2022 : Updated Global Variables in function header comment.
 *                     Changed the condition of whether to use ADC trigger selection to pointer check.
 * 1.4.2: 10/03/2022 : Updated internal function Adc_HwStartGroupConversion,
 *                     - Added the initialization of sample and channel completion counters
 *                       before pushing the requested group.
 *                     - Change to determine whether to disable DMA transfer by configuration of the current group.
 * 1.4.1: 25/11/2021 : Use ADCXnADHALTR to stop SG if only one SG is used in ADCK.
 *        24/11/2021 : Changed the condition of compile switch to support ADCK.
 * 1.4.0: 02/11/2021 : Added compile switches to remove unused static functions in some configurations.
 *                     Added compile switches to remove unused local variables in some configurations.
 * 1.3.2: 10/09/2021 : Changed init/de-init to call the ECM interrupt configuration even with U2Ax.
 *        09/09/2021 : Added synchronization after handling each bus group.
 *        06/09/2021 : Changed to Adc_Mapping.h from Adc_MemMap.h
 *        03/09/2021 : Added PRQA comment based on the result of static analysis.
 *                     Added copying supplementary information when PWM-Diag.
 *        30/08/2021 : Added processing related to PWM-Diag feature.
 *        25/08/2021 : Fixed typo of macro ADC_ADCX_ODCR_INIT_VALUE.
 * 1.3.1: 17/07/2021 : Added the CONST qualifier to pointers that have not changed their reference.
 *                     Removed unnecessary register initialization.
 *        16/07/2021 : Simplified conditional branching in the internal function Adc_StateTransition.
 *                     Changed the protection range of the internal functions Adc_DmaIsr and Adc_PollingReadGroup.
 *        13/07/2021 : Added the internal function Adc_DisableDetection.
 *                     Removed the redundant conditional branches.
 *        12/07/2021 : Redesigned the functions Adc_ErrIsr, Adc_ParityErrIsr, Adc_CheckError and related functions.
 *                     Added the internal functions Adc_CheckParity and Adc_ReportError.
 *                     Changed the argument of Adc_HwStopScanGroup to LddGroup.
 *                     Added SG stop for groups that are implicitly stopped in the function Adc_DmaIsr.
 *                     Removed the functions Adc_GetLastSgConvGroup, Adc_IdErrIntCheck.
 *                     Removed the global variables Adc_GblDataAvailable, Adc_GblErrIntStatus.
 *                     Removed the redundant conditions of compile switches.
 *                     Integrated the ADC_DET_REPORT_ERROR_NOFLAG and ADC_DET_REPORT_ERROR into ADC_DET_RUNTIME_ERROR.
 *                     Removed the argument LucChannelCount of function Adc_PollingReadGroup.
 *                     ADC_ENABLE_START_STOP_GROUP_API to functions and processes that handle queues.
 *        07/07/2021 : Added QAC message 9.5.0
 *                     Changed comment format to 120 columns
 *                     Changed violation tag from START/END
 *        16/06/2021 : Updated by nesting ADC register structures.
 *                     Add casts to calculation processing.
 *        01/06/2021 : Changed to the appropriate memory classes and pointer classes.
 *        24/05/2021 : Removed unnecessary include header.
 *                     Moved "Adc_DmaIsr()" from "Adc_sDMAC_LLDriver.c" to Adc_LLDriver.c
 *                     Moved the function declaration of the internal function from the header to the source code.
 *        07/04/2021 : Changed to comply with coding rules.
 * 1.3.0: 19/12/2020 : Change macro ADC_TIMEOUT_COUNT to macro ADC_DMA_TIMEOUT_COUNT.
 *        11/12/2020 : Function Adc_HwStopScanGroup,
 *                     update macro ADC_TIMEOUT_COUNT to macro
 *                     ADC_AD_TIMER_TIMEOUT_COUNT
 *        09/12/2020 : Update function Adc_HwInit() to add
 *                     conditional compilation. Invoke function Adc_PicInit()
 *                     in case ADC_NUM_OF_CONVERT_TRIGGER_CONFIG_REG is not zero.
 *        06/12/2020 : Update function Adc_HwInit() to invoke function
 *                     Adc_PicInit()
 *        05/12/2020 : Report DEM error ADC_E_TIMEOUT in
 *                     Adc_HwStartGroupConversion, Adc_HwEnableHardwareTrigger,
 *                     Adc_HwDisableHardwareTrigger, Adc_PollingReadGroup
 *                     in case cannot stop scan group or DMA channel
 *        15/10/2020 : Set ucSamplesCompleted to ADC_BYTE_ONE if requested group
 *                     is single access in Adc_ChannelCompleteMode.
 *        12/10/2020 : Add condition to check if ucSamplesCompleted is equal to
 *                     ucStreamingSamples before get the address of pBuffer for
 *                     group popped from queue in Adc_ConfigureGroupForConversion
 *        17/09/2020 : Update function Adc_HwStopScanGroup to correct
 *                     AdcHwUnit when checking AdcHwUnit to disable
 *                     Track and Hold feature
 *        04/09/2020 : Update function Adc_IntDisableEnableChannel to support
 *                     disable the same physical channel ID in group
 * 1.2.0: 25/08/2020 : Release
 *                     Add QAC 9.3.1 comment.
 *                     Update critical section in Adc_HwStartGroupConversion,
 *                     Adc_PollingReadGroup, Adc_Isr, Adc_ErrIsr, Adc_ParityErrIsr
 *                     Add function Adc_IdErrIntCheck to check ID error when
 *                     Error interrupt is enable.
 *                     Add condition to check invalid group in Adc_ErrIsr
 *                     Remove redundant QAC 9.3.1 comment
 * 1.1.3: 06/07/2020 : - Remove array Adc_GaaCurrentConvGroup
 *                     - Update function Adc_GetLastSgConvGroup to get the
 *                       conversion group by Adc_GpSgUnitRamData
 * 1.1.2: 02/07/2020 : - Update Adc_GddCurrentConvGroup to Adc_GaaCurrentConvGroup
 *                     - Remove parameter LucHwUnitIndex in function
 *                       Adc_PopFromQueue
 *                     - Add new function Adc_GetLastSgConvGroup to get the
 *                       last SG conversion group
 * 1.1.1: 30/06/2020 : - Remove search loop in Adc_PopFromQueue.
 *                     - Update initial value of Adc_GaaCurrentConvGroup from
 *                       ADC_FALSE to ADC_VAL_BYTE_INIT
 * 1.1.0: 19/06/2020 : Release
 * 1.0.7: 18/06/2020 : Change blWaitTimeEnabled to ucWaitTimeIndex
 * 1.0.6: 22/05/2020 : - Invoke function Adc_TrackHoldDisable after calling
 *                     Adc_HwStopScanGroup in function Adc_HwStopGroupConversion.
 *                     - Update if T&H is enable for the requested group,
 *                     only write 1 to bit TRGMD in register ADCJnSGCR.
 * 1.0.5: 12/05/2020 : Update macro DET_REPORT_ERROR to ADC_DET_REPORT_ERROR,
 *                     DET_REPORT_ERROR_NOFLAG to ADC_DET_REPORT_ERROR_NOFLAG.
 * 1.0.4: 25/04/2020 : As per new requirement, remove Adc_ClearInternalBuffer().
 * 1.0.3: 22/04/2020 : As per Redmine #267724: Report DEM ADC_E_ID_FAILURE when
 *                     ID error is detected in Adc_ErrIsr.
 * 1.0.2: 20/04/2020 : Redmine #266165: Add ADC_E_BUSY
 *                     error report in Adc_HwStartGroupConversion and
 *                     Adc_HwEnableHardwareTrigger when start/enable
 *                     channel group conversion from different hardware
 *                     scan group.
 * 1.0.1: 09/04/2020 : Add const qualifier for arguments of internal functions
 *                     that are never changed
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for version check macro definitions and type definitions */
#include "Adc.h"

/* Included for RAM variable declarations */
#include "Adc_Ram.h"
/* Included for the declaration of internal function prototypes */
#include "Adc_LLDriver.h"
#include "Adc_sDMAC_LLDriver.h"
#include ADC_HWIP_LLDRIVER_H_FILE

#if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
     (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
/* Included for the declaration of DET report function */
#include "Det.h"
#endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
           (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */

#if (ADC_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Adc.h"
#endif /* (ADC_CRITICAL_SECTION_PROTECTION == STD_ON) */

/* Included for declaration of the function DEM_REPORT_ERROR() */
#include "Dem.h"
/* Included for the macro declaration of supervisor mode(SV) write enabled Registers IMR & ICxxx */
#include "rh850_Types.h"

/* Include for the Kernel multi core support */
#if (ADC_MULTI_CORE_SUPPORT == STD_ON)
#include "Adc_Kernel.h"
#include "Os.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define ADC_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION_VALUE
#define ADC_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION_VALUE
#define ADC_LLDRIVER_C_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ADC_LLDRIVER_C_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION_VALUE
#define ADC_LLDRIVER_C_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ADC_LLDRIVER_AR_RELEASE_MAJOR_VERSION != ADC_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Adc_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (ADC_LLDRIVER_AR_RELEASE_MINOR_VERSION != ADC_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Adc_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (ADC_LLDRIVER_AR_RELEASE_REVISION_VERSION != ADC_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Adc_LLDriver.c : Mismatch in Release Patch Version"
#endif

#if (ADC_LLDRIVER_SW_MAJOR_VERSION != ADC_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Adc_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (ADC_LLDRIVER_SW_MINOR_VERSION != ADC_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Adc_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : MISRA C:2012 Rule-11.4, CERTCCM INT36, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
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
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : MISRA C:2012 Rule-8.7, CERTCCM DCL19, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1532)    : The function '%1s' is only referenced in one translation unit - but not the one in which it  */
/*                       is defined.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.7, CERTCCM DCL19, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This macro identifier is following AUTOSAR standard rule  (Symbolic Name or Published        */
/*                       Macro's name), so this is accepted                                                           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:2755)    : Analysis time of function '%1s' has exceeded the configured maximum: '%2sms'. Dataflow       */
/*                       analysis continues with the next function.                                                   */
/* Rule                : MISRA C:2012 CMN-0.4, CERTCCM CMN-0.4, CWE Rule CMN-0.4                                      */
/* JV-01 Justification : This is depends on Hardware Specification for each module                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-476, CWE-465, CWE-737, CWE-690                                   */
/* JV-01 Justification : This is accepted, due to the implementation following hardware specification.                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2824)    : Possible: Arithmetic operation on NULL pointer.                                              */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-468, CWE-476, CWE-465, CWE-737                                   */
/* JV-01 Justification : This is accepted, due to the implementation following hardware specification.                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2844)    : Possible: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127,       */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : It is specific for device register accessing and confirmed has no issue in software behavior.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : MISRA C:2012 Dir-4.1, CERTCCM MSC07, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/* Message (2:2934)    : Possible: Computing an invalid pointer value.                                                */
/* Rule                : CERTCCM EXP08, ARR30, ARR37, ARR38, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125,    */
/*                       CWE-126, CWE-127, CWE-129, CWE-131, CWE-469, CWE-823, CWE-465, CWE-633, CWE-740              */
/* JV-01 Justification : This message prevents existing of an out-of-range pointer                                    */
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
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used following AUTOSAR standard rule. It is accepted.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3464)    : Argument to macro '%s' contains a side effect that will be evaluated more than once.         */
/* Rule                : CERTCCM PRE31                                                                                */
/* JV-01 Justification : This message is only emitted for expressions expanded from argument tokens written out at    */
/*                       the top level, that did not themselves originate from a macro expansion.                     */
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
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"

STATIC FUNC(boolean, ADC_PRIVATE_CODE) Adc_HwStopScanGroup(const Adc_GroupType LddGroup, const boolean LblForced);
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_ConfigureGroupForConversion(const Adc_GroupType LddGroup);
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_SetStatus(const Adc_GroupType LddGroup, const Adc_StatusType LenStatusType);

#if (ADC_HW_TRIGGER_API == STD_ON)
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_EnableHwGroup(const Adc_GroupType LddGroup);
STATIC FUNC(boolean, ADC_PRIVATE_CODE) Adc_DisableHwGroup(const Adc_GroupType LddGroup);
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
     ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_PushToQueue(const Adc_GroupType LddGroup);
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_SearchAndDelete(const Adc_GroupType LddGroup);
#endif

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
#if ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON) || (ADC_ENABLE_DMA_MODE == STD_ON))
STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_CallGroupNotify(const Adc_GroupType LddGroup);
#endif
#endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
     ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
STATIC FUNC(Adc_GroupType, ADC_CODE_FAST) Adc_PopFromQueue(const uint8 LucCurrentSgUnitIndex);
#endif

#if ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON))
STATIC FUNC(boolean, ADC_CODE_FAST) Adc_CheckAndCopyResultData(const Adc_GroupType LddGroup,
  const uint8 LucChannelCount);
STATIC FUNC(boolean, ADC_CODE_FAST) Adc_GroupCompleteMode(const Adc_GroupType LddGroup, const uint8 LucHwUnitIndex);

#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
STATIC FUNC(boolean, ADC_CODE_FAST) Adc_ChannelCompleteMode(const Adc_GroupType LddGroup, const uint8 LucHwUnitIndex);
#endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
#endif /* ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON)) */

#if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
STATIC FUNC(void, ADC_CODE_FAST) Adc_DisableConvertInterrupt(const uint8 LucHwUnitIndex, const uint8 LucSgUnitIndex);
STATIC FUNC(void, ADC_CODE_FAST) Adc_EnableConvertInterrupt(const uint8 LucHwUnitIndex, const uint8 LucSgUnitIndex);
#endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

#if (ADC_ENABLE_PARITY_ERR == STD_ON)
#if ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON) || (ADC_ENABLE_DMA_MODE == STD_ON))
STATIC FUNC(boolean, ADC_CODE_FAST) Adc_CheckParity(const Adc_GroupType LddGroup);
#endif
#endif

#if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
     (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON) || \
     (ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
#if ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON) || (ADC_ENABLE_DMA_MODE == STD_ON))
STATIC FUNC(boolean, ADC_CODE_FAST) Adc_CheckError(const Adc_GroupType LddGroup);
#endif
#endif

#if ((ADC_ENABLE_ERR == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON))
#if ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON) || (ADC_ENABLE_DMA_MODE == STD_ON))
STATIC FUNC(void, ADC_CODE_FAST) Adc_ReportError(const Adc_GroupType LddGroup);
#endif
#endif

#if ((ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON) || \
     (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) || (ADC_ENABLE_WIRE_BRK == STD_ON))
STATIC FUNC(void, ADC_CODE_FAST) Adc_DisableDetection(const Adc_GroupType LddGroup);
#endif

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name        : Adc_HwStartGroupConversion
**
** Service ID           : NA
**
** Description          : This internal function shall start the conversion of
**                        all channels of the requested ADC Channel group.
**                        Depending on the group configuration single-shot or
**                        continuous conversion is started.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpSgUnitRamData, Adc_GpGroupRamData,
**                        Adc_GpHwUnitConfig, Adc_GucMaxSwTriggGroups
**
** Functions invoked    : ADC_ENTER_CRITICAL_SECTION, Adc_ConfigureGroupForConversion, Adc_DisableHwGroup,
**                        Adc_DmaDisable, Adc_PushToQueue, Adc_HwStopScanGroup, ADC_EXIT_CRITICAL_SECTION,
**                        ADC_DEM_REPORT_ERROR, ADC_DET_RUNTIME_ERROR
**
** Registers Used       : ADCXnSGSRx
**
** Reference ID         : ADC_DUD_ACT_020, ADC_DUD_ACT_020_CRT001, ADC_DUD_ACT_020_CRT002,
** Reference ID         : ADC_DUD_ACT_020_ERR001, ADC_DUD_ACT_020_ERR008, ADC_DUD_ACT_020_GBL001,
** Reference ID         : ADC_DUD_ACT_020_GBL002, ADC_DUD_ACT_020_GBL005, ADC_DUD_ACT_020_GBL006,
** Reference ID         : ADC_DUD_ACT_020_GBL007, ADC_DUD_ACT_020_GBL008, ADC_DUD_ACT_020_GBL009,
** Reference ID         : ADC_DUD_ACT_020_GBL012, ADC_DUD_ACT_020_GBL013, ADC_DUD_ACT_020_GBL014,
** Reference ID         : ADC_DUD_ACT_020_GBL015
***********************************************************************************************************************/
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_HwStartGroupConversion(const Adc_GroupType LddGroup)                                   /* PRQA S 1532 # JV-01 */
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  P2VAR(volatile Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  uint8 LucSgUnitId;
  /* Pointer definition to store the base address of the ADC registers */
  volatile P2CONST(Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  volatile P2CONST(Adc_SGRegType, AUTOMATIC, REGSPACE) LpSGRegisters;
  #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)))
  /* Local variable to store the current conversion group ID */
  Adc_GroupType LddCurrentGroup;
  #endif
  /* Local variable to store the hardware unit number */
  uint8 LucHwUnitIndex;
  uint8 LucSgUnitIndex;
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  boolean LblDetErrFlag;
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  boolean LblHwTimedOut;
  #if (ADC_ENABLE_DMA_MODE == STD_ON)
  boolean LblDmaTimedOut;
  #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */

  /* Initialize the error flag */
  LblHwTimedOut = ADC_FALSE;
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */

  /* Get the pointer to the group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the SG unit to which the channel group is mapped */
  LucSgUnitIndex = LpGroup->ucSgUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  /* Read the Hardware Unit to which the group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;
  LucSgUnitId = Adc_GpSgUnitConfig[LucSgUnitIndex].ucSgUnitId;                                                          /* PRQA S 2824 # JV-01 */
  /* Initialize SG RAM data to a local pointer */
  LpSgUnitData = &Adc_GpSgUnitRamData[LucSgUnitIndex];                                                                  /* PRQA S 2824 # JV-01 */
  /* Read the group data pointer */
  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */

  /* Enter the critical section protection */
  ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

  #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)))
  /* Get the current group under conversion */
  LddCurrentGroup = LpSgUnitData->ddCurrentConvGroup;                                                                   /* PRQA S 2814 # JV-01 */
  #endif
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  /* Initialize error status flag */
  LblDetErrFlag = ADC_FALSE;

  /* Check if it can be restarted for the same group */
  if ((LddCurrentGroup == LddGroup) && (ADC_IDLE != LpGroupData->enGroupStatus) &&                                      /* PRQA S 2814 # JV-01 */
      ((ADC_STREAM_COMPLETED != LpGroupData->enGroupStatus) || (ADC_FALSE == LpGroup->blImplicitlyStopped)))
  {
    LblDetErrFlag = ADC_TRUE;
  }
  else
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  {
    /* Read the base configuration address of the hardware unit */
    LpAdcRegisters = Adc_GpHwUnitConfig[LucHwUnitIndex].pHwUnitBaseAddress;                                             /* PRQA S 2824 # JV-01 */
    LpSGRegisters = &LpAdcRegisters->aaADCXnSG[LucSgUnitId];                                                            /* PRQA S 2814, 2934 # JV-01, JV-01 */

    /* Check if the requested hardware unit is busy */
    if ((ADC_BYTE_ZERO == LpSGRegisters->ucADCXnSGSRx) && (ADC_FALSE == LpSgUnitData->blSgUnitStatus))                  /* PRQA S 2844 # JV-01 */
    {
      /* Set the SG unit status to busy */
      LpSgUnitData->blSgUnitStatus = ADC_TRUE;
      /* Reset the number of completed sample to zero. */
      LpGroupData->ucSamplesCompleted = ADC_COUNT_BYTE_INIT;
      /* Reset the number of completed channels to zero. */
      LpGroupData->ucChannelsCompleted = ADC_COUNT_BYTE_INIT;
      /* Configure the requested group for conversion */
      Adc_ConfigureGroupForConversion(LddGroup);
    }
    else
    {
      #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
      /* Check if the current group priority is less than requested */
      if (LpSgUnitData->ddCurrentPriority < LpGroup->ddGroupPriority)
      {
        #if ((ADC_HW_TRIGGER_API == STD_ON))
        /* Check if the ongoing lower priority group is HW triggered */
        if (LddCurrentGroup >= Adc_GucMaxSwTriggGroups)
        {
          /* Disable the lower ongoing HW triggered group */
          LblHwTimedOut = Adc_DisableHwGroup(LddCurrentGroup);
          if (ADC_FALSE == LblHwTimedOut)
          {
            /* Set the SG unit status to busy */
            LpSgUnitData->blSgUnitStatus = ADC_TRUE;
            /* Reset the number of completed sample to zero. */
            LpGroupData->ucSamplesCompleted = ADC_COUNT_BYTE_INIT;
            /* Reset the number of completed channels to zero. */
            LpGroupData->ucChannelsCompleted = ADC_COUNT_BYTE_INIT;
            /* Start conversion of requested higher SW triggered group */
            Adc_ConfigureGroupForConversion(LddGroup);
          } /* else: No action required */
        } /* end of if (LddCurrentGroup >= Adc_GucMaxSwTriggGroups) */
        else
        #endif /* ((ADC_HW_TRIGGER_API == STD_ON)) */
        {
          /* Check if the queue is full */
          if (ADC_QUEUE_FULL != LpSgUnitData->ucQueueStatus)
          {
            /* Disable ongoing DMA of current group */
            #if (ADC_ENABLE_DMA_MODE == STD_ON)
            /* Disable DMA transfer */
            if (ADC_TRUE == Adc_GpGroupConfig[LddCurrentGroup].blEnableDmaTransfer)                                     /* PRQA S 2824 # JV-01 */
            {
              LblDmaTimedOut = Adc_DmaDisable(LddCurrentGroup);
            }
            else
            {
              LblDmaTimedOut = ADC_FALSE;
            }
            #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
            /*
             * Stop conversion of SG unit in which requested group is mapped
             * by changing mode to Multicycle scan mode and no of scan as one
             */
            LblHwTimedOut = Adc_HwStopScanGroup(LddCurrentGroup, ADC_TRUE);
            if (ADC_FALSE == LblHwTimedOut)
            {
              #if (ADC_ENABLE_DMA_MODE == STD_ON)
              if (ADC_TRUE == LblDmaTimedOut)
              {
                LblHwTimedOut = ADC_TRUE;
              }
              else
              #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
              {
                /* Push the current conversion group into queue */
                Adc_PushToQueue(LddCurrentGroup);
                /* Set the SG unit status to busy */
                LpSgUnitData->blSgUnitStatus = ADC_TRUE;
                /* Reset the number of completed sample to zero. */
                LpGroupData->ucSamplesCompleted = ADC_COUNT_BYTE_INIT;
                /* Reset the number of completed channels to zero. */
                LpGroupData->ucChannelsCompleted = ADC_COUNT_BYTE_INIT;
                /* Configure the requested group for conversion */
                Adc_ConfigureGroupForConversion(LddGroup);
              }
            } /* end of if (ADC_FALSE == LblHwTimedOut) */
              /* else: No action required */
          } /* end of if (ADC_QUEUE_FULL != LpSgUnitData->ucQueueStatus) */
          else
          {
            #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
                (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
            LblDetErrFlag = ADC_TRUE;
            #endif
          }
        }
      } /* end of if (LpSgUnitData->ddCurrentPriority < LpGroup->ddGroupPriority) */
      else
      #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
      {
        #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
        if (ADC_QUEUE_FULL != LpSgUnitData->ucQueueStatus)
        {
          /* Reset the number of completed sample to zero. */
          LpGroupData->ucSamplesCompleted = ADC_COUNT_BYTE_INIT;
          /* Reset the number of completed channels to zero. */
          LpGroupData->ucChannelsCompleted = ADC_COUNT_BYTE_INIT;
          /* Push the requested group into the first come first serve mechanism queue */
          Adc_PushToQueue(LddGroup);
        }
        else
        #endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */
        {
          #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
               (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
          LblDetErrFlag = ADC_TRUE;
          #endif
        }
      }
    }
  }

  /* Exit the critical section protection */
  ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  /* Report Error to DET if error occurs */
  if (ADC_TRUE == LblDetErrFlag)
  {
    ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_START_GROUP_CONVERSION_SID, ADC_E_BUSY);
  }
  else
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  {
    #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
    /* Report timed out error to Dem if timeout occurs */
    if (ADC_TRUE == LblHwTimedOut)
    {
      /* Reporting to DEM when timeout cause by hardware error */
      ADC_DEM_REPORT_ERROR(ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
    } /* else: No action required */
    #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
  }
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_HwEnableHardwareTrigger
**
** Service ID           : NA
**
** Description          : This internal function will enable the hardware
**                        trigger for the requested ADC Channel group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpSgUnitRamData, Adc_GpHwUnitConfig,
**                        Adc_GucMaxSwTriggGroups
**
** Functions invoked    : ADC_ENTER_CRITICAL_SECTION, Adc_EnableHwGroup, Adc_DmaDisable, Adc_PushToQueue,
**                        Adc_DisableHwGroup, Adc_HwStopScanGroup, ADC_DET_RUNTIME_ERROR, ADC_EXIT_CRITICAL_SECTION,
**                        ADC_DEM_REPORT_ERROR
**
** Registers Used       : ADCXnSGSRx
**
** Reference ID         : ADC_DUD_ACT_021, ADC_DUD_ACT_021_CRT001, ADC_DUD_ACT_021_CRT006,
** Reference ID         : ADC_DUD_ACT_021_ERR002, ADC_DUD_ACT_021_ERR006
***********************************************************************************************************************/
#if (ADC_HW_TRIGGER_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_HwEnableHardwareTrigger(const Adc_GroupType LddGroup)                                  /* PRQA S 1532 # JV-01 */
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  /* Pointer to the hardware unit user base configuration address */
  volatile P2CONST(Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  volatile P2CONST(Adc_SGRegType, AUTOMATIC, REGSPACE) LpSGRegisters;
  volatile P2CONST(Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  /* Local variable to store the hardware unit number */
  uint8 LucHwUnitIndex;
  uint8 LucSgUnitId;
  uint8 LucSgUnitIndex;
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  boolean LblDetErrFlag;
  #endif
  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  /* Local variable to store the current conversion group ID */
  Adc_GroupType LddCurrentGroup;
  boolean LblHwTimedOut;
  #if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && (ADC_ENABLE_DMA_MODE == STD_ON))
  boolean LblDmaTimedOut;
  #endif /* ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && (ADC_ENABLE_DMA_MODE == STD_ON)) */
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */

  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  LblDetErrFlag = ADC_FALSE;
  #endif
  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  /* Initialize the error flag */
  LblHwTimedOut = ADC_FALSE;
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */

  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the SG unit to which the channel group is mapped */
  LucSgUnitIndex = LpGroup->ucSgUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  /* Read the Hardware Unit to which the group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;
  /* Get the SG unit Id */
  LucSgUnitId = Adc_GpSgUnitConfig[LucSgUnitIndex].ucSgUnitId;                                                          /* PRQA S 2824 # JV-01 */
  /* Get the pointer to SG runtime data */
  LpSgUnitData = &Adc_GpSgUnitRamData[LucSgUnitIndex];                                                                  /* PRQA S 2824 # JV-01 */
  /* Get the base register address of the hardware unit */
  LpAdcRegisters = Adc_GpHwUnitConfig[LucHwUnitIndex].pHwUnitBaseAddress;                                               /* PRQA S 2824 # JV-01 */
  /* Get the SG register address */
  LpSGRegisters = &LpAdcRegisters->aaADCXnSG[LucSgUnitId];                                                              /* PRQA S 2814, 2934 # JV-01, JV-01 */
  /* Enter the critical section protection */
  ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

  if ((ADC_BYTE_ZERO == LpSGRegisters->ucADCXnSGSRx) && (ADC_FALSE == LpSgUnitData->blSgUnitStatus))                    /* PRQA S 2814, 2844 # JV-01, JV-01 */
  {
    Adc_EnableHwGroup(LddGroup);
  }
  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  else if (LpSgUnitData->ddCurrentPriority < LpGroup->ddGroupPriority)
  {
    /* Fetch the group id of the current conversion group */
    LddCurrentGroup = LpSgUnitData->ddCurrentConvGroup;

    #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    /* Check if the current ongoing conversion is of SW triggered group */
    if (LddCurrentGroup < Adc_GucMaxSwTriggGroups)
    {
      /* Check if the queue is full */
      if (ADC_QUEUE_FULL != LpSgUnitData->ucQueueStatus)
      {
        #if (ADC_ENABLE_DMA_MODE == STD_ON)
        if (ADC_TRUE == Adc_GpGroupConfig[LddCurrentGroup].blEnableDmaTransfer)                                         /* PRQA S 2824 # JV-01 */
        {
          LblDmaTimedOut = Adc_DmaDisable(LddCurrentGroup);
        }
        else
        {
          LblDmaTimedOut = ADC_FALSE;
        }
        #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
        /*
         * Stop conversion of SG unit in which requested group is mapped
         * by changing mode to Multicycle scan mode and no of scan as one
         */
        LblHwTimedOut = Adc_HwStopScanGroup(LddCurrentGroup, ADC_TRUE);
        if (ADC_FALSE == LblHwTimedOut)
        {
          #if (ADC_ENABLE_DMA_MODE == STD_ON)
          if (ADC_TRUE == LblDmaTimedOut)
          {
            /* Merge the timed out flags */
            LblHwTimedOut = ADC_TRUE;
          }
          else
          #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
          {
            /* Push the current conversion group into queue */
            Adc_PushToQueue(LddCurrentGroup);
            /* Configure the requested group for conversion */
            Adc_EnableHwGroup(LddGroup);
          }
        } /* end of if (ADC_FALSE == LblHwTimedOut) */
          /* else: No action required */
      } /* end of if (ADC_QUEUE_FULL != LpSgUnitData->ucQueueStatus) */
      else
      {
        #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
        LblDetErrFlag = ADC_TRUE;
        #endif
      }
    } /* end of if (LddCurrentGroup < Adc_GucMaxSwTriggGroups) */
    else
    #endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */
    {
      LblHwTimedOut = Adc_DisableHwGroup(LddCurrentGroup);
      if (ADC_FALSE == LblHwTimedOut)
      {
        Adc_EnableHwGroup(LddGroup);
      } /* else: No action required */
    }
  } /* end of else if (LpSgUnitData->ddCurrentPriority < LpGroup->ddGroupPriority) */
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
  else
  {
    #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
         (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
    LblDetErrFlag = ADC_TRUE;
    #endif
  }

  /* Exit the critical section protection */
  ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  /* Report Error to DET if error occurs */
  if (ADC_TRUE == LblDetErrFlag)
  {
    ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_HARDWARE_TRIGGER_SID, ADC_E_BUSY);
  }
  else
  #endif
  {
    #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
    /* Report an error to Dem if some timeouts occur */
    if (ADC_TRUE == LblHwTimedOut)
    {
      /* Reporting to DEM when timeout cause by hardware error */
      ADC_DEM_REPORT_ERROR(ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
    } /* else: No action required */
    #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
  }
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_HW_TRIGGER_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_HwDisableHardwareTrigger
**
** Service ID           : NA
**
** Description          : This internal function will disables the hardware
**                        trigger for the requested ADC Channel group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : The ADC Driver must be Initialized first by invoking
**                        API Adc_Init().
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpSgUnitRamData, Adc_GaaHwUnitData
**
** Functions invoked    : Adc_DisableHwGroup, Adc_ConfigureGroupForConversion, Adc_PopFromQueue, ADC_DEM_REPORT_ERROR,
**                        ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_022, ADC_DUD_ACT_022_CRT001, ADC_DUD_ACT_022_CRT002, ADC_DUD_ACT_022_ERR001
***********************************************************************************************************************/
#if (ADC_HW_TRIGGER_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_HwDisableHardwareTrigger(const Adc_GroupType LddGroup)                                 /* PRQA S 1532 # JV-01 */
{
  #if (ADC_TRACK_AND_HOLD == STD_ON)
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2CONST(volatile Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  P2VAR(volatile Adc_HwUnitDataType, AUTOMATIC, ADC_VAR_NO_INIT) LpHwUnitData;
  uint8 LucSgUnitId;
  #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */
  #if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
       ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  Adc_GroupType LddNextGroup;
  /* Local variable to store SG unit index */
  uint8 LucSgUnitIndex;
  #endif
  boolean LblHwTimedOut;

  /* Exit the critical section protection */
  ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

  #if (ADC_TRACK_AND_HOLD == STD_ON)
  /* Get the SG unit configuration */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[Adc_GpGroupConfig[LddGroup].ucSgUnitIndex];                                      /* PRQA S 2824 # JV-01 */
  /* Get the pointer to the runtime data of the SG unit to which the requested group belongs */
  LpSgUnitData = &Adc_GpSgUnitRamData[Adc_GpGroupConfig[LddGroup].ucSgUnitIndex];                                       /* PRQA S 2824 # JV-01 */
  /* Get the pointer to the runtime data of the HW unit to which the requested group belongs */
  LpHwUnitData = &Adc_GaaHwUnitData[Adc_GpGroupConfig[LddGroup].ucHwUnitIndex];                                         /* PRQA S 2934 # JV-01 */
  /* Get the SG unit ID to which the requested group is configured */
  LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                             /* PRQA S 2814 # JV-01 */

  /* Check if the requested group is for T&H */
  if (ADC_TH_DISABLED != Adc_GpGroupConfig[LddGroup].ucTrackAndHoldGroup)
  {
    /* Check if other T&H group is not active in the same SG unit */
    if ((ADC_FALSE == LpSgUnitData->blSgUnitStatus) ||                                                                  /* PRQA S 2814 # JV-01 */
        (LpSgUnitData->ddCurrentConvGroup == LddGroup) ||
        (ADC_TH_DISABLED == Adc_GpGroupConfig[LpSgUnitData->ddCurrentConvGroup].ucTrackAndHoldGroup))
    {
      /* Update T&H status to disable T&H of this SG unit */
      LpHwUnitData->ucTrackHoldStatus &= (uint8)~(1U << LucSgUnitId);                                                   /* PRQA S 2844 # JV-01 */
    } /* else: No action required */
  } /* else: No action required */
  #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

  /* Disable the ongoing HW triggered group */
  LblHwTimedOut = Adc_DisableHwGroup(LddGroup);

  #if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
       ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
  if (ADC_FALSE == LblHwTimedOut)
  {
    /* Get the pointer to the group configuration */
    LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                             /* PRQA S 2824 # JV-01 */
    /* Get the SG unit index to which group is mapped */
    LucSgUnitIndex = LpGroup->ucSgUnitIndex;                                                                            /* PRQA S 2814 # JV-01 */
    /* Fetch the next group for conversion if the queue is not empty */
    LddNextGroup = Adc_PopFromQueue(LucSgUnitIndex);
    if (ADC_INVALID_GROUP != LddNextGroup)
    {
      Adc_ConfigureGroupForConversion(LddNextGroup);
    } /* else: No action required */
  } /* else: No action required */
  #endif /*
          * ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
          *  ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
          */

  /* Exit the critical section protection */
  ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

  /* Report an error to Dem if timeout occurs */
  if (ADC_TRUE == LblHwTimedOut)
  {
    /* Reporting to DEM when timeout cause by hardware error */
    ADC_DEM_REPORT_ERROR(ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
  } /* else: No action required */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_HW_TRIGGER_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_PushToQueue
**
** Service ID           : NA
**
** Description          : This internal function shall add the requested group
**                        into Queue.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant for different SG units, Non-Reentrant for the same SG unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpSgUnitRamData, Adc_GpGroupRamData
**
** Functions invoked    : None
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_023, ADC_DUD_ACT_023_GBL001, ADC_DUD_ACT_023_GBL002,
** Reference ID         : ADC_DUD_ACT_023_GBL003, ADC_DUD_ACT_023_GBL004, ADC_DUD_ACT_023_GBL005,
** Reference ID         : ADC_DUD_ACT_023_GBL006
***********************************************************************************************************************/
#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
     ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_PushToQueue(const Adc_GroupType LddGroup)
{
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  P2VAR(volatile Adc_GroupType, AUTOMATIC, ADC_VAR_NO_INIT) LpQueue;
  uint8 LucSgUnitIndex;
  uint8 LucLoopCount;
  uint8 LucQueueSize;
  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  uint8 LucPriority;
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */

  /* Read for hardware unit and the Priority Queue */
  LucSgUnitIndex = Adc_GpGroupConfig[LddGroup].ucSgUnitIndex;                                                           /* PRQA S 2824 # JV-01 */
  /* Initialize HW RAM data to a local pointer */
  LpSgUnitData = &Adc_GpSgUnitRamData[LucSgUnitIndex];                                                                  /* PRQA S 2824 # JV-01 */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LucSgUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  LpQueue = LpSgUnitConfig->pQueue;                                                                                     /* PRQA S 2814 # JV-01 */

  /* Check if the Pointer Priority Queue is NULL */
  if (NULL_PTR != LpQueue)
  {
    /* Read the configured priority queue size */
    LucQueueSize = LpSgUnitConfig->ucAdcSgQueueSize;

    /* Read the queue counter */
    LucLoopCount = LpSgUnitData->ucQueueCounter;                                                                        /* PRQA S 2814 # JV-01 */

    if (ADC_FALSE == Adc_GpGroupRamData[LddGroup].blGrpPresent)                                                         /* PRQA S 2824 # JV-01 */
    {
      /* Set the flag indicating that group is present in the queue */
      Adc_GpGroupRamData[LddGroup].blGrpPresent = ADC_TRUE;

      #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
      /* Store the group into queue if queue is empty */
      if (ADC_QUEUE_EMPTY == LpSgUnitData->ucQueueStatus)
      #else /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
      /* Store the group into queue if queue is empty or not full */
      if ((ADC_QUEUE_EMPTY == LpSgUnitData->ucQueueStatus) || (ADC_QUEUE_FILLED == LpSgUnitData->ucQueueStatus))
      #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
      {
        /* Store the group into queue */
        LpQueue[LucLoopCount] = LddGroup;
        /* Increment the queue counter */
        LpSgUnitData->ucQueueCounter++;                                                                                 /* PRQA S 3383, 3387 # JV-01, JV-01 */
      }
      else /* Queue not empty */
      {
        #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
        /* Read the priority of the requested group */
        LucPriority = Adc_GpGroupConfig[LddGroup].ddGroupPriority;
        /* Place the requested group in the queue based on this priority */
        while ((ADC_COUNT_BYTE_INIT != LucLoopCount) &&
               (Adc_GpGroupConfig[LpQueue[LucLoopCount - ADC_BYTE_ONE]].ddGroupPriority >= LucPriority) &&
               (LddGroup != LpSgUnitData->ddCurrentConvGroup))
        {
          LpQueue[LucLoopCount] = LpQueue[LucLoopCount - ADC_BYTE_ONE];
          LucLoopCount--;
        }
        LpQueue[LucLoopCount] = LddGroup;

        /* Increment the queue counter */
        LpSgUnitData->ucQueueCounter++;                                                                                 /* PRQA S 3383, 3387 # JV-01, JV-01 */
        #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
      }
    } /* end of if (ADC_FALSE == Adc_GpGroupRamData[LddGroup].blGrpPresent) */
      /* else: No action required */

    /* Check whether the Queue is Full */
    if (LpSgUnitData->ucQueueCounter >= LucQueueSize)
    {
      /* Set queue status as full */
      LpSgUnitData->ucQueueStatus = ADC_QUEUE_FULL;
    }
    else
    {
      /* Set queue status as filled */
      LpSgUnitData->ucQueueStatus = ADC_QUEUE_FILLED;
    }
  } /* end of if (NULL_PTR != LpQueue) */
  /* Pointer Priority Queue is NULL */
  else
  {
    /* Set queue status as empty */
    LpSgUnitData->ucQueueStatus = ADC_QUEUE_EMPTY;
  }
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /*
        * ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
        *  ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
        */

/***********************************************************************************************************************
** Function Name        : Adc_PopFromQueue
**
** Service ID           : NA
**
** Description          : This internal function shall returns the highest
**                        priority group that was pushed in the Queue.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant for different SG units, Non-Reentrant for the same SG unit
**
** Input Parameters     : LucCurrentSgUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : Adc_GroupType
**
** Preconditions        : None
**
** Global Variables     : Adc_GpSgUnitRamData, Adc_GpGroupRamData, Adc_GpSgUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_024, ADC_DUD_ACT_024_GBL001, ADC_DUD_ACT_024_GBL003,
** Reference ID         : ADC_DUD_ACT_024_GBL006, ADC_DUD_ACT_024_GBL004, ADC_DUD_ACT_024_GBL005
***********************************************************************************************************************/
#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
     ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(Adc_GroupType, ADC_CODE_FAST) Adc_PopFromQueue(const uint8 LucCurrentSgUnitIndex)
{
  P2VAR(volatile Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  P2VAR(volatile Adc_GroupType, AUTOMATIC, ADC_VAR_NO_INIT) LpQueue;                                                    /* PRQA S 3678 # JV-01 */
  Adc_GroupType LddGroup;
  uint32 LulQueueCounter;
  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE)
  uint32 LulLoopCount;
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_NONE) */

  /* Initialize HW RAM data to a local pointer */
  LpSgUnitData = &Adc_GpSgUnitRamData[LucCurrentSgUnitIndex];                                                           /* PRQA S 2824 # JV-01 */
  if (ADC_QUEUE_EMPTY != LpSgUnitData->ucQueueStatus)                                                                   /* PRQA S 2814 # JV-01 */
  {
    LpSgUnitData->blSgUnitStatus = ADC_TRUE;
    /* Get the pointer to SG unit queue */
    LpQueue = Adc_GpSgUnitConfig[LucCurrentSgUnitIndex].pQueue;                                                         /* PRQA S 2824 # JV-01 */

    /* Read the highest priority task from the queue */
    LulQueueCounter = (uint32)LpSgUnitData->ucQueueCounter;

    #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
    /* Get the Group which is of next priority level */
    LddGroup = LpQueue[LulQueueCounter - 1UL];                                                                          /* PRQA S 2824, 3383 # JV-01, JV-01 */
    #else /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
    /* Initialize the loop counter to zero */
    LulLoopCount = 0UL;

    /* Decrement the queue counter value by one */
    LulQueueCounter--;                                                                                                  /* PRQA S 3383 # JV-01 */
    /* Get the group which was requested just after the immediate conversion completed group */
    LddGroup = LpQueue[0];                                                                                              /* PRQA S 2824 # JV-01 */
    do
    {
      /* Re-arrange the queue based on which channel group was requested first */
      LpQueue[LulLoopCount] = LpQueue[LulLoopCount + 1UL];                                                              /* PRQA S 3383 # JV-01 */
      /* Increment the loop count */
      LulLoopCount++;                                                                                                   /* PRQA S 3383 # JV-01 */
    } while (LulLoopCount < LulQueueCounter);
    #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */

    /* Check whether the Queue is not empty */
    if (ADC_COUNT_BYTE_INIT < LpSgUnitData->ucQueueCounter)
    {
      /* Update the queue counter */
      LpSgUnitData->ucQueueCounter--;                                                                                   /* PRQA S 3384, 3387 # JV-01, JV-01 */
      if (ADC_COUNT_BYTE_INIT == LpSgUnitData->ucQueueCounter)
      {
        /* Set queue status as empty */
        LpSgUnitData->ucQueueStatus = ADC_QUEUE_EMPTY;
      }
      else
      {
        /* Set queue status as filled */
        LpSgUnitData->ucQueueStatus = ADC_QUEUE_FILLED;
      }
    } /* end of if (ADC_COUNT_BYTE_INIT < LpSgUnitData->ucQueueCounter) */
      /* else: No action required */
    /* Clear the flag indicating group is no longer in queue */
    Adc_GpGroupRamData[LddGroup].blGrpPresent = ADC_FALSE;                                                              /* PRQA S 2824 # JV-01 */
  } /* end of if (ADC_QUEUE_EMPTY != LpSgUnitData->ucQueueStatus) */
  else
  {
    LddGroup = ADC_INVALID_GROUP;
  }
  return LddGroup;
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#endif /*
        * ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
        *  ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
        */

/***********************************************************************************************************************
** Function Name        : Adc_SearchAndDelete
**
** Service ID           : NA
**
** Description          : This internal function shall be called by the
**                        Adc_StopGroupConversion API to search if the requested
**                        group is in the queue and remove it from the queue.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different SG units, Non-Reentrant for the same SG unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitRamData, Adc_GpSgUnitConfig, Adc_GpGroupRamData
**
** Functions invoked    : None
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_025, ADC_DUD_ACT_025_GBL001, ADC_DUD_ACT_025_GBL002, ADC_DUD_ACT_025_GBL003
***********************************************************************************************************************/
#if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
     ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_SearchAndDelete(const Adc_GroupType LddGroup)
{
  P2VAR(volatile Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2VAR(volatile Adc_GroupType, AUTOMATIC, ADC_VAR_NO_INIT) LpQueue;
  uint32 LulQueueSize;
  uint32 LulLoopCount;

  /* Initialize the loop count to zero */
  LulLoopCount = 0UL;
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Initialize HW RAM data to a local pointer */
  LpSgUnitData = &Adc_GpSgUnitRamData[LpGroup->ucSgUnitIndex];                                                          /* PRQA S 2814, 2824 # JV-01, JV-01 */
  /* Get the base address of the Queue */
  LpQueue = Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex].pQueue;                                                          /* PRQA S 2824 # JV-01 */
  /* Read the configured priority queue size */
  LulQueueSize = (uint32)LpSgUnitData->ucQueueCounter;                                                                  /* PRQA S 2814 # JV-01 */
  /*
   * Find the requested group in the queue and re-arrange the
   * queue by deleting the requested group.
   */
  while (LulLoopCount < LulQueueSize)
  {
    if (LddGroup == LpQueue[LulLoopCount])                                                                              /* PRQA S 2824 # JV-01 */
    {
      /* Decrement the queue size by one */
      LulQueueSize--;
      /* Update the queue counter value */
      LpSgUnitData->ucQueueCounter = (uint8)LulQueueSize;
      /* Re-arrange the queue after deleting the requested group */
      while (LulLoopCount < LulQueueSize)
      {
        LpQueue[LulLoopCount] = LpQueue[LulLoopCount + 1UL];
        LulLoopCount++;
      }
      /* To exit from the while loop */
      LulLoopCount = LulQueueSize;
    } /* end of if (LddGroup == LpQueue[LulLoopCount]) */
      /* else: No action required */
    LulLoopCount++;                                                                                                     /* PRQA S 3383 # JV-01 */
  } /* end of while (LulLoopCount < LulQueueSize) */
  /* Clear the flag indicating group removed from the queue */
  Adc_GpGroupRamData[LddGroup].blGrpPresent = ADC_FALSE;                                                                /* PRQA S 2824 # JV-01 */
  /* Update the queue status */
  if (ADC_COUNT_BYTE_INIT == LpSgUnitData->ucQueueCounter)
  {
    /* Set queue status as empty */
    LpSgUnitData->ucQueueStatus = ADC_QUEUE_EMPTY;
  }
  else
  {
    /* Set queue status as filled */
    LpSgUnitData->ucQueueStatus = ADC_QUEUE_FILLED;
  }
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /*
        * ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
        *  ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
        */

/***********************************************************************************************************************
** Function Name        : Adc_StateTransition
**
** Service ID           : NA
**
** Description          : This internal function shall translate the group state
**                        after the call of the API Adc_ReadGroup or
**                        Adc_GetStreamLastPointer.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupRamData, Adc_GpGroupConfig
**
** Functions invoked    : Adc_SetStatus
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_026
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_StateTransition(const Adc_GroupType LddGroup)                                          /* PRQA S 1532 # JV-01 */
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  volatile P2CONST(Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;

  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */

  /* Check if the group status is stream completed */
  if (ADC_STREAM_COMPLETED == LpGroupData->enGroupStatus)                                                               /* PRQA S 2814 # JV-01 */
  {
    if (ADC_TRUE == LpGroup->blImplicitlyStopped)                                                                       /* PRQA S 2814 # JV-01 */
    {
      /* Set the group status to idle */
      Adc_SetStatus(LddGroup, ADC_IDLE);
    }
    else
    {
      /* Set the Group status to busy */
      Adc_SetStatus(LddGroup, ADC_BUSY);
    }
  }
  else if (ADC_COMPLETED == LpGroupData->enGroupStatus)
  {
    /* Set the Group status to busy */
    Adc_SetStatus(LddGroup, ADC_BUSY);
  }
  else
  {
    /* No action required */
  }
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_CheckAndCopyResultData
**
** Service ID           : NA
**
** Description          : This internal function shall check result of converted data.
**                        When there is valid data in data register, converted data is copied to internal buffer.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW unit, Non-Reentrant for same HW unit
**
** Input Parameters     : LddGroup, LucChannelCount
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : boolean
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpGroupRamData, Adc_GpHwUnitConfig, Adc_GpChannelToGroup
**
** Functions invoked    : Adc_PwmDiagReadData, Adc_CheckError, Adc_CheckParity
**
** Registers Used       : ADCXnDIRj, ADCXnVCRj
**
** Reference ID         : ADC_DUD_ACT_027, ADC_DUD_ACT_027_GBL004, ADC_DUD_ACT_027_GBL005
***********************************************************************************************************************/
#if ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON))

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(boolean, ADC_CODE_FAST) Adc_CheckAndCopyResultData(const Adc_GroupType LddGroup,
  const uint8 LucChannelCount)
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  /* Pointer to the hardware unit user base configuration address */
  volatile P2CONST(Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;                                      /* PRQA S 3678 # JV-01 */
  P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) LpBuffer;                                                                     /* PRQA S 3432 # JV-01 */
  uint32 LulLoopCount;
  uint32 LulNumChannel;
  uint32 LulConvertedValue;
  uint32 LulBufferOffset;
  uint8 LucHwUnitIndex;
  /* Local variable to store the actual channel index */
  uint8 LucChannelIndex;
  #if (ADC_ENABLE_ID_ERR == STD_ON)
  uint8 LucErrorVirCh;
  uint8 LucPhysCh;
  #if (ADC_ENABLE_PWM_DIAG == STD_ON)
  uint8 LucChannelToGroupIndex;
  #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
  #endif /* (ADC_ENABLE_ID_ERR == STD_ON) */
  #if (((ADC_ENABLE_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || \
       (ADC_ENABLE_LIMIT_CHECK == STD_ON) || (ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON))
  /* Error flag */
  boolean LblErrorFlag;
  #endif
  /* Read data available flag */
  boolean LblDataAvailable;

  /* Read the hardware unit of the group */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Read the Hardware Unit to which the group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  /* Read the group's runtime data pointer */
  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */
  /* Get the pointer to hardware unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the base register address of the hardware unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */
  /* Initialize read data available flag */
  LblDataAvailable = ADC_FALSE;

  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  /* Check if group is configured in Suspend_resume mode */
  if (ADC_GROUP_REPL_SUSPEND_RESUME == LpGroup->enGroupReplacement)
  {
    /* Get latest channel index */
    LulNumChannel = (uint32)LucChannelCount;
  }
  else
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
  {
    /* Get last channel index */
    LulNumChannel = (uint32)LucChannelCount - 1UL;                                                                      /* PRQA S 3383, 3384 # JV-01, JV-01 */
  }
  /* Get last channel conversion result */
  LucChannelIndex = (uint8)(LpGroup->ucStartVirChPtr + (uint8)LulNumChannel);

  #if (ADC_ENABLE_PWM_DIAG == STD_ON)
  if (ADC_TRUE == LpGroup->blPwmDiag)
  {
    /* Read the result data and information from register for PWM-Diag */
    LulConvertedValue = Adc_PwmDiagReadData(LddGroup);
  }
  else
  #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
  {
    /* Read the result data and information from register indicated by the channel number */
    LulConvertedValue = LpAdcRegisters->aaADCXnDIR[LucChannelIndex];                                                    /* PRQA S 2814, 2844 # JV-01, JV-01 */
  }

  /* Check if the conversion is completed */
  if (ADC_RESULT_AVAILABLE == (LulConvertedValue & ADC_RESULT_AVAILABLE))
  {
    /* Set the read data available flag */
    LblDataAvailable = ADC_TRUE;

    #if (((ADC_ENABLE_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || \
         (ADC_ENABLE_LIMIT_CHECK == STD_ON) || (ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
    /* Get and check the error status */
    LblErrorFlag = Adc_CheckError(LddGroup);
    if (ADC_TRUE == LblErrorFlag)
    {
      /* Clear the read data available flag */
      LblDataAvailable = ADC_FALSE;
    } /* else: No action required */
    /* The DIR register must be read, as it must be discarded even if an error occurs */
    #endif
    /* Load the current group's current channel buffer pointer */
    LpBuffer = LpGroupData->pBuffer;                                                                                    /* PRQA S 2814 # JV-01 */

    /* Read the offset of the buffer for normal mode */
    LulBufferOffset = LulNumChannel;
    #if (ADC_ENABLE_STREAMING == STD_ON)
    /* Check if the group is configured in streaming access mode */
    if (ADC_ACCESS_MODE_STREAMING == LpGroup->enGroupAccessMode)
    {
      /* Read the offset for the buffer pointer based on number of channels and completed samples. */
      LulBufferOffset *= (uint32)LpGroup->ddNumberofSamples;                                                            /* PRQA S 3383, 3384 # JV-01, JV-01 */
    } /* else: No action required */
    #endif /* (ADC_ENABLE_STREAMING == STD_ON) */

    #if (ADC_ENABLE_ID_ERR == STD_ON)
    /* Initialize the Id error channel */
    LucErrorVirCh = ADC_INVALID_CHANNELID;
    /* Check if Id error has occurred */
    if (ADC_ADCX_DIR_IDEF_ERR == (LulConvertedValue & ADC_ADCX_DIR_IDEF))
    {
      /* Store the current channel index to the Id error channel */
      LucErrorVirCh = LucChannelIndex;
      /* Clear the result buffer */
      LpBuffer[LulBufferOffset] = ADC_RESULT_BUF_INIT;                                                                  /* PRQA S 2824, 2844 # JV-01, JV-01 */
    }
    else
    #endif /* (ADC_ENABLE_ID_ERR == STD_ON) */
    {
      /* Copy the converted value to the result buffer */
      #if (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS)
      LpBuffer[LulBufferOffset] = (uint16)(LulConvertedValue & ADC_ADCX_DIR_DR);                                        /* PRQA S 2824, 2844 # JV-01, JV-01 */
      #else
      LpBuffer[LulBufferOffset] = LulConvertedValue;                                                                    /* PRQA S 2824, 2844 # JV-01, JV-01 */
      #endif /* (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS) */

      #if (ADC_ENABLE_PWM_DIAG == STD_ON)
      if (ADC_TRUE == LpGroup->blPwmDiag)
      {
        /* Store the supplemental information to the next of the result buffer */
        LulBufferOffset++;                                                                                              /* PRQA S 3383 # JV-01 */
        LpBuffer[LulBufferOffset] = (uint16)(LulConvertedValue >> ADC_ADCX_DIR_SFT);
      } /* else: No action required */
      #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
    }

    #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
    if (ADC_GROUP_REPL_ABORT_RESTART == LpGroup->enGroupReplacement)
    #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
    {
      /* Get first channel conversion result */
      LucChannelIndex = LpGroup->ucStartVirChPtr;
      /* Copy result data to internal buffer by down count for AdcGroup */
      for (LulLoopCount = 0UL; LulLoopCount < LulNumChannel; LulLoopCount++)
      {
        /* Read the offset of the buffer for normal mode */
        LulBufferOffset = LulLoopCount;
        #if (ADC_ENABLE_STREAMING == STD_ON)
        /* Check if the group is configured in streaming access mode */
        if (ADC_ACCESS_MODE_STREAMING == LpGroup->enGroupAccessMode)
        {
          /* Read the offset for the buffer pointer based on number of channels and completed samples. */
          LulBufferOffset *= (uint32)LpGroup->ddNumberofSamples;                                                        /* PRQA S 3383, 3384 # JV-01, JV-01 */
        } /* else: No action required */
        #endif /* (ADC_ENABLE_STREAMING == STD_ON) */
        LulConvertedValue = LpAdcRegisters->aaADCXnDIR[LucChannelIndex];

        #if (ADC_ENABLE_ID_ERR == STD_ON)
        /* Check for ID error */
        if (ADC_ADCX_DIR_IDEF_ERR == (LulConvertedValue & ADC_ADCX_DIR_IDEF))
        {
          if (ADC_INVALID_CHANNELID == LucErrorVirCh)
          {
            /* Store the current channel index in the Id error channel */
            LucErrorVirCh = LucChannelIndex;
          } /* else: No action required */
          LpBuffer[LulBufferOffset] = ADC_RESULT_BUF_INIT;
        }
        else
        #endif /* (ADC_ENABLE_ID_ERR == STD_ON) */
        {
          /* Copy the converted value to the internal buffer */
          #if (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS) 
          LpBuffer[LulBufferOffset] = (uint16)(LulConvertedValue & ADC_ADCX_DIR_DR);
          #else
          LpBuffer[LulBufferOffset] = LulConvertedValue;
          #endif /* (ADC_RESULT_DATA_TYPE == ADC_RESULT_DATA_16_BITS) */
        }

        /* Increment the index of channel */
        LucChannelIndex++;                                                                                              /* PRQA S 3383 # JV-01 */
      } /* end of for (LulLoopCount = 0UL; LulLoopCount < LulNumChannel; LulLoopCount++) */
    } /* end of if (ADC_GROUP_REPL_ABORT_RESTART == LpGroup->enGroupReplacement) */
      /* else: No action required */

    #if (ADC_ENABLE_ID_ERR == STD_ON)
    /* Check if ID error is detected from the conversion result */
    if (ADC_INVALID_CHANNELID != LucErrorVirCh)
    {
      #if (ADC_ENABLE_PWM_DIAG == STD_ON)
      if (ADC_TRUE == LpGroup->blPwmDiag)
      {
        /* Get the channel from the group channel configuration as PWM-Diag has no virtual channel */
        LucChannelToGroupIndex = LpGroup->ucChannelToGroupIndex;
        LucPhysCh = (uint8)(Adc_GpChannelToGroup[LucChannelToGroupIndex] & ADC_CHANNEL_ID_MASK);                        /* PRQA S 2824 # JV-01 */
      }
      else
      #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
      {
        /* Get the physical channel from ADCXnVCRj register */
        LucPhysCh = (uint8)(LpAdcRegisters->aaADCXnVCR[LucErrorVirCh] & ADC_ADCX_VCR_GCTRL);                            /* PRQA S 2844 # JV-01 */
      }
      /* Store the physical channel in the Id error status of group data */
      LpGroupData->ucChannelIdError = LucPhysCh;
      /* Clear the read data available flag */
      LblDataAvailable = ADC_FALSE;
    } /* end of if (ADC_INVALID_CHANNELID != LucErrorVirCh) */
      /* else: No action required */
    #endif /* (ADC_ENABLE_ID_ERR == STD_ON) */

    #if ((ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
    /* Check error status via error interrupt if it is enabled */
    if (ADC_TRUE == LpHwUnitConfig->blInterruptErr)
    {
      #if (((((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON)) && \
            (ADC_ENABLE_ERR_INT == STD_ON)) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
      /* Read and clear the error status if an error interrupt has already occurred */
      if (ADC_TRUE == LpGroupData->blConvError)
      {
        LpGroupData->blConvError = ADC_FALSE;
        /* Clear the read data available flag */
        LblDataAvailable = ADC_FALSE;
      } /* else: No action required */
      #endif
    }
    else
    #endif /* ((ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON)) */
    {
      #if (ADC_ENABLE_PARITY_ERR == STD_ON)
      /* Check for parity error that may occur after reading the result data */
      LblErrorFlag = Adc_CheckParity(LddGroup);
      if (ADC_TRUE == LblErrorFlag)
      {
        /* Clear the read data available flag */
        LblDataAvailable = ADC_FALSE;
      } /* else: No action required */
      #endif /* (ADC_ENABLE_PARITY_ERR == STD_ON) */
    }

    #if (((ADC_ENABLE_ERR == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON)) && (ADC_TRACK_AND_HOLD == STD_ON))
    /* If the requested group is for T&H, do not discard the result even when error is detected */
    if (ADC_TH_DISABLED != LpGroup->ucTrackAndHoldGroup)
    {
      /* Set the read data available flag even if the error occurs */
      LblDataAvailable = ADC_TRUE;
    } /* else: No action required */
    #endif /* (((ADC_ENABLE_ERR == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON)) && (ADC_TRACK_AND_HOLD == STD_ON)) */
  } /* end of if (ADC_RESULT_AVAILABLE == (LulConvertedValue & ADC_RESULT_AVAILABLE)) */
    /* else: No action required */

  return LblDataAvailable;
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON)) */

/***********************************************************************************************************************
** Function Name        : Adc_SetStatus
**
** Service ID           : NA
**
** Description          : This internal function shall set statue to RAM for requested ADC channel group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LddGroup, LenStatusType
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupRamData
**
** Functions invoked    : None
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_029, ADC_DUD_ACT_029_GBL001
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_SetStatus(const Adc_GroupType LddGroup, const Adc_StatusType LenStatusType)
{
  Adc_GpGroupRamData[LddGroup].enGroupStatus = LenStatusType;                                                           /* PRQA S 2824 # JV-01 */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_EnableHwGroup
**
** Service ID           : NA
**
** Description          : This internal function shall enables the ongoing HW triggered group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitRamData, Adc_GpGroupRamData, Adc_GpHwUnitConfig
**
** Functions invoked    : Adc_PicEnableHwTrigger, Adc_ConfigureGroupForConversion
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_030, ADC_DUD_ACT_030_GBL001, ADC_DUD_ACT_030_GBL002,
** Reference ID         : ADC_DUD_ACT_030_GBL003, ADC_DUD_ACT_030_GBL004
***********************************************************************************************************************/
#if (ADC_HW_TRIGGER_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_EnableHwGroup(const Adc_GroupType LddGroup)
{
  #if (ADC_ENABLE_ADC_TSEL == STD_ON) && (ADC_IP_C_ADCK == STD_OFF)
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  #endif /* (ADC_ENABLE_ADC_TSEL == STD_ON) && (ADC_IP_C_ADCK == STD_OFF) */
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2VAR(volatile Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  uint8 LucSgUnitIndex;

  /* Get the pointer to requested group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  LucSgUnitIndex = LpGroup->ucSgUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  /* Initialize HW RAM data to a local pointer */
  LpSgUnitData = &Adc_GpSgUnitRamData[LucSgUnitIndex];                                                                  /* PRQA S 2824 # JV-01 */
  /* Read the group data pointer */
  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */

  #if (ADC_ENABLE_PWM_DIAG == STD_ON)
  /* Check if trigger source of requested group is PWM-Diag */
  if (ADC_TRUE == LpGroup->blPwmDiag)
  {
    /* No action required for HW triggers when enabling PWM-Diag */
  }
  else
  #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
  {
    #if (ADC_ENABLE_ADC_TSEL == STD_ON) && (ADC_IP_C_ADCK == STD_OFF)
    /* Get the HW unit configuration. */
    LpHwUnitConfig = &Adc_GpHwUnitConfig[LpGroup->ucHwUnitIndex];                                                       /* PRQA S 2824 # JV-01 */
    /* Check if requested group belongs to HW unit in AWO */
    if (NULL_PTR != LpHwUnitConfig->pSgTriggReg)                                                                        /* PRQA S 2814 # JV-01 */
    {
      /* No action required for HW triggers as those for HW unit in AWO are statically configured at initialization */
    }
    else
    #endif /* (ADC_ENABLE_ADC_TSEL == STD_ON) && (ADC_IP_C_ADCK == STD_OFF) */
    {
      #if (ADC_ENABLE_PIC_TSEL == STD_ON)
      /* Enable Hw trigger of PIC unit */
      Adc_PicEnableHwTrigger(LddGroup);
      #endif /* (ADC_ENABLE_PIC_TSEL == STD_ON) */
    }
  }

  /* Set the Trigger status for the group as true */
  LpGroupData->blHwTriggStatus = ADC_TRUE;                                                                              /* PRQA S 2814 # JV-01 */

  /* Set the SG unit status to busy */
  LpSgUnitData->blSgUnitStatus = ADC_TRUE;                                                                              /* PRQA S 2814 # JV-01 */
  /* Reset the number of completed sample to zero. */
  LpGroupData->ucSamplesCompleted = ADC_COUNT_BYTE_INIT;
  /* Reset the number of completed channels to zero. */
  LpGroupData->ucChannelsCompleted = ADC_COUNT_BYTE_INIT;

  /* Configure the group for conversion */
  Adc_ConfigureGroupForConversion(LddGroup);
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_HW_TRIGGER_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_IntDisableEnableChannel
**
** Service ID           : NA
**
** Description          : This internal function shall enable or disable
**                        a channel for conversion during runtime.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LddGroup, LddChannelId, LblApiType
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupRamData, Adc_GpGroupConfig, Adc_GpChannelToGroup, Adc_GpChannelToDisableEnable
**
** Functions invoked    : Det_ReportError, ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_031, ADC_DUD_ACT_031_CRT001, ADC_DUD_ACT_031_CRT002,
** Reference ID         : ADC_DUD_ACT_031_ERR001, ADC_DUD_ACT_031_ERR002, ADC_DUD_ACT_031_GBL001,
** Reference ID         : ADC_DUD_ACT_031_GBL002, ADC_DUD_ACT_031_GBL003
***********************************************************************************************************************/
#if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_IntDisableEnableChannel(const Adc_GroupType LddGroup,                                  /* PRQA S 1532 # JV-01 */
  const Adc_ChannelType LddChannelId, const boolean LblApiType)
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  Adc_ChannelType LddGroupChannel;
  uint8 LucChannelToGroupIndex;
  uint32 LulNoOfChannels;
  uint32 LulLoopCount;
  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  boolean LblDetErrFlag;
  uint8 LucNoOfChannelDisable;
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */

  /* Enter the critical section protection */
  ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);

  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */
  /* Get the pointer to requested group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Read the number of channels in the group */
  LulNoOfChannels = (uint32)LpGroup->ucChannelCount;                                                                    /* PRQA S 2814 # JV-01 */
  /* Make the Adc_GpChannelToDisableEnable[] all true */

  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  LblDetErrFlag = ADC_TRUE;
  LucNoOfChannelDisable = ADC_VAL_BYTE_INIT;
  /* Check number of channel when disable channel */
  if (ADC_FALSE == LblApiType)
  {
    /* Get group index of 1st channel, configured for the requested group */
    LucChannelToGroupIndex = LpGroup->ucChannelToGroupIndex;
    LulLoopCount = LulNoOfChannels;
    while (LulLoopCount > 0UL)
    {
      /* Decrement counter */
      LulLoopCount--;

      LddGroupChannel = (uint8)(Adc_GpChannelToGroup[LucChannelToGroupIndex] & ADC_CHANNEL_ID_MASK);                    /* PRQA S 2824 # JV-01 */
      /* Check the channel to disable */
      if (LddGroupChannel == LddChannelId)
      {
        if (Adc_GpChannelToDisableEnable[LucChannelToGroupIndex] != LblApiType)                                         /* PRQA S 2824 # JV-01 */
        {
          /* Increase the count of the target channel */
          LucNoOfChannelDisable++;                                                                                      /* PRQA S 3383 # JV-01 */
        }
        else
        {
          /* Set the error flag to ADC_FALSE to avoid reporting DET if channel input is already disabled */
          LblDetErrFlag = ADC_FALSE;
          LulLoopCount = 0UL;
        }
      } /* end of if (LddGroupChannel == LddChannelId) */
        /* else: No action required */

      /* Increment the pointer to next channel configured in the group */
      LucChannelToGroupIndex++;                                                                                         /* PRQA S 3383 # JV-01 */
    } /* end of while (LulLoopCount > 0UL) */
  } /* end of if (ADC_FALSE == LblApiType) */
    /* else: No action required */

  /* Check if the action is to disable channels and if the target channel does not exist or disable all channels */
  if ((ADC_FALSE == LblApiType) &&
      (((LpGroupData->ucNoOfDisabledChannels + LucNoOfChannelDisable) == LpGroup->ucChannelCount) ||                    /* PRQA S 2814 # JV-01 */
       (ADC_VAL_BYTE_INIT == LucNoOfChannelDisable)))
  {
    /* No action required */
  }
  else
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Reset group index of 1st channel, configured for the requested group */
    LucChannelToGroupIndex = LpGroup->ucChannelToGroupIndex;
    LulLoopCount = LulNoOfChannels;
    while (LulLoopCount > 0UL)
    {
      /* Decrement counter */
      LulLoopCount--;

      LddGroupChannel = (uint8)(Adc_GpChannelToGroup[LucChannelToGroupIndex] & ADC_CHANNEL_ID_MASK);                    /* PRQA S 2824 # JV-01 */
      /* Check the channel to disable */
      if (LddGroupChannel == LddChannelId)
      {
        #if (ADC_DEV_ERROR_DETECT == STD_ON)
        LblDetErrFlag = ADC_FALSE;
        #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
        /* Is the setting state different from the current state? */
        if (Adc_GpChannelToDisableEnable[LucChannelToGroupIndex] != LblApiType)                                         /* PRQA S 2824 # JV-01 */
        {
          /* Set the flag indicating to enable or disable the channel Id */
          Adc_GpChannelToDisableEnable[LucChannelToGroupIndex] = LblApiType;
          /* Check if Adc_EnableChannel or Adc_DisableChannel was called */
          if (ADC_FALSE == LblApiType)
          {
            /* Increment the number of channels disabled */
            LpGroupData->ucNoOfDisabledChannels++;                                                                      /* PRQA S 2814, 3383, 3387 # JV-01, JV-01, JV-01 */
          }
          else
          {
            /* Decrement the number of channels disabled */
            LpGroupData->ucNoOfDisabledChannels--;                                                                      /* PRQA S 3384, 3387 # JV-01, JV-01 */
          }
        } /* end of if (Adc_GpChannelToDisableEnable[LucChannelToGroupIndex] != LblApiType) */
          /* else: No action required */
      } /* end of if (LddGroupChannel == LddChannelId) */
        /* else: No action required */

      /* Increment the pointer to next channel configured in the group */
      LucChannelToGroupIndex++;                                                                                         /* PRQA S 3383 # JV-01 */
    } /* end of while (LulLoopCount > 0UL) */
  }

  /* Exit the critical section protection */
  ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);

  #if (ADC_DEV_ERROR_DETECT == STD_ON)
  /* Report the error to DET if an error is detected */
  if (ADC_TRUE == LblDetErrFlag)
  {
    if (ADC_FALSE == LblApiType)
    {
      (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DISABLE_CHANNEL_SID, ADC_E_PARAM_CHANNEL);
    }
    else
    {
      (void)Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_ENABLE_CHANNEL_SID, ADC_E_PARAM_CHANNEL);
    }
  } /* else: No action required */
  #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_DISABLE_CHANNEL == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_PollingReadGroup
**
** Service ID           : NA
**
** Description          : This internal function shall update the group status,
**                        get the converted value from the peripheral registers,
**                        call the call-back function if enabled.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpGroupRamData
**
** Functions invoked    : ADC_ENTER_CRITICAL_SECTION, Adc_DmaIsr, Adc_CheckAndCopyResultData, Adc_GroupCompleteMode,
**                        Adc_ChannelCompleteMode, ADC_DEM_REPORT_ERROR, Adc_CallGroupNotify,
**                        ADC_EXIT_CRITICAL_SECTION, Adc_ReportError
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_032, ADC_DUD_ACT_032_CRT001, ADC_DUD_ACT_032_CRT002, ADC_DUD_ACT_032_ERR001
***********************************************************************************************************************/
#if ((ADC_FUNCTIONALITY_MODE != ADC_INTERRUPT) && (ADC_READ_GROUP_API == STD_ON))

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_PollingReadGroup(const Adc_GroupType LddGroup)                                         /* PRQA S 1532 # JV-01 */
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  volatile P2CONST(Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  uint8 LucHwUnitIndex;
  /* Number of available channels */
  uint8 LucChannelCount;
  /* Hardware stop timeout flag */
  boolean LblHwTimedOut;
  /* Read data available flag */
  boolean LblDataAvailable;

  /* Get the pointer to requested group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Read the Hardware Unit to which the group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */

  #if (ADC_ENABLE_DMA_MODE == STD_ON)
  if (ADC_TRUE == LpGroup->blEnableDmaTransfer)
  {
    /* Get the SG unit to which the group is mapped */
    Adc_DmaIsr(LucHwUnitIndex, LpGroup->ucSgUnitIndex);
  }
  else
  #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
  {
    /* Get the pointer to the group runtime data */
    LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                        /* PRQA S 2824 # JV-01 */

    /* Enter the critical section protection */
    ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

    /* Load the current group's first channel buffer pointer */
    #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
    if (ADC_GROUP_REPL_SUSPEND_RESUME == LpGroup->enGroupReplacement)
    {
      LucChannelCount = LpGroupData->ucChannelsCompleted;                                                               /* PRQA S 2814 # JV-01 */
    }
    else
    #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
    {
      LucChannelCount = LpGroupData->ucChannelCount;                                                                    /* PRQA S 2814 # JV-01 */
    }

    /* Read conversion result data */
    LblDataAvailable = Adc_CheckAndCopyResultData(LddGroup, LucChannelCount);
    if (ADC_TRUE == LblDataAvailable)
    {
      #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
      /* Check if group is configured Suspend_resume mode */
      if (ADC_GROUP_REPL_SUSPEND_RESUME == LpGroup->enGroupReplacement)
      {
        /* Invoke channel complete function */
        LblHwTimedOut = Adc_ChannelCompleteMode(LddGroup, LucHwUnitIndex);
      }
      else
      #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
      {
        /* Invoke group complete function */
        LblHwTimedOut = Adc_GroupCompleteMode(LddGroup, LucHwUnitIndex);
      }
    } /* else: No action required */

    /* Exit the critical section protection */
    ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

    if (ADC_TRUE == LblDataAvailable)
    {
      #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
      /* Call to notification function */
      Adc_CallGroupNotify(LddGroup);
      #endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

      if (ADC_TRUE == LblHwTimedOut)
      {
        /* Reporting to DEM when timeout cause by hardware error */
        ADC_DEM_REPORT_ERROR(ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
      } /* else: No action required */
    } /* else: No action required */

    #if ((ADC_ENABLE_ERR == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON))
    /* Report errors to Dem and invokes error notification callback functions, if any errors are detected */
    Adc_ReportError(LddGroup);
    #endif
  }
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* ((ADC_FUNCTIONALITY_MODE != ADC_INTERRUPT) && (ADC_READ_GROUP_API == STD_ON)) */

/***********************************************************************************************************************
** Function Name        : Adc_HwInit
**
** Service ID           : NA
**
** Description          : This internal function performs the initialization
**                        of the ADC Driver hardware registers.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig, Adc_GaaHwUnitData, Adc_GpSgUnitRamData, Adc_GucMaxDmaChannels,
**                        Adc_GpLimitCheckRange, Adc_GucNoOfGroups, Adc_GpGroupRamData, Adc_GucMaxSwTriggGroups
**
** Functions invoked    : Adc_DmaInit, Adc_PicInit, Adc_SetWaitTime, Adc_EcmErrorInterrupt, Adc_SetStatus, Adc_AdcInit
**
** Registers Used       : AIR_ISELR0, AIR_DSELR0, EIC, ADCXnADHALTR, ADCXnSFTCR, ADCXnADCR1, ADCXnADCR2,
**                        ADCXnVCULLMTBRy, ADCXnVCLMINTER1, ADCXnVCLMINTER2, ADCXnTOCCR
**
** Reference ID         : ADC_DUD_ACT_033, ADC_DUD_ACT_033_GBL003, ADC_DUD_ACT_033_GBL004,
** Reference ID         : ADC_DUD_ACT_033_GBL006, ADC_DUD_ACT_033_GBL007, ADC_DUD_ACT_033_GBL008,
** Reference ID         : ADC_DUD_ACT_033_REG001, ADC_DUD_ACT_033_REG002, ADC_DUD_ACT_033_REG003,
** Reference ID         : ADC_DUD_ACT_033_REG004, ADC_DUD_ACT_033_REG005, ADC_DUD_ACT_033_REG006,
** Reference ID         : ADC_DUD_ACT_033_REG007, ADC_DUD_ACT_033_REG008, ADC_DUD_ACT_033_REG009,
** Reference ID         : ADC_DUD_ACT_033_REG010, ADC_DUD_ACT_033_REG011
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_HwInit(void)                                                                           /* PRQA S 1532, 2755, 3006 # JV-01, JV-01, JV-01 */
{
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  P2VAR(volatile Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  P2CONST(Adc_LimitCheckConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpLimitCheckRange;
  uint32 LulLimitRegCount;
  #endif
  uint8 LucHwUnitIndex;
  uint8 LucSgUnitCount;
  uint8 LucSgLoopCount;
  uint8 LucLoopCount;
  /* Local variable for safety control register */
  uint8 LucSftcrValue;
  uint8 LucSgUnitIndex;

  /* INITIALIZATION DMA UNIT */
  #if (ADC_ENABLE_DMA_MODE == STD_ON)
  if (ADC_NUM_CHANNEL_ZERO != Adc_GucMaxDmaChannels)
  {
    Adc_DmaInit();
  } /* else: No action required */
  #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */

  #if (ADC_ENABLE_PIC_TSEL == STD_ON)
  #if ((ADC_ENABLE_PIC_COMMON == STD_ON) || (ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  /* INITIALIZATION OF PIC UNITS */
  Adc_PicInit();
  #endif /* ((ADC_ENABLE_PIC_COMMON == STD_ON) || (ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
  #endif /* (ADC_ENABLE_PIC_TSEL == STD_ON) */

  #if (ADC_IP_C_ADCK == STD_OFF)
  #if ((ADC_IP_ADCH == STD_ON) || (ADC_IP_ADCK == STD_ON))
  #if ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_ENABLE_ERR_INT == STD_ON))
  /* Initialize ADC interrupt request select register and perform synchronization for AIR */
  ADC_AIR_ISELR0 &= ADC_INTERRUPT_REQUEST;                                                                              /* PRQA S 0303 # JV-01 */
  (void)ADC_AIR_ISELR0;                                                                                                 /* PRQA S 0303 # JV-01 */
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  #endif /* ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_ENABLE_ERR_INT == STD_ON)) */

  #if (ADC_ENABLE_DMA_MODE == STD_ON)
  /* Initialize ADC DMA request select register and perform synchronization for AIR */
  ADC_AIR_DSELR0 &= ADC_DMATRANSFER_REQUEST;                                                                            /* PRQA S 0303 # JV-01 */
  (void)ADC_AIR_DSELR0;                                                                                                 /* PRQA S 0303 # JV-01 */
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
  #endif /* ((ADC_IP_ADCH == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
  #endif /* #if (ADC_IP_C_ADCK == STD_OFF) */
  
  LucSgUnitIndex = (uint8)0U;

  /* INITIALIZATION OF ADC HARDWARE UNITS */
  for (LucHwUnitIndex = (uint8)0U; LucHwUnitIndex < (uint8)ADC_MAX_HW_UNITS; LucHwUnitIndex++)                          /* PRQA S 2877 # JV-01 */
  {
    /* Initialize the local variable for HW unit configuration */
    LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                               /* PRQA S 2824 # JV-01 */
    /* Read the base configuration register of the hardware unit */
    LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                /* PRQA S 2814 # JV-01 */

    #if (ADC_IP_ADCH == STD_ON)
    /* Store the first SG unit index of HW unit */
    Adc_GaaHwUnitData[LucHwUnitIndex].ucSgUnitIndex = LucSgUnitIndex;
    #endif /* (ADC_IP_ADCH == STD_ON) */

    /* Initialize the status of all SG units */
    Adc_GaaHwUnitData[LucHwUnitIndex].ucSgUnitStatus = ADC_BYTE_ZERO;
    #if (ADC_TRACK_AND_HOLD == STD_ON)
    Adc_GaaHwUnitData[LucHwUnitIndex].ucTrackHoldStatus = ADC_BYTE_ZERO;
    #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

    #if (ADC_ENABLE_ERR_INT == STD_ON)
    if (ADC_TRUE == LpHwUnitConfig->blInterruptErr)
    {
      /* Enable ADC error interrupt and perform synchronization for INTC2 */
      RH850_SV_CLEAR_ICR_SYNCP(8, LpHwUnitConfig->pErrEicRegAddress, (uint8)~ADC_EIC_EIMK);                             /* PRQA S 0751, 1006, 2814 # JV-01, JV-01, JV-01 */
    } /* else: No action required */
    #endif /* (ADC_ENABLE_ERR_INT == STD_ON) */

    /* Set all SGACT of all scan groups to 0 */
    LpAdcRegisters->ucADCXnADHALTR = ADC_ADCX_ADHALTR_HALT;                                                             /* PRQA S 2814 # JV-01 */
    #if ((ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
    if (ADC_TRUE == LpHwUnitConfig->blInterruptErr)                                                                     /* PRQA S 2814 # JV-01 */
    {
      LucSftcrValue = ADC_ERR_INT_MASK;
    }
    else
    #endif /* ((ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON)) */
    {
      LucSftcrValue = ADC_REG_BYTE_INIT;
    }
    LpAdcRegisters->ucADCXnSFTCR = (uint8)(LucSftcrValue | ADC_READ_AND_CLEAR_ENABLE);
    /*
     * Set the HW unit register as per the configuration for self-diagnostic,
     * Alignment control, resolution and suspend mode.
     */
    LpAdcRegisters->ucADCXnADCR1 = ADC_ASYNCHRONOUS_SUSPEND;
    #if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT)
    LpAdcRegisters->ucADCXnADCR2 = ADC_ALIGN_RIGHT_MASK;
    #else /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT) */
    LpAdcRegisters->ucADCXnADCR2 = ADC_ALIGN_LEFT_MASK;
    #endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT) */
    LucSgUnitCount = LpHwUnitConfig->ucSgUnitCount;

    #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
    /* Initialize the device-specific ADC hardware registers */
    Adc_AdcInit(LucHwUnitIndex);
    #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
    #if (ADC_IP_ADCH == STD_ON)
    if (ADC_WAITTIME_DISABLED != LpHwUnitConfig->ucWaitTimeIndex)
    {
      /* INITIALIZATION OF WAIT TIME CONFIGURATION */
      Adc_SetWaitTime(LucHwUnitIndex);
    } /* else: No action required */
    #endif /* (ADC_IP_ADCH == STD_ON) */

    /* INITIALIZATION OF ADC SCAN GROUPS */
    for (LucSgLoopCount = ADC_COUNT_BYTE_INIT; LucSgLoopCount < LucSgUnitCount; LucSgLoopCount++)
    {
      LpSgUnitData = &Adc_GpSgUnitRamData[LucSgUnitIndex];                                                              /* PRQA S 2824 # JV-01 */
      /* clearing the scan group unit status */
      LpSgUnitData->blSgUnitStatus = ADC_FALSE;                                                                         /* PRQA S 2814 # JV-01 */
      LpSgUnitData->ddCurrentConvGroup = ADC_INVALID_GROUP;
      #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
      LpSgUnitData->ddCurrentPriority = (Adc_GroupPriorityType)0U;
      #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
      #if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
           ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
      /* Initialize queue */
      LpSgUnitData->ucQueueStatus = ADC_QUEUE_EMPTY;
      LpSgUnitData->ucQueueCounter = ADC_COUNT_BYTE_INIT;
      #endif

      /* Increment SG unit index */
      LucSgUnitIndex++;                                                                                                 /* PRQA S 3383 # JV-01 */
    } /* end of for (LucSgLoopCount = ADC_COUNT_BYTE_INIT; LucSgLoopCount < LucSgUnitCount; LucSgLoopCount++) */

    #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    /* INITIALIZATION OF VIRTUAL CHANNEL UPPER/LOWER LIMIT TABLE REGISTER */
    if (NULL_PTR != Adc_GpLimitCheckRange)
    {
      LpLimitCheckRange = &Adc_GpLimitCheckRange[LucHwUnitIndex];
      for (LulLimitRegCount = 0UL; LulLimitRegCount < ADC_NUM_OF_LIMIT_TABLE; LulLimitRegCount++)
      {
        if (ADC_ADCX_VCULLMTBR_OFF != LpLimitCheckRange->ulVCULLMTBR[LulLimitRegCount])                                 /* PRQA S 2814 # JV-01 */
        {
          /* Load the Lower and Upper Limit Value. */
          LpAdcRegisters->aaADCXnVCULLMTBRy[LulLimitRegCount] = LpLimitCheckRange->ulVCULLMTBR[LulLimitRegCount];
        } /* else: No action required */
      }
      #if (ADC_ENABLE_ERR_INT == STD_ON)
      if (ADC_TRUE == LpHwUnitConfig->blInterruptErr)
      {
        LpAdcRegisters->aaADCXnVCLMINTER[ADC_VCLM_1] = LpHwUnitConfig->ulLimitCheckInterruptMask1;
        LpAdcRegisters->aaADCXnVCLMINTER[ADC_VCLM_2] = LpHwUnitConfig->ulLimitCheckInterruptMask2;
      }
      else
      {
        LpAdcRegisters->aaADCXnVCLMINTER[ADC_VCLM_1] = ADC_REG_DWORD_INIT;
        LpAdcRegisters->aaADCXnVCLMINTER[ADC_VCLM_2] = ADC_REG_DWORD_INIT;
      }
      #endif /* (ADC_ENABLE_ERR_INT == STD_ON) */
    } /* end of if (NULL_PTR != Adc_GpLimitCheckRange) */
      /* else: No action required */
    #endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */

    /* INITIALIZATION OF TRIGGER OVERLAP CHECK CONTROL REGISTER */
    #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
    LpAdcRegisters->ucADCXnTOCCR = ADC_BYTE_ONE;
    #endif /* (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON) */
  } /* end of for (LucHwUnitIndex = (uint8)0U; LucHwUnitIndex < (uint8)ADC_MAX_HW_UNITS; LucHwUnitIndex++) */

  #if (ADC_ENABLE_PARITY_ERR_INT == STD_ON)
  Adc_EcmErrorInterrupt(ADC_TRUE);
  #endif /* (ADC_ENABLE_PARITY_ERR_INT == STD_ON) */

  /* INITIALIZATION OF GROUPS TO SCAN GROUPS */
  for (LucLoopCount = ADC_VAL_BYTE_INIT; LucLoopCount < Adc_GucNoOfGroups; LucLoopCount++)
  {
    /* Initialize all the Group Pointer */
    LpGroupData = &Adc_GpGroupRamData[LucLoopCount];                                                                    /* PRQA S 2824 # JV-01 */
    /* Initialize all the groups as idle */
    Adc_SetStatus((Adc_GroupType)LucLoopCount, ADC_IDLE);
    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* Store the disabled notification into RAM */
    /* Disable notifications */
    LpGroupData->blNotifyStatus = ADC_FALSE;                                                                            /* PRQA S 2814 # JV-01 */
    #endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* Disable buffer address initialization */
    LpGroupData->blBufferStatus = ADC_FALSE;
    #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */
    #if (ADC_HW_TRIGGER_API == STD_ON)
    /* Disable hardware trigger status */
    LpGroupData->blHwTriggStatus = ADC_FALSE;
    #endif /* (ADC_HW_TRIGGER_API == STD_ON) */

    #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
    /* Clear the flag indicating no group is present in queue */
    LpGroupData->blGrpPresent = ADC_FALSE;
    #endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */

    /* Set the flag indicating result data is not available */
    LpGroupData->blResultRead = ADC_TRUE;
    #if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)
    /* Set no of channels disabled during initialization as zero */
    LpGroupData->ucNoOfDisabledChannels = (uint8)0U;
    #endif /* (ADC_ENABLE_DISABLE_CHANNEL == STD_ON) */

    /* Initialize the error status */
    #if (((((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON)) && \
          (ADC_ENABLE_ERR_INT == STD_ON)) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
    LpGroupData->blConvError = ADC_FALSE;
    #endif
    #if (ADC_ENABLE_ID_ERR == STD_ON)
    LpGroupData->ucChannelIdError = ADC_INVALID_CHANNELID;
    #endif
    #if (ADC_ENABLE_OVERWRITE_ERR == STD_ON)
    LpGroupData->ucChannelOverwritten = ADC_INVALID_CHANNELID;
    #endif
    #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    LpGroupData->ucChannelLimitError = ADC_INVALID_CHANNELID;
    #endif
    #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
    LpGroupData->blTriggerOverlapped = ADC_FALSE;
    #endif
    #if (ADC_ENABLE_PARITY_ERR == STD_ON)
    LpGroupData->ucChannelParityError = ADC_INVALID_CHANNELID;
    #endif
    /* Initialize the buffer status and request */
    #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
    #if (ADC_HW_TRIGGER_API == STD_ON)
    if (LucLoopCount < (uint8)(Adc_GucNoOfGroups - Adc_GucMaxSwTriggGroups))
    {
      Adc_EnableHardwareTriggerInfo[LucLoopCount].blBufferLock = ADC_FALSE;                                             /* PRQA S 2844 # JV-01 */
      Adc_EnableHardwareTriggerInfo[LucLoopCount].blSetRequest = ADC_FALSE;                                             /* PRQA S 2844 # JV-01 */
      Adc_DisableHardwareTriggerInfo[LucLoopCount].blBufferLock = ADC_FALSE;                                            /* PRQA S 2844 # JV-01 */
      Adc_DisableHardwareTriggerInfo[LucLoopCount].blSetRequest = ADC_FALSE;                                            /* PRQA S 2844 # JV-01 */
    }
    #endif
    #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    if (LucLoopCount < Adc_GucMaxSwTriggGroups)
    {
      Adc_StartGroupConversionInfo[LucLoopCount].blBufferLock = ADC_FALSE;                                              /* PRQA S 2844 # JV-01 */
      Adc_StartGroupConversionInfo[LucLoopCount].blSetRequest = ADC_FALSE;                                              /* PRQA S 2844 # JV-01 */
      Adc_StopGroupConversionInfo[LucLoopCount].blBufferLock = ADC_FALSE;                                               /* PRQA S 2844 # JV-01 */
      Adc_StopGroupConversionInfo[LucLoopCount].blSetRequest = ADC_FALSE;                                               /* PRQA S 2844 # JV-01 */
    }
    #endif
    #endif /* (ADC_MULTI_CORE_SUPPORT == STD_ON) */
  } /* end of for (LucLoopCount = ADC_VAL_BYTE_INIT; LucLoopCount < Adc_GucNoOfGroups; LucLoopCount++) */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_HwDeInit
**
** Service ID           : NA
**
** Description          : This internal function performs the de-initialization
**                        of the ADC Driver global variables and registers.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig, Adc_GpSgUnitConfig, Adc_GpSgUnitRamData, Adc_GblDriverStatus,
**                        Adc_GucNoOfGroups, Adc_GpGroupRamData, Adc_GucMaxDmaChannels
**
** Functions invoked    : ADC_DET_RUNTIME_ERROR, Adc_DisableConvertInterrupt, Adc_DeInitWaitTime, Adc_DmaDeInit,
**                        Adc_PicDeInit, Adc_EcmErrorInterrupt, Adc_AdcDeInit
**
** Registers Used       : ADCXnSGSRx, ADCXnADHALTR, ADCXnSFTCR, ADCXnADCR1, ADCXnADCR2, ADCXnTDCR, ADCXnODCR,
**                        ADCXnTOCCR, ADCXnVCULLMTBRy, ADCXnVCLMINTER1, ADCXnVCLMINTER2, ADCXnVCLMSCR1, ADCXnVCLMSCR2,
**                        ADCXnECR, ADCXnADTIPRx, ADCXnADTPRRx, ADCXnSGCRx, ADCXnSGMCYCRx, ADCXnSGVCPRx, ADCXnVCRj,
**                        AIR_ISELR0, AIR_DSELR0, EIC
**
** Reference ID         : ADC_DUD_ACT_034, ADC_DUD_ACT_034_ERR001, ADC_DUD_ACT_034_GBL001,
** Reference ID         : ADC_DUD_ACT_034_GBL002, ADC_DUD_ACT_034_REG001, ADC_DUD_ACT_034_REG002,
** Reference ID         : ADC_DUD_ACT_034_REG003, ADC_DUD_ACT_034_REG004, ADC_DUD_ACT_034_REG005,
** Reference ID         : ADC_DUD_ACT_034_REG006, ADC_DUD_ACT_034_REG007, ADC_DUD_ACT_034_REG008,
** Reference ID         : ADC_DUD_ACT_034_REG010, ADC_DUD_ACT_034_REG011, ADC_DUD_ACT_034_REG012,
** Reference ID         : ADC_DUD_ACT_034_REG013, ADC_DUD_ACT_034_REG014, ADC_DUD_ACT_034_REG015,
** Reference ID         : ADC_DUD_ACT_034_REG016, ADC_DUD_ACT_034_REG017, ADC_DUD_ACT_034_REG018,
** Reference ID         : ADC_DUD_ACT_034_REG019, ADC_DUD_ACT_034_REG020, ADC_DUD_ACT_034_REG021,
** Reference ID         : ADC_DUD_ACT_034_REG022
***********************************************************************************************************************/
#if (ADC_DEINIT_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_HwDeInit(void)                                                                         /* PRQA S 1532, 2755, 3006 # JV-01, JV-01, JV-01 */
{
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  P2VAR(volatile Adc_SGRegType, AUTOMATIC, REGSPACE) LpSGRegisters;
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  uint32 LulLimitRegCount;
  #endif
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  boolean LblDetErrFlag;
  volatile P2CONST(Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */

  uint32 LulSgLoopCount;
  uint32 LulChannelLoop;
  uint32 LulNoOfVirCh;
  uint8 LucSgUnitId;
  uint8 LucHwUnitIndex;
  uint8 LucSgUnitIndex;
  #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
  uint8 LucGroup;
  #endif

  /* Initialize the loop count value to zero */
  LucHwUnitIndex = ADC_VAL_BYTE_INIT;
  LucSgUnitIndex = ADC_VAL_BYTE_INIT;

  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  /* Initialize error flag */
  LblDetErrFlag = ADC_FALSE;
  #if (ADC_MAX_HW_UNITS != ADC_SINGLE_HWUNIT)
  do
  {
  #endif /* (ADC_MAX_HW_UNITS != ADC_SINGLE_HWUNIT) */
    LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                               /* PRQA S 2824 # JV-01 */
    /* Read the user base configuration register of the hardware unit */
    LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                /* PRQA S 2814 # JV-01 */
    LulSgLoopCount = (uint32)LpHwUnitConfig->ucSgUnitCount;
    while (LulSgLoopCount != 0UL)
    {
      /* Decrement counter */
      LulSgLoopCount--;

      LucSgUnitId = Adc_GpSgUnitConfig[LucSgUnitIndex].ucSgUnitId;                                                      /* PRQA S 2824 # JV-01 */
      LpSgUnitData = &Adc_GpSgUnitRamData[LucSgUnitIndex];                                                              /* PRQA S 2824 # JV-01 */
      /* Get the register pointing to SG unit mapped */
      LpSGRegisters = &LpAdcRegisters->aaADCXnSG[LucSgUnitId];                                                          /* PRQA S 2814, 2934 # JV-01, JV-01 */
      /* Check if the requested hardware unit is busy */
      if ((ADC_REG_BYTE_INIT != (uint8)(LpSGRegisters->ucADCXnSGSRx & ADC_SGACT_STATUS)) ||                             /* PRQA S 2844 # JV-01 */
          (ADC_FALSE != LpSgUnitData->blSgUnitStatus))                                                                  /* PRQA S 2814 # JV-01 */
      {
        /* Report Error to DET */
        ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_DEINIT_SID, ADC_E_BUSY);
        LblDetErrFlag = ADC_TRUE;
        /* Exit from the loop */
        LulSgLoopCount = 0UL;
      } /* else: No action required */
      /* Increment SG unit index */
      LucSgUnitIndex++;                                                                                                 /* PRQA S 3383 # JV-01 */
    } /* end of while (LulSgLoopCount != 0UL) */
  #if (ADC_MAX_HW_UNITS != ADC_SINGLE_HWUNIT)
    /* Increment the loop count to next HW Unit */
    LucHwUnitIndex++;                                                                                                   /* PRQA S 3383 # JV-01 */
  } while ((LucHwUnitIndex < (uint8)ADC_MAX_HW_UNITS) && (ADC_FALSE == LblDetErrFlag));
  #endif /* (ADC_MAX_HW_UNITS != ADC_SINGLE_HWUNIT) */

  if (ADC_FALSE == LblDetErrFlag)
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  {
    #if (ADC_DEV_ERROR_DETECT == STD_ON)
    /* Set the ADC driver as un-Initialized */
    Adc_GblDriverStatus = ADC_UNINITIALIZED;
    #endif /* (ADC_DEV_ERROR_DETECT == STD_ON) */

    /* DeInit position Index is reset */
    LucSgUnitIndex = ADC_COUNT_BYTE_INIT;

    for (LucHwUnitIndex = ADC_VAL_BYTE_INIT; LucHwUnitIndex < (uint8)ADC_MAX_HW_UNITS; LucHwUnitIndex++)                /* PRQA S 2877 # JV-01 */
    {
      /* Read the base configuration register of the hardware unit */
      LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                             /* PRQA S 2824 # JV-01 */
      LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                              /* PRQA S 2814 # JV-01 */

      #if (ADC_ENABLE_ERR_INT == STD_ON)
      /* Check if the Adc error interrupt is used */
      if (ADC_TRUE == LpHwUnitConfig->blInterruptErr)
      {
        /* Disable ADC error interrupt and perform synchronization for INTC2 */
        RH850_SV_SET_ICR_SYNCP(8, LpHwUnitConfig->pErrEicRegAddress, ADC_EIC_EIMK);                                     /* PRQA S 0751, 1006, 2814 # JV-01, JV-01, JV-01 */
      } /* else: No action required */
      #endif /* (ADC_ENABLE_ERR_INT == STD_ON) */

      /* Set all SGACT of all scan groups to 0 */
      LpAdcRegisters->ucADCXnADHALTR = ADC_ADCX_ADHALTR_HALT;                                                           /* PRQA S 2814 # JV-01 */
      /* Reset the registers to power on reset value */
      LpAdcRegisters->ucADCXnSFTCR = ADC_REG_BYTE_INIT;
      LpAdcRegisters->ucADCXnADCR1 = ADC_REG_BYTE_INIT;
      #if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT)
      LpAdcRegisters->ucADCXnADCR2 = ADC_REG_BYTE_INIT;
      #endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT) */
      #if (ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON)
      LpAdcRegisters->ucADCXnTDCR = ADC_REG_BYTE_INIT;
      #endif /* (ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON) */
      #if ((ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) || (ADC_ENABLE_WIRE_BRK == STD_ON))
      LpAdcRegisters->ddADCXnODCR = ADC_ADCX_ODCR_INIT_VALUE;
      #endif /* ((ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) || (ADC_ENABLE_WIRE_BRK == STD_ON)) */
      #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
      LpAdcRegisters->ucADCXnTOCCR = ADC_REG_BYTE_INIT;
      #endif /* (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON) */
      #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
      for (LulLimitRegCount = 0UL; LulLimitRegCount < (uint32)ADC_NUM_OF_LIMIT_TABLE; LulLimitRegCount++)
      {
        /* Load the Lower and Upper Limit Value. */
        LpAdcRegisters->aaADCXnVCULLMTBRy[LulLimitRegCount] = ADC_ADCX_VCULLMTBR_INIT_VALUE;
      }
      LpAdcRegisters->aaADCXnVCLMINTER[ADC_VCLM_1] = ADC_REG_DWORD_INIT;
      LpAdcRegisters->aaADCXnVCLMINTER[ADC_VCLM_2] = ADC_REG_DWORD_INIT;
      LpAdcRegisters->aaADCXnVCLMSCR[ADC_VCLM_1] = ADC_ADCX_VCLMSCR1_ALL_MASK;
      LpAdcRegisters->aaADCXnVCLMSCR[ADC_VCLM_2] = ADC_ADCX_VCLMSCR2_ALL_MASK;
      #endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */
      #if (ADC_ENABLE_ERR == STD_ON)
      LpAdcRegisters->ddADCXnECR = ADC_ADCX_ECR_CLEAR_ALL;
      #endif /* (ADC_ENABLE_ERR == STD_ON) */
      #if (ADC_ENABLE_PARITY_ERR == STD_ON)
      LpAdcRegisters->ddADCXnECR = ADC_ADCX_ECR_PEC;
      #endif /* (ADC_ENABLE_PARITY_ERR == STD_ON) */
      #if (ADC_ENABLE_ADTIMER == STD_ON)
      /* Clearing the ADTPRRx register of scan group 3 */
      LpAdcRegisters->aaADCXnSG[ADC_SCANGROUP_3].ulADCXnADTIPRx = ADC_REG_DWORD_INIT;
      LpAdcRegisters->aaADCXnSG[ADC_SCANGROUP_3].ulADCXnADTPRRx = ADC_ADCX_ADTPRR_INIT_VALUE;
      /* Clearing the ADTPRRx register of scan group 4 */
      LpAdcRegisters->aaADCXnSG[ADC_SCANGROUP_4].ulADCXnADTIPRx = ADC_REG_DWORD_INIT;
      LpAdcRegisters->aaADCXnSG[ADC_SCANGROUP_4].ulADCXnADTPRRx = ADC_ADCX_ADTPRR_INIT_VALUE;
      #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */
      /* Get the number of SG units configured for this HW unit */
      LulSgLoopCount = Adc_GpHwUnitConfig[LucHwUnitIndex].ucSgUnitCount;                                                /* PRQA S 2824 # JV-01 */
      while (LulSgLoopCount != 0UL)
      {
        /* Decrement counter */
        LulSgLoopCount--;

        LpSgUnitConfig = &Adc_GpSgUnitConfig[LucSgUnitIndex];                                                           /* PRQA S 2824 # JV-01 */
        /* Get the SG unit Id */
        LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                       /* PRQA S 2814 # JV-01 */
        LpSGRegisters = &LpAdcRegisters->aaADCXnSG[LucSgUnitId];                                                        /* PRQA S 2934 # JV-01 */
        #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
        /* Check if the Group is mapped for HW configured for interrupt mode */
        if (ADC_INTERRUPT_MODE == LpSgUnitConfig->enFunctionalityModeType)
        {
          /* Disable the interrupt for the SG unit */
          Adc_DisableConvertInterrupt(LucHwUnitIndex, LucSgUnitIndex);
        } /* else: No action required */
        #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

        LpSGRegisters->ucADCXnSGCRx = ADC_REG_BYTE_INIT;                                                                /* PRQA S 2824, 2844 # JV-01, JV-01 */
        LpSGRegisters->ucADCXnSGMCYCRx = ADC_REG_BYTE_INIT;
        LpSGRegisters->usADCXnSGVCPRx = ADC_REG_WORD_INIT;
        /* Increment SG unit index */
        LucSgUnitIndex++;                                                                                               /* PRQA S 3383 # JV-01 */
      } /* end of while (LulSgLoopCount != 0UL) */

      #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
      /* De-initialize the device-specific ADC hardware registers */
      Adc_AdcDeInit(LucHwUnitIndex);
      #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
      #if (ADC_IP_ADCH == STD_ON)
      if (ADC_WAITTIME_DISABLED != LpHwUnitConfig->ucWaitTimeIndex)
      {
        /* DE-INITIALIZATION OF WAIT TIME CONFIGURATION */
        Adc_DeInitWaitTime(LucHwUnitIndex);
      } /* else: No action required */
      #endif /* (ADC_IP_ADCH == STD_ON) */

      /* DE-INITIALIZATION OF VIRTUAL CHANNEL */
      /* Get the number of max virtual channels of this HW unit */
      LulNoOfVirCh = (uint32)Adc_GpHwUnitConfig[LucHwUnitIndex].ucMaxVirtualChannel;                                    /* PRQA S 2824 # JV-01 */
      for (LulChannelLoop = 0UL; LulChannelLoop < LulNoOfVirCh; LulChannelLoop++)
      {
        /* Map the physical channels to the virtual channels */
        LpAdcRegisters->aaADCXnVCR[LulChannelLoop] = ADC_REG_DWORD_INIT;                                                /* PRQA S 2844 # JV-01 */
      }
    } /* end of for (LucHwUnitIndex = ADC_VAL_BYTE_INIT; LucHwUnitIndex < (uint8)ADC_MAX_HW_UNITS; LucHwUnitIndex++) */

    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    for (LucGroup = ADC_VAL_BYTE_INIT; LucGroup < Adc_GucNoOfGroups; LucGroup++)
    {
      /* Disable notifications */
      Adc_GpGroupRamData[LucGroup].blNotifyStatus = ADC_FALSE;                                                          /* PRQA S 2824 # JV-01 */
      /* De-Initialize the buffer status and request */
      #if (ADC_MULTI_CORE_SUPPORT == STD_ON)
      #if (ADC_HW_TRIGGER_API == STD_ON)
      if (LucGroup < (uint8)(Adc_GucNoOfGroups - Adc_GucMaxSwTriggGroups))
      {
        Adc_EnableHardwareTriggerInfo[LucGroup].blBufferLock = ADC_FALSE;
        Adc_EnableHardwareTriggerInfo[LucGroup].blSetRequest = ADC_FALSE;
        Adc_DisableHardwareTriggerInfo[LucGroup].blBufferLock = ADC_FALSE;
        Adc_DisableHardwareTriggerInfo[LucGroup].blSetRequest = ADC_FALSE;
      }
      #endif
      #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
      if (LucGroup < Adc_GucMaxSwTriggGroups)
      {
        Adc_StartGroupConversionInfo[LucGroup].blBufferLock = ADC_FALSE;
        Adc_StartGroupConversionInfo[LucGroup].blSetRequest = ADC_FALSE;
        Adc_StopGroupConversionInfo[LucGroup].blBufferLock = ADC_FALSE;
        Adc_StopGroupConversionInfo[LucGroup].blSetRequest = ADC_FALSE;
      }
      #endif
      #endif /* (ADC_MULTI_CORE_SUPPORT == STD_ON) */
    }
    #endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

    /* DE-INITIALIZATION OF DMA UNITS */
    #if (ADC_ENABLE_DMA_MODE == STD_ON)
    if (ADC_NUM_CHANNEL_ZERO != Adc_GucMaxDmaChannels)
    {
      Adc_DmaDeInit();
    } /* else: No action required */
    #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */

    /* DE-INITIALIZATION OF PIC UNITS */
    #if (ADC_HW_TRIGGER_API == STD_ON)
    Adc_PicDeInit();
    #endif /* (ADC_HW_TRIGGER_API == STD_ON) */

    #if (ADC_IP_C_ADCK == STD_OFF)
    #if ((ADC_IP_ADCH == STD_ON) || (ADC_IP_ADCK == STD_ON))
    #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    /* De-initialize ADC interrupt request select register and perform synchronization for AIR */
    ADC_AIR_ISELR0 = ADC_REG_DWORD_INIT;                                                                                /* PRQA S 0303 # JV-01 */
    (void)ADC_AIR_ISELR0;                                                                                               /* PRQA S 0303 # JV-01 */
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
    #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

    #if (ADC_ENABLE_DMA_MODE == STD_ON)
    /* De-initialize ADC DMA request select register and perform synchronization for AIR */
    ADC_AIR_DSELR0 = ADC_AIR_DSEL_INIT;                                                                                 /* PRQA S 0303 # JV-01 */
    (void)ADC_AIR_DSELR0;                                                                                               /* PRQA S 0303 # JV-01 */
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
    #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
    #endif /* ((ADC_IP_ADCH == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
    #endif /*(ADC_IP_C_ADCK == STD_OFF) */

    /* DE-INITIALIZATION OF ECM UNITS */
    #if (ADC_ENABLE_PARITY_ERR_INT == STD_ON)
    Adc_EcmErrorInterrupt(ADC_FALSE);
    #endif /* (ADC_ENABLE_PARITY_ERR_INT == STD_ON) */
  } /* end of if (ADC_FALSE == LblDetErrFlag) */
    /* else: No action required */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_DEINIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_HwStopGroupConversion
**
** Service ID           : NA
**
** Description          : This internal function shall stop conversion of the
**                        requested ADC Channel group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpGroupRamData, Adc_GpSgUnitRamData,
**                        Adc_GaaHwUnitData
**
** Functions invoked    : ADC_ENTER_CRITICAL_SECTION, Adc_DmaDisable, Adc_HwStopScanGroup,
**                        Adc_DisableConvertInterrupt, Adc_DisableDetection, Adc_PopFromQueue,
**                        Adc_ConfigureGroupForConversion, Adc_SearchAndDelete, Adc_SetStatus, Adc_TrackHoldDisable,
**                        ADC_EXIT_CRITICAL_SECTION, ADC_DET_RUNTIME_ERROR, ADC_DEM_REPORT_ERROR
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_035, ADC_DUD_ACT_035_CRT001, ADC_DUD_ACT_035_CRT002,
** Reference ID         : ADC_DUD_ACT_035_CRT003, ADC_DUD_ACT_035_CRT004, ADC_DUD_ACT_035_GBL001,
** Reference ID         : ADC_DUD_ACT_035_GBL002, ADC_DUD_ACT_035_GBL003, ADC_DUD_ACT_035_GBL004
***********************************************************************************************************************/
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_PRIVATE_CODE) Adc_HwStopGroupConversion(const Adc_GroupType LddGroup)                                    /* PRQA S 1532 # JV-01 */
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  P2VAR(volatile Adc_HwUnitDataType, AUTOMATIC, ADC_VAR_NO_INIT) LpHwUnitData;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;

  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  boolean LblDetErrFlag;
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  uint8 LucHwUnitIndex;
  uint8 LucSgUnitIndex;
  uint8 LucSgUnitId;

  #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
  /* Local variable to store the next conversion group number */
  Adc_GroupType LddNextGroup;
  #endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */
  /* The local variable that stores whether the SG unit needs to be stopped*/
  boolean LblStopNeeded;
  /* The local variable to store whether the SG unit stop has timed out */
  boolean LblHwTimedOut;
  #if (ADC_ENABLE_DMA_MODE == STD_ON)
  /* The local variable to store whether the DMA stop has timed out */
  boolean LblDmaTimedOut;

  /* Initialize the DMA stop timeout flag to ADC_FALSE */
  LblDmaTimedOut = ADC_FALSE;
  #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
  /* Initialize the SG unit stop timeout flag to ADC_FALSE */
  LblHwTimedOut = ADC_FALSE;
  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  /* Initialize the Det error flag */
  LblDetErrFlag = ADC_FALSE;
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  /* Initialize the flag indicating that the SG unit needs to be stopped */
  LblStopNeeded = ADC_FALSE;

  /* Get the pointer to Group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the index of HW unit */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  /* Get the SG unit to which the channel group is mapped */
  LucSgUnitIndex = LpGroup->ucSgUnitIndex;
  /* Get the SG unit configuration */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LucSgUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the pointer to the runtime data of the SG unit to which the requested group belongs */
  LpSgUnitData = &Adc_GpSgUnitRamData[LucSgUnitIndex];                                                                  /* PRQA S 2824 # JV-01 */
  /* Get the pointer to the runtime data of the HW unit to which the requested group belongs */
  LpHwUnitData = &Adc_GaaHwUnitData[LucHwUnitIndex];                                                                    /* PRQA S 2934 # JV-01 */
  /* Get the SG unit ID to which the requested group is configured */
  LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                             /* PRQA S 2814 # JV-01 */
  /* Get the pointer to the runtime data of the requested group */
  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */

  /* Enter the critical section protection */
  ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

  #if (ADC_TRACK_AND_HOLD == STD_ON)
  /* Check if the requested group is T&H */
  if (ADC_TH_DISABLED != LpGroup->ucTrackAndHoldGroup)
  {
    /* Check if other T&H group is not active in the same SG unit */
    if ((ADC_FALSE == LpSgUnitData->blSgUnitStatus) ||                                                                  /* PRQA S 2814 # JV-01 */
        (LpSgUnitData->ddCurrentConvGroup == LddGroup) ||
        (ADC_TH_DISABLED == Adc_GpGroupConfig[LpSgUnitData->ddCurrentConvGroup].ucTrackAndHoldGroup))
    {
      /* Update T&H status to disable T&H of this SG unit */
      LpHwUnitData->ucTrackHoldStatus &= (uint8)~(1U << LucSgUnitId);                                                   /* PRQA S 2844 # JV-01 */
    } /* else: No action required */
  } /* else: No action required */
  #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

  /* Check if the requested group can be stopped */
  if (ADC_IDLE == LpGroupData->enGroupStatus)                                                                           /* PRQA S 2814 # JV-01 */
  {
    #if (ADC_TRACK_AND_HOLD == STD_ON)
    /* If the requested group is T&H, no DET error as T&H sampling needs to be stopped */
    if (ADC_TH_DISABLED == LpGroup->ucTrackAndHoldGroup)
    #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */
    {
      #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
      /* Check if the requested group is not queued */
      if (ADC_FALSE == LpGroupData->blGrpPresent)
      #endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */
      {
        #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
        LblDetErrFlag = ADC_TRUE;
        #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
                   (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
      } /* else: No action required */
    } /* else: No action required */
  } /* end of if (ADC_IDLE == LpGroupData->enGroupStatus) */
  else
  {
    /* Check if the requested group is current group */
    if (LpSgUnitData->ddCurrentConvGroup == LddGroup)                                                                   /* PRQA S 2814 # JV-01 */
    {
      LblStopNeeded = ADC_TRUE;
    } /* else: No action required */
  }

  /* Check if the SG unit needs to be stopped */
  if (ADC_TRUE == LblStopNeeded)
  {
    #if (ADC_ENABLE_DMA_MODE == STD_ON)
    if (ADC_TRUE == LpGroup->blEnableDmaTransfer)
    {
      LblDmaTimedOut = Adc_DmaDisable(LddGroup);
    } /* else: No action required */
    #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */

    /* Stop the Scan Group */
    LblHwTimedOut = Adc_HwStopScanGroup(LddGroup, ADC_TRUE);

    /* Change SG unit status to inactive */
    LpSgUnitData->blSgUnitStatus = ADC_FALSE;
    LpHwUnitData->ucSgUnitStatus &= (uint8)~(1U << LucSgUnitId);                                                        /* PRQA S 2814, 2844 # JV-01, JV-01 */

    /* Check if scan group is stopped successfully? */
    if (ADC_FALSE == LblHwTimedOut)
    {
      #if ((ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON) || \
           (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) || (ADC_ENABLE_WIRE_BRK == STD_ON))
      /* Disable self-diagnosis pin level and wiring break detection if they are configured */
      Adc_DisableDetection(LddGroup);
      #endif

      #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
      /* Check if the Group is mapped for HW configured for interrupt mode */
      if (ADC_INTERRUPT_MODE == LpSgUnitConfig->enFunctionalityModeType)
      {
        #if (ADC_ENABLE_DMA_MODE == STD_ON)
        /* Check if the requested group does not use DMA transfer */
        if (ADC_FALSE == LpGroup->blEnableDmaTransfer)
        #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
        {
          /* Enter the critical section protection */
          ADC_ENTER_CRITICAL_SECTION(ADC_INTERRUPT_CONTROL_PROTECTION);
          /* Disable interrupt for SG unit to which group is mapped */
          Adc_DisableConvertInterrupt(LucHwUnitIndex, LucSgUnitIndex);
          /* Exit the critical section protection */
          ADC_EXIT_CRITICAL_SECTION(ADC_INTERRUPT_CONTROL_PROTECTION);
        } /* else: No action required */
      } /* end of if (ADC_INTERRUPT_MODE == LpSgUnitConfig->enFunctionalityModeType) */
        /* else: No action required */
      #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

      #if (ADC_ENABLE_DMA_MODE == STD_ON)
      /* Only start group from queue when DMA is disabled successfully */
      if (ADC_TRUE == LblDmaTimedOut)
      {
        /* Merge the timed out status */
        LblHwTimedOut = ADC_TRUE;
      }
      else
      #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
      {
        /* Group Priority is enabled or queue is enabled */
        #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
        /* Fetch the next group for conversion if the queue is not empty */
        LddNextGroup = Adc_PopFromQueue(LucSgUnitIndex);
        if (ADC_INVALID_GROUP != LddNextGroup)
        {
          Adc_ConfigureGroupForConversion(LddNextGroup);
        } /* else: No action required */
        #endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */
      }
    } /* end of if (ADC_FALSE == LblHwTimedOut) */
      /* else: No action required */
  } /* end of if (ADC_TRUE == LblStopNeeded) */
  else
  {
    #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
         (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
    /* Check if no DET error occurs */
    if (ADC_FALSE == LblDetErrFlag)
    #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
               (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
    {
      #if (ADC_TRACK_AND_HOLD == STD_ON)
      /* Check if T&H sampling can be stopped */
      if ((ADC_TH_SAMPLING == LpHwUnitData->ucTrackHoldStatus) && ((uint8)0U == LpHwUnitData->ucSgUnitStatus))
      {
        /* Stop T&H sampling */
        Adc_TrackHoldDisable(LddGroup);
      } /* else: No action required */
      #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

      #if ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON))
      if (ADC_TRUE == LpGroupData->blGrpPresent)
      {
        /* Search and delete the requested group from the queue */
        Adc_SearchAndDelete(LddGroup);
      } /* else: No action required */
      #endif /* ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)) */
    } /* end of if (ADC_FALSE == LblDetErrFlag) */
      /* else: No action required */
  }

  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  /* Check if no DET error occurs */
  if (ADC_FALSE == LblDetErrFlag)
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  {
    /* Set the group status as idle */
    Adc_SetStatus(LddGroup, ADC_IDLE);

    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* Store disabled notification into RAM */
    LpGroupData->blNotifyStatus = ADC_FALSE;
    #endif
  } /* else: No action required */

  /* Exit the critical section protection */
  ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

  #if ((ADC_DEV_ERROR_DETECT == STD_ON) || \
       (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION))
  /* Check if DET error occurs */
  if (ADC_TRUE == LblDetErrFlag)
  {
    /* Report Error to DET */
    ADC_DET_RUNTIME_ERROR(ADC_MODULE_ID, ADC_INSTANCE_ID, ADC_STOP_GROUP_CONVERSION_SID, ADC_E_IDLE);
  }
  else
  #endif /* ((ADC_DEV_ERROR_DETECT == STD_ON) || 
             (ADC_AR_VERSION == ADC_AR_431_VERSION) || (ADC_AR_VERSION == ADC_AR_R22_11_VERSION)) */
  {
    /* Check if DEM error occurs */
    if (ADC_TRUE == LblHwTimedOut)
    {
      /* Reporting to DEM when timeout cause by hardware error */
      ADC_DEM_REPORT_ERROR(ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
    } /* else: No action required */
  }
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_Isr
**
** Service ID           : NA
**
** Description          : This internal function shall be an interrupt service
**                        routine for ADC Driver.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LucHwUnitIndex, LucSgUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpSgUnitRamData, Adc_GpGroupConfig, Adc_GpGroupRamData
**
** Functions invoked    : ADC_ENTER_CRITICAL_SECTION, Adc_GroupCompleteMode, Adc_ChannelCompleteMode,
**                        Adc_CheckAndCopyResultData, ADC_EXIT_CRITICAL_SECTION, ADC_DEM_REPORT_ERROR,
**                        Adc_CallGroupNotify, Adc_ReportError
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_036, ADC_DUD_ACT_036_CRT001, ADC_DUD_ACT_036_CRT002,
** Reference ID         : ADC_DUD_ACT_036_GBL001, ADC_DUD_ACT_036_ERR001
***********************************************************************************************************************/
#if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_CODE_FAST) Adc_Isr(const uint8 LucHwUnitIndex, const uint8 LucSgUnitIndex)                               /* PRQA S 1532 # JV-01 */
{
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;                                      /* PRQA S 3678 # JV-01 */
  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
  uint8 LucChannelCount;
  /* Local variable to store the group number */
  Adc_GroupType LddGroup;
  /* Hardware stop timeout flag */
  boolean LblHwTimedOut;
  /* Read data available flag */
  boolean LblDataAvailable;

  /* Read the current conversion group number */
  LddGroup = Adc_GpSgUnitRamData[LucSgUnitIndex].ddCurrentConvGroup;                                                    /* PRQA S 2824 # JV-01 */
  /* Read the group's runtime data pointer */
  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */
  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  /* Read the group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  #endif

  /* Enter the critical section protection */
  ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  /* Load the current group's first channel buffer pointer */
  if (ADC_GROUP_REPL_SUSPEND_RESUME == LpGroup->enGroupReplacement)                                                     /* PRQA S 2814 # JV-01 */
  {
    LucChannelCount = LpGroupData->ucChannelsCompleted;                                                                 /* PRQA S 2814 # JV-01 */
  }
  else
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
  {
    LucChannelCount = LpGroupData->ucChannelCount;                                                                      /* PRQA S 2814 # JV-01 */
  }

  /* Read conversion result data */
  LblDataAvailable = Adc_CheckAndCopyResultData(LddGroup, LucChannelCount);
  if (ADC_TRUE == LblDataAvailable)
  {
    #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
    /* Initialize the timeout flag */
    LblHwTimedOut = ADC_FALSE;
    if (ADC_GROUP_REPL_SUSPEND_RESUME == LpGroup->enGroupReplacement)
    {
      /* Check whether ucIsrSkipCount is greater than 0 */
      if (LpGroupData->ucIsrSkipCount > ADC_COUNT_BYTE_INIT)
      {
        LpGroupData->ucIsrSkipCount--;                                                                                  /* PRQA S 3384, 3387 # JV-01, JV-01 */
      }
      else
      {
        /* Invoke channel complete function */
        LblHwTimedOut = Adc_ChannelCompleteMode(LddGroup, LucHwUnitIndex);
      }
    }
    else
    #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
    {
      /* Invoke group complete function */
      LblHwTimedOut = Adc_GroupCompleteMode(LddGroup, LucHwUnitIndex);
    }
  } /* end of if (ADC_TRUE == LblDataAvailable) */
    /* else: No action required */

  /* Exit the critical section protection */
  ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

  if (ADC_TRUE == LblDataAvailable)
  {
    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* Call to notification function */
    Adc_CallGroupNotify(LddGroup);
    #endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

    if (ADC_TRUE == LblHwTimedOut)
    {
      /* Reporting to DEM when timeout cause by hardware error */
      ADC_DEM_REPORT_ERROR(ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
    } /* else: No action required */
  } /* else: No action required */

  #if ((ADC_ENABLE_ERR == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON))
  /* Report errors to Dem and invokes error notification callback functions, if any errors are detected */
  Adc_ReportError(LddGroup);
  #endif
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

/***********************************************************************************************************************
** Function Name        : Adc_ChannelCompleteMode
**
** Service ID           : NA
**
** Description          : This internal function shall be invoked from ADC ISR
**                        for servicing the groups configured in suspend/resume
**                        mode.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LddGroup, LucHwUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : boolean
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpHwUnitConfig, Adc_GpGroupRamData,
**                        Adc_GpSgUnitRamData, Adc_GaaHwUnitData
**
** Functions invoked    : Adc_SetStatus, Adc_ConfigureGroupForConversion, Adc_PopFromQueue, Adc_HwStopScanGroup,
**                        Adc_DisableDetection, Adc_DisableConvertInterrupt, ADC_ENTER_CRITICAL_SECTION,
**                        ADC_EXIT_CRITICAL_SECTION
**
** Registers Used       : ADCXnADTENDCRx
**
** Reference ID         : ADC_DUD_ACT_037, ADC_DUD_ACT_037_GBL001, ADC_DUD_ACT_037_GBL002,
** Reference ID         : ADC_DUD_ACT_037_GBL003, ADC_DUD_ACT_037_GBL004, ADC_DUD_ACT_037_GBL005,
** Reference ID         : ADC_DUD_ACT_037_GBL006, ADC_DUD_ACT_037_GBL007, ADC_DUD_ACT_037_GBL008,
** Reference ID         : ADC_DUD_ACT_037_GBL009, ADC_DUD_ACT_037_GBL011, ADC_DUD_ACT_037_GBL012,
** Reference ID         : ADC_DUD_ACT_037_REG003, ADC_DUD_ACT_037_CRT001, ADC_DUD_ACT_037_CRT002,
** Reference ID         : ADC_DUD_ACT_037_GBL013
***********************************************************************************************************************/
#if ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON))
#if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(boolean, ADC_CODE_FAST) Adc_ChannelCompleteMode(const Adc_GroupType LddGroup, const uint8 LucHwUnitIndex)
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  #if (ADC_ENABLE_ADTIMER == STD_ON)
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */
  uint8 LucSgUnitIndex;
  /* Local variable to store Scan Group ID */
  uint8 LucSgUnitId;
  #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
  Adc_GroupType LddNextGroup;
  #endif
  boolean LblHwTimedOut;
  uint8 LucChannelCount;

  /* Initialize scan group stop timeout flag to ADC_FALSE */
  LblHwTimedOut = ADC_FALSE;
  /* Read the HW unit of the group */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Read the group data pointer */
  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */

  /* Get the SG unit to which the channel group is mapped */
  LucSgUnitIndex = LpGroup->ucSgUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */

  /* Initialize SG unit RAM data to a local pointer */
  LpSgUnitData = &Adc_GpSgUnitRamData[LucSgUnitIndex];                                                                  /* PRQA S 2824 # JV-01 */

  /* Get the SG unit which is configured for this group */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LucSgUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the SG unit ID */
  LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                             /* PRQA S 2814 # JV-01 */

  #if (ADC_ENABLE_ADTIMER == STD_ON)
  /* Read the base address of the hardware unit */
  LpAdcRegisters = Adc_GpHwUnitConfig[LucHwUnitIndex].pHwUnitBaseAddress;                                               /* PRQA S 2824 # JV-01 */
  #endif

  /* Update the number of channels that completed conversion */
  LpGroupData->ucChannelsCompleted++;                                                                                   /* PRQA S 2814, 3383, 3387 # JV-01, JV-01, JV-01 */

  /* Get the number of channels enabled in the group */
  LucChannelCount = LpGroupData->ucChannelCount;

  #if (ADC_ENABLE_STREAMING == STD_ON)
  /* Check if the result access mode is Streaming */
  if (ADC_ACCESS_MODE_STREAMING == LpGroup->enGroupAccessMode)
  {
    /* Check if the conversion of all channels in the group is completed */
    if (LpGroupData->ucChannelsCompleted == LucChannelCount)
    {
      /* Reset the number of completed channels to zero */
      LpGroupData->ucChannelsCompleted = ADC_COUNT_BYTE_INIT;
      /* Check if the conversion of all the samples are completed */
      if (LpGroupData->ucSamplesCompleted == LpGroup->ddNumberofSamples)
      {
        /* Reset the number of completed sample to zero. */
        LpGroupData->ucSamplesCompleted = ADC_COUNT_BYTE_INIT;
      } /* else: No action required */
      /* Update the completed conversion samples */
      LpGroupData->ucSamplesCompleted++;                                                                                /* PRQA S 3383, 3387 # JV-01, JV-01 */

      /* Check if the conversion of all the samples are completed */
      if (LpGroupData->ucSamplesCompleted == LpGroup->ddNumberofSamples)
      {
        /* If the conversion mode is circular buffer, reload the result buffer pointer */
        if (ADC_STREAM_BUFFER_CIRCULAR == LpGroup->enStreamBufferMode)
        {
          LpGroupData->pBuffer = LpGroupData->pChannelBuffer;
        } /* else: No action required */

        /* Set group status as conversion completed */
        Adc_SetStatus(LddGroup, ADC_STREAM_COMPLETED);
      }
      else
      {
        /* Reload the result buffer pointer */
        LpGroupData->pBuffer = &LpGroupData->pChannelBuffer[LpGroupData->ucSamplesCompleted];                           /* PRQA S 0404 # JV-01 */

        /* Set group status as conversion completed */
        Adc_SetStatus(LddGroup, ADC_COMPLETED);
      }

      /* Set the flag indicating Adc_ReadGroup or Adc_GetStreamLastPointer should be called */
      LpGroupData->blResultRead = ADC_FALSE;
    } /* end of if (LpGroupData->ucChannelsCompleted == LucChannelCount) */
      /* else: No action required */
  } /* end of if (ADC_ACCESS_MODE_STREAMING == LpGroup->enGroupAccessMode) */
  else
  #endif /* (ADC_ENABLE_STREAMING == STD_ON) */
  {
    /* Check if the conversion of all channels in the group is completed */
    if (LpGroupData->ucChannelsCompleted == LucChannelCount)
    {
      /* Reset the number of completed channels to zero. */
      LpGroupData->ucChannelsCompleted = ADC_COUNT_BYTE_INIT;
      /* Update the completed conversion samples */
      LpGroupData->ucSamplesCompleted = ADC_BYTE_ONE;
      /* Set group status as conversion completed */
      Adc_SetStatus(LddGroup, ADC_STREAM_COMPLETED);
      /* Set the flag indicating Adc_ReadGroup or Adc_GetStreamLastPointer should be called */
      LpGroupData->blResultRead = ADC_FALSE;
    } /* else: No action required */
  }

  /* Check if the conversion of all the samples are completed */
  if (ADC_STREAM_COMPLETED == LpGroupData->enGroupStatus)
  {
    /* Check if the conversion is implicitly stopped */
    if (ADC_TRUE == LpGroup->blImplicitlyStopped)
    {
      /* Stop the conversion of the SG unit */
      LblHwTimedOut = Adc_HwStopScanGroup(LddGroup, ADC_FALSE);

      #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
      /* Check if the Group is mapped for HW configured for interrupt mode */
      if (ADC_INTERRUPT_MODE == LpSgUnitConfig->enFunctionalityModeType)
      {
        /* Enter the critical section protection */
        ADC_ENTER_CRITICAL_SECTION(ADC_INTERRUPT_CONTROL_PROTECTION);

        /* Disable interrupt for SG unit to which group is mapped */
        Adc_DisableConvertInterrupt(LucHwUnitIndex, LucSgUnitIndex);

        /* Exit the critical section protection */
        ADC_EXIT_CRITICAL_SECTION(ADC_INTERRUPT_CONTROL_PROTECTION);
      } /* else: No action required */
      #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

      #if ((ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON) || \
           (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) || (ADC_ENABLE_WIRE_BRK == STD_ON))
      /* Disable self-diagnosis pin level and wiring break detection if they are configured */
      Adc_DisableDetection(LddGroup);
      #endif

      /* Change SG unit status to inactive */
      LpSgUnitData->blSgUnitStatus = ADC_FALSE;                                                                         /* PRQA S 2814 # JV-01 */
      Adc_GaaHwUnitData[LucHwUnitIndex].ucSgUnitStatus &= ~(1U << LucSgUnitId);                                         /* PRQA S 2844 # JV-01 */

      #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
      /* Check if SG is stopped */
      if (ADC_FALSE == LblHwTimedOut)
      {
        /* Fetch the next group for conversion if the queue is not empty */
        LddNextGroup = Adc_PopFromQueue(LucSgUnitIndex);
        if (ADC_INVALID_GROUP != LddNextGroup)
        {
          Adc_ConfigureGroupForConversion(LddNextGroup);
        } /* else: No action required */
      } /* else: No action required */
      #endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */
    } /* end of if (ADC_TRUE == LpGroup->blImplicitlyStopped) */
    else
    {
      #if (ADC_ENABLE_ADTIMER == STD_ON)
      /* If AD timer is enabled and group is one-shot, just stop AD timer */
      if ((ADC_TRUE == LpGroup->blAdcEnableAdTimerTriggMode) && (ADC_CONV_MODE_ONESHOT == LpGroup->enGroupConvMode))
      {
        LpAdcRegisters->aaADCXnSG[LucSgUnitId].ucADCXnADTENDCRx = ADC_ADCX_ADTENDCR_ADTEND;                             /* PRQA S 2814, 2844 # JV-01, JV-01 */
      } /* else: No action required */
      #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */
    }
  } /* end of if (ADC_STREAM_COMPLETED == LpGroupData->enGroupStatus) */
    /* else: No action required */

  return LblHwTimedOut;
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
#endif /* ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON)) */

/***********************************************************************************************************************
** Function Name        : Adc_GroupCompleteMode
**
** Service ID           : NA
**
** Description          : This internal function shall be invoked from ADC ISR
**                        for servicing the groups configured in scan operation
**                        mode.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LddGroup, LucHwUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : boolean
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpHwUnitConfig, Adc_GpGroupRamData,
**                        Adc_GpSgUnitRamData, Adc_GaaHwUnitData, Adc_GucMaxSwTriggGroups
**
** Functions invoked    : Adc_ConfigureGroupForConversion, Adc_DisableConvertInterrupt, Adc_DisableDetection,
**                        ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION, Adc_HwStopScanGroup,
**                        Adc_PicClearHwTrigger, Adc_PopFromQueue, Adc_SetStatus
**
** Registers Used       : ADCXnADTENDCRx
**
** Reference ID         : ADC_DUD_ACT_038, ADC_DUD_ACT_038_GBL001, ADC_DUD_ACT_038_GBL002,
** Reference ID         : ADC_DUD_ACT_038_GBL003, ADC_DUD_ACT_038_GBL004, ADC_DUD_ACT_038_GBL005,
** Reference ID         : ADC_DUD_ACT_038_GBL006, ADC_DUD_ACT_038_GBL008, ADC_DUD_ACT_038_REG003,
** Reference ID         : ADC_DUD_ACT_038_CRT001, ADC_DUD_ACT_038_CRT002
***********************************************************************************************************************/
#if ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON))

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(boolean, ADC_CODE_FAST) Adc_GroupCompleteMode(const Adc_GroupType LddGroup, const uint8 LucHwUnitIndex)
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  #if (ADC_ENABLE_ADTIMER == STD_ON)
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */
  P2VAR(volatile Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  uint8 LucSgUnitId;
  uint8 LucSgUnitIndex;
  #if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
      ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
  Adc_GroupType LddNextGroup;
  #endif
  boolean LblHwTimedOut;

  /* Initialize scan group stop timeout flag to ADC_FALSE */
  LblHwTimedOut = ADC_FALSE;
  /* Read the hardware unit of the group */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Read the group data pointer */
  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */

  /* Get the SG unit to which the channel group is mapped */
  LucSgUnitIndex = LpGroup->ucSgUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */

  /* Initialize HW RAM data to a local pointer */
  LpSgUnitData = &Adc_GpSgUnitRamData[LucSgUnitIndex];                                                                  /* PRQA S 2824 # JV-01 */

  /* Get the SG unit which is configured for this group */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LucSgUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the SG unit Id */
  LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                             /* PRQA S 2814 # JV-01 */

  #if (ADC_ENABLE_ADTIMER == STD_ON)
  /* Read the base address of the hardware unit */
  LpAdcRegisters = Adc_GpHwUnitConfig[LucHwUnitIndex].pHwUnitBaseAddress;                                               /* PRQA S 2824 # JV-01 */
  #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */

  /* Check if the conversion of all the samples are completed */
  if (LpGroupData->ucSamplesCompleted == LpGroup->ddNumberofSamples)                                                    /* PRQA S 2814 # JV-01 */
  {
    LpGroupData->ucSamplesCompleted = ADC_COUNT_BYTE_INIT;
  } /* else: No action required */
  /* Update the completed conversion samples */
  LpGroupData->ucSamplesCompleted++;                                                                                    /* PRQA S 3383, 3387 # JV-01, JV-01 */

  #if (ADC_ENABLE_STREAMING == STD_ON)
  /* Check if the result access mode is Streaming */
  if (ADC_ACCESS_MODE_STREAMING == LpGroup->enGroupAccessMode)
  {
    /* Update the buffer pointer to point to the next sample */
    LpGroupData->pBuffer++;                                                                                             /* PRQA S 3387 # JV-01 */
    /* Check if the conversion of all the samples are completed */
    if (LpGroupData->ucSamplesCompleted == LpGroup->ddNumberofSamples)
    {
      /* If the conversion mode is circular buffer, reload the result buffer pointer */
      if (ADC_STREAM_BUFFER_CIRCULAR == LpGroup->enStreamBufferMode)
      {
        LpGroupData->pBuffer = LpGroupData->pChannelBuffer;
      } /* else: No action required */

      /* Set group status as conversion completed */
      Adc_SetStatus(LddGroup, ADC_STREAM_COMPLETED);
    }
    else
    {
      /* Set group status as conversion completed */
      Adc_SetStatus(LddGroup, ADC_COMPLETED);
    }

    /* Set the flag indicating Adc_ReadGroup or Adc_GetStreamLastPointer should be called */
    LpGroupData->blResultRead = ADC_FALSE;
  } /* end of if (ADC_ACCESS_MODE_STREAMING == LpGroup->enGroupAccessMode) */
  else
  #endif /* (ADC_ENABLE_STREAMING == STD_ON) */
  {
    /* Set group status as conversion completed */
    Adc_SetStatus(LddGroup, ADC_STREAM_COMPLETED);
    /* Set the flag indicating Adc_ReadGroup or Adc_GetStreamLastPointer should be called */
    LpGroupData->blResultRead = ADC_FALSE;
  }

  /* Check if the conversion of all the samples are completed */
  if (ADC_STREAM_COMPLETED == LpGroupData->enGroupStatus)
  {
    /* Check if the conversion is implicitly stopped */
    if (ADC_TRUE == LpGroup->blImplicitlyStopped)
    {
      /* Stop the conversion of the SG unit */
      LblHwTimedOut = Adc_HwStopScanGroup(LddGroup, ADC_FALSE);

      #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
      /* Check if the Group is mapped for HW configured for interrupt mode */
      if (ADC_INTERRUPT_MODE == LpSgUnitConfig->enFunctionalityModeType)
      {
        /* Enter the critical section protection */
        ADC_ENTER_CRITICAL_SECTION(ADC_INTERRUPT_CONTROL_PROTECTION);

        /* Disable interrupt for SG unit to which group is mapped */
        Adc_DisableConvertInterrupt(LucHwUnitIndex, LucSgUnitIndex);

        /* Exit the critical section protection */
        ADC_EXIT_CRITICAL_SECTION(ADC_INTERRUPT_CONTROL_PROTECTION);
      } /* else: No action required */
      #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

      #if (ADC_ENABLE_PIC_TSEL == STD_ON)
      /* Check if the conversion is HW Triggered */
      if (LddGroup >= Adc_GucMaxSwTriggGroups)
      {
        /* Clear to avoid conversion on next HW trigger */
        Adc_PicClearHwTrigger(LddGroup);
      } /* else: No action required */
      #endif /* (ADC_HW_TRIGGER_API == STD_ON) */

      #if ((ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON) || \
           (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) || (ADC_ENABLE_WIRE_BRK == STD_ON))
      /* Disable self-diagnosis pin level and wiring break detection if they are configured */
      Adc_DisableDetection(LddGroup);
      #endif

      /* Change SG unit status to inactive */
      LpSgUnitData->blSgUnitStatus = ADC_FALSE;                                                                         /* PRQA S 2814 # JV-01 */
      Adc_GaaHwUnitData[LucHwUnitIndex].ucSgUnitStatus &= ~(1U << LucSgUnitId);                                         /* PRQA S 2844 # JV-01 */

      #if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
           ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
      /* Check if SG is stopped */
      if (ADC_FALSE == LblHwTimedOut)
      {
        /* Fetch the next group for conversion if the queue is not empty */
        LddNextGroup = Adc_PopFromQueue(LucSgUnitIndex);
        if (ADC_INVALID_GROUP != LddNextGroup)
        {
          Adc_ConfigureGroupForConversion(LddNextGroup);
        } /* else: No action required */
      } /* else: No action required */
      #endif
    } /* end of if (ADC_TRUE == LpGroup->blImplicitlyStopped) */
    else
    {
      #if (ADC_ENABLE_ADTIMER == STD_ON)
      /* If AD timer is enabled and group is one-shot, just stop AD timer */
      if ((ADC_TRUE == LpGroup->blAdcEnableAdTimerTriggMode) && (ADC_CONV_MODE_ONESHOT == LpGroup->enGroupConvMode))
      {
        LpAdcRegisters->aaADCXnSG[LucSgUnitId].ucADCXnADTENDCRx = ADC_ADCX_ADTENDCR_ADTEND;                             /* PRQA S 2814, 2844 # JV-01, JV-01 */
      } /* else: No action required */
      #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */
    }
  } /* end of if (ADC_STREAM_COMPLETED == LpGroupData->enGroupStatus) */
    /* else: No action required */

  return LblHwTimedOut;
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON)) */

/***********************************************************************************************************************
** Function Name        : Adc_ConfigureGroupForConversion
**
** Service ID           : NA
**
** Description          : This internal function shall configures the requested
**                        group for conversion.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpHwUnitConfig, Adc_GpSgUnitConfig, Adc_GpSgUnitRamData,
**                        Adc_GpGroupRamData, Adc_GucMaxSwTriggGroups, Adc_GpChannelToDisableEnable,
**                        Adc_GpChannelToGroup, Adc_GaaHwUnitData
**
** Functions invoked    : Adc_PwmDiagReadData, ADC_ENTER_CRITICAL_SECTION, Adc_DisableConvertInterrupt,
**                        Adc_EnableConvertInterrupt, ADC_EXIT_CRITICAL_SECTION, Adc_DmaEnable, Adc_SetStatus,
**                        Adc_PwmDiagEnable, Adc_TrackHoldEnable
**
** Registers Used       : ADCXnECR, ADCXnDIRj, ADCXnSGMCYCRx, ADCXnTDCR, ADCXnODCR, ADCXnSGVCPRx, ADCXnVCRj,
**                        ADCXnADTIPRx, ADCXnADTPRRx, ADCXnSGCRx, ADCXnADTSTCRx, ADCXnSGSTCRx
**
** Reference ID         : ADC_DUD_ACT_039, ADC_DUD_ACT_039_CRT001, ADC_DUD_ACT_039_CRT002,
** Reference ID         : ADC_DUD_ACT_039_GBL001, ADC_DUD_ACT_039_GBL003, ADC_DUD_ACT_039_GBL004,
** Reference ID         : ADC_DUD_ACT_039_GBL005, ADC_DUD_ACT_039_GBL006, ADC_DUD_ACT_039_GBL007,
** Reference ID         : ADC_DUD_ACT_039_GBL008, ADC_DUD_ACT_039_GBL009, ADC_DUD_ACT_039_GBL010,
** Reference ID         : ADC_DUD_ACT_039_GBL011, ADC_DUD_ACT_039_GBL012, ADC_DUD_ACT_039_GBL015,
** Reference ID         : ADC_DUD_ACT_039_GBL016, ADC_DUD_ACT_039_GBL017, ADC_DUD_ACT_039_GBL018,
** Reference ID         : ADC_DUD_ACT_039_GBL019, ADC_DUD_ACT_039_GBL020, ADC_DUD_ACT_039_GBL021,
** Reference ID         : ADC_DUD_ACT_039_GBL022, ADC_DUD_ACT_039_REG007, ADC_DUD_ACT_039_REG009,
** Reference ID         : ADC_DUD_ACT_039_REG012, ADC_DUD_ACT_039_REG013, ADC_DUD_ACT_039_REG014,
** Reference ID         : ADC_DUD_ACT_039_REG015, ADC_DUD_ACT_039_REG016, ADC_DUD_ACT_039_REG017,
** Reference ID         : ADC_DUD_ACT_039_REG018, ADC_DUD_ACT_039_REG019, ADC_DUD_ACT_039_REG021,
** Reference ID         : ADC_DUD_ACT_039_REG022, ADC_DUD_ACT_039_REG023, ADC_DUD_ACT_039_REG024,
** Reference ID         : ADC_DUD_ACT_039_REG025, ADC_DUD_ACT_039_REG026, ADC_DUD_ACT_039_REG027,
** Reference ID         : ADC_DUD_ACT_039_REG028, ADC_DUD_ACT_039_REG029, ADC_DUD_ACT_039_REG030,
** Reference ID         : ADC_DUD_ACT_039_REG031
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_ConfigureGroupForConversion(const Adc_GroupType LddGroup)                       /* PRQA S 3006 # JV-01 */
{
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  /* Pointer to the hardware unit configuration */
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2VAR(volatile Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  P2VAR(volatile Adc_SGRegType, AUTOMATIC, REGSPACE) LpSGRegisters;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;

  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  uint32 LulBufferOffset;
  #endif
  uint8 LucChannelToGroupIndex;
  uint8 LucLoopCount;
  uint8 LucRegValues;
  uint8 LucHwUnitIndex;
  uint8 LucChannelCount;
  uint8 LucSgUnitId;
  uint8 LucSgUnitIndex;
  uint8 LucChannelIndex;
  uint8 LucScanCount;

  /* Read the HW unit of the group */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the SG unit index to which the channel group is mapped */
  LucSgUnitIndex = LpGroup->ucSgUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */

  /* Read the HW Unit to which the group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;
  /* Initialize the local variable for HW unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the SG unit which is configured for this group */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LucSgUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */

  /* Get the SG unit to which the group is configured */
  LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                             /* PRQA S 2814 # JV-01 */
  /* Initialize HW RAM data to a local pointer */
  LpSgUnitData = &Adc_GpSgUnitRamData[LucSgUnitIndex];                                                                  /* PRQA S 2824 # JV-01 */

  /* Initialize Group RAM data to a local pointer */
  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */

  #if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)
  /* Get the no of channels configured for the requested group */
  LucChannelCount = LpGroup->ucChannelCount - LpGroupData->ucNoOfDisabledChannels;                                      /* PRQA S 2814 # JV-01 */
  #else
  /* Get the no of channels configured for the requested group */
  LucChannelCount = LpGroup->ucChannelCount;
  #endif

  /* Read the user base configuration address of the HW unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */

  /* Initialize the error status */
  #if (((((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON)) && \
        (ADC_ENABLE_ERR_INT == STD_ON)) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
  LpGroupData->blConvError = ADC_FALSE;                                                                                 /* PRQA S 2814 # JV-01 */
  #endif
  #if (ADC_ENABLE_ID_ERR == STD_ON)
  LpGroupData->ucChannelIdError = ADC_INVALID_CHANNELID;
  #endif
  #if (ADC_ENABLE_OVERWRITE_ERR == STD_ON)
  LpGroupData->ucChannelOverwritten = ADC_INVALID_CHANNELID;
  #endif
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  LpGroupData->ucChannelLimitError = ADC_INVALID_CHANNELID;
  #endif
  #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
  LpGroupData->blTriggerOverlapped = ADC_FALSE;
  #endif
  #if (ADC_ENABLE_PARITY_ERR == STD_ON)
  LpGroupData->ucChannelParityError = ADC_INVALID_CHANNELID;
  #endif

  /* Clear error status and parity error */
  #if (ADC_ENABLE_ERR == STD_ON)
  LpAdcRegisters->ddADCXnECR = ADC_ADCX_ECR_CLEAR_ALL;                                                                  /* PRQA S 2814 # JV-01 */
  #endif
  #if (ADC_ENABLE_PARITY_ERR == STD_ON)
  LpAdcRegisters->ddADCXnECR = ADC_ADCX_ECR_PEC;
  #endif

  /* Initialize the number of channels present in the group */ 
  LpGroupData->ucChannelCount = LucChannelCount;                                                                        /* PRQA S 2814 # JV-01 */
  /* Initialize the number of ISR need to be skipped */
  LpGroupData->ucIsrSkipCount = ADC_BYTE_ZERO;

  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  /* Check for group popped from queue if the sample are completed? */
  if (LpGroupData->ucSamplesCompleted == LpGroup->ddNumberofSamples)                                                    /* PRQA S 2814 # JV-01 */
  {
    /* Initialize the number of conversion rounds to zero */
    /* Initialize the group's buffer pointer to the result buffer pointer */
    LpGroupData->pBuffer = LpGroupData->pChannelBuffer;
  }
  else
  {
    /* Initialize the group's buffer pointer from the sample which was suspended or aborted */
    LpGroupData->pBuffer = &LpGroupData->pChannelBuffer[LpGroupData->ucSamplesCompleted];                               /* PRQA S 0404 # JV-01 */
  }
  #else
  /* Initialize the number of conversion rounds to zero */
  LpGroupData->ucSamplesCompleted = ADC_BYTE_ZERO;
  /* Initialize the group's buffer pointer to the result buffer pointer */
  LpGroupData->pBuffer = LpGroupData->pChannelBuffer;
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */

  /* Set the flag indicating Group is not read so far */
  LpGroupData->blResultRead = ADC_TRUE;

  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  /* Check if the group uses suspend/resume feature */
  if (ADC_GROUP_REPL_SUSPEND_RESUME == LpGroup->enGroupReplacement)
  {
    /* Initialize the group's buffer pointer from the channel which was suspended */
    LulBufferOffset = (uint32)LpGroup->ddNumberofSamples * (uint32)LpGroupData->ucChannelsCompleted;                    /* PRQA S 3384 # JV-01 */
    LpGroupData->pBuffer = &LpGroupData->pBuffer[LulBufferOffset];

    /* Initialize the number of ISR need to be skipped */
    LpGroupData->ucIsrSkipCount = LpGroupData->ucChannelsCompleted;
  }
  else
  {
    /* Initialize the number of conversion completed channels */
    LpGroupData->ucChannelsCompleted = ADC_BYTE_ZERO;
  }
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
  LpSGRegisters = &LpAdcRegisters->aaADCXnSG[LucSgUnitId];                                                              /* PRQA S 2814, 2934 # JV-01, JV-01 */

  /* Suppose the scan count is 0 (continuous or once per trigger) */
  LucScanCount = (uint8)0U;
  #if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && (ADC_ENABLE_STREAMING == STD_ON))
  /* Check if the requested group is configured as SW triggered and linear streaming and using multicycle scan mode */
  if ((LddGroup < Adc_GucMaxSwTriggGroups) && (ADC_ACCESS_MODE_STREAMING == LpGroup->enGroupAccessMode) &&              /* PRQA S 2814 # JV-01 */
      (ADC_STREAM_BUFFER_LINEAR == LpGroup->enStreamBufferMode) &&
    #if (ADC_ENABLE_ADTIMER == STD_ON)
    /* Check if AD timer is not used */
      (ADC_FALSE == LpGroup->blAdcEnableAdTimerTriggMode) &&
    #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */
      ((uint8)0U == LpGroup->ucScanMode))
  {
    /* Set the scan count to number of samples, for SW triggered linear streaming with DMA or no error detection */
    LucScanCount = LpGroup->ddNumberofSamples - LpGroupData->ucSamplesCompleted - (uint8)1U;
  } /* else: No action required */
  #endif /* ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && (ADC_ENABLE_STREAMING == STD_ON)) */
  LpSGRegisters->ucADCXnSGMCYCRx = LucScanCount;                                                                        /* PRQA S 2844 # JV-01 */

  #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
  LpSgUnitData->ddCurrentPriority = LpGroup->ddGroupPriority;                                                           /* PRQA S 2814 # JV-01 */
  #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
  /* Update the SG unit ram data with the current group information */
  LpSgUnitData->ddCurrentConvGroup = LddGroup;                                                                          /* PRQA S 2814 # JV-01 */

  #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
  /* Check if the Group is mapped for HW configured for interrupt mode */
  if (ADC_INTERRUPT_MODE == LpSgUnitConfig->enFunctionalityModeType)                                                    /* PRQA S 2814 # JV-01 */
  {
    /* Enter the critical section protection */
    ADC_ENTER_CRITICAL_SECTION(ADC_INTERRUPT_CONTROL_PROTECTION);

    #if (ADC_ENABLE_PWM_DIAG == STD_ON)
    if ((ADC_TRUE == LpGroup->blPwmDiag)
      #if (ADC_ENABLE_DMA_MODE == STD_ON)
      || (ADC_TRUE == LpGroup->blEnableDmaTransfer)
      #endif
      )
    {
      /* Disable interrupt for SG unit since there is no interrupt at the end of conversion for PWM-Diag */
      Adc_DisableConvertInterrupt(LucHwUnitIndex, LucSgUnitIndex);
    }
    else
    #elif (ADC_ENABLE_DMA_MODE == STD_ON)
    if (ADC_TRUE == LpGroup->blEnableDmaTransfer)                                                                       /* PRQA S 2814 # JV-01 */
    {
      /* Disable interrupt for SG unit to which the group is mapped. */
      Adc_DisableConvertInterrupt(LucHwUnitIndex, LucSgUnitIndex);
    }
    else
    #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
    {
      /* Enable interrupt for SG unit to which group is mapped. */
      Adc_EnableConvertInterrupt(LucHwUnitIndex, LucSgUnitIndex);
    }
    /* Exit the critical section protection */
    ADC_EXIT_CRITICAL_SECTION(ADC_INTERRUPT_CONTROL_PROTECTION);
  } /* end of if (ADC_INTERRUPT_MODE == LpSgUnitConfig->enFunctionalityModeType) */
    /* else: No action required */
  #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

  #if (ADC_ENABLE_DMA_MODE == STD_ON)
  if (ADC_TRUE == LpGroup->blEnableDmaTransfer)
  {
    /* Enable DMA transfer */
    Adc_DmaEnable(LddGroup);
  } /* else: No action required */
  #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */

  #if (ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON)
  /* Check if Group Configured for Pin Level Diagnostic. */
  if (ADC_SELF_DIAG_PIN_LVL == LpGroup->enAdcSelfDiagMode)
  {
    /* Set value for "ADCXnTDCR" Register */
    LpAdcRegisters->ucADCXnTDCR = LpGroup->ucAdcSelfdiagpinlevelMask;
  }
  else
  {
    /* Clear "ADCXnTDCR" Register */
    LpAdcRegisters->ucADCXnTDCR = ADC_BYTE_ZERO;
  }
  #endif /* (ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON) */
  #if (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON)
  /* Check if self-diagnosis is wiring-break detection mode 1 (same as ADC_SELF_DIAG_WIRE_BRK for E2x) */
  if (ADC_SELF_DIAG_WIRE_BRK_MODE1 == LpGroup->enAdcSelfDiagMode)
  {
    #if (ADC_IP_ADCH == STD_ON)
    /* Setting of Wiring-break Detection Self-Diagnosis Enable */
    LpAdcRegisters->ddADCXnODCR =
      ADC_ADCX_ODCR_ODDE | ADC_ADCX_ODCR_ODE | (Adc_WireBreakRegType)LpGroup->ucAdcSelfDiagWireBreakPulseWidth;
    #else
    /* Set "ADCXnODCR" Register */
    LpAdcRegisters->ddADCXnODCR = (Adc_WireBreakRegType)LpGroup->ucAdcSelfDiagWireBreakPulseWidth;
    #endif /* (ADC_IP_ADCH == STD_ON) */
  }
  else
  {
    /* Clear "ADCXnODCR" Register */
    LpAdcRegisters->ddADCXnODCR = ADC_ADCX_ODCR_INIT_VALUE;
  }
  #endif /* (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) */

  #if (ADC_ENABLE_WIRE_BRK == STD_ON)
  #if (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON)
  if (ADC_SELF_DIAG_OFF == LpGroup->enAdcSelfDiagMode)
  #endif /* (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) */
  {
    if (ADC_TRUE == LpGroup->blAdcEnableWiringBreakDetection)
    {
      #if (ADC_IP_ADCH == STD_ON)
      /* Set Wiring-break Detection Enable */
      LpAdcRegisters->ddADCXnODCR = ADC_ADCX_ODCR_ODE | (Adc_WireBreakRegType)LpGroup->ucAdcSelfDiagWireBreakPulseWidth;
      #else
      LpAdcRegisters->ddADCXnODCR = (Adc_WireBreakRegType)LpGroup->ucAdcSelfDiagWireBreakPulseWidth;
      #endif /* (ADC_IP_ADCH == STD_ON) */
    }
    else
    {
      /* Clear "ADCXnODCR" Register */
      LpAdcRegisters->ddADCXnODCR = ADC_ADCX_ODCR_INIT_VALUE;
    }
  } /* end of if (ADC_SELF_DIAG_OFF == LpGroup->enAdcSelfDiagMode) */
    /* else: No action required */
  #endif /* (ADC_ENABLE_WIRE_BRK == STD_ON) */

  /* Check whether group status is ADC_IDLE or "ADC_STREAM_COMPLETED and implicitly stopped group" */
  if ((ADC_IDLE == LpGroupData->enGroupStatus) ||
      ((ADC_TRUE == LpGroup->blImplicitlyStopped) && (ADC_STREAM_COMPLETED == LpGroupData->enGroupStatus)))
  {
    /* Set the group status as busy */
    Adc_SetStatus(LddGroup, ADC_BUSY);
  } /* else: No action required */

  #if (ADC_ENABLE_PWM_DIAG == STD_ON)
  if (ADC_TRUE == LpGroup->blPwmDiag)
  {
    /* Dummy read ADCXnPWDDIR register to clear WFLAG */
    (void)Adc_PwmDiagReadData(LddGroup);
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */

    /* Enable the trigger of PWM-Diag */
    Adc_PwmDiagEnable(LddGroup);
  }
  else
  #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
  {
    /* Loop all channels of group */
    for (LucLoopCount = ADC_BYTE_ZERO; LucLoopCount < LucChannelCount; LucLoopCount++)
    {
      /* Get the actual channel index */
      LucChannelIndex = LpGroup->ucStartVirChPtr + LucLoopCount;
      /* Dummy read to clear ADCXnDIRj.WFLG bit to avoid data overwrite */
      (void)LpAdcRegisters->aaADCXnDIR[LucChannelIndex];                                                                /* PRQA S 2844, 2814 # JV-01, JV-01 */
    }
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */

    /* Set the virtual channel start pointer and end pointer */
    LpSGRegisters->usADCXnSGVCPRx =                                                                                     /* PRQA S 2814 # JV-01 */
      (uint16)((uint32)LpGroup->ucStartVirChPtr |                                                                       /* PRQA S 2814 # JV-01 */
               (((uint32)LpGroup->ucStartVirChPtr + (uint32)LucChannelCount - 1UL) << ADC_SHIFT_BYTE));                 /* PRQA S 3383, 3384 # JV-01, JV-01 */

    /* Initialize the virtual channels with the channel groups configured for requested group. */
    /* Get the index of 1st channel, configured for the requested group */
    LucChannelToGroupIndex = LpGroup->ucChannelToGroupIndex;
    /* Re-Initialize the channel count to actual configured no of channels */
    LucChannelCount = LpGroup->ucChannelCount;
    /* Get the actual first channel index */
    LucChannelIndex = LpGroup->ucStartVirChPtr;
    /* Map the physical channels to the virtual channels */
    for (LucLoopCount = ADC_COUNT_BYTE_INIT; LucLoopCount < LucChannelCount; LucLoopCount++)
    {
      #if (ADC_ENABLE_DISABLE_CHANNEL == STD_ON)
      /* Check if the channel is enabled */
      if (ADC_TRUE == Adc_GpChannelToDisableEnable[LucChannelToGroupIndex])                                             /* PRQA S 2824 # JV-01 */
      #endif /* (ADC_ENABLE_DISABLE_CHANNEL == STD_ON) */
      {
        /* Map the physical channels to the virtual channels */
        LpAdcRegisters->aaADCXnVCR[LucChannelIndex] = Adc_GpChannelToGroup[LucChannelToGroupIndex];                     /* PRQA S 2814, 2824, 2844 # JV-01, JV-01, JV-01 */
        /* Get the next channel index */
        LucChannelIndex++;                                                                                              /* PRQA S 3383 # JV-01 */
      } /* else: No action required */
      LucChannelToGroupIndex++;                                                                                         /* PRQA S 3383 # JV-01 */
    } /* end of for (LucLoopCount = ADC_COUNT_BYTE_INIT; LucLoopCount < LucChannelCount; LucLoopCount++) */

    #if (ADC_TRACK_AND_HOLD == STD_ON)
    if (ADC_TH_DISABLED != LpGroup->ucTrackAndHoldGroup)
    {
      /* Enable Track and Hold and start/enable SG */
      Adc_TrackHoldEnable(LddGroup);
    }
    else
    #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */
    {
      /* Configure the hardware unit with the group's operation mode */
      LucRegValues = LpGroup->ucScanMode;
      /* Update to generate output when the scan for SGx ends */
      LucRegValues |= ADC_ADCX_SGCR_ADIE;

      #if (ADC_ENABLE_ADTIMER == STD_ON)
      /* Check if the requested group has AD Timer Trigger */
      if (ADC_TRUE == LpGroup->blAdcEnableAdTimerTriggMode)
      {
        /* Enable the SG unit to start the conversion on trigger */
        LucRegValues |= ADC_ADCX_SGCR_TRGMD_ADTIMER;
        /* Set the Register ADCXnADTIPRx and ADCXnADTPRRx */
        LpSGRegisters->ulADCXnADTIPRx = LpGroup->ulAdcTimerPhaseDelay;
        LpSGRegisters->ulADCXnADTPRRx = LpGroup->ulAdcTimerPeriod;

        /* Check if the requested group is SW triggered */
        if (LddGroup < Adc_GucMaxSwTriggGroups)
        {
          /* Enable the SG unit to start the conversion for SW triggered group */
          LpSGRegisters->ucADCXnSGCRx = LucRegValues;
          /* Start the AD Timer */
          LpSGRegisters->ucADCXnADTSTCRx = ADC_ADCX_ADTSTCR_ADTST;
        }
        else
        {
          /* Enable the SG unit to start the conversion for HW triggered group */
          LucRegValues |= ADC_ADCX_SGCR_TRGMD_HW;
          LpSGRegisters->ucADCXnSGCRx = LucRegValues;
        }
      } /* end of if (ADC_TRUE == LpGroup->blAdcEnableAdTimerTriggMode) */
      else
      #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */
      {
        /* Check if the requested group is SW triggered */
        if (LddGroup < Adc_GucMaxSwTriggGroups)
        {
          /* Initiate conversion for SW triggered group */
          LpSGRegisters->ucADCXnSGCRx = LucRegValues;
          LpSGRegisters->ucADCXnSGSTCRx = ADC_ADCX_SGSTCR_SGST;
        }
        else
        {
          /* Enable the SG unit to start the conversion for HW triggered group */
          LucRegValues |= ADC_ADCX_SGCR_TRGMD_HW;
          LpSGRegisters->ucADCXnSGCRx = LucRegValues;
        }
      }
    }
  }

  /* Change SG unit status to active */
  Adc_GaaHwUnitData[LucHwUnitIndex].ucSgUnitStatus |= (uint8)(1U << LucSgUnitId);                                       /* PRQA S 2844 # JV-01 */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_DisableHwGroup
**
** Service ID           : NA
**
** Description          : This internal function shall disables the ongoing HW triggered group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : boolean
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpHwUnitConfig, Adc_GpGroupRamData,
**                        Adc_GpSgUnitRamData, Adc_GaaHwUnitData
**
** Functions invoked    : Adc_PwmDiagDisable, Adc_PicDisableHwTrigger, Adc_HwStopScanGroup, Adc_TrackHoldDisable,
**                        Adc_DisableDetection, ADC_ENTER_CRITICAL_SECTION, Adc_DisableConvertInterrupt,
**                        ADC_EXIT_CRITICAL_SECTION, Adc_DmaDisable, Adc_SetStatus
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_040, ADC_DUD_ACT_040_CRT001, ADC_DUD_ACT_040_CRT002,
** Reference ID         : ADC_DUD_ACT_040_GBL001, ADC_DUD_ACT_040_GBL002, ADC_DUD_ACT_040_GBL003,
** Reference ID         : ADC_DUD_ACT_040_GBL004
***********************************************************************************************************************/
#if (ADC_HW_TRIGGER_API == STD_ON)

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(boolean, ADC_PRIVATE_CODE) Adc_DisableHwGroup(const Adc_GroupType LddGroup)
{
  #if (ADC_ENABLE_ADC_TSEL == STD_ON) && (ADC_IP_C_ADCK == STD_OFF)
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  #endif /* (ADC_ENABLE_ADC_TSEL == STD_ON) && (ADC_IP_C_ADCK == STD_OFF) */
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  P2VAR(volatile Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  uint8 LucHwUnitIndex;
  uint8 LucSgUnitIndex;
  boolean LblHwTimedOut;
  #if (ADC_ENABLE_DMA_MODE == STD_ON)
  boolean LblDmaTimedOut;
  #endif

  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Read the Hardware Unit to which the group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  LucSgUnitIndex = LpGroup->ucSgUnitIndex;

  /* Get the SG unit which is configured for this group */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LucSgUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Initialize HW RAM data to a local pointer */
  LpSgUnitData = &Adc_GpSgUnitRamData[LucSgUnitIndex];                                                                  /* PRQA S 2824 # JV-01 */

  #if (ADC_ENABLE_PWM_DIAG == STD_ON)
  /* Check if trigger source of requested group is PWM-Diag */
  if (ADC_TRUE == LpGroup->blPwmDiag)
  {
    /* Disable the trigger of PWM-Diag */
    LblHwTimedOut = Adc_PwmDiagDisable(LddGroup);
  }
  else
  #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
  {
    #if (ADC_ENABLE_ADC_TSEL == STD_ON) && (ADC_IP_C_ADCK == STD_OFF)
    /* Get the HW unit configuration. */
    LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                               /* PRQA S 2824 # JV-01 */
    /* Check if requested group belongs to HW unit in AWO */
    if (NULL_PTR != LpHwUnitConfig->pSgTriggReg)                                                                        /* PRQA S 2814 # JV-01 */
    {
      /* No action required for HW triggers as those for HW unit in AWO are statically configured at initialization */
    }
    else
    #endif /* (ADC_ENABLE_ADC_TSEL == STD_ON) && (ADC_IP_C_ADCK == STD_OFF) */
    {
      /* Disable Hw trigger of PIC unit */
      Adc_PicDisableHwTrigger(LddGroup);
    }

    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* Enter global Protect area */
    ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
    /* Store disabled notification into RAM */
    LpGroupData->blNotifyStatus = ADC_FALSE;                                                                            /* PRQA S 2814 # JV-01 */
    /* Exit global Protect area */
    ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION_GLOBAL);
    #endif

    /* Stop the conversion of the SG unit */
    LblHwTimedOut = Adc_HwStopScanGroup(LddGroup, ADC_TRUE);

    if (ADC_FALSE == LblHwTimedOut)
    {
      #if (ADC_TRACK_AND_HOLD == STD_ON)
      Adc_TrackHoldDisable(LddGroup);
      #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

      #if ((ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON) || \
           (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) || (ADC_ENABLE_WIRE_BRK == STD_ON))
      /* Disable self-diagnosis pin level and wiring break detection if they are configured */
      Adc_DisableDetection(LddGroup);
      #endif
    } /* else: No action required */

    #if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)
    /* Check if the Group is mapped for HW configured for interrupt mode */
    if (ADC_INTERRUPT_MODE == LpSgUnitConfig->enFunctionalityModeType)                                                  /* PRQA S 2814 # JV-01 */
    {
      #if (ADC_ENABLE_DMA_MODE == STD_ON)
      /* Check if the requested group does not use DMA transfer */
      if (ADC_FALSE == LpGroup->blEnableDmaTransfer)
      #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
      {
        /* Enter the critical section protection */
        ADC_ENTER_CRITICAL_SECTION(ADC_INTERRUPT_CONTROL_PROTECTION);
        /* Disable interrupt for SG unit to which group is mapped */
        Adc_DisableConvertInterrupt(LucHwUnitIndex, LucSgUnitIndex);
        /* Exit the critical section protection */
        ADC_EXIT_CRITICAL_SECTION(ADC_INTERRUPT_CONTROL_PROTECTION);
      } /* else: No action required */
    } /* end of if (ADC_INTERRUPT_MODE == LpSgUnitConfig->enFunctionalityModeType) */
      /* else: No action required */
    #endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

    #if (ADC_ENABLE_DMA_MODE == STD_ON)
    if (ADC_TRUE == LpGroup->blEnableDmaTransfer)
    {
      LblDmaTimedOut = Adc_DmaDisable(LddGroup);
      if (ADC_TRUE == LblDmaTimedOut)
      {
        LblHwTimedOut = ADC_TRUE;
      } /* else: No action required */
    } /* else: No action required */
    #endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */
  }

  /* Change SG unit status to inactive */
  LpSgUnitData->blSgUnitStatus = ADC_FALSE;                                                                             /* PRQA S 2814 # JV-01 */
  Adc_GaaHwUnitData[LucHwUnitIndex].ucSgUnitStatus &= (uint8)~(1U << LpSgUnitConfig->ucSgUnitId);                       /* PRQA S 2844 # JV-01 */

  /* Set the Group status to idle */
  Adc_SetStatus(LddGroup, ADC_IDLE);

  /* Set the group enable hardware trigger status to false */
  LpGroupData->blHwTriggStatus = ADC_FALSE;

  return LblHwTimedOut;
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_HW_TRIGGER_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_DisableConvertInterrupt
**
** Service ID           : NA
**
** Description          : This internal function is A/D convert interrupt
**                        disable process by EIC register.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : LucHwUnitIndex, LucSgUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpSgUnitConfig, Adc_GpHwUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : EIC
**
** Reference ID         : ADC_DUD_ACT_041, ADC_DUD_ACT_041_REG001, ADC_DUD_ACT_041_REG002
***********************************************************************************************************************/
#if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_CODE_FAST) Adc_DisableConvertInterrupt(const uint8 LucHwUnitIndex, const uint8 LucSgUnitIndex)    /* PRQA S 3006 # JV-01 */
{
  P2VAR(volatile uint16, AUTOMATIC, REGSPACE) LpEicRegBaseAddress;                                                      /* PRQA S 3678 # JV-01 */
  uint8 LucSgUnitId;

  LucSgUnitId = Adc_GpSgUnitConfig[LucSgUnitIndex].ucSgUnitId;                                                          /* PRQA S 2824 # JV-01 */
  LpEicRegBaseAddress = Adc_GpHwUnitConfig[LucHwUnitIndex].pEicRegAddress;                                              /* PRQA S 2824 # JV-01 */

  /* Disable ADC conversion end interrupt */
  RH850_SV_MODE_ICR_OR(8, &LpEicRegBaseAddress[LucSgUnitId], ADC_EIC_EIMK);                                             /* PRQA S 0404, 0751, 2824, 3464 # JV-01, JV-01, JV-01, JV-01 */

  /* Clear Interrupt Request Flag and perform synchronization for INTC2 */
  RH850_SV_CLEAR_ICR_SYNCP(16, &LpEicRegBaseAddress[LucSgUnitId], (uint16)~ADC_EIC_EIRF);                               /* PRQA S 0404, 1006, 3464 # JV-01, JV-01, JV-01 */
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

/***********************************************************************************************************************
** Function Name        : Adc_EnableConvertInterrupt
**
** Service ID           : NA
**
** Description          : This internal function is A/D convert interrupt
**                        enable process by EIC register.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : LucHwUnitIndex, LucSgUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpSgUnitConfig, Adc_GpHwUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : EIC
**
** Reference ID         : ADC_DUD_ACT_042, ADC_DUD_ACT_042_REG001, ADC_DUD_ACT_042_REG002
***********************************************************************************************************************/
#if (ADC_FUNCTIONALITY_MODE != ADC_POLLING)

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_CODE_FAST) Adc_EnableConvertInterrupt(const uint8 LucHwUnitIndex, const uint8 LucSgUnitIndex)     /* PRQA S 3006 # JV-01 */
{
  P2VAR(volatile uint16, AUTOMATIC, REGSPACE) LpEicRegBaseAddress;                                                      /* PRQA S 3678 # JV-01 */
  uint8 LucSgUnitId;

  LucSgUnitId = Adc_GpSgUnitConfig[LucSgUnitIndex].ucSgUnitId;                                                          /* PRQA S 2824 # JV-01 */
  LpEicRegBaseAddress = Adc_GpHwUnitConfig[LucHwUnitIndex].pEicRegAddress;                                              /* PRQA S 2824 # JV-01 */

  /* Clear Interrupt Request Flag */
  RH850_SV_MODE_ICR_AND(16, &LpEicRegBaseAddress[LucSgUnitId], (uint16)~ADC_EIC_EIRF);                                  /* PRQA S 0404, 2824, 3464 # JV-01, JV-01, JV-01 */

  /* Enable ADC conversion end interrupt and perform synchronization for INTC2 */
  RH850_SV_CLEAR_ICR_SYNCP(8, &LpEicRegBaseAddress[LucSgUnitId], (uint8)~ADC_EIC_EIMK);                                 /* PRQA S 0404, 0751, 1006, 3464 # JV-01, JV-01, JV-01, JV-01 */
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_FUNCTIONALITY_MODE != ADC_POLLING) */

/***********************************************************************************************************************
** Function Name        : Adc_ErrIsr
**
** Service ID           : NA
**
** Description          : This internal function shall be an error interrupt service routine for ADC Driver.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW unit, Non-Reentrant for the same HW unit
**
** Input Parameters     : LucHwUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig, Adc_GaaHwUnitData, Adc_GpSgUnitRamData, Adc_GpGroupConfig,
**                        Adc_GpGroupRamData, Adc_GpSgUnitConfig, Adc_GpChannelToGroup
**
** Functions invoked    : ADC_DEM_REPORT_ERROR, pErrorNotificationPointerSG, pErrorNotificationPointer
**
** Registers Used       : ADCXnIDER, ADCXnOWER, ADCXnTOCER, ADCXnVCLMSR1, ADCXnVCLMSR2, ADCXnVCRj, ADCXnECR,
**                        ADCXnVCLMSCR1, ADCXnVCLMSCR2
**
** Reference ID         : ADC_DUD_ACT_043, ADC_DUD_ACT_043_ERR001, ADC_DUD_ACT_043_GBL001,
** Reference ID         : ADC_DUD_ACT_043_GBL002, ADC_DUD_ACT_043_REG001, ADC_DUD_ACT_043_REG002,
** Reference ID         : ADC_DUD_ACT_043_REG003
***********************************************************************************************************************/
#if (ADC_ENABLE_ERR_INT == STD_ON)

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_CODE_FAST) Adc_ErrIsr(const uint8 LucHwUnitIndex)                                                        /* PRQA S 1532, 2755 # JV-01, JV-01 */
{
  #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
       (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON))
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  #endif
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  volatile P2CONST(Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
       (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON))
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  #endif
  uint32 LulSgUnitIndex;
  uint32 LulSgUnitCount;
  #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
       (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON))
  Adc_GroupType LddGroup;
  #endif

  #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
       (ADC_ENABLE_OVERWRITE_ERR == STD_ON))
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  uint8 LucErrorVirCh;
  uint8 LucPhysCh;
  #endif
  #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_OVERWRITE_ERR == STD_ON))
  uint8 LucStartVirCh;
  uint8 LucEndVirCh;
  uint8 LucCapVirCh;
  #endif
  #if ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF))
  uint8 LucIderValue;
  #if (ADC_ENABLE_PWM_DIAG == STD_ON)
  uint8 LucChannelToGroupIndex;
  #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
  #endif
  #if (ADC_ENABLE_OVERWRITE_ERR == STD_ON)
  uint8 LucOwerValue;
  #endif
  #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
  uint8 LucSgUnitId;
  uint8 LucTocerValue;
  #endif
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  uint32 LulVclmsrValue[ADC_NUM_OF_LIMIT_REG];
  uint32 LulRegSel;
  uint32 LulBitLoc;
  #endif

  /* Get the pointer to the hardware unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
       (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON))
  /* Get the base register address of the hardware unit */
  LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                  /* PRQA S 2814 # JV-01 */
  #endif

  /* Get the error status */
  #if ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF))
  LucIderValue = LpAdcRegisters->ucADCXnIDER;                                                                           /* PRQA S 2814 # JV-01 */
  #endif
  #if (ADC_ENABLE_OVERWRITE_ERR == STD_ON)
  LucOwerValue = LpAdcRegisters->ucADCXnOWER;
  #endif
  #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
  LucTocerValue = LpAdcRegisters->ucADCXnTOCER;                                                                         /* PRQA S 2814 # JV-01 */
  #endif
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  LulVclmsrValue[ADC_VCLM_1] = LpAdcRegisters->aaADCXnVCLMSR[ADC_VCLM_1];
  LulVclmsrValue[ADC_VCLM_2] = LpAdcRegisters->aaADCXnVCLMSR[ADC_VCLM_2];
  #endif
  #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
       (ADC_ENABLE_OVERWRITE_ERR == STD_ON))
  LucErrorVirCh = ADC_INVALID_CHANNELID;
  #endif

  /* Get the index of the first SG unit config in the hardware unit */
  #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
  LulSgUnitIndex = (uint32)LpHwUnitConfig->ucSgUnitOffset;
  #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
  #if (ADC_IP_ADCH == STD_ON)
  LulSgUnitIndex = (uint32)Adc_GaaHwUnitData[LucHwUnitIndex].ucSgUnitIndex;
  #endif /* (ADC_IP_ADCH == STD_ON) */
  /* Get the number of scan group config in the hardware unit */
  LulSgUnitCount = (uint32)LpHwUnitConfig->ucSgUnitCount;

  /* Loop the number of SG unit configurations */
  while (LulSgUnitCount != 0UL)
  {
    LulSgUnitCount--;
    /* Get the pointer to the runtime data of the SG unit */
    LpSgUnitData = &Adc_GpSgUnitRamData[LulSgUnitIndex + LulSgUnitCount];                                               /* PRQA S 2824, 3383 # JV-01, JV-01 */
    /* Check if the SG unit is active */
    if (ADC_TRUE == LpSgUnitData->blSgUnitStatus)                                                                       /* PRQA S 2814 # JV-01 */
    {
      #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
           (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON))
      /* Get the pointer to the current group configuration of the SG unit */
      LddGroup = LpSgUnitData->ddCurrentConvGroup;
      LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                           /* PRQA S 2824 # JV-01 */
      #endif
      #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
           (ADC_ENABLE_OVERWRITE_ERR == STD_ON))
      /* Get the pointer to the runtime data of the group */
      LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                      /* PRQA S 2824 # JV-01 */
      #endif

      #if ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_ENABLE_PWM_DIAG == STD_ON))
      if (ADC_TRUE == LpGroup->blPwmDiag)                                                                               /* PRQA S 2814 # JV-01 */
      {
        /* Set the group channel range to PWM-Diag channel */
        LucStartVirCh = ADC_ADCX_IDER_IDECAP_PWD;
        LucEndVirCh = ADC_ADCX_IDER_IDECAP_PWD;
      }
      else
      #endif /* ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_ENABLE_PWM_DIAG == STD_ON)) */
      #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_OVERWRITE_ERR == STD_ON))
      #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
      if (ADC_GROUP_REPL_SUSPEND_RESUME == LpGroup->enGroupReplacement)                                                 /* PRQA S 2814 # JV-01 */
      {
        /* Set the group channel range to the current virtual channel of the group */
        LucStartVirCh = LpGroup->ucStartVirChPtr + LpGroupData->ucChannelsCompleted;                                    /* PRQA S 2814 # JV-01 */
        LucEndVirCh = LucStartVirCh;
      }
      else
      #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
      {
        /* Set the group channel range to the virtual channel range of the group */
        LucStartVirCh = LpGroup->ucStartVirChPtr;                                                                       /* PRQA S 2814 # JV-01 */
        LucEndVirCh = (uint8)(LucStartVirCh + LpGroupData->ucChannelCount - ADC_BYTE_ONE);                              /* PRQA S 2814 # JV-01 */
      }
      #endif /* (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_OVERWRITE_ERR == STD_ON)) */

      #if ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF))
      /* Check the Id error status */
      if (ADC_BYTE_ZERO != (uint8)(LucIderValue & ADC_ADCX_IDER_IDE))
      {
        /* Check if it is within the range of channels in the group */
        LucCapVirCh = (uint8)(LucIderValue & ADC_ADCX_IDER_IDECAP);
        if ((LucStartVirCh <= LucCapVirCh) && (LucCapVirCh <= LucEndVirCh))
        {
          /* Set the conversion error status */
          LpGroupData->blConvError = ADC_TRUE;
          /* Set the error channel */
          LucErrorVirCh = LucCapVirCh;
          /* Report the Id error to Dem */
          ADC_DEM_REPORT_ERROR(ADC_E_ID_FAILURE, DEM_EVENT_STATUS_FAILED);
        } /* else: No action required */
      } /* end of if (ADC_BYTE_ZERO != (uint8)(LucIderValue & ADC_ADCX_IDER_IDE)) */
        /* else: No action required */
      #endif /* ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) */

      #if (ADC_ENABLE_OVERWRITE_ERR == STD_ON)
      /* Check the overwrite error status */
      if (ADC_BYTE_ZERO != (uint8)(LucOwerValue & ADC_ADCX_OWER_OWE))
      {
        /* Check if it is within the range of channels in the group */
        LucCapVirCh = (uint8)(LucOwerValue & ADC_ADCX_OWER_OWECAP);
        if ((LucStartVirCh <= LucCapVirCh) && (LucCapVirCh <= LucEndVirCh))
        {
          /* Set the error channel */
          LucErrorVirCh = LucCapVirCh;
        } /* else: No action required */
      } /* else: No action required */
      #endif /* (ADC_ENABLE_OVERWRITE_ERR == STD_ON) */

      #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
      if (NULL_PTR != LpHwUnitConfig->pErrorNotificationPointerSG)
      {
        /* Check the trigger overlap check status */
        LucSgUnitId = Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex].ucSgUnitId;                                            /* PRQA S 2824, 2814 # JV-01, JV-01 */
        if (ADC_BYTE_ZERO != (uint8)(LucTocerValue & (uint8)(ADC_ADCX_TOCER_TOCESG_LSB << LucSgUnitId)))
        {
          /* Invoke the callback function for the trigger overlap error */
          LpHwUnitConfig->pErrorNotificationPointerSG(LucSgUnitId);                                                     /* PRQA S 2814 # JV-01 */
        } /* else: No action required */
      } /* else: No action required */
      #endif /* (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON) */

      #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
      if (ADC_TRUE == LpGroup->blLimitCheckEnabled)
      {
        /* Get the values of upper/lower limit check error status registers */
        LulRegSel = ((uint32)LpGroup->ucStartVirChPtr >> ADC_ADCX_VCLMSR_HIGH_SHIFT) & ADC_ADCX_VCLMSR_HIGH_MASK;
        LulBitLoc = (uint32)LpGroup->ucStartVirChPtr & ADC_ADCX_VCLMSR_LOW_MASK;
        if (0UL != (LulVclmsrValue[LulRegSel] & (1UL << LulBitLoc)))
        {
          /* Set the conversion error status */
          LpGroupData->blConvError = ADC_TRUE;
          /* Store the channel where the limit error occurred */
          LucErrorVirCh = LpGroup->ucStartVirChPtr;
        } /* else: No action required */
      } /* else: No action required */
      #endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */

      #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
           (ADC_ENABLE_OVERWRITE_ERR == STD_ON))
      if (NULL_PTR != LpHwUnitConfig->pErrorNotificationPointer)
      {
        if (ADC_INVALID_CHANNELID != LucErrorVirCh)
        {
          #if ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_ENABLE_PWM_DIAG == STD_ON))
          if (ADC_TRUE == LpGroup->blPwmDiag)
          {
            /* Get the channel from the group channel configuration as PWM-Diag has no virtual channel */
            LucChannelToGroupIndex = LpGroup->ucChannelToGroupIndex;
            LucPhysCh = (uint8)(Adc_GpChannelToGroup[LucChannelToGroupIndex] & ADC_CHANNEL_ID_MASK);                    /* PRQA S 2824 # JV-01 */
          }
          else
          #endif /* ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_ENABLE_PWM_DIAG == STD_ON)) */
          {
            /* Get the physical channel where error occurred */
            LucPhysCh = (uint8)(LpAdcRegisters->aaADCXnVCR[LucErrorVirCh] & ADC_ADCX_VCR_GCTRL);                        /* PRQA S 2844 # JV-01 */
          }
          /*
           * Invoke the call-back function
           * When multiple errors, only one channel is notified with priority of overwrite < ID < limit
           */
          LpHwUnitConfig->pErrorNotificationPointer(LucPhysCh);
        } /* end of if (ADC_INVALID_CHANNELID != LucErrorVirCh) */
          /* else: No action required */
      } /* end of if (NULL_PTR != LpHwUnitConfig->pErrorNotificationPointer) */
        /* else: No action required */
      #endif
    } /* end of if (ADC_TRUE == LpSgUnitData->blSgUnitStatus) */
      /* else: No action required */
  } /* end of while (LulSgUnitCount != 0UL) */

  #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || \
       (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON))
  /* Clear error status */
  LpAdcRegisters->ddADCXnECR = ADC_ADCX_ECR_CLEAR_ALL;
  #endif
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Clear error status */
  LpAdcRegisters->aaADCXnVCLMSCR[ADC_VCLM_1] = ADC_ADCX_VCLMSCR1_ALL_MASK;
  LpAdcRegisters->aaADCXnVCLMSCR[ADC_VCLM_2] = ADC_ADCX_VCLMSCR2_ALL_MASK;
  #endif
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_ERR_INT == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_ParityErrIsr
**
** Service ID           : NA
**
** Description          : This internal function shall be an parity error interrupt service routine for ADC.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpHwUnitConfig, Adc_GpSgUnitRamData, Adc_GpGroupConfig, Adc_GpGroupRamData,
**                        Adc_GpChannelToGroup, Adc_GaaHwUnitData
**
** Functions invoked    : pErrorNotificationPointer, ADC_DEM_REPORT_ERROR
**
** Registers Used       : ADCXnPER, ADCXnVCRj, ADCXnECR
**
** Reference ID         : ADC_DUD_ACT_044, ADC_DUD_ACT_044_ERR001, ADC_DUD_ACT_044_GBL002, ADC_DUD_ACT_044_REG001
***********************************************************************************************************************/
#if (ADC_ENABLE_PARITY_ERR_INT == STD_ON)

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_CODE_FAST) Adc_ParityErrIsr(void)                                                                        /* PRQA S 1532, 2755 # JV-01, JV-01 */
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  volatile P2CONST(Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;

  uint8 LucHwUnitIndex;
  uint32 LulSgUnitIndex;
  uint32 LulSgUnitCount;
  uint8 LucPerValue;
  uint8 LucErrorVirCh;
  Adc_GroupType LddGroup;
  uint8 LucStartVirCh;
  uint8 LucEndVirCh;
  uint8 LucPhysCh;
  #if (ADC_ENABLE_PWM_DIAG == STD_ON)
  uint8 LucChannelToGroupIndex;
  #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */

  /* Check all HW units as parity errors are handled by a common interrupt */
  for (LucHwUnitIndex = ADC_COUNT_BYTE_INIT; LucHwUnitIndex < (uint8)ADC_MAX_HW_UNITS; LucHwUnitIndex++)                /* PRQA S 2877 # JV-01 */
  {
    /* Get the pointer to the hardware unit configuration */
    LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                               /* PRQA S 2824 # JV-01 */
    /* Get the base register address of the hardware unit */
    LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;                                                                /* PRQA S 2814 # JV-01 */

    /* Check the parity error status */
    LucPerValue = LpAdcRegisters->ucADCXnPER;                                                                           /* PRQA S 2814 # JV-01 */
    if (ADC_BYTE_ZERO != (uint8)(LucPerValue & ADC_ADCX_PER_PE))
    {
      /* Get the virtual channel captured due to parity error */
      LucErrorVirCh = (uint8)(LucPerValue & ADC_ADCX_PER_PECAP);
      /* Initialize the physical channel to ADC_INVALID_CHANNELID */
      LucPhysCh = ADC_INVALID_CHANNELID;

      /* Get the index of the first SG unit configuration in the hardware unit */
      #if ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON))
      LulSgUnitIndex = LpHwUnitConfig->ucSgUnitOffset;
      #endif /* ((ADC_IP_ADCJ == STD_ON) || (ADC_IP_ADCK == STD_ON)) */
      #if (ADC_IP_ADCH == STD_ON)
      LulSgUnitIndex = Adc_GaaHwUnitData[LucHwUnitIndex].ucSgUnitIndex;
      #endif /* (ADC_IP_ADCH == STD_ON) */

      /* Get the number of SG unit configurations in the hardware unit */
      LulSgUnitCount = (uint32)LpHwUnitConfig->ucSgUnitCount;
      /* Check for errors in order from the highest priority SG unit */
      while (LulSgUnitCount != 0UL)
      {
        LulSgUnitCount--;
        /* Get the pointer to the runtime data of the SG unit */
        LpSgUnitData = &Adc_GpSgUnitRamData[LulSgUnitIndex + LulSgUnitCount];                                           /* PRQA S 2824, 3383 # JV-01, JV-01 */
        /* Check if the SG unit is active */
        if (ADC_TRUE == LpSgUnitData->blSgUnitStatus)                                                                   /* PRQA S 2814 # JV-01 */
        {
          /* Get the current group of the SG unit */
          LddGroup = LpSgUnitData->ddCurrentConvGroup;
          /* Get the pointer to the group configuration */
          LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                       /* PRQA S 2824 # JV-01 */
          /* Get the pointer to the runtime data of the group */
          LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                  /* PRQA S 2824 # JV-01 */

          #if (ADC_ENABLE_PWM_DIAG == STD_ON)
          if (ADC_TRUE == LpGroup->blPwmDiag)                                                                           /* PRQA S 2814 # JV-01 */
          {
            /* Set the group channel range to PWM-Diag channel */
            LucStartVirCh = ADC_ADCX_PER_PECAP_PWD;
            LucEndVirCh = ADC_ADCX_PER_PECAP_PWD;
          }
          else
          #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
          #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
          if (ADC_GROUP_REPL_SUSPEND_RESUME == LpGroup->enGroupReplacement)                                             /* PRQA S 2814 # JV-01 */
          {
            /* Set the group channel range to the current virtual channel of the group */
            LucStartVirCh = LpGroup->ucStartVirChPtr + LpGroupData->ucChannelsCompleted;                                /* PRQA S 2814 # JV-01 */
            LucEndVirCh = LucStartVirCh;
          }
          else
          #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
          {
            /* Set the group channel range to the virtual channel range of the group */
            LucStartVirCh = LpGroup->ucStartVirChPtr;                                                                   /* PRQA S 2814 # JV-01 */
            LucEndVirCh = (uint8)(LucStartVirCh + LpGroupData->ucChannelCount - ADC_BYTE_ONE);                          /* PRQA S 2814 # JV-01 */
          }

          /* Check if it is within the range of channels in the group */
          if ((LucStartVirCh <= LucErrorVirCh) && (LucErrorVirCh <= LucEndVirCh))
          {
            /* Set the conversion error status */
            LpGroupData->blConvError = ADC_TRUE;

            #if (ADC_ENABLE_PWM_DIAG == STD_ON)
            if (ADC_ADCX_PER_PECAP_PWD == LucErrorVirCh)
            {
              /* Get the channel from the group channel configuration as PWM-Diag has no virtual channel */
              LucChannelToGroupIndex = LpGroup->ucChannelToGroupIndex;
              LucPhysCh = (uint8)(Adc_GpChannelToGroup[LucChannelToGroupIndex] & ADC_CHANNEL_ID_MASK);                  /* PRQA S 2824 # JV-01 */
            }
            else
            #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
            {
              /* Get the physical channel where parity error occurred */
              LucPhysCh = (uint8)(LpAdcRegisters->aaADCXnVCR[LucErrorVirCh] & ADC_ADCX_VCR_GCTRL);                      /* PRQA S 2844 # JV-01 */
            }

            /* Set the loop count to 0 to end the loop */
            LulSgUnitCount = 0UL;
          } /* end of if ((LucStartVirCh <= LucErrorVirCh) && (LucErrorVirCh <= LucEndVirCh)) */
            /* else: No action required */
        } /* end of if (ADC_TRUE == LpSgUnitData->blSgUnitStatus) */
          /* else: No action required */
      } /* end of while (LulSgUnitCount != 0UL) */

      if (NULL_PTR != LpHwUnitConfig->pErrorNotificationPointer)
      {
        if (ADC_INVALID_CHANNELID != LucPhysCh)
        {
          /* Invoke a callback function for error notification */
          LpHwUnitConfig->pErrorNotificationPointer(LucPhysCh);
        } /* else: No action required */
      } /* else: No action required */

      /* Report parity check error to Dem */
      ADC_DEM_REPORT_ERROR(ADC_E_PARITY_FAILURE, DEM_EVENT_STATUS_FAILED);

      /* Clear parity error status */
      LpAdcRegisters->ddADCXnECR = ADC_ADCX_ECR_PEC;
    } /* end of if (ADC_BYTE_ZERO != (uint8)(LucPerValue & ADC_ADCX_PER_PE)) */
      /* else: No action required */
  } /* end of for (LucHwUnitIndex = ADC_COUNT_BYTE_INIT; LucHwUnitIndex < (uint8)ADC_MAX_HW_UNITS; LucHwUnitIndex++) */
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_PARITY_ERR_INT == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_CheckParity
**
** Service ID           : NA
**
** Description          : This internal function checks whether there's parity error or not.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW unit, Non-Reentrant for same HW unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : boolean
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpHwUnitConfig, Adc_GpGroupRamData, Adc_GpChannelToGroup
**
** Functions invoked    : None
**
** Registers Used       : ADCXnPER, ADCXnVCRj, ADCXnECR
**
** Reference ID         : ADC_DUD_ACT_075, ADC_DUD_ACT_075_GBL001, ADC_DUD_ACT_075_REG001
***********************************************************************************************************************/
#if (ADC_ENABLE_PARITY_ERR == STD_ON)
#if ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON) || (ADC_ENABLE_DMA_MODE == STD_ON))

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(boolean, ADC_CODE_FAST) Adc_CheckParity(const Adc_GroupType LddGroup)
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  uint8 LucPerValue;
  uint8 LucErrorVirCh;
  uint8 LucStartVirCh;
  uint8 LucEndVirCh;
  uint8 LucPhysCh;
  boolean LblErrorFlag;
  #if (ADC_ENABLE_PWM_DIAG == STD_ON)
  uint8 LucChannelToGroupIndex;
  #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */

  /* Get the pointer to the group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the base register address of the hardware unit */
  LpAdcRegisters = Adc_GpHwUnitConfig[LpGroup->ucHwUnitIndex].pHwUnitBaseAddress;                                       /* PRQA S 2814, 2824 # JV-01, JV-01 */
  /* Get the pointer to the runtime data of the group */
  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */

  /* Initialize the error flag */
  LblErrorFlag = ADC_FALSE;

  /* Check the parity error status */
  LucPerValue = LpAdcRegisters->ucADCXnPER;                                                                             /* PRQA S 2814 # JV-01 */
  if (ADC_BYTE_ZERO != (uint8)(LucPerValue & ADC_ADCX_PER_PE))
  {
    #if (ADC_ENABLE_PWM_DIAG == STD_ON)
    if (ADC_TRUE == LpGroup->blPwmDiag)
    {
      /* Set the group channel range to PWM-Diag channel */
      LucStartVirCh = ADC_ADCX_PER_PECAP_PWD;
      LucEndVirCh = ADC_ADCX_PER_PECAP_PWD;
    }
    else
    #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
    #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
    if (ADC_GROUP_REPL_SUSPEND_RESUME == LpGroup->enGroupReplacement)
    {
      /* Set the group channel range to the current virtual channel of the group */
      LucStartVirCh = LpGroup->ucStartVirChPtr + LpGroupData->ucChannelsCompleted;                                      /* PRQA S 2814 # JV-01 */
      LucEndVirCh = LucStartVirCh;
    }
    else
    #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
    {
      /* Set the group channel range to the virtual channel range of the group */
      LucStartVirCh = LpGroup->ucStartVirChPtr;
      LucEndVirCh = (uint8)(LucStartVirCh + LpGroupData->ucChannelCount - ADC_BYTE_ONE);                                /* PRQA S 2814 # JV-01 */
    }

    /* Get the virtual channel captured due to an parity error */
    LucErrorVirCh = (uint8)(LucPerValue & ADC_ADCX_PER_PECAP);
    if ((LucStartVirCh <= LucErrorVirCh) && (LucErrorVirCh <= LucEndVirCh))
    {
      /* Set the conversion error status */
      LblErrorFlag = ADC_TRUE;

      #if (ADC_ENABLE_PWM_DIAG == STD_ON)
      if (ADC_ADCX_PER_PECAP_PWD == LucErrorVirCh)
      {
        /* Get the channel from the group channel configuration as PWM-Diag has no virtual channel */
        LucChannelToGroupIndex = LpGroup->ucChannelToGroupIndex;
        LucPhysCh = (uint8)(Adc_GpChannelToGroup[LucChannelToGroupIndex] & ADC_CHANNEL_ID_MASK);                        /* PRQA S 2824 # JV-01 */
      }
      else
      #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
      {
        /* Get and store the physical channel where the parity error occurred */
        LucPhysCh = (uint8)(LpAdcRegisters->aaADCXnVCR[LucErrorVirCh] & ADC_ADCX_VCR_GCTRL);                            /* PRQA S 2844 # JV-01 */
      }
      LpGroupData->ucChannelParityError = LucPhysCh;
      /* Clear parity error status */
      LpAdcRegisters->ddADCXnECR = ADC_ADCX_ECR_PEC;
    } /* end of if ((LucStartVirCh <= LucErrorVirCh) && (LucErrorVirCh <= LucEndVirCh)) */
      /* else: No action required */
  } /* end of if (ADC_BYTE_ZERO != (uint8)(LucPerValue & ADC_ADCX_PER_PE)) */
    /* else: No action required */

  return LblErrorFlag;
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /*
        * ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON) || (ADC_ENABLE_DMA_MODE == STD_ON))
        */
#endif /* (ADC_ENABLE_PARITY_ERR == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_CheckError
**
** Service ID           : NA
**
** Description          : This internal function checks whether there's error or not.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW unit, Non-Reentrant for same HW unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : boolean
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpHwUnitConfig, Adc_GpGroupRamData, Adc_GpChannelToGroup,
**                        Adc_GpSgUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : ADCXnIDER, ADCXnOWER, ADCXnTOCER, ADCXnVCRj, ADCXnECR, ADCXnVCLMSR1, ADCXnVCLMSR2,
**                        ADCXnVCLMSCR1, ADCXnVCLMSCR2
**
** Reference ID         : ADC_DUD_ACT_045, ADC_DUD_ACT_045_GBL002, ADC_DUD_ACT_045_GBL003,
** Reference ID         : ADC_DUD_ACT_045_GBL004, ADC_DUD_ACT_045_GBL005, ADC_DUD_ACT_045_GBL006,
** Reference ID         : ADC_DUD_ACT_045_REG001, ADC_DUD_ACT_045_REG002, ADC_DUD_ACT_045_REG003,
** Reference ID         : ADC_DUD_ACT_045_REG004
***********************************************************************************************************************/
#if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
     (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON) || \
     (ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
#if ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON) || (ADC_ENABLE_DMA_MODE == STD_ON))

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(boolean, ADC_CODE_FAST) Adc_CheckError(const Adc_GroupType LddGroup)
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
       (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON) || \
       (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  #endif
  #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
       (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON))
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  #endif
  uint8 LucHwUnitIndex;
  #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
       (ADC_ENABLE_OVERWRITE_ERR == STD_ON))
  uint8 LucErrorVirCh;
  uint8 LucPhysCh;
  #endif
  #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_OVERWRITE_ERR == STD_ON))
  uint8 LucStartVirCh;
  uint8 LucEndVirCh;
  #endif
  #if ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF))
  uint8 LucIderValue;
  #if (ADC_ENABLE_PWM_DIAG == STD_ON)
  uint8 LucChannelToGroupIndex;
  #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
  #endif
  #if (ADC_ENABLE_OVERWRITE_ERR == STD_ON)
  uint8 LucOwerValue;
  #endif
  #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
  uint8 LucSgUnitId;
  uint8 LucTocerValue;
  #endif
  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  uint32 LulVclmsrValue;
  uint32 LulRegSel;
  uint32 LulBitLoc;
  #endif
  boolean LblErrorFlag;

  /* Get the pointer to the group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the hardware unit index to which the group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  /* Get the pointer to the hardware unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
       (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON) || \
       (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
  /* Get the pointer to the runtime data of the group */
  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */
  #endif

  /* Initialize the error flag */
  LblErrorFlag = ADC_FALSE;

  #if ((ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
  /* Check if error interrupt is enabled */
  if (ADC_TRUE == LpHwUnitConfig->blInterruptErr)                                                                       /* PRQA S 2814 # JV-01 */
  {
    #if (((((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON)) && \
          (ADC_ENABLE_ERR_INT == STD_ON)) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
    /* Read and clear conversion error flag from error interrupt */
    LblErrorFlag = LpGroupData->blConvError;                                                                            /* PRQA S 2814 # JV-01 */
    if (ADC_TRUE == LblErrorFlag)
    {
      LpGroupData->blConvError = ADC_FALSE;
    } /* else: No action required */
    #endif
  }
  else
  #endif /* ((ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON)) */
  {
    #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
         (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON))
    /* Get the base register address of the hardware unit */
    LpAdcRegisters = LpHwUnitConfig->pHwUnitBaseAddress;
    #endif

    /* Get the error status */
    #if ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF))
    LucIderValue = LpAdcRegisters->ucADCXnIDER;                                                                         /* PRQA S 2814 # JV-01 */
    #endif
    #if (ADC_ENABLE_OVERWRITE_ERR == STD_ON)
    LucOwerValue = LpAdcRegisters->ucADCXnOWER;
    #endif
    #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
    LucTocerValue = LpAdcRegisters->ucADCXnTOCER;                                                                       /* PRQA S 2814 # JV-01 */
    #endif

    #if (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_OVERWRITE_ERR == STD_ON))
    #if ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF) && (ADC_ENABLE_PWM_DIAG == STD_ON))
    if (ADC_TRUE == LpGroup->blPwmDiag)
    {
      /* Set the group channel range to PWM-Diag channel */
      LucStartVirCh = ADC_ADCX_IDER_IDECAP_PWD;
      LucEndVirCh = ADC_ADCX_IDER_IDECAP_PWD;
    }
    else
    #endif /* ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF) && (ADC_ENABLE_PWM_DIAG == STD_ON)) */
    #if (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW)
    /* Get the virtual channel information of the group */
    if (ADC_GROUP_REPL_SUSPEND_RESUME == LpGroup->enGroupReplacement)
    {
      LucStartVirCh = LpGroup->ucStartVirChPtr + LpGroupData->ucChannelsCompleted;
      LucEndVirCh = LucStartVirCh;
    }
    else
    #endif /* (ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) */
    {
      LucStartVirCh = LpGroup->ucStartVirChPtr;
      LucEndVirCh = (uint8)(LucStartVirCh + LpGroupData->ucChannelCount - ADC_BYTE_ONE);
    }
    #endif /* (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_OVERWRITE_ERR == STD_ON)) */

    #if ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF))
    /* Check the Id error status */
    if (ADC_BYTE_ZERO != (uint8)(LucIderValue & ADC_ADCX_IDER_IDE))
    {
      /* Get the virtual channel captured due to an Id error */
      LucErrorVirCh = (uint8)(LucIderValue & ADC_ADCX_IDER_IDECAP);
      if ((LucStartVirCh <= LucErrorVirCh) && (LucErrorVirCh <= LucEndVirCh))
      {
        /* Set the conversion error status */
        LblErrorFlag = ADC_TRUE;

        #if (ADC_ENABLE_PWM_DIAG == STD_ON)
        if (ADC_TRUE == LpGroup->blPwmDiag)
        {
          /* Get the channel from the group channel configuration as PWM-Diag has no virtual channel */
          LucChannelToGroupIndex = LpGroup->ucChannelToGroupIndex;
          LucPhysCh = (uint8)(Adc_GpChannelToGroup[LucChannelToGroupIndex] & ADC_CHANNEL_ID_MASK);                      /* PRQA S 2824 # JV-01 */
        }
        else
        #endif /* (ADC_ENABLE_PWM_DIAG == STD_ON) */
        {
          /* Get and store the physical channel where the Id error occurred */
          LucPhysCh = (uint8)(LpAdcRegisters->aaADCXnVCR[LucErrorVirCh] & ADC_ADCX_VCR_GCTRL);                          /* PRQA S 2844 # JV-01 */
        }
        LpGroupData->ucChannelIdError = LucPhysCh;
        /* Clear Id error status */
        LpAdcRegisters->ddADCXnECR = ADC_ADCX_ECR_IDEC;
      } /* end of if ((LucStartVirCh <= LucErrorVirCh) && (LucErrorVirCh <= LucEndVirCh)) */
        /* else: No action required */
    } /* end of if (ADC_BYTE_ZERO != (uint8)(LucIderValue & ADC_ADCX_IDER_IDE)) */
      /* else: No action required */
    #endif /* ((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) */

    #if (ADC_ENABLE_OVERWRITE_ERR == STD_ON)
    /* Check the overwrite error status */
    if (ADC_BYTE_ZERO != (uint8)(LucOwerValue & ADC_ADCX_OWER_OWE))
    {
      /* Get the virtual channel captured due to an overwrite error */
      LucErrorVirCh = (uint8)(LucOwerValue & ADC_ADCX_OWER_OWECAP);
      if ((LucStartVirCh <= LucErrorVirCh) && (LucErrorVirCh <= LucEndVirCh))
      {
        /* Get and store the channel where the overwrite error occurred */
        LucPhysCh = (uint8)(LpAdcRegisters->aaADCXnVCR[LucErrorVirCh] & ADC_ADCX_VCR_GCTRL);
        LpGroupData->ucChannelOverwritten = LucPhysCh;
        /* Clear error status */
        LpAdcRegisters->ddADCXnECR = ADC_ADCX_ECR_OWEC;
      } /* else: No action required */
    } /* else: No action required */
    #endif /* (ADC_ENABLE_OVERWRITE_ERR == STD_ON) */

    #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
    /* Get the SG unit Id of the group */
    LucSgUnitId = Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex].ucSgUnitId;                                                /* PRQA S 2824 # JV-01 */
    /* Check the trigger overlap check status */
    if (ADC_BYTE_ZERO != (uint8)(LucTocerValue & (uint8)(ADC_ADCX_TOCER_TOCESG_LSB << LucSgUnitId)))
    {
      /* Set the error status */
      LpGroupData->blTriggerOverlapped = ADC_TRUE;                                                                      /* PRQA S 2814 # JV-01 */
      /* Clear error status */
      LpAdcRegisters->ddADCXnECR = (Adc_ErrClearRegType)(ADC_ADCX_ECR_TOCESGC_LSB << LucSgUnitId);
    } /* else: No action required */
    #endif /* (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON) */

    #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    if (ADC_TRUE == LpGroup->blLimitCheckEnabled)
    {
      /* Get the values of upper/lower limit check error status registers */
      LulRegSel = ((uint32)LpGroup->ucStartVirChPtr >> ADC_ADCX_VCLMSR_HIGH_SHIFT) & ADC_ADCX_VCLMSR_HIGH_MASK;
      LulBitLoc = (uint32)LpGroup->ucStartVirChPtr & ADC_ADCX_VCLMSR_LOW_MASK;
      LulVclmsrValue = LpAdcRegisters->aaADCXnVCLMSR[LulRegSel] & (1UL << LulBitLoc);
      if (0UL != LulVclmsrValue)
      {
        /* Set the conversion error status */
        LblErrorFlag = ADC_TRUE;
        /* Get and store the physical channel where the limit check error occurred */
        LucErrorVirCh = LpGroup->ucStartVirChPtr;
        LucPhysCh = (uint8)(LpAdcRegisters->aaADCXnVCR[LucErrorVirCh] & ADC_ADCX_VCR_GCTRL);
        LpGroupData->ucChannelLimitError = LucPhysCh;
        /* Clear error status */
        LpAdcRegisters->aaADCXnVCLMSCR[LulRegSel] = LulVclmsrValue;
      } /* else: No action required */
    } /* end of if (ADC_TRUE == LpGroup->blLimitCheckEnabled) */
      /* else: No action required */
    #endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */
  }

  return LblErrorFlag;
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /*
        * ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON) || (ADC_ENABLE_DMA_MODE == STD_ON))
        */
#endif /*
        * (((ADC_ENABLE_ID_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
        *  (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON) || \
        *  (ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
        */

/***********************************************************************************************************************
** Function Name        : Adc_ReportError
**
** Service ID           : NA
**
** Description          : This internal function reports errors to Dem and
**                        invokes error notification callback functions.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different Groups, Non-Reentrant for same Group
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpHwUnitConfig, Adc_GpSgUnitConfig, Adc_GpGroupRamData
**
** Functions invoked    : ADC_DEM_REPORT_ERROR, pErrorNotificationPointer, pErrorNotificationPointerSG
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_076, ADC_DUD_ACT_076_ERR001, ADC_DUD_ACT_076_ERR002,
** Reference ID         : ADC_DUD_ACT_076_GBL001, ADC_DUD_ACT_076_GBL002, ADC_DUD_ACT_076_GBL003,
** Reference ID         : ADC_DUD_ACT_076_GBL004, ADC_DUD_ACT_076_GBL005
***********************************************************************************************************************/
#if ((ADC_ENABLE_ERR == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON))
#if ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON) || (ADC_ENABLE_DMA_MODE == STD_ON))

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_CODE_FAST) Adc_ReportError(const Adc_GroupType LddGroup)
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2CONST(Adc_HwUnitConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpHwUnitConfig;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  uint8 LucHwUnitIndex;
  #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
  uint8 LucSgUnitId;
  #endif
  #if ((ADC_ENABLE_ID_ERR == STD_ON) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
       (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON))
  uint8 LucErrCh;
  uint8 LucPhysCh;

  /* Initialize the local variable for storing the physical channel */
  LucPhysCh = ADC_INVALID_CHANNELID;
  #endif

  /* Get the pointer to the group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the hardware unit index to which the group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  /* Get the pointer to the hardware unit configuration */
  LpHwUnitConfig = &Adc_GpHwUnitConfig[LucHwUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the pointer to the runtime data of the group */
  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */

  #if (ADC_ENABLE_OVERWRITE_ERR == STD_ON)
  /* Get and clear the channel where overwrite error occurs */
  LucErrCh = LpGroupData->ucChannelOverwritten;                                                                         /* PRQA S 2814 # JV-01 */
  if (ADC_INVALID_CHANNELID != LucErrCh)
  {
    LucPhysCh = LucErrCh;
    LpGroupData->ucChannelOverwritten = ADC_INVALID_CHANNELID;
  } /* else: No action required */
  #endif /* (ADC_ENABLE_OVERWRITE_ERR == STD_ON) */

  #if (ADC_ENABLE_ID_ERR == STD_ON)
  /* Get and clear the channel where Id error occurs */
  LucErrCh = LpGroupData->ucChannelIdError;
  if (ADC_INVALID_CHANNELID != LucErrCh)
  {
    LucPhysCh = LucErrCh;
    LpGroupData->ucChannelIdError = ADC_INVALID_CHANNELID;
    /* Report the Id error to Dem */
    ADC_DEM_REPORT_ERROR(ADC_E_ID_FAILURE, DEM_EVENT_STATUS_FAILED);
  } /* else: No action required */
  #endif /* (ADC_ENABLE_ID_ERR == STD_ON) */

  #if (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON)
  /* Get and clear the status of trigger overlap error */
  if (ADC_TRUE == LpGroupData->blTriggerOverlapped)                                                                     /* PRQA S 2814 # JV-01 */
  {
    LpGroupData->blTriggerOverlapped = ADC_FALSE;

    /* Invoke the callback function if it is configured */
    if (NULL_PTR != LpHwUnitConfig->pErrorNotificationPointerSG)                                                        /* PRQA S 2814 # JV-01 */
    {
      LucSgUnitId = Adc_GpSgUnitConfig[LpGroup->ucSgUnitIndex].ucSgUnitId;                                              /* PRQA S 2824 # JV-01 */
      LpHwUnitConfig->pErrorNotificationPointerSG(LucSgUnitId);                                                         /* PRQA S 2814 # JV-01 */
    } /* else: No action required */
  } /* else: No action required */
  #endif /* (ADC_ENABLE_TRIGGER_OVERLAP_ERR == STD_ON) */

  #if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
  /* Get and clear the channel where limit check error occurs */
  LucErrCh = LpGroupData->ucChannelLimitError;
  if (ADC_INVALID_CHANNELID != LucErrCh)
  {
    LucPhysCh = LucErrCh;
    LpGroupData->ucChannelLimitError = ADC_INVALID_CHANNELID;
  } /* else: No action required */
  #endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */

  #if (ADC_ENABLE_PARITY_ERR == STD_ON)
  /* Get and clear the channel where parity error occurs */
  LucErrCh = LpGroupData->ucChannelParityError;
  if (ADC_INVALID_CHANNELID != LucErrCh)
  {
    LucPhysCh = LucErrCh;
    LpGroupData->ucChannelParityError = ADC_INVALID_CHANNELID;
    /* Report the parity error to Dem */
    ADC_DEM_REPORT_ERROR(ADC_E_PARITY_FAILURE, DEM_EVENT_STATUS_FAILED);
  } /* else: No action required */
  #endif /* (ADC_ENABLE_PARITY_ERR == STD_ON) */

  #if ((ADC_ENABLE_ID_ERR == STD_ON) || (ADC_ENABLE_LIMIT_CHECK == STD_ON) || \
       (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON))
  /* Invoke the error notification callback function if there are any errors */
  if (ADC_INVALID_CHANNELID != LucPhysCh)
  {
    if (NULL_PTR != LpHwUnitConfig->pErrorNotificationPointer)
    {
      /*
       * Invoke the call-back function
       * When multiple errors, only one channel is notified with priority of overwrite < ID < limit < parity
       */
      LpHwUnitConfig->pErrorNotificationPointer(LucPhysCh);
    } /* else: No action required */
  } /* else: No action required */
  #endif
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /*
        * ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON) || (ADC_ENABLE_DMA_MODE == STD_ON))
        */
#endif /* ((ADC_ENABLE_ERR == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON)) */

/***********************************************************************************************************************
** Function Name        : Adc_CallGroupNotify
**
** Service ID           : NA
**
** Description          : This internal function calls the group notification
**                        function in a state where conversion of all channels
**                        of the group requested is completed.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : The conversion of the group specified.
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpGroupRamData
**
** Functions invoked    : pGroupNotificationPointer
**
** Registers Used       : None
**
** Reference ID         : ADC_DUD_ACT_046
***********************************************************************************************************************/
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
#if ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON) || (ADC_ENABLE_DMA_MODE == STD_ON))

#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_PRIVATE_CODE) Adc_CallGroupNotify(const Adc_GroupType LddGroup)
{
  /* Invoke notification function if enabled */
  if ((ADC_TRUE == Adc_GpGroupRamData[LddGroup].blNotifyStatus) &&                                                      /* PRQA S 2824 # JV-01 */
      (NULL_PTR != Adc_GpGroupConfig[LddGroup].pGroupNotificationPointer))                                              /* PRQA S 2824 # JV-01 */
  {
    Adc_GpGroupConfig[LddGroup].pGroupNotificationPointer();                                                            /* PRQA S 2814 # JV-01 */
  } /* else: No action required */
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /*
        * ((ADC_FUNCTIONALITY_MODE != ADC_POLLING) || (ADC_READ_GROUP_API == STD_ON) || (ADC_ENABLE_DMA_MODE == STD_ON))
        */
#endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_DmaIsr
**
** Service ID           : NA
**
** Description          : This internal function shall be an DMA completer
**                        interrupt service routine for ADC Driver.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LucHwUnitIndex, LucSgUnitIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpSgUnitConfig, Adc_GpHwUnitConfig, Adc_GpGroupRamData,
**                        Adc_GpSgUnitRamData, Adc_GaaHwUnitData, Adc_GucMaxSwTriggGroups
**
** Functions invoked    : Adc_CallGroupNotify, Adc_CheckError, Adc_CheckParity, Adc_ConfigureGroupForConversion,
**                        ADC_DEM_REPORT_ERROR, Adc_DisableDetection, Adc_DmaClearInterruptFlag, Adc_DmaDisable,
**                        Adc_DmaGetTransferStatus, ADC_ENTER_CRITICAL_SECTION, ADC_EXIT_CRITICAL_SECTION,
**                        Adc_HwStopScanGroup, Adc_PicClearHwTrigger, Adc_PopFromQueue, Adc_ReportError,
**                        Adc_SetStatus
**
** Registers Used       : ADCXnADTENDCRx
**
** Reference ID         : ADC_DUD_ACT_065, ADC_DUD_ACT_065_CRT001, ADC_DUD_ACT_065_CRT006,
** Reference ID         : ADC_DUD_ACT_065_ERR001, ADC_DUD_ACT_065_GBL002, ADC_DUD_ACT_065_GBL003,
** Reference ID         : ADC_DUD_ACT_065_GBL004, ADC_DUD_ACT_065_GBL005, ADC_DUD_ACT_065_GBL006,
** Reference ID         : ADC_DUD_ACT_065_GBL008, ADC_DUD_ACT_065_REG001, ADC_DUD_ACT_065_GBL009
***********************************************************************************************************************/
#if (ADC_ENABLE_DMA_MODE == STD_ON)

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ADC_CODE_FAST) Adc_DmaIsr(const uint8 LucHwUnitIndex, const uint8 LucSgUnitIndex)                            /* PRQA S 1505 # JV-01 */
{
  P2VAR(volatile Adc_SgUnitRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpSgUnitData;
  P2VAR(volatile Adc_ChannelGroupRamData, AUTOMATIC, ADC_VAR_NO_INIT) LpGroupData;
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  #if (ADC_ENABLE_ADTIMER == STD_ON)
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */
  /* Local variable to store the group number */
  Adc_GroupType LddGroup;
  uint8 LucSgUnitId;
  #if (((ADC_ENABLE_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || \
       (ADC_ENABLE_LIMIT_CHECK == STD_ON) || (ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON))
  boolean LblErrorFlag;
  #endif
  #if (ADC_ENABLE_STREAMING == STD_ON)
  uint8 LucFirstHalf;
  #endif /* (ADC_ENABLE_STREAMING == STD_ON) */
  boolean LblDmaTimedOut;
  boolean LblHwTimedOut;
  boolean LblDataAvailable;
  boolean LblConversionCompleted;
  #if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
       ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
  uint8 LddNextGroup;
  #endif

  /* Initialize DMA transfer completion flag to ADC_TRUE */
  LblDataAvailable = ADC_TRUE;
  /* Initialize timeout flags to ADC_FALSE */
  LblDmaTimedOut = ADC_FALSE;
  LblHwTimedOut = ADC_FALSE;
  /* Initialize the conversion completed flag */
  LblConversionCompleted = ADC_FALSE;
  /* Get the pointer to the SG unit runtime data */
  LpSgUnitData = &Adc_GpSgUnitRamData[LucSgUnitIndex];                                                                  /* PRQA S 2824 # JV-01 */
  /* Get the current conversion group number */
  LddGroup = LpSgUnitData->ddCurrentConvGroup;                                                                          /* PRQA S 2814 # JV-01 */
  /* Get the pointer to the group runtime data */
  LpGroupData = &Adc_GpGroupRamData[LddGroup];                                                                          /* PRQA S 2824 # JV-01 */
  /* Get the pointer to the group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the SG unit Id */
  LucSgUnitId = Adc_GpSgUnitConfig[LucSgUnitIndex].ucSgUnitId;                                                          /* PRQA S 2824 # JV-01 */
  #if (ADC_ENABLE_ADTIMER == STD_ON)
  /* Get the base register address of the hardware unit */
  LpAdcRegisters = Adc_GpHwUnitConfig[LucHwUnitIndex].pHwUnitBaseAddress;                                               /* PRQA S 2824 # JV-01 */
  #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */

  /* Enter the critical section protection */
  ADC_ENTER_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

  #if (ADC_FUNCTIONALITY_MODE != ADC_INTERRUPT)
  if (ADC_POLLING_MODE == Adc_GpSgUnitConfig[LucSgUnitIndex].enFunctionalityModeType)                                   /* PRQA S 2824 # JV-01 */
  {
    /* Check DMA completion status when called in polling mode */
    LblDataAvailable = Adc_DmaGetTransferStatus(LddGroup);
  } /* else: No action required */

  if (ADC_TRUE == LblDataAvailable)
  #endif /* (ADC_FUNCTIONALITY_MODE != ADC_INTERRUPT) */
  {
    /* Clear DMA transfer end flag */
    Adc_DmaClearInterruptFlag(LddGroup);

    #if (((ADC_ENABLE_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || \
         (ADC_ENABLE_LIMIT_CHECK == STD_ON) || (ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR_INT == STD_ON))
    /* Get and check the error status including the parity error when using the error interrupt */
    LblErrorFlag = Adc_CheckError(LddGroup);
    if (ADC_TRUE == LblErrorFlag)
    {
      /* Clear the read data available flag */
      LblDataAvailable = ADC_FALSE;
    } /* else: No action required */
    #endif

    #if (ADC_ENABLE_PARITY_ERR == STD_ON)
    #if (ADC_ENABLE_PARITY_ERR_INT == STD_ON)
    /* Check if error interrupt is disabled */
    if (ADC_FALSE == Adc_GpHwUnitConfig[LucHwUnitIndex].blInterruptErr)                                                 /* PRQA S 2824 # JV-01 */
    #endif /* (ADC_ENABLE_PARITY_ERR_INT == STD_ON) */
    {
      /* Check for parity error that may occur when read by DMA */
      LblErrorFlag = Adc_CheckParity(LddGroup);
      if (ADC_TRUE == LblErrorFlag)
      {
        /* Clear the read data available flag */
        LblDataAvailable = ADC_FALSE;
      } /* else: No action required */
    } /* else: No action required */
    #endif /* (ADC_ENABLE_PARITY_ERR == STD_ON) */

    #if (ADC_ENABLE_STREAMING == STD_ON)
    /* Increment the counter even if there is an error in case of streaming in DMA */
    if (ADC_ACCESS_MODE_STREAMING == LpGroup->enGroupAccessMode)                                                        /* PRQA S 2814 # JV-01 */
    {
      /* First half streaming sample */
      LucFirstHalf = (uint8)(((uint32)LpGroup->ddNumberofSamples + 1UL) >> 1U);                                         /* PRQA S 3383 # JV-01 */

      /* Update the number of completed samples. (Possible values are 0, half, full) */
      if (LpGroupData->ucSamplesCompleted != LucFirstHalf)                                                              /* PRQA S 2814 # JV-01 */
      {
        LpGroupData->ucSamplesCompleted = LucFirstHalf;
      }
      else
      {
        LpGroupData->ucSamplesCompleted = LpGroup->ddNumberofSamples;
      }

      if (LpGroupData->ucSamplesCompleted == LpGroup->ddNumberofSamples)
      {
        /* All samples have completed the conversion */
        Adc_SetStatus(LddGroup, ADC_STREAM_COMPLETED);

        if (ADC_STREAM_BUFFER_LINEAR == LpGroup->enStreamBufferMode)
        {
          LblConversionCompleted = ADC_TRUE;
        } /* else: No action required */
      }
      else
      {
        /* Half of the samples have completed the conversion */
        Adc_SetStatus(LddGroup, ADC_COMPLETED);
      }

      /* Set the flag indicating Adc_ReadGroup or Adc_GetStreamLastPointer should be called */
      LpGroupData->blResultRead = ADC_FALSE;
      /* Set the read data enable flag for streaming even if any error occurs */
      LblDataAvailable = ADC_TRUE;
    } /* end of if (ADC_ACCESS_MODE_STREAMING == LpGroup->enGroupAccessMode) */
    else
    #endif /* (ADC_ENABLE_STREAMING == STD_ON) */
    {
      /* Discard data if an error occurs in DMA single mode */
      #if (((ADC_ENABLE_ERR == STD_ON) && (ADC_IP_ADCH == STD_OFF)) || (ADC_ENABLE_OVERWRITE_ERR == STD_ON) || \
           (ADC_ENABLE_LIMIT_CHECK == STD_ON) || (ADC_ENABLE_ERR_INT == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON))
      #if (ADC_TRACK_AND_HOLD == STD_ON)
      /* If the requested group is for T&H, do not discard the result even when error is detected */
      if (ADC_TH_DISABLED != LpGroup->ucTrackAndHoldGroup)                                                              /* PRQA S 2814 # JV-01 */
      {
        /* Set the read data available flag even if the error occurs */
        LblDataAvailable = ADC_TRUE;
      } /* else: No action required */
      #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

      if (ADC_TRUE == LblDataAvailable)
      #endif
      {
        /* Update the completed conversion samples */
        LpGroupData->ucSamplesCompleted = ADC_COUNT_BYTE_ONE;                                                           /* PRQA S 2814 # JV-01 */
        /* Stop scan group if requested group is implicitly stopped */
        if (ADC_TRUE == LpGroup->blImplicitlyStopped)                                                                   /* PRQA S 2814 # JV-01 */
        {
          LblConversionCompleted = ADC_TRUE;
        } /* else: No action required */
        Adc_SetStatus(LddGroup, ADC_STREAM_COMPLETED);
        /* Set the flag indicating Adc_ReadGroup or Adc_GetStreamLastPointer should be called */
        LpGroupData->blResultRead = ADC_FALSE;
      } /* else: No action required */
    }

    /* Check whether current group is implicitly stopped or not */
    if (ADC_TRUE == LblConversionCompleted)
    {
      /* Stop the DMA and scan group */
      LblDmaTimedOut = Adc_DmaDisable(LddGroup);
      LblHwTimedOut = Adc_HwStopScanGroup(LddGroup, ADC_FALSE);

      #if (ADC_ENABLE_PIC_TSEL == STD_ON)
      /* Check if the conversion is HW Triggered */
      if (LddGroup >= Adc_GucMaxSwTriggGroups)
      {
        /* Clear to avoid conversion on next HW trigger */
        Adc_PicClearHwTrigger(LddGroup);
      } /* else: No action required */
      #endif /* (ADC_HW_TRIGGER_API == STD_ON) */

      #if ((ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON) || \
           (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) || (ADC_ENABLE_WIRE_BRK == STD_ON))
      /* Disable self-diagnosis pin level and wiring break detection if they are configured */
      Adc_DisableDetection(LddGroup);
      #endif

      /* Change SG unit status to inactive */
      LpSgUnitData->blSgUnitStatus = ADC_FALSE;
      Adc_GaaHwUnitData[LucHwUnitIndex].ucSgUnitStatus &= ~(1U << LucSgUnitId);                                         /* PRQA S 2844 # JV-01 */

      #if ((ADC_ENABLE_START_STOP_GROUP_API == STD_ON) && \
           ((ADC_PRIORITY_IMPLEMENTATION == ADC_PRIORITY_HW_SW) || (ADC_ENABLE_QUEUING == STD_ON)))
      /* Check if DMA and SG are stopped */
      if ((ADC_FALSE == LblDmaTimedOut) && (ADC_FALSE == LblHwTimedOut))
      {
        /* Fetch the next group for conversion if the queue is not empty */
        LddNextGroup = Adc_PopFromQueue(LucSgUnitIndex);
        if (ADC_INVALID_GROUP != LddNextGroup)
        {
          Adc_ConfigureGroupForConversion(LddNextGroup);
        } /* else: No action required */
      } /* else: No action required */
      #endif
    } /* end of if (ADC_TRUE == LblConversionCompleted) */
    else
    {
      #if (ADC_ENABLE_ADTIMER == STD_ON)
      /* If AD timer is enabled and group is one-shot, just stop AD timer */
      if ((ADC_TRUE == LpGroup->blAdcEnableAdTimerTriggMode) && (ADC_CONV_MODE_ONESHOT == LpGroup->enGroupConvMode))
      {
        LpAdcRegisters->aaADCXnSG[LucSgUnitId].ucADCXnADTENDCRx = ADC_ADCX_ADTENDCR_ADTEND;                             /* PRQA S 2814, 2844 # JV-01, JV-01 */
      } /* else: No action required */
      #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */
    }
  } /* end of if (ADC_TRUE == LblDataAvailable) */
    /* else: No action required */

  /* Exit the critical section protection */
  ADC_EXIT_CRITICAL_SECTION(ADC_RAM_DATA_PROTECTION);

  if (ADC_TRUE == LblDataAvailable)
  {
    #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    /* Call to notification function */
    Adc_CallGroupNotify(LddGroup);
    #endif

    /* Report an error to Dem if some timeouts occur */
    if ((ADC_TRUE == LblDmaTimedOut) || (ADC_TRUE == LblHwTimedOut))
    {
      ADC_DEM_REPORT_ERROR(ADC_E_TIMEOUT, DEM_EVENT_STATUS_FAILED);
    } /* else: No action required */
  } /* else: No action required */

  #if ((ADC_ENABLE_ERR == STD_ON) || (ADC_ENABLE_PARITY_ERR == STD_ON))
  /* Report errors to Dem and invokes error notification callback functions, if any errors are detected */
  Adc_ReportError(LddGroup);
  #endif
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (ADC_ENABLE_DMA_MODE == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Adc_HwStopScanGroup
**
** Service ID           : NA
**
** Description          : This internal function stops a specific Scan Group.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LddGroup, LblForced
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : boolean
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpHwUnitConfig, Adc_GpSgUnitConfig, Adc_GaaHwUnitData
**
** Functions invoked    : Adc_TrackHoldDisable
**
** Registers Used       : ADCXnADHALTR, ADCXnADTENDCRx, ADCXnSGCRx, ADCXnSGSRx, ADCXnSGSTPCRx
**
** Reference ID         : ADC_DUD_ACT_071, ADC_DUD_ACT_071_REG002, ADC_DUD_ACT_071_REG003,
** Reference ID         : ADC_DUD_ACT_071_REG007, ADC_DUD_ACT_071_REG011
***********************************************************************************************************************/
#define ADC_START_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(boolean, ADC_PRIVATE_CODE) Adc_HwStopScanGroup(const Adc_GroupType LddGroup, const boolean LblForced)
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;
  P2CONST(Adc_HwSgUnitType, AUTOMATIC, ADC_CONFIG_DATA) LpSgUnitConfig;
  P2VAR(volatile Adc_SGRegType, AUTOMATIC, REGSPACE) LpSGRegisters;
  P2CONST(volatile Adc_HwUnitDataType, AUTOMATIC, ADC_VAR_NO_INIT) LpHwUnitData;
  uint32 LulDelayCount;
  uint8 LucHwUnitIndex;
  uint8 LucSgUnitIndex;
  uint8 LucSgUnitId;
  uint8 LucSgUnitStatus;
  boolean LblHwTimedOut;

  /* Get the group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the hardware unit index to which the group belongs */
  LucHwUnitIndex = LpGroup->ucHwUnitIndex;                                                                              /* PRQA S 2814 # JV-01 */
  /* Read the base configuration address of the hardware unit */
  LpAdcRegisters = Adc_GpHwUnitConfig[LucHwUnitIndex].pHwUnitBaseAddress;                                               /* PRQA S 2824 # JV-01 */
  /* Get the SG unit to which the channel group is mapped */
  LucSgUnitIndex = LpGroup->ucSgUnitIndex;
  /* Get the SG unit which is configured for this group */
  LpSgUnitConfig = &Adc_GpSgUnitConfig[LucSgUnitIndex];                                                                 /* PRQA S 2824 # JV-01 */
  /* Get the SG unit Id */
  LucSgUnitId = LpSgUnitConfig->ucSgUnitId;                                                                             /* PRQA S 2814 # JV-01 */
  /* Get the pointer to SG register */
  LpSGRegisters = &LpAdcRegisters->aaADCXnSG[LucSgUnitId];                                                              /* PRQA S 2814, 2934 # JV-01, JV-01 */
  /* Get the pointer to the HW unit data */
  LpHwUnitData = &Adc_GaaHwUnitData[LucHwUnitIndex];                                                                    /* PRQA S 2934 # JV-01 */
  /* Get the status of all other SG units in the HW unit */
  LucSgUnitStatus = LpHwUnitData->ucSgUnitStatus;                                                                       /* PRQA S 2844 # JV-01 */

  /* Initialize scan group stop timeout flag to ADC_FALSE */
  LblHwTimedOut = ADC_FALSE;

  #if (ADC_TRACK_AND_HOLD == STD_ON)
  /* Check if all other SGs are inactive when the T&H groups are explicitly stopped */
  if (((ADC_TRUE == LblForced) || (ADC_TH_DISABLED == LpGroup->ucTrackAndHoldGroup)) &&
      ((uint8)0U == (uint8)(LucSgUnitStatus & (uint8)~(1U << LucSgUnitId))) &&
      (ADC_TH_SAMPLING == LpHwUnitData->ucTrackHoldStatus))
  {
    /* Stop T&H sampling */
    Adc_TrackHoldDisable(LddGroup);
  }
  else
  #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */
  {
    /* Check if the requested group is not stopped */
    if ((uint8)0UL != (uint8)(LucSgUnitStatus & (uint8)(1U << LucSgUnitId)))
    {
      #if (ADC_TRACK_AND_HOLD == STD_ON)
      /* Check if the requested group is configured as T&H and it stops explicitly */
      if ((ADC_TRUE == LblForced) && (ADC_TH_DISABLED == LpGroup->ucTrackAndHoldGroup))
      {
        /* Disable T&H hold trigger */
        Adc_TrackHoldDisable(LddGroup);
      } /* else: No action required */
      #endif /* (ADC_TRACK_AND_HOLD == STD_ON) */

      /* Disable trigger mode and conversion end interrupt */
      LpSGRegisters->ucADCXnSGCRx &= (uint8)~(ADC_ADCX_SGCR_TRGMD | ADC_ADCX_SGCR_ADIE);                                /* PRQA S 2844 # JV-01 */

      #if (ADC_ENABLE_ADTIMER == STD_ON)
      /* Stop the AD Timer if the requested group has AD Timer Trigger */
      if (ADC_TRUE == LpGroup->blAdcEnableAdTimerTriggMode)
      {
        LpSGRegisters->ucADCXnADTENDCRx = ADC_ADCX_ADTENDCR_ADTEND;
      } /* else: No action required */
      #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */

      /* Check If the request is an explicit stop or the requested group uses continuous scan mode */
      if ((ADC_TRUE == LblForced) || ((uint8)0U != LpGroup->ucScanMode))
      {
        /* Check if any other SG is active */
        if ((uint8)0U != (uint8)(LucSgUnitStatus & (uint8)~(1U << LucSgUnitId)))
        {
          /* Set A/D conversion stop for Scan Group x Stop Control Register */
          LpSGRegisters->ucADCXnSGSTPCRx = ADC_ADCX_SGSTPCR_SGSTP;

          #if (ADC_ENABLE_ADTIMER == STD_ON)
          /* Wait for the AD Timer to stop if the requested group uses AD Timer Trigger */
          if (ADC_TRUE == LpGroup->blAdcEnableAdTimerTriggMode)
          {
            /* Initialize the delay loop count to zero */
            LulDelayCount = ADC_AD_TIMER_TIMEOUT_COUNT;
            while (((uint8)0U != (uint8)(LpSGRegisters->ucADCXnSGSRx & ADC_ADTACT_STATUS)) && (LulDelayCount > 0UL))
            {
              LulDelayCount--;
            }
            if (0UL == LulDelayCount)
            {
              LblHwTimedOut = ADC_TRUE;
            } /* else: No action required */
          } /* else: No action required */

          /* Check if the AD Timer is stopped */
          if (ADC_FALSE == LblHwTimedOut)
          #endif /* (ADC_ENABLE_ADTIMER == STD_ON) */
          {
            /* Initialize the delay loop count to zero */
            LulDelayCount = LpSgUnitConfig->ulVcrProcessWait;
            /* Wait for the termination of the Scan Group x */
            while (((uint8)0U != (uint8)(LpSGRegisters->ucADCXnSGSRx & ADC_SGACT_STATUS)) && (LulDelayCount > 0UL))
            {
              LulDelayCount--;
            }
            /* Check if it has timed out */
            if (0UL == LulDelayCount)
            {
              /* Timed out, Can not stop scan group */
              LblHwTimedOut = ADC_TRUE;
            } /* else: No action required */
          } /* end of if (ADC_FALSE == LblHwTimedOut) */
            /* else: No action required */
        } /* end of if ((uint8)0U != (uint8)(LucSgUnitStatus & (uint8)~(1U << LucSgUnitId))) */
        else
        {
          /* Use HALT to stop the SG if only one SG is used */
          LpAdcRegisters->ucADCXnADHALTR = ADC_ADCX_ADHALTR_HALT;
        }
      } /* end of if ((ADC_TRUE == LblForced) || (ADC_CONV_MODE_CONTINUOUS == LpGroup->enGroupConvMode)) */
        /* else: No action required */
    } /* end of if ((uint8)0UL != (uint8)(LucSgUnitStatus & (uint8)(1U << LucSgUnitId))) */
      /* else: No action required */
  }

  return LblHwTimedOut;
}

#define ADC_STOP_SEC_PRIVATE_CODE
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Adc_DisableDetection
**
** Service ID           : NA
**
** Description          : This internal function disables self-diagnosis and wiring-break detection.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different HW units, Non-Reentrant for the same HW unit
**
** Input Parameters     : LddGroup
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Adc_GpGroupConfig, Adc_GpHwUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : ADCXnTDCR, ADCXnODCR
**
** Reference ID         : ADC_DUD_ACT_077, ADC_DUD_ACT_077_REG001, ADC_DUD_ACT_077_REG002, ADC_DUD_ACT_077_REG003
***********************************************************************************************************************/
#if ((ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON) || \
     (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) || (ADC_ENABLE_WIRE_BRK == STD_ON))

#define ADC_START_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC FUNC(void, ADC_CODE_FAST) Adc_DisableDetection(const Adc_GroupType LddGroup)
{
  P2CONST(Adc_GroupConfigType, AUTOMATIC, ADC_CONFIG_DATA) LpGroup;
  /* Pointer definition to store the base address of the ADC registers */
  P2VAR(volatile Adc_ConfigRegisters, AUTOMATIC, REGSPACE) LpAdcRegisters;

  /* Get the group configuration */
  LpGroup = &Adc_GpGroupConfig[LddGroup];                                                                               /* PRQA S 2824 # JV-01 */
  /* Get the base register address of the hardware unit */
  LpAdcRegisters = Adc_GpHwUnitConfig[LpGroup->ucHwUnitIndex].pHwUnitBaseAddress;                                       /* PRQA S 2814, 2824 # JV-01, JV-01 */

  #if (ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON)
  /* Check if Group Configured for Pin Level Diagnostic. */
  if (ADC_SELF_DIAG_PIN_LVL == LpGroup->enAdcSelfDiagMode)
  {
    /* Clear "ADCXnTDCR" Register */
    LpAdcRegisters->ucADCXnTDCR = ADC_REG_BYTE_INIT;                                                                    /* PRQA S 2814 # JV-01 */
  } /* else: No action required */
  #endif /* (ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON) */

  #if (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON)
  /* Check if self-diagnosis is wiring-break detection mode 1 (same as ADC_SELF_DIAG_WIRE_BRK for E2x) */
  if (ADC_SELF_DIAG_WIRE_BRK_MODE1 == LpGroup->enAdcSelfDiagMode)
  {
    /* Clear "ADCXnODCR" Register */
    LpAdcRegisters->ddADCXnODCR = ADC_ADCX_ODCR_INIT_VALUE;
  }
  else
  #endif /* (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) */
  {
    #if (ADC_ENABLE_WIRE_BRK == STD_ON)
    if (ADC_TRUE == LpGroup->blAdcEnableWiringBreakDetection)
    {
      LpAdcRegisters->ddADCXnODCR = ADC_ADCX_ODCR_INIT_VALUE;
    } /* else: No action required */
    #endif /* (ADC_ENABLE_WIRE_BRK == STD_ON) */
  }
}

#define ADC_STOP_SEC_CODE_FAST
#include "Adc_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /*
        * ((ADC_ENABLE_SELF_DIAG_PIN_LVL == STD_ON) || \
        *  (ADC_ENABLE_SELF_DIAG_WIRE_BRK == STD_ON) || (ADC_ENABLE_WIRE_BRK == STD_ON))
        */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
