/**********************************************************************************************************************
    Program Name    : Sample program for Renesas Flash Driver (RFD28F)
    
    File Name       : sample_common_control.h
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
 *   Rule         : MISRA-C 2012 rule Dir-4.6 / QAC message 5209
 *   Message      : Use of basic type '%s'.
 *   Reason       : Since we have defined a main function for each PE, we have defined the return value as an
 *                  int type.
 *   Verification : Incorrect declaration would result in compilation fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule DCL00 / QAC message 3204
 *   Message      : The variable '%s' is only set once and so it could be declared with the 'const' qualifier.
 *   Reason       : The relevant part can be declared with const, but since it is easier to read
 *                  if it is implemented with code equivalent to the similar part, we will leave it as it is.
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

#ifndef SAMPLE_COMMON_CONTROL_H
#define SAMPLE_COMMON_CONTROL_H

#include "sample_flash_control.h"   /* !CERT-C rule 5002 */

/**********************************************************************************************************************
    Prototype declaration
**********************************************************************************************************************/

/* !QAC message 0776 */

extern T_u4_RFDReturn  Sample_SuspendPE(T_u2_FACI i_u2_TargetFACI);
extern T_u4_RFDReturn  Sample_ResumePE(T_u2_FACI i_u2_TargetFACI);
extern T_u4_RFDReturn  Sample_ReleaseCommandLock(T_u2_FACI i_u2_TargetFACI);
extern T_u4_RFDReturn  Sample_CheckFaciStatus(T_u2_FACI i_u2_TargetFACI);
extern T_u4_RFDReturn  Sample_SuspendResume(T_u2_FACI i_u2_TargetFACI);

#endif
