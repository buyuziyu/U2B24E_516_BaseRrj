/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22-11 X2x MCAL Components                                                          */
/* Module       = Fee.c                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains FEE related API implementations                                                                 */
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
 * 1.1.0:  30/06/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D)
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                      As part of <QAC 11.6.0> support, following changes are made
 *                      Added message 3384, removed message 2814, 3673, 3383, 2844, 2824
 * 1.0.1:  28/02/2025:  Update initiate block status in Fee_Init
 * 1.0.0:  31/12/2024:  Update check Fee_GenRequestedCmd case FEE_CMD_SWAP_ERASE_IMMEDIATE_BLOCK_DATA 
 *                      in Fee_MainFunction
 *                      Update check condition to report Det error FEE_E_INVALID_BLOCK_LEN in API Fee_Read
 * 0.0.2:  31/10/2024:  Add critical Section.
 *                      Update reference ID for all APIs.
 *                      Update Fee_Cancel - add condition for Det_ReportRuntimeError.
 * 0.0.1:  30/08/2024:  Initial Version.
 */

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Fee.h"
#include "Fee_Ram.h"
#include "NvM_MemIf.h"
/* Included for internal functions prototypes */
#include "Fee_InternalFct.h"

/* Det module */
#include "Det.h"

#include "MemAcc.h"

#if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Fee.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define FEE_C_AR_RELEASE_MAJOR_VERSION    FEE_AR_RELEASE_MAJOR_VERSION_VALUE
#define FEE_C_AR_RELEASE_MINOR_VERSION    FEE_AR_RELEASE_MINOR_VERSION_VALUE
#define FEE_C_AR_RELEASE_REVISION_VERSION FEE_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define FEE_C_SW_MAJOR_VERSION            FEE_SW_MAJOR_VERSION_VALUE
#define FEE_C_SW_MINOR_VERSION            FEE_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (FEE_AR_RELEASE_MAJOR_VERSION != FEE_C_AR_RELEASE_MAJOR_VERSION)
#error "Fee.c : Mismatch in Release Major Version"
#endif

#if (FEE_AR_RELEASE_MINOR_VERSION != FEE_C_AR_RELEASE_MINOR_VERSION)
#error "Fee.c : Mismatch in Release Minor Version"
#endif

#if (FEE_AR_RELEASE_REVISION_VERSION != FEE_C_AR_RELEASE_REVISION_VERSION)
#error "Fee.c : Mismatch in Release Revision Version"
#endif

#if (FEE_SW_MAJOR_VERSION != FEE_C_SW_MAJOR_VERSION)
#error "Fee.c : Mismatch in Software Major Version"
#endif

#if (FEE_SW_MINOR_VERSION != FEE_C_SW_MINOR_VERSION)
#error "Fee.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : #include directives should only be preceded by preprocessor directives or comments           */
/* Rule                : MISRA C:2012 Rule 20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE rule CWE-398, CWE-569                                            */
/*                       REFERENCE - ISO:C90-6.3.1 Primary Expressions                                                */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is           */
/*                       accepted.                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : [I] Cast between a pointer to object and an integral type.                                   */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE rule CWE-398, CWE-569, CWE-738                    */
/*                       REFERENCE - ISO:C90-6.3.4  Semantics                                                         */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : CERTCCM MSC01, MISRA C:2012 Rule-15.7                                                        */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3205)    : The identifier '%s' is not used and could be removed.                                        */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.3                                                  */
/* JV-01 Justification : This identifier is used by other file.                                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0604)    :  [C99] Declaration appears after statements in a compound statement.                         */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127        */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : If Msg have Level 0, 1 or 2, it can be disabled.                                             */
/*             (Except the Msg that is enforced by MISRA rule with Mandatory, Required, Advisary or or CERT-C Rules   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563      */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3397)    : Extra parentheses recommended. A binary operation is the operand of a binary operator with   */
/*                       different precedence.                                                                        */
/* Rule                : CERTCCM EXP00, MISRA C:2012 Rule-12.1, CWE Rule CWE-398, CWE-783, CWE-569                    */
/* JV-01 Justification : It is confirmed that no data loss occurs if Loss of parentheses , so it is accepted          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name         : Fee_GetVersionInfo
**
** Service ID            : 0x08
**
** Description           : Service to return the version information of the FEE module.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : VersionInfoPtr: Pointer to standard version information structure.
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Functions Invoked     : Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : FEE_DUD_ACT_008, FEE_DUD_ACT_008_ERR004
***********************************************************************************************************************/
/* SWS_Fee_00093 */
#if (FEE_VERSION_INFO_API == STD_ON)
#define FEE_START_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"
FUNC(void, FEE_PUBLIC_CODE) Fee_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, FEE_APPL_DATA) VersionInfoPtr)     /* PRQA S 1503, 3432 # JV-01, JV-01 */
{
  #if (FEE_DEV_ERROR_DETECT == STD_ON)
  /* Check if parameter passed is equal to Null pointer */
  if (NULL_PTR == VersionInfoPtr)
  {
    /* Report to DET */
    /* SWS_Fee_00147 */
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_GET_VERSIONINFO_SID, FEE_E_PARAM_POINTER);
  }
  else
  #endif /* (FEE_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Copy the vendor Id */
    VersionInfoPtr->vendorID = FEE_VENDOR_ID;
    /* Copy the module Id */
    VersionInfoPtr->moduleID = FEE_MODULE_ID;
    /* Copy Software Major Version */
    VersionInfoPtr->sw_major_version = FEE_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    VersionInfoPtr->sw_minor_version = FEE_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    VersionInfoPtr->sw_patch_version = FEE_SW_PATCH_VERSION;
  }
}
#define FEE_STOP_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (FEE_VERSION_INFO_API == STD_ON) */

/***********************************************************************************************************************
** Function Name      : Fee_Init
**
** Service ID         : 0x00
**
** Description        : Service to initialize the FEE module.
**
** Sync/Async         : Asynchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : ConfigPtr: Pointer to the selected configuration set.
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return Parameter   : None
**
** Preconditions      : Fee state shall be in FEE_UNINIT
**
** Global Variables   : Fee_GaaBlockConfig[], Fee_GenModuleState, Fee_GaaAddrAreaInfo, Fee_GaaBlockInfo,
**                      Fee_GenJobResult, Fee_GblWaitMemAccResult, Fee_GstVar, Fee_GenRequestedCmd
**
** Functions invoked  : Det_ReportError 
**
** Registers Used     : None
**
** Reference ID       : FEE_DUD_ACT_001, FEE_DUD_ACT_001_ERR008, FEE_DUD_ACT_001_GBL001
** Reference ID       : FEE_DUD_ACT_001_GBL002, FEE_DUD_ACT_001_GBL003, FEE_DUD_ACT_001_GBL004
** Reference ID       : FEE_DUD_ACT_001_GBL005, FEE_DUD_ACT_001_GBL006, FEE_DUD_ACT_001_GBL007
** Reference ID       : FEE_DUD_ACT_001_GBL008, FEE_DUD_ACT_001_GBL009, FEE_DUD_ACT_001_GBL010
** Reference ID       : FEE_DUD_ACT_001_GBL011, FEE_DUD_ACT_001_GBL012, FEE_DUD_ACT_001_GBL013
** Reference ID       : FEE_DUD_ACT_001_GBL014, FEE_DUD_ACT_001_GBL015, FEE_DUD_ACT_001_GBL016
** Reference ID       : FEE_DUD_ACT_001_GBL017, FEE_DUD_ACT_001_GBL018, FEE_DUD_ACT_001_GBL019
***********************************************************************************************************************/
/* SWS_Fee_00168: 
+ New approach to follow Figure 9.1 : In API Fee_Init: State of module change from MEMIF_UNINIT -> MEMIF_BUSY_INTERNAL 
+ In mainfuntion: State of module change MEMIF_BUSY_INTERNAL -> MEMIF_IDLE
*/
/* SWS_Fee_00085 */
#define FEE_START_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, FEE_PUBLIC_CODE) Fee_Init(P2CONST(Fee_ConfigType, AUTOMATIC, FEE_APPL_CONST) ConfigPtr)                      /* PRQA S 1503 # JV-01 */
{
  uint16 LusIndex;
  uint32 LulLoop;
  /* SWS_Fee_00189: R4.2.2 */
  /* The Configuration pointer "ConfigPtr" is currently not used and therefore shall be set NULL_PTR value */
  (void)ConfigPtr;

  /* SWS_Fee_00168: 
  Note: The FEE module's environment shall not call the function Fee_Init during a running operation 
  of the FEE module.*/
  #if (FEE_DEV_ERROR_DETECT == STD_ON)
  #if (FEE_ALREADY_INIT_DET_CHECK == STD_ON)
  if (MEMIF_UNINIT != Fee_GenModuleState)
  {
    /* Report to DET */
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_INIT_SID, FEE_E_ALREADY_INITIALIZED);
  }
  else
  #endif /* #if (FEE_ALREADY_INIT_DET_CHECK == STD_ON) */
  #endif /* #if (FEE_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Init configuration point */
    Fee_GpBlockConfig = &Fee_GaaBlockConfig[FEE_ZERO];

    /* Assign the current Address/Sub Address Area ID to ZERO to begin initialize */
    Fee_GusCurrAddrAreaId = (uint16) FEE_ZERO;
    Fee_GusCurrSubAddrAreaId = (uint16) FEE_ZERO;

    /* Assign the Block Index to ZERO to begin initialize */
    Fee_GusBlockIndex = (uint16)FEE_ZERO; 

    /* Update the current header address and data address to ZERO to begin initialize */
    Fee_GulJobRefAreaAddr = (uint32)FEE_ZERO;  
    Fee_GulJobDataAddr = (uint32)FEE_ZERO;

    /* Assign the Data buffer value to ZERO to begin initialize */
    for (LulLoop = (uint32)FEE_ZERO; (LulLoop < (uint32)FEE_DATA_BUFFER); LulLoop++)
    {
    Fee_GaaDataBuffer[LulLoop] = (uint32)FEE_ZERO;
    }
    /* For address area */
    /* Initialize for internal variable for each FEE Address Area */
    for (LusIndex = FEE_ZERO; LusIndex < FEE_MAX_DEFINED_ADDRESS_AREA_NUMBER; LusIndex++)
    {
      Fee_GaaAddrAreaInfo[LusIndex].usAddrAreaID = FEE_INVALID_ADDRESS_AREA_IDX;
      Fee_GaaAddrAreaInfo[LusIndex].usSubAddrAreaIndex = FEE_ZERO;
      Fee_GaaAddrAreaInfo[LusIndex].ulCurrHeaderAreaAddr = FEE_ZERO;

      #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON)
      Fee_GaaAddrAreaInfo[LusIndex].ulCurrDataAreaAddr = FEE_ZERO;
      #endif /* #if (FEE_WRITE_DATA_IN_REVERT_DIRECTION == STD_ON) */
    }

    /* For BLOCK */
    /* Initialize for internal variable for each FEE Block */
    for (LusIndex = FEE_ZERO; LusIndex < FEE_MAX_CONFIGURED_BLOCK_NUMBER; LusIndex++)
    {
      /* Initiate block status is FEE_BLOCK_INCONSISTENT in initialization. */
      Fee_GaaBlockInfo[LusIndex].enBlockStatus = FEE_BLOCK_INCONSISTENT;
      /* Infor of Block Configuration */
      /* Address of Header of Block: Reference Area */
      Fee_GaaBlockInfo[LusIndex].ulBlockRefAddr = FEE_ZERO;
      /* Address of Block ID: Data Area */
      Fee_GaaBlockInfo[LusIndex].ulBlockDataAddr = FEE_ZERO;
      /* Initilaize the first value for W/E Cycle */
      Fee_GaaBlockInfo[LusIndex].ulBlockWECycle = FEE_ZERO;
    }

    /* Global variable */
    /* Fee_Init is asynchronous API. It will be executed in Fee_MainFunction() */
    Fee_GenRequestedCmd = FEE_CMD_INITIALIZE;

    /* Update the current request is No pending Job to begin initialize */
    Fee_enPreviousRequestCmd = FEE_CMD_NO_PENDING;

    /* Initialize Job status */
    Fee_GenJobResult = MEMIF_JOB_OK;

    /* Update wating MemAcc result flag */
    Fee_GblWaitMemAccResult = FEE_FALSE;

    /* The status of FEE will be changed asynchronously in Fee_MainFunction(). */
    /* SWS_Fee_00168: The module state from MEMIF_UNINIT -> MEMIF_IDLE */
    /* Follow sequence: Figure 9.1: Sequence diagram of Fee_Init */
    Fee_GenModuleState = MEMIF_BUSY_INTERNAL;

    /* Initialize configure struct request Job */
    Fee_GstVar.enCmdJobRequest = FEE_CMD_NO_PENDING;
    Fee_GstVar.usBlockIndex = (uint16) FEE_ZERO;
    Fee_GstVar.usBlockOffset = (uint16) FEE_ZERO;
    Fee_GstVar.usBlockLength = (uint16) FEE_ZERO;
    Fee_GstVar.pJobReadDatatPtr = (uint8 *) NULL_PTR;
    Fee_GstVar.pJobWriteDatatPtr = (uint8 *) NULL_PTR;
  }
}
#define FEE_STOP_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name      : Fee_Read
**
** Service ID         : 0x02
**
** Description        : Service to initiate a read job.
**
** Sync/Async         : Asynchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : BlockNumber: Number of logical block, also denoting start address of that block in flash memory
**                      BlockOffset: Read address offset inside the block
**                      Length: Number of bytes to read
**
** InOut Parameters   : None
**
** Output Parameters  : DataBufferPtr: Pointer to data buffer
**
** Return Parameter   : None
**
** Preconditions      : Fee state shall be in MEMIF_IDLE/MEMIF_BUSY_INTERNAL
**
** Global Variables   : Fee_GenRequestedCmd, Fee_GenModuleState, Fee_GaaBlockConfig, Fee_GpBlockConfig, Fee_GenJobResult
**
** Functions invoked  : Det_ReportError, Det_ReportRuntimeError, Fee_GetBlockIndex
**
** Registers Used     : None
**
** Reference ID       : FEE_DUD_ACT_002, FEE_DUD_ACT_002_ERR005, FEE_DUD_ACT_002_ERR003
** Reference ID       : FEE_DUD_ACT_002_ERR004, FEE_DUD_ACT_002_ERR006, FEE_DUD_ACT_002_ERR001
** Reference ID       : FEE_DUD_ACT_002_ERR002, FEE_DUD_ACT_002_GBL001, FEE_DUD_ACT_002_GBL002
** Reference ID       : FEE_DUD_ACT_002_GBL004, FEE_DUD_ACT_002_GBL005, FEE_DUD_ACT_002_GBL003
***********************************************************************************************************************/
/* SWS_Fee_00087 */
#define FEE_START_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_Read(uint16 BlockNumber, uint16 BlockOffset,                                  /* PRQA S 1503 # JV-01 */
                                                P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr, uint16 Length)    /* PRQA S 3432 # JV-01 */
{
  /* Define a return value */
  Std_ReturnType LucReturnValue;

  #if (FEE_DEV_ERROR_DETECT == STD_ON)
  uint32 LulEndAddress;
  #endif /* #if (FEE_DEV_ERROR_DETECT == STD_ON) */

  uint16 LusBlockIndex;

  /* Initilize the first value for return */
  LucReturnValue = E_OK;

  /* SWS_Fee_00172 If not Initialization yet, SWS_Fee_00010, SWS_Fee_00122 */
  if (MEMIF_UNINIT == Fee_GenModuleState)
  {
    #if (FEE_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_READ_SID, FEE_E_UNINIT);

    #endif /* #if (FEE_DEV_ERROR_DETECT == STD_ON) */

    /* SWS_Fee_00172: Update the return value */
    LucReturnValue = E_NOT_OK;
  }
  else if (MEMIF_BUSY == Fee_GenModuleState)
  {
    /* SWS_Fee_00172: Report runtime error */
    /* SWS_Fee_91002, SWS_Fee_00133 */
    (void)Det_ReportRuntimeError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_READ_SID, FEE_E_BUSY);

    /* SWS_Fee_00172: If the current module status is MEMIF_BUSY,
    the function Fee_Read shall reject the job request and return with E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Validate Block Number */
    LusBlockIndex = Fee_GetBlockIndex(BlockNumber);

    #if (FEE_DEV_ERROR_DETECT == STD_ON)
    LulEndAddress = (uint32)BlockOffset + (uint32)Length;                                                               /* PRQA S 3384 # JV-01 */

    /* SWS_Fee_00134: checking block invalid and raise the development error FEE_E_INVALID_BLOCK_NO
      and return with E_NOT_OK. */
    /* SWS_Fee_00010 */
    if (FEE_INVALID_BLOCK_IDX == LusBlockIndex)
    {
      /* Report to DET  */
      (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_READ_SID, FEE_E_INVALID_BLOCK_NO);

      /* Update the return value */
      LucReturnValue = E_NOT_OK;
    }
    /* SWS_Fee_00135, SWS_Fee_00010 */
    else if (BlockOffset >= Fee_GpBlockConfig[LusBlockIndex].usBlockSize)
    {
      /* Report to DET  */
      (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_READ_SID, FEE_E_INVALID_BLOCK_OFS);
      
      /* Update the return value */
      LucReturnValue = E_NOT_OK;
    }
    /* SWS_Fee_00136, SWS_Fee_00010 */
    else if ((NULL_PTR == DataBufferPtr) || (((uint32)DataBufferPtr &                                                   /* PRQA S 0306 # JV-01 */
                     ((uint32)Fee_GaaBlockConfig[LusBlockIndex].ucBufferAlignmentValue - (uint32)FEE_ONE)) != FEE_ZERO))/* PRQA S 3384 # JV-01 */
    {
      /* Report to DET  */
      (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_READ_SID, FEE_E_PARAM_POINTER);

      /* Update the return value */
      LucReturnValue = E_NOT_OK;
    }
    /* SWS_Fee_00137, SWS_Fee_00010 */
    else if ((uint16)FEE_ZERO == Length || LulEndAddress > Fee_GpBlockConfig[LusBlockIndex].usBlockSize)                        /* PRQA S 2004, 3397 # JV-01, JV-01 */
    {
      /* Report to DET if Length is invalid */
      (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_READ_SID, FEE_E_INVALID_BLOCK_LEN);
      
      /* Update the return value */
      LucReturnValue = E_NOT_OK;
    }
    #endif /* #if (FEE_DEV_ERROR_DETECT == STD_ON) */
  }

  if (E_OK == LucReturnValue)
  {
    /* SWS_Fee_00187 */
    #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
    FEE_ENTER_CRITICAL_SECTION(FEE_RAM_DATA_PROTECTION);
    #endif /* #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON) */
    if (MEMIF_IDLE == Fee_GenModuleState)
    {
      Fee_GenRequestedCmd = FEE_CMD_READ;
    }


    /* SWS_Fee_00022: Set the job result to MEMIF_JOB_PENDING */
    Fee_GenJobResult = MEMIF_JOB_PENDING;

    /* SWS_Fee_00022: Set the module status to MEMIF_BUSY */
    Fee_GenModuleState = MEMIF_BUSY;

    /* Initialize configure struct request Job */
    Fee_GstVar.enCmdJobRequest = FEE_CMD_READ;
    Fee_GstVar.usBlockIndex = (uint16) LusBlockIndex;
    Fee_GstVar.usBlockOffset = (uint16) BlockOffset;
    Fee_GstVar.usBlockLength = (uint16) Length;
    Fee_GstVar.pJobReadDatatPtr = (uint8 *) DataBufferPtr;
    Fee_GstVar.pJobWriteDatatPtr = (uint8 *) NULL_PTR;

    #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
    FEE_EXIT_CRITICAL_SECTION(FEE_RAM_DATA_PROTECTION);
    #endif /* #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON) */
	
  }
  else
  {
    /* SWS_Fee_00162 */
    /* No action required */
  }

  /* Return value */
  return (LucReturnValue);
}
#define FEE_STOP_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name      : Fee_Write
**
** Service ID         : 0x03
**
** Description        : Service to initiate a write job.
**
** Sync/Async         : Asynchronous
**
** Re-entrancy        : Non-Reentrant
**
** Input Parameters   : BlockNumber: Number of logical block, also denoting start address of that block in EEPROM
**                      DataBufferPtr: Pointer to data buffer
**
** InOut Parameters   : None
**
** Output Parameters  : None
**
** Return Parameter   : None
**
** Preconditions      : Fee state shall be in MEMIF_IDLE/MEMIF_BUSY_INTERNAL
**
** Global Variables   : Fee_GstVar, Fee_GaaBlockConfig[], Fee_GenModuleState, Fee_GenJobResult, Fee_GenRequestedCmd
**
** Functions invoked  : Det_ReportError, Det_ReportRuntimeError, Fee_GetBlockIndex 
**
** Registers Used     : None
**
** Reference ID       : FEE_DUD_ACT_003, FEE_DUD_ACT_003_ERR002, FEE_DUD_ACT_003_ERR004
** Reference ID       : FEE_DUD_ACT_003_ERR001, FEE_DUD_ACT_003_ERR006, FEE_DUD_ACT_003_GBL001
** Reference ID       : FEE_DUD_ACT_003_GBL002, FEE_DUD_ACT_003_GBL003, FEE_DUD_ACT_003_GBL004
** Reference ID       : FEE_DUD_ACT_003_GBL005, FEE_DUD_ACT_003_GBL006
***********************************************************************************************************************/
/* SWS_Fee_00088 */
#define FEE_START_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_Write(uint16 BlockNumber,                                                     /* PRQA S 1503 # JV-01 */
                                                                P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST) DataBufferPtr)
{
  /* Declare a return variable */
  Std_ReturnType LucReturnValue;
  uint16 LusBlockIndex;

  /* Init return value */
  LucReturnValue = E_OK;

  /* SWS_Fee_00123, SWS_Fee_00010 */
  if (MEMIF_UNINIT == Fee_GenModuleState)
  {
    #if (FEE_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET  */
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_WRITE_SID, FEE_E_UNINIT);
    #endif /* #if (FEE_DEV_ERROR_DETECT == STD_ON) */

    /* SWS_Fee_00174: Update the return value */
    LucReturnValue = E_NOT_OK;
  }
  /* SWS_Fee_00144, SWS_Fee_91002 */
  else if (MEMIF_BUSY == Fee_GenModuleState)
  {
    /* Report runtime error */
    (void)Det_ReportRuntimeError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_WRITE_SID, FEE_E_BUSY);

    /* SWS_Fee_00174: Update the return value */
    LucReturnValue = E_NOT_OK;
  }
  else
  {
    /* Validate Block Number */
    LusBlockIndex = Fee_GetBlockIndex(BlockNumber);

    #if (FEE_DEV_ERROR_DETECT == STD_ON)
    /* SWS_Fee_00138, SWS_Fee_00010 */
    if (FEE_INVALID_BLOCK_IDX == LusBlockIndex)
    {
      /* Report to DET  */
      (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_WRITE_SID, FEE_E_INVALID_BLOCK_NO);

      /*  Update the return value */
      LucReturnValue = E_NOT_OK;
    }
    /* SWS_Fee_00139, SWS_Fee_00010 */
    else if ((NULL_PTR == DataBufferPtr) ||                                                                             /* PRQA S 2004 # JV-01 */
        (((uint32)DataBufferPtr &                                                                                       /* PRQA S 0306 # JV-01 */
                    ((uint32)Fee_GaaBlockConfig[LusBlockIndex].ucBufferAlignmentValue - (uint32)FEE_ONE)) != FEE_ZERO)) /* PRQA S 3384 # JV-01 */
    {
      /* Report to DET  */
      (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_WRITE_SID, FEE_E_PARAM_POINTER);

      /*  Update the return value */
      LucReturnValue = E_NOT_OK;
    }
    #endif /* #if (FEE_DEV_ERROR_DETECT == STD_ON) */
  }

  if (E_OK == LucReturnValue)
  {
    /* If the current module status is MEMIF_IDLE or if the current module status is MEMIF_BUSY INTERNAL,
    the function Fee_Write shall accept the write request, copy the given / computed parameters to
    module internal variables, initiate a write job */

    #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
    FEE_ENTER_CRITICAL_SECTION(FEE_RAM_DATA_PROTECTION);
    #endif /* #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* Init Job - Info */
    /* SWS_Fee_00026: Update Command - Async proceed by Mainfunction */
    if (MEMIF_IDLE == Fee_GenModuleState)
    {
      Fee_GenRequestedCmd = FEE_CMD_WRITE;
    }

    /* Update Job status to Busy */
    Fee_GenJobResult = MEMIF_JOB_PENDING;

    /* SWS_Fee_00025: Set the module status to MEMIF_BUSY */
    Fee_GenModuleState = MEMIF_BUSY;

    /* SWS_Fee_00024 */
    /* Initialize configure struct request Job */
    Fee_GstVar.enCmdJobRequest = FEE_CMD_WRITE;
    Fee_GstVar.usBlockIndex = (uint16) LusBlockIndex;
    Fee_GstVar.usBlockOffset = (uint16) FEE_ZERO;
    Fee_GstVar.usBlockLength = (uint16) FEE_ZERO;
    Fee_GstVar.pJobReadDatatPtr = (uint8 *) NULL_PTR;
    Fee_GstVar.pJobWriteDatatPtr = (const uint8 *) DataBufferPtr;
    #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
    FEE_EXIT_CRITICAL_SECTION(FEE_RAM_DATA_PROTECTION);
    #endif /* #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON) */

  }
  else
  {
    /* SWS_Fee_00163 */
    /* No action required */
  }

  /* Exit function */
  return LucReturnValue;
}
#define FEE_STOP_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fee_Cancel
**
** Service ID            : 0x04
**
** Description           : Service to call the cancel function.
**
** Sync/Async            : Asynchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : Fee_Init should be called
**
** Global Variables Used : Fee_GenModuleState, Fee_GenJobResult, Fee_GenRequestedCmd, Fee_GaaAddrAreaConfig[]
**
** Functions Invoked     : Det_ReportError, Det_ReportRuntimeError, MemAcc_Cancel
**
** Registers Used        : MemAcc_Cancel
**
** Reference ID       : FEE_DUD_ACT_004, FEE_DUD_ACT_004_ERR007, FEE_DUD_ACT_004_ERR001
** Reference ID       : FEE_DUD_ACT_004_GBL001, FEE_DUD_ACT_004_GBL002, FEE_DUD_ACT_004_GBL003
** Reference ID       : FEE_DUD_ACT_004_GBL004, FEE_DUD_ACT_004_GBL005
***********************************************************************************************************************/
/* SWS_Fee_00089 */
#define FEE_START_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, FEE_PUBLIC_CODE) Fee_Cancel(void)                                                                            /* PRQA S 1503 # JV-01 */
{
  boolean LblDetErrFlag;
  MemAcc_AddressAreaIdType LusAreaId;

  /* Initilize the first value for Det Error Report Flag */
  LblDetErrFlag = FEE_FALSE;

  #if (FEE_DEV_ERROR_DETECT == STD_ON)
  /* SWS_Fee_00124, SWS_Fee_00010 */
  if (MEMIF_UNINIT == Fee_GenModuleState)
  {
    /* Report to DET  */
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_CANCEL_SID, FEE_E_UNINIT);

    /* Set the error status flag to FEE_TRUE */
    LblDetErrFlag = FEE_TRUE;
  }
  #endif /* #if (FEE_DEV_ERROR_DETECT == STD_ON) */

  /* SWS_Fee_00164, SWS_Fee_00184, SWS_Fee_91002 */
  if (MEMIF_BUSY != Fee_GenModuleState && MEMIF_UNINIT != Fee_GenModuleState)                                           /* PRQA S 3397 # JV-01 */
  {
    /* If the current module status is not MEMIF_BUSY (i.e. the request to cancel a pending job is rejected 
    by the function), the function shall not change the current module status or job result. */
    /* SWS_Fee_00184 Report runtime error */
    (void)Det_ReportRuntimeError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_CANCEL_SID, FEE_E_INVALID_CANCEL);

    /* Set the error status flag to FEE_TRUE */
    LblDetErrFlag = FEE_TRUE;
  }

  if (FEE_FALSE == LblDetErrFlag)
  {
    /* TODO: need to check MEMIF_JOB_PENDING */
    LusAreaId = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usAddrAreaID;
    /* SWS_Fee_00080 */
    MemAcc_Cancel(LusAreaId);

    #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
    FEE_ENTER_CRITICAL_SECTION(FEE_RAM_DATA_PROTECTION);
    #endif /* #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* Update status of job is MEMIF_JOB_CANCELED */
    Fee_GenJobResult = MEMIF_JOB_CANCELED;
  
    /* Update request for Asynchronous in Main function is FEE_CMD_NO_PENDING */
    Fee_GenRequestedCmd = FEE_CMD_NO_PENDING;

    /* SWS_Fee_00081: Update the driver state is MEMIF_IDLE */
    Fee_GenModuleState = MEMIF_IDLE;
    #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
    FEE_EXIT_CRITICAL_SECTION(FEE_RAM_DATA_PROTECTION);
    #endif /* #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON) */
  }
}
#define FEE_STOP_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fee_GetStatus
**
** Service ID            : 0x05
**
** Description           : Service to return the status.
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
** Return Parameter      : MEMIF_UNINIT: The FEE module has not been initialized.
**                         MEMIF_IDLE: The FEE module is currently idle.
**                         MEMIF_BUSY: The FEE module is currently busy.
**                         MEMIF_BUSY_INTERNAL: The FEE module is busy with internal management operations.
**
** Preconditions         : None
**
** Global Variables Used : Fee_GenModuleState
**
** Functions Invoked     : None
**
** Registers Used        : None
**
** Reference ID          : FEE_DUD_ACT_005
***********************************************************************************************************************/
/* SWS_Fee_00090 */
#define FEE_START_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(MemIf_StatusType, FEE_PUBLIC_CODE) Fee_GetStatus(void)                                                             /* PRQA S 1503 # JV-01 */
{
  /* Declare Mem status */
  MemIf_StatusType LenMemIfStatus;

  /* Get from driver status variable */
  /* SWS_Fee_00034, SWS_Fee_00128, SWS_Fee_00129, SWS_Fee_00074 */
  LenMemIfStatus = Fee_GenModuleState;

  /* Return to MemIf Status */
  return LenMemIfStatus;
}
#define FEE_STOP_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fee_GetJobResult
**
** Service ID            : 0x06
**
** Description           : Service to query the result of the last accepted job issued by the upper layer software.
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
** Return Parameter      : MEMIF_JOB_OK: The last job has been finished successfully.
**                         MEMIF_JOB_PENDING: The last job is waiting for execution or currently being executed.
**                         MEMIF_JOB_CANCELED: The last job has been canceled (which means it failed).
**                         MEMIF_JOB_FAILED: The last job has not been finished successfully (it failed).
**                         MEMIF_BLOCK_INCONSISTENT: The requested block is inconsistent, it may contain corrupted data.
**                         MEMIF_BLOCK_INVALID: The requested block has been invalidated, the requested read operation 
**                         can not be performed.
**
** Preconditions         : None
**
** Global Variables Used : Fee_GenModuleState, Fee_GenJobResult
**
** Functions Invoked     : Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : FEE_DUD_ACT_006, FEE_DUD_ACT_006_ERR001
***********************************************************************************************************************/
/* SWS_Fee_00091 */
#define FEE_START_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(MemIf_JobResultType, FEE_PUBLIC_CODE) Fee_GetJobResult(void)                                                       /* PRQA S 1503 # JV-01 */
{
  /* Declare the return value */
  MemIf_JobResultType LenJobResult;

  /* SWS_Fee_00125, SWS_Fee_00010 */
  #if (FEE_DEV_ERROR_DETECT == STD_ON)
  if (MEMIF_UNINIT == Fee_GenModuleState)
  {
    /* Report to DET  */
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_GET_JOB_RESULT_SID, FEE_E_UNINIT);

    LenJobResult = MEMIF_JOB_FAILED;
  }
  else
  #endif /* #if (FEE_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Get the latest job status from global variable: Fee_GenJobResult */
    /* SWS_Fee_00035, SWS_Fee_00156, SWS_Fee_00157, SWS_Fee_00158, SWS_Fee_00159, SWS_Fee_00160 */
    /* SWS_Fee_00155: Fee_GenJobResult is only change by requested from upper layer */
    LenJobResult = Fee_GenJobResult;
  }

  /* Return value */
  return LenJobResult;
}
#define FEE_STOP_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fee_InvalidateBlock
**
** Service ID            : 0x07
**
** Description           : Service to invalidate a logical block.
**
** Sync/Async            : Asynchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : BlockNumber: Number of logical block, also denoting start address of that block in 
**                         flash memory.
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : E_OK: The requested job has been accepted by the module.
**                         E_NOT_OK - only if DET is enabled: The requested job has not
**                               been accepted by the module.
**
** Preconditions         : None
**
** Global Variables Used : Fee_GenModuleState, Fee_GenJobResult, Fee_GenRequestedCmd, Fee_GstVar
**
** Functions Invoked     : Fee_GetBlockIndex, Det_ReportError, Det_ReportRuntimeError
**
** Registers Used        : None
**
** Reference ID          : FEE_DUD_ACT_007, FEE_DUD_ACT_007_ERR001, FEE_DUD_ACT_007_ERR006
** Reference ID          : FEE_DUD_ACT_007_ERR002, FEE_DUD_ACT_007_GBL001, FEE_DUD_ACT_007_GBL002
** Reference ID          : FEE_DUD_ACT_007_GBL003, FEE_DUD_ACT_007_GBL004, FEE_DUD_ACT_007_GBL005
** Reference ID          : FEE_DUD_ACT_007_GBL006
***********************************************************************************************************************/
/* SWS_Fee_00092 */
#define FEE_START_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_InvalidateBlock(uint16 BlockNumber)                                           /* PRQA S 1503 # JV-01 */
{
  /* Declare the return value */
  Std_ReturnType LucReturnValue;

  uint16 LusBlockIndex;

  /* Initilize the return value to E_OK */
  LucReturnValue = E_OK;

  /* Validate Block Number */
  LusBlockIndex = Fee_GetBlockIndex(BlockNumber);

  #if (FEE_DEV_ERROR_DETECT == STD_ON)
  /* SWS_Fee_00126, SWS_Fee_00010 */
  /* Checking if not init */
  if (MEMIF_UNINIT == Fee_GenModuleState)
  {
    /* Report to DET  */
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_INVALIDATE_BLOCK_SID, FEE_E_UNINIT);

    /* Update the return value to E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  /* SWS_Fee_00140, SWS_Fee_00010 */
  else if (FEE_INVALID_BLOCK_IDX == LusBlockIndex)                                                                      /* PRQA S 2004 # JV-01 */
  {
    /* Report to DET  */
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_INVALIDATE_BLOCK_SID, FEE_E_INVALID_BLOCK_NO);

    /* Update the return value to E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FEE_DEV_ERROR_DETECT == STD_ON) */

  /* SWS_Fee_00145, SWS_Fee_91002 */
  if (MEMIF_BUSY == Fee_GenModuleState)
  {
    /* Report runtime error */
    (void)Det_ReportRuntimeError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_INVALIDATE_BLOCK_SID, FEE_E_BUSY);

    /* Update the return value to E_NOT_OK */
    LucReturnValue = E_NOT_OK;
  }

  /* SWS_Fee_00192 */
  if (E_OK == LucReturnValue)
  {
    /* The function Fee_InvalidateBlock shall check if the module state is MEMIF_IDLE or MEMIF_BUSY_INTERNAL.
    If this is the case the module shall accept the invalidation request and shall return E_OK to the caller */
    /* SWS_Fee_00192 */

    #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
    FEE_ENTER_CRITICAL_SECTION(FEE_RAM_DATA_PROTECTION);
    #endif /* #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON) */
    /* SWS_Fee_00193: Update Command - Async proceed by Mainfunction */
    if (MEMIF_IDLE == Fee_GenModuleState)
    {
      Fee_GenRequestedCmd = FEE_CMD_INVALIDATE;
    }

    /* Update Job status to Busy */
    Fee_GenJobResult = MEMIF_JOB_PENDING;

    /* Update Driver status to MEMIF_BUSY */
    Fee_GenModuleState = MEMIF_BUSY;

    /* SWS_Fee_00036 */
    /* Initialize configure struct request Job */
    Fee_GstVar.enCmdJobRequest = FEE_CMD_INVALIDATE;
    Fee_GstVar.usBlockIndex = (uint16) LusBlockIndex;
    Fee_GstVar.usBlockOffset = FEE_ZERO;
    Fee_GstVar.usBlockLength = FEE_ZERO;
    Fee_GstVar.pJobReadDatatPtr = (uint8 *) NULL_PTR;
    Fee_GstVar.pJobWriteDatatPtr = (uint8 *) NULL_PTR;

    #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
    FEE_EXIT_CRITICAL_SECTION(FEE_RAM_DATA_PROTECTION);
    #endif /* #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON) */
  }
  else
  {
    /* SWS_Fee_00165 */
    /* No action required */
  }

  /* Return value */
  return LucReturnValue;
}
#define FEE_STOP_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fee_EraseImmediateBlock
**
** Service ID            : 0x09
**
** Description           : Service to erase a logical block.
**
** Sync/Async            : Asynchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : BlockNumber: Number of logical block, also denoting start address of that block in EEPROM.
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : E_OK: The requested job has been accepted by the module.
**                         E_NOT_OK - only if DET is enabled: The requested job has not been accepted by the module.
**
** Preconditions         : None
**
** Global Variables Used : Fee_GenModuleState, Fee_GenRequestedCmd, Fee_GenJobResult, Fee_GstVar, Fee_GpBlockConfig[]
**
** Functions Invoked     : Det_ReportError, Fee_GetBlockIndex, Det_ReportRuntimeError
**
** Registers Used        : None
**
** Reference ID          : FEE_DUD_ACT_009, FEE_DUD_ACT_009_ERR002, FEE_DUD_ACT_009_ERR006
** Reference ID          : FEE_DUD_ACT_009_ERR001, FEE_DUD_ACT_009_GBL001, FEE_DUD_ACT_009_GBL002
** Reference ID          : FEE_DUD_ACT_009_GBL003, FEE_DUD_ACT_009_GBL004, FEE_DUD_ACT_009_GBL005
** Reference ID          : FEE_DUD_ACT_009_GBL006
***********************************************************************************************************************/
/* Note: The function Fee_EraseImmediateBlock shall only be called by e.g. diagnostic or similar system service to
pre-erase the area for immediate data if necessary. */
#define FEE_START_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_EraseImmediateBlock(uint16 BlockNumber)                                       /* PRQA S 1503 # JV-01 */
{
  /* Declare the return value */
  Std_ReturnType LucReturnValue;

  uint16 LusBlockIndex;

  /* Initialize the return value */
  LucReturnValue = E_OK;

  /* Validate Block Number */
  LusBlockIndex = Fee_GetBlockIndex(BlockNumber);

  /* SWS_Fee_00127, SWS_Fee_00010 */
  #if (FEE_DEV_ERROR_DETECT == STD_ON)
  if (MEMIF_UNINIT == Fee_GenModuleState)
  {
    /* Report to DET  */
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_ERASE_IMMEDIATE_BLOCK_SID, FEE_E_UNINIT);

    /* Update the return value */
    LucReturnValue = E_NOT_OK;
  }
  /* SWS_Fee_00068, SWS_Fee_00010, SWS_Fee_00141 */
  else if (FEE_INVALID_BLOCK_IDX == LusBlockIndex)
  {
    /* Report to DET  */
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_ERASE_IMMEDIATE_BLOCK_SID, FEE_E_INVALID_BLOCK_NO);

    /* Update the return value */
    LucReturnValue = E_NOT_OK;
  }
  /* SWS_Fee_00010 */
  else if (FALSE == Fee_GpBlockConfig[LusBlockIndex].blImmeData)                                                        /* PRQA S 2004 # JV-01 */
  {
    /* Report to DET  */
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_ERASE_IMMEDIATE_BLOCK_SID, FEE_E_INVALID_BLOCK_NO);

    /* Update the return value */
    LucReturnValue = E_NOT_OK;
  }
  #endif /* #if (FEE_DEV_ERROR_DETECT == STD_ON) */

  /* SWS_Fee_00146, SWS_Fee_91002 */
  if (MEMIF_BUSY == Fee_GenModuleState)
  {
    /* Report runtime error - NOT FEE_E_BUSY::R_EEL_STATUS_BUSY */
    (void)Det_ReportRuntimeError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_ERASE_IMMEDIATE_BLOCK_SID, FEE_E_BUSY);
    LucReturnValue = E_NOT_OK;
  }

  if (E_OK == LucReturnValue)
  {
    /* SWS_Fee_00067: The function Fee_EraseImmediateBlock shall ensure that the FEE module can write immediate data.
     Whether this involves physically erasing a memory area and therefore calling the erase function of the
     underlying driver depends on the implementation of the module */

    #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
    FEE_ENTER_CRITICAL_SECTION(FEE_RAM_DATA_PROTECTION);
    #endif /* #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON) */

    /* Update Command - Async proceed by Mainfunction */
    if (MEMIF_IDLE == Fee_GenModuleState)
    {
      Fee_GenRequestedCmd = FEE_CMD_ERASE_IMMEDIATE;
    }

    /* Update Job status to Busy */
    Fee_GenJobResult = MEMIF_JOB_PENDING;

    /* Update the Driver status */
    Fee_GenModuleState = MEMIF_BUSY;

    /* SWS_Fee_00066 */
    /* Initialize configure struct request Job */
    Fee_GstVar.enCmdJobRequest = FEE_CMD_ERASE_IMMEDIATE;
    Fee_GstVar.usBlockIndex = (uint16) LusBlockIndex;
    Fee_GstVar.usBlockOffset = FEE_ZERO;
    Fee_GstVar.usBlockLength = FEE_ZERO;
    Fee_GstVar.pJobReadDatatPtr = (uint8 *) NULL_PTR;
    Fee_GstVar.pJobWriteDatatPtr = (uint8 *) NULL_PTR;

    #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
    FEE_EXIT_CRITICAL_SECTION(FEE_RAM_DATA_PROTECTION);
    #endif /* #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON) */
  }
  else
  {
    /* SWS_Fee_00166 */
    /* No action required */
  }

  /* Return value */
  return LucReturnValue;
}
#define FEE_STOP_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Fee_MainFunction
**
** Service ID            : 0x12
**
** Description           : Service to handle the requested read/write/erase jobs and the internal management operations
**
** Sync/Async            : Asynchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fee_GenJobResult, Fee_GenRequestedCmd, Fee_GenModuleState, Fee_GaaAddrAreaConfig[],
**                       : Fee_GusCurrAddrAreaId
**
** Functions Invoked     : Det_ReportError, MemAcc_GetJobStatus, MemAcc_GetJobResult,
**                         Fee_JobReadMain, Fee_WriteUnalignedBlockData, Fee_JobWriteValidateBlock
**                         Fee_JobWriteDone, Fee_JobEraseImmediate, Fee_JobInvalidateBlock
**                         Fee_JobInvalidateBlockDone    
**
** Registers Used        : None
**
** Reference ID          : FEE_DUD_ACT_010
***********************************************************************************************************************/
#define FEE_START_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, FEE_PUBLIC_CODE) Fee_MainFunction(void)                                                                      /* PRQA S 1503 # JV-01 */
{
  MemIf_JobResultType LenJobResult;

  /* If there is a job - on going */
  if ((MEMIF_BUSY == Fee_GenModuleState) || (MEMIF_BUSY_INTERNAL == Fee_GenModuleState))
  {
    /* Initialize local job result */
    LenJobResult = MEMIF_JOB_PENDING;   
    if (FEE_FALSE == Fee_GblWaitMemAccResult)
    {
      /* SWS_Fee_00057 */
      if ((Fee_GenRequestedCmd >= FEE_CMD_INITIALIZE) && (Fee_GenRequestedCmd <= FEE_CMD_SWAP_DONE))
      {
        /* Handle SWAP related commands */
        LenJobResult = Fee_HandleInternalManagementCommands();
      }
      else
      {
        switch (Fee_GenRequestedCmd)
        {
          /* Fee_Read() related jobs */
          case FEE_CMD_READ:
              LenJobResult = Fee_JobReadMain();
              break;
          case FEE_CMD_READ_DONE:
              LenJobResult = Fee_JobReadDone();
              break;
          /* Fee_Write() related jobs */
          case FEE_CMD_WRITE:
              LenJobResult = Fee_JobWriteMain();
              break;
          case FEE_CMD_WRITE_BLOCK_DATA:
              LenJobResult = Fee_JobWriteBlockData();
              break;
          case FEE_CMD_WRITE_UNALIGNED_BLOCK:
              LenJobResult = Fee_WriteUnalignedBlockData();
              break;
          case FEE_CMD_WRITE_VALIDATE_BLOCK:
              LenJobResult = Fee_JobWriteValidateBlock();
              break;
          case FEE_CMD_WRITE_DONE:
              LenJobResult = Fee_JobWriteDone();
              break;
          /* Fee_InvalidateBlock() related jobs */
          case FEE_CMD_INVALIDATE:
              LenJobResult = Fee_JobInvalidateBlock();
              break;
          case FEE_CMD_INVALIDATE_DONE:
              LenJobResult = Fee_JobInvalidateBlockDone();
              break;
          /* Fee_EraseImmediateBlock() related jobs */
          case FEE_CMD_ERASE_IMMEDIATE:
              LenJobResult = Fee_JobEraseImmediate();
              break;
          case FEE_CMD_SWAP_ERASE_IMMEDIATE_BLOCK_DATA:
              LenJobResult = Fee_JobEraseImmediate();
              break;
          case FEE_CMD_NO_PENDING:
          default:
              /* Do nothing command */
              break;
        }
      }
    }
    /* Check the job result and handle accordingly */
    Fee_CheckMemIfJobResult(LenJobResult);
  }
}
#define FEE_STOP_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
*                                                 CALLBACK FUNCTIONS                                                   *
***********************************************************************************************************************/
#if (FEE_POLLING_MODE == STD_OFF)
/***********************************************************************************************************************
** Function Name         : Fee_JobEndNotification
**
** Service ID            : 0x10
**
** Description           : Service to report to this module the successful end of an asynchronous operation.
**
** Sync/Async            : Asynchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return Parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Fee_GaaAddrAreaConfig[], Fee_GenJobResult, Fee_GenModuleState, Fee_GenRequestedCmd,
**                       : Fee_GblWaitMemAccResult
**
** Functions Invoked     : Det_ReportError, MemAcc_GetJobResult
**
** Registers Used        : None
**
** Reference ID          : FEE_DUD_ACT_011, FEE_DUD_ACT_011_GBL001, FEE_DUD_ACT_011_GBL002
** Reference ID          : FEE_DUD_ACT_011_GBL003, FEE_DUD_ACT_011_GBL004, FEE_DUD_ACT_011_GBL005
***********************************************************************************************************************/
/* SWS_Fee_00095 Callback Function */
#define FEE_START_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, FEE_PUBLIC_CODE) Fee_JobEndNotification(void)                                                                /* PRQA S 1503 # JV-01 */
{
  MemAcc_AddressAreaIdType LusAddressAreaId;
  /* Declare the value of MemAcc job result */
  MemAcc_JobResultType LenMemAccJobResult;

  LusAddressAreaId = Fee_GaaAddrAreaConfig[Fee_GusCurrAddrAreaId].usAddrAreaID;

  /* Get MemAcc job result */
  LenMemAccJobResult = MemAcc_GetJobResult(LusAddressAreaId);

  #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
  FEE_ENTER_CRITICAL_SECTION(FEE_RAM_DATA_PROTECTION);
  #endif /* #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON) */
  if (MEMACC_MEM_OK != LenMemAccJobResult)
  {
    /* Set the JOB result as failed */
    Fee_GenJobResult = MEMIF_JOB_FAILED;

    if (MEMIF_BUSY_INTERNAL != Fee_GenModuleState)
    {
      /* Call job error notification function */
      FEE_CALLBACK_ERROR_NOTIFICATION;
    }
    /* Update final status */
    Fee_GenModuleState = MEMIF_IDLE;
    
    /* Stop current operation */
    Fee_GenRequestedCmd = FEE_CMD_NO_PENDING;
  }

  /* Reset MemAcc flag */
  Fee_GblWaitMemAccResult = FEE_FALSE;
  
  #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON)
  FEE_EXIT_CRITICAL_SECTION(FEE_RAM_DATA_PROTECTION);
  #endif /* #if (FEE_CRITICAL_SECTION_PROTECTION == STD_ON) */
}
#define FEE_STOP_SEC_PUBLIC_CODE
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* #if (FEE_POLLING_MODE == STD_OFF) */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
