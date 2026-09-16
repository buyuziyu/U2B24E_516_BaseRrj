/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22-11 X2x MCAL Components                                                          */
/* Module       = Fee_Ram.c                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Global variable definitions.                                                                                       */
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
 * 1.1.0:  30/06/2025:  Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024:  Update SW-VERSION 1.0.0.
 * 0.0.2:  31/10/2024:  Add QAC Msg 5087
 * 0.0.1:  30/08/2024:  Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Fee APIs header file */
#include "Fee.h"
/* Global RAM variables header file */
#include "Fee_Ram.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define FEE_RAM_C_AR_RELEASE_MAJOR_VERSION                                      FEE_AR_RELEASE_MAJOR_VERSION_VALUE
#define FEE_RAM_C_AR_RELEASE_MINOR_VERSION                                      FEE_AR_RELEASE_MINOR_VERSION_VALUE
#define FEE_RAM_C_AR_RELEASE_REVISION_VERSION                                   FEE_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define FEE_RAM_C_SW_MAJOR_VERSION                                              FEE_SW_MAJOR_VERSION_VALUE
#define FEE_RAM_C_SW_MINOR_VERSION                                              FEE_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (FEE_RAM_AR_RELEASE_MAJOR_VERSION != FEE_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "Fee_Ram.c : Mismatch in Release Major Version"
#endif

#if (FEE_RAM_AR_RELEASE_MINOR_VERSION != FEE_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "Fee_Ram.c : Mismatch in Release Minor Version"
#endif

#if (FEE_RAM_AR_RELEASE_REVISION_VERSION != FEE_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "Fee_Ram.c : Mismatch in Release Revision Version"
#endif

#if (FEE_RAM_SW_MAJOR_VERSION != FEE_RAM_C_SW_MAJOR_VERSION)
  #error "Fee_Ram.c : Mismatch in Software Major Version"
#endif

#if (FEE_RAM_SW_MINOR_VERSION != FEE_RAM_C_SW_MINOR_VERSION)
  #error "Fee_Ram.c : Mismatch in Software Minor Version"
#endif

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : #include directives should only be preceded by preprocessor directives or comments           */
/* Rule                : MISRA C:2012 Rule 20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0612)    : [L] Size of object '%s' exceeds 32767 bytes - program does not conform strictly to ISO:C90.  */
/* Rule                : MISRA-C:2012 Dir 1.1                                                                         */
/* JV-01 Justification : Size of global variable exceeds 32767 due to size of Tx buffer byte of Eth module.           */
/*       Verification  : There is no problem because it is an intended design considering the space-time tradeoff,    */
/*                       that is, scalability.                                                                        */
/**********************************************************************************************************************/
/* Message (2:0686)    : Array has fewer initializers than its declared size. Default initialization is applied to    */
/*                       the remainder of the array elements.                                                         */
/* Rule                : MISRA C:2012 Rule-9.3, CWE Rule CWE-665, CWE-452                                             */
/* JV-01 Justification : This initialization to avoid passing address of uninitialized object. This can be accepted.  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1531)    : The object '%1s' is only referenced in one translation unit - but not the one in which it    */
/*                       is defined.                                                                                  */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7                                                         */
/* JV-01 Justification : This object identifier is following AUTOSAR standard rule (Symbolic Name or Published        */
/*                       Macro's name) so this is accepted                                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

#define FEE_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Fee_MemMap.h"
VAR(boolean, FEE_VAR) Fee_GblWaitMemAccResult;
#define FEE_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define FEE_START_SEC_VAR_NO_INIT_16
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
VAR(uint16, FEE_VAR) Fee_GusCurrAddrAreaId;
VAR(uint16, FEE_VAR) Fee_GusCurrSubAddrAreaId;
VAR(uint16, FEE_VAR) Fee_GusBlockIndex;
#define FEE_STOP_SEC_VAR_NO_INIT_16
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define FEE_START_SEC_VAR_NO_INIT_32
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
VAR(MemAcc_AddressType, FEE_VAR) Fee_GulJobRefAreaAddr;
VAR(MemAcc_AddressType, FEE_VAR) Fee_GulJobDataAddr;
VAR(uint32, FEE_VAR) Fee_GaaDataBuffer[FEE_DATA_BUFFER];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
VAR(MemIf_StatusType, FEE_VAR) Fee_GenModuleState = MEMIF_UNINIT;
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */  

#define FEE_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */    
VAR(Fee_CommandType, FEE_VAR) Fee_GenRequestedCmd;
VAR(Fee_CommandType, FEE_VAR) Fee_enPreviousRequestCmd;
P2CONST(Fee_ConfigType, TYPEDEF, FEE_APPL_CONST) Fee_GpBlockConfig;
VAR(MemIf_JobResultType, FEE_VAR) Fee_GenJobResult;
VAR(Fee_InforJobRequest, FEE_VAR) Fee_GstVar;
VAR(Fee_BlockInfoType, FEE_VAR) Fee_GaaBlockInfo[FEE_MAX_CONFIGURED_BLOCK_NUMBER];
VAR(Fee_AddrAreaInfoType, FEE_VAR) Fee_GaaAddrAreaInfo[FEE_MAX_DEFINED_ADDRESS_AREA_NUMBER];
#define FEE_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Fee_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
