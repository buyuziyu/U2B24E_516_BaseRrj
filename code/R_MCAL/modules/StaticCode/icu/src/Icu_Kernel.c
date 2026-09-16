/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Icu_Kernel.c                                                                                        */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains API function implementations of ICU Driver                                                      */
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
 *  2.4.1:  30/06/2025  : Remove SW-VERSION in file header
 *  2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01 Release
 *  2.3.1:  31/03/2025  : As part of support QAC 11.6.0, following changes are made:
                          1. Add message 0404 and remove message 2814
 *  2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 *  2.1.2:  31/10/2024  : As part of support QAC 9.5.0, following changes are made:
 *                        1. Update QAC message and QAC header
 *                        As part of supporting GTM HWIP into common code, following changes are made:
 *                        1. Remove pEnableEdgeDetection and pDisableEdgeDetection, update code comment, remove Det.h
 *                        As part of supporting multi core multi postbuid variant, following changes are made:
 *                        1. Change macro ICU_KERNEL_COREID to global variable Icu_GucKernalCoreId
 *                        Update SW-VERSION for Ver22.01.02 Beta2 Release 
 *  2.0.1  19/10/2023   : Remove QAC messages 0857, 2814. Add QAC message 0404.
 *  2.0.0  04/04/2023   : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                             Margin for Control History                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : MISRA C:2012 Rule-1.3, Rule-13.2, CERTCCM EXP30, EXP10, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get an element in the array of struct, volatile of the counter variable of 'for'  */
/*                       loop is used to ensure no optimization. It is accepted                                       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : MISRA C:2012 Rule-2.1, CERTCCM MSC07, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with persistent side effects.            */
/* Rule                : MISRA C:2012 Rule-13.5, CERTCCM EXP02, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it does not have direct access to the HW register, and     */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifiers. There is no impact on the functionality    */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used following AUTOSAR standard rule. It is accepted.*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* internal type */
#include "Icu.h"
#include "Icu_Ram.h"
#if (ICU_MULTI_CORE_SUPPORT == STD_ON)
/* Kernel header */
#include "Icu_Kernel.h"
/* Os header */
#include "Os.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define ICU_KERNEL_C_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_KERNEL_C_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_KERNEL_C_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define ICU_KERNEL_C_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION_VALUE
#define ICU_KERNEL_C_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (ICU_AR_RELEASE_MAJOR_VERSION != ICU_KERNEL_C_AR_RELEASE_MAJOR_VERSION)
  #error "Icu_Kernel.c : Mismatch in Release Major Version"
#endif
#if (ICU_AR_RELEASE_MINOR_VERSION != ICU_KERNEL_C_AR_RELEASE_MINOR_VERSION)
  #error "Icu_Kernel.c : Mismatch in Release Minor Version"
#endif
#if (ICU_AR_RELEASE_REVISION_VERSION != ICU_KERNEL_C_AR_RELEASE_REVISION_VERSION)
  #error "Icu_Kernel.c : Mismatch in Release Revision Version"
#endif
#if (ICU_SW_MAJOR_VERSION != ICU_KERNEL_C_SW_MAJOR_VERSION)
  #error "Icu_Kernel.c : Mismatch in Software Major Version"
#endif
#if (ICU_SW_MINOR_VERSION != ICU_KERNEL_C_SW_MINOR_VERSION)
  #error "Icu_Kernel.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if (ICU_MULTI_CORE_SUPPORT == STD_ON)
/* Globale scope - share among cores */
#define ICU_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Icu_MemMap.h"

#if (ICU_TIMESTAMP_API == STD_ON)
/* Icu_StartTimestamp request */
volatile VAR(Icu_StartTimestamp_RequestType, ICU_VAR_NO_INIT) 
                                                          Icu_GaaStartTimestampBuffer[ICU_TOTAL_TIMESTAMP_CHANNELS];
/* Icu_StopTimestamp request */
volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT) Icu_GaaStopTimestampBuffer[ICU_TOTAL_TIMESTAMP_CHANNELS];
#endif

#if (ICU_EDGE_COUNT_API == STD_ON)
/* Icu_ResetEdgeCount request */
volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT) Icu_GaaResetEdgeCountBuffer[ICU_TOTAL_EDGECOUNT_CHANNELS];
/* Icu_EnableEdgeCount request */
volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT) Icu_GaaEnableEdgeCountBuffer[ICU_TOTAL_EDGECOUNT_CHANNELS];
/* Icu_DisableEdgeCount request */
volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT) Icu_GaaDisableEdgeCountBuffer[ICU_TOTAL_EDGECOUNT_CHANNELS];
#endif

#if (ICU_EDGE_DETECT_API == STD_ON)
/* Icu_EnableEdgeDetection request */
volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT) Icu_GaaEnableEdgeDetectionBuffer[ICU_TOTAL_EDGEDETECT_CHANNELS];
/* Icu_DisableEdgeDetection request */
volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT) 
Icu_GaaDisableEdgeDetectionBuffer[ICU_TOTAL_EDGEDETECT_CHANNELS];
#endif

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/* Icu_StartSignalMeasurement request */
volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT)
                                            Icu_GaaStartSignalMeasurementBuffer[ICU_TOTAL_SIGNALMEASUREMENT_CHANNELS];
/* Icu_StopSignalMeasurement request */
volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT)
                                            Icu_GaaStopSignalMeasurementBuffer[ICU_TOTAL_SIGNALMEASUREMENT_CHANNELS];
#endif

/* Icu_SetActivationCondition request */
volatile VAR(Icu_SetActivationCondition_RequestType, ICU_VAR_NO_INIT)
                                                            Icu_GaaSetActivationConditionBuffer[ICU_MAX_CHANNEL];

#define ICU_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/

#define ICU_START_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
** Function Name         : Icu_Kernel_StartTimestamp
**
** Service ID            : None
**
** Description           : This kernel function will check all requests of Icu_StartTimestamp API from the satellite 
**                         core, and proceed the request to the internal function Icu_<HWIP>_StartTimestamp of 
**                         respective hardware IP.
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
** Preconditions         : 1. ICU Driver should be initialized.
**                         2. The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Icu_GblDriverStatus, Icu_GaaStartTimestampBuffer, Icu_GaaHwDepFunc
**                         Icu_GpTimeStampData, Icu_GpChannelConfig, Icu_GpChannelRamData
**
** Functions invoked     : Icu_HW_Atu_StopCountMeasurement,
**                         Icu_HW_Taud_StopCountMeasurement, Icu_HW_Tauj_StopCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_094, ICU_DUD_ACT_094_CRT001
** Reference ID          : ICU_DUD_ACT_094_CRT002, ICU_DUD_ACT_094_CRT003, ICU_DUD_ACT_094_CRT004
** Reference ID          : ICU_DUD_ACT_094_GBL001, ICU_DUD_ACT_094_GBL002, ICU_DUD_ACT_094_GBL003
** Reference ID          : ICU_DUD_ACT_094_GBL004, ICU_DUD_ACT_094_GBL005, ICU_DUD_ACT_094_CRT005
***********************************************************************************************************************/
#if (ICU_TIMESTAMP_API == STD_ON)
FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_StartTimestamp(void)                                                             /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerType;
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucRamIndex;
  /* Declare the variable to hold the channel index */
  VAR(Icu_ChannelType, AUTOMATIC) LddChannelIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check if the kernel isn't running on configured partition */
  if ((Icu_GucKernalCoreId == LucCoreID) && (ICU_INITIALIZED == Icu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucRamIndex = 0U; LucRamIndex < ICU_TOTAL_TIMESTAMP_CHANNELS; LucRamIndex++)
    {
      /* Checking if any request from Satellite */
      if(ICU_CHECKINGREQUEST(Icu_GaaStartTimestampBuffer[LucRamIndex].blSetRequest))                                    /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        /* Check if the buffer is locked */
        if(ICU_UNLOCKEDSTATUS(Icu_GaaStartTimestampBuffer[LucRamIndex].blBufferLock))                                   /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          ICU_LOCKPROCESS(Icu_GaaStartTimestampBuffer[LucRamIndex].blBufferLock);                                       /* PRQA S 3432 # JV-01 */
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
          /* Initialize Timestamp RAM data */
          Icu_GpTimeStampData[LucRamIndex].pBufferPointer = Icu_GaaStartTimestampBuffer[LucRamIndex].lpBufferPtr;       /* PRQA S 0404 # JV-01 */
          Icu_GpTimeStampData[LucRamIndex].usBufferSize = Icu_GaaStartTimestampBuffer[LucRamIndex].lusBufferSize;       /* PRQA S 0404 # JV-01 */
          Icu_GpTimeStampData[LucRamIndex].usTimestampIndex = (uint16)ICU_BUFFER_IDX_INIT_VAL;
          Icu_GpTimeStampData[LucRamIndex].usTimestampsCounter = (uint16)ICU_ZERO;
          Icu_GpTimeStampData[LucRamIndex].usNotifyInterval =                                                           /* PRQA S 0404 # JV-01 */
                                                      Icu_GaaStartTimestampBuffer[LucRamIndex].lusNotifyInterval;
          /* Read the channel index */
          LddChannelIndex = Icu_GaaStartTimestampBuffer[LucRamIndex].lddChannel;
          /* Read the Timer Type for the given channel */
          LucTimerType = Icu_GpChannelConfig[LddChannelIndex].ucIcuChannelType;
          /* Activate Timestamp capturing */
          if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pStartCountMeasurement)                                       /* PRQA S 3416 # JV-01 */
          {
            Icu_GaaHwDepFunc[LucTimerType]->pStartCountMeasurement(LddChannelIndex);
          } /* else No action required */
          /* Get the spin lock due to ucChannelStatus be updated by satellite core */
          ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
          /* Initialize channel status as active */
          Icu_GpChannelRamData[LddChannelIndex].ucChannelStatus = (uint8)ICU_ACTIVE;
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
          /* Set the flag to indicate that the timestamping is started */
          Icu_GpTimeStampData[LucRamIndex].blTimestampingStarted = ICU_TRUE;
          /* Clean request */
          Icu_GaaStartTimestampBuffer[LucRamIndex].blSetRequest = ICU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          ICU_UNLOCKPROCESS(Icu_GaaStartTimestampBuffer[LucRamIndex].blBufferLock);                                     /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    } /* else No action required */
  } /* End of ICU_INITIALIZED == Icu_GblDriverStatus */
} /* End of API Icu_StartTimer */
#endif /* End of ICU_TIMESTAMP_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Icu_Kernel_StopTimestamp
**
** Service ID            : None
**
** Description           : This kernel function will check all requests of Icu_StopTimestamp API from the satellite 
**                         core, and proceed the request to the internal function Icu_<HWIP>_StopTimestamp of 
**                         respective hardware IP.
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
** Preconditions         : 1. ICU Driver should be initialized.
**                         2. The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Icu_GblDriverStatus, Icu_GaaStopTimestampBuffer, Icu_GaaHwDepFunc, Icu_GpChannelConfig
**                         Icu_GpChannelRamData
**
** Functions invoked     : Icu_HW_Atu_StopCountMeasurement,
**                         Icu_HW_Taud_StopCountMeasurement, Icu_HW_Tauj_StopCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_095, ICU_DUD_ACT_095_GBL001, ICU_DUD_ACT_095_GBL002, ICU_DUD_ACT_095_GBL003
** Reference ID          : ICU_DUD_ACT_095_GBL004, ICU_DUD_ACT_095_CRT001, ICU_DUD_ACT_095_CRT002,ICU_DUD_ACT_095_CRT003
***********************************************************************************************************************/
#if (ICU_TIMESTAMP_API == STD_ON)
FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_StopTimestamp(void)                                                              /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerType;
  /* Declare the variable to loop all time stamp ram index */
  VAR(uint8, AUTOMATIC) LucRamIndex;
  /* Declare the variable to hold the channel index */
  VAR(Icu_ChannelType, AUTOMATIC) LddChannelIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check if the kernel isn't running on configured partition */
  if ((Icu_GucKernalCoreId == LucCoreID) && (ICU_INITIALIZED == Icu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Loop for all channels for checking if any requests */
    for(LucRamIndex = 0U; LucRamIndex < ICU_TOTAL_TIMESTAMP_CHANNELS; LucRamIndex++)
    {
      /* Checking if any request from Satellite */
      if(ICU_CHECKINGREQUEST(Icu_GaaStopTimestampBuffer[LucRamIndex].blSetRequest))                                     /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the buffer is locked */
        if(ICU_UNLOCKEDSTATUS(Icu_GaaStopTimestampBuffer[LucRamIndex].blBufferLock))                                    /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          ICU_LOCKPROCESS(Icu_GaaStopTimestampBuffer[LucRamIndex].blBufferLock);                                        /* PRQA S 3432 # JV-01 */
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
          /* Read the channel index */
          LddChannelIndex = Icu_GaaStopTimestampBuffer[LucRamIndex].lddChannel;
          /* Read the Timer Type for the given channel */
          LucTimerType = Icu_GpChannelConfig[LddChannelIndex].ucIcuChannelType;
          /* Stop Timestamp capturing */
          if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pStopCountMeasurement)                                        /* PRQA S 3416 # JV-01 */
          {
            Icu_GaaHwDepFunc[LucTimerType]->pStopCountMeasurement(LddChannelIndex);
          } /* else No action required */
          /* Initialize channel status as idle */
          Icu_GpChannelRamData[LddChannelIndex].ucChannelStatus = (uint8)ICU_IDLE;

          /* Clean request */
          Icu_GaaStopTimestampBuffer[LucRamIndex].blSetRequest = ICU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          ICU_UNLOCKPROCESS(Icu_GaaStopTimestampBuffer[LucRamIndex].blBufferLock);                                      /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    } /* End of looping all channels */
  } /* End of ICU_INITIALIZED == Icu_GblDriverStatus */
} /* End of API Icu_Kernel_StopChannel */
#endif /* End of ICU_TIMESTAMP_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Icu_Kernel_ResetEdgeCount
**
** Service ID            : None
**
** Description           : This kernel function will check all requests of Icu_ResetEdgeCount API from the satellite 
**                         core, and proceed the request to the internal function Icu_<HWIP>_ResetEdgeCount of 
**                         respective hardware IP.
**
** Sync/Async            : Asynchronous
**
** Re-entrancy           : Reentrant for different channel numbers
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : 1. ICU Driver should be initialized.
**                         2. The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Icu_GblDriverStatus, Icu_GaaResetEdgeCountBuffer, Icu_GpChannelConfig, Icu_GaaHwDepFunc
**
** Functions invoked     : Icu_HW_Atu_ResetEdgeCount, Icu_HW_Taud_ResetEdgeCount, Icu_HW_Tauj_ResetEdgeCount
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_096, ICU_DUD_ACT_096_GBL001, ICU_DUD_ACT_096_GBL002, ICU_DUD_ACT_096_GBL003
** Reference ID          : ICU_DUD_ACT_096_CRT001, ICU_DUD_ACT_096_CRT002, ICU_DUD_ACT_096_CRT003
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_ResetEdgeCount(void)                                                             /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerType;
  /* Declare the variable to loop all edge count ram index */
  VAR(uint8, AUTOMATIC) LucRamIndex;
  /* Declare the variable to hold the channel index */
  VAR(Icu_ChannelType, AUTOMATIC) LddChannelIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check if the kernel isn't running on configured partition */
  if ((Icu_GucKernalCoreId == LucCoreID) && (ICU_INITIALIZED == Icu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Checking if any request from Satellite */
    for(LucRamIndex = 0U; LucRamIndex < ICU_TOTAL_EDGECOUNT_CHANNELS; LucRamIndex++)
    {
      /* If the request is not ongoing by Satellite */
      if(ICU_CHECKINGREQUEST(Icu_GaaResetEdgeCountBuffer[LucRamIndex].blSetRequest))                                    /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the new request is issued */
        if(ICU_UNLOCKEDSTATUS(Icu_GaaResetEdgeCountBuffer[LucRamIndex].blBufferLock))                                   /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          ICU_LOCKPROCESS(Icu_GaaResetEdgeCountBuffer[LucRamIndex].blBufferLock);                                       /* PRQA S 3432 # JV-01 */
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
          /* Read the channel index */
          LddChannelIndex = Icu_GaaResetEdgeCountBuffer[LucRamIndex].lddChannel;
          /* Read the Timer Type for the given channel */
          LucTimerType = Icu_GpChannelConfig[LddChannelIndex].ucIcuChannelType;
          /* Check against null pointer */
          if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pResetEdgeCount)                                              /* PRQA S 3416 # JV-01 */
          {
            /* Invoke low-level driver for initializing the hardware */
            Icu_GaaHwDepFunc[LucTimerType]->pResetEdgeCount(LddChannelIndex);
          } /* else No action required */
          /* Clean request */
          Icu_GaaResetEdgeCountBuffer[LucRamIndex].blSetRequest = ICU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          ICU_UNLOCKPROCESS(Icu_GaaResetEdgeCountBuffer[LucRamIndex].blBufferLock);                                     /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    } /* End of E_OK == LddReturnValue */
  } /* End of ICU_INITIALIZED == Icu_GblDriverStatus */
} /* End of API Icu_SetPinState */
#endif /* End of ICU_SET_PIN_STATE_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Icu_Kernel_EnableEdgeCount
**
** Service ID            : None
**
** Description           : This kernel function will check all requests of Icu_EnableEdgeCount API from the satellite 
**                         core, and proceed the request to the internal function Icu_<HWIP>_EnableEdgeCount of 
**                         respective hardware IP.
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
** Preconditions         : Icu_Init must be called before this function and
**                         The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Icu_GblDriverStatus, Icu_GaaEnableEdgeCountBuffer, Icu_GpChannelConfig
**                         Icu_GaaHwDepFunc, Icu_GpChannelRamData
**
** Functions invoked     : Icu_HW_Atu_StartCountMeasurement,
**                         Icu_HW_Taud_StartCountMeasurement, Icu_HW_Tauj_StartCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_097, ICU_DUD_ACT_097_GBL001, ICU_DUD_ACT_097_GBL002, ICU_DUD_ACT_097_GBL003
** Reference ID          : ICU_DUD_ACT_097_GBL004, ICU_DUD_ACT_097_CRT001, ICU_DUD_ACT_097_CRT002,ICU_DUD_ACT_097_CRT003
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_EnableEdgeCount(void)                                                            /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerType;
  /* Declare the variable to loop all edge count ram index */
  VAR(uint8, AUTOMATIC) LucRamIndex;
  /* Declare the variable to hold the channel index */
  VAR(Icu_ChannelType, AUTOMATIC) LddChannelIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check if the kernel isn't running on configured partition */
  if ((Icu_GucKernalCoreId == LucCoreID) && (ICU_INITIALIZED == Icu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Checking if any request from Satellite */
    for(LucRamIndex = 0U; LucRamIndex < ICU_TOTAL_EDGECOUNT_CHANNELS; LucRamIndex++)
    {
      /* If the request is not ongoing by Satellite */
      if(ICU_CHECKINGREQUEST(Icu_GaaEnableEdgeCountBuffer[LucRamIndex].blSetRequest))                                   /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the new request is issued */
        if(ICU_UNLOCKEDSTATUS(Icu_GaaEnableEdgeCountBuffer[LucRamIndex].blBufferLock))                                  /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          ICU_LOCKPROCESS(Icu_GaaEnableEdgeCountBuffer[LucRamIndex].blBufferLock);                                      /* PRQA S 3432 # JV-01 */
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
          /* Read the channel index */
          LddChannelIndex = Icu_GaaEnableEdgeCountBuffer[LucRamIndex].lddChannel;
          /* Read the Timer Type for the given channel */
          LucTimerType = Icu_GpChannelConfig[LddChannelIndex].ucIcuChannelType;
          /* Check against null pointer */
          if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pStartCountMeasurement)                                       /* PRQA S 3416 # JV-01 */
          {
            Icu_GaaHwDepFunc[LucTimerType]->pStartCountMeasurement(LddChannelIndex);
          } /* else No action required */
          /* Initialize the channel status as active */
          Icu_GpChannelRamData[LddChannelIndex].ucChannelStatus = (uint8)ICU_ACTIVE;
          /* Clean request */
          Icu_GaaEnableEdgeCountBuffer[LucRamIndex].blSetRequest = ICU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          ICU_UNLOCKPROCESS(Icu_GaaEnableEdgeCountBuffer[LucRamIndex].blBufferLock);                                    /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    } /* End of looping all channels */
  } /* End of ICU_INITIALIZED == Icu_GblDriverStatus */
} /* End of API Icu_SetPinAction */
#endif /* End of ICU_EDGE_COUNT_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Icu_Kernel_DisableEdgeCount
**
** Service ID            : None
**
** Description           : This kernel function will check all requests of Icu_DisableEdgeCount API from the satellite 
**                         core, and proceed the request to the internal function Icu_<HWIP>_DisableEdgeCount of 
**                         respective hardware IP.
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
** Preconditions         : Icu_Init must be called before this function and
**                         The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Icu_GblDriverStatus, Icu_GaaDisableEdgeCountBuffer, Icu_GpChannelConfig
**                         Icu_GaaHwDepFunc, Icu_GpChannelRamData
**
** Functions invoked     : Icu_HW_Taud_StopCountMeasurement,
**                         Icu_HW_Tauj_StopCountMeasurement, Icu_HW_Atu_StopCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_098, ICU_DUD_ACT_098_GBL001, ICU_DUD_ACT_098_GBL002, ICU_DUD_ACT_098_GBL003
** Reference ID          : ICU_DUD_ACT_098_GBL004, ICU_DUD_ACT_098_CRT001, ICU_DUD_ACT_098_CRT002,ICU_DUD_ACT_098_CRT003
***********************************************************************************************************************/
#if (ICU_EDGE_COUNT_API == STD_ON)
FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_DisableEdgeCount(void)                                                           /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerType;
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucRamIndex;
  /* Declare the variable to hold the channel index */
  VAR(Icu_ChannelType, AUTOMATIC) LddChannelIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check if the kernel isn't running on configured partition */
  if ((Icu_GucKernalCoreId == LucCoreID) && (ICU_INITIALIZED == Icu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Checking if any request from Satellite */
    for(LucRamIndex = 0U; LucRamIndex < ICU_TOTAL_EDGECOUNT_CHANNELS; LucRamIndex++)
    {
      /* If the request is not ongoing by Satellite */
      if(ICU_CHECKINGREQUEST(Icu_GaaDisableEdgeCountBuffer[LucRamIndex].blSetRequest))                                  /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the new request is issued */
        if(ICU_UNLOCKEDSTATUS(Icu_GaaDisableEdgeCountBuffer[LucRamIndex].blBufferLock))                                 /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          ICU_LOCKPROCESS(Icu_GaaDisableEdgeCountBuffer[LucRamIndex].blBufferLock);                                     /* PRQA S 3432 # JV-01 */
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
          /* Read the channel index */
          LddChannelIndex = Icu_GaaDisableEdgeCountBuffer[LucRamIndex].lddChannel;
          /* Read the Timer Type for the given channel */
          LucTimerType = Icu_GpChannelConfig[LddChannelIndex].ucIcuChannelType;
          /* Invoke the Low-Level Driver for disabling the edge count */
          if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pStopCountMeasurement)                                        /* PRQA S 3416 # JV-01 */
          {
            Icu_GaaHwDepFunc[LucTimerType]->pStopCountMeasurement(LddChannelIndex);
          } /* else No action required */
          /* Initialize the channel status as idle */
          Icu_GpChannelRamData[LddChannelIndex].ucChannelStatus = (uint8)ICU_IDLE;
          /* Clean request */
          Icu_GaaDisableEdgeCountBuffer[LucRamIndex].blSetRequest = ICU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          ICU_UNLOCKPROCESS(Icu_GaaDisableEdgeCountBuffer[LucRamIndex].blBufferLock);                                   /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    } /* End of looping all channels */
  } /* End of ICU_INITIALIZED == Icu_GblDriverStatus */
} /* End of API Icu_SetAbsoluteThreshold */
#endif /* End of ICU_EDGE_COUNT_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Icu_Kernel_EnableEdgeDetection
**
** Service ID            : None
**
** Description           : This kernel function will check all requests of Icu_EnableEdgeDetection API from the  
**                         satellite core, and proceed the request to the internal function  
**                         Icu_<HWIP>_EnableEdgeDetection of respective hardware IP.
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
** Preconditions         : Icu_Init must be called before this function and
**                         The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Icu_GblDriverStatus, Icu_GaaEnableEdgeDetectionBuffer, Icu_GaaHwDepFunc, Icu_GpChannelConfig
**
** Functions invoked     : Icu_HW_Atu_StartCountMeasurement, Icu_HW_Pin_EnableEdgeDetection
**                         Icu_HW_Taud_StartCountMeasurement, Icu_HW_Tauj_StartCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_099, ICU_DUD_ACT_099_GBL001, ICU_DUD_ACT_099_GBL002, ICU_DUD_ACT_099_GBL003
** Reference ID          : ICU_DUD_ACT_099_CRT001, ICU_DUD_ACT_099_CRT002, ICU_DUD_ACT_099_CRT003
***********************************************************************************************************************/
#if (ICU_EDGE_DETECT_API == STD_ON)
FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_EnableEdgeDetection(void)                                                        /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucRamIndex;
  /* Declare the variable to hold the channel index */
  VAR(Icu_ChannelType, AUTOMATIC) LddChannelIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check if the kernel isn't running on configured partition */
  if ((Icu_GucKernalCoreId == LucCoreID) && (ICU_INITIALIZED == Icu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Checking if any request from Satellite */
    for(LucRamIndex = 0U; LucRamIndex < ICU_TOTAL_EDGEDETECT_CHANNELS; LucRamIndex++)
    {
      /* If the request is not ongoing by Satellite */
      if(ICU_CHECKINGREQUEST(Icu_GaaEnableEdgeDetectionBuffer[LucRamIndex].blSetRequest))                               /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the new request is issued */
        if(ICU_UNLOCKEDSTATUS(Icu_GaaEnableEdgeDetectionBuffer[LucRamIndex].blBufferLock))                              /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          ICU_LOCKPROCESS(Icu_GaaEnableEdgeDetectionBuffer[LucRamIndex].blBufferLock);                                  /* PRQA S 3432 # JV-01 */
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
          /* Read the channel index */
          LddChannelIndex = Icu_GaaEnableEdgeDetectionBuffer[LucRamIndex].lddChannel;
          /* Read the Timer Type for the given channel */
          LucHWIPType = Icu_GpChannelConfig[LddChannelIndex].ucIcuChannelType;
          /* Enable the edge Detect for the channel */
          if (NULL_PTR != Icu_GaaHwDepFunc[LucHWIPType]->pStartCountMeasurement)                                        /* PRQA S 3416 # JV-01 */
          {
            Icu_GaaHwDepFunc[LucHWIPType]->pStartCountMeasurement(LddChannelIndex);
          } /* else No action required */
          /* Clean request */
          Icu_GaaEnableEdgeDetectionBuffer[LucRamIndex].blSetRequest = ICU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          ICU_UNLOCKPROCESS(Icu_GaaEnableEdgeDetectionBuffer[LucRamIndex].blBufferLock);                                /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    } /* End of looping all channels */
  } /* End of ICU_INITIALIZED == Icu_GblDriverStatus */
} /* End of API Icu_Kernel_EnableEdgeDetection */
#endif /* End of ICU_EDGE_DETECT_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Icu_Kernel_DisableEdgeDetection
**
** Service ID            : None
**
** Description           : This kernel function will check all requests of Icu_DisableEdgeDetection API from the  
**                         satellite core, and proceed the request to the internal function  
**                         Icu_<HWIP>_DisableEdgeDetection of respective hardware IP.
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
** Preconditions         : Icu_Init must be called before this function and
**                         The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Icu_GblDriverStatus, Icu_GaaDisableEdgeDetectionBuffer, Icu_GaaHwDepFunc,Icu_GpChannelConfig
**
** Functions invoked     : Icu_HW_Atu_StopCountMeasurement, Icu_HW_Pin_DisableEdgeDetection
**                         Icu_HW_Taud_StopCountMeasurement, Icu_HW_Tauj_StopCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_100, ICU_DUD_ACT_100_GBL001, ICU_DUD_ACT_100_GBL002
** Reference ID          : ICU_DUD_ACT_100_CRT001, ICU_DUD_ACT_100_CRT002, ICU_DUD_ACT_100_CRT003
***********************************************************************************************************************/
#if (ICU_EDGE_DETECT_API == STD_ON)
FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_DisableEdgeDetection(void)                                                       /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucHWIPType;
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucRamIndex;
  /* Declare the variable to hold the channel index */
  VAR(Icu_ChannelType, AUTOMATIC) LddChannelIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check if the kernel isn't running on configured partition */
  if ((Icu_GucKernalCoreId == LucCoreID) && (ICU_INITIALIZED == Icu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Checking if any request from Satellite */
    for(LucRamIndex = 0U; LucRamIndex < ICU_TOTAL_EDGEDETECT_CHANNELS; LucRamIndex++)
    {
      /* If the request is not ongoing by Satellite */
      if(ICU_CHECKINGREQUEST(Icu_GaaDisableEdgeDetectionBuffer[LucRamIndex].blSetRequest))                              /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the new request is issued */
        if(ICU_UNLOCKEDSTATUS(Icu_GaaDisableEdgeDetectionBuffer[LucRamIndex].blBufferLock))                             /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          ICU_LOCKPROCESS(Icu_GaaDisableEdgeDetectionBuffer[LucRamIndex].blBufferLock);                                 /* PRQA S 3432 # JV-01 */
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
          /* Read the channel index */
          LddChannelIndex = Icu_GaaDisableEdgeDetectionBuffer[LucRamIndex].lddChannel;
          /* Read the Timer Type for the given channel */
          LucHWIPType = Icu_GpChannelConfig[LddChannelIndex].ucIcuChannelType;
          /* Enable the edge Detect for the channel */
          if (NULL_PTR != Icu_GaaHwDepFunc[LucHWIPType]->pStopCountMeasurement)                                         /* PRQA S 3416 # JV-01 */
          {
            Icu_GaaHwDepFunc[LucHWIPType]->pStopCountMeasurement(LddChannelIndex);
          } /* else No action required */
          /* Clean request */
          Icu_GaaDisableEdgeDetectionBuffer[LucRamIndex].blSetRequest = ICU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          ICU_UNLOCKPROCESS(Icu_GaaDisableEdgeDetectionBuffer[LucRamIndex].blBufferLock);                               /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    } /* End of looping all channels */
  } /* End of ICU_INITIALIZED == Icu_GblDriverStatus */
} /* End of API Icu_SetAbsoluteThreshold */
#endif /* End of ICU_EDGE_COUNT_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Icu_Kernel_StartSignalMeasurement
**
** Service ID            : None
**
** Description           : This kernel function will check all requests of Icu_StartSignalMeasurement API from the  
**                         satellite core, and proceed the request to the internal function  
**                         Icu_<HWIP>_StartSignalMeasurement of respective hardware IP.
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
** Preconditions         : Icu_Init must be called before this function and
**                         The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Icu_GblDriverStatus, Icu_GaaStartSignalMeasurementBuffer, Icu_GpChannelRamData
**                         Icu_GpChannelConfig, Icu_GpChannelUserRegConfig, Icu_GaaHwDepFunc
**
** Functions invoked     : Icu_HW_Atu_StartCountMeasurement,
**                         Icu_HW_Taud_StartCountMeasurement, Icu_HW_Tauj_StartCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_101, ICU_DUD_ACT_101_GBL001, ICU_DUD_ACT_101_GBL002
** Reference ID          : ICU_DUD_ACT_101_GBL003, ICU_DUD_ACT_101_GBL004
** Reference ID          : ICU_DUD_ACT_101_CRT001, ICU_DUD_ACT_101_CRT002
** Reference ID          : ICU_DUD_ACT_101_CRT003, ICU_DUD_ACT_101_CRT004, ICU_DUD_ACT_101_CRT005
***********************************************************************************************************************/
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_StartSignalMeasurement(void)                                                     /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerType;
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LucRamIndex;
  /* Declare the variable to hold the channel index */
  VAR(Icu_ChannelType, AUTOMATIC) LddChannelIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check if the kernel isn't running on configured partition */
  if ((Icu_GucKernalCoreId == LucCoreID) && (ICU_INITIALIZED == Icu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Checking if any request from Satellite */
    for(LucRamIndex = 0U; LucRamIndex < ICU_TOTAL_SIGNALMEASUREMENT_CHANNELS; LucRamIndex++)
    {
      /* If the request is not ongoing by Satellite */
      if(ICU_CHECKINGREQUEST(Icu_GaaStartSignalMeasurementBuffer[LucRamIndex].blSetRequest))                            /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the new request is issued */
        if(ICU_UNLOCKEDSTATUS(Icu_GaaStartSignalMeasurementBuffer[LucRamIndex].blBufferLock))                           /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          ICU_LOCKPROCESS(Icu_GaaStartSignalMeasurementBuffer[LucRamIndex].blBufferLock);                               /* PRQA S 3432 # JV-01 */
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
          /* Read the channel index */
          LddChannelIndex = Icu_GaaStartSignalMeasurementBuffer[LucRamIndex].lddChannel;
          /* Read the Timer Type for the given channel  */
          LucTimerType = Icu_GpChannelConfig[LddChannelIndex].ucIcuChannelType;
          /* Start count measurement for the channel */
          if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pStartCountMeasurement)                                       /* PRQA S 3416 # JV-01 */
          {
            Icu_GaaHwDepFunc[LucTimerType]->pStartCountMeasurement(LddChannelIndex);
          } /* else No action required */
          /* Get the spinlock since ucChannelStatus and blResultComplete be updated by satellite core */
          ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);

          /* Initialize channel status as idle */
          Icu_GpChannelRamData[LddChannelIndex].ucChannelStatus = (uint8)ICU_IDLE;

          /* Set result status is FALSE for channel */
          Icu_GpChannelRamData[LddChannelIndex].blResultComplete = ICU_FALSE;

          /* If the channel is duty cycle channel, set result status is FALSE for extra channel */
          if (((uint8)(Icu_GpChannelUserRegConfig[LddChannelIndex].ucChannelProperties &                                /* PRQA S 3416 # JV-01 */
                                                    ICU_DUTY_PERIOD_ENABLED_MASK)) == ICU_DUTY_PERIOD_ENABLED_MASK)
          {
            /* Set result status is FALSE for extra channel */
            Icu_GpChannelRamData[LddChannelIndex + ICU_ONE].blResultComplete = ICU_FALSE;
          } /* else No action required */
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
          /* Clean request */
          Icu_GaaStartSignalMeasurementBuffer[LucRamIndex].blSetRequest = ICU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          ICU_UNLOCKPROCESS(Icu_GaaStartSignalMeasurementBuffer[LucRamIndex].blBufferLock);                             /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    } /* End of looping all channels */
  } /* End of ICU_INITIALIZED == Icu_GblDriverStatus */
} /* End of API Icu_Kernel_StartSignalMeasurement */
#endif /* End of ICU_SIGNAL_MEASUREMENT_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Icu_Kernel_StopSignalMeasurement
**
** Service ID            : None
**
** Description           : This kernel function will check all requests of Icu_StopSignalMeasurement API from the  
**                         satellite core, and proceed the request to the internal function  
**                         Icu_<HWIP>_StopSignalMeasurement of respective hardware IP.
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
** Preconditions         : Icu_Init must be called before this function and
**                         The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Icu_GblDriverStatus, Icu_GaaStopSignalMeasurementBuffer,Icu_GaaHwDepFunc,Icu_GpChannelConfig
**
** Functions invoked     : Icu_HW_Atu_StopCountMeasurement,
**                         Icu_HW_Taud_StopCountMeasurement, Icu_HW_Tauj_StopCountMeasurement
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_102, ICU_DUD_ACT_102_GBL001, ICU_DUD_ACT_102_GBL002, ICU_DUD_ACT_102_GBL003
** Reference ID          : ICU_DUD_ACT_102_CRT001, ICU_DUD_ACT_102_CRT002, ICU_DUD_ACT_102_CRT003
***********************************************************************************************************************/
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_StopSignalMeasurement(void)                                                      /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerType;
  /* Declare the variable to loop all signal measurement index */
  VAR(uint8, AUTOMATIC) LucRamIndex;
  /* Declare the variable to hold the channel index */
  VAR(Icu_ChannelType, AUTOMATIC) LddChannelIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check if the kernel isn't running on configured partition */
  if ((Icu_GucKernalCoreId == LucCoreID) && (ICU_INITIALIZED == Icu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Checking if any request from Satellite */
    for(LucRamIndex = 0U; LucRamIndex < ICU_TOTAL_SIGNALMEASUREMENT_CHANNELS; LucRamIndex++)
    {
      /* If the request is not ongoing by Satellite */
      if(ICU_CHECKINGREQUEST(Icu_GaaStopSignalMeasurementBuffer[LucRamIndex].blSetRequest))                             /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the new request is issued */
        if(ICU_UNLOCKEDSTATUS(Icu_GaaStopSignalMeasurementBuffer[LucRamIndex].blBufferLock))                            /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          ICU_LOCKPROCESS(Icu_GaaStopSignalMeasurementBuffer[LucRamIndex].blBufferLock);                                /* PRQA S 3432 # JV-01 */
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
          /* Read the channel index */
          LddChannelIndex = Icu_GaaStopSignalMeasurementBuffer[LucRamIndex].lddChannel;
          /* Read the Timer Type for the given channel */
          LucTimerType = Icu_GpChannelConfig[LddChannelIndex].ucIcuChannelType;
          /* Stop count measurement for the channel */
          if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pStopCountMeasurement)                                        /* PRQA S 3416 # JV-01 */
          {
            Icu_GaaHwDepFunc[LucTimerType]->pStopCountMeasurement(LddChannelIndex);
          } /* else No action required */
          /* Clean request */
          Icu_GaaStopSignalMeasurementBuffer[LucRamIndex].blSetRequest = ICU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          ICU_UNLOCKPROCESS(Icu_GaaStopSignalMeasurementBuffer[LucRamIndex].blBufferLock);                              /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    } /* End of looping all channels */
  } /* End of ICU_INITIALIZED == Icu_GblDriverStatus */
} /* End of API Icu_SetAbsoluteThreshold */
#endif /* End of ICU_SIGNAL_MEASUREMENT_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : Icu_Kernel_SetActivationCondition
**
** Service ID            : None
**
** Description           : This kernel function will check all requests of Icu_SetActivationCondition API from the  
**                         satellite core, and proceed the request to the internal function  
**                         Icu_<HWIP>_SetActivationCondition of respective hardware IP.
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
** Preconditions         : Icu_Init must be called before this function and
**                         The Kernel is a scheduled function, which will be mapped to a period task
**
** Global Variables      : Icu_GblDriverStatus, Icu_GaaSetActivationConditionBuffer
**                         Icu_GaaHwDepFunc, Icu_GpChannelConfig
**
** Functions invoked     : Icu_HW_Taud_SetActivation, Icu_HW_Tauj_SetActivation,
**                         Icu_HW_Atu_SetActivation, Icu_HW_Pin_SetActivation
**
** Registers Used        : None
**
** Reference ID          : ICU_DUD_ACT_103, ICU_DUD_ACT_103_GBL001, ICU_DUD_ACT_103_GBL002, ICU_DUD_ACT_103_GBL003
** Reference ID          : ICU_DUD_ACT_103_CRT001, ICU_DUD_ACT_103_CRT002
** Reference ID          : ICU_DUD_ACT_103_CRT003, ICU_DUD_ACT_103_CRT004, ICU_DUD_ACT_103_CRT005 
***********************************************************************************************************************/
FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_SetActivationCondition(void)                                                     /* PRQA S 1503 # JV-01 */
{
  /* Declare a Local variable to Timer Type */
  VAR(volatile uint8, AUTOMATIC) LucTimerType;
  /* Declare the variable to loop all configured channels */
  VAR(uint8, AUTOMATIC) LddChannelIndex;
  /* Declare a Local variable for the current core ID */
  VAR(volatile uint8, AUTOMATIC) LucCoreID;
  /* Get the current core ID by OS service */
  LucCoreID = (uint8)GetCoreID();
  /* Check if the kernel isn't running on configured partition */
  if ((Icu_GucKernalCoreId == LucCoreID) && (ICU_INITIALIZED == Icu_GblDriverStatus))                                   /* PRQA S 3415, 3416 # JV-01, JV-01 */
  {
    /* Checking if any request from Satellite */
    for(LddChannelIndex = 0U; LddChannelIndex < ICU_MAX_CHANNEL; LddChannelIndex++)
    {
      /* If the request is not ongoing by Satellite */
      if(ICU_CHECKINGREQUEST(Icu_GaaSetActivationConditionBuffer[LddChannelIndex].blSetRequest))                        /* PRQA S 3432 # JV-01 */
      {
        /* Get the spinlock */
        ICU_ENTER_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        /* If the new request is issued */
        if(ICU_UNLOCKEDSTATUS(Icu_GaaSetActivationConditionBuffer[LddChannelIndex].blBufferLock))                       /* PRQA S 3432 # JV-01 */
        {
          /* Lock processing - notify that master is proceeded the request */
          ICU_LOCKPROCESS(Icu_GaaSetActivationConditionBuffer[LddChannelIndex].blBufferLock);                           /* PRQA S 3432 # JV-01 */
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
          /* Read the Unit Type for the given unit */
          LucTimerType = Icu_GpChannelConfig[LddChannelIndex].ucIcuChannelType;
          /* Set the activation edge value */
          if (NULL_PTR != Icu_GaaHwDepFunc[LucTimerType]->pSetActivation)                                               /* PRQA S 3416 # JV-01 */
          {
            /* Get the spinlock */
            ICU_ENTER_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
            /* Invoked lower layer function */
            Icu_GaaHwDepFunc[LucTimerType]->pSetActivation(LddChannelIndex,                                             /* PRQA S 0404 # JV-01 */
                                                  Icu_GaaSetActivationConditionBuffer[LddChannelIndex].lddActivation);
            /* Release the spinlock */
            ICU_EXIT_CRITICAL_SECTION(ICU_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
          } /* else No action required */
          /* Clean request */
          Icu_GaaSetActivationConditionBuffer[LddChannelIndex].blSetRequest = ICU_FALSE;
          /* Lock processing - notify that master is proceeded the request */
          ICU_UNLOCKPROCESS(Icu_GaaSetActivationConditionBuffer[LddChannelIndex].blBufferLock);                         /* PRQA S 3432 # JV-01 */
        }
        else
        {
          /* Release the spinlock */
          ICU_EXIT_CRITICAL_SECTION(ICU_RAM_DATA_PROTECTION_GLOBAL);
        } /* end of Check if the buffer is locked */
      } /* else No action required */
    } /* End of looping all channels */
  }  /* End of ICU_INITIALIZED == Icu_GblDriverStatus */
} /* End of API Icu_SetActivationCondition */

#define ICU_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */
#endif /* ICU_MULTI_CORE_SUPPORT == STD_ON */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
