/*==============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                           */
/* Module       = MemAccMemMap.h                                                */
/*==============================================================================*/
/*                                  COPYRIGHT                                   */
/*==============================================================================*/
/* Copyright(c) 2024 Renesas Electronics Corporation. All rights reserved.      */
/*==============================================================================*/
/* Purpose:                                                                     */
/* Provision for sections for Memory Mapping                                    */
/*                                                                              */
/*==============================================================================*/
/*                                                                              */
/* Unless otherwise agreed upon in writing between your company and             */
/* Renesas Electronics Corporation the following shall apply!                   */
/*                                                                              */
/* Warranty Disclaimer                                                          */
/*                                                                              */
/* There is no warranty of any kind whatsoever granted by Renesas. Any          */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed   */
/* or implied, including but not limited to those for non-infringement of       */
/* intellectual property, merchantability and/or fitness for the particular     */
/* purpose.                                                                     */
/*                                                                              */
/* Renesas shall not have any obligation to maintain, service or provide bug    */
/* fixes for the supplied Product(s) and/or the Application.                    */
/*                                                                              */
/* Each User is solely responsible for determining the appropriateness of       */
/* using the Product(s) and assumes all risks associated with its exercise      */
/* of rights under this Agreement, including, but not limited to the risks      */
/* and costs of program errors, compliance with applicable laws, damage to      */
/* or loss of data, programs or equipment, and unavailability or                */
/* interruption of operations.                                                  */
/*                                                                              */
/* Limitation of Liability                                                      */
/*                                                                              */
/* In no event shall Renesas be liable to the User for any incidental,          */
/* consequential, indirect, or punitive damage (including but not limited       */
/* to lost profits) regardless of whether such liability is based on breach     */
/* of contract, tort, strict liability, breach of warranties, failure of        */
/* essential purpose or otherwise and even if advised of the possibility of     */
/* such damages. Renesas shall not be liable for any services or products       */
/* provided by third party vendors, developers or consultants identified or     */
/* referred to the User by Renesas in connection with the Product(s) and/or     */
/* the Application.                                                             */
/*                                                                              */
/*==============================================================================*/
/* Environment:                                                                 */
/*              Devices:        X2x                                             */
/*==============================================================================*/

/*********************************************************************************
**                      Revision Control History                                **
*********************************************************************************/
/*
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header
 * 1.1.0:  30/06/2025:  Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 * 1.0.1:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL
 *                       Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024  : Update SW-VERSION
 *                       for Ver22.02.00/Ver22.02.00.D Final Release
 * 0.0.1:  14/08/2024  : Initial Version

 */
/********************************************************************************/

/*********************************************************************************
**                      Include Section                                         **
*********************************************************************************/

/*********************************************************************************
**                      Version Information                                     **
*********************************************************************************/
/*
 * AUTOSAR specification version information
 */
#define MEMACC_MEMMAP_AR_RELEASE_MAJOR_VERSION      4
#define MEMACC_MEMMAP_AR_RELEASE_MINOR_VERSION      8
#define MEMACC_MEMMAP_AR_RELEASE_REVISION_VERSION   0

/*
 * File version information
 */
#define MEMACC_MEMMAP_SW_MAJOR_VERSION   1
#define MEMACC_MEMMAP_SW_MINOR_VERSION   1
#define MEMACC_MEMMAP_SW_PATCH_VERSION   0

/*********************************************************************************
**                      Global Symbols                                          **
*********************************************************************************/

/*********************************************************************************
**                      Global Data Types                                       **
*********************************************************************************/

/*********************************************************************************
**                      Module section mapping                                  **
*********************************************************************************/
/*
 * The symbol 'START_WITH_IF' is undefined.
 *
 * Thus, the preprocessor continues searching for defined symbols
 * This first #ifdef makes integration of delivered parts of MemAccMemMap.h
 * easier because every supplier starts with #elif
 */
#if defined (START_WITH_IF)
/* -------------------------------------------------------------------------- */
/*             MemAcc                                                         */
/* -------------------------------------------------------------------------- */
#elif defined (MEMACC_START_SEC_VAR_INIT_BOOLEAN)
   #ifdef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_BOOLEAN_SEC_STARTED
     #undef  MEMACC_START_SEC_VAR_INIT_BOOLEAN
     #define DEFAULT_START_SEC_VAR_1BIT
   #endif
#elif defined (MEMACC_STOP_SEC_VAR_INIT_BOOLEAN)
   #ifndef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_BOOLEAN_SEC_STARTED
     #undef  MEMACC_STOP_SEC_VAR_INIT_BOOLEAN
     #define DEFAULT_STOP_SEC_VAR_1BIT
   #endif

#elif defined (MEMACC_START_SEC_VAR_NO_INIT_BOOLEAN)
   #ifdef VAR_NO_INIT_BOOLEAN_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_BOOLEAN_SEC_STARTED
     #undef  MEMACC_START_SEC_VAR_NO_INIT_BOOLEAN
     #define DEFAULT_START_SEC_VAR_NO_INIT_1BIT
   #endif
#elif defined (MEMACC_STOP_SEC_VAR_NO_INIT_BOOLEAN)
   #ifndef VAR_NO_INIT_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_BOOLEAN_SEC_STARTED
     #undef  MEMACC_STOP_SEC_VAR_NO_INIT_BOOLEAN
     #define DEFAULT_STOP_SEC_VAR_NO_INIT_1BIT
   #endif

#elif defined (MEMACC_START_SEC_VAR_NO_INIT_32)
   #ifdef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_32_SEC_STARTED
     #undef  MEMACC_START_SEC_VAR_NO_INIT_32
     #define DEFAULT_START_SEC_VAR_NO_INIT_32BIT
   #endif
#elif defined (MEMACC_STOP_SEC_VAR_NO_INIT_32)
   #ifndef VAR_NO_INIT_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_32_SEC_STARTED
     #undef  MEMACC_STOP_SEC_VAR_NO_INIT_32
     #define DEFAULT_STOP_SEC_VAR_NO_INIT_32BIT
   #endif
#elif defined (MEMACC_START_SEC_VAR_NO_INIT_8)
   #ifdef VAR_NO_INIT_8_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_8_SEC_STARTED
     #undef  MEMACC_START_SEC_VAR_NO_INIT_8
     #define DEFAULT_START_SEC_VAR_NO_INIT_8BIT
   #endif
#elif defined (MEMACC_STOP_SEC_VAR_NO_INIT_8)
   #ifndef VAR_NO_INIT_8_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_8_SEC_STARTED
     #undef  MEMACC_STOP_SEC_VAR_NO_INIT_8
     #define DEFAULT_STOP_SEC_VAR_NO_INIT_8BIT
   #endif
#elif defined (MEMACC_START_SEC_VAR_INIT_PTR)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  MEMACC_START_SEC_VAR_INIT_PTR
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED
   #endif
#elif defined (MEMACC_STOP_SEC_VAR_INIT_PTR)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  MEMACC_STOP_SEC_VAR_INIT_PTR
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED
   #endif

#elif defined (MEMACC_START_SEC_VAR_INIT_UNSPECIFIED)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  MEMACC_START_SEC_VAR_INIT_UNSPECIFIED
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED
   #endif
#elif defined (MEMACC_STOP_SEC_VAR_INIT_UNSPECIFIED)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  MEMACC_STOP_SEC_VAR_INIT_UNSPECIFIED
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED
   #endif

#elif defined (MEMACC_START_SEC_VAR_NO_INIT_UNSPECIFIED)
   #ifdef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  MEMACC_START_SEC_VAR_NO_INIT_UNSPECIFIED
     #define DEFAULT_START_SEC_VAR_NO_INIT_UNSPECIFIED
   #endif
#elif defined (MEMACC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
   #ifndef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  MEMACC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
     #define DEFAULT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
   #endif

#elif defined (MEMACC_START_SEC_VAR_NO_INIT_PTR)
   #ifdef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_PTR_SEC_STARTED
     #undef  MEMACC_START_SEC_VAR_NO_INIT_PTR
     #define DEFAULT_START_SEC_VAR_NO_INIT_PTR
   #endif
#elif defined (MEMACC_STOP_SEC_VAR_NO_INIT_PTR)
   #ifndef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_PTR_SEC_STARTED
     #undef  MEMACC_STOP_SEC_VAR_NO_INIT_PTR
     #define DEFAULT_STOP_SEC_VAR_NO_INIT_PTR
   #endif

#elif defined (MEMACC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
   #ifdef CONFIG_DATA_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define CONFIG_DATA_UNSPECIFIED_SEC_STARTED
     #undef  MEMACC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
     #pragma ghs startdata
     #pragma ghs section rodata=".MEMACC_CFG_DATA_UNSPECIFIED"
   #endif
#elif defined (MEMACC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
   #ifndef CONFIG_DATA_UNSPECIFIED_SEC_STARTED
      #error "Memory section is not started"
   #else
     #undef  CONFIG_DATA_UNSPECIFIED_SEC_STARTED
     #undef  MEMACC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
     #define DEFAULT_STOP_SEC_CONST_UNSPECIFIED
   #endif

#elif defined (MEMACC_START_SEC_PUBLIC_CODE)
   #ifdef PUBLIC_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define PUBLIC_CODE_SEC_STARTED
     #undef  MEMACC_START_SEC_PUBLIC_CODE
     #pragma ghs section text=".MEMACC_PUBLIC_CODE_ROM"
   #endif
#elif defined (MEMACC_STOP_SEC_PUBLIC_CODE)
   #ifndef PUBLIC_CODE_SEC_STARTED
      #error "Memory section is not started"
   #else
     #undef  PUBLIC_CODE_SEC_STARTED
     #undef  MEMACC_STOP_SEC_PUBLIC_CODE
     #define DEFAULT_STOP_SEC_CODE
   #endif

#elif defined (MEMACC_START_SEC_PRIVATE_CODE)
   #ifdef PRIVATE_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define PRIVATE_CODE_SEC_STARTED
     #undef  MEMACC_START_SEC_PRIVATE_CODE
     #pragma ghs section text=".MEMACC_PRIVATE_CODE_ROM"
   #endif
#elif defined (MEMACC_STOP_SEC_PRIVATE_CODE)
   #ifndef PRIVATE_CODE_SEC_STARTED
      #error "Memory section is not started"
   #else
     #undef  PRIVATE_CODE_SEC_STARTED
     #undef  MEMACC_STOP_SEC_PRIVATE_CODE
     #define DEFAULT_STOP_SEC_CODE
   #endif
#elif defined (MEMACC_STOP_SEC_PRIVATERAM_CODE)
   #ifndef PRIVATE_CODE_SEC_STARTED
      #error "Memory section is not started"
   #else
     #undef  PRIVATE_CODE_SEC_STARTED
     #undef  MEMACC_STOP_SEC_PRIVATERAM_CODE
     #define DEFAULT_STOP_SEC_CODE
   #endif

#elif defined (MEMACC_START_SEC_APPL_CODE)
   #undef      MEMACC_START_SEC_APPL_CODE
   #pragma ghs section text=".MEMACC_APPL_CODE_ROM"
#elif defined (MEMACC_STOP_SEC_APPL_CODE)
   #undef      MEMACC_STOP_SEC_APPL_CODE
   #define DEFAULT_STOP_SEC_CODE

#elif defined (MEMACC_START_SEC_CODE_FAST)
   #ifdef FAST_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define FAST_CODE_SEC_STARTED
     #undef  MEMACC_START_SEC_CODE_FAST
     #pragma ghs section text=".MEMACC_FAST_CODE_ROM"
   #endif
#elif defined (MEMACC_STOP_SEC_CODE_FAST)
   #ifndef FAST_CODE_SEC_STARTED
      #error "Memory section is not started"
   #else
     #undef  FAST_CODE_SEC_STARTED
     #undef  MEMACC_STOP_SEC_CODE_FAST
     #define DEFAULT_STOP_SEC_CODE
   #endif
/* -------------------------------------------------------------------------- */
/* End of module section mapping                                              */
/* -------------------------------------------------------------------------- */
#else
  #error "MemAcc_MemMap.h: No valid section define found"
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
   #pragma ghs section bss=".NOINIT_RAM_1BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NO_INIT_1BIT)
   #undef      DEFAULT_STOP_SEC_VAR_NO_INIT_1BIT
   #pragma ghs section bss=default
   #pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_NO_INIT_8BIT)
   #undef      DEFAULT_START_SEC_VAR_NO_INIT_8BIT
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_8BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NO_INIT_8BIT)
   #undef      DEFAULT_STOP_SEC_VAR_NO_INIT_8BIT
   #pragma ghs section bss=default
   #pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_NO_INIT_16BIT)
   #undef      DEFAULT_START_SEC_VAR_NO_INIT_16BIT
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_16BIT"
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

#elif defined (DEFAULT_SPI_LOC_DATARAM1_START)
   #undef      DEFAULT_SPI_LOC_DATARAM1_START
   #pragma ghs startdata
   #pragma ghs section data=".LOCAL_RAM_AREA1"
#elif defined (DEFAULT_SPI_LOC_DATARAM1_STOP)
   #undef      DEFAULT_SPI_LOC_DATARAM1_STOP
   #pragma ghs section data=default
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

