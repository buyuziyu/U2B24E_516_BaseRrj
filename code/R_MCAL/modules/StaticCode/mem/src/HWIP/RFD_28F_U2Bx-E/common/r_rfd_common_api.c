/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD28F)
    
    File Name       : r_rfd_commmon_api.c
    Program Version : V1.00
    File Revision   : $Rev: 4343 $
    File Date       : $Date:: 2023-05-17 16:23:15 +0700#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : API for Common Process
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
 *   Rule         : MISRA-C 2012 rule 2.7 / QAC message 3206
 *   Message      : The parameter '%s' is not used in this function.
 *   Reason       : It is an parameter which is not used at this time but it is expected to be specified in the future
 *                  and we want to define API interface without changing it.
 *   Verification : Incorrect declaration would result in compilation fails.
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
 *                  This is "version information" to be placed in the const attribute area and is declared
 *                  so as to acquire it directly from the corresponding area.
 *   Verification : Incorrect declaration would result in compilation fails.
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
 *   Rule         : MISRA-C 2012 rule 10.1 / QAC message 4522
 *   Message      : An expression of 'essentially enum' type (%1s) is being used as the %2s operand of this bitwise
 *                  operator (%3s).
 *   Reason       : This declaration is intentionally used according to the bit allocation of register and avoiding
 *                  to specify outside range by enumerated types, this prioritize code efficiency and readability.
 *   Verification : Incorrect using would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 11.4 / QAC message 0303
 *   Message      : Cast between a pointer to volatile object and an integral type.
 *   Reason       : For effective embedded programming, integer to pointer conversions are used.
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
 *   Rule         : CERT-C rule ARR02-EX1
 *   Message      : Exception of ARR02.
 *   Reason       : STR11-C is a specific exception to this recommendation; it requires that the bound of a character
 *                  array initialized with a string literal is unspecified.
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
 *   Rule         : CERT-C rule INT02 / QAC message 2100,2101
 *   Message      : Understand integer conversion rules.
 *   Reason       : Since it can be confirmed that the corresponding operation result does not exceed the specified
 *                  type range, the correct operation result can be acquired without conversion to integer type.
 *                  So, there is no problem.
 *   Verification : Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule INT30 / QAC message 3383
 *   Message      : Cannot identify wraparound guard for unsigned arithmetic expression.
 *   Reason       : The corresponding operation result counts the number of FACIs present, and the increment result
 *                  cannot exceed the specified type range. So, there is no problem.
 *   Verification : Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule EXP45 / QAC message 3416
 *   Message      : Logical operation performed on expression with possible side effects.
 *   Reason       : Logical operation accesses volatile object which is a register access. All register addresses are
 *                  generated with volatile qualifier. There is no impact on the functionality due to this conditional
 *                  check for mode change.
 *   Verification : Incorrect conditional checking would result in test fails.
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
 *   Rule         : No MISRA-C 2012 or CERT-C rule / QAC(RCMA) message 1532
 *   Message      : The function '%1s' is only referenced in one translation unit - but not the one
 *                  in which it is defined.
 *   Reason       : The API in common component is assumed to include an API that can be commonly used by other
 *                  components. So, there is no problem.
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

#include "r_rfd_config.h"           /* !CERT-C rule 5002 */
#include "r_rfd.h"
#include "r_rfd_common.h"           /* !CERT-C rule 5002 */
#include "r_rfd_common_local.h"     /* !CERT-C rule 5002 */
#include "r_rfd_common_version.h"   /* !CERT-C rule 5002 */

/**************************************************************************************************************
 *  Version Information
 *    - Version of the Common Flash Control Component
 *  Section declaration
 *    - Definition of the const section
 *
 *  - Traceability          : [Covers:UD_40_001] [Covers:UD_40_002]
 *************************************************************************************************************/

/* Start of the definition of the const section */
#define  R_RFD_VERSION_COMMON_START_SEC_CONST_UNSPECIFIED
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */

/* Alignment4 for the variables */
R_RFD_ALIGN_VARIABLE_4

/* Version of the Common Flash Control Component */
const T_u1  pu1_versionCommonComponent[] = R_RFD_VERSION_COMMON_COMPONENT;
                                /* !MISRA-C 2012 rule 8.4 (QAC message 3408)                      */
                                /* QAC(RCMA) message 1502                                         */
                                /* !CERT-C rule ARR02 (QAC message 3674) -> CERT-C rule ARR02-EX1 */

/* End of the definition of the const section */
#define  R_RFD_VERSION_COMMON_STOP_SEC_CONST_UNSPECIFIED
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

/**************************************************************************************************************
 *  Section declaration
 *    - Start of the definition of the text section for the Common Flash Control Component
 *
 *  - Traceability          : [Covers:UD_20_006]
 *************************************************************************************************************/

/* Start of the definition of the text section */
#define  R_RFD_COMMON_START_SEC_CODE
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

/**********************************************************************************************************************
**  Function Name   : R_RFD_Init
**  
**  - Outline
**      Initializes the RFD28F
**  - Format
**      T_u4_RFDReturn
**          R_RFD_Init(
**              T_u2        i_u2_FaciFrequency
**          );
**  - Input parameter
**      i_u2_FaciFrequency  : FACI Frequency
**  - Return
**      R_RFD_OK                    : Normal End
**      R_RFD_ERR_INTERNAL_HW       : Internal Hardware error
**      R_RFD_ERR_FACI_DEFINITION   : There are mistakes in setting of FACI described in "r_rfd_config.h"
**  - Preconditions
**      No preconditions
**  
**  - Traceability          : [Covers:UD_01_100]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_Init(T_u2 i_u2_FaciFrequency)
{
    /* !MISRA-C 2012 rule 2.7 (QAC message 3206) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;                          /* Return value for this function    */
    T_u4            l_bu4_numberOfFaci;                         /* Number of FACI                    */
    T_bl            l_bl1_errorFlag;                            /* Error flag                        */
    T_u2_FACI       l_bu2_faciInitInfo[R_RFD_MAX_FACI_NUMBER];  /* For FACI initializing information */
    T_u2_FACI       l_bu2_loopCount;                             /* For FACI initializing loop        */
    
    
    /* Initialization of the local variables */
    l_bu4_returnValue    = R_RFD_OK;
    l_bu4_numberOfFaci   = 0U;
    l_bl1_errorFlag      = R_RFD_FALSE;
    l_bu2_loopCount       = 0U;
    
    for(l_bu2_loopCount = 0U; l_bu2_loopCount < R_RFD_MAX_FACI_NUMBER; l_bu2_loopCount++)
    {
        l_bu2_faciInitInfo[l_bu2_loopCount] = R_RFD_INVALID_FACI;
    }
    
    /**********************************************************************************************
     *  Check whether "Number of FACI operated by RFD28F (R_RFD_NUMBER_OF_FACI)" and
     *  "Number of definition per FACI number (R_RFD_BASE_ADDRESS_FACIx, R_RFD_CMDAREA_FACIx,
     *  R_RFD_DF_BASE_FACIx)" set in the configuration match.
     *********************************************************************************************/
    /* Check to exist FACI0 */
    if (R_RFD_VALID_FACI0 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
    {
        l_bu2_faciInitInfo[l_bu4_numberOfFaci] = R_RFD_FACI0;
        l_bu4_numberOfFaci++;       /* !CERT-C rule INT30 (QAC message 3383) */
    }
    else
    {
        /* no operation */
    }
    
    /* Check to exist FACI1 */
    if (R_RFD_VALID_FACI1 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
    {
        l_bu2_faciInitInfo[l_bu4_numberOfFaci] = R_RFD_FACI1;
        l_bu4_numberOfFaci++;       /* !CERT-C rule INT30 (QAC message 3383) */
    }
    else
    {
        /* no operation */
    }
    
    /* Check to exist FACI2 */
    if (R_RFD_VALID_FACI2 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
    {
        l_bu2_faciInitInfo[l_bu4_numberOfFaci] = R_RFD_FACI2;
        l_bu4_numberOfFaci++;       /* !CERT-C rule INT30 (QAC message 3383) */
    }
    else
    {
        /* no operation */
    }
    
    /* Check the number of FACI */
    if (l_bu4_numberOfFaci != (T_u4)R_RFD_NUMBER_OF_FACI)
    {
        /* Definition of FACI is incorrect (Set return value) */
        l_bu4_returnValue = R_RFD_ERR_FACI_DEFINITION;
        
        /* Error occurred */
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    /**********************************************************************************************
     *  Initialize each FACI
     *********************************************************************************************/
    if (l_bl1_errorFlag == R_RFD_FALSE)         /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Initialize FACI0, FACI1, FACI2 */
        for(l_bu2_loopCount = 0U; l_bu2_loopCount < R_RFD_NUMBER_OF_FACI; l_bu2_loopCount++)
        {                                               /* !CERT-C rule INT02 (QAC message 2101) */
            
            /* Call main process of initialization for FACI */
            l_bu4_returnValue = rfd_fu4_InitFACI(l_bu2_faciInitInfo[l_bu2_loopCount]);
            
            if (l_bu4_returnValue == R_RFD_ERR_INTERNAL_HW)
            {
                /* Error occurred  */
                l_bl1_errorFlag = R_RFD_TRUE;
                
                /* Escape for loop */
                break;
            }
            else
            {
                /* no operation */
            }
            
        } /* for(l_bu2_loopCount = 0U; l_bu2_loopCount < R_RFD_NUMBER_OF_FACI; l_bu2_loopCount++) */
        
    }
    else
    {
        /* no operation */
    }

    /**********************************************************************************************
     *  Set the clock setting
     *********************************************************************************************/
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* No FCU clock setting */
        
        /* No registers clock setting */
        
        /* Set return value */
        l_bu4_returnValue = R_RFD_OK;
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    return(l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_ShiftToReadMode
**  
**  - Outline
**      Shifts the mode of the flash memory of the target FACI to the read mode
**  - Format
**      T_u4_RFDReturn
**          R_RFD_ShiftToReadMode(
**              T_u2_FACI   i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI     : Target FACI to be shifted to the read mode
**  - Return
**      R_RFD_OK               : Normal End
**      R_RFD_ERR_INTERNAL_HW  : Internal Hardware error
**      R_RFD_ERR_NOFACI       : Specified FACI is nonexistance
**  - Preconditions
**      The state of the flash memory must be the READY state
**  
**  - Traceability          : [Covers:UD_01_110]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_ShiftToReadMode(T_u2_FACI i_u2_TargetFACI)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    T_u1            l_bu1_FASTAT;           /* FASTAT register value          */
    volatile T_u2   l_bu2_FENTRYR;          /* FENTRYR register value         */
    T_bl            l_bl1_errorFlag;        /* Error flag                     */
    
    /* Initialization of the local variables */
    l_bu4_returnValue    = R_RFD_OK;
    l_bu1_FASTAT         = 0U;
    l_bu2_FENTRYR        = 0U;
    l_bl1_errorFlag      = R_RFD_FALSE;
    
    
    /* Check FACI number */
    l_bu4_returnValue = rfd_fu4_CheckFaciNumber(i_u2_TargetFACI);
    
    if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
    {
        /* Specified FACI is nonexistence */
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(i_u2_TargetFACI);
        
        /* Acquire the value of FASTAT register */
        l_bu1_FASTAT = R_RFD_REG_FASTAT;    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Check the command lock status */
        if (((T_u1)l_bu1_FASTAT & (T_u1)R_RFD_MASK_FASTAT_CMDLK) != (T_u1)0x00U)
        {                                                    /* !CERT-C rule INT02 (QAC message 2100) */
            /* Release the command lock status */
            l_bu4_returnValue = rfd_fu4_ReleaseCommandLock(i_u2_TargetFACI);
            
            if (l_bu4_returnValue == R_RFD_ERR_INTERNAL_HW)
            {
                /* Failed to release command lock */
                l_bl1_errorFlag = R_RFD_TRUE;
            }
            else
            {
                /* no operation */
            }
        } /* if ((l_bu1_FASTAT & R_RFD_MASK_FASTAT_CMDLK) != 0U) */
        
        else
        {
            /* no operation */
        }
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Write to register to shift to read mode */
        R_RFD_REG_FENTRYR = (R_RFD_KEY_FENTRYR | R_RFD_VALUE_READ_MODE);
                                                    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        /* Dummy read the FENTRYR register */
        l_bu2_FENTRYR = R_RFD_REG_FENTRYR;          /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        /* Read the FENTRYR register */
        l_bu2_FENTRYR = R_RFD_REG_FENTRYR;          /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Check to shift to read mode */
        /* Shift to read mode */
        if (l_bu2_FENTRYR == R_RFD_VALUE_READ_MODE) /* !CERT-C rule INT02 (QAC message 2101) */
        {                                           /* !CERT-C rule EXP45 (QAC message 3416) */
            /* Set return value */
            l_bu4_returnValue = R_RFD_OK;
        }
        /* No shift to read mode */
        else
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_ERR_INTERNAL_HW;
        }
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_ShiftToPEMode
**  
**  - Outline
**      Shifts the mode of the target memory of the target FACI to the P/E mode
**  - Format
**      T_u4_RFDReturn
**          R_RFD_ChangeToPEMode(
**              T_u2_FACI       i_u2_TargetFACI
**              T_en_FACIMode   i_en_FACIMode
**          );
**  - Input parameter
**      i_u2_TargetFACI     : Target FACI to be shifted to the P/E mode
**      i_en_FACIMode       : Target flash memory to be shifted to the P/E mode
**  - Return
**      R_RFD_OK            : Mode has already "i_en_FACIMode" or shift completed
**      R_RFD_STS_BUSY      : Set the value of "i_en_FACIMode" to the mode (Not shifted to the mode yet)
**      R_RFD_ERR_NOFACI    : Specified FACI is nonexistence
**  - Preconditions
**      The state of the flash memory must be the READY state
**  
**  - Traceability          : [Covers:UD_01_120]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_ShiftToPEMode(T_u2_FACI i_u2_TargetFACI, T_en_FACIMode i_en_FACIMode)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    volatile T_u2   l_bu2_FENTRYR;          /* FENTRYR register value         */
    T_bl            l_bl1_errorFlag;        /* Error flag                     */
    
    /* Initialization of the local variables */
    l_bu4_returnValue    = R_RFD_OK;
    l_bu2_FENTRYR        = 0U;
    l_bl1_errorFlag      = R_RFD_FALSE;
    
    
    /* Check FACI number */
    l_bu4_returnValue = rfd_fu4_CheckFaciNumber(i_u2_TargetFACI);
    
    if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
    {
        /* Specified FACI is nonexistence */
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(i_u2_TargetFACI);
        
        
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Acquire the FENTRYR register value */
        l_bu2_FENTRYR = R_RFD_REG_FENTRYR;          /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* FENTRYR register value has already "i_en_FACIMode" */
        if (l_bu2_FENTRYR == (T_u2)i_en_FACIMode)   /* !CERT-C rule INT02 (QAC message 2101) */
        {                                           /* !CERT-C rule EXP45 (QAC message 3416) */
            /* Set return value */
            l_bu4_returnValue = R_RFD_OK;
        }
        /* Set "i_en_FACIMode" to FENTRYR register */
        else
        {
            
            /* Write to the FENTRY register to shift to read mode */
            R_RFD_REG_FENTRYR = ((T_u2)R_RFD_KEY_FENTRYR | (T_u2)i_en_FACIMode);
                                                    /* !MISRA-C 2012 rule 10.1 (QAC message 4522) */
                                                    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
                                                
            /* Dummy read the FENTRYR register */
            l_bu2_FENTRYR = R_RFD_REG_FENTRYR;      /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            /* Read the FENTRYR register */
            l_bu2_FENTRYR = R_RFD_REG_FENTRYR;      /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            
            /* Check to shift to P/E mode */
            if (l_bu2_FENTRYR == (T_u2)i_en_FACIMode)   /* !CERT-C rule INT02 (QAC message 2101) */
            {                                           /* !CERT-C rule EXP45 (QAC message 3416) */
                /* Set return value */
                l_bu4_returnValue = R_RFD_OK;
            }
            /* No shift to P/E mode */
            else
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_STS_BUSY;
            }
        }
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_StatusClear
**  
**  - Outline
**      Clears the state of the target FACI
**  - Format
**      T_u4_RFDReturn
**          R_RFD_StatusClear(
**              T_u2_FACI     i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI       : Target FACI whose state is to be cleared
**  - Return
**      R_RFD_OK              : Normal End
**      R_RFD_ERR_NOFACI      : Specified FACI is nonexistence
**  - Preconditions
**      The state of the flash memory must be the READY state
**  
**  - Traceability            : [Covers:UD_01_150]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_StatusClear(T_u2_FACI i_u2_TargetFACI)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    T_bl            l_bl1_errorFlag;        /* Error flag                     */
    
    /* Initialization of the local variables  */
    l_bu4_returnValue   = R_RFD_OK;
    l_bl1_errorFlag     = R_RFD_FALSE;
    
    
    /* Check FACI number */
    l_bu4_returnValue = rfd_fu4_CheckFaciNumber(i_u2_TargetFACI);
    
    if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
    {
        /* Specified FACI is nonexistence */
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(i_u2_TargetFACI);
        
        /*  Issue the command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_STATUS_CLEAR;    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Set return value */
        l_bu4_returnValue = R_RFD_OK;
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_SetFHVE
**  
**  - Outline
**      Enables or disables programming, erasure, or blank checking of the flash memory
**  - Format
**      T_u4_RFDReturn
**          R_RFD_SetFHVE(
**              T_u2_FACI     i_u2_TargetFACI,
**              T_en_Protect  i_en_ProtectMode
**          );
**  - Input parameter
**      i_u2_TargetFACI       : Target FACI whose FHVE registers are to be manipulated
**      i_en_ProtectMode      : Specifying to enable or disable programming, erasure, or blank checking of
**                              the flash memory.
**  - Return
**      R_RFD_OK            : Normal End
**      R_RFD_ERR_NOFACI    : Specified FACI is nonexistence
**  - Preconditions
**      The state of the flash memory must be the READY state
**      
**  - Traceability            : [Covers:UD_01_200]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_SetFHVE(T_u2_FACI i_u2_TargetFACI, T_en_Protect i_en_ProtectMode)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    T_bl            l_bl1_errorFlag;        /* Error flag                     */
    volatile T_u4   i_u4_dummy;             /* Temporary for dummy read       */
                                            /* QAC message 3203               */
    /* Initialization of the local variables */
    i_u4_dummy = 0UL;
    l_bu4_returnValue   = R_RFD_OK;
    l_bl1_errorFlag     = R_RFD_FALSE;
    
    
    /* Check FACI number */
    l_bu4_returnValue = rfd_fu4_CheckFaciNumber(i_u2_TargetFACI);
    
    if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
    {
        /* Specified FACI is nonexistence */
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)         /* !CERT-C rule INT02 (QAC message 2100) */
    {
        if (i_u2_TargetFACI == R_RFD_FACI0)     /* !CERT-C rule INT02 (QAC message 2101) */
        {
            /* Set to FHVE3FP0 register  */
            R_RFD_REG_FHVE3FP0  = (T_u4)i_en_ProtectMode;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            /* Set to FHVE15FP0 register */
            R_RFD_REG_FHVE15FP0 = (T_u4)i_en_ProtectMode;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            /* Dummy read from FHVE15FP0 */
            i_u4_dummy = R_RFD_REG_FHVE15FP0;               /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        }
        else if (i_u2_TargetFACI == R_RFD_FACI1)    /* !CERT-C rule INT02 (QAC message 2101) */
        {
            /* Set to FHVE3FP1 register  */
            R_RFD_REG_FHVE3FP1  = (T_u4)i_en_ProtectMode;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            /* Set to FHVE15FP1 register */
            R_RFD_REG_FHVE15FP1 = (T_u4)i_en_ProtectMode;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            /* Dummy read from FHVE15FP1 */
            i_u4_dummy = R_RFD_REG_FHVE15FP1;               /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        }
        else if (i_u2_TargetFACI == R_RFD_FACI2)    /* !CERT-C rule INT02 (QAC message 2101) */
        {
            /* Set to FHVE3FP2 register  */
            R_RFD_REG_FHVE3FP2  = (T_u4)i_en_ProtectMode;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            /* Set to FHVE15FP2 register */
            R_RFD_REG_FHVE15FP2 = (T_u4)i_en_ProtectMode;   /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            /* Dummy read from FHVE15FP2 */
            i_u4_dummy = R_RFD_REG_FHVE15FP2;               /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
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
    
    /* SYNCP command */
    R_RFD_SYNCP();
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu4_InitFACI
**  
**  - Outline
**      Executes the initialization processing for the FACI specified by the parameter
**  - Format
**      T_u4_RFDReturn
**          rfd_fu4_InitFACI(
**              T_u2_FACI   i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI : FACI number of FACI to be initialized
**  - Return
**      R_RFD_OK                    : Normal End
**      R_RFD_ERR_INTERNAL_HW       : Internal Hardware error
**  - Preconditions
**      No preconditions
**  
**  - Traceability          : [Covers:UD_01_320]
**********************************************************************************************************************/

T_u4_RFDReturn
rfd_fu4_InitFACI(T_u2_FACI i_u2_TargetFACI)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function       */
    T_u4_RFDReturn  l_bu4_returnInternal;   /* Return value for calling function    */
    T_bl            l_bl1_errorFlag;        /* Error flag                           */
    
    /* Initialization of the local variables */
    l_bu4_returnValue    = R_RFD_OK;
    l_bu4_returnInternal = R_RFD_OK;
    l_bl1_errorFlag      = R_RFD_FALSE;
    
    
    /**********************************************************************************************
     *  Check whether the FACI has already been P/E mode.
     *  If the FACI is P/E mode, shift to the P/E mode to Read mode
     *  by issuing R_RFD_ForcedStopAndErrorClear
     *********************************************************************************************/
     
    /* Whether FACI0 data flash memory has already been check P/E mode   */
    /* At this point, R_RFD_CheckPEMode is not return "R_RFD_ERR_NOFACI" */
    l_bu4_returnInternal = R_RFD_CheckPEMode(i_u2_TargetFACI, R_RFD_MODE_READ);
    
    if (l_bu4_returnInternal == R_RFD_STS_BUSY)
    {
        /* Force stop */
        l_bu4_returnInternal = R_RFD_ForcedStopAndErrorClear(i_u2_TargetFACI);
        
        if (l_bu4_returnInternal == R_RFD_ERR_INTERNAL_HW)
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_ERR_INTERNAL_HW;
            l_bl1_errorFlag   = R_RFD_TRUE;
        }
        else
        {
            /* At this point, R_RFD_ForcedStopAndErrorClear is not return "R_RFD_ERR_NOFACI" */

            /* Shift to read mode */
            l_bu4_returnInternal = R_RFD_ShiftToReadMode(i_u2_TargetFACI);
            
            if (l_bu4_returnInternal == R_RFD_ERR_INTERNAL_HW)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_ERR_INTERNAL_HW;
                l_bl1_errorFlag   = R_RFD_TRUE;
            }
            else
            {
                /* no operation */
            }
        }
    } /* if (l_bu4_returnInternal == R_RFD_STS_BUSY) */
    
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE) /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Set the value for FAEINT register */
        R_RFD_REG_FAEINT = (T_u1)R_RFD_VALUE_FAEINT;    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
                                                        /* !CERT-C rule INT02 (QAC message 2100)      */
                
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    return(l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu4_ReleaseCommandLock (Internal Use only)
**  
**  - Outline
**      Releases the target FACI from the command-locked state
**  - Format
**      T_u4_RFDReturn
**          rfd_fu4_ReleaseCommandLock(
**              T_u2_FACI     i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI       : Target FACI to be released from the command-locked state
**  - Return
**      R_RFD_OK              : Normal End
**      R_RFD_ERR_INTERNAL_HW : Internal Hardware error
**      R_RFD_ERR_NOFACI      : Specified FACI is nonexistence
**  - Preconditions
**      The state of the flash memory must be the READY state
**  
**  - Traceability            : [Covers:UD_01_230]
**********************************************************************************************************************/

T_u4_RFDReturn
rfd_fu4_ReleaseCommandLock(T_u2_FACI i_u2_TargetFACI)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    T_u4            l_bu4_FSTATR;           /* FSTATR register value          */
    T_bl            l_bl1_errorFlag;        /* Error flag                     */
    
    /* Initialization of the local variables */
    l_bu4_returnValue   = R_RFD_OK;
    l_bu4_FSTATR        = 0U;
    l_bl1_errorFlag     = R_RFD_FALSE;
    
    
    /* Check the FACI number */
    l_bu4_returnValue = rfd_fu4_CheckFaciNumber(i_u2_TargetFACI);
    
    if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
    {
        /* Specified FACI is nonexistence (Set return value) */
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE) /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(i_u2_TargetFACI);

        /* Acquire the FSTATR register value */
        l_bu4_FSTATR = R_RFD_REG_FSTATR;        /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Check the FHVEERR bit of FSTATR register */
        if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_FHVEERR) != 0UL)
        {
            /* When the FHVEERR bit is valid (Set return value) */
            l_bu4_returnValue = R_RFD_ForcedStopAndErrorClear(i_u2_TargetFACI);
        }
        else
        {
            /* When the FHVEERR bit is invalid (Set return value) */
            l_bu4_returnValue = R_RFD_StatusClear(i_u2_TargetFACI);
        }
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fv0_Memcpy1ByteUnit
**  
**  - Outline
**      Copies data 1 byte each from the start address of the copy source to the start address of the copy destination
**      for the amount of the copy size.
**  - Format
**      void
**          fad_fv0_Memcpy1ByteUnit(
**              T_u1*      i_pu1_Destination,
**              T_u1*      i_pu1_Source,
**              T_u4       i_bu4_Size
**              );
**  - Input parameter
**      i_pu1_Destination  : Start address of copy destination
**      i_pu1_Source       : Start address of copy source
**      i_bu4_Size         : Copy size
**  - Return
**      non return value
**  - Preconditions
**      No preconditions
**  
**  - Traceability         : [Covers:UD_01_260]
**********************************************************************************************************************/

void
rfd_fv0_Memcpy1ByteUnit(T_u1* i_pu1_Destination, const T_u1* i_pu1_Source, T_u4 i_bu4_Size)
{
    /* Definition of the local variables */
    
    /* No local variables         */
    
    /* Initialization of the local variables */
    
    /* No local variables             */
    
    
    while (i_bu4_Size > 0UL)
    {
        /* Copy data 1-byte */
        *i_pu1_Destination = *i_pu1_Source;
        
        i_pu1_Destination++;    /* Increment destination address              */
                                /* !MISRA-C 2012 rule 17.8 (QAC message 1338) */
        i_pu1_Source++;         /* Increment source address                   */
                                /* !MISRA-C 2012 rule 17.8 (QAC message 1338) */
        i_bu4_Size--;           /* Decrement size                             */
                                /* !MISRA-C 2012 rule 17.8 (QAC message 1338) */
    }
}

/**************************************************************************************************************
 *  Section declaration
 *    - End of the definition of the text section for the Common Flash Control Component
 *************************************************************************************************************/

/* End of the definition of the text section */
#define  R_RFD_COMMON_STOP_SEC_CODE
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

/**************************************************************************************************************
 *  Section declaration
 *    - Start of the definition of the text section for the Common Flash Control Component
 *      (on RAM when No BGO condition)
 *
 *  - Traceability          : [Covers:UD_20_007]
 ***********************************************)**************************************************************/

/* Start of the definition of the text section */
#define  R_RFD_COMMON_RAM_NO_BGO_START_SEC_CODE
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

/**********************************************************************************************************************
**  Function Name   : R_RFD_CheckPEMode
**  
**  - Outline
**      Checks whether the mode of the code flash memory or data flash memory of the target FACI is the mode
**      specified by the second parameter
**  - Format
**      T_u4_RFDReturn
**          R_RFD_CheckPEMode(
**              T_u2_FACI       i_u2_TargetFACI,
**              T_en_FACIMode   i_en_FACIMode
**          );
**  - Input parameter
**      i_u2_TargetFACI     : Target FACI for which the mode of the flash memory is checked
**      i_en_FACIMode       : Mode to be checked (P/E mode or read mode). This API function checks whether the current
**                            mode of the flash memory is the mode specified by this parameter
**  - Return
**      R_RFD_OK            : Normal End
**      R_RFD_STS_BUSY      : FACI mode is not the mode specified by the second parameter
**      R_RFD_ERR_NOFACI    : Specified FACI is nonexistence
**  - Preconditions
**      The state of the flash memory must be the READY state
**  
**  - Traceability          : [Covers:UD_01_130]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_CheckPEMode(T_u2_FACI i_u2_TargetFACI, T_en_FACIMode i_en_FACIMode)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    T_u2            l_bu2_FENTRYR;          /* FENTRYR register value         */
    T_bl            l_bl1_errorFlag;        /* Error flag                     */
    
    /* Initialization of the local variables */
    l_bu4_returnValue    = R_RFD_OK;
    l_bu2_FENTRYR        = 0U;
    l_bl1_errorFlag      = R_RFD_FALSE;
    
    
    /* Check FACI number */
    l_bu4_returnValue = rfd_fu4_CheckFaciNumber(i_u2_TargetFACI);
    
    if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
    {
        /* Specified FACI is nonexistence */
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(i_u2_TargetFACI);
        
        /* Acquire the FENTRYR register */
        l_bu2_FENTRYR = R_RFD_REG_FENTRYR;          /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Mode is equal to the 2nd parameter */
        if (l_bu2_FENTRYR == (T_u2)i_en_FACIMode)   /* !CERT-C rule INT02 (QAC message 2101)      */
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_OK;
        }
        /* Mode is not equal to the 2nd parameter */
        else
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_STS_BUSY;
        }
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_ForcedStopAndErrorClear
**  
**  - Outline
**      Forcibly stops the operation on the target memory in the target FACI
**  - Format
**      T_u4_RFDReturn
**          R_RFD_ForcedStopAndErrorClear(
**              T_u2_FACI     i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI       : Target FACI whose operation is to be stopped forcibly
**  - Return
**      R_RFD_OK              : Normal End
**      R_RFD_ERR_INTERNAL_HW : Internal Hardware error
**      R_RFD_ERR_NOFACI      : Specified FACI is nonexistence
**  - Preconditions
**      The FACI mode must be the code flash P/E mode or data flash P/E mode
**  
**  - Traceability            : [Covers:UD_01_140]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_ForcedStopAndErrorClear(T_u2_FACI i_u2_TargetFACI)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function   */
    T_u4            l_u4_timeout;           /* Timeout value                    */
    T_u4            l_bu4_FSTATR;           /* FSTATR register value            */
    T_bl            l_bl1_errorFlag;        /* Error flag                       */
    volatile T_u1   l_bu1_dummyRead;        /* For dummy read                   */
                                            /* QAC message 3203                 */
    /* Initialization of the local variables */
    l_bu4_returnValue   = R_RFD_OK;
    l_u4_timeout        = R_RFD_VALUE_FORCED_STOP_TIMEOUT;  /* From r_rfd_config.h */
    l_bu4_FSTATR        = 0U;
    l_bl1_errorFlag     = R_RFD_FALSE;
    l_bu1_dummyRead     = 0U;
    
    
    /* Check FACI number */
    l_bu4_returnValue = rfd_fu4_CheckFaciNumber(i_u2_TargetFACI);
    
    if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
    {
        /* Specified FACI is nonexistence */
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(i_u2_TargetFACI);
        
        /* Read the command-issuing area to shift to the command lock state */
        l_bu1_dummyRead = R_RFD_CMD_ISSUING_AREA;           /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Issue the command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_FORCED_STOP;     /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Set return value */
        l_bu4_returnValue = R_RFD_ERR_INTERNAL_HW;
        
        /* Check until the FRDY bit of FSTATR register is valid */
        do
        {
            /* Read FSTATR register */
            l_bu4_FSTATR = R_RFD_REG_FSTATR;                /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            
            /* Check timeout */
            if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_FRDY) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_OK;
                break;
            }
            else
            {
                l_u4_timeout--;  /* Timeout count */
            }
        } while (l_u4_timeout > 0UL);
        
        /* Timeout */
        if (l_u4_timeout == 0UL)
        {
            /* Read the command-issuing area to shift to the command lock state (stop the sequencer process) */
            l_bu1_dummyRead = R_RFD_CMD_ISSUING_AREA;          /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
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
    
    return (l_bu4_returnValue);
    
}



/**********************************************************************************************************************
**  Function Name   : R_RFD_GetFaciSequenceReady
**  
**  - Outline
**      Checks whether the target FACI is in the READY state
**  - Format
**      T_u4_RFDReturn
**          R_RFD_GetFaciSequenceReady(
**              T_u2_FACI   i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI     : Target FACI to be checked whether its state is READY
**  - Return
**      R_RFD_STS_READY     : FRDY bit in the FSTATR_n register is valid
**      R_RFD_STS_BUSY      : FRDY bit in the FSTATR_n register is invalid
**      R_RFD_ERR_NOFACI    : Specified FACI is nonexistence
**  - Preconditions
**      No preconditions
**  
**  - Traceability          : [Covers:UD_01_160]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_GetFaciSequenceReady(T_u2_FACI i_u2_TargetFACI)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    T_u4            l_bu4_FSTATR;           /* FSTATR register value          */
    T_bl            l_bl1_errorFlag;        /* Error flag                     */
    
    /* Initialization of the local variables */
    l_bu4_returnValue   = R_RFD_OK;
    l_bu4_FSTATR        = 0U;
    l_bl1_errorFlag     = R_RFD_FALSE;
    
    
    /* Check FACI number */
    l_bu4_returnValue = rfd_fu4_CheckFaciNumber(i_u2_TargetFACI);
    
    if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
    {
        /* Specified FACI is nonexistence */
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(i_u2_TargetFACI);
        
        /* Acquire the value of FSTATR register */
        l_bu4_FSTATR = R_RFD_REG_FSTATR;            /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* FRDY bit of FSTATR register is valid */
        if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_FRDY) != 0UL)
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_STS_READY;
        }
        /* FRDY bit of FSTATR register is invalid */
        else
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_STS_BUSY;
        }
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_GetFaciStatus
**  
**  - Outline
**      Acquires the state of the target FACI
**  - Format
**      T_u4_RFDReturn
**          R_RFD_GetFaciStatus(
**              T_u2_FACI   i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI     : Target FACI whose state is to be acquired
**  - Return
**      R_RFD_OK                         : Normal End
**      R_RFD_ERR_ACCESS_ENV             : Illegal Access Error
**      R_RFD_ERR_BLOCKPROTECTION0_DATA  : Block Protection Area for FPSYS0 ECC 2-Bit Error
**      R_RFD_ERR_BLOCKPROTECTION1_DATA  : Block Protection Area for FPSYS1 ECC 2-Bit Error
**      R_RFD_ERR_CONFIGURATION_DATA     : Configuration Setting Area ECC 2-Bit Error
**      R_RFD_ERR_ERASE                  : Erase Error state
**      R_RFD_ERR_ERASECOUNTER_DATA      : Erase counter ECC 2-Bit Error
**      R_RFD_ERR_FHVE_PROTECT           : FHVE Protect Error
**      R_RFD_ERR_INTERNAL_DATA          : 2-Bit Error Detection (For Internal Data)
**      R_RFD_ERR_INTERNAL_HW            : Internal Hardware error
**      R_RFD_ERR_NOFACI                 : Specified FACI is nonexistence
**      R_RFD_ERR_SECURITY_DATA          : Security Setting Area ECC 2-Bit Error
**      R_RFD_ERR_SWITCH_DATA            : Switch Area ECC 2-Bit Error
**      R_RFD_ERR_WRITE                  : Write Error state
**      R_RFD_STS_ERASE_SUSPENDED        : Erasure Suspended state
**      R_RFD_STS_WRITE_SUSPENDED        : Programming Suspension state
**      R_RFD_WARN_BLOCKPROTECTION0_DATA : Block Protection Area for FPSYS0 ECC 1-Bit Error Correction
**      R_RFD_WARN_BLOCKPROTECTION1_DATA : Block Protection Area for FPSYS1 ECC 1-Bit Error Correction
**      R_RFD_WARN_CONFIGURATION_DATA    : Configuration Setting Area ECC 1-Bit Error Correction
**      R_RFD_WARN_ERASECOUNTER_DATA     : Erase counter ECC 1-Bit Error Correction
**      R_RFD_WARN_INTERNAL_DATA         : 1-Bit Error Correction (For Internal Data)
**      R_RFD_WARN_SECURITY_DATA         : Security Setting Area ECC 1-Bit Error Correction
**      R_RFD_WARN_SWITCH_DATA           : Switch Area ECC 1-Bit Error
**  - Preconditions
**      No preconditions
**  
**  - Traceability          : [Covers:UD_01_170]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_GetFaciStatus(T_u2_FACI i_u2_TargetFACI)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    T_u4            l_bu4_FSTATR;           /* FSTATR register value          */
    T_u1            l_bu1_FASTAT;           /* FASTAT register value          */
    T_bl            l_bl1_errorFlag;        /* Error flag                     */
    
    /* Initialization of the local variables */
    l_bu4_returnValue   = R_RFD_OK;
    l_bu4_FSTATR        = 0U;
    l_bu1_FASTAT        = 0U;
    l_bl1_errorFlag     = R_RFD_FALSE;
    
    
    /* Check FACI number */
    l_bu4_returnValue = rfd_fu4_CheckFaciNumber(i_u2_TargetFACI);
    
    if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
    {
        /* Specified FACI is nonexistence */
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(i_u2_TargetFACI);
        
        /* Acquire FASTAT register value */
        l_bu1_FASTAT = R_RFD_REG_FASTAT;    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Acquire FSTATR register value */
        l_bu4_FSTATR = R_RFD_REG_FSTATR;    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Command lock status is valid */
        if (((T_u1)l_bu1_FASTAT & (T_u1)R_RFD_MASK_FASTAT_CMDLK) != (T_u1)0x00U)
        {                                               /* !CERT-C rule INT02 (QAC message 2100) */
            /* Flash Write/Erase Protect Error (FHVERR) status is valid */
            if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_FHVEERR) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_ERR_FHVE_PROTECT;
            }
            /* 2-Bit Error Detection Monitor (P/E Parameter Table) (TBLDTCT) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_TBLDTCT) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_ERR_INTERNAL_DATA;
            }
            /* Security setting area ECC 2-Bit Error Detection Monitoring Bit (SECDTCT) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_SECDTCT) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_ERR_SECURITY_DATA;
            }
            /* Block Protection Area ECC 2-Bit Error Detection Monitoring Bit (BPLDTCT) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_BPLDTCT) != 0UL)
            {
                /* Target FACI is FACI0 */
                if (i_u2_TargetFACI == R_RFD_FACI0)         /* !CERT-C rule INT02 (QAC message 2101) */
                {
                    /* Set return value */
                    l_bu4_returnValue = R_RFD_ERR_BLOCKPROTECTION0_DATA;
                }
                else if (i_u2_TargetFACI == R_RFD_FACI1)    /* !CERT-C rule INT02 (QAC message 2101) */
                {
                    /* Set return value */
                    l_bu4_returnValue = R_RFD_ERR_BLOCKPROTECTION1_DATA;
                }
                else
                {
                    /* Set return value */
                    l_bu4_returnValue = R_RFD_ERR_INTERNAL_HW;
                }
            }
            /* Configuration Setting Area ECC 2-Bit Error Detection Monitoring Bit (CFGDTCT) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_CFGDTCT) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_ERR_CONFIGURATION_DATA;
            }
            /* Switch Area and TAG Area ECC 2-Bit Error Detection Monitoring Bit (SWTDTCT) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_SWTDTCT) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_ERR_SWITCH_DATA;
            }
            /* Erase counter ECC 2-Bit Error Detection Monitoring Bit (ERCDTCT) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_ERCDTCT) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_ERR_ERASECOUNTER_DATA;
            }
            /* Illegal Command Error status (ILGLERR) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_ILGLERR) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_ERR_ACCESS_ENV;
            }
            /* Erasure Error status (ERSERR) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_ERSERR) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_ERR_ERASE;
            }
            /* Programming Error status (PRGERR) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_PRGERR) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_ERR_WRITE;
            }
            /* Other error */
            else
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_ERR_INTERNAL_HW;
            }
            
        } /* if ((l_bu1_FASTAT & R_RFD_MASK_FASTAT_CMDLK) != 0U) */
        /* Command lock status is invalid */
        else
        {
            /* Switch Area and TAG Area ECC 1-Bit Error Detection Monitoring Bit (SWTCRCT) is valid */
            if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_SWTCRCT) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_WARN_SWITCH_DATA;
            }
            /* Security Setting Area ECC 1-Bit Error Correction Monitoring Bit (SECCRCT) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_SECCRCT) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_WARN_SECURITY_DATA;
            }
            /* Block Protection Area ECC 1-Bit Error Correction Monitoring Bit (BPLCRCT) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_BPLCRCT) != 0UL)
            {
                /* Target FACI is FACI0 */
                if (i_u2_TargetFACI == R_RFD_FACI0)         /* !CERT-C rule INT02 (QAC message 2101) */
                {
                    /* Set return value */
                    l_bu4_returnValue = R_RFD_WARN_BLOCKPROTECTION0_DATA;
                }
                else if (i_u2_TargetFACI == R_RFD_FACI1)    /* !CERT-C rule INT02 (QAC message 2101) */
                {
                    /* Set return value */
                    l_bu4_returnValue = R_RFD_WARN_BLOCKPROTECTION1_DATA;
                }
                else
                {
                    /* Set return value */
                    l_bu4_returnValue = R_RFD_ERR_INTERNAL_HW;
                }
            }
            /* Configuration Setting Area ECC 1-Bit Error Correction Monitoring Bit (CFGCRCT) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_CFGCRCT) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_WARN_CONFIGURATION_DATA;
            }
            /* Erase counter 1-Bit Error Correction Monitoring Bit (ERCCRCT) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_ERCCRCT) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_WARN_ERASECOUNTER_DATA;
            }
            /* 1-Bit Error Correction Monitor (TBLCRCT) is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_TBLCRCT) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_WARN_INTERNAL_DATA;
            }
            /* Erasure-Suspended status is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_ERSSPD) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_STS_ERASE_SUSPENDED;
            }
            /* Programming Suspension status is valid */
            else if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_PRGSPD) != 0UL)
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_STS_WRITE_SUSPENDED;
            }
            else
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_OK;
            }
        }
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_SuspendPERequest
**  
**  - Outline
**      Checks whether suspending the processing of the target FACI can be accepted
**  - Format
**      T_u4_RFDReturn
**          R_RFD_SuspendPERequest(
**              T_u2_FACI     i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI       : Target FACI whose processing is to be suspended
**  - Return
**      R_RFD_OK              : FRDY bit of the FSTATR_n register is valid at this point
**      R_RFD_STS_BUSY        : SUSRDY bit of the FSTATR_n register value is valid
**      R_RFD_ERR_REJECT      : SUSRDY bit of the FSTATR_n register value is invalid
**      R_RFD_ERR_NOFACI      : Specified FACI is nonexistence
**  - Preconditions
**      The FACI mode must be the code flash P/E mode or data flash P/E mode
**      The flash access status must not be the command-locked state
**  
**  - Traceability            : [Covers:UD_01_180]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_SuspendPERequest(T_u2_FACI i_u2_TargetFACI)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    T_u4            l_bu4_FSTATR;           /* FSTATR register value          */
    T_bl            l_bl1_errorFlag;        /* Error flag                     */
    
    /* Initialization of the local variables  */
    l_bu4_returnValue   = R_RFD_OK;
    l_bu4_FSTATR        = 0U;
    l_bl1_errorFlag     = R_RFD_FALSE;
    
    
    /* Check FACI number */
    l_bu4_returnValue = rfd_fu4_CheckFaciNumber(i_u2_TargetFACI);
    
    if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
    {
        /* Specified FACI is nonexistence */
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(i_u2_TargetFACI);
        
        /* Acquire the FSTATR register value */
        l_bu4_FSTATR = R_RFD_REG_FSTATR;                    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */

        /* Check the FRDY bit of FSTATR register */
        if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_FRDY) != 0UL)
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_OK;
        }
        else
        {
            /* Check the SUSRDY bit of FSTATR register */
            /* SUSRDY bit is valid */
            if ((l_bu4_FSTATR & R_RFD_MASK_FSTATR_SUSRDY) != 0UL)
            {
                R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_SUSPEND; /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
                /* Set return value */
                l_bu4_returnValue = R_RFD_STS_BUSY;
            }
            /* SUSRDY bit is invalid */
            else
            {
                /* Set return value */
                l_bu4_returnValue = R_RFD_ERR_REJECT;
            }
        }
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_ResumePERequest
**  
**  - Outline
**      Resumes the suspended processing of the target FACI
**  - Format
**      T_u4_RFDReturn
**          R_RFD_ResumePERequest(
**              T_u2_FACI   i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI     : Target FACI whose suspended processing is to be resumed
**  - Return
**      R_RFD_OK            : Normal End
**      R_RFD_ERR_NOFACI    : Specified FACI is nonexistence
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the code flash P/E mode or data flash P/E mode
**  
**  - Traceability          : [Covers:UD_01_190]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_ResumePERequest(T_u2_FACI i_u2_TargetFACI)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    T_bl            l_bl1_errorFlag;        /* Error flag                     */
    
    /* Initialization of the local variables */
    l_bu4_returnValue   = R_RFD_OK;
    l_bl1_errorFlag     = R_RFD_FALSE;
    
    
    /* Check FACI number */
    l_bu4_returnValue = rfd_fu4_CheckFaciNumber(i_u2_TargetFACI);
    
    if (l_bu4_returnValue == R_RFD_ERR_NOFACI)
    {
        /* Specified FACI is nonexistence */
        l_bl1_errorFlag = R_RFD_TRUE;
    }
    else
    {
        /* no operation */
    }
    
    if (l_bl1_errorFlag == R_RFD_FALSE)     /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(i_u2_TargetFACI);
        
        
        /* Issue the command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_RESUME;      /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Set return value */
        l_bu4_returnValue = R_RFD_OK;
        
    } /* if (l_bl1_errorFlag == R_RFD_FALSE) */
    else
    {
        /* no operation */
    }
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu4_CheckFaciNumber (Internal Use only)
**  
**  - Outline
**      Checks whether the FACI specified by the parameter exists
**  - Format
**      T_u4_RFDReturn
**          rfd_fu4_CheckFaciNumber(
**              T_u2_FACI   i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI     : FACI number whose existence is to be checked
**  - Return
**      R_RFD_OK            : Normal End
**      R_RFD_ERR_NOFACI    : Specified FACI is nonexistence
**  - Preconditions
**      No preconditions
**  
**  - Traceability          : [Covers:UD_01_240]
**********************************************************************************************************************/

T_u4_RFDReturn
rfd_fu4_CheckFaciNumber(T_u2_FACI i_u2_TargetFACI)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    
    /* Initialization of the local variables */
    l_bu4_returnValue   = R_RFD_OK;
    
    
    /* Parameter is FACI0? */
    if (i_u2_TargetFACI == R_RFD_FACI0)         /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* FACI0 is valid */
        if (R_RFD_VALID_FACI0  == R_RFD_TRUE)   /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_OK;
        }
        /* FACI0 is not valid */
        else
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_ERR_NOFACI;
        }
        
    } /* if (i_u2_TargetFACI == R_RFD_FACI0) */
    /* Parameter is FACI1? */
    else if (i_u2_TargetFACI == R_RFD_FACI1)    /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* FACI1 is valid */
        if (R_RFD_VALID_FACI1  == R_RFD_TRUE)   /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_OK;
        }
        /* FACI1 is not valid */
        else
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_ERR_NOFACI;
        }
        
    } /* else if (i_u2_TargetFACI == R_RFD_FACI1) */
    /* Parameter is FACI2? */
    else if (i_u2_TargetFACI == R_RFD_FACI2)    /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* FACI1 is valid */
        if (R_RFD_VALID_FACI2  == R_RFD_TRUE)   /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_OK;
        }
        /* FACI1 is not valid */
        else
        {
            /* Set return value */
            l_bu4_returnValue = R_RFD_ERR_NOFACI;
        }
        
    } /* else if (i_u2_TargetFACI == R_RFD_FACI2) */
    /* Parameter is not FACI0, FACI1 or FACI2 */
    else
    {
        /* Set return value */
        l_bu4_returnValue = R_RFD_ERR_NOFACI;
    }
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fv0_SetFaci (Internal Use only)
**  
**  - Outline
**      Switches the FACI base address and FACI command-issuing area to those of the FACI specified by the parameter
**  - Format
**      void
**          rfd_fv0_SetFaci(
**              T_u2_FACI     i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI       : FACI number to be switched
**  - Return
**      no return value
**  - Preconditions
**      No preconditions
**  
**  - Traceability            : [Covers:UD_01_250]
**********************************************************************************************************************/

void
rfd_fv0_SetFaci(T_u2_FACI i_u2_TargetFACI)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    
    /* No local variables         */
    
    /* Initialization of the local variables */
    
    /* No local variables             */
    
    
    /* Parameter is FACI0 */
    if (i_u2_TargetFACI == R_RFD_FACI0)         /* !CERT-C rule INT02 (QAC message 2101) */
    {
        bu4_CMN_FaciBaseAddress = R_RFD_BASE_FACI0;     /* Set FACI Base address         */
        bu4_CMN_FaciCommandArea = R_RFD_CMDAREA_FACI0;  /* Set FACI command area address */
    }
    /* Parameter is FACI1 */
    else if (i_u2_TargetFACI == R_RFD_FACI1)    /* !CERT-C rule INT02 (QAC message 2101) */
    {
        bu4_CMN_FaciBaseAddress = R_RFD_BASE_FACI1;     /* Set FACI Base address         */
        bu4_CMN_FaciCommandArea = R_RFD_CMDAREA_FACI1;  /* Set FACI command area address */
    }
    else if (i_u2_TargetFACI == R_RFD_FACI2)    /* !CERT-C rule INT02 (QAC message 2101) */
    {
        bu4_CMN_FaciBaseAddress = R_RFD_BASE_FACI2;     /* Set FACI Base address         */
        bu4_CMN_FaciCommandArea = R_RFD_CMDAREA_FACI2;  /* Set FACI command area address */
    }
    else
    {
        /* no operation */
    }
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fv0_SingleWrite
**  
**  - Outline
**      Writes the data to the code flash memory or data flash memory
**  - Format
**      void
**          rfd_fv0_SingleWrite(
**              T_u4_RfdAddress  i_u4_Start,
**              T_u2             i_u2_Length,
**              T_u4_RfdBuffer   i_pu4_Data
**          );
**  - Input parameter
**      i_u4_Start        : Start address of the programming area
**      i_u2_Length       : Length of the write data
**      i_pu4_Data        : Address of the buffer storing the write data
**  - Return
**      non return value
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the code flash P/E mode or data flash P/E mode
**      The second parameter must be 4 for programming the data flash memory and 512 for programming
**      the code flash memory
**  
**  - Traceability        : [Covers:UD_01_270]
**********************************************************************************************************************/

void
rfd_fv0_SingleWrite(T_u4_RfdAddress i_u4_Start, T_u2 i_u2_Length, T_pu4_RfdBuffer i_pu4_Data)
{
    /* !CERT-C rule DCL00 (QAC message 3227)      */
    /* !MISRA-C 2012 rule 8.13 (QAC message 3673) */
    
    /* Definition of the local variables */
    T_u1    l_bu1_writingCount;     /* Writing Count                */
    T_u4    l_bu4_loopCount;        /* Loop count for FOR statement */
    
    /* Initialization of the local variables  */
    l_bu1_writingCount = (T_u1)(i_u2_Length >> R_RFD_CONVERT_TO_WRITING_COUNT);
                                            /* !CERT-C rule INT02 (QAC message 2101) */
    l_bu4_loopCount     = 0U;
    
    
    /* Set start address */
    R_RFD_REG_FSADDR = i_u4_Start;                      /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Issue the writing command (single write) */
    R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_SINGLE_WRITE;    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Write the writing count (Value is always 1) */
    R_RFD_CMD_ISSUING_AREA = l_bu1_writingCount;        /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Write data 4 bytes at a time */
    for (l_bu4_loopCount = 0U; l_bu4_loopCount < (T_u4)l_bu1_writingCount; l_bu4_loopCount++)
    {
        R_RFD_CMD_ISSUING_AREA_4BYTE = *i_pu4_Data;     /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        i_pu4_Data++;                                   /* !MISRA-C 2012 rule 17.8 (QAC message 1338) */
    }
    
    /* Issue the run command */
    R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_RUN;             /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fv0_MultiWrite
**  
**  - Outline
**      Writes the data to the data flash memory
**  - Format
**      void
**          rfd_fv0_MultiWrite(
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
**      The value of the second parameter must be 8, 16, 32, 64, or 128
**  
**  - Traceability         : [Covers:UD_01_280]
**********************************************************************************************************************/

void
rfd_fv0_MultiWrite(T_u4_RfdAddress i_u4_Start, T_u2 i_u2_Length, T_pu4_RfdBuffer i_pu4_Data)
{
    /* !CERT-C rule DCL00 (QAC message 3227)      */
    /* !MISRA-C 2012 rule 8.13 (QAC message 3673) */
    
    /* Definition of the local variables */
    T_u1    l_bu1_writingCount;     /* Number of writes             */
    T_u4    l_bu4_loopCount;        /* loop count for FOR statement */
    
    /* Initialization of the local variables  */
    l_bu1_writingCount  = (T_u1)(i_u2_Length >> R_RFD_CONVERT_TO_WRITING_COUNT);
                                                        /* !CERT-C rule INT02 (QAC message 2101)     */
    l_bu4_loopCount = 0U;
    
    
    /* Set start address */
    R_RFD_REG_FSADDR = i_u4_Start;                      /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Issue the writing command (single write) */
    R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_MULTI_WRITE;     /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Write the writing count */
    R_RFD_CMD_ISSUING_AREA = l_bu1_writingCount;        /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Write data 4 bytes at a time */
    for (l_bu4_loopCount = 0U; l_bu4_loopCount < (T_u4)l_bu1_writingCount; l_bu4_loopCount++)
    {
        R_RFD_CMD_ISSUING_AREA_4BYTE = *i_pu4_Data;     /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        i_pu4_Data++;                                   /* !MISRA-C 2012 rule 17.8 (QAC message 1338) */
    }
    
    /* Issue the run command */
    R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_RUN;             /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fv0_SingleErase
**  
**  - Outline
**      Erases one sector of the code flash memory or data flash memory
**  - Format
**      void
**          rfd_fv0_SingleErase(
**              T_u4_RfdAddress  i_u4_Start
**          );
**  - Input parameter
**      i_u4_Start        : Start address of the erasure area
**  - Return
**      non return value
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the code flash P/E mode or data flash P/E mode
**  
**  - Traceability        : [Covers:UD_01_290]
**********************************************************************************************************************/

void
rfd_fv0_SingleErase(T_u4_RfdAddress i_u4_Start)
{
    /* !QAC(RCMA) message 1532               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    
    /* No local variables         */
    
    /* Initialization of the local variables */
    
    /* No local variables             */
    
    
    /* Set start address */
    R_RFD_REG_FSADDR = i_u4_Start;                  /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Issue the area erasure command */
    R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_BLOCK_ERASE; /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Issue the run command */
    R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_RUN;         /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fv0_MultiErase
**  
**  - Outline
**      Erases multiple sectors of the data flash memory
**  - Format
**      void
**          rfd_fv0_MultiErase(
**              T_u4_RfdAddress  i_u4_Start,
**              T_u4_RfdAddress  i_u4_End
**          );
**  - Input parameter
**      i_u4_Start         : Start address of the erasure area
**      i_u4_End           : End address of the erasure area
**  - Return
**      non return value
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the data flash P/E mode
**  
**  - Traceability         : [Covers:UD_01_300]
**********************************************************************************************************************/

void
rfd_fv0_MultiErase(T_u4_RfdAddress i_u4_Start, T_u4_RfdAddress i_u4_End)
{
    /* !QAC(RCMA) message 1532               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    
    /* No local variables         */
    
    /* Initialization of the local variables */
    
    /* No local variables             */
    
    
    /* Set start address */
    R_RFD_REG_FSADDR = i_u4_Start;                  /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Set end address */
    R_RFD_REG_FEADDR = i_u4_End;                    /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Issue the area erasure command */
    R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_AREA_ERASE;  /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Issue the run command */
    R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_RUN;         /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu1_ReadFSWASTAT
**  
**  - Outline
**      Reads the value of the FSWASTAT register and returns the value
**  - Format
**      T_u1
**          rfd_fu1_ReadFSWASTAT(
**              T_u2_FACI   i_u2_TargetFACI
**          );
**  - Input parameter
**      i_u2_TargetFACI     : FACI number currently being operated
**  - Return
**      Value of FSWASTAT register
**  - Preconditions
**      non preconditions
**
**  - Traceability         : [Covers:UD_01_310]
**********************************************************************************************************************/

T_u1
rfd_fu1_ReadFSWASTAT(T_u2_FACI i_u2_TargetFACI)
{
    /* !QAC(RCMA) message 1532               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u1    l_bu1_FSWASTAT;     /* FSWASTAT register value  */
    
    /* Initialization of the local variables */
    l_bu1_FSWASTAT = 0U;
    
    
    /* Switch the FACI base address to FACI0 */
    rfd_fv0_SetFaci(R_RFD_FACI0);
    
    /* Acquire the FSWASTAT register value */
    l_bu1_FSWASTAT = R_RFD_REG_FSWASTAT;        /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Switch the FACI base address to i_u2_TargetFACI */
    rfd_fv0_SetFaci(i_u2_TargetFACI);
    
    return(l_bu1_FSWASTAT);
    
}


/**************************************************************************************************************
 *  Section declaration
 *    - End of the definition of the text section for the Common Flash Control Component
 *      (on RAM when No BGO condition)
 *************************************************************************************************************/

/* End of the definition of the text section */
#define  R_RFD_COMMON_RAM_NO_BGO_STOP_SEC_CODE
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

