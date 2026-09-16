/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Pwm_PBcfg.c                                                                                         */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2023, 2024 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains post-build time parameters.                                                                     */
/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                                         */
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
/*              Devices:        R7F7025BxFABC                                                                         */
/*====================================================================================================================*/


/***********************************************************************************************************************
**                      Revision Control History                                                                      **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Generation Tool Version                                                                       **
***********************************************************************************************************************/
/*                                                                                                                    */
/* TOOL VERSION:  PwmU2Bx-E.dll version: 2.5.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\pwm\generator\U2B24-E\R2211_pwm_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_pwm.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_pwm.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_pwm.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:50:00
 */


/***********************************************************************************************************************
**                      Instance Index                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Pwm.h"
#include "Pwm_Ram.h"
#include "Pwm_Externals.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/**********************************************************************************************************************/
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569, CWE-738                    */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0315)    : Implicit conversion from a pointer to object type to a pointer to void.                      */
/* Rule                : MISRA C:2012 Dir-1.1, CWE Rule CWE-188, CWE-398, CWE-569                                     */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : [I] Cast from a pointer to void to a pointer to object type.                                 */
/* Rule                : MISRA C:2012 Rule-11.5                                                                       */
/* JV-01 Justification : A cast should not be performed between a pointer to object type and a different pointer      */
/*                       to object type.                                                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object 'name' is only referenced in the translation unit where it is defined.            */
/* Rule                : MISRA C:2012 Rule-8.7, CERTCCM DCL15, DCL19,  CWE Rule CWE-398, CWE-569                      */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is           */
/*                       accepted.                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : '%s' has external linkage and is being defined without any previous declaration.             */
/* Rule                : MISRA C:2012 Rule-8.4, CERTCCM DCL07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping ).      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1502)    : The object 'name' is defined but is not used within this project.                            */
/* Rule                : MISRA C:2012 Rule-2.8, CWE Rule CWE-398, CWE-569, CERTC Rule MSC13                           */
/* JV-01 Justification : Array is used in another part of driver code. There is no problem in use                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0326)    : Cast between a pointer to void and an integral type.                                         */
/* Rule                : CERTCCM EXP36, INT36, MISRA C:2012 Rule-11.6, CWE Rule CWE-398, CWE-569, CWE-738             */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped.          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1257)    : An integer constant suffixed with L or LL is being converted to a type of lower rank on      */
/*                       assignment.                                                                                  */
/* Rule                : CERTCCM INT02, MISRA C:2012 Rule-10.3, CWE-136, CWE-192                                      */
/* JV-01 Justification : Depending on SPI functionality, lower rank on assignment is needed.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_PBCFG_C_AR_RELEASE_MAJOR_VERSION                                    4U
#define PWM_PBCFG_C_AR_RELEASE_MINOR_VERSION                                    8U
#define PWM_PBCFG_C_AR_RELEASE_REVISION_VERSION                                 0U

/* File version information */
#define PWM_PBCFG_C_SW_MAJOR_VERSION                                            2U
#define PWM_PBCFG_C_SW_MINOR_VERSION                                            5U

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/
#if (PWM_PBTYPES_AR_RELEASE_MAJOR_VERSION != PWM_PBCFG_C_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm_PBcfg.c : Mismatch in Release Major Version"
#endif

#if (PWM_PBTYPES_AR_RELEASE_MINOR_VERSION != PWM_PBCFG_C_AR_RELEASE_MINOR_VERSION)
  #error "Pwm_PBcfg.c : Mismatch in Release Minor Version"
#endif

#if (PWM_PBTYPES_AR_RELEASE_REVISION_VERSION != PWM_PBCFG_C_AR_RELEASE_REVISION_VERSION)
  #error "Pwm_PBcfg.c : Mismatch in Release Revision Version"
#endif

#if (PWM_PBTYPES_SW_MAJOR_VERSION != PWM_PBCFG_C_SW_MAJOR_VERSION)
  #error "Pwm_PBcfg.c : Mismatch in Software Major Version"
#endif

#if (PWM_PBTYPES_SW_MINOR_VERSION != PWM_PBCFG_C_SW_MINOR_VERSION)
  #error "Pwm_PBcfg.c : Mismatch in Software Minor Version"
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/
#define PWM_START_SEC_VAR_INIT_PTR
#include "Pwm_MemMap.h"


/* Pointer to function table for all timer IP */
P2CONST(Pwm_HwFuncTableType, PWM_VAR_INIT, PWM_CONFIG_DATA) Pwm_GaaHwFunc[] =
{
  /* ATU Function Table */
  NULL_PTR,
  /* TAUD Function Table */
  NULL_PTR,
  /* TAUJ Function Table */
  NULL_PTR,
  /* DIAG Function Table */
  NULL_PTR,
  /* GTM Function Table */
  &Pwm_GtmFunc
};

#define PWM_STOP_SEC_VAR_INIT_PTR
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define PWM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/* Structure for Hardware IP configuration */
CONST(Pwm_HWIP_ConfigType, PWM_CONFIG_DATA) Pwm_GaaHWIP_Used[] =
{
  /* Index: 0 - GTM */
  {
    /* ucIndex */
    PWM_HWIP_GTM
  }
};

/* Structure for TAUD channel properties */

/* Structure for TAUJ channel properties */

/* Structure for TAU channel configuration */

CONST(Pwm_GTMChannelPropType, PWM_CONFIG_DATA) Pwm_GaaGTMChannelProp[] =                                                /* PRQA S 3408, 1504 # JV-01, JV-01 */
{
  /* Index: 0 - PwmChannel_ATOM00 */
  {
    /* pGtmTomATomChannelRegs */
    (P2VAR(void, TYPEDEF, REGSPACE)) 0xFF601804UL,                                                                      /* PRQA S 0326 # JV-01 */

    /* pEICx_Address */
    NULL_PTR,

    /* pGTM_IRQ_SELxy */
    NULL_PTR,

    /* ulGTM_IRQ_SELxyEnableValue */
    0x00000000U,

    /* ucChClockSelect */
    0x00U,

    /* ddDefault_Period */
    0x00007FFDUL,

    /* ddDefault_Duty */
    0x4000U,

    /* usPeriodShift */
    0x0000UL,                                                                                                           /* PRQA S 1257 # JV-01 */

    /* ucTimerUnitIndex */
    0x00U,

    /* ucChannelNumber */
    0x00U,

    /* ucTomAtomType */
    PWM_GTM_ATOMTYPE
  }
};

/* Structure for each TAUD unit configuration set */

/* Structure for each TAUJ unit configuration set */

/* Structure for each GTM unit configuration set */
CONST(Pwm_GTMUnitConfigType, PWM_CONFIG_DATA) Pwm_GaaGTMUnitConfig[] =                                                  /* PRQA S 3408, 1504 # JV-01, JV-01 */
{
  /* Index: 0 - ATOM0 */
  {
    /* pGtmTomATomClusterRegs */
    (P2VAR(void, TYPEDEF, REGSPACE)) 0xFF601C40UL,                                                                      /* PRQA S 0326 # JV-01 */

    /* usEnableChannelValue */
    0x0002U,

    /* usSyncChannelMask */
    0x0000U,

    /* ucTomAtomType */
    PWM_GTM_ATOMTYPE
  }
};

/* Structure for channel Configuration set */
CONST(Pwm_ChannelConfigType, PWM_CONFIG_DATA) Pwm_GaaChannelConfig[] =                                                  /* PRQA S 1504 # JV-01 */
{
  /* Index: 0 - PwmChannel_ATOM00 */
  {
    /* pChannelProp */
    &Pwm_GaaGTMChannelProp[0],

    /* pPwmEdgeNotifPtr */
    NULL_PTR,

    /* ucPolarity */
    PWM_POLARITY_HIGH,

    /* enClassType */
    PWM_VARIABLE_PERIOD,

    /* ucIdleLevel */
    (uint8)PWM_HIGH,

    /* blSyncStartReq */
    PWM_FALSE,

    /* pHWIPChannelConfig */
    NULL_PTR,

    /* ucTimerUnitType */
    PWM_HWIP_GTM
  }
};

/* Structure for Configuration */
CONST(Pwm_ConfigType, PWM_CONFIG_DATA) Pwm_GaaConfiguration[] =                                                         /* PRQA S 1502 # JV-01 */
{
  /* Index: 0 - Pwm_GaaConfiguration */
  {
    /* ulStartOfDbToc */
    0x0EDE4228UL,

    /* Index: 1 - aaTimerUnitConfig */
    {
      /* aaTimerUnitConfig[0] */
      NULL_PTR,

      /* aaTimerUnitConfig[1] */
      NULL_PTR,

      /* aaTimerUnitConfig[2] */
      NULL_PTR,

      /* aaTimerUnitConfig[3] */
      NULL_PTR,

      /* aaTimerUnitConfig[4] */
      &Pwm_GaaGTMUnitConfig[0]
    },
    /* pChannelConfig */
    &Pwm_GaaChannelConfig[0],

    /* pHWIPConfig */
    NULL_PTR
  }
};

#define PWM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */



/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

