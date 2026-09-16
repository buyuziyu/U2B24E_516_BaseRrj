/**********************************************************************************************************************
    Program Name    : Sample program for Renesas Flash Driver (RFD28F)
    
    File Name       : sample_flash_control.h
    Program Version : V1.00
    File Revision   : $Rev: 4348 $
    File Date       : $Date:: 2023-05-19 15:07:16 +0700#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : Sample application for Renesas Flash Driver (RFD28F)
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
 *   Rule         : No MISRA-C 2012 or CERT-C rule / QAC message 0776
 *   Message      : External identifier matches other external identifier(s) (e.g. '%s')
 *                  in first 6 characters - program does not conform strictly to ISO:C90.
 *   Reason       : "R_RFD_" is defined as a string necessary to recognize that it is an API of RFD provided
 *                  by Renesas to distinguish it from other APIs. Furthermore, since both the external identifier and
 *                  the internal identifier do not exceed 31 characters, the minimum requirement of valid characters
 *                  is satisfied and it is determined that there is no problem.
 *   Verification : Incorrect API name would result in test fails.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule 5002
 *   Message      : The header '%s' file name shadows a previously included header.
 *   Reason       : The header file of the RFD28F starts with "r_rfd", and in the case of a component-specific
 *                  header file is given a component name to improve identification.
 *                  It is intentional and there is no problem.
 *   Verification : Incorrect processing would result in test fails.
 *********************************************************************************************************************/

#ifndef SAMPLE_FLASH_CONTROL_H
#define SAMPLE_FLASH_CONTROL_H

#include "r_rfd.h"
#include "r_rfd_common.h"       /* !CERT-C rule 5002 */
#include "r_rfd_df.h"

#if   defined(__RH850_U2A__) || defined(__RH850_U2B__)
#include "r_rfd_cf.h"
#endif

/**********************************************************************************************************************
    Return value
**********************************************************************************************************************/

#define R_RFD_ERR_NO_SUSPENSION     0x00010000UL    /* Example of error code defined by sample program */
#define R_RFD_ERR_TIMEOUT           0x00010001UL    /* Example of error code defined by sample program */

/**********************************************************************************************************************
    Macro Difinition
**********************************************************************************************************************/

#define R_RFD_LENGTH_4BYTES         4UL     /* Length of writing data (4 bytes)    */
#define R_RFD_LENGTH_8BYTES         8UL     /* Length of writing data (8 bytes)    */
#define R_RFD_LENGTH_16BYTES        16UL    /* Length of writing data (16 bytes)   */
#define R_RFD_LENGTH_32BYTES        32UL    /* Length of writing data (32 bytes)   */
#define R_RFD_LENGTH_64BYTES        64UL    /* Length of writing data (64 bytes)   */
#define R_RFD_LENGTH_128BYTES       128UL   /* Length of writing data (128 bytes)  */
#define R_RFD_LENGTH_256BYTES       256UL   /* Length of writing data (256 bytes)  */
#define R_RFD_LENGTH_512BYTES       512UL   /* Length of writing data (512 bytes)  */

#define R_RFD_LENGTH_IDAUTH          32UL   /* Length of writing data (1byte * 32) */

/**********************************************************************************************
 *  Definition of register for clock gear up
 *********************************************************************************************/

/* Clock Controller */
#if   defined(__RH850_U2A__)

/* Address definition */
#define REG_ADDR_MOSCE       0xFF988000U
#define REG_ADDR_MOSCS       0xFF988004U
#define REG_ADDR_PLLE        0xFF980000U
#define REG_ADDR_PLLS        0xFF980004U
#define REG_ADDR_CKSC_CPUC   0xFF980100U
#define REG_ADDR_CKSC_CPUS   0xFF980108U
#define REG_ADDR_CLKD_PLLC   0xFF980120U
#define REG_ADDR_CLKD_PLLS   0xFF980128U
#define REG_ADDR_CLKKCPROT1  0xFF980700U
#define REG_ADDR_CKSC_RCANC  0xFF980150U
#define REG_ADDR_CKSC_RCANS  0xFF980158U

/* For Access definition */
#define REG_MOSCE       (*((volatile unsigned long *)(REG_ADDR_MOSCE)))         /* 32bit R/W */
#define REG_MOSCS       (*((volatile unsigned long *)(REG_ADDR_MOSCS)))         /* 32bit R   */
#define REG_PLLE        (*((volatile unsigned long *)(REG_ADDR_PLLE)))          /* 32bit R/W */
#define REG_PLLS        (*((volatile unsigned long *)(REG_ADDR_PLLS)))          /* 32bit R   */
#define REG_CKSC_CPUC   (*((volatile unsigned long *)(REG_ADDR_CKSC_CPUC)))     /* 32bit R/W */
#define REG_CKSC_CPUS   (*((volatile unsigned long *)(REG_ADDR_CKSC_CPUS)))     /* 32bit R   */
#define REG_CLKD_PLLC   (*((volatile unsigned long *)(REG_ADDR_CLKD_PLLC)))     /* 32bit R/W */
#define REG_CLKD_PLLS   (*((volatile unsigned long *)(REG_ADDR_CLKD_PLLS)))     /* 32bit R   */
#define REG_CLKKCPROT1  (*((volatile unsigned long *)(REG_ADDR_CLKKCPROT1)))    /* 32bit R/W */
#define REG_CKSC_RCANC  (*((volatile unsigned long *)(REG_ADDR_CKSC_RCANC)))    /* 32bit R/W */
#define REG_CKSC_RCANS  (*((volatile unsigned long *)(REG_ADDR_CKSC_RCANS)))    /* 32bit R   */

/* Related Main OSC */
#define VALUE_MAINOSC_START                 0x00000001UL    /* Main OSC is starting (for MOSCE) */
#define VALUE_MAINOSC_STOP                  0x00000002UL    /* Main OSC is stopping (for MOSCE) */
#define VALUE_MAINOSC_STOPPING              0x00000000UL    /* Main OSC is stopping (for MOSCS) */
#define VALUE_MAINOSC_START_STABLE          0x00000003UL    /* Main OSC is stable (for MOSCS)   */
#define VALUE_MAINOSC_STOP_STABLE           0x00000000UL    /* Main OSC is stable (for MOSCS)   */

/* Related PLL */
#define VALUE_PLL_STOP                      0x00000002UL    /* STOP PLL (for PLLE)                  */
#define VALUE_PLL_START                     0x00000001UL    /* STOP PLL (for PLLE)                  */
#define VALUE_PLL_STOPPING                  0x00000000UL    /* PLLS is stopping  (for PLLS)         */
#define VALUE_PLL_START_STABLE              0x00000003UL    /* PLLS is stable (on start) (for PLLS) */
#define VALUE_PLL_STOP_STABLE               0x00000000UL    /* PLLS is stable (on stop) (for PLLS)  */

/* Related Write protection */
#define VALUE_CLKKCPROT0_KCE_DISABLE        0xA5A5A500UL    /* Disable write access */
#define VALUE_CLKKCPROT0_KCE_ENABLE         0xA5A5A501UL    /* Enable write access  */

/* Related PLL Divider */
#define VALUE_CLKD_PLLC_NO_DIVISION         0x00000001UL    /* No Division                 */
#define VALUE_CLKD_PLLC_DIVIDED2            0x00000002UL    /* Divided by 2                */
#define VALUE_CLKD_STABLE                   0x00000003UL    /* PLL Clock divider is stable */

/* Related Selector of CLK source */
#define VALUE_CKSC_CPU_CLK_PLLO             0x00000000UL    /* Clock source is CLK_PLLO        */
#define VALUE_CKSC_CPU_CLK_IOSC             0x00000001UL    /* Clock source is CLK_IOSC        */
#define VALUE_CKSC_CPU_CLK_PLLO_STABLE      0x00000000UL    /* Stable as CLK_PLLO              */
#define VALUE_CKSC_CPU_CLK_IOSC_STABLE      0x00000001UL    /* Stable as CLK_IOSC              */

/* Related Selector of CLK source */
#define VALUE_CKSC_RCANC_CLK_MOSC           0x00000001UL    /* Clock source is CKSC_RCANC      */
#define VALUE_CKSC_RCANS_CLK_MOSC           0x00000001UL    /* Clock source is CKSC_RCANS      */

#elif   defined(__RH850_U2B__)

/* Address definition */
#define REG_ADDR_MOSCE        0xFF988000U
#define REG_ADDR_MOSCS        0xFF988004U
#define REG_ADDR_PLLE         0xFF980000U
#define REG_ADDR_PLLS         0xFF980004U
#define REG_ADDR_CKS_CLEANC   0xFF980100U
#define REG_ADDR_CKS_CLEANS   0xFF980108U
#define REG_ADDR_CKD_PLLC     0xFF980120U
#define REG_ADDR_CKD_PLLS     0xFF980128U
#define REG_ADDR_CLKKCPROT1   0xFF980700U
#define REG_ADDR_CKS_RCANC    0xFF980150U
#define REG_ADDR_CKS_RCANS    0xFF980158U

/* For Access definition */
#define REG_MOSCE        (*((volatile unsigned long *)(REG_ADDR_MOSCE)))         /* 32bit R/W */
#define REG_MOSCS        (*((volatile unsigned long *)(REG_ADDR_MOSCS)))         /* 32bit R   */
#define REG_PLLE         (*((volatile unsigned long *)(REG_ADDR_PLLE)))          /* 32bit R/W */
#define REG_PLLS         (*((volatile unsigned long *)(REG_ADDR_PLLS)))          /* 32bit R   */
#define REG_CKS_CLEANC   (*((volatile unsigned long *)(REG_ADDR_CKS_CLEANC)))     /* 32bit R/W */
#define REG_CKS_CLEANS   (*((volatile unsigned long *)(REG_ADDR_CKS_CLEANS)))     /* 32bit R   */
#define REG_CKD_PLLC     (*((volatile unsigned long *)(REG_ADDR_CKD_PLLC)))     /* 32bit R/W */
#define REG_CKD_PLLS     (*((volatile unsigned long *)(REG_ADDR_CKD_PLLS)))     /* 32bit R   */
#define REG_CLKKCPROT1   (*((volatile unsigned long *)(REG_ADDR_CLKKCPROT1)))    /* 32bit R/W */
#define REG_CKS_RCANC    (*((volatile unsigned long *)(REG_ADDR_CKS_RCANC)))    /* 32bit R/W */
#define REG_CKS_RCANS    (*((volatile unsigned long *)(REG_ADDR_CKS_RCANS)))    /* 32bit R   */

/* Related Main OSC */
#define VALUE_MAINOSC_START                 0x00000001UL    /* Main OSC is starting (for MOSCE) */
#define VALUE_MAINOSC_STOP                  0x00000002UL    /* Main OSC is stopping (for MOSCE) */
#define VALUE_MAINOSC_STOPPING              0x00000000UL    /* Main OSC is stopping (for MOSCS) */
#define VALUE_MAINOSC_START_STABLE          0x00000003UL    /* Main OSC is stable (for MOSCS)   */
#define VALUE_MAINOSC_STOP_STABLE           0x00000000UL    /* Main OSC is stable (for MOSCS)   */

/* Related PLL */
#define VALUE_PLL_STOP                      0x00000002UL    /* STOP PLL (for PLLE)                  */
#define VALUE_PLL_START                     0x00000001UL    /* STOP PLL (for PLLE)                  */
#define VALUE_PLL_STOPPING                  0x00000000UL    /* PLLS is stopping  (for PLLS)         */
#define VALUE_PLL_START_STABLE              0x00000003UL    /* PLLS is stable (on start) (for PLLS) */
#define VALUE_PLL_STOP_STABLE               0x00000000UL    /* PLLS is stable (on stop) (for PLLS)  */

/* Related Write protection */
#define VALUE_CLKKCPROT0_KCE_DISABLE        0xA5A5A500UL    /* Disable write access */
#define VALUE_CLKKCPROT0_KCE_ENABLE         0xA5A5A501UL    /* Enable write access  */

/* Related PLL Divider */
#define VALUE_CKD_PLLC_NO_DIVISION          0x00000000UL    /* No Division                 */
#define VALUE_CKD_PLLC_DIVIDED2             0x00000008UL    /* Divided by 2                */
#define VALUE_CKD_PLLC_DIVIDED4             0x00000004UL    /* Divided by 4				   */
#define VALUE_CKD_PLLC_DIVIDED8             0x00000002UL    /* Divided by 8				   */
#define VALUE_CKD_PLLC_DIVIDED16            0x00000001UL    /* Divided by 16			   */
#define VALUE_CKD_STABLE                    0x00000002UL    /* PLL Clock divider is stable */

/* Related Selector of CLK source */
#define VALUE_CKSC_CPU_CLK_PLLO             0x00000000UL    /* Clock source is CLK_PLLO        */
#define VALUE_CKSC_CPU_CLK_IOSC             0x00000001UL    /* Clock source is CLK_IOSC        */
#define VALUE_CKSC_CPU_CLK_PLLO_STABLE      0x00000000UL    /* Stable as CLK_PLLO              */
#define VALUE_CKSC_CPU_CLK_IOSC_STABLE      0x00000001UL    /* Stable as CLK_IOSC              */

/* Related Selector of CLK source */
#define VALUE_CKSC_RCANC_CLK_MOSC           0x00000001UL    /* Clock source is CKSC_RCANC      */
#define VALUE_CKSC_RCANS_CLK_MOSC           0x00000001UL    /* Clock source is CKSC_RCANS      */

#else

#define REG_CLK_BASE  0xff703000UL
#define REG_CLKD0DIV    (*((volatile unsigned long *)(REG_CLK_BASE)))             /* 32bit R/W */
#define REG_CLKD0STAT   (*((volatile unsigned long *)(REG_CLK_BASE + 0x004UL)))   /* 32bit R/W */
#define REG_CKSC0C      (*((volatile unsigned long *)(REG_CLK_BASE + 0x100UL)))   /* 32bit R/W */
#define REG_CKSC0S      (*((volatile unsigned long *)(REG_CLK_BASE + 0x108UL)))   /* 32bit R/W */
#define REG_PLLCLKS     (*((volatile unsigned long *)(REG_CLK_BASE + 0x200UL)))   /* 32bit R/W */
#define REG_CLKKCPROT0  (*((volatile unsigned long *)(REG_CLK_BASE + 0x700UL)))   /* 32bit R/W */

#define MASK_PLLCLKS_CLKSTUB            0x00000002UL    /* PLL is stable */
#define MASK_CLKD0DIV_CLKD0DIV          0x00000001UL    /* No division   */
#define MASK_CKSC0C_CKSC0               0x00000001UL    /* PLL           */
#define MASK_CKSC0S_CLKACT0             0x00000001UL    /* PLL           */
#define MASK_CLKD0STAT_CLKD0SYNC        0x00000002UL    /* Division ratio setting is CLKD0DIV */

#define VALUE_CLKKCPROT0_KCE_DISABLE    0xA5A5A500UL    /* Disable write access */
#define VALUE_CLKKCPROT0_KCE_ENABLE     0xA5A5A501UL    /* Enable write access  */

#endif /* #defined(__RH850_U2A__), defined(__RH850_U2B__) */

/**********************************************************************************************************************
    Prototype declaration
**********************************************************************************************************************/

/* !QAC message 0776 */
extern T_u4_RFDReturn  Sample_DataFlashControl(T_u4_RfdAddress i_u4_Start, \
                                               T_u4_RfdAddress i_u4_End, T_pu4_RfdBuffer i_pu4_Data);
extern T_u4_RFDReturn  Sample_CodeFlashControl(T_u4_RfdAddress i_u4_Start, \
                                               T_u4_RfdAddress i_u4_End, T_pu4_RfdBuffer i_pu4_Data);

extern T_u4_RFDReturn  Sample_PropertyAreaControl(void);

extern T_u4_RFDReturn  Sample_ExtendedDataControl(T_u4_RfdAddress i_u4_Start, \
                                               T_u4_RfdAddress i_u4_End, T_pu4_RfdBuffer i_pu4_Data);

#endif  /* SAMPLE_FLASH_CONTROL_H */
