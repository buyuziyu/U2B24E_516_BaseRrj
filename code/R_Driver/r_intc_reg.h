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
#ifndef R_INTC_REG_H
#define R_INTC_REG_H

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_compiler.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define INTC1_SELF_base       0xFFFC0000UL
#define INTC1_PE0_base        0xFFFC4000UL
#define INTC1_PE1_base        0xFFFC8000UL
#define INTC1_PE2_base        0xFFFCC000UL
#define INTC1_PE3_base        0xFFFD0000UL
#define INTC1_PE4_base        0xFFFD4000UL
#define INTC1_PE5_base        0xFFFD8000UL
#define INTC2_base            0xFFF80000UL
#define INTIF_base            0xFF090000UL
#define EINT_base             0xFFC00000UL
#define FENC_base             0xFF9A3A00UL
#define FEINC_PE0_base        0xFF9A3B00UL
#define FEINC_PE1_base        0xFF9A3C00UL
#define FEINC_PE2_base        0xFF9A3D00UL
#define FEINC_PE3_base        0xFF9A3E00UL
#define FEINC_PE4_base        0xFF9A3F00UL
#define FEINC_PE5_base        0xFF9A4000UL
#define INTSEL_INTSTT_base    0xFF090800UL

#define INTC1_EIC(n)     REG16(INTC1_SELF_base + 0x0000UL + 0x02UL * (n))
#define INTC1_IMR0       REG32(INTC1_SELF_base + 0x00F0UL)
#define INTC1_EIBD(n)    REG32(INTC1_SELF_base + 0x0100UL + 0x04UL * (n))
#define INTC1_FIBD(n)    REG32(INTC1_SELF_base + 0x01C0UL)
#define INTC1_EEIC(n)    REG32(INTC1_SELF_base + 0x0200UL + 0x04UL * (n))
#define INTC1_EIBG       REG32(INTC1_SELF_base + 0x0280UL)
#define INTC1_FIBG       REG32(INTC1_SELF_base + 0x02C0UL)
#define INTC1_IHVCFG     REG32(INTC1_SELF_base + 0x02F0UL)

#define INTC2_EIC(n)     REG16(INTC2_base + 0x0000UL + 0x02UL * (n))
#define INTC2_IMR(n)     REG32(INTC2_base + 0x1000UL + 0x04UL * (n))
#define INTC2_I2EIBG(n)  REG32(INTC2_base + 0x1FE0UL + 0x04UL * (n))
#define INTC2_EIBD(n)    REG32(INTC2_base + 0x2000UL + 0x04UL * (n))
#define INTC2_EEIC(n)    REG32(INTC2_base + 0x4000UL + 0x04UL * (n))

#define PINT(n)          REG32(INTIF_base + 0x00UL + 0x04UL * (n))
#define PINTCLR(n)       REG32(INTIF_base + 0x20UL + 0x04UL * (n))
#define TPTMSEL          REG32(INTIF_base + 0x0200UL)
#define RLIN3INTSEL(n)   REG32(INTSEL_INTSTT_base + 0x00UL + 0x04UL * (n))
#define CANINTSEL(n)     REG32(INTSEL_INTSTT_base + 0x1CUL + 0x04UL * (n))
#define TAUD3INTNOSEL(n) REG32(INTSEL_INTSTT_base + 0x30UL + 0x04UL * (n))
#define ENCA1INTNOSEL0   REG32(INTSEL_INTSTT_base + 0x3CUL)
#define TPBAINTNOSEL0    REG32(INTSEL_INTSTT_base + 0x40UL)
#define INTSYSMRESMON    REG32(INTSEL_INTSTT_base + 0x48UL)
#define INTQOSMON(m,n)   REG32(INTSEL_INTSTT_base + 0x50UL + 0x08UL * (m) + 0x04UL * (n))

#define SINTR(n)         REG08(EINT_base  + 0x04UL * (n))

#define FENMIF           REG32(FENC_base  + 0x00UL)
#define FENMIC           REG32(FENC_base  + 0x08UL)

#define FEINTF(pe)       REG32((pe)  + 0x00UL)
#define FEINTMSK(pe)     REG32((pe)  + 0x04UL)
#define FEINTC(pe)       REG32((pe)  + 0x08UL)

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global functions
 *****************************************************************************/

#endif  /* R_INTC_REG_H */
