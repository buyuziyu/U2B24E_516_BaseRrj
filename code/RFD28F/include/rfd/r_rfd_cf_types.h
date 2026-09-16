/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD28F)
    
    File Name       : r_rfd_cf_types.h
    Program Version : V1.00
    File Revision   : $Rev: 4343 $
    File Date       : $Date:: 2023-05-17 16:23:15 +0700#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : Include file for type definition for Code Flash Control Component
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
 *   Rule         : CERT-C rule 5004 (DCL05)
 *   Message      : Use typedefs of non-pointer types only.
 *   Reason       : The corresponding typedef is defined as an API parameter type, and its use according to the
 *                  specification is assumed. Also, the naming rules make it possible to easily identify the pointer.
 *                  Therefore, usage like const-correct is not assumed and there is no problem.
 *   Verification : Incorrect processing would result in test fails.
 *********************************************************************************************************************/

#ifndef R_RFD_CF_TYPES_H
#define R_RFD_CF_TYPES_H

#include "r_rfd_types.h"    /* !CERT-C rule 5002 */

/**********************************************************************************************************************
    For Code Flash Control Component
    
    - Traceability          : [Covers:UD_20_000]
**********************************************************************************************************************/

/**********************************************************************************************************************
    Data types
**********************************************************************************************************************/

#ifndef R_RFD_COMMON_TYPES_H
    typedef T_u4    T_u4_RFDReturn;
    typedef T_u2    T_u2_FACI;
    typedef T_u4    T_u4_RfdAddress;
    typedef T_u4*   T_pu4_RfdBuffer;    /* !CERT-C rule 5004 (DCL05) */
#endif

/**********************************************************************************************************************
    Enum for Authenticate ID type
    
    - Traceability          : [Covers:UD_52_000]
**********************************************************************************************************************/

typedef enum
{
    R_RFD_ID_SPID    = 0x0000,
    R_RFD_ID_DFID    = 0x0001,
    R_RFD_ID_OCDID   = 0x0002,
    R_RFD_ID_CUSTIDA = 0x0004,
    R_RFD_ID_CUSTIDB = 0x0005,
    R_RFD_ID_CUSTIDC = 0x0006,
    R_RFD_ID_RHSIFID = 0x0007

} T_en_IDType;


#endif  /* R_RFD_CF_TYPES_H */
