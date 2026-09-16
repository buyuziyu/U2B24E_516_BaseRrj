/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_RAMTST_Common_Sample.c                                  */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for RAM TEST Driver Component        */
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
 *  1.4.1:  30/06/2025  : Update SW-VERSION
 *  1.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E 
 *  1.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0:  31/12/2024  : Update SW-Version for Ver22.02.00/Ver22.02.00.D U2Bx
 *                        Final release
 *  1.1.2:  31/10/2024  : Update SW-VERSION to 1.1.2
 *  1.1.1:  29/07/2024  : Update to support U2Bx-E SampleApp 
 *  1.0.1:  21/09/2023  : Remove pre-processor for 
 *                        RAMTST_CRITICAL_SECTION_PROTECTION
 *  1.0.0:  20/06/2023  : Add confirmation checkpoint to verify Sample
 *                        Application result
 *          19-05-2023  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_RAMTST_Common_Sample.h"
#include "App_RAMTST_Device_Sample.h"
#include "SchM_RamTst.h"

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/
uint8 GucVerCheckStatus = RAMTST_FAIL;
uint8 GucTestResult = RAMTST_FAIL; 
uint8 GucReturnCount = 0;
uint8 GucTestCompleteStatus;
uint8 GucErrorStatus;
uint8 GucLoopCount;
uint8 LucCoreId = 0 ;
/* Variable used to store the Module Version Info */
Std_VersionInfoType GddVersionInfo;
RamTst_ExecutionStatusType App_ExeStatus;
RamTst_TestResultType App_TestResult;
RamTst_AlgorithmType App_AlgoType;
RamTst_NumberOfTestedCellsType App_NoOfTestedCells;
RamTst_AlgParamsIdType App_AlgParamsId;

/*******************************************************************************
**                      User Function Prototype                               **
*******************************************************************************/
void Delay(void);
extern void Wdg_Init(void);
extern void Mcu_Init(void);
extern void Port_Init(void);
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

int main(void)
#if defined (RUN_OTHER_PE)
{
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

  /* Initialize Port */
  Port_Init();

  /* Initialize MCU */
  Mcu_Init();

  RamTst_GetVersionInfo(&GddVersionInfo);
  /* Check for the correctness of version information */
  if ((GddVersionInfo.vendorID == RAMTST_VENDOR_ID) &&
      (GddVersionInfo.moduleID == RAMTST_MODULE_ID) &&
      (GddVersionInfo.sw_major_version == RAMTST_SW_MAJOR_VERSION) &&
      (GddVersionInfo.sw_minor_version == RAMTST_SW_MINOR_VERSION) &&
      (GddVersionInfo.sw_patch_version == RAMTST_SW_PATCH_VERSION))
  {

    GucVerCheckStatus = RAMTST_PASS;
  }
  else
  {
    GucVerCheckStatus = RAMTST_FAIL;
  }

  /* Initialize the RAMTST Driver */
  RamTst_Init(NULL_PTR);
  /* Execute the full RAM Test in the foreground */
  RamTst_RunFullTest();
  /* Check Overall test result */
  if (RAMTST_RESULT_OK == RamTst_GetTestResult())
  {
    GucReturnCount++;
  } 
  /* Set the test algorithm and its parameter set. */
  RamTst_SelectAlgParams(2);
  if (2 == RamTst_GetAlgParams())
  {
    GucReturnCount++;
  } 
  /* Test specific RAM block in the foreground. */ 
  RamTst_RunPartialTest(2); 
  if (RAMTST_RESULT_OK == RamTst_GetTestResultPerBlock(2))
  {
    GucReturnCount++;
  } 
  /* Execute the full RAM Test in the foreground */
  RamTst_RunFullTest();
  /* Confirm test result after run full test */
  if (RAMTST_RESULT_OK == RamTst_GetTestResult())
  {
    GucReturnCount++;
  } 
  /* Set the test algorithm and its parameter set. */
  RamTst_SelectAlgParams(3);
  /* Allow Background test */
  RamTst_Allow();
  if (RAMTST_EXECUTION_RUNNING == RamTst_GetExecutionStatus())
  {
    GucReturnCount++;
  } 
  GucTestCompleteStatus = RAMTST_FALSE;
  /* Run one sequence of background test */
  RamTst_MainFunction();
  /* Suspend Background test */
  RamTst_Suspend();
  if (RAMTST_EXECUTION_SUSPENDED == RamTst_GetExecutionStatus())
  {
    GucReturnCount++;
  } 
  GucTestCompleteStatus = RAMTST_FALSE;
  for (GucLoopCount = 0; GucLoopCount < 3; GucLoopCount++)
  {
    RamTst_MainFunction();
    Delay();
  }
  /* Confirm that RamTst_Mainfunction will not run when suspended*/
  if (RAMTST_RESULT_UNDEFINED == RamTst_GetTestResult())
  {
    GucReturnCount++;
  } 
  /* Resume Background test */
  RamTst_Resume();
  /* Check current status */
  if (RAMTST_EXECUTION_RUNNING == RamTst_GetExecutionStatus())
  {
    GucReturnCount++;
  } 
  /* Resume background test */
  GucTestCompleteStatus = RAMTST_FALSE;
  do
  {
    RamTst_MainFunction();
    Delay();
  } while (GucTestCompleteStatus != RAMTST_TRUE);
  /*Invoke RamTst_Stop*/
  RamTst_Stop();
  if (RAMTST_RESULT_OK == RamTst_GetTestResult())
  {
    GucReturnCount++;
  } 
  /* Set the test algorithm and its parameter set */
  RamTst_SelectAlgParams(4);
  /* Get Current number of tested cell */
  App_NoOfTestedCells = RamTst_GetNumberOfTestedCells();
  /* Change current number of tested cell */
  RamTst_ChangeNumberOfTestedCells(App_NoOfTestedCells - RAMTST_TWO);
  /* Invoke RamTst_RunFullTest */
  RamTst_RunFullTest();
  /* Confirm test result */
  if (RAMTST_RESULT_OK == RamTst_GetTestResult())
  {
    GucReturnCount++;
  } 
  /* Set the test algorithm and its parameter set */
  RamTst_SelectAlgParams(5);
  if (RAMTST_TRANSP_GALPAT_TEST == RamTst_GetTestAlgorithm())
  {
    GucReturnCount++;
  } 
  /* Invoke RamTst_RunFullTest */
  RamTst_RunFullTest();
  /* Confirm test result */
  if (RAMTST_RESULT_OK == RamTst_GetTestResult())
  {
    GucReturnCount++;
  } 
  /* Set the test algorithm and its parameter set */
  RamTst_SelectAlgParams(6);
  /* Allow Background test */
  RamTst_Allow();
  GucTestCompleteStatus = RAMTST_FALSE;
  do
  {
    RamTst_MainFunction();
    Delay();
  } while (GucTestCompleteStatus != RAMTST_TRUE);
  /* Confirm test result */
  if (RAMTST_RESULT_OK == RamTst_GetTestResult())
  {
    GucReturnCount++;
  } 
  RamTst_DeInit();
  if (13 == GucReturnCount)
  {
    GucTestResult = RAMTST_PASS;
  }
  else
  {
    GucTestResult = RAMTST_FAIL;
  }

  return(0);
} /* End of main() function */



/******************************************************************************
**                           Interrupt Function                              **
******************************************************************************/
/******************************************************************************
**                           User Function Definition                        **
******************************************************************************/
void Delay(void)
{
  uint16 LusDelayCounter;
  for (LusDelayCounter = 0 ; LusDelayCounter < 0xFFFF; LusDelayCounter++);
}
/******************************************************************************
**                           Notification Functions                          **
******************************************************************************/
/* Notification for test complete */
void Complete_Notify(void)
{
  GucTestCompleteStatus = RAMTST_TRUE;
}

/* Error Notification */
void Error_Notify(void)
{
  GucErrorStatus = RAMTST_TRUE;
}

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
