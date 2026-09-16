/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD28F)
    
    File Name       : r_rfd_memmap.h
    Program Version : V1.00
    File Revision   : $Rev: 4343 $
    File Date       : $Date:: 2023-05-17 16:23:15 +0700#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : Include file for memory map information (AUTOSAR Format)
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
 *   Rule         : MISRA-C 2012 dir 4.10 / QAC message 0883
 *   Message      : Include file code is not protected against repeated inclusion.
 *   Reason       : This file compliant AUTOSAR format. So, there is no need to protect against repeated inclusion
 *   Verification : Incorrect declaration would result in compilation fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 20.5 / QAC message 0841
 *   Message      : Using '#undef'.
 *   Reason       : This file compliant AUTOSAR format. So, there is need to use #undef.
 *   Verification : Incorrect declaration would result in compilation fails.
 *********************************************************************************************************************/

/* !MISRA-C 2012 dir 4.10 (QAC message 0883) */

/**********************************************************************************************************************
    Module section mapping
    
    - Traceability          : [Covers:UD_20_000] [Covers:UD_20_001] [Covers:UD_20_002] [Covers:UD_20_003]
                              [Covers:UD_20_004] [Covers:UD_20_005] [Covers:UD_20_010] [Covers:UD_20_011]
                              [Covers:UD_40_000] [Covers:UD_40_001] [Covers:UD_40_002] [Covers:UD_40_010]
                              [Covers:UD_40_011]
                              [Covers:UD_60_000] [Covers:UD_60_001] [Covers:UD_60_002] [Covers:UD_60_003]
                              [Covers:UD_60_004] [Covers:UD_60_010] [Covers:UD_60_011]
**********************************************************************************************************************/

/**********************************************************************************************************************
    For GHS Compiler
**********************************************************************************************************************/

#ifdef  __ghs__

/**********************************************************************************************************************
    The symbol 'START_WITH_IF' is undefined.

    Thus, the preprocessor continues searching for defined symbols
    This first #ifdef makes integration of delivered parts of MemMap.h
    easier because every supplier starts with #elif
**********************************************************************************************************************/

/* !MISRA-C 2012 dir 20.5 (QAC message 0841) */

    #if defined (START_WITH_IF)
        
    /**********************************************************************************************
     * Code Section
     *********************************************************************************************/
        
    /* Section definition for Common Component */
    #elif defined (R_RFD_COMMON_START_SEC_CODE)
        
        #ifdef  R_RFD_COMMON_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_COMMON_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_COMMON_CODE_SEC_STARTED
            #undef  R_RFD_COMMON_START_SEC_CODE
            #pragma ghs section text = ".R_RFD_CODE_COMMON"
        #endif
        
    #elif defined (R_RFD_COMMON_STOP_SEC_CODE)
        
        #ifndef R_RFD_COMMON_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_COMMON_START_SEC_CODE) is not started."
        #else
            #undef  R_RFD_COMMON_CODE_SEC_STARTED
            #undef  R_RFD_COMMON_STOP_SEC_CODE
            #pragma ghs section text = default
        #endif
        
    /* Section definition for Common Component (on RAM when No BGO condition) */
    #elif defined (R_RFD_COMMON_RAM_NO_BGO_START_SEC_CODE)
        
        #ifdef  R_RFD_COMMON_RAM_NO_BGO_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_COMMON_RAM_NO_BGO_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_COMMON_RAM_NO_BGO_CODE_SEC_STARTED
            #undef  R_RFD_COMMON_RAM_NO_BGO_START_SEC_CODE
            #pragma ghs section text = ".R_RFD_CODE_COMMON_RAM_NO_BGO"
        #endif
        
    #elif defined (R_RFD_COMMON_RAM_NO_BGO_STOP_SEC_CODE)
        
        #ifndef R_RFD_COMMON_RAM_NO_BGO_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_COMMON_RAM_NO_BGO_START_SEC_CODE) is not started."
        #else
            #undef  R_RFD_COMMON_RAM_NO_BGO_CODE_SEC_STARTED
            #undef  R_RFD_COMMON_RAM_NO_BGO_STOP_SEC_CODE
            #pragma ghs section text = default
        #endif
        
    /* Section definition for Userown of Common Component */
    #elif defined (R_RFD_USEROWN_COMMON_START_SEC_CODE)
        
        #ifdef  R_RFD_USEROWN_COMMON_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_USEROWN_COMMON_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_USEROWN_COMMON_CODE_SEC_STARTED
            #undef  R_RFD_USEROWN_COMMON_START_SEC_CODE
            #pragma ghs section text = ".R_RFD_CODE_USEROWN_COMMON"
        #endif
        
    #elif defined (R_RFD_USEROWN_COMMON_STOP_SEC_CODE)
        
        #ifndef R_RFD_USEROWN_COMMON_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_USEROWN_COMMON_START_SEC_CODE) is not started."
        #else
            #undef  R_RFD_USEROWN_COMMON_CODE_SEC_STARTED
            #undef  R_RFD_USEROWN_COMMON_STOP_SEC_CODE
            #pragma ghs section text = default
        #endif
        
    /* Section definition for Data Flash Component */
    #elif defined (R_RFD_DF_START_SEC_CODE)
        
        #ifdef  R_RFD_DF_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_DF_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_DF_CODE_SEC_STARTED
            #undef  R_RFD_DF_START_SEC_CODE
            #pragma ghs section text = ".R_RFD_CODE_DF"
        #endif
    
    #elif defined (R_RFD_DF_STOP_SEC_CODE)
        
        #ifndef R_RFD_DF_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_DF_START_SEC_CODE) is not started."
        #else
            #undef  R_RFD_DF_CODE_SEC_STARTED
            #undef  R_RFD_DF_STOP_SEC_CODE
            #pragma ghs section text = default
        #endif
    
    /* Section definition for Code Flash Component */
    #elif defined (R_RFD_CF_START_SEC_CODE)
        
        #ifdef  R_RFD_CF_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_CF_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_CF_CODE_SEC_STARTED
            #undef  R_RFD_CF_START_SEC_CODE
            #pragma ghs section text = ".R_RFD_CODE_CF"
        #endif
    
    #elif defined (R_RFD_CF_STOP_SEC_CODE)
        
        #ifndef R_RFD_CF_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_CF_START_SEC_CODE) is not started."
        #else
            #undef  R_RFD_CF_CODE_SEC_STARTED
            #undef  R_RFD_CF_STOP_SEC_CODE
            #pragma ghs section text = default
        #endif
        
    /* Section definition for Code Flash Component (on RAM when No BGO condition) */
    #elif defined (R_RFD_CF_RAM_NO_BGO_START_SEC_CODE)
        
        #ifdef  R_RFD_CF_RAM_NO_BGO_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_CF_RAM_NO_BGO_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_CF_RAM_NO_BGO_CODE_SEC_STARTED
            #undef  R_RFD_CF_RAM_NO_BGO_START_SEC_CODE
            #pragma ghs section text = ".R_RFD_CODE_CF_RAM_NO_BGO"
        #endif
        
    #elif defined (R_RFD_CF_RAM_NO_BGO_STOP_SEC_CODE)
        
        #ifndef R_RFD_CF_RAM_NO_BGO_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_CF_RAM_NO_BGO_START_SEC_CODE) is not started."
        #else
            #undef  R_RFD_CF_RAM_NO_BGO_CODE_SEC_STARTED
            #undef  R_RFD_CF_RAM_NO_BGO_STOP_SEC_CODE
            #pragma ghs section text = default
        #endif
        
    /* Section definition for Extra Area of Code Flash Control Component */
    #elif defined (R_RFD_EXTRA_START_SEC_CODE)
        
        #ifdef  R_RFD_EXTRA_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_EXTRA_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_EXTRA_CODE_SEC_STARTED
            #undef  R_RFD_EXTRA_START_SEC_CODE
            #pragma ghs section text = ".R_RFD_CODE_EXTRA"
        #endif
        
    #elif defined (R_RFD_EXTRA_STOP_SEC_CODE)
        
        #ifndef R_RFD_EXTRA_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_EXTRA_START_SEC_CODE) is not started."
        #else
            #undef  R_RFD_EXTRA_CODE_SEC_STARTED
            #undef  R_RFD_EXTRA_STOP_SEC_CODE
            #pragma ghs section text = default
        #endif
        
    /**********************************************************************************************
     * Const Data Section
     *********************************************************************************************/
    
    /* Section definition for Const Data for Extra Area (Code Flash Component information) */
    #elif defined (R_RFD_EXTRA_START_SEC_CONST_UNSPECIFIED)
        
        #ifdef  R_RFD_EXTRA_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_EXTRA_STOP_SEC_CONST_UNSPECIFIED) is not stopped."
        #else
            #define R_RFD_EXTRA_CONST_SEC_STARTED
            #undef  R_RFD_EXTRA_START_SEC_CONST_UNSPECIFIED
            #pragma ghs section rodata = ".R_RFD_ROSDATA_EXTRA"
            #pragma ghs section rodata  = ".R_RFD_RODATA_EXTRA"
        #endif
        
    #elif defined (R_RFD_EXTRA_STOP_SEC_CONST_UNSPECIFIED)
        
        #ifndef  R_RFD_EXTRA_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_EXTRA_STOP_SEC_CONST_UNSPECIFIED) is not started."
        #else
            #undef  R_RFD_EXTRA_CONST_SEC_STARTED
            #undef  R_RFD_EXTRA_STOP_SEC_CONST_UNSPECIFIED
            #pragma ghs section rodata = default
            #pragma ghs section rodata  = default
        #endif
        
    /* Section definition for Const Data of Version for Common Component information */
    #elif defined (R_RFD_VERSION_COMMON_START_SEC_CONST_UNSPECIFIED)
        
        #ifdef  R_RFD_VERSION_COMMON_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_VERSION_COMMON_STOP_SEC_CONST_UNSPECIFIED) is not stopped."
        #else
            #define R_RFD_VERSION_COMMON_CONST_SEC_STARTED
            #undef  R_RFD_VERSION_COMMON_START_SEC_CONST_UNSPECIFIED
            #pragma ghs section rodata = ".R_RFD_ROSDATA_VERSION_COMMON"
            #pragma ghs section rodata  = ".R_RFD_RODATA_VERSION_COMMON"
        #endif
        
    #elif defined (R_RFD_VERSION_COMMON_STOP_SEC_CONST_UNSPECIFIED)
        
        #ifndef  R_RFD_VERSION_COMMON_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_VERSION_COMMON_STOP_SEC_CONST_UNSPECIFIED) is not started."
        #else
            #undef  R_RFD_VERSION_COMMON_CONST_SEC_STARTED
            #undef  R_RFD_VERSION_COMMON_STOP_SEC_CONST_UNSPECIFIED
            #pragma ghs section rodata = default
            #pragma ghs section rodata  = default
        #endif
    
    /* Section definition for Const Data of Version for Data Flash Component information */
    #elif defined (R_RFD_VERSION_DF_START_SEC_CONST_UNSPECIFIED)
        
        #ifdef  R_RFD_VERSION_DF_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_VERSION_DF_STOP_SEC_CONST_UNSPECIFIED) is not stopped."
        #else
            #define R_RFD_VERSION_DF_CONST_SEC_STARTED
            #undef  R_RFD_VERSION_DF_START_SEC_CONST_UNSPECIFIED
            #pragma ghs section rodata = ".R_RFD_ROSDATA_VERSION_DF"
            #pragma ghs section rodata  = ".R_RFD_RODATA_VERSION_DF"
        #endif
        
    #elif defined (R_RFD_VERSION_DF_STOP_SEC_CONST_UNSPECIFIED)
        
        #ifndef  R_RFD_VERSION_DF_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_VERSION_DF_STOP_SEC_CONST_UNSPECIFIED) is not started."
        #else
            #undef  R_RFD_VERSION_DF_CONST_SEC_STARTED
            #undef  R_RFD_VERSION_DF_STOP_SEC_CONST_UNSPECIFIED
            #pragma ghs section rodata = default
            #pragma ghs section rodata  = default
        #endif
    
    /* Section definition for Const Data of Version for Code Flash Component information */
    #elif defined (R_RFD_VERSION_CF_START_SEC_CONST_UNSPECIFIED)
        
        #ifdef  R_RFD_VERSION_CF_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_VERSION_CF_STOP_SEC_CONST_UNSPECIFIED) is not stopped."
        #else
            #define R_RFD_VERSION_CF_CONST_SEC_STARTED
            #undef  R_RFD_VERSION_CF_START_SEC_CONST_UNSPECIFIED
            #pragma ghs section rodata = ".R_RFD_ROSDATA_VERSION_CF"
            #pragma ghs section rodata  = ".R_RFD_RODATA_VERSION_CF"
        #endif
        
    #elif defined (R_RFD_VERSION_CF_STOP_SEC_CONST_UNSPECIFIED)
        
        #ifndef  R_RFD_VERSION_CF_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_VERSION_CF_STOP_SEC_CONST_UNSPECIFIED) is not started."
        #else
            #undef  R_RFD_VERSION_CF_CONST_SEC_STARTED
            #undef  R_RFD_VERSION_CF_STOP_SEC_CONST_UNSPECIFIED
            #pragma ghs section rodata = default
            #pragma ghs section rodata  = default
        #endif
    
    /**********************************************************************************************
     * Data Section
     *********************************************************************************************/
    
    /* Section definition for No Initialization Data */
    #elif defined (R_RFD_WORK_START_SEC_VAR_NOINIT_UNSPECIFIED)
    
        #ifdef  R_RFD_WORK_NOINIT_VAR_SEC_STARTED
            #error  "Memory section (R_RFD_WORK_START_SEC_VAR_NOINIT_UNSPECIFIED) is not stopped."
        #else
            #define R_RFD_WORK_NOINIT_VAR_SEC_STARTED
            #undef  R_RFD_WORK_START_SEC_VAR_NOINIT_UNSPECIFIED
            #pragma ghs section bss  = ".R_RFD_BSS"
            #pragma ghs section bss = ".R_RFD_SBSS"
        #endif
    
    #elif defined (R_RFD_WORK_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
    
        #ifndef  R_RFD_WORK_NOINIT_VAR_SEC_STARTED
            #error  "Memory section (R_RFD_WORK_START_SEC_VAR_NOINIT_UNSPECIFIED) is not started."
        #else
            #undef  R_RFD_WORK_NOINIT_VAR_SEC_STARTED
            #undef  R_RFD_WORK_STOP_SEC_VAR_NOINIT_UNSPECIFIED
            #pragma ghs section bss  = default
            #pragma ghs section bss = default
        #endif
        
    #else
        #error "r_rfd_memmap.h: No valid section definition found."
        
    #endif  /* START_WITH_IF */
    
#endif  /* __ghs__ */


/**********************************************************************************************************************
    For Renesas Compiler (CC-RH)
**********************************************************************************************************************/

#ifdef  __RENESAS__

/**********************************************************************************************************************
    The symbol 'START_WITH_IF' is undefined.

    Thus, the preprocessor continues searching for defined symbols
    This first #ifdef makes integration of delivered parts of MemMap.h
    easier because every supplier starts with #elif
**********************************************************************************************************************/

    #if defined (START_WITH_IF)
        
    /**********************************************************************************************
     * Code Section
     *********************************************************************************************/
        
    /* Section definition for Common Component */
    #elif defined (R_RFD_COMMON_START_SEC_CODE)
        
        #ifdef  R_RFD_COMMON_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_COMMON_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_COMMON_CODE_SEC_STARTED
            #undef  R_RFD_COMMON_START_SEC_CODE
            #pragma section .R_RFD_CODE_COMMON
        #endif
        
    #elif defined (R_RFD_COMMON_STOP_SEC_CODE)
        
        #ifndef R_RFD_COMMON_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_COMMON_START_SEC_CODE) is not started."
        #else
            #undef  R_RFD_COMMON_CODE_SEC_STARTED
            #undef  R_RFD_COMMON_STOP_SEC_CODE
            #pragma section default
        #endif
        
    /* Section definition for Common Component (on RAM when No BGO condition) */
    #elif defined (R_RFD_COMMON_RAM_NO_BGO_START_SEC_CODE)
        
        #ifdef  R_RFD_COMMON_RAM_NO_BGO_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_COMMON_RAM_NO_BGO_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_COMMON_RAM_NO_BGO_CODE_SEC_STARTED
            #undef  R_RFD_COMMON_RAM_NO_BGO_START_SEC_CODE
            #pragma section .R_RFD_CODE_COMMON_RAM_NO_BGO
        #endif
        
    #elif defined (R_RFD_COMMON_RAM_NO_BGO_STOP_SEC_CODE)
        
        #ifndef R_RFD_COMMON_RAM_NO_BGO_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_COMMON_RAM_NO_BGO_START_SEC_CODE) is not started."
        #else
            #undef  R_RFD_COMMON_RAM_NO_BGO_CODE_SEC_STARTED
            #undef  R_RFD_COMMON_RAM_NO_BGO_STOP_SEC_CODE
            #pragma section default
        #endif
        
    /* Section definition for Userown of Common Component */
    #elif defined (R_RFD_USEROWN_COMMON_START_SEC_CODE)
        
        #ifdef  R_RFD_USEROWN_COMMON_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_USEROWN_COMMON_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_USEROWN_COMMON_CODE_SEC_STARTED
            #undef  R_RFD_USEROWN_COMMON_START_SEC_CODE
            #pragma section .R_RFD_CODE_USEROWN_COMMON
        #endif
        
    #elif defined (R_RFD_USEROWN_COMMON_STOP_SEC_CODE)
        
        #ifndef R_RFD_USEROWN_COMMON_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_USEROWN_COMMON_START_SEC_CODE) is not started."
        #else
            #undef  R_RFD_USEROWN_COMMON_CODE_SEC_STARTED
            #undef  R_RFD_USEROWN_COMMON_STOP_SEC_CODE
            #pragma section default
        #endif
        
    /* Section definition for Data Flash Component */
    #elif defined (R_RFD_DF_START_SEC_CODE)
        
        #ifdef  R_RFD_DF_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_DF_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_DF_CODE_SEC_STARTED
            #undef  R_RFD_DF_START_SEC_CODE
            #pragma section .R_RFD_CODE_DF
        #endif
    
    #elif defined (R_RFD_DF_STOP_SEC_CODE)
        
        #ifndef R_RFD_DF_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_DF_STOP_SEC_CODE) is not started."
        #else
            #undef  R_RFD_DF_CODE_SEC_STARTED
            #undef  R_RFD_DF_STOP_SEC_CODE
            #pragma section default
        #endif
    
    /* Section definition for Code Flash Component */
    #elif defined (R_RFD_CF_START_SEC_CODE)
        
        #ifdef  R_RFD_CF_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_CF_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_CF_CODE_SEC_STARTED
            #undef  R_RFD_CF_START_SEC_CODE
            #pragma section .R_RFD_CODE_CF
        #endif
    
    #elif defined (R_RFD_CF_STOP_SEC_CODE)
        
        #ifndef R_RFD_CF_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_CF_STOP_SEC_CODE) is not started."
        #else
            #undef  R_RFD_CF_CODE_SEC_STARTED
            #undef  R_RFD_CF_STOP_SEC_CODE
            #pragma section default
        #endif
        
    /* Section definition for Code Flash Component (on RAM when No BGO condition) */
    #elif defined (R_RFD_CF_RAM_NO_BGO_START_SEC_CODE)
        
        #ifdef  R_RFD_CF_RAM_NO_BGO_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_CF_RAM_NO_BGO_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_CF_RAM_NO_BGO_CODE_SEC_STARTED
            #undef  R_RFD_CF_RAM_NO_BGO_START_SEC_CODE
            #pragma section .R_RFD_CODE_CF_RAM_NO_BGO
        #endif
        
    #elif defined (R_RFD_CF_RAM_NO_BGO_STOP_SEC_CODE)
        
        #ifndef R_RFD_CF_RAM_NO_BGO_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_CF_RAM_NO_BGO_START_SEC_CODE) is not started."
        #else
            #undef  R_RFD_CF_RAM_NO_BGO_CODE_SEC_STARTED
            #undef  R_RFD_CF_RAM_NO_BGO_STOP_SEC_CODE
            #pragma section default
        #endif
        
    /* Section definition for Extra Area of Code Flash Control Component */
    #elif defined (R_RFD_EXTRA_START_SEC_CODE)
        
        #ifdef  R_RFD_EXTRA_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_EXTRA_START_SEC_CODE) is not stopped."
        #else
            #define R_RFD_EXTRA_CODE_SEC_STARTED
            #undef  R_RFD_EXTRA_START_SEC_CODE
            #pragma section .R_RFD_CODE_EXTRA
        #endif
        
    #elif defined (R_RFD_EXTRA_STOP_SEC_CODE)
        
        #ifndef R_RFD_EXTRA_CODE_SEC_STARTED
            #error  "Memory section (R_RFD_EXTRA_START_SEC_CODE) is not started."
        #else
            #undef  R_RFD_EXTRA_CODE_SEC_STARTED
            #undef  R_RFD_EXTRA_STOP_SEC_CODE
            #pragma section default
        #endif
        
    /**********************************************************************************************
     * Const Data Section
     *********************************************************************************************/
    
    /* Section definition for Const Data for Extra Area (Code Flash Component information) */
    #elif defined (R_RFD_EXTRA_START_SEC_CONST_UNSPECIFIED)
        
        #ifdef  R_RFD_EXTRA_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_EXTRA_STOP_SEC_CONST_UNSPECIFIED) is not stopped."
        #else
            #define R_RFD_EXTRA_CONST_SEC_STARTED
            #undef  R_RFD_EXTRA_START_SEC_CONST_UNSPECIFIED
            #pragma section .R_RFD_RODATA_EXTRA
        #endif
        
    #elif defined (R_RFD_EXTRA_STOP_SEC_CONST_UNSPECIFIED)
        
        #ifndef  R_RFD_EXTRA_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_EXTRA_STOP_SEC_CONST_UNSPECIFIED) is not started."
        #else
            #undef  R_RFD_EXTRA_CONST_SEC_STARTED
            #undef  R_RFD_EXTRA_STOP_SEC_CONST_UNSPECIFIED
            #pragma section default
        #endif
        
    /* Section definition for Const Data of Version for Common Component information */
    #elif defined (R_RFD_VERSION_COMMON_START_SEC_CONST_UNSPECIFIED)
        
        #ifdef  R_RFD_VERSION_COMMON_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_VERSION_COMMON_STOP_SEC_CONST_UNSPECIFIED) is not stopped."
        #else
            #define R_RFD_VERSION_COMMON_CONST_SEC_STARTED
            #undef  R_RFD_VERSION_COMMON_START_SEC_CONST_UNSPECIFIED
            #pragma section .R_RFD_RODATA_VERSION_COMMON
        #endif
        
    #elif defined (R_RFD_VERSION_COMMON_STOP_SEC_CONST_UNSPECIFIED)
        
        #ifndef  R_RFD_VERSION_COMMON_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_VERSION_COMMON_STOP_SEC_CONST_UNSPECIFIED) is not started."
        #else
            #undef  R_RFD_VERSION_COMMON_CONST_SEC_STARTED
            #undef  R_RFD_VERSION_COMMON_STOP_SEC_CONST_UNSPECIFIED
            #pragma section default
        #endif
    
    /* Section definition for Const Data of Version for Data Flash Component information */
    #elif defined (R_RFD_VERSION_DF_START_SEC_CONST_UNSPECIFIED)
        
        #ifdef  R_RFD_VERSION_DF_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_VERSION_DF_STOP_SEC_CONST_UNSPECIFIED) is not stopped."
        #else
            #define R_RFD_VERSION_DF_CONST_SEC_STARTED
            #undef  R_RFD_VERSION_DF_START_SEC_CONST_UNSPECIFIED
            #pragma section .R_RFD_RODATA_VERSION_DF
        #endif
        
    #elif defined (R_RFD_VERSION_DF_STOP_SEC_CONST_UNSPECIFIED)
        
        #ifndef  R_RFD_VERSION_DF_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_VERSION_DF_STOP_SEC_CONST_UNSPECIFIED) is not started."
        #else
            #undef  R_RFD_VERSION_DF_CONST_SEC_STARTED
            #undef  R_RFD_VERSION_DF_STOP_SEC_CONST_UNSPECIFIED
            #pragma section default
        #endif
    
    /* Section definition for Const Data of Version for Code Flash Component information */
    #elif defined (R_RFD_VERSION_CF_START_SEC_CONST_UNSPECIFIED)
        
        #ifdef  R_RFD_VERSION_CF_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_VERSION_CF_STOP_SEC_CONST_UNSPECIFIED) is not stopped."
        #else
            #define R_RFD_VERSION_CF_CONST_SEC_STARTED
            #undef  R_RFD_VERSION_CF_START_SEC_CONST_UNSPECIFIED
            #pragma section .R_RFD_RODATA_VERSION_CF
        #endif
        
    #elif defined (R_RFD_VERSION_CF_STOP_SEC_CONST_UNSPECIFIED)
        
        #ifndef  R_RFD_VERSION_CF_CONST_SEC_STARTED
            #error  "Memory section (R_RFD_VERSION_CF_STOP_SEC_CONST_UNSPECIFIED) is not started."
        #else
            #undef  R_RFD_VERSION_CF_CONST_SEC_STARTED
            #undef  R_RFD_VERSION_CF_STOP_SEC_CONST_UNSPECIFIED
            #pragma section default
        #endif
     
    /**********************************************************************************************
     * Data Section
     *********************************************************************************************/
    
    /* Section definition for No Initialization Data */
    #elif defined (R_RFD_WORK_START_SEC_VAR_NOINIT_UNSPECIFIED)
    
        #ifdef  R_RFD_WORK_NOINIT_VAR_SEC_STARTED
            #error  "Memory section (R_RFD_WORK_START_SEC_VAR_NOINIT_UNSPECIFIED) is not stopped."
        #else
            #define R_RFD_WORK_NOINIT_VAR_SEC_STARTED
            #undef  R_RFD_WORK_START_SEC_VAR_NOINIT_UNSPECIFIED
            #pragma section .R_RFD_BSS
        #endif
    
    #elif defined (R_RFD_WORK_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
    
        #ifndef  R_RFD_WORK_NOINIT_VAR_SEC_STARTED
            #error  "Memory section (R_RFD_WORK_START_SEC_VAR_NOINIT_UNSPECIFIED) is not started."
        #else
            #undef  R_RFD_WORK_NOINIT_VAR_SEC_STARTED
            #undef  R_RFD_WORK_STOP_SEC_VAR_NOINIT_UNSPECIFIED
            #pragma section default
        #endif
        
    #else
        #error "r_rfd_memmap.h: No valid section definition found."
        
    #endif  /* START_WITH_IF */
    
#endif  /* __RENESAS__ */
