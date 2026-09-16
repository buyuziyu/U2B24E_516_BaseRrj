
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
#ifndef R_SLAVE_GUARD_REG_H
#define R_SLAVE_GUARD_REG_H

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "r_compiler.h"

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#ifdef  __RH850_U2A__
#define PBG00_base	        0xFFC6B080UL
#define PBG01_base	        0xFFC6B100UL
#define PBG10_base	        0xFFC63000UL
#define PBG20_base	        0xFFDE0B00UL
#define PBG21_base	        0xFFDE0C00UL
#define PBG22_base	        0xFFDE0D00UL
#define PBG30_base	        0xFFC72B00UL
#define PBG31_base	        0xFFC72C00UL
#define PBG32_base	        0xFFC72D00UL
#define PBG33_base	        0xFFC72E00UL
#define PBG40_base	        0xFFC75300UL
#define PBG50_base	        0xFFC7A300UL
#define PBG51_base	        0xFFC7A400UL
#define PBG52_base	        0xFFC7A500UL
#define PBG53_base	        0xFFC7A600UL
#define PBG6H0_base	        0xFF751000UL
#define PBG6L0_base	        0xFFC81000UL
#define PBG6L1_base	        0xFFC81200UL
#define PBG70_base	        0xFFF49400UL
#define PBG80_base	        0xFFF29300UL
#define PBG90_base	        0xFF0A1300UL

#define PBGERRSLV00_base	0xFFC6B000UL
#define PBGERRSLV10_base	0xFFC63100UL
#define PBGERRSLV20_base	0xFFDE1000UL
#define PBGERRSLV30_base	0xFFC73200UL
#define PBGERRSLV40_base	0xFFC75400UL
#define PBGERRSLV50_base	0xFFC7B000UL
#define PBGERRSLV6H0_base	0xFF752000UL
#define PBGERRSLV6L0_base	0xFFC83000UL
#define PBGERRSLV6L1_base	0xFFC83040UL
#define PBGERRSLV70_base	0xFFF4A000UL
#define PBGERRSLV80_base	0xFFF2A000UL
#define PBGERRSLV90_base	0xFF0A1400UL
#endif



#ifdef  __RH850_U2B__
#define PBG00_base	        0xFFC6B080UL
#define PBG01_base	        0xFFC6B100UL
#define PBG10_base	        0xFFC63000UL
#define PBG100_base	        0xFF879400UL
#define PBG101_base	        0xFF879500UL
#define PBG11H0_base	    0xFF8B1400UL
#define PBG11H1_base	    0xFF8B1600UL
#define PBG11H2_base	    0xFF8B1800UL
#define PBG11L0_base	    0xFF8F8000UL
#define PBG20_base	        0xFFDE0B00UL
#define PBG21_base	        0xFFDE0C00UL
#define PBG22_base	        0xFFDE0D00UL
#define PBG23_base	        0xFFDE0E00UL
#define PBG24_base	        0xFFDE1200UL
#define PBG30_base	        0xFFC72B00UL
#define PBG31_base	        0xFFC72C00UL
#define PBG32_base	        0xFFC72D00UL
#define PBG40_base	        0xFFC75300UL
#define PBG41_base	        0xFFC75380UL
#define PBG50_base	        0xFFC7A300UL
#define PBG51_base	        0xFFC7A400UL
#define PBG52_base	        0xFFC7A500UL
#define PBG60_base	        0xFFC81000UL
#define PBG61_base	        0xFFC81200UL
#define PBG62_base	        0xFFC82000UL
#define PBG70_base	        0xFFF49400UL
#define PBG71_base	        0xFFF49600UL
#define PBG8H0_base	        0xFFF29300UL
#define PBG8L0_base	        0xFF97A000UL
#define PBG90_base	        0xFF0A1300UL
#define PBG91_base	        0xFF0A1500UL
#define PBG92_base	        0xFF0A1700UL

#define PBG_ATU_base	    0xFF88FA00UL
#define PBG_CANFD0_base	    0xFF860000UL
#define PBG_CANFD1_base	    0xFF860800UL
#define PBG_GTM_base	    0xFFF60000UL

#define PBGERRSLV00_base	0xFFC6B000UL
#define PBGERRSLV10_base	0xFFC63100UL
#define PBGERRSLV100_base	0xFF87A000UL
#define PBGERRSLV11H0_base	0xFF8B2000UL
#define PBGERRSLV11L0_base	0xFF8F8100UL
#define PBGERRSLV20_base	0xFFDE1000UL
#define PBGERRSLV30_base	0xFFC73200UL
#define PBGERRSLV40_base	0xFFC75400UL
#define PBGERRSLV50_base	0xFFC7B000UL
#define PBGERRSLV60_base	0xFFC83000UL
#define PBGERRSLV62_base	0xFFC83040UL
#define PBGERRSLV70_base	0xFFF4A000UL
#define PBGERRSLV8H0_base	0xFFF2A000UL
#define PBGERRSLV8L0_base	0xFF97A200UL
#define PBGERRSLV90_base	0xFF0A1400UL
#define PBGERRSLV91_base	0xFF0A1600UL
#endif



#ifdef  __RH850_U2C__
#define PBG00_base	        0xFFC6B080UL
#define PBG01_base	        0xFFC6B100UL
#define PBG10_base	        0xFFC63000UL
#define PBG20_base	        0xFFDE0B00UL
#define PBG21_base	        0xFFDE0C00UL
#define PBG22_base	        0xFFDE0D00UL
#define PBG30_base	        0xFFC72B00UL
#define PBG31_base	        0xFFC72C00UL
#define PBG40_base	        0xFFC75300UL
#define PBG41_base	        0xFFC75380UL
#define PBG50_base	        0xFFC7A300UL
#define PBG51_base	        0xFFC7A400UL
#define PBG52_base	        0xFFC7A500UL
#define PBG60_base	        0xFFC81000UL
#define PBG61_base	        0xFFC81200UL
#define PBG7H0_base	        0xFFF4D400UL
#define PBG7L0_base	        0xFFF49400UL
#define PBG8H0_base	        0xFFF29300UL
#define PBG8L0_base	        0xFF97A000UL
#define PBG90_base	        0xFF0A1300UL
#define PBG91_base	        0xFF0A1500UL
#define PBG100_base	        0xFF879400UL
#define PBG101_base	        0xFF879500UL
#define PBG11H0_base	    0xFF8B1400UL
#define PBG11H1_base	    0xFF8B1600UL
#define PBG11L0_base	    0xFF8F8000UL
#define PBG_CANFD0_base     0xFF860000UL
#define PBG_CANFD1_base     0xFF860800UL
#define PBG_ATU_base        0xFF88FA00UL
#define PBG_GTM_base        0xFFF60000UL

#define PBGERRSLV00_base	0xFFC6B000UL
#define PBGERRSLV10_base	0xFFC63100UL
#define PBGERRSLV20_base	0xFFDE1000UL
#define PBGERRSLV30_base	0xFFC73200UL
#define PBGERRSLV40_base	0xFFC75400UL
#define PBGERRSLV50_base	0xFFC7B000UL
#define PBGERRSLV60_base	0xFFC83000UL
#define PBGERRSLV61_base	0xFFC83040UL
#define PBGERRSLV7H0_base	0xFFF4E000UL
#define PBGERRSLV7L0_base	0xFFF4A000UL
#define PBGERRSLV8H0_base	0xFFF2A000UL
#define PBGERRSLV8L0_base	0xFF97A200UL
#define PBGERRSLV90_base	0xFF0A1400UL
#define PBGERRSLV91_base	0xFF0A1600UL
#define PBGERRSLV100_base	0xFF87A000UL
#define PBGERRSLV11H0_base	0xFF8B2000UL
#define PBGERRSLV11L0_base	0xFF8F8100UL
#endif



#define PBG_OVFCLR(Group)                   REG32((Group) + 0x00UL)
#define PBG_OVFSTAT(Group)                  REG32((Group) + 0x04UL)
#define PBG_ERRADDR(Group)                  REG32((Group) + 0x08UL)
#define PBG_ERRTYPE(Group)                  REG32((Group) + 0x0CUL)
#define PBG_SPIDERRCLR(Group)               REG32((Group) + 0x10UL)
#define PBG_SPIDERRSTAT(Group)              REG32((Group) + 0x14UL)
#define PBG_KCPROT(Group)                   REG32((Group) + 0x18UL)

#define PBG_PROT0(Group, Channel)           REG32((Group) + (0x08UL * Channel))
#define PBG_PROT1(Group, Channel)           REG32((Group) + (0x08UL * Channel) + 0x04UL)

#define PBG_CFDAS(Group, Channel)           REG32((Group) + (0x04UL * Channel))
#define PBG_ATUAS(Group, Channel)           REG32((Group) + (0x04UL * Channel))
#define PBG_GTMAS(Group, Channel)           REG32((Group) + (0x04UL * Channel))


#define PEGPE0CL0_base                      0xFFC6C000
#define PEG_KCPROT(Group)                   REG32(Group)
#define PEG_PEGSPID(Group, Channel)         REG32((Group) + 0x44UL + (Channel * 0x10))

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global functions
 *****************************************************************************/

#endif  /* R_SLAVE_GUARD_REG_H */
