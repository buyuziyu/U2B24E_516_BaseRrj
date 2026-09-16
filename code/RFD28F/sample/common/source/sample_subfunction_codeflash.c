/**********************************************************************************************************************
    Program Name    : Sample program for Renesas Flash Driver (RFD28F)
    
    File Name       : sample_subfunction_codeflash.c
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
 *   Rule         : MISRA-C 2012 rule 3.1 / QAC message 3108
 *   Message      : Nested comments are not recognized in the ISO standard.
 *   Reason       : Description "//" is a part of URL, so This does not apply.
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
 *   Rule         : CERT-C rule DCL00 / QAC message 3227
 *   Message      : The parameter '%s' is never modified and so it could be declared with the 'const' qualifier.
 *   Reason       : This function is an API and is a user I/F. In other words, since the user set parameters,
 *                  it cannot be limited to the const type.
 *   Verification : No violation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule 5002
 *   Message      : The header '%s' file name shadows a previously included header.
 *   Reason       : The header file of the RFD28F starts with "r_rfd", and in the case of a component-specific
 *                  header file is given a component name to improve identification.
 *                  It is intentional and there is no problem.
 *   Verification : Incorrect processing would result in test fails.
 *********************************************************************************************************************/

#include "sample_common_control.h"
#include "sample_codeflash_control.h"   /* !CERT-C rule 5002 */

/**********************************************************************************************************************
**  Function Name   : Sample_EraseCF
**  
**  - Outline
**      Erase the contents of the code flash memory
**  - Format
**      T_u4_RFDReturn
**          Sample_EraseCF(
**              T_u4_RfdAddress  i_u4_Start
**          );
**  - Input parameter
**      i_u4_Start                : Address in the target code flash memory to start erasure
**  - Return
**      R_RFD_OK                  : Normal End
**      R_RFD_STS_BUSY            : Busy state
**      R_RFD_STS_ERASE_SUSPENDED : Erasure Suspended state
**      R_RFD_STS_WRITE_SUSPENDED : Programming Suspension state
**      R_RFD_ERR_INTERNAL_HW     : Internal Hardware error
**      R_RFD_ERR_NOFACI          : Specified FACI is noexistance
**  
**  - Traceability          : [Covers:UD_110_001]
**********************************************************************************************************************/

/* !CERT-C rule DCL00 (QAC message 3227)     */

T_u4_RFDReturn
Sample_EraseCF(T_u4_RfdAddress i_u4_Start)
{
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    T_u2_FACI       l_u2_TargetFACI;        /* FACI number                    */
    T_bl            l_bl1_errorFlag;        /* Error flag                     */
    
    /* Initialization of the local variables  */
    l_bu4_returnValue   = R_RFD_OK;
    l_u2_TargetFACI     = R_RFD_INVALID_FACI;
    l_bl1_errorFlag     = R_RFD_FALSE;
    
    /* Acquire the target for FACI to control */
    l_u2_TargetFACI = R_RFD_CFAddressToFaciNumber(i_u4_Start);
    
    if (l_u2_TargetFACI == R_RFD_INVALID_FACI)  /* !CERT-C rule INT02 (QAC message 2101) */
    {
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Acquire the FACI status */
        l_bu4_returnValue = Sample_CheckFaciStatus(l_u2_TargetFACI);
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Status has been the command-lock status (return value of Sample_CheckFaciStatus) as follows  */
        /* R_RFD_ERR_ACCESS_ENV,  R_RFD_ERR_ERASE, R_RFD_ERR_FHVE_PROTECT, R_RFD_ERR_INTERNAL_DATA,     */
        /* R_RFD_ERR_INTERNAL_HW, R_RFD_ERR_WRITE                                                       */
        if ((l_bu4_returnValue & R_RFD_ERR_CMD_LOCK) != 0UL)
        {
            l_bu4_returnValue = Sample_ReleaseCommandLock(l_u2_TargetFACI);
        }
        else
        {
            /* no operation */
        }
        
        /* Return value of the R_RFD_GetFaciStatus or Sample_ReleaseCommandLock is R_RFD_OK */
        if (l_bu4_returnValue == R_RFD_OK)
        {
            R_RFD_EraseCFRequest(i_u4_Start);
        }
        else
        {
            /* Status (return value of Sample_CheckFaciStatus) as follows           */
            /* R_RFD_STS_BUSY, R_RFD_STS_ERASE_SUSPENDED, R_RFD_STS_WRITE_SUSPENDED */
            /* no operation */
        }
    }
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : Sample_WriteCF
**  
**  - Outline
**      Write the data to the code flash memory
**  - Format
**      T_u4_RFDReturn
**          Sample_WriteDF(
**              T_u4_RfdAddress  i_u4_Start,
**              T_u4_RfdBuffer   i_pu4_Data
**          );
**  - Input parameter
**      i_u4_Start                : Address in the target code flash memory to start writing
**      i_pu4_Data                : Buffer address where writing data is stored
**  - Return
**      R_RFD_OK                  : Normal End
**      R_RFD_STS_BUSY            : Busy state
**      R_RFD_STS_ERASE_SUSPENDED : Erasure Suspended state
**      R_RFD_STS_WRITE_SUSPENDED : Programming Suspension state
**      R_RFD_ERR_INTERNAL_HW     : Internal Hardware error
**      R_RFD_ERR_NOFACI          : Specified FACI is noexistance
**  
**  - Traceability          : [Covers:UD_111_001]
**********************************************************************************************************************/

/* !CERT-C rule DCL00 (QAC message 3227)     */

T_u4_RFDReturn
Sample_WriteCF(T_u4_RfdAddress i_u4_Start, T_pu4_RfdBuffer i_pu4_Data)
{
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    T_u2_FACI       l_u2_TargetFACI;        /* FACI number                    */
    T_bl            l_bl1_errorFlag;        /* Error flag                     */
    
    /* Initialization of the local variables  */
    l_bu4_returnValue   = R_RFD_OK;
    l_u2_TargetFACI     = R_RFD_INVALID_FACI;
    l_bl1_errorFlag     = R_RFD_FALSE;
    
    
    /* Acquire the target for FACI to control */
    l_u2_TargetFACI = R_RFD_CFAddressToFaciNumber(i_u4_Start);
    
    if (l_u2_TargetFACI == R_RFD_INVALID_FACI)  /* !CERT-C rule INT02 (QAC message 2101) */
    {
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Acquire the FACI status */
        l_bu4_returnValue = Sample_CheckFaciStatus(l_u2_TargetFACI);
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Status has been the command-lock status (return value of Sample_CheckFaciStatus) as follows  */
        /* R_RFD_ERR_ACCESS_ENV,  R_RFD_ERR_ERASE, R_RFD_ERR_FHVE_PROTECT, R_RFD_ERR_INTERNAL_DATA,     */
        /* R_RFD_ERR_INTERNAL_HW, R_RFD_ERR_WRITE                                                       */
        if ((l_bu4_returnValue & R_RFD_ERR_CMD_LOCK) != 0UL)
        {
            l_bu4_returnValue = Sample_ReleaseCommandLock(l_u2_TargetFACI);
        }
        else
        {
            /* no operation */
        }
        
        /* Return value of the R_RFD_GetFaciStatus or Sample_ReleaseCommandLock is R_RFD_OK */
        if (l_bu4_returnValue == R_RFD_OK)
        {
            R_RFD_WriteCFRequest(i_u4_Start, i_pu4_Data);
        }
        else
        {
            /* Status (return value of Sample_CheckFaciStatus) as follows           */
            /* R_RFD_STS_BUSY, R_RFD_STS_ERASE_SUSPENDED, R_RFD_STS_WRITE_SUSPENDED */
            /* no operation */
        }
    }
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}
