/*============================================================================*/
/* Project      = AUTOSAR Renesas R22-11 X2x MCAL Components                  */
/* Module       = App_MEMACC_Common_Sample.c                                  */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for MEMACC Driver Component          */
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
/*              Devices:        RH850/X2x                                     */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header
 * 1.1.0:  30/06/2025:  Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 *                      As part of support U2Bx-E SampleApp on G4KH, following changes are made:
 *                      + Add function Guard_Enable_PE
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.1:  31/01/2025:  Update support U2Cx device 
 * 1.0.0:  31/12/2024:  Update SW-VERSION for Ver22.02.00 U2Bx Final Release. 
 *         19/11/2024:  Update Sample App to test sequence with invocation is
 *                      INDIRECT_DYNAMIC.
 * 0.0.2:  31//2024:  Update data type for buffer to testing
 * 0.0.1:  30/08/2024:  Initial Version.
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_MEMACC_Common_Sample.h"
#include "App_MEMACC_Device_Sample.h"
#include "MemAcc_Cbk.h"
#include "Mem_59_Renesas.h"
#include "Mem_59_Renesas_Cfg.h"
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/
/* Buffer for Application */
volatile uint32 GaaWriteBufferApplication[MEMACC_MAX_BUFFER_SIZE];
volatile uint32 GaaReadBufferApplication[MEMACC_MAX_BUFFER_SIZE];
/* Variable used to store Sample app result */
volatile boolean GblTestResult;
/* Variable used to store the Job result */
volatile MemAcc_JobResultType GbJobResult;
/* Variable used to store the Jos status */
volatile MemAcc_JobStatusType GbobStatus;
/* Variable used to store the Memory information */
MemAcc_MemoryInfoType GstMemoryInfo;
/*  Variable used to store the Process length */
volatile MemAcc_LengthType GulProcessedLength;
/* Variable used to store the Job information */
MemAcc_JobInfoType GstJobInfo;
/* Variable used to stored the return value for API */
Std_ReturnType GucReturnValue;
/* Variable used to store the Module Version Info */
Std_VersionInfoType GddVersionInfo;
/* Flag to check if lock notification call back is invoked */
volatile boolean GblLockNotificationFlag;
/*******************************************************************************
**              Mem driver header structure stub for tesing                   **
*******************************************************************************/
MemAcc_MemInitFuncType ApplicationInitFuncPtr = (MemAcc_MemInitFuncType) &Mem_59_Renesas_Init;
MemAcc_MemDeInitFuncType ApplicationDeInitFuncPtr = (MemAcc_MemDeInitFuncType) &Mem_59_Renesas_DeInit;
MemAcc_MemEraseFuncType ApplicationEraseFuncPtr = (MemAcc_MemEraseFuncType) &Mem_59_Renesas_Erase;
MemAcc_MemMainFuncType ApplicationMainFuncPtr = (MemAcc_MemMainFuncType) &Mem_59_Renesas_MainFunction;
MemAcc_MemGetJobResultFuncType ApplicationGetJobResultFuncPtr = (MemAcc_MemGetJobResultFuncType) &Mem_59_Renesas_GetJobResult;
MemAcc_MemReadFuncType ApplicationReadFuncPtr = (MemAcc_MemReadFuncType) &Mem_59_Renesas_Read;
MemAcc_MemWriteFuncType ApplicationWriteFuncPtr = (MemAcc_MemWriteFuncType) &Mem_59_Renesas_Write;
MemAcc_MemBlankCheckFuncType ApplicationBlankCheckFuncPtr = (MemAcc_MemBlankCheckFuncType) &Mem_59_Renesas_BlankCheck;
MemAcc_MemHwSpecificServiceFuncType ApplicationMemHwSpecificFuncPtr = (MemAcc_MemHwSpecificServiceFuncType) &Mem_59_Renesas_HwSpecificService;
MemAcc_MemSuspendFuncType ApplicationSuspendFuncPtr = (MemAcc_MemSuspendFuncType) &Mem_59_Renesas_Suspend;
MemAcc_MemResumeFuncType ApplicationResumeFuncPtr = (MemAcc_MemResumeFuncType) &Mem_59_Renesas_Resume;
MemAcc_UniqueIdType GstUniqueId;
MemAcc_MemBinaryHeaderType GstMemBinary;


/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
void TestPass (void);
void TestFail (void);
void clear_read_buffer(void);
void Delay(void);
void Initial_write_buffer(void);
void ApplicationLockNotification(void);
void InitialMemDriverHeaderStub(void);
extern void Guard_Enable_PE(void);
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
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
  /* Initial Mem Driver Header Data Stub  */
  InitialMemDriverHeaderStub();

  volatile uint32 LulLoopCount;
  uint32 LulOPBTValue;
  MemAcc_LengthType LulOPBTLength;

  GblTestResult = MEMACC_SAMPLE_TRUE;
  GblLockNotificationFlag = FALSE;

  /* Init MCU */
  Mcu_Init();

  /* To get the version of the MEMACC Driver module */
  MemAcc_GetVersionInfo(&GddVersionInfo);
  /* Check for the correctness of version information */
  if ((MEMACC_VENDOR_ID != GddVersionInfo.vendorID) ||
      (MEMACC_MODULE_ID != GddVersionInfo.moduleID) ||
      (MEMACC_SW_MAJOR_VERSION != GddVersionInfo.sw_major_version) ||
      (MEMACC_SW_MINOR_VERSION != GddVersionInfo.sw_minor_version) ||
      (MEMACC_SW_PATCH_VERSION != GddVersionInfo.sw_patch_version))
  {
    GblTestResult = MEMACC_SAMPLE_FALSE;
  }

  /********************************************************************************************************************/
  /* Initital driver                                                                                                  */
  /********************************************************************************************************************/
  /* Init MemAcc driver */
  MemAcc_Init(MemAcc_Config);
  /* Mem driver activation through MemAcc_ActiveMem */
  GucReturnValue = MemAcc_ActivateMem((MemAcc_AddressType)&GstMemBinary, (MemAcc_HwIdType)MEMACC_SAMPLE_ZERO);
  if (E_OK != GucReturnValue)
  {
    GblTestResult = MEMACC_SAMPLE_FALSE;
  }
  /********************************************************************************************************************/
  /* Get information of MemAcc after initialization                                                                   */
  /********************************************************************************************************************/
  GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ZERO);
  if (MEMACC_MEM_OK != GbJobResult)
  {
    GblTestResult = MEMACC_SAMPLE_FALSE;
  }

  GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO);
  if (MEMACC_JOB_IDLE != GbobStatus)
  {
    GblTestResult = MEMACC_SAMPLE_FALSE;
  }

  GucReturnValue   = MemAcc_GetMemoryInfo(MEMACC_SAMPLE_ZERO, MEMACC_LOGICAL_START_ADDRESS_AREA0, &GstMemoryInfo);
  if (E_OK == GucReturnValue)
  {
    if ((MEMACC_LOGICAL_START_ADDRESS_AREA0 != GstMemoryInfo.LogicalStartAddress) ||
        (MEMACC_PHYSICAL_START_ADDRESS_AREA0 != GstMemoryInfo.PhysicalStartAddress) ||
        (MEMACC_MAX_OFFSET_AREA0 != GstMemoryInfo.MaxOffset) ||
        (MEMACC_ERASE_SECTOR_SIZE_AREA0 != GstMemoryInfo.EraseSectorSize) ||
        (MEMACC_ERASE_SECTOR_BURST_SIZE_AREA0 != GstMemoryInfo.EraseSectorBurstSize) ||
        (MEMACC_MIN_READ_SIZE_AREA0 != GstMemoryInfo.ReadPageSize) ||
        (MEMACC_WRITE_PAGE_SIZE_AREA0 != GstMemoryInfo.WritePageSize) ||
        (MEMACC_MAX_READ_SIZE_AREA0 != GstMemoryInfo.ReadPageBurstSize) ||
        (MEMACC_WRITE_PAGE_BURST_SIZE_AREA0 != GstMemoryInfo.WritePageBurstSize) ||
        (MEMACC_HW_ID_AREA0 != GstMemoryInfo.HwId))
    {
      GblTestResult = MEMACC_SAMPLE_FALSE;
    }
  }
  else
  {
    GblTestResult = MEMACC_SAMPLE_FALSE;
  }

  GulProcessedLength = MemAcc_GetProcessedLength(MEMACC_SAMPLE_ZERO);
  if (MEMACC_SAMPLE_ZERO != GulProcessedLength)
  {
    GblTestResult = MEMACC_SAMPLE_FALSE;
  }

  MemAcc_GetJobInfo(MEMACC_SAMPLE_ZERO, &GstJobInfo);
  if ((MEMACC_LOGICAL_START_ADDRESS_AREA0 != GstJobInfo.LogicalAddress) ||
      (MEMACC_SAMPLE_ZERO != GstJobInfo.Length) ||
      (MEMACC_SAMPLE_ZERO != GstJobInfo.HwId) ||
      (MEMACC_SAMPLE_ZERO != GstJobInfo.MemInstanceId) ||
      (MEMACC_PHYSICAL_START_ADDRESS_AREA0 != GstJobInfo.MemAddress) ||
      (MEMACC_SAMPLE_ZERO != GstJobInfo.MemLength) ||
      (MEMACC_NO_JOB != GstJobInfo.CurrentJob) ||
      (MEM_59_RENESAS_JOB_OK != GstJobInfo.MemResult))
  {
    GblTestResult = MEMACC_SAMPLE_FALSE;
  }
  /********************************************************************************************************************/
  /* Sequence 1: Normal erase/blank check/write/read/compare                                                          */
  /********************************************************************************************************************/
  /* 
  PROCESS 1: SA for 
  + Memacc_Erase():                               Expected: OK
  + Memacc_BlankCheck():                          Expected: OK
  + Memacc_Write():                               Expetced: OK
  + Memacc_Read():                                Expected: OK
  + Memacc_Compare():                             Expected: OK
  */

  /********************************************************************************************************************/
  /* PROCESS 1.1: Erase operation                                                                                     */
  /********************************************************************************************************************/

  if (MEMACC_SAMPLE_TRUE == GblTestResult)
  {
    GucReturnValue = MemAcc_Erase(MEMACC_SAMPLE_ZERO, MEMACC_LOGICAL_START_ADDRESS_AREA0, MEMACC_ERASE_LENGTH_AREA0);
    GucReturnValue |= MemAcc_Erase(MEMACC_SAMPLE_ONE, MEMACC_LOGICAL_START_ADDRESS_AREA1, MEMACC_ERASE_LENGTH_AREA1);
  
    if (E_OK == GucReturnValue)
    {
      /****************************************************************************************************************/
      /* Get information of MemAcc after accept job request                                                           */
      /****************************************************************************************************************/
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ZERO);
      if (MEMACC_MEM_OK != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO);
      if (MEMACC_JOB_PENDING != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      GulProcessedLength = MemAcc_GetProcessedLength(MEMACC_SAMPLE_ZERO);
      if (MEMACC_SAMPLE_ZERO != GulProcessedLength)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      MemAcc_GetJobInfo(MEMACC_SAMPLE_ZERO, &GstJobInfo);
      if ((MEMACC_LOGICAL_START_ADDRESS_AREA0 != GstJobInfo.LogicalAddress) ||
          (MEMACC_ERASE_LENGTH_AREA0 != GstJobInfo.Length) ||
          (MEMACC_SAMPLE_ZERO != GstJobInfo.HwId) ||
          (MEMACC_SAMPLE_ZERO != GstJobInfo.MemInstanceId) ||
          (MEMACC_PHYSICAL_START_ADDRESS_AREA0 != GstJobInfo.MemAddress) ||
          (MEMACC_SAMPLE_ZERO != GstJobInfo.MemLength) ||
          (MEMACC_ERASE_JOB != GstJobInfo.CurrentJob) ||
          (MEM_59_RENESAS_JOB_OK != GstJobInfo.MemResult))
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      /* Execute scheduled function until complete job on area 1 */
      while (MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE))
      {
        Delay();
        /* Invoke schedule function */
        MemAcc_MainFunction();
      }

      /* Since area 1 priority > area 0 priority, then area 0 status should be still pending */
      if (MEMACC_JOB_PENDING != MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO))
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      /* Execute scheduled function until complete job on area 0 */
      while (MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO))
      {
        Delay();
        /* Invoke schedule function */
        MemAcc_MainFunction();
      }

      /****************************************************************************************************************/
      /* Get information of MemAcc after job completion                                                               */
      /****************************************************************************************************************/
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ZERO);
      if (MEMACC_MEM_OK != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ONE);
      if (MEMACC_MEM_OK != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO);
      if (MEMACC_JOB_IDLE != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE);
      if (MEMACC_JOB_IDLE != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      GulProcessedLength = MemAcc_GetProcessedLength(MEMACC_SAMPLE_ZERO);
      if (MEMACC_ERASE_LENGTH_AREA0 != GulProcessedLength)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
      GulProcessedLength = MemAcc_GetProcessedLength(MEMACC_SAMPLE_ONE);
      if (MEMACC_ERASE_LENGTH_AREA1 != GulProcessedLength)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
    }
    else
    {
      GblTestResult = MEMACC_SAMPLE_FALSE;
    }
  }

  /********************************************************************************************************************/
  /* PROCESS 1.2: blank check operation                                                                               */
  /********************************************************************************************************************/
  if (MEMACC_SAMPLE_TRUE == GblTestResult)
  {
    GucReturnValue = MemAcc_BlankCheck(MEMACC_SAMPLE_ZERO,
      MEMACC_LOGICAL_START_ADDRESS_AREA0, MEMACC_ERASE_LENGTH_AREA0);
    GucReturnValue |= MemAcc_BlankCheck(MEMACC_SAMPLE_ONE,
     MEMACC_LOGICAL_START_ADDRESS_AREA1, MEMACC_ERASE_LENGTH_AREA1);
  
    if (E_OK == GucReturnValue)
    {
      /* Execute scheduled function until complete job on area 1 */
      while (MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE))
      {
        Delay();
        /* Invoke schedule function */
        MemAcc_MainFunction();
      }

      /* Since area 1 priority > area 0 priority, then area 0 status should be still pending */
      if (MEMACC_JOB_PENDING != MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO))
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      /* Execute scheduled function until complete job on area 0 */
      while (MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO))
      {
        Delay();
        /* Invoke schedule function */
        MemAcc_MainFunction();
      }

      /****************************************************************************************************************/
      /* Get information of MemAcc after job completion                                                               */
      /****************************************************************************************************************/
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ZERO);
      if (MEMACC_MEM_OK != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ONE);
      if (MEMACC_MEM_OK != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO);
      if (MEMACC_JOB_IDLE != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE);
      if (MEMACC_JOB_IDLE != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
    }
    else
    {
      GblTestResult = MEMACC_SAMPLE_FALSE;
    }
  }

  /********************************************************************************************************************/
  /* PROCESS 1.3: Write operation                                                                                     */
  /********************************************************************************************************************/
  if (MEMACC_SAMPLE_TRUE == GblTestResult)
  {
    /* Initial application buffer */
    Initial_write_buffer();
    GucReturnValue = MemAcc_Write(MEMACC_SAMPLE_ZERO, MEMACC_LOGICAL_START_ADDRESS_AREA0,
      (MemAcc_DataType*)&GaaWriteBufferApplication[MEMACC_SAMPLE_ZERO], MEMACC_TEST_LENGTH);
    GucReturnValue |= MemAcc_Write(MEMACC_SAMPLE_ONE, MEMACC_LOGICAL_START_ADDRESS_AREA1,
      (MemAcc_DataType*)&GaaWriteBufferApplication[MEMACC_SAMPLE_ZERO], MEMACC_TEST_LENGTH);
  
    if (E_OK == GucReturnValue)
    {
      /* Execute scheduled function until complete job on area 1 */
      while (MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE))
      {
        Delay();
        /* Invoke schedule function */
        MemAcc_MainFunction();
      }

      /* Since area 1 priority > area 0 priority, then area 0 status should be still pending */
      if (MEMACC_JOB_PENDING != MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO))
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      /* Execute scheduled function until complete job on area 0 */
      while (MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO))
      {
        Delay();
        /* Invoke schedule function */
        MemAcc_MainFunction();
      }

      /****************************************************************************************************************/
      /* Get information of MemAcc after job completion                                                               */
      /****************************************************************************************************************/
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ZERO);
      if (MEMACC_MEM_OK != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ONE);
      if (MEMACC_MEM_OK != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO);
      if (MEMACC_JOB_IDLE != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE);
      if (MEMACC_JOB_IDLE != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
    }
    else
    {
      GblTestResult = MEMACC_SAMPLE_FALSE;
    }
  }

  /********************************************************************************************************************/
  /* PROCESS 1.4: Read operation                                                                                      */
  /********************************************************************************************************************/
  if (MEMACC_SAMPLE_TRUE == GblTestResult)
  {
    GucReturnValue = MemAcc_Read(MEMACC_SAMPLE_ZERO, MEMACC_LOGICAL_START_ADDRESS_AREA0,
      (MemAcc_DataType*)&GaaReadBufferApplication[MEMACC_SAMPLE_ZERO], MEMACC_TEST_LENGTH);

    if (E_OK == GucReturnValue)
    {
      /* Execute scheduled function until complete job on area 0 */
      while (MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO))
      {
        Delay();
        /* Invoke schedule function */
        MemAcc_MainFunction();
      }
      /* Get information MemAcc after job completion */
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ZERO);
      if (MEMACC_MEM_OK != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO);
      if (MEMACC_JOB_IDLE != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
      /* Verify read data and write data */
      for(LulLoopCount = MEMACC_SAMPLE_ZERO; LulLoopCount < MEMACC_TEST_LENGTH; LulLoopCount++)
      {
        if (GaaReadBufferApplication[LulLoopCount] != GaaWriteBufferApplication[LulLoopCount])
        {
          GblTestResult = MEMACC_SAMPLE_FALSE;
        }
      }
    }
    else
    {
      GblTestResult = MEMACC_SAMPLE_FALSE;
    }
  }

  if (MEMACC_SAMPLE_TRUE == GblTestResult)
  {
    clear_read_buffer();
    GucReturnValue = MemAcc_Read(MEMACC_SAMPLE_ONE, MEMACC_LOGICAL_START_ADDRESS_AREA1,
      (MemAcc_DataType*)&GaaReadBufferApplication[MEMACC_SAMPLE_ZERO], MEMACC_TEST_LENGTH);

    if (E_OK == GucReturnValue)
    {
      /* Execute scheduled function until complete job on area 1 */
      while (MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE))
      {
        Delay();
        /* Invoke schedule function */
        MemAcc_MainFunction();
      }
      /* Get information MemAcc after job completion */
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ONE);
      if (MEMACC_MEM_OK != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE);
      if (MEMACC_JOB_IDLE != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
      /* Verify read data and write data */
      for(LulLoopCount = MEMACC_SAMPLE_ZERO; LulLoopCount < MEMACC_TEST_LENGTH; LulLoopCount++)
      {
        if (GaaReadBufferApplication[LulLoopCount] != GaaWriteBufferApplication[LulLoopCount])
        {
          GblTestResult = MEMACC_SAMPLE_FALSE;
        }
      }
    }
    else
    {
      GblTestResult = MEMACC_SAMPLE_FALSE;
    }
  }

  /********************************************************************************************************************/
  /* PROCESS 1.5: Compare operation                                                                                   */
  /********************************************************************************************************************/
  if (MEMACC_SAMPLE_TRUE == GblTestResult)
  {
    GucReturnValue = MemAcc_Compare(MEMACC_SAMPLE_ONE, MEMACC_LOGICAL_START_ADDRESS_AREA1,
      (MemAcc_DataType*)&GaaWriteBufferApplication[0], MEMACC_TEST_LENGTH);
    GucReturnValue |= MemAcc_Compare(MEMACC_SAMPLE_ZERO, MEMACC_LOGICAL_START_ADDRESS_AREA0,
      (MemAcc_DataType*)&GaaWriteBufferApplication[0], MEMACC_TEST_LENGTH);

    if (E_OK == GucReturnValue)
    {
      /* Execute scheduled function until complete job on area 1 */
      while (MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE))
      {
        Delay();
        /* Invoke schedule function */
        MemAcc_MainFunction();
      }

      /* Since area 1 priority > area 0 priority, then area 0 status should be still pending */
      if (MEMACC_JOB_PENDING != MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO))
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      /* Execute scheduled function until complete job on area 0 */
      while (MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO))
      {
        Delay();
        /* Invoke schedule function */
        MemAcc_MainFunction();
      }

      /****************************************************************************************************************/
      /* Get information of MemAcc after job completion                                                               */
      /****************************************************************************************************************/
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ZERO);
      if (MEMACC_MEM_OK != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ONE);
      if (MEMACC_MEM_OK != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO);
      if (MEMACC_JOB_IDLE != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE);
      if (MEMACC_JOB_IDLE != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
    }
    else
    {
      GblTestResult = MEMACC_SAMPLE_FALSE;
    }
  }

  /********************************************************************************************************************/
  /* Sequence 2: Cancel on-going job                                                                                  */
  /********************************************************************************************************************/
  if (MEMACC_SAMPLE_TRUE == GblTestResult)
  {
    GucReturnValue = MemAcc_Compare(MEMACC_SAMPLE_ONE, MEMACC_LOGICAL_START_ADDRESS_AREA1,
      (MemAcc_DataType*)&GaaWriteBufferApplication[0], MEMACC_TEST_LENGTH);
    GucReturnValue |= MemAcc_Compare(MEMACC_SAMPLE_ZERO, MEMACC_LOGICAL_START_ADDRESS_AREA0,
      (MemAcc_DataType*)&GaaWriteBufferApplication[0], MEMACC_TEST_LENGTH);

    if (E_OK == GucReturnValue)
    {
      /* Invoke 1st schedule function */
      MemAcc_MainFunction();

      /* Cancel area 1 */
      MemAcc_Cancel(MEMACC_SAMPLE_ONE);

      /* Execute scheduled function until complete all job */
      while ((MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE)) ||
        (MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO)))
      {
        Delay();
        /* Invoke schedule function */
        MemAcc_MainFunction();
      }

      /****************************************************************************************************************/
      /* Get information of MemAcc after job completion                                                               */
      /****************************************************************************************************************/
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ZERO);
      if (MEMACC_MEM_OK != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ONE);
      if (MEMACC_MEM_CANCELED != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO);
      if (MEMACC_JOB_IDLE != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE);
      if (MEMACC_JOB_IDLE != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
    }
    else
    {
      GblTestResult = MEMACC_SAMPLE_FALSE;
    }
  }

  /********************************************************************************************************************/
  /* Sequence 3: Lock and Release                                                                                     */
  /********************************************************************************************************************/
  if (MEMACC_SAMPLE_TRUE == GblTestResult)
  {
    GucReturnValue = MemAcc_Erase(MEMACC_SAMPLE_ZERO, MEMACC_LOGICAL_START_ADDRESS_AREA0, MEMACC_ERASE_LENGTH_AREA0);
    GucReturnValue |= MemAcc_Erase(MEMACC_SAMPLE_ONE, MEMACC_LOGICAL_START_ADDRESS_AREA1, MEMACC_ERASE_LENGTH_AREA1);

    if (E_OK == GucReturnValue)
    {
      /* Invoke 1st schedule function */
      MemAcc_MainFunction();
      /* Delay to waite execute scheduled function */
      Delay();

      /* Request lock */
      GucReturnValue = MemAcc_RequestLock(MEMACC_SAMPLE_ONE, MEMACC_LOGICAL_START_ADDRESS_AREA1,
        MEMACC_TEST_LENGTH, (void*)&ApplicationLockNotification);

      if (E_OK == GucReturnValue)
      {
        /* Execute scheduled function while locked */
        LulLoopCount = MEMACC_TIMEOUT;
        while (LulLoopCount--)
        {
          Delay();
          /* Invoke schedule function */
          MemAcc_MainFunction();
        }

        /* Check if lock notification is called */
        if (TRUE != GblLockNotificationFlag)
        {
          GblTestResult = MEMACC_SAMPLE_FALSE;
        }

        /* Check if job is still pending */
        GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO);
        if (MEMACC_JOB_PENDING != GbobStatus)
        {
          GblTestResult = MEMACC_SAMPLE_FALSE;
        }
        GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE);
        if (MEMACC_JOB_PENDING != GbobStatus)
        {
          GblTestResult = MEMACC_SAMPLE_FALSE;
        }
      }
      else
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      /* Release lock */
      GucReturnValue = MemAcc_ReleaseLock(MEMACC_SAMPLE_ONE,
        MEMACC_LOGICAL_START_ADDRESS_AREA1, MEMACC_TEST_LENGTH);

      if (E_OK == GucReturnValue)
      {
        /* Execute scheduled function until complete all job */
        while ((MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE)) ||
          (MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO)))
        {
          Delay();
          /* Invoke schedule function */
          MemAcc_MainFunction();
        }

        /**************************************************************************************************************/
        /* Get information of MemAcc after job completion                                                             */
        /**************************************************************************************************************/
        GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ZERO);
        if (MEMACC_MEM_OK != GbJobResult)
        {
          GblTestResult = MEMACC_SAMPLE_FALSE;
        }
        GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ONE);
        if (MEMACC_MEM_OK != GbJobResult)
        {
          GblTestResult = MEMACC_SAMPLE_FALSE;
        }

        GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO);
        if (MEMACC_JOB_IDLE != GbobStatus)
        {
          GblTestResult = MEMACC_SAMPLE_FALSE;
        }
        GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ONE);
        if (MEMACC_JOB_IDLE != GbobStatus)
        {
          GblTestResult = MEMACC_SAMPLE_FALSE;
        }
      }
      else
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
    }
    else
    {
      GblTestResult = MEMACC_SAMPLE_FALSE;
    }
  }
  
  /********************************************************************************************************************/
  /* Hardware specific feature                                                                                        */
  /********************************************************************************************************************/
  if (MEMACC_SAMPLE_TRUE == GblTestResult)
  {
    LulOPBTValue = MEMACC_OPBT_NUMBER;
    LulOPBTLength = MEMACC_SAMPLE_FOUR;
    GucReturnValue = MemAcc_HwSpecificService(MEMACC_SAMPLE_ZERO, (MemAcc_HwIdType)MEMACC_SAMPLE_ZERO,
      MEMACC_HW_SERVICE_READ_OPBT, (MemAcc_DataType*)&LulOPBTValue, &LulOPBTLength);

    if (E_OK == GucReturnValue)
    {
      /* Execute scheduled function until complete all job */
      while (MEMACC_JOB_IDLE != MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO))
      {
        Delay();
        /* Invoke schedule function */
        MemAcc_MainFunction();
      }

      /****************************************************************************************************************/
      /* Get information of MemAcc after job completion                                                               */
      /****************************************************************************************************************/
      GbJobResult = MemAcc_GetJobResult(MEMACC_SAMPLE_ZERO);
      if (MEMACC_MEM_OK != GbJobResult)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }

      GbobStatus = MemAcc_GetJobStatus(MEMACC_SAMPLE_ZERO);
      if (MEMACC_JOB_IDLE != GbobStatus)
      {
        GblTestResult = MEMACC_SAMPLE_FALSE;
      }
    }
    else
    {
      GblTestResult = MEMACC_SAMPLE_FALSE;
    }
  }
  
  /* Mem driver De-activation through MemAcc_DeactivateMem */
  GucReturnValue = MemAcc_DeactivateMem((MemAcc_HwIdType)MEMACC_SAMPLE_ZERO, (MemAcc_AddressType) &GstMemBinary);
  if (E_OK != GucReturnValue)
  {
    GblTestResult = MEMACC_SAMPLE_FALSE;
  }

  /* DeInit MemAcc driver */
  MemAcc_DeInit();

  /********************************************************************************************************************/
  /* Check result                                                                                                     */
  /********************************************************************************************************************/

  if (MEMACC_SAMPLE_FALSE == GblTestResult)
  {
    TestFail();
  }
  else
  {
    TestPass();
  }
  return 0;
} /* End of main() function */

/* Test pass */
void TestPass (void)
{
  volatile boolean LblTestResult;
  LblTestResult = GblTestResult;
  while (1);
}

/* Test fail */
void TestFail (void)
{
  volatile boolean LblTestResult;
  LblTestResult = GblTestResult;
  while (1);
}

void Delay (void)
{
  volatile uint32 lulDelayCounter;
  lulDelayCounter = MEMACC_SAMPLE_ZERO;
  while (lulDelayCounter < MEMACC_DELAY_TIME)
  {
    lulDelayCounter++;
  }
  return;
}

/* Initial value of application buffer */
void Initial_write_buffer (void)
{
  /* Declaration local variable */
  uint32 LulLoopCount;
  /* define a pointer point to buffer*/
  uint8* bufferPtr = (uint8*)&GaaWriteBufferApplication[0];
  /* Initialization value for buffer */
  for ( LulLoopCount = 0; LulLoopCount < MEMACC_MAX_BUFFER_SIZE; LulLoopCount++)
  {
    *bufferPtr = (uint8)LulLoopCount;
    bufferPtr++;
  }
}

/* Setup data stub for Mem Driver Header */
void InitialMemDriverHeaderStub (void)
{
  /* Data for UniqueId*/
  GstUniqueId.usABIversion = MEMACC_SAMPLE_ONE;
  GstUniqueId.usVendorId = MEMACC_VENDOR_ID;
  GstUniqueId.ulDriverId = MEMACC_SAMPLE_ZERO;

  /* Data for elements of Mem Driver Header */
  GstMemBinary.Flags = MEMACC_SAMPLE_ONE;
  GstMemBinary.Header = MEMACC_LOGICAL_START_ADDRESS_AREA0;
  GstMemBinary.UniqueId = *(uint64*)&GstUniqueId;
  GstMemBinary.Delimiter = (uint64)&GstUniqueId;
  GstMemBinary.InitFunc = &ApplicationInitFuncPtr;
  GstMemBinary.DeInitFunc = &ApplicationDeInitFuncPtr;
  GstMemBinary.EraseFunc = &ApplicationEraseFuncPtr;
  GstMemBinary.MainFunc = &ApplicationMainFuncPtr;
  GstMemBinary.GetJobResultFunc = &ApplicationGetJobResultFuncPtr;
  GstMemBinary.ReadFunc = &ApplicationReadFuncPtr;
  GstMemBinary.WriteFunc = &ApplicationWriteFuncPtr;
  GstMemBinary.BlankCheckFunc = &ApplicationBlankCheckFuncPtr;
  GstMemBinary.HwSpecificServiceFunc = &ApplicationMemHwSpecificFuncPtr; 
  GstMemBinary.SuspendFunc = &ApplicationSuspendFuncPtr;
  GstMemBinary.ResumeFunc = &ApplicationResumeFuncPtr;
}

/* Clear value of application buffer */
void clear_read_buffer (void)
{
  /* Declaration local variable */
  uint32 LulLoopCount;
  /* Clear value of application buffer */
  for ( LulLoopCount = 0; LulLoopCount < MEMACC_MAX_BUFFER_SIZE; LulLoopCount++)
  {
    GaaReadBufferApplication[LulLoopCount] = MEMACC_SAMPLE_ZERO;
  }
}

void EndNotification0(MemAcc_AddressAreaIdType addressAreaId,
MemAcc_JobResultType jobResult)
{
  (void)addressAreaId;
  (void)jobResult;
}

void EndNotification1(MemAcc_AddressAreaIdType addressAreaId,
MemAcc_JobResultType jobResult)
{
  (void)addressAreaId;
  (void)jobResult;
}

void ApplicationLockNotification(void)
{
  GblLockNotificationFlag = TRUE;
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
