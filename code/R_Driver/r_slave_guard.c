
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
#include "r_slave_guard.h"
#include "r_slave_guard_reg.h"

#include "r_stbc.h"
#include "r_intc.h"


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

/*****************************************************************************
 Static functions
 *****************************************************************************/

/*****************************************************************************
--------------------- Global functions --------------------------------------
 *****************************************************************************/
/*****************************************************************************
 * Declaration : 
 * Description : 
 * Parameters  : 
 * Return      : 
 *****************************************************************************/
void R_PBG_Reassign_Permissions(void)
{
    uint32 Lu4Peid;
    uint32 u32IndexI;

    Lu4Peid = GetPEID();
    if (PE_CPU0 == (Lu4Peid & 0x1FUL))
    {
        /************************* PEG_KCPROT ON *************************/
        PBG_KCPROT(PBGERRSLV00_base)    = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV10_base)    = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV100_base)   = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV11H0_base)  = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV11L0_base)  = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV20_base)    = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV30_base)    = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV40_base)    = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV50_base)    = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV60_base)    = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV62_base)    = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV70_base)    = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV8H0_base)   = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV8L0_base)   = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV90_base)    = KCPROT_ON;			
        PBG_KCPROT(PBGERRSLV91_base)    = KCPROT_ON;			


        /* P-Bus Group 101 */
        PBG_PROT1(PBG101_base, 0) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);

        /* P-Bus Group 11H2 */
        PBG_PROT1(PBG101_base, 0) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
        PBG_PROT1(PBG101_base, 1) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);

        /* P-Bus Group 10/24 */
        for(u32IndexI = 0u; u32IndexI < 2u; u32IndexI++)
        {
            PBG_PROT1(PBG10_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG24_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
        }

        /* P-Bus Group 62/71/91 */
        for(u32IndexI = 0u; u32IndexI < 3u; u32IndexI++)
        {
            PBG_PROT1(PBG62_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG71_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG91_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
        }

        /* P-Bus Group 32/60 */
        for(u32IndexI = 0u; u32IndexI < 6u; u32IndexI++)
        {
            PBG_PROT1(PBG32_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG60_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
        }

        /* P-Bus Group 92 */
        for(u32IndexI = 0u; u32IndexI < 7u; u32IndexI++)
        {
            PBG_PROT1(PBG92_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
        }

        /* P-Bus Group 61/11L0 */
        for(u32IndexI = 0u; u32IndexI < 8u; u32IndexI++)
        {
            PBG_PROT1(PBG61_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG11L0_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
        }

        /* P-Bus Group 90 */
        for(u32IndexI = 0u; u32IndexI < 9u; u32IndexI++)
        {
            PBG_PROT1(PBG90_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
        }

        /* P-Bus Group 00/8H0 */
        for(u32IndexI = 0u; u32IndexI < 10u; u32IndexI++)
        {
            PBG_PROT1(PBG00_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG8H0_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
        }
        
        /* P-Bus Group 01 */
        for(u32IndexI = 0u; u32IndexI < 13u; u32IndexI++)
        {
            PBG_PROT1(PBG01_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
        }

        /* P-Bus Group 41 */
        for(u32IndexI = 0u; u32IndexI < 14u; u32IndexI++)
        {
            PBG_PROT1(PBG41_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
        }

        /* P-Bus Group 20/21/22/23/30/31/40/50/51/70/8L0/100/11H0/11L0 */
        for(u32IndexI = 0u; u32IndexI < 15u; u32IndexI++)
        {
            PBG_PROT1(PBG20_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG21_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG22_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG23_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG30_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG31_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG40_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG50_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG51_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG70_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG8L0_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG100_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
            PBG_PROT1(PBG11H0_base, u32IndexI) |= (SPID_CPU0 | SPID_CPU1 | SPID_CPU2 | SPID_CPU3 | SPID_SDMAC1 | SPID_SDMAC0);
        }

        PBG_KCPROT(PBGERRSLV00_base)    = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV10_base)    = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV100_base)   = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV11H0_base)  = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV11L0_base)  = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV20_base)    = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV30_base)    = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV40_base)    = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV50_base)    = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV60_base)    = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV62_base)    = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV70_base)    = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV8H0_base)   = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV8L0_base)   = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV90_base)    = KCPROT_OFF;			
        PBG_KCPROT(PBGERRSLV91_base)    = KCPROT_OFF;	
        /************************* PEG_KCPROT OFF *************************/

        /* Key Code Protection */
        // PEG_KCPROT(PEGPE0CL0_base) = KCPROT_ON;
        // PEG_PEGSPID(PEGPE0CL0_base, 0) = 0x1800000f;
        // PEG_PEGSPID(PEGPE0CL0_base, 1) = 0x1800000f;
        // PEG_PEGSPID(PEGPE0CL0_base, 2) = 0x1800000f;
        // PEG_PEGSPID(PEGPE0CL0_base, 3) = 0x1800000f;
        // PEG_PEGSPID(PEGPE0CL0_base, 4) = 0x1800000f;
        // PEG_PEGSPID(PEGPE0CL0_base, 5) = 0x1800000f;
        // PEG_PEGSPID(PEGPE0CL0_base, 6) = 0x1800000f;
        // PEG_PEGSPID(PEGPE0CL0_base, 7) = 0x1800000f;
        // PEG_KCPROT(PEGPE0CL0_base) = KCPROT_OFF;
    }
}

tsPBG_GUARD_ERROR_INFO PBG_GuardErrorInfo[nPBG_GroupMaxNum];


void R_PBG_GetErrorInfo(void)
{
    PBG_GuardErrorInfo[nPBGERRSLV00].PBG_GuardErrorOverflowStatus       = PBG_OVFSTAT(PBGERRSLV00_base);
    PBG_GuardErrorInfo[nPBGERRSLV10].PBG_GuardErrorOverflowStatus       = PBG_OVFSTAT(PBGERRSLV10_base);
    PBG_GuardErrorInfo[nPBGERRSLV100].PBG_GuardErrorOverflowStatus      = PBG_OVFSTAT(PBGERRSLV100_base);
    PBG_GuardErrorInfo[nPBGERRSLV11H0].PBG_GuardErrorOverflowStatus     = PBG_OVFSTAT(PBGERRSLV11H0_base);
    PBG_GuardErrorInfo[nPBGERRSLV11L0].PBG_GuardErrorOverflowStatus     = PBG_OVFSTAT(PBGERRSLV11L0_base);
    PBG_GuardErrorInfo[nPBGERRSLV20].PBG_GuardErrorOverflowStatus       = PBG_OVFSTAT(PBGERRSLV20_base);
    PBG_GuardErrorInfo[nPBGERRSLV30].PBG_GuardErrorOverflowStatus       = PBG_OVFSTAT(PBGERRSLV30_base);
    PBG_GuardErrorInfo[nPBGERRSLV40].PBG_GuardErrorOverflowStatus       = PBG_OVFSTAT(PBGERRSLV40_base);
    PBG_GuardErrorInfo[nPBGERRSLV50].PBG_GuardErrorOverflowStatus       = PBG_OVFSTAT(PBGERRSLV50_base);
    PBG_GuardErrorInfo[nPBGERRSLV60].PBG_GuardErrorOverflowStatus       = PBG_OVFSTAT(PBGERRSLV60_base);
    PBG_GuardErrorInfo[nPBGERRSLV62].PBG_GuardErrorOverflowStatus       = PBG_OVFSTAT(PBGERRSLV62_base);
    PBG_GuardErrorInfo[nPBGERRSLV70].PBG_GuardErrorOverflowStatus       = PBG_OVFSTAT(PBGERRSLV70_base);
    PBG_GuardErrorInfo[nPBGERRSLV8H0].PBG_GuardErrorOverflowStatus      = PBG_OVFSTAT(PBGERRSLV8H0_base);
    PBG_GuardErrorInfo[nPBGERRSLV8L0].PBG_GuardErrorOverflowStatus      = PBG_OVFSTAT(PBGERRSLV8L0_base);
    PBG_GuardErrorInfo[nPBGERRSLV90].PBG_GuardErrorOverflowStatus       = PBG_OVFSTAT(PBGERRSLV90_base);
    PBG_GuardErrorInfo[nPBGERRSLV91].PBG_GuardErrorOverflowStatus       = PBG_OVFSTAT(PBGERRSLV91_base);

    PBG_GuardErrorInfo[nPBGERRSLV00].PBG_GuardErrorAddress              = PBG_ERRADDR(PBGERRSLV00_base);
    PBG_GuardErrorInfo[nPBGERRSLV10].PBG_GuardErrorAddress              = PBG_ERRADDR(PBGERRSLV10_base);
    PBG_GuardErrorInfo[nPBGERRSLV100].PBG_GuardErrorAddress             = PBG_ERRADDR(PBGERRSLV100_base);
    PBG_GuardErrorInfo[nPBGERRSLV11H0].PBG_GuardErrorAddress            = PBG_ERRADDR(PBGERRSLV11H0_base);
    PBG_GuardErrorInfo[nPBGERRSLV11L0].PBG_GuardErrorAddress            = PBG_ERRADDR(PBGERRSLV11L0_base);
    PBG_GuardErrorInfo[nPBGERRSLV20].PBG_GuardErrorAddress              = PBG_ERRADDR(PBGERRSLV20_base);
    PBG_GuardErrorInfo[nPBGERRSLV30].PBG_GuardErrorAddress              = PBG_ERRADDR(PBGERRSLV30_base);
    PBG_GuardErrorInfo[nPBGERRSLV40].PBG_GuardErrorAddress              = PBG_ERRADDR(PBGERRSLV40_base);
    PBG_GuardErrorInfo[nPBGERRSLV50].PBG_GuardErrorAddress              = PBG_ERRADDR(PBGERRSLV50_base);
    PBG_GuardErrorInfo[nPBGERRSLV60].PBG_GuardErrorAddress              = PBG_ERRADDR(PBGERRSLV60_base);
    PBG_GuardErrorInfo[nPBGERRSLV62].PBG_GuardErrorAddress              = PBG_ERRADDR(PBGERRSLV62_base);
    PBG_GuardErrorInfo[nPBGERRSLV70].PBG_GuardErrorAddress              = PBG_ERRADDR(PBGERRSLV70_base);
    PBG_GuardErrorInfo[nPBGERRSLV8H0].PBG_GuardErrorAddress             = PBG_ERRADDR(PBGERRSLV8H0_base);
    PBG_GuardErrorInfo[nPBGERRSLV8L0].PBG_GuardErrorAddress             = PBG_ERRADDR(PBGERRSLV8L0_base);
    PBG_GuardErrorInfo[nPBGERRSLV90].PBG_GuardErrorAddress              = PBG_ERRADDR(PBGERRSLV90_base);
    PBG_GuardErrorInfo[nPBGERRSLV91].PBG_GuardErrorAddress              = PBG_ERRADDR(PBGERRSLV91_base);    

    PBG_GuardErrorInfo[nPBGERRSLV00].PBG_GuardErrorAccessInformation    = PBG_ERRTYPE(PBGERRSLV00_base);
    PBG_GuardErrorInfo[nPBGERRSLV10].PBG_GuardErrorAccessInformation    = PBG_ERRTYPE(PBGERRSLV10_base);
    PBG_GuardErrorInfo[nPBGERRSLV100].PBG_GuardErrorAccessInformation   = PBG_ERRTYPE(PBGERRSLV100_base);
    PBG_GuardErrorInfo[nPBGERRSLV11H0].PBG_GuardErrorAccessInformation  = PBG_ERRTYPE(PBGERRSLV11H0_base);
    PBG_GuardErrorInfo[nPBGERRSLV11L0].PBG_GuardErrorAccessInformation  = PBG_ERRTYPE(PBGERRSLV11L0_base);
    PBG_GuardErrorInfo[nPBGERRSLV20].PBG_GuardErrorAccessInformation    = PBG_ERRTYPE(PBGERRSLV20_base);
    PBG_GuardErrorInfo[nPBGERRSLV30].PBG_GuardErrorAccessInformation    = PBG_ERRTYPE(PBGERRSLV30_base);
    PBG_GuardErrorInfo[nPBGERRSLV40].PBG_GuardErrorAccessInformation    = PBG_ERRTYPE(PBGERRSLV40_base);
    PBG_GuardErrorInfo[nPBGERRSLV50].PBG_GuardErrorAccessInformation    = PBG_ERRTYPE(PBGERRSLV50_base);
    PBG_GuardErrorInfo[nPBGERRSLV60].PBG_GuardErrorAccessInformation    = PBG_ERRTYPE(PBGERRSLV60_base);
    PBG_GuardErrorInfo[nPBGERRSLV62].PBG_GuardErrorAccessInformation    = PBG_ERRTYPE(PBGERRSLV62_base);
    PBG_GuardErrorInfo[nPBGERRSLV70].PBG_GuardErrorAccessInformation    = PBG_ERRTYPE(PBGERRSLV70_base);
    PBG_GuardErrorInfo[nPBGERRSLV8H0].PBG_GuardErrorAccessInformation   = PBG_ERRTYPE(PBGERRSLV8H0_base);
    PBG_GuardErrorInfo[nPBGERRSLV8L0].PBG_GuardErrorAccessInformation   = PBG_ERRTYPE(PBGERRSLV8L0_base);
    PBG_GuardErrorInfo[nPBGERRSLV90].PBG_GuardErrorAccessInformation    = PBG_ERRTYPE(PBGERRSLV90_base);
    PBG_GuardErrorInfo[nPBGERRSLV91].PBG_GuardErrorAccessInformation    = PBG_ERRTYPE(PBGERRSLV91_base);

    PBG_GuardErrorInfo[nPBGERRSLV00].PBG_GuardSPIDErrorStatus           = PBG_SPIDERRSTAT(PBGERRSLV00_base);
    PBG_GuardErrorInfo[nPBGERRSLV10].PBG_GuardSPIDErrorStatus           = PBG_SPIDERRSTAT(PBGERRSLV10_base);
    PBG_GuardErrorInfo[nPBGERRSLV100].PBG_GuardSPIDErrorStatus          = PBG_SPIDERRSTAT(PBGERRSLV100_base);
    PBG_GuardErrorInfo[nPBGERRSLV11H0].PBG_GuardSPIDErrorStatus         = PBG_SPIDERRSTAT(PBGERRSLV11H0_base);
    PBG_GuardErrorInfo[nPBGERRSLV11L0].PBG_GuardSPIDErrorStatus         = PBG_SPIDERRSTAT(PBGERRSLV11L0_base);
    PBG_GuardErrorInfo[nPBGERRSLV20].PBG_GuardSPIDErrorStatus           = PBG_SPIDERRSTAT(PBGERRSLV20_base);
    PBG_GuardErrorInfo[nPBGERRSLV30].PBG_GuardSPIDErrorStatus           = PBG_SPIDERRSTAT(PBGERRSLV30_base);
    PBG_GuardErrorInfo[nPBGERRSLV40].PBG_GuardSPIDErrorStatus           = PBG_SPIDERRSTAT(PBGERRSLV40_base);
    PBG_GuardErrorInfo[nPBGERRSLV50].PBG_GuardSPIDErrorStatus           = PBG_SPIDERRSTAT(PBGERRSLV50_base);
    PBG_GuardErrorInfo[nPBGERRSLV60].PBG_GuardSPIDErrorStatus           = PBG_SPIDERRSTAT(PBGERRSLV60_base);
    PBG_GuardErrorInfo[nPBGERRSLV62].PBG_GuardSPIDErrorStatus           = PBG_SPIDERRSTAT(PBGERRSLV62_base);
    PBG_GuardErrorInfo[nPBGERRSLV70].PBG_GuardSPIDErrorStatus           = PBG_SPIDERRSTAT(PBGERRSLV70_base);
    PBG_GuardErrorInfo[nPBGERRSLV8H0].PBG_GuardSPIDErrorStatus          = PBG_SPIDERRSTAT(PBGERRSLV8H0_base);
    PBG_GuardErrorInfo[nPBGERRSLV8L0].PBG_GuardSPIDErrorStatus          = PBG_SPIDERRSTAT(PBGERRSLV8L0_base);
    PBG_GuardErrorInfo[nPBGERRSLV90].PBG_GuardSPIDErrorStatus           = PBG_SPIDERRSTAT(PBGERRSLV90_base);
    PBG_GuardErrorInfo[nPBGERRSLV91].PBG_GuardSPIDErrorStatus           = PBG_SPIDERRSTAT(PBGERRSLV91_base);
}


void R_PBG_CleanErrorStatus(void)
{
    PBG_OVFCLR(PBGERRSLV00_base)        = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV10_base)        = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV100_base)       = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV11H0_base)      = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV11L0_base)      = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV20_base)        = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV30_base)        = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV40_base)        = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV50_base)        = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV60_base)        = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV62_base)        = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV70_base)        = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV8H0_base)       = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV8L0_base)       = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV90_base)        = 0x00000002UL;
    PBG_OVFCLR(PBGERRSLV91_base)        = 0x00000002UL;

    PBG_SPIDERRCLR(PBGERRSLV00_base)    = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV10_base)    = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV100_base)   = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV11H0_base)  = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV11L0_base)  = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV20_base)    = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV30_base)    = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV40_base)    = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV50_base)    = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV60_base)    = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV62_base)    = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV70_base)    = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV8H0_base)   = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV8L0_base)   = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV90_base)    = 0xFFFFFFFFUL;
    PBG_SPIDERRCLR(PBGERRSLV91_base)    = 0xFFFFFFFFUL;

}


/*****************************************************************************
--------------------- Static functions --------------------------------------
 *****************************************************************************/
