/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = Gpt_MemMap.h                                                */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023 - 2025 Renesas Electronics Corporation. All rights reserved.      */
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
 * 2.4.0:  30/06/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00 (D)
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 * 2.3.1:  31/03/2025  : As part of U2B24-E support, following changes is made
 *                       1. Add memory section for Core 4 to Core 6
 * 2.3.0:  28/02/2025  : Update SW-VERSION for
 *                       RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                       Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION to 2.1.2
 * 2.1.1:  24/07/2024  : Update SW-VERSION to 2.1.1
 * 2.1.0:  23/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.3:  11/04/2024  : Update GPT_MEMMAP_SW_PATCH_VERSION to 4
 * 2.0.1:  07/10/2023  : Update memory section from CONFIG_DATA
 *                       to CONFIG_DATA_POSTBUILD
 *         22/09/2023  : Initial Version
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
#define GPT_MEMMAP_AR_RELEASE_MAJOR_VERSION      4
#define GPT_MEMMAP_AR_RELEASE_MINOR_VERSION      8
#define GPT_MEMMAP_AR_RELEASE_REVISION_VERSION   0

/*
 * File version information
 */
#define GPT_MEMMAP_SW_MAJOR_VERSION   2
#define GPT_MEMMAP_SW_MINOR_VERSION   3
#define GPT_MEMMAP_SW_PATCH_VERSION   3

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
 * This first #ifdef makes integration of delivered parts of MemMap.h
 * easier because every supplier starts with #elif
 */
#if defined (START_WITH_IF)

/* -------------------------------------------------------------------------- */
/*             GPT                                                            */
/* -------------------------------------------------------------------------- */
#elif defined (GPT_START_SEC_VAR_INIT_BOOLEAN)
   #ifdef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_START_SEC_VAR_INIT_BOOLEAN
     #define DEFAULT_START_SEC_VAR_1BIT
   #endif
#elif defined (GPT_STOP_SEC_VAR_INIT_BOOLEAN)
   #ifndef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_STOP_SEC_VAR_INIT_BOOLEAN
     #define DEFAULT_STOP_SEC_VAR_1BIT
   #endif

#elif defined (GPT_START_SEC_VAR_INIT_PTR)
  #ifdef VAR_INIT_PTR_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define VAR_INIT_PTR_SEC_STARTED
    #undef  GPT_START_SEC_VAR_INIT_PTR
    #define DEFAULT_START_SEC_VAR_INIT_PTR
  #endif
#elif defined (GPT_STOP_SEC_VAR_INIT_PTR)
  #ifndef VAR_INIT_PTR_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef  VAR_INIT_PTR_SEC_STARTED
    #undef  GPT_STOP_SEC_VAR_INIT_PTR
    #define DEFAULT_STOP_SEC_VAR_INIT_PTR
  #endif

/* Core 0 */
#elif defined (GPT_CORE0_START_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifdef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #define  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE0_START_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE0_START_SEC_VAR_1BIT_LOCAL
   #endif
#elif defined (GPT_CORE0_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifndef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE0_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE0_STOP_SEC_VAR_1BIT_LOCAL
   #endif

/* Core 1 */
#elif defined (GPT_CORE1_START_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifdef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #define  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE1_START_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE1_START_SEC_VAR_1BIT_LOCAL
   #endif
#elif defined (GPT_CORE1_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifndef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE1_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE1_STOP_SEC_VAR_1BIT_LOCAL
   #endif

/* Core 2 */
#elif defined (GPT_CORE2_START_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifdef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #define  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE2_START_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE2_START_SEC_VAR_1BIT_LOCAL
   #endif
#elif defined (GPT_CORE2_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifndef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE2_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE2_STOP_SEC_VAR_1BIT_LOCAL
   #endif

/* Core 3 */
#elif defined (GPT_CORE3_START_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifdef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #define  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE3_START_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE3_START_SEC_VAR_1BIT_LOCAL
   #endif
#elif defined (GPT_CORE3_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifndef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE3_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE3_STOP_SEC_VAR_1BIT_LOCAL
   #endif

/* Core 4 */
#elif defined (GPT_CORE4_START_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifdef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #define  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE4_START_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE4_START_SEC_VAR_1BIT_LOCAL
   #endif
#elif defined (GPT_CORE4_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifndef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE4_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE4_STOP_SEC_VAR_1BIT_LOCAL
   #endif

/* Core 5 */
#elif defined (GPT_CORE5_START_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifdef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #define  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE5_START_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE5_START_SEC_VAR_1BIT_LOCAL
   #endif
#elif defined (GPT_CORE5_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifndef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE5_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE5_STOP_SEC_VAR_1BIT_LOCAL
   #endif

/* Core 6 */
#elif defined (GPT_CORE6_START_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifdef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #define  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE6_START_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE6_START_SEC_VAR_1BIT_LOCAL
   #endif
#elif defined (GPT_CORE6_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL)
   #ifndef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_CORE6_STOP_SEC_VAR_INIT_BOOLEAN_LOCAL
     #define DEFAULT_CORE6_STOP_SEC_VAR_1BIT_LOCAL
   #endif

//
#elif defined (GPT_START_SEC_VAR_INIT_8)
   #ifdef VAR_8_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_8_SEC_STARTED
     #undef  GPT_START_SEC_VAR_INIT_8
     #define DEFAULT_START_SEC_VAR_8BIT
   #endif
#elif defined (GPT_STOP_SEC_VAR_INIT_8)
   #ifndef VAR_8_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_8_SEC_STARTED
     #undef  GPT_STOP_SEC_VAR_INIT_8
     #define DEFAULT_STOP_SEC_VAR_8BIT
   #endif

#elif defined (GPT_START_SEC_VAR_NO_INIT_BOOLEAN)
   #ifdef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_START_SEC_VAR_NO_INIT_BOOLEAN
     #define DEFAULT_START_SEC_VAR_NOINIT_1BIT
   #endif
#elif defined (GPT_STOP_SEC_VAR_NO_INIT_BOOLEAN)
   #ifndef VAR_BOOLEAN_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_BOOLEAN_SEC_STARTED
     #undef  GPT_STOP_SEC_VAR_NO_INIT_BOOLEAN
     #define DEFAULT_STOP_SEC_VAR_NOINIT_1BIT
   #endif

#elif defined (GPT_START_SEC_VAR_NO_INIT_8)
   #ifdef VAR_NOINIT_8_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_8_SEC_STARTED
     #undef  GPT_START_SEC_VAR_NO_INIT_8
     #define DEFAULT_START_SEC_VAR_NOINIT_8BIT
   #endif
#elif defined (GPT_STOP_SEC_VAR_NO_INIT_8)
   #ifndef VAR_NOINIT_8_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_8_SEC_STARTED
     #undef  GPT_STOP_SEC_VAR_NO_INIT_8
     #define DEFAULT_STOP_SEC_VAR_NOINIT_8BIT
   #endif

#elif defined (GPT_START_SEC_VAR_NO_INIT_PTR)
   #ifdef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_START_SEC_VAR_NO_INIT_PTR
     #define DEFAULT_START_SEC_VAR_NO_INIT_PTR
   #endif
#elif defined (GPT_STOP_SEC_VAR_NO_INIT_PTR)
   #ifndef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_STOP_SEC_VAR_NO_INIT_PTR
     #define DEFAULT_STOP_SEC_VAR_NO_INIT_PTR
   #endif

/* Core 0 */
#elif defined (GPT_CORE0_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifdef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE0_START_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE0_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif
#elif defined (GPT_CORE0_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifndef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE0_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE0_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif

/* Core 1 */
#elif defined (GPT_CORE1_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifdef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE1_START_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE1_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif
#elif defined (GPT_CORE1_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifndef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE1_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE1_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif

/* Core 2 */
#elif defined (GPT_CORE2_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifdef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE2_START_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE2_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif
#elif defined (GPT_CORE2_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifndef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE2_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE2_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif

/* Core 3 */
#elif defined (GPT_CORE3_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifdef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE3_START_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE3_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif
#elif defined (GPT_CORE3_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifndef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE3_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE3_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif

/* Core 4 */
#elif defined (GPT_CORE4_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifdef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE4_START_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE4_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif
#elif defined (GPT_CORE4_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifndef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE4_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE4_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif

/* Core 5 */
#elif defined (GPT_CORE5_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifdef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE5_START_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE5_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif
#elif defined (GPT_CORE5_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifndef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE5_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE5_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif

/* Core 6 */
#elif defined (GPT_CORE6_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifdef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE6_START_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE6_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif
#elif defined (GPT_CORE6_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #ifndef VAR_NO_INIT_PTR_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_PTR_SEC_STARTED
     #undef  GPT_CORE6_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
     #define DEFAULT_CORE6_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
   #endif

//
#elif defined (GPT_START_SEC_VAR_NO_INIT_UNSPECIFIED)
   #ifdef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_START_SEC_VAR_NO_INIT_UNSPECIFIED
     #pragma ghs startdata
     #pragma ghs section bss=".GPT_CFG_RAM_UNSPECIFIED"
   #endif
#elif defined (GPT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
   #ifndef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
     #pragma ghs section bss=default
     #pragma ghs enddata
   #endif
/* Core 0 */
#elif defined (GPT_CORE0_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE0_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs startdata
     #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED_CORE0"
   #endif
#elif defined (GPT_CORE0_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE0_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs section bss=default
     #pragma ghs enddata
   #endif

/* Core 1 */
#elif defined (GPT_CORE1_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE1_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs startdata
     #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED_CORE1"
   #endif
#elif defined (GPT_CORE1_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE1_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs section bss=default
     #pragma ghs enddata
   #endif
   
/* Core 2 */
#elif defined (GPT_CORE2_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE2_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs startdata
     #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED_CORE2"
   #endif
#elif defined (GPT_CORE2_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE2_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs section bss=default
     #pragma ghs enddata
   #endif
   
/* Core 3 */
#elif defined (GPT_CORE3_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE3_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs startdata
     #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED_CORE3"
   #endif
#elif defined (GPT_CORE3_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE3_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs section bss=default
     #pragma ghs enddata
   #endif

/* Core 4 */
#elif defined (GPT_CORE4_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE4_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs startdata
     #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED_CORE4"
   #endif
#elif defined (GPT_CORE4_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE4_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs section bss=default
     #pragma ghs enddata
   #endif

/* Core 5 */
#elif defined (GPT_CORE5_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE5_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs startdata
     #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED_CORE5"
   #endif
#elif defined (GPT_CORE5_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE5_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs section bss=default
     #pragma ghs enddata
   #endif

/* Core 6 */
#elif defined (GPT_CORE6_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE6_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs startdata
     #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED_CORE6"
   #endif
#elif defined (GPT_CORE6_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NO_INIT_UNSPECIFIED_SEC_STARTED
     #undef  GPT_CORE6_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #pragma ghs section bss=default
     #pragma ghs enddata
   #endif

#elif defined (GPT_START_SEC_CONST_32)
  #ifdef CONST_32_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define CONST_32_SEC_STARTED
    #undef  GPT_START_SEC_CONST_32
    #define DEFAULT_START_SEC_CONST_32BIT
  #endif
#elif defined (GPT_STOP_SEC_CONST_32)
  #ifndef CONST_32_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef  CONST_32_SEC_STARTED
    #undef  GPT_STOP_SEC_CONST_32
    #define DEFAULT_STOP_SEC_CONST_32BIT
  #endif

#elif defined (GPT_START_SEC_CONST_8)
   #ifdef CONST_8_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define CONST_8_SEC_STARTED
     #undef  GPT_START_SEC_CONST_8
     #define DEFAULT_START_SEC_CONST_8BIT
   #endif
#elif defined (GPT_STOP_SEC_CONST_8)
   #ifndef CONST_8_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  CONST_8_SEC_STARTED
     #undef  GPT_STOP_SEC_CONST_8
     #define DEFAULT_STOP_SEC_CONST_8BIT
   #endif

#elif defined (GPT_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
   #ifdef CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
     #undef  GPT_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
     #pragma ghs startdata
     #pragma ghs section rodata=".GPT_CFG_DATA_UNSPECIFIED"
   #endif
#elif defined (GPT_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
   #ifndef CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
     #undef  GPT_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
     #define DEFAULT_STOP_SEC_CONST_UNSPECIFIED
   #endif

#elif defined (GPT_START_SEC_VAR_INIT_UNSPECIFIED)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  GPT_START_SEC_VAR_INIT_UNSPECIFIED
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED
   #endif
#elif defined (GPT_STOP_SEC_VAR_INIT_UNSPECIFIED)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  GPT_STOP_SEC_VAR_INIT_UNSPECIFIED
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED
   #endif
#elif defined (GPT_START_SEC_PUBLIC_CODE)
   #ifdef PUBLIC_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define PUBLIC_CODE_SEC_STARTED
     #undef  GPT_START_SEC_PUBLIC_CODE
     #pragma ghs section text=".GPT_PUBLIC_CODE_ROM"
   #endif
#elif defined (GPT_STOP_SEC_PUBLIC_CODE)
   #ifndef PUBLIC_CODE_SEC_STARTED
      #error "Memory section is not started"
   #else
     #undef  PUBLIC_CODE_SEC_STARTED
     #undef  GPT_STOP_SEC_PUBLIC_CODE
     #define DEFAULT_STOP_SEC_CODE
   #endif

#elif defined (GPT_START_SEC_PRIVATE_CODE)
   #ifdef PRIVATE_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define PRIVATE_CODE_SEC_STARTED
     #undef  GPT_START_SEC_PRIVATE_CODE
     #pragma ghs section text=".GPT_PRIVATE_CODE_ROM"
   #endif
#elif defined (GPT_STOP_SEC_PRIVATE_CODE)
   #ifndef PRIVATE_CODE_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  PRIVATE_CODE_SEC_STARTED
     #undef  GPT_STOP_SEC_PRIVATE_CODE
     #define DEFAULT_STOP_SEC_CODE
   #endif
#elif defined (GPT_START_SEC_APPL_CODE)
   #ifdef APPL_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define APPL_CODE_SEC_STARTED
     #undef  GPT_START_SEC_APPL_CODE
     #pragma ghs section text=".GPT_APPL_CODE_ROM"
   #endif
#elif defined (GPT_STOP_SEC_APPL_CODE)
   #ifndef APPL_CODE_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  APPL_CODE_SEC_STARTED
     #undef  GPT_STOP_SEC_APPL_CODE
     #define DEFAULT_STOP_SEC_CODE
   #endif

#elif defined (GPT_START_SEC_CODE_FAST)
   #ifdef ISR_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define ISR_CODE_SEC_STARTED
     #undef  GPT_START_SEC_CODE_FAST
     #pragma ghs section text=".GPT_FAST_CODE_ROM"
   #endif
#elif defined (GPT_STOP_SEC_CODE_FAST)
   #ifndef ISR_CODE_SEC_STARTED
      #error "Memory section is not started"
   #else
     #undef  ISR_CODE_SEC_STARTED
     #undef  GPT_STOP_SEC_CODE_FAST
     #define DEFAULT_STOP_SEC_CODE
   #endif
#else
  #error "Gpt_MemMap.h: No valid section define found"
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

#elif defined (DEFAULT_CORE0_START_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE0_START_SEC_VAR_1BIT_LOCAL
   #pragma ghs startdata
   #pragma ghs section data=".RAM_1BIT_CORE0"
#elif defined (DEFAULT_CORE0_STOP_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE0_STOP_SEC_VAR_1BIT_LOCAL
   #pragma ghs section data=default
   #pragma ghs enddata
#elif defined (DEFAULT_CORE1_START_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE1_START_SEC_VAR_1BIT_LOCAL
   #pragma ghs startdata
   #pragma ghs section data=".RAM_1BIT_CORE1"
#elif defined (DEFAULT_CORE1_STOP_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE1_STOP_SEC_VAR_1BIT_LOCAL
   #pragma ghs section data=default
   #pragma ghs enddata
#elif defined (DEFAULT_CORE2_START_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE2_START_SEC_VAR_1BIT_LOCAL
   #pragma ghs startdata
   #pragma ghs section data=".RAM_1BIT_CORE2"
#elif defined (DEFAULT_CORE2_STOP_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE2_STOP_SEC_VAR_1BIT_LOCAL
   #pragma ghs section data=default
   #pragma ghs enddata
#elif defined (DEFAULT_CORE3_START_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE3_START_SEC_VAR_1BIT_LOCAL
   #pragma ghs startdata
   #pragma ghs section data=".RAM_1BIT_CORE3"
#elif defined (DEFAULT_CORE3_STOP_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE3_STOP_SEC_VAR_1BIT_LOCAL
   #pragma ghs section data=default
   #pragma ghs enddata
#elif defined (DEFAULT_CORE4_START_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE4_START_SEC_VAR_1BIT_LOCAL
   #pragma ghs startdata
   #pragma ghs section data=".RAM_1BIT_CORE4"
#elif defined (DEFAULT_CORE4_STOP_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE4_STOP_SEC_VAR_1BIT_LOCAL
   #pragma ghs section data=default
   #pragma ghs enddata
#elif defined (DEFAULT_CORE5_START_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE5_START_SEC_VAR_1BIT_LOCAL
   #pragma ghs startdata
   #pragma ghs section data=".RAM_1BIT_CORE5"
#elif defined (DEFAULT_CORE5_STOP_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE5_STOP_SEC_VAR_1BIT_LOCAL
   #pragma ghs section data=default
   #pragma ghs enddata
#elif defined (DEFAULT_CORE6_START_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE6_START_SEC_VAR_1BIT_LOCAL
   #pragma ghs startdata
   #pragma ghs section data=".RAM_1BIT_CORE6"
#elif defined (DEFAULT_CORE6_STOP_SEC_VAR_1BIT_LOCAL)
   #undef      DEFAULT_CORE6_STOP_SEC_VAR_1BIT_LOCAL
   #pragma ghs section data=default
   #pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_INIT_PTR)
   #undef      DEFAULT_START_SEC_VAR_INIT_PTR
   #pragma ghs startdata
   #pragma ghs section data=".RAM_INIT_PTR"
#elif defined (DEFAULT_STOP_SEC_VAR_INIT_PTR)
   #undef      DEFAULT_STOP_SEC_VAR_INIT_PTR
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
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_1BIT)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_1BIT
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_1BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_1BIT)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_1BIT
   #pragma ghs section bss=default
   #pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_NOINIT_8BIT)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_8BIT
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_8BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_8BIT
   #pragma ghs section bss=default
   #pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_NOINIT_16BIT)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_16BIT
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_16BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_16BIT
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
#elif defined (DEFAULT_CORE0_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE0_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_PTR_CORE0"
#elif defined (DEFAULT_CORE0_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE0_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
   #pragma ghs section bss=default
   #pragma ghs enddata
#elif defined (DEFAULT_CORE1_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE1_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_PTR_CORE1"
#elif defined (DEFAULT_CORE1_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE1_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
   #pragma ghs section bss=default
   #pragma ghs enddata
#elif defined (DEFAULT_CORE2_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE2_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_PTR_CORE2"
#elif defined (DEFAULT_CORE2_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE2_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
   #pragma ghs section bss=default
   #pragma ghs enddata
#elif defined (DEFAULT_CORE3_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE3_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_PTR_CORE3"
#elif defined (DEFAULT_CORE3_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE3_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
   #pragma ghs section bss=default
   #pragma ghs enddata
#elif defined (DEFAULT_CORE4_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE4_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_PTR_CORE4"
#elif defined (DEFAULT_CORE4_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE4_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
   #pragma ghs section bss=default
   #pragma ghs enddata
#elif defined (DEFAULT_CORE5_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE5_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_PTR_CORE5"
#elif defined (DEFAULT_CORE5_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE5_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
   #pragma ghs section bss=default
   #pragma ghs enddata
#elif defined (DEFAULT_CORE6_START_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE6_START_SEC_VAR_NO_INIT_PTR_LOCAL
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_PTR_CORE6"
#elif defined (DEFAULT_CORE6_STOP_SEC_VAR_NO_INIT_PTR_LOCAL)
   #undef      DEFAULT_CORE6_STOP_SEC_VAR_NO_INIT_PTR_LOCAL
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
/* ROM code                                                                   */
/* -------------------------------------------------------------------------- */
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
