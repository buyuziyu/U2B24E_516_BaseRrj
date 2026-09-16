/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = FlsTst.c                                                                                            */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of Flash Test Driver Component.                                                       */
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
 * 1.4.1:  30/06/2025  : Update SW-VERSION
 * 1.3.1:  31/03/2025  : To support QAC 11.6.0: Add msg 3006
 * 1.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Relase
 * 1.1.2:  31/10/2024  : Update SW Version to 1.1.2
 * 1.1.1:  30/08/2024  : As part of QAC 9.5.0 support, following changes are made:
 *                       1. Add message: 0303, 3383, 2814, 2824, 2844 
 * 1.1.0:  22/02/2024  : Update SW-VERSION to 1.1.0
 * 1.0.1:  18/10/2023  : Add QAC message 2982, 1881, 3006
 *         17/10/2023  : Update to read last signature if background test fail
 *         22/09/2023  : Add check if defined FLSTST_E_FLSTST_FAILURE before report DEM
 * 1.0.0:  17/03/2023  : Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "FlsTst.h"
/* Global RAM variables header file */
#include "FlsTst_Ram.h"
#if (FLSTST_DEV_ERROR_DETECT == STD_ON)
/* Development Error header file */
#include "Det.h"
#endif
/* Dem header file */
#include "Dem.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define FLSTST_C_AR_RELEASE_MAJOR_VERSION    FLSTST_AR_RELEASE_MAJOR_VERSION_VALUE
#define FLSTST_C_AR_RELEASE_MINOR_VERSION    FLSTST_AR_RELEASE_MINOR_VERSION_VALUE
#define FLSTST_C_AR_RELEASE_REVISION_VERSION FLSTST_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define FLSTST_C_SW_MAJOR_VERSION            FLSTST_SW_MAJOR_VERSION_VALUE
#define FLSTST_C_SW_MINOR_VERSION            FLSTST_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (FLSTST_AR_RELEASE_MAJOR_VERSION != FLSTST_C_AR_RELEASE_MAJOR_VERSION)
#error "FlsTst.c : Mismatch in Release Major Version"
#endif

#if (FLSTST_AR_RELEASE_MINOR_VERSION != FLSTST_C_AR_RELEASE_MINOR_VERSION)
#error "FlsTst.c : Mismatch in Release Minor Version"
#endif

#if (FLSTST_AR_RELEASE_REVISION_VERSION != FLSTST_C_AR_RELEASE_REVISION_VERSION)
#error "FlsTst.c : Mismatch in Release Revision Version"
#endif

#if (FLSTST_SW_MAJOR_VERSION != FLSTST_C_SW_MAJOR_VERSION)
#error "FlsTst.c : Mismatch in Software Major Version"
#endif

#if (FLSTST_SW_MINOR_VERSION != FLSTST_C_SW_MINOR_VERSION)
#error "FlsTst.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/**********************************************************************************************************************/
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold.                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569, CWE-738                    */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0759)    : An object of union type has been defined.                                                    */
/* Rule                : MISRA C:2012 Rule-19.2, CWE Rule CWE-843                                                     */
/* JV-01 Justification : Data access of larger data types is used to achieve better throughput.                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function 'name' is defined but is not used within this project.                          */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the             */
/*                       expression should be split up into individual dynamic operations, with their own guards      */
/*                       where applicable.                                                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1006)    : [E] This in-line assembler construct is a language extension. The code has been ignored.     */
/* Rule                : MISRA-C:2012 Dir-1.1, Rule-1.2, Dir-4.2, CERTC 1.2.4 MSC14                                   */
/* JV-01 Justification : Inline assembler support for syncp instruction.                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : MISRA C:2012 Rule-2.2, CERTCCM MSC07, MSC13, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563,     */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:1881)    : The operands of this equality operator are expressions of different 'essential type'         */
/*                       categories (%1s and %2s).                                                                    */
/* Rule                : MISRA C:2012 Rule-10.4, CERTCCM INT02, CWE Rule CWE-136, CWE-192                             */
/* JV-01 Justification : The equality operator between enum and unsigned type can be accepted.                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3006)    : This function contains a mixture of in-line assembler statements and C statements.           */
/* Rule                : MISRA C:2012 Dir-4.3, CWE Rule CWE-398, CWE-569                                              */
/* JV-01 Justification : This is accepted, due to the implementation is following hardware specification.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define FLSTST_START_SEC_PRIVATE_CODE
#include "FlsTst_MemMap.h"

#if (FLSTST_START_FGND_API == STD_ON)
static void FlsTst_ReadLoadMemData(
  volatile P2CONST(uint8, AUTOMATIC, FLSTST_APPL_CONST) LpReadAddress,
  volatile P2VAR(uint32, AUTOMATIC, FLSTST_APPL_DATA) LpCrcAddr,                                                        /* PRQA S 3432 # JV-01 */
  const uint32 LulSize);

static uint8 FlsTst_InitFgndTest(
  P2CONST(FlsTstBlock_ConfigType, AUTOMATIC, FLSTST_CONFIG_CONST) LpFlsTstBlock);
#endif
#if (FLSTST_BGND_TEST_ENABLE == STD_ON)
static void FlsTst_ReadLoadMemDataBgnd(
  P2CONST(FlsTstBlock_ConfigType, AUTOMATIC, FLSTST_CONFIG_CONST) LpFlsTstBlock);

static void FlsTst_GetStoredCRC(
  P2CONST(FlsTstBlock_ConfigType, AUTOMATIC, FLSTST_CONFIG_CONST) LpFlsTstBlock,
  P2VAR(uint32, AUTOMATIC, FLSTST_APPL_DATA) LpStoredBgndCrc);                                                          /* PRQA S 3432 # JV-01 */

static void FlsTst_InitBgndTest(
  P2CONST(FlsTstBlock_ConfigType, AUTOMATIC, FLSTST_CONFIG_CONST) LpFlsTstBlock);
#endif
#if (FLSTST_TEST_ECC_API  == STD_ON) && (FLSTST_TEST_ECC_CF_BANK == STD_ON)
static Std_ReturnType FlsTst_TestEccCFBank(void);
#endif

#if (FLSTST_TEST_ECC_API  == STD_ON) && (FLSTST_TEST_ECC_CF_GLOBAL == STD_ON)
static Std_ReturnType FlsTst_TestEccCFGlobal(void);
#endif

#define FLSTST_STOP_SEC_PRIVATE_CODE
#include "FlsTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

#define FLSTST_START_SEC_PUBLIC_CODE
#include "FlsTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : FlsTst_Init
**
** Service ID            : 0x00
**
** Description           : This API performs the initialization of the FLSTST
**                         Driver Component.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
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
** Global Variables Used : FlsTst_GpConfigPtr(W), FlsTst_GpBgndBlk(W),
**                         FlsTst_GpFgndBlk(W), FlsTst_GenOverallBgndResult(W),
**                         FlsTst_GenLastFgndResult(W), FlsTst_GucTestComplete(W)
**                         FlsTst_GaaLastFgndSignature(W), FlsTst_GblTestComplete(W),
**                         FlsTst_GaaLastBgndSignature(W),
**                         FlsTst_GulTestIntervalId(R), FlsTst_GenExeState(R/W),
**                         FlsTst_GVar.FlsTst_GenBgndCheckState(W),
**                         FlsTst_GVar.FlsTst_GulBgndConfigIndex(W),
**                         FlsTst_GVar.FlsTst_GulCalculatedCrc(W),
**                         FlsTst_GVar.FlsTst_GulCalculatedCrc_H(W),
**                         FlsTst_GVar.FlsTst_GulReadAddress(W).
**                         FlsTst_GddEccErrorDetail.ucCFGlobalEccStatus(W),
**                         FlsTst_GddEccErrorDetail.ulCFGlobalEccFaultAddress(W),
**                         FlsTst_GddEccErrorDetail.ucCFBankEccStatus(W),
**                         FlsTst_GddEccErrorDetail.ulCFBankEccFaultAddress(W).
**
** Function(s) invoked   : Det_ReportError, FlsTst_InitRAMMirror
**
** Registers Used        : KCRCDIN, KCRCDOUT0, KCRCDOUT1, KCRCCTL, KCRCPOLY0, 
**                         KCRCPOLY1, KCRCXOR0, KCRCXOR1, CFSECCCTL, CF_ERRINT,
**                         CF_SERSTR, CF_00SEADR, CF_DERSTR, CF_00DEADR, CFCECCCTL.
**
** Reference ID          : FLSTST_DUD_ACT_001,
** Reference ID          : FLSTST_DUD_ACT_001_ERR001, FLSTST_DUD_ACT_001_ERR002, FLSTST_DUD_ACT_001_ERR003, 
** Reference ID          : FLSTST_DUD_ACT_001_ERR004, FLSTST_DUD_ACT_001_ERR005
** Reference ID          : FLSTST_DUD_ACT_001_REG001, FLSTST_DUD_ACT_001_REG002, FLSTST_DUD_ACT_001_REG003, 
** Reference ID          : FLSTST_DUD_ACT_001_REG004, FLSTST_DUD_ACT_001_REG005, FLSTST_DUD_ACT_001_REG006,
** Reference ID          : FLSTST_DUD_ACT_001_REG007, FLSTST_DUD_ACT_001_REG008, FLSTST_DUD_ACT_001_REG009, 
** Reference ID          : FLSTST_DUD_ACT_001_REG010, FLSTST_DUD_ACT_001_REG011, FLSTST_DUD_ACT_001_REG012,  
** Reference ID          : FLSTST_DUD_ACT_001_REG013, FLSTST_DUD_ACT_001_REG014, FLSTST_DUD_ACT_001_REG015,
** Reference ID          : FLSTST_DUD_ACT_001_REG016,
** Reference ID          : FLSTST_DUD_ACT_001_GBL001, FLSTST_DUD_ACT_001_GBL002, FLSTST_DUD_ACT_001_GBL003,
** Reference ID          : FLSTST_DUD_ACT_001_GBL004, FLSTST_DUD_ACT_001_GBL005, FLSTST_DUD_ACT_001_GBL006,
** Reference ID          : FLSTST_DUD_ACT_001_GBL007, FLSTST_DUD_ACT_001_GBL008, FLSTST_DUD_ACT_001_GBL009,
** Reference ID          : FLSTST_DUD_ACT_001_GBL010, FLSTST_DUD_ACT_001_GBL011, FLSTST_DUD_ACT_001_GBL012
***********************************************************************************************************************/

FUNC(void, FLSTST_PUBLIC_CODE) FlsTst_Init(                                                                             /* PRQA S 1503 # JV-01 */
    P2CONST(FlsTst_ConfigType, AUTOMATIC, FLSTST_APPL_CONST) ConfigPtr)
{
  #if (FLSTST_DEV_ERROR_DETECT == STD_ON)
  #if (FLSTST_ALREADY_INIT_DET_CHECK == STD_ON)
  if (FLSTST_UNINIT != FlsTst_GenExeState)
  {
    (void)Det_ReportError(FLSTST_MODULE_ID,
      FLSTST_INSTANCE_ID, FLSTST_INIT_SID, FLSTST_E_ALREADY_INITIALIZED);
  }
  else
  #endif /* (FLSTST_ALREADY_INIT_DET_CHECK == STD_ON) */
  /* Check if configuration pointer is a NULL Pointer */
  if (NULL_PTR == ConfigPtr)
  {
    (void)Det_ReportError(FLSTST_MODULE_ID,
      FLSTST_INSTANCE_ID, FLSTST_INIT_SID, FLSTST_E_INIT_FAILED);
  }
  /* Initialize the module only if Database is present */
  else if (FLSTST_DBTOC_VALUE != ConfigPtr->ulStartOfDbToc)
  {
    (void)Det_ReportError(FLSTST_MODULE_ID,
      FLSTST_INSTANCE_ID, FLSTST_INIT_SID, FLSTST_E_INVALID_DATABASE);
  }
  else
  #endif /* (FLSTST_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check ECC register default value */
    #if (FLSTST_TEST_ECC_CF_GLOBAL == STD_ON) || (FLSTST_TEST_ECC_CF_BANK == STD_ON)
    if ((FLSTST_CF_SERSTR != CF_SERSTR_DEFAULT) ||                                                                      /* PRQA S 0303 # JV-01 */
        (FLSTST_CF_ERRINT != CF_ERRINT_DEFAULT) ||                                                                      /* PRQA S 0303 # JV-01 */
        (FLSTST_CF_DERSTR != CF_DERSTR_DEFAULT) ||                                                                      /* PRQA S 0303 # JV-01 */
        #if (FLSTST_TEST_ECC_CF_GLOBAL == STD_ON)
        (FLSTST_CFSECCCTL != CFSECCCTL_DEFAULT)                                                                         /* PRQA S 0303 # JV-01 */
        #endif
        #if (FLSTST_TEST_ECC_CF_GLOBAL == STD_ON) && (FLSTST_TEST_ECC_CF_BANK == STD_ON)
        ||
        #endif
        #if (FLSTST_TEST_ECC_CF_BANK == STD_ON)
        (FLSTST_CFCECCCTL != CFCECCCTL_DEFAULT)                                                                         /* PRQA S 0303 # JV-01 */
        #endif
        )
    {
      /* Report to Dem if register value is not default */
      #if defined(FLSTST_E_ECC_FAILED)
      (void)Dem_SetEventStatus(FLSTST_E_ECC_FAILED, DEM_EVENT_STATUS_FAILED);
      #endif
    }
    else
    #endif
    {
      /* Assign the Config pointer value to global config pointer */
      FlsTst_GpConfigPtr = ConfigPtr;

      /* Initialize KCRC registers used for background test */
      FLSTST_KCRCDINBGND = FLSTST_LONG_WORD_ZERO;                                                                       /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCDOUT0BGND = FLSTST_KCRCDOUT_RESET_VAL ^ FLSTST_KCRCDOUT_RESET_VAL;                                     /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCDOUT1BGND = FLSTST_KCRCDOUT_RESET_VAL ^ FLSTST_KCRCDOUT_RESET_VAL;                                     /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCCTLBGND = FLST_KCRCCTL_RESET_VAL;                                                                      /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCPOLY0BGND = FLST_KCRCPOLY0_RESET_VAL;                                                                  /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCPOLY1BGND = FLSTST_LONG_WORD_ZERO;                                                                     /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCXOR0BGND = FLSTST_ALL1_VALUE;                                                                          /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCXOR1BGND = FLSTST_LONG_WORD_ZERO;                                                                      /* PRQA S 0303 # JV-01 */

      /* Initialize KCRC registers used for foreground test */
      FLSTST_KCRCDINFGND = FLSTST_LONG_WORD_ZERO;                                                                       /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCDOUT0FGND = FLSTST_KCRCDOUT_RESET_VAL ^ FLSTST_KCRCDOUT_RESET_VAL;                                     /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCDOUT1FGND = FLSTST_KCRCDOUT_RESET_VAL ^ FLSTST_KCRCDOUT_RESET_VAL;                                     /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCCTLFGND = FLST_KCRCCTL_RESET_VAL;                                                                      /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCPOLY0FGND = FLST_KCRCPOLY0_RESET_VAL;                                                                  /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCPOLY1FGND = FLSTST_LONG_WORD_ZERO;                                                                     /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCXOR0FGND = FLSTST_ALL1_VALUE;                                                                          /* PRQA S 0303 # JV-01 */
      FLSTST_KCRCXOR1FGND = FLSTST_LONG_WORD_ZERO;                                                                      /* PRQA S 0303 # JV-01 */

      /* Load start address of background config array to global pointer */
      FlsTst_GpBgndBlk = ConfigPtr->pFlsTstBgndBlkConfig;
      /* Load start address of foreground config array to global pointer */
      FlsTst_GpFgndBlk = ConfigPtr->pFlsTstFgndBlkConfig;
      /* Set background test result */
      #if (FLSTST_TEST_RESULT_SIGNATURE != STD_ON)
      FlsTst_GenOverallBgndResult = FLSTST_RESULT_NOT_TESTED;
      #endif
      /* Set foreground test result */
      FlsTst_GenLastFgndResult = FLSTST_NOT_TESTED;
      /* Initialize signature value */
      FlsTst_GaaLastFgndSignature[FLSTST_ZERO] = FLSTST_ZERO;
      FlsTst_GaaLastFgndSignature[FLSTST_ONE] = FLSTST_ZERO;
      #if (FLSTST_TEST_RESULT_SIGNATURE == STD_ON)
      FlsTst_GaaLastBgndSignature[FLSTST_ZERO] = FLSTST_ZERO;
      FlsTst_GaaLastBgndSignature[FLSTST_ONE] = FLSTST_ZERO;
      #endif
      /* Initialize test interval value */
      FlsTst_GulTestIntervalId = FLSTST_ZERO;
      /* Set test complete flag */
      FlsTst_GblTestComplete = FLSTST_FALSE;
      /* Initialize the global variable */
      FlsTst_GVar.FlsTst_GulBgndConfigIndex = FLSTST_ZERO;
      #if (FLSTST_TEST_RESULT_SIGNATURE != STD_ON)
      FlsTst_GVar.FlsTst_GblCurrentTestFail = FLSTST_FALSE;
      #endif
      FlsTst_GVar.FlsTst_GulCalculatedCrc = FLSTST_ZERO;
      FlsTst_GVar.FlsTst_GulCalculatedCrc_H = FLSTST_ZERO;

      /* Check whether any test blocks are available for the background test */
      if (NULL_PTR != FlsTst_GpBgndBlk)
      {
        FlsTst_GVar.FlsTst_GulReadAddress = FlsTst_GpBgndBlk->ulFlsTstBlockBaseAddress;
      }
      else
      {
        FlsTst_GVar.FlsTst_GulReadAddress = FLSTST_ZERO;
      }

      /* Initialize backgorund check state */
      FlsTst_GVar.FlsTst_GenBgndCheckState = FLSTST_BGND_CHECK_INIT;

      /* Initialize Ecc error information */
      FlsTst_GddEccErrorDetail.ucCFBankEccStatus = FLSTST_ZERO;
      FlsTst_GddEccErrorDetail.ulCFBankEccFaultAddress = FLSTST_ZERO;
      FlsTst_GddEccErrorDetail.ucCFGlobalEccStatus = FLSTST_ZERO;
      FlsTst_GddEccErrorDetail.ulCFGlobalEccFaultAddress = FLSTST_ZERO;

      /* Set module status to initialized */
      FlsTst_GenExeState = FLSTST_INIT;
    }
  }
}

/***********************************************************************************************************************
** Function Name         : FlsTst_DeInit
**
** Service ID            : 0x01
**
** Description           : This API performs the De-Initialization of the FLSTST
**                         Driver Component.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The FlsTst Driver must be initialized
**
** Global Variables Used : FlsTst_GenOverallBgndResult(W),
**                         FlsTst_GenLastFgndResult(W), FlsTst_GulTestIntervalId(W),
**                         FlsTst_GaaLastFgndSignature(W), FlsTst_GblTestComplete (W),
**                         FlsTst_GaaLastBgndSignature(W), FlsTst_GenExeState(R/W),
**                         FlsTst_GVar.FlsTst_GulBgndConfigIndex(W),
**                         FlsTst_GVar.FlsTst_GulCalculatedCrc(W),
**                         FlsTst_GVar.FlsTst_GulCalculatedCrc_H(W),
**                         FlsTst_GVar.FlsTst_GenBgndCheckState(W),
**                         FlsTst_Gvar.FlsTst_GulReadAddress(W),
**                         FlsTst_GddEccErrorDetail.ucCFBankEccStatus(W),
**                         FlsTst_GddEccErrorDetail.ulCFBankEccFaultAddress(W),
**                         FlsTst_GddEccErrorDetail.ucCFGlobalEccStatus(W),
**                         FlsTst_GddEccErrorDetail.ulCFGlobalEccFaultAddress(W).
**
** Function(s) invoked   : Det_ReportError
**
** Registers Used        : KCRCCTL, KCRCDIN, KCRCDOUT0, KCRCDOUT1,
**                         KCRCPOLY0, KCRCPOLY1, KCRCXOR0, KCRCXOR1
** Reference ID          : FLSTST_DUD_ACT_002, FLSTST_DUD_ACT_002_ERR001, FLSTST_DUD_ACT_002_GBL001
** Reference ID          : FLSTST_DUD_ACT_002_GBL002, FLSTST_DUD_ACT_002_GBL003, FLSTST_DUD_ACT_002_GBL004,
** Reference ID          : FLSTST_DUD_ACT_002_GBL005, FLSTST_DUD_ACT_002_GBL006, FLSTST_DUD_ACT_002_GBL007,
** Reference ID          : FLSTST_DUD_ACT_002_GBL008, FLSTST_DUD_ACT_002_GBL009, 
** Reference ID          : FLSTST_DUD_ACT_002_REG001, FLSTST_DUD_ACT_002_REG002, FLSTST_DUD_ACT_002_REG003, 
** Reference ID          : FLSTST_DUD_ACT_002_REG004, FLSTST_DUD_ACT_002_REG005, FLSTST_DUD_ACT_002_REG006,
** Reference ID          : FLSTST_DUD_ACT_002_REG007, FLSTST_DUD_ACT_002_REG008, FLSTST_DUD_ACT_002_REG009,
** Reference ID          : FLSTST_DUD_ACT_002_REG010, FLSTST_DUD_ACT_002_REG011, FLSTST_DUD_ACT_002_REG012,
** Reference ID          : FLSTST_DUD_ACT_002_REG013, FLSTST_DUD_ACT_002_REG014, FLSTST_DUD_ACT_002_REG015,
** Reference ID          : FLSTST_DUD_ACT_002_REG016
***********************************************************************************************************************/
FUNC(void, FLSTST_PUBLIC_CODE) FlsTst_DeInit(void)                                                                      /* PRQA S 1503 # JV-01 */
{
  #if (FLSTST_DEV_ERROR_DETECT == STD_ON)
  if (FLSTST_UNINIT == FlsTst_GenExeState)
  {
    (void)Det_ReportError(FLSTST_MODULE_ID,
      FLSTST_INSTANCE_ID, FLSTST_DEINIT_SID, FLSTST_E_UNINIT);
  }
  else
  #endif /* (FLSTST_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Reset module status to uninitialized */
    FlsTst_GenExeState = FLSTST_UNINIT;
    /* Reset test complete flag */
    FlsTst_GblTestComplete = FLSTST_FALSE;
    /* Reset background test result */
    #if (FLSTST_TEST_RESULT_SIGNATURE != STD_ON)
    FlsTst_GenOverallBgndResult = FLSTST_RESULT_NOT_TESTED;
    #endif
    /* Reset foreground test result */
    FlsTst_GenLastFgndResult = FLSTST_NOT_TESTED;
    /* Reset test interval value */
    FlsTst_GulTestIntervalId = FLSTST_ZERO;
    /* Reset the global variable */
    FlsTst_GVar.FlsTst_GulBgndConfigIndex = FLSTST_ZERO;
    FlsTst_GVar.FlsTst_GulCalculatedCrc = FLSTST_ZERO;
    FlsTst_GVar.FlsTst_GulCalculatedCrc_H = FLSTST_ZERO;
    FlsTst_GVar.FlsTst_GulReadAddress = FLSTST_ZERO;
    FlsTst_GVar.FlsTst_GenBgndCheckState = FLSTST_BGND_CHECK_INIT;
    #if (FLSTST_TEST_RESULT_SIGNATURE != STD_ON)
    FlsTst_GVar.FlsTst_GblCurrentTestFail = FLSTST_FALSE;
    #endif
    /* Reset signature value */
    FlsTst_GaaLastFgndSignature[FLSTST_ZERO] = FLSTST_ZERO;
    FlsTst_GaaLastFgndSignature[FLSTST_ONE] = FLSTST_ZERO;
    #if (FLSTST_TEST_RESULT_SIGNATURE == STD_ON)
    FlsTst_GaaLastBgndSignature[FLSTST_ZERO] = FLSTST_ZERO;
    FlsTst_GaaLastBgndSignature[FLSTST_ONE] = FLSTST_ZERO;
    #endif

    /* Reset Ecc error information */
    FlsTst_GddEccErrorDetail.ucCFBankEccStatus = FLSTST_ZERO;
    FlsTst_GddEccErrorDetail.ulCFBankEccFaultAddress = FLSTST_ZERO;
    FlsTst_GddEccErrorDetail.ucCFGlobalEccStatus = FLSTST_ZERO;
    FlsTst_GddEccErrorDetail.ulCFGlobalEccFaultAddress = FLSTST_ZERO;

    /* Reset the KCRC registers used for background test to default values */
    FLSTST_KCRCCTLBGND = FLST_KCRCCTL_RESET_VAL;                                                                        /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDINBGND = FLSTST_LONG_WORD_ZERO;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT0BGND = FLSTST_KCRCDOUT_RESET_VAL ^ FLSTST_KCRCDOUT_RESET_VAL;                                       /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1BGND = FLSTST_KCRCDOUT_RESET_VAL ^ FLSTST_KCRCDOUT_RESET_VAL;                                       /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY0BGND = FLST_KCRCPOLY0_RESET_VAL;                                                                    /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1BGND = FLSTST_LONG_WORD_ZERO;                                                                       /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR0BGND = FLSTST_ALL1_VALUE;                                                                            /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1BGND = FLSTST_LONG_WORD_ZERO;                                                                        /* PRQA S 0303 # JV-01 */

    /* Reset the KCRC registers used for foreground test to default values */
    FLSTST_KCRCCTLFGND = FLST_KCRCCTL_RESET_VAL;                                                                        /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDINFGND = FLSTST_LONG_WORD_ZERO;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT0FGND = FLSTST_KCRCDOUT_RESET_VAL ^ FLSTST_KCRCDOUT_RESET_VAL;                                       /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1FGND = FLSTST_KCRCDOUT_RESET_VAL ^ FLSTST_KCRCDOUT_RESET_VAL;                                       /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY0FGND = FLST_KCRCPOLY0_RESET_VAL;                                                                    /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1FGND = FLSTST_LONG_WORD_ZERO;                                                                       /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR0FGND = FLSTST_ALL1_VALUE;                                                                            /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1FGND = FLSTST_LONG_WORD_ZERO;                                                                        /* PRQA S 0303 # JV-01 */
  }
}

/***********************************************************************************************************************
** Function Name         : FlsTst_StartFgnd
**
** Service ID            : 0x02
**
** Description           : This API will execute foreground Flash Test.
**
** Sync/Async            : synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : FgndBlockId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType - Returns E_OK if Foreground
**                         test processed else returns E_NOT_OK if Foreground
**                         test has not been accepted.
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GenExeState(R), FlsTst_GpConfigPtr(R),
**                         FlsTst_GenLastFgndResult(W), FlsTst_GpFgndBlk(R),
**                         FlsTst_GaaLastFgndSignature(W)
**
** Function(s) invoked   : Det_ReportError,
**                         ReadLoadMemData,
**                         FLSTST_ENTER_CRITICAL_SECTION,
**                         FLSTST_EXIT_CRITICAL_SECTION
**
** Registers Used        : KCRCCTL, KCRCDOUT0, KCRCDOUT1, KCRCPOLY0,  
**                         KCRCPOLY1, KCRCXOR0, KCRCXOR1
** Reference ID          : FLSTST_DUD_ACT_003,  FLSTST_DUD_ACT_003_ERR001, FLSTST_DUD_ACT_003_ERR002, 
** Reference ID          : FLSTST_DUD_ACT_003_CRT001, FLSTST_DUD_ACT_003_GBL001, FLSTST_DUD_ACT_003_GBL002
** Reference ID          : FLSTST_DUD_ACT_003_CRT002
***********************************************************************************************************************/
#if (FLSTST_START_FGND_API == STD_ON)
FUNC(Std_ReturnType, FLSTST_PUBLIC_CODE)
    FlsTst_StartFgnd(FlsTst_BlockIdFgndType FgndBlockId)                                                                /* PRQA S 1503 # JV-01 */
{
  /* Local variable to hold the return value of the function */
  Std_ReturnType LenReturnValue;
  /* Local variable to hold the read address */
  volatile uint32 LulReadAddress;
  /* Local variable to hold the block size */
  uint32 LulCurrentTestBlockSize;
  /* Local variable to hold stored crc */
  uint32 LaaStoredCrc[FLSTST_TWO];
  /* Local variable to hold the signature address */
  volatile P2CONST(uint8, AUTOMATIC, FLSTST_APPL_CONST) LpSignatureAddress;
  /* Local variable to hold the calculated CRC */
  uint32  LaaCalculatedCrc[FLSTST_TWO];
  /* Local variable to hold the loop count */
  uint8 LucLoopCount;
  /* Local variable to hold the number of byte to process for signature */
  uint8 LucByteToProcess;
  /* Local Pointer to FlsTstBlockConfigType configuration */
  P2CONST(FlsTstBlock_ConfigType, FLSTST_VAR, FLSTST_CONFIG_CONST) LpFlsTstBlock;
  /* Local union variable to access crc value */
  FlsTst_CrcConvert LddCrcConvert;                                                                                      /* PRQA S 0759 # JV-01 */
  /* Local union variable to access higher bytes of crc64 value */
  FlsTst_CrcConvert LddCrc64Convert;                                                                                    /* PRQA S 0759 # JV-01 */

  /* Set the default value */
  LenReturnValue = E_OK;
  LaaCalculatedCrc[FLSTST_ZERO] = FLSTST_ZERO;                                                                          /* PRQA S 2982 # JV-01 */
  LaaCalculatedCrc[FLSTST_ONE] = FLSTST_ZERO;
  LddCrcConvert.ulCrc32Data = FLSTST_ZERO;
  LddCrc64Convert.ulCrc32Data = FLSTST_ZERO;

  /* Check Det error */
  #if (FLSTST_DEV_ERROR_DETECT == STD_ON)
  if (FLSTST_UNINIT == FlsTst_GenExeState)
  {
    (void)Det_ReportError(FLSTST_MODULE_ID, FLSTST_INSTANCE_ID,
      FLSTST_START_FGND_SID, FLSTST_E_UNINIT);
    LenReturnValue = E_NOT_OK;
  }
  else if (FgndBlockId >= FlsTst_GpConfigPtr->ulFlsTstMaxFgndBlkNo)
  {
    (void)Det_ReportError(FLSTST_MODULE_ID, FLSTST_INSTANCE_ID,
      FLSTST_START_FGND_SID, FLSTST_E_PARAM_INVALID);
    LenReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
    /* Get block parameters */
    LpFlsTstBlock = &FlsTst_GpFgndBlk[FgndBlockId];
    LulReadAddress = LpFlsTstBlock->ulFlsTstBlockBaseAddress;
    LulCurrentTestBlockSize = LpFlsTstBlock->ulFlsTstBlockSize;
    LpSignatureAddress = (P2CONST(uint8, AUTOMATIC, FLSTST_APPL_CONST))LpFlsTstBlock->ulFlsTstSignatureAddress;         /* PRQA S 0306 # JV-01 */
    /* Initialize store CRC */
    LaaStoredCrc[FLSTST_ZERO] = FLSTST_ZERO;                                                                            /* PRQA S 2982 # JV-01 */
    LaaStoredCrc[FLSTST_ONE] = FLSTST_ZERO;

    /* Initialize KCRC registers for fore ground test */
    LucByteToProcess = FlsTst_InitFgndTest(LpFlsTstBlock);

    /* Read data from flash memory and write to KCRCDINFGND */
    FlsTst_ReadLoadMemData((volatile const uint8*)LulReadAddress,                                                       /* PRQA S 0303 # JV-01 */
      &FLSTST_KCRCDINFGND, LulCurrentTestBlockSize);                                                                    /* PRQA S 0303 # JV-01 */

    /* Read stored crc from signature address */
    for (LucLoopCount = FLSTST_ZERO; LucLoopCount < LucByteToProcess;
         LucLoopCount++)
    {
      /* Read stored crc data from memory and store in array */
      if (FLSTST_FOUR > LucLoopCount)
      {
        LddCrcConvert.ucCrcData4[LucLoopCount] = *LpSignatureAddress;
      }
      else
      {
        LddCrc64Convert.ucCrcData4[LucLoopCount - FLSTST_FOUR] = *LpSignatureAddress;
      }

      /* Increase to next memory location */
      LpSignatureAddress++;
    }

    /* Get the calculated CRC value from KCRC unit */
    if ((FLSTST_8BIT_2F == LpFlsTstBlock->enFlsTstTestAlgorithm) ||
        (FLSTST_8BIT_SAE_J1850 == LpFlsTstBlock->enFlsTstTestAlgorithm))
    {
      LaaCalculatedCrc[FLSTST_ZERO] = FLSTST_KCRCDOUT0FGND & FLSTST_8BIT_CRC_MASK;                                      /* PRQA S 0303 # JV-01 */
      LaaStoredCrc[FLSTST_ZERO] = (uint32)LddCrcConvert.ucCrc8Data;
    }
    else if (FLSTST_15BIT_CRC15CAN == LpFlsTstBlock->enFlsTstTestAlgorithm)
    {
      LaaCalculatedCrc[FLSTST_ZERO] = FLSTST_KCRCDOUT0FGND & FLSTST_15BIT_CRC_MASK;                                     /* PRQA S 0303 # JV-01 */
      LaaStoredCrc[FLSTST_ZERO] = (uint32)LddCrcConvert.usCrc16Data;
    }
    else if ((FLSTST_16BIT_CCITT16 == LpFlsTstBlock->enFlsTstTestAlgorithm) ||
            (FLSTST_16BIT_BAICHEVA00 == LpFlsTstBlock->enFlsTstTestAlgorithm) ||
            (FLSTST_16BIT_ARC == LpFlsTstBlock->enFlsTstTestAlgorithm))
    {
      LaaCalculatedCrc[FLSTST_ZERO] = FLSTST_KCRCDOUT0FGND & FLSTST_16BIT_CRC_MASK;                                     /* PRQA S 0303 # JV-01 */
      LaaStoredCrc[FLSTST_ZERO] = LddCrcConvert.usCrc16Data;
    }
    else if ((FLSTST_32BIT_CRC32 == LpFlsTstBlock->enFlsTstTestAlgorithm) ||
             (FLSTST_32BIT_CRC32_REVPOLY == LpFlsTstBlock->enFlsTstTestAlgorithm) ||
             (FLSTST_32BIT_CRC32C == LpFlsTstBlock->enFlsTstTestAlgorithm) ||
             (FLSTST_32BIT_CRC32P4 == LpFlsTstBlock->enFlsTstTestAlgorithm))
    {
      LaaCalculatedCrc[FLSTST_ZERO] = FLSTST_KCRCDOUT0FGND;                                                             /* PRQA S 0303 # JV-01 */
      LaaStoredCrc[FLSTST_ZERO] = LddCrcConvert.ulCrc32Data;
    }
    else /* FLSTST_64BIT_CRC64ECMA */
    {
      LaaCalculatedCrc[FLSTST_ZERO] = FLSTST_KCRCDOUT0FGND;                                                             /* PRQA S 0303 # JV-01 */
      LaaCalculatedCrc[FLSTST_ONE] = FLSTST_KCRCDOUT1FGND;                                                              /* PRQA S 0303 # JV-01 */
      LaaStoredCrc[FLSTST_ZERO] = LddCrcConvert.ulCrc32Data;
      LaaStoredCrc[FLSTST_ONE] = LddCrc64Convert.ulCrc32Data;
    }

    /* Enter critical section */
    FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);

    /* Check the calculated crc and stored crc*/
    if ((LaaCalculatedCrc[FLSTST_ZERO] == LaaStoredCrc[FLSTST_ZERO]) &&
        (LaaCalculatedCrc[FLSTST_ONE] == LaaStoredCrc[FLSTST_ONE]))
    {
      FlsTst_GenLastFgndResult = FLSTST_OK;
    }
    else
    {
      FlsTst_GenLastFgndResult = FLSTST_NOT_OK;
    }

    /* Set the value of last signature for Fgnd test */
    FlsTst_GaaLastFgndSignature[FLSTST_ZERO] = LaaCalculatedCrc[FLSTST_ZERO];
    FlsTst_GaaLastFgndSignature[FLSTST_ONE] = LaaCalculatedCrc[FLSTST_ONE];

    /* Exit critical section */
    FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
  }

  return LenReturnValue;
}
#endif /* if (FLSTST_START_FGND_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : FlsTst_Abort
**
** Service ID            : 0x03
**
** Description           : This API will abort flash test operation in
**                         background mode and set the state to FLSTST_ABORTED
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GenExeState(R/W)
**
** Function(s) invoked   : Det_ReportError,
**                         FLSTST_ENTER_CRITICAL_SECTION,
**                         FLSTST_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
** Reference ID          : FLSTST_DUD_ACT_004, FLSTST_DUD_ACT_004_ERR001, FLSTST_DUD_ACT_004_CRT002, 
** Reference ID          : FLSTST_DUD_ACT_004_CRT001, FLSTST_DUD_ACT_004_GBL001
***********************************************************************************************************************/
FUNC(void, FLSTST_PUBLIC_CODE) FlsTst_Abort(void)                                                                       /* PRQA S 1503 # JV-01 */
{
  #if (FLSTST_DEV_ERROR_DETECT == STD_ON)
  if (FLSTST_UNINIT == FlsTst_GenExeState)
  {
    (void)Det_ReportError(FLSTST_MODULE_ID,
      FLSTST_INSTANCE_ID, FLSTST_ABORT_SID, FLSTST_E_UNINIT);
  }
  else
  #endif /* (FLSTST_DEV_ERROR_DETECT == STD_ON) */
  {
    FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
    /* Change state to ABORTED */
    FlsTst_GenExeState = FLSTST_ABORTED;
    FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
  }
}

/***********************************************************************************************************************
** Function Name         : FlsTst_Suspend
**
** Service ID            : 0x04
**
** Description           : This API suspend the ongoing bgnd flash test if
**                         the flash test state is RUNNING or INIT
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GenExeState(R/W).
**
** Function(s) invoked   : Det_ReportError,
**                         FLSTST_ENTER_CRITICAL_SECTION,
**                         FLSTST_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
** Reference ID          : FLSTST_DUD_ACT_005, FLSTST_DUD_ACT_005_ERR001, FLSTST_DUD_ACT_005_CRT001,
** Reference ID          : FLSTST_DUD_ACT_005_GBL001, FLSTST_DUD_ACT_005_CRT002
***********************************************************************************************************************/
#if (FLSTST_SUSPEND_RESUME_API == STD_ON)
FUNC(void, FLSTST_PUBLIC_CODE) FlsTst_Suspend(void)                                                                     /* PRQA S 1503 # JV-01 */
{
  #if (FLSTST_DEV_ERROR_DETECT == STD_ON)
  if (FLSTST_UNINIT == FlsTst_GenExeState)
  {
    (void)Det_ReportError(FLSTST_MODULE_ID,
      FLSTST_INSTANCE_ID, FLSTST_SUSPEND_SID, FLSTST_E_UNINIT);
  }
  else
  #endif /* (FLSTST_DEV_ERROR_DETECT == STD_ON) */
  {
    FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
    /* If current state is RUNNING or INIT, change state to SUSPENDED */
    if ((FLSTST_RUNNING == FlsTst_GenExeState) ||
        (FLSTST_INIT == FlsTst_GenExeState))
    {
      /* Change state to SUSPENDED */
      FlsTst_GenExeState = FLSTST_SUSPENDED;
    }
    FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
  }
}

/***********************************************************************************************************************
** Function Name         : FlsTst_Resume
**
** Service ID            : 0x05
**
** Description           : This API start the suspended bgnd check again.
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
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GenExeState(R/W).
**
** Function(s) invoked   : Det_ReportError,
**                         FLSTST_ENTER_CRITICAL_SECTION,
**                         FLSTST_EXIT_CRITICAL_SECTION
**
** Registers Used        : KCRCCTL
** Reference ID          : FLSTST_DUD_ACT_006, FLSTST_DUD_ACT_006_ERR001, FLSTST_DUD_ACT_006_ERR002,
** Reference ID          : FLSTST_DUD_ACT_006_GBL001, FLSTST_DUD_ACT_006_CRT002, FLSTST_DUD_ACT_006_CRT001
***********************************************************************************************************************/
FUNC(void, FLSTST_PUBLIC_CODE) FlsTst_Resume(void)                                                                      /* PRQA S 1503 # JV-01 */
{
  #if (FLSTST_DEV_ERROR_DETECT == STD_ON)
  if (FLSTST_UNINIT == FlsTst_GenExeState)
  {
    (void)Det_ReportError(FLSTST_MODULE_ID,
      FLSTST_INSTANCE_ID, FLSTST_RESUME_SID, FLSTST_E_UNINIT);
  }
  else if (FLSTST_SUSPENDED != FlsTst_GenExeState)
  {
    /* Report Det if current state is not SUSPENDED */
    (void)Det_ReportError(FLSTST_MODULE_ID,
      FLSTST_INSTANCE_ID, FLSTST_RESUME_SID, FLSTST_E_STATE_FAILURE);
  }
  else
  #endif /* (FLSTST_DEV_ERROR_DETECT == STD_ON) */
  {
    FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
    /* Change state to SUSPENDED */
    FlsTst_GenExeState = FLSTST_RUNNING;
    FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
  }
}
#endif /* if (FLSTST_SUSPEND_RESUME_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : FlsTst_GetCurrentState
**
** Service ID            : 0x06
**
** Description           : This API Returns the FLSTST module state.
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
** Return parameter      : FlsTst_StateType
**
** Preconditions         : None
**
** Global Variables Used : FlsTst_GenExeState(R).
**
** Function(s) invoked   : FLSTST_ENTER_CRITICAL_SECTION,
**                         FLSTST_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
** Reference ID          : FLSTST_DUD_ACT_007, FLSTST_DUD_ACT_007_CRT001, FLSTST_DUD_ACT_007_CRT002
***********************************************************************************************************************/
#if (FLSTST_GET_CURRENT_STATE_API == STD_ON)
FUNC(FlsTst_StateType, FLSTST_PUBLIC_CODE) FlsTst_GetCurrentState(void)                                                 /* PRQA S 1503 # JV-01 */
{
  FlsTst_StateType LenStatus; /* Local variable to store module state */

  FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
  /* Read current state of the driver */
  LenStatus = FlsTst_GenExeState;
  FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);

  return LenStatus;
}
#endif

/***********************************************************************************************************************
** Function Name         : FlsTst_GetTestResultBgnd
**
** Service ID            : 0x07
**
** Description           : This API Returns the FLSTST module bgnd check result
**                         and Test Interval Id of the last background test
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : FlsTst_TestResultBgndType
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GenExeState(R),
**                         FlsTst_GulTestIntervalId(R),
**                         FlsTst_GenOverallBgndResult(R).
**
** Function(s) invoked   : Det_ReportError,
**                         FLSTST_ENTER_CRITICAL_SECTION,
**                         FLSTST_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
** Reference ID          : FLSTST_DUD_ACT_008, FLSTST_DUD_ACT_008_ERR001, FLSTST_DUD_ACT_008_CRT001
** Reference ID          : FLSTST_DUD_ACT_008_CRT002
***********************************************************************************************************************/
#if (FLSTST_GET_TEST_RESULT_BGND_API == STD_ON)
FUNC(FlsTst_TestResultBgndType, FLSTST_PUBLIC_CODE)
    FlsTst_GetTestResultBgnd(void)                                                                                      /* PRQA S 1503 # JV-01 */
{
  /* Local variable to store the last Bgnd test result status */
  FlsTst_TestResultBgndType LddTestResultBgnd;
  
  /* Initialize the return value */
  LddTestResultBgnd.ulTestIntervalId = FLSTST_ZERO;                                                                     /* PRQA S 2982 # JV-01 */
  LddTestResultBgnd.enTestResultBgnd = FLSTST_RESULT_NOT_TESTED;                                                        /* PRQA S 2982 # JV-01 */

  /* Check if the module is initialized */
  #if (FLSTST_DEV_ERROR_DETECT == STD_ON)
  if (FLSTST_UNINIT == FlsTst_GenExeState)
  {
     /* Report error to DET that module is not initialized */
     (void)Det_ReportError(FLSTST_MODULE_ID, FLSTST_INSTANCE_ID,
       FLSTST_GET_TEST_RESULT_BGND_SID, FLSTST_E_UNINIT);
  }
  else
  #endif
  {
    FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
    /* Get current interval Id */
    LddTestResultBgnd.ulTestIntervalId = FlsTst_GulTestIntervalId;
    /* Get overall background test result */
    #if (FLSTST_TEST_RESULT_SIGNATURE != STD_ON)
    LddTestResultBgnd.enTestResultBgnd = FlsTst_GenOverallBgndResult;
    #endif
    FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
  }

  return LddTestResultBgnd;
}
#endif /* (FLSTST_GET_TEST_RESULT_BGND_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : FlsTst_GetTestResultFgnd
**
** Service ID            : 0x0f
**
** Description           : This API Returns  last fgnd check result.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : FlsTst_TestResultFgndType
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GenExeState(R), FlsTst_GenLastFgndResult(R).
**
** Function(s) invoked   : Det_ReportError
**
** Registers Used        : None
** Reference ID          : FLSTST_DUD_ACT_009, FLSTST_DUD_ACT_009_ERR001
***********************************************************************************************************************/
#if (FLSTST_GET_TEST_RESULT_FGND_API == STD_ON)
FUNC(FlsTst_TestResultFgndType, FLSTST_PUBLIC_CODE)
    FlsTst_GetTestResultFgnd(void)                                                                                      /* PRQA S 1503 # JV-01 */
{
  /* Local variable to store the last Fgnd test result status */
  FlsTst_TestResultFgndType LenReturnValue;
  
  /* Initialize the return value */
  LenReturnValue = FLSTST_NOT_TESTED;                                                                                   /* PRQA S 2982 # JV-01 */

  /* Check if the module is initialized */
  #if (FLSTST_DEV_ERROR_DETECT == STD_ON)
  if (FLSTST_UNINIT == FlsTst_GenExeState)
  {
     /* Report error to DET that module is not initialized */
     (void)Det_ReportError(FLSTST_MODULE_ID, FLSTST_INSTANCE_ID,
       FLSTST_GET_TEST_RESULT_FGND_SID, FLSTST_E_UNINIT);
  }
  else
  #endif
  {
    /* Get the last Fgnd test result of the driver */
    LenReturnValue = FlsTst_GenLastFgndResult;
  }

  return LenReturnValue;
}
#endif /* if (FLSTST_GET_TEST_RESULT_FGND_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : FlsTst_GetVersionInfo
**
** Service ID            :0x08 
**
** Description           : This API returns the version information of this module.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : versioninfo
**
** Return parameter      : none
**
** Preconditions         : versioninfo pointer should not be a NULL_PTR. 
**
** Global Variables Used : None
**
** Function(s) invoked   : Det_ReportError
**
** Registers Used        : None
** Reference ID          : FLSTST_DUD_ACT_015, FLSTST_DUD_ACT_015_ERR001
***********************************************************************************************************************/
#if (FLSTST_VERSION_INFO_API == STD_ON)
FUNC(void, FLSTST_PUBLIC_CODE) FlsTst_GetVersionInfo                                                                    /* PRQA S 1503 # JV-01 */
    (P2VAR(Std_VersionInfoType, AUTOMATIC, FLSTST_APPL_CONST) versioninfo)                                              /* PRQA S 3432 # JV-01 */
{
  #if (FLSTST_DEV_ERROR_DETECT == STD_ON)
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == versioninfo)
  {
    /* Report to DET  */
    (void)Det_ReportError(FLSTST_MODULE_ID, FLSTST_INSTANCE_ID, FLSTST_GET_VERSION_INFO_SID, FLSTST_E_PARAM_POINTER);
  }
  else
  #endif /* (FLSTST_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Copy the vendor Id */
    versioninfo->vendorID = FLSTST_VENDOR_ID;
    /* Copy the module Id */
    versioninfo->moduleID = FLSTST_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = FLSTST_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = FLSTST_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = FLSTST_SW_PATCH_VERSION;
  }
}
#endif

/***********************************************************************************************************************
** Function Name         : FlsTst_GetTestSignatureBgnd
**
** Service ID            : 0x09
**
** Description           : This API Returns signature of last bgnd check and
**                         Test Interval Id of the last background test.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : FlsTst_TestSignatureBgndType
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GenExeState(R), FlsTst_GulTestIntervalId(R),
**                         FlsTst_GaaLastBgndSignature(R).
**
** Function(s) invoked   : Det_ReportError,
**                         FLSTST_ENTER_CRITICAL_SECTION,
**                         FLSTST_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
** Reference ID          : FLSTST_DUD_ACT_010, FLSTST_DUD_ACT_010_ERR001, FLSTST_DUD_ACT_010_CRT001
** Reference ID          : FLSTST_DUD_ACT_010_CRT002
***********************************************************************************************************************/
#if (FLSTST_GET_TEST_SIGNATURE_BGND_API == STD_ON)
FUNC(FlsTst_TestSignatureBgndType, FLSTST_PUBLIC_CODE)
    FlsTst_GetTestSignatureBgnd(void)                                                                                   /* PRQA S 1503 # JV-01 */
{
  /* Local variable to store the driver Bgnd test result status */
  FlsTst_TestSignatureBgndType LulTestResult;

  /* Initialize signature value */
  LulTestResult.ulSignatureValue = FLSTST_ZERO;
  LulTestResult.ulSignatureValue_H = FLSTST_ZERO;
  LulTestResult.ulTestIntervalId = FLSTST_ZERO;                                                                         /* PRQA S 2982 # JV-01 */

  /* Check if the module is initialized */
  #if (FLSTST_DEV_ERROR_DETECT == STD_ON)
  if (FLSTST_UNINIT == FlsTst_GenExeState)
  {
    /* Report error to DET that module is not initialized */
    (void)Det_ReportError(FLSTST_MODULE_ID, FLSTST_INSTANCE_ID,
      FLSTST_GET_TEST_SIGNATURE_BGND_SID, FLSTST_E_UNINIT);
  }
  else
  #endif
  {
    /* Enter critical section */
    FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
    /* Load the interval Id */
    LulTestResult.ulTestIntervalId = FlsTst_GulTestIntervalId;
    #if (FLSTST_TEST_RESULT_SIGNATURE == STD_ON)
    /* Load the signature of the last fgnd check */
    LulTestResult.ulSignatureValue =  FlsTst_GaaLastBgndSignature[FLSTST_ZERO];
    LulTestResult.ulSignatureValue_H = FlsTst_GaaLastBgndSignature[FLSTST_ONE];
    #endif
    /* Exit critical section */
    FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
  }

  return(LulTestResult);
}
#endif /* if (FLSTST_GET_TEST_SIGNATURE_BGND_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : FlsTst_GetTestSignatureFgnd
**
** Service ID            : 0x0a
**
** Description           : This API Returns signature of last fgnd check.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : FlsTst_TestSignatureFgndType
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GenExeState(R), FlsTst_GaaLastFgndSignature(R).
**
** Function(s) invoked   : Det_ReportError,
**                         FLSTST_ENTER_CRITICAL_SECTION,
**                         FLSTST_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
** Reference ID          : FLSTST_DUD_ACT_011, FLSTST_DUD_ACT_011_ERR001, FLSTST_DUD_ACT_011_CRT001
** Reference ID          : FLSTST_DUD_ACT_011_CRT002
***********************************************************************************************************************/
#if (FLSTST_GET_TEST_SIGNATURE_FGND_API == STD_ON)
FUNC(FlsTst_TestSignatureFgndType, FLSTST_PUBLIC_CODE)
    FlsTst_GetTestSignatureFgnd(void)                                                                                   /* PRQA S 1503 # JV-01 */
{
  /* Local variable to store the driver fgnd test result status */
  FlsTst_TestSignatureFgndType LulTestResult;

  /* Initialize signature value */
  LulTestResult.ulSignatureValue = FLSTST_ZERO;                                                                         /* PRQA S 2982 # JV-01 */
  LulTestResult.ulSignatureValue_H = FLSTST_ZERO;                                                                       /* PRQA S 2982 # JV-01 */

  /* Check if the module is initialized */
  #if (FLSTST_DEV_ERROR_DETECT == STD_ON)
  if (FLSTST_UNINIT == FlsTst_GenExeState)
  {
    /* Report error to DET that module is not initialized */
    (void)Det_ReportError(FLSTST_MODULE_ID, FLSTST_INSTANCE_ID,
      FLSTST_GET_TEST_SIGNATURE_FGND_SID, FLSTST_E_UNINIT);
  }
  else
  #endif
  {
    /* Enter critical section */
    FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
    /* Load the signature of the last fgnd check */
    LulTestResult.ulSignatureValue =  FlsTst_GaaLastFgndSignature[FLSTST_ZERO];
    LulTestResult.ulSignatureValue_H = FlsTst_GaaLastFgndSignature[FLSTST_ONE];
    /* Exit critical section */
    FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
  }

  return(LulTestResult);
}
#endif /* if (FLSTST_GET_TEST_SIGNATURE_FGND_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : FlsTst_GetErrorDetails
**
** Service ID            : 0x0b
**
** Description           : This API Returns the FLSTST module ECC circuitry
**                         test result which include ECC error status
**                         and fault address.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : FlsTst_ErrorDetailsType
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GenExeState(R), FlsTst_GddEccErrorDetail(R).
**
** Function(s) invoked   : Det_ReportError
**
** Registers Used        : None
** Reference ID          : FLSTST_DUD_ACT_012, FLSTST_DUD_ACT_012_ERR001
***********************************************************************************************************************/
#if (FLSTST_GET_ERROR_DETAILS_API == STD_ON)
FUNC(FlsTst_ErrorDetailsType, FLSTST_PUBLIC_CODE)
    FlsTst_GetErrorDetails(void)                                                                                        /* PRQA S 1503 # JV-01 */
{
  FlsTst_ErrorDetailsType LddEccTestResult;

  /* Initialize return value */
  LddEccTestResult.ucCFGlobalEccStatus = FLSTST_ZERO;                                                                   /* PRQA S 2982 # JV-01 */
  LddEccTestResult.ucCFBankEccStatus = FLSTST_ZERO;                                                                     /* PRQA S 2982 # JV-01 */
  LddEccTestResult.ulCFGlobalEccFaultAddress = FLSTST_ZERO;                                                             /* PRQA S 2982 # JV-01 */
  LddEccTestResult.ulCFBankEccFaultAddress = FLSTST_ZERO;                                                               /* PRQA S 2982 # JV-01 */

  #if (FLSTST_DEV_ERROR_DETECT == STD_ON)
  if (FLSTST_UNINIT == FlsTst_GenExeState)
  {
    /* Report error to DET that module is not initialized */
    (void)Det_ReportError(FLSTST_MODULE_ID, FLSTST_INSTANCE_ID,
      FLSTST_GET_ERROR_DETAILS_SID, FLSTST_E_UNINIT);
  }
  else
  #endif
  {
    LddEccTestResult = FlsTst_GddEccErrorDetail;
  }

  return LddEccTestResult;
}
#endif /* if (FLSTST_GET_ERROR_DETAILS_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : FlsTst_TestEcc
**
** Service ID            : 0x0c
**
** Description           : This API Service executes a test of ECC hardware.
**                         This is only applicable in case the hardware
**                         provides such functionality.
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
** Return parameter      : Std_ReturnType
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GenExeState(R)
**
** Function(s) invoked   : Det_ReportError,
**                         FlsTst_TestEccCFGlobal,
**                         FlsTst_TestEccCFBank
**
** Registers Used        : None
** Reference ID          : FLSTST_DUD_ACT_013, FLSTST_DUD_ACT_013_ERR001
***********************************************************************************************************************/
#if (FLSTST_TEST_ECC_API == STD_ON)
FUNC(Std_ReturnType, FLSTST_PUBLIC_CODE) FlsTst_TestEcc(void)                                                           /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LenReturnValue;

  #if (FLSTST_DEV_ERROR_DETECT == STD_ON)
  if (FLSTST_UNINIT == FlsTst_GenExeState)
  {
    /* Report error to DET that module is not initialized */
    (void)Det_ReportError(FLSTST_MODULE_ID, FLSTST_INSTANCE_ID,
      FLSTST_TEST_ECC_SID, FLSTST_E_UNINIT);
    /* Set return value to not ok */
    LenReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
    #if (FLSTST_TEST_ECC_CF_GLOBAL == STD_ON) && (FLSTST_TEST_ECC_CF_BANK == STD_ON)
    /* Excute test ECC for code flash global area */
    LenReturnValue = FlsTst_TestEccCFGlobal();
    /* Excute test ECC for code flash bank area */
    LenReturnValue |= FlsTst_TestEccCFBank();
    #elif (FLSTST_TEST_ECC_CF_GLOBAL == STD_ON)
    /* Excute test ECC for code flash global area */
    LenReturnValue = FlsTst_TestEccCFGlobal();
    #elif (FLSTST_TEST_ECC_CF_BANK == STD_ON)
    /* Excute test ECC for code flash bank area */
    LenReturnValue = FlsTst_TestEccCFBank();
    #endif
  }

  return LenReturnValue;
}
#endif /* if (FLSTST_TEST_ECC_API == STD_ON) */

/***********************************************************************************************************************
** Function Name         : FlsTst_MainFunction
**
** Service ID            : 0x0d
**
** Description           : This API performs testing of the defined flash
**                         blocks in background mode and shall set the Flash
**                         Test execution state from INIT to RUNNING when
**                         calling the function the first time after
**                         initialization or after a complete test interval
**
** Sync/Async            : NA
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GpConfigPtr(R), FlsTst_GpBgndBlk(R),
**                                      FlsTst_GenOverallBgndResult(W),
**                                      FlsTst_GaaLastBgndSignature(W),
**                                      FlsTst_GulTestIntervalId(R/W),
**                                      FlsTst_GenExeState(R/W),
**                                      FlsTst_GVar.FlsTst_GenBgndCheckState(R/W),
**                                      FlsTst_Gvar.FlsTst_GulBgndConfigIndex(R/W),
**                                      FlsTst_Gvar.FlsTst_GulCalculatedCrc(R),
**                                      FlsTst_Gvar.FlsTst_GulCalculatedCrc_H(R),
**                                      FlsTst_Gvar.FlsTst_GulReadAddress(R/W),
**                                      FlsTst_GblTestComplete(R/W).
**
**
** Function(s) invoked   : Det_ReportError, Dem_ReportErrorStatus,
**                         FLSTST_ENTER_CRITICAL_SECTION,
**                         FLSTST_EXIT_CRITICAL_SECTION, FlsTst_TestCompleted,
**                         FlsTst_InitBgndTest, FlsTst_GetStoredCRC,
**                         FlsTst_ReadLoadMemDataBgnd
**
** Registers Used        : KCRCCTL, KCRCDOUT0, KCRCDOUT1, KCRCIN,
**                         KCRCPOLY0, KCRCPOLY1, KCRCXOR0, KCRCXOR1.
** Reference ID          : FLSTST_DUD_ACT_014,
** Reference ID          : FLSTST_DUD_ACT_014_ERR001, FLSTST_DUD_ACT_014_ERR002,
** Reference ID          : FLSTST_DUD_ACT_014_GBL001, FLSTST_DUD_ACT_014_GBL002, FLSTST_DUD_ACT_014_GBL003,
** Reference ID          : FLSTST_DUD_ACT_014_GBL004, FLSTST_DUD_ACT_014_GBL005, FLSTST_DUD_ACT_014_GBL006,
** Reference ID          : FLSTST_DUD_ACT_014_GBL007, FLSTST_DUD_ACT_014_GBL008, FLSTST_DUD_ACT_014_GBL009,
** Reference ID          : FLSTST_DUD_ACT_014_GBL010, FLSTST_DUD_ACT_014_GBL011, FLSTST_DUD_ACT_014_GBL012,
** Reference ID          : FLSTST_DUD_ACT_014_GBL013, FLSTST_DUD_ACT_014_GBL014, FLSTST_DUD_ACT_014_GBL015,
** Reference ID          : FLSTST_DUD_ACT_014_CRT001, FLSTST_DUD_ACT_014_CRT002, FLSTST_DUD_ACT_014_CRT003,
** Reference ID          : FLSTST_DUD_ACT_014_CRT004, FLSTST_DUD_ACT_014_CRT005, FLSTST_DUD_ACT_014_CRT006,
** Reference ID          : FLSTST_DUD_ACT_014_CRT007, FLSTST_DUD_ACT_014_CRT008, FLSTST_DUD_ACT_014_CRT009,
** Reference ID          : FLSTST_DUD_ACT_014_CRT010, FLSTST_DUD_ACT_014_CRT011, FLSTST_DUD_ACT_014_CRT012,
** Reference ID          : FLSTST_DUD_ACT_014_CRT013, FLSTST_DUD_ACT_014_CRT014, FLSTST_DUD_ACT_014_CRT015
***********************************************************************************************************************/
FUNC(void, FLSTST_PUBLIC_CODE) FlsTst_MainFunction(void)                                                                /* PRQA S 1503 # JV-01 */
{
  #if (FLSTST_BGND_TEST_ENABLE == STD_ON)
  /* Local pointer variable to hold the individual test block params */
  P2CONST(FlsTstBlock_ConfigType, AUTOMATIC, FLSTST_CONFIG_CONST) LpFlsTstBlock;
  /* Variable to hold stored bgnd crc */
  uint32 LaaStoredBgndCrc[FLSTST_TWO];
  #endif

  /* Check if module has been initialized */
  if (FLSTST_UNINIT != FlsTst_GenExeState)
  {
    #if (FLSTST_BGND_TEST_ENABLE == STD_ON)
    /* Enter critical section */
    FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
    /* Set module state to RUNNING */
    if (FLSTST_INIT == FlsTst_GenExeState)
    {
      FlsTst_GenExeState = FLSTST_RUNNING;
    } /*else: No action required */

    if (FLSTST_RUNNING == FlsTst_GenExeState)
    {
      /* Load the test block parameters based on the index */
      LpFlsTstBlock =
        &FlsTst_GpBgndBlk[FlsTst_GVar.FlsTst_GulBgndConfigIndex];

      /* Increase test interval at the start of new test if back ground test
         is completed for all blocks */
      if (FLSTST_TRUE == FlsTst_GblTestComplete)
      {
        /* Reset test interval if it exceeds the end value */
        if (FlsTst_GulTestIntervalId >= FLSTST_TEST_INTERVAL_ID_END_VALUE)
        {
          FlsTst_GulTestIntervalId = FLSTST_ZERO;
        }
        else
        {
          FlsTst_GulTestIntervalId++;
        }
        /* Reset completed flag new interval */
        FlsTst_GblTestComplete = FLSTST_FALSE;
      }/* else: No action required */

      /* Exit critical section */
      FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);

      if (FLSTST_BGND_CHECK_INIT == FlsTst_GVar.FlsTst_GenBgndCheckState)
      {
        FlsTst_InitBgndTest(LpFlsTstBlock);
        /* Set global flag to INPROGRESS */
        FlsTst_GVar.FlsTst_GenBgndCheckState = FLSTST_BGND_CHECK_INPROGRESS;
      }

      if (FLSTST_BGND_CHECK_INPROGRESS == FlsTst_GVar.FlsTst_GenBgndCheckState)
      {
        /* Read data from flash memory and write to data register */
        FlsTst_ReadLoadMemDataBgnd(LpFlsTstBlock);

        /* Enter critical section */
        FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
        /* Save the CRC value */
        FlsTst_GVar.FlsTst_GulCalculatedCrc = FLSTST_KCRCDOUT0BGND;                                                     /* PRQA S 0303 # JV-01 */
        FlsTst_GVar.FlsTst_GulCalculatedCrc_H = FLSTST_KCRCDOUT1BGND;                                                   /* PRQA S 0303 # JV-01 */
        /* Exit critical section */
        FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);

        /* Check if the data is read from flash memory is completed */
        if (FlsTst_GVar.FlsTst_GulReadAddress >=
            (LpFlsTstBlock->ulFlsTstBlockBaseAddress +                                                                  /* PRQA S 3383 # JV-01 */
                                      LpFlsTstBlock->ulFlsTstBlockSize))
        {
          /* Get stored signature value */
          LaaStoredBgndCrc[FLSTST_ZERO] = FLSTST_ZERO;
          LaaStoredBgndCrc[FLSTST_ONE] = FLSTST_ZERO;
          FlsTst_GetStoredCRC(LpFlsTstBlock, LaaStoredBgndCrc);

          /* Check whether the calculated crc and stored crc is same */
          if ((LaaStoredBgndCrc[FLSTST_ZERO] == FlsTst_GVar.FlsTst_GulCalculatedCrc) &&
              (LaaStoredBgndCrc[FLSTST_ONE] == FlsTst_GVar.FlsTst_GulCalculatedCrc_H))
          {
            #if (FLSTST_TEST_RESULT_SIGNATURE == STD_ON)
            /* Enter critical section */
            FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
            FlsTst_GaaLastBgndSignature[FLSTST_ZERO] = FlsTst_GVar.FlsTst_GulCalculatedCrc;
            FlsTst_GaaLastBgndSignature[FLSTST_ONE] = FlsTst_GVar.FlsTst_GulCalculatedCrc_H;
            /* Exit critical section */
            FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
            #endif
          }
          else
          {
            #if (FLSTST_TEST_RESULT_SIGNATURE == STD_ON)
            /* Enter critical section */
            FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
            FlsTst_GaaLastBgndSignature[FLSTST_ZERO] = FlsTst_GVar.FlsTst_GulCalculatedCrc;
            FlsTst_GaaLastBgndSignature[FLSTST_ONE] = FlsTst_GVar.FlsTst_GulCalculatedCrc_H;
            /* Exit critical section */
            FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
            #endif
            #if (FLSTST_TEST_RESULT_SIGNATURE != STD_ON)
            /* Enter critical section */
            FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
            /* Set overall status to not ok */
            FlsTst_GenOverallBgndResult = FLSTST_RESULT_NOT_OK;
            /* Exit critical section */
            FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
            /* Set flag to indicate overall status change to not ok in current test */
            FlsTst_GVar.FlsTst_GblCurrentTestFail = FLSTST_TRUE;
            /* Report to Dem with detection criteria fail */
            #if defined(FLSTST_E_FLSTST_FAILURE)
            (void)Dem_SetEventStatus(FLSTST_E_FLSTST_FAILURE, DEM_EVENT_STATUS_FAILED);
            #endif
            #endif
          }

          /* Increment the test block index */
          FlsTst_GVar.FlsTst_GulBgndConfigIndex++;                                                                      /* PRQA S 3383 # JV-01 */

          /* Check if all blocks have been tested */
          if (FlsTst_GVar.FlsTst_GulBgndConfigIndex >=
                                  FlsTst_GpConfigPtr->ulFlsTstMaxBgndBlkNo)
          {
            /* If no block with test result is not ok, set overall result to OK */
            #if (FLSTST_TEST_RESULT_SIGNATURE != STD_ON)
            if (FLSTST_FALSE == FlsTst_GVar.FlsTst_GblCurrentTestFail)
            {
              /* Enter critical section */
              FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
              FlsTst_GenOverallBgndResult = FLSTST_RESULT_OK;
              /* Exit critical section */
              FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
              /* Report to Dem with detection criteria pass */
              #if defined(FLSTST_E_FLSTST_FAILURE)
              (void)Dem_SetEventStatus(FLSTST_E_FLSTST_FAILURE, DEM_EVENT_STATUS_PASSED);
              #endif
            }
            else
            {
              /* Reset test fail flag */
              FlsTst_GVar.FlsTst_GblCurrentTestFail = FLSTST_FALSE;
            }
            #endif

            /* Reset global variable for next background test */
            FlsTst_GVar.FlsTst_GulBgndConfigIndex = FLSTST_ZERO;
            /* Enter critical section */
            FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
            FlsTst_GenExeState = FLSTST_INIT;
            /* Exit critical section */
            FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
            /* Set the flag that indicates all blocks have been tested to TRUE */
            FlsTst_GblTestComplete = FLSTST_TRUE;

            /* Call test complete notification */
            #if (FLSTST_TEST_COMPLETED_NOTIFICATION_SUPPORTED == STD_ON)
            if (NULL_PTR != FlsTst_GpConfigPtr->pTestCompleteNotifyFunc)
            {
              FlsTst_GpConfigPtr->pTestCompleteNotifyFunc();
            }
            #endif
          }/* else: No action required */

          /* Load the test block parameters based on the index */
          LpFlsTstBlock =
            &FlsTst_GpBgndBlk[FlsTst_GVar.FlsTst_GulBgndConfigIndex];
          FlsTst_GVar.FlsTst_GulReadAddress =
            LpFlsTstBlock->ulFlsTstBlockBaseAddress;
          FlsTst_GVar.FlsTst_GenBgndCheckState = FLSTST_BGND_CHECK_INIT;
        }
      }/* else: No action required */
    }
    else
    {
      /* Exit critical section */
      FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
    }
    #endif
  }/* else: No action required */
}

#define FLSTST_STOP_SEC_PUBLIC_CODE
#include "FlsTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

#define FLSTST_START_SEC_PRIVATE_CODE
#include "FlsTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

/*******************************************************************************
** Function Name         : FlsTst_ReadLoadMemData
**
** Service ID            : NA
**
** Description           : Internal function to read the CRC value from the
**                         flash memory.
**
** Sync/Async            : NA
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LpReadAddress, LulSize
**
** InOut Parameters      : None
**
** Output Parameters     : LpCrcAddr
**
** Return parameter      : None
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
** Reference ID          : FLSTST_DUD_ACT_016
*******************************************************************************/
#if (FLSTST_START_FGND_API == STD_ON)
static void FlsTst_ReadLoadMemData(
  volatile P2CONST(uint8, AUTOMATIC, FLSTST_APPL_CONST) LpReadAddress,
  volatile P2VAR(uint32, AUTOMATIC, FLSTST_APPL_DATA) LpCrcAddr,                                                        /* PRQA S 3432 # JV-01 */
  const uint32 LulSize)
{
  uint8 LucMemData;
  uint32 LulRemainingSize;
  volatile P2CONST(uint8, AUTOMATIC, FLSTST_APPL_CONST) LpReadAddr;

  LpReadAddr = LpReadAddress;
  LulRemainingSize = LulSize;
  while (LulRemainingSize > FLSTST_ZERO)
  {
    LucMemData = *LpReadAddr;
    /* Read data from memory and loading to configured KCRC unit */
    *LpCrcAddr = (uint32)LucMemData;
    /* Move to next data */
    LpReadAddr++;
    LulRemainingSize--;
  }
}

/*******************************************************************************
** Function Name         : FlsTst_InitFgndTest
**
** Service ID            : NA
**
** Description           : Internal function to initialize fore ground test
**                         related registers.
**
** Sync/Async            : NA
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LpFlsTstBlock
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Number of CRC byte
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : KCRCCTL, KCRCDOUT0, KCRCDOUT1, KCRCPOLY0,
**                                  KCRCPOLY1, KCRCXOR0, KCRCXOR1.
** Reference ID          : FLSTST_DUD_ACT_019,
** Reference ID          : FLSTST_DUD_ACT_019_REG001, FLSTST_DUD_ACT_019_REG002, FLSTST_DUD_ACT_019_REG003, 
** Reference ID          : FLSTST_DUD_ACT_019_REG004, FLSTST_DUD_ACT_019_REG005, FLSTST_DUD_ACT_019_REG006,
** Reference ID          : FLSTST_DUD_ACT_019_REG007, FLSTST_DUD_ACT_019_REG008, FLSTST_DUD_ACT_019_REG009,
** Reference ID          : FLSTST_DUD_ACT_019_REG010, FLSTST_DUD_ACT_019_REG011, FLSTST_DUD_ACT_019_REG012,
** Reference ID          : FLSTST_DUD_ACT_019_REG013, FLSTST_DUD_ACT_019_REG014, FLSTST_DUD_ACT_019_REG015,
** Reference ID          : FLSTST_DUD_ACT_019_REG016, FLSTST_DUD_ACT_019_REG017, FLSTST_DUD_ACT_019_REG018,
** Reference ID          : FLSTST_DUD_ACT_019_REG019, FLSTST_DUD_ACT_019_REG020, FLSTST_DUD_ACT_019_REG021,
** Reference ID          : FLSTST_DUD_ACT_019_REG022, FLSTST_DUD_ACT_019_REG023, FLSTST_DUD_ACT_019_REG024,
** Reference ID          : FLSTST_DUD_ACT_019_REG025, FLSTST_DUD_ACT_019_REG026, FLSTST_DUD_ACT_019_REG027,
** Reference ID          : FLSTST_DUD_ACT_019_REG028, FLSTST_DUD_ACT_019_REG029, FLSTST_DUD_ACT_019_REG030,
** Reference ID          : FLSTST_DUD_ACT_019_REG031, FLSTST_DUD_ACT_019_REG032, FLSTST_DUD_ACT_019_REG033,
** Reference ID          : FLSTST_DUD_ACT_019_REG034, FLSTST_DUD_ACT_019_REG035, FLSTST_DUD_ACT_019_REG036,
** Reference ID          : FLSTST_DUD_ACT_019_REG037, FLSTST_DUD_ACT_019_REG038, FLSTST_DUD_ACT_019_REG039,
** Reference ID          : FLSTST_DUD_ACT_019_REG040, FLSTST_DUD_ACT_019_REG041, FLSTST_DUD_ACT_019_REG042,
** Reference ID          : FLSTST_DUD_ACT_019_REG043, FLSTST_DUD_ACT_019_REG044, FLSTST_DUD_ACT_019_REG045,
** Reference ID          : FLSTST_DUD_ACT_019_REG046, FLSTST_DUD_ACT_019_REG047, FLSTST_DUD_ACT_019_REG048,
** Reference ID          : FLSTST_DUD_ACT_019_REG049, FLSTST_DUD_ACT_019_REG050, FLSTST_DUD_ACT_019_REG051,
** Reference ID          : FLSTST_DUD_ACT_019_REG052, FLSTST_DUD_ACT_019_REG053, FLSTST_DUD_ACT_019_REG054,
** Reference ID          : FLSTST_DUD_ACT_019_REG055, FLSTST_DUD_ACT_019_REG056, FLSTST_DUD_ACT_019_REG057,
** Reference ID          : FLSTST_DUD_ACT_019_REG058, FLSTST_DUD_ACT_019_REG059, FLSTST_DUD_ACT_019_REG060,
** Reference ID          : FLSTST_DUD_ACT_019_REG061, FLSTST_DUD_ACT_019_REG062, FLSTST_DUD_ACT_019_REG063,
** Reference ID          : FLSTST_DUD_ACT_019_REG064, FLSTST_DUD_ACT_019_REG065, FLSTST_DUD_ACT_019_REG066,
** Reference ID          : FLSTST_DUD_ACT_019_REG067, FLSTST_DUD_ACT_019_REG068, FLSTST_DUD_ACT_019_REG069,
** Reference ID          : FLSTST_DUD_ACT_019_REG070, FLSTST_DUD_ACT_019_REG071, FLSTST_DUD_ACT_019_REG072,
** Reference ID          : FLSTST_DUD_ACT_019_REG073, FLSTST_DUD_ACT_019_REG074, FLSTST_DUD_ACT_019_REG075,
** Reference ID          : FLSTST_DUD_ACT_019_REG076, FLSTST_DUD_ACT_019_REG077, FLSTST_DUD_ACT_019_REG078,
** Reference ID          : FLSTST_DUD_ACT_019_REG079, FLSTST_DUD_ACT_019_REG080, FLSTST_DUD_ACT_019_REG081,
** Reference ID          : FLSTST_DUD_ACT_019_REG082
*******************************************************************************/
static uint8 FlsTst_InitFgndTest(
  P2CONST(FlsTstBlock_ConfigType, AUTOMATIC, FLSTST_CONFIG_CONST) LpFlsTstBlock)
{
  uint8 LucByteToProcess;

  if (FLSTST_8BIT_2F == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC8 and 8 bits input data size */
    FLSTST_KCRCCTLFGND = FLSTST_CRC8_2F_CNTL;                                                                           /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    FLSTST_KCRCDOUT0FGND = FLSTST_CRC8_2F_INITIAL_VALUE;                                                                /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0FGND = FLSTST_CRC8_2F_POLY;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0FGND = FLSTST_8BIT_ALL_ONE;                                                                          /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */

    LucByteToProcess = (uint8)FLSTST_ONE;
  }
  else if (FLSTST_8BIT_SAE_J1850 == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC8 and 8 bits input data size */
    FLSTST_KCRCCTLFGND = FLSTST_CRC8_SAE_J1850_CNTL;                                                                    /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    FLSTST_KCRCDOUT0FGND = FLSTST_CRC8_SAE_J1850_INITIAL_VALUE;                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0FGND = FLSTST_CRC8_SAE_J1850_POLY;                                                                  /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0FGND = FLSTST_8BIT_ALL_ONE;                                                                          /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */

    LucByteToProcess = (uint8)FLSTST_ONE;
  }
  else if (FLSTST_15BIT_CRC15CAN == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC15 and 15 bits input data size */
    FLSTST_KCRCCTLFGND = FLSTST_CRC15_CRC15CAN_CNTL;                                                                    /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    FLSTST_KCRCDOUT0FGND = FLSTST_CRC15_CRC15CAN_INITIAL_VALUE;                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0FGND = FLSTST_CRC15_CRC15CAN_POLY;                                                                  /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */

    LucByteToProcess = (uint8)FLSTST_TWO;
  }
  else if (FLSTST_16BIT_CCITT16 == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC16 and 16 bits input data size */
    FLSTST_KCRCCTLFGND = FLSTST_CRC16_CCITT16_CNTL;                                                                     /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    FLSTST_KCRCDOUT0FGND = FLSTST_CRC16_CCITT16_INITIAL_VALUE;                                                          /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0FGND = FLSTST_CRC16_CCITT16_POLY;                                                                   /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */

    LucByteToProcess = (uint8)FLSTST_TWO;
  }
  else if (FLSTST_16BIT_BAICHEVA00 == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC16 and 16 bits input data size */
    FLSTST_KCRCCTLFGND = FLSTST_CRC16_BAICHEVA00_CNTL;                                                                  /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    FLSTST_KCRCDOUT0FGND = FLSTST_CRC16_BAICHEVA00_INITIAL_VALUE;                                                       /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0FGND = FLSTST_CRC16_BAICHEVA00_POLY;                                                                /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */

    LucByteToProcess = (uint8)FLSTST_TWO;
  }
  else if (FLSTST_16BIT_ARC == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC16 and 16 bits input data size */
    FLSTST_KCRCCTLFGND = FLSTST_CRC16_ARC_CNTL;                                                                         /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    FLSTST_KCRCDOUT0FGND = FLSTST_CRC16_ARC_INITIAL_VALUE;                                                              /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0FGND = FLSTST_CRC16_ARC_POLY;                                                                       /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */

    LucByteToProcess = (uint8)FLSTST_TWO;
  }
  else if (FLSTST_32BIT_CRC32 == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC32 and 32 bits input data size */
    FLSTST_KCRCCTLFGND = FLSTST_CRC32_CNTL;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    if (FLSTST_TRUE == LpFlsTstBlock->ucFlsTstAddressDepdntCrc)                                                         /* PRQA S 1881 # JV-01 */
    {
      FLSTST_KCRCDOUT0FGND = LpFlsTstBlock->ulFlsTstBlockBaseAddress;                                                   /* PRQA S 0303 # JV-01 */
    }
    else
    {
      FLSTST_KCRCDOUT0FGND = FLSTST_CRC32_INITIAL_VALUE;                                                                /* PRQA S 0303 # JV-01 */
    }
    FLSTST_KCRCDOUT1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0FGND = FLSTST_CRC32_POLY;                                                                           /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0FGND = FLSTST_32BIT_ALL_ONE;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */

    LucByteToProcess = (uint8)FLSTST_FOUR;
  }
  else if (FLSTST_32BIT_CRC32_REVPOLY == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC32 and 32 bits input data size */
    FLSTST_KCRCCTLFGND = FLSTST_CRC32_REVPOLY_CNTL;                                                                     /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    if (FLSTST_TRUE == LpFlsTstBlock->ucFlsTstAddressDepdntCrc)                                                         /* PRQA S 1881 # JV-01 */
    {
      FLSTST_KCRCDOUT0FGND = LpFlsTstBlock->ulFlsTstBlockBaseAddress;                                                   /* PRQA S 0303 # JV-01 */
    }
    else
    {
      FLSTST_KCRCDOUT0FGND = FLSTST_CRC32_REVPOLY_INITIAL_VALUE;                                                        /* PRQA S 0303 # JV-01 */
    }
    FLSTST_KCRCDOUT1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0FGND = FLSTST_CRC32_REVPOLY_POLY;                                                                   /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0FGND = FLSTST_32BIT_ALL_ONE;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */

    LucByteToProcess = (uint8)FLSTST_FOUR;
  }
  else if (FLSTST_32BIT_CRC32C == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC32 and 32 bits input data size */
    FLSTST_KCRCCTLFGND = FLSTST_CRC32_C_CNTL;                                                                           /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    if (FLSTST_TRUE == LpFlsTstBlock->ucFlsTstAddressDepdntCrc)                                                         /* PRQA S 1881 # JV-01 */
    {
      FLSTST_KCRCDOUT0FGND = LpFlsTstBlock->ulFlsTstBlockBaseAddress;                                                   /* PRQA S 0303 # JV-01 */
    }
    else
    {
      FLSTST_KCRCDOUT0FGND = FLSTST_CRC32_C_INITIAL_VALUE;                                                              /* PRQA S 0303 # JV-01 */
    }
    FLSTST_KCRCDOUT1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0FGND = FLSTST_CRC32_C_POLY;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0FGND = FLSTST_32BIT_ALL_ONE;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */

    LucByteToProcess = (uint8)FLSTST_FOUR;
  }
  else if (FLSTST_32BIT_CRC32P4 == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC32 and 32 bits input data size */
    FLSTST_KCRCCTLFGND = FLSTST_CRC32_P4_CNTL;                                                                          /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    if (FLSTST_TRUE == LpFlsTstBlock->ucFlsTstAddressDepdntCrc)                                                         /* PRQA S 1881 # JV-01 */
    {
      FLSTST_KCRCDOUT0FGND = LpFlsTstBlock->ulFlsTstBlockBaseAddress;                                                   /* PRQA S 0303 # JV-01 */
    }
    else
    {
      FLSTST_KCRCDOUT0FGND = FLSTST_CRC32_P4_INITIAL_VALUE;                                                             /* PRQA S 0303 # JV-01 */
    }
    FLSTST_KCRCDOUT1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0FGND = FLSTST_CRC32_P4_POLY;                                                                        /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1FGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0FGND = FLSTST_32BIT_ALL_ONE;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1FGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */

    LucByteToProcess = (uint8)FLSTST_FOUR;
  }
  else /* FLSTST_64BIT_CRC64ECMA */
  {
    /* Select CRC64 and 64 bits input data size */
    FLSTST_KCRCCTLFGND = FLSTST_CRC64_ECMA_CNTL;                                                                        /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    if (FLSTST_TRUE == LpFlsTstBlock->ucFlsTstAddressDepdntCrc)                                                         /* PRQA S 1881 # JV-01 */
    {
      FLSTST_KCRCDOUT0FGND = LpFlsTstBlock->ulFlsTstBlockBaseAddress;                                                   /* PRQA S 0303 # JV-01 */
    }
    else
    {
      FLSTST_KCRCDOUT0FGND = FLSTST_CRC64_ECMA_INITIAL_VALUE;                                                           /* PRQA S 0303 # JV-01 */
    }
    FLSTST_KCRCDOUT1FGND = FLSTST_CRC64_ECMA_INITIAL_VALUE;                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0FGND = FLSTST_CRC64_ECMA_POLY0;                                                                     /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1FGND = FLSTST_CRC64_ECMA_POLY1;                                                                     /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0FGND = FLSTST_32BIT_ALL_ONE;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1FGND = FLSTST_32BIT_ALL_ONE;                                                                         /* PRQA S 0303 # JV-01 */

    LucByteToProcess = (uint8)FLSTST_EIGHT;
  }

  return LucByteToProcess;
}
#endif

/*******************************************************************************
** Function Name         : FlsTst_ReadLoadMemDataBgnd
**
** Service ID            : NA
**
** Description           : Internal function to read the CRC value from the
**                         flash memory and write to data input register.
**
** Sync/Async            : NA
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LpFlsTstBlock
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GenExeState(R), FlsTst_GVar.FlsTst_GulReadAddress(R/W)
**
** Function(s) invoked   : None
**
** Registers Used        : KCRCDIN
** Reference ID          : FLSTST_DUD_ACT_018, FLSTST_DUD_ACT_018_REG001, FLSTST_DUD_ACT_018_GBL001,
** Reference ID          : FLSTST_DUD_ACT_018_CRT001, FLSTST_DUD_ACT_018_CRT002
*******************************************************************************/
#if (FLSTST_BGND_TEST_ENABLE == STD_ON)
static void FlsTst_ReadLoadMemDataBgnd(
  P2CONST(FlsTstBlock_ConfigType, AUTOMATIC, FLSTST_CONFIG_CONST) LpFlsTstBlock)
{
  /* Variable to hold  number of atomic cell count */
  uint32 LulAtomicCellCount;
  /* Variable to hold  number of byte to process in one call  */
  uint32 LulByteToProcess;
  /* Variable to hold  loop count */
  uint32 LulLoopCount;
  /* Variable to hold the execution state change */
  uint8 LucSuspendAbortCheck;
  /* Variable to hold data from flash */
  uint8 Lucdata;

  /* Check block size is greater than no of cell to be tested in
  * one scheduled task (FlsTst_MainFunction() call), if yes load
  * maximum value configured for one scheduled task.
  */
  if (((LpFlsTstBlock->ulFlsTstBlockBaseAddress +                                                                       /* PRQA S 3383 # JV-01 */
        LpFlsTstBlock->ulFlsTstBlockSize) -                                                                             /* PRQA S 3384 # JV-01 */
        FlsTst_GVar.FlsTst_GulReadAddress)
                          > FLSTST_NUMBER_OF_TESTED_CELLS)
  {
    LulByteToProcess = FLSTST_NUMBER_OF_TESTED_CELLS;
  }
  else
  {
    LulByteToProcess = (LpFlsTstBlock->ulFlsTstBlockBaseAddress +                                                       /* PRQA S 3383 # JV-01 */
      LpFlsTstBlock->ulFlsTstBlockSize) - FlsTst_GVar.FlsTst_GulReadAddress;                                            /* PRQA S 3384 # JV-01 */
  }

  /* Initialize atomic cell count to zero */
  LulAtomicCellCount = FLSTST_ZERO;
  LucSuspendAbortCheck = FLSTST_ZERO;

  /* Loop all cells to be tested in one scheduled task */
  for (LulLoopCount = FLSTST_ZERO; ((LulLoopCount < LulByteToProcess) &&
                (FLSTST_ZERO == LucSuspendAbortCheck)); LulLoopCount++)
  {
    /* Read the data from memory  */
    Lucdata = (*((volatile uint8 *)(FlsTst_GVar.FlsTst_GulReadAddress)));                                               /* PRQA S 0303 # JV-01 */
    /* Load the data in crc input reg */
    FLSTST_KCRCDINBGND = (uint32)Lucdata;                                                                               /* PRQA S 0303 # JV-01 */
    /* Increment the address */
    FlsTst_GVar.FlsTst_GulReadAddress++;                                                                                /* PRQA S 3383 # JV-01 */
    /* Increment atomic cell count */
    LulAtomicCellCount++;                                                                                               /* PRQA S 3383 # JV-01 */

    /* Check if number of atomic cell exceeds configured value */
    if (LulAtomicCellCount > FLSTST_NUMBER_OF_TESTED_CELLS_ATOMIC)
    {
      /* Re-initialize to zero */
      LulAtomicCellCount = FLSTST_ZERO;

      /* Enter critical section */
      FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
      /* Check user requests (Abort, Suspend) */
      if (FLSTST_SUSPENDED == FlsTst_GenExeState)
      {
        LucSuspendAbortCheck = FLSTST_ONE;
      }
      else if (FLSTST_ABORTED == FlsTst_GenExeState)
      {
        LucSuspendAbortCheck = FLSTST_ONE;
      }
      else
      {
        /* No action required */
      }
      /* Exit critical section */
      FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
    }/* else: No action required */
  }
}

/*******************************************************************************
** Function Name         : FlsTst_GetStoredCRC
**
** Service ID            : NA
**
** Description           : Internal function to get CRC value stored in
**                         signature address.
**
** Sync/Async            : NA
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LpFlsTstBlock
**
** InOut Parameters      : None
**
** Output Parameters     : LpStoredBgndCrc
**
** Return parameter      : None
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GVar.FlsTst_GucByteToProcess(R)
**
** Function(s) invoked   : None
**
** Registers Used        : None
** Reference ID          : FLSTST_DUD_ACT_017
*******************************************************************************/
static void FlsTst_GetStoredCRC(
  P2CONST(FlsTstBlock_ConfigType, AUTOMATIC, FLSTST_CONFIG_CONST) LpFlsTstBlock,
  P2VAR(uint32, AUTOMATIC, FLSTST_APPL_DATA) LpStoredBgndCrc)                                                           /* PRQA S 3432 # JV-01 */
{
  /* Variable to hold bgnd signature address */
  uint32 LulBgndSignatureAddress;
  /* Variable to hold  loop count */
  uint8 LucLoopCount;
  /* Variable to hold  number of byte to process in one call  */
  uint8 LucByteToProcess;
  /* Local union variable to access crc value */
  FlsTst_CrcConvert LddCrcConvert;                                                                                      /* PRQA S 0759 # JV-01 */
  /* Local union variable to access higher bytes of crc64 value */
  FlsTst_CrcConvert LddCrc64Convert;                                                                                    /* PRQA S 0759 # JV-01 */

  /* Initialize variable */
  LddCrcConvert.ulCrc32Data = FLSTST_ZERO;
  LddCrc64Convert.ulCrc32Data = FLSTST_ZERO;
  LulBgndSignatureAddress = LpFlsTstBlock->ulFlsTstSignatureAddress;
  LucByteToProcess = FlsTst_GVar.FlsTst_GucByteToProcess;

  /* Read stored crc from signature address */
  for (LucLoopCount = FLSTST_ZERO; LucLoopCount < LucByteToProcess;
      LucLoopCount++)
  {
    /* Read stored crc data from memory and store in array */
    if (FLSTST_FOUR > LucLoopCount)
    {
      LddCrcConvert.ucCrcData4[LucLoopCount] =
        *((volatile uint8 *)LulBgndSignatureAddress);                                                                   /* PRQA S 0303 # JV-01 */
    }
    else
    {
      LddCrc64Convert.ucCrcData4[LucLoopCount - FLSTST_FOUR] =                                                          
        *((volatile uint8 *)LulBgndSignatureAddress);                                                                   /* PRQA S 0303 # JV-01 */
    }

    /* Increase to next memory location */
    LulBgndSignatureAddress++;                                                                                          /* PRQA S 3383 # JV-01 */
  }

  /* Get the calculated CRC value from KCRC unit */
  if ((FLSTST_8BIT_2F == LpFlsTstBlock->enFlsTstTestAlgorithm) ||
      (FLSTST_8BIT_SAE_J1850 == LpFlsTstBlock->enFlsTstTestAlgorithm))
  {
    LpStoredBgndCrc[FLSTST_ZERO] = (uint32)LddCrcConvert.ucCrc8Data;
  }
  else if (FLSTST_15BIT_CRC15CAN == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    LpStoredBgndCrc[FLSTST_ZERO] = (uint32)LddCrcConvert.usCrc16Data;
  }
  else if ((FLSTST_16BIT_CCITT16 == LpFlsTstBlock->enFlsTstTestAlgorithm) ||
          (FLSTST_16BIT_BAICHEVA00 == LpFlsTstBlock->enFlsTstTestAlgorithm) ||
          (FLSTST_16BIT_ARC == LpFlsTstBlock->enFlsTstTestAlgorithm))
  {
    LpStoredBgndCrc[FLSTST_ZERO] = (uint32)LddCrcConvert.usCrc16Data;
  }
  else if ((FLSTST_32BIT_CRC32 == LpFlsTstBlock->enFlsTstTestAlgorithm) ||
          (FLSTST_32BIT_CRC32_REVPOLY == LpFlsTstBlock->enFlsTstTestAlgorithm) ||
          (FLSTST_32BIT_CRC32C == LpFlsTstBlock->enFlsTstTestAlgorithm) ||
          (FLSTST_32BIT_CRC32P4 == LpFlsTstBlock->enFlsTstTestAlgorithm))
  {
    LpStoredBgndCrc[FLSTST_ZERO] = LddCrcConvert.ulCrc32Data;
  }
  else /* FLSTST_64BIT_CRC64ECMA */
  {
    LpStoredBgndCrc[FLSTST_ZERO] = LddCrcConvert.ulCrc32Data;
    LpStoredBgndCrc[FLSTST_ONE] =  LddCrc64Convert.ulCrc32Data;
  }
}

/*******************************************************************************
** Function Name         : FlsTst_InitBgndTest
**
** Service ID            : NA
**
** Description           : Internal function to intialize back ground test
**                         related registers.
**
** Sync/Async            : NA
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LpFlsTstBlock
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GVar.FlsTst_GucByteToProcess(W)
**
** Function(s) invoked   : None
**
** Registers Used        : KCRCCTL, KCRCDOUT0, KCRCDOUT1, KCRCPOLY0,
**                                  KCRCPOLY1, KCRCXOR0, KCRCXOR1.
** Reference ID          : FLSTST_DUD_ACT_020,
** Reference ID          : FLSTST_DUD_ACT_020_REG001, FLSTST_DUD_ACT_020_REG002, FLSTST_DUD_ACT_020_REG003, 
** Reference ID          : FLSTST_DUD_ACT_020_REG004, FLSTST_DUD_ACT_020_REG005, FLSTST_DUD_ACT_020_REG006,
** Reference ID          : FLSTST_DUD_ACT_020_REG007, FLSTST_DUD_ACT_020_REG008, FLSTST_DUD_ACT_020_REG009,
** Reference ID          : FLSTST_DUD_ACT_020_REG010, FLSTST_DUD_ACT_020_REG011, FLSTST_DUD_ACT_020_REG012,
** Reference ID          : FLSTST_DUD_ACT_020_REG013, FLSTST_DUD_ACT_020_REG014, FLSTST_DUD_ACT_020_REG015,
** Reference ID          : FLSTST_DUD_ACT_020_REG016, FLSTST_DUD_ACT_020_REG017, FLSTST_DUD_ACT_020_REG018,
** Reference ID          : FLSTST_DUD_ACT_020_REG019, FLSTST_DUD_ACT_020_REG020, FLSTST_DUD_ACT_020_REG021,
** Reference ID          : FLSTST_DUD_ACT_020_REG022, FLSTST_DUD_ACT_020_REG023, FLSTST_DUD_ACT_020_REG024,
** Reference ID          : FLSTST_DUD_ACT_020_REG025, FLSTST_DUD_ACT_020_REG026, FLSTST_DUD_ACT_020_REG027,
** Reference ID          : FLSTST_DUD_ACT_020_REG028, FLSTST_DUD_ACT_020_REG029, FLSTST_DUD_ACT_020_REG030,
** Reference ID          : FLSTST_DUD_ACT_020_REG031, FLSTST_DUD_ACT_020_REG032, FLSTST_DUD_ACT_020_REG033,
** Reference ID          : FLSTST_DUD_ACT_020_REG034, FLSTST_DUD_ACT_020_REG035, FLSTST_DUD_ACT_020_REG036,
** Reference ID          : FLSTST_DUD_ACT_020_REG037, FLSTST_DUD_ACT_020_REG038, FLSTST_DUD_ACT_020_REG039,
** Reference ID          : FLSTST_DUD_ACT_020_REG040, FLSTST_DUD_ACT_020_REG041, FLSTST_DUD_ACT_020_REG042,
** Reference ID          : FLSTST_DUD_ACT_020_REG043, FLSTST_DUD_ACT_020_REG044, FLSTST_DUD_ACT_020_REG045,
** Reference ID          : FLSTST_DUD_ACT_020_REG046, FLSTST_DUD_ACT_020_REG047, FLSTST_DUD_ACT_020_REG048,
** Reference ID          : FLSTST_DUD_ACT_020_REG049, FLSTST_DUD_ACT_020_REG050, FLSTST_DUD_ACT_020_REG051,
** Reference ID          : FLSTST_DUD_ACT_020_REG052, FLSTST_DUD_ACT_020_REG053, FLSTST_DUD_ACT_020_REG054,
** Reference ID          : FLSTST_DUD_ACT_020_REG055, FLSTST_DUD_ACT_020_REG056, FLSTST_DUD_ACT_020_REG057,
** Reference ID          : FLSTST_DUD_ACT_020_REG058, FLSTST_DUD_ACT_020_REG059, FLSTST_DUD_ACT_020_REG060,
** Reference ID          : FLSTST_DUD_ACT_020_REG061, FLSTST_DUD_ACT_020_REG062, FLSTST_DUD_ACT_020_REG063,
** Reference ID          : FLSTST_DUD_ACT_020_REG064, FLSTST_DUD_ACT_020_REG065, FLSTST_DUD_ACT_020_REG066,
** Reference ID          : FLSTST_DUD_ACT_020_REG067, FLSTST_DUD_ACT_020_REG068, FLSTST_DUD_ACT_020_REG069,
** Reference ID          : FLSTST_DUD_ACT_020_REG070, FLSTST_DUD_ACT_020_REG071, FLSTST_DUD_ACT_020_REG072,
** Reference ID          : FLSTST_DUD_ACT_020_REG073, FLSTST_DUD_ACT_020_REG074, FLSTST_DUD_ACT_020_REG075,
** Reference ID          : FLSTST_DUD_ACT_020_REG076, FLSTST_DUD_ACT_020_REG077, FLSTST_DUD_ACT_020_REG078,
** Reference ID          : FLSTST_DUD_ACT_020_REG079, FLSTST_DUD_ACT_020_REG080, FLSTST_DUD_ACT_020_REG081,
** Reference ID          : FLSTST_DUD_ACT_020_REG082, FLSTST_DUD_ACT_020_GBL001, FLSTST_DUD_ACT_020_GBL002,
** Reference ID          : FLSTST_DUD_ACT_020_GBL003, FLSTST_DUD_ACT_020_GBL004, FLSTST_DUD_ACT_020_GBL005,
** Reference ID          : FLSTST_DUD_ACT_020_GBL006, FLSTST_DUD_ACT_020_GBL007, FLSTST_DUD_ACT_020_GBL008,
** Reference ID          : FLSTST_DUD_ACT_020_GBL009, FLSTST_DUD_ACT_020_GBL010, FLSTST_DUD_ACT_020_GBL011
*******************************************************************************/
static void FlsTst_InitBgndTest(
  P2CONST(FlsTstBlock_ConfigType, AUTOMATIC, FLSTST_CONFIG_CONST) LpFlsTstBlock)
{
  /* Initialize the CRC value for new test */
  if (FLSTST_8BIT_2F == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC8 and 8 bits input data size */
    FLSTST_KCRCCTLBGND = FLSTST_CRC8_2F_CNTL;                                                                           /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    FLSTST_KCRCDOUT0BGND = FLSTST_CRC8_2F_INITIAL_VALUE;                                                                /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0BGND = FLSTST_CRC8_2F_POLY;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0BGND = FLSTST_8BIT_ALL_ONE;                                                                          /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
  
    FlsTst_GVar.FlsTst_GucByteToProcess = (uint8)FLSTST_ONE;
  }
  else if (FLSTST_8BIT_SAE_J1850 == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC8 and 8 bits input data size */
    FLSTST_KCRCCTLBGND = FLSTST_CRC8_SAE_J1850_CNTL;                                                                    /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    FLSTST_KCRCDOUT0BGND = FLSTST_CRC8_SAE_J1850_INITIAL_VALUE;                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0BGND = FLSTST_CRC8_SAE_J1850_POLY;                                                                  /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0BGND = FLSTST_8BIT_ALL_ONE;                                                                          /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
  
    FlsTst_GVar.FlsTst_GucByteToProcess = (uint8)FLSTST_ONE;
  }
  else if (FLSTST_15BIT_CRC15CAN == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC15 and 15 bits input data size */
    FLSTST_KCRCCTLBGND = FLSTST_CRC15_CRC15CAN_CNTL;                                                                    /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    FLSTST_KCRCDOUT0BGND = FLSTST_CRC15_CRC15CAN_INITIAL_VALUE;                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0BGND = FLSTST_CRC15_CRC15CAN_POLY;                                                                  /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
  
    FlsTst_GVar.FlsTst_GucByteToProcess = (uint8)FLSTST_TWO;
  }
  else if (FLSTST_16BIT_CCITT16 == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC16 and 16 bits input data size */
    FLSTST_KCRCCTLBGND = FLSTST_CRC16_CCITT16_CNTL;                                                                     /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    FLSTST_KCRCDOUT0BGND = FLSTST_CRC16_CCITT16_INITIAL_VALUE;                                                          /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0BGND = FLSTST_CRC16_CCITT16_POLY;                                                                   /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
  
    FlsTst_GVar.FlsTst_GucByteToProcess = (uint8)FLSTST_TWO;
  }
  else if (FLSTST_16BIT_BAICHEVA00 == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC16 and 16 bits input data size */
    FLSTST_KCRCCTLBGND = FLSTST_CRC16_BAICHEVA00_CNTL;                                                                  /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    FLSTST_KCRCDOUT0BGND = FLSTST_CRC16_BAICHEVA00_INITIAL_VALUE;                                                       /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0BGND = FLSTST_CRC16_BAICHEVA00_POLY;                                                                /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
  
    FlsTst_GVar.FlsTst_GucByteToProcess = (uint8)FLSTST_TWO;
  }
  else if (FLSTST_16BIT_ARC == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC16 and 16 bits input data size */
    FLSTST_KCRCCTLBGND = FLSTST_CRC16_ARC_CNTL;                                                                         /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    FLSTST_KCRCDOUT0BGND = FLSTST_CRC16_ARC_INITIAL_VALUE;                                                              /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCDOUT1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0BGND = FLSTST_CRC16_ARC_POLY;                                                                       /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
  
    FlsTst_GVar.FlsTst_GucByteToProcess = (uint8)FLSTST_TWO;
  }
  else if (FLSTST_32BIT_CRC32 == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC32 and 32 bits input data size */
    FLSTST_KCRCCTLBGND = FLSTST_CRC32_CNTL;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    if (FLSTST_TRUE == LpFlsTstBlock->ucFlsTstAddressDepdntCrc)                                                         /* PRQA S 1881 # JV-01 */
    {
      FLSTST_KCRCDOUT0BGND = LpFlsTstBlock->ulFlsTstBlockBaseAddress;                                                   /* PRQA S 0303 # JV-01 */
    }
    else
    {
      FLSTST_KCRCDOUT0BGND = FLSTST_CRC32_INITIAL_VALUE;                                                                /* PRQA S 0303 # JV-01 */
    }
    FLSTST_KCRCDOUT1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0BGND = FLSTST_CRC32_POLY;                                                                           /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0BGND = FLSTST_32BIT_ALL_ONE;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
  
    FlsTst_GVar.FlsTst_GucByteToProcess = (uint8)FLSTST_FOUR;
  }
  else if (FLSTST_32BIT_CRC32_REVPOLY == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC32 and 32 bits input data size */
    FLSTST_KCRCCTLBGND = FLSTST_CRC32_REVPOLY_CNTL;                                                                     /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    if (FLSTST_TRUE == LpFlsTstBlock->ucFlsTstAddressDepdntCrc)                                                         /* PRQA S 1881 # JV-01 */
    {
      FLSTST_KCRCDOUT0BGND = LpFlsTstBlock->ulFlsTstBlockBaseAddress;                                                   /* PRQA S 0303 # JV-01 */
    }
    else
    {
      FLSTST_KCRCDOUT0BGND = FLSTST_CRC32_REVPOLY_INITIAL_VALUE;                                                        /* PRQA S 0303 # JV-01 */
    }
    FLSTST_KCRCDOUT1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0BGND = FLSTST_CRC32_REVPOLY_POLY;                                                                   /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0BGND = FLSTST_32BIT_ALL_ONE;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
  
    FlsTst_GVar.FlsTst_GucByteToProcess = (uint8)FLSTST_FOUR;
  }
  else if (FLSTST_32BIT_CRC32C == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC32 and 32 bits input data size */
    FLSTST_KCRCCTLBGND = FLSTST_CRC32_C_CNTL;                                                                           /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    if (FLSTST_TRUE == LpFlsTstBlock->ucFlsTstAddressDepdntCrc)                                                         /* PRQA S 1881 # JV-01 */
    {
      FLSTST_KCRCDOUT0BGND = LpFlsTstBlock->ulFlsTstBlockBaseAddress;                                                   /* PRQA S 0303 # JV-01 */
    }
    else
    {
      FLSTST_KCRCDOUT0BGND = FLSTST_CRC32_C_INITIAL_VALUE;                                                              /* PRQA S 0303 # JV-01 */
    }
    FLSTST_KCRCDOUT1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0BGND = FLSTST_CRC32_C_POLY;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0BGND = FLSTST_32BIT_ALL_ONE;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
  
    FlsTst_GVar.FlsTst_GucByteToProcess = (uint8)FLSTST_FOUR;
  }
  else if (FLSTST_32BIT_CRC32P4 == LpFlsTstBlock->enFlsTstTestAlgorithm)
  {
    /* Select CRC32 and 32 bits input data size */
    FLSTST_KCRCCTLBGND = FLSTST_CRC32_P4_CNTL;                                                                          /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    if (FLSTST_TRUE == LpFlsTstBlock->ucFlsTstAddressDepdntCrc)                                                         /* PRQA S 1881 # JV-01 */
    {
      FLSTST_KCRCDOUT0BGND = LpFlsTstBlock->ulFlsTstBlockBaseAddress;                                                   /* PRQA S 0303 # JV-01 */
    }
    else
    {
      FLSTST_KCRCDOUT0BGND = FLSTST_CRC32_P4_INITIAL_VALUE;                                                             /* PRQA S 0303 # JV-01 */
    }
    FLSTST_KCRCDOUT1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0BGND = FLSTST_CRC32_P4_POLY;                                                                        /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1BGND = FLSTST_ALL_ZERO;                                                                             /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0BGND = FLSTST_32BIT_ALL_ONE;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1BGND = FLSTST_ALL_ZERO;                                                                              /* PRQA S 0303 # JV-01 */
  
    FlsTst_GVar.FlsTst_GucByteToProcess = (uint8)FLSTST_FOUR;
  }
  else /* FLSTST_64BIT_CRC64ECMA */
  {
    /* Select CRC64 and 64 bits input data size */
    FLSTST_KCRCCTLBGND = FLSTST_CRC64_ECMA_CNTL;                                                                        /* PRQA S 0303 # JV-01 */
    /* Set initial value for data output register */
    if (FLSTST_TRUE == LpFlsTstBlock->ucFlsTstAddressDepdntCrc)                                                         /* PRQA S 1881 # JV-01 */
    {
      FLSTST_KCRCDOUT0BGND = LpFlsTstBlock->ulFlsTstBlockBaseAddress;                                                   /* PRQA S 0303 # JV-01 */
    }
    else
    {
      FLSTST_KCRCDOUT0BGND = FLSTST_CRC64_ECMA_INITIAL_VALUE;                                                           /* PRQA S 0303 # JV-01 */
    }
    FLSTST_KCRCDOUT1BGND = FLSTST_CRC64_ECMA_INITIAL_VALUE;                                                             /* PRQA S 0303 # JV-01 */
    /* Set Polynomial */
    FLSTST_KCRCPOLY0BGND = FLSTST_CRC64_ECMA_POLY0;                                                                     /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCPOLY1BGND = FLSTST_CRC64_ECMA_POLY1;                                                                     /* PRQA S 0303 # JV-01 */
    /* Set XOR mask */
    FLSTST_KCRCXOR0BGND = FLSTST_32BIT_ALL_ONE;                                                                         /* PRQA S 0303 # JV-01 */
    FLSTST_KCRCXOR1BGND = FLSTST_32BIT_ALL_ONE;                                                                         /* PRQA S 0303 # JV-01 */
  
    FlsTst_GVar.FlsTst_GucByteToProcess = (uint8)FLSTST_EIGHT;
  }
}
#endif

/*******************************************************************************
** Function Name         : FlsTst_TestEccCFBank
**
** Service ID            : NA
**
** Description           : Internal function for ECC test of code flash 
**                         bank area.
**
** Sync/Async            : NA
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GddEccErrorDetail.ucCFBankEccStatus(W),
**                         FlsTst_GddEccErrorDetail.ulCFBankEccFaultAddress(W)
**
** Function(s) invoked   : FLSTST_ENTER_CRITICAL_SECTION,
**                         FLSTST_EXIT_CRITICAL_SECTION
**
** Registers Used        : CFCECCCTL, CF_ERRINT, CF_SSTCLR, CF_DSTCLR,
**                         CF_SERSTR, CF_00SEADR, CF_DERSTR, CF_00DEADR.
** Reference ID          : FLSTST_DUD_ACT_021,
** Reference ID          : FLSTST_DUD_ACT_021_CRT001, FLSTST_DUD_ACT_021_CRT002, FLSTST_DUD_ACT_021_REG001, 
** Reference ID          : FLSTST_DUD_ACT_021_REG002, FLSTST_DUD_ACT_021_REG003, FLSTST_DUD_ACT_021_REG004,
** Reference ID          : FLSTST_DUD_ACT_021_REG005, FLSTST_DUD_ACT_021_REG006, FLSTST_DUD_ACT_021_REG007,
** Reference ID          : FLSTST_DUD_ACT_021_REG008, FLSTST_DUD_ACT_021_REG009, FLSTST_DUD_ACT_021_GBL001,
** Reference ID          : FLSTST_DUD_ACT_021_GBL002
*******************************************************************************/
#if (FLSTST_TEST_ECC_API  == STD_ON) && (FLSTST_TEST_ECC_CF_BANK == STD_ON)
static Std_ReturnType FlsTst_TestEccCFBank(void)                                                                        /* PRQA S 3006 # JV-01 */
{
  P2CONST(volatile uint32, AUTOMATIC, FLSTST_APPL_CONST) LpEccTestAddress;
  P2CONST(volatile uint32, AUTOMATIC, FLSTST_APPL_CONST) LpErrStatusReg;
  P2CONST(volatile uint32, AUTOMATIC, FLSTST_APPL_CONST) LpErrAddrReg;
  P2VAR(volatile uint32, AUTOMATIC, FLSTST_APPL_DATA) LpErrClearReg;
  uint32 LulCompareData;
  uint32 LulDataWord;
  uint32 LulEccSaveAddress;
  uint16 LusPatternNumber;
  uint8 LucLoopCount;
  uint8 LucEccDelayCount;
  uint8 LucExpectedError;
  Std_ReturnType LenReturnValue;

  /* Initialize return value */
  LenReturnValue = E_OK;

  /* Enable ECC error detection and SEC */
  FLSTST_CFCECCCTL = FLSTST_ECC_SEC_APE_ACTIVATE;                                                                       /* PRQA S 0303 # JV-01 */
  /* Disable ECC notification */
  FLSTST_CF_ERRINT = FLSTST_ECC_DISABLE_NOTIFICATION;                                                                   /* PRQA S 0303 # JV-01 */
  /* Clear ECC status registers */
  FLSTST_CF_SSTCLR = (uint32)FLSTST_ONE;                                                                                /* PRQA S 0303 # JV-01 */
  FLSTST_CF_DSTCLR = (uint32)FLSTST_ONE;                                                                                /* PRQA S 0303 # JV-01 */

  /* Initialize variables for walking-1 pattern */
  LusPatternNumber = (uint16)FLSTST_ONE;
  LulCompareData = FLSTST_ZERO;
  LucExpectedError = FLSTST_ONE;
  LpErrStatusReg = &FLSTST_CF_SERSTR;                                                                                   /* PRQA S 0303 # JV-01 */
  LpErrAddrReg = &FLSTST_CF_00SEADR;                                                                                    /* PRQA S 0303 # JV-01 */
  LpErrClearReg = &FLSTST_CF_SSTCLR;                                                                                    /* PRQA S 0303 # JV-01 */
  /* Set global self test address */
  LpEccTestAddress = FLSTST_ECC_BANK_SELF_TEST_ADDRESS;                                                                 /* PRQA S 0303 # JV-01 */

  /* Loop through all patters */
  while (LusPatternNumber <= FLSTST_ECC_CF_BANK_APE_PATTERN)
  {
    /* Update compared data, expected error for each pattern */
    if(FLSTST_CF_BANK_WALK1_END == LusPatternNumber)
    {
      LulCompareData = FLSTST_ALL1_VALUE;
      LucExpectedError = FLSTST_TWO;
      /* Change register address to fatal error register after walking-1 end */
      LpErrStatusReg = &FLSTST_CF_DERSTR;                                                                               /* PRQA S 0303 # JV-01 */
      LpErrAddrReg = &FLSTST_CF_00DEADR;                                                                                /* PRQA S 0303 # JV-01 */
      LpErrClearReg = &FLSTST_CF_DSTCLR;                                                                                /* PRQA S 0303 # JV-01 */
    }
    else if ((FLSTST_CF_BANK_ALL1_END == LusPatternNumber) ||
             (FLSTST_ECC_CF_BANK_END_PATTERN == LusPatternNumber))
    {
      LulCompareData = FLSTST_LONG_WORD_ZERO;
      LucExpectedError = FLSTST_TWO;
    }
    else if (FLSTST_ECC_CF_BANK_APE_PATTERN == LusPatternNumber)
    {
      LulCompareData = FLSTST_LONG_WORD_ZERO;
      LucExpectedError = FLSTST_FOUR;
    }
    else /* Walking-1 pattern */
    {
      /* No action required */
    }

    /* Update expected error address at the start of each pattern */
    LulEccSaveAddress = (uint32)LpEccTestAddress;                                                                       /* PRQA S 0303 # JV-01 */

    /* Loop through each address in a pattern */
    for (LucLoopCount = FLSTST_ZERO; LucLoopCount < FLSTST_EIGHT;
                                                          LucLoopCount++)
    {
      /* Small delay for ECC error and address status update */
      for (LucEccDelayCount = FLSTST_ZERO;
               LucEccDelayCount < FLSTST_ECC_TEST_DELAY; LucEccDelayCount++)
      {
        /* No operation */
        ASM_NOP();                                                                                                      /* PRQA S 1006 # JV-01 */
      }

      /* Update expected address if required */
      if (FLSTST_FOUR == LucLoopCount)
      {
        LulEccSaveAddress = (uint32)LpEccTestAddress;                                                                   /* PRQA S 0303 # JV-01 */
      }/* else: No action required */

      /* Update compared data to 2-bit error if required */
      if (FLSTST_SEVEN == LucLoopCount)
      {
        if(FLSTST_ECC_CF_BANK_END_PATTERN == LusPatternNumber)
        {
          LulCompareData = FLSTST_2BIT_ERROR_VALUE;
        }/* else: No action required */
      }/* else: No action required */

      /* Read the data from global ECC self test area */
      LulDataWord = *(LpEccTestAddress);

      /* Check if data from global ECC self test address is same expected value */
      if ((LulDataWord != LulCompareData) ||
          ((uint32)LucExpectedError != *LpErrStatusReg) ||
          (LulEccSaveAddress != FLSTST_GET_ECC_ERR_ADDR(*LpErrAddrReg)))                                                /* PRQA S 3432 # JV-01 */
      {
        /* Update test result to not ok */
        LenReturnValue = E_NOT_OK;
        /* Enter critical section */
        FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
        /* Save ECC error status and address */
        FlsTst_GddEccErrorDetail.ucCFBankEccStatus = (uint8)(*LpErrStatusReg);
        FlsTst_GddEccErrorDetail.ulCFBankEccFaultAddress =
          FLSTST_GET_ECC_ERR_ADDR(*LpErrAddrReg);                                                                       /* PRQA S 3432 # JV-01 */
        /* Exit critical section */
        FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
      }/* else: No action required */

      /* Clear the ECC error flag */
      *LpErrClearReg = (uint32)FLSTST_ONE;

      /* Increase ECC test address */
      LpEccTestAddress++;
    }

    /* Increase the pattern number */
    LusPatternNumber++;
  }

  /* Enable ECC error detection, SEC and APE */
  FLSTST_CFCECCCTL = FLSTST_ECC_SEC_APE_ACTIVATE;                                                                       /* PRQA S 0303 # JV-01 */
  /* Enable ECC notification */
  FLSTST_CF_ERRINT = FLSTST_ECC_ENABLE_NOTIFICATION;                                                                    /* PRQA S 0303 # JV-01 */
  /* Clear ECC status registers */
  FLSTST_CF_SSTCLR = (uint32)FLSTST_ONE;                                                                                /* PRQA S 0303 # JV-01 */
  FLSTST_CF_DSTCLR = (uint32)FLSTST_ONE;                                                                                /* PRQA S 0303 # JV-01 */

  return LenReturnValue;
}
#endif

/*******************************************************************************
** Function Name         : FlsTst_TestEccCFGlobal
**
** Service ID            : NA
**
** Description           : Internal function for ECC test of code flash 
**                         global area.
**
** Sync/Async            : NA
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : 
**
** Preconditions         : Component must be initialized using FlsTst_Init().
**
** Global Variables Used : FlsTst_GddEccErrorDetail.ucCFGlobalEccStatus(W),
**                         FlsTst_GddEccErrorDetail.ulCFGlobalEccFaultAddress(W)
**
** Function(s) invoked   : FLSTST_ENTER_CRITICAL_SECTION,
**                         FLSTST_EXIT_CRITICAL_SECTION
**
** Registers Used        : CFSECCCTL, CF_ERRINT, CF_SSTCLR, CF_DSTCLR,
**                         CF_SERSTR, CF_00SEADR, CF_DERSTR, CF_00DEADR.
** Reference ID          : FLSTST_DUD_ACT_022,
** Reference ID          : FLSTST_DUD_ACT_022_CRT001, FLSTST_DUD_ACT_022_CRT002, FLSTST_DUD_ACT_022_REG001, 
** Reference ID          : FLSTST_DUD_ACT_022_REG002, FLSTST_DUD_ACT_022_REG003, FLSTST_DUD_ACT_022_REG004,
** Reference ID          : FLSTST_DUD_ACT_022_REG005, FLSTST_DUD_ACT_022_REG006, FLSTST_DUD_ACT_022_REG007,
** Reference ID          : FLSTST_DUD_ACT_022_REG008, FLSTST_DUD_ACT_022_REG009, FLSTST_DUD_ACT_022_GBL001,
** Reference ID          : FLSTST_DUD_ACT_022_GBL002
*******************************************************************************/
#if (FLSTST_TEST_ECC_API  == STD_ON) && (FLSTST_TEST_ECC_CF_GLOBAL == STD_ON)
static Std_ReturnType FlsTst_TestEccCFGlobal(void)                                                                      /* PRQA S 3006 # JV-01 */
{
  P2CONST(volatile uint32, AUTOMATIC, FLSTST_APPL_CONST) LpEccTestAddress;
  P2CONST(volatile uint32, AUTOMATIC, FLSTST_APPL_CONST) LpErrStatusReg;
  P2CONST(volatile uint32, AUTOMATIC, FLSTST_APPL_CONST) LpErrAddrReg;
  P2VAR(volatile uint32, AUTOMATIC, FLSTST_APPL_DATA) LpErrClearReg;
  uint32 LulCompareData;
  uint32 LulDataWord;
  uint32 LulEccSaveAddress;
  uint16 LusPatternNumber;
  uint8 LucLoopCount;
  uint8 LucEccDelayCount;
  uint8 LucExpectedError;
  Std_ReturnType LenReturnValue;

  /* Initialize return value */
  LenReturnValue = E_OK;

  /* Enable ECC error detection and SEC */
  FLSTST_CFSECCCTL = FLSTST_ECC_SEC_ACTIVATE;                                                                           /* PRQA S 0303 # JV-01 */
  /* Disable ECC notification */
  FLSTST_CF_ERRINT = FLSTST_ECC_DISABLE_NOTIFICATION;                                                                   /* PRQA S 0303 # JV-01 */
  /* Clear ECC status registers */
  FLSTST_CF_SSTCLR = (uint32)FLSTST_ONE;                                                                                /* PRQA S 0303 # JV-01 */
  FLSTST_CF_DSTCLR = (uint32)FLSTST_ONE;                                                                                /* PRQA S 0303 # JV-01 */

  /* Initialize variables for walking-1 pattern */
  LusPatternNumber = (uint16)FLSTST_ONE;
  LulCompareData = FLSTST_ZERO;
  LucExpectedError = FLSTST_ONE;
  LpErrStatusReg = &FLSTST_CF_SERSTR;                                                                                   /* PRQA S 0303 # JV-01 */
  LpErrAddrReg = &FLSTST_CF_00SEADR;                                                                                    /* PRQA S 0303 # JV-01 */
  LpErrClearReg = &FLSTST_CF_SSTCLR;                                                                                    /* PRQA S 0303 # JV-01 */
  /* Set global self test address */
  LpEccTestAddress = FLSTST_ECC_GLOBAL_SELF_TEST_ADDRESS;                                                               /* PRQA S 0303 # JV-01 */

  /* Loop through all patters */
  while (LusPatternNumber <= (uint16)FLSTST_ECC_CF_GLOBAL_END_PATTERN)
  {
    /* Update compared data, expected error for each pattern */
    if(FLSTST_CF_GLOBAL_WALK1_END == LusPatternNumber)
    {
      LulCompareData = FLSTST_ALL1_VALUE;
      LucExpectedError = FLSTST_TWO;
      /* Change register address to fatal error register after walking-1 end */
      LpErrStatusReg = &FLSTST_CF_DERSTR;                                                                               /* PRQA S 0303 # JV-01 */
      LpErrAddrReg = &FLSTST_CF_00DEADR;                                                                                /* PRQA S 0303 # JV-01 */
      LpErrClearReg = &FLSTST_CF_DSTCLR;                                                                                /* PRQA S 0303 # JV-01 */
    }
    else if ((FLSTST_CF_GLOBAL_ALL1_END == LusPatternNumber) ||
             (FLSTST_ECC_CF_GLOBAL_END_PATTERN == LusPatternNumber))
    {
      LulCompareData = FLSTST_LONG_WORD_ZERO;
      LucExpectedError = FLSTST_TWO;
    }
    else /* Walking-1 pattern */
    {
      /* No action required */
    }

    /* Update expected error address at the start of each pattern */
    LulEccSaveAddress = (uint32)LpEccTestAddress;                                                                       /* PRQA S 0303 # JV-01 */

    /* Loop through each address in a pattern */
    for (LucLoopCount = FLSTST_ZERO; LucLoopCount < FLSTST_FOUR;
                                                          LucLoopCount++)
    {
      /* Small delay for ECC error and address status update */
      for (LucEccDelayCount = FLSTST_ZERO;
               LucEccDelayCount < FLSTST_ECC_TEST_DELAY; LucEccDelayCount++)
      {
        /* No operation */
        ASM_NOP();                                                                                                      /* PRQA S 1006 # JV-01 */
      }

      if (FLSTST_THREE == LucLoopCount)
      {
        if(FLSTST_ECC_CF_GLOBAL_END_PATTERN == LusPatternNumber)
        {
          LulCompareData = FLSTST_2BIT_ERROR_VALUE;
        }/* else: No action required */
      }/* else: No action required */

      /* Read the data from global ECC self test area */
      LulDataWord = *(LpEccTestAddress);

      /* Check if data from global ECC self test address is same expected value */
      if ((LulDataWord != LulCompareData) ||
          ((uint32)LucExpectedError != *LpErrStatusReg) ||                                                              
          (LulEccSaveAddress != FLSTST_GET_ECC_ERR_ADDR(*LpErrAddrReg)))                                                /* PRQA S 3432 # JV-01 */
      {
        /* Update test result to not ok */
        LenReturnValue = E_NOT_OK;
        /* Enter critical section */
        FLSTST_ENTER_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
        /* Save ECC error status and address */
        FlsTst_GddEccErrorDetail.ucCFGlobalEccStatus = (uint8)(*LpErrStatusReg);
        FlsTst_GddEccErrorDetail.ulCFGlobalEccFaultAddress =
          FLSTST_GET_ECC_ERR_ADDR(*LpErrAddrReg);                                                                       /* PRQA S 3432 # JV-01 */
        /* Exit critical section */
        FLSTST_EXIT_CRITICAL_SECTION(FLSTST_RAM_DATA_PROTECTION);
      }/* else: No action required */

      /* Clear the ECC error flag */
      *LpErrClearReg = (uint32)FLSTST_ONE;

      /* Increase ECC test address */
      LpEccTestAddress++;
    }

    /* Increase the pattern number */
    LusPatternNumber++;
  }

  /* Enable ECC error detection and SEC */
  FLSTST_CFSECCCTL = FLSTST_ECC_SEC_ACTIVATE;                                                                           /* PRQA S 0303 # JV-01 */
  /* Enable ECC notification */
  FLSTST_CF_ERRINT = FLSTST_ECC_ENABLE_NOTIFICATION;                                                                    /* PRQA S 0303 # JV-01 */
  /* Clear ECC status registers */
  FLSTST_CF_SSTCLR = (uint32)FLSTST_ONE;                                                                                /* PRQA S 0303 # JV-01 */
  FLSTST_CF_DSTCLR = (uint32)FLSTST_ONE;                                                                                /* PRQA S 0303 # JV-01 */

  return LenReturnValue;
}
#endif

#define FLSTST_STOP_SEC_PRIVATE_CODE
#include "FlsTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
