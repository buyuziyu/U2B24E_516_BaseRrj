/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Dio.h                                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros, DIO type definitions, structure data types and API function prototypes of DIO Driver.   */
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
 * 2.4.1:  13/06/2025  : Update SW-VERSION to 2.4.1
 * 2.4.0:  30/06/2025  : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D U2Bx Final Release
 * 2.1.2:  31/10/2024  : 
 *                       Remove Condition DIO_AR_VERSION == DIO_AR_431_VERSION with following definition for AR 4.3.1 
 *                       Update memory mapping from DIO_START/STOP_SEC_CONST_UNSPECIFIED 
 *                       to DIO_START/STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED in definition 
 *                       of Dio_GaaChannelGroupData, DIO_GaaPweData
 * 2.1.1:  11/06/2024  : As part of ARDAACL-34989, following changes are made
 *                       Remove QAC msg 1534, 1536
 * 2.1.0:  29/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  20/12/2023  : Update SW-Version for DIO         
 * 2.0.1:  22/10/2023  : Add QAC msg 1534, 1536
 *         16/10/2023  : Correct Syntax of Dio_MaskedWritePort API
 *         12/10/2023  : Update SW-VERSION and Module Software version information to 2.0.1
 *         30/09/2023  : Update value of macro DIO_AR_R21_11_VERSION to DIO_AR_R22_11_VERSION (value from 470U to 480U)
 *                       Update condition DIO_AR_VERSION == DIO_AR_R21_11_VERSION to 
 *                       DIO_AR_VERSION == DIO_AR_R22_11_VERSION and value of DIO_AR_RELEASE_MINOR_VERSION to 8U
 * 2.0.0:  18/07/2023  : Add DIO_E_INVALID_CORE macro to support multi-core.
 *                       Add ucChannelGroupCoreIndex in Dio_ChannelGroupType.
 *         21/04/2023  : Update DIO_SW_MAJOR_VERSION to 2u for sw-version up to 2.0.0
 *                       Update DIO_SW_MINOR_VERSION to 0u for sw-version up to 2.0.0
 * 1.5.0:  07/03/2023  : Update DIO_SW_MINOR_VERSION to 5u for sw-version up to 1.5.0
 *                       Update DIO_SW_PATCH_VERSION to 0u for sw-version up to 1.5.0
 * 1.4.3:  01/12/2022  : Support Autosar Version 21.11
 *                       Update DIO_SW_PATCH_VERSION to 3u for sw-version up to 1.4.3
 * 1.4.2:  24/04/2022  : Update DIO_SW_PATCH_VERSION to 2u for sw-version up to 1.4.2
 * 1.4.1:  06/12/2021  : Update DIO_SW_PATCH_VERSION to 1u for sw-version up
 * 1.4.0:  08/10/2021  : Updated SW-VERSION 
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 *         06/05/2021  : A space shall be used after each comma in the argument
 *                       or initialization list follow Style_Format_010.
 * 1.3.0:  15/12/2020  : Release
 * 1.2.1:  15/12/2020  : Update DIO_SW_MINOR_VERSION
 * 1.2.0:  26/08/2020  : Release
 * 1.1.1:  26/08/2020  : Update DIO_SW_MINOR_VERSION
 * 1.1.0:  19/06/2020  : Release
 * 1.0.2:  22/05/2020  : Update software version definition.
 * 1.0.1:  09/12/2019  : Support Autosar Version 4.3.1
 *         19/03/2020  : Add Justification for QAC MISRA-C:2012
 * 1.0.0:  09/09/2019  : Initial Version
 */
/**********************************************************************************************************************/
#ifndef DIO_H
#define DIO_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Standard AUTOSAR types */
#include "Std_Types.h"
/* DIO Configuration header file */
#include "Dio_Cfg.h"
#include "rh850_Types.h"
/* Included for macro definitions and structure declarations */
#include "Dio_LTTypes.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#define DIO_VENDOR_ID       DIO_VENDOR_ID_VALUE
#define DIO_MODULE_ID       DIO_MODULE_ID_VALUE
#define DIO_INSTANCE_ID     DIO_INSTANCE_ID_VALUE
#define DIO_AR_422_VERSION  422U
#define DIO_AR_R22_11_VERSION 480U

/*START of DIO_AR_VERSION */

/* AUTOSAR release version information */
#if (DIO_AR_VERSION == DIO_AR_422_VERSION)
#define DIO_AR_RELEASE_MAJOR_VERSION    4U
#define DIO_AR_RELEASE_MINOR_VERSION    2U
#define DIO_AR_RELEASE_REVISION_VERSION 2U
#elif (DIO_AR_VERSION == DIO_AR_R22_11_VERSION)
#define DIO_AR_RELEASE_MAJOR_VERSION    4U
#define DIO_AR_RELEASE_MINOR_VERSION    8U
#define DIO_AR_RELEASE_REVISION_VERSION 0U
#endif
/*END of DIO_AR_VERSION */

/* Module Software version information */
#define DIO_SW_MAJOR_VERSION                    2U
#define DIO_SW_MINOR_VERSION                    4U
#define DIO_SW_PATCH_VERSION                    1U

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, , CWE Rule CWE-398, CWE-569                                          */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               API Service Id Macros                                                **
***********************************************************************************************************************/
/* Service ID for DIO read Channel */
#define DIO_READ_CHANNEL_SID                    (uint8)0x00

/* Service ID for DIO write Channel */
#define DIO_WRITE_CHANNEL_SID                   (uint8)0x01

/* Service ID for DIO read Port */
#define DIO_READ_PORT_SID                       (uint8)0x02

/* Service ID for DIO write Port */
#define DIO_WRITE_PORT_SID                      (uint8)0x03

/* Service ID for DIO read Channel Group */
#define DIO_READ_CHANNEL_GROUP_SID              (uint8)0x04

/* Service ID for DIO write Channel Group */
#define DIO_WRITE_CHANNEL_GROUP_SID             (uint8)0x05

/* Service ID for DIO flip Channel */
#define DIO_FLIP_CHANNEL_SID                    (uint8)0x11

/* Service ID for DIO getting Version Information */
#define DIO_GET_VERSION_INFO_SID                (uint8)0x12

/* Service ID for DIO Masked Write Channel */
#define DIO_MASKED_WRITE_PORT_SID               (uint8)0x13

/* Service ID for DIO Read Channel Output Value */
#define DIO_READ_CHANNEL_OUTPUT_VALUE_SID       (uint8)0x14

/* Service ID for DIO Read Channel Group Output Value */
#define DIO_READ_CHANNEL_GROUP_OUTPUT_VALUE_SID (uint8)0x15

/***********************************************************************************************************************
**                                                  DET Error Codes                                                   **
***********************************************************************************************************************/
/* DET code to report Invalid Channel */
#define DIO_E_PARAM_INVALID_CHANNEL_ID          (uint8)0x0A

/* DET code to report Invalid Port */
#define DIO_E_PARAM_INVALID_PORT_ID             (uint8)0x14

/* DET code to report Invalid Channel Group */
#define DIO_E_PARAM_INVALID_GROUP               (uint8)0x1F

/* Dio API service called with NULL pointer parameter (except Dio_Init) */
#define DIO_E_PARAM_POINTER                     (uint8)0x20

/* Regarding PWE register */
#define DIO_PWE_INVALID_VALUE                   (uint32)0x00000000UL

#define DIO_PWE_EACH_WRITE_DISABLE              (uint8)0x00
#define DIO_PWE_EACH_WRITE_ENABLE               (uint8)0x01

#define DIO_PKCPROT_REG                         (*((volatile uint32 *)DIO_PKCPROT))
#define DIO_PWE_REG                             (*((volatile uint32 *)DIO_PWE))

/* DET Error - Call in invalid core */
#define DIO_E_INVALID_CORE                      (uint8)0xF1

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* Type definition for Dio_ChannelType used by the DIO APIs */
typedef uint16 Dio_ChannelType;

/* Type definition for Dio_PortType used by the DIO APIs */
typedef uint8 Dio_PortType;

/* Type definition for Dio_LevelType used by the DIO APIs */
typedef uint8 Dio_LevelType;

/* Type definition for Dio_PortLevelType used by the DIO APIs */
typedef uint16 Dio_PortLevelType;

/* Structure for Dio_ChannelGroup*/
typedef struct STag_Dio_ChannelGroupType
{
  /* Positions of the Channel Group */
  uint16 usMask;
  /* First appearance bit position from LSB of usMask */
  uint8 ucOffset;
  /* PortGroup Index in the array Dio_GaaPortGroup[] */
  uint8 ucPortIndex;

  #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare the variable to store list of configured core ID for the channel group */
  uint8 ucChannelGroupCoreIndex;
  #endif
} Dio_ChannelGroupType;
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define DIO_START_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"

/* Function for DIO read Channel API */
extern FUNC(Dio_PortLevelType, DIO_PUBLIC_CODE) Dio_ReadPort(Dio_PortType PortId);

/* Function for DIO write Channel API */
extern FUNC(void, DIO_PUBLIC_CODE) Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

/* Function for DIO read Port API */
extern FUNC(Dio_LevelType, DIO_PUBLIC_CODE) Dio_ReadChannel(Dio_ChannelType ChannelId);

/* Function for DIO write Port API */
extern FUNC(void, DIO_PUBLIC_CODE) Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

#if (DIO_MASKED_WRITE_PORT_API == STD_ON)
/* Function for DIO Masked Write channel API */
extern FUNC(void, DIO_PUBLIC_CODE) Dio_MaskedWritePort(Dio_PortType PortId, Dio_PortLevelType Level,
                                                       Dio_PortLevelType Mask);
#endif

#if (DIO_READ_CHANNEL_OUTPUT_VALUE_API == STD_ON)
/* Function for DIO Read Channel Output Value API */
extern FUNC(Dio_LevelType, DIO_PUBLIC_CODE) Dio_ReadChannelOutputValue(const Dio_ChannelType LddChannelId);
#endif

#if (DIO_READ_CHANNELGROUP_OUTPUT_VALUE_API == STD_ON)
/* Function for DIO Read Channel Group Output Value API */
extern FUNC(Dio_PortLevelType, DIO_PUBLIC_CODE) Dio_ReadChannelGroupOutputValue
    (P2CONST(Dio_ChannelGroupType, DIO_VAR, DIO_CONFIG_DATA) ChannelGroupIdPtr);
#endif

/* Function for DIO read Channel Group API */
extern FUNC(Dio_PortLevelType, DIO_PUBLIC_CODE) Dio_ReadChannelGroup
    (P2CONST(Dio_ChannelGroupType, DIO_VAR, DIO_CONFIG_DATA) ChannelGroupIdPtr);

/* Function for DIO write Channel Group API */
extern FUNC(void, DIO_PUBLIC_CODE) Dio_WriteChannelGroup
    (P2CONST(Dio_ChannelGroupType, DIO_VAR, DIO_CONFIG_DATA) ChannelGroupIdPtr, Dio_PortLevelType Level);

#if (DIO_FLIP_CHANNEL_API == STD_ON)
/* Function for DIO flip channel API */
extern FUNC(Dio_LevelType, DIO_PUBLIC_CODE) Dio_FlipChannel(Dio_ChannelType ChannelId);
#endif

#if (DIO_VERSION_INFO_API == STD_ON)
extern FUNC(void, DIO_PUBLIC_CODE) 
                                Dio_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, DIO_APPL_DATA) versioninfo);   /* PRQA S 3432 # JV-01 */
#endif /*(DIO_VERSION_INFO_API == STD_ON)*/

#define DIO_STOP_SEC_PUBLIC_CODE
#include "Dio_MemMap.h"

#define DIO_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Dio_MemMap.h"
extern CONST(Dio_ChannelGroupType, DIO_CONFIG_DATA) Dio_GaaChannelGroupData[];                                          /* PRQA S 3684 # JV-01 */

extern CONST(uint32, DIO_CONST) DIO_GaaPweData[];                                                                       /* PRQA S 3684 # JV-01 */
#define DIO_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Dio_MemMap.h"

#endif
/* DIO_H  */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
