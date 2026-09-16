/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Fr_59_Renesas_Types.h                                                                               */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of Database declaration.                                                                                 */
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
 * 2.4.1:  30/06/2025   : Remove SW-VERSION in file header
 * 2.4.0:  30/06/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.01.00(D) Final Release
 * 2.3.2:  29/04/2025   : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025   : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 *                        As part of QAC 11.6.0 support, following changes are made: 
 *                        1. Remove QAC comments of message 0778
 * 2.3.0:  28/02/2025   : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.1:  31/12/2024   : Update SW-VERSION for Ver22.00.01 U2Ax Release
 * 2.2.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.3:  31/10/2024   : Update SW-VERSION to 2.1.3
 * 2.1.2:  20/08/2024   : As part of R22-11 support, following changes are made:
 *                        Remove preprocessor FR_59_RENESAS_AR_431_VERSION
 * 2.1.1:  01/06/2024   : As part of multicore support, following changes are made:
 *                        Add FR_59_RENESAS_INVALID_CORE to support multicore
 *                      : As part of QAC 10.3.0 support, following changes are made:
 *                        1. Remove redundant QAC message: 1534, 1536
 *                        2. Remove redundant QAC message: 0791, 0779
 * 2.1.0:  24/02/2024   : Change SW-VERSION to 2.1.0
 * 2.0.1:  27/09/2023   : Change FR_59_RENESAS_AR_R21_11_VERSION with FR_59_RENESAS_AR_R22_11_VERSION to support AR22-11
 *                        Add QAC message: 1534, 1536
 * 2.0.0:  30/07/2023   : Add CWE rule into QAC header (0778, 0779 message)
 *                      : Change FR_59_RENESAS_AR_2111_VERSION to FR_59_RENESAS_AR_R21_11_VERSION
 *                        Improve Cyclomatic Complexity (STCYC<=20):
 *                        + Add number mask values
 *                        + Add new structures Fr_59_Renesas_UpdateCCConfig, Fr_59_Renesas_CheckPOCSts
 *                        + Add Types of AUTOSAR FlexRay modules (Fr, FrIf and FrTrcv)
 *         24/04/2023   : Add macro FR_59_RENESAS_CYCLE_MASK, FR_59_RENESAS_CHANNEL_MASK for support AR2111
 *         06/04/2023   : Due to reduce STCYC <=20
 *                        Add new structure:  Fr_Renesas_ReadDataFromCC
 *                        Update SW-VERSION to 2.0.0
 * 1.4.4:  13/06/2022   : Remove macros FR_59_RENESAS_FLX0IBCM, FR_59_RENESAS_FLX0IBCR, FR_59_RENESAS_FLX0SWNIT_FLX0MTSB
 * 1.4.3:  09/05/2022   : Change SW-VERSION to 1.4.3
 *                        Remove unused macro
 * 1.3.3:  02/03/2022   : Change SW-VERSION to 1.4.2
 * 1.3.2:  13/08/2021   : Change SW-VERSION to 1.3.2
 * 1.3.1:  02/07/2021   : Add QAC message 9.5.0.
 *                        Format source code to 120 characters.
 *                        Improve Violation tag (remove START/END).
 *         04/05/2021   : + Added QAC message 0779.
 *                        + Update name of macro FR_59_RENESAS_FLX0TXC_CYC_SHIFT (from FR_59_RENESAS_FLX0TxC_CYC_SHIFT)
 *                        and FR_59_RENESAS_FLX0TXC_OFFSET_SHIFT (from FR_59_RENESAS_FLX0TxC_OFFSET_SHIFT)
 *                        to follow coding guideline Name_Macro_001.
 *                        + Update to correct name of enumeration type Fr_59_Renesas_TimerSelectionType and
 *                        Fr_59_Renesas_TimerModeSelectType and their elements to follow SWS Autosar Requirement
 *                        SWS_BSW_00124.
 *                        + Update name for the following self defined structure type to follow naming convention
 *                        in coding guideline Name_Type_002.
 *                        Fr_59_Renesas_OperationRegType (from FR_OperationReg)
 *                        Fr_59_Renesas_InterruptRegType (from FR_InterruptReg)
 *                        Fr_59_Renesas_TimerRegType (from FR_TimerReg)
 *                        Fr_59_Renesas_CCControlRegType (from FR_CCControlReg)
 *                        Fr_59_Renesas_CCStatusRegType (from FR_CCStatusReg)
 *                        Fr_59_Renesas_MessageBufferControlRegType (from FR_MessageBufferControlReg)
 *                        Fr_59_Renesas_MessageBufferStatusRegType (from FR_MessageBufferStatusReg)
 *                        Fr_59_Renesas_InputBufferRegType (from FR_InputBufferReg)
 *                        Fr_59_Renesas_OutputBufferRegType (from FR_OutputBufferReg)
 *                        Fr_59_Renesas_DataTransferControlRegType (from FR_DataTransferControlReg)
 *                        Fr_59_Renesas_DataTransferStatusRegType (from FR_DataTransferStatusReg)
 *                        Fr_59_Renesas_InputConstdataType (from Fr_59_Renesas_InputConstdata)
 *                        Fr_59_Renesas_OutputConstdataType (from Fr_59_Renesas_OutputConstdata)
 *         29/04/2021   : + Update defined value for macro FR_59_RENESAS_FLX0FRAES_RESET from 0x00000FFFUL
 *                        to 0x00000F00UL to fix issue write to read-only bits EIDX[7:0] of register FLXAnFRAES with
 *                        value different from value after reset (internal function Fr_59_Renesas_UpdateInputPtrTable).
 *                        + Update define value of FR_59_RENESAS_FLX0FRAES_RESET to upper case to follow
 *                        coding guideline Rules_Const_001.
 * 1.3.0:  17/11/2020   : Add definition of Fr_TimerSelectionType, Fr_TimerModeSelectType
 *                        Remove redundant QAC comment for message 0791.
 * 1.2.0:  26/08/2020   : Release.
 * 1.1.0:  19/06/2020   : Release.
 *         28/07/2020   : Add QAC 9.3.1 comment.
 * 1.0.3:  24/05/2020   : Add MISRA C Rule Violation (2:3453).
 *         06/05/2020   : Add definition of FR_59_RENESAS_MAX_MB_NUMBER.
 *         04/05/2020   : Add definition of FR_59_RENESAS_MAX_FRAMEID.
 * 1.0.2:  17/04/2020   : Update the header files including.
 *         15/04/2020   : Add definition of Channel value : CH[1:0] bits in FRWRHS1.
 * 1.0.1:  20/03/2020   : + Remove FR_59_RENESAS_FLX0TXRQ1, FR_59_RENESAS_FLX0TXRQ2,
 *                           FR_59_RENESAS_FLX0TXRQ3, FR_59_RENESAS_FLX0TXRQ4, FR_59_RENESAS_TXRQ_REG_OFFSET
 *                           FR_59_RENESAS_FLX0NDAT1, FR_59_RENESAS_FLX0NDAT2, FR_59_RENESAS_FLX0NDAT3,
 *                           FR_59_RENESAS_FLX0NDAT4, FR_59_RENESAS_NDAT_REG_OFFSET.
 *                           + Add FR_59_RENESAS_REGNUMBER_OFFSET, FR_59_RENESAS_BITNUMBER_MASK,
 *                           FR_59_RENESAS_FLX0FRMBS_TCIB_MASK, FR_59_RENESAS_FLX0FRMBS_TCIA_MASK
 *         14/01/2020    : Add FR_59_RENESAS_AR_422_VERSION and
 *                           FR_59_RENESAS_AR_431_VERSION to define AUTOSAR
 *                           version number.
 * 1.0.0:  11/12/2019    : Initial Version.
 */
/**********************************************************************************************************************/
#ifndef FR_59_RENESAS_TYPES_H
#define FR_59_RENESAS_TYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Include standard AUTOSAR Types */
#include "Std_Types.h"
/* Types of AUTOSAR FlexRay modules (Fr, FrIf and FrTrcv) */
#include "Fr_GeneralTypes.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define FR_59_RENESAS_TYPES_AR_RELEASE_MAJOR_VERSION       FR_59_RENESAS_AR_RELEASE_MAJOR_VERSION
#define FR_59_RENESAS_TYPES_AR_RELEASE_MINOR_VERSION       FR_59_RENESAS_AR_RELEASE_MINOR_VERSION
#define FR_59_RENESAS_TYPES_AR_RELEASE_REVISION_VERSION    FR_59_RENESAS_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FR_59_RENESAS_TYPES_SW_MAJOR_VERSION               FR_59_RENESAS_SW_MAJOR_VERSION
#define FR_59_RENESAS_TYPES_SW_MINOR_VERSION               FR_59_RENESAS_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0778)    : Identifier matches other identifier(s) (e.g. '%s') in first 31 characters - program does     */
/*                       not conform strictly to ISO:C90.                                                             */
/* Rule                : CERTCCM DCL23, DCL40, MISRA C:2012 Dir-1.1, CWE Rule CWE-736                                 */
/* JV-01 Justification : Compiler will distinguish numerous characters, so this is accepted.                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/


/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    QAC Warning                                                     **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                               AUTOSAR Version number                                               **
***********************************************************************************************************************/
#define FR_59_RENESAS_AR_422_VERSION                        422
#define FR_59_RENESAS_AR_R22_11_VERSION                     480
/***********************************************************************************************************************
**                                              Interrupt Registers Mask                                              **
***********************************************************************************************************************/
#define FR_59_RENESAS_FLX0FRAES_ERR_MASK                   0x00000900UL

/***********************************************************************************************************************
**                                                CC Status Registers                                                 **
***********************************************************************************************************************/
/* Even Sync ID [1] */
#define FR_59_RENESAS_FLX0ESID1                            0x00000130UL
#define FR_59_RENESAS_FLX0ESID2                            0x00000134UL
#define FR_59_RENESAS_FLX0ESID3                            0x00000138UL
#define FR_59_RENESAS_FLX0ESID4                            0x0000013CUL
#define FR_59_RENESAS_FLX0ESID5                            0x00000140UL
#define FR_59_RENESAS_FLX0ESID6                            0x00000144UL
#define FR_59_RENESAS_FLX0ESID7                            0x00000148UL
#define FR_59_RENESAS_FLX0ESID8                            0x0000014CUL
#define FR_59_RENESAS_FLX0ESID9                            0x00000150UL
#define FR_59_RENESAS_FLX0ESID10                           0x00000154UL
#define FR_59_RENESAS_FLX0ESID11                           0x00000158UL
#define FR_59_RENESAS_FLX0ESID12                           0x0000015CUL
#define FR_59_RENESAS_FLX0ESID13                           0x00000160UL
#define FR_59_RENESAS_FLX0ESID14                           0x00000164UL
#define FR_59_RENESAS_FLX0ESID15                           0x00000168UL
/* Odd Sync ID [1] */
#define FR_59_RENESAS_FLX0OSID1                            0x00000170UL
#define FR_59_RENESAS_FLX0OSID2                            0x00000174UL
#define FR_59_RENESAS_FLX0OSID3                            0x00000178UL
#define FR_59_RENESAS_FLX0OSID4                            0x0000017CUL
#define FR_59_RENESAS_FLX0OSID5                            0x00000180UL
#define FR_59_RENESAS_FLX0OSID6                            0x00000184UL
#define FR_59_RENESAS_FLX0OSID7                            0x00000188UL
#define FR_59_RENESAS_FLX0OSID8                            0x0000018CUL
#define FR_59_RENESAS_FLX0OSID9                            0x00000190UL
#define FR_59_RENESAS_FLX0OSID10                           0x00000194UL
#define FR_59_RENESAS_FLX0OSID11                           0x00000198UL
#define FR_59_RENESAS_FLX0OSID12                           0x0000019CUL
#define FR_59_RENESAS_FLX0OSID13                           0x000001A0UL
#define FR_59_RENESAS_FLX0OSID14                           0x000001A4UL
#define FR_59_RENESAS_FLX0OSID15                           0x000001A8UL

/***********************************************************************************************************************
**                                          Message Buffer Status Registers                                           **
***********************************************************************************************************************/
/* Calculate the corresponding register number for Message Buffer ID */
#define FR_59_RENESAS_REGNUMBER_OFFSET(MSGNUM)             (uint8)((uint32)(MSGNUM) >> 5U)
/* Calculate the corresponding bit mask for Message buffer ID */
#define FR_59_RENESAS_BITNUMBER_MASK(MSGNUM)               ((uint32)1U << (((uint32)(MSGNUM) & (uint32)31U)))           /* PRQA S 3472 # JV-01 */
/* Bit mask for FLXAnFRMBS.TCIB */
#define FR_59_RENESAS_FLX0FRMBS_TCIB_MASK                  0x00000200UL
/* Bit mask for FLXAnFRMBS.TCIA */
#define FR_59_RENESAS_FLX0FRMBS_TCIA_MASK                  0x00000100UL
/***********************************************************************************************************************
**                                                    Input Buffer                                                    **
***********************************************************************************************************************/
/* Write Data Section [1] */
#define FR_59_RENESAS_FLX0WRDS1                            0x00000400UL
#define FR_59_RENESAS_FLX0WRDS2                            0x00000404UL
#define FR_59_RENESAS_FLX0WRDS3                            0x00000408UL
#define FR_59_RENESAS_FLX0WRDS4                            0x0000040CUL
#define FR_59_RENESAS_FLX0WRDS5                            0x00000410UL
#define FR_59_RENESAS_FLX0WRDS6                            0x00000414UL
#define FR_59_RENESAS_FLX0WRDS7                            0x00000418UL
#define FR_59_RENESAS_FLX0WRDS8                            0x0000041CUL
#define FR_59_RENESAS_FLX0WRDS9                            0x00000420UL
#define FR_59_RENESAS_FLX0WRDS10                           0x00000424UL
#define FR_59_RENESAS_FLX0WRDS11                           0x00000428UL
#define FR_59_RENESAS_FLX0WRDS12                           0x0000042CUL
#define FR_59_RENESAS_FLX0WRDS13                           0x00000430UL
#define FR_59_RENESAS_FLX0WRDS14                           0x00000434UL
#define FR_59_RENESAS_FLX0WRDS15                           0x00000438UL
#define FR_59_RENESAS_FLX0WRDS16                           0x0000043CUL
#define FR_59_RENESAS_FLX0WRDS17                           0x00000440UL
#define FR_59_RENESAS_FLX0WRDS18                           0x00000444UL
#define FR_59_RENESAS_FLX0WRDS19                           0x00000448UL
#define FR_59_RENESAS_FLX0WRDS20                           0x0000044CUL
#define FR_59_RENESAS_FLX0WRDS21                           0x00000450UL
#define FR_59_RENESAS_FLX0WRDS22                           0x00000454UL
#define FR_59_RENESAS_FLX0WRDS23                           0x00000458UL
#define FR_59_RENESAS_FLX0WRDS24                           0x0000045CUL
#define FR_59_RENESAS_FLX0WRDS25                           0x00000460UL
#define FR_59_RENESAS_FLX0WRDS26                           0x00000464UL
#define FR_59_RENESAS_FLX0WRDS27                           0x00000468UL
#define FR_59_RENESAS_FLX0WRDS28                           0x0000046CUL
#define FR_59_RENESAS_FLX0WRDS29                           0x00000470UL
#define FR_59_RENESAS_FLX0WRDS30                           0x00000474UL
#define FR_59_RENESAS_FLX0WRDS31                           0x00000478UL
#define FR_59_RENESAS_FLX0WRDS32                           0x0000047CUL
#define FR_59_RENESAS_FLX0WRDS33                           0x00000480UL
#define FR_59_RENESAS_FLX0WRDS34                           0x00000484UL
#define FR_59_RENESAS_FLX0WRDS35                           0x00000488UL
#define FR_59_RENESAS_FLX0WRDS36                           0x0000048CUL
#define FR_59_RENESAS_FLX0WRDS37                           0x00000490UL
#define FR_59_RENESAS_FLX0WRDS38                           0x00000494UL
#define FR_59_RENESAS_FLX0WRDS39                           0x00000498UL
#define FR_59_RENESAS_FLX0WRDS40                           0x0000049CUL
#define FR_59_RENESAS_FLX0WRDS41                           0x000004A0UL
#define FR_59_RENESAS_FLX0WRDS42                           0x000004A4UL
#define FR_59_RENESAS_FLX0WRDS43                           0x000004A8UL
#define FR_59_RENESAS_FLX0WRDS44                           0x000004ACUL
#define FR_59_RENESAS_FLX0WRDS45                           0x000004B0UL
#define FR_59_RENESAS_FLX0WRDS46                           0x000004B4UL
#define FR_59_RENESAS_FLX0WRDS47                           0x000004B8UL
#define FR_59_RENESAS_FLX0WRDS48                           0x000004BCUL
#define FR_59_RENESAS_FLX0WRDS49                           0x000004C0UL
#define FR_59_RENESAS_FLX0WRDS50                           0x000004C4UL
#define FR_59_RENESAS_FLX0WRDS51                           0x000004C8UL
#define FR_59_RENESAS_FLX0WRDS52                           0x000004CCUL
#define FR_59_RENESAS_FLX0WRDS53                           0x000004D0UL
#define FR_59_RENESAS_FLX0WRDS54                           0x000004D4UL
#define FR_59_RENESAS_FLX0WRDS55                           0x000004D8UL
#define FR_59_RENESAS_FLX0WRDS56                           0x000004DCUL
#define FR_59_RENESAS_FLX0WRDS57                           0x000004E0UL
#define FR_59_RENESAS_FLX0WRDS58                           0x000004E4UL
#define FR_59_RENESAS_FLX0WRDS59                           0x000004E8UL
#define FR_59_RENESAS_FLX0WRDS60                           0x000004ECUL
#define FR_59_RENESAS_FLX0WRDS61                           0x000004F0UL
#define FR_59_RENESAS_FLX0WRDS62                           0x000004F4UL
#define FR_59_RENESAS_FLX0WRDS63                           0x000004F8UL
#define FR_59_RENESAS_FLX0WRDS64                           0x000004FCUL
/* Write Header Section 1 */
#define FR_59_RENESAS_FLX0WRHS1                            0x00000500UL
/* Write Header Section 2 */
#define FR_59_RENESAS_FLX0WRHS2                            0x00000504UL
/* Write Header Section 3 */
#define FR_59_RENESAS_FLX0WRHS3                            0x00000508UL

/***********************************************************************************************************************
**                                                   Output Buffer                                                    **
***********************************************************************************************************************/
/* Read Data Section [1] */
#define FR_59_RENESAS_FLX0RDDS1                            0x00000600UL
#define FR_59_RENESAS_FLX0RDDS2                            0x00000604UL
#define FR_59_RENESAS_FLX0RDDS3                            0x00000608UL
#define FR_59_RENESAS_FLX0RDDS4                            0x0000060CUL
#define FR_59_RENESAS_FLX0RDDS5                            0x00000610UL
#define FR_59_RENESAS_FLX0RDDS6                            0x00000614UL
#define FR_59_RENESAS_FLX0RDDS7                            0x00000618UL
#define FR_59_RENESAS_FLX0RDDS8                            0x0000061CUL
#define FR_59_RENESAS_FLX0RDDS9                            0x00000620UL
#define FR_59_RENESAS_FLX0RDDS10                           0x00000624UL
#define FR_59_RENESAS_FLX0RDDS11                           0x00000628UL
#define FR_59_RENESAS_FLX0RDDS12                           0x0000062CUL
#define FR_59_RENESAS_FLX0RDDS13                           0x00000630UL
#define FR_59_RENESAS_FLX0RDDS14                           0x00000634UL
#define FR_59_RENESAS_FLX0RDDS15                           0x00000638UL
#define FR_59_RENESAS_FLX0RDDS16                           0x0000063CUL
#define FR_59_RENESAS_FLX0RDDS17                           0x00000640UL
#define FR_59_RENESAS_FLX0RDDS18                           0x00000644UL
#define FR_59_RENESAS_FLX0RDDS19                           0x00000648UL
#define FR_59_RENESAS_FLX0RDDS20                           0x0000064CUL
#define FR_59_RENESAS_FLX0RDDS21                           0x00000650UL
#define FR_59_RENESAS_FLX0RDDS22                           0x00000654UL
#define FR_59_RENESAS_FLX0RDDS23                           0x00000658UL
#define FR_59_RENESAS_FLX0RDDS24                           0x0000065CUL
#define FR_59_RENESAS_FLX0RDDS25                           0x00000660UL
#define FR_59_RENESAS_FLX0RDDS26                           0x00000664UL
#define FR_59_RENESAS_FLX0RDDS27                           0x00000668UL
#define FR_59_RENESAS_FLX0RDDS28                           0x0000066CUL
#define FR_59_RENESAS_FLX0RDDS29                           0x00000670UL
#define FR_59_RENESAS_FLX0RDDS30                           0x00000674UL
#define FR_59_RENESAS_FLX0RDDS31                           0x00000678UL
#define FR_59_RENESAS_FLX0RDDS32                           0x0000067CUL
#define FR_59_RENESAS_FLX0RDDS33                           0x00000680UL
#define FR_59_RENESAS_FLX0RDDS34                           0x00000684UL
#define FR_59_RENESAS_FLX0RDDS35                           0x00000688UL
#define FR_59_RENESAS_FLX0RDDS36                           0x0000068CUL
#define FR_59_RENESAS_FLX0RDDS37                           0x00000690UL
#define FR_59_RENESAS_FLX0RDDS38                           0x00000694UL
#define FR_59_RENESAS_FLX0RDDS39                           0x00000698UL
#define FR_59_RENESAS_FLX0RDDS40                           0x0000069CUL
#define FR_59_RENESAS_FLX0RDDS41                           0x000006A0UL
#define FR_59_RENESAS_FLX0RDDS42                           0x000006A4UL
#define FR_59_RENESAS_FLX0RDDS43                           0x000006A8UL
#define FR_59_RENESAS_FLX0RDDS44                           0x000006ACUL
#define FR_59_RENESAS_FLX0RDDS45                           0x000006B0UL
#define FR_59_RENESAS_FLX0RDDS46                           0x000006B4UL
#define FR_59_RENESAS_FLX0RDDS47                           0x000006B8UL
#define FR_59_RENESAS_FLX0RDDS48                           0x000006BCUL
#define FR_59_RENESAS_FLX0RDDS49                           0x000006C0UL
#define FR_59_RENESAS_FLX0RDDS50                           0x000006C4UL
#define FR_59_RENESAS_FLX0RDDS51                           0x000006C8UL
#define FR_59_RENESAS_FLX0RDDS52                           0x000006CCUL
#define FR_59_RENESAS_FLX0RDDS53                           0x000006D0UL
#define FR_59_RENESAS_FLX0RDDS54                           0x000006D4UL
#define FR_59_RENESAS_FLX0RDDS55                           0x000006D8UL
#define FR_59_RENESAS_FLX0RDDS56                           0x000006DCUL
#define FR_59_RENESAS_FLX0RDDS57                           0x000006E0UL
#define FR_59_RENESAS_FLX0RDDS58                           0x000006E4UL
#define FR_59_RENESAS_FLX0RDDS59                           0x000006E8UL
#define FR_59_RENESAS_FLX0RDDS60                           0x000006ECUL
#define FR_59_RENESAS_FLX0RDDS61                           0x000006F0UL
#define FR_59_RENESAS_FLX0RDDS62                           0x000006F4UL
#define FR_59_RENESAS_FLX0RDDS63                           0x000006F8UL
#define FR_59_RENESAS_FLX0RDDS64                           0x000006FCUL

/***********************************************************************************************************************
**                                     FlexRay Communication Controller commands                                      **
***********************************************************************************************************************/
#define FR_59_RENESAS_CMD_NOT_ACCEPTED                     0UL  /* 0000 */
#define FR_59_RENESAS_CONFIG                               1UL  /* 0001 */
#define FR_59_RENESAS_READY                                2UL  /* 0010 */
#define FR_59_RENESAS_WAKEUP                               3UL  /* 0011 */
#define FR_59_RENESAS_RUN                                  4UL  /* 0100 */
#define FR_59_RENESAS_ALL_SLOTS                            5UL  /* 0101 */
#define FR_59_RENESAS_HALT                                 6UL  /* 0110 */
#define FR_59_RENESAS_FREEZE                               7UL  /* 0111 */
#define FR_59_RENESAS_ALLOW_COLDSTART                      9UL  /* 1001 */
#define FR_59_RENESAS_RESET_STATUS_INDICATORS              10UL /* 1010 */

/***********************************************************************************************************************
**                                 Protocol Operation Control Status : POCS of FRCCSV                                 **
***********************************************************************************************************************/
#define FR_59_RENESAS_DEFAULT_CONFIG_STATE                 0UL  /* 00 0000 */
#define FR_59_RENESAS_READY_STATE                          1UL  /* 00 0001 */
#define FR_59_RENESAS_NORMAL_ACTIVE_STATE                  2UL  /* 00 0010 */
#define FR_59_RENESAS_NORMAL_PASSIVE_STATE                 3UL  /* 00 0011 */
#define FR_59_RENESAS_HALT_STATE                           4UL  /* 00 0100 */
#define FR_59_RENESAS_CONFIG_STATE                         15UL /* 00 1111 */

#define FR_59_RENESAS_WAKEUP_STATE                         16UL /* 01 xxxx */
#define FR_59_RENESAS_STARTUP_STATE                        32UL /* 1x xxxx */

#define FR_59_RENESAS_WAKEUP_STANDBY_STATE                 16UL /* 01 0000 */
#define FR_59_RENESAS_WAKEUP_LISTEN_STATE                  17UL /* 01 0001 */
#define FR_59_RENESAS_WAKEUP_SEND_STATE                    18UL /* 01 0010 */
#define FR_59_RENESAS_WAKEUP_DETECT_STATE                  19UL /* 01 0011 */

#define FR_59_RENESAS_STARTUP_PREPARE_STATE                32UL /* 10 0000 */
#define FR_59_RENESAS_COLDSTART_LISTEN_STATE               33UL /* 10 0001 */
#define FR_59_RENESAS_COLDSTART_COLLISION_RESOLUTION_STATE 34UL /* 10 0010 */
#define FR_59_RENESAS_COLDSTART_CONSISTENCY_CHECK_STATE    35UL /* 10 0011 */
#define FR_59_RENESAS_COLDSTART_GAP_STATE                  36UL /* 10 0100 */
#define FR_59_RENESAS_COLDSTART_JOIN_STATE                 37UL /* 10 0101 */
#define FR_59_RENESAS_INTEGRATION_COLDSTART_CHECK_STATE    38UL /* 10 0110 */
#define FR_59_RENESAS_INTEGRATION_LISTEN_STATE             39UL /* 10 0111 */
#define FR_59_RENESAS_INTEGRATION_CONSISTENCY_CHECK_STATE  40UL /* 10 1000 */
#define FR_59_RENESAS_INITIALIZE_SCHEDULE_STATE            41UL /* 10 1001 */
#define FR_59_RENESAS_ABORT_STARTUP_STATE                  42UL /* 10 1010 */

/***********************************************************************************************************************
**                                           Wakeup Status : WSV of FRCCSV                                            **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                             Slot Mode : SLM of FRCCSV                                              **
***********************************************************************************************************************/
#define FR_59_RENESAS_SLM_SINGLE                           0U /* 00 */
#define FR_59_RENESAS_SLM_ALL_PENDING                      2U /* 10 */
#define FR_59_RENESAS_SLM_ALL                              3U /* 11 */

/***********************************************************************************************************************
**                                            Error Mode : ERRM of FRCCEV                                             **
***********************************************************************************************************************/
#define FR_59_RENESAS_ERRM_ACTIVE                          0U /* 00 */
#define FR_59_RENESAS_ERRM_PASSIVE                         1U /* 01 */
#define FR_59_RENESAS_ERRM_COMM_HALT                       2U /* 10 */

/***********************************************************************************************************************
**                                      Channel value : CH[1:0] bits in FRWRHS1                                       **
***********************************************************************************************************************/
#define FR_59_RENESAS_CHANNEL_A                            1U /*01*/
#define FR_59_RENESAS_CHANNEL_B                            2U /*10*/
#define FR_59_RENESAS_CHANNEL_AB                           3U /*11*/

/***********************************************************************************************************************
**                                               Register reset values                                                **
***********************************************************************************************************************/
/* Message RAM FFB bit mask*/
#define FR_59_RENESAS_FLX0MRC_FFB_MASK                     0x0000FF00UL
/* FROTS FGIDX Mask*/
#define FR_59_RENESAS_FLX0FROTS_FDA_RESET                  0x00002000UL
/***********************************************************************************************************************
**                                                   Input transfer                                                   **
***********************************************************************************************************************/
/* FROTS Register Mask */
#define FR_59_RENESAS_FLX0FROTS_FFL_MASK                   0x3F000000UL

/***********************************************************************************************************************
**                                                    Mask values                                                     **
***********************************************************************************************************************/

#define FR_59_RENESAS_DBTOC_VALUE                                      \
  (((uint32)FR_59_RENESAS_VENDOR_ID_VALUE << 22U) | ((uint32)FR_59_RENESAS_MODULE_ID_VALUE << 14U) | \
   ((uint32)FR_59_RENESAS_SW_MAJOR_VERSION_VALUE << 8U) | ((uint32)FR_59_RENESAS_SW_MINOR_VERSION_VALUE << 3U))

#define FR_59_RENESAS_TRUE                                     (boolean)0x01
#define FR_59_RENESAS_FALSE                                    (boolean)0x00
#define FR_59_RENESAS_ZERO                                     0x0U
#define FR_59_RENESAS_ONE                                      0x1U
#define FR_59_RENESAS_TWO                                      0x2U
#define FR_59_RENESAS_THREE                                    0x3U
#define FR_59_RENESAS_FOUR                                     0x4U
#define FR_59_RENESAS_FIVE                                     0x5U
#define FR_59_RENESAS_SIX                                      0x6U
#define FR_59_RENESAS_SEVEN                                    0x7U
#define FR_59_RENESAS_EIGHT                                    0x8U
#define FR_59_RENESAS_NINE                                     0x9U
#define FR_59_RENESAS_TEN                                      0xAU
#define FR_59_RENESAS_ELEVEN                                   0xBU
#define FR_59_RENESAS_TWELVE                                   0xCU
#define FR_59_RENESAS_THIRTEEN                                 0xDU
#define FR_59_RENESAS_FOURTEEN                                 0xEU
#define FR_59_RENESAS_FIFTEEN                                  0xFU
#define FR_59_RENESAS_SIXTEEN                                  0x10U
#define FR_59_RENESAS_SEVENTEEN                                0x11U
#define FR_59_RENESAS_EIGHTTEEN                                0x12U
#define FR_59_RENESAS_NINETEEN                                 0x13U
#define FR_59_RENESAS_TWENTY                                   0x14U
#define FR_59_RENESAS_TWENTYONE                                0x15U
#define FR_59_RENESAS_TWENTYTWO                                0x16U
#define FR_59_RENESAS_TWENTYTHREE                              0x17U
#define FR_59_RENESAS_TWENTYFOUR                               0x18U
#define FR_59_RENESAS_TWENTYFIVE                               0x19U
#define FR_59_RENESAS_TWENTYSIX                                0x1AU
#define FR_59_RENESAS_TWENTYSEVEN                              0x1BU
#define FR_59_RENESAS_TWENTYEIGHT                              0x1CU
#define FR_59_RENESAS_TWENTYNINE                               0x1DU
#define FR_59_RENESAS_THIRTY                                   0x1EU
#define FR_59_RENESAS_THIRTYONE                                0x1FU
#define FR_59_RENESAS_THIRTYTWO                                0x20U
#define FR_59_RENESAS_THIRTYTHREE                              0x21U
#define FR_59_RENESAS_THIRTYFOUR                               0x22U
#define FR_59_RENESAS_THIRTYFIVE                               0x23U
#define FR_59_RENESAS_THIRTYSIX                                0x24U
#define FR_59_RENESAS_THIRTYSEVEN                              0x25U
#define FR_59_RENESAS_THIRTYEIGHT                              0x26U
#define FR_59_RENESAS_THIRTYNINE                               0x27U
#define FR_59_RENESAS_FOURTY                                   0x28U
#define FR_59_RENESAS_FOURTYONE                                0x29U
#define FR_59_RENESAS_FOURTYTWO                                0x2AU
#define FR_59_RENESAS_FOURTYTHREE                              0x2BU
#define FR_59_RENESAS_FOURTYFOUR                               0x2CU
#define FR_59_RENESAS_FOURTYFIVE                               0x2DU
#define FR_59_RENESAS_FOURTYSIX                                0x2EU
#define FR_59_RENESAS_FOURTYSEVEN                              0x2FU
#define FR_59_RENESAS_FOURTYEIGHT                              0x30U
#define FR_59_RENESAS_FOURTYNINE                               0x31U
#define FR_59_RENESAS_FIFTY                                    0x32U
#define FR_59_RENESAS_FIFTYONE                                 0x33U
#define FR_59_RENESAS_FIFTYTWO                                 0x34U
#define FR_59_RENESAS_FIFTYTHREE                               0x35U
#define FR_59_RENESAS_FIFTYFOUR                                0x36U
#define FR_59_RENESAS_FIFTYFIVE                                0x37U
#define FR_59_RENESAS_FIFTYSIX                                 0x38U
#define FR_59_RENESAS_FIFTYSEVEN                               0x39U
#define FR_59_RENESAS_FIFTYEIGHT                               0x3AU
#define FR_59_RENESAS_FIFTYNINE                                0x3BU
#define FR_59_RENESAS_SIXTY                                    0x3CU
#define FR_59_RENESAS_SIXTYONE                                 0x3DU
#define FR_59_RENESAS_SIXTYTWO                                 0x3EU
#define FR_59_RENESAS_SIXTYTHREE                               0x3FU
#define FR_59_RENESAS_SIXTYFOUR                                0x40U
#define FR_59_RENESAS_EMPTY                                    0xFFU

#define FR_59_RENESAS_NANOSEC_CONVERSION                       1000000000.0F

#define FR_59_RENESAS_N1SAMPLES                                0U
#define FR_59_RENESAS_N2SAMPLES                                1U

#define FR_59_RENESAS_T12_5NS                                  0U
#define FR_59_RENESAS_T25NS                                    1U
#define FR_59_RENESAS_T50NS                                    2U
#define FR_59_RENESAS_T100NS                                   3U
#define FR_59_RENESAS_T200NS                                   4U
#define FR_59_RENESAS_T400NS                                   5U

/* Transmission Mode */
#define FR_59_RENESAS_TXM_SINGLESHOT                           1U

/* Message Buffer Direction Configuration */
#define FR_59_RENESAS_CFG_RECEIVE                              0U
#define FR_59_RENESAS_CFG_TRANSMIT                             1U

#define FR_59_RENESAS_MAX_CRC                                  2047U   
/* Maximum frame ID */
#define FR_59_RENESAS_MAX_FRAMEID                              2047U   

/* Maximum of Sync Frame List size */
#define FR_59_RENESAS_MAX_FRAMELIST_SIZE                       15U     

/* FLXnESID.FLXnRXEB[15], FLXnESID.FLXnRXEA[14] */
#define FR_59_RENESAS_FLX0ESID_FLX0RXEA_FLX0RXEB_MASK                        0x0000C000UL
/* FLXnESID.FLXnEIDm[9:0] */
#define FR_59_RENESAS_FLX0ESID_FLX0EID_MASK                                  0x000003FFUL
/* FLXnOSID.FLXnOIDm[9:0] */
#define FR_59_RENESAS_FLX0OSID_FLX0OID_MASK                                  0x000003FFUL

/* SIR.WUPA */
#define FR_59_RENESAS_FLX0SIR_FLX0WUPA_MASK                    0x00010000UL
/* SIR.WUPB */
#define FR_59_RENESAS_FLX0SIR_FLX0WUPB_MASK                    0x01000000UL
/* SIR.MTSA, SIR.MTSB */
#define FR_59_RENESAS_FLX0SIR_FLX0MTS_MASK                     0x02020000UL
/* SIR.WUPA, SIR.WUPB */
#define FR_59_RENESAS_FLX0SIR_FLX0WUP_RESET                    0x01010000UL

#define FR_59_RENESAS_FLX0CCSV_FLX0POCS_MASK                   0x0000003FUL /* POCS[5:0] */
#define FR_59_RENESAS_FLX0CCSV_FLX0WSV_MASK                    0x00070000UL /* WSV[2:0] */
#define FR_59_RENESAS_FLX0CCSV_FLX0SLM_MASK                    0x00000300UL /* SLM[1:0] */
#define FR_59_RENESAS_FLX0CCSV_FLX0HRQ_MASK                    0x00000080UL /* HRQ */
#define FR_59_RENESAS_FLX0CCSV_FLX0FSI_MASK                    0x00000040UL /* FSI */
#define FR_59_RENESAS_FLX0CCSV_FLX0CSNI_MASK                   0x00001000UL /* CSNI */

/* Shift value for wakeup status*/
#define FR_59_RENESAS_FLX0CCSV_FLX0WSV_SHIFT                   16U

#define FR_59_RENESAS_FLX0CCSV_FLX0SLM_SHIFT                   8U /* Shift value for slot mode */

#define FR_59_RENESAS_FLX0CCEV_FLX0ERRM_MASK                   0x000000C0UL /* ERRM[1:0] */

/* Shift value for error mode. */
#define FR_59_RENESAS_FLX0CCEV_FLX0ERRM_SHIFT                  6U

#define FR_59_RENESAS_FLX0SUCC1_FLX0PBSY_MASK                  0x00000080UL /* PBSY bit */
/* Mask value to set POC command */
#define FR_59_RENESAS_FLX0SUCC1_FLX0CMD_MASK                   0xFFFFFFF0UL

/* Mask to get SUCC1 value except PBSY and CMD[3:0]*/
#define FR_59_RENESAS_FLX0SUCC1_FLX0_PBSY_CMD_MASK             0xFFFFFF00UL

#define FR_59_RENESAS_FLX0SUCC1_FLX0WUCS_MASK                  0xFFDFFFFFUL /* WUCS bit Mask */
#define FR_59_RENESAS_FLX0SUCC1_FLX0WUCS_SET                   0x00200000UL /* WUCS */

#define FR_59_RENESAS_FLX0NEMC_MAX                             12U /* Maximum value of valid */
/* Value in the NEMC. */
/* Mask value to stop timer. */

#define FR_59_RENESAS_FLX0LCK_FIRST                            0x000000CEUL
#define FR_59_RENESAS_FLX0LCK_SECOND                           0x00000031UL

/* Shift value for MTSB */
/* Update bit for no MTS */

/* FREIR.EDA, FREIR.EDB, FREIR.LTVA, FREIR.LTVB */
#define FR_59_RENESAS_FLX0EIR_ED_LTV                           0x03030000UL

#define FR_59_RENESAS_FID_MASK                                 0x000007FFUL /* Frame ID mask value*/
#define FR_59_RENESAS_CYC_MASK                                 0x0000007FUL /* Cycle mask value */
#define FR_59_RENESAS_CYC_SHIFT                                16U
#define FR_59_RENESAS_CHNL_MASK                                0x00000003UL
#define FR_59_RENESAS_CHNL_SHIFT                               24U
#define FR_59_RENESAS_CFG_MASK                                 0x00000001UL
#define FR_59_RENESAS_CFG_SHIFT                                26U
#define FR_59_RENESAS_PPIT_MASK                                0x00000001UL
#define FR_59_RENESAS_PPIT_SHIFT                               27U
#define FR_59_RENESAS_TXM_MASK                                 0x00000001UL
#define FR_59_RENESAS_TXM_SHIFT                                28U
#define FR_59_RENESAS_MBI_MASK                                 0x00000001UL
#define FR_59_RENESAS_MBI_SHIFT                                29U
#define FR_59_RENESAS_CRC_MASK                                 0x000007FFUL
#define FR_59_RENESAS_PLC_MASK                                 0x0000007FUL
#define FR_59_RENESAS_PLC_SHIFT                                16U
#define FR_59_RENESAS_DP_MASK                                  0x000007FFUL
#define FR_59_RENESAS_FLX0IBCR_FLX0IBSYH_MASK                  0x00008000UL

#define FR_59_RENESAS_FLX0IBCR_FLX0IBRH                        0x0000007FUL

/* MB updated with data */
/* Read data and header section */
#define FR_59_RENESAS_FLX0OBCM_READ_MASK                       0x00000003UL
/* Transfer of MB contents from RAM to OBF shadow. */
#define FR_59_RENESAS_FLX0OBCR_RAM_OBF                         0x00000200UL

/* Reset the REQ bit to 0 */
#define FR_59_RENESAS_FLX0OBCR_RAM_OBF_RESET                   0xFFFFFDFFUL
/* Transfer from OBF shadow to OBF host */
#define FR_59_RENESAS_FLX0OBCR_OBFS_OBFH                       0x00000100UL
/* Maximum of payload length */
#define FR_59_RENESAS_PAYLOADLENGTHMAX                         127U    
/* Maximum Message Buffer number*/
#define FR_59_RENESAS_MAX_MB_NUMBER                            127U    
/* Mask to get data length */
#define FR_59_RENESAS_DATA_LENGTH_MASK                         0x7F000000UL
/* Shift value to get data length */
#define FR_59_RENESAS_DATA_LENGTH_SHIFT                        24U
/* Mask to get the 1st byte. */
#define FR_59_RENESAS_DATA_MASK                                0x000000FFUL
/* Shift value to get 2nd byte. */
#define FR_59_RENESAS_DATA_BYTE2_SHIFT                         8U
/* Shift value to get 3rd byte. */
#define FR_59_RENESAS_DATA_BYTE3_SHIFT                         16U
/* Shift value to get last byte. */
#define FR_59_RENESAS_DATA_BYTE4_SHIFT                         24U

#define FR_59_RENESAS_FLX0IBCM_FLX0LHSH_MASK                   0x1U
#define FR_59_RENESAS_FLX0IBCM_FLX0STXRH_FLX0LDSH              0x6U

#define FR_59_RENESAS_FLX0IBCM_FLX0STXRH_CLEAR                 0x2U

#define FR_59_RENESAS_FLX0IBCR_FLX0IBRH_MASK                   0x0000007FUL

#define FR_59_RENESAS_FLX0MTCCV_FLX0CCV_MASK                   0x003F0000UL
#define FR_59_RENESAS_FLX0MTCCV_FLX0CCV_SHIFT                  16U
#define FR_59_RENESAS_FLX0MTCCV_FLX0MTV_MASK                   0x00003FFFUL

#define FR_59_RENESAS_FLX0T0C_FLX0T0RC_SET                     0x00000001UL
#define FR_59_RENESAS_FLX0T0C_FLX0T0RC_CLR                     0x00000001UL
#define FR_59_RENESAS_FLX0T0C_FLX0T0RC_HALT                    0xFFFFFFFEUL

#define FR_59_RENESAS_FLX0T2C_FLX0T2RC_SET                     0x00000001UL
#define FR_59_RENESAS_FLX0T2C_FLX0T2RC_CLR                     0x00000001UL
#define FR_59_RENESAS_FLX0T2C_FLX0T2RC_HALT                    0xFFFFFFFEUL

#define FR_59_RENESAS_FLX0TXC_CYC_SHIFT                        8U
#define FR_59_RENESAS_FLX0TXC_OFFSET_SHIFT                     16U

/* Number of absolute timers configured */

/* Cycle Code Bits masking */
#define FR_59_RENESAS_CYCLE_CODE_MASK                          0x0000007FUL
/* Maximum cycle count value */
#define FR_59_RENESAS_MAX_CYCLE_COUNT                          63U
/* To set the cycle repetition */
/* Mask to set MSB of FLXAnFRTxC.TxCC */
#define FR_59_RENESAS_INT_EVERY_64_CYCLE                       0x00000040UL

#define FR_59_RENESAS_FLX0FROC_T0IE_SET                        0X00010000UL
#define FR_59_RENESAS_FLX0FROS_T0IS_CLR                        0X00010000UL
#define FR_59_RENESAS_FLX0FROC_T0IE_RESET                      0XFFFEFFFFUL
#define FR_59_RENESAS_FLX0FROS_T0IS_MASK                       0X00010000UL

#define FR_59_RENESAS_FLX0FROC_T2IE_SET                        0X00040000UL
#define FR_59_RENESAS_FLX0FROC_T2IE_RESET                      0XFFFBFFFFUL
#define FR_59_RENESAS_FLX0FROS_T2IS_CLR                        0X00040000UL
#define FR_59_RENESAS_FLX0FROS_T2IS_MASK                       0X00040000UL




#define FR_59_RENESAS_SPLM_MASK                                0x00000001UL
#define FR_59_RENESAS_SPLM_SHIFT                               26U
#define FR_59_RENESAS_TXSY_SHIFT                               9U
#define FR_59_RENESAS_TXSY_MASK                                0x00000001UL
#define FR_59_RENESAS_TXST_SHIFT                               8U
#define FR_59_RENESAS_TXST_MASK                                0x00000001UL

#define FR_59_RENESAS_HEADER_LENGTH                            20U
#define FR_59_RENESAS_HCRC_REG_SHIFT                           21U
#define FR_59_RENESAS_HCRC_REG                                 (0x1AUL << FR_59_RENESAS_HCRC_REG_SHIFT)

#define FR_59_RENESAS_CRC_POLY_SHIFT                           21U
#define FR_59_RENESAS_CRC_POLYNOMIAL                           (0x385UL << FR_59_RENESAS_CRC_POLY_SHIFT)

#define FR_59_RENESAS_SYNC_BIT_SHIFT                           19U
#define FR_59_RENESAS_STARTUP_BIT_SHIFT                        18U
#define FR_59_RENESAS_FRAME_ID_SHIFT                           7U
#define FR_59_RENESAS_HEADER_DATA_SHIFT                        1U
#define FR_59_RENESAS_HEADER_SHIFT                             11U
#define FR_59_RENESAS_HEADER_DATA_MASK                         0x80000000UL
#define FR_59_RENESAS_CRC_REG_DATA_SHIFT                       1U


#define FR_59_RENESAS_FLX0ACS_CHNL_A_MASK                      0x0000001FUL
#define FR_59_RENESAS_FLX0ACS_CHNL_B_MASK                      0x0000001FUL


#define FR_59_RENESAS_FLX0SWNIT_MTSA_MASK                      0x00000040UL
#define FR_59_RENESAS_FLX0SWNIT_MTSB_MASK                      0x00000080UL

#define FR_59_RENESAS_FLX0SWNIT_SW_A_MASK                      0x00000007UL
#define FR_59_RENESAS_FLX0SWNIT_SW_B_MASK                      0x00000038UL

#define FR_59_RENESAS_FLX0SWNIT_NIT_A_MASK                     0x00000030UL
#define FR_59_RENESAS_FLX0SWNIT_NIT_B_MASK                     0x000000C0UL


#define FR_59_RENESAS_FLX0FSR_FLX0RFNE_MASK                    0x00000001UL

#define FR_59_RENESAS_FLX0MBS_SLOT_ERROR_MASK                  0x000000FCUL
#define FR_59_RENESAS_FLX0SIR_FLX0WUPA                         0x00010000U /* SIR.WUPA */
#define FR_59_RENESAS_FLX0SIR_FLX0WUPB                         0x01000000U /* SIR.WUPB */
#define FR_59_RENESAS_FLX0MBS_FLX0MBSVFR_MASK                  0x00000003UL
#define FR_59_RENESAS_FLX0MBS_SEOB_CEOB_SVOB_MASK              0x000000A8UL
#define FR_59_RENESAS_FLX0MBS_SEOA_CEOA_SVOA_MASK              0x00000054UL
/* Disable rel timer */
#define FR_59_RENESAS_FLX0PRTC1_FLX0CASM_MASK                  0x0000400UL
#define FR_59_RENESAS_FLX0FROC_OEP_SET                         0x00000080UL
#define FR_59_RENESAS_FLX0FROC_OEP_RESET                       0x00000000UL
#define FR_59_RENESAS_FLX0FROC_OE_SET                          0x00000001UL
#define FR_59_RENESAS_FLX0FROS_OS_MASK                         0x00000001UL
#define FR_59_RENESAS_FLX0FRITC_IQHR_RESET                     0xFFFFFFFDUL /*IQHR*/

#define FR_59_RENESAS_FLX0FRITS_FLX0_ITS_MASK                  0x00000001UL /*ITS*/
#define FR_59_RENESAS_FLX0FRITS_FLX0_ITM_MASK                  0x007F0000UL /*ITM*/
#define FR_59_RENESAS_FLX0FRITC_FLX0_IQHR_MASK                 0x00000002UL /*IQHR*/
#define FR_59_RENESAS_FLX0FRITS_FLX0_IQH_MASK                  0x00000002UL /*IQH*/
#define FR_59_RENESAS_FLX0FROTS_FLX0_OTS_MASK                  0x00000001UL /*OTS*/
#define FR_59_RENESAS_FLX0FROBCR_FLX0_OBSYS_MASK               0x00008000UL /*OBSYS*/
#define FR_59_RENESAS_FLX0FRITS_FLX0_IPIDX_MASK                0x007F0000UL /*IPIDX*/
#define FR_59_RENESAS_FLX0FRITS_FLX0_IGIDX_MASK                0x7F000000UL /*IGIDX*/
#define FR_59_RENESAS_FLX0FRITS_FLX0_IQFP_MASK                 0x00001000UL /*IQFP*/
#define FR_59_RENESAS_FLX0FRWRHS4_FLX0_IMBNR                   0x0000007FUL /*IMBNR*/
#define FR_59_RENESAS_FLX0FRWRHS4_FLX0_INV_MASK                0x00000800UL /*INV*/
#define FR_59_RENESAS_FLX0FRITS_FLX0_UIRP_MASK                 0x00000004UL /*UIRP*/
#define FR_59_RENESAS_FLX0FROTS_FLX0_UORP_MASK                 0x00000004UL /*UORP*/

#define FR_59_RENESAS_FLX0FRUOR_URDS_SET                       0x00000200UL

#define FR_59_RENESAS_FLX0FRITC_ITE_SET                        0x00000001UL
#define FR_59_RENESAS_FLX0FROTC_OTE_SET                        0x00000001UL
#define FR_59_RENESAS_FLX0FRITC_ITE_RESET                      0xFFFFFFFEUL
#define FR_59_RENESAS_FLX0FROTC_OTE_RESET                      0xFFFFFFFEUL
/* Mask for Max FIFO entries contained in local RAM */
#define FR_59_RENESAS_FLX0FROTC_FIFO_MAX                       0x001F0000UL
/* Mask for pMicroPerCycle FLX0GTUC01 FLX0UT[19:00] */
#define FR_59_RENESAS_CIDX_PMICROPERCYCLE_MASK                 0x000FFFFFUL
/* Mask for pdListenTimeout FLX0SUCC2 FLX0LT[20:00] */
#define FR_59_RENESAS_CIDX_PDLISTENTIMEOUT_MASK                0x001FFFFFUL
/* Mask for gMacroPerCycle FLX0GTUC02 FLX0MPC[13:0] */
#define FR_59_RENESAS_CIDX_GMACROPERCYCLE_MASK                 0x00003FFFUL
/* Mask for gNumberOfMinislots FLX0GTUC08 FLX0NMS[28:16] */
#define FR_59_RENESAS_CIDX_GNUMBEROFMINISLOTS_MASK             0x1FFF0000UL
/* Mask for gNumberOfStaticSlots FLX0GTUC07 FLX0NSS[25:16] */
#define FR_59_RENESAS_CIDX_GNUMBEROFSTATICSLOTS_MASK           0x03FF0000UL
/* Mask for gdStaticSlot FLX0GTUC07 FLX0SSL[9:0] */
#define FR_59_RENESAS_CIDX_GDSTATICSLOT_MASK                   0x000003FFUL
/* Mask for gdWakeupSymbolRxWindow FLX0PRTC1 FLX0RXW[24:16] */
#define FR_59_RENESAS_CIDX_GDWAKEUPRXWINDOW_MASK               0x01FF0000UL
/* Mask for pLatestTx FLX0MHDC FLX0SLT[28:16] */
#define FR_59_RENESAS_CIDX_PLATESTTX_MASK                      0x1FFF0000UL
/* Mask for pOffsetCorrectionOut FLX0GTUC10 FLX0MOC[13:0] */
#define FR_59_RENESAS_CIDX_POFFSETCORRECTIONOUT_MASK           0x00003FFFUL
/* Mask for FrPOffsetCorrectionStart FLX0GTUC4 FLX0OCS[29:16] */
#define FR_59_RENESAS_CIDX_POFFSETCORRECTIONSTART_MASK         0x3FFF0000UL
/* Mask for pRateCorrectionOut FLX0GTUC10 FLX0MRC[26:16] */
#define FR_59_RENESAS_CIDX_PRATECORRECTIONOUT_MASK             0x07FF0000UL
/* Mask for pdAcceptedStartupRange FLX0GTUC06 FLX0ASR[26:16] */
#define FR_59_RENESAS_CIDX_PDACCEPTEDSTARTUPRANGE_MASK         0x000007FFUL
/* Mask for gColdstartAttempts FLX0SUCC1 FLX0CSA[15:11] */
#define FR_59_RENESAS_CIDX_GCOLDSTARTATTEMPTS_MASK             0x0000F800UL
/* Mask for gListenNoise FLX0SUCC2 FLX0LTN[27:24] */
#define FR_59_RENESAS_CIDX_GLISTENNOISE_MASK                   0x0F000000UL
/* Mask for FrIfGMaxWithoutClockCorrectFatal FLX0SUCC3 FLX0WCP[7:4] */
#define FR_59_RENESAS_CIDX_GMAXWITHOUTCLOCKCORRECTFATAL_MASK   0x000000F0UL
/* Mask for FrIfGMaxWithoutClockCorrectPassive FLX0SUCC3 FLX0WCF[3:0] */
#define FR_59_RENESAS_CIDX_GMAXWITHOUTCLOCKCORRECTPASSIVE_MASK 0x0000000FUL
/* Mask for gNetworkManagementVectorLength FLX0NEMC FLX0NML[3:0] */
#define FR_59_RENESAS_CIDX_GNETWORKMANAGEMENTVECTORLENGTH_MASK 0x0000000FUL

/* Mask for gPayloadLengthStatic FLX0MHDC FLX0SFDL[6:0] */
#define FR_59_RENESAS_CIDX_GPAYLOADLENGTHSTATIC_MASK           0x0000007FUL
/* Mask for GSYNCFRAMEIDCOUNTMAX FLX0GTUC02 FLX0SNM[19:16] */
#define FR_59_RENESAS_CIDX_GSYNCFRAMEIDCOUNTMAX_MASK           0x000F0000UL
/* Mask for GDACTIONPOINTOFFSET FLX0GTUC09 FLX0APO[5:0] */
#define FR_59_RENESAS_CIDX_GDACTIONPOINTOFFSET_MASK            0x0000003FUL
/* Mask for gdCASRxLowMax FRPRTC1(10:4) */
#define FR_59_RENESAS_CIDX_GDCASRXLOWMAX_MASK                  0x000007F0UL
/* GDDYNAMICSLOTIDLEPHASE FLX0GTUC09 FLX0DSI[17:16] */
#define FR_59_RENESAS_CIDX_GDDYNAMICSLOTIDLEPHASE_MASK         0x00030000UL
/* Mask for gdMinislotActionPointOffset FRGTUC9(12:8) */
#define FR_59_RENESAS_CIDX_GDMINISLOTACTIONPOINTOFFSET_MASK    0x00001F00UL
/* Mask for gdMinislot FRGTUC8(5:0) */
#define FR_59_RENESAS_CIDX_GDMINISLOT_MASK                     0x0000003FUL
/* Mask for gdSampleClockPeriod FRPRTC1(15:14) */
#define FR_59_RENESAS_CIDX_GDSAMPLECLOCKPERIOD_MASK            0x0000C000UL
/* Mask for gdTSSTransmitter FRPRTC1(3:0) */
#define FR_59_RENESAS_CIDX_GDTSSTRANSMITTER_MASK               0x0000000FUL
/* Mask for gdWakeupSymbolTxIdle FRPRTC2 FLX0RXI[5:0] */
#define FR_59_RENESAS_CIDX_GDWAKEUPRXIDLE_MASK                 0x0000003FUL
/* Mask for gdWakeupSymbolTxIdle FRPRTC2(13:8) */
#define FR_59_RENESAS_CIDX_GDWAKEUPRXLOW_MASK                  0x00003F00UL
/* Mask for gdWakeupSymbolTxIdle FRPRTC2(23:16) */
#define FR_59_RENESAS_CIDX_GDWAKEUPTXIDLE_MASK                 0x00FF0000UL
/* Mask for gdWakeupSymbolTxLow FRPRTC2(29:24) */
#define FR_59_RENESAS_CIDX_GDWAKEUPTXACTIVE_MASK               0x3F000000UL
/* Mask for pAllowPassiveToActive FLX0SUCC1 FLX0PTA[20:16] */
#define FR_59_RENESAS_CIDX_PALLOWPASSIVETOACTIVE_MASK          0x001F0000UL
/* Mask for pChannelsA FLX0SUCC1 FLX0CCHA(26), FLX0CCHB(27) */
#define FR_59_RENESAS_CIDX_PCHANNELS_MASK                      0x0C000000UL
/* Mask for pClusterDriftDamping FRGTUC5(20:16) */
#define FR_59_RENESAS_CIDX_PCLUSTERDRIFTDAMPING_MASK           0x001F0000UL
/* Mask for pDecodingCorrection FRGTUC5(31:24) */
#define FR_59_RENESAS_CIDX_PDECODINGCORRECTION_MASK            0xFF000000UL
/* Mask for pDelayCompensationA FRGTUC5(7:0) */
#define FR_59_RENESAS_CIDX_PDELAYCOMPENSATIONA_MASK            0x000000FFUL
/* Mask for pDelayCompensationB FRGTUC5(15:8) */
#define FR_59_RENESAS_CIDX_PDELAYCOMPENSATIONB_MASK            0x0000FF00UL
/* Mask for pMacroInitialOffsetA FRGTUC3(22:16) */
#define FR_59_RENESAS_CIDX_PMACROINITIALOFFSETA_MASK           0x007F0000UL
/* Mask for pMacroInitialOffsetB FRGTUC3(30:24) */
#define FR_59_RENESAS_CIDX_PMACROINITIALOFFSETB_MASK           0x7F000000UL
/* Mask for pMicroInitialOffsetA RGTUC3(7:0) */
#define FR_59_RENESAS_CIDX_PMICROINITIALOFFSETA_MASK           0x000000FFUL
/* Mask for pMicroInitialOffsetB FRGTUC3(15:8) */
#define FR_59_RENESAS_CIDX_PMICROINITIALOFFSETB_MASK           0x0000FF00UL

/* Mask for pSamplesPerMicrotick FRPRTC1(15:14) */
#define FR_59_RENESAS_CIDX_PSAMPLESPERMICROTICK_MASK           0x0000C000UL
/* Mask for pWakeupChannel FRSUCC1(21) */
#define FR_59_RENESAS_CIDX_PWAKEUPCHANNEL_MASK                 0x00200000UL
/* Mask for pWakeupPattern FRPRTC1(31:26) */
#define FR_59_RENESAS_CIDX_PWAKEUPPATTERN_MASK                 0xFC000000UL
/* Mask for PDMICROTICK FLX0PRTC1 FLX0BRP[15:14] */
#define FR_59_RENESAS_CIDX_PDMICROTICK_MASK                    0x0000C000UL
/* Mask for pAllowHaltDueToClock FRSUCC1(23) */
#define FR_59_RENESAS_CIDX_PALLOWHALTDUETOCLOCK_MASK           0x00800000UL
/* Mask for PKEYSLOTONLYENABLED FLX0SUCC1 FLX0TSM (22) */
#define FR_59_RENESAS_CIDX_PKEYSLOTONLYENABLED_MASK            0x00400000UL
/* Mask for PKEYSLOTUSEDFORSTARTUP FLX0SUCC1 FLX0TXST (8) */
#define FR_59_RENESAS_CIDX_PKEYSLOTUSEDFORSTARTUP_MASK         0x00000100UL
/* Mask for PKEYSLOTUSEDFORSYNC FLX0SUCC1 FLX0TXSY (9) */
#define FR_59_RENESAS_CIDX_PKEYSLOTUSEDFORSYNC_MASK            0x00000200UL

#define FR_59_RENESAS_FLXnFRDAi_MASK                           0x1FU
#define FR_59_RENESAS_FLXnFRDA_INDEX_MASK                      0x03U
#define FR_59_RENESAS_FLX0FRDA_FLAG_RESET                      0xFFFFFFFFUL
#define FR_59_RENESAS_FLX0FRDA_INDEX_ZERO                      0x00U
#define FR_59_RENESAS_FLX0FRDA_INDEX_ONE                       0x01U
#define FR_59_RENESAS_FLX0FRDA_INDEX_TWO                       0x02U
#define FR_59_RENESAS_FLX0FRAES_RESET                          0x00000F00UL
/*Mask values for register write verification*/

#define FR_59_RENESAS_FLX0ACS_MASK                             0x00001F1FUL
#define FR_59_RENESAS_DEM_NOT_CONFIGURED                       0U
#define FR_59_RENESAS_INVALID_LPDUID                           4096U
#define FR_59_RENESAS_MAX_CYCLE_CODE                           127U    
#define FR_59_RENESAS_FLX0FRRCV_MASK                           0x00000800UL
#define FR_59_RENESAS_FLX0FROCV_MASK                           0x00040000UL
#define FR_59_RENESAS_FLX0FRRCV_COMPLEMENT                     0x0000F000UL
#define FR_59_RENESAS_FLX0FROCV_COMPLEMENT                     0xFFF80000UL

/*  FRWRHS1.CH, FRWRHS1.CYC  */
#define FR_59_RENESAS_CHANNEL_MASK                             0x03000000UL
#define FR_59_RENESAS_CYCLE_MASK                               0x007F0000UL

/* Multicore support */
#if (FR_59_RENESAS_MULTI_CORE_SUPPORT == STD_ON)
#define FR_59_RENESAS_INVALID_CORE                              (uint8)0xFF
#endif

/***********************************************************************************************************************
 **                      Structure declarations                                **
 *******************************************************************************/

/* Structure for FlexRay Operation register set */
typedef struct STag_Fr_59_Renesas_OperationRegType                                                                      /* PRQA S 3630 # JV-01 */
{
  uint32 ulFLXAnFROC; /* <FLXAn_base> + 0004H */
  uint32 ulReserved0; /* <FLXAn_base> + 0008H */
  uint32 ulFLXAnFROS; /* <FLXAn_base> + 000CH */
} Fr_59_Renesas_OperationRegType;

/* Structure for interrupt register set */
typedef struct STag_Fr_59_Renesas_InterruptRegType                                                                      /* PRQA S 3630 # JV-01 */
{
  uint32 ulFLXAnFREIR;  /* <FLXAn_base> + 0020H */
  uint32 ulFLXAnFRSIR;  /* <FLXAn_base> + 0024H */
  uint32 ulFLXAnFREILS; /* <FLXAn_base> + 0028H */
  uint32 ulFLXAnFRSILS; /* <FLXAn_base> + 002CH */
  uint32 ulFLXAnFREIES; /* <FLXAn_base> + 0030H */
  uint32 ulFLXAnFREIER; /* <FLXAn_base> + 0034H */
  uint32 ulFLXAnFRSIES; /* <FLXAn_base> + 0038H */
  uint32 ulFLXAnFRSIER; /* <FLXAn_base> + 003CH */
  uint32 ulFLXAnFRILE;  /* <FLXAn_base> + 0040H */
} Fr_59_Renesas_InterruptRegType;

/* Structure for FlexRay Timer register set */
typedef struct STag_Fr_59_Renesas_TimerRegType                                                                          /* PRQA S 3630 # JV-01 */
{
  uint32 ulFLXAnFRT0C;   /* <FLXAn_base> + 0044H */
  uint32 ulFLXAnFRT1C;   /* <FLXAn_base> + 0048H */
  uint32 ulFLXAnFRSTPW1; /* <FLXAn_base> + 004CH */
  uint32 ulFLXAnFRSTPW2; /* <FLXAn_base> + 0050H */
} Fr_59_Renesas_TimerRegType;

/* Structure for CC Control register set */
typedef struct STag_Fr_59_Renesas_CCControlRegType                                                                      /* PRQA S 3630 # JV-01 */
{
  uint32 ulFLXAnFRSUCC1;  /* <FLXAn_base> + 0080H */
  uint32 ulFLXAnFRSUCC2;  /* <FLXAn_base> + 0084H */
  uint32 ulFLXAnFRSUCC3;  /* <FLXAn_base> + 0088H */
  uint32 ulFLXAnFRNEMC;   /* <FLXAn_base> + 008CH */
  uint32 ulFLXAnFRPRTC1;  /* <FLXAn_base> + 0090H */
  uint32 ulFLXAnFRPRTC2;  /* <FLXAn_base> + 0094H */
  uint32 ulFLXAnFRMHDC;   /* <FLXAn_base> + 0098H */
  uint32 ulReserved0;     /* <FLXAn_base> + 009CH */
  uint32 ulFLXAnFRGTUC1;  /* <FLXAn_base> + 00A0H */
  uint32 ulFLXAnFRGTUC2;  /* <FLXAn_base> + 00A4H */
  uint32 ulFLXAnFRGTUC3;  /* <FLXAn_base> + 00A8H */
  uint32 ulFLXAnFRGTUC4;  /* <FLXAn_base> + 00ACH */
  uint32 ulFLXAnFRGTUC5;  /* <FLXAn_base> + 00B0H */
  uint32 ulFLXAnFRGTUC6;  /* <FLXAn_base> + 00B4H */
  uint32 ulFLXAnFRGTUC7;  /* <FLXAn_base> + 00B8H */
  uint32 ulFLXAnFRGTUC8;  /* <FLXAn_base> + 00BCH */
  uint32 ulFLXAnFRGTUC9;  /* <FLXAn_base> + 00C0H */
  uint32 ulFLXAnFRGTUC10; /* <FLXAn_base> + 00C4H */
  uint32 ulFLXAnFRGTUC11; /* <FLXAn_base> + 00C8H */
} Fr_59_Renesas_CCControlRegType;

/* Structure for CC Status register set */
typedef struct STag_Fr_59_Renesas_CCStatusRegType                                                                       /* PRQA S 3630 # JV-01 */
{
  uint32 ulFLXAnFRCCSV;   /* <FLXAn_base> + 0100H */
  uint32 ulFLXAnFRCCEV;   /* <FLXAn_base> + 0104H */
  uint32 ulReserved0;     /* <FLXAn_base> + 0108H */
  uint32 ulReserved1;     /* <FLXAn_base> + 010CH */
  uint32 ulFLXAnFRSCV;    /* <FLXAn_base> + 0110H */
  uint32 ulFLXAnFRMTCCV;  /* <FLXAn_base> + 0114H */
  uint32 ulFLXAnFRRCV;    /* <FLXAn_base> + 0118H */
  uint32 ulFLXAnFROCV;    /* <FLXAn_base> + 011CH */
  uint32 ulFLXAnFRSFS;    /* <FLXAn_base> + 0120H */
  uint32 ulFLXAnFRSWNIT;  /* <FLXAn_base> + 0124H */
  uint32 ulFLXAnFRACS;    /* <FLXAn_base> + 0128H */
  uint32 ulReserved2;     /* <FLXAn_base> + 012CH */
  uint32 ulFLXAnFRESID1;  /* <FLXAn_base> + 0130H */
  uint32 ulFLXAnFRESID2;  /* <FLXAn_base> + 0134H */
  uint32 ulFLXAnFRESID3;  /* <FLXAn_base> + 0138H */
  uint32 ulFLXAnFRESID4;  /* <FLXAn_base> + 013CH */
  uint32 ulFLXAnFRESID5;  /* <FLXAn_base> + 0140H */
  uint32 ulFLXAnFRESID6;  /* <FLXAn_base> + 0144H */
  uint32 ulFLXAnFRESID7;  /* <FLXAn_base> + 0148H */
  uint32 ulFLXAnFRESID8;  /* <FLXAn_base> + 014CH */
  uint32 ulFLXAnFRESID9;  /* <FLXAn_base> + 0150H */
  uint32 ulFLXAnFRESID10; /* <FLXAn_base> + 0154H */
  uint32 ulFLXAnFRESID11; /* <FLXAn_base> + 0158H */
  uint32 ulFLXAnFRESID12; /* <FLXAn_base> + 015CH */
  uint32 ulFLXAnFRESID13; /* <FLXAn_base> + 0160H */
  uint32 ulFLXAnFRESID14; /* <FLXAn_base> + 0164H */
  uint32 ulFLXAnFRESID15; /* <FLXAn_base> + 0168H */
  uint32 ulReserved3;     /* <FLXAn_base> + 016CH */
  uint32 ulFLXAnFROSID1;  /* <FLXAn_base> + 0170H */
  uint32 ulFLXAnFROSID2;  /* <FLXAn_base> + 0174H */
  uint32 ulFLXAnFROSID3;  /* <FLXAn_base> + 0178H */
  uint32 ulFLXAnFROSID4;  /* <FLXAn_base> + 017CH */
  uint32 ulFLXAnFROSID5;  /* <FLXAn_base> + 0180H */
  uint32 ulFLXAnFROSID6;  /* <FLXAn_base> + 0184H */
  uint32 ulFLXAnFROSID7;  /* <FLXAn_base> + 0188H */
  uint32 ulFLXAnFROSID8;  /* <FLXAn_base> + 018CH */
  uint32 ulFLXAnFROSID9;  /* <FLXAn_base> + 0190H */
  uint32 ulFLXAnFROSID10; /* <FLXAn_base> + 0194H */
  uint32 ulFLXAnFROSID11; /* <FLXAn_base> + 0198H */
  uint32 ulFLXAnFROSID12; /* <FLXAn_base> + 019CH */
  uint32 ulFLXAnFROSID13; /* <FLXAn_base> + 01A0H */
  uint32 ulFLXAnFROSID14; /* <FLXAn_base> + 01A4H */
  uint32 ulFLXAnFROSID15; /* <FLXAn_base> + 01A8H */
  uint32 ulReserved4;     /* <FLXAn_base> + 01ACH */
  uint32 ulFLXAnFRNMV1;   /* <FLXAn_base> + 01B0H */
  uint32 ulFLXAnFRNMV2;   /* <FLXAn_base> + 01B4H */
  uint32 ulFLXAnFRNMV3;   /* <FLXAn_base> + 01B8H */
} Fr_59_Renesas_CCStatusRegType;

/* Structure for Message Buffer Control register set */
typedef struct STag_Fr_59_Renesas_MessageBufferControlRegType                                                           /* PRQA S 3630 # JV-01 */
{
  uint32 ulFLXAnFRMRC;  /* <FLXAn_base> + 0300H */
  uint32 ulFLXAnFRFRF;  /* <FLXAn_base> + 0304H */
  uint32 ulFLXAnFRFRFM; /* <FLXAn_base> + 0308H */
  uint32 ulFLXAnFRFCL;  /* <FLXAn_base> + 030CH */
} Fr_59_Renesas_MessageBufferControlRegType;

/* Structure for Message Buffer Status register set */
typedef struct STag_Fr_59_Renesas_MessageBufferStatusRegType                                                            /* PRQA S 3630 # JV-01 */
{
  uint32 ulFLXAnFRMHDS;  /* <FLXAn_base> + 0310H */
  uint32 ulFLXAnFRLDTS;  /* <FLXAn_base> + 0314H */
  uint32 ulFLXAnFRFSR;   /* <FLXAn_base> + 0318H */
  uint32 ulFLXAnFRMHDF;  /* <FLXAn_base> + 031CH */
  uint32 ulFLXAnFRTXRQ1; /* <FLXAn_base> + 0320H */
  uint32 ulFLXAnFRTXRQ2; /* <FLXAn_base> + 0324H */
  uint32 ulFLXAnFRTXRQ3; /* <FLXAn_base> + 0328H */
  uint32 ulFLXAnFRTXRQ4; /* <FLXAn_base> + 032CH */
  uint32 ulFLXAnFRNDAT1; /* <FLXAn_base> + 0330H */
  uint32 ulFLXAnFRNDAT2; /* <FLXAn_base> + 0334H */
  uint32 ulFLXAnFRNDAT3; /* <FLXAn_base> + 0338H */
  uint32 ulFLXAnFRNDAT4; /* <FLXAn_base> + 033CH */
  uint32 ulFLXAnFRMBSC1; /* <FLXAn_base> + 0340H */
  uint32 ulFLXAnFRMBSC2; /* <FLXAn_base> + 0344H */
  uint32 ulFLXAnFRMBSC3; /* <FLXAn_base> + 0348H */
  uint32 ulFLXAnFRMBSC4; /* <FLXAn_base> + 034CH */
} Fr_59_Renesas_MessageBufferStatusRegType;

/* Structure for Input Buffer register set */
typedef struct STag_Fr_59_Renesas_InputBufferRegType                                                                    /* PRQA S 3630 # JV-01 */
{
  uint32 ulFLXAnFRWRDS1;  /* <FLXAn_base> +  0400H */
  uint32 ulFLXAnFRWRDS2;  /* <FLXAn_base> +  0404H */
  uint32 ulFLXAnFRWRDS3;  /* <FLXAn_base> +  0408H */
  uint32 ulFLXAnFRWRDS4;  /* <FLXAn_base> +  040CH */
  uint32 ulFLXAnFRWRDS5;  /* <FLXAn_base> +  0410H */
  uint32 ulFLXAnFRWRDS6;  /* <FLXAn_base> +  0414H */
  uint32 ulFLXAnFRWRDS7;  /* <FLXAn_base> +  0418H */
  uint32 ulFLXAnFRWRDS8;  /* <FLXAn_base> +  041CH */
  uint32 ulFLXAnFRWRDS9;  /* <FLXAn_base> +  0420H */
  uint32 ulFLXAnFRWRDS10; /* <FLXAn_base> +  0424H */
  uint32 ulFLXAnFRWRDS11; /* <FLXAn_base> +  0428H */
  uint32 ulFLXAnFRWRDS12; /* <FLXAn_base> +  042CH */
  uint32 ulFLXAnFRWRDS13; /* <FLXAn_base> +  0430H */
  uint32 ulFLXAnFRWRDS14; /* <FLXAn_base> +  0434H */
  uint32 ulFLXAnFRWRDS15; /* <FLXAn_base> +  0438H */
  uint32 ulFLXAnFRWRDS16; /* <FLXAn_base> +  043CH */
  uint32 ulFLXAnFRWRDS17; /* <FLXAn_base> +  0440H */
  uint32 ulFLXAnFRWRDS18; /* <FLXAn_base> +  0444H */
  uint32 ulFLXAnFRWRDS19; /* <FLXAn_base> +  0448H */
  uint32 ulFLXAnFRWRDS20; /* <FLXAn_base> +  044CH */
  uint32 ulFLXAnFRWRDS21; /* <FLXAn_base> +  0450H */
  uint32 ulFLXAnFRWRDS22; /* <FLXAn_base> +  0454H */
  uint32 ulFLXAnFRWRDS23; /* <FLXAn_base> +  0458H */
  uint32 ulFLXAnFRWRDS24; /* <FLXAn_base> +  045CH */
  uint32 ulFLXAnFRWRDS25; /* <FLXAn_base> +  0460H */
  uint32 ulFLXAnFRWRDS26; /* <FLXAn_base> +  0464H */
  uint32 ulFLXAnFRWRDS27; /* <FLXAn_base> +  0468H */
  uint32 ulFLXAnFRWRDS28; /* <FLXAn_base> +  046CH */
  uint32 ulFLXAnFRWRDS29; /* <FLXAn_base> +  0470H */
  uint32 ulFLXAnFRWRDS30; /* <FLXAn_base> +  0474H */
  uint32 ulFLXAnFRWRDS31; /* <FLXAn_base> +  0478H */
  uint32 ulFLXAnFRWRDS32; /* <FLXAn_base> +  047CH */
  uint32 ulFLXAnFRWRDS33; /* <FLXAn_base> +  0480H */
  uint32 ulFLXAnFRWRDS34; /* <FLXAn_base> +  0484H */
  uint32 ulFLXAnFRWRDS35; /* <FLXAn_base> +  0488H */
  uint32 ulFLXAnFRWRDS36; /* <FLXAn_base> +  048CH */
  uint32 ulFLXAnFRWRDS37; /* <FLXAn_base> +  0490H */
  uint32 ulFLXAnFRWRDS38; /* <FLXAn_base> +  0494H */
  uint32 ulFLXAnFRWRDS39; /* <FLXAn_base> +  0498H */
  uint32 ulFLXAnFRWRDS40; /* <FLXAn_base> +  049CH */
  uint32 ulFLXAnFRWRDS41; /* <FLXAn_base> +  04A0H */
  uint32 ulFLXAnFRWRDS42; /* <FLXAn_base> +  04A4H */
  uint32 ulFLXAnFRWRDS43; /* <FLXAn_base> +  04A8H */
  uint32 ulFLXAnFRWRDS44; /* <FLXAn_base> +  04ACH */
  uint32 ulFLXAnFRWRDS45; /* <FLXAn_base> +  04B0H */
  uint32 ulFLXAnFRWRDS46; /* <FLXAn_base> +  04B4H */
  uint32 ulFLXAnFRWRDS47; /* <FLXAn_base> +  04B8H */
  uint32 ulFLXAnFRWRDS48; /* <FLXAn_base> +  04BCH */
  uint32 ulFLXAnFRWRDS49; /* <FLXAn_base> +  04C0H */
  uint32 ulFLXAnFRWRDS50; /* <FLXAn_base> +  04C4H */
  uint32 ulFLXAnFRWRDS51; /* <FLXAn_base> +  04C8H */
  uint32 ulFLXAnFRWRDS52; /* <FLXAn_base> +  04CCH */
  uint32 ulFLXAnFRWRDS53; /* <FLXAn_base> +  04D0H */
  uint32 ulFLXAnFRWRDS54; /* <FLXAn_base> +  04D4H */
  uint32 ulFLXAnFRWRDS55; /* <FLXAn_base> +  04D8H */
  uint32 ulFLXAnFRWRDS56; /* <FLXAn_base> +  04DCH */
  uint32 ulFLXAnFRWRDS57; /* <FLXAn_base> +  04E0H */
  uint32 ulFLXAnFRWRDS58; /* <FLXAn_base> +  04E4H */
  uint32 ulFLXAnFRWRDS59; /* <FLXAn_base> +  04E8H */
  uint32 ulFLXAnFRWRDS60; /* <FLXAn_base> +  04ECH */
  uint32 ulFLXAnFRWRDS61; /* <FLXAn_base> +  04F0H */
  uint32 ulFLXAnFRWRDS62; /* <FLXAn_base> +  04F4H */
  uint32 ulFLXAnFRWRDS63; /* <FLXAn_base> +  04F8H */
  uint32 ulFLXAnFRWRDS64; /* <FLXAn_base> +  04FCH */
  uint32 ulFLXAnFRWRHS1;  /* <FLXAn_base> +  0500H */
  uint32 ulFLXAnFRWRHS2;  /* <FLXAn_base> +  0504H */
  uint32 ulFLXAnFRWRHS3;  /* <FLXAn_base> +  0508H */
  uint32 ulReserved4;     /* <FLXAn_base> +  050CH */
  uint32 ulFLXAnFRIBCM;   /* <FLXAn_base> +  0510H */
  uint32 ulFLXAnFRIBCR;   /* <FLXAn_base> +  0514H */
} Fr_59_Renesas_InputBufferRegType;

/* Structure for Output Buffer register set */
typedef struct STag_Fr_59_Renesas_OutputBufferRegType                                                                   /* PRQA S 3630 # JV-01 */
{
  uint32 ulFLXAnFRRDDS1;  /* <FLXAn_base> +  0600H */
  uint32 ulFLXAnFRRDDS2;  /* <FLXAn_base> +  0604H */
  uint32 ulFLXAnFRRDDS3;  /* <FLXAn_base> +  0608H */
  uint32 ulFLXAnFRRDDS4;  /* <FLXAn_base> +  060CH */
  uint32 ulFLXAnFRRDDS5;  /* <FLXAn_base> +  0610H */
  uint32 ulFLXAnFRRDDS6;  /* <FLXAn_base> +  0614H */
  uint32 ulFLXAnFRRDDS7;  /* <FLXAn_base> +  0618H */
  uint32 ulFLXAnFRRDDS8;  /* <FLXAn_base> +  061CH */
  uint32 ulFLXAnFRRDDS9;  /* <FLXAn_base> +  0620H */
  uint32 ulFLXAnFRRDDS10; /* <FLXAn_base> +  0624H */
  uint32 ulFLXAnFRRDDS11; /* <FLXAn_base> +  0628H */
  uint32 ulFLXAnFRRDDS12; /* <FLXAn_base> +  062CH */
  uint32 ulFLXAnFRRDDS13; /* <FLXAn_base> +  0630H */
  uint32 ulFLXAnFRRDDS14; /* <FLXAn_base> +  0634H */
  uint32 ulFLXAnFRRDDS15; /* <FLXAn_base> +  0638H */
  uint32 ulFLXAnFRRDDS16; /* <FLXAn_base> +  063CH */
  uint32 ulFLXAnFRRDDS17; /* <FLXAn_base> +  0640H */
  uint32 ulFLXAnFRRDDS18; /* <FLXAn_base> +  0644H */
  uint32 ulFLXAnFRRDDS19; /* <FLXAn_base> +  0648H */
  uint32 ulFLXAnFRRDDS20; /* <FLXAn_base> +  064CH */
  uint32 ulFLXAnFRRDDS21; /* <FLXAn_base> +  0650H */
  uint32 ulFLXAnFRRDDS22; /* <FLXAn_base> +  0654H */
  uint32 ulFLXAnFRRDDS23; /* <FLXAn_base> +  0658H */
  uint32 ulFLXAnFRRDDS24; /* <FLXAn_base> +  065CH */
  uint32 ulFLXAnFRRDDS25; /* <FLXAn_base> +  0660H */
  uint32 ulFLXAnFRRDDS26; /* <FLXAn_base> +  0664H */
  uint32 ulFLXAnFRRDDS27; /* <FLXAn_base> +  0668H */
  uint32 ulFLXAnFRRDDS28; /* <FLXAn_base> +  066CH */
  uint32 ulFLXAnFRRDDS29; /* <FLXAn_base> +  0670H */
  uint32 ulFLXAnFRRDDS30; /* <FLXAn_base> +  0674H */
  uint32 ulFLXAnFRRDDS31; /* <FLXAn_base> +  0678H */
  uint32 ulFLXAnFRRDDS32; /* <FLXAn_base> +  067CH */
  uint32 ulFLXAnFRRDDS33; /* <FLXAn_base> +  0680H */
  uint32 ulFLXAnFRRDDS34; /* <FLXAn_base> +  0684H */
  uint32 ulFLXAnFRRDDS35; /* <FLXAn_base> +  0688H */
  uint32 ulFLXAnFRRDDS36; /* <FLXAn_base> +  068CH */
  uint32 ulFLXAnFRRDDS37; /* <FLXAn_base> +  0690H */
  uint32 ulFLXAnFRRDDS38; /* <FLXAn_base> +  0694H */
  uint32 ulFLXAnFRRDDS39; /* <FLXAn_base> +  0698H */
  uint32 ulFLXAnFRRDDS40; /* <FLXAn_base> +  069CH */
  uint32 ulFLXAnFRRDDS41; /* <FLXAn_base> +  06A0H */
  uint32 ulFLXAnFRRDDS42; /* <FLXAn_base> +  06A4H */
  uint32 ulFLXAnFRRDDS43; /* <FLXAn_base> +  06A8H */
  uint32 ulFLXAnFRRDDS44; /* <FLXAn_base> +  06ACH */
  uint32 ulFLXAnFRRDDS45; /* <FLXAn_base> +  06B0H */
  uint32 ulFLXAnFRRDDS46; /* <FLXAn_base> +  06B4H */
  uint32 ulFLXAnFRRDDS47; /* <FLXAn_base> +  06B8H */
  uint32 ulFLXAnFRRDDS48; /* <FLXAn_base> +  06BCH */
  uint32 ulFLXAnFRRDDS49; /* <FLXAn_base> +  06C0H */
  uint32 ulFLXAnFRRDDS50; /* <FLXAn_base> +  06C4H */
  uint32 ulFLXAnFRRDDS51; /* <FLXAn_base> +  06C8H */
  uint32 ulFLXAnFRRDDS52; /* <FLXAn_base> +  06CCH */
  uint32 ulFLXAnFRRDDS53; /* <FLXAn_base> +  06D0H */
  uint32 ulFLXAnFRRDDS54; /* <FLXAn_base> +  06D4H */
  uint32 ulFLXAnFRRDDS55; /* <FLXAn_base> +  06D8H */
  uint32 ulFLXAnFRRDDS56; /* <FLXAn_base> +  06DCH */
  uint32 ulFLXAnFRRDDS57; /* <FLXAn_base> +  06E0H */
  uint32 ulFLXAnFRRDDS58; /* <FLXAn_base> +  06E4H */
  uint32 ulFLXAnFRRDDS59; /* <FLXAn_base> +  06E8H */
  uint32 ulFLXAnFRRDDS60; /* <FLXAn_base> +  06ECH */
  uint32 ulFLXAnFRRDDS61; /* <FLXAn_base> +  06F0H */
  uint32 ulFLXAnFRRDDS62; /* <FLXAn_base> +  06F4H */
  uint32 ulFLXAnFRRDDS63; /* <FLXAn_base> +  06F8H */
  uint32 ulFLXAnFRRDDS64; /* <FLXAn_base> +  06FCH */
  uint32 ulFLXAnFRRDHS1;  /* <FLXAn_base> +  0700H */
  uint32 ulFLXAnFRRDHS2;  /* <FLXAn_base> +  0704H */
  uint32 ulFLXAnFRRDHS3;  /* <FLXAn_base> +  0708H */
  uint32 ulFLXAnFRMBS;    /* <FLXAn_base> +  070CH */
  uint32 ulFLXAnFROBCM;   /* <FLXAn_base> +  0710H */
  uint32 ulFLXAnFROBCR;   /* <FLXAn_base> +  0714H */
} Fr_59_Renesas_OutputBufferRegType;

/* Structure for Data Transfer Control register set */
typedef struct STag_Fr_59_Renesas_DataTransferControlRegType                                                            /* PRQA S 3630 # JV-01 */
{
  uint32 ulFLXAnFRITC; /* <FLXAn_base> +  0800H */
  uint32 ulFLXAnFROTC; /* <FLXAn_base> +  0804H */
  uint32 ulFLXAnFRIBA; /* <FLXAn_base> +  0808H */
  uint32 ulFLXAnFRFBA; /* <FLXAn_base> +  080CH */
  uint32 ulFLXAnFROBA; /* <FLXAn_base> +  0810H */
  uint32 ulFLXAnFRIQC; /* <FLXAn_base> +  0814H */
  uint32 ulFLXAnFRUIR; /* <FLXAn_base> +  0818H */
  uint32 ulFLXAnFRUOR; /* <FLXAn_base> +  081CH */
} Fr_59_Renesas_DataTransferControlRegType;

/* Structure for Data Transfer Status register set */
typedef struct STag_Fr_59_Renesas_DataTransferStatusRegType                                                             /* PRQA S 3630 # JV-01 */
{
  uint32 ulFLXAnFRITS; /* <FLXAn_base> +  0820H */
  uint32 ulFLXAnFROTS; /* <FLXAn_base> +  0824H */
  uint32 ulFLXAnFRAES; /* <FLXAn_base> +  0828H */
  uint32 ulFLXAnFRAEA; /* <FLXAn_base> +  082CH */
  uint32 ulFLXAnFRDA0; /* <FLXAn_base> +  0830H */
  uint32 ulFLXAnFRDA1; /* <FLXAn_base> +  0834H */
  uint32 ulFLXAnFRDA2; /* <FLXAn_base> +  0838H */
  uint32 ulFLXAnFRDA3; /* <FLXAn_base> +  083CH */
} Fr_59_Renesas_DataTransferStatusRegType;

  /* Structure to contain pointer to register */
  typedef struct Stag_Fr_59_Renesas_ReadDataFromCC
  {
    uint32     LulOffSet;
    uint32     LulConfiguredData;
    uint8      LucRegCnt;
  } Fr_59_Renesas_ReadDataFromCC;
  /* Structure to contain the POC states */
  typedef struct Stag_Fr_59_Renesas_CheckPOCSts
  {
    uint32              LulData;
    Fr_POCStateType     LpState;
    Fr_StartupStateType LpStartupState;
  } Fr_Renesas_CheckPOCSts;

  /* Structure to contain Fr_59_Renesas_UpdateCCConfig */
  typedef struct Stag_Fr_59_Renesas_UpdateCCConfig
  {
    uint8         Fr_ConfigParamIdx;
    P2VAR(volatile uint32, TYPEDEF, REGSPACE) pOffset;
    uint32        LulMask;
    uint8         LucBitsTobeMovedRight;
    uint32        Fr_ConfigParamValuePtr;
  } Fr_Renesas_UpdateCCConfig;

/***********************************************************************************************************************
**                                       Structure for FlexRay registers mirror                                       **
***********************************************************************************************************************/
/* Data section of input data structure */
typedef struct STag_Fr_59_Renesas_InputConstdataType                                                                    /* PRQA S 3630 # JV-01 */
{
  uint32 volatile ulFLXAnFRWRDS1;
  uint32 volatile ulFLXAnFRWRDS2;
  uint32 volatile ulFLXAnFRWRDS3;
  uint32 volatile ulFLXAnFRWRDS4;
  uint32 volatile ulFLXAnFRWRDS5;
  uint32 volatile ulFLXAnFRWRDS6;
  uint32 volatile ulFLXAnFRWRDS7;
} Fr_59_Renesas_InputConstdataType;

/* Data section of output data structure */
typedef struct STag_Fr_59_Renesas_OutputConstdataType                                                                   /* PRQA S 3630 # JV-01 */
{
  uint32 volatile aaFLXAnFRRDDS[FR_59_RENESAS_SIXTYFOUR];
} Fr_59_Renesas_OutputConstdataType;

/* Input data structure (Header and data) */
typedef struct STag_Fr_59_Renesas_InputDataStrType                                                                      /* PRQA S 3630 # JV-01 */
{
  uint32 volatile ulFLX0FRWRHS1;
  uint32 volatile ulFLX0FRWRHS2;
  uint32 volatile ulFLX0FRWRHS3;
  /* Pointer to input data section */
  P2VAR(volatile Fr_59_Renesas_InputConstdataType, TYPEDEF, REGSPACE)
  Fr_59_Renesas_pInputDataSectionPtr;
} Fr_59_Renesas_InputDataStrType;

/* Output data structure (header and data) */
typedef struct STag_Fr_59_Renesas_OuputDataStrType                                                                      /* PRQA S 3630 # JV-01 */
{
  uint32 volatile ulFLX0FRRDHS1;
  uint32 volatile ulFLX0FRRDHS2;
  uint32 volatile ulFLX0FRRDHS3;
  uint32 volatile ulFLX0FRMBS;
  /* Pointer to output data section */
  P2VAR(volatile Fr_59_Renesas_OutputConstdataType, TYPEDEF, REGSPACE)
  Fr_59_Renesas_pOutputDataSectionPtr;
} Fr_59_Renesas_OutputDataStrType;

/* Input queue table structure */
#if (FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON)
typedef struct STag_Fr_59_Renesas_InputPointerTableType                                                                 /* PRQA S 3630 # JV-01 */
{
  uint32 volatile ulFLX0FRWRHS4;
  P2VAR(volatile Fr_59_Renesas_InputDataStrType, TYPEDEF, REGSPACE)
  Fr_59_Renesas_pInputDataPtr;
} Fr_59_Renesas_InputPointerTableType;
#endif

/* Output queue table structure */
#if ((FR_59_RENESAS_ENABLE_INPUT_TX_HANDLER == STD_ON) || (FR_59_RENESAS_ENABLE_OUTPUT_RX_HANDLER == STD_ON) || \
     (FR_59_RENESAS_ENABLE_OUTPUT_RX_FIFO_HANDLER == STD_ON))
typedef struct STag_Fr_59_Renesas_OutputPointerTableType                                                                /* PRQA S 3630 # JV-01 */
{
  P2VAR(volatile Fr_59_Renesas_OutputDataStrType, TYPEDEF, REGSPACE)
  Fr_59_Renesas_pOutputDataPtr;
  /*Message buffer to be transferred */
  uint8 ucMsgBuffer;
} Fr_59_Renesas_OutputPointerTableType;
#endif
/***********************************************************************************************************************
 **                      Enum declarations                                    **
 *******************************************************************************/
/* Fr_TimerSelection */
typedef enum ETag_Fr_59_Renesas_TimerSelectionType
{
  FR_59_RENESAS_TIMER0 = 0,
  FR_59_RENESAS_TIMER2
} Fr_59_Renesas_TimerSelectionType;

/* Fr_TimerModeSelect */
typedef enum ETag_Fr_59_Renesas_TimerModeSelectType
{
  FR_59_RENESAS_SINGLESHOT = 0,
  FR_59_RENESAS_CONTINUOUS
} Fr_59_Renesas_TimerModeSelectType;

#endif /* FR_59_RENESAS_TYPES_H */
/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/
