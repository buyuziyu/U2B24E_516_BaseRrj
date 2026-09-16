/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = FlsTst_Ram.c                                                                                        */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.4.1:  30/06/2025  : Update SW-VERSION
 * 1.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E 
 * 1.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Relase
 * 1.1.2:  31/10/2024  : Update SW Version to 1.1.2
 * 1.1.1:  30/08/2024    As part of QAC 9.5.0 support, following changes are made:
 *                       1. Add message: 1531
 * 1.1.0:  22/02/2024  : Update SW-VERSION to 1.1.0
 * 1.0.0:  17/03/2023  : Initial Version.
 *
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Flash Test APIs header file */
#include "FlsTst.h"
/* Global RAM variables header file */
#include "FlsTst_Ram.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define FLSTST_RAM_C_AR_RELEASE_MAJOR_VERSION    FLSTST_AR_RELEASE_MAJOR_VERSION_VALUE
#define FLSTST_RAM_C_AR_RELEASE_MINOR_VERSION    FLSTST_AR_RELEASE_MINOR_VERSION_VALUE
#define FLSTST_RAM_C_AR_RELEASE_REVISION_VERSION FLSTST_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define FLSTST_RAM_C_SW_MAJOR_VERSION            FLSTST_SW_MAJOR_VERSION_VALUE
#define FLSTST_RAM_C_SW_MINOR_VERSION            FLSTST_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (FLSTST_RAM_AR_RELEASE_MAJOR_VERSION != FLSTST_RAM_C_AR_RELEASE_MAJOR_VERSION)
  #error "FlsTst_Ram.c : Mismatch in Release Major Version"
#endif

#if (FLSTST_RAM_AR_RELEASE_MINOR_VERSION != FLSTST_RAM_C_AR_RELEASE_MINOR_VERSION)
  #error "FlsTst_Ram.c : Mismatch in Release Minor Version"
#endif

#if (FLSTST_RAM_AR_RELEASE_REVISION_VERSION != FLSTST_RAM_C_AR_RELEASE_REVISION_VERSION)
  #error "FlsTst_Ram.c : Mismatch in Release Revision Version"
#endif

#if (FLSTST_RAM_SW_MAJOR_VERSION != FLSTST_RAM_C_SW_MAJOR_VERSION)
  #error "FlsTst_Ram.c : Mismatch in Software Major Version"
#endif

#if (FLSTST_RAM_SW_MINOR_VERSION != FLSTST_RAM_C_SW_MINOR_VERSION)
  #error "FlsTst_Ram.c : Mismatch in Software Minor Version"
#endif

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1531)    : The object 'name' is referenced in only one translation unit - but not the one in which      */
/*                       it is defined.                                                                               */
/* Rule                : CERTCCM DCL15, CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569               */
/* JV-01 Justification : Followed coding rules, the objects (global variable/const) is define in seperated source     */
/*                       file, so this could be accepted                                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define FLSTST_START_SEC_VAR_NO_INIT_BOOLEAN
#include "FlsTst_MemMap.h"

/* Variable to store the test execution status*/
VAR(boolean, FLSTST_VAR_NO_INIT) FlsTst_GblTestComplete;

#define FLSTST_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "FlsTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

#define FLSTST_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "FlsTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

/* Global variable to store the config pointer */
P2CONST(FlsTst_ConfigType, FLSTST_VAR_NO_INIT, FLSTST_CONFIG_CONST) FlsTst_GpConfigPtr;

/* Pointer variable to load the base address of the Foreground test block configured */
P2CONST(FlsTstBlock_ConfigType, FLSTST_VAR_NO_INIT, FLSTST_CONFIG_CONST) FlsTst_GpFgndBlk;

/* Pointer variable to load the base address of the Background test block configured */
P2CONST(FlsTstBlock_ConfigType, FLSTST_VAR_NO_INIT, FLSTST_CONFIG_CONST) FlsTst_GpBgndBlk;

/* Variable to store the background test result */
#if (FLSTST_TEST_RESULT_SIGNATURE != STD_ON)
VAR(FlsTst_TestResultType, FLSTST_VAR_NO_INIT) FlsTst_GenOverallBgndResult;
#endif

/* Variable to store the foreground test result */
VAR(FlsTst_TestResultFgndType, FLSTST_VAR_NO_INIT) FlsTst_GenLastFgndResult;

/* Variable to store the Ecc test result */
VAR(FlsTst_ErrorDetailsType, FLSTST_VAR_NO_INIT) FlsTst_GddEccErrorDetail;

/* Data Structure required for initializing the FLSTST test Block */
VAR(FlsTst_GVarProperties, FLSTST_VAR_NO_INIT) FlsTst_GVar;

#define FLSTST_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "FlsTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

#define FLSTST_START_SEC_VAR_INIT_UNSPECIFIED
#include "FlsTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

/* Variable holds the status of Initialization */
VAR(FlsTst_StateType, FLSTST_VAR_INIT) FlsTst_GenExeState = FLSTST_UNINIT;

#define FLSTST_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "FlsTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

#define FLSTST_START_SEC_VAR_NO_INIT_32
#include "FlsTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

/* Variable to store the last signature for Foreground test */
VAR(uint32, FLSTST_VAR_NO_INIT) FlsTst_GaaLastFgndSignature[FLSTST_TWO];

/* Variable to store the last signature for Background test */
#if (FLSTST_TEST_RESULT_SIGNATURE == STD_ON)
VAR(uint32, FLSTST_VAR_NO_INIT) FlsTst_GaaLastBgndSignature[FLSTST_TWO];
#endif

/* Variable used to increment test interval when all configured test blocks are tested once. */
VAR(uint32, FLSTST_VAR_NO_INIT) FlsTst_GulTestIntervalId;

#define FLSTST_STOP_SEC_VAR_NO_INIT_32
#include "FlsTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
