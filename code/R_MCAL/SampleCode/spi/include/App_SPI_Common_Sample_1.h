/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = App_SPI_Common_Sample_1.h                                                                           */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2019-2025 Renesas Electronics Corporation                                                             */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the implementations AUTOSAR specified APIs for SPI handler.                                     */
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
 * 2.5.1: 30/06/2025:  Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D) Release
 *                       Update Number of check points, remove macro CCRH
 * 2.4.0: 31/05/2025   : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 *                     : Add new function define "Gpt_Init_1" to support for post build variant on core 1
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  28/10/2023  : Updated SW-VERSION.
 * 2.0.0:  03/08/2023  : Remove instance
 * 1.5.0:  07/03/2023  : Updated SW-VERSION
 * 1.4.3:  18/05/2022  : Add macro cover
 * 1.4.2:  02/03/2022  : Updated SW-VERSION
 * 1.2.1:  04/09/2021  : Add inclusion of SchM_Spi_59_Inst1.h for PE1
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  06/03/2019  : Initial version
 */
/******************************************************************************/
#ifndef APP_SPI_COMMON_SAMPLE_1_H
#define APP_SPI_COMMON_SAMPLE_1_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Compiler.h"
#include "SchM_Spi.h"

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                          Defines                                           **
*******************************************************************************/
#define SPI_TRUE            (boolean)1
#define SPI_FALSE           (boolean)0

/* Number of check points */
#define SPI_CHECK_POINTS    100U

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
extern void Spi_Init_PE1(void);
extern void Wdg_Init(void);
extern void Mcu_Init(void);
extern void Port_Init(void);
extern void Guard_Init(void);
extern void Gpt_Init(void);
extern void Gpt_Start(void);
extern void Gpt_Stop(void);
extern void Gpt_Init_1(void);
extern _INTERRUPT_ void Timer_Task_1(void);
extern void Spi_Kernel_AsyncTransmit(void);
extern void Spi_Kernel_SyncTransmit(void);
extern void Spi_Kernel_Cancel(void);
extern void Spi_Kernel_ForceCancel(void);

#endif /* APP_SPI_COMMON_SAMPLE_1_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
