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
#ifndef _R_DSADC_REG_H_
#define _R_DSADC_REG_H_

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_compiler.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define DSADC_base                                  0xFFF24000UL
#define DSADC00_base                                0xFFF24200UL
#define DSADC10_base                                0xFFF24400UL
#define DSADC20_base                                0xFFF24600UL
#define DSADC12_base                                0xFFF24800UL
#define DSADC13_base                                0xFFCA2000UL
#define DSADC11_base                                0xFFCA2200UL
#define DSADC15_base                                0xFFCA2400UL
#define DSADC14_base                                0xFFCA2600UL
#define DSADC22_base                                0xFFCA2800UL
#define DSADC21_base                                0xFFCA2A00UL


#define DSADCSYNSTCR                                REG08(DSADC_base + 0x00)
#define DSADCADGCR                                  REG08(DSADC_base + 0x04)
#define DSADCTDCR                                   REG08(DSADC_base + 0x0C)

#define DSADC_VCR(n,m)                              REG32(n + (0x04 * m))

#define DSADC_DIR(n,m)                              REG32(n + 0x20 + (0x04 * m))

#define DSADC_ADSTCR(n)                             REG08(n + 0x40)
#define DSADC_ADENDCR(n)                            REG08(n + 0x44)
#define DSADC_CLBSTCR(n)                            REG08(n + 0x48)
#define DSADC_CLBEDCR(n)                            REG08(n + 0x4C)
#define DSADC_ADTCR(n)                              REG08(n + 0x50)
#define DSADC_UCR(n)                                REG32(n + 0x54)
#define DSADC_VCPTRR(n)                             REG08(n + 0x58)
#define DSADC_ADSR(n)                               REG08(n + 0x60)
#define DSADC_UDPTRR(n)                             REG08(n + 0x64)
#define DSADC_UDIR(n)                               REG08(n + 0x68)

#define DSADC_TSVAL(n)                              REG32(n + 0x6C)
#define DSADC_SFTCR(n)                              REG08(n + 0x70)
#define DSADC_ECR(n)                                REG08(n + 0x74)
#define DSADC_ER(n)                                 REG32(n + 0x78)
#define DSADC_TDLVR(n)                              REG08(n + 0x7C)
#define DSADC_ULTBR(n,m)                            REG32(n + 0x80 + (0x04 * m))
#define DSADC_TRCR(n)                               REG08(n + 0xB0)
#define DSADC_VBIASR(n)                             REG08(n + 0xB4)
/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/

#endif

