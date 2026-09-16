/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_MSPI_LLDriver.c                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Low level driver function definitions of the SPI Driver                                         */
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
 *                       Update memory section macro from SPI_START/STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED 
 *                       to SPI_START/STOP_SEC_CONST_UNSPECIFIED for function pointer table Spi_GstMSPIFunc
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Add new QAC msg: 0404,3415,5087 to support QAC 11.6.0
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.1:  31/12/2024  : Update setting flow of MSPI trigger source for DMA in function Spi_MSPIInit
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 *                     : Update to correct interrupt sequence in Spi_MSPIForceStop for device U2Ax.
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 *                     : Support AR2211: update macro condition SPI_AR_R22_11_VERSION in Spi_MSPIMainFunction_Handling,
 *                     : Remove support SPI_AR_431_VERSION
 * 2.1.1:  07/08/2024  : Update function "Spi_MSPIInitializeForJob", "Spi_MSPIInitializeForCh", "Spi_MSPIProcessJob" 
 *                       to support for change frame length 
 *                       when "SpiEnablePersistentHwConfiguration" is congiured as TRUE
 *                     : Add new global variable "Spi_GstHwActiveOredIsr" to support for U2Cx device
 *                       Update to correct support for ored interrupts when assigning multiple units for 
 *                       an ored interrupt ID in U2Cx in function:
 *                       + Spi_MSPIInit, Spi_MSPITransmitSyncJob, Spi_MSPIForceStop, Spi_MSPIMaskHWUnitInterrupts
 *                     : Update to correct support for multiple jobs in sequence:
 *                       Update function "Spi_MSPIReceiveISR", "Spi_MSPIFrameEndISR", "Spi_MSPIDMACompleteISR"
 *                     : Update to correct support for Ored interrupt in U2Cx device:
 *                       Update function "Spi_MSPIInit", "Spi_MSPIDeInit", "Spi_MSPITransmitSyncJob", 
 *                       "Spi_MSPIDisableAllInterrupts", "Spi_MSPIMainFunction_Handling", "Spi_MSPIForceStop", 
 *                       "Spi_MSPIMaskHWUnitInterrupts"
 *                     : Update function Spi_MSPIInit to correct support for DMA trigger generation register in U2Bx-E
 *                     : Change SPI_START_SEC_CONFIG_DATA_UNSPECIFIED to
 *                       SPI_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
 *                     : Change SPI_STOP_SEC_CONFIG_DATA_UNSPECIFIED to
 *                       SPI_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
 *                     : Remove QAC messages (2:0857), (1:1531), (2:2824), (2:2934), (2:0314) 
 *                       to fix redundant QAC messages
 *                     : Increase SW-VERSION up to 2.0.3
 *                     : Update Generator for MSPITGCTL and MSPITRGCTLi in Spi_MSPIInit
 *                     : Update function Spi_MSPITransmitSyncJob, Spi_MSPIDisableAllInterrupts, 
 *                       Spi_MSPIMainFunction_Handling, Spi_MSPIForceStop, Spi_MSPIMaskHWUnitInterrupts to support Ored
 *                       Interrupt function
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  23/10/2023  : Add message 3006, 3415 support Amendment 2
 *                       Remove SPI_AR_R21_11_VERSION
 *         11/10/2023  : Update pre-condition SPI_AR_VERSION == SPI_AR_R22_11_VERSION for 
 *                       SPI_LEVEL_DELIVERED == SPI_LEVEL_1 to Spi_MSPIMainFunction_Handling
 *                       Update SW-VERSION to 2.0.1
 * 2.0.0:  23/08/2023  : Update PI_ENTER_CRITICAL_SECTION/SPI_EXIT_CRITICAL_SECTION GLOBAL for Spi_MSPIHWControlCS
 *         03/08/2023  : Update QAC message 1006, 2814, 2844.
 *         25/07/2023  : Update from "Spi_Mapping.h to "Spi_MemMap.h".
 *                       Update Exclusive_Area of SPI_ENTER_CRITICAL_SECTION/SPI_EXIT_CRITICAL_SECTION
 *         17/07/2023  : Update pre-condition SPI_AR_VERSION == SPI_AR_R21_11_VERSION for 
 *                       SPI_LEVEL_DELIVERED == SPI_LEVEL_1 to Spi_MSPIMainFunction_Handling
 *         09/05/2023  : Update SW-VERSION to 2.0.0
 * 1.5.0:  07/04/2023  : Update
 *                       Spi_MSPIDeInit, Spi_MSPIProcessJob, Spi_MSPIReceiveISR, Spi_MSPIFrameEndISR: Add 
 *                       Spi_MSPIHWControlCS into Function invoked
 *                       Spi_MSPIStartChannelFixedBufferMode: Remove Spi_LoadTxData in Function invoked
 *                       Spi_MSPITransmitSyncJob: Add Spi_DMAGetInterruptFlag, Spi_MSPIDMACompleteISR into 
 *                       Function invoked
 *                       Spi_MSPIDMACompleteISR: Add Spi_TurnOffHWUnit, Spi_MSPIHWControlCS into Function invoked field
 *                       Spi_MSPIStartChannelFixedBufferMode, Spi_MSPIStartChannelFixedFIFOMode: Remove LpChConfig
 *                       in Input Parameters field
 *                       Spi_MSPIFrameEndISR: Remove Spi_GpFirstChannel in Global Variable field
 *                       Spi_MSPIDMACompleteISR: Change LulHWUnitIndex to LulDMAUnitIndex in Input Parameters field
 *                       Spi_MSPIMainFunction_Handling: Remove Spi_GulCancelHWUnits, Spi_GetHWUnitStatus in
 *                       Global Variable field
 * 1.4.4:  18/07/2022  : Add QAC message for Spi_MSPIHWControlCS
 *         13/07/2022  : Update operator AND for Spi_MSPIHWControlCS
 *         08/07/2022  : Add DummyRead & SYNCP in functions: Spi_MSPITransmitSyncJob, Spi_MSPIDisableAllInterrupts,
 *                       Spi_MSPIMainFunction_Handling
 * 1.4.3:  21/06/2022  : Added de-active CS when CS as GPIO for Spi_MSPIReceiveISR, Spi_MSPIDMACompleteISR, 
 *                       Spi_MSPIDeInit, Spi_MSPIFrameEndISR
 *                       Add active CS when CS as GPIO for Spi_MSPIProcessJob (start transmit)
 *                       Add new function Spi_MSPIHWControlCS to control CS via GPIO
 *         10/05/2022  : Remove else do nothing
 * 1.4.2:  19/04/2022  : Change ulTRGCTL to ulTGCTL, ulTRGCTLi to ulTGCTL in Spi_MSPIInit
 *                       Remove redundant character
 * 1.4.1:  09/09/2021  : Change ucCSInfo to usCSInfo and update SW-VERSION to 1.4.1
 *                       Set DMA Trigger Generator for MSPITRGCTL and MSPITRGCTLi in Spi_MSPIInit function.
 * 1.3.2:  04/09/2021  : Replace the inclusion of Spi_MemMap.h with Spi_Mapping.h
 *                       Update precondition for calling SPI_DEM_REPORT_ERROR
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 *         19/05/2021  : Update QAC contents.
 *         13/05/2021  : Update to fix coding rule violations.
 * 1.2.1:  02/10/2020  : Implement dummy read after setting CTL1 and CTL2 before write "1" to MSPInEN in Spi_MSPIInit,
 *                       Spi_MSPIInitializeForJob and Spi_MSPIProcessJob to avoid slave output data is shifted in
 *                       slave mode.
 *         11/09/2020  : Implement interrupt control flow for Spi_MSPITransmitISR and Spi_MSPIReceiveISR to prevent
 *                       buffer full during transmission.
 * 1.2.0:  10/08/2020  : Release
 *                       Correct the index of Spi_GaaMSPIRegs in function Spi_MSPIDMACompleteISR.
 *         30/07/2020  : Fix bug that memory mode could not switch between jobs.
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.4:  19/05/2020  : 1. Update declaration of element Spi_MSPIDMACompleteISR in struct Spi_GstMSPIFunc to support
 *                          DMA at Level 0.
 * 1.0.3:  18/05/2020  : 1. Spi_MSPIReceiveISR, Spi_MSPITransmitISR: simplified method of getting HW channel
 *                          configuration from loop-based checking to Job configuration.
 * 1.0.2:  07/05/2020  : The following changes are made:
 *                       1. Move masking of interrupt factor HW unit settings from Spi_MSPIInit into
 *                          Spi_MSPIInitializeForJob to support multiple memory modes configured for one HW channel.
 * 1.0.1:  14/04/2020  : The following are made:
 *                       1. Remove redundent pre-compile option DMA ON for Spi_MSPIInitializeForCh.
 *                       2. Remove pre-compile option of Spi_MSPIDMACompleteISR to support DMA in level 0.
 *                       3. Disable HW channel is moved out of persistent cfg.
 *                       4. Remove MSPI RAM copy in Spi_MSPIFrameEndISR Spi_MSPIStartChannelFixedBufferMode.
 *                       5. Remove EOJ setting in Spi_MSPITransmitISR and Spi_MSPIStartChannelDirectMemoryMode since it
 *                          is not related to frame end interrupt.
 *                       6. Set IFEE for all memory modes in Spi_MSPIInit.
 *                       7. Check DCE, CEF, PEF for all memory modes in Spi_MSPIReceiveISR and Spi_MSPIDMACompleteISR.
 *                       8. Update Spi_MSPIReceiveISR and Spi_MSPITransmitISR to remove redundant code and improve
 *                          performance.
 *                       9. Correct HW physical index when accessing Spi_GaaMSPIRegs in Spi_MSPIDMACompleteISR.
 *                       10. Update condition for SW trigger in Spi_MSPIStartChannelDirectMemoryMode,
 *                           Spi_MSPIStartChannelFixedBufferMode, and Spi_MSPIStartChannelFixedFIFOMode.
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Spi.h"
#include "Spi_Ram.h"
#include "Spi_Irq.h"
#include "Spi_MSPI_LLDriver.h"
#include "rh850_Types.h"
#include "Dem.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define SPI_MSPI_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION_VALUE
#define SPI_MSPI_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION_VALUE
#define SPI_MSPI_LLDRIVER_C_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define SPI_MSPI_LLDRIVER_C_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION_VALUE
#define SPI_MSPI_LLDRIVER_C_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (SPI_MSPI_LLDRIVER_AR_RELEASE_MAJOR_VERSION != SPI_MSPI_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "Spi_MSPI_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (SPI_MSPI_LLDRIVER_AR_RELEASE_MINOR_VERSION != SPI_MSPI_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "Spi_MSPI_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (SPI_MSPI_LLDRIVER_AR_RELEASE_REVISION_VERSION != SPI_MSPI_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "Spi_MSPI_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (SPI_MSPI_LLDRIVER_SW_MAJOR_VERSION != SPI_MSPI_LLDRIVER_C_SW_MAJOR_VERSION)
#error "Spi_MSPI_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (SPI_MSPI_LLDRIVER_SW_MINOR_VERSION != SPI_MSPI_LLDRIVER_C_SW_MINOR_VERSION)
#error "Spi_MSPI_LLDriver.c : Mismatch in Software Minor Version"
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
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-476, CWE-465, CWE-737, CWE-690                                   */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2844)    : Possible: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127        */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : It is specific for device register accessing and confirmed has no issue in software behavior.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3387)    : A full expression containing an increment (++) or decrement (--) operator should have no     */
/*                       potential side effects other than that caused by the increment or decrement operator.        */
/* Rule                : MISRA C:2012 Rule-13.3                                                                       */
/* JV-01 Justification : An increment/decrement is created a side affect. In this case it's accessing a volatile      */
/*                       object. This can be accepted.                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : CERTCCM EXP10, EXP30, MISRA C:2012 Rule-1.3, Rule-13.2, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get element in array of struct, volatile of counter variable of 'for' loop is     */
/*                       used to ensure no optimization. It is accepted                                               */
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
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4461)    : A non-constant expression of 'essentially unsigned' type (%1s) is being converted to         */
/*                       narrower unsigned type, '%2s' on assignment.                                                 */
/* Rule                : CERTCCM INT02, MISRA C:2012 Rule-10.3, CWE Rule CWE-681, CWE-136, CWE-192                    */
/* JV-01 Justification : This operation is necessary to offset a 32-bit address on RAM to a 16-bit buffer address.    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4391)    : A composite expression of 'essentially unsigned' type (%1s) is being cast to a wider         */
/*                       unsigned type, '%2s'.                                                                        */
/* Rule                : MISRA C:2012 Rule-10.8, CWE Rule CWE-136                                                     */
/* JV-01 Justification : This casting is for the lower operator which requires wider type.                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : This is accepted. It just an advise for  improve safety by reducing the possibility that     */
/*                       the referenced data is unintentionally modified through an unexpected alias and improves     */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2962)    : Apparent: Using value of uninitialized automatic object '%s'.                                */
/* Rule                : CERTCCM EXP33, MISRA C:2012 Rule-9.1, CWE Rule CWE-457, CWE-824, CWE-908, CWE-452, CWE-465   */
/*                       CWE-737                                                                                      */
/* JV-01 Justification : It will be initialized based on scope of 'if' statements  where at least an 'if' statement   */
/*                       will be executed that will initialize the variable.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:3305)    : Pointer cast to stricter alignment.                                                          */
/* Rule                : CERTCCM EXP36, EXP39, MISRA C:2012 Rule-11.3, CWE Rule CWE-188, CWE-737                      */
/* JV-01 Justification : Pointer alignment is changed by casting, but it's necessary for embedded programming         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : CERTCCM EXP11, EXP39, MISRA C:2012 Rule-11.3, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588    */
/*                       CWE-465, CWE-569, CWE-737                                                                    */
/* JV-01 Justification : For accessing 8-bit and 16-bit PNOT and JPNOT register respectively, the 32-bit pointer is   */
/*                       typecasted.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4, CWE Rule CWE-188, CWE-398, CWE-569                    */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : [E] This in-line assembler construct is a language extension. The code has been ignored.     */
/* Rule                : MISRA-C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTC 1.2.4 MSC14                                   */
/* JV-01 Justification : Inline assembler support for syncp instruction.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with possible side effects.              */
/* Rule                : CERTCCM EXP02, MISRA C:2012 Rule-13.5, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it is not a direct access to the HW register, and          */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#if (SPI_MSPI_CONFIGURED == STD_ON)
#define SPI_START_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"

/* Prototypes for functions used in this file only */
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIInit(void);
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIDeInit(void);
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIDisableAllInterrupts(void);
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIProcessJob(const boolean LblFirst, CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig);
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
STATIC FUNC(Std_ReturnType, SPI_PRIVATE_CODE)
    Spi_MSPITransmitSyncJob(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig);
#endif
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIMaskHWUnitInterrupts(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,
                                 const boolean LblMask);
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
#if (SPI_FORCE_CANCEL_API == STD_ON)
STATIC FUNC(void, SPI_CODE_FAST) Spi_MSPIForceStop(const uint32 LulHWUnitIndex);
#endif
#endif
#if (SPI_DMA_CONFIGURED == STD_ON)
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIDMACompleteISR(const uint32 LulDMAUnitIndex);
#endif
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIMainFunction_Handling(void);
#endif
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPITurnOff(const uint32 LulHWPhyIndex);

STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIInitializeForJob(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,
                             const boolean LblCFGxOnly);

STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIInitializeForCh(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,
                            CONSTP2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig);

#if (SPI_DIRECT_ACCESS_MODE == STD_ON)
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIStartChannelDirectMemoryMode(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,
                                         volatile CONSTP2CONST(Spi_HWStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpHWStat,
                                         const uint32 LulHWPhyIndex, const uint32 LulHWChannel);
#endif

#if (SPI_FIXED_BUFFER_MODE == STD_ON)
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIStartChannelFixedBufferMode(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,
                                        volatile CONSTP2VAR(Spi_HWStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpHWStat,     /* PRQA S 3432 # JV-01 */
                                        const uint32 LulHWPhyIndex, const uint32 LulHWChannel);
#endif

#if (SPI_FIXED_FIFO_MODE == STD_ON)
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIStartChannelFixedFIFOMode(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,
                                      volatile CONSTP2CONST(Spi_HWStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpHWStat,
                                      const uint32 LulHWPhyIndex, const uint32 LulHWChannel);
#endif

STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_LoadTxData(volatile CONSTP2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) LpData,
                   CONSTP2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig,
                   volatile CONSTP2VAR(uint32, AUTOMATIC, AUTOMATIC) LpOutData);                                        /* PRQA S 3432 # JV-01 */

STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_StoreRxData(volatile CONSTP2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) LpData,                           /* PRQA S 3432 # JV-01 */
                    CONSTP2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig, const uint32 LulInData);

#if (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON)
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIHWControlCS(
  CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,
  CONST(boolean, AUTOMATIC) LblActivateCS);
#endif

#define SPI_STOP_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

#define SPI_START_SEC_CONST_UNSPECIFIED
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* HW-dependent function pointer table */
CONST(Spi_HwFuncTableType, SPI_CONST)
Spi_GstMSPIFunc =
{
  &Spi_MSPIInit,
  &Spi_MSPIDisableAllInterrupts,
  &Spi_MSPIProcessJob,
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  &Spi_MSPITransmitSyncJob,
  #endif
  &Spi_MSPIMaskHWUnitInterrupts,
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  #if (SPI_FORCE_CANCEL_API == STD_ON)
  &Spi_MSPIForceStop,
  #endif
  #endif
  #if (SPI_DMA_CONFIGURED == STD_ON)
  &Spi_MSPIDMACompleteISR,
  #endif
  #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)
  &Spi_MSPIMainFunction_Handling,
  #endif
  &Spi_MSPITurnOff,
  &Spi_MSPIDeInit
};

#define SPI_STOP_SEC_CONST_UNSPECIFIED
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
STATIC volatile VAR(Spi_MSPIHwOredISR, SPI_VAR_NO_INIT) Spi_GstHwActiveOredIsr[SPI_MSPI_ORED_UNITS];
#endif /* #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON) */

#define SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define SPI_START_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name      : Spi_MSPIInit
**
** Service ID         : Not Applicable
**
** Description        : This function initializes all configured MSPI units
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Global variables must have been initialized
**
** Global Variable    : Spi_GpConfigPtr, Spi_GpFirstHWUnit, Spi_GaaMSPIRegs, Spi_GpFirstJob, Spi_GpFirstDMAUnit
**
** Function invoked   : Spi_MSPIInitializeForJob, Spi_MSPIDisableAllInterrupts,
**
** Registers Used     : MSPInCTL0, MSPInCTL1, MSPITGCTLn, MSPInFRERSTCm, MSPInCESTCm, MSPInCFGm0,
**                      INTMSPICTSMSKn, INTMSPICRSMSKn, INTMSPICFCMSKn, INTMSPICERMSKn
**
** Reference ID       : SPI_DUD_ACT_059, SPI_DUD_ACT_059_REG010, SPI_DUD_ACT_059_REG007, SPI_DUD_ACT_059_REG014,
** Reference ID       : SPI_DUD_ACT_059_REG008, SPI_DUD_ACT_059_REG009, SPI_DUD_ACT_059_REG015, SPI_DUD_ACT_059_GBL001,
** Reference ID       : SPI_DUD_ACT_059_REG016, SPI_DUD_ACT_059_REG011, SPI_DUD_ACT_059_REG012
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIInit(void)
{
  uint32 LulHWPhyIndex;
  uint32 LulPhyChannel;
  uint32 LulHWUnitIndex;
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;
  P2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig;
  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;
  #if (SPI_DMA_CONFIGURED == STD_ON)
  P2CONST(Spi_DmaConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpDmaConfig;
  uint32 LulDmaIndex;
  #endif
  uint32 LulJobIndex;
  uint32 LulInitialized;
  #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_OFF)
  volatile uint32 LulDummyCount;
  #endif

  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
  VAR(uint8, AUTOMATIC) LucIsrSelId;
  #endif

  #if (SPI_DMA_CONFIGURED == STD_ON)
  /* Set DMA Trigger Generator Registers */
  for (LulDmaIndex = 0UL; LulDmaIndex < Spi_GpConfigPtr->ucNoOfDMAChannels; LulDmaIndex++)                              /* PRQA S 3416 # JV-01 */
  {
    LpDmaConfig = &Spi_GpFirstDMAUnit[LulDmaIndex];
    LulHWPhyIndex = Spi_GpFirstHWUnit[LpDmaConfig->ucSPIHWUnit].ucPhyUnitIndex;

    #if (SPI_MSPI_MAX_CHANNEL == SPI_MSPI_MAX_CHANNEL_DEFAULT)
    Spi_GaaMSPIRegs[LulHWPhyIndex].pTrgGenRegs->ulTGCTL[LulHWPhyIndex] |= LpDmaConfig->ulMSPITGCTLn;

    Spi_GaaMSPIRegs[LulHWPhyIndex].pTrgGenRegs->ulTGCTLi[LulHWPhyIndex] |= LpDmaConfig->ulMSPITGCTLi;
    #else
    Spi_GaaMSPIRegs[LulHWPhyIndex].pTrgGenRegs->ulTGCTL[LulHWPhyIndex] |= LpDmaConfig->ulMSPITGCTLn;
    #endif
  }
  #endif

  /* Disable all interrupts unconditionally */
  Spi_MSPIDisableAllInterrupts();

  /* Mask interrupt for all HW unit to disable all interrupt */
  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
  /* Scan all ORed Interrupts */
  for (LucIsrSelId = 0U;  LucIsrSelId < SPI_MAX_MSPI_ORED; LucIsrSelId++)
  {
    RH850_SV_MODE_ICR_OR(32, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTSMSK, SPI_INTERRUPT_MASK);
    RH850_SV_MODE_ICR_OR(32, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRSMSK, SPI_INTERRUPT_MASK);
    RH850_SV_MODE_ICR_OR(32, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFCMSK, SPI_INTERRUPT_MASK);
    RH850_SV_MODE_ICR_OR(32, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICERMSK, SPI_INTERRUPT_MASK);

    Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredTxIsr = SPI_MSPI_ORED_DISABLED;
    Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredRxIsr = SPI_MSPI_ORED_DISABLED;
    Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredFeIsr = SPI_MSPI_ORED_DISABLED;
  }
  #endif /* #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON) */

  /* Initialize already initialized flags */
  LulInitialized = 0UL;
  /* Scan all jobs and initialize the associated HWUnits */
  for (LulJobIndex = 0U; LulJobIndex < Spi_GpConfigPtr->usNoOfJobs; LulJobIndex++)                                      /* PRQA S 3416 # JV-01 */
  {
    LpJobConfig = &Spi_GpFirstJob[LulJobIndex];
    /* Get HW unit index */
    LulHWUnitIndex = LpJobConfig->ucHWUnitIndex;
    LpHWInfo = &Spi_GpFirstHWUnit[LulHWUnitIndex];
    /* Get physical unit index */
    LulHWPhyIndex = LpHWInfo->ucPhyUnitIndex;
    LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;           /* PRQA S 0316 # JV-01 */
    /* Get physical channel index */
    LulPhyChannel = LpHWDevConfig->ucPhyChannelIndex;

    /* Enable interrupt requests */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulPhyChannel].ulCFG0 =
        (uint32)(SPI_MSPI_IRXE | SPI_MSPI_ITXE | SPI_MSPI_IFEE | SPI_MSPI_CFG0_DEFAULT);

    /* Clear all error status bits */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulPhyChannel].ucFRERSTC =
        (uint8)(SPI_MSPI_DCEFSC | SPI_MSPI_CEFSC | SPI_MSPI_PEFSC);
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulPhyChannel].ucCESTC =
        (uint8)(SPI_MSPI_OVREEC | SPI_MSPI_OVWREC | SPI_MSPI_OVRUEC | SPI_MSPI_DCEC | SPI_MSPI_CEC | SPI_MSPI_PEC);

    /* Avoid initializing same HW twice */
    if (0UL == (LulInitialized & (1UL << LulHWUnitIndex)))
    {
      /* Initialize MSPI channel offset variable */
      #if (SPI_FIXED_BUFFER_MODE == STD_ON)
      Spi_GaaHWStatus[LulHWUnitIndex].usTxChannelOffset = 0U;
      #endif
      /* Disable MSPI channel */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucCTL0 = SPI_MSPI_CTL0_DEFAULT;
      #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_ON)
      /*
       * If hardware settings never changed during operation, initialize entire the MSPI unit here.
       */
      Spi_MSPIInitializeForJob(LpJobConfig, SPI_FALSE);
      #else
      /* Otherwise, initialize CTL1 with the first Job as default value */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ulCTL1 = LpHWDevConfig->ulMSPICTL1;
      /* MSPInEN is set again, dummy read MSPInCTL0 12 times */
      LulDummyCount = SPI_MSPI_DUMMY_READ_12T;
      while (0UL < LulDummyCount)                                                                                       /* PRQA S 3416 # JV-01 */
      {
        Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucCTL0;
        LulDummyCount--;                                                                                                /* PRQA S 3387, 3384 # JV-01, JV-01 */
      }
      /* Enable MSPI unit by setting CTL0.MSPInEN = 1 */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucCTL0 = SPI_MSPI_EN;
      #endif /* (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_ON) */

      /* Un-mask interrupt of HW */
      #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
      LucIsrSelId = Spi_GaaMSPIRegs[LulHWPhyIndex].ucInterruptSel;

      /* Mapping interrupt for U2Cx device to support ORED interrupt function */
      RH850_SV_MODE_ICR_AND(32, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTSMSK, ((uint16)(~(1UL << LulHWPhyIndex))));
      RH850_SV_MODE_ICR_AND(32, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRSMSK, ((uint16)(~(1UL << LulHWPhyIndex))));
      RH850_SV_MODE_ICR_AND(32, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFCMSK, ((uint16)(~(1UL << LulHWPhyIndex))));
      #endif /* #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF) */

      /* Avoid initializing same HW twice */
      LulInitialized = LulInitialized | (1UL << LulHWUnitIndex);
    }
    else
    {
      #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_ON)
      /* Initialize MSPI HW channel associated to each Job */
      Spi_MSPIInitializeForJob(LpJobConfig, SPI_TRUE);
      #endif
    }
  }
}

/***********************************************************************************************************************
** Function Name      : Spi_MSPIDeInit
**
** Service ID         : Not Applicable
**
** Description        : This function de-initializes all configured MSPI units
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Spi_Init must have been invoked.
**
** Global Variable    : Spi_GpConfigPtr, Spi_GpFirstJob, Spi_GpFirstHWUnit, Spi_GaaMSPIRegs
**
** Function invoked   : Spi_MSPIDisableAllInterrupts, Spi_MSPIHWControlCS
**
** Registers Used     : MSPInCTL0, MSPInCTL1, MSPInCTL2, MSPInINTMSKk, MSPInCFGm0, MSPInCFGm1, MSPInCFGm2,
**                      MSPInCFGm3, MSPInCFGm4, MSPInRASTADm, MSPInSEUPm, MSPInHOLDm, MSPInIDLEm, MSPInINDAm,
**                      MSPInCFSETm, MSPInFRERSTCm, MSPInCESTCm
**                      INTMSPICTSMSKn, INTMSPICRSMSKn, INTMSPICFCMSKn, INTMSPICERMSKn
**
** Reference ID       : SPI_DUD_ACT_060, SPI_DUD_ACT_060_REG001, SPI_DUD_ACT_060_REG002, SPI_DUD_ACT_060_REG003,
** Reference ID       : SPI_DUD_ACT_060_REG004, SPI_DUD_ACT_060_REG005, SPI_DUD_ACT_060_REG006, SPI_DUD_ACT_060_REG007,
** Reference ID       : SPI_DUD_ACT_060_REG008, SPI_DUD_ACT_060_REG009, SPI_DUD_ACT_060_REG010, SPI_DUD_ACT_060_REG011,
** Reference ID       : SPI_DUD_ACT_060_REG012, SPI_DUD_ACT_060_REG013, SPI_DUD_ACT_060_REG014, SPI_DUD_ACT_060_REG015,
** Reference ID       : SPI_DUD_ACT_060_REG016, SPI_DUD_ACT_060_REG017, SPI_DUD_ACT_060_REG018, SPI_DUD_ACT_060_REG019
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIDeInit(void)
{
  uint32 LulJobIndex;
  uint32 LulHWUnitIndex;
  uint32 LulHWPhyIndex;
  uint32 LulHWPhyChannel;
  uint32 LulInitialized;
  uint32 LulMask;
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;
  P2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig;
  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;

  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
  VAR(uint8, AUTOMATIC) LucIsrSelId;
  #endif

  LulInitialized = 0UL;
  /* Scan all jobs and initialize the associated HWUnits */
  for (LulJobIndex = 0U; LulJobIndex < Spi_GpConfigPtr->usNoOfJobs; LulJobIndex++)                                      /* PRQA S 3416 # JV-01 */
  {
    LpJobConfig = &Spi_GpFirstJob[LulJobIndex];
    LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;           /* PRQA S 0316 # JV-01 */
    LulHWUnitIndex = LpJobConfig->ucHWUnitIndex;
    LpHWInfo = &Spi_GpFirstHWUnit[LulHWUnitIndex];

    /* Initialize MSPI unit */
    LulHWPhyIndex = LpHWInfo->ucPhyUnitIndex;
    /* Get physical channel number */
    LulHWPhyChannel = LpHWDevConfig->ucPhyChannelIndex;

    /* Avoid initializing same HW twice */
    if (0UL == (LulInitialized & (1UL << LulHWUnitIndex)))
    {
      /* Disable MSPI channel */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucCTL0 = SPI_MSPI_CTL0_DEFAULT;

      /* Restore all used registers as the rest default value */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ulCTL1 = SPI_MSPI_CTL1_DEFAULT;
      Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucCTL2 = SPI_MSPI_CTL2_DEFAULT;

      /* Calculate number of channels corresponding to HW physical index */
      LulMask = (1UL << Spi_GaaMSPIRegs[LulHWPhyIndex].ucPhyChannelMax) - 1UL;                                          /* PRQA S 3384 # JV-01 */
      /* Tx interrupts output to INTC2 masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK0 = LulMask;
      /* Rx interrupts output to INTC2 masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK1 = LulMask;
      /* FE interrupts output to INTC2 masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK2 = LulMask;

      /* Set initialization flag to configure once for same HW unit in job */
      LulInitialized = LulInitialized | (1UL << LulHWUnitIndex);
    } /* else No action required */

    /* Initialize CFGx registers */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].ulCFG0 = SPI_MSPI_CFG0_DEFAULT;
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].ulCFG1 = SPI_MSPI_CFG1_DEFAULT;
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usCFG2 = SPI_MSPI_CFG2_DEFAULT;
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usCFG3 = SPI_MSPI_CFG3_DEFAULT;
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].ulCFG4 = SPI_MSPI_CFG4_DEFAULT;
    /* Initialize MSPI RAM start address register */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usRASTAD = SPI_MSPI_RASTAD_DEFAULT;
    /* Initialize Setup/Hold/Idle/Inter-Data time set registers */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usSEUP = SPI_MSPI_SEUP_DEFAULT;
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usHOLD = SPI_MSPI_HOLD_DEFAULT;
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usIDLE = SPI_MSPI_IDLE_DEFAULT;
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usINDA = SPI_MSPI_INDA_DEFAULT;
    /* Initialize frame count register */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usCFSET = SPI_MSPI_CFSET_DEFAULT;
    /* Initialize error status clear registers */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].ucFRERSTC =
        (uint8)(SPI_MSPI_DCEFSC | SPI_MSPI_CEFSC | SPI_MSPI_PEFSC);
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].ucCESTC =
        (uint8)(SPI_MSPI_OVREEC | SPI_MSPI_OVWREC | SPI_MSPI_OVRUEC | SPI_MSPI_DCEC | SPI_MSPI_CEC | SPI_MSPI_PEC);
    #if (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON)
    if (SPI_GPIO_CS == LpJobConfig->enCSType)
    {
      /* Deactivate the chip select */
      Spi_MSPIHWControlCS(LpJobConfig, SPI_FALSE);
    }
    #endif /* (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON) */
  }
  Spi_MSPIDisableAllInterrupts();

  /* Mask interrupt for all HW unit to disable all interrupt */
  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
  /* Scan all ORed Interrupts */
  for (LucIsrSelId = 0U;  LucIsrSelId < SPI_MAX_MSPI_ORED; LucIsrSelId++)
  {
    RH850_SV_MODE_ICR_OR(32, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTSMSK, SPI_INTERRUPT_MASK);
    RH850_SV_MODE_ICR_OR(32, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRSMSK, SPI_INTERRUPT_MASK);
    RH850_SV_MODE_ICR_OR(32, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFCMSK, SPI_INTERRUPT_MASK);
    RH850_SV_MODE_ICR_OR(32, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICERMSK, SPI_INTERRUPT_MASK);
  }
  #endif /* #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON) */
}
/***********************************************************************************************************************
** Function Name     : Spi_MSPIInitializeForJob
**
** Service ID        : Not Applicable
**
** Description       : Setup a MSPI unit according to Job and the first channel
**
** Sync/Async        : Synchronous
**
** Re-entrancy       : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters  : LpJobConfig - Pointer to the Job configuration
**                     LblCFGxOnly - If true, only CFGx registers are configured
**
** InOut Parameters  : None
**
** Output Parameters : None
**
** Return parameter  : None
**
** Preconditions     : Spi_Init must have been invoked.
**
** Global Variable   : Spi_GpFirstChannel, Spi_GpFirstHWUnit, Spi_GaaMSPIRegs
**
** Function Invoked  : None
**
** Registers Used    : MSPInCFGm0, MSPInCTL0, MSPInCTL1, MSPInCTL2, MSPInFRERSTCm, MSPInCESTCm,
**                     MSPInINTMSKk, MSPInCFGm0, MSPInCFGm1, MSPInCFGm2, MSPInCFGm3, MSPInCFGm4, MSPInSEUPm,
**                     MSPInHOLDm, MSPInIDLEm, MSPInINDAm
**
** Reference ID      : SPI_DUD_ACT_061, SPI_DUD_ACT_061_REG001, SPI_DUD_ACT_061_REG002, SPI_DUD_ACT_061_REG003,
** Reference ID      : SPI_DUD_ACT_061_REG004, SPI_DUD_ACT_061_REG005, SPI_DUD_ACT_061_REG006, SPI_DUD_ACT_061_REG007,
** Reference ID      : SPI_DUD_ACT_061_REG008, SPI_DUD_ACT_061_REG009, SPI_DUD_ACT_061_REG010, SPI_DUD_ACT_061_REG011,
** Reference ID      : SPI_DUD_ACT_061_REG012, SPI_DUD_ACT_061_REG013, SPI_DUD_ACT_061_REG014, SPI_DUD_ACT_061_REG015,
** Reference ID      : SPI_DUD_ACT_061_REG016, SPI_DUD_ACT_061_REG017, SPI_DUD_ACT_061_REG018, SPI_DUD_ACT_061_REG019,
** Reference ID      : SPI_DUD_ACT_061_REG020, SPI_DUD_ACT_061_REG021, SPI_DUD_ACT_061_REG022, SPI_DUD_ACT_061_REG023,
** Reference ID      : SPI_DUD_ACT_061_REG024
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIInitializeForJob(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,
                             const boolean LblCFGxOnly)
{
  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;
  P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig;
  uint32 LulHWPhyIndex;
  uint32 LulHWPhyChannel;
  uint32 LulCFG1Value;
  volatile uint32 LulDummyCount;

  LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;             /* PRQA S 0316 # JV-01 */
  LpHWInfo = &Spi_GpFirstHWUnit[LpJobConfig->ucHWUnitIndex];
  LulHWPhyIndex = LpHWInfo->ucPhyUnitIndex;
  LulHWPhyChannel = LpHWDevConfig->ucPhyChannelIndex;

  if (SPI_FALSE == LblCFGxOnly)
  {
    /* Setup CTL0/1/2 registers according to Job settings */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ulCTL1 = LpHWDevConfig->ulMSPICTL1;
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucCTL2 = LpHWDevConfig->ucMSPICTL2;
    /* MSPInEN is set again, dummy read MSPInCTL0 12 times */
    LulDummyCount = SPI_MSPI_DUMMY_READ_12T;
    while (0UL < LulDummyCount)                                                                                         /* PRQA S 3416 # JV-01 */
    {
      Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucCTL0;
      LulDummyCount--;                                                                                                  /* PRQA S 3387, 3384 # JV-01, JV-01 */
    }
    /* Enable MSPI unit by setting CTL0.MSPInEN = 1 */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucCTL0 = SPI_MSPI_EN;
  } /* else No action required */

  /* Un-mask/mask for the MSPI channel */
  #if (SPI_DMA_CONFIGURED == STD_ON)
  if (SPI_INVALID_DMAUNIT != LpJobConfig->ucRxDmaIndex)
  {
    /* Tx interrupts output to INTC2 masked */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK0 |= (1UL << LulHWPhyChannel);
    /* Rx interrupts output to INTC2 masked */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK1 |= (1UL << LulHWPhyChannel);
    /* Tool has rejected jobs having memory mode as Fixed buffer related to DMA */
  }
  else
  #endif /* (SPI_DMA_CONFIGURED == STD_ON) */
  {
    /* Check memory mode configured for job */
    if (SPI_MEMORYMODE_FIXED_BUFFER != LpHWDevConfig->enMemoryMode)
    {
      /* Tx interrupts output to INTC2 un-masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK0 &= ~(1UL << LulHWPhyChannel);
      /* Rx interrupts output to INTC2 un-masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK1 &= ~(1UL << LulHWPhyChannel);
      /* FE interrupts output to INTC2 masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK2 |= (1UL << LulHWPhyChannel);
    }
    else
    {
      /* Tx interrupts output to INTC2 masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK0 |= (1UL << LulHWPhyChannel);
      /* Rx interrupts output to INTC2 masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK1 |= (1UL << LulHWPhyChannel);
      /* FE interrupts output to INTC2 un-masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK2 &= ~(1UL << LulHWPhyChannel);
    }
  }

  /* Get CFGx value from Job(includes baudrate and ChipSelect settings) and
   * the first Channel(includes data length and direction) */
  LpChConfig = &Spi_GpFirstChannel[LpJobConfig->pChannelList[0]];
  LulCFG1Value = LpHWDevConfig->ulMSPICFG1;
  if (SPI_TRANSFER_START_LSB == LpChConfig->enTransferStart)
  {
    LulCFG1Value |= SPI_MSPI_DIR;
  } /* else No action required */

  /* Clear all error status bits */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].ucFRERSTC =
      (uint8)(SPI_MSPI_DCEFSC | SPI_MSPI_CEFSC | SPI_MSPI_PEFSC);
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].ucCESTC =
      (uint8)(SPI_MSPI_OVREEC | SPI_MSPI_OVWREC | SPI_MSPI_OVRUEC | SPI_MSPI_DCEC | SPI_MSPI_CEC | SPI_MSPI_PEC);

  /* Setup CFGx registers */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].ulCFG0 = LpHWDevConfig->ulMSPICFG0;
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].ulCFG1 = LulCFG1Value;
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usCFG2 = (uint16)LpChConfig->ucDataWidth;
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usCFG3 = LpHWDevConfig->usMSPICFG3;
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].ulCFG4 = LpHWDevConfig->ulMSPICFG4;
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usSEUP = LpHWDevConfig->usMSPISEUP;
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usHOLD = LpHWDevConfig->usMSPIHOLD;
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usIDLE = LpHWDevConfig->usMSPIIDLE;
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usINDA = LpHWDevConfig->usMSPIINDA;
}

/***********************************************************************************************************************
** Function Name      : Spi_MSPIInitializeForCh
**
** Service ID         : Not Applicable
**
** Description        : Setup a MSPI unit according to Channel configuration
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters   : LpJobConfig    - Pointer to the Job configuration
**                      LpChConfig     - Pointer to the Channel configuration
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Spi_Init must have been invoked.
**
** Global Variable    : Spi_GpFirstHWUnit, Spi_GaaMSPIRegs
**
** Function Invoked   : None
**
** Registers Used     : MSPInCFGm1, MSPInCFGm2, MSPInCFSETm
**
** Reference ID       : SPI_DUD_ACT_062, SPI_DUD_ACT_062_REG007, SPI_DUD_ACT_062_REG002, SPI_DUD_ACT_062_REG003,
** Reference ID       : SPI_DUD_ACT_062_REG006
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIInitializeForCh(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,
                            CONSTP2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig)
{
  uint32 LulHWPhyIndex;
  uint32 LulHWPhyChannel;
  #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_OFF)
  uint32 LulCFG1Value;
  #endif /* #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_OFF) */
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;
  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;

  LpHWInfo = &Spi_GpFirstHWUnit[LpJobConfig->ucHWUnitIndex];
  LulHWPhyIndex = LpHWInfo->ucPhyUnitIndex;
  LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;             /* PRQA S 0316 # JV-01 */
  LulHWPhyChannel = LpHWDevConfig->ucPhyChannelIndex;

  #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_OFF)
  /* Make CFGx value from Job(includes baudrate and ChipSelect settings) and
   * the first Channel(includes data length and direction) */
  LulCFG1Value = LpHWDevConfig->ulMSPICFG1;
  if (SPI_TRANSFER_START_LSB == LpChConfig->enTransferStart)
  {
    LulCFG1Value |= SPI_MSPI_DIR;
  } /* else No action required */
  /* Since only the first CFGx is marked as dominant, it is enough to modify the first CFGx */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].ulCFG1 = LulCFG1Value;
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usCFG2 = (uint16)LpChConfig->ucDataWidth;
  #endif /* #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_OFF) */

  /* Set the frame count */
  #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
  if (SPI_BUFFER_TYPE_IB == LpChConfig->enChannelBufferType)
  #endif
  {
    #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usCFSET = LpChConfig->usNoOfBuffers;
    #endif
  }
  #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
  else
  #endif
  {
    #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_EB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usCFSET = LpChConfig->pEBData->usEBLength;
    #endif
  }
}

/***********************************************************************************************************************
** Function Name      : Spi_MSPIProcessJob
**
** Service ID         : Not Applicable
**
** Description        : This function perform scheduling under Job layer
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters   : LblFirst    - This is the first call for the Job
**                      LpJobConfig - Pointer to the Job configuration
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Spi_Init must have been invoked.
**
** Global Variable    : Spi_GpFirstChannel, Spi_GpFirstHWUnit, Spi_GaaHWStatus, Spi_GaaMSPIRegs
**
** Function Invoked   : Spi_MSPIInitializeForJob, Spi_MSPIInitializeForCh, Spi_MSPIStartChannelDirectMemoryMode,
**                      Spi_MSPIStartChannelFixedBufferMode, Spi_MSPIStartChannelFixedFIFOMode, Spi_MSPIHWControlCS
**
** Registers Used     : MSPInCTL0, MSPInCFSETm, MSPInCSTCm
**
** Reference ID       : SPI_DUD_ACT_066, SPI_DUD_ACT_066_GBL001, SPI_DUD_ACT_066_GBL002, SPI_DUD_ACT_066_GBL003,
** Reference ID       : SPI_DUD_ACT_066_REG001, SPI_DUD_ACT_066_REG002, SPI_DUD_ACT_066_REG003, SPI_DUD_ACT_066_REG004
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIProcessJob(const boolean LblFirst, CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig)
{
  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;
  volatile P2VAR(Spi_HWStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpHWStat;                                                /* PRQA S 3432 # JV-01 */
  P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig;
  uint32 LulHWPhyIndex;
  uint32 LulHWPhyChannel;
  uint32 LulChIndex;

  LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;             /* PRQA S 0316 # JV-01 */
  LpHWInfo = &Spi_GpFirstHWUnit[LpJobConfig->ucHWUnitIndex];
  LulHWPhyIndex = LpHWInfo->ucPhyUnitIndex;
  LulHWPhyChannel = LpHWDevConfig->ucPhyChannelIndex;
  LpHWStat = &Spi_GaaHWStatus[LpJobConfig->ucHWUnitIndex];

  /*
   * If this is the start of Job, initialize entire MSPI.
   * Otherwise, initialize channel relevant registers only.
   */
  if (SPI_TRUE == LblFirst)
  {
    /* Initialize status and HW according to Job config */
    LpHWStat->ucTxChannelCount = 0U;
    LpHWStat->ucRxChannelCount = 0U;
    #if (SPI_FIXED_BUFFER_MODE == STD_ON)
    LpHWStat->usTxChannelOffset = 0U;
    #endif
    LulChIndex = LpJobConfig->pChannelList[0];
    LpChConfig = &Spi_GpFirstChannel[LulChIndex];

    #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_OFF)
    /* Power OFF */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucCTL0 = SPI_MSPI_TURNOFF;
    /* Initialize MSPIn */
    Spi_MSPIInitializeForJob(LpJobConfig, SPI_FALSE);
    #endif /* #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_OFF) */

    /* Disable HW channel to setting channel configuration registers for */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].ucCSTC = SPI_MSPI_CHENC;

    /* Set the frame count */
    #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
    if (SPI_BUFFER_TYPE_IB == LpChConfig->enChannelBufferType)
    #endif
    {
      #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
      Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usCFSET = LpChConfig->usNoOfBuffers;
      #endif
    }
    #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
    else
    #endif
    {
      #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_EB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
      Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usCFSET = LpChConfig->pEBData->usEBLength;
      #endif
    }

    #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_ON)
    /* Power ON */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucCTL0 = SPI_MSPI_EN;
    #endif /* #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_ON) */

  } /* if (SPI_TRUE == LblFirst) */
  else
  {
    /* Initialize HW according to Channel config */
    LulChIndex = LpJobConfig->pChannelList[LpHWStat->ucTxChannelCount];
    LpChConfig = &Spi_GpFirstChannel[LulChIndex];
    /* Disable HW channel to setting channel configuration registers */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].ucCSTC = SPI_MSPI_CHENC;

    /* Initialize CFGx according to Channel config */
    Spi_MSPIInitializeForCh(LpJobConfig, LpChConfig);
  } /* else (SPI_TRUE == LblFirst) */

  if (SPI_MEMORYMODE_FIXED_BUFFER != LpHWDevConfig->enMemoryMode)
  {
    /* Prepare channel buffers */
    #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
    if (SPI_BUFFER_TYPE_IB == LpChConfig->enChannelBufferType)
    #endif
    {
      #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
      /* Initialize rx/tx pointers to point to IB */
      LpHWStat->pTxPtr = LpChConfig->pTxBuffer;
      LpHWStat->pRxPtr = LpChConfig->pRxBuffer;
      LpHWStat->usRemainedTxCount = LpChConfig->usNoOfBuffers;
      LpHWStat->usRemainedRxCount = LpChConfig->usNoOfBuffers;
      #endif
    }
    #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
    else
    #endif
    {
      #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_EB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
      /* Initialize rx/tx pointers to point to EB */
      LpHWStat->pTxPtr = LpChConfig->pEBData->pSrcPtr;
      LpHWStat->pRxPtr = LpChConfig->pEBData->pDestPtr;
      LpHWStat->usRemainedTxCount = LpChConfig->pEBData->usEBLength;
      LpHWStat->usRemainedRxCount = LpChConfig->pEBData->usEBLength;
      #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_ON)
      /* If using static configuration, CFSET won't be updated after user call
         Spi_SetupEB API, need to update it again before transmission. */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWPhyChannel].usCFSET = LpChConfig->pEBData->usEBLength;
      #endif
      #endif
    }
  } /* else No action required */
  #if (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON)
  if (SPI_GPIO_CS == LpJobConfig->enCSType)
  {
    /* Activate the chip select */
    Spi_MSPIHWControlCS(LpJobConfig, SPI_TRUE);
  }
  #endif /* (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON) */
  
  switch (LpHWDevConfig->enMemoryMode)
  {
  #if (SPI_DIRECT_ACCESS_MODE == STD_ON)
  case SPI_MEMORYMODE_DIRECT:
    /* Direct memory mode */
    Spi_MSPIStartChannelDirectMemoryMode(LpJobConfig, LpHWStat, LulHWPhyIndex, LulHWPhyChannel);
    break;
  #endif
  #if (SPI_FIXED_FIFO_MODE == STD_ON)
  case SPI_MEMORYMODE_FIXED_FIFO:
    /* Fixed FIFO memory mode */
    Spi_MSPIStartChannelFixedFIFOMode(LpJobConfig, LpHWStat, LulHWPhyIndex, LulHWPhyChannel);
    break;
  #endif
  #if (SPI_FIXED_BUFFER_MODE == STD_ON)
  case SPI_MEMORYMODE_FIXED_BUFFER:
    /* Fixed buffer memory mode */
    Spi_MSPIStartChannelFixedBufferMode(LpJobConfig, LpHWStat, LulHWPhyIndex, LulHWPhyChannel);
    break;
  #endif
  default:
    /* Nothing to do */
    break;
  }
}

#if (SPI_DIRECT_ACCESS_MODE == STD_ON)
/***********************************************************************************************************************
** Function Name      : Spi_MSPIStartChannelDirectMemoryMode
**
** Service ID         : Not Applicable
**
** Description        : In Direct Memory Mode on MSPI, Transmitted data is controlled by the TX register,
**                      and received data is controlled by the RX register.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters   : LpJobConfig   - Pointer to the Job configuration
**                      LpHWStat      - Pointer to the HW status structure
**                      LulHWPhyIndex - Physical index of the HWUnit
**                      LulHWChannel  - Physical index of the HWUnit channel
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Spi_Init must have been invoked.
**
** Global Variable    : Spi_GpFirstChannel, Spi_GulDmaRxData, Spi_GaaMSPIRegs, Spi_GulActiveHWUnits
**
** Function Invoked   : Spi_DMAStart
**
** Registers Used     : MSPInTXDAm, MSPInCSTSm, MSPInSSELm, MSPInRASTADm
**
** Reference ID       : SPI_DUD_ACT_067, SPI_DUD_ACT_067_REG001, SPI_DUD_ACT_067_REG002, SPI_DUD_ACT_067_REG003,
** Reference ID       : SPI_DUD_ACT_067_REG004
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIStartChannelDirectMemoryMode(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,
                                         volatile CONSTP2CONST(Spi_HWStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpHWStat,
                                         const uint32 LulHWPhyIndex, const uint32 LulHWChannel)
{
  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;
  #if (SPI_DMA_CONFIGURED == STD_ON)
  uint32 LulChIndex;
  P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig;
  #endif

  LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;             /* PRQA S 0316 # JV-01 */

  #if (SPI_DMA_CONFIGURED == STD_ON)
  LulChIndex = LpJobConfig->pChannelList[LpHWStat->ucTxChannelCount];
  LpChConfig = &Spi_GpFirstChannel[LulChIndex];
  /* In dirrect memory mode, use default seting TC bits in initialization */
  /* Setup DMA for Rx side */
  if (SPI_INVALID_DMAUNIT != LpJobConfig->ucRxDmaIndex)
  {
    if (NULL_PTR != LpHWStat->pRxPtr)
    {
      /* If rx buffer isn't NULL, set pointer to rx buffer to DMA */
      Spi_DMAStart(                                                                                                     /* PRQA S 0404 # JV-01 */
          (uint32)LpJobConfig->ucRxDmaIndex,
          (volatile P2CONST(void, AUTOMATIC, SPI_APPL_DATA))LpHWStat->pRxPtr, (uint32)LpHWStat->usRemainedRxCount,
          (uint32)LpChConfig->ucByteSize | SPI_DMA_INCDST | SPI_DMA_INTERRUPT | SPI_DMA_TC(1UL));                       /* PRQA S 3469 # JV-01 */
    }
    else
    {
      /* If rx buffer is NULL, set pointer to the dummy variable to DMA */
      Spi_DMAStart(
          (uint32)LpJobConfig->ucRxDmaIndex, (volatile P2CONST(void, AUTOMATIC, SPI_APPL_DATA)) & Spi_GulDmaRxData,
          (uint32)LpHWStat->usRemainedRxCount, (uint32)LpChConfig->ucByteSize | SPI_DMA_INTERRUPT | SPI_DMA_TC(1UL));   /* PRQA S 3469 # JV-01 */
    }
  } /* else No action required */
  /* Setup DMA for Tx side */
  if (SPI_INVALID_DMAUNIT != LpJobConfig->ucTxDmaIndex)
  {
    if (NULL_PTR != LpHWStat->pTxPtr)
    {
      /* If tx buffer isn't NULL, set pointer to tx buffer to DMA */
      Spi_DMAStart((uint32)LpJobConfig->ucTxDmaIndex,                                                                   /* PRQA S 0404 # JV-01 */
                   (volatile P2CONST(void, AUTOMATIC, SPI_APPL_DATA))LpHWStat->pTxPtr,
                   (uint32)LpHWStat->usRemainedTxCount,
                   (uint32)LpChConfig->ucByteSize | SPI_DMA_INCSRC | SPI_DMA_TC(1UL));                                  /* PRQA S 3469 # JV-01 */
    }
    else
    {
      /* If tx buffer is NULL, set pointer to the default data to DMA */
      Spi_DMAStart((uint32)LpJobConfig->ucTxDmaIndex,
                   (volatile P2CONST(void, AUTOMATIC, SPI_APPL_DATA)) & LpChConfig->ulDefaultData,
                   (uint32)LpHWStat->usRemainedTxCount, (uint32)LpChConfig->ucByteSize | SPI_DMA_TC(1UL));              /* PRQA S 3469 # JV-01 */
    }
  } /* else No action required */
  #endif /* (SPI_DMA_CONFIGURED == STD_ON) */

  /* ChipSelect/Job Enable and Start transmission setting */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWChannel].usSSEL = LpJobConfig->usCSInfo;

  /* Set MSPI RAM address */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWChannel].usRASTAD = SPI_MSPI_RASTAD_DEFAULT;

  /* Set channel enable flag of MSPInCSTS */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWChannel].ucCSTS = SPI_MSPI_CHENS;

  /* Check if sync transmission or the first channel of a job or SW trigger is configured */
  if ((0UL != (Spi_GulActiveHWUnits & (1UL << LpJobConfig->ucHWUnitIndex))) || (0U != LpHWStat->ucTxChannelCount) ||    /* PRQA S 3416 # JV-01 */
      (0UL == (SPI_MSPI_HWTS_MASK & LpHWDevConfig->ulMSPICFG4)))
  {
    /* Set channel active flag of MSPInCSTS */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWChannel].ucCSTS = SPI_MSPI_ACTFS;
  } /* else No action required */
}
#endif /* (SPI_DIRECT_ACCESS_MODE == STD_ON) */

#if (SPI_FIXED_BUFFER_MODE == STD_ON)
/***********************************************************************************************************************
** Function Name      : Spi_MSPIStartChannelFixedBufferMode
**
** Service ID         : Not Applicable
**
** Description        : In Fixed Buffer Memory Mode on MSPI, The channels use MSPI RAM. Data directly written in the
**                      MSPI RAM memory is used as transmission data, and the received data is stored in the MSPI RAM.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters   : LpJobConfig   - Pointer to the Job configuration
**                      LpHWStat      - Pointer to the HW status structure
**                      LulHWPhyIndex - Physical index of the HWUnit
**                      LulHWChannel  - Physical index of the HWUnit channel
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Spi_Init must have been invoked.
**
** Global Variable    : Spi_GpFirstChannel, Spi_GaaMSPIRegs, Spi_GulActiveHWUnits
**
** Function Invoked   : None
**
** Registers Used     : MSPInRASTADm, MSPInSSELm, MSPInCSTSm
**
** Reference ID       : SPI_DUD_ACT_068, SPI_DUD_ACT_068_GBL004, SPI_DUD_ACT_068_GBL005, SPI_DUD_ACT_068_REG004,
** Reference ID       : SPI_DUD_ACT_068_REG001, SPI_DUD_ACT_068_REG002, SPI_DUD_ACT_068_REG003
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIStartChannelFixedBufferMode(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,
                                        volatile CONSTP2VAR(Spi_HWStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpHWStat,     /* PRQA S 3432 # JV-01 */
                                        const uint32 LulHWPhyIndex, const uint32 LulHWChannel)
{
  uint32 LulChIndex;
  uint16 LusCS;
  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;
  P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig;

  LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;             /* PRQA S 0316 # JV-01 */
  LulChIndex = LpJobConfig->pChannelList[LpHWStat->ucTxChannelCount];
  LpChConfig = &Spi_GpFirstChannel[LulChIndex];

  /* Set ChipSelect field(MSPInCSRm) of MSPInSSELm register */
  LusCS = LpJobConfig->usCSInfo;

  /* Chip Select setting */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWChannel].usSSEL = LusCS;

  /* Set MSPI RAM address for Tx buffer of channel */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWChannel].usRASTAD =
      LpHWDevConfig->usMSPIRASTAD + LpHWStat->usTxChannelOffset;

  /* Offset RAM address for Rx buffer of channel */
  LpHWStat->usTxChannelOffset += SPI_ALIGN_4(((uint16)LpChConfig->ucByteSize * LpChConfig->usNoOfBuffers));             /* PRQA S 3384, 4461, 3469, 4391, 3383 # JV-01, JV-01, JV-01, JV-01, JV-01 */

  /* Offset RAM address for next channel */
  LpHWStat->usTxChannelOffset += SPI_ALIGN_4(((uint16)LpChConfig->ucByteSize * LpChConfig->usNoOfBuffers));             /* PRQA S 3384, 4461, 4391, 3469, 3383 # JV-01, JV-01, JV-01, JV-01, JV-01 */

  /* Set channel enable flag of MSPInCSTS */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWChannel].ucCSTS = SPI_MSPI_CHENS;

  /* Check if sync transmission or the first channel of a job or SW trigger is configured */
  if ((0UL != (Spi_GulActiveHWUnits & (1UL << LpJobConfig->ucHWUnitIndex))) || (0U != LpHWStat->ucTxChannelCount) ||    /* PRQA S 3416 # JV-01 */
      (0UL == (SPI_MSPI_HWTS_MASK & LpHWDevConfig->ulMSPICFG4)))
  {
    /* Set channel active flag of MSPInCSTS */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWChannel].ucCSTS = SPI_MSPI_ACTFS;
  } /* else No action required */
}
#endif /* (SPI_FIXED_BUFFER_MODE == STD_ON) */

#if (SPI_FIXED_FIFO_MODE == STD_ON)
/***********************************************************************************************************************
** Function Name      : Spi_MSPIStartChannelFixedFIFOMode
**
** Service ID         : Not Applicable
**
** Description        : In Fixed FIFO Memory Mode on MSPI, The channels use MSPI RAM. Transmission data written from
**                      CPU/DMA to the MSPInTXDAm0 register is automatically stored in MSPI RAM.
**                      Reception data is automatically stored in the MSPI RAM, and the CPU/DMA can read received data 
**                      using MSPInRXDAm0.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters   : LpJobConfig   - Pointer to the Job configuration
**                      LpHWStat      - Pointer to the HW status structure
**                      LulHWPhyIndex - Physical index of the HWUnit
**                      LulHWChannel  - Physical index of the HWUnit channel
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Spi_Init must have been invoked.
**
** Global Variable    : Spi_GpFirstChannel, Spi_GulDmaRxData, Spi_GaaMSPIRegs, Spi_GulActiveHWUnits
**
** Function Invoked   : Spi_DMAStart
**
** Registers Used     : MSPInTXDAm, MSPInCSTSm, MSPInRASTADm, MSPInSSELm
**
** Reference ID       : SPI_DUD_ACT_069, SPI_DUD_ACT_069_REG001, SPI_DUD_ACT_069_REG002, SPI_DUD_ACT_069_REG003
** Reference ID       : SPI_DUD_ACT_069_REG004
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIStartChannelFixedFIFOMode(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,
                                      volatile CONSTP2CONST(Spi_HWStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpHWStat,
                                      const uint32 LulHWPhyIndex, const uint32 LulHWChannel)
{
  uint16 LusCS;
  #if (SPI_DMA_CONFIGURED == STD_ON)
  uint8 LucSize;
  uint32 LulChIndex;
  P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig;
  #endif

  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;
  LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;             /* PRQA S 0316 # JV-01 */

  #if (SPI_DMA_CONFIGURED == STD_ON)
  LulChIndex = LpJobConfig->pChannelList[LpHWStat->ucTxChannelCount];
  LpChConfig = &Spi_GpFirstChannel[LulChIndex];
  /* Compute number of DMA transmission per trigger */
  LucSize = (uint8)(LpHWDevConfig->ulMSPICFG4 & SPI_MSPI_SIZE_MASK);
  LucSize = (uint8)SPI_MSPI_HALF_MIN_STAGE << LucSize;

  /* Setup DMA for Rx side */
  if (SPI_INVALID_DMAUNIT != LpJobConfig->ucRxDmaIndex)
  {
    if (NULL_PTR != LpHWStat->pRxPtr)
    {
      /* If rx buffer isn't NULL, set pointer to rx buffer to DMA */
      Spi_DMAStart(                                                                                                     /* PRQA S 0404 # JV-01 */
          (uint32)LpJobConfig->ucRxDmaIndex,
          (volatile P2CONST(void, AUTOMATIC, SPI_APPL_DATA))LpHWStat->pRxPtr, (uint32)LpHWStat->usRemainedRxCount,
          (uint32)LpChConfig->ucByteSize | SPI_DMA_INCDST | SPI_DMA_INTERRUPT | SPI_DMA_TC(LucSize));                   /* PRQA S 3469 # JV-01 */
    }
    else
    {
      /* If rx buffer is NULL, set pointer to the dummy variable to DMA */
      Spi_DMAStart((uint32)LpJobConfig->ucRxDmaIndex,
                   (volatile P2CONST(void, AUTOMATIC, SPI_APPL_DATA)) & Spi_GulDmaRxData,
                   (uint32)LpHWStat->usRemainedRxCount,
                   (uint32)LpChConfig->ucByteSize | SPI_DMA_INTERRUPT | SPI_DMA_TC(LucSize));                           /* PRQA S 3469 # JV-01 */
    }
  } /* else No action required */
  /* Setup DMA for Tx side */
  if (SPI_INVALID_DMAUNIT != LpJobConfig->ucTxDmaIndex)
  {
    if (NULL_PTR != LpHWStat->pTxPtr)
    {
      /* If tx buffer isn't NULL, set pointer to tx buffer to DMA */
      Spi_DMAStart((uint32)LpJobConfig->ucTxDmaIndex,                                                                   /* PRQA S 0404 # JV-01 */
                   (volatile P2CONST(void, AUTOMATIC, SPI_APPL_DATA))LpHWStat->pTxPtr,
                   (uint32)LpHWStat->usRemainedTxCount,
                   (uint32)LpChConfig->ucByteSize | SPI_DMA_INCSRC | SPI_DMA_TC(LucSize));                              /* PRQA S 3469 # JV-01 */
    }
    else
    {
      /* If tx buffer is NULL, set pointer to the default data to DMA */
      Spi_DMAStart((uint32)LpJobConfig->ucTxDmaIndex,
                   (volatile P2CONST(void, AUTOMATIC, SPI_APPL_DATA)) & LpChConfig->ulDefaultData,
                   (uint32)LpHWStat->usRemainedTxCount, (uint32)LpChConfig->ucByteSize | SPI_DMA_TC(LucSize));          /* PRQA S 3469 # JV-01 */
    }
  } /* else No action required */
  #endif /* (SPI_DMA_CONFIGURED == STD_ON) */

  /* Set ChipSelect field of MSPInSSELm  register */
  LusCS = LpJobConfig->usCSInfo;

  /* ChipSelect/Job Enable and Start transmission setting */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWChannel].usSSEL = LusCS;

  /* Set MSPI RAM address */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWChannel].usRASTAD = LpHWDevConfig->usMSPIRASTAD;

  /* Set channel enable flag of MSPInCSTS */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWChannel].ucCSTS = SPI_MSPI_CHENS;

  /* Check if sync transmission or the first channel of a job or SW trigger is configured */
  if ((0UL != (Spi_GulActiveHWUnits & (1UL << LpJobConfig->ucHWUnitIndex))) || (0U != LpHWStat->ucTxChannelCount) ||    /* PRQA S 3416 # JV-01 */
      (0UL == (SPI_MSPI_HWTS_MASK & LpHWDevConfig->ulMSPICFG4)))
  {
    /* Set channel active flag of MSPInCSTS */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulHWChannel].ucCSTS = SPI_MSPI_ACTFS;
  } /* else No action required */
}
#endif /* (SPI_FIXED_FIFO_MODE == STD_ON) */

/***********************************************************************************************************************
** Function Name      : Spi_MSPITransmitSyncJob
**
** Service ID         : Not Applicable
**
** Description        : This service is used for transmitting the sequences synchronously
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters   : LpJobConfig - Pointer to the Job configuration
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType (E_OK/E_NOT_OK)
**
** Preconditions      : Spi_Init must have been invoked.
**
** Global Variables   : Spi_GpFirstHWUnit, Spi_GaaHWStatus, Spi_GpFirstDMAUnit, Spi_GaaMSPIRegs,
**                      Spi_GpConfigPtr, Spi_GaaJobStatus, Spi_GaaSeqStatus, Spi_GaaMSPIOredISRRegs
**
** Function Invoked   : SPI_DEM_REPORT_ERROR, Spi_MSPIProcessJob, Spi_MSPIFrameEndISR, Spi_MSPIReceiveISR,
**                      Spi_MSPITransmitISR, Spi_DMAClearInterruptFlag, Spi_DMAGetInterruptFlag, Spi_MSPIDMACompleteISR
**
** Registers Used     : EIC(INTMSPInTXm), EIC(INTMSPInRXm), EIC(INTMSPInFEm), EIC(INTMSPInERRm), INTMSPICTSMONn, 
**                      INTMSPICTRSMONn, INTMSPICFCMONn
**
** Reference ID       : SPI_DUD_ACT_063, SPI_DUD_ACT_063_ERR001, SPI_DUD_ACT_063_GBL001, SPI_DUD_ACT_063_GBL002,
** Reference ID       : SPI_DUD_ACT_063_REG001, SPI_DUD_ACT_063_REG002, SPI_DUD_ACT_063_REG003, SPI_DUD_ACT_063_REG004,
** Reference ID       : SPI_DUD_ACT_063_REG005
***********************************************************************************************************************/
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
STATIC FUNC(Std_ReturnType, SPI_PRIVATE_CODE)
    Spi_MSPITransmitSyncJob(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig)                    /* PRQA S 3006 # JV-01 */
{
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWUnitInfo;
  volatile P2VAR(Spi_HWStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpHWStat;                                                /* PRQA S 3432, 3678 # JV-01, JV-01 */

  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
  uint32 LulHWPhyIndex;
  #endif /* #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF) */

  uint32 LulWaitCount;
  Std_ReturnType LenReturnValue;
  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
  VAR(uint8, AUTOMATIC) LucIsrSelId;
  #endif
  
  #if (((SPI_DIRECT_ACCESS_MODE == STD_ON) || (SPI_FIXED_FIFO_MODE == STD_ON)) && (SPI_DMA_CONFIGURED == STD_ON))
  P2CONST(Spi_DmaConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpDmaConfig;
  uint32 LulDmaIntFlag;
  #endif

  LenReturnValue = E_OK;

  /* Get the base address of the HW Unit */
  LpHWUnitInfo = &Spi_GpFirstHWUnit[LpJobConfig->ucHWUnitIndex];
  LpHWStat = &Spi_GaaHWStatus[LpJobConfig->ucHWUnitIndex];

  #if (((SPI_DIRECT_ACCESS_MODE == STD_ON) || (SPI_FIXED_FIFO_MODE == STD_ON)) && (SPI_DMA_CONFIGURED == STD_ON))
  if (SPI_INVALID_DMAUNIT != LpJobConfig->ucRxDmaIndex)
  {
    LpDmaConfig = &Spi_GpFirstDMAUnit[LpJobConfig->ucRxDmaIndex];
    /* Clear TE interrupt flag */
    Spi_DMAClearInterruptFlag((uint32)LpJobConfig->ucRxDmaIndex);
  } /* else No action required */
  #endif
  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
  /* Get Ored Interrupt selection index */
  LucIsrSelId = Spi_GaaMSPIRegs[LpHWUnitInfo->ucPhyUnitIndex].ucInterruptSel;
  #endif
  
#if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
  /* Get the index of physical HW Unit */
  LulHWPhyIndex = LpHWUnitInfo->ucPhyUnitIndex;
  /* Clear EIRF flags before starting transmission */
  RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LulHWPhyIndex].pICTX, (uint16)(~SPI_EIC_EIRF_MASK));
  RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LulHWPhyIndex].pICRX, (uint16)(~SPI_EIC_EIRF_MASK));
  RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LulHWPhyIndex].pICFE, (uint16)(~SPI_EIC_EIRF_MASK));
#else
  /* Clear EIRF flags before starting transmission */
  RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX, (uint16)(~SPI_EIC_EIRF_MASK));
  RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRX, (uint16)(~SPI_EIC_EIRF_MASK));
  RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFE, (uint16)(~SPI_EIC_EIRF_MASK));
#endif
  /* Setup HW for Job and send the first data */
  Spi_MSPIProcessJob(SPI_TRUE, LpJobConfig);

  /* Loop until Job end or any error occurs */
  LulWaitCount = 0U;
  do
  {
    #if ((SPI_DIRECT_ACCESS_MODE == STD_ON) || (SPI_FIXED_FIFO_MODE == STD_ON))
    #if (SPI_DMA_CONFIGURED == STD_ON)
    if ((SPI_INVALID_DMAUNIT != LpJobConfig->ucRxDmaIndex) && (SPI_TRUE == LpDmaConfig->blRxSide))                      /* PRQA S 2962 # JV-01 */
    {
      /* Invoke DMA ISR if the IRQ is asserted */
      LulDmaIntFlag = Spi_DMAGetInterruptFlag((uint32)LpJobConfig->ucRxDmaIndex);
      if (0UL != LulDmaIntFlag)
      {
        Spi_MSPIDMACompleteISR((uint32)LpJobConfig->ucRxDmaIndex);
        /* Reset timeout count */
        LulWaitCount = 0U;
      }
      else
      {
        /* Increment timeout count */
        LulWaitCount++;                                                                                                 /* PRQA S 3383 # JV-01 */
      }
    }
    else
    #endif /* (SPI_DMA_CONFIGURED == STD_ON) */
    {
      #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
      if (0U != (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIRegs[LulHWPhyIndex].pICRX) & SPI_EIC_EIRF_MASK))
      #else
      if (0U != (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRX) & SPI_EIC_EIRF_MASK))
      #endif
      {
        /* To emulate the default interrupt priority (MSPInTX > MSPInRx),
        check MSPInTX again */
        #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
        if (0U != (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIRegs[LulHWPhyIndex].pICTX) & SPI_EIC_EIRF_MASK))
        #else
        if (0U != (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX) & SPI_EIC_EIRF_MASK))
        #endif
        {
            #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
            /* Clear pending interrupt flag */
            RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LulHWPhyIndex].pICTX, (uint16)(~SPI_EIC_EIRF_MASK));
            /* If tx interruption flag is activated, call TxISR */
            Spi_MSPITransmitISR((uint32)LpJobConfig->ucHWUnitIndex);
            #else
            if (1U == ((uint16)(*Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTSMON >> (LpHWUnitInfo->ucPhyUnitIndex)) & 1U))
            {
                /* Clear pending interrupt flag */
                RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX, (uint16)(~SPI_EIC_EIRF_MASK));

                /* If tx interruption flag is activated, call TxISR */
                Spi_MSPITransmitISR((uint32)LpJobConfig->ucHWUnitIndex);
            } /* else No action required */
            #endif
        } /* else No action required */
        #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
        /* Clear pending interrupt flag */
        RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LulHWPhyIndex].pICRX, (uint16)(~SPI_EIC_EIRF_MASK));
        /* If rx interruption flag is activated, call RxISR */
        Spi_MSPIReceiveISR((uint32)LpJobConfig->ucHWUnitIndex);
        #else
        if (1U == ((uint16)(*Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRSMON >> (LpHWUnitInfo->ucPhyUnitIndex)) & 1U))
        {
           /* Clear pending interrupt flag */
           RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRX, (uint16)(~SPI_EIC_EIRF_MASK));

           /* If rx interruption flag is activated, call RxISR */
           Spi_MSPIReceiveISR((uint32)LpJobConfig->ucHWUnitIndex);
        } /* else No action required */
        #endif
        /* Reset timeout count */
        LulWaitCount = 0U;
      }
      else
      {
        /* Increment timeout count */
        LulWaitCount++;                                                                                                 /* PRQA S 3383 # JV-01 */
      }

      #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
      if (0U != (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIRegs[LulHWPhyIndex].pICTX) & SPI_EIC_EIRF_MASK))
      #else
      if (0U != (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX) & SPI_EIC_EIRF_MASK))
      #endif
      {
        #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
        /* Clear pending interrupt flag */
        RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LulHWPhyIndex].pICTX, (uint16)(~SPI_EIC_EIRF_MASK));
        /* If tx interruption flag is activated, call TxISR */
        Spi_MSPITransmitISR((uint32)LpJobConfig->ucHWUnitIndex);
        #else
        if (1U == ((uint16)(*Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTSMON >> (LpHWUnitInfo->ucPhyUnitIndex)) & 1U))
        {
          /* Clear pending interrupt flag */
          RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX, (uint16)(~SPI_EIC_EIRF_MASK));

          /* If tx interruption flag is activated, call TxISR */
          Spi_MSPITransmitISR((uint32)LpJobConfig->ucHWUnitIndex);
        } /* else No action required */
        #endif

        /* Reset timeout count */
        LulWaitCount = 0U;
      }
      else
      {
        /* Increment timeout count */
        LulWaitCount++;                                                                                                 /* PRQA S 3383 # JV-01 */
      }
    }
    #endif /* ((SPI_DIRECT_ACCESS_MODE == STD_ON) || (SPI_FIXED_FIFO_MODE == STD_ON)) */

    #if (SPI_FIXED_BUFFER_MODE == STD_ON)
    #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
    if (0U != (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIRegs[LulHWPhyIndex].pICFE) & SPI_EIC_EIRF_MASK))
    #else
    if (0U != (RH850_SV_MODE_REG_READ_ONLY(32, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFE) & SPI_EIC_EIRF_MASK))         /* PRQA S 0310, 3305 # JV-01, JV-01 */
    #endif
    {
      #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
      /* Clear pending interrupt flag */
      RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LulHWPhyIndex].pICFE, (uint16)(~SPI_EIC_EIRF_MASK));
      /* If tx interruption flag is activated, call FrameEnd */
      Spi_MSPIFrameEndISR((uint32)LpJobConfig->ucHWUnitIndex);
      #else
      if (1U == ((uint16)(*Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFCMON >> (LpHWUnitInfo->ucPhyUnitIndex)) & 1U))
      {
        /* Clear pending interrupt flag */
        RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFE, (uint16)(~SPI_EIC_EIRF_MASK));

        /* If tx interruption flag is activated, call FrameEnd */
        Spi_MSPIFrameEndISR((uint32)LpJobConfig->ucHWUnitIndex);
      } /* else No action required */
      #endif

      /* Reset timeout count */
      LulWaitCount = 0U;
    }
    else
    {
      /* Increment timeout count */
      LulWaitCount++;                                                                                                   /* PRQA S 3383 # JV-01 */
    }
    #endif /* (SPI_FIXED_BUFFER_MODE == STD_ON) */

    /* Check timeout */
    if (Spi_GpConfigPtr->ulTimeoutCount <= LulWaitCount)                                                                /* PRQA S 3416 # JV-01 */
    {
      #if (STD_ON == SPI_E_DATA_TX_TIMEOUT_FAILURE_CONFIGURED)
      SPI_DEM_REPORT_ERROR(SPI_E_DATA_TX_TIMEOUT_FAILURE, DEM_EVENT_STATUS_FAILED);
      #endif
      Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult = SPI_JOB_FAILED;
      /* At least one Job failed, set Sequence failed flag */
      Spi_GaaSeqStatus[LpHWStat->ucOngoingSeqIndex].blFailed = SPI_TRUE;
      LenReturnValue = E_NOT_OK;
    } /* else No action required */
  
    /* DummyRead & SYNCP */
    #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
    RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIRegs[0].pICRX);
    #else
    RH850_SV_MODE_REG_READ_ONLY(32, Spi_GaaMSPIOredISRRegs[0].pICRSMSK);
    RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIOredISRRegs[0].pICRX);
    #endif
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  } while ((E_OK == LenReturnValue) && (LpHWStat->ucRxChannelCount < LpJobConfig->ucNoOfChannels));


  /* If any HW error has been occurred, return E_NOT_OK */
  if (SPI_TRUE == Spi_GaaSeqStatus[LpHWStat->ucOngoingSeqIndex].blFailed)                                               /* PRQA S 0404 # JV-01 */
  {
    LenReturnValue = E_NOT_OK;
  } /* else No action required */

  return (LenReturnValue);
}
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

/***********************************************************************************************************************
** Function Name      : Spi_LoadTxData
**
** Service ID         : Not Applicable
**
** Description        : This function loads data from the buffer and encode it to send with TXDA0 register
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant
**
** Input Parameters   : LpData       - Pointer to the buffer to load data from
**                      LpChConfig   - Pointer to the Channel configuration
**
** InOut Parameters   : None
**
** Output Parameters  : LpOutData    - Pointer to store the data of MSPInTXDAm0
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : None
**
** Reference ID       : SPI_DUD_ACT_064
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_LoadTxData(volatile CONSTP2CONST(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) LpData,
                   CONSTP2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig,
                   volatile CONSTP2VAR(uint32, AUTOMATIC, AUTOMATIC) LpOutData)                                         /* PRQA S 3432 # JV-01 */
{
  uint32 LulData;

  /* Load data from memory according to the access size */
  if (NULL_PTR == LpData)
  {
    LulData = LpChConfig->ulDefaultData;
  }
  else
  {
    switch (LpChConfig->ucByteSize)
    {
    case sizeof(uint32):
      LulData = *(volatile P2CONST(uint32, AUTOMATIC, SPI_APPL_DATA))LpData;                                            /* PRQA S 3305, 0310 # JV-01, JV-01 */
      break;
    case sizeof(uint16):
      LulData = *(volatile P2CONST(uint16, AUTOMATIC, SPI_APPL_DATA))LpData;                                            /* PRQA S 0310, 3305 # JV-01, JV-01 */
      break;
    default:
      LulData = *LpData;
      break;
    }
  }

  *LpOutData = LulData;
}

/***********************************************************************************************************************
** Function Name      : Spi_StoreRxData
**
** Service ID         : Not Applicable
**
** Description        : This function merges two word from RXDA0 register and stores it to the buffer
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant
**
** Input Parameters   : LpChConfig    - Pointer to the Channel configuration
**                      LulInData     - The data from MSPInRXDAm0 register
**
** InOut Parameters   : None
**
** Output Parameters  : LpData        - Pointer to the buffer to store data to
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : None
**
** Reference ID       : SPI_DUD_ACT_065
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_StoreRxData(volatile CONSTP2VAR(Spi_DataBufferType, AUTOMATIC, SPI_APPL_DATA) LpData,                           /* PRQA S 3432 # JV-01 */
                    CONSTP2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig, const uint32 LulInData)
{
  uint32 LulData;

  LulData = (uint32)LulInData;

  /* Store data to memory according to the access size */
  switch (LpChConfig->ucByteSize)
  {
  case sizeof(uint32):
    *(volatile P2VAR(uint32, AUTOMATIC, SPI_APPL_DATA))LpData = LulData;                                                /* PRQA S 3305, 0310, 3432 # JV-01, JV-01, JV-01 */
    break;
  case sizeof(uint16):
    *(volatile P2VAR(uint16, AUTOMATIC, SPI_APPL_DATA))LpData = (uint16)LulData;                                        /* PRQA S 3305, 0310, 3432 # JV-01, JV-01, JV-01 */
    break;
  default:
    *LpData = (uint8)LulData;
    break;
  }
}

/***********************************************************************************************************************
** Function Name      : Spi_MSPITransmitISR
**
** Service ID         : Not Applicable
**
** Description        : This is the interrupt service routine for transmission
**                      This ISR is invoked when the following case:
**                      DIRECT_ACCESS_MODE    : every transmission complete
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters   : LulHWUnitIndex - Index of HWUnit configuration
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Spi_Init must have been invoked.
**
** Global Variable    : Spi_GpFirstHWUnit, Spi_GaaHWStatus, Spi_GaaMSPIRegs, Spi_GpFirstJob, Spi_GpFirstChannel
**
** Function Invoked   : Spi_LoadTxData
**
** Registers Used     : MSPInINTFk, MSPInTXDA, MSPInINTFCk, MSPInCFGm4, MSPInINTMSKk
**
** Reference ID       : SPI_DUD_ACT_073, SPI_DUD_ACT_073_GBL002, SPI_DUD_ACT_073_GBL003,
** Reference ID       : SPI_DUD_ACT_073_GBL004, SPI_DUD_ACT_073_GBL005, SPI_DUD_ACT_073_REG001, SPI_DUD_ACT_073_REG003
** Reference ID       : SPI_DUD_ACT_073_REG004, SPI_DUD_ACT_073_REG005
***********************************************************************************************************************/
FUNC(void, SPI_PRIVATE_CODE) Spi_MSPITransmitISR(const uint32 LulHWUnitIndex)                                           /* PRQA S 1505 # JV-01 */
{
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;
  volatile P2VAR(Spi_HWStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpHWStat;                                                /* PRQA S 3432 # JV-01 */
  P2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig;
  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;
  P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig;

  uint32 LulHWPhyIndex;
  uint32 LulPhyChannel;
  uint32 LulSndData;
  uint32 LulINTFactor;
  uint32 LulBurstCount;
  #if (SPI_MSPI_NOT_SUPPORT_RX_BUFFER_FULL == STD_ON)
  uint32 LulBkBurstCount;
  uint16 LusNofChBuffer;
  #endif

  /* Get pointers and index relevant to HW */
  LpHWInfo = &Spi_GpFirstHWUnit[LulHWUnitIndex];
  LulHWPhyIndex = LpHWInfo->ucPhyUnitIndex;
  LpHWStat = &Spi_GaaHWStatus[LulHWUnitIndex];

  LpJobConfig = &Spi_GpFirstJob[LpHWStat->usOngoingJobIndex];                                                           /* PRQA S 0404 # JV-01 */

  LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;             /* PRQA S 0316 # JV-01 */

  LulPhyChannel = LpHWDevConfig->ucPhyChannelIndex;
  /* Mask Tx interrupt output of the corresponding MSPI channel to INTC2 */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK0 |= 1UL << LulPhyChannel;

  /* Get the interrupt factor */
  LulINTFactor = Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTF0;

  /* Clear the interrupt factor */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTFC0 = LulINTFactor;

  LpChConfig = &Spi_GpFirstChannel[LpJobConfig->pChannelList[LpHWStat->ucTxChannelCount]];                              /* PRQA S 0404 # JV-01 */

  /* Check a memory mode */
  if (SPI_MEMORYMODE_FIXED_FIFO == LpHWDevConfig->enMemoryMode)
  {
    /* Fixed FIFO memory mode */
    /* Set the number of free buffers */
    LulBurstCount = (uint32)(LpHWDevConfig->ulMSPICFG4 & SPI_MSPI_SIZE_MASK);
    LulBurstCount = (uint32)SPI_MSPI_HALF_MIN_STAGE << LulBurstCount;
  }
  else
  {
    /* Direct access memory mode, set to one */
    LulBurstCount = 1U;
  }

  #if (SPI_MSPI_NOT_SUPPORT_RX_BUFFER_FULL == STD_ON)
  /* Back up burst count */
  LulBkBurstCount = LulBurstCount;
  #endif

  /* Check whether a Channel is finished */
  if (0U == LpHWStat->usRemainedTxCount)
  {
    /* When a Channel is finished, increment Channel count */
    LpHWStat->ucTxChannelCount++;                                                                                       /* PRQA S 3387, 3383 # JV-01, JV-01 */

    /*
     * There are remained Channels and all Channel properties are same, setup buffer for the next channel and continue
     * the operation. Otherwise this operation will be done by RxISR.
     */
    if ((LpHWStat->ucTxChannelCount < LpJobConfig->ucNoOfChannels) &&
        (SPI_MEMORYMODE_DIRECT == LpHWDevConfig->enMemoryMode)
        #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_OFF)
        && (SPI_TRUE == LpJobConfig->blChannelPropertySame)
        #endif
    )
    {
      LpChConfig = &Spi_GpFirstChannel[LpJobConfig->pChannelList[LpHWStat->ucTxChannelCount]];                          /* PRQA S 0404 # JV-01 */
      #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
      if (SPI_BUFFER_TYPE_IB == LpChConfig->enChannelBufferType)
      #endif
      {
        #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
        /* Store Tx buffer, the number of buffer of next channel */
        LpHWStat->pTxPtr = LpChConfig->pTxBuffer;
        LpHWStat->usRemainedTxCount = LpChConfig->usNoOfBuffers;
        #endif
      }
      #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
      else
      #endif
      {
        #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_EB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
        /* Store Tx buffer, the number of buffer of next channel */
        LpHWStat->pTxPtr = LpChConfig->pEBData->pSrcPtr;
        LpHWStat->usRemainedTxCount = LpChConfig->pEBData->usEBLength;
        #endif
      }
    }
    else
    {
      /* Do not process next channel */
      LulBurstCount = 0UL;
    }
  } /* if (LpHWStat->usRemainedTxCount == 0U) */

  /*
   * Loop to transmit data
   */
  while (0UL != LulBurstCount)
  {
    /* If there is the next data, send it */
    LulBurstCount--;
    /* Prepare Tx data from memory */
    Spi_LoadTxData(LpHWStat->pTxPtr, LpChConfig, &LulSndData);

    /* Increment the data pointer */
    if (NULL_PTR != LpHWStat->pTxPtr)
    {
      LpHWStat->pTxPtr = LpHWStat->pTxPtr + LpChConfig->ucByteSize;                                                     /* PRQA S 0488 # JV-01 */
    } /* else No action required */

    /* Data transmission */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulPhyChannel].ulTXDA0 = LulSndData;

    /* Decrease TxCount */
    LpHWStat->usRemainedTxCount--;                                                                                      /* PRQA S 3384, 3387 # JV-01, JV-01 */
  } /* while (0U != LulBurstCount) */

  #if (SPI_MSPI_NOT_SUPPORT_RX_BUFFER_FULL == STD_ON)
  /* The number of buffer of on-going channel */
  LusNofChBuffer = Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulPhyChannel].usCFSET;
  /* Check whether first Tx interrupt is raised */
  if (LusNofChBuffer == (LpHWStat->usRemainedTxCount + (uint16)LulBkBurstCount))
  #endif /* End of (SPI_MSPI_NOT_SUPPORT_RX_BUFFER_FULL == STD_ON) */
  {
    /* Un-mask Tx interrupt for next transmission */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK0 &= ~(1UL << LulPhyChannel);
  } /* else No action required */
}

/***********************************************************************************************************************
** Function Name      : Spi_MSPIReceiveISR
**
** Service ID         : Not Applicable
**
** Description        : This is the interrupt service routine for MSPI
**                      This is invoked when the following case:
**                      DIRECT_ACCESS_MODE    : every reception complete
**
** Sync/Async         : Asynchronous
**
** Re-entrancy        : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters   : LulHWUnitIndex - Index of HWUnit configuration
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Spi_Init must have been invoked.
**
** Global Variable    : Spi_GpFirstHWUnit, Spi_GaaHWStatus, Spi_GaaMSPIRegs, Spi_GulActiveHWUnits, Spi_GpFirstJob,
**                      Spi_GpFirstChannel, Spi_GaaJobStatus, Spi_GaaSeqStatus
**
** Function Invoked   : SPI_DEM_REPORT_ERROR, Spi_StoreRxData, Spi_MSPIProcessJob, Spi_ProcessSequence,
**                      Spi_TurnOffHWUnit, Spi_MSPIHWControlCS
**
** Registers Used     : MSPInINTFk, MSPInRXDAm, MSPInINTFCk, MSPInFRERSTm, MSPInCSTSm, MSPInFRERSTCm, MSPInCESTm,
**                      MSPInCESTCm, MSPInCFSETm, MSPInINTMSKk
**
** Reference ID       : SPI_DUD_ACT_074, SPI_DUD_ACT_074_ERR001, SPI_DUD_ACT_074_ERR002, SPI_DUD_ACT_074_GBL001,
** Reference ID       : SPI_DUD_ACT_074_GBL002, SPI_DUD_ACT_074_GBL003, SPI_DUD_ACT_074_GBL004, SPI_DUD_ACT_074_GBL005,
** Reference ID       : SPI_DUD_ACT_074_GBL006, SPI_DUD_ACT_074_GBL007, SPI_DUD_ACT_074_GBL008, SPI_DUD_ACT_074_GBL009,
** Reference ID       : SPI_DUD_ACT_074_GBL010, SPI_DUD_ACT_074_GBL011, SPI_DUD_ACT_074_REG001, SPI_DUD_ACT_074_REG002,
** Reference ID       : SPI_DUD_ACT_074_REG003, SPI_DUD_ACT_074_REG004, SPI_DUD_ACT_074_REG005, SPI_DUD_ACT_074_REG006,
** Reference ID       : SPI_DUD_ACT_074_REG007, SPI_DUD_ACT_074_GBL012, SPI_DUD_ACT_074_REG008, SPI_DUD_ACT_074_ERR003
***********************************************************************************************************************/
FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIReceiveISR(const uint32 LulHWUnitIndex)                                            /* PRQA S 1505 # JV-01 */
{
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;
  volatile P2VAR(Spi_HWStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpHWStat;                                                /* PRQA S 3432 # JV-01 */
  P2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig;
  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;
  P2CONST(Spi_ChannelConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpChConfig;

  uint32 LulHWPhyIndex;
  uint32 LulINTFactor;
  uint32 LulPhyChannel;
  uint32 LulRcvData;
  uint32 LulBurstCount;
  uint32 LulWaitCount;

  LpHWInfo = &Spi_GpFirstHWUnit[LulHWUnitIndex];
  LulHWPhyIndex = LpHWInfo->ucPhyUnitIndex;
  LpHWStat = &Spi_GaaHWStatus[LulHWUnitIndex];

  LpJobConfig = &Spi_GpFirstJob[LpHWStat->usOngoingJobIndex];                                                           /* PRQA S 0404 # JV-01 */

  LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;             /* PRQA S 0316 # JV-01 */

  LulPhyChannel = LpHWDevConfig->ucPhyChannelIndex;
  /* Mask Rx interrupt output of the corresponding MSPI channel to INTC2 */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK1 |= 1UL << LulPhyChannel;

  /* Get the interrupt factor */
  LulINTFactor = Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTF1;

  /* Clear the interrupt factor */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTFC1 = LulINTFactor;

  LpChConfig = &Spi_GpFirstChannel[LpJobConfig->pChannelList[LpHWStat->ucRxChannelCount]];                              /* PRQA S 0404 # JV-01 */

  /* Check a memory mode */
  if (SPI_MEMORYMODE_FIXED_FIFO == LpHWDevConfig->enMemoryMode)
  {
    /* Fixed FIFO memory mode */
    /* Set the number of free buffers */
    LulBurstCount = (uint32)(LpHWDevConfig->ulMSPICFG4 & SPI_MSPI_SIZE_MASK);
    LulBurstCount = (uint32)SPI_MSPI_HALF_MIN_STAGE << LulBurstCount;
  }
  else
  {
    /* Direct access memory mode, set to one */
    LulBurstCount = 1U;
  }

  /* Read reception data */
  do
  {
    /* Receive and store data to memory */
    LulRcvData = Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulPhyChannel].ulRXDA0;

    if (NULL_PTR != LpHWStat->pRxPtr)
    {
      Spi_StoreRxData(LpHWStat->pRxPtr, LpChConfig, LulRcvData);

      LpHWStat->pRxPtr = LpHWStat->pRxPtr + LpChConfig->ucByteSize;                                                     /* PRQA S 0488 # JV-01 */
    } /* else No action required */
    /* Decrease the number of Rx data in a channel */
    LpHWStat->usRemainedRxCount--;                                                                                      /* PRQA S 3384, 3387 # JV-01, JV-01 */
    /* Decrease burst count */
    LulBurstCount--;                                                                                                    /* PRQA S 3383 # JV-01 */
  } while (0UL != LulBurstCount);

  #if (SPI_MSPI_NOT_SUPPORT_RX_BUFFER_FULL == STD_ON)
  if (0UL != (Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTF0 & (1UL << LulPhyChannel)))
  {
    /* Transmit next data if there is a Tx request */
    Spi_MSPITransmitISR(LulHWUnitIndex);
  }
  else
  {
    /* Unmask Tx interrupt for next transmission */
    Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK0 &= ~(1UL << LulPhyChannel);
  }
  #endif

  /* Check whether a Channel is finished */
  if (0U == LpHWStat->usRemainedRxCount)
  {
    /* Increase channel count for next channel */
    LpHWStat->ucRxChannelCount++;                                                                                       /* PRQA S 3383, 3387 # JV-01, JV-01 */

    /* Check whether any error has been occurred during a frame in Direct memory access mode*/
    if ((SPI_MEMORYMODE_DIRECT == LpHWDevConfig->enMemoryMode) &&
        (SPI_MSPI_NO_ERR !=
         (uint8)(Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LpHWDevConfig->ucPhyChannelIndex].ucFRERST &
                 (uint8)(SPI_MSPI_DCEFST | SPI_MSPI_CEFST | SPI_MSPI_PEFST))))
    {
      #if (STD_ON == SPI_E_HARDWARE_ERROR_CONFIGURED)
      SPI_DEM_REPORT_ERROR(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
      #endif
      Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LpHWDevConfig->ucPhyChannelIndex].ucFRERSTC =
          (uint8)(SPI_MSPI_DCEFSC | SPI_MSPI_CEFSC | SPI_MSPI_PEFSC);

      /* Update Job result as FAILED */
      Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult = SPI_JOB_FAILED;
      /* A least one Job failed, set Sequence failed flag */
      Spi_GaaSeqStatus[LpHWStat->ucOngoingSeqIndex].blFailed = SPI_TRUE;
    } /* else No action required */

    /* Check whether any error has been occurred during a Channel */
    if (SPI_MSPI_NO_ERR !=
        (uint8)(Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LpHWDevConfig->ucPhyChannelIndex].ucCEST &
                (uint8)(SPI_MSPI_OVREE | SPI_MSPI_OVWRE | SPI_MSPI_OVRUE | SPI_MSPI_DCE | SPI_MSPI_CE | SPI_MSPI_PE)))
    {
      #if (STD_ON == SPI_E_HARDWARE_ERROR_CONFIGURED)
      SPI_DEM_REPORT_ERROR(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
      #endif
      Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LpHWDevConfig->ucPhyChannelIndex].ucCESTC =
          (uint8)(SPI_MSPI_OVREEC | SPI_MSPI_OVWREC | SPI_MSPI_OVRUEC | SPI_MSPI_DCEC | SPI_MSPI_CEC | SPI_MSPI_PEC);

      /* Update Job result as FAILED */
      Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult = SPI_JOB_FAILED;
      /* A least one Job failed, set Sequence failed flag */
      Spi_GaaSeqStatus[LpHWStat->ucOngoingSeqIndex].blFailed = SPI_TRUE;
    } /* else No action required */

    /* Check whether a Job is finished */
    if (LpHWStat->ucRxChannelCount == LpJobConfig->ucNoOfChannels)
    {

      /* Loop until the communication status is completed */
      LulWaitCount = 0U;

      /* Wait until MSPInSTR0.MSPInCSF becomes 0. */
      while (((Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucSTR0 & SPI_MSPI_STR0_CSF) == SPI_MSPI_STR0_CSF) && \
                                                                      (LulWaitCount < Spi_GpConfigPtr->ulTimeoutCount)) /* PRQA S 3416, 3415 # JV-01, JV-01 */
      {
        LulWaitCount++;
      }

      /* Check timeout */
      if (Spi_GpConfigPtr->ulTimeoutCount <= LulWaitCount)                                                              /* PRQA S 3416 # JV-01 */
      {
        #if (STD_ON == SPI_E_HARDWARE_ERROR_CONFIGURED)
        SPI_DEM_REPORT_ERROR(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
        #endif
        Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult = SPI_JOB_FAILED;                                        /* PRQA S 2844 # JV-01 */
        /* Set Sequence failed flag */
        Spi_GaaSeqStatus[LpHWStat->ucOngoingSeqIndex].blFailed = SPI_TRUE;
      } /* else No action required */

      /* Disable MSPI unit to de-activate CS when the job finishes (SWS_Spi_00263)
      * Disable MSPI unit interrupts associated with job.
      */
      Spi_TurnOffHWUnit(LpJobConfig);
      #if (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON)
      /* Check if job is configured with CS as GPIO */
      if (SPI_GPIO_CS == LpJobConfig->enCSType)
      {
        /* Deactivate the chip select via selected GPIO port pin */
        Spi_MSPIHWControlCS(LpJobConfig, SPI_FALSE);
      }
      #endif /* (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON) */
      /* All Channels in a Job are completed */
      if (SPI_JOB_FAILED != Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult)                                     /* PRQA S 0404 # JV-01 */
      {
        Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult = SPI_JOB_OK;
      } /* else No action required */
      #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
      if (0UL != (Spi_GulActiveHWUnits & (1UL << LulHWUnitIndex)))                                                      /* PRQA S 3416 # JV-01 */
      {
        /* When SyncTransmit, scheduling is done by Spi_SyncTransmit */
      }
      else
      #endif
      {
        #if (SPI_LEVEL_DELIVERED != SPI_LEVEL_0)
        /* Invoke the upper layer scheduler */
        Spi_ProcessSequence(LulHWUnitIndex);
        #endif
      }
    } /* if (LpHWStat->ucRxChannelCount == LpJobConfig->ucNoOfChannels) */
    else
    {
      LpChConfig = &Spi_GpFirstChannel[LpJobConfig->pChannelList[LpHWStat->ucRxChannelCount]];                          /* PRQA S 0404 # JV-01 */
      if ((SPI_MEMORYMODE_FIXED_FIFO == LpHWDevConfig->enMemoryMode)
      #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_OFF)
          || (SPI_FALSE == LpJobConfig->blChannelPropertySame)
      #endif /* (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_OFF) */
      )
      {
        /*
         * If ChannelProperty is not same, TxChannelCount is not updated because TxISR never occur on the last data.
         * Hence update it here.
         */
        LpHWStat->ucTxChannelCount = LpHWStat->ucRxChannelCount;
        /* Start the next Channel */
        Spi_MSPIProcessJob(SPI_FALSE, &Spi_GpFirstJob[LpHWStat->usOngoingJobIndex]);                                    /* PRQA S 0404 # JV-01 */
      }
      else
      {
        /*
         * When a channel is completed and all channel properties are same, setup buffer for the next channel and
         * continue the operation. Otherwise, call job scheduler.
         */
        #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
        if (SPI_BUFFER_TYPE_IB == LpChConfig->enChannelBufferType)
        #endif
        {
          #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
          LpHWStat->pRxPtr = LpChConfig->pRxBuffer;
          LpHWStat->usRemainedRxCount = LpChConfig->usNoOfBuffers;
          /* Set CFSET again for next channel */
          Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulPhyChannel].usCFSET = LpChConfig->usNoOfBuffers;
          #endif
        }
        #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)
        else
        #endif
        {
          #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_EB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
          LpHWStat->pRxPtr = LpChConfig->pEBData->pDestPtr;
          LpHWStat->usRemainedRxCount = LpChConfig->pEBData->usEBLength;
          /* Set CFSET again for next channel */
          Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulPhyChannel].usCFSET = LpChConfig->pEBData->usEBLength;
          #endif
        }
        /* Need to enable channel again to start transmission */
        Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LulPhyChannel].ucCSTS = SPI_MSPI_CHENS | SPI_MSPI_ACTFS;
      } /* else (SPI_FALSE == LpJobConfig->blChannelPropertySame) */
    }   /* else (LpHWStat->ucRxChannelCount == LpJobConfig->ucNoOfChannels) */
  }     /* else (0U == LpHWStat->usRemainedRxCount) */

  /* Un-mask Rx interrupt output of the corresponding MSPI channel to INTC2 */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK1 &= ~(1UL << LulPhyChannel);
}

#if (SPI_FIXED_BUFFER_MODE == STD_ON)
/***********************************************************************************************************************
** Function Name      : Spi_MSPIFrameEndISR
**
** Service ID         : Not Applicable
**
** Description        : This is the interrupt service routine for frame count end
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters   : LulHWUnitIndex - Index of HWUnit configuration
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Spi_Init must have been invoked.
**
** Global Variable    : Spi_GpFirstHWUnit, Spi_GaaMSPIRegs, Spi_GaaHWStatus, Spi_GpFirstJob,
**                      Spi_GaaJobStatus, Spi_GaaSeqStatus, Spi_GulActiveHWUnits
**
** Function Invoked   : Spi_ProcessSequence, Spi_TurnOffHWUnit, Spi_MSPIProcessJob, SPI_DEM_REPORT_ERROR, 
**                      Spi_MSPIHWControlCS
**
** Registers Used     : MSPInINTFk, MSPInINTFCk, MSPInCESTm, MSPInCESTCm
**
** Reference ID       : SPI_DUD_ACT_075, SPI_DUD_ACT_075_ERR002, SPI_DUD_ACT_075_REG003, SPI_DUD_ACT_075_GBL008
** Reference ID       : SPI_DUD_ACT_075_GBL005, SPI_DUD_ACT_075_GBL006, SPI_DUD_ACT_075_GBL007,
** Reference ID       : SPI_DUD_ACT_075_REG001, SPI_DUD_ACT_075_REG002, SPI_DUD_ACT_075_ERR001,
***********************************************************************************************************************/
FUNC(void, SPI_CODE_FAST) Spi_MSPIFrameEndISR(const uint32 LulHWUnitIndex)
{
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;
  volatile P2VAR(Spi_HWStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpHWStat;                                                /* PRQA S 3432 # JV-01 */
  P2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig;
  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;
  uint32 LulHWPhyIndex;
  uint32 LulINTFactor;
  uint32 LulWaitCount;

  /* Get pointers and index relevant to HW */
  LpHWInfo = &Spi_GpFirstHWUnit[LulHWUnitIndex];
  LulHWPhyIndex = LpHWInfo->ucPhyUnitIndex;

  /* Get the interrupt factor */
  LulINTFactor = Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTF2;
  /* Clear the interrupt factor */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTFC2 = LulINTFactor;

  LpHWStat = &Spi_GaaHWStatus[LulHWUnitIndex];

  LpJobConfig = &Spi_GpFirstJob[LpHWStat->usOngoingJobIndex];                                                           /* PRQA S 0404 # JV-01 */

  LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;             /* PRQA S 0316 # JV-01 */

  /* When a Channel is finished, increment Channel count */
  LpHWStat->ucTxChannelCount++;                                                                                         /* PRQA S 3383, 3387 # JV-01, JV-01 */
  LpHWStat->ucRxChannelCount++;                                                                                         /* PRQA S 3387, 3383 # JV-01, JV-01 */

  /* Check whether any error has been occurred during a Channel */
  if (SPI_MSPI_NO_ERR != (uint8)(Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LpHWDevConfig->ucPhyChannelIndex].ucCEST &
                                 (uint8)(SPI_MSPI_DCE | SPI_MSPI_CE | SPI_MSPI_PE)))
  {
    #if (STD_ON == SPI_E_HARDWARE_ERROR_CONFIGURED)
    SPI_DEM_REPORT_ERROR(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
    #endif
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LpHWDevConfig->ucPhyChannelIndex].ucCESTC =
        (uint8)(SPI_MSPI_DCEC | SPI_MSPI_CEC | SPI_MSPI_PEC);

    /* Update Job result as FAILED */
    Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult = SPI_JOB_FAILED;
    /* A least one Job failed, set Sequence failed flag */
    Spi_GaaSeqStatus[LpHWStat->ucOngoingSeqIndex].blFailed = SPI_TRUE;
  } /* else No action required */

  /* Check whether a Job is finished */
  if (LpHWStat->ucRxChannelCount == LpJobConfig->ucNoOfChannels)
  {
    /* Loop until the communication status is completed */
    LulWaitCount = 0U;

    /* Wait until MSPInSTR0.MSPInCSF becomes 0. */
    while (((Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucSTR0 & SPI_MSPI_STR0_CSF) == SPI_MSPI_STR0_CSF) && \
                                                                    (LulWaitCount < Spi_GpConfigPtr->ulTimeoutCount))   /* PRQA S 3416, 3415 # JV-01, JV-01 */
    {
      LulWaitCount++;
    }

    /* Check timeout */
    if (Spi_GpConfigPtr->ulTimeoutCount <= LulWaitCount)                                                                /* PRQA S 3416 # JV-01 */
    {
      #if (STD_ON == SPI_E_HARDWARE_ERROR_CONFIGURED)
      SPI_DEM_REPORT_ERROR(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
      #endif
      Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult = SPI_JOB_FAILED;                                          /* PRQA S 2844 # JV-01 */
      /* Set Sequence failed flag */
      Spi_GaaSeqStatus[LpHWStat->ucOngoingSeqIndex].blFailed = SPI_TRUE;
    } /* else No action required */

    /* Disable MSPI unit to de-activate CS when the job finishes (SWS_Spi_00263)
     * Disable MSPI/DMA unit interrupts associated with job.
     */
    Spi_TurnOffHWUnit(LpJobConfig);
    /* Update job status */
    if (SPI_JOB_FAILED != Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult)                                       /* PRQA S 0404 # JV-01 */
    {
      Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult = SPI_JOB_OK;
    } /* else No action required */
    #if (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON)
    if (SPI_GPIO_CS == LpJobConfig->enCSType)
    {
      /* Activate the chip select */
      Spi_MSPIHWControlCS(LpJobConfig, SPI_FALSE);
    }
    #endif /* (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON) */
    #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
    if (0UL != (Spi_GulActiveHWUnits & (1UL << LulHWUnitIndex)))                                                        /* PRQA S 3416 # JV-01 */
    {
      /* When SyncTransmit, scheduling is done by Spi_SyncTransmit */
    }
    else
    #endif
    {
      #if (SPI_LEVEL_DELIVERED != SPI_LEVEL_0)
      /* Invoke the upper layer scheduler */
      Spi_ProcessSequence(LulHWUnitIndex);
      #endif
    }
  }
  else
  {
    #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_OFF)
    if (SPI_FALSE == LpJobConfig->blChannelPropertySame)
    {
      /* If properties of channels in on-going is not same, need to update HW registers */
      Spi_MSPIProcessJob(SPI_FALSE, LpJobConfig);
    }
    else
    #endif
    {
      /* Trigger for next channel */
      Spi_MSPIStartChannelFixedBufferMode(LpJobConfig, LpHWStat, LulHWPhyIndex, LpHWDevConfig->ucPhyChannelIndex);
    }
  } /* if (LpHWStat->ucRxChannelCount == LpJobConfig->ucNoOfChannels) */
}
#endif /* (SPI_FIXED_BUFFER_MODE == STD_ON) */

/***********************************************************************************************************************
** Function Name      : Spi_MSPIDMACompleteISR
**
** Service ID         : Not Applicable
**
** Description        : This function is invoked when DMA transfer is completed
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HW, Non-Reentrant for same HW
**
** Input Parameters   : LulDMAUnitIndex
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Spi_Init must have been invoked.
**
** Global Variable    : Spi_GpFirstDMAUnit, Spi_GaaHWStatus, Spi_GpFirstJob, Spi_GaaMSPIRegs, Spi_GaaJobStatus,
**                      Spi_GaaSeqStatus, Spi_GulActiveHWUnits, Spi_GpFirstHWUnit
**
** Function Invoked   : SPI_DEM_REPORT_ERROR, Spi_MSPIProcessJob, Spi_ProcessSequence, Spi_DMAClearInterruptFlag, 
**                      Spi_TurnOffHWUnit, Spi_MSPIHWControlCS
**
** Registers Used     : MSPInFRERSTm, MSPInFRERSTCm, MSPInCESTm, MSPInCESTCm
**
** Reference ID       : SPI_DUD_ACT_076, SPI_DUD_ACT_076_ERR001, SPI_DUD_ACT_076_ERR002, SPI_DUD_ACT_076_REG002
** Reference ID       : SPI_DUD_ACT_076_GBL001, SPI_DUD_ACT_076_GBL002, SPI_DUD_ACT_076_GBL003, SPI_DUD_ACT_076_GBL004,
** Reference ID       : SPI_DUD_ACT_076_GBL005, SPI_DUD_ACT_076_GBL006, SPI_DUD_ACT_076_GBL007, SPI_DUD_ACT_076_REG001
** Reference ID       : SPI_DUD_ACT_076_GBL008, SPI_DUD_ACT_076_ERR003, SPI_DUD_ACT_076_REG003
***********************************************************************************************************************/
#if (SPI_DMA_CONFIGURED == STD_ON)
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIDMACompleteISR(const uint32 LulDMAUnitIndex)
{
  volatile P2VAR(Spi_HWStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpHWStat;                                                /* PRQA S 3432 # JV-01 */
  P2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig;
  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;
  uint32 LulHWUnitIndex;
  uint32 LulHWPhyIndex;
  uint32 LulWaitCount;

  LulHWUnitIndex = Spi_GpFirstDMAUnit[LulDMAUnitIndex].ucSPIHWUnit;

  LpHWInfo = &Spi_GpFirstHWUnit[LulHWUnitIndex];
  LulHWPhyIndex = LpHWInfo->ucPhyUnitIndex;

  LpHWStat = &Spi_GaaHWStatus[LulHWUnitIndex];

  LpJobConfig = &Spi_GpFirstJob[LpHWStat->usOngoingJobIndex];                                                           /* PRQA S 0404 # JV-01 */
  LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;             /* PRQA S 0316 # JV-01 */

  /* Check whether any error has been occurred during a frame in Direct memory access mode*/
  if ((SPI_MEMORYMODE_DIRECT == LpHWDevConfig->enMemoryMode) &&
      (SPI_MSPI_NO_ERR !=
       (uint8)(Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[(uint32)LpHWDevConfig->ucPhyChannelIndex].ucFRERST &
               (uint8)(SPI_MSPI_DCEFST | SPI_MSPI_CEFST | SPI_MSPI_PEFST))))
  {
    #if (STD_ON == SPI_E_HARDWARE_ERROR_CONFIGURED)
    SPI_DEM_REPORT_ERROR(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
    #endif
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LpHWDevConfig->ucPhyChannelIndex].ucFRERSTC =
        (uint8)(SPI_MSPI_DCEFSC | SPI_MSPI_CEFSC | SPI_MSPI_PEFSC);

    /* Update Job result as FAILED */
    Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult = SPI_JOB_FAILED;
    /* A least one Job failed, set Sequence failed flag */
    Spi_GaaSeqStatus[LpHWStat->ucOngoingSeqIndex].blFailed = SPI_TRUE;
  } /* else No action required */

  /* Check whether any error has been occurred during a Channel */
  if (SPI_MSPI_NO_ERR !=
      (uint8)(Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LpHWDevConfig->ucPhyChannelIndex].ucCEST &
              (uint8)(SPI_MSPI_OVREE | SPI_MSPI_OVWRE | SPI_MSPI_OVRUE | SPI_MSPI_DCE | SPI_MSPI_CE | SPI_MSPI_PE)))
  {
    #if (STD_ON == SPI_E_HARDWARE_ERROR_CONFIGURED)
    SPI_DEM_REPORT_ERROR(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
    #endif
    Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->aaCH[LpHWDevConfig->ucPhyChannelIndex].ucCESTC =
        (uint8)(SPI_MSPI_OVREEC | SPI_MSPI_OVWREC | SPI_MSPI_OVRUEC | SPI_MSPI_DCEC | SPI_MSPI_CEC | SPI_MSPI_PEC);

    /* Update Job result as FAILED */
    Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult = SPI_JOB_FAILED;
    /* A least one Job failed, set Sequence failed flag */
    Spi_GaaSeqStatus[LpHWStat->ucOngoingSeqIndex].blFailed = SPI_TRUE;
  } /* else No action required */

  /* Clear TE interrupt flag */
  Spi_DMAClearInterruptFlag(LulDMAUnitIndex);

  LpHWStat->ucTxChannelCount++;                                                                                         /* PRQA S 3387, 3383 # JV-01, JV-01 */
  LpHWStat->ucRxChannelCount++;                                                                                         /* PRQA S 3387, 3383 # JV-01, JV-01 */
  if (LpHWStat->ucRxChannelCount == LpJobConfig->ucNoOfChannels)
  {
    /* Loop until the communication status is completed */
    LulWaitCount = 0U;

    /* Wait until MSPInSTR0.MSPInCSF becomes 0. */
    while (((Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucSTR0 & SPI_MSPI_STR0_CSF) == SPI_MSPI_STR0_CSF) && \
                                                                    (LulWaitCount < Spi_GpConfigPtr->ulTimeoutCount))   /* PRQA S 3416, 3415 # JV-01, JV-01 */
    {
      LulWaitCount++;
    }

    /* Check timeout */
    if (Spi_GpConfigPtr->ulTimeoutCount <= LulWaitCount)                                                                /* PRQA S 3416 # JV-01 */
    {
      #if (STD_ON == SPI_E_HARDWARE_ERROR_CONFIGURED)
      SPI_DEM_REPORT_ERROR(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_FAILED);
      #endif
      Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult = SPI_JOB_FAILED;                                          /* PRQA S 2844 # JV-01 */
      /* Set Sequence failed flag */
      Spi_GaaSeqStatus[LpHWStat->ucOngoingSeqIndex].blFailed = SPI_TRUE;
    } /* else No action required */

    /* Disable MSPI unit to de-activate CS when the job finishes (SWS_Spi_00263)
     * Disable MSPI/DMA unit interrupts associated with job.
     */
    Spi_TurnOffHWUnit(LpJobConfig);
    /* Update Job status */
    if (SPI_JOB_FAILED != Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult)                                       /* PRQA S 0404 # JV-01 */
    {
      Spi_GaaJobStatus[LpHWStat->usOngoingJobIndex].enResult = SPI_JOB_OK;
    } /* else No action required */
    #if (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON)
    if (SPI_GPIO_CS == LpJobConfig->enCSType)
    {
      /* Activate the chip select */
      Spi_MSPIHWControlCS(LpJobConfig, SPI_FALSE);
    }
    #endif /* (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON) */
    #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)
    if (0UL != (Spi_GulActiveHWUnits & (1UL << LulHWUnitIndex)))                                                        /* PRQA S 3416 # JV-01 */
    {
      /* When SyncTransmit, scheduling is done by Spi_SyncTransmit */
    }
    else
    #endif
    {
      #if (SPI_LEVEL_DELIVERED != SPI_LEVEL_0)
      /* Invoke the upper layer scheduler */
      Spi_ProcessSequence(LulHWUnitIndex);
      #endif
    }
  }
  else
  {
    /* Otherwise, process the next Channel */
    Spi_MSPIProcessJob(SPI_FALSE, LpJobConfig);
  }
}
#endif /* (SPI_DMA_CONFIGURED == STD_ON) */

/***********************************************************************************************************************
** Function Name      : Spi_MSPIDisableAllInterrupts
**
** Service ID         : NA
**
** Description        : This service disables interrupts for all MSPI units
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Global variables must be initialized
**
** Global Variable    : Spi_GpConfigPtr, Spi_GpFirstHWUnit, Spi_GaaMSPIRegs, Spi_GaaMSPIOredISRRegs
**
** Function invoked   : None
**
** Registers Used     : EIC(INTMSPInTXm), EIC(INTMSPInRXm), EIC(INTMSPInFEm)
**
** Reference ID       : SPI_DUD_ACT_071, SPI_DUD_ACT_071_REG001, SPI_DUD_ACT_071_REG002, SPI_DUD_ACT_071_REG003,
** Reference ID       : SPI_DUD_ACT_071_REG004, SPI_DUD_ACT_071_REG005, SPI_DUD_ACT_071_REG006, SPI_DUD_ACT_071_REG007,
** Reference ID       : SPI_DUD_ACT_071_REG008, SPI_DUD_ACT_071_REG009, SPI_DUD_ACT_071_REG010, SPI_DUD_ACT_071_REG011,
** Reference ID       : SPI_DUD_ACT_071_REG012
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIDisableAllInterrupts(void)                                                  /* PRQA S 3006 # JV-01 */
{
  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;
  uint32 LulHWUnitIndex;
  /* Scan all HWUnit informations */
  for (LulHWUnitIndex = 0U; LulHWUnitIndex < Spi_GpConfigPtr->ucNoOfHWUnits; LulHWUnitIndex++)                          /* PRQA S 3416 # JV-01 */
  {
    LpHWInfo = &Spi_GpFirstHWUnit[LulHWUnitIndex];
    if (SPI_MACRO_MSPI == LpHWInfo->ucMacroIndex)
    {
      /* Disable all interrupts unconditionally */
      RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICRX, (uint8)SPI_EIC_EIMK_MASK);               /* PRQA S 0751 # JV-01 */
      RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICTX, (uint8)SPI_EIC_EIMK_MASK);               /* PRQA S 0751 # JV-01 */
      RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICFE, (uint8)SPI_EIC_EIMK_MASK);               /* PRQA S 0751 # JV-01 */
      RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICERR, (uint8)SPI_EIC_EIMK_MASK);              /* PRQA S 0751 # JV-01 */
      /* Clear pending interrupt flags */
      RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICTX, (uint16)(~SPI_EIC_EIRF_MASK));
      RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICRX, (uint16)(~SPI_EIC_EIRF_MASK));
      RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICFE, (uint16)(~SPI_EIC_EIRF_MASK));
      RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICERR, (uint16)(~SPI_EIC_EIRF_MASK));
    } /* else No action required */
    
    /* DummyRead & SYNCP */
    RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIRegs[0].pICRX);
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  }
  #else
  VAR(uint8, AUTOMATIC) LucIsrSelId;
  /* Scan all ORed Interrupts */
  for (LucIsrSelId = 0U;  LucIsrSelId < SPI_MAX_MSPI_ORED; LucIsrSelId++)
  {
    /* Disable all interrupts unconditionally */
    RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRX, (uint8)SPI_EIC_EIMK_MASK);                       /* PRQA S 0751 # JV-01 */
    RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX, (uint8)SPI_EIC_EIMK_MASK);                       /* PRQA S 0751 # JV-01 */
    RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFE, (uint8)SPI_EIC_EIMK_MASK);                       /* PRQA S 0751 # JV-01 */
    RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICERR, (uint8)SPI_EIC_EIMK_MASK);                      /* PRQA S 0751 # JV-01 */
    /* Clear pending interrupt flags */
    RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX, (uint16)(~SPI_EIC_EIRF_MASK));
    RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRX, (uint16)(~SPI_EIC_EIRF_MASK));
    RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFE, (uint16)(~SPI_EIC_EIRF_MASK));
    RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICERR, (uint16)(~SPI_EIC_EIRF_MASK));
  }
  /* DummyRead & SYNCP */
  RH850_SV_MODE_REG_READ_ONLY(32, Spi_GaaMSPIOredISRRegs[0].pICRSMSK);
  RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIOredISRRegs[0].pICRX);
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  #endif
}

/***********************************************************************************************************************
** Function Name      : Spi_MSPIMainFunction_Handling
**
** Service ID         : Not Applicable
**
** Description        : This function performs the polling operation
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : None
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : void
**
** Preconditions      : Spi_Init must have been invoked.
**
** Global Variable    : Spi_GpConfigPtr, Spi_GpFirstDMAUnit, Spi_GulCancelingHWUnits, Spi_GpFirstJob,
**                      Spi_GpFirstHWUnit, Spi_GulActiveHWUnits, Spi_GaaMSPIRegs, Spi_GaaMSPIOredISRRegs
**
** Function Invoked   : Spi_DMAGetInterruptFlag, Spi_MSPIFrameEndISR, Spi_MSPIReceiveISR, Spi_MSPITransmitISR,
**                      Spi_MSPIDMACompleteISR
**
** Registers Used     : EIC(INTMSPInTXm), EIC(INTMSPInRXm), EIC(INTMSPInFEm), EIC(INTMSPInERRm), INTMSPICTSMONn, 
**                      INTMSPICTSMSKn, INTMSPICTRSMONn
**
** Reference ID       : SPI_DUD_ACT_072, SPI_DUD_ACT_072_REG001, SPI_DUD_ACT_072_REG002, SPI_DUD_ACT_072_REG003,
** Reference ID       : SPI_DUD_ACT_072_REG004
***********************************************************************************************************************/
 #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIMainFunction_Handling(void)                                                 /* PRQA S 3006 # JV-01 */
{
  #if (SPI_DMA_CONFIGURED == STD_ON)
  P2CONST(Spi_DmaConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpDmaConfig;
  P2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig;
  uint32 LulDmaIndex;
  uint32 LulDmaIntFlag;
  uint32 LulJobIndex;
  #endif
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;
  uint32 LulHWUnitIndex;
  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
  VAR(uint8, AUTOMATIC) LucIsrSelId;
  #endif
  /* Scan DMA completions */
  #if (SPI_DMA_CONFIGURED == STD_ON)
  for (LulDmaIndex = 0U; LulDmaIndex < Spi_GpConfigPtr->ucNoOfDMAChannels; LulDmaIndex++)                               /* PRQA S 3416 # JV-01 */
  {
    LpDmaConfig = &Spi_GpFirstDMAUnit[LulDmaIndex];

    if (SPI_TRUE == LpDmaConfig->blRxSide)
    {
      /* Invoke DMA ISR if the IRQ is asserted */
      LulDmaIntFlag = Spi_DMAGetInterruptFlag(LulDmaIndex);
      if (
          #if (SPI_FORCE_CANCEL_API == STD_ON)
          (0UL == (Spi_GulCancelingHWUnits & (1UL << LpDmaConfig->ucSPIHWUnit))) &&                                     /* PRQA S 3416 # JV-01 */
          #endif
          (0UL != LulDmaIntFlag))
      {
        Spi_MSPIDMACompleteISR(LulDmaIndex);
      } /* else No action required */
    } /* else No action required */
  }
  #endif

  /* Scan all HWUnit informations */
  #if (SPI_DMA_CONFIGURED == STD_ON)
  /* Scan all jobs and initialize the associated HWUnits */
  for (LulJobIndex = 0U; LulJobIndex < Spi_GpConfigPtr->usNoOfJobs; LulJobIndex++)                                      /* PRQA S 3416 # JV-01 */
  {
    LpJobConfig = &Spi_GpFirstJob[LulJobIndex];
    LulHWUnitIndex = LpJobConfig->ucHWUnitIndex;
  #else
  for (LulHWUnitIndex = 0U; LulHWUnitIndex < Spi_GpConfigPtr->ucNoOfHWUnits; LulHWUnitIndex++)                          /* PRQA S 3416 # JV-01 */
  {
  #endif
    LpHWInfo = &Spi_GpFirstHWUnit[LulHWUnitIndex];
    #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
    /* Get Ored Interrupt selection index */
    LucIsrSelId = Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].ucInterruptSel;
    #endif
    /*
    Spi_GulCancelingHWUnits is modified by Spi_ForceCancel, but no critical section is required here for this variable.
    Because:
    - Spi_ForceCancel is modified in the interrupt disabled section.
    - Spi_ForceCancel can't be invoked in any higher priority task than
    Spi_MainFunction_Handling, so Spi_GulCancelHWUnits is never changed while this function is executing.
    */

    /*
    Spi_GulActiveHWUnits is modified by Spi_SyncTransmit, Spi_AsyncTransmit.
    - In case of Spi_SyncTransmit, It should not be invoked in any higher priority task than Spi_MainFunction_Handling
    for a sequence associated with on-going HW unit. Calling the API Spi_GetHWUnitStatus to check whether HW unit is
    on-going or not.
    - In case of Spi_AsyncTransmit, sequence pending state is checked before modifying Spi_GulActiveHWUnits. 
    Therefore re-entrancy between Spi_AsyncTransmit and Spi_MainFunction_Handling are not affected.
    */
    if ((SPI_MACRO_MSPI == LpHWInfo->ucMacroIndex)
        #if (SPI_AR_VERSION == SPI_AR_422_VERSION)
        && (SPI_FALSE == LpHWInfo->blSynchronous)
        #elif (SPI_AR_VERSION == SPI_AR_R22_11_VERSION)
        && (0UL == (Spi_GulActiveHWUnits & (1UL << LulHWUnitIndex)))                                                    /* PRQA S 3416, 3415 # JV-01, JV-01 */      
        #endif
        #if (SPI_FORCE_CANCEL_API == STD_ON)
        && (0UL == (Spi_GulCancelingHWUnits & (1UL << LulHWUnitIndex)))                                                 /* PRQA S 3416, 3415 # JV-01, JV-01 */
        #endif
    )
    {
      #if (SPI_FIXED_BUFFER_MODE == STD_ON)
      /* FrameEnd interruption  */
      #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
      if (0U != (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICFE) & SPI_EIC_EIRF_MASK))
      #else
      if (0U != (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFE) & SPI_EIC_EIRF_MASK))
      #endif
      {
        #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
        RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICFE, (uint16)(~SPI_EIC_EIRF_MASK));
        Spi_MSPIFrameEndISR(LulHWUnitIndex);
        #else
        if (1U == ((uint16)(*Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFCMON >> (LpHWInfo->ucPhyUnitIndex)) & 1U))
        {
           RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFE, (uint16)(~SPI_EIC_EIRF_MASK));
           Spi_MSPIFrameEndISR(LulHWUnitIndex);
        }/* else No action required */
        #endif
      } /* else No action required */
      #endif /* (SPI_FIXED_BUFFER_MODE == STD_ON) */

      #if ((SPI_DIRECT_ACCESS_MODE == STD_ON) || (SPI_FIXED_FIFO_MODE == STD_ON))
      /* Tx interruption */
      if (
          #if (SPI_DMA_CONFIGURED == STD_ON)
          (SPI_INVALID_DMAUNIT == LpJobConfig->ucTxDmaIndex) &&
          #endif
          #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
          (0U !=
           (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICTX) & SPI_EIC_EIRF_MASK)))
          #else
          (0U !=
           (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX) & SPI_EIC_EIRF_MASK)))
          #endif
      {
        #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
        RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICTX, (uint16)(~SPI_EIC_EIRF_MASK));
        Spi_MSPITransmitISR(LulHWUnitIndex);
        #else
        if (1U == ((uint16)(*Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTSMON >> (LpHWInfo->ucPhyUnitIndex)) & 1U))
        {
           RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX, (uint16)(~SPI_EIC_EIRF_MASK));
           Spi_MSPITransmitISR(LulHWUnitIndex);
        }/* else No action required */
        #endif
      } /* else No action required */

      /* Rx interruption */
      if (
          #if (SPI_DMA_CONFIGURED == STD_ON)
          (SPI_INVALID_DMAUNIT == LpJobConfig->ucRxDmaIndex) &&
          #endif
          #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
          (0U !=
           (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICRX) & SPI_EIC_EIRF_MASK)))
          #else
          (0U !=
           (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRX) & (SPI_EIC_EIRF_MASK))))
          #endif
      {
        /* To emulate the default interrupt priority (MSPInTX > MSPInRX), check MSPInTX again */
        if (
            #if (SPI_DMA_CONFIGURED == STD_ON)
            (SPI_INVALID_DMAUNIT == LpJobConfig->ucTxDmaIndex) &&
            #endif
            #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
            (0U !=
             (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICTX) & SPI_EIC_EIRF_MASK)))
            #else
            (0U !=
            (RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX) & SPI_EIC_EIRF_MASK)))
            #endif
        {
            #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
            RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICTX, (uint16)(~SPI_EIC_EIRF_MASK));
            Spi_MSPITransmitISR(LulHWUnitIndex);
            #else
            if (1U == ((uint16)(*Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTSMON >> (LpHWInfo->ucPhyUnitIndex)) & 1U))
            {
                RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX, (uint16)(~SPI_EIC_EIRF_MASK));
                Spi_MSPITransmitISR(LulHWUnitIndex);
            }/* else No action required */
            #endif
        } /* else No action required */
        #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
        RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICRX, (uint16)(~SPI_EIC_EIRF_MASK));
        Spi_MSPIReceiveISR(LulHWUnitIndex);
        #else
        if (1U == ((uint16)(*Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRSMON >> (LpHWInfo->ucPhyUnitIndex)) & 1U))
        {
            RH850_SV_MODE_ICR_AND(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRX, (uint16)(~SPI_EIC_EIRF_MASK));
            Spi_MSPIReceiveISR(LulHWUnitIndex);
        }/* else No action required */
        #endif
      } /* else No action required */
      #endif /* ((SPI_DIRECT_ACCESS_MODE == STD_ON) || (SPI_FIXED_FIFO_MODE == STD_ON)) */
    } /* else No action required */

    /* Do DummyRead & SYNCP */
    #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
    RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIRegs[0].pICRX);
    #else
    RH850_SV_MODE_REG_READ_ONLY(32, Spi_GaaMSPIOredISRRegs[0].pICTSMSK);
    RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIOredISRRegs[0].pICRX);
    #endif
    EXECUTE_SYNCP();                                                                                                    /* PRQA S 1006 # JV-01 */
  }
}
#endif /* (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) */

#if ((SPI_LEVEL_DELIVERED != SPI_LEVEL_0) && (SPI_FORCE_CANCEL_API == STD_ON))
/***********************************************************************************************************************
** Function Name      : Spi_MSPIForceStop
**
** Service ID         : Not Applicable
**
** Description        : This function stops a MSPI unit unconditionally
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HWUnit. Non-Reentrant for same HWUnit
**
** Input Parameters   : LulHWUnitIndex - Index of HW to be stopped
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : The interrupts of target HWUnit are disabled
**
** Global Variable    : Spi_GpFirstHWUnit, Spi_GaaMSPIRegs, Spi_GpFirstJob, Spi_GaaHWStatus, Spi_GaaMSPIOredISRRegs
**
** Function Invoked   : Spi_DMAStop
**
** Registers Used     : MSPInCTL0, MSPInINTFCk, EIC(INTMSPInTXm), EIC(INTMSPInRXm), EIC(INTMSPInFEm), EIC(INTMSPInERRm),
**
** Reference ID       : SPI_DUD_ACT_077, SPI_DUD_ACT_077_REG001, SPI_DUD_ACT_077_REG002, SPI_DUD_ACT_077_REG003,
** Reference ID       : SPI_DUD_ACT_077_REG004, SPI_DUD_ACT_077_REG005, SPI_DUD_ACT_077_REG006, SPI_DUD_ACT_077_REG007
** Reference ID       : SPI_DUD_ACT_077_REG008, SPI_DUD_ACT_077_REG009, SPI_DUD_ACT_077_REG010, SPI_DUD_ACT_077_REG011
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIForceStop(const uint32 LulHWUnitIndex)                                      /* PRQA S 3006 # JV-01 */
{
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;
  uint32 LulHWPhyIndex;
  #if ((SPI_DMA_CONFIGURED == STD_ON) || \
            ((SPI_MSPI_NOT_SUPPORT_RX_BUFFER_FULL == STD_ON) && (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_ON)))
  P2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig;
  #endif
  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
  VAR(uint8, AUTOMATIC) LucIsrSelId;
  #endif

  #if (SPI_MSPI_NOT_SUPPORT_RX_BUFFER_FULL == STD_ON)
  #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_ON)
  uint32 LulHWPhyChannel;
  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;
  #endif
  #endif

  #if ((SPI_DMA_CONFIGURED == STD_ON) || \
            ((SPI_MSPI_NOT_SUPPORT_RX_BUFFER_FULL == STD_ON) && (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_ON)))
  LpJobConfig = &Spi_GpFirstJob[Spi_GaaHWStatus[LulHWUnitIndex].usOngoingJobIndex];                                     /* PRQA S 0404 # JV-01 */
  #endif

  #if (SPI_MSPI_NOT_SUPPORT_RX_BUFFER_FULL == STD_ON)
  #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_ON)
  LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;             /* PRQA S 0316 # JV-01 */
  LulHWPhyChannel = LpHWDevConfig->ucPhyChannelIndex;
  #endif
  #endif

  /* Get pointers and index relevant to HW */
  LpHWInfo = &Spi_GpFirstHWUnit[LulHWUnitIndex];
  LulHWPhyIndex = LpHWInfo->ucPhyUnitIndex;
  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
  /* Get Ored Interrupt selection index */
  LucIsrSelId = Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].ucInterruptSel;
  #endif
  /* Stop SPI unit by CTL0.MSPInEN = 0 */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucCTL0 = SPI_MSPI_TURNOFF;

  /* To ensure SPI unit was stopped, do dummy read & SYNCP */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucCTL0;
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */

  #if (SPI_DMA_CONFIGURED == STD_ON)
  if (SPI_INVALID_DMAUNIT != LpJobConfig->ucRxDmaIndex)
  {
    Spi_DMAStop((uint32)LpJobConfig->ucRxDmaIndex);
  } /* else No action required */
  if (SPI_INVALID_DMAUNIT != LpJobConfig->ucTxDmaIndex)
  {
    Spi_DMAStop((uint32)LpJobConfig->ucTxDmaIndex);
  } /* else No action required */
  #endif /* (SPI_DMA_CONFIGURED == STD_ON) */

  /* Clear interrupt factor Tx */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTFC0 = Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTF0;
  /* Clear interrupt factor Rx */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTFC1 = Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTF1;
  /* Clear interrupt factor Error */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTFC2 = Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTF2;
  /* Clear interrupt factor End frame */
  Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTFC3 = Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTF3;

  #if (SPI_MSPI_NOT_SUPPORT_RX_BUFFER_FULL == STD_ON)
  #if (SPI_PERSISTENT_HW_CONFIGURATION_ENABLED == STD_ON)
  #if (SPI_DMA_CONFIGURED == STD_ON)
  if (SPI_INVALID_DMAUNIT == LpJobConfig->ucRxDmaIndex)
  #endif
  {
    /* Check memory mode configured for job */
    if (SPI_MEMORYMODE_FIXED_BUFFER != LpHWDevConfig->enMemoryMode)
    {
      /* Tx interrupts output to INTC2 un-masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK0 &= ~(1UL << LulHWPhyChannel);
      /* Rx interrupts output to INTC2 un-masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK1 &= ~(1UL << LulHWPhyChannel);
      /* FE interrupts output to INTC2 masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK2 |= (1UL << LulHWPhyChannel);
    }
    else
    {
      /* Tx interrupts output to INTC2 masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK0 |= (1UL << LulHWPhyChannel);
      /* Rx interrupts output to INTC2 masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK1 |= (1UL << LulHWPhyChannel);
      /* FE interrupts output to INTC2 un-masked */
      Spi_GaaMSPIRegs[LulHWPhyIndex].pIntfRegs->ulINTMSK2 &= ~(1UL << LulHWPhyChannel);
    }
  }
  #endif
  #endif /* #if (SPI_MSPI_NOT_SUPPORT_RX_BUFFER_FULL == STD_ON) */

  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
  /* Clear pending interrupt flags */
  RH850_SV_MODE_ICR_AND(16, (Spi_GaaMSPIRegs[LulHWPhyIndex].pICTX), (uint16)(~SPI_EIC_EIRF_MASK));
  RH850_SV_MODE_ICR_AND(16, (Spi_GaaMSPIRegs[LulHWPhyIndex].pICRX), (uint16)(~SPI_EIC_EIRF_MASK));
  RH850_SV_MODE_ICR_AND(16, (Spi_GaaMSPIRegs[LulHWPhyIndex].pICFE), (uint16)(~SPI_EIC_EIRF_MASK));

  /* Disable all interrupts unconditionally */
  RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICRX, (uint8)SPI_EIC_EIMK_MASK);                   /* PRQA S 0751 # JV-01 */
  RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICTX, (uint8)SPI_EIC_EIMK_MASK);                   /* PRQA S 0751 # JV-01 */
  RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICFE, (uint8)SPI_EIC_EIMK_MASK);                   /* PRQA S 0751 # JV-01 */

  /* To ensure interrupt requests were cleared, do dummy read & SYNCP */
  RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIRegs[LulHWPhyIndex].pICTX);
  #else
  /* Clear pending interrupt flags */
  RH850_SV_MODE_ICR_AND(16, (Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX), (uint16)(~SPI_EIC_EIRF_MASK));
  RH850_SV_MODE_ICR_AND(16, (Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRX), (uint16)(~SPI_EIC_EIRF_MASK));
  RH850_SV_MODE_ICR_AND(16, (Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFE), (uint16)(~SPI_EIC_EIRF_MASK));

  /* Disable all interrupts unconditionally */
  if (SPI_MSPI_ORED_DISABLED == (Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredTxIsr & (uint16)(~(1UL << LulHWPhyIndex))))
  {
    RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRX, (uint8)SPI_EIC_EIMK_MASK);                       /* PRQA S 0751 # JV-01 */
    RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX, (uint8)SPI_EIC_EIMK_MASK);                       /* PRQA S 0751 # JV-01 */
  } /* No action required */

  if (SPI_MSPI_ORED_DISABLED == (Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredFeIsr & (uint16)(~(1UL << LulHWPhyIndex))))
  {
    RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFE, (uint8)SPI_EIC_EIMK_MASK);                       /* PRQA S 0751 # JV-01 */
  } /* No action required */

  Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredTxIsr &= ((uint16)(~(1UL << LulHWPhyIndex)));
  Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredRxIsr &= ((uint16)(~(1UL << LulHWPhyIndex)));
  Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredFeIsr &= ((uint16)(~(1UL << LulHWPhyIndex)));

  /* To ensure interrupt requests were cleared, do dummy read & SYNCP */
  RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX);
  #endif
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
}
#endif /* ((SPI_LEVEL_DELIVERED != SPI_LEVEL_0) && (SPI_FORCE_CANCEL_API == STD_ON)) */

/***********************************************************************************************************************
** Function Name      : Spi_MSPIMaskHWUnitInterrupts
**
** Service ID         : NA
**
** Description        : This function manipulates interrupt masks of a HWUnit, including DMA interrupts if available.
**                      This function modifies EIMK bit only, EIRF bit is not affected.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant for different HWUnit. Non-Reentrant for same HWUnit
**
** Input Parameters   : LpJobConfig    - Pointer to the Job configuration
**                      LblMask        - TRUE: set mask FALSE: reset mask
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : Global variables must be initialized
**
** Global Variable    : Spi_GpFirstHWUnit, Spi_GaaMSPIRegs, Spi_GaaMSPIOredISRRegs
**
** Function invoked   : Spi_DMAMaskHWUnitInterrupts, SPI_ENTER_CRITICAL_SECTION, SPI_EXIT_CRITICAL_SECTION
**
** Registers Used     : EIC(INTMSPInTXm), EIC(INTMSPInRXm), EIC(INTMSPInFEm), EIC(INTMSPInERRm)
**
** Reference ID       : SPI_DUD_ACT_078, SPI_DUD_ACT_078_CRT001, SPI_DUD_ACT_078_CRT002, SPI_DUD_ACT_078_REG001,
** Reference ID       : SPI_DUD_ACT_078_REG002, SPI_DUD_ACT_078_REG003, SPI_DUD_ACT_078_REG004, SPI_DUD_ACT_078_REG005,
** Reference ID       : SPI_DUD_ACT_078_REG006, SPI_DUD_ACT_078_REG007, SPI_DUD_ACT_078_REG008, SPI_DUD_ACT_078_REG009
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MSPIMaskHWUnitInterrupts(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,               /* PRQA S 3006 # JV-01 */
                                 const boolean LblMask)
{
  P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpHWDevConfig;
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;
  uint32 LulHWUnitIndex;
  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
  uint32 LulHWPhyIndex;
  VAR(uint8, AUTOMATIC) LucIsrSelId;
  #endif
  /* Get HW unit index */
  LulHWUnitIndex = LpJobConfig->ucHWUnitIndex;
  LpHWInfo = &Spi_GpFirstHWUnit[LulHWUnitIndex];
  /* Get pointer to HW unit configuration*/
  LpHWDevConfig = (P2CONST(Spi_MSPIDeviceConfigType, AUTOMATIC, SPI_CONFIG_DATA))LpJobConfig->pHWDevConfig;             /* PRQA S 0316 # JV-01 */
  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_ON)
  LulHWPhyIndex = LpHWInfo->ucPhyUnitIndex;
  /* Get Ored Interrupt selection index */
  LucIsrSelId = Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].ucInterruptSel;
  #endif
  /* INTERRUPT_PROTECTION is required to avoid ISR occur
  while EIMK is being set */
  SPI_ENTER_CRITICAL_SECTION(SPI_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  /* Check if request to mask interrupts */
  if (SPI_TRUE == LblMask)
  {
    #if (SPI_DMA_CONFIGURED == STD_ON)
    if (LpJobConfig->ucRxDmaIndex != SPI_INVALID_DMAUNIT)
    {
      Spi_DMAMaskHWUnitInterrupts((uint32)LpJobConfig->ucRxDmaIndex, SPI_TRUE);
    }
    else
    #endif
    {
      if (SPI_MEMORYMODE_FIXED_BUFFER != LpHWDevConfig->enMemoryMode)
      {
        #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
        RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICRX, (uint8)SPI_EIC_EIMK_MASK);             /* PRQA S 0751 # JV-01 */
        /* Write the lower byte of EIC registers to avoid modifying EIRF bit */
        RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICTX, (uint8)SPI_EIC_EIMK_MASK);             /* PRQA S 0751 # JV-01 */
        #else
        if (SPI_MSPI_ORED_DISABLED == (Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredTxIsr \
                                                                                  & (uint16)(~(1UL << LulHWPhyIndex))))
        {
          /* Write the lower byte of EIC registers to avoid modifying EIRF bit */
          RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRX, (uint8)(SPI_EIC_EIMK_MASK));               /* PRQA S 0751 # JV-01 */
          RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX, (uint8)(SPI_EIC_EIMK_MASK));               /* PRQA S 0751 # JV-01 */
        } /* No action required */

        Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredTxIsr &= ((uint16)(~(1UL << LulHWPhyIndex)));
        Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredRxIsr &= ((uint16)(~(1UL << LulHWPhyIndex)));
        #endif
      }
      else
      {
        /* Write the lower byte of EIC registers to avoid modifying EIRF bit */
        #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
        RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICFE, (uint8)SPI_EIC_EIMK_MASK);             /* PRQA S 0751 # JV-01 */
        #else
        if (SPI_MSPI_ORED_DISABLED == (Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredFeIsr & \
                                                                                    (uint16)(~(1UL << LulHWPhyIndex))))
        {
          /* Write the lower byte of EIC registers to avoid modifying EIRF bit */
          RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFE, (uint8)SPI_EIC_EIMK_MASK);                 /* PRQA S 0751 # JV-01 */
        } /* No action required */

        Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredFeIsr &= ((uint16)(~(1UL << LulHWPhyIndex)));
        #endif
      }
    }
  }
  else
  {
    #if (SPI_DMA_CONFIGURED == STD_ON)
    if (LpJobConfig->ucRxDmaIndex != SPI_INVALID_DMAUNIT)
    {
      #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
      /* Mask Rx and Tx interrupt when using DMA */
      RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICRX, (uint8)SPI_EIC_EIMK_MASK);               /* PRQA S 0751 # JV-01 */
      /* Write the lower byte of EIC registers to avoid modifying EIRF bit */
      RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICTX, (uint8)SPI_EIC_EIMK_MASK);               /* PRQA S 0751 # JV-01 */
      /* Un-mask DMA interrupt */
      #else
      if (SPI_MSPI_ORED_DISABLED == (Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredTxIsr & \
                                                                                    (uint16)(~(1UL << LulHWPhyIndex))))
      {
        /* Mask Rx and Tx interrupt when using DMA */
        RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRX, (uint8)(SPI_EIC_EIMK_MASK));                 /* PRQA S 0751 # JV-01 */
        /* Write the lower byte of EIC registers to avoid modifying EIRF bit */
        RH850_SV_MODE_ICR_OR(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX, (uint8)(SPI_EIC_EIMK_MASK));                 /* PRQA S 0751 # JV-01 */
      } /* No action required */
      #endif
      Spi_DMAMaskHWUnitInterrupts((uint32)LpJobConfig->ucRxDmaIndex, SPI_FALSE);
    }
    else
    #endif
    {
      if (SPI_MEMORYMODE_FIXED_BUFFER != LpHWDevConfig->enMemoryMode)
      {
        #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
        /* Write the lower byte of EIC registers to avoid modifying EIRF bit */
        RH850_SV_MODE_ICR_AND(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICRX, (uint8)(~SPI_EIC_EIMK_MASK));         /* PRQA S 0751 # JV-01 */
        /* Write the lower byte of EIC registers to avoid modifying EIRF bit */
        RH850_SV_MODE_ICR_AND(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICTX, (uint8)(~SPI_EIC_EIMK_MASK));         /* PRQA S 0751 # JV-01 */
        #else
        /* Write the lower byte of EIC registers to avoid modifying EIRF bit */
        RH850_SV_MODE_ICR_AND(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICRX, (uint8)(~SPI_EIC_EIMK_MASK));               /* PRQA S 0751 # JV-01 */
        RH850_SV_MODE_ICR_AND(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX, (uint8)(~SPI_EIC_EIMK_MASK));               /* PRQA S 0751 # JV-01 */

        Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredTxIsr |= ((uint16)(1UL << LulHWPhyIndex));
        Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredRxIsr |= ((uint16)(1UL << LulHWPhyIndex));
        #endif
      }
      else
      {
        #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
        /* Write the lower byte of EIC registers to avoid modifying EIRF bit */
        RH850_SV_MODE_ICR_AND(8, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICFE, (uint8)(~SPI_EIC_EIMK_MASK));         /* PRQA S 0751 # JV-01 */
        #else
        RH850_SV_MODE_ICR_AND(8, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICFE, (uint8)(~SPI_EIC_EIMK_MASK));               /* PRQA S 0751 # JV-01 */

        Spi_GstHwActiveOredIsr[LucIsrSelId].usHwOredFeIsr |= ((uint16)(1UL << LulHWPhyIndex));
        #endif
      }
    }
  }
  /* To ensure change of interrupt masks, do dummy read & SYNCP */
  #if (SPI_ORED_INTERRUPT_FUNCTION == STD_OFF)
  RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIRegs[LpHWInfo->ucPhyUnitIndex].pICTX);
  #else
  RH850_SV_MODE_REG_READ_ONLY(32, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTSMSK);
  RH850_SV_MODE_REG_READ_ONLY(16, Spi_GaaMSPIOredISRRegs[LucIsrSelId].pICTX);
  #endif
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
  SPI_EXIT_CRITICAL_SECTION(SPI_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
}

/***********************************************************************************************************************
** Function Name      : Spi_MSPITurnOff
**
** Service ID         : Not Applicable
**
** Description        : This function turn off MSPI.
**
** Sync/Async         : Synchronous
**
** Re-entrancy        : Reentrant
**
** Input Parameters   : LulHWPhyIndex - Physical index of the HWUnit
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : void
**
** Preconditions      : None
**
** Global Variable    : Spi_GaaMSPIRegs
**
** Function Invoked   : None
**
** Registers Used     : MSPInCTL0
**
** Reference ID       : SPI_DUD_ACT_079, SPI_DUD_ACT_079_REG001
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPITurnOff(const uint32 LulHWPhyIndex)
{
  Spi_GaaMSPIRegs[LulHWPhyIndex].pRegs->ucCTL0 = 0U;
}

#if (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON)
/***********************************************************************************************************************
** Function Name      : Spi_MSPIHWControlCS
**
** Service ID         : Not Applicable
**
** Description        : This service performs activation of the Chip Select pin.
**
** Sync/Async         : Synchronous.
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : LpJobConfig - Pointer to Job configuration.
**                      LblActivateCS - Chip select activation is required.
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : None
**
** Global Variable    : None
**
** Function Invoked   : None
**
** Registers Used     : PSRn, JPSRn, APSRn
**
** Reference ID       : SPI_DUD_ACT_102,
** Reference ID       : SPI_DUD_ACT_102_REG001, SPI_DUD_ACT_102_REG002
** Reference ID       : SPI_DUD_ACT_102_CRT001, SPI_DUD_ACT_102_CRT002
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_MSPIHWControlCS(
  CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig,
  CONST(boolean, AUTOMATIC) LblActivateCS)
{
  volatile VAR(uint32, AUTOMATIC) LulLoopCount;
  #if (SPI_CRITICAL_SECTION_PROTECTION == STD_ON)
  SPI_ENTER_CRITICAL_SECTION(SPI_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  #endif
  /* Set or reset port pin depending on chip select polarity and cs act flag */
  if (((SPI_CS_HIGH == LpJobConfig->blCsPolarity) && (SPI_TRUE == LblActivateCS)) ||
    ((SPI_CS_LOW == LpJobConfig->blCsPolarity) && (SPI_FALSE == LblActivateCS)))
  {
    *(LpJobConfig->pPSRReg) = LpJobConfig->ulPortPinMask;
  }
  else /* If Chip select polarity is configured as active Low */
  {
    *(LpJobConfig->pPSRReg) = LpJobConfig->ulPortPinMask & SPI_PORT_PIN_MASK;
  }

  /* Check whether CS activation is required */
  if (SPI_TRUE == LblActivateCS)
  {
    /* Timing between chip select activated and clock start when writing data */
    LulLoopCount = LpJobConfig->ulClk2CsCount;
    while ((uint32)SPI_ZERO < LulLoopCount)                                                                             /* PRQA S 3416 # JV-01 */
    {
      LulLoopCount--;                                                                                                   /* PRQA S 3387, 3384 # JV-01, JV-01 */
    }
  }
  #if (SPI_CRITICAL_SECTION_PROTECTION == STD_ON)
  SPI_EXIT_CRITICAL_SECTION(SPI_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  #endif
}
#endif /* (SPI_CS_VIA_GPIO_CONFIGURED == STD_ON) */

#define SPI_STOP_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* (SPI_MSPI_CONFIGURED == STD_ON) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
