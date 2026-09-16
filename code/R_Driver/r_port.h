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
#ifndef R_PORT_H
#define R_PORT_H

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_compiler.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#ifndef HIGH
  #define HIGH      1
#endif

#ifndef LOW
  #define LOW       0
#endif

#define PORT_PINV                    0x40000000U
#define PORT_PODC                    0x10000000U
#define PORT_PODCE                   0x08000000U
#define PORT_PUCC                    0x02000000U
#define PORT_PDSC                    0x01000000U
#define PORT_PISA                    0x00400000U
#define PORT_PIS                     0x00100000U
#define PORT_PU                      0x00080000U
#define PORT_PD                      0x00040000U
#define PORT_PBDC                    0x00020000U
#define PORT_PIBC                    0x00010000U
#define PORT_P                       0x00001000U
#define PORT_PPR                     0x00000100U
#define PORT_PMC                     0x00000040U
#define PORT_PIPC                    0x00000020U
#define PORT_PM                      0x00000010U
#define PORT_APF1                    0x00000000U
#define PORT_APF2                    0x00000001U
#define PORT_APF3                    0x00000002U
#define PORT_APF4                    0x00000003U
#define PORT_APF5                    0x00000004U
#define PORT_APF6                    0x00000005U
#define PORT_APF7                    0x00000006U
#define PORT_APF8                    0x00000007U
#define PORT_APF9                    0x00000008U
#define PORT_APF10                   0x00000009U
#define PORT_APF11                   0x0000000AU
#define PORT_APF12                   0x0000000BU
#define PORT_APF13                   0x0000000CU
#define PORT_APF14                   0x0000000DU
#define PORT_APF15                   0x0000000EU
#define PORT_APF16                   0x0000000FU

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global functions
 *****************************************************************************/
extern void R_PORT_EnablePort(void);
extern void R_PORT_DisablePort(void);
extern void R_PORT_Init(uint8 Pu1Port, uint8 Pu1Pin, uint32 Pu4Setting);
extern uint32 R_PORT_ReadPin(uint8 Pu1Port, uint8 Pu1Pin);
extern uint32 R_PORT_ReadPort(uint8 Pu1Port);
extern void R_PORT_WritePin(uint8 Pu1Port, uint8 Pu1Pin, uint8 Pu1State);
extern void R_PORT_WritePort(uint8 Pu1Port, uint16 Pu1Value);
extern void R_PORT_FlipPin(uint8 Pu1Port, uint8 Pu1Pin);
extern void R_PORT_FlipPort(uint8 Pu1Port);

#endif  /* PORT_H */
