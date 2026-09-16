/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD28F)
    
    File Name       : r_rfd_common_error.h
    Program Version : V1.00
    File Revision   : $Rev: 4343 $
    File Date       : $Date:: 2023-05-17 16:23:15 +0700#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : Include file for error definition for Common Flash Control Component
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

#ifndef R_RFD_COMMON_ERROR_H
#define R_RFD_COMMON_ERROR_H

/**********************************************************************************************************************
    For Common Flash Control Component
**********************************************************************************************************************/

/**********************************************************************************************************************
    Return value
    
    - Traceability          : [Covers:UD_14_000]
**********************************************************************************************************************/

#define R_RFD_OK                            0x00000000UL
#define R_RFD_STS_READY                     0x00000001UL
#define R_RFD_STS_BUSY                      0x00000002UL
#define R_RFD_WARN_SWITCH_DATA              0x00000004UL
#define R_RFD_WARN_SECURITY_DATA            0x00000005UL
#define R_RFD_WARN_BLOCKPROTECTION0_DATA    0x00000006UL
#define R_RFD_WARN_BLOCKPROTECTION1_DATA    0x00000007UL
#define R_RFD_WARN_CONFIGURATION_DATA       0x00000008UL
#define R_RFD_WARN_ERASECOUNTER_DATA        0x00000009UL
#define R_RFD_WARN_INTERNAL_DATA            0x0000000aUL
#define R_RFD_STS_ERASE_SUSPENDED           0x00000010UL
#define R_RFD_STS_WRITE_SUSPENDED           0x00000011UL
#define R_RFD_ERR_FHVE_PROTECT              0x00001000UL
#define R_RFD_ERR_ACCESS_ENV                0x00001001UL
#define R_RFD_ERR_INTERNAL_DATA             0x00001002UL
#define R_RFD_ERR_ERASE                     0x00001003UL
#define R_RFD_ERR_WRITE                     0x00001004UL
#define R_RFD_ERR_INTERNAL_HW               0x00001005UL
#define R_RFD_ERR_ERASECOUNTER_DATA         0x00001006UL
#define R_RFD_ERR_SWITCH_DATA               0x00001007UL
#define R_RFD_ERR_SECURITY_DATA             0x00001008UL
#define R_RFD_ERR_BLOCKPROTECTION0_DATA     0x00001009UL
#define R_RFD_ERR_BLOCKPROTECTION1_DATA     0x0000100aUL
#define R_RFD_ERR_CONFIGURATION_DATA        0x0000100bUL
#define R_RFD_ERR_REJECT                    0x00000100UL
#define R_RFD_ERR_NOFACI                    0x00000101UL
#define R_RFD_ERR_FACI_DEFINITION           0x00000102UL
#define R_RFD_ERR_FPMON                     0x00000105UL

/**********************************************************************************************************************
    Masking value for Return value
**********************************************************************************************************************/

#define R_RFD_ERR_CMD_LOCK          0x00001000UL
#define R_RFD_ERR_NO_CMD_LOCK       0x00000100UL
#define R_RFD_STS_SUSPENDING        0x00000010UL


#endif  /* R_RFD_COMMON_ERROR_H */
