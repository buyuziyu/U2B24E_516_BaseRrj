/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas R22-11 X2x MCAL Components                                                          */
/* Module       = MemAcc_PBTypes.h                                                                                    */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the type definitions of Post Build time Parameters                                              */
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
/*              Devices:        RH850/X2x                                                                             */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.1.1:  30/06/2025:  Remove SW-VERSION in file header
 * 1.1.0:  30/06/2025:  Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 1.0.3:  25/04/2025:  Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 
 * 1.0.2:  31/03/2025:  Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 * 1.0.1:  28/02/2025:  Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024:  Update SW-VERSION for Ver22.02.00 U2Bx Final Release. 
 * 0.0.2:  31/10/2024:  Define Mem Services Name Macros
 * 0.0.1:  30/08/2024:  Initial Version.
 */
/**********************************************************************************************************************/
#ifndef MEMACC_PBTYPES_H
#define MEMACC_PBTYPES_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Type definitions */
#include "Std_Types.h"
#include "MemAcc_Cfg.h"
#include "MemAcc_Types.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MEMACC_PBTYPES_AR_RELEASE_MAJOR_VERSION    MEMACC_AR_RELEASE_MAJOR_VERSION
#define MEMACC_PBTYPES_AR_RELEASE_MINOR_VERSION    MEMACC_AR_RELEASE_MINOR_VERSION
#define MEMACC_PBTYPES_AR_RELEASE_REVISION_VERSION MEMACC_AR_RELEASE_REVISION_VERSION
/* File version information */
#define MEMACC_PBTYPES_SW_MAJOR_VERSION            MEMACC_SW_MAJOR_VERSION
#define MEMACC_PBTYPES_SW_MINOR_VERSION            MEMACC_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : MISRA C:2012 Rule-20.10, CERTCCM PRE05                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Macro Defines                                                    **
***********************************************************************************************************************/
#define MEMACC_FIXED_ABI_VERSION  1
/* General defines */
#define MEMACC_DBTOC_VALUE                                                                                       \
  ((uint32)(((uint32)MEMACC_VENDOR_ID_VALUE << MEMACC_TWENTY_TWO) | ((uint32)MEMACC_MODULE_ID_VALUE << MEMACC_FOURTEEN) | \
            ((uint32)MEMACC_SW_MAJOR_VERSION_VALUE << MEMACC_EIGHT) | ((uint32)MEMACC_SW_MINOR_VERSION_VALUE << MEMACC_THREE)))

/* Macros to avoid direct numbers */
#define MEMACC_ZERO               ((uint8)0)
#define MEMACC_ONE                ((uint8)1)
#define MEMACC_TWO                ((uint8)2)
#define MEMACC_THREE              ((uint8)3)
#define MEMACC_FOUR               ((uint8)4)
#define MEMACC_EIGHT              ((uint16)8)
#define MEMACC_FOURTEEN           ((uint16)14)
#define MEMACC_TWENTY_TWO         ((uint32)22)

/* Macros for boolean variables */
#define MEMACC_FALSE              ((boolean)0)
#define MEMACC_TRUE               ((boolean)1)

#define MEMACC_INVALID_AREA_ID    (0xFFFFU)
#define MEMACC_RELOCATABLE_BINARY_MASK  0x1ULL

#define MEMACC_DIRECT_STATIC      (uint8)0
#define MEMACC_INDIRECT_DYNAMIC   (uint8)1
#define MEMACC_INDIRECT_STATIC    (uint8)2
/***********************************************************************************************************************
**                                      SchM Critical Section Protection Macros                                       **
***********************************************************************************************************************/
#define MEMACC_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_MemAcc_##Exclusive_Area()                              /* PRQA S 0342 # JV-01 */
#define MEMACC_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_MemAcc_##Exclusive_Area()                               /* PRQA S 0342 # JV-01 */
/***********************************************************************************************************************
**                                            Mem Services Name Macros                                                **
***********************************************************************************************************************/
#define MEMACC_MEM_API_CONCAT(PREFIX, REQ)            PREFIX##_##REQ                                                    /* PRQA S 0342 # JV-01 */
#define MEMACC_MEM_API_REQUEST(PREFIX, REQ)           MEMACC_MEM_API_CONCAT(PREFIX, REQ)                                
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : CERTCCM PRE05, MISRA C:2012 Rule-20.10                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                Extern declarations for Global Arrays Of Structures                                 **
***********************************************************************************************************************/

#endif /* MEMACC_PBTYPES_H  */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
