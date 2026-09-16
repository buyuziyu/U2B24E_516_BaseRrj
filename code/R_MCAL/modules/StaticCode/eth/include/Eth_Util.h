/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_Util.h                                                                                          */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains software utility functions implementation of Eth Driver                                         */
/* Component.                                                                                                         */
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
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 30/08/2024    : Update QAC message
 *                      : Remove QA-C Warning 1534, 1536, update QAC comment.
 * 2.0.1: 18/10/2023    : Added QA-C Warning 1534, 1536 according to QA-C 10.3.0
 *                        Added QA-C 10.3.0 comments
 * 2.0.0: 27/07/2023    : Add CWE rule into QAC header
 * 1.5.0: 12/01/2021    : Update QA-C 9.5.0 comments
 * 1.4.2: 24/08/2021    : Modify the format to 120 characters
 *        26/08/2021    : Updated QA-C 9.5.0 comments
 * 1.4.1: 24/06/2021    : Support heap algorithm APIs.
 *        07/05/2021    : Remove vendor ID from the file name, API names
 *                        and parameters according to BSW00347 requirement
 *        09/06/2021    : Remove QA-C Warning 3432 according to QA-C 9.5.0
 *        06/07/2021    : Updated QA-C 9.5.0 comments.
 * 1.2.0: 13/07/2020    : Release
 *        29/07/2020    : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020    : Release
 * 1.0.1: 04/06/2020    : Remove Eth_59_MemoryNodeType, Eth_59_MemManagerType,
 *                        Eth_59_GaaRamManager and Eth_59_Util_MemCopy.
 *                        Removed unnecessary code.
 *                        Update for improvement by the QA-C.
 * 1.0.0: 25/03/2020    : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ETH_UTIL_H
#define ETH_UTIL_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define ETH_UTIL_AR_RELEASE_MAJOR_VERSION    ETH_AR_RELEASE_MAJOR_VERSION
#define ETH_UTIL_AR_RELEASE_MINOR_VERSION    ETH_AR_RELEASE_MINOR_VERSION
#define ETH_UTIL_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION

/* File version information */
#define ETH_UTIL_SW_MAJOR_VERSION            ETH_SW_MAJOR_VERSION
#define ETH_UTIL_SW_MINOR_VERSION            ETH_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to use function call for   */
/*                       such a small operation.                                                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : The pointers point to this struct are dereferenced in other .c files, so this                */
/*                       implementation should not be hidden.                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is           */
/*                       accepted.                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3430)    : Macro argument expression may require parentheses.                                           */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is           */
/*                       accepted.                                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* CPU archtecture alignment */
#define ETH_32BIT_ALIGN     4U
#define ETH_64BIT_ALIGN     8U

#ifdef CPU_ALIGN_64
#define ETH_ALIGN_TO_CPU(n) ((((n) + ETH_64BIT_ALIGN) - 1ULL) & 0xFFFFFFFFFFFFFFF8ULL)
#else
#define ETH_ALIGN_TO_CPU(n) ((((n) + ETH_32BIT_ALIGN) - 1UL) & 0xFFFFFFFCUL)                                            /* PRQA S 3472 # JV-01 */
#endif

#define ETH_LIST_MAX_NODES  0xFFFFFFFFUL /* Maxinum number of nodes */

#define ETH_LIST_PREV       0x0001U      /* Insert node into prev flag */
#define ETH_LIST_NEXT       0x0002U      /* Insert node into next flag */
#define ETH_LIST_REMOVE     0x0010U      /* Remove node flag */
#define ETH_LIST_NOREMOVE   0x0020U      /* Not remove node flag */

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

typedef struct STag_Eth_DListNodeType                                                                                   /* PRQA S 3630 # JV-01 */
{
  uint32 ulSize;                                                /* Node size */
  P2VAR(struct STag_Eth_DListNodeType, TYPEDEF, TYPEDEF) pNext; /* Next node */                                         /* PRQA S 3430 # JV-01 */
  P2VAR(struct STag_Eth_DListNodeType, TYPEDEF, TYPEDEF) pPrev; /* Prev node */                                         /* PRQA S 3430 # JV-01 */
} Eth_DListNodeType;

typedef struct STag_Eth_ListType                    /* Linked list */                                                   /* PRQA S 3630 # JV-01 */
{
  uint32 ulCount;                                   /* Number of node */
  P2VAR(Eth_DListNodeType, TYPEDEF, TYPEDEF) pLast; /* Last node */                                                     /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_DListNodeType, TYPEDEF, TYPEDEF) pHead; /* Head node */                                                     /* PRQA S 3432 # JV-01 */
} Eth_ListType;

typedef struct STag_Eth_HeapManagerType                                                                                 /* PRQA S 3630 # JV-01 */
{
  P2VAR(struct STag_Eth_HeapManagerType, TYPEDEF, TYPEDEF) pNext; /* Next node */                                       /* PRQA S 3430 # JV-01 */
  P2VAR(struct STag_Eth_HeapManagerType, TYPEDEF, TYPEDEF) pPrev; /* Prev node */                                       /* PRQA S 3430 # JV-01 */
  uint32 ulHeapSize;                                              /* Memory block size */
  boolean blHeapLock;                                             /* Memory lock flag */
  uint8 ucDummy[3];                                               /* Dummy */
} Eth_HeapManagerType;

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"
extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_Util_IniLinkedList(CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList);                                  /* PRQA S 3432 # JV-01 */

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_Util_EnqToList(CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList,                                       /* PRQA S 3432 # JV-01 */
                       CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpElem);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_Util_EnqToNode(CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpNodes,                                            /* PRQA S 3432 # JV-01 */
                       CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpElem);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_Util_PushToList(CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList,                                      /* PRQA S 3432 # JV-01 */
                        CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpElem);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_Util_PushToNode(CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpNodes,                                           /* PRQA S 3432 # JV-01 */
                        CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpElem);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_Util_InsertToList(CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList,                                    /* PRQA S 3432 # JV-01 */
                          CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpSrc,
                          CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpElem, CONST(uint16, AUTOMATIC) LusFlag);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_Util_InsertToNode(CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpSrc,
                          CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpElem, CONST(uint16, AUTOMATIC) LusFlag);

extern FUNC_P2VAR(void, AUTOMATIC, ETH_PRIVATE_CODE)                                                                    /* PRQA S 3432 # JV-01 */
    Eth_Util_GetFromList(
                         CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList,                                     /* PRQA S 3432 # JV-01 */
                         CONST(uint16, AUTOMATIC) LusFlag);

extern FUNC_P2VAR(void, AUTOMATIC, ETH_PRIVATE_CODE)                                                                    /* PRQA S 3432 # JV-01 */
    Eth_Util_GetFromNode(
                         CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpNodes,                                          /* PRQA S 3432 # JV-01 */
                         CONST(uint16, AUTOMATIC) LusFlag);

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_Util_RemoveToList(CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList,                                    /* PRQA S 3432 # JV-01 */
                          CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpElem);                                         /* PRQA S 3432 # JV-01 */
extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_Util_RemoveToNode(CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpNode);                                         /* PRQA S 3432 # JV-01 */

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_Util_AllRemoveToList(CONSTP2VAR(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList);                                /* PRQA S 3432 # JV-01 */

extern FUNC(Std_ReturnType, ETH_PRIVATE_CODE)
    Eth_Util_AllRemoveToNode(CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpNodes);                                     /* PRQA S 3432 # JV-01 */

extern FUNC(uint32, ETH_PRIVATE_CODE)
    Eth_Util_GetCountFromList(CONSTP2CONST(Eth_ListType, AUTOMATIC, ETH_APPL_DATA) LpList);

extern FUNC(uint32, ETH_PRIVATE_CODE) Eth_Util_GetCountFromNode(CONSTP2CONST(void, AUTOMATIC, ETH_APPL_DATA) LpNodes);

extern FUNC(void *, ETH_PRIVATE_CODE)
    Eth_Util_RamInit(CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpBaseAddr, CONST(uint32, AUTOMATIC) LulRamSize);

extern FUNC(void *, ETH_PRIVATE_CODE) Eth_Util_RamAlloc(CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpHeap,            /* PRQA S 3432 # JV-01 */
                                                        CONST(uint32, AUTOMATIC) LulRamSize);

extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_Util_RamFree(CONSTP2VAR(void *, AUTOMATIC, ETH_APPL_DATA) LpHeap,                                               /* PRQA S 3432 # JV-01 */
                     CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpMemAddr);

extern FUNC(void, ETH_PRIVATE_CODE) Eth_Util_RamSetCircularAddr(CONSTP2VAR(void, AUTOMATIC, ETH_APPL_DATA) LpHeap);

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"
#endif /* !ETH_UTIL_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
