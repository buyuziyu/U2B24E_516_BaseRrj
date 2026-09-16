/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = Spi_MemMap.h                                                */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2024 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Provision for sections for Memory Mapping                                  */
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
/*
 * 2.5.1:  30/06/2025:  Remove SW-VERSION in file header
 * 2.5.0:     30/06/2025     Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:     31/05/2025     Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:     30/04/2025     Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:     31/03/2025     Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.2.0:     31/12/2024     Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2      31/10/2024     Update SW-VERSION to 2.1.2
 * 2.1.1      24/07/2024     Update SW-VERSION to 2.1.1
 * 2.1.0      23/02/2024     Update SW-VERSION to 2.1.0
 *            09/04/2024     Change SPI_START_SEC_CONFIG_DATA_UNSPECIFIED to
 *                           SPI_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
 *                           Change SPI_STOP_SEC_CONFIG_DATA_UNSPECIFIED to
 *                           SPI_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
 *                           Update SPI_MEMMAP_SW_PATCH_VERSION to 3
 *            04/04/2024     Update SW-VERSION up to 2.0.3
 *            13/03/2024     Change SPI_START_SEC_CONFIG_DATA_ to
 *                           SPI_START_SEC_CONFIG_DATA_POSTBUILD_.
 *                           Change SPI_STOP_SEC_CONFIG_DATA_ to
 *                           SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_
 *                           Change SPI_START_SEC_CONFIG_DATA_BOOLEAN to
 *                           SPI_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
 *                           Change SPI_STOP_SEC_CONFIG_DATA_BOOLEAN to
 *                            SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
 * 2.0.1      12/10/2023     Update CONFIG_DATA_ to CONFIG_DATA_POSTBUILD
 *            22/09/2023     Initial Version
 */
/******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/*
* AUTOSAR specification version information
*/
#define SPI_MEMMAP_AR_RELEASE_MAJOR_VERSION      4
#define SPI_MEMMAP_AR_RELEASE_MINOR_VERSION      8
#define SPI_MEMMAP_AR_RELEASE_REVISION_VERSION   0

/*
* File version information
*/
#define SPI_MEMMAP_SW_MAJOR_VERSION   2
#define SPI_MEMMAP_SW_MINOR_VERSION   5
#define SPI_MEMMAP_SW_PATCH_VERSION   0

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Module section mapping                                **
*******************************************************************************/
/*
* The symbol 'START_WITH_IF' is undefined.
*
* Thus, the preprocessor continues searching for defined symbols
* This first #ifdef makes integration of delivered parts of Spi_MemMap.h
* easier because every supplier starts with #elif
*/
#if defined (START_WITH_IF)

/* -------------------------------------------------------------------------- */
/*             SPI                                                            */
/* -------------------------------------------------------------------------- */

#elif defined (SPI_START_SEC_VAR_INIT_BOOLEAN)
#ifdef VAR_BOOLEAN_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_BOOLEAN_SEC_STARTED
#undef  SPI_START_SEC_VAR_INIT_BOOLEAN
#define DEFAULT_START_SEC_VAR_1BIT
#endif
#elif defined (SPI_STOP_SEC_VAR_INIT_BOOLEAN)
#ifndef VAR_BOOLEAN_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_BOOLEAN_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_INIT_BOOLEAN
#define DEFAULT_STOP_SEC_VAR_1BIT
#endif

#elif defined (SPI_START_SEC_VAR_NO_INIT_BOOLEAN)
#ifdef VAR_NO_INIT_BOOLEAN_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_NO_INIT_BOOLEAN_SEC_STARTED
#undef  SPI_START_SEC_VAR_NO_INIT_BOOLEAN
#define DEFAULT_START_SEC_VAR_NO_INIT_1BIT
#endif
#elif defined (SPI_STOP_SEC_VAR_NO_INIT_BOOLEAN)
#ifndef VAR_NO_INIT_BOOLEAN_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_NO_INIT_BOOLEAN_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_NO_INIT_BOOLEAN
#define DEFAULT_STOP_SEC_VAR_NO_INIT_1BIT
#endif

#elif defined (SPI_START_SEC_VAR_FAST_INIT_BOOLEAN)
#ifdef VAR_FAST_BOOLEAN_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_FAST_BOOLEAN_SEC_STARTED
#undef  SPI_START_SEC_VAR_FAST_INIT_BOOLEAN
#define DEFAULT_START_SEC_VAR_FAST_1BIT
#endif
#elif defined (SPI_STOP_SEC_VAR_FAST_INIT_BOOLEAN)
#ifndef VAR_FAST_BOOLEAN_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_FAST_BOOLEAN_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_FAST_INIT_BOOLEAN
#define DEFAULT_STOP_SEC_VAR_FAST_1BIT
#endif

#elif defined (SPI_START_SEC_VAR_INIT_8)
#ifdef VAR_8_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_8_SEC_STARTED
#undef  SPI_START_SEC_VAR_INIT_8
#define DEFAULT_START_SEC_VAR_8BIT
#endif
#elif defined (SPI_STOP_SEC_VAR_INIT_8)
#ifndef VAR_8_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_8_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_INIT_8
#define DEFAULT_STOP_SEC_VAR_8BIT
#endif

#elif defined (SPI_START_SEC_VAR_NO_INIT_8)
#ifdef VAR_NO_INIT_8_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_NO_INIT_8_SEC_STARTED
#undef  SPI_START_SEC_VAR_NO_INIT_8
#define DEFAULT_START_SEC_VAR_NO_INIT_8BIT
#endif
#elif defined (SPI_STOP_SEC_VAR_NO_INIT_8)
#ifndef VAR_NO_INIT_8_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_NO_INIT_8_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_NO_INIT_8
#define DEFAULT_STOP_SEC_VAR_NO_INIT_8BIT
#endif

#elif defined (SPI_START_SEC_VAR_FAST_INIT_8)
#ifdef VAR_FAST_8_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_FAST_8_SEC_STARTED
#undef  SPI_START_SEC_VAR_FAST_INIT_8
#define DEFAULT_START_SEC_VAR_FAST_8BIT
#endif
#elif defined (SPI_STOP_SEC_VAR_FAST_INIT_8)
#ifndef VAR_FAST_8_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_FAST_8_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_FAST_INIT_8
#define DEFAULT_STOP_SEC_VAR_FAST_8BIT
#endif

#elif defined (SPI_START_SEC_VAR_INIT_16)
#ifdef VAR_16_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_16_SEC_STARTED
#undef  SPI_START_SEC_VAR_INIT_16
#define DEFAULT_START_SEC_VAR_16BIT
#endif
#elif defined (SPI_STOP_SEC_VAR_INIT_16)
#ifndef VAR_16_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_16_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_INIT_16
#define DEFAULT_STOP_SEC_VAR_16BIT
#endif

#elif defined (SPI_START_SEC_VAR_NO_INIT_16)
#ifdef VAR_NO_INIT_16_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_NO_INIT_16_SEC_STARTED
#undef  SPI_START_SEC_VAR_NO_INIT_16
#define DEFAULT_START_SEC_VAR_NO_INIT_16BIT
#endif
#elif defined (SPI_STOP_SEC_VAR_NO_INIT_16)
#ifndef VAR_NO_INIT_16_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_NO_INIT_16_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_NO_INIT_16
#define DEFAULT_STOP_SEC_VAR_NO_INIT_16BIT
#endif

#elif defined (SPI_START_SEC_VAR_FAST_INIT_16)
#ifdef VAR_FAST_16_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_FAST_16_SEC_STARTED
#undef  SPI_START_SEC_VAR_FAST_INIT_16
#define DEFAULT_START_SEC_VAR_FAST_16BIT
#endif
#elif defined (SPI_STOP_SEC_VAR_FAST_INIT_16)
#ifndef VAR_FAST_16_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_FAST_16_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_FAST_INIT_16
#define DEFAULT_STOP_SEC_VAR_FAST_16BIT
#endif

#elif defined (SPI_START_SEC_VAR_INIT_32)
#ifdef VAR_32_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_32_SEC_STARTED
#undef  SPI_START_SEC_VAR_INIT_32
#define DEFAULT_START_SEC_VAR_32BIT
#endif
#elif defined (SPI_STOP_SEC_VAR_INIT_32)
#ifndef VAR_32_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_32_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_INIT_32
#define DEFAULT_STOP_SEC_VAR_32BIT
#endif

#elif defined (SPI_START_SEC_VAR_NO_INIT_32)
#ifdef VAR_NO_INIT_32_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_NO_INIT_32_SEC_STARTED
#undef  SPI_START_SEC_VAR_NO_INIT_32
#define DEFAULT_START_SEC_VAR_NO_INIT_32BIT
#endif
#elif defined (SPI_STOP_SEC_VAR_NO_INIT_32)
#ifndef VAR_NO_INIT_32_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_NO_INIT_32_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_NO_INIT_32
#define DEFAULT_STOP_SEC_VAR_NO_INIT_32BIT
#endif

#elif defined (SPI_START_SEC_VAR_FAST_INIT_32)
#ifdef VAR_FAST_32_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_FAST_32_SEC_STARTED
#undef  SPI_START_SEC_VAR_FAST_INIT_32
#define DEFAULT_START_SEC_VAR_FAST_32BIT
#endif
#elif defined (SPI_STOP_SEC_VAR_FAST_INIT_32)
#ifndef VAR_FAST_32_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_FAST_32_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_FAST_INIT_32
#define DEFAULT_STOP_SEC_VAR_FAST_32BIT
#endif

#elif defined (SPI_START_SEC_VAR_NO_INIT_64)
#ifdef VAR_NO_INIT_64_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_NO_INIT_64_SEC_STARTED
#undef  SPI_START_SEC_VAR_NO_INIT_64
#define DEFAULT_START_SEC_VAR_NO_INIT_64BIT
#endif
#elif defined (SPI_STOP_SEC_VAR_NO_INIT_64)
#ifndef VAR_NO_INIT_64_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_NO_INIT_64_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_NO_INIT_64
#define DEFAULT_STOP_SEC_VAR_NO_INIT_64BIT
#endif

#elif defined (SPI_START_SEC_VAR_INIT_UNSPECIFIED)
#ifdef VAR_UNSPECIFIED_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_UNSPECIFIED_SEC_STARTED
#undef  SPI_START_SEC_VAR_INIT_UNSPECIFIED
#define DEFAULT_START_SEC_VAR_UNSPECIFIED
#endif
#elif defined (SPI_STOP_SEC_VAR_INIT_UNSPECIFIED)
#ifndef VAR_UNSPECIFIED_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_UNSPECIFIED_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_INIT_UNSPECIFIED
#define DEFAULT_STOP_SEC_VAR_UNSPECIFIED
#endif

#elif defined (SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED)
#ifdef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
#undef  SPI_START_SEC_VAR_NO_INIT_UNSPECIFIED
#define DEFAULT_START_SEC_VAR_NO_INIT_UNSPECIFIED
#endif
#elif defined (SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
#ifndef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#define DEFAULT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#endif

#elif defined (SPI_START_SEC_VAR_NO_INIT_PTR)
#ifdef VAR_NO_INIT_PTR_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_NO_INIT_PTR_SEC_STARTED
#undef  SPI_START_SEC_VAR_NO_INIT_PTR
#define DEFAULT_START_SEC_VAR_NO_INIT_PTR
#endif
#elif defined (SPI_STOP_SEC_VAR_NO_INIT_PTR)
#ifndef VAR_NO_INIT_PTR_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_NO_INIT_PTR_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_NO_INIT_PTR
#define DEFAULT_STOP_SEC_VAR_NO_INIT_PTR
#endif

#elif defined (SPI_START_SEC_VAR_FAST_INIT_UNSPECIFIED)
#ifdef VAR_FAST_UNSPECIFIED_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_FAST_UNSPECIFIED_SEC_STARTED
#undef  SPI_START_SEC_VAR_FAST_INIT_UNSPECIFIED
#define DEFAULT_START_SEC_VAR_FAST_UNSPECIFIED
#endif
#elif defined (SPI_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED)
#ifndef VAR_FAST_UNSPECIFIED_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_FAST_UNSPECIFIED_SEC_STARTED
#undef  SPI_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
#define DEFAULT_STOP_SEC_VAR_FAST_UNSPECIFIED
#endif

#elif defined (SPI_START_SEC_CONFIG_VAR_NO_INIT_UNSPECIFIED)
#ifdef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
#error "Memory section is not stopped"
#else
#define VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
#undef  SPI_START_SEC_CONFIG_VAR_NO_INIT_UNSPECIFIED
#pragma ghs startdata
#pragma ghs section bss=".SPI_CFG_RAM_UNSPECIFIED"
#endif
#elif defined (SPI_STOP_SEC_CONFIG_VAR_NO_INIT_UNSPECIFIED)
#ifndef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
#error "Memory section is not started"
#else
#undef  VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
#undef  SPI_STOP_SEC_CONFIG_VAR_NO_INIT_UNSPECIFIED
#pragma ghs section bss=default
#pragma ghs enddata
#endif

#elif defined (SPI_START_SEC_CONST_BOOLEAN)
#ifdef CONST_BOOLEAN_SEC_STARTED
#error "Memory section is not stopped"
#else
#define CONST_BOOLEAN_SEC_STARTED
#undef  SPI_START_SEC_CONST_BOOLEAN
#define DEFAULT_START_SEC_CONST_1BIT
#endif
#elif defined (SPI_STOP_SEC_CONST_BOOLEAN)
#ifndef CONST_BOOLEAN_SEC_STARTED
#error "Memory section is not started"
#else
#undef  CONST_BOOLEAN_SEC_STARTED
#undef  SPI_STOP_SEC_CONST_BOOLEAN
#define DEFAULT_STOP_SEC_CONST_1BIT
#endif

#elif defined (SPI_START_SEC_CONST_8)
#ifdef CONST_8_SEC_STARTED
#error "Memory section is not stopped"
#else
#define CONST_8_SEC_STARTED
#undef  SPI_START_SEC_CONST_8
#define DEFAULT_START_SEC_CONST_8BIT
#endif
#elif defined (SPI_STOP_SEC_CONST_8)
#ifndef CONST_8_SEC_STARTED
#error "Memory section is not started"
#else
#undef  CONST_8_SEC_STARTED
#undef  SPI_STOP_SEC_CONST_8
#define DEFAULT_STOP_SEC_CONST_8BIT
#endif

#elif defined (SPI_START_SEC_CONST_16)
#ifdef CONST_16_SEC_STARTED
#error "Memory section is not stopped"
#else
#define CONST_16_SEC_STARTED
#undef  SPI_START_SEC_CONST_16
#define DEFAULT_START_SEC_CONST_16BIT
#endif
#elif defined (SPI_STOP_SEC_CONST_16)
#ifndef CONST_16_SEC_STARTED
#error "Memory section is not started"
#else
#undef  CONST_16_SEC_STARTED
#undef  SPI_STOP_SEC_CONST_16
#define DEFAULT_STOP_SEC_CONST_16BIT
#endif

#elif defined (SPI_START_SEC_CONST_32)
#ifdef CONST_32_SEC_STARTED
#error "Memory section is not stopped"
#else
#define CONST_32_SEC_STARTED
#undef  SPI_START_SEC_CONST_32
#define DEFAULT_START_SEC_CONST_32BIT
#endif
#elif defined (SPI_STOP_SEC_CONST_32)
#ifndef CONST_32_SEC_STARTED
#error "Memory section is not started"
#else
#undef  CONST_32_SEC_STARTED
#undef  SPI_STOP_SEC_CONST_32
#define DEFAULT_STOP_SEC_CONST_32BIT
#endif

#elif defined (SPI_START_SEC_CONST_UNSPECIFIED)
#ifdef CONST_UNSPECIFIED_SEC_STARTED
#error "Memory section is not stopped"
#else
#define CONST_UNSPECIFIED_SEC_STARTED
#undef  SPI_START_SEC_CONST_UNSPECIFIED
#define DEFAULT_START_SEC_CONST_UNSPECIFIED
#endif
#elif defined (SPI_STOP_SEC_CONST_UNSPECIFIED)
#ifndef CONST_UNSPECIFIED_SEC_STARTED
#error "Memory section is not started"
#else
#undef  CONST_UNSPECIFIED_SEC_STARTED
#undef  SPI_STOP_SEC_CONST_UNSPECIFIED
#define DEFAULT_STOP_SEC_CONST_UNSPECIFIED
#endif

#elif defined (SPI_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
#ifdef SPI_CONFIG_DATA_POSTBUILD_BOOLEAN_SEC_STARTED
#error "Memory section is not stopped"
#else
#define SPI_CONFIG_DATA_POSTBUILD_BOOLEAN_SEC_STARTED
#undef  SPI_START_SEC_CONFIG_DATA_BOOLEAN
#pragma ghs startdata
#pragma ghs section rodata=".SPI_CFG_DATA_1BIT"
#endif
#elif defined (SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
#ifndef SPI_CONFIG_DATA_POSTBUILD_BOOLEAN_SEC_STARTED
#error "Memory section is not started"
#else
#undef  SPI_CONFIG_DATA_POSTBUILD_BOOLEAN_SEC_STARTED
#undef  SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
#define DEFAULT_STOP_SEC_CONST_1BIT
#endif

#elif defined (SPI_START_SEC_CONFIG_DATA_POSTBUILD_8)
#ifdef SPI_CONFIG_DATA_POSTBUILD_8_SEC_STARTED
#error "Memory section is not stopped"
#else
#define SPI_CONFIG_DATA_POSTBUILD_8_SEC_STARTED
#undef  SPI_START_SEC_CONFIG_DATA_POSTBUILD_8
#pragma ghs startdata
#pragma ghs section rodata=".SPI_CFG_DATA_8BIT"
#endif
#elif defined (SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_8)
#ifndef SPI_CONFIG_DATA_POSTBUILD_8_SEC_STARTED
#error "Memory section is not started"
#else
#undef  SPI_CONFIG_DATA_POSTBUILD_8_SEC_STARTED
#undef  SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#define DEFAULT_STOP_SEC_CONST_8BIT
#endif

#elif defined (SPI_START_SEC_CONFIG_DATA_POSTBUILD_16)
#ifdef SPI_CONFIG_DATA_POSTBUILD_16_SEC_STARTED
#error "Memory section is not stopped"
#else
#define SPI_CONFIG_DATA_POSTBUILD_16_SEC_STARTED
#undef  SPI_START_SEC_CONFIG_DATA_POSTBUILD_16
#pragma ghs startdata
#pragma ghs section rodata=".SPI_CFG_DATA_16BIT"
#endif
#elif defined (SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_16)
#ifndef SPI_CONFIG_DATA_16_SEC_STARTED
#error "Memory section is not started"
#else
#undef  SPI_CONFIG_DATA_POSTBUILD_16_SEC_STARTED
#undef  SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_16
#define DEFAULT_STOP_SEC_CONST_16BIT
#endif

#elif defined (SPI_START_SEC_CONFIG_DATA_POSTBUILD_32)
#ifdef SPI_CONFIG_DATA_POSTBUILD_32_SEC_STARTED
#error "Memory section is not stopped"
#else
#define SPI_CONFIG_DATA_POSTBUILD_32_SEC_STARTED
#undef  SPI_START_SEC_CONFIG_DATA_POSTBUILD_32
#pragma ghs startdata
#pragma ghs section rodata=".SPI_CFG_DATA_32BIT"
#endif
#elif defined (SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_32)
#ifndef SPI_CONFIG_DATA_POSTBUILD_32_SEC_STARTED
#error "Memory section is not started"
#else
#undef  SPI_CONFIG_DATA_POSTBUILD_32_SEC_STARTED
#undef  SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_32
#define DEFAULT_STOP_SEC_CONST_32BIT
#endif

#elif defined (SPI_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
#ifdef SPI_CONFIG_DATA_PREBUILD_UNSPECIFIED_SEC_STARTED
#error "Memory section is not stopped"
#else
#define SPI_CONFIG_DATA_PREBUILD_UNSPECIFIED_SEC_STARTED
#undef  SPI_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#pragma ghs startdata
#pragma ghs section rodata=".SPI_CFG_DATA_UNSPECIFIED"
#endif
#elif defined (SPI_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
#ifndef SPI_CONFIG_DATA_PREBUILD_UNSPECIFIED_SEC_STARTED
#error "Memory section is not started"
#else
#undef  SPI_CONFIG_DATA_PREBUILD_UNSPECIFIED_SEC_STARTED
#undef  SPI_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#define DEFAULT_STOP_SEC_CONST_UNSPECIFIED
#endif

#elif defined (SPI_START_SEC_DBTOC_DATA_UNSPECIFIED)
#ifdef DBTOC_DATA_UNSPECIFIED_SEC_STARTED
#error "Memory section is not stopped"
#else
#define DBTOC_DATA_UNSPECIFIED_SEC_STARTED
#undef  SPI_START_SEC_DBTOC_DATA_UNSPECIFIED
#pragma ghs startdata
#pragma ghs section rodata=".SPI_CFG_DBTOC_UNSPECIFIED"
#endif
#elif defined (SPI_STOP_SEC_DBTOC_DATA_UNSPECIFIED)
#ifndef DBTOC_DATA_UNSPECIFIED_SEC_STARTED
#error "Memory section is not started"
#else
#undef  DBTOC_DATA_UNSPECIFIED_SEC_STARTED
#undef  SPI_STOP_SEC_DBTOC_DATA_UNSPECIFIED
#define DEFAULT_STOP_SEC_CONST_UNSPECIFIED
#endif

#elif defined (SPI_START_SEC_PUBLIC_CODE)
#ifdef PUBLIC_CODE_SEC_STARTED
#error "Memory section is not stopped"
#else
#define PUBLIC_CODE_SEC_STARTED
#undef  SPI_START_SEC_PUBLIC_CODE
#pragma ghs section text=".SPI_PUBLIC_CODE_ROM"
#endif
#elif defined (SPI_STOP_SEC_PUBLIC_CODE)
#ifndef PUBLIC_CODE_SEC_STARTED
#error "Memory section is not started"
#else
#undef  PUBLIC_CODE_SEC_STARTED
#undef  SPI_STOP_SEC_PUBLIC_CODE
#define DEFAULT_STOP_SEC_CODE
#endif

#elif defined (SPI_START_SEC_PRIVATE_CODE)
#ifdef PRIVATE_CODE_SEC_STARTED
#error "Memory section is not stopped"
#else
#define PRIVATE_CODE_SEC_STARTED
#undef  SPI_START_SEC_PRIVATE_CODE
#pragma ghs section text=".SPI_PRIVATE_CODE_ROM"
#endif
#elif defined (SPI_STOP_SEC_PRIVATE_CODE)
#ifndef PRIVATE_CODE_SEC_STARTED
#error "Memory section is not started"
#else
#undef  PRIVATE_CODE_SEC_STARTED
#undef  SPI_STOP_SEC_PRIVATE_CODE
#define DEFAULT_STOP_SEC_CODE
#endif

#elif defined (SPI_START_SEC_APPL_CODE)
#ifdef APPL_CODE_SEC_STARTED
#error "Memory section is not stopped"
#else
#define APPL_CODE_SEC_STARTED
#undef  SPI_START_SEC_APPL_CODE
#pragma ghs section text=".SPI_APPL_CODE_ROM"
#endif
#elif defined (SPI_STOP_SEC_APPL_CODE)
#ifndef APPL_CODE_SEC_STARTED
#error "Memory section is not started"
#else
#undef  APPL_CODE_SEC_STARTED
#undef  SPI_STOP_SEC_APPL_CODE
#define DEFAULT_STOP_SEC_CODE
#endif

#elif defined (SPI_START_SEC_CODE_FAST)
#ifdef ISR_CODE_SEC_STARTED
#error "Memory section is not stopped"
#else
#define ISR_CODE_SEC_STARTED
#undef  SPI_START_SEC_CODE_FAST
#pragma ghs section text=".SPI_FAST_CODE_ROM"
#endif
#elif defined (SPI_STOP_SEC_CODE_FAST)
#ifndef ISR_CODE_SEC_STARTED
#error "Memory section is not started"
#else
#undef  ISR_CODE_SEC_STARTED
#undef  SPI_STOP_SEC_CODE_FAST
#define DEFAULT_STOP_SEC_CODE
#endif

/* For multi core */
#elif defined (SPI_START_SEC_PUBLIC_CODE_GLOBAL)
   #ifdef PUBLIC_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define PUBLIC_CODE_SEC_STARTED
     #undef  SPI_START_SEC_PUBLIC_CODE_GLOBAL
     #pragma ghs section text=".SPI_PUBLIC_CODE_ROM"
   #endif
#elif defined (SPI_STOP_SEC_PUBLIC_CODE_GLOBAL)
   #ifndef PUBLIC_CODE_SEC_STARTED
      #error "Memory section is not started"
   #else
     #undef  PUBLIC_CODE_SEC_STARTED
     #undef  SPI_STOP_SEC_PUBLIC_CODE_GLOBAL
     #define DEFAULT_STOP_SEC_CODE
   #endif
#elif defined (SPI_START_SEC_PUBLIC_CODE_LOCAL)
   #ifdef PUBLIC_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define PUBLIC_CODE_SEC_STARTED
     #undef  SPI_START_SEC_PUBLIC_CODE_LOCAL
     #pragma ghs section text=".SPI_PUBLIC_CODE_ROM"
   #endif
#elif defined (SPI_STOP_SEC_PUBLIC_CODE_LOCAL)
   #ifndef PUBLIC_CODE_SEC_STARTED
      #error "Memory section is not started"
   #else
     #undef  PUBLIC_CODE_SEC_STARTED
     #undef  SPI_STOP_SEC_PUBLIC_CODE_LOCAL
     #define DEFAULT_STOP_SEC_CODE
   #endif
/* End of multi core */

#elif defined (SPI_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
#ifdef SPI_CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
#error "Memory section is not stopped"
#else
#define SPI_CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
#undef  SPI_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#pragma ghs startdata
#pragma ghs section rodata=".SPI_CFG_DATA_UNSPECIFIED"
#endif
#elif defined (SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
#ifndef SPI_CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
#error "Memory section is not started"
#else
#undef  SPI_CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
#undef  SPI_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#define DEFAULT_STOP_SEC_CONST_UNSPECIFIED
#endif

/* -------------------------------------------------------------------------- */
/* End of module section mapping                                              */
/* -------------------------------------------------------------------------- */
#else
#error "Spi_MemMap.h: No valid section define found"
#endif  /* START_WITH_IF */

/*******************************************************************************
**                      Default section mapping                               **
*******************************************************************************/
/* general start of #elif chain whith #if                                     */
#if defined (START_WITH_IF)

/* -------------------------------------------------------------------------- */
/* RAM variables initialized from ROM on reset                                */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_VAR_1BIT)
#undef      DEFAULT_START_SEC_VAR_1BIT
#pragma ghs startdata
#pragma ghs section data=".RAM_1BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_1BIT)
#undef      DEFAULT_STOP_SEC_VAR_1BIT
#pragma ghs section data=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_8BIT)
#undef      DEFAULT_START_SEC_VAR_8BIT
#pragma ghs startdata
#pragma ghs section data=".RAM_8BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_8BIT)
#undef      DEFAULT_STOP_SEC_VAR_8BIT
#pragma ghs section data=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_16BIT)
#undef      DEFAULT_START_SEC_VAR_16BIT
#pragma ghs startdata
#pragma ghs section data=".RAM_16BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_16BIT)
#undef      DEFAULT_STOP_SEC_VAR_16BIT
#pragma ghs section data=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_32BIT)
#undef      DEFAULT_START_SEC_VAR_32BIT
#pragma ghs startdata
#pragma ghs section data=".RAM_32BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_32BIT)
#undef      DEFAULT_STOP_SEC_VAR_32BIT
#pragma ghs section data=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_UNSPECIFIED)
#undef      DEFAULT_START_SEC_VAR_UNSPECIFIED
#pragma ghs startdata
#pragma ghs section data=".RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_UNSPECIFIED)
#undef      DEFAULT_STOP_SEC_VAR_UNSPECIFIED
#pragma ghs section data=default
#pragma ghs enddata

/* -------------------------------------------------------------------------- */
/* RAM variables not initialized                                              */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_VAR_NO_INIT_1BIT)
#undef      DEFAULT_START_SEC_VAR_NO_INIT_1BIT
#pragma ghs startdata
#pragma ghs section bss=".NO_INIT_RAM_1BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NO_INIT_1BIT)
#undef      DEFAULT_STOP_SEC_VAR_NO_INIT_1BIT
#pragma ghs section bss=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_NO_INIT_8BIT)
#undef      DEFAULT_START_SEC_VAR_NO_INIT_8BIT
#pragma ghs startdata
#pragma ghs section bss=".NO_INIT_RAM_8BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NO_INIT_8BIT)
#undef      DEFAULT_STOP_SEC_VAR_NO_INIT_8BIT
#pragma ghs section bss=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_NO_INIT_16BIT)
#undef      DEFAULT_START_SEC_VAR_NO_INIT_16BIT
#pragma ghs startdata
#pragma ghs section bss=".NO_INIT_RAM_16BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NO_INIT_16BIT)
#undef      DEFAULT_STOP_SEC_VAR_NO_INIT_16BIT
#pragma ghs section bss=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_NO_INIT_32BIT)
#undef      DEFAULT_START_SEC_VAR_NO_INIT_32BIT
#pragma ghs startdata
#pragma ghs section bss=".NOINIT_RAM_32BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NO_INIT_32BIT)
#undef      DEFAULT_STOP_SEC_VAR_NO_INIT_32BIT
#pragma ghs section bss=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_NO_INIT_64BIT)
#undef      DEFAULT_START_SEC_VAR_NO_INIT_64BIT
#pragma ghs startdata
#pragma ghs section bss=".NOINIT_RAM_64BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NO_INIT_64BIT)
#undef      DEFAULT_STOP_SEC_VAR_NO_INIT_64BIT
#pragma ghs section bss=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_NO_INIT_UNSPECIFIED)
#undef      DEFAULT_START_SEC_VAR_NO_INIT_UNSPECIFIED
#pragma ghs startdata
#pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
#undef      DEFAULT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#pragma ghs section bss=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_NO_INIT_PTR)
#undef      DEFAULT_START_SEC_VAR_NO_INIT_PTR
#pragma ghs startdata
#pragma ghs section bss=".NOINIT_RAM_PTR"
#elif defined (DEFAULT_STOP_SEC_VAR_NO_INIT_PTR)
#undef      DEFAULT_STOP_SEC_VAR_NO_INIT_PTR
#pragma ghs section bss=default
#pragma ghs enddata

/* -------------------------------------------------------------------------- */
/* RAM variables frequently used or accessed bitwise                          */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_VAR_FAST_1BIT)
#undef      DEFAULT_START_SEC_VAR_FAST_1BIT
#pragma ghs startdata
#pragma ghs section data=".FAST_RAM_1BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_1BIT)
#undef      DEFAULT_STOP_SEC_VAR_FAST_1BIT
#pragma ghs section data=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_FAST_8BIT)
#undef      DEFAULT_START_SEC_VAR_FAST_8BIT
#pragma ghs startdata
#pragma ghs section data=".FAST_RAM_8BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_8BIT)
#undef      DEFAULT_STOP_SEC_VAR_FAST_8BIT
#pragma ghs section data=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_FAST_16BIT)
#undef      DEFAULT_START_SEC_VAR_FAST_16BIT
#pragma ghs startdata
#pragma ghs section data=".FAST_RAM_16BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_16BIT)
#undef      DEFAULT_STOP_SEC_VAR_FAST_16BIT
#pragma ghs section data=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_FAST_32BIT)
#undef      DEFAULT_START_SEC_VAR_FAST_32BIT
#pragma ghs startdata
#pragma ghs section data=".FAST_RAM_32BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_32BIT)
#undef      DEFAULT_STOP_SEC_VAR_FAST_32BIT
#pragma ghs section data=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_FAST_UNSPECIFIED)
#undef      DEFAULT_START_SEC_VAR_FAST_UNSPECIFIED
#pragma ghs startdata
#pragma ghs section data=".FAST_RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_UNSPECIFIED)
#undef      DEFAULT_STOP_SEC_VAR_FAST_UNSPECIFIED
#pragma ghs section data=default
#pragma ghs enddata

/* -------------------------------------------------------------------------- */
/* ROM constants                                                              */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_CONST_1BIT)
#undef      DEFAULT_START_SEC_CONST_1BIT
#pragma ghs startdata
#pragma ghs section rodata=".CONST_ROM_1BIT"
#elif defined (DEFAULT_STOP_SEC_CONST_1BIT)
#undef      DEFAULT_STOP_SEC_CONST_1BIT
#pragma ghs section rodata=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_CONST_8BIT)
#undef      DEFAULT_START_SEC_CONST_8BIT
#pragma ghs startdata
#pragma ghs section rodata=".CONST_ROM_8BIT"
#elif defined (DEFAULT_STOP_SEC_CONST_8BIT)
#undef      DEFAULT_STOP_SEC_CONST_8BIT
#pragma ghs section rodata=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_CONST_16BIT)
#undef      DEFAULT_START_SEC_CONST_16BIT
#pragma ghs startdata
#pragma ghs section rodata=".CONST_ROM_16BIT"
#elif defined (DEFAULT_STOP_SEC_CONST_16BIT)
#undef      DEFAULT_STOP_SEC_CONST_16BIT
#pragma ghs section rodata=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_CONST_32BIT)
#undef      DEFAULT_START_SEC_CONST_32BIT
#pragma ghs startdata
#pragma ghs section rodata=".CONST_ROM_32BIT"
#elif defined (DEFAULT_STOP_SEC_CONST_32BIT)
#undef      DEFAULT_STOP_SEC_CONST_32BIT
#pragma ghs section rodata=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_CONST_UNSPECIFIED)
#undef      DEFAULT_START_SEC_CONST_UNSPECIFIED
#pragma ghs startdata
#pragma ghs section rodata=".CONST_ROM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_CONST_UNSPECIFIED)
#undef      DEFAULT_STOP_SEC_CONST_UNSPECIFIED
#pragma ghs section rodata=default
#pragma ghs enddata
/* -------------------------------------------------------------------------- */
/* ROM FAR constants                                                          */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_CONST_1BIT_FAR)
#undef      DEFAULT_START_SEC_CONST_1BIT_FAR
#pragma ghs startdata
#pragma ghs section rodata=".CONST_FAR_ROM_1BIT"
#elif defined (DEFAULT_STOP_SEC_CONST_1BIT_FAR)
#undef      DEFAULT_STOP_SEC_CONST_1BIT_FAR
#pragma ghs section rodata=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_CONST_8BIT_FAR)
#undef      DEFAULT_START_SEC_CONST_8BIT_FAR
#pragma ghs startdata
#pragma ghs section rodata=".CONST_FAR_ROM_8BIT"
#elif defined (DEFAULT_STOP_SEC_CONST_8BIT_FAR)
#undef      DEFAULT_STOP_SEC_CONST_8BIT_FAR
#pragma ghs section rodata=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_CONST_16BIT_FAR)
#undef      DEFAULT_START_SEC_CONST_16BIT_FAR
#pragma ghs startdata
#pragma ghs section rodata=".CONST_FAR_ROM_16BIT"
#elif defined (DEFAULT_STOP_SEC_CONST_16BIT_FAR)
#undef      DEFAULT_STOP_SEC_CONST_16BIT_FAR
#pragma ghs section rodata=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_CONST_32BIT_FAR)
#undef      DEFAULT_START_SEC_CONST_32BIT_FAR
#pragma ghs startdata
#pragma ghs section rodata=".CONST_FAR_ROM_32BIT"
#elif defined (DEFAULT_STOP_SEC_CONST_32BIT_FAR)
#undef      DEFAULT_STOP_SEC_CONST_32BIT_FAR
#pragma ghs section rodata=default
#pragma ghs enddata

#elif defined (DEFAULT_START_SEC_CONST_UNSPECIFIED_FAR)
#undef      DEFAULT_START_SEC_CONST_UNSPECIFIED_FAR
#pragma ghs startdata
#pragma ghs section rodata=".CONST_FAR_ROM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_CONST_UNSPECIFIED_FAR)
#undef      DEFAULT_STOP_SEC_CONST_UNSPECIFIED_FAR
#pragma ghs section rodata=default
#pragma ghs enddata
/* -------------------------------------------------------------------------- */
/* ROM code                                                                   */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_CODE)
#undef      DEFAULT_START_SEC_CODE
#pragma ghs section text=".DEFAULT_CODE_ROM"
#elif defined (DEFAULT_STOP_SEC_CODE)
#undef      DEFAULT_STOP_SEC_CODE
#pragma ghs section text=default

/* ---------------------------------------------------------------------------*/
/* End of default section mapping                                             */
/* ---------------------------------------------------------------------------*/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif  /* START_WITH_IF */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
