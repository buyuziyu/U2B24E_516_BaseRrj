/*====================================================================================================================*/
/* Project      = RH850/X2x AR4 MCAL Development                                                                      */
/* Module       = Pwm_Types.h                                                                                         */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                       COPYRIGHT                                                    */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* API function implementations of PWM  Driver                                                                        */
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
/*                                              Devices:        X2x                                                   */
/*====================================================================================================================*/
/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.5.1: 30/06/2025 : Update macro name for elements of Pwm_ClockSourceType                                          **
 * 2.5.0: 30/06/2025 : Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release                                        **
 * 2.4.0: 31/05/2025 : Update SW-VERSION for U2Cx Ver21.01.01 Final Release                                           **
 * 2.3.2: 29/04/2025 : Update SW-VERSION for U2Ax Ver22.00.03 Beta Release                                            **
 * 2.3.1: 31/03/2025 : Update SW-VERSION for U2BxE Ver22.00.02 Beta Release                                           **
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release                        **
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release                                  **
 * 2.1.2: 31/10/2024 : As part of GTM support, following changes are made                                             **
 *                     1. Update Pwm_ClockSourceType for GTM unit and value of macro PWM_TOTAL_HWFUNC_SUPPORTED to 5  **
 * 2.1.1: 30/08/2024 : Update SW-VERSION for Ver22.01.01 U2Bx Beta Release                                            **
 *                     As part of ARDAACL-40198 support, following changes are made                                   **
 *                     1. Add ucKernelCoreId to struct Pwm_ConfigType                                                 **
 *                     As part of U2C support, following changes are made                                             **
 *                     1. Remove QAC message 1534, 1535, 1536                                                         **
 * 2.0.1: 21/10/2023 : Follow rule QAC 10.3.0, add new QAC message 1534, 1536, 1535                                   **
 * 2.0.0: 05/07/2023 : Remove #ifdef PWM_INSTANCE_INDEX. Remove message 0841                                          **
 *        11/05/2023 : Modify value of struct Pwm_OutputStateType: PWM_HIGH has avlue as 0x00,                        **
 *                     PWM_LOW has value as 0x01                                                                      **
 * 1.4.2: 26/02/2022 : Updated SW VERSION to 1.4.2 and add macro PWM_TOTAL_HWFUNC_SUPPORTED                           **
 * 1.3.2: 04/08/2021 : Device specific implementation move to device specific file.                                   **
 *                     Format source code unified within module.                                                      **
 * 1.3.1: 02/07/2021 : Add QAC message 9.5.0                                                                          **
 *                     Format source code to 120 characters                                                           **
 *                     Improve Violation tag (remove START/END)                                                       **
 *        15/05/2021  : Fixed Coding Rule and tailor space                                                            **
 * 1.2.0: 28/07/2020 : Release                                                                                        **
 * 1.1.0: 19/06/2020 : Release                                                                                        **
 * 1.0.1: 27/05/2020 : Modify "aaTimerUnitConfig[PWM_TOTAL_HW_IP_CONFIG]"                                             **
 *                     to "aaTimerUnitConfig[PWM_TOTAL_HW_IP_SUPPORTED]"                                              **
 * 1.0.0: 24/03/2020 : Initial Version.                                                                               **
 *                                                                                                                    */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/**********************************************************************************************************************/

/**********************************************************************************************************************/

#ifndef PWM_TYPES_H
#define PWM_TYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_TYPES_AR_RELEASE_MAJOR_VERSION    PWM_AR_RELEASE_MAJOR_VERSION
#define PWM_TYPES_AR_RELEASE_MINOR_VERSION    PWM_AR_RELEASE_MINOR_VERSION
#define PWM_TYPES_AR_RELEASE_REVISION_VERSION PWM_AR_RELEASE_REVISION_VERSION
/* Software module version information */
#define PWM_TYPES_SW_MAJOR_VERSION            PWM_SW_MAJOR_VERSION
#define PWM_TYPES_SW_MINOR_VERSION            PWM_SW_MINOR_VERSION
/**********************************************************************************************************************/

#define PWM_TOTAL_HWFUNC_SUPPORTED            5

/* Type definition for Pwm_ChannelType */
typedef uint8 Pwm_ChannelType;
/* Type definition for Pwm_PeriodType */
typedef uint32 Pwm_PeriodType;
/* Type definition for Pwm_OutputStateType */
typedef enum ETag_Pwm_OutputStateType
{
  PWM_HIGH = 0,
  PWM_LOW
} Pwm_OutputStateType;
/* Type definition for Pwm_EdgeNotificationType */
typedef enum ETag_Pwm_EdgeNotificationType
{
  PWM_RISING_EDGE = 0,
  PWM_FALLING_EDGE,
  PWM_BOTH_EDGES
} Pwm_EdgeNotificationType;
/* Type definition for Pwm_ChannelClassType */
typedef enum ETag_Pwm_ChannelClassType
{
  PWM_VARIABLE_PERIOD = 0,
  PWM_FIXED_PERIOD,
  PWM_FIXED_PERIOD_SHIFTED
} Pwm_ChannelClassType;

/* Type definition for Pwm_ClockSourceType */
typedef enum ETag_Pwm_ClockSourceType
{
  PWM_CLKBUSLINE0 = 0,
  PWM_CLKBUSLINE1,
  PWM_CLKBUSLINE2,
  PWM_CLKBUSLINE3,
  PWM_CCM_FXCLK_RES0,
  PWM_CCM_FXCLK_RES1,
  PWM_CCM_FXCLK_RES2,
  PWM_CCM_FXCLK_RES3,
  PWM_CCM_FXCLK_RES4,
  PWM_CCM_CLK_RES_0,
  PWM_CCM_CLK_RES_1,
  PWM_CCM_CLK_RES_2,
  PWM_CCM_CLK_RES_3,
  PWM_CCM_CLK_RES_4,
  PWM_CCM_CLK_RES_5,
  PWM_CCM_CLK_RES_6,
  PWM_CCM_CLK_RES_7,
  PWM_INVALID_CLOCK_SOURCE = 0xFF
} Pwm_ClockSourceType;

/* Structure for Pwm_Init configuration */
/* Overall module configuration data structure */
typedef struct STag_Pwm_ConfigType
{
  /* Database start value */
  uint32 ulStartOfDbToc;
  #if (PWM_MULTI_CORE_SUPPORT == STD_ON)
  /* Hold the configured kernel core ID */
  uint8 ucKernelCoreId;
  #endif
  /* Pointer to PWM Driver Sub-block Unit configuration */
  P2CONST(void, TYPEDEF, PWM_CONFIG_CONST) aaTimerUnitConfig[PWM_TOTAL_HWFUNC_SUPPORTED];
  /* Pointer to PWM Driver channel configuration */
  P2CONST(void, TYPEDEF, PWM_CONFIG_DATA) pChannelConfig;
  /* Pointer to PWM Driver HWIP configuration */
  P2CONST(void, TYPEDEF, PWM_CONFIG_DATA) pHWIPConfig; 
  
} Pwm_ConfigType;

/***********************************************************************************************************************
**                                     Structure for PWM HW-IP config information                                     **
***********************************************************************************************************************/
/* Data Structure for PWM required for Initializing the PWM timer unit */
typedef struct STag_Pwm_HWIP_ConfigType
{
  /* Pointer to PWM driver Timer Unit configuration */
  VAR(uint8, PWM_VAR_NO_INIT) ucIndex;
} Pwm_HWIP_ConfigType;

#endif /* PWM_TYPES_H */

/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
