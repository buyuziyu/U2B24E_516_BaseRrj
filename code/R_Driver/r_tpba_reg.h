
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
#ifndef R_TPBA_REG_H
#define R_TPBA_REG_H

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_compiler.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define TPBA0_base          0xFFBFA000UL
#define TPBA1_base          0xFF892000UL

#define TPBA_CTL(n)         REG32((n) + 0x200UL)
#define TPBA_RDM(n)         REG32((n) + 0x118UL)
#define TPBA_RSF(n)         REG32((n) + 0x110UL)
#define TPBA_RDT(n)         REG32((n) + 0x114UL)
#define TPBA_TOE(n)         REG32((n) + 0x120UL)
#define TPBA_TO(n)          REG32((n) + 0x11CUL)
#define TPBA_TOL(n)         REG32((n) + 0x124UL)
#define TPBA_CMP0(n)        REG32((n) + 0x100UL)
#define TPBA_BUF(n,m)       REG32((n) + (m * 0x04UL))
#define TPBA_CMP1(n)        REG32((n) + 0x104UL)
#define TPBA_CNT0(n)        REG32((n) + 0x108UL)
#define TPBA_CNT1(n)        REG32((n) + 0x10CUL)
#define TPBA_TE(n)          REG32((n) + 0x128UL)
#define TPBA_TS(n)          REG32((n) + 0x12CUL)
#define TPBA_TT(n)          REG32((n) + 0x130UL)
/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global functions
 *****************************************************************************/

#endif  /* R_SLAVE_GUARD_REG_H */
