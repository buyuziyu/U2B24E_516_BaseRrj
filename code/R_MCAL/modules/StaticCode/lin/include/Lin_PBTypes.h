/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Lin_PBTypes.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 *
 * 2.4.1:  30/06/2025  : Remove the SW-VERSION from header of file
 *                       Remove QAC 4641
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release 
 *                       Add new QAC message 4641
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : As part of QAC 9.5.0 support, following changes are made:
 *                       1. Update SW-VERSION to 2.1.2
 *                       2. Fix QAC findings
 *                     : Remove redundant QAC message
 * 2.0.1:  20/10/2023  : Add new QAC message 1534 and 1536
 *         11/10/2023  : Update AR version "LIN_AR_R21_11_VERSION" to "LIN_AR_R22_11_VERSION"
 *                       Update "LIN_START/STOP_SEC_CONFIG_DATA_UNSPECIFIED" to
 *                       "LIN_START/STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED"
 * 2.0.0:  26/07/2023  : Add information about CWE violation ID
 *         18/07/2023  : Update to support for multicore:
 *                       Add new include "Os" section to support for multicore
 *                       Remove parameter "ucPropertiesIndex" in struct "Lin_ChannelInfo",
 *                       Lin_GaaChannelRamData[] in Global Data Section
 *                       Add new parameter "ucChannelRamIndex" in stuct "Lin_ChannelInfo"
 *                       Add new struct Lin_GlobalAccessPointType to support for multicore in Global Data Type
 *         25/05/2023  : Change name of AR version LIN_AR_2111_VERSION to LIN_AR_R21_11_VERSION
 *         28/04/2023  : Add new parameter ucBaudRate1 in Lin3_ChannelConfigType
 *         20/04/2023  : Add pre-compile LIN_SLAVE_MODE_SUPPORT for enNodeType, Lin_NodeType
 * 1.5.0:  05/04/2023  : Add data types for support AR21-11: Lin_NodeType, blHeaderComplete, enNodeType
 * 1.4.3:  17/05/2022  : Add preprocessor for LIN_INTERRUPT_MUX_SUPPORT
 *         20/04/2022  : Change from ucLin3IntMuxNumer to ucLin3IntMuxNumber
 *         14/04/2022  : Update SW-VERSION to 1.4.3
 * 1.4.2:  04/03/2022  : Update SW-VERSION
 * 1.4.1:  11/11/2021  : Update struct Lin3_ChannelConfigType, add pLin3IntMuxAddress and ucLin3IntMuxNumer
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 * 1.2.0:  26/08/2020  : Release.
 * 1.1.0:  19/06/2020  : Release.
 * 1.0.1:  16/04/2020  : Modified #include heading files.
 *         19/03/2019  : Fix QAC
 *                         1. Update "MISRA C Rule Violations" and "QAC warning"
 *                            message from MISRA-C:2004 to MISRA-C:2012.
 *                         2. Move static function prototypes from header file
 *                            to source file.
 * 1.0.0:  12/03/2019  : Initial Version.
 *
 */
/**********************************************************************************************************************/

#ifndef LIN_PBTYPES_H
#define LIN_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for declarations of EcuM APIs */
#if (LIN_WAKEUP_SUPPORT == STD_ON)
#include "EcuM.h"
#endif

/**
 * include os
*/
#if (LIN_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
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
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define LIN_PBTYPES_AR_RELEASE_MAJOR_VERSION    LIN_TYPES_AR_RELEASE_MAJOR_VERSION
#define LIN_PBTYPES_AR_RELEASE_MINOR_VERSION    LIN_TYPES_AR_RELEASE_MINOR_VERSION
#define LIN_PBTYPES_AR_RELEASE_REVISION_VERSION LIN_TYPES_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define LIN_PBTYPES_SW_MAJOR_VERSION            LIN_TYPES_SW_MAJOR_VERSION
#define LIN_PBTYPES_SW_MINOR_VERSION            LIN_TYPES_SW_MINOR_VERSION

#if (LIN_DEV_ERROR_DETECT == STD_ON)
#define LIN_DBTOC_VALUE                                                          \
  (((uint32)LIN_VENDOR_ID_VALUE << 22U) | ((uint32)LIN_MODULE_ID_VALUE << 14U) | \
   ((uint32)LIN_SW_MAJOR_VERSION_VALUE << 8U) | ((uint32)LIN_SW_MINOR_VERSION_VALUE << 3U))
#endif /* #if (LIN_DEV_ERROR_DETECT == STD_ON) */

#if (LIN_CRITICAL_SECTION_PROTECTION == STD_ON)
#define LIN_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Lin_##Exclusive_Area()                                    /* PRQA S 0342 # JV-01 */

#define LIN_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Lin_##Exclusive_Area()                                     /* PRQA S 0342 # JV-01 */
#else
#define LIN_ENTER_CRITICAL_SECTION(Exclusive_Area)
#define LIN_EXIT_CRITICAL_SECTION(Exclusive_Area)
#endif /* #if (LIN_CRITICAL_SECTION_PROTECTION == STD_ON) */

/***********************************************************************************************************************
**                                              DEM Report Error Macros                                               **
***********************************************************************************************************************/
#if (LIN_AR_VERSION == LIN_AR_422_VERSION)
#define LIN_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_ReportErrorStatus(EventId, EventStatus)
#elif ((LIN_AR_VERSION == LIN_AR_431_VERSION) || (LIN_AR_VERSION == LIN_AR_R22_11_VERSION))
#define LIN_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
#endif

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
#define LIN_REG_RESERVED_SIZE_3BYTES (uint8)0x03
#define LIN_REG_RESERVED_SIZE_8BYTES (uint8)0x08
#define LIN_FRAMEDATA_SIZE           (uint8)0x08
#if (LIN_INTERRUPT_MUX_SUPPORT == STD_ON)
#define LIN_INTSEL_MUX_MASK          (uint8)0x1F
#endif /* #if (LIN_INTERRUPT_MUX_SUPPORT == STD_ON) */

/* [AR22-11] Lin channel node Type */
#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
typedef enum ETag_Lin_NodeType
{
  LIN_MASTER_NODE      = 0x00,
  LIN_SLAVE_NODE       = 0x01
} Lin_NodeType;
#endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */

/* Structure for LIN Channel RAM data */
typedef struct STag_Lin_RamData                                                                                         /* PRQA S 3630 # JV-01 */
{
  Lin_FrameResponseType enFrameType;
  /* To hold 8 byte frame data + 1 byte checksum */
  uint8 aaFrameData[LIN_FRAMEDATA_SIZE];
  Lin_FramePidType ucFrameId;
  Lin_FrameDlType ucFrameLength;
  Lin_FrameCsModelType enCheckSumModel;
  Lin_StatusType enChannelStatus;
  uint8 ucSlpRqst_RespRdy;
  boolean blWakeupCalled;
  boolean blSleepPending;
  #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
  boolean blHeaderComplete;
  #endif
} Lin_RamData;

/* Structure for RLIN3 hardware Channel registers */
typedef struct STag_RLin3_UartRegs                                                                                      /* PRQA S 3630 # JV-01 */
{
  uint8 volatile ucRLN3nLWBR;
  uint8 volatile ucRLN3nLBRP0;
  uint8 volatile ucRLN3nLBRP1;
  uint8 volatile ucRLN3nLSTC;
  uint8 volatile ucReserved1[LIN_REG_RESERVED_SIZE_3BYTES];
  uint8 volatile ucRLN3nLMD;
  uint8 volatile ucRLN3nLBFC;
  uint8 volatile ucRLN3nLSC;
  uint8 volatile ucRLN3nLWUP;
  uint8 volatile ucRLN3nLIE;
  uint8 volatile ucRLN3nLEDE;
  uint8 volatile ucRLN3nLCUC;
  uint8 volatile ucReserved2;
  uint8 volatile ucRLN3nLTRC;
  uint8 volatile ucRLN3nLMST;
  uint8 volatile ucRLN3nLST;
  uint8 volatile ucRLN3nLEST;
  uint8 volatile ucRLN3nLDFC;
  uint8 volatile ucRLN3nLIDB;
  uint8 volatile ucRLN3nLCBR;
  uint8 volatile ucReserved3;
  uint8 volatile ucRLN3nLDBR[LIN_REG_RESERVED_SIZE_8BYTES];
} RLin3_UartRegs;

/* Structure for RLIN3 Channel information */
typedef struct STag_Lin3_ChannelConfigType
{
  volatile P2VAR(RLin3_UartRegs, TYPEDEF, REGSPACE) pLn3ChanlBaseAddress;                                               /* PRQA S 3432 # JV-01 */
  uint8 ucBaudRate;
  #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
  uint8 ucBaudRate1;
  #endif /* (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
  uint8 ucPrescalerClk_Select;
  uint8 ucBitSamples;
  boolean blLinSpec_Select;
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pLin3IntTxEicReg;                                                           /* PRQA S 3432 # JV-01 */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pLin3IntRxEicReg;                                                           /* PRQA S 3432 # JV-01 */
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pLin3IntStEicReg;                                                           /* PRQA S 3432 # JV-01 */
  #if (LIN_INTERRUPT_MUX_SUPPORT == STD_ON)
  volatile P2VAR(uint16, TYPEDEF, REGSPACE) pLin3IntMuxAddress;                                                         /* PRQA S 3432 # JV-01 */
  uint8 ucLin3IntMuxNumber;
  uint8 ucLin3IntMuxValue;
  #endif
} Lin3_ChannelConfigType;

typedef struct STag_Lin_ChannelInfo
{
  #if (LIN_WAKEUP_SUPPORT == STD_ON)
  uint8 ucWakeupSourceId;
  #endif
  uint8 ucModReg;

  #if (LIN_WAKEUP_SUPPORT == STD_ON)
  boolean blWakeupSupport;
  #endif

  /* Break Field Config Value */
  uint8 ucRLINBreakfieldwidth;
  /* Inter-Byte Space Config Value */
  uint8 ucRLINInterbytespace;

  #if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
  /* [AR22-11] Lin channel node type value */
  Lin_NodeType enNodeType;
  #endif

  /* Multi core support */
  #if (LIN_MULTI_CORE_SUPPORT == STD_ON)
  /* Index to access the RamData respectively */
  uint8 ucChannelRamIndex;
  #endif
} Lin_ChannelInfo;

/* Global data for using across core */
typedef struct STag_Lin_GlobalAccessPointType
{
  /* Driver Status for each core */
  volatile boolean *pDriverState;
  /* Global pointer to hold first channel data structure */
  volatile P2CONST(Lin_ChannelInfo *, TYPEDEF, LIN_APPL_CONST)  pChannelConfig;
  /* Global pointer to hold first RLin3 channel data structure address */
  volatile P2CONST(Lin3_ChannelConfigType *, TYPEDEF, LIN_APPL_CONST)  pRLIN3Properties;
  /* Global pointer to hold first channel RAM structure */
  volatile P2VAR(Lin_RamData, TYPEDEF, LIN_APPL_DATA)  pChannelRamData;                                                 /* PRQA S 3432 # JV-01 */
} Lin_GlobalAccessPointType;

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#define LIN_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Lin_MemMap.h"

/* This array contains RLIN3 channel specific information for all active channels */
extern CONST(Lin3_ChannelConfigType, LIN_APPL_CONST) Lin_GaaRLIN3Properties[];                                          /* PRQA S 3684 # JV-01 */

/* This array contains channel specific information for all active channels */
extern CONST(Lin_ChannelInfo, LIN_APPL_CONST) Lin_GaaChannelConfig[];                                                   /* PRQA S 3684 # JV-01 */

#define LIN_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Lin_MemMap.h"
/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* LIN_PBTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
