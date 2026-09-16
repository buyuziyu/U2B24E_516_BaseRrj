/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_RAM_LLDriver.c                                                                                  */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 * 2.3.0:  28/02/2025   : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Release
 * 2.1.2:  31/10/2024   : Update SW-VERSION to 2.1.2
 * 2.1.1:  30/08/2024   : Update SW-VERSION to 2.1.1
 *         16/07/2024   : As part of ARDAACL-47932 (ARDAACL-47792), following changes are made:
 *                        - Update Mcu_RAMInitRamSection initializes the Retention RAM section
 * 2.0.0:  04/08/2023   : Remove redundant QAC message 0791
 * 1.4.5:  01/02/2023   : Initial Version as new Mcu Structure
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
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : MISRA C:2012 Rule-11.4, CERTCCM INT36, CWE Rule CWE-398, CWE-569, CWE-738                    */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer to   */
/*                       object type.                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifiers. There is no impact on the functionality    */
/*                       due to this conditional check for mode change.                                               */
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
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
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
#define MCU_RAM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION    MCU_AR_RELEASE_MAJOR_VERSION_VALUE
#define MCU_RAM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION    MCU_AR_RELEASE_MINOR_VERSION_VALUE
#define MCU_RAM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MCU_RAM_LLDRIVER_C_SW_MAJOR_VERSION            MCU_SW_MAJOR_VERSION_VALUE
#define MCU_RAM_LLDRIVER_C_SW_MINOR_VERSION            MCU_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (MCU_RAM_LLDRIVER_AR_RELEASE_MAJOR_VERSION != MCU_RAM_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
#error "MCU_RAM_LLDriver.c : Mismatch in Release Major Version"
#endif

#if (MCU_RAM_LLDRIVER_AR_RELEASE_MINOR_VERSION != MCU_RAM_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
#error "MCU_RAM_LLDriver.c : Mismatch in Release Minor Version"
#endif

#if (MCU_RAM_LLDRIVER_AR_RELEASE_REVISION_VERSION != MCU_RAM_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
#error "MCU_RAM_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (MCU_RAM_LLDRIVER_SW_MAJOR_VERSION != MCU_RAM_LLDRIVER_C_SW_MAJOR_VERSION)
#error "MCU_RAM_LLDriver.c : Mismatch in Software Major Version"
#endif

#if (MCU_RAM_LLDRIVER_SW_MINOR_VERSION != MCU_RAM_LLDRIVER_C_SW_MINOR_VERSION)
#error "MCU_RAM_LLDriver.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/**********************************************************************************************************************/
/**                                             Internal Function Prototypes                                         **/
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name      : Mcu_RAMInitRamSection
**
** Service ID         : None
**
** Description        : This function initializes the RAM section as provided from the configuration structure.
**
** Sync/Async         : Synchronous
**
** Reentrancy         : Non-Reentrant
**
** Input Parameters   : LddRamSection - Id for RAM section
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return parameter   : None
**
** Preconditions      : MCU Driver component must be initialized
**
** Global Variables   : Mcu_GpConfigPtr, Mcu_GucLramEccEcmInit, Mcu_GucCramEccEcmInit, Mcu_GucRramEccEcmInit
**
** Function Invoked   : Mcu_ECCSetLramEccInt, Mcu_ECCSetCramEccInt, Mcu_ECCSetRramEccInt, Mcu_ECMSetEcmRegister
**
** Registers Used     : None
**
** Reference ID       : MCU_DUD_ACT_067, MCU_DUD_ACT_067_CRT001, MCU_DUD_ACT_067_CRT002,
** Reference ID       : MCU_DUD_ACT_067_GBL001, MCU_DUD_ACT_067_GBL002, MCU_DUD_ACT_067_GBL003
***********************************************************************************************************************/
#define MCU_START_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"
FUNC(void, MCU_PRIVATE_CODE) Mcu_RAMInitRamSection(Mcu_RamSectionType LddRamSection)
{
  P2CONST(Mcu_RamSettingType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) LpRamSetting;
  uint32 LulRamStartAddress;
  uint32 LulWriteSize;
  uint32 LulNoOfByte;
  uint32 LulDataLword;

  /* Get the pointer to the RAM structure */
  LpRamSetting = (P2CONST(Mcu_RamSettingType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA))(Mcu_GpConfigPtr->pRamSetting);         /* PRQA S 0316 # JV-01 */

  #if (MCU_RAM_ECCECM_SETTING_INITRAMSECTION == STD_ON)
  /* Clear RAM status and Set RAM Error state */
  if (MCU_RAM_SECTION_LRAM == LpRamSetting[LddRamSection].ucRamSectionType)
  {
    if (MCU_RAM_ECCECM_INIT_NOT_DONE == Mcu_GucLramEccEcmInit)                                                          /* PRQA S 3416 # JV-01 */
    {
      MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

      Mcu_ECCSetLramEccInt();

      MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
    } /* else No action is required */
  }
  #if (MCU_RETENTION_RAM_SETTING == STD_ON)
  else if (MCU_RAM_SECTION_RRAM == LpRamSetting[LddRamSection].ucRamSectionType)
  {
    if (MCU_RAM_ECCECM_INIT_NOT_DONE == Mcu_GucRramEccEcmInit)                                                          /* PRQA S 3416 # JV-01 */
    {
      MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

      Mcu_ECCSetRramEccInt();

      MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
    } /* else No action is required */
  }
  #endif /* MCU_RETENTION_RAM_SETTING == STD_ON */
  else
  {
    if (MCU_RAM_ECCECM_INIT_NOT_DONE == Mcu_GucCramEccEcmInit)                                                          /* PRQA S 3416 # JV-01 */
    {
      MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

      Mcu_ECCSetCramEccInt();

      MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);
    } /* else No action is required */
  }
  #endif /* MCU_RAM_ECCECM_SETTING_INITRAMSECTION == STD_ON */
  /* Get the start address of the RAM section */
  LulRamStartAddress = (uint32)LpRamSetting[LddRamSection].pRamSectionBaseAddress;                                      /* PRQA S 0306 # JV-01 */
  /* Get the size of RAM section */
  LulNoOfByte = LpRamSetting[LddRamSection].ulRamSectionSize;
  /* Get initial value */
  LulDataLword = (uint32)LpRamSetting[LddRamSection].ucRamDefaultValue;

  /* Set WriteSize */
  LulWriteSize = LpRamSetting[LddRamSection].ulRamSectionWriteSize;

  LulDataLword |= (LulDataLword << MCU_LONG_WORD_EIGHT);
  LulDataLword |= (LulDataLword << MCU_LONG_WORD_SIXTEEN);

  MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  while (MCU_LONG_WORD_ZERO != LulNoOfByte)
  {
    /* Initialize RAM area with the value */
    MCU_ADDR_WRITE32(LulRamStartAddress, LulDataLword);                                                                 /* PRQA S 0303, 3469 # JV-01, JV-01 */
    /* Decrement the size */
    LulNoOfByte -= LulWriteSize;                                                                                        /* PRQA S 3383 # JV-01 */
    /* Increment the pointer of RAM Section address */
    LulRamStartAddress += LulWriteSize;                                                                                 /* PRQA S 3383 # JV-01 */
  }

  MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

  #if (MCU_ECM_OPERATION == STD_ON)
  #if (MCU_RAM_ECCECM_SETTING_INITRAMSECTION == STD_ON)
  /* Clear RAM status and Set RAM Error state */
  if (MCU_RAM_SECTION_LRAM == LpRamSetting[LddRamSection].ucRamSectionType)
  {
    if (MCU_RAM_ECCECM_INIT_NOT_DONE == Mcu_GucLramEccEcmInit)                                                          /* PRQA S 3416 # JV-01 */
    {
      MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

      /* Configure for related RAM ECM errors after initilize LRAM */
      (void)Mcu_ECMSetEcmRegister(MCU_ECM_SETTING_AFTER_RAMINIT_LRAM);

      MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

      /* Set global CRAM ECC ECM init status */
      Mcu_GucLramEccEcmInit = MCU_RAM_ECCECM_INIT_DONE;
    } /* else No action is required */
  }
  #if (MCU_RETENTION_RAM_SETTING == STD_ON)
  else if (MCU_RAM_SECTION_RRAM == LpRamSetting[LddRamSection].ucRamSectionType)
  {
    if (MCU_RAM_ECCECM_INIT_NOT_DONE == Mcu_GucRramEccEcmInit)                                                          /* PRQA S 3416 # JV-01 */
    {
      MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

      /* Configure for related RAM ECM error afters initilize RRAM */
      (void)Mcu_ECMSetEcmRegister(MCU_ECM_SETTING_AFTER_RAMINIT_RRAM);

      MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

      /* Set global RRAM ECC ECM init status */
      Mcu_GucRramEccEcmInit = MCU_RAM_ECCECM_INIT_DONE;
    } /* else No action is required */
  }
  #endif /* MCU_RETENTION_RAM_SETTING == STD_ON */
  else
  {
    if (MCU_RAM_ECCECM_INIT_NOT_DONE == Mcu_GucCramEccEcmInit)                                                          /* PRQA S 3416 # JV-01 */
    {
      MCU_ENTER_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

      /* Configure for related RAM ECM error afters initilize CRAM */
      (void)Mcu_ECMSetEcmRegister(MCU_ECM_SETTING_AFTER_RAMINIT_CRAM);

      MCU_EXIT_CRITICAL_SECTION(MCU_INTERRUPT_CONTROL_PROTECTION);

      /* Set global CRAM ECC ECM init status */
      Mcu_GucCramEccEcmInit = MCU_RAM_ECCECM_INIT_DONE;
    } /* else No action is required */
  }
  #endif /* MCU_RAM_ECCECM_SETTING_INITRAMSECTION == STD_ON */
  #endif /* MCU_ECM_OPERATION == STD_ON */

  return;
}
#define MCU_STOP_SEC_PRIVATE_CODE
#include "Mcu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
