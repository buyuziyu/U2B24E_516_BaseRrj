/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = DIO                                                         */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.             */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for DIO Driver Component             */
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
/*              Devices:        U2B6-E                                       */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 1.0.0:   13/02/2025  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_Dio_Device_Sample.h"
#include "Dio.h"

/*******************************************************************************
**                      Defines                                               **
*******************************************************************************/
volatile boolean GblSyncFlag = 0;
/*******************************************************************************
**                      Global variables                                      **
*******************************************************************************/

/*******************************************************************************
**                      User Function Prototypes                              **
*******************************************************************************/

/*******************************************************************************
**                      Main Function Definitions                             **
*******************************************************************************/
void sample_end(void)
{
  while (1)
  {
    /* No action required*/
  }
}

/*******************************************************************************
**                      Watchdog Initialization                               **
*******************************************************************************/
void Wdg_Init(void)
{
  /* No Action Required*/
}

/*******************************************************************************
**                      Mcu Initialization                                    **
*******************************************************************************/
void Mcu_Init(void)
{
  /* No Action Required*/
}

/*******************************************************************************
**                      Port Initialization                                   **
*******************************************************************************/
void Port_Init(void)
{
  /*Enable Write Protection*/
  PKCPROT = 0xA5A5A501UL;
  PWE = 0x00002000UL;
  /*Disable Write Protection*/
  PKCPROT = 0xA5A5A500UL;
  /* Initialize Output data Low level, Output mode, turn Input Buffer ON,
  turn Bidirectional Control ON, turn DIO mode on for P02*/
  PSR02 = (uint32)0xFFFF0000UL;
  PMSR02 = (uint32)0xFFFF0000UL;
  PIBC02 = (uint16)0x0038U;
  PBDC02 = (uint16)0x0038U;
  PMCSR02 = (uint32)0xFFFF0000UL;
  /* Initialize Output data Low level, Output mode, turn Input Buffer ON,
  turn Bidirectional Control ON, turn DIO mode on for P10*/
  PSR10 = (uint32)0xFFFF0000UL;
  PMSR10 = (uint32)0xFFFF0000UL;
  PIBC10 = (uint16)0x003FU;
  PBDC10 = (uint16)0x003FU;
  PMCSR10 = (uint32)0xFFFF0000UL;
  
   /* Initialize Output data Low level, Output mode, turn Input Buffer ON,
  turn Bidirectional Control ON, turn DIO mode on for P22*/
  PSR22 = (uint32)0xFFFF0000UL;
  PMSR22 = (uint32)0xFFFF0000UL;
  PIBC22 = (uint16)0x003FU;
  PBDC22 = (uint16)0x003FU;
  PMCSR22 = (uint32)0xFFFF0000UL;
  
   /* Initialize Output data Low level, Output mode, turn Input Buffer ON,
  turn Bidirectional Control ON, turn DIO mode on for P20*/
  PSR20 = (uint32)0xFFFF0000UL;
  PMSR20 = (uint32)0xFFFF0000UL;
  PIBC20 = (uint16)0x003FU;
  PBDC20 = (uint16)0x003FU;
  PMCSR20 = (uint32)0xFFFF0000UL;
}

/*******************************************************************************
**                      PE Guard Initialization                               **
*******************************************************************************/
void Guard_Enable_PE(void)
{
  PBGKCPROT(20) = DIO_KCPROT_SET;
  PBGCKPROT1(20, 0) |= (uint32)((0x01<<1)|(0x01<<2));
  PBGKCPROT(20) = DIO_KCPROT_CLR;
}

void Guard_Init(void)
{
  PBGKCPROT(20) = DIO_KCPROT_SET;
  PBGCKPROT1(21, 6) |= (uint32)((0x01<<1)|(0x01<<2));
  PBGKCPROT(20) = DIO_KCPROT_CLR;
 
  PBGKCPROT(20) = DIO_KCPROT_SET;
  PBGCKPROT1(21, 7) |= (uint32)((0x01<<1)|(0x01<<2));
  PBGKCPROT(20) = DIO_KCPROT_CLR;
  
  PBGKCPROT(20) = DIO_KCPROT_SET;
  PBGCKPROT1(21, 15) |= (uint32)((0x01<<1)|(0x01<<2));
  PBGKCPROT(20) = DIO_KCPROT_CLR;
  
  PBGKCPROT(20) = DIO_KCPROT_SET;
  PBGCKPROT1(21, 13) |= (uint32)((0x01<<1)|(0x01<<2));
  PBGKCPROT(20) = DIO_KCPROT_CLR;
}
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
