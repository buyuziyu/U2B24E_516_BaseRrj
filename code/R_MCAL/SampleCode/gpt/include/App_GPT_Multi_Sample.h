/*============================================================================*/
/* Project      = RH850/U2Bx,U2Cx MCAL Ver21.00.00.D                          */
/* Module       = App_GPT_Multi_Sample.h                                      */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2020,2023-2025 Renesas Electronics Corporation. All rights reserved.   */
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
 *  2.1.2  31/10/2024  : As part of GTM HWIP support, following changes are made
 *                       1.Add macro EIBD support for GTM
 *                       As part of Post Build multiple varriant support,
 *                       following changes are made
 *                       1.Add macro used for Post-build variant
 *                       2.Remove macro related to Barrier-Synchronization
 *                       3.Add extern for GblSyncFlag
 *  2.0.0  26/07/2023  : Remove multi-instance
 *         12/05/2023  : Update SW version 2.0.0
 *  1.4.5  12/02/2023  : Add EI Level Interrupt Bind Register for U2Bx
 *  1.3.1  15/05/2021  : Fixed Coding Rule
 *  1.2.0  17/07/2020  : Release
 *  1.1.0  19/06/2020  : Release
 *  1.0.0  01/01/2020  : Initial Version
 */
/******************************************************************************/
#ifndef APP_GPT_MULTI_SAMPLE_H
#define APP_GPT_MULTI_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Std_Types.h"
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* Global flag for sync information between cores */
extern volatile boolean GblSyncFlag;

#define GPT_SYNC_CLEAR               0x01UL
#define GPT_SYNC_START_PE0           0x01UL
#define GPT_SYNC_START_PE1           0x01UL << 1
#define GPT_SYNC_START_PE2           0x01UL << 2
#define GPT_SYNC_START_PE3           0x01UL << 3
#define GPT_SYNC_ENABLE              0x01UL
#define GPT_SYNC_COMPLETION          0x01UL
#define GPT_SYNC_UNCOMPLETION        0x00UL

#define GPT_SYNC_FALSE                        0x00000000UL
#define GPT_SYNC_TRUE                         0x55555555UL
#define GPT_RELEASE                           0x00000000UL
#define GPT_GETTING                           0xAAAAAAAAUL
#define GPT_CLEAR                             0x00UL

//EIDB: EI Level Interrupt Bind Register
#if (DEVICE == U2Bx)
#define EIBD232                               *(uint32*)(0xFFF823A0UL)
#define EIBD960                               *(uint32*)(0xFFF82F00UL)
#define EIBD961                               *(uint32*)(0xFFF82F04UL)
#define EIBD360                               *(uint32*)(0xFFF825A0UL)
#define EIBD361                               *(uint32*)(0xFFF825A4UL)
#define EIBD86                                *(uint32*)(0xFFF82158UL)
#define EIBD87                                *(uint32*)(0xFFF8215CUL)
#define EIBD102                               *(uint32*)(0xFFF82198UL)
#elif (DEVICE == U2BxE)
#define EIBD232                               *(uint32*)(0xFFF823A0UL)
#define EIBD960                               *(uint32*)(0xFFF82F00UL)
#define EIBD961                               *(uint32*)(0xFFF82F04UL)
#define EIBD360                               *(uint32*)(0xFFF825A0UL)
#define EIBD361                               *(uint32*)(0xFFF825A4UL)
#define EIBD328                               *(uint32*)(0xFFF825A4UL)
#else
#define EIBD232                               *(uint32*)(0xFFF823A0UL)
#define EIBD368                               *(uint32*)(0xFFF825C0UL)
#define EIBD369                               *(uint32*)(0xFFF825C4UL)
#define EIBD199                               *(uint32*)(0xFFF8231CUL)
#define EIBD200                               *(uint32*)(0xFFF82320UL)
#endif

#define EIBD379                               *(uint32*)(0xFFF825ECUL)
#define EIBD272_U2Bx                          *(uint32*)(0xfff82440UL)

/* OSTM2 */
#define EIBD841_U2Bx                          *(uint32*)(0xfff82d24UL)
#define EIBD104	                             *(uint32*) (0xfff821a0UL)
#define BOUND_PE1                             0x00000001UL
/* TAUJ3I0 */
#define EIBD372                            *(volatile uint32*) (0xfff825d0)
#define GPT_BUFF_SIZE                         0x0100U
#define GPT_LOOP_MASK                         0x00FFU

#define Channel_0                             0x0
#define Channel_1                             0x1
#define Channel_2                             0x2
#define Channel_3                             0x3
#define Channel_4                             0x4

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
#define GPT_NOTIF_USED                  0x0A
/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
/* Global variable to hold the values of GPT */
extern volatile uint8 GaaNotificationEntered_global[10];
extern Std_ReturnType Init_MCAL(void);
extern void sample_end(void);

#endif /* End of APP_GPT_MULTI_SAMPLE_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
