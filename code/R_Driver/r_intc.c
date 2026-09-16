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
#include "r_intc.h"

#include "r_intc_reg.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/
R_INTC_UNINIT_INTERVAL[][2] = { {416U,  511u}, {298U, 347U}};
R_INTC_UNINIT_SINGLE[]   = { 0xFFFFU};

/*****************************************************************************
 Global static variables
 *****************************************************************************/

/*****************************************************************************
 Static functions
 *****************************************************************************/

/*****************************************************************************
--------------------- Global functions --------------------------------------
 *****************************************************************************/
/*****************************************************************************
 * Declaration : void R_INTC_Init(uint16 Pu2IntcX, uint16 Pu2Cfg)
 * Description : INTC Initialize.
 * Parameters  : Pu2IntcX - INTC number
 *               Pu2Cfg   - INTC configuration
 * Return      : None
 *****************************************************************************/
void R_INTC_Init(uint16 Pu2IntcX, uint16 Pu2Cfg)
{
    if (Pu2IntcX > 31UL)
    {
        INTC2_EIC(Pu2IntcX) = Pu2Cfg;
    }
    else
    {
        INTC1_EIC(Pu2IntcX) = Pu2Cfg;
    }
}
/*****************************************************************************
 * Declaration : void R_INTC_Bind(uint16 Pu2IntcX, uint32 Pu4Cfg)
 * Description : INTC Initialize.
 * Parameters  : Pu2IntcX - INTC number
 *               Pu4Cfg   - INTC configuration
 * Return      : None
 *****************************************************************************/
void R_INTC_Bind(uint16 Pu2IntcX, uint32 Pu4Cfg)
{
    if (Pu2IntcX > 31UL)
    {
        INTC2_EIBD(Pu2IntcX) = Pu4Cfg;
    }
    else
    {
        INTC1_EIBD(Pu2IntcX) = Pu4Cfg;
    }
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
void R_INTC_TptmSel(uint32 Pu4Cfg)
{
    TPTMSEL = Pu4Cfg;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
void R_INTC_Rlin3IntSel(uint8 Pu1Unit, uint32 Pu4Cfg)
{
    RLIN3INTSEL(Pu1Unit) = Pu4Cfg;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
void R_INTC_CanIntSel(uint8 Pu1Unit, uint32 Pu4Cfg)
{
    CANINTSEL(Pu1Unit) = Pu4Cfg;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
void R_INTC_Taud3IntNoSel(uint8 Pu1Unit, uint32 Pu4Cfg)
{
    TAUD3INTNOSEL(Pu1Unit) = Pu4Cfg;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
void R_INTC_Enca1IntNoSel0(uint32 Pu4Cfg)
{
    ENCA1INTNOSEL0 = Pu4Cfg;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
void R_INTC_TpbaIntNoSel0(uint32 Pu4Cfg)
{
    TPBAINTNOSEL0 = Pu4Cfg;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
void R_INTC_IntSysmResMon(uint32 Pu4Cfg)
{
    INTSYSMRESMON = Pu4Cfg;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
void R_INTC_IntQosMon(uint8 Pu1Unit, uint8 Pu1Chn, uint32 Pu4Cfg)
{
    INTQOSMON(Pu1Unit, Pu1Chn) = Pu4Cfg;
}

/*****************************************************************************
--------------------- Static functions --------------------------------------
 *****************************************************************************/
