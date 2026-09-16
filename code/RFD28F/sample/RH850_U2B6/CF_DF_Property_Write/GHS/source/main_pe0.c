/**********************************************************************************************************************
    Program Name    : Sample program for Renesas Flash Driver (RFD28F)
    
    File Name       : main_pe0.c
    Program Version : V1.00
    File Revision   : $Rev: 675 $
    File Date       : $Date:: 2019-03-29 18:08:31 +0900#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : Sample application for Renesas Flash Driver (RFD28F)
**********************************************************************************************************************/

/* !MISRA-C 2012 dir 1.1 (QAC message 0292) */

/**********************************************************************************************************************
    DISCLAIMER
    This software is supplied by Renesas Electronics Corporation and is only  intended for use with
    Renesas products. No other uses are authorized. This software is owned by Renesas Electronics
    Corporation and is protected under all applicable laws, including copyright laws.
    THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE,
    WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
    TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR
    ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR
    CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
    BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
    Renesas reserves the right, without notice, to make changes to this software and to discontinue the
    availability of this software. By using this software, you agree to the additional terms and conditions
    found by accessing the  following link:
    http://www.renesas.com/disclaimer
    
    Copyright (C) 2018-2023 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/

/* !MISRA-C 2012 rule 3.1 (QAC message 3108) */

/**********************************************************************************************************************
 *  MISRA-C 2012 Rule Violation
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 dir 1.1 / QAC message 0292
 *   Message      : Source file '%s' has comments containing one of the characters '$', '@' or '`'.
 *   Reason       : To support automatic insertion of revision by the source revision control system, it is necessary
 *                  to violate this rule, because the system uses non basic characters.
 *   Verification : The character '$' is used in comment only. Therefore, this rule violation is not influence code
 *                  compilation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule Dir-4.6 / QAC message 5209
 *   Message      : Use of basic type '%s'.
 *   Reason       : Since we have defined a main function for each PE, we have defined the return value as an
 *                  int type.
 *   Verification : Incorrect declaration would result in compilation fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 3.1 / QAC message 3108
 *   Message      : Nested comments are not recognized in the ISO standard.
 *   Reason       : Description "//" is a part of URL, so This does not apply.
 *   Verification : No violation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 8.4 / QAC message 3408
 *   Message      : '%s' has external linkage and is being defined without any previous declaration.
 *   Reason       : The corresponding point is not declared for access from multiple components. 
 *                  This is "version information" to be placed in the const attribute area and is declared so
 *                  as to acquire it directly from the corresponding area.
 *   Verification : Incorrect declaration would result in compilation fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 11.3 / QAC message 0310
 *   Message      : Casting to different object pointer type.
 *   Reason       : It is necessary to operate 4-byte data allocated at the 4-byte alignment address and 4-byte data
 *                  allocated at the not 4-byte aligned equally. In the latter case, it must copies to 4-byte
 *                  alignment address and processes, so casting to a different pointer type is required.
 *   Verification : The casts are essential for complete code execution.
 *                  Incorrect cast would result in compilation fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 11.3 / QAC message 3305
 *   Message      : Pointer cast to stricter alignment.
 *   Reason       : It is necessary to operate 4-byte data allocated at the 4-byte alignment address and 4-byte data
 *                  allocated at the not 4-byte aligned equally. In the latter case, it must copy to 4-byte
 *                  alignment address and processes, so casting to a different pointer type is required.
 *   Verification : The casts are essential for complete code execution.
 *                  Incorrect cast would result in compilation fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 11.4 / QAC message 0303
 *   Message      : Cast between a pointer to volatile object and an integral type.
 *   Reason       : In order to judge whether the address value of the pointer is odd or not, it is dared to cast to
 *                  an integer value. Since it is used only in this judgment part, so the intention is clear, there is
 *                  no influence on the operation.
 *   Verification : The converted addresses are essential for complete code execution.
 *                  Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule DCL00 / QAC message 3204
 *   Message      : The variable '%s' is only set once and so it could be declared with the 'const' qualifier.
 *   Reason       : The relevant part can be declared with const, but since it is easier to read
 *                  if it is implemented with code equivalent to the similar part, we will leave it as it is.
 *   Verification : No violation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule DCL06 / QAC message 3132
 *   Message      : Hard coded 'magic' number, '%s', used to define the size of an array.
 *   Reason       : The free area in the structure elements are defined, and the number of free bytes is the number of
 *                  array elements. The relevant part is a hardware dependent part, The free area location and
 *                  the number of free bytes also change depending on the hardware, and there is no point in defining
 *                  the number of elements separately, so this implementation method is adopted.
 *   Verification : Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule INT02 / QAC message 2100, 2101
 *   Message      : Understand integer conversion rules.
 *   Reason       : Since it can be confirmed that the corresponding operation result does not exceed the specified
 *                  type range, the correct operation result can be acquired without conversion to integer type.
 *                  So, there is no problem.
 *   Verification : Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule INT30 / QAC message 3383
 *   Message      : Cannot identify wraparound guard for unsigned arithmetic expression.
 *   Reason       : The corresponding operation result counts the number of FACIs present, and the increment result
 *                  cannot exceed the specified type range. So, there is no problem.
 *   Verification : Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

#include "sample_flash_control.h"

/* Sample data for writing to the data flash memory (4 bytes) */
R_RFD_ALIGN_VARIABLE_4

T_u1  bu1_WriteData[R_RFD_LENGTH_512BYTES]; /* Write data                                */
                                            /* !MISRA-C 2012 rule 8.4 (QAC message 3408) */

#define DFBLOCK_10_START            0xFF20A000UL
#define DFBLOCK_10_END              0xFF20AFFFUL
#define CFBLOCK_BANK_B_01_START     0x00300000UL
#define CFBLOCK_BANK_B_01_END       0x00303FFFUL
#define EXDATA_START                0xFF320000UL
#define EXDATA_END                  0xFF3207FFUL

#define R_RFD_FLMD_BASE             0xFFA00000UL                            /* FLMD base address */
#define R_RFD_REG_FLMD              (*(volatile T_u4 *)R_RFD_FLMD_BASE)

/* Prototype declaration */
int main(void); /* !QAC message 5209 */

/**********************************************************************************************************************
**  Function Name   : main
**  
**  - Outline
**      main function for PE0 sample program
**  - Format
**      int main(void);
**  - Input parameter
**      non
**  - Preconditions
**      No preconditions
**  - Return
**      R_RFD_TRUE  : Normal End
**      R_RFD_FALSE : Some error occured
**********************************************************************************************************************/

int
main(void)
{
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;                  /* Return value for this function        */
    T_u2            l_bu2_faciFequency;                 /* FACI Frequency                        */
                                                        /* !CERT-C rule DCL00 (QAC message 3204) */
    T_u4            l_bu4_loopCount;                    /* for loop count                        */
    T_u1            l_bu1_DFPEID[R_RFD_LENGTH_IDAUTH];  /* for authentification of DFPEID        */
    T_u1            l_bu1_CUSTIDx[R_RFD_LENGTH_IDAUTH]; /* for authentification of CUSTIDx       */
    T_bl            l_bl1_errorFlag;                    /* Error flag                            */
    T_bl            l_bl1_returnFlag;                   /* Return flag for main function         */
    
    T_u1*           l_bu1_writtenData;                  /* for written data                      */
    
    
    /* Initialization of the local variables */
    l_bu4_returnValue  = R_RFD_OK;
    l_bu2_faciFequency = 0xFFFFU;
    l_bu4_loopCount    = 0UL;
    l_bl1_errorFlag    = R_RFD_FALSE;
    l_bl1_returnFlag   = R_RFD_FALSE;
    l_bu1_writtenData  = 0UL;
    
    
    /* Create writing data */
    for (l_bu4_loopCount = 0UL; l_bu4_loopCount < 64UL; l_bu4_loopCount++)
    {
        bu1_WriteData[l_bu4_loopCount] = (T_u1)(0x10UL + l_bu4_loopCount); /* !CERT-C rule INT30 (QAC message 3383) */
    }
    
    /* Initialize RFD28F */
    l_bu4_returnValue = R_RFD_Init(l_bu2_faciFequency);
    
    if (l_bu4_returnValue != R_RFD_OK)
    {
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* FHVE Protect OFF (FACI0) */
        l_bu4_returnValue = R_RFD_SetFHVE(R_RFD_FACI0, R_RFD_FHVE_PROTECT_OFF);
        
        if (l_bu4_returnValue != R_RFD_OK)
        {
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* FHVE Protect OFF (FACI2) */
            l_bu4_returnValue = R_RFD_SetFHVE(R_RFD_FACI2, R_RFD_FHVE_PROTECT_OFF);
            
            if (l_bu4_returnValue != R_RFD_OK)
            {
                l_bl1_errorFlag = R_RFD_TRUE;
            }
            else
            {
                /* no operation */
            }
        }
    }
    else
    {
        /* no operation */
    }
    
    /******************************************************************************************************************
     *  Control Data Flash
     *****************************************************************************************************************/
    
    /**************************************************************************************************************
     *  Data Flash Control Component is valid or invalid ?
     *    - If the definition of "R_RFD_CONTROL_TARGET_DATAFLASH" is "R_RFD_DISABLE",
     *      Compiler output warning and no object is created by #warning directive.
     *************************************************************************************************************/
    
    /* !MISRA-C 2012 rule 20.13 (QAC message 3115) */
    #if (R_RFD_CONTROL_TARGET_DATAFLASH == R_RFD_DISABLE)
        #warning "Data Flash Control Component is invalidated in r_rfd_config.h"
    #else   /* R_RFD_CONTROL_TARGET_DATAFLASH == R_RFD_ENABLE */
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Authenticate DFPEID                      */
        /* In the case that all DFPEID is 0xFF      */
        for (l_bu4_loopCount = 0UL; l_bu4_loopCount < 32UL; l_bu4_loopCount++)
        {
            l_bu1_DFPEID[l_bu4_loopCount] = 0xFFU;
        }
        
        /* Initialize RFD28F */
        l_bu4_returnValue = R_RFD_DFIDAuth(l_bu1_DFPEID);
        
        if (l_bu4_returnValue != R_RFD_OK)
        {
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* no operation */
        }
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /*************************************/
        /*  Execute Sample_DataFlashControl  */
        /*************************************/
        l_bu4_returnValue = Sample_DataFlashControl((T_u4_RfdAddress)DFBLOCK_10_START,
                                                    (T_u4_RfdAddress)DFBLOCK_10_END,
                                                    (T_pu4_RfdBuffer)&bu1_WriteData[0]);
                                                    /* !MISRA-C 2012 rule 11.3 (QAC message 0310) */
                                                    /* !MISRA-C 2012 rule 11.3 (QAC message 3305) */
        
        /* Check return value */
        if (l_bu4_returnValue != R_RFD_OK)
        {
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* no operation */
        }
        
        /* Check written data for Data Flash */
        l_bu1_writtenData = (T_u1*)DFBLOCK_10_START;
        
        for (l_bu4_loopCount = 0UL; l_bu4_loopCount < 64UL; l_bu4_loopCount++)
        {
            if (l_bu1_writtenData[l_bu4_loopCount] != bu1_WriteData[l_bu4_loopCount])
            {
                l_bl1_errorFlag = R_RFD_TRUE;
                break;
            }
        }
    }
    else
    {
        /* no operation */
    }
    
    #endif /* R_RFD_CONTROL_TARGET_DATAFLASH == R_RFD_DISABLE */
    
    
    /******************************************************************************************************************
     *  Control Code Flash / Property Area / Extended Data Area
     *****************************************************************************************************************/
    
    /**************************************************************************************************************
     *  Code Flash Control Component is valid or invalid ?
     *    - If the definition of "R_RFD_CONTROL_TARGET_CODEFLASH" is "R_RFD_DISABLE",
     *      Compiler output warning and no object is created by #warning directive.
     *************************************************************************************************************/
    
    /* !MISRA-C 2012 rule 20.13 (QAC message 3115) */
    #if (R_RFD_CONTROL_TARGET_CODEFLASH == R_RFD_DISABLE)
        #warning "Code Flash Control Component is invalidated in r_rfd_config.h"
    #else   /* R_RFD_CONTROL_TARGET_CODEFLASH == R_RFD_ENABLE */
    
    /* Set the value to FLMD due to access to code flash */
    R_RFD_REG_FLMD = 0x00000001UL;      /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Code Flash Control */
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Authenticate CUSTIDA, CUSTIDB, CUSTIDC                     */
        /* In the case that all CUSTIDA, CUSTIDB and CUSTIDC are 0xFF */
        for (l_bu4_loopCount = 0UL; l_bu4_loopCount < 32UL; l_bu4_loopCount++)
        {
            l_bu1_CUSTIDx[l_bu4_loopCount] = 0xFFU;
        }
        
        /* Check all of CUSTIDA, CUSTIDB and CUSTIDC, and if any one return value */
        /* is not R_RFD_OK, enable error flag.                                    */
        
        /* Authenticate CUSTIDA */
        l_bu4_returnValue = R_RFD_IDAuth(R_RFD_ID_CUSTIDA, l_bu1_CUSTIDx);
        
        /* Check return value */
        if (l_bu4_returnValue != R_RFD_OK)
        {
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* no operation */
        }
        
        /* Authenticate CUSTIDB */
        l_bu4_returnValue = R_RFD_IDAuth(R_RFD_ID_CUSTIDB, l_bu1_CUSTIDx);
        
        /* Check return value */
        if (l_bu4_returnValue != R_RFD_OK)
        {
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* no operation */
        }
        
        /* Authenticate CUSTIDC */
        l_bu4_returnValue = R_RFD_IDAuth(R_RFD_ID_CUSTIDC, l_bu1_CUSTIDx);
        
        /* Check return value */
        if (l_bu4_returnValue != R_RFD_OK)
        {
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* no operation */
        }
        
    }
    else
    {
        /* no operation */
    }
    
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100)      s*/
    {
        /*************************************/
        /*  Execute Sample_CodeFlashControl  */
        /*************************************/
        l_bu4_returnValue = Sample_CodeFlashControl((T_u4_RfdAddress)CFBLOCK_BANK_B_01_START,
                                                    (T_u4_RfdAddress)CFBLOCK_BANK_B_01_END,
                                                    (T_pu4_RfdBuffer)&bu1_WriteData[0]);
                                                    /* !MISRA-C 2012 rule 11.3 (QAC message 0310) */
                                                    /* !MISRA-C 2012 rule 11.3 (QAC message 3305) */
        /* Check return value */
        if (l_bu4_returnValue != R_RFD_OK)
        {
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* no operation */
        }
        
        /* Check written data for Code Flash */
        l_bu1_writtenData = (T_u1*)CFBLOCK_BANK_B_01_START;
        
        for (l_bu4_loopCount = 0UL; l_bu4_loopCount < 64UL; l_bu4_loopCount++)
        {
            if (l_bu1_writtenData[l_bu4_loopCount] != bu1_WriteData[l_bu4_loopCount])
            {
                l_bl1_errorFlag = R_RFD_TRUE;
                break;
            }
        }
        
    }
    else
    {
        /* no operation */
    }
    
    /* Set the value to FLMD due to not access to code flash */
    R_RFD_REG_FLMD = 0x00000000UL;      /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Property Area Control */
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100)      s*/
    {
        /****************************************/
        /*  Execute Sample_PropertyAreaControl  */
        /****************************************/
        l_bu4_returnValue = Sample_PropertyAreaControl();
        
        /* Check return value */
        if (l_bu4_returnValue != R_RFD_OK)
        {
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* no operation */
        }
    }
    else
    {
        /* no operation */
    }
    
    
        /* Extended Data Area */
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100)      s*/
    {
        /****************************************/
        /*  Execute Sample_ExtendedDataControl  */
        /****************************************/
        l_bu4_returnValue = Sample_ExtendedDataControl((T_u4_RfdAddress)EXDATA_START,
                                                    (T_u4_RfdAddress)EXDATA_END,
                                                    (T_pu4_RfdBuffer)&bu1_WriteData[0]);
                                                    /* !MISRA-C 2012 rule 11.3 (QAC message 0310) */
                                                    /* !MISRA-C 2012 rule 11.3 (QAC message 3305) */
        /* Check return value */
        if (l_bu4_returnValue != R_RFD_OK)
        {
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* no operation */
        }
        
        /* Check written data for Data Flash */
        l_bu1_writtenData = (T_u1*)EXDATA_START;
        
        for (l_bu4_loopCount = 0UL; l_bu4_loopCount < 64UL; l_bu4_loopCount++)
        {
            if (l_bu1_writtenData[l_bu4_loopCount] != bu1_WriteData[l_bu4_loopCount])
            {
                l_bl1_errorFlag = R_RFD_TRUE;
                break;
            }
        }
    }
    else
    {
        /* no operation */
    }
    
    
    #endif /* R_RFD_CONTROL_TARGET_CODEFLASH == R_RFD_DISABLE */
    
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* FHVE Protect OFF (FACI0) */
        l_bu4_returnValue = R_RFD_SetFHVE(R_RFD_FACI0, R_RFD_FHVE_PROTECT_ON);
        
        if (l_bu4_returnValue != R_RFD_OK)
        {
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* FHVE Protect OFF (FACI2) */
            l_bu4_returnValue = R_RFD_SetFHVE(R_RFD_FACI2, R_RFD_FHVE_PROTECT_ON);
            
            if (l_bu4_returnValue != R_RFD_OK)
            {
                l_bl1_errorFlag = R_RFD_TRUE;
            }
            else
            {
                /* no operation */
            }
        }
    }
    else
    {
        /* no operation */
    }
    
    
    /* Set return value */
    if (l_bl1_errorFlag == R_RFD_FALSE)
    {
        l_bl1_returnFlag = R_RFD_TRUE;
    }
    else
    {
        l_bl1_returnFlag = R_RFD_FALSE;
    }
    
    return ((int)l_bl1_returnFlag); /* !QAC message 5209 */
    
}
