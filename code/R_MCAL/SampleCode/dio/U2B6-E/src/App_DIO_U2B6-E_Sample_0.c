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
/*              Devices:        U2B24-E                                       */
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

/*******************************************************************************
**                      Global variables                                      **
*******************************************************************************/
/* Global variable to store the version information of the DIO Driver
   Component */
Std_VersionInfoType VersionInfo_PE0;

/* Local variable to store the return value of the Dio_ReadPort() and
   Dio_ReadChannelGroup() */
volatile Dio_PortLevelType LddPortLevel_PE0;

/* Local variable to store the return value of the Dio_ReadChannel() */
volatile Dio_LevelType LddLevel_PE0;

/* Local variable to store the test result */
uint8 GaaTestResult_PE0[13];

/*******************************************************************************
**                      User Function Prototypes                              **
*******************************************************************************/

/*******************************************************************************
**                      Main Function Definitions                             **
*******************************************************************************/
int main(void)
{
  /* Initialize Watchdog */
  Wdg_Init();

  /* Initialize MCU */
  Mcu_Init();

  /* Initialize PORT */
  Port_Init();
  
  Guard_Enable_PE();
  
  GblSyncFlag = 1;
  /*============================================================*/
  /* VersionInfo_PE0 Check                                          */
  /*============================================================*/
  /* To Get Version Information of the DIO Driver component */
  Dio_GetVersionInfo(&VersionInfo_PE0);
  if ((DIO_VENDOR_ID == VersionInfo_PE0.vendorID) &&
      (DIO_MODULE_ID == VersionInfo_PE0.moduleID) &&
     ((uint8)DIO_SW_MAJOR_VERSION == VersionInfo_PE0.sw_major_version) &&
     ((uint8)DIO_SW_MINOR_VERSION == VersionInfo_PE0.sw_minor_version) &&
     ((uint8)DIO_SW_PATCH_VERSION == VersionInfo_PE0.sw_patch_version))
  {
    GaaTestResult_PE0[0] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult_PE0[0] = (uint8)FALSE;
  }

  /*============================================================*/
  /* Channel-based Check                                        */
  /*============================================================*/
  /* To Set the Channel value */
  Dio_WriteChannel(DioConf_DioChannel_UserChannel_02_03, (Dio_LevelType)0x01);
  /* To Read the Output Data value */
  LddLevel_PE0 = Dio_ReadChannelOutputValue(DioConf_DioChannel_UserChannel_02_03);
  if ((Dio_LevelType)0x01 == LddLevel_PE0)
  {
    GaaTestResult_PE0[1] = (uint8)TRUE;

    /* To Read the Channel Pin level */
    LddLevel_PE0 = Dio_ReadChannel(DioConf_DioChannel_UserChannel_02_03);
    if ((Dio_LevelType)0x01 == LddLevel_PE0)
    {
      GaaTestResult_PE0[2] = (uint8)TRUE;
    }
    else
    {
      GaaTestResult_PE0[2] = (uint8)FALSE;
    }
  }
  else
  {
    GaaTestResult_PE0[1] = (uint8)FALSE;
    GaaTestResult_PE0[2] = (uint8)FALSE;
  }

  /* To Set the Channel value */
  Dio_WriteChannel(DioConf_DioChannel_UserChannel_02_03, (Dio_LevelType)0x00);
  /* To Read the Output Data value */
  LddLevel_PE0 = Dio_ReadChannelOutputValue(DioConf_DioChannel_UserChannel_02_03);
  if ((Dio_LevelType)0x00 == LddLevel_PE0)
  {
    GaaTestResult_PE0[3] = (uint8)TRUE;

    /* To Read the Channel Pin level */
    LddLevel_PE0 = Dio_ReadChannel(DioConf_DioChannel_UserChannel_02_03);
    if ((Dio_LevelType)0x00 == LddLevel_PE0)
    {
      GaaTestResult_PE0[4] = (uint8)TRUE;
    }
    else
    {
      GaaTestResult_PE0[4] = (uint8)FALSE;
    }
  }
  else
  {
    GaaTestResult_PE0[3] = (uint8)FALSE;
    GaaTestResult_PE0[4] = (uint8)FALSE;
  }
  /*============================================================*/
  /* Port-based Check                                           */
  /*============================================================*/
  /* To Set the Port value */
  Dio_WritePort(DioConf_DioPort_UserPort_PG20, (Dio_PortLevelType)0x0049);
  /* To Read the Port value */
  LddPortLevel_PE0 = Dio_ReadPort(DioConf_DioPort_UserPort_PG20);
  
  if ((Dio_PortLevelType)0x0049 ==
      (Dio_PortLevelType)(LddPortLevel_PE0 & (Dio_PortLevelType)0x0049))
  {
    GaaTestResult_PE0[5] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult_PE0[5] = (uint8)FALSE;
  }
  /*============================================================*/
  /* Channnel Group-based Check                                 */
  /*============================================================*/
  /* To Set the ChannelGroup value */
  Dio_WriteChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_PG33,
                        (Dio_PortLevelType)0x007F);
  /* To Read the ChannelGroup Output value  */
  LddPortLevel_PE0 = Dio_ReadChannelGroupOutputValue(DioConf_DioChannelGroup_DioChannelGroup_PG33);
  if ((Dio_PortLevelType)0x007F == LddPortLevel_PE0)
  {
    GaaTestResult_PE0[6] = (uint8)TRUE;

    /* To Read the ChannelGroup Level value  */
    LddPortLevel_PE0 = Dio_ReadChannelGroup(DioConf_DioChannelGroup_DioChannelGroup_PG33);
    if ((Dio_PortLevelType)0x007F == LddPortLevel_PE0)
    {
      GaaTestResult_PE0[7] = (uint8)TRUE;
    }
    else
    {
      GaaTestResult_PE0[7] = (uint8)FALSE;
    }
  }
  else
  {
    GaaTestResult_PE0[6] = (uint8)FALSE;
    GaaTestResult_PE0[7] = (uint8)FALSE;
  }
  /*============================================================*/
  /* Masked Write Port Check                                    */
  /*============================================================*/
  /* Service to set the value of a given port with required mask */
  Dio_MaskedWritePort(DioConf_DioPort_UserPort_PG02,
                      (Dio_PortLevelType)0x0038, (Dio_PortLevelType)0x0018);
  LddPortLevel_PE0 = Dio_ReadPort(DioConf_DioPort_UserPort_PG02);
  if ((Dio_PortLevelType)0x0018 ==
      (Dio_PortLevelType)(LddPortLevel_PE0 & (Dio_PortLevelType)0x0038))
  {
    GaaTestResult_PE0[8] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult_PE0[8] = (uint8)FALSE;
  }
  /*============================================================*/
  /* Flip Channel Check                                         */
  /*============================================================*/
  Dio_WriteChannel(DioConf_DioChannel_UserChannel_02_03, (Dio_LevelType)0x01);
  LddLevel_PE0 = Dio_ReadChannel(DioConf_DioChannel_UserChannel_02_03);
  if ((Dio_LevelType)0x01 == LddLevel_PE0)
  {
    GaaTestResult_PE0[9] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult_PE0[9] = (uint8)FALSE;
  }
  /*
   * Service to flip (change from 1 to 0 or from 0 to 1) the level of
   * a channel and return the level of the channel after flip
   */
  LddLevel_PE0 = Dio_FlipChannel(DioConf_DioChannel_UserChannel_02_03);
  LddLevel_PE0 = Dio_ReadChannel(DioConf_DioChannel_UserChannel_02_03);
  if ((Dio_LevelType)0x00 == LddLevel_PE0)
  {
    GaaTestResult_PE0[10] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult_PE0[10] = (uint8)FALSE;
  }

  Dio_WriteChannel(DioConf_DioChannel_UserChannel_02_03, (Dio_LevelType)0x00);
  LddLevel_PE0 = Dio_ReadChannel(DioConf_DioChannel_UserChannel_02_03);
  if ((Dio_LevelType)0x00 == LddLevel_PE0)
  {
    GaaTestResult_PE0[11] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult_PE0[11] = (uint8)FALSE;
  }
  LddLevel_PE0 = Dio_FlipChannel(DioConf_DioChannel_UserChannel_02_03);
  LddLevel_PE0 = Dio_ReadChannel(DioConf_DioChannel_UserChannel_02_03);
  if ((Dio_LevelType)0x01 == LddLevel_PE0)
  {
    GaaTestResult_PE0[12] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult_PE0[12] = (uint8)FALSE;
  }

  sample_end();

  return 0;
}
/* End of main() function */

/*******************************************************************************
**                      Watchdog Initialization                               **
*******************************************************************************/

/*******************************************************************************
**                      Mcu Initialization                                    **
*******************************************************************************/
/*******************************************************************************
**                      Port Initialization                                   **
*******************************************************************************/
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
