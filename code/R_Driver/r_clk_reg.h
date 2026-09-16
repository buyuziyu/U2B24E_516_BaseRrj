/******************************************************************************* 
* DISCLAIMER 
* This software is supplied by Renesas Electronics Corporation and is only  
* intended for use with Renesas products. No other uses are authorized. This  
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE  
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. 
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS  
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE  
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software. By using this software, 
* you agree to the additional terms and conditions found by accessing the  
* following link: 
* http://www.renesas.com/disclaimer 
* 
* Copyright (C) 2012, 2014 Renesas Electronics Corporation. All rights reserved.     
*******************************************************************************/
#ifndef R_CLK_REG_H
#define R_CLK_REG_H

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_compiler.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define PLLE                         REG32(0xFF980000UL)
#define PLLS                         REG32(0xFF980004UL)
#define PLLSTPM                      REG32(0xFF98000CUL)
#define CKSC_CPUC                    REG32(0xFF980100UL)
#define CKSC_CPUS                    REG32(0xFF980108UL)
#define CLKD_PLLC                    REG32(0xFF980120UL)
#define CLKD_PLLS                    REG32(0xFF980128UL)
#define CKSC_RLINC                   REG32(0xFF980140UL)
#define CKSC_RLINS                   REG32(0xFF980148UL)
#define CKSC_RCANC                   REG32(0xFF980150UL)
#define CKSC_RCANS                   REG32(0xFF980158UL)
#define CKSC_ADCC                    REG32(0xFF980160UL)
#define CKSC_ADCS                    REG32(0xFF980168UL)
#define CKSC_MSPIC                   REG32(0xFF980170UL)
#define CKSC_MSPIS                   REG32(0xFF980178UL)
#define CLKKCPROT1                   REG32(0xFF980700UL)
#define MOSCE                        REG32(0xFF988000UL)
#define MOSCS                        REG32(0xFF988004UL)
#define MOSCSTPM                     REG32(0xFF98800CUL)
#define HSOSCS                       REG32(0xFF988100UL)
#define HSOSCSTPM                    REG32(0xFF988104UL)
#define CKSC_AWDTC                   REG32(0xFF988200UL)
#define CKSC_AWDTS                   REG32(0xFF988208UL)
#define CKSC_ATAUJC                  REG32(0xFF988210UL)
#define CKSC_ATAUJS                  REG32(0xFF988218UL)
#define CKSC_ARTCAC                  REG32(0xFF988220UL)
#define CKSC_ARTCAS                  REG32(0xFF988228UL)
#define CKSC_AADCC                   REG32(0xFF988230UL)
#define CKSC_AADCS                   REG32(0xFF988238UL)
#define CLKD_AADCC                   REG32(0xFF988240UL)
#define CLKD_AADCS                   REG32(0xFF988248UL)
#define CKSC_FOUT0C                  REG32(0xFF988250UL)
#define CKSC_FOUT0S                  REG32(0xFF988258UL)
#define CLKD_FOUT0C                  REG32(0xFF988260UL)
#define CLKD_FOUT0S                  REG32(0xFF988268UL)
#define CKSC_FOUT1C                  REG32(0xFF988270UL)
#define CKSC_FOUT1S                  REG32(0xFF988278UL)
#define CLKD_FOUT1C                  REG32(0xFF988280UL)
#define CLKD_FOUT1S                  REG32(0xFF988288UL)
#define CKSC_WDTC                    REG32(0xFF988300UL)
#define CKSC_WDTS                    REG32(0xFF988308UL)

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global functions
 *****************************************************************************/

#endif  /* R_CLK_REG_H */
