/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_MEM_Common_Sample.c                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for MEM Driver Component             */
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
 * 1.1.0:  30/06/2025   : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax release
 * 1.0.3:  25/04/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 1.0.2:  31/03/2025   : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 
 *                        Release
 *                        As part of support U2Bx-E SampleApp on G4KH, 
 *                        following changes are made:
 *                        1. Add function Guard_Enable_PE
 * 1.0.1:  28/02/2025   : Update support U2Cx device 
 * 1.0.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D 
 *                        Final Release
 *                        Extern R_RFD_HOOK_ExitCriticalSection and 
 *                        R_RFD_HOOK_EnterCriticalSection.
 * 0.0.2:  31/10/2024   : As part of ARDAACJ-621, Support downgrade from 
 *                        version AR23-11 to AR22-11.
 *                        Support commonize
 *                        Add API Mem_59_Renesas_ReadImmediate
 * 0.0.1:  30/08/2024   : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_MEM_Common_Sample.h"
#include "App_MEM_Device_Sample.h"
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/
/* Global Variable to maintain application buffer */
uint8 GaaAppBufferForWriteA[MEM_59_RENESAS_APP_BUFFER_SIZE];
uint8 GaaAppBufferForWriteB[MEM_59_RENESAS_APP_BUFFER_SIZE];
uint8 GaaAppBufferForRead[MEM_59_RENESAS_APP_BUFFER_SIZE];
Mem_59_Renesas_LengthType GaaAppBufferForLengthOPBT[MEM_59_RENESAS_ONE] = {0x08UL};
/* Variable used to stored the return value for  API */
Std_ReturnType GddReturnValue;

uint16 GusLoopVar;
volatile boolean GblTestResult;
volatile uint8 GucTestNo;
/* loop counter for Mem_59_Renesas_MainFunction */
volatile Mem_59_Renesas_JobResultType GddJobResultType;
/* Variable used to store the Module Version Info */
Std_VersionInfoType GddVersionInfo;
uint32 GulDelayCounter;
uint32 GulStartAddr;
/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
extern void Wdg_Init(void);
extern void Mcu_Init(void);
extern void Port_Init(void);
void Delay(void);
void TestBufferClear(void);
void TestPass(void);
void TestFail(void);
#if defined(RUN_OTHER_PE)
extern void Guard_Enable_PE(void);
#endif
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
int main(void)
#if defined(RUN_OTHER_PE)
{
  Guard_Enable_PE();
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
  /* Wait for PE0 to enable PBG access */ 
  volatile  uint32 count;
  while (count < 80000) {
     count++;
  };
  uint8 LucWriteCount;
  uint8 *LpTempBuffer;

  /* Initialize test result */
  GblTestResult = MEM_59_RENESAS_SAMPLE_TRUE;

  /* Initialize Watchdog */
  Wdg_Init();
  /* Initialize MCU */
  Mcu_Init();

  /* Initialize PORT */
  Port_Init();
  
  /* Test this sequence 2 times to verify initialization/deinitialization */
  GucTestNo = MEM_59_RENESAS_TWO;

  while (GucTestNo > 0)
  {
    /* 0x0Cul is ID of OPBT, after read done  GaaAppBufferForReturnOPBT is full data of OPBT*/
    Mem_59_Renesas_DataType GaaAppBufferForReturnOPBT[MEM_59_RENESAS_INPUT_OPBT] = {0x0Cul, 0x0ul, 0x0ul, 0x0ul};
    
    /* To get the version of the MEM Driver module */
    Mem_59_Renesas_GetVersionInfo(&GddVersionInfo);
    /* Check for the correctness of version information */
    if ((MEM_59_RENESAS_VENDOR_ID != GddVersionInfo.vendorID) ||
        (MEM_59_RENESAS_MODULE_ID != GddVersionInfo.moduleID) ||
        (MEM_59_RENESAS_SW_MAJOR_VERSION != GddVersionInfo.sw_major_version) ||
        (MEM_59_RENESAS_SW_MINOR_VERSION != GddVersionInfo.sw_minor_version) ||
        (MEM_59_RENESAS_SW_PATCH_VERSION != GddVersionInfo.sw_patch_version))
    {
      GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
    }

    /* Initialize the MEM Driver */
    Mem_59_Renesas_Init(NULL_PTR);

    #if (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)
/**********************************************************************************************************************/
/************************************************ CODE FLASH Routines *************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/******************************************** Request Erase Operation *************************************************/
/**********************************************************************************************************************/
    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      /* Erase 4KB Data Flash starting from address MEM_59_RENESAS_SAMPLE_CF_ADDR1 */
      GddReturnValue = Mem_59_Renesas_Erase(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, 
                                              MEM_59_RENESAS_SAMPLE_CF_ADDR1, MEM_59_RENESAS_SAMPLE_CF_LEN_16KB);
      if (E_OK == GddReturnValue)
      {
        while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
        {
          Mem_59_Renesas_MainFunction();
        }

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }
      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }
/**********************************************************************************************************************/
/************************************* Request blank check Operation (blank case) *************************************/
/**********************************************************************************************************************/
    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      GddReturnValue = Mem_59_Renesas_BlankCheck(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, 
                                                    MEM_59_RENESAS_SAMPLE_CF_ADDR1, MEM_59_RENESAS_SAMPLE_CF_LEN_16KB);

      if (E_OK == GddReturnValue)
      {
        while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
        {
          Mem_59_Renesas_MainFunction();
        }   

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }
      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }
/**********************************************************************************************************************/
/********************************************* Request Write Operation ************************************************/
/**********************************************************************************************************************/
    /* Initial buffer */
    TestBufferClear();

    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult )
    {
      GulStartAddr = MEM_59_RENESAS_SAMPLE_CF_ADDR1;
      LucWriteCount = MEM_59_RENESAS_SAMPLE_CF_LEN_4KB / MEM_59_RENESAS_SAMPLE_CF_WRITE_BURST_SIZE;
      LpTempBuffer = GaaAppBufferForWriteA;

      while ((LucWriteCount > 0) && (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult))
      {
        GddReturnValue = Mem_59_Renesas_Write(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, GulStartAddr,
          LpTempBuffer, MEM_59_RENESAS_SAMPLE_CF_WRITE_BURST_SIZE);

        if (E_OK == GddReturnValue)
        {
          while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
          {
            Mem_59_Renesas_MainFunction();
          }  

          GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

          if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
          {
            GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
          }
        }
        else
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }

        LucWriteCount--;
        GulStartAddr += MEM_59_RENESAS_SAMPLE_CF_WRITE_BURST_SIZE;
        LpTempBuffer += MEM_59_RENESAS_SAMPLE_CF_WRITE_BURST_SIZE;
      }
    }
/**********************************************************************************************************************/
/************************************* Request blank check Operation (not blank case) *********************************/
/**********************************************************************************************************************/
    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      GddReturnValue = Mem_59_Renesas_BlankCheck(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, 
                                                        MEM_59_RENESAS_SAMPLE_CF_ADDR1, MEM_59_RENESAS_SAMPLE_LEN_4KB);
      if (E_OK == GddReturnValue)
      {
        while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
        {
          Mem_59_Renesas_MainFunction();
        }   

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_INCONSISTENT != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }
      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }
/**********************************************************************************************************************/
/************************************************* Request Read Operation *********************************************/
/**********************************************************************************************************************/
    /* Initial buffer */
    TestBufferClear();

    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      GddReturnValue = Mem_59_Renesas_Read(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, MEM_59_RENESAS_SAMPLE_CF_ADDR1,
        GaaAppBufferForRead, MEM_59_RENESAS_SAMPLE_CF_READ_LEN);

      if (E_OK == GddReturnValue)
      {
        while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
        {
          Mem_59_Renesas_MainFunction();
        }  

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }

        for (GusLoopVar = 0; GusLoopVar < MEM_59_RENESAS_SAMPLE_CF_READ_LEN; GusLoopVar++)
        {
          if (GaaAppBufferForRead[GusLoopVar] != GaaAppBufferForWriteA[GusLoopVar])
          {
            GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
            break;
          }
        }
      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }

#if (MEM_59_RENESAS_READIMMEDIATE_API == STD_ON)
/**********************************************************************************************************************/
/*************************************** Request Read Immediate Operation *********************************************/
/**********************************************************************************************************************/
    /* Initial buffer */
    TestBufferClear();

    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      GddReturnValue = Mem_59_Renesas_ReadImmediate(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, MEM_59_RENESAS_SAMPLE_CF_ADDR1,
        GaaAppBufferForRead, MEM_59_RENESAS_SAMPLE_CF_READ_LEN);

      if (E_OK == GddReturnValue)
      {
        while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
        {
          Mem_59_Renesas_MainFunction();
        }  

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }

        for (GusLoopVar = 0; GusLoopVar < MEM_59_RENESAS_SAMPLE_CF_READ_LEN; GusLoopVar++)
        {
          if (GaaAppBufferForRead[GusLoopVar] != GaaAppBufferForWriteA[GusLoopVar])
          {
            GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
            break;
          }
        }
      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }
#endif
/**********************************************************************************************************************/
/****************************************************** Propagate Error ***********************************************/
/**********************************************************************************************************************/
    /* Initial buffer */
    TestBufferClear();

    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      GddReturnValue = Mem_59_Renesas_Read(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, MEM_59_RENESAS_SAMPLE_CF_ADDR1,
        GaaAppBufferForRead, MEM_59_RENESAS_SAMPLE_CF_READ_LEN);

      if (E_OK == GddReturnValue)
      {
        /* Handle read request */
        Mem_59_Renesas_MainFunction();
        /* Propagate Error */
        Mem_59_Renesas_PropagateError(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_ECC_UNCORRECTED != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }
      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }
#endif
#if (MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)
/**********************************************************************************************************************/
/*********************************************** DATA FLASH Routines **************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/******************************************** Request Erase Operation *************************************************/
/**********************************************************************************************************************/
    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      TestBufferClear();
      /* Erase 4KB Data Flash starting from address MEM_59_RENESAS_SAMPLE_ADDR1 */
      GddReturnValue = Mem_59_Renesas_Erase(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, 
                                                          MEM_59_RENESAS_SAMPLE_ADDR1, MEM_59_RENESAS_SAMPLE_LEN_4KB);
      if (E_OK == GddReturnValue)
      {
        while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
        {
          Mem_59_Renesas_MainFunction();
        }   

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }
      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }

/**********************************************************************************************************************/
/************************************** Request blank check Operation (blank case)*************************************/
/**********************************************************************************************************************/
    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      TestBufferClear();
      GddReturnValue = Mem_59_Renesas_BlankCheck(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, 
                                                          MEM_59_RENESAS_SAMPLE_ADDR1, MEM_59_RENESAS_SAMPLE_LEN_4KB);

      if (E_OK == GddReturnValue)
      {
        while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
        {
          Mem_59_Renesas_MainFunction();
        }   

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }
      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }

/**********************************************************************************************************************/
/********************************************** Request Write Operation ***********************************************/
/**********************************************************************************************************************/
    /* Initial buffer */
    TestBufferClear();

    if ( MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult )
    {
      GulStartAddr = MEM_59_RENESAS_SAMPLE_ADDR1;
      LucWriteCount = MEM_59_RENESAS_SAMPLE_LEN_4KB / MEM_59_RENESAS_SAMPLE_WRITE_BURST_SIZE;
      LpTempBuffer = GaaAppBufferForWriteA;

      while ((LucWriteCount > 0) && (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult))
      {
        GddReturnValue = Mem_59_Renesas_Write(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, GulStartAddr,
          LpTempBuffer, MEM_59_RENESAS_SAMPLE_WRITE_BURST_SIZE);

        if (E_OK == GddReturnValue)
        {
          while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
          {
            Mem_59_Renesas_MainFunction();
          }  

          GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

          if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
          {
            GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
          }
        }
        else
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }

        LucWriteCount--;
        GulStartAddr += MEM_59_RENESAS_SAMPLE_WRITE_BURST_SIZE;
        LpTempBuffer += MEM_59_RENESAS_SAMPLE_WRITE_BURST_SIZE;
      }
    }

/**********************************************************************************************************************/
/*************************************** Request blank check Operation (not blank case)********************************/
/**********************************************************************************************************************/
    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      GddReturnValue = Mem_59_Renesas_BlankCheck(MEM_59_RENESAS_SAMPLE_INSTANCE_ID,
                                                          MEM_59_RENESAS_SAMPLE_ADDR1, MEM_59_RENESAS_SAMPLE_LEN_4KB);
      if (E_OK == GddReturnValue)
      {
        while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
        {
          Mem_59_Renesas_MainFunction();
        }   

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_INCONSISTENT != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }
      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }

#if (MEM_59_RENESAS_READIMMEDIATE_API == STD_ON)
/**********************************************************************************************************************/
/***************************************** Request Read Immediate Operation *******************************************/
/**********************************************************************************************************************/
    /* Initial buffer */
    TestBufferClear();

    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      GddReturnValue = Mem_59_Renesas_ReadImmediate(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, MEM_59_RENESAS_SAMPLE_ADDR1,
        GaaAppBufferForRead, MEM_59_RENESAS_SAMPLE_LEN_4KB);

      if (E_OK == GddReturnValue)
      {
        while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
        {
          Mem_59_Renesas_MainFunction();
        }  

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }

        for (GusLoopVar = 0; GusLoopVar < MEM_59_RENESAS_SAMPLE_LEN_4KB; GusLoopVar++)
        {
          if (GaaAppBufferForRead[GusLoopVar] != GaaAppBufferForWriteA[GusLoopVar])
          {
            GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
            break;
          }
        }
      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }
#endif
/**********************************************************************************************************************/
/********************************************* Request Read Operation *************************************************/
/**********************************************************************************************************************/
    /* Initial buffer */
    TestBufferClear();

    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      GddReturnValue = Mem_59_Renesas_Read(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, MEM_59_RENESAS_SAMPLE_ADDR1,
        GaaAppBufferForRead, MEM_59_RENESAS_SAMPLE_LEN_4KB);

      if (E_OK == GddReturnValue)
      {
        while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
        {
          Mem_59_Renesas_MainFunction();
        }  

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }

        for (GusLoopVar = 0; GusLoopVar < MEM_59_RENESAS_SAMPLE_LEN_4KB; GusLoopVar++)
        {
          if (GaaAppBufferForRead[GusLoopVar] != GaaAppBufferForWriteA[GusLoopVar])
          {
            GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
            break;
          }
        }
      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }
#endif

/**********************************************************************************************************************/
/************************************************* Propagate Error ****************************************************/
/**********************************************************************************************************************/
    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      GddReturnValue = Mem_59_Renesas_Read(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, MEM_59_RENESAS_SAMPLE_ADDR1,
        GaaAppBufferForRead, MEM_59_RENESAS_SAMPLE_LEN_4KB);

      if (E_OK == GddReturnValue)
      {
        /* Handle read request */
        Mem_59_Renesas_MainFunction();
        /* Propagate Error */
        Mem_59_Renesas_PropagateError(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_ECC_UNCORRECTED != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }
      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }

#if ((MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON) && (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON))
/**********************************************************************************************************************/
/******************************************* Request Suspend while Erase **********************************************/
/**********************************************************************************************************************/
    /* Initial Buffer */
    TestBufferClear();

    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      /* Erase 4KB Data Flash starting from address MEM_59_RENESAS_SAMPLE_CF_ADDR1 */
      GddReturnValue = Mem_59_Renesas_Erase(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, 
                                              MEM_59_RENESAS_SAMPLE_CF_ADDR1, MEM_59_RENESAS_SAMPLE_CF_LEN_16KB);
      if (E_OK == GddReturnValue)
      {
        Mem_59_Renesas_MainFunction();
        /* Request suspend while Erase is not completed */
        Mem_59_Renesas_Suspend(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        /* Request new erase starting from MEM_59_RENESAS_SAMPLE_ADDR1 */
        GddReturnValue = Mem_59_Renesas_Erase(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, 
                                                          MEM_59_RENESAS_SAMPLE_ADDR1, MEM_59_RENESAS_SAMPLE_LEN_4KB);

        if (E_OK == GddReturnValue)
        {
          while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
          {
            Mem_59_Renesas_MainFunction();
          }

          /* It will return the result of the last job  */
          GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

          if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
          {
            GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
          }
        }
        else
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }
      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }

/**********************************************************************************************************************/
/************************************** Request Write from MEM_59_RENESAS_SAMPLE_ADDR1 ********************************/
/**********************************************************************************************************************/
    /* Initial buffer */
    TestBufferClear();

    if ( MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult )
    {
      GulStartAddr = MEM_59_RENESAS_SAMPLE_ADDR1;
      LucWriteCount  = MEM_59_RENESAS_SAMPLE_LEN_4KB / MEM_59_RENESAS_SAMPLE_WRITE_BURST_SIZE;
      LpTempBuffer = GaaAppBufferForWriteB;

      while ((LucWriteCount > 0) && (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult))
      {
        GddReturnValue = Mem_59_Renesas_Write(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, GulStartAddr,
          LpTempBuffer, MEM_59_RENESAS_SAMPLE_WRITE_BURST_SIZE);

        if (E_OK == GddReturnValue)
        {
          while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
          {
            Mem_59_Renesas_MainFunction();
          }  

          GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

          if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
          {
            GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
          }
        }
        else
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }

        LucWriteCount--;
        GulStartAddr += MEM_59_RENESAS_SAMPLE_WRITE_BURST_SIZE;
        LpTempBuffer += MEM_59_RENESAS_SAMPLE_WRITE_BURST_SIZE;
      }
    }

/**********************************************************************************************************************/
/********************************************** Resume the suspended erase job ****************************************/
/**********************************************************************************************************************/
    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      Mem_59_Renesas_Resume(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

      while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
      {
        Mem_59_Renesas_MainFunction();
      }

      /* It will return the result of the last job  */
      GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);
      if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    }

/**********************************************************************************************************************/
/**************************************** Write from MEM_59_RENESAS_SAMPLE_CF_ADDR1 ***********************************/
/**********************************************************************************************************************/
    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult )
    {
      GulStartAddr = MEM_59_RENESAS_SAMPLE_CF_ADDR1;
      LucWriteCount = MEM_59_RENESAS_SAMPLE_CF_LEN_4KB / MEM_59_RENESAS_SAMPLE_CF_WRITE_BURST_SIZE;
      LpTempBuffer = GaaAppBufferForWriteA;

      while ((LucWriteCount > 0) && (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult))
      {
        GddReturnValue = Mem_59_Renesas_Write(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, GulStartAddr,
          LpTempBuffer, MEM_59_RENESAS_SAMPLE_CF_WRITE_BURST_SIZE);

        if (E_OK == GddReturnValue)
        {
          while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
          {
            Mem_59_Renesas_MainFunction();
          }  

          GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

          if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
          {
            GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
          }
        }
        else
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }

        LucWriteCount--;
        GulStartAddr += MEM_59_RENESAS_SAMPLE_CF_WRITE_BURST_SIZE;
        LpTempBuffer += MEM_59_RENESAS_SAMPLE_CF_WRITE_BURST_SIZE;
      }
    }

/**********************************************************************************************************************/
/********************************************* Request Read Operation *************************************************/
/**********************************************************************************************************************/
    if ( MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult )
    {
      GddReturnValue = Mem_59_Renesas_Read(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, MEM_59_RENESAS_SAMPLE_ADDR1,
        GaaAppBufferForRead, MEM_59_RENESAS_SAMPLE_LEN_4KB);

      if (E_OK == GddReturnValue)
      {
        while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
        {
          Mem_59_Renesas_MainFunction();
        }  

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }

        /* Compare read data and write data */
        LpTempBuffer = GaaAppBufferForRead;

        for (GusLoopVar = 0; GusLoopVar < MEM_59_RENESAS_SAMPLE_LEN_4KB; GusLoopVar++)
        {
          if (*LpTempBuffer != GaaAppBufferForWriteB[GusLoopVar])
          {
            GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
            break;
          }
          LpTempBuffer++;
        }
      }

      if ( MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult )
      {
        GddReturnValue = Mem_59_Renesas_Read(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, MEM_59_RENESAS_SAMPLE_CF_ADDR1,
        GaaAppBufferForRead, MEM_59_RENESAS_SAMPLE_CF_LEN_4KB);

        if (E_OK == GddReturnValue)
        {
          while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
          {
            Mem_59_Renesas_MainFunction();
          }  

          GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

          if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
          {
            GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
          }

          /* Compare read data and write data */
          LpTempBuffer = GaaAppBufferForRead;

          for (GusLoopVar = 0; GusLoopVar < MEM_59_RENESAS_SAMPLE_CF_LEN_4KB; GusLoopVar++)
          {
            if (*LpTempBuffer != GaaAppBufferForWriteA[GusLoopVar])
            {
              GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
              break;
            }
            LpTempBuffer++;
          }
        }
        else
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }
      }
    }   
#endif /* #if ((MEM_59_RENESAS_DATA_FLASH_CONFIGURED == STD_ON)  && (MEM_59_RENESAS_CODE_FLASH_CONFIGURED == STD_ON)) */

/**********************************************************************************************************************/
/************************************************ Hw Specific Service *************************************************/
/************************************************* Read Option Byte ***************************************************/
/**********************************************************************************************************************/
    if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
    {
      GddReturnValue = Mem_59_Renesas_HwSpecificService(MEM_59_RENESAS_SAMPLE_INSTANCE_ID, 
                              MEM_59_RENESAS_READ_OPTION_BYTES, GaaAppBufferForReturnOPBT, GaaAppBufferForLengthOPBT);

      if (E_OK == GddReturnValue)
      {
        while (MEM_59_RENESAS_JOB_PENDING == Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID))
        {
          Mem_59_Renesas_MainFunction();
        }  

        GddJobResultType = Mem_59_Renesas_GetJobResult(MEM_59_RENESAS_SAMPLE_INSTANCE_ID);

        if (MEM_59_RENESAS_JOB_OK != GddJobResultType)
        {
          GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
        }

      }
      else
      {
        GblTestResult = MEM_59_RENESAS_SAMPLE_FALSE;
      }
    } 
    
    /* Deinit driver */
    Mem_59_Renesas_DeInit();

    GucTestNo--;
  }


  if (MEM_59_RENESAS_SAMPLE_TRUE == GblTestResult)
  {
      TestPass();
  }
  else
  {
      TestFail();
  }
  
  while(1);
  
} /* End of main() function */

void Delay(void)
{
  GulDelayCounter = MEM_59_RENESAS_SAMPLE_ZERO;
  while (GulDelayCounter < MEM_59_RENESAS_DELAY_TIME)
  {
    GulDelayCounter++;
  }
  return;
}

void TestBufferClear(void)
{
  uint16 LusLoopCount;
  for (LusLoopCount = MEM_59_RENESAS_SAMPLE_ZERO; LusLoopCount < MEM_59_RENESAS_APP_BUFFER_SIZE; \
                                                                LusLoopCount++)
  {
    if ( MEM_59_RENESAS_SAMPLE_ZERO == ( LusLoopCount & MEM_59_RENESAS_SAMPLE_TWO ) )
    {
      GaaAppBufferForWriteA[LusLoopCount]     = 0xA5;
    }
    else
    {
      GaaAppBufferForWriteA[LusLoopCount]     = 0x00;
    }
    
    GaaAppBufferForWriteB[LusLoopCount]       = (uint8)LusLoopCount;
    GaaAppBufferForRead[LusLoopCount]         = 0u;
  }
}

void TestPass(void)
{
  while(1);
}

void TestFail(void)
{
  volatile boolean LblTestResult;
  volatile uint8   LucTestNo;
  
  LblTestResult = GblTestResult;
  LucTestNo     = GucTestNo;
  while(1);
}

/* Notification for single bit error */
void EccSEDNotification(uint32 ErrAddress)
{
  /* Defined by the user */
}

/* Notification for double bit error */
void EccDEDNotification(uint32 ErrAddress)
{
  /* Defined by the user */
}

/* Perform processing to enter critical section */
void R_RFD_HOOK_EnterCriticalSection(void)
{
    return;
}

/* Perform processing to exit critical section */
void R_RFD_HOOK_ExitCriticalSection(void)
{
  return;
}
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
