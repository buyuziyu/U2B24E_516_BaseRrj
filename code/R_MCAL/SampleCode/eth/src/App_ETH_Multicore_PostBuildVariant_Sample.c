/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_ETH_Multicore_PostBuildVariant_Sample.c                 */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.       */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for ETH Driver Component             */
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
 * 2.4.1: 30/06/2025    : Remove the SW-VERSION from header of file
 * 2.4.0: 30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.1: 31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0: 28/02/2025    : Added GblInitStatus, declare Guard_Enable_PE();
 *                      : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.0: 31/12/2024    : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2: 30/09/2024    : Update SW-VERSION to 2.1.2
 * 2.0.2: 15/04/2024    : Initial Version.
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/

#include "App_ETH_Multi_Sample.h"
#include "App_ETH_Device_Sample.h"
#include "App_ETH_Common_Sample_0.h"
#include "App_ETH_Common_Sample_1.h"

/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
volatile uint8 GblInitStatus[] = { 0, 0 };
/******************************************************************************/
/* busy waiting                                                               */
/******************************************************************************/
void wait_msec(uint32 ms)
{
  volatile uint32 i, loopLimit;
  loopLimit = ms * (1000 * 1000 / 4);
  loopLimit = loopLimit / 2;
  for (i=0; i < loopLimit; i++);
}

/******************************************************************************/
/* test OK                                                                    */
/******************************************************************************/
void sample_end(void)
{
  /* The transmitted message and the received message matched.(OK) */
  while (1){};
}

/******************************************************************************/
/* test NG                                                                    */
/******************************************************************************/
void sample_NG_end(void)
{
  /* The transmitted message and receiving message are different.(NG) */
  while (1){};
}

  /************************** Initilazation  *****************************/
void Init_MCAL(void)
{
#ifdef RUN_OTHER_PE
Guard_Enable_PE();
while(1);
}
#ifdef RUN_PE1
int main_PE1(void)
#endif
#ifdef RUN_PE2
int main_PE2(void)
#endif
#ifdef RUN_PE3
int main_PE3(void)
#endif
#ifdef RUN_PE4
int main_PE4(void)
#endif
#ifdef RUN_PE5
int main_PE5(void)
#endif
{
    volatile uint32 count;
    while (count < 80000) {
        count++;
    };
    Guard_Init();
#endif
  /* Initialize Clock */
  Clock_Init();

  /* Initialize MCU */
  Mcu_Init();

  /* Initialize WDG */
  Wdg_Init();

  /* Initialize PORT for Ethernet */
  Port_Init();

  #if !defined RUN_OTHER_PE && (defined ETH_U2Cx_USED || defined ETH_U2Ax_USED)
  Guard_Enable_PE();
  #endif
}

/******************************************************************************
**                           Notification Functions                          **
******************************************************************************/


/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
