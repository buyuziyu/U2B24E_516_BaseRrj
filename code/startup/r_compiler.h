/******************************************************************************* 
* DISCLAIMER 
* This software is supplied by Renesas Electronics Corporation and is only  
* intended for use with Renesas products. No other uses are authorized. This  
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE  
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. 
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS  
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE  
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software. By using this software, 
* you agree to the additional terms and conditions found by accessing the  
* following link: 
* http://www.renesas.com/disclaimer 
* 
* Copyright (C) 2012, 2014 Renesas Electronics Corporation. All rights reserved.     
*******************************************************************************/
#ifndef R_COMPILER_H
#define R_COMPILER_H

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/
#include "iodefine.h"
/*****************************************************************************
 Macro definitions
 *****************************************************************************/
#ifndef TRUE                                /* conditional check */
  #define TRUE      1
#endif

#ifndef FALSE                               /* conditional check */
  #define FALSE     0
#endif

#ifndef HIGH
  #define HIGH      1
#endif

#ifndef LOW
  #define LOW       0
#endif

#ifndef NULL
  #define NULL ((void *)0UL)
#endif

#ifndef R_OK                                /* conditional check */
  #define R_OK      0
#endif

#ifndef E_OK
  #define E_OK      0
#endif

#ifndef E_NOT_OK
  #define E_NOT_OK 1
#endif


#define ERR00                      0x00000001UL
#define ERR01                      0x00000002UL
#define ERR02                      0x00000004UL
#define ERR03                      0x00000008UL
#define ERR04                      0x00000010UL
#define ERR05                      0x00000020UL
#define ERR06                      0x00000040UL
#define ERR07                      0x00000080UL
#define ERR08                      0x00000100UL
#define ERR09                      0x00000200UL
#define ERR10                      0x00000400UL
#define ERR11                      0x00000800UL
#define ERR12                      0x00001000UL
#define ERR13                      0x00002000UL
#define ERR14                      0x00004000UL
#define ERR15                      0x00008000UL
#define ERR16                      0x00010000UL
#define ERR17                      0x00020000UL
#define ERR18                      0x00040000UL
#define ERR19                      0x00080000UL
#define ERR20                      0x00100000UL
#define ERR21                      0x00200000UL
#define ERR22                      0x00400000UL
#define ERR23                      0x00800000UL
#define ERR24                      0x01000000UL
#define ERR25                      0x02000000UL
#define ERR26                      0x04000000UL
#define ERR27                      0x08000000UL
#define ERR28                      0x10000000UL
#define ERR29                      0x20000000UL
#define ERR30                      0x40000000UL
#define ERR31                      0x80000000UL

#define REG08(reg)                                 (*(volatile uint8 *)(reg))
#define REG16(reg)                                 (*(volatile uint16 *)(reg))
#define REG32(reg)                                 (*(volatile uint32 *)(reg))

#define PE_CPU0                       0UL
#define PE_CPU1                       1UL
#define PE_CPU2                       2UL
#define PE_CPU3                       3UL

__inline asm unsigned long GetPEID(void)
{
  stsr 0, r10, 2
}

/* Inline assembler support for HALT instruction */
#define ASM_HALT() __asm("halt")
/* Inline assembler support for NOP instruction */
#define ASM_NOP() __asm("nop")
// #define ENABLE_INTERRUPT()        __asm("ei")
// #define DISABLE_INTERRUPT()       __asm("di")
/* Inline assembler support for SYNCI instruction */
#define EXECUTE_SYNCI() __asm("synci")
/* Inline assembler support for syncp instruction */
#define EXECUTE_SYNCP()           __asm("syncp")
/* Inline assembler support for syncm instruction */
#define EXECUTE_SYNCM()           __asm("syncm")
/* Utilize the GHS specific intrinsic functions for accessing the cpu system
registers */
#define LDSR                           __LDSR
#define STSR                           __STSR
void __LDSR(int regID, int selID, unsigned int val);
unsigned int __STSR(int regID, int selID);                            

#define R_LSH(n,m)                     ((n)<<(m))
#define R_RSH(n,m)                     ((n)>>(m))

/*****************************************************************************
 Typedef definitions
 *****************************************************************************/
#ifdef USE_EXT_DATATYPE
#include "Platform_Types.h"            /* platform specific type definitions */
#else
/*
 * integer data types
 */
typedef signed char         sint8;          /*        -128 .. +127           */
typedef unsigned char       uint8;          /*           0 .. 255            */
typedef signed short        sint16;         /*      -32768 .. +32767         */
typedef unsigned short      uint16;         /*           0 .. 65535          */
typedef signed long         sint32;         /* -2147483648 .. +2147483647    */
typedef unsigned long       uint32;         /*           0 .. 4294967295     */
typedef signed long long    sint64;         /* 63 bit + 1 bit sign           */
typedef unsigned long long  uint64;         /* 64 bit                        */
typedef float               float32;
typedef double              float64;

typedef unsigned long       uint8_least;    /* At least 8 bit                */
typedef unsigned long       uint16_least;   /* At least 16 bit               */
typedef unsigned long       uint32_least;   /* At least 32 bit               */
typedef signed long         sint8_least;    /* At least 7 bit + 1 bit sign   */
typedef signed long         sint16_least;   /* At least 15 bit + 1 bit sign  */
typedef signed long         sint32_least;   /* At least 31 bit + 1 bit sign  */
// typedef unsigned char       boolean;        /* for use with TRUE/FALSE       */
// #define ENABLE_INTERRUPT()        __EI()
// #define DISABLE_INTERRUPT()       __DI()

#endif

/*****************************************************************************
 Global variables
 *****************************************************************************/

/*****************************************************************************
 Global functions
 *****************************************************************************/

#endif  /* R_COMPILER_H */
