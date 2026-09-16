/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_FLSTST_Common_Sample.c                                  */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for FLSTST Driver Component          */
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
 * 1.4.1:  30/06/2025  : Update SW-VERSION
 * 1.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 1.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D 
 *                       Final Relase
 * 1.1.2:  31/10/2024  : Update SW-VERSION to 1.1.2
 * 1.0.0:  17/03/2023  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_FLSTST_Common_Sample.h"
#include "App_FLSTST_Device_Sample.h"
/*******************************************************************************
**                            Macros                                          **
*******************************************************************************/

/*******************************************************************************
**                        Global variables                                    **
*******************************************************************************/
/* Version check result */
boolean GblVerCheckStatus;
/* Check pass fail */
volatile boolean GblTestResult;
volatile boolean GblTestState;
volatile uint8 GucTestNo;
/* Variable used to store the Module Version Info */
Std_VersionInfoType GddVersionInfo;

/* API return value */
Std_ReturnType GddReturnValue;
FlsTst_StateType GddExecutionState;
Std_ReturnType GddEccTestResult;
FlsTst_ErrorDetailsType GddEccErrorDetailResult;

/* Variable to store fore ground test result */
FlsTst_TestSignatureFgndType GulSignatureFgnd;
FlsTst_TestResultFgndType GucTestResultFgnd;

/* Background test callback status */
uint8 GblTestCompleteStatus;
FlsTst_TestResultBgndType GucTestResultBgnd;



/*******************************************************************************
**                        User function prototypes                            **
*******************************************************************************/
void TestPass(void);
void TestFail(void);
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
int main(void)
#if defined(RUN_OTHER_PE)
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
  GblTestResult = FLSTST_TRUE;
  uint8 LucLoopCount;

  /* To get the version of the FLSTST Driver module */
  FlsTst_GetVersionInfo(&GddVersionInfo);

  /* Check for the correctness of version information */
  if ((GddVersionInfo.vendorID == FLSTST_VENDOR_ID) &&
   (GddVersionInfo.moduleID == FLSTST_MODULE_ID) &&
   (GddVersionInfo.sw_major_version == FLSTST_SW_MAJOR_VERSION) &&
   (GddVersionInfo.sw_minor_version == FLSTST_SW_MINOR_VERSION) &&
   (GddVersionInfo.sw_patch_version == FLSTST_SW_PATCH_VERSION))
  {
    GblVerCheckStatus = FLSTST_TRUE;
  }
  else
  {
    GblVerCheckStatus = FLSTST_FALSE;
  }
  
  /* Initialize the FLSTST Driver */
  FlsTst_Init(FlsTst_Config);

  /* Get the current FlsTst Execution state */
  GddExecutionState = FlsTst_GetCurrentState();
  
  /* Test ECC circuitry */
  GddEccTestResult = FlsTst_TestEcc();
  
  if (E_OK == GddEccTestResult)
  {
	GblTestResult = FLSTST_TRUE;
  }
  else
  {
	GblTestResult = FLSTST_FALSE;
  }

  /* Get the Ecc circuitry error details */
  GddEccErrorDetailResult = FlsTst_GetErrorDetails();
  
  /* Foreground flash test  */
  GddReturnValue = FlsTst_StartFgnd(FLSTST_ZERO);

  if (GddReturnValue == E_OK)
  {
    GulSignatureFgnd = FlsTst_GetTestSignatureFgnd();
    GucTestResultFgnd = FlsTst_GetTestResultFgnd();

  if ((FlsTst_TestResultType)GucTestResultFgnd == FLSTST_RESULT_OK)
    {
      GblTestResult = FLSTST_TRUE;
    }
    else
    {
      GblTestResult = FLSTST_FALSE;
    }

  }
  else
  {
    // no action required
  }
  
  /* Background  flash test*/
  GblTestCompleteStatus = FLSTST_FALSE;

 /* Call until test completed callback notification function  called */
  while (GblTestCompleteStatus != FLSTST_TRUE)
  {
    FlsTst_MainFunction();
  }

  /* Get the test Bgnd test status */
  GucTestResultBgnd = FlsTst_GetTestResultBgnd();
  
  if ((FlsTst_TestResultType)GucTestResultBgnd.enTestResultBgnd == FLSTST_RESULT_OK)
  {
	GblTestResult = FLSTST_TRUE;
  } 
  else
  {
	GblTestResult = FLSTST_FALSE;
  }

  /* Get the current FlsTst Execution state */
  GddExecutionState = FlsTst_GetCurrentState();

  /* Check if the state return init after a success test */
  if (FLSTST_INIT == GddExecutionState)
  {
    GblTestState = FLSTST_TRUE;
  }
  else
  {
    GblTestState = FLSTST_FALSE;
  }

  /* Invoke  FlsTst main function */
  FlsTst_MainFunction();

  /* Get the current FlsTst Execution state */
  GddExecutionState = FlsTst_GetCurrentState();

  /* Check if the state is running */
  if (FLSTST_RUNNING == GddExecutionState)
  {
    GblTestState = FLSTST_TRUE;
  }
  else
  {
    GblTestState = FLSTST_FALSE;
  }

  /*Suspend the on going background flash test */
  FlsTst_Suspend();

  /* Get the current FlsTst Execution state */
  GddExecutionState = FlsTst_GetCurrentState();

  /* Check if the state return suspended */
  if (FLSTST_SUSPENDED == GddExecutionState)
  {
    GblTestState = FLSTST_TRUE;
  }
  else
  {
    GblTestState = FLSTST_FALSE;
  }

  for (LucLoopCount = FLSTST_ZERO; LucLoopCount < FLSTST_TWO ;LucLoopCount++)
  {
    FlsTst_MainFunction();
  }

  /*Resume the suspended background flash test */
  FlsTst_Resume();

  /* Get the current FlsTst Execution state */
  GddExecutionState = FlsTst_GetCurrentState();

  /* Check if the state return to running */
  if (FLSTST_RUNNING == GddExecutionState)
  {
    GblTestState = FLSTST_TRUE;
  }
  else
  {
    GblTestState = FLSTST_FALSE;
  }

  for (LucLoopCount = FLSTST_ZERO; LucLoopCount < FLSTST_TWO ;LucLoopCount++)
  {
    FlsTst_MainFunction();
  }

  /* Abort the background test */
  FlsTst_Abort();

  /* Get the current FlsTst Execution state */
  GddExecutionState = FlsTst_GetCurrentState();

  /* Check if the Bgnd test was aborted */
  if (FLSTST_ABORTED == GddExecutionState)
  {
    GblTestState = FLSTST_TRUE;
  }
  else
  {
    GblTestState = FLSTST_FALSE;
  }

  for (LucLoopCount = FLSTST_ZERO; LucLoopCount < FLSTST_TWO ;LucLoopCount++)
  {
    FlsTst_MainFunction();
  }
  
  /* De-initialize FLSTST Driver */
  FlsTst_DeInit();
  
  /* Get the current FlsTst Execution state */
  GddExecutionState = FlsTst_GetCurrentState();

  /* Check the last state after De init module */
  if (FLSTST_UNINIT == GddExecutionState)
  {
    GblTestState = FLSTST_TRUE;
  }
  else
  {
    GblTestState = FLSTST_FALSE;
  }
  
   if ((FLSTST_TRUE == GblTestResult) && (FLSTST_TRUE == GblVerCheckStatus) && (FLSTST_TRUE == GblTestState))
  {
      TestPass();
  }
  else
  {
      TestFail();
  }
  
  while(1);
  
} /* End of main() function */

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

FUNC(void, FLSTST_APPL_CODE) TestCompleteNotification(void)
{
  GblTestCompleteStatus = FLSTST_TRUE;
}

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
