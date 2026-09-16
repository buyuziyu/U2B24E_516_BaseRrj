
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

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_tpba.h"
#include "r_tpba_reg.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global static variables
 *****************************************************************************/
static uint32 Gsu4atpba[] = {
    TPBA0_base,
    TPBA1_base
};
/*****************************************************************************
 Static functions
 *****************************************************************************/

 const unsigned short pattern_8bit[80] ={
    60,    //  0x3C	
    63,    //  0x3F	
    66,    //  0x42	
    68,    //  0x44	
    71,    //  0x47	
    74,    //  0x4A	
    76,    //  0x4C	
    79,    //  0x4F	
    81,    //  0x51	
    83,    //  0x53	
    85,    //  0x55	
    87,    //  0x57	
    89,    //  0x59	
    91,    //  0x5B	
    92,    //  0x5C	
    93,    //  0x5D	
    94,    //  0x5E	
    95,    //  0x5F	
    96,    //  0x60	
    96,    //  0x60	
    96,    //  0x60	
    96,    //  0x60	
    96,    //  0x60	
    95,    //  0x5F	
    94,    //  0x5E	
    93,    //  0x5D	
    92,    //  0x5C	
    91,    //  0x5B	
    89,    //  0x59	
    87,    //  0x57	
    85,    //  0x55	
    83,    //  0x53	
    81,    //  0x51	
    79,    //  0x4F	
    76,    //  0x4C	
    74,    //  0x4A	
    71,    //  0x47	
    68,    //  0x44	
    66,    //  0x42	
    63,    //  0x3F	
    60,    //  0x3C	
    57,    //  0x39	
    54,    //  0x36	
    52,    //  0x34	
    49,    //  0x31	
    46,    //  0x2E	
    44,    //  0x2C	
    41,    //  0x29	
    39,    //  0x27	
    37,    //  0x25	
    35,    //  0x23	
    33,    //  0x21	
    31,    //  0x1F	
    29,    //  0x1D	
    28,    //  0x1C	
    27,    //  0x1B	
    26,    //  0x1A	
    25,    //  0x19	
    24,    //  0x18	
    24,    //  0x18	
    24,    //  0x18	
    24,    //  0x18	
    24,    //  0x18	
    25,    //  0x19	
    26,    //  0x1A	
    27,    //  0x1B	
    28,    //  0x1C	
    29,    //  0x1D	
    31,    //  0x1F	
    33,    //  0x21	
    35,    //  0x23	
    37,    //  0x25	
    39,    //  0x27	
    41,    //  0x29	
    44,    //  0x2C	
    46,    //  0x2E	
    49,    //  0x31	
    52,    //  0x34	
    54,    //  0x36	
    57 };    //  0x39	
/*****************************************************************************
--------------------- Global functions --------------------------------------
 *****************************************************************************/
/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
void R_TPBA_Init(uint8 Pu1Unit, tpba_InitCfg PtsCfg)
{
    volatile unsigned short dummy;
    unsigned short* buff_prt;
    unsigned short  buff_temp0,buff_temp1,cnt_temp;

    TPBA_CTL(Gsu4atpba[Pu1Unit]) = PtsCfg.u1CTL;
    TPBA_TOE(Gsu4atpba[Pu1Unit]) = PtsCfg.u1TOE;
    TPBA_TOL(Gsu4atpba[Pu1Unit]) = PtsCfg.u1TOL;
    TPBA_CMP0(Gsu4atpba[Pu1Unit]) = PtsCfg.u1CMP0;    
    buff_prt = (unsigned short*)(&TPBA_BUF(Gsu4atpba[Pu1Unit], 0));
    
    for( dummy =0 ; dummy < 40 ; dummy++){  /* 2 data set in 1 loop */

            buff_temp0 = 0;
            buff_temp1 = 0;
    
            cnt_temp = dummy * 2; 
	    buff_temp0 = pattern_8bit[cnt_temp];
	    buff_temp1 = pattern_8bit[(cnt_temp+1)] << 8;
	    buff_temp0 = buff_temp0 | buff_temp1; 
	    *buff_prt = buff_temp0;
	    buff_prt +=2;
	    
    }
    TPBA_CMP1(Gsu4atpba[Pu1Unit])  = PtsCfg.u1CMP1;
}

void R_TPBA_Start(uint8 Pu1Unit)
{
    TPBA_RDT(Gsu4atpba[Pu1Unit]) = 0x01;
    TPBA_TS(Gsu4atpba[Pu1Unit]) = 0x01;
}

void R_TPBA_Stop(uint8 Pu1Unit)
{
    TPBA_TT(Gsu4atpba[Pu1Unit]) = 0x01;
}
/*****************************************************************************
--------------------- Static functions --------------------------------------
 *****************************************************************************/
