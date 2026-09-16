/**********************************************************************************************************************
    Program Name    : Sample program for Renesas Flash Driver (RFD28F)
    
    File Name       : sample_subfunction_common.c
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
 *   Rule         : CERT-C rule DCL00 / QAC message 3227
 *   Message      : The parameter '%s' is never modified and so it could be declared with the 'const' qualifier.
 *   Reason       : This function is an API and is a user I/F. In other words, since the user set parameters,
 *                  it cannot be limited to the const type.
 *   Verification : No violation.
 *********************************************************************************************************************/

#include "sample_common_control.h"

/**********************************************************************************************************************
**  Function Name   : Sample_SuspendPE
**  
**  - Outline
**      Suspend the flash control
**  - Format
**      T_u4_RFDReturn
**          Sample_SuspendPE(
**              T_u2_FACI     i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI       : Target FACI whose processing is to be suspended
**  - Return
**      R_RFD_OK                    : Normal End
**      R_RFD_ERR_ACCESS_ENV        : Illegal Access Error
**      R_RFD_ERR_ERASE             : Erase Error state
**      R_RFD_ERR_FHVE_PROTECT      : FHVE Protect Error
**      R_RFD_ERR_INTERNAL_DATA     : Internal Data Error
**      R_RFD_ERR_INTERNAL_HW       : Internal Hardware error
**      R_RFD_ERR_NOFACI            : Specified FACI is noexistance
**      R_RFD_ERR_REJECT            : Reject error
**      R_RFD_ERR_TIMEOUT           : Timeout
**      R_RFD_ERR_WRITE             : Write Error state
**      R_RFD_STS_ERASE_SUSPENDED   : Erasure Suspended state
**      R_RFD_STS_WRITE_SUSPENDED   : Programming Suspension state
**      R_RFD_STS_BUSY              : Busy state
**  
**  - Traceability          : [Covers:UD_103_001]
**********************************************************************************************************************/

/* !CERT-C rule DCL00 (QAC message 3227)     */

T_u4_RFDReturn
Sample_SuspendPE(T_u2_FACI i_u2_TargetFACI)
{
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    T_u4            l_bu4_timeout;          /* For timeout count              */
    
    /* Initialization of the local variables  */
    l_bu4_returnValue   = R_RFD_OK;
    l_bu4_timeout       = 100000UL;          /* !QAC message 3120 */
    
    
    /* Acquire the FACI status */
    l_bu4_returnValue = R_RFD_GetFaciStatus(i_u2_TargetFACI);
    
    if (l_bu4_returnValue == R_RFD_OK)
    {
        do
        {
            l_bu4_returnValue = R_RFD_SuspendPERequest(i_u2_TargetFACI);
            l_bu4_timeout--;    /* !CERT-C rule INT30 (QAC message 3383) */
            
            /* Check timeout */
            if (l_bu4_timeout == 0UL)
            {
                break;
            }
            else
            {
                /* no operation */
            }
        } while (l_bu4_returnValue == R_RFD_ERR_REJECT);
        
        /* Whether the mode does not shift to the P/E mode */
        if (l_bu4_returnValue == R_RFD_ERR_REJECT)
        {
            l_bu4_returnValue = R_RFD_ERR_TIMEOUT;  /* Timeout */
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
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : Sample_ResumePE
**  
**  - Outline
**      Resume the suspension process
**  - Format
**      T_u4_RFDReturn
**          Sample_ResumePE(
**              T_u2_FACI     i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI       : Target FACI to be resumed the suspension process
**  - Return
**      R_RFD_OK            : Normal End
**      R_RFD_ERR_NOFACI    : Specified FACI is noexistance
**  
**  - Traceability          : [Covers:UD_104_001]
**********************************************************************************************************************/

/* !CERT-C rule DCL00 (QAC message 3227)     */

T_u4_RFDReturn
Sample_ResumePE(T_u2_FACI i_u2_TargetFACI)
{
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;  /* Return value for this function           */
    T_bl            l_bl1_errorFlag;    /* Error flag                               */
    
    /* Initialization of the local variables  */
    l_bu4_returnValue   = R_RFD_OK;
    l_bl1_errorFlag     = R_RFD_FALSE;
    
    
    /* Acquire the FACI status */
    l_bu4_returnValue = R_RFD_GetFaciStatus(i_u2_TargetFACI);
    
    if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
    {
        l_bl1_errorFlag = R_RFD_TRUE;     /* Specified FACI is noexistance */
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)   /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Status has not been the suspension status */
        if ((l_bu4_returnValue & R_RFD_STS_SUSPENDING) != 0UL)
        {
            l_bu4_returnValue = R_RFD_ResumePERequest(i_u2_TargetFACI);
        }
        else
        {
            l_bu4_returnValue = R_RFD_ERR_NO_SUSPENSION;
        }
    }
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : Sample_ReleaseCommandLock
**  
**  - Outline
**      Release the command lock state for the target FACI
**  - Format
**      T_u4_RFDReturn
**          Sample_ReleaseCommandLock(
**              T_u2_FACI     i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI       : Target FACI to be command locked of flash memory
**  - Return
**      R_RFD_OK              : Normal End
**      R_RFD_ERR_INTERNAL_HW : Internal Hardware error
**      R_RFD_ERR_NOFACI      : Specified FACI is noexistance
**  
**  - Traceability          : [Covers:UD_108_001]
**********************************************************************************************************************/

/* !CERT-C rule DCL00 (QAC message 3227)     */

T_u4_RFDReturn
Sample_ReleaseCommandLock(T_u2_FACI i_u2_TargetFACI)
{
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function           */
    
    /* Initialization of the local variables  */
    l_bu4_returnValue   = R_RFD_OK;
    
    /* Status has not been the suspension status */
    
    l_bu4_returnValue = R_RFD_StatusClear(i_u2_TargetFACI);
    
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : Sample_CheckFaciStatus
**  
**  - Outline
**      Check the FACI sequencer status for the target FACI
**  - Format
**      T_u4_RFDReturn
**          Sample_CheckFaciStatus(
**              T_u2_FACI     i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI       : Target FACI to be command locked of flash memory
**  - Return
**      R_RFD_OK                    : Normal End
**      R_RFD_ERR_ACCESS_ENV        : Illegal Access Error
**      R_RFD_ERR_ERASE             : Erase Error state
**      R_RFD_ERR_FHVE_PROTECT      : FHVE Protect Error
**      R_RFD_ERR_INTERNAL_DATA     : Internal Data Error
**      R_RFD_ERR_INTERNAL_HW       : Internal Hardware error
**      R_RFD_ERR_NOFACI            : Specified FACI is noexistance
**      R_RFD_ERR_WRITE             : Write Error state
**      R_RFD_STS_BUSY              : Busy state
**      R_RFD_STS_ERASE_SUSPENDED   : Erasure Suspended state
**      R_RFD_STS_WRITE_SUSPENDED   : Programming Suspension state
**  
**  - Traceability          : [Covers:UD_109_001]
**********************************************************************************************************************/

/* !CERT-C rule DCL00 (QAC message 3227)     */

T_u4_RFDReturn
Sample_CheckFaciStatus(T_u2_FACI i_u2_TargetFACI)
{
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    
    /* Initialization of the local variables  */
    l_bu4_returnValue   = R_RFD_OK;
    
    
    /* Check whether the target FACI is in ready state */
    l_bu4_returnValue = R_RFD_GetFaciSequenceReady(i_u2_TargetFACI);
    
    /* Return value is not the R_RFD_ERR_NOFACI and the FACI status is not ready state */
    if ((l_bu4_returnValue != R_RFD_ERR_NOFACI)&&(l_bu4_returnValue != R_RFD_STS_BUSY))
    {
        /* Acquire the FACI status */
        l_bu4_returnValue = R_RFD_GetFaciStatus(i_u2_TargetFACI);
    }
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}
