/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_ATU_LLDriver.c                                                                                  */
/*====================================================================================================================*/
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Low Level function implementations of ICU Driver Component                                      */
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
 * 2.4.1:  30/06/2025  : As part of support QAC 11.6.0, following changes are made:
 *                       1. Update QAC message and QAC header
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : As part of support QAC 9.5.0, following changes are made:
 *                       1. Update QAC message and QAC header                     
 *                       As part of support GTM HWIP into common code, following changes are made:
 *                       1. Signal measurement counter overflow check move from Icu_ServiceSignalMeasurement to 
 *                       Icu_TimerIsr for supporting QAC STCYC less than 20.
 *                       2. Remove Icu_HW_Atu_EnableEdgeDetection, Icu_HW_Atu_DisableEdgeDetection, Icu_HW_Atu_SetMode
 *                       3. Remove update value of Icu_GpSignalMeasurementData in Icu_HW_Atu_UnitInit
 *                       4. Update precompile condition
 *                       5. Add preprocesser ICU_ATU_TIMER_UNIT_USED
 *                       Update QAC after run QAC version 10.3.0
 * 2.0.1:  18/10/2023  : Remove QAC messages 2814, 2824, 2844, 0857. Add messages 3006, 1881, 4304
 *         14/10/2023  : Remove pre-compile parameter ICU_E_INT_INCONSISTENT_CONFIGURED for ICU_DEM_REPORT_ERROR
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h"
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 *                       Add ucChannelRunning channel property in
 *                       Icu_HW_Atu_ChannelInit/Icu_HW_Atu_ChannelDeInit/Icu_HW_Atu_EnableEdgeDetection/
 *                       Icu_HW_Atu_DisableEdgeDetection/Icu_HW_Atu_StartCountMeasurement/
 *                       Icu_HW_Atu_StopCountMeasurement, add new function "Icu_HW_Atu_SetMode"
 *                       Support wakeup/setmode check condition on ATU channel
 * 1.4.5:  06/04/2023  : Update function Icu_ServiceSignalMeasurement to reduce STCYC <= 20
 * 1.4.4:  17/11/2022  : Update "Input Parameters", "Global Variables",
 *                       "Functions invoked" for all functions.
 *         16/06/2022  : Update QAC message and QAC header
 * 1.4.3:  23/05/2022  : Fix QAC header and message.
 *         09/05/2022  : Remove "else" statement when no action required; add QAC message 2004.
 *         17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 * 1.4.2:  02/03/2022  : Fix QAC header and message
 * 1.4.1:  18/10/2021  : Add QAC message 9.5.0
 *                       Icu_HW_Atu_UnitInit: add Read the HWIP Type for given channel
 *         05/10/2021  : Correct name of used variables, datatypes
 *                       Correct preprocessor directives
 *                       Correct Function Name in function headers
 *                       Remove inccorect comment EXINTCTL in Registers Used
 *                       Rename ATU5 -> ATU
 * 1.3.2:  30/08/2021  : Change from #include "Icu_MemMap.h" to #include "Icu_Mapping.h".
 *                       Update pre-compile parameter ICU_E_INT_INCONSISTENT_CONFIGURED for ICU_DEM_REPORT_ERROR
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.3.0:  20/01/2021  : Changed CONSTP2CONST to P2CONST for argument ConfigPtr
 *                     : Updated IF condition of Icu_ServiceSignalMeasurement
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
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
/* Message (4:1881)    : The operands of this equality operator are expressions of different 'essential type'         */
/*                       categories (%1s and %2s).                                                                    */
/* Rule                : MISRA C:2012 Rule-10.4, CERTCCM INT02, CWE Rule CWE-136, CWE-192                             */
/* JV-01 Justification : The equality operator between enum and unsigned type can be accepted.                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : MISRA C:2012 Rule-15.7, CERTCCM MSC01, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2962)    : Apparent: Using value of uninitialized automatic object '%s'.                                */
/* Rule                : MISRA C:2012 Rule-9.1, CERTCCM EXP33, CWE Rule CWE-457, CWE-824, CWE-908, CWE-452, CWE-465,  */
/*                       CWE-737                                                                                      */
/* JV-01 Justification : It will be initialized based on scope of 'if' statements where at least an 'if' statement    */
/*                       will be executed that will initialize the variable.                                          */
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
/* Message (3:4304)    : An expression of 'essentially Boolean' type (%1s) is being cast to unsigned type '%2s'.      */
/* Rule                : MISRA C:2012 Rule-10.5                                                                       */
/* JV-01 Justification : This is accepted. This casting from boolean to unsigned type for values 0 and 1 does not     */
/*                       make data conflict.                                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4342)    : An expression of 'essentially unsigned' type (%1s) is being cast to enum type '%2s'.         */
/* Rule                : MISRA C:2012 Rule-10.5, CWE Rule CWE-704                                                     */
/* JV-01 Justification : It is assigned to a variable with no conflict in the data.                                   */
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

/* Included for Header file inclusion */
#include "Icu_ATU_LLDriver.h"
/* Included for RAM variable declarations */
#include "Icu_Ram.h"

#if (ICU_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
/* Include for interrupt consistency check */
#include "Dem.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define ICU_ATU_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_ATU_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_ATU_LLDRIVER_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ICU_ATU_LLDRIVER_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_ATU_LLDRIVER_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (ICU_ATU_LLDRIVER_AR_RELEASE_MAJOR_VERSION != ICU_ATU_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Icu_ATU_LLDriver.c : Mismatch in Release Major Version"
#endif /* End of #if (ICU_LLDRIVER_AR_RELEASE_MAJOR_VERSION != \
                                     ICU_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION) */

#if (ICU_ATU_LLDRIVER_AR_RELEASE_MINOR_VERSION != ICU_ATU_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Icu_ATU_LLDriver.c : Mismatch in Release Minor Version"
#endif /* End of #if (ICU_LLDRIVER_AR_RELEASE_MINOR_VERSION != \
                                     ICU_LLDRIVER_C_AR_RELEASE_MINOR_VERSION) */

#if (ICU_ATU_LLDRIVER_AR_RELEASE_REVISION_VERSION != ICU_ATU_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Icu_ATU_LLDriver.c : Mismatch in Release Revision Version"
#endif /* End of #if (ICU_LLDRIVER_AR_RELEASE_REVISION_VERSION != \
                                  ICU_LLDRIVER_C_AR_RELEASE_REVISION_VERSION) */

#if (ICU_ATU_LLDRIVER_SW_MAJOR_VERSION != ICU_ATU_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Icu_ATU_LLDriver.c : Mismatch in Software Major Version"
#endif /* End of #if (ICU_LLDRIVER_SW_MAJOR_VERSION != \
                                             ICU_LLDRIVER_C_SW_MAJOR_VERSION) */

#if (ICU_ATU_LLDRIVER_SW_MINOR_VERSION != ICU_ATU_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Icu_ATU_LLDriver.c : Mismatch in Software Minor Version"
#endif /* End of #if (ICU_LLDRIVER_SW_MINOR_VERSION != \
                                             ICU_LLDRIVER_C_SW_MINOR_VERSION) */

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#if (ICU_ATU_TIMER_UNIT_USED == STD_ON)
/***********************************************************************************************************************
** Function Name         : Icu_HW_Atu_UnitInit
**
** Service ID            : None
**
** Description           : This service initializes the hardware for all the
**                         configured channels based on the measurement mode.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
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
** Global Variables      : Icu_GpChannelConfig, Icu_GpTimerClkBusConfig
**                         Icu_GpNoiseCancellationConfig, Icu_GpSignalMeasurementData.
**
** Functions invoked     : None
**
** Registers Used        : TCNTA, TIOR1A, TCNTCm, GRCmn, TIORCm, EICn, NCMR, NCMCR1A
**                         NCMCR2A, TIOR2A,ATUENR, NCCRCx, NCRCxy, NCMCR1C, NCMCR2C, TCR1A,TIERA
**
** Reference ID          : ICU_DUD_ACT_069, ICU_DUD_ACT_069_REG001, ICU_DUD_ACT_069_REG002, ICU_DUD_ACT_069_GBL003
** Reference ID          : ICU_DUD_ACT_069_REG003, ICU_DUD_ACT_069_REG004, ICU_DUD_ACT_069_REG005
** Reference ID          : ICU_DUD_ACT_069_REG006, ICU_DUD_ACT_069_REG007, ICU_DUD_ACT_069_REG008
** Reference ID          : ICU_DUD_ACT_069_REG009, ICU_DUD_ACT_069_REG010, ICU_DUD_ACT_069_GBL006
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Atu_UnitInit(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST) ConfigPtr)
{
  #if ((ICU_ATU_COMMON_PRESCALER_CONFIGURED != ICU_COMMON_PRESCALER_NOT_USED) ||                           \
     (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON) || \
                                                 (ICU_TIMER_CLK_BUS_NOT_USED != ICU_TIMER_CLK_BUS_SELECTION_CONFIGURED))
  /* Defining a pointer to the ATU configuration parameters */
  P2CONST(Icu_ATUConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUConfig;
  #endif
  #if (ICU_ATU_COMMON_PRESCALER_CONFIGURED != ICU_COMMON_PRESCALER_NOT_USED)
  /* Defining a pointer to the ATU channel configuration parameters */
  P2CONST(Icu_ATUChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelConfig;
  /* Defining a pointer to the common contrl Register */
  P2VAR(Icu_ATUCommonCntlRegs, AUTOMATIC, ICU_CONFIG_DATA) LpCommonCntlReg;                                             /* PRQA S 3432 # JV-01 */

  P2CONST(Icu_ATU_CommonPrescalerConfigType, AUTOMATIC, ICU_CONFIG_DATA) LaaATUCommonPrescalerConfig;

  P2CONST(Icu_ATU_CommonPrescalerConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpCommonPrescalerConfig;
  /* Store the global pointer to first Common Prescaler configuration */
  #endif
  /* Counter variable*/
  uint8 LucCnt;
  
  /* Local variable to hold the channel number */
  volatile uint8 LucChannelNo;
  
  /* Index of HW IP Type */
  volatile VAR(uint8, AUTOMATIC) LucHWIPType;

  #if (ICU_TIMER_CLK_BUS_NOT_USED != ICU_TIMER_CLK_BUS_SELECTION_CONFIGURED)
  /* Defining a pointer to the clock bus selection configuration parameters */
  P2CONST(Icu_ATU_ClockBusConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTimerClkBusConfig;
  #endif

  /* Defining a pointer to the clock bus selection Control Register */
  P2VAR(volatile uint8, AUTOMATIC, ICU_CONFIG_DATA) LpClkBusCntrlReg;

  #if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))
  /* Defining a pointer to the Timer Noise Cancellation configuration */
  P2CONST(Icu_NoiseCancellationConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpNoiseCancellationConfig;
  #if (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON)
  /* Defining a pointer to the NCCRC register Configuration parameter*/
  P2CONST(Icu_NCCRCCntrlRegConfigType, AUTOMATIC, ICU_CONFIG_DATA)
  LpNCCRCCntrlRegConfig;
  #endif /* End of #if (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) */
  #endif /* ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON)) */

  /* Update the global pointer with the first channel's configuration database address */
  #if ((ICU_ATU_COMMON_PRESCALER_CONFIGURED != ICU_COMMON_PRESCALER_NOT_USED) ||                           \
     (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON) || \
                                                 (ICU_TIMER_CLK_BUS_NOT_USED != ICU_TIMER_CLK_BUS_SELECTION_CONFIGURED))
  LpATUConfig = ConfigPtr->pATUConfig;                                                                                  /* PRQA S 0317 # JV-01 */
  #endif

  #if (ICU_ATU_COMMON_PRESCALER_CONFIGURED != ICU_COMMON_PRESCALER_NOT_USED)
  
  for (LucChannelNo = (uint8)ICU_ZERO; LucChannelNo < (uint8)ICU_MAX_CHANNEL; LucChannelNo++)                           /* PRQA S 3387, 3416 # JV-01, JV-01 */
  {
    /* Read the HWIP Type for given channel  */
    LucHWIPType = Icu_GpChannelConfig[LucChannelNo].ucIcuChannelType;                                                   /* PRQA S 0404 # JV-01 */
    if ((ICU_HW_ATU_TIMERA == LucHWIPType) || (ICU_HW_ATU_TIMERC == LucHWIPType))                                       /* PRQA S 3415, 3416 # JV-01, JV-01 */
    {
      LpATUChannelConfig = Icu_GpChannelConfig[LucChannelNo].pHWIPChannelConfig;                                        /* PRQA S 0317, 0404 # JV-01, JV-01 */
      break;
    } /* else No action required */
  }

  LaaATUCommonPrescalerConfig = LpATUConfig->pCommonPrescalerConfig;                                                    /* PRQA S 0317 # JV-01 */
  /* Enable the configured ICU ATU Units in ATUENR register */
  LpCommonCntlReg = (P2VAR(Icu_ATUCommonCntlRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pAtuCommonCntlRegs;   /* PRQA S 0316, 3432 # JV-01, JV-01 */

  /* Initialize the ATU-V Common Prescaler*/
  for (LucCnt = ICU_ZERO; (uint16)LucCnt < (uint16)ICU_ATU_COMMON_PRESCALER_CONFIGURED; LucCnt++)
  {
    /* Initialized Pointer for Common Prescaler Config */
    LpCommonPrescalerConfig = &LaaATUCommonPrescalerConfig[LucCnt];

    /* Set value of Prescaler*/
    *((volatile uint16 *)LpCommonPrescalerConfig->pATUCommonPrescalerCntlReg) =                                         /* PRQA S 0316 # JV-01 */
                                                                 LpCommonPrescalerConfig->usAtuCommonPrescalerDivRatio;
  }

  /* Enable the configured prescaler Units in ATUENR register */
  (LpCommonCntlReg->ucAtuTimerATUENR) |= ICU_PSCE_MASK_VALUE;

  #endif /* End of (ICU_ATU_COMMON_PRESCALER_CONFIGURED != ICU_COMMON_PRESCALER_NOT_USED)) */

  #if (ICU_TIMER_CLK_BUS_NOT_USED != ICU_TIMER_CLK_BUS_SELECTION_CONFIGURED)
  /* Update the global pointer with the ICU pTimerClock bus configuration */
  Icu_GpTimerClkBusConfig = LpATUConfig->pTimerClkBusConfig;                                                            /* PRQA S 0317 # JV-01 */
  /* Update the previous input use pointer to point to the current channel */
  LpTimerClkBusConfig = Icu_GpTimerClkBusConfig;
  /* Clock bus selection for the configured timer unit */
  for (LucCnt = ICU_ZERO; LucCnt < ICU_TIMER_CLK_BUS_SELECTION_CONFIGURED; LucCnt++)
  {
    /* Load clock bus selection for the timer unit */
    LpClkBusCntrlReg = LpTimerClkBusConfig->pAtuClkBusCntrlRegs;                                                        /* PRQA S 0317 # JV-01 */
    *(LpClkBusCntrlReg) = ((*(LpClkBusCntrlReg)&ICU_CLK_BUS_SELECT_MASK) | (LpTimerClkBusConfig->ucClkBusSelect));

    /* Increment the pointer to point to next previous input channel */
    LpTimerClkBusConfig++;

  } /* End of clock bus selection channel for loop */
  #endif /* #if (ICU_TIMER_CLK_BUS_NOT_USED != ICU_TIMER_CLK_BUS_SELECTION_CONFIGURED) */

  #if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))
  /* Update the Global pointer to point to first channel's the Timer Noise Cancellation configuration. */
  Icu_GpNoiseCancellationConfig = LpATUConfig->pNoiseCancellationConfig;                                                /* PRQA S 0317 # JV-01 */

  /* Update the local pointer to point to the Timer Noise Cancellation configuration. */
  LpNoiseCancellationConfig = Icu_GpNoiseCancellationConfig;

  if (ICU_NC_PLL_ENABLE == LpNoiseCancellationConfig->ucAtuNCMRCntrlRegValue)
  {
    /* Enabling the bit NCCSEL in the NCMR register */
    *(LpNoiseCancellationConfig->pAtuNCMRCntrlReg) |= ICU_NC_PLL_ENABLE;
  }
  else
  {
    /* Resetting the bit NCCSEL in the NCMR register */
    *(LpNoiseCancellationConfig->pAtuNCMRCntrlReg) &= (uint8)~ICU_NC_PLL_ENABLE;
  }
  /* Resetting the Noise Cancellation Mode Select bits of TimerA and TimerC */
  *(LpNoiseCancellationConfig->pAtuNCMRCntrlReg) &= (uint8)~ICU_NC_NCMR_MASK;

  #if (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON)
  /* Load the Noise Cancellation Selection mode in the Noise Cancellation Mode Channel Register 1A */
  *(LpNoiseCancellationConfig->pAtuNCMCR1ACntrlReg) = LpNoiseCancellationConfig->ucAtuNCMCR1ACntrlRegValue;

  /* Load the Noise Cancellation Selection mode in the Noise Cancellation Mode Channel Register 2A */
  *(LpNoiseCancellationConfig->pAtuNCMCR2ACntrlReg) = LpNoiseCancellationConfig->ucAtuNCMCR2ACntrlRegValue;

  /* Load the Timer I/O Control Register 2A based on the clock selection, and Enabling/Disabling the Noise Canceller */
  *(LpNoiseCancellationConfig->pAtuTIOR2ACntrlReg) = LpNoiseCancellationConfig->ulAtuTIOR2ACntrlRegValue;
  #endif /* End of #if (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON) */

  #if (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON)

  /* Select the Noise cancellation modes for the TimerC subblocks */
  *(LpNoiseCancellationConfig->pAtuNCMCR1CCntrlReg) = LpNoiseCancellationConfig->usAtuNCMCR1CCntrlRegValue;

  /* Select the Noise cancellation modes for the TimerC subblocks */
  *(LpNoiseCancellationConfig->pAtuNCMCR2CCntrlReg) = LpNoiseCancellationConfig->usAtuNCMCR2CCntrlRegValue;

  /* Load the value for the Noise Canceler Clock Selection and the Noise Canceler Enable or Disable */

  LpNCCRCCntrlRegConfig = LpNoiseCancellationConfig->pNCCRCCntrlRegConfig;                                              /* PRQA S 0317 # JV-01 */

  for (LucCnt = ICU_ZERO; LucCnt < LpNoiseCancellationConfig->ucTotalTimerCConfigured; LucCnt++)
  {
    /* Load the value of the Noise Canceler Control Register for the respective Timer C subblock. */
    *((LpNoiseCancellationConfig->pAtuNCCRCCntrlRegAdrs + LpNCCRCCntrlRegConfig->ucAtuNCCRCSubBlockIndex)) =            /* PRQA S 0488 # JV-01 */
                                                                        LpNCCRCCntrlRegConfig->ucAtuNCCRCCntrlRegValue;

    LpNCCRCCntrlRegConfig++;
  }

  #endif /* End of #if (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) */
  #endif /* End of #if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || \
                                                                      (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))*/
} /* End of Internal function Icu_HW_Atu_UnitInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Atu_ChannelInit
**
** Service ID            : None
**
** Description           : This service initializes the hardware for all the
**                         configured channels based on the measurement mode.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LddChannelIndex
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelUserRegConfig,
**                         Icu_GpChannelRamData.
**
** Functions invoked     : Icu_HW_Atu_EdgeCountingInit, Icu_HW_Atu_TimestampInit, Icu_HW_Atu_SignalMeasurementInit
**
** Registers Used        : TCNTA, TIOR1A, TSCRA, TCNTCm, GRCmn, TIORCm, TSCRCm, EICn, NCMR, NCMCR1A
**                         NCMCR2A, TIOR2A,ATUENR, NCCRCx, NCRCxy, NCMCR1C, NCMCR2C. TCR1A,TIERA
**
** Reference ID          : ICU_DUD_ACT_088, ICU_DUD_ACT_088_REG001, ICU_DUD_ACT_088_REG002
** Reference ID          : ICU_DUD_ACT_088_REG003, ICU_DUD_ACT_088_REG004, ICU_DUD_ACT_088_REG005,
** Reference ID          : ICU_DUD_ACT_088_REG006, ICU_DUD_ACT_088_REG007, ICU_DUD_ACT_088_REG008
** Reference ID          : ICU_DUD_ACT_088_REG009, ICU_DUD_ACT_088_REG010, ICU_DUD_ACT_088_REG011,
** Reference ID          : ICU_DUD_ACT_088_REG012, ICU_DUD_ACT_088_REG013, ICU_DUD_ACT_088_GBL001
** Reference ID          : ICU_DUD_ACT_088_GBL006, ICU_DUD_ACT_088_GBL005, ICU_DUD_ACT_088_REG014
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Atu_ChannelInit(const Icu_ChannelType LddChannelIndex)                              /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  #if ((ICU_ATU_TIMERC_UNIT_USED == STD_ON) || (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || \
                                                                        (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))
  /* Defining a pointer to the ATU channel configuration parameters */
  P2CONST(Icu_ATUChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelConfig;
  #endif

  /* Defining a pointer to the Channel Ram Data */
  P2VAR(volatile Icu_ChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpRamData;

  /* Defining a pointer to the timer channel configuration parameters */
  #if ((ICU_SIGNAL_MEASUREMENT_API == STD_ON) || (ICU_EDGE_COUNT_API == STD_ON) || (ICU_TIMESTAMP_API == STD_ON))
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  #endif 
  P2CONST(Icu_ATUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelUserRegConfig;

  #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
  /* Initialize pointer to the base address of the current channel */
  P2VAR(Icu_ATUTimerACommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerACommonRegs;                                 /* PRQA S 3432 # JV-01 */
  #endif

  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  /* Initialize pointer to the base address of the current channel */
  P2VAR(Icu_ATUTimerCSubBlkUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerCSubBlkRegs;                                 /* PRQA S 3432 # JV-01 */

  /* Initialize pointer to the base address of the current channel */
  P2VAR(Icu_ATUTimerCChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerCChannelRegs;                               /* PRQA S 3432 # JV-01 */
  #endif
  /* Local variable to store the measurement mode of a channel */
  Icu_MeasurementModeType LddMeasurementMode;

  #if ((ICU_ATU_TIMERC_UNIT_USED == STD_ON) || (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || \
                                                                        (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))
  /* Initialize all the configured Icu Channels */
  LpATUChannelConfig = Icu_GpChannelConfig[LddChannelIndex].pHWIPChannelConfig;                                         /* PRQA S 0317 # JV-01 */
  /* Update the global pointer with the first channel's ram address */
  #endif

  LpRamData = &Icu_GpChannelRamData[LddChannelIndex];

  /* Update the channel pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannelIndex];

  /* Initialize each channel status as idle */
  LpRamData->ucChannelStatus = (uint8)ICU_IDLE;
  /* Disable notification for each channel */
  LpRamData->ucNotificationEnable = (uint8)ICU_FALSE;                                                                   /* PRQA S 4304 # JV-01 */
  /* Initialize the status of result channel as False */
  LpRamData->blResultComplete = ICU_FALSE;
  /* Initialize all the configured Icu Channels */
  #if ((ICU_DISABLE_WAKEUP_API == STD_ON) || (ICU_ENABLE_WAKEUP_API == STD_ON) || \
                                                                              (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON))
  /* Disable each channel wake-up from sleep mode */
  LpRamData->ucWakeupEnable = (uint8)ICU_FALSE;                                                                         /* PRQA S 4304 # JV-01 */
  /* Initialize wakeup occurrence for each channel */
  LpRamData->blWakeupOccurrence = ICU_FALSE;
  #endif
  #if (STD_ON == ICU_SET_MODE_API)
  /* Initialize running status for each channel */
  LpRamData->ucChannelRunning = (uint8)ICU_FALSE;                                                                       /* PRQA S 4304 # JV-01 */
  #endif

  /* Update the Timer channel configuration pointer to point to the current channel */
  #if ((ICU_SIGNAL_MEASUREMENT_API == STD_ON) || (ICU_EDGE_COUNT_API == STD_ON) || (ICU_TIMESTAMP_API == STD_ON))
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannelIndex];
  #endif

  LpATUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannelIndex].pHWChannelUserRegConfig;                      /* PRQA S 0317 # JV-01 */

  /* Read the channel's measurement mode */
  LddMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */

  #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
  if (ICU_HW_ATU_TIMERA == LpChannelConfig->ucIcuChannelType)
  {
    /* Initialize pointer to the base address of the current channel */
    LpATUTimerACommonRegs =
             (P2VAR(Icu_ATUTimerACommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelUserRegConfig->pTimerCntlRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

    /* Enable TIERA timer interrupt enable register A  */
    LpATUTimerACommonRegs->usAtuTimerATIERA = ICU_ATU_TIMERA_TIERA_INIT_VAL;
    /* If the measurement mode is edge counter, put the defined count value to TCNTA Register */
    if (ICU_MODE_EDGE_COUNTER == LddMeasurementMode)
    {
      /* Assign the up count value to TCNTA register */
      LpATUTimerACommonRegs->ulAtuTimerATCNTA = ICU_ATU_TIMER_INITIAL_CNT_VAL;
    } /* else No action required */
    /* End of (LddMeasurementMode == ICU_MODE_EDGE_COUNTER) */

    /* Mask and set the configured default start edges for the channel */
    LpATUTimerACommonRegs->usAtuTimerATIOR1A &= (LpATUChannelUserRegConfig->usChannelModeUserRegSettings);

    if ((uint8)ICU_RISING_EDGE == LpChannelConfig->ucIcuDefaultStartEdge)
    {
      LpATUTimerACommonRegs->usAtuTimerATIOR1A |=
                         (uint16)((uint16)ICU_ATU_RISING_EDGE_MASK << (LpChannelConfig->usChannelMaskValue * ICU_TWO));
    }
    else if ((uint8)ICU_FALLING_EDGE == LpChannelConfig->ucIcuDefaultStartEdge)
    {
      LpATUTimerACommonRegs->usAtuTimerATIOR1A |=
                        (uint16)((uint16)ICU_ATU_FALLING_EDGE_MASK << (LpChannelConfig->usChannelMaskValue * ICU_TWO));
    }
    else if ((uint8)ICU_BOTH_EDGES == LpChannelConfig->ucIcuDefaultStartEdge)                                           /* PRQA S 2004 # JV-01 */
    {
      LpATUTimerACommonRegs->usAtuTimerATIOR1A |=
                           (uint16)((uint16)ICU_ATU_BOTH_EDGE_MASK << (LpChannelConfig->usChannelMaskValue * ICU_TWO));
    } /* else No action required */
    /* Reset Channel Status Clear Trigger Register */
    LpATUTimerACommonRegs->usAtuTimerATSCRA = ICU_RESET_ATU_TIMERA_ATSCRA_VAL;

  } /* else No action required */
  /* End of if (ICU_HW_ATU_TIMERA == LpChannelConfig->ucIcuChannelType) */
  #endif /* End of (ICU_ATU_TIMERA_UNIT_USED == STD_ON) */
  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  if (ICU_HW_ATU_TIMERC == LpChannelConfig->ucIcuChannelType)
  {
    /* Initialize pointer to the base address of the current channel */
    LpATUTimerCSubBlkRegs =
             (P2VAR(Icu_ATUTimerCSubBlkUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelUserRegConfig->pTimerCntlRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

    /* Initialize pointer to the base address of the current channel */
    LpATUTimerCChannelRegs =
            (P2VAR(Icu_ATUTimerCChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pTimerChannelUserRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

    /* If the measurement mode is edge counter, put the defined count value to TCNTC Register */
    if (ICU_MODE_EDGE_COUNTER == LddMeasurementMode)
    {
      /* Assign the down count value to CDR register */
      LpATUTimerCSubBlkRegs->ulAtuTimerCTCNTCm = ICU_ATU_TIMER_INITIAL_CNT_VAL;
      LpATUTimerCChannelRegs->ulAtuTimerCGRCmn = ICU_ATU_TIMER_INITIAL_CNT_VAL;
    } /* else No action required */
    /* End of LddMeasurementMode == ICU_MODE_EDGE_COUNTER */
    /* Enable TIERCx timer interrupt enable register */
    LpATUTimerCSubBlkRegs->usAtuTimerCTIERCm = ICU_ATU_TIMERC_TIERC_INIT_VAL;

    /* Mask and set the configured default start edges for the channel */
    LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm &= LpATUChannelUserRegConfig->usChannelModeUserRegSettings;

    if ((uint8)ICU_FALLING_EDGE == LpChannelConfig->ucIcuDefaultStartEdge)
    {
      LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm |=
          (uint16)((uint16)(ICU_SET_INPUT_CAPTURE_MODE | ICU_ATU_FALLING_EDGE_MASK)
                                                                  << (LpChannelConfig->usChannelMaskValue * ICU_FOUR));
    }
    else if ((uint8)ICU_RISING_EDGE == LpChannelConfig->ucIcuDefaultStartEdge)
    {
      LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm |=
          (uint16)((uint16)(ICU_SET_INPUT_CAPTURE_MODE | ICU_ATU_RISING_EDGE_MASK)
                                                                  << (LpChannelConfig->usChannelMaskValue * ICU_FOUR));
    }
    else if ((uint8)ICU_BOTH_EDGES == LpChannelConfig->ucIcuDefaultStartEdge)                                           /* PRQA S 2004 # JV-01 */
    {
      LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm |= (uint16)((uint16)(ICU_SET_INPUT_CAPTURE_MODE | ICU_ATU_BOTH_EDGE_MASK)
                                                                  << (LpChannelConfig->usChannelMaskValue * ICU_FOUR));
    } /* else No action required */
    /* End of (ICU_FALLING_EDGE == LpChannelConfig->ucIcuChannelType) */
    /* Reset Channel Status Clear Trigger Register */
    LpATUTimerCSubBlkRegs->usAtuTimerCTSCRCm = ICU_RESET_ATU_TIMERC_TSCRCm_VAL;
  } /* else No action required */
  /* End of (ICU_HW_ATU_TIMERC == LpChannelConfig->ucIcuChannelType) */
  #endif /* End of (ICU_ATU_TIMERC_UNIT_USED == STD_ON) */
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disable interrupts */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress),ICU_DISABLE_EIMK_MASK);                               /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */

  switch (LddMeasurementMode)
  {
    /* Edge Counter Mode */
  case ICU_MODE_EDGE_COUNTER:
  {
    #if (ICU_EDGE_COUNT_API == STD_ON)
    /* Configure the channel in Edge Counter Mode */
    Icu_HW_Atu_EdgeCountingInit(LpChannelUserRegConfig);
    #endif
    break;
  }

  /* Timestamp Mode */
  case ICU_MODE_TIMESTAMP:
  {
    #if (ICU_TIMESTAMP_API == STD_ON)
    /* Configure the channel in Timestamp Mode */
    Icu_HW_Atu_TimestampInit(LpChannelUserRegConfig);
    #endif
    break;
  }

  /* Signal Measurement Mode */
  case ICU_MODE_SIGNAL_MEASUREMENT:
  {
    #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
    /* Configure the channel in Signal Measurement Mode */
    Icu_HW_Atu_SignalMeasurementInit(LpChannelUserRegConfig);
    #endif
    break;
  }
  default: {
    /* edgedetect do nothing */
    break;
  }
  }
  /* End of switch case */

  #if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))
  if (ICU_TRUE == LpATUChannelConfig->ucIcuEnableNoiseCancellation)                                                     /* PRQA S 1881 # JV-01 */
  {
    /* Loading value of Noise cancellation period into Noise Canceler Register*/
    *(LpATUChannelConfig->pNCRPeriodRegAdress) = LpATUChannelConfig->usIcuNoiseCancellationPeriod;
  } /* else No action required */
#endif /* End of #if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || \
                                                                      (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))*/
} /* End of Internal function Icu_HW_Atu_ChannelInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Icu_HW_Atu_UnitDeInit
**
** Service ID            : None
**
** Description           : This service De-Initializes the hardware for all the
**                         configured channels based on the measurement mode.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
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
** Global Variables      : Icu_GpTimerClkBusConfig,
**                         Icu_GpNoiseCancellationConfig
**
** Functions invoked     : None
**
** Registers Used        : TIOR1A, GRCmn, TIORCm, EICn,
**                         NCMR, NCMCR1A, NCMCR2A, TIOR2A, NCMCR1C, NCMCR2C, NCCRC
**
** Reference ID          : ICU_DUD_ACT_070, ICU_DUD_ACT_070_REG002, ICU_DUD_ACT_070_REG003, ICU_DUD_ACT_070_REG004
** Reference ID          : ICU_DUD_ACT_070_REG005, ICU_DUD_ACT_070_REG006, ICU_DUD_ACT_070_REG001
***********************************************************************************************************************/
#if (ICU_DE_INIT_API == STD_ON)

#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Atu_UnitDeInit(void)
{
  #if (ICU_TIMER_CLK_BUS_NOT_USED != ICU_TIMER_CLK_BUS_SELECTION_CONFIGURED)
  /* Defining a pointer to the clock bus selection configuration parameters */
  P2CONST(Icu_ATU_ClockBusConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTimerClkBusConfig;
  #endif

  /* Defining a pointer to the clock bus selection Control Register */
  P2VAR(volatile uint8, AUTOMATIC, ICU_CONFIG_DATA) LpClkBusCntrlReg;
  /* Local counter variable */
  uint8 LucCnt;

  #if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))

  /* Defining a pointer to the Timer Noise Cancellation configuration */
  P2CONST(Icu_NoiseCancellationConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpNoiseCancellationConfig;

  #if (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON)
  /* Defining a pointer to the NCCRC register Configuration parameter*/
  P2CONST(Icu_NCCRCCntrlRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpNCCRCCntrlRegConfig;
  
  #endif /* End of #if (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) */
  #endif /* ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))*/

  #if (ICU_TIMER_CLK_BUS_NOT_USED != ICU_TIMER_CLK_BUS_SELECTION_CONFIGURED)
  /* Update the previous input use pointer to point to the current channel */
  LpTimerClkBusConfig = Icu_GpTimerClkBusConfig;
  /* default Clock bus selection for the configured timer unit */

  for (LucCnt = ICU_ZERO; LucCnt < ICU_TIMER_CLK_BUS_SELECTION_CONFIGURED; LucCnt++)
  {
    /* Load clock bus selection for the timer unit */
    LpClkBusCntrlReg = LpTimerClkBusConfig->pAtuClkBusCntrlRegs;                                                        /* PRQA S 0317 # JV-01 */

    *(LpClkBusCntrlReg) = (*(LpClkBusCntrlReg) & ICU_CLK_BUS_SELECT_MASK);

    /* Increment the pointer to point to next previous input channel */
    LpTimerClkBusConfig++;

  } /* End of clock bus selection channel for loop */
  #endif /* End of #if (ICU_TIMER_CLK_BUS_NOT_USED != ICU_TIMER_CLK_BUS_SELECTION_CONFIGURED)*/

  #if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))
  /* Update the local pointer to point to the Timer Noise Cancellation configuration. */
  LpNoiseCancellationConfig = Icu_GpNoiseCancellationConfig;

  if (ICU_NC_PLL_ENABLE == LpNoiseCancellationConfig->ucAtuNCMRCntrlRegValue)
  {
    /* Resetting the NCCSEL bit in the NCMR register to ZERO */
    *(LpNoiseCancellationConfig->pAtuNCMRCntrlReg) &= (uint8)~ICU_NC_PLL_ENABLE;
  } /* else No action required */

  #if (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON)
  /* Resetting the Mode Selection Register values to ZERO */
  *(LpNoiseCancellationConfig->pAtuNCMCR1ACntrlReg) = ICU_RESET_ATU_NCMCR1A_VAL;

  /* Resetting the Mode Selection Register values to ZERO */
  *(LpNoiseCancellationConfig->pAtuNCMCR2ACntrlReg) = ICU_RESET_ATU_NCMCR2A_VAL;
  /* Reset Timer I/O Control Register 2A values to ZERO */
  *(LpNoiseCancellationConfig->pAtuTIOR2ACntrlReg) = ICU_RESET_ATU_TIOR2A_VAL;
  #endif /* End of #if (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON) */

  #if (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON)
  /* Resetting the Mode Selection Register values to ZERO */
  *(LpNoiseCancellationConfig->pAtuNCMCR1CCntrlReg) = (uint16)ICU_RESET_ATU_NCMCR1C_VAL;

  /* Resetting the Mode Selection Register values to ZERO */
  *(LpNoiseCancellationConfig->pAtuNCMCR2CCntrlReg) = (uint16)ICU_RESET_ATU_NCMCR2C_VAL;

  LpNCCRCCntrlRegConfig = LpNoiseCancellationConfig->pNCCRCCntrlRegConfig;                                              /* PRQA S 0317 # JV-01 */

  for (LucCnt = ICU_ZERO; LucCnt < LpNoiseCancellationConfig->ucTotalTimerCConfigured; LucCnt++)
  {
    /* Reset the Noise Canceler Control Register values to ZERO */
    *((LpNoiseCancellationConfig->pAtuNCCRCCntrlRegAdrs + LpNCCRCCntrlRegConfig->ucAtuNCCRCSubBlockIndex)) =            /* PRQA S 0488 # JV-01 */
                                                                                      ICU_RESET_ATU_NOISE_CANCELER_VAL;
    LpNCCRCCntrlRegConfig++;
  } /* End loop */

#endif /* End of #if (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) */
#endif /* End of #if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || \
                                                                      (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))*/

} /* End of Internal function Icu_HW_Atu_UnitDeInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_DE_INIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_HW_Atu_ChannelDeInit
**
** Service ID            : None
**
** Description           : This service De-Initializes the hardware for all the
**                         configured channels based on the measurement mode.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
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
** Global Variables      : Icu_GpChannelUserRegConfig, Icu_GpChannelConfig, Icu_GpChannelRamData.
**
** Functions invoked     : RH850_SV_SET_ICR_SYNCP
**
** Registers Used        : TIOR1A, TSCRA, GRCmn, TIORCm, TSCRCm, EICn,
**                         NCMR, NCMCR1A, NCMCR2A, TIOR2A, NCMCR1C, NCMCR2C, NCCRC
**
** Reference ID          : ICU_DUD_ACT_089, ICU_DUD_ACT_089_REG001, ICU_DUD_ACT_089_REG002, ICU_DUD_ACT_089_REG003
** Reference ID          : ICU_DUD_ACT_089_REG004, ICU_DUD_ACT_089_REG005, ICU_DUD_ACT_089_REG006
** Reference ID          : ICU_DUD_ACT_089_REG007, ICU_DUD_ACT_089_REG008, ICU_DUD_ACT_089_GBL001
** Reference ID          : ICU_DUD_ACT_089_GBL004, ICU_DUD_ACT_089_GBL005, ICU_DUD_ACT_089_REG019
***********************************************************************************************************************/
#if (ICU_DE_INIT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Atu_ChannelDeInit(const Icu_ChannelType LddChannel)                                 /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  #if ((ICU_ATU_TIMERC_UNIT_USED == STD_ON) || (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || \
                                                                        (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))
  /* Defining a pointer to the ATU channel configuration parameters */
  P2CONST(Icu_ATUChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelConfig;
  #endif
  /* Defining a pointer to the Ram Data */
  P2VAR(volatile Icu_ChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpRamData;

  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ATUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelUserRegConfig;

  #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)

  /* Initialize pointer to the base address of the current channel */
  P2VAR(Icu_ATUTimerACommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerACommonRegs;                                 /* PRQA S 3432 # JV-01 */
  #endif /* End for #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON) */

  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  /* Initialize pointer to the base address of the current channel */
  P2VAR(Icu_ATUTimerCSubBlkUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerCSubBlkRegs;                                 /* PRQA S 3432 # JV-01 */

  /* Initialize pointer to the base address of the current channel */
  P2VAR(Icu_ATUTimerCChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerCChannelRegs;                               /* PRQA S 3432 # JV-01 */

  #endif /* End of #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON) */

  /* Update the channel pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  #if ((ICU_ATU_TIMERC_UNIT_USED == STD_ON) || (ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || \
                                                                        (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))
  /* Initialize all the configured Icu Channels */
  LpATUChannelConfig = Icu_GpChannelConfig[LddChannel].pHWIPChannelConfig;                                              /* PRQA S 0317 # JV-01 */
  #endif

  /* Initialize all the configured Timer Channels */
  LpATUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannel].pHWChannelUserRegConfig;                           /* PRQA S 0317 # JV-01 */
  /* Load the channel data pointer */
  LpRamData = &Icu_GpChannelRamData[LddChannel];
  /* Initialize each channel status as idle */
  LpRamData->ucChannelStatus = (uint8)ICU_IDLE;
  /* Disable notification for each channel */
  LpRamData->ucNotificationEnable = (uint8)ICU_FALSE;                                                                   /* PRQA S 4304 # JV-01 */
  /* Initialize the status of result channel as False */
  LpRamData->blResultComplete = ICU_FALSE;
  #if (STD_ON == ICU_SET_MODE_API)
  /* Initialize running status for each channel */
  LpRamData->ucChannelRunning = (uint8)ICU_FALSE;                                                                       /* PRQA S 4304 # JV-01 */
  #endif

  #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
  if (ICU_HW_ATU_TIMERA == LpChannelConfig->ucIcuChannelType)
  {
    /* Initialize pointer to the base address of the current channel */
    LpATUTimerACommonRegs =
             (P2VAR(Icu_ATUTimerACommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelUserRegConfig->pTimerCntlRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Reset the value of Channel TIOR1A Register */
    LpATUTimerACommonRegs->usAtuTimerATIOR1A = ICU_RESET_ATU_TIMERA_ATIOR1A_VAL;
    /* Reset Channel Status Clear Trigger Register */
    LpATUTimerACommonRegs->usAtuTimerATSCRA = ICU_RESET_ATU_TIMERA_ATSCRA_VAL;

    /* Reset TIERA timer interrupt enable register A  */
    LpATUTimerACommonRegs->usAtuTimerATIERA = ICU_RESET_ATU_TIMERA_TIERA_VAL;
  } /* else No action required */
  /* End of (ICU_HW_ATU_TIMERA == LpChannelConfig->ucIcuChannelType) */
  #endif /* End of #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON) */
  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  if (ICU_HW_ATU_TIMERC == LpChannelConfig->ucIcuChannelType)
  {
    /* Initialize pointer to the base address of the current channel */
    LpATUTimerCSubBlkRegs =
             (P2VAR(Icu_ATUTimerCSubBlkUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelUserRegConfig->pTimerCntlRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Initialize pointer to the base address of the current channel */
    LpATUTimerCChannelRegs =
            (P2VAR(Icu_ATUTimerCChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pTimerChannelUserRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Reset the value of Channel capture Register */
    LpATUTimerCChannelRegs->ulAtuTimerCGRCmn = ICU_RESET_ATU_TIMERC_GRCmn_VAL;

    /* Reset the value of Channel TIORC Register */
    LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm = ICU_RESET_ATU_TIMERC_TIORCm_VAL;

    /* Reset Channel Status Clear Trigger Register */
    LpATUTimerCSubBlkRegs->usAtuTimerCTSCRCm = ICU_RESET_ATU_TIMERC_TSCRCm_VAL;

    /* Reset TIERCx timer interrupt enable register C */
    LpATUTimerCSubBlkRegs->usAtuTimerCTIERCm = ICU_RESET_ATU_TIMERC_TIERC_VAL;

  } /* else No action required */
  /* End of (ICU_HW_ATU_TIMERC == LpChannelConfig->ucIcuChannelType) */
  #endif /* End of #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON) */

  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disable interrupts */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress),ICU_DISABLE_EIMK_MASK);                               /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */

  /* Check channel connected to Timers based on the measurement mode */
  #if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))
  if (ICU_TRUE == LpATUChannelConfig->ucIcuEnableNoiseCancellation)                                                     /* PRQA S 1881 # JV-01 */
  {
    /* Resetting the Noise Canceler register value to Zero */
    *(LpATUChannelConfig->pNCRPeriodRegAdress) = (uint16)ICU_RESET_ATU_NOISE_CANCELER_VAL;
  } /* else No action required */
  #endif /* End of #if ((ICU_ATUC_NOISE_CANCELLATION_ENABLE == STD_ON) || \
                                                                      (ICU_ATUA_NOISE_CANCELLATION_ENABLE == STD_ON))*/

} /* End of Internal function Icu_HW_Atu_ChannelDeInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_DE_INIT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_HW_Atu_EdgeCountingInit
**
** Service ID            : None
**
** Description           : This service initializes the channel configured for edge counting mode.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LpChannelUserRegConfig
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpEdgeCountData.
**
** Functions invoked     : None
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_071, ICU_DUD_ACT_071_GBL001
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE)
  Icu_HW_Atu_EdgeCountingInit(P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig) /* PRQA S 1505 # JV-01 */
{
  /* Local variable used to store the Ram index */
  uint8 LucIndex;

  /* Load the Ramdata Index */
  LucIndex = LpChannelUserRegConfig->ucRamDataIndex;

  /* Reset the edge count value */
  Icu_GpEdgeCountData[LucIndex].ulIcuEdgeCount = ICU_DOUBLE_ZERO;

} /* End of Internal function Icu_HW_Atu_EdgeCountingInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_EDGE_COUNT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_HW_Atu_TimestampInit
**
** Service ID            : None
**
** Description           : This service is used to initialize the channel configured for Timestamp Measurement mode.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LpChannelUserRegConfig
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpTimeStampData.
**
** Functions invoked     : None
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_072, ICU_DUD_ACT_072_GBL001
***********************************************************************************************************************/
#if (ICU_TIMESTAMP_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE)
     Icu_HW_Atu_TimestampInit(P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig) /* PRQA S 1505 # JV-01 */
{
  /* Local variable used to store the channel index */
  uint8 LucIndex;

  /* Read the Timestamp Channel ram index */
  LucIndex = LpChannelUserRegConfig->ucRamDataIndex;

  /* Reset buffer pointer and index */
  Icu_GpTimeStampData[LucIndex].usTimestampIndex = (uint16)ICU_BUFFER_IDX_INIT_VAL;

} /* End of Internal function Icu_HW_Atu_TimestampInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_TIMESTAMP_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_HW_Atu_SignalMeasurementInit
**
** Service ID            : None
**
** Description           : This service initializes the channel configured in Signal Measurement Mode.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LpChannelUserRegConfig
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpSignalMeasurementData.
**
** Functions invoked     : None
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_073, ICU_DUD_ACT_073_GBL001,
** Reference ID          : ICU_DUD_ACT_073_GBL002, ICU_DUD_ACT_073_GBL003, ICU_DUD_ACT_073_GBL004
***********************************************************************************************************************/
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Atu_SignalMeasurementInit                                                           /* PRQA S 1505 # JV-01 */
                             (P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig)
{
  /* Local variable used to store the Timer Instance */
  uint8 LucIndex;
  /* Read the Signal Measurement Channel ram index */
  LucIndex = LpChannelUserRegConfig->ucRamDataIndex;
  /* Initialize the Signal Active time to zero */
  Icu_GpSignalMeasurementData[LucIndex].ulSignalActiveTime = (uint32)ICU_ACTIVE_TIME_INIT_VAL;
  /* Initialize the Signal Period time to zero */
  Icu_GpSignalMeasurementData[LucIndex].ulSignalPeriodTime = (uint32)ICU_SIGNAL_PERIOD_TIME_INIT_VAL;
  /* Initialize the prev Signal active time to zero */
  Icu_GpSignalMeasurementData[LucIndex].ulPrevSignalActiveTime = (uint32)ICU_ACTIVE_TIME_INIT_VAL;
  /* Initialize the period measurement status to idle */
  Icu_GpSignalMeasurementData[LucIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_IDLE;
} /* End of Internal function Icu_HW_Atu_SignalMeasurementInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of  (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_HW_Atu_SetActivation
**
** Service ID            : None
**
** Description           : This service configures the hardware to the active edges of the requested channel.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel, ActiveEdge
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : NA
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelRamData, Icu_GpChannelUserRegConfig.
**
** Functions invoked     : RH850_SV_CLEAR_ICR_SYNCP
**
** Registers Used        : TIOR1A, TIORCm
**
** Reference ID          : ICU_DUD_ACT_074, ICU_DUD_ACT_074_REG001, ICU_DUD_ACT_074_REG002,
** Reference ID          : ICU_DUD_ACT_074_REG003, ICU_DUD_ACT_074_REG004, ICU_DUD_ACT_074_REG005
** Reference ID          : ICU_DUD_ACT_074_REG006, ICU_DUD_ACT_074_REG007, ICU_DUD_ACT_074_GBL001
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE)
                        Icu_HW_Atu_SetActivation(const Icu_ChannelType LddChannel, const Icu_ActivationType ActiveEdge) /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ATUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelUserRegConfig;

  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  /* Defining a pointer to the ATU channel configuration parameters */
  P2CONST(Icu_ATUChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelConfig;
  #endif

  #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
  /* Defining a pointer to point to the TimerA registers */
  P2VAR(Icu_ATUTimerACommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerACommonRegs;                                 /* PRQA S 3432 # JV-01 */
  #endif /* End of #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON) */

  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  /* Initialize pointer to the base address of the current channel */
  P2VAR(Icu_ATUTimerCSubBlkUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerCSubBlkRegs;                                 /* PRQA S 3432 # JV-01 */
  #endif /* End of #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON) */

  /* To store Channel Measurement Mode */
  Icu_MeasurementModeType LddMeasurementMode;

  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  LpATUChannelConfig = Icu_GpChannelConfig[LddChannel].pHWIPChannelConfig;                                              /* PRQA S 0317 # JV-01 */
  #endif

  /* Read measurement mode */
  LddMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  /* Update the Timer channel configuration pointer to point to the current channel */
  LpATUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannel].pHWChannelUserRegConfig;                           /* PRQA S 0317 # JV-01 */

  if (LddMeasurementMode != ICU_MODE_SIGNAL_MEASUREMENT)
  {
    #if ((ICU_ATU_TIMERA_UNIT_USED == STD_ON))
    if (ICU_HW_ATU_TIMERA == LpChannelConfig->ucIcuChannelType)
    {
      /* Initialize pointer to the base address of the current channel */
      LpATUTimerACommonRegs = (P2VAR(Icu_ATUTimerACommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA))                          /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                                                                             LpChannelConfig->pCntlRegs;

      /* Mask the active edge setting bit in th cntrl register */
      LpATUTimerACommonRegs->usAtuTimerATIOR1A &= (LpATUChannelUserRegConfig->usChannelModeUserRegSettings);

      /* Set the active edge setting bit in th cntrl register */
      if (ICU_RISING_EDGE == ActiveEdge)
      {
        LpATUTimerACommonRegs->usAtuTimerATIOR1A |=
                         (uint16)((uint16)ICU_ATU_RISING_EDGE_MASK << (LpChannelConfig->usChannelMaskValue * ICU_TWO));
      }
      else if (ICU_FALLING_EDGE == ActiveEdge)
      {
        LpATUTimerACommonRegs->usAtuTimerATIOR1A |=
                      (uint16)((uint16)(ICU_ATU_FALLING_EDGE_MASK) << (LpChannelConfig->usChannelMaskValue * ICU_TWO));
      }
      else /* if (ActiveEdge == ICU_BOTH_EDGES) */
      {
        LpATUTimerACommonRegs->usAtuTimerATIOR1A |=
                           (uint16)((uint16)ICU_ATU_BOTH_EDGE_MASK << (LpChannelConfig->usChannelMaskValue * ICU_TWO));
      }
    } /* else No action required */
    #endif /* End of (ICU_ATU_TIMERA_UNIT_USED == STD_ON) */
    #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
    if (ICU_HW_ATU_TIMERC == LpChannelConfig->ucIcuChannelType)
    {
      /* Initialize pointer to the base address of the current channel */
      LpATUTimerCSubBlkRegs =
              (P2VAR(Icu_ATUTimerCSubBlkUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pTimerSubBlkUserRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

      /* Mask and set the active edge */
      LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm &= LpATUChannelUserRegConfig->usChannelModeUserRegSettings;

      if (ICU_RISING_EDGE == ActiveEdge)
      {
        LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm |=
            (uint16)((uint16)(ICU_SET_INPUT_CAPTURE_MODE | ICU_ATU_RISING_EDGE_MASK)
                                                                  << (LpChannelConfig->usChannelMaskValue * ICU_FOUR));
      }
      else if (ICU_FALLING_EDGE == ActiveEdge)
      {
        LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm |=
            (uint16)((uint16)(ICU_SET_INPUT_CAPTURE_MODE | ICU_ATU_FALLING_EDGE_MASK)
                                                                  << (LpChannelConfig->usChannelMaskValue * ICU_FOUR));
      }
      else /* if (ActiveEdge == ICU_BOTH_EDGES) */
      {
        LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm |=
            (uint16)((uint16)(ICU_SET_INPUT_CAPTURE_MODE | ICU_ATU_BOTH_EDGE_MASK)
                                                                  << (LpChannelConfig->usChannelMaskValue * ICU_FOUR));
      }
    } /* else No action required */
    #endif /* End of (ICU_ATU_TIMERC_UNIT_USED == STD_ON) */

    #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
    /* Check if the Interrupt register is present for particular channel */
    if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
    {
      /* Clear the pending interrupts */
      RH850_SV_CLEAR_ICR_SYNCP(16, LpChannelConfig->pIntrCntlAddress, (uint16)ICU_CLEAR_PENDING_INTR_MASK);             /* PRQA S 1006 # JV-01 */
    } /* else No action required */
    #endif /* End of #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON) */

    /* Initialize channel status as idle */
    Icu_GpChannelRamData[LddChannel].ucChannelStatus = (uint8)ICU_IDLE;

  } /* else No action required */
} /* End of Internal function Icu_HW_Atu_SetActivation */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Icu_HW_Atu_StartCountMeasurement
**
** Service ID            : None
**
** Description           : This service routine starts the count measurement.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpChannelUserRegConfig, Icu_GpChannelConfig,
**                         Icu_GpSignalMeasurementData.
**
** Functions invoked     : RH850_SV_CLEAR_ICR_SYNCP, ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION
**
** Registers Used        : TCNTA, TCNTCm, GRCmn, ATUENR, TSTRC, EICn, TSCRA, TSCRC
**
** Reference ID          : ICU_DUD_ACT_075, ICU_DUD_ACT_075_CRT001, ICU_DUD_ACT_075_CRT002
** Reference ID          : ICU_DUD_ACT_075_REG002, ICU_DUD_ACT_075_REG003, ICU_DUD_ACT_075_REG004
** Reference ID          : ICU_DUD_ACT_075_REG006, ICU_DUD_ACT_075_REG007, ICU_DUD_ACT_075_REG008
** Reference ID          : ICU_DUD_ACT_075_REG009, ICU_DUD_ACT_075_REG011, ICU_DUD_ACT_075_GBL001
** Reference ID          : ICU_DUD_ACT_075_REG010, ICU_DUD_ACT_075_REG005, ICU_DUD_ACT_075_REG001
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Atu_StartCountMeasurement(const Icu_ChannelType LddChannel)                         /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* Local variable to store the measurement mode of a channel */
  Icu_MeasurementModeType LddMeasurementMode;
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ATUChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelConfig;
  /* Local variable of index */
  uint8 LucRamIndex;
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  P2CONST(Icu_ATUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelUserRegConfig;
  /* Defining a pointer to point to the Common control registers */
  P2VAR(Icu_ATUCommonCntlRegs, AUTOMATIC, ICU_CONFIG_DATA) LpCommonCntlReg;                                             /* PRQA S 3432 # JV-01 */
  /* Pointer definition for Signal Measurement RAM data */
  #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
  P2VAR(Icu_ATUTimerACommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA)                                                        /* PRQA S 3432 # JV-01 */
  LpATUTimerACommonRegs;
  #endif
  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  /* Defining a pointer to point to the TimerC registers */
  P2VAR(Icu_ATUTimerCCommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerCCommonRegs;                                 /* PRQA S 3432 # JV-01 */
  /* Initialize pointer to the base address of the current channel */
  P2VAR(Icu_ATUTimerCSubBlkUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerCSubBlkRegs;                                 /* PRQA S 3432 # JV-01 */
  /* Initialize pointer to the base address of the current channel */
  P2VAR(Icu_ATUTimerCChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerCChannelRegs;                               /* PRQA S 3432 # JV-01 */
  #endif

  /* Read channel configuration pointer */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  LpATUChannelConfig = Icu_GpChannelConfig[LddChannel].pHWIPChannelConfig;                                              /* PRQA S 0317 # JV-01 */
  /* Read timer channel configuration pointer */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannel];
  LpATUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannel].pHWChannelUserRegConfig;                           /* PRQA S 0317 # JV-01 */
  /* Read the channel ram index */
  LucRamIndex = LpChannelUserRegConfig->ucRamDataIndex;

  /* Get the spinlock */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

  /* Read the channel's measurement mode */
  LddMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */

  if ((ICU_MODE_TIMESTAMP == LddMeasurementMode) || (ICU_MODE_SIGNAL_MEASUREMENT == LddMeasurementMode))
  {
    #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
    if (ICU_HW_ATU_TIMERA == LpChannelConfig->ucIcuChannelType)
    {
      /* Initialize pointer to the base address of the current timer unit */
      LpCommonCntlReg =
                      (P2VAR(Icu_ATUCommonCntlRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pAtuCommonCntlRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
      /* Initialize pointer to the base address of the current channel */
      LpATUTimerACommonRegs =
             (P2VAR(Icu_ATUTimerACommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelUserRegConfig->pTimerCntlRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

      /* Disable TAE bit in ATUENR register */
      (LpCommonCntlReg->ucAtuTimerATUENR) &= (uint8)~ICU_ATUENR_TAE_ENABLE;

      /* Assign the up count value to TCNTA register */
      LpATUTimerACommonRegs->ulAtuTimerATCNTA = ICU_ATU_TIMER_INITIAL_CNT_VAL;
      /* Reset Channel Status Clear Trigger Register */
      LpATUTimerACommonRegs->usAtuTimerATSCRA = ICU_RESET_ATU_TIMERA_ATSCRA_VAL;

    } /* else No action required */
    #endif /* End of #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON) */
    #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
    if (ICU_HW_ATU_TIMERC == LpChannelConfig->ucIcuChannelType)
    {

      /* Initialize pointer to the base address of the current timer unit */
      LpCommonCntlReg =
                      (P2VAR(Icu_ATUCommonCntlRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pAtuCommonCntlRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

      LpATUTimerCCommonRegs = (P2VAR(Icu_ATUTimerCCommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA))                          /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                                                                             LpChannelConfig->pCntlRegs;

      LpATUTimerCSubBlkRegs =
              (P2VAR(Icu_ATUTimerCSubBlkUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pTimerSubBlkUserRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

      LpATUTimerCChannelRegs =
            (P2VAR(Icu_ATUTimerCChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pTimerChannelUserRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

      /* Set the bit corresponding to the channel no. in TSTRC register */
      LpATUTimerCCommonRegs->usAtuTimerCTSTRC &=
                                      (uint16)(~((LpATUChannelUserRegConfig->usTSTRCValue) & ICU_ATU_TIMER_GLOBL_MASK));

      /* Assign the up count value to TCNTC register */
      LpATUTimerCSubBlkRegs->ulAtuTimerCTCNTCm = ICU_ATU_TIMER_INITIAL_CNT_VAL;
      LpATUTimerCChannelRegs->ulAtuTimerCGRCmn = ICU_ATU_TIMER_INITIAL_CNT_VAL;
      /* Reset Channel Status Clear Trigger Register */
      LpATUTimerCSubBlkRegs->usAtuTimerCTSCRCm = ICU_RESET_ATU_TIMERC_TSCRCm_VAL;
    } /* else No action required */
    #endif /* End of #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON) */
  } /* else No action required */

  /* Check if the Interrupt register is present for particular channel */
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
    /* Clear the pending interrupts */
    RH850_SV_CLEAR_ICR_SYNCP(16, LpChannelConfig->pIntrCntlAddress, (uint16)ICU_CLEAR_PENDING_INTR_MASK);               /* PRQA S 1006 # JV-01 */
    #endif
    /* Enabling the Interrupt processing */
    #if ((ICU_ENABLE_WAKEUP_API == STD_ON) || (ICU_NOTIFY_WAKEUP_INTERRUPT == STD_ON))
    if (ICU_MODE_SLEEP == Icu_GenModuleMode)
    {
      /* No action required */
    }
    else
    #endif
    {
      RH850_SV_CLEAR_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_ENABLE_EIMK_MASK);                           /* PRQA S 0751, 1006 # JV-01, JV-01 */
    }
  } /* else No action required */

  if (ICU_MODE_SIGNAL_MEASUREMENT == LddMeasurementMode)
  {
    /* Initialize period measurement status to idle */
    Icu_GpSignalMeasurementData[LucRamIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_IDLE;

    /* If the channel is duty cycle channel, set to additional channel */
    if (((uint8)(LpChannelUserRegConfig->ucChannelProperties & ICU_DUTY_PERIOD_ENABLED_MASK)) ==
                                                                                          ICU_DUTY_PERIOD_ENABLED_MASK)
    {
      /* Check if the Interrupt register is present for particular channel */
      if (NULL_PTR != Icu_GpChannelConfig[LddChannel + ICU_ONE].pIntrCntlAddress)                                       /* PRQA S 3416 # JV-01 */
      {
        #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)
        /* Clear the pending interrupts */
        RH850_SV_CLEAR_ICR_SYNCP(16, Icu_GpChannelConfig[LddChannel + ICU_ONE].pIntrCntlAddress,                        /* PRQA S 0404, 1006, 3464 # JV-01, JV-01, JV-01 */
                                                                                  (uint16)ICU_CLEAR_PENDING_INTR_MASK);
        #endif
        /* Enabling the Interrupt processing */
        #if ((ICU_ENABLE_WAKEUP_API == STD_ON) || (ICU_NOTIFY_WAKEUP_INTERRUPT == STD_ON))
        if (ICU_MODE_SLEEP == Icu_GenModuleMode)
        {
          /* No action required */
        }
        else
        #endif
        {
         /* Enable interrupts */
         RH850_SV_CLEAR_ICR_SYNCP(8, Icu_GpChannelConfig[LddChannel + ICU_ONE].pIntrCntlAddress, ICU_ENABLE_EIMK_MASK); /* PRQA S 0404, 0751, 1006, 3464 # JV-01, JV-01, JV-01, JV-01 */
        }
      } /* else No action required */
    } /* else No action required */
  } /* else No action required */

  if ((ICU_MODE_TIMESTAMP == LddMeasurementMode) || (ICU_MODE_SIGNAL_MEASUREMENT == LddMeasurementMode))
  {
    #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
    if (ICU_HW_ATU_TIMERA == LpChannelConfig->ucIcuChannelType)
    {
      /* Enable TAE bit in ATUENR register */
      LpCommonCntlReg->ucAtuTimerATUENR |= (uint8)ICU_ATUENR_TAE_ENABLE;                                                /* PRQA S 2962 # JV-01 */
    } /* else No action required */
    #endif /* End of #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON) */
    #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
    if (ICU_HW_ATU_TIMERC == LpChannelConfig->ucIcuChannelType)
    {
      /* Ebable TCE bit in ATUENR register */
      LpCommonCntlReg->ucAtuTimerATUENR |= (uint8)ICU_ATUENR_TCE_ENABLE;

      /* Set the bit corresponding to the channel no. in TSTRC register */
      LpATUTimerCCommonRegs->usAtuTimerCTSTRC |=                                                                        /* PRQA S 2962 # JV-01 */
                                        (uint16)((LpATUChannelUserRegConfig->usTSTRCValue) & ICU_ATU_TIMER_GLOBL_MASK);
    } /* else No action required */
    #endif /* End of #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON) */
  } /* else No action required */
  #if (STD_ON == ICU_SET_MODE_API)
  /* Initialize running status for each channel */
  Icu_GpChannelRamData[LddChannel].ucChannelRunning = (uint8)ICU_TRUE;                                                  /* PRQA S 4304 # JV-01 */
  #endif
  /* Exit local critical section */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
} /* End of Internal function Icu_HW_Atu_StartCountMeasurement */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Atu_StopCountMeasurement
**
** Service ID            : None
**
** Description           : This service routine stops the count measurement.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpChannelUserRegConfig, Icu_GpChannelConfig,
**
** Functions invoked     : RH850_SV_SET_ICR_SYNCP, ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION
**
** Registers Used        : ATUENR, TSTRC, EICn
**
** Reference ID          : ICU_DUD_ACT_076, ICU_DUD_ACT_076_CRT001, ICU_DUD_ACT_076_CRT002,ICU_DUD_ACT_076_REG001
** Reference ID          : ICU_DUD_ACT_076_REG002, ICU_DUD_ACT_076_REG003, ICU_DUD_ACT_076_REG004
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Atu_StopCountMeasurement(const Icu_ChannelType LddChannel)                          /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ATUChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelConfig;
  #endif

  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ATUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelUserRegConfig;
  #endif
  /* Local variable to store the measurement mode of a channel */
  Icu_MeasurementModeType LddMeasurementMode;
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;

  #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
  /* Defining a pointer to point to the Common control registers */
  P2VAR(Icu_ATUCommonCntlRegs, AUTOMATIC, ICU_CONFIG_DATA) LpCommonCntlReg;                                             /* PRQA S 3432 # JV-01 */
  #endif
  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  /* Defining a pointer to point to the TimerC registers */
  P2VAR(Icu_ATUTimerCCommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerCCommonRegs;                                 /* PRQA S 3432 # JV-01 */
  #endif

  /* Read channel configuration pointer */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
  LpATUChannelConfig = Icu_GpChannelConfig[LddChannel].pHWIPChannelConfig;                                              /* PRQA S 0317 # JV-01 */
  #endif

  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  LpATUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannel].pHWChannelUserRegConfig;                           /* PRQA S 0317 # JV-01 */
  #endif
  /* Read the channel's measurement mode */
  LddMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */

  /* Read timer channel configuration pointer */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannel];

  /* Get the spinlock */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  /* Check if the Interrupt register is present for particular channel */
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disable interrupts */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);                              /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */

  if (ICU_MODE_SIGNAL_MEASUREMENT == LddMeasurementMode)
  {
    /* If the channel is duty cycle channel, disable interrupt for additional channel */
    if (((uint8)(LpChannelUserRegConfig->ucChannelProperties &
                                                         ICU_DUTY_PERIOD_ENABLED_MASK)) == ICU_DUTY_PERIOD_ENABLED_MASK)
    {
      /* Disable interrupts */
      /* Check if the Interrupt register is present for particular channel */
      if (NULL_PTR != Icu_GpChannelConfig[(LddChannel + ICU_ONE)].pIntrCntlAddress)                                     /* PRQA S 3416 # JV-01 */
      {
        RH850_SV_SET_ICR_SYNCP(8, Icu_GpChannelConfig[(LddChannel + ICU_ONE)].pIntrCntlAddress, ICU_DISABLE_EIMK_MASK); /* PRQA S 0404, 0751, 1006, 3464 # JV-01, JV-01, JV-01, JV-01 */

      } /* else No action required */
    } /* else No action required */
  } /* else No action required */

  if ((ICU_MODE_SIGNAL_MEASUREMENT == LddMeasurementMode) || (ICU_MODE_TIMESTAMP == LddMeasurementMode))
  {
    #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
    if (ICU_HW_ATU_TIMERA == LpChannelConfig->ucIcuChannelType)
    {
      /* Initialize pointer to the base address of the current timer unit */
      LpCommonCntlReg =
                      (P2VAR(Icu_ATUCommonCntlRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pAtuCommonCntlRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

      /* Disable TAE bit in ATUENR register */
      (LpCommonCntlReg->ucAtuTimerATUENR) &= (uint8)~ICU_ATUENR_TAE_ENABLE;
    } /* else No action required */
    #endif /* End of #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON) */
    #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
    if (ICU_HW_ATU_TIMERC == LpChannelConfig->ucIcuChannelType)
    {
      LpATUTimerCCommonRegs = (P2VAR(Icu_ATUTimerCCommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA))                          /* PRQA S 0316, 3432 # JV-01, JV-01 */
                                                                                             LpChannelConfig->pCntlRegs;
      /* Set the bit corresponding to the channel no. in TSTRC register */
      LpATUTimerCCommonRegs->usAtuTimerCTSTRC &=
                                     (uint16)(~((LpATUChannelUserRegConfig->usTSTRCValue) & ICU_ATU_TIMER_GLOBL_MASK));
    } /* else No action required */ 
    #endif /* End of #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON) */
  } /* else No action required */
  #if (STD_ON == ICU_SET_MODE_API)
  /* Initialize running status for each channel */
  Icu_GpChannelRamData[LddChannel].ucChannelRunning = (uint8)ICU_FALSE;                                                 /* PRQA S 4304 # JV-01 */
  #endif
  /* Release the spinlock */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
} /* End of Internal function Icu_HW_Atu_StopCountMeasurement */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Atu_ResetEdgeCount
**
** Service ID            : None
**
** Description           : This service resets the Timer Counter of the channel
**                         which is configured in Edge Counting Mode.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpEdgeCountData, Icu_GpChannelUserRegConfig.
**
** Functions invoked     : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_077, ICU_DUD_ACT_077_CRT001, ICU_DUD_ACT_077_CRT002, ICU_DUD_ACT_077_GBL001
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Atu_ResetEdgeCount(const Icu_ChannelType LddChannel)
{
  /* Defining a pointer to point to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  /* Channel Ram index */
  uint8 LucIndex;
  /* Update the Timer channel configuration pointer to point to the current channel */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannel];
  /* Enter Critical Section */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION);
  /* Read the RAM index */
  LucIndex = LpChannelUserRegConfig->ucRamDataIndex;
  /* Reset the global count variable */
  Icu_GpEdgeCountData[LucIndex].ulIcuEdgeCount = ICU_DOUBLE_ZERO;
  /* Exit Critical Section */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION);
} /* End of Internal function Icu_HW_Atu_ResetEdgeCount */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_EDGE_COUNT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_TimerIsr
**
** Service ID            : None
**
** Description           : This service routine invokes the required function based on the channel configuration
**                         for further calculations.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelUserRegConfig, Icu_GpChannelRamData, Icu_GpEdgeCountData.
**
** Functions invoked     : Icu_ServiceSignalMeasurement, Icu_ServiceTimestamp, ICU_DEM_REPORT_ERROR, 
**                         pIcuNotificationPointer.
**
** Registers Used        : ICRAm, GRCmn, TSCRCx, TSRCx, TSRA, TSCRA
**
** Reference ID          : ICU_DUD_ACT_080, ICU_DUD_ACT_080_GBL002, ICU_DUD_ACT_080_ERR001, ICU_DUD_ACT_080_GBL001
** Reference ID          : ICU_DUD_ACT_080_CRT001, ICU_DUD_ACT_080_CRT002
** Reference ID          : ICU_DUD_ACT_080_REG001, ICU_DUD_ACT_080_REG002
***********************************************************************************************************************/
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_CODE_FAST) Icu_TimerIsr(const Icu_ChannelType LddChannel)
{
  /* Defining a pointer to point to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  #if (ICU_EDGE_COUNT_API == STD_ON)
  /* Define a pointer to point to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  uint8 LucIndex;
  #endif

  #if (ICU_TIMESTAMP_API == STD_ON)
  uint32 LulCapturedTimestampVal;
  #endif

  #if (ICU_TIMESTAMP_API == STD_ON) || ((ICU_SIGNAL_MEASUREMENT_API == STD_ON) && (ICU_ATU_TIMERC_UNIT_USED == STD_ON))
  /* Defining a pointer to the ATU channel configuration parameters */
  P2CONST(Icu_ATUChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelConfig;
  #endif

  #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
  #if (ICU_TIMESTAMP_API == STD_ON)
  /* Defining a pointer to point to the TimerA registers */
  P2VAR(Icu_ATUTimerAChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerAChannelRegs;                               /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #endif
  #if(ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  /* Defining a pointer to point to the TimerA registers */
  P2VAR(Icu_ATUTimerACommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerACommonRegs;                                 /* PRQA S 3432 # JV-01 */
  #endif
  #endif

  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  #if (ICU_TIMESTAMP_API == STD_ON)
  /* Defining a pointer to point to the TimerA registers */
  P2VAR(Icu_ATUTimerCChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerCChannelRegs;                               /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #endif
  #if(ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  /* Defining a pointer to point to the TimerC registers */
  P2VAR(Icu_ATUTimerCSubBlkUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerCSubBlkRegs;                                 /* PRQA S 3432 # JV-01 */
  #endif
  #endif

  Icu_MeasurementModeType LddMeasurementMode;

  /* Update the channel pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  #if (ICU_TIMESTAMP_API == STD_ON) || ((ICU_SIGNAL_MEASUREMENT_API == STD_ON) && (ICU_ATU_TIMERC_UNIT_USED == STD_ON))
  LpATUChannelConfig = Icu_GpChannelConfig[LddChannel].pHWIPChannelConfig;                                              /* PRQA S 0317 # JV-01 */
  #endif

  #if (ICU_EDGE_COUNT_API == STD_ON)
  /* Update the timer channel pointer to point to the current channel */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannel];
  #endif
  /* Read the channel's measurement property */
  LddMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  /* Check the right EIC is reported */
  #if (ICU_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  if ((uint16)ICU_ZERO != (uint16)(*LpChannelConfig->pIntrCntlAddress & ICU_EIC_EIMK_MASK))
  {
    ICU_DEM_REPORT_ERROR(ICU_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
    /* Check whether the channel is configured for Signal Measurement */
    if (ICU_MODE_SIGNAL_MEASUREMENT == LddMeasurementMode)
    {
      #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
      if (ICU_HW_ATU_TIMERA == LpChannelConfig->ucIcuChannelType)
      {
        #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
        LpATUTimerACommonRegs =
                           (P2VAR(Icu_ATUTimerACommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA)) LpChannelConfig->pCntlRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
        /* Check and clear the overflow bit */
        if (ICU_TSRA_OVERFLOW_VALUE == (ICU_TSRA_OVERFLOW_VALUE & (LpATUTimerACommonRegs->usAtuTimerATSRA)))
        {
          #if (ICU_NOTIFICATION_CONFIG == STD_ON)
          /* Check if the function pointer address is present for particular channel */
          if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
          {
            /* callback notification */
            LpChannelConfig->pIcuNotificationPointer();
          } /* else No action required */
          #endif /* End of #if (ICU_NOTIFICATION_CONFIG == STD_ON) */
          /* Clear the overflow flag */
          LpATUTimerACommonRegs->usAtuTimerATSCRA |= ICU_TSRA_OVERFLOW_VALUE;
        } /* Else nothing */
        #endif
      }
      else
      {
        #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
        LpATUTimerCSubBlkRegs =
              (P2VAR(Icu_ATUTimerCSubBlkUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pTimerSubBlkUserRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

        /* Check overflow the counter */
        if (ICU_TSRC_OVERFLOW_VALUE == (ICU_TSRC_OVERFLOW_VALUE & (LpATUTimerCSubBlkRegs->usAtuTimerCTSRCm)))
        {
          #if (ICU_NOTIFICATION_CONFIG == STD_ON)
          /* Check if the function pointer address is present for particular channel */
          if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
          {
            /* callback notification */
            LpChannelConfig->pIcuNotificationPointer();
          } /* else No action required */
          #endif /* End of #if (ICU_NOTIFICATION_CONFIG == STD_ON) */
          /* Clear the overflow flag */
          LpATUTimerCSubBlkRegs->usAtuTimerCTSCRCm |= ICU_TSRC_OVERFLOW_VALUE;
        }
        #endif
      }
      /* Process Signal Measurement */
      Icu_ServiceSignalMeasurement(LddChannel);
      #endif
    }
    /* Check whether the channel is configured for Edge Detection */
    else if (ICU_MODE_SIGNAL_EDGE_DETECT == LddMeasurementMode)
    {
      #if (ICU_EDGE_DETECT_API == STD_ON)
      /* Get the spinlock since ucChannelStatus be updated by satellite core */
      ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Set channel input status as active */
      Icu_GpChannelRamData[LddChannel].ucChannelStatus = (uint8)ICU_ACTIVE;
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      #if (ICU_NOTIFICATION_CONFIG == STD_ON)
      /* Check if notification is enabled */
      if ((ICU_TRUE == Icu_GpChannelRamData[LddChannel].ucNotificationEnable))                                          /* PRQA S 0404, 1881, 3416 # JV-01, JV-01, JV-01 */
      {
        /* Check if the function pointer address is present for particular channel */
        if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
        {
          /* callback notification */
          LpChannelConfig->pIcuNotificationPointer();
        } /* else No action required */
      } /* else No action required */
      #endif /* End of #if (ICU_NOTIFICATION_CONFIG == STD_ON) */
      #endif /* #if (ICU_EDGE_DETECT_API == STD_ON) */
    }
    /* Check whether the channel is configured for Timestamp */
    else if (ICU_MODE_TIMESTAMP == LddMeasurementMode)
    {
      #if (ICU_TIMESTAMP_API == STD_ON)
      if (ICU_HW_ATU_TIMERA == LpChannelConfig->ucIcuChannelType)
      {
        #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
        /* Initialize pointer to the base address of the current channel */
        LpATUTimerAChannelRegs =
            (P2VAR(Icu_ATUTimerAChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pTimerSubBlkUserRegs;  /* PRQA S 0316, 3432 # JV-01, JV-01 */

        if ((uint8)ICU_ACTIVE == Icu_GpChannelRamData[LddChannel].ucChannelStatus)                                      /* PRQA S 0404, 3416 # JV-01, JV-01 */
        {
          /* Calculate captured value */
          LulCapturedTimestampVal = (LpATUTimerAChannelRegs->ulAtuTimerAICRAm);

          /* Process Timestamp */
          Icu_ServiceTimestamp(LddChannel, LulCapturedTimestampVal);
        } /* else No action required */
        #endif /* End of #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON) */
      }
      else
      {
        #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
        /* Initialize pointer to the base address of the current channel */
        LpATUTimerCChannelRegs =
            (P2VAR(Icu_ATUTimerCChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pTimerChannelUserRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

        if ((uint8)ICU_ACTIVE == Icu_GpChannelRamData[LddChannel].ucChannelStatus)                                      /* PRQA S 0404, 3416 # JV-01, JV-01 */
        {
          /* Calculate captured value */
          LulCapturedTimestampVal = (LpATUTimerCChannelRegs->ulAtuTimerCGRCmn);

          /* Process Timestamp */
          Icu_ServiceTimestamp(LddChannel, LulCapturedTimestampVal);
        } /* else No action required */
        #endif /* End of #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON) */
      } /* else No action required */
      #endif /* End of #if (ICU_TIMESTAMP_API == STD_ON) */
    } /* End of (LddMeasurementMode == ICU_MODE_TIMESTAMP) */
    /* Check whether the channel is configured for Edge Counter */
    else /* If (ICU_MODE_EDGE_COUNTER == LddMeasurementMode)*/
    {
      #if (ICU_EDGE_COUNT_API == STD_ON)
      if ((uint8)ICU_ACTIVE == Icu_GpChannelRamData[LddChannel].ucChannelStatus)                                        /* PRQA S 0404, 3416 # JV-01, JV-01 */
      {
        /* Read the edge count RAM index */
        LucIndex = LpChannelUserRegConfig->ucRamDataIndex;

        if (Icu_GpEdgeCountData[LucIndex].ulIcuEdgeCount < ICU_EDGECOUNT_RESET_VAL)                                     /* PRQA S 0404, 3416 # JV-01, JV-01 */
        {
          Icu_GpEdgeCountData[LucIndex].ulIcuEdgeCount++;                                                               /* PRQA S 0404, 3383, 3387 # JV-01, JV-01, JV-01 */
        }
        else
        {
          Icu_GpEdgeCountData[LucIndex].ulIcuEdgeCount = ICU_DOUBLE_ZERO;
          #if (ICU_NOTIFICATION_CONFIG == STD_ON)
          /* Check if the function pointer address is present for particular channel */
          if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
          {
            /* callback notification */
            LpChannelConfig->pIcuNotificationPointer();
          } /* else No action required */
          #endif /* End of #if (ICU_NOTIFICATION_CONFIG == STD_ON) */
        }
      } /* else No action required */
      #endif /* End of #if (ICU_EDGE_COUNT_API == STD_ON)*/
    }  /* End of (LddMeasurementMode == ICU_MODE_EDGE_COUNTER) */
  }
} /* End of Internal function Icu_TimerIsr */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Icu_ServiceSignalMeasurement
**
** Service ID            : None
**
** Description           : This service routine calculates the channel's Signal
**                         Time (Low, High, Period or Duty) based on its configuration.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpSignalMeasurementData,
**                         Icu_GpChannelUserRegConfig, Icu_GpChannelRamData
**
** Functions invoked     : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION
**
** Registers Used        : TIOR1A, ICRAm, TCNTA, TIORCm, GRCmn, TCNTCm, ATUENR, TSTRC
**
** Reference ID          : ICU_DUD_ACT_081, ICU_DUD_ACT_081_GBL001
** Reference ID          : ICU_DUD_ACT_081_GBL004, ICU_DUD_ACT_081_GBL005, ICU_DUD_ACT_081_GBL006
** Reference ID          : ICU_DUD_ACT_081_GBL007, ICU_DUD_ACT_081_GBL008, ICU_DUD_ACT_081_GBL009
** Reference ID          : ICU_DUD_ACT_081_GBL010, ICU_DUD_ACT_081_GBL011, ICU_DUD_ACT_081_GBL012
** Reference ID          : ICU_DUD_ACT_081_GBL013, ICU_DUD_ACT_081_GBL014, ICU_DUD_ACT_081_GBL015
** Reference ID          : ICU_DUD_ACT_081_GBL016, ICU_DUD_ACT_081_GBL017, ICU_DUD_ACT_081_GBL018
** Reference ID          : ICU_DUD_ACT_081_GBL019, ICU_DUD_ACT_081_GBL020, ICU_DUD_ACT_081_GBL021
** Reference ID          : ICU_DUD_ACT_081_GBL022, ICU_DUD_ACT_081_GBL023, ICU_DUD_ACT_081_GBL024
** Reference ID          : ICU_DUD_ACT_081_GBL025, ICU_DUD_ACT_081_GBL026, ICU_DUD_ACT_081_GBL027
** Reference ID          : ICU_DUD_ACT_081_GBL028, ICU_DUD_ACT_081_GBL029, ICU_DUD_ACT_081_GBL030
** Reference ID          : ICU_DUD_ACT_081_GBL031, ICU_DUD_ACT_081_CRT001, ICU_DUD_ACT_081_CRT002
** Reference ID          : ICU_DUD_ACT_081_REG001, ICU_DUD_ACT_081_REG002, ICU_DUD_ACT_081_REG003
** Reference ID          : ICU_DUD_ACT_081_REG004, ICU_DUD_ACT_081_GBL003, ICU_DUD_ACT_081_GBL002
***********************************************************************************************************************/
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_CODE_FAST) Icu_ServiceSignalMeasurement(const Icu_ChannelType LddChannel)                                /* PRQA S 1505 # JV-01 */
{
  /* Defining a pointer to point to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* Define a pointer to point to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  /* Define a pointer to point to the ATU timer channel configuration parameters */
  P2CONST(Icu_ATUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelUserRegConfig;
  /* Defining a pointer to the ATU channel configuration parameters */
  P2CONST(Icu_ATUChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpATUChannelConfig;
  /* Defining a pointer to the channel ram data */
  P2VAR(volatile Icu_ChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpRamData;

  #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
  /* Defining a pointer to point to the TimerA registers */
  P2VAR(Icu_ATUTimerAChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerAChannelRegs;                               /* PRQA S 3432, 3678 # JV-01, JV-01 */
  /* Defining a pointer to point to the TimerA registers */
  P2VAR(Icu_ATUTimerACommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerACommonRegs;                                 /* PRQA S 3432 # JV-01 */
  #endif /* End of #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON) */

  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  /* Defining a pointer to point to the TimerC registers */
  P2VAR(Icu_ATUTimerCSubBlkUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerCSubBlkRegs;                                 /* PRQA S 3432 # JV-01 */
  P2VAR(Icu_ATUTimerCChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA) LpATUTimerCChannelRegs;                               /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #endif /* End of #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON) */

  uint8 LucMeasureProperty;
  uint8 LucRamIndex;
  uint16 LusCurrentEdgeConfig;

  STATIC CONST(uint8, ICU_CONST) LaaEdgeSettingTable[2] = {
    ICU_ATU_FALLING_EDGE_MASK,
    ICU_ATU_RISING_EDGE_MASK
    };

  uint8 LucHigh_Low_Time;

  uint8 LucEdge_Setting;

  /* variable of setting next detect edge */
  uint8 LucSetDetectEdge;

  /* Read channel configuration pointer */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  /* Read timer channel configuration pointer */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannel];
  
  /* Read the channel ram data */
  LpRamData = &Icu_GpChannelRamData[LddChannel];
  
  /* Read ATU timer channel configuration pointer */
  LpATUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannel].pHWChannelUserRegConfig;                           /* PRQA S 0317 # JV-01 */

  /* Read the channel ram index */
  LucRamIndex = LpChannelUserRegConfig->ucRamDataIndex;
  LucMeasureProperty = LpChannelUserRegConfig->ucChannelProperties;
  LpATUChannelConfig = Icu_GpChannelConfig[LddChannel].pHWIPChannelConfig;                                              /* PRQA S 0317 # JV-01 */

  /* Get the spinlock */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

  #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON)
  if (ICU_HW_ATU_TIMERA == LpChannelConfig->ucIcuChannelType)
  {
    /* Initialize pointer to the base address of the current channel */
    LpATUTimerAChannelRegs =
             (P2VAR(Icu_ATUTimerAChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pTimerSubBlkUserRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

    LpATUTimerACommonRegs = (P2VAR(Icu_ATUTimerACommonUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpChannelConfig->pCntlRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */
    /* Check channel property as on time and off time */
    if (((uint8)(LucMeasureProperty & ICU_HIGH_LOW_TIME_MASK)) < ICU_PERIOD_CHANNEL_ENABLED_MASK)
    {
      /* Capture the value when period measurement status is ongoing. */

      if ((uint8)ICU_PERIOD_ONGOING == Icu_GpSignalMeasurementData[LucRamIndex].ucPeriodMeasurementStatus)              /* PRQA S 0404, 3416 # JV-01, JV-01 */
      {
        /* Save input capture register value when end edge */
        LpRamData->ulEndEdgeCaptureValue = (LpATUTimerAChannelRegs->ulAtuTimerAICRAm);

        /* Calculate Active time */
        Icu_GpSignalMeasurementData[LucRamIndex].ulSignalActiveTime = LpRamData->ulEndEdgeCaptureValue -                /* PRQA S 0404, 3384 # JV-01, JV-01 */
                                                                                    LpRamData->ulStartEdgeCaptureValue;

        /* Set channel input status as active */
        LpRamData->blResultComplete = ICU_TRUE;

        /* Set channel input status as active */
        LpRamData->ucChannelStatus = (uint8)ICU_ACTIVE;

        /* Toggle and configure edge detection for ON_TIME, OFF_TIME
         * measurement.
         */
        if (ICU_DUTY_PERIOD_ENABLED_MASK != ((uint8)(LucMeasureProperty & ICU_DUTY_PERIOD_ENABLED_MASK)))
        {
          LucHigh_Low_Time = (uint8)(LucMeasureProperty & ICU_HIGH_LOW_TIME_MASK);
          LucEdge_Setting = LaaEdgeSettingTable[LucHigh_Low_Time];

          /* Mask the edge configured in the register for particular channel */
          LpATUTimerACommonRegs->usAtuTimerATIOR1A &= LpATUChannelUserRegConfig->usChannelModeUserRegSettings;

          /* Set the Edge to be detected for next time */
          LpATUTimerACommonRegs->usAtuTimerATIOR1A |=
                         (uint16)((uint16)LucEdge_Setting << (LpChannelConfig->usChannelMaskValue * ICU_TWO));

          /* Change status to idle */
          Icu_GpSignalMeasurementData[LucRamIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_IDLE;
        }
        else /* In case of Duty cycle additional channel (both edge) */
        {
          /* Save input capture register value as re-start edge */
          LpRamData->ulStartEdgeCaptureValue = (LpATUTimerAChannelRegs->ulAtuTimerAICRAm);
        }
      }
      else /* if (LpSignalMeasureData->ucPeriodMeasurementStatus == ICU_PERIOD_IDLE )*/
      {
        /* Save input capture register value when start edge */
        LpRamData->ulStartEdgeCaptureValue = (LpATUTimerAChannelRegs->ulAtuTimerAICRAm);

        /* Check whether channel configured for duty cycle, then do actions in period time ,else start the timer
         for signal measurement(on time, off time) and toggle the edge to be detected for next time. */
        if (((uint8)(LucMeasureProperty & ICU_DUTY_PERIOD_ENABLED_MASK)) != ICU_DUTY_PERIOD_ENABLED_MASK)
        {
          /*  Mask and get the current loaded edge configuration from register*/
          LusCurrentEdgeConfig = (LpATUTimerACommonRegs->usAtuTimerATIOR1A &
                                                   (uint16)(~LpATUChannelUserRegConfig->usChannelModeUserRegSettings));
          /* get edge configuration for particular channel  */
          LusCurrentEdgeConfig = (LusCurrentEdgeConfig >> (LpChannelConfig->usChannelMaskValue * (uint16)ICU_TWO));
          /* Clear the current edge setting before setting */
          LpATUTimerACommonRegs->usAtuTimerATIOR1A &= LpATUChannelUserRegConfig->usChannelModeUserRegSettings;

          /* Checking measurement property */
          if ((uint8)ICU_HIGH_TIME == (uint8)(LucMeasureProperty & ICU_HIGH_LOW_TIME_MASK))
          {
            if (ICU_ATU_RISING_EDGE_MASK == (uint8)LusCurrentEdgeConfig)
            {
              /* Setting next detect edge to Falling for capture value */
              LucSetDetectEdge = ICU_ATU_FALLING_EDGE_MASK;
              /* Set period measurement status as ongoing. */
              Icu_GpSignalMeasurementData[LucRamIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_ONGOING;
            }
            else /* ICU_ATU_FALLING_EDGE_MASK == LusCurrentEdgeConfig case */
            {
              /*  Setting next detect edge to Rising for start count */
              LucSetDetectEdge = ICU_ATU_RISING_EDGE_MASK;
            }
          }
          else
          {
            if (ICU_ATU_FALLING_EDGE_MASK == (uint8)LusCurrentEdgeConfig)
            {
              /* Setting next detect edge to Rising for capture value */
              LucSetDetectEdge = ICU_ATU_RISING_EDGE_MASK;
              /* CSet period measurement status as ongoing. */
              Icu_GpSignalMeasurementData[LucRamIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_ONGOING;
            }
            else /* ICU_ATU_RISING_EDGE_MASK == LusCurrentEdgeConfig case */
            {
              /*  Setting next detect edge to Falling for start count */
              LucSetDetectEdge = ICU_ATU_FALLING_EDGE_MASK;
            }
          }
          /* Setting next detect edge */
          LpATUTimerACommonRegs->usAtuTimerATIOR1A |=
                                 (uint16)((uint16)LucSetDetectEdge << (LpChannelConfig->usChannelMaskValue * ICU_TWO));
        } /* else No action required */
      }
    }
    else /* (LucMeasureProperty == (ICU_PERIOD_TIME)) */
    {
      /* Set period measurement status as ongoing */

      if ((uint8)ICU_PERIOD_ONGOING == Icu_GpSignalMeasurementData[LucRamIndex].ucPeriodMeasurementStatus)              /* PRQA S 0404, 3416 # JV-01, JV-01 */
      {
        Icu_GpSignalMeasurementData[LucRamIndex].ulPrevSignalActiveTime =                                               /* PRQA S 0404 # JV-01 */
                                                            Icu_GpSignalMeasurementData[LucRamIndex].ulSignalActiveTime;

        /* Save input capture register value when end edge */
        LpRamData->ulEndEdgeCaptureValue = (LpATUTimerAChannelRegs->ulAtuTimerAICRAm);

        /* Calculate Period time */
        Icu_GpSignalMeasurementData[LucRamIndex].ulSignalPeriodTime = LpRamData->ulEndEdgeCaptureValue -                /* PRQA S 0404, 3384 # JV-01, JV-01 */
                                                                                    LpRamData->ulStartEdgeCaptureValue;
        /* Save input capture register value as re-start edge */
        LpRamData->ulStartEdgeCaptureValue = (LpATUTimerAChannelRegs->ulAtuTimerAICRAm);

        /* Change status to active since signal measurement values available */
        LpRamData->blResultComplete = ICU_TRUE;

        /* Set channel input status as active */
        LpRamData->ucChannelStatus = (uint8)ICU_ACTIVE;
      }
      else
      {
        /* Save input capture register value when first edge */
        LpRamData->ulStartEdgeCaptureValue = (LpATUTimerAChannelRegs->ulAtuTimerAICRAm);

        /* Set period measurement status as ongoing */
        Icu_GpSignalMeasurementData[LucRamIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_ONGOING;
      }
    }
  } /* else No action required */
  /* End of (ICU_HW_ATU_TIMERA == LpChannelConfig->ucIcuChannelType) */
  #endif /* End of #if (ICU_ATU_TIMERA_UNIT_USED == STD_ON) */
  #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON)
  if (ICU_HW_ATU_TIMERC == LpChannelConfig->ucIcuChannelType)
  {
    LpATUTimerCSubBlkRegs =
              (P2VAR(Icu_ATUTimerCSubBlkUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pTimerSubBlkUserRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

    LpATUTimerCChannelRegs =
            (P2VAR(Icu_ATUTimerCChannelUserRegs, AUTOMATIC, ICU_CONFIG_DATA))LpATUChannelConfig->pTimerChannelUserRegs; /* PRQA S 0316, 3432 # JV-01, JV-01 */

    if (((uint8)(LucMeasureProperty & ICU_HIGH_LOW_TIME_MASK)) < ICU_PERIOD_CHANNEL_ENABLED_MASK)
    {
      if ((uint8)ICU_PERIOD_ONGOING == Icu_GpSignalMeasurementData[LucRamIndex].ucPeriodMeasurementStatus)              /* PRQA S 0404, 3416 # JV-01, JV-01 */
      {
        /* Save input capture register value when end edge */
        LpRamData->ulEndEdgeCaptureValue = (LpATUTimerCChannelRegs->ulAtuTimerCGRCmn);

        /* Calculate Active time */
        Icu_GpSignalMeasurementData[LucRamIndex].ulSignalActiveTime = LpRamData->ulEndEdgeCaptureValue -                /* PRQA S 0404, 3384 # JV-01, JV-01 */
                                                                                    LpRamData->ulStartEdgeCaptureValue;
        /* Set channel input status as active */
        LpRamData->blResultComplete = ICU_TRUE;

        /* Set channel input status as active */
        LpRamData->ucChannelStatus = (uint8)ICU_ACTIVE;

        /* Check whether channel configured for duty cycle,then do actions in period time ,else start the timer
         for signal measurement(on time, off time) and toggle the edge to be detected for next time. */
        if (ICU_DUTY_PERIOD_ENABLED_MASK != ((uint8)(LucMeasureProperty & ICU_DUTY_PERIOD_ENABLED_MASK)))
        {
            LucHigh_Low_Time = (uint8)(LucMeasureProperty & ICU_HIGH_LOW_TIME_MASK);
            LucEdge_Setting = LaaEdgeSettingTable[LucHigh_Low_Time];

            /* Mask and toggle the edge for next interrupt */
            LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm &= LpATUChannelUserRegConfig->usChannelModeUserRegSettings;


            LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm |= (((uint16)ICU_SET_INPUT_CAPTURE_MODE | 
                                         (uint16)LucEdge_Setting) << (LpChannelConfig->usChannelMaskValue * ICU_FOUR));

            /* Change status to idle */
            Icu_GpSignalMeasurementData[LucRamIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_IDLE;
        }
        else /* In case of Duty cycle additional channel (both edge) */
        {
          /* Save input capture register value when start edge */
          LpRamData->ulStartEdgeCaptureValue = (LpATUTimerCChannelRegs->ulAtuTimerCGRCmn);
        }
      }
      else /* if (LpSignalMeasureData->ucPeriodMeasurementStatus == ICU_PERIOD_IDLE )*/
      {
        /* Save input capture register value when start edge */
        LpRamData->ulStartEdgeCaptureValue = (LpATUTimerCChannelRegs->ulAtuTimerCGRCmn);

        if (((uint8)(LucMeasureProperty & ICU_DUTY_PERIOD_ENABLED_MASK)) != ICU_DUTY_PERIOD_ENABLED_MASK)
        {
          /*  Mask and get the current loaded edge configuration from register*/
          LusCurrentEdgeConfig = (LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm &
                                                   (uint16)(~LpATUChannelUserRegConfig->usChannelModeUserRegSettings));
          /* get edge configuration for particular channel  */
          LusCurrentEdgeConfig =
              ((uint16)(LusCurrentEdgeConfig >> (LpChannelConfig->usChannelMaskValue * (uint16)ICU_FOUR)) &
                                                                                        (uint16)ICU_ATU_BOTH_EDGE_MASK);
          /* Clear the current edge setting before setting */
          LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm &= LpATUChannelUserRegConfig->usChannelModeUserRegSettings;

          /* Checking measurement property */
          if ((uint8)ICU_HIGH_TIME == (uint8)(LucMeasureProperty & ICU_HIGH_LOW_TIME_MASK))
          {
            if (ICU_ATU_RISING_EDGE_MASK == (uint8)LusCurrentEdgeConfig)
            {
              /* Setting next detect edge to Falling for capture value */
              LucSetDetectEdge = ICU_ATU_FALLING_EDGE_MASK;
              /* Set period measurement status as ongoing. */
              Icu_GpSignalMeasurementData[LucRamIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_ONGOING;
            }
            else /* ICU_ATU_FALLING_EDGE_MASK == LusCurrentEdgeConfig case */
            {
              /*  Setting next detect edge to Rising for start count */
              LucSetDetectEdge = ICU_ATU_RISING_EDGE_MASK;
            }
          }
          else
          {
            if (ICU_ATU_FALLING_EDGE_MASK == (uint8)LusCurrentEdgeConfig)
            {
              /* Setting next detect edge to Rising for capture value */
              LucSetDetectEdge = ICU_ATU_RISING_EDGE_MASK;
              /* Set period measurement status as ongoing. */
              Icu_GpSignalMeasurementData[LucRamIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_ONGOING;
            }
            else /* ICU_ATU_RISING_EDGE_MASK == LusCurrentEdgeConfig case */
            {
              /*  Setting next detect edge to Falling for start count */
              LucSetDetectEdge = ICU_ATU_FALLING_EDGE_MASK;
            }
          }
          /* Setting next detect edge */
          LpATUTimerCSubBlkRegs->usAtuTimerCTIORCm |=
                                          (uint16)(((uint32)ICU_SET_INPUT_CAPTURE_MODE | (uint32)LucSetDetectEdge)
                                                                  << (LpChannelConfig->usChannelMaskValue * ICU_FOUR));
        } /* else No action required */
      }
    }
    else /* (LucMeasureProperty == (ICU_PERIOD_TIME)) */
    {

      if ((uint8)ICU_PERIOD_ONGOING == Icu_GpSignalMeasurementData[LucRamIndex].ucPeriodMeasurementStatus)              /* PRQA S 0404, 3416 # JV-01, JV-01 */
      {
        /* Store the active time */
        Icu_GpSignalMeasurementData[LucRamIndex].ulPrevSignalActiveTime =                                               /* PRQA S 0404 # JV-01 */
                                                          Icu_GpSignalMeasurementData[LucRamIndex].ulSignalActiveTime;

        /* Save input capture register value when end edge */
        LpRamData->ulEndEdgeCaptureValue = LpATUTimerCChannelRegs->ulAtuTimerCGRCmn;

        /* Calculate Period time */
        Icu_GpSignalMeasurementData[LucRamIndex].ulSignalPeriodTime = LpRamData->ulEndEdgeCaptureValue -                /* PRQA S 0404, 3384 # JV-01, JV-01 */
                                                                                    LpRamData->ulStartEdgeCaptureValue;

        /* Save input capture register value as re-start edge */
        LpRamData->ulStartEdgeCaptureValue = LpATUTimerCChannelRegs->ulAtuTimerCGRCmn;

        LpRamData->blResultComplete = ICU_TRUE;

        /* Set channel input status as active */
        LpRamData->ucChannelStatus = (uint8)ICU_ACTIVE;
      }
      else
      {
        /* Save input capture register value when first edge */
        LpRamData->ulStartEdgeCaptureValue = (LpATUTimerCChannelRegs->ulAtuTimerCGRCmn);

        Icu_GpSignalMeasurementData[LucRamIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_ONGOING;
      }
    } /* else No action required */
  } /* End of (ICU_HW_ATU_TIMERC == LpChannelConfig->ucIcuChannelType) */
  #endif /* End of #if (ICU_ATU_TIMERC_UNIT_USED == STD_ON) */
  
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

} /* End of Internal function Icu_ServiceSignalMeasurement */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_ServiceTimestamp
**
** Service ID            : None
**
** Description           : This service routine captures the channel's Timestamp
**                         data based on its active edge configuration.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LddChannel, LulCapturedTimestampVal
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables      : Icu_GpChannelConfig, Icu_GpTimeStampData,
**                         Icu_GpChannelUserRegConfig, Icu_GpChannelRamData.
**
** Functions invoked     : pIcuNotificationPointer
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_082, ICU_DUD_ACT_082_GBL001, ICU_DUD_ACT_082_GBL002
***********************************************************************************************************************/
#if (ICU_TIMESTAMP_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_CODE_FAST) Icu_ServiceTimestamp(const Icu_ChannelType LddChannel, const uint32 LulCapturedTimestampVal)  /* PRQA S 1505 # JV-01 */
{
  #if (ICU_NOTIFICATION_CONFIG == STD_ON)
  /* Defining a pointer to point to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  #endif /* End of #if (ICU_NOTIFICATION_CONFIG == STD_ON) */

  /* Defining a pointer to point to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;

  /* Defining a pointer to point to the time stamp data */
  P2VAR(volatile Icu_TimeStampChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpTimestampdata;

  /* Local variable used to store the ram index of the channel */
  uint8 LucRamIndex;

  #if (ICU_NOTIFICATION_CONFIG == STD_ON)
  /* Update the channel pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  #endif /* End of #if (ICU_NOTIFICATION_CONFIG == STD_ON) */

  /* Load timer channel configuration pointer and channel properties */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannel];

  /* Read channel ram index */
  LucRamIndex = LpChannelUserRegConfig->ucRamDataIndex;

  /* Read the Timestamp channel data pointer */
  LpTimestampdata = &Icu_GpTimeStampData[LucRamIndex];

  /* Check if timestamp capturing reached end of the buffer */
  if ((LpTimestampdata->usTimestampIndex) < (LpTimestampdata->usBufferSize))                                            /* PRQA S 0404 # JV-01 */
  {
    /* Update the buffer pointer with current timestamp */
    *(LpTimestampdata->pBufferPointer) = LulCapturedTimestampVal;

    (LpTimestampdata->usTimestampIndex)++;                                                                              /* PRQA S 3383, 3387 # JV-01, JV-01 */

    (LpTimestampdata->pBufferPointer)++;                                                                                /* PRQA S 3387 # JV-01 */

    /* Check whether the timestamp index has reached the end of buffer */
    if ((LpTimestampdata->usTimestampIndex) >= (LpTimestampdata->usBufferSize))                                         /* PRQA S 0404 # JV-01 */
    {
      /*  Check if buffer is configured as circular */
      if (((uint8)(LpChannelUserRegConfig->ucChannelProperties & ICU_TS_CIRCULAR_BUFFER_MASK)) ==
                                                                                            ICU_TS_CIRCULAR_BUFFER_MASK)
      {
        /* Reset buffer pointer and index */
        LpTimestampdata->usTimestampIndex = (uint16)ICU_BUFFER_IDX_INIT_VAL;
        LpTimestampdata->pBufferPointer = LpTimestampdata->pBufferPointer - LpTimestampdata->usBufferSize;              /* PRQA S 0404, 0488 # JV-01, JV-01 */
      }
      else
      {
        /* Stop the hardware channel */
        Icu_HW_Atu_StopCountMeasurement(LddChannel);
      }
    } /* else No action required */
    /* End of ((LpTimestampdata->usTimestampIndex) >= (LpTimestampdata->usBufferSize)) */
    /* Notify if the configured number of timestamps are captured and notification is enabled */
    #if (ICU_NOTIFICATION_CONFIG == STD_ON)
    if (ICU_TRUE == Icu_GpChannelRamData[LddChannel].ucNotificationEnable)                                              /* PRQA S 0404, 1881, 3416 # JV-01, JV-01, JV-01 */
    {
      (LpTimestampdata->usTimestampsCounter)++;                                                                         /* PRQA S 3383, 3387 # JV-01, JV-01 */

      if ((LpTimestampdata->usTimestampsCounter) ==  (LpTimestampdata->usNotifyInterval))                               /* PRQA S 0404 # JV-01 */
      {
        /* Reset the number of timestamp captured counter */
        LpTimestampdata->usTimestampsCounter = (uint16)ICU_ZERO;

        /* Check if the function pointer address is present for particular channel */
        if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
        {
          /* callback notification */
          LpChannelConfig->pIcuNotificationPointer();
        } /* else No action required */
      } /* else No action required */
    } /* else No action required */
    #endif /* if (ICU_NOTIFICATION_CONFIG == STD_ON) */
  } /* else No action required */
} /* End of Internal function Icu_ServiceTimestamp */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of #if (ICU_TIMESTAMP_API == STD_ON) */
#endif /* End of #if (STD_ON == ICU_ATU_TIMER_UNIT_USED) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
