/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22-11 X2x MCAL Components                                                          */
/* Module       = MemAcc_Control.c                                                                                    */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains internal functions.                                                                             */
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
 * 1.1.0:  30/06/2025:  Update sequence of MemAcc_ProcessWriteJob to check align with MemWriteBurstSize
 *                      before request to Mem driver
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
                        Add message 0404, remove 2814, 2824, 2844 to support QA-C version 11.6.0
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024:  Update to correct file name in Version Check. 
 * 0.0.2:  31/10/2024:  Update to flow of MemAcc_ProcessReadJob to support MemAccUseReadBurst parameter.
 *                      Add call JobEndNotification after calling services from Mem with return value is E_NOT_OK
 *                      Update to call services to Mem with Mem prefix name.
 *                      Update to support macro MEMACC_COMPARE_API
 *                      Update MemAcc_ProcessJobOk to set job result to MEMACC_MEM_INCONSISTENT when compared data is
 *                      miss match.
 *                      Add MemAcc_CheckCancelRequest, MemAcc_SelectAreaToProcess function
 * 0.0.1:  30/08/2024:  Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for pre-compile options */
#include "MemAcc_PBTypes.h"
/* Included prototypes for internal functions of Flash Wrapper Component */
#include "MemAcc.h"
/* Included for RAM variable declarations */
#include "MemAcc_Ram.h"
/* Included prototypes for FCU functions of Flash Wrapper Component */
#include "MemAcc_Types.h"
/* Included prototypes for FCU functions of Flash Wrapper Component */
#include "Mem_59_Renesas.h"
#include "MemAcc_Control.h"


/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MEMACC_CONTROL_C_AR_RELEASE_MAJOR_VERSION    MEMACC_AR_RELEASE_MAJOR_VERSION_VALUE
#define MEMACC_CONTROL_C_AR_RELEASE_MINOR_VERSION    MEMACC_AR_RELEASE_MINOR_VERSION_VALUE
#define MEMACC_CONTROL_C_AR_RELEASE_REVISION_VERSION MEMACC_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MEMACC_CONTROL_C_SW_MAJOR_VERSION            MEMACC_SW_MAJOR_VERSION_VALUE
#define MEMACC_CONTROL_C_SW_MINOR_VERSION            MEMACC_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (MEMACC_CONTROL_AR_RELEASE_MAJOR_VERSION != MEMACC_CONTROL_C_AR_RELEASE_MAJOR_VERSION)
  #error "MemAcc_Control.c : Mismatch in Release Major Version"
#endif

#if (MEMACC_CONTROL_AR_RELEASE_MINOR_VERSION != MEMACC_CONTROL_C_AR_RELEASE_MINOR_VERSION)
  #error "MemAcc_Control.c : Mismatch in Release Minor Version"
#endif

#if (MEMACC_CONTROL_AR_RELEASE_REVISION_VERSION != MEMACC_CONTROL_C_AR_RELEASE_REVISION_VERSION)
  #error "MemAcc_Control.c : Mismatch in Release Revision Version"
#endif

#if (MEMACC_CONTROL_SW_MAJOR_VERSION != MEMACC_CONTROL_C_SW_MAJOR_VERSION)
  #error "MemAcc_Control.c : Mismatch in Software Major Version"
#endif

#if (MEMACC_CONTROL_SW_MINOR_VERSION != MEMACC_CONTROL_C_SW_MINOR_VERSION)
  #error "MemAcc_Control.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : MISRA C:2012 Rule-15.7, CERTCCM MSC01, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : MISRA C:2012 Rule-18.4, CERTCCM EXP08, CWE Rule CWE-188, CWE-398, CWE-569                    */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used following AUTOSAR standard rule. It is accepted.*/
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
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : MISRA C:2012 Rule-8.7, CERTCCM DCL19, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2993)    : The value of this 'do - while' loop controlling expression is always 'false'. The loop will  */
/*                       only be executed once.                                                                       */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : This loop will only be executed atleast once, depends on user configuration.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2996)    : The result of this logical operation is always 'false'.                                      */
/* Rule                : MISRA C:2012 Rule-2.2, CWE Rule CWE-561, CWE-633                                             */
/* JV-01 Justification : Depending on device status, there is case where the 'if' will return 'true'.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : MISRA C:2012 Dir-4.1, CERTCCM MSC07, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP39, EXP11, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
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
#define MEMACC_START_SEC_PRIVATE_CODE
#include "MemAcc_MemMap.h"

/*****************************************************************************
** Function Name            : MemAcc_ProcessReadJob
**
** Service ID               : NA
**
** Description              : NA
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : LulInstanceId
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variable(s) Used  : MemAcc_GstVar.usProcessingAreaId, MemAcc_GstAddrAreaData.usCurrentSubAreaIdx,
** Global Variable(s) Used  : MemAcc_GpAddressAreaConfig.pSubAreaConfig, MemAcc_GstAddrAreaData.ddCurrentAddress,
** Global Variable(s) Used  : MemAcc_GstAddrAreaData.ddRemainingLength, MemAcc_GstAddrAreaData.ddMemRequestedLength,
** Global Variable(s) Used  : MemAcc_GstAddrAreaData.pBufferAddress, MemAcc_GpConfigPtr->pInstInvocation,
** Global Variable(s) Used  : MemAcc_GstVar.pMemBinary, MemAcc_GstAddrAreaData.blWaitingMemResult,
** Global Variable(s) Used  : MemAcc_GstAddrAreaData.enJobResult, MemAcc_GstAddrAreaData.enJobStatus,
** Global Variable(s) Used  : MemAcc_GstAddrAreaData.enCommand
**
** Function(s) invoked      : Mem_59_Renesas_Read
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_020, MEMACC_DUD_ACT_020_GBL001, MEMACC_DUD_ACT_020_GBL002
** Reference ID             : MEMACC_DUD_ACT_020_GBL003, MEMACC_DUD_ACT_020_GBL004, MEMACC_DUD_ACT_020_GBL005
** Reference ID             : MEMACC_DUD_ACT_020_GBL006, MEMACC_DUD_ACT_020_GBL007, MEMACC_DUD_ACT_020_GBL008
** Reference ID             : MEMACC_DUD_ACT_020_GBL009, MEMACC_DUD_ACT_020_GBL010, MEMACC_DUD_ACT_020_GBL011
** Reference ID             : MEMACC_DUD_ACT_020_GBL012, MEMACC_DUD_ACT_020_GBL013, MEMACC_DUD_ACT_020_GBL014
** Reference ID             : MEMACC_DUD_ACT_020_GBL015, MEMACC_DUD_ACT_020_GBL016
********************************************************************************/
FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessReadJob(Mem_59_Renesas_InstanceIdType LulInstanceId)                         
{
  Std_ReturnType LenStdResult;
  uint16 LusAreaId;
  uint16 LusSubAreaIdx;
  MemAcc_AddressType LddAddress;
  MemAcc_LengthType LddLength;
  /* Pointer to sub-area */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;
  P2VAR(Mem_59_Renesas_DataType, AUTOMATIC, MEMACC_APPL_DATA) pReadBuffer;                                              /* PRQA S 3432 # JV-01 */

  /* Get processing area id */
  LusAreaId = MemAcc_GstVar[LulInstanceId].usProcessingAreaId;                                                          
  /* Get current sub-area index */
  LusSubAreaIdx = MemAcc_GstAddrAreaData[LusAreaId].usCurrentSubAreaIdx;                                                
  /* Get sub-area config */
  LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[LusAreaId].pSubAreaConfig[LusSubAreaIdx];                               
  /* Get current address */
  LddAddress = MemAcc_GstAddrAreaData[LusAreaId].ddCurrentAddress;
  /* Calculate remaining sub-area length */
  LddLength = LpSubAreaConfig->ddSubAreaLength - (LddAddress - LpSubAreaConfig->ddLogicStartAddr);                      /* PRQA S 3383 # JV-01 */

  /* Remaining area is only on this sub-area */
  if (MemAcc_GstAddrAreaData[LusAreaId].ddRemainingLength <= LddLength)
  {
    if (MemAcc_GstAddrAreaData[LusAreaId].ddRemainingLength < LpSubAreaConfig->ulMemReadBurstSize)
    {
      LddLength = LpSubAreaConfig->ulMemReadPageSize;
    }
    else
    {
      LddLength = LpSubAreaConfig->ulMemReadBurstSize;
    }
  }
  /* Remaining area is not only on this sub-area */
  else
  {
    if (LpSubAreaConfig->ulMemReadBurstSize <= LddLength)
    {
      LddLength = LpSubAreaConfig->ulMemReadBurstSize;
    } 
    else
    {
      LddLength = LpSubAreaConfig->ulMemReadPageSize;
    }
  }
  
  /* Store requested lenth */
  MemAcc_GstAddrAreaData[LusAreaId].ddMemRequestedLength = LddLength;                                                   

  /* Convert logical address to physical address */
  LddAddress = (LddAddress - LpSubAreaConfig->ddLogicStartAddr) + LpSubAreaConfig->ddPhysicalStartAddr;                 /* PRQA S 3383 # JV-01 */
  
  if (MEMACC_READ_JOB == MemAcc_GstAddrAreaData[LusAreaId].enCommand)
  {
    pReadBuffer = (Mem_59_Renesas_DataType*)MemAcc_GstAddrAreaData[LusAreaId].pBufferAddress;
    
  }
  #if (MEMACC_COMPARE_API == STD_ON)
  else /* Compare job */
  {
    pReadBuffer = (Mem_59_Renesas_DataType*)MemAcc_CompareBuffer;                                                       /* PRQA S 0751 # JV-01 */
  }
  #endif /* #if (MEMACC_COMPARE_API == STD_ON) */

  /* Request read to Mem driver */
  if (MEMACC_DIRECT_STATIC == MemAcc_GpConfigPtr->pInstInvocation[LulInstanceId])                                       
  {
    LenStdResult = MEMACC_MEM_API_REQUEST(MEMACC_MEM_PREFIX_NAME, Read)(LulInstanceId, LddAddress, pReadBuffer, LddLength);
  }
  else
  {
    LenStdResult = (*(MemAcc_GstVar[LulInstanceId].pMemBinary->ReadFunc))(                                              /* PRQA S 0404 # JV-01 */
      LulInstanceId, LddAddress, pReadBuffer, LddLength);
  }
  
  /* Mem driver accept read request */
  if (E_OK == LenStdResult)
  {
    /* Set flag for waiting result from Mem driver */
    MemAcc_GstAddrAreaData[LusAreaId].blWaitingMemResult = MEMACC_TRUE;                                                 
  }
  else
  {
    MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_FAILED;                                                  
    MemAcc_GstAddrAreaData[LusAreaId].enJobStatus = MEMACC_JOB_IDLE;                                                    
    MemAcc_GstAddrAreaData[LusAreaId].enCommand = MEMACC_NO_JOB;                                                        
    /* Call job end notification callback */
    if (NULL_PTR != MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer)                                   
    {
      MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer(                                                 
                    LusAreaId, MemAcc_GstAddrAreaData[LusAreaId].enJobResult);
    }
  }
} /* End of API MemAcc_ProcessReadJob */

/*******************************************************************************
** Function Name             : MemAcc_ProcessEraseJob
**
** Service ID                : NA
**
** Description               : NA
**                             
** Sync/Async                : Asynchronous
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
** Global Variables Used     : MemAcc_GstVar.usProcessingAreaId, MemAcc_GstAddrAreaData.usCurrentSubAreaIdx, MemAcc_GpAddressAreaConfig.pSubAreaConfig, MemAcc_GstAddrAreaData.ddCurrentAddress, MemAcc_GstAddrAreaData.ddRemainingLength, MemAcc_GstAddrAreaData.ddMemRequestedLength, MemAcc_GpConfigPtr->pInstInvocation, MemAcc_GstVar.pMemBinary, MemAcc_GstAddrAreaData.blWaitingMemResult,  MemAcc_GstAddrAreaData.enJobResult, MemAcc_GstAddrAreaData.enJobStatus, MemAcc_GstAddrAreaData.enCommand
**
** Function(s) invoked       : Mem_59_Renesas_Erase
**
**
** Registers Used            : None
**
** Reference ID              : MEMACC_DUD_ACT_021, MEMACC_DUD_ACT_021_GBL001, MEMACC_DUD_ACT_021_GBL002
** Reference ID              : MEMACC_DUD_ACT_021_GBL003, MEMACC_DUD_ACT_021_GBL004, MEMACC_DUD_ACT_021_GBL005
** Reference ID              : MEMACC_DUD_ACT_021_GBL006, MEMACC_DUD_ACT_021_GBL007, MEMACC_DUD_ACT_021_GBL008
** Reference ID              : MEMACC_DUD_ACT_021_GBL009, MEMACC_DUD_ACT_021_GBL010, MEMACC_DUD_ACT_021_GBL011
** Reference ID              : MEMACC_DUD_ACT_021_GBL012
**************************************************************************************/
FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessEraseJob(Mem_59_Renesas_InstanceIdType LulInstanceId)                     
{
  Std_ReturnType LenStdResult;
  uint16 LusAreaId;
  uint16 LusSubAreaIdx;
  MemAcc_AddressType LddAddress;
  MemAcc_LengthType LddLength;
  /* Pointer to sub-area */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  /* Get processing area id */
  LusAreaId = MemAcc_GstVar[LulInstanceId].usProcessingAreaId;                                                          
  /* Get current sub-area index */
  LusSubAreaIdx = MemAcc_GstAddrAreaData[LusAreaId].usCurrentSubAreaIdx;                                                
  /* Get sub-area config */
  LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[LusAreaId].pSubAreaConfig[LusSubAreaIdx];                               
  /* Get current address */
  LddAddress = MemAcc_GstAddrAreaData[LusAreaId].ddCurrentAddress;
  /* Calculate remaining sub-area length */
  LddLength = LpSubAreaConfig->ddSubAreaLength - (LddAddress - LpSubAreaConfig->ddLogicStartAddr);                      /* PRQA S 3383 # JV-01 */

  /* Remaining area is only on this sub-area */
  if (MemAcc_GstAddrAreaData[LusAreaId].ddRemainingLength <= LddLength)
  {
    if (MemAcc_GstAddrAreaData[LusAreaId].ddRemainingLength < LpSubAreaConfig->ulMemEraseBurstSize)
    {
      LddLength = LpSubAreaConfig->ulMemEraseSectorSize; 
    }
    else
    {
      LddLength = LpSubAreaConfig->ulMemEraseBurstSize;
    }
  }
  /* Remaining area is not only on this sub-area */
  else
  {
    if (LpSubAreaConfig->ulMemEraseBurstSize <= LddLength)
    {
      LddLength = LpSubAreaConfig->ulMemEraseBurstSize;
    }
    else
    {
      LddLength = LpSubAreaConfig->ulMemEraseSectorSize;
    }
  }
  
  /* Store requested lenth */
  MemAcc_GstAddrAreaData[LusAreaId].ddMemRequestedLength = LddLength;                                                   

  /* Convert logical address to physical address */
  LddAddress = (LddAddress - LpSubAreaConfig->ddLogicStartAddr) + LpSubAreaConfig->ddPhysicalStartAddr;                 /* PRQA S 3383 # JV-01 */
  /* Request erase to Mem driver */
  if (MEMACC_DIRECT_STATIC == MemAcc_GpConfigPtr->pInstInvocation[LulInstanceId])                                       
  {
    LenStdResult = MEMACC_MEM_API_REQUEST(MEMACC_MEM_PREFIX_NAME, Erase)(LulInstanceId, LddAddress, LddLength);
  }
  else
  {
    LenStdResult = (*(MemAcc_GstVar[LulInstanceId].pMemBinary->EraseFunc))(                                             /* PRQA S 0404 # JV-01 */
      LulInstanceId, LddAddress, LddLength);
  }
  
  /* Mem driver accept erase request */
  if (E_OK == LenStdResult)
  {
    /* Set flag for waiting result from Mem driver */
    MemAcc_GstAddrAreaData[LusAreaId].blWaitingMemResult = MEMACC_TRUE;                                                 
  }
  else
  {
    MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_FAILED;                                                      
    MemAcc_GstAddrAreaData[LusAreaId].enJobStatus = MEMACC_JOB_IDLE;                                                    
    MemAcc_GstAddrAreaData[LusAreaId].enCommand = MEMACC_NO_JOB;                                                        
    /* Call job end notification callback */
    if (NULL_PTR != MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer)                                   
    {
      MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer(                                                 
                    LusAreaId, MemAcc_GstAddrAreaData[LusAreaId].enJobResult);
    }
  }
} /* End of API MemAcc_ProcessEraseJob */
/*******************************************************************************
** Function Name             : MemAcc_ProcessWriteJob
**
** Service ID                : NA
**
** Description               : NA
**                         
**
** Sync/Async                : Asynchronous
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
** Global Variables Used     : MemAcc_GstVar.usProcessingAreaId, MemAcc_GstAddrAreaData.usCurrentSubAreaIdx, MemAcc_GpAddressAreaConfig.pSubAreaConfig, MemAcc_GstAddrAreaData.ddCurrentAddress, MemAcc_GstAddrAreaData.ddRemainingLength, MemAcc_GstAddrAreaData.ddMemRequestedLength, MemAcc_GstAddrAreaData.pBufferAddress, MemAcc_GpConfigPtr->pInstInvocation, MemAcc_GstVar.pMemBinary, MemAcc_GstAddrAreaData.pReadOnlyBufferAddr MemAcc_GstAddrAreaData.blWaitingMemResult,  MemAcc_GstAddrAreaData.enJobResult, MemAcc_GstAddrAreaData.enJobStatus, MemAcc_GstAddrAreaData.enCommand
**
** Function(s) invoked       : Mem_59_Renesas_Write
**
**
** Registers Used            : None
**
** Reference ID             : MEMACC_DUD_ACT_022, MEMACC_DUD_ACT_022_GBL001, MEMACC_DUD_ACT_022_GBL002
** Reference ID             : MEMACC_DUD_ACT_022_GBL003, MEMACC_DUD_ACT_022_GBL004, MEMACC_DUD_ACT_022_GBL005
** Reference ID             : MEMACC_DUD_ACT_022_GBL006, MEMACC_DUD_ACT_022_GBL007
** Reference ID             : MEMACC_DUD_ACT_022_GBL009, MEMACC_DUD_ACT_022_GBL010, MEMACC_DUD_ACT_022_GBL011
** Reference ID             : MEMACC_DUD_ACT_022_GBL012, MEMACC_DUD_ACT_022_GBL013
**************************************************************************************/
FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessWriteJob(Mem_59_Renesas_InstanceIdType LulInstanceId)                     
{
  Std_ReturnType LenStdResult;
  uint16 LusAreaId;
  uint16 LusSubAreaIdx;
  MemAcc_AddressType LddAddress;
  MemAcc_LengthType LddLength;
  /* Pointer to sub-area */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  /* Get processing area id */
  LusAreaId = MemAcc_GstVar[LulInstanceId].usProcessingAreaId;                                                          
  /* Get current sub-area index */
  LusSubAreaIdx = MemAcc_GstAddrAreaData[LusAreaId].usCurrentSubAreaIdx;                                                
  /* Get sub-area config */
  LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[LusAreaId].pSubAreaConfig[LusSubAreaIdx];                               
  /* Get current address */
  LddAddress = MemAcc_GstAddrAreaData[LusAreaId].ddCurrentAddress;
  /* Calculate remaining sub-area length */
  LddLength = LpSubAreaConfig->ddSubAreaLength - (LddAddress - LpSubAreaConfig->ddLogicStartAddr);                      /* PRQA S 3383 # JV-01 */
  /* Convert logical address to physical address */
  LddAddress = (LddAddress - LpSubAreaConfig->ddLogicStartAddr) + LpSubAreaConfig->ddPhysicalStartAddr;                 /* PRQA S 3383 # JV-01 */

  /* In case address not align with burst size => only request to Mem with page size */
  if (MEMACC_ZERO != (LddAddress & (LpSubAreaConfig->ulMemWriteBurstSize - (uint32)MEMACC_ONE)))                        /* PRQA S 3383 # JV-01 */
  {
    LddLength = LpSubAreaConfig->ulMemWritePageSize;
  }
  else
  {
    /* Remaining area is only on this sub-area */
    if (MemAcc_GstAddrAreaData[LusAreaId].ddRemainingLength <= LddLength)
    {
      if (MemAcc_GstAddrAreaData[LusAreaId].ddRemainingLength < LpSubAreaConfig->ulMemWriteBurstSize)
      {
        LddLength = LpSubAreaConfig->ulMemWritePageSize; 
      }
      else
      {
        LddLength = LpSubAreaConfig->ulMemWriteBurstSize;
      }
    }
    /* Remaining area is not only on this sub-area */
    else
    {
      if (LpSubAreaConfig->ulMemWriteBurstSize <= LddLength)
      {
        LddLength = LpSubAreaConfig->ulMemWriteBurstSize;
      }
      else
      {
        LddLength = LpSubAreaConfig->ulMemWritePageSize;
      }
    }
  }
    
  /* Store requested lenth */
  MemAcc_GstAddrAreaData[LusAreaId].ddMemRequestedLength = LddLength;                                                   

  /* Request write to Mem driver */
  if (MEMACC_DIRECT_STATIC == MemAcc_GpConfigPtr->pInstInvocation[LulInstanceId])                                       
  {
    LenStdResult = MEMACC_MEM_API_REQUEST(MEMACC_MEM_PREFIX_NAME, Write)(LulInstanceId, LddAddress,
      MemAcc_GstAddrAreaData[LusAreaId].pReadOnlyBufferAddr, LddLength);
  }
  else
  {
    LenStdResult = (*(MemAcc_GstVar[LulInstanceId].pMemBinary->WriteFunc))(LulInstanceId,                               /* PRQA S 0404 # JV-01 */
      LddAddress, MemAcc_GstAddrAreaData[LusAreaId].pReadOnlyBufferAddr, LddLength);
  }
  
  /* Mem driver accept erase request */
  if (E_OK == LenStdResult)
  {
    /* Set flag for waiting result from Mem driver */
    MemAcc_GstAddrAreaData[LusAreaId].blWaitingMemResult = MEMACC_TRUE;                                                 
  }
  else
  {
    MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_FAILED;                                                      
    MemAcc_GstAddrAreaData[LusAreaId].enJobStatus = MEMACC_JOB_IDLE;                                                    
    MemAcc_GstAddrAreaData[LusAreaId].enCommand = MEMACC_NO_JOB;                                                        
    /* Call job end notification callback */
    if (NULL_PTR != MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer)                                   
    {
      MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer(                                                 
                    LusAreaId, MemAcc_GstAddrAreaData[LusAreaId].enJobResult);
    }
  }
} /* End of API MemAcc_ProcessWriteJob */
/*******************************************************************************
** Function Name             : MemAcc_ProcessBlankCheckJob
**
** Service ID                : NA
**
** Description               : NA
**
** Sync/Async                : Asynchronous
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
** Global Variables Used     : MemAcc_GstVar.usProcessingAreaId, MemAcc_GstAddrAreaData.usCurrentSubAreaIdx, MemAcc_GpAddressAreaConfig.pSubAreaConfig, MemAcc_GstAddrAreaData.ddCurrentAddress, MemAcc_GstAddrAreaData.ddRemainingLength, MemAcc_GstAddrAreaData.ddMemRequestedLength, MemAcc_GstAddrAreaData.blWaitingMemResult, MemAcc_GstAddrAreaData.enJobResult, MemAcc_GstAddrAreaData.enJobStatus, MemAcc_GstAddrAreaData.enCommand
**
** Function(s) invoked       : None
**
**
** Registers Used            : None
**
** Reference ID              : MEMACC_DUD_ACT_023, MEMACC_DUD_ACT_023_GBL001, MEMACC_DUD_ACT_023_GBL002
** Reference ID              : MEMACC_DUD_ACT_023_GBL003, MEMACC_DUD_ACT_023_GBL004, MEMACC_DUD_ACT_023_GBL005
** Reference ID              : MEMACC_DUD_ACT_023_GBL006, MEMACC_DUD_ACT_023_GBL007, MEMACC_DUD_ACT_023_GBL008
** Reference ID              : MEMACC_DUD_ACT_023_GBL009, MEMACC_DUD_ACT_023_GBL010, MEMACC_DUD_ACT_023_GBL011
** Reference ID              : MEMACC_DUD_ACT_023_GBL012, MEMACC_DUD_ACT_023_GBL013
**************************************************************************************/
FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessBlankCheckJob(Mem_59_Renesas_InstanceIdType LulInstanceId)                
{
  Std_ReturnType LenStdResult;
  uint16 LusAreaId;
  uint16 LusSubAreaIdx;
  MemAcc_AddressType LddAddress;
  MemAcc_LengthType LddLength;
  /* Pointer to sub-area */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  /* Get processing area id */
  LusAreaId = MemAcc_GstVar[LulInstanceId].usProcessingAreaId;                                                          
  /* Get current sub-area index */
  LusSubAreaIdx = MemAcc_GstAddrAreaData[LusAreaId].usCurrentSubAreaIdx;                                                
  /* Get sub-area config */
  LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[LusAreaId].pSubAreaConfig[LusSubAreaIdx];                               
  /* Get current address */
  LddAddress = MemAcc_GstAddrAreaData[LusAreaId].ddCurrentAddress;
  /* Calculate remaining sub-area length */
  LddLength = LpSubAreaConfig->ddSubAreaLength - (LddAddress - LpSubAreaConfig->ddLogicStartAddr);                      /* PRQA S 3383 # JV-01 */

  /* Remaining area is only on this sub-area */
  if (MemAcc_GstAddrAreaData[LusAreaId].ddRemainingLength <= LddLength)
  {
    if (MemAcc_GstAddrAreaData[LusAreaId].ddRemainingLength < LpSubAreaConfig->ulMemReadBurstSize)
    {
      LddLength = MemAcc_GstAddrAreaData[LusAreaId].ddRemainingLength;
    }
    else
    {
      LddLength = LpSubAreaConfig->ulMemReadBurstSize;
    }
  }
  /* Remaining area is not only on this sub-area */
  else
  {
    if (LpSubAreaConfig->ulMemReadBurstSize < LddLength)
    {
      LddLength = LpSubAreaConfig->ulMemReadBurstSize;
    } /* else length = remaining size of sub-area */
  }
  
  /* Store requested lenth */
  MemAcc_GstAddrAreaData[LusAreaId].ddMemRequestedLength = LddLength;                                                   

  /* Convert logical address to physical address */
  LddAddress = (LddAddress - LpSubAreaConfig->ddLogicStartAddr) + LpSubAreaConfig->ddPhysicalStartAddr;                 /* PRQA S 3383 # JV-01 */
  
  /* Request blank check to Mem driver */
  if (MEMACC_DIRECT_STATIC == MemAcc_GpConfigPtr->pInstInvocation[LulInstanceId])                                       
  {
    LenStdResult = MEMACC_MEM_API_REQUEST(MEMACC_MEM_PREFIX_NAME, BlankCheck)(LulInstanceId, LddAddress, LddLength);
  }
  else
  {
    LenStdResult = (*(MemAcc_GstVar[LulInstanceId].pMemBinary->BlankCheckFunc))(                                        /* PRQA S 0404 # JV-01 */
      LulInstanceId, LddAddress, LddLength);
  }
  
  /* Mem driver accept read request */
  if (E_OK == LenStdResult)
  {
    /* Set flag for waiting result from Mem driver */
    MemAcc_GstAddrAreaData[LusAreaId].blWaitingMemResult = MEMACC_TRUE;                                                 
  }
  else
  {
    MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_FAILED;                                                      
    MemAcc_GstAddrAreaData[LusAreaId].enJobStatus = MEMACC_JOB_IDLE;                                                    
    MemAcc_GstAddrAreaData[LusAreaId].enCommand = MEMACC_NO_JOB;                                                        
    /* Call job end notification callback */
    if (NULL_PTR != MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer)                                   
    {
      MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer(                                                 
                    LusAreaId, MemAcc_GstAddrAreaData[LusAreaId].enJobResult);
    }
  }
} /* End of API MemAcc_ProcessBlankCheckJob */

/*****************************************************************************
** Function Name            : MemAcc_ProcessHwSpecificJob
**
** Service ID               : NA
**
** Description              : NA
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : LulInstanceId
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variable(s) Used  : MemAcc_GstVar.usProcessingAreaId, MemAcc_GstAddrAreaData.ulHwServiceId
** Global Variable(s) Used  : MemAcc_GstAddrAreaData.pBufferAddress, MemAcc_GpConfigPtr->pInstInvocation,
** Global Variable(s) Used  : MemAcc_GstVar.pMemBinary, MemAcc_GstAddrAreaData.blWaitingMemResult,
** Global Variable(s) Used  : MemAcc_GstAddrAreaData.enJobResult, MemAcc_GstAddrAreaData.enJobStatus,
** Global Variable(s) Used  : MemAcc_GstAddrAreaData.enCommand, MemAcc_GstAddrAreaData.pLengthPtr
**
** Function(s) invoked      : Mem_59_Renesas_Read
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_028, MEMACC_DUD_ACT_028_GBL001, MEMACC_DUD_ACT_028_GBL002
** Reference ID             : MEMACC_DUD_ACT_028_GBL003, MEMACC_DUD_ACT_028_GBL004
** Reference ID             : MEMACC_DUD_ACT_028_GBL005, MEMACC_DUD_ACT_028_GBL006
** Reference ID             : MEMACC_DUD_ACT_028_GBL007, MEMACC_DUD_ACT_028_GBL008
********************************************************************************/
FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessHwSpecificJob(Mem_59_Renesas_InstanceIdType LulInstanceId)                
{
  Std_ReturnType LenStdResult;
  uint16 LusAreaId;

  /* Get processing area id */
  LusAreaId = MemAcc_GstVar[LulInstanceId].usProcessingAreaId;                                                          

  /* Request to Mem driver */
  if (MEMACC_DIRECT_STATIC == MemAcc_GpConfigPtr->pInstInvocation[LulInstanceId])                                       
  {
    LenStdResult = MEMACC_MEM_API_REQUEST(MEMACC_MEM_PREFIX_NAME, HwSpecificService)(LulInstanceId,
      MemAcc_GstAddrAreaData[LusAreaId].ulHwServiceId,                                                                  
      MemAcc_GstAddrAreaData[LusAreaId].pBufferAddress,
      MemAcc_GstAddrAreaData[LusAreaId].pLengthPtr);
  }
  else
  {
    LenStdResult = (*(MemAcc_GstVar[LulInstanceId].pMemBinary->HwSpecificServiceFunc))(                                 /* PRQA S 0404 # JV-01 */
      LulInstanceId, MemAcc_GstAddrAreaData[LusAreaId].ulHwServiceId,
      MemAcc_GstAddrAreaData[LusAreaId].pBufferAddress,
      MemAcc_GstAddrAreaData[LusAreaId].pLengthPtr);
  }

  /* Mem driver accept read request */
  if (E_OK == LenStdResult)
  {
    /* Set flag for waiting result from Mem driver */
    MemAcc_GstAddrAreaData[LusAreaId].blWaitingMemResult = MEMACC_TRUE;                                                 
  }
  else
  {
    MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_FAILED;                                                  
    MemAcc_GstAddrAreaData[LusAreaId].enJobStatus = MEMACC_JOB_IDLE;                                                    
    MemAcc_GstAddrAreaData[LusAreaId].enCommand = MEMACC_NO_JOB;                                                        
    /* Call job end notification callback */
    if (NULL_PTR != MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer)                                   
    {
      MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer(                                                 
                    LusAreaId, MemAcc_GstAddrAreaData[LusAreaId].enJobResult);
    }
  }
} /* End of API MemAcc_ProcessHwSpecificJob */

/***********************************************************************
** Function Name            : MemAcc_ProcessJobResult
**
** Service ID               : NA
**
** Description              : NA
**
** Sync/Async               : Asynchronous
**
** Re-entrancy              : None Re-entrant
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
** Global Variables Used    : MemAcc_GstVar.usProcessingAreaId, MemAcc_GpConfigPtr->pInstInvocation, 
** Global Variables Used    : MemAcc_GstVar.pMemBinary, MemAcc_GstAddrAreaData.enMemJobResult, MemAcc_GstAddrAreaData.ucRetryTimes, MemAcc_GstVar.enInstanceStatus
** Global Variables Used    : MemAcc_GpAddressAreaConfig.pJobEndNotificationPointer, MemAcc_GstAddrAreaData.blWaitingMemResult, MemAcc_GstAddrAreaData.enJobResult, MemAcc_GstAddrAreaData.enJobStatus, MemAcc_GstAddrAreaData.enCommand
**
** Function(s) invoked      : Mem_59_Renesas_GetJobResult
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_024, MEMACC_DUD_ACT_024_GBL001, MEMACC_DUD_ACT_024_GBL002
** Reference ID             : MEMACC_DUD_ACT_024_GBL003, MEMACC_DUD_ACT_024_GBL004, MEMACC_DUD_ACT_024_GBL005
** Reference ID             : MEMACC_DUD_ACT_024_GBL006, MEMACC_DUD_ACT_024_GBL007, MEMACC_DUD_ACT_024_GBL008
** Reference ID             : MEMACC_DUD_ACT_024_GBL009, MEMACC_DUD_ACT_024_GBL010, MEMACC_DUD_ACT_024_GBL011
** Reference ID             : MEMACC_DUD_ACT_024_GBL012, MEMACC_DUD_ACT_024_GBL013, MEMACC_DUD_ACT_024_GBL014
** Reference ID             : MEMACC_DUD_ACT_024_GBL015, MEMACC_DUD_ACT_024_GBL016, MEMACC_DUD_ACT_024_GBL017
** Reference ID             : MEMACC_DUD_ACT_024_GBL018, MEMACC_DUD_ACT_024_GBL019, MEMACC_DUD_ACT_024_GBL020
** Reference ID             : MEMACC_DUD_ACT_024_GBL021, MEMACC_DUD_ACT_024_GBL022, MEMACC_DUD_ACT_024_GBL023
** Reference ID             : MEMACC_DUD_ACT_024_GBL024
**********************************************************************************/
FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessJobResult(Mem_59_Renesas_InstanceIdType LulInstanceId)                    
{
  uint16 LusAreaId;
  Mem_59_Renesas_JobResultType LenJobResult;

  /* Get processing area id */
  LusAreaId = MemAcc_GstVar[LulInstanceId].usProcessingAreaId;                                                          
  /* Get Mem driver result */
  if (MEMACC_DIRECT_STATIC == MemAcc_GpConfigPtr->pInstInvocation[LulInstanceId])                                       
  {
    LenJobResult = MEMACC_MEM_API_REQUEST(MEMACC_MEM_PREFIX_NAME, GetJobResult)(LulInstanceId);
  }
  else
  {
    LenJobResult = (*(MemAcc_GstVar[LulInstanceId].pMemBinary->GetJobResultFunc))(LulInstanceId);                       /* PRQA S 0404 # JV-01 */
  }

  MemAcc_GstAddrAreaData[LusAreaId].enMemJobResult = LenJobResult;                                                      

  if(MEM_59_RENESAS_JOB_PENDING != LenJobResult)
  {
    if (MEM_59_RENESAS_JOB_OK == LenJobResult)
    {
      if (MEMACC_MEMHWSPECIFIC_JOB == MemAcc_GstAddrAreaData[LusAreaId].enCommand)
      {
        /* Set result to failed */
        MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_OK;                                                  
        /* Change job status to IDLE */
        MemAcc_GstAddrAreaData[LusAreaId].enJobStatus = MEMACC_JOB_IDLE;                                                
        /* Set current command to none */
        MemAcc_GstAddrAreaData[LusAreaId].enCommand = MEMACC_NO_JOB;                                                    
      }
      else
      {
        MemAcc_ProcessJobOk(LusAreaId);
      }
    }
    else if (MEM_59_RENESAS_JOB_FAILED == LenJobResult)
    {
      if ((MEMACC_ERASE_JOB == MemAcc_GstAddrAreaData[LusAreaId].enCommand) ||
        (MEMACC_WRITE_JOB == MemAcc_GstAddrAreaData[LusAreaId].enCommand))
      {
        if (MEMACC_ZERO == MemAcc_GstAddrAreaData[LusAreaId].ucRetryTimes)
        {
          /* Set result to failed */
          MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_FAILED;                                            
          /* Change job status to IDLE */
          MemAcc_GstAddrAreaData[LusAreaId].enJobStatus = MEMACC_JOB_IDLE;                                              
          /* Set current command to none */
          MemAcc_GstAddrAreaData[LusAreaId].enCommand = MEMACC_NO_JOB;                                                  
        }
        else
        {
          MemAcc_GstAddrAreaData[LusAreaId].ucRetryTimes--;
        }
      }
      else
      {
        /* Set result to failed */
        MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_FAILED;                                              
        /* Change job status to IDLE */
        MemAcc_GstAddrAreaData[LusAreaId].enJobStatus = MEMACC_JOB_IDLE;                                                
        /* Set current command to none */
        MemAcc_GstAddrAreaData[LusAreaId].enCommand = MEMACC_NO_JOB;                                                    
      }
    }
    else /* other error cases */
    {
      if (MEM_59_RENESAS_INCONSISTENT == LenJobResult)
      {
        MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_INCONSISTENT;                                        
      }
      else if (MEM_59_RENESAS_ECC_UNCORRECTED == LenJobResult)
      {
        MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_ECC_UNCORRECTED;                                     
      }
      else /* (MEM_59_RENESAS_ECC_CORRECTED == LenJobResult) */
      {
        MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_ECC_CORRECTED;                                       
      }
      /* Change job status to IDLE */
      MemAcc_GstAddrAreaData[LusAreaId].enJobStatus = MEMACC_JOB_IDLE;                                                  
      /* Set current command to none */
      MemAcc_GstAddrAreaData[LusAreaId].enCommand = MEMACC_NO_JOB;                                                      
    }
    /* Set flag for waiting result from Mem driver to FALSE */
    MemAcc_GstAddrAreaData[LusAreaId].blWaitingMemResult = MEMACC_FALSE;                                                
    /* Change instance status to IDLE */
    MemAcc_GstVar[LulInstanceId].enInstanceStatus = MEMACC_INSTANCE_IDLE;                                               

    /* Call job end notification callback */
    if (MEMACC_JOB_IDLE == MemAcc_GstAddrAreaData[LusAreaId].enJobStatus)
    {
      if (NULL_PTR != MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer)                                 
      {
        MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer(                                               
          LusAreaId, MemAcc_GstAddrAreaData[LusAreaId].enJobResult);
      }
    } 
  } /* else PENDING state, continue checking in next schedule */
} /* End of API MemAcc_ProcessJobResult */

#if (MEMACC_COMPARE_API == STD_ON)
/***********************************************************************
** Function Name            : MemAcc_ProcessCompareData
**
** Service ID               : NA
**
** Description              : NA
**                            
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : LusAreaId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : Std_ReturnType
**
** Preconditions            : None
**
** Global Variables Used    : MemAcc_GstAddrAreaData.ddMemRequestedLength, MemAcc_GstAddrAreaData.pReadOnlyBufferAddr, MemAcc_GstAddrAreaData.ddRemainingLength, MemAcc_GstAddrAreaData.pReadOnlyBufferAddr
**
** Function(s) invoked      : None
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_025, MEMACC_DUD_ACT_025_GBL001, MEMACC_DUD_ACT_025_GBL002
** Reference ID             : MEMACC_DUD_ACT_025_GBL003, MEMACC_DUD_ACT_025_GBL004
**********************************************************************************/
FUNC(Std_ReturnType, MEMACC_PRIVATE_CODE) MemAcc_ProcessCompareData(uint16 LusAreaId)                                   /* PRQA S 1505 # JV-01 */
{
  Std_ReturnType LenCompareResult;
  uint32 LulLoopCount;
  P2VAR(uint8, AUTOMATIC, MEMACC_APPL_DATA) LpMemoryData;                                                               /* PRQA S 3678, 3432 # JV-01, JV-01 */

  LenCompareResult = E_OK;
  LpMemoryData = (uint8*)MemAcc_CompareBuffer;                                                                          /* PRQA S 0751 # JV-01 */                                                                       

  /* Loop to compare data */
  for (LulLoopCount = MEMACC_ZERO; LulLoopCount <
        MemAcc_GstAddrAreaData[LusAreaId].ddMemRequestedLength; LulLoopCount++)                                         
  {
    if (*LpMemoryData != *((const uint8*) MemAcc_GstAddrAreaData[LusAreaId].pReadOnlyBufferAddr))                       
    {
      LenCompareResult = E_NOT_OK;
      /* Set remaining length = 0 to end process */
      MemAcc_GstAddrAreaData[LusAreaId].ddRemainingLength = MEMACC_ZERO;                                                
      break;
    }
    /* Increase compare buffers */
    LpMemoryData++;                                                                                                     
    MemAcc_GstAddrAreaData[LusAreaId].pReadOnlyBufferAddr++;                                                            
  }

  return LenCompareResult;
} /* End of MemAcc_ProcessCompareData */
#endif /* #if (MEMACC_COMPARE_API == STD_ON) */

/***********************************************************************
** Function Name            : MemAcc_ProcessJobOk
**
** Service ID               : NA
**
** Description              : NA                            
**
** Sync/Async               : Asynchronous
**
** Re-entrancy              : None Re-entrant
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
** Global Variables Used    : MemAcc_GstAddrAreaData.ddProcessedLength, MemAcc_GstAddrAreaData.ddMemRequestedLength, MemAcc_GstAddrAreaData.enCommand, MemAcc_GstAddrAreaData.pReadOnlyBufferAddr, MemAcc_GstAddrAreaData.ddMemRequestedLength, MemAcc_GstAddrAreaData.ddRemainingLength, MemAcc_GstAddrAreaData.ddCurrentAddress, MemAcc_GpAddressAreaConfig.usNumOfSubArea, MemAcc_GstAddrAreaData.usCurrentSubAreaIdx, MemAcc_GstAddrAreaData.enJobResult, MemAcc_GstAddrAreaData.enJobStatus, 
**
** Function(s) invoked      : MemAcc_ProcessCompareData
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_026, MEMACC_DUD_ACT_026_GBL001, MEMACC_DUD_ACT_026_GBL002
** Reference ID             : MEMACC_DUD_ACT_026_GBL003, MEMACC_DUD_ACT_026_GBL004, MEMACC_DUD_ACT_026_GBL005
** Reference ID             : MEMACC_DUD_ACT_026_GBL006, MEMACC_DUD_ACT_026_GBL007, MEMACC_DUD_ACT_026_GBL008
** Reference ID             : MEMACC_DUD_ACT_026_GBL009, MEMACC_DUD_ACT_026_GBL010, MEMACC_DUD_ACT_026_GBL011
** Reference ID             : MEMACC_DUD_ACT_026_GBL012, MEMACC_DUD_ACT_026_GBL013, MEMACC_DUD_ACT_026_GBL014
**********************************************************************************/
FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_ProcessJobOk(uint16 LusAreaId)                                                   /* PRQA S 1505 # JV-01 */
{
  #if (MEMACC_COMPARE_API == STD_ON)
  Std_ReturnType LenCompareResult = E_OK;
  #endif /* #if (MEMACC_COMPARE_API == STD_ON) */
  
  /* Pointer to sub-area */
  P2CONST(MemAcc_SubAreaConfigType, AUTOMATIC, MEMACC_CONFIG_DATA) LpSubAreaConfig;

  
  /* Update processed length */
  MemAcc_GstAddrAreaData[LusAreaId].ddProcessedLength +=                                                                /* PRQA S 3383 # JV-01 */
    MemAcc_GstAddrAreaData[LusAreaId].ddMemRequestedLength;
  /* Update remaining length */
  MemAcc_GstAddrAreaData[LusAreaId].ddRemainingLength -=                                                                /* PRQA S 3383 # JV-01 */
    MemAcc_GstAddrAreaData[LusAreaId].ddMemRequestedLength;

  if (MEMACC_READ_JOB == MemAcc_GstAddrAreaData[LusAreaId].enCommand)                                                   
  {
    /* Move user buffer to next address */
    MemAcc_GstAddrAreaData[LusAreaId].pBufferAddress +=                                                                 /* PRQA S 0488 # JV-01 */
      MemAcc_GstAddrAreaData[LusAreaId].ddMemRequestedLength;
  }
  else if (MEMACC_WRITE_JOB == MemAcc_GstAddrAreaData[LusAreaId].enCommand)
  {
    /* Move user buffer to next address */
    MemAcc_GstAddrAreaData[LusAreaId].pReadOnlyBufferAddr +=                                                            /* PRQA S 0488 # JV-01 */
      MemAcc_GstAddrAreaData[LusAreaId].ddMemRequestedLength;
  }
  #if (MEMACC_COMPARE_API == STD_ON)
  else if (MEMACC_COMPARE_JOB == MemAcc_GstAddrAreaData[LusAreaId].enCommand)                                           /* PRQA S 2004 # JV-01 */
  {
    /* Compare user data and memory data */
    LenCompareResult = MemAcc_ProcessCompareData(LusAreaId);
  }
  #endif /* #if (MEMACC_COMPARE_API == STD_ON) */

  if (MEMACC_ZERO < MemAcc_GstAddrAreaData[LusAreaId].ddRemainingLength)                                                
  {
    /* Move to next address */
    MemAcc_GstAddrAreaData[LusAreaId].ddCurrentAddress +=                                                               /* PRQA S 3383 # JV-01 */
      MemAcc_GstAddrAreaData[LusAreaId].ddMemRequestedLength;
    /* Check if process address moves to next sub-area */
    if ((MemAcc_GpAddressAreaConfig[LusAreaId].usNumOfSubArea -                                                         
        (uint16)MEMACC_ONE) != MemAcc_GstAddrAreaData[LusAreaId].usCurrentSubAreaIdx)                                   
    {
      /* Get next sub-area config */
      LpSubAreaConfig = &MemAcc_GpAddressAreaConfig[LusAreaId].
        pSubAreaConfig[MemAcc_GstAddrAreaData[LusAreaId].usCurrentSubAreaIdx + (uint16)MEMACC_ONE];
      /* If current address is belong to next sub-area */
      if (LpSubAreaConfig->ddLogicStartAddr <= MemAcc_GstAddrAreaData[LusAreaId].ddCurrentAddress)                      
      {
        MemAcc_GstAddrAreaData[LusAreaId].usCurrentSubAreaIdx++;                                                        /* PRQA S 3383 # JV-01 */
      }
    }
  }
  /* If requested area is processed completely */
  else /* (MEMACC_ZERO == MemAcc_GstAddrAreaData[LusAreaId].ddRemainingLength) */
  {
    #if (MEMACC_COMPARE_API == STD_ON)
    /* Check compare result */
    if (E_NOT_OK == LenCompareResult)
    {
      MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_INCONSISTENT;                                          
    }
    else 
    #endif /* #if (MEMACC_COMPARE_API == STD_ON) */
    {
      MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_OK;                                                    
    }

    /* Change job status to IDLE */
    MemAcc_GstAddrAreaData[LusAreaId].enJobStatus = MEMACC_JOB_IDLE;                                                    
    /* Set current command to none */
    MemAcc_GstAddrAreaData[LusAreaId].enCommand = MEMACC_NO_JOB;                                                        
  }
}

/***********************************************************************************************************************
** Function Name            : MemAcc_CheckCancelRequest
**
** Service ID               : NA
**
** Description              : This function will check and process cancel request
**
** Sync/Async               : Synchronous
**
** Reentrancy               : None re-entrant
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
** Global Variables Used    : MemAcc_GstAddrAreaData, MemAcc_GpAddressAreaConfig, MemAcc_GstVar
**
** Function(s) invoked      : None
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_029, MEMACC_DUD_ACT_029_GBL001, MEMACC_DUD_ACT_029_GBL002
** Reference ID             : MEMACC_DUD_ACT_029_GBL003, MEMACC_DUD_ACT_029_GBL004, MEMACC_DUD_ACT_029_GBL005
** Reference ID             : MEMACC_DUD_ACT_029_GBL006, MEMACC_DUD_ACT_029_GBL007, MEMACC_DUD_ACT_029_GBL008
***********************************************************************************************************************/
FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_CheckCancelRequest(void)                                                         
{
  uint16 LusAreaId;
  Mem_59_Renesas_InstanceIdType LulInstanceIdx;

  /* Loop through all area to check cancel request */
  for (LusAreaId = (uint16)MEMACC_ZERO; LusAreaId <= MEMACC_MAX_ADDRESS_AREA_ID; LusAreaId++)                           /* PRQA S 2877 # JV-01 */
  {
    if (MEMACC_TRUE == MemAcc_GstAddrAreaData[LusAreaId].blCancelRequest)
    {
      LulInstanceIdx = MemAcc_GpAddressAreaConfig[LusAreaId].pSubAreaConfig                                             
        [MemAcc_GstAddrAreaData[LusAreaId].usCurrentSubAreaIdx].ulInstanceId;
      
      if ((MEMACC_TRUE == MemAcc_GstVar[LulInstanceIdx].blSuspendedFlag) &&                                             
        (LusAreaId == MemAcc_GstVar[LulInstanceIdx].usSuspendedAreaId))
      {
        /* Can't cancel this area since the request in Mem driver is still pending */
      }
      else if (MEMACC_TRUE == MemAcc_GstAddrAreaData[LusAreaId].blWaitingMemResult)
      {
        /* Can't cancel this area since the request in Mem driver is still pending */
      }
      else /* Reset area data to cancel current request */
      {
        /* Reset current command */
        MemAcc_GstAddrAreaData[LusAreaId].enCommand = MEMACC_NO_JOB;
        /* Set job result to cancel */
        MemAcc_GstAddrAreaData[LusAreaId].enJobResult = MEMACC_MEM_CANCELED;
        /* Reset job status to IDLE */
        MemAcc_GstAddrAreaData[LusAreaId].enJobStatus = MEMACC_JOB_IDLE;
        /* Reset cancel flag */
        MemAcc_GstAddrAreaData[LusAreaId].blCancelRequest = MEMACC_FALSE;
        /* Call job end notification callback to notify that job was end due to cancel */
        if (NULL_PTR != MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer)
        {
          MemAcc_GpAddressAreaConfig[LusAreaId].pJobEndNotificationPointer(                                             
                        LusAreaId, MemAcc_GstAddrAreaData[LusAreaId].enJobResult);
        }
      }
    }
  }
}
/***********************************************************************************************************************
** Function Name            : MemAcc_SelectAreaToProcess
**
** Service ID               : None
**
** Description              : This function will check and select next area Id with highest priority to process
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : LulInstanceIdx
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : MemAcc_GpConfigPtr, MemAcc_GstVar, MemAcc_GpAddressAreaConfig, MemAcc_GstAddrAreaData
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEMACC_DUD_ACT_030, MEMACC_DUD_ACT_030_GBL001, MEMACC_DUD_ACT_030_GBL002
** Reference ID             : MEMACC_DUD_ACT_030_GBL003, MEMACC_DUD_ACT_030_GBL004, MEMACC_DUD_ACT_030_GBL005
** Reference ID             : MEMACC_DUD_ACT_030_GBL006, MEMACC_DUD_ACT_030_GBL007, MEMACC_DUD_ACT_030_GBL008
** Reference ID             : MEMACC_DUD_ACT_030_GBL009, MEMACC_DUD_ACT_030_GBL010, MEMACC_DUD_ACT_030_GBL011
** Reference ID             : MEMACC_DUD_ACT_030_GBL012, MEMACC_DUD_ACT_030_GBL013, MEMACC_DUD_ACT_030_GBL014
** Reference ID             : MEMACC_DUD_ACT_030_GBL015, MEMACC_DUD_ACT_030_GBL016, MEMACC_DUD_ACT_030_GBL017
** Reference ID             : MEMACC_DUD_ACT_030_GBL018
***********************************************************************************************************************/

FUNC(void, MEMACC_PRIVATE_CODE) MemAcc_SelectAreaToProcess(Mem_59_Renesas_InstanceIdType LulInstanceIdx)                
{
  uint16 LusAreaId;
  uint16 LusPriority;

  /* Determine which area id will be processed */
  LusPriority = MEMACC_HIGHEST_PRIORITY + (uint16)MEMACC_ONE;
  do
  {
    /* Move to next lower priority */
    LusPriority--;                                                                                                      /* PRQA S 3383 # JV-01 */
    /* Get area Id from priority */
    LusAreaId = MemAcc_GpConfigPtr->pPriority2AddrAreaId[LusPriority];                                                  
    /* Check if there is any request for this area */
    if ((LulInstanceIdx == MemAcc_GpAddressAreaConfig[LusAreaId].pSubAreaConfig                                         
                      [MemAcc_GstAddrAreaData[LusAreaId].usCurrentSubAreaIdx].ulInstanceId) &&                          
        (MEMACC_JOB_PENDING == MemAcc_GstAddrAreaData[LusAreaId].enJobStatus))
    {
      if (MEMACC_INSTANCE_IDLE == MemAcc_GstVar[LulInstanceIdx].enInstanceStatus)                                       
      {
        if ((MEMACC_TRUE == MemAcc_GstVar[LulInstanceIdx].blSuspendedFlag) &&
          (MemAcc_GstVar[LulInstanceIdx].usSuspendedAreaId == LusAreaId))
        {
          /* Resume operation of this area id */
          if (MEMACC_DIRECT_STATIC == MemAcc_GpConfigPtr->pInstInvocation[LulInstanceIdx])                              
          {
            MEMACC_MEM_API_REQUEST(MEMACC_MEM_PREFIX_NAME, Resume)(LulInstanceIdx);
          }
          else if ((MEMACC_INDIRECT_DYNAMIC == MemAcc_GpConfigPtr->pInstInvocation[LulInstanceIdx]) &&                  /* PRQA S 2004 # JV-01 */
          (MemAcc_GstVar[LulInstanceIdx].pMemBinary != NULL_PTR))
          {
            (*(MemAcc_GstVar[LulInstanceIdx].pMemBinary->ResumeFunc))(LulInstanceIdx);                                  /* PRQA S 0404 # JV-01 */
          }
          MemAcc_GstVar[LulInstanceIdx].usProcessingAreaId = MemAcc_GstVar[LulInstanceIdx].usSuspendedAreaId;           
          /* Set flag for waiting result from Mem driver to TRUE */
          MemAcc_GstAddrAreaData[LusAreaId].blWaitingMemResult = MEMACC_TRUE;                                           
          /* Reset suspend info */
          MemAcc_GstVar[LulInstanceIdx].blSuspendedFlag = MEMACC_FALSE;                                                 
          MemAcc_GstVar[LulInstanceIdx].usSuspendedAreaId = MEMACC_INVALID_AREA_ID;                                     
          MemAcc_GstVar[LulInstanceIdx].enInstanceStatus = MEMACC_INSTANCE_BUSY;                                        
        }
        else
        {
          /* Set processing area id = this area id */
          MemAcc_GstVar[LulInstanceIdx].usProcessingAreaId = LusAreaId;                                                 
          /* Set flag for waiting result from Mem driver to FALSE */
          MemAcc_GstAddrAreaData[LusAreaId].blWaitingMemResult = MEMACC_FALSE;                                          
          MemAcc_GstVar[LulInstanceIdx].enInstanceStatus = MEMACC_INSTANCE_BUSY;                                        
        }
      }
      /* The instance is busy */
      else if (MEMACC_INSTANCE_BUSY == MemAcc_GstVar[LulInstanceIdx].enInstanceStatus)                                  /* PRQA S 2004 # JV-01 */
      {
        /* The current processing area id is not highest priority */
        if (MemAcc_GstVar[LulInstanceIdx].usProcessingAreaId != LusAreaId)
        {
          /* No suspend request is made before */
          if (MEMACC_FALSE == MemAcc_GstVar[LulInstanceIdx].blSuspendedFlag)
          {
            /* Suspend the on-going request */
            if (MEMACC_DIRECT_STATIC == MemAcc_GpConfigPtr->pInstInvocation[LulInstanceIdx])
            {
              MEMACC_MEM_API_REQUEST(MEMACC_MEM_PREFIX_NAME, Suspend)(LulInstanceIdx);
            }
            else if ((MEMACC_INDIRECT_DYNAMIC == MemAcc_GpConfigPtr->pInstInvocation[LulInstanceIdx]) &&                /* PRQA S 2004 # JV-01 */
            (MemAcc_GstVar[LulInstanceIdx].pMemBinary != NULL_PTR))
            {
              (*(MemAcc_GstVar[LulInstanceIdx].pMemBinary->SuspendFunc))(LulInstanceIdx);                               /* PRQA S 0404 # JV-01 */
            }
            
            /* Set flag to aware this instance is suspended already */
            MemAcc_GstVar[LulInstanceIdx].blSuspendedFlag = MEMACC_TRUE;                                                
            /* Back up suspended area id */
            MemAcc_GstVar[LulInstanceIdx].usSuspendedAreaId =                                                           
              MemAcc_GstVar[LulInstanceIdx].usProcessingAreaId;
            /* Set next processing area id */
            MemAcc_GstVar[LulInstanceIdx].usProcessingAreaId = LusAreaId;                                               
            /* Set flag for waiting result from Mem driver to FALSE */
            MemAcc_GstAddrAreaData[LusAreaId].blWaitingMemResult = MEMACC_FALSE;                                        
          } /* If the suspend is request for this instance already,
               can't request suspend again then continue with current processing area id */
        } /* else No action and continue handle currend area id */
      } /* else Mem instance is not initialized */
      break; /* break since highest priority area was found */
    } /* end of if ((LulInstanceIdx == MemAcc_GpAddressAreaConfig[LusAreaId].pSubAreaConfig */
  } while (LusPriority > (uint16)MEMACC_ZERO);                                                                          /* PRQA S 2996, 2993 # JV-01, JV-01 */
}

#define MEMACC_STOP_SEC_PRIVATE_CODE
#include "MemAcc_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
