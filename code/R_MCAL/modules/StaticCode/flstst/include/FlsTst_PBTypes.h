/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = FlsTst_PBTypes.h                                                                                    */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the type definitions of Post-build Time Parameters.                                             */
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
 * 1.4.1:  30/06/2025  : Update SW-VERSION
 * 1.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E 
 * 1.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Relase
 * 1.1.2:  31/10/2024  : As part of QAC 9.5.0 support, following changes are made:
 *                       1. Remove QAC message 1534
 * 1.1.0:  22/02/2024  : Update SW-VERSION to 1.1.0
 * 1.0.1:  18/10/2023  : Add QAC message 1534, 3684
 *         05/10/2023  : Add CONFIG_DATA_POSTBUILD_UNSPECIFIED for gentool output
 * 1.0.0:  17/03/2023  : Initial Version.
 *
 */
/**********************************************************************************************************************/

#ifndef FLSTST_PBTYPES_H
#define FLSTST_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#if (FLSTST_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_FlsTst.h"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : CERTCCM PRE05, MISRA C:2012 Rule-20.10                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : MISRA C:2012 Rule-8.11, CERTCCM ARR02                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define FLSTST_PBTYPES_AR_RELEASE_MAJOR_VERSION    FLSTST_TYPES_AR_RELEASE_MAJOR_VERSION
#define FLSTST_PBTYPES_AR_RELEASE_MINOR_VERSION    FLSTST_TYPES_AR_RELEASE_MINOR_VERSION
#define FLSTST_PBTYPES_AR_RELEASE_REVISION_VERSION FLSTST_TYPES_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FLSTST_PBTYPES_SW_MAJOR_VERSION            FLSTST_TYPES_SW_MAJOR_VERSION
#define FLSTST_PBTYPES_SW_MINOR_VERSION            FLSTST_TYPES_SW_MINOR_VERSION

/* Macro to calculate data base value */
#define FLSTST_DBTOC_VALUE                                                          \
  (((uint32)FLSTST_VENDOR_ID_VALUE << 22U) | ((uint32)FLSTST_MODULE_ID_VALUE << 14U) | \
   ((uint32)FLSTST_SW_MAJOR_VERSION_VALUE << 8U) | ((uint32)FLSTST_SW_MINOR_VERSION_VALUE << 3U))

/* Exclusive area from SchM */
#if (FLSTST_CRITICAL_SECTION_PROTECTION == STD_ON)
#define FLSTST_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_FlsTst_##Exclusive_Area()                              /* PRQA S 0342 # JV-01 */

#define FLSTST_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_FlsTst_##Exclusive_Area()                               /* PRQA S 0342 # JV-01 */
#else
#define FLSTST_ENTER_CRITICAL_SECTION(Exclusive_Area)
#define FLSTST_EXIT_CRITICAL_SECTION(Exclusive_Area)
#endif /* #if (FLSTST_CRITICAL_SECTION_PROTECTION == STD_ON) */

/* True/false value */
#define FLSTST_TRUE                (boolean)1
#define FLSTST_FALSE               (boolean)0

/* ECC register default value */
#define CF_00SEADR_DEFAULT      0x00000000UL                                                                            
#define CF_00DEADR_DEFAULT      0x00000000UL                                                                            
#define CFSECCCTL_DEFAULT       0x00000000UL                                                                            
#define CFCECCCTL_DEFAULT       0x00000000UL                                                                            
#define CF_SERSTR_DEFAULT       0x00000000UL                                                                            
#define CF_ERRINT_DEFAULT       0x00000087UL                                                                            
#define CF_DERSTR_DEFAULT       0x00000000UL                                                                            

/* KCRC register default value */
#define FLSTST_KCRCDOUT_RESET_VAL       0xFFFFFFFFUL
#define FLST_KCRCCTL_RESET_VAL          0x001F0000UL
#define FLST_KCRCPOLY0_RESET_VAL        0x04C11DB7UL

/* KCRC register control value */
#define FLSTST_CRC8_2F_CNTL                 0x00070003UL
#define FLSTST_CRC8_2F_INITIAL_VALUE        0x000000FFUL
#define FLSTST_CRC8_2F_POLY                 0x0000002FUL

#define FLSTST_CRC8_SAE_J1850_CNTL          0x00070003UL
#define FLSTST_CRC8_SAE_J1850_INITIAL_VALUE 0x000000FFUL
#define FLSTST_CRC8_SAE_J1850_POLY          0x0000001DUL

#define FLSTST_CRC15_CRC15CAN_CNTL          0x000E0003UL
#define FLSTST_CRC15_CRC15CAN_INITIAL_VALUE 0x00000000UL
#define FLSTST_CRC15_CRC15CAN_POLY          0x00004599UL

#define FLSTST_CRC16_CCITT16_CNTL           0x000F0003UL
#define FLSTST_CRC16_CCITT16_INITIAL_VALUE  0x0000FFFFUL
#define FLSTST_CRC16_CCITT16_POLY           0x00001021UL

#define FLSTST_CRC16_BAICHEVA00_CNTL          0x000F0003UL
#define FLSTST_CRC16_BAICHEVA00_INITIAL_VALUE 0x00000000UL
#define FLSTST_CRC16_BAICHEVA00_POLY          0x000090D9UL

#define FLSTST_CRC16_ARC_CNTL               0x000F0123UL
#define FLSTST_CRC16_ARC_INITIAL_VALUE      0x00000000UL
#define FLSTST_CRC16_ARC_POLY               0x00008005UL

#define FLSTST_CRC32_CNTL                   0x001F0123UL
#define FLSTST_CRC32_INITIAL_VALUE          0xFFFFFFFFUL
#define FLSTST_CRC32_POLY                   0x04C11DB7UL

#define FLSTST_CRC32_REVPOLY_CNTL           0x001F0013UL
#define FLSTST_CRC32_REVPOLY_INITIAL_VALUE  0xFFFFFFFFUL
#define FLSTST_CRC32_REVPOLY_POLY           0xEDB88320UL

#define FLSTST_CRC32_C_CNTL                 0x001F0123UL
#define FLSTST_CRC32_C_INITIAL_VALUE        0xFFFFFFFFUL
#define FLSTST_CRC32_C_POLY                 0x1EDC6F41UL

#define FLSTST_CRC32_P4_CNTL                0x001F0123UL
#define FLSTST_CRC32_P4_INITIAL_VALUE       0xFFFFFFFFUL
#define FLSTST_CRC32_P4_POLY                0xF4ACFB13UL

#define FLSTST_CRC64_ECMA_CNTL              0x003F0123UL
#define FLSTST_CRC64_ECMA_INITIAL_VALUE     0xFFFFFFFFUL
#define FLSTST_CRC64_ECMA_POLY0             0xA9EA3693UL
#define FLSTST_CRC64_ECMA_POLY1             0x42F0E1EBUL

/* Mask to get CRC value */
#define FLSTST_8BIT_CRC_MASK       0x000000FFUL
#define FLSTST_15BIT_CRC_MASK      0x00007FFFUL
#define FLSTST_16BIT_CRC_MASK      0x0000FFFFUL

/* ECC control value */
#define FLSTST_ECC_SEC_ACTIVATE           0x00000000UL                                                                  
#define FLSTST_ECC_SEC_APE_ACTIVATE       0x00000000UL                                                                  
#define FLSTST_ECC_DISABLE_NOTIFICATION   0x00000000UL                                                                  
#define FLSTST_ECC_ENABLE_NOTIFICATION    0x00000087UL                                                                  
#define FLSTST_2BIT_ERROR_VALUE           0xC0000000UL                                                                  
#define FLSTST_ECC_TEST_DELAY             (uint8)0x1F                                                                   
#define FLSTST_CF_GLOBAL_WALK1_END        (uint8)0x8A                                                                   
#define FLSTST_CF_GLOBAL_ALL1_END         (uint8)0x8B                                                                   
#define FLSTST_ECC_CF_GLOBAL_END_PATTERN  (uint8)0x8C                                                                   
#define FLSTST_CF_BANK_WALK1_END          (uint16)0x10B                                                                 
#define FLSTST_CF_BANK_ALL1_END           (uint16)0x10C                                                                 
#define FLSTST_ECC_CF_BANK_END_PATTERN    (uint16)0x10D                                                                 
#define FLSTST_ECC_CF_BANK_APE_PATTERN    (uint16)0x10E                                                                 
#define FLSTST_GET_ECC_ERR_ADDR(reg)      ((reg & 0x03FFFFFCUL) << 2)                                                   

/* Number definition */
#define FLSTST_ZERO             (uint8)0x00
#define FLSTST_ONE              (uint8)0x01
#define FLSTST_TWO              (uint8)0x02
#define FLSTST_THREE            (uint8)0x03                                                                             
#define FLSTST_FOUR             (uint8)0x04
#define FLSTST_SIX              (uint8)0x06                                                                             
#define FLSTST_SEVEN            (uint8)0x07                                                                             
#define FLSTST_EIGHT            (uint8)0x08
#define FLSTST_THIRTY_TWO       (uint8)0x20                                                                             
#define FLSTST_LONG_WORD_ZERO   0x00000000UL
#define FLSTST_ALL_ZERO         0x00000000UL
#define FLSTST_ALL1_VALUE       0xFFFFFFFFUL
#define FLSTST_8BIT_ALL_ONE     0x000000FFUL
#define FLSTST_32BIT_ALL_ONE    0xFFFFFFFFUL


#define FLSTST_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "FlsTst_MemMap.h"

extern CONST(FlsTstBlock_ConfigType, FLSTST_CONST) FlsTst_GstFlsTstBlockBgnd[];                                         /* PRQA S 3684 # JV-01 */
extern CONST(FlsTstBlock_ConfigType, FLSTST_CONST) FlsTst_GstFlsTstBlockFgnd[];                                         /* PRQA S 3684 # JV-01 */

#define FLSTST_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "FlsTst_MemMap.h"
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* FLSTST_PBTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
