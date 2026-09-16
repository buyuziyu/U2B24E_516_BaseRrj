/*============================================================================*/
/* Project      = AUTOSAR Renesas X1x MCAL Components                         */
/* Module       = RamTst_MemMap.h                                             */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* Copyright(c) 2023-2025 Renesas Electronics Corporation.                    */
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
 * 1.4.1      30/06/2025   Update SW-VERSION
 * 1.4.0      31/03/2025   Update SW-VERSION for RH850/Ver22.01.01 U2Cx Release
 * 1.3.1      31/03/2025   Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 1.3.0      31/01/2025   Update SW-VERSION for Ver22.00.06 U2Cx Beta release
 * 1.2.0      31/12/2024   Update SW-Version for Ver22.02.00/Ver22.02.00.D 
 *                         U2Bx Final release 
 * 1.1.2      31/10/2024   Update SW-VERSION to 1.1.2
 * 1.1.1      24/07/2024   Update SW-VERSION to 1.1.1
 * 1.1.0      23/02/2024   Update SW-VERSION to 1.1.0
 * 1.0.2      10/01/2024   Update SW-VERSION to 1.0.2
 * 1.0.1      22/09/2023   Initial Version

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
#define RAMTST_MEMMAP_AR_RELEASE_MAJOR_VERSION      4
#define RAMTST_MEMMAP_AR_RELEASE_MINOR_VERSION      8
#define RAMTST_MEMMAP_AR_RELEASE_REVISION_VERSION   0

/*
 * File version information
 */
#define RAMTST_MEMMAP_SW_MAJOR_VERSION   1
#define RAMTST_MEMMAP_SW_MINOR_VERSION   4
#define RAMTST_MEMMAP_SW_PATCH_VERSION   1

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
/*             RAMTST                                                         */
/* -------------------------------------------------------------------------- */
#elif defined (RAMTST_START_SEC_VAR_POWER_ON_INIT_8)
   #ifdef VAR_8_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_8_SEC_STARTED
     #undef  RAMTST_START_SEC_VAR_POWER_ON_INIT_8
     #define DEFAULT_START_SEC_VAR_8BIT
   #endif
#elif defined (RAMTST_STOP_SEC_VAR_POWER_ON_INIT_8)
   #ifndef VAR_8_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_8_SEC_STARTED
     #undef  RAMTST_STOP_SEC_VAR_POWER_ON_INIT_8
     #define DEFAULT_STOP_SEC_VAR_8BIT
  #endif

/* core 0*/
#elif defined (RAMTST_CORE0_START_SEC_VAR_POWER_ON_INIT_8_LOCAL)
   #ifdef VAR_8_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_8_SEC_STARTED
     #undef  RAMTST_CORE0_START_SEC_VAR_POWER_ON_INIT_8_LOCAL
     #define DEFAULT_START_SEC_VAR_8BIT_CORE0
   #endif
#elif defined (RAMTST_CORE0_STOP_SEC_VAR_POWER_ON_INIT_8_LOCAL)
   #ifndef VAR_8_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_8_SEC_STARTED
     #undef  RAMTST_CORE0_STOP_SEC_VAR_POWER_ON_INIT_8_LOCAL
     #define DEFAULT_STOP_SEC_VAR_8BIT_CORE0
   #endif
/* core 1*/
#elif defined (RAMTST_CORE1_START_SEC_VAR_POWER_ON_INIT_8_LOCAL)
   #ifdef VAR_8_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_8_SEC_STARTED
     #undef  RAMTST_CORE1_START_SEC_VAR_POWER_ON_INIT_8_LOCAL
     #define DEFAULT_START_SEC_VAR_8BIT_CORE1
   #endif
#elif defined (RAMTST_CORE1_STOP_SEC_VAR_POWER_ON_INIT_8_LOCAL)
   #ifndef VAR_8_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_8_SEC_STARTED
     #undef  RAMTST_CORE1_STOP_SEC_VAR_POWER_ON_INIT_8_LOCAL
     #define DEFAULT_STOP_SEC_VAR_8BIT_CORE1
   #endif
    
/* core 2*/
#elif defined (RAMTST_CORE2_START_SEC_VAR_POWER_ON_INIT_8_LOCAL)
   #ifdef VAR_8_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_8_SEC_STARTED
     #undef  RAMTST_CORE2_START_SEC_VAR_POWER_ON_INIT_8_LOCAL
     #define DEFAULT_START_SEC_VAR_8BIT_CORE2
   #endif
#elif defined (RAMTST_CORE2_STOP_SEC_VAR_POWER_ON_INIT_8_LOCAL)
   #ifndef VAR_8_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_8_SEC_STARTED
     #undef  RAMTST_CORE2_STOP_SEC_VAR_POWER_ON_INIT_8_LOCAL
     #define DEFAULT_STOP_SEC_VAR_8BIT_CORE2
   #endif
   
/* core 3*/
#elif defined (RAMTST_CORE3_START_SEC_VAR_POWER_ON_INIT_8_LOCAL)
   #ifdef VAR_8_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_8_SEC_STARTED
     #undef  RAMTST_CORE3_START_SEC_VAR_POWER_ON_INIT_8_LOCAL
     #define DEFAULT_START_SEC_VAR_8BIT_CORE3
   #endif
#elif defined (RAMTST_CORE3_STOP_SEC_VAR_POWER_ON_INIT_8_LOCAL)
   #ifndef VAR_8_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_8_SEC_STARTED
     #undef  RAMTST_CORE3_STOP_SEC_VAR_POWER_ON_INIT_8_LOCAL
     #define DEFAULT_STOP_SEC_VAR_8BIT_CORE3
   #endif

#elif defined (RAMTST_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED
   #endif
#elif defined (RAMTST_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED
   #endif

/* core 0*/
#elif defined (RAMTST_CORE0_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE0_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE0
   #endif
#elif defined (RAMTST_CORE0_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE0_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE0
   #endif

   /* core 1*/
#elif defined (RAMTST_CORE1_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE1_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE1
   #endif
#elif defined (RAMTST_CORE1_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE1_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE1
   #endif   
   /* core 2*/
#elif defined (RAMTST_CORE2_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE2_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE2
   #endif
#elif defined (RAMTST_CORE2_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE2_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE2
   #endif
   
   /* core 3*/
#elif defined (RAMTST_CORE3_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE3_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE3
   #endif
#elif defined (RAMTST_CORE3_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE3_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE3
   #endif

#elif defined (RAMTST_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #ifdef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
    #error "Memory section is not stopped"
  #else
    #define VAR_NOINIT_UNSPECIFIED_SEC_STARTED
    #undef  RAMTST_START_SEC_VAR_NO_INIT_UNSPECIFIED
    #define DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED
  #endif
#elif defined (RAMTST_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #ifndef VAR_NOINIT_UNSPECIFIED_SEC_STARTED
    #error "Memory section is not started"
  #else
    #undef  VAR_NOINIT_UNSPECIFIED_SEC_STARTED
    #undef  RAMTST_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
    #define DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #endif

#elif defined (RAMTST_START_SEC_VAR_INIT_8)
   #ifdef VAR_INIT_8_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_8_SEC_STARTED
     #undef  RAMTST_START_SEC_VAR_INIT_8
     #define DEFAULT_START_SEC_VAR_8BIT
   #endif
#elif defined (RAMTST_STOP_SEC_VAR_INIT_8)
   #ifndef VAR_INIT_8_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_8_SEC_STARTED
     #undef  RAMTST_STOP_SEC_VAR_INIT_8
     #define DEFAULT_STOP_SEC_VAR_8BIT
   #endif


#elif defined (RAMTST_START_SEC_VAR_INIT_16)
   #ifdef VAR_INIT_16_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_16_SEC_STARTED
     #undef  RAMTST_START_SEC_VAR_INIT_16
     #define DEFAULT_START_SEC_VAR_16BIT
   #endif
#elif defined (RAMTST_STOP_SEC_VAR_INIT_16)
   #ifndef VAR_INIT_16_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_16_SEC_STARTED
     #undef  RAMTST_STOP_SEC_VAR_INIT_16
     #define DEFAULT_STOP_SEC_VAR_16BIT
   #endif

/* Core 0 */
#elif defined (RAMTST_CORE0_START_SEC_VAR_INIT_16_LOCAL)
   #ifdef VAR_INIT_16_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_16_SEC_STARTED
     #undef  RAMTST_CORE0_START_SEC_VAR_INIT_16_LOCAL
     #define DEFAULT_START_SEC_VAR_16BIT_CORE0
   #endif
#elif defined (RAMTST_CORE0_STOP_SEC_VAR_INIT_16_LOCAL)
   #ifndef VAR_INIT_16_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_16_SEC_STARTED
     #undef  RAMTST_CORE0_STOP_SEC_VAR_INIT_16_LOCAL
     #define DEFAULT_STOP_SEC_VAR_16BIT_CORE0
   #endif
/* Core 1 */
#elif defined (RAMTST_CORE1_START_SEC_VAR_INIT_16_LOCAL)
   #ifdef VAR_INIT_16_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_16_SEC_STARTED
     #undef  RAMTST_CORE1_START_SEC_VAR_INIT_16_LOCAL
     #define DEFAULT_START_SEC_VAR_16BIT_CORE1
   #endif
#elif defined (RAMTST_CORE1_STOP_SEC_VAR_INIT_16_LOCAL)
   #ifndef VAR_INIT_16_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_16_SEC_STARTED
     #undef  RAMTST_CORE1_STOP_SEC_VAR_INIT_16_LOCAL
     #define DEFAULT_STOP_SEC_VAR_16BIT_CORE1
   #endif
/* Core 2 */
#elif defined (RAMTST_CORE2_START_SEC_VAR_INIT_16_LOCAL)
   #ifdef VAR_INIT_16_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_16_SEC_STARTED
     #undef  RAMTST_CORE2_START_SEC_VAR_INIT_16_LOCAL
     #define DEFAULT_START_SEC_VAR_16BIT_CORE2
   #endif
#elif defined (RAMTST_CORE2_STOP_SEC_VAR_INIT_16_LOCAL)
   #ifndef VAR_INIT_16_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_16_SEC_STARTED
     #undef  RAMTST_CORE2_STOP_SEC_VAR_INIT_16_LOCAL
     #define DEFAULT_STOP_SEC_VAR_16BIT_CORE2
   #endif
   
/* Core 3 */
#elif defined (RAMTST_CORE3_START_SEC_VAR_INIT_16_LOCAL)
   #ifdef VAR_INIT_16_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_16_SEC_STARTED
     #undef  RAMTST_CORE3_START_SEC_VAR_INIT_16_LOCAL
     #define DEFAULT_START_SEC_VAR_16BIT_CORE3
   #endif
#elif defined (RAMTST_CORE3_STOP_SEC_VAR_INIT_16_LOCAL)
   #ifndef VAR_INIT_16_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_16_SEC_STARTED
     #undef  RAMTST_CORE3_STOP_SEC_VAR_INIT_16_LOCAL
     #define DEFAULT_STOP_SEC_VAR_16BIT_CORE3
   #endif

#elif defined (RAMTST_START_SEC_VAR_INIT_32)
   #ifdef VAR_INIT_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_32_SEC_STARTED
     #undef  RAMTST_START_SEC_VAR_INIT_32
     #define DEFAULT_START_SEC_VAR_32BIT
   #endif
#elif defined (RAMTST_STOP_SEC_VAR_INIT_32)
   #ifndef VAR_INIT_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_32_SEC_STARTED
     #undef  RAMTST_STOP_SEC_VAR_INIT_32
     #define DEFAULT_STOP_SEC_VAR_32BIT
   #endif

   /* core 0 */
#elif defined (RAMTST_CORE0_START_SEC_VAR_INIT_32_LOCAL)
   #ifdef VAR_INIT_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_32_SEC_STARTED
     #undef  RAMTST_CORE0_START_SEC_VAR_INIT_32_LOCAL
     #define DEFAULT_START_SEC_VAR_32BIT_CORE0
   #endif
#elif defined (RAMTST_CORE0_STOP_SEC_VAR_INIT_32_LOCAL)
   #ifndef VAR_INIT_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_32_SEC_STARTED
     #undef  RAMTST_CORE0_STOP_SEC_VAR_INIT_32_LOCAL
     #define DEFAULT_STOP_SEC_VAR_32BIT_CORE0
   #endif
   /* core 1 */
#elif defined (RAMTST_CORE1_START_SEC_VAR_INIT_32_LOCAL)
   #ifdef VAR_INIT_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_32_SEC_STARTED
     #undef  RAMTST_CORE1_START_SEC_VAR_INIT_32_LOCAL
     #define DEFAULT_START_SEC_VAR_32BIT_CORE1
   #endif
#elif defined (RAMTST_CORE1_STOP_SEC_VAR_INIT_32_LOCAL)
   #ifndef VAR_INIT_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_32_SEC_STARTED
     #undef  RAMTST_CORE1_STOP_SEC_VAR_INIT_32_LOCAL
     #define DEFAULT_STOP_SEC_VAR_32BIT_CORE1
   #endif

   /* core 2 */
#elif defined (RAMTST_CORE2_START_SEC_VAR_INIT_32_LOCAL)
   #ifdef VAR_INIT_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_32_SEC_STARTED
     #undef  RAMTST_CORE2_START_SEC_VAR_INIT_32_LOCAL
     #define DEFAULT_START_SEC_VAR_32BIT_CORE2
   #endif
#elif defined (RAMTST_CORE2_STOP_SEC_VAR_INIT_32_LOCAL)
   #ifndef VAR_INIT_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_32_SEC_STARTED
     #undef  RAMTST_CORE2_STOP_SEC_VAR_INIT_32_LOCAL
     #define DEFAULT_STOP_SEC_VAR_32BIT_CORE2
   #endif
   
   /* core 3 */
#elif defined (RAMTST_CORE3_START_SEC_VAR_INIT_32_LOCAL)
   #ifdef VAR_INIT_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_32_SEC_STARTED
     #undef  RAMTST_CORE3_START_SEC_VAR_INIT_32_LOCAL
     #define DEFAULT_START_SEC_VAR_32BIT_CORE3
   #endif
#elif defined (RAMTST_CORE3_STOP_SEC_VAR_INIT_32_LOCAL)
   #ifndef VAR_INIT_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_32_SEC_STARTED
     #undef  RAMTST_CORE3_STOP_SEC_VAR_INIT_32_LOCAL
     #define DEFAULT_STOP_SEC_VAR_32BIT_CORE3
   #endif

#elif defined (RAMTST_START_SEC_VAR_INIT_UNSPECIFIED)
   #ifdef VAR_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_START_SEC_VAR_INIT_UNSPECIFIED
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED
   #endif
#elif defined (RAMTST_STOP_SEC_VAR_INIT_UNSPECIFIED)
   #ifndef VAR_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_STOP_SEC_VAR_INIT_UNSPECIFIED
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED
   #endif

/* core 0 */
#elif defined (RAMTST_CORE0_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE0_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE0
   #endif
#elif defined (RAMTST_CORE0_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE0_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE0
   #endif   
/* core 1 */
#elif defined (RAMTST_CORE1_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE1_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE1
   #endif
#elif defined (RAMTST_CORE1_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE1_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE1
   #endif   
/* core 2 */
#elif defined (RAMTST_CORE2_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE2_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE2
   #endif
#elif defined (RAMTST_CORE2_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE2_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE2
   #endif
   
   /* core 3 */
#elif defined (RAMTST_CORE3_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifdef VAR_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define VAR_INIT_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE3_START_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE3
   #endif
#elif defined (RAMTST_CORE3_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL)
   #ifndef VAR_INIT_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  VAR_INIT_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_CORE3_STOP_SEC_VAR_INIT_UNSPECIFIED_LOCAL
     #define DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE3
   #endif

#elif defined (RAMTST_START_SEC_CONST_8)
   #ifdef CONST_8_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define CONST_8_SEC_STARTED
     #undef  RAMTST_START_SEC_CONST_8
     #define DEFAULT_START_SEC_CONST_8BIT
   #endif
#elif defined (RAMTST_STOP_SEC_CONST_8)
   #ifndef CONST_8_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  CONST_8_SEC_STARTED
     #undef  RAMTST_STOP_SEC_CONST_8
     #define DEFAULT_STOP_SEC_CONST_8BIT
   #endif

#elif defined (RAMTST_START_SEC_CONST_16)
   #ifdef CONST_16_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define CONST_16_SEC_STARTED
     #undef  RAMTST_START_SEC_CONST_16
     #define DEFAULT_START_SEC_CONST_16BIT
   #endif
#elif defined (RAMTST_STOP_SEC_CONST_16)
   #ifndef CONST_16_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  CONST_16_SEC_STARTED
     #undef  RAMTST_STOP_SEC_CONST_16
     #define DEFAULT_STOP_SEC_CONST_16BIT
   #endif

#elif defined (RAMTST_START_SEC_CONST_32)
   #ifdef CONST_32_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define CONST_32_SEC_STARTED
     #undef  RAMTST_START_SEC_CONST_32
     #define DEFAULT_START_SEC_CONST_32BIT
   #endif
#elif defined (RAMTST_STOP_SEC_CONST_32)
   #ifndef CONST_32_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  CONST_32_SEC_STARTED
     #undef  RAMTST_STOP_SEC_CONST_32
     #define DEFAULT_STOP_SEC_CONST_32BIT
   #endif

#elif defined (RAMTST_START_SEC_PUBLIC_CODE)
   #ifdef PUBLIC_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define PUBLIC_CODE_SEC_STARTED
     #undef  RAMTST_START_SEC_PUBLIC_CODE
     #pragma ghs section text=".RAMTST_PUBLIC_CODE_ROM"
   #endif
#elif defined (RAMTST_STOP_SEC_PUBLIC_CODE)
   #ifndef PUBLIC_CODE_SEC_STARTED
      #error "Memory section is not started"
   #else
     #undef  PUBLIC_CODE_SEC_STARTED
     #undef  RAMTST_STOP_SEC_PUBLIC_CODE
     #define DEFAULT_STOP_SEC_CODE
   #endif

#elif defined (RAMTST_START_SEC_PRIVATE_CODE)
   #ifdef PRIVATE_CODE_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define PRIVATE_CODE_SEC_STARTED
     #undef  RAMTST_START_SEC_PRIVATE_CODE
     #pragma ghs section text=".RAMTST_PRIVATE_CODE_ROM"
   #endif
#elif defined (RAMTST_STOP_SEC_PRIVATE_CODE)
   #ifndef PRIVATE_CODE_SEC_STARTED
     #error "Memory section is not started"
   #else
     #undef  PRIVATE_CODE_SEC_STARTED
     #undef  RAMTST_STOP_SEC_PRIVATE_CODE
     #define DEFAULT_STOP_SEC_CODE
   #endif

#elif defined (RAMTST_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
   #ifdef CONFIG_DATA_PREBUILD_UNSPECIFIED_SEC_STARTED
     #error "Memory section is not stopped"
   #else
     #define CONFIG_DATA_PREBUILD_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
     #pragma ghs startdata
     #pragma ghs section rodata=".RAMTST_CFG_DATA_UNSPECIFIED"
   #endif
#elif defined (RAMTST_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
   #ifndef CONFIG_DATA_PREBUILD_UNSPECIFIED_SEC_STARTED
      #error "Memory section is not started"
   #else
     #undef  CONFIG_DATA_PREBUILD_UNSPECIFIED_SEC_STARTED
     #undef  RAMTST_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
     #pragma ghs section rodata=default
     #pragma ghs enddata
   #endif
/* -------------------------------------------------------------------------- */
/* End of module section mapping                                              */
/* -------------------------------------------------------------------------- */
#else
  #error "RamTst_MemMap.h: No valid section define found"
#endif  /* START_WITH_IF */


/*******************************************************************************
**                      Default section mapping                               **
*******************************************************************************/
/* general start of #elif chain whith #if                                     */
#if defined (START_WITH_IF)

/* -------------------------------------------------------------------------- */
/* RAM variables initialized from ROM on reset                                */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_VAR_8BIT)
   #undef      DEFAULT_START_SEC_VAR_8BIT
   #pragma ghs startdata
   #pragma ghs section data=".RAM_8BIT"
#elif defined (DEFAULT_STOP_SEC_VAR_8BIT)
   #undef      DEFAULT_STOP_SEC_VAR_8BIT
   #pragma ghs section data=default
   #pragma ghs enddata

/* Core 0 */
#elif defined (DEFAULT_START_SEC_VAR_8BIT_CORE0)
   #undef      DEFAULT_START_SEC_VAR_8BIT_CORE0
   #pragma ghs startdata
   #pragma ghs section data=".RAM_8BIT_CORE0"
#elif defined (DEFAULT_STOP_SEC_VAR_8BIT_CORE0)
   #undef      DEFAULT_STOP_SEC_VAR_8BIT_CORE0
   #pragma ghs section data=default
   #pragma ghs enddata
/* Core 1 */
#elif defined (DEFAULT_START_SEC_VAR_8BIT_CORE1)
   #undef      DEFAULT_START_SEC_VAR_8BIT_CORE1
   #pragma ghs startdata
   #pragma ghs section data=".RAM_8BIT_CORE1"
#elif defined (DEFAULT_STOP_SEC_VAR_8BIT_CORE1)
   #undef      DEFAULT_STOP_SEC_VAR_8BIT_CORE1
   #pragma ghs section data=default
   #pragma ghs enddata
/* Core 2 */
#elif defined (DEFAULT_START_SEC_VAR_8BIT_CORE2)
   #undef      DEFAULT_START_SEC_VAR_8BIT_CORE2
   #pragma ghs startdata
   #pragma ghs section data=".RAM_8BIT_CORE2"
#elif defined (DEFAULT_STOP_SEC_VAR_8BIT_CORE2)
   #undef      DEFAULT_STOP_SEC_VAR_8BIT_CORE2
   #pragma ghs section data=default
   #pragma ghs enddata
/* Core 3 */
#elif defined (DEFAULT_START_SEC_VAR_8BIT_CORE3)
   #undef      DEFAULT_START_SEC_VAR_8BIT_CORE3
   #pragma ghs startdata
   #pragma ghs section data=".RAM_8BIT_CORE3"
#elif defined (DEFAULT_STOP_SEC_VAR_8BIT_CORE3)
   #undef      DEFAULT_STOP_SEC_VAR_8BIT_CORE3
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
/* Core 0 */
#elif defined (DEFAULT_START_SEC_VAR_16BIT_CORE0)
   #undef      DEFAULT_START_SEC_VAR_16BIT_CORE0
   #pragma ghs startdata
   #pragma ghs section data=".RAM_16BIT_CORE0"
#elif defined (DEFAULT_STOP_SEC_VAR_16BIT_CORE0)
   #undef      DEFAULT_STOP_SEC_VAR_16BIT_CORE0
   #pragma ghs section data=default
   #pragma ghs enddata
/* Core 1 */
#elif defined (DEFAULT_START_SEC_VAR_16BIT_CORE1)
   #undef      DEFAULT_START_SEC_VAR_16BIT_CORE1
   #pragma ghs startdata
   #pragma ghs section data=".RAM_16BIT_CORE1"
#elif defined (DEFAULT_STOP_SEC_VAR_16BIT_CORE1)
   #undef      DEFAULT_STOP_SEC_VAR_16BIT_CORE1
   #pragma ghs section data=default
   #pragma ghs enddata
/* Core 2 */
#elif defined (DEFAULT_START_SEC_VAR_16BIT_CORE2)
   #undef      DEFAULT_START_SEC_VAR_16BIT_CORE2
   #pragma ghs startdata
   #pragma ghs section data=".RAM_16BIT_CORE2"
#elif defined (DEFAULT_STOP_SEC_VAR_16BIT_CORE2)
   #undef      DEFAULT_STOP_SEC_VAR_16BIT_CORE2
   #pragma ghs section data=default
   #pragma ghs enddata
/* Core 3 */
#elif defined (DEFAULT_START_SEC_VAR_16BIT_CORE3)
   #undef      DEFAULT_START_SEC_VAR_16BIT_CORE3
   #pragma ghs startdata
   #pragma ghs section data=".RAM_16BIT_CORE3"
#elif defined (DEFAULT_STOP_SEC_VAR_16BIT_CORE3)
   #undef      DEFAULT_STOP_SEC_VAR_16BIT_CORE3
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
/* Core 0 */
#elif defined (DEFAULT_START_SEC_VAR_32BIT_CORE0)
   #undef      DEFAULT_START_SEC_VAR_32BIT_CORE0
   #pragma ghs startdata
   #pragma ghs section data=".RAM_32BIT_CORE0"
#elif defined (DEFAULT_STOP_SEC_VAR_32BIT_CORE0)
   #undef      DEFAULT_STOP_SEC_VAR_32BIT_CORE0
   #pragma ghs section data=default
   #pragma ghs enddata
/* Core 1 */
#elif defined (DEFAULT_START_SEC_VAR_32BIT_CORE1)
   #undef      DEFAULT_START_SEC_VAR_32BIT_CORE1
   #pragma ghs startdata
   #pragma ghs section data=".RAM_32BIT_CORE1"
#elif defined (DEFAULT_STOP_SEC_VAR_32BIT_CORE1)
   #undef      DEFAULT_STOP_SEC_VAR_32BIT_CORE1
   #pragma ghs section data=default
   #pragma ghs enddata
/* Core 2 */
#elif defined (DEFAULT_START_SEC_VAR_32BIT_CORE2)
   #undef      DEFAULT_START_SEC_VAR_32BIT_CORE2
   #pragma ghs startdata
   #pragma ghs section data=".RAM_32BIT_CORE2"
#elif defined (DEFAULT_STOP_SEC_VAR_32BIT_CORE2)
   #undef      DEFAULT_STOP_SEC_VAR_32BIT_CORE2
   #pragma ghs section data=default
   #pragma ghs enddata
/* Core 3 */
#elif defined (DEFAULT_START_SEC_VAR_32BIT_CORE3)
   #undef      DEFAULT_START_SEC_VAR_32BIT_CORE3
   #pragma ghs startdata
   #pragma ghs section data=".RAM_32BIT_CORE3"
#elif defined (DEFAULT_STOP_SEC_VAR_32BIT_CORE3)
   #undef      DEFAULT_STOP_SEC_VAR_32BIT_CORE3
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
/* Core 0 */
#elif defined (DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE0)
   #undef      DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE0
   #pragma ghs startdata
   #pragma ghs section data=".RAM_UNSPECIFIED_CORE0"
#elif defined (DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE0)
   #undef      DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE0
   #pragma ghs section data=default
   #pragma ghs enddata

/* Core 1 */
#elif defined (DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE1)
   #undef      DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE1
   #pragma ghs startdata
   #pragma ghs section data=".RAM_UNSPECIFIED_CORE1"
#elif defined (DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE1)
   #undef      DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE1
   #pragma ghs section data=default
   #pragma ghs enddata

/* Core 2 */
#elif defined (DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE2)
   #undef      DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE2
   #pragma ghs startdata
   #pragma ghs section data=".RAM_UNSPECIFIED_CORE2"
#elif defined (DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE2)
   #undef      DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE2
   #pragma ghs section data=default
   #pragma ghs enddata
   
/* Core 3 */
#elif defined (DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE3)
   #undef      DEFAULT_START_SEC_VAR_UNSPECIFIED_CORE3
   #pragma ghs startdata
   #pragma ghs section data=".RAM_UNSPECIFIED_CORE3"
#elif defined (DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE3)
   #undef      DEFAULT_STOP_SEC_VAR_UNSPECIFIED_CORE3
   #pragma ghs section data=default
   #pragma ghs enddata

/* -------------------------------------------------------------------------- */
/* RAM variables not initialized                                              */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef      DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED
  #pragma ghs startdata
  #pragma ghs section bss=".NOINIT_RAM_UNSPECIFIED"
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef      DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  #pragma ghs section bss=default
  #pragma ghs enddata
/* -------------------------------------------------------------------------- */
/* RAM variables frequently used or accessed bitwise                          */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* ROM constants                                                              */
/* -------------------------------------------------------------------------- */

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

/* -------------------------------------------------------------------------- */
/* ROM FAR constants                                                          */
/* -------------------------------------------------------------------------- */

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
