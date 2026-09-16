/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_DIAG_LLDriver.c                                                                                 */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                              COPYRIGHT                                                             */
/*====================================================================================================================*/
/* (c) 2021-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application for PWM Driver Component                                                     */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*                                                                                                                    **
 ** 2.5.1: 30/06/2025 : Remove SW-VERSION in header comment                                                           **
 ** 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                       **
 ** 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                          **
 ** 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.04 Beta Release                                           **
 ** 2.3.1: 31/03/2025 : Update SW-VERSION for U2Ax Ver22.00.03 Beta2 Release                                          **
 ** 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                       **
 ** 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                 **
 ** 2.1.2: 31/10/2024 : Update SW-VERSION for Ver22.00.05 U2Cx Beta2 Release                                          **
 ** 2.1.1: 21/08/2024 : As part of U2Cx Diag support, following changes are made                                      **
 **                     1. Pwm_HW_DIAG_EnableAdTrigger, Pwm_HW_DIAG_DisableAdTrigger:                                 **
 **                     2. Update Simultaneous Rewrite Procedure and add new DEM error PWM_E_REWRITE_FAILED           **
 **                     3. Update macro used PWM_DIAG_RESET_16BIT_RSFT to PWM_DIAG_RESET_16BIT_RSF, PWM_DIAG_PWGC_RDTT**
 **                        to PWM_DIAG_REWRITE_REQUEST                                                                **
 **                     4. Update Registers Used and Reference ID                                                     **
 **        16/07/2024 : As part of U2Cx Diag support, following changes are made                                      **
 **                     1. Update Simultaneous Rewrite Procedure and add new DEM error PWM_E_REWRITE_FAILED for       **
 **                        Pwm_HW_DIAG_SetDutyCycle, Pwm_HW_DIAG_SetOutputToIdle,Pwm_HW_DIAG_SetTriggerDelay          **
 **                     2. Add QAC massage 2877                                                                       **
 **                     3. Cast PWM_TRUE, PWM_FALSE to uint8                                                          **
 **                     4. Remove QAC 0791, 2841. Add QAC message 1006, 3006, 4304, 0404                              **
 ** 2.0.2: 14/12/2023 : Update version in header comment                                                              **
 ** 2.0.1: 21/10/2023 : Follow rule QAC 10.3.0, remove QAC message 1532, 2814, 2824, 2844, 4399                       **
 **        15/10/2023 : Change critical section PWM_RAM_DATA_PROTECTION_GLOBAL to PWM_INTERRUPT_CONTROL_PROTECTION in **
 **                     function Pwm_HW_DIAG_SetDutyCycle, Pwm_HW_DIAG_SetOutputToIdle                                **
 ** 2.0.0: 05/07/2023 : Update from "Pwm_Mapping.h to "Pwm_MemMap.h".                                                 **
 **                     Update Exclusive_Area of PWM_ENTER_CRITICAL_SECTION/PWM_EXIT_CRITICAL_SECTION                 **
 **                     Add PWM_ENTER_CRITICAL_SECTION/PWM_EXIT_CRITICAL_SECTION in Pwm_HW_DIAG_DisableAdTrigger,     **
 **                       Pwm_HW_DIAG_EnableAdTrigger to support Multicore                                            **
 **                     Remove pre-compile condition check for PWM_ENTER_CRITICAL_SECTION/PWM_EXIT_CRITICAL_SECTION   **
 **        21/04/2023 : Change PWM_TOTAL_HW_IP_SUPPORTED to PWM_TOTAL_HW_IP_CONFIG the following process              **
 **                     in Pwm_HW_DIAG_InitUnit().                                                                    **
 **                     Update header description for all APIs                                                        **
 **        03/04/2023 : Replace macro PWM_DIAG_TOTAL_PERIOD_SELECT to PWM_DIAG_MAX_PERIOD_SELECT_GROUP in             **
 **                     Pwm_HW_DIAG_InitUnit, Pwm_HW_DIAG_DeInitUnit                                                  **
 **        29/03/2023 : Added an IF condition to check usPWGCnCSDR <= ulPWGCnCRDR before set PWM_ZERO to usPWGCnCSDR  **
 **                     in function Pwm_HW_DIAG_SetOutputToIdle                                                       **
 ** 1.4.4: 13/07/2022 : Remove QAC message 1006                                                                       **
 **        22/06/2022 : Added QAC message and header for message 1006                                                 **
 **        09/06/2022 : Changed disable interrupt process in Pwm_HW_DIAG_DeInitUnit from RH850_SV_SET_ICR_SYNCP to    **
 **                     RH850_SV_MODE_ICR_OR and added DummyRead & SYNCP to improved synchronization process.         **
 ** 1.4.3: 25/05/2022 : Removed redundant header of message 2877                                                      **
 **        09/05/2022 : Removed "else" statement don't use when no action required                                    **
 **        18/04/2022 : Changed MAX_DUTY_CYCLE to PWM_MAX_DUTY_CYCLE_VALUE and                                        **
 **                             MIN_DUTY_CYCLE to PWM_MIN_DUTY_CYCLE_VALUE                                            **
 **        08/04/2022 : Corrected error content from "Pwm_DIAG_LLDriver.c : Mismatch in Release Patch Version" to     **
 **                     "Pwm_DIAG_LLDriver.c : Mismatch in Release Revision Version"                                  **
 ** 1.4.2: 08/03/2022 : Added header for message 2841                                                                 **
 **        26/02/2022 : Replace variable LulIndex with LucHWIPType on aaTimerUnitConfig array in Pwm_HW_DIAG_InitUnit **
 **        25/02/2022 : Remove redundant header, updated PRQA comment                                                 **
 **        22/02/2022 : Added header for message 2877, 3416 and updated PRQA comment,changed LucIndex to LulIndex in  **
 **                     Pwm_HW_DIAG_InitUnit                                                                          **
 ** 1.4.1: 11/12/2021 : Added loop for check  HWIPType before call HWUnit in function Pwm_HW_DIAG_InitUnit            **
 ** 1.4.0: 14/10/2021 : Updated setting condition of the falling edge timing in Pwm_HW_DIAG_InitChannel.              **
 ** 1.0.0: 23/08/2021 : Initial Version.                                                                              **
 **                                                                                                                   */
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
/* Message (2:0499)    : Right operand of shift operator is greater than or equal to the width of the essential type  */
/*                       of the left operand.                                                                         */
/* Rule                : CERTCCM INT34, MISRA C:2012 Rule-12.2, CWE Rule CWE-681, CWE-682, CWE-738                    */
/* JV-01 Justification : The result has been ensured by casting to the same Type                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Dir-4.1, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
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
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : This in-line assembler construct is a language extension. The code has been ignored.         */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTCCM MSC14                                       */
/* JV-01 Justification : This is accepted, due to the Synchronization Processing Instruction is following hardware    */
/*                       specification.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3                                                                         */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:4304)    : An expression of 'essentially Boolean' type (%1s) is being cast to unsigned type '%2s'.      */
/* Rule                : MISRA C:2012 Rule-10.5, CWE Rule CWE-704                                                     */
/* JV-01 Justification : This is accepted. This casting from boolean to unsigned type for values 0 and 1 does not     */
/*                       make data conflict.                                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/***********************************************************************************************************************
**                                              Include Section                                                       **
***********************************************************************************************************************/
#include "Pwm.h"
#include "Pwm_PBTypes.h"
#include "Pwm_Ram.h"
#include "Pwm_DIAG_PBTypes.h"
#include "Pwm_DIAG_Ram.h"
#include "Pwm_DIAG_LLDriver.h"

#if (PWM_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Pwm.h"
#endif
/* Included for DEM */
#if ((STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED) || (STD_ON == PWM_INTERRUPT_CONSISTENCY_CHECK))
#include "Dem.h"
#endif

/***********************************************************************************************************************
**                                             Version Information                                                    **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_DIAG_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION       PWM_AR_RELEASE_MAJOR_VERSION_VALUE
#define PWM_DIAG_LLDRIVER_C_AR_RELEASE_MINOR_VERSION       PWM_AR_RELEASE_MINOR_VERSION_VALUE
#define PWM_DIAG_LLDRIVER_C_AR_RELEASE_REVISION_VERSION    PWM_AR_RELEASE_REVISION_VERSION_VALUE
/* Module software version information */
#define PWM_DIAG_LLDRIVER_C_SW_MAJOR_VERSION               PWM_SW_MAJOR_VERSION_VALUE
#define PWM_DIAG_LLDRIVER_C_SW_MINOR_VERSION               PWM_SW_MINOR_VERSION_VALUE
#define PWM_DIAG_LLDRIVER_C_SW_PATCH_VERSION               PWM_SW_PATCH_VERSION_VALUE
/***********************************************************************************************************************
**                                              Version Check                                                         **
***********************************************************************************************************************/
#if (PWM_DIAG_LLDRIVER_AR_RELEASE_MAJOR_VERSION != PWM_DIAG_LLDRIVER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm_DIAG_LLDriver.c : Mismatch in Release Major Version"
#endif
#if (PWM_DIAG_LLDRIVER_AR_RELEASE_MINOR_VERSION != PWM_DIAG_LLDRIVER_C_AR_RELEASE_MINOR_VERSION)
  #error "Pwm_DIAG_LLDriver.c : Mismatch in Release Minor Version"
#endif
#if (PWM_DIAG_LLDRIVER_AR_RELEASE_REVISION_VERSION != PWM_DIAG_LLDRIVER_C_AR_RELEASE_REVISION_VERSION)
  #error "Pwm_DIAG_LLDriver.c : Mismatch in Release Revision Version"
#endif

#if (PWM_DIAG_LLDRIVER_SW_MAJOR_VERSION != PWM_DIAG_LLDRIVER_C_SW_MAJOR_VERSION)
  #error "Pwm_DIAG_LLDriver.c : Mismatch in Software Major Version"
#endif
#if (PWM_DIAG_LLDRIVER_SW_MINOR_VERSION != PWM_DIAG_LLDRIVER_C_SW_MINOR_VERSION)
  #error "Pwm_DIAG_LLDriver.c : Mismatch in Software Minor Version"
#endif
#if (PWM_DIAG_LLDRIVER_SW_PATCH_VERSION != PWM_DIAG_LLDRIVER_C_SW_PATCH_VERSION)
  #error "Pwm_DIAG_LLDriver.c : Mismatch in Software Patch Version"
#endif

/***********************************************************************************************************************
**                                              Function Definitions                                                  **
***********************************************************************************************************************/
#if (PWM_DIAG_UNIT_USED == STD_ON)
/***********************************************************************************************************************
** Function Name        : Pwm_HW_DIAG_InitUnit
**
** Service ID           : NA
**
** Description          : This function initializes the registers for all configured PWM-Diag units.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : LpConfigPtr
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : none
**
** Global Variables     : Pwm_GpDiagConfig, Pwm_GaaHWIP_Used
**
** Functions invoked    : none
**
** Registers Used       : PWBAnBRSm, PWGCPRDm, PWGCPRDSLq, EICn
**
** Reference ID         : PWM_DUD_ACT_080, PWM_DUD_ACT_080_GBL001
** Reference ID         : PWM_DUD_ACT_080_REG001, PWM_DUD_ACT_080_REG002, PWM_DUD_ACT_080_REG003
** Reference ID         : PWM_DUD_ACT_080_REG004
***********************************************************************************************************************/
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_DIAG_InitUnit(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpConfigPtr)      /* PRQA S 3006 # JV-01 */
{
  P2CONST(Pwm_DiagPeriodConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpPeriodConfig;
  P2CONST(Pwm_DiagPeriodSelectConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpPeriodSelectConfig;
  P2CONST(Pwm_DiagPrescalerConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpPrescalerConfig;
  P2CONST(Pwm_DiagNotifyConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagNotify;
  VAR(uint32, AUTOMATIC) LulIndex;
  VAR(uint8, AUTOMATIC) LucGrId;
  /* Index of HW IP Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;

  for (LulIndex = (uint32)PWM_ZERO; LulIndex < (uint32)PWM_TOTAL_HW_IP_CONFIG; LulIndex++)                              /* PRQA S 2877 # JV-01 */
  {
    LucHWIPType = Pwm_GaaHWIP_Used[LulIndex].ucIndex;
    if (PWM_HWIP_DIAG == LucHWIPType)                                                                                   /* PRQA S 3416 # JV-01 */
    {
      /* Initialize global pointer */
      Pwm_GpDiagConfig = (P2CONST(Pwm_DiagUnitConfigType, PWM_VAR_NO_INIT, PWM_CONFIG_DATA))                            /* PRQA S 0316 # JV-01 */
      LpConfigPtr->aaTimerUnitConfig[LucHWIPType];
    } /* else No action required */
  }

  /* Load configuration */
  LpPrescalerConfig = &Pwm_GpDiagConfig->pPrescalerConfig[0];
  LpPeriodConfig = &Pwm_GpDiagConfig->pPeriodConfig[0];
  LpPeriodSelectConfig = &Pwm_GpDiagConfig->pPeriodSelectConfig[0];

  /* Setting prescaler */
  for (LulIndex = 0; LulIndex < PWM_DIAG_TOTAL_PRESCALER; LulIndex++)
  {
    Pwm_GpDiagConfig->pPWBA->aaPWBAnBRSm[LpPrescalerConfig[LulIndex].ucBRSmIndex].usPWBAnBRSm
      = LpPrescalerConfig[LulIndex].usBSRmValue;
  }

  /* Setting default period */
  for (LulIndex = 0; LulIndex < PWM_DIAG_TOTAL_PERIOD; LulIndex++)
  {
    Pwm_GpDiagConfig->pSLPWG->aaPWGCPRDm[LpPeriodConfig[LulIndex].ucPRDmIndex].usPWGCPRDm
      = LpPeriodConfig[LulIndex].usPRDmValue;
  }

  /* Setting default selection of period */
  for (LulIndex = 0; LulIndex < PWM_DIAG_MAX_PERIOD_SELECT_GROUP; LulIndex++)                                           /* PRQA S 2877 # JV-01 */
  {
    Pwm_GpDiagConfig->pSLPWG->aaPWGCPRDSLq[LpPeriodSelectConfig[LulIndex].ucPWGCPRDSLqIndex].ulPWGCPRDSLq
      = LpPeriodSelectConfig[LulIndex].ulPWGCPRDSLqValue;
  }

  /* Enable EIC registers */
  /* Loop Notification Group0 to Group3 */
  for (LulIndex = 0; LulIndex < PWM_DIAG_NOTI_GROUP; LulIndex++)
  {
    /* Loop Channel Group0 to Group2 */
    for (LucGrId = 0; LucGrId < PWM_DIAG_CH_GROUP; LucGrId++)
    {
      /* Load configuration */
      LpDiagNotify = Pwm_GpDiagConfig->pDiagNotiGrConfig->aaDiagNotifyConfig[LulIndex][LucGrId];
      if (NULL_PTR != LpDiagNotify->pEICn)
      {
        #if (PWM_CLEAR_PENDING_INTERRUPT == STD_ON)
        /* Clear pending interrupt */
        RH850_SV_MODE_ICR_AND(16, LpDiagNotify->pEICn, PWM_CLEAR_PENDING_INTR_MASK);                                    /* PRQA S 0499 # JV-01 */
        #endif
        /* Enable interrupt of INTC */
        RH850_SV_CLEAR_ICR_SYNCP(8, LpDiagNotify->pEICn, (uint8)~PWM_EIC_EIMK_MASK);                                    /* PRQA S 0751, 1006 # JV-01, JV-01 */
      } /* else: No action */
    } /* End of for (LucGrId = 0; LucGrId < PWM_DIAG_CH_GROUP; LucGrId++) */
  } /* End of for (LulIndex = 0; LulIndex < PWM_DIAG_NOTI_GROUP; LulIndex++) */
} /* End of Pwm_HW_DIAG_InitUnit() function */

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_DIAG_InitChannel
**
** Service ID           : NA
**
** Description          : This function sets the registers for all configured PWM-Diag channels.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : void
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : none
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GpDiagConfig, Pwm_GaaNotifStatus
**
** Functions invoked    : none
**
** Registers Used       : PWSDnPVCRx, PWGCnCSDR, PWGCnCRDR, PWGCnCTDR, PWGCnCTL, PWGCnTCR,
**                      : PWGCINTMSKhk, EICn, PWBAnTS, SLPWGCk
**
** Reference ID         : PWM_DUD_ACT_081, PWM_DUD_ACT_081_REG001, PWM_DUD_ACT_081_REG002,
** Reference ID         : PWM_DUD_ACT_081_REG003, PWM_DUD_ACT_081_REG004, PWM_DUD_ACT_081_REG005,
** Reference ID         : PWM_DUD_ACT_081_REG006, PWM_DUD_ACT_081_REG007,
** Reference ID         : PWM_DUD_ACT_081_REG010, PWM_DUD_ACT_081_REG011,
** Reference ID         : PWM_DUD_ACT_081_REG012, PWM_DUD_ACT_081_GBL001
***********************************************************************************************************************/
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_DIAG_InitChannel(void)
{
  P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagCh;
  P2CONST(Pwm_DiagUnitConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagConfig;
  VAR(uint32, AUTOMATIC) LulPWGCnCRDRValue;
  VAR(uint32, AUTOMATIC) LulPWGCnCSDRValue; /* Register size is 16bit but it set to 32bit for reduce cast */
  VAR(uint32, AUTOMATIC) LulPWGCnCTDRValue; /* Register size is 16bit but it set to 32bit for reduce cast */
  VAR(uint32, AUTOMATIC) LulPWGCPRDmValue;  /* Register size is 16bit but it set to 32bit for reduce cast */
  VAR(uint8, AUTOMATIC) LucIndex;

  /* Load configuration */
  LpDiagConfig = Pwm_GpDiagConfig;

  /* Initialize all configured channels */
  for (LucIndex = 0; LucIndex < PWM_TOTAL_CHANNELS_CONFIG; LucIndex++)
  {
    if (PWM_HWIP_DIAG == Pwm_GpChannelConfig[LucIndex].ucTimerUnitType)                                                 /* PRQA S 3416 # JV-01 */
    {
      /* Set Diag channel pointer */
      LpDiagCh = (P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA))                                       /* PRQA S 0316 # JV-01 */
        Pwm_GpChannelConfig[LucIndex].pHWIPChannelConfig;
      /* Load period value */
      LulPWGCPRDmValue = LpDiagConfig->pSLPWG->aaPWGCPRDm[LpDiagCh->ucPeriodId].usPWGCPRDm;

      /* Setting related ADC setting */
      LpDiagConfig->pPWSD->aaPWSDnPVCRx[LpDiagCh->ucChNo].ulPWSDnPVCRx = LpDiagCh->ulPWSDnRVCRxValue;

      /* Load config default value */
      LulPWGCnCSDRValue = LpDiagCh->usDefaultPWGCnCSDR;
      /* Add offset to rising edge */
      LulPWGCnCSDRValue += LpDiagCh->usOffset;                                                                          /* PRQA S 3383 # JV-01 */
      if (LulPWGCnCSDRValue > LulPWGCPRDmValue)
      {
         /* Adjust offset to rising edge */
         LulPWGCnCSDRValue -= LulPWGCPRDmValue;                                                                         /* PRQA S 3383 # JV-01 */
      } /* else: No action */
      /* Setting rising edge timing */
      LpDiagCh->pPWGC->usPWGCnCSDR = (uint16)LulPWGCnCSDRValue;

      /* Load config default value */
      LulPWGCnCRDRValue = LpDiagCh->ulDefaultPWGCnCRDR;

      /* To check configured default value is not HIGH */
      if (LulPWGCnCRDRValue != ((uint32)PWM_PERIOD_LIMIT + 1UL))
      {
        /* Add offset to falling edge */
        LulPWGCnCRDRValue += LpDiagCh->usOffset;                                                                        /* PRQA S 3383 # JV-01 */
        if (LulPWGCnCRDRValue > LulPWGCPRDmValue)
        {
           /* Adjust offset to falling edge */
           LulPWGCnCRDRValue -= LulPWGCPRDmValue;                                                                       /* PRQA S 3383 # JV-01 */
        } /* else: No action */
      }
      /* Setting falling edge timing */
      LpDiagCh->pPWGC->ulPWGCnCRDR = LulPWGCnCRDRValue;

      /* Load config default value */
      LulPWGCnCTDRValue = LpDiagCh->usDefaultPWGCnCTDR;
      /* Check Trigger Adjust Offset is true*/
      if (PWM_TRUE == LpDiagCh->blTriggerAdjustOffset)
      {
        /* Add offset to trigger */
        LulPWGCnCTDRValue += LpDiagCh->usOffset;                                                                        /* PRQA S 3383 # JV-01 */
        if (LulPWGCnCTDRValue > LulPWGCPRDmValue)
        {
          /* Adjust offset to trigger */
          LulPWGCnCTDRValue -= LulPWGCPRDmValue;                                                                        /* PRQA S 3383 # JV-01 */
        } /* else: No action */
      } /* else: No action */
      /* Setting AD trigger timing */
      LpDiagCh->pPWGC->usPWGCnCTDR = (uint16)LulPWGCnCTDRValue;

      /* Setting operation mode */
      LpDiagCh->pPWGC->usPWGCnCTL = LpDiagCh->usPWGCnCTL_Value | PWM_DIAG_PWGC_OCL;
      /* Disable ouptput */
      LpDiagCh->pPWGC->ucPWGCnTCR &= ~PWM_DIAG_ENABLE_OUTPUT;
      /* Disable interrupt of DIAG */
      LpDiagConfig->pPWGC_INTF->aaPWGC_INTF[LpDiagCh->ucGroupId].ulPWGCINTMSKhk
        |= 1UL << (LpDiagCh->ucChNo & 0x1FUL);

      #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
      /* Set the Notification status as PWM_FALSE */
      Pwm_GaaNotifStatus[LucIndex] = (uint8)PWM_FALSE;                                                                  /* PRQA S 4304 # JV-01 */
      #endif

    } /* else: No action */
    /* End of if (PWM_HWIP_DIAG == Pwm_GpChannelConfig[LucIndex].ucTimerUnitType) */
  } /* End of for (LucIndex = 0; LucIndex < PWM_TOTAL_CHANNELS_CONFIG; LucIndex++) */

  /* Enable A/D conversion result storing control */
  LpDiagConfig->pPWSD->ucPWSDnCTL = (PWM_DIAG_PWSD_ARSE | PWM_DIAG_PWSD_ENBL);
  /* Enable clock */
  LpDiagConfig->pPWBA->ucPWBAnTS = PWM_DIAG_CLK_SETTING;

  /* Starts PWGC operation */
  for (LucIndex = 0; LucIndex < PWM_TOTAL_CHANNELS_CONFIG; LucIndex++)
  {
    if (PWM_HWIP_DIAG == Pwm_GpChannelConfig[LucIndex].ucTimerUnitType)                                                 /* PRQA S 3416 # JV-01 */
    {
      LpDiagCh = (P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA))                                       /* PRQA S 0316 # JV-01 */
        Pwm_GpChannelConfig[LucIndex].pHWIPChannelConfig;
      /* Starts the corresponding channels */
      LpDiagConfig->pSLPWG->aaSLPWGCk[LpDiagCh->ucGroupId].ulSLPWGCk
        |= 1UL << (LpDiagCh->ucChNo & 0x1FUL);
    } /* else: No action */
  }
} /* End of Pwm_HW_DIAG_InitChannel() function */

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_DIAG_DeInitUnit
**
** Service ID           : NA
**
** Description          : This function De-initializes the registers for all configured PWM-Diag units.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : void
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : PWM_DE_INIT_API is STD_ON
**
** Global Variables     : Pwm_GpDiagConfig
**
** Functions invoked    : none
**
** Registers Used       : PWBAnTT, PWBAnBRSm, PWGCPRDm, PWGCPRDSLq
**
** Reference ID         : PWM_DUD_ACT_082, PWM_DUD_ACT_082_REG001, PWM_DUD_ACT_082_REG002,
** Reference ID         : PWM_DUD_ACT_082_REG003, PWM_DUD_ACT_082_REG004, PWM_DUD_ACT_082_REG005
** Reference ID         : PWM_DUD_ACT_082_REG006, PWM_DUD_ACT_082_REG007
***********************************************************************************************************************/
#if (PWM_DE_INIT_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_DIAG_DeInitUnit(void)                                                               /* PRQA S 3006 # JV-01 */
{
  P2CONST(Pwm_DiagPrescalerConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpPrescalerConfig;
  P2CONST(Pwm_DiagPeriodConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpPeriodConfig;
  P2CONST(Pwm_DiagPeriodSelectConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpPeriodSelectConfig;
  P2CONST(Pwm_DiagNotifyConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagNotify;
  VAR(uint8, AUTOMATIC) LucIndex;
  VAR(uint8, AUTOMATIC) LucGrId;

  /* Load configuration */
  LpPrescalerConfig = &Pwm_GpDiagConfig->pPrescalerConfig[0];
  LpPeriodConfig = &Pwm_GpDiagConfig->pPeriodConfig[0];
  LpPeriodSelectConfig = &Pwm_GpDiagConfig->pPeriodSelectConfig[0];

  /* Disable setting clock */
  Pwm_GpDiagConfig->pPWBA->ucPWBAnTT &= ~PWM_DIAG_CLK_SETTING;
  /* Disable A/D conversion result storing control */
  Pwm_GpDiagConfig->pPWSD->ucPWSDnCTL &= ~(PWM_DIAG_PWSD_ARSE | PWM_DIAG_PWSD_ENBL);

  /* Disable EIC registers */
  /* Loop Notification Group0 to Group3 */
  for (LucIndex = 0; LucIndex < PWM_DIAG_NOTI_GROUP; LucIndex++)
  {
    /* Loop Channel Group0 to Group2 */
    for (LucGrId = 0; LucGrId < PWM_DIAG_CH_GROUP; LucGrId++)
    {
      /* Load configuration */
      LpDiagNotify = Pwm_GpDiagConfig->pDiagNotiGrConfig->aaDiagNotifyConfig[LucIndex][LucGrId];

      if (NULL_PTR != LpDiagNotify->pEICn)
      {
        /* Disable interrupt of INTC */
        RH850_SV_MODE_ICR_OR(8, LpDiagNotify->pEICn, (uint8)PWM_EIC_EIMK_MASK);                                         /* PRQA S 0751 # JV-01 */
        #if (PWM_CLEAR_PENDING_INTERRUPT == STD_ON)
        /* Clear pending interrupt */
        RH850_SV_MODE_ICR_AND(16, LpDiagNotify->pEICn, PWM_CLEAR_PENDING_INTR_MASK);                                    /* PRQA S 0499 # JV-01 */
        #endif
        /* DummyRead & SYNCP */
        RH850_SV_MODE_REG_READ_ONLY(16, LpDiagNotify->pEICn);
        EXECUTE_SYNCP();                                                                                                /* PRQA S 1006 # JV-01 */
      } /* else: No action */
    } /* End of for (LucGrId = 0; LucGrId < PWM_DIAG_CH_GROUP; LucGrId++) */
  } /* End of for (LucIndex = 0; LucIndex < PWM_DIAG_NOTI_GROUP; LucIndex++) */

  /* Reset prescaler */
  for (LucIndex = 0; LucIndex < PWM_DIAG_TOTAL_PRESCALER; LucIndex++)
  {
    Pwm_GpDiagConfig->pPWBA->aaPWBAnBRSm[LpPrescalerConfig[LucIndex].ucBRSmIndex].usPWBAnBRSm
      &= ~(LpPrescalerConfig[LucIndex].usBSRmValue);
  }

  /* Reset period setting */
  for (LucIndex = 0; LucIndex < PWM_DIAG_TOTAL_PERIOD; LucIndex++)
  {
    Pwm_GpDiagConfig->pSLPWG->aaPWGCPRDm[LpPeriodConfig[LucIndex].ucPRDmIndex].usPWGCPRDm
      &= ~(LpPeriodConfig[LucIndex].usPRDmValue);
  }

  /* Reset selection of period */
  for (LucIndex = 0; LucIndex < PWM_DIAG_MAX_PERIOD_SELECT_GROUP; LucIndex++)                                           /* PRQA S 2877 # JV-01 */
  {
    Pwm_GpDiagConfig->pSLPWG->aaPWGCPRDSLq[LpPeriodSelectConfig[LucIndex].ucPWGCPRDSLqIndex].ulPWGCPRDSLq
      &= ~(LpPeriodSelectConfig[LucIndex].ulPWGCPRDSLqValue);
  }
} /* End of Pwm_HW_DIAG_DeInitUnit() function */

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_DE_INIT_API == STD_ON */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_DIAG_DeInitChannel
**
** Service ID           : NA
**
** Description          : This function reset the registers for all configured PWM-Diag channels.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : void
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : PWM_DE_INIT_API is STD_ON
**
** Global Variables     : Pwm_GpChannelConfig, Pwm_GpDiagConfig, Pwm_GaaNotifStatus
**
** Functions invoked    : none
**
** Registers Used       : SLPWGCk, PWGCINTMSKhk, PWSDnPVCRx, PWGCnCSDR, PWGCnCRDR,
**                      : PWGCnCTDR, PWGCnCTL, PWGCnTCR, EICn
**
** Reference ID         : PWM_DUD_ACT_083, PWM_DUD_ACT_083_GBL001, PWM_DUD_ACT_083_REG001, PWM_DUD_ACT_083_REG002,
** Reference ID         : PWM_DUD_ACT_083_REG005, PWM_DUD_ACT_083_REG006, PWM_DUD_ACT_083_REG007,
** Reference ID         : PWM_DUD_ACT_083_REG008, PWM_DUD_ACT_083_REG009, PWM_DUD_ACT_083_REG010
***********************************************************************************************************************/
#if (PWM_DE_INIT_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_DIAG_DeInitChannel(void)
{
  P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagCh;
  P2CONST(Pwm_DiagUnitConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagConfig;
  VAR(uint8, AUTOMATIC) LucIndex;

  /* Load configuration */
  LpDiagConfig = Pwm_GpDiagConfig;

  /* Initialize all configured channels */
  for (LucIndex = 0; LucIndex < PWM_TOTAL_CHANNELS_CONFIG; LucIndex++)
  {
    if (PWM_HWIP_DIAG == Pwm_GpChannelConfig[LucIndex].ucTimerUnitType)                                                 /* PRQA S 3416 # JV-01 */
    {
      /* Load configuration */
      LpDiagCh = (P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA))                                       /* PRQA S 0316 # JV-01 */
        Pwm_GpChannelConfig[LucIndex].pHWIPChannelConfig;
      /* Stop the corresponding channels */
      LpDiagConfig->pSLPWG->aaSLPWGCk[LpDiagCh->ucGroupId].ulSLPWGCk
        &= ~(1UL << (LpDiagCh->ucChNo & 0x1FUL));
      /* Disable interrupt of DIAG */
      LpDiagConfig->pPWGC_INTF->aaPWGC_INTF[LpDiagCh->ucGroupId].ulPWGCINTMSKhk
        &= ~(1UL << (LpDiagCh->ucChNo & 0x1FUL));
      /* DeInitialize PWSDnPVCRx register */
      LpDiagConfig->pPWSD->aaPWSDnPVCRx[LpDiagCh->ucChNo].ulPWSDnPVCRx = (uint32)PWM_ZERO;
      /* Reset rising edge timing */
      LpDiagCh->pPWGC->usPWGCnCSDR = (uint16)PWM_ZERO;
      /* Reset falling edge timing */
      LpDiagCh->pPWGC->ulPWGCnCRDR = (uint32)PWM_ZERO;
      /* Reset A/D trigger timing */
      LpDiagCh->pPWGC->usPWGCnCTDR = (uint16)PWM_ZERO;
      /* Reset operation mode */
      LpDiagCh->pPWGC->usPWGCnCTL = (uint16)PWM_ZERO;
      /* Disable ouptput */
      LpDiagCh->pPWGC->ucPWGCnTCR = (uint8)PWM_ZERO;

      #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
      /* Set the Notification status as PWM_FALSE */
      Pwm_GaaNotifStatus[LucIndex] = (uint8)PWM_FALSE;                                                                  /* PRQA S 4304 # JV-01 */
      #endif

    } /* else: No action */
    /* End of if (PWM_HWIP_DIAG == Pwm_GpChannelConfig[LucIndex].ucTimerUnitType) */
  } /* End of for (LucIndex = 0; LucIndex < PWM_TOTAL_CHANNELS_CONFIG; LucIndex++) */
} /* End of Pwm_HW_DIAG_DeInitChannel() function */

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_DE_INIT_API == STD_ON */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_DIAG_SetDutyCycle
**
** Service ID           : NA
**
** Description          : This function sets the duty cycle setting register of
**
**                      : the requested channel with the value of LusDutyCycle.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different channel
**
** Input Parameters     : LddChannelId, LusDutyCycle
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : PWM_SET_DUTY_CYCLE_API is STD_ON
**
** Global Variables     : Pwm_GpDiagConfig, Pwm_GpChannelConfig
**
** Functions invoked    : PWM_DEM_REPORT_ERROR
**
** Registers Used       : PWGCnRDT, PWGCnCSDR, PWGCnCRDR, PWGCnST
**
** Reference ID         : PWM_DUD_ACT_084, PWM_DUD_ACT_084_REG001, PWM_DUD_ACT_084_REG002, 
** Reference ID         : PWM_DUD_ACT_084_REG003, PWM_DUD_ACT_084_REG004, PWM_DUD_ACT_084_ERR001
** Reference ID         : PWM_DUD_ACT_084_CRT001, PWM_DUD_ACT_084_CRT002
***********************************************************************************************************************/
#if (PWM_SET_DUTY_CYCLE_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_DIAG_SetDutyCycle(Pwm_ChannelType LddChannelId, uint16 LusDutyCycle)
{
  P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagCh;
  P2CONST(Pwm_DiagUnitConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagConfig;
  VAR(uint32, AUTOMATIC) LulPWGCnCRDR;
  VAR(uint32, AUTOMATIC) LulPWGCnCSDR; /* Register size is 16bit but it set to 32bit for reduce cast */
  VAR(uint32, AUTOMATIC) LulPWGCPRD;   /* Register size is 16bit but it set to 32bit for reduce cast */
  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  VAR(boolean, AUTOMATIC) blDemReport;

  /* Initialize DEM report status */
  blDemReport = PWM_FALSE;
  #endif

  /* Load configuration */
  LpDiagConfig = Pwm_GpDiagConfig;
  LpDiagCh = (P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA))                                           /* PRQA S 0316 # JV-01 */
    Pwm_GpChannelConfig[LddChannelId].pHWIPChannelConfig;
  /* Enter protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);

  /* Load period of used clock */
  LulPWGCPRD = LpDiagConfig->pSLPWG->aaPWGCPRDm[LpDiagCh->ucPeriodId].usPWGCPRDm;

  /* Check whether simultaneous rewrite has been completed */
  if (PWM_DIAG_RESET_16BIT == (uint16)(LpDiagCh->pPWGC->usPWGCnST & PWM_DIAG_RESET_16BIT_RSF))                          /* PRQA S 0404 # JV-01 */
  {
    /* Set rising edge timing to offset */
    LpDiagCh->pPWGC->usPWGCnCSDR = LpDiagCh->usOffset;
    
    if ((uint8)PWM_HIGH == Pwm_GpChannelConfig[LddChannelId].ucPolarity)                                                /* PRQA S 3416 # JV-01 */
    {
      switch(LusDutyCycle)
      {
        case PWM_MAX_DUTY_CYCLE_VALUE: /* Set PWGCnCRDR to max value for Duty 100 % */
          LpDiagCh->pPWGC->ulPWGCnCRDR = (uint32)PWM_PERIOD_LIMIT + 1UL;
          break;
        case PWM_MIN_DUTY_CYCLE_VALUE: /* Set PWGCnCRDR to PWGCnCSDR value for Duty 0 % */
          LpDiagCh->pPWGC->ulPWGCnCRDR = LpDiagCh->pPWGC->usPWGCnCSDR;
          break;
        default: /* Set PWGCnCRDR to calculate: Duty 1% - 99% */
          LulPWGCnCRDR = (LulPWGCPRD * LusDutyCycle) >> PWM_DUTY_CALC_DIV;                                              /* PRQA S 3383 # JV-01 */
          /* Add offset */
          LulPWGCnCRDR += LpDiagCh->usOffset;                                                                           /* PRQA S 3383 # JV-01 */
          if (LulPWGCnCRDR > LulPWGCPRD)
          {
            /* Adjust offset */
            LulPWGCnCRDR -= LulPWGCPRD;                                                                                 /* PRQA S 3383 # JV-01 */
          } /* else: No action */
          /* Set falling edge timing */
          LpDiagCh->pPWGC->ulPWGCnCRDR = LulPWGCnCRDR;
          break;
      } /* End of switch */
    }
    else /* (PWM_LOW == ucPolarity) case */
    {
      switch(LusDutyCycle)
      {
        case PWM_MAX_DUTY_CYCLE_VALUE: /* Set PWGCnCRDR to max value for Duty 100 % */
          LpDiagCh->pPWGC->ulPWGCnCRDR = LpDiagCh->pPWGC->usPWGCnCSDR;
          break;
        case PWM_MIN_DUTY_CYCLE_VALUE: /* Set PWGCnCRDR to PWGCnCSDR value for Duty 0 % */
          LpDiagCh->pPWGC->ulPWGCnCRDR = (uint32)PWM_PERIOD_LIMIT + 1UL;
          break;
        default: /* Set PWGCnCRDR to calculate: Duty 1% - 99% */
          LulPWGCnCSDR = (LulPWGCPRD * LusDutyCycle) >> PWM_DUTY_CALC_DIV;                                              /* PRQA S 3383 # JV-01 */
          /* Add offset */
          LulPWGCnCSDR += LpDiagCh->usOffset;                                                                           /* PRQA S 3383 # JV-01 */
          if (LulPWGCnCSDR > LulPWGCPRD)
          {
            /* Adjust offset */
            LulPWGCnCSDR -= LulPWGCPRD;                                                                                 /* PRQA S 3383 # JV-01 */
          } /* else: No action */
          /* Set rising edge and falling edge timing */
          LpDiagCh->pPWGC->usPWGCnCSDR = (uint16)LulPWGCnCSDR;
          LpDiagCh->pPWGC->ulPWGCnCRDR = LpDiagCh->usOffset;
          break;
      } /* End of switch */
    } /* End of if (PWM_HIGH == Pwm_GpChannelConfig[LddChannelId].ucPolarity) */
    /* Rewrite request */
    LpDiagCh->pPWGC->ucPWGCnRDT = PWM_DIAG_REWRITE_REQUEST;
  }
  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  else
  {
    /* Set Dem error flag */
    blDemReport = PWM_TRUE;
  }
  #endif

  /* Exit protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);

  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  if (PWM_TRUE == blDemReport)
  {
    /*Report to DEM module*/
    PWM_DEM_REPORT_ERROR(PWM_E_REWRITE_FAILED, DEM_EVENT_STATUS_FAILED);
  } /* else No action required */
  #endif

} /* End of Pwm_HW_DIAG_SetDutyCycle() function */

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_SET_DUTY_CYCLE_API == STD_ON */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_DIAG_SetOutputToIdle
**
** Service ID           : NA
**
** Description          : This function set the channels output to the configured idle level
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different channel
**
** Input Parameters     : LddChannelId
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : PWM_SET_OUTPUT_TO_IDLE_API is STD_ON
**
** Global Variables     : Pwm_GpChannelConfig
**
** Functions invoked    : PWM_DEM_REPORT_ERROR
**
** Registers Used       : PWGCnRDT, PWGCnCSDR, PWGCnCRDR, PWGCnST
**
** Reference ID         : PWM_DUD_ACT_085, PWM_DUD_ACT_085_REG001, PWM_DUD_ACT_085_REG002,
** Reference ID         : PWM_DUD_ACT_085_REG003, PWM_DUD_ACT_085_REG004, PWM_DUD_ACT_085_ERR001
** Reference ID         : PWM_DUD_ACT_085_CRT001, PWM_DUD_ACT_085_CRT002
***********************************************************************************************************************/
#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_DIAG_SetOutputToIdle(Pwm_ChannelType LddChannelId)
{
  P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagCh;
  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  VAR(boolean, AUTOMATIC) blDemReport;

  /* Initialize DEM report status */
  blDemReport = PWM_FALSE;
  #endif

  /* Load configuration */
  LpDiagCh = (P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA))                                           /* PRQA S 0316 # JV-01 */
  Pwm_GpChannelConfig[LddChannelId].pHWIPChannelConfig;
  
  /* Enter protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);

  /* Check whether simultaneous rewrite has been completed */
  if (PWM_DIAG_RESET_16BIT == (uint16)(LpDiagCh->pPWGC->usPWGCnST & PWM_DIAG_RESET_16BIT_RSF))                          /* PRQA S 0404 # JV-01 */
  {
    /* Checking idle level */
    if ((uint8)PWM_HIGH == Pwm_GpChannelConfig[LddChannelId].ucIdleLevel)                                               /* PRQA S 3416 # JV-01 */
    {
      /* Set output to HIGH state */
      if ((uint32)LpDiagCh->pPWGC->usPWGCnCSDR <= LpDiagCh->pPWGC->ulPWGCnCRDR)                                         /* PRQA S 0404 # JV-01 */
      {
        LpDiagCh->pPWGC->usPWGCnCSDR = (uint16)PWM_ZERO;
      } /* else no action required */
      LpDiagCh->pPWGC->ulPWGCnCRDR = (uint32)PWM_PERIOD_LIMIT + 1UL;
    }
    else /* (PWM_LOW == ucIdleLevel) case */
    {
      /* Set output to LOW state */
      LpDiagCh->pPWGC->ulPWGCnCRDR = LpDiagCh->pPWGC->usPWGCnCSDR;
    }
  /* Rewrite request */
  LpDiagCh->pPWGC->ucPWGCnRDT = PWM_DIAG_REWRITE_REQUEST;
  }
  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  else
  {
    /* Set Dem error flag */
    blDemReport = PWM_TRUE;
  }
  #endif

  /* Exit protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);

  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  if (PWM_TRUE == blDemReport)
  {
    /*Report to DEM module*/
    PWM_DEM_REPORT_ERROR(PWM_E_REWRITE_FAILED, DEM_EVENT_STATUS_FAILED);
  } /* else No action required */
  #endif

} /* End of Pwm_HW_DIAG_SetOutputToIdle() function */

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_SET_OUTPUT_TO_IDLE_API == STD_ON */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_DIAG_DisableNotification
**
** Service ID           : NA
**
** Description          : This function disable interrupt of PWM-Diag channel.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different channel
**
** Input Parameters     : LddChannelId
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : PWM_NOTIFICATION_SUPPORTED is STD_ON
**
** Global Variables     : Pwm_GpDiagConfig, Pwm_GpChannelConfig
**
** Functions invoked    : None
**
** Registers Used       : PWGCnCTL, PWGCINTMSKhk
**
** Reference ID         : PWM_DUD_ACT_086, PWM_DUD_ACT_086_REG001, PWM_DUD_ACT_086_REG002,
** Reference ID         : PWM_DUD_ACT_086_CRT001, PWM_DUD_ACT_086_CRT002
***********************************************************************************************************************/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_DIAG_DisableNotification(Pwm_ChannelType LddChannelId)
{
  P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagCh;
  P2CONST(Pwm_DiagUnitConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagConfig;

  /* Load configuration */
  LpDiagConfig = Pwm_GpDiagConfig;
  LpDiagCh = (P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA))                                           /* PRQA S 0316 # JV-01 */
    Pwm_GpChannelConfig[LddChannelId].pHWIPChannelConfig;
  /* Enter protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

  /* Disable rising/falling edge interrupt */
  LpDiagCh->pPWGC->usPWGCnCTL &= ~(PWM_DIAG_RISING_EDGE|PWM_DIAG_FALLING_EDGE);
  /* Disable interrupt of DIAG */
  LpDiagConfig->pPWGC_INTF[LpDiagCh->ucNotifyGrId].aaPWGC_INTF[LpDiagCh->ucGroupId].ulPWGCINTMSKhk
    |= 1UL << (LpDiagCh->ucChNo & 0x1FUL);

  /* Exit protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

} /* End of Pwm_HW_DIAG_DisableNotification() function */

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_NOTIFICATION_SUPPORTED == STD_ON */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_DIAG_EnableNotification
**
** Service ID           : NA
**
** Description          : This function enable interrupt of PWM-Diag channel.
**                      : And select edge of notification.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different channel
**
** Input Parameters     : LddChannelId, LenNotification
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : PWM_NOTIFICATION_SUPPORTED is STD_ON
**
** Global Variables     : Pwm_GpDiagConfig, Pwm_GpChannelConfig, Pwm_GaaNotifStatus
**
** Functions invoked    : None
**
** Registers Used       : PWGCnCTL, PWGCINTMSKhk
**
** Reference ID         : PWM_DUD_ACT_087, PWM_DUD_ACT_087_GBL001, PWM_DUD_ACT_087_REG001, PWM_DUD_ACT_087_REG002,
** Reference ID         : PWM_DUD_ACT_087_REG003, PWM_DUD_ACT_087_REG004,
** Reference ID         : PWM_DUD_ACT_087_CRT001, PWM_DUD_ACT_087_CRT002
***********************************************************************************************************************/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_DIAG_EnableNotification(
  Pwm_ChannelType LddChannelId, Pwm_EdgeNotificationType LenNotification)
{
  P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagCh;
  P2CONST(Pwm_DiagUnitConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagConfig;

  /* Load configuration */
  LpDiagConfig = Pwm_GpDiagConfig;
  LpDiagCh = (P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA))                                           /* PRQA S 0316 # JV-01 */
    Pwm_GpChannelConfig[LddChannelId].pHWIPChannelConfig;
  /* Enter protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);

  switch(LenNotification)
  {
    case PWM_RISING_EDGE:
      /* Enable rising edge */
      LpDiagCh->pPWGC->usPWGCnCTL |= PWM_DIAG_RISING_EDGE;
      break;
    case PWM_FALLING_EDGE:
      /* Enable falling edge */
      LpDiagCh->pPWGC->usPWGCnCTL |= PWM_DIAG_FALLING_EDGE;
      break;
    default: /* PWM_BOTH_EDGES case */
      /* Enable both edge */
      LpDiagCh->pPWGC->usPWGCnCTL |= (PWM_DIAG_RISING_EDGE | PWM_DIAG_FALLING_EDGE);
      break;
  } /* End of switch */

  /* Enable interrupt of DIAG */
  LpDiagConfig->pPWGC_INTF[LpDiagCh->ucNotifyGrId].aaPWGC_INTF[LpDiagCh->ucGroupId].ulPWGCINTMSKhk
    &= ~(1UL << (LpDiagCh->ucChNo & 0x1FUL));


  /* Check whether any notification is configured for this channel */
  if (NULL_PTR != Pwm_GpChannelConfig[LddChannelId].pPwmEdgeNotifPtr)                                                   /* PRQA S 3416 # JV-01 */
  {
    /* Set the Notification enable status as PWM_TRUE for this channel */
    Pwm_GaaNotifStatus[LddChannelId] = (uint8)PWM_TRUE;                                                                 /* PRQA S 4304 # JV-01 */
  } /* else No action required */

  /* Exit protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
} /* End of Pwm_HW_DIAG_EnableNotification() function */

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_NOTIFICATION_SUPPORTED == STD_ON */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_DIAG_DisableAdTrigger
**
** Service ID           : NA
**
** Description          : This function disables A/D Trigger of PWM-Diag channel.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different channel
**
** Input Parameters     : LddChannelId
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : PWM_ENABLE_DISABLE_AD_TRG_API is STD_ON
**
** Global Variables     : Pwm_GpChannelConfig
**
** Functions invoked    : PWM_DEM_REPORT_ERROR
**
** Registers Used       : PWGCnTCR, PWGCnRDT, PWGCnST
**
** Reference ID         : PWM_DUD_ACT_088, PWM_DUD_ACT_088_REG001, PWM_DUD_ACT_088_REG002, PWM_DUD_ACT_088_REG003
** Reference ID         : PWM_DUD_ACT_088_CRT001, PWM_DUD_ACT_088_CRT002, PWM_DUD_ACT_088_ERR001
***********************************************************************************************************************/
#if (PWM_ENABLE_DISABLE_AD_TRG_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_DIAG_DisableAdTrigger(Pwm_ChannelType LddChannelId)
{
  P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagCh;
  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  VAR(boolean, AUTOMATIC) blDemReport;

  /* Initialize DEM report status */
  blDemReport = PWM_FALSE;
  #endif

  /* Load configuration */
  LpDiagCh = (P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA))                                           /* PRQA S 0316 # JV-01 */
    Pwm_GpChannelConfig[LddChannelId].pHWIPChannelConfig;
    
  /* Enter protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

  /* Check whether A/D Trigger is rising edge or failing edge */
  if ((PWM_DIAG_AD_TRIGGER_RISING_EDGE == (uint16)(LpDiagCh->usPWGCnCTL_Value & PWM_DIAG_AD_TRIGGER_RISING_EDGE)) ||
     (PWM_DIAG_AD_TRIGGER_FALLING_EDGE == (uint16)(LpDiagCh->usPWGCnCTL_Value & PWM_DIAG_AD_TRIGGER_FALLING_EDGE)))
  {
     /* Check whether simultaneous rewrite has been completed */
     if (PWM_DIAG_RESET_16BIT == (uint16)(LpDiagCh->pPWGC->usPWGCnST & PWM_DIAG_RESET_16BIT_RSFT))                      /* PRQA S 0404 # JV-01 */
     {
       /* Disable ouptput */
       LpDiagCh->pPWGC->ucPWGCnTCR = PWM_DIAG_DISABLE_OUTPUT;
       /* Rewrite request */
       LpDiagCh->pPWGC->ucPWGCnRDT = PWM_DIAG_PWGC_RDTT;
     }
     #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
     else
     {
       /* Set Dem error flag */
       blDemReport = PWM_TRUE;
     }
     #endif
  }
  else
  {
    /* Disable ouptput */
    LpDiagCh->pPWGC->ucPWGCnTCR = PWM_DIAG_DISABLE_OUTPUT;
  }

  /* Exit protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  if (PWM_TRUE == blDemReport)
  {
    /*Report to DEM module*/
    PWM_DEM_REPORT_ERROR(PWM_E_REWRITE_FAILED, DEM_EVENT_STATUS_FAILED);
  } /* else No action required */
  #endif
} /* End of Pwm_HW_DIAG_DisableAdTrigger() function */

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_ENABLE_DISABLE_AD_TRG_API == STD_ON */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_DIAG_EnableAdTrigger
**
** Service ID           : NA
**
** Description          : This function Enables A/D Trigger of PWM-Diag channel.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different channel
**
** Input Parameters     : LddChannelId
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : PWM_ENABLE_DISABLE_AD_TRG_API is STD_ON
**
** Global Variables     : Pwm_GpChannelConfig
**
** Functions invoked    : PWM_DEM_REPORT_ERROR
**
** Registers Used       : PWGCnTCR, PWGCnRDT, PWGCnST
**
** Reference ID         : PWM_DUD_ACT_089, PWM_DUD_ACT_089_REG001, PWM_DUD_ACT_089_REG002, PWM_DUD_ACT_089_REG003
** Reference ID         : PWM_DUD_ACT_089_CRT001, PWM_DUD_ACT_089_CRT002, PWM_DUD_ACT_089_ERR001
***********************************************************************************************************************/
#if (PWM_ENABLE_DISABLE_AD_TRG_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_DIAG_EnableAdTrigger(Pwm_ChannelType LddChannelId)
{
  P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagCh;
  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  VAR(boolean, AUTOMATIC) blDemReport;

  /* Initialize DEM report status */
  blDemReport = PWM_FALSE;
  #endif

  /* Load configuration */
  LpDiagCh = (P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA))                                           /* PRQA S 0316 # JV-01 */
    Pwm_GpChannelConfig[LddChannelId].pHWIPChannelConfig;

  /* Enter protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

  /* Check whether A/D Trigger is rising edge or failing edge */
  if ((PWM_DIAG_AD_TRIGGER_RISING_EDGE == (uint16)(LpDiagCh->usPWGCnCTL_Value & PWM_DIAG_AD_TRIGGER_RISING_EDGE)) ||
     (PWM_DIAG_AD_TRIGGER_FALLING_EDGE == (uint16)(LpDiagCh->usPWGCnCTL_Value & PWM_DIAG_AD_TRIGGER_FALLING_EDGE)))
  {
     /* Check whether simultaneous rewrite has been completed */
     if (PWM_DIAG_RESET_16BIT == (uint16)(LpDiagCh->pPWGC->usPWGCnST & PWM_DIAG_RESET_16BIT_RSFT))                      /* PRQA S 0404 # JV-01 */
     {
       /* Enable ouptput */
       LpDiagCh->pPWGC->ucPWGCnTCR = PWM_DIAG_ENABLE_OUTPUT;
       /* Rewrite request */
       LpDiagCh->pPWGC->ucPWGCnRDT = PWM_DIAG_PWGC_RDTT;
     }
     #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
     else
     {
       /* Set Dem error flag */
       blDemReport = PWM_TRUE;
     }
     #endif
  }
  else
  {
    /* Enable ouptput */
    LpDiagCh->pPWGC->ucPWGCnTCR = PWM_DIAG_ENABLE_OUTPUT;
  }

  /* Exit protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_RAM_DATA_PROTECTION_GLOBAL);

  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  if (PWM_TRUE == blDemReport)
  {
    /*Report to DEM module*/
    PWM_DEM_REPORT_ERROR(PWM_E_REWRITE_FAILED, DEM_EVENT_STATUS_FAILED);
  } /* else No action required */
  #endif
} /* End of Pwm_HW_DIAG_EnableAdTrigger() function */

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_ENABLE_DISABLE_AD_TRG_API == STD_ON */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_DIAG_SetTriggerDelay
**
** Service ID           : NA
**
** Description          : This function set A/D Trigger timing for Diag channel during runtime.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different channel
**
** Input Parameters     : LddChannelId, LusTriggerDelay
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : PWM_SET_TRIGGER_DELAY_API is STD_ON
**
** Global Variables     : Pwm_GpDiagConfig, Pwm_GpChannelConfig
**
** Functions invoked    : PWM_DEM_REPORT_ERROR
**
** Registers Used       : PWGCnCTDR, PWGCnRDT, PWGCnST
**
** Reference ID         : PWM_DUD_ACT_090, PWM_DUD_ACT_090_REG001, PWM_DUD_ACT_090_REG002
** Reference ID         : PWM_DUD_ACT_090_ERR001, PWM_DUD_ACT_090_REG003
** Reference ID         : PWM_DUD_ACT_090_CRT001, PWM_DUD_ACT_090_CRT002
***********************************************************************************************************************/
#if (PWM_SET_TRIGGER_DELAY_API ==STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_DIAG_SetTriggerDelay(Pwm_ChannelType LddChannelId, uint16 LusTriggerDelay)
{
  P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagCh;
  P2CONST(Pwm_DiagUnitConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagConfig;
  VAR(uint32, AUTOMATIC) LulPWGCnCTDR; /* Register size is 16bit but it set to 32bit for reduce cast */
  VAR(uint32, AUTOMATIC) LulPWGCPRD;  /* Register size is 16bit but it set to 32bit for reduce cast */
  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  VAR(boolean, AUTOMATIC) blDemReport;

  /* Initialize DEM report status */
  blDemReport = PWM_FALSE;
  #endif

  /* Load configuration */
  LpDiagConfig = Pwm_GpDiagConfig;
  LpDiagCh = (P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA))                                           /* PRQA S 0316 # JV-01 */
  Pwm_GpChannelConfig[LddChannelId].pHWIPChannelConfig;
  
  /* Enter protected area */
  PWM_ENTER_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);

  /* Read period value */
  LulPWGCPRD = LpDiagConfig->pSLPWG->aaPWGCPRDm[LpDiagCh->ucPeriodId].usPWGCPRDm;
  /* Set Trigger delay to local variable */
  LulPWGCnCTDR = (LulPWGCPRD * LusTriggerDelay) >> PWM_DUTY_CALC_DIV;                                                   /* PRQA S 3383 # JV-01 */

  /* Check Trigger Adjust Offset is true*/
  if (PWM_TRUE == LpDiagCh->blTriggerAdjustOffset)
  {
    /* Add offset to trigger */
    LulPWGCnCTDR += LpDiagCh->usOffset;                                                                                 /* PRQA S 3383 # JV-01 */
    if (LulPWGCnCTDR > LulPWGCPRD)
    {
      /* Adjust offset to trigger */
      LulPWGCnCTDR -= LulPWGCPRD;                                                                                       /* PRQA S 3383 # JV-01 */
    } /* else: No action */
  } /* else: No action */

  /* Check whether simultaneous rewrite has been completed */
  if (PWM_DIAG_RESET_16BIT == (uint16)(LpDiagCh->pPWGC->usPWGCnST & PWM_DIAG_RESET_16BIT_RSF))                          /* PRQA S 0404 # JV-01 */
  {
    /* Setting AD trigger timing */
    LpDiagCh->pPWGC->usPWGCnCTDR = (uint16)LulPWGCnCTDR;
    /* Rewrite request */
    LpDiagCh->pPWGC->ucPWGCnRDT = PWM_DIAG_REWRITE_REQUEST;
  }
  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  else
  {
    /* Set Dem error flag */
    blDemReport = PWM_TRUE;
  }
  #endif

  /* Exit protected area */
  PWM_EXIT_CRITICAL_SECTION(PWM_INTERRUPT_CONTROL_PROTECTION);

  #if (STD_ON == PWM_E_REWRITE_FAILED_CONFIGURED)
  if (PWM_TRUE == blDemReport)
  {
    /*Report to DEM module*/
    PWM_DEM_REPORT_ERROR(PWM_E_REWRITE_FAILED, DEM_EVENT_STATUS_FAILED);
  } /* else No action required */
  #endif

} /* End of Pwm_HW_DIAG_SetTriggerDelay() function */

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* End of PWM_SET_TRIGGER_DELAY_API ==STD_ON */

/***********************************************************************************************************************
** Function Name        : Pwm_HW_DIAG_ReadAdConvResult
**
** Service ID           : NA
**
** Description          : This function read A/D conversion result.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different channel
**
** Input Parameters     : LddChannelId
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : uint32
**
** Preconditions        : PWM_READ_CONV_RESLUT_API is STD_ON
**
** Global Variables     : Pwm_GpDiagConfig, Pwm_GpChannelConfig
**
** Functions invoked    : none
**
** Registers Used       : PWSDnPWDDIRx
**
** Reference ID         : PWM_DUD_ACT_091, PWM_DUD_ACT_091_REG001
***********************************************************************************************************************/
#if (PWM_READ_CONV_RESLUT_API == STD_ON)
#define PWM_START_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(uint32, PWM_PRIVATE_CODE) Pwm_HW_DIAG_ReadAdConvResult(Pwm_ChannelType LddChannelId)
{
  P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagCh;
  P2CONST(Pwm_DiagUnitConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagConfig;
  VAR(uint32, AUTOMATIC) LulAdConvResult;

  /* Load configuration */
  LpDiagConfig = Pwm_GpDiagConfig;
  LpDiagCh = (P2CONST(Pwm_DiagChannelConfigType, AUTOMATIC, PWM_CONFIG_DATA))                                           /* PRQA S 0316 # JV-01 */
    Pwm_GpChannelConfig[LddChannelId].pHWIPChannelConfig;
  /* Read PWSDnPWDDIRx register */
  LulAdConvResult = LpDiagConfig->pPWSD->aaPWSDnPWDDIRx[LpDiagCh->ucChNo].ulPWSDnPWDDIRx;

  /* Return AD conversion result */
  return LulAdConvResult;
} /* End of Pwm_HW_DIAG_ReadAdConvResult() function */

#define PWM_STOP_SEC_PRIVATE_CODE
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif

/***********************************************************************************************************************
** Function Name        : Pwm_HW_DIAG_Callback
**
** Service ID           : NA
**
** Description          : This function callback function of DIAG channels.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different channel
**
** Input Parameters     : LucNotifyGrId, LucGrId
**
** InOut Parameters     : none
**
** Output Parameters    : none
**
** Return parameter     : none
**
** Preconditions        : none
**
** Global Variables     : Pwm_GpDiagConfig
**
** Functions invoked    : Configured notification function, PWM_DEM_REPORT_ERROR
**
** Registers Used       : EICn, PWGCINTFChk
**
** Reference ID         : PWM_DUD_ACT_092, PWM_DUD_ACT_092_REG002 PWM_DUD_ACT_092_ERR001
***********************************************************************************************************************/
#define PWM_START_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

FUNC(void, PWM_PRIVATE_CODE) Pwm_HW_DIAG_Callback(uint8 LucNotifyGrId, uint8 LucGrId )
{
  P2CONST(Pwm_DiagUnitConfigType, AUTOMATIC, PWM_CONFIG_DATA) LpDiagConfig;
  VAR(uint32, AUTOMATIC) LulIntFactor;

  /* Load configuration */
  LpDiagConfig = Pwm_GpDiagConfig;

  #if (PWM_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
  /* Interrupt consistency check */
  if ((0xFFFFFFFFUL == LpDiagConfig->pPWGC_INTF[LucNotifyGrId].aaPWGC_INTF[LucGrId].ulPWGCINTMSKhk)
   || (PWM_ZERO != (*Pwm_GpDiagConfig->pDiagNotiGrConfig->aaDiagNotifyConfig[LucNotifyGrId][LucGrId]->pEICn
                    & PWM_EIC_EIMK_MASK)))
  {
    /* DEM report error */
    PWM_DEM_REPORT_ERROR(PWM_E_INT_INCONSISTENT, DEM_EVENT_STATUS_FAILED);
  }
  else
  #endif
  {
    /* Read interrupt factor */
    LulIntFactor = LpDiagConfig->pPWGC_INTF[LucNotifyGrId].aaPWGC_INTF[LucGrId].ulPWGCINTFhk;
    /* Clear interrupt factor */
    LpDiagConfig->pPWGC_INTF[LucNotifyGrId].aaPWGC_INTF[LucGrId].ulPWGCINTFChk = LulIntFactor;
    #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
    if (NULL_PTR != LpDiagConfig->pDiagNotiGrConfig->aaDiagNotifyConfig[LucNotifyGrId][LucGrId]->pNotifyFunc)
    {
      /* Invoke notify group */
      LpDiagConfig->pDiagNotiGrConfig->aaDiagNotifyConfig[LucNotifyGrId][LucGrId]->pNotifyFunc(LulIntFactor);
    } /* else: No action */
    #endif
  } /* End of interrupt consistency check */
} /* End of Pwm_HW_DIAG_Callback() function */

#define PWM_STOP_SEC_CODE_FAST
#include "Pwm_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* End of PWM_DIAG_UNIT_USED == STD_ON */
/***********************************************************************************************************************
**                                              End of File                                                           **
***********************************************************************************************************************/
