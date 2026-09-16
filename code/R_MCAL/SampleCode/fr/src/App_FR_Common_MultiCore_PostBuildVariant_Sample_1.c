/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_FR_Common_Sample.c                                      */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This application file contains sample test application of FlexRay Driver   */
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
 * 2.4.1:   30/06/2025   : Remove SW-VERSION in file header
 * 2.4.0:   30/06/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00(D) Final Release
 * 2.3.2:   29/04/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:   31/03/2025   : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                         As per multicore support, following changes are made:
 *                         + Add Guard_Init()  
 * 2.3.0:   28/02/2025   : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *                         As per multicore support, following changes are made:
 *                         + add GblPE1Done
 * 2.2.1:   31/12/2024   : Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0:   31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:   31/10/2024   : Update SW-VERSION to 2.1.3
 * 2.1.1:   13/08/2024   : Change Fr_59_Renesas_SetWakeupChannel to call
 *                         channel A instead of channel AB
 *          22/07/2024   : Change Fr_GucInvoked_core1 to Fr_GucInvoked_1 to
 *                          unify when running multiple PE
 *          16/05/2024   : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_FR_Common_Sample_1.h"
#include "App_FR_Common_Sample.h"
#include "App_FR_Device_Sample.h"

/*******************************************************************************
**                           Local Definitions                                **
*******************************************************************************/
#if (DEVICE==U2BxE)
extern void Guard_Init(void);
#endif

/*******************************************************************************
**                      Global variables                                      **
*******************************************************************************/
/* Variable used to store the result of version information check*/



VAR(Fr_59_Renesas_OutputConstdataType, FR_DATA) Fr_output_data_core1[6] =
  {
  /*Fr data 0*/
  { 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006,
  0x00000007, 0x00000008, 0x00000009, 0x00000010, 0x00000011, 0x00000012,
  0x00000013, 0x00000014, 0x00000015, 0x00000016, 0x00000017, 0x00000018,
  0x00000019, 0x00000020, 0x00000021, 0x00000022, 0x00000023, 0x00000024,
  0x00000025, 0x00000026, 0x00000027, 0x00000028, 0x00000029, 0x00000030,
  0x00000031, 0x00000032, 0x00000033, 0x00000034, 0x00000035, 0x00000036,
  0x00000037, 0x00000038, 0x00000039, 0x00000040, 0x00000041, 0x00000042,
  0x00000043, 0x00000044, 0x00000045, 0x00000046, 0x00000047, 0x00000048,
  0x00000049, 0x00000050, 0x00000051, 0x00000052, 0x00000053, 0x00000054,
  0x00000055, 0x00000056, 0x00000057, 0x00000058, 0x00000059, 0x00000060,
  0x00000061, 0x00000062, 0x00000063, 0x00000064 },
  /*Fr data 1*/
  { 0xEEEEEEEE, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006,
  0x00000007, 0x00000008, 0x00000009, 0x00000010, 0x00000011, 0x00000012,
  0x00000013, 0x00000014, 0x00000015, 0x00000016, 0x00000017, 0x00000018,
  0x00000019, 0x00000020, 0x00000021, 0x00000022, 0x00000023, 0x00000024,
  0x00000025, 0x00000026, 0x00000027, 0x00000028, 0x00000029, 0x00000030,
  0x00000031, 0x00000032, 0x00000033, 0x00000034, 0x00000035, 0x00000036,
  0x00000037, 0x00000038, 0x00000039, 0x00000040, 0x00000041, 0x00000042,
  0x00000043, 0x00000044, 0x00000045, 0x00000046, 0x00000047, 0x00000048,
  0x00000049, 0x00000050, 0x00000051, 0x00000052, 0x00000053, 0x00000054,
  0x00000055, 0x00000056, 0x00000057, 0x00000058, 0x00000059, 0x00000060,
  0x00000061, 0x00000062, 0x00000063, 0x00000064 },
  /*Fr data 2*/
  { 0xDDDDDDDD, 0x33333332, 0x00000003, 0x00000004, 0x00000005, 0x00000006,
  0x00000007, 0x00000008, 0x00000009, 0x00000010, 0x00000011, 0x00000012,
  0x00000013, 0x00000014, 0x00000015, 0x00000016, 0x00000017, 0x00000018,
  0x00000019, 0x00000020, 0x00000021, 0x00000022, 0x00000023, 0x00000024,
  0x00000025, 0x00000026, 0x00000027, 0x00000028, 0x00000029, 0x00000030,
  0x00000031, 0x00000032, 0x00000033, 0x00000034, 0x00000035, 0x00000036,
  0x00000037, 0x00000038, 0x00000039, 0x00000040, 0x00000041, 0x00000042,
  0x00000043, 0x00000044, 0x00000045, 0x00000046, 0x00000047, 0x00000048,
  0x00000049, 0x00000050, 0x00000051, 0x00000052, 0x00000053, 0x00000054,
  0x00000055, 0x00000056, 0x00000057, 0x00000058, 0x00000059, 0x00000060,
  0x00000061, 0x00000062, 0x00000063, 0x00000064 },
  /*Fr data 3*/
  { 0xCCCCCCCC, 0x11111111, 0x00000003, 0x00000004, 0x00000005, 0x00000006,
  0x00000007, 0x00000008, 0x00000009, 0x00000010, 0x00000011, 0x00000012,
  0x00000013, 0x00000014, 0x00000015, 0x00000016, 0x00000017, 0x00000018,
  0x00000019, 0x00000020, 0x00000021, 0x00000022, 0x00000023, 0x00000024,
  0x00000025, 0x00000026, 0x00000027, 0x00000028, 0x00000029, 0x00000030,
  0x00000031, 0x00000032, 0x00000033, 0x00000034, 0x00000035, 0x00000036,
  0x00000037, 0x00000038, 0x00000039, 0x00000040, 0x00000041, 0x00000042,
  0x00000043, 0x00000044, 0x00000045, 0x00000046, 0x00000047, 0x00000048,
  0x00000049, 0x00000050, 0x00000051, 0x00000052, 0x00000053, 0x00000054,
  0x00000055, 0x00000056, 0x00000057, 0x00000058, 0x00000059, 0x00000060,
  0x00000061, 0x00000062, 0x00000063, 0x00000064 },
  /*Fr data 4*/
  { 0xB0000000, 0x11111111, 0x00000003, 0x00000004, 0x00000005, 0x00000006,
  0x00000007, 0x00000008, 0x00000009, 0x00000010, 0x00000011, 0x00000012,
  0x00000013, 0x00000014, 0x00000015, 0x00000016, 0x00000017, 0x00000018,
  0x00000019, 0x00000020, 0x00000021, 0x00000022, 0x00000023, 0x00000024,
  0x00000025, 0x00000026, 0x00000027, 0x00000028, 0x00000029, 0x00000030,
  0x00000031, 0x00000032, 0x00000033, 0x00000034, 0x00000035, 0x00000036,
  0x00000037, 0x00000038, 0x00000039, 0x00000040, 0x00000041, 0x00000042,
  0x00000043, 0x00000044, 0x00000045, 0x00000046, 0x00000047, 0x00000048,
  0x00000049, 0x00000050, 0x00000051, 0x00000052, 0x00000053, 0x00000054,
  0x00000055, 0x00000056, 0x00000057, 0x00000058, 0x00000059, 0x00000060,
  0x00000061, 0x00000062, 0x00000063, 0x00000064 },
  /*Fr data 5*/
  { 0xA0000000, 0x11111111, 0x00000003, 0x00000004, 0x00000005, 0x00000006,
  0x00000007, 0x00000008, 0x00000009, 0x00000010, 0x00000011, 0x00000012,
  0x00000013, 0x00000014, 0x00000015, 0x00000016, 0x00000017, 0x00000018,
  0x00000019, 0x00000020, 0x00000021, 0x00000022, 0x00000023, 0x00000024,
  0x00000025, 0x00000026, 0x00000027, 0x00000028, 0x00000029, 0x00000030,
  0x00000031, 0x00000032, 0x00000033, 0x00000034, 0x00000035, 0x00000036,
  0x00000037, 0x00000038, 0x00000039, 0x00000040, 0x00000041, 0x00000042,
  0x00000043, 0x00000044, 0x00000045, 0x00000046, 0x00000047, 0x00000048,
  0x00000049, 0x00000050, 0x00000051, 0x00000052, 0x00000053, 0x00000054,
  0x00000055, 0x00000056, 0x00000057, 0x00000058, 0x00000059, 0x00000060,
  0x00000061, 0x00000062, 0x00000063, 0x00000064 }
  };
VAR(Fr_59_Renesas_OutputDataStrType, FR_DATA) Fr_59_Gstoutput_data_core1[4] =
  {
  /*message buffer 0*/
  {
  /*ulFLX0FRRDHS1*/
  0x050006AC,
  /*ulFLX0FRRDHS2*/
  0xBB80FE00,
  /*ulFLX0FRRDHS3*/
  0x0C800000,
  /*ulFLX0FRMBS*/
  0x0C800000,
  /*Pointer to output data section */
  &Fr_output_data_core1[0] },
  /*message buffer 1*/
  {
  /*ulFLX0FRRDHS1*/
  0x00E006A8,
  /*ulFLX0FRRDHS2*/
  0xBB80002A,
  /*ulFLX0FRRDHS3*/
  0x09E00000,
  /*ulFLX0FRMBS*/
  0x0C800000,
  /*Pointer to output data section */
  &Fr_output_data_core1[1] },
  /*message buffer 2*/
  {
  /*ulFLX0FRRDHS1*/
  0x00A006A0,
  /*ulFLX0FRRDHS2*/
  0xBB80FE00,
  /*ulFLX0FRRDHS3*/
  0xB8F00000,
  /*ulFLX0FRMBS*/
  0x0C800000,
  /*Pointer to output data section */
  &Fr_output_data_core1[2] },
  /*message buffer 3*/
  {
  /*ulFLX0FRRDHS1*/
  0x05E006B4,
  /*ulFLX0FRRDHS2*/
  0xBB80FE00,
  /*ulFLX0FRRDHS3*/
  0xAC400000,
  /*ulFLX0FRMBS*/
  0x0C800000,
  /*Pointer to output data section */
  &Fr_output_data_core1[3] }
  };
VAR(Fr_59_Renesas_OutputPointerTableType, FR_DATA) Fr_59_Gstoutput_table_core1[4] =
  {
  {
  /*pointer to output data structure */
  &Fr_59_Gstoutput_data_core1[0],
  /*Message buffer to be transferred*/
  2 }, {
  /*pointer to output data structure */
  &Fr_59_Gstoutput_data_core1[1],
  /*Message buffer to be transferred*/
  127 }, {
  /*pointer to output data structure */
  &Fr_59_Gstoutput_data_core1[2],
  /*Message buffer to be transferred*/
  127 }, {
  /*pointer to output data structure */
  &Fr_59_Gstoutput_data_core1[3],
  /*Message buffer to be transferred*/
  127 }
  };
/* ========= */
VAR(Fr_59_Renesas_InputConstdataType, FR_DATA) Fr_input_data_core1[6] =
  {
  /*Fr data 0*/
  {
  0xEEEEEEEE,
  0x00000002,
  0x00000003,
  0x00000004,
  0x00000005,
  0x00000006,
  0x00000007
  },
  /*Fr data 1*/
  {
  0xEEEEEEEE,
  0x00000002,
  0x00000003,
  0x00000004,
  0x00000005,
  0x00000006,
  0x00000007
  },
  /*Fr data 2*/
  {
  0xDDDDDDDD,
  0x33333332,
  0x00000003,
  0x00000004,
  0x00000005,
  0x00000006,
  0x00000007
  },
  /*Fr data 3*/
  {
  0xCCCCCCCC,
  0x11111111,
  0x00000003,
  0x00000004,
  0x00000005,
  0x00000006,
  0x00000007
  },
  /*Fr data 4*/
  {
  0xB0000000,
  0x11111111,
  0x00000003,
  0x00000004,
  0x00000005,
  0x00000006,
  0x00000007
  },
  /*Fr data 5*/
  {
  0xA0000000,
  0x11111111,
  0x00000003,
  0x00000004,
  0x00000005,
  0x00000006,
  0x00000007
  }
  };
VAR(Fr_59_Renesas_InputDataStrType, FR_DATA) Fr_59_Gstinput_data_core1[4] =
  {
  /*message buffer 0*/
  {
  /*ulFLX0FRWRHS1*/
  0x157E000E,
  /*ulFLX0FRWRHS2*/
  0x000E0235,
  /*ulFLX0FRWRHS3 */
  0x00000E0,
  /*Pointer to input data section */
  &Fr_input_data_core1[0]
  },
  /*message buffer 1*/
  {
  /*ulFLX0FRWRHS1*/
  0x157F000D,
  /*ulFLX0FRWRHS2*/
  0x000E0235,
  /*ulFLX0FRWRHS3 */
  0x00000D0,
  /*Pointer to input data section */
  &Fr_input_data_core1[1]
  },
  /*message buffer 2*/
  {
  /*ulFLX0FRWRHS1*/
  0x05000005,
  /*ulFLX0FRWRHS2*/
  0x000E0618,
  /*ulFLX0FRWRHS3 */
  0x00000D0,
  /*Pointer to input data section */
  &Fr_input_data_core1[2]
  },
  /*message buffer 3*/
  {
  /*ulFLX0FRWRHS1*/
  0x05E006B4,
  /*ulFLX0FRWRHS2*/
  0xBB80FE00,
  /*ulFLX0FRWRHS3 */
  0xAC400000,
  /*Pointer to input data section */
  &Fr_input_data_core1[3]
  }
  };
VAR(Fr_59_Renesas_InputPointerTableType, FR_DATA) Fr_59_Gstinput_table_core1[4] =
  {
  {
  /*ulFLX0FRWRHS4*/
  0x80704,
  /*pointer to input data structure */
  &Fr_59_Gstinput_data_core1[0]
  },
  {
  /*ulFLX0FRWRHS4*/
  0x80703,
  /*pointer to input data structure */
  &Fr_59_Gstinput_data_core1[1]
  },
  {
  /*ulFLX0FRWRHS4*/
  0x8020B40B,
  /*pointer to input data structure */
  &Fr_59_Gstinput_data_core1[2]
  },
  {
  /*ulFLX0FRWRHS4*/
  0x8020B400,
  /*pointer to input data structure */
  &Fr_59_Gstinput_data_core1[3]
  }
};

/*******************************************************************************
**                           Function Definitions                             **
*******************************************************************************/



int main_PE1(void)
{
  /* Invoke application init function to initilaize MCU, Timer
   and interrupt regsiters */
  uint8 LucControllerIdx;
  uint8 LucAbsTimerIdx ;
  uint8 LucCycle;
  uint8 LucCount;
  uint16 LusOffset;
  uint32 LulCount;
  uint8 LucFr_ListSize;
  uint8 LucFr_WakeupRxStatus;
  uint32 LulFr_ConfigParamValue_Expect;
  uint32 LulFr_ConfigParamValue;
  uint8 LucFr_ConfigParamIdx;
  Std_ReturnType LucReturnValue;
  uint16 LusLPduIdx;
  uint8 Fr_CycleCode;
  uint16 Fr_Offset;
  uint8 LucCyclePtr;
  uint16 LusMacroTickPtr;
  uint8 LucFr_NumOfStartupFrames;
  sint16 LusFr_RateCorrection;
  sint32 LulFr_OffsetCorrection;

  LucControllerIdx = FR_59_RENESAS_ONE;
  LucAbsTimerIdx = FR_59_RENESAS_ZERO;
  LucCycle = FR_59_RENESAS_ZERO;
  LucCount = FR_59_RENESAS_ZERO;
  LusOffset = FR_59_RENESAS_ZERO;
  LucFr_ListSize = FR_59_RENESAS_FIFTEEN;
  LucFr_NumOfStartupFrames = FR_59_RENESAS_ZERO;
  uint16 LusFr_ChannelAOddList[15] = { 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  uint16 LusFr_ChannelBOddList[15] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  uint16 LusFr_ChannelAEvenList[15] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  uint16 LusFr_ChannelBEvenList[15] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  LulFr_ConfigParamValue_Expect = 0xB44C40;
  LulFr_ConfigParamValue = FR_59_RENESAS_ZERO;
  LucFr_ConfigParamIdx = FR_CIDX_GDCYCLE;
  Fr_POCStatusType LddPOCState1 = {0U};
  LucReturnValue = E_OK;
  GblPE0Done = FALSE;

  BoundIntToPE1();
  /* Waiting for core 0 to complete init */
  while (GucStubInitFlag == 0);
  #if (DEVICE==U2BxE)
  Guard_Init();
  #endif
  /* Invoke the API to initialize the FlexRay Driver Component */
  //Fr_59_Renesas_Init(Fr_Config);
  
  /* Support MCU reset for post build variant */
  if (GET_BIT(APP_RESF, APP_MCU_RESF_BIT_POS) == APP_MCU_RST_FLAG_VALUE)
  {
    uint32 LulTimeOut = 0;
    while (LulTimeOut < 0xFF)
    {
      LulTimeOut++;
    }
    Fr_59_Renesas_Init(Fr_Config_Variant_2);
  }
  else
  {
    Fr_59_Renesas_Init(Fr_Config_Variant_1);
  }


  /* Invoke the API to initialize the Communication Controllers */
  LucReturnValue = Fr_59_Renesas_ControllerInit(LucControllerIdx);
  do
  {
    LucReturnValue = Fr_59_Renesas_GetWakeupRxStatus(LucControllerIdx, &LucFr_WakeupRxStatus);
  }while(E_NOT_OK == LucReturnValue);
  /* Invoke the API Fr_59_Renesas_GetPOCStatus() till the POC state is READY */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetPOCStatus(LucControllerIdx, &LddPOCState1);
  }while(FR_POCSTATE_READY != LddPOCState1.State);
  /* Invoke the API Fr_59_Renesas_ReadCCConfig() */
  do
  {
    Fr_59_Renesas_ReadCCConfig(LucControllerIdx, LucFr_ConfigParamIdx, &LulFr_ConfigParamValue);
  }while(LulFr_ConfigParamValue_Expect != LulFr_ConfigParamValue);

  LusLPduIdx = FR_59_RENESAS_ELEVEN;
  /* Invoke the API Fr_59_Renesas_DisableLPdu() */
  do
  {
    LucReturnValue = Fr_59_Renesas_DisableLPdu(LucControllerIdx, LusLPduIdx);
  }while(E_OK != LucReturnValue);


  /* Invoke the API Fr_59_Renesas_SetWakeupChannel() */
  LucReturnValue = Fr_59_Renesas_SetWakeupChannel(LucControllerIdx, FR_CHANNEL_A);

  /* Invoke the API Fr_59_Renesas_SendWUP to send wakeup pattern */
  LucReturnValue = Fr_59_Renesas_SendWUP(LucControllerIdx);

  /* Wait all nodes and are completely awakened  */
  WaitWakeup();

  /* Invoke the API Fr_59_Renesas_GetPOCStatus() till the POC state is READY */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetPOCStatus(LucControllerIdx, &LddPOCState1);
  }while ((FR_POCSTATE_READY != LddPOCState1.State)||
                                                  (E_NOT_OK == LucReturnValue));

  /* Invoke the API to perform coldstart */
  LucReturnValue = Fr_59_Renesas_AllowColdstart(LucControllerIdx);
  /* Invoke the API to start communication */
  LucReturnValue = Fr_59_Renesas_StartCommunication(LucControllerIdx);
  /* Invoke the API Fr_59_Renesas_GetNumOfStartupFrames() */
  do
  {
    Fr_59_Renesas_GetNumOfStartupFrames(LucControllerIdx, &LucFr_NumOfStartupFrames);
  }while(FR_59_RENESAS_TWO != LucFr_NumOfStartupFrames);

  /* Invoke the API Fr_59_Renesas_GetPOCStatus() till the POC state is NORMAL ACTIVE */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetPOCStatus(FR_59_RENESAS_ONE, &LddPOCState1);
  }while (FR_POCSTATE_NORMAL_ACTIVE != (LddPOCState1.State));

  /* Invoke the API Fr_59_Renesas_AllSlots() */
  LucReturnValue = Fr_59_Renesas_AllSlots(LucControllerIdx);

  LucCyclePtr = FR_59_RENESAS_ZERO;
  LusMacroTickPtr = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_GetGlobalTime() */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetGlobalTime(LucControllerIdx, &LucCyclePtr, &LusMacroTickPtr);
  }while(E_OK != LucReturnValue);

  /* Invoke the API Fr_59_Renesas_GetSyncFrameList() */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetSyncFrameList(LucControllerIdx, LucFr_ListSize, LusFr_ChannelAEvenList,
                                                  LusFr_ChannelBEvenList, LusFr_ChannelAOddList, LusFr_ChannelBOddList);
  }while(E_OK != LucReturnValue);

  /* Invoke the API Fr_59_Renesas_GetClockCorrection() */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetClockCorrection(LucControllerIdx, &LusFr_RateCorrection, &LulFr_OffsetCorrection);
  }while(E_OK != LucReturnValue);

  /* Invoke the API Fr_59_Renesas_EnableAbsoluteTimerIRQ() */
  Fr_59_Renesas_EnableAbsoluteTimerIRQ(LucControllerIdx, LucAbsTimerIdx);
  /* Invoke the API Fr_59_Renesas_SetAbsoluteTimer() */
  LucCycle = 15U;
  LusOffset = 8000U;
  LucReturnValue = Fr_59_Renesas_SetAbsoluteTimer(LucControllerIdx,
                   LucAbsTimerIdx, LucCycle, LusOffset);
  if (E_OK == LucReturnValue)
  {
    LucCount = FR_59_RENESAS_ZERO;
    do
    {
      LucCount++;
    }while (FR_59_RENESAS_ONE != Fr_GucInvoked_1[1]);
  }

  LulCount = 1000000;
  while(LulCount--);

  LucCycle = 16U;
  LusOffset = 2800U;
  /* Invoke the API Fr_59_Renesas_SetAbsoluteTimer() */
  LucReturnValue = Fr_59_Renesas_SetAbsoluteTimer(LucControllerIdx,
                                           LucAbsTimerIdx, LucCycle, LusOffset);
  if (E_OK == LucReturnValue)
  {
    LucCount = FR_59_RENESAS_ZERO;
    do
    {
      LucCount++;
    }while (FR_59_RENESAS_TEN != Fr_GucInvoked_1[1]);
  }

  LulCount = 1000000;
  while(LulCount--);

  LucCycle = 16U;
  LusOffset = 2800U;
  /* Invoke the API Fr_59_Renesas_SetAbsoluteTimer() */
  LucReturnValue = Fr_59_Renesas_SetAbsoluteTimer(LucControllerIdx,
                                           LucAbsTimerIdx, LucCycle, LusOffset);
  if (E_OK == LucReturnValue)
  {
    LucCount = FR_59_RENESAS_ZERO;
    do
    {
      LucCount++;
    }while (FR_59_RENESAS_ELEVEN != Fr_GucInvoked_1[1]);
    if (FR_59_RENESAS_ELEVEN == Fr_GucInvoked_1[1])
    {
      do
      {
        /* Invoke the API Fr_59_Renesas_TransferHandlerInit() */
        LucReturnValue = Fr_59_Renesas_TransferHandlerInit(LucControllerIdx, &Fr_59_Gstoutput_table_core1[0],
                                                                                              &Fr_59_Gstoutput_table_core1[0]);
      }while(E_OK != LucReturnValue);

      do
      {
        /* Invoke the API Fr_59_Renesas_TransferQueueTable() */
        LucReturnValue = Fr_59_Renesas_TransferQueueTable( LucControllerIdx, &Fr_59_Gstinput_table_core1[0]);
      }while(E_OK != LucReturnValue);
   }
  }

  LulCount = 1000000;
  while(LulCount--);

  LucCycle = 40U;
  LusOffset = 8000U;
  /* Invoke the API Fr_59_Renesas_SetAbsoluteTimer() */
  LucReturnValue = Fr_59_Renesas_SetAbsoluteTimer(LucControllerIdx,
                                           LucAbsTimerIdx, LucCycle, LusOffset);
  if (E_OK == LucReturnValue)
  {
    LucCount = FR_59_RENESAS_ZERO;
    do
    {
      LucCount++;
    }while (FR_59_RENESAS_FOURTEEN != Fr_GucInvoked_1[1]);
  }

  LulCount = 1000000;
  while(LulCount--);

  /* Invoke the API Fr_59_Renesas_DisableAbsoluteTimerIRQ() */
  LucReturnValue = Fr_59_Renesas_DisableAbsoluteTimerIRQ(LucControllerIdx, LucAbsTimerIdx);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
    }
  /* Invoke the API Fr_59_Renesas_OutputTransferDisable() */
  LucReturnValue = Fr_59_Renesas_OutputTransferDisable(LucControllerIdx);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
    }

  LulCount = 1000000;
  while(LulCount--);

  /* Invoke the API Fr_59_Renesas_InputTransferDisable() */
  LucReturnValue =  Fr_59_Renesas_InputTransferDisable(LucControllerIdx);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
    }

  LulCount = 1000000;
  while(LulCount--);

  Fr_CycleCode = 100;
  Fr_Offset = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_SetCycleCounterFiltering() */
  LucControllerIdx = Fr_59_Renesas_SetCycleCounterFiltering(LucControllerIdx, LucAbsTimerIdx, Fr_CycleCode, Fr_Offset);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
    }
  /* Invoke the API Fr_59_Renesas_AbortCommunication() */
  LucReturnValue = Fr_59_Renesas_AbortCommunication(LucControllerIdx);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
    }
  
  GblPE1Done = TRUE;
  sample_end();
  return 0;
}/* end of main */

/*******************************************************************************
                                End of the file
*******************************************************************************/
