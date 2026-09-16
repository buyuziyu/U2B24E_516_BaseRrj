/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_PORT_U2B24-E_EVA_Sample.c                               */
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
/*              Devices:        U2B24E_EVA                                    */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/* 2.3.1:  31/03/2025   : Update checkpoint for Port_Init()                   */
/* 2.1.2:  31/10/2024   : Update SW-VERSION 2.1.2 for Ver22.01.02 U2Bx Beta2  */
/* 2.1.1:  27/07/2024   : Update checkpoint to support execute on VLAB        */
/*         31/05/2023   : Initial version                                     */
/*                                                                            */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "App_Port_Device_Sample.h"
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
uint8 GaaTestResult[8];

int main(void)
{
  boolean LblERRORIN;
  /* Invoking the Port_GetVersionInfo API */
  Port_GetVersionInfo(&versionInfo);
  if (PORT_VENDOR_ID == versionInfo.vendorID &&
      PORT_MODULE_ID == versionInfo.moduleID &&
      (uint8)PORT_SW_MAJOR_VERSION == versionInfo.sw_major_version &&
      (uint8)PORT_SW_MINOR_VERSION == versionInfo.sw_minor_version &&
      (uint8)PORT_SW_PATCH_VERSION == versionInfo.sw_patch_version)
  {
    GaaTestResult[0] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResult[0] = (uint8)PORT_FAIL;
  }

  /* This API will initilize all the registers to the initial values */
  Port_Init(Port_Config);

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
    GaaTestResult[1] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResult[1] = (uint8)PORT_FAIL;
  }

  /*
     * This API will change the pin mode to the requested mode if the
     * PortPinModeChangeable runtime parameter for the pin is
     * configured as TRUE. If set to FALSE, this API is not applicable.
     */

  /* PortMode Setting of PortGroup10 PortPin6 is                          */
  /* "Alternative Output mode (ALT1 OUT)"                                 */
  /* PMC:1(ALT) PIPC:0(S/W IO) <PFCEAE:0> PFCAE:0 PFCE:0 PFC:0 PM:0(OUT)  */
  /* PINV:0 PODC:1 PODCE:1(P-ch open drain) PDSC:1 PUCC:0(Mid) P:1(High)  */

  Port_SetPinMode(PortConf_PortGroup10_PortPin6, PORT_APP_ALT1_OUT);
  if ((0x0040 == (PMC10 & 0x0040)) && (0x0000 == (PIPC10 & 0x0040)) 
  && (0x0000 == (PM10 & 0x0040)) && (0 == (PFCAE10 & 0x0040)) 
  && (0x0000 == (PFCE10 & 0x0040)) && (0 == (PFC10 & 0x0040)))
  {
    GaaTestResult[2] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResult[2] = (uint8)PORT_FAIL;
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
     * PM:1(IN) PMC:0(DIO) PIBC:1(Input Buffer)
     */
  Port_SetPinDirection(PortConf_PortGroup10_PortPin5, PORT_PIN_IN);
  if (((PM10 & 0x0020) == 0x0020) && ((PMC10 & 0x0020) == 0x0000))
  {
    GaaTestResult[3] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResult[3] = (uint8)PORT_FAIL;
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
  Port_RefreshPortDirection();
    /* Default Pin direction of PortGroup10
     * Pin5: direction changeable -> Not being affected after
     * refreshing.
     * Pin4: direction unchangeable -> change from IN to OUT after
     * refreshing.
     */
  if (((PM10 & 0x0030) == 0x0020))
  {
    GaaTestResult[4] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResult[4] = (uint8)PORT_FAIL;
  } /* End of Port_RefreshPortDirection API */

  /* This API will switch a pin of port from DIO to ALT. */
  Port_SetToAlternateMode(PortConf_PortGroup10_PortPin3);
  if ((PMC10 & 0x0008) == 0x0008)
  {
    GaaTestResult[5] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResult[5] = (uint8)PORT_FAIL;
  }

  /* This API will switch a pin of port from ALT to DIO. */
  Port_SetToDioMode(PortConf_PortGroup10_PortPin3);
  if ((PMC10 & 0x0004) == 0x0000)
  {
    GaaTestResult[6] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResult[6] = (uint8)PORT_FAIL;
  }

  /* This API will switch a port pin to initial/default configured direction*/
  Port_SetPinDirection(PortConf_PortGroup10_PortPin2, PORT_PIN_IN);
  Port_SetPinDefaultDirection(PortConf_PortGroup10_PortPin2);
  if ((PM10 & 0x0004) == 0x0000)
  {
    GaaTestResult[7] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResult[7] = (uint8)PORT_FAIL;
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
     *
     * Sample usage for the Mask/Unmask of ERRORIN signal output
     * and clearing of ERRORIN error status.
     *
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

  return (0);
} /* End of main() function */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
