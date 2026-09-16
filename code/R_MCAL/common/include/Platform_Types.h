/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* File name    = Platform_Types.h                                            */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision for platform and compiler dependent types                        */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        X2x                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/* 2.4.1      30/06/2025     Remove the SW-VERSION from header of file
 * 2.3.0      28/02/2025     Update SW-VERSION for
 *                           Ver22.01.00/Ver22.01.00.D U2Cx Release
 * 2.2.1      31/12/2024     Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0      31/12/2024     Update SW-VERSION
 *                           for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.1      27/06/2024     Update SW-VERSION to 2.1.1
 * 2.1.0      23/02/2024     Update SW-VERSION to 2.1.0
 * 2.0.3      15/04/2024     Update SW-VERSION to 2.0.3
 * 2.0.1      22/09/2023     Initial Version
 */
/******************************************************************************/
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification release version information for R21_11 */
#define PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION     4
#define PLATFORM_TYPES_AR_RELEASE_MINOR_VERSION     8
#define PLATFORM_TYPES_AR_RELEASE_REVISION_VERSION  0

/* File version information */
#define PLATFORM_TYPES_SW_MAJOR_VERSION  2
#define PLATFORM_TYPES_SW_MINOR_VERSION  3
#define PLATFORM_TYPES_SW_PATCH_VERSION  0

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/*
 * CPU register type width
 */
#define CPU_TYPE_8        8
#define CPU_TYPE_16       16
#define CPU_TYPE_32       32
#define CPU_TYPE_64       64

/*
 * Bit order definition
 */
#define MSB_FIRST         0                 /* Big endian bit ordering       */
#define LSB_FIRST         1                 /* Little endian bit ordering    */

/*
 * Byte order definition
 */
#define HIGH_BYTE_FIRST   0                 /* Big endian byte ordering      */
#define LOW_BYTE_FIRST    1                 /* Little endian byte ordering   */

/*
 * Platform type and endianess definitions
 */
#define CPU_TYPE            CPU_TYPE_32
#define CPU_BIT_ORDER       LSB_FIRST
#define CPU_BYTE_ORDER      LOW_BYTE_FIRST

/*
 * Interrupt Mode definitions
 */
#define MCAL_ISR_TYPE_TOOLCHAIN  1
#define MCAL_ISR_TYPE_OS         2
#define MCAL_ISR_TYPE_NONE       3

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/*
 * AUTOSAR integer data types
 */
typedef signed char         sint8;          /*        -128 .. +127           */
typedef unsigned char       uint8;          /*           0 .. 255            */
typedef signed short        sint16;         /*      -32768 .. +32767         */
typedef unsigned short      uint16;         /*           0 .. 65535          */
typedef signed long         sint32;         /* -2147483648 .. +2147483647    */
typedef unsigned long       uint32;         /*           0 .. 4294967295     */
typedef signed long long    sint64;         /* 63 bit + 1 bit sign           */
typedef unsigned long long  uint64;         /* 64 bit                        */

typedef unsigned long       uint8_least;    /* At least 8 bit                */
typedef unsigned long       uint16_least;   /* At least 16 bit               */
typedef unsigned long       uint32_least;   /* At least 32 bit               */
typedef signed long         sint8_least;    /* At least 7 bit + 1 bit sign   */
typedef signed long         sint16_least;   /* At least 15 bit + 1 bit sign  */
typedef signed long         sint32_least;   /* At least 31 bit + 1 bit sign  */

typedef float               float32;
typedef double              float64;

typedef _Bool               boolean;

#ifndef true 
  #define true        1
#endif
#ifndef TRUE                                /* conditional check */
  #define TRUE      true
#endif

#ifndef false 
  #define false       0
#endif
#ifndef FALSE                               /* conditional check */
  #define FALSE     false
#endif

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* PLATFORM_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
