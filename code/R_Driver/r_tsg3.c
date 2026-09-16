
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
#include "r_tsg3.h"
#include "r_tsg3_reg.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define TSG3_CLK           80000000UL

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/
/* 80M / 1000 / 1000 = Us Count */
#define USCLKCount         ((TSG3_CLK / 1000) / 1000)

/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global static variables
 *****************************************************************************/
static uint32 Gsu4aTsg3[] = {
    TSG30_base,
    TSG31_base,
    TSG32_base,
};
static uint16 Gsu2aDtpr[3];

static uint32 Gu4TSG3Freq[3] = {
    0, 0, 0
};

static Tsg3_Duty GsuTSG3Duty[3] = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
};

static Tsg3_Deadtime GsuTSG3DeadTime[3] = {
    {0.0f, 0.0f},
    {0.0f, 0.0f},
    {0.0f, 0.0f},
};


/*****************************************************************************
 Static functions
 *****************************************************************************/
static void TSG3_PwmSetFrequencyCom(uint8 Pu1Unit, uint32 Pu4Frequency);
static void TSG3_HtPwmSetFrequency(uint8 Pu1Unit, uint32 Pu4Frequency);
static void (*GsfpPwmSetFrequency[])(uint8 Pu1Unit, uint32 Pu4Frequency) = {
    TSG3_PwmSetFrequencyCom,
    TSG3_HtPwmSetFrequency,
    TSG3_PwmSetFrequencyCom,
    TSG3_PwmSetFrequencyCom,
    TSG3_PwmSetFrequencyCom,
};

static void TSG3_PwmSetDuty(uint8 Pu1Unit, Tsg3_Duty PstDuty);
static void TSG3_HtPwmSetDuty(uint8 Pu1Unit, Tsg3_Duty PstDuty);
static void TSG3_SpPwmSetDuty(uint8 Pu1Unit, Tsg3_Duty PstDuty);
static void TSG3_120DcSetDuty(uint8 Pu1Unit, Tsg3_Duty PstDuty);
static void TSG3_HspPwmSetDuty(uint8 Pu1Unit, Tsg3_Duty PstDuty);
static void (*GsfpPwmSetDuty[])(uint8 Pu1Unit, Tsg3_Duty PstDuty) = {
    TSG3_PwmSetDuty,
    TSG3_HtPwmSetDuty,
    TSG3_SpPwmSetDuty,
    TSG3_120DcSetDuty,
    TSG3_HspPwmSetDuty,
};

static void TSG3_PwmSetDeadtimeCom(uint8 Pu1Unit, Tsg3_Deadtime PstDeadtime);
static void TSG3_HtPwmSetDeadtime(uint8 Pu1Unit, Tsg3_Deadtime PstDeadtime);
static void (*GsfpPwmSetDeadtime[])(uint8 Pu1Unit, Tsg3_Deadtime PstDeadtime) = {
    TSG3_PwmSetDeadtimeCom,
    TSG3_HtPwmSetDeadtime,
    TSG3_PwmSetDeadtimeCom,
    TSG3_PwmSetDeadtimeCom,
    TSG3_PwmSetDeadtimeCom,
};

static void TSG3_PwmSetAdDelayCom(uint8 Pu1Unit, Tsg3_AdDelay PstAdDelay);
static void TSG3_HtPwmSetAdDelay(uint8 Pu1Unit, Tsg3_AdDelay PstAdDelay);
static void (*GsfpPwmSetAdDelay[])(uint8 Pu1Unit, Tsg3_AdDelay PstAdDelay) = {
    TSG3_PwmSetAdDelayCom,
    TSG3_HtPwmSetAdDelay,
    TSG3_PwmSetAdDelayCom,
    TSG3_PwmSetAdDelayCom,
    TSG3_PwmSetAdDelayCom,
};

/*****************************************************************************
--------------------- Global functions --------------------------------------
 *****************************************************************************/
/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
uint8 R_TSG3_Init(uint8 Pu1Unit, Tsg3_InitCfg PstInitCfg)
{
    TRG1(Gsu4aTsg3[Pu1Unit]) = 0x01U;
    STC(Gsu4aTsg3[Pu1Unit])  = 0x0000U;
    CTL0(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u1CTL0;
    CTL1(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u2CTL1;
    CTL3(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u1CTL3;
    CTL4(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u4CTL4;
    CTL5(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u2CTL5;
    CTL6(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u2CTL6;
    CTL7(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u1CTL7;
    CTL8(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u1CTL8;
    IOC0(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u1IOC0;
    IOC1(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u1IOC1;
    IOC2(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u2IOC2;
    IOC3(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u4IOC3;
    OPT0(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u1OPT0;
    OPT1(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u1OPT1;
    OPT2(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u1OPT2;
    DTPR(Gsu4aTsg3[Pu1Unit]) = PstInitCfg.u2DTPR | 0x8000U;
    Gsu2aDtpr[Pu1Unit]       = PstInitCfg.u2DTPR;
    return R_OK;
}

uint8 R_TSG3_DeadTime_Protection(uint8 Pu1Unit, uint8 Pu1En, uint16 Pu2CodeValue)
{
    uint16 PRD_REG = ((!Pu1En) << 15) | (Pu2CodeValue & 0x7FFFU);
    DTPR(Gsu4aTsg3[Pu1Unit]) = PRD_REG;
    return R_OK;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
uint8 R_TSG3_SetFrequency(uint8 Pu1Unit, uint32 Pu4Frequency)
{
    Gu4TSG3Freq[Pu1Unit] = Pu4Frequency;
    (*GsfpPwmSetFrequency[CTL0(Gsu4aTsg3[Pu1Unit]) & 0x07U])(Pu1Unit, Gu4TSG3Freq[Pu1Unit]);
    return R_OK;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
uint8 R_TSG3_SetDuty(uint8 Pu1Unit, Tsg3_Duty PstDuty)
{
    GsuTSG3Duty[Pu1Unit].f4DutyU = PstDuty.f4DutyU;
    GsuTSG3Duty[Pu1Unit].f4DutyV = PstDuty.f4DutyV;
    GsuTSG3Duty[Pu1Unit].f4DutyW = PstDuty.f4DutyW;   
    (*GsfpPwmSetDuty[CTL0(Gsu4aTsg3[Pu1Unit]) & 0x07U])(Pu1Unit, GsuTSG3Duty[Pu1Unit]);
    return R_OK;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
uint8 R_TSG3_SetDeadTime(uint8 Pu1Unit, Tsg3_Deadtime PstDeadtime, uint16 Pu2CodeValue)
{
    GsuTSG3DeadTime[Pu1Unit].f4OffUs = PstDeadtime.f4OffUs;
    GsuTSG3DeadTime[Pu1Unit].f4OnUs = PstDeadtime.f4OnUs;
    Gsu2aDtpr[Pu1Unit] = Pu2CodeValue;
    //DTPR(Gsu4aTsg3[Pu1Unit]) &= 0x7FFFU;
    (*GsfpPwmSetDeadtime[CTL0(Gsu4aTsg3[Pu1Unit]) & 0x07U])(Pu1Unit, GsuTSG3DeadTime[Pu1Unit]);
    //DTPR(Gsu4aTsg3[Pu1Unit]) |= 0x8000U;
    return R_OK;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
uint8 R_TSG3_SetAdDelay(uint8 Pu1Unit, Tsg3_AdDelay PstAdDelay)
{
    (*GsfpPwmSetAdDelay[CTL0(Gsu4aTsg3[Pu1Unit]) & 0x07U])(Pu1Unit, PstAdDelay);
    return R_OK;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
uint8 R_TSG3_SetSoc(uint8 Pu1Unit, uint8 Pu1Pattarn)
{
    OPT1(Gsu4aTsg3[Pu1Unit]) = Pu1Pattarn & 0x07U;
    OPT0(Gsu4aTsg3[Pu1Unit]) = TSG3_SOC;
    return R_OK;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
uint8 R_TSG3_ClrSoc(uint8 Pu1Unit)
{
    OPT0(Gsu4aTsg3[Pu1Unit]) &= ~TSG3_SOC;
    return R_OK;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
uint8 R_TSG3_Start(uint8 Pu1Unit)
{
    TRG0(Gsu4aTsg3[Pu1Unit]) = 0x01U;
    return R_OK;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
uint8 R_TSG3_Stop(uint8 Pu1Unit)
{
    TRG1(Gsu4aTsg3[Pu1Unit]) = 0x01U;
    return R_OK;
}

/*****************************************************************************
--------------------- Static functions --------------------------------------
 *****************************************************************************/
/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
static void TSG3_PwmSetFrequencyCom(uint8 Pu1Unit, uint32 Pu4Frequency)
{
    CMP0E(Gsu4aTsg3[Pu1Unit]) = TSG3_CLK / Pu4Frequency - 1UL;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
static void TSG3_HtPwmSetFrequency(uint8 Pu1Unit, uint32 Pu4Frequency)
{
    CMP0E(Gsu4aTsg3[Pu1Unit]) = (TSG3_CLK / Pu4Frequency) & 0x3fffe;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
static void TSG3_PwmSetDuty(uint8 Pu1Unit, Tsg3_Duty PstDuty)
{

}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
static void TSG3_HtPwmSetDuty(uint8 Pu1Unit, Tsg3_Duty PstDuty)
{
    CMPUE(Gsu4aTsg3[Pu1Unit]) = (uint32)(PstDuty.f4DutyU * (CMP0E(Gsu4aTsg3[Pu1Unit]) + DTC0W(Gsu4aTsg3[Pu1Unit]) + DTC1W(Gsu4aTsg3[Pu1Unit]))) & 0x3fffe;
    CMPVE(Gsu4aTsg3[Pu1Unit]) = (uint32)(PstDuty.f4DutyV * (CMP0E(Gsu4aTsg3[Pu1Unit]) + DTC0W(Gsu4aTsg3[Pu1Unit]) + DTC1W(Gsu4aTsg3[Pu1Unit]))) & 0x3fffe;
    CMPWE(Gsu4aTsg3[Pu1Unit]) = (uint32)(PstDuty.f4DutyW * (CMP0E(Gsu4aTsg3[Pu1Unit]) + DTC0W(Gsu4aTsg3[Pu1Unit]) + DTC1W(Gsu4aTsg3[Pu1Unit]))) & 0x3fffe;
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
static void TSG3_SpPwmSetDuty(uint8 Pu1Unit, Tsg3_Duty PstDuty)
{
    UPWE(Gsu4aTsg3[Pu1Unit]) = (uint32)((1.0f - PstDuty.f4DutyU) * (CMP0E(Gsu4aTsg3[Pu1Unit]) + 1UL));
    VPWE(Gsu4aTsg3[Pu1Unit]) = (uint32)((1.0f - PstDuty.f4DutyV) * (CMP0E(Gsu4aTsg3[Pu1Unit]) + 1UL));
    WPWE(Gsu4aTsg3[Pu1Unit]) = (uint32)((1.0f - PstDuty.f4DutyW) * (CMP0E(Gsu4aTsg3[Pu1Unit]) + 1UL));
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
static void TSG3_120DcSetDuty(uint8 Pu1Unit, Tsg3_Duty PstDuty)
{

}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
static void TSG3_HspPwmSetDuty(uint8 Pu1Unit, Tsg3_Duty PstDuty)
{

}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
static void TSG3_PwmSetDeadtimeCom(uint8 Pu1Unit, Tsg3_Deadtime PstDeadtime)
{
    DTC0W(Gsu4aTsg3[Pu1Unit]) = (Gsu2aDtpr[Pu1Unit] << 16U) | (uint16)(PstDeadtime.f4OnUs  * USCLKCount);
    DTC1W(Gsu4aTsg3[Pu1Unit]) = (Gsu2aDtpr[Pu1Unit] << 16U) | (uint16)(PstDeadtime.f4OffUs * USCLKCount);
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
static void TSG3_HtPwmSetDeadtime(uint8 Pu1Unit, Tsg3_Deadtime PstDeadtime)
{
    DTC0W(Gsu4aTsg3[Pu1Unit]) = (Gsu2aDtpr[Pu1Unit] << 16U) | (uint16)(PstDeadtime.f4OnUs  * USCLKCount);
    DTC1W(Gsu4aTsg3[Pu1Unit]) = (Gsu2aDtpr[Pu1Unit] << 16U) | (uint16)(PstDeadtime.f4OffUs * USCLKCount);
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
static void TSG3_PwmSetAdDelayCom(uint8 Pu1Unit, Tsg3_AdDelay PstAdDelay)
{
    DCMP0E(Gsu4aTsg3[Pu1Unit]) = (uint32)(PstAdDelay.f4DCMP0EUs * USCLKCount);
    DCMP1E(Gsu4aTsg3[Pu1Unit]) = (uint32)(PstAdDelay.f4DCMP1EUs * USCLKCount);
    DCMP2E(Gsu4aTsg3[Pu1Unit]) = (uint32)(PstAdDelay.f4DCMP2EUs * USCLKCount);
}

/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
static void TSG3_HtPwmSetAdDelay(uint8 Pu1Unit, Tsg3_AdDelay PstAdDelay)
{
    DCMP0E(Gsu4aTsg3[Pu1Unit]) = (uint32)(PstAdDelay.f4DCMP0EUs * USCLKCount);
    DCMP1E(Gsu4aTsg3[Pu1Unit]) = (uint32)(PstAdDelay.f4DCMP1EUs * USCLKCount);
    DCMP2E(Gsu4aTsg3[Pu1Unit]) = (uint32)(PstAdDelay.f4DCMP2EUs * USCLKCount);
}
