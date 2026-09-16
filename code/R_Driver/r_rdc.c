/*******************************************************************************
* Warranty Disclaimer :
*
* Because the Product(s) is licensed free of charge, there is no warranty of
* any kind whatsoever and expressly disclaimed and excluded by Renesas, either
* expressed or implied, including but not limited to those for non-infringement
* of intellectual property, merchantability and/or fitness for the particular
* purpose. Renesas shall not have any obligation to maintain, service or provide
* bug fixes for the supplied Product(s) and/or the Application.
*
* Each User is solely responsible for determining the appropriateness of using
* the Product(s) and assumes all risks associated with its exercise of rights
* under this Agreement, including, but not limited to the risks and costs of
* program errors, compliance with applicable laws, damage to or loss of data,
* programs or equipment, and unavailability or interruption of operations.
*
* Limitation of Liability :
*
* In no event shall Renesas be liable to the User for any incidental,
* consequential, indirect, or punitive damage (including but not limited to
* lost profits) regardless of whether such liability is based on breach of 
* contract, tort, strict liability, breach of warranties, failure of essential
* purpose or otherwise and even if advised of the possibility of such damages.
* Renesas shall not be liable for any services or products provided by third
* party vendors, developers or consultants identified or referred to the User
* by Renesas in connection with the Product(s) and/or the Application.
*
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/******************************************************************************
Includes <System Includes> , �gProject Includes�h
******************************************************************************/

#include "r_rdc.h" 
static float32 Rdc_Gsu2RdcAngleResult;
/******************************************************************************
* Function Name: RDC3AS0.Init
* Description  : RDC3AS0 initialise
* Arguments    : none
* Return Value : none
******************************************************************************/
void RDC3AS0_Init(void){
	
	
   volatile unsigned long dummy;
   volatile unsigned long phase_deray = 520;
   uint32 Lu4TimeDelayCnt = 0U;
    /* (1) ���� setting support register (RDC3ASnDSST) */ 
    /*   ����ADC group delay setting */
    /*   10us (F2) ,200kHz (F1b,F3b,F2,F4) */
    /*  DS-ADC setting F2 */
    RDC3AS0.DSST.UINT32 = 0x00000011UL; /*   ����ADC group delay setting 10us (F2) ,200kHz 200kHz (F1b,F3b,F2,F4)*/

    /* (2) Control Gain Select Register 0 (RDC3ASnPI0) */
    /* Control Gain Select  */
    /* DEVCK[2:0]  200-��s*1 clock period */
    /* BWCS=1, LPGS[2:0] 111= AUTO */
    RDC3AS0.PI0.UINT32 = 0x00020017UL;  /* Use AGC */
	
    /* (3) Control Gain Select Register 1 (RDC3ASnPI1) */
    /* 240000rpm 12bit(default)*/
    RDC3AS0.PI1.UINT32 = 0x00011B01UL;
	
    /* (4) PHI Compare Setting Register 0(RDC3ASnPHICP0) */
    /* (5) PHI Compare Setting Register 1(RDC3ASnPHICP1) */
    /* (6) PHI Compare Setting Register 2(RDC3ASnPHICP2) */
    // No setting
	
    /* (7) Sine/Cosine Angle Correction Register (RDC3ASnSCCOR0) */
    /* (8) Sine/Cosine Correction Register 1 (RDC3ASnSCCOR1)     */
    /* (9) Sine/Cosine Correction Register 2(RDC3ASnSCCOR2)      */
    /* (10) Sine/Cosine Correction Register 3 (RDC3ASnSCCOR3) */
    // No setting
	
    /* (11) Error Detection Register 0 (RDC3ASnDIAG0) */
    RDC3AS0.DIAG0.UINT32 = 0x001A2933UL;
		
    /* (12) Error Detection Register 1(RDC3ASnDIAG1) */
    RDC3AS0.DIAG1.UINT32 = 0xB0000000UL;
	
    /* (13) Error Detection Register 2 (RDC3ASnDIAG2) */
    RDC3AS0.DIAG2.UINT32 = 0x00800000UL;
		
    /* (14) Error Detection Output Register 0 (RDC3ASnDGOUT0) */
    /* (15) Error Detection Output Register 1 (RDC3ASnDGOUT1) */
    // No setting
	
    /* (16) BIST Register 0 (RDC3ASnBIST0) */
    /* (17) BIST Register 1 (RDC3ASnBIST1) */
    // No BIST Execute
    	
    /* (18) Excitation Setting Register (RDC3ASnREF) */
    /*   Excitation Extraction Noise Filter :Not Used */
    /*   Excitation component extraction function is enabled */
    /*   SENS AC Resolver */
    /*   EXIO AC Resolver */
    /*** for use TPBA IPTN ***/
    /*   REFINSL[1:0] Input excitation phase signal selection :01 select excitation phase signal from timer in LSI.  */
    /*   EXRFPSL excitation phase signal shape selection bit : 01 excitation period H pulse */
    /*   phase tune :input to dummy  1LSB = 50ns */
    dummy = 0x0A110000 + phase_deray; /* value of deray */
    RDC3AS0.REF.UINT32 = dummy;
	
    /* (19) Encoder Register 0 (RDC3ASnENC0) */
    /* Zero cross INT enable */
    RDC3AS0.ENC0.UINT32 = 0x00000120UL;
	

    /* (20) Encoder Register 1 (RDC3ASnENC1) */
    /* (21) Encoder Register 2 (RDC3ASnENC2)  */
    /* (22) Angular Velocity Register (RDC3ASnOMG) */
    /* (23) MNT Signal Register (RDC3ASnETC) */
    /* (24) Test Bus Register (RDC3ASnTBUS) */
    // No setting
	
    /* (25) ET Control Register (RDC3ASnETEN) */
    /* AD trig ON  & TE counter enable */
    RDC3AS0.ETEN.UINT32 =0x00050000;
    /* (26) ET Capture Register (RDC3ASnETCAP) */
    // No setting

    /* (27) ET Zero-Crossing Counter Register (RDC3ASnETMCNT) */
    // No setting
	
    /* (28) Error Detection Register 3 (RDC3ASnDIAG3) */
    /* (29) Error Detection Register 4 (RDC3ASnDIAG4) */
    // No setting
	
    /* (30) Debugging Read Register 0(RDC3ASnDBG0) */
    /* (31) Debugging Read Register 1 (RDC3ASnDBG1) */
    /* (32) Debugging Read Register 3 (RDC3ASnDBG3) */
	
    dummy = RDC3AS0.ENC0.UINT32;
    EXECUTE_SYNCP();

    /* RDC Start  */
	
    RDC3AS0.DIAG1.BIT.KIRST = 1; /*  Execute Ki reset */
    
    /* Wait for 5 msec */
    for (dummy = 0; dummy < 150000; dummy++){
        ASM_NOP();
    }
	
    RDC3AS0.DIAG1.BIT.ERDEN = 1; /*  Error detect enable */
    /* Wait for 26 msec */
    for (dummy = 0; dummy < 5200000U; dummy++){
        ASM_NOP();
    }
    RDC3AS0.DIAG1.BIT.SQERST = 1; /*  SQ reset */
    RDC3AS0.DIAG1.BIT.ERRST = 1;  /*  ERROR reset */
	
    dummy = RDC3AS0.ENC0.UINT32;
    EXECUTE_SYNCP();

}

uint16 RDC3AS0_GetCurrentPosition(void)
{
    return(RDC3AS0.ENC1.BIT.PHI);
}

float32 RDC3AS0_SamplePosition(void)
{
    Rdc_Gsu2RdcAngleResult = RDC3AS0.ENC1.BIT.PHI;
    Rdc_Gsu2RdcAngleResult = Rdc_Gsu2RdcAngleResult/65535*360;
    return (Rdc_Gsu2RdcAngleResult);
}

/******************************************************************************
* Function Name: dsadc_init
* Description  : DS_ADC initialise
* Arguments    : none
* Return Value : none
******************************************************************************/
void Dsadc_Init (void){
	

    /* AD Global setting */
    DSADC.ADGCR.UINT8 = 0x00;
	
    /* AD Local setting */
    Dsadc_Cos_Init();
    Dsadc_Sin_Init();
	
#ifdef USE_REF_ADC	
	dsadc_ref_init();
#endif	
	DSADC.SYNSTCR.BIT.ADSTART = 1; /* DSADC Start Synchronous */
	
}

/******************************************************************************
* Function Name: dsadc_cos_init
* Description  : COS DS_ADC ������
* Arguments    : none
* Return Value : none
******************************************************************************/
void Dsadc_Cos_Init (void){
	
    /* For DSDADC for RDC3AS0.COS:(S1-S3)  */
    /* RDC3AS0S1	DSAN150P:AN043	 */
    /* RDC3AS0S3	DSAN150N:AN041	 */
	
    /* DSADC15.VCR0 */
    /* 31 FSELEXTE Extended Fs switching bit =0 : Non-expanded Fs */
    /* 30 Reserved */
    /* 29, 28 GAIN[1:0] =00 :X1  */
    /* 27 VCULME Virtual Channel Upper-Limit Excess Notification =0 : not notified. */
    /* 26 VCLLME Virtual Channel Lower-Limit Excess Notification =0 : not notified. */
    /* 25, 24 VCULLMTBS =00 : Not used */
	//0000 0000 =0x00
    /* Case 3 (F2) : FSELEXTE=0 ,DSDFTYP=0, ORT =0 , TPVSL =2*/
    /* 23 ORT =0  */
    /* 22 to 20 TPVSL[2:0] =2 */
    /* 19 to 16 DSDFTYP[3:0] = 0 */
        // 0010 0000 =0x20
    /* 15 ADIE Conversion End Interrupt Enable =0 : Not output */
    /* 14 ULEIE Upper-Limit/Lower-Limit Error Interrupt Enable =0: Not output  */
    /* 13 Reserved */
    /* 12 DFENT DFE Entry =0: Entry is not performed. */
    /* 11 to 8 DFTAG[3:0] DFE-TAG : Not used */
        // 0000 0000 =0x00
    /* 7, 6 Reserved */
    /* 5, 4 CNVCLS[1:0] Conversion Type =2H: Differential input */
    /* 3 to 0 GCTRL[3:0] General Control 0H: DSANn0P/DSANn0N */
	// 00100000 =0x20
    DSADC15.VCR0.UINT32 = 0x00200020;
	
    /* STTRGE = 0, ENDTRGE = 0 , ADSTTE = 1 :A/D Synchronization Start Enable */
    DSADC15.ADTCR.UINT8 = 0x40;
	
    /* DSADC15.UCR */
    /* 31, 30 Reserved */
    /* 29 VPRSTE Virtual Channel Pointer Reset Enable = 0 */
    /* 28 RDMA Read Gate DMA Mode = 0 */
    /* 27 Reserved */
    /* 26 RESO0 High Resolution Mode 0: High resolution mode */
    /* 25 Reserved */
    /* 24 DFES = 0 */
        // 0000 0000 
    /* 23 to 12 Reserved */
	// 0000 0000 0000
    /* 11 to 8 DFMT[3:0] Data Format =0 : No masked */
    /* 7 to 3 Reserved */
    /* 2 to 0 VCEP[2:0] End Virtual Channel Pointer =0 : VC 0 only */
	// 0000 0000 0000
    DSADC15.UCR.UINT32 = 0x00000000;
	
    DSADC15.VCPTRR.UINT8 = 0x00; /* Pointer set to 0 */
	
    /* DIDEIE = 0 , PEIE = 0, OWEIE = 0, RDCLRE = 0 */
    DSADC15.SFTCR.UINT8 = 0x00;
	
}



/******************************************************************************
* Function Name: dsadc_sin_init
* Description  : SIN DS_ADC ������
* Arguments    : none
* Return Value : none
******************************************************************************/
void Dsadc_Sin_Init (void){
	/* For DSDADC for RDC3AS0.SIN:(S2-S4)  */
	/* RDC3AS0S2	DSAN003P:AN012	 */
        /* RDC3AS0S4	DSAN003N:AN013	 */
    
	/* 3 to 0 GCTRL[3:0] General Control 6H: DSANn3P/DSANn3N */
    DSADC00.VCR0.UINT32 = 0x00200026;
	DSADC00.ADTCR.UINT8 = 0x40;
	DSADC00.UCR.UINT32 = 0x00000000;
	DSADC00.VCPTRR.UINT8 = 0x00;
	DSADC00.SFTCR.UINT8 = 0x00;
	
}


/******************************************************************************
* Function Name: dsadc_ref_init
* Description  : REF DS_ADC ������
* Arguments    : none
* Return Value : none
******************************************************************************/
void Dsadc_Ref_Init (void){
	
	/* For DSDADC for RDC3AS0.Ref:(Ref1-Ref2)  */
	/* RDC3AS0EXP	DSAN130N:AN023	*/
        /* RDC3AS0EXN	DSAN130P:AN030	*/

    DSADC13.VCR0.UINT32 = 0x00200020;
	DSADC13.ADTCR.UINT8 = 0x40;
	DSADC13.UCR.UINT32 = 0x00000000;
	DSADC13.VCPTRR.UINT8 = 0x00;
	DSADC13.SFTCR.UINT8 = 0x00;

}

