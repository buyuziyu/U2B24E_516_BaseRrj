/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD28F)
    
    File Name       : r_rfd_common_api.h
    Program Version : V1.00
    File Revision   : $Rev: 4343 $
    File Date       : $Date:: 2023-05-17 16:23:15 +0700#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : Include file for prototype definition of API for Common Flash Control Component
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
 *   Rule         : CERT-C rule 5002
 *   Message      : The header '%s' file name shadows a previously included header.
 *   Reason       : The header file of the RFD28F starts with "r_rfd", and in the case of a component-specific
 *                  header file is given a component name to improve identification.
 *                  It is intentional and there is no problem.
 *   Verification : Incorrect processing would result in test fails.
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

#ifndef R_RFD_COMMON_API_H
#define R_RFD_COMMON_API_H

#include "r_rfd_types.h"            /* !CERT-C rule 5002 */
#include "r_rfd_common_types.h"     /* !CERT-C rule 5002 */

/**********************************************************************************************************************
    For Common Flash Control Component
**********************************************************************************************************************/

/**********************************************************************************************************************
    Prototype declaration
**********************************************************************************************************************/

/* !QAC message 0776 */

extern T_u4_RFDReturn  R_RFD_Init(T_u2 i_u2_FaciFrequency);
extern T_u4_RFDReturn  R_RFD_ShiftToReadMode(T_u2_FACI i_u2_TargetFACI);
extern T_u4_RFDReturn  R_RFD_ShiftToPEMode(T_u2_FACI i_u2_TargetFACI, T_en_FACIMode i_en_FACIMode);
extern T_u4_RFDReturn  R_RFD_CheckPEMode(T_u2_FACI i_u2_TargetFACI, T_en_FACIMode i_en_FACIMode);
extern T_u4_RFDReturn  R_RFD_ForcedStopAndErrorClear(T_u2_FACI i_u2_TargetFACI);
extern T_u4_RFDReturn  R_RFD_StatusClear(T_u2_FACI i_u2_TargetFACI);
extern T_u4_RFDReturn  R_RFD_GetFaciSequenceReady(T_u2_FACI i_u2_TargetFACI);
extern T_u4_RFDReturn  R_RFD_GetFaciStatus(T_u2_FACI i_u2_TargetFACI);
extern T_u4_RFDReturn  R_RFD_SuspendPERequest(T_u2_FACI i_u2_TargetFACI);
extern T_u4_RFDReturn  R_RFD_ResumePERequest(T_u2_FACI i_u2_TargetFACI);
extern T_u4_RFDReturn  R_RFD_SetFHVE(T_u2_FACI i_u2_TargetFACI, T_en_Protect i_en_ProtectMode);
extern void            R_RFD_HOOK_EnterCriticalSection(void);
extern void            R_RFD_HOOK_ExitCriticalSection(void);

#endif  /* R_RFD_COMMON_API_H */
