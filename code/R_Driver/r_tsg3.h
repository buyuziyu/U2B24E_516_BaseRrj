
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
#ifndef R_TSG3_H
#define R_TSG3_H

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_compiler.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/

#define TSG3_DWD                    R_LSH(1UL, 4UL)
#define TSG3_MD(n)                  R_LSH((n), 0UL)
#define TSG3_TBA2                   R_LSH(1UL, 9UL)
#define TSG3_TBA1                   R_LSH(1UL, 8UL)
#define TSG3_TBA0                   R_LSH(1UL, 7UL)
#define TSG3_PPC                    R_LSH(1UL, 6UL)
#define TSG3_PEC                    R_LSH(1UL, 5UL)
#define TSG3_TDC                    R_LSH(1UL, 4UL)
#define TSG3_NDC                    R_LSH(1UL, 3UL)
#define TSG3_PRC                    R_LSH(1UL, 2UL)
#define TSG3_PTC(n)                 R_LSH((n), 0UL)
#define TSG3_RIA                    R_LSH(1UL, 1UL)
#define TSG3_RMC                    R_LSH(1UL, 0UL)
#define TSG3_PRE                    R_LSH(1UL, 8UL)
#define TSG3_VRE                    R_LSH(1UL, 7UL)
#define TSG3_PIE                    R_LSH(1UL, 6UL)
#define TSG3_VIE                    R_LSH(1UL, 5UL)
#define TSG3_RCC(n)                 R_LSH((n), 0UL)
#define TSG3_ACC(n)                 R_LSH((n), 10UL)
#define TSG3_AT09                   R_LSH(1UL, 9UL)
#define TSG3_AT08                   R_LSH(1UL, 8UL)
#define TSG3_AT07                   R_LSH(1UL, 7UL)
#define TSG3_AT06                   R_LSH(1UL, 6UL)
#define TSG3_AT05                   R_LSH(1UL, 5UL)
#define TSG3_AT04                   R_LSH(1UL, 4UL)
#define TSG3_AT03                   R_LSH(1UL, 3UL)
#define TSG3_AT02                   R_LSH(1UL, 2UL)
#define TSG3_AT01                   R_LSH(1UL, 1UL)
#define TSG3_AT00                   R_LSH(1UL, 0UL)
#define TSG3_AT19                   R_LSH(1UL, 9UL)
#define TSG3_AT18                   R_LSH(1UL, 8UL)
#define TSG3_AT17                   R_LSH(1UL, 7UL)
#define TSG3_AT16                   R_LSH(1UL, 6UL)
#define TSG3_AT15                   R_LSH(1UL, 5UL)
#define TSG3_AT14                   R_LSH(1UL, 4UL)
#define TSG3_AT13                   R_LSH(1UL, 3UL)
#define TSG3_AT12                   R_LSH(1UL, 2UL)
#define TSG3_AT11                   R_LSH(1UL, 1UL)
#define TSG3_AT10                   R_LSH(1UL, 0UL)
#define TSG3_SPSTL2                 R_LSH(1UL, 2UL)
#define TSG3_SPSTL1                 R_LSH(1UL, 1UL)
#define TSG3_SPSTL0                 R_LSH(1UL, 0UL)
#define TSG3_S120DCO                R_LSH(1UL, 0UL)
#define TSG3_TOE6                   R_LSH(1UL, 6UL)
#define TSG3_TOE5                   R_LSH(1UL, 5UL)
#define TSG3_TOE4                   R_LSH(1UL, 4UL)
#define TSG3_TOE3                   R_LSH(1UL, 3UL)
#define TSG3_TOE2                   R_LSH(1UL, 2UL)
#define TSG3_TOE1                   R_LSH(1UL, 1UL)
#define TSG3_PTS                    R_LSH(1UL, 4UL)
#define TSG3_EOC                    R_LSH(1UL, 3UL)
#define TSG3_WOC                    R_LSH(1UL, 2UL)
#define TSG3_TGS                    R_LSH(1UL, 1UL)
#define TSG3_TOS                    R_LSH(1UL, 0UL)
#define TSG3_OL6                    R_LSH(1UL, 14UL)
#define TSG3_OL5                    R_LSH(1UL, 13UL)
#define TSG3_OL4                    R_LSH(1UL, 12UL)
#define TSG3_OL3                    R_LSH(1UL, 11UL)
#define TSG3_OL2                    R_LSH(1UL, 10UL)
#define TSG3_OL1                    R_LSH(1UL, 9UL)
#define TSG3_TO6                    R_LSH(1UL, 6UL)
#define TSG3_TO5                    R_LSH(1UL, 5UL)
#define TSG3_TO4                    R_LSH(1UL, 4UL)
#define TSG3_TO3                    R_LSH(1UL, 3UL)
#define TSG3_TO2                    R_LSH(1UL, 2UL)
#define TSG3_TO1                    R_LSH(1UL, 1UL)
#define TSG3_TOL6                   R_LSH(1UL, 6UL)
#define TSG3_TOL5                   R_LSH(1UL, 5UL)
#define TSG3_TOL4                   R_LSH(1UL, 4UL)
#define TSG3_TOL3                   R_LSH(1UL, 3UL)
#define TSG3_TOL2                   R_LSH(1UL, 2UL)
#define TSG3_TOL1                   R_LSH(1UL, 1UL)
#define TSG3_SOC                    R_LSH(1UL, 6UL)
#define TSG3_STE                    R_LSH(1UL, 5UL)
#define TSG3_POT                    R_LSH(1UL, 4UL)
#define TSG3_PSS                    R_LSH(1UL, 3UL)
#define TSG3_IDC                    R_LSH(1UL, 2UL)
#define TSG3_PSC                    R_LSH(1UL, 1UL)
#define TSG3_SPC(n)                 R_LSH((n), 0UL)
#define TSG3_ESSC                   R_LSH(1UL, 0UL)

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/
typedef struct STag_Tsg3_InitCfgType
{
    /* Control Register */
    uint8  u1CTL0;
    uint16 u2CTL1;
    uint8  u1CTL3;
    uint32 u4CTL4;
    uint16 u2CTL5;
    uint16 u2CTL6;
    uint8  u1CTL7;
    uint8  u1CTL8;
    /* I/O Control  */
    uint8  u1IOC0;
    uint8  u1IOC1;
    uint16 u2IOC2;
    uint32 u4IOC3;
    /* Option Register */
    uint8  u1OPT0;
    uint8  u1OPT1;
    uint8  u1OPT2;
    /* Dead Time Protection */
    uint16 u2DTPR;
}Tsg3_InitCfg;
typedef struct STag_Tsg3_DutyType
{
    float32 f4DutyU;
    float32 f4DutyV;
    float32 f4DutyW;
}Tsg3_Duty;
typedef struct STag_Tsg3_DeadtimeType
{
    float32 f4OnUs;
    float32 f4OffUs;
}Tsg3_Deadtime;

typedef struct STag_Tsg3_AdDelayType
{
    float32 f4DCMP0EUs;
    float32 f4DCMP1EUs;
    float32 f4DCMP2EUs;
}Tsg3_AdDelay;


/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global functions
 *****************************************************************************/
uint8 R_TSG3_Init(uint8 Pu1Unit, Tsg3_InitCfg PstInitCfg);
uint8 R_TSG3_SetFrequency(uint8 Pu1Unit, uint32 Pu4Frequency);
uint8 R_TSG3_SetDuty(uint8 Pu1Unit, Tsg3_Duty PstDuty);
uint8 R_TSG3_SetDeadTime(uint8 Pu1Unit, Tsg3_Deadtime PstDeadtime, uint16 Pu2CodeValue);
uint8 R_TSG3_SetAdDelay(uint8 Pu1Unit, Tsg3_AdDelay PstAdDelay);
uint8 R_TSG3_SetSoc(uint8 Pu1Unit, uint8 Pu1Pattarn);
uint8 R_TSG3_ClrSoc(uint8 Pu1Unit);
uint8 R_TSG3_Start(uint8 Pu1Unit);
uint8 R_TSG3_Stop(uint8 Pu1Unit);
uint8 R_TSG3_DeadTime_Protection(uint8 Pu1Unit, uint8 Pu1En, uint16 Pu2CodeValue);

#endif  /* R_TSG3_H */