/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD28F)
    
    File Name       : r_rfd_constant.h
    Program Version : V1.00
    File Revision   : $Rev: 4356 $
    File Date       : $Date:: 2023-05-22 14:27:05 +0700#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : Include file for constant value information
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

#ifndef R_RFD_CONSTANT_H
#define R_RFD_CONSTANT_H

/**********************************************************************************************************************
    For All Component
    
    - Traceability          : [Covers:UD_14_000]
**********************************************************************************************************************/

/**********************************************************************************************************************
    For Erasure suspend processing mode
**********************************************************************************************************************/

#define R_RFD_SUSPENSION_PRIORITY_MODE  0UL
#define R_RFD_ERASURE_PRIORITY_MODE     1UL

/**********************************************************************************************************************
    FACI Number
**********************************************************************************************************************/

#define R_RFD_FACI0         ((T_u2_FACI)0x0000U)
#define R_RFD_FACI1         ((T_u2_FACI)0x0001U)
#define R_RFD_FACI2         ((T_u2_FACI)0x0002U)
#define R_RFD_INVALID_FACI  ((T_u2_FACI)0x00ffU)

/**********************************************************************************************************************
    Definition of logical value
**********************************************************************************************************************/

#define R_RFD_TRUE      ((T_bl)1U)
#define R_RFD_FALSE     ((T_bl)0U)

#define R_RFD_ENABLE    1U
#define R_RFD_DISABLE   0U

/**********************************************************************************************************************
    Definition of Map Mode value
**********************************************************************************************************************/

#define R_RFD_SINGLE    0U
#define R_RFD_DOUBLE    1U

/**********************************************************************************************************************
    Definition of no defined
**********************************************************************************************************************/

#define R_RFD_NO_DEFINITION         0xFFFFFFFFUL
#define R_RFD_NO_DEFINED_ADDRESS    0xFFFFFFFFUL

/**********************************************************************************************************************
    For bit calculation
**********************************************************************************************************************/

#define R_RFD_LENGTH_BYTE1  ((T_u2)8U)      /* Number of bit of 1byte */
#define R_RFD_LENGTH_BYTE2  ((T_u2)16U)     /* Number of bit of 2byte */
#define R_RFD_LENGTH_BYTE4  ((T_u2)32U)     /* Number of bit of 4byte */


#endif  /* R_RFD_CONSTANT_H */
