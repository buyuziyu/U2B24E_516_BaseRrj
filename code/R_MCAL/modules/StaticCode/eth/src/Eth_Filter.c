/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_Filter.c                                                                                        */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains software filter functions implementation of Eth Driver Component.                               */
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
/*                                        Devices:                X2x                                                 */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                          Revision Control History                                                  **
***********************************************************************************************************************/
/*
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Updated QA-C 9.5.0 comments
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 30/08/2024    : Update QAC message
 *                      : Add Eth_IsMatchFilter function
 *                      : Removed QA-C warning 1533, 2814, 2844 according to QA-C 10.3.0
 *                      : Include header file Eth_ETND_Ram.h and Eth_ETNE_Ram.h
 *                      : Remove header file Eth_ETNDE_Ram.h
 * 2.0.0: 27/07/2023    : Add CWE rule into QAC header
 * 1.5.1: 18/10/2021    : Commonized Eth_ETNE_Ram.h and Eth_ETND_Ram.h.
 *        12/01/2021    : Update QA-C 9.5.0 comments
 * 1.4.2: 24/08/2021    : Modify the format to 120 characters
 *        20/08/2021    : Update include file for support U2Bx devices.
 * 1.4.1: 07/05/2021    : Changes to support U2Bx devices.
 *                        Remove vendor ID from the file name, API names
 *        09/06/2021    : Remove QA-C Warning 0404 and 3432 according to QA-C 9.5.0
 *                        and parameters according to BSW00347 requirement
 *        06/07/2021    : Updated QA-C 9.5.0 comments.
 * 1.2.0: 13/07/2020    : Release
 *        29/07/2020    : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020    : Release
 * 1.0.0: 25/03/2020    : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                       Include Section                                                              **
***********************************************************************************************************************/
#include "Eth.h"
#include "Eth_Ram.h"
#if (ETH_MACRO_ETNC == STD_ON)
#include "Eth_ETNC_Ram.h"
#elif (ETH_MACRO_ETNB == STD_ON)
#include "Eth_ETNB_Ram.h"
#elif (ETH_MACRO_ETND == STD_ON)
#include "Eth_ETND_Ram.h"
#elif (ETH_MACRO_ETNE == STD_ON)
#include "Eth_ETNE_Ram.h"
#endif
#if (ETH_MACRO_ETNF == STD_ON)
#include "Eth_ETNF_Ram.h"
#endif
#if (ETH_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Eth.h"
#endif
#include "Eth_Filter.h"

/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ETH_FILTER_C_AR_RELEASE_MAJOR_VERSION ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETH_FILTER_C_AR_RELEASE_MINOR_VERSION ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETH_FILTER_C_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ETH_FILTER_C_SW_MAJOR_VERSION    ETH_SW_MAJOR_VERSION_VALUE
#define ETH_FILTER_C_SW_MINOR_VERSION    ETH_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/
#if (ETH_FILTER_AR_RELEASE_MAJOR_VERSION != ETH_FILTER_C_AR_RELEASE_MAJOR_VERSION)
  #error "Eth_Filter.c : Mismatch in Release Major Version"
#endif
#if (ETH_FILTER_AR_RELEASE_MINOR_VERSION != ETH_FILTER_C_AR_RELEASE_MINOR_VERSION)
  #error "Eth_Filter.c : Mismatch in Release Minor Version"
#endif
#if (ETH_FILTER_AR_RELEASE_REVISION_VERSION != ETH_FILTER_C_AR_RELEASE_REVISION_VERSION)
  #error "Eth_Filter.c : Mismatch in Release Revision Version"
#endif

#if (ETH_FILTER_SW_MAJOR_VERSION != ETH_FILTER_C_SW_MAJOR_VERSION)
  #error "Eth_Filter.c : Mismatch in Software Major Version"
#endif
#if (ETH_FILTER_SW_MINOR_VERSION != ETH_FILTER_C_SW_MINOR_VERSION)
  #error "Eth_Filter.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1533)    : The object '%1s' is only referenced by function '%2s'.                                       */
/* Rule                : MISRA C:2012 Rule-8.9, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : This is accepted, due to the object is defined in separated source C file to followed        */
/*                       coding rule                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to call a function here    */
/*                       for such a small operation.                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is accepted, due to implementation for include memmap is following AUTOSAR rule.        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : The object addressed by this pointer change so it can not be of type "pointer to const"      */
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
/* Message (2:2934)    : Possible: Computing an invalid pointer value.                                                */
/* Rule                : CERTCCM ARR30, ARR37, ARR38, EXP08                                                           */
/* JV-01 Justification : To prevent overhead and excessive nesting of condition statements, this pointer has been     */
/*                       tested valid with many test cases, so there is no problem with the current implementation.   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/
#define ETH_START_SEC_CONST_32
#include "Eth_MemMap.h"

/* Const values of broadcast and null address to be compared */
CONST(Eth_MacAddressType, ETH_CONST) Eth_GstBroadcastAddr =
{
  0xFFFFFFFFUL, 0x0000FFFFU
};
CONST(Eth_MacAddressType, ETH_CONST) Eth_GstNullAddr =                                                                  /* PRQA S 1533 # JV-01 */
{
  0x00000000UL, 0x00000000U
};
#define ETH_STOP_SEC_CONST_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


/***********************************************************************************************************************
**                                         Function Definitions                                                       **
***********************************************************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/***********************************************************************************************************************
** Function Name         : Eth_GetFilterIndex
**
** Service ID            : N/A
**
** Description           : Get the index of the specified MAC address if exists
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx: Index of a controller
**                         LpMacAddr:  Pointer to a MAC address to be searched
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GaaAddressFilters
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_032
***********************************************************************************************************************/
FUNC(uint32, ETH_PRIVATE_CODE) Eth_GetFilterIndex(                                                                      
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2CONST(Eth_MacAddressType, AUTOMATIC, AUTOMATIC) LpMacAddr)
{
  uint32 LulFilterIdx;
  uint32 LulFoundIdx;

  LulFoundIdx = ETH_INVALID_FILTER_INDEX;
  /* Check the specified address is already registered */
  for (LulFilterIdx = 0UL; (ETH_INVALID_FILTER_INDEX == LulFoundIdx) &&
    (LulFilterIdx < ETH_MAX_FILTERS); LulFilterIdx++)
  {
    if ((0UL != (Eth_GaaCtrlStat[LulCtrlIdx].ulActiveFilterBits & (1UL << LulFilterIdx))) &&                            
      (0UL == ETH_COMPARE_MAC(*LpMacAddr, Eth_GaaAddressFilters[LulCtrlIdx][LulFilterIdx])))                            /* PRQA S 3469 # JV-01 */
    {
      LulFoundIdx = LulFilterIdx;
    }
    else
    {
      /* No action required */
    }
  }

  return LulFoundIdx;
}

/***********************************************************************************************************************
** Function Name         : Eth_ClearAllAddressFilters
**
** Service ID            : N/A
**
** Description           : Remove all filters from the filter list and turn off promiscuous mode
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx: Index of a controller
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_033, ETH_DUD_ACT_033_GBL001,
** Reference ID          : ETH_DUD_ACT_033_GBL002
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ClearAllAddressFilters(                                                                
  CONST(uint32, AUTOMATIC) LulCtrlIdx)
{
  Eth_GaaCtrlStat[LulCtrlIdx].ulActiveFilterBits = 0UL;                                                                 
  Eth_GaaCtrlStat[LulCtrlIdx].blPromiscuous = ETH_FALSE;                                                                
}

/***********************************************************************************************************************
** Function Name         : Eth_RemoveAddressFilter
**
** Service ID            : N/A
**
** Description           : Remove a filter from the filter list
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx  : Index of a controller
**                         LulFilterIdx: Index of an address in the filter list
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaCtrlStat
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_034, ETH_DUD_ACT_034_GBL001
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_RemoveAddressFilter(                                                                   
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulFilterIdx)
{
  /* Clear an active bit */
  Eth_GaaCtrlStat[LulCtrlIdx].ulActiveFilterBits &= ~(1UL << LulFilterIdx);                                             
}

/***********************************************************************************************************************
** Function Name         : Eth_AddAddressFilter
**
** Service ID            : N/A
**
** Description           : Add a address filter to the filter list
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx: Index of a controller
**                         LpMacAddr : Pointer to a MAC address to be added
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : At least there is an empty entry in the FilterArray
**
** Global Variable(s)    : Eth_GaaCtrlStat, Eth_GaaAddressFilters
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_035, ETH_DUD_ACT_035_GBL001,
** Reference ID          : ETH_DUD_ACT_035_GBL002
***********************************************************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_AddAddressFilter(                                                                      
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONSTP2CONST(Eth_MacAddressType, AUTOMATIC, AUTOMATIC) LpMacAddr)
{
  uint32 LulFilterIdx;
  boolean LblRegistered;

  LblRegistered = ETH_FALSE;
  for (LulFilterIdx = 0UL; (ETH_FALSE == LblRegistered) && (LulFilterIdx < ETH_MAX_FILTERS); LulFilterIdx++)
  {
    if (0UL == (Eth_GaaCtrlStat[LulCtrlIdx].ulActiveFilterBits & (1UL << (LulFilterIdx))))                              
    {
      Eth_GaaAddressFilters[LulCtrlIdx][LulFilterIdx] = *LpMacAddr;                                                     
      Eth_GaaCtrlStat[LulCtrlIdx].ulActiveFilterBits |= (1UL << LulFilterIdx);
      LblRegistered = ETH_TRUE;
    }
    else
    {
      /* No action required */
    }
  }
}

#if (ETH_MACRO_ETNE == STD_ON)
/*******************************************************************************
** Function Name         : Eth_IsMatchFilter
**
** Service ID            : N/A
**
** Description           : Add a address filter to the filter list
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx: Index of a controller
**                         LpMacAddr : Pointer to a MAC address
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : boolean
**                         ETH_TRUE  : Allow reception to specified MACaddress
**                         ETH_FALSE : Reject reception to specified MACaddress
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaMacFilterMng, Eth_GaaCtrlStat,
**                         Eth_GstBroadcastAddr
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_036
** Reference ID          : ETH_DUD_ACT_036_CRT001, ETH_DUD_ACT_036_CRT002
** Reference ID          : ETH_DUD_ACT_036_CRT003
*******************************************************************************/
FUNC(boolean, ETH_PRIVATE_CODE) Eth_IsMatchFilter(                                                                      
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_MacAddressType, AUTOMATIC, ETH_APPL_DATA) LpMacAddr)
{
  Eth_MacFilterMng* LpMng;                                                                                              /* PRQA S 3678 # JV-01 */
  uint32 LulIdx;
  boolean LbResult;
  
  LbResult = ETH_FALSE;

  /* Get Mac Filter Manager */
  LpMng = &(Eth_GaaMacFilterMng[LulCtrlIdx]);                                                                           

  if (0UL < LpMng->ulPromiscuousCount)                                                                                  
  {
    /* Always returns True when in promiscuous mode */
    LbResult = ETH_TRUE;
  }
  else if (0UL == ETH_COMPARE_MAC(*LpMacAddr, Eth_GstBroadcastAddr))                                                    /* PRQA S 3469 # JV-01 */
  {
    /* Always returns True when Broadcat Address */
    LbResult = ETH_TRUE;
  }
  else
  {
    if (0UL == ETH_COMPARE_MAC(*LpMacAddr, Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr))                                      /* PRQA S 3469 # JV-01 */
    {
      /* Always returns True when Own MAC Address */
      LbResult = ETH_TRUE;
    }
    else
    {
      /* Check Filter Macthing */
      for (LulIdx = 0; LulIdx < ETH_MAX_FILTERS; LulIdx++)
      {
        ETH_ENTER_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);
        if ((0UL < LpMng->stFilter[LulIdx].ulCount) &&
          (0UL == ETH_COMPARE_MAC(*LpMacAddr, LpMng->stFilter[LulIdx].stMacAddr)))                                      /* PRQA S 3469 # JV-01 */
        {
          ETH_EXIT_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);
          
          LbResult = ETH_TRUE;
          break;
        }
        else
        {
          /* No Action Required */
        }
        ETH_EXIT_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);
      }
    }
  }
  
  return LbResult;
}
#endif /* (ETH_MACRO_ETNE == STD_ON) */
#endif /* (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON) */

#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                            End of File                                                             **
***********************************************************************************************************************/
