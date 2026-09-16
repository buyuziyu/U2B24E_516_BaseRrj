/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2018, 2025 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : r_cg_cgc.h
* Version          : 1.8.0
* Device(s)        : R7F7025Bx
* Description      : This file contains macro define for clock setting according to Clocks tabs setting.
***********************************************************************************************************************/

#ifndef R_CGC_H
#define R_CGC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    PLL/SSCG/SSCG1 Enable Register (PLLE)
*/
/* PLL/SSCG/SSCG1 disable trigger (PLLDISTRG) */
#define _CGC_PLL_SSCG_SSCG1_STOP                       (0x00000002UL) /* Stop PLL/SSCG/SSCG1 */
/* PLL/SSCG/SSCG1 enable trigger (PLLENTRG) */
#define _CGC_PLL_SSCG_SSCG1_START                      (0x00000001UL) /* Start PLL/SSCG/SSCG1 */

/*
    PLL/SSCG/SSCG1 Status Register (PLLS)
*/
/* PLL/SSCG/SSCG1 enable and stable status (PLLCLKSTAB,PLLCLKEN) */
#define _CGC_PLL_SSCG_SSCG1_ACTIVE                     (0x00000003UL) /* PLL/SSCG/SSCG1 clock are enabled and stable */
/* PLL/SSCG/SSCG1 clock stable state (PLLCLKSTAB) */
#define _CGC_PLL_SSCG_SSCG1_STABLE                     (0x00000002UL) /* PLL/SSCG/SSCG1 clock are stable */
/* PLL/SSCG/SSCG1 clock enable state (PLLCLKEN) */
#define _CGC_PLL_SSCG_SSCG1_ENABLED                    (0x00000001UL) /* PLL/SSCG/SSCG1 clock are enabled */

/*
    PLL Stop Mask Register (PLLSTPM)
*/
/* PLL stop request mask (PLLSTPMSK) */
#define _CGC_PLL_REQUEST_STOP                          (0x00000000UL) /* PLL stops operation in standby mode */
#define _CGC_PLL_REQUEST_CONTINUE                      (0x00000001UL) /* PLL continues operation in standby mode */

/*
    SSCG/SSCG1 Control Register (SSCGC/SSCG1C)
*/
/* SSCG/SSCG1 control (SSMODE1) */
#define _CGC_SSCG_MODULATION_DISABLE                   (0x00000000UL) /* Modulation disabled */
#define _CGC_SSCG_MODULATION_ENABLE                    (0x00000200UL) /* Modulation enabled */
/* SSCG/SSCG1 modulation frequency control (SELMFREQ[4:0]) */
/* Set by PFD frequency 20MHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD20_595           (0x000000A8UL) /* 59.5 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD20_581           (0x000000B0UL) /* 58.1 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD20_500           (0x000000B8UL) /* 50.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD20_417           (0x000000C0UL) /* 41.7 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD20_397           (0x000000C8UL) /* 39.7 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD20_373           (0x000000D0UL) /* 37.3 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD20_333           (0x000000D8UL) /* 33.3 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD20_301           (0x000000E0UL) /* 30.1 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD20_250           (0x000000E8UL) /* 25.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD20_200           (0x000000F0UL) /* 20.0 KHz */
/* Set by PFD frequency 16MHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD16_606           (0x00000088UL) /* 60.6 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD16_556           (0x00000090UL) /* 55.6 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD16_526           (0x00000098UL) /* 52.6 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD16_500           (0x000000A0UL) /* 50.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD16_476           (0x000000A8UL) /* 47.6 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD16_465           (0x000000B0UL) /* 46.5 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD16_400           (0x000000B8UL) /* 40.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD16_333           (0x000000C0UL) /* 33.3 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD16_317           (0x000000C8UL) /* 31.7 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD16_299           (0x000000D0UL) /* 29.9 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD16_267           (0x000000D8UL) /* 26.7 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD16_241           (0x000000E0UL) /* 24.1 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD16_200           (0x000000E8UL) /* 20.0 KHz */
/* Set by PFD frequency 12.5MHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_625          (0x00000060UL) /* 62.5 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_558          (0x00000068UL) /* 55.8 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_538          (0x00000070UL) /* 53.8 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_520          (0x00000078UL) /* 52.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_504          (0x00000080UL) /* 50.4 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_473          (0x00000088UL) /* 47.3 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_434          (0x00000090UL) /* 43.4 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_411          (0x00000098UL) /* 41.1 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_390          (0x000000A0UL) /* 39.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_372          (0x000000A8UL) /* 37.2 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_363          (0x000000B0UL) /* 36.3 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_312          (0x000000B8UL) /* 31.2 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_260          (0x000000C0UL) /* 26.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_248          (0x000000C8UL) /* 24.8 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_233          (0x000000D0UL) /* 23.3 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD125_208          (0x000000D8UL) /* 20.8 KHz */
/* Set by PFD frequency 12MHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_600           (0x00000060UL) /* 60.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_536           (0x00000068UL) /* 53.6 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_517           (0x00000070UL) /* 51.7 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_500           (0x00000078UL) /* 50.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_484           (0x00000080UL) /* 48.4 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_455           (0x00000088UL) /* 45.5 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_417           (0x00000090UL) /* 41.7 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_395           (0x00000098UL) /* 39.5 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_375           (0x000000A0UL) /* 37.5 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_357           (0x000000A8UL) /* 35.7 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_349           (0x000000B0UL) /* 34.9 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_300           (0x000000B8UL) /* 30.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_250           (0x000000C0UL) /* 25.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_238           (0x000000C8UL) /* 23.8 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_224           (0x000000D0UL) /* 22.4 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD12_200           (0x000000D8UL) /* 20.0 KHz */
/* Set by PFD frequency 8MHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_588            (0x00000040UL) /* 58.8 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_526            (0x00000048UL) /* 52.6 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_500            (0x00000050UL) /* 50.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_455            (0x00000058UL) /* 45.5 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_400            (0x00000060UL) /* 40.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_357            (0x00000068UL) /* 35.7 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_345            (0x00000070UL) /* 34.5 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_333            (0x00000078UL) /* 33.3 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_323            (0x00000080UL) /* 32.3 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_303            (0x00000088UL) /* 30.3 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_278            (0x00000090UL) /* 27.8 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_263            (0x00000098UL) /* 26.3 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_250            (0x000000A0UL) /* 25.0 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_238            (0x000000A8UL) /* 23.8 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_233            (0x000000B0UL) /* 23.3 KHz */
#define _CGC_SSCG_MODULATION_FREQ_FPFD8_200            (0x000000B8UL) /* 20.0 KHz */
/* SSCG/SSCG1 modulation dithered range control (SELMPERCENT[2:0]) */
#define _CGC_SSCG_MODULATION_RANGE_MINUS1              (0x00000000UL) /* -1.0% */
#define _CGC_SSCG_MODULATION_RANGE_MINUS2              (0x00000001UL) /* -2.0% */
#define _CGC_SSCG_MODULATION_RANGE_MINUS3              (0x00000002UL) /* -3.0% */
#define _CGC_SSCG_MODULATION_RANGE_MINUS4              (0x00000003UL) /* -4.0% */
#define _CGC_SSCG_MODULATION_RANGE_MINUS5              (0x00000004UL) /* -5.0% */

/*
    Main OSC Enable Register (MOSCE)
*/
/* Main OSC disable trigger (MOSCDISTRG) */
#define _CGC_MAINOSC_STOP                              (0x00000002UL) /* Stop MainOSC */
/* Main OSC enable trigger (MOSCENTRG) */
#define _CGC_MAINOSC_START                             (0x00000001UL) /* Start MainOSC */

/*
    Main OSC Status Register (MOSCS)
*/
#define _CGC_MAINOSC_ACTIVE                            (0x00000003UL) /* Main OSC clock is enable and stable */
/* Main OSC stable state (MOSCSTAB) */
#define _CGC_MAINOSC_STABLE                            (0x00000002UL) /* Main OSC clock is stable */
/* Main OSC enable state (MOSCEN) */
#define _CGC_MAINOSC_ENABLED                           (0x00000001UL) /* Main OSC clock is enable */

/*
    Main OSC Stop Mask Register (MOSCSTPM)
*/
/* Main OSC stop request mask (MOSCSTPMSK) */
#define _CGC_MAINOSC_REQUEST_STOP                      (0x00000000UL) /* Main OSC stops operation in standby mode */
#define _CGC_MAINOSC_REQUEST_CONTINUE                  (0x00000001UL) /* Main OSC continues operation in standby mode */

/*
    HS IntOSC Status Register (HSOSCS)
*/
/* HS IntOSC clock stable state (HSOSCSTAB) */
#define _CGC_HSOSC_ACTIVE                              (0x00000002UL) /* HS IntOSC clock is stable */

/*
    HS IntOSC Stop Mask Register (HSOSCSTPM)
*/
/* HS IntOSC stop request mask (HSOSCSTPMSK) */
#define _CGC_HSOSC_REQUEST_STOP                        (0x00000000UL) /* HS IntOSC stops operation in standby mode */
#define _CGC_HSOSC_REQUEST_CONTINUE                    (0x00000001UL) /* HS IntOSC continues operation in standby 
                                                                         mode */

/*
    HSOSC Trimming Period Control Register (HSOSCTRMPRODC)
*/
/* Frequency measurement period (PROD[1:0]) */
#define _CGC_HSOSC_MEASUREMENT_PERIOD_50US             (0x00000002UL) /* Frequency measurement period 50us */
#define _CGC_HSOSC_MEASUREMENT_PERIOD_100US            (0x00000003UL) /* Frequency measurement period 100us */

/*
    HSOSC Trimming Function Enable Register (HSOSCTRMEN)
*/
/* Enable Trigger (ENTRG) */
#define _CGC_HSOSC_TRIMMING_NO_FUNCTION                (0x00000000UL) /* No Function */
#define _CGC_HSOSC_TRIMMING_START                      (0x00000001UL) /* Start */

/*
    HSOSC Frequency Trimming Status Register (HSOSCFRETRMS)
*/
/* Trimming Status (TRMST) */
#define _CGC_HSOSC_TRIMMING_COUNT_END                  (0x00000000UL) /* End of trimming count */
#define _CGC_HSOSC_TRIMMING_COUNT_DURING               (0x00000001UL) /* During trimming count */
#define _CGC_HSOSC_TRIMMING_STATUS_DEFAULT             (0xFFFFFFFEUL) /* Trimming status default value of bit TRMST */

/*
    CLK_SYS_CLEAN Selector Control Register (CKS_CLEANC)
*/
/* Clock source control (SYSCLKSCSID) */
#define _CGC_SYS_CLEAN_SOURCE_CLKIOSC                  (0x00000001UL) /* CLK_IOSC (default) */
#define _CGC_SYS_CLEAN_SOURCE_CLKPLLO                  (0x00000000UL) /* CLK_PLLO */

/*
    CLK_SYS_CLEAN Selector Status Register (CKS_CLEANS)
*/
/* Clock source status for CLK_SYS (SYSCLKSACT) */
#define _CGC_SYS_CLEAN_CLKPLLO_ACTIVE                  (0x00000000UL) /* CLK_PLLO selection is active */
#define _CGC_SYS_CLEAN_CLKIOSC_ACTIVE                  (0x00000001UL) /* CLK_IOSC selection is active */

/*
    CLK_SYS_SSCG Selector Control Register (CKS_SSCGC)
*/
/* Clock source control (SYSCLKSCSID) */
#define _CGC_SYS_SSCG_SOURCE_CLKIOSC                   (0x00000001UL) /* CLK_IOSC (default) */
#define _CGC_SYS_SSCG_SOURCE_CLKSSCGO                  (0x00000000UL) /* CLK_SSCGO */

/*
    CLK_SYS_SSCG Selector Status Register (CKS_SSCGS)
*/
/* Clock source status for CLK_SYS_SSCG (SYSCLKSACT) */
#define _CGC_SYS_SSCG_CLKIOSC_ACTIVE                   (0x00000001UL) /* CLK_IOSC selection is active */
#define _CGC_SYS_SSCG_CLKSSCGO_ACTIVE                  (0x00000000UL) /* CLK_SSCGO selection is active */

/*
    CLK_SYS_SSCG1 Selector Control Register (CKS_SSCG1C)
*/
/* Clock source control (SYSCLKSCSID) */
#define _CGC_SYS_SSCG1_SOURCE_CLKIOSC                  (0x00000001UL) /* CLK_IOSC (default) */
#define _CGC_SYS_SSCG1_SOURCE_CLKSSCG1O                (0x00000000UL) /* CLK_SSCG1O */

/*
    CLK_SYS_SSCG1 Selector Status Register (CKS_SSCG1S)
*/
/* Clock source status for CLK_SYS_SSCG1 (SYSCLKSACT) */
#define _CGC_SYS_SSCG1_CLKIOSC_ACTIVE                  (0x00000001UL) /* CLK_IOSC selection is active */
#define _CGC_SYS_SSCG1_CLKSSCG1O_ACTIVE                (0x00000000UL) /* CLK_SSCG1O selection is active */

/*
    CLK_PLLO Divider Control Register (CKD_PLLC)
*/
/* Clock divider control (PLLCLKDCSID[3:0]) */
#define _CGC_CLK_PLLO_DIVISION_NO                      (0x00000000UL) /* No division (default) */
#define _CGC_CLK_PLLO_DIVISION_1_16                    (0x00000001UL) /* Divided by 1/16 */
#define _CGC_CLK_PLLO_DIVISION_2_16                    (0x00000002UL) /* Divided by 2/16 */
#define _CGC_CLK_PLLO_DIVISION_3_16                    (0x00000003UL) /* Divided by 3/16 */
#define _CGC_CLK_PLLO_DIVISION_4_16                    (0x00000004UL) /* Divided by 4/16 */
#define _CGC_CLK_PLLO_DIVISION_5_16                    (0x00000005UL) /* Divided by 5/16 */
#define _CGC_CLK_PLLO_DIVISION_6_16                    (0x00000006UL) /* Divided by 6/16 */
#define _CGC_CLK_PLLO_DIVISION_7_16                    (0x00000007UL) /* Divided by 7/16 */
#define _CGC_CLK_PLLO_DIVISION_8_16                    (0x00000008UL) /* Divided by 8/16 */
#define _CGC_CLK_PLLO_DIVISION_9_16                    (0x00000009UL) /* Divided by 9/16 */
#define _CGC_CLK_PLLO_DIVISION_10_16                   (0x0000000AUL) /* Divided by 10/16 */
#define _CGC_CLK_PLLO_DIVISION_11_16                   (0x0000000BUL) /* Divided by 11/16 */
#define _CGC_CLK_PLLO_DIVISION_12_16                   (0x0000000CUL) /* Divided by 12/16 */
#define _CGC_CLK_PLLO_DIVISION_13_16                   (0x0000000DUL) /* Divided by 13/16 */
#define _CGC_CLK_PLLO_DIVISION_14_16                   (0x0000000EUL) /* Divided by 14/16 */
#define _CGC_CLK_PLLO_DIVISION_15_16                   (0x0000000FUL) /* Divided by 15/16 */

/*
    CLK_PLLO Divider Status Register (CKD_PLLS)
*/
/* Divider clock synchronized (PLLCLKDSYNC) */
#define _CGC_CLK_PLLO_DIVIDER_SYNC                     (0x00000002UL) /* Clock output corresponds to the 
                                                                         divisor setting in PLLCLKDCSID */

/*
    CLK_SSCGO Divider Control Register (CKD_SSCGC)
*/
/* Clock divider control (SSCGCLKDCSID[3:0]) */
#define _CGC_CLK_SSCGO_DIVISION_NO                     (0x00000000UL) /* No division (default) */
#define _CGC_CLK_SSCGO_DIVISION_1_16                   (0x00000001UL) /* Divided by 1/16 */
#define _CGC_CLK_SSCGO_DIVISION_2_16                   (0x00000002UL) /* Divided by 2/16 */
#define _CGC_CLK_SSCGO_DIVISION_3_16                   (0x00000003UL) /* Divided by 3/16 */
#define _CGC_CLK_SSCGO_DIVISION_4_16                   (0x00000004UL) /* Divided by 4/16 */
#define _CGC_CLK_SSCGO_DIVISION_5_16                   (0x00000005UL) /* Divided by 5/16 */
#define _CGC_CLK_SSCGO_DIVISION_6_16                   (0x00000006UL) /* Divided by 6/16 */
#define _CGC_CLK_SSCGO_DIVISION_7_16                   (0x00000007UL) /* Divided by 7/16 */
#define _CGC_CLK_SSCGO_DIVISION_8_16                   (0x00000008UL) /* Divided by 8/16 */
#define _CGC_CLK_SSCGO_DIVISION_9_16                   (0x00000009UL) /* Divided by 9/16 */
#define _CGC_CLK_SSCGO_DIVISION_10_16                  (0x0000000AUL) /* Divided by 10/16 */
#define _CGC_CLK_SSCGO_DIVISION_11_16                  (0x0000000BUL) /* Divided by 11/16 */
#define _CGC_CLK_SSCGO_DIVISION_12_16                  (0x0000000CUL) /* Divided by 12/16 */
#define _CGC_CLK_SSCGO_DIVISION_13_16                  (0x0000000DUL) /* Divided by 13/16 */
#define _CGC_CLK_SSCGO_DIVISION_14_16                  (0x0000000EUL) /* Divided by 14/16 */
#define _CGC_CLK_SSCGO_DIVISION_15_16                  (0x0000000FUL) /* Divided by 15/16 */

/*
    CLK_SSCGO Divider Status Register (CKD_SSCGS)
*/
/* Divider clock synchronized (SSCGCLKDSYNC) */
#define _CGC_CLK_SSCGO_DIVIDER_SYNC                    (0x00000002UL) /* Clock output corresponds to the 
                                                                         divisor setting in SSCGCLKDCSID */

/*
    CLK_SSCG1O Divider Control Register (CKD_SSCG1C)
*/
/* Clock divider control (SSCG1CLKDCSID[3:0]) */
#define _CGC_CLK_SSCG1O_DIVISION_NO                    (0x00000000UL) /* No division (default) */
#define _CGC_CLK_SSCG1O_DIVISION_1_16                  (0x00000001UL) /* Divided by 1/16 */
#define _CGC_CLK_SSCG1O_DIVISION_2_16                  (0x00000002UL) /* Divided by 2/16 */
#define _CGC_CLK_SSCG1O_DIVISION_3_16                  (0x00000003UL) /* Divided by 3/16 */
#define _CGC_CLK_SSCG1O_DIVISION_4_16                  (0x00000004UL) /* Divided by 4/16 */
#define _CGC_CLK_SSCG1O_DIVISION_5_16                  (0x00000005UL) /* Divided by 5/16 */
#define _CGC_CLK_SSCG1O_DIVISION_6_16                  (0x00000006UL) /* Divided by 6/16 */
#define _CGC_CLK_SSCG1O_DIVISION_7_16                  (0x00000007UL) /* Divided by 7/16 */
#define _CGC_CLK_SSCG1O_DIVISION_8_16                  (0x00000008UL) /* Divided by 8/16 */
#define _CGC_CLK_SSCG1O_DIVISION_9_16                  (0x00000009UL) /* Divided by 9/16 */
#define _CGC_CLK_SSCG1O_DIVISION_10_16                 (0x0000000AUL) /* Divided by 10/16 */
#define _CGC_CLK_SSCG1O_DIVISION_11_16                 (0x0000000BUL) /* Divided by 11/16 */
#define _CGC_CLK_SSCG1O_DIVISION_12_16                 (0x0000000CUL) /* Divided by 12/16 */
#define _CGC_CLK_SSCG1O_DIVISION_13_16                 (0x0000000DUL) /* Divided by 13/16 */
#define _CGC_CLK_SSCG1O_DIVISION_14_16                 (0x0000000EUL) /* Divided by 14/16 */
#define _CGC_CLK_SSCG1O_DIVISION_15_16                 (0x0000000FUL) /* Divided by 15/16 */

/*
    CLK_SSCG1O Divider Status Register (CKD_SSCG1S)
*/
/* Divider clock synchronized (SSCG1CLKDSYNC) */
#define _CGC_CLK_SSCG1O_DIVIDER_SYNC                   (0x00000002UL) /* Clock output corresponds to the 
                                                                         divisor setting in SSCG1CLKDCSID */

/*
    CLK_RLIN3 Selector Control Register (CKS_RLINC)
*/
/* Clock source control (RLINSCSID[2:0]) */
#define _CGC_CLK_RLIN3_SOURCE_CLKEMG                   (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_RLIN3_SOURCE_CLKCHSB                  (0x00000001UL) /* CLKC_HSB */
#define _CGC_CLK_RLIN3_SOURCE_CLKMOSC                  (0x00000002UL) /* CLK_MOSC */
#define _CGC_CLK_RLIN3_SOURCE_CLKMOSC_4                (0x00000003UL) /* CLK_MOSC / 4 */
#define _CGC_CLK_RLIN3_SOURCE_CLKMOSC_8                (0x00000004UL) /* CLK_MOSC / 8 */
/* Clock source control (RLIN23SCSID[2:0]) */
#define _CGC_CLK_RLIN3CH23_SOURCE_CLKEMG               (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_RLIN3CH23_SOURCE_CLKCHBUS             (0x00010000UL) /* CLKC_HBUS */
#define _CGC_CLK_RLIN3CH23_SOURCE_CLKMOSC              (0x00020000UL) /* CLK_MOSC */
#define _CGC_CLK_RLIN3CH23_SOURCE_CLKMOSC_4            (0x00030000UL) /* CLK_MOSC / 4 */
#define _CGC_CLK_RLIN3CH23_SOURCE_CLKMOSC_8            (0x00040000UL) /* CLK_MOSC / 8 */

/*
    CLK_RLIN3 Selector Status Register (CKS_RLINS)
*/
/* Clock source status for CLK_RLIN3 (RLINSACT[2:0]) */
#define _CGC_CLK_RLIN3_CLKEMG_ACTIVE                   (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_RLIN3_CLKCHSB_ACTIVE                  (0x00000001UL) /* CLKC_HSB */
#define _CGC_CLK_RLIN3_CLKMOSC_ACTIVE                  (0x00000002UL) /* CLK_MOSC */
#define _CGC_CLK_RLIN3_CLKMOSC_4_ACTIVE                (0x00000003UL) /* CLK_MOSC / 4 */
#define _CGC_CLK_RLIN3_CLKMOSC_8_ACTIVE                (0x00000004UL) /* CLK_MOSC / 8 */
#define _CGC_CLK_RLIN3_STATUS_DEFAULT                  (0xFFFFFFF8UL) /* CLK_RLIN3 status default value */
/* Clock source status for CLK_RLIN3_CH23 (RLIN23SACT[2:0]) */
#define _CGC_CLK_RLIN3CH23_CLKEMG_ACTIVE               (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_RLIN3CH23_CLKCHBUS_ACTIVE             (0x00010000UL) /* CLKC_HBUS */
#define _CGC_CLK_RLIN3CH23_CLKMOSC_ACTIVE              (0x00020000UL) /* CLK_MOSC */
#define _CGC_CLK_RLIN3CH23_CLKMOSC_4_ACTIVE            (0x00030000UL) /* CLK_MOSC / 4 */
#define _CGC_CLK_RLIN3CH23_CLKMOSC_8_ACTIVE            (0x00040000UL) /* CLK_MOSC / 8 */
#define _CGC_CLK_RLIN3CH23_STATUS_DEFAULT              (0xFFF8FFFFUL) /* CLK_RLIN3_CH23 status default value */

/*
    CLK_CANFD_C/CLK_CANFD_XIN Selector Control Register (CKS_RCANC)
*/
/* Clock source control (RCANCSCSID[1:0]) */
#define _CGC_CLK_CANFD_C_SOURCE_CLKEMG                 (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_CANFD_C_SOURCE_CLKCHSB                (0x00010000UL) /* CLKC_HSB */
#define _CGC_CLK_CANFD_C_SOURCE_CLKCHSB_2              (0x00020000UL) /* CLKC_HSB / 2 */
#define _CGC_CLK_CANFD_C_SOURCE_CLKCHSB_4              (0x00030000UL) /* CLKC_HSB / 4 */
/* Clock source control (RCANXINSCSID[1:0]) */
#define _CGC_CLK_CANFD_XIN_SOURCE_CLKEMG               (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_CANFD_XIN_SOURCE_CLKMOSC              (0x00000001UL) /* CLK_MOSC */
#define _CGC_CLK_CANFD_XIN_SOURCE_CLKMOSC_2            (0x00000002UL) /* CLK_MOSC / 2 */
#define _CGC_CLK_CANFD_XIN_SOURCE_CLKMOSC_4            (0x00000003UL) /* CLK_MOSC / 4 */

/*
    CLK_CANFD_C/CLK_CANFD_XIN Selector Status Register (CKS_RCANS)
*/
/* Clock source status for CLK_CANFD_C (RCANCSACT[1:0]) */
#define _CGC_CLK_CANFD_C_CLKEMG_ACTIVE                 (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_CANFD_C_CLKCHSB_ACTIVE                (0x00010000UL) /* CLKC_HSB */
#define _CGC_CLK_CANFD_C_CLKCHSB_2_ACTIVE              (0x00020000UL) /* CLKC_HSB / 2 */
#define _CGC_CLK_CANFD_C_CLKCHSB_4_ACTIVE              (0x00030000UL) /* CLKC_HSB / 4 */
#define _CGC_CLK_CANFD_C_STATUS_DEFAULT                (0xFFFCFFFFUL) /* CLK_CANFD_C status default value */
/* Clock source status for CLK_CANFD_XIN (RCANXINSACT[1:0]) */
#define _CGC_CLK_CANFD_XIN_CLKEMG_ACTIVE               (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_CANFD_XIN_CLKMOSC_ACTIVE              (0x00000001UL) /* CLK_MOSC */
#define _CGC_CLK_CANFD_XIN_CLKMOSC_2_ACTIVE            (0x00000002UL) /* CLK_MOSC / 2 */
#define _CGC_CLK_CANFD_XIN_CLKMOSC_4_ACTIVE            (0x00000003UL) /* CLK_MOSC / 4 */
#define _CGC_CLK_CANFD_XIN_STATUS_DEFAULT              (0xFFFFFFFCUL) /* CLK_CANFD_XIN status default value */

/*
    CLK_MSPI Selector Control Register (CKS_MSPIC)
*/
/* Clock source control (MSPISCSID[1:0]) */
#define _CGC_CLK_MSPI_SOURCE_CLKEMG                    (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_MSPI_SOURCE_CLKMOSC                   (0x00000001UL) /* CLK_MOSC */
#define _CGC_CLK_MSPI_SOURCE_CLKCHSB                   (0x00000002UL) /* CLKC_HSB */

/*
    CLK_MSPI Selector Status Register (CKS_MSPIS)
*/
/* Clock source status for CLK_MSPI (MSPISACT[1:0]) */
#define _CGC_CLK_MSPI_CLKEMG_ACTIVE                    (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_MSPI_CLKMOSC_ACTIVE                   (0x00000001UL) /* CLK_MOSC */
#define _CGC_CLK_MSPI_CLKCHSB_ACTIVE                   (0x00000002UL) /* CLKC_HSB */
#define _CGC_CLK_MSPI_STATUS_DEFAULT                   (0xFFFFFFFCUL) /* CLK_MSPI status default value */

/*
    CLK_SWDT Selector Control Register (CLK_SWDT)
*/
/* Clock source control (SWDTSCSID[1:0]) */
#define _CGC_CLK_SWDT_SOURCE_HSIOSC_20                 (0x00000000UL) /* CLK_HSIOSC / 20 */
#define _CGC_CLK_SWDT_SOURCE_HSIOSC_640                (0x00000001UL) /* CLK_HSIOSC / 640 */
#define _CGC_CLK_SWDT_SOURCE_HSIOSC_800                (0x00000002UL) /* CLK_HSIOSC / 800 */
#define _CGC_CLK_SWDT_SOURCE_HSIOSC_100000             (0x00000003UL) /* CLK_HSIOSC / 100000 */

/*
    CLK_SWDT Selector Status Register (CKS_SWDTS)
*/
/* Clock source status for CLK_SWDT (SWDTSACT[1:0]) */
#define _CGC_CLK_SWDT_HSIOSC_20_ACTIVE                 (0x00000000UL) /* CLK_HSIOSC / 20 */
#define _CGC_CLK_SWDT_HSIOSC_640_ACTIVE                (0x00000001UL) /* CLK_HSIOSC / 640 */
#define _CGC_CLK_SWDT_HSIOSC_800_ACTIVE                (0x00000002UL) /* CLK_HSIOSC / 800 */
#define _CGC_CLK_SWDT_HSIOSC_100000_ACTIVE             (0x00000003UL) /* CLK_HSIOSC / 100000 */
#define _CGC_CLK_SWDT_STATUS_DEFAULT                   (0xFFFFFFFCUL) /* CLK_SWDT status default value */

/*
    CLKC_CANXL_CHn Selector Control Register (CKS_CANXLnC)
*/
/* Clock source control (CANXLSCSID[2:0]) */
#define _CGC_CLKC_CANXL_CHN_SOURCE_CLKEMG              (0x00000000UL) /* CLK_EMG */
#define _CGC_CLKC_CANXL_CHN_SOURCE_CLKCHSB             (0x00000001UL) /* CLKC_HSB */
#define _CGC_CLKC_CANXL_CHN_SOURCE_CLKCUHSB            (0x00000004UL) /* CLKC_UHSB */

/*
    CLKC_CANXL_CHn Selector Status Register (CKS_CANXLnS)
*/
/* Clock source status for CLKC_CANXL_CHn (CANXLSCSID[2:0] */
#define _CGC_CLKC_CANXL_CHN_CLKEMG_ACTIVE              (0x00000000UL) /* CLK_EMG */
#define _CGC_CLKC_CANXL_CHN_CLKCHSB_ACTIVE             (0x00000001UL) /* CLKC_HSB */
#define _CGC_CLKC_CANXL_CHN_CLKCUHSB_ACTIVE            (0x00000004UL) /* CLKC_UHSB */
#define _CGC_CLKC_CANXL_CHN_STATUS_DEFAULT             (0xFFFFFFF8UL) /* CLKC_CANXL_CH status default value */

/*
    CLK_OSPI Selector Control Register (CKS_OSPIC)
*/
/* Clock source control for CLK_OSPI (OSPISCSID[1:0]) */
#define _CGC_CLK_OSPI_SOURCE_CLKEMG                    (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_OSPI_SOURCE_CLKCHBUS_2                (0x00000001UL) /* CLKC_HBUS/2 */
#define _CGC_CLK_OSPI_SOURCE_CLKCSHSB_2                (0x00000002UL) /* CLKC_SHSB/2 */
/* Clock source control for CLK_OSPIX2 (OSPIX2SCSID[1:0]) */
#define _CGC_CLK_OSPIX2_SOURCE_CLKEMG                  (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_OSPIX2_SOURCE_CLKCHBUS                (0x00010000UL) /* CLKC_HBUS */
#define _CGC_CLK_OSPIX2_SOURCE_CLKCSHSB                (0x00020000UL) /* CLKC_SHSB */

/*
    CLK_OSPI Selector Status Register (CKS_OSPIS)
*/
/* Clock source status for CLK_OSPI (OSPISACT[1:0]) */
#define _CGC_CLK_OSPI_CLKEMG_ACTIVE                    (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_OSPI_CLKCHBUS_2_ACTIVE                (0x00000001UL) /* CLKC_HBUS/2 */
#define _CGC_CLK_OSPI_CLKCSHSB_2_ACTIVE                (0x00000002UL) /* CLKC_SHSB/2 */
#define _CGC_CLK_OSPI_STATUS_DEFAULT                   (0xFFFFFFFCUL) /* CLK_OSPI status default value */
/* Clock source status for CLK_OSPIX2 (OSPIX2SACT[1:0]) */
#define _CGC_CLK_OSPIX2_CLKEMG_ACTIVE                  (0x00000000UL) /* CLK_EMG */
#define _CGC_CLK_OSPIX2_CLKCHBUS_ACTIVE                (0x00010000UL) /* CLKC_HBUS */
#define _CGC_CLK_OSPIX2_CLKCSHSB_ACTIVE                (0x00020000UL) /* CLKC_SHSB */
#define _CGC_CLK_OSPIX2_STATUS_DEFAULT                 (0xFFFCFFFFUL) /* CLK_OSPIX2 status default value */

/*
    CLKA_WDTBA Selector Control Register (CKS_AWDTC)
*/
/* Clock source control (AWDTSCSID) */
#define _CGC_CLKA_WDTBA_SOURCE_CLKLSIOSC               (0x00000000UL) /* CLK_LSIOSC */
#define _CGC_CLKA_WDTBA_SOURCE_CLKLSIOSC_128           (0x00000001UL) /* CLK_LSIOSC / 128 */

/*
    CLKA_WDTBA Selector Status Register (CKS_AWDTS)
*/
/* Clock source status for CLKA_WDTBA (AWDTSACT) */
#define _CGC_CLKA_WDTBA_CLKLSIOSC_ACTIVE               (0x00000000UL) /* CLK_LSIOSC */
#define _CGC_CLKA_WDTBA_CLKLSIOSC_128_ACTIVE           (0x00000001UL) /* CLK_LSIOSC / 128 */

/*
    CLKA_TAUJ Selector Control Register (CKS_ATAUJC)
*/
/* Clock source control (ATAUJSCSID[2:0]) */
#define _CGC_CLKA_TAUJ_SOURCE_CLKEMG                   (0x00000000UL) /* CLK_EMG */
#define _CGC_CLKA_TAUJ_SOURCE_CLKLSIOSC                (0x00000001UL) /* CLK_LSIOSC */
#define _CGC_CLKA_TAUJ_SOURCE_CLKHSIOSC_20             (0x00000002UL) /* CLK_HSIOSC / 20 */
#define _CGC_CLKA_TAUJ_SOURCE_CLKMOSC                  (0x00000003UL) /* CLK_MOSC */
#define _CGC_CLKA_TAUJ_SOURCE_CLKCHSB                  (0x00000004UL) /* CLKC_HSB */

/*
    CLKA_TAUJ Selector Status Register (CKS_ATAUJS)
*/
/* Clock source status for CLKA_TAUJ (ATAUJSACT[2:0]) */
#define _CGC_CLKA_TAUJ_CLKEMG_ACTIVE                   (0x00000000UL) /* CLK_EMG */
#define _CGC_CLKA_TAUJ_CLKLSIOSC_ACTIVE                (0x00000001UL) /* CLK_LSIOSC */
#define _CGC_CLKA_TAUJ_CLKHSIOSC_20_ACTIVE             (0x00000002UL) /* CLK_HSIOSC / 20 */
#define _CGC_CLKA_TAUJ_CLKMOSC_ACTIVE                  (0x00000003UL) /* CLK_MOSC */
#define _CGC_CLKA_TAUJ_CLKCHSB_ACTIVE                  (0x00000004UL) /* CLKC_HSB */
#define _CGC_CLKA_TAUJ_STATUS_DEFAULT                  (0xFFFFFFF8UL) /* CLKA_TAUJ status default value */

/*
    CLKA_RTCA Selector Control Register (CKS_ARTCAC)
*/
/* Clock source control (ARTCASCSID[2:0]) */
#define _CGC_CLKA_RTCA_SOURCE_CLKEMG                   (0x00000000UL) /* CLK_EMG */
#define _CGC_CLKA_RTCA_SOURCE_CLKLSIOSC                (0x00000001UL) /* CLK_LSIOSC */
#define _CGC_CLKA_RTCA_SOURCE_CLKMOSC_16               (0x00000002UL) /* CLK_MOSC / 16 */

/*
    CLKA_RTCA Selector Status Register (CKS_ARTCAS)
*/
/* Clock source status for CLKA_RTCA (ARTCASACT[1:0]) */
#define _CGC_CLKA_RTCA_CLKEMG_ACTIVE                   (0x00000000UL) /* CLK_EMG */
#define _CGC_CLKA_RTCA_CLKLSIOSC_ACTIVE                (0x00000001UL) /* CLK_LSIOSC */
#define _CGC_CLKA_RTCA_CLKMOSC_16_ACTIVE               (0x00000002UL) /* CLK_MOSC / 16 */
#define _CGC_CLKA_RTCA_STATUS_DEFAULT                  (0xFFFFFFFCUL) /* CLKA_RTCA status default value */

/*
    EXTCLK0 Clock Selector Control Register (CKS_EXTCLK0C)
*/
/* Source clock setting for EXTCLK0O (EXTCLK0SCSID[3:0]) */
#define _CGC_EXTCLK0_SOURCE_CLKMOSC                    (0x00000000UL) /* CLK_MOSC */
#define _CGC_EXTCLK0_SOURCE_CLKLSIOSC                  (0x00000001UL) /* CLK_LSIOSC */
#define _CGC_EXTCLK0_SOURCE_CLKHSIOSC_20               (0x00000002UL) /* CLK_HSIOSC / 20 */
#define _CGC_EXTCLK0_SOURCE_CLKHSB                     (0x00000004UL) /* CLK_HSB */
#define _CGC_EXTCLK0_SOURCE_CLKCHSB                    (0x00000005UL) /* CLKC_HSB */

/*
    EXTCLK0 Clock Selector Status Register (CKS_EXTCLK0S)
*/
/* Clock source status for EXTCLK0 (EXTCLK0SACT[3:0]) */
#define _CGC_EXTCLK0_CLKMOSC_ACTIVE                    (0x00000000UL) /* CLK_MOSC */
#define _CGC_EXTCLK0_CLKLSIOSC_ACTIVE                  (0x00000001UL) /* CLK_LSIOSC */
#define _CGC_EXTCLK0_CLKHSIOSC_20_ACTIVE               (0x00000002UL) /* CLK_HSIOSC / 20 */
#define _CGC_EXTCLK0_CLKHSB_ACTIVE                     (0x00000004UL) /* CLK_HSB */
#define _CGC_EXTCLK0_CLKCHSB_ACTIVE                    (0x00000005UL) /* CLKC_HSB */
#define _CGC_EXTCLK0_STATUS_DEFAULT                    (0xFFFFFFF0UL) /* EXTCLK0 status default value */

/*
    EXTCLK0 Clock Divider Control Register (CKD_EXTCLK0C)
*/
/* Clock division for EXTCLK0 (EXTCLK0DIV[9:0]) */
#define _CGC_EXTCLK0O_OUTPUT_DISABLE                   (0x00000000UL) /* EXTCLK0O output is stopped */

/*
    EXTCLK0 Clock Divider Status Register (CKD_EXTCLK0S)
*/
/* Clock divider active (EXTCLK0CLKACT) */
#define _CGC_EXTCLK0_OUTPUT_ONGOING                    (0x00000002UL) /* Frequency output is ongoing */
/* Clock divider synchronized (EXTCLK0SYNC) */
#define _CGC_EXTCLK0_DIVIDER_STABLE                    (0x00000001UL) /* The clock divider is stable */

/*
    EXTCLK1 Clock Selector Control Register (CKS_EXTCLK1C)
*/
/* Source clock setting for EXTCLK1O (EXTCLK1SCSID[3:0]) */
#define _CGC_EXTCLK1_SOURCE_CLKMOSC                    (0x00000000UL) /* CLK_MOSC */
#define _CGC_EXTCLK1_SOURCE_CLKLSIOSC                  (0x00000001UL) /* CLK_LSIOSC */
#define _CGC_EXTCLK1_SOURCE_CLKHSIOSC_20               (0x00000002UL) /* CLK_HSIOSC / 20 */
#define _CGC_EXTCLK1_SOURCE_CLKHSB                     (0x00000004UL) /* CLK_HSB */
#define _CGC_EXTCLK1_SOURCE_CLKCHSB                    (0x00000005UL) /* CLKC_HSB */

/*
    EXTCLK1 Clock Selector Status Register (CKS_EXTCLK1S)
*/
/* Clock source status for EXTCLK1 (EXTCLK1SACT[3:0]) */
#define _CGC_EXTCLK1_CLKMOSC_ACTIVE                    (0x00000000UL) /* CLK_MOSC */
#define _CGC_EXTCLK1_CLKLSIOSC_ACTIVE                  (0x00000001UL) /* CLK_LSIOSC */
#define _CGC_EXTCLK1_CLKHSIOSC_20_ACTIVE               (0x00000002UL) /* CLK_HSIOSC / 20 */
#define _CGC_EXTCLK1_CLKHSB_ACTIVE                     (0x00000004UL) /* CLK_HSB */
#define _CGC_EXTCLK1_CLKCHSB_ACTIVE                    (0x00000005UL) /* CLKC_HSB */
#define _CGC_EXTCLK1_STATUS_DEFAULT                    (0xFFFFFFF0UL) /* EXTCLK1 status default value */

/*
    EXTCLK1 Clock Divider Control Register (CKD_EXTCLK1C)
*/
/* Clock division for EXTCLK1 (EXTCLK1DIV[9:0]) */
#define _CGC_EXTCLK1O_OUTPUT_DISABLE                   (0x00000000UL) /* EXTCLK1O output is stopped */

/*
    EXTCLK1 Clock Divider Status Register (CKD_EXTCLK1S)
*/
/* Clock divider active (EXTCLK1CLKACT) */
#define _CGC_EXTCLK1_OUTPUT_ONGOING                    (0x00000002UL) /* Frequency output is ongoing */
/* Clock divider synchronized (EXTCLK1SYNC) */
#define _CGC_EXTCLK1_DIVIDER_STABLE                    (0x00000001UL) /* The clock divider is stable */

/*
    CLK_WDTB/CLK_WDT_ICUM Selector Control Register (CKS_WDTC)
*/
/* Clock source control (WDTSCSID[1:0]) */
#define _CGC_CLK_WDTB_SOURCE_HSIOSC_20                 (0x00000000UL) /* CLK_HSIOSC / 20 */
#define _CGC_CLK_WDTB_SOURCE_HSIOSC_640                (0x00000001UL) /* CLK_HSIOSC / 640 */
#define _CGC_CLK_WDTB_SOURCE_HSIOSC_800                (0x00000002UL) /* CLK_HSIOSC / 800 */

/*
    CLK_WDTB Selector Status Register (CKS_WDTS)
*/
/* Clock source status for CLK_WDTB (WDTSACT[1:0]) */
#define _CGC_CLK_WDTB_HSIOSC_20_ACTIVE                 (0x00000000UL) /* CLK_HSIOSC / 20 */
#define _CGC_CLK_WDTB_HSIOSC_640_ACTIVE                (0x00000001UL) /* CLK_HSIOSC / 640 */
#define _CGC_CLK_WDTB_HSIOSC_800_ACTIVE                (0x00000002UL) /* CLK_HSIOSC / 800 */
#define _CGC_CLK_WDTB_STATUS_DEFAULT                   (0xFFFFFFFCUL) /* CLK_WDTB status default value */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _CGC_HSOSC_TARGET_FREQUENCY_MIN                (197U) /* HSOSC min of the target frequency (200 - 1.5% MHz) */
#define _CGC_HSOSC_TARGET_FREQUENCY_MAX                (203U) /* HSOSC max of the target frequency (200 + 1.5% MHz) */
#define _CGC_EXTCLK0_DIVISION_RATIO                    (0x00000001UL) /* EXTCLK0 clock divider N */
#define _CGC_EXTCLK1_DIVISION_RATIO                    (0x00000001UL) /* EXTCLK1 clock divider N */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_CGC_Create(void);
void R_CGC_Create_UserInit(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
