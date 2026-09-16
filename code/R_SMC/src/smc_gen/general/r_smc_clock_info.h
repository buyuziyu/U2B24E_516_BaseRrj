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
* File Name        : r_smc_clock_info.h
* Version          : 1.8.0
* Device(s)        : R7F7025Bx
* Description      : This file contains MCU information and clocks frequency define according to Clocks tabs setting.
***********************************************************************************************************************/

#ifndef R_SMC_CLOCK_INFO_H
#define R_SMC_CLOCK_INFO_H

/***********************************************************************************************************************
 * MCU information
***********************************************************************************************************************/
 
/*
 R 7 F 7025 x xEAB x -C
  | | |  |  |  |  |  |_____not used              Ambient operating temperature range
  | | |  |  |  |  |________SMC_CFG_MCU_PART_PIN_NUM   Pin count
  | | |  |  |  |___________not used              Package type
  | | |  |  |______________SMC_CFG_MCU_PART_ROM_SIZE  ROM capacity
  | | |  |_________________not used              RH850/U2B
  | | |____________________SMC_CFG_MCU_PART_ROM_TYPE  Device type
  | |______________________not used              Renesas MCU
  |________________________not used              Renesas semiconductor product
*/
 
/* Pin count
 B = 292-pin  : 0x0U
 A = 373-pin  : 0x1U
 G = 468-pin  : 0x2U
*/
#define SMC_CFG_MCU_PART_PIN_NUM                                  (0x1U)
 
/* ROM capacity (Code Flash/Data Flash/RAM)
 5 = 6MB/128KB/576KB : 0x0U
 4 = 10MB/256KB/1280KB : 0x1U
 2 = 20MB/512KB/2560KB : 0x2U
 1 = 24MB/512KB/4096KB : 0x3U
*/
#define SMC_CFG_MCU_PART_ROM_SIZE                                 ()
 
/* group
 7025 = RH850/U2B : (true)
*/
#define SMC_CFG_MCU_PART_HAS_DATA_FLASH                           (true)
 
/* Device type
 F = Flash memory : 0U
*/
#define SMC_CFG_MCU_PART_ROM_TYPE                                 (0U)
 
/***********************************************************************************************************************
 * Clocks frequency
***********************************************************************************************************************/

/* HV IntOSC clock (KHz) */
#define SMC_CFG_CLK_HV_INTOSC                                     (16000U)

/* LS IntOSC clock (KHz) */
#define SMC_CFG_CLK_LS_INTOSC                                     (240U)

/* HS IntOSC clock (KHz) */
#define SMC_CFG_CLK_HS_INTOSC                                     (200000UL)

/* Internal OSC clock (KHz) */
#define SMC_CFG_CLK_IOSC                                          (200000UL)

/* Emergency clock (KHz) */
#define SMC_CFG_CLK_EMG                                           (10000U)

/* Main OSC clock (KHz) */
#define SMC_CFG_CLK_MOSC                                          (20000U)

/* SSCG clock (KHz)*/
#define SMC_CFG_CLK_SSCG                                          (800000UL)

/* SSCG1 clock (KHz)*/
#define SMC_CFG_CLK_SSCG1                                         (800000UL)

/* CPU clock (KHz) */
#define SMC_CFG_CLK_CPU                                           (400000UL)

/* System bus clock (KHz) */
#define SMC_CFG_CLK_SBUS                                          (200000UL)

/* H-BUS clock (KHz) */
#define SMC_CFG_CLK_HBUS                                          (100000UL)

/* Peripheral ultra high speed clock (KHz) */
#define SMC_CFG_CLK_UHSB                                          (160000UL)

/* Peripheral high speed clock (KHz) */
#define SMC_CFG_CLK_HSB                                           (80000UL)

/* Peripheral low speed clock (KHz) */
#define SMC_CFG_CLK_LSB                                           (40000U)

/* CPU clock (Clean) (KHz) */
#define SMC_CFG_CLKC_CPU                                          (400000UL)

/* System bus clock (Clean) (KHz) */
#define SMC_CFG_CLKC_SBUS                                         (200000UL)

/* H-BUS clock (Clean) (KHz) */
#define SMC_CFG_CLKC_HBUS                                         (100000UL)

/* Peripheral ultra high speed clock (Clean) (KHz) */
#define SMC_CFG_CLKC_UHSB                                         (160000UL)

/* Peripheral super speed clock (Clean) (KHz) */
#define SMC_CFG_CLKC_SHSB                                         (133333UL)

/* Peripheral high speed clock (Clean) (KHz) */
#define SMC_CFG_CLKC_HSB                                          (80000UL)

/* Peripheral low speed clock (Clean) (KHz) */
#define SMC_CFG_CLKC_LSB                                          (40000U)

/* DFA clock (KHz) */
#define SMC_CFG_CLK_DFA                                           (400000UL)

/* LPS operating clock (KHz) */
#define SMC_CFG_CLKA_LPS                                          (10000U)

/* SWDT operating clock (KHz) */
#define SMC_CFG_CLK_SWDT                                          (10000U)

/* CANXL_CH0 operating clock (KHz) */
#define SMC_CFG_CLKC_CANXL_CH0                                    (80000UL)

/* CANXL_CH1 operating clock (KHz) */
#define SMC_CFG_CLKC_CANXL_CH1                                    (10000U)

/* OSPI operating clock (KHz) */
#define SMC_CFG_CLK_OSPI                                          (10000U)

/* OSPIX2 operating clock (KHz) */
#define SMC_CFG_CLK_OSPIX2                                        (10000U)

/* WDTBA count clock (Hz) */
#define SMC_CFG_CLKA_WDTBA                                        (1875U)

/* TAUJn (n = 2, 3) operating clock (KHz) */
#define SMC_CFG_CLKA_TAUJ                                         (80000UL)

/* RTCA count clock (KHz) */
#define SMC_CFG_CLKA_RTCA                                         (240U)

/* Clock output 0 (EXTCLK0) (KHz) */
#define SMC_CFG_EXTCLK0O                                          (10000U)

/* Clock output 1 (EXTCLK1) (KHz) */
#define SMC_CFG_EXTCLK1O                                          (10000U)

/* MSPI comm. clock (KHz) */
#define SMC_CFG_CLK_MSPI                                          (80000UL)

/* RLIN3 comm. clock (KHz) */
#define SMC_CFG_CLK_RLIN3                                         (5000U)

/* RLIN3 CH23 comm. clock (KHz) */
#define SMC_CFG_CLK_RLIN3_CH23                                    (5000U)

/* RS-CANFD_C comm. clock (KHz) */
#define SMC_CFG_CLK_CANFD_C                                       (80000UL)

/* RS-CANFD_XIN comm. clock (KHz) */
#define SMC_CFG_CLK_CANFD_XIN                                     (20000U)

/* WDTBn (n = 0 to 7) count clock (Hz) */
#define SMC_CFG_CLK_WDTB_ICUM                                     (312500UL)

/* GTM main/bus clock (KHz) */
#define SMC_CFG_CLK_GTM                                           (200000UL)

/* ECM delay timer clock (KHz) */
#define SMC_CFG_CLK_ECMCNT                                        (10000U)

#endif
