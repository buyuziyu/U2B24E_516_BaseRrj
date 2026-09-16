/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mem_59_Renesas.c                                                                                    */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains API implementations of Mem Driver Component.                                                    */
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
 * 1.1.0:  30/06/2025   : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax release
 *                        Support parameter on/off for Mem_59_Renesas_ReadImmediate API
 *                        Support checking the alignment of write burst size for the program
 * 1.0.3:  25/04/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 *                        As part of ARDAACL-51989, support timeout for Mem Driver
 * 1.0.2:  31/03/2025   : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 1.0.1:  28/02/2025   : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 0.0.2:  31/10/2024   : As part of ARDAACJ-621, support downgrade from version AR23-11 to AR22-11.
 *                        Change name from Mem_AddressType to Mem_59_Renesas_AddressType
 *                        Support commonize
 * 0.0.1:  30/08/2024   : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Mem_59_Renesas_Types.h"
/* Included prototypes for internal functions of Flash Wrapper Component */
#include "Mem_59_Renesas_FPSYS_Control.h"
/* Included for RAM variable declarations */
#include "Mem_59_Renesas_Ram.h"
/* Included prototypes for FCU functions of Flash Wrapper Component */
#include "Mem_59_Renesas_FPSYS_LLDriver.h"
/* Included for the declaration of Det_ReportError() */
#if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MEM_59_RENESAS_C_AR_RELEASE_MAJOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION_VALUE
#define MEM_59_RENESAS_C_AR_RELEASE_MINOR_VERSION    MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION_VALUE
#define MEM_59_RENESAS_C_AR_RELEASE_REVISION_VERSION MEM_59_RENESAS_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define MEM_59_RENESAS_C_SW_MAJOR_VERSION            MEM_59_RENESAS_SW_MAJOR_VERSION_VALUE
#define MEM_59_RENESAS_C_SW_MINOR_VERSION            MEM_59_RENESAS_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION != MEM_59_RENESAS_C_AR_RELEASE_MAJOR_VERSION)
  #error "Mem_59_Renesas.c : Mismatch in Release Major Version"
#endif

#if (MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION != MEM_59_RENESAS_C_AR_RELEASE_MINOR_VERSION)
  #error "Mem_59_Renesas.c : Mismatch in Release Minor Version"
#endif

#if (MEM_59_RENESAS_AR_RELEASE_REVISION_VERSION != MEM_59_RENESAS_C_AR_RELEASE_REVISION_VERSION)
  #error "Mem_59_Renesas.c : Mismatch in Release Revision Version"
#endif

#if (MEM_59_RENESAS_SW_MAJOR_VERSION != MEM_59_RENESAS_C_SW_MAJOR_VERSION)
  #error "Mem_59_Renesas.c : Mismatch in Software Major Version"
#endif

#if (MEM_59_RENESAS_SW_MINOR_VERSION != MEM_59_RENESAS_C_SW_MINOR_VERSION)
  #error "Mem_59_Renesas.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : MISRA C:2012 Rule-8.7, CERTCCM DCL19, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : MISRA C:2012 Rule-15.7, CERTCCM MSC01, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else" statement with empty content is removed to improve readability.                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : MISRA C:2012 Dir-4.1, CERTCCM MSC07, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used following AUTOSAR standard rule. It is accepted.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3673)    : The object addressed by the pointer parameter '%s' is not modified and so the pointer could  */
/*                       be of type 'pointer to const'.                                                               */
/* Rule                : MISRA C:2012 Rule-8.13, CERTCCM DCL00, DCL13, CWE Rule CWE-398, CWE-569                      */
/* JV-01 Justification : Pointer variable is used to modify the value at the address so the pointer cannot be         */
/*                       declared as 'pointer to const' type.                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_Init
**
** Service ID                : 0x01
**
** Description               : This API performs the initialization of the MEM
**                             Driver Component.
**
** Sync/Async                : Synchronous
**
** Reentrancy                : Non Re-entrant
**
** Input Parameters          : configPtr
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : None
**
** Preconditions             : None
**
** Global Variables Used     : Mem_59_Renesas_GenInstanceState, Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GpConfigPtr, 
**                             Mem_59_Renesas_GenJobResult, Mem_59_Renesas_GstVar, Mem_59_Renesas_GblJobSuspendRequest,
**                             Mem_59_Renesas_GucInitState, Mem_59_Renesas_GstConfiguration
**                             Mem_59_Renesas_GulTimeOutCounter
**
** Function(s) invoked       : Det_ReportError, Mem_59_Renesas_ClearBackUpData
**                             pHWResourceInit
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_001, MEM_DUD_ACT_001_GBL001, MEM_DUD_ACT_001_GBL002
** Reference ID              : MEM_DUD_ACT_001_GBL003, MEM_DUD_ACT_001_GBL004, MEM_DUD_ACT_001_GBL005
** Reference ID              : MEM_DUD_ACT_001_GBL006, MEM_DUD_ACT_001_GBL007,
** Reference ID              : MEM_DUD_ACT_001_GBL009, MEM_DUD_ACT_001_GBL010, MEM_DUD_ACT_001_GBL011
** Reference ID              : MEM_DUD_ACT_001_GBL012, MEM_DUD_ACT_001_ERR001, MEM_DUD_ACT_001_ERR002
** Reference ID              : MEM_DUD_ACT_001_GBL008, MEM_DUD_ACT_001_GBL013, MEM_DUD_ACT_001_GBL014
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"
FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_Init(P2CONST(Mem_59_Renesas_ConfigType, AUTOMATIC, MEM_APPL_CONST) configPtr)/* PRQA S 1503 # JV-01 */
{
  /* Local variable to hold the hardware resource init result */
  Std_ReturnType LucHwInitResult;
  /* Local variable to hold the loop counter */
  Mem_59_Renesas_InstanceIdType LulLoop;

  /* Initialize local variables */
  LucHwInitResult = E_OK;

  /* Check if the Configuration pointer is not NULL pointer */
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (MEM_59_RENESAS_INITIALIZED == Mem_59_Renesas_GucInitState)
  {
    /* Report Error to Det */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_INIT_SID, 
                                                                                  MEM_59_RENESAS_E_ALREADY_INITIALIZED);
  }
  else if (NULL_PTR != configPtr)
  {
    /* Report Error to Det */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_INIT_SID, 
                                                                                        MEM_59_RENESAS_E_PARAM_POINTER);
  }
  else
  #else
   /* Set configPtr as unused */
  (void)configPtr;
  #endif
  {
    /* Get global configuration pointer */
    Mem_59_Renesas_GpConfigPtr = &Mem_59_Renesas_GstConfiguration[MEM_59_RENESAS_ZERO];
    /* Get Mem instance pointer */
    Mem_59_Renesas_GpInsConfig = Mem_59_Renesas_GpConfigPtr->pInstanceConfig;

    /* Initialize hardware resource of each instance */
    for (LulLoop = (Mem_59_Renesas_InstanceIdType)MEM_59_RENESAS_ZERO; \
                             (LulLoop < (Mem_59_Renesas_InstanceIdType)MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG); LulLoop++)/* PRQA S 2877 # JV-01 */
    {
      LucHwInitResult |= Mem_59_Renesas_GpInsConfig[LulLoop].pHWIPFunc->pHWResourceInit(LulLoop);
    }

    /* Intialize common variable */
    if (E_OK == LucHwInitResult)
    {
      for (LulLoop = (Mem_59_Renesas_InstanceIdType)MEM_59_RENESAS_ZERO; \
                             (LulLoop < (Mem_59_Renesas_InstanceIdType)MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG); LulLoop++)/* PRQA S 2877 # JV-01 */
      {
        Mem_59_Renesas_ClearBackUpData(LulLoop);
        /* Initialize the global variable for counter */
        Mem_59_Renesas_GulTimeOutCounter[LulLoop] = (uint32)MEM_59_RENESAS_ZERO;
        Mem_59_Renesas_GblJobSuspendRequest[LulLoop] = MEM_59_RENESAS_FALSE;
        /* Initialize the global variables related buffer address */
        Mem_59_Renesas_GstVar[LulLoop].pBufferAddress = NULL_PTR;
        /* Initialize the global variables related address */
        Mem_59_Renesas_GstVar[LulLoop].ulSrcDestAddress = (uint32)MEM_59_RENESAS_ZERO;
        Mem_59_Renesas_GstVar[LulLoop].ulReadAddress = (uint32)MEM_59_RENESAS_ZERO;
        Mem_59_Renesas_GstVar[LulLoop].ulJobStartAddress = (uint32)MEM_59_RENESAS_ZERO;
        Mem_59_Renesas_GstVar[LulLoop].ulJobEndAddress = (uint32)MEM_59_RENESAS_ZERO;
        /* Initialize the global variables requested length to zero. */
        Mem_59_Renesas_GstVar[LulLoop].ulRequestedLength = (uint32)MEM_59_RENESAS_ZERO;
        /* Initialize the global variable general command to None */
        Mem_59_Renesas_GstVar[LulLoop].enGenCommand = MEM_59_RENESAS_COMMAND_NONE;
        /* Initialize job result of each instance */
        Mem_59_Renesas_GenJobResult[LulLoop] = MEM_59_RENESAS_JOB_OK;
        /* Set the instance status to idle */
        Mem_59_Renesas_GenInstanceState[LulLoop] = MEM_59_RENESAS_IDLE;
      }

      /* Set module init state to INITIALIZED */
      Mem_59_Renesas_GucInitState = MEM_59_RENESAS_INITIALIZED;
    }
  } /* else No action required */
} /* End of API Mem_59_Renesas_Init */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/**********************************************************************************************************************
** Function Name             : Mem_59_Renesas_Erase
**
** Service ID                : 0x07
**
** Description               : This API will erase the one or more complete
**                             flash sectors.
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Re-entrant
**
** Input Parameters          : instanceId, targetAddress, length
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : Std_ReturnType
**                             E_OK: If Erase command has been accepted.
**                             E_NOT_OK: If Erase command has not been accepted.
**
** Preconditions             : Component must be initialized using Mem_59_Renesas_Init().
**
** Global Variables Used     : Mem_59_Renesas_GenInstanceState, Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GstVar,
**                             Mem_59_Renesas_GblJobSuspendRequest, Mem_59_Renesas_GenJobResult,
**                             Mem_59_Renesas_GucInitState
**
** Function(s) invoked       : Det_ReportError, Mem_59_Renesas_FPSYS_SuspendPreCheck
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_007, MEM_DUD_ACT_007_GBL001, MEM_DUD_ACT_007_GBL002, MEM_DUD_ACT_007_GBL003
** Reference ID              : MEM_DUD_ACT_007_GBL004, MEM_DUD_ACT_007_GBL005, MEM_DUD_ACT_007_GBL006, 
** Reference ID              : MEM_DUD_ACT_007_GBL007, MEM_DUD_ACT_007_GBL008, MEM_DUD_ACT_007_GBL009,
** Reference ID              : MEM_DUD_ACT_007_GBL010, MEM_DUD_ACT_007_GBL011, MEM_DUD_ACT_007_GBL012,
** Reference ID              : MEM_DUD_ACT_007_ERR001, MEM_DUD_ACT_007_ERR003, MEM_DUD_ACT_007_ERR004,
** Reference ID              : MEM_DUD_ACT_007_ERR005, MEM_DUD_ACT_007_ERR006, MEM_DUD_ACT_007_ERR007
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MEM_PUBLIC_CODE) Mem_59_Renesas_Erase(Mem_59_Renesas_InstanceIdType instanceId,                    /* PRQA S 1503 # JV-01 */
                                            Mem_59_Renesas_AddressType targetAddress, Mem_59_Renesas_LengthType length)
{
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to check if address is valid */
  boolean LblAddrValid;
  #endif
  /* Local variable to hold the DET return value */
  Std_ReturnType LucReturnValue;
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold align check value */
  uint32 LulCheckAlign;
  #endif
  /* Local variable to hold loop count */
  uint32 LulLoop;
  /* Local variable to hold end address */
  uint32 LulEndAddr;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  
  /* Initialize return value */
  LucReturnValue = E_OK;
  /* Calculate end address */
  LulEndAddr = (targetAddress + length) - (uint32)MEM_59_RENESAS_ONE;                                                   /* PRQA S 3383, 3384 # JV-01, JV-01 */

  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (MEM_59_RENESAS_INITIALIZED != Mem_59_Renesas_GucInitState)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_ERASE_SID, 
                                                                                               MEM_59_RENESAS_E_UNINIT);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if instanceId is valid */
  else if (MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG <= instanceId)
  {
    /* Report error to DET */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_ERASE_SID, 
                                                                                    MEM_59_RENESAS_E_PARAM_INSTANCE_ID);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if the driver is busy by servicing another request */
  else if (MEM_59_RENESAS_BUSY == Mem_59_Renesas_GenInstanceState[instanceId])                                          /* PRQA S 2004 # JV-01 */
  {
    /* Report to DET if the driver is currently busy */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_ERASE_SID,
                                                                                          MEM_59_RENESAS_E_JOB_PENDING);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }

  /* Check whether any error is reported to DET */
  if (E_OK == LucReturnValue)
  #endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    LblAddrValid = MEM_59_RENESAS_FALSE;
    #endif
    LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[instanceId].pSectorBatch);
    
    for (LulLoop = (uint32)MEM_59_RENESAS_ZERO;
      (LulLoop < Mem_59_Renesas_GpInsConfig[instanceId].ulTotalSectorBatch); LulLoop++)
    {
      if ((LpSectorBatch[LulLoop].ulSectorStartAddr <= targetAddress) &&
          (LpSectorBatch[LulLoop].ulSectorEndAddr >= targetAddress))
      {
        /* Store index of sector batch */
        Mem_59_Renesas_GstVar[instanceId].ulSectorBatchIdx = LulLoop;
        
        #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
        LulCheckAlign = LpSectorBatch[LulLoop].ulEraseSectorSize - (uint32)MEM_59_RENESAS_ONE;                          /* PRQA S 3383 # JV-01 */
        
        /* Check if targetAddress aligned to page size */
        if (MEM_59_RENESAS_ZERO == (targetAddress & LulCheckAlign))
        {
          LblAddrValid = MEM_59_RENESAS_TRUE;
        }
        
        /* Check length */
        if ((MEM_59_RENESAS_ZERO == length) ||
            (LulEndAddr > LpSectorBatch[LulLoop].ulSectorEndAddr) ||
            (MEM_59_RENESAS_ZERO != ((targetAddress + length) & LulCheckAlign)) ||                                      /* PRQA S 3383 # JV-01 */
            (length > LpSectorBatch[LulLoop].ulEraseBurstSize))
        {
          /* Report error to DET */
          (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_ERASE_SID,
                                                                                         MEM_59_RENESAS_E_PARAM_LENGTH);
          /* Reset return value to E_NOT_OK due to failure */
          LucReturnValue = E_NOT_OK;
        }
        #endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */

        break;
      }
    }

    #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    /* Check sourceAddress */
    if (MEM_59_RENESAS_FALSE == LblAddrValid)
    {
      /* Report error to DET */
      (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_ERASE_SID, 
                                                                                        MEM_59_RENESAS_E_PARAM_ADDRESS);
      /* Reset return value to E_NOT_OK due to failure */
      LucReturnValue = E_NOT_OK;
    }
    #endif
  }

  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Check whether any error is reported to DET */
  if (E_OK == LucReturnValue)
  #endif
  {
    #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) && (MEM_59_RENESAS_HW_IP == MEM_59_RENESAS_HW_IP_FPSYS)
    /* Check if request overlap area */
    if (MEM_59_RENESAS_TRUE == Mem_59_Renesas_GblJobSuspendRequest[instanceId])
    {
      LucReturnValue = Mem_59_Renesas_FPSYS_SuspendPreCheck(instanceId, targetAddress, LulEndAddr, 
                                                                                          MEM_59_RENESAS_COMMAND_ERASE);
    }

    if (E_NOT_OK == LucReturnValue)
    {
      /* Report error to DET */
      (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_ERASE_SID,
                                                                                        MEM_59_RENESAS_E_PARAM_ADDRESS);
    }
    else
    #endif
    {
      /* Set the instance state to busy to accept this read request */
      Mem_59_Renesas_GenInstanceState[instanceId] = MEM_59_RENESAS_BUSY;
      /* Set the job result to Job pending */
      Mem_59_Renesas_GenJobResult[instanceId] = MEM_59_RENESAS_JOB_PENDING;
      /* Get the write start and end address */
      Mem_59_Renesas_GstVar[instanceId].ulJobStartAddress = targetAddress;
      Mem_59_Renesas_GstVar[instanceId].ulJobEndAddress = LulEndAddr;
      /* Set the global variable with length */
      Mem_59_Renesas_GstVar[instanceId].ulRequestedLength = length;
      /* Set RFD requested flag to FALSE */
      Mem_59_Renesas_GstVar[instanceId].blHwRequestedFlg = MEM_59_RENESAS_FALSE;
      /* Set the type of Flash */
      Mem_59_Renesas_GstVar[instanceId].enFlashType =
                                          LpSectorBatch[Mem_59_Renesas_GstVar[instanceId].ulSectorBatchIdx].enFlashType;
      /* Set the command as Write command */
      Mem_59_Renesas_GstVar[instanceId].enGenCommand = MEM_59_RENESAS_COMMAND_ERASE;
    }
  }

  return (LucReturnValue);
} /* End of API Mem_59_Renesas_Erase */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name             : Mem_59_Renesas_Write
**
** Service ID                : 0x06
**
** Description               : This API performs programming of one or more complete flash pages of the flash device. 
**                             The data from input buffer (source address) is written to the flash pointed by 
**                             the target offset.The target address must be aligned to flash page boundary.
**
** Sync/Async                : Asynchronous
**
** Reentrancy                : Non Re-entrant
**
** Input Parameters          : instanceId, targetAddress, sourceDataPtr, length
**
** InOut Parameters          : None
**
** Output Parameters         : None
**
** Return parameter          : Std_ReturnType
**                             E_OK: if Write command has been accepted.
**                             E_NOT_OK: if Write command has not been accepted.
**
** Preconditions             : Component must be initialized using Mem_59_Renesas_Init().
**
** Global Variables Used     : Mem_59_Renesas_GenInstanceState, Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GstVar, 
**                             Mem_59_Renesas_GblJobSuspendRequest, Mem_59_Renesas_GenJobResult
**
** Function(s) invoked       : Det_ReportError, Mem_59_Renesas_FPSYS_SuspendPreCheck, 
**
** Registers Used            : None
**
** Reference ID              : MEM_DUD_ACT_006, MEM_DUD_ACT_006_GBL001, MEM_DUD_ACT_006_GBL002, MEM_DUD_ACT_006_GBL003
** Reference ID              : MEM_DUD_ACT_006_GBL004, MEM_DUD_ACT_006_GBL005, MEM_DUD_ACT_006_GBL006,
** Reference ID              : MEM_DUD_ACT_006_GBL008, MEM_DUD_ACT_006_GBL009, MEM_DUD_ACT_006_GBL010, 
** Reference ID              : MEM_DUD_ACT_006_ERR001, MEM_DUD_ACT_006_ERR002, MEM_DUD_ACT_006_ERR003, 
** Reference ID              : MEM_DUD_ACT_006_ERR005, MEM_DUD_ACT_006_ERR006, MEM_DUD_ACT_006_ERR004
** Reference ID              : MEM_DUD_ACT_006_GBL012, MEM_DUD_ACT_006_ERR007, MEM_DUD_ACT_006_GBL007,
** Reference ID              : MEM_DUD_ACT_006_GBL011, MEM_DUD_ACT_006_GBL013
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MEM_PUBLIC_CODE) Mem_59_Renesas_Write(Mem_59_Renesas_InstanceIdType instanceId,                    /* PRQA S 1503 # JV-01 */
Mem_59_Renesas_AddressType targetAddress, P2CONST(Mem_59_Renesas_DataType, AUTOMATIC, MEM_APPL_CONST) sourceDataPtr, 
Mem_59_Renesas_LengthType length)
{
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to check if address is valid */
  boolean LblAddrValid;
  #endif
  /* Local variable to hold the DET return value */
  Std_ReturnType LucReturnValue;
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold align check value */
  uint32 LulCheckAlign;
  #endif
  /* Local variable to hold loop count */
  uint32 LulLoop;
  /* Local variable to hold end address */
  uint32 LulEndAddr;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  
  /* Initialize return value */
  LucReturnValue = E_OK;
  /* Calculate end address */
  LulEndAddr = (targetAddress + length) - (uint32)MEM_59_RENESAS_ONE;                                                   /* PRQA S 3383, 3384 # JV-01, JV-01 */

  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (MEM_59_RENESAS_INITIALIZED != Mem_59_Renesas_GucInitState)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_WRITE_SID, 
                                                                                               MEM_59_RENESAS_E_UNINIT);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if instanceId is valid */
  else if (MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG <= instanceId)
  {
    /* Report error to DET */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_WRITE_SID, 
                                                                                    MEM_59_RENESAS_E_PARAM_INSTANCE_ID);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if the driver is busy by servicing another request */
  else if (MEM_59_RENESAS_BUSY == Mem_59_Renesas_GenInstanceState[instanceId])
  {
    /* Report to DET if the driver is currently busy */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_WRITE_SID, 
                                                                                          MEM_59_RENESAS_E_JOB_PENDING);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if sourceDataPtr is NULL_PTR */
  else if (NULL_PTR == sourceDataPtr)                                                                                   /* PRQA S 2004 # JV-01 */
  {
    /* Report error to DET */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_WRITE_SID, 
                                                                                        MEM_59_RENESAS_E_PARAM_POINTER);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }

  /* Check whether any error is reported to DET */
  if (E_OK == LucReturnValue)
  #endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    LblAddrValid = MEM_59_RENESAS_FALSE;
    #endif
    LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[instanceId].pSectorBatch);
    
    for (LulLoop = (uint32)MEM_59_RENESAS_ZERO;
      (LulLoop < Mem_59_Renesas_GpInsConfig[instanceId].ulTotalSectorBatch); LulLoop++)
    {
      if ((LpSectorBatch[LulLoop].ulSectorStartAddr <= targetAddress) &&
          (LpSectorBatch[LulLoop].ulSectorEndAddr >= targetAddress))
      {
        /* Store index of sector batch */
        Mem_59_Renesas_GstVar[instanceId].ulSectorBatchIdx = LulLoop;
        
        #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)

        /* Type access request which only page size or burst size */
        if ((MEM_59_RENESAS_ZERO != length) &&
              (LpSectorBatch[LulLoop].ulWritePageSize == length) &&
                (LulEndAddr <= LpSectorBatch[LulLoop].ulSectorEndAddr))
        {
          LulCheckAlign = LpSectorBatch[LulLoop].ulWritePageSize - (uint32)MEM_59_RENESAS_ONE;                          /* PRQA S 3383 # JV-01 */

          /* Check if targetAddress aligned to page size */
          if (MEM_59_RENESAS_ZERO == (targetAddress & LulCheckAlign))
          {
            LblAddrValid = MEM_59_RENESAS_TRUE;
          }
        }
        else if ((MEM_59_RENESAS_ZERO != length) &&
              (LpSectorBatch[LulLoop].ulWriteBurstSize == length) &&
                (LulEndAddr <= LpSectorBatch[LulLoop].ulSectorEndAddr))
        {
          LulCheckAlign = LpSectorBatch[LulLoop].ulWriteBurstSize - (uint32)MEM_59_RENESAS_ONE;                         /* PRQA S 3383 # JV-01 */

          /* Check if targetAddress aligned to page size */
          if (MEM_59_RENESAS_ZERO == (targetAddress & LulCheckAlign))
          {
            LblAddrValid = MEM_59_RENESAS_TRUE;
          }
        }
        else
        {
          /* Report error to DET */
          (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_WRITE_SID, 
                                                                                         MEM_59_RENESAS_E_PARAM_LENGTH);
          /* Reset return value to E_NOT_OK due to failure */
          LucReturnValue = E_NOT_OK;
        }
        #endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
        break;
      }
    }

    #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    /* Check sourceAddress */
    if ((MEM_59_RENESAS_FALSE == LblAddrValid) && (E_OK == LucReturnValue))
    {
      /* Report error to DET */
      (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_WRITE_SID, 
                                                                                        MEM_59_RENESAS_E_PARAM_ADDRESS);
      /* Reset return value to E_NOT_OK due to failure */
      LucReturnValue = E_NOT_OK;
    }
    #endif
  }

  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Check whether any error is reported to DET */
  if (E_OK == LucReturnValue)
  #endif
  {
    #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) && (MEM_59_RENESAS_HW_IP == MEM_59_RENESAS_HW_IP_FPSYS)
    /* Check if request overlap area */
    if (MEM_59_RENESAS_TRUE == Mem_59_Renesas_GblJobSuspendRequest[instanceId])
    {
      LucReturnValue = Mem_59_Renesas_FPSYS_SuspendPreCheck(instanceId, targetAddress, LulEndAddr, 
                                                                                          MEM_59_RENESAS_COMMAND_WRITE);
    }
    if (E_NOT_OK == LucReturnValue)
    {
      /* Report error to DET */
      (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_WRITE_SID, 
                                                                                        MEM_59_RENESAS_E_PARAM_ADDRESS);
    }
    else
    #endif
    {
      /* Set the instance state to busy to accept this read request */
      Mem_59_Renesas_GenInstanceState[instanceId] = MEM_59_RENESAS_BUSY;
      /* Set the job result to Job pending */
      Mem_59_Renesas_GenJobResult[instanceId] = MEM_59_RENESAS_JOB_PENDING;
      /* Get the write start and end address */
      Mem_59_Renesas_GstVar[instanceId].ulJobStartAddress = targetAddress;
      Mem_59_Renesas_GstVar[instanceId].ulJobEndAddress = LulEndAddr;
      /* Set the global variable with length */
      Mem_59_Renesas_GstVar[instanceId].ulRequestedLength = length;
      /* Set the global variable with application buffer pointer */
      Mem_59_Renesas_GstVar[instanceId].pBufferAddress = sourceDataPtr;
      /* Set RFD requested flag to FALSE */
      Mem_59_Renesas_GstVar[instanceId].blHwRequestedFlg = MEM_59_RENESAS_FALSE;
      /* Set the type of Flash */
      Mem_59_Renesas_GstVar[instanceId].enFlashType =
                                          LpSectorBatch[Mem_59_Renesas_GstVar[instanceId].ulSectorBatchIdx].enFlashType;
      /* Set the command as Write command */
      Mem_59_Renesas_GstVar[instanceId].enGenCommand = MEM_59_RENESAS_COMMAND_WRITE;
    }
  }

  return (LucReturnValue);
} /* End of API Mem_59_Renesas_Write */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_GetJobResult
**
** Service ID               : 0x04
**
** Description              : Service to return results of the most recent job.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Non Reentrant
**
** Input Parameters         : instanceId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : Mem_59_Renesas_JobResultType
**
** Preconditions            : Component must be initialized using Mem_59_Renesas_Init().
**
** Global Variables Used    : Mem_59_Renesas_GenJobResult, Mem_59_Renesas_GucInitState
**
** Function(s) invoked      : Det_ReportError
**
** Reference ID             : MEM_DUD_ACT_004, MEM_DUD_ACT_004_GBL001, MEM_DUD_ACT_004_GBL002
** Reference ID             : MEM_DUD_ACT_004_ERR001, MEM_DUD_ACT_004_ERR002
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Mem_59_Renesas_JobResultType, MEM_PUBLIC_CODE) Mem_59_Renesas_GetJobResult(                                        /* PRQA S 1503 # JV-01 */
                                                                          Mem_59_Renesas_InstanceIdType instanceId)     
{
  /* Local variable to hold the job result */
  Mem_59_Renesas_JobResultType LenJobResult;

  /* Set local variable with the default value */
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  LenJobResult = MEM_59_RENESAS_JOB_FAILED;
  #endif

  /* Check if the module is initialized */
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (MEM_59_RENESAS_INITIALIZED != Mem_59_Renesas_GucInitState)
  {
    /* Report error to DET that module is not initialized */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_GET_JOB_RESULT_SID,
                                                                                               MEM_59_RENESAS_E_UNINIT);
  }
  else if (MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG <= instanceId)
  {
    /* Report error to DET that instanceId is invalid */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_GET_JOB_RESULT_SID,
                                                                                    MEM_59_RENESAS_E_PARAM_INSTANCE_ID);
  }
  else
  #endif
  {
    /* Read the job status */
    LenJobResult = Mem_59_Renesas_GenJobResult[instanceId];
  } /* else No action required */
  /* Return the job result */
  return (LenJobResult);
} /* End of API Mem_59_Renesas_GetJobResult */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_MainFunction
**
** Service ID               : 0x03
**
** Description              : This API performs the job processing of erase,
**                            write, read and compare jobs. This API is called
**                            cyclically until the job is processed completely.
**
** Sync/Async               : NA
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : Component must be initialized using Mem_59_Renesas_Init().
**
** Global Variables Used    : Mem_59_Renesas_GenInstanceState, Mem_59_Renesas_GucInitState
**
** Function(s) invoked      : pProcessJob
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_003, MEM_DUD_ACT_003_GBL001, MEM_DUD_ACT_003_GBL002
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_MainFunction(void)                                                           /* PRQA S 1503 # JV-01 */
{
  Mem_59_Renesas_InstanceIdType LulInstanceId;

  if (MEM_59_RENESAS_INITIALIZED == Mem_59_Renesas_GucInitState)
  {
    for (LulInstanceId = (Mem_59_Renesas_InstanceIdType)MEM_59_RENESAS_ZERO;
      (LulInstanceId < (Mem_59_Renesas_InstanceIdType)MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG); LulInstanceId++)           /* PRQA S 2877 # JV-01 */
    {
      /* Check if any job is being processed */
      if (MEM_59_RENESAS_BUSY == Mem_59_Renesas_GenInstanceState[LulInstanceId])
      {
        /* Process request job */
        Mem_59_Renesas_GpInsConfig[LulInstanceId].pHWIPFunc->pProcessJob(LulInstanceId);
      } /* else No action required */
    }
  } /* End of if (MEM_59_RENESAS_INITIALIZED == Mem_59_Renesas_GucInitState) */
} /* End of API Mem_59_Renesas_MainFunction */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_Read
**
** Service ID               : 0x05
**
** Description              : This API performs the reading of the flash memory
**                            The data from flash memory (source address) is
**                            read to the data buffer (Target address) of the
**                            application.
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : instanceId, sourceAddress, length
**
** InOut Parameters         : None
**
** Output Parameters        : destinationDataPtr
**
** Return parameter         : Std_ReturnType
**                            E_OK: if Read command has been accepted.
**                            E_NOT_OK: if Read command has not been accepted.
**
** Preconditions            : Component must be initialized using Mem_59_Renesas_Init().
**
** Global Variables Used    : Mem_59_Renesas_GucInitState, Mem_59_Renesas_GenInstanceState, Mem_59_Renesas_GpInsConfig,
**                            Mem_59_Renesas_GstVar, Mem_59_Renesas_GenJobResult
**
** Function(s) invoked      : Det_ReportError
**
** Reference ID             : MEM_DUD_ACT_005, MEM_DUD_ACT_005_GBL001, MEM_DUD_ACT_005_GBL002, MEM_DUD_ACT_005_GBL003
** Reference ID             : MEM_DUD_ACT_005_GBL004, MEM_DUD_ACT_005_GBL005, MEM_DUD_ACT_005_GBL006,
** Reference ID             : MEM_DUD_ACT_005_GBL008, MEM_DUD_ACT_005_GBL009, MEM_DUD_ACT_005_GBL010
** Reference ID             : MEM_DUD_ACT_005_ERR001, MEM_DUD_ACT_005_ERR002, MEM_DUD_ACT_005_ERR003,
** Reference ID             : MEM_DUD_ACT_005_ERR005, MEM_DUD_ACT_005_ERR006, MEM_DUD_ACT_005_GBL007,
** Reference ID             : MEM_DUD_ACT_005_ERR004, MEM_DUD_ACT_005_GBL011
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MEM_PUBLIC_CODE) Mem_59_Renesas_Read(Mem_59_Renesas_InstanceIdType instanceId,                     /* PRQA S 1503 # JV-01 */
Mem_59_Renesas_AddressType sourceAddress, P2VAR(Mem_59_Renesas_DataType, AUTOMATIC, MEM_APPL_DATA) destinationDataPtr,  /* PRQA S 3432, 3673 # JV-01, JV-01 */
Mem_59_Renesas_LengthType length)
{
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to check if address is valid */
  boolean LblAddrValid;
  #endif
  /* Local variable to hold the DET return value */
  Std_ReturnType LucReturnValue;
  /* Local variable to hold align check value */
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  uint32 LulCheckAlign;
  #endif
  /* Local variable to hold loop count */
  uint32 LulLoop;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  
  /* Initialize return value */
  LucReturnValue = E_OK;
  
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (MEM_59_RENESAS_INITIALIZED != Mem_59_Renesas_GucInitState)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_READ_SID, 
                                                                                               MEM_59_RENESAS_E_UNINIT);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if instanceId is valid */
  else if (MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG <= instanceId)
  {
    /* Report error to DET */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_READ_SID, 
                                                                                    MEM_59_RENESAS_E_PARAM_INSTANCE_ID);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if the driver is busy by servicing another request */
  else if (MEM_59_RENESAS_BUSY == Mem_59_Renesas_GenInstanceState[instanceId])
  {
    /* Report to DET if the driver is currently busy */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_READ_SID, 
                                                                                          MEM_59_RENESAS_E_JOB_PENDING);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if destinationDataPtr is NULL_PTR */
  else if (NULL_PTR == destinationDataPtr)                                                                              /* PRQA S 2004 # JV-01 */
  {
    /* Report error to DET */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_READ_SID,
                                                                                        MEM_59_RENESAS_E_PARAM_POINTER);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }

  /* Check whether any error is reported to DET */
  if (E_OK == LucReturnValue)
  #endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    LblAddrValid = MEM_59_RENESAS_FALSE;
    #endif
    LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[instanceId].pSectorBatch);

    for (LulLoop = (uint32)MEM_59_RENESAS_ZERO;
      #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
      (MEM_59_RENESAS_FALSE == LblAddrValid) &&
      #endif
      (LulLoop < Mem_59_Renesas_GpInsConfig[instanceId].ulTotalSectorBatch); LulLoop++)
    {
      if ((LpSectorBatch[LulLoop].ulSectorStartAddr <= sourceAddress) &&
          (LpSectorBatch[LulLoop].ulSectorEndAddr >= sourceAddress))
      {
        /* Store index of sector batch */
        Mem_59_Renesas_GstVar[instanceId].ulSectorBatchIdx = LulLoop;

        #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
        LulCheckAlign = LpSectorBatch[LulLoop].ulReadPageSize - (uint32)MEM_59_RENESAS_ONE;                             /* PRQA S 3383 # JV-01 */

        /* Check if sourceAddress aligned to page size */
        if (MEM_59_RENESAS_ZERO == (sourceAddress & LulCheckAlign))
        {
          LblAddrValid = MEM_59_RENESAS_TRUE;
        }
        
        /* Check length */
        if ((MEM_59_RENESAS_ZERO == length) ||
            ((sourceAddress + length - (uint32)MEM_59_RENESAS_ONE) > LpSectorBatch[LulLoop].ulSectorEndAddr) ||         /* PRQA S 3383, 3384 # JV-01, JV-01 */
            (MEM_59_RENESAS_ZERO != ((sourceAddress + length) & LulCheckAlign)) ||                                      /* PRQA S 3383 # JV-01 */
            (length > LpSectorBatch[LulLoop].ulReadBurstSize))
        {
          /* Report error to DET */
          (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_READ_SID, 
                                                                                         MEM_59_RENESAS_E_PARAM_LENGTH);
          /* Reset return value to E_NOT_OK due to failure */
          LucReturnValue = E_NOT_OK;
        }
        #endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
      }
    }

    #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    /* Check sourceAddress */
    if (MEM_59_RENESAS_FALSE == LblAddrValid)
    {
      /* Report error to DET */
      (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_READ_SID, 
                                                                                        MEM_59_RENESAS_E_PARAM_ADDRESS);
      /* Reset return value to E_NOT_OK due to failure */
      LucReturnValue = E_NOT_OK;
    }
    #endif
  }

  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Check whether any error is reported to DET */
  if (E_OK == LucReturnValue)
  #endif
  {
    /* Set the instance state to busy to accept this read request */
    Mem_59_Renesas_GenInstanceState[instanceId] = MEM_59_RENESAS_BUSY;
    /* Global variable to hold the read start address */
    Mem_59_Renesas_GstVar[instanceId].ulReadAddress = sourceAddress;
    /* Set the global variable with length of bytes to be processed */
    Mem_59_Renesas_GstVar[instanceId].ulRequestedLength = length;
    /* Initialize the global variable with target address and length */
    Mem_59_Renesas_GstVar[instanceId].pBufferAddress = destinationDataPtr;
    /* set the job result as pending */
    Mem_59_Renesas_GenJobResult[instanceId] = MEM_59_RENESAS_JOB_PENDING;
    /* Set the command for Read operation */
    Mem_59_Renesas_GstVar[instanceId].enGenCommand = MEM_59_RENESAS_COMMAND_READ;
  } /* else No action required */

  return (LucReturnValue);
} /* End of API Mem_59_Renesas_Read */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#if (MEM_59_RENESAS_READIMMEDIATE_API == STD_ON)
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_ReadImmediate
**
** Service ID               : 0x0E
**
** Description              : This API performs the reading of the flash memory without blank-check
**                            The data from flash memory (source address) is
**                            read to the data buffer (Target address) of the
**                            application.
**
** Sync/Async               : Asynchronous
**
** Reentrancy               : Non Re-entrant
**
** Input Parameters         : instanceId, sourceAddress, length
**
** InOut Parameters         : None
**
** Output Parameters        : destinationDataPtr
**
** Return parameter         : Std_ReturnType
**                            E_OK: if Read command has been accepted.
**                            E_NOT_OK: if Read command has not been accepted.
**
** Preconditions            : Component must be initialized using Mem_59_Renesas_Init().
**
** Global Variables Used    : Mem_59_Renesas_GucInitState, Mem_59_Renesas_GenInstanceState, Mem_59_Renesas_GpInsConfig,
**                            Mem_59_Renesas_GstVar, Mem_59_Renesas_GenJobResult
**
** Function(s) invoked      : Det_ReportError
**
** Reference ID             : MEM_DUD_ACT_062, MEM_DUD_ACT_062_GBL001, MEM_DUD_ACT_062_GBL002, MEM_DUD_ACT_062_GBL003,
** Reference ID             : MEM_DUD_ACT_062_GBL004, MEM_DUD_ACT_062_GBL005, MEM_DUD_ACT_062_GBL006,
** Reference ID             : MEM_DUD_ACT_062_GBL008, MEM_DUD_ACT_062_GBL009, MEM_DUD_ACT_062_GBL010,
** Reference ID             : MEM_DUD_ACT_062_ERR001, MEM_DUD_ACT_062_ERR002, MEM_DUD_ACT_062_ERR003,
** Reference ID             : MEM_DUD_ACT_062_ERR005, MEM_DUD_ACT_062_ERR006, MEM_DUD_ACT_062_GBL007,
** Reference ID             : MEM_DUD_ACT_062_ERR004, MEM_DUD_ACT_062_GBL011
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MEM_PUBLIC_CODE) Mem_59_Renesas_ReadImmediate(Mem_59_Renesas_InstanceIdType instanceId,            /* PRQA S 1503 # JV-01 */
Mem_59_Renesas_AddressType sourceAddress, P2VAR(Mem_59_Renesas_DataType, AUTOMATIC, MEM_APPL_DATA) destinationDataPtr,  /* PRQA S 3432, 3673 # JV-01, JV-01 */
Mem_59_Renesas_LengthType length)
{
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to check if address is valid */
  boolean LblAddrValid;
  #endif
  /* Local variable to hold the DET return value */
  Std_ReturnType LucReturnValue;
  /* Local variable to hold align check value */
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  uint32 LulCheckAlign;
  #endif
  /* Local variable to hold loop count */
  uint32 LulLoop;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  
  /* Initialize return value */
  LucReturnValue = E_OK;
  
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (MEM_59_RENESAS_INITIALIZED != Mem_59_Renesas_GucInitState)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_READIMMEDIATE_SID,
                                                                                               MEM_59_RENESAS_E_UNINIT);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if instanceId is valid */
  else if (MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG <= instanceId)
  {
    /* Report error to DET */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_READIMMEDIATE_SID, 
                                                                                    MEM_59_RENESAS_E_PARAM_INSTANCE_ID);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if the driver is busy by servicing another request */
  else if (MEM_59_RENESAS_BUSY == Mem_59_Renesas_GenInstanceState[instanceId])
  {
    /* Report to DET if the driver is currently busy */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_READIMMEDIATE_SID, 
                                                                                          MEM_59_RENESAS_E_JOB_PENDING);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if destinationDataPtr is NULL_PTR */
  else if (NULL_PTR == destinationDataPtr)                                                                              /* PRQA S 2004 # JV-01 */
  {
    /* Report error to DET */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_READIMMEDIATE_SID, 
                                                                                        MEM_59_RENESAS_E_PARAM_POINTER);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }

  /* Check whether any error is reported to DET */
  if (E_OK == LucReturnValue)
  #endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    LblAddrValid = MEM_59_RENESAS_FALSE;
    #endif
    LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[instanceId].pSectorBatch);

    for (LulLoop = (uint32)MEM_59_RENESAS_ZERO;
      #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
      (MEM_59_RENESAS_FALSE == LblAddrValid) &&
      #endif
      (LulLoop < Mem_59_Renesas_GpInsConfig[instanceId].ulTotalSectorBatch); LulLoop++)
    {
      if ((LpSectorBatch[LulLoop].ulSectorStartAddr <= sourceAddress) &&
          (LpSectorBatch[LulLoop].ulSectorEndAddr >= sourceAddress))
      {
        /* Store index of sector batch */
        Mem_59_Renesas_GstVar[instanceId].ulSectorBatchIdx = LulLoop;

        #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
        LulCheckAlign = LpSectorBatch[LulLoop].ulReadPageSize - (uint32)MEM_59_RENESAS_ONE;                             /* PRQA S 3383 # JV-01 */

        /* Check if sourceAddress aligned to page size */
        if (MEM_59_RENESAS_ZERO == (sourceAddress & LulCheckAlign))
        {
          LblAddrValid = MEM_59_RENESAS_TRUE;
        }
        
        /* Check length */
        if ((MEM_59_RENESAS_ZERO == length) ||
            ((sourceAddress + length - (uint32)MEM_59_RENESAS_ONE) > LpSectorBatch[LulLoop].ulSectorEndAddr) ||         /* PRQA S 3383, 3384 # JV-01, JV-01 */
            (MEM_59_RENESAS_ZERO != ((sourceAddress + length) & LulCheckAlign)) ||                                      /* PRQA S 3383 # JV-01 */
            (length > LpSectorBatch[LulLoop].ulReadBurstSize))
        {
          /* Report error to DET */
          (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_READIMMEDIATE_SID,
                                                                                         MEM_59_RENESAS_E_PARAM_LENGTH);
          /* Reset return value to E_NOT_OK due to failure */
          LucReturnValue = E_NOT_OK;
        }
        #endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
      }
    }

    #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    /* Check sourceAddress */
    if (MEM_59_RENESAS_FALSE == LblAddrValid)
    {
      /* Report error to DET */
      (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_READIMMEDIATE_SID, 
                                                                                        MEM_59_RENESAS_E_PARAM_ADDRESS);
      /* Reset return value to E_NOT_OK due to failure */
      LucReturnValue = E_NOT_OK;
    }
    #endif
  }

  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Check whether any error is reported to DET */
  if (E_OK == LucReturnValue)
  #endif
  {
    /* Set the instance state to busy to accept this read request */
    Mem_59_Renesas_GenInstanceState[instanceId] = MEM_59_RENESAS_BUSY;
    /* Global variable to hold the read start address */
    Mem_59_Renesas_GstVar[instanceId].ulReadAddress = sourceAddress;
    /* Set the global variable with length of bytes to be processed */
    Mem_59_Renesas_GstVar[instanceId].ulRequestedLength = length;
    /* Initialize the global variable with target address and length */
    Mem_59_Renesas_GstVar[instanceId].pBufferAddress = destinationDataPtr;
    /* set the job result as pending */
    Mem_59_Renesas_GenJobResult[instanceId] = MEM_59_RENESAS_JOB_PENDING;
    /* Set the command for Read operation */
    Mem_59_Renesas_GstVar[instanceId].enGenCommand = MEM_59_RENESAS_COMMAND_READIMMEDIATE;
  } /* else No action required */

  return (LucReturnValue);
} /* End of API Mem_59_Renesas_Read */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_GetVersionInfo
**
** Service ID               : 0x02
**
** Description              : This API returns the version information of
**                            this module.
**
** Sync/Async               : Synchronous
**
** Reentrancy               : Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : versionInfoPtr - Pointer to standard version
**                            information structure.
**
** Return parameter         : None
**
** Preconditions            : None
**
** Global Variables Used    : None
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_002, MEM_DUD_ACT_002_ERR001
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_GetVersionInfo(                                                              /* PRQA S 1503 # JV-01 */
                                                    P2VAR(Std_VersionInfoType, AUTOMATIC, MEM_APPL_DATA) versionInfoPtr)/* PRQA S 3432 # JV-01 */
{
  /* Check if parameter passed is equal to Null pointer */
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == versionInfoPtr)
  {
    /* Report to DET  */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_GET_VERSION_INFO_SID, 
                                                                                        MEM_59_RENESAS_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* Copy the vendor Id */
    versionInfoPtr->vendorID = (uint16)MEM_59_RENESAS_VENDOR_ID;
    /* Copy the module Id */
    versionInfoPtr->moduleID = (uint16)MEM_59_RENESAS_MODULE_ID;
    /* Copy Software Major Version */
    versionInfoPtr->sw_major_version = MEM_59_RENESAS_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versionInfoPtr->sw_minor_version = MEM_59_RENESAS_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versionInfoPtr->sw_patch_version = MEM_59_RENESAS_SW_PATCH_VERSION;
  }
} /* End of API Mem_59_Renesas_GetVersionInfo */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_BlankCheck
**
** Service ID               : 0x09
**
** Description              : This API performs the blank check of flash
**                            memory.
**
** Sync/Async               : Asynchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : instanceId, targetAddress, length
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : Std_ReturnType
**                            E_OK: if blank check command has been accepted.
**                            E_NOT_OK: if blank check command has not been accepted.
**
** Preconditions            : Component must be initialized using Mem_59_Renesas_Init().
**
** Global Variables Used    : Mem_59_Renesas_GucInitState, Mem_59_Renesas_GenInstanceState, Mem_59_Renesas_GpInsConfig,
**                            Mem_59_Renesas_GstVar, Mem_59_Renesas_GenJobResult
**
** Function(s) invoked      : Det_ReportError
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_009, MEM_DUD_ACT_009_GBL001, MEM_DUD_ACT_009_GBL002, MEM_DUD_ACT_009_GBL003
** Reference ID             : MEM_DUD_ACT_009_GBL004, MEM_DUD_ACT_009_GBL005, MEM_DUD_ACT_009_GBL006,
** Reference ID             : MEM_DUD_ACT_009_GBL008, MEM_DUD_ACT_009_GBL009, MEM_DUD_ACT_009_GBL010,
** Reference ID             : MEM_DUD_ACT_009_ERR001, MEM_DUD_ACT_009_ERR003, MEM_DUD_ACT_009_ERR004
** Reference ID             : MEM_DUD_ACT_009_ERR006, MEM_DUD_ACT_009_GBL007, MEM_DUD_ACT_009_ERR005
** Reference ID             : MEM_DUD_ACT_009_GBL011
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MEM_PUBLIC_CODE) Mem_59_Renesas_BlankCheck(Mem_59_Renesas_InstanceIdType instanceId,               /* PRQA S 1503 # JV-01 */
                                          Mem_59_Renesas_AddressType targetAddress, Mem_59_Renesas_LengthType length)
{
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to check if address is valid */
  boolean LblAddrValid;
  #endif
  /* Local variable to hold the DET return value */
  Std_ReturnType LucReturnValue;
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Local variable to hold align check value */
  uint32 LulCheckAlign;
  #endif
  /* Local variable to hold loop count */
  uint32 LulLoop;
  /* Local variable to hold end address */
  uint32 LulEndAddr;
  /* Pointer to sector batch */
  const Mem_59_Renesas_SectorBatchType* LpSectorBatch;
  
  /* Initialize return value */
  LucReturnValue = E_OK;
  /* Calculate end address */
  LulEndAddr = (targetAddress + length) - (uint32)MEM_59_RENESAS_ONE;                                                   /* PRQA S 3383, 3384 # JV-01, JV-01 */

  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (MEM_59_RENESAS_INITIALIZED != Mem_59_Renesas_GucInitState)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_BLANK_CHECK_SID,
                                                                                               MEM_59_RENESAS_E_UNINIT);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if instanceId is valid */
  else if (MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG <= instanceId)
  {
    /* Report error to DET */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_BLANK_CHECK_SID, 
                                                                                    MEM_59_RENESAS_E_PARAM_INSTANCE_ID);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if the driver is busy by servicing another request */
  else if (MEM_59_RENESAS_BUSY == Mem_59_Renesas_GenInstanceState[instanceId])                                          /* PRQA S 2004 # JV-01 */
  {
    /* Report to DET if the driver is currently busy */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_BLANK_CHECK_SID, 
                                                                                          MEM_59_RENESAS_E_JOB_PENDING);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }

  /* Check whether any error is reported to DET */
  if (E_OK == LucReturnValue)
  #endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    LblAddrValid = MEM_59_RENESAS_FALSE;
    #endif
    LpSectorBatch = (const Mem_59_Renesas_SectorBatchType*)(Mem_59_Renesas_GpInsConfig[instanceId].pSectorBatch);

    for (LulLoop = (uint32)MEM_59_RENESAS_ZERO;
      (LulLoop < Mem_59_Renesas_GpInsConfig[instanceId].ulTotalSectorBatch); LulLoop++)
    {
      if ((LpSectorBatch[LulLoop].ulSectorStartAddr <= targetAddress) &&
          (LpSectorBatch[LulLoop].ulSectorEndAddr >= targetAddress))
      {
        /* Store index of sector batch */
        Mem_59_Renesas_GstVar[instanceId].ulSectorBatchIdx = LulLoop;
        
        #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
        LulCheckAlign = LpSectorBatch[LulLoop].ulReadPageSize - (uint32)MEM_59_RENESAS_ONE;                             /* PRQA S 3383 # JV-01 */

        /* Check if targetAddress aligned to page size */
        if (MEM_59_RENESAS_ZERO == (targetAddress & LulCheckAlign))
        {
          LblAddrValid = MEM_59_RENESAS_TRUE;
        }
        
        /* Check length */
        if ((MEM_59_RENESAS_ZERO == length) ||
            (LulEndAddr > LpSectorBatch[LulLoop].ulSectorEndAddr) ||
            (MEM_59_RENESAS_ZERO != ((targetAddress + length) & LulCheckAlign)))                                        /* PRQA S 3383 # JV-01 */
        {
          /* Report error to DET */
          (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_BLANK_CHECK_SID,
                                                                                         MEM_59_RENESAS_E_PARAM_LENGTH);
          /* Reset return value to E_NOT_OK due to failure */
          LucReturnValue = E_NOT_OK;
        }
        #endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
        break;
      }
    }

    #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
    /* Check sourceAddress */
    if (MEM_59_RENESAS_FALSE == LblAddrValid)
    {
      /* Report error to DET */
      (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_BLANK_CHECK_SID, 
                                                                                        MEM_59_RENESAS_E_PARAM_ADDRESS);
      /* Reset return value to E_NOT_OK due to failure */
      LucReturnValue = E_NOT_OK;
    }
    #endif
  }

  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  /* Check whether any error is reported to DET */
  if (E_OK == LucReturnValue)
  #endif
  {
    /* Set the instance state to busy to accept this read request */
    Mem_59_Renesas_GenInstanceState[instanceId] = MEM_59_RENESAS_BUSY;
    /* Set the job result to Job pending */
    Mem_59_Renesas_GenJobResult[instanceId] = MEM_59_RENESAS_JOB_PENDING;
    /* Get the write start and end address */
    Mem_59_Renesas_GstVar[instanceId].ulJobStartAddress = targetAddress;
    Mem_59_Renesas_GstVar[instanceId].ulJobEndAddress = LulEndAddr;
    /* Set the global variable with length */
    Mem_59_Renesas_GstVar[instanceId].ulRequestedLength = length;
    /* Set RFD requested flag to FALSE */
    Mem_59_Renesas_GstVar[instanceId].blHwRequestedFlg = MEM_59_RENESAS_FALSE;
    /* Set the command as Write command */
    Mem_59_Renesas_GstVar[instanceId].enGenCommand = MEM_59_RENESAS_COMMAND_BLANKCHECK;
  }
  return (LucReturnValue);
} /* End of API Mem_59_Renesas_BlankCheck */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_Suspend
**
** Service ID               : 0x0c
**
** Description              : This API performs the suspend of the on going
**                            job.
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : instanceId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : Component must be initialized using Mem_59_Renesas_Init().
**
** Global Variables Used    : Mem_59_Renesas_GucInitState, Mem_59_Renesas_GstVar, Mem_59_Renesas_GenJobResult,
**                            Mem_59_Renesas_GblJobSuspendRequest, Mem_59_Renesas_GpInsConfig
**
** Function(s) invoked      : Det_ReportError, pProcessSuspend
**
** Reference ID             : MEM_DUD_ACT_012, MEM_DUD_ACT_012_GBL001, MEM_DUD_ACT_012_GBL002, MEM_DUD_ACT_012_GBL003
** Reference ID             : MEM_DUD_ACT_012_GBL004, MEM_DUD_ACT_012_GBL005, MEM_DUD_ACT_012_ERR001,
** Reference ID             : MEM_DUD_ACT_012_ERR002
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_Suspend(Mem_59_Renesas_InstanceIdType instanceId)                            /* PRQA S 1503 # JV-01 */
{
  /* Check if the module is initialized */
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (MEM_59_RENESAS_INITIALIZED != Mem_59_Renesas_GucInitState)
  {
    /* Report error to DET that module is not initialized */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_SUSPEND_SID, 
                                                                                               MEM_59_RENESAS_E_UNINIT);
  }
  /* Check if instanceId is valid */
  else if (MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG <= instanceId)
  {
    /* Report error to DET */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_SUSPEND_SID, 
                                                                                    MEM_59_RENESAS_E_PARAM_INSTANCE_ID);
  }
  else
  #endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if there is any erase/write check request pending */
    if (((MEM_59_RENESAS_COMMAND_ERASE == Mem_59_Renesas_GstVar[instanceId].enGenCommand) ||
        (MEM_59_RENESAS_COMMAND_WRITE == Mem_59_Renesas_GstVar[instanceId].enGenCommand)) &&
        (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GenJobResult[instanceId]))
    {
      /* Reject if the suspend is already request */
      if (MEM_59_RENESAS_FALSE == Mem_59_Renesas_GblJobSuspendRequest[instanceId])
      {
        Mem_59_Renesas_GpInsConfig[instanceId].pHWIPFunc->pProcessSuspend(instanceId);
      }
    }
  }
} /* End of API Mem_59_Renesas_Suspend */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_Resume
**
** Service ID               : 0x0d
**
** Description              : This API resumes the suspended job.
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : Component must be initialized using Mem_59_Renesas_Init().
**
** Global Variables Used    : Mem_59_Renesas_GucInitState, Mem_59_Renesas_GpInsConfig,
**                            Mem_59_Renesas_GblJobSuspendRequest
**
** Function(s) invoked      : Det_ReportError, pProcessResume, Mem_59_Renesas_RestoreJobData
**                            Mem_59_Renesas_ClearBackUpData
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_013, MEM_DUD_ACT_013_GBL001, MEM_DUD_ACT_013_GBL002, MEM_DUD_ACT_013_GBL003
** Reference ID             : MEM_DUD_ACT_013_ERR001, MEM_DUD_ACT_013_ERR002
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_Resume(Mem_59_Renesas_InstanceIdType instanceId)                             /* PRQA S 1503 # JV-01 */
{
  /* Check if the module is initialized */
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (MEM_59_RENESAS_INITIALIZED != Mem_59_Renesas_GucInitState)
  {
    /* Report error to DET that module is not initialized */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_RESUME_SID, 
                                                                                               MEM_59_RENESAS_E_UNINIT);
  }
  /* Check if instanceId is valid */
  else if (MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG <= instanceId)
  {
    /* Report error to DET */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_RESUME_SID,
                                                                                    MEM_59_RENESAS_E_PARAM_INSTANCE_ID);
  }
  else
  #endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if suspend is requested before and there is no pending request */
    if ((MEM_59_RENESAS_TRUE == Mem_59_Renesas_GblJobSuspendRequest[instanceId]) &&
                                                  (MEM_59_RENESAS_IDLE == Mem_59_Renesas_GenInstanceState[instanceId]))
    {
      /* Restore the Job Variables from the back-up structure */
      Mem_59_Renesas_RestoreJobData(instanceId);
      Mem_59_Renesas_ClearBackUpData(instanceId);
      Mem_59_Renesas_GpInsConfig[instanceId].pHWIPFunc->pProcessResume(instanceId);
    }
  }
} /* End of API Mem_59_Renesas_Resume */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_DeInit
**
** Service ID               : 0x0b
**
** Description              : This API De-initialized MEM module.
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : Component must be initialized using Mem_59_Renesas_Init().
**
** Global Variables Used    : Mem_59_Renesas_GucInitState, Mem_59_Renesas_GstVar, Mem_59_Renesas_GstBackUpVar,
**                            Mem_59_Renesas_GpInsConfig
**
** Function(s) invoked      : Det_ReportError, pHWProcessCancel
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_011, MEM_DUD_ACT_011_GBL001, MEM_DUD_ACT_011_GBL002, MEM_DUD_ACT_011_GBL003
** Reference ID             : MEM_DUD_ACT_011_GBL004,
** Reference ID             : MEM_DUD_ACT_011_ERR001
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_DeInit(void)                                                                 /* PRQA S 1503 # JV-01 */
{
  Mem_59_Renesas_InstanceIdType LulLoop;

  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (MEM_59_RENESAS_INITIALIZED != Mem_59_Renesas_GucInitState)
  {
    /* Report error to DET if the component is not initialized */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_DEINIT_SID,
                                                                                               MEM_59_RENESAS_E_UNINIT);
  }
  else
  #endif /* #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Set module status to uninit */
    Mem_59_Renesas_GucInitState = MEM_59_RENESAS_UNINITIALIZED;

    for (LulLoop = (Mem_59_Renesas_InstanceIdType)MEM_59_RENESAS_ZERO;
                             (LulLoop < (Mem_59_Renesas_InstanceIdType)MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG); LulLoop++)/* PRQA S 2877 # JV-01 */
    {
      /* Cancel on-going job */
      if ((MEM_59_RENESAS_COMMAND_NONE != Mem_59_Renesas_GstVar[LulLoop].enGenCommand) ||
          (MEM_59_RENESAS_COMMAND_NONE != Mem_59_Renesas_GstBackUpVar[LulLoop].enGenCommand))
      {
        Mem_59_Renesas_GpInsConfig[LulLoop].pHWIPFunc->pHWProcessCancel(LulLoop);
      } /* else No action required */
    }
  }
} /* End of API Mem_59_Renesas_DeInit */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_PropagateError
**
** Service ID               : 0x08
**
** Description              : This API De-initialized MEM module.
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : instanceId
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : Component must be initialized using Mem_59_Renesas_Init().
**
** Global Variables Used    : Mem_59_Renesas_GucInitState, Mem_59_Renesas_GenJobResult, Mem_59_Renesas_GstVar
**                            Mem_59_Renesas_GstBackUpVar, Mem_59_Renesas_GpInsConfig, Mem_59_Renesas_GenInstanceState
**                            Mem_59_Renesas_GblJobSuspendRequest
**
** Function(s) invoked      : Det_ReportError, pHWProcessCancel, Mem_59_Renesas_ClearBackUpData
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_008, MEM_DUD_ACT_008_ERR001, MEM_DUD_ACT_008_ERR002, MEM_DUD_ACT_008_GBL002,
** Reference ID             : MEM_DUD_ACT_008_GBL001, MEM_DUD_ACT_008_GBL004, MEM_DUD_ACT_008_GBL003
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PUBLIC_CODE) Mem_59_Renesas_PropagateError(Mem_59_Renesas_InstanceIdType instanceId)                     /* PRQA S 1503 # JV-01 */
{
  /* Check if the module is initialized */
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (MEM_59_RENESAS_INITIALIZED != Mem_59_Renesas_GucInitState)
  {
    /* Report error to DET that module is not initialized */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_PROPAGATE_ERROR_SID,
                                                                                               MEM_59_RENESAS_E_UNINIT);
  }
  /* Check whether the InstanceId is out of range */
  else if (MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG <= instanceId)
  {
    /* Report Error to DET */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_PROPAGATE_ERROR_SID,
                                                                                    MEM_59_RENESAS_E_PARAM_INSTANCE_ID);
  }
  else
  #endif
  {
    /* If instance Id is valid*/
    Mem_59_Renesas_GenJobResult[instanceId] = MEM_59_RENESAS_ECC_UNCORRECTED;
    /* Cancel current job*/
    if ((MEM_59_RENESAS_COMMAND_NONE != Mem_59_Renesas_GstVar[instanceId].enGenCommand) ||
        (MEM_59_RENESAS_COMMAND_NONE != Mem_59_Renesas_GstBackUpVar[instanceId].enGenCommand))
    {
      Mem_59_Renesas_GpInsConfig[instanceId].pHWIPFunc->pHWProcessCancel(instanceId);

      /* Set the command as None */
      Mem_59_Renesas_GstVar[instanceId].enGenCommand = MEM_59_RENESAS_COMMAND_NONE;
      /* Set the instance state to idle */
      Mem_59_Renesas_GenInstanceState[instanceId] = MEM_59_RENESAS_IDLE;

      /* Clear backup data if there a suspended job */
      if (MEM_59_RENESAS_COMMAND_NONE != Mem_59_Renesas_GstBackUpVar[instanceId].enGenCommand)
      {
        Mem_59_Renesas_ClearBackUpData(instanceId);
        Mem_59_Renesas_GblJobSuspendRequest[instanceId] = MEM_59_RENESAS_FALSE;
      }
    }
  }
}/* End of API Mem_59_Renesas_PropagateError */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_HwSpecificService
**
** Service ID               : 0x0A
**
** Description              : This API performs the hardware specific service of the flash memory
**                              The service ID is hwServiceId, data pointer of service dataPtr
** Sync/Async               : Asynchronous
**
** Re-entrancy              : Non Reentrant
**
** Input Parameters         : instanceId, hwServiceId, lengthPtr
**
** InOut Parameters         : dataPtr
**
** Output Parameters        : None
**
** Return parameter         : Std_ReturnType
**
** Preconditions            : Component must be initialized using Mem_59_Renesas_HwSpecificService().
**
** Global Variables Used    : Mem_59_Renesas_GucInitState, Mem_59_Renesas_GpInsConfig
**
** Function(s) invoked      : Det_ReportError, pHWSpecificService
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_010, MEM_DUD_ACT_010_ERR001, MEM_DUD_ACT_010_ERR002, MEM_DUD_ACT_010_ERR003
** Reference ID             : MEM_DUD_ACT_010_ERR004, MEM_DUD_ACT_010_GBL001
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(Std_ReturnType, MEM_PUBLIC_CODE) Mem_59_Renesas_HwSpecificService(Mem_59_Renesas_InstanceIdType instanceId,        /* PRQA S 1503 # JV-01 */
Mem_59_Renesas_HwServiceIdType hwServiceId, P2VAR(Mem_59_Renesas_DataType, AUTOMATIC, MEM_APPL_DATA) dataPtr,           /* PRQA S 3432 # JV-01 */
P2VAR(Mem_59_Renesas_LengthType, AUTOMATIC, MEM_APPL_DATA) lengthPtr)                                                   /* PRQA S 3432 # JV-01 */
{
  /* Local variable to hold the DET return value */
  Std_ReturnType LucReturnValue;
  
  /* Check if the module is initialized */
  #if (MEM_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if (MEM_59_RENESAS_INITIALIZED != Mem_59_Renesas_GucInitState)
  {
    /* Report error to DET that module is not initialized */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, 
                                        MEM_59_RENESAS_HW_SPECIFIC_SERVICE_SID, MEM_59_RENESAS_E_UNINIT);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  else if (MEM_59_RENESAS_TOTAL_INSTANCE_CONFIG <= instanceId)
  {
    /* Report error to DET that instanceId is invalid */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID,
                            MEM_59_RENESAS_HW_SPECIFIC_SERVICE_SID, MEM_59_RENESAS_E_PARAM_INSTANCE_ID);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  else if ((NULL_PTR == dataPtr) || (NULL_PTR == lengthPtr))
  {
    /* Report error to DET that dataPtr or lengthPtr is invalid */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID,
                                  MEM_59_RENESAS_HW_SPECIFIC_SERVICE_SID, MEM_59_RENESAS_E_PARAM_POINTER);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  /* Check if the driver is busy by servicing another request */
  else if (MEM_59_RENESAS_BUSY == Mem_59_Renesas_GenInstanceState[instanceId])
  {
    /* Report to DET if the driver is currently busy */
    (void)Det_ReportError(MEM_59_RENESAS_MODULE_ID, MEM_59_RENESAS_INSTANCE_ID, MEM_59_RENESAS_HW_SPECIFIC_SERVICE_SID,
                                                                                          MEM_59_RENESAS_E_JOB_PENDING);
    /* Reset return value to E_NOT_OK due to failure */
    LucReturnValue = E_NOT_OK;
  }
  else
  #endif
  {
    LucReturnValue = Mem_59_Renesas_GpInsConfig[instanceId].pHWIPFunc->pHWSpecificService(
                                                                instanceId, hwServiceId, dataPtr, lengthPtr);
  }

  return (LucReturnValue);
}/* End of API Mem_59_Renesas_HwSpecificService */
#define MEM_59_RENESAS_STOP_SEC_PUBLIC_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_BackupJobData
**
** Service ID               : NA
**
** Description              : This function takes the job result from the
**                            global job structure and stores it into the
**                            backup structure when suspend operation occurs
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non Re-entrant
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
** Global Variables Used    : Mem_59_Renesas_GstBackUpVar[LulInstanceId].pBufferAddress, 
**                            Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress,
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulSrcDestAddress,
**                            Mem_59_Renesas_GstVar[LulInstanceId].ulSrcDestAddress,
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulReadAddress,
**                            Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress,
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobStartAddress,
**                            Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress,
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobEndAddress,
**                            Mem_59_Renesas_GstVar[LulInstanceId].ulJobEndAddress,
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulRequestedLength,
**                            Mem_59_Renesas_GstVar[LulInstanceId].ulRequestedLength,
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].blHwRequestedFlg,
**                            Mem_59_Renesas_GstVar[LulInstanceId].blHwRequestedFlg,
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulSectorBatchIdx,
**                            Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx,
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].enGenCommand,
**                            Mem_59_Renesas_GstVar[LulInstanceId].enGenCommand,
**                            Mem_59_Renesas_GusBackUpFACI, Mem_59_Renesas_GusFACI
**
** Function(s) invoked      : None
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_022, MEM_DUD_ACT_022_GBL001, MEM_DUD_ACT_022_GBL002, MEM_DUD_ACT_022_GBL003
** Reference ID             : MEM_DUD_ACT_022_GBL004, MEM_DUD_ACT_022_GBL005, MEM_DUD_ACT_022_GBL006,
** Reference ID             : MEM_DUD_ACT_022_GBL007, MEM_DUD_ACT_022_GBL008, MEM_DUD_ACT_022_GBL009,
** Reference ID             : MEM_DUD_ACT_022_GBL010
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_BackupJobData(Mem_59_Renesas_InstanceIdType LulInstanceId)
{
  /* Store the source address */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].pBufferAddress = Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress;
  /* Store the target address */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulSrcDestAddress = Mem_59_Renesas_GstVar[LulInstanceId].ulSrcDestAddress;
  /* Store the read address */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulReadAddress = Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress;
  /* Store the erase/write start address */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobStartAddress = Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress;
  /* Store the erase/write end address */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobEndAddress = Mem_59_Renesas_GstVar[LulInstanceId].ulJobEndAddress;
  /* Store the requested number of bytes to be processed */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulRequestedLength = Mem_59_Renesas_GstVar[LulInstanceId].ulRequestedLength;
  #if (MEM_59_RENESAS_HW_IP == MEM_59_RENESAS_HW_IP_FPSYS)
  /* Store the FACI Number */
  Mem_59_Renesas_GusBackUpFACI = Mem_59_Renesas_GusFACI;
  #endif
  /* Store RFD requested flag */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].blHwRequestedFlg = Mem_59_Renesas_GstVar[LulInstanceId].blHwRequestedFlg;
  /* Store the type of Flash */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulSectorBatchIdx = Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx;
  /* Store the requested commands */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].enGenCommand = Mem_59_Renesas_GstVar[LulInstanceId].enGenCommand;
} /* End of function Mem_59_Renesas_BackupJobData */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_RestoreJobData
**
** Service ID               : NA
**
** Description              : This function takes the job result from the back
**                            up global job structure and restores it into
**                            the original job structure when suspend operation
**                            occurs
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : NA
**
** Global Variables Used    : Mem_59_Renesas_GstBackUpVar.pBufferAddress, 
**                            Mem_59_Renesas_GstBackUpVar.ulSrcDestAddress, Mem_59_Renesas_GstBackUpVar.ulReadAddress,
**                            Mem_59_Renesas_GstBackUpVar.ulJobStartAddress, Mem_59_Renesas_GstBackUpVar.ulJobEndAddress
**                            Mem_59_Renesas_GstBackUpVar.ulRequestedLength, Mem_59_Renesas_GstBackUpVar.enGenCommand,
**                            Mem_59_Renesas_GstBackUpVar.ulSectorBatchIdx, Mem_59_Renesas_GstBackUpVar.blHwRequestedFlg
**                            Mem_59_Renesas_GstVar.pBufferAddress, 
**                            Mem_59_Renesas_GstVar.ulSrcDestAddress, Mem_59_Renesas_GstVar.ulReadAddress,
**                            Mem_59_Renesas_GstVar.ulJobStartAddress, Mem_59_Renesas_GstVar.ulJobEndAddress
**                            Mem_59_Renesas_GstVar.ulRequestedLength, Mem_59_Renesas_GstVar.enGenCommand,
**                            Mem_59_Renesas_GstVar.ulSectorBatchIdx, Mem_59_Renesas_GstVar.blHwRequestedFlg
**
** Function(s) invoked      : Mem_59_Renesas_FPSYS_GetFACINumber
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_024, MEM_DUD_ACT_024_GBL001, MEM_DUD_ACT_024_GBL002, MEM_DUD_ACT_024_GBL003
** Reference ID             : MEM_DUD_ACT_024_GBL004, MEM_DUD_ACT_024_GBL005, MEM_DUD_ACT_024_GBL006,
** Reference ID             : MEM_DUD_ACT_024_GBL008, MEM_DUD_ACT_024_GBL009, MEM_DUD_ACT_024_GBL007
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_RestoreJobData(Mem_59_Renesas_InstanceIdType LulInstanceId)                 /* PRQA S 1505 # JV-01 */
{
  /* Store the source address */
  Mem_59_Renesas_GstVar[LulInstanceId].pBufferAddress = Mem_59_Renesas_GstBackUpVar[LulInstanceId].pBufferAddress;
  /* Store the target address */
  Mem_59_Renesas_GstVar[LulInstanceId].ulSrcDestAddress = Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulSrcDestAddress;
  /* Store the read address */
  Mem_59_Renesas_GstVar[LulInstanceId].ulReadAddress = Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulReadAddress;
  /* Store the erase/write start address */
  Mem_59_Renesas_GstVar[LulInstanceId].ulJobStartAddress = Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobStartAddress;
  /* Store the erase/write end address */
  Mem_59_Renesas_GstVar[LulInstanceId].ulJobEndAddress = Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobEndAddress;
  /* Store the requested number of bytes to be processed */
  Mem_59_Renesas_GstVar[LulInstanceId].ulRequestedLength = Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulRequestedLength;
  /* Store the requested commands */
  Mem_59_Renesas_GstVar[LulInstanceId].enGenCommand = Mem_59_Renesas_GstBackUpVar[LulInstanceId].enGenCommand;
  /* Store the Sectorbatch index */
   Mem_59_Renesas_GstVar[LulInstanceId].ulSectorBatchIdx = Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulSectorBatchIdx;
  #if (MEM_59_RENESAS_HW_IP == MEM_59_RENESAS_HW_IP_FPSYS)
  /* Invoke Mem_59_Renesas_FPSYS_GetFACINumber function with 
                                                        Mem_59_Renesas_GstBackUpVar.ulJobStartAddress as an argument */
  Mem_59_Renesas_FPSYS_GetFACINumber(Mem_59_Renesas_GstVar[LulInstanceId].ulJobEndAddress, LulInstanceId);
  #endif
  /* Store RFD requested flag */
  Mem_59_Renesas_GstVar[LulInstanceId].blHwRequestedFlg = Mem_59_Renesas_GstBackUpVar[LulInstanceId].blHwRequestedFlg;
} /* End of function Mem_59_Renesas_RestoreJobData */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name            : Mem_59_Renesas_ClearBackUpData
**
** Service ID               : NA
**
** Description              : This function clears the job data from the back
**                            up global job structure.
**
** Sync/Async               : Synchronous
**
** Re-entrancy              : Non Re-entrant
**
** Input Parameters         : None
**
** InOut Parameters         : None
**
** Output Parameters        : None
**
** Return parameter         : None
**
** Preconditions            : NA
**
** Global Variables Used    : Mem_59_Renesas_GstBackUpVar[LulInstanceId].pBufferAddress, 
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulSrcDestAddress,
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulReadAddress,
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobStartAddress,
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobEndAddress
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulRequestedLength,
**                            Mem_59_Renesas_GstBackUpVar[LulInstanceId].enGenCommand,
**                            Mem_59_Renesas_GusBackUpFACI, Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulSectorBatchIdx
**
** Function(s) invoked      : None
**
** Registers Used           : None
**
** Reference ID             : MEM_DUD_ACT_026, MEM_DUD_ACT_026_GBL001, MEM_DUD_ACT_026_GBL002, MEM_DUD_ACT_026_GBL003
** Reference ID             : MEM_DUD_ACT_026_GBL004, MEM_DUD_ACT_026_GBL005, MEM_DUD_ACT_026_GBL006,
** Reference ID             : MEM_DUD_ACT_026_GBL008, MEM_DUD_ACT_026_GBL007
***********************************************************************************************************************/
#define MEM_59_RENESAS_START_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
FUNC(void, MEM_PRIVATE_CODE) Mem_59_Renesas_ClearBackUpData(Mem_59_Renesas_InstanceIdType LulInstanceId)                /* PRQA S 1505 # JV-01 */
{
  /* Store the source address */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].pBufferAddress = NULL_PTR;
  /* Store the target address */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulSrcDestAddress = (uint32)MEM_59_RENESAS_ZERO;
  /* Store the read address */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulReadAddress = (uint32)MEM_59_RENESAS_ZERO;
  /* Store the erase/write start address */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobStartAddress = (uint32)MEM_59_RENESAS_ZERO;
  /* Store the erase/write end address */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulJobEndAddress = (uint32)MEM_59_RENESAS_ZERO;
  /* Store the requested number of bytes to be processed */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulRequestedLength = (uint32)MEM_59_RENESAS_ZERO;
  /* Store the sectorbatch index */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].ulSectorBatchIdx = (uint32)MEM_59_RENESAS_ZERO;
  /* Store the requested commands */
  Mem_59_Renesas_GstBackUpVar[LulInstanceId].enGenCommand = MEM_59_RENESAS_COMMAND_NONE;
  /* Store the FACI Number with Initiate value */
  #if (MEM_59_RENESAS_HW_IP == MEM_59_RENESAS_HW_IP_FPSYS)
  /* Store the FACI Number with Initiate value */
  Mem_59_Renesas_GusBackUpFACI = MEM_59_RENESAS_FACI_0;
  #endif
} /* End of function Mem_59_Renesas_ClearBackUpData */
#define MEM_59_RENESAS_STOP_SEC_PRIVATE_CODE
#include "Mem_59_Renesas_MemMap.h"                                                                                      /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
