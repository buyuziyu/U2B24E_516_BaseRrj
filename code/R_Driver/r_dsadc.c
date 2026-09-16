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
#include    "r_dsadc.h" 
#include    "r_dsadc_reg.h" 
/*****************************************************************************
 Macro definitions
 *****************************************************************************/   
/*****************************************************************************
 Typedef definitions
 *****************************************************************************/  

/*****************************************************************************
 Global variables
 *****************************************************************************/
static uint32 Gsu4DsAdc[] = {
    DSADC00_base,
    DSADC10_base,
    DSADC20_base,
    DSADC12_base,
    DSADC13_base,
    DSADC11_base,
    DSADC15_base,
    DSADC14_base,
    DSADC22_base,
    DSADC21_base
};

/*****************************************************************************
 Global static variables
 *****************************************************************************/

/*****************************************************************************
 Static functions
 *****************************************************************************/
void R_DSADC_Init(uint8 Lu1DsadcUnit, DsadcCfg PuDsAdcCfg)
{
    /* Global Regist Setting */
    DSADCADGCR = PuDsAdcCfg.u1ADGCR;

    /* Delta-Sigma ADC Post-Filter 2nd Stage applied 2 */
    /* Conversion Type:Differential Input */
    /* Analog input channels are selected DSANn0P/DSANn0N */
    DSADC_VCR(Gsu4DsAdc[Lu1DsadcUnit],0) = PuDsAdcCfg.u4VCR;
    /* A/D Synchronization Start Enable */
    DSADC_ADTCR(Gsu4DsAdc[Lu1DsadcUnit]) = PuDsAdcCfg.u1ADTCR;

    DSADC_UCR(Gsu4DsAdc[Lu1DsadcUnit]) = PuDsAdcCfg.u4UCR;

    DSADC_VCPTRR(Gsu4DsAdc[Lu1DsadcUnit]) = PuDsAdcCfg.u1VCPTRR;

    DSADC_SFTCR(Gsu4DsAdc[Lu1DsadcUnit]) = PuDsAdcCfg.u1SFTCR;
}

void R_DSADC_Start(uint8 Lu1DsadcUnit)
{
    DSADCSYNSTCR = 0x01;
}


uint16 R_DSADC_GetData(uint8 Lu1DsadcUnit, uint8 Lu1DsChannel)
{
    static uint32 Gu4DsAdcValue = 0;
    static uint16 Lu2RetValue = 0;
    Gu4DsAdcValue = DSADC_DIR(Gsu4DsAdc[Lu1DsadcUnit],Lu1DsChannel);
    Lu2RetValue = (Gu4DsAdcValue >> ((DSADC_VCR(Gsu4DsAdc[Lu1DsadcUnit],Lu1DsChannel) >> 8) & 0xF)) & 0xFFFF;
    return Lu2RetValue;
}


