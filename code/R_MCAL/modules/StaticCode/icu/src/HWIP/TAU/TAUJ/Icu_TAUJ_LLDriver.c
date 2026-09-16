/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_TAUJ_LLDriver.c                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
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
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01 Release
 * 2.3.1:  31/03/2025  : As part of support QAC 11.6.0, following changes are made:
                         1. Add 3006, 3415, 3416 and remove 1532, 2814, 2824, 2844, 3678, 4304
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : As part of support QAC 9.5.0, following changes are made:
 *                       1. Remove redundant QAC messageer
 *                       As part of support GTM HWIP into common code, following changes are made:
 *                       1. Update function Icu_HW_Tauj_UnitInit, Icu_HW_Tauj_ChannelInit, Icu_HW_Tauj_TimerIsr
 *                       2. Remove function Icu_HW_Tauj_SetMode, add new function Icu_HW_Tauj_ResetEdgeCount
 *                       3. Remove update value of Icu_GpSignalMeasurementData in Icu_HW_Tauj_UnitInit
 *                       Update SW-VERSION for Ver22.01.02 Beta2 Release 
 * 2.0.1:  19/10/2023  : Remove QAC messages 2814, 2824, 2844, 1532, 0857. Add messages 3006, 4304, 3415, 3416, 1881.
 *         14/10/2023  : Remove pre-compile parameter ICU_E_INT_INCONSISTENT_CONFIGURED for ICU_DEM_REPORT_ERROR
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 *                       Icu_HW_Tauj_UnitInit only stop the channel configured by ICU
 *                       Access ucChannelRunning which precompiles STD_ON == ICU_SET_MODE_API
 *                       Update the Global critical section 
 *                       Icu_HW_Tauj_TimerIsr update precompile condition and brand condition when the report wake up
 *                       Icu_HW_Tauj_ServiceTimestamp: Stop hardware channel upon buffer linear reach the end.
 *         11/06/2023  : Update function Icu_HW_Tauj_SetActivation for setting the edge detection due to Autosar
 *                       R21-11 change typedef enum ETag_Icu_ActivationType
 * 1.4.5:  17/11/2022  : Update "Input Parameters", "Global Variables", 
 *                       "Functions invoked" for all functions.
 *                       Add ICU_DUD_ACT_048_REG004 in description of Icu_HW_Tauj_ChannelInit.
 *         15/11/2022  : Update Icu_HW_Tauj_UnitDeInit to access all TAUJnTT registers
 * 1.4.4:  16/06/2022  : Update QAC message and QAC header
 * 1.4.3:  23/05/2022  : Fix QAC header and message.
 *         09/05/2022  : Remove "else" statement when no action required; add QAC message 2004.
 *         17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 *         13/04/2022  : Update function Icu_HW_Tauj_GetTAUInCountValue, get Tau counter value from new pTAUJCNTAddress
 *                       and add Null check before read pTAUJCNTAddress counter value
 * 1.4.2:  02/03/2022  : Fix QAC header and message
 * 1.4.1:  20/11/2021  : Add QAC message 9.5.0
 *         07/10/2021  : Remove code segment of usTAUJnTPS and ucTAUJnBRS in Icu_HW_Tauj_UnitDeInit
 *         18/10/2021  : Add QAC message 9.5.0
 *         16/09/2021  : Correct preprocessor directives
 *                       Correct if conditions
 *                       Correct names, datatypes of used variables
 *                       Removed redundant switch/case branches
 * 1.3.2:  30/08/2021  : Change from #include "Icu_MemMap.h" to #include "Icu_Mapping.h".
 *                       Update pre-compile parameter ICU_E_INT_INCONSISTENT_CONFIGURED for ICU_DEM_REPORT_ERROR
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.3.0:  20/01/2021  : Changed CONSTP2CONST to P2CONST for argument ConfigPtr
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : MISRA C:2012 Rule-11.3, CERTCCM EXP39, EXP11, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588,   */
/*                       CWE-465, CWE-569, CWE-737                                                                    */
/* JV-01 Justification : For accessing 8-bit and 16-bit PNOT and JPNOT register respectively, the 32-bit pointer is   */
/*                       typecasted.                                                                                  */
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
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3, CWE Rule CWE-398, CWE-569                                              */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:3305)    : Pointer cast to stricter alignment.                                                          */
/* Rule                : MISRA C:2012 Rule-11.3, CERTCCM EXP36, EXP39, CWE Rule CWE-188, CWE-737                      */
/* JV-01 Justification : Pointer alignment is changed by casting, but it's necessary for embedded programming         */
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
#include "Icu_TAU_LLDriver.h"
#include "Icu_TAUJ_LLDriver.h"
/* Included for RAM variable declarations */
#include "Icu_Ram.h"
#include "Icu_TAUJ_Ram.h"

#if (ICU_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
/* Include for interrupt consistency check */
#include "Dem.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_TAUJ_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_TAUJ_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_TAUJ_LLDRIVER_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ICU_TAUJ_LLDRIVER_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_TAUJ_LLDRIVER_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ICU_TAUJ_LLDRIVER_AR_RELEASE_MAJOR_VERSION != ICU_TAUJ_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "Icu_TAUJ_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (ICU_TAUJ_LLDRIVER_AR_RELEASE_MINOR_VERSION != ICU_TAUJ_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "Icu_TAUJ_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (ICU_TAUJ_LLDRIVER_AR_RELEASE_REVISION_VERSION != ICU_TAUJ_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "Icu_TAUJ_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (ICU_TAUJ_LLDRIVER_SW_MAJOR_VERSION != ICU_TAUJ_LLDRIVER_C_SW_MAJOR_VERSION)
#error "Icu_TAUJ_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (ICU_TAUJ_LLDRIVER_SW_MINOR_VERSION != ICU_TAUJ_LLDRIVER_C_SW_MINOR_VERSION)
#error "Icu_TAUJ_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#if (ICU_TAUJ_UNIT_USED == STD_ON)
/***********************************************************************************************************************
** Function Name        : Icu_HW_Tauj_UnitInit
**
** Service ID           : None
**
** Description          : This service initializes the hardware for all the
**                        configured channels based on the measurement mode.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Non Reentrant
**
** Input Parameters     : ConfigPtr
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Icu_GpTAUUnitConfig, Icu_GpSignalMeasurementData.
**
** Functions invoked    : None
**
** Registers Used       : TAUJnTT, TAUJnTPS, TAUJnBRS.
**
** Reference ID         : ICU_DUD_ACT_047, ICU_DUD_ACT_047_GBL002, ICU_DUD_ACT_047_GBL003,
** Reference ID         : ICU_DUD_ACT_047_REG001, ICU_DUD_ACT_047_REG002,
** Reference ID         : ICU_DUD_ACT_047_REG003, ICU_DUD_ACT_047_REG004
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Tauj_UnitInit(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST) ConfigPtr)
{
  #if (ICU_PRESCALER_CONFIGURED == STD_ON)
  /* Defining a pointer to the TAU configuration parameters */
  P2CONST(Icu_TAUUnitConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUUnitConfig;
  /* Declare a Local variable to Unit Type */
  uint8 LucUnitType;
  /* Local variable to hold the channel number */
  uint8 LucCount;
  /* Pointer pointing to the TAUJ Unit control registers */
  P2VAR(volatile Icu_TAUJUnitOsRegs, AUTOMATIC, REGSPACE) LpTAUJUnitOsReg;
  P2VAR(volatile Icu_TAUJUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUJUnitUserReg;
  #endif

  /* Store the global pointer to the first Unit Configuration */
  Icu_GpTAUUnitConfig = ConfigPtr->pTAUUnitConfig;                                                                      /* PRQA S 0317 # JV-01 */

  #if (ICU_PRESCALER_CONFIGURED == STD_ON)
  /* Update the TAU configuration pointer to point to the current TAU */
  for (LucCount = (uint8)ICU_ZERO; LucCount < (uint8)ICU_TOTAL_TAU_UNITS_CONFIGURED; LucCount++)
  {
    /* Update the Timer channel configuration pointer to point to the current channel */
    LpTAUUnitConfig = &Icu_GpTAUUnitConfig[LucCount];
    /* Read the Unit Type for the given unit */
    LucUnitType = LpTAUUnitConfig->ucIcuUnitType;
    /* Invoke low-level driver for initializing the hardware */
    if(ICU_HW_TAUJ == LucUnitType)
    {
      /* Initialize pointer to the base address of the current timer unit */
      LpTAUJUnitOsReg = (P2VAR(volatile Icu_TAUJUnitOsRegs, AUTOMATIC, REGSPACE)) LpTAUUnitConfig->pTAUnitOsCntlRegs;   /* PRQA S 0310, 3305 # JV-01, JV-01 */
                                                                          
      LpTAUJUnitUserReg = (P2VAR(volatile Icu_TAUJUnitUserRegs, AUTOMATIC, REGSPACE))                                   /* PRQA S 0310, 3305 # JV-01, JV-01 */
                                                                          LpTAUUnitConfig->pTAUnitUserCntlRegs;
      /* Set the values of baud rate to TPS/BRS registers respectively */
      if ((uint8)ICU_TRUE == LpTAUUnitConfig->ucConfigurePrescaler)                                                     /* PRQA S 4304 # JV-01 */
      {
        /* Set the bit corresponding to the channel number in the TAUJnTT register */
        LpTAUJUnitUserReg->ucTAUJnTT = ICU_TAUJ_TIMER_RESET_VAL;
        /* Write the configured prescaler value to TAUJnTPS register */
        LpTAUJUnitOsReg->usTAUJnTPS = LpTAUUnitConfig->usPrescaler;
        /* Load the configured baud rate value */
        LpTAUJUnitOsReg->ucTAUJnBRS = LpTAUUnitConfig->ucBaudRate;
      }
      else
      {
        /* Set the bit corresponding to the channel number in TAUJnTT register */
        LpTAUJUnitUserReg->ucTAUJnTT = (uint8)LpTAUUnitConfig->usTAUChannelMaskValue;
      }
    } /* else No action required */
  } /* End of looping all units */
  #endif
} /* End of Internal function Icu_HW_Tauj_UnitInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Tauj_ChannelInit
**
** Service ID           : None
**
** Description          : This service initializes the hardware for all the
**                        configured channels based on the measurement mode.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Non Reentrant
**
** Input Parameters     : LddChannelIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Icu_GpChannelConfig, Icu_GpChannelUserRegConfig, Icu_GpChannelRamData.
**
** Functions invoked    : Icu_HW_Tauj_TimestampInit, Icu_HW_Tauj_SignalMeasurementInit, RH850_SV_SET_ICR_SYNCP
**
** Registers Used       : TAUJnCMORm, TAUJnCMURm, TAUJnCSCm.
**
** Reference ID         : ICU_DUD_ACT_048, ICU_DUD_ACT_048_REG001, ICU_DUD_ACT_048_REG002, ICU_DUD_ACT_048_REG003
** Reference ID         : ICU_DUD_ACT_048_REG004
** Reference ID         : ICU_DUD_ACT_048_GBL003, ICU_DUD_ACT_048_GBL004, ICU_DUD_ACT_048_GBL001
** Reference ID         : ICU_DUD_ACT_048_GBL005, ICU_DUD_ACT_048_GBL006, ICU_DUD_ACT_048_GBL002
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Tauj_ChannelInit(const Icu_ChannelType LddChannelIndex)                             /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* Defining a pointer to the Channel Ram Data */
  P2VAR(volatile Icu_ChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpRamData;

  /* Defining a pointer to the timer TAU channel configuration parameters */
  P2CONST(Icu_TAUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUChannelUserRegConfig;

  /* Pointer pointing to the TAUJ channel control registers */
  P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUJChannelReg;

  #if ((ICU_TIMESTAMP_API == STD_ON) || (ICU_SIGNAL_MEASUREMENT_API == STD_ON) || (ICU_EDGE_COUNT_API == STD_ON))
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  /* Local variable to store the measurement mode of a channel */
  Icu_MeasurementModeType LenMeasurementMode;
  #endif

  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannelIndex];
  /* Update the global pointer with the first channel's ram address */
  LpRamData = &Icu_GpChannelRamData[LddChannelIndex];
  /* Initialize all the configured Icu Channels */
  /* Initialize each channel status as idle */
  LpRamData->ucChannelStatus = (uint8)ICU_IDLE;
  #if (STD_ON == ICU_SET_MODE_API)
  /* Initialize running status for each channel */
  LpRamData->ucChannelRunning = (uint8)ICU_FALSE;                                                                       /* PRQA S 4304 # JV-01 */
  #endif

  #if ((ICU_DISABLE_WAKEUP_API == STD_ON) || (ICU_ENABLE_WAKEUP_API == STD_ON) || \
                                                                              (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON))
  /* Disable each channel wakeup from sleep mode */
  LpRamData->ucWakeupEnable = (uint8)ICU_FALSE;                                                                         /* PRQA S 4304 # JV-01 */
  /* Initialize wakeup occurrence for each channel */
  LpRamData->blWakeupOccurrence = ICU_FALSE;
  #endif
  /* Disable notification for each channel */
  LpRamData->ucNotificationEnable = (uint8)ICU_FALSE;                                                                   /* PRQA S 4304 # JV-01 */
  /* Initialize the status of result channel as False */
  LpRamData->blResultComplete = ICU_FALSE;

  LpTAUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannelIndex].pHWChannelUserRegConfig;                      /* PRQA S 0317 # JV-01 */

  #if ((ICU_TIMESTAMP_API == STD_ON) || (ICU_SIGNAL_MEASUREMENT_API == STD_ON) || (ICU_EDGE_COUNT_API == STD_ON))
  /* Update the Timer channel configuration pointer to point to the current channel */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannelIndex];
  /* Read the channel's measurement mode */
  LenMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  #endif
  /* Initialize pointer to the base address of the current channel */
  LpTAUJChannelReg = (P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;         /* PRQA S 0316 # JV-01 */

  /* Read the value of Channel Mode OS Register configured */
  *(LpTAUChannelUserRegConfig->pCMORReg) = LpTAUChannelUserRegConfig->usChannelModeOSRegSettings;

  /* Read the value of Channel Mode User Register configured */
  LpTAUJChannelReg->ucTAUJnCMURm = LpTAUChannelUserRegConfig->ucChannelModeUserRegSettings;

  /* Reset Channel Status Clear Trigger Register */
  LpTAUJChannelReg->ucTAUJnCSCm = ICU_TAUJ_CSC_RESET_VAL;

  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disable the Interrupt processing of the current channel */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);                              /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */

  #if ((ICU_TIMESTAMP_API == STD_ON) || (ICU_SIGNAL_MEASUREMENT_API == STD_ON) || (ICU_EDGE_COUNT_API == STD_ON))
  if ((Icu_MeasurementModeType)ICU_MODE_TIMESTAMP == LenMeasurementMode)
  {
    #if (ICU_TIMESTAMP_API == STD_ON)
    /* Configure the channel in Timestamp Mode */
    Icu_HW_Tauj_TimestampInit(LpChannelUserRegConfig);
    #endif
  }
  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  else if (ICU_MODE_SIGNAL_MEASUREMENT == LenMeasurementMode)
  {
    /* Configure the channel in Edge Counter Mode */
    Icu_HW_Tauj_SignalMeasurementInit(LpChannelUserRegConfig);
  }
  #endif
  #if (ICU_EDGE_COUNT_API == STD_ON)
  else if (ICU_MODE_EDGE_COUNTER == LenMeasurementMode)                                                                 /* PRQA S 2004 # JV-01 */
  {
    /* Configure the channel in Edge Counter Mode */
    Icu_HW_Tauj_EdgeCountingInit(LpChannelUserRegConfig);
  } /* else No action required */
  #endif
  #endif
} /* End of Internal function Icu_HW_Tauj_ChannelInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Tauj_UnitDeInit
**
** Service ID           : None
**
** Description          : This service De-Initializes the hardware for all the
**                        configured channels based on the measurement mode.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Non Reentrant
**
** Input Parameters     : None
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Icu_GpTAUUnitConfig
**
** Functions invoked    : None
**
** Registers Used       : TAUJnTT.
**
** Reference ID         : ICU_DUD_ACT_049, ICU_DUD_ACT_049_REG001
***********************************************************************************************************************/
#if (ICU_DE_INIT_API == STD_ON)

#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Tauj_UnitDeInit(void)
{
  /* Defining a pointer to the TAU configuration parameters */
  P2CONST(Icu_TAUUnitConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUUnitConfig;

  /* Pointer pointing to the TAUJ channel control registers */
  P2VAR(volatile Icu_TAUJUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUJUnitUserReg;

  /* Declare a Local variable to Timer Type */
  VAR(uint8, AUTOMATIC) LucTimerType;

  /* Declare a Local variable to counting loop */
  VAR(uint8, AUTOMATIC) LucCount;

  /* Update the TAU configuration pointer to point to the current TAU */
  LpTAUUnitConfig = Icu_GpTAUUnitConfig;

  for (LucCount = (uint8)ICU_ZERO; LucCount < (uint8)ICU_TOTAL_TAU_UNITS_CONFIGURED; LucCount++)
  {
    /* Read the Timer Type for given channel */
    LucTimerType = LpTAUUnitConfig[LucCount].ucIcuUnitType;
    if (ICU_HW_TAUJ == LucTimerType)
    {
      /* Initialize pointer to the base address of the current channel */
      LpTAUJUnitUserReg =
            (P2VAR(volatile Icu_TAUJUnitUserRegs, AUTOMATIC, REGSPACE))(LpTAUUnitConfig[LucCount].pTAUnitUserCntlRegs); /* PRQA S 0310, 3305 # JV-01, JV-01 */

      /* Set the bit corresponding to the channel number in TAUJnTT register */
      LpTAUJUnitUserReg->ucTAUJnTT = (uint8)(LpTAUUnitConfig[LucCount].usTAUChannelMaskValue);
    } /* else No action required */
  }
} /* End of Internal function Icu_HW_Tauj_UnitDeInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_DE_INIT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Tauj_ChannelDeInit
**
** Service ID           : None
**
** Description          : This service De-Initializes the hardware for all the
**                        configured channels based on the measurement mode.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Non Reentrant
**
** Input Parameters     : LddChannelIndex
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Icu_GpChannelConfig, Icu_GpChannelUserRegConfig, Icu_GpChannelRamData.
**
** Functions invoked    : None
**
** Registers Used       : TAUJnCMORm, TAUJnCDRm, TAUJnCSCm, TAUJnCMURm.
**
** Reference ID         : ICU_DUD_ACT_050, ICU_DUD_ACT_050_REG001, ICU_DUD_ACT_050_REG002, ICU_DUD_ACT_050_REG003
** Reference ID         : ICU_DUD_ACT_050_REG004, ICU_DUD_ACT_050_GBL001, ICU_DUD_ACT_050_GBL002, ICU_DUD_ACT_050_GBL003
** Reference ID         : ICU_DUD_ACT_050_GBL004, ICU_DUD_ACT_050_GBL005, ICU_DUD_ACT_050_GBL006, ICU_DUD_ACT_050_REG005
***********************************************************************************************************************/
#if (ICU_DE_INIT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Tauj_ChannelDeInit(const Icu_ChannelType LddChannelIndex)                           /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the timer TAU channel configuration parameters */
  P2CONST(Icu_TAUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUChannelUserRegConfig;
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* Defining a pointer to the Timer registers */
  P2VAR(volatile Icu_ChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpRamData;

  /* Pointer pointing to the TAUJ channel control registers */
  P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUJChannelReg;

  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannelIndex];
  LpRamData = &Icu_GpChannelRamData[LddChannelIndex];
  /* Initialize each channel status as idle */
  LpRamData->ucChannelStatus = (uint8)ICU_IDLE;
  #if ((ICU_DISABLE_WAKEUP_API == STD_ON) || (ICU_ENABLE_WAKEUP_API == STD_ON) || \
                                                                               (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON))
  /* Disable each channel wakeup from sleep mode */
  LpRamData->ucWakeupEnable = (uint8)ICU_FALSE;                                                                         /* PRQA S 4304 # JV-01 */
  /* Initialize wakeup occurrence for each channel */
  LpRamData->blWakeupOccurrence = ICU_FALSE;
  #endif
  /* Disable notification for each channel */
  LpRamData->ucNotificationEnable = (uint8)ICU_FALSE;                                                                   /* PRQA S 4304 # JV-01 */
  /* Initialize the status of result channel as False */
  LpRamData->blResultComplete = ICU_FALSE;
  #if (STD_ON == ICU_SET_MODE_API)
  /* Initialize running status for each channel */
  LpRamData->ucChannelRunning = (uint8)ICU_FALSE;                                                                       /* PRQA S 4304 # JV-01 */
  #endif

  LpTAUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannelIndex].pHWChannelUserRegConfig;                      /* PRQA S 0317 # JV-01 */

  /* Initialize pointer to the base address of the current channel */
  LpTAUJChannelReg = (P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;         /* PRQA S 0316 # JV-01 */

  /* Reset the value of Channel Mode OS Register */
  *(LpTAUChannelUserRegConfig->pCMORReg) = ICU_TAUJ_CMOR_RESET_VAL;

  /* Reset the value of Channel Data Register */
  LpTAUJChannelReg->ulTAUJnCDRm = ICU_TAUJ_CDR_RESET_VAL;

  /* Reset the value of Channel Mode User Register */
  LpTAUJChannelReg->ucTAUJnCMURm = ICU_TAUJ_CMUR_RESET_VAL;

  /* Reset Channel Status Clear Trigger Register */
  LpTAUJChannelReg->ucTAUJnCSCm = ICU_TAUJ_CSC_RESET_VAL;

  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disabling the Interrupt processing */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);                              /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */

} /* End of Internal function Icu_HW_Tauj_ChannelDeInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_DE_INIT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Tauj_TimestampInit
**
** Service ID            : None
**
** Description           : This service is used to initialize the channel configured for Timestamp Measurement mode.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
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
** Reference ID          : ICU_DUD_ACT_051, ICU_DUD_ACT_051_GBL001
***********************************************************************************************************************/
#if (ICU_TIMESTAMP_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE)
    Icu_HW_Tauj_TimestampInit(P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig) /* PRQA S 1505 # JV-01 */
{
  /* Local variable used to store the channel index */
  uint8 LucIndex;
  /* Read the Timestamp Channel ram index */
  LucIndex = LpChannelUserRegConfig->ucRamDataIndex;

  Icu_GpTimeStampData[LucIndex].usTimestampIndex = (uint16)ICU_BUFFER_IDX_INIT_VAL;
} /* End of Internal function Icu_HW_Tauj_TimestampInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_TIMESTAMP_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Tauj_SignalMeasurementInit
**
** Service ID            : None
**
** Description           : This service initializes the channel configured in Signal Measurement Mode.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
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
** Reference ID          : ICU_DUD_ACT_052, ICU_DUD_ACT_052_GBL001,
** Reference ID          : ICU_DUD_ACT_052_GBL002, ICU_DUD_ACT_052_GBL003, ICU_DUD_ACT_052_GBL004
***********************************************************************************************************************/
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE)Icu_HW_Tauj_SignalMeasurementInit                                                           /* PRQA S 1505 # JV-01 */
                             (P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig)
{
  /* Local variable used to store the Timer Instance */
  uint8 LucIndex;
  /* Read the Signal Measurement Channel ram index */
  LucIndex = LpChannelUserRegConfig->ucRamDataIndex;
  /* Initialize the Signal Active time to zero */
  Icu_GpSignalMeasurementData[LucIndex].ulSignalActiveTime = (uint32)ICU_ACTIVE_TIME_RESET_VAL;
  /* Initialize the Signal Period time to zero */
  Icu_GpSignalMeasurementData[LucIndex].ulSignalPeriodTime = (uint32)ICU_PERIOD_TIME_RESET_VAL;
  /* Initialize the Signal Period time to zero */
  Icu_GpSignalMeasurementData[LucIndex].ulPrevSignalActiveTime = (uint32)ICU_ACTIVE_TIME_RESET_VAL;
  /* Initialize the Period measurement status */
  Icu_GpSignalMeasurementData[LucIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_IDLE;
} /* End of Internal function Icu_HW_Tauj_SignalMeasurementInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Tauj_SetActivation
**
** Service ID           : None
**
** Description          : This service configures the hardware to the active edges of the requested channel.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : LddChannel, LenActiveEdge
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : NA
**
** Global Variables     : Icu_GpChannelConfig, Icu_GpChannelRamData.
**
** Functions invoked    : RH850_SV_CLEAR_ICR_SYNCP.
**
** Registers Used       : TAUJnCMURm
**
** Reference ID         : ICU_DUD_ACT_053, ICU_DUD_ACT_053_REG001, ICU_DUD_ACT_053_GBL001, ICU_DUD_ACT_053_REG002
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE)
                    Icu_HW_Tauj_SetActivation(const Icu_ChannelType LddChannel, const Icu_ActivationType LenActiveEdge) /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  /* Defining a pointer to point to the TAUJ registers */
  P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUJChannelReg;

  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  /* Initialize pointer to the base address of the current channel */
  LpTAUJChannelReg = (P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;         /* PRQA S 0316 # JV-01 */

  /* TAUJ doesn't support edge counter mode. so, set the active edge for timestamp mode only */
  if (ICU_FALLING_EDGE == LenActiveEdge)
  {
    /* Set the edge detection bits in the channel mode user register as per mask */
    LpTAUJChannelReg->ucTAUJnCMURm = ICU_TAU_FALLING_EDGE_MASK;
  }

  else if (ICU_RISING_EDGE == LenActiveEdge)
  {
    /* Set the edge detection bits in the channel mode user register as per mask */
    LpTAUJChannelReg->ucTAUJnCMURm = ICU_TAU_RISING_EDGE_MASK;
  }

  else
  {
    /* Set the edge detection bits in the channel mode user register as per mask */
    LpTAUJChannelReg->ucTAUJnCMURm = ICU_TAU_BOTH_EDGES_MASK;
  }

  #if (ICU_CLEAR_PENDING_INTERRUPT == STD_ON)

  /* Check if the Interrupt register is present for particular channel */
  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Clear the pending interrupts */
    RH850_SV_CLEAR_ICR_SYNCP(16, LpChannelConfig->pIntrCntlAddress, ICU_CLEAR_PENDING_INTR_MASK);                       /* PRQA S 1006 # JV-01 */
  } /* else No action required */
  /* End of  NULL_PTR != LpChannelConfig->pIntrCntlAddress */
  #endif /* End of ICU_CLEAR_PENDING_INTERRUPT == STD_ON */

  /* Initialize channel status as idle */
  Icu_GpChannelRamData[LddChannel].ucChannelStatus = (uint8)ICU_IDLE;

} /* End of Internal function Icu_HW_Tauj_SetActivation */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Tauj_StartCountMeasurement
**
** Service ID           : None
**
** Description          : This service routine starts the count measurement.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : LddChannel
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Icu_GpChannelUserRegConfig, Icu_GpChannelConfig, Icu_GpTAUUnitConfig, 
**                        Icu_GpSignalMeasurementData, Icu_GpChannelRamData.
**
** Functions invoked    : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION, Icu_HW_Tau_StartCountMeasurement.
**
** Registers Used       : TAUJnTT, TAUJnTS, TAUJnCSCm.
**
** Reference ID         : ICU_DUD_ACT_054, ICU_DUD_ACT_054_CRT001, ICU_DUD_ACT_054_CRT002, ICU_DUD_ACT_054_GBL001
** Reference ID         : ICU_DUD_ACT_054_REG001, ICU_DUD_ACT_054_REG002, ICU_DUD_ACT_054_GBL002
** Reference ID         : ICU_DUD_ACT_054_REG003
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Tauj_StartCountMeasurement(const Icu_ChannelType LddChannel)
{
  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  /* Local variable to store the RAM index */
  uint8 LucIndex;
  /* To store Channel Measurement Mode */
  Icu_MeasurementModeType LenMeasurementMode;
  /* Defining a pointer to point to the TAUJ registers */
  P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUJChannelReg;
  #endif
  /* Defining a pointer to the TAU configuration parameters */
  P2CONST(Icu_TAUUnitConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUUnitConfig;
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_TAUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUChannelUserRegConfig;
  /* Defining a pointer to point to the TAUJ user registers */
  P2VAR(volatile Icu_TAUJUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUJUnitUserReg;

  /* Read channel configuration pointer */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Get the spinlock */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  /* Invoke service start count measurement and enable interrupt */
  Icu_HW_Tau_StartCountMeasurement(LddChannel);
  /* Read timer channel configuration pointer */
  LpTAUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannel].pHWChannelUserRegConfig;                           /* PRQA S 0317 # JV-01 */
  /* Update the TAU configuration pointer to point to the current TAU */
  LpTAUUnitConfig = &Icu_GpTAUUnitConfig[LpTAUChannelUserRegConfig->ucTimerUnitIndex];
  /* Initialize pointer to the base address of the current timer unit */
  LpTAUJUnitUserReg = (P2VAR(volatile Icu_TAUJUnitUserRegs, AUTOMATIC, REGSPACE)) LpTAUUnitConfig->pTAUnitUserCntlRegs; /* PRQA S 0310, 3305 # JV-01, JV-01 */
  #if (STD_ON == ICU_SET_MODE_API)
  /* Set the bit status running of channel is ICU_TRUE */
  Icu_GpChannelRamData[LddChannel].ucChannelRunning = (uint8)ICU_TRUE;                                                  /* PRQA S 4304 # JV-01 */
  #endif
  /* Set the bit corresponding to the channel number in TAUJnTT register */
  LpTAUJUnitUserReg->ucTAUJnTT = (uint8)LpChannelConfig->usChannelMaskValue;
  /* Set the bit corresponding to the channel number in TAUJnTS register */
  LpTAUJUnitUserReg->ucTAUJnTS = (uint8)LpChannelConfig->usChannelMaskValue;
  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  /* Get the channel measure mode */
  LenMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  if (ICU_MODE_SIGNAL_MEASUREMENT == LenMeasurementMode)
  {
    /* Initialize pointer to the base address of the current channel */
    LpTAUJChannelReg = (P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;       /* PRQA S 0316 # JV-01 */
    /* Reset Channel Status Clear Trigger Register */
    LpTAUJChannelReg->ucTAUJnCSCm = ICU_TAUJ_CSC_RESET_VAL;
    /* Read the current activation edge from RAM */
    LucIndex = Icu_GpChannelUserRegConfig[LddChannel].ucRamDataIndex;
    /* Initialize period measurement status as idle */
    Icu_GpSignalMeasurementData[LucIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_IDLE;
  } /* else No action required */
  #endif /* End of #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)*/
  /* Release the spinlock */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
} /* End of Internal function Icu_HW_Tauj_StartCountMeasurement */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Tauj_StopCountMeasurement
**
** Service ID           : None
**
** Description          : This service routine stops the count measurement.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : LddChannel
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Icu_GpChannelUserRegConfig, Icu_GpChannelConfig, Icu_GpTAUUnitConfig, 
**                        Icu_GpChannelRamData, Icu_GpSignalMeasurementData.
**
** Functions invoked    : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION, Icu_HW_Tau_StopCountMeasurement.
**
** Registers Used       : TAUJnTT, TAUJnCSCm
**
** Reference ID         : ICU_DUD_ACT_055, ICU_DUD_ACT_055_CRT001, ICU_DUD_ACT_055_CRT002
** Reference ID         : ICU_DUD_ACT_055_REG001, ICU_DUD_ACT_055_GBL002, ICU_DUD_ACT_055_GBL001
** Reference ID         : ICU_DUD_ACT_055_REG002
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Tauj_StopCountMeasurement(const Icu_ChannelType LddChannel)
{
  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  /* Local variable to store the RAM index */
  uint8 LucIndex;
  /* To store Channel Measurement Mode */
  Icu_MeasurementModeType LenMeasurementMode;
  /* Defining a pointer to point to the TAUJ registers */
  P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUJChannelReg;
  #endif
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_TAUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUChannelUserRegConfig;
  /* Defining a pointer to the TAU configuration parameters */
  P2CONST(Icu_TAUUnitConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUUnitConfig;
  /* Defining a pointer to point to the TAUJ registers */
  P2VAR(volatile Icu_TAUJUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUJUnitUserReg;

  /* Read channel configuration pointer */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Get the spinlock */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  /* Invoke service stop count measurement and disable interrupt */
  Icu_HW_Tau_StopCountMeasurement(LddChannel);
  /* Read timer channel configuration pointer */
  LpTAUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannel].pHWChannelUserRegConfig;                           /* PRQA S 0317 # JV-01 */
  /* Update the TAU configuration pointer to point to the current TAU */
  LpTAUUnitConfig = &Icu_GpTAUUnitConfig[LpTAUChannelUserRegConfig->ucTimerUnitIndex];
  /* Initialize pointer to the base address of the current timer unit */
  LpTAUJUnitUserReg = (P2VAR(volatile Icu_TAUJUnitUserRegs, AUTOMATIC, REGSPACE)) LpTAUUnitConfig->pTAUnitUserCntlRegs; /* PRQA S 0310, 3305 # JV-01, JV-01 */
  #if (STD_ON == ICU_SET_MODE_API)
  /* Set bit flag channel running is ICU_FALSE */
  Icu_GpChannelRamData[LddChannel].ucChannelRunning = (uint8)ICU_FALSE;                                                 /* PRQA S 4304 # JV-01 */
  #endif
  /* Set the bit corresponding to the channel number in TAUJnTT register */
  LpTAUJUnitUserReg->ucTAUJnTT = (uint8)LpChannelConfig->usChannelMaskValue;
  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  /* Get the channel measure mode */
  LenMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  if (ICU_MODE_SIGNAL_MEASUREMENT == LenMeasurementMode)
  {
    /* Initialize pointer to the base address of the current channel */
    LpTAUJChannelReg = (P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;       /* PRQA S 0316 # JV-01 */
    /* Reset Channel Status Clear Trigger Register */
    LpTAUJChannelReg->ucTAUJnCSCm = ICU_TAUJ_CSC_RESET_VAL;
    /* Read the current activation edge from RAM */
    LucIndex = Icu_GpChannelUserRegConfig[LddChannel].ucRamDataIndex;
    /* Initialize period measurement status as idle */
    Icu_GpSignalMeasurementData[LucIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_IDLE;
  } /* else No action required */
  #endif /* End of #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */
  /* Release the spinlock */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

} /* End of Internal function Icu_HW_Tauj_StopCountMeasurement */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Tauj_TimerIsr
**
** Service ID            : None
**
** Description           : This service routine invokes the required function
**                         based on the channel configuration for further calculations.
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
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelUserRegConfig,
**                         Icu_GpChannelRamData, Icu_GenModuleMode, Icu_GpSignalMeasurementData.
**
** Functions invoked     : Icu_HW_Tauj_ServiceSignalMeasurement,
**                         Icu_HW_Tauj_ServiceTimestamp,
**                         ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION
**                         EcuM_CheckWakeup, ICU_DEM_REPORT_ERROR.
**
** Registers Used        : TAUDnCDRm, TAUJnCSRm, TAUJnCSCm.
**
** Reference ID          : ICU_DUD_ACT_044, ICU_DUD_ACT_044_CRT001, ICU_DUD_ACT_044_CRT002
** Reference ID          : ICU_DUD_ACT_044_GBL002, ICU_DUD_ACT_044_GBL003, ICU_DUD_ACT_044_GBL006
** Reference ID          : ICU_DUD_ACT_044_GBL004, ICU_DUD_ACT_044_GBL005, ICU_DUD_ACT_044_GBL001
** Reference ID          : ICU_DUD_ACT_044_REG001, ICU_DUD_ACT_044_REG002
***********************************************************************************************************************/
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_CODE_FAST) Icu_HW_Tauj_TimerIsr(const Icu_ChannelType LddChannel)
{
  /* Defining a pointer to point to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  #if ((ICU_SIGNAL_MEASUREMENT_API == STD_ON) || (ICU_EDGE_COUNT_API == STD_ON))
  /* Define a pointer to point to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  #endif

  #if ((ICU_TIMESTAMP_API == STD_ON) || (ICU_SIGNAL_MEASUREMENT_API == STD_ON))
  /* Defining a pointer to point to the TAUJ registers */
  P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUJChannelReg;
  #endif

  Icu_MeasurementModeType LenMeasurementMode;
  #if (ICU_TIMESTAMP_API == STD_ON)
  uint32 LulCapturedTimestampVal;
  #endif

  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  uint8 LucMeasureProperty;
  uint8 LucPeriodMeasurementStatus;
  #endif
  
  #if ((ICU_SIGNAL_MEASUREMENT_API == STD_ON) || (ICU_EDGE_COUNT_API == STD_ON))
  uint8 LucIndex;
  /* Update the timer channel pointer to point to the current channel */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannel];
  /* Read the edge count RAM index */
  LucIndex = LpChannelUserRegConfig->ucRamDataIndex;
  #endif /* End of #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)*/

  /* Update the channel pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  /* Read the channel's measurement property */
  LenMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  #if (ICU_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  if ((uint16)ICU_ZERO != (uint16)(*LpChannelConfig->pIntrCntlAddress & ICU_EIC_EIMK_MASK))
  {
    ICU_DEM_REPORT_ERROR(ICU_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
    /* Check whether the channel is configured for Signal Measurement */
    if (ICU_MODE_SIGNAL_MEASUREMENT == LenMeasurementMode)
    {
      #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
      /* Initialize pointer to the base address of the current channel */
      LpTAUJChannelReg = (P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;     /* PRQA S 0316 # JV-01 */
      /* Check counter overflow flag */
      if (ICU_TAUJ_CSC_RESET_VAL == (LpTAUJChannelReg->ucTAUJnCSRm & ICU_TAUJ_CSC_RESET_VAL))
      {
        #if (ICU_NOTIFICATION_CONFIG == STD_ON)
        /* Check if the the channel is configured overflow the counter */
        if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
        {
          /* callback notification */
          LpChannelConfig->pIcuNotificationPointer();
        } /* else No action required */
        #endif /* End of (ICU_NOTIFICATION_CONFIG == STD_ON) */
        /* Clear overflow flag */
        LpTAUJChannelReg->ucTAUJnCSCm = ICU_TAUJ_CSC_RESET_VAL;
      } /* else No action required */
      /* Get the spinlock since ucChannelStatus, blResultComplete be updated by satellite core */
      ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Process Signal Measurement */
      Icu_HW_Tauj_ServiceSignalMeasurement(LddChannel);

      /* Read channel measurement property */
      LucMeasureProperty = LpChannelUserRegConfig->ucChannelProperties;
      /* Check measurement property is period */
      if (ICU_PERIOD_CHANNEL_ENABLED_MASK == (uint8)(LucMeasureProperty & ICU_HIGH_LOW_TIME_MASK))
      {

        LucPeriodMeasurementStatus = Icu_GpSignalMeasurementData[LucIndex].ucPeriodMeasurementStatus;                   /* PRQA S 0404 # JV-01 */
        if ((uint8)ICU_PERIOD_IDLE == LucPeriodMeasurementStatus)
        {
          /* Set period measurement status as ongoing */
          Icu_GpSignalMeasurementData[LucIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_ONGOING;
        }
        else /* if ((uint8)ICU_PERIOD_ONGOING == LucPeriodMeasurementStatus) */
        {
          /* Set channel input status as active */
          Icu_GpChannelRamData[LddChannel].ucChannelStatus = (uint8)ICU_ACTIVE;

          /* Set channel result status as available */
          Icu_GpChannelRamData[LddChannel].blResultComplete = ICU_TRUE;
        }
      }
      else /* (LucMeasureProperty != (ICU_PERIOD_TIME)) */
      {
        /* Set channel input status as active */
        Icu_GpChannelRamData[LddChannel].ucChannelStatus = (uint8)ICU_ACTIVE;

        /* Set channel result status as available */
        Icu_GpChannelRamData[LddChannel].blResultComplete = ICU_TRUE;
      }
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      #endif /* End of (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */
    }
    /* Check whether the channel is configured for Timestamp */
    else if (ICU_MODE_TIMESTAMP == LenMeasurementMode)
    {
      #if (ICU_TIMESTAMP_API == STD_ON)
      if ((uint8)ICU_ACTIVE == Icu_GpChannelRamData[LddChannel].ucChannelStatus)                                        /* PRQA S 0404, 3416 # JV-01, JV-01 */
      {
        /* Initialize pointer to the base address of the current channel */
        LpTAUJChannelReg = (P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;   /* PRQA S 0316 # JV-01 */

        /* Calculate captured value */
        LulCapturedTimestampVal = (uint32)(LpTAUJChannelReg->ulTAUJnCDRm + (uint32)ICU_ONE);                            /* PRQA S 3383 # JV-01 */

        /* Process Timestamp */
        Icu_HW_Tauj_ServiceTimestamp(LddChannel, LulCapturedTimestampVal);
      } /* else No action required */
      #endif /* End of (ICU_TIMESTAMP_API == STD_ON) */
    }
    else if (ICU_MODE_SIGNAL_EDGE_DETECT == LenMeasurementMode)
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
    }  /* End of (LddMeasurementMode == ICU_MODE_SIGNAL_EDGE_DETECT) */
    else /* If (ICU_MODE_EDGE_COUNTER == LddMeasurementMode)*/
    {
      #if (ICU_EDGE_COUNT_API == STD_ON)
      if ((uint8)ICU_ACTIVE == Icu_GpChannelRamData[LddChannel].ucChannelStatus)                                        /* PRQA S 0404, 3416 # JV-01, JV-01 */
      {
        /* Check if the number of edges is 0xFFFFFFFFUL */
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
    }
    #if ((ICU_REPORT_WAKEUP_SOURCE == STD_ON) && (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON))
    /* If Module was in SLEEP mode and reporting wakeup is enabled */
    if ((ICU_MODE_SLEEP == Icu_GenModuleMode) && ((uint8)ICU_TRUE == Icu_GpChannelRamData[LddChannel].ucWakeupEnable))  /* PRQA S 0404, 3415, 3416, 4304 # JV-01, JV-01, JV-01, JV-01 */
    {
      if (((uint8)ICU_FALSE == LpChannelConfig->ucIcuDisableEcumWakeupNotification) &&                                  /* PRQA S 4304 # JV-01 */
                                                           (ICU_NOWAKEUP != LpChannelConfig->ucEcuMChannelWakeupInfo))
      {
        /* Set the wakeup status to true */
        Icu_GpChannelRamData[LddChannel].blWakeupOccurrence = ICU_TRUE;

        /* Report Wakeup Event to EcuM */
        EcuM_CheckWakeup((EcuM_WakeupSourceType)(ICU_DOUBLE_ONE << (LpChannelConfig->ucEcuMChannelWakeupInfo)));
      } /* else No action required */
    } /* else No action required */
    #endif /* End of (ICU_REPORT_WAKEUP_SOURCE == STD_ON) */
  }
} /* End of Internal function Icu_HW_Tauj_TimerIsr */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Tauj_ServiceSignalMeasurement
**
** Service ID           : None
**
** Description          : This service routine calculates the channel's Signal
**                        Time (Low, High, Period or Duty) based on its configuration.
**
** Sync/Async           : Synchronous
**
** Reentrancy           : Reentrant
**
** Input Parameters     : LddChannel
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return parameter     : None
**
** Preconditions        : None
**
** Global Variables     : Icu_GpChannelConfig, Icu_GpSignalMeasurementData, Icu_GpChannelUserRegConfig.
**
** Functions invoked    : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION.
**
** Registers Used       : TAUJnCDRm
**
** Reference ID         : ICU_DUD_ACT_045
** Reference ID         : ICU_DUD_ACT_045_GBL001, ICU_DUD_ACT_045_GBL002
***********************************************************************************************************************/
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_CODE_FAST) Icu_HW_Tauj_ServiceSignalMeasurement(const Icu_ChannelType LddChannel)                        /* PRQA S 1505 # JV-01 */
{
  /* Defining a pointer to point to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  /* Define a pointer to point to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;

  /* Defining a pointer to point to the TAUJ registers */
  P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUJChannelReg;                                        /* PRQA S 3678 # JV-01 */

  uint8 LucMeasureProperty;
  uint8 LucRamIndex;

  /* Read channel configuration pointer */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  /* Read timer channel configuration pointer */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannel];

  /* Read the channel ram index */
  LucRamIndex = LpChannelUserRegConfig->ucRamDataIndex;
  /* Read channel measurement property */
  LucMeasureProperty = LpChannelUserRegConfig->ucChannelProperties;

  /* Initialize pointer to the base address of the current channel */
  LpTAUJChannelReg = (P2VAR(volatile Icu_TAUJChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;         /* PRQA S 0316 # JV-01 */

  if ((ICU_HIGH_TIME_MASK == (uint8)(LucMeasureProperty & ICU_HIGH_LOW_TIME_MASK)) ||
                                           (ICU_LOW_TIME_MASK == (uint8)(LucMeasureProperty & ICU_HIGH_LOW_TIME_MASK)))
  /* Calculate Active time */
  {
    Icu_GpSignalMeasurementData[LucRamIndex].ulSignalActiveTime =                                                       /* PRQA S 0404 # JV-01 */
                                                           (uint32)((LpTAUJChannelReg->ulTAUJnCDRm) + (uint32)ICU_ONE); /* PRQA S 3383 # JV-01 */
  }
  else /* (LucMeasureProperty == (ICU_PERIOD_TIME)) */
  {
    Icu_GpSignalMeasurementData[LucRamIndex].ulPrevSignalActiveTime =                                                   /* PRQA S 0404 # JV-01 */
                                                           Icu_GpSignalMeasurementData[LucRamIndex].ulSignalActiveTime;
    /* Calculate Period time */
    Icu_GpSignalMeasurementData[LucRamIndex].ulSignalPeriodTime =                                                       /* PRQA S 0404 # JV-01 */
                                                             (uint32)(LpTAUJChannelReg->ulTAUJnCDRm + (uint32)ICU_ONE); /* PRQA S 3383 # JV-01 */
  }

} /* End of Internal function Icu_HW_Tauj_ServiceSignalMeasurement */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Tauj_ServiceTimestamp
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
** Global Variables      : Icu_GpChannelConfig, Icu_GpTimeStampData, Icu_GpChannelUserRegConfig, Icu_GpChannelRamData.
**
** Functions invoked     : pIcuNotificationPointer.
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_046, ICU_DUD_ACT_046_GBL001, ICU_DUD_ACT_046_GBL002
***********************************************************************************************************************/
#if (ICU_TIMESTAMP_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_CODE_FAST)
                   Icu_HW_Tauj_ServiceTimestamp(const Icu_ChannelType LddChannel, const uint32 LulCapturedTimestampVal) /* PRQA S 1505 # JV-01 */
{
  #if (ICU_NOTIFICATION_CONFIG == STD_ON)
  /* Defining a pointer to point to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  #endif /* if (ICU_NOTIFICATION_CONFIG == STD_ON) */
  /* Defining a pointer to point to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;

  P2VAR(volatile Icu_TimeStampChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpTimestampdata;

  /* Local variable used to store the ram index of the channel */
  uint8 LucRamIndex;
  #if (ICU_NOTIFICATION_CONFIG == STD_ON)
  /* Update the channel pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  #endif /* if (ICU_NOTIFICATION_CONFIG == STD_ON) */
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
      if (ICU_TS_CIRCULAR_BUFFER_MASK ==
                                    (uint8)(LpChannelUserRegConfig->ucChannelProperties & ICU_TS_CIRCULAR_BUFFER_MASK))
      {
        /* Reset buffer pointer and index */
        LpTimestampdata->usTimestampIndex = (uint16)ICU_BUFFER_IDX_INIT_VAL;
        LpTimestampdata->pBufferPointer = LpTimestampdata->pBufferPointer - LpTimestampdata->usBufferSize;              /* PRQA S 0404, 0488 # JV-01, JV-01 */
      }
      else
      {
        /* Stop the hardware channel */
        Icu_HW_Tauj_StopCountMeasurement(LddChannel);
      }
    } /* else No action required */

    /* Notify if the configured number of timestamps are captured and notification is enabled */
    #if (ICU_NOTIFICATION_CONFIG == STD_ON)

    if ((uint8)ICU_TRUE == Icu_GpChannelRamData[LddChannel].ucNotificationEnable)                                       /* PRQA S 0404, 3416, 4304 # JV-01, JV-01, JV-01 */
    {
      (LpTimestampdata->usTimestampsCounter)++;                                                                         /* PRQA S 3383, 3387 # JV-01, JV-01 */
      if ((LpTimestampdata->usTimestampsCounter) == (LpTimestampdata->usNotifyInterval))                                /* PRQA S 0404 # JV-01 */
      {
        /* Reset the number of timestamp captured counter */
        LpTimestampdata->usTimestampsCounter = (uint16)ICU_TIMESTAMP_RESET_CNT_VAL;
        /* Check if the function pointer address is present for particular channel */
        if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
        {
          /* callback notification */
          LpChannelConfig->pIcuNotificationPointer();
        } /* else No action required */
      } /* else No action required */
    } /* else No action required*/
    #endif /* if (ICU_NOTIFICATION_CONFIG == STD_ON) */
  } /* else No action required */

} /* End of Internal function Icu_HW_Tauj_ServiceTimestamp */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_TIMESTAMP_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Tauj_GetTAUInCountValue
**
** Service ID            : NA
**
** Description           : This API service returns the counter value of TAU timer.
**
** Sync/Async            : NA
**
** Reentrancy            : NA
**
** Input Parameters      : LddChannel
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Icu_CounterValueType
**
** Preconditions         : The Icu Driver must be initialized, ICU_GET_TAU_COUNT_VALUE_API must be STD_ON
**
** Global Variables      : Icu_GpChannelConfig
**
** Functions invoked     : None
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_056
***********************************************************************************************************************/
#if (ICU_GET_TAU_COUNT_VALUE_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Icu_CounterValueType, ICU_PRIVATE_CODE) Icu_HW_Tauj_GetTAUInCountValue(const Icu_ChannelType LddChannel)
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_TAUChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUChannelConfig;

  /* Local variable to store the return level value  */
  Icu_CounterValueType LddTAUInCounterValue;

  /* Initialize the return value */
  LddTAUInCounterValue = ICU_TAU_CNT_INIT_VAL;

  LpTAUChannelConfig = Icu_GpChannelConfig[LddChannel].pHWIPChannelConfig;                                              /* PRQA S 0317 # JV-01 */

  /* Get the TAUIn counter value of particular channel */
  if (NULL_PTR != LpTAUChannelConfig->pTAUJCNTAddress)
  {
    LddTAUInCounterValue = *(LpTAUChannelConfig->pTAUJCNTAddress);
  } /* else No action required */

  /* Return the TAUIn counter value of particular channel */
  return (LddTAUInCounterValue);
} /* End of API Icu_HW_Tauj_GetTAUInCountValue */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_GET_TAU_COUNT_VALUE_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : Icu_HW_Tauj_ResetEdgeCount
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
** Reference ID          : ICU_DUD_ACT_105, ICU_DUD_ACT_105_CRT001, ICU_DUD_ACT_105_CRT002, ICU_DUD_ACT_105_GBL001
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Tauj_ResetEdgeCount(const Icu_ChannelType LddChannel)
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
** Function Name         : Icu_HW_Tauj_EdgeCountingInit
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
** Reference ID          : ICU_DUD_ACT_106, ICU_DUD_ACT_106_GBL001
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE)
  Icu_HW_Tauj_EdgeCountingInit(P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig)/* PRQA S 1505 # JV-01 */
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

#endif /* End of (ICU_TAUJ_UNIT_USED == STD_ON) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
