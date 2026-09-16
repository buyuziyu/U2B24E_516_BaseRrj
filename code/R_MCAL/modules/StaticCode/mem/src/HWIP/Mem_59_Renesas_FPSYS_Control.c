/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mem_59_Renesas_FPSYS_Control.c                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Internal functions implementation of Flash Wrapper Component.                                   */
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
 *                        Change the location of the critical section in Mem_59_Renesas_FPSYS_ProcessSuspend
 *                        Support parameter on/off for Mem_59_Renesas_ReadImmediate API
 * 1.0.3:  25/04/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 *                        As part of ARDAACL-54679, support reset all FACIs
 *                        As part of ARDAACL-51989, support timeout for Mem Driver
 *                        As part of ARDAACL-53723, change access pointer from 4 bytes to 1 byte
 * 1.0.2:  31/03/2025   : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release 
 * 1.0.1:  28/02/2025   : Update sequence check option byte ID of Mem_59_Renesas_FPSYS_HwSpecificService
 * 1.0.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                        As part of ARDAACL-51152, support read option from back side in 
 *                        Mem_59_Renesas_FPSYS_HwSpecificService.
 * 0.0.2:  31/10/2024   : As part of ARDAACJ-621, support downgrade from version AR23-11 to AR22-11.
 *                        Support commonize
 * 0.0.1:  30/08/2024   : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for prototypes for internal functions of Flash Wrapper Component */
#include "Mem_59_Renesas_FPSYS_Control.h"
/* Included for RAM variable declarations */
#include "Mem_59_Renesas_Ram.h"
/* Included for device specific functions */
#include "Mem_59_Renesas_device_dep.h"
/* Included for the declaration of Det_ReportError(),Det_ReportRuntimeError() */
#if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
/* Included for the macro declaration of supervisor mode(SV) write enabled Registers IMR */
#include "Mem_59_Renesas_FPSYS_LLDriver.h"
/* Include for RFD */
#include "r_rfd.h"
#include "r_rfd_df.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MEM_59_RENESAS_CONTROL_C_AR_RELEASE_MAJOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION_VALUE
#define MEM_59_RENESAS_CONTROL_C_AR_RELEASE_MINOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION_VALUE
#define MEM_59_RENESAS_CONTROL_C_AR_RELEASE_REVISION_VERSION MEM_59_RENESAS_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define MEM_59_RENESAS_CONTROL_C_SW_MAJOR_VERSION            MEM_59_RENESAS_SW_MAJOR_VERSION_VALUE
#define MEM_59_RENESAS_CONTROL_C_SW_MINOR_VERSION            MEM_59_RENESAS_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (MEM_59_RENESAS_CONTROL_AR_RELEASE_MAJOR_VERSION != MEM_59_RENESAS_CONTROL_C_AR_RELEASE_MAJOR_VERSION)
#error "Mem_59_Renesas_FPSYS_Control.c : Mismatch in Release Major Version"
#endif

#if (MEM_59_RENESAS_CONTROL_AR_RELEASE_MINOR_VERSION != MEM_59_RENESAS_CONTROL_C_AR_RELEASE_MINOR_VERSION)
#error "Mem_59_Renesas_FPSYS_Control.c : Mismatch in Release Minor Version"
#endif

#if (MEM_59_RENESAS_CONTROL_AR_RELEASE_REVISION_VERSION != MEM_59_RENESAS_CONTROL_C_AR_RELEASE_REVISION_VERSION)
#error "Mem_59_Renesas_FPSYS_Control.c : Mismatch in Release Revision Version"
#endif

#if (MEM_59_RENESAS_CONTROL_SW_MAJOR_VERSION != MEM_59_RENESAS_CONTROL_C_SW_MAJOR_VERSION)
#error "Mem_59_Renesas_FPSYS_Control.c : Mismatch in Software Major Version"
#endif

#if (MEM_59_RENESAS_CONTROL_SW_MINOR_VERSION != MEM_59_RENESAS_CONTROL_C_SW_MINOR_VERSION)
#error "Mem_59_Renesas_FPSYS_Control.c : Mismatch in Software Minor Version"
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
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used following AUTOSAR standard rule. It is accepted.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3673)    : The object addressed by the pointer parameter '%s' is not modified and so the pointer could  */
/*                       be of type 'pointer to const'.                                                               */
/* Rule                : MISRA C:2012 Rule-8.13, CERTCCM DCL00, DCL13, CWE Rule CWE-398, CWE-569                      */
/* JV-01 Justification : Pointer variable is used to modify the value at the address so the pointer cannot be         */
/*                       declared as 'pointer to const' type.                                                         */
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
/* Message (1:0751)    : Casting to char pointer type.                                                                */
/* Rule                : MISRA C:2012 CWE-188, CWE-468, CWE-1157, CWE-398, CWE-465, CWE-569, CWE-588                  */
/* JV-01 Justification : Since each byte needs to be processed, it needs to be cast as a pointer of char type.        */
/*                       So, there is no problem.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_FPSYS_HWResourceInit
**
** Service ID                : NA
**
** Description               : This function flash initiates source control.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Non Re-entrant
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
** Global Variables used     : Mem_59_Renesas_GusFACI, Mem_59_Renesas_GblFlashEnable
**
** Function(s) invoked       : Mem_59_Renesas_FPSYS_InitFlashControl, Mem_59_Renesas_FPSYS_SetFHVE,
**                             Mem_59_Renesas_FPSYS_GetFACINumber
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_067, MEM_DUD_ACT_067_GBL002, MEM_DUD_ACT_067_GBL001
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"
FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_HWResourceInit(Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  Std_ReturnType LucReturnValue;

  #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED)
  uint16 LucLoop;
  #endif /* #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED) */
  Mem_59_Renesas_FcuStatusType LenFcuInitStatus;

  /* Initialize flash control */
  LenFcuInitStatus = Mem_59_Renesas_FPSYS_InitFlashControl();

  if (MEM_59_RENESAS_FCU_OK != LenFcuInitStatus)
  {
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Enable Write/Erase protection settings */
    #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED)
    /* Enable the flash memory software protection */
    for (LucLoop = MEM_59_RENESAS_FACI_0; (LucLoop < (uint16)R_RFD_NUMBER_OF_FACI); LucLoop++)                          /* PRQA S 2877 # JV-01 */
    {
      Mem_59_Renesas_GusFACI = LucLoop;
      Mem_59_Renesas_FPSYS_SetFHVE(MEM_59_RENESAS_FLASH_PROTECTION_ON);
    }
    /* Initialize the global variable flash enable to False */
    Mem_59_Renesas_GblFlashEnable = MEM_59_RENESAS_FALSE;
    #endif /* #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED) */

    /* Get FACI number with Mem_59_Renesas_FPSYS_GetFACINumber */
    Mem_59_Renesas_FPSYS_GetFACINumber((uint32)MEM_59_RENESAS_ZERO, LulInstanceId);

    /* Set result to OK */
    LucReturnValue = E_OK;
  }

  return LucReturnValue;
}
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_FPSYS_InitFlashControl
**
** Service ID                : NA
**
** Description               : This function flash initite control.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Non Re-entrant
**
** Input Parameters          : LulInstanceId
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : LenReturnValue
**
** Preconditions             : None
**
** Global Variables used     : None
**
** Function(s) invoked       : Mem_59_Renesas_FPSYS_PreFcuInitCheck,Mem_59_Renesas_FPSYS_InitFcu,
**                             Mem_59_Renesas_FPSYS_SetDFEccErrInt, Mem_59_Renesas_FPSYS_SetCFEccErrInt
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_014
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_FcuStatusType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_InitFlashControl(void)                        /* PRQA S 1505 # JV-01 */
{
  /* local variable to hold the FCU Status */
  Mem_59_Renesas_FcuStatusType LenFcuInitStatus;
  Mem_59_Renesas_FcuStatusType LenECCStatus;
  Mem_59_Renesas_FcuStatusType LenReturnValue;

  /* Verify ECC control register settings */
  LenECCStatus = Mem_59_Renesas_FPSYS_PreFcuInitCheck();

  #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
  /* Disable DF ECC interrupt setting */
  Mem_59_Renesas_FPSYS_SetDFEccErrInt(MEM_59_RENESAS_FCU_REGVAL_DFERRINT_NOINT);
  #endif
  #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
  /* Disable DF ECC interrupt setting */
  Mem_59_Renesas_FPSYS_SetCFEccErrInt(MEM_59_RENESAS_FCU_REGVAL_CFERRINT_NOINT);
  #endif
  /* Flash memory initialization */
  LenFcuInitStatus = Mem_59_Renesas_FPSYS_InitFcu();

  if ((MEM_59_RENESAS_FCU_OK == LenFcuInitStatus) && (MEM_59_RENESAS_FCU_OK == LenECCStatus))
  {
    LenReturnValue = MEM_59_RENESAS_FCU_OK;
  }
  else if (MEM_59_RENESAS_FCU_OK != LenFcuInitStatus)
  {
    LenReturnValue = LenFcuInitStatus;
  }
  else
  {
    LenReturnValue = LenECCStatus;
  }
  return (LenReturnValue);
} /* End of function Mem_59_Renesas_FPSYS_InitFlashControl */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_FPSYS_ProcessJob
**
** Service ID                : NA
**
** Description               : This function process Mem driver job of FPSYS IP.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Non Re-entrant
**
** Input Parameters          : LulInstanceId
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables used     : Mem_59_Renesas_GstVar
**
** Function(s) invoked       : Mem_59_Renesas_FPSYS_MainErase, Mem_59_Renesas_FPSYS_MainWrite, 
**                             Mem_59_Renesas_FPSYS_MainBlankCheck, Mem_59_Renesas_FPSYS_MainRead
**                             Mem_59_Renesas_FPSYS_MainReadImmediate, Mem_59_Renesas_FPSYS_ReadOptionByteService
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_068
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessJob(Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  switch (Mem_59_Renesas_GstVar[LulInstanceId].enGenCommand)
  {
  case MEM_59_RENESAS_COMMAND_ERASE:
    Mem_59_Renesas_FPSYS_MainErase(LulInstanceId);
    break;
  case MEM_59_RENESAS_COMMAND_WRITE:
    Mem_59_Renesas_FPSYS_MainWrite(LulInstanceId);
    break;
  case MEM_59_RENESAS_COMMAND_BLANKCHECK:
    Mem_59_Renesas_FPSYS_MainBlankCheck(LulInstanceId);
    break;
  case MEM_59_RENESAS_COMMAND_READ:
    Mem_59_Renesas_FPSYS_MainRead(LulInstanceId);
    break;
  #if (MEM_59_RENESAS_READIMMEDIATE_API == STD_ON)
  case MEM_59_RENESAS_COMMAND_READIMMEDIATE:
    Mem_59_Renesas_FPSYS_MainReadImmediate(LulInstanceId); 
    break;
  #endif
  case MEM_59_RENESAS_COMMAND_HWSPECIFIC_SERVICE:
    Mem_59_Renesas_FPSYS_ReadOptionByteService(LulInstanceId, 
                                       (Mem_59_Renesas_DataType *)Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress); /* PRQA S 0311, 0312 # JV-01, JV-01 */
    break;
  default:
    /* No action required */
    break;
  }
} /* End of Mem_59_Renesas_FPSYS_ProcessJob */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_FPSYS_MainErase
**
** Service ID                : NA
**
** Description               : This function is called from Mem_59_Renesas_MainFunction,
**                             when the command is Erase Operation.
**
** Sync/Async                : NA
**
** Reentrancy                : Non Re-entrant
**
** Input Parameters          : LulInstanceId
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Mem_59_Renesas_GstVar, Mem_59_Renesas_GulTimeOutCounter
**
** Function(s) invoked       : Mem_59_Renesas_FPSYS_GetFACINumber, Mem_59_Renesas_FPSYS_FcuCheckJobStatus
**                             Mem_59_Renesas_FPSYS_ProcessJobResult,Mem_59_Renesas_FPSYS_ProcessEraseJob
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_016, MEM_DUD_ACT_016_GBL001, MEM_DUD_ACT_016_GBL002, MEM_DUD_ACT_016_GBL003
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_MainErase(Mem_59_Renesas_InstanceIdType LulInstanceId)                /* PRQA S 1505 # JV-01 */
{
  /* Variable to return write job result */
  Std_ReturnType LucReturnValue;
  /* Variable to hold the Data Flash Status */
  Mem_59_Renesas_FcuStatusType LenStatus;

  LucReturnValue = E_OK;
  /* Invoke Mem_59_Renesas_FPSYS_GetFACINumber function with the calculated start address as an argument */
  Mem_59_Renesas_FPSYS_GetFACINumber(Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress, LulInstanceId);
  /* Check if write request is issued to FACI */
  if (MEM_59_RENESAS_FALSE == Mem_59_Renesas_GstVar[LulInstanceId].blHwRequestedFlg)
  {
    /* Trigger write request to FACI */
    LucReturnValue = Mem_59_Renesas_FPSYS_ProcessEraseJob(LulInstanceId);
    /* Set RFD requested flag to TRUE */
    Mem_59_Renesas_GstVar[LulInstanceId].blHwRequestedFlg = MEM_59_RENESAS_TRUE;
  }
  
  if (E_NOT_OK == LucReturnValue)
  {
    Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_FAILED);
  }
  else
  {
    /* Check if the job is completed or error or busy */
    LenStatus = Mem_59_Renesas_FPSYS_FcuCheckJobStatus();
    if (MEM_59_RENESAS_FCU_OK == LenStatus)
    {
      Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_OK);
    }
    else if (MEM_59_RENESAS_FCU_ERR_HW_FAILED == LenStatus)
    {
      Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_FAILED);
    }
    else
    {
      /* else busy state, handle in next schedule */
      Mem_59_Renesas_GulTimeOutCounter[LulInstanceId]--;                                                                /* PRQA S 3384, 3387 # JV-01, JV-01 */
      if (MEM_59_RENESAS_ZERO == Mem_59_Renesas_GulTimeOutCounter[LulInstanceId])
      {
        Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_FAILED);
      }/* else No action required */
    }
  }
} /* End of function Mem_59_Renesas_FPSYS_MainErase */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_FPSYS_MainWrite
**
** Service ID                : NA
**
** Description               : This function is called from Mem_59_Renesas_MainFunction,
**                             when the command is Write Operation.
**
** Sync/Async                : NA
**
** Reentrancy                : Non Re-entrant
**
** Input Parameters          : LucServiceId
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Mem_59_Renesas_GstVar, Mem_59_Renesas_GulTimeOutCounter
**
** Function(s) invoked       : Mem_59_Renesas_FPSYS_GetFACINumber, Mem_59_Renesas_FPSYS_ProcessWriteJob,
**                             Mem_59_Renesas_FPSYS_ProcessJobResult, Mem_59_Renesas_FPSYS_FcuCheckJobStatus
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_017, MEM_DUD_ACT_017_GBL001, MEM_DUD_ACT_017_GBL002, MEM_DUD_ACT_017_GBL003
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_MainWrite(Mem_59_Renesas_InstanceIdType LulInstanceId)                /* PRQA S 1505 # JV-01 */
{
  /* Variable to return write job result */
  Std_ReturnType LucReturnValue;
  /* Variable to hold the Data Flash Status */
  Mem_59_Renesas_FcuStatusType LenStatus;

  LucReturnValue = E_OK;
  /* Invoke Mem_59_Renesas_FPSYS_GetFACINumber function with the calculated start address as an argument */
  Mem_59_Renesas_FPSYS_GetFACINumber(Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress, LulInstanceId);

  /* Check if write request is issued to FACI */
  if (MEM_59_RENESAS_FALSE == Mem_59_Renesas_GstVar[LulInstanceId].blHwRequestedFlg)
  {
    /* Trigger write request to FACI */
    LucReturnValue = Mem_59_Renesas_FPSYS_ProcessWriteJob(LulInstanceId);
    /* Set RFD requested flag to TRUE */
    Mem_59_Renesas_GstVar[LulInstanceId].blHwRequestedFlg = MEM_59_RENESAS_TRUE;
  }
  
  if (E_NOT_OK == LucReturnValue)
  {
    Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_FAILED);
  }
  else
  {
    /* Check if the job is completed or error or busy */
    LenStatus = Mem_59_Renesas_FPSYS_FcuCheckJobStatus();
    if (MEM_59_RENESAS_FCU_OK == LenStatus)
    {
      Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_OK);
    }
    else if (MEM_59_RENESAS_FCU_ERR_HW_FAILED == LenStatus)
    {
      Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_FAILED);
    }
    else
    {
      Mem_59_Renesas_GulTimeOutCounter[LulInstanceId]--;                                                                /* PRQA S 3384, 3387 # JV-01, JV-01 */
      if (MEM_59_RENESAS_ZERO == Mem_59_Renesas_GulTimeOutCounter[LulInstanceId])
      {
        Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_FAILED);
      }
    }
  }
} /* End of function Mem_59_Renesas_FPSYS_MainWrite */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_MainRead
**
** Service ID               : NA
**
** Description              : This function is called from Mem_59_Renesas_MainFunction,
**                            when the command is Read Operation.
**
** Sync/Async               : NA
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : LulInstanceId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variable(s) Used  : Mem_59_Renesas_GstVar, Mem_59_Renesas_GenJobResult
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_ProcessRead
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_018, MEM_DUD_ACT_018_GBL001, MEM_DUD_ACT_018_GBL002, MEM_DUD_ACT_018_GBL003
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_MainRead(Mem_59_Renesas_InstanceIdType LulInstanceId)                 /* PRQA S 1505 # JV-01 */
{
  /* Local variable to hold the return from ProcessRead Function */
  Mem_59_Renesas_JobResultType LenInternalJobResult;
  /* Call Internal Read Process Function */
  LenInternalJobResult = Mem_59_Renesas_FPSYS_ProcessRead(LulInstanceId);
  /* Set the job result to internal job status */
  Mem_59_Renesas_GenJobResult[LulInstanceId] = LenInternalJobResult;
  /* Set the command to none */
  Mem_59_Renesas_GstVar[LulInstanceId].enGenCommand = MEM_59_RENESAS_COMMAND_NONE;
  /* Set the driver state to idle */
  Mem_59_Renesas_GenInstanceState[LulInstanceId] = MEM_59_RENESAS_IDLE;
} /* End of function Mem_59_Renesas_FPSYS_MainRead */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#if (MEM_59_RENESAS_READIMMEDIATE_API == STD_ON)
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_MainReadImmediate
**
** Service ID               : NA
**
** Description              : This function is called from Mem_59_Renesas_MainFunction,
**                            when the command is Read Fast Operation.
**
** Sync/Async               : NA
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variable(s) Used  : Mem_59_Renesas_GstVar, Mem_59_Renesas_GenJobResult
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_ProcessReadImmediate
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_061, MEM_DUD_ACT_061_GBL001, MEM_DUD_ACT_061_GBL002
** Reference ID             : MEM_DUD_ACT_061_GBL003
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_MainReadImmediate(Mem_59_Renesas_InstanceIdType LulInstanceId)        /* PRQA S 1505 # JV-01 */
{
  /* Local variable to hold the return from ProcessRead Function */
  Mem_59_Renesas_JobResultType LenInternalJobResult;
  /* Call Internal Read Process Function */
  LenInternalJobResult = Mem_59_Renesas_FPSYS_ProcessReadImmediate(LulInstanceId);
  /* Set the job result to internal job status */
  Mem_59_Renesas_GenJobResult[LulInstanceId] = LenInternalJobResult;
  /* Set the command to none */
  Mem_59_Renesas_GstVar[LulInstanceId].enGenCommand = MEM_59_RENESAS_COMMAND_NONE;
  /* Set the driver state to idle */
  Mem_59_Renesas_GenInstanceState[LulInstanceId] = MEM_59_RENESAS_IDLE;
} /* End of function Mem_59_Renesas_FPSYS_MainReadImmediate */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_ProcessCancel
**
** Service ID               : NA
**
** Description              : This function invokes issues the Forced Stop
**                            Command to stop the ongoing FCU operation.
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
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GusFACI, Mem_59_Renesas_GblFlashEnable
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_FcuReset, Mem_59_Renesas_FPSYS_SetFHVE
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_020, MEM_DUD_ACT_020_GBL001, MEM_DUD_ACT_020_GBL002
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessCancel(Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  uint16 LucLoop;
  /* Currently this HWIP does not use instance Id */
  (void)LulInstanceId;
  /* Occuer Other FHVE error */
  #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Disable relevant DF and FACI to exit this critical section */
  MEM_59_RENESAS_ENTER_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
  #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */

  for (LucLoop = MEM_59_RENESAS_FACI_0; LucLoop < (uint16)R_RFD_NUMBER_OF_FACI ; LucLoop++)                             /* PRQA S 2877 # JV-01 */
  {
    Mem_59_Renesas_GusFACI = LucLoop;
    (void)Mem_59_Renesas_FPSYS_FcuReset();
  }

  #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED)
  if (MEM_59_RENESAS_TRUE == Mem_59_Renesas_GblFlashEnable)                                                             /* PRQA S 3416 # JV-01 */
  {
    /* Enable the flash memory software protection */
    Mem_59_Renesas_FPSYS_SetFHVE(MEM_59_RENESAS_FLASH_PROTECTION_ON);
    Mem_59_Renesas_GblFlashEnable = MEM_59_RENESAS_FALSE;
  } /* else No action required */
  #endif /* #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED) */

  #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enable relevant DF and FACI to exit this critical section */
  MEM_59_RENESAS_EXIT_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
  #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */
} /* End of function Mem_59_Renesas_FPSYS_ProcessCancel */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_MainBlankCheck
**
** Service ID               : NA
**
** Description              : This function is called from Mem_59_Renesas_MainFunction,
**                            when the command is BlankCheck Operation.
**
** Sync/Async               : Asynchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : LucServiceId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GstVar, Mem_59_Renesas_GenJobResult,
**                            Mem_59_Renesas_GenInstanceState, Mem_59_Renesas_GulTimeOutCounter
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_BlankCheckCFRequest, Mem_59_Renesas_FPSYS_GetFACINumber, 
**                            Mem_59_Renesas_FPSYS_ProcessBlankCheckDFJob, 
**                            R_RFD_GetFaciStatus, Mem_59_Renesas_FPSYS_ProcessJobResult, 
**                            Mem_59_Renesas_FPSYS_FcuCheckBCJobStatus
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_019, MEM_DUD_ACT_019_GBL001, MEM_DUD_ACT_019_GBL002, MEM_DUD_ACT_019_GBL003
** Reference ID             : MEM_DUD_ACT_019_GBL004, MEM_DUD_ACT_019_GBL005, MEM_DUD_ACT_019_GBL006,
** Reference ID             : MEM_DUD_ACT_019_GBL008, MEM_DUD_ACT_019_GBL007, MEM_DUD_ACT_019_GBL009
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_MainBlankCheck(Mem_59_Renesas_InstanceIdType LulInstanceId)           /* PRQA S 1505 # JV-01 */
{
  /* Variable to return write job result */
  #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
  Std_ReturnType LucStatus;
  #endif
  Mem_59_Renesas_FcuStatusType LenFcuStatus;

  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  Mem_59_Renesas_FlashType LenFlashType;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  /* Get pointer Sector Batch*/
  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);
  /* Determine the current type of Flash */
  LenFlashType = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].enFlashType;
  #endif

  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  if (MEM_59_RENESAS_CODE_FLASH == LenFlashType)
  #endif
  {
    #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
    LenFcuStatus = Mem_59_Renesas_FPSYS_BlankCheckCFRequest(LulInstanceId);

    if (MEM_59_RENESAS_FCU_BC_INCONSISTENT == LenFcuStatus)
    {
      /* Set the job result to internal job status */
      Mem_59_Renesas_GenJobResult[LulInstanceId] = MEM_59_RENESAS_INCONSISTENT;
    }
    else
    {
      /* Set the job result to internal job status */
      Mem_59_Renesas_GenJobResult[LulInstanceId] = MEM_59_RENESAS_JOB_OK;
    }

    /* Set the command to none */
    Mem_59_Renesas_GstVar[LulInstanceId].enGenCommand = MEM_59_RENESAS_COMMAND_NONE;
    /* Set the instance state to idle */
    Mem_59_Renesas_GenInstanceState[LulInstanceId] = MEM_59_RENESAS_IDLE;
    #endif
  }
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  else
  #endif
  {
    #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
    /* Initial value for DF status */
    LucStatus = E_OK;
    /* Invoke Mem_59_Renesas_FPSYS_GetFACINumber function with the calculated start address as an argument */
    Mem_59_Renesas_FPSYS_GetFACINumber(Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress, LulInstanceId);

    if (MEM_59_RENESAS_FALSE == Mem_59_Renesas_GstVar[LulInstanceId].blHwRequestedFlg)
    {
      /* Trigger write request to FACI */
      LucStatus = Mem_59_Renesas_FPSYS_ProcessBlankCheckDFJob(LulInstanceId);
      /* Set RFD requested flag to TRUE */
      Mem_59_Renesas_GstVar[LulInstanceId].blHwRequestedFlg = MEM_59_RENESAS_TRUE;
    }

    if (E_NOT_OK == LucStatus)
    {
      Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_FAILED);
    }
    else
    {
      /* Check if the job is completed or error or busy */
      LenFcuStatus = Mem_59_Renesas_FPSYS_FcuCheckBCJobStatus();
      if (MEM_59_RENESAS_FCU_OK == LenFcuStatus)
      {
        Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_OK);
      }
      else if (MEM_59_RENESAS_FCU_BC_INCONSISTENT == LenFcuStatus)
      {
        Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_INCONSISTENT);
      }
      else if (MEM_59_RENESAS_FCU_ERR_HW_FAILED == LenFcuStatus)
      {
        Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_FAILED);
      }
      else
      {
        Mem_59_Renesas_GulTimeOutCounter[LulInstanceId]--;                                                              /* PRQA S 3384, 3387 # JV-01, JV-01 */
        if (MEM_59_RENESAS_ZERO == Mem_59_Renesas_GulTimeOutCounter[LulInstanceId])
        {
          Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_FAILED);
        }
      }
    }
    #endif
  }
} /* End of function Mem_59_Renesas_FPSYS_MainBlankCheck */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_ProcessJobResult
**
** Service ID               : NA
**
** Description              : Function to process in case of Job Success/
**                            Failure for erase, write and read operations.
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Re-entrant
**
** Input Parameters         : LulInstanceId, LenResult
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GstVar, Mem_59_Renesas_GblFlashEnable, Mem_59_Renesas_GenInstanceState
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_FcuResetErrorBits, Mem_59_Renesas_FPSYS_FcuSwitchMode, 
**                            Mem_59_Renesas_FPSYS_SetFHVE, Mem_59_Renesas_GulTimeOutCounter
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_025, MEM_DUD_ACT_025_GBL001, MEM_DUD_ACT_025_GBL002, MEM_DUD_ACT_025_GBL003
** Reference ID             : MEM_DUD_ACT_025_GBL004, MEM_DUD_ACT_025_GBL005, MEM_DUD_ACT_025_GBL006
** Reference ID             : MEM_DUD_ACT_025_GBL007
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessJobResult(Mem_59_Renesas_InstanceIdType LulInstanceId,         /* PRQA S 1505 # JV-01 */
                                                                        const Mem_59_Renesas_JobResultType LenResult)
{
  Mem_59_Renesas_FcuStatusType LenStatus;

  /*Invoke Mem_59_Renesas_FPSYS_FcuResetErrorBits to clear error bits */
  LenStatus = Mem_59_Renesas_FPSYS_FcuResetErrorBits(LulInstanceId);

  /* Switching to User Mode */
  LenStatus |= Mem_59_Renesas_FPSYS_FcuSwitchMode(R_RFD_MODE_READ);                                                     /* PRQA S 4522, 4432 # JV-01, JV-01 */

  if (MEM_59_RENESAS_FCU_OK != LenStatus)
  {
    Mem_59_Renesas_GenJobResult[LulInstanceId] = MEM_59_RENESAS_JOB_FAILED;
  }
  else
  {
    /* Set the job result */
    Mem_59_Renesas_GenJobResult[LulInstanceId] = LenResult;
  }

  #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED)
  if (MEM_59_RENESAS_TRUE == Mem_59_Renesas_GblFlashEnable)                                                             /* PRQA S 3416 # JV-01 */
  {
    /* Enable the flash memory software protection */
    Mem_59_Renesas_FPSYS_SetFHVE(MEM_59_RENESAS_FLASH_PROTECTION_ON);
    Mem_59_Renesas_GblFlashEnable = MEM_59_RENESAS_FALSE;
  } /* else No action required */
  #endif /* #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED) */

  /* Initialization the timeout counter */
  Mem_59_Renesas_GulTimeOutCounter[LulInstanceId] = (uint32)MEM_59_RENESAS_ZERO;
  /* Set the command as None */
  Mem_59_Renesas_GstVar[LulInstanceId].enGenCommand = MEM_59_RENESAS_COMMAND_NONE;
  /* Set the instance state to idle */
  Mem_59_Renesas_GenInstanceState[LulInstanceId] = MEM_59_RENESAS_IDLE;
} /* End of function Mem_59_Renesas_FPSYS_ProcessJobResult */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_ProcessResume
**
** Service ID               : NA
**
** Description              : The function restores the job data and resumes
**                            the job
**
** Sync/Async               : Asynchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : LulInstanceId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : NA
**
** Global Variables Used    : Mem_59_Renesas_GblJobSuspendRequest, Mem_59_Renesas_GenJobResult, 
**                            Mem_59_Renesas_GstVar, Mem_59_Renesas_GenInstanceState, Mem_59_Renesas_GulTimeOutCounter
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_ResumeHwOperation, Mem_59_Renesas_FPSYS_ProcessJobResult
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_023, MEM_DUD_ACT_023_GBL001, MEM_DUD_ACT_023_GBL002, MEM_DUD_ACT_023_GBL003
** Reference ID             : MEM_DUD_ACT_023_GBL004
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessResume(Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  Std_ReturnType LenReturnValue;
  LenReturnValue = E_OK;

  #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Disable relevant DF and FACI to exit this critical section */
  MEM_59_RENESAS_ENTER_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
  #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */

  if (MEM_59_RENESAS_TRUE == Mem_59_Renesas_GstVar[LulInstanceId].blHwRequestedFlg)
  {
    LenReturnValue = Mem_59_Renesas_FPSYS_ResumeHwOperation(LulInstanceId);
  }

  if (E_OK == LenReturnValue)
  {
    /* Set the driver state to idle */
    Mem_59_Renesas_GenInstanceState[LulInstanceId] = MEM_59_RENESAS_BUSY;
    /* Set the job Result to  */
    Mem_59_Renesas_GenJobResult[LulInstanceId] = MEM_59_RENESAS_JOB_PENDING;
    /* Set suspend flag to false */
    Mem_59_Renesas_GblJobSuspendRequest[LulInstanceId] = MEM_59_RENESAS_FALSE;
    /* Set timeout counter */
    if (MEM_59_RENESAS_COMMAND_WRITE == Mem_59_Renesas_GstVar[LulInstanceId].enGenCommand)
    {
      Mem_59_Renesas_GulTimeOutCounter[LulInstanceId] = MEM_59_RENESAS_PROGRAM_TIMEOUT_COUNT;
    }
    else
    {
      Mem_59_Renesas_GulTimeOutCounter[LulInstanceId] = MEM_59_RENESAS_ERASE_TIMEOUT_COUNT;
    }
  }
  else
  {
    /* Process job fail */
    Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_FAILED);
  }

  #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enable relevant DF and FACI to exit this critical section */
  MEM_59_RENESAS_EXIT_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
  #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */
} /* End of function Mem_59_Renesas_FPSYS_ProcessResume */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_ProcessSuspend
**
** Service ID               : NA
**
** Description              : This function backs up the Job structure and
**                            clears original job structure
**
** Sync/Async               : Asynchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : LulInstanceId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : NA
**
** Global Variables Used    : Mem_59_Renesas_GstVar, Mem_59_Renesas_GenInstanceState
**                            Mem_59_Renesas_GenJobResult, Mem_59_Renesas_GblJobSuspendRequest
**
** Function(s) invoked      : Mem_59_Renesas_BackupJobData, Mem_59_Renesas_FPSYS_SuspendHwOperation,
**                            Mem_59_Renesas_FPSYS_ProcessJobResult
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_021, MEM_DUD_ACT_021_GBL001, MEM_DUD_ACT_021_GBL002, MEM_DUD_ACT_021_GBL003
** Reference ID             : MEM_DUD_ACT_021_GBL004, MEM_DUD_ACT_021_GBL005, MEM_DUD_ACT_021_GBL006
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessSuspend(Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  Std_ReturnType LenReturnValue;
  LenReturnValue = E_OK;

  if (MEM_59_RENESAS_TRUE == Mem_59_Renesas_GstVar[LulInstanceId].blHwRequestedFlg)
  {
    LenReturnValue = Mem_59_Renesas_FPSYS_SuspendHwOperation(LulInstanceId);
  }

  #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Disable relevant DF and FACI to exit this critical section */
  MEM_59_RENESAS_ENTER_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
  #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */

  if (E_OK == LenReturnValue)
  {
    /* Backup the required data in the Job Structure*/
    Mem_59_Renesas_BackupJobData(LulInstanceId);
    /* Set the command to none */
    Mem_59_Renesas_GstVar[LulInstanceId].enGenCommand = MEM_59_RENESAS_COMMAND_NONE;
    /* Set the instance state to idle */
    Mem_59_Renesas_GenInstanceState[LulInstanceId] = MEM_59_RENESAS_IDLE;
    /* Set the job Result to  */
    Mem_59_Renesas_GenJobResult[LulInstanceId] = MEM_59_RENESAS_JOB_OK;
    /* Set suspend flag */
    Mem_59_Renesas_GblJobSuspendRequest[LulInstanceId] = MEM_59_RENESAS_TRUE;
  }
  else
  {
    /* Set the job Result to FAILED but Shift Suspend State */
    Mem_59_Renesas_FPSYS_ProcessJobResult(LulInstanceId, MEM_59_RENESAS_JOB_FAILED);
  }

  #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON)
  /* Enable relevant DF and FACI to exit this critical section */
  MEM_59_RENESAS_EXIT_CRITICAL_SECTION(MEM_INTERRUPT_CONTROL_PROTECTION);
  #endif /* #if (MEM_59_RENESAS_CRITICAL_SECTION_PROTECTION == STD_ON) */
} /* End of function Mem_59_Renesas_FPSYS_ProcessSuspend */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_HwSpecificService
**
** Service ID               : NA
**
** Description              : This function invokes issues the Forced Stop
**                            Command to stop the ongoing FCU operation.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : LulInstanceId, pDataPtr, pLengthPtr
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : Mem_59_Renesas_GenInstanceState, Mem_59_Renesas_GenJobResult, Mem_59_Renesas_GstVar
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_069, MEM_DUD_ACT_069_GBL001, MEM_DUD_ACT_069_GBL002
** Reference ID             : MEM_DUD_ACT_069_GBL003, MEM_DUD_ACT_069_GBL004, MEM_DUD_ACT_069_ERR001
** Reference ID             : MEM_DUD_ACT_069_ERR002, MEM_DUD_ACT_069_ERR003
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_HwSpecificService(
  Mem_59_Renesas_InstanceIdType LulInstanceId, Mem_59_Renesas_HwServiceIdType LulHwServiceId, 
  P2VAR(Mem_59_Renesas_DataType, AUTOMATIC, MEM_APPL_DATA) pDataPtr,                                                    /* PRQA S 3432, 3673 # JV-01, JV-01 */
  P2VAR(Mem_59_Renesas_LengthType, AUTOMATIC, MEM_APPL_DATA) pLengthPtr)                                                /* PRQA S 3432, 3673 # JV-01, JV-01 */
{
  Std_ReturnType LucReturnValue;
  uint8 LenOPBTID;
  uint8 LucShiftNum;
  uint32 LulMemGroup;
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (((uint8)MEM_59_RENESAS_MIN_DATA_LENGTH_OPBT) > (*((uint8 *)pLengthPtr)))                                          /* PRQA S 0751 # JV-01 */
  {
    /* Report error to DET that the lengthPtr is invalid */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, 
                                                MEM_59_RENESAS_HW_SPECIFIC_SERVICE_SID, MEM_59_RENESAS_E_PARAM_LENGTH);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  else if ( ((*(pDataPtr + MEM_59_RENESAS_ONE)) != MEM_59_RENESAS_FRONT_SIDE) &&                                        /* PRQA S 0488 # JV-01 */
                                                    ((*(pDataPtr + MEM_59_RENESAS_ONE)) != MEM_59_RENESAS_BACK_SIDE))   /* PRQA S 0488 # JV-01 */
  {
    /* Report error to DET that the lengthPtr is invalid */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, 
                                                MEM_59_RENESAS_HW_SPECIFIC_SERVICE_SID, MEM_59_RENESAS_E_PARAM_INPUT);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  else
  #else
  /* Unused pLengthPtr if Det off */
  (void)pLengthPtr;
  #endif
  {
    LenOPBTID = (uint8)(*pDataPtr);
    switch (LulHwServiceId)
    {
      case MEM_59_RENESAS_READ_OPTION_BYTES:
          /* Set the group for option byte */
          if(LenOPBTID < (uint8)MEM_59_RENESAS_THIRTY_TWO)
          {
            LucShiftNum = LenOPBTID;
            LulMemGroup = MEM_59_RENESAS_OPBTIDGR1;
          }
          else
          {
            LucShiftNum = LenOPBTID - (uint8)MEM_59_RENESAS_THIRTY_TWO;
            LulMemGroup = MEM_59_RENESAS_OPBTIDGR2;
          }
          if (((LulMemGroup >> LucShiftNum) & (uint32)MEM_59_RENESAS_ONE) == (uint32)MEM_59_RENESAS_ONE)
          {
            /* Set the instance state to busy to accept this read request */
            Mem_59_Renesas_GenInstanceState[LulInstanceId] = MEM_59_RENESAS_BUSY;
            /* Set the job result to Job pending */
            Mem_59_Renesas_GenJobResult[LulInstanceId] = MEM_59_RENESAS_JOB_PENDING;
            /* Set the address of buffer data */
            Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress = pDataPtr;
            /* Set the command as Write command */
            Mem_59_Renesas_GstVar[LulInstanceId].enGenCommand = MEM_59_RENESAS_COMMAND_HWSPECIFIC_SERVICE;
            /* Set return value */
            LucReturnValue = E_OK;
          }
          else
          {
            #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
            /* Report error to DET that the pdata is invalid */
            (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, 
                                                  MEM_59_RENESAS_HW_SPECIFIC_SERVICE_SID, MEM_59_RENESAS_E_PARAM_INPUT);
            #endif
            LucReturnValue = E_NOT_OK;
          }
          break;
      default:
        LucReturnValue = E_MEM_59_RENESAS_SERVICE_NOT_AVAIL;
        break;
    }
  }

  return LucReturnValue;
} /* End of function Mem_59_Renesas_FPSYS_HwSpecificService */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_ProcessRead
**
** Service ID               : NA
**
** Description              : This function processes the read command for flash memory
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : Mem_59_Renesas_JobResultType
**
** Return parameter         : LenJobResult
**
** Preconditions            : None
**
** Global Variable(s) Used  : Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GstVar, Mem_59_Renesas_GpConfigPtr
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_PerformBlankCheckForReadOp, 
**                            Mem_59_Renesas_FPSYS_PerformReadCFCheckECC,
**                            Mem_59_Renesas_FPSYS_PerformReadDFCheckECC,
**                            Mem_59_Renesas_GpConfigPtr->pEccDEDNotificationPointer
**                            Mem_59_Renesas_GpConfigPtr->pEccSEDNotificationPointer
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_056,MEM_DUD_ACT_056_GBL001, MEM_DUD_ACT_056_GBL002, MEM_DUD_ACT_056_GBL003
** Reference ID             : MEM_DUD_ACT_056_GBL004, MEM_DUD_ACT_056_GBL005, MEM_DUD_ACT_056_GBL006, 
** Reference ID             : MEM_DUD_ACT_056_GBL007, MEM_DUD_ACT_056_GBL008, MEM_DUD_ACT_056_GBL009,
** Reference ID             : MEM_DUD_ACT_056_GBL010, MEM_DUD_ACT_056_GBL011, MEM_DUD_ACT_056_GBL012,
** Reference ID             : MEM_DUD_ACT_056_GBL013, MEM_DUD_ACT_056_GBL014, MEM_DUD_ACT_056_GBL015
** Reference ID             : MEM_DUD_ACT_056_GBL016
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_JobResultType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessRead(                                  /* PRQA S 1505 # JV-01 */
                                                                      Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  /* Local variable to hold the FCU Status */
  Mem_59_Renesas_FcuStatusType LenStatus;
  /* Local variable to hold return value */
  Mem_59_Renesas_JobResultType LenJobResult;
  /* Local variable to hold the loop count */
  uint32 LulCounter;
  volatile uint32 LulLoopCount;
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  Mem_59_Renesas_FlashType LenFlashType;
  #endif
  uint32 LulReadPageSize;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;

  /* Get pointer Sector Batch*/
  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  /* Determine the current type of Flash */
  LenFlashType = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].enFlashType;
  #endif
  LulReadPageSize = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].ulReadPageSize;

  /* Initialize return value */
  LenJobResult = MEM_59_RENESAS_JOB_OK;
  /* Calculate loop count from request read length */
  LulLoopCount = Mem_59_Renesas_GstVar[LulInstanceId].ulRequestedLength / (uint32)LulReadPageSize;

  do
  {
    LenStatus = Mem_59_Renesas_FPSYS_PerformBlankCheckForReadOp(LulInstanceId, 
                                                                    Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress);

    if (MEM_59_RENESAS_FCU_OK == LenStatus)
    {
      for (LulCounter = ((uint32)MEM_59_RENESAS_ZERO); LulCounter < (LulReadPageSize / (uint32)MEM_59_RENESAS_FOUR); 
                                                                                                          LulCounter++)
      {
        /* Writing the fixed pattern data to application buffer */
        *((volatile uint32 *)(Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress +                                     /* PRQA S 0310, 0311, 0488, 3305 # JV-01, JV-01, JV-01, JV-01 */
          (((uint32)MEM_59_RENESAS_FOUR) * ((uint32)LulCounter)))) = MEM_59_RENESAS_ERASED_VALUE;                       /* PRQA S 3384 # JV-01 */
      }
    }
    else
    {
      #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
      if (MEM_59_RENESAS_CODE_FLASH == LenFlashType)
      {
        /* Perform read 32 bytes and check ECC */
        LenStatus = Mem_59_Renesas_FPSYS_PerformReadCFCheckECC(LulInstanceId,                                           /* PRQA S 0404 # JV-01 */
                                                    (uint32)Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress,
                                                         (uint32)Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress);  /* PRQA S 0303 # JV-01 */
      }
      else
      {
        /* Perform read 4 bytes and check ECC */
        LenStatus = Mem_59_Renesas_FPSYS_PerformReadDFCheckECC(LulInstanceId,                                           /* PRQA S 0404 # JV-01 */
                                                    (uint32)Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress, 
                                                          (uint32)Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress); /* PRQA S 0303 # JV-01 */
      }
      #elif (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
      /* Perform read 32 bytes and check ECC */
      LenStatus = Mem_59_Renesas_FPSYS_PerformReadCFCheckECC(LulInstanceId,                                             /* PRQA S 0404 # JV-01 */
                                              (uint32)Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress,
                                                          (uint32)Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress); /* PRQA S 0303 # JV-01 */
      #elif (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
      /* Perform read 4 bytes and check ECC */
      LenStatus = Mem_59_Renesas_FPSYS_PerformReadDFCheckECC(LulInstanceId,                                             /* PRQA S 0404 # JV-01 */
                                              (uint32)Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress,
                                                          (uint32)Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress); /* PRQA S 0303 # JV-01 */
      #endif

      if ((MEM_59_RENESAS_FCU_CF_ERR_ECC_DED == LenStatus) || (MEM_59_RENESAS_FCU_DF_ERR_ECC_DED == LenStatus))
      {
        /* Set Job result to MEM_59_RENESAS_ECC_UNCORRECTED */
        LenJobResult = MEM_59_RENESAS_ECC_UNCORRECTED;
        /* Set status to OK to continue read process */
        LenStatus = MEM_59_RENESAS_FCU_OK;
        /* Call user callback */
        if (NULL_PTR != Mem_59_Renesas_GpConfigPtr->pEccDEDNotificationPointer)
        {
          /* ECC double bit error notification to the upper layer */
          Mem_59_Renesas_GpConfigPtr->pEccDEDNotificationPointer(Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress);
        } /* else No action required */
      }
      else if ((MEM_59_RENESAS_FCU_CF_ERR_ECC_SED == LenStatus) || (MEM_59_RENESAS_FCU_DF_ERR_ECC_SED == LenStatus))    /* PRQA S 2004 # JV-01 */
      {
        /* Set Job result to MEM_59_RENESAS_ECC_CORRECTED*/
        LenJobResult = MEM_59_RENESAS_ECC_CORRECTED;
        /* Set status to OK to continue read process */
        LenStatus = MEM_59_RENESAS_FCU_OK;
        /* Call user callback */
        if (NULL_PTR != Mem_59_Renesas_GpConfigPtr->pEccSEDNotificationPointer)
        {
          /* ECC single bit error notification to the upper layer */
          Mem_59_Renesas_GpConfigPtr->pEccSEDNotificationPointer(Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress);
        } /* else No action required */
      } /* else No action required */
    }
    /* Move to next address */
    Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress =
                                                  Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress + LulReadPageSize;/* PRQA S 0488 # JV-01 */
    Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress =
                                                   Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress + LulReadPageSize;/* PRQA S 3383 # JV-01 */
    LulLoopCount--;                                                                                                     /* PRQA S 3384, 3387 # JV-01, JV-01 */
  } while ((LulLoopCount > (uint32)MEM_59_RENESAS_ZERO) && (MEM_59_RENESAS_FCU_OK == LenStatus));                       /* PRQA S 3416 # JV-01 */

  return (LenJobResult);
} /* End of function Mem_59_Renesas_FPSYS_ProcessRead */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#if (MEM_59_RENESAS_READIMMEDIATE_API == STD_ON)
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_FPSYS_ProcessReadImmediate
**
** Service ID               : NA
**
** Description              : This function processes the read immediate command for flash memory
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : LulInstanceId
**
** InOut Parameters         : None
**
** Output Parameters        : Mem_59_Renesas_JobResultType
**
** Return parameter         : LenJobResult
**
** Preconditions            : None
**
** Global Variable(s) Used  : Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GstVar, Mem_59_Renesas_GpConfigPtr
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_PerformReadCFCheckECC, Mem_59_Renesas_FPSYS_PerformReadDFCheckECC
**                            Mem_59_Renesas_GpConfigPtr->pEccDEDNotificationPointer,
**                            Mem_59_Renesas_GpConfigPtr->pEccSEDNotificationPointer
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_060, MEM_DUD_ACT_060_GBL001, MEM_DUD_ACT_060_GBL002,
** Reference ID             : MEM_DUD_ACT_060_GBL003, MEM_DUD_ACT_060_GBL004, MEM_DUD_ACT_060_GBL005,
** Reference ID             : MEM_DUD_ACT_060_GBL006, MEM_DUD_ACT_060_GBL007, MEM_DUD_ACT_060_GBL008,
** Reference ID             : MEM_DUD_ACT_060_GBL009
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_JobResultType, MEM_PRIVATE_CODE) Mem_59_Renesas_FPSYS_ProcessReadImmediate(                         /* PRQA S 1505 # JV-01 */
                                                                            Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  /* Local variable to hold the FCU Status */
  Mem_59_Renesas_FcuStatusType LenStatus;
  /* Local variable to hold return value */
  Mem_59_Renesas_JobResultType LenJobResult;
  volatile uint32 LulLoopCount;
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  Mem_59_Renesas_FlashType LenFlashType;
  #endif
  uint32 LulReadPageSize;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;

  /* Get pointer Sector Batch*/
  LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[LulInstanceId].pSectorBatch);
  #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
  /* Determine the current type of Flash */
  LenFlashType = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].enFlashType;
  #endif
  LulReadPageSize = LpSectorBatch[Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx].ulReadPageSize;

  /* Initialize return value */
  LenJobResult = MEM_59_RENESAS_JOB_OK;
  /* Calculate loop count from request read length */
  LulLoopCount = Mem_59_Renesas_GstVar[LulInstanceId].ulRequestedLength / (uint32)LulReadPageSize;

  do
  {
    #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
    if (MEM_59_RENESAS_CODE_FLASH == LenFlashType)
    #endif
    #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
    {
      /* Perform read 32 bytes and check ECC */
      LenStatus = Mem_59_Renesas_FPSYS_PerformReadCFCheckECC(LulInstanceId,                                             /* PRQA S 0404 # JV-01 */
                                      (uint32)Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress,
                                                    (uint32)Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress);       /* PRQA S 0303 # JV-01 */
    }
    #endif
    #if ((MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON) &&  (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON))
    else
    #endif
    #if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
    { 
      /* Perform read 4 bytes and check ECC */  
      LenStatus = Mem_59_Renesas_FPSYS_PerformReadDFCheckECC(LulInstanceId,                                             /* PRQA S 0404 # JV-01 */
                                    (uint32)Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress,
                                                    (uint32)Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress);       /* PRQA S 0303 # JV-01 */
    }
    #endif 
  
    if ((MEM_59_RENESAS_FCU_CF_ERR_ECC_DED == LenStatus) || (MEM_59_RENESAS_FCU_DF_ERR_ECC_DED == LenStatus)) 
    { 
      /* Set Job result to MEM_59_RENESAS_ECC_UNCORRECTED */ 
      LenJobResult = MEM_59_RENESAS_ECC_UNCORRECTED; 
      /* Set status to OK to continue read process */ 
      LenStatus = MEM_59_RENESAS_FCU_OK; 
      /* Call user callback */  
      if (NULL_PTR != Mem_59_Renesas_GpConfigPtr->pEccDEDNotificationPointer)
      { 
        /* ECC double bit error notification to the upper layer */  
        Mem_59_Renesas_GpConfigPtr->pEccDEDNotificationPointer(Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress);
      } /* else No action required */ 
    } 
    else if ((MEM_59_RENESAS_FCU_CF_ERR_ECC_SED == LenStatus) || (MEM_59_RENESAS_FCU_DF_ERR_ECC_SED == LenStatus))      /* PRQA S 2004 # JV-01 */
    {
      /* Set Job result to MEM_59_RENESAS_ECC_CORRECTED*/
      LenJobResult = MEM_59_RENESAS_ECC_CORRECTED;
      /* Set status to OK to continue read process */
      LenStatus = MEM_59_RENESAS_FCU_OK;
      /* Call user callback */
      if (NULL_PTR != Mem_59_Renesas_GpConfigPtr->pEccSEDNotificationPointer)
      {
        /* ECC single bit error notification to the upper layer */
        Mem_59_Renesas_GpConfigPtr->pEccSEDNotificationPointer(Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress);
      } /* else No action required */
    } /* else No action required */

    /* Move to next address */
    Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress =
                                                  Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress + LulReadPageSize;/* PRQA S 0488 # JV-01 */
    Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress =
                                                   Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress + LulReadPageSize;/* PRQA S 3383 # JV-01 */
    LulLoopCount--;                                                                                                     /* PRQA S 3384, 3387 # JV-01, JV-01 */
  } while ((LulLoopCount > (uint32)MEM_59_RENESAS_ZERO) && (MEM_59_RENESAS_FCU_OK == LenStatus));                       /* PRQA S 3416 # JV-01 */

  return (LenJobResult);
} /* End of function Mem_59_Renesas_FPSYS_ProcessRead */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
