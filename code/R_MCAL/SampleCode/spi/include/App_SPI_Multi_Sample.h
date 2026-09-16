/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = App_SPI_Multi_Sample.h                                                                              */
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
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 *                     : Update to support for post build variant
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  28/10/2023  : Updated SW-VERSION.
 * 2.0.0:  03/08/2023  : Add content for Global Symbols and add Spi_AllCoreRun
 * 1.5.0:  07/03/2023  : Updated SW-VERSION
 * 1.4.2:  02/03/2022  : Updated SW-VERSION
 * 1.3.2:  04/09/2021  : Move the inclusion of SchM_Spi.h into specifi application of each PE.
 * 1.3.1:  07/05/2021  : Add inclusion of SchM_Spi.h
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 *                       Add functions PassTo_PE1 and PassTo_PE0 to improve sync process.
 * 1.0.1:  19/05/2020  : Removed polling-flags to utilize barrier-sync
 * 1.0.0:  14/03/2019  : Initial Version
 */
/**********************************************************************************************************************/
#ifndef APP_SPI_MULTI_SAMPLE_H
#define APP_SPI_MULTI_SAMPLE_H

/***********************************************************************************************************************
**                                                Include Section                                                     **
***********************************************************************************************************************/
#include "Std_Types.h"

/***********************************************************************************************************************
**                                                Global Symbols                                                      **
***********************************************************************************************************************/
extern volatile uint8 App_GucKernelExcutionFlag;

#if defined (CCRH)
extern uint32 App_GaaWriteBuffer0[];
extern uint32 App_GaaReadBuffer0[4];
extern uint32 App_GaaWriteBuffer1[];
extern uint32 App_GaaReadBuffer1[4];
#else
extern uint8 App_GaaWriteBuffer0[];
extern uint8 App_GaaReadBuffer0[4];
extern uint8 App_GaaWriteBuffer1[];
extern uint8 App_GaaReadBuffer1[4];
#endif

#if defined (CCRH)
extern uint32 App_GaaWriteBuffer0_Variant1[];
extern uint32 App_GaaReadBuffer0_Variant1[4];
extern uint32 App_GaaWriteBuffer1_Variant1[];
extern uint32 App_GaaReadBuffer1_Variant1[4];
#else
extern uint8 App_GaaWriteBuffer0_Variant1[];
extern uint8 App_GaaReadBuffer0_Variant1[4];
extern uint8 App_GaaWriteBuffer1_Variant1[];
extern uint8 App_GaaReadBuffer1_Variant1[4];
#endif

#if defined (CCRH)
extern uint32 App_GaaWriteBuffer0_Variant2[];
extern uint32 App_GaaReadBuffer0_Variant2[4];
extern uint32 App_GaaWriteBuffer1_Variant2[];
extern uint32 App_GaaReadBuffer1_Variant2[4];
#else
extern uint8 App_GaaWriteBuffer0_Variant2[];
extern uint8 App_GaaReadBuffer0_Variant2[4];
extern uint8 App_GaaWriteBuffer1_Variant2[];
extern uint8 App_GaaReadBuffer1_Variant2[4];
#endif

extern volatile uint8 App_Finish_Variant;

/***********************************************************************************************************************
**                                                Global Data Type                                                    **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Global Function Prototypes                                          **
***********************************************************************************************************************/
extern Std_ReturnType Init_MCAL(void);
extern void Guard_Enable_PE(void);
extern void Spi_IvtInit_Variant(void);
extern void Spi_Init_Barrier_Sync(void);
extern void Spi_PassTo_PE0(void);
extern void Spi_PassTo_PE1(void);
extern void Spi_AllCoreRun(void);

/***********************************************************************************************************************
**                                                End of File                                                         **
***********************************************************************************************************************/
#endif
