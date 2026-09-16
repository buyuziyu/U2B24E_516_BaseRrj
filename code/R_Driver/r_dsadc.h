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
#ifndef _R_DSADC_H_
#define _R_DSADC_H_

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_compiler.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define DSADC_CNVCLS(n)    (n << 4)
#define DSADC_GCTRL(n)     (n)
#define DSADC_TPVSL(n)     (n << 20)

#define DSADC_DFMT(n)      (n << 8)
/*****************************************************************************
 Typedef definitions
 *****************************************************************************/
typedef struct STag_DsadcCfgType
{
    uint8 u1ADGCR;
    uint32 u4VCR;
    uint8 u1ADTCR;
    uint32 u4UCR;
    uint8 u1VCPTRR;
    uint8 u1SFTCR;
}DsadcCfg;
/*****************************************************************************
 Global variables
 *****************************************************************************/


void R_DSADC_Init(uint8 Lu1DsadcUnit, DsadcCfg PuDsAdcCfg);
void R_DSADC_Start(uint8 Lu1DsadcUnit);
uint16 R_DSADC_GetData(uint8 Lu1DsadcUnit, uint8 Lu1DsChannel);
#endif
