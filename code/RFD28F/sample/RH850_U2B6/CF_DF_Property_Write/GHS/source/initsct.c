/**********************************************************************************************************************
    Program Name    : Sample program for Renesas Flash Driver (RFD28F)
    
    File Name       : initsct.c
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
 *   Rule         : MISRA-C 2012 rule 11.4 / QAC message 0306
 *   Message      : Cast between a pointer to object and an integral type.
 *   Reason       : This code is provided by the GHS and is recommended for use during initialization. 
 *                  Therefore, this sample use it as it is without changing it.
 *   Verification : The converted addresses are essential for complete code execution.
 *                  Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 11.5 / QAC message 0316
 *   Message      : Cast from a pointer to void to a pointer to object type.
 *   Reason       : This code is provided by the GHS and is recommended for use during initialization. 
 *                  Therefore, this sample use it as it is without changing it.
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
 *   Rule         : CERT-C rule DCL00 / QAC message 3227
 *   Message      : The parameter '%s' is never modified and so it could be declared with the 'const' qualifier.
 *   Reason       : This code is provided by the GHS and is recommended for use during initialization. 
 *                  Therefore, this sample use it as it is without changing it.
 *   Verification : No violation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule Dir-4.6 / QAC message 5209
 *   Message      : Use of basic type '%s'.
 *   Reason       : This code is provided by the GHS and is recommended for use during initialization. 
 *                  Therefore, this sample use it as it is without changing it.
 *   Verification : The converted addresses are essential for complete code execution.
 *                  Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

#include "sample_flash_control.h"

/* section information */
typedef struct {
    unsigned long dest;     /* Destination Address  */  /* !MISRA-C 2012 rule Dir-4.6 / QAC message 5209 */
    unsigned long src;      /* Source Address       */  /* !MISRA-C 2012 rule Dir-4.6 / QAC message 5209 */
    unsigned long size;     /* Section Size         */  /* !MISRA-C 2012 rule Dir-4.6 / QAC message 5209 */
} SEC_INFO;

/* Prototype declaration */
void    initsct(void *p_sinfo_copy, void *p_einfo_copy, void *p_sinfo_clear, void *p_einfo_clear);

#ifdef  __GHS__
#pragma ghs section text=".startup"
#endif

/**********************************************************************************************************************
    Function Name   : initsct

    - Outline
        Copies initialization data on ROM to RAM
        Clears RAM
        This is GHS sample.
**********************************************************************************************************************/

/* !CERT-C rule DCL00 (QAC message 3227)     */

void
initsct(void *p_sinfo_copy, void *p_einfo_copy, void *p_sinfo_clear, void *p_einfo_clear)
{
    
    SEC_INFO        *p_info;
    SEC_INFO        *p_einfo;
    unsigned long   n;          /* !MISRA-C 2012 rule Dir-4.6 / QAC message 5209 */
    unsigned char   *p;         /* !MISRA-C 2012 rule Dir-4.6 / QAC message 5209 */
    unsigned char   *q;         /* !MISRA-C 2012 rule Dir-4.6 / QAC message 5209 */
    
    /**********************************************************************************************
     *  Copy data from ROM to RAM
     *********************************************************************************************/
    
    p_info  = (SEC_INFO *)p_sinfo_copy;     /* !MISRA-C 2012 rule 11.5 / QAC message 0316 */
    p_einfo = (SEC_INFO *)p_einfo_copy;     /* !MISRA-C 2012 rule 11.5 / QAC message 0316 */
    
    while (p_info < p_einfo)
    {
        if (p_info->size != 0UL)
        {
            n = p_info->size;
            p = (unsigned char *)p_info->src;   /* !MISRA-C 2012 rule 11.4 / QAC message 0306    */
                                                /* !MISRA-C 2012 rule Dir-4.6 / QAC message 5209 */
            q = (unsigned char *)p_info->dest;  /* !MISRA-C 2012 rule 11.4 / QAC message 0306    */
                                                /* !MISRA-C 2012 rule Dir-4.6 / QAC message 5209 */
            while (n > 0UL)
            {
                *q = *p;
                q++;
                p++;
                n--;
            }
        }
        else
        {
            /* no operation */
        }
        p_info++;
    }
    
    /**********************************************************************************************
     *  Clear RAM
     *********************************************************************************************/
    
    p_info  = (SEC_INFO *)p_sinfo_clear;    /* !MISRA-C 2012 rule 11.5 / QAC message 0316 */
    p_einfo = (SEC_INFO *)p_einfo_clear;    /* !MISRA-C 2012 rule 11.5 / QAC message 0316 */
    
    while (p_info < p_einfo)
    {
        if (p_info->size != 0UL)
        {
            n = p_info->size;
            p = (unsigned char *)p_info->dest;  /* !MISRA-C 2012 rule 11.4 / QAC message 0306    */
                                                /* !MISRA-C 2012 rule Dir-4.6 / QAC message 5209 */
            while (n > 0UL)
            {
                *p = 0U;
                p++;
                n--;
            }
        }
        else
        {
            /* no operation */
        }
        p_info++;
    }
    
    return;
    
}
