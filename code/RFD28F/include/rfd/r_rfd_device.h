/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD28F)
    
    File Name       : r_rfd_device.h
    Program Version : V2.00
    File Revision   : $Rev: 4364 $
    File Date       : $Date:: 2023-05-22 17:37:11 +0700#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : Include file for device dependency information
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
 *   Rule         : MISRA-C 2012 rule 2.4 / QAC(RCMA) message 1755
 *   Message      : The tag 'name' is declared but not used within this project.
 *   Reason       : The corresponding tag name is defined as a name representing the feature of the structure,
 *                  and is necessary to identify the type of multiple defined structure.
 *   Verification : No violation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : MISRA-C 2012 rule 3.1 / QAC message 3108
 *   Message      : Nested comments are not recognized in the ISO standard.
 *   Reason       : Description "//" is a part of URL, so This does not apply.
 *   Verification : No violation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *   Rule         : CERT-C rule DCL06 / QAC message 3132
 *   Message      : Hard coded 'magic' number, '%s', used to define the size of an array.
 *   Reason       : The free area in the structure elements are defined, and the number of free bytes is the number of
 *                  array elements. The relevant part is a hardware dependent part, The free area location and
 *                  the number of free bytes also change depending on the hardware, and there is no point in defining
 *                  the number of elements separately, so this implementation method is adopted.
 *   Verification : Incorrect conversion would result in test fails.
 *********************************************************************************************************************/

#ifndef R_RFD_DEVICE_H
#define R_RFD_DEVICE_H

#include "r_rfd_types.h"    /* !CERT-C rule 5002 */
#include "r_rfd_config.h"   /* !CERT-C rule 5002 */

/**********************************************************************************************************************
    For All Component
**********************************************************************************************************************/

/**********************************************************************************************************************
    Base address of FACI
**********************************************************************************************************************/

#ifndef __R_RFD_USE_STUB__   /* For Normal Code */
    
    /* If FACI0 is defined in the r_rfd_config.h    */
    #if defined(R_RFD_BASE_ADDRESS_FACI0)
        /* FACI0 Base address   */
        #define R_RFD_BASE_FACI0    R_RFD_BASE_ADDRESS_FACI0
        /* FHVE3FP0 & FHVE15FP0 address */
        #define R_RFD_REG_FHVE3FP0  (*(volatile T_u4 *)R_RFD_REG_ADDRESS_FHVE3_0)
        #define R_RFD_REG_FHVE15FP0 (*(volatile T_u4 *)R_RFD_REG_ADDRESS_FHVE15_0)
        /* Valid flag for FACI0 */
        #define R_RFD_VALID_FACI0   R_RFD_TRUE
    #endif
    
    /* If FACI1 is defined in the r_rfd_config.h    */
    #if defined(R_RFD_BASE_ADDRESS_FACI1)
        /* FACI0 Base address   */
        #define R_RFD_BASE_FACI1    R_RFD_BASE_ADDRESS_FACI1
        /* FHVE3FP1 & FHVE15FP1 address */
        #define R_RFD_REG_FHVE3FP1  (*(volatile T_u4 *)R_RFD_REG_ADDRESS_FHVE3_1)
        #define R_RFD_REG_FHVE15FP1 (*(volatile T_u4 *)R_RFD_REG_ADDRESS_FHVE15_1)
        /* Valid flag for FACI1 */
        #define R_RFD_VALID_FACI1   R_RFD_TRUE
    #endif
    
    /* If FACI2 is defined in the r_rfd_config.h    */
    #if defined(R_RFD_BASE_ADDRESS_FACI2)
        /* FACI2 Base address   */
        #define R_RFD_BASE_FACI2    R_RFD_BASE_ADDRESS_FACI2
        /* FHVE3FP2 & FHVE15FP2 address */
        #define R_RFD_REG_FHVE3FP2  (*(volatile T_u4 *)R_RFD_REG_ADDRESS_FHVE3_2)
        #define R_RFD_REG_FHVE15FP2 (*(volatile T_u4 *)R_RFD_REG_ADDRESS_FHVE15_2)
        /* Valid flag for FACI2 */
        #define R_RFD_VALID_FACI2   R_RFD_TRUE
    #endif
    
    /* If FACI0 is NOT defined in the r_rfd_config.h    */
    #if !defined(R_RFD_BASE_ADDRESS_FACI0)
        #define R_RFD_VALID_FACI0   R_RFD_FALSE         /* Valid flag for FACI0 */
        #define R_RFD_BASE_FACI0    R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_CMDAREA_FACI0 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_DF_BASE_FACI0 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_CF_BASE_FACI0 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_REG_FHVE3FP0  (*(volatile T_u4 *)R_RFD_NO_DEFINED_ADDRESS) /* No definition */
        #define R_RFD_REG_FHVE15FP0 (*(volatile T_u4 *)R_RFD_NO_DEFINED_ADDRESS) /* No definition */
    #endif
    
    /* If FACI1 is NOT defined in the r_rfd_config.h    */
    #if !defined(R_RFD_BASE_ADDRESS_FACI1)
        #define R_RFD_VALID_FACI1   R_RFD_FALSE         /* Valid flag for FACI1 */
        #define R_RFD_BASE_FACI1    R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_CMDAREA_FACI1 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_DF_BASE_FACI1 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_CF_BASE_FACI1 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_REG_FHVE3FP1  (*(volatile T_u4 *)R_RFD_NO_DEFINED_ADDRESS)    /* No definition */
        #define R_RFD_REG_FHVE15FP1 (*(volatile T_u4 *)R_RFD_NO_DEFINED_ADDRESS)    /* No definition */
    #endif
    
    /* If FACI2 is NOT defined in the r_rfd_config.h    */
    #if !defined(R_RFD_BASE_ADDRESS_FACI2)
        #define R_RFD_VALID_FACI2   R_RFD_FALSE         /* Valid flag for FACI2 */
        #define R_RFD_BASE_FACI2    R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_CMDAREA_FACI2 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_DF_BASE_FACI2 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_CF_BASE_FACI2 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_REG_FHVE3FP2  (*(volatile T_u4 *)R_RFD_NO_DEFINED_ADDRESS)    /* No definition */
        #define R_RFD_REG_FHVE15FP2 (*(volatile T_u4 *)R_RFD_NO_DEFINED_ADDRESS)    /* No definition */
    #endif
    
#else   /* For Internal Test */
    
    extern struct faciRegisters   base_Faci0;
    extern struct faciRegisters   base_Faci1;
    extern struct faciRegisters   base_Faci2;

    /* If FACI0 is defined in the r_rfd_config.h    */
    #if defined(R_RFD_BASE_ADDRESS_FACI0)
        /* FACI0 Base address   */
        #define R_RFD_BASE_FACI0    ((T_u4)&base_Faci0)
        /* FHVE3FP0 & FHVE15FP0 address */
        #define R_RFD_REG_FHVE3FP0      (*(volatile T_u4 *)R_RFD_REG_ADDRESS_FHVE3_0)
        #define R_RFD_REG_FHVE15FP0     (*(volatile T_u4 *)R_RFD_REG_ADDRESS_FHVE15_0)
        /* Valid flag for FACI0 */
        #define R_RFD_VALID_FACI0   R_RFD_TRUE
    #endif
    
    /* If FACI1 is defined in the r_rfd_config.h    */
    #if defined(R_RFD_BASE_ADDRESS_FACI1)
        /* FACI0 Base address   */
        #define R_RFD_BASE_FACI1    ((T_u4)&base_Faci1)
        /* FHVE3FP1 & FHVE15FP1 address */
        #define R_RFD_REG_FHVE3FP1      (*(volatile T_u4 *)R_RFD_REG_ADDRESS_FHVE3_1)
        #define R_RFD_REG_FHVE15FP1     (*(volatile T_u4 *)R_RFD_REG_ADDRESS_FHVE15_1)
        /* Valid flag for FACI1 */
        #define R_RFD_VALID_FACI1   R_RFD_TRUE
    #endif
    
    /* If FACI2 is defined in the r_rfd_config.h    */
    #if defined(R_RFD_BASE_ADDRESS_FACI2)
        /* FACI2 Base address   */
        #define R_RFD_BASE_FACI2    ((T_u4)&base_Faci2)
        /* FHVE3FP2 & FHVE15FP2 address */
        #define R_RFD_REG_FHVE3FP2      (*(volatile T_u4 *)R_RFD_REG_ADDRESS_FHVE3_2)
        #define R_RFD_REG_FHVE15FP2     (*(volatile T_u4 *)R_RFD_REG_ADDRESS_FHVE15_2)
        /* Valid flag for FACI2 */
        #define R_RFD_VALID_FACI2   R_RFD_TRUE
    #endif
    
    /* If FACI0 is NOT defined in the r_rfd_config.h    */
    #if !defined(R_RFD_BASE_ADDRESS_FACI0)
        #define R_RFD_VALID_FACI0   R_RFD_FALSE         /* Valid flag for FACI0 */
        #define R_RFD_BASE_FACI0    R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_CMDAREA_FACI0 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_DF_BASE_FACI0 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_CF_BASE_FACI0 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_REG_FHVE3FP0  (*(volatile T_u4 *)R_RFD_NO_DEFINED_ADDRESS) /* No definition */
        #define R_RFD_REG_FHVE15FP0 (*(volatile T_u4 *)R_RFD_NO_DEFINED_ADDRESS) /* No definition */
    #endif
    
    /* If FACI1 is NOT defined in the r_rfd_config.h    */
    #if !defined(R_RFD_BASE_ADDRESS_FACI1)
        #define R_RFD_VALID_FACI1   R_RFD_FALSE         /* Valid flag for FACI1 */
        #define R_RFD_BASE_FACI1    R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_CMDAREA_FACI1 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_DF_BASE_FACI1 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_CF_BASE_FACI1 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_REG_FHVE3FP1  (*(volatile T_u4 *)R_RFD_NO_DEFINED_ADDRESS)    /* No definition */
        #define R_RFD_REG_FHVE15FP1 (*(volatile T_u4 *)R_RFD_NO_DEFINED_ADDRESS)    /* No definition */
    #endif
    
    /* If FACI2 is NOT defined in the r_rfd_config.h    */
    #if !defined(R_RFD_BASE_ADDRESS_FACI2)
        #define R_RFD_VALID_FACI2   R_RFD_FALSE         /* Valid flag for FACI2 */
        #define R_RFD_BASE_FACI2    R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_CMDAREA_FACI2 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_DF_BASE_FACI2 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_CF_BASE_FACI2 R_RFD_NO_DEFINITION /* No definition        */
        #define R_RFD_REG_FHVE3FP2  (*(volatile T_u4 *)R_RFD_NO_DEFINED_ADDRESS)    /* No definition */
        #define R_RFD_REG_FHVE15FP2 (*(volatile T_u4 *)R_RFD_NO_DEFINED_ADDRESS)    /* No definition */
    #endif
    
#endif  /* __R_RFD_USE_STUB__ */

/**********************************************************************************************************************
    For Related Code Flash Components settings
**********************************************************************************************************************/

#if (R_RFD_CONTROL_TARGET_CODEFLASH == R_RFD_DISABLE)
    #define R_RFD_VALID_MAPMODE R_RFD_SINGLE
    #define R_RFD_VALID_FPMON   R_RFD_DISABLE
#else
    #define R_RFD_VALID_MAPMODE R_RFD_MAPMODE
    #define R_RFD_VALID_FPMON   R_RFD_FPMON_CHECK
#endif


/**********************************************************************************************************************
    Maximum FACI number with device
**********************************************************************************************************************/

#define R_RFD_MAX_FACI_NUMBER   ((T_u1)3U)

/**********************************************************************************************************************
    Registers Related to Write and Erase Protection of Flash Memory

    - Traceability          : [Covers:UD_12_000]
**********************************************************************************************************************/

struct faciRegisters                /* !MISRA-C 2012 rule 2.4 (QAC(RCMA) message 1755) */
{                                   /* !CERT-C rule DCL06 (QAC message 3132)           */
    volatile T_u1 FPMON;            /* FPMON     */
    volatile T_u1 reserve00[15];    /* Reserved  */
    volatile T_u1 FASTAT;           /* FASTAT    */
    volatile T_u1 reserve01[3];     /* Reserved  */
    volatile T_u1 FAEINT;           /* FAEINT    */
    volatile T_u1 reserve02[3];     /* Reserved  */
    volatile T_u1 reserve03[1];     /* Reserved  */
    volatile T_u1 reserve04[7];     /* Reserved  */
    volatile T_u2 FAREASELC;        /* FAREASELC */ /* U2B only */
    volatile T_u1 reserve06[14];    /* Reserved  */
    volatile T_u4 FSADDR;           /* FSADDR    */
    volatile T_u4 FEADDR;           /* FEADDR    */
    volatile T_u1 reserve07[8];     /* Reserved  */
    volatile T_u2 FCVAPROT;         /* FCVAPROT  */
    volatile T_u1 reserve08[62];    /* Reserved  */
    volatile T_u4 FSTATR;           /* FSTATR    */
    volatile T_u2 FENTRYR;          /* FENTRYR   */
    volatile T_u1 reserve09[6];     /* Reserved  */
    volatile T_u2 FSUINITR;         /* FSUINITR  */
    volatile T_u1 reserve10[10];    /* Reserved  */
    volatile T_u1 reserve11[1];     /* Reserved  */
    volatile T_u1 reserve12[3];     /* Reserved  */
    volatile T_u1 reserve13[1];     /* Reserved  */
    volatile T_u1 reserve14[3];     /* Reserved  */
    volatile T_u2 FCMDR;            /* FCMDR     */
    volatile T_u1 reserve15[2];     /* Reserved  */
    volatile T_u2 FCMDMON;          /* FCMDMON   */
    volatile T_u1 reserve16[2];     /* Reserved  */
    volatile T_u1 FSWASTAT;         /* FSWASTAT  */
    volatile T_u1 reserve17[23];    /* Reserved  */
    volatile T_u2 FPESTAT;          /* FPESTAT   */
    volatile T_u1 reserve18[14];    /* Reserved  */
    volatile T_u1 FBCCNT;           /* FBCCNT    */
    volatile T_u1 reserve19[3];     /* Reserved  */
    volatile T_u1 FBCSTAT;          /* FBCSTAT   */
    volatile T_u1 reserve20[3];     /* Reserved  */
    volatile T_u4 FPSADDR;          /* FPSADDR   */
    volatile T_u1 reserve21[4];     /* Reserved  */
    volatile T_u2 FCPSR;            /* FCPSR     */ /* U2A only */
    volatile T_u1 reserve22[2];     /* Reserved  */
    volatile T_u1 reserve23[2];     /* Reserved  */
    volatile T_u1 reserve24[10];    /* Reserved  */
    volatile T_u1 reserve25[1];     /* Reserved  */
    volatile T_u1 reserve26[3];     /* Reserved  */
    volatile T_u1 reserve27[4];     /* Reserved  */
    volatile T_u1 reserve28[8];     /* Reserved  */
    volatile T_u2 FECCEMON;         /* FECCEMON  */
    volatile T_u1 reserve29[2];     /* Reserved  */
    volatile T_u2 FECCTMD;          /* FECCTMD   */
    volatile T_u1 reserve30[2];     /* Reserved  */
    volatile T_u2 FDMYECC;          /* FDMYECC  */
};

extern  T_u4    bu4_CMN_FaciBaseAddress;

#define FACI    (*(volatile struct faciRegisters *)bu4_CMN_FaciBaseAddress)

#define R_RFD_REG_FPMON         (FACI.FPMON)
#define R_RFD_REG_FASTAT        (FACI.FASTAT)
#define R_RFD_REG_FAEINT        (FACI.FAEINT)
#define R_RFD_REG_FAREASELC     (FACI.FAREASELC)    /*U2B only */
#define R_RFD_REG_FSADDR        (FACI.FSADDR)
#define R_RFD_REG_FEADDR        (FACI.FEADDR)
#define R_RFD_REG_FCVAPROT      (FACI.FCVAPROT)
#define R_RFD_REG_FSTATR        (FACI.FSTATR)
#define R_RFD_REG_FENTRYR       (FACI.FENTRYR)
#define R_RFD_REG_FSUINITR      (FACI.FSUINITR)
#define R_RFD_REG_FRTSTAT       (FACI.FRTSTAT)
#define R_RFD_REG_FRTEINT       (FACI.FRTEINT)
#define R_RFD_REG_FCMDR         (FACI.FCMDR)
#define R_RFD_REG_FCMDMON       (FACI.FCMDMON)
#define R_RFD_REG_FSWASTAT      (FACI.FSWASTAT)
#define R_RFD_REG_FPESTAT       (FACI.FPESTAT)
#define R_RFD_REG_FBCCNT        (FACI.FBCCNT)
#define R_RFD_REG_FBCSTAT       (FACI.FBCSTAT)
#define R_RFD_REG_FPSADDR       (FACI.FPSADDR)
#define R_RFD_REG_FCPSR         (FACI.FCPSR)        /*U2A only */
#define R_RFD_REG_FPCKAR        (FACI.FPCKAR)
#define R_RFD_REG_FLEMU         (FACI.FLEMU)
#define R_RFD_REG_FLEAD         (FACI.FLEAD)
#define R_RFD_REG_FECCEMON      (FACI.FECCEMON)
#define R_RFD_REG_FECCTMD       (FACI.FECCTMD)
#define R_RFD_REG_FDMYECC       (FACI.FDMYECC)

/**********************************************************************************************************************
    Masking value for FASTAT register
**********************************************************************************************************************/

#define R_RFD_MASK_FASTAT_CFAE  0x80U
#define R_RFD_MASK_FASTAT_DFAE  0x08U
#define R_RFD_MASK_FASTAT_CMDLK 0x10U

/**********************************************************************************************************************
    Masking value for FSTATR register
**********************************************************************************************************************/

#define R_RFD_MASK_FSTATR_ERCDTCT   0x20000000UL
#define R_RFD_MASK_FSTATR_ERCCRCT   0x10000000UL
#define R_RFD_MASK_FSTATR_SWTDTCT   0x08000000UL
#define R_RFD_MASK_FSTATR_SWTCRCT   0x04000000UL
#define R_RFD_MASK_FSTATR_SECDTCT   0x02000000UL
#define R_RFD_MASK_FSTATR_SECCRCT   0x01000000UL
#define R_RFD_MASK_FSTATR_ILGCOMERR 0x00800000UL
#define R_RFD_MASK_FSTATR_FESETERR  0x00400000UL
#define R_RFD_MASK_FSTATR_SECERR    0x00200000UL
#define R_RFD_MASK_FSTATR_OTERR     0x00100000UL
#define R_RFD_MASK_FSTATR_EBFULL    0x00040000UL
#define R_RFD_MASK_FSTATR_BPLDTCT   0x00020000UL
#define R_RFD_MASK_FSTATR_BPLCRCT   0x00010000UL
#define R_RFD_MASK_FSTATR_FRDY      0x00008000UL
#define R_RFD_MASK_FSTATR_ILGLERR   0x00004000UL
#define R_RFD_MASK_FSTATR_ERSERR    0x00002000UL
#define R_RFD_MASK_FSTATR_PRGERR    0x00001000UL
#define R_RFD_MASK_FSTATR_SUSRDY    0x00000800UL
#define R_RFD_MASK_FSTATR_DBFULL    0x00000400UL
#define R_RFD_MASK_FSTATR_ERSSPD    0x00000200UL
#define R_RFD_MASK_FSTATR_PRGSPD    0x00000100UL
#define R_RFD_MASK_FSTATR_FHVEERR   0x00000040UL
#define R_RFD_MASK_FSTATR_CFGDTCT   0x00000020UL
#define R_RFD_MASK_FSTATR_CFGCRCT   0x00000010UL
#define R_RFD_MASK_FSTATR_TBLDTCT   0x00000008UL
#define R_RFD_MASK_FSTATR_TBLCRCT   0x00000004UL

/**********************************************************************************************************************
    Set and Read value for FPMON register
**********************************************************************************************************************/

#define R_RFD_VALUE_FPMON_SFWE      ((T_u1)0x80U)

/**********************************************************************************************************************
    Set and Read value for the register
**********************************************************************************************************************/

#define R_RFD_KEY_FENTRYR           ((T_u2)0xAA00U)
#define R_RFD_VALUE_DF_PE_MODE      ((T_u2)0x0080U)
#define R_RFD_VALUE_CF_PE_MODE      ((T_u2)0x0001U)
#define R_RFD_VALUE_READ_MODE       ((T_u2)0x0000U)

#define R_RFD_KEY_FSUINITR          ((T_u2)0x2D00U)
#define R_RFD_VALUE_INIT_FSUINITR   ((T_u2)0x0000U)

#define R_RFD_KEY_FECCTMD           ((T_u2)0xA600U)
#define R_RFD_VALUE_INIT_FECCTMD    ((T_u2)0x0030U)

#define R_RFD_KEY_FCVAPROT          ((T_u2)0xFE00U)
#define R_RFD_VALUE_CF_PROTECT      ((T_u2)0x0001U)

/**********************************************************************************************************************
    The FCPSR register value (Flash Sequencer Process Switch Register)
**********************************************************************************************************************/

#define R_RFD_VALUE_FCPSR_SUSPRI_MODE   ((T_u2)0x0000U)
#define R_RFD_VALUE_FCPSR_ERSPRI_MODE   ((T_u2)0x0001U)

/**********************************************************************************************************************
    The FBCCNT register value (Data Flash Blank Check Control Register)
**********************************************************************************************************************/

#define R_RFD_VALUE_FBCCNT_INC_MODE     ((T_u1)0x00U)
#define R_RFD_VAUEL_FBCCNT_DEC_MODE     ((T_u1)0x01U)

/**********************************************************************************************************************
    The FCMDR register value (FACI Command Register)
**********************************************************************************************************************/

#define R_RFD_VALUE_FCMDR_BLANK_CHECKING   ((T_u2)0xD071U)

/**********************************************************************************************************************
    The FBCSTAT register value (Data Flash Blank Check Control Status Register)
**********************************************************************************************************************/

#define R_RFD_VALUE_FBCSTAT_BLANK       ((T_u1)0x00U)
#define R_RFD_VALUE_FBCSTAT_NOTBLANK    ((T_u1)0x01U)

/**********************************************************************************************************************
    The FAEINT register value (Flash Access Error Interrupt Enable Register)
    
    - Traceability          : [Covers:UD_14_000]
**********************************************************************************************************************/

#define R_RFD_VALUE_FAEINT_CFAEIE     ((T_u1)(R_RFD_REG_FAEINT_CFAEIE  << 7U))  /* From r_rfd_config.h */
#define R_RFD_VALUE_FAEINT_CMDLKIE    ((T_u1)(R_RFD_REG_FAEINT_CMDLKIE << 4U))  /* From r_rfd_config.h */
#define R_RFD_VALUE_FAEINT_DFAEIE     ((T_u1)(R_RFD_REG_FAEINT_DFAEIE  << 3U))  /* From r_rfd_config.h */
#define R_RFD_VALUE_FAEINT_ECRCTIE    ((T_u1)(R_RFD_REG_FAEINT_ECRCTIE))        /* From r_rfd_config.h */

#define R_RFD_VALUE_FAEINT      (R_RFD_VALUE_FAEINT_CFAEIE      \
                                  | R_RFD_VALUE_FAEINT_CMDLKIE  \
                                  | R_RFD_VALUE_FAEINT_DFAEIE   \
                                  | R_RFD_VALUE_FAEINT_ECRCTIE)


/**********************************************************************************************************************
    Masking value for FSWASTAT register (Switch Area Status Register)
    
    - Traceability          : [Covers:UD_01_310]
**********************************************************************************************************************/

#define R_RFD_MASK_FSWASTAT_BPVA1       0x20U
#define R_RFD_MASK_FSWASTAT_BPVA0       0x10U
#define R_RFD_MASK_FSWASTAT_SECVA       0x08U
#define R_RFD_MASK_FSWASTAT_CFGVA       0x04U
#define R_RFD_MASK_FSWASTAT_SWAS        0x02U
#define R_RFD_MASK_FSWASTAT_SWVA        0x01U

/**********************************************************************************************************************
    FACI Command ID
**********************************************************************************************************************/

#define R_RFD_CMD_FORCED_STOP           0xB3U
#define R_RFD_CMD_STATUS_CLEAR          0x50U
#define R_RFD_CMD_SUSPEND               0xB0U
#define R_RFD_CMD_RESUME                0xD0U
#define R_RFD_CMD_BLOCK_ERASE           0x20U
#define R_RFD_CMD_AREA_ERASE            0x23U
#define R_RFD_CMD_SINGLE_WRITE          0xE8U
#define R_RFD_CMD_MULTI_WRITE           0xEDU
#define R_RFD_CMD_BLANK_CHECK           0x71U
#define R_RFD_CMD_PROPERTY_ERASE        0x47U
#define R_RFD_CMD_PROPERTY_WRITE        0x45U
#define R_RFD_CMD_SWITCH_ERASE          0x87U
#define R_RFD_CMD_SWITCH_WRITE          0x85U
#define R_RFD_CMD_TAG_ERASE             0x89U
#define R_RFD_CMD_TAG_UPDATE            0x83U
#define R_RFD_CMD_RUN                   0xD0U

/**********************************************************************************************************************
    IDs Input Registers
        - IDs for use in authentication
**********************************************************************************************************************/

/**********************************************************************************************************************
    Common Definition
**********************************************************************************************************************/

#define R_RFD_LENGTH_ID                 256U    /* Length of ID (bit)                           */
#define R_RFD_LENGTH_UNIT_ID            32U     /* Unit Length of ID (bit)                      */
#define R_RFD_LENGTH_PROPERTY_WRITE     32U     /* Unit of writing length to Hardware Property  */
#define R_RFD_LENGTH_SWITCH_AREA_WRITE  32U     /* Unit of writing length to Switch Area        */

/**********************************************************************************************************************
    Serial Programmer ID Input Register
        - ID for use in authentication at the time of Serial-Programming
**********************************************************************************************************************/

#define R_RFD_REG_SPIDIN_TOP_ADDRESS    0xFFA08000UL    /* Address of SPIDIN */

#define R_RFD_REG_SPIDIN0_ADDRESS       0xFFA08000UL
#define R_RFD_REG_SPIDIN1_ADDRESS       0xFFA08004UL
#define R_RFD_REG_SPIDIN2_ADDRESS       0xFFA08008UL
#define R_RFD_REG_SPIDIN3_ADDRESS       0xFFA0800CUL
#define R_RFD_REG_SPIDIN4_ADDRESS       0xFFA08010UL
#define R_RFD_REG_SPIDIN5_ADDRESS       0xFFA08014UL
#define R_RFD_REG_SPIDIN6_ADDRESS       0xFFA08018UL
#define R_RFD_REG_SPIDIN7_ADDRESS       0xFFA0801CUL

#define R_RFD_REG_SPIDIN0               (*(volatile T_u4 *)R_RFD_REG_SPIDIN0_ADDRESS)
#define R_RFD_REG_SPIDIN1               (*(volatile T_u4 *)R_RFD_REG_SPIDIN1_ADDRESS)
#define R_RFD_REG_SPIDIN2               (*(volatile T_u4 *)R_RFD_REG_SPIDIN2_ADDRESS)
#define R_RFD_REG_SPIDIN3               (*(volatile T_u4 *)R_RFD_REG_SPIDIN3_ADDRESS)
#define R_RFD_REG_SPIDIN4               (*(volatile T_u4 *)R_RFD_REG_SPIDIN4_ADDRESS)
#define R_RFD_REG_SPIDIN5               (*(volatile T_u4 *)R_RFD_REG_SPIDIN5_ADDRESS)
#define R_RFD_REG_SPIDIN6               (*(volatile T_u4 *)R_RFD_REG_SPIDIN6_ADDRESS)
#define R_RFD_REG_SPIDIN7               (*(volatile T_u4 *)R_RFD_REG_SPIDIN7_ADDRESS)

#define R_RFD_LENGTH_SPID       256U    /* Length of SPID (bit)       */
#define R_RFD_LENGTH_UNIT_SPID  32U     /* Unit Length of SPID (bit)  */
#define R_RFD_IDST_SPIDR        0x01U   /* Serial-Programming ID Authentication Status */

/**********************************************************************************************************************
    Data Flash ID Input Register
        - ID for use in authentication for Data Flash Protection
**********************************************************************************************************************/

#define R_RFD_REG_DFIDIN_TOP_ADDRESS    0xFFA08020UL    /* Address of DFIDIN */

#define R_RFD_REG_DFIDIN0_ADDRESS       0xFFA08020UL
#define R_RFD_REG_DFIDIN1_ADDRESS       0xFFA08024UL
#define R_RFD_REG_DFIDIN2_ADDRESS       0xFFA08028UL
#define R_RFD_REG_DFIDIN3_ADDRESS       0xFFA0802CUL
#define R_RFD_REG_DFIDIN4_ADDRESS       0xFFA08030UL
#define R_RFD_REG_DFIDIN5_ADDRESS       0xFFA08034UL
#define R_RFD_REG_DFIDIN6_ADDRESS       0xFFA08038UL
#define R_RFD_REG_DFIDIN7_ADDRESS       0xFFA0803CUL

#define R_RFD_REG_DFIDIN0               (*(volatile T_u4 *)R_RFD_REG_DFIDIN0_ADDRESS)
#define R_RFD_REG_DFIDIN1               (*(volatile T_u4 *)R_RFD_REG_DFIDIN1_ADDRESS)
#define R_RFD_REG_DFIDIN2               (*(volatile T_u4 *)R_RFD_REG_DFIDIN2_ADDRESS)
#define R_RFD_REG_DFIDIN3               (*(volatile T_u4 *)R_RFD_REG_DFIDIN3_ADDRESS)
#define R_RFD_REG_DFIDIN4               (*(volatile T_u4 *)R_RFD_REG_DFIDIN4_ADDRESS)
#define R_RFD_REG_DFIDIN5               (*(volatile T_u4 *)R_RFD_REG_DFIDIN5_ADDRESS)
#define R_RFD_REG_DFIDIN6               (*(volatile T_u4 *)R_RFD_REG_DFIDIN6_ADDRESS)
#define R_RFD_REG_DFIDIN7               (*(volatile T_u4 *)R_RFD_REG_DFIDIN7_ADDRESS)

#define R_RFD_LENGTH_DFID           256U    /* Length of DFID (bit)       */
#define R_RFD_LENGTH_UNIT_DFID      32U     /* Unit Length of DFID (bit)  */
#define R_RFD_IDST_DFIDR            0x02U   /* Data Flash ID Authentication Status */

/**********************************************************************************************************************
    OCD ID Input Register
        - ID for use in authentication for OCD ID
**********************************************************************************************************************/

#define R_RFD_REG_OCDIDIN_TOP_ADDRESS   0xFFA08040UL    /* Address of OCDIDIN */

#define R_RFD_REG_OCDIDIN0_ADDRESS      0xFFA08040UL
#define R_RFD_REG_OCDIDIN1_ADDRESS      0xFFA08044UL
#define R_RFD_REG_OCDIDIN2_ADDRESS      0xFFA08048UL
#define R_RFD_REG_OCDIDIN3_ADDRESS      0xFFA0804CUL
#define R_RFD_REG_OCDIDIN4_ADDRESS      0xFFA08050UL
#define R_RFD_REG_OCDIDIN5_ADDRESS      0xFFA08054UL
#define R_RFD_REG_OCDIDIN6_ADDRESS      0xFFA08058UL
#define R_RFD_REG_OCDIDIN7_ADDRESS      0xFFA0805CUL

#define R_RFD_REG_OCDIDIN0              (*(volatile T_u4 *)R_RFD_REG_OCDIDIN0_ADDRESS)
#define R_RFD_REG_OCDIDIN1              (*(volatile T_u4 *)R_RFD_REG_OCDIDIN1_ADDRESS)
#define R_RFD_REG_OCDIDIN2              (*(volatile T_u4 *)R_RFD_REG_OCDIDIN2_ADDRESS)
#define R_RFD_REG_OCDIDIN3              (*(volatile T_u4 *)R_RFD_REG_OCDIDIN3_ADDRESS)
#define R_RFD_REG_OCDIDIN4              (*(volatile T_u4 *)R_RFD_REG_OCDIDIN4_ADDRESS)
#define R_RFD_REG_OCDIDIN5              (*(volatile T_u4 *)R_RFD_REG_OCDIDIN5_ADDRESS)
#define R_RFD_REG_OCDIDIN6              (*(volatile T_u4 *)R_RFD_REG_OCDIDIN6_ADDRESS)
#define R_RFD_REG_OCDIDIN7              (*(volatile T_u4 *)R_RFD_REG_OCDIDIN7_ADDRESS)

#define R_RFD_LENGTH_OCDID          256U    /* Length of OCDID (bit)      */
#define R_RFD_LENGTH_UNIT_OCDID     32U     /* Unit Length of OCDID (bit) */
#define R_RFD_IDST_OCDIDR           0x04U   /* OCD ID Authentication Status */

/**********************************************************************************************************************
    Customer ID A Input Register
        - ID for use in authentication for Customer ID A
**********************************************************************************************************************/

#define R_RFD_REG_CUSTIDAIN_TOP_ADDRESS 0xFFA08080UL    /* Address of CUSTIDAIN */

#define R_RFD_REG_CUSTIDAIN0_ADDRESS    0xFFA08080UL
#define R_RFD_REG_CUSTIDAIN1_ADDRESS    0xFFA08084UL
#define R_RFD_REG_CUSTIDAIN2_ADDRESS    0xFFA08088UL
#define R_RFD_REG_CUSTIDAIN3_ADDRESS    0xFFA0808CUL
#define R_RFD_REG_CUSTIDAIN4_ADDRESS    0xFFA08090UL
#define R_RFD_REG_CUSTIDAIN5_ADDRESS    0xFFA08094UL
#define R_RFD_REG_CUSTIDAIN6_ADDRESS    0xFFA08098UL
#define R_RFD_REG_CUSTIDAIN7_ADDRESS    0xFFA0809CUL

#define R_RFD_REG_CUSTIDAIN0            (*(volatile T_u4 *)R_RFD_REG_CUSTIDAIN0_ADDRESS)
#define R_RFD_REG_CUSTIDAIN1            (*(volatile T_u4 *)R_RFD_REG_CUSTIDAIN1_ADDRESS)
#define R_RFD_REG_CUSTIDAIN2            (*(volatile T_u4 *)R_RFD_REG_CUSTIDAIN2_ADDRESS)
#define R_RFD_REG_CUSTIDAIN3            (*(volatile T_u4 *)R_RFD_REG_CUSTIDAIN3_ADDRESS)
#define R_RFD_REG_CUSTIDAIN4            (*(volatile T_u4 *)R_RFD_REG_CUSTIDAIN4_ADDRESS)
#define R_RFD_REG_CUSTIDAIN5            (*(volatile T_u4 *)R_RFD_REG_CUSTIDAIN5_ADDRESS)
#define R_RFD_REG_CUSTIDAIN6            (*(volatile T_u4 *)R_RFD_REG_CUSTIDAIN6_ADDRESS)
#define R_RFD_REG_CUSTIDAIN7            (*(volatile T_u4 *)R_RFD_REG_CUSTIDAIN7_ADDRESS)

#define R_RFD_LENGTH_CUSTIDAID      256U    /* Length of CUSTIDAID (bit)            */
#define R_RFD_LENGTH_UNIT_CUSTIDAID 32U     /* Unit Length of CUSTIDAID (bit)       */
#define R_RFD_IDST_CUSTIDAIDR       0x10U   /* Customer ID A Authentication Status  */

/**********************************************************************************************************************
    Customer ID B Input Register
        - ID for use in authentication for Customer ID B
**********************************************************************************************************************/

#define R_RFD_REG_CUSTIDBIN_TOP_ADDRESS 0xFFA080A0UL    /* Address of CUSTIDBIN */

#define R_RFD_REG_CUSTIDBIN0_ADDRESS    0xFFA080A0UL
#define R_RFD_REG_CUSTIDBIN1_ADDRESS    0xFFA080A4UL
#define R_RFD_REG_CUSTIDBIN2_ADDRESS    0xFFA080A8UL
#define R_RFD_REG_CUSTIDBIN3_ADDRESS    0xFFA080ACUL
#define R_RFD_REG_CUSTIDBIN4_ADDRESS    0xFFA080B0UL
#define R_RFD_REG_CUSTIDBIN5_ADDRESS    0xFFA080B4UL
#define R_RFD_REG_CUSTIDBIN6_ADDRESS    0xFFA080B8UL
#define R_RFD_REG_CUSTIDBIN7_ADDRESS    0xFFA080BCUL

#define R_RFD_REG_CUSTIDBIN0            (*(volatile T_u4 *)R_RFD_REG_CUSTIDBIN0_ADDRESS)
#define R_RFD_REG_CUSTIDBIN1            (*(volatile T_u4 *)R_RFD_REG_CUSTIDBIN1_ADDRESS)
#define R_RFD_REG_CUSTIDBIN2            (*(volatile T_u4 *)R_RFD_REG_CUSTIDBIN2_ADDRESS)
#define R_RFD_REG_CUSTIDBIN3            (*(volatile T_u4 *)R_RFD_REG_CUSTIDBIN3_ADDRESS)
#define R_RFD_REG_CUSTIDBIN4            (*(volatile T_u4 *)R_RFD_REG_CUSTIDBIN4_ADDRESS)
#define R_RFD_REG_CUSTIDBIN5            (*(volatile T_u4 *)R_RFD_REG_CUSTIDBIN5_ADDRESS)
#define R_RFD_REG_CUSTIDBIN6            (*(volatile T_u4 *)R_RFD_REG_CUSTIDBIN6_ADDRESS)
#define R_RFD_REG_CUSTIDBIN7            (*(volatile T_u4 *)R_RFD_REG_CUSTIDBIN7_ADDRESS)

#define R_RFD_LENGTH_CUSTIDBID      256U    /* Length of CUSTIDBID (bit)            */
#define R_RFD_LENGTH_UNIT_CUSTIDBID 32U     /* Unit Length of CUSTIDBID (bit)       */
#define R_RFD_IDST_CUSTIDBIDR       0x20U   /* Customer ID B Authentication Status  */

/**********************************************************************************************************************
    Customer ID C Input Register
        - ID for use in authentication for Customer ID C
**********************************************************************************************************************/

#define R_RFD_REG_CUSTIDCIN_TOP_ADDRESS 0xFFA080C0UL    /* Address of CUSTIDCIN */

#define R_RFD_REG_CUSTIDCIN0_ADDRESS    0xFFA080C0UL
#define R_RFD_REG_CUSTIDCIN1_ADDRESS    0xFFA080C4UL
#define R_RFD_REG_CUSTIDCIN2_ADDRESS    0xFFA080C8UL
#define R_RFD_REG_CUSTIDCIN3_ADDRESS    0xFFA080CCUL
#define R_RFD_REG_CUSTIDCIN4_ADDRESS    0xFFA080D0UL
#define R_RFD_REG_CUSTIDCIN5_ADDRESS    0xFFA080D4UL
#define R_RFD_REG_CUSTIDCIN6_ADDRESS    0xFFA080D8UL
#define R_RFD_REG_CUSTIDCIN7_ADDRESS    0xFFA080DCUL

#define R_RFD_REG_CUSTIDCIN0            (*(volatile T_u4 *)R_RFD_REG_CUSTIDCIN0_ADDRESS)
#define R_RFD_REG_CUSTIDCIN1            (*(volatile T_u4 *)R_RFD_REG_CUSTIDCIN1_ADDRESS)
#define R_RFD_REG_CUSTIDCIN2            (*(volatile T_u4 *)R_RFD_REG_CUSTIDCIN2_ADDRESS)
#define R_RFD_REG_CUSTIDCIN3            (*(volatile T_u4 *)R_RFD_REG_CUSTIDCIN3_ADDRESS)
#define R_RFD_REG_CUSTIDCIN4            (*(volatile T_u4 *)R_RFD_REG_CUSTIDCIN4_ADDRESS)
#define R_RFD_REG_CUSTIDCIN5            (*(volatile T_u4 *)R_RFD_REG_CUSTIDCIN5_ADDRESS)
#define R_RFD_REG_CUSTIDCIN6            (*(volatile T_u4 *)R_RFD_REG_CUSTIDCIN6_ADDRESS)
#define R_RFD_REG_CUSTIDCIN7            (*(volatile T_u4 *)R_RFD_REG_CUSTIDCIN7_ADDRESS)

#define R_RFD_LENGTH_CUSTIDCID      256U    /* Length of CUSTIDCID (bit)            */
#define R_RFD_LENGTH_UNIT_CUSTIDCID 32U     /* Unit Length of CUSTIDCID (bit)       */
#define R_RFD_IDST_CUSTIDCIDR       0x40U   /* Customer ID C Authentication Status  */

/**********************************************************************************************************************
    RHSIF ID Input Register
        - ID for use in authentication for RHSIF ID
**********************************************************************************************************************/

#define R_RFD_REG_RHSIFIDIN_TOP_ADDRESS 0xFFA08200UL    /* Address of RHSIFIDIN */

#define R_RFD_REG_RHSIFIDIN0_ADDRESS    0xFFA08200UL
#define R_RFD_REG_RHSIFIDIN1_ADDRESS    0xFFA08204UL
#define R_RFD_REG_RHSIFIDIN2_ADDRESS    0xFFA08208UL
#define R_RFD_REG_RHSIFIDIN3_ADDRESS    0xFFA0820CUL
#define R_RFD_REG_RHSIFIDIN4_ADDRESS    0xFFA08210UL
#define R_RFD_REG_RHSIFIDIN5_ADDRESS    0xFFA08214UL
#define R_RFD_REG_RHSIFIDIN6_ADDRESS    0xFFA08218UL
#define R_RFD_REG_RHSIFIDIN7_ADDRESS    0xFFA0821CUL

#define R_RFD_REG_RHSIFIDIN0            (*(volatile T_u4 *)R_RFD_REG_RHSIFIDIN0_ADDRESS)
#define R_RFD_REG_RHSIFIDIN1            (*(volatile T_u4 *)R_RFD_REG_RHSIFIDIN1_ADDRESS)
#define R_RFD_REG_RHSIFIDIN2            (*(volatile T_u4 *)R_RFD_REG_RHSIFIDIN2_ADDRESS)
#define R_RFD_REG_RHSIFIDIN3            (*(volatile T_u4 *)R_RFD_REG_RHSIFIDIN3_ADDRESS)
#define R_RFD_REG_RHSIFIDIN4            (*(volatile T_u4 *)R_RFD_REG_RHSIFIDIN4_ADDRESS)
#define R_RFD_REG_RHSIFIDIN5            (*(volatile T_u4 *)R_RFD_REG_RHSIFIDIN5_ADDRESS)
#define R_RFD_REG_RHSIFIDIN6            (*(volatile T_u4 *)R_RFD_REG_RHSIFIDIN6_ADDRESS)
#define R_RFD_REG_RHSIFIDIN7            (*(volatile T_u4 *)R_RFD_REG_RHSIFIDIN7_ADDRESS)

#define R_RFD_LENGTH_RHSIFID        256U    /* Length of RHSIFID (bit)              */
#define R_RFD_LENGTH_UNIT_RHSIFID   32U     /* Unit Length of RHSIFID (bit)         */
#define R_RFD_IDST_RHSIFIDR         0x01U   /* RHSIF ID Authentication Status       */

/**********************************************************************************************************************
    Making value for the result of blank check
        - Change to physical address for Data Flash Memory
**********************************************************************************************************************/

#define R_RFD_PHYSICAL_BASE_ADDRESS_DF  0xFF200000UL

/**********************************************************************************************************************
    ID Authentication Status Register
**********************************************************************************************************************/

#define R_RFD_REG_IDST_ADDRESS      0xFFA081FCUL
#define R_RFD_REG_IDST2_ADDRESS     0xFFA083FCUL

#define R_RFD_REG_IDST              (*(volatile T_u4 *)0xFFA081FCUL)
#define R_RFD_REG_IDST2             (*(volatile T_u4 *)0xFFA083FCUL)

/**********************************************************************************************************************
    Information related to Extended Data Area

    - Traceability          : [Covers:UD_03_190]
**********************************************************************************************************************/

/**********************************************************************************************************************
    Definition of Address of Extended Data Area for RH850/U2x
**********************************************************************************************************************/

#define R_RFD_EXDATA_BASE_FACI0    0xFF320000UL
#define R_RFD_EXDATA_END_FACI0     0xFF3207FFUL

/**********************************************************************************************************************
    Registers Related to Check Hardware Property Area

    - Traceability          : [Covers:UD_03_360]
**********************************************************************************************************************/

/**********************************************************************************************************************
    Definition of Each Address of Hardware Property Area for RH850/U2x
**********************************************************************************************************************/

/* Invalid side of Configuration Setting Area */
#define R_RFD_CSA_BASE_FACI0    0xFF321000UL
#define R_RFD_CSA_END_FACI0     0xFF3217FFUL

/* Invalid side of Security Setting Area    */
#define R_RFD_SSA_BASE_FACI0    0xFF322000UL
#define R_RFD_SSA_END_FACI0     0xFF3227FFUL

/* Invalid side of Block Protection Area0   */
#define R_RFD_BPA0_BASE_FACI0   0xFF323000UL
#define R_RFD_BPA0_END_FACI0    0xFF3237FFUL

/* Invalid side of Block Protection Area1   */
#define R_RFD_BPA1_BASE_FACI1   0xFF340800UL
#define R_RFD_BPA1_END_FACI1    0xFF340FFFUL

/**********************************************************************************************************************
    Definition of Configuration Setting Flags for RH850/U2x
**********************************************************************************************************************/

struct CSAFlags                             /* !MISRA-C 2012 rule 2.4 (QAC(RCMA) message 1755) */
{
    volatile T_u4   CSAVOFC0;               /* CSAVOFC0  */
    volatile T_u4   csavofcreserve01;       /* CSAVOFC1  */
    volatile T_u4   csavofcreserve02;       /* CSAVOFC2  */
    volatile T_u4   csavofcreserve03;       /* CSAVOFC3  */
    volatile T_u4   csavofcreserve04;       /* CSAVOFC4  */
    volatile T_u4   csavofcreserve05;       /* CSAVOFC5  */
    volatile T_u4   csavofcreserve06;       /* CSAVOFC6  */
    volatile T_u4   csavofcreserve07;       /* CSAVOFC7  */
    volatile T_u4   CSAVOFC8;               /* CSAVOFC8  */
    volatile T_u4   CSAVOFC9;               /* CSAVOFC9  */
    volatile T_u4   CSAVOFC10;              /* CSAVOFC10 */
    volatile T_u4   CSAVOFC11;              /* CSAVOFC11 */
    volatile T_u4   CSAVOFC12;              /* CSAVOFC12 */
    volatile T_u4   CSAVOFC13;              /* CSAVOFC13 */
    volatile T_u4   CSAVOFC14;              /* CSAVOFC14 */
    volatile T_u4   CSAVOFC15;              /* CSAVOFC15 */
    volatile T_u4   CSAVOFC16;              /* CSAVOFC16 */
    volatile T_u4   CSAVOFC17;              /* CSAVOFC17 */
    volatile T_u4   CSAVOFC18;              /* CSAVOFC18 */
    volatile T_u4   CSAVOFC19;              /* CSAVOFC19 */
    volatile T_u4   csavofcreserve20;       /* CSAVOFC20 */
    volatile T_u4   csavofcreserve21;       /* CSAVOFC21 */
    volatile T_u4   csavofcreserve22;       /* CSAVOFC22 */
    volatile T_u4   csavofcreserve23;       /* CSAVOFC23 */
    volatile T_u4   csavofcreserve24;       /* CSAVOFC24 */
    volatile T_u4   csavofcreserve25;       /* CSAVOFC25 */
    volatile T_u4   csavofcreserve26;       /* CSAVOFC26 */
    volatile T_u4   csavofcreserve27;       /* CSAVOFC27 */
    volatile T_u4   csavofcreserve28;       /* CSAVOFC28 */
    volatile T_u4   csavofcreserve29;       /* CSAVOFC29 */
    volatile T_u4   csavofcreserve30;       /* CSAVOFC30 */
    volatile T_u4   csavofcreserve31;       /* CSAVOFC31 */
    volatile T_u4   csavofcreserve32;       /* CSAVOFC32 */
    volatile T_u4   csavofcreserve33;       /* CSAVOFC33 */
    volatile T_u4   csavofcreserve34;       /* CSAVOFC34 */
    volatile T_u4   csavofcreserve35;       /* CSAVOFC35 */
    volatile T_u4   csavofcreserve36;       /* CSAVOFC36 */
    volatile T_u4   csavofcreserve37;       /* CSAVOFC37 */
    volatile T_u4   csavofcreserve38;       /* CSAVOFC38 */
    volatile T_u4   csavofcreserve39;       /* CSAVOFC39 */
    volatile T_u4   csavofcreserve40;       /* CSAVOFC40 */
    volatile T_u4   csavofcreserve41;       /* CSAVOFC41 */
    volatile T_u4   csavofcreserve42;       /* CSAVOFC42 */
    volatile T_u4   csavofcreserve43;       /* CSAVOFC43 */
    volatile T_u4   csavofcreserve44;       /* CSAVOFC44 */
    volatile T_u4   csavofcreserve45;       /* CSAVOFC45 */
    volatile T_u4   csavofcreserve46;       /* CSAVOFC46 */
    volatile T_u4   csavofcreserve47;       /* CSAVOFC47 */
    volatile T_u4   csavofcreserve48;       /* CSAVOFC48 */
    volatile T_u4   csavofcreserve49;       /* CSAVOFC49 */
    volatile T_u4   csavofcreserve50;       /* CSAVOFC50 */
    volatile T_u4   csavofcreserve51;       /* CSAVOFC51 */
    volatile T_u4   csavofcreserve52;       /* CSAVOFC52 */
    volatile T_u4   csavofcreserve53;       /* CSAVOFC53 */
    volatile T_u4   csavofcreserve54;       /* CSAVOFC54 */
    volatile T_u4   csavofcreserve55;       /* CSAVOFC55 */
    volatile T_u4   csavofcreserve56;       /* CSAVOFC56 */
    volatile T_u4   csavofcreserve57;       /* CSAVOFC57 */
    volatile T_u4   csavofcreserve58;       /* CSAVOFC58 */
    volatile T_u4   csavofcreserve59;       /* CSAVOFC59 */
    volatile T_u4   csavofcreserve60;       /* CSAVOFC60 */
    volatile T_u4   csavofcreserve61;       /* CSAVOFC61 */
    volatile T_u4   csavofcreserve62;       /* CSAVOFC62 */
    volatile T_u4   csavofcreserve63;       /* CSAVOFC63 */
};

#ifndef __R_RFD_USE_STUB__   /* For Normal Code */
    #define CSA    (*(volatile struct CSAFlags *)0xFF321100UL)
#else   /* __R_RFD_USE_STUB__ */
    extern struct   CSAFlags    base_CSA;
    #define CSA    (*(volatile struct CSAFlags *)&base_CSA)
#endif

/* CSAVOFCn */
#define R_RFD_FLAG_CSAVOFC0     (CSA.CSAVOFC0)
#define R_RFD_FLAG_CSAVOFC8     (CSA.CSAVOFC8)
#define R_RFD_FLAG_CSAVOFC9     (CSA.CSAVOFC9)
#define R_RFD_FLAG_CSAVOFC10    (CSA.CSAVOFC10)
#define R_RFD_FLAG_CSAVOFC11    (CSA.CSAVOFC11)
#define R_RFD_FLAG_CSAVOFC12    (CSA.CSAVOFC12)
#define R_RFD_FLAG_CSAVOFC13    (CSA.CSAVOFC13)
#define R_RFD_FLAG_CSAVOFC14    (CSA.CSAVOFC14)
#define R_RFD_FLAG_CSAVOFC15    (CSA.CSAVOFC15)
#define R_RFD_FLAG_CSAVOFC16    (CSA.CSAVOFC16)
#define R_RFD_FLAG_CSAVOFC17    (CSA.CSAVOFC17)
#define R_RFD_FLAG_CSAVOFC18    (CSA.CSAVOFC18)
#define R_RFD_FLAG_CSAVOFC19    (CSA.CSAVOFC19)

/**********************************************************************************************************************
    Definition of Security Setting Flags for RH850/U2x
**********************************************************************************************************************/

struct  SSAFlags                            /* !MISRA-C 2012 rule 2.4 (QAC(RCMA) message 1755) */
{
    volatile T_u4   SSAVOFC0;               /* SSAVOFC0  */
    volatile T_u4   SSAVOFC1;               /* SSAVOFC1  */
    volatile T_u4   ssavofcreserve02;       /* SSAVOFC2  */
    volatile T_u4   ssavofcreserve03;       /* SSAVOFC3  */
    volatile T_u4   ssavofcreserve04;       /* SSAVOFC4  */
    volatile T_u4   ssavofcreserve05;       /* SSAVOFC5  */
    volatile T_u4   ssavofcreserve06;       /* SSAVOFC6  */
    volatile T_u4   SSAVOFC7;               /* SSAVOFC7  */
    volatile T_u4   SSAVOFC8;               /* SSAVOFC8  */
    volatile T_u4   SSAVOFC9;               /* SSAVOFC9  */
    volatile T_u4   SSAVOFC10;              /* SSAVOFC10 */
    volatile T_u4   SSAVOFC11;              /* SSAVOFC11 */
    volatile T_u4   SSAVOFC12;              /* SSAVOFC12 */
    volatile T_u4   SSAVOFC13;              /* SSAVOFC13 */
    volatile T_u4   SSAVOFC14;              /* SSAVOFC14 */
    volatile T_u4   SSAVOFC15;              /* SSAVOFC15 */
    volatile T_u4   SSAVOFC16;              /* SSAVOFC16 */
    volatile T_u4   SSAVOFC17;              /* SSAVOFC17 */
    volatile T_u4   SSAVOFC18;              /* SSAVOFC18 */
    volatile T_u4   ssavofcreserve19;       /* SSAVOFC19 */
    volatile T_u4   ssavofcreserve20;       /* SSAVOFC20 */
    volatile T_u4   ssavofcreserve21;       /* SSAVOFC21 */
    volatile T_u4   ssavofcreserve22;       /* SSAVOFC22 */
    volatile T_u4   ssavofcreserve23;       /* SSAVOFC23 */
    volatile T_u4   ssavofcreserve24;       /* SSAVOFC24 */
    volatile T_u4   ssavofcreserve25;       /* SSAVOFC25 */
    volatile T_u4   ssavofcreserve26;       /* SSAVOFC26 */
    volatile T_u4   ssavofcreserve27;       /* SSAVOFC27 */
    volatile T_u4   ssavofcreserve28;       /* SSAVOFC28 */
    volatile T_u4   ssavofcreserve29;       /* SSAVOFC29 */
    volatile T_u4   ssavofcreserve30;       /* SSAVOFC30 */
    volatile T_u4   ssavofcreserve31;       /* SSAVOFC31 */
    volatile T_u4   ssavofcreserve32;       /* SSAVOFC32 */
    volatile T_u4   ssavofcreserve33;       /* SSAVOFC33 */
    volatile T_u4   ssavofcreserve34;       /* SSAVOFC34 */
    volatile T_u4   ssavofcreserve35;       /* SSAVOFC35 */
    volatile T_u4   ssavofcreserve36;       /* SSAVOFC36 */
    volatile T_u4   ssavofcreserve37;       /* SSAVOFC37 */
    volatile T_u4   ssavofcreserve38;       /* SSAVOFC38 */
    volatile T_u4   ssavofcreserve39;       /* SSAVOFC39 */
    volatile T_u4   SSAVOFC40;              /* SSAVOFC40 */
    volatile T_u4   ssavofcreserve41;       /* SSAVOFC41 */
    volatile T_u4   ssavofcreserve42;       /* SSAVOFC42 */
    volatile T_u4   ssavofcreserve43;       /* SSAVOFC43 */
    volatile T_u4   ssavofcreserve44;       /* SSAVOFC44 */
    volatile T_u4   ssavofcreserve45;       /* SSAVOFC45 */
    volatile T_u4   ssavofcreserve46;       /* SSAVOFC46 */
    volatile T_u4   ssavofcreserve47;       /* SSAVOFC47 */
    volatile T_u4   ssavofcreserve48;       /* SSAVOFC48 */
    volatile T_u4   ssavofcreserve49;       /* SSAVOFC49 */
    volatile T_u4   ssavofcreserve50;       /* SSAVOFC50 */
    volatile T_u4   ssavofcreserve51;       /* SSAVOFC51 */
    volatile T_u4   ssavofcreserve52;       /* SSAVOFC52 */
    volatile T_u4   ssavofcreserve53;       /* SSAVOFC53 */
    volatile T_u4   ssavofcreserve54;       /* SSAVOFC54 */
    volatile T_u4   ssavofcreserve55;       /* SSAVOFC55 */
    volatile T_u4   ssavofcreserve56;       /* SSAVOFC56 */
    volatile T_u4   ssavofcreserve57;       /* SSAVOFC57 */
    volatile T_u4   ssavofcreserve58;       /* SSAVOFC58 */
    volatile T_u4   ssavofcreserve59;       /* SSAVOFC59 */
    volatile T_u4   ssavofcreserve60;       /* SSAVOFC60 */
    volatile T_u4   ssavofcreserve61;       /* SSAVOFC61 */
    volatile T_u4   ssavofcreserve62;       /* SSAVOFC62 */
    volatile T_u4   ssavofcreserve63;       /* SSAVOFC63 */
};

#ifndef __R_RFD_USE_STUB__   /* For Normal Code */
    #define SSA    (*(volatile struct SSAFlags *)0xFF322100UL)
#else   /* __R_RFD_USE_STUB__ */
    extern struct   SSAFlags    base_SSA;
    #define SSA    (*(volatile struct SSAFlags *)&base_SSA)
#endif

/* SSAVOFCn */
#define R_RFD_FLAG_SSAVOFC0     (SSA.SSAVOFC0)
#define R_RFD_FLAG_SSAVOFC1     (SSA.SSAVOFC1)
#define R_RFD_FLAG_SSAVOFC7     (SSA.SSAVOFC7)
#define R_RFD_FLAG_SSAVOFC8     (SSA.SSAVOFC8)
#define R_RFD_FLAG_SSAVOFC9     (SSA.SSAVOFC9)
#define R_RFD_FLAG_SSAVOFC10    (SSA.SSAVOFC10)
#define R_RFD_FLAG_SSAVOFC11    (SSA.SSAVOFC11)
#define R_RFD_FLAG_SSAVOFC12    (SSA.SSAVOFC12)
#define R_RFD_FLAG_SSAVOFC13    (SSA.SSAVOFC13)
#define R_RFD_FLAG_SSAVOFC14    (SSA.SSAVOFC14)
#define R_RFD_FLAG_SSAVOFC15    (SSA.SSAVOFC15)
#define R_RFD_FLAG_SSAVOFC16    (SSA.SSAVOFC16)
#define R_RFD_FLAG_SSAVOFC17    (SSA.SSAVOFC17)
#define R_RFD_FLAG_SSAVOFC18    (SSA.SSAVOFC18)
#define R_RFD_FLAG_SSAVOFC40    (SSA.SSAVOFC40)

/**********************************************************************************************************************
    Definition of Block Protection Area0 Flags for RH850/U2x
**********************************************************************************************************************/

struct  BPA0Flags                           /* !MISRA-C 2012 rule 2.4 (QAC(RCMA) message 1755) */
{
    volatile T_u4   BPA0VOFC0;              /* BPA0VOFC0  */
    volatile T_u4   BPA0VOFC1;              /* BPA0VOFC1  */
    volatile T_u4   BPA0VOFC2;              /* BPA0VOFC2  */
    volatile T_u4   BPA0VOFC3;              /* BPA0VOFC3  */
    volatile T_u4   BPA0VOFC4;              /* BPA0VOFC4  */
    volatile T_u4   BPA0VOFC5;              /* BPA0VOFC5  */
    volatile T_u4   BPA0VOFC6;              /* BPA0VOFC6  */
    volatile T_u4   BPA0VOFC7;              /* BPA0VOFC7  */
    volatile T_u4   bpa0vofcreserve8;       /* BPA0VOFC8  */
    volatile T_u4   bpa0vofcreserve9;       /* BPA0VOFC9  */
    volatile T_u4   bpa0vofcreserve10;      /* BPA0VOFC10 */
    volatile T_u4   bpa0vofcreserve11;      /* BPA0VOFC11 */
    volatile T_u4   bpa0vofcreserve12;      /* BPA0VOFC12 */
    volatile T_u4   bpa0vofcreserve13;      /* BPA0VOFC13 */
    volatile T_u4   bpa0vofcreserve14;      /* BPA0VOFC14 */
    volatile T_u4   BPA0VOFC15;             /* BPA0VOFC15 */
    volatile T_u4   BPA0VOFC16;             /* BPA0VOFC16 */
    volatile T_u4   BPA0VOFC17;             /* BPA0VOFC17 */
    volatile T_u4   BPA0VOFC18;             /* BPA0VOFC18 */
    volatile T_u4   BPA0VOFC19;             /* BPA0VOFC19 */
    volatile T_u4   BPA0VOFC20;             /* BPA0VOFC20 */
    volatile T_u4   BPA0VOFC21;             /* BPA0VOFC21 */
    volatile T_u4   BPA0VOFC22;             /* BPA0VOFC22 */
    volatile T_u4   BPA0VOFC23;             /* BPA0VOFC23 */
    volatile T_u4   BPA0VOFC24;             /* BPA0VOFC24 */
    volatile T_u4   BPA0VOFC25;             /* BPA0VOFC25 */
    volatile T_u4   BPA0VOFC26;             /* BPA0VOFC26 */
    volatile T_u4   BPA0VOFC27;             /* BPA0VOFC27 */
    volatile T_u4   BPA0VOFC28;             /* BPA0VOFC28 */
    volatile T_u4   BPA0VOFC29;             /* BPA0VOFC29 */
    volatile T_u4   BPA0VOFC30;             /* BPA0VOFC30 */
    volatile T_u4   BPA0VOFC31;             /* BPA0VOFC31 */
    volatile T_u4   bpa0vofcreserve32;      /* BPA0VOFC32 */
    volatile T_u4   bpa0vofcreserve33;      /* BPA0VOFC33 */
    volatile T_u4   bpa0vofcreserve34;      /* BPA0VOFC34 */
    volatile T_u4   bpa0vofcreserve35;      /* BPA0VOFC35 */
    volatile T_u4   bpa0vofcreserve36;      /* BPA0VOFC36 */
    volatile T_u4   bpa0vofcreserve37;      /* BPA0VOFC37 */
    volatile T_u4   bpa0vofcreserve38;      /* BPA0VOFC38 */
    volatile T_u4   BPA0VOFC39;             /* BPA0VOFC39 */
    volatile T_u4   bpa0vofcreserve40;      /* BPA0VOFC40 */
    volatile T_u4   bpa0vofcreserve41;      /* BPA0VOFC41 */
    volatile T_u4   bpa0vofcreserve42;      /* BPA0VOFC42 */
    volatile T_u4   bpa0vofcreserve43;      /* BPA0VOFC43 */
    volatile T_u4   bpa0vofcreserve44;      /* BPA0VOFC44 */
    volatile T_u4   bpa0vofcreserve45;      /* BPA0VOFC45 */
    volatile T_u4   bpa0vofcreserve46;      /* BPA0VOFC46 */
    volatile T_u4   bpa0vofcreserve47;      /* BPA0VOFC47 */
    volatile T_u4   bpa0vofcreserve48;      /* BPA0VOFC48 */
    volatile T_u4   bpa0vofcreserve49;      /* BPA0VOFC49 */
    volatile T_u4   bpa0vofcreserve50;      /* BPA0VOFC50 */
    volatile T_u4   bpa0vofcreserve51;      /* BPA0VOFC51 */
    volatile T_u4   bpa0vofcreserve52;      /* BPA0VOFC52 */
    volatile T_u4   bpa0vofcreserve53;      /* BPA0VOFC53 */
    volatile T_u4   bpa0vofcreserve54;      /* BPA0VOFC54 */
    volatile T_u4   bpa0vofcreserve55;      /* BPA0VOFC55 */
    volatile T_u4   bpa0vofcreserve56;      /* BPA0VOFC56 */
    volatile T_u4   bpa0vofcreserve57;      /* BPA0VOFC57 */
    volatile T_u4   bpa0vofcreserve58;      /* BPA0VOFC58 */
    volatile T_u4   bpa0vofcreserve59;      /* BPA0VOFC59 */
    volatile T_u4   bpa0vofcreserve60;      /* BPA0VOFC60 */
    volatile T_u4   bpa0vofcreserve61;      /* BPA0VOFC61 */
    volatile T_u4   bpa0vofcreserve62;      /* BPA0VOFC62 */
    volatile T_u4   bpa0vofcreserve63;      /* BPA0VOFC63 */
};

#ifndef __R_RFD_USE_STUB__   /* For Normal Code */
    #define BPA0    (*(volatile struct BPA0Flags *)0xFF323100UL)
#else   /* __R_RFD_USE_STUB__ */
    extern struct   BPA0Flags   base_BPA0;
    #define BPA0    (*(volatile struct BPA0Flags *)&base_BPA0)
#endif

/* BPA0VOFCn */
#define R_RFD_FLAG_BPA0VOFC0    (BPA0.BPA0VOFC0)
#define R_RFD_FLAG_BPA0VOFC1    (BPA0.BPA0VOFC1)
#define R_RFD_FLAG_BPA0VOFC2    (BPA0.BPA0VOFC2)
#define R_RFD_FLAG_BPA0VOFC3    (BPA0.BPA0VOFC3)
#define R_RFD_FLAG_BPA0VOFC4    (BPA0.BPA0VOFC4)
#define R_RFD_FLAG_BPA0VOFC5    (BPA0.BPA0VOFC5)
#define R_RFD_FLAG_BPA0VOFC6    (BPA0.BPA0VOFC6)
#define R_RFD_FLAG_BPA0VOFC7    (BPA0.BPA0VOFC7)
#define R_RFD_FLAG_BPA0VOFC15   (BPA0.BPA0VOFC15)
#define R_RFD_FLAG_BPA0VOFC16   (BPA0.BPA0VOFC16)
#define R_RFD_FLAG_BPA0VOFC17   (BPA0.BPA0VOFC17)
#define R_RFD_FLAG_BPA0VOFC18   (BPA0.BPA0VOFC18)
#define R_RFD_FLAG_BPA0VOFC19   (BPA0.BPA0VOFC19)
#define R_RFD_FLAG_BPA0VOFC20   (BPA0.BPA0VOFC20)
#define R_RFD_FLAG_BPA0VOFC21   (BPA0.BPA0VOFC21)
#define R_RFD_FLAG_BPA0VOFC22   (BPA0.BPA0VOFC22)
#define R_RFD_FLAG_BPA0VOFC23   (BPA0.BPA0VOFC23)
#define R_RFD_FLAG_BPA0VOFC24   (BPA0.BPA0VOFC24)
#define R_RFD_FLAG_BPA0VOFC25   (BPA0.BPA0VOFC25)
#define R_RFD_FLAG_BPA0VOFC26   (BPA0.BPA0VOFC26)
#define R_RFD_FLAG_BPA0VOFC27   (BPA0.BPA0VOFC27)
#define R_RFD_FLAG_BPA0VOFC28   (BPA0.BPA0VOFC28)
#define R_RFD_FLAG_BPA0VOFC29   (BPA0.BPA0VOFC29)
#define R_RFD_FLAG_BPA0VOFC30   (BPA0.BPA0VOFC30)
#define R_RFD_FLAG_BPA0VOFC31   (BPA0.BPA0VOFC31)
#define R_RFD_FLAG_BPA0VOFC39   (BPA0.BPA0VOFC39)

/**********************************************************************************************************************
    Definition of Block Protection Area1 Flags for RH850/U2x
**********************************************************************************************************************/

struct  BPA1Flags                           /* !MISRA-C 2012 rule 2.4 (QAC(RCMA) message 1755) */
{
    volatile T_u4   BPA1VOFC0;              /* BPA1VOFC0  */
    volatile T_u4   BPA1VOFC1;              /* BPA1VOFC1  */
    volatile T_u4   BPA1VOFC2;              /* BPA1VOFC2  */
    volatile T_u4   BPA1VOFC3;              /* BPA1VOFC3  */
    volatile T_u4   BPA1VOFC4;              /* BPA1VOFC4  */
    volatile T_u4   BPA1VOFC5;              /* BPA1VOFC5  */
    volatile T_u4   BPA1VOFC6;              /* BPA1VOFC6  */
    volatile T_u4   BPA1VOFC7;              /* BPA1VOFC7  */
    volatile T_u4   bpa1vofcreserve8;       /* BPA1VOFC8  */
    volatile T_u4   bpa1vofcreserve9;       /* BPA1VOFC9  */
    volatile T_u4   bpa1vofcreserve10;      /* BPA1VOFC10 */
    volatile T_u4   bpa1vofcreserve11;      /* BPA1VOFC11 */
    volatile T_u4   bpa1vofcreserve12;      /* BPA1VOFC12 */
    volatile T_u4   bpa1vofcreserve13;      /* BPA1VOFC13 */
    volatile T_u4   bpa1vofcreserve14;      /* BPA1VOFC14 */
    volatile T_u4   bpa1vofcreserve15;      /* BPA1VOFC15 */
    volatile T_u4   BPA1VOFC16;             /* BPA1VOFC16 */
    volatile T_u4   BPA1VOFC17;             /* BPA1VOFC17 */
    volatile T_u4   BPA1VOFC18;             /* BPA1VOFC18 */
    volatile T_u4   BPA1VOFC19;             /* BPA1VOFC19 */
    volatile T_u4   BPA1VOFC20;             /* BPA1VOFC20 */
    volatile T_u4   BPA1VOFC21;             /* BPA1VOFC21 */
    volatile T_u4   BPA1VOFC22;             /* BPA1VOFC22 */
    volatile T_u4   BPA1VOFC23;             /* BPA1VOFC23 */
    volatile T_u4   BPA1VOFC24;             /* BPA1VOFC24 */
    volatile T_u4   BPA1VOFC25;             /* BPA1VOFC25 */
    volatile T_u4   BPA1VOFC26;             /* BPA1VOFC26 */
    volatile T_u4   BPA1VOFC27;             /* BPA1VOFC27 */
    volatile T_u4   BPA1VOFC28;             /* BPA1VOFC28 */
    volatile T_u4   BPA1VOFC29;             /* BPA1VOFC29 */
    volatile T_u4   BPA1VOFC30;             /* BPA1VOFC30 */
    volatile T_u4   BPA1VOFC31;             /* BPA1VOFC31 */
    volatile T_u4   bpa1vofcreserve32;      /* BPA1VOFC32 */
    volatile T_u4   bpa1vofcreserve33;      /* BPA1VOFC33 */
    volatile T_u4   bpa1vofcreserve34;      /* BPA1VOFC34 */
    volatile T_u4   bpa1vofcreserve35;      /* BPA1VOFC35 */
    volatile T_u4   bpa1vofcreserve36;      /* BPA1VOFC36 */
    volatile T_u4   bpa1vofcreserve37;      /* BPA1VOFC37 */
    volatile T_u4   bpa1vofcreserve38;      /* BPA1VOFC38 */
    volatile T_u4   bpa1vofcreserve39;      /* BPA1VOFC39 */
    volatile T_u4   bpa1vofcreserve40;      /* BPA1VOFC40 */
    volatile T_u4   bpa1vofcreserve41;      /* BPA1VOFC41 */
    volatile T_u4   bpa1vofcreserve42;      /* BPA1VOFC42 */
    volatile T_u4   bpa1vofcreserve43;      /* BPA1VOFC43 */
    volatile T_u4   bpa1vofcreserve44;      /* BPA1VOFC44 */
    volatile T_u4   bpa1vofcreserve45;      /* BPA1VOFC45 */
    volatile T_u4   bpa1vofcreserve46;      /* BPA1VOFC46 */
    volatile T_u4   bpa1vofcreserve47;      /* BPA1VOFC47 */
    volatile T_u4   bpa1vofcreserve48;      /* BPA1VOFC48 */
    volatile T_u4   bpa1vofcreserve49;      /* BPA1VOFC49 */
    volatile T_u4   bpa1vofcreserve50;      /* BPA1VOFC50 */
    volatile T_u4   bpa1vofcreserve51;      /* BPA1VOFC51 */
    volatile T_u4   bpa1vofcreserve52;      /* BPA1VOFC52 */
    volatile T_u4   bpa1vofcreserve53;      /* BPA1VOFC53 */
    volatile T_u4   bpa1vofcreserve54;      /* BPA1VOFC54 */
    volatile T_u4   bpa1vofcreserve55;      /* BPA1VOFC55 */
    volatile T_u4   bpa1vofcreserve56;      /* BPA1VOFC56 */
    volatile T_u4   bpa1vofcreserve57;      /* BPA1VOFC57 */
    volatile T_u4   bpa1vofcreserve58;      /* BPA1VOFC58 */
    volatile T_u4   bpa1vofcreserve59;      /* BPA1VOFC59 */
    volatile T_u4   bpa1vofcreserve60;      /* BPA1VOFC60 */
    volatile T_u4   bpa1vofcreserve61;      /* BPA1VOFC61 */
    volatile T_u4   bpa1vofcreserve62;      /* BPA1VOFC62 */
    volatile T_u4   bpa1vofcreserve63;      /* BPA1VOFC63 */
};

#ifndef __R_RFD_USE_STUB__   /* For Normal Code */
    #define BPA1    (*(volatile struct BPA1Flags *)0xFF340900UL)
#else   /* __R_RFD_USE_STUB__ */
    extern struct   BPA1Flags   base_BPA1;
    #define BPA1    (*(volatile struct BPA1Flags *)&base_BPA1)
#endif

/* BPA1VOFCn */
#define R_RFD_FLAG_BPA1VOFC0     (BPA1.BPA1VOFC0)
#define R_RFD_FLAG_BPA1VOFC1     (BPA1.BPA1VOFC1)
#define R_RFD_FLAG_BPA1VOFC2     (BPA1.BPA1VOFC2)
#define R_RFD_FLAG_BPA1VOFC3     (BPA1.BPA1VOFC3)
#define R_RFD_FLAG_BPA1VOFC4     (BPA1.BPA1VOFC4)
#define R_RFD_FLAG_BPA1VOFC5     (BPA1.BPA1VOFC5)
#define R_RFD_FLAG_BPA1VOFC6     (BPA1.BPA1VOFC6)
#define R_RFD_FLAG_BPA1VOFC7     (BPA1.BPA1VOFC7)
#define R_RFD_FLAG_BPA1VOFC16    (BPA1.BPA1VOFC16)
#define R_RFD_FLAG_BPA1VOFC17    (BPA1.BPA1VOFC17)
#define R_RFD_FLAG_BPA1VOFC18    (BPA1.BPA1VOFC18)
#define R_RFD_FLAG_BPA1VOFC19    (BPA1.BPA1VOFC19)
#define R_RFD_FLAG_BPA1VOFC20    (BPA1.BPA1VOFC20)
#define R_RFD_FLAG_BPA1VOFC21    (BPA1.BPA1VOFC21)
#define R_RFD_FLAG_BPA1VOFC22    (BPA1.BPA1VOFC22)
#define R_RFD_FLAG_BPA1VOFC23    (BPA1.BPA1VOFC23)
#define R_RFD_FLAG_BPA1VOFC24    (BPA1.BPA1VOFC24)
#define R_RFD_FLAG_BPA1VOFC25    (BPA1.BPA1VOFC25)
#define R_RFD_FLAG_BPA1VOFC26    (BPA1.BPA1VOFC26)
#define R_RFD_FLAG_BPA1VOFC27    (BPA1.BPA1VOFC27)
#define R_RFD_FLAG_BPA1VOFC28    (BPA1.BPA1VOFC28)
#define R_RFD_FLAG_BPA1VOFC29    (BPA1.BPA1VOFC29)
#define R_RFD_FLAG_BPA1VOFC30    (BPA1.BPA1VOFC30)
#define R_RFD_FLAG_BPA1VOFC31    (BPA1.BPA1VOFC31)

/**********************************************************************************************************************
    Definition of Switch Area Flags for RH850/U2x
**********************************************************************************************************************/

/* Invalid side of Switch Area */
#define R_RFD_SWA_BASE_FACI0    0xFF374000UL
#define R_RFD_CVA_ADDRESS       0xFF374200UL

struct SWAFlags                         /* !MISRA-C 2012 rule 2.4 (QAC(RCMA) message 1755) */
{                                       /* !CERT-C rule DCL06 / QAC message 3132           */
    volatile T_u4   AnPC;               /* A0PC/A1PC    */
    volatile T_u4   AnES;               /* A0ES/A1ES    */
    volatile T_u4   AnEC;               /* A0ES/A1ES    */
    volatile T_u4   swareserve00[5];    /* Reserved     */
    volatile T_u4   TES;                /* TES          */
    volatile T_u4   TEC;                /* TEC          */
    volatile T_u4   swareserve01[6];    /* Reserved     */
    volatile T_u4   swareserve02[112];  /* Reserved     */
    volatile T_u4   CVA;                /* CVA          */
    volatile T_u4   SVA;                /* SVA          */
    volatile T_u4   BVA0;               /* BVA0         */
    volatile T_u4   BVA1;               /* BVA1         */
    volatile T_u4   swareserve03[4];    /* Reserved     */
                                        /* swa0reserve04[376]   */
};

#ifndef __R_RFD_USE_STUB__   /* For Normal Code */
    #define SWA     (*(volatile struct SWAFlags *)0xFF374000UL)
#else   /* __R_RFD_USE_STUB__ */
    extern struct   SWAFlags    base_SWA;
    #define SWA     (*(volatile struct SWAFlags *)&base_SWA)
#endif

/* SWA */
#define R_RFD_FLAG_SWAAnPC  (SWA.AnPC)
#define R_RFD_FLAG_SWAAnES  (SWA.AnES)
#define R_RFD_FLAG_SWAAnEC  (SWA.AnEC)
#define R_RFD_FLAG_SWATES   (SWA.TES)
#define R_RFD_FLAG_SWATEC   (SWA.TEC)
#define R_RFD_FLAG_SWACVA   (SWA.CVA)
#define R_RFD_FLAG_SWASVA   (SWA.SVA)
#define R_RFD_FLAG_SWABVA0  (SWA.BVA0)
#define R_RFD_FLAG_SWABVA1  (SWA.BVA1)

/**********************************************************************************************************************
    Definition of Tag Area Flags for RH850/U2x
**********************************************************************************************************************/

/* Invalid side of Switch Area */
#define R_RFD_TAG_BASE_FACI0    0xFF374800UL
#define R_RFD_TAG_VAF_FACI0     0xFF374A00UL

struct TAGFlags                         /* !MISRA-C 2012 rule 2.4 (QAC(RCMA) message 1755) */
{                                       /* !CERT-C rule DCL06 (QAC message 3132)           */
    volatile T_u4   VAPC;               /* VAPC     */
    volatile T_u4   tagreserve00[127];  /* Reserved */
    volatile T_u4   VAF;                /* VAF      */
                                        /* tagreserve01[383]    */
};

#ifndef __R_RFD_USE_STUB__   /* For Normal Code */
    #define TAG     (*(volatile struct TAGFlags *)0xFF374800UL)
#else   /* __R_RFD_USE_STUB__ */
    extern struct   TAGFlags    base_TAG;
    #define TAG     (*(volatile struct TAGFlags *)&base_TAG)
#endif

/* TAG */
#define R_RFD_FLAG_TAGVAPC  (TAG.VAPC)
#define R_RFD_FLAG_TAGVAF   (TAG.VAF)

/**********************************************************************************************************************
    Definition of Valid or Invalid value for Hardware Property Area/Switch Area, Tag Area for RH850/U2x
**********************************************************************************************************************/

#define R_RFD_VALUE_VALID_AREA0         0xA55A5AA5UL
#define R_RFD_VALUE_VALID_AREA1         0x5AA5A55AUL

#define R_RFD_VALUE_WRITTEN_COMPLETELY  0x5AA5A55AUL

/**********************************************************************************************************************
    Definition of DFECC for RH850/U2x
**********************************************************************************************************************/
struct DFECCRegisters           /* !MISRA-C 2012 rule 2.4 (QAC(RCMA) message 1755) */
{
    #ifndef __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__ /* DFECC Registers RH850/U2Ax */
        volatile T_u4   DFECCCTL;   /* Data Flash ECC control register                  */
        volatile T_u4   DFERSTR;    /* Data Flash error status register                 */
        volatile T_u4   DFERSTC;    /* Data Flash error status clear register           */
        volatile T_u4   DFOVFSTR;   /* Data Flash error overflow status register        */
        volatile T_u4   DFOVFSTC;   /* Data Flash error overflow status clear register  */
        volatile T_u4   DFERRINT;   /* Data Flash error notification control register   */
        volatile T_u4   DFTSTCTL;   /* Data flash test control register                 */
        volatile T_u4   DFKCPROT;   /* Data Flash ECC key code register                 */
    #else /* DFECC Registers RH850/U2Bx */
        volatile T_u4   DFECCCTL;       /* Data Flash ECC control register                  */
        volatile T_u4   DFSERSTR;       /* Data Flash 1-bit error status register           */
        volatile T_u4   DFDERSTR;       /* Data Flash 2-bit error status register           */    
        volatile T_u4   DFSERSTC;       /* Data Flash 1-bit error status clear register     */
        volatile T_u4   DFDERSTC;       /* Data Flash 2-bit error status clear register     */
        volatile T_u4   DFOVFSTR;       /* Data Flash error overflow status register        */
        volatile T_u4   DFOVFSTC;       /* Data Flash error overflow status clear register  */
        volatile T_u4   DFERRINT;       /* Data Flash error notification control register   */
        volatile T_u4   DFSEADR0;       /* Data Flash 1st 1-bit error address register      */
        volatile T_u4   DFSEADR1;       /* Data Flash 2nd 1-bit error address register      */
        volatile T_u4   DFSEADR2;       /* Data Flash 3rd 1-bit error address register      */
        volatile T_u4   DFSEADR3;       /* Data Flash 4th 1-bit error address register      */
        volatile T_u1   reserve00[48];  /* Reserved                                         */
        volatile T_u4   DFDEADR;        /* Data Flash 2-bit error address register          */
        volatile T_u1   reserve01[12];  /* Reserved                                         */
        volatile T_u4   DFSESPID0;      /* Data Flash 1st 1-bit error SPID register         */
        volatile T_u4   DFSESPIDC0;     /* Data Flash 1st 1-bit error SPID clear register   */
        volatile T_u4   DFSESPID1;      /* Data Flash 2nd 1-bit error SPID register         */
        volatile T_u4   DFSESPIDC1;     /* Data Flash 2nd 1-bit error SPID clear register   */
        volatile T_u4   DFSESPID2;      /* Data Flash 3rd 1-bit error SPID register         */
        volatile T_u4   DFSESPIDC2;     /* Data Flash 3rd 1-bit error SPID clear register   */
        volatile T_u4   DFSESPID3;      /* Data Flash 4th 1-bit error SPID register         */
        volatile T_u4   DFSESPIDC3;     /* Data Flash 4th 1-bit error SPID clear register   */
        volatile T_u1   reserve02[96];  /* Reserved                                         */
        volatile T_u4   DFDESPID;       /* Data flash 2-bit error SPID register             */
        volatile T_u4   DFDESPIDC;      /* Data flash 2-bit error SPID clear register       */
        volatile T_u4   DFTSTCTL;       /* Data flash test control register                 */
        volatile T_u4   DFKCPROT;       /* Data Flash ECC key code register                 */
    #endif/* DFECC Registers */
};
    
#ifndef __R_RFD_USE_STUB__   /* For Normal Code */
    #define DFECCBase   (*(volatile struct DFECCRegisters *)R_RFD_BASE_ADDRESS_DFECC)
#else   /* __R_RFD_USE_STUB__ */
    extern  struct  DFECCRegisters  base_DFECC;
    #define DFECCBase   (*(volatile struct DFECCRegisters *)&base_DFECC)
#endif

/* DFECC */
#ifndef __RH850_PROVIDED_MULTI_STAGE_ADDRESS_BUFFER__/* DFECC RH850/U2Ax */
    #define R_RFD_REG_DFECCCTL  (DFECCBase.DFECCCTL)
    #define R_RFD_REG_DFERSTR   (DFECCBase.DFERSTR)
    #define R_RFD_REG_DFERSTC   (DFECCBase.DFERSTC)
    #define R_RFD_REG_DFOVFSTR  (DFECCBase.DFOVFSTR)
    #define R_RFD_REG_DFOVFSTC  (DFECCBase.DFOVFSTC)
    #define R_RFD_REG_DFERRINT  (DFECCBase.DFERRINT)
    #define R_RFD_REG_DFEADR    (DFECCBase.DFEADR)
    #define R_RFD_REG_DFTSTCTL  (DFECCBase.DFTSTCTL)
    #define R_RFD_REG_DFKCPROT  (DFECCBase.DFKCPROT)

    #define R_RFD_VALUE_DFERSTR_SEDF    0x00000001UL
    #define R_RFD_VALUE_DFERSTR_DEDF    0x00000002UL
    #define R_RFD_VALUE_DFERSTC_ERRCLR  0x00000001UL    
#else /* DFECC RH850/U2Bx */
    #define R_RFD_REG_DFECCCTL   (DFECCBase.DFECCCTL)
    #define R_RFD_REG_DFSERSTR   (DFECCBase.DFSERSTR)
    #define R_RFD_REG_DFDERSTR   (DFECCBase.DFDERSTR)
    #define R_RFD_REG_DFSERSTC   (DFECCBase.DFSERSTC)
    #define R_RFD_REG_DFDERSTC   (DFECCBase.DFDERSTC)
    #define R_RFD_REG_DFOVFSTR   (DFECCBase.DFOVFSTR)
    #define R_RFD_REG_DFOVFSTC   (DFECCBase.DFOVFSTC)
    #define R_RFD_REG_DFERRINT   (DFECCBase.DFERRINT)
    #define R_RFD_REG_DFSEADR0   (DFECCBase.DFSEADR0)
    #define R_RFD_REG_DFSEADR1   (DFECCBase.DFSEADR1)
    #define R_RFD_REG_DFSEADR2   (DFECCBase.DFSEADR2)
    #define R_RFD_REG_DFSEADR3   (DFECCBase.DFSEADR3)
    #define R_RFD_REG_DFDEADR    (DFECCBase.DFDEADR)
    #define R_RFD_REG_DFSESPID0  (DFECCBase.DFSESPID0)
    #define R_RFD_REG_DFSESPID1  (DFECCBase.DFSESPID1)
    #define R_RFD_REG_DFSESPID2  (DFECCBase.DFSESPID2)
    #define R_RFD_REG_DFSESPID3  (DFECCBase.DFSESPID3)
    #define R_RFD_REG_DFSESPIDC0 (DFECCBase.DFSESPIDC0)
    #define R_RFD_REG_DFSESPIDC1 (DFECCBase.DFSESPIDC1)
    #define R_RFD_REG_DFSESPIDC2 (DFECCBase.DFSESPIDC2)
    #define R_RFD_REG_DFSESPIDC3 (DFECCBase.DFSESPIDC3)
    #define R_RFD_REG_DFDESPID   (DFECCBase.DFDESPID)
    #define R_RFD_REG_DFDESPIDC  (DFECCBase.DFDESPIDC)
    #define R_RFD_REG_DFTSTCTL   (DFECCBase.DFTSTCTL)
    #define R_RFD_REG_DFKCPROT   (DFECCBase.DFKCPROT)

    #define R_RFD_VALUE_DFSERSTR_SEDF0    0x00000001UL
    #define R_RFD_VALUE_DFSERSTR_SEDF1    0x00000002UL
    #define R_RFD_VALUE_DFSERSTR_SEDF2    0x00000004UL
    #define R_RFD_VALUE_DFSERSTR_SEDF3    0x00000008UL

    #define R_RFD_VALUE_DFDERSTR_DEDF     0x00000001UL
    #define R_RFD_VALUE_DFSERSTC_SSTCLR   0x0000000FUL
    #define R_RFD_VALUE_DFDERSTC_DSTCLR   0x00000001UL
#endif/* DFECC */

#endif  /* R_RFD_DEVICE_H */
