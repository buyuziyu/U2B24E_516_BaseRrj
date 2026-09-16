/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_PORT_U2B24-E_Sample_0.c                                 */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024 - 2025 Renesas Electronics Corporation. All rights reserved.      */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for PORT Driver Component            */
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
/*              Devices:        U2B24E                                        */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/* 2.3.1:  31/03/2025   : Update SW-VERSION for RH850/U2Bx-E MCAL             */
/*                        Ver22.00.02 Release                                 */
/* 2.1.2:  31/10/2024   : Update SW-VERSION 2.1.2 for Ver22.01.02 U2Bx Beta2  */
/* 2.1.1:  27/07/2024   : Update checkpoint to support execute on VLAB        */
/*         29/06/2024   : Initial Version                                     */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "App_Port_Device_Multi_Sample.h"
#include "Det.h"
#if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_Port.h"
#endif

/*******************************************************************************
**                      Global Variables                                      **
*******************************************************************************/

Std_VersionInfoType versionInfo;
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
uint8 GaaTestResultPE0[8];

void Guard_Enable_PE(void)
{
  const uint32 RSLVXX_base[]=
  {
  (uint32) 0xFFC6B000UL, //PBGERRSLV00_base
  (uint32) 0xFFC63100UL, //PBGERRSLV10_base
  (uint32) 0xFFDE1000UL, //PBGERRSLV20_base
  (uint32) 0xFFC73200UL, //PBGERRSLV30_base
  (uint32) 0xFFC75400UL, //PBGERRSLV40_base
  (uint32) 0xFFC7B000UL, //PBGERRSLV50_base
  (uint32) 0xFFC83000UL, //PBGERRSLV60_base
  (uint32) 0xFFC83040UL, //PBGERRSLV62_base
  (uint32) 0xFFF4A000UL, //PBGERRSLV70_base
  (uint32) 0xFFF2A000UL, //PBGERRSLV8H0_base
  (uint32) 0xFF97A200UL, //PBGERRSLV8L0_base
  (uint32) 0xFF0A1400UL, //PBGERRSLV90_base
  (uint32) 0xFF0A1600UL, //PBGERRSLV91_base
  (uint32) 0xFF87A000UL, //PBGERRSLV100_base
  (uint32) 0xFF8B2000UL, //PBGERRSLV11H0_base
  (uint32) 0xFF8F8100UL,  //PBGERRSLV11L0_base
  };

  const uint32 PBGXX_base[]=
  {
  (uint32) 0xFFC6B080UL, //PBG00_base
  (uint32) 0xFFC6B100UL, //PBG01_base
  (uint32) 0xFFC63000UL, //PBG10_base
  (uint32) 0xFFDE0B00UL, //PBG20_base
  (uint32) 0xFFDE0C00UL, //PBG21_base
  (uint32) 0xFFDE0D00UL, //PBG22_base
  (uint32) 0xFFDE0E00UL, //PBG23_base
  (uint32) 0xFFDE1200UL, //PBG24_base
  (uint32) 0xFFC72B00UL, //PBG30_base
  (uint32) 0xFFC72C00UL, //PBG31_base
  (uint32) 0xFFC72D00UL, //PBG32_base
  (uint32) 0xFFC75300UL, //PBG40_base
  (uint32) 0xFFC75380UL, //PBG41_base
  (uint32) 0xFFC7A300UL, //PBG50_base
  (uint32) 0xFFC7A400UL, //PBG51_base
  (uint32) 0xFFC7A500UL, //PBG52_base
  (uint32) 0xFFC81000UL, //PBG60_base
  (uint32) 0xFFC81200UL, //PBG61_base
  (uint32) 0xFFC82000UL, //PBG62_base
  (uint32) 0xFFF49400UL, //PBG70_base
  (uint32) 0xFFF49600UL, //PBG71_base
  (uint32) 0xFFF29300UL, //PBG8H0_base
  (uint32) 0xFF97A000UL, //PBG8L0_base
  (uint32) 0xFF0A1300UL, //PBG90_base
  (uint32) 0xFF0A1500UL, //PBG91_base
  (uint32) 0xFF0A1700UL, //PBG92_base
  (uint32) 0xFF879400UL, //PBG100_base
  (uint32) 0xFF879500UL, //PBG101_base
  (uint32) 0xFF8B1400UL, //PBG11H0_base
  (uint32) 0xFF8B1600UL, //PBG11H1_base
  (uint32) 0xFF8B1800UL, //PBG11H2_base
  (uint32) 0xFF8F8000UL, //PBG11L0_base    
  (uint32) 0xFF860000UL, //PBG_CANFD0_base
  (uint32) 0xFF860800UL, //PBG_CANFD1_base
  (uint32) 0xFF88FA00UL, //PBG_ATU_base
  (uint32) 0xFFF60000UL  //PBG_GTM_base
  };

  //Enable write
  for (int i =0; i<16;i++)
  {
  volatile uint32 *ptr;
  ptr = (volatile uint32 *)(RSLVXX_base[i] + (uint32)0x18UL);
  *ptr = (uint32)0xA5A5A501UL;
  }

  //Write PBG0
  for (int i =0; i<36;i++)
  {
    for (int ii =0; ii<16;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + ((uint32)ii * 0x8UL));
      *ptr |= 0x00000143UL;
    }
  }

  //Write PBG1
  for (int i =0; i<36;i++)
  {
    for (int ii =0; ii<16;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + 0x4UL + ((uint32)ii * 0x8UL));
      *ptr |= 0xFFFFUL;
    }
  }

  //Disable write
  for (int i =0; i<16;i++)
  {
  volatile uint32 *ptr;
  ptr = (volatile uint32 *)(RSLVXX_base[i]+0x18UL);
  *ptr = 0xA5A5A500UL;
  }
  
}

int main(void)
{
    /* PE0 enables PBG*/
   Guard_Enable_PE();
  boolean LblERRORIN;
  /* Invoking the Port_GetVersionInfo API */
  Port_GetVersionInfo(&versionInfo);
  if (PORT_VENDOR_ID == versionInfo.vendorID &&
      PORT_MODULE_ID == versionInfo.moduleID &&
      (uint8)PORT_SW_MAJOR_VERSION == versionInfo.sw_major_version &&
      (uint8)PORT_SW_MINOR_VERSION == versionInfo.sw_minor_version &&
      (uint8)PORT_SW_PATCH_VERSION == versionInfo.sw_patch_version)
  {
    GaaTestResultPE0[0] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE0[0] = (uint8)PORT_FAIL;
  }

  /* This API will initilize all the registers to the initial values */
  Port_Init(Port_Config);

  /* Set flag to indicate core 1 stub modules have been initialized */
  GucStubInitFlag = 1;

  /* Verifying the configuration values for Port Group 10 registers       */
  /* Check PortMode of Pin7 as Alternative Output (ALT5 OUT)              */
  /* PMC:1(ALT) PIPC:0(S/W IO) <PFCEAE:0> PFCAE:1 PFCE:0 PFC:0 PM:0(OUT)  */
  /* PU: 0, PD:0                                                          */

  if (((PMC10 & 0x0080) == 0x0080) && ((PIPC10 & 0x0080) == 0x0000) 
      && ((PFCAE10 & 0x0080) == 0x0080) && ((PFCE10 & 0x0080) == 0x0000) 
      && ((PM10 & 0x0080) == 0x0000) && ((PU10 & 0x0080) == 0x0000) 
      && ((PD10 & 0x0080) == 0x0000) && ((PIBC10 & 0x0080) == 0x0000) 
      && ((PFC10 & 0x0080) == 0x0000))
  {
    GaaTestResultPE0[1] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE0[1] = (uint8)PORT_FAIL;
  }

  /*
     * This API will change the pin mode to the requested mode if the
     * PortPinModeChangeable runtime parameter for the pin is
     * configured as TRUE. If set to FALSE, this API is not applicable.
     */

  /* PortMode Setting of PortGroup10 PortPin6 is                          */
  /* "Alternative Output mode (ALT1 OUT)"                                 */
  /* PMC:1(ALT) PIPC:0(S/W IO) <PFCEAE:0> PFCAE:0 PFCE:0 PFC:0 PM:0(OUT)  */

  Port_SetPinMode(PortConf_PortGroup10_PortPin6, PORT_APP_ALT1_OUT);
  if ((0x0040 == (PMC10 & 0x0040)) && (0x0000 == (PIPC10 & 0x0040)) 
  && (0x0000 == (PM10 & 0x0040)) && (0 == (PFCAE10 & 0x0040)) 
  && (0 == (PFCE10 & 0x0040)) && (0 == (PFC10 & 0x0040)))
  {
    GaaTestResultPE0[2] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE0[2] = (uint8)PORT_FAIL;
  }
  /*
     * This API will change the direction of the pin to the requested
     * direction if the PortPinDirectionChangeable runtime parameter for
     * the pin is configured as TRUE. If set to FALSE, this API is not
     * applicable.
     *
     * Default Pin direction of PortGroup10
     * Pin5: OUT: direction changeable
     *       -> INPUT
     * PM:1(IN) PMC:0(DIO) PIBC:0(Input Buffer)
     */
  Port_SetPinDirection(PortConf_PortGroup10_PortPin5, PORT_PIN_IN);
  if (((PM10 & 0x0020) == 0x0020) && ((PMC10 & 0x0020) == 0x0000))
  {
    GaaTestResultPE0[3] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE0[3] = (uint8)PORT_FAIL;
  }

  /*
     * Change the direction of PortGroup10 PortPin4
     * If the direction of pin is not changeable, refresh direction.
     */
  /* Enable PWE writing */
  PKCPROT_REG = PORT_PWE_ENABLE_WRITE;

  /* Set PortGroup10 Write Enable value */
  PWE_REG = (uint32)0x00000004UL;

  /* PMSR10 write directly 
   * Set PIN 4 direction to IN.
  */
  PMSR10 = 0x00100010;

  /* Set PortGroup10 Write Disable value */
  PWE_REG = (uint32)0x00000000UL;

  /* Disable PWE writing */
  PKCPROT_REG = PORT_PWE_DISABLE_WRITE;

    /*
     * This API will refresh all the port pins to the configured value.
     */
  while (GucRefreshPinFlag == 1);
  Port_RefreshPortDirection();
  GucRefreshPinFlag = 1;
    /* Default Pin direction of PortGroup10
     * Pin5: direction changeable -> Not being affected after
     * refreshing.
     * Pin4: direction unchangeable -> change from IN to OUT after
     * refreshing.
     */
  if (((PM10 & 0x0030) == 0x0020))
  {
    GaaTestResultPE0[4] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE0[4] = (uint8)PORT_FAIL;
  } /* End of Port_RefreshPortDirection API */

  /* This API will switch a pin of port from DIO to ALT. */
  Port_SetToAlternateMode(PortConf_PortGroup10_PortPin3);
  if ((PMC10 & 0x0008) == 0x0008)
  {
    GaaTestResultPE0[5] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE0[5] = (uint8)PORT_FAIL;
  }

  /* This API will switch a pin of port from ALT to DIO. */
  Port_SetToDioMode(PortConf_PortGroup10_PortPin3);
  if ((PMC10 & 0x0004) == 0x0000)
  {
    GaaTestResultPE0[6] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE0[6] = (uint8)PORT_FAIL;
  }

  /* This API will switch a port pin to initial/default configured direction*/
  Port_SetPinDirection(PortConf_PortGroup10_PortPin2, PORT_PIN_IN);
  Port_SetPinDefaultDirection(PortConf_PortGroup10_PortPin2);
  if ((PM10 & 0x0004) == 0x0000)
  {
    GaaTestResultPE0[7] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE0[7] = (uint8)PORT_FAIL;
  }

  /*
  * Change the mode of P10_1 and P10_0 to "Alt mode"
  * "Alternative mode".
  * P10_0 is configured as PortPinModeChangeable = false.
  * This step is for Port_SetPinDefaultMode.
  *
  * Default Configured setting is:
  *  PortGroup10
  *  Pin1: PortPinModeChangeable = True; DIO Mode
  *  Pin0: PortPinModeChangeable = False; DIO Mode
  * Change setting temporally
  *  Pin1: ALT Mode
  *  Pin0: ALT Mode
  */
  /* Enable PWE writing */
  PKCPROT_REG = PORT_PWE_ENABLE_WRITE;

  /* Set PortGroup10 Write Enable value */
  PWE_REG = (uint32)0x00000004UL;

  /* PMCSR0 write directly */
  PMCSR10 = 0x00030003; /* Pin1: On, Pin0: On */
  
  /* In addition, also set non-default value of PFC, PFCE, PIPC, and PMSR
  * to verify after Port_SetPinDefaultMode is called.
  */

  PFC10 = PFC10 | 0x0003;   /* Pin1: 1, Pin0: 1 */
  PFCE10 = PFCE10 | 0x0003; /* Pin1: 1, Pin0: 1 */
  PMCSR10 = 0x00030003;     /* Pin1: ALT Pin0: ALT */
  PMSR10 = 0x00030003;      /* Pin1: IN, Pin0: IN */

  /* Set PortGroup10 Write Disable value */
  PWE_REG = (uint32)0x00000000UL;

  /* Disable PWE writing */
  PKCPROT_REG = PORT_PWE_DISABLE_WRITE;

  /*
  * Sample usage for the Mask/Unmask of ERRORIN signal output
  * and clearing of ERRORIN error status.
  */

  /* Save the current mask value of ERRORIN,
  Mask the ECM error output signal of ERRORIN */
  LblERRORIN = Port_EcmMaskERRORIN(PORT_MASK);
  /* Cleared ERRORIN error status */
  Port_EcmClearERRORIN();
  /* Set Unmask/Mask the ECM error output signal of ERRORIN */
  if (PORT_UNMASK == LblERRORIN)
  {
    LblERRORIN = Port_EcmMaskERRORIN(PORT_UNMASK);
  }
  else
  {
    /* No action required */
  }
  sample_end();

  return (0);
} /* End of main() function */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
