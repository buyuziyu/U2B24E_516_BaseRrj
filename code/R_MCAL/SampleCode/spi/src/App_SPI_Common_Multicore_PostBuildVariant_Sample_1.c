/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = App_SPI_Common_Multicore_PostBuildVariant_Sample_1.c                                                */
/*====================================================================================================================*/
/*                                                COPYRIGHT                                                           */
/*====================================================================================================================*/
/* Copyright(c) 2025 Renesas Electronics Corporation                                                                  */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application for SPI Driver Component                                                     */
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
**                      Revision Control History                                                                      **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 * 2.0.3:    24/03/2024  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                      Instance Index                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Spi.h"
#include "App_SPI_Device_Sample.h"
#include "App_SPI_Common_Sample_1.h"
#include "App_SPI_Multi_Sample.h"
#include "Spi_Kernel.h"
#include "Dem.h"

/***********************************************************************************************************************
**                      Function Prototypes                                                                           **
***********************************************************************************************************************/
#define SPI_START_SEC_APPL_CODE
#include "Spi_MemMap.h"

STATIC FUNC(void, SPI_APPL_CODE) SPI_RESULT_ASSERT(boolean blValue);

STATIC FUNC(Std_ReturnType, SPI_APPL_CODE) Spi_WaitingTransmitCompleted(void);

STATIC FUNC(boolean, SPI_APPL_CODE) Spi_AppFinalCheck(void);

STATIC FUNC(Std_ReturnType, SPI_APPL_CODE)
Spi_AppVerifyData(const Spi_DataBufferType *LpSrc, const Spi_DataBufferType *LpDest, uint16 LusLength);

STATIC FUNC(void, SPI_APPL_CODE) Spi_ClearBuffer(uint8 *LpBuffer, uint32 LulDataLength);

#define SPI_STOP_SEC_APPL_CODE
#include "Spi_MemMap.h"

/***********************************************************************************************************************
**                         Global Data                                                                                **
***********************************************************************************************************************/
/* Variable to check the result of API */
#if defined (CCRH)
volatile boolean App_GaaTestResult_1[SPI_CHECK_POINTS];
#else
STATIC boolean App_GaaTestResult_1[SPI_CHECK_POINTS];
#endif

/* Variable to store the check point count */
STATIC uint8 App_GucCheckCount = 0;

/* Variable to support CI */
const char *GucProgramStart1;
const char *GucProgramStop1;
const char *GucFinalResult1;

/***********************************************************************************************************************
**                      User Function Prototype                                                                       **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/
int main_PE1(void)
{
  volatile uint32 LulCounter;
  /* Delay until core 0 is reach */
  for (LulCounter = 0; LulCounter < 20000 ; LulCounter++);

  /* Enable Interrupt */
  ENABLE_INTERRUPT();

  /* Passing sequence to core 0 */
  Spi_PassTo_PE0();

  EXECUTE_SYNCP();

  /* PROGRAM START */
  GucProgramStart1 = "CORE 1: PROGRAM START ON";
  
  /* This service is for writing data to external buffers */
  #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_EB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
  SPI_RESULT_ASSERT(E_OK == Spi_SetupEB(SpiConf_SpiChannel_SpiChannel, (Spi_DataBufferType *)App_GaaWriteBuffer0_Variant1, (Spi_DataBufferType *)App_GaaReadBuffer0_Variant1, 2));
  #endif

  /* This service is for setting up transmission in slave unit */
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  SPI_RESULT_ASSERT(E_OK == Spi_AsyncTransmit(SpiConf_SpiSequence_SpiSequence));
  #endif

  /* Cancel on-going sequences */
  #if (SPI_CANCEL_API == STD_ON)
  Spi_ForceCancel(SpiConf_SpiSequence_SpiSequence);
  #endif

  /* Wait kernel API to execute request */
  App_GucKernelExcutionFlag = 1;
  while (App_GucKernelExcutionFlag == 1);

  /* Passing sequence to core 0 */
  Spi_PassTo_PE0();

  /* Get status of specified SPI Hardware micro-controller peripheral */
  #if (SPI_HW_STATUS_API == STD_ON)
  SPI_RESULT_ASSERT(SPI_IDLE == Spi_GetHWUnitStatus(SPI_MSPI0));
  #endif

  /* Get result of the Jobs */
  SPI_RESULT_ASSERT(SPI_JOB_FAILED == Spi_GetJobResult(SpiConf_SpiJob_SpiJob));

  /* Get result of the specified sequences */
  SPI_RESULT_ASSERT(SPI_SEQ_CANCELED == Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence));

  /* Passing sequence to core 0 */
  Spi_PassTo_PE0();
    
  /* This service is for writing data to external buffers */
  #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_EB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
  SPI_RESULT_ASSERT(E_OK == Spi_SetupEB(SpiConf_SpiChannel_SpiChannel, (Spi_DataBufferType *)App_GaaWriteBuffer0_Variant1, (Spi_DataBufferType *)App_GaaReadBuffer0_Variant1, 2));
  #endif
  
  /* This service is for setting up transmission in slave unit */
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  SPI_RESULT_ASSERT(E_OK == Spi_AsyncTransmit(SpiConf_SpiSequence_SpiSequence));
  #endif

  /* Cancel on-going sequences */
  #if (SPI_CANCEL_API == STD_ON)
  Spi_Cancel(SpiConf_SpiSequence_SpiSequence);
  #endif

  /* Wait kernel API to execute request */
  App_GucKernelExcutionFlag = 1;
  while (App_GucKernelExcutionFlag == 1);

  /* Passing sequence to core 0 */
  Spi_PassTo_PE0();

  /* Wait for transmission completed */
  SPI_RESULT_ASSERT(E_OK == Spi_WaitingTransmitCompleted());

  /* Get result of the Jobs */
  SPI_RESULT_ASSERT(SPI_JOB_OK == Spi_GetJobResult(SpiConf_SpiJob_SpiJob));

  /* Get result of the specified sequences */
  SPI_RESULT_ASSERT(SPI_SEQ_OK == Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence));
  
  /* Verify master/slave data */
  SPI_RESULT_ASSERT(E_OK == Spi_AppVerifyData((Spi_DataBufferType *)App_GaaWriteBuffer1_Variant1, (Spi_DataBufferType *)App_GaaReadBuffer0_Variant1, 2));

  /* Clear buffer */
  Spi_ClearBuffer((Spi_DataBufferType *)App_GaaReadBuffer0_Variant1, sizeof(App_GaaReadBuffer0_Variant1));
  
  /* Passing sequence to core 0 */
  Spi_PassTo_PE0();

  /* This service is for writing data to external buffers */
  #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_EB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
  SPI_RESULT_ASSERT(E_OK == Spi_SetupEB(SpiConf_SpiChannel_SpiChannel, (Spi_DataBufferType *)App_GaaWriteBuffer0_Variant1, (Spi_DataBufferType *)App_GaaReadBuffer0_Variant1, 2));
  #endif
  
  /* This service is for setting up transmission in master unit */
  App_GucKernelExcutionFlag = 1;
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  SPI_RESULT_ASSERT(E_OK == Spi_SyncTransmit(SpiConf_SpiSequence_SpiSequence));
  #endif

  /* Wait kernel API to execute request */
  while (App_GucKernelExcutionFlag == 1);

  /* Passing sequence to core 0 */
  Spi_PassTo_PE0();

  /* Wait for transmission completed */
  SPI_RESULT_ASSERT(E_OK == Spi_WaitingTransmitCompleted());
    
  /* Get result of the Jobs */
  SPI_RESULT_ASSERT(SPI_JOB_OK == Spi_GetJobResult(SpiConf_SpiJob_SpiJob));

  /* Get result of the specified sequences */
  SPI_RESULT_ASSERT(SPI_SEQ_OK == Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence));

  /* Verify master/slave data */
  SPI_RESULT_ASSERT(E_OK == Spi_AppVerifyData((Spi_DataBufferType *)App_GaaWriteBuffer1_Variant1, (Spi_DataBufferType *)App_GaaReadBuffer0_Variant1, 2));
  
  /* Passing sequence to core 0 */
  Spi_PassTo_PE0();

  while(App_Finish_Variant == 0);

/**********************************************************************************************************************/
/*                                                VARIANT 2                                                           */
/**********************************************************************************************************************/
  Gpt_Stop();

  /* Initialize EIC registers on core 1 for Variant 2 */
  Spi_IvtInit_Variant();

  /* Initialize GPT for core 1 */
  Gpt_Init_1();

  /* Initialize SPI */
  Spi_Init(Spi_Config_Variant_2);

  /* Passing sequence to core 0 */
  Spi_PassTo_PE0();

  /* This service is for writing data to the internal and external buffers */
  #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
  SPI_RESULT_ASSERT(E_OK == Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_001, (Spi_DataBufferType *)App_GaaWriteBuffer1_Variant2));
  #endif

  /* This service is for setting up the polling mode */
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1))
  SPI_RESULT_ASSERT(E_OK == Spi_SetAsyncMode(SPI_POLLING_MODE));
  #endif

  /* This service is for setting up transmission in slave unit */
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  SPI_RESULT_ASSERT(E_OK == Spi_AsyncTransmit(SpiConf_SpiSequence_SpiSequence_001));
  #endif

  /* Cancel on-going sequences */
  #if (SPI_FORCE_CANCEL_API == STD_ON)
  Spi_ForceCancel(SpiConf_SpiSequence_SpiSequence_001);
  #endif

  /* Wait kernel API to execute request */
  App_GucKernelExcutionFlag = 1;
  while (App_GucKernelExcutionFlag == 1);

  /* Passing sequence to core 0 */
  Spi_PassTo_PE0();

  /* Get status of specified SPI Hardware micro-controller peripheral */
  #if (SPI_HW_STATUS_API == STD_ON)
  SPI_RESULT_ASSERT(SPI_IDLE == Spi_GetHWUnitStatus(SPI_MSPI1));
  #endif

  /* Get result of the Jobs */
  SPI_RESULT_ASSERT(SPI_JOB_FAILED == Spi_GetJobResult(SpiConf_SpiJob_SpiJob_001));

  /* Get result of the specified sequences */
  SPI_RESULT_ASSERT(SPI_SEQ_CANCELED == Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_001));
  
  /* This service is for reading the data from internal buffer */
  #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
  SPI_RESULT_ASSERT(E_OK == Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_001, (Spi_DataBufferType *)App_GaaReadBuffer1_Variant2));
  #endif

  /* Passing sequence to core 1 */
  Spi_PassTo_PE0();

  /* This service is for writing data to the internal and external buffers */
  #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)) 
  SPI_RESULT_ASSERT(E_OK == Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_001, (Spi_DataBufferType *)App_GaaWriteBuffer1_Variant2));
  #endif

  /* This service is for setting the asynchronous mode */
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1))
  SPI_RESULT_ASSERT(E_OK == Spi_SetAsyncMode(SPI_INTERRUPT_MODE));
  #endif

  /* This service is for setting up transmission in slave unit */
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  SPI_RESULT_ASSERT(E_OK == Spi_AsyncTransmit(SpiConf_SpiSequence_SpiSequence_001));
  #endif

  /* Cancel on-going sequences */
  #if (SPI_CANCEL_API == STD_ON)
  Spi_Cancel(SpiConf_SpiSequence_SpiSequence_001);
  #endif
  
  /* Wait kernel API to execute request */
  App_GucKernelExcutionFlag = 1;
  while (App_GucKernelExcutionFlag == 1);

  /* Passing sequence to core 1 */
  Spi_PassTo_PE0();

  /* Wait for transmission completed */
  SPI_RESULT_ASSERT(E_OK == Spi_WaitingTransmitCompleted());

  /* Get result of the Jobs */
  SPI_RESULT_ASSERT(SPI_JOB_OK == Spi_GetJobResult(SpiConf_SpiJob_SpiJob_001));

  /* Get result of the specified sequences */
  SPI_RESULT_ASSERT(SPI_SEQ_OK == Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_001));

  /* This service is for reading the data from internal buffer */
  #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
  SPI_RESULT_ASSERT(E_OK == Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_001, (Spi_DataBufferType *)App_GaaReadBuffer1_Variant2));
  #endif

  /* Verify master/slave data */
  SPI_RESULT_ASSERT(E_OK == Spi_AppVerifyData((Spi_DataBufferType *)App_GaaWriteBuffer0_Variant2, (Spi_DataBufferType *)App_GaaReadBuffer1_Variant2, 2));

  /* Clear buffer */
  Spi_ClearBuffer((Spi_DataBufferType *)App_GaaReadBuffer1_Variant2, sizeof(App_GaaReadBuffer1_Variant2));
    
  /* Passing sequence to core 1 */
  Spi_PassTo_PE0();

  /* This service is for writing data to the internal and external buffers */
  #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)) 
  SPI_RESULT_ASSERT(E_OK == Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_001, (Spi_DataBufferType *)App_GaaWriteBuffer1_Variant2));
  #endif

  /* This service is for setting up transmission in slave unit */
  #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
  SPI_RESULT_ASSERT(E_OK == Spi_AsyncTransmit(SpiConf_SpiSequence_SpiSequence_001));
  #endif
  
  /* Wait kernel API to execute request */
  App_GucKernelExcutionFlag = 1;
  while (App_GucKernelExcutionFlag == 1);

  /* Passing sequence to core 1 */
  Spi_PassTo_PE0();

  /* Wait for transmission completed */
  SPI_RESULT_ASSERT(E_OK == Spi_WaitingTransmitCompleted());
  
  /* Get result of the Jobs */
  SPI_RESULT_ASSERT(SPI_JOB_OK == Spi_GetJobResult(SpiConf_SpiJob_SpiJob_001));

  /* Get result of the specified sequences */
  SPI_RESULT_ASSERT(SPI_SEQ_OK == Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_001));

  /* This service is for reading the data from internal buffer */
  #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
  SPI_RESULT_ASSERT(E_OK == Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_001, (Spi_DataBufferType *)App_GaaReadBuffer1_Variant2));
  #endif
  
  /* Verify master/slave data */
  SPI_RESULT_ASSERT(E_OK == Spi_AppVerifyData((Spi_DataBufferType *)App_GaaWriteBuffer0_Variant2, (Spi_DataBufferType *)App_GaaReadBuffer1_Variant2, 2));

  /* Stop timer */
  Gpt_Stop();

  /* Clear buffer */
  Spi_ClearBuffer((Spi_DataBufferType *)App_GaaReadBuffer1_Variant2, sizeof(App_GaaReadBuffer1_Variant2));
    
  Spi_AllCoreRun();

  /* Verify final result */
  GucFinalResult1 = (SPI_TRUE == Spi_AppFinalCheck()) ? "CORE 1: EXECUTED OK" : "CORE 1: EXECUTED NOT OK";

  /*PROGRAM STOP */
  GucProgramStop1 = "CORE 1: PROGRAM STOP";

  /* Stop for debugging */
  #if defined (IAR)
    return 1;
  #else
    while(1);
  #endif
} /* End of main() function */

#define SPI_START_SEC_APPL_CODE
#include "Spi_MemMap.h"

/***********************************************************************************************************************
**                           Interrupt Function                                                                       **
***********************************************************************************************************************/
/* Timer Interrupt */
#if defined (CCRH)
#pragma interrupt Timer_Task_1(enable=false, fpu=true, fxu=false, callt=false)
#endif
_INTERRUPT_ FUNC(void, SPI_APPL_CODE) Timer_Task_1(void)
{
  /* This function is to be invoked in the scheduler loop for asynchronous transmission in polling mode */
  if (App_GucKernelExcutionFlag == 1)
  {
    Spi_Kernel_AsyncTransmit();
    Spi_Kernel_SyncTransmit();
    Spi_Kernel_Cancel();
    Spi_Kernel_ForceCancel();
    App_GucKernelExcutionFlag = 0;
  }
  Spi_MainFunction_Handling();
}

/***********************************************************************************************************************
**                                   This function is to checking checkpoint in Sample App                            **
***********************************************************************************************************************/
STATIC FUNC(void, SPI_APPL_CODE) SPI_RESULT_ASSERT(boolean blValue)
{
  App_GaaTestResult_1[App_GucCheckCount] = (SPI_TRUE == blValue) ? SPI_TRUE : SPI_FALSE;
  App_GucCheckCount += 1U;
}

/***********************************************************************************************************************
**                                   This function is to waiting for transmission is completed                        **
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, SPI_APPL_CODE) Spi_WaitingTransmitCompleted(void)
{
  Spi_StatusType LenDriverStatus;
  /* Wait for transmission completed */
  do
  {
    LenDriverStatus = Spi_GetStatus();
  } while (SPI_IDLE != LenDriverStatus);

  if (SPI_IDLE != LenDriverStatus)
    return E_NOT_OK;
  else
    return E_OK;
}

/***********************************************************************************************************************
**                                     The function to confirm sample app result                                      **
***********************************************************************************************************************/
STATIC FUNC(boolean, SPI_APPL_CODE) Spi_AppFinalCheck(void)
{
  uint8 LucCheckPointId;
  boolean LblRet;
  LblRet = SPI_TRUE;

  /* Check if there is no HW error */
  if (Dem_EventStatus == DEM_EVENT_STATUS_PASSED)
  {
    /* Verify check points */
    for (LucCheckPointId = 0U; ((LucCheckPointId < App_GucCheckCount) && (SPI_FALSE != LblRet)); LucCheckPointId++)
    {
      if (SPI_FALSE == App_GaaTestResult_1[LucCheckPointId])
      {
        /* At least one check point failed, set final result as failure */
        LblRet = SPI_FALSE;
      } /* else No action required */
    }
  }
  else
  {
    /* There is a DEM error, set final result as failure */
    LblRet = SPI_FALSE;
  }
  return LblRet;
}

/***********************************************************************************************************************
**                                   This function is to clear application buffer                                     **
***********************************************************************************************************************/
STATIC FUNC(void, SPI_APPL_CODE) Spi_ClearBuffer(uint8 *LpBuffer, uint32 LulDataLength)
{
  uint32 i = 0U;
  for (i = 0U; i < LulDataLength; i++)
  {
    *LpBuffer = SPI_ZERO;
    LpBuffer++;
  }
}

/***********************************************************************************************************************
**                                   This function is to compare application buffer                                   **
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, SPI_APPL_CODE)
Spi_AppVerifyData(const Spi_DataBufferType *LpSrc, const Spi_DataBufferType *LpDest, uint16 LusLength)
{
  uint16 LusCnt;
  Std_ReturnType LenReturnValue;

  /* Initialize default value for local variable */
  LenReturnValue = E_OK;

  for (LusCnt = 0U; LusCnt < LusLength; LusCnt++)
  {
    if (LpSrc[LusCnt] != LpDest[LusCnt])
    {
      LenReturnValue = E_NOT_OK;
    } /* else No action required */
  }
  return LenReturnValue;
}

#define SPI_STOP_SEC_APPL_CODE
#include "Spi_MemMap.h"

/***********************************************************************************************************************
**                           Notification Functions                                                                   **
***********************************************************************************************************************/
#define SPI_START_SEC_APPL_CODE
#include "Spi_MemMap.h"

FUNC(void, SPI_APPL_CODE) SpiJob0Notification_1(void)
{
  /* No Action Required */
}

FUNC(void, SPI_APPL_CODE) SpiSequence0EndNotification_1(void)
{
  /* No Action Required */
}

FUNC(void, SPI_APPL_CODE) SpiSequence0StartNotification_1(void)
{
  /* No Action Required */
}

#define SPI_STOP_SEC_APPL_CODE
#include "Spi_MemMap.h"

/***********************************************************************************************************************
**                          End of File                                                                               **
***********************************************************************************************************************/
