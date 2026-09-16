/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD28F)
    
    File Name       : r_rfd_commmon_definition.c
    Program Version : V1.00
    File Revision   : $Rev: 4343 $
    File Date       : $Date:: 2023-05-17 16:23:15 +0700#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : Definitions for Common Process
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

#include "r_rfd.h"
#include "r_rfd_common_local.h"

/**************************************************************************************************************
 *  Section declaration
 *    - Definition of the data section
 *
 *  - Traceability          : [Covers:UD_20_010] [Covers:UD_20_011]
 *
 *  Section ".R_RFD_CODE_EX_PROT" is defined in linker directive file
 *
 *  - Traceability          : [Covers:UD_20_005]
 *************************************************************************************************************/

/**********************************************************************************************************************
 *  Definition of the external variable
 *
 *  - Traceability          : [Covers:UD_11_000]
 *********************************************************************************************************************/

#define  R_RFD_WORK_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "r_rfd_memmap.h"

T_u4    bu4_CMN_FaciBaseAddress;    /* Base address of FACI                                     */
T_u4    bu4_CMN_FaciCommandArea;    /* Address for the area of issuing command                  */

/**********************************************************************************************************************
 *  Definition of the external variable for STUB
 *********************************************************************************************************************/

#ifdef __R_RFD_USE_STUB__

struct faciRegisters   base_Faci0;
struct faciRegisters   base_Faci1;
struct faciRegisters   base_Faci2;

#endif  /* __R_RFD_USE_STUB__ */


/**************************************************************************************************************
 *  Section declaration
 *    - End of the definition of the data section
 *************************************************************************************************************/

#define  R_RFD_WORK_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

