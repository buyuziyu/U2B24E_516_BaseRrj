/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_LIN_Common_Sample.c                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2017-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for LIN Driver Component             */
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
 * 2.4.0:  30/06/2025  : Remove the SW-VERSION from header of file
 *                       Add ASM_NOP() to support IAR compiler
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *                       Release
 *                       Add ASM_NOP() to support CCRH compiler
 * 2.3.1:  31/03/2025  : Support core G4KH for U2Bx-E device
 *                       Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 *                       Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL
 *                       Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION
 * 2.1.1:  30/08/2024  : As part of U2BxE support, following changes are made:
 *                       1. Add precondition for U2BxE
 *                     : As part of U2Cx support, following changes are made:
 *                       1. Update check point to support SA for U2Cx device
 * 2.0.1:  29/10/2023  : Update to support for U2Cx device
 *         11/10/2023  : Update AR version "LIN_AR_R21_11_VERSION" to
 *                       "LIN_AR_R22_11_VERSION"
 * 2.0.0:  18/07/2023  : Update to correct for Sample app after update code
 *                       to support multicore
 *         03/07/2023  : Update Sample App to cover Slave mode
 *         25/05/2023  : Change name of AR version LIN_AR_2111_VERSION to 
 *                       LIN_AR_R21_11_VERSION
 * 1.5.0:  05/04/2023  : Add new value LIN_AR_2111_VERSION of 
 *                       macro LIN_AR_VERSION, 
 *                       and macro LIN_MASTER_MODE_SUPPORT to support R21-11
 * 1.4.4:  13/06/2022  : Update SW-VERSION to 1.4.4
 * 1.4.3:  17/05/2022  : Update source of Sample App to cover all API
           14/04/2022  : Update SW-VERSION to 1.4.3
 * 1.3.3:  04/03/2022  : Update SW-VERSION
 * 1.3.2:  22/02/2022  : Update SW-VERSION
 * 1.3.1:  27/04/2021  : Fix coding rule, update record history and copy right
 * 1.2.0:  26/08/2020  : Release
 * 1.1.0:  19/06/2020  : Release
 * 1.0.4:  25/03/2020  : Update Common/Date, Version format
 * 1.0.3:  05/12/2018  : As per JIRA ARDAABO-884, change name of
 *                         Configuration Set Handles.
 * 1.0.2:  08/03/2018  : QAC improvement
 * 1.0.1:  02/10/2017  : [ARDAABO-193] Remove Lin_ChannelConfigType structure
 * 1.0.0:  31/03/2017  : Initial Version
 *
 */
/******************************************************************************/

/*******************************************************************************
**                     Include Section                                        **
*******************************************************************************/
#include "App_LIN_Common_Sample.h"
#include "App_LIN_Device_Sample.h"
#include "Lin_Ram.h"


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* Global variable for Lin Pdu structure used in Lin_SendHeader and
 * Lin_SendResponse APIs */
Lin_PduType GddPduInfo;
/* Global variable to use in Lin_GetStatus API for function return type */
Lin_StatusType GenStatusType;
/* Global variable for 1msec timer counter */
uint8 Guc1msecCount;
/* Global variable for 5msec timer counter */
uint8 Guc5msecCount;
/* Global pointer used in Lin_GetStatus API as output parameter */
#if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
const uint8 ** GpRxDataPtr;
/* Global pointer used by GpRxDataPtr */
const uint8 *GpLinSduPtr;
#else
uint8 ** GpRxDataPtr;
/* Global pointer used by GpRxDataPtr */
uint8 *GpLinSduPtr;
#endif /* #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION) */

/* Global data used as input parameter in Lin_SendResponse API */
uint8 Lin_GaaDataArray0[LIN_DATA_SIZE] = 
                      {(uint8)0x01U, (uint8)0x02U, (uint8)0x03U, (uint8)0x04U, 
                       (uint8)0x05U, (uint8)0x06U, (uint8)0x07U, (uint8)0x08U};
/* Global data used by GpLinSduPtr for a default value */
uint8 Lin_GaaDataArray1[LIN_DATA_SIZE] = 
                      {(uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, 
                       (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU};
#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
uint8 Lin_GaaDataArrayToSlave[LIN_DATA_SIZE] = 
                      {(uint8)0x08U, (uint8)0x08U, (uint8)0x08U, (uint8)0x08U, 
                       (uint8)0x08U, (uint8)0x08U, (uint8)0x08U, (uint8)0x08U};
uint8 Lin_GaaDataArrayFromSlave[LIN_DATA_SIZE] = 
                      {(uint8)0x02U, (uint8)0x02U, (uint8)0x03U, (uint8)0x04U, 
                       (uint8)0x05U, (uint8)0x06U, (uint8)0x07U, (uint8)0x08U};
#endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */

/* Global data used as input parameter in Lin_SendResponse API */
uint8 Lin_GaaDataReceiveArray0[LIN_DATA_SIZE] = 
                      {(uint8)0x03U, (uint8)0x03U, (uint8)0x03U, (uint8)0x03U, 
                       (uint8)0x03U, (uint8)0x03U, (uint8)0x03U, (uint8)0x03U};

/* Global variable to store RLIN3 status */
uint8 GucRLN30LST = 0;
uint8 GucRLN30LEST = 0;
/* Variable used to store the result of version information check*/
uint8 GucVerCheckStatus;

uint32 LulTimeOut = 0;
/* Default core support for SA */
uint8 LucPEId = 0;

/*Local variable to store status of Lin_SendFrame*/
uint8 LucStatus;

#if (LIN_MASTER_MODE_SUPPORT == STD_ON)
/* Local variable to store status of Lin_GetStatus */
Lin_StatusType LucGetStatus;
#endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */

/* Time excuetion for Lin_GotoSleep and Lin_Wakeup (Slave Channel) */
#define TEST_LIN_WAIT                                                 (20000000)

/* Local variable to store the test result */
uint8 GaaTestResult[50];

/* Variable to store result of checked point */
uint8 GucTestResultCount;

volatile uint8 GucStubInitFlag = 0;
/******************************************************************************
* F U N C T I O N    D E F I N I T I O N S
******************************************************************************/
void sample_end(void)
{
  while (1)
  {
    ASM_NOP();/* No action required*/
  }
}

int main(void)
#if defined(RUN_OTHER_PE)
{
  Guard_Enable_PE();
  /* System Initialisation
   * Clock Initialisation, Programmable Peripheral I/O register, selecting
   * the clock for the LIN Module */
  /* Clock Initialisation */
  Clock_Init();

  /* Initialize the watchdog */
  Wdg_Init();

  /* System Initialisation */
  Mcu_Init();

  /* LIN Port Pin Configuration */
  Port_Init();

  /* Set flag to indicate core 1 stub modules have been initialized */
  GucStubInitFlag = 1;

  while(1);
}
#if defined(RUN_PE1)
void main_PE1(void)
#elif defined(RUN_PE2)
void main_PE2(void)
#elif defined(RUN_PE3)
void main_PE3(void)
#elif defined(RUN_PE4)
void main_PE4(void)
#elif defined(RUN_PE5)
void main_PE5(void)
#elif defined(RUN_PE6)
void main_PE6(void)
#endif
#endif
{

  #if (LIN_MASTER_MODE_SUPPORT == STD_ON)
  /* Local pointer variables to store transmitted and recieved data*/
  const uint8 *LppLin_TxSduPtr[1];
  const uint8 *LppLin_RxSduPtr[1];
  #endif /* (LIN_MASTER_MODE_SUPPORT == STD_ON) */

  #ifndef RUN_OTHER_PE
  /* System Initialisation
   * Clock Initialisation, Programmable Peripheral I/O register, selecting
   * the clock for the LIN Module */

  #if (DEVICE == U2Ax || DEVICE == U2Bx || DEVICE == U2Cx || DEVICE == U2BxE)
  /* Clock Initialisation */
  Clock_Init();

  /* Initialize the watchdog */
  Wdg_Init();
  
  /* System Initialisation */
  #endif //#if (DEVICE == U2Ax || DEVICE == U2Bx || DEVICE == U2Cx || DEVICE == U2BxE)

  Mcu_Init();

  /* LIN Port Pin Configuration */
  Port_Init();
  #endif

  #if defined(RUN_OTHER_PE)
  /* Waiting for core 0 to complete init */
  while (GucStubInitFlag == 0);

  BoundIntToPEMax();
  #endif

  /* Timer Initialization */
  App_Lin_Start_Timer0();

  /* LIN Global as well as Channel initialisation */
  Appl_Lin_Init();

  #if(LIN_VERSION_INFO_API == STD_ON)
  Std_VersionInfoType versionInfo;

  /* Invoke the API Lin_GetVersionInfo() to get the version information of LIN Driver */
  Lin_GetVersionInfo(&versionInfo);

  /* Check for the correctness of version information */
  if((LIN_VENDOR_ID == versionInfo.vendorID) &&
     (LIN_MODULE_ID == versionInfo.moduleID) &&
     (LIN_SW_MAJOR_VERSION == versionInfo.sw_major_version) &&
     (LIN_SW_MINOR_VERSION == versionInfo.sw_minor_version) &&
     (LIN_SW_PATCH_VERSION == versionInfo.sw_patch_version))
  {
    GucVerCheckStatus = TRUE;
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    /* If the version information is incorrect */ 
    GucVerCheckStatus = FALSE;
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }
  #endif /* (LIN_VERSION_INFO_API == STD_ON) */


  /* Enable the global interrupts */
  ENABLE_INTERRUPT();

  /* Set the LIN PDU parameters for transmitting the LIN Frame */
  GddPduInfo.Pid = (uint8)LIN_SEND_PID;
  GddPduInfo.Cs = LIN_CLASSIC_CS;
  #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
  GddPduInfo.Drc = LIN_FRAMERESPONSE_TX;
  #else
  GddPduInfo.Drc = LIN_MASTER_RESPONSE;
  #endif
  GddPduInfo.Dl = LIN_DATA_SIZE;
  GddPduInfo.SduPtr = Lin_GaaDataArray0;

  #if (DEVICE == U2Ax || DEVICE == U2Bx || DEVICE == U2Cx || DEVICE == U2BxE)
  /* Disable the global interrupts */
  DISABLE_INTERRUPT();
  #endif /* #if (DEVICE == U2Ax || DEVICE == U2Bx || DEVICE == U2Cx || DEVICE == U2BxE) */
  /* Functionality related to R4.2 */
  /* Following API is invoked to transmit the header and response part of a LIN
   * as Frame on the addressed LIN Channel
   */
  #if (LIN_MASTER_MODE_SUPPORT == STD_ON)
  Lin_WakeupInternal(LIN_CHANNEL_MASTER);

  LucStatus = Lin_SendFrame(LIN_CHANNEL_MASTER, &GddPduInfo);

  /* Checkpoint 10: Check for the correctness of Lin_SendFrame: Transmit */
  if (E_OK == LucStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }
  #endif /* (LIN_MASTER_MODE_SUPPORT ==STD_ON) */

  #if (DEVICE == U2Ax || DEVICE == U2Bx || DEVICE == U2Cx || DEVICE == U2BxE)
  /* Read Status Registers */
  while (0 == GucRLN30LST )
  {
    GucRLN30LST = LIN_RLN30LST;
    if (0 == GucRLN30LEST)
    {
      GucRLN30LEST = LIN_RLN30LEST;
    }
  }
  /* Initialize 5msec Counter */
  Guc5msecCount = LIN_COUNT_INITIAL_VALUE;
  /* Enable the global interrupts */
  ENABLE_INTERRUPT();
  #endif /* #if (DEVICE == U2Ax || DEVICE == U2Bx || DEVICE == U2Cx || DEVICE == U2BxE) */

  /* Wait for the maximum transfer delay for the frame to be transmitted */
  while (Guc5msecCount < LIN_MAX_TIMEOUT_COUNT)
  {
    ASM_NOP();/* No operation. Counter is incremented in timer interrupt handler. */
  }
  
  Guc5msecCount = LIN_COUNT_INITIAL_VALUE;
  /* Wait for the maximum transfer delay for the frame to be transmitted */
  while (Guc5msecCount < LIN_MAX_TIMEOUT_COUNT)
  {
    ASM_NOP();/* No operation. Counter is incremented in timer interrupt handler. */
  }
  /* Checkpoint 11: Check status of Lin_SendFrame in case transmition */
  LppLin_TxSduPtr[0] = Lin_GaaDataArray0;

  /* Invkoe Lin_GetStatus */
  LucGetStatus = Lin_GetStatus(LIN_CHANNEL_MASTER, LppLin_TxSduPtr);

  if (LIN_TX_OK == LucGetStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }

  /* Initialize 5msec Counter */
  Guc5msecCount = LIN_COUNT_INITIAL_VALUE;

  #if (DEVICE == U2Ax || DEVICE == U2Bx || DEVICE == U2Cx || DEVICE == U2BxE)
  #if 0
  /* Wait until LST.HTRC is set for LIN Header Tx completed successfully */
  while ((RLIN30_LST & 0x80U) != 0x80U );
  #endif
  #endif /* #if (DEVICE == U2Ax || DEVICE == U2Bx || DEVICE == U2Cx || DEVICE == U2BxE) */

  /* Set the LIN PDU parameters for receive the the LIN response */
  GddPduInfo.Pid = (uint8)LIN_RESP_PID;
  GddPduInfo.Cs = LIN_CLASSIC_CS;
  #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
  GddPduInfo.Drc = LIN_FRAMERESPONSE_RX;
  #else
  GddPduInfo.Drc = LIN_SLAVE_RESPONSE;
  #endif
  GddPduInfo.Dl = LIN_DATA_SIZE ;
  GddPduInfo.SduPtr = Lin_GaaDataArray1;

  /* Functionality related to R4.2 */
  /* Following API is invoked to transmit the header and receive the response
   * as part of a LIN Frame on the addressed LIN Channel
   */
  #if (LIN_MASTER_MODE_SUPPORT == STD_ON)
  LucStatus = Lin_SendFrame(LIN_CHANNEL_MASTER, &GddPduInfo);

  /* Checkpoint: Check for the correctness of Lin_SendFrame: Reception */
  if (E_OK == LucStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }
  #endif /* (LIN_MASTER_MODE_SUPPORT == STD_ON) */

  /* Wait for the maximum transfer delay for the frame to be transmitted */
  while (Guc5msecCount < LIN_MAX_TIMEOUT_COUNT)
  {
    ASM_NOP();/* No operation. Counter is incremented in timer interrupt handler. */
  }

  /* Checkpoint: Check status of Lin_SendFrame in case reception*/
  LppLin_RxSduPtr[0] = Lin_GaaDataArray1;

  LucGetStatus = Lin_GetStatus(LIN_CHANNEL_MASTER, LppLin_RxSduPtr);

  if (LIN_RX_OK == LucGetStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }

  /* Checkpoint: Verify the received data should be same with the sent data */
  for(uint8 i = 0 ; i < LIN_DATA_SIZE; i++)
  {
    if(LppLin_RxSduPtr[0][i] == Lin_GaaDataReceiveArray0[i])
    {
      GaaTestResult[GucTestResultCount] = TRUE;
      GucTestResultCount++;
    }
    else
    {
      GaaTestResult[GucTestResultCount] = FALSE;
      GucTestResultCount++;
    }
  }
  /* Initialize 5msec Counter */
  Guc5msecCount = LIN_COUNT_INITIAL_VALUE;

  #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)

  /* PDU: Master send data to Slave */
  GddPduInfo.Pid = (uint8)LIN_SEND_PID;
  GddPduInfo.Cs = LIN_CLASSIC_CS;
  GddPduInfo.Drc = LIN_FRAMERESPONSE_TX;
  GddPduInfo.Dl = LIN_DATA_SIZE ;
  GddPduInfo.SduPtr = Lin_GaaDataArrayToSlave;

  /* Define LIN channel ID and Response Type for stub LinIf : SLAVE CHANNEL */
  /* Slave channel receive Header + Response Reception */
  LIN_CHANNEL_ID[LucPEId] = LIN_CHANNEL_SLAVE;
  Linif_GstSlavePdu[LucPEId].Pid = (uint8)LIN_SEND_PID;
  Linif_GstSlavePdu[LucPEId].Cs = LIN_CLASSIC_CS;
  Linif_GstSlavePdu[LucPEId].Drc = LIN_FRAMERESPONSE_RX;
  Linif_GstSlavePdu[LucPEId].Dl = LIN_DATA_SIZE;
  Linif_GstSlavePdu[LucPEId].SduPtr = Lin_GaaDataArrayToSlave;

  /* Invoke Lin_WakeupInternal for Master Channel */
  Lin_WakeupInternal(LIN_CHANNEL_MASTER);

  /* Invoke Lin_WakeupInternal for Slave channel */
  Lin_WakeupInternal(LIN_CHANNEL_SLAVE);

  #if (LIN_MASTER_MODE_SUPPORT == STD_ON)
  Lin_SendFrame(LIN_CHANNEL_MASTER, &GddPduInfo);

  /* Wait for transfer delay for the frame to be transmitted */
  while (0 == GblLinIfRxReceivedFlag[LucPEId])
  {
    ASM_NOP();// No action required until Slave channel receive Header and Response Reception
  }

  /* PDU: Master request data from Slave */
  GddPduInfo.Pid = (uint8)LIN_SEND_PID;
  GddPduInfo.Cs = LIN_CLASSIC_CS;
  GddPduInfo.Drc = LIN_FRAMERESPONSE_RX;
  GddPduInfo.Dl = LIN_DATA_SIZE ;
  GddPduInfo.SduPtr = Lin_GaaDataArrayFromSlave;

  /* Define LIN channel ID and Response Type for stub LinIf: SLAVE CHANNEL */
  /* Slave channel receive Header + Response Transmision */
  LIN_CHANNEL_ID[LucPEId] = LIN_CHANNEL_SLAVE;
  Linif_GstSlavePdu[LucPEId].Pid = (uint8)LIN_SEND_PID;
  Linif_GstSlavePdu[LucPEId].Cs = LIN_CLASSIC_CS;
  Linif_GstSlavePdu[LucPEId].Drc = LIN_FRAMERESPONSE_TX;
  Linif_GstSlavePdu[LucPEId].Dl = LIN_DATA_SIZE;
  Linif_GstSlavePdu[LucPEId].SduPtr = Lin_GaaDataArrayFromSlave;

  Lin_SendFrame(LIN_CHANNEL_MASTER, &GddPduInfo);

  /* Wait for transfer delay for the frame to be transmitted */
  while (!((GpRxDataPtr[0][0] == Lin_GaaDataArrayFromSlave[0]) &&
  (GpRxDataPtr[0][1] == Lin_GaaDataArrayFromSlave[1]) &&
  (GpRxDataPtr[0][2] == Lin_GaaDataArrayFromSlave[2]) &&
  (GpRxDataPtr[0][3] == Lin_GaaDataArrayFromSlave[3]) &&
  (GpRxDataPtr[0][4] == Lin_GaaDataArrayFromSlave[4]) &&
  (GpRxDataPtr[0][5] == Lin_GaaDataArrayFromSlave[5]) &&
  (GpRxDataPtr[0][6] == Lin_GaaDataArrayFromSlave[6]) &&
  (GpRxDataPtr[0][7] == Lin_GaaDataArrayFromSlave[7])))
  {
    ASM_NOP();
  }
  
  #endif /* (LIN_MASTER_MODE_SUPPORT == STD_ON) */
  #endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */

  /* End trap */
  sample_end();
}
/*****************************************************************************
                        LIN Module Initialization
*****************************************************************************/
void Appl_Lin_Init(void)
{
  /* Initialise Global variable for 1msec timer counter to 0 */
  Guc1msecCount = LIN_COUNT_INITIAL_VALUE;
  /* Initialise Global variable for 5msec timer counter to 0 */
  Guc5msecCount = LIN_COUNT_INITIAL_VALUE;
  /* Initialise GpLinSduPtr to application buffer */
  GpLinSduPtr = &Lin_GaaDataArray1[0];
  /* Initialise GpRxDataPtr to GpLinSduPtr */
  GpRxDataPtr = &GpLinSduPtr;

  #if (NON_RLININTCNTLREG == STD_ON)
  #if (DEVICE == E2x)
  /* Enable the RLIN Tx/Rx/Status interrupt by using IC register */
  RLININT_UR0CNTLREG = LIN_ENABLE_INTERRUPT;
  RLININT_UR1CNTLREG = LIN_ENABLE_INTERRUPT;
  RLININT_UR2CNTLREG = LIN_ENABLE_INTERRUPT;
  #elif (DEVICE == U2Ax)
  /* Enable the RLIN Tx/Rx/Status interrupt by using IC register */
  /* RLIN30 */
  EIC417 = LIN_ENABLE_INTERRUPT;
  EIC418 = LIN_ENABLE_INTERRUPT;
  EIC419 = LIN_ENABLE_INTERRUPT;
  /* RLIN31 */
  EIC421 = LIN_ENABLE_INTERRUPT;
  EIC422 = LIN_ENABLE_INTERRUPT;
  EIC423 = LIN_ENABLE_INTERRUPT;
  /* RLIN32 */
  EIC425 = LIN_ENABLE_INTERRUPT;
  EIC426 = LIN_ENABLE_INTERRUPT;
  EIC427 = LIN_ENABLE_INTERRUPT;
  /* RLIN33 */
  EIC429 = LIN_ENABLE_INTERRUPT;
  EIC430 = LIN_ENABLE_INTERRUPT;
  EIC431 = LIN_ENABLE_INTERRUPT;
  /* RLIN34 */
  EIC433 = LIN_ENABLE_INTERRUPT;
  EIC434 = LIN_ENABLE_INTERRUPT;
  EIC435 = LIN_ENABLE_INTERRUPT;
  /* RLIN35 */
  EIC437 = LIN_ENABLE_INTERRUPT;
  EIC438 = LIN_ENABLE_INTERRUPT;
  EIC439 = LIN_ENABLE_INTERRUPT;
  /* RLIN36 */
  EIC441 = LIN_ENABLE_INTERRUPT;
  EIC442 = LIN_ENABLE_INTERRUPT;
  EIC443 = LIN_ENABLE_INTERRUPT;
  /* RLIN37 */
  EIC445 = LIN_ENABLE_INTERRUPT;
  EIC446 = LIN_ENABLE_INTERRUPT;
  EIC447 = LIN_ENABLE_INTERRUPT;
  /* RLIN38 */
  EIC449 = LIN_ENABLE_INTERRUPT;
  EIC450 = LIN_ENABLE_INTERRUPT;
  EIC451 = LIN_ENABLE_INTERRUPT;
  /* RLIN39 */
  EIC453 = LIN_ENABLE_INTERRUPT;
  EIC454 = LIN_ENABLE_INTERRUPT;
  EIC455 = LIN_ENABLE_INTERRUPT;
  /* RLIN310 */
  EIC457 = LIN_ENABLE_INTERRUPT;
  EIC458 = LIN_ENABLE_INTERRUPT;
  EIC459 = LIN_ENABLE_INTERRUPT;
  /* RLIN311 */
  EIC461 = LIN_ENABLE_INTERRUPT;
  EIC462 = LIN_ENABLE_INTERRUPT;
  EIC463 = LIN_ENABLE_INTERRUPT;
  /* RLIN312 */
  EIC465 = LIN_ENABLE_INTERRUPT;
  EIC466 = LIN_ENABLE_INTERRUPT;
  EIC467 = LIN_ENABLE_INTERRUPT;
  /* RLIN313 */
  EIC469 = LIN_ENABLE_INTERRUPT;
  EIC470 = LIN_ENABLE_INTERRUPT;
  EIC471 = LIN_ENABLE_INTERRUPT;
  /* RLIN314 */
  EIC473 = LIN_ENABLE_INTERRUPT;
  EIC474 = LIN_ENABLE_INTERRUPT;
  EIC475 = LIN_ENABLE_INTERRUPT;
  /* RLIN315 */
  EIC477 = LIN_ENABLE_INTERRUPT;
  EIC478 = LIN_ENABLE_INTERRUPT;
  EIC479 = LIN_ENABLE_INTERRUPT;
  /* RLIN316 */
  EIC481 = LIN_ENABLE_INTERRUPT;
  EIC482 = LIN_ENABLE_INTERRUPT;
  EIC483 = LIN_ENABLE_INTERRUPT;
  /* RLIN317 */
  EIC485 = LIN_ENABLE_INTERRUPT;
  EIC486 = LIN_ENABLE_INTERRUPT;
  EIC487 = LIN_ENABLE_INTERRUPT;
  /* RLIN318 */
  EIC489 = LIN_ENABLE_INTERRUPT;
  EIC490 = LIN_ENABLE_INTERRUPT;
  EIC491 = LIN_ENABLE_INTERRUPT;
  /* RLIN319 */
  EIC493 = LIN_ENABLE_INTERRUPT;
  EIC494 = LIN_ENABLE_INTERRUPT;
  EIC495 = LIN_ENABLE_INTERRUPT;
  /* RLIN320 */
  EIC497 = LIN_ENABLE_INTERRUPT;
  EIC498 = LIN_ENABLE_INTERRUPT;
  EIC499 = LIN_ENABLE_INTERRUPT;
  /* RLIN321 */
  EIC501 = LIN_ENABLE_INTERRUPT;
  EIC502 = LIN_ENABLE_INTERRUPT;
  EIC503 = LIN_ENABLE_INTERRUPT;
  /* RLIN322 */
  EIC505 = LIN_ENABLE_INTERRUPT;
  EIC506 = LIN_ENABLE_INTERRUPT;
  EIC507 = LIN_ENABLE_INTERRUPT;
  /* RLIN323 */
  EIC509 = LIN_ENABLE_INTERRUPT;
  EIC510 = LIN_ENABLE_INTERRUPT;
  EIC511 = LIN_ENABLE_INTERRUPT;
  #elif (DEVICE == U2Bx || DEVICE == U2BxE)
  /* Enable the RLIN Tx/Rx/Status interrupt by using IC register */
  /* RLIN30 */
  EIC621 = LIN_ENABLE_INTERRUPT;
  EIC622 = LIN_ENABLE_INTERRUPT;
  EIC623 = LIN_ENABLE_INTERRUPT;
  /* RLIN31 */
  EIC626 = LIN_ENABLE_INTERRUPT;
  EIC627 = LIN_ENABLE_INTERRUPT;
  EIC628 = LIN_ENABLE_INTERRUPT;
  /* RLIN32 */
  EIC631 = LIN_ENABLE_INTERRUPT;
  EIC632 = LIN_ENABLE_INTERRUPT;
  EIC633 = LIN_ENABLE_INTERRUPT;
  /* RLIN33 */
  EIC636 = LIN_ENABLE_INTERRUPT;
  EIC637 = LIN_ENABLE_INTERRUPT;
  EIC638 = LIN_ENABLE_INTERRUPT;
  /* RLIN34 */
  EIC641 = LIN_ENABLE_INTERRUPT;
  EIC642 = LIN_ENABLE_INTERRUPT;
  EIC643 = LIN_ENABLE_INTERRUPT;
  /* RLIN35 */
  EIC645 = LIN_ENABLE_INTERRUPT;
  EIC646 = LIN_ENABLE_INTERRUPT;
  EIC647 = LIN_ENABLE_INTERRUPT;
  /* RLIN36 */
  EIC993 = LIN_ENABLE_INTERRUPT;
  EIC994 = LIN_ENABLE_INTERRUPT;
  EIC995 = LIN_ENABLE_INTERRUPT;
  /* RLIN37 */
  EIC997 = LIN_ENABLE_INTERRUPT;
  EIC998 = LIN_ENABLE_INTERRUPT;
  EIC999 = LIN_ENABLE_INTERRUPT;
  /* RLIN38 */
  EIC321 = LIN_ENABLE_INTERRUPT;
  EIC322 = LIN_ENABLE_INTERRUPT;
  EIC323 = LIN_ENABLE_INTERRUPT;
  /* RLIN39 */
  EIC329 = LIN_ENABLE_INTERRUPT;
  EIC330 = LIN_ENABLE_INTERRUPT;
  EIC331 = LIN_ENABLE_INTERRUPT;
  /* RLIN310 */
  EIC333 = LIN_ENABLE_INTERRUPT;
  EIC334 = LIN_ENABLE_INTERRUPT;
  EIC335 = LIN_ENABLE_INTERRUPT;
  /* RLIN311 */
  EIC345 = LIN_ENABLE_INTERRUPT;
  EIC346 = LIN_ENABLE_INTERRUPT;
  EIC347 = LIN_ENABLE_INTERRUPT; 
  /* RLIN312 */
  EIC349 = LIN_ENABLE_INTERRUPT;
  EIC350 = LIN_ENABLE_INTERRUPT;
  EIC351 = LIN_ENABLE_INTERRUPT; 
  /* RLIN313 */
  EIC388 = LIN_ENABLE_INTERRUPT;
  EIC389 = LIN_ENABLE_INTERRUPT;
  EIC390 = LIN_ENABLE_INTERRUPT;
  /* RLIN314 */
  EIC392 = LIN_ENABLE_INTERRUPT;
  EIC393 = LIN_ENABLE_INTERRUPT;
  EIC394 = LIN_ENABLE_INTERRUPT;
  /* RLIN315 */
  EIC522 = LIN_ENABLE_INTERRUPT;
  EIC523 = LIN_ENABLE_INTERRUPT;
  EIC524 = LIN_ENABLE_INTERRUPT;
  /* RLIN316 */
  EIC526 = LIN_ENABLE_INTERRUPT;
  EIC527 = LIN_ENABLE_INTERRUPT;
  EIC528 = LIN_ENABLE_INTERRUPT;
  /* RLIN317 */
  EIC530 = LIN_ENABLE_INTERRUPT;
  EIC531 = LIN_ENABLE_INTERRUPT;
  EIC532 = LIN_ENABLE_INTERRUPT;
  /* RLIN318 */
  EIC546 = LIN_ENABLE_INTERRUPT;
  EIC547 = LIN_ENABLE_INTERRUPT;
  EIC548 = LIN_ENABLE_INTERRUPT;
  /* RLIN319 */
  EIC550 = LIN_ENABLE_INTERRUPT;
  EIC551 = LIN_ENABLE_INTERRUPT;
  EIC552 = LIN_ENABLE_INTERRUPT;
  /* RLIN320 */
  EIC554 = LIN_ENABLE_INTERRUPT;
  EIC555 = LIN_ENABLE_INTERRUPT;
  EIC556 = LIN_ENABLE_INTERRUPT;
  /* RLIN321 */
  EIC558 = LIN_ENABLE_INTERRUPT;
  EIC559 = LIN_ENABLE_INTERRUPT;
  EIC560 = LIN_ENABLE_INTERRUPT;
  /* RLIN322 */
  EIC565 = LIN_ENABLE_INTERRUPT;
  EIC566 = LIN_ENABLE_INTERRUPT;
  EIC567 = LIN_ENABLE_INTERRUPT;
  /* RLIN323 */
  EIC649 = LIN_ENABLE_INTERRUPT;
  EIC650 = LIN_ENABLE_INTERRUPT;
  EIC651 = LIN_ENABLE_INTERRUPT;
  #elif (DEVICE == U2Cx)
  /* Enable the RLIN Tx/Rx/Status interrupt by using IC register */
  /* RLIN30 */
  EIC174 = LIN_ENABLE_INTERRUPT;
  EIC175 = LIN_ENABLE_INTERRUPT;
  EIC176 = LIN_ENABLE_INTERRUPT;
  /* RLIN31 */
  EIC179 = LIN_ENABLE_INTERRUPT;
  EIC180 = LIN_ENABLE_INTERRUPT;
  EIC181 = LIN_ENABLE_INTERRUPT;
  /* RLIN32 */
  EIC184 = LIN_ENABLE_INTERRUPT;
  EIC185 = LIN_ENABLE_INTERRUPT;
  EIC186 = LIN_ENABLE_INTERRUPT;
  /* RLIN33 */
  EIC189 = LIN_ENABLE_INTERRUPT;
  EIC190 = LIN_ENABLE_INTERRUPT;
  EIC191 = LIN_ENABLE_INTERRUPT;
  /* RLIN34 */
  EIC194 = LIN_ENABLE_INTERRUPT;
  EIC195 = LIN_ENABLE_INTERRUPT;
  EIC196 = LIN_ENABLE_INTERRUPT;
  /* RLIN35 */
  EIC198 = LIN_ENABLE_INTERRUPT;
  EIC199 = LIN_ENABLE_INTERRUPT;
  EIC200 = LIN_ENABLE_INTERRUPT;
  /* RLIN36 */
  EIC202 = LIN_ENABLE_INTERRUPT;
  EIC203 = LIN_ENABLE_INTERRUPT;
  EIC204 = LIN_ENABLE_INTERRUPT;
  /* RLIN37 */
  EIC395 = LIN_ENABLE_INTERRUPT;
  EIC396 = LIN_ENABLE_INTERRUPT;
  EIC397 = LIN_ENABLE_INTERRUPT;
  /* RLIN38 */
  EIC399 = LIN_ENABLE_INTERRUPT;
  EIC400 = LIN_ENABLE_INTERRUPT;
  EIC401 = LIN_ENABLE_INTERRUPT;
  /* RLIN39 */
  EIC403 = LIN_ENABLE_INTERRUPT;
  EIC404 = LIN_ENABLE_INTERRUPT;
  EIC405 = LIN_ENABLE_INTERRUPT;
  /* RLIN310 */
  EIC407 = LIN_ENABLE_INTERRUPT;
  EIC408 = LIN_ENABLE_INTERRUPT;
  EIC409 = LIN_ENABLE_INTERRUPT;
  /* RLIN311 */
  EIC494 = LIN_ENABLE_INTERRUPT;
  EIC495 = LIN_ENABLE_INTERRUPT;
  EIC496 = LIN_ENABLE_INTERRUPT; 
  /* RLIN312 */
  EIC498 = LIN_ENABLE_INTERRUPT;
  EIC499 = LIN_ENABLE_INTERRUPT;
  EIC500 = LIN_ENABLE_INTERRUPT; 
  /* RLIN313 */
  EIC502 = LIN_ENABLE_INTERRUPT;
  EIC503 = LIN_ENABLE_INTERRUPT;
  EIC504 = LIN_ENABLE_INTERRUPT;
  /* RLIN314 */
  EIC506 = LIN_ENABLE_INTERRUPT;
  EIC507 = LIN_ENABLE_INTERRUPT;
  EIC508 = LIN_ENABLE_INTERRUPT;
  /* RLIN315 */
  EIC569 = LIN_ENABLE_INTERRUPT;
  EIC570 = LIN_ENABLE_INTERRUPT;
  EIC571 = LIN_ENABLE_INTERRUPT;
  /* RLIN316 */
  EIC573 = LIN_ENABLE_INTERRUPT;
  EIC574 = LIN_ENABLE_INTERRUPT;
  EIC575 = LIN_ENABLE_INTERRUPT;
  /* RLIN317 */
  EIC577 = LIN_ENABLE_INTERRUPT;
  EIC578 = LIN_ENABLE_INTERRUPT;
  EIC579 = LIN_ENABLE_INTERRUPT;
  /* RLIN318 */
  EIC581 = LIN_ENABLE_INTERRUPT;
  EIC582 = LIN_ENABLE_INTERRUPT;
  EIC583 = LIN_ENABLE_INTERRUPT;
  /* RLIN323 */
  EIC206 = LIN_ENABLE_INTERRUPT;
  EIC207 = LIN_ENABLE_INTERRUPT;
  EIC208 = LIN_ENABLE_INTERRUPT;
  #endif //#if (DEVICE == E2x)
  #else
  /* Enable the RLIN interrupt by using IC register */
  RLININTCNTLREG = LIN_ENABLE_INTERRUPT;
  #endif /* #if (NON_RLININTCNTLREG == STD_ON) */
  /* Global Initialisation */
  Lin_Init(Lin_Config);

  #if ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION))
  LucStatus = Lin_WakeupInternal(LIN_CHANNEL_MASTER);

  /* Checkpoint 1: Lin_WakeupInternal */
  if (E_OK == LucStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }
  #endif /* #if ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)) */

  #if (LIN_MASTER_MODE_SUPPORT == STD_ON)
  LucStatus = Lin_GoToSleep(LIN_CHANNEL_MASTER);

  /* Checkpoint 2: Lin_GoToSleep */
  if (E_OK == LucStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }
  #endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */


  LulTimeOut = 0;
  while (LulTimeOut < TEST_LIN_WAIT)
  {
    LulTimeOut++;
  }

  LulTimeOut = TEST_LIN_WAIT;
  /* Checkpoint 3: Confirm satus of Lin_GotoSleep */
  while (((GenStatusType = Lin_GetStatus(LIN_CHANNEL_MASTER, GpRxDataPtr)) != LIN_CH_SLEEP) && (LulTimeOut > 0))
  {
    LulTimeOut--;
  }

  if (LulTimeOut > 0)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }

  LucStatus = Lin_Wakeup(LIN_CHANNEL_MASTER);

  /* Checkpoint 4: Lin_Wakeup */
  if (E_OK == LucStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }

  LulTimeOut = TEST_LIN_WAIT;

  /* Checkpoint 5: Confirm satus of Lin_Wakeup */
  while (((GenStatusType = Lin_GetStatus(LIN_CHANNEL_MASTER, GpRxDataPtr)) != LIN_OPERATIONAL) && (LulTimeOut > 0))
  {
    LulTimeOut--;
  }

  if (LulTimeOut > 0)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }

  LucStatus = Lin_CheckWakeup(LIN_CHANNEL_MASTER);

  /* Checkpoint 6: Lin_Wakeup */
  if (E_OK == LucStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }

  LucStatus = Lin_GoToSleepInternal(LIN_CHANNEL_MASTER);

  /* Checkpoint 7: Lin_GoToSleepInternal */
  if (E_OK == LucStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }

  #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)

  /* Checkpoint 8: Confirm Lin_WakeupInternal for LIN SLAVE CHANNEL */
  LucStatus = Lin_WakeupInternal(LIN_CHANNEL_SLAVE);

  if (E_OK == LucStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }

  /* Checkpoint 9: Confirm Lin_GoToSleepInternal for LIN SLAVE CHANNEL */
  LucStatus = Lin_GoToSleepInternal(LIN_CHANNEL_SLAVE);
  
  if (E_OK == LucStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }  

  /* Checkpoint 10: Confirm Lin_Wakeup for LIN SLAVE CHANNEL */
  LucStatus = Lin_Wakeup(LIN_CHANNEL_SLAVE);

  if (E_OK == LucStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }

  LulTimeOut = 0;
  while (LulTimeOut < TEST_LIN_WAIT)
  {
    LulTimeOut++;
  }

  /* Checkpoint 11: Confirm Lin_CheckWakeup for LIN SLAVE CHANNEL */
  LucStatus = Lin_CheckWakeup(LIN_CHANNEL_SLAVE);
  
  if (E_OK == LucStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }  

  /* Checkpoint 12: Confirm Lin_GoToSleepInternal for LIN SLAVE CHANNEL */
  LucStatus = Lin_GoToSleepInternal(LIN_CHANNEL_SLAVE);

  if (E_OK == LucStatus)
  {
    GaaTestResult[GucTestResultCount] = TRUE;
    GucTestResultCount++;
  }
  else
  {
    GaaTestResult[GucTestResultCount] = FALSE;
    GucTestResultCount++;
  }  

  #endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
}

void Appl_Scheduler_Task(void)
{

  /* Following API is invoked to get the status of the LIN Driver */
  #if (LIN_MASTER_MODE_SUPPORT == STD_ON)
  GenStatusType = Lin_GetStatus(LIN_CHANNEL_MASTER, GpRxDataPtr);
  #endif /* #if (LIN_MASTER_MODE_SUPPORT == STD_ON) */

  /* Increment 5msec count */
  Guc5msecCount++;
}

/*******************************************************************************
                              Timer Interrupt routine
*******************************************************************************/
/* 1 msec timer interrupt */
_INTERRUPT_ void Timer0_Interrupt(void)
{
  /* Increment Guc1msecCount by 1 */
  Guc1msecCount++;
  /* Wait for the maximum transfer delay for the frame to be transmitted */
  if (LIN_WAIT_5MS == Guc1msecCount)
  {
    /* Invoke Task */
    Appl_Scheduler_Task();

    /* Re-initialise Guc1msecCount to 0 */
    Guc1msecCount = LIN_COUNT_INITIAL_VALUE;
  }
  else
  {
    /* No action required */
  }
}
/****************************************************************************
                          End of the file
****************************************************************************/
