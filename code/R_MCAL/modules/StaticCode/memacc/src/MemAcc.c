/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22-11 X2x MCAL Components                                                          */
/* Module       = MemAcc.c                                                                                            */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains API implementations of Memacc Driver Component.                                                 */
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
/*              Devices:        RH850/X2x                                                                             */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header
 * 1.1.0:  30/06/2025:  Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
                        Add message 3384 and 0404, remove 2814, 2824, 2844 to support QA-C version 11.6.0
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024:  Update condition to report DET when length is zero in MemAcc_RequestLock, MemAcc_ReleaseLock. 
 *                      Update flow of MemAcc_Erase, MemAcc_BlankCheck, MemAcc_Write, MemAcc_Read, MemAcc_Compare
 *                      to avoid underflow value when program the end logical address.
 * 0.0.2:  31/10/2024:  Change MEMACC_READ_SID to MEMACC_COMPARE_SID in MemAcc_Compare API
 *                      Update to support macro MEMACC_COMPARE_API
 *                      Update Reference for all APIs
 * 0.0.1:  30/08/2024:  Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for pre-compile options */
#include "MemAcc_PBTypes.h"
/* Included prototypes for APIs */
#include "MemAcc.h"
/* Included for RAM variable declarations */
#include "MemAcc_Ram.h"
/* Included module type definition */
#include "MemAcc_Types.h"
/* Included prototypes internal function */
#include "MemAcc_Control.h"
/* Included Mem driver APIs */
#include "Mem_59_Renesas.h"
/* Included for the declaration of Det_ReportError() */
#if (MEMACC_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MEMACC_C_AR_RELEASE_MAJOR_VERSION    MEMACC_AR_RELEASE_MAJOR_VERSION_VALUE
#define MEMACC_C_AR_RELEASE_MINOR_VERSION    MEMACC_AR_RELEASE_MINOR_VERSION_VALUE
#define MEMACC_C_AR_RELEASE_REVISION_VERSION MEMACC_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MEMACC_C_SW_MAJOR_VERSION            MEMACC_SW_MAJOR_VERSION_VALUE
#define MEMACC_C_SW_MINOR_VERSION            MEMACC_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (MEMACC_AR_RELEASE_MAJOR_VERSION != MEMACC_C_AR_RELEASE_MAJOR_VERSION)
  #error "MemAcc.c : Mismatch in Release Major Version"
#endif

#if (MEMACC_AR_RELEASE_MINOR_VERSION != MEMACC_C_AR_RELEASE_MINOR_VERSION)
  #error "MemAcc.c : Mismatch in Release Minor Version"
#endif

#if (MEMACC_AR_RELEASE_REVISION_VERSION != MEMACC_C_AR_RELEASE_REVISION_VERSION)
  #error "MemAcc.c : Mismatch in Release Revision Version"
#endif

#if (MEMACC_SW_MAJOR_VERSION != MEMACC_C_SW_MAJOR_VERSION)
  #error "MemAcc.c : Mismatch in Software Major Version"
#endif

#if (MEMACC_SW_MINOR_VERSION != MEMACC_C_SW_MINOR_VERSION)
  #error "MemAcc.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : MISRA C:2012 Rule-15.7, CERTCCM MSC01, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used following AUTOSAR standard rule. It is accepted.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
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
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:4643)    : The identifier '%1s' could conflict in the future with the name of a function in '<%2s>'.    */
/* Rule                : CERTCCM DCL37, CWE Rule CWE-398, CWE-569                                                     */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : MISRA C:2012 Rule-11.4, CERTCCM INT36, CWE Rule CWE-398, CWE-569, CWE-738                    */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3673)    : The object addressed by the pointer parameter '%s' is not modified and so the pointer        */
/*                       could be of type 'pointer to const'.                                                         */
/* Rule                : CERTCCM DCL00, DCL13, MISRA C:2012 Rule-8.13                                                 */
/* JV-01 Justification : Pointer variable is used to modify the value at the address so the pointer cannot be         */
/*                       declared as 'pointer to const' type.                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0307)    : [u] Cast between a pointer to object and a pointer to function.                              */
/* Rule                : CERTCCM DCL13, CWE-758, MISRA C:2012 Rule-1.3, Rule-11.1                                     */
/* JV-01 Justification : Pointer variable is used to modify the value at the address so the pointer cannot be         */
/*                       declared as 'pointer to const' type.                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0303)    : Cast between a pointer to volatile object and an integral type.                              */
/* Rule                : MISRA C:2012 Rule-11.4, CERTCCM INT36, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : CERTCCM EXP11, EXP39, MISRA C:2012 Rule-11.3                                                 */
/* JV-01 Justification : For accessing 8-bit and 16-bit PNOT and JPNOT register respectively, the 32-bit pointer is   */
/*                       typecasted.                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:0312)    : Dangerous pointer cast results in loss of volatile qualification.                            */
/* Rule                : CERTCCM EXP32, MISRA C:2012 Rule 11.8                                                        */
/* JV-01 Justification : According to the coding guide, all global variables must have volatile attribute, but        */
/*                       volatile must be removed when return these variables from APIs according to the AUTOSAR      */
/*                       specification.                                                                               */
/*       Verification  : Since these are normal memory objects, any problem doesn't occurs.                           */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : MISRA C:2012 Dir-4.1, CERTCCM MSC07, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define MEMACC_START_SEC_PUBLIC_CODE
#include "MemAcc_MemMap.h"
/***********************************************************************************************************************
** Function Name             : MemAcc_Init
**
** Service ID                : 0x01
**
** Description               : Initialization function - initializes all variables
**                             and sets the module state to initialized.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Non Re-entrant
**
** Input Parameters          : configPtr
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : MemAcc_GenInitStatus, MemAcc_GstAddrAreaData, MemAcc_GstVar, MemAcc_GstLockRequestData, MemAcc_GpAddressAreaConfig
**
** Function(s) invoked       : Det_ReportError
**
** Registers Used            : None
**
** Reference ID              : MEMACC_DUD_ACT_001_ERR008, MEMACC_DUD_ACT_001_ERR002,
** Reference ID              : MEMACC_DUD_ACT_001, MEMACC_DUD_ACT_001_GBL001,
** Reference ID              : MEMACC_DUD_ACT_001_GBL002, MEMACC_DUD_ACT_001_GBL003,
** Reference ID              : MEMACC_DUD_ACT_001_GBL004, MEMACC_DUD_ACT_001_GBL005,
** Reference ID              : MEMACC_DUD_ACT_001_GBL006, MEMACC_DUD_ACT_001_ERR009
***********************************************************************************************************************/
FUNC(void, MEMACC_PUBLIC_CODE) MemAcc_Init(P2CONST(MemAcc_ConfigType, AUTOMATIC, MEMACC_APPL_CONST) configPtr)          /* PRQA S 1503 # JV-01 */
{
  uint16 LusLoopCount;
  /* Pointer to sub area config */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  #if (MEMACC_ALREADY_INIT_DET_CHECK == STD_ON)
  if (MEMACC_UNINIT != MemAcc_GenInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_INIT_SID, MEMACC_E_ALREADY_INITIALIZED);
  }
  else
  #endif /* #if (MEMACC_ALREADY_INIT_DET_CHECK == STD_ON) */
  if (NULL_PTR == configPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_INIT_SID, MEMACC_E_PARAM_POINTER);
  }
  else if (MEMACC_DBTOC_VALUE != (configPtr->ulStartOfDbToc))
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_INIT_SID, MEMACC_E_INVALID_DATABASE);
  }
  else
  #endif /* #if (MEMACC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get post-build configuration pointer */
    MemAcc_GpConfigPtr = configPtr;
    /* Get address area configuration pointer */
    MemAcc_GpAddressAreaConfig = MemAcc_GpConfigPtr->pAddrAreaConfig;                                                   
    /* Initialize Lock Request variable */
    MemAcc_GstLockRequestData.ulNumOfLockInstance = (uint32)MEMACC_ZERO;
    MemAcc_GstLockRequestData.pLockNotificationFctPtr = NULL_PTR;

    /* Initialize instance data */
    for (LusLoopCount = (uint16)MEMACC_ZERO; MEMACC_NUM_OF_MEM_INSTANCE > LusLoopCount; LusLoopCount++)                 /* PRQA S 2877 # JV-01 */
    {
      MemAcc_GstVar[LusLoopCount].blSuspendedFlag = MEMACC_FALSE;
      MemAcc_GstVar[LusLoopCount].usProcessingAreaId = (uint16)MEMACC_ZERO;
      MemAcc_GstVar[LusLoopCount].usSuspendedAreaId = (uint16)MEMACC_ZERO;

      if (MEMACC_INDIRECT_DYNAMIC == MemAcc_GpConfigPtr->pInstInvocation[LusLoopCount])                                 
      {
        MemAcc_GstVar[LusLoopCount].enInstanceStatus = MEMACC_INSTANCE_UNINIT;
        MemAcc_GstVar[LusLoopCount].pMemBinary = NULL_PTR;
      }
      else if (MEMACC_DIRECT_STATIC == MemAcc_GpConfigPtr->pInstInvocation[LusLoopCount])                               /* PRQA S 2004 # JV-01 */
      {
        MemAcc_GstVar[LusLoopCount].enInstanceStatus = MEMACC_INSTANCE_IDLE;
      }

      MemAcc_GstVar[LusLoopCount].blLockRequest = MEMACC_FALSE;
      MemAcc_GstVar[LusLoopCount].blLockState = MEMACC_FALSE;
    }

    /* Initialize area data */
    for (LusLoopCount = MEMACC_ZERO; MEMACC_MAX_ADDRESS_AREA_ID >= LusLoopCount; LusLoopCount++)                        /* PRQA S 2877 # JV-01 */
    {
      /* Get first sub-area of area */
      LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[LusLoopCount].pSubAreaConfig[(uint16)MEMACC_ZERO];                  
      MemAcc_GstAddrAreaData[LusLoopCount].blWaitingMemResult = MEMACC_FALSE;
      MemAcc_GstAddrAreaData[LusLoopCount].blCancelRequest = MEMACC_FALSE;
      MemAcc_GstAddrAreaData[LusLoopCount].ucRetryTimes = (uint8)MEMACC_ZERO;
      MemAcc_GstAddrAreaData[LusLoopCount].usCurrentSubAreaIdx = (uint16)MEMACC_ZERO;
      MemAcc_GstAddrAreaData[LusLoopCount].enCommand = MEMACC_NO_JOB;
      MemAcc_GstAddrAreaData[LusLoopCount].ddMemRequestedLength = (MemAcc_LengthType)MEMACC_ZERO;
      MemAcc_GstAddrAreaData[LusLoopCount].ddProcessedLength = (MemAcc_LengthType)MEMACC_ZERO;
      MemAcc_GstAddrAreaData[LusLoopCount].enJobResult = MEMACC_MEM_OK;
      MemAcc_GstAddrAreaData[LusLoopCount].enMemJobResult = MEM_59_RENESAS_JOB_OK;
      MemAcc_GstAddrAreaData[LusLoopCount].enJobStatus = MEMACC_JOB_IDLE;
      MemAcc_GstAddrAreaData[LusLoopCount].ddCurrentAddress = LpSubAreaConfig->ddLogicStartAddr;                        
      MemAcc_GstAddrAreaData[LusLoopCount].ddRemainingLength = (MemAcc_LengthType)MEMACC_ZERO;
      MemAcc_GstAddrAreaData[LusLoopCount].pBufferAddress = NULL_PTR;
      MemAcc_GstAddrAreaData[LusLoopCount].pReadOnlyBufferAddr = NULL_PTR;
    }
    
    /* Set module status to initialized */
    MemAcc_GenInitStatus = MEMACC_INIT;
    
  }
} /* End of API MemAcc_Init */

/***********************************************************************************************************************
** Function Name             : MemAcc_DeInit
**
** Service ID                : 0x13
**
** Description               : Deinitialize module.
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
** Return parameter          : None
**
** Preconditions             : Component must be initialized using MemAcc_Init().
**
** Global Variables Used     : MemAcc_GenInitStatus, MemAcc_GstAddrAreaData[], 
**
** Function(s) invoked       : Det_ReportError
**
** Registers Used            : None
**
** Reference ID             : MEMACC_DUD_ACT_002, MEMACC_DUD_ACT_002_ERR001, MEMACC_DUD_ACT_002_GBL001
** Reference ID             : MEMACC_DUD_ACT_002_GBL002, MEMACC_DUD_ACT_002_GBL003, MEMACC_DUD_ACT_002_GBL004
***********************************************************************************************************************/
FUNC(void, MEMACC_PUBLIC_CODE) MemAcc_DeInit(void)                                                                      /* PRQA S 1503 # JV-01 */
{
  uint16 LusLoopCount;

  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_DEINIT_SID, MEMACC_E_UNINIT);
  }
  else
  #endif /* #if (MEMACC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Set module status to uninitialized */
    MemAcc_GenInitStatus = MEMACC_UNINIT;
    
    /* Terminate pending jobs */
    for (LusLoopCount = (uint16)MEMACC_ZERO; MEMACC_MAX_ADDRESS_AREA_ID >= LusLoopCount; LusLoopCount++)                /* PRQA S 2877 # JV-01 */
    {
      /* if this job is pending */
      if (MEMACC_JOB_IDLE != MemAcc_GstAddrAreaData[LusLoopCount].enJobStatus)
      {
        /* Reset job status and command */
        MemAcc_GstAddrAreaData[LusLoopCount].enJobStatus = MEMACC_JOB_IDLE;
        MemAcc_GstAddrAreaData[LusLoopCount].enCommand = MEMACC_NO_JOB;
      }
    }
  }
} /* End of API MemAcc_DeInit */

/***********************************************************************************************************************
** Function Name        : MemAcc_GetProcessedLength
**
** Service ID           : 0x07
**
** Description          : This API service shall return the accumulated number of bytes that
**                        have already been processed in the current job.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : addressAreaId
**
** InOut Parameters     : None
**
** Output Parameters    : None
**
** Return Parameter     : MemAcc_LengthType
**
** Preconditions        : The MEMACC Driver must be Initialized first by invoking
**                        API MemAcc_Init().
**
** Global Variables     : MemAcc_GenProcessedLength(R), MemAcc_GstAddrAreaData[]
**
** Functions invoked    : Det_ReportError
**
** Registers Used       : None
**
** Reference ID         : MEMACC_DUD_ACT_007, MEMACC_DUD_ACT_007_ERR001
** Reference ID         : MEMACC_DUD_ACT_007_ERR003, MEMACC_DUD_ACT_007_GBL001, MEMACC_DUD_ACT_007_GBL002
***********************************************************************************************************************/
FUNC(MemAcc_LengthType, MEMACC_PUBLIC_CODE) MemAcc_GetProcessedLength(MemAcc_AddressType addressAreaId)                 /* PRQA S 1503 # JV-01 */
{
  /* Local variable to hold the driver status */
  MemAcc_LengthType LddReturnValue;

  /* Check if the module is initialized */
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    /* Initialize return value */
  LddReturnValue = (MemAcc_LengthType)MEMACC_ZERO;
  
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_PROCESSED_LENGHT_SID, MEMACC_E_UNINIT);
  }
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_PROCESSED_LENGHT_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
  }
  else
  #endif /* #if (MEMACC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get processed length */
    LddReturnValue = MemAcc_GstAddrAreaData[addressAreaId].ddProcessedLength;                                           
  }
  /* return the current state of the driver */
  return (LddReturnValue);
} /* End of API MemAcc_GetProcessedLength */

/***********************************************************************************************************************
** Function Name            : MemAcc_GetVersionInfo
**
** Service ID               : 0x02
**
** Description              : Service to return the version information of the MemAcc module
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : versionInfoPtr - Pointer to where to store the
**                            version information of this module.
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : None
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_003, MEMACC_DUD_ACT_003_ERR002
***********************************************************************************************************************/
FUNC(void, MEMACC_PUBLIC_CODE) MemAcc_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,                              /* PRQA S 3432, 1503 # JV-01, JV-01 */
MEMACC_APPL_DATA) versionInfoPtr)
{
  /* Check if parameter passed is equal to Null pointer */
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == versionInfoPtr)
  {
    /* Report to DET  */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_VERSION_INFO_SID, MEMACC_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* Copy the vendor Id */
    versionInfoPtr->vendorID = (uint16)MEMACC_VENDOR_ID;                                                                
    /* Copy the module Id */
    versionInfoPtr->moduleID = (uint16)MEMACC_MODULE_ID;
    /* Copy Software Major Version */
    versionInfoPtr->sw_major_version = MEMACC_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versionInfoPtr->sw_minor_version = MEMACC_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versionInfoPtr->sw_patch_version = MEMACC_SW_PATCH_VERSION;
  }
  return;
} /* End of API MemAcc_GetVersionInfo */

/***********************************************************************************************************************
** Function Name             : MemAcc_GetJobResult
**
** Service ID                : 0x05
**
** Description               : Returns the consolidated job result of the address
**                             area referenced by addressAreaId.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Reentrant
**
** Input Parameters          : addressAreaId
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemAcc_JobResultType
**
** Preconditions             : Component must be initialized using MemAcc_Init().
**
** Global Variables Used     : MemAcc_GenInitStatus, MemAcc_GstAddrAreaData[]
**
** Function(s) invoked       : Det_ReportError
**
** Registers Used            : None
**
** Reference ID              : MEMACC_DUD_ACT_004_ERR001, MEMACC_DUD_ACT_004_ERR003
** Reference ID              : MEMACC_DUD_ACT_004, MEMACC_DUD_ACT_004_GBL001, MEMACC_DUD_ACT_004_GBL002
***********************************************************************************************************************/
FUNC(MemAcc_JobResultType, MEMACC_PUBLIC_CODE) MemAcc_GetJobResult(MemAcc_AddressAreaIdType addressAreaId)              /* PRQA S 1503 # JV-01 */
{
  MemAcc_JobResultType LenReturnValue;
  
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_JOB_RESULT_SID, MEMACC_E_UNINIT);
    /* Set return value to failed to due error */
    LenReturnValue = MEMACC_MEM_FAILED;
  }
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_JOB_RESULT_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
    /* Set return value to failed to due error */
    LenReturnValue = MEMACC_MEM_FAILED;
  }
  else
  #endif /* #if (MEMACC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get job result */
    LenReturnValue = MemAcc_GstAddrAreaData[addressAreaId].enJobResult;                                                 
  }
  
  return LenReturnValue;
} /* End of API MemAcc_GetJobResult */

/***********************************************************************************************************************
** Function Name             : MemAcc_GetJobStatus
**
** Service ID                : 0x10
**
** Description               : Returns the status of the MemAcc job referenced by addressAreaId.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Reentrant
**
** Input Parameters          : addressAreaId
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : MemAcc_JobStatusType
**
** Preconditions             : Component must be initialized using MemAcc_Init().
**
** Global Variables Used     : MemAcc_GstAddrAreaData[], MemAcc_GenInitStatus
**
** Function(s) invoked       : Det_ReportError
**
** Registers Used            : None
**
** Reference ID             : MEMACC_DUD_ACT_005_ERR001, MEMACC_DUD_ACT_005_ERR003
** Reference ID             : MEMACC_DUD_ACT_005, MEMACC_DUD_ACT_005_GBL001, MEMACC_DUD_ACT_005_GBL002
***********************************************************************************************************************/
FUNC(MemAcc_JobStatusType, MEMACC_PUBLIC_CODE) MemAcc_GetJobStatus(MemAcc_AddressAreaIdType addressAreaId)              /* PRQA S 1503 # JV-01 */
{
  MemAcc_JobStatusType LenReturnValue;
  
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Initialize return value */
  LenReturnValue = MEMACC_JOB_IDLE;

  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_JOB_STATUS_SID, MEMACC_E_UNINIT);
  }
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_JOB_STATUS_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
  }
  else
  #endif /* #if (MEMACC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get job status */
    LenReturnValue = MemAcc_GstAddrAreaData[addressAreaId].enJobStatus;                                                 
  }
  
  return LenReturnValue;
} /* End of API MemAcc_GetJobStatus */

/***********************************************************************************************************************
** Function Name             : MemAcc_GetMemoryInfo
**
** Service ID                : 0x06
**
** Description               : This service function retrieves the physical memory
**                             device information of a specific address area.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Reentrant
**
** Input Parameters          : addressAreaId, address
**
** InOut Parameters          : None
**
** Output Parameters         : memoryInfoPtr
**
** Return parameter          : Std_ReturnType
**
** Preconditions             : Component must be initialized using MemAcc_Init().
**
** Global Variables Used     : MemAcc_GpAddressAreaConfig, MemAcc_GenInitStatus
**
** Function(s) invoked       : Det_ReportError
**
** Registers Used            : None
**
** Reference ID              : MEMACC_DUD_ACT_006, MEMACC_DUD_ACT_006_ERR001
** Reference ID              : MEMACC_DUD_ACT_006_ERR002, MEMACC_DUD_ACT_006_ERR003
** Reference ID              : MEMACC_DUD_ACT_006_ERR004, MEMACC_DUD_ACT_006_GBL001, MEMACC_DUD_ACT_006_GBL002
***********************************************************************************************************************/
FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_GetMemoryInfo (                                                         /* PRQA S 1503 # JV-01 */
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType address,
  P2VAR(MemAcc_MemoryInfoType, AUTOMATIC, MEMACC_APPL_DATA) memoryInfoPtr)                                              /* PRQA S 3432, 4643 # JV-01, JV-01 */
{
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to check if address is valid */
  boolean LblAddrValid;
  #endif
  /* Local variable to hold the DET return value */
  Std_ReturnType LenReturnValue;
  /* Local variable to hold loop count */
  uint16 LusSubAreaIdx;
  /* Pointer to sub area config */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  /* Initialize return value */
  LenReturnValue = E_OK;

  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_MEMORY_INFO_SID, MEMACC_E_UNINIT);
    /* Set return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_MEMORY_INFO_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
    /* Set return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  else if (NULL_PTR == memoryInfoPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_MEMORY_INFO_SID, MEMACC_E_PARAM_POINTER);
    /* Set return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  else
  #endif /* #if (MEMACC_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    LblAddrValid = MEMACC_FALSE;
    #endif

    for (LusSubAreaIdx = MEMACC_ZERO;
      #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
      (MEMACC_FALSE == LblAddrValid) &&
      #endif
      (LusSubAreaIdx < MemAcc_GpAddressAreaConfig[addressAreaId].usNumOfSubArea); LusSubAreaIdx++)                      
    {
      LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].pSubAreaConfig[LusSubAreaIdx];

      /* Check if sourceAddress is inside this sub-area */
      if ((address >= LpSubAreaConfig->ddLogicStartAddr) &&                                                             
          (address < (LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength)))                           /* PRQA S 3383 # JV-01 */
      {
        /* Set area info */
        memoryInfoPtr->LogicalStartAddress = LpSubAreaConfig->ddLogicStartAddr;                                         
        memoryInfoPtr->PhysicalStartAddress = LpSubAreaConfig->ddPhysicalStartAddr;
        memoryInfoPtr->MaxOffset = LpSubAreaConfig->ddSubAreaLength - (MemAcc_LengthType)MEMACC_ONE;                    /* PRQA S 3383 # JV-01 */ 
        memoryInfoPtr->EraseSectorSize = LpSubAreaConfig->ulMemEraseSectorSize;
        memoryInfoPtr->EraseSectorBurstSize = LpSubAreaConfig->ulMemEraseBurstSize;
        memoryInfoPtr->ReadPageSize = LpSubAreaConfig->ulMemReadPageSize;
        memoryInfoPtr->WritePageSize = LpSubAreaConfig->ulMemWritePageSize;
        memoryInfoPtr->ReadPageBurstSize = LpSubAreaConfig->ulMemReadBurstSize;
        memoryInfoPtr->WritePageBurstSize = LpSubAreaConfig->ulMemWriteBurstSize;
        memoryInfoPtr->HwId = LpSubAreaConfig->ulInstanceId;

        #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
        /* Set value for local variable */
        LblAddrValid = MEMACC_TRUE;
        #endif
      }
    }

    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    if (MEMACC_FALSE == LblAddrValid)
    {
      /* Report to DET if sourceAddress or length is invalid */
      (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_MEMORY_INFO_SID, MEMACC_E_PARAM_ADDRESS_LENGTH);
      /* Reset return value to E_NOT_OK due to failure */
      LenReturnValue = E_NOT_OK;
    }
    #endif
  }
  
  return LenReturnValue;
} /* End of API MemAcc_GetJobStatus */

/***********************************************************************************************************************
** Function Name             : MemAcc_GetJobInfo
**
** Service ID                : 0x08
**
** Description               : This service function returns detailed information
**                             about the current memory job.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Reentrant
**
** Input Parameters          : addressAreaId
**
** InOut Parameters          : None
**
** Output Parameters         : jobInfoPtr
**
** Return parameter          : None
**
** Preconditions             : Component must be initialized using MemAcc_Init().
**
** Global Variables Used     : MemAcc_GpAddressAreaConfig[], MemAcc_GenInitStatus
**
** Function(s) invoked       : Det_ReportError
**
** Registers Used            : None
**
** Reference ID              : MEMACC_DUD_ACT_008_ERR001, MEMACC_DUD_ACT_008_ERR002
** Reference ID              : MEMACC_DUD_ACT_008_ERR003, MEMACC_DUD_ACT_008, MEMACC_DUD_ACT_008_GBL001
** Reference ID              : MEMACC_DUD_ACT_008_GBL002, MEMACC_DUD_ACT_008_GBL003
***********************************************************************************************************************/
FUNC(void, MEMACC_PUBLIC_CODE) MemAcc_GetJobInfo (                                                                      /* PRQA S 1503 # JV-01 */
  MemAcc_AddressAreaIdType addressAreaId,
  P2VAR(MemAcc_JobInfoType, AUTOMATIC, MEMACC_APPL_DATA) jobInfoPtr)                                                    /* PRQA S 3432 # JV-01 */
{
  /* Pointer to sub area config */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_JOB_INFO_SID, MEMACC_E_UNINIT);
  }
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_JOB_INFO_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
  }
  else if (NULL_PTR == jobInfoPtr)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_GET_JOB_INFO_SID, MEMACC_E_PARAM_POINTER);
  }
  else
  #endif /* #if (MEMACC_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get sub-area config of currently active request */
    LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].                                                       
            pSubAreaConfig[MemAcc_GstAddrAreaData[addressAreaId].usCurrentSubAreaIdx];                                  
    /* Get job info */
    jobInfoPtr->LogicalAddress = MemAcc_GstAddrAreaData[addressAreaId].ddCurrentAddress;                                
    jobInfoPtr->Length = MemAcc_GstAddrAreaData[addressAreaId].ddRemainingLength;
    jobInfoPtr->HwId = LpSubAreaConfig->enHwType;                                                                       
    jobInfoPtr->MemInstanceId = LpSubAreaConfig->ulInstanceId;
    jobInfoPtr->MemAddress = (MemAcc_GstAddrAreaData[addressAreaId].ddCurrentAddress -                                  /* PRQA S 3383 # JV-01 */
      LpSubAreaConfig->ddLogicStartAddr) + LpSubAreaConfig->ddPhysicalStartAddr;                                        /* PRQA S 3383 # JV-01 */
    jobInfoPtr->MemLength = MemAcc_GstAddrAreaData[addressAreaId].ddMemRequestedLength;
    jobInfoPtr->CurrentJob = MemAcc_GstAddrAreaData[addressAreaId].enCommand;
    jobInfoPtr->MemResult = MemAcc_GstAddrAreaData[addressAreaId].enMemJobResult;
  }
} /* End of API MemAcc_GetJobStatus */

/***********************************************************************************************************************
** Function Name            : MemAcc_MainFunction
**
** Service ID               : 0x03
**
** Description              : Service to handle the requested jobs and
**                            the internal management operations.
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
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : MemAcc_GenInitStatus, MemAcc_GpAddressAreaConfig[], MemAcc_GstAddrAreaData,
**                            MemAcc_GstVar, MemAcc_GstLockRequestData
**
** Function(s) invoked      : MemAcc_ProcessJobResult, MemAcc_ProcessBlankCheckJob, MemAcc_ProcessWriteJob,
**                            MemAcc_ProcessEraseJob, MemAcc_ProcessReadJob, MemAcc_ProcessHwSpecificJob
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_019, MEMACC_DUD_ACT_019_GBL001, MEMACC_DUD_ACT_019_GBL002
** Reference ID             : MEMACC_DUD_ACT_019_GBL003, MEMACC_DUD_ACT_019_GBL004, MEMACC_DUD_ACT_019_GBL005
** Reference ID             : MEMACC_DUD_ACT_019_GBL006, MEMACC_DUD_ACT_019_GBL007, MEMACC_DUD_ACT_019_GBL008
** Reference ID             : MEMACC_DUD_ACT_019_GBL009, MEMACC_DUD_ACT_019_GBL010, MEMACC_DUD_ACT_019_GBL011
** Reference ID             : MEMACC_DUD_ACT_019_GBL012
***********************************************************************************************************************/
FUNC(void, MEMACC_PUBLIC_CODE) MemAcc_MainFunction(void)                                                                /* PRQA S 1503 # JV-01 */
{
  uint16 LusAreaId;
  Mem_59_Renesas_InstanceIdType LulInstanceIdx;

  /* Check if module has been intialized */
  if (MEMACC_INIT == MemAcc_GenInitStatus)
  {
    /* Check cancel request */
    MemAcc_CheckCancelRequest();

    /* Loop through all instance */
    for (LulInstanceIdx = (uint32)MEMACC_ZERO; LulInstanceIdx < (uint32)MEMACC_NUM_OF_MEM_INSTANCE; LulInstanceIdx++)   /* PRQA S 2877 # JV-01 */
    {
      if (MEMACC_FALSE == MemAcc_GstVar[LulInstanceIdx].blLockState)
      {
        if (MEMACC_FALSE == MemAcc_GstVar[LulInstanceIdx].blLockRequest)
        {
          /* Determine which area id will be processed */
          MemAcc_SelectAreaToProcess(LulInstanceIdx);
        }
        else
        {
          if (MEMACC_INSTANCE_IDLE == MemAcc_GstVar[LulInstanceIdx].enInstanceStatus)
          {
            /* Set lock state */
            MemAcc_GstVar[LulInstanceIdx].blLockState = MEMACC_TRUE;
            /* Decrease number of instance to be locked */
            MemAcc_GstLockRequestData.ulNumOfLockInstance--;                                                            /* PRQA S 3383 # JV-01 */

            /* Call lock request notification if all instances are locked */
            if (MEMACC_ZERO == MemAcc_GstLockRequestData.ulNumOfLockInstance)
            {
              MemAcc_GstLockRequestData.pLockNotificationFctPtr();                                                      
            }
          }
        }

        /* Process pending job */
        if (MEMACC_INSTANCE_BUSY == MemAcc_GstVar[LulInstanceIdx].enInstanceStatus)
        {
          /* Get processing area id */
          LusAreaId = MemAcc_GstVar[LulInstanceIdx].usProcessingAreaId;

          if (MEMACC_FALSE == MemAcc_GstAddrAreaData[LusAreaId].blWaitingMemResult)                                     
          {
            /* Check which job is pending */
            switch (MemAcc_GstAddrAreaData[LusAreaId].enCommand)
            {
            case MEMACC_READ_JOB:
            #if (MEMACC_COMPARE_API == STD_ON)
            case MEMACC_COMPARE_JOB:
            #endif /* #if (MEMACC_COMPARE_API == STD_ON) */
              MemAcc_ProcessReadJob(LulInstanceIdx);
              break;
            case MEMACC_ERASE_JOB:
              MemAcc_ProcessEraseJob(LulInstanceIdx);
              break;
            case MEMACC_WRITE_JOB:
              MemAcc_ProcessWriteJob(LulInstanceIdx);
              break;
            case MEMACC_BLANKCHECK_JOB:
              MemAcc_ProcessBlankCheckJob(LulInstanceIdx);
              break;
            case MEMACC_MEMHWSPECIFIC_JOB:
              MemAcc_ProcessHwSpecificJob(LulInstanceIdx);
              break;

            default: /* MEMACC_NO_JOB */
              break;
            }
          }

          /* Invoke Mem driver schedule function */
          if ((MEMACC_INDIRECT_DYNAMIC == MemAcc_GpConfigPtr->pInstInvocation[LulInstanceIdx]) &&                       
          (MemAcc_GstVar[LulInstanceIdx].pMemBinary != NULL_PTR))
          {
            (*(MemAcc_GstVar[LulInstanceIdx].pMemBinary->MainFunc))();                                                  /* PRQA S 0404 # JV-01 */
          }

          /* Job result processing */
          if (MEMACC_TRUE == MemAcc_GstAddrAreaData[LusAreaId].blWaitingMemResult)                                      
          {
            MemAcc_ProcessJobResult(LulInstanceIdx);
          }
        } /* end of if (MEMACC_INSTANCE_BUSY == MemAcc_GstVar[LulInstanceIdx].enInstanceStatus) */
      } /* end of if (MEMACC_FALSE == MemAcc_GstVar[LpSubAreaConfig->ulInstanceId].blLockState) */
    } /* end of for (LulInstanceIdx = MEMACC_ZERO; LulInstanceIdx < MEMACC_NUM_OF_MEM_INSTANCE; LulInstanceIdx++) */
  } /* else No action required */
} /* End of API MemAcc_MainFunction */       

/***********************************************************************************************************************
** Function Name            : MemAcc_Read
**
** Service ID               : 0x09
**
** Description              : This API performs the reading of the flash memory
**                            The data from flash memory (source address) is
**                            read to the data buffer (Target address) of the
**                            application.
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : addressAreaId, sourceAddress, length
**
** InOut Parameters         : None
**
** Output Parameters        : destinationDataPtr
**
** Return parameter         : Std_ReturnType
**                            E_OK: if Read command has been accepted.
**                            E_NOT_OK: if Read command has not been accepted.
**                            E_MEM_SERVICE_NOT_AVAIL: The underlying Mem driver
**                            service function is not available
**
** Preconditions            : Component must be initialized using MemAcc_Init().
**
** Global Variables Used    : MemAcc_GstVar.pTempBufferAddress(W),
**                            MemAcc_GstVar.ulReadAddress(W),
**                            MemAcc_GstVar.pBufferAddress(W),
**                            MemAcc_GstVar.ulRequestedLength(W),
**                            MemAcc_GstVar.ulCurrentLength(W),
**                            MemAcc_GstVar.enGenCommand(W), MemAcc_GenState(W),
**                            MemAcc_GenJobResult(W),MemAcc_GstVar.ucOffset(R/W),
**                            MemAcc_GstVar.enFlashStatus(W)
**                            MemAcc_GstVar.blBCCmdNotFirstStartFlg(W),
**                            MemAcc_GaaTempBuffer(W)
**
** Function(s) invoked      : Det_ReportError,MemAcc_DetErrorCheckAndSwitchBusy,
**                            MemAcc_GetIntReq,MemAcc_ClearIntReq,MemAcc_SetStatus
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_012, MEMACC_DUD_ACT_012_ERR001
** Reference ID             : MEMACC_DUD_ACT_012_ERR002, MEMACC_DUD_ACT_012_ERR003
** Reference ID             : MEMACC_DUD_ACT_012_ERR004, MEMACC_DUD_ACT_012_ERR006, MEMACC_DUD_ACT_012_GBL001
** Reference ID             : MEMACC_DUD_ACT_012_GBL002, MEMACC_DUD_ACT_012_GBL003, MEMACC_DUD_ACT_012_GBL004
** Reference ID             : MEMACC_DUD_ACT_012_GBL005, MEMACC_DUD_ACT_012_GBL006, MEMACC_DUD_ACT_012_GBL007
** Reference ID             : MEMACC_DUD_ACT_012_GBL008, MEMACC_DUD_ACT_012_GBL009, MEMACC_DUD_ACT_012_GBL010
***********************************************************************************************************************/
FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_Read(                                                                   /* PRQA S 1503 # JV-01 */
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType sourceAddress,
  P2VAR(MemAcc_DataType, AUTOMATIC, MEMACC_APPL_DATA) destinationDataPtr,                                               /* PRQA S 3432 # JV-01 */
  MemAcc_LengthType length)
{
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to check if address and length is valid */
  boolean LblAddrValid, LblLengthValid;
  #endif
  /* Local variable to hold the DET return value */
  Std_ReturnType LenReturnValue;
  /* Local variable to hold loop count */
  uint16 LusSubAreaIdx;
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold align check value */
  uint32 LulCheckAlign;
  /* Local varriable to hold end logical address */
  MemAcc_AddressType LddEndLogicAddr;
  #endif
  /* Pointer to sub area config */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  /* Initialize return value */
  LenReturnValue = E_OK;
  
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_READ_SID, MEMACC_E_UNINIT);
    /* Reset return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if addressAreaId is valid */
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_READ_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
    /* Set return value to failed to due error */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if destinationDataPtr is NULL_PTR or not align with buffer alignment value */
  else if ((NULL_PTR == destinationDataPtr) ||
    ((((uint32)destinationDataPtr) & ((uint32)MemAcc_GpAddressAreaConfig[addressAreaId].                                /* PRQA S 0306 # JV-01 */
      ucBufferAlignValue - (uint32)MEMACC_ONE)) != MEMACC_ZERO))                                                        /* PRQA S 3384 # JV-01 */
  {
   /* Report error to DET */
   (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_READ_SID, MEMACC_E_PARAM_POINTER);
   /* Reset return value to E_NOT_OK due to failure */
   LenReturnValue = E_NOT_OK;
  }
  /* Check if the job for addressAreaId is pending */
  else if (MEMACC_JOB_PENDING == MemAcc_GstAddrAreaData[addressAreaId].enJobStatus)                                     /* PRQA S 2004 # JV-01 */
  {
    /* Report to DET if the driver is currently busy */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_READ_SID, MEMACC_E_BUSY);
    /* Reset return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  /* Check whether any error is reported to DET */
  if (E_OK == LenReturnValue)
  #endif /* #if (MEMACC_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    LblAddrValid = MEMACC_FALSE;
    LblLengthValid = MEMACC_FALSE;
    #endif

    for (LusSubAreaIdx = MEMACC_ZERO;
      #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
      ((MEMACC_FALSE == LblAddrValid) || (MEMACC_FALSE == LblLengthValid)) &&
      #endif
      (LusSubAreaIdx < MemAcc_GpAddressAreaConfig[addressAreaId].usNumOfSubArea); LusSubAreaIdx++)                      
    {
      LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].pSubAreaConfig[LusSubAreaIdx];

      /* Check if sourceAddress is inside this sub-area */
      if ((sourceAddress >= LpSubAreaConfig->ddLogicStartAddr) &&                                                       
          (sourceAddress < (LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength)))                     /* PRQA S 3383 # JV-01 */
      {
        /* Store sub-area index */
        MemAcc_GstAddrAreaData[addressAreaId].usCurrentSubAreaIdx = LusSubAreaIdx;                                      

        #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
        /* Calculate alignment check value */
        LulCheckAlign = LpSubAreaConfig->ulMemReadPageSize - (uint32)MEMACC_ONE;                                        /* PRQA S 3383 # JV-01 */
        
        /* Check address alignment */
        if (MEMACC_ZERO == (sourceAddress & LulCheckAlign))
        {
          LblAddrValid = MEMACC_TRUE;
        }
        #else
        /* break this loop since sub-area was found */
        break;
        #endif
      }

      #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
      if (MEMACC_ZERO != length)
      {
        /* Calculate end address */
        LddEndLogicAddr = sourceAddress + length - (MemAcc_AddressType)MEMACC_ONE;                                      /* PRQA S 3383, 3384 # JV-01, JV-01 */
        /* Check if end address is inside this sub-area */
        if ((LddEndLogicAddr >= LpSubAreaConfig->ddLogicStartAddr) &&
            (LddEndLogicAddr < (LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength)))                 /* PRQA S 3383 # JV-01 */
        {
          /* Calculate alignment check value */
          LulCheckAlign = LpSubAreaConfig->ulMemReadPageSize - (uint32)MEMACC_ONE;                                      /* PRQA S 3383 # JV-01 */

          /* Check address alignment */
          if (MEMACC_ZERO == ((LddEndLogicAddr + (MemAcc_AddressType)MEMACC_ONE) & LulCheckAlign))
          {
            LblLengthValid = MEMACC_TRUE;
          }
        }
      }
      #endif
    }

    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    if ((MEMACC_FALSE == LblAddrValid) || (MEMACC_FALSE == LblLengthValid))
    {
      /* Report to DET if sourceAddress or length is invalid */
      (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_READ_SID, MEMACC_E_PARAM_ADDRESS_LENGTH);
      /* Reset return value to E_NOT_OK due to failure */
      LenReturnValue = E_NOT_OK;
    }
    #endif
  }

  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Check whether any error is reported to DET */
  if (E_OK == LenReturnValue)
  #endif
  {
    /* Set job status to pending */
    MemAcc_GstAddrAreaData[addressAreaId].enJobStatus = MEMACC_JOB_PENDING;                                             
    /* Set request address */
    MemAcc_GstAddrAreaData[addressAreaId].ddCurrentAddress = sourceAddress;                                             
    /* Set request length */
    MemAcc_GstAddrAreaData[addressAreaId].ddRemainingLength = length;                                                   
    /* Set upper layer buffer */
    MemAcc_GstAddrAreaData[addressAreaId].pBufferAddress = destinationDataPtr;                                          
    /* Set processed length = 0 */
    MemAcc_GstAddrAreaData[addressAreaId].ddProcessedLength = MEMACC_ZERO;                                              
    /* Set command = read */
    MemAcc_GstAddrAreaData[addressAreaId].enCommand = MEMACC_READ_JOB;                                                  
    /* Set requested Length */
    MemAcc_GstAddrAreaData[addressAreaId].ddMemRequestedLength = MEMACC_ZERO;                                           
  } /* else No action required */

  return (LenReturnValue);
} /* End of API MemAcc_Read */

/***********************************************************************************************************************
** Function Name            : MemAcc_Erase
**
** Service ID               : 0x0B
**
** Description              : This API triggers an erase job of the given area.
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : addressAreaId, targetAddress, length
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : Std_ReturnType
**                            E_OK: if Erase command has been accepted.
**                            E_NOT_OK: if Erase command has not been accepted.
**                            E_MEM_SERVICE_NOT_AVAIL: The underlying Mem driver
**                            service function is not available
**
** Preconditions            : Component must be initialized using MemAcc_Init().
**
** Global Variables Used    : MemAcc_GenInitStatus, MemAcc_GstAddrAreaData[], MemAcc_GpAddressAreaConfig
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_014_ERR001, MEMACC_DUD_ACT_014_ERR003
** Reference ID             : MEMACC_DUD_ACT_014_ERR004, MEMACC_DUD_ACT_014_ERR006
** Reference ID             : MEMACC_DUD_ACT_014, MEMACC_DUD_ACT_014_GBL001, MEMACC_DUD_ACT_014_GBL002
** Reference ID             : MEMACC_DUD_ACT_014_GBL003, MEMACC_DUD_ACT_014_GBL004, MEMACC_DUD_ACT_014_GBL005
** Reference ID             : MEMACC_DUD_ACT_014_GBL006, MEMACC_DUD_ACT_014_GBL007, MEMACC_DUD_ACT_014_GBL008
** Reference ID             : MEMACC_DUD_ACT_014_GBL009, MEMACC_DUD_ACT_014_GBL010
***********************************************************************************************************************/
FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_Erase (                                                                 /* PRQA S 1503 # JV-01 */
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType targetAddress,
  MemAcc_LengthType length)
{
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to check if address and length is valid */
  boolean LblAddrValid, LblLengthValid;
  #endif
  /* Local variable to hold the DET return value */
  Std_ReturnType LenReturnValue;
  /* Local variable to hold loop count */
  uint16 LusSubAreaIdx;
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold align check value */
  uint32 LulCheckAlign;
  /* Local varriable to hold end logical address */
  MemAcc_AddressType LddEndLogicAddr;
  #endif
  /* Pointer to sub area config */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  /* Initialize return value */
  LenReturnValue = E_OK;
  
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_ERASE_SID, MEMACC_E_UNINIT);
    /* Reset return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if addressAreaId is valid */
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_ERASE_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
    /* Set return value to failed to due error */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if the job for addressAreaId is pending */
  else if (MEMACC_JOB_PENDING == MemAcc_GstAddrAreaData[addressAreaId].enJobStatus)                                     /* PRQA S 2004 # JV-01 */
  {
    /* Report to DET if the driver is currently busy */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_ERASE_SID, MEMACC_E_BUSY);
    /* Reset return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  /* Check whether any error is reported to DET */
  if (E_OK == LenReturnValue)
  #endif /* #if (MEMACC_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    LblAddrValid = MEMACC_FALSE;
    LblLengthValid = MEMACC_FALSE;
    #endif

    for (LusSubAreaIdx = MEMACC_ZERO;
      #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
      ((MEMACC_FALSE == LblAddrValid) || (MEMACC_FALSE == LblLengthValid)) &&
      #endif
      (LusSubAreaIdx < MemAcc_GpAddressAreaConfig[addressAreaId].usNumOfSubArea); LusSubAreaIdx++)                      
    {
      LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].pSubAreaConfig[LusSubAreaIdx];

      /* Check if targetAddress is inside this sub-area */
      if ((targetAddress >= LpSubAreaConfig->ddLogicStartAddr) &&                                                       
          (targetAddress < (LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength)))                     /* PRQA S 3383 # JV-01 */
      {
        /* Store sub-area index */
        MemAcc_GstAddrAreaData[addressAreaId].usCurrentSubAreaIdx = LusSubAreaIdx;                                      
        /* Set retry count */
        MemAcc_GstAddrAreaData[addressAreaId].ucRetryTimes = LpSubAreaConfig->ucNumberOfEraseRetries;                   

        #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
        /* Calculate alignment check value */
        LulCheckAlign = LpSubAreaConfig->ulMemEraseSectorSize - (uint32)MEMACC_ONE;                                     /* PRQA S 3383 # JV-01 */
        
        /* Check address alignment */
        if (MEMACC_ZERO == (targetAddress & LulCheckAlign))
        {
          LblAddrValid = MEMACC_TRUE;
        }
        #else
        /* break this loop since sub-area was found */
        break;
        #endif
      }

      #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
      if (MEMACC_ZERO != length)
      {
        /* Calculate end address */
        LddEndLogicAddr = targetAddress + length - (MemAcc_AddressType)MEMACC_ONE;                                      /* PRQA S 3383, 3384 # JV-01, JV-01 */
        /* Check if end address is inside this sub-area */
        if ((LddEndLogicAddr >= LpSubAreaConfig->ddLogicStartAddr) &&
            (LddEndLogicAddr < (LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength)))                 /* PRQA S 3383 # JV-01 */
        {
          /* Calculate alignment check value */
          LulCheckAlign = LpSubAreaConfig->ulMemEraseSectorSize - (uint32)MEMACC_ONE;                                   /* PRQA S 3383 # JV-01 */

          /* Check address alignment */
          if (MEMACC_ZERO == ((LddEndLogicAddr + (MemAcc_AddressType)MEMACC_ONE) & LulCheckAlign))
          {
            LblLengthValid = MEMACC_TRUE;
          }
        }
      }
      #endif
    }

    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    if ((MEMACC_FALSE == LblAddrValid) || (MEMACC_FALSE == LblLengthValid))
    {
      /* Report to DET if targetAddress or length is invalid */
      (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_ERASE_SID, MEMACC_E_PARAM_ADDRESS_LENGTH);
      /* Reset return value to E_NOT_OK due to failure */
      LenReturnValue = E_NOT_OK;
    }
    #endif
  }

  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Check whether any error is reported to DET */
  if (E_OK == LenReturnValue)
  #endif
  {
    /* Set job status to pending */
    MemAcc_GstAddrAreaData[addressAreaId].enJobStatus = MEMACC_JOB_PENDING;                                             
    /* Set request address */
    MemAcc_GstAddrAreaData[addressAreaId].ddCurrentAddress = targetAddress;                                             
    /* Set request length */
    MemAcc_GstAddrAreaData[addressAreaId].ddRemainingLength = length;                                                   
    /* Set processed length = 0 */
    MemAcc_GstAddrAreaData[addressAreaId].ddProcessedLength = MEMACC_ZERO;                                              
    /* Set command = erase */
    MemAcc_GstAddrAreaData[addressAreaId].enCommand = MEMACC_ERASE_JOB;                                                 
    /* Set requested Length */
    MemAcc_GstAddrAreaData[addressAreaId].ddMemRequestedLength = MEMACC_ZERO;                                            
  } /* else No action required */

  return (LenReturnValue);
} /* End of API MemAcc_Erase */

#if (MEMACC_COMPARE_API == STD_ON)
/***********************************************************************************************************************
** Function Name            : MemAcc_Compare
**
** Service ID               : 0x0c
**
** Description              : This API triggers a job to compare the passed data
**                            to the memory content of the provided address area.
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : addressAreaId, sourceAddress, length
**
** InOut Parameters         : None
**
** Output Parameters        : destinationDataPtr
**
** Return parameter         : Std_ReturnType
**                            E_OK: if Read command has been accepted.
**                            E_NOT_OK: if Read command has not been accepted.
**                            E_MEM_SERVICE_NOT_AVAIL: The underlying Mem driver
**                            service function is not available
**
** Preconditions            : Component must be initialized using MemAcc_Init().
**
** Global Variables Used    : MemAcc_GstVar.pTempBufferAddress(W),
**                            MemAcc_GstVar.ulReadAddress(W),
**                            MemAcc_GstVar.pBufferAddress(W),
**                            MemAcc_GstVar.ulRequestedLength(W),
**                            MemAcc_GstVar.ulCurrentLength(W),
**                            MemAcc_GstVar.enGenCommand(W), MemAcc_GenState(W),
**                            MemAcc_GenJobResult(W),MemAcc_GstVar.ucOffset(R/W),
**                            MemAcc_GstVar.enFlashStatus(W)
**                            MemAcc_GstVar.blBCCmdNotFirstStartFlg(W),
**                            MemAcc_GaaTempBuffer(W)
**
** Function(s) invoked      : Det_ReportError,MemAcc_DetErrorCheckAndSwitchBusy,
**                            MemAcc_GetIntReq,MemAcc_ClearIntReq,MemAcc_SetStatus
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_015
** Reference ID             : MEMACC_DUD_ACT_015_ERR001, MEMACC_DUD_ACT_015_ERR002
** Reference ID             : MEMACC_DUD_ACT_015_ERR003, MEMACC_DUD_ACT_015_ERR006, MEMACC_DUD_ACT_015_GBL001
** Reference ID             : MEMACC_DUD_ACT_015_GBL002, MEMACC_DUD_ACT_015_GBL003, MEMACC_DUD_ACT_015_GBL004
** Reference ID             : MEMACC_DUD_ACT_015_GBL005, MEMACC_DUD_ACT_015_GBL006, MEMACC_DUD_ACT_015_GBL007
** Reference ID             : MEMACC_DUD_ACT_015_GBL008, MEMACC_DUD_ACT_015_GBL009, MEMACC_DUD_ACT_015_GBL010
***********************************************************************************************************************/
FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_Compare (                                                               /* PRQA S 1503 # JV-01 */
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType sourceAddress,
  P2CONST(MemAcc_DataType, AUTOMATIC, MEMACC_APPL_CONST) dataPtr,
  MemAcc_LengthType length)
{
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to check if address and length is valid */
  boolean LblAddrValid, LblLengthValid;
  #endif
  /* Local variable to hold the DET return value */
  Std_ReturnType LenReturnValue;
  /* Local variable to hold loop count */
  uint16 LusSubAreaIdx;
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold align check value */
  uint32 LulCheckAlign;
  /* Local varriable to hold end logical address */
  MemAcc_AddressType LddEndLogicAddr;
  #endif
  /* Pointer to sub area config */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  /* Initialize return value */
  LenReturnValue = E_OK;
  
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_COMPARE_SID, MEMACC_E_UNINIT);
    /* Reset return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if addressAreaId is valid */
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_COMPARE_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
    /* Set return value to failed to due error */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if destinationDataPtr is NULL_PTR */
  else if (NULL_PTR == dataPtr)
  {
   /* Report error to DET */
   (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_COMPARE_SID, MEMACC_E_PARAM_POINTER);
   /* Reset return value to E_NOT_OK due to failure */
   LenReturnValue = E_NOT_OK;
  }
  /* Check if the job for addressAreaId is pending */
  else if (MEMACC_JOB_PENDING == MemAcc_GstAddrAreaData[addressAreaId].enJobStatus)                                     /* PRQA S 2004 # JV-01 */
  {
    /* Report to DET if the driver is currently busy */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_COMPARE_SID, MEMACC_E_BUSY);
    /* Reset return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  /* Check whether any error is reported to DET */
  if (E_OK == LenReturnValue)
  #endif /* #if (MEMACC_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    LblAddrValid = MEMACC_FALSE;
    LblLengthValid = MEMACC_FALSE;
    #endif

    for (LusSubAreaIdx = MEMACC_ZERO;
      #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
      ((MEMACC_FALSE == LblAddrValid) || (MEMACC_FALSE == LblLengthValid)) &&
      #endif
      (LusSubAreaIdx < MemAcc_GpAddressAreaConfig[addressAreaId].usNumOfSubArea); LusSubAreaIdx++)                      
    {
      LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].pSubAreaConfig[LusSubAreaIdx];

      /* Check if sourceAddress is inside this sub-area */
      if ((sourceAddress >= LpSubAreaConfig->ddLogicStartAddr) &&                                                       
          (sourceAddress < (LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength)))                     /* PRQA S 3383 # JV-01 */
      {
        /* Store sub-area index */
        MemAcc_GstAddrAreaData[addressAreaId].usCurrentSubAreaIdx = LusSubAreaIdx;                                      

        #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
        /* Calculate alignment check value */
        LulCheckAlign = LpSubAreaConfig->ulMemReadPageSize - (uint32)MEMACC_ONE;                                         /* PRQA S 3383 # JV-01 */
        
        /* Check address alignment */
        if (MEMACC_ZERO == (sourceAddress & LulCheckAlign))
        {
          LblAddrValid = MEMACC_TRUE;
        }
        #else
        /* break this loop since sub-area was found */
        break;
        #endif
      }

      #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
      if (MEMACC_ZERO != length)
      {
        /* Calculate end address */
        LddEndLogicAddr = sourceAddress + length - (MemAcc_AddressType)MEMACC_ONE;                                      /* PRQA S 3383, 3384 # JV-01, JV-01 */

        /* Check if end address is inside this sub-area */
        if ((LddEndLogicAddr >= LpSubAreaConfig->ddLogicStartAddr) &&
            (LddEndLogicAddr < (LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength)))                 /* PRQA S 3383 # JV-01 */
        {
          /* Calculate alignment check value */
          LulCheckAlign = LpSubAreaConfig->ulMemReadPageSize - (uint32)MEMACC_ONE;                                      /* PRQA S 3383 # JV-01 */

          /* Check address alignment */
          if (MEMACC_ZERO == ((LddEndLogicAddr + (MemAcc_AddressType)MEMACC_ONE) & LulCheckAlign))
          {
            LblLengthValid = MEMACC_TRUE;
          }
        }
      }
      #endif
    }

    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    if ((MEMACC_FALSE == LblAddrValid) || (MEMACC_FALSE == LblLengthValid))
    {
      /* Report to DET if sourceAddress or length is invalid */
      (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_COMPARE_SID, MEMACC_E_PARAM_ADDRESS_LENGTH);
      /* Reset return value to E_NOT_OK due to failure */
      LenReturnValue = E_NOT_OK;
    }
    #endif
  }

  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Check whether any error is reported to DET */
  if (E_OK == LenReturnValue)
  #endif
  {
    /* Set job status to pending */
    MemAcc_GstAddrAreaData[addressAreaId].enJobStatus = MEMACC_JOB_PENDING;                                             
    /* Set request address */
    MemAcc_GstAddrAreaData[addressAreaId].ddCurrentAddress = sourceAddress;                                             
    /* Set request length */
    MemAcc_GstAddrAreaData[addressAreaId].ddRemainingLength = length;                                                   
    /* Set upper layer buffer */
    MemAcc_GstAddrAreaData[addressAreaId].pReadOnlyBufferAddr = dataPtr;                                                
    /* Set processed length = 0 */
    MemAcc_GstAddrAreaData[addressAreaId].ddProcessedLength = MEMACC_ZERO;                                              
    /* Set command = compare */
    MemAcc_GstAddrAreaData[addressAreaId].enCommand = MEMACC_COMPARE_JOB;                                               
    /* Set requested Length */
    MemAcc_GstAddrAreaData[addressAreaId].ddMemRequestedLength = MEMACC_ZERO;                                            
  } /* else No action required */

  return (LenReturnValue);
} /* End of API MemAcc_Compare */
#endif /* #if (MEMACC_COMPARE_API == STD_ON) */

/***********************************************************************************************************************
** Function Name            : MemAcc_Write
**
** Service ID               : 0x0A
**
** Description              : This API triggers a write job to store the passed
**                            data to the provided address area.
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : addressAreaId, targetAddress, sourceDataPtr, length
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : Std_ReturnType
**                            E_OK: requested job has been accepted by the module.
**                            E_NOT_OK: requested job has not been accepted by the module.
**                            E_MEM_SERVICE_NOT_AVAIL: The underlying Mem driver
**                            service function is not available
**
** Preconditions            : Component must be initialized using MemAcc_Init().
**
** Global Variables Used    : MemAcc_GstAddrAreaData, MemAcc_GpAddressAreaConfig, MemAcc_GenInitStatus
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_013_ERR001, MEMACC_DUD_ACT_013_ERR002
** Reference ID             : MEMACC_DUD_ACT_013_ERR003, MEMACC_DUD_ACT_013_ERR004
** Reference ID             : MEMACC_DUD_ACT_013_ERR006, MEMACC_DUD_ACT_013, MEMACC_DUD_ACT_013_GBL001
** Reference ID             : MEMACC_DUD_ACT_013_GBL002, MEMACC_DUD_ACT_013_GBL003, MEMACC_DUD_ACT_013_GBL004
** Reference ID             : MEMACC_DUD_ACT_013_GBL005, MEMACC_DUD_ACT_013_GBL006, MEMACC_DUD_ACT_013_GBL007
** Reference ID             : MEMACC_DUD_ACT_013_GBL008, MEMACC_DUD_ACT_013_GBL009, MEMACC_DUD_ACT_013_GBL010
** Reference ID             : MEMACC_DUD_ACT_013_GBL011
***********************************************************************************************************************/
FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_Write (                                                                 /* PRQA S 1503 # JV-01 */
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType targetAddress,
  P2CONST(MemAcc_DataType, AUTOMATIC, MEMACC_APPL_CONST) sourceDataPtr,
  MemAcc_LengthType length)
{
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to check if address and length is valid */
  boolean LblAddrValid, LblLengthValid;
  #endif
  /* Local variable to hold the DET return value */
  Std_ReturnType LenReturnValue;
  /* Local variable to hold loop count */
  uint16 LusSubAreaIdx;
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold align check value */
  uint32 LulCheckAlign;
  /* Local varriable to hold end logical address */
  MemAcc_AddressType LddEndLogicAddr;
  #endif
  /* Pointer to sub area config */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  /* Initialize return value */
  LenReturnValue = E_OK;
  
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_WRITE_SID, MEMACC_E_UNINIT);
    /* Reset return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if addressAreaId is valid */
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_WRITE_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
    /* Set return value to failed to due error */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if sourceDataPtr is NULL_PTR or not align with buffer alignment value */
  else if ((NULL_PTR == sourceDataPtr) ||
    ((((uint32)sourceDataPtr) & ((uint32)MemAcc_GpAddressAreaConfig[addressAreaId].                                     /* PRQA S 0306 # JV-01 */
      ucBufferAlignValue -(uint32)MEMACC_ONE)) != MEMACC_ZERO))                                                         /* PRQA S 3384 # JV-01 */
  {
    /* Report error to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_WRITE_SID, MEMACC_E_PARAM_POINTER);
    /* Reset return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if the job for addressAreaId is pending */
  else if (MEMACC_JOB_PENDING == MemAcc_GstAddrAreaData[addressAreaId].enJobStatus)                                     /* PRQA S 2004 # JV-01 */
  {
    /* Report to DET if the driver is currently busy */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_WRITE_SID, MEMACC_E_BUSY);
    /* Reset return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  /* Check whether any error is reported to DET */
  if (E_OK == LenReturnValue)
  #endif /* #if (MEMACC_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    LblAddrValid = MEMACC_FALSE;
    LblLengthValid = MEMACC_FALSE;
    #endif
    
    for (LusSubAreaIdx = MEMACC_ZERO;
      #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
      ((MEMACC_FALSE == LblAddrValid) || (MEMACC_FALSE == LblLengthValid)) &&
      #endif
      (LusSubAreaIdx < MemAcc_GpAddressAreaConfig[addressAreaId].usNumOfSubArea); LusSubAreaIdx++)                      
    {
      LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].pSubAreaConfig[LusSubAreaIdx];

      /* Check if targetAddress is inside this sub-area */
      if ((targetAddress >= LpSubAreaConfig->ddLogicStartAddr) &&                                                       
          (targetAddress < (LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength)))                     /* PRQA S 3383 # JV-01 */
      {
        /* Store sub-area index */
        MemAcc_GstAddrAreaData[addressAreaId].usCurrentSubAreaIdx = LusSubAreaIdx;                                      
        /* Set retry count */
        MemAcc_GstAddrAreaData[addressAreaId].ucRetryTimes = LpSubAreaConfig->ucNumberOfWriteRetries;                   

        #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
        /* Calculate alignment check value */
        LulCheckAlign = LpSubAreaConfig->ulMemWritePageSize - (uint32)MEMACC_ONE;                                       /* PRQA S 3383 # JV-01 */
        
        /* Check address alignment */
        if (MEMACC_ZERO == (targetAddress & LulCheckAlign))
        {
          LblAddrValid = MEMACC_TRUE;
        }
        #else
        /* break this loop since sub-area was found */
        break;
        #endif
      }

      #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
      if (MEMACC_ZERO != length)
      {
        /* Calculate end address */
        LddEndLogicAddr = targetAddress + length - (MemAcc_AddressType)MEMACC_ONE;                                      /* PRQA S 3383, 3384 # JV-01, JV-01 */
        /* Check if end address is inside this sub-area */
        if ((LddEndLogicAddr >= LpSubAreaConfig->ddLogicStartAddr) &&
            (LddEndLogicAddr < (LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength)))                 /* PRQA S 3383 # JV-01 */
        {
          /* Calculate alignment check value */
          LulCheckAlign = LpSubAreaConfig->ulMemWritePageSize - (uint32)MEMACC_ONE;                                     /* PRQA S 3383 # JV-01 */
          /* Check address alignment */
          if (MEMACC_ZERO == ((LddEndLogicAddr + (MemAcc_AddressType)MEMACC_ONE) & LulCheckAlign))
          {
            LblLengthValid = MEMACC_TRUE;
          }
        }
      }
      #endif
    }

    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    if ((MEMACC_FALSE == LblAddrValid) || (MEMACC_FALSE == LblLengthValid))
    {
      /* Report to DET if targetAddress or length is invalid */
      (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_WRITE_SID, MEMACC_E_PARAM_ADDRESS_LENGTH);
      /* Reset return value to E_NOT_OK due to failure */
      LenReturnValue = E_NOT_OK;
    }
    #endif
  }

  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Check whether any error is reported to DET */
  if (E_OK == LenReturnValue)
  #endif
  {
    /* Set job status to pending */
    MemAcc_GstAddrAreaData[addressAreaId].enJobStatus = MEMACC_JOB_PENDING;                                             
    /* Set request address */
    MemAcc_GstAddrAreaData[addressAreaId].ddCurrentAddress = targetAddress;                                             
    /* Set request length */
    MemAcc_GstAddrAreaData[addressAreaId].ddRemainingLength = length;                                                   
    /* Set processed length = 0 */
    MemAcc_GstAddrAreaData[addressAreaId].ddProcessedLength = MEMACC_ZERO;                                              
    /* Set upper layer buffer */
    MemAcc_GstAddrAreaData[addressAreaId].pReadOnlyBufferAddr = sourceDataPtr;                                          
    /* Set command = write */
    MemAcc_GstAddrAreaData[addressAreaId].enCommand = MEMACC_WRITE_JOB;                                                 
    /* Set requested Length */
    MemAcc_GstAddrAreaData[addressAreaId].ddMemRequestedLength = MEMACC_ZERO;                                            
  } /* else No action required */

  return (LenReturnValue);
} /* End of API MemAcc_Write */

/***********************************************************************************************************************
** Function Name            : MemAcc_BlankCheck
**
** Service ID               : 0x0d
**
** Description              : This API Checks if the passed address space is blank.
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : addressAreaId, targetAddress, length
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : Std_ReturnType
**                            E_OK: requested job has been accepted by the module.
**                            E_NOT_OK: requested job has not been accepted by the module.
**                            E_MEM_SERVICE_NOT_AVAIL: The underlying Mem driver
**                            service function is not available
**
** Preconditions            : Component must be initialized using MemAcc_Init().
**
** Global Variables Used    : MemAcc_GenInitStatus, MemAcc_GstAddrAreaData, MemAcc_GpAddressAreaConfig
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_016_ERR001, MEMACC_DUD_ACT_016_ERR003
** Reference ID             : MEMACC_DUD_ACT_016, MEMACC_DUD_ACT_016_ERR006, MEMACC_DUD_ACT_016_GBL001
** Reference ID             : MEMACC_DUD_ACT_016_GBL002, MEMACC_DUD_ACT_016_GBL003, MEMACC_DUD_ACT_016_GBL004
** Reference ID             : MEMACC_DUD_ACT_016_GBL005, MEMACC_DUD_ACT_016_GBL006, MEMACC_DUD_ACT_016_GBL007
** Reference ID             : MEMACC_DUD_ACT_016_GBL008, MEMACC_DUD_ACT_016_GBL009
***********************************************************************************************************************/
FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_BlankCheck (                                                            /* PRQA S 1503 # JV-01 */
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType targetAddress,
  MemAcc_LengthType length)
{
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to check if address and length is valid */
  boolean LblAddrValid, LblLengthValid;
  #endif
  /* Local variable to hold the DET return value */
  Std_ReturnType LenReturnValue;
  /* Local variable to hold loop count */
  uint16 LusSubAreaIdx;
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold align check value */
  uint32 LulCheckAlign;
  /* Local varriable to hold end logical address */
  MemAcc_AddressType LddEndLogicAddr;
  #endif
  /* Pointer to sub area config */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  /* Initialize return value */
  LenReturnValue = E_OK;
  
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_BLANK_CHECK_SID, MEMACC_E_UNINIT);
    /* Reset return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if addressAreaId is valid */
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_BLANK_CHECK_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
    /* Set return value to failed to due error */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if the job for addressAreaId is pending */
  else if (MEMACC_JOB_PENDING == MemAcc_GstAddrAreaData[addressAreaId].enJobStatus)                                     /* PRQA S 2004 # JV-01 */
  {
    /* Report to DET if the driver is currently busy */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_BLANK_CHECK_SID, MEMACC_E_BUSY);
    /* Reset return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  /* Check whether any error is reported to DET */
  if (E_OK == LenReturnValue)
  #endif /* #if (MEMACC_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    LblAddrValid = MEMACC_FALSE;
    LblLengthValid = MEMACC_FALSE;
    #endif

    for (LusSubAreaIdx = MEMACC_ZERO;
      #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
      ((MEMACC_FALSE == LblAddrValid) || (MEMACC_FALSE == LblLengthValid)) &&
      #endif
      (LusSubAreaIdx < MemAcc_GpAddressAreaConfig[addressAreaId].usNumOfSubArea); LusSubAreaIdx++)                      
    {
      LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].pSubAreaConfig[LusSubAreaIdx];

      /* Check if targetAddress is inside this sub-area */
      if ((targetAddress >= LpSubAreaConfig->ddLogicStartAddr) &&                                                       
          (targetAddress < (LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength)))                     /* PRQA S 3383 # JV-01 */
      {
        /* Store sub-area index */
        MemAcc_GstAddrAreaData[addressAreaId].usCurrentSubAreaIdx = LusSubAreaIdx;                                      

        #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
        /* Calculate alignment check value */
        LulCheckAlign = LpSubAreaConfig->ulMemReadPageSize - (uint32)MEMACC_ONE;                                         /* PRQA S 3383 # JV-01 */
        
        /* Check address alignment */
        if (MEMACC_ZERO == (targetAddress & LulCheckAlign))
        {
          LblAddrValid = MEMACC_TRUE;
        }
        #else
        /* break this loop since sub-area was found */
        break;
        #endif
      }

      #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
      if (MEMACC_ZERO != length)
      {
        /* Calculate end address */
        LddEndLogicAddr = targetAddress + length - (MemAcc_AddressType)MEMACC_ONE;                                      /* PRQA S 3383, 3384 # JV-01, JV-01 */
        /* Check if end address is inside this sub-area */
        if ((LddEndLogicAddr >= LpSubAreaConfig->ddLogicStartAddr) &&
            (LddEndLogicAddr < (LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength)))                 /* PRQA S 3383 # JV-01 */
        {
          /* Calculate alignment check value */
          LulCheckAlign = LpSubAreaConfig->ulMemReadPageSize - (uint32)MEMACC_ONE;                                      /* PRQA S 3383 # JV-01 */

          /* Check address alignment */
          if (MEMACC_ZERO == ((LddEndLogicAddr + (MemAcc_AddressType)MEMACC_ONE) & LulCheckAlign))
          {
            LblLengthValid = MEMACC_TRUE;
          }
        }
      }
      #endif
    }

    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    if ((MEMACC_FALSE == LblAddrValid) || (MEMACC_FALSE == LblLengthValid))
    {
      /* Report to DET if targetAddress or length is invalid */
      (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_BLANK_CHECK_SID, MEMACC_E_PARAM_ADDRESS_LENGTH);
      /* Reset return value to E_NOT_OK due to failure */
      LenReturnValue = E_NOT_OK;
    }
    #endif
  }

  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Check whether any error is reported to DET */
  if (E_OK == LenReturnValue)
  #endif
  {
    /* Set job status to pending */
    MemAcc_GstAddrAreaData[addressAreaId].enJobStatus = MEMACC_JOB_PENDING;                                             
    /* Set request address */
    MemAcc_GstAddrAreaData[addressAreaId].ddCurrentAddress = targetAddress;                                             
    /* Set request length */
    MemAcc_GstAddrAreaData[addressAreaId].ddRemainingLength = length;                                                   
    /* Set processed length = 0 */
    MemAcc_GstAddrAreaData[addressAreaId].ddProcessedLength = MEMACC_ZERO;                                              
    /* Set command = blank check */
    MemAcc_GstAddrAreaData[addressAreaId].enCommand = MEMACC_BLANKCHECK_JOB;                                            
    /* Set requested Length */
    MemAcc_GstAddrAreaData[addressAreaId].ddMemRequestedLength = MEMACC_ZERO;                                            
  } /* else No action required */

  return (LenReturnValue);
} /* End of API MemAcc_BlankCheck */

/***********************************************************************************************************************
** Function Name            : MemAcc_RequestLock
**
** Service ID               : 0x11
**
** Description              : This API request lock of an address area for
**                            exclusive access.
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : addressAreaId, address, length, lockNotificationFctPtr
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : Std_ReturnType
**                            E_OK: The requested job has been accepted by the module.
**                            E_NOT_OK: The requested job has been rejected by the module.
**
** Preconditions            : Component must be initialized using MemAcc_Init().
**
** Global Variables Used    : MemAcc_GenInitStatus, MemAcc_GpAddressAreaConfig, MemAcc_GstLockRequestData, MemAcc_GstVar
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_017_ERR001, MEMACC_DUD_ACT_017_ERR002
** Reference ID             : MEMACC_DUD_ACT_017_ERR003, MEMACC_DUD_ACT_017, MEMACC_DUD_ACT_017_GBL001
** Reference ID             : MEMACC_DUD_ACT_017_GBL002, MEMACC_DUD_ACT_017_GBL003, MEMACC_DUD_ACT_017_GBL004
** Reference ID             : MEMACC_DUD_ACT_017_GBL005, MEMACC_DUD_ACT_017_GBL006, MEMACC_DUD_ACT_017_GBL007
** Reference ID             : MEMACC_DUD_ACT_017_GBL008, MEMACC_DUD_ACT_017_GBL009, MEMACC_DUD_ACT_017_GBL010
***********************************************************************************************************************/
FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_RequestLock (                                                           /* PRQA S 1503 # JV-01 */
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType address,
  MemAcc_AddressType length,
  void* lockNotificationFctPtr)                                                                                         /* PRQA S 3673 # JV-01 */
{
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to check if address and length is valid */
  boolean LblAddrValid;
  #endif
  boolean LblSubAreaFound;
  /* Local variable to hold the DET return value */
  Std_ReturnType LenReturnValue;
  /* Local variable to hold loop count */
  uint16 LusSubAreaIdx;
  /* Local varriable to hold end logical address */
  MemAcc_AddressType LddEndLogicAddr;
  /* Pointer to sub area config */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  /* Initialize return value */
  LenReturnValue = E_OK;
    
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_REQUEST_LOCK_SID, MEMACC_E_UNINIT);
    /* Reset return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if addressAreaId is valid */
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_REQUEST_LOCK_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
    /* Set return value to failed to due error */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if lockNotificationFctPtr is NULL_PTR */
  else if (NULL_PTR == lockNotificationFctPtr)
  {
   /* Report error to DET */
   (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_REQUEST_LOCK_SID, MEMACC_E_PARAM_POINTER);
   /* Reset return value to E_NOT_OK due to failure */
   LenReturnValue = E_NOT_OK;
  }
  /* Check address and length */
  else
  {
    LblAddrValid = MEMACC_TRUE;

    /* Get 1st sub-area config */
    LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].pSubAreaConfig[MEMACC_ZERO];                           

    /* Check if address is invalid */
    if (LpSubAreaConfig->ddLogicStartAddr > address)                                                                    
    {
      LblAddrValid = MEMACC_FALSE;
    }

    /* Get last sub-area config */
    LusSubAreaIdx = MemAcc_GpAddressAreaConfig[addressAreaId].usNumOfSubArea - (uint16)MEMACC_ONE;
    LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].pSubAreaConfig[LusSubAreaIdx];

    /* Check if length is invalid */
    if (length != MEMACC_ZERO)
    {
      /* Calculate end address */
      LddEndLogicAddr = address + length - (MemAcc_AddressType)MEMACC_ONE;                                              /* PRQA S 3383, 3384 # JV-01, JV-01 */
      if ((LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength) <= LddEndLogicAddr)                    /* PRQA S 3383 # JV-01 */
      {
        LblAddrValid = MEMACC_FALSE;
      }
    }
    /* Check length is Zero */
    else
    {
      LblAddrValid = MEMACC_FALSE;
    }

    if (MEMACC_FALSE == LblAddrValid)
    {
      /* Report to DET if sourceAddress or length is invalid */
      (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_REQUEST_LOCK_SID, MEMACC_E_PARAM_ADDRESS_LENGTH);
      /* Reset return value to E_NOT_OK due to failure */
      LenReturnValue = E_NOT_OK;
    }
  }

  /* Check whether any error is reported to DET */
  if (E_OK == LenReturnValue)
  #endif
  {
    /* Get lock request notification pointer */
    MemAcc_GstLockRequestData.pLockNotificationFctPtr = (void (*)(void))lockNotificationFctPtr;                         /* PRQA S 0307 # JV-01 */
    /* Initialize variables */
    MemAcc_GstLockRequestData.ulNumOfLockInstance = (uint32)MEMACC_ZERO;
    LblSubAreaFound = MEMACC_FALSE;
    
    /* Calculate end address */
    LddEndLogicAddr = address + length - (MemAcc_AddressType)MEMACC_ONE;                                                /* PRQA S 3383, 3384 # JV-01, JV-01 */
    /* Loop through all sub-area */
    for (LusSubAreaIdx = (uint16)MEMACC_ZERO; LusSubAreaIdx <
      MemAcc_GpAddressAreaConfig[addressAreaId].usNumOfSubArea; LusSubAreaIdx++)                                        
    {
      LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].pSubAreaConfig[LusSubAreaIdx];
      
      if (MEMACC_FALSE == LblSubAreaFound)
      {
        if ((LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength) > address)                           /* PRQA S 3383 # JV-01 */
        {
          LblSubAreaFound = MEMACC_TRUE;
          /* Set lock request flag */
          MemAcc_GstVar[LpSubAreaConfig->ulInstanceId].blLockRequest = MEMACC_TRUE;                                     
          /* Initialize lock state */
          MemAcc_GstVar[LpSubAreaConfig->ulInstanceId].blLockState = MEMACC_FALSE;                                      
          /* Increase number of instance to be locked */
          MemAcc_GstLockRequestData.ulNumOfLockInstance++;                                                              /* PRQA S 3383 # JV-01 */
        }
      }
      else
      {
        if (LpSubAreaConfig->ddLogicStartAddr <= LddEndLogicAddr)
        {
          if (MEMACC_FALSE == MemAcc_GstVar[LpSubAreaConfig->ulInstanceId].blLockRequest)                               
          {
            /* Set lock request flag */
            MemAcc_GstVar[LpSubAreaConfig->ulInstanceId].blLockRequest = MEMACC_TRUE;                                   
            /* Initialize lock state */
            MemAcc_GstVar[LpSubAreaConfig->ulInstanceId].blLockState = MEMACC_FALSE;                                    
            /* Increase number of instance to be locked */
            MemAcc_GstLockRequestData.ulNumOfLockInstance++;                                                            /* PRQA S 3383 # JV-01 */
          }
        }
        else
        {
          /* Break the loop since last sub-area is found */
          break;
        }
      }
    }
  } /* else No action required */

  return (LenReturnValue);
} /* End of API MemAcc_RequestLock */

/***********************************************************************************************************************
** Function Name            : MemAcc_ReleaseLock
**
** Service ID               : 0x12
**
** Description              : This API Release access lock of provided
**                            address area.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : addressAreaId, address, length
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : Std_ReturnType
**                            E_OK: The requested job has been accepted by the module.
**                            E_NOT_OK: The requested job has been rejected by the module.
**
** Preconditions            : Component must be initialized using MemAcc_Init().
**
** Global Variables Used    : MemAcc_GpAddressAreaConfig, MemAcc_GenInitStatus, MemAcc_GstVar
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_018_ERR001, MEMACC_DUD_ACT_018_ERR004
** Reference ID             : MEMACC_DUD_ACT_018_ERR003, MEMACC_DUD_ACT_018, MEMACC_DUD_ACT_018_GBL001
** Reference ID             : MEMACC_DUD_ACT_018_GBL002, MEMACC_DUD_ACT_018_GBL003, MEMACC_DUD_ACT_018_GBL004
** Reference ID             : MEMACC_DUD_ACT_018_GBL005, MEMACC_DUD_ACT_018_GBL006, MEMACC_DUD_ACT_018_GBL007
** Reference ID             : MEMACC_DUD_ACT_018_GBL008
***********************************************************************************************************************/
FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_ReleaseLock (                                                           /* PRQA S 1503 # JV-01 */
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_AddressType address,
  MemAcc_AddressType length)
{
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to check if address and length is valid */
  boolean LblAddrValid;
  #endif
  boolean LblSubAreaFound;
  /* Local variable to hold the DET return value */
  Std_ReturnType LenReturnValue;
  /* Local variable to hold loop count */
  uint16 LusSubAreaIdx;
  /* Local varriable to hold end logical address */
  MemAcc_AddressType LddEndLogicAddr;
  /* Pointer to sub area config */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  /* Initialize return value */
  LenReturnValue = E_OK;
   
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_RELEASE_LOCK_SID, MEMACC_E_UNINIT);
    /* Reset return value to E_NOT_OK due to failure */
    LenReturnValue = E_NOT_OK;
  }
  /* Check if addressAreaId is valid */
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_RELEASE_LOCK_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
    /* Set return value to failed to due error */
    LenReturnValue = E_NOT_OK;
  }
  /* Check address and length */
  else
  {
    LblAddrValid = MEMACC_TRUE;

    /* Get 1st sub-area config */
    LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].pSubAreaConfig[MEMACC_ZERO];                           

    /* Check if address is invalid */
    if (LpSubAreaConfig->ddLogicStartAddr > address)                                                                    
    {
      LblAddrValid = MEMACC_FALSE;
    }

    /* Get last sub-area config */
    LusSubAreaIdx = MemAcc_GpAddressAreaConfig[addressAreaId].usNumOfSubArea - (uint16)MEMACC_ONE;
    LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].pSubAreaConfig[LusSubAreaIdx];

    /* Check if length is invalid */
    if (length != MEMACC_ZERO)
    {
      /* Calculate end address */
      LddEndLogicAddr = address + length - (MemAcc_AddressType)MEMACC_ONE;                                              /* PRQA S 3383, 3384 # JV-01, JV-01 */
      if ((LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength) <= LddEndLogicAddr)                    /* PRQA S 3383 # JV-01 */
      {
        LblAddrValid = MEMACC_FALSE;
      }
    }
    /* Check length is Zero */
    else
    {
      LblAddrValid = MEMACC_FALSE;
    }

    if (MEMACC_FALSE == LblAddrValid)
    {
      /* Report to DET if sourceAddress or length is invalid */
      (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_RELEASE_LOCK_SID, MEMACC_E_PARAM_ADDRESS_LENGTH);
      /* Reset return value to E_NOT_OK due to failure */
      LenReturnValue = E_NOT_OK;
    }
  }

  /* Check whether any error is reported to DET */
  if (E_OK == LenReturnValue)
  #endif
  {
    LblSubAreaFound = MEMACC_FALSE;
    /* Calculate end address */
    LddEndLogicAddr = address + length - (MemAcc_AddressType)MEMACC_ONE;                                                /* PRQA S 3383, 3384 # JV-01, JV-01 */
    /* Loop through all sub-area */
    for (LusSubAreaIdx = (uint16)MEMACC_ZERO; LusSubAreaIdx <
      MemAcc_GpAddressAreaConfig[addressAreaId].usNumOfSubArea; LusSubAreaIdx++)                                        
    {
      LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].pSubAreaConfig[LusSubAreaIdx];
      
      if (MEMACC_FALSE == LblSubAreaFound)
      {
        if ((LpSubAreaConfig->ddLogicStartAddr + LpSubAreaConfig->ddSubAreaLength) > address)                           /* PRQA S 3383 # JV-01 */
        {
          LblSubAreaFound = MEMACC_TRUE;
          /* Set lock request flag */
          MemAcc_GstVar[LpSubAreaConfig->ulInstanceId].blLockRequest = MEMACC_FALSE;                                    
          /* Initialize lock state */
          MemAcc_GstVar[LpSubAreaConfig->ulInstanceId].blLockState = MEMACC_FALSE;                                      
        }
      }
      else
      {
        if (LpSubAreaConfig->ddLogicStartAddr <= LddEndLogicAddr)
        {
          /* Set lock request flag */
          MemAcc_GstVar[LpSubAreaConfig->ulInstanceId].blLockRequest = MEMACC_FALSE;                                    
          /* Initialize lock state */
          MemAcc_GstVar[LpSubAreaConfig->ulInstanceId].blLockState = MEMACC_FALSE;                                      
        }
        else
        {
          /* Break the loop since last sub-area is found */
          break;
        }
      }
    }
  } /* else No action required */

  return (LenReturnValue);
} /* End of API MemAcc_ReleaseLock */

/***********************************************************************************************************************
** Function Name            : MemAcc_Cancel
**
** Service ID               : 0x04
**
** Description              : This API triggers a cancel operation of the
**                            pending job for the address area.
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : addressAreaId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : Component must be initialized using MemAcc_Init().
**
** Global Variables Used    : MemAcc_GstAddrAreaData[], MemAcc_GenInitStatus
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_011, MEMACC_DUD_ACT_011_ERR001,
** Reference ID             : MEMACC_DUD_ACT_011_ERR003, MEMACC_DUD_ACT_011_GBL001, MEMACC_DUD_ACT_011_GBL002
** Reference ID             : MEMACC_DUD_ACT_011_GBL003
***********************************************************************************************************************/
FUNC(void, MEMACC_PUBLIC_CODE) MemAcc_Cancel (MemAcc_AddressAreaIdType addressAreaId)                                   /* PRQA S 1503 # JV-01 */
{ 
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_CANCEL_SID, MEMACC_E_UNINIT);
  }
  /* Check if addressAreaId is valid */
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_CANCEL_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
  }
  else
  #endif
  {
    /* Check if this area is pending */
    if (MEMACC_JOB_PENDING == MemAcc_GstAddrAreaData[addressAreaId].enJobStatus)                                        
    {
      /* Set cancel request flag */
      MemAcc_GstAddrAreaData[addressAreaId].blCancelRequest = MEMACC_TRUE;                                              
    }
  }
} /* End of API MemAcc_Cancel */

/***********************************************************************************************************************
** Function Name            : MemAcc_ActivateMem
**
** Service ID               : 0x14
**
** Description              : Dynamic activation and initialization of
**                            a Mem driver.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : headerAddress, hwId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : Std_ReturnType
**                            E_OK: Mem driver activation successful.
**                            E_NOT_OK: Mem driver activation failed.
**
** Preconditions            : Component must be initialized using MemAcc_Init().
**
** Global Variables Used    : MemAcc_GstVar, MemAcc_GenInitStatus, MemAcc_GpConfigPtr
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_009_ERR001, MEMACC_DUD_ACT_009_ERR007
** Reference ID             : MEMACC_DUD_ACT_009, MEMACC_DUD_ACT_009_GBL001, MEMACC_DUD_ACT_009_GBL002
** Reference ID             : MEMACC_DUD_ACT_009_GBL003, MEMACC_DUD_ACT_009_GBL004
***********************************************************************************************************************/
FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_ActivateMem(MemAcc_AddressType headerAddress, MemAcc_HwIdType hwId)     /* PRQA S 1503 # JV-01 */
{
  Std_ReturnType LenReturnValue;
  MemAcc_MemBinaryHeaderType *LpMemBinary;

  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  MemAcc_UniqueIdType *LpUniqueId;                                                                                      /* PRQA S 3678 # JV-01 */
  #endif
  /* Initialize return value */
  LenReturnValue = E_OK;
  /* Get Mem driver binary */
  LpMemBinary = (MemAcc_MemBinaryHeaderType*)headerAddress;                                                             /* PRQA S 0303 # JV-01 */

  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_ACTIVATE_MEM_SID, MEMACC_E_UNINIT);
    /* Set return to not OK */
    LenReturnValue = E_NOT_OK;
  }
  /* Validate Mem driver binary */
  else
  {
    /* Check relocated of Mem driver and validate header address */
    if (((LpMemBinary->Flags & MEMACC_RELOCATABLE_BINARY_MASK) == MEMACC_ZERO) &&                                       
      (headerAddress != (MemAcc_AddressType)LpMemBinary->Header))
    {
      LenReturnValue = E_NOT_OK;
    }

    /* Validate Unique ID */
    LpUniqueId = (MemAcc_UniqueIdType*)(&LpMemBinary->UniqueId);                                                        /* PRQA S 0310, 0312 # JV-01, JV-01 */ 
    
    if ((uint16)MEMACC_FIXED_ABI_VERSION != LpUniqueId->usABIversion)                                                   
    {
      LenReturnValue = E_NOT_OK;
    }
    else if ((uint16)MEMACC_VENDOR_ID != LpUniqueId->usVendorId)
    {
      LenReturnValue = E_NOT_OK;
    }
    else if (MEMACC_RENESAS_DRIVER_ID != LpUniqueId->ulDriverId)                                                        /* PRQA S 2004 # JV-01 */
    {
      LenReturnValue = E_NOT_OK;
    } /* else No action */

    /* Validate Delimiter */
    if ((uint64)(*((uint32*)(uint32)LpMemBinary->Delimiter)) != LpMemBinary->UniqueId)                                  /* PRQA S 0306, 0404 # JV-01, JV-01 */
    {
      LenReturnValue = E_NOT_OK;
    }
    
    /* Validate hwId out of range */
    if (hwId >= MEMACC_NUM_OF_MEM_INSTANCE)
    {
      LenReturnValue = E_NOT_OK;
    }

    if (E_NOT_OK == LenReturnValue)
    {
      /* Report error to DET if Mem binary is incorrect */
      (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID,
        MEMACC_ACTIVATE_MEM_SID, MEMACC_E_MEM_INIT_FAILED);
    }

  }

  if (E_OK == LenReturnValue)
  #endif
  {
    if (MEMACC_INDIRECT_DYNAMIC == MemAcc_GpConfigPtr->pInstInvocation[hwId])                                           
    {
      /* Initialize Mem driver */
      (*(*LpMemBinary->InitFunc))(NULL_PTR);                                                                            
      /* Store Mem driver binary address */
      MemAcc_GstVar[hwId].pMemBinary = LpMemBinary;                                                                     
      /* Set instance status to IDLE to accept request */
      MemAcc_GstVar[hwId].enInstanceStatus = MEMACC_INSTANCE_IDLE;                                                      
    }
    else
    {
      LenReturnValue = E_NOT_OK;
    }
  }
 
  return LenReturnValue;
} /* End of API MemAcc_ActivateMem */

/***********************************************************************************************************************
** Function Name            : MemAcc_DeactivateMem
**
** Service ID               : 0x15
**
** Description              : Dynamic deactivation of a Mem driver.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : hwId, headerAddress 
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : Std_ReturnType
**                            E_OK: Mem driver deactivation successful.
**                            E_NOT_OK: Mem driver deactivation failed.
**
** Preconditions            : Component must be initialized using MemAcc_Init().
**
** Global Variables Used    : MemAcc_GenInitStatus, MemAcc_GstVar, MemAcc_GpConfigPtr
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_010_ERR001, MEMACC_DUD_ACT_010, MEMACC_DUD_ACT_010_GBL001
** Reference ID             : MEMACC_DUD_ACT_010_GBL002, MEMACC_DUD_ACT_010_GBL003, MEMACC_DUD_ACT_010_GBL004
***********************************************************************************************************************/
FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_DeactivateMem(MemAcc_HwIdType hwId, MemAcc_AddressType headerAddress)   /* PRQA S 1503 # JV-01 */
{ 
  Std_ReturnType LenReturnValue;
  MemAcc_MemBinaryHeaderType *LpMemBinary;                                                                              /* PRQA S 3678 # JV-01 */

  /* Initialize return value */
  LenReturnValue = E_OK;
  /* Get Mem driver binary */
  LpMemBinary = (MemAcc_MemBinaryHeaderType*)headerAddress;                                                             /* PRQA S 0303 # JV-01 */

  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID, MEMACC_DEACTIVATE_MEM_SID, MEMACC_E_UNINIT);
    /* Set return to not OK */
    LenReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
    if ((hwId < MEMACC_NUM_OF_MEM_INSTANCE) && (MEMACC_INDIRECT_DYNAMIC == MemAcc_GpConfigPtr->pInstInvocation[hwId])   
        && (MemAcc_GstVar[hwId].enInstanceStatus == MEMACC_INSTANCE_IDLE))
    {
      /* De-Initialize Mem driver */
      (*(*LpMemBinary->DeInitFunc))();                                                                                  
      /* Reset Mem driver binary address */
      MemAcc_GstVar[hwId].pMemBinary = NULL_PTR;
      /* Set instance status to UNINIT to not accept request */
      MemAcc_GstVar[hwId].enInstanceStatus = MEMACC_INSTANCE_UNINIT;
    }
    else
    {
      LenReturnValue = E_NOT_OK;
    }
  }
 
  return LenReturnValue;
} /* End of API MemAcc_DeactivateMem */

/***********************************************************************************************************************
** Function Name            : MemAcc_HwSpecificService
**
** Service ID               : 0xe
**
** Description              : Triggers a hardware specific job request referenced by hwServiceId. Service specific
**                            data can be passed/retrieved by dataPtr.
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : addressAreaId, hwId, hwServiceId
**
** InOut Parameters         : dataPtr, lengthPtr
**
** Output Parameters        : None
**
** Return parameter         : Std_ReturnType
**                            E_OK: The requested job has been accepted by the module.
**                            E_NOT_OK: The requested job has not been accepted by the module.
**                            E_MEM_SERVICE_NOT_AVAIL: The underlying Mem driver
**                            service function is not available.
**
** Preconditions            : Component must be initialized using MemAcc_Init().
**
** Global Variables Used    : MemAcc_GenInitStatus, MemAcc_GstAddrAreaData.enJobStatus,
**                            MemAcc_GpAddressAreaConfig.usNumOfSubArea, MemAcc_GpAddressAreaConfig.pSubAreaConfig,
**                            MemAcc_GstAddrAreaData.usCurrentSubAreaIdx, MemAcc_GstAddrAreaData.enJobStatus,
**                            MemAcc_GstAddrAreaData.ulHwServiceId, MemAcc_GstAddrAreaData.pBufferAddress,
**                            MemAcc_GstAddrAreaData.pLengthPtr, MemAcc_GstAddrAreaData.enCommand
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_027_ERR001, MEMACC_DUD_ACT_027_ERR002,
** Reference ID             : MEMACC_DUD_ACT_027_ERR003,MEMACC_DUD_ACT_027_ERR004, MEMACC_DUD_ACT_027
** Reference ID             : MEMACC_DUD_ACT_027_GBL001, MEMACC_DUD_ACT_027_GBL002, MEMACC_DUD_ACT_027_GBL003
** Reference ID             : MEMACC_DUD_ACT_027_GBL004, MEMACC_DUD_ACT_027_GBL005, MEMACC_DUD_ACT_027_GBL006
** Reference ID             : MEMACC_DUD_ACT_027_GBL007, MEMACC_DUD_ACT_027_GBL008, MEMACC_DUD_ACT_027_GBL009
***********************************************************************************************************************/
FUNC(Std_ReturnType, MEMACC_PUBLIC_CODE) MemAcc_HwSpecificService(                                                      /* PRQA S 1503 # JV-01 */
  MemAcc_AddressAreaIdType addressAreaId,
  MemAcc_HwIdType hwId,
  MemAcc_MemHwServiceIdType hwServiceId,
  MemAcc_DataType* dataPtr,
  MemAcc_LengthType* lengthPtr)
{ 
  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  boolean LblSubAreaFound;
  #endif
  Std_ReturnType LenReturnValue;
  /* Local variable to hold loop count */
  uint16 LusSubAreaIdx;
  /* Pointer to sub area config */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  /* Initialize return value */
  LenReturnValue = E_OK;

  #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
  if (MEMACC_UNINIT == MemAcc_GenInitStatus)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID,
      MEMACC_HW_SPECIFIC_SERVICE_SID, MEMACC_E_UNINIT);
    /* Set return to not OK */
    LenReturnValue = E_NOT_OK;
  }
  else if (MEMACC_MAX_ADDRESS_AREA_ID < addressAreaId)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID,
                 MEMACC_HW_SPECIFIC_SERVICE_SID, MEMACC_E_PARAM_ADDRESS_AREA_ID);
    /* Set return to not OK */
    LenReturnValue = E_NOT_OK;
  }
  else if (MEMACC_JOB_PENDING == MemAcc_GstAddrAreaData[addressAreaId].enJobStatus)
  {
    /* Report to DET */
    (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID,
                 MEMACC_HW_SPECIFIC_SERVICE_SID, MEMACC_E_BUSY);
    /* Set return to not OK */
    LenReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    LblSubAreaFound = MEMACC_FALSE;
    #endif
    /* Loop through all sub-area */
    for (LusSubAreaIdx = (uint16)MEMACC_ZERO; LusSubAreaIdx <
      MemAcc_GpAddressAreaConfig[addressAreaId].usNumOfSubArea; LusSubAreaIdx++)                                        
    {
      LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[addressAreaId].pSubAreaConfig[LusSubAreaIdx];

      if (hwId == LpSubAreaConfig->enHwType)                                                                            
      {
        #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
        LblSubAreaFound = MEMACC_TRUE;
        #endif
        /* Store sub area index */
        MemAcc_GstAddrAreaData[addressAreaId].usCurrentSubAreaIdx = LusSubAreaIdx;                                      
        break;
      }
    }

    #if (MEMACC_DEV_ERROR_DETECT == STD_ON)
    if (MEMACC_FALSE == LblSubAreaFound)
    {
      /* Report to DET */
      (void)Det_ReportError(MEMACC_MODULE_ID, MEMACC_INSTANCE_ID,
                   MEMACC_HW_SPECIFIC_SERVICE_SID, MEMACC_E_PARAM_HW_ID);
      /* Set return to not OK */
      LenReturnValue = E_NOT_OK;
    }
    else
    #endif
    {
      /* Set job status to pending */
      MemAcc_GstAddrAreaData[addressAreaId].enJobStatus = MEMACC_JOB_PENDING;                                           
      /* Set request hwServiceId */
      MemAcc_GstAddrAreaData[addressAreaId].ulHwServiceId = hwServiceId;                                                
      /* Set request dataPtr */
      MemAcc_GstAddrAreaData[addressAreaId].pBufferAddress = dataPtr;                                                   
      /* Set plengthPtr = lengthPtr */
      MemAcc_GstAddrAreaData[addressAreaId].pLengthPtr = lengthPtr;                                                     
      /* Set command = MEMACC_MEMHWSPECIFIC_JOB */
      MemAcc_GstAddrAreaData[addressAreaId].enCommand = MEMACC_MEMHWSPECIFIC_JOB;                                       
    }
  }
  return LenReturnValue;
} /* End of API MemAcc_HwSpecificService */

#define MEMACC_STOP_SEC_PUBLIC_CODE
#include "MemAcc_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
