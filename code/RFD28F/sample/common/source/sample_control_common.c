/**********************************************************************************************************************
    Program Name    : Sample program for Renesas Flash Driver (RFD28F)
    
    File Name       : sample_control_common.c
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
 *   Rule         : MISRA-C 2012 rule 10.5 / QAC message 4342
 *   Message      : An expression of 'essentially unsigned' type (%1s) is being cast to enum type '%2s'.
 *   Reason       : Where it is used to determine the value of an API parameter with an Enum type as the second
 *                  parameter. This method is used because the Enum type element in the corresponding location is used
 *                  with the recognition that it is effectively an unsigned 2-byte size, and the type will be
 *                  mismatched if it is not cast.
 *   Verification : Incorrect specification would result in test fails.
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

/**********************************************************************************************************************
**  Function Name   : Sample_SuspendResume
**  
**  - Outline
**      Sample of Suspension and Resuming
**  - Format
**      T_u4_RFDReturn
**          Sample_SuspendResume(
**              T_u2_FACI     i_u2_TargetFACI,
**          );
**  - Input parameter
**      i_u2_TargetFACI           : Target FACI whose suspended processing is to be resumed
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
**  - Traceability          : [Covers:VT_01_009] [Covers:VT_01_010] [Covers:VT_01_028] [Covers:VT_01_029]
**********************************************************************************************************************/

/* !CERT-C rule DCL00 (QAC message 3227)     */

T_u4_RFDReturn
Sample_SuspendResume(T_u2_FACI i_u2_TargetFACI)
{
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function           */
    T_u4_RFDReturn  l_bu4_returnInternal;   /* Return value for saving                  */
    T_u4            l_bu4_timeout;          /* For timeout count                        */
    T_u2            l_bu2_FACIMode;         /* Target FACI mode                         */
    T_bl            l_bl1_timeoutFlag;      /* Timeout error flag                       */
    T_bl            l_bl1_errorFlag;        /* Error flag                               */
    
    /* Initialization of the local variables */
    l_bu4_returnValue    = R_RFD_OK;
    l_bu4_returnInternal = R_RFD_OK;
    l_bu4_timeout        = 0UL;
    l_bu2_FACIMode       = 0U;
    l_bl1_timeoutFlag    = R_RFD_FALSE;
    l_bl1_errorFlag      = R_RFD_FALSE;
    
    
    /******************************************************************************************************************
     *  Save the current mode for recovering
     *****************************************************************************************************************/
    
    l_bu4_returnValue = R_RFD_CheckPEMode(i_u2_TargetFACI, R_RFD_MODE_DFPE);
    
    if (l_bu4_returnValue == R_RFD_OK)
    {
        l_bu2_FACIMode = (T_u2)R_RFD_MODE_DFPE;
    }
    else
    {
        l_bu4_returnValue = R_RFD_CheckPEMode(i_u2_TargetFACI, R_RFD_MODE_CFPE);
        
        if (l_bu4_returnValue == R_RFD_OK)
        {
            l_bu2_FACIMode = (T_u2)R_RFD_MODE_CFPE;
        }
        else
        {
            l_bu2_FACIMode = (T_u2)R_RFD_MODE_READ;
        }
        
    }
    
    /******************************************************************************************************************
     *  Suspension process of the target FACI
     *****************************************************************************************************************/
    
    l_bu4_returnValue = Sample_SuspendPE(i_u2_TargetFACI);
    
    /* Set the timeout value for checking suspended status */
    l_bu4_timeout = 10000UL;          /* !QAC message 3120 */
    
    /* Check whether the status to be suspended */
    if (l_bu4_returnValue == R_RFD_STS_BUSY)
    {
        do
        {
            l_bu4_returnValue = Sample_CheckFaciStatus(i_u2_TargetFACI);
            l_bu4_timeout--;        /* !CERT-C rule INT30 (QAC message 3383) */
            
            /* Check timeout */
            if (l_bu4_timeout == 0UL)
            {
                /* Timeout has occurred */
                l_bl1_timeoutFlag = R_RFD_TRUE;   /* Timeout occured */
                break;
            }
            else
            {
                /* no operation */
            }
        } while (l_bu4_returnValue == R_RFD_STS_BUSY);
    }
    else
    {
        /* no operation */
    }
    
    /* Whether a timeout has occurred  */
    if (l_bl1_timeoutFlag == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
    {
        l_bu4_returnValue = R_RFD_ERR_TIMEOUT;
    }
    else
    {
        /* no operation */
    }
    
    /******************************************************************************************************************
     *  Shift the mode to the read mode
     *****************************************************************************************************************/
    
    /* Suspension process was timeout */
    if (l_bl1_timeoutFlag == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* no operation */
    }
    /* Suspension process was not timeout */
    else
    {
        if (l_bu4_returnValue == R_RFD_ERR_FHVE_PROTECT)
        {
            l_bl1_errorFlag = R_RFD_TRUE;   /* Error occurred */
        }
        else
        {
            /* Shift the mode to the read mode */
            l_bu4_returnInternal = l_bu4_returnValue;   /* Save the return value */
            l_bu4_returnValue    = R_RFD_ShiftToReadMode(i_u2_TargetFACI);
            
            if (l_bu4_returnValue != R_RFD_OK)
            {
                l_bl1_errorFlag = R_RFD_TRUE;   /* Error occurred */
            }
            else
            {
                /* no operation */
            }
        }
    }
    
    /******************************************************************************************************************
     *  Processing during suspension status
     *****************************************************************************************************************/
    
    if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_timeoutFlag == R_RFD_FALSE))
    {                                                   /* !CERT-C rule INT02 (QAC message 2100) */
        /* Describe the processing that the user wants to process */
    }
    else
    {
        /* no operation */
    }
    
    /******************************************************************************************************************
     *  Shift the mode to the P/E mode
     *****************************************************************************************************************/
    
    if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_timeoutFlag == R_RFD_FALSE))
    {                                                   /* !CERT-C rule INT02 (QAC message 2100) */
        
        l_bu4_returnValue = R_RFD_ShiftToPEMode(i_u2_TargetFACI, (T_en_FACIMode)l_bu2_FACIMode);
                                                        /* !MISRA-C 2012 rule 10.5 / QAC message 4342 */
        /* Set the timeout value for checking whether the mode is P/E mode */
        l_bu4_timeout = 10000UL;                 /* !QAC message 3120 */
        
        /* Mode has not already R_RFD_MODE_DFPE */
        if (l_bu4_returnValue == R_RFD_STS_BUSY)
        {
            /* Check whether the mode shift to P/E mode */
            do
            {
                l_bu4_returnValue = R_RFD_CheckPEMode(i_u2_TargetFACI, (T_en_FACIMode)l_bu2_FACIMode);
                                                        /* !MISRA-C 2012 rule 10.5 / QAC message 4342 */
                
                l_bu4_timeout--;                        /* !CERT-C rule INT30 (QAC message 3383) */
                
                /* Check timeout */
                if (l_bu4_timeout == 0UL)
                {
                    /* Timeout */
                    l_bl1_timeoutFlag = R_RFD_TRUE;   /* Timeout occured */
                    break;
                }
                else
                {
                    /* no operation */
                }
            } while (l_bu4_returnValue == R_RFD_STS_BUSY);
            
            /* Whether the mode does not shift to the P/E mode */
            if (l_bu4_returnValue != R_RFD_OK)
            {
                l_bl1_errorFlag   = R_RFD_TRUE;     /* Error occurred */
                
                /* Shift the mode to the read mode */
                l_bu4_returnValue = R_RFD_ShiftToReadMode(i_u2_TargetFACI);
                
                if (l_bu4_returnValue != R_RFD_ERR_INTERNAL_HW)
                {
                    l_bu4_returnValue = R_RFD_ERR_TIMEOUT;  /* Set return value */
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
        }
        else if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
        {
            l_bl1_errorFlag = R_RFD_TRUE;   /* Error occurred */
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
     *  Resume the suspension process for the target FACI
     *****************************************************************************************************************/
    
    if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_timeoutFlag == R_RFD_FALSE))
    {                                                   /* !CERT-C rule INT02 (QAC message 2100) */
        /* Check FACI Status */
        if (l_bu4_returnInternal != R_RFD_OK)
        {
            l_bu4_returnValue = R_RFD_GetFaciStatus(i_u2_TargetFACI);
            
            /* Check whether current status is suspension status */
            /* Current status is suspension status */
            if ((l_bu4_returnValue == R_RFD_STS_ERASE_SUSPENDED) || (l_bu4_returnValue == R_RFD_STS_WRITE_SUSPENDED))
            {
                l_bu4_returnValue = Sample_ResumePE(i_u2_TargetFACI);
            }
            else
            {
                /* no operation */
            }
        }
        else
        {
            l_bu4_returnValue = l_bu4_returnInternal;   /* Error when suspension process has occurred  */
        }
    }
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);

}
