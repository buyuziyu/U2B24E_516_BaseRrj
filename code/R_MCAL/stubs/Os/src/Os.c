/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = Os.c                                                        */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This application file contains the OS Stub functions.                      */
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
/* 2.4.1      30/06/2025     Remove the SW-VERSION from header of file
 * 2.3.1      31/03/2025     Add new volatile for GbSpinlockNothingStatus
 *                           and GbSpinlockAllISRsStatus
 * 2.3.0      28/02/2025     Update SW-VERSION for
 *                           Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.1      31/12/2024     Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0      31/12/2024     Update SW-VERSION 
 *                           for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.1      24/07/2024     Update SW-VERSION to 2.1.1
 * 2.1.0      06/03/2024     Update SW-VERSION to 2.1.0
 * 2.0.1      25/09/2023     Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                          Include Section                                   **
*******************************************************************************/
#include "ComStack_Types.h"
#include "Os.h"
#include "Compiler.h"

/*******************************************************************************
**                            Global Data                                     **
*******************************************************************************/
static uint16 i=0;
#ifdef USE_MULTI_CORE
/* For Multi-Core support */
static volatile boolean GbSpinlockNothingStatus = 0;
static volatile boolean GbSpinlockAllISRsStatus = 0;
#endif
/*******************************************************************************
**                        GetCounterValue                                     **
*******************************************************************************/
StatusType GetCounterValue( CounterType CounterID, TickRefType Value )
{
  if (i == 0xFFFF)
  {
    i = 0x0000;
  }
  i++;
  *Value = i;

  return (E_OK);
}

/* For Multi-Core support */
/*******************************************************************************
**                        GetCoreID                                           **
*******************************************************************************/
CoreIdType GetCoreID(void)
{
  CoreIdType LucRegValues;
  /*
  regID: SR0; selID: 2
  */
  LucRegValues = STSR(0,2);
  /* Return the unique core identifier. */
  return LucRegValues;
}

/* For Multi-Core support */
#ifdef USE_MULTI_CORE
/*******************************************************************************
**                        GetSpinlock                                         **
*******************************************************************************/
StatusType GetSpinlock(uint8 SpinlockType)
{
  /* Check the lock type */
  if (SpinlockNothing == SpinlockType)
  {
    /* Wait for other cores to release the lock flag */
    while(GbSpinlockNothingStatus);
    /* Claim the lock flag */
    GbSpinlockNothingStatus = 1;
  }
  else 
  {
    /* Wait for other cores to release the lock flag */
    while(GbSpinlockAllISRsStatus);
    /* Claim the lock flag */
    GbSpinlockAllISRsStatus = 1;
  }
  /* Disable local core interrupt */
  DISABLE_INTERRUPT();
  return (E_OK);
}

/* For Multi-Core support */
/*******************************************************************************
**                        ReleaseSpinlock                                     **
*******************************************************************************/
StatusType ReleaseSpinlock(uint8 SpinlockType)
{
  /* Check the lock type */
  if (SpinlockNothing == SpinlockType)
  {
    /* Release the lock flag */
    GbSpinlockNothingStatus = 0;
  }
  else 
  {
    /* Release the lock flag */
    GbSpinlockAllISRsStatus = 0;
  }
  /* Enable local core interrupt */
  ENABLE_INTERRUPT();
  return (E_OK);
}
#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
