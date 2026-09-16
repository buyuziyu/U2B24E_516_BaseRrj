/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Icu_Types.h                                                                                         */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 * 2.4.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.4.0:  30/05/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.01 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 * 2.1.2:  31/10/2024  : As part of support GTM HWIP into common code, following changes are made:
 *                       1. Update struct definition Icu_ConfigType add pGtmTbuUnitConfig
 *                       2. Update precompile condition
 *                       As part of support QAC 9.5.0, following changes are made:
 *                       1. Remove QAC messages 1534, 1536.
 *                       As part of support multi core multi postbuid variant, following changes are made:
 *                       1. Add item ucKernelCoreId in struct Icu_ConfigType 
 * 2.0.1:  19/10/2023  : Add QAC messages 1534, 1536
 * 2.0.0:  03/08/2023  : #include "Icu_Mapping.h" update to #include "Icu_MemMap.h" 
 *                       Remove all multi-instance including methods
 *                       Remove all supported multi-instance header file
 * 1.4.5:  02/12/2022  : Remove ICU_CBK_HEADER (move include Icu_Cbk.h/Icu_External.h to Pbcfg file)
 * 1.4.3:  17/04/2022  : Merge QAC message from U2Ax, E2x and U2Bx
 * 1.4.1:  18/10/2021  : Add QAC message 9.5.0
 *         15/09/2021  : Rename pTimerChannelConfig to pChannelUserRegConfig
 *                       Correct preprocessor directives
 *                       Update Pointer to ICU driver Timer IP configuration
 * 1.3.2:  30/08/2021  : Update header file macro.
 *                       Correct included file.
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  25/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/**********************************************************************************************************************/
#ifndef ICU_TYPES_H
#define ICU_TYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for pre-compile options */

/* platform specific type definitions */
#include "Std_Types.h"
/* Included for pre-compile options */
#include "Icu_Cfg.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define ICU_TYPES_AR_RELEASE_MAJOR_VERSION    ICU_AR_RELEASE_MAJOR_VERSION
#define ICU_TYPES_AR_RELEASE_MINOR_VERSION    ICU_AR_RELEASE_MINOR_VERSION
#define ICU_TYPES_AR_RELEASE_REVISION_VERSION ICU_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define ICU_TYPES_SW_MAJOR_VERSION            ICU_SW_MAJOR_VERSION
#define ICU_TYPES_SW_MINOR_VERSION            ICU_SW_MINOR_VERSION

/**********************************************************************************************************************/

/* Data Structure for ICU for Initializing the ICU Module */
typedef struct STag_Icu_ConfigType
{
  /* Database start value */
  uint32 ulStartOfDbToc;

  /* Pointer to ICU driver channel configuration */
  P2CONST(void, TYPEDEF, ICU_CONFIG_DATA) pChannelConfig;

  /* Pointer to ICU driver channel user register configuration */
  P2CONST(void, TYPEDEF, ICU_CONFIG_DATA) pChannelUserRegConfig;

  /* Pointer to the address of internal RAM data */
  P2VAR(volatile void, TYPEDEF, ICU_CONFIG_DATA) pRamAddress;

  #if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
  /* Pointer to the address of Signal Measure RAM data */
  P2VAR(volatile void, TYPEDEF, ICU_CONFIG_DATA) pSignalMeasureAddress;
  #endif

  #if (ICU_TIMESTAMP_API == STD_ON)
  /* Pointer to the address of TimeStamp RAM data */
  P2VAR(volatile void, TYPEDEF, ICU_CONFIG_DATA) pTimeStampAddress;
  #endif

  #if (ICU_EDGE_COUNT_API == STD_ON)
  /* Pointer to the address of Edge Count RAM data */
  P2VAR(volatile void, TYPEDEF, ICU_CONFIG_DATA) pEdgeCountRamAddress;
  #endif

  #if (ICU_TAU_UNIT_USED == STD_ON)
  /* Pointer to ICU driver TAU configuration */
  P2CONST(void, TYPEDEF, ICU_CONFIG_DATA) pTAUUnitConfig;
  #endif
  
  #if (ICU_ATU_TIMER_UNIT_USED == STD_ON)
  /* Pointer to ICU driver ATU configuration */
  P2CONST(void, TYPEDEF, ICU_CONFIG_DATA) pATUConfig;
  #endif
  
  #if (ICU_GTM_TBU_UNIT_USED == STD_ON)
  /* Pointer to ICU driver GTM configuration */
  P2CONST(void, TYPEDEF, ICU_CONFIG_DATA) pGtmTbuUnitConfig;
  #endif

  #if (ICU_MULTI_CORE_SUPPORT == STD_ON)
  /* Hold the configured kernel core ID */
  uint8 ucKernelCoreId;
  #endif

} Icu_ConfigType;

/* Operation Mode of the ICU Module */
typedef enum ETag_Icu_ModeType                                                                                          
{
  ICU_MODE_NORMAL,
  ICU_MODE_SLEEP
} Icu_ModeType;

typedef struct STag_Icu_HWIPType
{
  /* Pointer to GPT driver Timer Unit configuration */
  VAR(uint8, ICU_CONFIG_DATA) ucIndex;
} Icu_HWIPType;

#endif /* ICU_TYPES_HEADER */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
