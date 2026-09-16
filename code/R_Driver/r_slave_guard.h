
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
#ifndef R_SLAVE_GUARD_H
#define R_SLAVE_GUARD_H

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_compiler.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define KCPROT_ON    0xA5A5A501U;
#define KCPROT_OFF   0xA5A5A500U;

#define SPID_CPU0     (0x01 << 0)
#define SPID_CPU1     (0x01 << 1)
#define SPID_CPU2     (0x01 << 2)
#define SPID_CPU3     (0x01 << 3)
#define SPID_CPU4     (0x01 << 4)
#define SPID_CPU5     (0x01 << 5)
#define SPID_GTM      (0x01 << 10)
#define SPID_EMU3S0   (0x01 << 11)
#define SPID_EMU3S1   (0x01 << 12)
#define SPID_SW       (0x01 << 13)
#define SPID_ACEU0    (0x01 << 14)
#define SPID_ACEU1    (0x01 << 15)
#define SPID_RHSIF1   (0x01 << 18)
#define SPID_RHSIF0   (0x01 << 19)
#define SPID_FLEXRAY0 (0x01 << 23)
#define SPID_ETND1    (0x01 << 24)
#define SPID_ETND0    (0x01 << 25)
#define SPID_ICUMHB   (0x01 << 26)
#define SPID_SDMAC1   (0x01 << 27)
#define SPID_SDMAC0   (0x01 << 28)

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/
typedef struct
{
    uint32 PBG_GuardErrorOverflowStatus;
    uint32 PBG_GuardErrorAddress;
    uint32 PBG_GuardErrorAccessInformation;
    uint32 PBG_GuardSPIDErrorStatus;
}tsPBG_GUARD_ERROR_INFO;

typedef enum
{
    nPBGERRSLV00    = 0u,
    nPBGERRSLV10    = 1u,
    nPBGERRSLV100   = 2u,
    nPBGERRSLV11H0  = 3u,
    nPBGERRSLV11L0  = 4u,
    nPBGERRSLV20    = 5u,
    nPBGERRSLV30    = 6u,
    nPBGERRSLV40    = 7u,
    nPBGERRSLV50    = 8u,
    nPBGERRSLV60    = 9u,
    nPBGERRSLV62    = 10u,
    nPBGERRSLV70    = 11u,
    nPBGERRSLV8H0   = 12u,
    nPBGERRSLV8L0   = 13u,
    nPBGERRSLV90    = 14u,
    nPBGERRSLV91    = 15u,
    nPBG_GroupMaxNum,

}tenPBG_GROUP;


/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global functions
 *****************************************************************************/
void R_PBG_Reassign_Permissions(void);
void R_PBG_CleanErrorStatus(void);
void R_PBG_GetErrorInfo(void);

#endif  /* R_SLAVE_GUARD_H */
