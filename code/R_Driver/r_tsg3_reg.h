
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
#ifndef R_TSG3_REG_H
#define R_TSG3_REG_H

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_compiler.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define TSG30_base                     0xFFBF8000UL
#define TSG31_base                     0xFF898000UL
#define TSG32_base                     0xFFBF8800UL

#define CTL0(n)                        REG08((n) + 0x0208UL)
#define CTL1(n)                        REG16((n) + 0x020CUL)
#define CTL3(n)                        REG08((n) + 0x0004UL)
#define CTL4(n)                        REG32((n) + 0x007CUL)
#define CTL5(n)                        REG16((n) + 0x0008UL)
#define CTL6(n)                        REG16((n) + 0x000CUL)
#define CTL7(n)                        REG08((n) + 0x0218UL)
#define CTL8(n)                        REG08((n) + 0x021CUL)
#define IOC0(n)                        REG08((n) + 0x0200UL)
#define IOC1(n)                        REG08((n) + 0x0204UL)
#define IOC2(n)                        REG16((n) + 0x0000UL)
#define IOC3(n)                        REG32((n) + 0x0074UL)
#define STR0(n)                        REG08((n) + 0x0010UL)
#define STR1(n)                        REG08((n) + 0x0014UL)
#define STR2(n)                        REG16((n) + 0x0018UL)
#define STC(n)                         REG16((n) + 0x001CUL)
#define OPT0(n)                        REG08((n) + 0x0020UL)
#define OPT1(n)                        REG08((n) + 0x0024UL)
#define OPT2(n)                        REG08((n) + 0x003CUL)
#define OPT2BF(n)                      REG08((n) + 0x00CCUL)
#define TRG0(n)                        REG08((n) + 0x0030UL)
#define TRG1(n)                        REG08((n) + 0x0034UL)
#define TRG2(n)                        REG08((n) + 0x0038UL)
#define CNT(n)                         REG16((n) + 0x0028UL)
#define CNTE(n)                        REG32((n) + 0x01A0UL)
#define SBC(n)                         REG16((n) + 0x002CUL)
#define SBCE(n)                        REG32((n) + 0x01A4UL)
#define CMP0(n)                        REG32((n) + 0x0058UL)
#define CMP0E(n)                       REG32((n) + 0x014CUL)
#define CMP1W(n)                       REG32((n) + 0x0040UL)
#define CMP5W(n)                       REG32((n) + 0x0044UL)
#define CMP9W(n)                       REG32((n) + 0x0048UL)
#define CMP3W(n)                       REG32((n) + 0x004CUL)
#define CMP7W(n)                       REG32((n) + 0x0050UL)
#define CMP11W(n)                      REG32((n) + 0x0054UL)
#define CMP1(n)                        REG16((n) + 0x0080UL)
#define CMP2(n)                        REG16((n) + 0x0084UL)
#define CMP3(n)                        REG16((n) + 0x0098UL)
#define CMP4(n)                        REG16((n) + 0x009CUL)
#define CMP5(n)                        REG16((n) + 0x0088UL)
#define CMP6(n)                        REG16((n) + 0x008CUL)
#define CMP7(n)                        REG16((n) + 0x00A0UL)
#define CMP8(n)                        REG16((n) + 0x00A4UL)
#define CMP9(n)                        REG16((n) + 0x0090UL)
#define CMP10(n)                       REG16((n) + 0x0094UL)
#define CMP11(n)                       REG16((n) + 0x00A8UL)
#define CMP12(n)                       REG16((n) + 0x00ACUL)
#define CMP1E(n)                       REG32((n) + 0x017CUL)
#define CMP2E(n)                       REG32((n) + 0x0178UL)
#define CMP3E(n)                       REG32((n) + 0x0164UL)
#define CMP4E(n)                       REG32((n) + 0x0160UL)
#define CMP5E(n)                       REG32((n) + 0x0174UL)
#define CMP6E(n)                       REG32((n) + 0x0170UL)
#define CMP7E(n)                       REG32((n) + 0x015CUL)
#define CMP8E(n)                       REG32((n) + 0x0158UL)
#define CMP9E(n)                       REG32((n) + 0x016CUL)
#define CMP10E(n)                      REG32((n) + 0x0168UL)
#define CMP11E(n)                      REG32((n) + 0x0154UL)
#define CMP12E(n)                      REG32((n) + 0x0150UL)
#define DCMP0W(n)                      REG32((n) + 0x005CUL)
#define DCMP2(n)                       REG32((n) + 0x0060UL)
#define DCMP0E(n)                      REG32((n) + 0x0148UL)
#define DCMP1E(n)                      REG32((n) + 0x0144UL)
#define DCMP2E(n)                      REG32((n) + 0x0140UL)
#define PAT0W(n)                       REG32((n) + 0x0064UL)
#define PAT1W(n)                       REG32((n) + 0x0068UL)
#define DTC0W(n)                       REG32((n) + 0x006CUL)
#define DTC1W(n)                       REG32((n) + 0x0070UL)
#define CMPU(n)                        REG16((n) + 0x00B0UL)
#define CMPV(n)                        REG16((n) + 0x00B4UL)
#define CMPW(n)                        REG16((n) + 0x00B8UL)
#define CMPUE(n)                       REG32((n) + 0x0188UL)
#define CMPVE(n)                       REG32((n) + 0x0184UL)
#define CMPWE(n)                       REG32((n) + 0x0180UL)
#define UPW(n)                         REG16((n) + 0x00BCUL)
#define VPW(n)                         REG16((n) + 0x00C0UL)
#define WPW(n)                         REG16((n) + 0x00C4UL)
#define UPWE(n)                        REG32((n) + 0x0198UL)
#define VPWE(n)                        REG32((n) + 0x0194UL)
#define WPWE(n)                        REG32((n) + 0x0190UL)
#define HSPSHWE(n)                     REG32((n) + 0x0120UL)
#define HSPSHVE(n)                     REG32((n) + 0x0124UL)
#define HSPSHUE(n)                     REG32((n) + 0x0128UL)
#define HSPCMWE(n)                     REG32((n) + 0x012CUL)
#define HSPCMVE(n)                     REG32((n) + 0x0130UL)
#define HSPCMUE(n)                     REG32((n) + 0x0134UL)
#define DTPR(n)                        REG16((n) + 0x0210UL)

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global functions
 *****************************************************************************/

#endif  /* R_TSG3_REG_H */