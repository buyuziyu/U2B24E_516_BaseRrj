/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD28F)
    
    File Name       : r_rfd_cf_api.c
    Program Version : V1.00
    File Revision   : $Rev: 4348 $
    File Date       : $Date:: 2023-05-19 15:07:16 +0700#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : API for Code Flash
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
 *   Rule         : MISRA-C 2012 dir 1.1 / QAC message 1031
 *   Message      : Initializer for 'struct','union' or array type is not a constant expression.
 *   Reason       : Information for accessing each information of the Hardware Property Area is stored in the elements
 *                  of the array. Since the address required for access is determined at the time of building, it is
 *                  agreed to treat it as a constant value instead of a variable.
 *   Verification : Incorrect specification would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 3.1 / QAC message 3108
 *   Message      : Nested comments are not recognized in the ISO standard.
 *   Reason       : Description "//" is a part of URL, so This does not apply.
 *   Verification : No violation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 8.4 / QAC message 3408
 *   Message      : '%s' has external linkage and is being defined without any previous declaration.
 *   Reason       : The corresponding point is not declared for access from multiple components. 
 *                  This is "version information" to be placed in the const attribute area and is declared so
 *                  as to acquire it directly from the corresponding area.
 *   Verification : Incorrect declaration would result in compilation fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 8.9 / QAC message 3218
 *   Message      : File scope static, '%s', is only accessed in one function.
 *   Reason       : When declared in a function, variables area are allocated on the stack.
 *                  Furthermore, since there are many necessary variables, the consumption of RAM increases and
 *                  the impact is large. Therefore, they are declared as external const variables.
 *                  It is intentional and there is no problem.
 *   Verification : Incorrect accessing would result in compilation fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 8.13 / QAC message 3673
 *   Message      : The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of
 *                  type 'pointer to const'.
 *   Reason       : This is APIs to be opened to the user, and usability is reduced when specifying to the const
 *                  attribute, so do not add the const attribute.
 *   Verification : This information is a kind of advice and there is no problem in operation even if it does not
 *                  correspond.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 11.3 / QAC message 0310
 *   Message      : Casting to different object pointer type.
 *   Reason       : It is necessary to operate 4-byte data allocated at the 4-byte alignment address and 4-byte data
 *                  allocated at the not 4-byte aligned equally. In the latter case, it must copies to 4-byte
 *                  alignment address and processes, so casting to a different pointer type is required.
 *   Verification : The casts are essential for complete code execution.
 *                  Incorrect cast would result in compilation fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 11.3 / QAC message 3305
 *   Message      : Pointer cast to stricter alignment.
 *   Reason       : It is necessary to operate 4-byte data allocated at the 4-byte alignment address and 4-byte data
 *                  allocated at the not 4-byte aligned equally. In the latter case, it must copy to 4-byte
 *                  alignment address and processes, so casting to a different pointer type is required.
 *   Verification : The casts are essential for complete code execution.
 *                  Incorrect cast would result in compilation fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 11.4 / QAC message 0303
 *   Message      : Cast between a pointer to volatile object and an integral type.
 *   Reason       : In order to judge whether the address value of the pointer is odd or not, it is dared to cast to
 *                  an integer value. Since it is used only in this judgment part, so the intention is clear, there is
 *                  no influence on the operation.
 *   Verification : The converted addresses are essential for complete code execution.
 *                  Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 11.4 / QAC message 0306
 *   Message      : Cast between a pointer to object and an integral type.
 *   Reason       : In order to judge whether the address value of the pointer is odd or not, it is dared to cast to
 *                  an integer value. Since it is used only in this judgment part, so the intention is clear, there is
 *                  no influence on the operation.
 *   Verification : The converted addresses are essential for complete code execution.
 *                  Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 17.8 / QAC message 1338
 *   Message      : The parameter '%s' is being modified.
 *   Reason       : The corresponding point is where the pointer is specified as a parameter. 
 *                  Although data is acquired while incrementing the address pointed to by the pointer,
 *                  there is no problem in this implementation because it is not necessary to refer to the
 *                  pointer value at the time of starting this function.
 *   Verification : Incorrect processing would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 20.1 / QAC message 5087
 *   Message      : #include directives should only be preceded by preprocessor directives or comments.
 *   Reason       : This writing format is in accordance with the AUTOSAR Specification.
 *   Verification : Incorrect processing would result in test fails.
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
 *   Rule         : CERT-C rule ARR02 / QAC message 3674
 *   Message      : An array has been defined without an explicit size. Its size is defined implicitly by the
 *                : number of initializers.
 *   Reason       : This is a structure in which members are increased or decreased depending on the type of device,
 *                  and it is necessary to maintain high reusability for re-using. Therefore, we chose a method that
 *                  did not describe the size of the structure.
 *   Verification : Incorrect size number specifying would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule ARR02-EX1
 *   Message      : Exception of ARR02.
 *   Reason       : STR11-C is a specific exception to this recommendation; it requires that the bound of a character
 *                  array initialized with a string literal is unspecified.
 *   Verification : No violation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule DCL00 / QAC message 3204
 *   Message      : The variable '%s' is only set once and so it could be declared with the 'const' qualifier.
 *   Reason       : The relevant part can be declared with const, but since it is easier to read
 *                  if it is implemented with code equivalent to the similar part, we will leave it as it is.
 *   Verification : No violation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule DCL00 / QAC message 3227
 *   Message      : The parameter '%s' is never modified and so it could be declared with the 'const' qualifier.
 *   Reason       : This function is an API and is a user I/F. In other words, since the user set parameters,
 *                  it cannot be limited to the const type.
 *   Verification : No violation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule INT02 / QAC message 2100, 2101
 *   Message      : Understand integer conversion rules.
 *   Reason       : Since it can be confirmed that the corresponding operation result does not exceed the specified
 *                  type range, the correct operation result can be acquired without conversion to integer type.
 *                  So, there is no problem.
 *   Verification : Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : No MISRA-C 2012 or CERT-C rule / QAC message 0751
 *   Message      : Casting to char pointer type.
 *   Reason       : Since each byte needs to be processed, it needs to be cast as a pointer of char type.
 *                  So, there is no problem.
 *   Verification : Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : No MISRA-C 2012 or CERT-C rule / QAC(RCMA) message 1502
 *   Message      : The object 'name' is defined but is not used within this project.
 *   Reason       : Version information is stored, RFD version information is prepared to be acquired from symbols.
 *                  There is no reference from the project, but there is no problem in use.
 *   Verification : No violation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : No MISRA-C 2012 or CERT-C rule / QAC(RCMA) message 1505
 *   Message      : The function 'name' is only referenced in the translation unit where it is defined.
 *   Reason       : The corresponding API is defined as an internal function, but in order to carry out the test
 *                  efficiently, it is defined as an external function. It is a function that is not disclosed to
 *                  the user in terms of specifications, and there is no particular problem.
 *   Verification : No violation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : No MISRA-C 2012 or CERT-C rule / QAC message 3203
 *   Message      : The variable '%s' is set but never used.
 *   Reason       : Depending on the specifications of the device, there is a place where the register value is dummy
 *                  and needs to be read once, and it is used as a variable to store the read value.
 *                  So, there is no problem.
 *   Verification : No violation.
 *********************************************************************************************************************/

#include "r_rfd_config.h"
#include "r_rfd.h"
#include "r_rfd_common.h"           /* !CERT-C rule 5002 */
#include "r_rfd_common_local.h"     /* !CERT-C rule 5002 */
#include "r_rfd_cf.h"
#include "r_rfd_cf_local.h"         /* !CERT-C rule 5002 */
#include "r_rfd_cf_version.h"       /* !CERT-C rule 5002 */

/**************************************************************************************************************
 *  Possibility of operating the code flash memory by RFD28F
 *    - If the definition of "R_RFD_CONTROL_TARGET_CODEFLASH" is "R_RFD_DISABLE",
 *      the compiler output warning and no object is created by #warning directive.
 *************************************************************************************************************/

#if (R_RFD_CONTROL_TARGET_CODEFLASH == R_RFD_DISABLE)
    #warning "Code Flash Control Component is invalidated in r_rfd_config.h"
#else   /* R_RFD_CONTROL_TARGET_CODEFLASH == R_RFD_ENABLE */

/*******************************************************************************************************
 *  Due to keep address information of VOFC of the Extra Area
 *   (Configuration Setting Area, Security Setting Area, Block Protection Area0, Block Protection Area1)
 *  Section declaration
 *    - Definition of the const section
 *
 *  - Traceability          : [Covers:UD_60_005] [Covers:UD_60_006]
 ******************************************************************************************************/

/* Start of the definition of the const section */
#define  R_RFD_EXTRA_START_SEC_CONST_UNSPECIFIED
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */

/* Items to check for CSAVOFCn of Configuration Setting Area                           */
/* This is dependent on the device. (This setting is for RH850/U2A series)             */
/* If using a device different from RH850/U2A series, these definition must be changed */
/* !MISRA-C 2012 rule 8.9 (QAC message 3218)  */
/* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
/* !CERT-C rule ARR02 (QAC message 3674)      */

static const T_u4   bu4_toCheckCSAVOFCitem[] = {
    (T_u4)&R_RFD_FLAG_CSAVOFC0,   /* CSAVOFC0  */
    (T_u4)&R_RFD_FLAG_CSAVOFC8,   /* CSAVOFC8  */
    (T_u4)&R_RFD_FLAG_CSAVOFC9,   /* CSAVOFC9  */
    (T_u4)&R_RFD_FLAG_CSAVOFC10,  /* CSAVOFC10 */
    (T_u4)&R_RFD_FLAG_CSAVOFC11,  /* CSAVOFC11 */
    (T_u4)&R_RFD_FLAG_CSAVOFC12,  /* CSAVOFC12 */
    (T_u4)&R_RFD_FLAG_CSAVOFC13,  /* CSAVOFC13 */
    (T_u4)&R_RFD_FLAG_CSAVOFC14,  /* CSAVOFC14 */
    (T_u4)&R_RFD_FLAG_CSAVOFC15,  /* CSAVOFC15 */
    (T_u4)&R_RFD_FLAG_CSAVOFC16,  /* CSAVOFC16 */
    (T_u4)&R_RFD_FLAG_CSAVOFC17,  /* CSAVOFC17 */
    (T_u4)&R_RFD_FLAG_CSAVOFC18,  /* CSAVOFC18 */
    (T_u4)&R_RFD_FLAG_CSAVOFC19   /* CSAVOFC19 */
};

/* Items to check for SSAVOFCn of Security Setting Area                                */
/* This is dependent on the device. (This setting is for RH850/U2A series)             */
/* If using a device different from RH850/U2A series, these definition must be changed */
/* !MISRA-C 2012 rule 8.9 (QAC message 3218)  */
/* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
/* !CERT-C rule ARR02 (QAC message 3674)      */

static const T_u4   bu4_toCheckSSAVOFCitem[] = {
    (T_u4)&R_RFD_FLAG_SSAVOFC0,   /* SSAVOFC0  */
    (T_u4)&R_RFD_FLAG_SSAVOFC1,   /* SSAVOFC1  */
    (T_u4)&R_RFD_FLAG_SSAVOFC7,   /* SSAVOFC7  */
    (T_u4)&R_RFD_FLAG_SSAVOFC8,   /* SSAVOFC8  */
    (T_u4)&R_RFD_FLAG_SSAVOFC9,   /* SSAVOFC9  */
    (T_u4)&R_RFD_FLAG_SSAVOFC10,  /* SSAVOFC10 */
    (T_u4)&R_RFD_FLAG_SSAVOFC11,  /* SSAVOFC11 */
    (T_u4)&R_RFD_FLAG_SSAVOFC12,  /* SSAVOFC12 */
    (T_u4)&R_RFD_FLAG_SSAVOFC13,  /* SSAVOFC13 */
    (T_u4)&R_RFD_FLAG_SSAVOFC14,  /* SSAVOFC14 */
    (T_u4)&R_RFD_FLAG_SSAVOFC15,  /* SSAVOFC15 */
    (T_u4)&R_RFD_FLAG_SSAVOFC16,  /* SSAVOFC16 */
    (T_u4)&R_RFD_FLAG_SSAVOFC17,  /* SSAVOFC17 */
    (T_u4)&R_RFD_FLAG_SSAVOFC18,  /* SSAVOFC18 */
    (T_u4)&R_RFD_FLAG_SSAVOFC40   /* SSAVOFC40 */
};

/* Items to check for BPA0VOFCn of Block Protection Area0                              */
/* This is dependent on the device. (This setting is for RH850/U2A series)             */
/* If using a device different from RH850/U2A series, these definition must be changed */
/* !MISRA-C 2012 rule 8.9 (QAC message 3218)  */
/* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
/* !CERT-C rule ARR02 (QAC message 3674)      */

static const T_u4   bu4_toCheckBPA0VOFCitem[] = {
    (T_u4)&R_RFD_FLAG_BPA0VOFC0,  /* BPA0VOFC0  */
    (T_u4)&R_RFD_FLAG_BPA0VOFC1,  /* BPA0VOFC1  */
    (T_u4)&R_RFD_FLAG_BPA0VOFC2,  /* BPA0VOFC2  */
    (T_u4)&R_RFD_FLAG_BPA0VOFC3,  /* BPA0VOFC3  */
    (T_u4)&R_RFD_FLAG_BPA0VOFC4,  /* BPA0VOFC4  */
    (T_u4)&R_RFD_FLAG_BPA0VOFC5,  /* BPA0VOFC5  */
    (T_u4)&R_RFD_FLAG_BPA0VOFC6,  /* BPA0VOFC6  */
    (T_u4)&R_RFD_FLAG_BPA0VOFC7,  /* BPA0VOFC7  */
    (T_u4)&R_RFD_FLAG_BPA0VOFC15, /* BPA0VOFC15 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC16, /* BPA0VOFC16 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC17, /* BPA0VOFC17 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC18, /* BPA0VOFC18 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC19, /* BPA0VOFC19 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC20, /* BPA0VOFC20 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC21, /* BPA0VOFC21 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC22, /* BPA0VOFC22 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC23, /* BPA0VOFC23 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC24, /* BPA0VOFC24 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC25, /* BPA0VOFC25 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC26, /* BPA0VOFC26 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC27, /* BPA0VOFC27 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC28, /* BPA0VOFC28 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC29, /* BPA0VOFC29 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC30, /* BPA0VOFC30 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC31, /* BPA0VOFC31 */
    (T_u4)&R_RFD_FLAG_BPA0VOFC39  /* BPA0VOFC39 */
};

/* Items to check for BPA1VOFCn of Block Protection Area1                              */
/* This is dependent on the device. (This setting is for RH850/U2A series)             */
/* If using a device different from RH850/U2A series, these definition must be changed */
/* !MISRA-C 2012 rule 8.9 (QAC message 3218)  */
/* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
/* !CERT-C rule ARR02 (QAC message 3674)      */

static const T_u4   bu4_toCheckBPA1VOFCitem[] = {
    (T_u4)&R_RFD_FLAG_BPA1VOFC0,  /* BPA1VOFC0  */
    (T_u4)&R_RFD_FLAG_BPA1VOFC1,  /* BPA1VOFC1  */
    (T_u4)&R_RFD_FLAG_BPA1VOFC2,  /* BPA1VOFC2  */
    (T_u4)&R_RFD_FLAG_BPA1VOFC3,  /* BPA1VOFC3  */
    (T_u4)&R_RFD_FLAG_BPA1VOFC4,  /* BPA1VOFC4  */
    (T_u4)&R_RFD_FLAG_BPA1VOFC5,  /* BPA1VOFC5  */
    (T_u4)&R_RFD_FLAG_BPA1VOFC6,  /* BPA1VOFC6  */
    (T_u4)&R_RFD_FLAG_BPA1VOFC7,  /* BPA1VOFC7  */
    (T_u4)&R_RFD_FLAG_BPA1VOFC16, /* BPA1VOFC16 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC17, /* BPA1VOFC17 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC18, /* BPA1VOFC18 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC19, /* BPA1VOFC19 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC20, /* BPA1VOFC20 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC21, /* BPA1VOFC21 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC22, /* BPA1VOFC22 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC23, /* BPA1VOFC23 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC24, /* BPA1VOFC24 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC25, /* BPA1VOFC25 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC26, /* BPA1VOFC26 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC27, /* BPA1VOFC27 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC28, /* BPA1VOFC28 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC29, /* BPA1VOFC29 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC30, /* BPA1VOFC30 */
    (T_u4)&R_RFD_FLAG_BPA1VOFC31, /* BPA1VOFC31 */
};

/* End of the definition of the const section */
#define  R_RFD_EXTRA_STOP_SEC_CONST_UNSPECIFIED
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

/**************************************************************************************************************
 *  Version Information
 *    - Version of the Code Flash Control Component
 *  Declared the section
 *    - Definition of the const section
 *
 *  - Traceability          : [Covers:UD_60_003] [Covers:UD_60_004]
 *********************************************************************************************/

/* Start of the definition of the const section */
#define  R_RFD_VERSION_CF_START_SEC_CONST_UNSPECIFIED
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */
/* Alignment4 for the variables */
R_RFD_ALIGN_VARIABLE_4

/* Version of the Code Flash Control Component */
const   T_u1 pu1_versionCFComponent[] = R_RFD_VERSION_CF_COMPONENT;
                                /* !MISRA-C 2012 rule 8.4 (QAC message 3408)                      */
                                /* QAC(RCMA) message 1502                                         */
                                /* !CERT-C rule ARR02 (QAC message 3674) -> CERT-C rule ARR02-EX1 */

/* End of the definition of the const section) */
#define  R_RFD_VERSION_CF_STOP_SEC_CONST_UNSPECIFIED
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

/**************************************************************************************************************
 *  Section declaration
 *    - Start of the definition of the text section for the Code Flash Control Component
 *
 *  - Traceability          : [Covers:UD_60_000]
 *************************************************************************************************************/

/* Start of the definition of the text section */
#define  R_RFD_CF_START_SEC_CODE
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

/**********************************************************************************************************************
**  Function Name   : R_RFD_IDAuth
**  
**  - Outline
**      Authenticates the ID
**  - Format
**      T_u4_RFDReturn
**          R_RFD_IDAuth(
**              T_en_IDType i_en_IDType,
**              T_u1*       i_pu1_AuthIDData
**          );
**  - Input parameter
**      i_en_IDType       : Type of ID to be authenticated
**      i_p_AuthIDData    : Pointer to the ID data to be authenticated
**  - Return
**      R_RFD_OK          : Authentication succeed
**      R_RFD_ERR_IDAUTH  : Authentication fails
**  - Preconditions
**      No preconditions
**  
**  - Traceability        : [Covers:UD_03_100]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_IDAuth(T_en_IDType i_en_IDType, T_u1* i_pu1_AuthIDData)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function               */
    T_bl            l_bl1_errorFlag;        /* Error flag                                   */
    T_u4            l_bu4_loopCount;        /* loop count for "for statement"               */
    
    T_u4*           l_pu4_authIDData;       /* Authentication Data                          */
    volatile T_u4*  l_pu4_IDIN;             /* Local variables for IDIN                     */
    T_u4            l_bu4_IDStatus;         /* Value of ID authentication status register   */
    T_u4            l_bu4_IDST_BIT;         /* Value for bit in IDST                        */
    volatile T_u4*  l_pu4_IDST;             /* For Switching IDST or IDST2                  */
    volatile T_u4*  l_pu4_IDIN7;            /* For dummy read                               */
    volatile T_u4   l_bu4_dummyRead;        /* For dummy read                               */
                                            /* QAC message 3203                              */
    T_u4            l_bu4_work[R_RFD_LENGTH_ID/R_RFD_LENGTH_UNIT_ID];   /* Working area     */
    
    /* Initialization of the local variables */
    l_bu4_returnValue = R_RFD_OK;
    l_bl1_errorFlag   = R_RFD_FALSE;
    l_bu4_loopCount   = 0U;
    
    l_pu4_authIDData  = (T_u4 *)0U;
    l_pu4_IDIN        = (T_u4 *)R_RFD_REG_SPIDIN_TOP_ADDRESS; /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
    l_bu4_IDStatus    = 0U;
    l_bu4_IDST_BIT    = 0U;
    l_pu4_IDST        = (T_u4 *)0U;
    l_pu4_IDIN7       = (T_u4 *)0U;
    l_bu4_dummyRead   = 0U;
    
    
    /* If Authentication ID is "R_RFD_ID_SPID" */
    if (i_en_IDType == R_RFD_ID_SPID)
    {
        l_pu4_IDIN      = (T_u4 *)R_RFD_REG_SPIDIN_TOP_ADDRESS;   /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_pu4_IDIN7     = (T_u4 *)R_RFD_REG_SPIDIN7_ADDRESS;      /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_bu4_IDST_BIT  = R_RFD_IDST_SPIDR;
        l_pu4_IDST      = (T_u4 *)R_RFD_REG_IDST_ADDRESS;         /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
    }
    /* If Authentication ID is "R_RFD_ID_DFID" */
    else if (i_en_IDType == R_RFD_ID_DFID)
    {
        l_pu4_IDIN      = (T_u4 *)R_RFD_REG_DFIDIN_TOP_ADDRESS;   /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_pu4_IDIN7     = (T_u4 *)R_RFD_REG_DFIDIN7_ADDRESS;      /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_bu4_IDST_BIT  = R_RFD_IDST_DFIDR;
        l_pu4_IDST      = (T_u4 *)R_RFD_REG_IDST_ADDRESS;         /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
    }
    /* If Authentication ID is "R_RFD_ID_OCDID" */
    else if (i_en_IDType == R_RFD_ID_OCDID)
    {
        l_pu4_IDIN      = (T_u4 *)R_RFD_REG_OCDIDIN_TOP_ADDRESS;  /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_pu4_IDIN7     = (T_u4 *)R_RFD_REG_OCDIDIN7_ADDRESS;     /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_bu4_IDST_BIT  = R_RFD_IDST_OCDIDR;
        l_pu4_IDST      = (T_u4 *)R_RFD_REG_IDST_ADDRESS;         /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
    }
    /* If Authentication ID is "R_RFD_ID_CUSTIDA" */
    else if (i_en_IDType == R_RFD_ID_CUSTIDA)
    {
        l_pu4_IDIN      = (T_u4 *)R_RFD_REG_CUSTIDAIN_TOP_ADDRESS;/* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_pu4_IDIN7     = (T_u4 *)R_RFD_REG_CUSTIDAIN7_ADDRESS;   /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_bu4_IDST_BIT  = R_RFD_IDST_CUSTIDAIDR;
        l_pu4_IDST      = (T_u4 *)R_RFD_REG_IDST_ADDRESS;         /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
    }
    /* If Authentication ID is "R_RFD_ID_CUSTIDB" */
    else if (i_en_IDType == R_RFD_ID_CUSTIDB)
    {
        l_pu4_IDIN      = (T_u4 *)R_RFD_REG_CUSTIDBIN_TOP_ADDRESS;/* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_pu4_IDIN7     = (T_u4 *)R_RFD_REG_CUSTIDBIN7_ADDRESS;   /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_bu4_IDST_BIT  = R_RFD_IDST_CUSTIDBIDR;
        l_pu4_IDST      = (T_u4 *)R_RFD_REG_IDST_ADDRESS;         /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
    }
    /* If Authentication ID is "R_RFD_ID_CUSTIDC" */
    else if (i_en_IDType == R_RFD_ID_CUSTIDC)
    {
        l_pu4_IDIN      = (T_u4 *)R_RFD_REG_CUSTIDCIN_TOP_ADDRESS;/* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_pu4_IDIN7     = (T_u4 *)R_RFD_REG_CUSTIDCIN7_ADDRESS;   /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_bu4_IDST_BIT  = R_RFD_IDST_CUSTIDCIDR;
        l_pu4_IDST      = (T_u4 *)R_RFD_REG_IDST_ADDRESS;         /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
    }
    /* If Authentication ID is "R_RFD_ID_RHSIFID" */
    else if (i_en_IDType == R_RFD_ID_RHSIFID)
    {
        l_pu4_IDIN      = (T_u4 *)R_RFD_REG_RHSIFIDIN_TOP_ADDRESS;/* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_pu4_IDIN7     = (T_u4 *)R_RFD_REG_RHSIFIDIN7_ADDRESS;   /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        l_bu4_IDST_BIT  = R_RFD_IDST_RHSIFIDR;
        l_pu4_IDST      = (T_u4 *)R_RFD_REG_IDST2_ADDRESS;        /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
    }
    else
    {
        /* There is no ID type as specified */
        l_bl1_errorFlag = R_RFD_TRUE;
        
        /* Set return value */
        l_bu4_returnValue = R_RFD_ERR_IDAUTH;
    }
    
    
    /* NOT error case */
    if (l_bl1_errorFlag != R_RFD_TRUE)      /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Check the alignment of AuthIDData */
        /* On 4-bytes alignment */
        if (((T_u4)i_pu1_AuthIDData & R_RFD_CHECK_ALIGN4) == 0UL)   /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
        {
            /* Use as it is */
            l_pu4_authIDData = (T_u4 *)i_pu1_AuthIDData;            /* !MISRA-C 2012 rule 11.3 (QAC message 0310) */
                                                                    /* !MISRA-C 2012 rule 11.3 (QAC message 3305) */
        }
        /* Not on 4-bytes alignment */
        else
        {
            /* Copy to the 4-bytes alignment and Use */
            rfd_fv0_Memcpy1ByteUnit((T_u1 *)&l_bu4_work[0], i_pu1_AuthIDData,
                                                                (T_u4)R_RFD_LENGTH_ID/R_RFD_LENGTH_BYTE1);
                                                                    /* !QAC message 0751 */
            l_pu4_authIDData = (T_u4 *)&l_bu4_work[0];
        }
        
        /* Write to IDINx register the AuthIDData */
        for (l_bu4_loopCount = 0U; l_bu4_loopCount < (R_RFD_LENGTH_ID/R_RFD_LENGTH_UNIT_ID); l_bu4_loopCount++)
        {
            *l_pu4_IDIN = *l_pu4_authIDData;
            l_pu4_IDIN++;
            l_pu4_authIDData++;
        }
        
        /* Dummy read the R_RFD_REG_xxxIDIN7 */
        l_bu4_dummyRead = *l_pu4_IDIN7;
        
        /* Acquire the value of IDST(ID Authentication Status Register) */
        l_bu4_IDStatus = *l_pu4_IDST;
        
        /* Check the Data-Flash ID Authentication Status */
        /* The IDs match (protection unlocked) */
        if ((l_bu4_IDStatus & (T_u4)l_bu4_IDST_BIT) == 0UL)
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_OK;
        }
        /* The IDs do not match (protection locked) */
        else
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_ERR_IDAUTH;
        }
    }/* if (l_bl1_errorFlag != R_RFD_TRUE) */
    
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}

/**************************************************************************************************************
 *  Section declaration
 *    - End of the cefinition of the text section for the Code Flash Control Component
 *************************************************************************************************************/

/* End of the definition of the text section */
#define  R_RFD_CF_STOP_SEC_CODE
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

/**************************************************************************************************************
 *  Section declaration
 *    - Start of the definition of the text section for the Code Flash Control Component
 *     (on RAM when No BGO condition)
 *
 *  - Traceability          : [Covers:UD_60_001]
 *************************************************************************************************************/

/* Start of the definition of the text section */
#define  R_RFD_CF_RAM_NO_BGO_START_SEC_CODE
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

/**********************************************************************************************************************
**  Function Name   : R_RFD_EraseCFRequest
**  
**  - Outline
**      Erases the contents of the code flash memory
**  - Format
**      void
**          R_RFD_EraseCFRequest(
**              T_u4_RfdAddress  i_u4_Start
**          );
**  - Input parameter
**      i_u4_Start        : Start address of the erasure area
**  - Return
**      non return value
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the code flash P/E mode
**  
**  - Traceability        : [Covers:UD_03_110]
**********************************************************************************************************************/

void
R_RFD_EraseCFRequest(T_u4_RfdAddress i_u4_Start)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = 0U;
    
    
    /* Acquire FACI number */
    l_bu2_targetFaci = R_RFD_CFAddressToFaciNumber(i_u4_Start);
    
    /* If target FACI is Valid */
    if (l_bu2_targetFaci != R_RFD_INVALID_FACI)     /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(l_bu2_targetFaci);
        
        
        /* Flash Sequencer Process Switch Register */
        /* Suspension-priority mode */
        if (R_RFD_ERASURE_SUSPENDED_MODE == R_RFD_SUSPENSION_PRIORITY_MODE)
        {
            R_RFD_REG_FCPSR = R_RFD_VALUE_FCPSR_SUSPRI_MODE;    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        }
        /* Erasure-priority mode */
        else if (R_RFD_ERASURE_SUSPENDED_MODE == R_RFD_ERASURE_PRIORITY_MODE)
        {
            R_RFD_REG_FCPSR = R_RFD_VALUE_FCPSR_ERSPRI_MODE;    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        }
        /* No having a mode */
        else
        {
            /* no operation */
        }
        
        /* 1 sector erasure */
        rfd_fv0_SingleErase(i_u4_Start);
        
    } /* if (l_bu2_targetFaci != R_RFD_INVALID_FACI) */
    
    /* If target FACI is NOT Valid */
    else
    {
        /* no operation */
    }
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_WriteCFRequest
**  
**  - Outline
**      Writes the data to the code flash memory
**  - Format
**      void
**          R_RFD_WriteCFRequest(
**              T_u4_RfdAddress  i_u4_Start,
**              T_u4_RfdBuffer   i_pu4_Data
**          );
**  - Input parameter
**      i_u4_Start         : Start address of the programming area
**      i_pu4_Data         : Address of the buffer storing the write data
**  - Return
**      non return value
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the code flash P/E mode
**  
**  - Traceability         : [Covers:UD_03_120]
**********************************************************************************************************************/

void
R_RFD_WriteCFRequest(T_u4_RfdAddress i_u4_Start, T_pu4_RfdBuffer i_pu4_Data)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = 0U;
    
    
    /* Acquire FACI number */
    l_bu2_targetFaci = R_RFD_CFAddressToFaciNumber(i_u4_Start);
    
    /* If target FACI is Valid */
    if (l_bu2_targetFaci != R_RFD_INVALID_FACI)     /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(l_bu2_targetFaci);
        
        
        /* Writing length is 512 bytes fixed */
        rfd_fv0_SingleWrite(i_u4_Start, R_RFD_LENGTH_DATA_512BYTES, i_pu4_Data);
        
        
    }/* if (l_bu2_targetFaci != R_RFD_INVALID_FACI) */
    
    /* If target FACI is NOT Valid */
    else
    {
        /* no operation */
    }
    
    return;
    
}


/**********************************************************************************************************************
**  Function Name   : R_RFD_CFAddressToFaciNumber
**  
**  - Outline
**      Acquires the FACI number of the specified code flash memory address
**  - Format
**      T_u2_Faci
**          R_RFD_CFAddressToFaciNumber(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the code flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI0         : Target is FACI0
**      R_RFD_FACI1         : Target is FACI1
**      R_RFD_FACI2         : Target is FACI2
**      R_RFD_INVALID_FACI  : Target is invalid FACI
**  - Preconditions
**      No preconditions
**  
**  - Traceability          : [Covers:UD_03_280]
**********************************************************************************************************************/

T_u2_FACI
R_RFD_CFAddressToFaciNumber(T_u4_RfdAddress i_u4_Address)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* FACI0 is Valid */
    if (R_RFD_VALID_FACI0 == R_RFD_TRUE)            /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* FACI0 is Valid / FACI1 is Valid */
        if (R_RFD_VALID_FACI1 == R_RFD_TRUE)        /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* FACI0 is Valid / FACI1 is Valid / FACI2 is Valid */
            if (R_RFD_VALID_FACI2 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
            {
                l_bu2_targetFaci = rfd_fu2_CheckCFFaci0Faci1Faci2(i_u4_Address);
            }
            /* FACI0 is Valid / FACI1 is Valid / FACI2 is Invalid */
            else
            {
                l_bu2_targetFaci = rfd_fu2_CheckCFFaci0Faci1(i_u4_Address);
            }
        } /* if (R_RFD_VALID_FACI1 == R_RFD_TRUE) */
        
        /* FACI0 is Valid / FACI1 is Invalid */
        else
        {
            /* FACI0 is Valid / FACI1 is Invalid / FACI2 is Valid */
            if (R_RFD_VALID_FACI2 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
            {
                l_bu2_targetFaci = rfd_fu2_CheckCFFaci0Faci2(i_u4_Address);
            }
            /* FACI0 is Valid / FACI1 is Invalid / FACI2 is Invalid */
            else
            {
                l_bu2_targetFaci = rfd_fu2_CheckCFFaci0(i_u4_Address);
            }
        } /* else */
        
    } /* if (R_RFD_VALID_FACI0 == R_RFD_TRUE) */
    
    /* FACI0 is Invalid */
    else
    {
        /* FACI0 is Invalid / FACI1 is Valid */
        if (R_RFD_VALID_FACI1 == R_RFD_TRUE)        /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* FACI0 is Invalid / FACI1 is Valid / FACI2 is Valid */
            if (R_RFD_VALID_FACI2 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
            {
                l_bu2_targetFaci = rfd_fu2_CheckCFFaci1Faci2(i_u4_Address);
            }
            /* FACI0 is Invalid / FACI1 is Valid / FACI2 is Invalid */
            else
            {
                l_bu2_targetFaci = rfd_fu2_CheckCFFaci1(i_u4_Address);
            }
        } /* if (R_RFD_VALID_FACI1 == R_RFD_TRUE) */
        
        /* FACI0 is Invalid / FACI1 is Invalid */
        else
        {
            /* FACI0 is Invalid / FACI1 is Invalid / FACI2 is Valid */
            if (R_RFD_VALID_FACI2 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
            {
                l_bu2_targetFaci = rfd_fu2_CheckCFFaci2(i_u4_Address);
            }
            /* FACI0 is Invalid / FACI1 is Invalid / FACI2 is Invalid */
            else
            {
                l_bu2_targetFaci = R_RFD_INVALID_FACI;
            }
        }
    } /* else */
    
    return (l_bu2_targetFaci);
    
}


/**********************************************************************************************************************
**  Function Name   : rfd_fu2_CheckCFFaci0Faci1Faci2
**  
**  - Outline
**      Checks whether the specified address of the code flash memory is for FACI0, FACI1, or FACI2
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckCFFaci0Faci1Faci2(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the code flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI0         : Target is FACI0
**      R_RFD_FACI1         : Target is FACI1
**      R_RFD_FACI2         : Target is FACI2
**      R_RFD_INVALID_FACI  : Target is not FACI0 or FACI1 or FACI2
**  - Preconditions
**      The definitions of FACI0, FACI1, and FACI2 are valid (R_RFD_VALID_FACI0, R_RFD_VALID_FACI1, and
**      R_RFD_VALID_FACI2 are R_RFD_TRUE).
**  
**  - Traceability          : [Covers:UD_03_290]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckCFFaci0Faci1Faci2(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* Check whether the i_u4_Address is included in FACI0 */
    l_bu2_targetFaci = rfd_fu2_CheckCFFaci0(i_u4_Address);
    
    if (l_bu2_targetFaci != R_RFD_FACI0)        /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* Check whether the i_u4_Address is included in FACI1 */
        l_bu2_targetFaci = rfd_fu2_CheckCFFaci1(i_u4_Address);
        
        if (l_bu2_targetFaci != R_RFD_FACI1)    /* !CERT-C rule INT02 (QAC message 2101) */
        {
            /* Check whether the i_u4_Address is included in FACI2 */
            l_bu2_targetFaci = rfd_fu2_CheckCFFaci2(i_u4_Address);
        }
        else
        {
            /* no operation */
        }
    } /* if (l_bu2_targetFaci != R_RFD_FACI0) */
    
    else
    {
        /* no operation */
    }
    
    return (l_bu2_targetFaci);
    
}


/**********************************************************************************************************************
**  Function Name   : rfd_fu2_CheckCFFaci0Faci1
**  
**  - Outline
**      Checks whether the specified address of the code flash memory is for FACI0 or FACI1
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckCFFaci0Faci1(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the code flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI0         : Target is FACI0
**      R_RFD_FACI1         : Target is FACI1
**      R_RFD_INVALID_FACI  : Target is not FACI0 or FACI1
**  - Preconditions
**      - The definitions of FACI0 and FACI1 are valid (R_RFD_VALID_FACI0 and R_RFD_VALID_FACI1 are R_RFD_TRUE)
**      - The definition of FACI2 is invalid (R_RFD_VALID_FACI2 is R_RFD_FALSE)
**  
**  - Traceability          : [Covers:UD_03_300]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckCFFaci0Faci1(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* Check whether the i_u4_Address is included in FACI0 */
    l_bu2_targetFaci = rfd_fu2_CheckCFFaci0(i_u4_Address);
    
    if (l_bu2_targetFaci != R_RFD_FACI0)    /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* Check whether the i_u4_Address is included in FACI1 */
        l_bu2_targetFaci = rfd_fu2_CheckCFFaci1(i_u4_Address);
    }
    else
    {
        /* no operation */
    }
    
    return (l_bu2_targetFaci);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu2_CheckCFFaci0Faci2
**  
**  - Outline
**      Checks whether the specified address of the code flash memory is for FACI0 or FACI2
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckCFFaci0Faci2(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the code flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI0         : Target is FACI0
**      R_RFD_FACI2         : Target is FACI2
**      R_RFD_INVALID_FACI  : Target is not FACI0 or FACI2
**  - Preconditions
**      - The definitions of FACI0 and FACI2 are valid (R_RFD_VALID_FACI0 and R_RFD_VALID_FACI2 are R_RFD_TRUE)
**      - The definition of FACI1 is invalid (R_RFD_VALID_FACI1 is R_RFD_FALSE)
**  
**  - Traceability          : [Covers:UD_03_310]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckCFFaci0Faci2(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* Check whether the i_u4_Address is included in FACI0 */
    l_bu2_targetFaci = rfd_fu2_CheckCFFaci0(i_u4_Address);
    
    if (l_bu2_targetFaci != R_RFD_FACI0)    /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* Check whether the i_u4_Address is included in FACI2 */
        l_bu2_targetFaci = rfd_fu2_CheckCFFaci2(i_u4_Address);
    }
    else
    {
        /* no operation */
    }
    
    return (l_bu2_targetFaci);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu2_CheckCFFaci1Faci2
**  
**  - Outline
**      Checks whether the specified address of the code flash memory is for FACI1 or FACI2
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckCFFaci1Faci2(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the code flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI1         : Target is FACI1
**      R_RFD_FACI2         : Target is FACI2
**      R_RFD_INVALID_FACI  : Target is not FACI1 or FACI2
**  - Preconditions
**      - The definitions of FACI1 and FACI2 are valid (R_RFD_VALID_FACI1 and R_RFD_VALID_FACI2 are R_RFD_TRUE)
**      - The definition of FACI0 is invalid (R_RFD_VALID_FACI0 is R_RFD_FALSE)
**  
**  - Traceability          : [Covers:UD_03_320]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckCFFaci1Faci2(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* Check whether the i_u4_Address is included in FACI1 */
    l_bu2_targetFaci = rfd_fu2_CheckCFFaci1(i_u4_Address);
    
    if (l_bu2_targetFaci != R_RFD_FACI1)    /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* Check whether the i_u4_Address is included in FACI2 */
        l_bu2_targetFaci = rfd_fu2_CheckCFFaci2(i_u4_Address);
    }
    else
    {
        /* no operation */
    }
    
    return (l_bu2_targetFaci);
    
}


/**********************************************************************************************************************
**  Function Name   : rfd_fu2_CheckCFFaci0
**  
**  - Outline
**      Checks whether the specified address of the code flash memory is for FACI0
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckCFFaci0(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the code flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI0         : Target is FACI0
**      R_RFD_INVALID_FACI  : Target is not FACI0
**  - Preconditions
**      The definition of FACI0 is valid (R_RFD_VALID_FACI0 is R_RFD_TRUE)
**  
**  - Traceability          : [Covers:UD_03_330]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckCFFaci0(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* If FACI0 is defined */
    if (R_RFD_CF_BASE_FACI0 != R_RFD_NO_DEFINITION)
    {
        /* Determine end address to check */
        if (R_RFD_VALID_FACI1 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* If FACI1 is defined */
            if (R_RFD_CF_BASE_FACI1 != R_RFD_NO_DEFINITION)
            {
                /* Check whether the address is within FACI0 */
                if ((i_u4_Address >= R_RFD_CF_BASE_FACI0)
                     &&(i_u4_Address < R_RFD_CF_BASE_FACI1))
                {
                    /* The address is within FACI0 */
                    l_bu2_targetFaci = R_RFD_FACI0;
                }
                else
                {
                    /* The address is not within FACI0 */
                    l_bu2_targetFaci = R_RFD_INVALID_FACI;
                }
            } /* if (R_RFD_CF_BASE_FACI1 != R_RFD_NO_DEFINITION) */
            
            /* If FACI1 is not defined (R_RFD_CF_BASE_FACI1 == R_RFD_NO_DEFINITION) */
            else
            {
                
                /* If FACI2 is valid */
                if (R_RFD_VALID_FACI2 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
                {
                    /* If FACI2 is defined */
                    if (R_RFD_CF_BASE_FACI2 != R_RFD_NO_DEFINITION)
                    {
                        /* Check whether the address is within FACI0 */
                        if ((i_u4_Address >= R_RFD_CF_BASE_FACI0)
                             &&(i_u4_Address < R_RFD_CF_BASE_FACI2))
                        {
                            /* The address is within FACI0 */
                            l_bu2_targetFaci = R_RFD_FACI0;
                        }
                        else
                        {
                            /* The address is not within FACI0 */
                            l_bu2_targetFaci = R_RFD_INVALID_FACI;
                        }
                    } /* if (R_RFD_CF_BASE_FACI2 != R_RFD_NO_DEFINITION) */
                    
                    /* If FACI2 is not defined */
                    else
                    {
                        /* Check whether the address is within FACI0 */
                        if ((i_u4_Address >= R_RFD_CF_BASE_FACI0)
                             &&(i_u4_Address <= R_RFD_CF_END))
                        {
                            /* The address is within FACI0 */
                            l_bu2_targetFaci = R_RFD_FACI0;
                        }
                        else
                        {
                            /* The address is not within FACI0 */
                            l_bu2_targetFaci = R_RFD_INVALID_FACI;
                        }
                    } /* else */
                    
                } /* if (R_RFD_VALID_FACI2 == R_RFD_TRUE) */
                
                /* If FACI2 is not valid */
                else
                {
                    
                    /* Check whether the address is within FACI0 */
                    if ((i_u4_Address >= R_RFD_CF_BASE_FACI0)
                         &&(i_u4_Address <= R_RFD_CF_END))
                    {
                        /* The address is within FACI0 */
                        l_bu2_targetFaci = R_RFD_FACI0;
                    }
                    else
                    {
                        /* The address is not within FACI0 */
                        l_bu2_targetFaci = R_RFD_INVALID_FACI;
                    }
                }
            } /* else */
            
        } /* if (R_RFD_VALID_FACI1 == R_RFD_TRUE) */
        
        else if (R_RFD_VALID_FACI2 == R_RFD_TRUE)   /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* If FACI2 is defined */
            if (R_RFD_CF_BASE_FACI2 != R_RFD_NO_DEFINITION)
            {
                /* Check whether the address is within FACI0 */
                if ((i_u4_Address >= R_RFD_CF_BASE_FACI0)
                     &&(i_u4_Address < R_RFD_CF_BASE_FACI2))
                {
                    /* The address is within FACI0 */
                    l_bu2_targetFaci = R_RFD_FACI0;
                }
                else
                {
                    /* The address is not within FACI0 */
                    l_bu2_targetFaci = R_RFD_INVALID_FACI;
                }
            }
            else
            {
                /* Check whether the address is within FACI0 */
                if ((i_u4_Address >= R_RFD_CF_BASE_FACI0)
                     &&(i_u4_Address <= R_RFD_CF_END))
                {
                    /* The address is within FACI0 */
                    l_bu2_targetFaci = R_RFD_FACI0;
                }
                else
                {
                    /* The address is not within FACI0 */
                    l_bu2_targetFaci = R_RFD_INVALID_FACI;
                }
            }
        } /* else if (R_RFD_VALID_FACI2 == R_RFD_TRUE) */
        
        else
        {
            /* Check whether the address is within FACI0 */
            if ((i_u4_Address >= R_RFD_CF_BASE_FACI0)
                 &&(i_u4_Address <= R_RFD_CF_END))
            {
                /* The address is within FACI0 */
                l_bu2_targetFaci = R_RFD_FACI0;
            }
            else
            {
                /* The address is not within FACI0 */
                l_bu2_targetFaci = R_RFD_INVALID_FACI;
            }
        } /* else */
        
    } /* if (R_RFD_CF_BASE_FACI0 != R_RFD_NO_DEFINITION) */
    
    /* If FACI0 is not defined (R_RFD_CF_BASE_FACI0 == R_RFD_NO_DEFINITION) */
    else
    {
        /* FACI0 is not available */
        l_bu2_targetFaci = R_RFD_INVALID_FACI;
    }
    
    return (l_bu2_targetFaci);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu2_CheckCFFaci1
**  
**  - Outline
**      Checks whether the specified address of the code flash memory is for FACI1
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckCFFaci1(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the code flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI1         : Target is FACI1
**      R_RFD_INVALID_FACI  : Target is not FACI1
**  - Preconditions
**      The definition of FACI1 is valid (R_RFD_VALID_FACI1 is R_RFD_TRUE)
**  
**  - Traceability          : [Covers:UD_03_340]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckCFFaci1(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* If FACI1 is defined */
    if (R_RFD_CF_BASE_FACI1 != R_RFD_NO_DEFINITION)
    {
        /* Determine end address to check */
        if (R_RFD_VALID_FACI2 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* If FACI2 is defined */
            if (R_RFD_CF_BASE_FACI2 != R_RFD_NO_DEFINITION)
            {
                /* Check whether the address is within FACI1 */
                if ((i_u4_Address >= R_RFD_CF_BASE_FACI1)
                     &&(i_u4_Address < R_RFD_CF_BASE_FACI2))
                {
                    /* The address is within FACI1 */
                    l_bu2_targetFaci = R_RFD_FACI1;
                }
                else
                {
                    /* The address is not within FACI1 */
                    l_bu2_targetFaci = R_RFD_INVALID_FACI;
                }
            } /* if (R_RFD_CF_BASE_FACI2 != R_RFD_NO_DEFINITION) */
            
            else
            {
                /* Check whether the address is within FACI1 */
                if ((i_u4_Address >= R_RFD_CF_BASE_FACI1)
                     &&(i_u4_Address <= R_RFD_CF_END))
                {
                    /* The address is within FACI1 */
                    l_bu2_targetFaci = R_RFD_FACI1;
                }
                else
                {
                    /* The address is not within FACI1 */
                    l_bu2_targetFaci = R_RFD_INVALID_FACI;
                }
            }
        } /* if (R_RFD_VALID_FACI2 == R_RFD_TRUE) */
        
        else
        {
            /* Check whether the address is within FACI1 */
            if ((i_u4_Address >= R_RFD_CF_BASE_FACI1)
                 &&(i_u4_Address <= R_RFD_CF_END))
            {
                /* The address is within FACI1 */
                l_bu2_targetFaci = R_RFD_FACI1;
            }
            else
            {
                /* The address is not within FACI1 */
                l_bu2_targetFaci = R_RFD_INVALID_FACI;
            }
        } /* else */
        
    } /* if (R_RFD_CF_BASE_FACI1 != R_RFD_NO_DEFINITION) */
    
    /* If FACI1 not defined (R_RFD_CF_BASE_FACI1 == R_RFD_NO_DEFINITION) */
    else
    {
        /* FACI1 is not available */
        l_bu2_targetFaci = R_RFD_INVALID_FACI;
    }
    
    return (l_bu2_targetFaci);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu2_CheckCFFaci2
**  
**  - Outline
**      Checks whether the specified address of the code flash memory is for FACI2
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckCFFaci2(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the code flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI2         : Target is FACI2
**      R_RFD_INVALID_FACI  : Target is not FACI2
**  - Preconditions
**      The definition of FACI2 is valid (R_RFD_VALID_FACI2 is R_RFD_TRUE)
**  
**  - Traceability          : [Covers:UD_03_350]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckCFFaci2(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* If FACI2 is defined */
    if (R_RFD_CF_BASE_FACI2 != R_RFD_NO_DEFINITION)
    {
        /* Check whether the address is within FACI2 */
        if ((i_u4_Address >= R_RFD_CF_BASE_FACI2)
             &&(i_u4_Address <= R_RFD_CF_END))
        {
            /* The address is within FACI2 */
            l_bu2_targetFaci = R_RFD_FACI2;
        }
        else
        {
            /* The address is not within FACI2 */
            l_bu2_targetFaci = R_RFD_INVALID_FACI;
        }
    } /* if (R_RFD_CF_BASE_FACI2 != R_RFD_NO_DEFINITION) */
    
    /* If FACI2 is not defined (R_RFD_CF_BASE_FACI2 == R_RFD_NO_DEFINITION) */
    else
    {
        /* FACI2 is not available */
        l_bu2_targetFaci = R_RFD_INVALID_FACI;
    }
    
    return (l_bu2_targetFaci);
    
}

/**************************************************************************************************************
 *  Section declaration
 *    - End of the definition of the text section for the Code Flash Control Component
 *     (on RAM when No BGO condition)
 *************************************************************************************************************/

/* End of the definition of the text section */
#define  R_RFD_CF_RAM_NO_BGO_STOP_SEC_CODE
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

/**************************************************************************************************************
 *  Section declaration
 *    - Start of the definition of the text section for the Extra Area of the Code Flash Control Component
 *
 *  - Traceability          : [Covers:UD_60_000]
 *************************************************************************************************************/

/* Start of the definition of the text section */
#define  R_RFD_EXTRA_START_SEC_CODE
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

/**********************************************************************************************************************
**  Function Name   : R_RFD_ErasePropertyRequest
**  
**  - Outline
**      Erases one area in the Hardware Property Area (The erasure size is one block (2 Kbytes))
**  - Format
**      void
**          R_RFD_ErasePropertyRequest(
**              T_u4_RfdAddress  i_u4_Start
**          );
**  - Input parameter
**      i_u4_Start        : Start address of one area in the Hardware Property Area to be erased
**  - Return
**      non return value
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the data flash P/E mode
**  
**  - Traceability        : [Covers:UD_03_130]
**********************************************************************************************************************/

void
R_RFD_ErasePropertyRequest(T_u4_RfdAddress i_u4_Start)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_bl        l_bl1_errorFlag;    /* Error flag   */
    T_u2_FACI   l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bl1_errorFlag  = R_RFD_FALSE;
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* Acquire FACI number */
    l_bu2_targetFaci = R_RFD_PropertyAddressToFaciNumber(i_u4_Start);
    
    /* Set FACI */
    if (l_bu2_targetFaci != R_RFD_INVALID_FACI)
    {
        rfd_fv0_SetFaci(l_bu2_targetFaci);
    }
    else
    {
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    
    /* NOT error case */
    if (l_bl1_errorFlag != R_RFD_TRUE)  /* !CERT-C rule INT02 (QAC message 2100) */
    {
        
        /* Set start address */
        R_RFD_REG_FSADDR = i_u4_Start;                          /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Issue the property erasure command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_PROPERTY_ERASE;      /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Issue the run command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_RUN;                 /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
    } /* if (l_bl1_errorFlag != R_RFD_TRUE) */
    
    /* Error case */
    else
    {
        /* no operation */
    }
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_WritePropertyRequest
**  
**  - Outline
**      Writes 32 bytes of data to an area in the Hardware Property Area
**  - Format
**      void
**          R_RFD_WritePropertyRequest(
**              T_u4_RfdAddress  i_u4_Start,
**              T_u4_RfdBuffer   i_pu4_Data
**          );
**  - Input parameter
**      i_u4_Start         : Start address of the programming area
**      i_pu4_Data         : Address of the buffer storing the write data
**  - Return
**      non return value
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the data flash P/E mode
**  
**  - Traceability         : [Covers:UD_03_140]
**********************************************************************************************************************/

void
R_RFD_WritePropertyRequest(T_u4_RfdAddress i_u4_Start, T_pu4_RfdBuffer i_pu4_Data)
{
    /* !CERT-C rule DCL00 (QAC message 3227)      */
    /* !MISRA-C 2012 rule 8.13 (QAC message 3673) */
    
    /* Definition of the local variables */
    T_bl        l_bl1_errorFlag;    /* Error flag                     */
    T_u1        l_bu1_writingCount; /* Number of writes               */ /* !CERT-C rule DCL00 (QAC message 3204) */
    T_u4        l_bu4_loopCount;    /* loop count for "for statement" */
    T_u2_FACI   l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bl1_errorFlag    = R_RFD_FALSE;
    l_bu1_writingCount = (T_u1)(R_RFD_LENGTH_PROPERTY_WRITE >> R_RFD_CONVERT_TO_WRITING_COUNT);
    l_bu4_loopCount    = 0U;
    l_bu2_targetFaci   = R_RFD_INVALID_FACI;
    
    
    /* Acquire FACI number */
    l_bu2_targetFaci = R_RFD_PropertyAddressToFaciNumber(i_u4_Start);
    
    /* Set FACI */
    if (l_bu2_targetFaci != R_RFD_INVALID_FACI)
    {
        rfd_fv0_SetFaci(l_bu2_targetFaci);
    }
    else
    {
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    
    /* NOT error case */
    if (l_bl1_errorFlag != R_RFD_TRUE)      /* !CERT-C rule INT02 (QAC message 2100) */
    {
        
        /* Writing length is 32 bytes fixed */
        /* Set start address */
        R_RFD_REG_FSADDR = i_u4_Start;                          /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Issue the property programming command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_PROPERTY_WRITE;      /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Write the writing count */
        R_RFD_CMD_ISSUING_AREA = l_bu1_writingCount;            /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Write data 4-bytes at one time */
        for (l_bu4_loopCount = 0U; l_bu4_loopCount < (T_u4)l_bu1_writingCount; l_bu4_loopCount++)
        {
            R_RFD_CMD_ISSUING_AREA_4BYTE = *i_pu4_Data;         /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            i_pu4_Data++;                                       /* !MISRA-C 2012 rule 17.8 (QAC message 1338) */
        }
        
        /* Issue the run command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_RUN;                 /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
    } /* if (l_bl1_errorFlag != R_RFD_TRUE) */
    
    /* Error case */
    else
    {
        /* no operation */
    }
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_EraseSwitchRequest
**  
**  - Outline
**      Erases the contents of the Switch Area on the back side (invalid side)
**  - Format
**      void
**          R_RFD_EraseSwitchRequest(void);
**  - Input parameter
**      non input parameter
**  - Return
**      R_RFD_OK               : Normal End
**      R_RFD_ERR_SWITCH_DATA  : VAPC value in the TAG Area is not correct
**                               SEDF bit or DEDF bit in the DFERSTR is valid
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the data flash P/E mode
**      The Tag Update command must be completed normally
**  
**  - Traceability        : [Covers:UD_03_150]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_EraseSwitchRequest(void)
{
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;  /* Return value for this function   */
    T_bl            l_bl1_errorFlag;    /* Error flag                       */
    T_u4            l_bu4_TagVAPC;      /* Value of VAPC in TAG Area        */
    
    /* Initialization of the local variables  */
    l_bu4_returnValue = R_RFD_OK;
    l_bl1_errorFlag   = R_RFD_FALSE;
    l_bu4_TagVAPC     = 0U;
    
    
    /* Beginning of the Critical Section */
    R_RFD_HOOK_EnterCriticalSection();
    
    /* Switch the FACI base address and FACI command issue area */
    /* Switch Area is FACI0                                     */
    rfd_fv0_SetFaci(R_RFD_FACI0);
    
    #ifndef    __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__
        /* Valid the R_RFD_VALUE_DFERSTC_ERRCLR */
        R_RFD_REG_DFERSTC = R_RFD_VALUE_DFERSTC_ERRCLR;     /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    #else
        /* Valid the R_RFD_VALUE_DFSERSTC_SSTCLR */
        R_RFD_REG_DFSERSTC = R_RFD_VALUE_DFSERSTC_SSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Valid the R_RFD_VALUE_DFDERSTC_DSTCLR */
        R_RFD_REG_DFDERSTC = R_RFD_VALUE_DFDERSTC_DSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    #endif  /* __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ */
    
    /* Read value from VAPC in TAG Area */
    l_bu4_TagVAPC = R_RFD_FLAG_TAGVAPC;                 /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Check ECC 2bit Error or 1bit Error is occurred */
    l_bl1_errorFlag = rfd_fbl_CheckDFEccError();
    
    /* ECC 2bit Error or 1bit Error is NOT occurred */
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* VAPC value in the TAG is NOT written completely */
        if (l_bu4_TagVAPC != R_RFD_VALUE_WRITTEN_COMPLETELY)
        {
            /* There is a not completed data */
            l_bl1_errorFlag = R_RFD_TRUE;
            
            /* Set Return value */
            l_bu4_returnValue = R_RFD_ERR_SWITCH_DATA;
        }
        /* VAPC value in the TAG is written completely */
        else
        {
            /* no operation */
        }
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    /* ECC 2bit Error or 1bit Error is occurred */
    else
    {
        /* There is a not completed data */
        l_bl1_errorFlag = R_RFD_TRUE;
        
        /* Set Return value */
        l_bu4_returnValue = R_RFD_ERR_SWITCH_DATA;
    }
    
    /* End of the Critical Section */
    R_RFD_HOOK_ExitCriticalSection();
    
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        
        /* Set start address */
        R_RFD_REG_FSADDR = R_RFD_SWA_BASE_FACI0;                /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Issue the switch erasure command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_SWITCH_ERASE;        /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Issue the run command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_RUN;                 /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    return(l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_WriteSwitchRequest
**  
**  - Outline
**      Writes the data to the Switch Area on the back side (invalid side)
**  - Format
**      void
**          R_RFD_WriteSwitchRequest(
**              T_u4_RfdBuffer   i_pu4_Data
**          );
**  - Input parameter
**      i_pu4_Data : Address of the buffer storing the write data
**  - Return
**      non return value
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the data flash P/E mode
**  
**  - Traceability         : [Covers:UD_03_160]
**********************************************************************************************************************/

void
R_RFD_WriteSwitchRequest(T_pu4_RfdBuffer i_pu4_Data)
{
    /* !MISRA-C 2012 rule 8.13 (QAC message 3673) */
    /* !CERT-C rule DCL00 (QAC message 3227)      */
    
    /* Definition of the local variables */
    T_u1    l_bu1_writingCount;     /* Number of writes               */ /* !CERT-C rule DCL00 (QAC message 3204) */
    T_u4    l_bu4_loopCount;        /* loop count for "for statement" */
    
    /* Initialization of the local variables  */
    l_bu1_writingCount = (T_u1)(R_RFD_LENGTH_SWITCH_AREA_WRITE >> R_RFD_CONVERT_TO_WRITING_COUNT);
    l_bu4_loopCount    = 0U;
    
    
    /* Switch the FACI base address and FACI command issue area */
    /* Switch Area is FACI0                                     */
    rfd_fv0_SetFaci(R_RFD_FACI0);
        
    
    
    /* Set start address */
    R_RFD_REG_FSADDR = R_RFD_CVA_ADDRESS;               /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Issue the switch erasure command */
    R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_SWITCH_WRITE;    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Write the writing count */
    R_RFD_CMD_ISSUING_AREA = l_bu1_writingCount;        /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    
    /* Write to the Switch Area */
    for (l_bu4_loopCount = 0U; l_bu4_loopCount < l_bu1_writingCount; l_bu4_loopCount++)
    {                                                   /* !CERT-C rule INT02 (QAC message 2100)      */
        R_RFD_CMD_ISSUING_AREA_4BYTE = i_pu4_Data[l_bu4_loopCount];
                                                        /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    }
    
    /* Issue the run command */
    R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_RUN;             /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_EraseTagRequest
**  
**  - Outline
**      Erases the contents of the TAG Area
**  - Format
**      T_u4_RFDReturn
**          R_RFD_EraseTagRequest(void);
**  - Input parameter
**      non input parameter
**  - Return
**      R_RFD_OK                        : Normal End
**      R_RFD_ERR_SWITCH_DATA           : Some data in Switch Area are not correct
**      R_RFD_ERR_CONFIGURATION_DATA    : Some data in Configuration Area are not correct
**      R_RFD_ERR_SECURITY_DATA         : Some data in Security Setting Area are not correct
**      R_RFD_ERR_BLOCKPROTECTION0_DATA : Some data in Block Protection Area for FACI0 are not correct
**      R_RFD_ERR_BLOCKPROTECTION1_DATA : Some data in Block Protection Area for FACI1 are not correct
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the data flash P/E mode
**  
**  - Traceability        : [Covers:UD_03_170]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_EraseTagRequest(void)
{
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;  /* Return value for this function               */
    T_bl            l_bl1_errorFlag;    /* Error flag   */
    
    /* Initialization of the local variables  */
    l_bu4_returnValue = R_RFD_OK;
    l_bl1_errorFlag   = R_RFD_FALSE;
    
    
    /* Check the values of switch area and hardware property area */
    l_bu4_returnValue = rfd_fu4_CheckSwitchArea_HardwarePropertyArea();
    
    
    if (l_bu4_returnValue != R_RFD_OK)
    {
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Switch the FACI base address and FACI command issue area */
        /* Switch Area is FACI0                                     */
        rfd_fv0_SetFaci(R_RFD_FACI0);
        
        
        /* Set start address */
        R_RFD_REG_FSADDR = R_RFD_TAG_BASE_FACI0;                /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Issue the switch erasure command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_TAG_ERASE;           /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Issue the run command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_RUN;                 /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    return(l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_UpdateTagRequest
**  
**  - Outline
**      Updates the contents of the TAG Area
**  - Format
**      T_u4_RFDReturn
**          R_RFD_UpdateTagRequest(void);
**  - Input parameter
**      non input parameter
**  - Return
**      R_RFD_OK                        : Normal End
**      R_RFD_ERR_SWITCH_DATA           : Some data in Switch Area are not correct
**      R_RFD_ERR_CONFIGURATION_DATA    : Some data in Configuration Area are not correct
**      R_RFD_ERR_SECURITY_DATA         : Some data in Security Setting Area are not correct
**      R_RFD_ERR_BLOCKPROTECTION0_DATA : Some data in Block Protection Area for FACI0 are not correct
**      R_RFD_ERR_BLOCKPROTECTION1_DATA : Some data in Block Protection Area for FACI1 are not correct
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the data flash P/E mode
**  
**  - Traceability        : [Covers:UD_03_180]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_UpdateTagRequest(void)
{
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;  /* Return value for this function               */
    T_bl            l_bl1_errorFlag;    /* Error flag   */
    
    /* Initialization of the local variables  */
    l_bu4_returnValue = R_RFD_OK;
    l_bl1_errorFlag   = R_RFD_FALSE;
    
    
    /* Check the values of switch area and hardware property area */
    l_bu4_returnValue = rfd_fu4_CheckSwitchArea_HardwarePropertyArea();
    
    
    if (l_bu4_returnValue != R_RFD_OK)
    {
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Switch the FACI base address and FACI command issue area */
        /* Switch Area is FACI0                                     */
        rfd_fv0_SetFaci(R_RFD_FACI0);
        
        
        /* Set start address */
        R_RFD_REG_FSADDR = R_RFD_TAG_VAF_FACI0;                 /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Issue the switch erasure command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_TAG_UPDATE;          /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Issue the run command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_RUN;                 /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    return(l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_EraseExtendedDataRequest
**  
**  - Outline
**      Erases the contents of the extended data area
**  - Format
**      void
**          R_RFD_EraseExtendedDataRequest(void);
**              T_u4_RfdAddress  i_u4_Start
**          );
**  - Input parameter
**      i_u4_Start        : Start address for erasure sector
**  - Return
**      non return value
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the data flash P/E mode
**  
**  - Traceability        : [Covers:UD_03_190]
**********************************************************************************************************************/

void
R_RFD_EraseExtendedDataRequest(T_u4_RfdAddress i_u4_Start)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    
    /* No local variables         */
    
    /* Initialization of the local variables */
    
    /* No local variables             */
    
    
    /* Switch the FACI base address and FACI command issue area */
    /* Switch Area is FACI0                                     */
    rfd_fv0_SetFaci(R_RFD_FACI0);
    
    
    /* Flash Sequencer Process Switch Register */
    /* Suspension-priority mode */
    if (R_RFD_ERASURE_SUSPENDED_MODE == R_RFD_SUSPENSION_PRIORITY_MODE)
    {
        R_RFD_REG_FCPSR = R_RFD_VALUE_FCPSR_SUSPRI_MODE;    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    }
    /* Erasure-priority mode */
	else if (R_RFD_ERASURE_SUSPENDED_MODE == R_RFD_ERASURE_PRIORITY_MODE)
    {
        R_RFD_REG_FCPSR = R_RFD_VALUE_FCPSR_ERSPRI_MODE;    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    }
    /* No having a mode */
    else
    {
        /* no operation */
    }
 
    /* Sector erasure */
    rfd_fv0_SingleErase(i_u4_Start);
    
    return;
    
}


/**********************************************************************************************************************
**  Function Name   : R_RFD_WriteExtendedDataRequest
**  
**  - Outline
**      Writes the data to the extended data area
**  - Format
**      void
**          R_RFD_WriteExtendedDataRequest(
**              T_u4_RfdAddress  i_u4_Start,
**              T_u2             i_u2_Length,
**              T_u4_RfdBuffer   i_pu4_Data
**          );
**  - Input parameter
**      i_u4_Start         : Start address of the programming area
**      i_u2_Length        : Length of the write data
**      i_pu4_Data         : Address of the buffer storing the write data
**  - Return
**      non return value
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the data flash P/E mode
**  
**  - Traceability         : [Covers:UD_03_200]
**********************************************************************************************************************/

void
R_RFD_WriteExtendedDataRequest(T_u4_RfdAddress i_u4_Start, T_u2 i_u2_Length, T_pu4_RfdBuffer i_pu4_Data)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    
    /* No local variables         */
    
    /* Initialization of the local variables */
    
    /* No local variables             */
    
    
    /* Switch the FACI base address and FACI command issue area */
    /* Switch Area is FACI0                                     */
    rfd_fv0_SetFaci(R_RFD_FACI0);
    
    /* Data for writing length (2nd parameter) */
    /* Writing length is 4-bytes */
    if (i_u2_Length == R_RFD_LENGTH_DATA_4BYTES)            /* !CERT-C rule INT02 (QAC message 2101) */
    {
        rfd_fv0_SingleWrite(i_u4_Start, i_u2_Length, i_pu4_Data);
    }
    /* Writing length is 8 bytes */
    else if (i_u2_Length == R_RFD_LENGTH_DATA_8BYTES)       /* !CERT-C rule INT02 (QAC message 2101) */
    {
        rfd_fv0_MultiWrite(i_u4_Start, i_u2_Length, i_pu4_Data);
    }
    /* Writing length is 16 bytes */
    else if (i_u2_Length == R_RFD_LENGTH_DATA_16BYTES)      /* !CERT-C rule INT02 (QAC message 2101) */
    {
        rfd_fv0_MultiWrite(i_u4_Start, i_u2_Length, i_pu4_Data);
    }
    /* Writing length is 32bytes */
    else if (i_u2_Length == R_RFD_LENGTH_DATA_32BYTES)      /* !CERT-C rule INT02 (QAC message 2101) */
    {
        rfd_fv0_MultiWrite(i_u4_Start, i_u2_Length, i_pu4_Data);
    }
    /* Writing length is 64bytes */
    else if (i_u2_Length == R_RFD_LENGTH_DATA_64BYTES)      /* !CERT-C rule INT02 (QAC message 2101) */
    {
        rfd_fv0_MultiWrite(i_u4_Start, i_u2_Length, i_pu4_Data);
    }
    /* Writing length is 128bytes */
    else if (i_u2_Length == R_RFD_LENGTH_DATA_128BYTES)     /* !CERT-C rule INT02 (QAC message 2101) */
    {
        rfd_fv0_MultiWrite(i_u4_Start, i_u2_Length, i_pu4_Data);
    }
    else
    {
        /* no operation */
    }
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_PropertyAddressToFaciNumber
**  
**  - Outline
**      Acquires the FACI number of the specified Hardware Property Area address
**  - Format
**      T_u2_Faci
**          R_RFD_PropertyAddressToFaciNumber(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the Hardware Property Area whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI0         : Target is FACI0
**      R_RFD_FACI1         : Target is FACI1
**      R_RFD_INVALID_FACI  : Target is invalid FACI
**  - Preconditions
**      No preconditions
**  
**  - Traceability          : [Covers:UD_03_420]
**********************************************************************************************************************/

T_u2_FACI
R_RFD_PropertyAddressToFaciNumber(T_u4_RfdAddress i_u4_Address)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* Acquire FACI number */
    /* In the Configuration Setting Area (Invalid side) ? */
    if ((i_u4_Address >= R_RFD_CSA_BASE_FACI0)&&(i_u4_Address <= R_RFD_CSA_END_FACI0))
    {
        /* Determine end address to check */
        if (R_RFD_VALID_FACI0 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
        {
            l_bu2_targetFaci = R_RFD_FACI0;
        }
        else
        {
            l_bu2_targetFaci = R_RFD_INVALID_FACI;
        }
    }
    /* In the Security Setting Area (Invalid side) ? */
    else if ((i_u4_Address >= R_RFD_SSA_BASE_FACI0)&&(i_u4_Address <= R_RFD_SSA_END_FACI0))
    {
        /* Determine end address to check */
        if (R_RFD_VALID_FACI0 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
        {
            l_bu2_targetFaci = R_RFD_FACI0;
        }
        else
        {
            l_bu2_targetFaci = R_RFD_INVALID_FACI;
        }
    }
    /* In the Block Protection Area0 (Invalid side) ? */
    else if ((i_u4_Address >= R_RFD_BPA0_BASE_FACI0)&&(i_u4_Address <= R_RFD_BPA0_END_FACI0))
    {
        /* Determine end address to check */
        if (R_RFD_VALID_FACI0 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
        {
            l_bu2_targetFaci = R_RFD_FACI0;
        }
        else
        {
            l_bu2_targetFaci = R_RFD_INVALID_FACI;
        }
    }
    /* In the Block Protection Area1 (Invalid side) ? */
    else if ((i_u4_Address >= R_RFD_BPA1_BASE_FACI1)&&(i_u4_Address <= R_RFD_BPA1_END_FACI1))
    {
        /* Determine end address to check */
        if (R_RFD_VALID_FACI1 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
        {
            l_bu2_targetFaci = R_RFD_FACI1;
        }
        else
        {
            l_bu2_targetFaci = R_RFD_INVALID_FACI;
        }
    }
    /* In the Other Area ? */
    else
    {
        l_bu2_targetFaci = R_RFD_INVALID_FACI;
    }
    
    return (l_bu2_targetFaci);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu4_CheckSwitchArea_HardwarePropertyArea
**  
**  - Outline
**      Checks whether data is stored correctly in the Configuration Setting Area, Security Setting Area,
**      and Block Protection Areas in the Hardware Property Area
**  - Format
**      T_u4_RFDReturn
**          rfd_fu4_CheckSwitchArea_HardwarePropertyArea(void);
**  - Input parameter
**      non input parameter
**  - Return
**      R_RFD_OK                        : Normal End
**      R_RFD_ERR_SWITCH_DATA           : Some data in Switch Area are not correct
**      R_RFD_ERR_CONFIGURATION_DATA    : Some data in Configuration Area are not correct
**      R_RFD_ERR_SECURITY_DATA         : Some data in Security Setting Area are not correct
**      R_RFD_ERR_BLOCKPROTECTION0_DATA : Some data in Block Protection Area for FACI0 are not correct
**      R_RFD_ERR_BLOCKPROTECTION1_DATA : Some data in Block Protection Area for FACI1 are not correct
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**  
**  - Traceability        : [Covers:UD_03_360]
**********************************************************************************************************************/

T_u4_RFDReturn
rfd_fu4_CheckSwitchArea_HardwarePropertyArea(void)
{
    /* !QAC(RCMA) message 1505 */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;  /* Return value for this function   */
    T_bl            l_bl1_errorFlag;    /* Error flag                       */
    T_u4            l_bu4_SWAAnPC;      /* Value of AnPC in Switch Area     */
    
    /* Initialization of the local variables */
    l_bu4_returnValue = R_RFD_OK;
    l_bl1_errorFlag   = R_RFD_FALSE;
    l_bu4_SWAAnPC     = 0U;
    
    
    /* Beginning of the Critical Section */
    R_RFD_HOOK_EnterCriticalSection();
    
    /* Switch the FACI base address and FACI command issue area */
    /* Switch Area is FACI0                                     */
    rfd_fv0_SetFaci(R_RFD_FACI0);
    
    #ifndef    __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__
        /* Valid the R_RFD_VALUE_DFERSTC_ERRCLR */
        R_RFD_REG_DFERSTC = R_RFD_VALUE_DFERSTC_ERRCLR;     /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    #else
        /* Valid the R_RFD_VALUE_DFSERSTC_SSTCLR */
        R_RFD_REG_DFSERSTC = R_RFD_VALUE_DFSERSTC_SSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Valid the R_RFD_VALUE_DFDERSTC_DSTCLR */
        R_RFD_REG_DFDERSTC = R_RFD_VALUE_DFDERSTC_DSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    #endif  /* __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ */
    
    /* Read value from SWAAnPC in Switch Area */
    l_bu4_SWAAnPC = R_RFD_FLAG_SWAAnPC;                 /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Check ECC 2bit Error or 1bit Error is occurred */
    l_bl1_errorFlag = rfd_fbl_CheckDFEccError();
    
    /* ECC 2bit Error or 1bit Error is NOT occurred */
    if (l_bl1_errorFlag == R_RFD_FALSE)         /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* AnPC value in the Switch Area is NOT written completely */
        if (l_bu4_SWAAnPC != R_RFD_VALUE_WRITTEN_COMPLETELY)
        {
            /* There is a not completed data */
            l_bl1_errorFlag = R_RFD_TRUE;
            
            /* Set Return value */
            l_bu4_returnValue = R_RFD_ERR_SWITCH_DATA;
        }
        /* AnPC value in the Switch Area is written completely */
        else
        {
            /* no operation */
        }
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    /* ECC 2bit Error or 1bit Error is occurred */
    else
    {
        /* There is a not completed data */
        l_bl1_errorFlag = R_RFD_TRUE;
        
        /* Set Return value */
        l_bu4_returnValue = R_RFD_ERR_SWITCH_DATA;
    }
    
    /* End of the Critical Section */
    R_RFD_HOOK_ExitCriticalSection();
    
    /* Check Configuration Setting Area */
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        l_bu4_returnValue = rfd_fu4_CheckConfigSettingArea();
        
        if (l_bu4_returnValue != R_RFD_OK)
        {
            /* Some errors were occurred */
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* no operation */
        }
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    /* Check Security Setting Area */
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        l_bu4_returnValue = rfd_fu4_CheckSecuritySettingArea();
        
        if (l_bu4_returnValue != R_RFD_OK)
        {
            /* Some errors were occurred */
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* no operation */
        }
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    /* Check Block Protection Area0 */
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        l_bu4_returnValue = rfd_fu4_CheckBlkProtectionArea0();
        
        if (l_bu4_returnValue != R_RFD_OK)
        {
            /* Some errors were occurred */
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* no operation */
        }
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    /* Check Block Protection Area1 */
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        l_bu4_returnValue = rfd_fu4_CheckBlkProtectionArea1();
        
        if (l_bu4_returnValue != R_RFD_OK)
        {
            /* Some errors were occurred */
            l_bl1_errorFlag = R_RFD_TRUE;
        }
        else
        {
            /* no operation */
        }
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    return(l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu4_CheckConfigSettingArea
**  
**  - Outline
**      Checks whether data is stored correctly in the Configuration Setting Area in the Hardware Property Area
**  - Format
**      T_u4_RFDReturn
**          rfd_fu4_CheckConfigSettingArea(void);
**  - Input parameter
**      non input parameter
**  - Return
**      R_RFD_OK                        : Normal End
**      R_RFD_ERR_SWITCH_DATA           : Some data in Switch Area are not correct
**      R_RFD_ERR_CONFIGURATION_DATA    : Some data in Configuration Area are not correct
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The value of AnPC (n = 0 or 1) in the Switch Area must indicate that the area is programmed
**  
**  - Traceability        : [Covers:UD_03_370]
**********************************************************************************************************************/

T_u4_RFDReturn
rfd_fu4_CheckConfigSettingArea(void)
{
    /* !QAC(RCMA) message 1505 */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function   */
    T_u4            l_bu4_readValue;        /* The reading value                */
    T_bl            l_bl1_errorFlag;        /* Error flag                       */
    T_bl            l_bl1_skipFlag;         /* Skip flag                        */
    T_u4            l_bu4_loopCount;        /* loop count for "for statement"   */
    T_u4            l_bu4_checkItemNumber;  /* The number of items for checking */
    T_u4            l_bu4_SWACVA;           /* Value of CVA in Switch Area      */
    T_u1            l_bu1_FSWASTAT;         /* Value of FSWASTAT register       */
    
    /* Initialization of the local variables */
    l_bu4_returnValue = R_RFD_OK;
    l_bu4_readValue   = 0U;
    l_bl1_errorFlag   = R_RFD_FALSE;
    l_bl1_skipFlag    = R_RFD_FALSE;
    l_bu4_loopCount   = 0U;
    l_bu4_SWACVA      = 0U;
    l_bu1_FSWASTAT    = 0U;
    
    
    /* Beginning of the Critical Section */
    R_RFD_HOOK_EnterCriticalSection();
    
    /* Set FACI as FACI0 */
    rfd_fv0_SetFaci(R_RFD_FACI0);
    
    #ifndef    __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__
        /* Valid the R_RFD_VALUE_DFERSTC_ERRCLR */
        R_RFD_REG_DFERSTC = R_RFD_VALUE_DFERSTC_ERRCLR;     /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    #else
        /* Valid the R_RFD_VALUE_DFSERSTC_SSTCLR */
        R_RFD_REG_DFSERSTC = R_RFD_VALUE_DFSERSTC_SSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Valid the R_RFD_VALUE_DFDERSTC_DSTCLR */
        R_RFD_REG_DFDERSTC = R_RFD_VALUE_DFDERSTC_DSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    #endif  /* __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ */
    
    /* Read from R_RFD_FLAG_SWACVA */
    l_bu4_SWACVA = R_RFD_FLAG_SWACVA;                   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Check ECC 2bit Error or 1bit Error is occurred */
    l_bl1_errorFlag = rfd_fbl_CheckDFEccError();
    
    /* ECC 2bit Error or 1bit Error is NOT occurred */
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* CVA value in the Switch Area is NOT written completely */
        if ((l_bu4_SWACVA != R_RFD_VALUE_VALID_AREA0)&&(l_bu4_SWACVA != R_RFD_VALUE_VALID_AREA1))
        {
            /* Written value is not correct */
            l_bl1_errorFlag = R_RFD_TRUE;
            
            /* Set Return value */
            l_bu4_returnValue = R_RFD_ERR_SWITCH_DATA;
        }
        /* CVA value in the Switch Area is written completely */
        else
        {
            /* no operation */
        }
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    /* ECC 2bit Error or 1bit Error is occurred */
    else
    {
        /* There is a not completed data */
        l_bl1_errorFlag = R_RFD_TRUE;
        
        /* Set Return value */
        l_bu4_returnValue = R_RFD_ERR_SWITCH_DATA;
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Compare the old setting to new setting for Configuration Setting */
        
        /* Read the value of FSWASTAT register */
        l_bu1_FSWASTAT = rfd_fu1_ReadFSWASTAT(R_RFD_FACI0);
        
        /* SWACVA is R_RFD_VALUE_VALID_AREA1 setting */
        if (l_bu4_SWACVA == R_RFD_VALUE_VALID_AREA1)
        {
            /* CFGVA in FSWASTAT is 1 (Area 1 is valid) */
            if (((T_u1)l_bu1_FSWASTAT & (T_u1)R_RFD_MASK_FSWASTAT_CFGVA) != (T_u1)0U)
            {                                                          /* !CERT-C rule INT02 (QAC message 2100) */
                /* Old setting and new setting is same, so the process after this can be skipped */
                l_bl1_skipFlag = R_RFD_TRUE;
                
                /* Set Return value */
                l_bu4_returnValue = R_RFD_OK;
            }
            else
            {
                /* no operation */
                /* Old setting and new setting is different, so continue to process after this */
            }
        } /* if (l_bu4_SWACVA == R_RFD_VALUE_VALID_AREA1) */
        
        /* SWACVA is R_RFD_VALUE_VALID_AREA0 setting */
        else
        {
            /* CFGVA in FSWASTAT is 0 (Area 0 is valid) */
            if (((T_u1)l_bu1_FSWASTAT & (T_u1)R_RFD_MASK_FSWASTAT_CFGVA) == (T_u1)0U)
            {                                                           /* !CERT-C rule INT02 (QAC message 2100) */
                /* Old setting and new setting is same, so the process after this can be skipped */
                l_bl1_skipFlag = R_RFD_TRUE;
                
                /* Set Return value */
                l_bu4_returnValue = R_RFD_OK;
            }
            else
            {
                /* no operation */
                /* Old setting and new setting is different, so continue to process after this */
            }
        }
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    /* End of the Critical Section */
    R_RFD_HOOK_ExitCriticalSection();
    
    /* If the status is "not error" and "not skip" */
    if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_skipFlag == R_RFD_FALSE))
    {                                                           /* !CERT-C rule INT02 (QAC message 2100) */
        /* Beginning of the Critical Section */
        R_RFD_HOOK_EnterCriticalSection();
        
        /* Set FACI as FACI0 */
        rfd_fv0_SetFaci(R_RFD_FACI0);
        
        #ifndef    __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__
            /* Valid the R_RFD_VALUE_DFERSTC_ERRCLR */
            R_RFD_REG_DFERSTC = R_RFD_VALUE_DFERSTC_ERRCLR;     /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        #else
            /* Valid the R_RFD_VALUE_DFSERSTC_SSTCLR */
            R_RFD_REG_DFSERSTC = R_RFD_VALUE_DFSERSTC_SSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            
            /* Valid the R_RFD_VALUE_DFDERSTC_DSTCLR */
            R_RFD_REG_DFDERSTC = R_RFD_VALUE_DFDERSTC_DSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        #endif  /* __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ */
        
        /* Acquire the loop number */
        l_bu4_checkItemNumber = sizeof(bu4_toCheckCSAVOFCitem)/sizeof(bu4_toCheckCSAVOFCitem[0]);
        
        /* Check the value of items of Configuration setting Area */
        for (l_bu4_loopCount = 0U; l_bu4_loopCount < l_bu4_checkItemNumber; l_bu4_loopCount++)
        {
            /* Read from item for checking */
            l_bu4_readValue = *((volatile T_u4 *)bu4_toCheckCSAVOFCitem[l_bu4_loopCount]);
                                                                /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            /* Check ECC 2bit Error or 1bit Error is occurred */
            l_bl1_errorFlag = rfd_fbl_CheckDFEccError();
            
            /* ECC 2bit Error or 1bit Error is NOT occurred */
            if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
            {
                /* VOFC value in the Configuration Setting Area is NOT written completely */
                if (l_bu4_readValue != R_RFD_VALUE_WRITTEN_COMPLETELY)
                {
                    /* There is a not completed data */
                    l_bl1_errorFlag = R_RFD_TRUE;
                    
                    /* Set Return value */
                    l_bu4_returnValue = R_RFD_ERR_CONFIGURATION_DATA;
                }
                /* VOFC value in the Configuration Setting Area is written completely */
                else
                {
                    /* no operation */
                }
            } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
            
            /* ECC 2bit Error or 1bit Error is occurred */
            else
            {
                /* There is a not completed data */
                l_bl1_errorFlag = R_RFD_TRUE;
                
                /* Set Return value */
                l_bu4_returnValue = R_RFD_ERR_CONFIGURATION_DATA;
            }
            
            /* If an error is occurred, escape from for loop statement */
            if (l_bl1_errorFlag == R_RFD_TRUE)  /* !CERT-C rule INT02 (QAC message 2100) */
            {
                break;
            }
            else
            {
                /* no operation */
            }
        }
        
        /* End of the Critical Section */
        R_RFD_HOOK_ExitCriticalSection();
        
    } /* if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_skipFlag == R_RFD_FALSE)) */
    
    /* If the status is "error" or "skip" */
    else
    {
        /* no operation */
    }
    
    return(l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu4_CheckSecuritySettingArea
**  
**  - Outline
**      Checks whether data is stored correctly in the Security Setting Area in the Hardware Property Area
**  - Format
**      T_u4_RFDReturn
**          rfd_fu4_CheckSecuritySettingArea(void);
**  - Input parameter
**      non input parameter
**  - Return
**      R_RFD_OK                        : Normal End
**      R_RFD_ERR_SWITCH_DATA           : Some data in Switch Area are not correct
**      R_RFD_ERR_SECURITY_DATA         : Some data in Security Setting Area are not correct
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The value of AnPC (n = 0 or 1) in the Switch Area must indicate that the area is programmed
**  
**  - Traceability        : [Covers:UD_03_380]
**********************************************************************************************************************/

T_u4_RFDReturn
rfd_fu4_CheckSecuritySettingArea(void)
{
    /* !QAC(RCMA) message 1505 */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function   */
    T_u4            l_bu4_readValue;        /* The reading value                */
    T_bl            l_bl1_errorFlag;        /* Error flag                       */
    T_bl            l_bl1_skipFlag;         /* Skip flag                        */
    T_u4            l_bu4_loopCount;        /* loop count for "for statement"   */
    T_u4            l_bu4_checkItemNumber;  /* The number of items for checking */
    T_u4            l_bu4_SWASVA;           /* Value of SVA in Switch Area      */
    T_u1            l_bu1_FSWASTAT;         /* Value of FSWASTAT register       */
    
    /* Initialization of the local variables */
    l_bu4_returnValue = R_RFD_OK;
    l_bu4_readValue   = 0U;
    l_bl1_errorFlag   = R_RFD_FALSE;
    l_bl1_skipFlag    = R_RFD_FALSE;
    l_bu4_loopCount   = 0U;
    l_bu4_SWASVA      = 0U;
    l_bu1_FSWASTAT    = 0U;
    
    
    /* Beginning of the Critical Section */
    R_RFD_HOOK_EnterCriticalSection();
    
    /* Set FACI as FACI0 */
    rfd_fv0_SetFaci(R_RFD_FACI0);
    
    #ifndef    __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__
        /* Valid the R_RFD_VALUE_DFERSTC_ERRCLR */
        R_RFD_REG_DFERSTC = R_RFD_VALUE_DFERSTC_ERRCLR;     /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    #else
        /* Valid the R_RFD_VALUE_DFSERSTC_SSTCLR */
        R_RFD_REG_DFSERSTC = R_RFD_VALUE_DFSERSTC_SSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Valid the R_RFD_VALUE_DFDERSTC_DSTCLR */
        R_RFD_REG_DFDERSTC = R_RFD_VALUE_DFDERSTC_DSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    #endif  /* __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ */
    
    /* Read from R_RFD_FLAG_SWASVA */
    l_bu4_SWASVA = R_RFD_FLAG_SWASVA;                   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Check ECC 2bit Error or 1bit Error is occurred */
    l_bl1_errorFlag = rfd_fbl_CheckDFEccError();
    
    /* ECC 2bit Error or 1bit Error is NOT occurred */
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* SVA value in the Switch Area is NOT written completely */
        if ((l_bu4_SWASVA != R_RFD_VALUE_VALID_AREA0)&&(l_bu4_SWASVA != R_RFD_VALUE_VALID_AREA1))
        {
            /* Written value is not correct */
            l_bl1_errorFlag = R_RFD_TRUE;
            
            /* Set Return value */
            l_bu4_returnValue = R_RFD_ERR_SWITCH_DATA;
        }
        /* SVA value in the Switch Area is written completely */
        else
        {
            /* no operation */
        }
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    /* ECC 2bit Error or 1bit Error is occurred */
    else
    {
        /* There is a not completed data */
        l_bl1_errorFlag = R_RFD_TRUE;
        
        /* Set Return value */
        l_bu4_returnValue = R_RFD_ERR_SWITCH_DATA;
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Compare the old setting to new setting for Security Setting */
        
        /* Read the value of FSWASTAT register */
        l_bu1_FSWASTAT = rfd_fu1_ReadFSWASTAT(R_RFD_FACI0);
        
        /* SWASVA is R_RFD_VALUE_VALID_AREA1 setting */
        if (l_bu4_SWASVA == R_RFD_VALUE_VALID_AREA1)
        {
            /* SECVA in FSWASTAT is 1 (Area 1 is valid) */
            if (((T_u1)l_bu1_FSWASTAT & (T_u1)R_RFD_MASK_FSWASTAT_SECVA) != (T_u1)0U)
            {                                                           /* !CERT-C rule INT02 (QAC message 2100) */
                /* Old setting and new setting is same, so the process after this can be skipped */
                l_bl1_skipFlag = R_RFD_TRUE;
                
                /* Set Return value */
                l_bu4_returnValue = R_RFD_OK;
            }
            else
            {
                /* no operation */
                /* Old setting and new setting is different, so continue to process after this */
            }
            
        } /* if (l_bu4_SWASVA == R_RFD_VALUE_VALID_AREA1) */
        
        /* SWASVA is R_RFD_VALUE_VALID_AREA0 setting */
        else
        {
            /* SECVA in FSWASTAT is 0 (Area 0 is valid) */
            if (((T_u1)l_bu1_FSWASTAT & (T_u1)R_RFD_MASK_FSWASTAT_SECVA) == (T_u1)0U)
            {                                                           /* !CERT-C rule INT02 (QAC message 2100) */
                /* Old setting and new setting is same, so the process after this can be skipped */
                l_bl1_skipFlag = R_RFD_TRUE;
                
                /* Set Return value */
                l_bu4_returnValue = R_RFD_OK;
            }
            else
            {
                /* no operation */
                /* Old setting and new setting is different, so continue to process after this */
            }
        }
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    /* End of the Critical Section */
    R_RFD_HOOK_ExitCriticalSection();
    
    /* If the status is "not error" and "not skip" */
    if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_skipFlag == R_RFD_FALSE))  /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Beginning of the Critical Section */
        R_RFD_HOOK_EnterCriticalSection();
        
        /* Set FACI as FACI0 */
        rfd_fv0_SetFaci(R_RFD_FACI0);
        
        #ifndef	__RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__
            /* Valid the R_RFD_VALUE_DFERSTC_ERRCLR */
            R_RFD_REG_DFERSTC = R_RFD_VALUE_DFERSTC_ERRCLR;     /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        #else
            /* Valid the R_RFD_VALUE_DFSERSTC_SSTCLR */
            R_RFD_REG_DFSERSTC = R_RFD_VALUE_DFSERSTC_SSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            
            /* Valid the R_RFD_VALUE_DFDERSTC_DSTCLR */
            R_RFD_REG_DFDERSTC = R_RFD_VALUE_DFDERSTC_DSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        #endif  /* __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ */
        
        /* Acquire the loop number */
        l_bu4_checkItemNumber = sizeof(bu4_toCheckSSAVOFCitem)/sizeof(bu4_toCheckSSAVOFCitem[0]);
        
        /* Check the value of items of Security setting Area */
        for (l_bu4_loopCount = 0U; l_bu4_loopCount < l_bu4_checkItemNumber; l_bu4_loopCount++)
        {
            /* Read from item for checking */
            l_bu4_readValue = *((volatile T_u4 *)bu4_toCheckSSAVOFCitem[l_bu4_loopCount]);
                                                            /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            /* Check ECC 2bit Error or 1bit Error is occurred */
            l_bl1_errorFlag = rfd_fbl_CheckDFEccError();
            
            /* ECC 2bit Error or 1bit Error is NOT occurred */
            if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
            {
                /* VOFC value in the Security Setting Area is NOT written completely */
                if (l_bu4_readValue != R_RFD_VALUE_WRITTEN_COMPLETELY)
                {
                    /* There is a not completed data */
                    l_bl1_errorFlag = R_RFD_TRUE;
                    
                    /* Set Return value */
                    l_bu4_returnValue = R_RFD_ERR_SECURITY_DATA;
                }
                /* VOFC value in the Security Setting Area is written completely */
                else
                {
                    /* no operation */
                }
            } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
            
            /* ECC 2bit Error or 1bit Error is occurred */
            else
            {
                /* There is a not completed data */
                l_bl1_errorFlag = R_RFD_TRUE;
                
                /* Set Return value */
                l_bu4_returnValue = R_RFD_ERR_SECURITY_DATA;
            }
            
            /* If an error is occurred, escape from for loop statement */
            if (l_bl1_errorFlag == R_RFD_TRUE)  /* !CERT-C rule INT02 (QAC message 2100) */
            {
                break;
            }
            else
            {
                /* no operation */
            }
        }
        
        /* End of the Critical Section */
        R_RFD_HOOK_ExitCriticalSection();
        
    } /* if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_skipFlag == R_RFD_FALSE)) */
    
    else
    {
        /* no operation */
    }
    
    return(l_bu4_returnValue);
    
}


/**********************************************************************************************************************
**  Function Name   : rfd_fu4_CheckBlkProtectionArea0
**  
**  - Outline
**      Checks whether data is stored correctly in Block Protection Area 0 in the Hardware Property Area
**  - Format
**      T_u4_RFDReturn
**          rfd_fu4_CheckBlkProtectionArea0(void);
**  - Input parameter
**      non input parameter
**  - Return
**      R_RFD_OK                        : Normal End
**      R_RFD_ERR_SWITCH_DATA           : Some data in Switch Area are not correct
**      R_RFD_ERR_BLOCKPROTECTION0_DATA : Some data in Block Protection Area for FACI0 are not correct
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The value of AnPC (n = 0 or 1) in the Switch Area must indicate that the area is programmed
**  
**  - Traceability        : [Covers:UD_03_390]
**********************************************************************************************************************/

T_u4_RFDReturn
rfd_fu4_CheckBlkProtectionArea0(void)
{
    /* !QAC(RCMA) message 1505 */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function   */
    T_u4            l_bu4_readValue;        /* The reading value                */
    T_bl            l_bl1_errorFlag;        /* Error flag                       */
    T_bl            l_bl1_skipFlag;         /* Skip flag                        */
    T_u4            l_bu4_loopCount;        /* loop count for "for statement"   */
    T_u4            l_bu4_checkItemNumber;  /* The number of items for checking */
    T_u4            l_bu4_SWABVA0;          /* Value of BVA0 in Switch Area     */
    T_u1            l_bu1_FSWASTAT;         /* Value of FSWASTAT register       */
    
    /* Initialization of the local variables */
    l_bu4_returnValue = R_RFD_OK;
    l_bu4_readValue   = 0U;
    l_bl1_errorFlag   = R_RFD_FALSE;
    l_bl1_skipFlag    = R_RFD_FALSE;
    l_bu4_loopCount   = 0U;
    l_bu4_SWABVA0     = 0U;
    l_bu1_FSWASTAT    = 0U;
    
    
    /* Beginning of the Critical Section */
    R_RFD_HOOK_EnterCriticalSection();
    
    /* Set FACI as FACI0 */
    rfd_fv0_SetFaci(R_RFD_FACI0);
    
    #ifndef    __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__
        /* Valid the R_RFD_VALUE_DFERSTC_ERRCLR */
        R_RFD_REG_DFERSTC = R_RFD_VALUE_DFERSTC_ERRCLR;     /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    #else
        /* Valid the R_RFD_VALUE_DFSERSTC_SSTCLR */
        R_RFD_REG_DFSERSTC = R_RFD_VALUE_DFSERSTC_SSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Valid the R_RFD_VALUE_DFDERSTC_DSTCLR */
        R_RFD_REG_DFDERSTC = R_RFD_VALUE_DFDERSTC_DSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    #endif  /* __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ */
    
    /* Read from R_RFD_FLAG_SWABVA0 */
    l_bu4_SWABVA0 = R_RFD_FLAG_SWABVA0;                 /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Check ECC 2bit Error or 1bit Error is occurred */
    l_bl1_errorFlag = rfd_fbl_CheckDFEccError();
    
    /* ECC 2bit Error or 1bit Error is NOT occurred */
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* BVA0 value in the Switch Area is NOT written completely */
        if ((l_bu4_SWABVA0 != R_RFD_VALUE_VALID_AREA0)&&(l_bu4_SWABVA0 != R_RFD_VALUE_VALID_AREA1))
        {
            /* Written value is not correct */
            l_bl1_errorFlag = R_RFD_TRUE;
            
            /* Set Return value */
            l_bu4_returnValue = R_RFD_ERR_SWITCH_DATA;
        }
        /* BVA0 value in the Switch Area is written completely */
        else
        {
            /* no operation */
        }
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    /* ECC 2bit Error or 1bit Error is occurred */
    else
    {
        /* There is a not completed data */
        l_bl1_errorFlag = R_RFD_TRUE;
        
        /* Set Return value */
        l_bu4_returnValue = R_RFD_ERR_SWITCH_DATA;
    }
    
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Compare the old setting to new setting for Block Protection Area0 Setting */
        
        /* Read the value of FSWASTAT register */
        l_bu1_FSWASTAT = rfd_fu1_ReadFSWASTAT(R_RFD_FACI0);
        
        /* SWABVA0 is R_RFD_VALUE_VALID_AREA1 setting */
        if (l_bu4_SWABVA0 == R_RFD_VALUE_VALID_AREA1)
        {
            /* BPVA0 in FSWASTAT is 1 (Area 1 is valid) */
            if (((T_u1)l_bu1_FSWASTAT & (T_u1)R_RFD_MASK_FSWASTAT_BPVA0) != (T_u1)0U)
            {                                                       /* !CERT-C rule INT02 (QAC message 2100) */
                /* Old setting and new setting is same, so the process after this can be skipped */
                l_bl1_skipFlag = R_RFD_TRUE;
                
                /* Set Return value */
                l_bu4_returnValue   = R_RFD_OK;
            }
            else
            {
                /* no operation */
                /* Old setting and new setting is different, so continue to process after this */
            }
        } /* if (l_bu4_SWABVA0 == R_RFD_VALUE_VALID_AREA1) */
        
        /* SWABVA0 is R_RFD_VALUE_VALID_AREA0 setting */
        else
        {
            /* BPVA0 in FSWASTAT is 0 (Area 0 is valid) */
            if (((T_u1)l_bu1_FSWASTAT & (T_u1)R_RFD_MASK_FSWASTAT_BPVA0) == (T_u1)0U)
            {                                                           /* !CERT-C rule INT02 (QAC message 2100) */
                /* Old setting and new setting is same, so the process after this can be skipped */
                l_bl1_skipFlag = R_RFD_TRUE;
                
                /* Set Return value */
                l_bu4_returnValue = R_RFD_OK;
            }
            else
            {
                /* no operation */
                /* Old setting and new setting is different, so continue to process after this */
            }
        }
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    /* End of the Critical Section */
    R_RFD_HOOK_ExitCriticalSection();
    
    /* If the status is "not error" and "not skip" */
    if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_skipFlag == R_RFD_FALSE))  /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Beginning of the Critical Section */
        R_RFD_HOOK_EnterCriticalSection();
        
        /* Set FACI as FACI0 */
        rfd_fv0_SetFaci(R_RFD_FACI0);
        
        #ifndef    __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__
            /* Valid the R_RFD_VALUE_DFERSTC_ERRCLR */
            R_RFD_REG_DFERSTC = R_RFD_VALUE_DFERSTC_ERRCLR;     /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        #else
            /* Valid the R_RFD_VALUE_DFSERSTC_SSTCLR */
            R_RFD_REG_DFSERSTC = R_RFD_VALUE_DFSERSTC_SSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            
            /* Valid the R_RFD_VALUE_DFDERSTC_DSTCLR */
            R_RFD_REG_DFDERSTC = R_RFD_VALUE_DFDERSTC_DSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        #endif  /* __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ */
        
        /* Acquire the loop number */
        l_bu4_checkItemNumber = sizeof(bu4_toCheckBPA0VOFCitem)/sizeof(bu4_toCheckBPA0VOFCitem[0]);
        
        /* Check the value of items of Block Protection Area0 */
        for (l_bu4_loopCount = 0U; l_bu4_loopCount < l_bu4_checkItemNumber; l_bu4_loopCount++)
        {
            /* Read from item for checking */
            l_bu4_readValue = *((volatile T_u4 *)bu4_toCheckBPA0VOFCitem[l_bu4_loopCount]);
                                                            /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            /* Check ECC 2bit Error or 1bit Error is occurred */
            l_bl1_errorFlag = rfd_fbl_CheckDFEccError();
            
            /* ECC 2bit Error or 1bit Error is NOT occurred */
            if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
            {
                /* VOFC value in the Block Protection Area0 is NOT written completely */
                if (l_bu4_readValue != R_RFD_VALUE_WRITTEN_COMPLETELY)
                {
                    /* There is a not completed data */
                    l_bl1_errorFlag = R_RFD_TRUE;
                    
                    /* Set Return value */
                    l_bu4_returnValue = R_RFD_ERR_BLOCKPROTECTION0_DATA;
                }
                /* VOFC value in the Block Protection Area0 is written completely */
                else
                {
                    /* no operation */
                }
                
            } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
            
            /* ECC 2bit Error or 1bit Error is occurred */
            else
            {
                /* There is a not completed data */
                l_bl1_errorFlag = R_RFD_TRUE;
                
                /* Set Return value */
                l_bu4_returnValue = R_RFD_ERR_BLOCKPROTECTION0_DATA;
            }
            
            /* If an error is occurred, escape from for loop statement */
            if (l_bl1_errorFlag == R_RFD_TRUE)  /* !CERT-C rule INT02 (QAC message 2100) */
            {
                break;
            }
            else
            {
                /* no operation */
            }
        }
        /* End of the Critical Section */
        R_RFD_HOOK_ExitCriticalSection();
        
    } /* if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_skipFlag == R_RFD_FALSE)) */
    
    else
    {
        /* no operation */
    }
    
    return(l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu4_CheckBlkProtectionArea1
**  
**  - Outline
**      Checks whether data is stored correctly in Block Protection Area 1 in the Hardware Property Area
**  - Format
**      T_u4_RFDReturn
**          rfd_fu4_CheckBlkProtectionArea1(void);
**  - Input parameter
**      non input parameter
**  - Return
**      R_RFD_OK                        : Normal End
**      R_RFD_ERR_SWITCH_DATA           : Some data in Switch Area are not correct
**      R_RFD_ERR_BLOCKPROTECTION1_DATA : Some data in Block Protection Area for FACI1 are not correct
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The value of AnPC (n = 0 or 1) in the Switch Area must indicate that the area is programmed
**  
**  - Traceability        : [Covers:UD_03_400]
**********************************************************************************************************************/

T_u4_RFDReturn
rfd_fu4_CheckBlkProtectionArea1(void)
{
    /* !QAC(RCMA) message 1505 */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function   */
    T_u4            l_bu4_readValue;        /* The reading value                */
    T_bl            l_bl1_errorFlag;        /* Error flag                       */
    T_bl            l_bl1_skipFlag;         /* Skip flag                        */
    T_u4            l_bu4_loopCount;        /* loop count for "for statement"   */
    T_u4            l_bu4_checkItemNumber;  /* The number of items for checking */
    T_u4            l_bu4_SWABVA1;          /* Value of BVA1 in Switch Area     */
    T_u1            l_bu1_FSWASTAT;         /* Value of FSWASTAT register       */
    
    /* Initialization of the local variables */
    l_bu4_returnValue = R_RFD_OK;
    l_bu4_readValue   = 0U;
    l_bl1_errorFlag   = R_RFD_FALSE;
    l_bl1_skipFlag    = R_RFD_FALSE;
    l_bu4_loopCount   = 0U;
    l_bu4_SWABVA1     = 0U;
    l_bu1_FSWASTAT    = 0U;
    
    
    /* Block Protection Area for FACI1 is valid ? */
    if (R_RFD_BLOCK_PROTECTION_AREA1 != R_RFD_ENABLE)
    {
        /* Block Protection Area for FACI1 is invalid */
        /* Set Return value */
        l_bu4_returnValue = R_RFD_OK;
    }
    /* Block Protection Area for FACI1 is valid */
    else
    {
        /* Beginning of the Critical Section */
        R_RFD_HOOK_EnterCriticalSection();
        
        /* Set FACI as FACI1 */
        rfd_fv0_SetFaci(R_RFD_FACI1);
        
        #ifndef    __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__
            /* Valid the R_RFD_VALUE_DFERSTC_ERRCLR */
            R_RFD_REG_DFERSTC = R_RFD_VALUE_DFERSTC_ERRCLR;     /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        #endif  /* __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ */
        
        /* Read from R_RFD_FLAG_SWABVA1 */
        l_bu4_SWABVA1 = R_RFD_FLAG_SWABVA1;                 /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Check ECC 2bit Error or 1bit Error is occurred */
        l_bl1_errorFlag = rfd_fbl_CheckDFEccError();
        
        /* ECC 2bit Error or 1bit Error is NOT occurred */
        if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* BVA1 value in the Switch Area is NOT written completely */
            if ((l_bu4_SWABVA1 != R_RFD_VALUE_VALID_AREA0)&&(l_bu4_SWABVA1 != R_RFD_VALUE_VALID_AREA1))
            {
                /* Written value is not correct */
                l_bl1_errorFlag = R_RFD_TRUE;
                
                /* Set Return value */
                l_bu4_returnValue = R_RFD_ERR_SWITCH_DATA;
            }
            /* BVA1 value in the Switch Area is written completely */
            else
            {
                /* no operation */
            }
        } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
        
        /* ECC 2bit Error or 1bit Error is occurred */
        else
        {
            /* There is a not completed data */
            l_bl1_errorFlag = R_RFD_TRUE;
            
            /* Set Return value */
            l_bu4_returnValue = R_RFD_ERR_SWITCH_DATA;
        }
        
        if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* Compare the old setting to new setting for Block Protection Area1 Setting */
            
            /* Read the value of FSWASTAT register */
            l_bu1_FSWASTAT = rfd_fu1_ReadFSWASTAT(R_RFD_FACI1);
            
            /* SWABVA1 is R_RFD_VALUE_VALID_AREA1 setting */
            if (l_bu4_SWABVA1 == R_RFD_VALUE_VALID_AREA1)
            {
                /* BPVA1 in FSWASTAT is 1 (Area 1 is valid) */
                if (((T_u1)l_bu1_FSWASTAT & (T_u1)R_RFD_MASK_FSWASTAT_BPVA1) != (T_u1)0U)
                {                                                       /* !CERT-C rule INT02 (QAC message 2100) */
                    /* Old setting and new setting is same, so the process after this can be skipped */
                    l_bl1_skipFlag = R_RFD_TRUE;
                    
                    /* Set Return value */
                    l_bu4_returnValue = R_RFD_OK;
                }
                else
                {
                    /* no operation */
                    /* Old setting and new setting is different, so continue to process after this */
                }
            } /* if (l_bu4_SWABVA1 == R_RFD_VALUE_VALID_AREA1) */
            
            /* SWABVA1 is R_RFD_VALUE_VALID_AREA0 setting */
            else
            {
                /* BPVA1 in FSWASTAT is 0 (Area 0 is valid) */
                if (((T_u1)l_bu1_FSWASTAT & (T_u1)R_RFD_MASK_FSWASTAT_BPVA1) == (T_u1)0U)
                {                                                       /* !CERT-C rule INT02 (QAC message 2100) */
                    /* Old setting and new setting is same, so the process after this can be skipped */
                    l_bl1_skipFlag = R_RFD_TRUE;
                    
                    /* Set Return value */
                    l_bu4_returnValue = R_RFD_OK;
                }
                else
                {
                    /* no operation */
                    /* Old setting and new setting is different, so continue to process after this */
                }
            }
            
        } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
        
        else
        {
            /* no operation */
        }
        
        /* End of the Critical Section */
        R_RFD_HOOK_ExitCriticalSection();
        
        /* If the status is "not error" and "not skip" */
        if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_skipFlag == R_RFD_FALSE))
        {                                               /* !CERT-C rule INT02 (QAC message 2100) */
            /* Beginning of the Critical Section */
            R_RFD_HOOK_EnterCriticalSection();
            
            /* Set FACI as FACI1 */
            rfd_fv0_SetFaci(R_RFD_FACI1);
            
            #ifndef    __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__
                /* Valid the R_RFD_VALUE_DFERSTC_ERRCLR */
                R_RFD_REG_DFERSTC = R_RFD_VALUE_DFERSTC_ERRCLR;      /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            #endif  /* __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ */
            
            /* Acquire the loop number */
            l_bu4_checkItemNumber = sizeof(bu4_toCheckBPA1VOFCitem)/sizeof(bu4_toCheckBPA1VOFCitem[0]);
            
            /* Check the value of items of Block Protection Area1 */
            for (l_bu4_loopCount = 0U; l_bu4_loopCount < l_bu4_checkItemNumber; l_bu4_loopCount++)
            {
                /* Read from item for checking */
                l_bu4_readValue = *((volatile T_u4 *)bu4_toCheckBPA1VOFCitem[l_bu4_loopCount]);
                                                                 /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
                /* Check ECC 2bit Error or 1bit Error is occurred */
                l_bl1_errorFlag = rfd_fbl_CheckDFEccError();
                
                /* ECC 2bit Error or 1bit Error is NOT occurred */
                if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
                {
                    /* VOFC value in the Block Protection Area1 is NOT written completely */
                    if (l_bu4_readValue != R_RFD_VALUE_WRITTEN_COMPLETELY)
                    {
                        /* There is a not completed data */
                        l_bl1_errorFlag = R_RFD_TRUE;
                        
                        /* Set Return value */
                        l_bu4_returnValue = R_RFD_ERR_BLOCKPROTECTION1_DATA;
                    }
                    /* VOFC value in the Block Protection Area1 is written completely */
                    else
                    {
                        /* no operation */
                    }
                } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
                
                /* ECC 2bit Error or 1bit Error is occurred */
                else
                {
                    /* There is a not completed data */
                    l_bl1_errorFlag = R_RFD_TRUE;
                    
                    /* Set Return value */
                    l_bu4_returnValue = R_RFD_ERR_BLOCKPROTECTION1_DATA;
                }
                
                /* If an error is occurred, escape from for loop statement */
                if (l_bl1_errorFlag == R_RFD_TRUE)      /* !CERT-C rule INT02 (QAC message 2100) */
                {
                    break;
                }
                else
                {
                    /* no operation */
                }
            }
            /* End of the Critical Section */
            R_RFD_HOOK_ExitCriticalSection();
            
        } /* if ((l_bl1_errorFlag == R_RFD_FALSE)&&(l_bl1_skipFlag == R_RFD_FALSE)) */
        else
        {
            /* no operation */
        }
    }
    
    return(l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fbl_CheckDFEccError
**  
**  - Outline
**      Checks whether an ECC 2-bit error or ECC 1-bit error has occurred in the data flash memory
**  - Format
**      T_bl
**          rfd_fbl_CheckDFEccError(void);
**  - Input parameter
**      non input parameter
**  - Return
**      R_RFD_TRUE      : ECC 2bit Error or ECC 1bit Error was occurred
**      R_RFD_FALSE     : ECC 2bit Error or ECC 1bit Error was NOT occurred
**  - Preconditions
**      This function must be executed with the operation target set to FACI0
**  
**  - Traceability        : [Covers:UD_03_410]
**********************************************************************************************************************/

#ifndef __R_RFD_USE_STUB_ECC_ERROR__   /* For Normal Code */
T_bl
rfd_fbl_CheckDFEccError(void)
{
    /* !QAC(RCMA) message 1505 */
    
    /* Definition of the local variables */

    T_bl            l_bl1_errorFlag;    /* Error flag                   */

    #ifndef    __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__
        T_u4            l_bu4_DFERSTR;      /* Value of DFERSTR register    */
    #else
        T_u4            l_bu4_DFSERSTR;     /* Value of DFSERSTR register    */
        T_u4            l_bu4_DFDERSTR;     /* Value of DFDERSTR register    */
    #endif  /* __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ */
    
    /* Initialization of the local variables  */
    l_bl1_errorFlag = R_RFD_FALSE;

    #ifndef    __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__
        l_bu4_DFERSTR   = 0UL;
    #else
        l_bu4_DFSERSTR  = 0UL;
        l_bu4_DFDERSTR  = 0UL;
    #endif  /* __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ */
    

    #ifndef    __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__
        /* Read from DFERSTR register */
        l_bu4_DFERSTR = R_RFD_REG_DFERSTR;  /* Due to avoid to read twice                 */
                                            /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* SEDF bit or DEDF bit in the DFERSTR is valid ? */
        if ((l_bu4_DFERSTR & (R_RFD_VALUE_DFERSTR_SEDF | R_RFD_VALUE_DFERSTR_DEDF)) != 0UL)
        {
            /* ECC error was occurred */
            l_bl1_errorFlag = R_RFD_TRUE;
            
            /* Valid the R_RFD_VALUE_DFERSTC_ERRCLR */
            R_RFD_REG_DFERSTC = R_RFD_VALUE_DFERSTC_ERRCLR; /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            
        } /* if ((l_bu4_DFERSTR & (R_RFD_VALUE_DFERSTR_SEDF | R_RFD_VALUE_DFERSTR_DEDF)) != 0UL) */
        
    #else
        /* Read from DFSERSTR register */
        l_bu4_DFSERSTR = R_RFD_REG_DFSERSTR;    /* Due to avoid to read twice                 */
                                                /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        /* Read from DFDERSTR register */
        l_bu4_DFDERSTR = R_RFD_REG_DFDERSTR;    /* Due to avoid to read twice                 */
                                                /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        /* SEDFn bit in the DFSERSTR or DEDF bit in the DFDERSTR is valid ? */
        if (((l_bu4_DFSERSTR & (R_RFD_VALUE_DFSERSTR_SEDF0 | R_RFD_VALUE_DFSERSTR_SEDF1
              | R_RFD_VALUE_DFSERSTR_SEDF2 | R_RFD_VALUE_DFSERSTR_SEDF3)) != 0UL)
            || ((l_bu4_DFDERSTR & R_RFD_VALUE_DFDERSTR_DEDF) != 0UL ))
        {
            /* ECC error was occurred */
            l_bl1_errorFlag = R_RFD_TRUE;
            
            /* Valid the R_RFD_VALUE_DFSERSTC_SSTCLR */
            R_RFD_REG_DFSERSTC = R_RFD_VALUE_DFSERSTC_SSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            
            /* Valid the R_RFD_VALUE_DFDERSTC_DSTCLR */
            R_RFD_REG_DFDERSTC = R_RFD_VALUE_DFDERSTC_DSTCLR;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            
        } /* if (((l_bu4_DFSERSTR & (R_RFD_VALUE_DFSERSTR_SEDF0 | R_RFD_VALUE_DFSERSTR_SEDF1   */
          /*       | R_RFD_VALUE_DFSERSTR_SEDF2 | R_RFD_VALUE_DFSERSTR_SEDF3)) != 0UL))        */
          /*     || ((l_bu4_DFDERSTR & R_RFD_VALUE_DFERSTR_DEDF) != 0UL ))                     */
        
    #endif  /* __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ */
    else
    {
        /* no operation */
    }
    
    return (l_bl1_errorFlag);
    
}
#endif  /* __R_RFD_USE_STUB_ECC_ERROR__ */

/**************************************************************************************************************
 *  Section declaration
 *    - End of the definition of the text section for the Extra Area of the Code Flash Control Component
 *************************************************************************************************************/

/* End of the definition of the text section */
#define  R_RFD_EXTRA_STOP_SEC_CODE
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

#endif  /* R_RFD_CONTROL_TARGET_CODEFLASH == R_RFD_DISABLE */
