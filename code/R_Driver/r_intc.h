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
#ifndef R_INTC_H
#define R_INTC_H

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_compiler.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define INTC_EICT         (1UL << 15UL)
#define INTC_EIRF         (1UL << 12UL)
#define INTC_EIMK         (~(1UL << 7UL))
#define INTC_EITB         (1UL << 6UL)
#define INTC_EIOV         (1UL << 5UL)
#define INTC_EIP(n)       ((n) << 0UL)

#define INTC_CST          (1UL << 31UL)
#define INTC_BCP(n)       ((n) << 24UL)
#define INTC_GM           (1UL << 15UL)
#define INTC_GPID(n)      ((n) << 8UL)
#define INTC_PEID(n)      ((n) << 0UL)

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global functions
 *****************************************************************************/
void R_INTC_Init(uint16 Pu2IntcX, uint16 Pu2Cfg);
void R_INTC_Bind(uint16 Pu2IntcX, uint32 Pu4Cfg);

void R_INTC_TptmSel(uint32 Pu4Cfg);
void R_INTC_Rlin3IntSel(uint8 Pu1Unit, uint32 Pu4Cfg);
void R_INTC_CanIntSel(uint8 Pu1Unit, uint32 Pu4Cfg);
void R_INTC_Taud3IntNoSel(uint8 Pu1Unit, uint32 Pu4Cfg);
void R_INTC_Enca1IntNoSel0(uint32 Pu4Cfg);
void R_INTC_TpbaIntNoSel0(uint32 Pu4Cfg);
void R_INTC_IntSysmResMon(uint32 Pu4Cfg);
void R_INTC_IntQosMon(uint8 Pu1Unit, uint8 Pu1Chn, uint32 Pu4Cfg);

#endif  /* R_INTC_H */
