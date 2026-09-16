/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_Ram.h                                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of API information.                                                                                      */
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
/*              Devices:        X2X                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025   : Update SW-VERSION for U2Bx Ver22.02.00.001 Release
 * 2.5.0:  30/06/2025   : Update SW-VERSION for U2Ax Ver22.01.00(D) Release
 *                        Modify memory section for Mcu_GblRAMInitStatus
 * 2.4.0:  31/05/2025   : Update SW-VERSION for U2Cx Ver21.01.01 Release
 * 2.3.2:  29/04/2025   : Update SW-VERSION for U2Ax Ver22.00.03 Release
 * 2.3.1:  31/03/2025   : Update SW-VERSION for U2BxE Ver22.00.02 Release
 * 2.3.0:  28/02/2025   : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Release
 * 2.1.2:  31/10/2024   : Update SW-VERSION to 2.1.2
 * 2.1.1:  30/08/2024   : Update SW-VERSION to 2.1.1
 *                        As part of ARDAACL-47932 (ARDAACL-47792), following changes are made:
 *                        - Add global variable Mcu_GucRramEccEcmInit
 * 1.4.5:  06/01/2023   : As new Mcu structure:
 *                        - Add definitions of Mcu_GpClockHwInfo, Mcu_GpResetHwInfo, Mcu_GpWakeUpHwInfo,
 *                          Mcu_GpWUFMONHwInfo, Mcu_GpStbHwInfo, Mcu_GpDmonHwInfo, Mcu_GpVmonHwInfo, Mcu_GpClmHwInfo,
 *                          Mcu_GpIOBufferHoldHwInfo, Mcu_GpEcmHwInfo
 * 1.4.3:  13/04/2022   : Update SW-VERSION to 1.4.3
 * 1.3.1:  02/07/2021   : Add QAC message 9.5.0
 *                        Format source code to 120 characters
 *                        Improve Violation tag (remove START/END)
 *         07/05/2021   : As per ARDAACL-145, remove definition of Mcu_GpEcmSetting since it's redundant.
 * 1.3.0:  17/11/2020   : Add new Mcu_GaaDmonWaitCntNumPll variable
 * 1.2.0:  17/07/2020   : Release
 * 1.1.0:  19/06/2020   : Release
 * 1.0.1:  12/05/2020   : Update to add global variable to the appropriate memory section
 * 1.0.0:  10/01/2020   : Initial Version
 */
/**********************************************************************************************************************/
#ifndef MCU_RAM_H
#define MCU_RAM_H

/***********************************************************************************************************************
**                                                 Include Section                                                    **
***********************************************************************************************************************/
#include "Mcu_PBTypes.h"
#include "Mcu_CLK_LLDriver.h"
#include "Mcu_CLM_LLDriver.h"
#include "Mcu_ECM_LLDriver.h"
#include "Mcu_ECC_LLDriver.h"
#include "Mcu_ECM_Irq.h"
#include "Mcu_RAM_LLDriver.h"
#include "Mcu_VMN_LLDriver.h"
#include "Mcu_RST_LLDriver.h"
#include "Mcu_STB_LLDriver.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR specification version information */
#define MCU_RAM_AR_RELEASE_MAJOR_VERSION    MCU_AR_RELEASE_MAJOR_VERSION
#define MCU_RAM_AR_RELEASE_MINOR_VERSION    MCU_AR_RELEASE_MINOR_VERSION
#define MCU_RAM_AR_RELEASE_REVISION_VERSION MCU_AR_RELEASE_REVISION_VERSION

/* File version information */
#define MCU_RAM_SW_MAJOR_VERSION            MCU_SW_MAJOR_VERSION
#define MCU_RAM_SW_MINOR_VERSION            MCU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#define MCU_START_SEC_VAR_NO_INIT_PTR
#include "Mcu_MemMap.h"

/* Global variable to store the config pointer */
extern P2CONST(Mcu_ConfigType, MCU_VAR_NO_INIT, MCU_CONFIG_CONST) volatile Mcu_GpConfigPtr;

/* Global pointer variable for MCU Clock Setting configuration */
extern P2CONST(Mcu_ClockSettingType, MCU_VAR_NO_INIT, MCU_CONFIG_CONST) volatile Mcu_GpClockSetting;

/* Global pointer variable for MCU Clock HW information */
extern volatile P2CONST(Mcu_ClockHwInfoType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) Mcu_GpClockHwInfo;

/* Global pointer variable for MCU Reset HW information */
extern volatile P2CONST(Mcu_ResetHwInfoType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) Mcu_GpResetHwInfo;

#if ((MCU_GETWAKEUPFACTOR_API == STD_ON) || (MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON))
/* Global pointer variable for MCU Wake Up Factor HW information */
extern volatile P2CONST(Mcu_WakeUpHwInfoType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) Mcu_GpWakeUpHwInfo;
#endif /* ((MCU_GETWAKEUPFACTOR_API == STD_ON) || (MCU_CLEARANDSETWAKEUPFACTOR_API == STD_ON)) */

#if (MCU_GETWAKEUPFACTOR_API == STD_ON)
/* Global pointer variable for MCU Wake Up Factor Monitor HW information */
extern volatile P2CONST(Mcu_WUFMONHwInfoType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) Mcu_GpWUFMONHwInfo;
#endif /* (MCU_GETWAKEUPFACTOR_API == STD_ON) */

#if (MCU_MODE_TRANSITION_SUPPORT == STD_ON)
/* Global pointer variable for MCU Standby HW information */
extern volatile P2CONST(Mcu_StbHwInfoType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) Mcu_GpStbHwInfo;
#endif

#if (MCU_DMON_DIAG_OPERATION == STD_ON)
/* Global pointer variable for MCU Dmon HW information */
extern volatile P2CONST(Mcu_DmonHwInfoType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) Mcu_GpDmonHwInfo;
#endif

#if (MCU_VMON_DIAG_OPERATION == STD_ON)
/* Global pointer variable for MCU Vmon HW information */
extern volatile P2CONST(Mcu_VmonHwInfoType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) Mcu_GpVmonHwInfo;
#endif

#if (MCU_CLMA_OPERATION == STD_ON)
/* Global pointer variable for MCU CLM HW information */
extern volatile P2CONST(Mcu_ClmHwInfoType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) Mcu_GpClmHwInfo;
#endif

#if (MCU_RELEASEIOBUFFERHOLD_API == STD_ON)
/* Global pointer variable for MCU IO Buffer Hold information */
extern volatile P2CONST(Mcu_IOBufferHoldHwInfoType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) Mcu_GpIOBufferHoldHwInfo;
#endif

/* Global pointer variable for MCU ECC information */
extern volatile P2CONST(Mcu_EccHwInfoType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) Mcu_GpEccHwInfo;

#if (MCU_ECM_OPERATION == STD_ON)
/* Global pointer variable for MCU ECM information */
extern volatile P2CONST(Mcu_EcmHwInfoType, MCU_VAR_NO_INIT, MCU_CONFIG_DATA) Mcu_GpEcmHwInfo;
#endif

#define MCU_STOP_SEC_VAR_NO_INIT_PTR
#include "Mcu_MemMap.h"

#define MCU_START_SEC_VAR_INIT_BOOLEAN
#include "Mcu_MemMap.h"

/* Global variable to store Initialization status of MCU Driver */
extern VAR(volatile boolean, MCU_VAR_INIT) Mcu_GblDriverStatus;

#define MCU_STOP_SEC_VAR_INIT_BOOLEAN
#include "Mcu_MemMap.h"

#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

#if (MCU_GET_RAM_STATE_API == STD_ON)
/* Global variable to store ram state of MCU Driver */
extern VAR(volatile Mcu_RamStateType, MCU_VAR_INIT) Mcu_GblRAMInitStatus;
#endif /* MCU_GET_RAM_STATE_API == STD_ON */

#if (MCU_RAM_ECCECM_SETTING_INITRAMSECTION == STD_ON)
extern volatile VAR(uint8, MCU_VAR_INIT) Mcu_GucLramEccEcmInit;
extern volatile VAR(uint8, MCU_VAR_INIT) Mcu_GucCramEccEcmInit;
#if (MCU_RETENTION_RAM_SETTING == STD_ON)
extern volatile VAR(uint8, MCU_VAR_INIT) Mcu_GucRramEccEcmInit;
#endif /* MCU_RETENTION_RAM_SETTING == STD_ON */
#endif /* MCU_RAM_ECCECM_SETTING_INITRAMSECTION == STD_ON */

#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Mcu_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* MCU_RAM_H  */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
