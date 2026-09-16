/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD28F)
    
    File Name       : r_rfd_userown.c
    Program Version : V1.00
    File Revision   : $Rev: 4343 $
    File Date       : $Date:: 2023-05-17 16:23:15 +0700#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : Userown API for Common Process
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

#include "r_rfd_config.h"
#include "r_rfd.h"
#include "r_rfd_common.h"
#include "r_rfd_common_local.h"
#include "r_rfd_common_version.h"

/**************************************************************************************************************
 *  Declared the section
 *    - Text Section Definition for Userown of Common Component
 *
 *  - Traceability          : [Covers:UD_20_008]
 *************************************************************************************************************/

/* Start Text Section Definition */
#define  R_RFD_USEROWN_COMMON_START_SEC_CODE
#include "r_rfd_memmap.h"

/**********************************************************************************************************************
**  Function Name   : R_RFD_HOOK_EnterCriticalSection
**  
**  - Outline
**      Perform processing to enter critical section
**  - Format
**      void
**          R_RFD_HOOK_EnterCriticalSection(void);
**  - Input parameter
**      non parameter
**  - Return
**      non return value
**  - Preconditions
**      non preconditions
**  
**  - Traceability        : [Covers:UD_01_210]
**********************************************************************************************************************/

void
R_RFD_HOOK_EnterCriticalSection(void)
{
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_HOOK_ExitCriticalSection
**  
**  - Outline
**      Perform processing to exit critical section
**  - Format
**      void
**          R_RFD_HOOK_ExitCriticalSection(void);
**  - Input parameter
**      non parameter
**  - Return
**      non return value
**  - Preconditions
**      non preconditions
**  
**  - Traceability        : [Covers:UD_01_220]
**********************************************************************************************************************/

void
R_RFD_HOOK_ExitCriticalSection(void)
{
    
    return;
    
}

/**************************************************************************************************************
 *  Declared the section
 *    - End of Text Section Definition for Common Flash Control Component
 *************************************************************************************************************/

/* Stop Text Section Definition */
#define  R_RFD_USEROWN_COMMON_STOP_SEC_CODE
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */

