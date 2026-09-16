/**********************************************************************************************************************
    Program Name    : Sample program for Renesas Flash Driver (RFD28F)
    
    File Name       : sample_control_property.c
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
 *   Rule         : MISRA-C 2012 rule 11.4 / QAC message 0303
 *   Message      : Cast between a pointer to volatile object and an integral type.
 *   Reason       : For effective embedded programming, integer to pointer conversions are used.
 *   Verification : The converted addresses are essential for complete code execution.
 *                  Incorrect conversion would result in test fails.
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
 *   Rule         : MISRA-C 2012 rule 18.4 / QAC message 0488
 *   Message      : Performing pointer arithmetic.
 *   Reason       : Since the writing unit of data is determined to be 32bytes, it is necessary to move the pointer to
 *                  32 bytes after writing one data, and this calculation is performed.
 *   Verification : Incorrect calculation would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : No MISRA-C 2012 or CERT-C rule / QAC message 0776
 *   Message      : External identifier matches other external identifier(s) (e.g. '%s')
 *                  in first 6 characters - program does not conform strictly to ISO:C90.
 *   Reason       : "R_RFD_" is defined as a string necessary to recognize that it is an API of RFD provided
 *                  by Renesas to distinguish it from other APIs. Furthermore, since both the external identifier and
 *                  the internal identifier do not exceed 31 characters, the minimum requirement of valid characters
 *                  is satisfied and it is determined that there is no problem.
 *   Verification : Incorrect API name would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : No MISRA-C 2012 rule / QAC message 3120
 *   Message      : Hard-coded 'magic' integer constant, '%s'.
 *   Reason       : This is sample program for user, in order to clearly indicate what should be specified,
 *                  this program is daringly using the magic number.
 *   Verification : This information is a kind of advice and there is no problem in operation even if it does not
 *                  correspond.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule DCL06 / QAC message 3132
 *   Message      : Hard coded 'magic' number, '%s', used to define the size of an array.
 *   Reason       : Because this function is a sample, it is better to describe the number of elements of the array
 *                  as a number, so it is easier to understand the meaning.
 *   Verification : Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule DCL00 / QAC message 3227
 *   Message      : The parameter '%s' is never modified and so it could be declared with the 'const' qualifier.
 *   Reason       : This function is an API and is a user I/F. In other words, since the user set parameters,
 *                  it cannot be limited to the const type.
 *   Verification : No violation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule INT02 / QAC message 2100,2101
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

#include "sample_common_control.h"
#include "sample_property_control.h"

#define R_RFD_CSA_BASE_FACI0_FS    0xFF320800UL    /* Base address of Front side of Configuration Setting Area */
#define R_RFD_CSA_BASE_FACI0_BS    0xFF321000UL    /* Base address of Back side of Configuration Setting Area  */

/**********************************************************************************************************************
**  Function Name   : Sample_PropertyAreaControl
**  
**  - Outline
**      Sample of Property Area Control
**  - Format
**      T_u4_RFDReturn
**          Sample_PropertyAreaControl(void);
**  - Input parameter
**      non
**  - Return
**      R_RFD_OK                  : Normal End
**      R_RFD_ERR_ACCESS_ENV      : Illegal Access Error
**      R_RFD_ERR_ERASE           : Erase Error state
**      R_RFD_ERR_FHVE_PROTECT    : FHVE Protect Error
**      R_RFD_ERR_INTERNAL_DATA   : Internal Data Error
**      R_RFD_ERR_INTERNAL_HW     : Internal Hardware error
**      R_RFD_ERR_NOFACI          : Specified FACI is noexistance
**      R_RFD_ERR_WRITE           : Write Error state
**      R_RFD_STS_BUSY            : Busy state
**      R_RFD_STS_ERASE_SUSPENDED : Erasure Suspended state
**      R_RFD_STS_WRITE_SUSPENDED : Programming Suspension state
**  - Preconditions
**      No preconditions
**  
**  - Traceability          : [Covers:VT_01_003] [Covers:VT_01_004] [Covers:VT_01_005]
**                            [Covers:VT_01_006] [Covers:VT_01_007] [Covers:VT_01_008]
**                            [Covers:VT_01_022] [Covers:VT_01_023] [Covers:VT_01_024]
**                            [Covers:VT_01_025] [Covers:VT_01_026] [Covers:VT_01_027]
**********************************************************************************************************************/

T_u4_RFDReturn
Sample_PropertyAreaControl(void)
{
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnInternal;       /* Return value for saving                  */
    T_u4_RFDReturn  l_bu4_returnValue;          /* Return value for this function           */
    T_bl            l_bl1_errorFlag;            /* Error flag                               */
    T_u4            l_bu4_timeout;              /* For timeout count                        */
    T_bl            l_bl1_timeoutFlag;          /* Timeout error flag                       */
    T_u4            l_bu4_loopValue;            /* For loop                                 */
    T_u2_FACI       l_u2_TargetFACI;            /* FACI number                              */
    T_u4            i_pu4_Data[8];              /* Array for data of Switch Area            */
    T_u4            l_bu4_CSAContentsFS[104];   /* Offset 0x200-0x47F for Configuration Setting Area (Front Side) */
    T_u4            l_bu4_CSAContentsBS[104];   /* Offset 0x200-0x47F for Configuration Setting Area (Back Side)  */
    T_u4*           l_pu4_CSAFrontSideBase;     /* Base address of Front side of Configuration Setting Area       */
    T_u4*           l_pu4_CSABackSideBase;      /* Base address of Back side of Configuration Setting Area        */
    
    
    /* Initialization of the local variables  */
    l_bu4_returnValue    = R_RFD_OK;
    l_bu4_returnInternal = R_RFD_OK;
    l_bu4_timeout        = 0UL;
    l_bl1_timeoutFlag    = R_RFD_FALSE;
    l_bl1_errorFlag      = R_RFD_FALSE;
    l_bu4_loopValue      = 0UL;
    l_u2_TargetFACI      = R_RFD_INVALID_FACI;
    
    /******************************************************************************************************************
     *  Read the contents of the Configuration Setting Area (Front side)
     *****************************************************************************************************************/
     
    /* Set the start address of Configuration Setting Area (Front side) (0x200 - 0x21F) */
    l_pu4_CSAFrontSideBase = (T_u4 *)(R_RFD_CSA_BASE_FACI0_FS + 0x200UL); /* !QAC message 3120                          */
                                                                    /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
    /* Acquire the target of FACI */
    l_u2_TargetFACI  = R_RFD_PropertyAddressToFaciNumber((T_u4_RfdAddress)R_RFD_CSA_BASE_FACI0_BS);
                                                                    /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
    
    if (l_u2_TargetFACI == R_RFD_INVALID_FACI)  /* !CERT-C rule INT02 (QAC message 2101) */
    {
        l_bl1_errorFlag = R_RFD_TRUE;       /* Specified FACI is noexistance */
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Read from the offset 0x200 - 0x21F */
        for(l_bu4_loopValue = 0UL; l_bu4_loopValue < 8UL; l_bu4_loopValue++)    /* !QAC message 3120 */
        {
            l_bu4_CSAContentsFS[l_bu4_loopValue] = *l_pu4_CSAFrontSideBase;
            l_pu4_CSAFrontSideBase++;
        }
        
        /* Set the start address of Configuration Setting Area (Front side) (0x300 - 0x47F) */
        l_pu4_CSAFrontSideBase = (T_u4 *)(R_RFD_CSA_BASE_FACI0_FS + 0x300UL); /* !QAC message 3120                          */
                                                                        /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        /* Read from the offset 0x300 - 0x47F */
        for(l_bu4_loopValue = 8UL; l_bu4_loopValue < 104UL; l_bu4_loopValue++)    /* !QAC message 3120 */
        {
            l_bu4_CSAContentsFS[l_bu4_loopValue] = *l_pu4_CSAFrontSideBase;
            l_pu4_CSAFrontSideBase++;
        }
    }
    else
    {
        /* no operation */
    }
    
    /******************************************************************************************************************
     *  Change the value of the Configuration Setting Area
     *****************************************************************************************************************/
    
    
    /************************************************************************************
     * Here, values are substituted into the read temporary at the point to be changed. *
     * The sample writes the read value as it is.                                       *
     ***********************************************************************************/
    
    
    /******************************************************************************************************************
     *  Shift the mode to the P/E mode
     *****************************************************************************************************************/
    
    if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_timeoutFlag == R_RFD_FALSE))
    {                                                           /* !CERT-C rule INT02 (QAC message 2100) */
        /* Shift the mode to the P/E mode */
        l_bu4_returnValue = R_RFD_ShiftToPEMode(l_u2_TargetFACI, R_RFD_MODE_DFPE);
        
        /* Mode has not already R_RFD_MODE_DFPE */
        if (l_bu4_returnValue == R_RFD_STS_BUSY)
        {
            l_bl1_errorFlag   = R_RFD_TRUE;     /* Error occurred */
            
            /* Shift the mode to the read mode */
            l_bu4_returnValue = R_RFD_ShiftToReadMode(l_u2_TargetFACI);
            
            if (l_bu4_returnValue != R_RFD_ERR_INTERNAL_HW)
            {
                l_bu4_returnValue = R_RFD_ERR_TIMEOUT;  /* Set return value */
            }
            else
            {
                /* no operation */
            }
        }
        else if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
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
    
    /******************************************************************************************************************
     *  Erase the contents of the Configuration Setting Area (Back side)
     *****************************************************************************************************************/
    
    if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_timeoutFlag == R_RFD_FALSE))
    {                                                           /* !CERT-C rule INT02 (QAC message 2100) */
        /* Set the start address of the Configuration Setting Area (Back side) */
        l_pu4_CSABackSideBase = (T_u4 *)R_RFD_CSA_BASE_FACI0_BS;      /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        
        /* Erase the contents of the Configuration Setting Area (Back side) */
        l_bu4_returnValue = Sample_EraseConfigurationSettingArea((T_u4_RfdAddress)l_pu4_CSABackSideBase);
                                                                /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        if (l_bu4_returnValue == R_RFD_OK)
        {
            /* Set the timeout value for checking whether erasure is completed */
            l_bu4_timeout = 100000UL;     /* !QAC message 3120 */
            
            /* Check whether the erasure is completed */
            do
            {
                l_bu4_returnValue = Sample_CheckFaciStatus(l_u2_TargetFACI);
                l_bu4_timeout--;        /* !CERT-C rule INT30 (QAC message 3383) */
                
                /* Check timeout */
                if (l_bu4_timeout == 0UL)
                {
                    l_bl1_timeoutFlag = R_RFD_TRUE; /* Timeout occured */
                    break;
                }
                else
                {
                    /* no operation */
                }
            } while (l_bu4_returnValue == R_RFD_STS_BUSY);
            
            /* If the timeout is not occured  */
            if (l_bu4_returnValue == R_RFD_OK)
            {
                /* no operation */
            }
            else
            {
                l_bl1_errorFlag = R_RFD_TRUE; /* Error occurred */
            }
        }
        /* Return value of Sample_EraseConfigurationSettingArea is not R_RFD_OK */
        else
        {
            /* Return value of Sample_EraseConfigurationSettingArea is */
            /* "R_RFD_ERR_NOFACI" or "R_RFD_ERR_INTERNAL_HW"           */
            l_bl1_errorFlag = R_RFD_TRUE;   /* Error occurred */
        }
    }
    else
    {
        /* no operation */
    }
    
    /******************************************************************************************************************
     *  Write the contents of Configuration Setting Area (Back side)
     *****************************************************************************************************************/
    
    if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_timeoutFlag == R_RFD_FALSE))
    {                                                           /* !CERT-C rule INT02 (QAC message 2100) */
        /* Write to the offset 0x200 - 0x21F */
        l_pu4_CSABackSideBase = (T_u4 *)(R_RFD_CSA_BASE_FACI0_BS + 0x200UL); /* !QAC message 3120                          */
                                                                       /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        
        l_bu4_returnValue = Sample_WriteConfigurationSettingArea((T_u4_RfdAddress)l_pu4_CSABackSideBase, 
                                                                 (T_pu4_RfdBuffer)&l_bu4_CSAContentsFS[0]);
                                                                       /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        if (l_bu4_returnValue == R_RFD_OK)
        {
            /* Set the timeout value for checking whether erasure is completed */
            l_bu4_timeout = 100000UL;     /* !QAC message 3120 */
            
            /* Check whether the erasure is completed */
            do
            {
                l_bu4_returnValue = Sample_CheckFaciStatus(l_u2_TargetFACI);
                l_bu4_timeout--;        /* !CERT-C rule INT30 (QAC message 3383) */
                
                /* Check timeout */
                if (l_bu4_timeout == 0UL)
                {
                    l_bl1_timeoutFlag = R_RFD_TRUE; /* Timeout occured */
                    break;
                }
                else
                {
                    /* no operation */
                }
            } while (l_bu4_returnValue == R_RFD_STS_BUSY);
            
            /* Whether a timeout has occurred */
            if (l_bu4_returnValue == R_RFD_OK)
            {
                /* no operation */
            }
            else
            {
                l_bl1_errorFlag = R_RFD_TRUE; /* Error occurred */
            }
        }
        /* Return value of Sample_WriteConfigurationSettingArea is not R_RFD_OK */
        else
        {
            /* Return value of Sample_WriteConfigurationSettingArea is */
            /* "R_RFD_ERR_NOFACI" or "R_RFD_ERR_INTERNAL_HW"           */
            l_bl1_errorFlag = R_RFD_TRUE;   /* Error occurred */
        }
        
        
        if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_timeoutFlag == R_RFD_FALSE))
        {                                                           /* !CERT-C rule INT02 (QAC message 2100) */
            /* Write to the offset 0x300 - 0x47F */
            l_pu4_CSABackSideBase = (T_u4 *)(R_RFD_CSA_BASE_FACI0_BS + 0x300UL);
                                                                    /* !QAC message 3120                          */
                                                                    /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
            for(l_bu4_loopValue = 8UL; l_bu4_loopValue < 104UL; l_bu4_loopValue += 8UL)
            {                                                       /* !QAC message 3120 */
                l_bu4_returnValue = Sample_WriteConfigurationSettingArea((T_u4_RfdAddress)l_pu4_CSABackSideBase,
                                                     (T_pu4_RfdBuffer)&l_bu4_CSAContentsFS[l_bu4_loopValue]);
                                                                    /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
                if (l_bu4_returnValue == R_RFD_OK)
                {
                    /* Set the timeout value for checking whether erasure is completed */
                    l_bu4_timeout = 100000UL;     /* !QAC message 3120 */
                    
                    /* Check whether the erasure is completed */
                    do
                    {
                        l_bu4_returnValue = Sample_CheckFaciStatus(l_u2_TargetFACI);
                        l_bu4_timeout--;        /* !CERT-C rule INT30 (QAC message 3383) */
                        
                        /* Check timeout */
                        if (l_bu4_timeout == 0UL)
                        {
                            l_bl1_timeoutFlag = R_RFD_TRUE; /* Timeout occured */
                            break;
                        }
                        else
                        {
                            /* no operation */
                        }
                    } while (l_bu4_returnValue == R_RFD_STS_BUSY);
                    
                    /* Whether a timeout has occurred */
                    if (l_bu4_returnValue == R_RFD_OK)
                    {
                        /* no operation */
                    }
                    else
                    {
                        l_bl1_errorFlag = R_RFD_TRUE; /* Error occurred */
                    }
                }
                /* Return value of Sample_WriteConfigurationSettingArea is not R_RFD_OK */
                else
                {
                    /* Return value of Sample_WriteConfigurationSettingArea is */
                    /* "R_RFD_ERR_NOFACI" or "R_RFD_ERR_INTERNAL_HW"           */
                    l_bl1_errorFlag = R_RFD_TRUE;   /* Error occurred */
                }
                
                l_pu4_CSABackSideBase = l_pu4_CSABackSideBase + 8;  /* increments 32bytes                         */
                                                        /* !QAC message 3120                          */
                                                        /* !MISRA-C 2012 rule 18.4 / QAC message 0488 */
            } /* for(l_bu4_loopValue = 0; l_bu4_loopValue < 12; l_bu4_loopValue++) */
            
        } /* if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_timeoutFlag == R_RFD_FALSE)) */
        else
        {
            /* no operation */
        }
        
        /* Read from the offset 0x200 - 0x21F */
        for (l_bu4_loopValue = 0UL; l_bu4_loopValue < 8UL; l_bu4_loopValue++)    /* !QAC message 3120 */
        {
            l_bu4_CSAContentsBS[l_bu4_loopValue] = *l_pu4_CSABackSideBase;
            l_pu4_CSABackSideBase++;
        }
        
        /* Set the start address of Configuration Setting Area (Back side) (0x300 - 0x47F) */
        l_pu4_CSABackSideBase = (T_u4 *)(R_RFD_CSA_BASE_FACI0_BS + 0x300UL);  /* !QAC message 3120                          */
                                                                              /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        /* Read from the offset 0x300 - 0x47F */
        for (l_bu4_loopValue = 8UL; l_bu4_loopValue < 104UL; l_bu4_loopValue++) /* !QAC message 3120 */
        {
            l_bu4_CSAContentsBS[l_bu4_loopValue] = *l_pu4_CSABackSideBase;
            l_pu4_CSABackSideBase++;
        }
        
        /* Compare Front side value to Back side value */
        for (l_bu4_loopValue = 0UL; l_bu4_loopValue < 104UL; l_bu4_loopValue++)   /* !QAC message 3120 */
        {
            if (l_bu4_CSAContentsFS[l_bu4_loopValue] != l_bu4_CSAContentsBS[l_bu4_loopValue])
            {
                
                l_bl1_errorFlag = R_RFD_TRUE;
                break;
            }
        }
        
    }/* if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_timeoutFlag == R_RFD_FALSE)) */
    else
    {
        /* no operation */
    } 
    
    /******************************************************************************************************************
     *  Set the value for the CVA, SVA, BVA0 and BVA1 in Switch Area (To Back side)
     *****************************************************************************************************************/
    
    /* This time, only the Configuration Setting Area is being operated, so the operation is performed for */
    /* i_pu4_Data [0]. Set 0x5AA5A55A for 0xA55A5AA5 or 0xA55A5AA5 for 0x5AA5A55A                          */
    
    /* Valid area of the Configration Setting Area is Area1 ? */
    /* Change specified area                                  */
    if (((T_u1)R_RFD_REG_FSWASTAT & (T_u1)R_RFD_MASK_FSWASTAT_CFGVA) != (T_u1)0x00U)
    {                                                               /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
                                                                    /* !CERT-C rule INT02 (QAC message 2100)      */
        i_pu4_Data[0] = R_RFD_VALUE_VALID_AREA0;
    }
    else
    {
        i_pu4_Data[0] = R_RFD_VALUE_VALID_AREA1;
    }
    
    /* Valid area of the Security Setting Area is Area1 ? */
    /* No change                                          */
    if (((T_u1)R_RFD_REG_FSWASTAT & (T_u1)R_RFD_MASK_FSWASTAT_SECVA) != (T_u1)0x00U)
    {                                                               /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
                                                                    /* !CERT-C rule INT02 (QAC message 2100)      */
        i_pu4_Data[1] = R_RFD_VALUE_VALID_AREA1;
    }
    else
    {
        i_pu4_Data[1] = R_RFD_VALUE_VALID_AREA0;
    }
    
    /* Valid area of the Block Protection Area0 is Area1 ? */
    /* No change                                           */
    if (((T_u1)R_RFD_REG_FSWASTAT & (T_u1)R_RFD_MASK_FSWASTAT_BPVA0) != (T_u1)0x00U)
    {                                                               /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
                                                                    /* !CERT-C rule INT02 (QAC message 2100)      */
        i_pu4_Data[2] = R_RFD_VALUE_VALID_AREA1;    /* !QAC message 3120 */
    }
    else
    {
        i_pu4_Data[2] = R_RFD_VALUE_VALID_AREA0;    /* !QAC message 3120 */
    }
    
    #ifdef __RH850_U2A__
        /* Valid area of the Block Protection Area1 is Area1 ? */
        /* No change                                           */
        if (((T_u1)R_RFD_REG_FSWASTAT & (T_u1)R_RFD_MASK_FSWASTAT_BPVA1) != (T_u1)0x00U)
        {                                                               /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
                                                                    /* !CERT-C rule INT02 (QAC message 2100)      */
            i_pu4_Data[3] = R_RFD_VALUE_VALID_AREA1;    /* !QAC message 3120 */
        }
        else
        {
            i_pu4_Data[3] = R_RFD_VALUE_VALID_AREA0;    /* !QAC message 3120 */
        }
    #else /* __RH850_U2B__ */
        i_pu4_Data[3] = 0xFFFFFFFFUL;   /* !QAC message 3120 */
    #endif /* __RH850_U2A__ */
    
    /* Store the reserved value to the element 4 to 7 */
    i_pu4_Data[4] = 0xFFFFFFFFUL;   /* !QAC message 3120 */
    i_pu4_Data[5] = 0xFFFFFFFFUL;   /* !QAC message 3120 */
    i_pu4_Data[6] = 0xFFFFFFFFUL;   /* !QAC message 3120 */
    i_pu4_Data[7] = 0xFFFFFFFFUL;   /* !QAC message 3120 */
    
    /******************************************************************************************************************
     *  Erase the contents of the Switch Area (Back side)
     *****************************************************************************************************************/
    
    if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_timeoutFlag == R_RFD_FALSE))
    {                                                           /* !CERT-C rule INT02 (QAC message 2100) */
        /* Erase the contents of Switch Area (Back side) */
        l_bu4_returnValue = Sample_EraseSwitchArea();
        
        if (l_bu4_returnValue == R_RFD_OK)
        {
            /* Set the timeout value for checking whether erasure is completed */
            l_bu4_timeout = 100000UL;     /* !QAC message 3120 */
            
            /* Check whether the erasure is completed */
            do
            {
                l_bu4_returnValue = Sample_CheckFaciStatus(l_u2_TargetFACI);
                l_bu4_timeout--;        /* !CERT-C rule INT30 (QAC message 3383) */
                
                /* Check timeout */
                if (l_bu4_timeout == 0UL)
                {
                    l_bl1_timeoutFlag = R_RFD_TRUE; /* Timeout occured */
                    break;
                }
                else
                {
                    /* no operation */
                }
            } while (l_bu4_returnValue == R_RFD_STS_BUSY);
            
            /* Whether a timeout has occurred */
            if (l_bu4_returnValue == R_RFD_OK)
            {
                /* no operation */
            }
            else
            {
                l_bl1_errorFlag = R_RFD_TRUE; /* Error occurred   */
            }
        }
        /* Return value of the Sample_EraseSwitchArea is not R_RFD_OK */
        else
        {
            /* Return value of Sample_EraseSwitchArea is          */
            /* "R_RFD_ERR_NOFACI" or "R_RFD_ERR_INTERNAL_HW"      */
            l_bl1_errorFlag = R_RFD_TRUE;   /* Error occurred     */
        }
    }
    else
    {
        /* no operation */
    }
    
    /******************************************************************************************************************
     *  Write the contents of the Switch Area (Back side)
     *****************************************************************************************************************/
    
    if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_timeoutFlag == R_RFD_FALSE))
    {                                                           /* !CERT-C rule INT02 (QAC message 2100) */
        /* Erase the contents of the Switch Area (Back side) */
        l_bu4_returnValue = Sample_WriteSwitchArea(&i_pu4_Data[0]);
        
        if (l_bu4_returnValue == R_RFD_OK)
        {
            /* Set the timeout value for checking whether erasure is completed */
            l_bu4_timeout = 100000UL;     /* !QAC message 3120 */
            
            /* Check whether the erasure is completed */
            do
            {
                l_bu4_returnValue = Sample_CheckFaciStatus(l_u2_TargetFACI);
                l_bu4_timeout--;        /* !CERT-C rule INT30 (QAC message 3383) */
                
                /* Check timeout */
                if (l_bu4_timeout == 0UL)
                {
                    l_bl1_timeoutFlag = R_RFD_TRUE; /* Timeout occured */
                    break;
                }
                else
                {
                    /* no operation */
                }
            } while (l_bu4_returnValue == R_RFD_STS_BUSY);
            
            /* Whether a timeout has occurred */
            if (l_bu4_returnValue == R_RFD_OK)
            {
                /* no operation */
            }
            else
            {
                l_bl1_errorFlag = R_RFD_TRUE; /* Error occurred */
            }
        }
        /* Return value of the Sample_WriteSwitchArea is not R_RFD_OK */
        else
        {
            /* Return value of Sample_WriteSwitchArea is      */
            /* "R_RFD_ERR_NOFACI" or "R_RFD_ERR_INTERNAL_HW"  */
            l_bl1_errorFlag = R_RFD_TRUE;   /* Error occurred */
        }
    }
    else
    {
        /* no operation */
    }
    
    /******************************************************************************************************************
     *  Erase the contents of the Tag Area
     *****************************************************************************************************************/
    
    if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_timeoutFlag == R_RFD_FALSE))
    {                                                           /* !CERT-C rule INT02 (QAC message 2100) */
        /* Erase the contents of Tag Area */
        l_bu4_returnValue = Sample_EraseTagArea();
        
        if (l_bu4_returnValue == R_RFD_OK)
        {
            /* Set the timeout value for checking whether erasure is completed */
            l_bu4_timeout = 100000UL;     /* !QAC message 3120 */
            
            /* Check whether the erasure is completed */
            do
            {
                l_bu4_returnValue = Sample_CheckFaciStatus(l_u2_TargetFACI);
                l_bu4_timeout--;        /* !CERT-C rule INT30 (QAC message 3383) */
                
                /* Check timeout */
                if (l_bu4_timeout == 0UL)
                {
                    l_bl1_timeoutFlag = R_RFD_TRUE; /* Timeout occured */
                    break;
                }
                else
                {
                    /* no operation */
                }
            } while (l_bu4_returnValue == R_RFD_STS_BUSY);
            
            /* Whether a timeout has occurred */
            if (l_bu4_returnValue == R_RFD_OK)
            {
                /* no operation */
            }
            else
            {
                l_bl1_errorFlag = R_RFD_TRUE; /* Error occurred */
            }
        }
        /* Return value of the Sample_EraseTagArea is not R_RFD_OK */
        else
        {
            /* Return value of Sample_EraseTagArea is          */
            /* "R_RFD_ERR_NOFACI" or "R_RFD_ERR_INTERNAL_HW"   */
            l_bl1_errorFlag = R_RFD_TRUE;   /* Error occurred  */
        }
    }
    else
    {
        /* no operation */
    }
    
    /******************************************************************************************************************
     *  Update the contents of the Tag Area
     *****************************************************************************************************************/
    
    if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_timeoutFlag == R_RFD_FALSE))
    {                                                           /* !CERT-C rule INT02 (QAC message 2100) */
        /* Update the Tag Area */
        l_bu4_returnValue = Sample_UpdateTagArea();
        
        if (l_bu4_returnValue == R_RFD_OK)
        {
            /* Set the timeout value for checking erasure complete */
            l_bu4_timeout = 100000UL;     /* !QAC message 3120 */
            
            /* Check whether the erasure is completed */
            do
            {
                l_bu4_returnValue = Sample_CheckFaciStatus(l_u2_TargetFACI);
                l_bu4_timeout--;        /* !CERT-C rule INT30 (QAC message 3383) */
                
                /* Check timeout */
                if (l_bu4_timeout == 0UL)
                {
                    l_bl1_timeoutFlag = R_RFD_TRUE; /* Timeout occured */
                    break;
                }
                else
                {
                    /* no operation */
                }
            } while (l_bu4_returnValue == R_RFD_STS_BUSY);
            
            /* Whether a timeout has occurred */
            if (l_bu4_returnValue == R_RFD_OK)
            {
                /* no operation */
            }
            else
            {
                l_bl1_errorFlag = R_RFD_TRUE; /* Error occurred */
            }
        }
        /* Return value of the Sample_UpdateTagArea is not R_RFD_OK */
        else
        {
            /* Return value of Sample_UpdateTagArea is          */
            /* "R_RFD_ERR_NOFACI" or "R_RFD_ERR_INTERNAL_HW"    */
            l_bl1_errorFlag = R_RFD_TRUE;   /* Error occurred   */
        }
    }
    else
    {
        /* no operation */
    }
    
    /******************************************************************************************************************
     *  Shift the mode to the read mode
     *****************************************************************************************************************/
    
    if (l_bl1_timeoutFlag == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
    {
        l_bu4_returnInternal = R_RFD_ForcedStopAndErrorClear(l_u2_TargetFACI);
        
        if (l_bu4_returnInternal == R_RFD_OK)
        {
            l_bu4_returnInternal = R_RFD_ShiftToReadMode(l_u2_TargetFACI);
            
            if ( l_bu4_returnInternal != R_RFD_OK )
            {
                l_bu4_returnValue = l_bu4_returnInternal;
            }
            else
            {
                /* no operation */
            }
        }
        else
        {
            l_bu4_returnValue = l_bu4_returnInternal;
        }
    }
    else	/* l_bl1_timeoutFlag == R_RFD_FALSE */
    {
        if (l_bu4_returnValue != R_RFD_OK)
        {
            /* Release the command-lock states */
            l_bu4_returnInternal = Sample_ReleaseCommandLock(l_u2_TargetFACI);
            
            if (l_bu4_returnInternal != R_RFD_OK)
            {
                l_bu4_returnValue = l_bu4_returnInternal;
                l_bu4_returnInternal = R_RFD_ShiftToReadMode(l_u2_TargetFACI);
            }
            else
            {
                l_bu4_returnValue = R_RFD_ShiftToReadMode(l_u2_TargetFACI);
            }
        }
        else
        {
            /* Shift the mode to the read mode */
            l_bu4_returnValue = R_RFD_ShiftToReadMode(l_u2_TargetFACI);
        }
    }
    
    return (l_bu4_returnValue);

}
