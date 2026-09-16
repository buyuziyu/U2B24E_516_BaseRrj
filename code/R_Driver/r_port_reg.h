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
#ifndef R_PORT_REG_H
#define R_PORT_REG_H

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_compiler.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#define PORT             0xFFD90000UL
#define JPORT            0xFFDA0000UL

#define P(n)             REG16(PORT  + 0x0000UL + 0x40UL * (n))
#define AP(n)            REG16(PORT  + 0x0C80UL + 0x40UL * (n))  
#define JP(n)            REG16(JPORT + 0x0000UL + 0x40UL * (n))    

#define PSR(n)           REG32(PORT  + 0x0004UL + 0x40UL * (n))
#define APSR(n)          REG32(PORT  + 0x0C84UL + 0x40UL * (n))  
#define JPSR(n)          REG32(JPORT + 0x0004UL + 0x40UL * (n))   

#define PNOT(n)          REG16(PORT  + 0x0008UL + 0x40UL * (n))
#define APNOT(n)         REG16(PORT  + 0x0C88UL + 0x40UL * (n))  
#define JPNOT(n)         REG16(JPORT + 0x0008UL + 0x40UL * (n)) 

#define PPR(n)           REG16(PORT  + 0x000CUL + 0x40UL * (n))
#define APPR(n)          REG16(PORT  + 0x0C8CUL + 0x40UL * (n))  
#define JPPR(n)          REG16(JPORT + 0x000CUL + 0x40UL * (n)) 

#define PM(n)            REG16(PORT  + 0x0010UL + 0x40UL * (n))
#define APM(n)           REG16(PORT  + 0x0C90UL + 0x40UL * (n))  
#define JPM(n)           REG16(JPORT + 0x0010UL + 0x40UL * (n)) 

#define PMC(n)           REG16(PORT  + 0x0014UL + 0x40UL * (n))
#define JPMC(n)          REG16(JPORT + 0x0014UL + 0x40UL * (n)) 

#define PFC(n)           REG16(PORT  + 0x0018UL + 0x40UL * (n))
#define JPFC(n)          REG16(JPORT + 0x0018UL + 0x40UL * (n)) 

#define PFCE(n)          REG16(PORT  + 0x001CUL + 0x40UL * (n))
#define JPFCE(n)         REG16(JPORT + 0x001CUL + 0x40UL * (n)) 

#define PMSR(n)          REG32(PORT  + 0x0020UL + 0x40UL * (n))
#define APMSR(n)         REG32(PORT  + 0x0CA0UL + 0x40UL * (n))  
#define JPMSR(n)         REG32(JPORT + 0x0020UL + 0x40UL * (n)) 

#define PMCSR(n)         REG32(PORT  + 0x0024UL + 0x40UL * (n))
#define JPMCSR(n)        REG32(JPORT + 0x0024UL + 0x40UL * (n)) 

#define PFCAE(n)         REG16(PORT  + 0x0028UL + 0x40UL * (n))

#define PINV(n)          REG16(PORT  + 0x0030UL + 0x40UL * (n))
#define APINV(n)         REG16(PORT  + 0x0CB0UL + 0x40UL * (n))  
#define JPINV(n)         REG16(JPORT + 0x0030UL + 0x40UL * (n)) 

#define PIBC(n)          REG16(PORT  + 0x4000UL + 0x40UL * (n))
#define APIBC(n)         REG16(PORT  + 0x4C80UL + 0x40UL * (n))  
#define JPIBC(n)         REG16(JPORT + 0x4000UL + 0x40UL * (n))  

#define PBDC(n)          REG16(PORT  + 0x4004UL + 0x40UL * (n))
#define APBDC(n)         REG16(PORT  + 0x4C84UL + 0x40UL * (n))  
#define JPBDC(n)         REG16(JPORT + 0x4004UL + 0x40UL * (n))  

#define PIPC(n)          REG16(PORT  + 0x4008UL + 0x40UL * (n))

#define PU(n)            REG16(PORT  + 0x400CUL + 0x40UL * (n))
#define JPU(n)           REG16(JPORT + 0x400CUL + 0x40UL * (n))  

#define PD(n)            REG16(PORT  + 0x4010UL + 0x40UL * (n))
#define JPD(n)           REG16(JPORT + 0x4010UL + 0x40UL * (n))  

#define PODC(n)          REG16(PORT  + 0x4014UL + 0x40UL * (n))
#define APODC(n)         REG16(PORT  + 0x4C94UL + 0x40UL * (n))  
#define JPODC(n)         REG16(JPORT + 0x4014UL + 0x40UL * (n)) 

#define PDSC(n)          REG16(PORT  + 0x4018UL + 0x40UL * (n))
#define APDSC(n)         REG16(PORT  + 0x4C98UL + 0x40UL * (n))  
#define JPDSC(n)         REG16(JPORT + 0x4018UL + 0x40UL * (n)) 

#define PIS(n)           REG16(PORT  + 0x401CUL + 0x40UL * (n))
#define JPIS(n)          REG16(JPORT + 0x401CUL + 0x40UL * (n)) 

#define PISA(n)          REG16(PORT  + 0x4024UL + 0x40UL * (n))
#define JPISA(n)         REG16(JPORT + 0x4024UL + 0x40UL * (n)) 

#define PUCC(n)          REG16(PORT  + 0x4028UL + 0x40UL * (n))
#define JPUCC(n)         REG16(JPORT + 0x4028UL + 0x40UL * (n)) 

#define PODCE(n)         REG16(PORT  + 0x4038UL + 0x40UL * (n))
#define APODCE(n)        REG16(PORT  + 0x4CB8UL + 0x40UL * (n))  
#define JPODCE(n)        REG16(JPORT + 0x4038UL + 0x40UL * (n))  

#define PCR(n,m)         REG32(PORT  + 0x2000UL + 0x40UL * (n) + 0x04UL * (m))
#define APCR(n,m)        REG32(PORT  + 0x2C80UL + 0x40UL * (n) + 0x04UL * (m))
#define JPCR(n,m)        REG32(JPORT + 0x2000UL + 0x40UL * (n) + 0x04UL * (m))

#define PSFC(n)          REG16(PORT  + 0x6000UL + 0x40UL * (n))
#define APSFC(n)         REG16(PORT  + 0x6C80UL + 0x40UL * (n)) 

#define PSFTS(n)         REG16(PORT  + 0x6010UL + 0x40UL * (n))
#define APSFTS(n)        REG16(PORT  + 0x6C90UL + 0x40UL * (n)) 

#define PSFTSE(n)        REG16(PORT  + 0x6014UL + 0x40UL * (n))
#define APSFTSE(n)       REG16(PORT  + 0x6C94UL + 0x40UL * (n)) 

#define PKCPROT          REG32(PORT  + 0x2F40UL)
#define PWE              REG32(PORT  + 0x2F44UL)
#define LVDSCTRLA        REG32(PORT  + 0x2F50UL)
#define LVDSCTRLB        REG32(PORT  + 0x2F54UL)

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global functions
 *****************************************************************************/

#endif  /* R_PORT_REG_H */
