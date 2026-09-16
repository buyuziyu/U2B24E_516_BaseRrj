/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_PORT_U2B12-E_Multicore_PostBuildVariant_Sample.c        */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.             */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for PORT Driver Component            */
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
/*              Devices:        U2B12E                                        */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/* 2.3.1:  31/03/2025   : Initial Version                                     */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "App_Port_Device_Multi_Sample.h"
#include "Det.h"
#if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_Port.h"
#endif

/*******************************************************************************
**                      Global Variables                                      **
*******************************************************************************/
volatile uint8 GucStubInitFlag_Variant1 = 0;
volatile uint8 GucRefreshPinFlag_Variant1 = 1;
volatile uint8 GucStubInitFlag_Variant2 = 0;
volatile uint8 GucRefreshPinFlag_Variant2 = 1;  
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
void sample_end(void)
{
  while (1)
  {
    /* No action required*/
  }
}

/*****************************************************************************
                        PORT Module Initialization
*****************************************************************************/
/*******************************************************************************
                              Timer Interrupt routine
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
