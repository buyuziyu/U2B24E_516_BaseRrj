/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_Kernel.h                                                                                        */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Kernel prototypes for ADC Driver                                                                */
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
 * 2.5.1: 30/06/2025 : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                     Remove SW-VERSION in file header
 * 2.5.0: 30/06/2025 : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.4.0: 31/05/2025 : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.1: 28/02/2025 : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3: 31/10/2024 : Update SW-VERSION 2.1.3
 * 2.1.2: 30/09/2024 : Update SW-VERSION 2.1.2
 * 2.0.1: 18/10/2023 : Support QAC Amendment 2, add message 1534, 1536
 * 2.0.0: 26/06/2023 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef ADC_KERNEL_H
#define ADC_KERNEL_H


/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for using Std Type (e.g STD_ON), Compiler Macros(e.g P2FUNC), Platform Types (e.g uint8)*/
#include "Std_Types.h"
#include "Adc_Cfg.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ADC_KERNEL_AR_RELEASE_MAJOR_VERSION    ADC_AR_RELEASE_MAJOR_VERSION                                             /* PRQA S 1534 # JV-01 */
#define ADC_KERNEL_AR_RELEASE_MINOR_VERSION    ADC_AR_RELEASE_MINOR_VERSION                                             /* PRQA S 1534 # JV-01 */
#define ADC_KERNEL_AR_RELEASE_REVISION_VERSION ADC_AR_RELEASE_REVISION_VERSION                                          /* PRQA S 1534 # JV-01 */

/* File version information */
#define ADC_KERNEL_SW_MAJOR_VERSION            ADC_SW_MAJOR_VERSION                                                     /* PRQA S 1534 # JV-01 */
#define ADC_KERNEL_SW_MINOR_VERSION            ADC_SW_MINOR_VERSION                                                     /* PRQA S 1534 # JV-01 */

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (1:1534)    : The macro '%1s' is declared but not used within this project.                                */
/* Rule                : MISRA C:2012 Rule-2.5                                                                        */
/* JV-01 Justification : This is accepted. This macro is used by other file.                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1536)    : The tag '%1s' is declared but not used within this project.                                  */
/* Rule                : MISRA C:2012 Rule-2.4                                                                        */
/* JV-01 Justification : This is accepted. This tag is used by other file.                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#if (ADC_MULTI_CORE_SUPPORT == STD_ON)

/* Satellite Service */
#define Adc_LockedStatus(X)             (X == ADC_TRUE)                                                                 /* PRQA S 1534 # JV-01 */
#define Adc_UnLockedStatus(X)           (X == ADC_FALSE) 

/* Master Service */ 
#define Adc_CheckingRequest(X)          (X == ADC_TRUE)
#define Adc_LockProcess(X)              (X = ADC_TRUE)
#define Adc_UnLockProcess(X)            (X = ADC_FALSE)


/* Type definition for Request from Adc_GroupConfig */
typedef struct Adc_GroupConfig_RequestType_Stag                                                                         /* PRQA S 1536 # JV-01 */
{
  /* Satellite request */
  boolean blSetRequest;
  /* Status of processing - Locking the buffer */
  boolean blBufferLock;
} Adc_GroupConfig_RequestType;
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#define ADC_START_SEC_PUBLIC_CODE_LOCAL
#include "ADC_MemMap.h"

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/* Kernel API handle request by Adc_StartGroupConversion */
extern FUNC(void, ADC_PUBLIC_CODE) Adc_Kernel_StartGroupConversion(void);
/* Kernel API handle request by Adc_StopGroupConversion */
extern FUNC(void, ADC_PUBLIC_CODE) Adc_Kernel_StopGroupConversion(void);
#endif 

#if (ADC_HW_TRIGGER_API == STD_ON)
/* Kernel API handle request by Adc_EnableHwTrigger */
extern FUNC(void, ADC_PUBLIC_CODE) Adc_Kernel_EnableHardwareTrigger(void);
/* Kernel API handle request by Adc_DisableHwTrigger */
extern FUNC(void, ADC_PUBLIC_CODE) Adc_Kernel_DisableHardwareTrigger(void);
#endif

#define ADC_STOP_SEC_PUBLIC_CODE_LOCAL
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"
/* Globale scope - share among cores */
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
extern volatile VAR(Adc_GroupConfig_RequestType, ADC_VAR_NO_INIT) Adc_StartGroupConversionInfo[ADC_MAX_SW_TRIGGER];
extern volatile VAR(Adc_GroupConfig_RequestType, ADC_VAR_NO_INIT) Adc_StopGroupConversionInfo[ADC_MAX_SW_TRIGGER];
#endif

#if (ADC_HW_TRIGGER_API == STD_ON)
extern volatile VAR(Adc_GroupConfig_RequestType, ADC_VAR_NO_INIT) Adc_EnableHardwareTriggerInfo[ADC_MAX_HW_TRIGGER];
extern volatile VAR(Adc_GroupConfig_RequestType, ADC_VAR_NO_INIT) Adc_DisableHardwareTriggerInfo[ADC_MAX_HW_TRIGGER];
#endif

#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Adc_MemMap.h"

#endif /* ADC_MULTI_CORE_SUPPORT == STD_ON */
#endif /* ADC_KERNEL_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
