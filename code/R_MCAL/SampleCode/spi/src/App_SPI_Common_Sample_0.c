/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = App_SPI_Common_Sample_0.c                                                                           */
/*====================================================================================================================*/
/*                                                COPYRIGHT                                                           */
/*====================================================================================================================*/
/* Copyright(c) 2019-2025 Renesas Electronics Corporation                                                             */
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
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  28/10/2023  : Updated SW-VERSION.
 * 2.0.0:  25/07/2023  : Update from "Spi_Mapping.h to "Spi_MemMap.h". Re-write test app to support SPI Multi-core
 *         17/07/2023  : Updated SW-VERSION
 * 1.5.0:  07/03/2023  : Updated SW-VERSION
 * 1.4.3:  18/05/2022  : Add API cover
 * 1.4.2:  02/03/2022  : Updated SW-VERSION
 * 1.3.1:  13/05/2021  : Update to fix coding rule violations.
 * 1.2.0:  17/07/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 *                       Update sequence to utilize master-slave communication
 * 1.0.0:  06/03/2019  : Initial Version
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
#include "App_SPI_Common_Sample_0.h"
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
/* Variable used to store the Module Version Info */
STATIC Std_VersionInfoType App_GstVersionInfo;

/* Variable to check the result of API */
STATIC boolean App_GaaTestResult_0[SPI_CHECK_POINTS];

/* Variable to store the check point count */
STATIC uint8 App_GucCheckCount = 0;

#ifdef CCRH
uint32 App_GaaWriteBuffer0[] = {11, 12, 13, 14};
uint32 App_GaaReadBuffer0[4] = { 0 };
uint32 App_GaaWriteBuffer1[] = {21, 22, 23, 24};
uint32 App_GaaReadBuffer1[4] = { 0 };
#else
uint8 App_GaaWriteBuffer0[] = {11, 12, 13, 14};
uint8 App_GaaReadBuffer0[4] = { 0 };
uint8 App_GaaWriteBuffer1[] = {21, 22, 23, 24};
uint8 App_GaaReadBuffer1[4] = { 0 };
#endif

/* Variable to support CI */
const char *GucProgramStart;
const char *GucProgramStop;
const char *GucFinalResult;

/***********************************************************************************************************************
**                      User Function Prototype                                                                       **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/
int main(void)
{
  Std_ReturnType LddInitCheckValue;

  /* Initialize related MCAL modules */
  LddInitCheckValue = Init_MCAL();
  /* PROGRAM START */
  GucProgramStart = "CORE 0: PROGRAM START ON";
  if (E_OK == LddInitCheckValue)
  {
    #ifdef CCRH
    /* do nothing */
    #else
    /* Passing sequence to core 1 */
    Spi_PassTo_PE1();
    #endif

    /* This service is for getting the status of SPI Driver. */
    SPI_RESULT_ASSERT(SPI_IDLE == Spi_GetStatus());

    /* Read and check the SPI Driver version information. */
    #if (SPI_VERSION_INFO_API == STD_ON)
    Spi_GetVersionInfo(&App_GstVersionInfo);
    SPI_RESULT_ASSERT(
                        (SPI_VENDOR_ID == App_GstVersionInfo.vendorID) &&
                        (SPI_MODULE_ID == App_GstVersionInfo.moduleID) &&
                        (SPI_SW_MAJOR_VERSION == App_GstVersionInfo.sw_major_version) &&
                        (SPI_SW_MINOR_VERSION == App_GstVersionInfo.sw_minor_version) &&
                        (SPI_SW_PATCH_VERSION == App_GstVersionInfo.sw_patch_version)
                     );
    #endif
    
    /* This service is for writing data to the internal and external buffers */
    #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
    SPI_RESULT_ASSERT(E_OK == Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_001, (Spi_DataBufferType *)App_GaaWriteBuffer1));
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

    #if defined (CCRH) || defined (IAR)
    /* Passing sequence to core 1 */
    Spi_PassTo_PE1();
    #endif

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
    SPI_RESULT_ASSERT(E_OK == Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_001, (Spi_DataBufferType *)App_GaaReadBuffer1));
    #endif

    /* Passing sequence to core 1 */
    Spi_PassTo_PE1();

    /* This service is for writing data to internal buffers */
    #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
    SPI_RESULT_ASSERT(E_OK == Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_001, (Spi_DataBufferType *)App_GaaWriteBuffer1));
    #endif

    /* This service is for setting the asynchronous mode */
    #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1))
    SPI_RESULT_ASSERT(E_OK == Spi_SetAsyncMode(SPI_INTERRUPT_MODE));
    #endif

    /* Passing sequence to core 1 */
    Spi_PassTo_PE1();

    /* This service is for setting up transmission in slave unit */
    #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
    SPI_RESULT_ASSERT(E_OK == Spi_AsyncTransmit(SpiConf_SpiSequence_SpiSequence_001));
    #endif

    #if defined (CCRH) || defined (IAR)
    /* do nothing */
    #else
    /* Wait kernel API to execute request */
    App_GucKernelExcutionFlag = 1;
    while (App_GucKernelExcutionFlag == 1);

    /* Passing sequence to core 1 */
    Spi_PassTo_PE1();
    #endif

    /* Cancel on-going sequences */
    #if (SPI_CANCEL_API == STD_ON)
    Spi_Cancel(SpiConf_SpiSequence_SpiSequence_001);
    #endif

    /* Wait kernel API to execute request */
    App_GucKernelExcutionFlag = 1;
    while (App_GucKernelExcutionFlag == 1);

    #if defined (CCRH) || defined (IAR)
    /* Passing sequence to core 1 */
    Spi_PassTo_PE1();
    #endif

    /* Wait for transmission completed */
    SPI_RESULT_ASSERT(E_OK == Spi_WaitingTransmitCompleted());

    /* Get result of the Jobs */
    SPI_RESULT_ASSERT(SPI_JOB_OK == Spi_GetJobResult(SpiConf_SpiJob_SpiJob_001));

    /* Get result of the specified sequences */
    SPI_RESULT_ASSERT(SPI_SEQ_OK == Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_001));
        
    /* This service is for reading the data from internal buffer */
    #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
    SPI_RESULT_ASSERT(E_OK == Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_001, (Spi_DataBufferType *)App_GaaReadBuffer1));
    #endif

    /* Verify master/slave data */
    SPI_RESULT_ASSERT(E_OK == Spi_AppVerifyData((Spi_DataBufferType *)App_GaaWriteBuffer0, (Spi_DataBufferType *)App_GaaReadBuffer1, 2));

    /* Clear buffer */
    Spi_ClearBuffer((Spi_DataBufferType *)App_GaaReadBuffer1, sizeof(App_GaaReadBuffer1));
  
    /* Passing sequence to core 1 */
    Spi_PassTo_PE1();

    /* This service is for writing data to the internal and external buffers */
    #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB)) 
    SPI_RESULT_ASSERT(E_OK == Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_001, (Spi_DataBufferType *)App_GaaWriteBuffer1));
    #endif

    /* This service is for setting up transmission in slave unit */
    #if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
    SPI_RESULT_ASSERT(E_OK == Spi_AsyncTransmit(SpiConf_SpiSequence_SpiSequence_001));
    #endif

    /* Wait kernel API to execute request */
    App_GucKernelExcutionFlag = 1;
    while (App_GucKernelExcutionFlag == 1);

    /* Passing sequence to core 1 */
    Spi_PassTo_PE1();

    /* Wait for transmission completed */
    SPI_RESULT_ASSERT(E_OK == Spi_WaitingTransmitCompleted());   
    
    /* Get result of the Jobs */
    SPI_RESULT_ASSERT(SPI_JOB_OK == Spi_GetJobResult(SpiConf_SpiJob_SpiJob_001));

    /* Get result of the specified sequences */
    SPI_RESULT_ASSERT(SPI_SEQ_OK == Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_001));

    /* This service is for reading the data from internal buffer */
    #if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IB) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_IBEB))
    SPI_RESULT_ASSERT(E_OK == Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_001, (Spi_DataBufferType *)App_GaaReadBuffer1));
    #endif

    /* Verify master/slave data */
    SPI_RESULT_ASSERT(E_OK == Spi_AppVerifyData((Spi_DataBufferType *)App_GaaWriteBuffer0, (Spi_DataBufferType *)App_GaaReadBuffer1, 2));

    /* Stop timer */
    Gpt_Stop();

    /* De-Initializing the SPI Driver */
    SPI_RESULT_ASSERT(E_OK == Spi_DeInit());

    /* Verify final result */
    GucFinalResult = (SPI_TRUE == Spi_AppFinalCheck()) ? "CORE 0: EXECUTED OK" : "CORE 0: EXECUTED NOT OK";

    /*PROGRAM STOP */
    GucProgramStop = "CORE 0: PROGRAM STOP";

    /* Stop for debugging */
    #if defined (IAR)
      return 1;
    #else
      while(1);
    #endif
  } /* else No action required */

  /* Stop for debugging */
  return 0;
} /* End of main() function */

#define SPI_START_SEC_APPL_CODE
#include "Spi_MemMap.h"

/***********************************************************************************************************************
**                           Interrupt Function                                                                       **
***********************************************************************************************************************/
/* Timer Interrupt */
#if defined (CCRH)
#pragma interrupt Timer_Task_0(enable=false, fpu=true, fxu=false, callt=false)
#endif
_INTERRUPT_ FUNC(void, SPI_APPL_CODE) Timer_Task_0(void)
{
  /* This function is to be invoked in the scheduler
   * loop for asynchronous transmission in polling mode
   */
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
  App_GaaTestResult_0[App_GucCheckCount] = (SPI_TRUE == blValue) ? SPI_TRUE : SPI_FALSE;
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
      if (SPI_FALSE == App_GaaTestResult_0[LucCheckPointId])
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

FUNC(void, SPI_APPL_CODE) SpiJob0Notification(void)
{
  /* No Action Required */
}

FUNC(void, SPI_APPL_CODE) SpiSequence0EndNotification(void)
{
  /* No Action Required */
}

FUNC(void, SPI_APPL_CODE) SpiSequence0StartNotification_0(void)
{
  /* No Action Required */
}

#define SPI_STOP_SEC_APPL_CODE
#include "Spi_MemMap.h"

/***********************************************************************************************************************
**                          End of File                                                                               **
***********************************************************************************************************************/
