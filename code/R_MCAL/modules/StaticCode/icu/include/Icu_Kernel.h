/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Icu_Kernel.h                                                                                        */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Database declaration.                                                                                 */
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
 *  2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *  2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2:  31/10/2024  : Update SW-VERSION for Ver22.01.02 Beta2 Release
 *                        As part of support QAC 9.5.0, following changes are made:
 *                        1. Remove QAC messages 1534, 1536.
 *  2.0.1:  20/10/2023  : Add QAC messages 1534, 1536
 *  2.0.0:  04/04/2023  : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ICU_KERNEL_H
#define ICU_KERNEL_H
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define ICU_KERNEL_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION_VALUE
#define ICU_KERNEL_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION_VALUE
#define ICU_KERNEL_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION_VALUE

/* Module Software version information */
#define ICU_KERNEL_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION
#define ICU_KERNEL_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION
#define ICU_KERNEL_SW_PATCH_VERSION            ICU_SW_PATCH_VERSION
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#if (ICU_MULTI_CORE_SUPPORT == STD_ON)
/*
CAT1->Controll API
CAT2->Trigger API
CAT3->Read API
CAT4->Write API

Icu_Init                      CAT1
Icu_DeInit                    CAT1
Icu_SetMode                   CAT1
Icu_DisableWakeup             CAT4
Icu_EnableWakeup              CAT4
Icu_CheckWakeup               CAT1
Icu_SetActivationCondition    CAT2
Icu_DisableNotification       CAT4
Icu_EnableNotification        CAT4
Icu_GetInputState             CAT3
Icu_StartTimestamp            CAT2
Icu_StopTimestamp             CAT2
Icu_GetTimestampIndex         CAT3
Icu_ResetEdgeCount            CAT2
Icu_EnableEdgeCount           CAT2
Icu_DisableEdgeCount          CAT2
Icu_EnableEdgeDetection       CAT2
Icu_DisableEdgeDetection      CAT2
Icu_GetEdgeNumbers            CAT3
Icu_StartSignalMeasurement    CAT2
Icu_StopSignalMeasurement     CAT2
Icu_GetTimeElapsed            CAT3
Icu_GetDutyCycleValues        CAT3
Icu_GetInputLevel             CAT3
Icu_GetTAUInCountValue        CAT3
Icu_GetVersionInfo            Other
*/

/* Satellite service */
#define ICU_LOCKEDSTATUS(x)                    (x == ICU_TRUE)
#define ICU_UNLOCKEDSTATUS(x)                  (x == ICU_FALSE)


/* Master serivce */
#define ICU_CHECKINGREQUEST(x)                 (x == ICU_TRUE)
#define ICU_LOCKPROCESS(x)                     (x =  ICU_TRUE)
#define ICU_UNLOCKPROCESS(x)                   (x =  ICU_FALSE)

/* Type definition for Request from Icu_StopTimestamp, Icu_ResetEdgeCount, Icu_EnableEdgeCount, Icu_DisableEdgeCount
Icu_EnableEdgeDetection, Icu_DisableEdgeDetection, Icu_StartSignalMeasurement, Icu_StopSignalMeasurement */
typedef struct Stag_Icu_Channel_RequestType
{
    /* The channel that send the request */
    Icu_ChannelType lddChannel;
    /* Satellite request */
    boolean blSetRequest;
    /* Status of locking the buffer */
    boolean blBufferLock;
} Icu_Channel_RequestType;

#if (ICU_TIMESTAMP_API == STD_ON)
/* Type definition for Request from Icu_StartTimestamp */
typedef struct Stag_Icu_StartTimestamp_RequestType
{
    /* The channel that send the request */
    Icu_ChannelType lddChannel;
    /* storing value of request from Icu_StartTimestamp (BufferPtr) */
    P2VAR(Icu_ValueType, AUTOMATIC, ICU_APPL_DATA) lpBufferPtr;                                                         /* PRQA S 3432 # JV-01 */
    /* storing value of request from Icu_StartTimestamp (BufferSize) */
    uint16 lusBufferSize;
    /* storing value of request from Icu_StartTimestamp (NotifyInterval) */
    uint16 lusNotifyInterval;
    /* Satellite request */
    boolean blSetRequest;
    /* Status of locking the buffer */
    boolean blBufferLock;
} Icu_StartTimestamp_RequestType;
#endif

/* Type definition for Request from Icu_SetActivationCondition */
typedef struct Stag_Icu_SetActivationCondition_RequestType
{
    /* storing value of request from Icu_SetActivationCondition (Activation) */
    Icu_ActivationType lddActivation;
    /* Satellite request */
    boolean blSetRequest;
    /* Status of locking the buffer */
    boolean blBufferLock;
} Icu_SetActivationCondition_RequestType;


/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
/* Globale scope - share among cores */
#define ICU_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Icu_MemMap.h"

#if (ICU_TIMESTAMP_API == STD_ON)
/* Icu_StartTimestamp request */
extern volatile VAR(Icu_StartTimestamp_RequestType, ICU_VAR_NO_INIT)
                                                             Icu_GaaStartTimestampBuffer[ICU_TOTAL_TIMESTAMP_CHANNELS];
/* Icu_StopTimestamp request */
extern volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT) Icu_GaaStopTimestampBuffer[ICU_TOTAL_TIMESTAMP_CHANNELS];
#endif

#if (ICU_EDGE_COUNT_API == STD_ON)
/* Icu_ResetEdgeCount request */
extern volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT)
                                                        Icu_GaaResetEdgeCountBuffer[ICU_TOTAL_EDGECOUNT_CHANNELS];
/* Icu_EnableEdgeCount request */
extern volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT)
                                                        Icu_GaaEnableEdgeCountBuffer[ICU_TOTAL_EDGECOUNT_CHANNELS];
/* Icu_DisableEdgeCount request */
extern volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT)
                                                        Icu_GaaDisableEdgeCountBuffer[ICU_TOTAL_EDGECOUNT_CHANNELS];
#endif

#if (ICU_EDGE_DETECT_API == STD_ON)
/* Icu_EnableEdgeDetection request */
extern volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT)
                                                    Icu_GaaEnableEdgeDetectionBuffer[ICU_TOTAL_EDGEDETECT_CHANNELS];
/* Icu_DisableEdgeDetection request */
extern volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT)
                                                    Icu_GaaDisableEdgeDetectionBuffer[ICU_TOTAL_EDGEDETECT_CHANNELS];
#endif

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/* Icu_StartSignalMeasurement request */
extern volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT)
                                           Icu_GaaStartSignalMeasurementBuffer[ICU_TOTAL_SIGNALMEASUREMENT_CHANNELS];
/* Icu_StopSignalMeasurement request */
extern volatile VAR(Icu_Channel_RequestType, ICU_VAR_NO_INIT)
                                            Icu_GaaStopSignalMeasurementBuffer[ICU_TOTAL_SIGNALMEASUREMENT_CHANNELS];
#endif

/* Icu_SetActivationCondition request */
extern volatile VAR(Icu_SetActivationCondition_RequestType, ICU_VAR_NO_INIT)
                                                                Icu_GaaSetActivationConditionBuffer[ICU_MAX_CHANNEL];

#define ICU_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Icu_MemMap.h"
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#define ICU_START_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"

/* Kernel API handle request by Icu_SetActivationCondition */
extern FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_SetActivationCondition(void);

/* Kernel API handle request by Icu_StartTimestamp, Icu_StopTimestamp */
#if (ICU_TIMESTAMP_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_StartTimestamp(void);
extern FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_StopTimestamp(void);
#endif

/* Kernel API handle request by Icu_ResetEdgeCount, Icu_EnableEdgeCount, Icu_DisableEdgeCount */
#if (ICU_EDGE_COUNT_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_ResetEdgeCount(void);
extern FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_EnableEdgeCount(void);
extern FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_DisableEdgeCount(void);
#endif

/* Kernel API handle request by Icu_EnableEdgeDetection and Icu_DisableEdgeDetection */
#if (ICU_EDGE_DETECT_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_EnableEdgeDetection(void);
extern FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_DisableEdgeDetection(void);
#endif

/* Kernel API handle request by Icu_StartSignalMeasurement and Icu_StopSignalMeasurement */
#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
extern FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_StartSignalMeasurement(void);
extern FUNC(void, ICU_PUBLIC_CODE) Icu_Kernel_StopSignalMeasurement(void);
#endif

#define ICU_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Icu_MemMap.h"

#endif /* ICU_MULTI_CORE_SUPPORT == STD_ON */
#endif /* ICU_KERNEL_H */
/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
