/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu_Kernel.h                                                                                        */
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
 *  1.4.0  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01
 *  1.3.1  31/03/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 and RH850/U2Bx-E MCAL Ver22.00.02 Release
 *  1.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  1.0.1  23/10/2023  : Change from OCU_AR_RELEASE_MAJOR_VERSION_VALUE to OCU_AR_RELEASE_MAJOR_VERSION
                         Change from OCU_AR_RELEASE_MINOR_VERSION_VALUE to OCU_AR_RELEASE_MINOR_VERSION
                         Change from OCU_AR_RELEASE_REVISION_VERSION_VALUE to OCU_AR_RELEASE_REVISION_VERSION
                         Add new QAC messages 1534, 1536
           25/09/2023  : Update brand condition in function macro OCU_UNLOCKEDSTATUS, OCU_CHECKINGREQUEST
                         Remove macro OCU_LOCKEDSTATUS
                         Reason: Coding rule
 *  1.0.0  04/04/2023  : Initial Version
 */
/**********************************************************************************************************************/
#ifndef OCU_KERNEL_H
#define OCU_KERNEL_H
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define OCU_KERNEL_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION
#define OCU_KERNEL_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION
#define OCU_KERNEL_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define OCU_KERNEL_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION
#define OCU_KERNEL_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION
#define OCU_KERNEL_SW_PATCH_VERSION            OCU_SW_PATCH_VERSION
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#if (OCU_MULTI_CORE_SUPPORT == STD_ON)
/* Satellite service */
#define OCU_UNLOCKEDSTATUS(x)                  (OCU_FALSE == x)

/* Master serivce */
#define OCU_CHECKINGREQUEST(x)                 (OCU_TRUE == x)
#define OCU_LOCKPROCESS(x)                     (x = OCU_TRUE)
#define OCU_UNLOCKPROCESS(x)                   (x = OCU_FALSE)

/* Type definition for Request from Ocu_StartChannel, Ocu_StopChannel */
typedef struct Stag_Ocu_Channel_RequestType
{
    /* Satellite request */
    boolean blSetRequest;
    /* Status of locking the buffer */
    boolean blBufferLock;
} Ocu_Channel_RequestType;

#if (OCU_SET_PIN_STATE_API == STD_ON)
/* Type definition for Request from Ocu_SetPinState */
typedef struct Stag_Ocu_SetPinState_RequestType
{
    /* storing value of request from Ocu_SetPinState (Ocu_PinStateType Type) */
    Ocu_PinStateType lddPinState;
    /* Satellite request */
    boolean blSetRequest;
    /* Status of locking the buffer */
    boolean blBufferLock;
} Ocu_SetPinState_RequestType;
#endif

#if (OCU_SET_PIN_ACTION_API == STD_ON)
/* Type definition for Request from Ocu_SetPinAction */
typedef struct Stag_Ocu_SetPinAction_RequestType
{
    /* storing value of request from Ocu_SetPinAction (Ocu_PinActionType Type) */
    Ocu_PinActionType lddPinAction;
    /* Satellite request */
    boolean blSetRequest;
    /* Status of locking the buffer */
    boolean blBufferLock;
} Ocu_SetPinAction_RequestType;
#endif

#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
/* Type definition for Request from Ocu_SetAbsoluteThreshold */
typedef struct Stag_Ocu_SetAbsoluteThreshold_RequestType
{
    /* Storing the new SW threshold value */
    Ocu_ValueType lddSwAbsoluteValue;
    /* Satellite request */
    boolean blSetRequest;
    /* Status of locking the buffer */
    boolean blBufferLock;
    /* The current counter value after setting the threshold */
    Ocu_ValueType lddSwCounterValue;
} Ocu_SetAbsoluteThreshold_RequestType;
#endif

#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
/* Type definition for Request from Ocu_SetRelativeThreshold */
typedef struct Stag_Ocu_SetRelativeThreshold_RequestType
{
    /* Storing the new SW threshold value */
    Ocu_ValueType lddSwRelativeValue;
    /* Satellite request */
    boolean blSetRequest;
    /* Status of locking the buffer */
    boolean blBufferLock;
    /* The current counter value after setting the threshold */
    Ocu_ValueType lddSwCounterValue;
    /* The sw reference value */
    Ocu_ValueType lddSwReferenceValue;
    /* The sw threshold value */
    Ocu_ValueType lddSwThresholdValue;
} Ocu_SetRelativeThreshold_RequestType;
#endif

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
/* Globale scope - share among cores */
#define OCU_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Ocu_MemMap.h"

/* Start and stop channel request */
extern volatile VAR(Ocu_Channel_RequestType, OCU_VAR_NO_INIT) Ocu_GaaStartChannelBuffer[OCU_TOTAL_CHANNELS_CONFIG];
extern volatile VAR(Ocu_Channel_RequestType, OCU_VAR_NO_INIT) Ocu_GaaStopChannelBuffer[OCU_TOTAL_CHANNELS_CONFIG];

/* Set pin state request */
#if (OCU_SET_PIN_STATE_API == STD_ON)
extern volatile VAR(Ocu_SetPinState_RequestType, OCU_VAR_NO_INIT) Ocu_GaaSetPinStateBuffer[OCU_TOTAL_CHANNELS_CONFIG];
#endif

/* Set pin action request */
#if (OCU_SET_PIN_ACTION_API == STD_ON)
extern volatile VAR(Ocu_SetPinAction_RequestType, OCU_VAR_NO_INIT)
                                                                 Ocu_GaaSetPinActionBuffer[OCU_TOTAL_CHANNELS_CONFIG];
#endif

/* Set absolute threshold request */
#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
extern volatile VAR(Ocu_SetAbsoluteThreshold_RequestType, OCU_VAR_NO_INIT)
                                                          Ocu_GaaSetAbsoluteThresholdBuffer[OCU_TOTAL_CHANNELS_CONFIG];
#endif

/* Set relative threshold request */
#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
extern volatile VAR(Ocu_SetRelativeThreshold_RequestType, OCU_VAR_NO_INIT)
                                                          Ocu_GaaSetRelativeThresholdBuffer[OCU_TOTAL_CHANNELS_CONFIG];
#endif

#define OCU_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Ocu_MemMap.h"
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#define OCU_START_SEC_PUBLIC_CODE_LOCAL
#include "Ocu_MemMap.h"

/* Kernel API handle request by Ocu_StartChannel */
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_Kernel_StartChannel(void);
/* Kernel API handle request by Ocu_StopChannel */
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_Kernel_StopChannel(void);

/* Kernel API handle request by Ocu_SetPinState */
#if (OCU_SET_PIN_STATE_API == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_Kernel_SetPinState(void);
#endif

/* Kernel API handle request by Ocu_SetPinAction */
#if (OCU_SET_PIN_ACTION_API == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_Kernel_SetPinAction(void);
#endif

/* Kernel API handle request by Ocu_SetAbsoluteThreshold and Ocu_SetRelativeThreshold */
#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_Kernel_SetAbsoluteThreshold(void);
#endif

#if  (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_Kernel_SetRelativeThreshold(void);
#endif

#define OCU_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Ocu_MemMap.h"

#endif /* OCU_MULTI_CORE_SUPPORT == STD_ON */
#endif /* Ocu_KERNEL_H */
/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
