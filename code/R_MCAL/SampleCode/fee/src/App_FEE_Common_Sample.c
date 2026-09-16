/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22.11 X2x MCAL Components                                                          */
/* Module       = App_Fee_Common_Sample.c                                                                             */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application for FEE Component                                                            */
/*                                                                                                                    */
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
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header
 * 1.1.0:  30/06/2025:  Update SW-VERSION for U2Ax Ver22.01.00(D) Final Release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                      As part of support U2Bx-E SampleApp on G4KH, following changes are made:
 *                       1. Add function Guard_Enable_PE
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024:  Update SW-VERSION 1.0.0.
 * 0.0.2:  31/10/2024:  Update SW-VERSION 0.0.2.
 * 0.0.1:  30/08/2024:  Initial Version. 
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "App_FEE_Common_Sample.h"
#include "App_Fee_Device_Sample.h"
#include "Fee.h"
#include "MemAcc.h"
#include "Mem_59_Renesas.h"
#include "MemAcc_Cbk.h"
#include "Mem_59_Renesas_Cbk.h"

/***********************************************************************************************************************
**                                                Global Data                                                         **
***********************************************************************************************************************/
uint32 RamWriteDataBuffer_64[16] = {(uint8) 0};
uint32 RamWriteDataBuffer_128[32] = {(uint8) 0};
uint32 RamWriteDataBuffer_128_Cancel[32] = {(uint8) 0};
uint32 RamWriteDataBuffer_1024[256] = {(uint8) 0};

uint32 RamReadDataBuffer_64[16];
uint32 RamReadDataBuffer_128[32];
uint32 RamReadDataBuffer_1024[256];

/* Global variable to store result of the current request */
MemIf_JobResultType GenJobResult;
Std_VersionInfoType GddVersionInfo;
Std_ReturnType GddReturnValue;
MemAcc_JobStatusType GenMemAccStatus;
MemIf_StatusType GenFeeStatus;
uint32 GulFee_StubDelayCounter;

volatile boolean GblTestResult;

/* Variable used to stored the Address ID */
MemAcc_AddressAreaIdType GusaddressAreaId;

/* Local variable to store the test result */
uint8 GaaTestResult[50];
/* Variable to store result of checked point */
uint8 GucTestResultCount;

/***********************************************************************************************************************
**                                                User function prototypes                                            **
***********************************************************************************************************************/
void Fee_StubDelay(void);

// void BufferClear(uint8 *pAppBufferForRead, uint16 LusLength);

// void BufferWrite_0(uint8 *pAppBufferForWrite, uint16 LusLength);

// void BufferWrite_1(uint8 *pAppBufferForWrite, uint16 LusLength);

// void BufferWrite_Value(uint8 *pAppBufferForWrite, uint16 LusLength, uint8 LucValue);

boolean Fee_StubCompareData(const uint8 *pDataWrite, const uint8 *pDataRead, uint16 LusLength);

void Fee_MainFunction(void);

void Fee_StubJobStatusConfirmation(void);

void Fee_StubReadConfirmation(const uint8 *pRamDataWrite, const uint8 *pRamDataRead, uint16 LusLength);

void Fee_ScheduleFunction(void);

void TestPass (void);
void TestFail (void);
void Fee_StubInitialBuffer (uint32 length , uint8 *buffer);
void Fee_StubClearBuffer (uint32 length, uint8 *buffer);
void Fee_StubSetValueBuffer (uint32 length, uint8 value, uint8 *buffer);
extern void Guard_Enable_PE(void);
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
int main(void)
#if defined (RUN_OTHER_PE)
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
    /* Module initialize status definition */
  GblTestResult = FEE_SAMPLE_TRUE;

  /* Mcu Initialisation */
  Mcu_Init();
  /* Enable the global interrupts to periodically schedule Fee_MainFunction() */
  ENABLE_INTERRUPT();
  /* Timer Initialisation */
  Timer_Init();

  /* GET VERSIONINFO */
  #if (FEE_VERSION_INFO_API == STD_ON)
  /* Invoke the API Fee_GetVersionInfo to read the version information of FEE software component */
  Fee_GetVersionInfo(&GddVersionInfo);
  if ((FEE_VENDOR_ID != GddVersionInfo.vendorID) ||
      (FEE_MODULE_ID != GddVersionInfo.moduleID) ||
      (FEE_SW_MAJOR_VERSION != GddVersionInfo.sw_major_version) ||
      (FEE_SW_MINOR_VERSION != GddVersionInfo.sw_minor_version) ||
      (FEE_SW_PATCH_VERSION != GddVersionInfo.sw_patch_version))
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }
  #endif

  /* INIT*/
  /* FEE Component initialization */
  Fee_Init(NULL_PTR);
  /* Initilazation MemAcc  */
  MemAcc_Init(MemAcc_Config);
  /* Initilazation MEM_Init */
  Mem_59_Renesas_Init(NULL_PTR);

  /* Stub all area before initalazation Fee_Init */
  Fee_StubPrepareAreas();
  
  /* Initilazation Fee */
  Fee_ScheduleFunction();
  
  /********************************************************************************************************************/
  /*                                              ADDRESS AREA 0                                                      */
  /********************************************************************************************************************/

  /********************************************************************************************************************/
  /*                                              BLOCK 0                                                             */
  /********************************************************************************************************************/
  /* 
  PROCESS 1: SA for 
  + Fee_Write():                                  Expected: OK
  + Fee_Read():                                   Expetced: OK
  + Fee_InvalidateBlock():                        Expected: OK
  + Fee_Read():                                   Expected: MEMIF_BLOCK_INVALID
  */
  if (FEE_SAMPLE_TRUE == GblTestResult)
  {
    /* Prepare data for FEE write */
    Fee_StubSetValueBuffer(64, 0x11, (uint8 *)&RamWriteDataBuffer_64);
    Fee_StubClearBuffer(64, (uint8 *)&RamReadDataBuffer_64);

    /* WRITE */
    /* Invoke the API to perform write operation */
    GddReturnValue = Fee_Write(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_0, (uint8 *)&RamWriteDataBuffer_64);

    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */

      Fee_ScheduleFunction();
      
      /* Check process of Fee_Write */
      Fee_StubJobStatusConfirmation();
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }

    /* READ */
    /* Invoke the API to perform Read operation */
    GddReturnValue = 
                    Fee_Read(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_0, 0x0000, (uint8 *)&RamReadDataBuffer_64, 0x0040);
    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process and data of Fee_Read() */
      Fee_StubReadConfirmation((uint8 *)&RamWriteDataBuffer_64, (uint8 *)&RamReadDataBuffer_64, 64);
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }

    /* Clear data buffer */
    Fee_StubClearBuffer(64, (uint8 *)&RamWriteDataBuffer_64);
    Fee_StubClearBuffer(64, (uint8 *)&RamReadDataBuffer_64);

    /* INVALIDATE BLOCK */
    /* Invoke the API to perform Invalidate operation */
    GddReturnValue = Fee_InvalidateBlock(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_0);

    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process of Fee_InvalidateBlock */
      Fee_StubJobStatusConfirmation();
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }

    /* READ */
    /* Invoke the API to perform Read operation */
    GddReturnValue = 
                    Fee_Read(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_0, 0x0000, (uint8 *)&RamReadDataBuffer_64, 0x0040);
    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Check if the processing of the current request is completed. */

      Fee_ScheduleFunction();

      /* This call back function shall be call in Fls_MainFunction */
      /* @todo: In feasible, FEE invoke Fee_JobEndNotification to confirm behavior of FEE */
      /* Block is invalid  -> No need to call Fee_JobEndNotifiction */

      /* Check process and data of Fee_Read() */
      Fee_StubReadConfirmation((uint8 *)&RamWriteDataBuffer_64, (uint8 *)&RamReadDataBuffer_64, 64);
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }
  }
  /********************************************************************************************************************/
  /*                                              BLOCK 2                                                             */
  /********************************************************************************************************************/
  /* 
  PROCESS 2: SA for 
  + Fee_EraseImmediateBlock()                     Expected: OK
  + Fee_Write()                                   Expected: OK
  + Fee_Read()                                    Expected: OK
  */
  if (FEE_SAMPLE_TRUE == GblTestResult)
  {
    /* Prepare data for FEE write */
    Fee_StubSetValueBuffer(128, 0x22, (uint8 *)&RamWriteDataBuffer_128);
    Fee_StubClearBuffer(128, (uint8 *)&RamReadDataBuffer_128);

    /* ERASE */
    /* Invoke the API to perform erase operation */
    GddReturnValue = Fee_EraseImmediateBlock(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_2);

    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process of Fee_EraseImmediateBlock */
      Fee_StubJobStatusConfirmation();
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }

    /* Invoke write operation and then cancel the write operation */
    GddReturnValue = Fee_Write(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_2, (uint8 *)&RamWriteDataBuffer_128);
    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process of Fee_EraseImmediateBlock */
      Fee_StubJobStatusConfirmation();
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }

    /* READ */
    /* Invoke the API to perform Read operation */
    GddReturnValue = 
                  Fee_Read(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_2, 0x0000, (uint8 *)&RamReadDataBuffer_128, 0x0080);
    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process and data of Fee_Read() */
      Fee_StubReadConfirmation((uint8 *)&RamWriteDataBuffer_128, (uint8 *)&RamReadDataBuffer_128, 128);
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }
  }
  /********************************************************************************************************************/
  /*                                              BLOCK 2                                                             */
  /********************************************************************************************************************/
  /* 
  PROCESS 3: SA for 
  + Fee_Write()                                   Expected: Cancel by Fee_Cancel()
  + Fee_Cancel()                                  Expected: OK
  + Fee_Read()                                    Expected: Return to value of previous process
  */
  if (FEE_SAMPLE_TRUE == GblTestResult)
  {
    /* Prepare data for FEE write */
    Fee_StubInitialBuffer(128, (uint8 *)&RamWriteDataBuffer_128_Cancel);
    Fee_StubClearBuffer(128, (uint8 *)&RamReadDataBuffer_128);

    /* Invoke write operation and then cancel the write operation */
    GddReturnValue = Fee_Write(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_2, (uint8 *)&RamWriteDataBuffer_128_Cancel);

    /* CANCEL */
    Fee_Cancel();
    if ((GenJobResult = Fee_GetJobResult()) == MEMIF_JOB_CANCELED)
    {
      GblTestResult = FEE_SAMPLE_TRUE;
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }

    /* READ */
    /* Invoke the API to perform Read operation */
    GddReturnValue = 
                  Fee_Read(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_2, 0x0000, (uint8 *)&RamReadDataBuffer_128, 0x0080);
    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process and data of Fee_Read() */
      Fee_StubReadConfirmation((uint8 *)&RamWriteDataBuffer_128, (uint8 *)&RamReadDataBuffer_128, 128);
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }
  }

  /********************************************************************************************************************/
  /*                                              BLOCK 0                                                             */
  /********************************************************************************************************************/
  /* 
  PROCESS 4: SA for 
  + Fee_Write()                                   Expected: OK
  + Fee_Read()                                    Expected: OK
  + Fee_Write()                                   Expected: OK
  + Fee_Read()                                    Expected: OK
  */
  if (FEE_SAMPLE_TRUE == GblTestResult)
  {
    /* Prepare data for FEE write */
    Fee_StubSetValueBuffer(64, 0x88, (uint8 *)&RamWriteDataBuffer_64);
    Fee_StubClearBuffer(64, (uint8 *)&RamReadDataBuffer_64);

    /* WRITE */
    /* Invoke the API to perform write operation */
    GddReturnValue = Fee_Write(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_0, (uint8 *)&RamWriteDataBuffer_64);

    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process of Fee_Write */
      Fee_StubJobStatusConfirmation();
    }
    else
    {
        GblTestResult = FEE_SAMPLE_FALSE;
    }

    /* READ */
    /* Invoke the API to perform Read operation */
    GddReturnValue = 
                    Fee_Read(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_0, 0x0000, (uint8 *)&RamReadDataBuffer_64, 0x0040);
    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process and data of Fee_Read() */
      Fee_StubReadConfirmation((uint8 *)&RamWriteDataBuffer_64, (uint8 *)&RamReadDataBuffer_64, 64);
    }
    else
    {
      GaaTestResult[GucTestResultCount] = FALSE;
      GucTestResultCount++;
    }

    /* Clear data buffer */
    Fee_StubClearBuffer(64, (uint8 *)&RamReadDataBuffer_64);
    Fee_StubSetValueBuffer(64, 0x99, (uint8 *)&RamWriteDataBuffer_64);

    /* WRITE */
    /* Invoke the API to perform write operation */
    GddReturnValue = Fee_Write(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_0, (uint8 *)&RamWriteDataBuffer_64);

    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process of Fee_Write */
      Fee_StubJobStatusConfirmation();
    }
    else
    {
        GblTestResult = FEE_SAMPLE_FALSE;
    }

    /* READ */
    /* Invoke the API to perform Read operation */
    GddReturnValue = 
                    Fee_Read(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_0, 0x0000, (uint8 *)&RamReadDataBuffer_64, 0x0040);
    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process and data of Fee_Read() */
      Fee_StubReadConfirmation((uint8 *)&RamWriteDataBuffer_64, (uint8 *)&RamReadDataBuffer_64, 64);
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }
  }
  /********************************************************************************************************************/
  /*                                              ADDRESS AREA 1                                                      */
  /********************************************************************************************************************/

  /********************************************************************************************************************/
  /*                                              BLOCK 1                                                             */
  /********************************************************************************************************************/
  /* 
  PROCESS 5: SA for 
  + Fee_Write()                                   Expected: OK
  + Fee_Read()                                    Expected: OK
  */
  if (FEE_SAMPLE_TRUE == GblTestResult)
  {
    /* Prepare data for FEE write */
    Fee_StubInitialBuffer(128, (uint8 *)&RamWriteDataBuffer_128);
    Fee_StubClearBuffer(128, (uint8 *)&RamReadDataBuffer_128);

    /* Invoke write operation and then cancel the write operation */
    GddReturnValue = Fee_Write(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_1, (uint8 *)&RamWriteDataBuffer_128);
    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process of Fee_EraseImmediateBlock */
      Fee_StubJobStatusConfirmation();
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    } /* End of if (GddReturnValue == E_OK) */

    /* READ */
    /* Invoke the API to perform Read operation */
    GddReturnValue = 
                  Fee_Read(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_1, 0x0000, (uint8 *)&RamReadDataBuffer_128, 0x0080);
    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process and data of Fee_Read() */
      Fee_StubReadConfirmation((uint8 *)&RamWriteDataBuffer_128, (uint8 *)&RamReadDataBuffer_128, 128);
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }
  }

  /********************************************************************************************************************/
  /*                                              ADDRESS AREA 0                                                      */
  /********************************************************************************************************************/
  /* 
  PROCESS 6: SA for 
  + Fee_EraseImmediateBlock()                     Expected: Pre-allocated address for immediate data block
  + Fee_Write()                                   Expected: OK
  + Fee_Read()                                    Expected: OK
  */
  /* Prepare data for FEE write */
  if (FEE_SAMPLE_TRUE == GblTestResult)
  {
    Fee_StubInitialBuffer(1024,(uint8 *)&RamWriteDataBuffer_1024);
    Fee_StubClearBuffer(1024, (uint8 *)&RamReadDataBuffer_1024);

    /* ERASE */
    /* Invoke the API to perform erase operation */
    GddReturnValue = Fee_EraseImmediateBlock(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_3);

    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process of Fee_EraseImmediateBlock */
      Fee_StubJobStatusConfirmation();
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }

    /* WRITE */
    /* Invoke the API to perform write operation */
    GddReturnValue = Fee_Write(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_3, (uint8 *)&RamWriteDataBuffer_1024);

    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process of Fee_Write */
      Fee_StubJobStatusConfirmation();
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    } /* End of if (GddReturnValue == E_OK) */

    /* READ */
    /* Invoke the API to perform Read operation */
    GddReturnValue = 
                  Fee_Read(FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_3, 0x0000, (uint8 *)&RamReadDataBuffer_1024, 1024);
    /* Check if the current request is accepted for processing */
    if (GddReturnValue == E_OK)
    {
      /* Invoke Fee_MainFunction to support API in Asynchronous */
      Fee_ScheduleFunction();

      /* Check process and data of Fee_Read() */
      Fee_StubReadConfirmation((uint8 *)&RamWriteDataBuffer_1024, (uint8 *)&RamReadDataBuffer_1024, 1024);
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }
  }

  if (FEE_SAMPLE_FALSE == GblTestResult)
  {
    TestFail();
  }
  else
  {
    TestPass();
  }
  
  while(1);
} /* End of main() function */

/* Test pass */
void TestPass (void)
{
  volatile boolean LblTestResult;
  
  LblTestResult = GblTestResult;
  while (1);
}

void Fee_StubInitialBuffer (uint32 length , uint8 *buffer)
{
  for (uint32 i = 0; i < length; i++)
  {
    *buffer = i;
    buffer++;
  }
}

void Fee_StubSetValueBuffer (uint32 length, uint8 value, uint8 *buffer)
{
  for (uint32 i = 0; i < length; i++)
  {
    *buffer = value;
    buffer++;
  }
  
}

void Fee_StubClearBuffer (uint32 length, uint8 *buffer)
{
  for (uint32 i = 0; i < length; i++)
  {
    *buffer = FEE_SAMPLE_ZERO;
    buffer++;
  }
}

/* Test fail */
void TestFail (void)
{
  volatile boolean LblTestResult;
  
  LblTestResult = GblTestResult;
  while (1);
}


/***********************************************************************************************************************
**                                                Internal function to support for SA                                 **
***********************************************************************************************************************/
boolean Fee_StubCompareData(const uint8 *pDataWrite, const uint8 *pDataRead, uint16 LusLength)
{
  uint16 LusLoopCount;
  boolean LblReturnValue;

  LblReturnValue = 1;

  for(LusLoopCount = 0; LusLoopCount < LusLength; LusLoopCount++)
  {
    if(*(pDataWrite + LusLoopCount) != *(pDataRead + LusLoopCount))
    {
      LblReturnValue = 0;
      break;
    }
    else
    {
      /* Not required */
    }
  }
  return LblReturnValue;
}

void Fee_StubJobStatusConfirmation(void)
{
  GenJobResult= Fee_GetJobResult();
  GenFeeStatus = Fee_GetStatus();

  if ((MEMIF_IDLE == GenFeeStatus) && (MEMIF_JOB_OK == GenJobResult))
  {
    GblTestResult = FEE_SAMPLE_TRUE;
  }
  else
  {
    GblTestResult = FEE_SAMPLE_FALSE;
  }
}

void Fee_StubReadConfirmation(const uint8 *pRamDataWrite, const uint8 *pRamDataRead, uint16 LusLength)
{
  GenJobResult= Fee_GetJobResult();
  GenFeeStatus = Fee_GetStatus();

  if ((MEMIF_IDLE == GenFeeStatus) && (MEMIF_JOB_OK == GenJobResult))
  {
    /* Check point for Compare Data */
    if (Fee_StubCompareData(pRamDataWrite, pRamDataRead, LusLength))
    {
      GblTestResult = FEE_SAMPLE_TRUE;
    }
    else
    {
      GblTestResult = FEE_SAMPLE_FALSE;
    }
  }
}

/***********************************************************************************************************************
**                                                Timer ISR                                                           **
***********************************************************************************************************************/
void Fee_StubDelay (void)
{
  uint32 lulDelayCounter;
  lulDelayCounter = FEE_SAMPLE_ZERO;
  while (lulDelayCounter < FEE_DELAY_TIME)
  {
    lulDelayCounter++;
  }
  return;
}
/***********************************************************************************************************************
**                                                Notification Functions                                              **
***********************************************************************************************************************/
/* Notification for job End */
void EndNotification0(MemAcc_AddressAreaIdType addressAreaId, MemAcc_JobResultType jobResult)
{
  /* Defined by the user */
}

/* Notification for job SED error */
void EccSEDNotification(uint32 ErrAddress)
{
  /* Defined by the user */
}

/* Notification for job DED error */
void EccDEDNotification(uint32 ErrAddress)
{
  /* Defined by the user */
}

/***********************************************************************************************************************
**                                                Schedule Functions                                              **
***********************************************************************************************************************/
void Fee_ScheduleFunction (void)
{
  do
  {
    /* Invoke schedule function */
    Fee_MainFunction();
    MemAcc_MainFunction();
    Mem_59_Renesas_MainFunction();
  } while (MEMIF_IDLE != Fee_GetStatus());
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
/***********************************************************************************************************************
**                                                End of File                                                         **
***********************************************************************************************************************/
