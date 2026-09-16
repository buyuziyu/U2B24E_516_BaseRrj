/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_Util.c                                                                                          */
/*====================================================================================================================*/
/*                                                    COPYRIGHT                                                       */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains utility functions implementation of Ethernet Driver  Component.                                 */
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
/* associated with its exercise of rights under this Agreement, including, but not limited to the risks and costs     */
/* of program errors, compliance with applicable laws, damage to or loss of data, programs or equipment,              */
/* and unavailability or interruption of operations.                                                                  */
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
/*                                        Devices:        X2x                                                         */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                    Revision Control History                                                        **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Updated QA-C 9.5.0 comments
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 *        26/11/2024    : Updated QA-C 9.5.0 comments
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 30/08/2024    : Update QAC message
 * 2.0.1: 18/10/2023    : Added QA-C Warning 3678 according to QA-C 10.3.0
 *                      : Added QA-C 10.3.0 comments
 * 2.0.0: 27/07/2023    : Add CWE rule into QAC header
 *        24/07/2023    : Remove redundant QA-C warning 1532, 1503, 3383
 * 1.5.1: 12/01/2021    : Update QA-C 9.5.0 comments
 * 1.4.2: 24/08/2021    : Modify the format to 120 characters
 *        30/08/2021    : Updated QA-C 9.5.0 comments
 * 1.4.1: 24/06/2021    : Support heap algorithm APIs.
 *        07/05/2021    : Remove vendor ID from the file name, API names and parameters according to 
 *                        BSW00347 requirement
 *        09/06/2021    : Remove QA-C Warning 3432 according to QA-C 9.5.0
 *                      : Add QA-C Warning 3673
 *        06/07/2021    : Updated QA-C 9.5.0 comments.
 * 1.2.0: 13/07/2020    : Release
 *        29/07/2020    : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020    : Release
 * 1.0.1: 04/06/2020    : Remove Eth_59_GaaRamManager global variable.
 *                        Remove Eth_59_Util_MemCopy function.
 *                        Update for improvement by the QA-C.
 * 1.0.0: 25/03/2020    : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                       Include Section                                                              **
***********************************************************************************************************************/
/* Included for prototypes for internal functions of Ethernet Component */
#include "Eth.h"
#include "Eth_Util.h"

/***********************************************************************************************************************
**                                       Version Information                                                          **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ETH_UTIL_C_AR_RELEASE_MAJOR_VERSION ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETH_UTIL_C_AR_RELEASE_MINOR_VERSION ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETH_UTIL_C_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ETH_UTIL_C_SW_MAJOR_VERSION    ETH_SW_MAJOR_VERSION_VALUE
#define ETH_UTIL_C_SW_MINOR_VERSION    ETH_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                       Version Check                                                                **
***********************************************************************************************************************/
#if (ETH_UTIL_AR_RELEASE_MAJOR_VERSION != ETH_UTIL_C_AR_RELEASE_MAJOR_VERSION)
  #error "Eth_Util.c : Mismatch in Release Major Version"
#endif
#if (ETH_UTIL_AR_RELEASE_MINOR_VERSION != ETH_UTIL_C_AR_RELEASE_MINOR_VERSION)
  #error "Eth_Util.c : Mismatch in Release Minor Version"
#endif
#if (ETH_UTIL_AR_RELEASE_REVISION_VERSION != ETH_UTIL_C_AR_RELEASE_REVISION_VERSION)
  #error "Eth_Util.c : Mismatch in Release Revision Version"
#endif

#if (ETH_UTIL_SW_MAJOR_VERSION != ETH_UTIL_C_SW_MAJOR_VERSION)
  #error "Eth_Util.c : Mismatch in Software Major Version"
#endif
#if (ETH_UTIL_SW_MINOR_VERSION != ETH_UTIL_C_SW_MINOR_VERSION)
  #error "Eth_Util.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3673)    : The object addressed by the pointer parameter '%s' is not modified and so the pointer could  */
/*                       be of type 'pointer to const'.                                                               */
/* Rule                : CERTCCM DCL00, DCL13, MISRA C:2012 Rule-8.13, CWE Rule CWE-398, CWE-569                      */
/* JV-01 Justification : Pointer variable is used to modify the value at the address so the pointer cannot be         */
/*                       declared as 'pointer to const' type.                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0316)    : Cast from a pointer to void to a pointer to object type.                                     */
/* Rule                : MISRA C:2012 Rule-11.5, CWE Rule CWE-188, CWE-398, CWE-569                                   */
/* JV-01 Justification : Typecasting from void* is necessary to hide internal types from the header files which are   */
/*                       exposed to user.                                                                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add a   */
/*                       wraparound guard here.                                                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0310)    : Casting to different object pointer type.                                                    */
/* Rule                : CERTCCM EXP11, EXP39, MISRA C:2012 Rule-11.3, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588    */
/*                       CWE-465, CWE-569, CWE-737                                                                    */
/* JV-01 Justification : There is no problem because it is as designed.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1532)    : The function '%1s' is only referenced in one translation unit - but not the one in which it  */
/*                       is defined.                                                                                  */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the specific coding rule, function of each hardware unit is         */
/*                       implemented in separated files for this hardware unit. Could not be static function.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to call a function here    */
/*                       for such a small operation.                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : Wraparound can't be occur in this unsigned integer arithmetic so there is no need to add a   */
/*                       wraparound guard here.                                                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:3305)    : Pointer cast to stricter alignment.                                                          */
/* Rule                : CERTCCM EXP36, EXP39, MISRA C:2012 Rule-11.3, CWE Rule CWE-188, CWE-737                      */
/* JV-01 Justification : It is an implementation required to manage heap memory. There is no problem because the      */
/*                       4-byte alignment boundary is guaranteed by the implementation of the heap memory operation   */
/*                       algorithm.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0751)    : Casting to char pointer type.                                                                */
/* Rule                : CERTCCM EXP11, EXP39, CWE Rule CWE-188, CWE-398, CWE-468, CWE-588, CWE-465, CWE-569, CWE-737 */
/* JV-01 Justification : Using void due to specific requirement of input parameter. So, this can be skipped           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4, CWE Rule CWE-188, CWE-398, CWE-569                    */
/* JV-01 Justification : This implementation is required for heap memory allocation algorithm                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : (4:5087) #include statements in a file should only be preceded by other preprocessor         */
/*                       directives or comments.                                                                      */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is accepted, due to implementation for include memmap is following AUTOSAR rule.        */
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
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2814)    : Possible: Dereference of NULL pointer.                                                       */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-476, CWE-465, CWE-737, CWE-690                                   */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2844)    : Possible: Dereference of an invalid pointer value.                                           */
/* Rule                : CERTCCM ARR30, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125, CWE-126, CWE-127        */
/*                       CWE-129, CWE-131, CWE-466, CWE-786, CWE-787, CWE-788, CWE-805, CWE-465, CWE-633, CWE-740     */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2824)    : Possible: Arithmetic operation on NULL pointer.                                              */
/* Rule                : CERTCCM EXP34, CWE Rule CWE-468, CWE-476, CWE-465, CWE-737                                   */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1532)    : The function '%1s' is only referenced in one translation unit - but not the one in which it  */
/*                       is defined.                                                                                  */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the specific coding rule, function of each hardware unit is         */
/*                       implemented in separated files for this hardware unit. Could not be static function.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0314)    : [I] Cast from a pointer to object type to a pointer to void.                                 */
/* Rule                : MISRA-C:2012 Dir-1.1                                                                         */
/* JV-01 Justification : Pointer to a void is a generic pointer type which can be use cast to any other pointer type. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2934)    : Possible: Computing an invalid pointer value.                                                */
/* Rule                : CERTCCM EXP08, ARR30, ARR37, ARR38, CWE Rule CWE-120, CWE-121, CWE-122, CWE-124, CWE-125,    */
/*                       CWE-126, CWE-127, CWE-129, CWE-131, CWE-469, CWE-823, CWE-465, CWE-633, CWE-740              */
/* JV-01 Justification : This message prevents existing of an out-of-range pointer                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Global Data                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Function Definitions                                                 **
***********************************************************************************************************************/
/***********************************************************************************************************************
** Function Name         : Eth_Util_IniLinkedList
**
** Service ID            : NA
**
** Description           : This Api initialize linked list
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : None
**
** InOut Parameters      : LpList - Linked list
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_037
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"
FUNC(void, ETH_PRIVATE_CODE) Eth_Util_IniLinkedList(                                                                    /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList)                                                            /* PRQA S 3432 # JV-01 */
{
  if (NULL_PTR != LpList)
  {
    LpList->ulCount = 0UL;
    LpList->pLast = NULL_PTR;
    LpList->pHead = NULL_PTR;
  }
  else
  {
    /* No action required */
  }
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_EnqToList
**
** Service ID            : NA
**
** Description           : This Api enqueue into the list (FIFO method)
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : LpElem - Node data
**
** InOut Parameters      : LpList - Linked list
**
** Output Parameters     : None
**
** Return parameter      : LucReturnValue
**                         E_OK - if Node has been enqueue successfully
**                         E_NOT_OK - otherwise
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_038
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Util_EnqToList(                                                              /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList,                                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpElem)                                                                    
{
  CONSTP2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpNode =                                                      /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA))LpElem;                                                         /* PRQA S 0316, 3432 # JV-01, JV-01 */
  Std_ReturnType LucReturnValue;

  LucReturnValue = E_NOT_OK;

  if ((NULL_PTR != LpList) && (NULL_PTR != LpNode) && (ETH_LIST_MAX_NODES != LpList->ulCount))
  {
    if (0UL == LpList->ulCount)
    {
      /* Enqueue at the head */
      LpNode->pPrev = NULL_PTR;
      LpList->pHead = LpNode;
      LpNode->pNext = NULL_PTR;
      LpList->pLast = LpNode;
    }
    else
    {
      /* Enqueue at the last */
      LpList->pLast->pNext = LpNode;                                                                                    
      LpNode->pNext = NULL_PTR;
      LpNode->pPrev = LpList->pLast;
      LpList->pLast = LpNode;
    }
    LpList->ulCount++;

    LucReturnValue = E_OK;
  }
  else
  {
    /* No action required */
  }

  return (LucReturnValue);
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_EnqToNode
**
** Service ID            : NA
**
** Description           : This Api enqueue into the node chain (FIFO method)
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : LpElem - Node data
**
** InOut Parameters      : LpNodes - Node chain
**
** Output Parameters     : None
**
** Return parameter      : LucReturnValue
**                         E_OK - if Node has been enqueue successfully
**                         E_NOT_OK - otherwise
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_039
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Util_EnqToNode(                                                              /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpNodes,                                                                 /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpElem)                                                                    
{
  CONSTP2VAR(Eth_DListNodeType *, AUTOMATIC, ETH_APPL_DATA) LpNodeList =                                                /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_DListNodeType *, AUTOMATIC, ETH_APPL_DATA))LpNodes;                                                      /* PRQA S 0310, 3432 # JV-01, JV-01 */
  CONSTP2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpNode =                                                      /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA))LpElem;                                                         /* PRQA S 0316, 3432 # JV-01, JV-01 */
  P2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpLast;                                                            /* PRQA S 3432 # JV-01 */
  Std_ReturnType LucReturnValue;

  LucReturnValue = E_NOT_OK;

  if ((NULL_PTR != LpNodeList) && (NULL_PTR != LpNode))
  {
    LpNode->pNext = NULL_PTR;

    if (NULL_PTR == *LpNodeList)
    {
      /* Enqueue at the head */
      LpNode->pPrev = NULL_PTR;
      *LpNodeList = LpNode;
    }
    else
    {
      /* Enqueue at the last */
      for (LpLast = *LpNodeList; NULL_PTR != LpLast->pNext; LpLast = LpLast->pNext)                                     
      {
        /* No action required */
      }

      LpNode->pPrev = LpLast;
      LpLast->pNext = LpNode;                                                                                           
    }

    LucReturnValue = E_OK;
  }
  else
  {
    /* No action required */
  }

  return (LucReturnValue);
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_PushToList
**
** Service ID            : NA
**
** Description           : This Api push into the list (FILO method)
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : LpElem - Node data
**
** InOut Parameters      : LpList - Linked list
**
** Output Parameters     : None
**
** Return parameter      : LucReturnValue
**                         E_OK - if Node has been push successfully
**                         E_NOT_OK - otherwise
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_040
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Util_PushToList(                                                             /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList,                                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpElem)                                                                    
{
  CONSTP2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpNode =                                                      /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA))LpElem;                                                         /* PRQA S 0316, 3432 # JV-01, JV-01 */
  Std_ReturnType LucReturnValue;

  LucReturnValue = E_NOT_OK;

  if ((NULL_PTR != LpList) && (NULL_PTR != LpNode) && (ETH_LIST_MAX_NODES != LpList->ulCount))
  {
    if (0UL == LpList->ulCount)
    {
      /* First push */
      LpNode->pPrev = NULL_PTR;
      LpList->pHead = LpNode;
      LpNode->pNext = NULL_PTR;
      LpList->pLast = LpNode;
    }
    else
    {
      /* Second and subsequent push */
      LpList->pHead->pPrev = LpNode;                                                                                    
      LpNode->pPrev = NULL_PTR;
      LpNode->pNext = LpList->pHead;
      LpList->pHead = LpNode;
    }
    LpList->ulCount++;

    LucReturnValue = E_OK;
  }
  else
  {
    /* No action required */
  }

  return (LucReturnValue);
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_PushToNode
**
** Service ID            : NA
**
** Description           : This Api push into the node chain (FILO method)
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : LpElem - Node data
**
** InOut Parameters      : LpNodes - Node chain
**
** Output Parameters     : None
**
** Return parameter      : LucReturnValue
**                         E_OK - if Node has been enqueue successfully
**                         E_NOT_OK - otherwise
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_041
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Util_PushToNode(                                                             /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpNodes,                                                                 /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpElem)                                                                    
{
  CONSTP2VAR(Eth_DListNodeType *, AUTOMATIC, ETH_APPL_DATA) LpNodeList =                                                /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_DListNodeType *, AUTOMATIC, ETH_APPL_DATA))LpNodes;                                                      /* PRQA S 0310, 3432 # JV-01, JV-01 */
  CONSTP2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpNode =                                                      /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA))LpElem;                                                         /* PRQA S 0316, 3432 # JV-01, JV-01 */
  Std_ReturnType LucReturnValue;

  LucReturnValue = E_NOT_OK;

  if ((NULL_PTR != LpNodeList) && (NULL_PTR != LpNode))
  {
    if (NULL_PTR == *LpNodeList)
    {
      /* Push stack */
      LpNode->pPrev = NULL_PTR;
      LpNode->pNext = NULL_PTR;
      *LpNodeList = LpNode;
    }
    else
    {
      /* Push stack */
      LpNode->pPrev = NULL_PTR;
      (*LpNodeList)->pPrev = LpNode;
      LpNode->pNext = *LpNodeList;
      *LpNodeList = LpNode;
    }

    LucReturnValue = E_OK;
  }
  else
  {
    /* No action required */
  }

  return (LucReturnValue);
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_InsertToList
**
** Service ID            : NA
**
** Description           : This Api insert elem node to prev or next a src node
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : LpSrc - Source node
**                         LpElem - Node data
**                         LusFlag - Direction flag
**
** InOut Parameters      : LpList - Linked list
**
** Output Parameters     : None
**
** Return parameter      : LucReturnValue
**                         E_OK - if Node has been insert successfully
**                         E_NOT_OK - otherwise
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_042
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Util_InsertToList(                                                           /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList,                                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpSrc,                                                                     
  CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpElem,                                                                    
  CONST(uint16, AUTOMATIC) LusFlag)
{
  CONSTP2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpSrcNode =                                                   /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA))LpSrc;                                                          /* PRQA S 0316, 3432 # JV-01, JV-01 */
  CONSTP2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpNode =                                                      /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA))LpElem;                                                         /* PRQA S 0316, 3432 # JV-01, JV-01 */
  Std_ReturnType LucReturnValue;

  LucReturnValue = E_NOT_OK;

  if ((NULL_PTR != LpList) && (NULL_PTR != LpSrcNode) && (NULL_PTR != LpNode) &&
      (ETH_LIST_MAX_NODES != LpList->ulCount) && (0U != (LusFlag & (ETH_LIST_PREV | ETH_LIST_NEXT))))
  {
    if (0U != (LusFlag & ETH_LIST_NEXT))
    {
      /* Re-chain insert node at LpSrcNode->pNext */
      LpNode->pPrev = LpSrcNode;
      LpNode->pNext = LpSrcNode->pNext;
      if (NULL_PTR == LpSrcNode->pNext)
      {
        LpList->pLast = LpNode;
      }
      else
      {
        LpSrcNode->pNext->pPrev = LpNode;                                                                               
      }
      LpSrcNode->pNext = LpNode;
    }
    else
    {
      /* Re-chain insert node at LpSrcNode->pPrev */
      LpNode->pPrev = LpSrcNode->pPrev;
      LpNode->pNext = LpSrcNode;
      if (NULL_PTR == LpSrcNode->pPrev)
      {
        LpList->pHead = LpNode;
      }
      else
      {
        LpSrcNode->pPrev->pNext = LpNode;                                                                               
      }
      LpSrcNode->pPrev = LpNode;
    }
    LpList->ulCount++;

    LucReturnValue = E_OK;
  }
  else
  {
    /* No action required */
  }

  return (LucReturnValue);
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_InsertToNode
**
** Service ID            : NA
**
** Description           : This Api insert elem node to prev or next a src node
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : LpElem - Node data
**                         LusFlag - Direction flag
**
** InOut Parameters      : LpSrc - Source node
**
** Output Parameters     : None
**
** Return parameter      : LucReturnValue
**                         E_OK - if Node has been insert successfully
**                         E_NOT_OK - otherwise
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_043
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Util_InsertToNode(                                                           /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpSrc,                                                                     
  CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpElem,                                                                    
  CONST(uint16, AUTOMATIC) LusFlag)
{
  CONSTP2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpSrcNode =                                                   /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA))LpSrc;                                                          /* PRQA S 0316, 3432 # JV-01, JV-01 */
  CONSTP2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpNode =                                                      /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA))LpElem;                                                         /* PRQA S 0316, 3432 # JV-01, JV-01 */
  Std_ReturnType LucReturnValue;

  LucReturnValue = E_NOT_OK;

  if ((NULL_PTR != LpSrcNode) && (NULL_PTR != LpNode) && (0U != (LusFlag & (ETH_LIST_PREV | ETH_LIST_NEXT))))
  {
    if (0U != (LusFlag & ETH_LIST_NEXT))
    {
      /* Re-chain insert node at LpSrcNode->pNext */
      LpNode->pPrev = LpSrcNode;
      LpNode->pNext = LpSrcNode->pNext;
      if (NULL_PTR != LpSrcNode->pNext)
      {
        LpSrcNode->pNext->pPrev = LpNode;                                                                               
      }
      else
      {
        /* No action required */
      }
      LpSrcNode->pNext = LpNode;
    }
    else
    {
      /* Re-chain insert node at LpSrcNode->pPrev */
      LpNode->pPrev = LpSrcNode->pPrev;
      LpNode->pNext = LpSrcNode;
      if (NULL_PTR != LpSrcNode->pPrev)
      {
        LpSrcNode->pPrev->pNext = LpNode;                                                                               
      }
      else
      {
        /* No action required */
      }
      LpSrcNode->pPrev = LpNode;
    }

    LucReturnValue = E_OK;
  }
  else
  {
    /* No action required */
  }

  return (LucReturnValue);
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_GetFromList
**
** Service ID            : NA
**
** Description           : This Api get node from the list
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : LusFlag - Direction flag
**
** InOut Parameters      : LpList - Linked list
**
** Output Parameters     : None
**
** Return parameter      : LpNode
**                         Node address - Node exists in the list.
**                         NULL_PTR - Not found node in the list.
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_044
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC_P2VAR(void, AUTOMATIC, ETH_PRIVATE_CODE) Eth_Util_GetFromList(                                                     /* PRQA S 1505, 3432 # JV-01, JV-01 */
  CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList,                                                            /* PRQA S 3432 # JV-01 */
  CONST(uint16, AUTOMATIC) LusFlag)
{
  P2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpNode;                                                            /* PRQA S 3432 # JV-01 */

  LpNode = NULL_PTR;

  if ((NULL_PTR != LpList) && (0U != (LusFlag & (ETH_LIST_REMOVE | ETH_LIST_NOREMOVE))))
  {
    if (0UL != LpList->ulCount)
    {
      /* Get head node */
      LpNode = LpList->pHead;
      /* Remove node judgment */
      if (0U == (LusFlag & ETH_LIST_NOREMOVE))
      {
        LpList->pHead = LpNode->pNext;                                                                                  
        if (NULL_PTR != LpList->pHead)
        {
          LpList->pHead->pPrev = NULL_PTR;
        }
        else
        {
          /* No action required */
        }

        LpList->ulCount--;
        if (0UL == LpList->ulCount)
        {
          LpList->pLast = NULL_PTR;
        }
        else
        {
          /* No action required */
        }
        LpNode->pNext = NULL_PTR;
      }
      else
      {
        /* No action required */
      }
    }
    else
    {
      /* No action required */
    }
  }
  else
  {
    /* No action required */
  }

  return (P2VAR(void, AUTOMATIC, ETH_APPL_DATA))LpNode;                                                                 
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_GetFromNode
**
** Service ID            : NA
**
** Description           : This Api get node from the nodes
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : LusFlag - Direction flag
**
** InOut Parameters      : LpNodes - Node chain
**
** Output Parameters     : None
**
** Return parameter      : LpNode
**                         Node address - Node exists in the list.
**                         NULL_PTR - Not found node in the list.
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_045
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC_P2VAR(void, AUTOMATIC, ETH_PRIVATE_CODE) Eth_Util_GetFromNode(                                                     /* PRQA S 1505, 3432 # JV-01, JV-01 */
  CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpNodes,                                                                 /* PRQA S 3432 # JV-01 */
  CONST(uint16, AUTOMATIC) LusFlag)
{
  CONSTP2VAR(Eth_DListNodeType *, AUTOMATIC, ETH_APPL_DATA) LpNodeList =                                                /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_DListNodeType *, AUTOMATIC, ETH_APPL_DATA))LpNodes;                                                      /* PRQA S 0310, 3432 # JV-01, JV-01 */
  P2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpNode;                                                            /* PRQA S 3432 # JV-01 */

  LpNode = NULL_PTR;

  if ((NULL_PTR != LpNodeList) && (NULL_PTR != *LpNodeList) &&
     (0U != (LusFlag & (ETH_LIST_REMOVE | ETH_LIST_NOREMOVE))))
  {
    /* Get next node */
    LpNode = (*LpNodeList)->pNext;                                                                                      
    /* Remove node judgment */
    if (0U == (LusFlag & ETH_LIST_NOREMOVE))
    {
      if (NULL_PTR != LpNode)
      {
        LpNode->pPrev = NULL_PTR;
      }
      else
      {
        /* No action required */
      }
      (*LpNodeList)->pNext = NULL_PTR;
      *LpNodeList = LpNode;
    }
    else
    {
      /* No action required */
    }
  }
  else
  {
    /* No action required */
  }

  return (P2VAR(void, AUTOMATIC, ETH_APPL_DATA))LpNode;                                                                 
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_RemoveToList
**
** Service ID            : NA
**
** Description           : This Api remove node from the list
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : LpElem - Remove node data
**
** InOut Parameters      : LpList - Linked list
**
** Output Parameters     : None
**
** Return parameter      : LucReturnValue
**                         E_OK - if Node has been remove successfully
**                         E_NOT_OK - otherwise
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_046
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Util_RemoveToList(                                                           /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList,                                                            /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpElem)                                                                  /* PRQA S 3432 # JV-01 */
{
  CONSTP2VAR(Eth_DListNodeType *, AUTOMATIC, ETH_APPL_DATA) LpNode =                                                    /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_DListNodeType *, AUTOMATIC, ETH_APPL_DATA))LpElem;                                                       /* PRQA S 0310, 3432 # JV-01, JV-01 */
  P2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpRmvNode;                                                         /* PRQA S 3432, 3678 # JV-01, JV-01 */
  Std_ReturnType LucReturnValue;

  LucReturnValue = E_NOT_OK;

  if ((NULL_PTR != LpList) && (NULL_PTR != LpNode) && (NULL_PTR != *LpNode))
  {
    if (0UL != LpList->ulCount)
    {
      /* Re-chain */
      LpRmvNode = *LpNode;
      if (NULL_PTR == LpRmvNode->pPrev)                                                                                 
      {
        LpList->pHead = LpRmvNode->pNext;
      }
      else
      {
        LpRmvNode->pPrev->pNext = LpRmvNode->pNext;                                                                     
      }
      if (NULL_PTR == LpRmvNode->pNext)
      {
        LpList->pLast = LpRmvNode->pPrev;
      }
      else
      {
        LpRmvNode->pNext->pPrev = LpRmvNode->pPrev;                                                                     
      }
      LpList->ulCount--;
      *LpNode = LpRmvNode->pNext;

      LucReturnValue = E_OK;
    }
    else
    {
      /* No action required */
    }
  }
  else
  {
    /* No action required */
  }

  return (LucReturnValue);
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_RemoveToNode
**
** Service ID            : NA
**
** Description           : This Api remove node from the node
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : None
**
** InOut Parameters      : LpNode - Node chain
**
** Output Parameters     : None
**
** Return parameter      : LucReturnValue
**                         E_OK - if Node has been remove successfully
**                         E_NOT_OK - otherwise
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_047
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Util_RemoveToNode(                                                           /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpNode)                                                                  /* PRQA S 3432 # JV-01 */
{
  CONSTP2VAR(Eth_DListNodeType *, AUTOMATIC, ETH_APPL_DATA) LpRmvNode =                                                 /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_DListNodeType *, AUTOMATIC, ETH_APPL_DATA))LpNode;                                                       /* PRQA S 0310, 3432 # JV-01, JV-01 */
  P2VAR(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpNext;                                                            /* PRQA S 3432 # JV-01 */
  Std_ReturnType LucReturnValue;

  LucReturnValue = E_NOT_OK;

  if ((NULL_PTR != LpRmvNode) && (NULL_PTR != *LpRmvNode))
  {
    LpNext = (*LpRmvNode)->pNext;                                                                                       
    (*LpRmvNode)->pNext = NULL_PTR;
    if (NULL_PTR != LpNext)
    {
      (*LpRmvNode)->pPrev = NULL_PTR;
      LpNext->pPrev = NULL_PTR;
    }
    else
    {
      /* No action required */
    }
    *LpRmvNode = LpNext;

    LucReturnValue = E_OK;
  }
  else
  {
    /* No action required */
  }

  return (LucReturnValue);
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_AllRemoveToList
**
** Service ID            : NA
**
** Description           : This Api remove all node from the list
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : None
**
** InOut Parameters      : LpList - Linked list
**
** Output Parameters     : None
**
** Return parameter      : LucReturnValue
**                         E_OK - if Node has been remove successfully
**                         E_NOT_OK - otherwise
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_048
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Util_AllRemoveToList(                                                        /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList)                                                            /* PRQA S 3432 # JV-01 */
{
  P2CONST(void, AUTOMATIC, ETH_APPL_DATA) LpNode;
  Std_ReturnType LucReturnValue;

  LucReturnValue = E_NOT_OK;

  if (NULL_PTR != LpList)
  {
    /* All remove node from the list */
    do
    {
      LpNode = Eth_Util_GetFromList(LpList, ETH_LIST_REMOVE);
    } while (NULL_PTR != LpNode);

    LucReturnValue = E_OK;
  }
  else
  {
    /* No action required */
  }

  return (LucReturnValue);
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_AllRemoveToNode
**
** Service ID            : NA
**
** Description           : This Api remove all node from the list
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : None
**
** InOut Parameters      : LpList - Linked list
**
** Output Parameters     : None
**
** Return parameter      : LucReturnValue
**                         E_OK - if Node has been remove successfully
**                         E_NOT_OK - otherwise
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_049
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_Util_AllRemoveToNode(                                                        /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpNodes)                                                                 /* PRQA S 3432 # JV-01 */
{
  P2CONST(void, AUTOMATIC, ETH_APPL_DATA) LpNode;
  Std_ReturnType LucReturnValue;

  LucReturnValue = E_NOT_OK;

  if (NULL_PTR != LpNodes)
  {
    /* All remove node from the nodes */
    do
    {
      LpNode = Eth_Util_GetFromNode(LpNodes, ETH_LIST_REMOVE);
    }
    while (NULL_PTR != LpNode);

    LucReturnValue = E_OK;
  }
  else
  {
    /* No action required */
  }

  return (LucReturnValue);
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_GetCountFromList
**
** Service ID            : NA
**
** Description           : This Api get number of nodes in the list
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : LpList - Linked list
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LulReturnValue - Number of nodes
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_050
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(uint32, ETH_PRIVATE_CODE) Eth_Util_GetCountFromList(                                                               /* PRQA S 1503 # JV-01 */
  CONSTP2CONST(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList)
{
  uint32 LulReturnValue;

  LulReturnValue = 0UL;

  if (NULL_PTR != LpList)
  {
    LulReturnValue = LpList->ulCount;
  }
  else
  {
    /* No action required */
  }

  return (LulReturnValue);
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_GetCountFromNode
**
** Service ID            : NA
**
** Description           : This Api get number of nodes in the nodes
**
**
** Sync/Async            : Synchronous
**
** Reentrancy            : NA
**
** Input Parameters      : LpNodes - Node chain
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LulReturnValue - Number of nodes
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_051
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(uint32, ETH_PRIVATE_CODE) Eth_Util_GetCountFromNode(                                                               /* PRQA S 1503 # JV-01 */
  CONSTP2CONST(void, AUTOMATIC, ETH_APPL_DATA) LpNodes)
{
  P2CONST(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA) LpNode;
  uint32 LulReturnValue;

  LulReturnValue = 0UL;

  if (NULL_PTR != LpNodes)
  {
    for (LpNode = (P2CONST(Eth_DListNodeType, AUTOMATIC, ETH_APPL_DATA))LpNodes; NULL_PTR != LpNode;                    /* PRQA S 0316 # JV-01 */
         LpNode = LpNode->pNext)
    {
      LulReturnValue++;                                                                                                 /* PRQA S 3383 # JV-01 */
    }
  }
  else
  {
    /* No action required */
  }

  return (LulReturnValue);
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_RamInit
**
** Service ID            : NA
**
** Description           : This Initialize base address of RAM for application
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LpBaseAddr - Start Address for the Ram
**                       : LulRamSize - size of all available memory (in Byte)
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_053
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void *, ETH_PRIVATE_CODE) Eth_Util_RamInit(                                                                        /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpBaseAddr, CONST(uint32, AUTOMATIC) LulRamSize)                           
{
  CONSTP2VAR(Eth_HeapManagerType, AUTOMATIC, ETH_APPL_DATA) LpMemMgr =                                                  /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_HeapManagerType, AUTOMATIC, ETH_APPL_DATA))LpBaseAddr;                                                   /* PRQA S 0316, 3432 # JV-01, JV-01 */

  if (NULL_PTR != LpMemMgr)
  {
    LpMemMgr->pNext = LpMemMgr;
    LpMemMgr->pPrev = LpMemMgr;
    LpMemMgr->ulHeapSize = LulRamSize;
    LpMemMgr->blHeapLock = ETH_FALSE;
  }
  else
  {
    /* No action required */
  }

  return (P2VAR(void, AUTOMATIC, ETH_APPL_DATA))LpMemMgr;                                                               
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_RamAlloc
**
** Service ID            : NA
**
** Description           : This Allocate RAM with given size
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LpHeap - Heap handler
**                       : LulRamSize - size of memory to be allocated
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LulRetAddress
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_054
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void *, ETH_PRIVATE_CODE) Eth_Util_RamAlloc(                                                                       /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpHeap, CONST(uint32, AUTOMATIC) LulRamSize)                             /* PRQA S 3432 # JV-01 */
{
  CONSTP2VAR(Eth_HeapManagerType *, AUTOMATIC, ETH_APPL_DATA) LpMemMgr =                                                /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_HeapManagerType *, AUTOMATIC, ETH_APPL_DATA))LpHeap;                                                     /* PRQA S 0310, 3432 # JV-01, JV-01 */
  CONST(uint32, AUTOMATIC) LulRequiredSize = ETH_ALIGN_TO_CPU((LulRamSize + (uint32)sizeof(Eth_HeapManagerType)));      /* PRQA S 3383, 3469, 3384 # JV-01, JV-01, JV-01 */

  P2VAR(Eth_HeapManagerType, AUTOMATIC, ETH_APPL_DATA) LpHeapNode;                                                      /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_HeapManagerType, AUTOMATIC, ETH_APPL_DATA) LpNewBlock;                                                      /* PRQA S 3432 # JV-01 */
  P2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpRetAddress;

  LpRetAddress = NULL_PTR;

  if (NULL_PTR != LpMemMgr)
  {
    /* Allocation algorithm with circular list */
    LpHeapNode = *LpMemMgr;
    do
    {
      /* If block of heap node is not reserved and block size is more than required size */
      if ((ETH_FALSE == LpHeapNode->blHeapLock) && (LpHeapNode->ulHeapSize >= LulRequiredSize))                         
      {
        /* If block size of heap node-whether required size exceeds management area size of heap node */
        if ((LpHeapNode->ulHeapSize - LulRequiredSize) > (uint32)sizeof(Eth_HeapManagerType))                           
        {
          /* Create the heap node */
          LpNewBlock = (P2VAR(Eth_HeapManagerType, AUTOMATIC, ETH_APPL_DATA))((uint8 *)LpHeapNode + LulRequiredSize);   /* PRQA S 3305, 0310, 3432, 0751, 0488 # JV-01, JV-01, JV-01, JV-01, JV-01 */
          LpNewBlock->ulHeapSize = LpHeapNode->ulHeapSize - LulRequiredSize;                                            
          LpNewBlock->blHeapLock = ETH_FALSE;

          /* Re-chain as circular list */
          LpHeapNode->pNext->pPrev = LpNewBlock;
          LpNewBlock->pNext = LpHeapNode->pNext;
          LpHeapNode->pNext = LpNewBlock;
          LpNewBlock->pPrev = LpHeapNode;

          /* Reserved this heap block */
          LpHeapNode->ulHeapSize = LulRequiredSize;
          LpHeapNode->blHeapLock = ETH_TRUE;

          /* Set next heap node search start position */
          *LpMemMgr = LpNewBlock;
        }
        else
        {
          /* Allocate this heap node without separate the heap node */
          LpHeapNode->blHeapLock = ETH_TRUE;
        }
        LpRetAddress = (P2VAR(void, AUTOMATIC, ETH_APPL_DATA))((uint8 *)LpHeapNode + sizeof(Eth_HeapManagerType));      /* PRQA S 0751, 0488 # JV-01, JV-01 */
        break;
      }
      else
      {
        LpHeapNode = LpHeapNode->pNext;
      }
    } while (LpHeapNode != *LpMemMgr);
  }
  else
  {
    /* No action required */
  }

  return LpRetAddress;
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_RamFree
**
** Service ID            : NA
**
** Description           : This free RAM at given address
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LpHeap - Heap handler
**                       : LulMemAddr - Memory Address need to be freed
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_055
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, ETH_PRIVATE_CODE) Eth_Util_RamFree(                                                                          /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpHeap, CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpMemAddr)            /* PRQA S 3432 # JV-01 */
{
  CONSTP2VAR(Eth_HeapManagerType *, AUTOMATIC, ETH_APPL_DATA) LpMemMgr =                                                /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_HeapManagerType *, AUTOMATIC, ETH_APPL_DATA))LpHeap;                                                     /* PRQA S 0310, 3432 # JV-01, JV-01 */
  P2VAR(Eth_HeapManagerType, AUTOMATIC, ETH_APPL_DATA) LpFreeNode;                                                      /* PRQA S 3432 # JV-01 */

  if ((NULL_PTR != LpMemMgr) && (NULL_PTR != LpMemAddr))
  {
    /* Get the address of memory node */
    LpFreeNode =
      (P2VAR(Eth_HeapManagerType, AUTOMATIC, ETH_APPL_DATA))((uint8 *)LpMemAddr - sizeof(Eth_HeapManagerType));         /* PRQA S 3305, 0310, 3432, 0316, 0488 # JV-01, JV-01, JV-01, JV-01, JV-01 */

    /* If the next node is empty and the next node does not to LpFreeNode */
    if ((ETH_FALSE == LpFreeNode->pNext->blHeapLock) && (LpFreeNode != LpFreeNode->pNext))                              
    {
      if (LpFreeNode < LpFreeNode->pNext)
      {
        /* Marge next heap block into the LpFreeNode */
        if (LpFreeNode->pNext == *LpMemMgr)
        {
          /* Change heap search start position to the LpFreeNode */
          *LpMemMgr = LpFreeNode;
        }
        else
        {
          /* No action required */
        }

        /* Re-chain circular list */
        LpFreeNode->ulHeapSize += LpFreeNode->pNext->ulHeapSize;                                                        /* PRQA S 3383 # JV-01 */
        LpFreeNode->pNext->pNext->pPrev = LpFreeNode;
        LpFreeNode->pNext = LpFreeNode->pNext->pNext;
      }
      else
      {
        /* No action required */
      }
    }
    else
    {
      /* No action required */
    }

    /* If the prev node is empty and the prev node does not to LpFreeNode */
    if ((ETH_FALSE == LpFreeNode->pPrev->blHeapLock) && (LpFreeNode != LpFreeNode->pPrev))                              
    {
      if (LpFreeNode > LpFreeNode->pPrev)
      {
        /* Marge LpFreeNode into the prev node */
        if (LpFreeNode == *LpMemMgr)
        {
          /* Change heap search start position to the prev node */
          *LpMemMgr = LpFreeNode->pPrev;
        }
        else
        {
          /* No action required */
        }

        /* Re-chain circular list */
        LpFreeNode->pPrev->ulHeapSize += LpFreeNode->ulHeapSize;                                                        /* PRQA S 3383 # JV-01 */
        LpFreeNode->pNext->pPrev = LpFreeNode->pPrev;
        LpFreeNode->pPrev->pNext = LpFreeNode->pNext;
      }
      else
      {
        /* No action required */
      }
    }
    else
    {
      /* No action required */
    }
    LpFreeNode->blHeapLock = ETH_FALSE;
  }
  else
  {
    /* No action required */
  }
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Eth_Util_RamSetCircularAddr
**
** Service ID            : NA
**
** Description           : This set the circular address
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LpHeap - Heap handler
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_056
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
FUNC(void, ETH_PRIVATE_CODE) Eth_Util_RamSetCircularAddr(                                                               /* PRQA S 1503 # JV-01 */
  CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpHeap)                                                                    
{
  CONSTP2VAR(Eth_HeapManagerType, AUTOMATIC, ETH_APPL_DATA) LpMemMgr =                                                  /* PRQA S 3432 # JV-01 */
    (P2VAR(Eth_HeapManagerType, AUTOMATIC, ETH_APPL_DATA))LpHeap;                                                       /* PRQA S 0316, 3432 # JV-01, JV-01 */

  if (NULL_PTR != LpMemMgr)
  {
    LpMemMgr->pNext = LpMemMgr;
    LpMemMgr->pPrev = LpMemMgr;
  }
  else
  {
    /* No action required */
  }
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                End of File                                                         **
***********************************************************************************************************************/
