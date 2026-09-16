/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Ocu_Types.h                                                                                         */
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
 *  1.3.1  27/02/2025  : As part of QAC message 11.6.0 support, following changes are made:
 *                       1. Remove message 3883
 *                       2. Add message 3884
 *  1.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  1.1.1  30/08/2024  : As part of Multi Variant support, following changes are made:
                         1. Add variable blCountingDirection, ulAsynchonousPollingTimes, ucKernelCoreId to 
                            Ocu_ConfigType type
 *  1.0.1  23/10/2023  : Change from OCU_AR_RELEASE_MAJOR_VERSION_VALUE to OCU_AR_RELEASE_MAJOR_VERSION
                         Change from OCU_AR_RELEASE_MINOR_VERSION_VALUE to OCU_AR_RELEASE_MINOR_VERSION
                         Change from OCU_AR_RELEASE_REVISION_VERSION_VALUE to OCU_AR_RELEASE_REVISION_VERSION
           17/10/2023  : Add new QAC message 1534, 1336 and 1536
 *  1.0.0  04/04/2023  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:1336)    : Parameter identifiers missing in declaration of a function type.                             */
/* Rule                : MISRA C:2012 Rule-8.2, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : Parameter identifiers are  missing however not impact the MCAL operation.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#ifndef OCU_TYPES_H
#define OCU_TYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define OCU_TYPES_AR_RELEASE_MAJOR_VERSION    OCU_AR_RELEASE_MAJOR_VERSION
#define OCU_TYPES_AR_RELEASE_MINOR_VERSION    OCU_AR_RELEASE_MINOR_VERSION
#define OCU_TYPES_AR_RELEASE_REVISION_VERSION OCU_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define OCU_TYPES_SW_MAJOR_VERSION            OCU_SW_MAJOR_VERSION
#define OCU_TYPES_SW_MINOR_VERSION            OCU_SW_MINOR_VERSION
#define OCU_TYPES_SW_PATCH_VERSION            OCU_SW_PATCH_VERSION
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* Numeric identifier of an OCU channel.  */
typedef uint8 Ocu_ChannelType;

/* Type for reading the counter and writing the threshold values (in number of ticks).  */
typedef uint32 Ocu_ValueType;

/* Output state of the pin linked to an OCU channel. */
typedef enum ETag_Ocu_PinStateType
{
  OCU_HIGH,
  OCU_LOW
} Ocu_PinStateType;

/* Return information after setting a new threshold value. */
typedef enum ETag_Ocu_ReturnType
{
  OCU_CM_IN_REF_INTERVAL,
  OCU_CM_OUT_REF_INTERVAL
} Ocu_ReturnType;

/* Automatic action (by hardware) to be performed on a pin attached to an OCU channel. */
typedef enum ETag_Ocu_PinActionType
{
  OCU_SET_HIGH,
  OCU_SET_LOW,
  OCU_TOGGLE,
  OCU_DISABLE
} Ocu_PinActionType;

/***********************************************************************************************************************
**                                        Structure for OCU config information                                        **
***********************************************************************************************************************/
/* Data Structure for OCU required for Initializing the OCU timer unit */
typedef struct STag_Ocu_ConfigType
{

  /* Holds configured counting direction */
  boolean blCountingDirection;
  #if (OCU_MULTI_CORE_SUPPORT == STD_ON)
  /* Hold the configured kernel core ID */
  uint8 ucKernelCoreId;
  /* Hold the polling times for Ocu_StartChannel and Ocu_SetAbsolute/RelativeThreshold */
  uint32 ulAsynchonousPollingTimes;
  #endif /* End of (OCU_ATU_TIMER_UNIT_USED == STD_ON) */
  /* Database start value */
  uint32 ulStartOfDbToc;
  /* Pointer to OCU driver channel configuration */
  P2CONST(void, TYPEDEF, OCU_CONFIG_DATA) pChannelConfig;
  /* Pointer to address internal RAM data */
  P2VAR(void, TYPEDEF, OCU_CONFIG_DATA) pChannelRamData;
  /* Pointer to OCU driver Timer Unit configuration */
  P2CONST(void, TYPEDEF, OCU_CONFIG_DATA) aaTimerUnitConfig[OCU_TOTAL_HW_IP_CONFIG];
} Ocu_ConfigType;

/* Data Structure for OCU required for Initializing the OCU timer unit */
typedef struct STag_Ocu_HWIPType
{
  /* Pointer to OCU driver Timer Unit configuration */
  VAR(uint8, OCU_CONFIG_DATA) ucIndex;
} Ocu_HWIPType;

/* Data Structure for OCU required for Initializing the OCU timer Channel Ram Data */
typedef struct STag_Ocu_ChannelRamDataType                                                                              /* PRQA S 3630 # JV-01 */
{
  /* RAM used to maintain timer status */
  boolean blChannelStatus;
  #if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
  /* RAM used to store Notification status */
  boolean blNotifyStatus;
  #endif
  /* RAM used to maintain channel threshold, this is hardware threshold */
  Ocu_ValueType ddHwLastThreshold;
  #if (OCU_SET_PIN_ACTION_API == STD_ON)
  /* RAM used to maintain channel output action state */
  Ocu_PinActionType ddPinActionState;
  #endif
  /* The need to rewrite the count value for the slave channel data register in the next cycle */
  boolean blRequireRewriteCountValue;
} Ocu_ChannelRamDataType;

/* Data Structure for OCU function Table */
typedef struct STag_Ocu_HwFuncTableType                                                                                 /* PRQA S 3630 # JV-01 */
{
  P2FUNC(void, OCU_PRIVATE_CODE, pHWUnitInit)(const Ocu_ConfigType *);                                                  /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, OCU_PRIVATE_CODE, pHWChannelInit)(Ocu_ChannelType);                                                      /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #if (OCU_DE_INIT_API == STD_ON)
  P2FUNC(void, OCU_PRIVATE_CODE, pHWChannelDeInit)(Ocu_ChannelType);                                                    /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, OCU_PRIVATE_CODE, pHWUnitDeInit)(void);                                                                  /* PRQA S 3432 # JV-01 */
  #endif
  P2FUNC(void, OCU_PRIVATE_CODE, pStartRestartChannel)(Ocu_ChannelType, Ocu_ValueType);                                 /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, OCU_PRIVATE_CODE, pStopChannel)(Ocu_ChannelType);                                                        /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #if (OCU_SET_PIN_STATE_API == STD_ON)
  P2FUNC(void, OCU_PRIVATE_CODE, pSetPinState)(Ocu_ChannelType, Ocu_PinStateType);                                      /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #endif
  #if (OCU_SET_PIN_ACTION_API == STD_ON)
  P2FUNC(void, OCU_PRIVATE_CODE, pSetPinAction)(Ocu_ChannelType, Ocu_PinActionType);                                    /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #endif
  #if (((OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)) \
                                                                                  || (OCU_GET_COUNTER_API == STD_ON))
  P2FUNC(Ocu_ValueType, OCU_PRIVATE_CODE, pGetCounter)(Ocu_ChannelType);                                                /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #endif
  #if ((OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON) || (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON))
  P2FUNC(void, OCU_PRIVATE_CODE, pSetThreshold)(Ocu_ChannelType, Ocu_ValueType);                                        /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #endif
  P2FUNC(void, OCU_PRIVATE_CODE, pEnableInterrupt)(Ocu_ChannelType);                                                    /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, OCU_PRIVATE_CODE, pDisableInterrupt)(Ocu_ChannelType);                                                   /* PRQA S 1336, 3432 # JV-01, JV-01 */
} Ocu_HwFuncTableType;

#endif /* OCU_TYPES_H */
/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
