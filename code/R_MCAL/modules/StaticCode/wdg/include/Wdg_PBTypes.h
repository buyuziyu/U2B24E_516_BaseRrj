/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Wdg_PBTypes.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.4.1:  30/06/2025    : Remove SW-VERSION in file header 
 * 2.4.0:  30/06/2025    : Update SW-VERSION for RH850/Ver22.01.00 (D) U2Ax release
 * 2.3.2:  29/04/2025    : Update SW-VERSION for RH850/Ver22.00.03 U2Bx-E  
 * 2.3.1:  31/03/2025    : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 *                         Support QAC 11.6.0
 * 2.3.0:  28/02/2025    : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024    : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final release
 * 2.1.2:  30/10/2024    : Update SW-VERSION to 2.1.2
 * 2.1.1:  31/08/2024    : Update SW-VERSION to 2.1.1
 *                         Remove message (1:1534) and update Copyright.
 * 2.0.1:  21/10/2023    : Add message (1:1534).
           12/10/2023    : Update re-processor (WDG_AR_VERSION == WDG_AR_R22_11_VERSION) for support R22-11
 * 2.0.0   18/07/2023    : Delete #ifdef WDG_INSTANCE_INDEX macros related, delete Message (2:0841),
 *                         change SCHM_WDG_HEADER with "SchM_Wdg.h" 
 * 1.4.4:  02/12/2022    : Add re-processor (WDG_AR_VERSION == WDG_AR_R21_11_VERSION) for support R21-11
 *                         Update SW-VERSION to 1.4.4
 * 1.4.3:  10/05/2022    : Update SW-VERSION
 *                         Remove marco WDG_ROM
 *                         Change marco name WDG_TIME_UNIT_MSEC_TO_MICRO_SEC from TIME_UNIT_MSEC_TO_MICRO_SEC
 * 1.4.1:  06/12/2021    : Add INST6 to support U2Bx devices
 * 1.3.1:  07/07/2021    : Add QAC message 9.5.0
 *                         Format source code to 120 characters
 *                         Improve Violation tag (remove START/END)
 *         30/06/2021    : 1) Change file name from Wdg_59_PBTypes.h to Wdg_PBTypes.h.
 *                         2) Update header file macro to call file multiple times.
 *                         3) Using #include SCHM_WDG_HEADER instead of
 *                         #include "SchM_Wdg_59_Renesas.h"
 *                         4) Remove _VendorID  ("_59") in all macros.
 * 1.2.0:  26/08/2020    : Release
 * 1.1.0:  19/06/2020    : Release
 * 1.0.0:  20/03/2020    : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : CERTCCM PRE05, MISRA C:2012 Rule-20.10                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1534)    : The macro '%1s' is declared but not used within this project.                                */
/* Rule                : MISRA C:2012 Rule-2.5                                                                        */
/* JV-01 Justification : These macros are used for version checking in precompile or in user application.             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#ifndef WDG_PBTYPES_H
#define WDG_PBTYPES_H

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#if (WDG_CRITICAL_SECTION_PROTECTION == STD_ON)
/* Included for the declaration of the critical section protection functions */
#include "SchM_Wdg.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define WDG_PBTYPES_AR_RELEASE_MAJOR_VERSION    WDG_AR_RELEASE_MAJOR_VERSION
#define WDG_PBTYPES_AR_RELEASE_MINOR_VERSION    WDG_AR_RELEASE_MINOR_VERSION
#define WDG_PBTYPES_AR_RELEASE_REVISION_VERSION WDG_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define WDG_PBTYPES_SW_MAJOR_VERSION            WDG_SW_MAJOR_VERSION
#define WDG_PBTYPES_SW_MINOR_VERSION            WDG_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                              MISRA C Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    QAC Warning                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* The number to convert millisecond to microsecond */
#define WDG_TIME_UNIT_MSEC_TO_MICRO_SEC         1000UL

/* Type definition for trigger mode */
#define WDG_WINDOW                              1U                                                                      

/* Macros for watchdog driver execution area */
#define WDG_RAM                                 0U                                                                     

/* General defines */
#define WDG_DBTOC_VALUE                                                                                        \
  (((uint32)WDG_VENDOR_ID << 22UL) | ((uint32)WDG_MODULE_ID << 14UL) | ((uint32)WDG_SW_MAJOR_VERSION << 8UL) | \
   ((uint32)WDG_SW_MINOR_VERSION << 3UL))

#if (WDG_CRITICAL_SECTION_PROTECTION == STD_ON)
#define WDG_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Wdg_##Exclusive_Area()                                    /* PRQA S 0342 # JV-01 */
#define WDG_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Wdg_##Exclusive_Area()                                     /* PRQA S 0342 # JV-01 */
#endif /*WDG_CRITICAL_SECTION_PROTECTION*/
/***********************************************************************************************************************
**                                              DEM Report Error Macros                                               **
***********************************************************************************************************************/
#if (WDG_AR_VERSION == WDG_AR_422_VERSION)
#define WDG_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_ReportErrorStatus(EventId, EventStatus)
#elif ((WDG_AR_VERSION == WDG_AR_431_VERSION) || (WDG_AR_VERSION == WDG_AR_R22_11_VERSION))
#define WDG_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
#endif
#endif /* WDG_PBTYPES_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
