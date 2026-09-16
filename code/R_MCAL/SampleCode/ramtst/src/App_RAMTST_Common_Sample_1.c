/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_RAMTST_Common_Sample_1.c                                */
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
 *  1.0.1:  21/09/2023  : Remove pre-processor for 
 *                        RAMTST_CRITICAL_SECTION_PROTECTION
 *  1.0.0:  17/07/2023  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_RAMTST_Multi_Sample.h"
#include "App_RAMTST_Device_Sample.h"
#include "App_RAMTST_Common_Sample_1.h"
#include "SchM_RamTst.h"
#include "Os.h"
/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/
uint8 GucTestResult_Core1 = RAMTST_FAIL ; 
uint8 GucReturnCount_Core1 = 0;
uint8 GucLoopCount_Core1;

/* Variable used to store the Module Version Info */
RamTst_ExecutionStatusType App_ExeStatus_Core1;
RamTst_TestResultType App_TestResult_Core1;
RamTst_AlgorithmType App_AlgoType_Core1;
RamTst_NumberOfTestedCellsType App_NoOfTestedCells_Core1;
RamTst_AlgParamsIdType App_AlgParamsId_Core1;


/*******************************************************************************
**                      User Function Prototype                               **
*******************************************************************************/
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
int main_PE1(void)
{
  uint8 LucCoreId;
  /* Get core ID */
  LucCoreId = GetCoreID();

  ENABLE_INTERRUPT();
  while (GucStubInitFlag == 0);
  /* Initialize the RAMTST Driver */
  RamTst_Init(NULL_PTR);

  /* Set the test algorithm and its parameter set. */
  RamTst_SelectAlgParams(4);

  /* Check Global variable AlgParamsID after change ID*/
  if (4 == (*(RamTst_GaaGlobalAccPoint[LucCoreId].pAlgParamsId)))
  {
    GucReturnCount_Core1++;
  }

  /* Check current status*/
  if (RAMTST_EXECUTION_STOPPED == 
                      (*(RamTst_GaaGlobalAccPoint[LucCoreId].pExecutionStatus)))
  {
    GucReturnCount_Core1++;
  }

  /* Execute the full RAM Test in the foreground */
  RamTst_RunFullTest();

  if (RAMTST_EXECUTION_STOPPED == 
                      (*(RamTst_GaaGlobalAccPoint[LucCoreId].pExecutionStatus)))
  {
    GucReturnCount_Core1++;
  }

  /* Check Overall test result */
  if (RAMTST_RESULT_OK == 
                    (*(RamTst_GaaGlobalAccPoint[LucCoreId].pOverallTestResult)))
  {
    GucReturnCount_Core1++;
  } 

  RamTst_Allow();
  
  /* Get current RAM Test execution status */
  App_ExeStatus_Core1 = RamTst_GetExecutionStatus();
  
  if (RAMTST_EXECUTION_RUNNING == App_ExeStatus_Core1)
  {
    GucReturnCount_Core1++;
  } 

  GucTestCompleteStatus_Core1 = RAMTST_FALSE;
  do
  {
    RamTst_MainFunction();
    Delay();
  }while (GucTestCompleteStatus_Core1 != RAMTST_TRUE);

  /*Return the current RAM Test result */
  App_TestResult_Core1 = RamTst_GetTestResult();

  /* Check Overall test result */
  if (RAMTST_RESULT_OK == App_TestResult_Core1)
  {
    GucReturnCount_Core1++;
  } 

  /* Return the current RAM Test algorithm. */
  App_AlgoType_Core1 = RamTst_GetTestAlgorithm();

  /* Suspend current operation of background RAM Test */
  RamTst_Suspend();
  /* Get current RAM Test execution status */
  App_ExeStatus_Core1 = RamTst_GetExecutionStatus();

  /* Check Overall test result */
  if (RAMTST_EXECUTION_SUSPENDED == App_ExeStatus_Core1) 
  {
    GucReturnCount_Core1++;
  }

  for (GucLoopCount_Core1 = 0; GucLoopCount_Core1 < 2; GucLoopCount_Core1++)
  {
    RamTst_MainFunction();
    Delay();
  }

  /* Allow to continue the background RAM Test at the point is was suspended */
  RamTst_Resume();
  /* Get current RAM Test execution status */
  App_ExeStatus_Core1 = RamTst_GetExecutionStatus();

  /* Check Overall test result */
  if (RAMTST_EXECUTION_RUNNING == App_ExeStatus_Core1) 
  {
    GucReturnCount_Core1++;
  }

  GucTestCompleteStatus_Core1 = RAMTST_FALSE;
  do
  {
    RamTst_MainFunction();
    Delay();
  }while (GucTestCompleteStatus_Core1 != RAMTST_TRUE);

  /* Stopping the RAM Test. */
  RamTst_Stop();
  /* Get current RAM Test execution status */
  App_ExeStatus_Core1 = RamTst_GetExecutionStatus();

  /* Check Overall test result */
  if (RAMTST_EXECUTION_STOPPED == App_ExeStatus_Core1) 
  {
    GucReturnCount_Core1++;
  }

  /* Continue the RAM Test after calling RamTst_Stop */
  RamTst_Allow();
  
  GucTestCompleteStatus_Core1 = RAMTST_FALSE;
  /* Get current RAM Test execution status */
  App_ExeStatus_Core1 = RamTst_GetExecutionStatus();

  /* Check Overall test result */
  if (RAMTST_EXECUTION_RUNNING == App_ExeStatus_Core1) 
  {
    GucReturnCount_Core1++;
  }

  do
  {
    RamTst_MainFunction();
    Delay();
  }while (GucTestCompleteStatus_Core1 != RAMTST_TRUE);

  /* Return the ID of the current RAM Test algorithm parameter set. */
  App_AlgParamsId_Core1 = RamTst_GetAlgParams();

  /* Return the current number of tested cells per mainfunction cycle */
  App_NoOfTestedCells_Core1 = RamTst_GetNumberOfTestedCells();

  /* Stopping the RAM Test. */
  RamTst_Stop();
  App_NoOfTestedCells_Core1 = App_NoOfTestedCells_Core1 - 0x02;
  /* changes the current number of tested cells. */
  RamTst_ChangeNumberOfTestedCells(App_NoOfTestedCells_Core1);
  App_NoOfTestedCells_Core1 = RamTst_GetNumberOfTestedCells();

  /*Return the current RAM Test result */
  App_TestResult_Core1 = RamTst_GetTestResult();

  /* Check Overall test result */
  if (RAMTST_RESULT_OK == App_TestResult_Core1) 
  {
    GucReturnCount_Core1++;
  }

  /* Set the test algorithm and its parameter set. */
  RamTst_SelectAlgParams(5);

  /* Check Global variable AlgParamsID after change ID*/
  if (5 == (*(RamTst_GaaGlobalAccPoint[LucCoreId].pAlgParamsId)))
  {
    GucReturnCount_Core1++;
  }

  /* Test one RAM block in the foreground. */
  RamTst_RunPartialTest(1);

  App_TestResult_Core1 = RamTst_GetTestResultPerBlock(1);

  /* Check Overall test result */
  if (RAMTST_RESULT_OK == App_TestResult_Core1) 
  {
    GucReturnCount_Core1++;
  }

  /* Set the test algorithm and its parameter set. */
  RamTst_SelectAlgParams(6);

  /* Check Global variable AlgParamsID after change ID*/
  if (6 == (*(RamTst_GaaGlobalAccPoint[LucCoreId].pAlgParamsId)))
  {
    GucReturnCount_Core1++;
  }

  /* Execute the full RAM Test in the foreground */
  RamTst_RunFullTest();

  /* Check Overall test result */
  if (RAMTST_RESULT_OK == 
                    (*(RamTst_GaaGlobalAccPoint[LucCoreId].pOverallTestResult)))
  {
    GucReturnCount_Core1++;
  } 

  RamTst_DeInit();

  /* Check Overall test result */
  if (RAMTST_EXECUTION_UNINIT == 
                      (*(RamTst_GaaGlobalAccPoint[LucCoreId].pExecutionStatus))) 
  {
    GucReturnCount_Core1++;
  }

  /* End of main() function */
  
  if (16 == GucReturnCount_Core1)
  {
    GucTestResult_Core1 = RAMTST_PASS;
  }
  sample_end();
  return 0 ;
}

/******************************************************************************
**                           Interrupt Function                              **
******************************************************************************/
/******************************************************************************
**                           User Function Definition                        **
******************************************************************************/
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
