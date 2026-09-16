/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD28F)
    
    File Name       : r_rfd_df_api.c
    Program Version : V1.00
    File Revision   : $Rev: 4349 $
    File Date       : $Date:: 2023-05-19 15:15:27 +0700#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : API for Data Flash
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
 *   Rule         : MISRA-C 2012 rule 8.4 / QAC message 3408
 *   Message      : '%s' has external linkage and is being defined without any previous declaration.
 *   Reason       : The corresponding point is not declared for access from multiple components. 
 *                  This is "version information" to be placed in the const attribute area and is declared
 *                  so as to acquire it directly from the corresponding area.
 *   Verification : Incorrect declaration would result in compilation fails.
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
 *   Rule         : MISRA-C 2012 rule 11.3 / QAC message 0310
 *   Message      : Casting to different object pointer type.
 *   Reason       : It is necessary to operate 4-byte data allocated at the 4-byte alignment address and 4-byte data
 *                  allocated at the not 4-byte aligned equally. In the latter case, it must copy to 4-byte
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
 *   Rule         : MISRA-C 2012 rule 20.1 / QAC message 5087
 *   Message      : #include directives should only be preceded by preprocessor directives or comments.
 *   Reason       : This writing format is in accordance with the AUTOSAR Specification.
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
#include "r_rfd_common.h"       /* !CERT-C rule 5002 */
#include "r_rfd_common_local.h" /* !CERT-C rule 5002 */
#include "r_rfd_df.h"
#include "r_rfd_df_local.h"     /* !CERT-C rule 5002 */
#include "r_rfd_df_version.h"   /* !CERT-C rule 5002 */

/**************************************************************************************************************
 *  Possibility of operating the data flash memory by RFD28F
 *    - If the definition of "R_RFD_CONTROL_TARGET_DATAFLASH" is "R_RFD_DISABLE",
 *      the compiler output warning and no object is created by #warning directive.
 *************************************************************************************************************/

#if (R_RFD_CONTROL_TARGET_DATAFLASH == R_RFD_DISABLE)
    #warning "Data Flash Control Component is invalidated in r_rfd_config.h"
#else   /* R_RFD_CONTROL_TARGET_DATAFLASH == R_RFD_ENABLE */

/**************************************************************************************************************
 *  Version Information
 *    - Version of the Data Flash Control Component
 *  Declares the section
 *    - Definition of the const section
 *
 *  - Traceability          : [Covers:UD_40_001] [Covers:UD_40_002]
 *********************************************************************************************/

/* Start of the definition of the const section */
#define  R_RFD_VERSION_DF_START_SEC_CONST_UNSPECIFIED
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */
/* Alignment4 for the variables */
R_RFD_ALIGN_VARIABLE_4

/* Version of the Data Flash Control Component */
const   T_u1 pu1_versionDFComponent[] = R_RFD_VERSION_DF_COMPONENT;
                                /* !MISRA-C 2012 rule 8.4 (QAC message 3408)                      */
                                /* QAC(RCMA) message 1502                                         */
                                /* CERT-C rule ARR02-EX1                                          */
                                /* !CERT-C rule ARR02 (QAC message 3674) -> CERT-C rule ARR02-EX1 */

/* End of the definition of the const section */
#define  R_RFD_VERSION_DF_STOP_SEC_CONST_UNSPECIFIED
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

/**************************************************************************************************************
 *  Declares the section
 *    - Start of the definition of the text section for the Data Flash Control Component
 *
 *  - Traceability          : [Covers:UD_30_000]
 *************************************************************************************************************/

/* Start of the definition of the text section */
#define  R_RFD_DF_START_SEC_CODE
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

/**********************************************************************************************************************
**  Function Name   : R_RFD_DFIDAuth
**  
**  - Outline
**      Authenticates the data flash ID
**  - Format
**      T_u4_RFDReturn
**          R_RFD_DFIDAuth(
**              T_u1*     i_pu1_AuthIDData
**          );
**  - Input parameter
**      i_p_AuthIDData    : Pointer to the data flash ID data to be authenticated
**  - Return
**      R_RFD_OK          : Authentication succeeds
**      R_RFD_ERR_IDAUTH  : Authentication fails
**  - Preconditions
**      No preconditions
**  
**  - Traceability        : [Covers:UD_02_100]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_DFIDAuth(T_u1* i_pu1_AuthIDData)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function               */
    T_u4*           l_pu4_authIDData;       /* Authentication Data                          */
    volatile T_u4*  l_pu4_DFIDIN;           /* Local variables for DFIDIN                   */
    T_u4            l_bu4_loopCount;        /* loop count for FOR statement                 */
    T_u4            l_bu4_IDStatus;         /* Data-Flash ID authentication status register */
    volatile T_u4   l_bu4_dummyRead;        /* For dummy read                               */
                                            /* QAC message 3203                             */
    T_u4            l_bu4_work[R_RFD_LENGTH_DFID/R_RFD_LENGTH_UNIT_DFID];   /* Working area */
    
    /* Initialization of the local variables */
    l_bu4_returnValue = R_RFD_OK;
    l_pu4_DFIDIN      = (T_u4 *)R_RFD_REG_DFIDIN_TOP_ADDRESS;   /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
    l_bu4_loopCount   = 0U;
    l_bu4_IDStatus    = 0U;
    l_bu4_dummyRead   = 0U;
    
    
    /* Check the alignment of AuthIDData */
    /* On 4-bytes alignment */
    if (((T_u4)i_pu1_AuthIDData & R_RFD_CHECK_ALIGN4) == 0UL)   /* !MISRA-C 2012 rule 11.4 (QAC message 0306) */
    {
        l_pu4_authIDData = (T_u4 *)i_pu1_AuthIDData;            /* !MISRA-C 2012 rule 11.3 (QAC message 0310) */
                                                                /* !MISRA-C 2012 rule 11.3 (QAC message 3305) */
    }
    /* Not on 4-bytes alignment */
    else
    {
        rfd_fv0_Memcpy1ByteUnit((T_u1 *)&l_bu4_work[0], i_pu1_AuthIDData,
                                                            (T_u4)R_RFD_LENGTH_DFID/(T_u4)R_RFD_LENGTH_BYTE1);
                                                                /* !QAC message 0751 */
        l_pu4_authIDData = (T_u4 *)&l_bu4_work[0];
    }
    
    /* Write to DFIDINx register the AuthIDData */
    for (l_bu4_loopCount = 0U; l_bu4_loopCount < (R_RFD_LENGTH_DFID/R_RFD_LENGTH_UNIT_DFID); l_bu4_loopCount++)
    {
        *l_pu4_DFIDIN = *l_pu4_authIDData;
        l_pu4_DFIDIN++;
        l_pu4_authIDData++;
    }
    
    /* Dummy read the R_RFD_REG_DFIDIN7 */
    l_bu4_dummyRead = R_RFD_REG_DFIDIN7;        /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Acquire the value of IDST(ID Authentication Status Register) */
    l_bu4_IDStatus = R_RFD_REG_IDST;            /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
    
    /* Check the Data-Flash ID Authentication Status */
    /* The IDs match (protection unlocked) */
    if ((l_bu4_IDStatus & (T_u4)R_RFD_IDST_DFIDR) == 0UL)
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
    
    return (l_bu4_returnValue);
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_EraseDFRequest
**  
**  - Outline
**      Erases the contents of the data flash memory
**  - Format
**      void
**          R_RFD_EraseDFRequest(
**              T_u4_RfdAddress  i_u4_Start,
**              T_u4_RfdAddress  i_u4_End
**          );
**  - Input parameter
**      i_u4_Start        : Start address of the erasure area
**      i_u4_End          : End address of the erasure area
**  - Return
**      non return value
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the data flash P/E mode
**  
**  - Traceability        : [Covers:UD_02_110]
**********************************************************************************************************************/

void
R_RFD_EraseDFRequest(T_u4_RfdAddress i_u4_Start, T_u4_RfdAddress i_u4_End)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci    = 0U;
    
    
    /* Acquire FACI number */
    l_bu2_targetFaci = R_RFD_DFAddressToFaciNumber(i_u4_Start);
    
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
        
        /* Area erasure */
        rfd_fv0_MultiErase(i_u4_Start, i_u4_End);
        
    } /* if (l_bu2_targetFaci != R_RFD_INVALID_FACI) */
    
    else
    {
        /* no operation */
    }
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_WriteDFRequest
**  
**  - Outline
**      Writes the data to the data flash memory
**  - Format
**      void
**          R_RFD_WriteDFRequest(
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
**  - Traceability         : [Covers:UD_02_120]
**********************************************************************************************************************/

void
R_RFD_WriteDFRequest(T_u4_RfdAddress i_u4_Start, T_u2 i_u2_Length, T_pu4_RfdBuffer i_pu4_Data)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = 0U;
    
    
    /* Acquire FACI number */
    l_bu2_targetFaci = R_RFD_DFAddressToFaciNumber(i_u4_Start);
    
    if (l_bu2_targetFaci != R_RFD_INVALID_FACI)     /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(l_bu2_targetFaci);
        
        
        /* Data for writing length (2nd parameter) */
        /* Writing length is 4-bytes */
        if (i_u2_Length == R_RFD_LENGTH_DATA_4BYTES)        /* !CERT-C rule INT02 (QAC message 2101) */
        {
            rfd_fv0_SingleWrite(i_u4_Start, i_u2_Length, i_pu4_Data);
        }
        /* Writing length is 8 bytes */
        else if (i_u2_Length == R_RFD_LENGTH_DATA_8BYTES)   /* !CERT-C rule INT02 (QAC message 2101) */
        {
            rfd_fv0_MultiWrite(i_u4_Start, i_u2_Length, i_pu4_Data);
        }
        /* Writing length is 16 bytes */
        else if (i_u2_Length == R_RFD_LENGTH_DATA_16BYTES)  /* !CERT-C rule INT02 (QAC message 2101) */
        {
            rfd_fv0_MultiWrite(i_u4_Start, i_u2_Length, i_pu4_Data);
        }
        /* Writing length is 32bytes */
        else if (i_u2_Length == R_RFD_LENGTH_DATA_32BYTES)  /* !CERT-C rule INT02 (QAC message 2101) */
        {
            rfd_fv0_MultiWrite(i_u4_Start, i_u2_Length, i_pu4_Data);
        }
        /* Writing length is 64bytes */
        else if (i_u2_Length == R_RFD_LENGTH_DATA_64BYTES)  /* !CERT-C rule INT02 (QAC message 2101) */
        {
            rfd_fv0_MultiWrite(i_u4_Start, i_u2_Length, i_pu4_Data);
        }
        /* Writing length is 128bytes */
        else if (i_u2_Length == R_RFD_LENGTH_DATA_128BYTES) /* !CERT-C rule INT02 (QAC message 2101) */
        {
            rfd_fv0_MultiWrite(i_u4_Start, i_u2_Length, i_pu4_Data);
        }
        else
        {
            /* no operation */
        }
        
    } /* if (l_bu2_targetFaci != R_RFD_INVALID_FACI) */
    
    else
    {
        /* no operation */
    }
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_BlankCheckDFRequest
**  
**  - Outline
**      Checks whether there is blank in the data flash memory
**  - Format
**      void
**          R_RFD_BlankCheckDFRequest(
**              T_u4_RfdAddress  i_u4_Start,
**              T_u4_RfdAddress  i_u4_End
**          );
**  - Input parameter
**      i_u4_Start         : Start address to check for blank
**      i_u4_End           : End address to check for blank
**  - Return
**      non return value
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      The FACI mode must be the data flash P/E mode
**  
**  - Traceability         : [Covers:UD_02_130]
**********************************************************************************************************************/

void
R_RFD_BlankCheckDFRequest(T_u4_RfdAddress i_u4_Start, T_u4_RfdAddress i_u4_End)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci    = 0U;
    
    
    /* Acquire FACI number */
    l_bu2_targetFaci = R_RFD_DFAddressToFaciNumber(i_u4_Start);
    
    if (l_bu2_targetFaci != R_RFD_INVALID_FACI)     /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* Switch the FACI base address and FACI command issue area */
        rfd_fv0_SetFaci(l_bu2_targetFaci);
        
        
        /* Data Flash Blank Check Control = Incremental mode */
        R_RFD_REG_FBCCNT = R_RFD_VALUE_FBCCNT_INC_MODE;         /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Set start address */
        R_RFD_REG_FSADDR = i_u4_Start;                          /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Set end address */
        R_RFD_REG_FEADDR = i_u4_End;                            /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Issue the erasure command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_BLANK_CHECK;         /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Issue the run command */
        R_RFD_CMD_ISSUING_AREA = R_RFD_CMD_RUN;                 /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
    } /* if (l_bu2_targetFaci != R_RFD_INVALID_FACI) */
    
    else
    {
        /* no operation */
    }
    
    return;
    
}

/**********************************************************************************************************************
**  Function Name   : R_RFD_GetBlankCheckResult
**  
**  - Outline
**      Acquires the result of blank checking of the data flash memory that was performed immediately before this
**      API function
**  - Format
**      void
**          R_RFD_GetBlankCheckResult(
**              T_u2_FACI           i_u2_TargetFaci,
**              T_u4_RfdAddress*    o_pu4_NotBlankAddress
**          );
**  - Input parameter
**      i_u2_TargetFaci     : Target FACI whose data flash memory is checked for blank
**      o_p_NotBlankAddress : Pointer for storing the address of the programmed data flash memory that was found first
**  - Return
**      R_RFD_OK            : Normal End
**      R_RFD_STS_NOTBLANK  : The FACI command executed just before is not "Blank Checking Command"
**      R_RFD_ERR_NOFACI    : Specified FACI is nonexistence
**  - Preconditions
**      The state of the flash memory must be the READY state
**      The flash access status must not be the command-locked state
**      Blank checking of the data flash memory must be performed immediately before this API function
**  
**  - Traceability          : [Covers:UD_02_140]
**********************************************************************************************************************/

T_u4_RFDReturn
R_RFD_GetBlankCheckResult(T_u2_FACI i_u2_TargetFaci, T_u4_RfdAddress* o_pu4_NotBlankAddress)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u4_RFDReturn  l_bu4_returnValue;      /* Return value for this function */
    T_u2            l_bu2_FCMDR;            /* FCMDR register value           */
    T_u1            l_bu1_FBCSTAT;          /* FBCSTAT register value         */
    T_u4            l_bu4_FPSADDR;          /* FPSADDR register value         */
    T_bl            l_bl1_errorFlag;        /* Error flag                     */
    
    /* Initialization of the local variables  */
    l_bu4_returnValue   = R_RFD_OK;
    l_bu2_FCMDR         = 0U;
    l_bu1_FBCSTAT       = 0U;
    l_bu4_FPSADDR       = 0U;
    l_bl1_errorFlag     = R_RFD_FALSE;
    
    
    /* Check FACI number */
    l_bu4_returnValue = rfd_fu4_CheckFaciNumber(i_u2_TargetFaci);
    
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
        rfd_fv0_SetFaci(i_u2_TargetFaci);
        
        /* Acquire FCMDR register value */
        l_bu2_FCMDR = R_RFD_REG_FCMDR;              /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
        
        /* Check previous FACI command */
        if (l_bu2_FCMDR != R_RFD_VALUE_FCMDR_BLANK_CHECKING)    /* !CERT-C rule INT02 (QAC message 2101) */
        {
        }
        else
        {
            /* Acquire FBCSTAT register value */
            l_bu1_FBCSTAT = R_RFD_REG_FBCSTAT;      /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
            
            /* Target area is not written (no writing after erasing) */
            if (l_bu1_FBCSTAT == R_RFD_VALUE_FBCSTAT_BLANK)     /* !CERT-C rule INT02 (QAC message 2100) */
            {
                /* Set zero to the 2nd parameter */
                *o_pu4_NotBlankAddress = 0x0U;
                /* Set return value */
                l_bu4_returnValue = R_RFD_OK;
            }
            /* Target area is filled */
            else
            {
                l_bu4_FPSADDR = R_RFD_REG_FPSADDR;  /* !MISRA-C 2012 rule 11.4 (QAC message 0303) */
                /* Set the value that obtained by ORing the value of the FPSADDR register and       */
                /* R_RFD_MAKE_PHYSICAL_ADDRESS_DF to the 2nd parameter (Change to Physical address) */
                *o_pu4_NotBlankAddress = (l_bu4_FPSADDR | R_RFD_PHYSICAL_BASE_ADDRESS_DF);
                /* Set return value */
                l_bu4_returnValue = R_RFD_STS_NOTBLANK;
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
**  Function Name   : R_RFD_DFAddressToFaciNumber
**  
**  - Outline
**      Acquires the FACI number of the specified data flash memory address
**  - Format
**      T_u2_Faci
**          R_RFD_DFAddressToFaciNumber(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the data flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI0         : Target is FACI0
**      R_RFD_FACI1         : Target is FACI1
**      R_RFD_FACI2         : Target is FACI2
**      R_RFD_INVALID_FACI  : Target is invalid FACI
**  - Preconditions
**      No preconditions
**  
**  - Traceability          : [Covers:UD_02_150]
**********************************************************************************************************************/

T_u2_FACI
R_RFD_DFAddressToFaciNumber(T_u4_RfdAddress i_u4_Address)
{
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* FACI0 is Valid */
    if (R_RFD_VALID_FACI0 == R_RFD_TRUE)        /* !CERT-C rule INT02 (QAC message 2100) */
    {
        /* FACI0 is Valid / FACI1 is Valid */
        if (R_RFD_VALID_FACI1 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* FACI0 is Valid / FACI1 is Valid / FACI2 is Valid */
            if (R_RFD_VALID_FACI2 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
            {
                l_bu2_targetFaci = rfd_fu2_CheckDFFaci0Faci1Faci2(i_u4_Address);
            }
            /* FACI0 is Valid / FACI1 is Valid / FACI2 is Invalid */
            else
            {
                l_bu2_targetFaci = rfd_fu2_CheckDFFaci0Faci1(i_u4_Address);
            }
            
        } /* if (R_RFD_VALID_FACI1 == R_RFD_TRUE) */
        
        /* FACI0 is Valid / FACI1 is Invalid */
        else
        {
            /* FACI0 is Valid / FACI1 is Invalid / FACI2 is Valid */
            if (R_RFD_VALID_FACI2 == R_RFD_TRUE)
            {
                l_bu2_targetFaci = rfd_fu2_CheckDFFaci0Faci2(i_u4_Address);
            }
            /* FACI0 is Valid / FACI1 is Invalid / FACI2 is Invalid */
            else
            {
                l_bu2_targetFaci = rfd_fu2_CheckDFFaci0(i_u4_Address);
            }
        }
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
                l_bu2_targetFaci = rfd_fu2_CheckDFFaci1Faci2(i_u4_Address);
            }
            /* FACI0 is Invalid / FACI1 is Valid / FACI2 is Invalid */
            else
            {
                l_bu2_targetFaci = rfd_fu2_CheckDFFaci1(i_u4_Address);
            }
            
        } /* if (R_RFD_VALID_FACI1 == R_RFD_TRUE) */
        
        /* FACI0 is Invalid / FACI1 is Invalid */
        else
        {
            /* FACI0 is Invalid / FACI1 is Invalid / FACI2 is Valid */
            if (R_RFD_VALID_FACI2 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
            {
                l_bu2_targetFaci = rfd_fu2_CheckDFFaci2(i_u4_Address);
            }
            /* FACI0 is Invalid / FACI1 is Invalid / FACI2 is Invalid */
            else
            {
                l_bu2_targetFaci = R_RFD_INVALID_FACI;
            }
            
        } /* else */
        
    } /* else */
    
    return (l_bu2_targetFaci);
    
}


/**********************************************************************************************************************
**  Function Name   : rfd_fu2_CheckDFFaci0Faci1Faci2
**  
**  - Outline
**      Checks whether the specified address of the data flash memory is for FACI0, FACI1, or FACI2
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckDFFaci0Faci1Faci2(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the data flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI0         : Target is FACI0
**      R_RFD_FACI1         : Target is FACI1
**      R_RFD_FACI2         : Target is FACI2
**      R_RFD_INVALID_FACI  : Target is not FACI0 or FACI1 or FACI2
**  - Preconditions
**      The definitions of FACI0, FACI1, and FACI2 are valid
**      (R_RFD_VALID_FACI0, R_RFD_VALID_FACI1, and R_RFD_VALID_FACI2 are R_RFD_TRUE)
**  
**  - Traceability          : [Covers:UD_02_160]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckDFFaci0Faci1Faci2(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* Check whether the i_u4_Address is included in FACI0 */
    l_bu2_targetFaci = rfd_fu2_CheckDFFaci0(i_u4_Address);
    
    if (l_bu2_targetFaci != (T_u2_FACI)R_RFD_FACI0)     /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* Check whether the i_u4_Address is included in FACI1 */
        l_bu2_targetFaci = rfd_fu2_CheckDFFaci1(i_u4_Address);
        
        if (l_bu2_targetFaci != R_RFD_FACI1)    /* !CERT-C rule INT02 (QAC message 2101) */
        {
            /* Check whether the i_u4_Address is included in FACI2 */
            l_bu2_targetFaci = rfd_fu2_CheckDFFaci2(i_u4_Address);
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
**  Function Name   : rfd_fu2_CheckDFFaci0Faci1
**  
**  - Outline
**      Checks whether the specified address of the data flash memory is for FACI0 or FACI1
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckDFFaci0Faci1(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the data flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI0         : Target is FACI0
**      R_RFD_FACI1         : Target is FACI1
**      R_RFD_INVALID_FACI  : Target is not FACI0 or FACI1
**  - Preconditions
**      - The definitions of FACI0 and FACI1 are valid (R_RFD_VALID_FACI0 and R_RFD_VALID_FACI1 are R_RFD_TRUE)
**      - The definition of FACI2 is invalid (R_RFD_VALID_FACI2 is R_RFD_FALSE)
**  
**  - Traceability          : [Covers:UD_02_170]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckDFFaci0Faci1(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* Check whether the i_u4_Address is included in FACI0 */
    l_bu2_targetFaci = rfd_fu2_CheckDFFaci0(i_u4_Address);
    
    if (l_bu2_targetFaci != R_RFD_FACI0)    /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* Check whether the i_u4_Address is included in FACI1 */
        l_bu2_targetFaci = rfd_fu2_CheckDFFaci1(i_u4_Address);
    }
    else
    {
        /* no operation */
    }
    
    return (l_bu2_targetFaci);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu2_CheckDFFaci0Faci2
**  
**  - Outline
**      Checks whether the specified address of the data flash memory is for FACI0 or FACI2
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckDFFaci0Faci2(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the data flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI0         : Target is FACI0
**      R_RFD_FACI2         : Target is FACI2
**      R_RFD_INVALID_FACI  : Target is not FACI0 or FACI2
**  - Preconditions
**      - The definitions of FACI0 and FACI2 are valid (R_RFD_VALID_FACI0 and R_RFD_VALID_FACI2 are R_RFD_TRUE)
**      - The definition of FACI1 is invalid (R_RFD_VALID_FACI1 is R_RFD_FALSE)
**  
**  - Traceability          : [Covers:UD_02_180]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckDFFaci0Faci2(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* Check whether the i_u4_Address is included in FACI0 */
    l_bu2_targetFaci = rfd_fu2_CheckDFFaci0(i_u4_Address);
    
    if (l_bu2_targetFaci != R_RFD_FACI0)    /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* Check whether the i_u4_Address is included in FACI2 */
        l_bu2_targetFaci = rfd_fu2_CheckDFFaci2(i_u4_Address);
    }
    else
    {
        /* no operation */
    }
    
    return (l_bu2_targetFaci);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu2_CheckDFFaci1Faci2
**  
**  - Outline
**      Checks whether the specified address of the data flash memory is for FACI1 or FACI2
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckDFFaci1Faci2(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the data flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI1         : Target is FACI1
**      R_RFD_FACI2         : Target is FACI2
**      R_RFD_INVALID_FACI  : Target is not FACI1 or FACI2
**  - Preconditions
**      - The definitions of FACI1 and FACI2 are valid (R_RFD_VALID_FACI1 and R_RFD_VALID_FACI2 are R_RFD_TRUE)
**      - The definition of FACI0 is invalid (R_RFD_VALID_FACI0 is R_RFD_FALSE)
**  
**  - Traceability          : [Covers:UD_02_190]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckDFFaci1Faci2(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* Check whether the i_u4_Address is included in FACI1 */
    l_bu2_targetFaci = rfd_fu2_CheckDFFaci1(i_u4_Address);
    
    if (l_bu2_targetFaci != R_RFD_FACI1)    /* !CERT-C rule INT02 (QAC message 2101) */
    {
        /* Check whether the i_u4_Address is included in FACI2 */
        l_bu2_targetFaci = rfd_fu2_CheckDFFaci2(i_u4_Address);
    }
    else
    {
        /* no operation */
    }
    
    return (l_bu2_targetFaci);
    
}


/**********************************************************************************************************************
**  Function Name   : rfd_fu2_CheckDFFaci0
**  
**  - Outline
**      Checks whether the specified address of the data flash memory is for FACI0
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckDFFaci0(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the data flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI0         : Target is FACI0
**      R_RFD_INVALID_FACI  : Target is not FACI0
**  - Preconditions
**      The definition of FACI0 is valid (R_RFD_VALID_FACI0 is R_RFD_TRUE)
**  
**  - Traceability          : [Covers:UD_02_200]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckDFFaci0(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* If FACI0 is defined */
    if (R_RFD_DF_BASE_FACI0 != R_RFD_NO_DEFINITION)
    {
        /* Determine end address to check */
        if (R_RFD_VALID_FACI1 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* If FACI1 is defined */
            if (R_RFD_DF_BASE_FACI1 != R_RFD_NO_DEFINITION)
            {
                /* Check whether the address is within FACI0 */
                if ((i_u4_Address >= R_RFD_DF_BASE_FACI0)
                     &&(i_u4_Address < R_RFD_DF_BASE_FACI1))
                {
                    /* The address is within FACI0 */
                    l_bu2_targetFaci = R_RFD_FACI0;
                }
                else
                {
                    /* The address is not within FACI0 */
                    l_bu2_targetFaci = R_RFD_INVALID_FACI;
                }
            } /* if (R_RFD_DF_BASE_FACI1 != R_RFD_NO_DEFINITION) */
            
            /* If FACI1 is not defined */
            else    /* R_RFD_DF_BASE_FACI1 == R_RFD_NO_DEFINITION */
            {
                /* If FACI2 is valid */
                if (R_RFD_VALID_FACI2 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
                {
                    /* If FACI2 is defined */
                    if (R_RFD_DF_BASE_FACI2 != R_RFD_NO_DEFINITION)
                    {
                        /* Check whether the address is within FACI0 */
                        if ((i_u4_Address >= R_RFD_DF_BASE_FACI0)
                             &&(i_u4_Address < R_RFD_DF_BASE_FACI2))
                        {
                            /* The address is within FACI0 */
                            l_bu2_targetFaci = R_RFD_FACI0;
                        }
                        else
                        {
                            /* The address is not within FACI0 */
                            l_bu2_targetFaci = R_RFD_INVALID_FACI;
                        }
                    } /* if (R_RFD_DF_BASE_FACI2 != R_RFD_NO_DEFINITION) */
                    
                    /* If FACI2 is not defined */
                    else
                    {
                        /* Check whether the address is within FACI0 */
                        if ((i_u4_Address >= R_RFD_DF_BASE_FACI0)
                             &&(i_u4_Address <= R_RFD_DF_END))
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
                    if ((i_u4_Address >= R_RFD_DF_BASE_FACI0)
                         &&(i_u4_Address <= R_RFD_DF_END))
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
            }
        } /* if (R_RFD_VALID_FACI1 == R_RFD_TRUE) */
        
        else if (R_RFD_VALID_FACI2 == R_RFD_TRUE)   /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* If FACI2 is defined */
            if (R_RFD_DF_BASE_FACI2 != R_RFD_NO_DEFINITION)
            {
                /* Check whether the address is within FACI0 */
                if ((i_u4_Address >= R_RFD_DF_BASE_FACI0)
                     &&(i_u4_Address < R_RFD_DF_BASE_FACI2))
                {
                    /* The address is within FACI0 */
                    l_bu2_targetFaci = R_RFD_FACI0;
                }
                else
                {
                    /* The address is not within FACI0 */
                    l_bu2_targetFaci = R_RFD_INVALID_FACI;
                }
            } /* if (R_RFD_DF_BASE_FACI2 != R_RFD_NO_DEFINITION) */
            
            else
            {
                /* Check whether the address is within FACI0 */
                if ((i_u4_Address >= R_RFD_DF_BASE_FACI0)
                     &&(i_u4_Address <= R_RFD_DF_END))
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
            if ((i_u4_Address >= R_RFD_DF_BASE_FACI0)
                 &&(i_u4_Address <= R_RFD_DF_END))
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
        
    } /* if (R_RFD_DF_BASE_FACI0 != R_RFD_NO_DEFINITION) */
    
    /* If FACI0 is not defined (R_RFD_DF_BASE_FACI0 == R_RFD_NO_DEFINITION) */
    else
    {
        /* FACI0 is not available */
        l_bu2_targetFaci = R_RFD_INVALID_FACI;
    }
    
    return (l_bu2_targetFaci);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu2_CheckDFFaci1
**  
**  - Outline
**      Checks whether the specified address of the data flash memory is for FACI1
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckDFFaci1(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the data flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI1         : Target is FACI1
**      R_RFD_INVALID_FACI  : Target is not FACI1
**  - Preconditions
**      The definition of FACI1 is valid (R_RFD_VALID_FACI1 is R_RFD_TRUE).
**  
**  - Traceability          : [Covers:UD_02_210]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckDFFaci1(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* If FACI1 is defined */
    if (R_RFD_DF_BASE_FACI1 != R_RFD_NO_DEFINITION)
    {
        /* Determine end address to check */
        if (R_RFD_VALID_FACI2 == R_RFD_TRUE)    /* !CERT-C rule INT02 (QAC message 2100) */
        {
            /* If FACI2 is defined */
            if (R_RFD_DF_BASE_FACI2 != R_RFD_NO_DEFINITION)
            {
                /* Check whether the address is within FACI1 */
                if ((i_u4_Address >= R_RFD_DF_BASE_FACI1)
                     &&(i_u4_Address < R_RFD_DF_BASE_FACI2))
                {
                    /* The address is within FACI1 */
                    l_bu2_targetFaci = R_RFD_FACI1;
                }
                else
                {
                    /* The address is not within FACI1 */
                    l_bu2_targetFaci = R_RFD_INVALID_FACI;
                }
            } /* if (R_RFD_DF_BASE_FACI2 != R_RFD_NO_DEFINITION) */
            
            /* If FACI2 is NOT defined */
            else
            {
                /* Check whether the address is within FACI1 */
                if ((i_u4_Address >= R_RFD_DF_BASE_FACI1)
                     &&(i_u4_Address <= R_RFD_DF_END))
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
            
        } /* if (R_RFD_VALID_FACI2 == R_RFD_TRUE) */
        
        /* R_RFD_VALID_FACI2 == R_RFD_TRUE */
        else
        {
            /* Check whether the address is within FACI1 */
            if ((i_u4_Address >= R_RFD_DF_BASE_FACI1)
                 &&(i_u4_Address <= R_RFD_DF_END))
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
        
    } /* if (R_RFD_DF_BASE_FACI1 != R_RFD_NO_DEFINITION) */
    
    /* If FACI1 not defined (R_RFD_DF_BASE_FACI1 == R_RFD_NO_DEFINITION) */
    else
    {
        /* FACI1 is not available */
        l_bu2_targetFaci = R_RFD_INVALID_FACI;
    }
    
    return (l_bu2_targetFaci);
    
}

/**********************************************************************************************************************
**  Function Name   : rfd_fu2_CheckDFFaci2
**  
**  - Outline
**      Checks whether the specified address of the data flash memory is for FACI2
**  - Format
**      T_u2_Faci
**          rfd_fu2_CheckDFFaci2(
**              T_u4_RfdAddress  i_u4_Address
**          );
**  - Input parameter
**      i_u4_Address        : Address of the data flash memory whose FACI number is to be acquired
**  - Return
**      R_RFD_FACI2         : Target is FACI2
**      R_RFD_INVALID_FACI  : Target is not FACI2
**  - Preconditions
**      The definition of FACI2 is valid (R_RFD_VALID_FACI2 is R_RFD_TRUE)
**  
**  - Traceability          : [Covers:UD_02_220]
**********************************************************************************************************************/

T_u2_FACI
rfd_fu2_CheckDFFaci2(T_u4_RfdAddress i_u4_Address)
{
    /* !QAC(RCMA) message 1505               */
    /* !CERT-C rule DCL00 (QAC message 3227) */
    
    /* Definition of the local variables */
    T_u2_FACI       l_bu2_targetFaci;   /* Target FACI  */
    
    /* Initialization of the local variables  */
    l_bu2_targetFaci = R_RFD_INVALID_FACI;
    
    
    /* If FACI2 is defined */
    if (R_RFD_DF_BASE_FACI2 != R_RFD_NO_DEFINITION)
    {
        /* Check whether the address is within FACI2 */
        if ((i_u4_Address >= R_RFD_DF_BASE_FACI2)
             &&(i_u4_Address <= R_RFD_DF_END))
        {
            /* The address is within FACI2 */
            l_bu2_targetFaci = R_RFD_FACI2;
        }
        else
        {
            /* The address is not within FACI2 */
            l_bu2_targetFaci = R_RFD_INVALID_FACI;
        }
        
    } /* if (R_RFD_DF_BASE_FACI2 != R_RFD_NO_DEFINITION) */
    
    /* If FACI2 is not defined (R_RFD_DF_BASE_FACI2 == R_RFD_NO_DEFINITION) */
    else
    {
        /* FACI2 is not available */
        l_bu2_targetFaci = R_RFD_INVALID_FACI;
    }
    
    return (l_bu2_targetFaci);
    
}


/**************************************************************************************************************
 *  Declares the section
 *    - End of the definition of the text section for the Data Flash Control Component
 *************************************************************************************************************/

/* End of the definition of the text section */
#define  R_RFD_DF_STOP_SEC_CODE
#include "r_rfd_memmap.h"       /* !MISRA-C 2012 rule 20.1 (QAC message 5087) */
                                /* !CERT-C rule 5002 */

#endif /* R_RFD_CONTROL_TARGET_DATAFLASH == R_RFD_DISABLE */

