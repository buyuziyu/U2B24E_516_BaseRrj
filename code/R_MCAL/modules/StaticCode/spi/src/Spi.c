/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi.c                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the implementations AUTOSAR specified APIs for SPI handler.                                     */
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
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Add new QAC msg: 2004,3415,3416 to support QAC 11.6.0
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : In Spi_SyncTransmit, Spi_AsyncTransmit: Remove pre-condition of SPI_DEV_ERROR_DETECT = ON
 *                       to check for DET report runtime error
 *                     : Update Sequence of Spi_WriteIB/Spi_ReadIB/Spi_SetupEb to fix bug: The result returns E_OK
 *                       when the channel type is invalid type in case the parameter SpiDevErrorDetect is disabled.
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 *                     : Remove support SPI_AR_431_VERSION
 * 2.1.1:  12/08/2024  : Improve to fix waring support QAC after updated "Spi_SyncTransmit" function
 *                       to correct for Sync transmission in multicore
 *                     : Update "Spi_SyncTransmit" to correct for Sync transmission in multicore
 *                     : Update Spi_Init to correct support for post build variant
 *                     : Remove QAC messages (2:0857), (2:2844), (2:2824), (2:2814), (6:2962)
 *                       to fix redundant QAC messages
 *                     : Add new QAC messages (3:2469)
 *                     : Change macro SPI_KERNEL_COREID to global variable Spi_GucKernalCoreId
 *                     : In API Spi_Init: Change Spi_GpConfigPtr->usNoOfJobs to SPI_MAX_JOB, 
 *                       Spi_GpConfigPtr->ucNoOfSequences to SPI_MAX_SEQUENCE, 
 *                       Spi_GpConfigPtr->ucNoOfChannels to SPI_MAX_CHANNEL, Spi_GpConfigPtr->ucNoOfHWUnits
 *                     : Update API Spi_GetHWUnitStatus to support for post build variant
 *                     : Update Spi_Init to get the kernel core Id from input Spi_Config
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  23/10/2023  : Remove SPI_AR_R21_11_VERSION.
 *         22/10/2023  : Improve to fix waring support QAC Amendment 2.
 *         11/10/2023  : Update SPI_AR_R22_11_VERSION.
 *                       Update SW-VERSION to 2.0.1.
 *                       Update pre-condition SPI_AR_VERSION == SPI_AR_R22_11_VERSION for 
 *                       SPI_LEVEL_DELIVERED == SPI_LEVEL_1 in function Spi_AsyncTransmit, Spi_SyncTransmit, 
 *                       Spi_MainFunction_Handling, Spi_Cancel, Spi_ForceCancel.
 *                       Correct condition Report to DET in Spi_AsyncTransmit: change from OR to AND condition
 *                       Update the order of DET error check for SPI_E_UNINIT in Spi_DeInit, Spi_SetAsyncMode to
 *                       support new requirement SWS_BSW_00243.
 * 2.0.0:  23/08/2023  : Update return value for DET error
 *         25/07/2023  : - Update from "Spi_Mapping.h to "Spi_MemMap.h".
 *                       - Add #include "Spi_Kernel.h" and "Os.h" to support Multicore 
 *                       - Update Exclusive_Area of SPI_ENTER_CRITICAL_SECTION/SPI_EXIT_CRITICAL_SECTION
 *                       - Change from SPI_START/END_SEC_PUBLIC_CODE to SPI_START/END_SEC_PUBLIC_CODE_LOCAL/GLOBAL
 *                       - Add DET error check for SPI_E_INVALID_CORE in Spi_Init, Spi_DeInit, Spi_WriteIB,
 *                       Spi_AsyncTransmit, Spi_ReadIB, Spi_SetupEB, Spi_GetJobResult, Spi_GetSequenceResult,
 *                       Spi_SyncTransmit, Spi_GetHWUnitStatus, Spi_Cancel, Spi_SetAsyncMode, Spi_ForceCancel.
 *                       - Add Spi_LockProcess/Spi_UnLockProcess process and DET error check for SPI_E_REQUEST_FALSE
 *                       in Spi_Cancel, Spi_ForceCancel.
 *         17/07/2023  : Update pre-condition SPI_AR_VERSION == SPI_AR_R21_11_VERSION for 
 *                       SPI_LEVEL_DELIVERED == SPI_LEVEL_1 in function Spi_Init, Spi_MainFunction_Handling
*          19/06/2023  : Change marco SPI_ACTIVE_HW_BITS to SPI_SYNC_HW_BITS in function Spi_SyncTransmit
 *         26/05/2023  : Change SPI_AR_2111_VERSION to SPI_AR_R21_11_VERSION
 *         12/05/2023  : Update 
 *                       Spi_SyncTransmit: change Asynchronous to Synchronous
 *                       Spi_MemCopy: correct Input Parameters and Output Parameters 
 *         07/04/2023  : Update precondition of Spi_SetAsyncMode function
 *         06/05/2023  : Update SPI_AR_2111_VERSION
 * 1.5.0:  07/04/2023  : Update
 *                       Spi_GetVersionInfo: Add versioninfo into Input Parameters
 *                       Spi_SyncTransmit: Remove 1 redundant Spi_GpFirstSeq in Global Variable field.
 *                       Spi_ForceCancel: Change from Sequence to LucSequence in Input Parameters
 * 1.4.3:  12/05/2022  : Mapping SPI_DUD_ACT_014_ERR002 to Spi_SetAsyncMode
 *         10/05/2022  : Remove if, else do nothing
 *                       Add QAC message
 * 1.3.3:  09/05/2022  : Update function Spi_SetAsyncMode to checking invalid mode
 * 1.3.2:  04/09/2021  : Replace the inclusion of Spi_MemMap.h with Spi_Mapping.h
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END) 
 *         19/05/2021  : Update QAC contents.
 *         07/05/2021  : Move pre-condition of SPI_LEVEL_2 inside function Spi_MainFunction_Handling.
 * 1.2.0:  30/07/2020  : Release
 *                       Add sequence checking before starting new transmission.
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.1:  16/06/2020  : Remove the HW Unit activation from Spi_AsyncTransmit
 * 1.0.0:  09/06/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Spi.h"
#include "Spi_Ram.h"

/* Included for the declaration of Det_ReportError() and Det_ReportRuntimeError */
#include "Det.h"

#if (SPI_MULTI_CORE_SUPPORT == STD_ON)
#include "Spi_Kernel.h"
#include "Os.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define SPI_C_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION_VALUE
#define SPI_C_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION_VALUE
#define SPI_C_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define SPI_C_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION_VALUE
#define SPI_C_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (SPI_AR_RELEASE_MAJOR_VERSION != SPI_C_AR_RELEASE_MAJOR_VERSION)
#error "Spi.c : Mismatch in Release Major Version"
#endif

#if (SPI_AR_RELEASE_MINOR_VERSION != SPI_C_AR_RELEASE_MINOR_VERSION)
#error "Spi.c : Mismatch in Release Minor Version"
#endif

#if (SPI_AR_RELEASE_REVISION_VERSION != SPI_C_AR_RELEASE_REVISION_VERSION)
#error "Spi.c : Mismatch in Release Revision Version"
#endif

#if (SPI_SW_MAJOR_VERSION != SPI_C_SW_MAJOR_VERSION)
#error "Spi.c : Mismatch in Software Major Version"
#endif

#if (SPI_SW_MINOR_VERSION != SPI_C_SW_MINOR_VERSION)
#error "Spi.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Dir-4.1, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there. (Other uses of  */
/*                       the macro may not necessarily be suitable for replacement.)                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : '%s' has external linkage and is being defined without any previous declaration.             */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : CERTCCM EXP11, EXP39, MISRA C:2012 Rule-11.3, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588    */
/*                       CWE-465, CWE-569, CWE-737                                                                    */
/* JV-01 Justification : For accessing 8-bit and 16-bit PNOT and JPNOT register respectively, the 32-bit pointer is   */
/*                       typecasted.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:3305)    : Pointer cast to stricter alignment.                                                          */
/* Rule                : CERTCCM EXP36, EXP39, MISRA C:2012 Rule-11.3, CWE Rule CWE-188, CWE-737                      */
/* JV-01 Justification : Pointer alignment is changed by casting, but it's necessary for embedded programming         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : CERTCCM EXP02, MISRA C:2012 Rule-15.7, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else"statement with empty content is removed to improve readability.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with possible side effects.              */
/* Rule                : CERTCCM EXP02, MISRA C:2012 Rule-13.5, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it is not a direct access to the HW register, and          */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4461)    : A non-constant expression of 'essentially unsigned' type (%1s) is being converted to         */
/*                       narrower unsigned type, '%2s' on assignment.                                                 */
/* Rule                : CERTCCM INT02, MISRA C:2012 Rule-10.3                                                        */
/* JV-01 Justification : This operation is necessary to offset a 32-bit address on RAM to a 16-bit buffer address.    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : CERTCCM EXP10, EXP30, MISRA C:2012 Rule-1.3, Rule-13.2, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get element in array of struct, volatile of counter variable of 'for' loop is     */
/*                       used to ensure no optimization. It is accepted                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : This arithmetic expression adds or multiplies values cast to uint32 from types smaller than  */
/*                       uint32, so it never exceeds the maximum value of uint32. Therefore, no wraparound guard is   */
/*                       required.                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3387)    : A full expression containing an increment (++) or decrement (--) operator should have no     */
/*                       potential side effects other than that caused by the increment or decrement operator.        */
/* Rule                : MISRA C:2012 Rule-13.3                                                                       */
/*                       REFERENCE - ISO:C90-5.1.2.3 Program Execution                                                */
/* JV-01 Justification : This increment/decrement is done to the struct members of the volatile object. However, it   */
/*                       is for RAM data that has no side effects, and is protected by a critical section, so it is   */
/*                       acceptable.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2469)    : Loop control variable in this 'for' statement LucHWUnitIndex is modified in the body of the  */
/*                       loop.                                                                                        */
/* Rule                : MISRA C:2012 Rule-14.2                                                                       */
/* JV-01 Justification : This is to exit from the linear search loop when the required channel Id is found.           */
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

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define SPI_START_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"

/* The prototype of function which is used in this file only */
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_SetStatus(const boolean LblStatus);
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MemCopy(CONSTP2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig,
                volatile CONSTP2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) LpDesPtr,                             /* PRQA S 3432 # JV-01 */
                volatile CONSTP2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) LpSrcPtr);
#endif

#define SPI_STOP_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define SPI_START_SEC_PUBLIC_CODE_LOCAL
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name       : Spi_Init
**
** Service ID          : 0x00
**
** Description         : This service performs initialization of the SPI Driver component
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Non-Reentrant
**
** Input Parameters    : ConfigPtr - Pointer to the configuration
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : None
**
** Global Variable     : Spi_GblInitialized, Spi_GpConfigPtr, Spi_GpFirstChannel, Spi_GpFirstJob, Spi_GpFirstSeq,
**                       Spi_GpFirstHWUnit, Spi_GpFirstDMAUnit, Spi_GpHwConfig, Spi_GenAsyncMode, Spi_GulActiveHWUnits,
**                       Spi_GulAllQueueSts, Spi_GaaQueue, Spi_GaaActiveSequence, Spi_GaaHWStatus, Spi_GaaJobStatus,
**                       Spi_GaaSeqStatus, Spi_GaaChannelBuffer, Spi_GulCancelingHWUnits, Spi_GaaAsyncTransmitInfo,
**                       Spi_GaaSyncTransmitInfo, Spi_GaaCancelTransmitInfo, Spi_GaaForceCancelTransmitInfo
**                       Spi_GucKernalCoreId
**
** Function Invoked    : Det_ReportError, Spi_SetStatus, Spi_MemCopy, Spi_CSIXInit, Spi_HSPIInit, Spi_MSPIInit,
**                       Spi_DMAInit
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_001, SPI_DUD_ACT_001_ERR001, SPI_DUD_ACT_001_ERR002, SPI_DUD_ACT_001_ERR003,
** Reference ID        : SPI_DUD_ACT_001_ERR004
** Reference ID        : SPI_DUD_ACT_001_GBL001, SPI_DUD_ACT_001_GBL002, SPI_DUD_ACT_001_GBL003, SPI_DUD_ACT_001_GBL004,
** Reference ID        : SPI_DUD_ACT_001_GBL005, SPI_DUD_ACT_001_GBL006, SPI_DUD_ACT_001_GBL007, SPI_DUD_ACT_001_GBL008,
** Reference ID        : SPI_DUD_ACT_001_GBL009, SPI_DUD_ACT_001_GBL010, SPI_DUD_ACT_001_GBL011, SPI_DUD_ACT_001_GBL012,
** Reference ID        : SPI_DUD_ACT_001_GBL013, SPI_DUD_ACT_001_GBL014, SPI_DUD_ACT_001_GBL015, SPI_DUD_ACT_001_GBL016,
** Reference ID        : SPI_DUD_ACT_001_GBL017, SPI_DUD_ACT_001_GBL018, SPI_DUD_ACT_001_GBL019, SPI_DUD_ACT_001_GBL020
** Reference ID        : SPI_DUD_ACT_001_GBL021
***********************************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_Init(P2CONST(Spi_ConfigType, AUTOMATIC, SPI_APPL_CONST) ConfigPtr)                      /* PRQA S 1503 # JV-01 */
{
  P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig;
  uint32 LulNumJobs;
  uint32 LulNumSeq;
  uint32 LulNumChannel;
  uint32 LulIndex;
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  uint32 LulSubIndex;
  uint32 LulPriorityIndex;
  #endif
  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  volatile uint8 LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */
  #endif
  #if (SPI_ALREADY_INIT_DET_CHECK == STD_ON)
  /* Check if SPI Driver already initialized */
  if (SPI_FALSE != Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_INIT_SID, SPI_E_ALREADY_INITIALIZED);
  }
  else
  #endif /* (SPI_ALREADY_INIT_DET_CHECK == STD_ON) */
  /* Check if SPI configuration pointer is a NULL Pointer */
  if (NULL_PTR == ConfigPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_INIT_SID, SPI_E_PARAM_POINTER);
  }
  /* Initialize the module only if Database is present */
  else if (SPI_DBTOC_VALUE != ConfigPtr->ulStartOfDbToc)
  {
    /* Report to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_INIT_SID, SPI_E_INVALID_DATABASE);
  }
  else
  #endif /* (SPI_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
    /* Holds the kernal core ID in multicore */
    Spi_GucKernalCoreId = ConfigPtr->ucKernelCoreId;
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if control API wasn't executed on Master Core */
    if (Spi_GucKernalCoreId != LucCoreID)                                                                               /* PRQA S 3416 # JV-01 */
    {
      /* Report Error to DET */
      (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_INIT_SID, SPI_E_INVALID_CORE);
    } /* else No action required */
    else
    #endif /* #if (SPI_DEV_ERROR_DETECT == STD_ON) */
    #endif /* #if (SPI_MULTI_CORE_SUPPORT == STD_ON) */
    {
      /* Load ConfigPtr to Global pointer variable  */
      Spi_GpConfigPtr = ConfigPtr;

      /* Get the pointer to  Channel configuration table */
      Spi_GpFirstChannel =
          (P2CONST(Spi_ChannelConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA))Spi_GpConfigPtr->pChannelConfig;            /* PRQA S 0316 # JV-01 */

      /* Get the pointer to Job configuration table */
      Spi_GpFirstJob = (P2CONST(Spi_JobConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA))Spi_GpConfigPtr->pJobConfig;       /* PRQA S 0316 # JV-01 */

      /* Get the pointer to Sequence configuration table */
      Spi_GpFirstSeq = (P2CONST(Spi_SeqConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA))Spi_GpConfigPtr->pSequenceConfig;  /* PRQA S 0316 # JV-01 */

      /* Get the pointer to SPI HWUnit configuration table */
      Spi_GpFirstHWUnit = (P2CONST(Spi_HWUnitInfoType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA))Spi_GpConfigPtr->pHWUnitInfo;  /* PRQA S 0316 # JV-01 */

      #if (SPI_DMA_CONFIGURED == STD_ON)
      /* Get the pointer to DMA HWUnit configuration table */
      Spi_GpFirstDMAUnit = (P2CONST(Spi_DmaConfigType, SPI_VAR_NO_INIT, SPI_CONFIG_DATA))Spi_GpConfigPtr->pDMAUnitInfo; /* PRQA S 0316 # JV-01 */
      #endif /* (SPI_DMA_CONFIGURED == STD_ON) */

      Spi_GpHwConfig = (P2CONST(Spi_HwConfigType, SPI_VAR_NO_INIT, SPI_CONST))Spi_GpConfigPtr->pHwConfig;               /* PRQA S 0316 # JV-01 */

      #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)
      /* Global variable for asynchronous mode is polling mode */
      Spi_GenAsyncMode = SPI_POLLING_MODE;
      #endif

      /* Global variable for active HW unit indexes used by a request transmission */
      Spi_GulActiveHWUnits = 0U;

      #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
      /* Initialize Queues */
      Spi_GulAllQueueSts = 0U;
      for (LulIndex = 0U; (uint32)SPI_MAX_QUEUE > LulIndex; LulIndex++)                                                 /* PRQA S 2877 # JV-01 */
      {
        Spi_GaaQueue[LulIndex].ucExists = 0U;
        Spi_GaaQueue[LulIndex].ucOngoingSeqIndex = SPI_INVALID_SEQUENCE;
        /* The following variable must be written before the first reading, but initialize with zero just in case */
        for (LulPriorityIndex = 0U; LulPriorityIndex < ((uint32)SPI_MAX_PRIORITY + 1UL); LulPriorityIndex++)
        {
          Spi_GaaQueue[LulIndex].aaTop[LulPriorityIndex] = 0U;
          Spi_GaaQueue[LulIndex].aaTail[LulPriorityIndex] = 0U;
        }
      }

      for (LulIndex = 0U; SPI_BITS_TO_WORDS(SPI_MAX_SEQUENCE) > LulIndex; LulIndex++)                                   /* PRQA S 3469, 2877 # JV-01, JV-01 */
      {
        Spi_GaaActiveSequence[LulIndex] = 0U;
      }
      #endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

      /* Initialize HW status */
      for (LulIndex = 0U; LulIndex < SPI_MAX_HWUNIT; LulIndex++)
      {
        #if (SPI_HW_STATUS_API == STD_ON)
        Spi_GaaHWStatus[LulIndex].blActive = SPI_FALSE;
        #endif
        /* The following variable must be written before the first reading, but initialize with zero just in case */
        Spi_GaaHWStatus[LulIndex].ucOngoingSeqIndex = 0U;
        Spi_GaaHWStatus[LulIndex].usOngoingJobIndex = 0U;
        Spi_GaaHWStatus[LulIndex].ucTxChannelCount = 0U;
        Spi_GaaHWStatus[LulIndex].ucRxChannelCount = 0U;
        Spi_GaaHWStatus[LulIndex].usRemainedTxCount = 0U;
        Spi_GaaHWStatus[LulIndex].usRemainedRxCount = 0U;
        Spi_GaaHWStatus[LulIndex].pTxPtr = NULL_PTR;
        Spi_GaaHWStatus[LulIndex].pRxPtr = NULL_PTR;
      }

      /* Initialize Job results */
      for (LulNumJobs = 0U; SPI_MAX_JOB > LulNumJobs; LulNumJobs++)
      {
        Spi_GaaJobStatus[LulNumJobs].enResult = SPI_JOB_OK;
      }

      /* Initialize Sequence results */
      for (LulNumSeq = 0U; SPI_MAX_SEQUENCE > LulNumSeq; LulNumSeq++)
      {
        Spi_GaaSeqStatus[LulNumSeq].enResult = SPI_SEQ_OK;
        /* The following variable must be written before the first reading, but initialize with zero just in case */
        #if (SPI_LEVEL_DELIVERED != SPI_LEVEL_0)
        #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
        Spi_GaaSeqStatus[LulNumSeq].ulActiveSubSequences = 0UL;
        #endif
        for (LulSubIndex = 0U; LulSubIndex < (uint32)SPI_MAX_QUEUE; LulSubIndex++)                                      /* PRQA S 2877 # JV-01 */
        {
          Spi_GaaSeqStatus[LulNumSeq].aaSubSeqs[LulSubIndex].usRemainJobCount = 0U;
          for (LulPriorityIndex = 0U; LulPriorityIndex < ((uint32)SPI_MAX_PRIORITY + 1UL); LulPriorityIndex++)
          {
            Spi_GaaSeqStatus[LulNumSeq].aaSubSeqs[LulSubIndex].aaPrev[LulPriorityIndex] = 0U;
            Spi_GaaSeqStatus[LulNumSeq].aaSubSeqs[LulSubIndex].aaNext[LulPriorityIndex] = 0U;
          }
        }
        #endif /* (SPI_LEVEL_DELIVERED != SPI_LEVEL_0) */
        #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
        #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
        Spi_GaaAsyncTransmitInfo[LulNumSeq].blSetRequest = SPI_FALSE;
        #endif
        #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
        Spi_GaaSyncTransmitInfo[LulNumSeq].blSetRequest = SPI_FALSE;
        Spi_GaaSyncTransmitInfo[LulNumSeq].ucResult = E_NOT_OK;
        #endif
        #if (SPI_CANCEL_API == STD_ON)
        Spi_GaaCancelTransmitInfo[LulNumSeq].blSetRequest = SPI_FALSE;
        Spi_GaaCancelTransmitInfo[LulNumSeq].blBufferLock = SPI_FALSE;
        #endif
        #if (SPI_FORCE_CANCEL_API == STD_ON)
        Spi_GaaForceCancelTransmitInfo[LulNumSeq].blSetRequest = SPI_FALSE;
        Spi_GaaForceCancelTransmitInfo[LulNumSeq].blBufferLock = SPI_FALSE;
        #endif
        #endif
      }

      /* Initialize entire internal buffer */
      #if (SPI_MAX_CHANNEL_BUFFER_SIZE > 0U)
      for (LulIndex = 0U; LulIndex < ((uint32)SPI_MAX_CHANNEL_BUFFER_SIZE / (uint32)sizeof(uint32)); LulIndex++)
      {
        Spi_GaaChannelBuffer[LulIndex] = 0UL;
      }
      #endif

      /* Initialize SPI HW, specific global variables used for each HW IP */
      for (LulIndex = 0UL; LulIndex < SPI_MAX_MACRO; LulIndex++)                                                        /* PRQA S 2877 # JV-01 */
      {
        Spi_GpHwConfig[LulIndex].pHwDepFunc->pHwInit();
      }

      /* Initialize DMA if it is configured */
      #if (SPI_DMA_CONFIGURED == STD_ON)
      Spi_DMAInit();
      #endif

      /* Initialize each Channel buffers */
      for (LulNumChannel = 0U; Spi_GpConfigPtr->ucNoOfChannels > LulNumChannel; LulNumChannel++)                        /* PRQA S 3416 # JV-01 */
      {
        LpChConfig = &Spi_GpFirstChannel[LulNumChannel];
        if (SPI_BUFFER_TYPE_EB == LpChConfig->enChannelBufferType)
        {
          #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_EB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
          /* When EB, initialize user pointers as NULL */
          LpChConfig->pEBData->usEBLength = (LpChConfig->usNoOfBuffers);
          LpChConfig->pEBData->pSrcPtr = NULL_PTR;
          LpChConfig->pEBData->pDestPtr = NULL_PTR;
          #endif
        }
        else
        {
          #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
          /* When IB, initialize buffer with default data */
          Spi_MemCopy(LpChConfig, LpChConfig->pTxBuffer, NULL_PTR);
          #endif
        }
      }

      #if (((SPI_LEVEL_DELIVERED == SPI_LEVEL_2) ||(SPI_LEVEL_DELIVERED == SPI_LEVEL_1)) && \
      (SPI_FORCE_CANCEL_API == STD_ON))
      /* HWUnits under processing by Spi_ForceCancel */
      Spi_GulCancelingHWUnits = 0UL;
      #endif

      /* Set Initialized flag */
      Spi_SetStatus(SPI_TRUE);
    }
  }
}

/***********************************************************************************************************************
** Function Name       : Spi_DeInit
**
** Service ID          : 0x01
**
** Description         : This service is used for de-initialization of this module.
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Non-Reentrant
**
** Input Parameters    : None
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : Std_ReturnType (E_OK/E_NOT_OK)
**
** Preconditions       : Spi_Init must have been invoked
**
** Global Variable     : Spi_GblInitialized, Spi_GulActiveHWUnits, Spi_GpHwConfig, Spi_GucKernalCoreId
**
** Function invoked    : Det_ReportError, Spi_SetStatus, Spi_MSPIDeInit, Spi_CSIXDeInit, Spi_HSPIDeInit, Spi_DMADeInit
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_002, SPI_DUD_ACT_002_ERR001, SPI_DUD_ACT_002_GBL001, SPI_DUD_ACT_002_ERR002
***********************************************************************************************************************/
FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_DeInit(void)                                                                  /* PRQA S 1503 # JV-01 */
{
  uint32 LulIndex;
  Std_ReturnType LucReturnValue;

  #if (SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  volatile uint8 LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */
  #endif
  
  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  /* Check if SPI Driver is initialized */
  if (SPI_FALSE == Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_DEINIT_SID, SPI_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  }
  else
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)  
  /* Check if control API wasn't executed on Master Core */
  if (Spi_GucKernalCoreId != LucCoreID)                                                                                 /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_DEINIT_SID, SPI_E_INVALID_CORE);
    LucReturnValue = E_NOT_OK;
  } /* else No action required */
  else
  #endif
  #endif /* (SPI_DEV_ERROR_DETECT == STD_ON) */
  /* Check if there is no HW unit activated */
  if (0UL == Spi_GulActiveHWUnits)                                                                                      /* PRQA S 3416 # JV-01 */
  {
    /* Update the SPI driver status as uninitialized */
    Spi_SetStatus(SPI_FALSE);

    /* DeInit HWs */
    for (LulIndex = 0UL; LulIndex < SPI_MAX_MACRO; LulIndex++)                                                          /* PRQA S 2877 # JV-01 */
    {
      Spi_GpHwConfig[LulIndex].pHwDepFunc->pHwDeInit();
    }
    #if (SPI_DMA_CONFIGURED == STD_ON)
    Spi_DMADeInit();
    #endif /* (SPI_DMA_CONFIGURED == STD_ON) */

    LucReturnValue = E_OK;
  }
  else
  {
    LucReturnValue = E_NOT_OK;
  }

  /* Return the value */
  return (LucReturnValue);
}

#define SPI_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define SPI_START_SEC_PUBLIC_CODE_GLOBAL
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name       : Spi_WriteIB
**
** Service ID          : 0x02
**
** Description         : This service for writing one or more data to an IB SPI Handler/Driver channel specified by
**                       parameter.
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant
**
** Input Parameters    : Channel - Channel ID
**                       DataBufferPtr - Pointer to source data buffer
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : Std_ReturnType (E_OK/E_NOT_OK)
**
** Preconditions       : Spi_Init must have been invoked.
**
** Global Variable     : Spi_GblInitialized, Spi_GpConfigPtr, Spi_GpFirstChannel
**
** Function invoked    : Det_ReportError, Spi_MemCopy, SPI_ENTER_CRITICAL_SECTION, SPI_EXIT_CRITICAL_SECTION
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_003, SPI_DUD_ACT_003_ERR001, SPI_DUD_ACT_003_ERR002, SPI_DUD_ACT_003_ERR003, 
** Reference ID        : SPI_DUD_ACT_003_ERR004, SPI_DUD_ACT_003_CRT001, SPI_DUD_ACT_003_CRT002
***********************************************************************************************************************/
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
FUNC(Std_ReturnType, SPI_PUBLIC_CODE)
Spi_WriteIB(Spi_ChannelType Channel, P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_CONST) DataBufferPtr)              /* PRQA S 1503 # JV-01 */
{
  P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig;
  Std_ReturnType LucReturnValue;
  #if (SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  volatile uint8 LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = SPI_ONE << (uint8)GetCoreID();
  #endif /* (SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON) */
  /* Initialize return value as E_OK */
  LucReturnValue = E_OK;
  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  /* Check if SPI Driver is initialized */
  if (SPI_FALSE == Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_WRITEIB_SID, SPI_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  }
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  else if ((Spi_GpFirstChannel[Channel].ucCoreMask & LucCoreID) != LucCoreID)                                           /* PRQA S 3416, 0404, 2004 # JV-01, JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_WRITEIB_SID, SPI_E_INVALID_CORE);
    LucReturnValue = E_NOT_OK;

  }
  #endif /* End of (SPI_MULTI_CORE_SUPPORT == STD_ON) */
  #endif /* End of (SPI_DEV_ERROR_DETECT == STD_ON) */
  /* Check if any DET error reported */
  if (E_OK == LucReturnValue)                                                                                           /* PRQA S 2991, 2995 # JV-01, JV-01 */
  {
    if (Spi_GpConfigPtr->ucNoOfChannels <= Channel)                                                                     /* PRQA S 3416 # JV-01 */
    {
      #if (SPI_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_WRITEIB_SID, SPI_E_PARAM_CHANNEL);
      #endif /* End of (SPI_DEV_ERROR_DETECT == STD_ON) */
      LucReturnValue = E_NOT_OK;
    }
    #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
    /* Check if the channel is configured with external buffer */
    else if (SPI_BUFFER_TYPE_EB == Spi_GpFirstChannel[Channel].enChannelBufferType)                                     /* PRQA S 3416 # JV-01 */
    {
      #if (SPI_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_WRITEIB_SID, SPI_E_PARAM_CHANNEL);
      #endif /* End of (SPI_DEV_ERROR_DETECT == STD_ON) */
      LucReturnValue = E_NOT_OK;
    }
    #endif /* (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB) */
    else if (SPI_BUFFER_TYPE_IB == Spi_GpFirstChannel[Channel].enChannelBufferType)                                     /* PRQA S 2004, 3416 # JV-01, JV-01 */
    {
      /* Copy operation */
      LpChConfig = &Spi_GpFirstChannel[Channel];
      SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
      Spi_MemCopy(LpChConfig, LpChConfig->pTxBuffer, DataBufferPtr);
      SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
    }
  }
  return (LucReturnValue);
}
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)) */

/***********************************************************************************************************************
** Function Name       : Spi_AsyncTransmit
**
** Service ID          : 0x03
**
** Description         : This service for transmitting data asynchronously
**
** Sync/Async          : Asynchronous.
**
** Re-entrancy         : Re-entrant for different Sequence, Non Re-entrant for same Sequence
**
** Input Parameters    : Sequence - Sequence ID
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : Std_ReturnType (E_OK/E_NOT_OK)
**
** Preconditions       : Spi_Init must have been invoked.
**
** Global Variable     : Spi_GblInitialized, Spi_GpConfigPtr, Spi_GpFirstSeq, Spi_GulActiveHWUnits, Spi_GaaSeqStatus,
**                       Spi_GaaActiveSequence, Spi_GaaAsyncTransmitInfo
**
** Function invoked    : Det_ReportError, SPI_DET_REPORT_RUNTIME_ERROR, Spi_StartTransmission,
**                       SPI_ENTER_CRITICAL_SECTION, SPI_EXIT_CRITICAL_SECTION
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_004, SPI_DUD_ACT_004_CRT001, SPI_DUD_ACT_004_CRT002, SPI_DUD_ACT_004_ERR001,
** Reference ID        : SPI_DUD_ACT_004_ERR002, SPI_DUD_ACT_004_ERR003, SPI_DUD_ACT_004_ERR004, SPI_DUD_ACT_004_GBL001,
** Reference ID        : SPI_DUD_ACT_004_GBL002, SPI_DUD_ACT_004_GBL005, SPI_DUD_ACT_004_GBL004, SPI_DUD_ACT_004_GBL006,
** Reference ID        : SPI_DUD_ACT_004_CRT003, SPI_DUD_ACT_004_CRT004
***********************************************************************************************************************/
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_AsyncTransmit(Spi_SequenceType Sequence)                                      /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LucReturnValue;
  uint32 LulCount;
  #if (SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  volatile uint8 LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = SPI_ONE << (uint8)GetCoreID();
  #endif
  LucReturnValue = E_OK;

  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  /* Check if SPI Driver is initialized */
  if (SPI_FALSE == Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ASYNCTRANSMIT_SID, SPI_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  }
  /* Check if the Sequence ID passed, is valid */
  else if (Spi_GpConfigPtr->ucNoOfSequences <= Sequence)                                                                /* PRQA S 3416, 2004 # JV-01, JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ASYNCTRANSMIT_SID, SPI_E_PARAM_SEQ);
    LucReturnValue = E_NOT_OK;
  }
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  else if ((Spi_GpFirstSeq[Sequence].ucCoreMask & LucCoreID) != LucCoreID)                                              /* PRQA S 3416, 0404, 2004 # JV-01, JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ASYNCTRANSMIT_SID, SPI_E_INVALID_CORE);
    LucReturnValue = E_NOT_OK;
  }
  #endif
  #if ((SPI_AR_VERSION == SPI_AR_422_VERSION) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  /*
   * Check if the HW Unit of the job is configured for synchronous transmission
   */
  else if (SPI_TRUE == Spi_GpFirstSeq[Sequence].blSynchronous)
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ASYNCTRANSMIT_SID, SPI_E_PARAM_SEQ);
    LucReturnValue = E_NOT_OK;
  }
  #endif /* ((SPI_AR_VERSION == SPI_AR_422_VERSION) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

  /* Check if not any DET error reported */
  if (E_NOT_OK != LucReturnValue)
  #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
  {
    /* Critical section required for re-entrancy of this API */
    SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
    #if ((SPI_AR_VERSION == SPI_AR_R22_11_VERSION) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
    /* Check if sequence is already used for sync transmission */
    if (0UL != (Spi_GulActiveHWUnits & Spi_GpFirstSeq[Sequence].ulUsingHWUnits))                                        /* PRQA S 3416, 0404 # JV-01, JV-01 */
    {
      /* This function shall return with value E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else /* Check if sequence is already used for async transmission */
    #endif /* ((SPI_AR_VERSION == SPI_AR_R22_11_VERSION) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

    /* Check if the requested sequence already pending */
    if (SPI_SEQ_PENDING == Spi_GaaSeqStatus[Sequence].enResult)
    {
      /* This function shall return with value E_NOT_OK */
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      for (LulCount = 0U; LulCount < SPI_BITS_TO_WORDS(SPI_MAX_SEQUENCE); LulCount++)                                   /* PRQA S 3469, 2877 # JV-01, JV-01 */
      {
        if (0UL != (Spi_GaaActiveSequence[LulCount] & Spi_GpFirstSeq[Sequence].aaJobSharedSequences[LulCount]))         /* PRQA S 3416, 0404 # JV-01, JV-01 */
        {
          LucReturnValue = E_NOT_OK;
        } /* else No action required */
      }

      /* If OK, set active flag for this Sequence */
      if (E_OK == LucReturnValue)
      {
        /* Set active sequence bit for check shared job in a sub-sequence */
        Spi_GaaActiveSequence[(uint32)Sequence / (uint32)SPI_UINT32_BITS] |=
            (1UL << ((uint32)Sequence & (uint32)(SPI_UINT32_BITS - 1U)));
        /* Set sequence status as pending */
        Spi_GaaSeqStatus[Sequence].enResult = SPI_SEQ_PENDING;
        #if (SPI_CANCEL_API == STD_ON)
        /* Initialize cancel request flag by Spi_Cancel */
        Spi_GaaSeqStatus[Sequence].blCancelRequested = SPI_FALSE;
        #endif
        #if ((SPI_CANCEL_API == STD_ON) || (SPI_FORCE_CANCEL_API == STD_ON))
        /* Initialize already canceled flag for Spi_Cancel or Spi_ForceCancel */
        Spi_GaaSeqStatus[Sequence].blCanceled = SPI_FALSE;
        #endif
      } /* else No action required */
    }
    SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);

    /* Report to DET on the outside of critical section */
    if (E_NOT_OK == LucReturnValue)
    {
      /* Report to DET */
      SPI_DET_REPORT_RUNTIME_ERROR(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ASYNCTRANSMIT_SID, SPI_E_SEQ_PENDING);
    }
    else
    {
      #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
      SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
      /* Request is issued */
      Spi_GaaAsyncTransmitInfo[Sequence].blSetRequest = SPI_TRUE;
      SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
      #else
      /* Transmission */
      Spi_StartTransmission((uint32)Sequence);
      #endif
    }
  }

  return (LucReturnValue);
}
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

/***********************************************************************************************************************
** Function Name       : Spi_ReadIB
**
** Service ID          : 0x04
**
** Description         : This service for reading one or more data from an IB SPI Handler/Driver channel specified by
**                       parameter
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Re-entrant for different Channel, Non Re-entrant for same Channel
**
** Input Parameters    : Channel - Channel ID                  
**
** InOut Parameters    : None
**
** Output Parameters   : DataBufferPointer - Pointer to destination data buffer
**
** Return parameter    : Std_ReturnType (E_OK/E_NOT_OK)
**
** Preconditions       : Spi_Init must have been invoked.
**
** Global Variable     : Spi_GblInitialized, Spi_GpConfigPtr, Spi_GpFirstChannel
**
** Function invoked    : Det_ReportError, Spi_MemCopy
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_005, SPI_DUD_ACT_005_ERR001, SPI_DUD_ACT_005_ERR002, SPI_DUD_ACT_005_ERR003,
** Reference ID        : SPI_DUD_ACT_005_ERR004, SPI_DUD_ACT_005_ERR005
***********************************************************************************************************************/
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
FUNC(Std_ReturnType, SPI_PUBLIC_CODE)
Spi_ReadIB(Spi_ChannelType Channel, P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DataBufferPointer)              /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
  P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig;
  Std_ReturnType LucReturnValue;
  #if (SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  volatile uint8 LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = SPI_ONE << (uint8)GetCoreID();
  #endif /* (SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON) */
  /* Initialize return value as E_OK */
  LucReturnValue = E_OK;
  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  /* Check if SPI Driver is initialized */
  if (SPI_FALSE == Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_READIB_SID, SPI_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  }
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  else if ((Spi_GpFirstChannel[Channel].ucCoreMask & LucCoreID) != LucCoreID)                                           /* PRQA S 3416, 0404, 2004 # JV-01, JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_READIB_SID, SPI_E_INVALID_CORE);
    LucReturnValue = E_NOT_OK;
  }  /* else No action required */
  #endif /* End of (SPI_MULTI_CORE_SUPPORT == STD_ON) */
  #endif /* End of (SPI_DEV_ERROR_DETECT == STD_ON) */
  /* Check if any DET error reported */
  if (E_OK == LucReturnValue)                                                                                           /* PRQA S 2991, 2995 # JV-01, JV-01 */
  {
    /* Check if the channel ID passed, is valid */
    if (Spi_GpConfigPtr->ucNoOfChannels <= Channel)                                                                     /* PRQA S 3416 # JV-01 */
    {
      #if (SPI_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_READIB_SID, SPI_E_PARAM_CHANNEL);
      #endif /* End of (SPI_DEV_ERROR_DETECT == STD_ON) */
      LucReturnValue = E_NOT_OK;
    }
    /* Check if the data buffer pointer passed, is NULL pointer */
    else if (NULL_PTR == DataBufferPointer)
    {
      #if (SPI_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_READIB_SID, SPI_E_PARAM_POINTER);
      #endif /* End of (SPI_DEV_ERROR_DETECT == STD_ON) */
      LucReturnValue = E_NOT_OK;
    }
    #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
    /* Check if the channel is configured with external buffer */
    else if (SPI_BUFFER_TYPE_EB == (Spi_GpFirstChannel[Channel].enChannelBufferType))                                   /* PRQA S 3416 # JV-01 */
    {
      #if (SPI_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_READIB_SID, SPI_E_PARAM_CHANNEL);
      #endif /* End of (SPI_DEV_ERROR_DETECT == STD_ON) */
      LucReturnValue = E_NOT_OK;
    }
    #endif /* (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB) */
    /* Check for IB or SPI_BUFFER_TYPE_TX_HWIB */
    else if (SPI_BUFFER_TYPE_IB == Spi_GpFirstChannel[Channel].enChannelBufferType)                                     /* PRQA S 2004, 3416 # JV-01, JV-01 */
    {
      /* Copy operation */
      LpChConfig = &Spi_GpFirstChannel[Channel];
      Spi_MemCopy(LpChConfig, DataBufferPointer, LpChConfig->pRxBuffer);
    }
  }
  return (LucReturnValue);
}
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)) */

/***********************************************************************************************************************
** Function Name       : Spi_SetupEB
**
** Service ID          : 0x05
**
** Description         : This service for setting the buffers and the length of data for the external buffer of the
**                       channel specified.
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Re-entrant for different Channel, Non Re-entrant for same Channel
**
** Input Parameters    : Channel - Channel ID
**                       SrcDataBufferPtr - Pointer to source data buffer                     
**                       buffer in RAM Length - Length of the data
**
** InOut Parameters    : DesDataBufferPtr - Pointer to destination data
**
** Output Parameters   : None
**
** Return parameter    : Std_ReturnType (E_OK/E_NOT_OK)
**
** Preconditions       : Spi_Init must have been invoked.
**
** Global Variable     : Spi_GblInitialized, Spi_GpConfigPtr, Spi_GpFirstChannel
**
** Function invoked    : Det_ReportError, SPI_ENTER_CRITICAL_SECTION, SPI_EXIT_CRITICAL_SECTION
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_006, SPI_DUD_ACT_006_ERR001, SPI_DUD_ACT_006_ERR002, SPI_DUD_ACT_006_ERR003,
** Reference ID        : SPI_DUD_ACT_006_ERR004, SPI_DUD_ACT_006_GBL001, SPI_DUD_ACT_006_ERR005, SPI_DUD_ACT_006_CRT001
** Reference ID        : SPI_DUD_ACT_006_CRT002
***********************************************************************************************************************/
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_EB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
FUNC(Std_ReturnType, SPI_PUBLIC_CODE)
Spi_SetupEB(Spi_ChannelType Channel, P2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) SrcDataBufferPtr,            /* PRQA S 1503 # JV-01 */
            P2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) DesDataBufferPtr, Spi_NumberOfDataType Length)          /* PRQA S 3432 # JV-01 */
{
  P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig;
  Std_ReturnType LucReturnValue;
  #if (SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  volatile uint8 LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = SPI_ONE << (uint8)GetCoreID();
  #endif /* (SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON)*/
  /* Initialize return value as E_OK */
  LucReturnValue = E_OK;
  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  /* Check if SPI Driver is initialized */
  if (SPI_FALSE == Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETUPEB_SID, SPI_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  }
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  else if ((Spi_GpFirstChannel[Channel].ucCoreMask & LucCoreID) != LucCoreID)                                           /* PRQA S 3416, 0404, 2004 # JV-01, JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETUPEB_SID, SPI_E_INVALID_CORE);
    LucReturnValue = E_NOT_OK;
  }

  #endif /* End of (SPI_MULTI_CORE_SUPPORT == STD_ON) */
  #endif /* End of (SPI_DEV_ERROR_DETECT == STD_ON) */
  /* Check if any DET error reported */
  if (E_OK == LucReturnValue)                                                                                           /* PRQA S 2991, 2995 # JV-01, JV-01 */
  {
    /* Check if the channel ID passed, is valid */
    if (Spi_GpConfigPtr->ucNoOfChannels <= Channel)                                                                     /* PRQA S 3416 # JV-01 */
    {
      #if (SPI_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETUPEB_SID, SPI_E_PARAM_CHANNEL);
      #endif /* End of (SPI_DEV_ERROR_DETECT == STD_ON) */
      LucReturnValue = E_NOT_OK;
    }  
    #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)

    /* Check if the requested channel is configured for internal buffer */
    else if (SPI_BUFFER_TYPE_EB != Spi_GpFirstChannel[Channel].enChannelBufferType)                                     /* PRQA S 3416 # JV-01 */
    {
      #if (SPI_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETUPEB_SID, SPI_E_PARAM_CHANNEL);
      #endif /* End of (SPI_DEV_ERROR_DETECT == STD_ON) */
      LucReturnValue = E_NOT_OK;
    }
    #endif /* (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB) */
    /* Check if the 'length' parameter is greater than configured length and if length is equal to zero */
    else if ((0U == Length) || (Length > Spi_GpFirstChannel[Channel].usNoOfBuffers))                                    /* PRQA S 3416, 3415 # JV-01, JV-01 */
    {
      #if (SPI_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETUPEB_SID, SPI_E_PARAM_LENGTH);
      #endif /* End of (SPI_DEV_ERROR_DETECT == STD_ON) */
      LucReturnValue = E_NOT_OK;
    }
    else

    {
      SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
      /* Set pointers from user */
      LpChConfig = &Spi_GpFirstChannel[Channel];
      LpChConfig->pEBData->pSrcPtr = SrcDataBufferPtr;
      LpChConfig->pEBData->pDestPtr = DesDataBufferPtr;
      LpChConfig->pEBData->usEBLength = Length;
      SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
    }
  }
  return (LucReturnValue);
}
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_EB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)) */

/***********************************************************************************************************************
** Function Name       : Spi_GetStatus
**
** Service ID          : 0x06
**
** Description         : This service is for getting the status of SPI Driver Component
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant
**
** Input Parameters    : None
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : Spi_StatusType (SPI_UNINIT/SPI_IDLE/SPI_BUSY)
**
** Preconditions       : Spi_Init must have been initialized
**
** Global Variable     : Spi_GblInitialized, Spi_GulActiveHWUnits
**
** Function Invoked    : Det_ReportError
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_007, SPI_DUD_ACT_007_ERR001
***********************************************************************************************************************/
FUNC(Spi_StatusType, SPI_PUBLIC_CODE) Spi_GetStatus(void)                                                               /* PRQA S 1503 # JV-01 */
{
  Spi_StatusType LenRetValue;

  if (SPI_FALSE == Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETSTATUS_SID, SPI_E_UNINIT);
    #endif
    LenRetValue = SPI_UNINIT;
  }
  else if (0UL != Spi_GulActiveHWUnits)                                                                                 /* PRQA S 3416 # JV-01 */
  {
    LenRetValue = SPI_BUSY;
  }
  else
  {
    LenRetValue = SPI_IDLE;
  }

  return LenRetValue;
}

/***********************************************************************************************************************
** Function Name       : Spi_GetJobResult
**
** Service ID          : 0x07
**
** Description         : This service is for getting result of the specified job
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant
**
** Input Parameters    : Job - Job ID
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : Spi_JobResultType (SPI_JOB_OK/SPI_JOB_PENDING/SPI_JOB_FAILED)
**
** Preconditions       : Spi_Init should have been invoked.
**
** Global Variable     : Spi_GblInitialized, Spi_GpConfigPtr, Spi_GaaJobStatus
**
** Function invoked    : Det_ReportError
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_008, SPI_DUD_ACT_008_ERR001, SPI_DUD_ACT_008_ERR002, SPI_DUD_ACT_008_ERR003
***********************************************************************************************************************/
FUNC(Spi_JobResultType, SPI_PUBLIC_CODE) Spi_GetJobResult(Spi_JobType Job)                                              /* PRQA S 1503 # JV-01 */
{
  Spi_JobResultType LenJobResult;
  #if (SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  volatile uint8 LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = SPI_ONE << (uint8)GetCoreID();
  #endif

  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  /* Check if SPI Driver is initialized */
  if (SPI_FALSE == Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETJOBRESULT_SID, SPI_E_UNINIT);
    LenJobResult = SPI_JOB_FAILED;
  }
  /* Check if the job ID passed, is valid */
  else if (Spi_GpConfigPtr->usNoOfJobs <= Job)                                                                          /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETJOBRESULT_SID, SPI_E_PARAM_JOB);
    LenJobResult = SPI_JOB_FAILED;
  }
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  else if ((Spi_GpFirstJob[Job].ucCoreMask & LucCoreID) != LucCoreID)                                                   /* PRQA S 3416, 0404 # JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETJOBRESULT_SID, SPI_E_INVALID_CORE);
    LenJobResult = SPI_JOB_FAILED;
  }
  #endif
  else
  #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
  {
    LenJobResult = Spi_GaaJobStatus[Job].enResult;
  }
  return (LenJobResult);
}

/***********************************************************************************************************************
** Function Name       : Spi_GetSequenceResult
**
** Service ID          : 0x08
**
** Description         : This service is for getting result of the specified sequence
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant
**
** Input Parameters    : Sequence - Sequence ID
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : Spi_SeqResultType (SPI_SEQ_OK/SPI_SEQ_PENDING/SPI_SEQ_FAILED/SPI_SEQ_CANCELED)
**
** Preconditions       : Spi_Init must have been invoked.
**
** Global Variable     : Spi_GblInitialized, Spi_GpConfigPtr, Spi_GaaSeqStatus
**
** Function invoked    : Det_ReportError
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_009, SPI_DUD_ACT_009_ERR001, SPI_DUD_ACT_009_ERR002, SPI_DUD_ACT_009_ERR003
***********************************************************************************************************************/
FUNC(Spi_SeqResultType, SPI_PUBLIC_CODE) Spi_GetSequenceResult(Spi_SequenceType Sequence)                               /* PRQA S 1503 # JV-01 */
{
  Spi_SeqResultType LenSeqResult;
  #if (SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  volatile uint8 LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = SPI_ONE << (uint8)GetCoreID();
  #endif

  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  /* Check if SPI Driver is initialized */
  if (SPI_FALSE == Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETSEQUENCERESULT_SID, SPI_E_UNINIT);
    LenSeqResult = SPI_SEQ_FAILED;
  }
  /* Check if the Sequence ID passed, is valid */
  else if (Spi_GpConfigPtr->ucNoOfSequences <= Sequence)                                                                /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETSEQUENCERESULT_SID, SPI_E_PARAM_SEQ);
    LenSeqResult = SPI_SEQ_FAILED;
  }
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  else if ((Spi_GpFirstSeq[Sequence].ucCoreMask & LucCoreID) != LucCoreID)                                              /* PRQA S 3416, 0404 # JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETSEQUENCERESULT_SID, SPI_E_INVALID_CORE);
    LenSeqResult = SPI_SEQ_FAILED;
  }
  #endif
  else
  #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
  {
    LenSeqResult = Spi_GaaSeqStatus[Sequence].enResult;
  }
  return (LenSeqResult);
}

/***********************************************************************************************************************
** Function Name         : Spi_GetVersionInfo
**
** Service ID            : 0x09
**
** Description           : This API returns the version information of SPI driver component.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : versioninfo
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
** Reference ID          : SPI_DUD_ACT_010, SPI_DUD_ACT_010_ERR001
***********************************************************************************************************************/
#if (SPI_VERSION_INFO_API == STD_ON)
FUNC(void, SPI_PUBLIC_CODE) Spi_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, SPI_APPL_DATA) versioninfo)        /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == versioninfo)
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETVERSIONINFO_SID, SPI_E_PARAM_POINTER);
  }
  else
  #endif /* (SPI_DEV_ERROR_DETECT == STD_ON) */
  {
    versioninfo->vendorID = SPI_VENDOR_ID;
    versioninfo->moduleID = SPI_MODULE_ID;
    versioninfo->sw_major_version = SPI_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = SPI_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = SPI_SW_PATCH_VERSION;
  }
}
#endif /* (SPI_VERSION_INFO_API == STD_ON) */

/***********************************************************************************************************************
** Function Name       : Spi_SyncTransmit
**
** Service ID          : 0x0A
**
** Description         : This service is for transmitting data synchronously
**
** Sync/Async          : Synchronous.
**
** Re-entrancy         : Re-entrant for different Sequence, Non Re-entrant for same Sequence
**
** Input Parameters    : Sequence - Sequence ID
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : Std_ReturnType (E_OK/E_NOT_OK)
**
** Preconditions       : Spi_Init should have been invoked.
**
** Global Variable     : Spi_GblInitialized, Spi_GpConfigPtr, Spi_GpFirstSeq, Spi_GulActiveHWUnits, 
**                       Spi_GaaSyncTransmitInfo
**
** Function invoked    : Det_ReportError, SPI_DET_REPORT_RUNTIME_ERROR, Spi_TransmitSyncSequence,
**                       SPI_ENTER_CRITICAL_SECTION, SPI_EXIT_CRITICAL_SECTION
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_011, SPI_DUD_ACT_011_CRT001, SPI_DUD_ACT_011_CRT002, SPI_DUD_ACT_011_CRT003,
** Reference ID        : SPI_DUD_ACT_011_CRT004, SPI_DUD_ACT_011_ERR001, SPI_DUD_ACT_011_ERR002, SPI_DUD_ACT_011_ERR003,
** Reference ID        : SPI_DUD_ACT_011_ERR004, SPI_DUD_ACT_011_GBL001, SPI_DUD_ACT_011_GBL002, SPI_DUD_ACT_011_ERR005,
** Reference ID        : SPI_DUD_ACT_011_ERR006, SPI_DUD_ACT_011_CRT005, SPI_DUD_ACT_011_CRT006, SPI_DUD_ACT_011_GBL003,
** Reference ID        : SPI_DUD_ACT_011_CRT007, SPI_DUD_ACT_011_CRT008
***********************************************************************************************************************/
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_SyncTransmit(Spi_SequenceType Sequence)                                       /* PRQA S 1503 # JV-01 */
{
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Polling times until the request has been executed */
  VAR(volatile uint32, AUTOMATIC) LulPollingTimes;
  #endif
  P2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSeqConfig;
  Std_ReturnType LucReturnValue;

  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a local variable for the current core ID */
  volatile uint8 LucHandleApiCoreID;
  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  /* Declare a local variable for the current core ID for each sequence */
  volatile uint8 LucCoreID;
  #endif /* #if (SPI_DEV_ERROR_DETECT == STD_ON) */
  #endif /* #if (SPI_MULTI_CORE_SUPPORT == STD_ON) */

  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Get the current core ID by OS service */
  LucHandleApiCoreID = (uint8)GetCoreID();
  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  LucCoreID = SPI_ONE << LucHandleApiCoreID;
  #endif /* #if (SPI_DEV_ERROR_DETECT == STD_ON) */
  #endif /* #if (SPI_MULTI_CORE_SUPPORT == STD_ON) */

  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  /* Check if SPI Driver is initialized */
  if (SPI_FALSE == Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SYNCTRANSMIT_SID, SPI_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  }
  /* Check if the sequence ID passed, is valid */
  else if (Spi_GpConfigPtr->ucNoOfSequences <= Sequence)                                                                /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SYNCTRANSMIT_SID, SPI_E_PARAM_SEQ);
    LucReturnValue = E_NOT_OK;
  }
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  else if ((Spi_GpFirstSeq[Sequence].ucCoreMask & LucCoreID) != LucCoreID)                                              /* PRQA S 3416, 0404 # JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SYNCTRANSMIT_SID, SPI_E_INVALID_CORE);
    LucReturnValue = E_NOT_OK;
  }
  #endif
  #if ((SPI_AR_VERSION == SPI_AR_422_VERSION) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  else if (SPI_FALSE == Spi_GpFirstSeq[Sequence].blSynchronous)
  {
    /* Report to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SYNCTRANSMIT_SID, SPI_E_PARAM_SEQ);
    LucReturnValue = E_NOT_OK;
  }
  #endif /* ((SPI_AR_VERSION == SPI_AR_422_VERSION) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */
  else
  #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
  {
    /* Get the pointer to the sequence structure */
    LpSeqConfig = &Spi_GpFirstSeq[Sequence];

    /* Check & Lock HWUnits to be used by this sequence */
    SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
    if ((0UL == (Spi_GulActiveHWUnits &                                                                                 /* PRQA S 3416 # JV-01 */
                 #if (SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT == STD_ON)
                 /* Check if a HW unit in the sequence is on-going in a sync transmission */
                 (LpSeqConfig->ulUsingHWUnits
                 #else
                 /* Check if any sync transmission is on-going */
                 (SPI_SYNC_HW_BITS
                 #endif
                 #if ((SPI_AR_VERSION == SPI_AR_R22_11_VERSION) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
                  /* Check if a HW unit in the sequence is on-going in an async transmission */
                  | (LpSeqConfig->ulUsingHWUnits << SPI_ACTIVE_HW_BITS)
                 #endif /* ((SPI_AR_VERSION == SPI_AR_R22_11_VERSION) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */
                      )))
        #if ((SPI_AR_VERSION == SPI_AR_R22_11_VERSION) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
        /* Check if a sequence status is not pending */
        && (SPI_SEQ_PENDING != Spi_GaaSeqStatus[Sequence].enResult)
        #endif /* ((SPI_AR_VERSION == SPI_AR_R22_11_VERSION) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */
    )
    {
      Spi_GulActiveHWUnits |= LpSeqConfig->ulUsingHWUnits;
      LucReturnValue = E_OK;
    }
    else
    {
      LucReturnValue = E_NOT_OK;
    }
    SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);

    if (E_OK != LucReturnValue)
    {
      /* Report to DET */
      SPI_DET_REPORT_RUNTIME_ERROR(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SYNCTRANSMIT_SID, SPI_E_SEQ_IN_PROCESS);
    }
    else
    {
      #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
      SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
      /* Request is issued */
      Spi_GaaSyncTransmitInfo[Sequence].blSetRequest = SPI_TRUE;
      SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);

      /* Waiting until the request is being executed */
      LulPollingTimes = SPI_ASYNCHONOUS_POLLING_TIMES;
      do
      {
        LulPollingTimes--;                                                                                              /* PRQA S 3384, 3387 # JV-01, JV-01 */
      } while ((SPI_TRUE == Spi_GaaSyncTransmitInfo[Sequence].blSetRequest) &&
               ((uint32)SPI_ZERO != LulPollingTimes));                                                                  /* PRQA S 3416, 3415 # JV-01, JV-01 */
      
      /* Check if the request has been executed */
      if ((SPI_TRUE == Spi_GaaSyncTransmitInfo[Sequence].blSetRequest) &&
          ((uint32)SPI_ZERO == LulPollingTimes))                                                                        /* PRQA S 3416, 3415 # JV-01, JV-01 */
      {
        SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
        /* Cancel request */
        Spi_GaaSyncTransmitInfo[Sequence].blSetRequest = SPI_FALSE;
        SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);

        /* Report to Runtime Error */
        SPI_DET_REPORT_RUNTIME_ERROR(SPI_MODULE_ID, SPI_INSTANCE_ID,
                                                  SPI_SYNCTRANSMIT_SID, SPI_E_REQUEST_ONGOING);

        LucReturnValue = E_NOT_OK;
      }
      else
      {
        /* The condition below only applies to cores other than the kernel core that perform sync transmit */
        if (Spi_GucKernalCoreId != LucHandleApiCoreID)                                                                  /* PRQA S 3416 # JV-01 */
        {
          SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
          /* Remark issue is ON_GOING */
          Spi_GaaSyncTransmitInfo[Sequence].blSetRequest = SPI_TRUE;
          SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);

          /* Polling for transmission requests on the kernel core */
          LulPollingTimes = Spi_GpConfigPtr->ulTimeoutCount;
          do
          {
            LulPollingTimes--;                                                                                          /* PRQA S 3384, 3387 # JV-01, JV-01 */
          } while ((SPI_TRUE == Spi_GaaSyncTransmitInfo[Sequence].blSetRequest) &&
            ((uint32)SPI_ZERO != LulPollingTimes));                                                                     /* PRQA S 3416, 3415 # JV-01, JV-01 */

          if ((SPI_TRUE == Spi_GaaSyncTransmitInfo[Sequence].blSetRequest) && 
              ((uint32)SPI_ZERO == LulPollingTimes))                                                                    /* PRQA S 3416, 3415 # JV-01, JV-01 */
          {
            /* Report to Runtime Error */
            SPI_DET_REPORT_RUNTIME_ERROR(SPI_MODULE_ID, SPI_INSTANCE_ID,
                                                    SPI_SYNCTRANSMIT_SID, SPI_E_SEQUENCE_TIMEOUT);

            LucReturnValue = E_NOT_OK;
          }
          else
          {
            LucReturnValue = Spi_GaaSyncTransmitInfo[Sequence].ucResult;
          }
        }
        else
        {
          LucReturnValue = Spi_GaaSyncTransmitInfo[Sequence].ucResult;
        }
      }

      SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
      /* Release locked HWUnits */
      Spi_GulActiveHWUnits &= ~(LpSeqConfig->ulUsingHWUnits);
      SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
      #else
      /* Transmission */
      LucReturnValue = Spi_TransmitSyncSequence((uint32)Sequence);

      /* Release locked HWUnits */
      SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION);
      Spi_GulActiveHWUnits &= ~(LpSeqConfig->ulUsingHWUnits);
      SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION);
      #endif
    }
  }

  return (LucReturnValue);
}
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

/***********************************************************************************************************************
** Function Name       : Spi_GetHWUnitStatus
**
** Service ID          : 0x0B
**
** Description         : This service is getting the status of the SPI. Hardware micro-controller peripheral
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant
**
** Input Parameters    : HWUnit - ID of Hardware Unit
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : Spi_StatusType (SPI_UNINIT/SPI_IDLE/SPI_BUSY)
**
** Preconditions       : Spi_Init must have been invoked.
**
** Global Variable     : Spi_GblInitialized, Spi_GpConfigPtr, Spi_GaaHWStatus
**
** Function invoked    : Det_ReportError
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_012, SPI_DUD_ACT_012_ERR001, SPI_DUD_ACT_012_ERR002, SPI_DUD_ACT_012_ERR003
***********************************************************************************************************************/
#if (SPI_HW_STATUS_API == STD_ON)
FUNC(Spi_StatusType, SPI_PUBLIC_CODE) Spi_GetHWUnitStatus(Spi_HWUnitType HWUnit)                                        /* PRQA S 1503 # JV-01 */
{
  Spi_StatusType LenHWUnitSts;

  #if (SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  volatile uint8 LucCoreID;
  #endif

  Spi_HWUnitType LucHwUnit;
  uint8 LucHWUnitIndex;

  /* Asign the first value to max number of HW Units */
  LucHwUnit = (Spi_HWUnitType)Spi_GpConfigPtr->ucNoOfHWUnits;

  /* Finding the index of HWUnit from config */
  for (LucHWUnitIndex = 0U; LucHWUnitIndex < (Spi_HWUnitType)Spi_GpConfigPtr->ucNoOfHWUnits; LucHWUnitIndex++)          /* PRQA S 3416 # JV-01 */
  {
    if (Spi_GpFirstHWUnit[LucHWUnitIndex].ucPhyUnitIndex == HWUnit)                                                     /* PRQA S 3416 # JV-01 */
    {
      LucHwUnit = (Spi_HWUnitType)LucHWUnitIndex;

      /* End of loop after found the index */
      LucHWUnitIndex = (Spi_HWUnitType)Spi_GpConfigPtr->ucNoOfHWUnits;                                                  /* PRQA S 2469 # JV-01 */
    }
  }

  #if (SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Get the current core ID by OS service */
  LucCoreID = SPI_ONE << (uint8)GetCoreID();
  #endif

  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  /* Check if SPI Driver is initialized */
  if (SPI_FALSE == Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETHWUNITSTATUS_SID, SPI_E_UNINIT);
    LenHWUnitSts = SPI_UNINIT;
  }
  /* Check the range of HWUnit index */
  else if (Spi_GpConfigPtr->ucNoOfHWUnits <= LucHwUnit)                                                                 /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETHWUNITSTATUS_SID, SPI_E_PARAM_UNIT);
    LenHWUnitSts = SPI_UNINIT;
  }
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  else if ((Spi_GpFirstHWUnit[LucHwUnit].ucCoreMask & LucCoreID) != LucCoreID)                                          /* PRQA S 3416, 0404 # JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETHWUNITSTATUS_SID, SPI_E_INVALID_CORE);
    LenHWUnitSts = SPI_UNINIT;
  }
  #endif
  else
  #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
  {
    if (SPI_TRUE == Spi_GaaHWStatus[LucHwUnit].blActive)
    {
      LenHWUnitSts = SPI_BUSY;
    }
    else
    {
      LenHWUnitSts = SPI_IDLE;
    }
  }
  return (LenHWUnitSts);
}
#endif /* End of (SPI_HW_STATUS_API == STD_ON) */

/***********************************************************************************************************************
** Function Name       : Spi_Cancel
**
** Service ID          : 0x0C
**
** Description         : This service is for canceling a on-going sequence
**
** Sync/Async          : Asynchronous
**
** Re-entrancy         : Reentrant
**
** Input Parameters    : Sequence - Sequence ID
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : Spi_Init must have been invoked.
**
** Global Variable     : Spi_GblInitialized, Spi_GpConfigPtr, Spi_GpFirstSeq, Spi_GulActiveHWUnits, 
**                       Spi_GaaCancelTransmitInfo
**
** Function invoked    : Det_ReportError, SPI_DET_REPORT_RUNTIME_ERROR, Spi_CancelSequence, SPI_ENTER_CRITICAL_SECTION
**                       SPI_EXIT_CRITICAL_SECTION
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_013, SPI_DUD_ACT_013_ERR001, SPI_DUD_ACT_013_ERR002, SPI_DUD_ACT_013_ERR003,
** Reference ID        : SPI_DUD_ACT_013_ERR004, SPI_DUD_ACT_013_ERR005, SPI_DUD_ACT_013_ERR006, SPI_DUD_ACT_013_ERR007,
** Reference ID        : SPI_DUD_ACT_013_CRT001, SPI_DUD_ACT_013_CRT002, SPI_DUD_ACT_013_GBL001
***********************************************************************************************************************/
#if (SPI_CANCEL_API == STD_ON)
FUNC(void, SPI_PUBLIC_CODE) Spi_Cancel(Spi_SequenceType Sequence)                                                       /* PRQA S 1503 # JV-01 */
{
  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  volatile uint8 LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = SPI_ONE << (uint8)GetCoreID();
  #endif
  
  /* Check if SPI Driver is initialized */
  if (SPI_FALSE == Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_CANCEL_SID, SPI_E_UNINIT);
  }
  /* Check if the sequence ID passed, is valid */
  else if (Spi_GpConfigPtr->ucNoOfSequences <= Sequence)                                                                /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_CANCEL_SID, SPI_E_PARAM_SEQ);
  }
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  else if ((Spi_GpFirstSeq[Sequence].ucCoreMask & LucCoreID) != LucCoreID)                                              /* PRQA S 3416, 0404 # JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_CANCEL_SID, SPI_E_INVALID_CORE);
  }
  #endif
  #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
  #if (SPI_AR_VERSION == SPI_AR_422_VERSION)
  /*
   * Check if the HW Unit of the job is configured for synchronous transmission
   */
  else if (SPI_TRUE == Spi_GpFirstSeq[Sequence].blSynchronous)
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_CANCEL_SID, SPI_E_PARAM_SEQ);
  }
  #endif /* (SPI_AR_VERSION == SPI_AR_422_VERSION) */
  #endif /* (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) */
  else
  #endif /* End of SPI_DEV_ERROR_DETECT == STD_ON */
  {
    #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_0)
    /* When LEVEL0, always raise error */
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_CANCEL_SID, SPI_E_PARAM_SEQ);
    #endif /* (SPI_DEV_ERROR_DETECT == STD_ON) */
    #else
    #if (SPI_AR_VERSION == SPI_AR_R22_11_VERSION)
    /* Check if sequence is already used for sync transmission */
    if (0UL != (Spi_GulActiveHWUnits & Spi_GpFirstSeq[Sequence].ulUsingHWUnits))                                        /* PRQA S 3416, 0404 # JV-01, JV-01 */
    {
      /* Report to DET */
      SPI_DET_REPORT_RUNTIME_ERROR(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_CANCEL_SID, SPI_E_SEQ_IN_PROCESS);
    }
    else
    #endif /* (SPI_AR_VERSION == SPI_AR_R22_11_VERSION) */
    {
      #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
      SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
      
      if (Spi_UnLockedStatus(Spi_GaaCancelTransmitInfo[Sequence].blBufferLock))                                         /* PRQA S 3432 # JV-01 */
      {
        /* Lock the shared buffer */
        Spi_LockProcess(Spi_GaaCancelTransmitInfo[Sequence].blBufferLock);                                              /* PRQA S 3432 # JV-01 */
        /* Release the spinlock */
        SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
        /* Request is issued */
        Spi_GaaCancelTransmitInfo[Sequence].blSetRequest = SPI_TRUE;
        /* Release Lock */
        Spi_UnLockProcess(Spi_GaaCancelTransmitInfo[Sequence].blBufferLock);                                            /* PRQA S 3432 # JV-01 */
      }
      else
      {
        /* Release the spinlock */
        SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
        /* Report to Development Errors */
        SPI_DET_REPORT_RUNTIME_ERROR(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_CANCEL_SID, SPI_E_REQUEST_FALSE);
      }
      #else
      Spi_CancelSequence((uint32)Sequence, SPI_FALSE);
      #endif
    }
    #endif /* (SPI_LEVEL_DELIVERED == SPI_LEVEL_0) */
  }
}
#endif /* End of (SPI_CANCEL_API == STD_ON) */

#define SPI_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define SPI_START_SEC_PUBLIC_CODE_LOCAL
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name       : Spi_SetAsyncMode
**
** Service ID          : 0x0D
**
** Description         : This service is for setting the asynchronous mode
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Non-Reentrant
**
** Input Parameters    : Mode - New Mode Required
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : Std_ReturnType (E_OK/E_NOT_OK)
**
** Preconditions       : Spi_Init must have been invoked.
**
** Global Variable     : Spi_GblInitialized, Spi_GenAsyncMode, Spi_GulAllQueuesSts, Spi_GpHwConfig, Spi_GucKernalCoreId
**
** Function invoked    : Det_ReportError, Spi_CSIXDisableAllInterrupts, Spi_HSPIDisableAllInterrupts,
**                       Spi_MSPIDisableAllInterrupts
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_014, SPI_DUD_ACT_014_ERR001, SPI_DUD_ACT_014_GBL001, SPI_DUD_ACT_014_GBL002
** Reference ID        : SPI_DUD_ACT_014_ERR002, SPI_DUD_ACT_014_ERR003
***********************************************************************************************************************/
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)
FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_SetAsyncMode(Spi_AsyncModeType Mode)                                          /* PRQA S 1503 # JV-01 */
{
  uint32 LulIndex;
  Std_ReturnType LucReturnValue;

  #if (SPI_DEV_ERROR_DETECT == STD_ON) && (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  volatile uint8 LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */
  #endif

  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  /* Check if SPI Driver is initialized */
  if (SPI_FALSE == Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETASYNCMODE_SID, SPI_E_UNINIT);
    LucReturnValue = E_NOT_OK;
  }
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Check if control API wasn't executed on Master Core */
  else if (Spi_GucKernalCoreId != LucCoreID)                                                                            /* PRQA S 3416 # JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETASYNCMODE_SID, SPI_E_INVALID_CORE);
    LucReturnValue = E_NOT_OK;
  }
  #endif
  /* Check if Mode is invalid */
  else if ((SPI_POLLING_MODE != Mode) && (SPI_INTERRUPT_MODE != Mode))
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETASYNCMODE_SID, SPI_E_PARAM_VALUE);
    LucReturnValue = E_NOT_OK;
  } 
  else
  #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
  {
    /* Confirm no async task is operating */
    if (0UL != Spi_GulAllQueueSts)                                                                                      /* PRQA S 3416 # JV-01 */
    {
      LucReturnValue = E_NOT_OK;
    }
    else
    {
      /* Enable or Disable interrupts according the specified mode */
      Spi_GenAsyncMode = Mode;
      if (SPI_POLLING_MODE == Mode)
      {
        for (LulIndex = 0UL; LulIndex < SPI_MAX_MACRO; LulIndex++)                                                      /* PRQA S 2877 # JV-01 */
        {
          Spi_GpHwConfig[LulIndex].pHwDepFunc->pHwDisableAllInterrupts();
        }
      } /* else No action required */
      LucReturnValue = E_OK;
    }
  }
  return (LucReturnValue);
}
#endif /* (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)||(SPI_LEVEL_DELIVERED == SPI_LEVEL_1) */

/***********************************************************************************************************************
** Function Name       : Spi_MainFunction_Handling
**
** Service ID          : 0x10
**
** Description         : This function is to be invoked in the scheduler loop for asynchronous transmission in
**                       polling mode
**
** Sync/Async          : NA
**
** Re-entrancy         : Non Reentrant
**
** Input Parameters    : None
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : This function should be invoked only when polling mechanism is selected by Spi_SetAsyncMode API
**
** Global Variable     : Spi_GblInitialized, Spi_GenAsyncMode, Spi_GpHwConfig, Spi_GucKernalCoreId
**
** Function Invoked    : Spi_CSIXMainFunction_Handling, Spi_HSPIMainFunction_Handling, Spi_MSPIMainFunction_Handling
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_015, SPI_DUD_ACT_015_GBL001
***********************************************************************************************************************/
FUNC(void, SPI_PUBLIC_CODE) Spi_MainFunction_Handling(void)                                                             /* PRQA S 1503, 3408 # JV-01, JV-01 */
{
  #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)
  uint32 LulIndex;

  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  volatile uint8 LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */
  /* Check if control API wasn't executed on Master Core */
  if (Spi_GucKernalCoreId != LucCoreID)                                                                                 /* PRQA S 3416 # JV-01 */
  {
    /* No action required */
  }
  else
  #endif
  {
    /* If SPI Driver is not initialized yet and in the interrupt mode, return immediately without any operation */
    if ((SPI_FALSE != Spi_GblInitialized) && (SPI_INTERRUPT_MODE != Spi_GenAsyncMode))                                  /* PRQA S 3416, 3415 # JV-01, JV-01 */
    {
      for (LulIndex = 0UL; LulIndex < SPI_MAX_MACRO; LulIndex++)                                                        /* PRQA S 2877 # JV-01 */
      {
        Spi_GpHwConfig[LulIndex].pHwDepFunc->pHwMainFunction_Handling();
      }
    }
  }
  #endif
}

#define SPI_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define SPI_START_SEC_PUBLIC_CODE_GLOBAL
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name       : Spi_ForceCancel
**
** Service ID          : 0xA0
**
** Description         : This service cancels a on-going Sequence immediately
**
** Sync/Async          : Synchronous (Single core)
**                       Asynchronous (Multi core)
**
** Re-entrancy         : Reentrant among Sequences which don't share same HW
**                       Non-Reentrant among Sequences which share same HW
**
** Input Parameters    : LucSequence - Sequence ID
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : Spi_Init must have been invoked.
**                       This function must not be invoked in a context which has the higher priority than any SPI ISRs.
**                       If this service preempts any ISRs, the subsequent operation is not guaranteed.
**
** Global Variable     : Spi_GblInitialized, Spi_GpConfigPtr, Spi_GpFirstSeq, Spi_GulActiveHWUnits, 
**                       Spi_GaaForceCancelTransmitInfo
**
** Function invoked    : SPI_DET_REPORT_RUNTIME_ERROR, Det_ReportError, Spi_CancelSequence, SPI_ENTER_CRITICAL_SECTION
**                       SPI_EXIT_CRITICAL_SECTION 
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_016, SPI_DUD_ACT_016_ERR001, SPI_DUD_ACT_016_ERR002, SPI_DUD_ACT_016_ERR003,
** Reference ID        : SPI_DUD_ACT_016_ERR004, SPI_DUD_ACT_036_GBL013, SPI_DUD_ACT_016_ERR005, SPI_DUD_ACT_016_ERR006,
** Reference ID        : SPI_DUD_ACT_016_GBL001, SPI_DUD_ACT_016_CRT001, SPI_DUD_ACT_016_CRT002
***********************************************************************************************************************/
#if (SPI_FORCE_CANCEL_API == STD_ON)
FUNC(void, SPI_PUBLIC_CODE) Spi_ForceCancel(const Spi_SequenceType LucSequence)                                         /* PRQA S 1503 # JV-01 */
{
  #if (SPI_DEV_ERROR_DETECT == STD_ON)
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare a Local variable for the current core ID */
  volatile uint8 LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = SPI_ONE << (uint8)GetCoreID();
  #endif
  
  /* Check if SPI Driver is initialized */
  if (SPI_FALSE == Spi_GblInitialized)                                                                                  /* PRQA S 3416 # JV-01 */
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_FORCECANCEL_SID, SPI_E_UNINIT);
  }
  /* Check if the sequence ID passed, is valid */
  else if (Spi_GpConfigPtr->ucNoOfSequences <= LucSequence)                                                             /* PRQA S 3416 # JV-01 */
  {
    /* Report to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_FORCECANCEL_SID, SPI_E_PARAM_SEQ);
  }
  #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
  else if ((Spi_GpFirstSeq[LucSequence].ucCoreMask & LucCoreID) != LucCoreID)                                           /* PRQA S 3416, 0404 # JV-01, JV-01 */
  {
    /* Report Error to DET */
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_FORCECANCEL_SID, SPI_E_INVALID_CORE);
  }
  #endif
  #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
  #if (SPI_AR_VERSION == SPI_AR_422_VERSION)
  /*
   * Check if the HW Unit of the job is configured for synchronous transmission
   */
  else if (SPI_TRUE == Spi_GpFirstSeq[LucSequence].blSynchronous)
  {
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_FORCECANCEL_SID, SPI_E_PARAM_SEQ);
  }
  #endif /* (SPI_AR_VERSION == SPI_AR_422_VERSION) */
  #endif /* (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) */
  else
  #endif /* (SPI_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_0)
    /* When LEVEL0, always raise error */
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_FORCECANCEL_SID, SPI_E_PARAM_SEQ);
    #endif /* (SPI_DEV_ERROR_DETECT == STD_ON) */
    #else
    #if (SPI_AR_VERSION == SPI_AR_R22_11_VERSION)
    /* Check if sequence is already used for sync transmission */
    if (0UL != (Spi_GulActiveHWUnits & Spi_GpFirstSeq[LucSequence].ulUsingHWUnits))                                     /* PRQA S 3416, 0404 # JV-01, JV-01 */
    {
      /* Report to DET */
      SPI_DET_REPORT_RUNTIME_ERROR(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_FORCECANCEL_SID, SPI_E_SEQ_IN_PROCESS);
    }
    else
    #endif /* (SPI_AR_VERSION == SPI_AR_R22_11_VERSION)*/
    {
      #if (SPI_MULTI_CORE_SUPPORT == STD_ON)
      SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
      
      if (Spi_UnLockedStatus(Spi_GaaForceCancelTransmitInfo[LucSequence].blBufferLock))                                 /* PRQA S 3432 # JV-01 */
      {
        /* Lock the shared buffer */
        Spi_LockProcess(Spi_GaaForceCancelTransmitInfo[LucSequence].blBufferLock);                                      /* PRQA S 3432 # JV-01 */
        /* Release the spinlock */
        SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
        /* Request is issued */
        Spi_GaaForceCancelTransmitInfo[LucSequence].blSetRequest = SPI_TRUE;
        /* Release Lock */
        Spi_UnLockProcess(Spi_GaaForceCancelTransmitInfo[LucSequence].blBufferLock);                                    /* PRQA S 3432 # JV-01 */
      }
      else
      {
        /* Release the spinlock */
        SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
        /* Report to Development Errors */
        SPI_DET_REPORT_RUNTIME_ERROR(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_FORCECANCEL_SID, SPI_E_REQUEST_FALSE);
      }
      #else
      Spi_CancelSequence((uint32)LucSequence, SPI_TRUE);
      #endif
    }
    #endif /* (SPI_LEVEL_DELIVERED == SPI_LEVEL_0) */
  }
}
#endif /* (SPI_FORCE_CANCEL_API == STD_ON) */

#define SPI_STOP_SEC_PUBLIC_CODE_GLOBAL
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define SPI_START_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name       : Spi_SetStatus
**
** Service ID          : Not Applicable
**
** Description         : This function updates Spi_GblInitialized. The purpose of this function is to prevent the order
**                       of instructions being changed by the compiler.
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Non-Reentrant
**
** Input Parameters    : LblStatus: New status value
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : None
**
** Global Variable     : Spi_GblInitialized
**
** Function invoked    : None
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_017, SPI_DUD_ACT_017_GBL001
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_SetStatus(const boolean LblStatus)
{
  Spi_GblInitialized = LblStatus;
}

/***********************************************************************************************************************
** Function Name       : Spi_MemCopy
**
** Service ID          : Not Applicable
**
** Description         : This function copies data from memory to memory
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant
**
** Input Parameters    : LpChConfig - Pointer to Channel configuration
**                       LpDesPtr   - Pointer to the destination address
**                       LpSrcPtr   - Pointer to the source address
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : None
**
** Global Variable     : None
**
** Function invoked    : None
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_018
***********************************************************************************************************************/
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MemCopy(CONSTP2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig,
                volatile CONSTP2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) LpDesPtr,                             /* PRQA S 3432 # JV-01 */
                volatile CONSTP2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) LpSrcPtr)
{
  uint32 LulCounter;
  LulCounter = 0U;
  if (NULL_PTR == LpSrcPtr)
  {
    switch (LpChConfig->ucByteSize)
    {
    case sizeof(uint32):
      /* Copy default data by 4 bytes */
      do
      {
        ((volatile P2VAR(uint32, AUTOMATIC, SPI_APPL_DATA))LpDesPtr)[LulCounter] = (uint32)LpChConfig->ulDefaultData;   /* PRQA S 0310, 3305, 3432 # JV-01, JV-01, JV-01 */
        LulCounter++;                                                                                                   /* PRQA S 3383 # JV-01 */
      } while (LulCounter < LpChConfig->usNoOfBuffers);
      break;
    case sizeof(uint16):
      /* Copy default data by 2 bytes */
      do
      {
        ((volatile P2VAR(uint16, AUTOMATIC, SPI_APPL_DATA))LpDesPtr)[LulCounter] = (uint16)LpChConfig->ulDefaultData;   /* PRQA S 3305, 0310, 3432 # JV-01, JV-01, JV-01 */
        LulCounter++;                                                                                                   /* PRQA S 3383 # JV-01 */
      } while (LulCounter < LpChConfig->usNoOfBuffers);
      break;
    default:
      /* Copy default data by byte */
      do
      {
        LpDesPtr[LulCounter] = (uint8)LpChConfig->ulDefaultData;
        LulCounter++;                                                                                                   /* PRQA S 3383 # JV-01 */
      } while (LulCounter < LpChConfig->usNoOfBuffers);
      break;
    }
  }
  else
  {
    switch (LpChConfig->ucByteSize)
    {
    case sizeof(uint32):
      /* Copy memory by 4 bytes */
      do
      {
        ((volatile P2VAR(uint32, AUTOMATIC, SPI_APPL_DATA))LpDesPtr)[LulCounter] =                                      /* PRQA S 3305, 0310, 3432 # JV-01, JV-01, JV-01 */
            ((volatile P2CONST(uint32, AUTOMATIC, SPI_APPL_DATA))LpSrcPtr)[LulCounter];                                 /* PRQA S 0310, 3305 # JV-01, JV-01 */
        LulCounter++;                                                                                                   /* PRQA S 3383 # JV-01 */
      } while (LulCounter < LpChConfig->usNoOfBuffers);
      break;
    case sizeof(uint16):
      /* Copy memory by 2 bytes */
      do
      {
        ((volatile P2VAR(uint16, AUTOMATIC, SPI_APPL_DATA))LpDesPtr)[LulCounter] =                                      /* PRQA S 0310, 3305, 3432 # JV-01, JV-01, JV-01 */
            ((volatile P2CONST(uint16, AUTOMATIC, SPI_APPL_DATA))LpSrcPtr)[LulCounter];                                 /* PRQA S 3305, 0310 # JV-01, JV-01 */
        LulCounter++;                                                                                                   /* PRQA S 3383 # JV-01 */
      } while (LulCounter < LpChConfig->usNoOfBuffers);
      break;
    default:
      /* Copy memory by byte */
      do
      {
        LpDesPtr[LulCounter] = LpSrcPtr[LulCounter];
        LulCounter++;                                                                                                   /* PRQA S 3383 # JV-01 */
      } while (LulCounter < LpChConfig->usNoOfBuffers);
      break;
    }
  }
}
#endif /* ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)) */

#define SPI_STOP_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
