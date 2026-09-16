/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = Wdg_MemMap.h                                                */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.        */
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
 * 2.4.1:     30/06/2025  : Remove SW-VERSION in file header     
 * 2.4.0:     30/06/2025  : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.2:     30/06/2025  : Update SW-VERSION for RH850/Ver22.00.03 U2Bx-E 
 * 2.3.1      31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 2.3.0      28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL                
 *                          Ver22.01.00/Ver22.01.00.D Release                     
 * 2.2.0      31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                          Final release
 * 2.1.2      31/10/2024  : Update SW-VERSION to 2.1.2
 * 2.1.1      24/07/2024  : Update SW-VERSION to 2.1.1
 * 2.1.0      23/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.1      09/10/2023  : Add mandatory tag configClass in memory section 
 *            22/09/2023  : Initial Version
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
#define WDG_MEMMAP_AR_RELEASE_MAJOR_VERSION      4
#define WDG_MEMMAP_AR_RELEASE_MINOR_VERSION      8
#define WDG_MEMMAP_AR_RELEASE_REVISION_VERSION   0

/*
 * File version information
 */
#define WDG_MEMMAP_SW_MAJOR_VERSION   2
#define WDG_MEMMAP_SW_MINOR_VERSION   4
#define WDG_MEMMAP_SW_PATCH_VERSION   0




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
/* -------------------------------------------------------------------------- */

#elif defined (WDG_START_SEC_CONST_8)
   #ifdef VAR_8_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_8_SEC_STARTED
     #undef  WDG_START_SEC_CONST_8
     #define DEFAULT_START_SEC_CONST_8BIT
   #endif
#elif defined (WDG_STOP_SEC_CONST_8)
   #ifndef VAR_8_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_8_SEC_STARTED
     #undef  WDG_STOP_SEC_CONST_8
     #define DEFAULT_STOP_SEC_CONST_8BIT
   #endif

#elif defined (WDG_START_SEC_CONST_32)
   #ifdef VAR_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_32_SEC_STARTED
     #undef  WDG_START_SEC_CONST_32
     #define DEFAULT_START_SEC_CONST_32BIT
   #endif
#elif defined (WDG_STOP_SEC_CONST_32)
   #ifndef VAR_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_32_SEC_STARTED
     #undef  WDG_STOP_SEC_CONST_32
     #define DEFAULT_STOP_SEC_CONST_32BIT
   #endif
   
#elif defined (WDG_START_SEC_VAR_NO_INIT_32)
   #ifdef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_START_SEC_VAR_NO_INIT_32
     #define DEFAULT_START_SEC_VAR_NOINIT_32BIT
   #endif
#elif defined (WDG_STOP_SEC_VAR_NO_INIT_32)
   #ifndef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_STOP_SEC_VAR_NO_INIT_32
     #define DEFAULT_STOP_SEC_VAR_NOINIT_32BIT
   #endif
//core0
#elif defined (WDG_CORE0_START_SEC_VAR_NO_INIT_32_LOCAL)
   #ifdef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_CORE0_START_SEC_VAR_NO_INIT_32_LOCAL
     #define DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE0
   #endif
#elif defined (WDG_CORE0_STOP_SEC_VAR_NO_INIT_32_LOCAL)
   #ifndef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_CORE0_STOP_SEC_VAR_NO_INIT_32_LOCAL
     #define DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE0
   #endif

//core1
#elif defined (WDG_CORE1_START_SEC_VAR_NO_INIT_32_LOCAL)
   #ifdef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_CORE1_START_SEC_VAR_NO_INIT_32_LOCAL
     #define DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE1
   #endif
#elif defined (WDG_CORE1_STOP_SEC_VAR_NO_INIT_32_LOCAL)
   #ifndef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_CORE1_STOP_SEC_VAR_NO_INIT_32_LOCAL
     #define DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE1
   #endif   

//core2
#elif defined (WDG_CORE2_START_SEC_VAR_NO_INIT_32_LOCAL)
   #ifdef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_CORE2_START_SEC_VAR_NO_INIT_32_LOCAL
     #define DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE2
   #endif
#elif defined (WDG_CORE2_STOP_SEC_VAR_NO_INIT_32_LOCAL)
   #ifndef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_CORE2_STOP_SEC_VAR_NO_INIT_32_LOCAL
     #define DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE2
   #endif 
//core3
#elif defined (WDG_CORE3_START_SEC_VAR_NO_INIT_32_LOCAL)
   #ifdef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_CORE3_START_SEC_VAR_NO_INIT_32_LOCAL
     #define DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE3
   #endif
#elif defined (WDG_CORE3_STOP_SEC_VAR_NO_INIT_32_LOCAL)
   #ifndef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_CORE3_STOP_SEC_VAR_NO_INIT_32_LOCAL
     #define DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE3
   #endif

//core4
#elif defined (WDG_CORE4_START_SEC_VAR_NO_INIT_32_LOCAL)
   #ifdef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_CORE4_START_SEC_VAR_NO_INIT_32_LOCAL
     #define DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE4
   #endif
#elif defined (WDG_CORE4_STOP_SEC_VAR_NO_INIT_32_LOCAL)
   #ifndef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_CORE4_STOP_SEC_VAR_NO_INIT_32_LOCAL
     #define DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE4
   #endif   

//core5
#elif defined (WDG_CORE5_START_SEC_VAR_NO_INIT_32_LOCAL)
   #ifdef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_CORE5_START_SEC_VAR_NO_INIT_32_LOCAL
     #define DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE5
   #endif
#elif defined (WDG_CORE5_STOP_SEC_VAR_NO_INIT_32_LOCAL)
   #ifndef VAR_NOINIT_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_32_SEC_STARTED
     #undef  WDG_CORE5_STOP_SEC_VAR_NO_INIT_32_LOCAL
     #define DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE5
   #endif 

#elif defined (WDG_START_SEC_VAR_NO_INIT_PTR)
   #ifdef VAR_NOINIT_PTR_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_PTR_SEC_STARTED
     #undef  WDG_START_SEC_VAR_NO_INIT_PTR
     #define DEFAULT_START_SEC_VAR_NOINIT_PTR
   #endif
#elif defined (WDG_STOP_SEC_VAR_NO_INIT_PTR)
   #ifndef VAR_NOINIT_PTR_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_PTR_SEC_STARTED
     #undef  WDG_STOP_SEC_VAR_NO_INIT_PTR
     #define DEFAULT_STOP_SEC_VAR_NOINIT_PTR
   #endif

#elif defined (WDG_START_SEC_VAR_INIT_UNSPECIFIED)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_START_SEC_VAR_INIT_UNSPECIFIED
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED
   #endif
#elif defined (WDG_STOP_SEC_VAR_INIT_UNSPECIFIED)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_STOP_SEC_VAR_INIT_UNSPECIFIED
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED
   #endif
//core0
#elif defined (WDG_CORE0_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE0_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE0
   #endif
#elif defined (WDG_CORE0_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE0_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE0
   #endif
//core1
#elif defined (WDG_CORE1_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE1_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE1
   #endif
#elif defined (WDG_CORE1_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE1_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE1
   #endif

//core2
#elif defined (WDG_CORE2_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE2_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE2
   #endif
#elif defined (WDG_CORE2_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE2_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE2
   #endif
//core3
#elif defined (WDG_CORE3_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE3_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE3
   #endif
#elif defined (WDG_CORE3_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE3_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE3
   #endif
//core4
#elif defined (WDG_CORE4_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE4_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE4
   #endif
#elif defined (WDG_CORE4_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE4_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE4
   #endif

//core5
#elif defined (WDG_CORE5_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE5_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE5
   #endif
#elif defined (WDG_CORE5_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE5_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE5
   #endif
   
#elif defined (WDG_START_SEC_VAR_NO_INIT_UNSPECIFIED)
   #ifdef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_START_SEC_VAR_NO_INIT_UNSPECIFIED
     #define DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED
   #endif
#elif defined (WDG_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
   #ifndef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
     #define DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #endif

//CORE0
#elif defined (WDG_CORE0_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE0_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE0
   #endif
#elif defined (WDG_CORE0_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE0_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE0
   #endif

//CORE1
#elif defined (WDG_CORE1_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE1_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE1
   #endif
#elif defined (WDG_CORE1_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE1_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE1
   #endif

//CORE2
#elif defined (WDG_CORE2_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE2_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE2
   #endif
#elif defined (WDG_CORE2_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE2_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE2
   #endif

//CORE3
#elif defined (WDG_CORE3_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE3_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE3
   #endif
#elif defined (WDG_CORE3_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE3_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE3
   #endif

//CORE4
#elif defined (WDG_CORE4_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE4_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE4
   #endif
#elif defined (WDG_CORE4_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE4_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE4
   #endif

//CORE5
#elif defined (WDG_CORE5_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE5_START_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE5
   #endif
#elif defined (WDG_CORE5_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_NOINIT_UNSPECIFIED_SEC_STARTED
     #undef  WDG_CORE5_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE5
   #endif

#elif defined (WDG_START_SEC_DBTOC_DATA_UNSPECIFIED)
   #ifdef DBTOC_DATA_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define DBTOC_DATA_UNSPECIFIED_SEC_STARTED
     #undef  WDG_START_SEC_DBTOC_DATA_UNSPECIFIED
     #pragma ghs startdata
     #pragma ghs section rodata=".WDG_CFG_DBTOC_UNSPECIFIED"
   #endif
#elif defined (WDG_STOP_SEC_DBTOC_DATA_UNSPECIFIED)
   #ifndef DBTOC_DATA_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  DBTOC_DATA_UNSPECIFIED_SEC_STARTED
     #undef  WDG_STOP_SEC_DBTOC_DATA_UNSPECIFIED
     #define DEFAULT_STOP_SEC_CONST_UNSPECIFIED
   #endif

#elif defined (WDG_START_SEC_PUBLIC_CODE)
   #ifdef PUBLIC_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define PUBLIC_CODE_SEC_STARTED
     #undef  WDG_START_SEC_PUBLIC_CODE
     #pragma ghs section text=".WDG_PUBLIC_CODE_ROM"
   #endif
#elif defined (WDG_STOP_SEC_PUBLIC_CODE)
   #ifndef PUBLIC_CODE_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  PUBLIC_CODE_SEC_STARTED
     #undef  WDG_STOP_SEC_PUBLIC_CODE
     #define DEFAULT_STOP_SEC_CODE
   #endif

#elif defined (WDG_START_SEC_CODE_FAST)
   #ifdef ISR_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define ISR_CODE_SEC_STARTED
     #undef  WDG_START_SEC_CODE_FAST
     #pragma ghs section text=".WDG_FAST_CODE_ROM"
   #endif
#elif defined (WDG_STOP_SEC_CODE_FAST)
   #ifndef ISR_CODE_SEC_STARTED
      #error "Memory section is not started"
   #else
     #undef  ISR_CODE_SEC_STARTED
     #undef  WDG_STOP_SEC_CODE_FAST
     #define DEFAULT_STOP_SEC_CODE
   #endif

#elif defined (WDG_START_SEC_PRIVATE_CODE)
   #ifdef PRIVATE_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define PRIVATE_CODE_SEC_STARTED
     #undef  WDG_START_SEC_PRIVATE_CODE
     #pragma ghs section text=".WDG_PRIVATE_CODE_ROM"
   #endif
#elif defined (WDG_STOP_SEC_PRIVATE_CODE)
   #ifndef PRIVATE_CODE_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  PRIVATE_CODE_SEC_STARTED
     #undef  WDG_STOP_SEC_PRIVATE_CODE
     #define DEFAULT_STOP_SEC_CODE
   #endif

#elif defined (WDG_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
   #ifdef WDG_CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define WDG_CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
     #undef  WDG_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
     #pragma ghs startdata
     #pragma ghs section rodata=".WDG_CFG_DATA_UNSPECIFIED"
   #endif
#elif defined (WDG_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
   #ifndef WDG_CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  WDG_CONFIG_DATA_POSTBUILD_UNSPECIFIED_SEC_STARTED
     #undef  WDG_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
     #define DEFAULT_STOP_SEC_CONST_UNSPECIFIED
   #endif
#else
  #error "Wdg_MemMap.h: No valid section define found"
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
//core0
#elif defined (DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE0)
   #undef      DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE0
   #pragma ghs startdata
   #pragma ghs section data=".RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE0)
   #undef      DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE0
   #pragma ghs section data=default
   #pragma ghs enddata
//core1
#elif defined (DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE1)
   #undef      DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE1
   #pragma ghs startdata
   #pragma ghs section data=".RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE1)
   #undef      DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE1
   #pragma ghs section data=default
   #pragma ghs enddata
//core2
#elif defined (DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE2)
   #undef      DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE2
   #pragma ghs startdata
   #pragma ghs section data=".RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE2)
   #undef      DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE2
   #pragma ghs section data=default
   #pragma ghs enddata
//core3
#elif defined (DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE3)
   #undef      DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE3
   #pragma ghs startdata
   #pragma ghs section data=".RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE3)
   #undef      DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE3
   #pragma ghs section data=default
   #pragma ghs enddata
//core4
#elif defined (DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE4)
   #undef      DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE4
   #pragma ghs startdata
   #pragma ghs section data=".RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE4)
   #undef      DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE4
   #pragma ghs section data=default
   #pragma ghs enddata
//core5
#elif defined (DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE5)
   #undef      DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE5
   #pragma ghs startdata
   #pragma ghs section data=".RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE5)
   #undef      DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE5
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

#elif defined (DEFAULT_START_SEC_VAR_NOINIT_32BIT)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_32BIT
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_32BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_32BIT
   #pragma ghs section bss=default
   #pragma ghs enddata

//core0
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE0)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE0
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_32BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE0)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE0
   #pragma ghs section bss=default
   #pragma ghs enddata

//core1
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE1)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE1
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_32BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE1)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE1
   #pragma ghs section bss=default
   #pragma ghs enddata

//core2
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE2)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE2
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_32BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE2)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE2
   #pragma ghs section bss=default
   #pragma ghs enddata

//core3
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE3)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE3
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_32BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE3)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE3
   #pragma ghs section bss=default
   #pragma ghs enddata

//core4
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE4)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE4
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_32BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE4)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE4
   #pragma ghs section bss=default
   #pragma ghs enddata

//core5
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE5)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_32BIT_CORE5
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_32BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE5)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_32BIT_CORE5
   #pragma ghs section bss=default
   #pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_NOINIT_PTR)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_PTR
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_PTR"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_PTR)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_PTR
   #pragma ghs section bss=default
   #pragma ghs enddata

#elif defined (DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #pragma ghs section bss=default
   #pragma ghs enddata

//core0
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE0)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE0
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE0)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE0
   #pragma ghs section bss=default
   #pragma ghs enddata
//core1
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE1)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE1
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE1)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE1
   #pragma ghs section bss=default
   #pragma ghs enddata
//core2
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE2)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE2
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE2)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE2
   #pragma ghs section bss=default
   #pragma ghs enddata
//core3
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE3)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE3
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE3)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE3
   #pragma ghs section bss=default
   #pragma ghs enddata
//core4
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE4)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE4
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE4)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE4
   #pragma ghs section bss=default
   #pragma ghs enddata
//core5
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE5)
   #undef      DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED_CORE5
   #pragma ghs startdata
   #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE5)
   #undef      DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED_CORE5
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
