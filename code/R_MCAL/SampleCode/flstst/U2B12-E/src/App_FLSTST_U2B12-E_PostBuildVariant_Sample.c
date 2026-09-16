/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_FLSTST_U2B12-E_Sample.c                                 */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for FLSTST Driver Component          */
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
/*              Devices:        U2B12-E                                       */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 1.4.1:  30/06/2025  : Update SW-VERSION
 * 1.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E 
 * 1.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D 
 *                       Final Relase
 * 1.0.0:  15/07/2024  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_FLSTST_Device_Sample.h"
#include "rh850_Types.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* Assign CRC signature initial value to be stored in section CRC32_STORE */
#pragma ghs section rodata = ".FLSTST_CRCSIG_STORE"
const uint8 GulFgndCrcSignature_Variant1[] = {0xc7, 0x5e};
const uint8 GulBgndCrcSignature_Variant1[] = {0x32, 0x05};
#pragma ghs section rodata = ".FLSTST_CRCSIG_STORE_1"
const uint8 GulFgndCrcSignature_Variant2[] = {0xa8, 0x88, 0x3d, 0x76};
const uint8 GulBgndCrcSignature_Variant2[] = {0x4f, 0x20, 0x48, 0x94};
#pragma ghs section rodata = default

/******************************************************************************
**                          End of File                                      **
*******************************************************************************/
