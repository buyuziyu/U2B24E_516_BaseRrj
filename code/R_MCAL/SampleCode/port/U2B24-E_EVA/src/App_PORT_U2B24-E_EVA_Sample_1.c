/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_PORT_U2B24-E_Sample_1.c                                 */
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

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
uint8 GaaTestResultPE1[7];

int main_PE1(void)
{
  //boolean LblERRORIN;
  /* Waiting for Port_Init() initialize on core 0 */
  while (GucStubInitFlag == 0);

  /* Verifying the configuration values for Port Group 2 registers    */
  /* Check PortMode of Pin7 as Alternative Output (ALT5 OUT)              */
  /* PMC:1(ALT) PIPC:1(S/W IO) <PFCEAE:0> PFCAE:1 PFCE:0 PFC:0 PM:0(OUT)  */
  /* PU: 0, PD:0                                                          */

  if (((PMC2 & 0x0080) == 0x0080) && ((PIPC2 & 0x0080) == 0x0000) 
      && ((PFCAE2 & 0x0080) == 0x0080) && ((PFCE2 & 0x0080) == 0x0000) 
      && ((PM2 & 0x0080) == 0x0000) && ((PU2 & 0x0080) == 0x0000) 
      && ((PD2 & 0x0080) == 0x0000) && ((PIBC2 & 0x0080) == 0x0000) 
      && ((PFC2 & 0x0080) == 0x0000) && ((PFCEAE2 & 0x0080) == 0x0000))
  {
    GaaTestResultPE1[0] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE1[0] = (uint8)PORT_FAIL;
  }

  /*
     * This API will change the pin mode to the requested mode if the
     * PortPinModeChangeable runtime parameter for the pin is
     * configured as TRUE. If set to FALSE, this API is not applicable.
     */

  /* PortMode Setting of PortGroup2 PortPin6 is                       */
  /* "Alternative IN mode (ALT5 IN)"                                  */
  /* PMC:1(ALT) PIPC:0(S/W IO) <PFCEAE:0> PFCAE:1 PFCE:0 PFC:0 PM:1(IN)  */

  Port_SetPinMode(PortConf_PortGroup2_PortPin6, PORT_APP_ALT5_IN);
  if ((0x0040 == (PMC2 & 0x0040)) && (0 == (PIPC2 & 0x0040)) 
  && (0x0040 == (PM2 & 0x0040)) && (0x0040 == (PFCAE2 & 0x0040)) 
  && (0 == (PFCE2 & 0x0040)) && (0 == (PFC2 & 0x0040)))
  {
    GaaTestResultPE1[1] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE1[1] = (uint8)PORT_FAIL;
  }
  /*
     * This API will change the direction of the pin to the requested
     * direction if the PortPinDirectionChangeable runtime parameter for
     * the pin is configured as TRUE. If set to FALSE, this API is not
     * applicable.
     *
     * Default Pin direction of PortGroup2
     * Pin5: OUT: direction changeable
     *       -> INPUT
     * PM:1(IN) PMC:0(DIO) PIBC:0(Input Buffer)
     */
  Port_SetPinDirection(PortConf_PortGroup2_PortPin5, PORT_PIN_IN);
  if (((PM2 & 0x0020) == 0x0020) && ((PMC2 & 0x0020) == 0x0000))
  {
    GaaTestResultPE1[2] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE1[2] = (uint8)PORT_FAIL;
  }

  /*
     * Change the direction of PortGroup2 PortPin4
     * If the direction of pin is not changeable, refresh direction.
     */
  /* Enable PWE writing */
  PKCPROT_REG = PORT_PWE_ENABLE_WRITE;

  /* Set PortGroup2 Write Enable value */
  PWE_REG = (uint32)0x00000003UL;

  /* PMSR2 write directly 
   * Set PIN 4 direction to IN.
  */
  PMSR2 = 0x00100010;

  /* Set PortGroup2 Write Disable value */
  PWE_REG = (uint32)0x00000000UL;

  /* Disable PWE writing */
  PKCPROT_REG = PORT_PWE_DISABLE_WRITE;

  GucRefreshPinFlag = 0;
  while (GucRefreshPinFlag == 0);
    /* Default Pin direction of PortGroup2
     * Pin5: direction changeable -> Not being affected after
     * refreshing.
     * Pin4: direction unchangeable -> change from IN to OUT after
     * refreshing.
     */
  if (((PM2 & 0x0030) == 0x0020))
  {
    GaaTestResultPE1[3] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE1[3] = (uint8)PORT_FAIL;
  } /* End of Port_RefreshPortDirection API */

  /* This API will switch a pin of port from DIO to ALT. */
  Port_SetToAlternateMode(PortConf_PortGroup2_PortPin3);
  if ((PMC2 & 0x0008) == 0x0008)
  {
    GaaTestResultPE1[4] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE1[4] = (uint8)PORT_FAIL;
  }

  /* This API will switch a pin of port from ALT to DIO. */
  Port_SetToDioMode(PortConf_PortGroup2_PortPin3);
  if ((PMC2 & 0x0004) == 0x0000)
  {
    GaaTestResultPE1[5] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE1[5] = (uint8)PORT_FAIL;
  }

  /* This API will switch a port pin to initial/default configured direction*/
  Port_SetPinDirection(PortConf_PortGroup2_PortPin2, PORT_PIN_IN);
  Port_SetPinDefaultDirection(PortConf_PortGroup2_PortPin2);
  if ((PM2 & 0x0004) == 0x0000)
  {
    GaaTestResultPE1[6] = (uint8)PORT_PASS;
  }
  else
  {
    GaaTestResultPE1[6] = (uint8)PORT_FAIL;
  }

  /*
     * Change the mode of P2_1 and P2_0 to "Alt mode"
     * "Alternative mode".
     * P2_0 is configured as PortPinModeChangeable = false.
     * This step is for Port_SetPinDefaultMode.
     *
     * Default Configured setting is:
     *  PortGroup2
     *  Pin1: PortPinModeChangeable = True; DIO Mode
     *  Pin0: PortPinModeChangeable = False; DIO Mode
     * Change setting temporally
     *  Pin1: ALT Mode
     *  Pin0: ALT Mode
     */
  /* Enable PWE writing */
  PKCPROT_REG = PORT_PWE_ENABLE_WRITE;

  /* Set PortGroup2 Write Enable value */
  PWE_REG = (uint32)0x00000002UL;

  /* PMCSR0 write directly */
  PMCSR2 = 0x00030003; /* Pin1: On, Pin0: On */
  /* In addition, also set non-default value of PFC, PFCE, PIPC, and PMSR
     * to verify after Port_SetPinDefaultMode is called.
     */
  PFC2 = PFC2 | 0x0003;   /* Pin1: 1, Pin0: 1 */
  PFCE2 = PFCE2 | 0x0003; /* Pin1: 1, Pin0: 1 */
  PMCSR2 = 0x00030003;     /* Pin1: ALT Pin0: ALT */
  PMSR2 = 0x00030003;      /* Pin1: IN, Pin0: IN */

  /* Set PortGroup2 Write Disable value */
  PWE_REG = (uint32)0x00000000UL;

  /* Disable PWE writing */
  PKCPROT_REG = PORT_PWE_DISABLE_WRITE;

  sample_end();

  return (0);
} /* End of main() function */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
