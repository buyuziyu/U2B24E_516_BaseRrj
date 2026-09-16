/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Ocu_GTM_LLDriver.h                                                                                  */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.                                                     */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of OCU Driver                                                                         */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.4.0: 30/05/2025 : Initial Version.
 */
/**********************************************************************************************************************/
#ifndef OCU_GTM_LLDRIVER_H
#define OCU_GTM_LLDRIVER_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/* Included for Type of Ocu_ChannelType and Ocu_ValueType */
#include "Ocu_Cfg.h"
/* Included for OCU module-specific definitions */
#include "Ocu_Types.h"
#include "Ocu_GTM_PBTypes.h"
/* Included for macro definitions (e.g. Service IDs)*/
#include "Ocu.h"
/* Included for RAM variable declarations */
#include "Ocu_Ram.h"
#include "Ocu_GTM_Ram.h"
#if (OCU_INTERRUPT_CONSISTENCY_CHECK == STD_ON)
#include "Dem.h"
#endif
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define OCU_GTM_LLDRIVER_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION
#define OCU_GTM_LLDRIVER_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION
#define OCU_GTM_LLDRIVER_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION

/*  Module software version information */
#define OCU_GTM_LLDRIVER_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION
#define OCU_GTM_LLDRIVER_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION
#define OCU_GTM_LLDRIVER_SW_PATCH_VERSION            OCU_SW_PATCH_VERSION
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#if(OCU_TIMER_IP_GTM == STD_ON)
#define OCU_START_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"
#if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
extern FUNC(void, OCU_PRIVATE_CODE)
                                Ocu_HW_Gtm_AtomTbuInit(P2CONST(Ocu_ConfigType, AUTOMATIC, OCU_APPL_CONST)LpConfigPtr);
#endif
extern FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_ChannelInit(Ocu_ChannelType LddChannel);
#if (OCU_DE_INIT_API == STD_ON)
extern FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_ChannelDeInit(Ocu_ChannelType LddChannel);
#if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
extern FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_UnitDeInit(void);
#endif
#endif
extern FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_StopChannel(Ocu_ChannelType LddChannel);
#if (OCU_SET_PIN_STATE_API == STD_ON)
extern FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_SetPinState(Ocu_ChannelType LddChannel, Ocu_PinStateType LddPinState);
#endif
#if (((OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)) \
                                                                                || (OCU_GET_COUNTER_API == STD_ON))
extern FUNC(Ocu_ValueType, OCU_PRIVATE_CODE) Ocu_HW_Gtm_GetCounter(Ocu_ChannelType LddChannel);
#endif
#if ((OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON))
extern FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_SetThreshold(Ocu_ChannelType LddChannel,
                                                                                    Ocu_ValueType LddSwThresholdValue);
#endif
extern FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_EnableInterrupt(Ocu_ChannelType LddChannel);
extern FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_DisableInterrupt(Ocu_ChannelType LddChannel);

FUNC(void, OCU_CODE_FAST) Ocu_HW_Gtm_StartRestartChannel(Ocu_ChannelType LddChannel, Ocu_ValueType LddHwNewThreshold);

#if (OCU_GTM_TBU_ATOM_SOMB_USED == STD_ON)
FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_CalCyclicEvent(Ocu_ChannelType LddChannel, Ocu_ValueType LddThresholdVal);
FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_SetCyclicEvent(Ocu_ChannelType LddChannel);
FUNC(uint32, OCU_PRIVATE_CODE) Ocu_HW_Gtm_GetTbuCounterVal(Ocu_ChannelType LddChannel);
#if (OCU_SET_PIN_ACTION_API == STD_ON)
FUNC(void, OCU_PRIVATE_CODE) Ocu_HW_Gtm_SetCyclicPinAction(Ocu_ChannelType LddChannel, Ocu_PinActionType LddPinAction);
#endif
#endif

#define OCU_STOP_SEC_PRIVATE_CODE
#include "Ocu_MemMap.h"

#define OCU_START_SEC_CODE_FAST
#include "Ocu_MemMap.h"
extern FUNC(void, OCU_CODE_FAST) Ocu_HW_Gtm_CbkNotification(uint8 LucChannelIdx);
#define OCU_STOP_SEC_CODE_FAST
#include "Ocu_MemMap.h"

#endif /* OCU_GTM_ATOM_USED, OCU_GTM_TOM_USED */
#endif  /* OCU_GTM_LLDRIVER_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
