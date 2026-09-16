/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_FR_U2B24-E_Sample.c                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains sample application for FR Driver Component              */
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
 *  2.4.1:   30/06/2025   : Remove SW-VERSION in file header
 *  2.3.1:   31/03/2025   : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                          As per multicore support, following changes are made:
 *                          + Add Guard_Enable_PE(), Guard_Init() 
 *                          + Update Port_Init()
 *  2.3.0:   28/02/2025   : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D U2Cx Release
 *                          As per HWUM U2B24E version 0.5 support, following changes are made:
 *                          - Update IH_Init, Port_Init
 *  2.2.0:   31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 *                          Update IH_Init, Port_Init
 *  2.1.3:   31/10/2024   : Update SW-VERSION to 2.1.3
 *  2.1.1:   13/08/2024   : Delete Fr_59_Renesas_HaltCommunication due to wrong
 *                           sequence when calling
 *                           Fr_59_Renesas_SetCycleCounterFiltering after that
 *           23/07/2024   : Change Fr_GucInvoked_core0 to Fr_GucInvoked
 *                           Fr_GucInvoked_core1 to Fr_GucInvoked_1 to
 *                           unify when running multiple PE
 *  2.0.2:   26/03/2024   : Initial Version
 */
/******************************************************************************/
/******************************************************************************
**                      Include Section                                      **
******************************************************************************/
#include "App_FR_Device_Sample.h"
#include "App_FR_Common_Sample_0.h"
#include "App_FR_Common_Sample_1.h"
/******************************************************************************
**                      Global variables                                      **
*******************************************************************************/

boolean Fr_GblInvoked = 0U;
boolean Fr_GblInvoked_1 = 0U;
uint8 Fr_GucInvoked[2] = {0U};
uint8 Fr_GucInvoked_1[2] = {0U};
const uint8 LaaAppArray[254] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14,
    0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
    0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C,
    0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44,
    0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
    0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C,
    0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
    0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74,
    0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80,
    0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C,
    0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
    0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
    0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0,
    0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC,
    0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8,
    0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4,
    0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0,
    0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC,
    0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
    0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE };
const uint8 LaaAppArray_2[8] =
    { 0, 234, 235, 236, 237, 238, 239, 240};

/*******************************************************************************
**                           Function Definitions                             **
*******************************************************************************/

#define PEID_MAX_VALUE              0x00000001

#define EIBD_BASE_ADDR       ((volatile uint32 *)(0xFFF82000UL))

void Guard_Enable_PE(void)
{
  PBGKCPROT(20) = KCPROT_SET;
  PBGCKPROT1(20,0) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  PBGKCPROT(20) = KCPROT_CLR;

  PBGKCPROT(0) = KCPROT_SET;
  PBGCKPROT1(0,0) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  PBGKCPROT(0) = KCPROT_CLR;
    
  PBGKCPROT(20) = KCPROT_SET;
  PBGCKPROT1(21,9) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  PBGKCPROT(20) = KCPROT_CLR;
    
  PBGKCPROT(20) = KCPROT_SET;
  PBGCKPROT1(21,15) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  PBGKCPROT(20) = KCPROT_CLR;
 
  INTC2GKCPROT = KCPROT_SET;
  INTC2GMPID(724) = (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  INTC2GPROT(724) |= (uint32)((0x01<<16)|(0x01<<18));
  INTC2GPROT_GR   |= (uint32)((0x01<<16)|(0x01<<18));
  INTC2GPROT_IMR  |= (uint32)((0x01<<16)|(0x01<<18));
  // BoundIntToPEMax();
  INTC2GKCPROT = KCPROT_CLR;
  
  INTC2GKCPROT = KCPROT_SET;
  INTC2GMPID(726) = (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  INTC2GPROT(726) |= (uint32)((0x01<<16)|(0x01<<18));
  INTC2GPROT_GR   |= (uint32)((0x01<<16)|(0x01<<18));
  INTC2GPROT_IMR   |= (uint32)((0x01<<16)|(0x01<<18));
  // BoundIntToPEMax();
  INTC2GKCPROT = KCPROT_CLR;

  PBGKCPROT(62) = KCPROT_SET;
  PBGCKPROT1(62,0) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  PBGKCPROT(62) = KCPROT_CLR;
    
  HBGKCPROT(92)  = KCPROT_SET;
  HBGPROT1(92)  |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  HBGKCPROT(92)  = KCPROT_CLR;

  HBGKCPROT(93)  = KCPROT_SET;
  HBGPROT1(93)  |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  HBGKCPROT(93)  = KCPROT_CLR;
}

void Guard_Init(void)
{
  PBGKCPROT(20) = KCPROT_SET;
  PBGCKPROT1(20,2) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  PBGKCPROT(20) = KCPROT_CLR;

  PBGKCPROT(0) = KCPROT_SET;
  PBGCKPROT1(0,0) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  PBGKCPROT(0) = KCPROT_CLR;

  PBGKCPROT(20) = KCPROT_SET;
  PBGCKPROT1(21,5) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  PBGKCPROT(20) = KCPROT_CLR;
    
  PBGKCPROT(20) = KCPROT_SET;
  PBGCKPROT1(21,6) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  PBGKCPROT(20) = KCPROT_CLR;
    
  PBGKCPROT(20) = KCPROT_SET;
  PBGCKPROT1(21,11) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  PBGKCPROT(20) = KCPROT_CLR;

  INTC2GKCPROT = KCPROT_SET;
  INTC2GMPID(724) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  INTC2GPROT(724) |= (uint32)((0x01<<16)|(0x01<<18));
  INTC2GPROT_GR   |= (uint32)((0x01<<16)|(0x01<<18));
  INTC2GPROT_IMR  |= (uint32)((0x01<<16)|(0x01<<18));
  // BoundIntToPEMax();
  INTC2GKCPROT = KCPROT_CLR;
  
  INTC2GKCPROT = KCPROT_SET;
  INTC2GMPID(726) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  INTC2GPROT(726) |= (uint32)((0x01<<16)|(0x01<<18));
  INTC2GPROT_GR   |= (uint32)((0x01<<16)|(0x01<<18));
  INTC2GPROT_IMR   |= (uint32)((0x01<<16)|(0x01<<18));
  // BoundIntToPEMax();
  INTC2GKCPROT = KCPROT_CLR;
 
  PBGKCPROT(62) = KCPROT_SET;
  PBGCKPROT1(62,1) |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  PBGKCPROT(62) = KCPROT_CLR;
  
  HBGKCPROT(92)  = KCPROT_SET;
  HBGPROT1(92)  |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  HBGKCPROT(92)  = KCPROT_CLR;

  HBGKCPROT(93)  = KCPROT_SET;
  HBGPROT1(93)  |= (uint32)((0x01<<1)|(0x01<<2)|(0x01<<3)|(0x01<<4));
  HBGKCPROT(93)  = KCPROT_CLR;
  
}

/*******************************************************************************
 * Initialization of Application                                               *
 ******************************************************************************/
void Appl_Init(void)
{
  /* Disable protection for module standby194 registers */
  MSRKCPROT = KCPROT_SET;
  /* Enable FLXA modules */
  MSR_FLXA &= MSR_ACTIVE;
  /* Enable protection for module standby registers */
  MSRKCPROT = KCPROT_CLR;

  /* Initialize MCU */
  Mcu_Init();

  /* Initialize Port */
  Port_Init();

  /* Initialize Interrupt Handler */
  IH_Init();

  /* Enable global interrupt */
  ENABLE_INTERRUPT();

}

/*******************************************************************************
**                      Port Initialization                                   **
*******************************************************************************/
void Port_Init(void)
{
  /* Set Port Keycode Register to Enable */
  PKCPROT = KCPROT_SET;

  /* Set Port Write Enable Register to Enable */
  PWE = 0x00000106UL;

  /* Pin   : Alternative Function    | PMC PM PIBC PIPC PBDC |  PFCEAE PFCAE PFCE PFC | */
  /* -----FLXA0----------------------+-----------------------+ -----------------------+ */
  /* P02_00 : ALT_OUT3  (FLXA0TXDA)  |  1   0   0    0    0  |    0      0     1   0  | */
  /* P02_01 : ALT_IN6   (FLXA0RXDA)  |  1   1   0    0    1  |    0      1     0   1  | */
  /* P02_02 : ALT_OUT4  (FLXA0TXDB)  |  1   0   0    0    0  |    0      0     1   1  | */
  /* P02_04 : ALT_OUT2  (FLXA0TXENA) |  1   0   0    0    0  |    0      0     0   1  | */
  /* P02_08 : ALT_IN6   (FLXA0RXDB)  |  1   1   0    0    1  |    0      1     0   1  | */
  /* P14_06 : ALT_OUT4  (FLXA0TXENB) |  1   0   0    0    0  |    0      0     1   1  | */
  /* -----FLXA1----------------------+-----------------------+ -----------------------+ */
  /* P01_01 : ALT_IN5   (FLXA1RXDA)  |  1   1   0    0    1  |    0      1     0   0  | */
  /* P01_08 : ALT_IN11  (FLXA1RXDB)  |  1   1   0    0    1  |    1      0     1   0  | */
  /* P01_12 : ALT_OUT5  (FLXA1TXDA)  |  1   0   0    0    0  |    0      1     0   0  | */
  /* P01_13 : ALT_OUT5  (FLXA1TXDB)  |  1   0   0    0    0  |    0      1     0   0  | */
  /* P01_14 : ALT_OUT5  (FLXA1TXENA) |  1   0   0    0    0  |    0      1     0   0  | */
  /* P02_15 : ALT_OUT5  (FLXA1TXENB) |  1   0   0    0    0  |    0      1     0   0  | */

  /* Port PIN set for FLXA0 */
  FR_PORT0[2].usPMC     = (uint16)0x8117;
  FR_PORT0[2].usPM      = (uint16)0x0102;
  FR_PORT1[2].usPIBC    = (uint16)0x0000;
  FR_PORT1[2].usPIPC    = (uint16)0x0000;
  FR_PORT1[2].usPBDC    = (uint16)0x0102;
  FR_PORT0[2].usPFCEAE  = (uint16)0x0000;
  FR_PORT0[2].usPFCAE   = (uint16)0x8102;
  FR_PORT0[2].usPFCE    = (uint16)0x0005;
  FR_PORT0[2].usPFC     = (uint16)0x0116;

  FR_PORT0[14].usPMC    = (uint16)0x0040;
  FR_PORT0[14].usPM     = (uint16)0x0000;
  FR_PORT1[14].usPIBC   = (uint16)0x0000;
  FR_PORT1[14].usPIPC   = (uint16)0x0000;
  FR_PORT1[14].usPBDC   = (uint16)0x0000;
  FR_PORT0[14].usPFCEAE = (uint16)0x0000;
  FR_PORT0[14].usPFCAE  = (uint16)0x0000;
  FR_PORT0[14].usPFCE   = (uint16)0x0040;
  FR_PORT0[14].usPFC    = (uint16)0x0040;

  FR_PORT0[1].usPMC     = (uint16)0x7102;
  FR_PORT0[1].usPM      = (uint16)0x0102;
  FR_PORT1[1].usPIBC    = (uint16)0x0000;
  FR_PORT1[1].usPIPC    = (uint16)0x0000;
  FR_PORT1[1].usPBDC    = (uint16)0x0102;
  FR_PORT0[1].usPFCEAE  = (uint16)0x0100;
  FR_PORT0[1].usPFCAE   = (uint16)0x7002;
  FR_PORT0[1].usPFCE    = (uint16)0x0100;
  FR_PORT0[1].usPFC     = (uint16)0x0000;

  /* Set Port Write Enable Register to Disable */
  PWE = 0x00000000UL;

  /* Set Port Keycode Register to Disable */
  PKCPROT = KCPROT_CLR;
}

void Mcu_Init(void)
{
  /**********************/
  /* LSIntOSC(240[KHz]) */
  /**********************/
  /* (After power supply the LSIntOSC starts operation. It cannot be stopped.) */

  /**********************/
  /* HSIntOSC(200[MHz]) */
  /**********************/
  /* (After Power On Reset or System Reset1 release the HSIntOSC starts operation.) */

  /* Wait to HSIntOSC clock is stable(HSOSCS.HSOSCSTAB = 1). */
  while ( (HSOSCS & 0x00000002UL) != 0x00000002UL )
  {
  }

  /* HSIntOSC stops operation in stand-by mode(HSOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = KCPROT_SET;
  HSOSCSTPM   = 0x00000000UL;
  CLKKCPROT1  = KCPROT_CLR;

  /************************************************/
  /* MainOSC(40[MHz] on U2AEVA1 evaluation board) */
  /* - OPBT10.MOSC_FREQ = 011b is needed.         */
  /************************************************/

  /* 1.Confirm that the HSIntOSC is stable (HSOSCS.HSOSCSTAB = 1). */
  /* (Checked) **/

  /* 3.Start the MainOSC (MOSCE.MOSCENTRG = 1). */
  CLKKCPROT1  = KCPROT_SET;
  MOSCE       = 0x00000001UL;
  CLKKCPROT1  = KCPROT_CLR;

  /* 4.Confirm that the MainOSC has been started (MOSCS.MOSCSTAB = 1). */
  while ( (MOSCS & 0x00000002UL) != 0x00000002UL )
  {
  }

  /* MainOSC stops operation in stand-by mode(MOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = KCPROT_SET;
  MOSCSTPM    = 0x00000000UL;
  CLKKCPROT1  = KCPROT_CLR;

  /************************************************/
  /* PLL                                          */
  /* - OPBT11.CKDIVMD = 11b is needed.            */
  /************************************************/

  /* 1.Confirm that the MainOSC is stable (MOSCS.MOSCSTAB = 1). */
  /* (Checked) **/

  /* 3.Start the PLL (PLLE.PLLENTRG = 1). */
  CLKKCPROT1  = KCPROT_SET;
  PLLE        = 0x00000001UL;
  CLKKCPROT1  = KCPROT_CLR;

  /* 4.Confirm that the PLL has been started      */
  /* (PLLS.PLLCLKSTAB = 1 and PLLS.PLLCLKEN = 1). */
  while ( (PLLS & 0x00000003UL) != 0x00000003UL )
  {
  }

  /* PLL stops operation in stand-by mode(PLLSTPM.PLLSTPMSK = 0) */
  CLKKCPROT1  = KCPROT_SET;
  PLLSTPM     = 0x00000000UL;
  CLKKCPROT1  = KCPROT_CLR;

  /* Select a source clock(CKS_CLEANC.CPUCLKSCSID = 0). */
  CLKKCPROT1  = KCPROT_SET;
  
  /* Selected Clock source ID=0:CLK_PLLO */
  /* (This setting dependencies Option Bytes. CKDIVMD = 11B) */
  CKS_CLEANC   = 0x00000000UL;
  CLKKCPROT1  = KCPROT_CLR;

  /* Confirm completion of selection(CKS_CLEANS.CPUCLKSACT = 1). */
  while ( (CKS_CLEANS & 0x00000001UL) != 0x00000000UL )
  {
  }

  /************************************************/
  /* As a result, FlexRay clocks are following.   */
  /* - Bus clock    : CLK_HBUS(100[MHz])          */
  /* - Sample clock : CLK_HSB(80[MHz])            */
  /************************************************/

}

/*******************************************************************************
 * Initialization of Timer                                                    **
 ******************************************************************************/

/*******************************************************************************
 * Initialization of variables used in interrupt functions                    **
 ******************************************************************************/
void IH_Init(void)
{
  /* Setting of interrupt registers: INTFLXA0TIM0 and INTFLXA0TIM2 only */
  /* Set Interrupt Priority and Interrupt Vector Method Select */
  FR_EIC[724] |= 0x004FU; /* INTFLXA0TIM0 */
  FR_EIC[726] |= 0x004FU; /* INTFLXA0TIM2 */

  /* Set Interrupt Mask */
  FR_EIC[724] &= 0xFF7AU; /* INTFLXA0TIM0 */
  FR_EIC[726] &= 0xFF7AU; /* INTFLXA0TIM2 */

  /* Select interrupt source for FLXA1 */
  FLXA1INTNOSEL0 = 0x155555;

  /* Set Interrupt Priority and Interrupt Vector Method Select */
  FR_EIC[921] |= 0x004FU; /* INTFLXA1TIM0 */
  FR_EIC[923] |= 0x004FU; /* INTFLXA1TIM2 */

  /* Set Interrupt Mask */
  FR_EIC[921] &= 0xFF7AU; /* INTFLXA1TIM0 */
  FR_EIC[923] &= 0xFF7AU; /* INTFLXA1TIM2 */
}

void WaitWakeup(void)
{
  volatile uint32 GulDelayCounter;
  GulDelayCounter = FR_59_RENESAS_ZERO;
  while (APP_FR_WAIT_WAKEUP > GulDelayCounter)
  {
    GulDelayCounter++;
  }
}

/*******************************************************************************
**                    Support post build variant: MCU Reset                   **
*******************************************************************************/
void Mcu_Reset(void)
{
  /* Reset Controller KeyCode Protection */
  #define MCU_RST_DISABLE_REG_PROTECT_VALUE     (uint32)0xA5A5A501UL
  #define MCU_RST_ENABLE_REG_PROTECT_VALUE      (uint32)0xA5A5A500UL
  #define MCU_SW_RESET_ENABLE_VALUE             (uint32)0x00000001UL

  #define RESKCPROT0                            (*((volatile uint32*)(0xFF980F00UL)))
  #define SWARESA                               (*((volatile uint32*)(0xFF988410UL)))

  RESKCPROT0 = MCU_RST_DISABLE_REG_PROTECT_VALUE;

  SWARESA = MCU_SW_RESET_ENABLE_VALUE;

  RESKCPROT0 = MCU_RST_ENABLE_REG_PROTECT_VALUE;
}

/*******************************************************************************
 * FlexRay Timer0 interrupt signal Controller 0                                *
 ******************************************************************************/

_INTERRUPT_ void INTFLX0TIM0(void)
{
  uint8 LucControllerIdx;
  uint8 LucLSduLength;
  uint16 LusLPduIdx;
  uint16 LusLPduIdx1;
  uint16 LusFrameId;
  Fr_ChannelType LddChnlIdx;
  uint8 LucCycleRepetition;
  uint8 LucCycleOffset;
  uint32 LucPayloadLength;
  Std_ReturnType LucReturnValue;
  uint16 LusHeaderCRC;
  uint16 LusFr_ChannelAStatus;
  uint16 LusFr_ChannelBStatus;
  uint8 LucAbsTimerIdx;
  boolean LblFr_IRQStatus;
  Fr_TxLPduStatusType LddTxLPduStatusPtr;
  Fr_SlotAssignmentType LddSlotAssignmentPtr;

  uint8 LucRxLSduPtr1[FR_59_RENESAS_LSDULENGHT];
  Fr_RxLPduStatusType LddRxLPduStatusPtr1;
  uint8 LucRxLSduLengthPtr1;
  uint8 LucCount1 ;
  uint8 LucFr_NmVector = 0;

  LucControllerIdx = FR_59_RENESAS_ZERO;
  LddTxLPduStatusPtr = FR_NOT_TRANSMITTED;
  LucLSduLength = FR_59_RENESAS_ZERO;
  LusLPduIdx = FR_59_RENESAS_ZERO;
  LusLPduIdx1 = FR_59_RENESAS_ELEVEN;
  LusFrameId = FR_59_RENESAS_ELEVEN;
  LddChnlIdx = FR_CHANNEL_B;
  LucCycleOffset = FR_59_RENESAS_ZERO;
  LucCycleRepetition = FR_59_RENESAS_ONE;
  LucAbsTimerIdx = FR_59_RENESAS_ZERO;
  LucReturnValue = E_NOT_OK;
  LucPayloadLength = 254;
  LusHeaderCRC = 0x25a;
  LddRxLPduStatusPtr1 = FR_NOT_RECEIVED;
  LblFr_IRQStatus = FALSE;
  LucRxLSduLengthPtr1 = FR_59_RENESAS_LSDULENGHT;
  LucCount1 = FR_59_RENESAS_ZERO;

  if (FR_59_RENESAS_ZERO == Fr_GucInvoked[0])
  {
    LusLPduIdx = FR_59_RENESAS_EIGHT;
    /*
     * Invoke Fr_PrepareLPdu to reconfigure buffer to transmit the frame of
     * index 1
     */
    #if(FR_59_RENESAS_PREPARE_LPDU == STD_ON)
    LucReturnValue = Fr_59_Renesas_PrepareLPdu(LucControllerIdx, LusLPduIdx);
    if (E_OK == LucReturnValue)
    #endif
    {
      LucLSduLength = 254;
      /* Invoke Fr_TransmitTxLPdu to transmit the frame of index 4 */
      LucReturnValue = Fr_59_Renesas_TransmitTxLPdu(LucControllerIdx,
                       LusLPduIdx,&LaaAppArray[0], LucLSduLength, &LddSlotAssignmentPtr);
      if (E_OK == LucReturnValue)
      {
        Fr_GblInvoked = FR_59_RENESAS_TRUE;
        Fr_GucInvoked[0]++;
      }
      else
      {
        Fr_GblInvoked = FR_59_RENESAS_FALSE;
      }
      /* Invoke the API Fr_59_Renesas_GetChannelStatus()  */
      do
      {
        LucReturnValue = Fr_59_Renesas_GetChannelStatus(LucControllerIdx, &LusFr_ChannelAStatus, &LusFr_ChannelBStatus);
      }
      while(E_OK != LucReturnValue || 0x1 != LusFr_ChannelAStatus || 0x1 != LusFr_ChannelBStatus);
      /* Invoke the API Fr_59_Renesas_GetAbsoluteTimerIRQStatus()  */
      do
      {
        LucReturnValue = Fr_59_Renesas_GetAbsoluteTimerIRQStatus(LucControllerIdx, LucAbsTimerIdx, &LblFr_IRQStatus);
      }
      while(FR_59_RENESAS_TRUE != LblFr_IRQStatus);
    }
    #if(FR_59_RENESAS_PREPARE_LPDU == STD_ON)
    else
    {
      Fr_GblInvoked = FR_59_RENESAS_FALSE;
    }
    #endif
    /* Invoke the API Fr_59_Renesas_CheckTxLPduStatus()  */
    do
    {
      LucReturnValue = Fr_59_Renesas_CheckTxLPduStatus(LucControllerIdx, LusLPduIdx, &LddTxLPduStatusPtr,
                       &LddSlotAssignmentPtr);
    }
    while(FR_TRANSMITTED != LddTxLPduStatusPtr);
  }

  else if (FR_59_RENESAS_ONE == Fr_GucInvoked[0])
  {
    LusLPduIdx = FR_59_RENESAS_SEVEN;
    /* Invoke Fr_ReceiveRxLPdu to receive the frame transmitted from Node 2 */
    LucReturnValue = Fr_59_Renesas_ReceiveRxLPdu(LucControllerIdx, LusLPduIdx,
                LucRxLSduPtr1, &LddRxLPduStatusPtr1, &LucRxLSduLengthPtr1, &LddSlotAssignmentPtr);
    if ((E_OK == LucReturnValue) && (FR_RECEIVED == LddRxLPduStatusPtr1) &&
                              (FR_59_RENESAS_LSDULENGHT == LucRxLSduLengthPtr1))
    {
      for (LucCount1 = FR_59_RENESAS_ZERO; LucCount1 < FR_59_RENESAS_EIGHT;
                                                                    LucCount1++)
      {
        if ((LucRxLSduPtr1[LucCount1]) == LaaAppArray_2[LucCount1])
        {
          Fr_GucInvoked[0]++;
        }
      }
      if (FR_59_RENESAS_NINE == Fr_GucInvoked[0])
      {
        Fr_GblInvoked = FR_59_RENESAS_TRUE;
		    Fr_GucInvoked[0]++;
      }
      else
      {
        Fr_GblInvoked = FR_59_RENESAS_FALSE;
      }
    }
    if(FR_59_RENESAS_TEN == Fr_GucInvoked[0])
    {
      /* Invoke the API Fr_59_Renesas_CancelAbsoluteTimer()  */
      LucReturnValue = Fr_59_Renesas_CancelAbsoluteTimer(LucControllerIdx, LucAbsTimerIdx);
	    if (E_OK == LucReturnValue)
      {
        Fr_GblInvoked = FR_59_RENESAS_TRUE;
      }
      else
      {
        Fr_GblInvoked = FR_59_RENESAS_FALSE;
      }
      /* Invoke the API Fr_59_Renesas_AckAbsoluteTimerIRQ()  */
      LucReturnValue = Fr_59_Renesas_AckAbsoluteTimerIRQ(LucControllerIdx, LucAbsTimerIdx);
        if (E_OK == LucReturnValue)
      {
        Fr_GblInvoked = FR_59_RENESAS_TRUE;
      }
      else
      {
        Fr_GblInvoked = FR_59_RENESAS_FALSE;
      }
      /* Invoke the API Fr_59_Renesas_CancelTxLPdu()  */
      LucReturnValue = Fr_59_Renesas_CancelTxLPdu(LucControllerIdx, LusLPduIdx);
        if (E_OK == LucReturnValue)
      {
        Fr_GblInvoked = FR_59_RENESAS_TRUE;
      }
      else
      {
        Fr_GblInvoked = FR_59_RENESAS_FALSE;
      }
      }
  }

  else if (FR_59_RENESAS_TEN == Fr_GucInvoked[0])
  {
    /* Invoke the API Fr_59_Renesas_GetNmVector()  */
    do
    {
      Fr_59_Renesas_GetNmVector(LucControllerIdx, &LucFr_NmVector);
    }
    while(LucFr_NmVector != 0);
    /* Invoke the API Fr_59_Renesas_ReconfigLPdu()  */
    LucReturnValue = Fr_59_Renesas_ReconfigLPdu(LucControllerIdx, LusLPduIdx1, LusFrameId, LddChnlIdx, LucCycleRepetition,
                                                                        LucCycleOffset, LucPayloadLength, LusHeaderCRC);
      if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked = FR_59_RENESAS_TRUE;
            Fr_GucInvoked[0]++;
    }
    else
    {
        Fr_GblInvoked = FR_59_RENESAS_FALSE;
    }
  }

  else if (FR_59_RENESAS_ELEVEN == Fr_GucInvoked[0])
  {
    /* Invoke the API Fr_59_Renesas_ReceiveQueueTable()  */
    LucReturnValue = Fr_59_Renesas_ReceiveQueueTable(LucControllerIdx, &Fr_59_Gstoutput_table_core0[0]);
      if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked = FR_59_RENESAS_TRUE;
          Fr_GucInvoked[0]++;
    }
    else
    {
        Fr_GblInvoked = FR_59_RENESAS_FALSE;
    }
    /* Invoke the API Fr_59_Renesas_UserOutputTransferRequest()  */
    LucReturnValue = Fr_59_Renesas_UserOutputTransferRequest(LucControllerIdx, &Fr_59_Gstoutput_table_core0[1]);
      if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked = FR_59_RENESAS_TRUE;
            Fr_GucInvoked[0]++;
    }
    else
    {
        Fr_GblInvoked = FR_59_RENESAS_FALSE;
    }
    /* Invoke the API Fr_59_Renesas_UserInputTransferRequest()  */
    LucReturnValue = Fr_59_Renesas_UserInputTransferRequest(LucControllerIdx, &Fr_59_Gstinput_table_core0[0]);
      if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked = FR_59_RENESAS_TRUE;
            Fr_GucInvoked[0]++;
    }
    else
    {
        Fr_GblInvoked = FR_59_RENESAS_FALSE;
    }
    /* Invoke the API Fr_59_Renesas_HaltInputQueue()  */
    LucReturnValue = Fr_59_Renesas_HaltInputQueue(LucControllerIdx, &Fr_59_Gstinput_table_core0[1]);
      if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked = FR_59_RENESAS_TRUE;
    }
  else
    {
        Fr_GblInvoked = FR_59_RENESAS_FALSE;
    }
  }

  else
  {
    Fr_GblInvoked = FR_59_RENESAS_FALSE;
  }
  FRSIR0 |= 0x00000100UL;
  FROS0  |= 0x00010000UL;
}

/*******************************************************************************
 * FlexRay Timer2 interrupt signal Controller 0                                *
 ******************************************************************************/
_INTERRUPT_ void INTFLX0TIM2(void)
{
}

/*******************************************************************************
 * FlexRay Timer0 interrupt signal Controller 1                                *
 ******************************************************************************/

_INTERRUPT_ void INTFLX1TIM0(void)
{
 uint8 LucControllerIdx;
  uint8 LucLSduLength;
  uint16 LusLPduIdx;
  uint16 LusLPduIdx1;
  uint16 LusFrameId;
  Fr_ChannelType LddChnlIdx;
  uint8 LucCycleRepetition;
  uint8 LucCycleOffset;
  uint32 LucPayloadLength;
  Std_ReturnType LucReturnValue;
  uint16 LusHeaderCRC;
  uint16 LusFr_ChannelAStatus;
  uint16 LusFr_ChannelBStatus;
  uint8 LucAbsTimerIdx;
  boolean LblFr_IRQStatus;
  Fr_TxLPduStatusType LddTxLPduStatusPtr;
  Fr_SlotAssignmentType LddSlotAssignmentPtr;

  uint8 LucRxLSduPtr1[FR_59_RENESAS_LSDULENGHT];
  Fr_RxLPduStatusType LddRxLPduStatusPtr1;
  uint8 LucRxLSduLengthPtr1;
  uint8 LucCount1 ;
  uint8 LucFr_NmVector = 0;

  LucControllerIdx = FR_59_RENESAS_ONE;
  LddTxLPduStatusPtr = FR_NOT_TRANSMITTED;
  LucLSduLength = FR_59_RENESAS_ZERO;
  LusLPduIdx = FR_59_RENESAS_ZERO;
  LusLPduIdx1 = FR_59_RENESAS_ELEVEN;
  LusFrameId = FR_59_RENESAS_ELEVEN;
  LddChnlIdx = FR_CHANNEL_B;
  LucCycleOffset = FR_59_RENESAS_ZERO;
  LucCycleRepetition = FR_59_RENESAS_ONE;
  LucAbsTimerIdx = FR_59_RENESAS_ZERO;
  LucReturnValue = E_NOT_OK;
  LucPayloadLength = 254;
  LusHeaderCRC = 0x25a;
  LddRxLPduStatusPtr1 = FR_NOT_RECEIVED;
  LblFr_IRQStatus = FALSE;
  LucRxLSduLengthPtr1 = FR_59_RENESAS_LSDULENGHT;
  LucCount1 = FR_59_RENESAS_ZERO;

    if (FR_59_RENESAS_ZERO == Fr_GucInvoked_1[1])
  {
    LusLPduIdx = FR_59_RENESAS_EIGHT;
    /*
     * Invoke Fr_PrepareLPdu to reconfigure buffer to transmit the frame of
     * index 1
     */
    #if(FR_59_RENESAS_PREPARE_LPDU == STD_ON)
    LucReturnValue = Fr_59_Renesas_PrepareLPdu(LucControllerIdx, LusLPduIdx);
    if (E_OK == LucReturnValue)
    #endif
    {
      LucLSduLength = 254;
      /* Invoke Fr_TransmitTxLPdu to transmit the frame of index 4 */
      LucReturnValue = Fr_59_Renesas_TransmitTxLPdu(LucControllerIdx,
                       LusLPduIdx,&LaaAppArray[0], LucLSduLength, &LddSlotAssignmentPtr);
      if (E_OK == LucReturnValue)
      {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
        Fr_GucInvoked_1[1]++;
      }
      else
      {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
      }
      /* Invoke the API Fr_59_Renesas_GetChannelStatus()  */
      do
      {
        LucReturnValue = Fr_59_Renesas_GetChannelStatus(LucControllerIdx, &LusFr_ChannelAStatus, &LusFr_ChannelBStatus);
      }
      while(E_OK != LucReturnValue || 0x1 != LusFr_ChannelAStatus || 0x1 != LusFr_ChannelBStatus);
      /* Invoke the API Fr_59_Renesas_GetAbsoluteTimerIRQStatus()  */
      do
      {
        LucReturnValue = Fr_59_Renesas_GetAbsoluteTimerIRQStatus(LucControllerIdx, LucAbsTimerIdx, &LblFr_IRQStatus);
      }
      while(FR_59_RENESAS_TRUE != LblFr_IRQStatus);
    }
    #if(FR_59_RENESAS_PREPARE_LPDU == STD_ON)
    else
    {
      Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
    }
    #endif
    /* Invoke the API Fr_59_Renesas_CheckTxLPduStatus()  */
    do
    {
      LucReturnValue = Fr_59_Renesas_CheckTxLPduStatus(LucControllerIdx, LusLPduIdx, &LddTxLPduStatusPtr,
                       &LddSlotAssignmentPtr);
    }
    while(FR_TRANSMITTED != LddTxLPduStatusPtr);
  }

  else if (FR_59_RENESAS_ONE == Fr_GucInvoked_1[1])
  {
    LusLPduIdx = FR_59_RENESAS_SEVEN;
    /* Invoke Fr_ReceiveRxLPdu to receive the frame transmitted from Node 2 */
    LucReturnValue = Fr_59_Renesas_ReceiveRxLPdu(LucControllerIdx, LusLPduIdx,
                LucRxLSduPtr1, &LddRxLPduStatusPtr1, &LucRxLSduLengthPtr1, &LddSlotAssignmentPtr);
    if ((E_OK == LucReturnValue) && (FR_RECEIVED == LddRxLPduStatusPtr1) &&
                              (FR_59_RENESAS_LSDULENGHT == LucRxLSduLengthPtr1))
    {
      for (LucCount1 = FR_59_RENESAS_ZERO; LucCount1 < FR_59_RENESAS_EIGHT;
                                                                    LucCount1++)
      {
        if ((LucRxLSduPtr1[LucCount1]) == LaaAppArray_2[LucCount1])
        {
          Fr_GucInvoked_1[1]++;
        }
      }
      if (FR_59_RENESAS_NINE == Fr_GucInvoked_1[1])
      {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
		    Fr_GucInvoked_1[1]++;
      }
      else
      {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
      }
    }
    if(FR_59_RENESAS_TEN == Fr_GucInvoked_1[1])
    {
      /* Invoke the API Fr_59_Renesas_CancelAbsoluteTimer()  */
      LucReturnValue = Fr_59_Renesas_CancelAbsoluteTimer(LucControllerIdx, LucAbsTimerIdx);
	    if (E_OK == LucReturnValue)
      {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
      }
      else
      {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
      }
      /* Invoke the API Fr_59_Renesas_AckAbsoluteTimerIRQ()  */
      LucReturnValue = Fr_59_Renesas_AckAbsoluteTimerIRQ(LucControllerIdx, LucAbsTimerIdx);
	    if (E_OK == LucReturnValue)
      {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
      }
      else
      {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
      }
      /* Invoke the API Fr_59_Renesas_CancelTxLPdu()  */
      LucReturnValue = Fr_59_Renesas_CancelTxLPdu(LucControllerIdx, LusLPduIdx);
	    if (E_OK == LucReturnValue)
      {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
      }
      else
      {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
      }
	  }
  }

  else if (FR_59_RENESAS_TEN == Fr_GucInvoked_1[1])
  {
    /* Invoke the API Fr_59_Renesas_GetNmVector()  */
    do
    {
      Fr_59_Renesas_GetNmVector(LucControllerIdx, &LucFr_NmVector);
    }
    while(LucFr_NmVector != 0);
    /* Invoke the API Fr_59_Renesas_ReconfigLPdu()  */
    LucReturnValue = Fr_59_Renesas_ReconfigLPdu(LucControllerIdx, LusLPduIdx1, LusFrameId, LddChnlIdx, LucCycleRepetition,
                                                                        LucCycleOffset, LucPayloadLength, LusHeaderCRC);
	  if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
		    Fr_GucInvoked_1[1]++;
    }
    else
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
    }
  }

  else if (FR_59_RENESAS_ELEVEN == Fr_GucInvoked_1[1])
  {
    /* Invoke the API Fr_59_Renesas_ReceiveQueueTable()  */
    LucReturnValue = Fr_59_Renesas_ReceiveQueueTable(LucControllerIdx, &Fr_59_Gstoutput_table_core1[0]);
	  if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
		  Fr_GucInvoked_1[1]++;
    }
    else
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
    }
    /* Invoke the API Fr_59_Renesas_UserOutputTransferRequest()  */
    LucReturnValue = Fr_59_Renesas_UserOutputTransferRequest(LucControllerIdx, &Fr_59_Gstoutput_table_core1[1]);
	  if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
		    Fr_GucInvoked_1[1]++;
    }
    else
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
    }
    /* Invoke the API Fr_59_Renesas_UserInputTransferRequest()  */
    LucReturnValue = Fr_59_Renesas_UserInputTransferRequest(LucControllerIdx, &Fr_59_Gstinput_table_core1[0]);
	  if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
		    Fr_GucInvoked_1[1]++;
    }
    else
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
    }
    /* Invoke the API Fr_59_Renesas_HaltInputQueue()  */
    LucReturnValue = Fr_59_Renesas_HaltInputQueue(LucControllerIdx, &Fr_59_Gstinput_table_core1[1]);
    if (E_OK == LucReturnValue)
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_TRUE;
    }
    else
    {
        Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
    }
  }

  else
  {
    Fr_GblInvoked_1 = FR_59_RENESAS_FALSE;
  }

  FRSIR1 |= 0x00000100UL;
  FROS1  |= 0x00010000UL;

}

/*******************************************************************************
 * FlexRay Timer2 interrupt signal Controller 1                                *
 ******************************************************************************/
_INTERRUPT_ void INTFLX1TIM2(void)
{
}

/*******************************************************************************
                          End of file
*******************************************************************************/
