/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_Filter.h                                                                                        */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains software filter functions implementation of Eth Driver */
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
 * 2.1.1: 30/08/2024    : Add definition of Eth_MacFilter struct, Eth_MacFilterMng struct.
 *                      : Add extern function Eth_IsMatchFilter.
 *        08/01/2024    : Remove QA-C Warning 1536
 *        26/12/2023    : Update QAC message.
 * 2.0.1: 18/10/2023    : Added QA-C Warning 1536 according to QA-C 10.3.0
 *                        Added QA-C 10.3.0 comments
 * 2.0.0: 24/07/2023    : Improve QAC comment.
 * 1.5.2: 28/01/2022    : Move the ETH_MACADDR_SIZE to Eth_Types.h.
 * 1.4.2: 24/08/2021    : Modify the format to 120 characters
 * 1.4.1: 07/05/2021    : Remove vendor ID from the file name, API names
 *                        and parameters according to BSW00347 requirement
 *        09/06/2021    : Remove QA-C Warning 3432 according to QA-C 9.5.0
 *        06/07/2021    : Updated QA-C 9.5.0 comments.
 * 1.2.0: 13/07/2020    : Release
 *        29/07/2020    : Add QAC 9.3.1 comment.
 * 1.1.0: 19/06/2020    : Release
 * 1.0.0: 25/03/2020    : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ETH_FILTER_H
#define ETH_FILTER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Eth_Types.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/

/* AUTOSAR release version information */
#define ETH_FILTER_AR_RELEASE_MAJOR_VERSION    ETH_AR_RELEASE_MAJOR_VERSION
#define ETH_FILTER_AR_RELEASE_MINOR_VERSION    ETH_AR_RELEASE_MINOR_VERSION
#define ETH_FILTER_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION

/* File version information */
#define ETH_FILTER_SW_MAJOR_VERSION            ETH_SW_MAJOR_VERSION
#define ETH_FILTER_SW_MINOR_VERSION            ETH_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to use function call       */
/*                       for such a small operation.                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* Compare two MAC addresses, return 0 when both are equal */
#define ETH_COMPARE_MAC(a, b)     (((a).ulH32 ^ (b).ulH32) | ((a).ulL16 ^ ((b).ulL16)))                                 /* PRQA S 3472 # JV-01 */

/* Check whehter a address has the multicast bit */
#define ETH_CHECK_MULTICAST(addr) ((addr).ulH32 & 0x01000000UL)                                                         /* PRQA S 3472 # JV-01 */

#define ETH_INVALID_FILTER_INDEX  0xFFFFFFFFUL

/* Maximum number of filters */
#define ETH_MAX_FILTERS           32UL
/* When all (32) entries are used, ulActiveFilterBits becomes this value */
#define ETH_FILTER_FULL_VALUE     0xFFFFFFFFUL

/* The structure contains MAC address. It consists of two word values
   to improve performance of MAC address comparing operation. */
typedef struct STag_Eth_MacAddressType
{
  /* e.g. when a address is "12:34:56:78:9A:BC": */
  uint32 ulH32; /* has 0x12345678 */
  uint32 ulL16; /* has 0x00009ABC */
} Eth_MacAddressType;

/* Multicast address table */
typedef struct STag_Eth_MacFilter
{
  /* Filter counter */
  uint32 ulCount;
  /* Mac Address */
  Eth_MacAddressType  stMacAddr;
} Eth_MacFilter;

/* Filter Function Management */
typedef struct STag_Eth_MacFilterMng
{
  /* Multicast address table */
  Eth_MacFilter stFilter[ETH_MAX_FILTERS];
  /* Promiscuous mode entering counter */
  uint32 ulPromiscuousCount;
} Eth_MacFilterMng;

/* Macros to convert between byte array and the structure */
#define ETH_PACK_ADDRESS_FROM_8(src, dst)                                                                               /* PRQA S 3472 # JV-01 */\
  do                                                                                                               \
  {                                                                                                                \
    (dst).ulH32 =                                                                                                  \
        ((uint32)(src)[0U] << 24UL) | ((uint32)(src)[1U] << 16UL) | ((uint32)(src)[2U] << 8U) | (uint32)(src)[3U]; \
    (dst).ulL16 = ((uint32)(src)[4U] << 8UL) | (uint32)(src)[5U];                                                  \
  } while (0)

#define ETH_UNPACK_ADDRESS_TO_8(src, dst)                                                                               /* PRQA S 3472 # JV-01 */\
  do                                         \
  {                                          \
    (dst)[0] = (uint8)((src).ulH32 >> 24UL); \
    (dst)[1] = (uint8)((src).ulH32 >> 16UL); \
    (dst)[2] = (uint8)((src).ulH32 >> 8UL);  \
    (dst)[3] = (uint8)(src).ulH32;           \
    (dst)[4] = (uint8)((src).ulL16 >> 8U);   \
    (dst)[5] = (uint8)(src).ulL16;           \
  } while (0)

#define ETH_START_SEC_CONST_32
#include "Eth_MemMap.h"

extern CONST(Eth_MacAddressType, ETH_CONST) Eth_GstBroadcastAddr;
extern CONST(Eth_MacAddressType, ETH_CONST) Eth_GstNullAddr;

#define ETH_STOP_SEC_CONST_32
#include "Eth_MemMap.h"

extern FUNC(uint32, ETH_PRIVATE_CODE)
    Eth_GetFilterIndex(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                       CONSTP2CONST(Eth_MacAddressType, AUTOMATIC, AUTOMATIC) LpMacAddr);

extern FUNC(void, ETH_PRIVATE_CODE) Eth_ClearAllAddressFilters(CONST(uint32, AUTOMATIC) LulCtrlIdx);

extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_AddAddressFilter(CONST(uint32, AUTOMATIC) LulCtrlIdx,
                         CONSTP2CONST(Eth_MacAddressType, AUTOMATIC, AUTOMATIC) LpMacAddr);

extern FUNC(void, ETH_PRIVATE_CODE)
    Eth_RemoveAddressFilter(CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulFilterIdx);

extern FUNC(boolean, ETH_PRIVATE_CODE) Eth_IsMatchFilter(
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONSTP2CONST(Eth_MacAddressType, AUTOMATIC, ETH_APPL_DATA) LpMacAddr);


#endif /* !ETH_FILTER_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
