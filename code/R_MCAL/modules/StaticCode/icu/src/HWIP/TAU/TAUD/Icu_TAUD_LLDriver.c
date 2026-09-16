/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_TAUD_LLDriver.c                                                                                 */
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
                         1. Add 3416, 3006 and remove 1532, 2814, 2824, 2844, 3305, 3678, 4304
 * 2.3.0:  28/02/2025  : As part of ARDAACL-52090, following changes are made:
 *                       Update function Icu_HW_Taud_UnitDeInit, Icu_HW_Taud_UnitInit 
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : As part of support GTM HWIP into common code, following changes are made:
 *                       1. Remove redundant QAC messages.  
 *                       2. Remove comment CRITICAL_SECTION in description information of 
 *                       Icu_HW_Taud_ServiceSignalMeasurement
 *                       3. Remove function Icu_HW_Taud_SetMode, Icu_HW_Taud_EnableEdgeDetection, 
 *                       Icu_HW_Taud_DisableEdgeDetection
 *                       4. Remove condition to check the edge detect on Icu_HW_Taud_StopCountMeasurement
 *                       Icu_HW_Taud_StartCountMeasurement 
 *                       5. Remove update value of Icu_GpSignalMeasurementData in Icu_HW_Taud_UnitInit
 *                       Update SW-VERSION for Ver22.01.02 Beta2 Release 
 * 2.0.1:  19/10/2023  : Remove QAC messages 0857, 1532, 2814, 2824, 2844. Add QAC messages 3006, 4304, 3415, 3416
 *         14/10/2023  : Remove pre-compile parameter ICU_E_INT_INCONSISTENT_CONFIGURED for ICU_DEM_REPORT_ERROR
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 *                       Icu_HW_Taud_UnitInit only stop the channel configured by ICU
 *                       Access ucChannelRunning which precompiles STD_ON == ICU_SET_MODE_API
 *                       Update the Global critical section 
 *                       Icu_HW_Taud_TimerIsr update precompile condition and brand condition when the report wake up
 *                       Icu_HW_Taud_ServiceTimestamp: Stop hardware channel upon buffer linear reach the end.
 *         09/06/2023  : Update function Icu_HW_Taud_SetActivation for set the edge detection due to Autosar
 *                       R21-11 change typedef enum ETag_Icu_ActivationType
 * 1.4.5:  17/11/2022  : Update "Input Parameters", "Global Variables", 
 *                       "Functions invoked" for all functions.
 *         15/11/2022  : Update Icu_HW_Taud_UnitDeInit to access all TAUDnTT registers
 * 1.4.4:  16/06/2022  : Update QAC message and QAC header
 * 1.4.3:  23/05/2022  : Fix QAC header and message.
 *         14/05/2022  : Change type of pTAUD3INTNOSELxReg from uint16 to uint32
 *                     : Change  ICU_TAUD3_INTERRUPT_SELECTION_USED to ICU_TAUD3_UNIT_USED
 *         09/05/2022  : Remove "else" statement when no action required; add QAC message 2004.
 *         17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 *         13/04/2022  : Update function Icu_HW_Taud_GetTAUInCountValue and add Null check before read 
 *                       pCNTAddress counter value
 * 1.4.2:  02/03/2022  : Fix QAC header and message
 * 1.4.1:  07/10/2021  : Remove code segment of usTAUDnTPS and ucTAUDnBRS in Icu_HW_Taud_UnitDeInit
 *         18/10/2021  : Add QAC message 9.5.0
 *         16/09/2021  : Correct preprocessor directives
 *                       Correct if conditions
 *                       Correct names, datatypes of used variables
 *                       Correct indents
 *                       Remove redundant if/else, switch/case branches
 *                       Remove redundant deinitialization for INTP
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
#include "Icu_TAUD_LLDriver.h"
/* Included for RAM variable declarations */
#include "Icu_Ram.h"
#include "Icu_TAUD_Ram.h"

#if (ICU_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
/* Include for interrupt consistency check */
#include "Dem.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ICU_TAUD_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_TAUD_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_TAUD_LLDRIVER_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ICU_TAUD_LLDRIVER_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_TAUD_LLDRIVER_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ICU_TAUD_LLDRIVER_AR_RELEASE_MAJOR_VERSION != ICU_TAUD_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "Icu_TAUD_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (ICU_TAUD_LLDRIVER_AR_RELEASE_MINOR_VERSION != ICU_TAUD_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "Icu_TAUD_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (ICU_TAUD_LLDRIVER_AR_RELEASE_REVISION_VERSION != ICU_TAUD_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "Icu_TAUD_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (ICU_TAUD_LLDRIVER_SW_MAJOR_VERSION != ICU_TAUD_LLDRIVER_C_SW_MAJOR_VERSION)
#error "Icu_TAUD_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (ICU_TAUD_LLDRIVER_SW_MINOR_VERSION != ICU_TAUD_LLDRIVER_C_SW_MINOR_VERSION)
#error "Icu_TAUD_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#if (ICU_TAUD_UNIT_USED == STD_ON)
/***********************************************************************************************************************
** Function Name        : Icu_HW_Taud_UnitInit
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
** Registers Used       : TAUDnTT, TAUDnTPS, TAUDnBRS, PIC1TAUDnSEL, PIC1SELB_TAUD2I
**
** Reference ID         : ICU_DUD_ACT_030, ICU_DUD_ACT_030_GBL002, ICU_DUD_ACT_030_GBL003
** Reference ID         : ICU_DUD_ACT_030_REG001, ICU_DUD_ACT_030_REG002, ICU_DUD_ACT_030_REG003
** Reference ID         : ICU_DUD_ACT_030_REG004, ICU_DUD_ACT_030_REG005, ICU_DUD_ACT_030_REG006
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Taud_UnitInit(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST) ConfigPtr)
{

  #if (ICU_PRESCALER_CONFIGURED == STD_ON)
  /* Defining a pointer to the TAU configuration parameters */
  P2CONST(Icu_TAUUnitConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUUnitConfig;
  /* Declare a Local variable to Unit Type */
  uint8 LucUnitType;
  /* Local variable to hold the channel number */
  uint8 LucCount;
  /* Pointer pointing to the TAUD Unit control registers */
  P2VAR(volatile Icu_TAUDUnitOsRegs, AUTOMATIC, REGSPACE) LpTAUDUnitOsReg;
  P2VAR(volatile Icu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  #endif

  /* Store the global pointer to the first Unit Configuration */
  Icu_GpTAUUnitConfig = ConfigPtr->pTAUUnitConfig;                                                                      /* PRQA S 0317 # JV-01 */

  #if (ICU_PRESCALER_CONFIGURED == STD_ON)
  for (LucCount = (uint8)ICU_ZERO; LucCount < (uint8)ICU_TOTAL_TAU_UNITS_CONFIGURED; LucCount++)
  {
    /* Update the Timer channel configuration pointer to point to the current channel */
    LpTAUUnitConfig = &Icu_GpTAUUnitConfig[LucCount];
    /* Read the Unit Type for the given unit */
    LucUnitType = LpTAUUnitConfig->ucIcuUnitType;
    /* Invoke low-level driver for initializing the hardware */
    if(ICU_HW_TAUD == LucUnitType)
    {
      /* Initialize pointer to the base address of the current timer unit */
      LpTAUDUnitOsReg = (P2VAR(volatile Icu_TAUDUnitOsRegs, AUTOMATIC, REGSPACE)) LpTAUUnitConfig->pTAUnitOsCntlRegs;   /* PRQA S 0310, 3305 # JV-01, JV-01 */
      LpTAUDUnitUserReg = (P2VAR(volatile Icu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE))                                   /* PRQA S 0310, 3305 # JV-01, JV-01 */
                                                                        LpTAUUnitConfig->pTAUnitUserCntlRegs;
      /* Set the values of baud rate to TPS/BRS registers respectively */
      if ((uint8)ICU_TRUE == LpTAUUnitConfig->ucConfigurePrescaler)                                                     /* PRQA S 4304 # JV-01 */
      {
        /* Set the bit corresponding to the channel number in the TAUDnTT register */
        LpTAUDUnitUserReg->usTAUDnTT = ICU_TAUD_TIMER_RESET_VAL;
        /* Write the configured prescaler value to TAUDnTPS register */
        LpTAUDUnitOsReg->usTAUDnTPS = LpTAUUnitConfig->usPrescaler;
        /* Load the configured baud rate value */
        LpTAUDUnitOsReg->ucTAUDnBRS = LpTAUUnitConfig->ucBaudRate;
      }
      else
      {
        /* Set the bit corresponding to the channel number in TAUDnTT register */
        LpTAUDUnitUserReg->usTAUDnTT = LpTAUUnitConfig->usTAUChannelMaskValue;
      }
      #if (ICU_TAUDN_USE_PREVIOUS_INPUT == STD_ON)
      /* Write PIC1TAUD01SEL register */
      if(NULL_PTR != LpTAUUnitConfig->pPic1TaudnSelRegs)
      {
        *(LpTAUUnitConfig->pPic1TaudnSelRegs) = LpTAUUnitConfig->ulPic1TaudnSelVal;
      }/* Else no action */
      #endif
      #if (ICU_TAUD2_USE_PREVIOUS_INPUT == STD_ON)
      /* Write PIC1TAUD2SEL register */
      if(NULL_PTR != LpTAUUnitConfig->pPic1Taud2SelRegs)
      {
        *(LpTAUUnitConfig->pPic1Taud2SelRegs) = LpTAUUnitConfig->usPic1Taud2SelVal;
      }/* Else no action */
      #endif
    } /* else No action required */
  } /* End of looping all units */
  #endif

} /* End of Internal function Icu_HW_Taud_UnitInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Taud_ChannelInit
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
** Functions invoked    : Icu_HW_Taud_TimestampInit,
**                        Icu_HW_Taud_SignalMeasurementInit.
**
** Registers Used       : TAUDnCMORm, TAUDnCMURm, TAUDnCDRm, TAUDnCSCm, TAUD3INTNOSELx
**
** Reference ID         : ICU_DUD_ACT_031, ICU_DUD_ACT_031_REG001, ICU_DUD_ACT_031_REG002, ICU_DUD_ACT_031_REG006
** Reference ID         : ICU_DUD_ACT_031_REG004, ICU_DUD_ACT_031_REG005, ICU_DUD_ACT_031_GBL001
** Reference ID         : ICU_DUD_ACT_031_GBL002, ICU_DUD_ACT_031_GBL003, ICU_DUD_ACT_031_GBL004
** Reference ID         : ICU_DUD_ACT_031_GBL005, ICU_DUD_ACT_031_GBL006, ICU_DUD_ACT_031_REG003
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Taud_ChannelInit(const Icu_ChannelType LddChannelIndex)                             /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* Defining a pointer to the Channel Ram Data */
  P2VAR(volatile Icu_ChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpRamData;

  #if ((ICU_TIMESTAMP_API == STD_ON) || (ICU_SIGNAL_MEASUREMENT_API == STD_ON))
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  #endif
  /* Defining a pointer to the TAU channel configuration parameters */
  P2CONST(Icu_TAUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUChannelUserRegConfig;

  /* Pointer pointing to the TAUD channel control registers */
  P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;

  /* Local variable to store the measurement mode of a channel */
  Icu_MeasurementModeType LenMeasurementMode;
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

  #if ((ICU_TIMESTAMP_API == STD_ON) || (ICU_SIGNAL_MEASUREMENT_API == STD_ON))
  /* Update the Timer channel configuration pointer to point to the current channel*/
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannelIndex];
  #endif

  LpTAUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannelIndex].pHWChannelUserRegConfig;                      /* PRQA S 0317 # JV-01 */

  /* Check if configuration contains any timer channels */
  /* Read the channel's measurement mode */
  LenMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  /* Initialize pointer to the base address of the current channel */
  LpTAUDChannelReg = (P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;         /* PRQA S 0316 # JV-01 */

  /* If the measurement mode is edge counter, put the defined count value to CDR Register */
  if (ICU_MODE_EDGE_COUNTER == LenMeasurementMode)
  {
    /* Assign the down count value to CDR register */
    LpTAUDChannelReg->usTAUDnCDRm = ICU_TAUD_START_DWNCNT_VAL;
  } /* else No action required */
  /* End of ICU_MODE_EDGE_COUNTER == LenMeasurementMode */

  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disabling the Interrupt processing */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);                              /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */

  #if (ICU_EDGE_DETECT_API == STD_ON)
  /* Reset CDR register if the measurement mode is edge detection */
  if (ICU_MODE_SIGNAL_EDGE_DETECT == LenMeasurementMode)
  {
    LpTAUDChannelReg->usTAUDnCDRm = ICU_TAUD_CDR_RESET_VAL;
  } /* else No action required */
  /* End of ICU_MODE_SIGNAL_EDGE_DETECT == LenMeasurementMode */
  #endif /* End of (ICU_EDGE_DETECT_API == STD_ON) */

  /* Read the value of Channel Mode OS Register configured */
  *(LpTAUChannelUserRegConfig->pCMORReg) = LpTAUChannelUserRegConfig->usChannelModeOSRegSettings;

  /* Read the value of Channel Mode User Register configured */
  LpTAUDChannelReg->ucTAUDnCMURm = LpTAUChannelUserRegConfig->ucChannelModeUserRegSettings;

  /* Reset Channel Status Clear Trigger Register */
  LpTAUDChannelReg->ucTAUDnCSCm = ICU_TAUD_CSC_RESET_VAL;
  
  /* Set value for TAUD3 interrupt selection register */
  #if (ICU_TAUD3_UNIT_USED == STD_ON)
  if (NULL_PTR != LpTAUChannelUserRegConfig->pTAUD3INTNOSELxReg)
  {
      RH850_SV_SET_ICR_SYNCP(32, LpTAUChannelUserRegConfig->pTAUD3INTNOSELxReg,                                         /* PRQA S 1006 # JV-01 */
                                            LpTAUChannelUserRegConfig->ulTAUD3SelectInterruptMask);
  } /* else No action required */
  #endif

  #if ((ICU_TIMESTAMP_API == STD_ON) || (ICU_SIGNAL_MEASUREMENT_API == STD_ON))
  if (ICU_MODE_TIMESTAMP == LenMeasurementMode)
  {
    #if (ICU_TIMESTAMP_API == STD_ON)
    /* Configure the channel in Timestamp Mode */
    Icu_HW_Taud_TimestampInit(LpChannelUserRegConfig);
    #endif
  }
  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  else if (ICU_MODE_SIGNAL_MEASUREMENT == LenMeasurementMode)                                                           /* PRQA S 2004 # JV-01 */
  {
    /* Configure the channel in Signal Measurement Mode */
    Icu_HW_Taud_SignalMeasurementInit(LpChannelUserRegConfig);
  } /* else No action required */
  #endif
  #endif /* End of ((ICU_TIMESTAMP_API == STD_ON) || (ICU_SIGNAL_MEASUREMENT_API == STD_ON)) */
} /* End of Internal function Icu_HW_Taud_ChannelInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Taud_UnitDeInit
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
** Registers Used       : TAUDnTT, PIC1TAUDnSEL, PIC1SELB_TAUD2I
**
** Reference ID         : ICU_DUD_ACT_032, ICU_DUD_ACT_032_REG001, ICU_DUD_ACT_032_REG002, ICU_DUD_ACT_032_REG003
***********************************************************************************************************************/
#if (ICU_DE_INIT_API == STD_ON)

#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Taud_UnitDeInit(void)
{
  /* Defining a pointer to the TAU configuration parameters */
  P2CONST(Icu_TAUUnitConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUUnitConfig;

  /* Pointer pointing to the TAUD channel control registers */
  P2VAR(volatile Icu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;

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
    if (ICU_HW_TAUD == LucTimerType)
    {
      /* Initialize pointer to the base address of the current channel */
      LpTAUDUnitUserReg =
            (P2VAR(volatile Icu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE))(LpTAUUnitConfig[LucCount].pTAUnitUserCntlRegs); /* PRQA S 0310, 3305 # JV-01, JV-01 */

      /* Set the bit corresponding to the channel number in TAUDnTT register */
      LpTAUDUnitUserReg->usTAUDnTT = LpTAUUnitConfig[LucCount].usTAUChannelMaskValue;
      /* Write PIC1 for USE_PREVIOUS_INPUT feature */
      #if (ICU_TAUDN_USE_PREVIOUS_INPUT == STD_ON)
      if(NULL_PTR != LpTAUUnitConfig[LucCount].pPic1TaudnSelRegs)
      {
        /* Clear PIC1TAUD01SEL value */
        *(LpTAUUnitConfig[LucCount].pPic1TaudnSelRegs) = ICU_DOUBLE_ZERO;
      }/* Else no action */
      #endif
      #if (ICU_TAUD2_USE_PREVIOUS_INPUT == STD_ON)
      if(NULL_PTR != LpTAUUnitConfig[LucCount].pPic1Taud2SelRegs)
      {
        /* Clear PIC1TAUD2SEL value */
        *(LpTAUUnitConfig[LucCount].pPic1Taud2SelRegs) = ICU_16BIT_ZERO;
      }/* Else no action */
      #endif
    } /* else No action required */
  }
} /* End of Internal function Icu_HW_Taud_UnitDeInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_DE_INIT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Taud_ChannelDeInit
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
** Registers Used       : TAUDnCMORm, TAUDnCDRm, TAUDnCSCm, TAUDnCMURm, TAUD3INTNOSELx.
**
** Reference ID         : ICU_DUD_ACT_033, ICU_DUD_ACT_033_REG001, ICU_DUD_ACT_033_REG002, ICU_DUD_ACT_033_REG003,
** Reference ID         : ICU_DUD_ACT_033_GBL001, ICU_DUD_ACT_033_GBL004, ICU_DUD_ACT_033_GBL002
** Reference ID         : ICU_DUD_ACT_033_GBL005, ICU_DUD_ACT_033_GBL003, ICU_DUD_ACT_033_GBL006,
** Reference ID         : ICU_DUD_ACT_033_REG004, ICU_DUD_ACT_033_REG005, ICU_DUD_ACT_033_REG006
***********************************************************************************************************************/
#if (ICU_DE_INIT_API == STD_ON)

#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Taud_ChannelDeInit(const Icu_ChannelType LddChannelIndex)                           /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_TAUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUChannelUserRegConfig;

  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* Defining a pointer to the channel Ram data */
  P2VAR(volatile Icu_ChannelRamDataType, AUTOMATIC, ICU_CONFIG_DATA) LpRamData;

  /* Pointer pointing to the TAUD channel control registers */
  P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;

  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannelIndex];
  /* Load the channel data pointer */
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
  LpTAUDChannelReg = (P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;         /* PRQA S 0316 # JV-01 */

  /* Reset the value of Channel Mode OS Register */
  *(LpTAUChannelUserRegConfig->pCMORReg) = ICU_TAUD_CMOR_RESET_VAL;

  /* Reset the value of Channel Data Register */
  LpTAUDChannelReg->usTAUDnCDRm = ICU_TAUD_CDR_RESET_VAL;

  /* Reset the value of Channel Mode User Register */
  LpTAUDChannelReg->ucTAUDnCMURm = ICU_TAUD_CMUR_RESET_VAL;

  /* Reset Channel Status Clear Trigger Register */
  LpTAUDChannelReg->ucTAUDnCSCm = ICU_TAUD_CSC_RESET_VAL;
  
  /* Reset value for TAUD3 interrupt selection register */
  #if (ICU_TAUD3_UNIT_USED == STD_ON)
  if (NULL_PTR != LpTAUChannelUserRegConfig->pTAUD3INTNOSELxReg)
  {
      RH850_SV_CLEAR_ICR_SYNCP(32, LpTAUChannelUserRegConfig->pTAUD3INTNOSELxReg,                                       /* PRQA S 1006 # JV-01 */
                                            ~LpTAUChannelUserRegConfig->ulTAUD3SelectInterruptMask);
  } /* else No action required */
  #endif

  if (NULL_PTR != LpChannelConfig->pIntrCntlAddress)
  {
    /* Disabling the Interrupt processing */
    RH850_SV_SET_ICR_SYNCP(8, (LpChannelConfig->pIntrCntlAddress), ICU_DISABLE_EIMK_MASK);                              /* PRQA S 0751, 1006 # JV-01, JV-01 */
  } /* else No action required */
} /* End of Internal function Icu_HW_Taud_ChannelDeInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* End of (ICU_DE_INIT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Taud_TimestampInit
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
** Reference ID          : ICU_DUD_ACT_035, ICU_DUD_ACT_035_GBL001
***********************************************************************************************************************/
#if (ICU_TIMESTAMP_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE)
Icu_HW_Taud_TimestampInit(P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig)     /* PRQA S 1505 # JV-01 */
{
  /* Local variable used to store the channel index */
  uint8 LucIndex;
  /* Read the Timestamp Channel ram index */
  LucIndex = LpChannelUserRegConfig->ucRamDataIndex;

  Icu_GpTimeStampData[LucIndex].usTimestampIndex = (uint16)ICU_BUFFER_IDX_INIT_VAL;
} /* End of Internal function Icu_HW_Taud_TimestampInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_TIMESTAMP_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Taud_SignalMeasurementInit
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
** Reference ID          : ICU_DUD_ACT_036, ICU_DUD_ACT_036_GBL001,
** Reference ID          : ICU_DUD_ACT_036_GBL002, ICU_DUD_ACT_036_GBL003, ICU_DUD_ACT_036_GBL004
***********************************************************************************************************************/
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE)Icu_HW_Taud_SignalMeasurementInit                                                           /* PRQA S 1505 # JV-01 */
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
} /* End of Internal function Icu_HW_Taud_SignalMeasurementInit */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */

/***********************************************************************************************************************
** Function Name        : Icu_HW_Taud_SetActivation
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
** Functions invoked    : RH850_SV_CLEAR_ICR_SYNCP
**
** Registers Used       : TAUDnCMURm
**
** Reference ID         : ICU_DUD_ACT_037, ICU_DUD_ACT_037_REG001, ICU_DUD_ACT_037_REG004
** Reference ID         : ICU_DUD_ACT_037_REG002, ICU_DUD_ACT_037_REG003, ICU_DUD_ACT_037_GBL001
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE)
                    Icu_HW_Taud_SetActivation(const Icu_ChannelType LddChannel, const Icu_ActivationType LenActiveEdge) /* PRQA S 3006 # JV-01 */
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  /* Defining a pointer to point to the TAUD registers */
  P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;

  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  LpTAUDChannelReg = (P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;         /* PRQA S 0316 # JV-01 */

  if (ICU_FALLING_EDGE == LenActiveEdge)
  {
    /* Set the edge detection bits in the channel mode user register as per mask */
    LpTAUDChannelReg->ucTAUDnCMURm = ICU_TAU_FALLING_EDGE_MASK;
  }

  else if (ICU_RISING_EDGE == LenActiveEdge)
  {
    /* Set the edge detection bits in the channel mode user register as per mask */
    LpTAUDChannelReg->ucTAUDnCMURm = ICU_TAU_RISING_EDGE_MASK;
  }

  else
  {
    /* Set the edge detection bits in the channel mode user register as per mask */
    LpTAUDChannelReg->ucTAUDnCMURm = ICU_TAU_BOTH_EDGES_MASK;
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

} /* End of Internal function Icu_HW_Taud_SetActivation */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Taud_StartCountMeasurement
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
** Global Variables     : Icu_GpChannelUserRegConfig, Icu_GpChannelConfig, Icu_GpTAUUnitConfig, Icu_GpChannelRamData,
**                        Icu_GpSignalMeasurementData.
**
** Functions invoked    : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION, Icu_HW_Tau_StartCountMeasurement.
**
** Registers Used       : TAUDnTT, TAUDnTS, TAUDnCSCm.
**
** Reference ID         : ICU_DUD_ACT_038, ICU_DUD_ACT_038_CRT001, ICU_DUD_ACT_038_CRT002, ICU_DUD_ACT_038_GBL001,
** Reference ID         : ICU_DUD_ACT_038_REG001, ICU_DUD_ACT_038_REG002, ICU_DUD_ACT_038_GBL002
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Taud_StartCountMeasurement(const Icu_ChannelType LddChannel)
{
  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  /* Local variable to store the RAM index */
  uint8 LucIndex;
  /* To store Channel Measurement Mode */
  Icu_MeasurementModeType LenMeasurementMode;
  /* Defining a pointer to point to the TAUD registers */
  P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;
  #endif
  /* Defining a pointer to the TAU configuration parameters */
  P2CONST(Icu_TAUUnitConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUUnitConfig;
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_TAUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUChannelUserRegConfig;
  /* Defining a pointer to point to the TAUD user registers */
  P2VAR(volatile Icu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;
  /* Read channel configuration pointer */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  /* Get the spinlock */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  /* Eanble the ISR */
  Icu_HW_Tau_StartCountMeasurement(LddChannel);
  /* Read timer channel configuration pointer */
  LpTAUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannel].pHWChannelUserRegConfig;                           /* PRQA S 0317 # JV-01 */
  /* Update the TAU configuration pointer to point to the current TAU */
  LpTAUUnitConfig = &Icu_GpTAUUnitConfig[LpTAUChannelUserRegConfig->ucTimerUnitIndex];
  /* Initialize pointer to the base address of the current timer unit */
  LpTAUDUnitUserReg = (P2VAR(volatile Icu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE)) LpTAUUnitConfig->pTAUnitUserCntlRegs; /* PRQA S 0310, 3305 # JV-01, JV-01 */
  #if (STD_ON == ICU_SET_MODE_API)
  /* Set the bit status running of channel is ICU_TRUE*/
  Icu_GpChannelRamData[LddChannel].ucChannelRunning = (uint8)ICU_TRUE;                                                  /* PRQA S 4304 # JV-01 */
  #endif
  /* Set the bit corresponding to the channel number in TAUDnTT register */
  LpTAUDUnitUserReg->usTAUDnTT = (LpChannelConfig->usChannelMaskValue);
  /* Set the bit corresponding to the channel number in TAUDnTS register */
  LpTAUDUnitUserReg->usTAUDnTS = (LpChannelConfig->usChannelMaskValue);
  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  /* Read measurement mode */
  LenMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  if (ICU_MODE_SIGNAL_MEASUREMENT == LenMeasurementMode)
  {
    /* Initialize pointer to the base address of the current channel */
    LpTAUDChannelReg = (P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;       /* PRQA S 0316 # JV-01 */
    /* Clear overflow flag */
    LpTAUDChannelReg->ucTAUDnCSCm = ICU_TAUD_CSC_RESET_VAL;
    /* Read the current activation edge from RAM */
    LucIndex = Icu_GpChannelUserRegConfig[LddChannel].ucRamDataIndex;
    /* Initialize period measurement status as idle */
    Icu_GpSignalMeasurementData[LucIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_IDLE;
  } /* else No action required */
  #endif /* End of #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)*/
  /* Release the spinlock */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

} /* End of Internal function Icu_HW_Taud_StartCountMeasurement */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Taud_StopCountMeasurement
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
** Global Variables     : Icu_GpChannelUserRegConfig, Icu_GpChannelConfig, Icu_GpTAUUnitConfig, Icu_GpChannelRamData,
**                        Icu_GpSignalMeasurementData.
**
** Functions invoked    : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION, Icu_HW_Tau_StopCountMeasurement.
**
** Registers Used       : TAUDnTT, TAUDnCSCm
**
** Reference ID         : ICU_DUD_ACT_039, ICU_DUD_ACT_039_CRT001, ICU_DUD_ACT_039_CRT002
** Reference ID         : ICU_DUD_ACT_039_GBL001, ICU_DUD_ACT_039_REG001, ICU_DUD_ACT_039_GBL002
***********************************************************************************************************************/
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Taud_StopCountMeasurement(const Icu_ChannelType LddChannel)
{
  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  /* Local variable to store the RAM index */
  uint8 LucIndex;
  /* To store Channel Measurement Mode */
  Icu_MeasurementModeType LenMeasurementMode;
  /* Defining a pointer to point to the TAUD registers */
  P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;
  #endif
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;
  /* Defining a pointer to the TAU configuration parameters */
  P2CONST(Icu_TAUUnitConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUUnitConfig;
  /* Defining a pointer to the timer channel configuration parameters */
  P2CONST(Icu_TAUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUChannelUserRegConfig;
  /* Defining a pointer to point to the TAUD registers */
  P2VAR(volatile Icu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;

  /* Read channel configuration pointer */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];
  /* Get the spinlock */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  /* Disable the ISR */
  Icu_HW_Tau_StopCountMeasurement(LddChannel);
  /* Read timer channel configuration pointer */
  LpTAUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannel].pHWChannelUserRegConfig;                           /* PRQA S 0317 # JV-01 */
  /* Update the TAU configuration pointer to point to the current TAU */
  LpTAUUnitConfig = &Icu_GpTAUUnitConfig[LpTAUChannelUserRegConfig->ucTimerUnitIndex];
  /* Initialize pointer to the base address of the current timer unit */
  LpTAUDUnitUserReg = (P2VAR(volatile Icu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE)) LpTAUUnitConfig->pTAUnitUserCntlRegs; /* PRQA S 0310, 3305 # JV-01, JV-01 */
  #if (STD_ON == ICU_SET_MODE_API)
  /* Set bit flag channel running is ICU_FALSE */
  Icu_GpChannelRamData[LddChannel].ucChannelRunning = (uint8)ICU_FALSE;                                                 /* PRQA S 4304 # JV-01 */
  #endif
  /* Set the bit corresponding to the channel number in TAUDnTT register */
  LpTAUDUnitUserReg->usTAUDnTT = (LpChannelConfig->usChannelMaskValue);
  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  /* Read measurement mode */
  LenMeasurementMode = (Icu_MeasurementModeType)(LpChannelConfig->ucIcuMeasurementMode);                                /* PRQA S 4342 # JV-01 */
  if (ICU_MODE_SIGNAL_MEASUREMENT == LenMeasurementMode)
  {
    /* Initialize pointer to the base address of the current channel */
    LpTAUDChannelReg = (P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;       /* PRQA S 0316 # JV-01 */
    /* Clear overflow flag */
    LpTAUDChannelReg->ucTAUDnCSCm = ICU_TAUD_CSC_RESET_VAL;
    /* Read the current activation edge from RAM */
    LucIndex = Icu_GpChannelUserRegConfig[LddChannel].ucRamDataIndex;
    /* Initialize period measurement status as idle */
    Icu_GpSignalMeasurementData[LucIndex].ucPeriodMeasurementStatus = (uint8)ICU_PERIOD_IDLE;
  } /* else No action required */
  #endif /* End of #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */
  /* Release the spinlock */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

} /* End of Internal function Icu_HW_Taud_StopCountMeasurement */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Taud_GetEdgeNumbers
**
** Service ID           : None
**
** Description          : This service routine counts the number of edges for the given channel.
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
** Global Variables     : Icu_GpChannelConfig, Icu_GpEdgeCountData, Icu_GpChannelUserRegConfig.
**
** Functions invoked    : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION.
**
** Registers Used       : TAUDnCDRm, TAUDnCNTm.
**
** Reference ID         : ICU_DUD_ACT_041, ICU_DUD_ACT_041_CRT001, ICU_DUD_ACT_041_CRT002, ICU_DUD_ACT_041_GBL001
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Taud_GetEdgeNumbers(const Icu_ChannelType LddChannel)
{
  /* Defining a pointer to point to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  /* Defining a pointer to point to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  
  /* Pointer definition for Signal Measurement RAM data */
  P2VAR(volatile Icu_EdgeCountModeRamDatatype, AUTOMATIC, ICU_CONFIG_DATA) LpEdgeCountData;
  
  /* Defining a pointer to point to the TAUD registers */
  P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;                                        /* PRQA S 3678 # JV-01 */
  uint8 LucRamIndex;

  /* Read channel configuration pointer */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  /* Read timer channel configuration pointer */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannel];

  /* Read the channel ram index */
  LucRamIndex = LpChannelUserRegConfig->ucRamDataIndex;

  LpEdgeCountData = &Icu_GpEdgeCountData[LucRamIndex];

  /* Initialize pointer to the base address of the current channel */
  LpTAUDChannelReg = (P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;         /* PRQA S 0316 # JV-01 */
  /* Enter Critical Section */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION);

  /* Storing the Edge count value into RAM */
  LpEdgeCountData->ulIcuEdgeCount = (uint32)LpTAUDChannelReg->usTAUDnCDRm - LpTAUDChannelReg->usTAUDnCNTm;              /* PRQA S 0404, 3384 # JV-01, JV-01 */
  /* Exit Critical Section */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION);

} /* End of Internal function Icu_HW_Taud_GetEdgeNumbers */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_EDGE_COUNT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Taud_ResetEdgeCount
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
** Global Variables      : Icu_GpChannelConfig, Icu_GpChannelUserRegConfig, Icu_GpTAUUnitConfig.
**
** Functions invoked     : ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION
**
** Registers Used        : TAUDnTS, TAUDnTT, TAUDnCDRm, TAUDnTE.
**
** Reference ID          : ICU_DUD_ACT_040, ICU_DUD_ACT_040_CRT001
** Reference ID          : ICU_DUD_ACT_040_REG001, ICU_DUD_ACT_040_REG002, ICU_DUD_ACT_040_CRT002
** Reference ID          : ICU_DUD_ACT_040_REG003, ICU_DUD_ACT_040_REG004, ICU_DUD_ACT_040_REG005
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)

#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_PRIVATE_CODE) Icu_HW_Taud_ResetEdgeCount(const Icu_ChannelType LddChannel)
{
  /* Defining a pointer to point to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  /* Defining a pointer to point to the timer channel configuration parameters */
  P2CONST(Icu_TAUChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUChannelUserRegConfig;
  
  /* Defining a pointer to point to the TAUD registers */
  P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;

  /* Defining a pointer to the TAU configuration parameters */
  P2CONST(Icu_TAUUnitConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUUnitConfig;

  /* Defining a pointer to point to the TAUD user registers */
  P2VAR(volatile Icu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE) LpTAUDUnitUserReg;

  /* Update the channel configuration pointer to point to the current channel */
  LpChannelConfig = &Icu_GpChannelConfig[LddChannel];

  /* Update the Timer channel configuration pointer to point to the current channel */
  LpTAUChannelUserRegConfig = Icu_GpChannelUserRegConfig[LddChannel].pHWChannelUserRegConfig;                           /* PRQA S 0317 # JV-01 */

  /* Initialize pointer to the base address of the current channel */
  LpTAUDChannelReg = (P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;         /* PRQA S 0316 # JV-01 */

  /* Enter local critical section */
  ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION);

  /* Reset the Timer Counter */
  LpTAUDChannelReg->usTAUDnCDRm = ICU_TIMER_RESET_VAL;
  /* Update the TAU configuration pointer to point to the current TAU */
  LpTAUUnitConfig = &Icu_GpTAUUnitConfig[LpTAUChannelUserRegConfig->ucTimerUnitIndex];

  /* Enable and Disable Edge Counting */
  /* Initialize pointer to the base address of the current timer unit */
  LpTAUDUnitUserReg = (P2VAR(volatile Icu_TAUDUnitUserRegs, AUTOMATIC, REGSPACE)) LpTAUUnitConfig->pTAUnitUserCntlRegs; /* PRQA S 0310, 3305 # JV-01, JV-01 */

  if (((LpTAUDUnitUserReg->usTAUDnTE) & (LpChannelConfig->usChannelMaskValue))
                                                                             == (LpChannelConfig->usChannelMaskValue))
  {
    /* Set the bit corresponding to the channel number in TAUDnTT register */
    LpTAUDUnitUserReg->usTAUDnTT = (LpChannelConfig->usChannelMaskValue);

    /* Set the bit corresponding to the channel number in TAUDnTS register */
    LpTAUDUnitUserReg->usTAUDnTS = (LpChannelConfig->usChannelMaskValue);
  }
  else
  {
    /* Set the bit corresponding to the channel number in TAUDnTS register */
    LpTAUDUnitUserReg->usTAUDnTS = (LpChannelConfig->usChannelMaskValue);

    /* Set the bit corresponding to the channel number in TAUDnTT register */
    LpTAUDUnitUserReg->usTAUDnTT = (LpChannelConfig->usChannelMaskValue);
  }
  /* Exit local critical section */
  ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION);

} /* End of Internal function Icu_HW_Taud_ResetEdgeCount */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_EDGE_COUNT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Taud_TimerIsr
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
**                         Icu_GpChannelRamData, Icu_GpSignalMeasurementData.
**
** Functions invoked     : Icu_HW_Taud_ServiceSignalMeasurement,
**                         Icu_HW_Taud_ServiceTimestamp,
**                         ICU_ENTER_CRITICAL_SECTION, ICU_EXIT_CRITICAL_SECTION
**                         ICU_DEM_REPORT_ERROR, pIcuNotificationPointer.
**
** Registers Used        : TAUDnCDRm, TAUDnCSCm, TAUDnCSRm.
**
** Reference ID          : ICU_DUD_ACT_027,ICU_DUD_ACT_027_GBL001,ICU_DUD_ACT_027_GBL002
** Reference ID          : ICU_DUD_ACT_027_GBL003, ICU_DUD_ACT_027_GBL004, ICU_DUD_ACT_027_GBL005
** Reference ID          : ICU_DUD_ACT_027_GBL006, ICU_DUD_ACT_027_CRT001, ICU_DUD_ACT_027_CRT002
** Reference ID          : ICU_DUD_ACT_027_REG001, ICU_DUD_ACT_027_REG002
***********************************************************************************************************************/
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_CODE_FAST) Icu_HW_Taud_TimerIsr(const Icu_ChannelType LddChannel)
{
  /* Defining a pointer to point to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  /* Define a pointer to point to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  #endif

  #if ((ICU_TIMESTAMP_API == STD_ON) || (ICU_SIGNAL_MEASUREMENT_API == STD_ON))
  /* Defining a pointer to point to the TAUD registers */
  P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;
  #endif

  Icu_MeasurementModeType LenMeasurementMode;
  #if (ICU_TIMESTAMP_API == STD_ON)
  uint32 LulCapturedTimestampVal;
  #endif

  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  uint8 LucIndex;
  uint8 LucMeasureProperty;
  uint8 LucPeriodMeasurementStatus;

  /* Update the timer channel pointer to point to the current channel */
  LpChannelUserRegConfig = &Icu_GpChannelUserRegConfig[LddChannel];
  /* Read the edge count RAM index */
  LucIndex = LpChannelUserRegConfig->ucRamDataIndex;
  #endif /* End of #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */

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
      LpTAUDChannelReg = (P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;     /* PRQA S 0316 # JV-01 */
      /* Check counter overflow flag */
      if (ICU_TAUD_CSC_RESET_VAL == (LpTAUDChannelReg->ucTAUDnCSRm & ICU_TAUD_CSC_RESET_VAL))
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
        LpTAUDChannelReg->ucTAUDnCSCm = ICU_TAUD_CSC_RESET_VAL;
      } /* else No action required */
      /* Get the spinlock since ucChannelStatus, blResultComplete be updated by satellite core */
      ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Process Signal Measurement */
      Icu_HW_Taud_ServiceSignalMeasurement(LddChannel);

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
      #endif /* End of #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */
    }
    /* Check whether the channel is configured for Edge Detection */
    else if (ICU_MODE_SIGNAL_EDGE_DETECT == LenMeasurementMode)
    {
      /* Get the spinlock since ucChannelStatus be updated by satellite core */
      ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      /* Set channel input status as active */
      Icu_GpChannelRamData[LddChannel].ucChannelStatus = (uint8)ICU_ACTIVE;
      /* Release the spinlock */
      ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
      #if (ICU_NOTIFICATION_CONFIG == STD_ON)
      /* Check if notification is enabled */
      if ((uint8)ICU_TRUE == (Icu_GpChannelRamData[LddChannel].ucNotificationEnable))                                   /* PRQA S 0404, 3416, 4304 # JV-01, JV-01, JV-01 */
      {
        /* Check if the function pointer address is present for particular channel */
        if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
        {
          /* callback notification */
          LpChannelConfig->pIcuNotificationPointer();
        } /* else No action required */
      } /* else No action required */
      #endif /* End of (ICU_NOTIFICATION_CONFIG == STD_ON) */
    }
    /* Check whether the channel is configured for Timestamp */
    else if (ICU_MODE_TIMESTAMP == LenMeasurementMode)
    {
      #if (ICU_TIMESTAMP_API == STD_ON)
      if ((uint8)ICU_ACTIVE == Icu_GpChannelRamData[LddChannel].ucChannelStatus)                                        /* PRQA S 0404, 3416 # JV-01, JV-01 */
      {
        /* Initialize pointer to the base address of the current channel */
        LpTAUDChannelReg = (P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;   /* PRQA S 0316 # JV-01 */

        /* Calculate captured value */
        LulCapturedTimestampVal = (uint32)(LpTAUDChannelReg->usTAUDnCDRm + (uint32)ICU_ONE);                            /* PRQA S 3383 # JV-01 */

        /* Process Timestamp */
        Icu_HW_Taud_ServiceTimestamp(LddChannel, LulCapturedTimestampVal);
      } /* else No action required */
      #endif /* End of (ICU_TIMESTAMP_API == STD_ON) */
    }
    else /* if (ICU_MODE_EDGE_COUNTER == LenMeasurementMode) */
    {

      if ((uint8)ICU_ACTIVE == Icu_GpChannelRamData[LddChannel].ucChannelStatus)                                        /* PRQA S 0404, 3416 # JV-01, JV-01 */
      {
        #if (ICU_NOTIFICATION_CONFIG == STD_ON)
        /* Check if the function pointer address is present for particular channel */
        if (NULL_PTR != LpChannelConfig->pIcuNotificationPointer)
        {
          /* callback notification */
          LpChannelConfig->pIcuNotificationPointer();
        } /* else No action required */
        #endif /* End of (ICU_NOTIFICATION_CONFIG == STD_ON) */
      } /* else No action required */
    }
  }
} /* End of Internal function Icu_HW_Taud_TimerIsr */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name        : Icu_HW_Taud_ServiceSignalMeasurement
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
** Functions invoked    : None
**
** Registers Used       : TAUDnCDRm
**
** Reference ID         : ICU_DUD_ACT_028
** Reference ID         : ICU_DUD_ACT_028_GBL001, ICU_DUD_ACT_028_GBL002,  
***********************************************************************************************************************/
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_CODE_FAST) Icu_HW_Taud_ServiceSignalMeasurement(const Icu_ChannelType LddChannel)                        /* PRQA S 1505 # JV-01 */
{
  /* Defining a pointer to point to the channel configuration parameters */
  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelConfig;

  /* Define a pointer to point to the timer channel configuration parameters */
  P2CONST(Icu_ChannelUserRegConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpChannelUserRegConfig;
  
  /* Defining a pointer to point to the TAUD registers */
  P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE) LpTAUDChannelReg;                                        /* PRQA S 3678 # JV-01 */

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
  LpTAUDChannelReg = (P2VAR(volatile Icu_TAUDChannelUserRegs, AUTOMATIC, REGSPACE)) LpChannelConfig->pCntlRegs;         /* PRQA S 0316 # JV-01 */

  if ((ICU_HIGH_TIME_MASK == (uint8)(LucMeasureProperty & ICU_HIGH_LOW_TIME_MASK)) ||
                                           (ICU_LOW_TIME_MASK == (uint8)(LucMeasureProperty & ICU_HIGH_LOW_TIME_MASK)))
  /* Calculate Active time */
  {
    Icu_GpSignalMeasurementData[LucRamIndex].ulSignalActiveTime =                                                       /* PRQA S 0404 # JV-01 */
                                                             (uint32)(LpTAUDChannelReg->usTAUDnCDRm + (uint32)ICU_ONE); /* PRQA S 3383 # JV-01 */
  }
  else /* (LucMeasureProperty == (ICU_PERIOD_TIME)) */
  {
    Icu_GpSignalMeasurementData[LucRamIndex].ulPrevSignalActiveTime =                                                   /* PRQA S 0404 # JV-01 */
                                                           Icu_GpSignalMeasurementData[LucRamIndex].ulSignalActiveTime;
    /* Calculate Period time */
    Icu_GpSignalMeasurementData[LucRamIndex].ulSignalPeriodTime =                                                       /* PRQA S 0404 # JV-01 */
                                                             (uint32)(LpTAUDChannelReg->usTAUDnCDRm + (uint32)ICU_ONE); /* PRQA S 3383 # JV-01 */
  }

} /* End of Internal function Icu_HW_Taud_ServiceSignalMeasurement */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_SIGNAL_MEASUREMENT_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Taud_ServiceTimestamp
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
** Reference ID          : ICU_DUD_ACT_029, ICU_DUD_ACT_029_GBL001, ICU_DUD_ACT_029_GBL002
***********************************************************************************************************************/
#if (ICU_TIMESTAMP_API == STD_ON)
#define ICU_START_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, ICU_CODE_FAST)
                   Icu_HW_Taud_ServiceTimestamp(const Icu_ChannelType LddChannel, const uint32 LulCapturedTimestampVal) /* PRQA S 1505 # JV-01 */
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
        Icu_HW_Taud_StopCountMeasurement(LddChannel);
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
    } /* else No action required */
    #endif /* if (ICU_NOTIFICATION_CONFIG == STD_ON) */
  } /* else No action required */
} /* End of Internal function Icu_HW_Taud_ServiceTimestamp */

#define ICU_STOP_SEC_CODE_FAST
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_TIMESTAMP_API == STD_ON) */
/***********************************************************************************************************************
** Function Name         : Icu_HW_Taud_GetTAUInCountValue
**
** Service ID            : NA
**
** Description           : This API service returns the counter value of TAU
**                         timer.
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
** Reference ID          : ICU_DUD_ACT_034
***********************************************************************************************************************/
#if (ICU_GET_TAU_COUNT_VALUE_API == STD_ON)
#define ICU_START_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(Icu_CounterValueType, ICU_PRIVATE_CODE) Icu_HW_Taud_GetTAUInCountValue(const Icu_ChannelType LddChannel)
{
  /* Defining a pointer to the channel configuration parameters */
  P2CONST(Icu_TAUChannelConfigType, AUTOMATIC, ICU_CONFIG_DATA) LpTAUChannelConfig;
  
  /* Local variable to store the return level value  */
  Icu_CounterValueType LddTAUInCounterValue;

  /* Initialize the return value */
  LddTAUInCounterValue = ICU_TAU_CNT_INIT_VAL;

  LpTAUChannelConfig = Icu_GpChannelConfig[LddChannel].pHWIPChannelConfig;                                              /* PRQA S 0317 # JV-01 */
  /* Get the TAUIn counter value of particular channel */
  if (NULL_PTR != LpTAUChannelConfig->pCNTAddress)
  {
    LddTAUInCounterValue = *(LpTAUChannelConfig->pCNTAddress);
  } /* else No action required */

  LddTAUInCounterValue = (LddTAUInCounterValue & ICU_TAUD_CNT_MASK_VAL);

  /* Return the TAUIn counter value of particular channel */
  return (LddTAUInCounterValue);
} /* End of API Icu_HW_Taud_GetTAUInCountValue */

#define ICU_STOP_SEC_PRIVATE_CODE
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (ICU_GET_TAU_COUNT_VALUE_API == STD_ON) */

#endif /* End of (ICU_TAUD_UNIT_USED == STD_ON) */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
