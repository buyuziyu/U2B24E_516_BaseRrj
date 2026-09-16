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
#include "r_clk.h"

#include "r_clk_reg.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define KCPROT_ENABLE          0xA5A5A501UL
#define KCPROT_DISABLE         0xA5A5A500UL

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/

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
 * Declaration : void R_CLK_Init(void)
 * Description : Clock Initialize.
 * Parameters  : None
 * Return      : None
 *****************************************************************************/
void R_CLK_Init(void)
{
    uint8 Lu1ReadTimes = 0U;

    CLKKCPROT1 = KCPROT_ENABLE;

    MOSCE = 0x01UL;

    while (0x03UL != MOSCS);

    do{
        if (0x03UL == MOSCS)
        {
            Lu1ReadTimes++;
        }
        else
        {
            Lu1ReadTimes = 0U;
        }
        
    } while (Lu1ReadTimes < 4U);

    PLLE = 0x01U;

    while (0x03UL != PLLS);

    Lu1ReadTimes = 0U;

    do{
        if (0x03UL == PLLS)
        {
            Lu1ReadTimes++;
        }
        else
        {
            Lu1ReadTimes = 0U;
        }
        
    } while (Lu1ReadTimes < 4U);

    CKSC_CPUC = 0x00UL;

    while (0x00UL != CKSC_CPUS);
    
    CLKKCPROT1 = KCPROT_DISABLE;
}

/*****************************************************************************
--------------------- Static functions --------------------------------------
 *****************************************************************************/
