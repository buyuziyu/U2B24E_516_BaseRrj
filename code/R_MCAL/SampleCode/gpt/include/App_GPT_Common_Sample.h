/*============================================================================*/
/* Project      = RH850/U2Bx,U2Cx MCAL Ver21.00.00.D                          */
/* Module       = App_GPT_Common_Sample.h                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Header file information for application.                                   */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        X2x                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 *  2.4.0  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) release
 *  2.3.2  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *  2.3.1  31/03/2025  : Update SW-VERSION for RH850/U2BxE MCAL
 *                       Ver22.00.02/Ver22.00.02.D Release
 *  2.3.0  28/02/2025  : Update SW-VERSION for
 *                       RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                       Final Release
 *  2.1.2  31/10/2024  : As part of Post Build multiple varriant support,
 *                       following changes are made
 *                       1.Add macro used for Post-build variant
 *  2.0.0  12/05/2023  : Update SW version 2.0.0
 *  1.4.1  12/10/2021  : Modify to add define for channel
 *                       Gpt_GptChannelConfiguration6.
 *  1.2.0  17/07/2020  : Release
 *  1.1.0  19/06/2020  : Release
 *  1.0.0  01/01/2020  : Initial Version
 */
/******************************************************************************/
#ifndef APP_GPT_COMMON_SAMPLE_H
#define APP_GPT_COMMON_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Gpt.h"
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define DEVICE_701503   701503

#define Gpt_GptChannelConfiguration0 GptConf_GptChannelConfiguration_GptChannelConfiguration
#define Gpt_GptChannelConfiguration1 GptConf_GptChannelConfiguration_GptChannelConfiguration_001
#define Gpt_GptChannelConfiguration2 GptConf_GptChannelConfiguration_GptChannelConfiguration_002
#define Gpt_GptChannelConfiguration3 GptConf_GptChannelConfiguration_GptChannelConfiguration_003
#define Gpt_GptChannelConfiguration4 GptConf_GptChannelConfiguration_GptChannelConfiguration_004
#define Gpt_GptChannelConfiguration5 GptConf_GptChannelConfiguration_GptChannelConfiguration_005
#define Gpt_GptChannelConfiguration6 GptConf_GptChannelConfiguration_GptChannelConfiguration_006
#define Gpt_GptChannelConfiguration7 GptConf_GptChannelConfiguration_GptChannelConfiguration_007
#define Gpt_GptChannelConfiguration8 GptConf_GptChannelConfiguration_GptChannelConfiguration_008
#define Gpt_GptChannelConfiguration9 GptConf_GptChannelConfiguration_GptChannelConfiguration_009

#define GPT_TARGET_VALUE_0              0x0000FFFFUL
#define GPT_TARGET_VALUE_1              0x0000FFFFUL
#define GPT_TARGET_VALUE_2              0x0000FFFFUL
#define GPT_TARGET_VALUE_3              0x0000FFFFUL
#define GPT_TARGET_VALUE_4              0x0000FFFFUL
#define GPT_TARGET_VALUE_5              0x0000FFFFUL
#define GPT_TARGET_VALUE_6              0x0000FFFFUL
#define GPT_TARGET_VALUE_7              0x0000FFFFUL
#define GPT_TARGET_VALUE_8              0x0000FFFFUL
#define GPT_TARGET_VALUE_9              0x0000FFFFUL

/* Macro used for Post-build variant case*/
#define GPT_TARGET_VALUE_MAX16BIT       0x0000FFFFUL
#define GPT_TARGET_VALUE_RANDOM         0x00007FFFUL
#define GPT_NOTI_COUNT_CONTINOUS        0x0F
#define GPT_NOTI_COUNT_ONESHOT          0x01
/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/

#endif /* APP_GPT_COMMON_SAMPLE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
