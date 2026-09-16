/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = App_SPI_U2B24-E_Sample.c                                                                            */
/*====================================================================================================================*/
/*                                                COPYRIGHT                                                           */
/*====================================================================================================================*/
/* ((c) 2025 Renesas Electronics Corporation. All rights reserved.                                                    */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains sample application for SPI Driver Component                                                     */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                                                                                    */
/* Unless otherwise agreed upon in writing between your company and Renesas Electronics Corporation the following     */
/* shall apply!                                                                                                       */
/*                                                                                                                    */
/* Warranty Disclaimer                                                                                                */
/*                                                                                                                    */
/* There is no warranty of any kind whatsoever granted by Renesas. Any warranty is expressly disclaimed and excluded  */
/* by Renesas, either expressed or implied, including but not limited to those for non-infringement of intellectual   */
/* property, merchantability and/or fitness for the particular purpose.                                               */
/*                                                                                                                    */
/*                                                                                                                    */
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s) and/or */
/* the Application.                                                                                                   */
/*                                                                                                                    */
/* Each User is solely responsible for determining the appropriateness of using the Product(s) and assumes all risks  */
/* associated with its exercise of rights under this Agreement, including, but not limited to the risks and costs of  */
/* program errors, compliance with applicable laws, damage to or loss of data, programs or equipment, and             */
/* unavailability or interruption of operations.                                                                      */
/*                                                                                                                    */
/* Limitation of Liability                                                                                            */
/*                                                                                                                    */
/* In no event shall Renesas be liable to the User for any incidental, consequential, indirect, or punitive damage    */
/* (including but not limited to lost profits) regardless of whether such liability is based on breach of contract,   */
/* tort, strict liability, breach of warranties, failure of essential purpose or otherwise and even if advised of the */
/* possibility of such damages. Renesas shall not be liable for any services or products provided by third party      */
/* vendors, developers or consultants identified or referred to the User by Renesas in connection with the Product(s) */
/* and/or the Application.                                                                                            */
/*                                                                                                                    */
/*====================================================================================================================*/
/* Environment:                                                                                                       */
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                      Revision Control History                                                                      **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                       Add setting relay porrt_pin for sample app
 *                       Update Guard_Enable_PE to un-protect all register protection
 * 2.3.0:  31/01/2025  : Update SW-VERSION for Ver22.01.00 U2Cx Final release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 * 2.0.3:  14/04/2024  : Update stub of PORT, GPT, Guard Protect to support for post build variant
 *         19/03/2024  : Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "App_Spi_Device_Sample.h"

/***********************************************************************************************************************
**                                                Global Symbols                                                      **
***********************************************************************************************************************/
/* Array for Intr Reg information */
CONST(uint32, SPI_APPL_CONST) Spi_GaaIntCntlRegsInfo[] =
{
  /* HW Unit: DMA */
  70UL,  /* EIC70  (INTSDMAC0CH0)  */       /*   Index 0    */
  71UL,  /* EIC71  (INTSDMAC0CH1)  */       /*   Index 1    */
  72UL,  /* EIC72  (INTSDMAC0CH2)  */       /*   Index 2    */
  73UL,  /* EIC73  (INTSDMAC0CH3)  */       /*   Index 3    */
  74UL,  /* EIC74  (INTSDMAC0CH4)  */       /*   Index 4    */
  75UL,  /* EIC75  (INTSDMAC0CH5)  */       /*   Index 5    */
  76UL,  /* EIC76  (INTSDMAC0CH6)  */       /*   Index 6    */
  77UL,  /* EIC77  (INTSDMAC0CH7)  */       /*   Index 7    */
  78UL,  /* EIC78  (INTSDMAC0CH8)  */       /*   Index 8    */
  79UL,  /* EIC79  (INTSDMAC0CH9)  */       /*   Index 9    */
  80UL,  /* EIC80  (INTSDMAC0CH10) */       /*   Index 10   */
  81UL,  /* EIC81  (INTSDMAC0CH11) */       /*   Index 11   */
  82UL,  /* EIC82  (INTSDMAC0CH12) */       /*   Index 12   */
  83UL,  /* EIC83  (INTSDMAC0CH13) */       /*   Index 13   */
  84UL,  /* EIC84  (INTSDMAC0CH14) */       /*   Index 14   */
  85UL,  /* EIC85  (INTSDMAC0CH15) */       /*   Index 15   */
  825UL, /* EIC825 (INTSDMAC1CH0)  */       /*   Index 16   */
  826UL, /* EIC826 (INTSDMAC1CH1)  */       /*   Index 17   */
  827UL, /* EIC827 (INTSDMAC1CH2)  */       /*   Index 18   */
  828UL, /* EIC828 (INTSDMAC1CH3)  */       /*   Index 19   */
  829UL, /* EIC829 (INTSDMAC1CH4)  */       /*   Index 20   */
  830UL, /* EIC830 (INTSDMAC1CH5)  */       /*   Index 21   */
  831UL, /* EIC831 (INTSDMAC1CH6)  */       /*   Index 22   */
  832UL, /* EIC832 (INTSDMAC1CH7)  */       /*   Index 23   */
  833UL, /* EIC833 (INTSDMAC1CH8)  */       /*   Index 24   */
  834UL, /* EIC834 (INTSDMAC1CH9)  */       /*   Index 25   */
  835UL, /* EIC835 (INTSDMAC1CH10) */       /*   Index 26   */
  836UL, /* EIC836 (INTSDMAC1CH11) */       /*   Index 27   */
  837UL, /* EIC837 (INTSDMAC1CH12) */       /*   Index 28   */
  838UL, /* EIC838 (INTSDMAC1CH13) */       /*   Index 29   */
  839UL, /* EIC839 (INTSDMAC1CH14) */       /*   Index 30   */
  840UL, /* EIC840 (INTSDMAC1CH15) */       /*   Index 31   */
  /* HW Unit: MSPI */
  564UL, /* EIC564 (INTMSPI0TX0)   */       /*   Index 32   */
  565UL, /* EIC565 (INTMSPI0TX1)   */       /*   Index 33   */
  566UL, /* EIC566 (INTMSPI0TX2)   */       /*   Index 34   */
  567UL, /* EIC567 (INTMSPI0RX0)   */       /*   Index 35   */
  568UL, /* EIC568 (INTMSPI0RX1)   */       /*   Index 36   */
  569UL, /* EIC569 (INTMSPI0RX2)   */       /*   Index 37   */
  570UL, /* EIC570 (INTMSPI1TX0)   */       /*   Index 38   */
  571UL, /* EIC571 (INTMSPI1TX1)   */       /*   Index 39   */
  572UL, /* EIC572 (INTMSPI1TX2)   */       /*   Index 40   */
  573UL, /* EIC573 (INTMSPI1RX0)   */       /*   Index 41   */
  574UL, /* EIC574 (INTMSPI1RX1)   */       /*   Index 42   */
  575UL, /* EIC575 (INTMSPI1RX2)   */       /*   Index 43   */
  576UL, /* EIC576 (INTMSPI0TX)    */       /*   Index 32   */
  577UL, /* EIC577 (INTMSPI0RX)    */       /*   Index 33   */
  578UL, /* EIC578 (INTMSPI0FE)    */       /*   Index 34   */
  579UL, /* EIC579 (INTMSPI0ERR)   */       /*   Index 35   */
  580UL, /* EIC580 (INTMSPI1TX)    */       /*   Index 36   */
  581UL, /* EIC581 (INTMSPI1RX)    */       /*   Index 37   */
  582UL, /* EIC582 (INTMSPI1FE)    */       /*   Index 38   */
  583UL, /* EIC583 (INTMSPI1ERR)   */       /*   Index 39   */
  584UL, /* EIC584 (INTMSPI2TX)    */       /*   Index 40   */
  585UL, /* EIC585 (INTMSPI2RX)    */       /*   Index 41   */
  586UL, /* EIC586 (INTMSPI2FE)    */       /*   Index 42   */
  587UL, /* EIC587 (INTMSPI2ERR)   */       /*   Index 43   */
  588UL, /* EIC588 (INTMSPI3TX)    */       /*   Index 44   */
  589UL, /* EIC589 (INTMSPI3RX)    */       /*   Index 45   */
  590UL, /* EIC590 (INTMSPI3FE)    */       /*   Index 46   */
  591UL, /* EIC591 (INTMSPI3ERR)   */       /*   Index 47   */
  592UL, /* EIC592 (INTMSPI4TX)    */       /*   Index 48   */
  593UL, /* EIC593 (INTMSPI4RX)    */       /*   Index 49   */
  594UL, /* EIC594 (INTMSPI4FE)    */       /*   Index 50   */
  595UL, /* EIC595 (INTMSPI4ERR)   */       /*   Index 51   */
  596UL, /* EIC596 (INTMSPI5TX)    */       /*   Index 52   */
  597UL, /* EIC597 (INTMSPI5RX)    */       /*   Index 53   */
  598UL, /* EIC598 (INTMSPI5FE)    */       /*   Index 54   */
  599UL, /* EIC599 (INTMSPI5ERR)   */       /*   Index 55   */
  600UL, /* EIC600 (INTMSPI6TX)    */       /*   Index 56   */
  601UL, /* EIC601 (INTMSPI6RX)    */       /*   Index 57   */
  602UL, /* EIC602 (INTMSPI6FE)    */       /*   Index 58   */
  603UL, /* EIC603 (INTMSPI6ERR)   */       /*   Index 59   */
  851UL, /* EIC851 (INTMSPI7TX)    */       /*   Index 60   */
  852UL, /* EIC852 (INTMSPI7RX)    */       /*   Index 61   */
  853UL, /* EIC853 (INTMSPI7FE)    */       /*   Index 62   */
  854UL, /* EIC854 (INTMSPI7ERR)   */       /*   Index 63   */
  855UL, /* EIC855 (INTMSPI8TX)    */       /*   Index 64   */
  856UL, /* EIC856 (INTMSPI8RX)    */       /*   Index 65   */
  857UL, /* EIC857 (INTMSPI8FE)    */       /*   Index 66   */
  858UL, /* EIC858 (INTMSPI8ERR)   */       /*   Index 67   */
  859UL, /* EIC859 (INTMSPI9TX)    */       /*   Index 68   */
  860UL, /* EIC860 (INTMSPI9RX)    */       /*   Index 69   */
  861UL, /* EIC861 (INTMSPI9FE)    */       /*   Index 70   */
  862UL  /* EIC862 (INTMSPI9ERR)   */       /*   Index 71   */
};

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
void Mcu_Init(void);
void Port_Init(void);
void Spi_PortSetting(uint8 PortGroup, uint8 PortPin, uint8 PIPC, uint8 LucAltMode);
void Clock_Init(void);
void Wdg_Init(void);
void Gpt_Init(void);
void Gpt_Start(void);
void Gpt_Stop(void);
void Gpt_Init_1(void);
void Spi_IvtInit(void);
void Spi_IvtInit_Variant(void);
void Guard_Init(void);

/***********************************************************************************************************************
**                                                Mcu Initialization                                                  **
***********************************************************************************************************************/
void Mcu_Init(void)
{
  Clock_Init();

  /* Setup module standby controllers */
  /* Disable protection for module standby registers */
  SPI_MSRKCPROT = SPI_KCPROT_SET;

  /* Enable MSPI modules */
  SPI_MSR_MSPI = SPI_MSR_ACTIVE;

  /* Enable TAUD module */
  SPI_MSR_TAUD = SPI_MSR_ACTIVE;

  /* Enable protection for module standby registers */
  SPI_MSRKCPROT = SPI_KCPROT_CLR;

  /* Enable DMA */
  SPI_DMA0OR = 0x0001;
  SPI_DMA1OR = 0x0001;

  /* Initialize EIC registers */
  Spi_IvtInit();

  /* Enable Interrupt */
  ENABLE_INTERRUPT();
}
/*******************************************************************************
**                      Port Initialization                                   **
*******************************************************************************/
void Port_Init(void)
{
  REG_PKCPROT = SPI_KCPROT_SET;
  REG_PWE = 0x0FFFFFFEUL;
  REG_PKCPROT = SPI_KCPROT_CLR;

  while(REG_PWE != 0x0FFFFFFEUL)
  {
    ASM_NOP();
  };

/* Setting relay board */
/* Enable port mode(DIO mode) */
SPI_PORT0[36].usPMC &=~ (BIT2);

/* Enable output mode */
SPI_PORT0[36].usPM  &=~ (BIT2);

/* Set low level for all pin */  // SA
SPI_PORT0[36].usP &=~ (BIT2);

// Ensure the relay board is ready
volatile  uint32 count;
while (count < 250000) 
{
  count++;
};

  /* Variant 1 and Single SA */
  /* <PORT_base>=0xFFD90000UL */
  /* MSPI0 */
  /*                                   | PMC PM PIPC | PFCEAE PFCAE PFCE PFCn | */
  /* P20_11   : AF7(IN/OUT): MSPI0SC   | 1   0  1    | 0      1     1    0    | */
  /* P20_14    : AF6(IN)    : MSPI0SI   | 1   1  0    | 0      0     0    0    | */
  /* P20_12   : AF10(OUT)  : MSPI0SO   | 1   0  1    | 1      0     0    1    | */
  /* P20_8    : AF12(OUT)  : MSPI0CSS0 | 1   0  0    | 1      0     1    1    | */

  Spi_PortSetting(20, 11, 1, ALT_INOUT7);
  Spi_PortSetting(20, 14,  0, ALT_IN6);
  Spi_PortSetting(20, 12, 1, ALT_OUT10);
  Spi_PortSetting(20, 8,  0, ALT_OUT12);

  /* <PORT_base>=0xFFD90000UL */
  /* MSPI1 */
  /*                                   | PMC PM PIPC | PFCEAE PFCAE PFCE PFCn | */
  /* P10_2   : AF2(IN/OUT) : MSPI1SC   | 1   1  1    | 0      0     0    1    | */
  /* P10_1   : AF8(IN)     : MSPI1SI   | 1   1  0    | 0      1     1    1    | */  
  /* P10_3   : AF2(OUT)    : MSPI1SO   | 1   0  1    | 0      0     0    1    | */ // P10_3 -> P10_4
  /* P10_4   : AF14(IN)    : MSPI1SSIZ | 1   1  0    | 1      1     0    1    | */ // P10_4 -> P01_7
  /* P10_4   : AF15(OUT)   : MSPI1SO   | 1   0  1    | 0      0     0    1    | */ // P10_3 -> P10_4
  /* P01_7   : AF12(IN)    : MSPI1SSIZ | 1   1  0    | 1      1     0    1    | */ // P10_4 -> P01_7

  Spi_PortSetting(10, 2, 1, ALT_INOUT2);
  Spi_PortSetting(10, 1, 0, ALT_IN8);
  //Spi_PortSetting(10, 3, 1, ALT_OUT2);
  //Spi_PortSetting(10, 4, 0, ALT_IN14);
  Spi_PortSetting(10, 4, 1, ALT_OUT15);
  Spi_PortSetting(01, 7, 0, ALT_IN12);

  /* Variant 2 */
  /* <PORT_base>=0xFFD90000UL */
  /* MSPI2 */
  /*                                      | PMC PM PIPC  | PFCAE PFCE  PFCn  PM  | */
  /* P15_3    : AF7 (IN/OUT) : MSPI2SC    |  1  *  1   |   0     1     1    *  | */
  /* P15_4    : AF6 (IN)     : MSPI2SI    |  1  1  0   |   0     1     1    1  | */
  /* P15_6    : AF13 (OUT)    : MSPI2SO   |  1  *  1   |   0     0     0    *  | */
  /* P15_2    : AF14 (OUT)    : MSPI2CSS0 |  1  0  0   |   0     1     0    0  | */

  Spi_PortSetting(15, 3, 1, ALT_INOUT7);
  Spi_PortSetting(15, 4, 0, ALT_IN6);
  Spi_PortSetting(15, 6, 1, ALT_OUT13);
  Spi_PortSetting(15, 2, 0, ALT_OUT15);

  /* MSPI3 */
  /*                                      | PMC PM PIPC  | PFCAE PFCE  PFCn  PM  | */
  /* P10_8    : AF2 (IN/OUT) : MSPI3SC    |  1  *  1   |   0     0     0    *  | */
  /* P10_7    : AF5 (IN)     : MSPI3SI    |  1  1  0   |   0     1     1    1  | */
  /* P10_6    : AF3 (OUT)    : MSPI3SO    |  1  *  1   |   0     0     0    *  | */
  /* P10_5    : AF12 (IN)     : MSPI3SSI   |  1  1  0   |   0     0     0    1  | */

  Spi_PortSetting(10, 8, 1, ALT_INOUT2);
  Spi_PortSetting(10, 7, 0, ALT_IN5);
  Spi_PortSetting(10, 6, 1, ALT_OUT3);
  Spi_PortSetting(10, 5, 0, ALT_IN12);

  REG_PKCPROT = SPI_KCPROT_SET;
  REG_PWE = 0x00000000UL;
  REG_PKCPROT = SPI_KCPROT_CLR;
}

void Spi_PortSetting(uint8 PortGroup, uint8 PortPin, uint8 PIPC, uint8 LucAltMode)
{
  REG_PODC(PortGroup) = 0x00UL;
 
  /* PMC setting */
  REG_PMC(PortGroup) |= (uint16) (1UL<<PortPin);
 
  /* PIPC */
  if (PIPC == 0)
  {
    REG_PIPC(PortGroup) &= (uint16)~ (1UL<<PortPin);
  }
  else
  {
    REG_PIPC(PortGroup) |= (uint16) (1UL<<PortPin);
  }
 
  /* PFCEAE */
  if ((LucAltMode & 0x10U) == 0)
  {
    REG_PFCEAE(PortGroup) &= (uint16)~ (1UL<<PortPin);
  }
  else
  {
    REG_PFCEAE(PortGroup) |= (uint16) (1UL<<PortPin);
  }
 
  /* PFCAE */
  if ((LucAltMode & 0x08U) == 0)
  {
    REG_PFCAE(PortGroup) &= (uint16)~ (1UL<<PortPin);
  }
  else
  {
    REG_PFCAE(PortGroup) |= (uint16) (1UL<<PortPin);
  }
 
  /* PFCE */
  if ((LucAltMode & 0x04U) == 0)
  {
    REG_PFCE(PortGroup) &= (uint16)~ (1UL<<PortPin);
  }
  else
  {
    REG_PFCE(PortGroup) |= (uint16) (1UL<<PortPin);
  }
 
  /* PFC */
  if ((LucAltMode & 0x02U) == 0)
  {
    REG_PFC(PortGroup) &= (uint16)~ (1UL<<PortPin);
  }
  else
  {
    REG_PFC(PortGroup) |= (uint16) (1UL<<PortPin);
  }
 
  /* PM */
  if ((LucAltMode & 0x01U) == 0)
  {
    REG_PM(PortGroup) &= (uint16)~ (1UL<<PortPin);
  }
  else
  {
    REG_PM(PortGroup) |= (uint16) (1UL<<PortPin);
  }
 
  /* Drive strength = 1*1 (very high) */
  REG_PDSC(PortGroup) |= (uint16) (1UL<<PortPin);
  REG_PUCC(PortGroup) |= (uint16) (1UL<<PortPin);
}

/***********************************************************************************************************************
**                                                Clock Initialization                                                **
***********************************************************************************************************************/
void Clock_Init(void)
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
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  HSOSCSTPM   = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /***********/
  /* MainOSC */
  /***********/

  /* 1.Confirm that the HSIntOSC is stable (HSOSCS.HSOSCSTAB = 1). */
  /* (Checked) **/

  /* 2.Confirm that the MainOSC is unstable (MOSCS.MOSCSTAB = 0). */
#if 0
  while ( (MOSCS & 0x00000002UL) != 0x00000000UL )
  {
  }
#else
  {
    volatile int w;
    for(w=0; w>1000000000; w++){};
  }
#endif

  /* 3.Start the MainOSC (MOSCE.MOSCENTRG = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCE       = 0x00000001UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* 4.Confirm that the MainOSC has been started (MOSCS.MOSCSTAB = 1). */
  while ( (MOSCS & 0x00000002UL) != 0x00000002UL )
  {
  }

  /* MainOSC stops operation in stand-by mode(MOSCSTPM.MOSCSTPMSK = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  MOSCSTPM    = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /*******/
  /* PLL */
  /*******/

  /* 1.Confirm that the MainOSC is stable (MOSCS.MOSCSTAB = 1). */
  /* (Checked) **/

  /* 2.Confirm that the PLL is unstable (PLLS.PLLCLKSTAB = 0). */
#if 0
  while ( (PLLS & 0x00000002UL) != 0x00000000UL )
  {
  }
#else
  {
    volatile int w;
    for(w=0; w>1000000000; w++){};
  }
#endif

  /* 3.Start the PLL (PLLE.PLLENTRG = 1). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  PLLE        = 0x00000001UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* 4.Confirm that the PLL has been started (PLLS.PLLCLKSTAB = 1). */
  while ( (PLLS & 0x00000002UL) != 0x00000002UL )
  {
  }

  /* PLL stops operation in stand-by mode(PLLSTPM.PLLSTPMSK = 0) */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  PLLSTPM     = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  CLKD_PLLC   = 0x00000001UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Select a source clock(CKSC_CPUC.CPUCLKSCSID = 0). */
  CLKKCPROT1  = ENABLE_WRITE_KEY_CODE;
  /* Selected Clock source ID=0:CLK_PLLO */
  /* (This setting dependencies Option Bytes. CKDIVMD = 11B) */
  CKSC_CPUC   = 0x00000000UL;
  CLKKCPROT1  = DISABLE_WRITE_KEY_CODE;

  /* Confirm completion of selection(CKSC_CPUS.CPUCLKSACT = 1). */
  while ( (CKSC_CPUS & 0x00000001UL) != 0x00000000UL )
  {
  }
}

/***********************************************************************************************************************
**                                                Wdg Initialization                                                  **
***********************************************************************************************************************/
void Wdg_Init(void)
{
   /*  No Action Required  */
}

/***********************************************************************************************************************
                                                  Timer Initialization
***********************************************************************************************************************/
void Gpt_Init(void)
{
  /* Only TAUD0 channel 0 is used.                             */
  /* Timer mode is interval timer mode and interval is 10[us]. */
  /* PCLK = 80[MHz] is assumed.                                */
  SPI_TAUD0TT         = 0xFFFFU;          /* Stop all channels of TAUD0.      */
  SPI_TAUD0TPS        = 0x0001U;          /* Setting CK0 (PCLK/(2^1)->40MHz). */
  SPI_TAUD0CDR0       = (50U - 1U);       /* 50/40MHz -> 1.25us.              */
  SPI_TAUD0CMOR0      = 0x0000U;          /* CK0, SW trigger and interval.    */

  SPI_EIC_INTTAUD0I0  = 0x004FU;          /* Enable INT(Table reference).     */
}

void Gpt_Start(void)
{
  SPI_TAUD0TS         = 0x0001U;          /* Start.                           */
}

void Gpt_Stop(void)
{
  SPI_TAUD0TT         = 0xFFFFU;          /* Stop all channels of TAUD0.      */
}

void Gpt_Init_1(void)
{
  /*
   * Timer count has to be loaded based on the system requirement. The value
   * provided here is just for reference and may not be suitable for
   * production purposes.
   */

  /* Only TAUD2 channel 0 is used.                            */
  /* Timer mode is interval timer mode and interval is 1[ms]. */
  /* PCLK = 80[MHz] is assumed.                               */
  SPI_TAUD2TT         = 0xFFFFU;          /* Stop all channels of TAUD2.      */
  SPI_TAUD2TPS        = 0x0001U;          /* Setting CK0 (PCLK/(2^1)->40MHz). */
  SPI_TAUD2CDR0       = (50U - 1U);       /* 50/40MHz -> 1.25us.              */
  SPI_TAUD2CMOR0      = 0x0000U;          /* CK0, SW trigger and interval.    */

  SPI_EIC_INTTAUD2I0  = 0x004FU;          /* Enable INT(Table reference).     */

  SPI_TAUD2TS         = 0x0001U;          /* Start.                           */
}

/***********************************************************************************************************************
**                                                Interrupt Initialization                                            **
***********************************************************************************************************************/
void Spi_IvtInit(void)
{
  uint32 LulIndex;

  for (LulIndex = 0U;
    LulIndex < (sizeof(Spi_GaaIntCntlRegsInfo) / sizeof(uint32)); LulIndex++)
  {
    SPI_EIC2[Spi_GaaIntCntlRegsInfo[LulIndex]] =
      (uint16)(SPI_EIMK | SPI_EITB | SPI_EIC_PRI);
  }

}

void Spi_IvtInit_Variant(void)
{
  uint32 LulIndex;

  for (LulIndex = 0U;
    LulIndex < (sizeof(Spi_GaaIntCntlRegsInfo) / sizeof(uint32)); LulIndex++)
  {
    SPI_EIC2[Spi_GaaIntCntlRegsInfo[LulIndex]] =
      (uint16)(SPI_EIMK | SPI_EITB | SPI_EIC_PRI);
  }
#if defined(SPI_USE_MULTICORE)
  /* Interrupt bound to PE1 for MSPI1 Tx and Rx when testing multi-core */
  SPI_EIBD2[576] |= SPI_EIBD_PE1;
  SPI_EIBD2[577] |= SPI_EIBD_PE1;
  SPI_EIBD2[580] |= SPI_EIBD_PE1;
  SPI_EIBD2[581] |= SPI_EIBD_PE1;
  SPI_EIBD2[584] |= SPI_EIBD_PE1;
  SPI_EIBD2[585] |= SPI_EIBD_PE1;
  SPI_EIBD2[344] |= SPI_EIBD_PE1;
#endif
}

/***********************************************************************************************************************
                                 Setup peripheral guard to enable Read/write by DMA
***********************************************************************************************************************/
void Guard_Init(void)
{
  PEGKCPROT0 = 0xA5A5A501UL;
  PEGKCPROT1 = 0xA5A5A501UL;
  PBGKCPROT30 = 0xA5A5A501UL;
  PBGKCPROT40 = 0xA5A5A501UL;

  /* Enable read/write Local RAM by DMA */
  PEGPROT0(0) |= 0x00000143UL;
  PEGPROT0(1) |= 0x00000143UL;
  PEGPROT0(2) |= 0x00000143UL;
  PEGPROT0(3) |= 0x00000143UL;
  PEGPROT0(4) |= 0x00000143UL;
  PEGPROT0(5) |= 0x00000143UL;
  PEGPROT0(6) |= 0x00000143UL;
  PEGPROT0(7) |= 0x00000143UL;

  PEGPROT1(0) |= 0x00000143UL;
  PEGPROT1(1) |= 0x00000143UL;
  PEGPROT1(2) |= 0x00000143UL;
  PEGPROT1(3) |= 0x00000143UL;
  PEGPROT1(4) |= 0x00000143UL;
  PEGPROT1(5) |= 0x00000143UL;
  PEGPROT1(6) |= 0x00000143UL;
  PEGPROT1(7) |= 0x00000143UL;

  /* Enable read/write MSPI RAM by DMA */
  PBG30PROT0(10) |= 0x00000143UL;
  PBG30PROT0(11) |= 0x00000143UL;
  PBG30PROT0(12) |= 0x00000143UL;
  PBG30PROT0(13) |= 0x00000143UL;
  PBG30PROT0(14) |= 0x00000143UL;

  PBG40PROT0(1) |= 0x00000143UL;
  PBG40PROT0(10) |= 0x00000143UL;
  PBG40PROT0(11) |= 0x00000143UL;
  PBG40PROT0(12) |= 0x00000143UL;
  PBG40PROT0(13) |= 0x00000143UL;
  PBG40PROT0(14) |= 0x00000143UL;
  PBG40PROT0(15) |= 0x00000143UL;
}


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
  (uint32) 0xFFF6D480UL, //PBGERRSLV8M0_base
  (uint32) 0xFF97A200UL, //PBGERRSLV8L0_base
  (uint32) 0xFFF6E080UL, //PBGERRSLV8UL0_base
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
  (uint32) 0xFFF6D400UL, //PBG8M0_base
  (uint32) 0xFF97A000UL, //PBG8L0_base
  (uint32) 0xFF97A100UL, //PBG8L1_base
  (uint32) 0xFFF6E000UL, //PBG8UL0_base
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
  for (int i =0; i<18;i++)
  {
  volatile uint32 *ptr;
  ptr = (volatile uint32 *)(RSLVXX_base[i] + (uint32)0x18UL);
  *ptr = (uint32)0xA5A5A501UL;
  }

  //Write PBG0
  for (int i =0; i<39;i++)
  {
    for (int ii =0; ii<16;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + ((uint32)ii * 0x8UL));
      *ptr |= 0x00000143UL;
    }
  }

  //Write PBG1
  for (int i =0; i<39;i++)
  {
    for (int ii =0; ii<16;ii++)
    {
      volatile uint32 *ptr;
      ptr = (volatile uint32 *)(PBGXX_base[i] + 0x4UL + ((uint32)ii * 0x8UL));
      *ptr |= 0xFFFFUL;
    }
  }

  //Disable write
  for (int i =0; i<18;i++)
  {
  volatile uint32 *ptr;
  ptr = (volatile uint32 *)(RSLVXX_base[i]+0x18UL);
  *ptr = 0xA5A5A500UL;
  }
  
}

/***********************************************************************************************************************
**                                                End of File                                                         **
***********************************************************************************************************************/

