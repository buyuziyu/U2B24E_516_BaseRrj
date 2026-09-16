/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = LinIf.c                                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023 - 2025 Renesas Electronics Corporation. All rights reserved.      */
/*============================================================================*/
/* Purpose:                                                                   */
/* This application file contains execution sequences to demonstrate the usage*/
/* of LIN Driver APIs.                                                        */
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
/* to lost profits) regardless of whLINer such liability is based on breach   */
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
**                      Revision History                                      **
*******************************************************************************/
/*
 * 2.4.0      30/06/2025     Remove the SW-VERSION from header of file
 * 2.3.2      25/04/2025     Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *                           Release
 * 2.3.1      31/03/2025     Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 *                           Release
 * 2.3.0      28/02/2025     Update SW-VERSION for RH850/U2Cx MCAL
 *                           Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0      31/12/2024     Update SW-VERSION for Ver22.02.00(D) U2Bx Final
 *                           Release
 * 2.1.2      31/10/2024     Remove 'static' for GucWakeupCount
 * 2.1.1      22/05/2024     Update macro LINIF_SW_MAJOR_VERSION to
 *                           LINIF_C_SW_MAJOR_VERSION and
 *                           LINIF_SW_MINOR_VERSION to LINIF_C_SW_MINOR_VERSION
 * 2.1.0      06/03/2024     Update SW-VERSION to 2.1.0
 * 2.0.1      11/10/2023     Update AR version LIN_AR_R21_11_VERSION to
 *                           LIN_AR_R22_11_VERSION
 *            22/09/2023     Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Lin.h"
#include "LinIf.h"
#include "Lin_Ram.h"
#include "Os.h"
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* AUTOSAR release version information */
#define LINIF_C_AR_RELEASE_MAJOR_VERSION   LIN_59_AR_RELEASE_MAJOR_VERSION_VALUE
#define LINIF_C_AR_RELEASE_MINOR_VERSION   LIN_59_AR_RELEASE_MINOR_VERSION_VALUE
#define LINIF_C_AR_RELEASE_REVISION_VERSION \
                                        LIN_59_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define LINIF_C_SW_MAJOR_VERSION    LIN_59_SW_MAJOR_VERSION
#define LINIF_C_SW_MINOR_VERSION    LIN_59_SW_MINOR_VERSION

/*******************************************************************************
**                         Global Data                                        **
*******************************************************************************/

uint8 GucWakeupCount[NUM_CPU] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL};

EcuM_WakeupSourceType Gul_Check_LinIf_WakeupConfirmation[NUM_CPU];

uint8 GblLinIfHeaderReceivedFlag[NUM_CPU] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL};
uint8 GblLinIfRxReceivedFlag[NUM_CPU] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL};
uint8 GblLinIfTxTransmitFlag[NUM_CPU] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL};

uint8 GblLinIfErrorHeaderErrorFlag[NUM_CPU] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL};
uint8 GblLinIfErrorFramingResponseErrorFlag[NUM_CPU] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL};
uint8 GblLinIfErrorChecksumErrorFlag[NUM_CPU] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL};
uint8 GblLinIfErrorDataBitResponseErrorFlag[NUM_CPU] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL};
uint8 GblLinIfErrorNoResponseFlag[NUM_CPU] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL};
uint8 GblLinIfErrorIncompleteResponseFlag[NUM_CPU] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL};

uint8 LIN_CHANNEL_ID[NUM_CPU] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL};

Lin_PduType Linif_GstSlavePdu[NUM_CPU];

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                             LinIf_WakeupConfirmation                       **
*******************************************************************************/
void LinIf_WakeupConfirmation( EcuM_WakeupSourceType WakeupSource)
{
  uint8 LucPE = 0;
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  LucPE = (uint8)GetCoreID();
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
  Gul_Check_LinIf_WakeupConfirmation[LucPE] = WakeupSource;
  // GucWakeupCount[LucPE]++;
}

Std_ReturnType LinIf_HeaderIndication(NetworkHandleType Channel, Lin_PduType* PduPtr)
{
  uint8 LucPE = 0;
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  LucPE = (uint8)GetCoreID();
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  uint8 LucCount;

  Std_ReturnType LucReturnValue;

  /* Set the return value as default */
  LucReturnValue = E_OK;

  /* Reset header receive flag */
  GblLinIfHeaderReceivedFlag[LucPE] = 0;

  /* SWS_LinIf_00843: LinIf_HeaderIndication shall report LINIF_E_NONEXISTENT_CHANNEL, 
  if an invalid value for Channel is given */
  /* For stub testing, DET is assumed to be ignored. */
  if (LIN_CHANNEL_ID[LucPE] != Channel)
  {
    LucReturnValue = E_NOT_OK;
  }

  /* SWS_LinIf_00844: ⌈If development error detection is enabled and the parameter
  PduPtr has an invalid value*/
  /* For stub testing, DET is assumed to be ignored. */
  if (NULL_PTR == PduPtr)
  {
    LucReturnValue = E_NOT_OK;
  }

  if (E_OK == LucReturnValue)
  {
    GblLinIfHeaderReceivedFlag[LucPE] = 1;
    /* Evaluate PID */
    /* If PID is not relevant to slave, set the PduPtr->Drc to LIN_FRAMERESPONSE_IGNORE */
    if (Linif_GstSlavePdu[LucPE].Pid != PduPtr->Pid)
    {
      PduPtr->Drc = LIN_FRAMERESPONSE_IGNORE;
    }
    else
    {
      /* SWS_LinIf_00738, SWS_LinIf_00733 */
      /* For testing, evaluating PID is ignored */
      /* Suppose PduPtr->Drc (Frame response type) is as a input */
      PduPtr->Drc = Linif_GstSlavePdu[LucPE].Drc;

      /* Configured check sum type */
      PduPtr->Cs = Linif_GstSlavePdu[LucPE].Cs;

      /* Copy the data length to local variable */
      PduPtr->Dl = Linif_GstSlavePdu[LucPE].Dl;

      #if (LIN_AR_VERSION == LIN_AR_R22_11_VERSION)
      /* AR22-11 use LIN_FRAMERESPONSE_TX instead of LIN_MASTER_RESPONSE */
      if (LIN_FRAMERESPONSE_TX == PduPtr->Drc)
      {
        /* Copy the data length to local variable */
        LucCount = PduPtr->Dl;

        /* SWS_LinIf_00845: the PID is evaluated and rated to belong to a transmit frame 
        and the parameter PduPtr->SduPtr has an invalid value, report LINIF_E_PARAM_POINTER*/
        /* For stub testing, DET is assumed to be ignored. */
        if (NULL_PTR == Linif_GstSlavePdu[LucPE].SduPtr)
        {
          GblLinIfHeaderReceivedFlag[LucPE] = 0;
          LucReturnValue = E_NOT_OK;
        }
        else
        {
          /* Copy the data bytes to a LIN Driver software buffer */
          for(uint8 i = 0; i < LucCount; i++)
          {
            PduPtr->SduPtr[i] = Linif_GstSlavePdu[LucPE].SduPtr[i];
          } 
        }
      }
      else
      {
        //Do nothing
      }
      #endif
    }
  }
  else
  {
    //Do nothing
  }
  return LucReturnValue;
}

void LinIf_RxIndication(NetworkHandleType Channel, uint8* Lin_SduPtr)
{
  uint8 LucPE = 0;
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  LucPE = (uint8)GetCoreID();
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  uint8 LucCount = 0;

  Std_ReturnType LucReturnValue;

  /* Set the return value as default */
  LucReturnValue = E_OK;

  /* Reset value of Rx received flag */
  GblLinIfRxReceivedFlag[LucPE] = 0;

  /* SWS_LinIf_00848: If no header of a receive frame has been indicated before
  the function LinIf_RxIndication shall return without further action */
  if (1 == GblLinIfHeaderReceivedFlag[LucPE])
  {
    /* Reset header receive flag */
    GblLinIfHeaderReceivedFlag[LucPE] = 0;

    /* SWS_LinIf_00849: If an invalid value for Channel is given, 
    report LINIF_E_NONEXISTENT_CHANNEL to the DET */
    /* For stub testing, DET is assumed to be ignored. */
    if (LIN_CHANNEL_ID[LucPE] != Channel)
    {
      LucReturnValue = E_NOT_OK;
    }
    
    /* SWS_LinIf_00850: Pduptr has an invalid value, shall raise the 
    development error code LINIF_E_PARAM_POINTER */
    /* For stub testing, DET is assumed to be ignored. */
    if (NULL_PTR == Lin_SduPtr)
    {
      LucReturnValue = E_NOT_OK;
    }

    if (E_OK == LucReturnValue)
    {

      uint8 LucDataLength = 0;

      LucDataLength = Linif_GstSlavePdu[LucPE].Dl;

      for (uint8 i = 0; i < LucDataLength ; i++)
      {
        if(Linif_GstSlavePdu[LucPE].SduPtr[i] == Lin_SduPtr[i])
        {
            LucCount++;
        }
      }

      if (LucCount == LucDataLength)
      {
        GblLinIfRxReceivedFlag[LucPE] = 1;
      }
      else
      {
        //Do nothing
      }
    }
    else
    {
      //Do nothing
    }
  }
  else
  {
    //Do nothing
  }
}

void LinIf_TxConfirmation(NetworkHandleType Channel)
{
  uint8 LucPE = 0;
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  LucPE = (uint8)GetCoreID();
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* Reset Tx Transmit flag */
  GblLinIfTxTransmitFlag[LucPE] = 0;

  /* SWS_LinIf_00852: If no header of a transmit frame has been indicated before
  the function LinIf_TxConfirmation shall return without further action */
  if (1 == GblLinIfHeaderReceivedFlag[LucPE])
  {
    /* SWS_LinIf_00853: If an invalid value for Channel is given, report LINIF_E_NONEXISTENT_CHANNEL */
    /* For stub testing, DET is assumed to be ignored. */
    if (LIN_CHANNEL_ID[LucPE] == Channel)
    {
      GblLinIfTxTransmitFlag[LucPE] = 1;
    }
  }
  else
  {
    GblLinIfTxTransmitFlag[LucPE] = 0;
  }
}

 void LinIf_LinErrorIndication(NetworkHandleType Channel, Lin_SlaveErrorType ErrorStatus)
{
  uint8 LucPE = 0;
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  LucPE = (uint8)GetCoreID();
  #endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */

  /* SWS_LinIf_00855: an invalid value for Channel is given, report LINIF_E_NONEXISTENT_CHANNEL*/
  /* For stub testing, DET is assumed to be ignored. */
  if (LIN_CHANNEL_ID[LucPE] == Channel)
  {
    /* Evaluating Error in header */ 
    if (ErrorStatus == 0x00UL)
    {
     GblLinIfErrorHeaderErrorFlag[LucPE] = 1;
    }
    /* Evaluating Framing error in response */ 
    else if (ErrorStatus == 0x01UL)
    {
      GblLinIfErrorFramingResponseErrorFlag[LucPE] = 1;
    }
    /* Evaluating Checksum error */ 
    else if (ErrorStatus == 0x02UL)
    {
      GblLinIfErrorChecksumErrorFlag[LucPE] = 1; 
    }
    /* Evaluating Monitoring error of transmitted data bit in response */ 
    else if (ErrorStatus == 0x03)
    {
      GblLinIfErrorDataBitResponseErrorFlag[LucPE] = 1;
    }
    /* Evaluating No response */ 
    else if (ErrorStatus == 0x04)
    {
      GblLinIfErrorNoResponseFlag[LucPE] = 1;
    }
    /* Evaluating Incomplete response */ 
    else if (ErrorStatus == 0x05)
    {
      GblLinIfErrorIncompleteResponseFlag[LucPE] = 1;
    }
    else
    {
      //do nothing
    }
  }
} 

/*******************************************************************************
                          End of the file
*******************************************************************************/
