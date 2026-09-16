/**************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
*
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
***************************************************************************/

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_tapa.h"
#include "r_tapa_reg.h"
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
static const uint32 Gscu4Tapa[] = {
    TAPA0_BASE,
    TAPA1_BASE,
    TAPA2_BASE,
    TAPA3_BASE,
    TAPA4_BASE,
    TAPA5_BASE,
};

/*****************************************************************************
 Static functions
 *****************************************************************************/

/*****************************************************************************
 Global functions
 *****************************************************************************/
void R_Drv_TAPA_ESO_Init(void)
{
    /* TAPA3ESO  TSG30 */
    CTL0(Gscu4Tapa[3]) = 0x14UL;
    ACWE(Gscu4Tapa[3]) = 0x01UL;
    ACTS(Gscu4Tapa[3]) = 0x01UL;
}


void R_Drv_TAPA_HIZ_Clear(void)
{
    /* TAPA3ESO  TSG30 */
    OPHT(Gscu4Tapa[3]) = 0x01UL;
}

