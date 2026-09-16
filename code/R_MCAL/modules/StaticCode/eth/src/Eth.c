/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth.c                                                                                               */
/*====================================================================================================================*/
/*                                                  COPYRIGHT                                                         */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose: This file contains API implementations of Ethernet Driver Component.                                      */
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
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s)        */
/* and/or the Application.                                                                                            */
/*                                                                                                                    */
/* Each User is solely responsible for determining the appropriateness of using the Product(s) and assumes all risks  */
/* associated with its exercise of rights under this Agreement, including, but not limited to the risks and costs     */
/* of program errors, compliance with applicable laws, damage to or loss of data, programs or equipment,              */
/* and unavailability or interruption of operations.                                                                  */
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
/*                                        Devices:                X2x                                                 */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                          Revision Control History                                                  **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Remove DEM_EVENT_STATUS_PREFAILED after invoking Eth_HwPreCommonInit in Eth_Init
 *                        - As per ticket ARDAACL-53039:
 *                         Add ETH_E_COMMUNICATION implementation for ETNB, ETNF
 *                      : Updated QA-C 9.5.0 comments
 * 2.2.0: 31/12/2024    : Updated the condition to check ETH_E_INV_MODE det error in the Eth_SetControllerMode
 *                      : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 *                      : Correct the description for API Eth_MainFunction
 *        26/11/2024    : Updated QA-C 9.5.0 comments
 * 2.1.2: 13/11/2024    : Correct condition to raise Det_ReportError in Eth_Transmit()
 *        31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 30/08/2024    : Update QAC message
 *        16/07/2024    : Add declaration of Eth_GpDemEventUnintendedIntChk in Eth_Init
 *        15/07/2024    : Add Precompile invoke Eth_HwDeinit for ETND in Eth_DeInit
 *        19/06/2024    : Eth_Init, Eth_MainFunction, Eth_CommonDetCheck:
 *                        Move the all DET error checking to before starting the function's processing.
 *        17/06/2024    : Change Eth_HwWriteMiiBit function call from directly to function pointer in Eth_WriteMii. 
 *                      : Add check HW_IP type before invoke internal function in Eth_WriteMii and Eth_ReadMii.
 *        01/06/2024    : Add declare of Eth_GpBothCoreCfgPtr, Eth_GpGlobalPauseCfgPtr, Eth_GpGwcaRegPtr in Eth_Init
 *                      : Eth_DeInit(): Add get unit type step.
 *                      : Eth_Transmit: Add condition when report ETH_E_INV_PARAM for ETNF, ETNB, ETNC.
 *                      : Update QAC message.
 *                      : Eth_Init API: Add assign the config pointer value to global pointer for
 *                        Eth_GpCoreId2Index, Eth_GpTotalCtrlConfig, Eth_CtrlConfigIdx, Eth_GpDriverState.
 *                      : Change variant name
 *                        from Eth_GaaTotalCtrlConfig, Eth_GenDriverState, Eth_GaaGetCoreId2Index, Eth_GenDriverState
 *                        to Eth_GpTotalCtrlConfig, Eth_GpDriverState, Eth_GpCoreId2Index, Eth_GpDriverState.
 *                      : Change variable name
 *                        from Eth_GbDemEventAccess to Eth_GpDemEventAccess,
 *                        from Eth_GbDemEventRxFramesLost to Eth_GpDemEventRxFramesLost,
 *                        from Eth_GbDemEventCRC to Eth_GpDemEventCRC,
 *                        from Eth_GbDemEventUnderSizeFrame to Eth_GpDemEventUnderSizeFrame,
 *                        from Eth_GbDemEventOverSizeFrame to Eth_GpDemEventOverSizeFrame,
 *                        from Eth_GbDemEventAlignment to Eth_GpDemEventAlignment,
 *                        from Eth_GbDemEventSinglecollision to Eth_GpDemEventSinglecollision,
 *                        from Eth_GbDemEventMultiplecollision to Eth_GpDemEventMultiplecollision,
 *                        from Eth_GbDemEventLatecollision to Eth_GpDemEventLatecollision.
 *                      : Eth_Init API: Add assign the config pointer value to global pointer for Dem Event.
 *                      : Change variable name
 *                        from Eth_GaaDemEventAccess to Eth_GbDemEventAccess,
 *                        from Eth_GaaDemEventRxFramesLost to Eth_GbDemEventRxFramesLost,
 *                        from Eth_GaaDemEventCRC to Eth_GbDemEventCRC,
 *                        from Eth_GaaDemEventUnderSizeFrame to Eth_GbDemEventUnderSizeFrame,
 *                        from Eth_GaaDemEventOverSizeFrame to Eth_GbDemEventOverSizeFrame,
 *                        from Eth_GaaDemEventAlignment to Eth_GbDemEventAlignment,
 *                        from Eth_GaaDemEventSinglecollision to Eth_GbDemEventSinglecollision,
 *                        from Eth_GaaDemEventMultiplecollision to Eth_GbDemEventMultiplecollision,
 *                        from Eth_GaaDemEventLatecollision to Eth_GbDemEventLatecollision.
 *                      : Include Os.h when support multi core. Included for declaration of the function GetCoreID().
 *                      : Update ApiId when report ETH_E_INVALID_CORE.
 *                      : Change argument of Eth_SetStatus.
 *                      : Eth_Init, Eth_DeInit, Eth_MainFunction, Eth_CommonDetCheck APIs
 *                           + Get CoreID by os service GetCoreID().
 *                           + Check invalid core and report ETH_E_INVALID_CORE error when valid.
 *                           + Change number of loop from 0 to ETH_TOTAL_CTRL_CONFIG by 0
 *                             to Eth_GaaTotalCtrlConfig[LucCoreIndex].
 *                             index name change from LulCtrlIdx to LulIdx.
 *                           + Change variable LulCtrlIdx corresponding to controller index
 *                             which is argument of internal function and bit of array variable to 
 *                             Eth_CtrlConfigIdx[LucCoreIndex][LulIdx].
 *                      : Eth_SetStatus API: Check invalid core and report ETH_E_INVALID_CORE error when valid.
 *                      : Eth_CommonDetCheck API: Check invalid ctrl and report ETH_E_INVALID_CORE error when valid.
 *                      : Remove condition check ETH_DEM_EVENT_REPORTING_TYPE in function Eth_DemConfigCheck
 *                        for support R22-11
 *                      : Update QAC message
 *                      : Removed ETH_USING_MACRO and enable/diasable HW_IP macro by STD_ON/STD_OFF
 *                        Removed ETH_HW_NOT_LEGACY_MDIO, ETH_HW_COMMON_INIT and ETH_HW_COMMON_DEINIT
 *                      : Removed QA-C warning 1503, 2814, 2844, 2824, 2982 according to QA-C 10.3.0
 *                      : Added QA-C warning 3416, 2962 according to QA-C 10.3.0
 *                      : For support function pointer, Change invoke HW_IP function by function pointer 
 * 2.0.1: 01/10/2023    : Remove condition check ETH_DEM_REPORT_ERROR for R431 and change condition precompile for 
 *                        Eth_HwPostCommonDeInit by ETH_HW_COMMON_DEINIT
 *        18/10/2023    : Added QA-C Warning 0404, 2986 according to QA-C 10.3.0
 *                        Added QA-C 10.3.0 comments
 *        14/10/2023    : Improved SGMII auto negotiation linkup success rate for R-Switch in Eth_Init and Eth_DeInit
 *                      : Add ETH_DEM_EVENT_REPORTING_TYPE to precompile ETH_DEM_REPORT_ERROR
 *        13/10/2023    : Change FifoIdx to QueueIdx in Eth_Receive
 *                      : Include header file Eth_ETND_Ram.h and Eth_ETNE_Ram.h
 *                      : Remove header file Eth_ETNDE_Ram.h
 * 2.0.0: 27/07/2023    : Add CWE rule into QAC header
 *        18/07/2023    : Remove redundant QA-C warning 3214, 2814, 2844, 2824, 2982
 *        21/07/2023    : Add QA-C Warning 2986
 *        01/07/2023    : Improved SGMII auto negotiation linkup success rate for R-Switch for Eth_Init and Eth_DeInit
 *        30/06/2023    : Add Eth_GetSpiStatus API
 *        07/06/2023    : Add trace ID for check INV_MODE in Eth_SetControllerMode
 *        29/05/2023    : Add QA-C Warning 1503, 3432
 *        27/05/2023    : Remove of clear promiscuous mode flag in Eth_UpdatePhysAddrFilter
 *                      : Add precompile ETH_DEV_ERROR_DETECT for check ETH_E_COMMUNICATION
 *        25/05/2023    : Change Eth_GetEgressTimeStamp and Eth_GetIngressTimeStamp to Std_ReturnType for R21_11.
 *                      : Add check CrtMode in Eth_SetControllerMode.
 *        23/05/2023    : Change Eth_HwReadMii return E_OK/E_NOT_OK and add *RegValPtr to argument to get Phy value
 *        22/05/2023    : Add Trace ID for ETH_E_COMMUNICATION in Eth_WriteMii and Eth_ReadMii
 *        20/05/2023    : Add DET runtime error "ETH_E_COMMUNICATION" for Eth_WriteMii, Eth_ReadMii
 *        20/04/2023    : Change precompile for Eth_GetEgressTimeStamp, Eth_GetIngressTimeStamp support for R21-11
 * 1.5.3: 05/04/2022    : Add control index to parameter of Eth_HwCheckFifoIndex.
 *                        Add Eth_DeInit API
 *        13/04/2022    : Update QA-C comments.
 *        18/05/2022    : Limit the parameter IncVal checking of Eth_SetIncrementTimeForGptp to U2Ax devices only.
 * 1.5.2: 08/03/2022    : Add inclusion of SchM_Eth.h
 *        03/03/2022    : Add control index to parameter of Eth_HwGetTxErrorCounterValues.
 *        07/02/2022    : Update QA-C comment.
 *        24/01/2022    : Fixed the executable condition of Eth_SetIncrementTimeForGptp
 *                        from ETH_MODE_ACTIVE or ETH_MODE_DOWN to ETH_MODE_ACTIVE.
 * 1.5.1: 13/12/2021    : Update the check process of the tx buffer index of Eth_Transmit for each controller.
 *        18/10/2021    : Commonized Eth_ETNE_Ram.h and Eth_ETND_Ram.h.
 *                      : Change the memory section of the Eth_DemConfigCheck function to ETH_PRIVATE_CODE.
 *        27/10/2021    : Implementing the return value checking for Eth_HwCommonInit
 *                        (Report DEM_EVENT_STATUS_PREFAILED to DEM if the return value is E_NOT_OK)
 *        12/01/2021    : Update QA-C 9.5.0 comments
 * 1.4.2: 20/08/2021    : Update include file for support U2Bx devices.
 *        23/08/2021    : Fix an issue in which wrong event ID is reported to Diagnostic Event Manager in case of
 *                        failing access to the Ethernet Controller
 *        24/08/2021    : Modify the format to 120 characters
 *        26/08/2021    : Updated QA-C 9.5.0 comments
 * 1.4.1: 24/06/2021    : Update Eth_GetEgressTimeStamp and Eth_GetIngressTimeStamp for R19-11 support.
 *        07/05/2021    : Update WriteMii/ReadMii function for supporting U2Bx
 *                        Changes to support U2Bx devices.
 *                        Remove vendor ID from the file name, API names and parameters according to 
 *                        BSW00347 requirement
 *        09/06/2021    : Remove QA-C Warning 1339, 3214 and 3432 according to QA-C 9.5.0
 *        06/07/2021    : Updated QA-C 9.5.0 comments.
 * 1.2.0: 13/07/2020    : Release
 *        29/07/2020    : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020    : Release
 * 1.0.1: 04/06/2020    : To support Transmit/Receive interrupts for each controller.
 *                        Removed redundant error reports in Eth_59_EnableEgressTimeStamp.
 *                        Commented on a cast from a large type to a small type.
 *                        Change File version information from hard-code to macro.
 *                        Update by full check of the critical section.
 *                        Updated static analysis result.
 *                        Check range of parameter IncVal in API Eth_59_SetIncrementTimeForGptp.
 *                        Changed include file structure.
 *                        Fixed the error check of Eth_59_Receive.
 *                        Changed the parameter of Eth_59_SetOffsetTimeForGptp.
 *                        Fixed violation of AUTOSAR specifications for EthSwt.
 * 1.0.0: 25/03/2020    : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                       Include Section                                                              **
***********************************************************************************************************************/
/* Included for module version information and other types declarations                                               */
#include "Eth.h"
#include "Eth_Ram.h"
#if (ETH_MACRO_ETNC == STD_ON)
#include "Eth_ETNC_Ram.h"
#elif (ETH_MACRO_ETNB == STD_ON)
#include "Eth_ETNB_Ram.h"
#elif (ETH_MACRO_ETND == STD_ON)
#include "Eth_ETND_Ram.h"
#elif (ETH_MACRO_ETNE == STD_ON)
#include "Eth_ETNE_Ram.h"
#endif
#if (ETH_MACRO_ETNF == STD_ON)
#include "Eth_ETNF_Ram.h"
#endif

#include "EthIf_Cbk.h"
#include "EthTrcv_Cbk.h"

/* Included for the declaration of Det_ReportError() */
#include "Det.h"

/* Included for declaration of the function Dem_ReportErrorStatus() */
#include "Dem.h"

#include "SchM_Eth.h"

/* Included for declaration of the function GetCoreID() */
#if (ETH_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif /* #if (ETH_MULTI_CORE_SUPPORT == STD_ON) */
/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define ETH_C_AR_RELEASE_MAJOR_VERSION ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETH_C_AR_RELEASE_MINOR_VERSION ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETH_C_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ETH_C_SW_MAJOR_VERSION      ETH_SW_MAJOR_VERSION_VALUE
#define ETH_C_SW_MINOR_VERSION      ETH_SW_MINOR_VERSION_VALUE

#define ETH_DBTOC_VALUE                                           \
                         (((uint32)ETH_VENDOR_ID_VALUE << 22UL) | \
                         ((uint32)ETH_MODULE_ID_VALUE << 14UL) | \
                         ((uint32)ETH_SW_MAJOR_VERSION_VALUE << 8UL) | \
                         ((uint32)ETH_SW_MINOR_VERSION_VALUE << 3UL))

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/

#if (ETH_AR_RELEASE_MAJOR_VERSION != ETH_C_AR_RELEASE_MAJOR_VERSION)
  #error "Eth.c : Mismatch in Release Major Version"
#endif

#if (ETH_AR_RELEASE_MINOR_VERSION != ETH_C_AR_RELEASE_MINOR_VERSION)
  #error "Eth.c : Mismatch in Release Minor Version"
#endif

#if (ETH_AR_RELEASE_REVISION_VERSION != ETH_C_AR_RELEASE_REVISION_VERSION)
  #error "Eth.c : Mismatch in Release Revision Version"
#endif

#if (ETH_SW_MAJOR_VERSION != ETH_C_SW_MAJOR_VERSION)
  #error "Eth.c : Mismatch in Software Major Version"
#endif

#if (ETH_SW_MINOR_VERSION != ETH_C_SW_MINOR_VERSION)
  #error "Eth.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3214)    : The macro '%s' is not used and could be removed.                                             */
/* Rule                : MISRA C:2012 Rule-2.5                                                                        */
/* JV-01 Justification : This can be accepted, it will be used in some case of configuration.                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563      */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to call a function here    */
/*                       for such a small operation.                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3464)    : Argument to macro '%s' contains a side effect that will be evaluated more than once.         */
/* Rule                : CERTCCM PRE31                                                                                */
/* JV-01 Justification : This message is only emitted for expressions expanded from argument tokens written out at    */
/*                       the top level, that did not themselves originate from a macro expansion.                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2824)    : Possible: Arithmetic operation on NULL pointer.                                              */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-468, CWE-476, CWE-465, CWE-737                                   */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2844)    : Possible: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127        */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add     */
/*                       a wraparound guard here.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1339)    : Evaluating the address of the parameter '%s'.                                                */
/* Rule                : MISRA C:2012 Rule-17.8                                                                       */
/* JV-01 Justification : This is accepted, there is no issue at this LOC with current implementation                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is accepted, due to implementation for include memmap is following AUTOSAR rule.        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2986)    : This operation is redundant. The value of the result is always that of the right-hand        */
/*                       operand.                                                                                     */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-398, CWE-561, CWE-569, CWE-633     */
/* JV-01 Justification : The operation is correct                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with possible side effects.                        */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : This is necessary for suppressing optimization by dummy loop.                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2962)    : Apparent: Using value of uninitialized automatic object '%s'.                                */
/* Rule                : CERTCCM EXP33, MISRA C:2012 Rule-9.1                                                         */
/* JV-01 Justification : It will be initialized based on scope of 'if' statements  where at least an 'if' statement   */
/*                       will be executed that will initialize the variable.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : MISRA C:2012 Rule-13.5, CERTCCM EXP02, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it does not have direct access to the HW register, and     */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2812)    : Apparent: Dereference of NULL pointer.                                                       */
/* Rule                : EXP34,CWE-476,CWE-465,CWE-737,5.8,Rule-1.3,Dir-4.1                                           */
/* JV-01 Justification : Although it is a volatile object, pointer checked before assign value,                       */
/*                       So it is not null pointer                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : CERTCCM MSC01, MISRA C:2012 Rule-15.7                                                        */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2995)    : The result of this logical operation is always 'true'.                                       */
/* Rule                : MISRA C:2012 Rule-2.2                                                                        */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2991)    : The value of this 'if' controlling expression is always 'true'.                              */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Dir-4.1, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/* Message (2:3673)    : The object addressed by the pointer parameter '%s' is not modified and so the pointer        */
/*                       could be of type 'pointer to const'.                                                         */
/* Rule                : CERTCCM DCL00, DCL13, MISRA C:2012 Rule-8.13                                                 */
/* JV-01 Justification : Pointer variable is used to modify the value at the address so the pointer cannot be         */
/*                       declared as 'pointer to const' type.                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-476, CWE-465, CWE-737, CWE-690                                   */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3206)    : The parameter 'ucApiId' is not used in this function.                                        */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.7                                                  */
/* JV-01 Justification : This argument is not used since only one controller is used. However, it is prepared         */
/*                       because it is used by another IP. There is no problem because it is as designed.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/* Static internal functions */
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"

STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_SetStatus(
  uint8 CoreId, CONST(Eth_StateType, AUTOMATIC) LenStatus);

#if (ETH_DEV_ERROR_DETECT == STD_ON)
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_CommonDetCheck(
  CONST(uint8, AUTOMATIC) LucSID, CONST(uint8, AUTOMATIC) LucCtrlIdx);
#endif

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_PUBLIC_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Init
**
** Service ID            : 0x01
**
** Description           : This API performs the initialization of the Ethernet Driver by initializing the configuration
**                         structure for subsequent API calls.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CfgPtr: Pointer to ETH Driver configuration set
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Eth_GaaCtrlStat, Eth_GpDemEventAccess, Eth_GpGetCoreId2Index, Eth_GpTotalCtrlConfig
**                         Eth_CtrlConfigIdx, Eth_GpDemEventRxFramesLost, Eth_GpDemEventCRC, Eth_GpDemEventAlignment 
**                         Eth_GpDemEventUnderSizeFrame, Eth_GpDemEventOverSizeFrame, Eth_GpDemEventSinglecollision,
**                         Eth_GpDemEventMultiplecollision, Eth_GpDemEventLatecollision, Eth_GpDemEventIntInconsistent,
**                         Eth_GpDemEventDmaError, Eth_GpDemEventEccError, Eth_GpDemEventTimerincFailed, 
**                         Eth_GpDemEventRegisterCorruption
**
** Function(s) invoked   : Det_ReportError, Eth_DemConfigCheck, Eth_SetStatus, Eth_HwInit, GetCoreID,
**                         Eth_InitializeBuffer, Eth_ClearAllAddressFilters, Eth_HwPreCommonInit, Eth_HwPostCommonInit
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_001
** Reference ID          : ETH_DUD_ACT_001_ERR001, ETH_DUD_ACT_001_ERR002, ETH_DUD_ACT_001_ERR003
** Reference ID          : ETH_DUD_ACT_001_ERR004, ETH_DUD_ACT_001_ERR005, ETH_DUD_ACT_001_ERR006
** Reference ID          : ETH_DUD_ACT_001_GBL001, ETH_DUD_ACT_001_GBL002
** Reference ID          : ETH_DUD_ACT_001_GBL003, ETH_DUD_ACT_001_GBL004
** Reference ID          : ETH_DUD_ACT_001_GBL103, ETH_DUD_ACT_001_GBL104, ETH_DUD_ACT_001_GBL105
** Reference ID          : ETH_DUD_ACT_001_GBL106, ETH_DUD_ACT_001_GBL107, ETH_DUD_ACT_001_GBL108
** Reference ID          : ETH_DUD_ACT_001_GBL109, ETH_DUD_ACT_001_GBL110, ETH_DUD_ACT_001_GBL111
** Reference ID          : ETH_DUD_ACT_001_GBL112, ETH_DUD_ACT_001_GBL113, ETH_DUD_ACT_001_GBL114
** Reference ID          : ETH_DUD_ACT_001_GBL115, ETH_DUD_ACT_001_GBL116, ETH_DUD_ACT_001_GBL117
** Reference ID          : ETH_DUD_ACT_001_GBL118, ETH_DUD_ACT_001_GBL119, ETH_DUD_ACT_001_GBL120
***********************************************************************************************************************/
FUNC(void, ETH_PUBLIC_CODE) Eth_Init(                                                                                   /* PRQA S 1503 # JV-01 */
  P2CONST(Eth_ConfigType, AUTOMATIC, ETH_APPL_CONST) CfgPtr)
{
  uint32 LulIdx;
  Std_ReturnType LucResult;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  uint8 LucCoreIndex;
  uint32 LulCtrIdx;
  uint32 LulTotalCtrlConfig;
  uint32 coreIdx;
  uint32 ctrIdx;

  #if (ETH_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  #else
  /* if Multicore is not configude, defauld coreid is 0x00
    To optimize implementation */
  LucCoreIndex = ETH_ZERO;
  #endif /* End of #if (ETH_MULTI_CORE_SUPPORT == STD_ON)*/
  LucResult = E_OK;                                                                                                     /* PRQA S 2982 # JV-01 */
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == CfgPtr)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_INIT_SID, ETH_E_PARAM_POINTER);
  }
  /* Check whether the existing database is correct */
  else if (ETH_DBTOC_VALUE != CfgPtr->ulStartOfDbToc)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_INIT_SID, ETH_E_INVALID_DATABASE);
  }
  else
  #endif /* (ETH_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ETH_MULTI_CORE_SUPPORT == STD_ON)
    Eth_GpCoreId2Index = CfgPtr->pCoreId2Index;
    /* Covert Core Id to Core Index */
    LucCoreIndex = Eth_GpCoreId2Index[LucCoreId];                                                                       
    #endif

    #if (ETH_DEV_ERROR_DETECT == STD_ON)
    #if (ETH_MULTI_CORE_SUPPORT == STD_ON)
    /* Check invalid core */
    if(ETH_INVALID_CORE == LucCoreIndex)
    {
      /* Report to DET */
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_INIT_SID, ETH_E_INVALID_CORE);
    }
    else
    #endif /* End of #if (ETH_MULTI_CORE_SUPPORT == STD_ON)*/
    #endif /* (ETH_DEV_ERROR_DETECT == STD_ON) */
    {
      /* Assign the config pointer value to global pointer */
      Eth_GpCtrlConfigPtr = CfgPtr->pCtrlConfig;                                                                        
      Eth_GpEthConfigPtr = Eth_GpCtrlConfigPtr->pEthConfig;
      #if (ETH_MACRO_ETNE == STD_ON)
      Eth_GpGwcaRegPtr = &CfgPtr->stGwcaRegValue;
      Eth_GpGlobalPauseCfgPtr = &CfgPtr->stGlobalPauseConfiguration[0];
      Eth_GpBothCoreCfgPtr = &CfgPtr->stBothCoreConfiguration;
      #endif /* ETH_MACRO_ETNE == STD_ON */
      Eth_GpDemEventAccess = CfgPtr->pDemEventAccess;
      Eth_GpDemEventRxFramesLost = CfgPtr->pDemEventRxFramesLost;
      Eth_GpDemEventCRC = CfgPtr->pDemEventCRC;
      Eth_GpDemEventUnderSizeFrame = CfgPtr->pDemEventUnderSizeFrame;
      Eth_GpDemEventOverSizeFrame = CfgPtr->pDemEventOverSizeFrame;
      Eth_GpDemEventAlignment = CfgPtr->pDemEventAlignment;
      Eth_GpDemEventSinglecollision = CfgPtr->pDemEventSinglecollision;
      Eth_GpDemEventMultiplecollision = CfgPtr->pDemEventMultiplecollision;
      Eth_GpDemEventLatecollision = CfgPtr->pDemEventLatecollision;
      #if (ETH_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
      Eth_GpDemEventIntInconsistent = CfgPtr->pDemEventIntInconsistent;
      #endif
      Eth_GpDemEventDmaError = CfgPtr->pDemEventDmaError;
      Eth_GpDemEventEccError = CfgPtr->pDemEventEccError;     
      #if (ETH_MACRO_ETNB == STD_ON || ETH_MACRO_ETNF ==STD_ON)
      #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
      Eth_GpDemEventTimerincFailed = CfgPtr->pDemEventTimerincFailed;
      Eth_GpDemEventTimeroffsetFailed = CfgPtr->pDemEventTimeroffsetFailed;
      #endif      
      #if ((ETH_REGISTER_CHECK_INITTIME == STD_ON) || (ETH_REGISTER_CHECK_RUNTIME == STD_ON))
      Eth_GpDemEventRegisterCorruption = CfgPtr->pDemEventRegisterCorruption;
      #endif
      #endif
      #if (ETH_MACRO_ETNE == STD_ON)
      #if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)
      Eth_GpDemEventUnintendedIntChk = CfgPtr->pDemEventUnintendedIntChk;
      #endif
      #endif
      Eth_GpTotalCtrlConfig = CfgPtr->pTotalCtrlConfig;
      for (coreIdx = 0UL; (coreIdx < (uint32)ETH_TOTAL_CORE_CONFIG); coreIdx++)                                  /* PRQA S 2877 # JV-01 */
      {
        for (ctrIdx = 0UL; (ctrIdx < (uint32)ETH_MAX_CTRL_CONFIG_PER_CODE); ctrIdx++)                            /* PRQA S 2877 # JV-01 */
        {
          Eth_CtrlConfigIdx[coreIdx][ctrIdx] = CfgPtr->ulCtrlConfigIdx[coreIdx][ctrIdx];
        }
      }
      Eth_GpDriverState = CfgPtr->pDriverState;
      /* Get total controller configured */
      LulTotalCtrlConfig = Eth_GpTotalCtrlConfig[LucCoreIndex];                                                         
      #if ((ETH_MACRO_ETND == STD_ON) || (ETH_MACRO_ETNE == STD_ON))
      LucResult = Eth_HwPreCommonInit();
      #endif
      for (LulIdx = 0UL; LulIdx < (uint32)LulTotalCtrlConfig; LulIdx++)
      {
        LulCtrIdx = Eth_CtrlConfigIdx[LucCoreIndex][LulIdx];                                                            
        /* Copy the configured MAC address as inital value */
        ETH_PACK_ADDRESS_FROM_8(Eth_GpCtrlConfigPtr[LulCtrIdx].aaEthMACAddr,                                            /* PRQA S 3469, 3464, 0404 # JV-01, JV-01, JV-01 */
          Eth_GaaCtrlStat[LulCtrIdx].stMacAddr);
        /* Initialize controller state as DOWN */
        Eth_GaaCtrlStat[LulCtrIdx].enMode = ETH_MODE_DOWN;                                                              
        /* Initialize address filter */
        #if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
        Eth_ClearAllAddressFilters(LulCtrIdx);
        #endif
        /* Get unit type */
        LucHWIPType = Eth_GaaHWIP[LulCtrIdx].ucIndex;                                                                   
        if (NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pInitializeBuffer)                                                  /* PRQA S 3416 # JV-01 */
        {
            /* Invoke Eth_InitializeBuffer to initialize Tx/Rx buffer pool */
          Eth_GaaHwFunc[LucHWIPType]->pInitializeBuffer(LulCtrIdx);
        }/* else No action required */
          /* Initialize low-level driver */
          if (NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwInit)                                                          /* PRQA S 3416 # JV-01 */
          {
          /* Initialize low-level driver */
          LucResult = Eth_GaaHwFunc[LucHWIPType]->pHwInit(LulCtrIdx);
          }/* else No action required */
          if (E_OK == LucResult)
          {
            /* Report PASS to DEM */
            Eth_DemConfigCheck(Eth_GpDemEventAccess[LulCtrIdx], DEM_EVENT_STATUS_PREPASSED);                            
          }
          else
          {
            Eth_DemConfigCheck(Eth_GpDemEventAccess[LulCtrIdx], DEM_EVENT_STATUS_PREFAILED);
          }
      }
      #if ((ETH_MACRO_ETND == STD_ON) || (ETH_MACRO_ETNE == STD_ON))
      if (E_OK == LucResult)
      {
        LucResult = Eth_HwPostCommonInit();
      }
      #endif
      if (E_OK == LucResult)
      {
        #if ((ETH_MACRO_ETND == STD_ON) || (ETH_MACRO_ETNE == STD_ON))
        for (LulIdx = 0UL; LulIdx < (uint32)LulTotalCtrlConfig; LulIdx++)
        {
          LulCtrIdx = Eth_CtrlConfigIdx[LucCoreIndex][LulIdx];                                                          
          Eth_DemConfigCheck(Eth_GpDemEventAccess[LulCtrIdx], DEM_EVENT_STATUS_PREPASSED);                              
        }
        #endif
        /* Initialize the Driver State to INIT */
        Eth_SetStatus(LucCoreIndex, ETH_STATE_INIT);
      }
      else
      {
        #if ((ETH_MACRO_ETND == STD_ON) || (ETH_MACRO_ETNE == STD_ON))
        for (LulIdx = 0UL; LulIdx < (uint32)LulTotalCtrlConfig; LulIdx++)
        {
          LulCtrIdx = Eth_CtrlConfigIdx[LucCoreIndex][LulIdx];                                                          
          Eth_DemConfigCheck(Eth_GpDemEventAccess[LulCtrIdx], DEM_EVENT_STATUS_PREFAILED);                              
        }
        #endif
      }
    }
  }
} /* End of API Eth_Init */

#if (ETH_DEINIT_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_DeInit
**
** Service ID            : 0xA3
**
** Description           : This API performs the SW Reset process needed for the initialization of the Ethernet Driver
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : ForceReset: Indicate the reset flow to follow (normal/emergency)
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: Success to SW Reset
**                         E_NOT_OK: Fail to SW Reset
**
** Preconditions         : The function requires previous controller initialization Eth_Init().
**
** Global Variables Used : Eth_GpDriverState, Eth_GpCoreId2Index, Eth_GpTotalCtrlConfig, Eth_CtrlConfigIdx
**
** Function(s) invoked   : Det_ReportError, Eth_SetStatus, Eth_HwDeInit, Eth_HwPreCommonDeInit, Eth_HwPostCommonDeInit,
**                         GetCoreID
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_052
** Reference ID          : ETH_DUD_ACT_052_ERR001, ETH_DUD_ACT_052_ERR002
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_DeInit(CONST(boolean, AUTOMATIC) ForceReset)                                  /* PRQA S 1503, 3206 # JV-01, JV-01 */
{
  Std_ReturnType LucResult;
  #if (ETH_MACRO_ETND == STD_ON)
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  #endif
  uint8 LucCoreIndex;
  #if (ETH_MACRO_ETND == STD_ON)
  uint32 LulIdx;
  uint32 LulCtrIdx;
  uint32 LulTotalCtrlConfig;
  #endif
  #if (ETH_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Eth_GpCoreId2Index[LucCoreId];                                                                         
  #else
  /* if Multicore is not configude, defauld coreid is 0x00
     To optimize implementation */
  LucCoreIndex = ETH_ZERO;
  #endif /* End of #if (ETH_MULTI_CORE_SUPPORT == STD_ON)*/
  LucResult = E_OK;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  #if (ETH_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core */
  if(ETH_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_DEINIT_SID, ETH_E_INVALID_CORE);
    LucResult = E_NOT_OK;
  }
  else
  #endif /* End of #if (ETH_MULTI_CORE_SUPPORT == STD_ON)*/
  {
    if (ETH_STATE_INIT != Eth_GpDriverState[LucCoreIndex])                                                              
    {
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_DEINIT_SID, ETH_E_UNINIT);
      LucResult = E_NOT_OK;
    }
  }
  if (E_OK == LucResult)
  #endif /* (ETH_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (ETH_MACRO_ETNE == STD_ON)
    LucResult = Eth_HwPreCommonDeInit();                                                                                /* PRQA S 2982 # JV-01 */
    #endif

    #if (ETH_MACRO_ETND == STD_ON)
    /* Get total controller configured */
      LulTotalCtrlConfig = Eth_GpTotalCtrlConfig[LucCoreIndex];                                                         
    for (LulIdx = 0UL; (LulIdx < (uint32)LulTotalCtrlConfig) && (E_OK == LucResult); LulIdx++)
    {
      LulCtrIdx = Eth_CtrlConfigIdx[LucCoreIndex][LulIdx];                                                              
      /* Get unit type */
      LucHWIPType = Eth_GaaHWIP[LulCtrIdx].ucIndex;                                                                     
      if (NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwDeInit)                                                            
      {
        /* Invoke Eth_HwDeInit to initialize low-level driver */
        LucResult = Eth_GaaHwFunc[LucHWIPType]->pHwDeInit(LulCtrIdx, ForceReset);
      }/* else No action required */
    }

    if (E_OK == LucResult)
    #endif
    {
      #if (ETH_MACRO_ETNE == STD_ON)
      LucResult = Eth_HwPostCommonDeInit();
      #endif
      Eth_SetStatus(LucCoreIndex, ETH_STATE_UNINIT);
    } /* else: No action required */

  } /* else: No action required */

  return LucResult;
} /* End of API Eth_DeInit */
#endif /* (ETH_DEINIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Eth_SetControllerMode
**
** Service ID            : 0x03
**
** Description           : This API performs enabling / disabling  of the indexed controller.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx:  Index of an ether controller
**                         CtrlMode: Enable/Disable controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: success.
**                         E_NOT_OK: controller mode could not be changed.
**
** Preconditions         : Component Requires previous controller initialization using Eth_Init.
**
** Global Variables Used : Eth_GaaCtrlStat, Eth_GpDemEventAccess, Eth_GpDemEventRxFramesLost,
**                         Eth_GDemEventCRC, Eth_GpDemEventUnderSizeFrame,
**                         Eth_GpDemEventOverSizeFrame, Eth_GpDemEventAlignment,
**                         Eth_GpDemEventSinglecollision, Eth_GpDemEventMultiplecollision,
**                         Eth_GpDemEventLatecollision
**
** Function(s) invoked   : Eth_DemConfigCheck, Eth_CommonDetCheck, Eth_HwEnableController,
**                         Eth_HwDisableController, Eth_InitializeBuffer,
**                         Eth_PreprocessBuffer, EthIf_CtrlModeIndication
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_002,
** Reference ID          : ETH_DUD_ACT_002_ERR001, ETH_DUD_ACT_002_ERR002
** Reference ID          : ETH_DUD_ACT_002_ERR003, ETH_DUD_ACT_002_ERR004
** Reference ID          : ETH_DUD_ACT_002_ERR005, ETH_DUD_ACT_002_ERR006
** Reference ID          : ETH_DUD_ACT_002_ERR007, ETH_DUD_ACT_002_ERR008
** Reference ID          : ETH_DUD_ACT_002_ERR009, ETH_DUD_ACT_002_ERR010
** Reference ID          : ETH_DUD_ACT_002_ERR011, ETH_DUD_ACT_002_ERR012
** Reference ID          : ETH_DUD_ACT_002_GBL001, ETH_DUD_ACT_002_GBL002
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_SetControllerMode(                                                            /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, Eth_ModeType CtrlMode)
{
  Std_ReturnType LucReturnValue;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_SETCONTROLLERMODE_SID, CtrlIdx);
  #if (ETH_AR_VERSION >= ETH_AR_R21_11_VERSION)
  if ((ETH_HWIP_ETNF == LucHWIPType) || (ETH_HWIP_ETNB == LucHWIPType))                                                 /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    if ((ETH_MODE_STANDBY != CtrlMode) && (ETH_MODE_ACTIVE != CtrlMode) && (ETH_MODE_DOWN != CtrlMode))
    {
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SETCONTROLLERMODE_SID, ETH_E_INV_MODE);
      LucReturnValue = E_NOT_OK;
    }/* else No action required */
  }
  else
  {
    if ((ETH_MODE_ACTIVE != CtrlMode) && (ETH_MODE_DOWN != CtrlMode))
    {
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SETCONTROLLERMODE_SID, ETH_E_INV_MODE);
      LucReturnValue = E_NOT_OK;
    }/* else No action required */
  }
  #endif
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    LucReturnValue = E_OK;
    if (Eth_GaaCtrlStat[CtrlIdx].enMode != CtrlMode)                                                                    
    {
      if (ETH_MODE_ACTIVE == CtrlMode)
      {
        /* Invoke Eth_HwEnableController to activate HW */
        if (NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwEnableController)                                                /* PRQA S 3416 # JV-01 */
        {
          LucReturnValue = Eth_GaaHwFunc[LucHWIPType]->pHwEnableController((uint32)CtrlIdx);
        }/* else No action required */
        if (E_OK == LucReturnValue)
        {
          if (NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pPreprocessBuffer)                                                /* PRQA S 3416 # JV-01 */
          {
            /* Invoke Eth_PreprocessBuffer to set source MAC address to all Tx Buffers in advance */
            Eth_GaaHwFunc[LucHWIPType]->pPreprocessBuffer((uint32)CtrlIdx);
            /* To prevent MainFunction be executed during the transition,
            set the controller state as ACTIVE after the transition. */
            Eth_GaaCtrlStat[CtrlIdx].enMode = ETH_MODE_ACTIVE;                                                          
          }/* else No action required */
        }
        else
        {
          Eth_DemConfigCheck(Eth_GpDemEventAccess[CtrlIdx], DEM_EVENT_STATUS_PREFAILED);                                
        }
      }
      else
      {
        /* To prevent MainFunction be executed during the transition,
        set the controller state as DOWN before the transition. */
        Eth_GaaCtrlStat[CtrlIdx].enMode = CtrlMode;                                                                     
        if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwDisableController))                                       /* PRQA S 3416 # JV-01 */
        {
          /* Invoke Eth_HwDisableController to stop HW */
          LucReturnValue= Eth_GaaHwFunc[LucHWIPType]->pHwDisableController((uint32)CtrlIdx);
        }
        /* Retreive all provided Tx Buffers */
        if (E_OK == LucReturnValue)
        {
          if (NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pInitializeBuffer)                                                /* PRQA S 3416 # JV-01 */
          {
            /* Invoke Eth_InitializeBuffer to initialize Tx/Rx buffer pool */
            Eth_GaaHwFunc[LucHWIPType]->pInitializeBuffer((uint32)CtrlIdx);
          }
        }
        else
        {
          Eth_DemConfigCheck(Eth_GpDemEventAccess[CtrlIdx], DEM_EVENT_STATUS_PREFAILED);                                
        }
      }
      if (E_OK == LucReturnValue)
      {
        /* Since this function is implemented as synchronous, indicate a mode switch to EthIf here */
        EthIf_CtrlModeIndication(CtrlIdx, CtrlMode);
        Eth_DemConfigCheck(Eth_GpDemEventAccess[CtrlIdx], DEM_EVENT_STATUS_PREPASSED);                                  
        Eth_DemConfigCheck(Eth_GpDemEventRxFramesLost[CtrlIdx], DEM_EVENT_STATUS_PREPASSED);                            
        Eth_DemConfigCheck(Eth_GpDemEventCRC[CtrlIdx], DEM_EVENT_STATUS_PREPASSED);                                     
        Eth_DemConfigCheck(Eth_GpDemEventUnderSizeFrame[CtrlIdx], DEM_EVENT_STATUS_PREPASSED);                          
        Eth_DemConfigCheck(Eth_GpDemEventOverSizeFrame[CtrlIdx], DEM_EVENT_STATUS_PREPASSED);                           
        Eth_DemConfigCheck(Eth_GpDemEventAlignment[CtrlIdx], DEM_EVENT_STATUS_PREPASSED);                               
        Eth_DemConfigCheck(Eth_GpDemEventSinglecollision[CtrlIdx], DEM_EVENT_STATUS_PREPASSED);                         
        Eth_DemConfigCheck(Eth_GpDemEventMultiplecollision[CtrlIdx], DEM_EVENT_STATUS_PREPASSED);                       
        Eth_DemConfigCheck(Eth_GpDemEventLatecollision[CtrlIdx], DEM_EVENT_STATUS_PREPASSED);                           
      }
      else
      {
        /* No action required */
      }
    }
    else
    {
       /* No action required */
    }
  }

  return(LucReturnValue);
} /* End of API Eth_SetControllerMode */

/***********************************************************************************************************************
** Function Name         : Eth_GetControllerMode
**
** Service ID            : 0x04
**
** Description           : This API Obtains the state of the indexed controller
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : CtrlModePtr: Pointer of the controller mode
**
** Return parameter      : Std_ReturnType
**                         E_OK: success.
**                         E_NOT_OK: controller mode could not be obtained.
**
** Preconditions         : The function requires previous controller initialization Eth_Init().
**
** Global Variables Used : Eth_GaaCtrlStat
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck,
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_003,
** Reference ID          : ETH_DUD_ACT_003_ERR001, ETH_DUD_ACT_003_GBL001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetControllerMode(                                                            /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, P2VAR(Eth_ModeType, AUTOMATIC, ETH_APPL_DATA) CtrlModePtr)                                             /* PRQA S 3432 # JV-01 */
{
  Std_ReturnType LucReturnValue;

  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_GETCONTROLLERMODE_SID, CtrlIdx);
  /* Report Error to DET, if the CtrlModePtr pointer value is NULL */
  if (NULL_PTR == CtrlModePtr)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GETCONTROLLERMODE_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif /* (ETH_DEV_ERROR_DETECT == STD_ON) */
  {
    *CtrlModePtr = Eth_GaaCtrlStat[CtrlIdx].enMode;                                                                     
    LucReturnValue = E_OK;
  }

  return(LucReturnValue);
} /* End of API Eth_GetControllerMode */

/***********************************************************************************************************************
** Function Name         : Eth_GetPhysAddr
**
** Service ID            : 0x08
**
** Description           : This API obtains the physical source address(MAC Address) configured for the 
**                         indexed controller.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : PhysAddrPtr: Pointer to memory containing the physical source address (MAC address) in 
**                         network byte order.
**
** Return parameter      : None
**
** Preconditions         : Component Requires previous controller initialization using Eth_Init.
**
** Global Variables Used : Eth_GaaCtrlStat
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_004,
** Reference ID          : ETH_DUD_ACT_004_ERR001
***********************************************************************************************************************/
FUNC(void, ETH_PUBLIC_CODE) Eth_GetPhysAddr(                                                                            /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr)                                                    /* PRQA S 3432 # JV-01 */
{
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucReturnValue;
  LucReturnValue = Eth_CommonDetCheck(ETH_GETPHYSADDR_SID, CtrlIdx);
  /* Report Error to DET, if the PhysAddrPtr pointer value is NULL */
  if (NULL_PTR == PhysAddrPtr)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GETPHYSADDR_SID, ETH_E_PARAM_POINTER);
     LucReturnValue  = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif /* (ETH_DEV_ERROR_DETECT == STD_ON) */
  {
    ETH_UNPACK_ADDRESS_TO_8(Eth_GaaCtrlStat[CtrlIdx].stMacAddr, PhysAddrPtr);                                           /* PRQA S 3469 # JV-01 */
  }
} /* End of API Eth_GetPhysAddr */

/***********************************************************************************************************************
** Function Name         : Eth_SetPhysAddr
**
** Service ID            : 0x13
**
** Description           : Sets the physical source address used by the indexed controller.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant for the same CtrlIdx,
**                         reentrant for different
**
** Input Parameters      : CtrlIdx:     Index of the controller
**                         PhysAddrPtr: Pointer to memory containing the physical source address (MAC address)
**                                      in network byte order.
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Component Requires previous controller initialization using Eth_Init.
**
** Global Variables Used : Eth_GaaCtrlStat
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_005,
** Reference ID          : ETH_DUD_ACT_005_ERR001, ETH_DUD_ACT_005_ERR002
** Reference ID          : ETH_DUD_ACT_005_GBL001
***********************************************************************************************************************/
FUNC(void, ETH_PUBLIC_CODE) Eth_SetPhysAddr(                                                                            /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr)
{
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucReturnValue;
  LucReturnValue = Eth_CommonDetCheck(ETH_SETPHYSADDR_SID, CtrlIdx);
  /* Report Error to DET, if the PhysAddrPtr pointer value is NULL */
  if (NULL_PTR == PhysAddrPtr)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SETPHYSADDR_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    if (ETH_MODE_ACTIVE == Eth_GaaCtrlStat[CtrlIdx].enMode)                                                             
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SETPHYSADDR_SID, ETH_E_INV_MODE);
      #endif
    }
    else
    {
      ETH_PACK_ADDRESS_FROM_8(PhysAddrPtr, Eth_GaaCtrlStat[CtrlIdx].stMacAddr);                                         /* PRQA S 3469 # JV-01 */
    }
  }
} /* End of API Eth_SetPhysAddr */

#if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_UpdatePhysAddrFilter
**
** Service ID            : 0x12
**
** Description           : Update the physical source address to/from the indexed controller filter.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant for the same CtrlIdx,
**                         reentrant for different
**
** Input Parameters      : CtrlIdx:    Index of the controller
**                         PhyAddrPtr: Pointer to memory containing the physical destination address (MAC address)
**                                     in network byte order.
**                         Action:     Add or remove the address from the Ethernet controllers
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: filter was successfully changed
**                         E_NOT_OK: filter could not be changed and the DET is ON
**
** Preconditions         : Component Requires previous controller initialization using Eth_Init.
**
** Global Variables Used : Eth_GaaCtrlStat, Eth_GstBroadcastAddr, Eth_GstNullAddr
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_AddAddressFilter, Eth_RemoveAddressFilter,
**                         Eth_GetFilterIndex, Eth_ClearAllAddressFilters
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_006,
** Reference ID          : ETH_DUD_ACT_006_ERR001, ETH_DUD_ACT_006_ERR002
** Reference ID          : ETH_DUD_ACT_006_ERR003, ETH_DUD_ACT_006_ERR004
** Reference ID          : ETH_DUD_ACT_006_GBL001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_UpdatePhysAddrFilter(                                                         /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr, Eth_FilterActionType Action)
{
  Eth_MacAddressType LstMacAddr;
  Std_ReturnType LucReturnValue;
  uint32 LulFilterIdx;

  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_UPDATEPHYSADDRFILTER_SID, CtrlIdx);
  /* Report Error to DET, if the PhysAddrPtr pointer value is NULL */
  if (NULL_PTR == PhysAddrPtr)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID,
      ETH_UPDATEPHYSADDRFILTER_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }

  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    /* Pack MAC address from user to the structure to be compared */
    ETH_PACK_ADDRESS_FROM_8(PhysAddrPtr, LstMacAddr);                                                                   /* PRQA S 3469 # JV-01 */

    /* FF:..:FF and 00:..:00 are not allowed while the controller is ACTVIE */
    if ((ETH_MODE_ACTIVE == Eth_GaaCtrlStat[CtrlIdx].enMode) &&                                                         
      ((0UL == ETH_COMPARE_MAC(LstMacAddr, Eth_GstBroadcastAddr)) ||                                                    /* PRQA S 3469 # JV-01 */
      (0UL == ETH_COMPARE_MAC(LstMacAddr, Eth_GstNullAddr))))                                                           /* PRQA S 3469 # JV-01 */
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_UPDATEPHYSADDRFILTER_SID, ETH_E_INV_MODE);
      #endif
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      LucReturnValue = E_OK;

      if (0UL == ETH_COMPARE_MAC(LstMacAddr, Eth_GstBroadcastAddr))                                                     /* PRQA S 3469 # JV-01 */
      {
        /* If FF:..:FF is specified, enter promiscuous mode */
        Eth_GaaCtrlStat[CtrlIdx].blPromiscuous = ETH_TRUE;                                                              
      }
      else if (0UL == ETH_COMPARE_MAC(LstMacAddr, Eth_GstNullAddr))                                                     /* PRQA S 3469 # JV-01 */
      {
        /* If 00:..:00 is specified, clear promisoucs mode and all filters */
        Eth_ClearAllAddressFilters((uint32)CtrlIdx);
      }
      else
      {
        if (ETH_ADD_TO_FILTER == Action)
        {
          #if (ETH_DEV_ERROR_DETECT == STD_ON)
          /*
             Report DET error when:
             - The specified address is not a multicast address
             - The specified address has been already registered
             - The filter array is full
          */
          LulFilterIdx = Eth_GetFilterIndex((uint32)CtrlIdx, &LstMacAddr);
          if ((0UL == ETH_CHECK_MULTICAST(LstMacAddr)) ||                                                               /* PRQA S 3469 # JV-01 */
            (ETH_INVALID_FILTER_INDEX != LulFilterIdx) ||
            (ETH_FILTER_FULL_VALUE == Eth_GaaCtrlStat[CtrlIdx].ulActiveFilterBits))                                     
          {
            (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID,
              ETH_UPDATEPHYSADDRFILTER_SID, ETH_E_INV_PARAM);
            LucReturnValue = E_NOT_OK;
          }
          else
          #endif
          {
            Eth_AddAddressFilter((uint32)CtrlIdx, &LstMacAddr);
          }
        }
        else
        {
          LulFilterIdx = Eth_GetFilterIndex((uint32)CtrlIdx, &LstMacAddr);
          #if (ETH_DEV_ERROR_DETECT == STD_ON)
          /* If the specified address is not registered, report error */
          if (ETH_INVALID_FILTER_INDEX == LulFilterIdx)
          {
            (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_UPDATEPHYSADDRFILTER_SID, ETH_E_INV_PARAM);
            LucReturnValue = E_NOT_OK;
          }
          else
          #endif
          {
            Eth_RemoveAddressFilter((uint32)CtrlIdx, LulFilterIdx);
          }
        }
      }
    }
  }

  return LucReturnValue;
}
#endif /* (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON) */

#if (ETH_CTRL_ENABLE_MII == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_WriteMii
**
** Service ID            : 0x05
**
** Description           : This API Configures a transceiver register or triggers a function offered by the receiver by
**                         writing the specified transceiver register through the MII of the indexed controller
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**                         TrcvIdx: Index of the transceiver on the MII
**                         RegIdx:  Index of the transceiver register on the MII
**                         RegVal:  Value to be written into the indexed register
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: No error has occurred during execution of the API
**                         E_NOT_OK: An error has occurred during execution of the API
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration 
**                         parameter EthCtrlEnableMii.
**
** Global Variables Used : None
**
** Function(s) invoked   : Det_ReportError, Det_ReportRuntimeError, Eth_CommonDetCheck, Eth_HwWriteMiiBit
**                         Eth_HwWriteMii, EthTrcv_WriteMiiIndication, Eth_HwReadMiiBit
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_007,
** Reference ID          : ETH_DUD_ACT_007_ERR001, ETH_DUD_ACT_007_ERR002, ETH_DUD_ACT_007_ERR003
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE)Eth_WriteMii(                                                                      /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal)
{
  #if ((ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNC == STD_ON) || (ETH_MACRO_ETNF == STD_ON))
  /* Local variable only used in E2x and U2Ax devices */
  uint32 LulBitCount;
  uint32 LulHeader;
  uint32 LulBit;
  uint16 LulRegVal;
  #endif

  Std_ReturnType LucReturnValue;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;

  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;

  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_WRITEMII_SID, CtrlIdx);
  /* Check for the valid TrcvIdx  */
  if (ETH_PHY_MAX_PHYAD_IDX < TrcvIdx)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_WRITEMII_SID, ETH_E_INV_PARAM);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  /* Check for the valid RegIdx  */
  if (ETH_PHY_MAX_REGAD_IDX < RegIdx)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_WRITEMII_SID, ETH_E_INV_PARAM);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }

  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif /* (ETH_DEV_ERROR_DETECT == STD_ON) */

  if ((ETH_HWIP_ETND == LucHWIPType) || (ETH_HWIP_ETNE == LucHWIPType))                                                 /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    #if ((ETH_MACRO_ETND == STD_ON) || (ETH_MACRO_ETNE == STD_ON))
    if (NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwWriteMii)                                                            /* PRQA S 3416 # JV-01 */
    {
      LucReturnValue = Eth_GaaHwFunc[LucHWIPType]->pHwWriteMii((uint32)CtrlIdx, TrcvIdx, RegIdx, RegVal);
    }/* else No action required */
    if (E_OK == LucReturnValue)                                                                                         
    {
      /* Since this function is implemented as synchronous, call EthTrcv here */
      EthTrcv_WriteMiiIndication(CtrlIdx, TrcvIdx, RegIdx);
    }
    else
    {
      (void)Det_ReportRuntimeError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_WRITEMII_SID, ETH_E_COMMUNICATION);
    }
    #endif
  }
  else
  {
    #if ((ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNC == STD_ON) || (ETH_MACRO_ETNF == STD_ON))
    if (NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwWriteMiibit)                                                         /* PRQA S 3416 # JV-01 */
    {
      /* PRE */
      for (LulBitCount = (uint32)ETH_PHY_PREAMBLE_SIZE; LulBitCount > 0UL; LulBitCount--)
      {
        LucReturnValue |= Eth_GaaHwFunc[LucHWIPType]->pHwWriteMiibit((uint32)CtrlIdx, 1UL);                             
      }
      /* ST, OP, PHYAD, REGAD */
      LulHeader = ETH_PHY_WHEADER(TrcvIdx, RegIdx);                                                                     /* PRQA S 3469 # JV-01 */
      for (LulBitCount = (uint32)ETH_PHY_HEADER_SIZE; LulBitCount > 0UL; LulBitCount--)
      {
        /* Pickup the bit which should be output next, MSB first */
        LulBit = (LulHeader >> (LulBitCount - 1UL)) & 1UL;                                                              /* PRQA S 3383 # JV-01 */
        LucReturnValue |= Eth_GaaHwFunc[LucHWIPType]->pHwWriteMiibit((uint32)CtrlIdx, LulBit);                          
      }

      /* TA: 10 */
        LucReturnValue |= Eth_GaaHwFunc[LucHWIPType]->pHwWriteMiibit((uint32)CtrlIdx, 1UL);                             
        LucReturnValue |= Eth_GaaHwFunc[LucHWIPType]->pHwWriteMiibit((uint32)CtrlIdx, 0UL);                             

      /* DATA */
      for (LulBitCount = (uint32)ETH_PHY_DATA_SIZE; LulBitCount > 0UL; LulBitCount--)
      {
        /* Pickup the bit which should be output next, MSB first */
        LulBit = ((uint32)RegVal >> (LulBitCount - 1UL)) & 1UL;                                                         /* PRQA S 3383 # JV-01 */
        LucReturnValue |= Eth_GaaHwFunc[LucHWIPType]->pHwWriteMiibit((uint32)CtrlIdx, LulBit);                          
        }
    }/* else No action required */

    /* Bus release (MDIO = Z) and IDLE cycle, it is same as read cycle */
    if (NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwReadMiibit)                                                          /* PRQA S 3416 # JV-01 */
    {
      LucReturnValue |= Eth_GaaHwFunc[LucHWIPType]->pHwReadMiibit((uint32)CtrlIdx, &LulRegVal);
    }

    if (E_OK == LucReturnValue)                                                                                         
    {
      /* Since this function is implemented as synchronous, call EthTrcv here */
      EthTrcv_WriteMiiIndication(CtrlIdx, TrcvIdx, RegIdx);
    }
    else
    {
      (void)Det_ReportRuntimeError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_WRITEMII_SID, ETH_E_COMMUNICATION);
    }
    #endif /* (ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNC == STD_ON) || (ETH_MACRO_ETNF == STD_ON) */
  }
  return LucReturnValue;                                                                                                
} /* End of API Eth_WriteMii */

/***********************************************************************************************************************
** Function Name         : Eth_ReadMii
**
** Service ID            : 0x06
**
** Description           : This API Reads the specified transceiver register through the MII of the indexed controller.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**                         TrcvIdx: Index of the transceiver on the MII
**                         RegIdx:  Index of the transceiver register on the MII
**
** InOut Parameters      : None
**
** Output Parameters     : RegValPtr: Filled with the register content of the indexed register
**
** Return parameter      : Std_ReturnType
**                         E_OK: No error has occurred during execution of the API
**                         E_NOT_OK: An error has occurred during execution of the API
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration 
**                         parameter EthCtrlEnableMii.
**
** Global Variables Used : None
**
** Function(s) invoked   : Det_ReportRuntimeError, Det_ReportError, Eth_CommonDetCheck, Eth_HwReadMiiBit,
**                         Eth_HwReadMii, EthTrcv_ReadMiiIndication, Eth_HwWriteMiiBit
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_008, ETH_DUD_ACT_008_ERR001,
** Reference ID          : ETH_DUD_ACT_008_ERR002, ETH_DUD_ACT_008_ERR003, ETH_DUD_ACT_008_ERR004
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_ReadMii(                                                                      /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx,
  P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA)RegValPtr)                                                                     /* PRQA S 3432 # JV-01 */
{
  #if ((ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNC == STD_ON) || (ETH_MACRO_ETNF == STD_ON))
  /* Local variable only used in E2x and U2Ax devices */
  uint32 LulBitCount;
  uint32 LulHeader;
  uint32 LulBit;
  /* uint16 LulRegVal; */
  uint32 LulRegVal;
  #endif
  /* Local variable to hold the DET return value */
  Std_ReturnType LucReturnValue;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;

  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;

  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_READMII_SID, CtrlIdx);
  if (NULL_PTR == RegValPtr)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_READMII_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  /* Check for the valid TrcvIdx  */
  if (ETH_PHY_MAX_PHYAD_IDX < TrcvIdx)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_READMII_SID, ETH_E_INV_PARAM);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  /* Check for the valid RegIdx  */
  if (ETH_PHY_MAX_REGAD_IDX < RegIdx)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_READMII_SID, ETH_E_INV_PARAM);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }

  /* Check if any DET was reported */
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif /* (ETH_DEV_ERROR_DETECT == STD_ON) */

  if ((ETH_HWIP_ETND == LucHWIPType) || (ETH_HWIP_ETNE == LucHWIPType))                                                 /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    #if ((ETH_MACRO_ETND == STD_ON) || (ETH_MACRO_ETNE == STD_ON))

    /* Read data from PHY */
    if (NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwReadMii)                                                             /* PRQA S 3416 # JV-01 */
    {
      LucReturnValue = Eth_GaaHwFunc[LucHWIPType]->pHwReadMii((uint32)CtrlIdx, TrcvIdx, RegIdx, RegValPtr);
    }/* else No action required */
    if (E_OK == LucReturnValue)                                                                                         
    {
      /* Since this function is implemented as synchronous, call EthTrcv here */
      EthTrcv_ReadMiiIndication(CtrlIdx, TrcvIdx, RegIdx, *RegValPtr);                                                  
    }
    else
    {
      (void)Det_ReportRuntimeError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_READMII_SID, ETH_E_COMMUNICATION);
    }
    #endif
  }
  else
  {

    #if ((ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNC == STD_ON) || (ETH_MACRO_ETNF == STD_ON))
    if (NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwWriteMiibit)                                                         /* PRQA S 3416 # JV-01 */
    {
      /* PRE */
      for (LulBitCount = (uint32)ETH_PHY_PREAMBLE_SIZE; LulBitCount > 0UL; LulBitCount--)
      {
        LucReturnValue |= Eth_GaaHwFunc[LucHWIPType]->pHwWriteMiibit((uint32)CtrlIdx, 1UL);                             
      }

      /* ST, OP, PHYAD, REGAD */
      LulHeader = ETH_PHY_RHEADER(TrcvIdx, RegIdx);                                                                     /* PRQA S 3469 # JV-01 */
      for (LulBitCount = (uint32)ETH_PHY_HEADER_SIZE; LulBitCount > 0UL; LulBitCount--)
      {
        /* Pickup the MSB which should be output next, MSB first */
        LulBit = (LulHeader >> (LulBitCount - 1UL)) & 1UL;                                                              /* PRQA S 3383 # JV-01 */
        LucReturnValue |= Eth_GaaHwFunc[LucHWIPType]->pHwWriteMiibit((uint32)CtrlIdx, LulBit);                          
      }
    }/* else No action required */
    
    if (NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwReadMiibit)                                                          /* PRQA S 3416 # JV-01 */
    {
      /* TA[0]: Turn MDIO to Z, it is same as Read cycle */
      LucReturnValue |= Eth_GaaHwFunc[LucHWIPType]->pHwReadMiibit((uint32)CtrlIdx, RegValPtr);
      /* TA[1]: Read 0 from PHY, ignore it */
      LucReturnValue |= Eth_GaaHwFunc[LucHWIPType]->pHwReadMiibit((uint32)CtrlIdx, RegValPtr);                          

      /* DATA */
      LulRegVal = 0UL;
      for (LulBitCount = (uint32)ETH_PHY_DATA_SIZE; LulBitCount > 0UL; LulBitCount--)
      {
        /* Since read data is MSB first, shift left the result */
        LulRegVal = LulRegVal << 1UL;
        /* Read data from PHY */
        LucReturnValue |= Eth_GaaHwFunc[LucHWIPType]->pHwReadMiibit((uint32)CtrlIdx, RegValPtr);                        
        LulRegVal |= *RegValPtr;
      }

      *RegValPtr = (uint16)LulRegVal;                                                                                   
    }

    if (E_OK == LucReturnValue)                                                                                         
    {
      /* Since this function is implemented as synchronous, call EthTrcv here */
      EthTrcv_ReadMiiIndication(CtrlIdx, TrcvIdx, RegIdx, *RegValPtr);
    }
    else
    {
      (void)Det_ReportRuntimeError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_READMII_SID, ETH_E_COMMUNICATION);
    }
    #endif /* #ifdef (ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNC == STD_ON) || (ETH_MACRO_ETNF == STD_ON) */
  }
  return LucReturnValue;                                                                                                
} /* End of API Eth_ReadMii */
#endif /* (ETH_CTRL_ENABLE_MII == STD_ON) */

#if (ETH_GET_DROP_COUNT_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_GetDropCount
**
** Service ID            : 0x14
**
** Description           : Reads a list with drop counter values of the corresponding controller.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx:     Index of the controller
**                         CountValues: Maximal number of values which can be written from DropCount
**
** InOut Parameters      : None
**
** Output Parameters     : DropCount: Pointer to where is stored the version information of this module
**
** Return parameter      : Std_ReturnType
**                         E_OK: success
**                         E_NOT_OK: Transmission failed
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration 
**                         parameter EthGetDropCountApi.
**
** Global Variables Used : None
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_HwGetDropCount
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_009, ETH_DUD_ACT_009_ERR001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE)Eth_GetDropCount(
  uint8 CtrlIdx, uint8 CountValues, P2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) DropCount)
{
  Std_ReturnType LucReturnValue;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_GETDROPCOUNT_SID, CtrlIdx);
  /* Report Error to DET, if the stherStats pointer value is NULL */
  if (NULL_PTR == DropCount)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GETDROPCOUNT_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    Eth_HwGetDropCount((uint32)CtrlIdx, (uint32)CountValues, DropCount);
    LucReturnValue = E_OK;
  }

  return (LucReturnValue);
} /* End of API Eth_GetDropCount */
#endif

#if (ETH_GET_COUNTER_VALUES_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_GetCounterValues
**
** Service ID            : 0x14
**
** Description           : This API Reads a list with drop counter values of the corresponding controller.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : CounterPtr: counter values according to IETF RFC 1757, RFC 1643 and RFC 2233.
**
** Return parameter      : Std_ReturnType
**                         E_OK: success
**                         E_NOT_OK: counter values read failure
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration 
**                         parameter EthGetCounterValuesApi
**
** Global Variables Used : None
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_HwGetCounterValues
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_010, ETH_DUD_ACT_010_ERR001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetCounterValues(                                                             /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, P2VAR(Eth_CounterType, AUTOMATIC, ETH_APPL_DATA) CounterPtr)                                           /* PRQA S 3432 # JV-01 */
{
  Std_ReturnType LucReturnValue;
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_GETCOUNTERVALUES_SID, CtrlIdx);
  /* Report Error to DET, if the stherStats pointer value is NULL */
  if (NULL_PTR == CounterPtr)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GETCOUNTERVALUES_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwGetCounterValues))                                                  /* PRQA S 3416 # JV-01 */
    {
      /* Invoke Eth_HwGetCounterValues to Get drop frame counts for each error factor */
      Eth_GaaHwFunc[LucHWIPType]->pHwGetCounterValues((uint32)CtrlIdx, CounterPtr);
    }/* else No action required */
    LucReturnValue = E_OK;
  }

  return (LucReturnValue);
} /* End of API Eth_GetCounterValues */
#endif

#if (ETH_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
** Function Name         : Eth_GetEtherStats
**
** Service ID            : 0x15
**
** Description           : This API get the ethernet statistics information.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : etherStats: List of values according to IETF RFC 2819
**
** Return parameter      : Std_ReturnType
**                         E_OK: Success
**                         E_NOT_OK: Transmission failed
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration 
**                         parameter EthGetEtherStatsApi.
**
** Global Variables Used : None
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_HwGetEtherStats
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_011, ETH_DUD_ACT_011_ERR001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetEtherStats(
  uint8 CtrlIdx, P2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) etherStats)                                                    
{
  Std_ReturnType LucReturnValue;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_GETETHERSTATS_SID, CtrlIdx);
  /* Report Error to DET, if the stherStats pointer value is NULL */
  if (NULL_PTR == etherStats)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GETETHERSTATS_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    Eth_HwGetEtherStats((uint32)CtrlIdx, etherStats);
    LucReturnValue = E_OK;
  }

  return (LucReturnValue);
} /* End of API Eth_GetEtherStats */
#endif

#if (ETH_GET_RX_STATS_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_GetRxStats
**
** Service ID            : 0x15
**
** Description           : This API Returns the following list according to IETF RFC2819, where the maximal possible 
**                         value shall denote an invalid value.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : RxStats: List of values according to IETF RFC 2819 (Remote Network Monitoring Management
**                                  Information Base).
**
** Return parameter      : Std_ReturnType
**                         E_OK: success
**                         E_NOT_OK: drop counter could not be obtained
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration 
**                         parameter EthGetRxStatsApi.
**
** Global Variables Used : None
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_HwGetRxStats
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_012, ETH_DUD_ACT_012_ERR001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetRxStats(                                                                   /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, P2VAR(Eth_RxStatsType, AUTOMATIC, ETH_APPL_DATA) RxStats)                                              /* PRQA S 3432 # JV-01 */
{
  Std_ReturnType LucReturnValue;
    /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_GETRXSTATS_SID, CtrlIdx);
  /* Report Error to DET, if the stherStats pointer value is NULL */
  if (NULL_PTR == RxStats)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GETRXSTATS_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwGetRxStats))                                                        /* PRQA S 3416 # JV-01 */
    {
      /* Invoke Eth_HwGetRxStats to get Rx statistics information */
      Eth_GaaHwFunc[LucHWIPType]->pHwGetRxStats((uint32)CtrlIdx, RxStats);
    }/* else No action required */
    LucReturnValue = E_OK;
  }

  return (LucReturnValue);
} /* End of API Eth_GetRxStats */
#endif

#if (ETH_GET_TX_STATS_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_GetTxStats
**
** Service ID            : 0x1C
**
** Description           : This API Returns the list of Transmission Statistics out of IETF RFC1213 defined with 
**                         Eth_TxStatsType, where the  maximal possible value shall denote an invalid value.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : TxStats: List of values to read statistic values for
**                                  transmission.
**
** Return parameter      : Std_ReturnType
**                         E_OK: success
**                         E_NOT_OK: Tx-statistics could not be obtained
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration 
**                         parameter EthGetTxStatsApi.
**
** Global Variables Used : None
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_HwGetTxStats
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_013, ETH_DUD_ACT_013_ERR001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetTxStats(                                                                   /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, P2VAR(Eth_TxStatsType, AUTOMATIC, ETH_APPL_DATA) TxStats)                                              /* PRQA S 3432 # JV-01 */
{
  Std_ReturnType LucReturnValue;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_GETTXSTATS_SID, CtrlIdx);
  /* Report Error to DET, if the stherStats pointer value is NULL */
  if (NULL_PTR == TxStats)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GETTXSTATS_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwGetTxStats))                                                        /* PRQA S 3416 # JV-01 */
    {
      /* Invoke Eth_HwGetTxStats to get Tx statistics information */
      Eth_GaaHwFunc[LucHWIPType]->pHwGetTxStats((uint32)CtrlIdx, TxStats);
    }/* else No action required */
    LucReturnValue = E_OK;
  }

  return (LucReturnValue);
} /* End of API Eth_GetTxStats */
#endif

#if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_GetTxErrorCounterValues
**
** Service ID            : 0x1D
**
** Description           : This API Returns the list of Transmission Error Counters out of IETF RFC1213 and RFC1643 
**                         defined with Eth_TxErrorCounterValuesType, where the maximal possible value shall denote 
**                         an invalid value.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : TxErrorCounterValues: List of values to read statistic values for transmission.
**
** Return parameter      : Std_ReturnType
**                         E_OK: success
**                         E_NOT_OK: Tx-statistics could not be obtained
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration 
**                         parameter EthGetTxErrorCounterValuesApi.
**
** Global Variables Used : None
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_HwGetTxErrorCounterValues
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_014, ETH_DUD_ACT_014_ERR001
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetTxErrorCounterValues(                                                      /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, P2VAR(Eth_TxErrorCounterValuesType, AUTOMATIC, ETH_APPL_DATA) TxErrorCounterValues)                    /* PRQA S 3432 # JV-01 */
{
  Std_ReturnType LucReturnValue;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_GETTXERRORCOUNTERVALUES_SID, CtrlIdx);
  /* Report Error to DET, if the stherStats pointer value is NULL */
  if (NULL_PTR == TxErrorCounterValues)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID,
      ETH_GETTXERRORCOUNTERVALUES_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwGetTxErrorCounterValues))                                           /* PRQA S 3416 # JV-01 */
    {
      Eth_GaaHwFunc[LucHWIPType]->pHwGetTxErrorCounterValues((uint32)CtrlIdx, TxErrorCounterValues);
    }/* else No action required */
    LucReturnValue = E_OK;
  }

  return (LucReturnValue);
} /* End of API Eth_GetTxErrorCounterValues */
#endif

/***********************************************************************************************************************
** Function Name         : Eth_ProvideTxBuffer
**
** Service ID            : 0x09
**
** Description           : This API Provides access to a transmit buffer of the specified controller
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : CtrlIdx:  Index of the controller
**                         Priority: Frame priority for transmit buffer FIFO selection *This parameter is valid for
**                                   AUTOSAR R4.3.1 later
**
** InOut Parameters      : LenBytePtr: In:  desired length in bytes,
**                                     Out: granted length in bytes
**
** Output Parameters     : BufIdxPtr: Index to the granted buffer resource
**                         BufPtr:    Pointer to the granted buffer
**
** Return parameter      : BufReq_ReturnType
**                         BUFREQ_OK:       success
**                         BUFREQ_E_NOT_OK: development error detected
**                         BUFREQ_E_BUSY:   all buffers in use
**                         BUFREQ_E_OVFL:   the requested size is larger than the buffer
**
** Preconditions         : Component Requires previous controller initialization using Eth_Init.
**
** Global Variables Used : Eth_GaaCtrlStat
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_GetTxBuffer
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_015, ETH_DUD_ACT_015_ERR001,
** Reference ID          : ETH_DUD_ACT_015_ERR002, ETH_DUD_ACT_015_ERR003,
** Reference ID          : ETH_DUD_ACT_015_ERR004
***********************************************************************************************************************/
FUNC(BufReq_ReturnType, ETH_PUBLIC_CODE) Eth_ProvideTxBuffer(                                                           /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx,
  #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
  uint8 Priority,
  #endif
  P2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) BufIdxPtr,                                                            /* PRQA S 3432 # JV-01 */
  P2VAR(uint8*, AUTOMATIC, ETH_APPL_DATA) BufPtr,                                                                       /* PRQA S 3432 # JV-01 */
  P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr)                                                                   /* PRQA S 3432 # JV-01 */
{
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucCommonResult;
  #endif
  BufReq_ReturnType LenReturnValue;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;

  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LenReturnValue = BUFREQ_OK;
  LucCommonResult = Eth_CommonDetCheck(ETH_PROVIDETXBUFFER_SID, CtrlIdx);
  if (E_OK != LucCommonResult)
  {
    LenReturnValue = BUFREQ_E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  /* Report Error to DET, if the BufIdxPtr pointer value is NULL */
  if (NULL_PTR == BufIdxPtr)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_PROVIDETXBUFFER_SID, ETH_E_PARAM_POINTER);
    LenReturnValue = BUFREQ_E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (NULL_PTR == BufPtr)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_PROVIDETXBUFFER_SID, ETH_E_PARAM_POINTER);
    LenReturnValue = BUFREQ_E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (NULL_PTR == LenBytePtr)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_PROVIDETXBUFFER_SID, ETH_E_PARAM_POINTER);
    LenReturnValue = BUFREQ_E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (BUFREQ_OK != LenReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    /* Report Error to DET, if the controller mode Is not Active */
    if (ETH_MODE_ACTIVE != Eth_GaaCtrlStat[CtrlIdx].enMode)                                                             
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_PROVIDETXBUFFER_SID, ETH_E_INV_MODE);
      #endif
      LenReturnValue = BUFREQ_E_NOT_OK;
    }
    else
    {
      if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pGetTxBuffer))                                                       /* PRQA S 3416 # JV-01 */
      {
        /* Get a buffer from the TxBufferRing */
        #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
        LenReturnValue = Eth_GaaHwFunc[LucHWIPType]->pGetTxBuffer(
                                                        (uint32)CtrlIdx, Priority, BufIdxPtr, BufPtr, LenBytePtr);
        #else
        LenReturnValue = Eth_GaaHwFunc[LucHWIPType]->pGetTxBuffer((uint32)CtrlIdx, BufIdxPtr, BufPtr, LenBytePtr);
        #endif
      }
    }
  }  
  return(LenReturnValue);                                                                                               /* PRQA S 2962 # JV-01 */
} /* End of API Eth_ProvideTxBuffer */

/***********************************************************************************************************************
** Function Name         : Eth_Transmit
**
** Service ID            : 0x0A
**
** Description           : This API triggers transmission of a previously filled transmit buffer
**
** Sync/Async            : Asynchronous
**
** Reentrancy            : Reentrant for different buffer indexes and
**                         Ctrl indexes
**
** Input Parameters      : CtrlIdx:        Index of the controller
**                         BufIdx:         Index of the buffer resource
**                         FrameType:      Ethernet frame type
**                         TxConfirmation: Activates transmission confirmation
**                         LenByte:        Data length in byte
**                         PhysAddrPtr:    Physical target address (MAC address)
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: Success.
**                         E_NOT_OK: Transmission failed.
**
** Preconditions         : Component Requires previous controller initialization using Eth_Init.
**
** Global Variables Used : Eth_GaaCtrlStat, Eth_GaaTxBufferTotal
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck,
**                         Eth_CheckProvideBuffer, Eth_PreprocessFrame,
**                         Eth_HwTransmit
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_016, ETH_DUD_ACT_016_ERR001,
** Reference ID          : ETH_DUD_ACT_016_ERR002, ETH_DUD_ACT_016_ERR003,
** Reference ID          : ETH_DUD_ACT_016_ERR004
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_Transmit(                                                                     /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, Eth_BufIdxType BufIdx, Eth_FrameType FrameType, boolean TxConfirmation,
  uint16 LenByte, P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr)
{
  Std_ReturnType LucReturnValue;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_TRANSMIT_SID, CtrlIdx);
  /* Report Error to DET, if the PhysAddrPtr pointer value is NULL */
  if (NULL_PTR == PhysAddrPtr)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_TRANSMIT_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  /* ETNC need #define ETH_TX_DESC_MAX ETH_TX_BUF_TOTAL_0 */
  /* Report Error to DET, if the BufIdx is out of range */
  #if ((ETH_MACRO_ETNF == STD_ON) || (ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNC == STD_ON))
  if ((ETH_HWIP_ETNF == LucHWIPType) || (ETH_HWIP_ETNB == LucHWIPType) || (ETH_HWIP_ETNC == LucHWIPType))               /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    if ((uint32)ETH_TX_DESC_MAX <= BufIdx)
    {
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_TRANSMIT_SID, ETH_E_INV_PARAM);
      LucReturnValue = E_NOT_OK;
    }/* else No action required */
  }
  else
  #endif
  {
    #if ((ETH_MACRO_ETND == STD_ON) || (ETH_MACRO_ETNE == STD_ON))
    if (Eth_GaaTxBufferTotal[CtrlIdx] <= BufIdx)
    {
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_TRANSMIT_SID, ETH_E_INV_PARAM);
      LucReturnValue = E_NOT_OK;
    }/* else No action required */
    #endif
  }
  
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    /* Report Error to DET, if the controller mode Is not Active */
    if (ETH_MODE_ACTIVE != Eth_GaaCtrlStat[CtrlIdx].enMode)                                                             
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_TRANSMIT_SID, ETH_E_INV_MODE);
      #endif
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pCheckProvideBuffer))                                                /* PRQA S 3416 # JV-01 */
      {
        /* Invoke Eth_CheckProvideBuffer to check whether the memory 
           at the specified buffer index has been allocated*/
        LucReturnValue = Eth_GaaHwFunc[LucHWIPType]->pCheckProvideBuffer((uint32)CtrlIdx, (uint32)BufIdx);
      }/* else No action required */
      /* If the buffer has not been provided, report the error */
      if (E_OK != LucReturnValue)                                                                                       /* PRQA S 2962 # JV-01 */
      {
        #if (ETH_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_TRANSMIT_SID, ETH_E_INV_PARAM);
        #endif
      }
      else
      {
        /* Invoke Eth_PreprocessFrame to prepare a frame for transmission.*/
        if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pPreprocessFrame))                                                 /* PRQA S 3416 # JV-01 */
        {
        #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
        Eth_GaaHwFunc[LucHWIPType]->pPreprocessFrame((uint32)CtrlIdx, (uint32)BufIdx, 
                                                     (uint32)FrameType, PhysAddrPtr, &LenByte);                         /* PRQA S 1339 # JV-01 */
        #else
        Eth_GaaHwFunc[LucHWIPType]->pPreprocessFrame((uint32)CtrlIdx, (uint32)BufIdx, (uint32)FrameType, PhysAddrPtr);
        #endif
        }/* else No action required */
        if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwTransmit))                                                      /* PRQA S 3416 # JV-01 */
        {
        /* Send a transmit request to the low level driver */
        LucReturnValue = Eth_GaaHwFunc[LucHWIPType]->pHwTransmit((uint32)CtrlIdx, (uint32)BufIdx, 
                                                                 (uint32)LenByte, TxConfirmation);
        }/* else No action required */
      }
    }
  }
  return LucReturnValue;                                                                                                /* PRQA S 2962 # JV-01 */
} /* End of API Eth_Transmit */

#if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_Receive
**
** Service ID            : 0x0B
**
** Description           : This API Triggers frame reception
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant for different FIFOs.
**                         Non Reentrant for the same FIFO.
**
** Input Parameters      : CtrlIdx: Index of the controller
**                         QueueIdx: Specifies the related FIFO
**                             *This parameter is valid for AUTOSAR R4.3.1 later
**
** InOut Parameters      : None
**
** Output Parameters     : RxStatusPtr: Indicates whether a frame has been received and if so, whether more frames
**                                      are available or frames got lost.
**
** Return parameter      : None
**
** Preconditions         : Component Requires previous controller initialization using Eth_Init.
**
** Global Variables Used : Eth_GaaCtrlStat
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck,
**                         Eth_HwCheckFifoIndex, Eth_HwReceive
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_017, ETH_DUD_ACT_017_ERR001,
** Reference ID          : ETH_DUD_ACT_017_ERR002, ETH_DUD_ACT_017_ERR003
***********************************************************************************************************************/
FUNC(void, ETH_PUBLIC_CODE) Eth_Receive(                                                                                /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx,
  #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
  uint8 QueueIdx,
  #endif
  P2VAR(Eth_RxStatusType, AUTOMATIC, ETH_APPL_DATA) RxStatusPtr)                                                        /* PRQA S 3432 # JV-01 */
{
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucReturnValue;
  #endif
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_RECEIVE_SID, CtrlIdx);
  #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
  if (E_OK == LucReturnValue)
  {
    if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwCheckFifoIndex))                                                    /* PRQA S 3416 # JV-01 */
    {
      /* Invoke Eth_HwCheckFifoIndex to check the validity of the Queue index specified in the Eth_Receive*/
      LucReturnValue = Eth_GaaHwFunc[LucHWIPType]->pHwCheckFifoIndex((uint32)CtrlIdx, (uint32)QueueIdx);
    }/* else No action required */
    if (E_OK != LucReturnValue)
    {
      /* Report Error to DET, if the FifoIdx is out of range */
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_RECEIVE_SID, ETH_E_INV_PARAM);
    }
    else
    {
      /* No action required */
    }
  }
  else
  {
    /* No action required */
  }
  #endif
  /* Report Error to DET, if the RxStatusPtr pointer value is NULL */
  if (NULL_PTR == RxStatusPtr)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_RECEIVE_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Initial Value Set */
    *RxStatusPtr = ETH_NOT_RECEIVED;
  }
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif /* (ETH_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Report Error to DET, if the controller mode Is not Active */
    if (ETH_MODE_ACTIVE != Eth_GaaCtrlStat[CtrlIdx].enMode)                                                             
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_RECEIVE_SID, ETH_E_INV_MODE);
      #endif
      *RxStatusPtr = ETH_NOT_RECEIVED;                                                                                  
    }
    else
    {
      /* Invoke Eth_HwReceive to update Descriptor */
      if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwReceive))                                                         /* PRQA S 3416 # JV-01 */
      {
      #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
      *RxStatusPtr = Eth_GaaHwFunc[LucHWIPType]->pHwReceive((uint32)CtrlIdx, (uint32)QueueIdx);
      #else
      *RxStatusPtr = Eth_GaaHwFunc[LucHWIPType]->pHwReceive((uint32)CtrlIdx);
      #endif
      }
    }
  }
}
#endif /* (ETH_CTRL_ENABLE_RX_POLLING == STD_ON) */

#if (ETH_CTRL_ENABLE_TX_POLLING == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_TxConfirmation
**
** Service ID            : 0x0C
**
** Description           : This API Triggers frame transmission confirmation
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Component Requires previous controller initialization
**                         using Eth_Init.
**
** Global Variables Used : Eth_GaaCtrlStat
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck,
**                         Eth_HwTxConfirmation
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_018, ETH_DUD_ACT_018_ERR001
***********************************************************************************************************************/
FUNC(void, ETH_PUBLIC_CODE) Eth_TxConfirmation(                                                                         /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx)
{
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucReturnValue;
  #endif
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_TXCONFIRMATION_SID, CtrlIdx);
  /* Do not execute at ETH_E_INV_CTRL_IDX */
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    /* Report Error to DET, if the controller mode Is not Active */
    if (ETH_MODE_ACTIVE != Eth_GaaCtrlStat[CtrlIdx].enMode)                                                             
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_TXCONFIRMATION_SID, ETH_E_INV_MODE);
      #endif
    }
    else
    {
      if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwTxConfirmation))                                                  /* PRQA S 3416 # JV-01 */
      {
        /* Invoke Eth_HwTxConfirmation to perform transmission processing, notify the upper layer of 
        transmission completion and release the Tx buffer */
        Eth_GaaHwFunc[LucHWIPType]->pHwTxConfirmation((uint32)CtrlIdx);
      }/* else No Action required */
    }
  }
}
#endif /* (ETH_CTRL_ENABLE_TX_POLLING == STD_ON) */

#if (ETH_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_GetVersionInfo
**
** Service ID            : 0x0D
**
** Description           : This API returns the version information of Ethernet driver component.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : VersionInfoPtr : Pointer to where is stored the version information of this module
**
** Return parameter      : None
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration 
**                         parameter ETH_VERSION_INFO_API.
**
** Global Variables      : None
**
** Functions invoked     : Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_019, ETH_DUD_ACT_019_ERR001
***********************************************************************************************************************/
FUNC(void, ETH_PUBLIC_CODE) Eth_GetVersionInfo(                                                                         /* PRQA S 1503 # JV-01 */
  P2VAR(Std_VersionInfoType, AUTOMATIC, ETH_APPL_DATA)VersionInfoPtr)                                                   /* PRQA S 3432 # JV-01 */
{
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == VersionInfoPtr)
  {
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GET_VERSION_INFO_SID, ETH_E_PARAM_POINTER);
  }
  else
  #endif
  {
    VersionInfoPtr->vendorID = (uint16)ETH_VENDOR_ID;                                                                   
    VersionInfoPtr->moduleID = (uint16)ETH_MODULE_ID;
    VersionInfoPtr->sw_major_version = (uint8)ETH_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = (uint8)ETH_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = (uint8)ETH_SW_PATCH_VERSION;
  }
}
#endif /* (STD_ON == ETH_VERSION_INFO_API ) */

/***********************************************************************************************************************
** Function Name         : Eth_MainFunction
**
** Service ID            : 0x20
**
** Description           : The function checks for controller errors and lost frames.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Eth_GpDriverState, Eth_GpTotalCtrlConfig, Eth_CtrlConfigIdx, Eth_GpCoreId2Index
**
** Functions invoked     : Eth_HwMainFunction, GetCoreID
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_020, ETH_DUD_ACT_020_ERR001
***********************************************************************************************************************/
FUNC(void, ETH_PUBLIC_CODE) Eth_MainFunction(void)                                                                      /* PRQA S 1503 # JV-01 */
{
  Eth_StateType LenState;
  uint32 LulIdx;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  uint8 LucCoreIndex;
  uint32 LulCtrIdx;
  uint32 LulTotalCtrlConfig;

  #if (ETH_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Eth_GpCoreId2Index[LucCoreId];                                                                         
  #else
  /* if Multicore is not configude, defauld coreid is 0x00
     To optimize implementation */
  LucCoreIndex = ETH_ZERO;
  #endif /* End of #if (ETH_MULTI_CORE_SUPPORT == STD_ON)*/

  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  #if (ETH_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core */
  if(ETH_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_MAINFUNCTION_SID, ETH_E_INVALID_CORE);
  }
  else
  #endif /* End of #if (ETH_MULTI_CORE_SUPPORT == STD_ON)*/
  #endif /* End of #if (ETH_DEV_ERROR_DETECT == STD_ON) */
  {
    LenState = Eth_GpDriverState[LucCoreIndex];                                                                         
    if (ETH_STATE_INIT != LenState)
    {
      /* No Action required */
    }
    else
    {
      /* Get total controller configured */
      LulTotalCtrlConfig = Eth_GpTotalCtrlConfig[LucCoreIndex];                                                         
      for (LulIdx = 0UL; LulIdx < (uint32)LulTotalCtrlConfig; LulIdx++)
      {
        /* Get controller index configured */
        LulCtrIdx = Eth_CtrlConfigIdx[LucCoreIndex][LulIdx];                                                            
        /* Get unit type */
        LucHWIPType = Eth_GaaHWIP[LulCtrIdx].ucIndex;                                                                   
        if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwMainFunction))                                                  /* PRQA S 3416 # JV-01 */
        {
          /* Error check and device specific operations */
          Eth_GaaHwFunc[LucHWIPType]->pHwMainFunction(LulCtrIdx);
        }/* else No Action required */
      }
    }
  }
}  

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_GetCurrentTime
**
** Service ID            : 0x16
**
** Description           : Returns a time value out of the HW registers according to the capability of the HW
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : timeQualPtr:  Quality of the HW TimeStamp returned
**                         timeStampPtr: Current TimeStamp value
**
** Return parameter      : Std_ReturnType
**                         E_OK: Success
**                         E_NOT_OK: Failed
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration 
**                         parameter EthGlobalTimeSupport.
**
** Global Variables Used : Eth_GaaCtrlStat,
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_HwGetCurrentTime
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_021, ETH_DUD_ACT_021_ERR001,
** Reference ID          : ETH_DUD_ACT_021_ERR002
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetCurrentTime(                                                               /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,                                    /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr)                                                      /* PRQA S 3432 # JV-01 */
{
  Std_ReturnType LucReturnValue;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_GETCURRENTTIME_SID, CtrlIdx);
  if ((NULL_PTR == timeQualPtr) || (NULL_PTR == timeStampPtr))
  {
    /* Report Error to DET */
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GETCURRENTTIME_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No Action required */
  }
  if (E_OK != LucReturnValue)
  {
    /* No Action required */
  }
  else
  #endif
  {
    if (ETH_MODE_ACTIVE != Eth_GaaCtrlStat[CtrlIdx].enMode)                                                             
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      /* Report Error to DET */
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GETCURRENTTIME_SID, ETH_E_INV_MODE);
      #endif
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /*Invoke Eth_HwGetCurrentTime to return TimeStamp from the HW register previously started.*/
      if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwGetCurrentTime))                                                  /* PRQA S 3416 # JV-01 */
      {
      LucReturnValue = Eth_GaaHwFunc[LucHWIPType]->pHwGetCurrentTime((uint32)CtrlIdx, timeQualPtr, timeStampPtr);
      }/* else no action required */
    }
  }
  return (LucReturnValue);                                                                                              /* PRQA S 2962 # JV-01 */
}

/***********************************************************************************************************************
** Function Name         : Eth_EnableEgressTimeStamp
**
** Service ID            : 0x17
**
** Description           : Enable TimeStamp capture for the message that will be transmitted
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**                         BufIdx:  Index of the message buffer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration 
**                         parameter EthGlobalTimeSupport.
**
** Global Variables Used : None
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_FindTxBufferHandler, Eth_CheckProvideBuffer
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_022,
** Reference ID          : ETH_DUD_ACT_022_ERR001
***********************************************************************************************************************/
FUNC(void, ETH_PUBLIC_CODE) Eth_EnableEgressTimeStamp(                                                                  /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, Eth_BufIdxType BufIdx)
{
  P2VAR(Eth_BufHandlerType, AUTOMATIC, ETH_APPL_DATA) LpBufHandlerPtr;                                                  /* PRQA S 3432 # JV-01 */
  Std_ReturnType LucErrorValue;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;

  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold the DET value */
  LucErrorValue = Eth_CommonDetCheck(ETH_ENEGRESSTS_SID, CtrlIdx);
  if (E_OK != LucErrorValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pCheckProvideBuffer))                                                  /* PRQA S 3416 # JV-01 */
    {
      /* Invoke Eth_CheckProvideBuffer to check whether the memory 
        at the specified buffer index has been allocated*/
      LucErrorValue = Eth_GaaHwFunc[LucHWIPType]->pCheckProvideBuffer((uint32)CtrlIdx, (uint32)BufIdx);
    }/* else No action required */
    /* Invalid Buffer */
    if (E_OK != LucErrorValue)                                                                                          /* PRQA S 2962 # JV-01 */
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_ENEGRESSTS_SID, ETH_E_INV_PARAM);
      #endif
    }
    else
    {
      /* This will be written in the Ram Descriptor on the next Eth_Transmit call */
      if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pFindTxBufferHandler))                                               /* PRQA S 3416 # JV-01 */
      {
      LpBufHandlerPtr = Eth_GaaHwFunc[LucHWIPType]->pFindTxBufferHandler((uint32)CtrlIdx, (uint32)BufIdx);
      } /* else No action required */
      if (NULL_PTR != LpBufHandlerPtr)                                                                                  /* PRQA S 2962 # JV-01 */
      {
        LpBufHandlerPtr->blbenableTS = ETH_TRUE;                                                                        /* PRQA S 2962 # JV-01 */
      }
      else
      {
        /* No action required */
      }
    }
  }
}

/***********************************************************************************************************************
** Function Name         : Eth_GetEgressTimeStamp
**
** Service ID            : 0x18
**
** Description           : Reads back the egress time stamp on a dedicated message object.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**                         BufIdx:  Index of the message buffer
**
** InOut Parameters      : None
**
** Output Parameters     : timeQualPtr:  Quality of HW time stamp
**                         timeStampPtr: Current time stamp
**
** Return parameter      : None
**                         For R19-11 or later, Std_ReturnType
**                                              E_OK: Success
**                                              E_NOT_OK: Failed
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration 
**                         parameter EthGlobalTimeSupport.
**
** Global Variables Used :
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck,
**                         Eth_HwGetEgressTimeStamp
**
** Registers Used        : Eth_GaaCtrlStat
**
** Reference ID          : ETH_DUD_ACT_023, ETH_DUD_ACT_023_ERR001,
** Reference ID          : ETH_DUD_ACT_023_ERR002
***********************************************************************************************************************/
#if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetEgressTimeStamp(                                                           /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, Eth_BufIdxType BufIdx,
  P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,                                                   /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr)                                                      /* PRQA S 3432 # JV-01 */
#else
FUNC(void, ETH_PUBLIC_CODE) Eth_GetEgressTimeStamp(                                                                     
  uint8 CtrlIdx, Eth_BufIdxType BufIdx,
  P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,                                                   
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr)                                                      
#endif
{
  #if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
  Std_ReturnType LucReturnValue;
  #endif
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucErrorValue;
  #endif
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold the DET value */
  LucErrorValue = Eth_CommonDetCheck(ETH_GETEGRESSTS_SID, CtrlIdx);
  if ((NULL_PTR == timeQualPtr) || (NULL_PTR == timeStampPtr))
  {
    /* Report Error to DET */
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GETEGRESSTS_SID, ETH_E_PARAM_POINTER);
    LucErrorValue = E_NOT_OK;
  }
  else
  {
    /* No Action required */
  }
  if (E_OK != LucErrorValue)
  {
    #if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
    LucReturnValue = E_NOT_OK;
    #endif
  }
  else
  #endif
  {
    if (ETH_MODE_ACTIVE != Eth_GaaCtrlStat[CtrlIdx].enMode)                                                             
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      /* Report Error to DET */
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GETEGRESSTS_SID, ETH_E_INV_MODE);
      #endif
      #if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
      LucReturnValue = E_NOT_OK;
      #endif
    }
    else
    {
      #if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
      if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwGetEgressTimeStamp))                                              /* PRQA S 3416 # JV-01 */
      {
      LucReturnValue = Eth_GaaHwFunc[LucHWIPType]->pHwGetEgressTimeStamp((uint32)CtrlIdx, BufIdx, 
                                                                                 timeQualPtr, timeStampPtr);
      }/* else no Action required */
      #else
      if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwGetEgressTimeStamp))
      {
      Eth_GaaHwFunc[LucHWIPType]->pHwGetEgressTimeStamp((uint32)CtrlIdx, BufIdx, timeQualPtr, timeStampPtr);
      }/* else no Action required */
      #endif
    }
  }

  #if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
  return LucReturnValue;                                                                                                /* PRQA S 2962 # JV-01 */
  #endif
}

/***********************************************************************************************************************
** Function Name         : Eth_GetIngressTimeStamp
**
** Service ID            : 0x19
**
** Description           : Return TimeStamp from the HW register
**                         previously started
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**                         DataPtr: Pointer to the message buffer
**
** InOut Parameters      : None
**
** Output Parameters     : timeQualPtr:  Quality of HW time stamp
**                         timeStampPtr: Current time stamp
**
** Return parameter      : None
**                         For R19-11 or later, Std_ReturnType
**                                              E_OK: Success
**                                              E_NOT_OK: Failed
**
** Preconditions         : This function is pre-compile time configurable
**                        (STD_ON/STD_OFF) by the configuration parameter
**                         EthGlobalTimeSupport.
**
** Global Variables Used : Eth_GaaCtrlStat
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck,
**                         Eth_HwGetIngressTimeStamp
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_024, ETH_DUD_ACT_024_ERR001,
** Reference ID          : ETH_DUD_ACT_024_ERR002
***********************************************************************************************************************/
#if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetIngressTimeStamp(                                                          /* PRQA S 1503 # JV-01 */
  uint8 CtrlIdx, P2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) DataPtr,
  P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,                                                   /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr)                                                      /* PRQA S 3432 # JV-01 */
#else
FUNC(void, ETH_PUBLIC_CODE) Eth_GetIngressTimeStamp(                                                                    
  uint8 CtrlIdx, P2CONST(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) DataPtr,
  P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETH_APPL_DATA) timeQualPtr,                                                   
  P2VAR(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr)                                                      
#endif
{
  #if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
  Std_ReturnType LucReturnValue;
  #endif
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucErrorValue;
  #endif
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold the DET value */
  LucErrorValue = Eth_CommonDetCheck(ETH_GETINGRESSTS_SID, CtrlIdx);
  if ((NULL_PTR == DataPtr) || (NULL_PTR == timeQualPtr) || (NULL_PTR == timeStampPtr))
  {
    /* Report Error to DET */
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GETINGRESSTS_SID, ETH_E_PARAM_POINTER);
    LucErrorValue = E_NOT_OK;
  }
  else
  {
    /* No Action required */
  }
  if (E_OK != LucErrorValue)
  {
    #if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
    LucReturnValue = E_NOT_OK;
    #endif
  }
  else
  #endif
  {
    if (ETH_MODE_ACTIVE != Eth_GaaCtrlStat[CtrlIdx].enMode)                                                             
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      /* Report Error to DET */
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_GETINGRESSTS_SID, ETH_E_INV_MODE);
      #endif
      #if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
      LucReturnValue = E_NOT_OK;
      #endif
    }
    else
    {
      #if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
      if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwGetIngressTimeStamp))                                             /* PRQA S 3416 # JV-01 */
      {
        LucReturnValue = Eth_GaaHwFunc[LucHWIPType]->pHwGetIngressTimeStamp((uint32)CtrlIdx, DataPtr, 
                                                                            timeQualPtr, timeStampPtr);
      }/* else no Action required */
      #else
      if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwGetIngressTimeStamp))
      {
      Eth_GaaHwFunc[LucHWIPType]->pHwGetIngressTimeStamp((uint32)CtrlIdx, DataPtr, timeQualPtr, timeStampPtr);
      }/* else no Action required */
      #endif
    }
  }

  #if (ETH_AR_VERSION >= ETH_AR_R19_11_VERSION)
  return LucReturnValue;                                                                                                /* PRQA S 2962 # JV-01 */
  #endif
}

#if (ETH_AR_VERSION == ETH_AR_422_VERSION)
/***********************************************************************************************************************
** Function Name         : Eth_SetCorrectionTime
**
** Service ID            : 0x1A
**
** Description           : Allows the Time Slave to adjust the local ETH
**                         Reference clock in HW
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant

** Input Parameters      : CtrlIdx:       Index of the controller
**                         timeOffsetPtr: Offset between time stamp grandmaster and time stamp by local clock
**                         rateRatioPtr:  Time elements to calculate and to modify the ratio of the frequency of the
**                                      grandmaster in relation to the frequency of the Local Clock.
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration
**                         parameter EthGlobalTimeSupport.
**
** Global Variables Used : Eth_GaaCtrlStat
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_HwSetCorrectionTime
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_025, ETH_DUD_ACT_025_ERR001,
** Reference ID          : ETH_DUD_ACT_025_ERR002
***********************************************************************************************************************/
FUNC(void, ETH_PUBLIC_CODE) Eth_SetCorrectionTime(
  uint8 CtrlIdx, P2CONST(Eth_TimeIntDiffType, AUTOMATIC, ETH_APPL_DATA) timeOffsetPtr,
  P2CONST(Eth_RateRatioType, AUTOMATIC, ETH_APPL_DATA) rateRatioPtr)
{
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType LucErrorValue;
  /* Local variable to hold the DET value */
  LucErrorValue = Eth_CommonDetCheck(ETH_SETCORRECTIONTIME_SID, CtrlIdx);
  if ((NULL_PTR == timeOffsetPtr) || (NULL_PTR == rateRatioPtr))
  {
    /* Report Error to DET */
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SETCORRECTIONTIME_SID, ETH_E_PARAM_POINTER);
    LucErrorValue = E_NOT_OK;
  }
  else
  {
    /* No Action required */
  }
  if (E_OK != LucErrorValue)
  {
    /* No Action required */
  }
  else
  #endif
  {
    if (ETH_MODE_ACTIVE != Eth_GaaCtrlStat[CtrlIdx].enMode)
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      /* Report Error to DET */
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SETCORRECTIONTIME_SID, ETH_E_INV_MODE);
      #endif
    }
    else
    {
      (void)Eth_HwSetCorrectionTime(CtrlIdx, timeOffsetPtr);
    }
  }
}

/***********************************************************************************************************************
** Function Name         : Eth_SetGlobalTime
**
** Service ID            : 0x1B
**
** Description           : Allows the Time Master to adjust the global ETH
**                         Reference clock in HW.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**                         timeStampPtr: New time stamp
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: Success
**                         E_NOT_OK: Failed
**
** Preconditions         : This function is pre-compile time configurable (STD_ON/STD_OFF) by the configuration 
**                         parameter EthGlobalTimeSupport.
**
** Global Variables Used : Eth_GaaCtrlStat
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_HwSetGlobalTime
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_026, ETH_DUD_ACT_026_ERR001,
** Reference ID          : ETH_DUD_ACT_026_ERR002
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_SetGlobalTime(
  uint8 CtrlIdx, P2CONST(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) timeStampPtr)
{
  Std_ReturnType LucReturnValue;
  LucReturnValue = E_OK;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_SETGLOBALTIME_SID, CtrlIdx);
  if (NULL_PTR == timeStampPtr)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SETGLOBALTIME_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No Action required */
  }
  if (E_OK != LucReturnValue)
  {
    /* No Action required */
  }
  else
  #endif
  {
    if (ETH_MODE_ACTIVE != Eth_GaaCtrlStat[CtrlIdx].enMode)
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      /* Report Error to DET */
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SETGLOBALTIME_SID, ETH_E_INV_MODE);
      #endif
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      LucReturnValue = Eth_HwSetGlobalTime(CtrlIdx, timeStampPtr);
    }
  }
  return (LucReturnValue);
}
#endif /* (ETH_AR_VERSION == ETH_AR_422_VERSION) */

#if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
/***********************************************************************************************************************
** Function Name         : Eth_SetIncrementTimeForGptp
**
** Service ID            : 0xA1
**
** Description           : Sets the gPTP timer increment with the specified value.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**                         IncVal:  Increment value for gPTP timer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: gPTP increment register was successfully changed
**                         E_NOT_OK: gPTP increment register could not be changed and the DET is ON
**
** Preconditions         : Component Requires previous controller initialization using Eth_Init.
**
** Global Variables Used : Eth_GaaCtrlStat
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck,
**                         Eth_HwSetIncrementTimeForGptp
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_027,
** Reference ID          : ETH_DUD_ACT_027_ERR002, ETH_DUD_ACT_027_ERR003
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_SetIncrementTimeForGptp(                                                      /* PRQA S 1503 # JV-01 */
  CONST(uint8, AUTOMATIC) CtrlIdx, CONST(uint32, AUTOMATIC) IncVal)
{
  Std_ReturnType LucReturnValue;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_SETINCREMENTTIMEFORGPTP_SID, CtrlIdx);
  if (E_OK != LucReturnValue)
  {
    /* No Action required */
  }
  else
  #endif
  {
    if (ETH_MODE_ACTIVE != Eth_GaaCtrlStat[CtrlIdx].enMode)                                                             
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      /* Report Error to DET, if the controller mode Is Standby */
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SETINCREMENTTIMEFORGPTP_SID, ETH_E_INV_MODE);
      #endif
      LucReturnValue = E_NOT_OK;
    }
    #if ((ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNF == STD_ON))
    else if ((ETH_GPTP_INC_MINVALUE > IncVal) || (ETH_GPTP_INC_MAXVALUE < IncVal))
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      /* Report Error to DET, if the increment value for gPTP timer out of range */
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SETINCREMENTTIMEFORGPTP_SID, ETH_E_INV_PARAM);
      #endif
      LucReturnValue = E_NOT_OK;
    }
    #endif
    else
    {
      /* Invoke Eth_SetIncrementTimeForGptp to set a value to GTI and issue a load request*/
      if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwSetIncrementTimeForGptp))                                         /* PRQA S 3416 # JV-01 */
      {
      LucReturnValue = Eth_GaaHwFunc[LucHWIPType]->pHwSetIncrementTimeForGptp((uint32)CtrlIdx, IncVal);
      }
    }
  }
  return LucReturnValue;                                                                                                /* PRQA S 2962 # JV-01 */
}

/***********************************************************************************************************************
** Function Name         : Eth_SetOffsetTimeForGptp
**
** Service ID            : 0xA2
**
** Description           : Sets the gPTP timer offset with the specified value.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx:        Index of the controller
**                         pTimeOffsetPtr: Offset value for gPTP timer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: gPTP offset register was successfully changed
**                         E_NOT_OK: gPTP offset register could not be changed and the DET is ON
**
** Preconditions         : Component Requires previous controller initialization using Eth_Init.
**
** Global Variables Used : Eth_GaaCtrlStat
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_HwSetOffsetTimeForGptp
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_028,
** Reference ID          : ETH_DUD_ACT_028_ERR002
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_SetOffsetTimeForGptp(                                                         /* PRQA S 1503 # JV-01 */
  CONST(uint8, AUTOMATIC) CtrlIdx, CONSTP2CONST(Eth_TimeStampType, AUTOMATIC, ETH_APPL_DATA) pTimeOffsetPtr)
{
  Std_ReturnType LucReturnValue;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Get unit type */
  LucHWIPType = Eth_GaaHWIP[CtrlIdx].ucIndex;
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold the DET value */
  LucReturnValue = Eth_CommonDetCheck(ETH_SETOFFSETTIMEFORGPTP_SID, CtrlIdx);
  if (NULL_PTR == pTimeOffsetPtr)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID,
      ETH_SETOFFSETTIMEFORGPTP_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    if (ETH_MODE_ACTIVE != Eth_GaaCtrlStat[CtrlIdx].enMode)                                                             
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      /* Report Error to DET */
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SETOFFSETTIMEFORGPTP_SID, ETH_E_INV_MODE);
      #endif
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Invoke Eth_HwSetOffsetTimeForGptp to adjust gPTP with an given delta*/
      if ((NULL_PTR != Eth_GaaHwFunc[LucHWIPType]->pHwSetOffsetTimeForGptp))                                            /* PRQA S 3416 # JV-01 */
      {
      LucReturnValue = Eth_GaaHwFunc[LucHWIPType]->pHwSetOffsetTimeForGptp((uint32)CtrlIdx, pTimeOffsetPtr);
      }/* else No action required */
    }
  }
  return LucReturnValue;                                                                                                /* PRQA S 2962 # JV-01 */
}
#endif /* (ETH_AR_VERSION >= ETH_AR_431_VERSION) */
#endif /* (ETH_GLOBAL_TIME_SUPPORT == STD_ON) */

#if (ETH_STREAM_FILTERING == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_UpdateStreamFilter
**
** Service ID            : 0xA0
**
** Description           : Update the stream ID for separate filtering with the specified AVB stream receive queue.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx:     Index of the controller
**                         QueIdx :     Index of the receive queue
**                         StreamIdPtr: Update the stream id for separate filtering
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK: filter was successfully changed
**                         E_NOT_OK: filter could not be changed and the DET is ON
**
** Preconditions         : Component Requires previous controller initialization using Eth_Init.
**
** Global Variables Used : Eth_GpDriverState
**
** Function(s) invoked   : Det_ReportError, Eth_CommonDetCheck, Eth_HwCheckRxStreamQueueIndex
**                         Eth_HwUpdateStreamFilter
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_029, ETH_DUD_ACT_029_ERR001
** Reference ID          : ETH_DUD_ACT_029_ERR002, ETH_DUD_ACT_029_ERR003
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_UpdateStreamFilter(                                                           /* PRQA S 1503 # JV-01 */
  CONST(uint8, AUTOMATIC) CtrlIdx, CONST(uint8, AUTOMATIC) QueIdx,
  CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) StreamIdPtr)
{
  Std_ReturnType LucReturnValue;

  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  LucReturnValue = Eth_CommonDetCheck(ETH_UPDATESTREAMFILTER_SID, CtrlIdx);
  if (E_OK == LucReturnValue)
  {
    LucReturnValue = Eth_HwCheckRxStreamQueueIndex((uint32)CtrlIdx, (uint32)QueIdx);
    if (E_OK != LucReturnValue)
    {
      /* Report Error to DET */
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_UPDATESTREAMFILTER_SID, ETH_E_INV_PARAM);
    }
    else
    {
      /* No action required */
    }
  }
  else
  {
    /* No action required */
  }
  if (NULL_PTR == StreamIdPtr)
  {
    /* Report Error to DET */
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_UPDATESTREAMFILTER_SID, ETH_E_PARAM_POINTER);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* No action required */
  }
  if (E_OK != LucReturnValue)
  {
    /* No action required */
  }
  else
  #endif
  {
    if ((ETH_MODE_ACTIVE != Eth_GaaCtrlStat[CtrlIdx].enMode)                                                            
       && (ETH_MODE_DOWN != Eth_GaaCtrlStat[CtrlIdx].enMode))
    {
      #if (ETH_DEV_ERROR_DETECT == STD_ON)
      /* Report Error to DET, if the controller mode Is Standby */
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_UPDATESTREAMFILTER_SID, ETH_E_INV_MODE);
      #endif
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Update Filter Pattern for the specific Rx queue */
      Eth_HwUpdateStreamFilter((uint32)CtrlIdx, (uint32)QueIdx, StreamIdPtr);
      LucReturnValue = E_OK;
    }
  }
  return LucReturnValue;
}
#endif /* (ETH_STREAM_FILTERING == STD_ON) */

#if (ETH_CTRL_ENABLE_SPI_INTERFACE_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_GetSpiStatus
**
** Service ID            : 0x1E
**
** Description           : This API returns the status defined by OA TC6 to identify if an error can occured at
**                         the SPI interface
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CtrlIdx: Index of the controller
**                       : SpiStatusType : Status of the Spi status type 
**
** InOut Parameters      : None
**
** Output Parameters     : SpiStatusType
**
** Return parameter      : Std_ReturnType
**                         E_OK: success
**
** Preconditions         : Component Requires previous controller initialization using Eth_Init.
**
** Global Variables Used : Eth_GpDriverState
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_366
***********************************************************************************************************************/
FUNC(Std_ReturnType, ETH_PUBLIC_CODE) Eth_GetSpiStatus(                                                                 /* PRQA S 1503 # JV-01 */
  CONST(uint8, AUTOMATIC) CtrlIdx, P2VAR(Eth_SpiStatusType, AUTOMATIC, ETH_APPL_DATA) SpiStatusType)                    /* PRQA S 3432, 3673 # JV-01, JV-01 */
{
  (void)CtrlIdx;
  (void)SpiStatusType;
  return E_OK;
}

#endif /* (ETH_CTRL_ENABLE_SPI_INTERFACE_API == STD_ON) */

#define ETH_STOP_SEC_PUBLIC_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Eth_DemConfigCheck
**
** Service ID            : N/A
**
** Description           : Checks if the EventId is configured, and if so, reports a DemEventReport.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : EventId : Identification of an event by assigned EventId.
**                         EventStatus : Monitor test result
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : None
**
** Functions invoked     : Dem_ReportError
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_174,
** Reference ID          : ETH_DUD_ACT_174_ERR001
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_DemConfigCheck(
  CONST(Dem_EventIdType, AUTOMATIC) EventId,
  CONST(Dem_EventStatusType, AUTOMATIC) EventStatus)
{
  /* Report PASS to DEM */
  if ((Dem_EventIdType)ETH_DEM_NOT_CONFIGURED == EventId)
  {
    /* No action required */
  }
  else
  {  
    ETH_DEM_REPORT_ERROR(EventId, EventStatus);   
  }
}

/***********************************************************************************************************************
** Function Name       : Eth_SetStatus
**
** Service ID          : N/A
**
** Description         : This function updates Eth_GpDriverState.
**                       The purpose of this function is to prevent the order of
**                       instructions being changed by the compiler.
**
** Sync/Async          : Synchronous
**
** Reentrancy          : Non Reentrant
**
** Input Parameters    : LenStatus: New status value.
**                       CoreId: Code index.
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : None
**
** Global Variable     : Eth_GpDriverState
**
** Function invoked    : None
**
** Registers Used      : None
**
** Reference ID        : ETH_DUD_ACT_030, ETH_DUD_ACT_030_GBL001, ETH_DUD_ACT_030_ERR001
***********************************************************************************************************************/
STATIC FUNC(void, ETH_PRIVATE_CODE) Eth_SetStatus(
  uint8 CoreId, CONST(Eth_StateType, AUTOMATIC) LenStatus)
{
  #if (ETH_DEV_ERROR_DETECT == STD_ON)
  #if (ETH_MULTI_CORE_SUPPORT == STD_ON)
  if(ETH_INVALID_CORE == CoreId)
  {
    /* Report to DET */
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, ETH_SETSTATUS_SID, ETH_E_INVALID_CORE);
  }
  else
  #endif
  #endif
  {
    Eth_GpDriverState[CoreId] = LenStatus;                                                                              
  }
}

/***********************************************************************************************************************
** Function Name         : Eth_CommonDetCheck
**
** Service ID            : N/A
**
** Description           : This function performs DET checks which are common among almost all APIs.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LucSID:     Service ID of the caller
**                         LucCtrlIdx: Index of the controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**                         E_OK     : No error is detected
**                         E_NOT_OK : Any error is detected
**
** Preconditions         : None
**
** Global Variables      : Eth_GpDriverState, Eth_GpTotalCtrlConfig, Eth_CtrlConfigIdx, Eth_GpCoreId2Index
**
** Functions invoked     : Det_ReportError, GetCoreID
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_031, ETH_DUD_ACT_031_ERR002,
** Reference ID          : ETH_DUD_ACT_031_ERR003, ETH_DUD_ACT_031_ERR004, ETH_DUD_ACT_031_ERR005
***********************************************************************************************************************/
#if (ETH_DEV_ERROR_DETECT == STD_ON)
STATIC FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_CommonDetCheck(
  CONST(uint8, AUTOMATIC) LucSID, CONST(uint8, AUTOMATIC) LucCtrlIdx)
{
  Std_ReturnType LucReturnValue;
  Eth_StateType LenState;
  uint8 LucCoreIndex;
  #if (ETH_MULTI_CORE_SUPPORT == STD_ON)
  uint32 LulIdx;
  boolean LblValid;
  uint32 LulCtrIdx;
  uint32 LulTotalCtrlConfig;
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = Eth_GpCoreId2Index[LucCoreId];                                                                         
  #else
  /* if Multicore is not configude, defauld coreid is 0x00
     To optimize implementation */
  LucCoreIndex = ETH_ZERO;
  #endif /* End of #if (ETH_MULTI_CORE_SUPPORT == STD_ON)*/
  LucReturnValue = E_OK;

  #if (ETH_MULTI_CORE_SUPPORT == STD_ON)
  LblValid = ETH_FALSE;
  /* Check invalid core */
  if(ETH_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, LucSID, ETH_E_INVALID_CORE);
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Get total controller configured */
    LulTotalCtrlConfig = Eth_GpTotalCtrlConfig[LucCoreIndex];                                                           
    for (LulIdx = 0UL; (LulIdx < (uint32)LulTotalCtrlConfig); LulIdx++)
    {
      /* Get controller index configured */
      LulCtrIdx = Eth_CtrlConfigIdx[LucCoreIndex][LulIdx];                                                              
      if (LulCtrIdx == LucCtrlIdx)
      {
        LblValid = ETH_TRUE;
      } /* else: No action required */
    }
    if (ETH_FALSE == LblValid)
    {
      /* Report to Det with invalid controller per core */
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, LucSID, ETH_E_INVALID_CORE);
      LucReturnValue = E_NOT_OK;
    }/* else: No action required */
  }
  #endif /* End of #if (ETH_MULTI_CORE_SUPPORT == STD_ON)*/
  if (E_OK == LucReturnValue)                                                                                           /* PRQA S 2991, 2995 # JV-01, JV-01 */
  {
    LenState = Eth_GpDriverState[LucCoreIndex];                                                                         
    if (ETH_STATE_INIT != LenState)
    {
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, LucSID, ETH_E_UNINIT);
      LucReturnValue = E_NOT_OK;
    }
    else if ((uint32)ETH_TOTAL_CTRL_CONFIG <= LucCtrlIdx)                                                               /* PRQA S 2004 # JV-01 */
    {
      (void)Det_ReportError(ETH_MODULE_ID, ETH_INSTANCE_ID, LucSID, ETH_E_INV_CTRL_IDX);
      LucReturnValue = E_NOT_OK;
    }/* else: No action required */
  }/* else: No action required */
  return LucReturnValue;
}
#endif /* (ETH_DEV_ERROR_DETECT == STD_ON) */

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                             End of File                                                            **
***********************************************************************************************************************/
