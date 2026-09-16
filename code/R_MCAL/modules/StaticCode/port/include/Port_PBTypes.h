/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Port_PBTypes.h                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020 - 2025 Renesas Electronics Corporation. All rights reserved.                                              */
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
 * 2.4.0: 30/06/2025 : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax Release
 * 2.3.2: 25/04/2025 : Update SW-VERSION for RH850/Ver22.00.03 U2Ax Release
 * 2.3.1: 28/02/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Ax Release
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release 
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D U2Bx Final Release
 * 2.1.2: 31/10/2024 : Update SW-VERSION to 2.1.2 for Ver22.01.02 U2Bx Beta2
 * 2.1.0: 28/02/2024 : Update SW-VERSION to 2.1.0
 *                   : Remove Msg 1536
 * 2.0.1: 19/10/2023 : Add Msg 3630, 1039
 * 2.0.1: 19/10/2023 : Add Msg 1536
 *        16/10/2023 : Change name for macro DNFP03_AVAILABLE to PORT_DNFP03_AVAILABLE
 *        30/09/2023 : Update condition 'PORT_AR_VERSION == PORT_AR_R21_11_VERSION' to
 *                     'PORT_AR_VERSION == PORT_AR_R22_11_VERSION'
 * 2.0.0: 01/08/2023 : Add define of ucPortPinCoreIndex when support multi-core
 *        25/05/2023 : Update PORT_AR_2111_VERSION to PORT_AR_R21_11_VERSION
 *        22/05/2023 : Remove redundant QAC message
 * 1.4.4: 30/09/2022 : Add condition DEM Report for support AR21-11
 * 1.4.3: 18/06/2022 : Add declaration for usModeAvailable, usModeDirIn, usModeDirOut, PORT_BYTE_ZERO, PORT_BYTE_ONE,
 *                     PORT_ALT_MODE_MASK, PORT_FOUR
 *        14/04/2022 : Remove macro: PORT_SHIFT_8, PORT_MSB_MASK, PORT_TRUE, PORT_FALSE, PORT_FOUR.
 *        12/04/2022 : Update SW-VERSION to 1.4.3
 * 1.4.1: 07/10/2021 : Update SW-VERSION to 1.4.1
 * 1.3.1: 02/07/2021 : Add QAC message 9.5.0
 *                     Format source code to 120 characters
 *                     Improve Violation tag (remove START/END)
 * 1.3.0: 12/11/2020 : Add definitions: PORT_THREE, PORT_TWO
 * 1.2.0: 28/07/2020 : Release.
 * 1.1.0: 19/06/2020 : Release.
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef PORT_PBTYPES_H
#define PORT_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Port_Device.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PORT_PBTYPES_AR_RELEASE_MAJOR_VERSION    PORT_AR_RELEASE_MAJOR_VERSION
#define PORT_PBTYPES_AR_RELEASE_MINOR_VERSION    PORT_AR_RELEASE_MINOR_VERSION
#define PORT_PBTYPES_AR_RELEASE_REVISION_VERSION PORT_AR_RELEASE_REVISION_VERSION
/* File version information */
#define PORT_PBTYPES_SW_MAJOR_VERSION            PORT_SW_MAJOR_VERSION
#define PORT_PBTYPES_SW_MINOR_VERSION            PORT_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : CERTCCM PRE05, MISRA C:2012 Rule-20.10                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1039)    : Treating array of length one as potentially flexible member.                                 */
/* Rule                : CERTCCM DCL38, MISRA C:2012 Dir-1.1, Rule-1.2                                                */
/* JV-01 Justification : Use array of length as the final member has no problem by manual reviewing.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* General defines */
#define PORT_ZERO                                (uint8)0x00U
#define PORT_ONE                                 (uint8)0x01U
#define PORT_TWO                                 (uint8)0x02U
#define PORT_THREE                               (uint8)0x03U
#define PORT_FOUR                                (uint8)0x04U

#define PORT_BYTE_ZERO                           (uint16)0x0000U
#define PORT_BYTE_ONE                            (uint16)0x0001U
#define PORT_ALT_MODE_MASK                       (uint16)0x000FU


#define PORT_UNINITIALIZED                       (boolean)0x00
#define PORT_INITIALIZED                         (boolean)0x01

#define PORT_LSB_MASK                            (uint32)0x0000FFFFUL

#define PORT_SHIFT_16                            16U

/***********************************************************************************************************************
**                                      SchM Critical Section Protection Macros                                       **
***********************************************************************************************************************/
#if (PORT_CRITICAL_SECTION_PROTECTION == STD_ON)
#define PORT_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Port_##Exclusive_Area()                                  /* PRQA S 0342 # JV-01 */
#define PORT_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Port_##Exclusive_Area()                                   /* PRQA S 0342 # JV-01 */
#endif

/***********************************************************************************************************************
**                                              DEM Report Error Macros                                               **
***********************************************************************************************************************/
#if (PORT_AR_VERSION == PORT_AR_422_VERSION)
#define PORT_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_ReportErrorStatus(EventId, EventStatus)
#elif (PORT_AR_VERSION == PORT_AR_431_VERSION)
#define PORT_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
#elif (PORT_AR_VERSION == PORT_AR_R22_11_VERSION)
#define PORT_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
#endif

/***********************************************************************************************************************
**  Global symbols used for For verifying the Modes
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* Pin Configuration */
typedef struct STag_Port_Pin_Config                                                                                     /* PRQA S 3630 # JV-01 */
{
  /* Changeable / Not Changeable
   *  b0:Direction
   *  b1:DIO/ALT
   *  b2:Mode
   */
  uint16 usChangeable;
  /* Port Type
   *  0:JPORT
   *  1:PORT
   *  2:APORT
   */
  uint16 usPortType;
  /* Location of Port Info[0-...] */
  uint16 usPortLoc;
  /* Location of Bit
   *  Only 1bit is ON
   */
  uint16 usBitLoc;
  
  /*Store value for Available mode*/
  uint16 usModeAvailable;
  uint16 usModeDirIn;
  uint16 usModeDirOut;

  #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
  uint8 ucPortPinCoreIndex;
  #endif  /* #if (PORT_MULTI_CORE_SUPPORT == STD_ON) */

} Port_Pin_Config;

#if (PORT_DNFP03_AVAILABLE == STD_ON)
/* Digital Noise Filter Initial Value */
typedef struct STag_Port_DNF_Init                                                                                       /* PRQA S 3630 # JV-01 */
{
  uint8 ucDNFP01_CTL_Init[PORT_DNFP01_NUM][PORT_DNFP01_CH_NUM];
  uint8 ucDNFP02_CTL_Init[PORT_DNFP02_NUM];
  uint8 ucDNFP03_CTL_Init[PORT_DNFP03_NUM];
  uint16 usDNFP02_EDC_Init[PORT_DNFP02_NUM][PORT_DNFP02_CH_NUM];
  uint16 usDNFP03_EDC_Init[PORT_DNFP03_NUM][PORT_DNFP03_CH_NUM];
  uint8 ucDNFP02_CTL_Init2;
  uint16 usDNFP02_EDC_Init2[PORT_DNFP02_CH_NUM];                                                                        /* PRQA S 1039 # JV-01 */
} Port_DNF_Init;
#else
/* Digital Noise Filter Initial Value */
typedef struct STag_Port_DNF_Init                                                                                       /* PRQA S 3630 # JV-01 */
{
  uint8 ucDNFP01_CTL_Init[PORT_DNFP01_NUM][PORT_DNFP01_CH_NUM];
  uint8 ucDNFP02_CTL_Init[PORT_DNFP02_NUM];
  uint16 usDNFP02_EDC_Init[PORT_DNFP02_NUM][PORT_DNFP02_CH_NUM];
  uint8 ucDNFP02_CTL_Init2;
  uint16 usDNFP02_EDC_Init2[PORT_DNFP02_CH_NUM];                                                                        /* PRQA S 1039 # JV-01 */
} Port_DNF_Init;
#endif /* (PORT_DNFP03_AVAILABLE == STD_ON)  */
/* Port Register Initial Value */
typedef struct STag_Port_Reg_Init                                                                                       /* PRQA S 3630 # JV-01 */
{
  uint16 usPortRegInit[PORT_REG_SET_NUM + PORT_REG_SFS_NUM];
} Port_Reg_Init;

#endif /* PORT_PBTYPES_H  */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
