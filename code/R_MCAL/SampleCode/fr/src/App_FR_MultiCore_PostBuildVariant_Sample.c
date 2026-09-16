/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_FR_Common_Sample.c                                      */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This application file contains sample test application of FlexRay Driver   */
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
 * 2.4.1:   30/06/2025   : Remove SW-VERSION in file header
 * 2.4.0:   30/06/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00(D) Final Release
 * 2.3.2:   29/04/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 *                       : As part of CCRH support, following changes are made:
 *                         1. Add GucStubInitFlag, GblPE0Done, GblPE1Done with volatile
 *                         2. Add preprocessor directive for macro CCRH
 * 2.3.1:   31/03/2025     : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:   28/02/2025     : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *                           As per multicore support, following changes are made:
 *                           + add GblPE0Done, GblPE1Done
 *                           + Update BoundIntToPE1, sample_end
 * 2.2.1:   31/12/2024     : Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0:   31/12/2024     : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:   31/10/2024     : Update SW-VERSION to 2.1.3
 * 2.1.1:   13/08/2024     : Change Fr_59_Renesas_SetWakeupChannel to call
 *                           channel A instead of channel AB
 * 1.0.0:   16/05/2024     : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_FR_Common_Sample.h"
#include "App_FR_Device_Sample.h"

/*******************************************************************************
**                           Local Definitions                                **
*******************************************************************************/

/*******************************************************************************
**                      Global variables                                      **
*******************************************************************************/
#if defined CCRH
uint8 volatile GucStubInitFlag = 0;
boolean volatile GblPE0Done = FALSE;
boolean volatile GblPE1Done = FALSE;
#else
uint8 GucStubInitFlag = 0;
boolean GblPE0Done = FALSE;
boolean GblPE1Done = FALSE;
#endif
/*Define maximum PE number*/
#define PEID_MAX_VALUE              0x00000001
#define EIBD_BASE_ADDR       ((volatile uint32 *)(0xFFF82000UL))

/*******************************************************************************
**                           Function Definitions                             **
*******************************************************************************/
void sample_end(void)
{
  if (GET_BIT(APP_RESF, APP_MCU_RESF_BIT_POS) == APP_MCU_RST_FLAG_VALUE)
  {
    // Not required
  }
  else if ((GblPE0Done == TRUE) && (GblPE1Done == TRUE))
  {
    /* Initialize the watchdog in the first variant */
    Mcu_Reset();
  }
  else
  {
    //do nothing
  }

  while (1)
  {
    /* No action required*/
  }
}

void BoundIntToPE1(void)
{
  int peid;
  peid = STSR(0, 2);
  if (peid == PEID_MAX_VALUE)
  {
    #if (DEVICE==U2BxE)
    EIBD_BASE_ADDR[919] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[920] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[921] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[922] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[923] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[924] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[925] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[926] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[927] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[928] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[929] = PEID_MAX_VALUE;

    #elif (DEVICE==U2Ax)
    EIBD_BASE_ADDR[634] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[635] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[636] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[637] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[638] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[639] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[640] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[641] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[642] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[643] = PEID_MAX_VALUE;
    EIBD_BASE_ADDR[644] = PEID_MAX_VALUE;
    #endif
  }
  else
  {
    // Do nothing since PE0 is default
  }
}

/*******************************************************************************
                                End of the file
*******************************************************************************/
