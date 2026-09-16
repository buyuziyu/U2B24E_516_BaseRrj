/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mem_59_Renesas_Ram.c                                                                                */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Global variable definitions for Flash Wrapper Component.                                              */
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
 * 1.1.0:  30/06/2025  : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax release
 * 1.0.3:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 *                       As part of ARDAACL-51989, support timeout for Mem Driver
 * 1.0.2:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 1.0.1:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 0.0.2:  31/10/2024  : As part of ARDAACJ-621, support downgrade from version AR23-11 to AR22-11.
 *                       Support commonize
 * 0.0.1:  30/08/2024  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for macro definitions and API prototypes */
#include "Mem_59_Renesas.h"
/* Included for RAM variable declarations */
#include "Mem_59_Renesas_Ram.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define MEM_59_RENESAS_RAM_C_AR_RELEASE_MAJOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION_VALUE
#define MEM_59_RENESAS_RAM_C_AR_RELEASE_MINOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION_VALUE
#define MEM_59_RENESAS_RAM_C_AR_RELEASE_REVISION_VERSION MEM_59_RENESAS_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define MEM_59_RENESAS_RAM_C_SW_MAJOR_VERSION            MEM_59_RENESAS_SW_MAJOR_VERSION_VALUE
#define MEM_59_RENESAS_RAM_C_SW_MINOR_VERSION            MEM_59_RENESAS_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (MEM_59_RENESAS_RAM_AR_RELEASE_MAJOR_VERSION != MEM_59_RENESAS_RAM_C_AR_RELEASE_MAJOR_VERSION)
    #error "Mem_59_Renesas_Ram.c : Mismatch in Release Major Version"
#endif

#if (MEM_59_RENESAS_RAM_AR_RELEASE_MINOR_VERSION != MEM_59_RENESAS_RAM_C_AR_RELEASE_MINOR_VERSION)
    #error "Mem_59_Renesas_Ram.c : Mismatch in Release Minor Version"
#endif

#if (MEM_59_RENESAS_RAM_AR_RELEASE_REVISION_VERSION != MEM_59_RENESAS_RAM_C_AR_RELEASE_REVISION_VERSION)
    #error "Mem_59_Renesas_Ram.c : Mismatch in Release Revision Version"
#endif

#if (MEM_59_RENESAS_RAM_SW_MAJOR_VERSION != MEM_59_RENESAS_RAM_C_SW_MAJOR_VERSION)
    #error "Mem_59_Renesas_Ram.c : Mismatch in Software Major Version"
#endif

#if (MEM_59_RENESAS_RAM_SW_MINOR_VERSION != MEM_59_RENESAS_RAM_C_SW_MINOR_VERSION)
    #error "Mem_59_Renesas_Ram.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_VAR_INIT_8
#include "Mem_59_Renesas_MemMap.h"

/* Global variable to store module intialized status */
uint8 Mem_59_Renesas_GucInitState = MEM_59_RENESAS_UNINITIALIZED;

#define MEM_59_RENESAS_STOP_SEC_VAR_INIT_8
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

#define MEM_59_RENESAS_START_SEC_VAR_NO_INIT_PTR
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/* Global variable to store pointer to Post build Configuration */
const Mem_59_Renesas_ConfigType* Mem_59_Renesas_GpConfigPtr;

/* Global variable to store pointer to instance Configuration */
const Mem_59_Renesas_InstanceType* Mem_59_Renesas_GpInsConfig;

#define MEM_59_RENESAS_STOP_SEC_VAR_NO_INIT_PTR
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

#define MEM_59_RENESAS_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

/* Variable to store the driver state */
volatile Mem_59_Renesas_StatusType Mem_59_Renesas_GenInstanceState[MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG];

/* Variable to store the job result */
volatile Mem_59_Renesas_JobResultType Mem_59_Renesas_GenJobResult[MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG];
/* Structure variable that contains MEM Global variables required for
 * MEM operation.
 */
volatile Mem_59_Renesas_GstVarProperties Mem_59_Renesas_GstVar[MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG];

/* Structure variable to Back Up Global Variables in case of Job Suspend */
volatile Mem_59_Renesas_GstVarProperties Mem_59_Renesas_GstBackUpVar[MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG];

#define MEM_59_RENESAS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

#define MEM_59_RENESAS_START_SEC_VAR_NO_INIT_BOOLEAN
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

#if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED)
/* Variable to store the flash protection state */
volatile boolean Mem_59_Renesas_GblFlashEnable;
#endif /* end of #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED) */

/* Variable to store the Job Suspended request state */
volatile boolean Mem_59_Renesas_GblJobSuspendRequest[MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG];

#define MEM_59_RENESAS_STOP_SEC_VAR_NO_INIT_BOOLEAN
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

#define MEM_59_RENESAS_START_SEC_VAR_NO_INIT_16
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

/* Variable to store the FACI number */
volatile uint16 Mem_59_Renesas_GusFACI;

/* Variable to store the FACI number */
volatile uint16 Mem_59_Renesas_GusBackUpFACI;

#define MEM_59_RENESAS_STOP_SEC_VAR_NO_INIT_16
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

#define MEM_59_RENESAS_START_SEC_VAR_NO_INIT_32
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

/* Variable to store the Time out value to be used for generating Timeout */
volatile uint32 Mem_59_Renesas_GulTimeOutCounter[MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG];

#define MEM_59_RENESAS_STOP_SEC_VAR_NO_INIT_32
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
