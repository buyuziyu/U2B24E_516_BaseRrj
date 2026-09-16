/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Spi.c                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2023-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains kernel API function implementations of SPI Driver                                               */
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
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 * 2.1.1:  07/08/2024  : Update "Spi_Kernel_SyncTransmit" to correct for Sync transmission in multicore
 *                     : Update conditions for the preprocessor Spi_Kernel_Cancel and Spi_Kernel_ForceCancel
 *                     : Remove QAC messages (2:0857) to fix redundant QAC messages
 *                     : Increase SW-VERSION up to 2.0.3
 *                       Change macro SPI_KERNEL_COREID to global variable Spi_GucKernalCoreId
 *                       In API Spi_Kernel_AsyncTransmit, Spi_Kernel_SyncTransmit, Spi_Kernel_Cancel, 
 *                       Spi_Kernel_ForceCancel: Change SPI_MAX_SEQUENCE to Spi_GpConfigPtr->ucNoOfSequences
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  23/10/2023  : Update SW-VERSION to 2.0.1
 * 2.0.0:  23/08/2023  : Update reference ID
 *         04/04/2023  : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function 'name' is defined but is not used within this project.                          */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1                                                         */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:4461)    : A non-constant expression of 'essentially unsigned' type (%1s) is being converted to         */
/*                       narrower unsigned type, '%2s' on assignment.                                                 */
/* Rule                : CERTCCM INT02, MISRA C:2012 Rule-10.3, CWE Rule CWE-681, CWE-136, CWE-192                    */
/* JV-01 Justification : This operation is necessary to offset a 32-bit address on RAM to a 16-bit buffer address.    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : CERTCCM EXP02, MISRA C:2012 Rule-13.5, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it is not a direct access to the HW register, and there    */
/*                       is no side effect.                                                                           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* internal type */
#include "Spi.h"
#include "Spi_Ram.h"
#if (SPI_MULTI_CORE_SUPPORT == STD_ON)
/* Kernel header */
#include "Spi_Kernel.h"
/* Os header */
#include "Os.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define SPI_KERNEL_C_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION_VALUE
#define SPI_KERNEL_C_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION_VALUE
#define SPI_KERNEL_C_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define SPI_KERNEL_C_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION_VALUE
#define SPI_KERNEL_C_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (SPI_AR_RELEASE_MAJOR_VERSION != SPI_KERNEL_C_AR_RELEASE_MAJOR_VERSION)
  #error "Spi_Kernel.c : Mismatch in Release Major Version"
#endif
#if (SPI_AR_RELEASE_MINOR_VERSION != SPI_KERNEL_C_AR_RELEASE_MINOR_VERSION)
  #error "Spi_Kernel.c : Mismatch in Release Minor Version"
#endif
#if (SPI_AR_RELEASE_REVISION_VERSION != SPI_KERNEL_C_AR_RELEASE_REVISION_VERSION)
  #error "Spi_Kernel.c : Mismatch in Release Revision Version"
#endif
#if (SPI_SW_MAJOR_VERSION != SPI_KERNEL_C_SW_MAJOR_VERSION)
  #error "Spi_Kernel.c : Mismatch in Software Major Version"
#endif
#if (SPI_SW_MINOR_VERSION != SPI_KERNEL_C_SW_MINOR_VERSION)
  #error "Spi_Kernel.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (SPI_MULTI_CORE_SUPPORT == STD_ON)
/* Globale scope - share among cores */
/* Start and stop channel request */
#define SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"

/* Sync and Async transmit request */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
volatile VAR(Spi_AsyncTransmit_RequestType, SPI_VAR_NO_INIT) Spi_GaaAsyncTransmitInfo[SPI_MAX_SEQUENCE];
#endif
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
volatile VAR(Spi_SyncTransmit_RequestType, SPI_VAR_NO_INIT) Spi_GaaSyncTransmitInfo[SPI_MAX_SEQUENCE];
#endif
/* Cancel transmit request */
#if (SPI_CANCEL_API == STD_ON)
volatile VAR(Spi_CancelTransmit_RequestType, SPI_VAR_NO_INIT) Spi_GaaCancelTransmitInfo[SPI_MAX_SEQUENCE];
#endif
#if (SPI_FORCE_CANCEL_API == STD_ON)
volatile VAR(Spi_CancelTransmit_RequestType, SPI_VAR_NO_INIT) Spi_GaaForceCancelTransmitInfo[SPI_MAX_SEQUENCE];
#endif

#define SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

#define SPI_START_SEC_PUBLIC_CODE_LOCAL
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Spi_Kernel_AsyncTransmit
**
** Service ID            : None
**
** Description           : This kernel function will check all requests from the satellite core, and proceed the request
**                         to hardware IP respectively.
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : 1. SPI Driver should be initialized.
**                         2. The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Spi_GaaAsyncTransmitInfo, Spi_GucKernalCoreId, Spi_GpConfigPtr
**
** Functions invoked     : Spi_StartTransmission, SPI_ENTER_CRITICAL_SECTION, SPI_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
**
** Reference ID          : SPI_DUD_ACT_104, SPI_DUD_ACT_104_CRT001, SPI_DUD_ACT_104_CRT002, SPI_DUD_ACT_104_GBL001
***********************************************************************************************************************/
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(void, SPI_PUBLIC_CODE) Spi_Kernel_AsyncTransmit(void)                                                              /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to loop all configured channels */
  VAR(Spi_SequenceType, AUTOMATIC) LucSeqIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */

  /* Check if the SPI Driver is initialized properly */
  if((SPI_TRUE == Spi_GblInitialized) && (Spi_GucKernalCoreId == LucCoreID))                                            /* PRQA S 3416, 3415 # JV-01, JV-01 */
  {
    /* Loop for all sequences for checking if any requests */
    for(LucSeqIndex = 0U; LucSeqIndex < Spi_GpConfigPtr->ucNoOfSequences; LucSeqIndex++)                                /* PRQA S 3416 # JV-01 */
    {
      /* Checking if any request from Satellite */
      if(Spi_CheckingRequest(Spi_GaaAsyncTransmitInfo[LucSeqIndex].blSetRequest))                                       /* PRQA S 3432 # JV-01 */
      {
        Spi_StartTransmission((uint32)LucSeqIndex);
        /* Clean request */
        SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
        Spi_GaaAsyncTransmitInfo[LucSeqIndex].blSetRequest = SPI_FALSE;
        SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
      } /* else No action required */
    }
  } /* else No action required */
}
#endif

/***********************************************************************************************************************
** Function Name         : Spi_Kernel_SyncTransmit
**
** Service ID            : None
**
** Description           : This kernel function will check all requests from the satellite core, and proceed the request
**                         to hardware IP respectively.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : 1. SPI Driver should be initialized.
**                         2. The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Spi_GaaSyncTransmitInfo, Spi_GucKernalCoreId, Spi_GpConfigPtr
**
** Functions invoked     : Spi_TransmitSyncSequence, SPI_ENTER_CRITICAL_SECTION, SPI_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
**
** Reference ID          : SPI_DUD_ACT_105, SPI_DUD_ACT_105_GBL001, SPI_DUD_ACT_105_CRT001, SPI_DUD_ACT_105_CRT002
***********************************************************************************************************************/
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
FUNC(void, SPI_PUBLIC_CODE) Spi_Kernel_SyncTransmit(void)                                                               /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to loop all configured channels */
  VAR(Spi_SequenceType, AUTOMATIC) LucSeqIndex;
  Std_ReturnType LucReturnValue;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */

  /* Check if the SPI Driver is initialized properly */
  if((SPI_TRUE == Spi_GblInitialized) && (Spi_GucKernalCoreId == LucCoreID))                                            /* PRQA S 3416, 3415 # JV-01, JV-01 */
  {
    /* Loop for all sequences for checking if any requests */
    for(LucSeqIndex = 0U; LucSeqIndex < Spi_GpConfigPtr->ucNoOfSequences; LucSeqIndex++)                                /* PRQA S 3416 # JV-01 */
    {
      /* Checking if any request from Satellite */
      if(Spi_CheckingRequest(Spi_GaaSyncTransmitInfo[LucSeqIndex].blSetRequest))                                        /* PRQA S 3432 # JV-01 */
      {
        SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
        /* Clean request */
        Spi_GaaSyncTransmitInfo[LucSeqIndex].blSetRequest = SPI_FALSE;
        SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);

        /* Transmit sequence */
        LucReturnValue = Spi_TransmitSyncSequence((uint32)LucSeqIndex);
        
        SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
        /* Set transmit result */
        Spi_GaaSyncTransmitInfo[LucSeqIndex].ucResult = LucReturnValue;

        /* Clean request after completing transmission */
        Spi_GaaSyncTransmitInfo[LucSeqIndex].blSetRequest = SPI_FALSE;
        SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
      } /* else No action required */
    }
  } /* else No action required */
}
#endif

/***********************************************************************************************************************
** Function Name         : Spi_Kernel_Cancel
**
** Service ID            : None
**
** Description           : This kernel function will check all requests from the satellite core, and proceed the request
**                         to hardware IP respectively.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : 1. SPI Driver should be initialized.
**                         2. The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Spi_GaaCancelTransmitInfo, Spi_GucKernalCoreId, Spi_GpConfigPtr
**
** Functions invoked     : Spi_CancelSequence, SPI_ENTER_CRITICAL_SECTION, SPI_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
**
** Reference ID          : SPI_DUD_ACT_106, SPI_DUD_ACT_106_GBL001, SPI_DUD_ACT_106_CRT001, SPI_DUD_ACT_106_CRT002
***********************************************************************************************************************/
#if ((SPI_CANCEL_API == STD_ON) && ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)))
FUNC(void, SPI_PUBLIC_CODE) Spi_Kernel_Cancel(void)                                                                     /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to loop all configured channels */
  VAR(Spi_SequenceType, AUTOMATIC) LucSeqIndex;

  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */

  /* Check if the SPI Driver is initialized properly */
  if((SPI_TRUE == Spi_GblInitialized) && (Spi_GucKernalCoreId == LucCoreID))                                            /* PRQA S 3416, 3415 # JV-01, JV-01 */
  {
    /* Loop for all sequences for checking if any requests */
    for(LucSeqIndex = 0U; LucSeqIndex < Spi_GpConfigPtr->ucNoOfSequences; LucSeqIndex++)                                /* PRQA S 3416 # JV-01 */
    {
      /* Checking if any request from Satellite */
      if(Spi_CheckingRequest(Spi_GaaCancelTransmitInfo[LucSeqIndex].blSetRequest))                                      /* PRQA S 3432 # JV-01 */
      {
        SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);

        if(Spi_UnLockedStatus(Spi_GaaCancelTransmitInfo[LucSeqIndex].blBufferLock))                                     /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          Spi_LockProcess(Spi_GaaCancelTransmitInfo[LucSeqIndex].blBufferLock);                                         /* PRQA S 3432 # JV-01 */
          SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
          /* Cancel sequence */
          Spi_CancelSequence((uint32)LucSeqIndex, SPI_FALSE);
          /* Clean request */
          Spi_GaaCancelTransmitInfo[LucSeqIndex].blSetRequest = SPI_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          Spi_UnLockProcess(Spi_GaaCancelTransmitInfo[LucSeqIndex].blBufferLock);                                       /* PRQA S 3432 # JV-01 */
        }
        else
        {
           SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
        }
      } /* else No action required */
    }
  } /* else No action required */
}
#endif /* #if ((SPI_CANCEL_API == STD_ON) \
                                    && ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)))*/

/***********************************************************************************************************************
** Function Name         : Spi_Kernel_ForceCancel
**
** Service ID            : None
**
** Description           : This kernel function will check all requests from the satellite core, and proceed the request
**                         to hardware IP respectively.
**
** Sync/Async            : Synchronous
**
** Re-entrancy           : Non-Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : 1. SPI Driver should be initialized.
**                         2. The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Spi_GaaForceCancelTransmitInfo, Spi_GucKernalCoreId, Spi_GpConfigPtr
**
** Functions invoked     : Spi_CancelSequence, SPI_ENTER_CRITICAL_SECTION, SPI_EXIT_CRITICAL_SECTION
**
** Registers Used        : None
**
** Reference ID          : SPI_DUD_ACT_107, SPI_DUD_ACT_107_GBL001, SPI_DUD_ACT_107_CRT001, SPI_DUD_ACT_107_CRT002
***********************************************************************************************************************/
#if ((SPI_FORCE_CANCEL_API == STD_ON) && ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)))
FUNC(void, SPI_PUBLIC_CODE) Spi_Kernel_ForceCancel(void)                                                                /* PRQA S 1503 # JV-01 */
{
  /* Declare the variable to loop all configured channels */
  VAR(Spi_SequenceType, AUTOMATIC) LucSeqIndex;

  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = GetCoreID();                                                                                              /* PRQA S 4461 # JV-01 */

  /* Check if the SPI Driver is initialized properly */
  if((SPI_TRUE == Spi_GblInitialized) && (Spi_GucKernalCoreId == LucCoreID))                                            /* PRQA S 3416, 3415 # JV-01, JV-01 */
  {
    /* Loop for all sequences for checking if any requests */
    for(LucSeqIndex = 0U; LucSeqIndex < Spi_GpConfigPtr->ucNoOfSequences; LucSeqIndex++)                                /* PRQA S 3416 # JV-01 */
    {
      /* Checking if any request from Satellite */
      if(Spi_CheckingRequest(Spi_GaaForceCancelTransmitInfo[LucSeqIndex].blSetRequest))                                 /* PRQA S 3432 # JV-01 */
      {
        SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);

        if(Spi_UnLockedStatus(Spi_GaaForceCancelTransmitInfo[LucSeqIndex].blBufferLock))                                /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          Spi_LockProcess(Spi_GaaForceCancelTransmitInfo[LucSeqIndex].blBufferLock);                                    /* PRQA S 3432 # JV-01 */

          SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);

          /* Cancel sequence */
          Spi_CancelSequence((uint32)LucSeqIndex, SPI_TRUE);
          /* Clean request */
          Spi_GaaForceCancelTransmitInfo[LucSeqIndex].blSetRequest = SPI_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          Spi_UnLockProcess(Spi_GaaForceCancelTransmitInfo[LucSeqIndex].blBufferLock);                                  /* PRQA S 3432 # JV-01 */
        }
        else
        {
           SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
        }
      } /* else No action required */
    }
  } /* else No action required */
}
#endif /* ((SPI_FORCE_CANCEL_API == STD_ON) && \
                                       ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)))*/

#define SPI_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* SPI_MULTI_CORE_SUPPORT == STD_ON */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
