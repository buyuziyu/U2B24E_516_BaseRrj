/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mem_59_Renesas_FPSYS_LLDriver.c                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains FCU related API implementations                                                                 */
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
/*              Devices:        U2Bx, U2Cx, U2Bx-E                                                                    */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.1.0:  30/06/2025   : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax release
 * 1.0.3:  25/04/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 *                        As part of ARDAACL-51989, support timeout for Mem Driver
 * 1.0.2:  31/03/2025   : Update name of CF and DF ECC register since Mem_59_Renesas_CFECCRegType and 
 *                        Mem_59_Renesas_DFECCRegType updated, Mem_59_Renesas_FPSYS_PerformReadCFCheckECC change 
 *                        read/write to 32 bit for ulCFSSTCLR, ulCFSERSTR
 *                        Update support new bank E, F, G, H for Mem_59_Renesas_FPSYS_SuspendPreCheck
 *                        Update sequence for Mem_59_Renesas_FPSYS_SuspendPreCheck
 * 1.0.1:  28/02/2025   : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 *                        As part of ARDAACL-51139, Remove redundant checkign ECC in 
 *                        Mem_59_Renesas_FPSYS_PreFcuInitCheck.
 *                        As part of ARDAACL-51152, support read option from back side in 
 *                        Mem_59_Renesas_FPSYS_ReadOptionByteService.
 *                        As part of ARDAACL-51748, update sequence FCU reset in Mem_59_Renesas_FPSYS_FcuReset and
 *                        remove precondition.
 *                        As part of ARDAACL-51139, update condition check for internal function 
 *                        Mem_59_Renesas_FPSYS_SuspendPreCheck.
 * 0.0.2:  31/10/2024   : As part of ARDAACJ-621, support downgrade from version AR23-11 to AR22-11.
 *                        Support commonize
 * 0.0.1:  30/08/2024   : Initial Version
 */

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Mem_59_Renesas_FPSYS_LLDriver.h"
/* Included for prototypes for internal functions of Flash Wrapper Component */
#include "Mem_59_Renesas_FPSYS_Control.h"
/* Included for RAM variable declarations */
#include "Mem_59_Renesas_Ram.h"
#if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
#include "r_rfd_df.h"
#include "r_rfd_cf.h"
/* Included for device specific functions */
#include "Mem_59_Renesas_device_dep.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MEM_59_RENESAS_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION_VALUE
#define MEM_59_RENESAS_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION_VALUE
#define MEM_59_RENESAS_LLDRIVER_C_AR_RELEASE_REVISION_VERSION MEM_59_RENESAS_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MEM_59_RENESAS_LLDRIVER_C_SW_MAJOR_VERSION            MEM_59_RENESAS_SW_MAJOR_VERSION_VALUE
#define MEM_59_RENESAS_LLDRIVER_C_SW_MINOR_VERSION            MEM_59_RENESAS_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (MEM_59_RENESAS_LLDRIVER_AR_RELEASE_MAJOR_VERSION != MEM_59_RENESAS_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "Mem_59_Renesas_FPSYS_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (MEM_59_RENESAS_LLDRIVER_AR_RELEASE_MINOR_VERSION != MEM_59_RENESAS_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "Mem_59_Renesas_FPSYS_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (MEM_59_RENESAS_LLDRIVER_AR_RELEASE_REVISION_VERSION != MEM_59_RENESAS_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "Mem_59_Renesas_FPSYS_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (MEM_59_RENESAS_LLDRIVER_SW_MAJOR_VERSION != MEM_59_RENESAS_LLDRIVER_C_SW_MAJOR_VERSION)
#error "Mem_59_Renesas_FPSYS_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (MEM_59_RENESAS_LLDRIVER_SW_MINOR_VERSION != MEM_59_RENESAS_LLDRIVER_C_SW_MINOR_VERSION)
#error "Mem_59_Renesas_FPSYS_LLDriver.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : MISRA C:2012 Rule-11.4, CERTCCM INT36, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : MISRA C:2012 Rule-11.3, CERTCCM EXP39, EXP11, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588,   */
/*                       CWE-465, CWE-569, CWE-737                                                                    */
/* JV-01 Justification : For accessing 8-bit and 16-bit PNOT and JPNOT register respectively, the 32-bit pointer is   */
/*                       typecasted.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:0311)    : Dangerous pointer cast results in loss of const qualification.                               */
/* Rule                : MISRA C:2012 Rule-11.8, CERTCCM EXP05                                                        */
/* JV-01 Justification : This is to achieve throughput in the code.                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:0312)    : Dangerous pointer cast results in loss of volatile qualification.                            */
/* Rule                : MISRA C:2012 Rule-11.8, CERTCCM EXP32, CWE Rule CWE-737                                      */
/* JV-01 Justification : According to the coding guide, all global variables must have volatile attribute, but        */
/*                       volatile must be removed when return these variables from APIs according to the AUTOSAR      */
/*                       specification.                                                                               */
/*       Verification  : Since these are normal memory objects, any problem doesn't occurs.                           */
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
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
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
/* Message (3:3206)    : The parameter '%s' is not used in this function.                                             */
/* Rule                : MISRA C:2012 Rule-2.7, CERTCCM MSC07, MSC13, CWE Rule CWE-398, CWE-563, CWE-569              */
/* JV-01 Justification : This is done as per implementation requirement                                               */
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
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there. (Other uses of  */
/*                       the macro may not necessarily be suitable for replacement.)                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3473)    : This usage of a function-like setter macro looks like it could be replaced by a similar      */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message is an improvement to refactor function-like macros to be implemented as true C  */
/*                       functions. It not affect to driver operation and can be accepted                             */
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
/* Message (5:4432)    : An expression of 'essentially signed' type (%1s) is being converted to enum type,            */
/*                       '%2s' on assignment.                                                                         */
/* Rule                : CERTCCM INT02, MISRA C:2012 Rule-10.3, CWE Rule CWE-681, CWE-136, CWE-192                    */
/* JV-01 Justification : Code review confirmed that values after calculation is within an enumerated type.            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:4522)    : An expression of 'essentially enum' type (%1s) is being used as the %2s operand              */
/*                       of this bitwise operator (%3s).                                                              */
/* Rule                : MISRA C:2012 Rule-10.1, CWE Rule CWE-136                                                     */
/* JV-01 Justification : Code review confirmed that values within an enumerated type are cast, so no problem.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3205)    : The identifier '%s' is not used and could be removed.                                        */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.3                                                  */
/* JV-01 Justification : This identifier is used by other file.                                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_FPSYS_FcuSwitchMode
**
** Service ID                : NA
**
** Description               : This function Switch FCU mode to Programming/User
**                             mode and checks if the Flash sequencer operation
**                             mode switch is performed correctly
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Non Re-entrant
**
** Input Parameters          : LddMode
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables Used     : Mem_59_Renesas_GusFACI
**
** Function(s) invoked       : R_RFD_CheckPEMode, R_RFD_GetFaciSequenceReady
**                             R_RFD_ShiftToPEMode,R_RFD_ShiftToReadMode
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_028, MEM_DUD_ACT_028_GBL001, MEM_DUD_ACT_028_GBL002, MEM_DUD_ACT_028_GBL003
** Reference ID              : MEM_DUD_ACT_028_GBL004, MEM_DUD_ACT_028_GBL005, MEM_DUD_ACT_028_GBL006,
** Reference ID              : MEM_DUD_ACT_028_GBL007
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuSwitchMode(
                                                                           CONST(T_en_FACIMode, MEM_APPL_CONST) LenMode)
{
  Mem_59_Renesas_FcuStatusType LenStatus;
  volatile uint32 LulLoopCount;
  T_u4_RFDReturn LulRFDStatus;

  LenStatus = MEM_59_RENESAS_FCU_ERR_INTERNAL;

  /* Check if the mode is already set. If yes, setting it again would toggle the mode.So, don't set it again */
  LulRFDStatus = R_RFD_CheckPEMode(Mem_59_Renesas_GusFACI, LenMode);
  if (R_RFD_OK != LulRFDStatus)
  {
    LulRFDStatus = R_RFD_GetFaciSequenceReady(Mem_59_Renesas_GusFACI);
    if (R_RFD_STS_READY == LulRFDStatus)
    {
      if (R_RFD_MODE_READ != LenMode)
      {
        if (R_RFD_MODE_CFPE == LenMode)
        {
          /* Software unprotection of code flash P/E mode entry */
          MEM_59_RENESAS_WRITE8(R_RFD_REG_ADDRESS_FLMDCNT, MEM_59_RENESAS_SFWE_UNPROTECT);                              /* PRQA S 0303, 3469 # JV-01, JV-01 */

          LulRFDStatus = R_RFD_ShiftToPEMode(Mem_59_Renesas_GusFACI, LenMode);
        }
        else
        {
          /* Software protection of code flash P/E mode entry */
          MEM_59_RENESAS_WRITE8(R_RFD_REG_ADDRESS_FLMDCNT, MEM_59_RENESAS_SFWE_PROTECT);                                /* PRQA S 0303, 3469 # JV-01, JV-01 */

          LulRFDStatus = R_RFD_ShiftToPEMode(Mem_59_Renesas_GusFACI, LenMode);
        }
      }
      else /* Switch User mode */
      {
        /* Sequencer is stopped before this code check cmd lock status */
        LulRFDStatus = R_RFD_ShiftToReadMode(Mem_59_Renesas_GusFACI);
      }

      LulLoopCount = (uint32)(MEM_59_RENESAS_FCU_MODE_CHECKCOUNT + MEM_59_RENESAS_SHIFT_PE_MODE_LOOP_COUNT);

      /* Check if value of the FENTRYD bit is set as requested */
      /* We need a dummy read as the mode is not changed immediately on some devices */
      /* Start : MEM_59_RENESAS_UT_002*/
      if (R_RFD_STS_BUSY == LulRFDStatus)
      {
        do
        {
          LulLoopCount--;                                                                                               /* PRQA S 3384, 3387 # JV-01, JV-01 */
          LulRFDStatus = R_RFD_CheckPEMode(Mem_59_Renesas_GusFACI, LenMode);
        } while ((R_RFD_STS_BUSY == LulRFDStatus) && (MEM_59_RENESAS_FCU_ZERO < LulLoopCount));                         /* PRQA S 3415, 3416 # JV-01, JV-01 */
        /* End : MEM_59_RENESAS_UT_002*/
        
        /* Start : MEM_59_RENESAS_UT_002*/
        /* Check if mode switch is successful or time out occurs */
        if (R_RFD_OK == LulRFDStatus)
        {
          /* Mode switch is successful */
          LenStatus = MEM_59_RENESAS_FCU_OK;
        }
        else
        {
          /* Error occurs due to internal error */
          LenStatus = MEM_59_RENESAS_FCU_ERR_INTERNAL;
          (void)R_RFD_ShiftToReadMode(Mem_59_Renesas_GusFACI);
        }
        /* End : MEM_59_RENESAS_UT_002*/
      }
      else if (R_RFD_OK == LulRFDStatus)                                                                                /* PRQA S 2004 # JV-01 */
      {
        /* Mode switch is successful */
        LenStatus = MEM_59_RENESAS_FCU_OK;
      } /* else No action required */
    } /* else No action required */
  }
  else
  {
    /* The intended mode is already set */
    LenStatus = MEM_59_RENESAS_FCU_OK;
  }

  return (LenStatus);
} /* End of function Mem_59_Renesas_FPSYS_FcuSwitchMode */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_FPSYS_FcuReset
**
** Service ID                : NA
**
** Description               : This function initialized FCU
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Non Re-entrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables Used     : Mem_59_Renesas_GusFACI
**
** Function(s) invoked       : Mem_59_Renesas_FPSYS_FcuSwitchMode,R_RFD_ForcedStopAndErrorClear,
**                             R_RFD_StatusClear, R_RFD_CheckPEMode
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_029, MEM_DUD_ACT_029_GBL001, MEM_DUD_ACT_029_GBL002, MEM_DUD_ACT_029_GBL003
** Reference ID              : MEM_DUD_ACT_029_GBL004
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuReset(void)
{
  /* Declaration for return of Switch mode */
  Mem_59_Renesas_FcuStatusType LenStatus;
  /* Switching to P/E Mode */
  T_u4_RFDReturn LulRFDStatus;
  Mem_59_Renesas_FcuStatusType LenTmpStatus;

  /* Initial return value for Fcu Reset */
  LenStatus = MEM_59_RENESAS_FCU_OK;
  
  LulRFDStatus = R_RFD_CheckPEMode(Mem_59_Renesas_GusFACI, R_RFD_MODE_CFPE);

  if (R_RFD_OK == LulRFDStatus)
  {
    /* In case code flash */
    /* Wait finished Forced Stop command */
    LulRFDStatus = R_RFD_ForcedStopAndErrorClear(Mem_59_Renesas_GusFACI);
    if (R_RFD_OK != LulRFDStatus)
    {
      /* Issues Status Clear command */
      (void)R_RFD_StatusClear(Mem_59_Renesas_GusFACI);
      LenStatus = MEM_59_RENESAS_FCU_ERR_INTERNAL;
    } /* else No action required */

    /* Switch to Reading Mode to be able to change P/E in Data Flash */
    /* Switching to Read Mode */
    LenTmpStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_READ);
  }
  else
  {
    /* Incase data flash or read mode */
    LenStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_DFPE);

    if (MEM_59_RENESAS_FCU_OK == LenStatus)
    {
      /* Wait finished Forced Stop command */
      LulRFDStatus = R_RFD_ForcedStopAndErrorClear(Mem_59_Renesas_GusFACI);
      if (R_RFD_OK != LulRFDStatus)
      {
        /* Issues Status Clear command */
        (void)R_RFD_StatusClear(Mem_59_Renesas_GusFACI);
        LenStatus = MEM_59_RENESAS_FCU_ERR_INTERNAL;
      } /* else No action required */
    } /* else No action required */

    /* Switching to Read Mode */
    LenTmpStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_READ);
  }

  if (MEM_59_RENESAS_FCU_OK != LenTmpStatus)
  {
    LenStatus = LenTmpStatus;
  }
  else
  {
    LenStatus = LenStatus;
  }
  return (LenStatus);
} /* End of function Mem_59_Renesas_FPSYS_FcuReset */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/**********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_FcuPreCheck
**
** Service ID               : NA
**
** Description              : Function to Check if Erase Job shall be initiated
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : LenStatus
**
** Preconditions            : None
**
** Global Variables Used    : None
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_FcuCheckSequencerStatus
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_030
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuPreCheck(void)                             /* PRQA S 1505 # JV-01 */
{
  Mem_59_Renesas_FcuStatusType LenStatus;

  LenStatus = Mem_59_Renesas_FPSYS_FcuCheckSequencerStatus();
  if (LenStatus != MEM_59_RENESAS_FCU_OK)
  {
    /* Setting the status as Erase/Write/Blank-Check error as error bits are set and
      flash sequencer is in command lock state.*/
    LenStatus = MEM_59_RENESAS_FCU_ERR_HW_FAILED;
  }
  else
  {
    LenStatus = MEM_59_RENESAS_FCU_OK;
  }

  return (LenStatus);
}
/* End of function Mem_59_Renesas_FPSYS_FcuPreCheck */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_FcuCheckJobStatus
**
** Service ID               : NA
**
** Description              : This function is called from Mem_59_Renesas_MainFunction,
**                            when the command is Erase Operation/ Write
**                            operation.This function checks if the FACI is
**                            ready to accept a new command and checks if any
**                            error bits are set after completion of a job.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : LenStatus
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GusFACI
**
** Function(s) invoked      : R_RFD_GetFaciSequenceReady, R_RFD_GetFaciStatus
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_032, MEM_DUD_ACT_032_GBL001, MEM_DUD_ACT_032_GBL002
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuCheckJobStatus(void)
{
  /* Return variable to store DF Status*/
  Mem_59_Renesas_FcuStatusType LenStatus;
  T_u4_RFDReturn LulRFDStatus;

  LenStatus = MEM_59_RENESAS_FCU_BUSY;
  LulRFDStatus = R_RFD_GetFaciSequenceReady(Mem_59_Renesas_GusFACI);
  /* Check if the Job is completed */
  if (R_RFD_STS_READY == LulRFDStatus)
  {
    LulRFDStatus = R_RFD_GetFaciStatus(Mem_59_Renesas_GusFACI);
    /* Success */
    if (MEM_59_RENESAS_FCU_ZERO == (LulRFDStatus & MEM_59_RENESAS_RFD_ERROR_BIT))
    {
      LenStatus = MEM_59_RENESAS_FCU_OK;
    }
    else
    {
      LenStatus = MEM_59_RENESAS_FCU_ERR_HW_FAILED;
    }
  } /* else No action required */
  /* FCU is busy */

  return (LenStatus);
} /* End of function Mem_59_Renesas_FPSYS_FcuCheckJobStatus */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_FcuCheckBCJobStatus
**
** Service ID               : NA
**
** Description              : This function is called from Mem_59_Renesas_MainFunction,
**                            when the command is Blank Check operation.
**                            This function checks if the FACI is ready to
**                            accept a new command.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : LenStatus
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GstVar.enFlashStatus(W),Mem_59_Renesas_GusFACI(R)
**
** Function(s) invoked      : R_RFD_GetFaciSequenceReady,R_RFD_GetFaciStatus,
**                            R_RFD_GetBlankCheckResult
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_033, MEM_DUD_ACT_033_GBL001, MEM_DUD_ACT_033_GBL002, MEM_DUD_ACT_033_GBL003
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuCheckBCJobStatus(void)                     /* PRQA S 1503 # JV-01 */
{
  /* Return variable to store DF Status*/
  Mem_59_Renesas_FcuStatusType LenStatus;
  T_u4_RFDReturn LulRFDStatus;
  T_u4_RfdAddress LulNotBlankAddress;
  LenStatus = MEM_59_RENESAS_FCU_BUSY;

  /* Get the register value */
  LulRFDStatus = R_RFD_GetFaciSequenceReady(Mem_59_Renesas_GusFACI);
  /* Check if the Job is completed */
  if (R_RFD_STS_READY == LulRFDStatus)
  {
    /* Get the register value */
    LulRFDStatus = R_RFD_GetFaciStatus(Mem_59_Renesas_GusFACI);
    /* Success */
    if (MEM_59_RENESAS_FCU_ZERO == (LulRFDStatus & MEM_59_RENESAS_RFD_ERROR_BIT))
    {
      LulRFDStatus = R_RFD_GetBlankCheckResult(Mem_59_Renesas_GusFACI, &LulNotBlankAddress);
      if (R_RFD_OK == LulRFDStatus)
      {
        LenStatus = MEM_59_RENESAS_FCU_OK;
      }
      else if (R_RFD_STS_NOTBLANK == LulRFDStatus)
      {
        LenStatus = MEM_59_RENESAS_FCU_BC_INCONSISTENT;
      }
      else
      {
        LenStatus = MEM_59_RENESAS_FCU_ERR_HW_FAILED;
      }
    }
    /* Error */
    else
    {
      LenStatus = MEM_59_RENESAS_FCU_ERR_HW_FAILED;
    }
  } /* else No action required */
  /* FCU is busy */

  return (LenStatus);
} /* End of function Mem_59_Renesas_FPSYS_FcuCheckBCJobStatus */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_FcuResetErrorBits
**
** Service ID               : NA
**
** Description              : This function clears the error bits
**                           (erasure error or program error) by issuing Status
**                            Clear Command or Forced stop command
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non-Reentrant
**
** Input Parameters         : LulInstanceId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : LenStatus
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GusFACI, Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GstVar
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_FcuSwitchMode, R_RFD_GetFaciSequenceReady,
**                            Mem_59_Renesas_FPSYS_FcuReset, R_RFD_GetFaciStatus, R_RFD_StatusClear
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_036, MEM_DUD_ACT_036_GBL001, MEM_DUD_ACT_036_GBL002, MEM_DUD_ACT_036_GBL003
** Reference ID             : MEM_DUD_ACT_036_GBL004, MEM_DUD_ACT_036_GBL005
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuResetErrorBits(
                                                                    Mem_59_Renesas_InstanceIdType LulInstanceId)        /* PRQA S 3206 # JV-01 */
{
  /* Variable to store return variable */
  Mem_59_Renesas_FcuStatusType LenStatus;
  Mem_59_Renesas_FcuStatusType LenTmpStatus;
  T_u4_RFDReturn LulRFDStatus;
  
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  Mem_59_Renesas_FlashType LenFlashType;
  #endif
  LenStatus = MEM_59_RENESAS_FCU_ERR_INTERNAL;                                                                          /* PRQA S 2982 # JV-01 */
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  /* Pointer to sector batch */

  /* Get pointer Sector Batch*/
  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);
  /* Determine the current type of Flash */
  LenFlashType = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].enFlashType;
  #endif
  LulRFDStatus = R_RFD_GetFaciSequenceReady(Mem_59_Renesas_GusFACI);
  /* Check if the Job is completed */
  if (R_RFD_STS_READY == LulRFDStatus)
  {
    LulRFDStatus = R_RFD_GetFaciStatus(Mem_59_Renesas_GusFACI);
    if (R_RFD_ERR_FHVE_PROTECT != LulRFDStatus)
    {
      /* Occuer Other FHVE error */
      #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enable relevant DF and FACI to exit this critical section */
      MEM_59_RENESAS_ENTER_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
      #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */

      #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
      if (MEM_59_RENESAS_CODE_FLASH == LenFlashType)
      #endif
      #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
      {
        /* Switching to P/E Mode */
        LenStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_CFPE);
      }
      #endif
      #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
      else
      #endif
      #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
      {
        /* Switching to P/E Mode */
        LenStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_DFPE);
      }
      #endif

      if (MEM_59_RENESAS_FCU_OK == LenStatus)
      {
        /* Issue Clear Status command */
        (void)R_RFD_StatusClear(Mem_59_Renesas_GusFACI);
      } /* else No action required */
      #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enable relevant DF and FACI to exit this critical section */
      MEM_59_RENESAS_EXIT_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
      #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */

      /* Switching to USER Mode */
      LenTmpStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_READ);
      if (MEM_59_RENESAS_FCU_OK != LenTmpStatus)
      {
        LenStatus = LenTmpStatus;
      } /* else No action required */
    }
    else
    {
      /* Occur other FHVE error */
      #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enable relevant DF and FACI to exit this critical section */
      MEM_59_RENESAS_ENTER_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
      #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */

      /* Occur FHVE error(need forced stop for release command lock) */
      LenStatus = Mem_59_Renesas_FPSYS_FcuReset();

      #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
      /* Enable relevant DF and FACI to exit this critical section */
      MEM_59_RENESAS_EXIT_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
      #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */
    }
  }
  else
  {
    /* Occur other FHVE error */
    #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant DF and FACI to exit this critical section */
    MEM_59_RENESAS_ENTER_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
    #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */

    /* Flash sequence is timeout (Fail-Safe) */
    LenStatus = Mem_59_Renesas_FPSYS_FcuReset();

    #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
    /* Enable relevant DF and FACI to exit this critical section */
    MEM_59_RENESAS_EXIT_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
    #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */
  }

  return (LenStatus);
} /* End of function Mem_59_Renesas_FPSYS_FcuResetErrorBits */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_FPSYS_FcuCheckSequencerStatus
**
** Service ID                : NA
**
** Description               : This function checks the FRDY bit and if
**                             there is a cmd lock based on timeout values.

** Sync/Async                : Synchronous
**
** Re-entrancy               : Non Re-entrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables Used     : Mem_59_Renesas_GusFACI
**
** Function(s) invoked       : R_RFD_GetFaciSequenceReady, R_RFD_GetFaciStatus
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_037, MEM_DUD_ACT_037_GBL001, MEM_DUD_ACT_037_GBL002
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuCheckSequencerStatus(void)                 /* PRQA S 1505 # JV-01 */
{
  Mem_59_Renesas_FcuStatusType LenStatus;
  T_u4_RFDReturn LulRFDStatus;

  LenStatus = MEM_59_RENESAS_FCU_ERR_INTERNAL;

  /* Checking against error bits */
  LulRFDStatus = R_RFD_GetFaciSequenceReady(Mem_59_Renesas_GusFACI);
  if (R_RFD_STS_READY == LulRFDStatus)
  {
    LulRFDStatus = R_RFD_GetFaciStatus(Mem_59_Renesas_GusFACI);
    if (MEM_59_RENESAS_FCU_ZERO == (LulRFDStatus & MEM_59_RENESAS_RFD_ERROR_BIT))
    {
      LenStatus = MEM_59_RENESAS_FCU_OK;
    } /* else No action required */
  } /* else No action required */

  return (LenStatus);
} /* End of function Mem_59_Renesas_FPSYS_FcuCheckSequencerStatus */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_FPSYS_GetFACINumber
**
** Service ID                : NA
**
** Description               : Invoke The function to acquires the FACI number
**                             of the data flash memory address (RFD API) with
**                             LulStartAddr as an argument, and set FACI number
**                             to Mem_59_Renesas_GusFACI.
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : Non Re-entrant
**
** Input Parameters          : LulStartAddr, LulInstanceId
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Mem_59_Renesas_GusFACI, Mem_59_Renesas_GpInsConfig
**
** Function(s) invoked       : R_RFD_DFAddressToFaciNumber, R_RFD_CFAddressToFaciNumber
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_039, MEM_DUD_ACT_039_GBL001, MEM_DUD_ACT_039_GBL002, MEM_DUD_ACT_039_GBL003
** Reference ID              : MEM_DUD_ACT_039_GBL004, MEM_DUD_ACT_039_GBL005, MEM_DUD_ACT_039_GBL006
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_GetFACINumber(const uint32 LulStartAddr, 
                                                                      const Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  /* Type of Flash */
  Mem_59_Renesas_FlashType LenFlashType;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;

  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);

  LenFlashType = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].enFlashType;
  #else
  (void)LulInstanceId;
  #endif

  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  if (MEM_59_RENESAS_CODE_FLASH == LenFlashType)
  #endif
  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
  {
    /* Acquire FACI number */
    Mem_59_Renesas_GusFACI = R_RFD_CFAddressToFaciNumber(LulStartAddr);
  }
  #endif
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  else if (MEM_59_RENESAS_DATA_FLASH == LenFlashType)                                                                   /* PRQA S 2004 # JV-01 */
  #endif
  #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
  {
    /* Acquire FACI number */
    Mem_59_Renesas_GusFACI = R_RFD_DFAddressToFaciNumber(LulStartAddr);
  }/* else No action required */
  #endif
} /* End of function Mem_59_Renesas_FPSYS_GetFACINumber */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_FPSYS_PreFcuInitCheck
**
** Service ID                : NA
**
** Description               : This function checks there are no ECC errors
**                             during MEM initialisation
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Non Re-entrant
**
** Input Parameters          : None
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : LenStatus
**
** Preconditions             : None
**
** Global Variables used     : Mem_59_Renesas_GpConfigPtr
**
** Function(s) invoked       : None
**
** Registers Used            : CFCECCCTL, DFECCCTL, DFTSTCTL
**
** Reference ID              : MEM_DUD_ACT_040, MEM_DUD_ACT_040_GBL001, MEM_DUD_ACT_040_GBL002, MEM_DUD_ACT_040_GBL003
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_PreFcuInitCheck(void)
{
  /* local variable to hold the FCU Status */
  Mem_59_Renesas_FcuStatusType LenStatus;
  #if (MEM_59_RENESAS_ECC_CHECK == STD_ON)
  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
  Mem_59_Renesas_FcuStatusType LenCFStatus;
  #endif
  #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
  volatile Mem_59_Renesas_DFECCRegType* LpDFECCRegPtr;                                                                  /* PRQA S 3678 # JV-01 */
  Mem_59_Renesas_FcuStatusType LenDFStatus;
  #endif

  #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
  LpDFECCRegPtr = Mem_59_Renesas_GpConfigPtr->pDFECCRegPtr;
  #endif
  
  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
  LenCFStatus = MEM_59_RENESAS_FCU_OK;
  #endif
  #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
  LenDFStatus = MEM_59_RENESAS_FCU_OK;
  #endif
  #endif
  /* Initialise the local variable to hold the FCU Status */
  LenStatus = MEM_59_RENESAS_FCU_OK;                                                                                    /* PRQA S 2982 # JV-01 */
  
  #if (MEM_59_RENESAS_ECC_CHECK == STD_ON)
  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
  if ((MEM_59_RENESAS_CFCECCCTL_RESET_VAL != (*((volatile uint32 *)(Mem_59_Renesas_GpConfigPtr->pCFCECCCTLRegPtr)))))
  {
    LenCFStatus = MEM_59_RENESAS_FCU_ERR_INTERNAL;
  } /* else No action required */
  #endif

  #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
  if ((MEM_59_RENESAS_DFECCCTL_RESET_VAL != (*((volatile uint32 *)(&LpDFECCRegPtr->ulDFECCCTL)))) ||
                            (MEM_59_RENESAS_DFTSTCTL_RESET_VAL != (*((volatile uint32 *)(&LpDFECCRegPtr->ulDFTSTCTL)))))
  {
    LenDFStatus = MEM_59_RENESAS_FCU_ERR_INTERNAL;
  } /* else No action required */
  #endif

  #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
  if (MEM_59_RENESAS_FCU_OK != LenDFStatus)
  {
    LenStatus = LenDFStatus;
  }
  #endif

  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
  if (MEM_59_RENESAS_FCU_OK != LenCFStatus)
  {
    LenStatus = LenCFStatus;
  }
  #endif
  #else  /* #if ( MEM_59_RENESAS_ECC_CHECK == STD_ON ) */
  LenStatus = MEM_59_RENESAS_FCU_OK;
  #endif /* #if ( MEM_59_RENESAS_ECC_CHECK == STD_ON ) */
  return (LenStatus);
} /* End of function Mem_59_Renesas_FPSYS_PreFcuInitCheck */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_InitFcu
**
** Service ID               : NA
**
** Description              : This function initialises FCU Global Variable
**                            Structure and prepares the environment
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : LenStatus
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GusFACI
**
** Function(s) invoked      : R_RFD_Init, Mem_59_Renesas_FPSYS_FcuReset
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_041, MEM_DUD_ACT_041_GBL001, MEM_DUD_ACT_041_GBL002, MEM_DUD_ACT_041_GBL003
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_InitFcu(void)
{
  Mem_59_Renesas_FcuStatusType LenStatus;
  T_u4_RFDReturn LulRFDStatus;
  uint16 LucLoop;
  volatile uint16 LusFacinumber;
  /* Initial local variable */
  LenStatus   = MEM_59_RENESAS_FCU_OK;                                                                                  /* PRQA S 2982 # JV-01 */

  /* Initialized RFD */
  LulRFDStatus = R_RFD_Init(MEM_59_RENESAS_FACI_FREQENCY);

  if (R_RFD_OK == LulRFDStatus)
  {
    /* Initialized FCU */
    LusFacinumber = Mem_59_Renesas_GusFACI;
    LenStatus = MEM_59_RENESAS_FCU_OK;
    for (LucLoop = MEM_59_RENESAS_FACI_0; 
                            (LucLoop < (uint16)R_RFD_NUMBER_OF_FACI) && (MEM_59_RENESAS_FCU_OK == LenStatus); LucLoop++)/* PRQA S 2877 # JV-01 */
    {
      Mem_59_Renesas_GusFACI = LucLoop;
      LenStatus = Mem_59_Renesas_FPSYS_FcuReset();
    }
    Mem_59_Renesas_GusFACI = LusFacinumber;
  }
  else if (R_RFD_ERR_FACI_DEFINITION == LulRFDStatus)
  {
    LenStatus = MEM_59_RENESAS_FCU_ERR_CONFIGURATION;
  }
  else
  {
    LenStatus = MEM_59_RENESAS_FCU_ERR_INTERNAL;
  }

  return (LenStatus);
} /* End of function Mem_59_Renesas_FPSYS_InitFcu */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_FPSYS_ProcessEraseJob
**
** Service ID                : NA
**
** Description               : This function initiates the Erase Job for
**                             configured Flash Blocks.
**
** Sync/Async                : Synchronous
**
** Re-entrancy               : Non Re-entrant
**
** Input Parameters          : None
**
** InOut Parameters          : LulInstanceId
**
** Output Parameters         : None
**
** Return parameter          : LucReturnValue
**
** Preconditions             : None
**
** Global Variables Used     : Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GstVar, Mem_59_Renesas_GblFlashEnable
**                             Mem_59_Renesas_GulTimeOutCounter
**
** Function(s) invoked       : Mem_59_Renesas_FPSYS_FcuSwitchMode, Mem_59_Renesas_FPSYS_FcuPreCheck,
**                             R_RFD_EraseDFRequest, Mem_59_Renesas_FPSYS_SetFHVE
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_051, MEM_DUD_ACT_051_GBL001, MEM_DUD_ACT_051_GBL002, MEM_DUD_ACT_051_GBL003
** Reference ID              : MEM_DUD_ACT_051_GBL004, MEM_DUD_ACT_051_GBL005, MEM_DUD_ACT_051_GBL006,
** Reference ID              : MEM_DUD_ACT_051_GBL008, MEM_DUD_ACT_051_GBL007, MEM_DUD_ACT_051_GBL009
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessEraseJob(Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  /* Variable to return Job Initiation status */
  Std_ReturnType LucReturnValue;
  /* Local variable to hold the FCU Status */
  Mem_59_Renesas_FcuStatusType LenStatus;
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  /* Variable to store the type of Flash */
  Mem_59_Renesas_FlashType LenFlashType;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  /* Get pointer Sector Batch*/
  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);
  /* Determine the current type of Flash */
  LenFlashType = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].enFlashType;
  #endif
  /* Initialize Local Variable */
  LucReturnValue = E_NOT_OK;

  #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enable relevant DF and FACI to exit this critical section */
  MEM_59_RENESAS_ENTER_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
  #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */

  #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED)
  if (MEM_59_RENESAS_FALSE == Mem_59_Renesas_GblFlashEnable)                                                            /* PRQA S 3416 # JV-01 */
  {
    /* Disable the flash memory software protection */
    Mem_59_Renesas_FPSYS_SetFHVE(MEM_59_RENESAS_FLASH_PROTECTION_OFF);
    Mem_59_Renesas_GblFlashEnable = MEM_59_RENESAS_TRUE;
  } /* else No action required */
  #endif /* End of #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED) */

  /* Check if FCU is ready to initiate write Job */
  LenStatus = Mem_59_Renesas_FPSYS_FcuPreCheck();

  if (MEM_59_RENESAS_FCU_OK == LenStatus)
  {
    #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
    if (MEM_59_RENESAS_CODE_FLASH == LenFlashType)
    #endif
    #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
    {
      /* Code Flash */
      LenStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_CFPE);
      if (MEM_59_RENESAS_FCU_OK == LenStatus)
      {
        R_RFD_EraseCFRequest((T_u4_RfdAddress)Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress);

        /* Set E_OK since Job Initiation Success */
        LucReturnValue = E_OK;
        /* Enable timeout counter */
        Mem_59_Renesas_GulTimeOutCounter[LulInstanceId] = MEM_59_RENESAS_ERASE_TIMEOUT_COUNT;
      } /* else No action required */
    }
    #endif
    #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
    else
    #endif
    #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
    {
      /* Data Flash */
      LenStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_DFPE);
      if (MEM_59_RENESAS_FCU_OK == LenStatus)
      {
        R_RFD_EraseDFRequest((T_u4_RfdAddress)Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress,                   /* PRQA S 0404 # JV-01 */
          (T_u4_RfdAddress)Mem_59_Renesas_GstVar[LulInstanceId].ulJobEndAddress);

        /* Set E_OK since Job Initiation Success */
        LucReturnValue = E_OK;
        /* Enable timeout counter */
        Mem_59_Renesas_GulTimeOutCounter[LulInstanceId] = MEM_59_RENESAS_ERASE_TIMEOUT_COUNT;
      } /* else No action required */
    }
    #endif
  } /* else No action required */

  #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enable relevant DF and FACI to exit this critical section */
  MEM_59_RENESAS_EXIT_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
  #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */

  return (LucReturnValue);
} /* End of function Mem_59_Renesas_FPSYS_ProcessEraseJob */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

#if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_PerformReadDFCheckECC
**
** Service ID               : NA
**
** Description              : This function reads data from the Data Flash.
**                            Doing so, it disables the ECC error interrupts to
**                            avoid interrupt generation on accepted ECC errors
**                            when reading e.g. blank or partly written Flash
**                            words.Instead,the error and fail address is
**                            returned to the calling function.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : LulInstanceId, LulDestAddr, LulSrcAddr
**
** InOut Parameters         : NA
**
** Output Parameters        : Mem_59_Renesas_FcuStatusType
**
** Return parameter         : LenStatus
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GpConfigPtr
**
** Function(s) invoked      : None
**
** Registers Used           : DFSERSTC, DFDERSTC
**
** Reference ID             : MEM_DUD_ACT_043, MEM_DUD_ACT_043_GBL001, MEM_DUD_ACT_043_GBL002, MEM_DUD_ACT_043_GBL003
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_PerformReadDFCheckECC(
  Mem_59_Renesas_InstanceIdType LulInstanceId, const uint32 LulSrcAddr, const uint32 LulDestAddr)
{
  /* Local variable to hold the read data */
  uint32 LulData;
  #if (R_RFD_NUMBER_OF_FACI == MEM_59_RENESAS_FACI_ONE)
  volatile uint32 LulRegDFSESTR;
  volatile uint32 LulRegDFDESTR;
  #endif
  volatile uint32 LulLoopCount;
  uint32 LulReadPageSize;
  Mem_59_Renesas_FcuStatusType LenStatus;
  volatile Mem_59_Renesas_DFECCRegType* LpDFECCRegPtr;

  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  /* Get pointer Sector Batch*/
  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);
  LulReadPageSize = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].ulReadPageSize;

  /*Local variable to hold the FCU status*/
  LenStatus = MEM_59_RENESAS_FCU_OK;
  LpDFECCRegPtr = Mem_59_Renesas_GpConfigPtr->pDFECCRegPtr;
  
  #if (R_RFD_NUMBER_OF_FACI == MEM_59_RENESAS_FACI_ONE)
  /* Clear ECC errors */
  MEM_59_RENESAS_WRITE32(&LpDFECCRegPtr->ulDFSERSTC, MEM_59_RENESAS_FCU_REGBIT_DFSERSTC_ERRCLR);                        /* PRQA S 3469 # JV-01 */
  /* Clear ECC errors */
  MEM_59_RENESAS_WRITE32(&LpDFECCRegPtr->ulDFDERSTC, MEM_59_RENESAS_FCU_REGBIT_DFDERSTC_ERRCLR);                        /* PRQA S 3469 # JV-01 */
  #else
  /* Clear ECC errors */
  MEM_59_RENESAS_WRITE32(&LpDFECCRegPtr->ulDFERSTC, MEM_59_RENESAS_FCU_REGBIT_DFERSTC_ERRCLR);                          /* PRQA S 3469 # JV-01 */
  #endif

  for (LulLoopCount = (uint32)MEM_59_RENESAS_ZERO; 
                                        LulLoopCount < (LulReadPageSize / (uint32)MEM_59_RENESAS_FOUR); LulLoopCount++) /* PRQA S 3387, 3416 # JV-01, JV-01 */
  {
    /* Read 32-Bit Data from source address */
    LulData = MEM_59_RENESAS_DF_READ32(LulSrcAddr + ((uint32)MEM_59_RENESAS_FOUR * LulLoopCount));                      /* PRQA S 0303, 3383, 3384, 3469, 0404 # JV-01, JV-01, JV-01, JV-01, JV-01 */
    /* Write the Data into the Destination Buffer Address */
    MEM_59_RENESAS_DF_WRITE32(LulDestAddr + ((uint32)MEM_59_RENESAS_FOUR * LulLoopCount), LulData);                     /* PRQA S 0303, 3383, 3384, 3469 # JV-01, JV-01, JV-01, JV-01 */
  }

  #if (R_RFD_NUMBER_OF_FACI == MEM_59_RENESAS_FACI_ONE)
  LulRegDFSESTR = (*((volatile uint32 *)(&LpDFECCRegPtr->ulDFSERSTR)));
  if (MEM_59_RENESAS_FCU_REGVAL_DFSERSTR_NOERR != LulRegDFSESTR)                                                        /* PRQA S 3416 # JV-01 */
  {
    if (MEM_59_RENESAS_FCU_REGBIT_DFSERSTR == (MEM_59_RENESAS_FCU_REGBIT_DFSERSTR & LulRegDFSESTR))                     /* PRQA S 3416 # JV-01 */
    {
      LenStatus = MEM_59_RENESAS_FCU_DF_ERR_ECC_SED;
    } /* else No action required */
    /* Clear ECC errors */
    MEM_59_RENESAS_WRITE32(&LpDFECCRegPtr->ulDFSERSTC, MEM_59_RENESAS_FCU_REGBIT_DFSERSTC_ERRCLR);                      /* PRQA S 3469 # JV-01 */
  } /* else No action required */
  LulRegDFDESTR = (*((volatile uint32 *)(&LpDFECCRegPtr->ulDFDERSTR)));
  if (MEM_59_RENESAS_FCU_REGVAL_DFDERSTR_NOERR != LulRegDFDESTR)                                                        /* PRQA S 3416 # JV-01 */
  {
    if (MEM_59_RENESAS_FCU_REGBIT_DFDERSTR == (MEM_59_RENESAS_FCU_REGBIT_DFDERSTR & LulRegDFDESTR))                     /* PRQA S 3416 # JV-01 */
    {
      LenStatus = MEM_59_RENESAS_FCU_DF_ERR_ECC_DED;
    } /* else No action required */
    /* Clear ECC errors */
    MEM_59_RENESAS_WRITE32(&LpDFECCRegPtr->ulDFDERSTC, MEM_59_RENESAS_FCU_REGBIT_DFDERSTC_ERRCLR);                      /* PRQA S 3469 # JV-01 */
  } /* else No action required */
  #else
  if (MEM_59_RENESAS_FCU_REGVAL_DFERSTR_NOERR !=  LpDFECCRegPtr->ulDFERSTR)
  {
    if ((uint32)MEM_59_RENESAS_ONE == (MEM_59_RENESAS_FCU_REGBIT_DFERSTR_SEDF & LpDFECCRegPtr->ulDFERSTR))
    {
      LenStatus = MEM_59_RENESAS_FCU_DF_ERR_ECC_SED;
    }
    else
    {
      LenStatus = MEM_59_RENESAS_FCU_DF_ERR_ECC_DED;
    }
    /* Clear ECC errors */
    MEM_59_RENESAS_WRITE32(&LpDFECCRegPtr->ulDFERSTC, MEM_59_RENESAS_FCU_REGBIT_DFERSTC_ERRCLR);                        /* PRQA S 3469 # JV-01 */
  }
  #endif
  return (LenStatus);
} /* End of function Mem_59_Renesas_FPSYS_PerformReadDFCheckECC */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#endif /* #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) */

#if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_PerformReadCFCheckECC
**
** Service ID               : NA
**
** Description              : This function reads data from the Code Flash.
**                            Doing so, it disables the ECC error interrupts to
**                            avoid interrupt generation on accepted ECC errors
**                            when reading e.g. blank or partly written Flash
**                            words.Instead,the error and fail address is
**                            returned to the calling function.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : LulInstanceId, LulSrcAddr, LulDestAddr
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : LenStatus
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GpConfigPtr, Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GstVar
**
** Function(s) invoked      : None
**
** Registers Used           : CFSSTCLR, CFDSTCLR, CFSERSTR, CFDERSTR
**
** Reference ID             : MEM_DUD_ACT_047, MEM_DUD_ACT_047_GBL001, MEM_DUD_ACT_047_GBL002, MEM_DUD_ACT_047_GBL003
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_PerformReadCFCheckECC(
  Mem_59_Renesas_InstanceIdType LulInstanceId, const uint32 LulSrcAddr, const uint32 LulDestAddr)
{
  /* Local variable to hold the read data */
  uint32 LulData;
  uint32 LulCounter;
  uint32 LulReadPageSize;
  Mem_59_Renesas_FcuStatusType LenStatus;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;

  volatile Mem_59_Renesas_CFECCRegType* LpCFECCRegPtr;                                                                  
  LpCFECCRegPtr = Mem_59_Renesas_GpConfigPtr->pCFECCRegPtr;

  /* Get pointer Sector Batch*/
  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);
  LulReadPageSize = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].ulReadPageSize;

  /*Local variable to hold the FCU status*/
  LenStatus = MEM_59_RENESAS_FCU_OK;

  /* Clear 1 bit ECC errors */
  MEM_59_RENESAS_CF_WRITE32(&LpCFECCRegPtr->ulCFSSTCLR, MEM_59_RENESAS_CLEAR_1_BIT_ERROR);                              /* PRQA S 3469 # JV-01 */
  /* Clear 2 bits ECC errors */
  MEM_59_RENESAS_CF_WRITE32(&LpCFECCRegPtr->ulCFDSTCLR, MEM_59_RENESAS_CLEAR_2_BITS_ERROR);                             /* PRQA S 3469 # JV-01 */

  /* Read 256-Bit Data from source address */
  for (LulCounter = ((uint32)MEM_59_RENESAS_ZERO);
                                           LulCounter < (LulReadPageSize / (uint32)MEM_59_RENESAS_FOUR); LulCounter++)
  {
    /* Read 256-Bit Data from source address */
    LulData = MEM_59_RENESAS_CF_READ32(LulSrcAddr + ((uint32)MEM_59_RENESAS_FOUR * LulCounter));                        /* PRQA S 0303, 3383, 3469 # JV-01, JV-01, JV-01 */
    /* Write the Data into the Destination Buffer Address */
    MEM_59_RENESAS_CF_WRITE32(LulDestAddr + ((uint32)MEM_59_RENESAS_FOUR * LulCounter), LulData);                       /* PRQA S 0303, 3383, 3469 # JV-01, JV-01, JV-01 */
  }

  if ((uint32)MEM_59_RENESAS_ZERO != 
                        ((*((volatile uint32 *)(&LpCFECCRegPtr->ulCFSERSTR))) & MEM_59_RENESAS_STATUS_1_BIT_ERROR_MASK))
  {
    LenStatus = MEM_59_RENESAS_FCU_CF_ERR_ECC_SED;
    /* Clear 1 bit ECC errors */
    MEM_59_RENESAS_CF_WRITE32(&LpCFECCRegPtr->ulCFSSTCLR, MEM_59_RENESAS_CLEAR_1_BIT_ERROR);                            /* PRQA S 3469 # JV-01 */
  }
  
  if ((uint32)MEM_59_RENESAS_ZERO != 
                       ((*((volatile uint32 *)(&LpCFECCRegPtr->ulCFDERSTR))) & MEM_59_RENESAS_STATUS_2_BITS_ERROR_MASK))
  {
    LenStatus = MEM_59_RENESAS_FCU_CF_ERR_ECC_DED;
    /* Clear 2 bits ECC errors */
    MEM_59_RENESAS_CF_WRITE32(&LpCFECCRegPtr->ulCFDSTCLR, MEM_59_RENESAS_CLEAR_2_BITS_ERROR);                           /* PRQA S 3469 # JV-01 */
  }
  return (LenStatus);
} /* End of function Mem_59_Renesas_FPSYS_PerformReadCFCheckECC */

#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#endif /* #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) */

#if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED)
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_SetFHVE
**
** Service ID               : NA
**
** Description              : Pull FHVE3 and FHVE15 registers pin to VDD or VSS
**                            to Enable or to Disable the flash memory software
**                            protection.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : Lulvalue
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GusFACI
**
** Function(s) invoked      : R_RFD_SetFHVE
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_044, MEM_DUD_ACT_044_GBL001
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_SetFHVE(const uint32 Lulvalue)
{
  (void)R_RFD_SetFHVE(Mem_59_Renesas_GusFACI, (T_en_Protect)Lulvalue);                                                  /* PRQA S 4342 # JV-01 */
} /* End of function Mem_59_Renesas_FPSYS_SetFHVE */

#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#endif /* #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED) */

#if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_ProcessBlankCheckDFJob
**
** Service ID               : NA
**
** Description              : This function initiates the Blank Check Job
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : LulInstanceId
**
** InOut Parameters         : None
**
** Output Parameters        : Std_ReturnType
**
** Return parameter         : LucReturnValue
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GblFlashEnable, Mem_59_Renesas_GstVar, Mem_59_Renesas_GulTimeOutCounter
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_SetFHVE, R_RFD_BlankCheckDFRequest,
**                            Mem_59_Renesas_FPSYS_FcuPreCheck, Mem_59_Renesas_FPSYS_FcuSwitchMode
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_049, MEM_DUD_ACT_049_GBL001, MEM_DUD_ACT_049_GBL002, MEM_DUD_ACT_049_GBL003
** Reference ID             : MEM_DUD_ACT_049_GBL004
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessBlankCheckDFJob(
                                        Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  /* Variable to return Job Initiation status */
  Std_ReturnType LucReturnValue;
  /* Initialise the local variable to hold the FCU Status */
  Mem_59_Renesas_FcuStatusType LenStatus;
  LucReturnValue = E_NOT_OK;

  #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED)
  if (MEM_59_RENESAS_FALSE == Mem_59_Renesas_GblFlashEnable)                                                            /* PRQA S 3416 # JV-01 */
  {
    /* Disable the flash memory software protection */
    Mem_59_Renesas_FPSYS_SetFHVE(MEM_59_RENESAS_FLASH_PROTECTION_OFF);
    Mem_59_Renesas_GblFlashEnable = MEM_59_RENESAS_TRUE;
  } /* else No action required */
  #endif /* End of #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED) */

  /* Check if FCU is ready to initiate blankcheck Job */
  LenStatus = Mem_59_Renesas_FPSYS_FcuPreCheck();

  if (MEM_59_RENESAS_FCU_OK == LenStatus)
  {
    LenStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_DFPE);

    if (MEM_59_RENESAS_FCU_OK == LenStatus)
    {
      R_RFD_BlankCheckDFRequest((T_u4_RfdAddress)Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress,                /* PRQA S 0404 # JV-01 */
        (T_u4_RfdAddress)Mem_59_Renesas_GstVar[LulInstanceId].ulJobEndAddress);
      /* Set return to E_OK */
      LucReturnValue = E_OK;
      /* Enable timeout counter */
      Mem_59_Renesas_GulTimeOutCounter[LulInstanceId] = MEM_59_RENESAS_BLANKCHECK_TIMEOUT_COUNT;
    } /* else No action required */
  } /* else No action required */

  return (LucReturnValue);
} /* End of function Mem_59_Renesas_ProcessBlankCheckJob */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#endif /*  #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON) */
#if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_BlankCheckCFRequest
**
** Service ID               : NA
**
** Description              : This function initiates the Blank Check Job
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : LulInstanceId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : LucReturnValue
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GstVar, 
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_PerformBlankCheckForReadOp
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_045, MEM_DUD_ACT_045_GBL001, MEM_DUD_ACT_045_GBL002, MEM_DUD_ACT_045_GBL003
** Reference ID             : MEM_DUD_ACT_045_GBL004, MEM_DUD_ACT_045_GBL005
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_BlankCheckCFRequest(
                                                                         Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  /* Local variable to hold the FCU Status */
  Mem_59_Renesas_FcuStatusType LucReturnValue;
  uint32 LulLoopCount;
  uint32 LulReadPageSize;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  /* Get pointer Sector Batch*/
  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);
  LulReadPageSize = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].ulReadPageSize;

  /* Calculate loop count from request read length */
  LulLoopCount = Mem_59_Renesas_GstVar[LulInstanceId].ulRequestedLength / (uint32)LulReadPageSize;

  do
  {
    LucReturnValue = Mem_59_Renesas_FPSYS_PerformBlankCheckForReadOp(
                                                 LulInstanceId, Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress);
    /* Move to next address */
    Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress =
                                              Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress + LulReadPageSize; /* PRQA S 3383 # JV-01 */
    LulLoopCount--;                                                                                                     /* PRQA S 3383 # JV-01 */
  } while ((LulLoopCount > (uint32)MEM_59_RENESAS_ZERO) && (MEM_59_RENESAS_FCU_OK == LucReturnValue));

  return LucReturnValue;
} /* End of function Mem_59_Renesas_FPSYS_BlankCheckCFRequest */ 
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#endif /*  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) */
#if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_SuspendPreCheck
**
** Service ID               : NA
**
** Description              : This function checks for whether different
**                            sequences of requests for suspension is to be
**                            allowed or not
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : LenRequestedCmd
**
** InOut Parameters         : None
**
** Output Parameters        : Std_ReturnType
**
** Return parameter         : LucReturnValue
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GstBackUpVar
**
** Function(s) invoked      : None
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_050, MEM_DUD_ACT_050_GBL001, MEM_DUD_ACT_050_GBL002, MEM_DUD_ACT_050_GBL003
** Reference ID             : MEM_DUD_ACT_050_GBL004, MEM_DUD_ACT_050_GBL005, MEM_DUD_ACT_050_GBL006, 
** Reference ID             : MEM_DUD_ACT_050_GBL007, MEM_DUD_ACT_050_GBL008, MEM_DUD_ACT_050_GBL009
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_SuspendPreCheck(
  Mem_59_Renesas_InstanceIdType LulInstanceId, const uint32 LulJobStartAddress,
  const uint32 LulJobEndAddress, const Mem_59_Renesas_CommandType LenGenCommand)                                        /* PRQA S 3206 # JV-01 */
{
  /* Variable to store return variable */
  Std_ReturnType LucReturnValue;
  uint8 LucLoop;
  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
  /* Variable to store the type of Flash */
  Mem_59_Renesas_FlashType LenFlashType;
  #endif
  /* Pointer to sector batch */
  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  #endif
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  Mem_59_Renesas_FlashType LenBackUpFlashType;
  #endif
  /* Initial version for return value */
  LucReturnValue = E_NOT_OK;

  /* Get pointer Sector Batch*/
  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);
  #endif

  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) && (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  LenBackUpFlashType = LpSectorBatch[Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulSectorBatchIdx].enFlashType;
  #endif
  /* Determine the current type of Flash */
  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
  LenFlashType = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].enFlashType;
  #endif

  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  if (LenFlashType != LenBackUpFlashType)
  {
    /* Accept with different type of memory */
    LucReturnValue = E_OK;
  }
  else
  #endif
  {
    #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
    if (MEM_59_RENESAS_CODE_FLASH == LenFlashType)
    {
      /* Accept with same code flash type */
      /* Block Erasure suspending area and Programming Command acceptable area */
      if ((MEM_59_RENESAS_COMMAND_ERASE == Mem_59_Renesas_GstBackUpVar[LulInstanceId].enGenCommand) && 
          (MEM_59_RENESAS_COMMAND_WRITE == LenGenCommand))
      {
        if ((LulJobStartAddress > Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobEndAddress) || 
            (LulJobEndAddress < Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobStartAddress))
        {
          LucReturnValue = E_OK;
        }/* else No action required */
      }
      else
      {
        LucReturnValue = E_OK;
        for (LucLoop = (uint8)MEM_59_RENESAS_ZERO; LucLoop < (uint8)MEM_59_RENESAS_TOTAL_BANK; LucLoop++)
        {
          if (((LulJobStartAddress >= Mem_59_Renesas_GaaCodeFlash[LucLoop][MEM_59_RENESAS_START_ADDRESS]) && 
                      (LulJobEndAddress <= Mem_59_Renesas_GaaCodeFlash[LucLoop][MEM_59_RENESAS_END_ADDRESS])) \
          && \
          ((Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobStartAddress >= \
                                                  Mem_59_Renesas_GaaCodeFlash[LucLoop][MEM_59_RENESAS_START_ADDRESS])
          && (Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobEndAddress <= \
                                                  Mem_59_Renesas_GaaCodeFlash[LucLoop][MEM_59_RENESAS_END_ADDRESS])))
          {
            LucReturnValue = E_NOT_OK;
            break;
          }/* else No action required */
        }
      }
    }
    #endif
    #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
    else
    #endif
    #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
    {
      #if (R_RFD_NUMBER_OF_FACI == MEM_59_RENESAS_FACI_ONE)
      if ((LulJobStartAddress > Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobEndAddress) || 
          (LulJobEndAddress < Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobStartAddress))
      {
        LucReturnValue = E_OK;
      }/* else No action required */
      LucLoop = (uint8)MEM_59_RENESAS_ZERO;
      (void)(LucLoop);
      #else
      if ((MEM_59_RENESAS_COMMAND_ERASE == LenGenCommand) || 
                              (MEM_59_RENESAS_COMMAND_WRITE == Mem_59_Renesas_GstBackUpVar[LulInstanceId].enGenCommand))
      {
        LucReturnValue = E_OK;
        for (LucLoop = (uint8)MEM_59_RENESAS_ZERO; LucLoop < (uint8)MEM_59_RENESAS_TOTAL_AREA; LucLoop++)
        {
          if (((LulJobStartAddress >= Mem_59_Renesas_GaaDataFlash[LucLoop][MEM_59_RENESAS_START_ADDRESS]) && 
                      (LulJobEndAddress <= Mem_59_Renesas_GaaDataFlash[LucLoop][MEM_59_RENESAS_END_ADDRESS])) \
          && \
          ((Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobStartAddress >= \
                                                  Mem_59_Renesas_GaaDataFlash[LucLoop][MEM_59_RENESAS_START_ADDRESS])
          && (Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobEndAddress <= \
                                                  Mem_59_Renesas_GaaDataFlash[LucLoop][MEM_59_RENESAS_END_ADDRESS])))
          {
            LucReturnValue = E_NOT_OK;
            break;
          }/* else No action required */
        }
      }
      else
      {
        if ((LulJobStartAddress > Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobEndAddress) || 
            (LulJobEndAddress < Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobStartAddress))
        {
          LucReturnValue = E_OK;
        }/* else No action required */
      }
      #endif
    }
    #endif
  }
  return (LucReturnValue);
} /* End of function Mem_59_Renesas_FPSYS_SuspendPreCheck */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#endif
#if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_SetDFEccErrInt
**
** Service ID               : NA
**
** Description              : Function to Set DFERRINT register
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : LucSetValue
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GpConfigPtr
**
** Function(s) invoked      : None
**
** Registers Used           : DFKCPROT, DFERRINT
**
** Reference ID             : MEM_DUD_ACT_055, MEM_DUD_ACT_055_GBL001
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_SetDFEccErrInt(const uint8 LucSetValue)                               /* PRQA S 3006 # JV-01 */
{
  volatile Mem_59_Renesas_DFECCRegType* LpDFECCRegPtr;                                                                  

  LpDFECCRegPtr = Mem_59_Renesas_GpConfigPtr->pDFECCRegPtr;

  MEM_59_RENESAS_DF_WRITE32(&LpDFECCRegPtr->ulDFKCPROT, MEM_59_RENESAS_FCU_REGVAL_DFKCPROT_ENABLE);                     /* PRQA S 3469 # JV-01 */

  MEM_59_RENESAS_WRITE32(&LpDFECCRegPtr->ulDFERRINT, (uint32)LucSetValue);                                              /* PRQA S 3469 # JV-01 */

  MEM_59_RENESAS_DF_WRITE32(&LpDFECCRegPtr->ulDFKCPROT, MEM_59_RENESAS_FCU_REGVAL_DFKCPROT_DISABLE);                    /* PRQA S 3469 # JV-01 */

  /* Dummy read */
  MEM_59_RENESAS_DUMMY_READ_32(&LpDFECCRegPtr->ulDFKCPROT);                                                             /* PRQA S 3469 # JV-01 */
  /* Synchronization */
  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
} /* End of function Mem_59_Renesas_FPSYS_SetDFEccErrInt */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#endif /*  #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON) */

#if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_SetCFEccErrInt
**
** Service ID               : NA
**
** Description              : Function to Set CFERRINT register
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : LucSetValue
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GpConfigPtr
**
** Function(s) invoked      : None
**
** Registers Used           : DFKCPROT, CFERRINT
**
** Reference ID             : MEM_DUD_ACT_054, MEM_DUD_ACT_054_GBL001, MEM_DUD_ACT_054_GBL002, MEM_DUD_ACT_054_GBL003
** Reference ID             : MEM_DUD_ACT_054_GBL004
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_SetCFEccErrInt(const uint8 LucSetValue)                               /* PRQA S 3006 # JV-01 */
{
  volatile Mem_59_Renesas_CFECCRegType* LpCFECCRegPtr;                                                                  
  LpCFECCRegPtr = Mem_59_Renesas_GpConfigPtr->pCFECCRegPtr;

  /* Enable write access to protected registers */
  MEM_59_RENESAS_REG_WRITE(*(Mem_59_Renesas_GpConfigPtr->pECCKCPROTRegPtr), MEM_59_RENESAS_FCU_REGVAL_DFKCPROT_ENABLE); /* PRQA S 3473 # JV-01 */
  /* Set control error reporting when 1-bit/2-bit ECC errors are detected */
  MEM_59_RENESAS_WRITE32(&LpCFECCRegPtr->ulCFERRINT, (uint32)LucSetValue);                                              /* PRQA S 3469 # JV-01 */
  /* Disable write access to protected registers */
  MEM_59_RENESAS_REG_WRITE(*(Mem_59_Renesas_GpConfigPtr->pECCKCPROTRegPtr), MEM_59_RENESAS_FCU_REGVAL_DFKCPROT_DISABLE);/* PRQA S 3473 # JV-01 */
  /* Dummy read */
  MEM_59_RENESAS_DUMMY_READ_32(Mem_59_Renesas_GpConfigPtr->pECCKCPROTRegPtr);                                           /* PRQA S 3469 # JV-01 */

  EXECUTE_SYNCP();                                                                                                      /* PRQA S 1006 # JV-01 */
} /* End of function Mem_59_Renesas_FPSYS_SetCFEccErrInt */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#endif /*  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_SuspendHwOperation
**
** Service ID               : NA
**
** Description              : This function handle the hardware suspend operation
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : LulInstanceId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : LenStatus
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GblFlashEnable, Mem_59_Renesas_GpInsConfig
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_FcuSwitchMode, Mem_59_Renesas_FPSYS_FcuSuspendRequest,
**                            Mem_59_Renesas_FPSYS_SetFHVE
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_038, MEM_DUD_ACT_038_GBL001, MEM_DUD_ACT_038_GBL002, MEM_DUD_ACT_038_GBL003
** Reference ID             : MEM_DUD_ACT_038_GBL004
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_SuspendHwOperation(
                                                                    Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  Std_ReturnType LenReturnValue;
  Mem_59_Renesas_FcuStatusType LenStatus;
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  Mem_59_Renesas_FlashType LenFlashType;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  
  /* Get pointer Sector Batch*/
  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);
  /* Determine the current type of Flash */
  LenFlashType = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].enFlashType;
  #else
  (void)LulInstanceId;
  #endif
  /* Initial return value */
  LenReturnValue = E_NOT_OK;
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  if (MEM_59_RENESAS_CODE_FLASH == LenFlashType)
  #endif
  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
  {
    /* Code Flash */
    LenStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_CFPE);
  }
  #endif
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  else
  #endif
  #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
  {
    /* Data Flash */
    LenStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_DFPE);
  }
  #endif

  if (LenStatus == MEM_59_RENESAS_FCU_OK)
  {
    LenStatus = Mem_59_Renesas_FPSYS_FcuSuspendRequest();
  }

  /* Shift to read mode */
  LenStatus |= Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_READ);                                                     /* PRQA S 4522, 4432 # JV-01, JV-01 */

  #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED)
  if (MEM_59_RENESAS_TRUE == Mem_59_Renesas_GblFlashEnable)                                                             /* PRQA S 3416 # JV-01 */
  {
    /* Enable the flash memory software protection */
    Mem_59_Renesas_FPSYS_SetFHVE(MEM_59_RENESAS_FLASH_PROTECTION_ON);
    Mem_59_Renesas_GblFlashEnable = MEM_59_RENESAS_FALSE;
  } /* else No action required */
  #endif /* #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED) */

  if (MEM_59_RENESAS_FCU_OK == LenStatus)
  {
    LenReturnValue = E_OK;
  }  
  return LenReturnValue;
} /* End Mem_59_Renesas_FPSYS_SuspendHwOperation */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_FcuSuspendRequest
**
** Service ID               : NA
**
** Description              : This function request FCU for a suspend operation
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : LenStatus
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GusFACI
**
** Function(s) invoked      : R_RFD_GetFaciStatus, R_RFD_SuspendPERequest
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_046, MEM_DUD_ACT_046_GBL001, MEM_DUD_ACT_046_GBL002, MEM_DUD_ACT_046_GBL003
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuSuspendRequest(void)                       /* PRQA S 1505 # JV-01 */
{
  Mem_59_Renesas_FcuStatusType LenStatus;
  T_u4_RFDReturn LulRFDStatus;
  uint32 LulTimeout = MEM_59_RENESAS_SUSPEND_TIMEOUT_COUNT;

  LenStatus = MEM_59_RENESAS_FCU_ERR_HW_FAILED;

  LulRFDStatus = R_RFD_GetFaciStatus(Mem_59_Renesas_GusFACI);

  if (R_RFD_OK == LulRFDStatus)
  {
    LulRFDStatus = R_RFD_SuspendPERequest(Mem_59_Renesas_GusFACI);

    if (R_RFD_STS_BUSY == LulRFDStatus)
    {
      /* Wait until suspend request is done */
      do
      {
        LulRFDStatus = R_RFD_GetFaciStatus(Mem_59_Renesas_GusFACI);

        if ((R_RFD_STS_ERASE_SUSPENDED == LulRFDStatus) ||
            (R_RFD_STS_WRITE_SUSPENDED == LulRFDStatus))
        {
          LenStatus = MEM_59_RENESAS_FCU_OK;
          break;
        }
        LulTimeout--;                                                                                                   /* PRQA S 3383 # JV-01 */
      } while (LulTimeout > MEM_59_RENESAS_ZERO);
    }
  } /* else No action required */

  return LenStatus;
} /* End Mem_59_Renesas_FPSYS_FcuSuspendRequest */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_ResumeHwOperation
**
** Service ID               : NA
**
** Description              : This function handle the hardware resume operation
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : LulInstanceId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : LenReturnValue
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GblFlashEnable, Mem_59_Renesas_GpInsConfig
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_SetFHVE, Mem_59_Renesas_FPSYS_FcuSwitchMode,
**                            Mem_59_Renesas_FPSYS_FcuResumeRequest
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_053, MEM_DUD_ACT_053_GBL001, MEM_DUD_ACT_053_GBL002, MEM_DUD_ACT_053_GBL003
** Reference ID             : MEM_DUD_ACT_053_GBL004
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ResumeHwOperation(
                                                                   Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  Std_ReturnType LenReturnValue;
  Mem_59_Renesas_FcuStatusType LenStatus;
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  Mem_59_Renesas_FlashType LenFlashType;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  #else
  (void)LulInstanceId;
  #endif
  /* Initial return value */
  LenReturnValue = E_NOT_OK;
  
  #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED)
  if (MEM_59_RENESAS_FALSE == Mem_59_Renesas_GblFlashEnable)                                                            /* PRQA S 3416 # JV-01 */
  {
    /* Disable the flash memory software protection */
    Mem_59_Renesas_FPSYS_SetFHVE(MEM_59_RENESAS_FLASH_PROTECTION_OFF);
    Mem_59_Renesas_GblFlashEnable = MEM_59_RENESAS_TRUE;
  } /* else No action required */
  #endif /* #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED) */
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  /* Get pointer Sector Batch*/
  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);
  /* Determine the current type of Flash */
  LenFlashType = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].enFlashType;
  #endif

  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  if (MEM_59_RENESAS_CODE_FLASH == LenFlashType)
  #endif
  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
  {
    /* Code Flash */
    LenStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_CFPE);
  }
  #endif
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  else
  #endif
  #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
  {
    /* Data Flash */
    LenStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_DFPE);
  }
  #endif

  if (LenStatus == MEM_59_RENESAS_FCU_OK)
  {
    LenStatus = Mem_59_Renesas_FPSYS_FcuResumeRequest();
  }

  if (MEM_59_RENESAS_FCU_OK == LenStatus)
  {
    LenReturnValue = E_OK;
  }
  
  return LenReturnValue;
} /* End Mem_59_Renesas_FPSYS_ResumeHwOperation */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_FcuResumeRequest
**
** Service ID               : NA
**
** Description              : This function handle the hardware resume request
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : LenStatus
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GusFACI
**
** Function(s) invoked      : R_RFD_GetFaciStatus, R_RFD_ResumePERequest
**
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_052, MEM_DUD_ACT_052_GBL001, MEM_DUD_ACT_052_GBL002
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_FcuResumeRequest(void)                        /* PRQA S 1505 # JV-01 */
{
  Mem_59_Renesas_FcuStatusType LenStatus;
  T_u4_RFDReturn LulRFDStatus;

  LenStatus = MEM_59_RENESAS_FCU_ERR_HW_FAILED;

  LulRFDStatus = R_RFD_GetFaciStatus(Mem_59_Renesas_GusFACI);

  if ((R_RFD_STS_SUSPENDING & LulRFDStatus) != (uint32)MEM_59_RENESAS_ZERO)
  {
    LulRFDStatus = R_RFD_ResumePERequest(Mem_59_Renesas_GusFACI);

    if (R_RFD_OK == LulRFDStatus)
    {
      LenStatus = MEM_59_RENESAS_FCU_OK;
    }
  } /* else No action required */

  return LenStatus;
} /* End Mem_59_Renesas_FPSYS_FcuResumeRequest*/
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_ReadOptionByteService
**
** Service ID               : NA
**
** Description              : Read OPBT register
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : LulInstanceId
**
** InOut Parameters         : dataPtr
**
** Output Parameters        : None
**
** Return parameter         : LenReturnValue
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GstVar, Mem_59_Renesas_GenJobResult, Mem_59_Renesas_GenInstanceState
**
** Function(s) invoked      : None
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_059, MEM_DUD_ACT_059_GBL001, MEM_DUD_ACT_059_GBL002, MEM_DUD_ACT_059_GBL003
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ReadOptionByteService(Mem_59_Renesas_InstanceIdType LulInstanceId,
  P2VAR(Mem_59_Renesas_DataType, AUTOMATIC, MEM_APPL_DATA) dataPtr)                                                     /* PRQA S 3432 # JV-01 */
{
  /* Local variable to hold the return of HW sepcific service */
  Mem_59_Renesas_JobResultType LenInternalJobResult;
  /* Definition of the local variable s */
  uint32          LulOptionByteAddress;  /* Option Byte Address               */
  uint32          LulOptionByteValue;    /* Option Byte Value                 */
  uint8           LucOptionBytePosition; /* Option Byte Position              */
  uint8           LucSideArea;           /* Front side/ Back side             */
  
  /* Initialization of the local variables */
  LulOptionByteAddress    = MEM_59_RENESAS_ZERO;                                                                        /* PRQA S 2982 # JV-01 */
  LulOptionByteValue      = MEM_59_RENESAS_ZERO;                                                                        /* PRQA S 2982 # JV-01 */
  LenInternalJobResult    = MEM_59_RENESAS_JOB_FAILED;                                                                  /* PRQA S 2982 # JV-01 */

  /* Assign Option Byte Position to local variable  */
  LucOptionBytePosition = *dataPtr;

  /* Assign the option to read the address from the front or back side. */
  LucSideArea = *(dataPtr + MEM_59_RENESAS_ONE);                                                                        /* PRQA S 0488 # JV-01 */

  
  if (MEM_59_RENESAS_FRONT_SIDE == LucSideArea)
  /* Read option byte from front side */
  {
    /* Calculate  Address of input requested Option Byte */
    LulOptionByteAddress =  MEM_59_RENESAS_OPBT0_ADDRESS_FRONT_SIDE +                                                   /* PRQA S 3383 # JV-01 */
    (uint32)((MEM_59_RENESAS_UNIT_REGISTER_ADDRESS) * (LucOptionBytePosition));                                         /* PRQA S 3383 # JV-01 */
    /* Get value at  Address of input requested Option Byte */      
    LulOptionByteValue = (*((volatile uint32 *)(LulOptionByteAddress)));                                                /* PRQA S 0303 # JV-01 */
    /* Store value of Option Byte to pointer */     
    *(dataPtr)             = (uint8)(LulOptionByteValue); 
    *(dataPtr + MEM_59_RENESAS_ONE)   = (uint8)(LulOptionByteValue>> MEM_59_RENESAS_EIGHT);                             /* PRQA S 0488 # JV-01 */
    *(dataPtr + MEM_59_RENESAS_TWO)   = (uint8)(LulOptionByteValue>> MEM_59_RENESAS_SIXTEEN);                           /* PRQA S 0488 # JV-01 */
    *(dataPtr + MEM_59_RENESAS_THREE) = (uint8)(LulOptionByteValue>> MEM_59_RENESAS_TWENTY_FOUR);                       /* PRQA S 0488 # JV-01 */
    LenInternalJobResult = MEM_59_RENESAS_JOB_OK;    
  }
  else
  /* Read option byte from back side */
  {
    /* Calculate  Address of input requested Option Byte */
    LulOptionByteAddress =  MEM_59_RENESAS_OPBT0_ADDRESS_BACK_SIDE +                                                    /* PRQA S 3383 # JV-01 */
    (uint32)((MEM_59_RENESAS_UNIT_REGISTER_ADDRESS) * (LucOptionBytePosition));                                         /* PRQA S 3383 # JV-01 */
    /* Get value at  Address of input requested Option Byte */
    LulOptionByteValue = (*((volatile uint32 *)(LulOptionByteAddress)));                                                /* PRQA S 0303 # JV-01 */
    /* Store value of Option Byte to pointer */
    *(dataPtr)             = (uint8)(LulOptionByteValue);
    *(dataPtr + MEM_59_RENESAS_ONE)   = (uint8)(LulOptionByteValue>> MEM_59_RENESAS_EIGHT);                             /* PRQA S 0488 # JV-01 */
    *(dataPtr + MEM_59_RENESAS_TWO)   = (uint8)(LulOptionByteValue>> MEM_59_RENESAS_SIXTEEN);                           /* PRQA S 0488 # JV-01 */
    *(dataPtr + MEM_59_RENESAS_THREE) = (uint8)(LulOptionByteValue>> MEM_59_RENESAS_TWENTY_FOUR);                       /* PRQA S 0488 # JV-01 */
    LenInternalJobResult = MEM_59_RENESAS_JOB_OK;
  }

  /* Set the job result to internal job status */
  Mem_59_Renesas_GenJobResult[LulInstanceId] = LenInternalJobResult;
  /* Set the command to none */
  Mem_59_Renesas_GstVar[LulInstanceId].enGenCommand = MEM_59_RENESAS_COMMAND_NONE;
  /* Set the driver state to idle */
  Mem_59_Renesas_GenInstanceState[LulInstanceId] = MEM_59_RENESAS_IDLE;
}
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_PerformBlankCheckForReadOp
**
** Service ID               : NA
**
** Description              : This function performs the blank check operation when the command is 
**                            MEM_59_RENESAS_COMMAND_READ.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : LulStartAddr
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : LenStatus
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GpInsConfig, 
**
** Function(s) invoked      : None
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_057, MEM_DUD_ACT_057_GBL001, MEM_DUD_ACT_057_GBL002
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_PerformBlankCheckForReadOp(
  Mem_59_Renesas_InstanceIdType LulInstanceId, const uint32 LulStartAddr)
{
  Mem_59_Renesas_FcuStatusType LenStatus;
  uint32 LulBlankCkeckAddr;
  uint32 LulBlankFlagData;
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  Mem_59_Renesas_FlashType LenFlashType;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  /* Get pointer Sector Batch*/
  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);
  /* Determine the current type of Flash */
  LenFlashType = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].enFlashType;
  #else
  (void)LulInstanceId;
  #endif

  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  if (MEM_59_RENESAS_CODE_FLASH == LenFlashType)
  #endif
  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
  {
    /* Blank Flag Check */
    LulBlankCkeckAddr = (LulStartAddr + (MEM_59_RENESAS_CF_BLANK_USER_AREA_OFFSET));                                    /* PRQA S 3383 # JV-01 */

    LulBlankFlagData = MEM_59_RENESAS_READ32(LulBlankCkeckAddr);                                                        /* PRQA S 0303, 3469 # JV-01, JV-01 */

    if (MEM_59_RENESAS_CODE_BLANK_STATE == LulBlankFlagData)
    {
      /* Blank */
      LenStatus = MEM_59_RENESAS_FCU_OK;
    }
    else
    {
      /* Not Blank */
      LenStatus = MEM_59_RENESAS_FCU_BC_INCONSISTENT;
    }
  }
  #endif
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  else
  #endif
  #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
  {
    /* Blank Flag Check */
    LulBlankCkeckAddr = (LulStartAddr + (MEM_59_RENESAS_DF_BLANK_AREA_OFFSET));                                         /* PRQA S 3383 # JV-01 */

    LulBlankFlagData = MEM_59_RENESAS_READ32(LulBlankCkeckAddr);                                                        /* PRQA S 0303, 3469 # JV-01, JV-01 */

    if (MEM_59_RENESAS_DATA_BLANK_STATE == LulBlankFlagData)
    {
      /* Blank */
      LenStatus = MEM_59_RENESAS_FCU_OK;
    }
    else
    {
      /* Not Blank */
      LenStatus = MEM_59_RENESAS_FCU_BC_INCONSISTENT;
    }
  }
  #endif

  return (LenStatus);
} /* End of function Mem_59_Renesas_FPSYS_PerformBlankCheckForReadOp */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_FPSYS_ProcessWriteJob
**
** Service ID                : NA
**
** Description               : This function initiates the write Job for each word.
**
** Sync/Async                : Asynchronous
**
** Re-entrancy               : Non Re-entrant
**
** Input Parameters          : LulInstanceId
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : LucReturnValue
**
** Preconditions             : None
**
** Global Variables Used     : Mem_59_Renesas_GstVar Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GulTimeOutCounter
**
** Function(s) invoked       : Mem_59_Renesas_FPSYS_FcuSwitchMode, Mem_59_Renesas_FPSYS_FcuPreCheck, 
**                             Mem_59_Renesas_FPSYS_SetFHVE, R_RFD_WriteDFRequest
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_058, MEM_DUD_ACT_058_GBL001, MEM_DUD_ACT_058_GBL002, MEM_DUD_ACT_058_GBL003
** Reference ID              : MEM_DUD_ACT_058_GBL004, MEM_DUD_ACT_058_GBL005, MEM_DUD_ACT_058_GBL006,
** Reference ID              : MEM_DUD_ACT_058_GBL008, MEM_DUD_ACT_058_GBL007, MEM_DUD_ACT_058_GBL009
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessWriteJob(Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  /* Variable to return Job Initiation status */
  Std_ReturnType LucReturnValue;
  /* Local variable to hold the FCU Status */
  Mem_59_Renesas_FcuStatusType LenStatus;

  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  /* Variable to store type of Flash */
  Mem_59_Renesas_FlashType LenFlashType;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  /* Get pointer Sector Batch*/
  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);
  /* Determine the current type of Flash */
  LenFlashType = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].enFlashType;
  #endif
  /* Initialize Local Variable */
  LucReturnValue = E_NOT_OK;
  #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enable relevant DF and FACI to exit this critical section */
  MEM_59_RENESAS_ENTER_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
  #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */

  #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED)
  if (MEM_59_RENESAS_FALSE == Mem_59_Renesas_GblFlashEnable)                                                            /* PRQA S 3416 # JV-01 */
  {
    /* Disable the flash memory software protection */
    Mem_59_Renesas_FPSYS_SetFHVE(MEM_59_RENESAS_FLASH_PROTECTION_OFF);
    Mem_59_Renesas_GblFlashEnable = MEM_59_RENESAS_TRUE;
  } /* else No action required */
  #endif /* End of #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED) */

  /* Check if FCU is ready to initiate write Job */
  LenStatus = Mem_59_Renesas_FPSYS_FcuPreCheck();

  if (MEM_59_RENESAS_FCU_OK == LenStatus)
  {
    #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
    if (MEM_59_RENESAS_CODE_FLASH == LenFlashType)
    #endif
    #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
    {
      /* Switching to P/E Mode */
      LenStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_CFPE);

      if (MEM_59_RENESAS_FCU_OK == LenStatus)
      {
        R_RFD_WriteCFRequest((T_u4_RfdAddress)Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress,                   /* PRQA S 0404 # JV-01 */
          (T_pu4_RfdBuffer)Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress);                                        /* PRQA S 0310, 0311, 0312, 3305 # JV-01, JV-01, JV-01, JV-01 */
        /* Set E_OK since Job Initiation Success */
        LucReturnValue = E_OK;
        /* Enable timeout counter */
        Mem_59_Renesas_GulTimeOutCounter[LulInstanceId] = MEM_59_RENESAS_PROGRAM_TIMEOUT_COUNT;
      } /* else No action required */
    }
    #endif
    #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
    else
    #endif
    #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
    {
      /* Switching to P/E Mode */
      LenStatus = Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_DFPE);

      if (MEM_59_RENESAS_FCU_OK == LenStatus)
      { 
        (R_RFD_WriteDFRequest((T_u4_RfdAddress)Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress,                  /* PRQA S 0404 # JV-01 */
                                            (T_u2)Mem_59_Renesas_GstVar[LulInstanceId].ulRequestedLength,
                                      (T_pu4_RfdBuffer)Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress));           /* PRQA S 0310, 0311, 0312, 3305 # JV-01, JV-01, JV-01, JV-01 */
        /* Set E_OK since Job Initiation Success */
        LucReturnValue = E_OK;
        /* Enable timeout counter */
        Mem_59_Renesas_GulTimeOutCounter[LulInstanceId] = MEM_59_RENESAS_PROGRAM_TIMEOUT_COUNT;
      } /* else No action required */
    }
    #endif
  } /* else No action required */

  #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Ena  ble relevant DF and FACI to exit this critical section */
  MEM_59_RENESAS_EXIT_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
  #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */

  return (LucReturnValue);
} /* End of function Mem_59_Renesas_FPSYS_ProcessWriteJob */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
