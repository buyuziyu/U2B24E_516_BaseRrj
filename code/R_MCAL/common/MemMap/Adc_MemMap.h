/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Adc_MemMap.h                                                                                        */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision for sections for Memory Mapping                                                                          */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                                                                                    */
/* Unless otherwise agreed upon in writing between your company and Renesas Electronics Corporation the following     */
/* shall apply!                                                                                                       */
/*                                                                                                                    */
/* Warranty Disclaimer                                                                                                */
/*                                                                                                                    */
/* There is no warranty of any kind whatsoever granted by Renesas. Any warranty is expressly disclaimed and excluded  */
/* by Renesas, either expressed or implied, including but not limited to those for non-infringement of intellectual   */
/* property, merchantability and/or fitness for the particular purpose.                                               */
/*                                                                                                                    */
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s) and/or */
/* the Application.                                                                                                   */
/*                                                                                                                    */
/* Each User is solely responsible for determining the appropriateness of using the Product(s) and assumes all risks  */
/* associated with its exercise of rights under this Agreement, including, but not limited to the risks and costs of  */
/* program errors, compliance with applicable laws, damage to or loss of data, programs or equipment, and             */
/* unavailability or interruption of operations.                                                                      */
/*                                                                                                                    */
/* Limitation of Liability                                                                                            */
/*                                                                                                                    */
/* In no event shall Renesas be liable to the User for any incidental, consequential, indirect, or punitive damage    */
/* (including but not limited to lost profits) regardless of whether such liability is based on breach of contract,   */
/* tort, strict liability, breach of warranties, failure of essential purpose or otherwise and even if advised of the */
/* possibility of such damages. Renesas shall not be liable for any services or products provided by third party      */
/* vendors, developers or consultants identified or referred to the User by Renesas in connection with the Product(s) */
/* and/or the Application.                                                                                            */
/*                                                                                                                    */
/*====================================================================================================================*/
/* Environment:                                                                                                       */
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.5.1: 30/06/2025 : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.03 release
 *                     Remove SW-VERSION in file header
 * 2.5.0: 30/06/2025 : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.4.0: 31/05/2025 : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.1: 28/02/2025 : Update SW-VERSION for Ver22.00.02 U2Ax Beta 1 Release
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3: 31/10/2024 : Increase Software version as 2.1.3
 * 2.1.2: 30/09/2024 : Increase Software version as 2.1.2
 * 2.1.1: 14/06/2024 : As part of Post-Build Variant support, following changes are made:
 *                     1.Change ADC_CFG_DATA_32BIT to ADC_CFG_DATA_POSTBUILD_32BIT, 
 *                       ADC_CFG_DATA_16BIT to ADC_CFG_DATA_POSTBUILD_16BIT,
 *                       ADC_CFG_DATA_8BIT to ADC_CFG_DATA_POSTBUILD_8BIT,
 *                       ADC_CFG_DATA_PTR to ADC_CFG_DATA_POSTBUILD_PTR,
 *                       ADC_CFG_DATA_UNSPECIFIED to ADC_CFG_DATA_POSTBUILD_UNSPECIFIED
 *                   : Increase Software version as 2.1.1
 *                   : As part of ARDAACL-45752 support, following changes are made:
 *                     1.Change ADC_START_SEC_CONFIG_DATA_PTR to ADC_START_SEC_CONFIG_DATA_POSTBUILD_PTR
 *                       and ADC_STOP_SEC_CONFIG_DATA_PTR to ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR
 *                     2.Change ADC_START_SEC_CONFIG_DATA_8 to ADC_START_SEC_CONFIG_DATA_POSTBUILD_8
 *                       and ADC_STOP_SEC_CONFIG_DATA_8 to ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_8
 *                     3.Change ADC_START_SEC_CONFIG_DATA_16 to ADC_START_SEC_CONFIG_DATA_POSTBUILD_16
 *                       and ADC_STOP_SEC_CONFIG_DATA_16 to ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_16
 *                     4.Change ADC_START_SEC_CONFIG_DATA_32 to ADC_START_SEC_CONFIG_DATA_POSTBUILD_32
 *                       and ADC_STOP_SEC_CONFIG_DATA_32 to ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_32
 * 2.1.0: 23/02/2024 : Update SW-VERSION to 2.1.0
 * 2.0.2: 18/12/2023 : Increase Software version as 2.0.2
 * 2.0.1: 12/10/2023 : Remove ADC_START/STOP_SEC_DBTOC_DATA_UNSPECIFIED
 *                     Change CONFIG_DATA_UNSPECIFIED_SEC_STARTED to CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
 *                     Change ADC_START_SEC_CONFIG_DATA_UNSPECIFIED to ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
 *                     and ADC_STOP_SEC_CONFIG_DATA_UNSPECIFIED to ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
 *        22/09/2023 : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/*
 * AUTOSAR specification version information
 */
#define ADC_MEMMAP_AR_RELEASE_MAJOR_VERSION    4
#define ADC_MEMMAP_AR_RELEASE_MINOR_VERSION    8
#define ADC_MEMMAP_AR_RELEASE_REVISION_VERSION 0

/*
 * File version information
 */
#define ADC_MEMMAP_SW_MAJOR_VERSION            2
#define ADC_MEMMAP_SW_MINOR_VERSION            5
#define ADC_MEMMAP_SW_PATCH_VERSION            0

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Module section mapping                                               **
***********************************************************************************************************************/
/*
 * The symbol 'START_WITH_IF' is undefined.
 *
 * Thus, the preprocessor continues searching for defined symbols
 * This first #ifdef makes integration of delivered parts of Adc_MemMap.h
 * easier because every supplier starts with #elif
 */
#if defined(START_WITH_IF)

/* -------------------------------------------------------------------------------------------------------------------*/
/*                                                         ADC                                                        */
/* -------------------------------------------------------------------------------------------------------------------*/

#elif defined(ADC_START_SEC_PUBLIC_CODE)
  #ifdef PUBLIC_CODE_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define PUBLIC_CODE_SEC_STARTED
    #undef ADC_START_SEC_PUBLIC_CODE
    #pragma ghs section text = ".ADC_PUBLIC_CODE_ROM"
  #endif
#elif defined(ADC_STOP_SEC_PUBLIC_CODE)
  #ifndef PUBLIC_CODE_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef PUBLIC_CODE_SEC_STARTED
    #undef ADC_STOP_SEC_PUBLIC_CODE
    #define DEFAULT_STOP_SEC_CODE
  #endif

#elif defined(ADC_START_SEC_PRIVATE_CODE)
  #ifdef PRIVATE_CODE_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define PRIVATE_CODE_SEC_STARTED
    #undef ADC_START_SEC_PRIVATE_CODE
    #pragma ghs section text = ".ADC_PRIVATE_CODE_ROM"
  #endif
#elif defined(ADC_STOP_SEC_PRIVATE_CODE)
  #ifndef PRIVATE_CODE_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef PRIVATE_CODE_SEC_STARTED
    #undef ADC_STOP_SEC_PRIVATE_CODE
    #define DEFAULT_STOP_SEC_CODE
  #endif

#elif defined(ADC_START_SEC_VAR_INIT_PTR)
  #ifdef VAR_INIT_PTR_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define VAR_INIT_PTR_SEC_STARTED
    #undef ADC_START_SEC_VAR_INIT_PTR
    #define DEFAULT_START_SEC_VAR_INIT_PTR
  #endif
#elif defined(ADC_STOP_SEC_VAR_INIT_PTR)
  #ifndef VAR_INIT_PTR_SEC_STARTED
    #error "Memory section is not started"
  #else
    #define VAR_INIT_PTR_SEC_STARTED
    #undef ADC_STOP_SEC_VAR_INIT_PTR
    #define DEFAULT_STOP_SEC_VAR_INIT_PTR
  #endif

/* For multi core */
#elif defined(ADC_START_SEC_PUBLIC_CODE_GLOBAL)
  #ifdef PUBLIC_CODE_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define PUBLIC_CODE_SEC_STARTED
    #undef ADC_START_SEC_PUBLIC_CODE_GLOBAL
    #pragma ghs section text = ".ADC_PUBLIC_CODE_ROM"
  #endif
#elif defined(ADC_STOP_SEC_PUBLIC_CODE_GLOBAL)
  #ifndef PUBLIC_CODE_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef PUBLIC_CODE_SEC_STARTED
    #undef ADC_STOP_SEC_PUBLIC_CODE_GLOBAL
    #define DEFAULT_STOP_SEC_CODE
  #endif
#elif defined(ADC_START_SEC_PUBLIC_CODE_LOCAL)
  #ifdef PUBLIC_CODE_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define PUBLIC_CODE_SEC_STARTED
    #undef ADC_START_SEC_PUBLIC_CODE_LOCAL
    #pragma ghs section text = ".ADC_PUBLIC_CODE_ROM"
  #endif
#elif defined(ADC_STOP_SEC_PUBLIC_CODE_LOCAL)
  #ifndef PUBLIC_CODE_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef PUBLIC_CODE_SEC_STARTED
    #undef ADC_STOP_SEC_PUBLIC_CODE_LOCAL
    #define DEFAULT_STOP_SEC_CODE
  #endif
/* End of multi core */

#elif defined(ADC_START_SEC_APPL_CODE)
  #ifdef APPL_CODE_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define APPL_CODE_SEC_STARTED
    #undef ADC_START_SEC_APPL_CODE
    #pragma ghs section text = ".ADC_APPL_CODE_ROM"
  #endif
#elif defined(ADC_STOP_SEC_APPL_CODE)
  #ifndef APPL_CODE_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef APPL_CODE_SEC_STARTED
    #undef ADC_STOP_SEC_APPL_CODE
    #define DEFAULT_STOP_SEC_CODE
  #endif

#elif defined(ADC_START_SEC_CODE_FAST)
  #ifdef ISR_CODE_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define ISR_CODE_SEC_STARTED
    #undef ADC_START_SEC_CODE_FAST
    #pragma ghs section text = ".ADC_FAST_CODE_ROM"
  #endif
#elif defined(ADC_STOP_SEC_CODE_FAST)
  #ifndef ISR_CODE_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef ISR_CODE_SEC_STARTED
    #undef ADC_STOP_SEC_CODE_FAST
    #define DEFAULT_STOP_SEC_CODE
  #endif

#elif defined(ADC_START_SEC_CONST_32)
  #ifdef CONST_32_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define CONST_32_SEC_STARTED
    #undef ADC_START_SEC_CONST_32
    #define DEFAULT_START_SEC_CONST_32BIT
  #endif
#elif defined(ADC_STOP_SEC_CONST_32)
  #ifndef CONST_32_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef CONST_32_SEC_STARTED
    #undef ADC_STOP_SEC_CONST_32
    #define DEFAULT_STOP_SEC_CONST_32BIT
  #endif

#elif defined(ADC_START_SEC_CONFIG_DATA_POSTBUILD_8)
  #ifdef ADC_CONFIG_DATA_POSTBUILD_8_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define ADC_CONFIG_DATA_POSTBUILD_8_SEC_STARTED
    #undef ADC_START_SEC_CONFIG_DATA_POSTBUILD_8
    #pragma ghs startdata
    #pragma ghs section rodata = ".ADC_CFG_DATA_POSTBUILD_8BIT"
  #endif
#elif defined(ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_8)
  #ifndef ADC_CONFIG_DATA_POSTBUILD_8_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef ADC_CONFIG_DATA_POSTBUILD_8_SEC_STARTED
    #undef ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_8
    #define DEFAULT_STOP_SEC_CONST_8BIT
  #endif
  
#elif defined(ADC_START_SEC_CONFIG_DATA_POSTBUILD_16)
  #ifdef ADC_CONFIG_DATA_POSTBUILD_16_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define ADC_CONFIG_DATA_POSTBUILD_16_SEC_STARTED
    #undef ADC_START_SEC_CONFIG_DATA_POSTBUILD_16
    #pragma ghs startdata
    #pragma ghs section rodata = ".ADC_CFG_DATA_POSTBUILD_16BIT"
  #endif
#elif defined(ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_16)
  #ifndef ADC_CONFIG_DATA_POSTBUILD_16_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef ADC_CONFIG_DATA_POSTBUILD_16_SEC_STARTED
    #undef ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_16
    #define DEFAULT_STOP_SEC_CONST_16BIT
  #endif
  
#elif defined(ADC_START_SEC_CONFIG_DATA_POSTBUILD_32)
  #ifdef ADC_CONFIG_DATA_POSTBUILD_32_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define ADC_CONFIG_DATA_POSTBUILD_32_SEC_STARTED
    #undef ADC_START_SEC_CONFIG_DATA_POSTBUILD_32
    #pragma ghs startdata
    #pragma ghs section rodata = ".ADC_CFG_DATA_POSTBUILD_32BIT"
  #endif
#elif defined(ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_32)
  #ifndef ADC_CONFIG_DATA_POSTBUILD_32_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef ADC_CONFIG_DATA_POSTBUILD_32_SEC_STARTED
    #undef ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_32
    #define DEFAULT_STOP_SEC_CONST_32BIT
  #endif
  
#elif defined(ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #ifdef CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
    #undef ADC_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #pragma ghs startdata
    #pragma ghs section rodata = ".ADC_CFG_DATA_POSTBUILD_UNSPECIFIED"
  #endif
#elif defined(ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #ifndef CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
    #undef ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #define DEFAULT_STOP_SEC_CONST_UNSPECIFIED
  #endif
  
#elif defined(ADC_START_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #ifdef CONFIG_DATA_POSTBUILD_PTR_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define CONFIG_DATA_POSTBUILD_PTR_SEC_STARTED
    #undef ADC_START_SEC_CONFIG_DATA_POSTBUILD_PTR
    #pragma ghs startdata
    #pragma ghs section rodata = ".ADC_CFG_DATA_POSTBUILD_PTR"
  #endif
#elif defined(ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #ifndef CONFIG_DATA_POSTBUILD_PTR_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef CONFIG_DATA_POSTBUILD_PTR_SEC_STARTED
    #undef ADC_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR
    #define DEFAULT_STOP_SEC_CONST_PTR
  #endif
  
#elif defined(ADC_START_SEC_VAR_INIT_BOOLEAN)
  #ifdef VAR_BOOLEAN_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define VAR_BOOLEAN_SEC_STARTED
    #undef ADC_START_SEC_VAR_INIT_BOOLEAN
    #define DEFAULT_START_SEC_VAR_1BIT
  #endif
#elif defined(ADC_STOP_SEC_VAR_INIT_BOOLEAN)
  #ifndef VAR_BOOLEAN_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef VAR_BOOLEAN_SEC_STARTED
    #undef ADC_STOP_SEC_VAR_INIT_BOOLEAN
    #define DEFAULT_STOP_SEC_VAR_1BIT
  #endif
  
#elif defined(ADC_START_SEC_VAR_NO_INIT_BOOLEAN)
  #ifdef VAR_NOINIT_BOOLEAN_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define VAR_NOINIT_BOOLEAN_SEC_STARTED
    #undef ADC_START_SEC_VAR_NO_INIT_BOOLEAN
    #define DEFAULT_START_SEC_VAR_NOINIT_1BIT
  #endif
#elif defined(ADC_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #ifndef VAR_NOINIT_BOOLEAN_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef VAR_NOINIT_BOOLEAN_SEC_STARTED
    #undef ADC_STOP_SEC_VAR_NO_INIT_BOOLEAN
    #define DEFAULT_STOP_SEC_VAR_NOINIT_1BIT
  #endif
  
#elif defined(ADC_START_SEC_VAR_NO_INIT_8)
  #ifdef VAR_NOINIT_8_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define VAR_NOINIT_8_SEC_STARTED
    #undef ADC_START_SEC_VAR_NO_INIT_8
    #define DEFAULT_START_SEC_VAR_NOINIT_8BIT
  #endif
#elif defined(ADC_STOP_SEC_VAR_NO_INIT_8)
  #ifndef VAR_NOINIT_8_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef VAR_NOINIT_8_SEC_STARTED
    #undef ADC_STOP_SEC_VAR_NO_INIT_8
    #define DEFAULT_STOP_SEC_VAR_NOINIT_8BIT
  #endif

#elif defined(ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #ifdef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define VAR_NOINIT_UNSPECIFIED_SEC_STARTED
    #undef ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
    #define DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED
  #endif
#elif defined(ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #ifndef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
    #undef ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
    #define DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #endif

#elif defined(ADC_START_SEC_VAR_NO_INIT_PTR)
  #ifdef VAR_NOINIT_PTR_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define VAR_NOINIT_PTR_SEC_STARTED
    #undef ADC_START_SEC_VAR_NO_INIT_PTR
    #define DEFAULT_START_SEC_VAR_NOINIT_PTR
    #endif
#elif defined(ADC_STOP_SEC_VAR_NO_INIT_PTR)
  #ifndef VAR_NOINIT_PTR_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef VAR_NOINIT_PTR_SEC_STARTED
    #undef ADC_STOP_SEC_VAR_NO_INIT_PTR
    #define DEFAULT_STOP_SEC_VAR_NOINIT_PTR
  #endif

#else
   #error "Adc_MemMap.h: No valid section define found"
#endif /* START_WITH_IF */

/***********************************************************************************************************************
**                                              Default section mapping                                               **
***********************************************************************************************************************/
/* general start of #elif chain whith #if                                                                             */
#if defined(START_WITH_IF)

/* -------------------------------------------------------------------------------------------------------------------*/
/* RAM variables initialized from ROM on reset                                                                        */
/* -------------------------------------------------------------------------------------------------------------------*/
#elif defined(DEFAULT_START_SEC_VAR_1BIT)
  #undef DEFAULT_START_SEC_VAR_1BIT
  #pragma ghs startdata
  #pragma ghs section data = ".RAM_1BIT"
#elif defined(DEFAULT_STOP_SEC_VAR_1BIT)
  #undef DEFAULT_STOP_SEC_VAR_1BIT
  #pragma ghs section data = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_VAR_8BIT)
  #undef DEFAULT_START_SEC_VAR_8BIT
  #pragma ghs startdata
  #pragma ghs section data = ".RAM_8BIT"
#elif defined(DEFAULT_STOP_SEC_VAR_8BIT)
  #undef DEFAULT_STOP_SEC_VAR_8BIT
  #pragma ghs section data = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_VAR_16BIT)
  #undef DEFAULT_START_SEC_VAR_16BIT
  #pragma ghs startdata
  #pragma ghs section data = ".RAM_16BIT"
#elif defined(DEFAULT_STOP_SEC_VAR_16BIT)
  #undef DEFAULT_STOP_SEC_VAR_16BIT
  #pragma ghs section data = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_VAR_32BIT)
  #undef DEFAULT_START_SEC_VAR_32BIT
  #pragma ghs startdata
  #pragma ghs section data = ".RAM_32BIT"
#elif defined(DEFAULT_STOP_SEC_VAR_32BIT)
  #undef DEFAULT_STOP_SEC_VAR_32BIT
  #pragma ghs section data = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_VAR_UNSPECIFIED)
  #undef DEFAULT_START_SEC_VAR_UNSPECIFIED
  #pragma ghs startdata
  #pragma ghs section data = ".RAM_UNSPECIFIED"
#elif defined(DEFAULT_STOP_SEC_VAR_UNSPECIFIED)
  #undef DEFAULT_STOP_SEC_VAR_UNSPECIFIED
  #pragma ghs section data = default
  #pragma ghs enddata

/* -------------------------------------------------------------------------- */
/* RAM variables not initialized                                                                                      */
/* -------------------------------------------------------------------------- */
#elif defined(DEFAULT_START_SEC_VAR_NOINIT_1BIT)
  #undef DEFAULT_START_SEC_VAR_NOINIT_1BIT
  #pragma ghs startdata
  #pragma ghs section bss = ".NOINIT_RAM_1BIT"
#elif defined(DEFAULT_STOP_SEC_VAR_NOINIT_1BIT)
  #undef DEFAULT_STOP_SEC_VAR_NOINIT_1BIT
  #pragma ghs section bss = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_VAR_NOINIT_8BIT)
  #undef DEFAULT_START_SEC_VAR_NOINIT_8BIT
  #pragma ghs startdata
  #pragma ghs section bss = ".NOINIT_RAM_8BIT"
#elif defined(DEFAULT_STOP_SEC_VAR_NOINIT_8BIT)
  #undef DEFAULT_STOP_SEC_VAR_NOINIT_8BIT
  #pragma ghs section bss = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_VAR_NOINIT_16BIT)
  #undef DEFAULT_START_SEC_VAR_NOINIT_16BIT
  #pragma ghs startdata
  #pragma ghs section bss = ".NOINIT_RAM_16BIT"
#elif defined(DEFAULT_STOP_SEC_VAR_NOINIT_16BIT)
  #undef DEFAULT_STOP_SEC_VAR_NOINIT_16BIT
  #pragma ghs section bss = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_VAR_NOINIT_32BIT)
  #undef DEFAULT_START_SEC_VAR_NOINIT_32BIT
  #pragma ghs startdata
  #pragma ghs section bss = ".NOINIT_RAM_32BIT"
#elif defined(DEFAULT_STOP_SEC_VAR_NOINIT_32BIT)
  #undef DEFAULT_STOP_SEC_VAR_NOINIT_32BIT
  #pragma ghs section bss = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_VAR_NOINIT_PTR)
  #undef DEFAULT_START_SEC_VAR_NOINIT_PTR
  #pragma ghs startdata
  #pragma ghs section bss = ".NOINIT_RAM_PTR"
#elif defined(DEFAULT_STOP_SEC_VAR_NOINIT_PTR)
  #undef DEFAULT_STOP_SEC_VAR_NOINIT_PTR
  #pragma ghs section bss = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED
  #pragma ghs startdata
  #pragma ghs section bss = ".NOINIT_RAM_UNSPECIFIED"
#elif defined(DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #pragma ghs section bss = default
  #pragma ghs enddata

/* -------------------------------------------------------------------------- */
/* RAM variables frequently used or accessed bitwise                                                                  */
/* -------------------------------------------------------------------------- */
#elif defined(DEFAULT_START_SEC_VAR_FAST_1BIT)
  #undef DEFAULT_START_SEC_VAR_FAST_1BIT
  #pragma ghs startdata
  #pragma ghs section data = ".FAST_RAM_1BIT"
#elif defined(DEFAULT_STOP_SEC_VAR_FAST_1BIT)
  #undef DEFAULT_STOP_SEC_VAR_FAST_1BIT
  #pragma ghs section data = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_VAR_FAST_8BIT)
  #undef DEFAULT_START_SEC_VAR_FAST_8BIT
  #pragma ghs startdata
  #pragma ghs section data = ".FAST_RAM_8BIT"
#elif defined(DEFAULT_STOP_SEC_VAR_FAST_8BIT)
  #undef DEFAULT_STOP_SEC_VAR_FAST_8BIT
  #pragma ghs section data = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_VAR_FAST_16BIT)
  #undef DEFAULT_START_SEC_VAR_FAST_16BIT
  #pragma ghs startdata
  #pragma ghs section data = ".FAST_RAM_16BIT"
#elif defined(DEFAULT_STOP_SEC_VAR_FAST_16BIT)
  #undef DEFAULT_STOP_SEC_VAR_FAST_16BIT
  #pragma ghs section data = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_VAR_FAST_32BIT)
  #undef DEFAULT_START_SEC_VAR_FAST_32BIT
  #pragma ghs startdata
  #pragma ghs section data = ".FAST_RAM_32BIT"
#elif defined(DEFAULT_STOP_SEC_VAR_FAST_32BIT)
  #undef DEFAULT_STOP_SEC_VAR_FAST_32BIT
  #pragma ghs section data = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_VAR_FAST_UNSPECIFIED)
  #undef DEFAULT_START_SEC_VAR_FAST_UNSPECIFIED
  #pragma ghs startdata
  #pragma ghs section data = ".FAST_RAM_UNSPECIFIED"
#elif defined(DEFAULT_STOP_SEC_VAR_FAST_UNSPECIFIED)
  #undef DEFAULT_STOP_SEC_VAR_FAST_UNSPECIFIED
  #pragma ghs section data = default
  #pragma ghs enddata

/* -------------------------------------------------------------------------- */
/* ROM constants                                                                                                      */
/* -------------------------------------------------------------------------- */
#elif defined(DEFAULT_START_SEC_CONST_1BIT)
  #undef DEFAULT_START_SEC_CONST_1BIT
  #pragma ghs startdata
  #pragma ghs section rodata = ".CONST_ROM_1BIT"
#elif defined(DEFAULT_STOP_SEC_CONST_1BIT)
  #undef DEFAULT_STOP_SEC_CONST_1BIT
  #pragma ghs section rodata = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_CONST_8BIT)
  #undef DEFAULT_START_SEC_CONST_8BIT
  #pragma ghs startdata
  #pragma ghs section rodata = ".CONST_ROM_8BIT"
#elif defined(DEFAULT_STOP_SEC_CONST_8BIT)
  #undef DEFAULT_STOP_SEC_CONST_8BIT
  #pragma ghs section rodata = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_CONST_16BIT)
  #undef DEFAULT_START_SEC_CONST_16BIT
  #pragma ghs startdata
  #pragma ghs section rodata = ".CONST_ROM_16BIT"
#elif defined(DEFAULT_STOP_SEC_CONST_16BIT)
  #undef DEFAULT_STOP_SEC_CONST_16BIT
  #pragma ghs section rodata = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_CONST_32BIT)
  #undef DEFAULT_START_SEC_CONST_32BIT
  #pragma ghs startdata
  #pragma ghs section rodata = ".CONST_ROM_32BIT"
#elif defined(DEFAULT_STOP_SEC_CONST_32BIT)
  #undef DEFAULT_STOP_SEC_CONST_32BIT
  #pragma ghs section rodata = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_CONST_UNSPECIFIED)
  #undef DEFAULT_START_SEC_CONST_UNSPECIFIED
  #pragma ghs startdata
  #pragma ghs section rodata = ".CONST_ROM_UNSPECIFIED"
#elif defined(DEFAULT_STOP_SEC_CONST_UNSPECIFIED)
  #undef DEFAULT_STOP_SEC_CONST_UNSPECIFIED
  #pragma ghs section rodata = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_CONST_PTR)
  #undef DEFAULT_START_SEC_CONST_PTR
  #pragma ghs startdata
  #pragma ghs section rodata = ".CONST_ROM_PTR"
#elif defined(DEFAULT_STOP_SEC_CONST_PTR)
  #undef DEFAULT_STOP_SEC_CONST_PTR
  #pragma ghs section rodata = default
  #pragma ghs enddata

/* -------------------------------------------------------------------------- */
/* ROM FAR constants                                                                                                  */
/* -------------------------------------------------------------------------- */
#elif defined(DEFAULT_START_SEC_CONST_1BIT_FAR)
  #undef DEFAULT_START_SEC_CONST_1BIT_FAR
  #pragma ghs startdata
  #pragma ghs section rodata = ".CONST_FAR_ROM_1BIT"
#elif defined(DEFAULT_STOP_SEC_CONST_1BIT_FAR)
  #undef DEFAULT_STOP_SEC_CONST_1BIT_FAR
  #pragma ghs section rodata = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_CONST_8BIT_FAR)
  #undef DEFAULT_START_SEC_CONST_8BIT_FAR
  #pragma ghs startdata
  #pragma ghs section rodata = ".CONST_FAR_ROM_8BIT"
#elif defined(DEFAULT_STOP_SEC_CONST_8BIT_FAR)
  #undef DEFAULT_STOP_SEC_CONST_8BIT_FAR
  #pragma ghs section rodata = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_CONST_16BIT_FAR)
  #undef DEFAULT_START_SEC_CONST_16BIT_FAR
  #pragma ghs startdata
  #pragma ghs section rodata = ".CONST_FAR_ROM_16BIT"
#elif defined(DEFAULT_STOP_SEC_CONST_16BIT_FAR)
  #undef DEFAULT_STOP_SEC_CONST_16BIT_FAR
  #pragma ghs section rodata = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_CONST_32BIT_FAR)
  #undef DEFAULT_START_SEC_CONST_32BIT_FAR
  #pragma ghs startdata
  #pragma ghs section rodata = ".CONST_FAR_ROM_32BIT"
#elif defined(DEFAULT_STOP_SEC_CONST_32BIT_FAR)
  #undef DEFAULT_STOP_SEC_CONST_32BIT_FAR
  #pragma ghs section rodata = default
  #pragma ghs enddata

#elif defined(DEFAULT_START_SEC_CONST_UNSPECIFIED_FAR)
  #undef DEFAULT_START_SEC_CONST_UNSPECIFIED_FAR
  #pragma ghs startdata
  #pragma ghs section rodata = ".CONST_FAR_ROM_UNSPECIFIED"
#elif defined(DEFAULT_STOP_SEC_CONST_UNSPECIFIED_FAR)
  #undef DEFAULT_STOP_SEC_CONST_UNSPECIFIED_FAR
  #pragma ghs section rodata = default
  #pragma ghs enddata
/* -------------------------------------------------------------------------- */
/* ROM code                                                                                                           */
/* -------------------------------------------------------------------------- */
#elif defined(DEFAULT_START_SEC_CODE)
  #undef DEFAULT_START_SEC_CODE
  #pragma ghs section text = ".DEFAULT_CODE_ROM"
#elif defined(DEFAULT_STOP_SEC_CODE)
  #undef DEFAULT_STOP_SEC_CODE
  #pragma ghs section text = default

/* -------------------------------------------------------------------------------------------------------------------*/
/* End of default section mapping                                                                                     */
/* -------------------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* START_WITH_IF */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
