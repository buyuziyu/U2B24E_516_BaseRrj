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
 *                       : As part of CCRH support, following changes are made:
 *                         1. Add GblVerCheckStatus, Fr_GblInvoked1 with volatile
 *                         2. Add preprocessor directive for macro CCRH
 * 2.3.1:     31/03/2025   : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                           As part of G4KH support for U2Bx-E, following changes are made:
 *                           + Add Mcu_Init()
 * 2.3.0:     28/02/2025   : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.1:     31/12/2024   : Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0:     31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:     31/10/2024   : Update SW-VERSION to 2.1.3
 *                           Move BoundIntToPEMax to specific application file of device
 *                           Add function call when using RUN_OTHER_PE
 * 2.1.1:     13/08/2024   : Change Fr_59_Renesas_SetWakeupChannel to call
 *                           channel A instead of channel AB
 *            22/07/2024   : Add macro RUN_OTHER_PE for run multiple PE
 * 2.0.2:     01/03/2024   : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_FR_Common_Sample.h"
#include "App_FR_Device_Sample.h"

/*******************************************************************************
**                           Local Definitions                                **
*******************************************************************************/
#define ENABLE_CTR_IDX_000    STD_ON
#define ENABLE_CTR_IDX_001    STD_OFF

/*******************************************************************************
**                      Global variables                                      **
*******************************************************************************/
#if defined(RUN_OTHER_PE)
extern void Guard_Enable_PE(void);
extern void Guard_Init(void);
extern void BoundIntToPEMax(void);
#endif

/* Variable used to store the result of version information check*/

#if(FR_59_RENESAS_VERSION_INFO_API == STD_ON)
Std_VersionInfoType VersioninfoPtr;
#endif
#if defined CCRH
boolean volatile GblVerCheckStatus = 0U;
boolean volatile Fr_GblInvoked1 = 0U;
#else
boolean GblVerCheckStatus = 0U;
boolean Fr_GblInvoked1 = 0U;
#endif
/*Define maximum PE number*/
#define PEID_MAX_VALUE              0x00000001
#define EIBD_BASE_ADDR       ((volatile uint32 *)(0xFFF82000UL))

VAR(Fr_59_Renesas_OutputConstdataType, FR_DATA) Fr_output_data[6] =
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
VAR(Fr_59_Renesas_OutputDataStrType, FR_DATA) Fr_59_Gstoutput_data[4] =
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
  &Fr_output_data[0] },
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
  &Fr_output_data[1] },
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
  &Fr_output_data[2] },
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
  &Fr_output_data[3] }
  };
VAR(Fr_59_Renesas_OutputPointerTableType, FR_DATA) Fr_59_Gstoutput_table[4] =
  {
  {
  /*pointer to output data structure */
  &Fr_59_Gstoutput_data[0],
  /*Message buffer to be transferred*/
  2 }, {
  /*pointer to output data structure */
  &Fr_59_Gstoutput_data[1],
  /*Message buffer to be transferred*/
  127 }, {
  /*pointer to output data structure */
  &Fr_59_Gstoutput_data[2],
  /*Message buffer to be transferred*/
  127 }, {
  /*pointer to output data structure */
  &Fr_59_Gstoutput_data[3],
  /*Message buffer to be transferred*/
  127 }
  };
/* ========= */
VAR(Fr_59_Renesas_InputConstdataType, FR_DATA) Fr_input_data[6] =
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
VAR(Fr_59_Renesas_InputDataStrType, FR_DATA) Fr_59_Gstinput_data[4] =
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
  &Fr_input_data[0]
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
  &Fr_input_data[1]
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
  &Fr_input_data[2]
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
  &Fr_input_data[3]
  }
  };
VAR(Fr_59_Renesas_InputPointerTableType, FR_DATA) Fr_59_Gstinput_table[4] =
  {
  {
  /*ulFLX0FRWRHS4*/
  0x80704,
  /*pointer to input data structure */
  &Fr_59_Gstinput_data[0]
  },
  {
  /*ulFLX0FRWRHS4*/
  0x80703,
  /*pointer to input data structure */
  &Fr_59_Gstinput_data[1]
  },
  {
  /*ulFLX0FRWRHS4*/
  0x8020B40B,
  /*pointer to input data structure */
  &Fr_59_Gstinput_data[2]
  },
  {
  /*ulFLX0FRWRHS4*/
  0x8020B400,
  /*pointer to input data structure */
  &Fr_59_Gstinput_data[3]
  }
};

/*******************************************************************************
**                           Function Definitions                             **
*******************************************************************************/
#if defined IAR
#pragma optimize=none
#endif
void sample_end(void)
{
  if (GET_BIT(APP_RESF, APP_MCU_RESF_BIT_POS) == APP_MCU_RST_FLAG_VALUE)
  {
    // Not required
  }
  else
  {
    /* Initialize the watchdog in the first variant */
    Mcu_Reset();
  }

  while (1)
  {
    /* No action required*/
  }
}

int main(void)
#if defined(RUN_OTHER_PE)
{
  Guard_Enable_PE();

  #if defined(RUN_PE6)
  /* Initialize MCU */
  Mcu_Init();
  #endif

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
  uint8 Fr_AbsTimerIdx;
  uint8 Fr_CycleCode;
  uint16 Fr_Offset;
  uint8 LucCyclePtr;
  uint16 LusMacroTickPtr;
  uint8 LucFr_NumOfStartupFrames;
  sint16 LusFr_RateCorrection;
  sint32 LulFr_OffsetCorrection;

  LucControllerIdx = FR_59_RENESAS_ZERO;
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
  #if ENABLE_CTR_IDX_000 == STD_ON
  Fr_POCStatusType LddPOCState0 = {0U};
  #endif
  #if ENABLE_CTR_IDX_001 == STD_ON
  Fr_POCStatusType LddPOCState1 = {0U};
  #endif

  LucReturnValue = E_OK;

  #if defined (RUN_OTHER_PE)
  volatile  uint32 count;
  while (count < 80000) {
     count++;
  };
  Guard_Init();
  #endif

  Appl_Init();
  #if defined (RUN_OTHER_PE)
  BoundIntToPEMax();
  #endif

  /* Invoke the API to get the module version Information of FlexRay
       Driver compoent */
  Fr_59_Renesas_GetVersionInfo(&VersioninfoPtr);
#if (FR_59_RENESAS_DEV_ERROR_DETECT == STD_ON)
  if ((FR_59_RENESAS_VENDOR_ID == VersioninfoPtr.vendorID) &&
     (FR_59_RENESAS_MODULE_ID == VersioninfoPtr.moduleID) &&
     (FR_59_RENESAS_SW_MAJOR_VERSION == VersioninfoPtr.sw_major_version) &&
     (FR_59_RENESAS_SW_MINOR_VERSION == VersioninfoPtr.sw_minor_version) &&
     (FR_59_RENESAS_SW_PATCH_VERSION_VALUE == VersioninfoPtr.sw_patch_version))
  {
    GblVerCheckStatus = FR_59_RENESAS_TRUE;
  }
  else
#endif
  {
    GblVerCheckStatus = FR_59_RENESAS_FALSE;
  }
  /* Invoke the API to initialize the FlexRay Driver Component */
  // Fr_59_Renesas_Init(Fr_Config_Variant_1);

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

#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  /* Invoke the API to initialize the Communication Controllers */
  LucReturnValue = Fr_59_Renesas_ControllerInit(LucControllerIdx);
  do
  {
    LucReturnValue = Fr_59_Renesas_GetWakeupRxStatus(LucControllerIdx, &LucFr_WakeupRxStatus);
  }while(E_NOT_OK == LucReturnValue);
  /* Invoke the API Fr_59_Renesas_GetPOCStatus() till the POC state is READY */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetPOCStatus(LucControllerIdx, &LddPOCState0);
  }while(FR_POCSTATE_READY != LddPOCState0.State);
  /* Invoke the API Fr_59_Renesas_ReadCCConfig() */
  do
  {
    Fr_59_Renesas_ReadCCConfig(LucControllerIdx, LucFr_ConfigParamIdx, &LulFr_ConfigParamValue);
  }while(LulFr_ConfigParamValue_Expect != LulFr_ConfigParamValue);
#endif
#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
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
#endif

#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  LusLPduIdx = FR_59_RENESAS_ELEVEN;
  /* Invoke the API Fr_59_Renesas_DisableLPdu() */
  do
  {
    LucReturnValue = Fr_59_Renesas_DisableLPdu(LucControllerIdx, LusLPduIdx);
  }while(E_OK != LucReturnValue);
#endif

#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  LusLPduIdx = FR_59_RENESAS_ELEVEN;
  /* Invoke the API Fr_59_Renesas_DisableLPdu() */
  do
  {
    LucReturnValue = Fr_59_Renesas_DisableLPdu(LucControllerIdx, LusLPduIdx);
  }while(E_OK != LucReturnValue);
#endif

#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_SetWakeupChannel() */
  LucReturnValue = Fr_59_Renesas_SetWakeupChannel(LucControllerIdx, FR_CHANNEL_A);
  if (E_OK == LucReturnValue)
  {
    Fr_GblInvoked1 = FR_59_RENESAS_TRUE;
  }
  else
  {
    Fr_GblInvoked1 = FR_59_RENESAS_FALSE;
  }
#endif

#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  /* Invoke the API Fr_59_Renesas_SetWakeupChannel() */
  LucReturnValue = Fr_59_Renesas_SetWakeupChannel(LucControllerIdx, FR_CHANNEL_A);
#endif


#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_SendWUP to send wakeup pattern */
  LucReturnValue = Fr_59_Renesas_SendWUP(LucControllerIdx);
#endif
#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  /* Invoke the API Fr_59_Renesas_SendWUP to send wakeup pattern */
  LucReturnValue = Fr_59_Renesas_SendWUP(LucControllerIdx);
#endif

  /* Wait all nodes and are completely awakened  */
  WaitWakeup();

#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_GetPOCStatus() till the POC state is READY */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetPOCStatus(LucControllerIdx, &LddPOCState0);
  }while ((FR_POCSTATE_READY != LddPOCState0.State)||
                                                  (E_NOT_OK == LucReturnValue));
#endif
#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  /* Invoke the API Fr_59_Renesas_GetPOCStatus() till the POC state is READY */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetPOCStatus(LucControllerIdx, &LddPOCState1);
  }while ((FR_POCSTATE_READY != LddPOCState1.State)||
                                                  (E_NOT_OK == LucReturnValue));
#endif

#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  /* Invoke the API to perform coldstart */
  LucReturnValue = Fr_59_Renesas_AllowColdstart(LucControllerIdx);
  /* Invoke the API to start communication */
  LucReturnValue = Fr_59_Renesas_StartCommunication(LucControllerIdx);
  /* Invoke the API Fr_59_Renesas_GetNumOfStartupFrames() */
  do
  {
    Fr_59_Renesas_GetNumOfStartupFrames(LucControllerIdx, &LucFr_NumOfStartupFrames);
  }while(FR_59_RENESAS_TWO != LucFr_NumOfStartupFrames);
#endif
#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  /* Invoke the API to perform coldstart */
  LucReturnValue = Fr_59_Renesas_AllowColdstart(LucControllerIdx);
  /* Invoke the API to start communication */
  LucReturnValue = Fr_59_Renesas_StartCommunication(LucControllerIdx);
  /* Invoke the API Fr_59_Renesas_GetNumOfStartupFrames() */
  do
  {
    Fr_59_Renesas_GetNumOfStartupFrames(LucControllerIdx, &LucFr_NumOfStartupFrames);
  }while(FR_59_RENESAS_TWO != LucFr_NumOfStartupFrames);
#endif

#if ENABLE_CTR_IDX_000 == STD_ON
  /* Invoke the API Fr_59_Renesas_GetPOCStatus() till the POC state is NORMAL ACTIVE */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetPOCStatus(FR_59_RENESAS_ZERO, &LddPOCState0);
  }while (FR_POCSTATE_NORMAL_ACTIVE != (LddPOCState0.State));
#endif

#if ENABLE_CTR_IDX_001 == STD_ON
  /* Invoke the API Fr_59_Renesas_GetPOCStatus() till the POC state is NORMAL ACTIVE */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetPOCStatus(FR_59_RENESAS_ONE, &LddPOCState1);
  }while (FR_POCSTATE_NORMAL_ACTIVE != (LddPOCState1.State));
#endif

#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_AllSlots() */
  LucReturnValue = Fr_59_Renesas_AllSlots(LucControllerIdx);
    if (E_OK == LucReturnValue)
    {
      Fr_GblInvoked1 = FR_59_RENESAS_TRUE;
    }
  else
    {
      Fr_GblInvoked1 = FR_59_RENESAS_FALSE;
    }
#endif
#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  /* Invoke the API Fr_59_Renesas_AllSlots() */
  LucReturnValue = Fr_59_Renesas_AllSlots(LucControllerIdx);
#endif

#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  LucCyclePtr = FR_59_RENESAS_ZERO;
  LusMacroTickPtr = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_GetGlobalTime() */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetGlobalTime(LucControllerIdx, &LucCyclePtr, &LusMacroTickPtr);
  }while(E_OK != LucReturnValue);
#endif
#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  LucCyclePtr = FR_59_RENESAS_ZERO;
  LusMacroTickPtr = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_GetGlobalTime() */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetGlobalTime(LucControllerIdx, &LucCyclePtr, &LusMacroTickPtr);
  }while(E_OK != LucReturnValue);
#endif

#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_GetSyncFrameList() */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetSyncFrameList(LucControllerIdx, LucFr_ListSize, LusFr_ChannelAEvenList,
                                                  LusFr_ChannelBEvenList, LusFr_ChannelAOddList, LusFr_ChannelBOddList);
  }while(E_OK != LucReturnValue);
#endif
#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  /* Invoke the API Fr_59_Renesas_GetSyncFrameList() */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetSyncFrameList(LucControllerIdx, LucFr_ListSize, LusFr_ChannelAEvenList,
                                                  LusFr_ChannelBEvenList, LusFr_ChannelAOddList, LusFr_ChannelBOddList);
  }while(E_OK != LucReturnValue);
#endif

#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_GetClockCorrection() */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetClockCorrection(LucControllerIdx, &LusFr_RateCorrection, &LulFr_OffsetCorrection);
  }while(E_OK != LucReturnValue);

#endif
#if ENABLE_CTR_IDX_001 == STD_ON
/* Invoke the API Fr_59_Renesas_GetClockCorrection() */
  do
  {
    LucReturnValue = Fr_59_Renesas_GetClockCorrection(LucControllerIdx, &LusFr_RateCorrection, &LulFr_OffsetCorrection);
  }while(E_OK != LucReturnValue);
#endif
#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  LucAbsTimerIdx = FR_59_RENESAS_ZERO;
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
    }while (FR_59_RENESAS_ONE != Fr_GucInvoked[0]);
  }
#endif
#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  LucAbsTimerIdx = FR_59_RENESAS_ZERO;
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
    }while (FR_59_RENESAS_ONE != Fr_GucInvoked[1]);
  }
#endif

  LulCount = 1000000;
  while(LulCount--);
#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  LucAbsTimerIdx = FR_59_RENESAS_ZERO;
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
    }while (FR_59_RENESAS_TEN != Fr_GucInvoked[0]);
  }
#endif
#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  LucAbsTimerIdx = FR_59_RENESAS_ZERO;
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
    }while (FR_59_RENESAS_TEN != Fr_GucInvoked[1]);
  }
#endif

  LulCount = 1000000;
  while(LulCount--);
#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  LucAbsTimerIdx = FR_59_RENESAS_ZERO;
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
    }while (FR_59_RENESAS_ELEVEN != Fr_GucInvoked[0]);
    if (FR_59_RENESAS_ELEVEN == Fr_GucInvoked[0])
    {
      do
      {
        /* Invoke the API Fr_59_Renesas_TransferHandlerInit() */
        LucReturnValue = Fr_59_Renesas_TransferHandlerInit(LucControllerIdx, &Fr_59_Gstoutput_table[0],
                                                                                              &Fr_59_Gstoutput_table[0]);
      }while(E_OK != LucReturnValue);
        /* Invoke the API Fr_59_Renesas_TransferQueueTable() */
      do
      {
        LucReturnValue = Fr_59_Renesas_TransferQueueTable( LucControllerIdx, &Fr_59_Gstinput_table[0]);
      }while(E_OK != LucReturnValue);
    }
  }
#endif
#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  LucAbsTimerIdx = FR_59_RENESAS_ZERO;
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
    }while (FR_59_RENESAS_ELEVEN != Fr_GucInvoked[1]);
    if (FR_59_RENESAS_ELEVEN == Fr_GucInvoked[1])
    {
      do
      {
        /* Invoke the API Fr_59_Renesas_TransferHandlerInit() */
        LucReturnValue = Fr_59_Renesas_TransferHandlerInit(LucControllerIdx, &Fr_59_Gstoutput_table[0],
                                                                                              &Fr_59_Gstoutput_table[0]);
      }while(E_OK != LucReturnValue);

      do
      {
        /* Invoke the API Fr_59_Renesas_TransferQueueTable() */
        LucReturnValue = Fr_59_Renesas_TransferQueueTable( LucControllerIdx, &Fr_59_Gstinput_table[0]);
      }while(E_OK != LucReturnValue);
   }
  }
#endif

  LulCount = 1000000;
  while(LulCount--);
#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  LucAbsTimerIdx = FR_59_RENESAS_ZERO;
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
    }while (FR_59_RENESAS_FOURTEEN != Fr_GucInvoked[0]);
  }
#endif
#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  LucAbsTimerIdx = FR_59_RENESAS_ZERO;
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
    }while (FR_59_RENESAS_FOURTEEN != Fr_GucInvoked[1]);
  }
#endif

  LulCount = 1000000;
  while(LulCount--);
#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  LucAbsTimerIdx = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_DisableAbsoluteTimerIRQ() */
  LucReturnValue = Fr_59_Renesas_DisableAbsoluteTimerIRQ(LucControllerIdx, LucAbsTimerIdx);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked1 = FR_59_RENESAS_FALSE;
    }
  /* Invoke the API Fr_59_Renesas_OutputTransferDisable() */
  LucReturnValue = Fr_59_Renesas_OutputTransferDisable(LucControllerIdx);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked1 = FR_59_RENESAS_FALSE;
    }
#endif

#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  LucAbsTimerIdx = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_DisableAbsoluteTimerIRQ() */
  LucReturnValue = Fr_59_Renesas_DisableAbsoluteTimerIRQ(LucControllerIdx, LucAbsTimerIdx);
    if (E_OK == LucReturnValue)
    {
        Fr_GblIFr_GblInvoked1nvoked = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked1 = FR_59_RENESAS_FALSE;
    }
  /* Invoke the API Fr_59_Renesas_OutputTransferDisable() */
  LucReturnValue = Fr_59_Renesas_OutputTransferDisable(LucControllerIdx);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked1 = FR_59_RENESAS_FALSE;
    }
#endif

  LulCount = 1000000;
  while(LulCount--);

#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_InputTransferDisable() */
  LucReturnValue =  Fr_59_Renesas_InputTransferDisable(LucControllerIdx);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked1 = FR_59_RENESAS_FALSE;
    }
#endif

#if ENABLE_CTR_IDX_001 == STD_ON
  LucAbsTimerIdx = FR_59_RENESAS_ONE;
  /* Invoke the API Fr_59_Renesas_InputTransferDisable() */
  LucReturnValue =  Fr_59_Renesas_InputTransferDisable(LucControllerIdx);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked1 = FR_59_RENESAS_FALSE;
    }
#endif

  LulCount = 1000000;
  while(LulCount--);
#if ENABLE_CTR_IDX_000 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ZERO;
  Fr_AbsTimerIdx  = FR_59_RENESAS_ZERO;
  Fr_CycleCode = 100;
  Fr_Offset = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_SetCycleCounterFiltering() */
  LucControllerIdx = Fr_59_Renesas_SetCycleCounterFiltering(LucControllerIdx, Fr_AbsTimerIdx, Fr_CycleCode, Fr_Offset);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked1 = FR_59_RENESAS_FALSE;
    }
  /* Invoke the API Fr_59_Renesas_AbortCommunication() */
  LucReturnValue = Fr_59_Renesas_AbortCommunication(LucControllerIdx);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked1 = FR_59_RENESAS_FALSE;
    }
#endif
#if ENABLE_CTR_IDX_001 == STD_ON
  LucControllerIdx = FR_59_RENESAS_ONE;
  Fr_AbsTimerIdx  = FR_59_RENESAS_ZERO;
  Fr_CycleCode = 100;
  Fr_Offset = FR_59_RENESAS_ZERO;
  /* Invoke the API Fr_59_Renesas_SetCycleCounterFiltering() */
  LucControllerIdx = Fr_59_Renesas_SetCycleCounterFiltering(LucControllerIdx, Fr_AbsTimerIdx, Fr_CycleCode, Fr_Offset);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked1 = FR_59_RENESAS_FALSE;
    }
  /* Invoke the API Fr_59_Renesas_AbortCommunication() */
  LucReturnValue = Fr_59_Renesas_AbortCommunication(LucControllerIdx);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked1 = FR_59_RENESAS_FALSE;
    }
#endif
  sample_end();
#if defined(RUN_OTHER_PE)
return 0;
#endif
}/* end of main */

/*******************************************************************************
                                End of the file
*******************************************************************************/
