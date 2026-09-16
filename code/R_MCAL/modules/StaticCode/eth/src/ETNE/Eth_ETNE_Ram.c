/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_ETNE_Ram.c                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Global RAM variable definitions for Eth Driver an RAM allocation functions                                         */
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
 * 2.4.1: 30/06/2025    : Change ETH_TOTAL_CTRL_CONFIG to ETH_ETNE_CTRLS_SUPPORTED
 *                      : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Update to fix for QAC messages
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 31/10/2024    : Increase SW-VERSION to 2.1.2
 * 2.1.1: 16/07/2024    : Remove Eth_GaaDemEventUnintendedIntChk
 *                        Update QAC message
 * 2.1.1: 19/06/2024    : Change stTimestamp to stTimestampRsw2 in Eth_ETNE_InitializeBuffer
 *        31/05/2024    : Initial Version 
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Eth.h inclusion and macro definitions */
#include "Eth.h"
/* Header file inclusion */
#include "Eth_ETNE_Ram.h"
#include "Eth_Ram.h"
#if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
#include "EthSwt_Cbk.h"
#endif

#if (ETH_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Eth.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#if (ETH_MACRO_ETNE == STD_ON)
/* AUTOSAR release version information */
#define ETH_ETNE_RAM_C_AR_RELEASE_MAJOR_VERSION ETH_AR_RELEASE_MAJOR_VERSION_VALUE
#define ETH_ETNE_RAM_C_AR_RELEASE_MINOR_VERSION ETH_AR_RELEASE_MINOR_VERSION_VALUE
#define ETH_ETNE_RAM_C_AR_RELEASE_REVISION_VERSION ETH_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ETH_ETNE_RAM_C_SW_MAJOR_VERSION    ETH_SW_MAJOR_VERSION_VALUE
#define ETH_ETNE_RAM_C_SW_MINOR_VERSION    ETH_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/

#if (ETH_ETNE_RAM_AR_RELEASE_MAJOR_VERSION != ETH_ETNE_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Eth_ETNE_Ram.c : Mismatch in Release Major Version"
#endif
#if (ETH_ETNE_RAM_AR_RELEASE_MINOR_VERSION != ETH_ETNE_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Eth_ETNE_Ram.c : Mismatch in Release Minor Version"
#endif
#if (ETH_ETNE_RAM_AR_RELEASE_REVISION_VERSION != ETH_ETNE_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Eth_ETNE_Ram.c : Mismatch in Release Revision Version"
#endif


#if (ETH_ETNE_RAM_SW_MAJOR_VERSION != ETH_ETNE_RAM_C_SW_MAJOR_VERSION)
   #error "Eth_ETNE_Ram.c : Mismatch in Software Major Version"
#endif
#if (ETH_ETNE_RAM_SW_MINOR_VERSION != ETH_ETNE_RAM_C_SW_MINOR_VERSION)
   #error "Eth_ETNE_Ram.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
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
/* Message (4:2985)    : This operation is redundant. The value of the result is always that of the left-hand operand.*/
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-398, CWE-561, CWE-569, CWE-633     */
/* JV-01 Justification : The content of LusReqSize will be changed if the user enables the EthSwt option, so the value*/
/*                       of this result is not always that of the left-hand operand.                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569, CWE-738                    */
/* JV-01 Justification : Typecasting is done as per the register size or hardware specific structure.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : The object addressed by this pointer change so it can not be of type "pointer to const"      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3469)    : This usage of a function-like macro looks like it could be replaced by an equivalent         */
/*                       function call.                                                                               */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : To prevent overhead and speed up the processing, there is no need to call a function here    */
/*                       for such a small operation.                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4, CWE Rule CWE-188, CWE-398, CWE-569                    */
/* JV-01 Justification : This implementation is required for heap memory allocation algorithm                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4391)    : A composite expression of 'essentially unsigned' type (unsigned char) is being cast to a     */
/*                       wider unsigned type 'unsigned short'.                                                        */
/* Rule                : MISRA C:2012 Rule-10.8, CWE Rule CWE-136                                                     */
/* JV-01 Justification : This casting is necessary and is confirmed to be no problem.                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1533)    : The object 'entity' is only referenced by function 'func'.                                   */
/* Rule                : MISRA C:2012 Rule-8.9, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : This is accepted, due to the object is defined in seperated cource C file to followed        */
/*                       coding rule                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : %s' has external linkage and is being defined without any previous declaration.              */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0613)    : [L] Size of object '%s' exceeds 65535 bytes - program does not conform strictly to ISO:C90.  */
/* Rule                : MISRA-C:2012 Dir 1.1                                                                         */
/* JV-01 Justification : Size of global variable exceeds 65535 due to size of Tx buffer byte of Eth module.           */
/*       Verification  : There is no problem because it is an intended design considering the space-time tradeoff,    */
/*                       that is, scalability.                                                                        */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7                                                         */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2982)    : This assignment is redundant. The value of this object is never used before being modified.  */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563      */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The variable needs to be initialized before using it.                                        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3673)    : The object addressed by the pointer parameter '%s' is not modified and so the pointer        */
/*                       could be of type 'pointer to const'.                                                         */
/* Rule                : CERTCCM DCL00, DCL13, MISRA C:2012 Rule-8.13                                                 */
/* JV-01 Justification : Pointer variable is used to modify the value at the address so the pointer cannot be         */
/*                       declared as 'pointer to const' type.                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1257)    : An integer constant suffixed with L or LL is being converted to a type of lower rank on      */
/*                       assignment.                                                                                  */
/* Rule                : CERTCCM INT02, MISRA C:2012 Rule-10.3, CWE-136, CWE-192                                      */
/* JV-01 Justification : Depending on SPI functionality, lower rank on assignment is needed.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1502)    : The object 'name' is defined but is not used within this project.                            */
/* Rule                : MISRA C:2012 Rule-2.8, CWE Rule CWE-398, CWE-569, CERTC Rule MSC13                           */
/* JV-01 Justification : Array is used in another part of driver code. There is no problem in use                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define ETH_START_SEC_VAR_NO_INIT_8
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_VAR_NO_INIT_8
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_NO_INIT_16
#include "Eth_MemMap.h"

#define ETH_STOP_SEC_VAR_NO_INIT_16
#include "Eth_MemMap.h"

#define ETH_START_SEC_VAR_NO_INIT_32
#include "Eth_MemMap.h"

STATIC VAR(uint32, ETH_VAR_NO_INIT) Eth_GaaTxAllocCnt[ETH_MAX_CTRLS_SUPPORTED][ETH_TXQ_NUM_RSW2];

#define ETH_STOP_SEC_VAR_NO_INIT_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_NO_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

P2VAR(void, ETH_VAR_FAST_NO_INIT, ETH_VAR_FAST_NO_INIT) Eth_GpDescHeap;                                                 
/* Global variable to store pointer to Configuration */
P2CONST(Eth_GwcaRegValue, ETH_CONST, ETH_CONFIG_CONST) volatile Eth_GpGwcaRegPtr;
P2CONST(Eth_GlobalPauseConfiguration, ETH_CONST, ETH_CONFIG_CONST) volatile Eth_GpGlobalPauseCfgPtr;
P2CONST(Eth_BothCoreConfiguration, ETH_CONST, ETH_CONFIG_CONST) volatile Eth_GpBothCoreCfgPtr;                          /* PRQA S 1533 # JV-01 */
P2CONST(Eth_EthConfigType, ETH_CONST, ETH_CONFIG_CONST) volatile Eth_GaaSerdesChConfig[ETH_RACE_PORT_TSNA_N];           /* PRQA S 1502 # JV-01 */

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
/* Global variable that stores the pointer of Time Stamp Descriptor */
P2VAR(Eth_TSDescType, ETH_VAR_FAST_NO_INIT, ETH_VAR_FAST_NO_INIT) Eth_GpNextTsDesc;                                     /* PRQA S 3432 # JV-01 */
#endif

#define ETH_STOP_SEC_VAR_NO_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* Multicast address filter list */
#if (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON)
VAR(Eth_MacFilterMng, ETH_VAR_NO_INIT) Eth_GaaMacFilterMng[ETH_MAX_CTRLS_SUPPORTED];                                    /* PRQA S 1533 # JV-01 */
#endif /* (ETH_UPDATE_PHYS_ADDR_FILTER == STD_ON) */

/* Descriptor Chain Infomation Map */
VAR(Eth_DescChainMap, ETH_VAR_NO_INIT) Eth_GstDescChainMap;                                                             

#define ETH_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_BOOLEAN
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

VAR(boolean, ETH_VAR_INIT)Eth_GaaRsw2ETHAValid[ETH_RACE_PORT_TSNA_N] =                                                  /* PRQA S 3408, 1502 # JV-01, JV-01 */
{
  ETH_FALSE,
  ETH_FALSE
};

VAR(boolean, ETH_VAR_INIT)Eth_GaaRsw2PortValid[ETH_RACE_PORT_N] =                                                       
{
  ETH_FALSE,
  ETH_FALSE,
  ETH_FALSE
};

VAR(boolean, ETH_VAR_INIT)Eth_GaaRsw2GWCACtrlValid = ETH_FALSE;                                                         

#define ETH_STOP_SEC_VAR_INIT_BOOLEAN
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_8
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_INIT_8
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_16
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_INIT_16
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

VAR(uint32, ETH_VAR_INIT) Eth_GulRxMaxFrameSize = ETH_GWCA_MAX_PAYLOAD_SIZE;                                            

#define ETH_STOP_SEC_VAR_INIT_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_CLEARED_DESCRIPTOR_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
VAR(uint8, ETH_VAR_NO_INIT) 
  Eth_GaaMemPoolDesc[ETH_ETNE_CTRLS_SUPPORTED * ((ETH_TXQ_NUM_RSW2 * (16UL + ((64UL + 1UL) * ETH_EXT_TX_DIR_DESC_SIZE)))/* PRQA S 1533, 0613 # JV-01, JV-01 */
                                             +(ETH_RXQ_NUM_RSW2 * (16UL + ((64UL + 1UL) * ETH_EXT_RX_ETH_DESC_SIZE))))];
VAR(Eth_LinkDescTypeRsw2, ETH_VAR_NO_INIT) Eth_GaaLinkFixTable[ETH_RACE_AXI_CHAIN_N];                                   

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
VAR(Eth_TSDescType, ETH_VAR_NO_INIT) Eth_GaaTsDescChain[ETH_MAX_TS_DESCRIPTOR + ETH_CYCLIC_DESC_NUM];                   
#endif

#define ETH_STOP_SEC_VAR_CLEARED_DESCRIPTOR_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#define ETH_START_SEC_VAR_PORT_BUFFER_0
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_PORT_BUFFER_0
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if defined(ETH_RAM_SIZE_1)
#define ETH_START_SEC_VAR_PORT_BUFFER_1
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_PORT_BUFFER_1
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* defined(ETH_RAM_SIZE_1) */

#define ETH_START_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/* The Function table for ETNE */
VAR(Eth_HwFuncTableType, ETH_VAR_INIT) Eth_EtneFunc =                                                                   
{
  &Eth_ETNE_InitializeBuffer,
  &Eth_ETNE_PreprocessBuffer,
  &Eth_ETNE_GetTxBuffer,
  &Eth_ETNE_ReleaseTxBuffer,
  &Eth_ETNE_CheckProvideBuffer,
  &Eth_ETNE_PreprocessFrame,
  &Eth_ETNE_FindTxBufferHandler,
  &Eth_ETNE_HwInit,
  #if (ETH_DEINIT_API == STD_ON)
  NULL_PTR,
  #endif
  &Eth_ETNE_HwDisableController,
  &Eth_ETNE_HwEnableController,
  &Eth_ETNE_HwTransmit,
  #if (ETH_GET_COUNTER_VALUES_API == STD_ON)
  &Eth_ETNE_HwGetCounterValues,
  #endif
  #if (ETH_GET_RX_STATS_API == STD_ON)
  &Eth_ETNE_HwGetRxStats,
  #endif
  #if (ETH_GET_TX_STATS_API == STD_ON)
  &Eth_ETNE_HwGetTxStats,
  #endif
  #if (ETH_GET_TX_ERROR_COUNTER_VALUES_API == STD_ON)
  &Eth_ETNE_HwGetTxErrorCounterValues,
  #endif
  &Eth_ETNE_HwMainFunction,
  #if (ETH_CTRL_ENABLE_TX_POLLING == STD_ON)
  &Eth_ETNE_HwTxConfirmation,
  #else
  NULL_PTR, /* pHwTxConfirmation */
  #endif
  #if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
  #if (ETH_AR_VERSION >= ETH_AR_431_VERSION)
  &Eth_ETNE_HwCheckFifoIndex,
  #endif
  #endif
  #if (ETH_CTRL_ENABLE_RX_POLLING == STD_ON)
  &Eth_ETNE_HwReceive,
  #else
  NULL_PTR, /* pHwReceive */
  #endif
  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  &Eth_ETNE_HwSetIncrementTimeForGptp,
  &Eth_ETNE_HwSetOffsetTimeForGptp,
  &Eth_ETNE_HwGetCurrentTime,
  &Eth_ETNE_HwGetEgressTimeStamp,
  &Eth_ETNE_HwGetIngressTimeStamp,
  #endif
  #if (ETH_CTRL_ENABLE_MII == STD_ON)
  #if ((ETH_MACRO_ETND == STD_ON) || (ETH_MACRO_ETNE == STD_ON))
  &Eth_ETNE_HwReadMii,
  &Eth_ETNE_HwWriteMii,
  #endif
  #if ((ETH_MACRO_ETNB == STD_ON) || (ETH_MACRO_ETNC == STD_ON) || (ETH_MACRO_ETNF == STD_ON))
  NULL_PTR, /* pHwWriteMiiBit */
  NULL_PTR /* pHwReadMiiBit */
  #endif
  #endif
};

#define ETH_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_CLEARED_USER_RAM_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
VAR(uint32, ETH_VAR_NO_INIT) Eth_GaaRsw2PortCtrlIdx[ETH_RACE_PORT_N];                                                   

#define ETH_STOP_SEC_VAR_CLEARED_USER_RAM_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define ETH_START_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/*******************************************************************************
** Function Name         : Eth_ETNE_InitializeBuffer
**
** Service ID            : N/A
**
** Description           : Initialize the Tx buffer ring
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : controller index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Eth_GaaRxBufferIndex, Eth_GaaTxAllocCnt,
**                         Eth_GpNextTsDesc, Eth_GaaTxBufferTotal,
**                         Eth_GaaTxBufferMgrTable, Eth_GaaCtrlStat,
**                         Eth_GaaRxFrame
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_401
** Reference ID          : ETH_DUD_ACT_401_GBL001, ETH_DUD_ACT_401_GBL002
** Reference ID          : ETH_DUD_ACT_401_GBL003, ETH_DUD_ACT_401_GBL004
** Reference ID          : ETH_DUD_ACT_401_GBL005, ETH_DUD_ACT_401_GBL006
** Reference ID          : ETH_DUD_ACT_401_GBL007, ETH_DUD_ACT_401_GBL008
*******************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_InitializeBuffer(CONST(uint32, AUTOMATIC) LulCtrlIdx)                             /* PRQA S 1505 # JV-01 */
{
  uint32 LulCnt;
  P2VAR(Eth_TxBufferType, AUTOMATIC, ETH_APPL_DATA) LpTxBuffer;                                                         /* PRQA S 3432 # JV-01 */

  /* Initialize resource information */
  Eth_GaaRxBufferIndex[LulCtrlIdx] = 0UL;                                                                               
  Eth_GaaCtrlStat[LulCtrlIdx].ulTxBufTail = 0UL;                                                                        
  Eth_GaaRxFrame[LulCtrlIdx].ulFrameAddr = 0UL;                                                                         
  Eth_GaaRxFrame[LulCtrlIdx].ulEthTypeAddr = 0UL;                                                                       
  Eth_GaaRxFrame[LulCtrlIdx].ulFrameLength = 0UL;                                                                       
  #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
  Eth_GaaRxFrame[LulCtrlIdx].stTimestampRsw2.ulTSNS = 0UL;                                                              /* PRQA S 1257 # JV-01 */
  Eth_GaaRxFrame[LulCtrlIdx].stTimestampRsw2.ulTSV = 0UL;                                                               /* PRQA S 1257 # JV-01 */
  Eth_GaaRxFrame[LulCtrlIdx].stTimestampRsw2.ulTSD = 0UL;                                                               /* PRQA S 1257 # JV-01 */
  Eth_GaaRxFrame[LulCtrlIdx].stTimestampRsw2.ulTSS = 0UL;                                                               
  #endif
  /* Initialize Tx buffer index list */
  for (LulCnt = 0UL; LulCnt < Eth_GaaTxBufferTotal[LulCtrlIdx]; LulCnt++)                                               
  {
    LpTxBuffer = (P2VAR(Eth_TxBufferType, AUTOMATIC, ETH_APPL_DATA))&Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulCnt];       /* PRQA S 3432 # JV-01 */
    LpTxBuffer->pBufferHdr = NULL_PTR;                                                                                  
    LpTxBuffer->blTxOngoing = ETH_FALSE;
  }

  /* Initialize buffer counter */
  for (LulCnt = 0UL; LulCnt < ETH_TXQ_NUM_RSW2; LulCnt++)
  {
    Eth_GaaTxAllocCnt[LulCtrlIdx][LulCnt] = 0UL;                                                                        
    Eth_GaaCtrlStat[LulCtrlIdx].stHwStat.aaBufTxCnt[LulCnt] = 0UL;                                                      
  }
}

/*******************************************************************************
** Function Name         : Eth_ETNE_PreprocessBuffer
**
** Service ID            : N/A
**
** Description           : Write source address to all Tx Buffers in advance
**                         because source address is never changed while
**                         a controller mode is ACTIVE.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LulCtrlIdx     : controller index
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_534
*******************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_PreprocessBuffer(CONST(uint32, AUTOMATIC) LulCtrlIdx)                             /* PRQA S 1505 # JV-01 */
{
  /* No action required because this function is retained for RSW2 compatibility. */
  (void)LulCtrlIdx;
}

/*******************************************************************************
** Function Name         : Eth_GetTxBuffer
**
** Service ID            : N/A
**
** Description           : Get a buffer from the Tx buffer ring
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulCtrlIdx     : controller index
**                         LucPriority
**
** InOut Parameters      : LenBytePtr
**
** Output Parameters     : LpBufIdxPtr
**                         LpBufPtr
**
** Return parameter      : BUFREQ_OK
**                         BUFREQ_E_NOT_OK
**                         BUFREQ_E_OVFL
**                         BUFREQ_E_BUSY
**
** Preconditions         : None
**
** Global Variables Used : Eth_GaaTxBufferMgrTable, Eth_GaaTxAllocCnt
**                         Eth_GaaTxBufferTotal, Eth_GaaHeap,
**                         Eth_GpCtrlConfigPtr, Eth_GaaCtrlStat
**
** Function(s) invoked   : EthSwt_EthTxAdaptBufferLength, Eth_Util_RamAlloc,
**                         EthSwt_EthTxPrepareFrame
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_403
** Reference ID          : ETH_DUD_ACT_403_CRT001, ETH_DUD_ACT_403_CRT002
** Reference ID          : ETH_DUD_ACT_403_GBL001, ETH_DUD_ACT_403_GBL002
** Reference ID          : ETH_DUD_ACT_403_GBL003, ETH_DUD_ACT_403_GBL004
** Reference ID          : ETH_DUD_ACT_403_GBL005, ETH_DUD_ACT_403_GBL006
*******************************************************************************/
FUNC(BufReq_ReturnType , ETH_PRIVATE_CODE) Eth_ETNE_GetTxBuffer(                                                        /* PRQA S 1505 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(uint8, AUTOMATIC) LucPriority,
  CONSTP2VAR(Eth_BufIdxType, AUTOMATIC, ETH_APPL_DATA) LpBufIdxPtr,                                                     /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint8*, AUTOMATIC, ETH_APPL_DATA) LpBufPtr,                                                                /* PRQA S 3432 # JV-01 */
  CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr)                                                              /* PRQA S 3432 # JV-01 */
{
  P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA) LpHwUnitConfig;
  BufReq_ReturnType LenReturnValue;
  Eth_BufHandlerType* LpTxBufferNode;
  uint32 LulRingIdx;
  uint32 LulTxBufferMax;
  uint16 LusTxPayloadMax;
  uint16 LusReqSize;
  #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
  P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) LpDataPtr;                                                                     /* PRQA S 3432 # JV-01 */
  Std_ReturnType LucReturnValue;
  #endif

  LpHwUnitConfig =
    (P2CONST(Eth_ETNEConfigType, AUTOMATIC, ETH_APPL_DATA))Eth_GpCtrlConfigPtr[LulCtrlIdx].pHwUnitConfig;               /* PRQA S 0316 # JV-01 */
  LulTxBufferMax = LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LucPriority].ulQueueBufs;                               
  LusTxPayloadMax =
    (uint16)(LpHwUnitConfig->stQueueConfig.pTxQueueConfig[LucPriority].ulMaxFrameSize - ETH_HEADER_SIZE);               /* PRQA S 3383 # JV-01 */

  /* If the requested size is smaller than the minimum size, expand it to the minimum size */
  if ((uint16)ETH_MIN_PAYLOAD_SIZE > *LenBytePtr)                                                                       
  {
    *LenBytePtr = (uint16)ETH_MIN_PAYLOAD_SIZE;
  }
  else
  {
    /* No action required */
  }

  LusReqSize = *LenBytePtr;
  #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
  /* Added Switch Management information */
  EthSwt_EthTxAdaptBufferLength(&LusReqSize);
  #endif

  if (0UL == LulTxBufferMax)
  {
    LenReturnValue = BUFREQ_E_NOT_OK;
  }
  else if (LusReqSize > LusTxPayloadMax)
  {
    /* If the requested size is larger than the buffer, return error */
    *LenBytePtr = LusTxPayloadMax - (LusReqSize - *LenBytePtr);                                                         /* PRQA S 2985 # JV-01 */
    LenReturnValue = BUFREQ_E_OVFL;
  }
  else
  {
    /* Enter the critical section protection */
    ETH_ENTER_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

    /* Check the number of the Tx buffers allocated */
    if (Eth_GaaTxAllocCnt[LulCtrlIdx][LucPriority] < LulTxBufferMax)                                                    
    {
      /* Get tx buffer index */
      LulRingIdx = Eth_GaaCtrlStat[LulCtrlIdx].ulTxBufTail;                                                             
      while (NULL_PTR != Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulRingIdx].pBufferHdr)                                    
      {
        /* Next buffer index */
        LulRingIdx = (LulRingIdx + 1UL) % Eth_GaaTxBufferTotal[LulCtrlIdx];                                             /* PRQA S 3383 # JV-01 */
      }


      /* Get the Tx buffer management node and Tx buffer */
      LpTxBufferNode = (Eth_BufHandlerType *)Eth_Util_RamAlloc(&Eth_GaaHeap[LulCtrlIdx],                                /* PRQA S 0316 # JV-01 */
        (uint32)(LusReqSize + ETH_HEADER_SIZE + sizeof(Eth_BufHandlerType) + ETH_TX_PAYLOAD_PADDING));                  /* PRQA S 3383 # JV-01 */
      if (NULL_PTR != LpTxBufferNode)
      {
        /* Set next buffer index */
        Eth_GaaCtrlStat[LulCtrlIdx].ulTxBufTail = (LulRingIdx + 1UL) % Eth_GaaTxBufferTotal[LulCtrlIdx];                /* PRQA S 3383 # JV-01 */
        Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulRingIdx].pBufferHdr = LpTxBufferNode;
        Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulRingIdx].blTxOngoing = ETH_FALSE;

        LpTxBufferNode->ulbufIdx = LulRingIdx;
        LpTxBufferNode->ulbufAddr = (uint32)LpTxBufferNode + (uint32)sizeof(Eth_BufHandlerType)                         /* PRQA S 0306, 3383 # JV-01, JV-01 */
                                                           + ETH_TX_PAYLOAD_PADDING;                                    /* PRQA S 3383 # JV-01 */
        LpTxBufferNode->ulTxLength  = 0UL;
        LpTxBufferNode->ucPriority  = LucPriority;
        LpTxBufferNode->blbenableTS = ETH_FALSE;
        LpTxBufferNode->blTxConfirm = ETH_FALSE;
        #if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)
        LpTxBufferNode->enTimeQual = ETH_INVALID;
        LpTxBufferNode->stTimeStamp.nanoseconds = (uint32)0UL;
        LpTxBufferNode->stTimeStamp.seconds     = (uint32)0UL;
        LpTxBufferNode->stTimeStamp.secondsHi   = (uint16)0U;
        #endif

        *LpBufIdxPtr = (Eth_BufIdxType)LpTxBufferNode->ulbufIdx;                                                        
        *LpBufPtr = (uint8 *)(LpTxBufferNode->ulbufAddr + (uint32)ETH_HEADER_SIZE);                                     /* PRQA S 0306, 3383 # JV-01, JV-01 */
        LpTxBufferNode->ulEthTypeAddr = LpTxBufferNode->ulbufAddr + ETH_SRC_DST_ADDRESS_SIZE;                           /* PRQA S 3383 # JV-01 */

        #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
        LpDataPtr = (uint8 *)(LpTxBufferNode->ulEthTypeAddr);                                                           /* PRQA S 0306 # JV-01 */
        /* Added Switch Management information */
        LusReqSize = *LenBytePtr;
        /* Since the maximum value of controller index is 4, casting to uint8 does no problem. */
        LucReturnValue = EthSwt_EthTxPrepareFrame((uint8)LulCtrlIdx, *LpBufIdxPtr, &LpDataPtr, &LusReqSize);
        if (E_OK == LucReturnValue)
        {
          LpTxBufferNode->ulEthTypeAddr  = (uint32)LpDataPtr;                                                           /* PRQA S 0306 # JV-01 */
          *LpBufPtr = (uint8 *)((uint32)LpDataPtr + ETH_ETHERTYPE_SIZE);                                                /* PRQA S 0306, 3383 # JV-01, JV-01 */
        }
        else
        {
          /* If it is not a switch frame, use it as a normal frame */
        }
        #endif

        LenReturnValue = BUFREQ_OK;

        /* Increment Tx buffer counter */
        Eth_GaaTxAllocCnt[LulCtrlIdx][LucPriority]++;                                                                   
      }
      else
      {
        LenReturnValue = BUFREQ_E_BUSY;
      }
    }
    else
    {
      LenReturnValue = BUFREQ_E_BUSY;
    }
    /* Exit the critical section protection */
    ETH_EXIT_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);
  }

  return LenReturnValue;
}

/*******************************************************************************
** Function Name         : Eth_ETNE_ReleaseTxBuffer
**
** Service ID            : N/A
**
** Description           : Release a Tx buffer and store it to the tail of the
**                         Tx buffer ring
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : LulCtrlIdx     : controller index
**                         LulBufIdx      : index to the buffer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Eth_GaaHeap, Eth_GaaTxBufferMgrTable, Eth_GaaTxAllocCnt
**
** Function(s) invoked   : Eth_Util_RamFree
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_404
** Reference ID          : ETH_DUD_ACT_404_GBL001, ETH_DUD_ACT_404_GBL002
** Reference ID          : ETH_DUD_ACT_404_GBL003
*******************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_ReleaseTxBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx)
{
  CONST(uint32, AUTOMATIC) LulPriority = Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr->ucPriority;         
  /* Release tx buffer handler */
  Eth_Util_RamFree(&Eth_GaaHeap[LulCtrlIdx], (void *)Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr);        
  Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr = NULL_PTR;
  Eth_GaaTxAllocCnt[LulCtrlIdx][LulPriority]--;                                                                         /* PRQA S 3383 # JV-01 */
}

/*******************************************************************************
** Function Name         : Eth_ETNE_PreprocessFrame
**
** Service ID            : N/A
**
** Description           : This function sets the destination MAC address
**                         and Ethernet type for the Tx buffer.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx     : controller index
**                         LulBufIdx      : index to the buffer
**                         LulFrameType   : ether type
**                         LpPhysAddrPtr  : destination mac address
**                         LpPayloadLen   : payload length
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : Eth_GaaTxBufferMgrTable, Eth_GaaCtrlStat
**
** Function(s) invoked   : EthSwt_EthTxProcessFrame
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_405
** Reference ID          : ETH_DUD_ACT_405_CRT001, ETH_DUD_ACT_405_CRT002
** Reference ID          : ETH_DUD_ACT_405_GBL001, ETH_DUD_ACT_405_GBL002
*******************************************************************************/
FUNC(void, ETH_PRIVATE_CODE) Eth_ETNE_PreprocessFrame(                                                                  /* PRQA S 1505 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx,
  CONST(uint32, AUTOMATIC) LulBufIdx,
  CONST(uint32, AUTOMATIC) LulFrameType,
  CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) LpPhysAddrPtr,
  CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LpPayloadLen)                                                            /* PRQA S 3432, 3673 # JV-01, JV-01 */
{
  P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) LpBufPtr;                                                               /* PRQA S 3432 # JV-01 */
  P2VAR(Eth_BufHandlerType, AUTOMATIC, ETH_APPL_DATA) LpBufHandlerPtr;                                                  /* PRQA S 3432, 3678 # JV-01, JV-01 */
  #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
  P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) LpDataPtr;                                                                     /* PRQA S 3432 # JV-01 */
  uint16 LusTxLength;
  Std_ReturnType LucReturnValue;
  #endif

  ETH_ENTER_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

  /* Get Tx buffer address */
  LpBufHandlerPtr = Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr;                                          

  ETH_EXIT_CRITICAL_SECTION(ETH_RAM_DATA_PROTECTION);

  LpBufPtr = (Eth_DataType *)LpBufHandlerPtr->ulbufAddr;                                                                /* PRQA S 0306 # JV-01 */

  #if (ETH_ETHSWITCH_MANAGEMENT_SUPPORT == STD_ON)
  LpDataPtr = (P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA))(LpBufHandlerPtr->ulbufAddr + ETH_SRC_DST_ADDRESS_SIZE);          /* PRQA S 0306, 3383, 3432 # JV-01, JV-01, JV-01 */
  /* Since the maximum value of buffer size is 1518, casting to uint16 does no problem. */
  LusTxLength = *LpPayloadLen;                                                                                          
  /* decreased by the management information length */
  /* Since the maximum value of controller index is 4, casting to uint8 does no problem. */
  LucReturnValue = EthSwt_EthTxProcessFrame((uint8)LulCtrlIdx, LpBufHandlerPtr->ulbufIdx, &LpDataPtr, &LusTxLength);
  if (E_OK == LucReturnValue)
  {
    LpBufPtr = (Eth_DataType *)(LpBufHandlerPtr->ulEthTypeAddr -                                                        /* PRQA S 0306, 3383 # JV-01, JV-01 */
                    (ETH_SRC_DST_ADDRESS_SIZE + (uint32)(LusTxLength - *LpPayloadLen)));                                /* PRQA S 3383, 4391 # JV-01, JV-01 */
    LpBufHandlerPtr->ulbufAddr = (uint32)LpBufPtr;                                                                      /* PRQA S 0306 # JV-01 */
    *LpPayloadLen = LusTxLength;
  }
  else
  {
    /* If EthSwt_SetMgmtInfo is not called, normal operation */
  }
  #else
  (void)LpPayloadLen;
  #endif

  /* Copy destination address */
  ETH_COPY_MAC_ADDRESS((CONST(uint8, AUTOMATIC) *)LpPhysAddrPtr, (uint8 *)LpBufPtr);                                    /* PRQA S 3469 # JV-01 */
  LpBufPtr = LpBufPtr + ETH_MACADDR_SIZE;                                                                               /* PRQA S 0488 # JV-01 */

  ETH_UNPACK_ADDRESS_TO_8(Eth_GaaCtrlStat[LulCtrlIdx].stMacAddr, LpBufPtr);                                             /* PRQA S 3469 # JV-01 */
  LpBufPtr = LpBufPtr + ETH_MACADDR_SIZE;                                                                               /* PRQA S 0488, 2982 # JV-01, JV-01 */

  /* Casted to uint8 to extract the required 1 byte. */
  LpBufPtr = (Eth_DataType *)LpBufHandlerPtr->ulEthTypeAddr;                                                            /* PRQA S 0306 # JV-01 */
  *LpBufPtr = (Eth_DataType)((uint8)(LulFrameType >> ETH_BYTE_BITS));                                                   
  LpBufPtr++;                                                                                                           
  /* Casted to uint8 to extract the required 1 byte. */
  *LpBufPtr = (Eth_DataType)((uint8)LulFrameType);                                                                      

}

/*******************************************************************************
** Function Name         : Eth_ETNE_CheckProvideBuffer
**
** Service ID            : N/A
**
** Description           : This function checks whether the memory
**                         at the specified buffer index has been allocated.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx     : controller index
**                         LulBufIdx      : index to the buffer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : E_OK : Success
**                         E_NOT_OK : Failure
**
** Preconditions         : None
**
** Global Variables Used : Eth_GaaTxBufferMgrTable
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_406
** Reference ID          : ETH_DUD_ACT_406_GBL001
*******************************************************************************/
FUNC(Std_ReturnType, ETH_PRIVATE_CODE) Eth_ETNE_CheckProvideBuffer(
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx)
{
  Std_ReturnType LucReturnValue;

  /* Find tx buffer handler */
  if ((NULL_PTR != Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr) &&                                        
      (ETH_FALSE == Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].blTxOngoing))
  {
    LucReturnValue = E_OK;
  }
  else
  {
    LucReturnValue = E_NOT_OK;
  }

  return LucReturnValue;
}

/*******************************************************************************
** Function Name         : Eth_ETNE_FindTxBufferHandler
**
** Service ID            : NA
**
** Description           : This get the tx buffer handler associated with
**                         the specified buffer index.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non-Reentrant
**
** Input Parameters      : LulCtrlIdx - Index of controller
**                         LulBufIdx  - Index of tx buffer
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Pointer of Buffer handle
**
** Preconditions         : None
**
** Global Variable(s)    : Eth_GaaTxBufferMgrTable
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : ETH_DUD_ACT_333
** Reference ID          : ETH_DUD_ACT_333_GBL001
*******************************************************************************/
FUNC(Eth_BufHandlerType *, ETH_PRIVATE_CODE) Eth_ETNE_FindTxBufferHandler(                                              /* PRQA S 1505 # JV-01 */
  CONST(uint32, AUTOMATIC) LulCtrlIdx, CONST(uint32, AUTOMATIC) LulBufIdx)
{
  return Eth_GaaTxBufferMgrTable[LulCtrlIdx][LulBufIdx].pBufferHdr;                                                     
}
#define ETH_STOP_SEC_PRIVATE_CODE
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* (ETH_MACRO_ETNE == STD_ON) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
