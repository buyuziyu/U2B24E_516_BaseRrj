/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_LIN_Common_Sample.h                                     */
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains macros/function prototypes/variables required for       */
/* source application file.                                                   */
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
 * 2.4.0:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *                       Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 *                       Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL
 *                       Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION
 * 2.1.1:  30/08/2024  : As part of U2BxE support, following changes are made:
 *                       1. Add precondition for U2BxE
 *                       As part of multi-core and post build variant support,
 *                       following changes are made:
 *                       1. Replace marco TEST_LIN_WAIT_500MS with LIN_WAIT_MS(t)
 *                       2. Add marco GucStubVariantFlag0, GucStubVariantFlag1
 * 2.0.1:  29/10/2023  : Update macro "LIN_MAX_TIMEOUT_COUNT" for U2Cx device
 * 2.0.0:  18/07/2023  : Initialize version for SA support multi-core
 */
/******************************************************************************/
#ifndef APP_LIN_MULTI_SAMPLE_H
#define APP_LIN_MULTI_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Compiler.h"
#include "Std_Types.h"
#include "Lin.h"
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define LIN_COUNT_INITIAL_VALUE           (uint8)0x00
#define LIN_DATA_SIZE                     (uint8)0x08
#define LIN_WAIT_5MS                      (uint8)0x05
#define LIN_SEND_PID                      (uint8)0xDD
#define LIN_RESP_PID                      (uint8)0x39
#define LIN_CHANNEL_0                     (uint8)0x00
#define LIN_CHANNEL_1                     (uint8)0x01
#define LIN_CHANNEL_2                     (uint8)0x02
#define LIN_CHANNEL_5                     (uint8)0x05
#if (DEVICE == E2x)
#define LIN_MAX_TIMEOUT_COUNT             (uint8)0x04
#elif (DEVICE == U2Ax)
#define LIN_MAX_TIMEOUT_COUNT             (uint8)0x03
#elif (DEVICE == U2Bx || DEVICE == U2BxE)
#define LIN_MAX_TIMEOUT_COUNT             (uint8)0x04
#elif (DEVICE == U2Cx)
#define LIN_MAX_TIMEOUT_COUNT             (uint8)0x04
#endif //#if (DEVICE == E2x)
#define NUM_CPU                           (uint8)0x06U

#define PEID_PE1_VALUE                    0x00000001UL
#define PEID_PE2_VALUE                    0x00000002UL
#define LIN_EIBD2                         ((volatile uint32*)0xFFF82000UL)
#define LIN_WAIT_MS(t)  { volatile uint32 cnt; \
  for ( cnt = 0;cnt < (((uint32)360 * ((uint32)t)) + (uint32)1);cnt++ ); }

/* Transfer time for each baudrate */
#define TEST_LIN_TRANSFER_DELAY_1000      (16647336)      /* 125 ms  */
#define TEST_LIN_TRANSFER_DELAY_1200      (13877219)      /* 104.2 ms*/
#define TEST_LIN_TRANSFER_DELAY_2400      (6938609)       /* 52.1 ms */
#define TEST_LIN_TRANSFER_DELAY_4800      (3469304)       /* 26 ms   */
#define TEST_LIN_TRANSFER_DELAY_9600      (1731323)       /* 13 ms   */
#define TEST_LIN_TRANSFER_DELAY_10417     (1598144)       /* 12 ms   */
#define TEST_LIN_TRANSFER_DELAY_14400     (1155991)       /* 8.68 ms */
#define TEST_LIN_TRANSFER_DELAY_19200     (865661)        /* 6.5 ms  */
#define TEST_LIN_TRANSFER_DELAY_20000     (832366)        /* 6.25 ms */

extern volatile uint8 GucStubInitFlag;
extern volatile uint8 GucStubVariantFlag0;
extern volatile uint8 GucStubVariantFlag1;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern void Init_MCAL(void);

extern void sample_end(void);

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#endif /* APP_LIN_COMMON_SAMPLE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
