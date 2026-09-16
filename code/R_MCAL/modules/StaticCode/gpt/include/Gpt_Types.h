/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Gpt_Types.h                                                                                         */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020,2021,2023-2025 Renesas Electronics Corporation. All rights reserved.                                      */
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
 *  2.4.1  30/06/2025  : As part of QAC 11.6.0 support, following changes are made:
 *                       Add QAC message 1039, 3630 from STag_Gpt_HwFuncTableType and aaTimerUnitConfig            
 *  2.4.0  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) release
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02/Ver22.00.02.D Release
 *                       Remove QAC message 1039, 3630 from STag_Gpt_HwFuncTableType and 
 *                       aaTimerUnitConfig
 *  2.3.0  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *  2.1.2  31/10/2024  : As part of Post Build multiple varriant support, following changes are made
 *                       1.Add QAC message 3630
 *                       2.Add parameter ucKernelCoreId and pointer pATUCommonPrescalerConfig in STag_Gpt_ConfigType
 *                       As part of QAC 9.5.0 support, following changes are made
 *                       1.Remove QAC message 1534, 1536
 *  2.0.1  17/10/2023  : Add QAC message 1534, 1536, 1336
 *  2.0.0  25/08/2023  : Remove qac message 3630
 *         26/07/2023  : Remove qac message 0841, GPT_INSTANCE_INDEX, update information of qac message 3432
 *                       Remove pChannelRamData in STag_Gpt_ConfigType, Add CWE QAC header
 *         12/05/2023  : Update SW version 2.0.0
 *  1.3.2  22/08/2021  : Following Changes were made:
 *                       1. Updated header file macro to call file multiple times.
 *                       2. Added QAC message 9.5.0.
 *  1.3.1  02/07/2021  : Added QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 *         15/05/2021  : Fixed Coding Rule and tailor space.
 *  1.2.0  17/07/2020  : Release.
 *  1.1.0  19/06/2020  : Release.
 *         10/03/2020  : As per Redmine #256079, update to add macro
 *                       pre-compile to enable/disable APIs respectively.
 *  1.0.0  01/01/2020  : Initial Version.
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:1039)    : Treating array of length one as potentially flexible member.                                 */
/* Rule                : MISRA C:2012 Dir-1.1, Rule-1.2, CERTCCM DCL38                                                */
/* JV-01 Justification : Use array of length as the final member has no problem by manual reviewing.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
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

#ifndef GPT_TYPES_HEADER
#define GPT_TYPES_HEADER

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type(e.g. STD_ON), Compiler Macros(e.g. P2FUNC), Platform Types(e.g. uint8) */
#include "Std_Types.h"
#if (GPT_TIMER_IP_ATU == STD_ON)
/* Included for using ATU specific defined Type*/
#include "Gpt_ATU_PBTypes.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define GPT_TYPES_AR_RELEASE_MAJOR_VERSION    GPT_AR_RELEASE_MAJOR_VERSION_VALUE
#define GPT_TYPES_AR_RELEASE_MINOR_VERSION    GPT_AR_RELEASE_MINOR_VERSION_VALUE
#define GPT_TYPES_AR_RELEASE_REVISION_VERSION GPT_AR_RELEASE_REVISION_VERSION_VALUE

/* Module Software version information */
#define GPT_TYPES_SW_MAJOR_VERSION            GPT_SW_MAJOR_VERSION
#define GPT_TYPES_SW_MINOR_VERSION            GPT_SW_MINOR_VERSION
#define GPT_TYPES_SW_PATCH_VERSION            GPT_SW_PATCH_VERSION
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* Type describing the timeout value */
typedef uint32 Gpt_ValueType;
/* Type describing the channel ID */
typedef uint8 Gpt_ChannelType;
/* Type describing the GPT modes */
typedef enum ETag_Gpt_ModeType
{
  GPT_MODE_NORMAL,
  GPT_MODE_SLEEP
} Gpt_ModeType;

#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
/* Type describing the GPT Predef Timer */
typedef enum ETag_Gpt_PredefTimerType  
{
  GPT_PREDEF_TIMER_1US_16BIT = 0,
  GPT_PREDEF_TIMER_1US_24BIT,
  GPT_PREDEF_TIMER_1US_32BIT,
  GPT_PREDEF_TIMER_100US_32BIT
} Gpt_PredefTimerType;
#endif

/***********************************************************************************************************************
**                                        Structure for GPT config information                                        **
***********************************************************************************************************************/
/* Data Structure for GPT required for Initializing the GPT timer Channel Ram Data */
typedef struct STag_Gpt_ChannelRamDataType
{
  /* RAM used to maintain timer status */
  uint8 ucChannelStatus;
  #if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
  /* RAM used to store Notification status */
  boolean blNotifyStatus;
  #endif
  #if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  /* RAM used to store Wakeup Notification status */
  boolean blWakeupStatus;
  /* RAM used to store Wakeup occurence status */
  boolean blWakeupOccurrence;
  #endif
} Gpt_ChannelRamDataType;

/* Data Structure for GPT required for Initializing the GPT timer unit */
typedef struct STag_Gpt_ConfigType
{
  /* Database start value */
  uint32 ulStartOfDbToc;
  #if (GPT_MULTI_CORE_SUPPORT == STD_ON)
  /* Value of configured Kernel core ID*/
  uint8 ucKernelCoreId;
  #endif
  /* Pointer to GPT driver channel configuration */
  P2CONST(void, TYPEDEF, GPT_CONFIG_CONST) pChannelConfig;
  #if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
  /* Pointer to Predef timer channel configuration */
  P2CONST(void, TYPEDEF, GPT_CONFIG_DATA) pPredefTimerConfig;
  #endif
  #if (GPT_TIMER_IP_ATU == STD_ON)
  #if (GPT_TOTAL_COMMON_PRESCALER_CONFIGURED != GPT_COMMON_PRESCALER_NOT_USED)
  /* Pointer to ATU Common Prescaler configuration */
  P2CONST(void, TYPEDEF, GPT_CONFIG_DATA) pATUCommonPrescalerConfig;
  #endif
  #endif
  /* Pointer to GPT driver Timer Unit configuration */
  P2CONST(void, TYPEDEF, GPT_CONFIG_DATA) aaTimerUnitConfig[GPT_TOTAL_HW_IP_CONFIG];                                    /* PRQA S 1039 # JV-01 */
} Gpt_ConfigType;

/* Data Structure for GPT required for Initializing the GPT timer unit */
typedef struct STag_Gpt_HWIPType
{
  /* Pointer to GPT driver Timer Unit configuration */
  VAR(uint8, GPT_CONFIG_DATA) ucIndex;
} Gpt_HWIPType;


#if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
/* Data Structure for GPT required for Initializing the GPT Predef Timer Channel */
typedef struct STag_Gpt_PredefTimerConfigType                                                                           /* PRQA S 3630 # JV-01 */
{
  /* Predef Timer tick length/duration Type */
  uint8 ucPredefTimerCounterType;
  /* Timer Type of Predef Timer */
  uint8 ucPredefTimerType;
  /* Pointer to address of Predef Timer Unit config */
  P2CONST(void, TYPEDEF, GPT_CONFIG_DATA) pPT_UnitConfig;
  /* Pointer to address of Predef Timer Channel config */
  P2CONST(void, TYPEDEF, GPT_CONFIG_DATA) pPT_ChannelConfig;
} Gpt_PredefTimerConfigType;
#endif

/* Data Structure for GPT function Table */
typedef struct STag_Gpt_HwFuncTableType                                                                                 /* PRQA S 3630 # JV-01 */
{
  P2FUNC(void, GPT_PRIVATE_CODE, pHWUnitInit)(const Gpt_ConfigType *);                                                  /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, GPT_PRIVATE_CODE, pHWChannelInit)(Gpt_ChannelType);                                                      /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #if (GPT_DE_INIT_API == STD_ON)
  P2FUNC(void, GPT_PRIVATE_CODE, pHWUnitDeInit)(void);                                                                  /* PRQA S 3432 # JV-01 */
  P2FUNC(void, GPT_PRIVATE_CODE, pHWChannelDeInit)(Gpt_ChannelType);                                                    /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #endif
  #if (GPT_TIME_ELAPSED_API == STD_ON)
  P2FUNC(Gpt_ValueType, GPT_PRIVATE_CODE, pGetTimeElapsed)(Gpt_ChannelType);                                            /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #endif
  #if (GPT_TIME_REMAINING_API == STD_ON)
  P2FUNC(Gpt_ValueType, GPT_PRIVATE_CODE, pGetTimeRemaining)(Gpt_ChannelType);                                          /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #endif
  P2FUNC(void, GPT_PRIVATE_CODE, pStartTimer)(Gpt_ChannelType, Gpt_ValueType);                                          /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, GPT_PRIVATE_CODE, pStopTimer)(Gpt_ChannelType);                                                          /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, GPT_PRIVATE_CODE, pEnableInterrupt)(Gpt_ChannelType);                                                    /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, GPT_PRIVATE_CODE, pDisableInterrupt)(Gpt_ChannelType);                                                   /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON) && (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
  P2FUNC(void, GPT_PRIVATE_CODE, pEnableWakeup)(Gpt_ChannelType);                                                       /* PRQA S 1336, 3432 # JV-01, JV-01 */
  P2FUNC(void, GPT_PRIVATE_CODE, pDisableWakeup)(Gpt_ChannelType);                                                      /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #endif
  #if (GPT_GET_PREDEF_TIMER_VALUE_API == STD_ON)
  P2FUNC(void, GPT_PRIVATE_CODE, pStartPredefTimer)(void);                                                              /* PRQA S 3432 # JV-01 */
  P2FUNC(void, GPT_PRIVATE_CODE, pStopPredefTimer)(void);                                                               /* PRQA S 3432 # JV-01 */
  P2FUNC(Std_ReturnType, GPT_PRIVATE_CODE, pGetPredefTimerValue)(Gpt_PredefTimerType, uint32 *);                        /* PRQA S 1336, 3432 # JV-01, JV-01 */
  #endif
} Gpt_HwFuncTableType;

#endif /* GPT_TYPES_HEADER */
/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
