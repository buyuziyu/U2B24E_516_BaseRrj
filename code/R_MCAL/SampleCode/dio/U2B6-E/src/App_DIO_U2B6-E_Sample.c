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
 * 2.4.1:   20/06/2025  : Update test app to support core max
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
Std_VersionInfoType VersionInfo;

/* Local variable to store the return value of the Dio_ReadPort() and
   Dio_ReadChannelGroup() */
volatile Dio_PortLevelType LddPortLevel;

/* Local variable to store the return value of the Dio_ReadChannel() */
volatile Dio_LevelType LddLevel;

/* Local variable to store the test result */
uint8 GaaTestResult[13];

/*******************************************************************************
**                      User Function Prototypes                              **
*******************************************************************************/
void Wdg_Init(void);
void Mcu_Init(void);
void Port_Init(void);
void Guard_Enable_PE(void);
void Guard_Init(void);
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

int main(void)
#if defined(RUN_OTHER_PE)
{
  Guard_Enable_PE();
  Guard_Init();
  while(1);
}
#if defined(RUN_PE1)
int main_PE1(void)
#elif defined(RUN_PE2)
int main_PE2(void)
#elif defined(RUN_PE3)
int main_PE3(void)
#elif defined(RUN_PE4)
int main_PE4(void)
#elif defined(RUN_PE5)
int main_PE5(void)
#elif defined(RUN_PE6)
int main_PE6(void)
#endif
#endif
{
  /* Initialize Watchdog */
  Wdg_Init();

  /* Initialize MCU */
  Mcu_Init();

  /* Initialize PORT */
  Port_Init();
  /*============================================================*/
  /* VersionInfo Check                                          */
  /*============================================================*/
  /* To Get Version Information of the DIO Driver component */
  Dio_GetVersionInfo(&VersionInfo);
  if ((DIO_VENDOR_ID == VersionInfo.vendorID) &&
      (DIO_MODULE_ID == VersionInfo.moduleID) &&
     ((uint8)DIO_SW_MAJOR_VERSION == VersionInfo.sw_major_version) &&
     ((uint8)DIO_SW_MINOR_VERSION == VersionInfo.sw_minor_version) &&
     ((uint8)DIO_SW_PATCH_VERSION == VersionInfo.sw_patch_version))
  {
    GaaTestResult[0] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult[0] = (uint8)FALSE;
  }

  /*============================================================*/
  /* Channel-based Check                                        */
  /*============================================================*/
  /* To Set the Channel value */
  Dio_WriteChannel(DioConf_DioChannel_UserChannel_02_03, (Dio_LevelType)0x01);
  /* To Read the Output Data value */
  LddLevel = Dio_ReadChannelOutputValue(DioConf_DioChannel_UserChannel_02_03);
  if ((Dio_LevelType)0x01 == LddLevel)
  {
    GaaTestResult[1] = (uint8)TRUE;

    /* To Read the Channel Pin level */
    LddLevel = Dio_ReadChannel(DioConf_DioChannel_UserChannel_02_03);
    if ((Dio_LevelType)0x01 == LddLevel)
    {
      GaaTestResult[2] = (uint8)TRUE;
    }
    else
    {
      GaaTestResult[2] = (uint8)FALSE;
    }
  }
  else
  {
    GaaTestResult[1] = (uint8)FALSE;
    GaaTestResult[2] = (uint8)FALSE;
  }

  /* To Set the Channel value */
  Dio_WriteChannel(DioConf_DioChannel_UserChannel_02_03, (Dio_LevelType)0x00);
  /* To Read the Output Data value */
  LddLevel = Dio_ReadChannelOutputValue(DioConf_DioChannel_UserChannel_02_03);
  if ((Dio_LevelType)0x00 == LddLevel)
  {
    GaaTestResult[3] = (uint8)TRUE;

    /* To Read the Channel Pin level */
    LddLevel = Dio_ReadChannel(DioConf_DioChannel_UserChannel_02_03);
    if ((Dio_LevelType)0x00 == LddLevel)
    {
      GaaTestResult[4] = (uint8)TRUE;
    }
    else
    {
      GaaTestResult[4] = (uint8)FALSE;
    }
  }
  else
  {
    GaaTestResult[3] = (uint8)FALSE;
    GaaTestResult[4] = (uint8)FALSE;
  }

  /*============================================================*/
  /* Port-based Check                                           */
  /*============================================================*/
  /* To Set the Port value */
  Dio_WritePort(DioConf_DioPort_UserPort_PG10, (Dio_PortLevelType)0x003F);
  /* To Read the Port value */
  LddPortLevel = Dio_ReadPort(DioConf_DioPort_UserPort_PG10);
  if ((Dio_PortLevelType)0x003F ==
      (Dio_PortLevelType)(LddPortLevel & (Dio_PortLevelType)0x003F))
  {
    GaaTestResult[5] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult[5] = (uint8)FALSE;
  }

  /*============================================================*/
  /* Channnel Group-based Check                                 */
  /*============================================================*/
  /* To Set the ChannelGroup value */
  Dio_WriteChannelGroup(DioConf_DioChannelGroup_UserChannelGroup_PG10,
                        (Dio_PortLevelType)0x0018);
  /* To Read the ChannelGroup Output value  */
  LddPortLevel = Dio_ReadChannelGroupOutputValue(DioConf_DioChannelGroup_UserChannelGroup_PG10);
  if ((Dio_PortLevelType)0x0018 == LddPortLevel)
  {
    GaaTestResult[6] = (uint8)TRUE;

    /* To Read the ChannelGroup Level value  */
    LddPortLevel = Dio_ReadChannelGroup(DioConf_DioChannelGroup_UserChannelGroup_PG10);
    if ((Dio_PortLevelType)0x0018 == LddPortLevel)
    {
      GaaTestResult[7] = (uint8)TRUE;
    }
    else
    {
      GaaTestResult[7] = (uint8)FALSE;
    }
  }
  else
  {
    GaaTestResult[6] = (uint8)FALSE;
    GaaTestResult[7] = (uint8)FALSE;
  }

  /*============================================================*/
  /* Masked Write Port Check                                    */
  /*============================================================*/
  /* Service to set the value of a given port with required mask */
  Dio_MaskedWritePort(DioConf_DioPort_UserPort_PG02,
                      (Dio_PortLevelType)0x0038, (Dio_PortLevelType)0x0028);
  LddPortLevel = Dio_ReadPort(DioConf_DioPort_UserPort_PG02);
  if ((Dio_PortLevelType)0x0028 ==
      (Dio_PortLevelType)(LddPortLevel & (Dio_PortLevelType)0x0038))
  {
    GaaTestResult[8] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult[8] = (uint8)FALSE;
  }

  /*============================================================*/
  /* Flip Channel Check                                         */
  /*============================================================*/
  Dio_WriteChannel(DioConf_DioChannel_UserChannel_02_03, (Dio_LevelType)0x01);
  LddLevel = Dio_ReadChannel(DioConf_DioChannel_UserChannel_02_03);
  if ((Dio_LevelType)0x01 == LddLevel)
  {
    GaaTestResult[9] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult[9] = (uint8)FALSE;
  }
  /*
   * Service to flip (change from 1 to 0 or from 0 to 1) the level of
   * a channel and return the level of the channel after flip
   */
  LddLevel = Dio_FlipChannel(DioConf_DioChannel_UserChannel_02_03);
  LddLevel = Dio_ReadChannel(DioConf_DioChannel_UserChannel_02_03);
  if ((Dio_LevelType)0x00 == LddLevel)
  {
    GaaTestResult[10] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult[10] = (uint8)FALSE;
  }

  Dio_WriteChannel(DioConf_DioChannel_UserChannel_02_03, (Dio_LevelType)0x00);
  LddLevel = Dio_ReadChannel(DioConf_DioChannel_UserChannel_02_03);
  if ((Dio_LevelType)0x00 == LddLevel)
  {
    GaaTestResult[11] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult[11] = (uint8)FALSE;
  }
  LddLevel = Dio_FlipChannel(DioConf_DioChannel_UserChannel_02_03);
  LddLevel = Dio_ReadChannel(DioConf_DioChannel_UserChannel_02_03);
  if ((Dio_LevelType)0x01 == LddLevel)
  {
    GaaTestResult[12] = (uint8)TRUE;
  }
  else
  {
    GaaTestResult[12] = (uint8)FALSE;
  }

  sample_end();

  return 0;
}
/* End of main() function */

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
  PWE = 0x00000000UL;
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
}

/*******************************************************************************
**                      PE Guard Initialization                               **
*******************************************************************************/
void Guard_Enable_PE(void)
{
  PBGKCPROT(20) = DIO_KCPROT_SET;
  PBGCKPROT1(20, 0) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4)|(0x01<<5)|(0x01<<6));
  PBGKCPROT(20) = DIO_KCPROT_CLR;
}

void Guard_Init(void)
{
  PBGKCPROT(20) = DIO_KCPROT_SET;
  PBGCKPROT1(21, 6) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4)|(0x01<<5)|(0x01<<6));
  PBGKCPROT(20) = DIO_KCPROT_CLR;
 
  PBGKCPROT(20) = DIO_KCPROT_SET;
  PBGCKPROT1(21, 7) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4)|(0x01<<5)|(0x01<<6));
  PBGKCPROT(20) = DIO_KCPROT_CLR;
  
  PBGKCPROT(20) = DIO_KCPROT_SET;
  PBGCKPROT1(21, 15) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4)|(0x01<<5)|(0x01<<6));
  PBGKCPROT(20) = DIO_KCPROT_CLR;
  
  PBGKCPROT(20) = DIO_KCPROT_SET;
  PBGCKPROT1(21, 13) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4)|(0x01<<5)|(0x01<<6));
  PBGKCPROT(20) = DIO_KCPROT_CLR;
}

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
