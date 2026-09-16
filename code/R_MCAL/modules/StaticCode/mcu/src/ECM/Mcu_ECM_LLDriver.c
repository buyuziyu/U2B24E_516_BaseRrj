/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_ECM_LLDriver.c                                                                                  */
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
 * 2.3.2:  29/04/2025   : Update SW-VERSION for U2Ax Ver22.00.03 Release
 * 2.3.1:  31/03/2025   : Update SW-VERSION for U2BxE Ver22.00.02 Release
 *                        As part of ARDAACL-54161, following changes are made:
 *                        Update function Mcu_ECMSetEcmRegister to check NULL_PTR for the ECM register
 *                        Update function Mcu_ECMClearErrorOut to check NULL_PTR for the ECM register
 * 2.3.0:  28/02/2025   : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Release
 * 2.1.2:  31/10/2024   : Update SW-VERSION to 2.1.2
 * 2.1.1:  30/08/2024   : Update SW-VERSION to 2.1.1
 *         16/07/2024   : As part of ARDAACL-47932 (ARDAACL-47792), following changes are made:
 *                        Update function Mcu_ECMSetEcmRegister to set the ECM register after initializing retention RAM
 *         12/06/2024   : As part of ARDAACL-46027 (ARDAACL-45132), following changes are made:
 *                        Update function Mcu_ECMSetEcmRegister to enable ECM maskable interrupt of FEINT for all PEn
 * 2.0.0:  04/08/2023   : Remove redundant QAC message 0791
 *                        Add QAC message 1006, 2814
 *         10/07/2023   : Remove redundant QAC message 2742, 2880, 2824, 2992
 * 1.5.0:  28/03/2023   : Add new function Mcu_ECMClearErrorValidate to setting counter clock domain
 *                        for register ECMEOCCFG/ECMETCCFGn in functions Mcu_ECMSetEcmRegister
 * 1.4.5:  06/01/2023   : As new Mcu structure:
 *                        - Update functions: Mcu_ECMClearErrorOut, Mcu_ECMSetEcmRegisterCommon,
 *                          Mcu_ECMSetEcmRegister, Mcu_ECMGetEcmResetReasonValue
 *                        - Add QAC Messages
 * 1.4.3:  23/06/2022   : Update description of QAC Message (2:0857), (4:5087), (7:0791), (2:3218), (1:1532), (2:0316),
 *                        (2:0303), (3:3416), (1:3384), (3:2004), (2:3678), (2:0715)
 *                        Add QAC Message for 0303, 2004, 2995, 2991
 *         14/06/2022   : GaaMcuEcmErrMapTable1[], GaaMcuEcmErrMapTable2[], GaaMcuEcmErrMapTable3[],
 *                        GaaMcuEcmErrMapTable4[], GaaMcuEcmErrMapTable5[], GaaMcuEcmErrMapTable6[], 
 *                        GaaMcuEcmErrMapTable7[], GaaMcuEcmErrMapTable8[]-Remove macro MCU_DEVICE_U2AX and code in side
 *                        Mcu_HW_SetEcmRegister, Mcu_HW_ClearErrorOut - Remove macro MCU_DEVICE_U2X only
 *                        and remove macro MCU_DEVICE_E2X with code inside
 *                        Remove function Mcu_HW_SetEcmEicRegister()
 *                        Mcu_HW_GetEcmResetReasonValue - Remove macro MCU_DEVICE_U2BX only,
 *                        Remove macro MCU_DEVICE_E2X, MCU_DEVICE_U2AX and code inside
 *         13/05/2022   : Updated QAC msg for 0303
 *         11/05/2022   : Removed "else" statement don't use when no action required
 *         09/05/2022   : Update wait time to check for register ECMEOCCFG/ECMETCCFGn in Mcu_HW_ClearErrorOut and
 *                        Mcu_HW_SetEcmRegister.
 *         21/04/2022   : GaaMcuEcmErrMapTable4, update to MCU_RESERVED_RST for bit 18 and bit 19
 *         13/04/2022   : Update SW-VERSION to 1.4.3; Change ECM_EOCCFG_CHECK_RETRY_MAX macro to 
 *                        MCU_ECM_EOCCFG_CHECK_RETRY_MAX according to naming rule
 * 1.3.2:  29/09/2021   : Update GaaMcuEcmErrMapTable0[] to GaaMcuEcmErrMapTable12[], 
 *                        GaaMcuEcmRamErrMask[], GaaMcuEcmRamErrMaskLram[] and 
 *                        GaaMcuEcmRamErrMaskCram support to U2Bx new device
 *                        Update function Mcu_HW_SetEcmRegister by adding new interrupt notification
 *                        Update function Mcu_HW_GetEcmResetReasonValue for new ECMM
 *                        error U2Bx device
 *                        Improve Violation tag (remove START/END) 
 * 1.3.1:  02/07/2021   : Add QAC message 9.5.0
 *                        Format source code to 120 characters
 *                        Improve Violation tag (remove START/END) 
 *         07/05/2021   : As per ARDAACL-145,
 *                        Add preprocessor for Interrupt notification 2, 3
 *                        generation setting 0..10 in Mcu_HW_SetEcmRegister
 *                        Separate casting for each device when writing to
 *                        MCU_ECMEPCFG register in Mcu_HW_SetEcmRegister.
 * 1.3.0:  15/12/2020   : Set MCU_ECMEMK0_ADDRESS = MCU_ECM_ECMEMK0_MASK
 *                        Remove redundant code line in "Mcu_HW_SetEcmRegister"
 * 1.2.0:  17/07/2020   : Release
 * 1.1.0:  19/06/2020   : Release
 * 1.0.5:  25/05/2020   : As per ticket #270238
 *                        Update level of QAC msg 0303
 *                        Add QAC msg for 0303, 0489
 *                        Fixed violation of msg 4397, 3892, 1862
 * 1.0.4:  21/05/2020   : As per ticket #271167
 *                        Update list of reset reason for E2x devices
 *                        Removed MCU_LRAM_ADR_PARITY_ERR_RST,
 *                        MCU_BARRIERSYNC_COMP_ERR_RST,
 *                        MCU_FACI_RST_TRANS_ERR_RST,
 *                        MCU_IPIR_COMP_ERR_RST
 * 1.0.3:  15/05/2020   : As per ticket #267431 revert for
 *                        Mcu_HW_GetEcmResetReasonValue due to note was added
 *                        to DUM
 * 1.0.2:  13/05/2020   : Update wait time to check for register ECMEOCCFG
 * 1.0.1:  26/04/2020   : As per #263856
 *                        + Add missing condition when checking for
 *                        Delay Timer Control setting: MCU_ECMDTMCTL
 *                        As per #263738
 *                        + Fix QAC message for Mcu_HW_GetEcmResetReasonValue
 *                        As per #263766
 *                        Fix register offset in Mcu_HW_SetEcmRegister
 *                        As per #263892
 *                        + Fix to check ECMEOCCFG/ECMETCCFGn before clearing
 *                        ECMmECLR/ECMmECLRn in Mcu_HW_ClearErrorOut.
 * 1.0.0:  10/01/2020   : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : MISRA C:2012 Rule-11.4, CERTCCM INT36, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
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
/* Message (2:1338)    : The parameter '%s' is being modified.                                                        */
/* Rule                : MISRA C:2012 Rule-17.8                                                                       */
/* JV-01 Justification : This in case, parameter is not const, it could be accepted for modification                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : MISRA C:2012 Rule-15.7, CERTCCM MSC01, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2741)    : This 'if' controlling expression is a constant expression and its value is 'true'.           */
/* Rule                : MISRA C:2012 Rule-14.3, CWE Rule CWE-571, CWE-569                                            */
/* JV-01 Justification : It is specific for device and confirmed has no issue in software behavior.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:2823)    : Suspicious: Arithmetic operation on NULL pointer.                                            */
/* Rule                : MISRA C:2012 Rule-1.3, Dir-4.1, CWE-468, CWE-476, CWE-1157, CWE-465                          */
/* JV-01 Justification : The pointer needs to be initialized before using it.                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
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
/* Message (2:2842)    : Apparent: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127,       */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : It is specific for device register accessing and confirmed has no issue in software behavior.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2843)    : Suspicious: Dereference of an invalid pointer value.                                         */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127,       */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : It is specific for device register accessing and confirmed has no issue in software behavior.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
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
#define MCU_ECM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    MCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define MCU_ECM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    MCU_AR_RELEASE_MINOR_VERSION_VALUE
#define MCU_ECM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MCU_ECM_LLDRIVER_C_SW_MAJOR_VERSION            MCU_SW_MAJOR_VERSION_VALUE
#define MCU_ECM_LLDRIVER_C_SW_MINOR_VERSION            MCU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (MCU_ECM_LLDRIVER_AR_RELEASE_MAJOR_VERSION != MCU_ECM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "MCU_ECM_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (MCU_ECM_LLDRIVER_AR_RELEASE_MINOR_VERSION != MCU_ECM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "MCU_ECM_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (MCU_ECM_LLDRIVER_AR_RELEASE_REVISION_VERSION != MCU_ECM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "MCU_ECM_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (MCU_ECM_LLDRIVER_SW_MAJOR_VERSION != MCU_ECM_LLDRIVER_C_SW_MAJOR_VERSION)
#error "MCU_ECM_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (MCU_ECM_LLDRIVER_SW_MINOR_VERSION != MCU_ECM_LLDRIVER_C_SW_MINOR_VERSION)
#error "MCU_ECM_LLDriver.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (MCU_ECM_OPERATION == STD_ON)

#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_ECMClearErrorOut(void);

STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_ECMClearErrorValidate(void);

STATIC FUNC(void, MCU_PRIVATE_CODE) Mcu_ECMSetEcmRegisterCommon(
  CONST(uint32, MCU_CONST) LulEcmRegAddress,
  CONST(uint8, MCU_CONST) LucEcmSetType,
  P2CONST(uint32, MCU_CONST, MCU_CONFIG_DATA) LpEcmSettingRegValue);

#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/**********************************************************************************************************************/
/**                                             Internal Function Prototypes                                         **/
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name      : Mcu_ECMSetEcmRegister
**
** Service ID         : None
**
** Description        : This service set ECM register.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LucEcmSetType
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : Std_ReturnType (E_OK, E_NOT_OK)
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpConfigPtr, GaaMcuEcmRamErrMask, GaaMcuEcmRamErrMaskLram, GaaMcuEcmRamErrMaskCram
**
** Function Invoked   : Mcu_ECMClearErrorOut, Mcu_ECMSetEcmRegisterCommon, Mcu_ECMClearErrorValidate
**
** Registers Used     : ECMKCPROT, ECMEPCFG, ECMDTMCTL, ECMDTMCMP, ECMDTMCTL, ECMEOCCFG
**
** Reference ID       : MCU_DUD_ACT_085
** Reference ID       : MCU_DUD_ACT_085_REG001, MCU_DUD_ACT_085_REG002,
** Reference ID       : MCU_DUD_ACT_085_REG003, MCU_DUD_ACT_085_REG004,
** Reference ID       : MCU_DUD_ACT_085_REG005, MCU_DUD_ACT_085_REG006,
** Reference ID       : MCU_DUD_ACT_085_REG007, MCU_DUD_ACT_085_REG008
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_ECMSetEcmRegister(CONST(uint8, MCU_CONST) LucEcmSetType)                     /* PRQA S 3006 # JV-01 */
{
  Std_ReturnType LucReturnValue;
  uint8 LucCount;
  uint8 LucPeCount;
  P2CONST(volatile Mcu_EcmHwInfoType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmHwInfo;
  P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_DATA) LpEcmSetting;
  P2CONST(Mcu_EcmCommonRegType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmCommonRegSetting;
  P2CONST(Mcu_EcmCommonRegType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmCommonDelayTimerRegSetting;
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpFeIntRegAddress;
  
  /* Initialize return value with E_OK */
  LucReturnValue = E_OK;
  /* Get the address to ECM configuration structure */
  LpEcmSetting = (P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_CONST))(Mcu_GpConfigPtr->pEcmSetting);              /* PRQA S 0316 # JV-01 */
  LpEcmHwInfo = (P2CONST(Mcu_EcmHwInfoType, MCU_CONST, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pEcmHwInfo;                    /* PRQA S 0316 # JV-01 */

  if (MCU_ECM_SETTING_INIT == LucEcmSetType)
  {
    LpEcmCommonRegSetting = LpEcmSetting->pEcmCommonRegInitSetting;
    LpEcmCommonDelayTimerRegSetting = LpEcmSetting->pEcmCommonDelayTimerRegInitSetting;
  }
  else if (MCU_ECM_SETTING_AFTER_RAMINIT_LRAM == LucEcmSetType)
  {
    LpEcmCommonRegSetting = LpEcmSetting->pEcmCommonRegAfterInitLramSetting;
    LpEcmCommonDelayTimerRegSetting = LpEcmSetting->pEcmCommonDelayTimerRegAfterInitLramSetting;
  }
  #if (MCU_RETENTION_RAM_SETTING == STD_ON)
  else if (MCU_ECM_SETTING_AFTER_RAMINIT_RRAM == LucEcmSetType)
  {
    LpEcmCommonRegSetting = LpEcmSetting->pEcmCommonRegAfterInitRramSetting;
    LpEcmCommonDelayTimerRegSetting = LpEcmSetting->pEcmCommonDelayTimerRegAfterInitRramSetting;
  }
  #endif /* MCU_RETENTION_RAM_SETTING == STD_ON */
  else
  {
    LpEcmCommonRegSetting = LpEcmSetting->pEcmCommonRegAfterInitCramSetting;
    LpEcmCommonDelayTimerRegSetting = LpEcmSetting->pEcmCommonDelayTimerRegAfterInitCramSetting;
  }

  /* Clear Error Out */
  if (MCU_ECM_SETTING_INIT == LucEcmSetType)
  {
    LucReturnValue = Mcu_ECMClearErrorOut();
  } /* else No action is required */

  if (E_OK == LucReturnValue)
  {
    /* Release Register Access Protection */
    *LpEcmHwInfo->pECMKCPROTReg = MCU_ECM_DISABLE_REG_PROTECT_VALUE;

    /* Setting Error Output Operation Mode */
    if (MCU_ECM_SETTING_INIT == LucEcmSetType)
    {
      /* Error pin operation configuration */
      *LpEcmHwInfo->pECMEPCFGReg = (uint32)LpEcmSetting->ucEcmErrorOutputMode;
    } /* else No action is required */

    /* Enable(Clear) ECM maskable interrupt for FEINT */
    LpFeIntRegAddress = LpEcmHwInfo->pFEINTMSK0Reg;
    for (LucPeCount = MCU_ZERO; LucPeCount < MCU_ECM_CORE_NUM; LucPeCount++)
    {
      if (MCU_TRUE == LpEcmSetting->aaFEIntEnable[LucPeCount][LucEcmSetType])
      {
        *LpFeIntRegAddress &= (uint32)(~(MCU_ECM_INT_MASK_FE_VALUE));
      } /* else No action is required */
      LpFeIntRegAddress += MCU_ECM_FEINTMSK_OFFSET;                                                                     /* PRQA S 0488 # JV-01 */
    }

    /* Enable(Clear) ECM maskable interrupt for IMR0 bit8 & bit 9 */
    if (MCU_TRUE == LpEcmSetting->aaEIIntEnable[LucEcmSetType])
    {
      /* Enable(Clear) ECM maskable interrupt for IMR0 bit8 & bit 9 */
      RH850_SV_MODE_IMR_AND                                                                                             /* PRQA S 0303, 0404 # JV-01, JV-01 */
      (32, (uint32)(LpEcmHwInfo->pIMR0Reg),((uint32)(~(MCU_ECM_INT_MASK_EIC8_VALUE | MCU_ECM_INT_MASK_EIC9_VALUE))));   /* PRQA S 3464 # JV-01 */
      /*  Dummy read */
      RH850_SV_MODE_REG_READ_ONLY(32, (uint32)(LpEcmHwInfo->pIMR0Reg));                                                 /* PRQA S 0303, 0404 # JV-01, JV-01 */
      /* Execute syncp*/
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */
    } /* else No action is required */

    if (((MCU_ECM_SETTING_INIT == LucEcmSetType) && (MCU_TRUE == LpEcmSetting->aaEIDCLSIntEnable[LucEcmSetType])) ||
          (MCU_TRUE == LpEcmSetting->aaEIC8IntEnable[LucEcmSetType]))
    {
      /* Enable(Clear) ECM maskable interrupt for EIC8 */
      RH850_SV_MODE_ICR_AND(8, (uint32)(LpEcmHwInfo->pEIC8Reg), (uint8)(~MCU_ECM_EIC_L_EIMK_MASK));                     /* PRQA S 0303, 0404, 3464 # JV-01, JV-01, JV-01 */

      /*  Dummy read */
      RH850_SV_MODE_REG_READ_ONLY(8, (uint32)(LpEcmHwInfo->pEIC8Reg));                                                  /* PRQA S 0303, 0404 # JV-01, JV-01 */
      /* Execute syncp*/
      EXECUTE_SYNCP();                                                                                                  /* PRQA S 1006 # JV-01 */

      if ((MCU_ECM_SETTING_INIT == LucEcmSetType) && (MCU_TRUE == LpEcmSetting->aaEIDCLSIntEnable[LucEcmSetType]))
      {
        /* Enable(Clear) ECM DCLS error maskable interrupt for EIC9 */
        RH850_SV_MODE_ICR_AND(8, (uint32)(LpEcmHwInfo->pEIC9Reg), (uint8)(~MCU_ECM_EIC_L_EIMK_MASK));                   /* PRQA S 0303, 0404, 3464 # JV-01, JV-01, JV-01 */

        /* Dummy read */
        RH850_SV_MODE_REG_READ_ONLY(8, (uint32)(LpEcmHwInfo->pEIC9Reg));                                                /* PRQA S 0303, 0404 # JV-01, JV-01 */
        /* Execute syncp */
        EXECUTE_SYNCP();                                                                                                /* PRQA S 1006 # JV-01 */
      } /* else No action is required */
    } /* else No action is required */

    for(LucCount = MCU_ZERO; (LucCount < MCU_ECM_COMMON_REG_LOOP_NUM); LucCount++)
    {
      /* Interrupt notification configuration register */
      /* Interrupt type generation setting */
      /* MI Interrupt generation setting */
      /* NMI Interrupt generation setting */
      /* Internal reset generation setting */
      /* Error output signal mask setting */
      /* Error trigger mask setting */
      if (NULL_PTR != (LpEcmCommonRegSetting[LucCount].pEcmCommonReg))
      {
        Mcu_ECMSetEcmRegisterCommon((uint32)(LpEcmCommonRegSetting[LucCount].pEcmCommonReg), LucEcmSetType,             /* PRQA S 0303 # JV-01 */
                                      &(LpEcmCommonRegSetting[LucCount].aaEcmRegisterValue[0]));
      }
    }

    if (MCU_ECM_DTMCTL_DELAYTIMER_ENABLE_VALUE == LpEcmSetting->ucEcmDelayTimerCtrl)
    {
      /* Setting when Init timing */
      if (MCU_ECM_SETTING_INIT == LucEcmSetType)
      {
        if (MCU_ECM_DTM_DELAYTIMER_STARTED != (*LpEcmHwInfo->pECMDTMCMPReg & MCU_ECM_DTM_DELAYTIMER_STATUS_MASK))       /* PRQA S 0404 # JV-01 */
        {
          /* Delay Timer Compare Value setting */
          *LpEcmHwInfo->pECMDTMCMPReg = LpEcmSetting->ulEcmDelayTimerOverflowValue;
        }
        else
        {
          /* Delay Timer Compare register already set */
          LucReturnValue = E_NOT_OK;
        }
        if (MCU_ECM_DTMCTL_DELAYTIMER_NOT_STARTED ==                                                                    /* PRQA S 0404 # JV-01 */
            ((uint32)(*LpEcmHwInfo->pECMDTMCTLReg) & MCU_ECM_DTMCTL_DELAYTIMER_WR_STATUS_MASK))
        {
          /* Delay Timer Control setting */
          *LpEcmHwInfo->pECMDTMCTLReg = MCU_ECM_DTMCTL_DELAYTIMER_ENABLE_VALUE;
        }
        else if (!(MCU_ECM_DTMCTL_DELAYTIMER_STARTED ==                                                                 /* PRQA S 0404, 2004 # JV-01, JV-01 */
                 ((uint32)(*LpEcmHwInfo->pECMDTMCTLReg) & MCU_ECM_DTMCTL_DELAYTIMER_WR_STATUS_MASK)))
        {
          /* When bit (DTMSTA, DTMSTACNTCLK) = (0,0) or (1, 1) are not satisfied. */
          LucReturnValue = E_NOT_OK;
        } /* else No action is required since delaytimer already stared */
      } /* else No action required */

      /* Delay Timer setting for each error source */
      if (E_OK == LucReturnValue)
      {
        Mcu_ECMSetEcmRegisterCommon((uint32)(LpEcmCommonDelayTimerRegSetting[MCU_ZERO].pEcmCommonReg), LucEcmSetType,   /* PRQA S 0303 # JV-01 */
                                      &(LpEcmCommonDelayTimerRegSetting[MCU_ZERO].aaEcmRegisterValue[0]));
      } /* else No action required */
    } /* else No action required */

    /* Setting ECM Error Trigger n Clear invalidation and ECM Error Output Clear invalidation*/
    if ((E_OK == LucReturnValue) && (MCU_ECM_SETTING_INIT == LucEcmSetType))
    {
      LucReturnValue = Mcu_ECMClearErrorValidate();
    } /* else No action is required */

    /* Hold Register Access protection */
    *LpEcmHwInfo->pECMKCPROTReg = MCU_ECM_ENABLE_REG_PROTECT_VALUE;
  }
  /* Return the value of ECM Register setting result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_ECMGetEcmResetReasonValue
**
** Service ID         : None
**
** Description        : This service return ECM Reset Reason from ECMMESSTRn register.
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
** Return parameter   : Mcu_ResetType
**
** Preconditions      : None
**
** Global Variables   : Mcu_GpConfigPtr, GaaMcuEcmErrMapTableX
**
** Function Invoked   : None
**
** Registers Used     : ECMMESSTRn, ECMESSTCn, ECMKCPROT
**
** Reference ID       : MCU_DUD_ACT_086, MCU_DUD_ACT_086_REG001,
** Reference ID       : MCU_DUD_ACT_086_REG002
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Mcu_ResetType, MCU_PRIVATE_CODE) Mcu_ECMGetEcmResetReasonValue(void)
{
  Mcu_ResetType LddResetSource;
  P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_DATA) LpEcmSetting;
  P2CONST(Mcu_EcmStatusType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmErrMap;
  P2CONST(volatile Mcu_EcmHwInfoType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmHwInfo;
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmStatusRegAddr;                                                /* PRQA S 3678 # JV-01 */
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmStatusClearRegAddr;
  uint32 LulEcmErrorStatus;
  uint8 LucECMCount;
  uint8 LucCount;
  uint32 LulSaveEcmKeyProtReg;
  uint8 LucEcmResetCount;

  /* Get the address to ECM configuration structure */
  LpEcmSetting = (P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_DATA))(Mcu_GpConfigPtr->pEcmSetting);               /* PRQA S 0316 # JV-01 */
  LpEcmHwInfo = (P2CONST(Mcu_EcmHwInfoType, MCU_CONST, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pEcmHwInfo;                    /* PRQA S 0316 # JV-01 */
  LucEcmResetCount = MCU_ZERO;
  LddResetSource = MCU_NON_RST;

  /* Set ECMMESSTR0 register address */
  LpEcmStatusRegAddr = LpEcmHwInfo->pECMMESSTR0Reg;
  LpEcmStatusClearRegAddr = LpEcmHwInfo->pECMESSTC0Reg;

  /* check ECMMESSTR0..j */
  for (LucECMCount = MCU_ZERO; LucECMCount < MCU_ECM_COMMON_REG_NUM; LucECMCount++)
  {
    /* Get the value of ECM0 error status data */
    LulEcmErrorStatus = *LpEcmStatusRegAddr &
                          LpEcmSetting->aaEcmInternalResetRegValue[LucECMCount];

    if (MCU_LONG_WORD_ZERO != LulEcmErrorStatus)
    {
      LpEcmErrMap = &Mcu_GaaMcuEcmErrMapTable[LucECMCount][MCU_ZERO];

      /* mapping between ECM Error status and McuResetType */
      for (LucCount = MCU_ZERO; LucCount < MCU_THIRTYTWO; LucCount++)
      {
        if ((LulEcmErrorStatus & (MCU_LONG_WORD_ONE << LucCount)) == LpEcmErrMap[LucCount].ulEcmBit)
        {
          if  (MCU_RESERVED_RST != LpEcmErrMap[LucCount].enMcuRst)
          {
            /* Set the value of reset reason */
            LddResetSource = LpEcmErrMap[LucCount].enMcuRst;
            LulSaveEcmKeyProtReg = *Mcu_GpEcmHwInfo->pECMKCPROTReg;                                                     /* PRQA S 0404 # JV-01 */

            /* Release Register Access Protection */
            *Mcu_GpEcmHwInfo->pECMKCPROTReg = MCU_ECM_DISABLE_REG_PROTECT_VALUE;

            /* Clear status for ECM */
            *LpEcmStatusClearRegAddr = (uint32)(MCU_LONG_WORD_ONE << (uint32)LucCount);

            /* Hold Register Access protection */
            *Mcu_GpEcmHwInfo->pECMKCPROTReg = LulSaveEcmKeyProtReg | MCU_ECM_ENABLE_REG_PROTECT_VALUE;

            /* Increase the count value for the ECM reset */
            LucEcmResetCount++;                                                                                         /* PRQA S 3383 # JV-01 */
          } /* else No action required */
        } /* else No action required */
      } /* else No action required */
    } /* else No action required */

    /* Increment the value of index */
    LpEcmStatusRegAddr++;
    LpEcmStatusClearRegAddr++;
  }

  /* Check if mutiple ECM reset occured */
  if (LucEcmResetCount > MCU_ONE)
  {
    LddResetSource = MCU_MULTI_RST;
  } /* else No action required */

  return (LddResetSource);
}

#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_ECMClearErrorOut
**
** Service ID         : None
**
** Description        : Clear ERROROUT_M and ERROROUT_C
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
** Global Variables   : None
**
** Function Invoked   : None
**
** Registers Used     : ECMKCPROT, ECMPEM, ECMEMKn, ECMMICFG9, ECMNMICFG9, ECMIRCFG9, ECMMECLR, ECMCECLR, ECMMESSTR9
**                      ECMCESSTR9, ECMEOCCFG, ECMETCCFGn
**
** Reference ID       : MCU_DUD_ACT_087,
** Reference ID       : MCU_DUD_ACT_087_REG001, MCU_DUD_ACT_087_REG002,
** Reference ID       : MCU_DUD_ACT_087_REG003, MCU_DUD_ACT_087_REG004,
** Reference ID       : MCU_DUD_ACT_087_REG005, MCU_DUD_ACT_087_REG006,
** Reference ID       : MCU_DUD_ACT_087_REG007, MCU_DUD_ACT_087_REG008
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_ECMClearErrorOut(void)
{
  Std_ReturnType LucReturnValue;
  uint8 LucCount;
  uint8 LucIndex;
  uint8 LucRegCount;
  volatile uint32 LulEcmRegValue;
  volatile uint32 LulEcmMasterRegValue;

  #if (MCU_ECM_ERROROUTC_CLEAR_VERIFY == STD_ON)
  volatile uint32 LulEcmCheckerRegValue;
  #endif /* Mcu_ECM_ERROROUTC_CLEAR_VERIFY == STD_ON */
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmRegAddress;
  P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_DATA) LpEcmSetting;
  P2CONST(Mcu_EcmErrorOutClearRegType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmErrorOutClearRegTypeSetting;
  uint8 LucLoopCount;
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpBackupRegAddress;
  P2CONST(volatile Mcu_EcmHwInfoType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmHwInfo;

  /* Initialize return value with E_OK */
  LucReturnValue = E_OK;                                                                                                /* PRQA S 2982 # JV-01 */

  LpEcmSetting = (P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_DATA))(Mcu_GpConfigPtr->pEcmSetting);               /* PRQA S 0316 # JV-01 */
  LpEcmErrorOutClearRegTypeSetting = LpEcmSetting->pEcmErrorOutClearRegTypeSetting;

  /* Get the address to ECM configuration structure */
  LpEcmHwInfo = (P2CONST(Mcu_EcmHwInfoType, MCU_CONST, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pEcmHwInfo;                    /* PRQA S 0316 # JV-01 */

  /* Initialize the following variables */
  LucReturnValue = E_OK;

  /* Release Register Access Protection */
  *LpEcmHwInfo->pECMKCPROTReg = MCU_ECM_DISABLE_REG_PROTECT_VALUE;

  /* Check if setting to counter clock domain is in-progress */
  LucIndex = MCU_ECM_EOCCFG_CHECK_RETRY_MAX;
  while ((MCU_ECM_EOCCFG_COUNTER_UPDATING == (*LpEcmHwInfo->pECMEOCCFGReg & MCU_ECM_EOCCFG_COUNTER_CMPW_MASK)) &&       /* PRQA S 0404 # JV-01 */
          (LucIndex > MCU_ZERO))
  {
    LucIndex--;
  }
  /* Check if ECMEOCCFG register is not set */
  if (MCU_ECM_EOCCFG_COUNTER_UPDATING !=                                                                                /* PRQA S 0404 # JV-01 */
    (*LpEcmHwInfo->pECMEOCCFGReg & MCU_ECM_EOCCFG_COUNTER_CMPW_MASK))
  {
    /* Set ECMEOCCFG register to all 0 */
    *LpEcmHwInfo->pECMEOCCFGReg = MCU_LONG_WORD_ZERO;
  }
  else
  {
    /* ECMEOUTCLRT update is in progress */
    LucReturnValue = E_NOT_OK;
  }

  if ((E_OK == LucReturnValue) && (MCU_ONE != MCU_ECM_ERROR_TRIGGER_NUM))
  {
    LpEcmRegAddress = LpEcmHwInfo->pECMETCCFG0Reg;
    for(LucCount = MCU_ZERO; (LucCount < MCU_ECM_ERROR_TRIGGER_NUM) && (LucReturnValue == E_OK); LucCount++)
    {
      /* Check if setting to counter clock domain is in-progress */
      LucIndex = MCU_ECM_ETCCFG_CHECK_RETRY_MAX;
      while ((MCU_ECM_ETCCFG_COUNTER_UPDATING == ((*LpEcmRegAddress) & MCU_ECM_ETCCFG_COUNTER_CMPW_MASK)) &&
              (LucIndex > MCU_ZERO))
      {
        LucIndex--;
      }
      /* Check if ECMETCCFGn register is not set */
      if (MCU_ECM_ETCCFG_COUNTER_UPDATING !=
         ((*LpEcmRegAddress) & MCU_ECM_ETCCFG_COUNTER_CMPW_MASK))
      {
        /* Clear ECMETCCFGn register to all 0 */
        *LpEcmRegAddress = MCU_LONG_WORD_ZERO;
        LpEcmRegAddress++;
      }
      else
      {
        /* ECMETRGCLRT update is in progress */
        LucReturnValue = E_NOT_OK;
      }
    }
  } /* else No action required */

  if (E_OK ==  LucReturnValue)
  {
    /* ECMPEM register set to masked */
    *LpEcmHwInfo->pECMPEMReg = MCU_ECM_ECMPEM_ERROR_MASK_VALUE;

    /* Disable error output signal mask for ECM compare error */
    /* Error output signal mask setting */
    LpEcmRegAddress = LpEcmHwInfo->pECMEMK0Reg;

    for (LucCount = MCU_ZERO; LucCount < MCU_ECM_COMMON_REG_NUM; LucCount++)
    {
      if (MCU_ZERO == LucCount)
      {
        *LpEcmRegAddress = MCU_ECM_ECMEMK0_MASK;
      }
      else
      {
        *LpEcmRegAddress = MCU_ECM_ECMEMK_ALL_MASK;
      }
      /* next ECMEMKx register */
      LpEcmRegAddress++;
    }
  } /* else No action required */

  if (E_OK == LucReturnValue)
  {
    for (LucRegCount = MCU_ZERO; LucRegCount < MCU_ECM_ERROROUT_CLEAR_NUM; LucRegCount++)
    {
      LpEcmRegAddress = LpEcmErrorOutClearRegTypeSetting[LucRegCount].pEcmErrorOutClearReg;
      for (LucCount = MCU_ZERO; LucCount < LpEcmErrorOutClearRegTypeSetting[LucRegCount].ucEcmErrorOutZNum; LucCount++)
      {
        /* Backup old error trigger register address */
        LpBackupRegAddress = LpEcmRegAddress;
        for (LucLoopCount = MCU_ZERO;
                        LucLoopCount < LpEcmErrorOutClearRegTypeSetting[LucRegCount].ucEcmCommonRegNum; LucLoopCount++)
        {
          if (NULL_PTR != LpEcmRegAddress)
          {
            if (MCU_TRUE == LpEcmErrorOutClearRegTypeSetting[LucRegCount].blEcmDisableInt)
            {
              /* Error trigger mask setting */
              /* Disable interrupt generate for ECM compare error */
              /* Disable MI interrupt generate for ECM compare error */
              /* Disable NMI interrupt generate for ECM compare error */
              /* Disable internal reset generate for ECM compare error */
              /* ERROR OUT Clear (ECM master/checker error clear trigger register) */
              *LpEcmRegAddress &= LpEcmErrorOutClearRegTypeSetting[LucRegCount].ulEcmErrorOutClearValue;
            }
            else
            {
              *LpEcmRegAddress = LpEcmErrorOutClearRegTypeSetting[LucRegCount].ulEcmErrorOutClearValue;
            }
          }
          /* next ECMj register */
          LpEcmRegAddress++;                                                                                            /* PRQA S 2823 # JV-01 */
        }
        /* next ECMi register */
        LpEcmRegAddress = (volatile uint32 *)
                          (LpBackupRegAddress + LpEcmErrorOutClearRegTypeSetting[LucRegCount].ulEcmErrorOutClearOffset);/* PRQA S 0488 # JV-01 */
      }
    }
  }

   /* Hold Register Access Protection */
  *LpEcmHwInfo->pECMKCPROTReg = MCU_ECM_ENABLE_REG_PROTECT_VALUE;
  
  /* Read 5 times ECM status register */
  for (LucCount = MCU_ZERO; LucCount < MCU_ECM_ESSTR_COUNT; LucCount++)
  {
    LulEcmMasterRegValue = *LpEcmHwInfo->pECMMESSTRjReg;                                                                /* PRQA S 0404 # JV-01 */
    #if (MCU_ECM_ERROROUTC_CLEAR_VERIFY == STD_ON)
    LulEcmCheckerRegValue = *LpEcmHwInfo->pECMCESSTRjReg;                                                               /* PRQA S 0404 # JV-01 */
    #endif /* MCU_ECM_ERROROUTC_CLEAR_VERIFY == STD_ON */
  }
  /* Check ERROROUT status */
  LulEcmMasterRegValue = *LpEcmHwInfo->pECMMESSTRjReg;                                                                  /* PRQA S 0404 # JV-01 */

  #if (MCU_ECM_ERROROUTC_CLEAR_VERIFY == STD_ON)
  if ((MCU_ECM_ESSTR_ERROUT_MASK != (MCU_ECM_ESSTR_ERROUT_MASK & LulEcmMasterRegValue)) ||                              /* PRQA S 3416 # JV-01 */
      (MCU_ECM_ESSTR_ERROUT_MASK != (MCU_ECM_ESSTR_ERROUT_MASK & LulEcmCheckerRegValue)))                               /* PRQA S 3415, 3416 # JV-01, JV-01 */
  #else
  if ((MCU_ECM_ESSTR_ERROUT_MASK != (MCU_ECM_ESSTR_ERROUT_MASK & LulEcmMasterRegValue)))                                /* PRQA S 3416 # JV-01 */
  #endif /* MCU_ECM_ERROROUTC_CLEAR_VERIFY == STD_ON */
  {
    /* ERROROUT not cleared */
    LucReturnValue = E_NOT_OK;
  } /* else No action required */
  /* Set MSKM bit and MSKC bit of the ECMPEM register */
  /* ECMPEM register set to masked */
  LulEcmRegValue = (uint32)MCU_ZERO;
  *LpEcmHwInfo->pECMPEMReg = LulEcmRegValue;                                                                            /* PRQA S 0404 # JV-01 */

  /* Return the value of ECM ERROROUT Clear result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_ECMSetEcmRegisterCommon
**
** Service ID         : None
**
** Description        : This service set ECM register for each function.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LulEcmRegAddress     - top address of target register
**                      LucEcmSetType        - select setting type of ECM
**                      LpEcmSettingRegValue - pointer of register setting value for LulEcmRegAddress
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : void
**
** Preconditions      : None
**
** Global Variables   : GaaMcuEcmRamErrMask, GaaMcuEcmRamErrMaskLram, GaaMcuEcmRamErrMaskCram
**
** Function Invoked   : None
**
** Registers Used     : ECMMICFGn, ECMNMICFGn, ECMIRCFGn, ECMEMKn, ECMMIDTMCFGn, ECMNMIDTMCFGn, ECMISCFGj, ECMINCFGi_j,
**                      ECMIRCFGj, ECMEMKj, ECMETMKn_j, ECMDTMCFGj.
** Reference ID       : MCU_DUD_ACT_088
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(void, MCU_PRIVATE_CODE) Mcu_ECMSetEcmRegisterCommon(
  CONST(uint32, MCU_CONST) LulEcmRegAddress,
  CONST(uint8, MCU_CONST) LucEcmSetType,
  P2CONST(uint32, MCU_CONST, MCU_CONFIG_DATA) LpEcmSettingRegValue)
{
  uint8 LucCount;
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmRegAddress;

  LpEcmRegAddress = (volatile uint32 *)LulEcmRegAddress;                                                                /* PRQA S 0303 # JV-01 */

  if (MCU_ECM_SETTING_INIT == LucEcmSetType)
  {
    for (LucCount = MCU_ZERO; LucCount < MCU_ECM_COMMON_REG_NUM; LucCount++)
    {
      *LpEcmRegAddress = *LpEcmSettingRegValue;

      /* next ECM register */
      LpEcmRegAddress++;
      LpEcmSettingRegValue++;                                                                                           /* PRQA S 1338 # JV-01 */
    }
  }
  else
  {
    for (LucCount = MCU_ZERO; LucCount < MCU_ECM_COMMON_REG_NUM; LucCount++)
    {
      *LpEcmRegAddress |= *LpEcmSettingRegValue;

      /* next ECM register */
      LpEcmRegAddress++;
      LpEcmSettingRegValue++;                                                                                           /* PRQA S 1338 # JV-01 */
    }
  }
  return;
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Mcu_ECMClearErrorValidate
**
** Service ID         : None
**
** Description        : This service support to set error output and error trigger clear invalidation counter
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
** Global Variables   : Mcu_GpConfigPtr
**
** Function Invoked   : None
**
** Registers Used     : ECMEOCCFG, ECMETCCFGn 
**
** Reference ID       : MCU_DUD_ACT_089
** Reference ID       : MCU_DUD_ACT_089_REG001, MCU_DUD_ACT_089_REG002
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
STATIC FUNC(Std_ReturnType, MCU_PRIVATE_CODE) Mcu_ECMClearErrorValidate(void)
{
  Std_ReturnType LucReturnValue;
  uint8 LucCount;
  uint8 LucIndex;
  P2CONST(volatile Mcu_EcmHwInfoType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmHwInfo;
  P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_DATA) LpEcmSetting;
  P2CONST(Mcu_EcmErrorOutClrConfigRegType, AUTOMATIC, MCU_CONFIG_DATA) LpEcmErrorOutClrConfigRegSetting;
  P2VAR(volatile uint32, AUTOMATIC, MCU_CONFIG_DATA) LpEcmRegAddress;

  /* Initialize return value with E_OK */
  LucReturnValue = E_OK;
  /* Get the address to ECM configuration structure */
  LpEcmSetting = (P2CONST(Mcu_EcmSettingType, MCU_CONST, MCU_CONFIG_CONST))(Mcu_GpConfigPtr->pEcmSetting);              /* PRQA S 0316 # JV-01 */
  LpEcmHwInfo = (P2CONST(Mcu_EcmHwInfoType, MCU_CONST, MCU_CONFIG_DATA))Mcu_GpConfigPtr->pEcmHwInfo;                    /* PRQA S 0316 # JV-01 */

  /* Check if setting to counter clock domain is in-progress */
  LucIndex = MCU_ECM_EOCCFG_CHECK_RETRY_MAX;
  while ((MCU_ECM_EOCCFG_COUNTER_UPDATING == (*LpEcmHwInfo->pECMEOCCFGReg & MCU_ECM_EOCCFG_COUNTER_CMPW_MASK)) &&       /* PRQA S 0404 # JV-01 */
          (LucIndex > MCU_ZERO))
  {
    LucIndex--;
  }
  /* Check if ECMEOCCFG register is not set */
  if (MCU_ECM_EOCCFG_COUNTER_UPDATING != (*LpEcmHwInfo->pECMEOCCFGReg & MCU_ECM_EOCCFG_COUNTER_CMPW_MASK))              /* PRQA S 0404 # JV-01 */
  {
    /* Error Output Clear Mask Count setting */
    *LpEcmHwInfo->pECMEOCCFGReg = LpEcmSetting->ulEcmErrorOutClrMaskCntValue;
  }
  else
  {
    /* ECMEOUTCLRT update is in progress */
    LucReturnValue = E_NOT_OK;
  }

  if ((E_OK == LucReturnValue) && (MCU_ONE != MCU_ECM_ERROR_TRIGGER_NUM))
  {
    LpEcmErrorOutClrConfigRegSetting = LpEcmSetting->pEcmErrorOutClrConfigRegSetting;
    LpEcmRegAddress = LpEcmErrorOutClrConfigRegSetting[0].pEcmErrorOutClrConfigReg;
    for(LucCount = MCU_ZERO; (LucCount < MCU_ECM_ERROR_TRIGGER_NUM) && (LucReturnValue == E_OK); LucCount++)
    {
      /* Check if setting to counter clock domain is in-progress */
      LucIndex = MCU_ECM_ETCCFG_CHECK_RETRY_MAX;
      while ((MCU_ECM_ETCCFG_COUNTER_UPDATING == ((*LpEcmRegAddress) & MCU_ECM_ETCCFG_COUNTER_CMPW_MASK)) &&
              (LucIndex > MCU_ZERO))
      {
        LucIndex--;
      }
      /* Check if ECMETCCFGn register is not set */
      if (MCU_ECM_ETCCFG_COUNTER_UPDATING != ((*LpEcmRegAddress) & MCU_ECM_ETCCFG_COUNTER_CMPW_MASK))
      {
        /* Error Trigger n Clear Mask Count setting */
        *LpEcmRegAddress = LpEcmErrorOutClrConfigRegSetting[0].aaEcmRegisterValue[LucCount];
        LpEcmRegAddress++;
      }
      else
      {
        /* ECMETRGCLRT update is in progress */
        LucReturnValue = E_NOT_OK;
      }
    }
  } /* else No action required */

  /* Return the value of ECM setting to counter clock domain result */
  return (LucReturnValue);
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of (Mcu_ECM_OPERATION == STD_ON) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
