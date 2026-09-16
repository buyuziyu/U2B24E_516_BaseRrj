/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = RamTst.c                                                                                            */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the implementations AUTOSAR specified APIs for RamTst                                           */
/* handler.                                                                                                           */
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
 *  1.4.1:  30/06/2025  : Update SW-VERSION
 *  1.3.1:  31/03/2025  : To support QAC 11.6.0: Remove redundant msg 2814, 2824, 2844
 *  1.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 *  1.2.0:  31/12/2024  : Update SW-Version for Ver22.02.00/Ver22.02.00.D U2Bx Final release
 *  1.1.2:  31/10/2024  : Update SW-VERSION to 1.1.2
 *  1.1.1:  30/08/2024  : As part of ARDAACL-39377, following changes are made
 *                        1. Update Ramtst_RunPartialTest to fix unintentional area may be test issue.
 *                        As part of QAC 9.5.0 support, following changes are made:
 *                        1. Remove redundant QAC message 3383
 *  1.0.1:  10/01/2024  : Update correct description for all API
 *                        In API RamTst_RunFullTest, add new compiler switch #ifdef RAMTST_RUNFL_RAM_FAILURE
 *                        In API RamTst_RunPartialTest, add new compiler switch #ifdef RAMTST_PART_RAM_FAILURE
 *                        In API RamTst_MainFunction, add new compiler switch #ifdef RAMTST_MAIN_RAM_FAILURE
 *                        Remove QAC message header 2814, 2844, 2824 to support QAC 10.3.0
 *  1.0.0:  17/08/2023  : Update API RamTst_ChangeBlockForeGrndTest to update Overall Test Result correctly.
 *                        Update API RamTst_ChangeNumberOfTestedCells and RamTst_RunPartialTest to support report 
 *                        multiple Det Error.
 *                        Remove Enter/Exit Crictical Section
 *          28/07/2023  : Change function name from RamTst_Checker_Algorithm, RamTst_Galpat_Algorithm, 
 *                        RamTst_WalkPath_Algorithm, RamTst_March_Algorithm, RamTst_Transp_Galpat_Algorithm, 
 *                        RamTst_Abraham_Algorithm, RamTst_Abraham_TestSteps, RamTst_ChangeBlock_BackGrndTest, 
 *                        RamTst_ChangeBlock_ForeGrndTest to  RamTst_CheckerAlgorithm, RamTst_GalpatAlgorithm, 
 *                        RamTst_WalkPathAlgorithm, RamTst_MarchAlgorithm, RamTst_TranspGalpatAlgorithm, 
 *                        RamTst_AbrahamAlgorithm, RamTst_AbrahamTestSteps, RamTst_ChangeBlockBackGrndTest
 *                        RamTst_ChangeBlockForeGrndTest.
 *                        Remove check ECC and March Y algorithm. 
 *                        Update support all function to multi core.  
 *                        Remove global and static variable.
 *                        Add MISRA C Rule Violation (1:3384), (6:2992), (6:2996), (2:3673), (2:3464)
 *          19/06/2023  : Change memory section of global pointer RamTst_GpCellAddress from VAR_INIT_UNSPECIFIED 
 *                        to VAR_INIT_32
 *                        Fix DET condition in API RamTst_RunFullTest
 *                        Remove redundant code in API RamTst_MainFunction 
 *                        Update If condition in API RamTst_WalkPathAlgorithm
 *          19/05/2023  : Initial Version
 */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0791)    : Macro identifier does not differ from other macro identifier(s) (e.g. '%s') within the       */
/*                       specified number of significant characters.                                                  */
/* Rule                : CERTCCM DCL23, MISRA C:2012 Rule-5.4                                                         */
/* JV-01 Justification : This macro identifier is following AUTOSAR standard rule (Symbolic Name or Published         */
/*                       Macro's name), so this is accepted.                                                          */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object 'name' is only referenced in the translation unit where it is defined.            */
/* Rule                : MISRA-C:2012 Rule-8.7, CERT-C:1.2.4 CERTCCM DCL15, DCL19, CWE Rule CWE-398, CWE-569          */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other    */
/*                       C source files                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1503)    : The function '%1s' is defined but is not used within this project.                           */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Rule-2.1, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to the module's API is exported for user's usage.                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3218)    : File scope static, '%s', is only accessed in one function.                                   */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.9, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : By moving the array into the function, the stack size used will be more, hence this is       */
/*                       defined outside.                                                                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3206)    : The parameter '%s' is not used in this function.                                             */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.7, CWE Rule CWE-398, CWE-569, CWE-563              */
/* JV-01 Justification : This is done as per implementation requirement                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : MISRA C:2012 Rule-15.7, CERTCCM MSC01, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else"statement with empty content is removed to improve readability.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0488)    : Performing pointer arithmetic.                                                               */
/* Rule                : CERTCCM EXP08, MISRA C:2012 Rule-18.4, CWE Rule CWE-398, CWE-569, CWE-188                    */
/* JV-01 Justification : This is to get the ID in the data structure in the code.                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold.                                                                   */
/*       Verification  : However, RAMTST_ONE is the lower constrained of RamTstBlockId, prevent LpRamTstBlockConfig   */
/*                       to be out of range.                                                                          */
/* JV-02 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold.                                                                   */
/*       Verification  : However, RAMTST_ONE is the lower constrained of RamTstAlgParamsId, prevent LpRamTstAlgConfig */
/*                       to be out of range.                                                                          */
/* JV-03 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold.                                                                   */
/*       Verification  : However, RAMTST_ONE is the lower constrained of Index, prevent Cellnumber, Bitnumber to be   */
/*                       out of range.                                                                                */
/* JV-04 Justification : The value of RamTstCellAddress is not exceed RamTstEndAddress. So result of operator in range*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1338)    : The parameter '%s' is being modified.                                                        */
/* Rule                : MISRA C:2012 Rule-17.8                                                                       */
/* JV-01 Justification : This in case, parameter is not const, it could be accepted for modification                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : Cast between a pointer to object and an integral type.                                       */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4, CWE Rule CWE-398, CWE-569, CWE-738                    */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0303)    : [I] Cast between a pointer to volatile object and an integral type.                          */
/* Rule                : MISRA C:2012 Rule-11.4,  CERT-C:1.2.4 CERTCCM INT36, CWE Rule CWE-398, CWE-569               */
/* JV-01 Justification : Typecasting is done as per the register size, to access hardware registers.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2992)    : The value of this 'if' controlling expression is always 'false'.                             */
/* Rule                : MISRA C:2012 Rule-14.3                                                                       */
/* JV-01 Justification : This is to support different configuration, macro value can be generated so that such        */
/*                       conditional statement can be either true or false                                            */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2996)    : The result of this logical operation is always 'false'.                                      */
/* Rule                : MISRA C:2012 Rule-2.2, CWE Rule CWE-561, CWE-633                                             */
/* JV-01 Justification : Depending on device status, there is case where the 'if' will return 'true'.                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3673)    : The object addressed by the pointer parameter '%s' is not modified and so the pointer could  */
/*                       be of type 'pointer to const'.                                                               */
/* Rule                : CERTCCM DCL00, DCL13, MISRA C:2012 Rule-8.13, CWE Rule CWE-398, CWE-569                      */
/* JV-01 Justification : Pointer variable is used to modify the value at the address so the pointer cannot be         */
/*                       declared as 'pointer to const' type.                                                         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3464)    : Argument to macro '%s' contains a side effect that will be evaluated more than once.         */
/* Rule                : CERTCCM PRE31                                                                                */
/* JV-01 Justification : This message is only emitted for expressions expanded from argument tokens written out at    */
/*                       the top level, that did not themselves originate from a macro expansion.                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* RamTest Header file */
#include "RamTst.h"
#if (RAMTST_DEV_ERROR_DETECT == STD_ON)
/* Det public header file*/
#include "Det.h"
#endif
#include "SchM_RamTst.h"
/* Dem public header file*/
#include "Dem.h"
#if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define RAMTST_C_AR_RELEASE_MAJOR_VERSION    RAMTST_AR_RELEASE_MAJOR_VERSION_VALUE
#define RAMTST_C_AR_RELEASE_MINOR_VERSION    RAMTST_AR_RELEASE_MINOR_VERSION_VALUE
#define RAMTST_C_AR_RELEASE_REVISION_VERSION RAMTST_AR_RELEASE_REVISION_VERSION_VALUE
/* File version information */
#define RAMTST_C_SW_MAJOR_VERSION            RAMTST_SW_MAJOR_VERSION_VALUE
#define RAMTST_C_SW_MINOR_VERSION            RAMTST_SW_MINOR_VERSION_VALUE
/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (RAMTST_AR_RELEASE_MAJOR_VERSION != RAMTST_C_AR_RELEASE_MAJOR_VERSION)
  #error "RamTst.c : Mismatch in Release Major Version"
#endif
#if (RAMTST_AR_RELEASE_MINOR_VERSION != RAMTST_C_AR_RELEASE_MINOR_VERSION)
  #error "RamTst.c : Mismatch in Release Minor Version"
#endif
#if (RAMTST_AR_RELEASE_REVISION_VERSION != RAMTST_C_AR_RELEASE_REVISION_VERSION)
  #error "RamTst.c : Mismatch in Release Revision Version"
#endif
#if (RAMTST_SW_MAJOR_VERSION != RAMTST_C_SW_MAJOR_VERSION)
  #error "RamTst.c : Mismatch in Software Major Version"
#endif
#if (RAMTST_SW_MINOR_VERSION != RAMTST_C_SW_MINOR_VERSION)
  #error "RamTst.c : Mismatch in Software Minor Version"
#endif
/***********************************************************************************************************************
**                                                  Global Variables                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Static Variables                                                  **
***********************************************************************************************************************/
#if (STD_ON == RAMTST_TRANSP_GALPAT_TEST_SELECTED)
#define RAMTST_START_SEC_CONST_16
#include "RamTst_MemMap.h"

/* Fast CRC lookup table, standard hashing table for Polynomial 0xA001 */
STATIC CONST(uint16, RAMTST_CONST) RamTst_CRC[RAMTST_CRC_TABLE_LENGTH] = {                                              /* PRQA S 3218 # JV-01 */
    0x0000u, 0xC0C1u, 0xC181u, 0x0140u, 0xC301u, 0x03C0u, 0x0280u, 0xC241u, 0xC601u, 0x06C0u, 0x0780u, 0xC741u,
    0x0500u, 0xC5C1u, 0xC481u, 0x0440u, 0xCC01u, 0x0CC0u, 0x0D80u, 0xCD41u, 0x0F00u, 0xCFC1u, 0xCE81u, 0x0E40u,
    0x0A00u, 0xCAC1u, 0xCB81u, 0x0B40u, 0xC901u, 0x09C0u, 0x0880u, 0xC841u, 0xD801u, 0x18C0u, 0x1980u, 0xD941u,
    0x1B00u, 0xDBC1u, 0xDA81u, 0x1A40u, 0x1E00u, 0xDEC1u, 0xDF81u, 0x1F40u, 0xDD01u, 0x1DC0u, 0x1C80u, 0xDC41u,
    0x1400u, 0xD4C1u, 0xD581u, 0x1540u, 0xD701u, 0x17C0u, 0x1680u, 0xD641u, 0xD201u, 0x12C0u, 0x1380u, 0xD341u,
    0x1100u, 0xD1C1u, 0xD081u, 0x1040u, 0xF001u, 0x30C0u, 0x3180u, 0xF141u, 0x3300u, 0xF3C1u, 0xF281u, 0x3240u,
    0x3600u, 0xF6C1u, 0xF781u, 0x3740u, 0xF501u, 0x35C0u, 0x3480u, 0xF441u, 0x3C00u, 0xFCC1u, 0xFD81u, 0x3D40u,
    0xFF01u, 0x3FC0u, 0x3E80u, 0xFE41u, 0xFA01u, 0x3AC0u, 0x3B80u, 0xFB41u, 0x3900u, 0xF9C1u, 0xF881u, 0x3840u,
    0x2800u, 0xE8C1u, 0xE981u, 0x2940u, 0xEB01u, 0x2BC0u, 0x2A80u, 0xEA41u, 0xEE01u, 0x2EC0u, 0x2F80u, 0xEF41u,
    0x2D00u, 0xEDC1u, 0xEC81u, 0x2C40u, 0xE401u, 0x24C0u, 0x2580u, 0xE541u, 0x2700u, 0xE7C1u, 0xE681u, 0x2640u,
    0x2200u, 0xE2C1u, 0xE381u, 0x2340u, 0xE101u, 0x21C0u, 0x2080u, 0xE041u, 0xA001u, 0x60C0u, 0x6180u, 0xA141u,
    0x6300u, 0xA3C1u, 0xA281u, 0x6240u, 0x6600u, 0xA6C1u, 0xA781u, 0x6740u, 0xA501u, 0x65C0u, 0x6480u, 0xA441u,
    0x6C00u, 0xACC1u, 0xAD81u, 0x6D40u, 0xAF01u, 0x6FC0u, 0x6E80u, 0xAE41u, 0xAA01u, 0x6AC0u, 0x6B80u, 0xAB41u,
    0x6900u, 0xA9C1u, 0xA881u, 0x6840u, 0x7800u, 0xB8C1u, 0xB981u, 0x7940u, 0xBB01u, 0x7BC0u, 0x7A80u, 0xBA41u,
    0xBE01u, 0x7EC0u, 0x7F80u, 0xBF41u, 0x7D00u, 0xBDC1u, 0xBC81u, 0x7C40u, 0xB401u, 0x74C0u, 0x7580u, 0xB541u,
    0x7700u, 0xB7C1u, 0xB681u, 0x7640u, 0x7200u, 0xB2C1u, 0xB381u, 0x7340u, 0xB101u, 0x71C0u, 0x7080u, 0xB041u,
    0x5000u, 0x90C1u, 0x9181u, 0x5140u, 0x9301u, 0x53C0u, 0x5280u, 0x9241u, 0x9601u, 0x56C0u, 0x5780u, 0x9741u,
    0x5500u, 0x95C1u, 0x9481u, 0x5440u, 0x9C01u, 0x5CC0u, 0x5D80u, 0x9D41u, 0x5F00u, 0x9FC1u, 0x9E81u, 0x5E40u,
    0x5A00u, 0x9AC1u, 0x9B81u, 0x5B40u, 0x9901u, 0x59C0u, 0x5880u, 0x9841u, 0x8801u, 0x48C0u, 0x4980u, 0x8941u,
    0x4B00u, 0x8BC1u, 0x8A81u, 0x4A40u, 0x4E00u, 0x8EC1u, 0x8F81u, 0x4F40u, 0x8D01u, 0x4DC0u, 0x4C80u, 0x8C41u,
    0x4400u, 0x84C1u, 0x8581u, 0x4540u, 0x8701u, 0x47C0u, 0x4680u, 0x8641u, 0x8201u, 0x42C0u, 0x4380u, 0x8341u,
    0x4100u, 0x81C1u, 0x8081u, 0x4040u};
#define RAMTST_STOP_SEC_CONST_16
#include "RamTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */
#endif
/***********************************************************************************************************************
**                                                 Internal Functions                                                 **
***********************************************************************************************************************/
/* Start of RAMTST Section Code */
#define RAMTST_START_SEC_PRIVATE_CODE
#include "RamTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */
#if (STD_ON == RAMTST_CHECKERBOARD_TEST_SELECTED)
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE) RamTst_CheckerAlgorithm(
    VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber);
#endif
#if (STD_ON == RAMTST_GALPAT_TEST_SELECTED)
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE) RamTst_GalpatAlgorithm(
    VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber);
#endif
#if (STD_ON == RAMTST_WALK_PATH_TEST_SELECTED)
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE) RamTst_WalkPathAlgorithm(
    VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber);
#endif
#if (STD_ON == RAMTST_MARCH_TEST_SELECTED)
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE) RamTst_MarchAlgorithm(
    VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber);
#endif
#if (STD_ON == RAMTST_TRANSP_GALPAT_TEST_SELECTED)
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE) RamTst_TranspGalpatAlgorithm(
    VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber);
#endif
#if (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED)
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE) RamTst_AbrahamAlgorithm(
    VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber);
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE) RamTst_AbrahamTestSteps(
    VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber,
    volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress);                                     /* PRQA S 3432 # JV-01 */
#endif
STATIC FUNC(void, RAMTST_PRIVATE_CODE) RamTst_ChangeBlockBackGrndTest(void);
#if (RAMTST_RUN_FULL_TEST_API == STD_ON)
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE) RamTst_ChangeBlockForeGrndTest(void);
#endif
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE) RamTst_CallAlgorithm(
    VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells);
#if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
STATIC FUNC(void, RAMTST_PRIVATE_CODE) RamTst_SaveData(
    volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_APPL_DATA) LpBuffer,                                          /* PRQA S 3432 # JV-01 */
    VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells);
STATIC FUNC(void, RAMTST_PRIVATE_CODE) RamTst_RestoreData(
    volatile P2CONST(RamTst_TestDataType, AUTOMATIC, RAMTST_APPL_DATA) LpBuffer,
    VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells,
    volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress);                                     /* PRQA S 3432 # JV-01 */
#endif
STATIC FUNC(void, RAMTST_PRIVATE_CODE) RamTst_FillData(
    VAR(uint32, RAMTST_VAR) RamTstFillPattern, VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells,
    volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress);                                     /* PRQA S 3432 # JV-01 */
#if ((STD_ON == RAMTST_ABRAHAM_TEST_SELECTED) || (STD_ON == RAMTST_MARCH_TEST_SELECTED) ||  \
     (STD_ON == RAMTST_GALPAT_TEST_SELECTED) || (STD_ON == RAMTST_WALK_PATH_TEST_SELECTED))
STATIC FUNC(void, RAMTST_PRIVATE_CODE) RamTst_InitializeCell(
    VAR(RamTst_TestDataType, AUTOMATIC) Init_CellVariable, VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells,
    volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress);                                     /* PRQA S 3432 # JV-01 */
#endif
#if ((STD_ON == RAMTST_ABRAHAM_TEST_SELECTED) || (STD_ON == RAMTST_MARCH_TEST_SELECTED))
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_RWAscend(VAR(uint8, AUTOMATIC) CheckVariable, VAR(uint32, AUTOMATIC) Totalbits,
                    volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress);                     /* PRQA S 3432 # JV-01 */
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_RWDescend(VAR(uint8, AUTOMATIC) CheckVariable, VAR(uint32, AUTOMATIC) Totalbits,
                     volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress);                    /* PRQA S 3432 # JV-01 */
#endif
#if (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED)
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_ReadAscend(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells,
                      VAR(RamTst_TestDataType, AUTOMATIC) BackGroundVariable,
                      volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress);                   /* PRQA S 3432 # JV-01 */
#endif
#if (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED)
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_ReadDescend(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells,
                       VAR(RamTst_TestDataType, AUTOMATIC) BackGroundVariable,
                       volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress);                  /* PRQA S 3432 # JV-01 */
#endif
#if (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED)
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_RWWDescend(VAR(uint8, AUTOMATIC) CheckVariable, VAR(uint32, AUTOMATIC) Totalbits,
                      volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress);                   /* PRQA S 3432 # JV-01 */
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_RWWAscend(VAR(uint8, AUTOMATIC) CheckVariable, VAR(uint32, AUTOMATIC) Totalbits,
                     volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress);                    /* PRQA S 3432 # JV-01 */
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_WRWAscend(VAR(uint8, AUTOMATIC) CheckVariable, VAR(uint32, AUTOMATIC) Totalbits,
                     volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress);                    /* PRQA S 3432 # JV-01 */
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_WRWDescend(VAR(uint8, AUTOMATIC) CheckVariable, VAR(uint32, AUTOMATIC) Totalbits,
                      volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress);                   /* PRQA S 3432 # JV-01 */
#endif

STATIC FUNC(uint8, RAMTST_PRIVATE_CODE) RamTst_GetCoreIndex (void);

#define RAMTST_STOP_SEC_PRIVATE_CODE
#include "RamTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
/* Start of RAMTST Section Code */
#define RAMTST_START_SEC_PUBLIC_CODE
#include "RamTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
** Function Name         : RamTst_Init
**
** Service ID            : 0x00
**
** Description           : This API is for initialization and change the state
**                         of Ram Test module.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : ConfigPtr
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : RamTst_GaaGlobalAccPoint,
**                         RamTst_GaaDefaultAlgParams,
**                         RamTst_Config
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : Nones
** Reference ID          : RAMTST_DUD_ACT_001
** Reference ID          : RAMTST_DUD_ACT_001_ERR001, RAMTST_DUD_ACT_001_ERR002
** Reference ID          : RAMTST_DUD_ACT_001_GBL001, RAMTST_DUD_ACT_001_GBL002, RAMTST_DUD_ACT_001_GBL003
** Reference ID          : RAMTST_DUD_ACT_001_GBL004, RAMTST_DUD_ACT_001_GBL005, RAMTST_DUD_ACT_001_GBL006
** Reference ID          : RAMTST_DUD_ACT_001_GBL007, RAMTST_DUD_ACT_001_GBL008
***********************************************************************************************************************/
FUNC(void, RAMTST_PUBLIC_CODE) RamTst_Init(P2CONST(RamTst_ConfigType, AUTOMATIC, RAMTST_CONFIG_CONST) ConfigPtr)        /* PRQA S 1503, 3206 # JV-01, JV-01 */
{
  /* Pointer to the Algorithm Configuration Structure for the RAM Test */ 
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  /* Index to the RamTst_TestResultBuffer */
  VAR(RamTst_NumberOfBlocksType, AUTOMATIC) Index;
  /* Core index */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)  
  /* Check if the Module is initialized */
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_INIT_SVCID, RAMTST_E_INVALID_CORE);
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  if (RAMTST_EXECUTION_UNINIT != (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */  
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_INIT_SVCID, RAMTST_E_STATUS_FAILURE);
  }
  else
  #else
  if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  #endif
  {
    /* Initialize all RAM Test relevant global variables. */
    *(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId) = RamTst_GaaDefaultAlgParams[LucCoreIndex];
    /* Initial value for algorithm is defautl Alg */
    LpRamTstAlgPtr = &((RamTst_Config[RAMTST_ZERO].LpRamTstAlgConfig)
                        [(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]);                       /* PRQA S 3384 # JV-01 */
    *(RamTst_GaaGlobalAccPoint[LucCoreIndex].pNumTestedCell) = LpRamTstAlgPtr->RamTstNumberOfTestedCells;
    /* Re-initial value for Algorithm, BlockId, Number of block in Algorithm*/
    *(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgTest) = LpRamTstAlgPtr->RamTstAlgorithm;
    *(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock) = RAMTST_ZERO;
    *(RamTst_GaaGlobalAccPoint[LucCoreIndex].pNumBlockId) = LpRamTstAlgPtr->RamTstNumberOfBlocks;
    /* Initial Start Address with default Alg ID and Block ID 0 based on Alg */
    *(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress) =
        (RamTst_TestDataType *)(LpRamTstAlgPtr->LpRamTstBlockConfig[RAMTST_ZERO].RamTstStartAddress);                   /* PRQA S 0306 # JV-01 */
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)) = 
                                            (uint32)LpRamTstAlgPtr->LpRamTstBlockConfig[RAMTST_ZERO].RamTstFillPattern;
    /* Initialize the test results of configured blocks of the RAM Test */
    for (Index = RAMTST_ZERO; Index < (RamTst_NumberOfBlocksType)LpRamTstAlgPtr->RamTstNumberOfBlocks; Index++)
    {
      RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer[Index] = RAMTST_RESULT_NOT_TESTED;
    }

    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)) = RAMTST_EXECUTION_STOPPED;
    /* Initialize the over all test result */
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pOverallTestResult)) = RAMTST_RESULT_NOT_TESTED;
  }
} /* End of RamTst_Init () */
/***********************************************************************************************************************
** Function Name         : RamTst_DeInit
**
** Service ID            : 0x0c
**
** Description           : This API performs Deinitialization of RamTst Driver.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called
**                         first before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_002
** Reference ID          : RAMTST_DUD_ACT_002_ERR001, RAMTST_DUD_ACT_002_ERR002
** Reference ID          : RAMTST_DUD_ACT_002_GBL004, RAMTST_DUD_ACT_002_GBL003, RAMTST_DUD_ACT_002_GBL002
** Reference ID          : RAMTST_DUD_ACT_002_GBL001
***********************************************************************************************************************/
FUNC(void, RAMTST_PUBLIC_CODE) RamTst_DeInit(void)                                                                      /* PRQA S 1503 # JV-01 */
{
  /* Core index */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON) 
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_DEINIT_SVCID, RAMTST_E_INVALID_CORE);
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  /* Check if the Module is initialized */
  if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_DEINIT_SVCID, RAMTST_E_UNINIT);
  }
  else
  #else
  if (RAMTST_EXECUTION_UNINIT != (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  #endif
  {
    /* DeInitialize all RAM Test relevant global variables. */  
    /* Change execution status */
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)) = RAMTST_EXECUTION_UNINIT;
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) = RAMTST_ZERO;
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pNumTestedCell)) = RAMTST_ZERO;
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress)) = NULL_PTR;
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)) = RAMTST_ZERO;
  }
} /* End of RamTst_DeInit() */
#if (RAMTST_STOP_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_Stop
**
** Service ID            : 0x02
**
** Description           : The Service for stopping the RAM Test.
**
** Sync/Async            : Asynchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called
**                         first before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, RamTst_Config
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_003
** Reference ID          : RAMTST_DUD_ACT_003_ERR001, RAMTST_DUD_ACT_003_ERR002
** Reference ID          : RAMTST_DUD_ACT_003_ERR003, RAMTST_DUD_ACT_003_GBL001
***********************************************************************************************************************/
FUNC(void, RAMTST_PUBLIC_CODE) RamTst_Stop(void)                                                                        /* PRQA S 1503 # JV-01 */
{ 
  /* Pointer to the Algorithm Configuration Structure for the RAM Test */ 
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  /* Core index */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)  
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_STOP_SVCID, RAMTST_E_INVALID_CORE);
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  /* Check if RAM Test Module is initialized */
  if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */ 
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_STOP_SVCID, RAMTST_E_UNINIT);
  }
  /* Check if the "(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus))" is relevant */
  else if (RAMTST_EXECUTION_STOPPED == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */  
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_STOP_SVCID, RAMTST_E_STATUS_FAILURE);
  }
  else
  #else
  if ((RAMTST_EXECUTION_RUNNING == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
     || (RAMTST_EXECUTION_SUSPENDED == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus))))
  #endif
  {  
    LpRamTstAlgPtr = &((RamTst_Config[RAMTST_ZERO].LpRamTstAlgConfig)
                      [(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]);                         /* PRQA S 3384 # JV-01 */
    /* Reset test parameters and loop data */
    *(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock) = RAMTST_ZERO;
    *(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress) =
        (RamTst_TestDataType *)(LpRamTstAlgPtr->LpRamTstBlockConfig[RAMTST_ZERO].RamTstStartAddress);                   /* PRQA S 0306 # JV-01 */
    /* Change execution status */
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)) = RAMTST_EXECUTION_STOPPED;
  }
} /* End of RamTst_Stop () */
#endif /* End of RAMTST_STOP_API == STD_ON */
#if (RAMTST_ALLOW_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_Allow
**
** Service ID            : 0x03
**
** Description           : This Service for continuing the RAM Test after
**                         calling RamTst_Stop.
**
** Sync/Async            : Asynchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_004
** Reference ID          : RAMTST_DUD_ACT_004_ERR001, RAMTST_DUD_ACT_004_ERR002
** Reference ID          : RAMTST_DUD_ACT_004_ERR003, RAMTST_DUD_ACT_004_GBL001
***********************************************************************************************************************/
FUNC(void, RAMTST_PUBLIC_CODE) RamTst_Allow(void)                                                                       /* PRQA S 1503 # JV-01 */
{
  /* Core index */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON) 
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_ALLOW_SVCID, RAMTST_E_INVALID_CORE);
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  /* Check if RAM Test Module is initialized */
  if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */  
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_ALLOW_SVCID, RAMTST_E_UNINIT);
  }
  else if (RAMTST_EXECUTION_STOPPED != (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_ALLOW_SVCID, RAMTST_E_STATUS_FAILURE);
  }
  else
  #else
  if (RAMTST_EXECUTION_STOPPED == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  #endif
  {
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)) = RAMTST_EXECUTION_RUNNING;
  }
}
#endif /* End of RAMTST_ALLOW_API == STD_ON */
#if (RAMTST_SUSPEND_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_Suspend
**
** Service ID            : 0x0d
**
** Description           : The Service for suspending current operation of
**                         background RAM Test, until RESUME is called.
**
** Sync/Async            : Asynchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_005
** Reference ID          : RAMTST_DUD_ACT_005_ERR001, RAMTST_DUD_ACT_005_ERR002
** Reference ID          : RAMTST_DUD_ACT_005_ERR003, RAMTST_DUD_ACT_005_GBL001
***********************************************************************************************************************/
FUNC(void, RAMTST_PUBLIC_CODE) RamTst_Suspend(void)                                                                     /* PRQA S 1503 # JV-01 */
{
  /* Core index */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)  
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_SUSPEND_SVCID, RAMTST_E_INVALID_CORE);
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  /* Check if RAM Test Module is initialized */
  if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_SUSPEND_SVCID, RAMTST_E_UNINIT);
  } 
  else if (RAMTST_EXECUTION_RUNNING != (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_SUSPEND_SVCID, RAMTST_E_STATUS_FAILURE);
  }
  else
  #else
  if (RAMTST_EXECUTION_RUNNING == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  #endif
  {
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)) = RAMTST_EXECUTION_SUSPENDED;
  }
}
#endif /* End of RAMTST_SUSPEND_API == STD_ON */
#if (RAMTST_RESUME_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_Resume
**
** Service ID            : 0x0e
**
** Description           : The Service for allowing to continue the background
**                         RAM Test at the point is was suspended.
**
** Sync/Async            : Asynchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_006
** Reference ID          : RAMTST_DUD_ACT_006_ERR001, RAMTST_DUD_ACT_006_ERR002
** Reference ID          : RAMTST_DUD_ACT_006_ERR003, RAMTST_DUD_ACT_006_GBL001
***********************************************************************************************************************/
FUNC(void, RAMTST_PUBLIC_CODE) RamTst_Resume(void)                                                                      /* PRQA S 1503 # JV-01 */
{
  /* Core index */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RESUME_SVCID, RAMTST_E_INVALID_CORE);
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  /* Check if RAM Test Module is initialized */
  if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RESUME_SVCID, RAMTST_E_UNINIT);
  }
  else if (RAMTST_EXECUTION_SUSPENDED != (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RESUME_SVCID, RAMTST_E_STATUS_FAILURE);
  }
  else
  #else
  if (RAMTST_EXECUTION_SUSPENDED == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  #endif
  {
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)) = RAMTST_EXECUTION_RUNNING;
  }
}
#endif /* End of RAMTST_RESUME_API == STD_ON */
#if (RAMTST_GET_EXECUTION_STATUS_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_GetExecutionStatus
**
** Service ID            : 0x04
**
** Description           : This API return current Ram Test execution status
**                         for RamTst Driver.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : RamTst_ExecutionStatusType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_007
** Reference ID          : RAMTST_DUD_ACT_007_ERR001, RAMTST_DUD_ACT_007_ERR002
** Reference ID          : RAMTST_DUD_ACT_007_GBL001
***********************************************************************************************************************/
FUNC(RamTst_ExecutionStatusType, RAMTST_PUBLIC_CODE) RamTst_GetExecutionStatus(void)                                    /* PRQA S 1503 # JV-01 */
{
  /* Variable for return current Ram Test execution status */
  VAR(RamTst_ExecutionStatusType, AUTOMATIC) TestStatus;
  /* Core index */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  TestStatus = RAMTST_EXECUTION_UNINIT;
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_EXECUTION_STATUS_SVCID, 
                                                                                                RAMTST_E_INVALID_CORE);
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  /* Check if the Module is initialized */
  if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_EXECUTION_STATUS_SVCID, RAMTST_E_UNINIT);
  }
  else
  #endif
  {
    TestStatus = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus));
  }
  return TestStatus;
} /* End of RamTst_GetExecutionStatus() */
#endif /* End of RAMTST_GET_EXECUTION_STATUS_API == STD_ON */
#if (RAMTST_GET_TEST_RESULT_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_GetTestResult
**
** Service ID            : 0x05
**
** Description           : This API is to change the state of Core Test module
**                         to Abort.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : RamTst_TestResultType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_008
** Reference ID          : RAMTST_DUD_ACT_008_ERR001, RAMTST_DUD_ACT_008_ERR002
** Reference ID          : RAMTST_DUD_ACT_008_GBL001, RAMTST_DUD_ACT_008_GBL002
***********************************************************************************************************************/
FUNC(RamTst_TestResultType, RAMTST_PUBLIC_CODE) RamTst_GetTestResult(void)                                              /* PRQA S 1503 # JV-01 */
{
  /* Variable for return current Ram Test result */
  VAR(RamTst_TestResultType, AUTOMATIC) TestResult;
  /* Core index */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  TestResult = RAMTST_RESULT_NOT_TESTED;
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_TEST_RESULT_SVCID, RAMTST_E_INVALID_CORE);
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  /* Check if the Module is initialized */
  if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_TEST_RESULT_SVCID, RAMTST_E_UNINIT);
  }
  else
  #endif
  {
    TestResult = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pOverallTestResult));
  }
  return TestResult;
} /* End of RamTst_GetTestResult () */
#endif /* End of RAMTST_GET_TEST_RESULT_API == STD_ON */
#if (RAMTST_GET_TEST_RESULT_PER_BLOCK_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_GetTestResultPerBlock
**
** Service ID            : 0x06
**
** Description           : This API return Current test result for the
**                         specified block for RamTst Driver.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : BlockID
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : RamTst_TestResultType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint,
**                         RamTst_Config
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_009
** Reference ID          : RAMTST_DUD_ACT_009_ERR001, RAMTST_DUD_ACT_009_ERR002
** Reference ID          : RAMTST_DUD_ACT_009_ERR003
** Reference ID          : RAMTST_DUD_ACT_009_GBL001, RAMTST_DUD_ACT_009_GBL002
***********************************************************************************************************************/
FUNC(RamTst_TestResultType, RAMTST_PUBLIC_CODE)
     RamTst_GetTestResultPerBlock(VAR(RamTst_NumberOfBlocksType, AUTOMATIC) BlockID)                                    /* PRQA S 1503 # JV-01 */
{
  VAR(RamTst_TestResultType, AUTOMATIC) TestResult;
  /* Core index */
  uint8 LucCoreIndex;
  /* Get core index */
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  /* Variable used to control execution */
  VAR(Std_ReturnType, AUTOMATIC) LblStatusValue;
  /* Pointer to the Algorithm Configuration Structure for the RAM Test */
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  /* Initialize the Value */
  LblStatusValue = E_OK;
  #endif
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  TestResult = RAMTST_RESULT_NOT_TESTED;
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_TEST_RESULT_PER_BLOCK_SVCID,
                                                                                                RAMTST_E_INVALID_CORE);
    LblStatusValue = E_NOT_OK;
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  {  
    /* Get current Algorithms */
    LpRamTstAlgPtr = &(RamTst_Config[RAMTST_ZERO].
                             LpRamTstAlgConfig[(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]); /* PRQA S 3384 # JV-01 */
    /* Check if the Module is initialized */
    if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
    {
      /* Report DET Error */
      (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_TEST_RESULT_PER_BLOCK_SVCID,
                            RAMTST_E_UNINIT);
      LblStatusValue = E_NOT_OK;
    }
    /* Check if the parameter "BlockID" is out of range of algorithm */
    if ((BlockID > LpRamTstAlgPtr->RamTstNumberOfBlocks) || (RAMTST_ZERO == BlockID))
    {
      /* Report DET Error */
      (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_TEST_RESULT_PER_BLOCK_SVCID,
                            RAMTST_E_OUT_OF_RANGE);
      TestResult = RAMTST_RESULT_UNDEFINED;
      LblStatusValue = E_NOT_OK;
    }
  }
  if (E_OK == LblStatusValue)
  #endif
  {
    TestResult = RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer[BlockID - RAMTST_ONE];                        /* PRQA S 3383 # JV-01 */
  }
  return (TestResult);
} /* End of RamTst_GetTestResultPerBlock () */
#endif /* End of RAMTST_GET_TEST_RESULT_PER_BLOCK_API == STD_ON */
#if (RAMTST_GET_ALG_PARAMS_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_GetAlgParams
**
** Service ID            : 0x12
**
** Description           : This API return the ID of the current RAM Test
**                         algorithm parameter set for RamTst Driver.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : RamTst_AlgParamsIdType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_011
** Reference ID          : RAMTST_DUD_ACT_011_ERR001, RAMTST_DUD_ACT_011_ERR002
** Reference ID          : RAMTST_DUD_ACT_011_GBL001, RAMTST_DUD_ACT_011_GBL002
***********************************************************************************************************************/
FUNC(RamTst_AlgParamsIdType, RAMTST_PUBLIC_CODE) RamTst_GetAlgParams(void)                                              /* PRQA S 1503 # JV-01 */
{
  /* Variable for algorithm parameter id */
  VAR(RamTst_AlgParamsIdType, AUTOMATIC) AlgParamsId;
  /* Core index */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  /* Initialize the value */
  AlgParamsId = RAMTST_ZERO;
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_ALGORITHM_PARAMS_SVCID, 
                                                                                                RAMTST_E_INVALID_CORE);
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  /* Check if the Module is initialized */
  if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_ALGORITHM_PARAMS_SVCID, RAMTST_E_UNINIT);
  }
  else
  #endif
  {
    AlgParamsId = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId));
  }
  return AlgParamsId;
} /* End of RamTst_GetAlgParams() */
#endif /* End of RAMTST_GET_ALG_PARAMS_API == STD_ON */
#if (RAMTST_GET_TEST_ALGORITHM_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_GetTestAlgorithm
**
** Service ID            : 0x07
**
** Description           : This API return the current RAM Test algorithm.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : RamTst_AlgorithmType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_012
** Reference ID          : RAMTST_DUD_ACT_012_ERR001, RAMTST_DUD_ACT_012_ERR002
** Reference ID          : RAMTST_DUD_ACT_012_GBL001, RAMTST_DUD_ACT_012_GBL002
***********************************************************************************************************************/
FUNC(RamTst_AlgorithmType, RAMTST_PUBLIC_CODE) RamTst_GetTestAlgorithm(void)                                            /* PRQA S 1503 # JV-01 */
{
  /* Variable for return the current RAM Test algorithm */
  VAR(RamTst_AlgorithmType, AUTOMATIC) Algorithm;
  /* Core index */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  /* Initialize the value */
  Algorithm = RAMTST_ALGORITHM_UNDEFINED;
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_TEST_ALGORITHM_SVCID, RAMTST_E_INVALID_CORE);
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  /* Check if the Module is initialized */
  if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_TEST_ALGORITHM_SVCID, RAMTST_E_UNINIT);
  }
  else
  #endif
  {
    Algorithm = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgTest)) ;
  }
  return Algorithm;
} /* End of RamTst_GetTestAlgorithm() */
#endif /* End of RAMTST_GET_TEST_ALGORITHM_API == STD_ON */
#if (RAMTST_GET_NUMBER_OF_TESTED_CELLS_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_GetNumberOfTestedCells
**
** Service ID            : 0x09
**
** Description           : This API return the current number of tested cells
**                         per main-function cycle.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : RamTst_NumberOfTestedCellsType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_013
** Reference ID          : RAMTST_DUD_ACT_013_ERR001, RAMTST_DUD_ACT_013_ERR002
** Reference ID          : RAMTST_DUD_ACT_013_GBL001, RAMTST_DUD_ACT_013_GBL002
***********************************************************************************************************************/
FUNC(RamTst_NumberOfTestedCellsType, RAMTST_PUBLIC_CODE) RamTst_GetNumberOfTestedCells(void)                            /* PRQA S 1503 # JV-01 */
{
  /* Variable for return the current number of tested cells */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells;
  /* Core index */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  /* Initialize the Value */
  TestedCells = RAMTST_ZERO;
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_NUMBER_OF_TESTED_CELLS_SVCID, 
                                                                                                RAMTST_E_INVALID_CORE);
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  /* Check if the Module is initialized */
  if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_NUMBER_OF_TESTED_CELLS_SVCID,
                          RAMTST_E_UNINIT);
  }
  else
  #endif
  {
    TestedCells = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pNumTestedCell));
  }
  return TestedCells;
} /* End of RamTst_GetNumberOfTestedCells() */
#endif /* End of RAMTST_GET_NUMBER_OF_TESTED_CELLS_API == STD_ON */
#if (RAMTST_SELECT_ALG_PARAMS_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_SelectAlgParams
**
** Service ID            : 0x0b
**
** Description           : This API used to set the test algorithm and
**                         its parameter set.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : NewAlgParamsId
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, 
**                         RamTst_GaaAlgId2CoreIndex, 
**                         RamTst_Config
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_014
** Reference ID          : RAMTST_DUD_ACT_014_ERR001, RAMTST_DUD_ACT_014_ERR002, RAMTST_DUD_ACT_014_ERR003
** Reference ID          : RAMTST_DUD_ACT_014_ERR004
** Reference ID          : RAMTST_DUD_ACT_014_GBL001, RAMTST_DUD_ACT_014_GBL002, RAMTST_DUD_ACT_014_GBL003
** Reference ID          : RAMTST_DUD_ACT_014_GBL004, RAMTST_DUD_ACT_014_GBL005, RAMTST_DUD_ACT_014_GBL006
** Reference ID          : RAMTST_DUD_ACT_014_GBL007, RAMTST_DUD_ACT_014_GBL008, RAMTST_DUD_ACT_014_GBL009
***********************************************************************************************************************/
FUNC(void, RAMTST_PUBLIC_CODE) RamTst_SelectAlgParams(VAR(RamTst_AlgParamsIdType, AUTOMATIC) NewAlgParamsId)            /* PRQA S 1503 # JV-01 */
{
  /* Pointer to the Algorithm Configuration Structure for the RAM Test */
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  /* Index to the RamTst_TestResultBuffer */
  VAR(RamTst_NumberOfBlocksType, AUTOMATIC) Index;
  /* Index of core */
  uint8 LucCoreIndex;
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  /* Record status of Det report */
  VAR(Std_ReturnType, AUTOMATIC) LblStatusValue;
  /* Initial value */
  LblStatusValue = E_OK;
  #endif /* RAMTST_DEV_ERROR_DETECT == STD_ON */
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  if ((NewAlgParamsId > RAMTST_NO_OF_ALGORITHM) || (NewAlgParamsId == RAMTST_ZERO))
    {
      /* Report DET Error */
      (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_SELECT_ALGORITHM_PARAMS_SVCID,
                            RAMTST_E_OUT_OF_RANGE);
      LblStatusValue = E_NOT_OK;
    }
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  else if ((RAMTST_INVALID_CORE == LucCoreIndex) || 
                                  (RamTst_GaaAlgId2CoreIndex[NewAlgParamsId - RAMTST_ONE] != LucCoreIndex))
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_SELECT_ALGORITHM_PARAMS_SVCID, 
                                                                                                RAMTST_E_INVALID_CORE);
    LblStatusValue = E_NOT_OK;
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  {
    /* Check if the Module is initialized */
    if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
    {
      /* Report DET Error */
      (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_SELECT_ALGORITHM_PARAMS_SVCID, 
                           RAMTST_E_UNINIT);
      LblStatusValue = E_NOT_OK;
    }
    else if (RAMTST_EXECUTION_STOPPED != (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))                  /* PRQA S 2004 # JV-01 */
    {
      /* Report DET Error */
      (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_SELECT_ALGORITHM_PARAMS_SVCID,
                            RAMTST_E_STATUS_FAILURE);
      LblStatusValue = E_NOT_OK;
    } /* else do not thing*/
  }
  if (E_OK == LblStatusValue)
  #else
  if (RAMTST_EXECUTION_STOPPED == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  #endif
  {
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) = NewAlgParamsId;
    LpRamTstAlgPtr = 
     &(RamTst_Config[RAMTST_ZERO].LpRamTstAlgConfig[NewAlgParamsId - RAMTST_ONE]);                                      /* PRQA S 3383 # JV-01 */
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pNumTestedCell)) = LpRamTstAlgPtr->RamTstNumberOfTestedCells;
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgTest)) = LpRamTstAlgPtr->RamTstAlgorithm;
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pNumBlockId)) = LpRamTstAlgPtr->RamTstNumberOfBlocks;
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock)) = RAMTST_ZERO;
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress)) =
        (RamTst_TestDataType *)(LpRamTstAlgPtr->LpRamTstBlockConfig->RamTstStartAddress);                               /* PRQA S 0306 # JV-01 */
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)) = 
                                         (uint32)LpRamTstAlgPtr->LpRamTstBlockConfig->RamTstFillPattern;
    /* Initialize the test results of configured blocks of the RAM Test*/
    for (Index = RAMTST_ZERO; Index < (RamTst_NumberOfBlocksType)LpRamTstAlgPtr->RamTstNumberOfBlocks; Index++)
    {
      RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer[Index] = RAMTST_RESULT_NOT_TESTED;
    }
    /* Initialize the over all test result  */
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pOverallTestResult)) = RAMTST_RESULT_NOT_TESTED;
  }
} /* End of RamTst_SelectAlgParams  () */
#endif /* End of RAMTST_SELECT_ALG_PARAMS_API == STD_ON */
#if (RAMTST_CHANGE_NUMBER_OF_TESTED_CELLS_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_ChangeNumberOfTestedCells
**
** Service ID            : 0x08
**
** Description           : This API used to changes the current number
**                         of tested cells.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : NewNumberOfTestedCells
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, 
**                         RamTst_Config
**
** Function(s) invoked   : Det_ReportError, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_015
** Reference ID          : RAMTST_DUD_ACT_015_ERR001, RAMTST_DUD_ACT_015_ERR002, RAMTST_DUD_ACT_015_ERR003
** Reference ID          : RAMTST_DUD_ACT_015_ERR004, RAMTST_DUD_ACT_015_GBL001, RAMTST_DUD_ACT_015_GBL002
***********************************************************************************************************************/
FUNC(void, RAMTST_PUBLIC_CODE)
RamTst_ChangeNumberOfTestedCells(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) NewNumberOfTestedCells)                 /* PRQA S 1503 # JV-01 */
{
  /* Index of core */
  uint8 LucCoreIndex;
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  /* Variable used to control execution */
  VAR(Std_ReturnType, AUTOMATIC) LblStatusValue;
  /* Pointer to the Algorithm Configuration Structure for the RAM Test */
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  LblStatusValue = E_OK;
  #endif
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();

  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_CHANGE_NUMBER_OF_TESTED_CELLS_SVCID,
                                                                                               RAMTST_E_INVALID_CORE);
    LblStatusValue = E_NOT_OK;
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  {
    /* Check if the Module is initialized*/
    if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
    {
      /* Report DET Error */
      (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_CHANGE_NUMBER_OF_TESTED_CELLS_SVCID,
                            RAMTST_E_UNINIT);
      LblStatusValue = E_NOT_OK;
    }
    /* Check if the "(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus))" is relevant*/
    else if (RAMTST_EXECUTION_STOPPED != (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))                  /* PRQA S 2004 # JV-01 */
    {
      /* Report DET Error */
      (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_CHANGE_NUMBER_OF_TESTED_CELLS_SVCID,
                            RAMTST_E_STATUS_FAILURE);
      LblStatusValue = E_NOT_OK;
    } 
    LpRamTstAlgPtr =  &(RamTst_Config[RAMTST_ZERO]
                            .LpRamTstAlgConfig[(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]); /* PRQA S 3384 # JV-01 */
    /* Check if the parameter "NewNumberOfTestedCells" is out of range */
    if ((NewNumberOfTestedCells > LpRamTstAlgPtr->RamTstMaxNumberOfTestedCells) ||
        (NewNumberOfTestedCells > LpRamTstAlgPtr->RamTstExtNumberOfTestedCells) ||
        (NewNumberOfTestedCells < RamTst_Config[RAMTST_ZERO].RamTstMinNumberOfTestedCells))
    {
      /* Report DET Error */
      (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_CHANGE_NUMBER_OF_TESTED_CELLS_SVCID,
                            RAMTST_E_OUT_OF_RANGE);
      LblStatusValue = E_NOT_OK;
    }
  }
  if (E_OK == LblStatusValue)
  #else
  if (RAMTST_EXECUTION_STOPPED == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  #endif
  {
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pNumTestedCell)) = NewNumberOfTestedCells;
  }
} /* End of RamTst_ChangeNumberOfTestedCells  () */
#endif /* End of RAMTST_CHANGE_NUMBER_OF_TESTED_CELLS_API == STD_ON */
#if (RAMTST_RUN_FULL_TEST_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_RunFullTest
**
** Service ID            : 0x10
**
** Description           : This API used for executing the full RAM Test in the
**                         foreground.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, 
**                         RamTst_Config
**
** Function(s) invoked   : Det_ReportError, Dem_SetEventStatus
**                         RamTst_ChangeBlockForeGrndTest, RamTst_GetCoreIndex, RamTst_CallAlgorithm
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_016
** Reference ID          : RAMTST_DUD_ACT_016_ERR001, RAMTST_DUD_ACT_016_ERR002, RAMTST_DUD_ACT_016_ERR003
** Reference ID          : RAMTST_DUD_ACT_016_ERR004
** Reference ID          : RAMTST_DUD_ACT_016_GBL001, RAMTST_DUD_ACT_016_GBL002, RAMTST_DUD_ACT_016_GBL003
** Reference ID          : RAMTST_DUD_ACT_016_GBL004, RAMTST_DUD_ACT_016_GBL005, RAMTST_DUD_ACT_016_GBL006
** Reference ID          : RAMTST_DUD_ACT_016_GBL007
***********************************************************************************************************************/
FUNC(void, RAMTST_PUBLIC_CODE) RamTst_RunFullTest(void)                                                                 /* PRQA S 1503 # JV-01 */
{
  /* Pointer to the Algorithm Configuration Structure for the RAM Test */
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  /* Variable to store the Result of RAM Test in each cycle*/
  VAR(Std_ReturnType, AUTOMATIC) Result;
  /* Number of tested RAM cells */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) NumTestCell;
  /* Local variable record Block ID */
  VAR(RamTst_NumberOfBlocksType, AUTOMATIC) LucRamTstBlockId;
  /* Local variable record Block */
  VAR(RamTst_NumberOfBlocksType, AUTOMATIC) LucRamTstBlock;
  VAR(Std_ReturnType, AUTOMATIC) Ret;
  /* Index of core */
  uint8 LucCoreIndex;
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  VAR(Std_ReturnType, AUTOMATIC) LblStatusValue;
  #endif /* RAMTST_DEV_ERROR_DETECT == STD_ON */
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  LblStatusValue = E_OK;
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUN_FULL_TEST_SVCID, RAMTST_E_INVALID_CORE);
    LblStatusValue = E_NOT_OK;
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  /* Check if the Module is initialized*/
  if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  {
    /* Report DET Error */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUN_FULL_TEST_SVCID, RAMTST_E_UNINIT);
    LblStatusValue = E_NOT_OK;
  }
  /* Check if the "(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus))" is relevant*/
  else if (RAMTST_EXECUTION_STOPPED != (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))                    /* PRQA S 2004 # JV-01 */
  {
    /* Report DET Error */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUN_FULL_TEST_SVCID, RAMTST_E_STATUS_FAILURE);
    LblStatusValue = E_NOT_OK;
  }
  if (E_OK == LblStatusValue)
  #else
  if (RAMTST_EXECUTION_STOPPED == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
  #endif
  {
    Ret = E_NOT_OK;
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)) = RAMTST_EXECUTION_RUNNING;
    LpRamTstAlgPtr = &((RamTst_Config[RAMTST_ZERO]
                          .LpRamTstAlgConfig)[(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]);  /* PRQA S 3384 # JV-01 */
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgTest)) = LpRamTstAlgPtr->RamTstAlgorithm;
    while (E_NOT_OK == Ret)
    {
      /* Get current Block, Block ID, Cell Address */
      LucRamTstBlock = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock));
      LucRamTstBlockId = (LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstBlockId);
      NumTestCell =
          (RamTst_NumberOfTestedCellsType)(((RamTst_TestDataType *)LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock]  /* PRQA S 0306 # JV-01 */
                                    .RamTstEndAddress) - (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress))) +    /* PRQA S 0488, 3383 # JV-01, JV-01 */
                                    (RamTst_NumberOfTestedCellsType)RAMTST_ONE;
      /* Set the Test Status of the Block */
      RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer[LucRamTstBlockId - RAMTST_ONE] =                         /* PRQA S 3383 # JV-01 */
                                                                                               RAMTST_RESULT_UNDEFINED;
      (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pOverallTestResult)) = RAMTST_RESULT_UNDEFINED;
      /*Function for Calling Different Algorithm */
      Result = RamTst_CallAlgorithm(NumTestCell);
      if (E_NOT_OK == Result)
      {
        /* Set the Test Status of the Block */
        RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer[LucRamTstBlockId - RAMTST_ONE] = RAMTST_RESULT_NOT_OK; /* PRQA S 3383 # JV-01 */
        #ifdef RAMTST_RUNFL_RAM_FAILURE
        /* Report production error RAMTST_RUNFL_RAM_FAILURE */
        RAMTST_DEM_REPORT_ERROR(RAMTST_RUNFL_RAM_FAILURE, DEM_EVENT_STATUS_FAILED);
        #endif
      }
      else
      {
        /* Set TestResult Status for the Tested Block  */
          RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer[LucRamTstBlockId - RAMTST_ONE] =                     /* PRQA S 3383 # JV-01 */
              RAMTST_RESULT_OK;
      }
      Ret = RamTst_ChangeBlockForeGrndTest();
    }
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)) = RAMTST_EXECUTION_STOPPED;
  }
} /* End of RamTst_RunFullTest() */
#endif /* End of RAMTST_RUN_FULL_TEST_API == STD_ON */
#if (RAMTST_RUN_PARTIAL_TEST_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_RunPartialTest
**
** Service ID            : 0x11
**
** Description           : This API used for testing one RAM block
**                         in the foreground.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, 
**                         RamTst_Config
**
** Function(s) invoked   : Det_ReportError, Dem_SetEventStatus
**                         RamTst_CallAlgorithm, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_017
** Reference ID          : RAMTST_DUD_ACT_017_ERR001, RAMTST_DUD_ACT_017_ERR002, RAMTST_DUD_ACT_017_ERR003
** Reference ID          : RAMTST_DUD_ACT_017_ERR004, RAMTST_DUD_ACT_017_ERR005
** Reference ID          : RAMTST_DUD_ACT_017_GBL001, RAMTST_DUD_ACT_017_GBL002, RAMTST_DUD_ACT_017_GBL003
** Reference ID          : RAMTST_DUD_ACT_017_GBL004, RAMTST_DUD_ACT_017_GBL005, RAMTST_DUD_ACT_017_GBL006
** Reference ID          : RAMTST_DUD_ACT_017_GBL007
***********************************************************************************************************************/
FUNC(void, RAMTST_PUBLIC_CODE) RamTst_RunPartialTest(VAR(RamTst_NumberOfBlocksType, AUTOMATIC) BlockId)                 /* PRQA S 1503 # JV-01 */
{
  /* Temporary variable to hold state of execution status */
  VAR(RamTst_ExecutionStatusType, AUTOMATIC) RamTst_TempExecutionStatus;
  /* Temporary variable to hold current block ID */
  VAR(RamTst_NumberOfBlocksType, AUTOMATIC) RamTst_TempBlockId;
  /* Temporary variable to hold current test cell Address */
  volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) RamTst_TempGpCellAddress;                             /* PRQA S 3432 # JV-01 */
  /* Temporary variable to hold current algorithm */
  VAR(RamTst_AlgorithmType, RAMTST_VAR) RamTst_TempAlgorithm;
  /* Temporary variable to hold current fill pattern */
  VAR(uint32, RAMTST_VAR) RamTst_TempFillPattern;
  /* Pointer to the Algorithm Configuration Structure for the RAM Test */
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  /* Number of tested RAM cells */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) NumTestCell;
  /* Variable to store the Result of RAM Test in each cycle*/
  VAR(Std_ReturnType, AUTOMATIC) Result;
  /* Index used for finding block ID */
  VAR(uint16, AUTOMATIC) Index;
  /* Indicate that block ID is found */
  VAR(uint8, AUTOMATIC) BlockIdFound;
  /* Index of core */
  uint8 LucCoreIndex;
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  /* Variable used to control execution */
  VAR(Std_ReturnType, AUTOMATIC) LblStatusValue;
  #endif /* RAMTST_DEV_ERROR_DETECT == STD_ON */
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  /* Initial value */
  LblStatusValue = E_OK;
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  /* Check invalid core for init API */
  if(RAMTST_INVALID_CORE == LucCoreIndex)
  {
    /* Report to DET */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUN_PARTIAL_TEST_SVCID, RAMTST_E_INVALID_CORE);
    LblStatusValue = E_NOT_OK;
  }
  else
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  {
    /* Check if the Module is initialized*/
    if (RAMTST_EXECUTION_UNINIT == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))
    {
      /* Report DET Error */
      (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUN_PARTIAL_TEST_SVCID, RAMTST_E_UNINIT);
      LblStatusValue = E_NOT_OK;
    }
    else if (RAMTST_EXECUTION_RUNNING == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))                  /* PRQA S 2004 # JV-01 */
    {
      /* Report DET Error */
      (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUN_PARTIAL_TEST_SVCID,
                            RAMTST_E_STATUS_FAILURE);
      LblStatusValue = E_NOT_OK;
    }
  #endif  /* RAMTST_DEV_ERROR_DETECT == STD_ON */
    LpRamTstAlgPtr = &((RamTst_Config[RAMTST_ZERO]
                          .LpRamTstAlgConfig)[(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]);  /* PRQA S 3384 # JV-01 */
    #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
    /* Check if the parameter "BlockId" is out of range */
    if ((BlockId > LpRamTstAlgPtr->RamTstNumberOfBlocks) || (RAMTST_ZERO == BlockId))
    {
      /* Report DET Error */
      (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_RUN_PARTIAL_TEST_SVCID, RAMTST_E_OUT_OF_RANGE);
      LblStatusValue = E_NOT_OK;
    }
  }
  if (E_OK == LblStatusValue)
    #else
  if ((RAMTST_EXECUTION_STOPPED == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus))) 
      || (RAMTST_EXECUTION_SUSPENDED == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus))))
    #endif /* RAMTST_DEV_ERROR_DETECT == STD_ON */
  {
    RamTst_TempExecutionStatus = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus));
    /* Save current test state and test loop when test is suspended */
    RamTst_TempBlockId = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock));
    RamTst_TempFillPattern = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern));
    RamTst_TempGpCellAddress = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress));
    RamTst_TempAlgorithm = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgTest));
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)) = RAMTST_EXECUTION_RUNNING;
    BlockIdFound = RAMTST_FALSE;
    for (Index = RAMTST_ZERO; (Index < LpRamTstAlgPtr->RamTstNumberOfBlocks) &&
                              (BlockIdFound == RAMTST_FALSE); Index++)
    {
      if (LpRamTstAlgPtr->LpRamTstBlockConfig[Index].RamTstBlockId == BlockId)
      {
        BlockId = Index;                                                                                                /* PRQA S 1338 # JV-01 */
        (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock)) = BlockId;
        (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)) = 
                                                (uint32)LpRamTstAlgPtr->LpRamTstBlockConfig[BlockId].RamTstFillPattern;
        BlockIdFound = RAMTST_TRUE;
      }
    }
    if (RAMTST_TRUE == BlockIdFound)
    {
      /* Get start address of block id */
      (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress)) = 
                            (RamTst_TestDataType *)(LpRamTstAlgPtr->LpRamTstBlockConfig[BlockId].RamTstStartAddress);   /* PRQA S 0306 # JV-01 */
      /* Initial value of Cell Address */
      (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgTest)) = LpRamTstAlgPtr->RamTstAlgorithm;
      NumTestCell =
          (RamTst_NumberOfTestedCellsType)(((RamTst_TestDataType *)LpRamTstAlgPtr->LpRamTstBlockConfig[BlockId]         /* PRQA S 0306 # JV-01 */
                              .RamTstEndAddress) - (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress))) +          /* PRQA S 0488, 3383 # JV-01, JV-01 */
                              (RamTst_NumberOfTestedCellsType) RAMTST_ONE;
      RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer[(LpRamTstAlgPtr->LpRamTstBlockConfig
          [(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock))].RamTstBlockId) - RAMTST_ONE] = RAMTST_RESULT_UNDEFINED;  /* PRQA S 3384 # JV-01 */
      Result = RamTst_CallAlgorithm(NumTestCell);
      if (E_NOT_OK == Result)
      {
        /* Set the Test Status of the Block */
        RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer[
          (LpRamTstAlgPtr->LpRamTstBlockConfig[BlockId].RamTstBlockId) - RAMTST_ONE] = RAMTST_RESULT_NOT_OK;            /* PRQA S 3383 # JV-01 */
        (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pOverallTestResult)) = RAMTST_RESULT_NOT_OK;
        #ifdef RAMTST_PART_RAM_FAILURE
        /* Report production error RAMTST_PART_RAM_FAILURE */
        RAMTST_DEM_REPORT_ERROR(RAMTST_PART_RAM_FAILURE, DEM_EVENT_STATUS_FAILED);
        #endif
      }
      else
      {
        /* Set TestResult Status for the Tested Block  */
        RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer
                      [(LpRamTstAlgPtr->LpRamTstBlockConfig[BlockId].RamTstBlockId) - RAMTST_ONE] = RAMTST_RESULT_OK;   /* PRQA S 3383 # JV-01 */
      }
      /* Restore current test state and test loop when test is suspended */
      (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock)) = RamTst_TempBlockId;
      (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)) = RamTst_TempFillPattern;
      (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress)) = RamTst_TempGpCellAddress;
      (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgTest)) = RamTst_TempAlgorithm;
      (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)) = RamTst_TempExecutionStatus;
    }
  }
} /* End of RamTst_RunPartialTest() */
#endif /* End of RAMTST_RUN_PARTIAL_TEST_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : RamTst_MainFunction
**
** Service ID            : 0x01
**
** Description           : Scheduled function for executing the RAM Test
**                         in the background.
**
** Sync/Async            : -
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, 
**                         RamTst_Config
**
** Function(s) invoked   : Dem_SetEventStatus
**                         RamTst_ChangeBlockBackGrndTest, RamTst_GetCoreIndex, RamTst_CallAlgorithm
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_018
** Reference ID          : RAMTST_DUD_ACT_018_ERR001
** Reference ID          : RAMTST_DUD_ACT_018_GBL001, RAMTST_DUD_ACT_018_GBL002, RAMTST_DUD_ACT_018_GBL003
** Reference ID          : RAMTST_DUD_ACT_018_GBL004, RAMTST_DUD_ACT_018_GBL005, RAMTST_DUD_ACT_018_GBL006
** Reference ID          : RAMTST_DUD_ACT_018_GBL007
***********************************************************************************************************************/
FUNC(void, RAMTST_PUBLIC_CODE) RamTst_MainFunction(void)                                                                /* PRQA S 1503 # JV-01 */
{
  /* Pointer to the Algorithm Configuration Structure for the RAM Test */
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  /* Local variable record Block ID */
  VAR(RamTst_NumberOfBlocksType, AUTOMATIC) LucRamTstBlockId;
  /* Variable to store the Result of RAM Test in each cycle */
  VAR(Std_ReturnType, AUTOMATIC) Result;
  /* Number of tested RAM cells */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) NumTestCell;
  /* Indicate Cell Address */
  volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpRamTstCellAddress;                                  /* PRQA S 3432 # JV-01 */
  /* Index to the block */
  VAR(RamTst_NumberOfBlocksType, RAMTST_VAR_INIT) LucRamTstBlock;
  /* Index of core */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  /* check invalid core*/
  if(RAMTST_INVALID_CORE == LucCoreIndex)                                                                               /* PRQA S 2996, 2992 # JV-01, JV-01 */
  {
    /* Do not thing*/
  }
  else if (RAMTST_EXECUTION_RUNNING == (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pExecutionStatus)))                    /* PRQA S 2004 # JV-01 */
  {
    LucRamTstBlock = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock));
    LpRamTstCellAddress = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress));
    /* Select current algorithm  */
    LpRamTstAlgPtr = &((RamTst_Config[RAMTST_ZERO]
                          .LpRamTstAlgConfig)[(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]);  /* PRQA S 3384 # JV-01 */
    /* Record current block ID */
    LucRamTstBlockId =  (LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstBlockId);
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgTest)) = LpRamTstAlgPtr->RamTstAlgorithm;
    if (((RamTst_NumberOfTestedCellsType)(((RamTst_TestDataType *)(LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock]  /* PRQA S 0306 # JV-01 */
            .RamTstEndAddress)) - LpRamTstCellAddress)) < (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pNumTestedCell)))   /* PRQA S 0488 # JV-01 */
    {
      NumTestCell =
          (RamTst_NumberOfTestedCellsType)((RamTst_TestDataType *)(LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock]  /* PRQA S 0306 # JV-01 */
                               .RamTstEndAddress) - LpRamTstCellAddress) + (RamTst_NumberOfTestedCellsType)RAMTST_ONE;  /* PRQA S 0488, 3383 # JV-01, JV-01 */
    }
    else
    {
      NumTestCell = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pNumTestedCell));
    }
    RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer[ LucRamTstBlockId - RAMTST_ONE] = RAMTST_RESULT_UNDEFINED; /* PRQA S 3383 # JV-01 */
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pOverallTestResult)) = RAMTST_RESULT_UNDEFINED;
    Result = RamTst_CallAlgorithm(NumTestCell);
    if (E_NOT_OK == Result)
    {
      /* Set the Test Status of the Block */
      RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer[LucRamTstBlockId - RAMTST_ONE] = RAMTST_RESULT_NOT_OK;   /* PRQA S 3383 # JV-01 */
      #ifdef RAMTST_MAIN_RAM_FAILURE
      /* Report production error RAMTST_MAIN_RAM_FAILURE */
      RAMTST_DEM_REPORT_ERROR(RAMTST_MAIN_RAM_FAILURE, DEM_EVENT_STATUS_FAILED);
      #endif
      if (NULL_PTR != RamTst_Config[RAMTST_ZERO].RamTstErrorNotification)
      {
        RamTst_Config[RAMTST_ZERO].RamTstErrorNotification();
      }
      LpRamTstCellAddress = (RamTst_TestDataType *)(LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].                /* PRQA S 0306 # JV-01 */ 
                                                                               RamTstEndAddress + (uint32)RAMTST_ONE);
    }
    else
    {
      LpRamTstCellAddress = LpRamTstCellAddress + NumTestCell;                                                          /* PRQA S 0488 # JV-01 */
      /* Set TestResult Status for the Tested Block  */
      if (((uint32)LpRamTstCellAddress) > LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstEndAddress)         /* PRQA S 0303 # JV-01 */
      {
        /* Set the Test Status of the Block */
        RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer[LucRamTstBlockId - RAMTST_ONE] = RAMTST_RESULT_OK;     /* PRQA S 3383 # JV-01 */
      }
    }
    /* Update current test location to GpCellAddress */
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress)) = LpRamTstCellAddress;
    if (((uint32)LpRamTstCellAddress) > LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstEndAddress)           /* PRQA S 0303 # JV-01 */
    {
      RamTst_ChangeBlockBackGrndTest();
    }
  } /* Else no action*/
} /* End of RamTst_MainFunction () */
/* End of RamTst Section Code */
#define RAMTST_STOP_SEC_PUBLIC_CODE
#include "RamTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */

#define RAMTST_START_SEC_PRIVATE_CODE
#include "RamTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */
#if (STD_ON == RAMTST_CHECKERBOARD_TEST_SELECTED)
/***********************************************************************************************************************
** Function Name         : RamTst_CheckerAlgorithm
**
** Service ID            : NA
**
** Description           : Function for RAM testing using the CheckerBoard
**                         Algorithm.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : TestedCellNumber
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, 
**                         RamTst_Config
**
** Function(s) invoked   : RamTst_SaveData, RamTst_GetCoreIndex
**                         RamTst_FillData, RamTst_RestoreData
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_019
** Reference ID          : RAMTST_DUD_ACT_019_GBL001, RAMTST_DUD_ACT_019_GBL002, RAMTST_DUD_ACT_019_GBL003
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_CheckerAlgorithm(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber)
{
  /* Value to check the cell*/
  VAR(RamTst_TestDataType, AUTOMATIC) value;
  /* Variable for check the Index */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Index;
  /* Testrun needed for the algorithm */
  VAR(uint8, AUTOMATIC) TestRun;
  /* Return value */
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  volatile  P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress;                                       /* PRQA S 3432 # JV-01 */
  /* Index of core */
  uint8 LucCoreIndex;
  /* Local variable record Block */
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  VAR(RamTst_NumberOfBlocksType, AUTOMATIC) LucRamTstBlock;
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  #endif
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  /* Initialize the block value */
  LucRamTstBlock = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock));
  LpRamTstAlgPtr = &((RamTst_Config[RAMTST_ZERO]
                          .LpRamTstAlgConfig)[(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]);  /* PRQA S 3384 # JV-01 */
  #endif
  /* Initialize the Return value */
  ReturnVal = E_OK;
  /* Load RamTst_GpCellAddress to LpCellAddress */
  LpCellAddress = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress));
  /* Load RAMTST_CHECKERVALUE to value */
  value = (RamTst_TestDataType)RAMTST_CHECKERVALUE;
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  if (RAMTST_NON_DESTRUCTIVE == LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstTestPolicy)
  {
    RamTst_SaveData(RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestBufferAddress, TestedCellNumber);
  }
  #endif
  /* write 0 and 1 in consecutive locations */
  for (TestRun = RAMTST_ZERO; (TestRun < RAMTST_TWO) && (E_OK == ReturnVal); TestRun++)
  {
    /* write 0 and 1 in consecutive locations */
    for (Index = RAMTST_ZERO; Index < TestedCellNumber; Index++)
    {
      *(LpCellAddress + Index) = value;                                                                                 /* PRQA S 0488 # JV-01 */
      value = ~value;
    }
    /* Check whether the number of tested cell is odd or even */
    if (RAMTST_ZERO != (((uint8)(TestedCellNumber)) & (uint8)RAMTST_ONE))
    {
      value = ~value;
    }
    /* Read 0 and 1 in consecutive locations */
    for (Index = RAMTST_ZERO; (Index < TestedCellNumber) && (E_OK == ReturnVal); Index++)
    {
      /* Check whether the data are correct */
      if (*(LpCellAddress + Index) != value)                                                                            /* PRQA S 0488 # JV-01 */
      {
        /* Returning E_NOT_OK */
        ReturnVal = E_NOT_OK;
      }
      value = ~value;
    }
    value = (RamTst_TestDataType)~RAMTST_CHECKERVALUE;
  }
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  if (RAMTST_NON_DESTRUCTIVE == LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstTestPolicy)
  {
    RamTst_RestoreData(RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestBufferAddress, TestedCellNumber,
                      LpCellAddress);
  }
  else
  {
    RamTst_FillData((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)), TestedCellNumber, LpCellAddress);
  }
  #else
  RamTst_FillData((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)), TestedCellNumber, LpCellAddress);
  #endif
  return ReturnVal;
} /* End of RamTst_CheckerAlgorithm () */
#endif /* End of STD_ON == RAMTST_CHECKERBOARD_TEST_SELECTED */
#if (STD_ON == RAMTST_GALPAT_TEST_SELECTED)
/***********************************************************************************************************************
** Function Name         : RamTst_GalpatAlgorithm
**
** Service ID            : NA
**
** Description           : Function for RAM testing using the Galpat Algorithm.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : TestedCellNumber
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, 
**                         RamTst_Config
**
** Function(s) invoked   : RamTst_SaveData, RamTst_InitializeCell,
**                         RamTst_FillData, RamTst_GetCoreIndex, RamTst_RestoreData
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_020
** Reference ID          : RAMTST_DUD_ACT_020_GBL001, RAMTST_DUD_ACT_020_GBL002, RAMTST_DUD_ACT_020_GBL003
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_GalpatAlgorithm(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber)
{
  /* Index of the cells*/
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Cellnumber;
  /* Cell to be tested*/
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) BaseCell;
  /* Testrun needed for the algorithm*/
  VAR(uint8, AUTOMATIC) TestRun;
  /* Bit to be tested in the cell*/
  VAR(uint8, AUTOMATIC) BaseBit;
  /* Total number of bits */
  VAR(uint32, AUTOMATIC) Totalbits;
  /* Bit numbering*/
  VAR(uint32, AUTOMATIC) Index;
  /* BackGroundVariable */
  VAR(RamTst_TestDataType, AUTOMATIC) BackGroundVariable;
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress;                                        /* PRQA S 3432 # JV-01 */
  /* Index of core */ 
  uint8 LucCoreIndex;
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  /* Local variable record Block */
  VAR(RamTst_NumberOfBlocksType, AUTOMATIC) LucRamTstBlock;
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  #endif
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  /* Value of block */
  LucRamTstBlock = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock)) ;
  LpRamTstAlgPtr = &((RamTst_Config[RAMTST_ZERO]
                           .LpRamTstAlgConfig)[(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]); /* PRQA S 3384 # JV-01 */
  #endif
  /* Initialize the Return value */
  ReturnVal = E_OK;
  /* Initialize the BackGroundVariable */
  BackGroundVariable = RAMTST_ZERO;
  LpCellAddress = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress));
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  if (RAMTST_NON_DESTRUCTIVE == LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstTestPolicy)
  {
    RamTst_SaveData(RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestBufferAddress, TestedCellNumber);
  }
  #endif
  /* Load Total number of bits */
  Totalbits = (uint32)TestedCellNumber << RAMTST_CELL_DIVIDER;
  for (TestRun = RAMTST_ZERO; (TestRun < RAMTST_TWO) && (E_OK == ReturnVal); TestRun++)
  {
    /* Initialize the tested cells with BackGroundVariable  */
    RamTst_InitializeCell(BackGroundVariable, TestedCellNumber, LpCellAddress);
    /* Select the base bit to be tested in the ascending order. (LSB to MSB) */
    for (Index = RAMTST_ZERO; (Index < Totalbits) && (E_OK == ReturnVal); Index++)
    {
      /* Loading BaseCell Value */
      BaseCell = (RamTst_NumberOfTestedCellsType)(Index >> RAMTST_CELL_DIVIDER);
      /* Loading BaseBit Value */
      BaseBit = (uint8)(Index & (RAM_TEST_DATA_TYPE - RAMTST_ONE));
      /* Invert the base bit */
      RAMTST_INVERT_BITX(*(LpCellAddress + BaseCell), BaseBit, RamTst_TestDataType);                                    /* PRQA S 0488, 3464 # JV-01, JV-01 */
      /* Read and check all other bits in the tested cells (LSB to MSB) */
      for (Cellnumber = RAMTST_ZERO; (Cellnumber < TestedCellNumber) && (E_OK == ReturnVal); Cellnumber++)
      {
        /* Read and Check the content of all other bits in each of tested cells,
        * followed by verification of the base bit each time
        */
        if ((Cellnumber != BaseCell) && (*(LpCellAddress + Cellnumber) != BackGroundVariable))                          /* PRQA S 0488 # JV-01 */
        {
          ReturnVal = E_NOT_OK;
        }
        if (*(LpCellAddress + BaseCell) != (BackGroundVariable ^ (((uint32)(RAMTST_ONE)) << BaseBit)))                  /* PRQA S 0488 # JV-01 */
        {
          ReturnVal = E_NOT_OK;
        }
      }
      /* Re-invert the base bit */
      RAMTST_INVERT_BITX(*(LpCellAddress + BaseCell), BaseBit, RamTst_TestDataType);                                    /* PRQA S 0488, 3464 # JV-01, JV-01 */
    }
    BackGroundVariable = ~BackGroundVariable;
  }
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  if (RAMTST_NON_DESTRUCTIVE == LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstTestPolicy)
  {
    RamTst_RestoreData(RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestBufferAddress, TestedCellNumber,
                      LpCellAddress);
  }
  else
  {
    RamTst_FillData((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)), TestedCellNumber, LpCellAddress);
  }
  #else
  RamTst_FillData((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)), TestedCellNumber, LpCellAddress);
  #endif
  return ReturnVal;
} /* End of Galpat_Algorithm */
#endif /*End of  STD_ON == RAMTST_GALPAT_TEST_SELECTED */
#if (STD_ON == RAMTST_WALK_PATH_TEST_SELECTED)
/***********************************************************************************************************************
** Function Name         : RamTst_WalkPathAlgorithm
**
** Service ID            : NA
**
** Description           : Function for RAM testing using the WalkPath
**                         Algorithm.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : TestedCellNumber
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, 
**                         RamTst_Config
**
** Function(s) invoked   : RamTst_SaveData, RamTst_InitializeCell,
**                         RamTst_FillData, RamTst_RestoreData, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_021
** Reference ID          : RAMTST_DUD_ACT_021_GBL001, RAMTST_DUD_ACT_021_GBL002, RAMTST_DUD_ACT_021_GBL003
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_WalkPathAlgorithm(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber)
{
  /* Index of the cells */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Cellnumber;
  /* Cell to be tested */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) BaseCell;
  /* Testrun needed for the algorithm */
  VAR(uint8, AUTOMATIC) TestRun;
  /* Bit to be tested in the cell */
  VAR(uint8, AUTOMATIC) BaseBit;
  /* Total number of bits */
  VAR(uint32, AUTOMATIC) Totalbits;
  /* Bit numbering */
  VAR(uint32, AUTOMATIC) Index;
  /* Initialize the tested cells with value 0 or 1 */
  VAR(RamTst_TestDataType, AUTOMATIC) BackGroundVariable;
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress;                                        /* PRQA S 3432 # JV-01 */
  /* Index of core */  
  uint8 LucCoreIndex;
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  /* Index to the block */
  VAR(RamTst_NumberOfBlocksType, RAMTST_VAR_INIT) LucRamTstBlock;
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  #endif
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  /* Value of block ID */
  LucRamTstBlock = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock));
  LpRamTstAlgPtr = &((RamTst_Config[RAMTST_ZERO]
                           .LpRamTstAlgConfig)[(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]); /* PRQA S 3384 # JV-01 */
  #endif
  /* Initialize the Return value */
  ReturnVal = E_OK;
  /* Initialize the BackGroundVariable */
  BackGroundVariable = RAMTST_ZERO;
  LpCellAddress = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress));
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  if (RAMTST_NON_DESTRUCTIVE == LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstTestPolicy)
  {
    RamTst_SaveData(RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestBufferAddress, TestedCellNumber);
  }
  #endif
  Totalbits = (uint32)TestedCellNumber << RAMTST_CELL_DIVIDER;
  for (TestRun = RAMTST_ZERO; (TestRun < RAMTST_TWO) && (E_OK == ReturnVal); TestRun++)
  {
    /* Initialize the tested cells with BackGroundVariable */
    RamTst_InitializeCell(BackGroundVariable, TestedCellNumber, LpCellAddress);
    /* Select the base bit to be tested in the ascending order. (LSB to MSB) */
    for (Index = RAMTST_ZERO; (Index < Totalbits) && (E_OK == ReturnVal); Index++)
    {
      BaseCell = (RamTst_NumberOfTestedCellsType)(Index >> RAMTST_CELL_DIVIDER);
      BaseBit = (uint8)(Index & (RAM_TEST_DATA_TYPE - RAMTST_ONE));
      /* Invert the base bit */
      RAMTST_INVERT_BITX(*(LpCellAddress + BaseCell), BaseBit, RamTst_TestDataType);                                    /* PRQA S 0488, 3464 # JV-01, JV-01 */
      /* Read and check all other bits in the tested cells (LSB to MSB) */
      for (Cellnumber = RAMTST_ZERO; (Cellnumber < TestedCellNumber) && (E_OK == ReturnVal); Cellnumber++)
      {
        /* Check for the base cell */
        if ((Cellnumber == BaseCell) && 
            (*(LpCellAddress + BaseCell) != (BackGroundVariable ^ (((uint32)(RAMTST_ONE)) << BaseBit))))                /* PRQA S 0488 # JV-01 */
        {
          ReturnVal = E_NOT_OK;
        }
        /* Check the content of all other cells excluding the base cell */
        if ((*(LpCellAddress + Cellnumber) != BackGroundVariable) && (Cellnumber != BaseCell))                          /* PRQA S 0488 # JV-01 */
        {
          ReturnVal = E_NOT_OK;
        }
      }
      /* Re-invert the base cell */
      RAMTST_INVERT_BITX(*(LpCellAddress + BaseCell), BaseBit, RamTst_TestDataType);                                    /* PRQA S 0488, 3464 # JV-01, JV-01 */
    }
    BackGroundVariable = ~BackGroundVariable;
  }
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  if (RAMTST_NON_DESTRUCTIVE == LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstTestPolicy)
  {
    RamTst_RestoreData(RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestBufferAddress, TestedCellNumber,
                      LpCellAddress);
  }
  else
  {
    RamTst_FillData((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)), TestedCellNumber, LpCellAddress);
  }
  #else
  RamTst_FillData((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)), TestedCellNumber, LpCellAddress);
  #endif
  return ReturnVal;
} /* End of RamTst_WalkPathAlgorithm */
#endif /* End of STD_ON == RAMTST_WALK_PATH_TEST_SELECTED */
#if (STD_ON == RAMTST_MARCH_TEST_SELECTED)
/***********************************************************************************************************************
** Function Name         : RamTst_MarchAlgorithm
**
** Service ID            : NA
**
** Description           : Function for RAM testing using the March Algorithm.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : TestedCellNumber
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, 
**                         RamTst_Config
**
** Function(s) invoked   : RamTst_SaveData, RamTst_InitializeCell,
**                         RamTst_RWAscend, RamTst_RWDescend,
**                         RamTst_FillData, RamTst_RestoreData, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_022
** Reference ID          : RAMTST_DUD_ACT_022_GBL001, RAMTST_DUD_ACT_022_GBL002
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_MarchAlgorithm(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber)
{
  /* Testrun needed for the algorithm*/
  VAR(uint8, AUTOMATIC) TestRun;
  /* Total number of bits */
  VAR(uint32, AUTOMATIC) Totalbits;
  /* check for the bit*/
  VAR(uint8, AUTOMATIC) MarchCheckVariable;
  /* Initialize the tested cells with value 0 or 1 */
  VAR(RamTst_TestDataType, AUTOMATIC) BackGroundVariable;
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress;                                        /* PRQA S 3432 # JV-01 */
  /* Index of core */
  uint8 LucCoreIndex;
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  /* Index to the block */
  VAR(RamTst_NumberOfBlocksType, RAMTST_VAR_INIT) LucRamTstBlock;
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  #endif
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  /* Value of block */
  LucRamTstBlock = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock));
  LpRamTstAlgPtr = &((RamTst_Config[RAMTST_ZERO]
                           .LpRamTstAlgConfig)[(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]); /* PRQA S 3384 # JV-01 */
  #endif
  /* Initialize the Return value */
  ReturnVal = E_OK;
  /* Initialize the BackGroundVariable */
  BackGroundVariable = RAMTST_ZERO;
  /* Initialize the MarchCheckVariable */
  MarchCheckVariable = RAMTST_ZERO;
  LpCellAddress = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress));
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  if (RAMTST_NON_DESTRUCTIVE == LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstTestPolicy)
  {
    RamTst_SaveData(RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestBufferAddress, TestedCellNumber);
  }
  #endif
  Totalbits = (uint32)TestedCellNumber << RAMTST_CELL_DIVIDER;
  for (TestRun = RAMTST_ZERO; (TestRun < RAMTST_TWO) && (E_OK == ReturnVal); TestRun++)
  {
    /* Initialize the tested cells with BackGroundVariable */
    RamTst_InitializeCell(BackGroundVariable, TestedCellNumber, LpCellAddress);
    /* Read, check and invert each bit in ascending order (LSB to MSB) */
    ReturnVal = RamTst_RWAscend(MarchCheckVariable, Totalbits, LpCellAddress);
    if (E_OK == ReturnVal)
    {
      MarchCheckVariable = MarchCheckVariable ^ RAMTST_ONE;
      /* Read, check and invert each bit in descending order (MSB to LSB) */
      ReturnVal = RamTst_RWDescend(MarchCheckVariable, Totalbits, LpCellAddress);
    }
    /* Change the Initializing value */
    BackGroundVariable = ~BackGroundVariable;
  }
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  if (RAMTST_NON_DESTRUCTIVE == LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstTestPolicy)
  {
    RamTst_RestoreData(RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestBufferAddress, TestedCellNumber,
                      LpCellAddress);
  }
  else
  {
    RamTst_FillData((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)), TestedCellNumber, LpCellAddress);
  }
  #else
  RamTst_FillData((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)), TestedCellNumber, LpCellAddress);
  #endif
  return ReturnVal;
} /* End of RamTst_MarchAlgorithm */
#endif /* End of STD_ON == RAMTST_MARCH_TEST_SELECTED */
#if (STD_ON == RAMTST_TRANSP_GALPAT_TEST_SELECTED)
/***********************************************************************************************************************
** Function Name         : RamTst_TranspGalpatAlgorithm
**
** Service ID            : NA
**
** Description           : Function for RAM testing using the
**                         Transparent_Galpat Algorithm.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : TestedCellNumber
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, 
**                         RamTst_Config
**
** Function(s) invoked   : RamTst_SaveData, RamTst_RestoreData,
**                         RamTst_FillData, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_024
** Reference ID          : RAMTST_DUD_ACT_024_GBL001, RAMTST_DUD_ACT_024_GBL002, RAMTST_DUD_ACT_024_GBL003
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_TranspGalpatAlgorithm(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber)
{
  /* Testrun needed for the algorithm*/
  VAR(uint8, AUTOMATIC) TestRun;
  /* Index of the cells */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) BaseCell;
  /* Cell Count */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Count;
  /* Bit to be tested in the cell */
  VAR(uint8, AUTOMATIC) BaseBit;
  /* Total number of bits */
  VAR(uint32, AUTOMATIC) Totalbits;
  /* Bit Index */
  VAR(uint32, AUTOMATIC) Index;
  /* CRC for the tested cells */
  VAR(uint16, AUTOMATIC)
  Signature[RAMTST_THREE] = {RAMTST_CRC_INIT_VALUE, RAMTST_CRC_INIT_VALUE, RAMTST_CRC_INIT_VALUE};
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  /* Initialize the tested cells with value 0 or 1 */
  VAR(RamTst_TestDataType, AUTOMATIC) BufferCell;
  volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress;                                        /* PRQA S 3432 # JV-01 */
   /* Index of core */
  uint8 LucCoreIndex;
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  /* Index to the block */
  VAR(RamTst_NumberOfBlocksType, RAMTST_VAR_INIT) LucRamTstBlock;
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  #endif
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  /* Value of block ID */
  LucRamTstBlock = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock));
  LpRamTstAlgPtr = &((RamTst_Config[RAMTST_ZERO]
                           .LpRamTstAlgConfig)[(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]); /* PRQA S 3384 # JV-01 */
  #endif
  /* Initialize the Return value */
  ReturnVal = E_OK;
  /* Initialize the BufferCell */
  BufferCell = RAMTST_ZERO;
  LpCellAddress = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress));
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  if (RAMTST_NON_DESTRUCTIVE == LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstTestPolicy)
  {
    RamTst_SaveData(RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestBufferAddress, TestedCellNumber);
  }
  #endif
  Totalbits = (uint32)TestedCellNumber << RAMTST_CELL_DIVIDER;
  /* Select the base bit to be tested in the ascending order. (LSB to MSB)*/
  for (Index = RAMTST_ZERO; Index < Totalbits; Index++)
  {
    BaseCell = (RamTst_NumberOfTestedCellsType)(Index >> RAMTST_CELL_DIVIDER);
    BaseBit = (uint8)(Index & (RAM_TEST_DATA_TYPE - RAMTST_ONE));
    for (TestRun = RAMTST_ZERO; ((TestRun < RAMTST_THREE) && (E_OK == ReturnVal)); TestRun++)
    {
      /* Calculate the Signature*/
      for (Count = RAMTST_ZERO; Count < TestedCellNumber; Count++)
      {
        /* Uses Fast Table based method */
        if (Count == BaseCell)
        {
          BufferCell = *(LpCellAddress + BaseCell);                                                                     /* PRQA S 0488 # JV-01 */
          *(LpCellAddress + BaseCell) = ((*(LpCellAddress + BaseCell)) &                                                /* PRQA S 0488 # JV-01 */
                                        (~(((RamTst_TestDataType)(RAMTST_ONE)) << BaseBit)));
        }
        /* Calculate the CRC using CRC lookup Table */
        Signature[TestRun] = (uint16)((Signature[TestRun] >> RAMTST_EIGHT) ^
                                      RamTst_CRC[(uint8)(Signature[TestRun]) ^ (uint8)(*(LpCellAddress + Count))]);     /* PRQA S 0488 # JV-01 */
      }
      *(LpCellAddress + BaseCell) = BufferCell;                                                                         /* PRQA S 0488 # JV-01 */
      /* Invert the base bit*/
      RAMTST_INVERT_BITX(*(LpCellAddress + BaseCell), BaseBit, RamTst_TestDataType);                                    /* PRQA S 0488, 3464 # JV-01, JV-01 */
      if ((TestRun > RAMTST_ZERO) && (Signature[RAMTST_ZERO] != Signature[TestRun]))
      {
        ReturnVal = E_NOT_OK;
      }
    }
    RAMTST_INVERT_BITX(*(LpCellAddress + BaseCell), BaseBit, RamTst_TestDataType);                                      /* PRQA S 0488, 3464 # JV-01, JV-01 */
  }
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  if (RAMTST_NON_DESTRUCTIVE == LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstTestPolicy)
  {
    RamTst_RestoreData(RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestBufferAddress, TestedCellNumber,
                      LpCellAddress);
  }
  else
  {
    RamTst_FillData((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)), TestedCellNumber, LpCellAddress);
  }
  #else
  RamTst_FillData((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)), TestedCellNumber, LpCellAddress);
  #endif
  return ReturnVal;
} /* End of RamTst_TranspGalpatAlgorithm */
#endif /* End of STD_ON == RAMTST_TRANSP_GALPAT_TEST_SELECTED */
#if (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED)
/***********************************************************************************************************************
** Function Name         : RamTst_AbrahamAlgorithm
**
** Service ID            : NA
**
** Description           : Function for RAM testing using the Abraham
**                         Algorithm.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : TestedCellNumber
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, 
**                         RamTst_Config
**
** Function(s) invoked   : RamTst_SaveData, RamTst_AbrahamTestSteps,
**                         RamTst_RestoreData, RamTst_FillData, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_025
** Reference ID          : RAMTST_DUD_ACT_025_GBL001, RAMTST_DUD_ACT_025_GBL002, RAMTST_DUD_ACT_025_GBL003
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_AbrahamAlgorithm(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber)
{
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress;                                        /* PRQA S 3432 # JV-01 */
  /* Index of core */
  uint8 LucCoreIndex;
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  /* Index to the block */
  VAR(RamTst_NumberOfBlocksType, RAMTST_VAR_INIT) LucRamTstBlock;
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  #endif
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  /* Value of block ID */
  LucRamTstBlock = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock));
  LpRamTstAlgPtr = &((RamTst_Config[RAMTST_ZERO]
                           .LpRamTstAlgConfig)[(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]); /* PRQA S 3384 # JV-01 */
  #endif
  LpCellAddress = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress));
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  if (RAMTST_NON_DESTRUCTIVE == LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstTestPolicy)
  {
    RamTst_SaveData(RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestBufferAddress, TestedCellNumber);
  }
  #endif
  ReturnVal = RamTst_AbrahamTestSteps(TestedCellNumber, LpCellAddress);
  #if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
  if (RAMTST_NON_DESTRUCTIVE == LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstTestPolicy)
  {
    RamTst_RestoreData(RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestBufferAddress, TestedCellNumber,
                      LpCellAddress);
  }
  else
  {
    RamTst_FillData((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)), TestedCellNumber, LpCellAddress);
  }
  #else
  RamTst_FillData((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)), TestedCellNumber, LpCellAddress);
  #endif
  return ReturnVal;
} /* End of RamTst_AbrahamAlgorithm */
#endif /* End of STD_ON == RAMTST_ABRAHAM_TEST_SELECTED */
#if (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED)
/***********************************************************************************************************************
** Function Name         : RamTst_AbrahamTestSteps
**
** Service ID            : NA
**
** Description           : Function for RAM testing using the Abraham
**                         Algorithm.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : TestedCellNumber,
**                         LpCellAddress
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : None
**
** Function(s) invoked   : RamTst_InitializeCell, RamTst_RWAscend,
**                         RamTst_ReadDescend, RamTst_RWDescend,
**                         RamTst_ReadAscend, RamTst_RWWAscend,
**                         RamTst_WRWDescend, RamTst_InitializeCell,
**                         RamTst_WRWAscend, RamTst_RWWDescend, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_026
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_AbrahamTestSteps(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCellNumber,
                            volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress)              /* PRQA S 3432 # JV-01 */
{
  /* Testrun needed for the algorithm */
  VAR(uint8, AUTOMATIC) TestRun;
  /* Total number of tested bits */
  VAR(uint32, AUTOMATIC) Totalbits;
  /* Check for the bit */
  VAR(uint8, AUTOMATIC) CheckVariable;
  /* Initialize the tested cells with value 0 or 1 */
  VAR(RamTst_TestDataType, AUTOMATIC) BackGroundVariable;
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  /* Initialize the Return value */
  ReturnVal = E_OK;
  /* Initialize the BackGroundVariable */
  BackGroundVariable = RAMTST_ZERO;
  /* Initialize the CheckVariable */
  CheckVariable = RAMTST_ZERO;
  Totalbits = (uint32)TestedCellNumber << RAMTST_CELL_DIVIDER;
  /* Initialize the tested cells with BackGroundVariable */
  RamTst_InitializeCell(BackGroundVariable, TestedCellNumber, LpCellAddress);
  for (TestRun = RAMTST_ZERO; (TestRun < RAMTST_ABRAHAM_TESTRUN) && (ReturnVal == E_OK); TestRun++)
  {
    switch (TestRun)
    {
      case RAMTST_RW1_ASCEND:
      case RAMTST_RW0_ASCEND:
        ReturnVal = RamTst_RWAscend(CheckVariable, Totalbits, LpCellAddress);
        if (E_OK == ReturnVal)
          {
            CheckVariable = CheckVariable ^ RAMTST_ONE;
            BackGroundVariable = ~BackGroundVariable;
            ReturnVal = RamTst_ReadDescend(TestedCellNumber, BackGroundVariable, LpCellAddress);
          }
        break;
      case RAMTST_RW1_DESCEND:
      case RAMTST_RW0_DESCEND:
        ReturnVal = RamTst_RWDescend(CheckVariable, Totalbits, LpCellAddress);
        if (E_OK == ReturnVal)
        {
          CheckVariable = CheckVariable ^ RAMTST_ONE;
          BackGroundVariable = ~BackGroundVariable;
          ReturnVal = RamTst_ReadAscend(TestedCellNumber, BackGroundVariable, LpCellAddress);
        }
        break;
      case RAMTST_RWW_ASCEND:
        ReturnVal = RamTst_RWWAscend(CheckVariable, Totalbits, LpCellAddress);
        break;
      case RAMTST_WRW_DESCEND:
        ReturnVal = RamTst_WRWDescend(CheckVariable, Totalbits, LpCellAddress);
        break;
      case RAMTST_W_ASCEND:
        BackGroundVariable = ~BackGroundVariable;
        CheckVariable = CheckVariable ^ RAMTST_ONE;
        RamTst_InitializeCell(BackGroundVariable, TestedCellNumber, LpCellAddress);
        break;
      case RAMTST_WRW_ASCEND:
        ReturnVal = RamTst_WRWAscend(CheckVariable, Totalbits, LpCellAddress);
        break;
      default:
        ReturnVal = RamTst_RWWDescend(CheckVariable, Totalbits, LpCellAddress);
        break;
    }
  }
  return ReturnVal;
} /* End of RamTst_AbrahamAlgorithm */
#endif /* End of STD_ON == RAMTST_ABRAHAM_TEST_SELECTED */
/***********************************************************************************************************************
** Function Name         : RamTst_ChangeBlockBackGrndTest
**
** Service ID            : NA
**
** Description           : Function for Changing the Block.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, 
**                         RamTst_Config
**
** Function(s) invoked   : RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_027
** Reference ID          : RAMTST_DUD_ACT_027_GBL001, RAMTST_DUD_ACT_027_GBL002, RAMTST_DUD_ACT_027_GBL003
** Reference ID          : RAMTST_DUD_ACT_027_GBL004, RAMTST_DUD_ACT_027_GBL005, RAMTST_DUD_ACT_027_GBL006
***********************************************************************************************************************/
STATIC FUNC(void, RAMTST_PRIVATE_CODE) RamTst_ChangeBlockBackGrndTest(void)
{
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  /* Index of the RamTst_TestResultBuffer for each block  */
  VAR(RamTst_NumberOfBlocksType, AUTOMATIC) Index;
  /* Temporary variable to store the test result to be assigned
   * to the overall test result
   */
  VAR(RamTst_TestResultType, AUTOMATIC) Result;
  /* Index to the block */
  VAR(RamTst_NumberOfBlocksType, RAMTST_VAR_INIT) LucRamTstBlock;
  /* Index of core */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  /* Initial value */
  LucRamTstBlock = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock));
  LpRamTstAlgPtr = &((RamTst_Config[RAMTST_ZERO]
                           .LpRamTstAlgConfig)[(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]); /* PRQA S 3384 # JV-01 */
  (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgTest)) = LpRamTstAlgPtr->RamTstAlgorithm;
  if (LucRamTstBlock >= ((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pNumBlockId)) - RAMTST_ONE))                         /* PRQA S 3384 # JV-01 */
  {
    Result = RAMTST_RESULT_OK;
    for (Index = RAMTST_ZERO; Index < (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pNumBlockId)); Index++)
    {
      if ((RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer
          [(LpRamTstAlgPtr->LpRamTstBlockConfig[Index].RamTstBlockId) - RAMTST_ONE]) == RAMTST_RESULT_NOT_OK)           /* PRQA S 3383 # JV-02 */
      {
        Result = RAMTST_RESULT_NOT_OK;
      }
    }
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pOverallTestResult)) = Result;
    if (NULL_PTR != RamTst_Config[RAMTST_ZERO].RamTstCompletedNotification)
    {
      RamTst_Config[RAMTST_ZERO].RamTstCompletedNotification();
    }
    LucRamTstBlock = RAMTST_ZERO;
  }
  else
  {
    LucRamTstBlock++;
  }
  /* Change block to block new */ 
  (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock)) = LucRamTstBlock;
  (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress)) = 
                        (RamTst_TestDataType *)LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstStartAddress;  /* PRQA S 0306 # JV-01 */
  (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)) = 
                                        (uint32)LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstFillPattern;
} /* End of RamTst_ChangeBlockBackGrndTest */
#if (RAMTST_RUN_FULL_TEST_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_ChangeBlockForeGrndTest
**
** Service ID            : NA
**
** Description           : Function for Changing the Block.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint, 
**                         RamTst_Config
**
** Function(s) invoked   : RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_028
** Reference ID          : RAMTST_DUD_ACT_028_GBL001, RAMTST_DUD_ACT_028_GBL002, RAMTST_DUD_ACT_028_GBL003
** Reference ID          : RAMTST_DUD_ACT_028_GBL004, RAMTST_DUD_ACT_028_GBL005, RAMTST_DUD_ACT_028_GBL006
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE) RamTst_ChangeBlockForeGrndTest(void)
{
  P2CONST(RamTst_AlgConfigType, AUTOMATIC, RAMTST_VAR) LpRamTstAlgPtr;
  /* Index of the RamTst_TestResultBuffer for each block */
  VAR(RamTst_NumberOfBlocksType, AUTOMATIC) Index;
  /* Temporary variable to store the test result to be assigned
   * to the overall test result
   */
  VAR(RamTst_TestResultType, AUTOMATIC) Result;
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  /* Index to the block */
  VAR(RamTst_NumberOfBlocksType, RAMTST_VAR_INIT) LucRamTstBlock;
  /* Index of core */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  /* Initialize the Return value */
  LucRamTstBlock = (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock));
  ReturnVal = E_OK;
  LpRamTstAlgPtr = &((RamTst_Config[RAMTST_ZERO].
                           LpRamTstAlgConfig)[(*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgParamsId)) - RAMTST_ONE]);  /* PRQA S 3384 # JV-01 */
  (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgTest)) = LpRamTstAlgPtr->RamTstAlgorithm;
  if (LucRamTstBlock >= ((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pNumBlockId)) - RAMTST_ONE))                         /* PRQA S 3384 # JV-01 */
  {
    Result = RAMTST_RESULT_OK;
    for (Index = RAMTST_ZERO; Index < (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pNumBlockId)); Index++)
    {
      if ((RamTst_GaaGlobalAccPoint[LucCoreIndex].pTestResultBuffer
                    [(LpRamTstAlgPtr->LpRamTstBlockConfig[Index].RamTstBlockId) - RAMTST_ONE]) == RAMTST_RESULT_NOT_OK) /* PRQA S 3383 # JV-01 */
      {
        Result = RAMTST_RESULT_NOT_OK;
      }
    }
    (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pOverallTestResult)) = Result;
    LucRamTstBlock = RAMTST_ZERO;
  }
  else
  {
    LucRamTstBlock++;
    ReturnVal = E_NOT_OK;
  }
  /* Change global var to new block */
  (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pBlock)) = LucRamTstBlock;
  (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress)) = 
                        (RamTst_TestDataType *)LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstStartAddress;  /* PRQA S 0306 # JV-01 */
  (*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pFillPattern)) = 
                                        (uint32)LpRamTstAlgPtr->LpRamTstBlockConfig[LucRamTstBlock].RamTstFillPattern;
  return ReturnVal;
} /* End of RamTst_ChangeBlockForeGrndTest */
#endif /* End of RAMTST_RUN_FULL_TEST_API == STD_ON */
/***********************************************************************************************************************
** Function Name         : RamTst_CallAlgorithm
**
** Service ID            : NA
**
** Description           : Function for Calling Different Algorithm.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : TestedCells
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : None
**
** Function(s) invoked   : RamTst_CheckerAlgorithm, RamTst_MarchAlgorithm,
**                         RamTst_WalkPathAlgorithm,
**                         RamTst_GalpatAlgorithm,
**                         RamTst_TranspGalpatAlgorithm,
**                         RamTst_AbrahamAlgorithm, RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_029
** Reference ID          : RAMTST_DUD_ACT_029_GBL001
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_CallAlgorithm(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells)
{
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  /* Index of core */
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  /* Initialize the Return value */
  ReturnVal = E_OK;
  switch ((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pAlgTest)))
  {
  #if (STD_ON == RAMTST_CHECKERBOARD_TEST_SELECTED)
  case RAMTST_CHECKERBOARD_TEST:
    /* Start the RAM Test by Checker Board Test Algorithm */
    ReturnVal = RamTst_CheckerAlgorithm(TestedCells);
    break;
  #endif
  #if (STD_ON == RAMTST_MARCH_TEST_SELECTED)
  case RAMTST_MARCH_TEST:
    /* Start the RAM Test by March Test Algorithm */
    ReturnVal = RamTst_MarchAlgorithm(TestedCells);
    break;
  #endif
  #if (STD_ON == RAMTST_WALK_PATH_TEST_SELECTED)
  case RAMTST_WALK_PATH_TEST:
    /* Start the RAM Test by WalkPath Test Algorithm */
    ReturnVal = RamTst_WalkPathAlgorithm(TestedCells);
    break;
  #endif
  #if (STD_ON == RAMTST_GALPAT_TEST_SELECTED)
  case RAMTST_GALPAT_TEST:
    /* Start the RAM Test by Galpat Test Algorithm */
    ReturnVal = RamTst_GalpatAlgorithm(TestedCells);
    break;
  #endif
  #if (STD_ON == RAMTST_TRANSP_GALPAT_TEST_SELECTED)
  case RAMTST_TRANSP_GALPAT_TEST:
    /* Start the RAM Test by Transparent Galpat Test Algorithm */
    ReturnVal = RamTst_TranspGalpatAlgorithm(TestedCells);
    break;
  #endif
  #if (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED)
  case RAMTST_ABRAHAM_TEST:
    /* Start the RAM Test by Abraham Test Algorithm */
    ReturnVal = RamTst_AbrahamAlgorithm(TestedCells);
    break;
  #endif
  default:
    /* Do Nothing */
    break;
  }
  return ReturnVal;
} /* End of RamTst_CallAlgorithm */
#if (RAMTST_NON_DESTRUCTIVE_POLICY == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_SaveData
**
** Service ID            : NA
**
** Description           : Function for storing the RAM content before
**                         starting the RAM Test.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : LpBuffer,
**                         TestedCells
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : RamTst_GaaGlobalAccPoint
**
** Function(s) invoked   : RamTst_GetCoreIndex
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_032
** Reference ID          : RAMTST_DUD_ACT_032_GBL001
***********************************************************************************************************************/
STATIC FUNC(void, RAMTST_PRIVATE_CODE) 
           RamTst_SaveData(volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_APPL_DATA) LpBuffer,                   /* PRQA S 3432 # JV-01 */
                           VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells)
{
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Index;
  uint8 LucCoreIndex;
  /* Get core index */
  LucCoreIndex = RamTst_GetCoreIndex();
  /* Initialize the Return value */
  for (Index = RAMTST_ZERO; Index < TestedCells; Index++)
  {
    *(LpBuffer + Index) = *((*(RamTst_GaaGlobalAccPoint[LucCoreIndex].pCellAddress)) + Index);                          /* PRQA S 0488 # JV-01 */
  }
} /* End of RamTst_SaveData */
/***********************************************************************************************************************
** Function Name         : RamTst_RestoreData
**
** Service ID            : NA
**
** Description           : Function for re-storing the RAM content after
**                         finishing the RAM Test.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : RamTst_TestDataType LpBuffer
**                         RamTst_NumberOfTestedCellsType TestedCells
**                         RamTst_TestDataType LpCellAddress
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_030
***********************************************************************************************************************/
STATIC FUNC(void, RAMTST_PRIVATE_CODE) 
            RamTst_RestoreData(volatile P2CONST(RamTst_TestDataType, AUTOMATIC, RAMTST_APPL_DATA) LpBuffer,
                               VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells,
                               volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress)           /* PRQA S 3432 # JV-01 */
{
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Index;
  for (Index = RAMTST_ZERO; Index < TestedCells; Index++)
  {
    *(LpCellAddress + Index) = *(LpBuffer + Index);                                                                     /* PRQA S 0488 # JV-01 */
  }
} /* End of RamTst_RestoreData */
#endif
/***********************************************************************************************************************
** Function Name         : RamTst_FillData
**
** Service ID            : NA
**
** Description           : Function for initializing the RAM content after
**                         finishing the destructive RAM Test.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : RamTstFillPattern,
**                         TestedCells,
**                         LpCellAddress
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_031
***********************************************************************************************************************/
STATIC FUNC(void, RAMTST_PRIVATE_CODE) RamTst_FillData(VAR(uint32, RAMTST_VAR) RamTstFillPattern,
                                               VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells,
                                        volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress)  /* PRQA S 3432 # JV-01 */
{
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Index;
  for (Index = RAMTST_ZERO; Index < TestedCells; Index++)
  {
    *(LpCellAddress + Index) = RamTstFillPattern;                                                                       /* PRQA S 0488 # JV-01 */
  }
} /* End of RamTst_FillData */
/***********************************************************************************************************************
** Function Name         : RamTst_InitializeCell
**
** Service ID            : NA
**
** Description           : Function for Initializing  RAM content either
**                         with zero or one.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : Init_CellVariable,
**                         TestedCells,
**                         LpCellAddress
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : None
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_033
***********************************************************************************************************************/
#if ((STD_ON == RAMTST_ABRAHAM_TEST_SELECTED) || (STD_ON == RAMTST_MARCH_TEST_SELECTED) ||  \
      (STD_ON == RAMTST_GALPAT_TEST_SELECTED) || (STD_ON == RAMTST_WALK_PATH_TEST_SELECTED))
STATIC FUNC(void, RAMTST_PRIVATE_CODE)
            RamTst_InitializeCell(VAR(RamTst_TestDataType, AUTOMATIC) Init_CellVariable,
                                  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells,
                                  volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress)        /* PRQA S 3432 # JV-01 */
{
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Index;
  for (Index = RAMTST_ZERO; Index < TestedCells; Index++)
  {
    *(LpCellAddress + Index) = Init_CellVariable;                                                                       /* PRQA S 0488 # JV-01 */
  }
} /* End of RamTst_InitializeCell */
#endif /* End of STD_ON == (test algorithms selected) */
#if ((STD_ON == RAMTST_ABRAHAM_TEST_SELECTED) || (STD_ON == RAMTST_MARCH_TEST_SELECTED))
/***********************************************************************************************************************
** Function Name         : RamTst_RWAscend
**
** Service ID            : NA
**
** Description           : Function for read, check and invert each bit in
**                         ascending order.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CheckVariable,
**                         Totalbits,
**                         LpCellAddress
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_034
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
            RamTst_RWAscend(VAR(uint8, AUTOMATIC) CheckVariable, VAR(uint32, AUTOMATIC) Totalbits,
                            volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress)              /* PRQA S 3432 # JV-01 */
{
  /* Index of the cells */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Cellnumber;
  /* Bit to be tested in the cell */
  VAR(uint8, AUTOMATIC) Bitnumber;
  /* Bit numbering */
  VAR(uint32, AUTOMATIC) Index;
  /* Return variable */
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  /* Initialize the value to ReturnVal */
  ReturnVal = E_OK;
  /* Read, check and invert each bit in ascending order (LSB to MSB) */
  for (Index = RAMTST_ZERO; (Index < Totalbits) && (E_OK == ReturnVal); Index++)
  {
    /* loading Value for Cellnumber */
    Cellnumber = (RamTst_NumberOfTestedCellsType)(Index >> RAMTST_CELL_DIVIDER);
    /* Loading Bitnumber value */
    Bitnumber = (uint8)(Index & (RAM_TEST_DATA_TYPE - RAMTST_ONE));
    if ((*(LpCellAddress + Cellnumber) & ((uint32)(RAMTST_ONE) << Bitnumber)) ==                                        /* PRQA S 0488 # JV-01 */
        (((RamTst_TestDataType)(CheckVariable)) << Bitnumber))
    {
      /* Invert the Testbit  */
      RAMTST_INVERT_BITX(*(LpCellAddress + Cellnumber), Bitnumber, RamTst_TestDataType);                                /* PRQA S 0488, 3464 # JV-01, JV-01 */
    }
    else
    {
      ReturnVal = E_NOT_OK;
    }
  }
  return ReturnVal;
} /* End of RamTst_RWAscend */
#endif
/* End of (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED)
 * || (STD_ON == RAMTST_MARCH_TEST_SELECTED)
 */
#if (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED)
/***********************************************************************************************************************
** Function Name         : RamTst_ReadDescend
**
** Service ID            : NA
**
** Description           : Function for read and check cells in descending
**                         order.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : TestedCells,
**                         BackGroundVariable,
**                         LpCellAddress
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_036
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_ReadDescend(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells,
                       VAR(RamTst_TestDataType, AUTOMATIC) BackGroundVariable,
                       volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress)                   /* PRQA S 3432, 3673 # JV-01, JV-01 */
{
  /* Index of the cells*/
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Cellnumber;
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  /* Initialize the value to ReturnVal */
  ReturnVal = E_OK;
  /* Read and check in descending order */
  for (Cellnumber = (TestedCells); ((Cellnumber > (RamTst_NumberOfTestedCellsType)RAMTST_ZERO) && (E_OK == ReturnVal));
       Cellnumber--)
  {
    if (*(LpCellAddress + (Cellnumber - (RamTst_NumberOfTestedCellsType)RAMTST_ONE)) != BackGroundVariable)             /* PRQA S 0488, 3383 # JV-01, JV-01 */
    {
      ReturnVal = E_NOT_OK;
    }
  }
  return ReturnVal;
} /* End of RamTst_ReadDescend */
#endif /* End of (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED) */
#if ((STD_ON == RAMTST_ABRAHAM_TEST_SELECTED) || (STD_ON == RAMTST_MARCH_TEST_SELECTED))
/***********************************************************************************************************************
** Function Name         : RamTst_RWDescend
**
** Service ID            : NA
**
** Description           : Function for read, check and invert each bit in
**                         descending order.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CheckVariable,
**                         Totalbits,
**                         LpCellAddress
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_037
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
            RamTst_RWDescend(VAR(uint8, AUTOMATIC) CheckVariable, VAR(uint32, AUTOMATIC) Totalbits,
                             volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress)             /* PRQA S 3432 # JV-01 */
{
  /* Index of the cells */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Cellnumber;
  /* Bit to be tested in the cell */
  VAR(uint8, AUTOMATIC) Bitnumber;
  /* Bit numbering */
  VAR(uint32, AUTOMATIC) Index;
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  /* Initialize the value to ReturnVal */
  ReturnVal = E_OK;
  /* Read, check and invert each bit in descending order (LSB to MSB) */
  for (Index = (Totalbits); (Index > (uint32)RAMTST_ZERO) && (E_OK == ReturnVal); Index--)
  {
    Cellnumber = (RamTst_NumberOfTestedCellsType)((Index - (uint32)RAMTST_ONE) >> RAMTST_CELL_DIVIDER);                 /* PRQA S 3383 # JV-03 */
    Bitnumber = (uint8)((Index - (uint32)RAMTST_ONE) & (RAM_TEST_DATA_TYPE - RAMTST_ONE));                              /* PRQA S 3383 # JV-01 */
    if (((*(LpCellAddress + Cellnumber)) & ((uint32)(RAMTST_ONE) << Bitnumber)) ==                                      /* PRQA S 0488 # JV-01 */
        ((RamTst_TestDataType)(CheckVariable) << Bitnumber))
    {
      /* Invert the Testbit  */
      RAMTST_INVERT_BITX(*(LpCellAddress + Cellnumber), Bitnumber, RamTst_TestDataType);                                /* PRQA S 0488, 3464 # JV-01, JV-01 */
    }
    else
    {
      ReturnVal = E_NOT_OK;
    }
  }
  return ReturnVal;
} /* End of RamTst_RWDescend */
#endif
/* End of (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED) ||
 * (STD_ON == RAMTST_MARCH_TEST_SELECTED)
 */
#if (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED)
/***********************************************************************************************************************
** Function Name         : RamTst_ReadAscend
**
** Service ID            : NA
**
** Description           : Function for read and check cells in ascending
**                         order.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : TestedCells
**                         BackGroundVariable
**                         LpCellAddress
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : None
**
** Function(s) invoked   : None
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_039
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
    RamTst_ReadAscend(VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells,
                      VAR(RamTst_TestDataType, AUTOMATIC) BackGroundVariable,
                      volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress)                    /* PRQA S 3432, 3673 # JV-01, JV-01 */
{
  /* Index of the cells */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Cellnumber;
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  /* Initialize the value to ReturnVal */
  ReturnVal = E_OK;
  /* Read and check in descending order */
  for (Cellnumber = RAMTST_ZERO; (Cellnumber < TestedCells) && (E_OK == ReturnVal); Cellnumber++)
  {
    if (*(LpCellAddress + Cellnumber) != BackGroundVariable)                                                            /* PRQA S 0488 # JV-01 */
    {
      ReturnVal = E_NOT_OK;
    }
  }
  return ReturnVal;
} /* End of RamTst_ReadAscend */
#endif /* End of ((STD_ON == RAMTST_ABRAHAM_TEST_SELECTED) */
#if (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED)
/***********************************************************************************************************************
** Function Name         : RamTst_RWWDescend
**
** Service ID            : NA
**
** Description           : Function for read, invert and re-invert each bit in
**                         descending order.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CheckVariable
**                         Totalbits
**                         LpCellAddress
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : None
**
** Function(s) invoked   : RamTst_ReadAscend
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_040
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
            RamTst_RWWDescend(VAR(uint8, AUTOMATIC) CheckVariable, VAR(uint32, AUTOMATIC) Totalbits,
                              volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress)            /* PRQA S 3432 # JV-01 */
{
  /* Index of the cells */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Cellnumber;
  VAR(uint32, AUTOMATIC) Bitnumber;
  /* Bit numbering */
  VAR(uint32, AUTOMATIC) Index;
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells;
  /* Initialize the tested cells with value ~0 */
  VAR(RamTst_TestDataType, AUTOMATIC) BackGroundVariable;
  /* Initialize the value to ReturnVal */
  ReturnVal = E_OK;
  /* Initialize the value to BackGroundVariable */
  BackGroundVariable = ~(RamTst_TestDataType)(RAMTST_ZERO);
  /* Read, check and invert each bit in descending order (LSB to MSB) */
  for (Index = Totalbits; (Index > (uint32)RAMTST_ZERO) && (E_OK == ReturnVal); Index--)
  {
    Cellnumber = (RamTst_NumberOfTestedCellsType)((Index - (uint32)RAMTST_ONE) >> RAMTST_CELL_DIVIDER);                 /* PRQA S 3383 # JV-01 */
    Bitnumber = (uint32)((Index - (uint32)RAMTST_ONE) & (RAM_TEST_DATA_TYPE - RAMTST_ONE));                             /* PRQA S 3383 # JV-01 */
    if (((*(LpCellAddress + Cellnumber)) & ((uint32)(RAMTST_ONE) << Bitnumber)) ==                                      /* PRQA S 0488 # JV-01 */
        ((RamTst_TestDataType)(CheckVariable) << Bitnumber))
    {
      /* Invert the Testbit  */
      RAMTST_INVERT_BITX(*(LpCellAddress + Cellnumber), Bitnumber, RamTst_TestDataType);                                /* PRQA S 0488, 3464 # JV-01, JV-01 */
      /* re-Invert the Testbit  */
      RAMTST_INVERT_BITX(*(LpCellAddress + Cellnumber), Bitnumber, RamTst_TestDataType);                                /* PRQA S 0488, 3464 # JV-01, JV-01 */
    }
    else
    {
      ReturnVal = E_NOT_OK;
    }
  }
  if (E_OK == ReturnVal)
  {
    TestedCells = (RamTst_NumberOfTestedCellsType)(Totalbits >> RAMTST_CELL_DIVIDER);
    ReturnVal = RamTst_ReadAscend(TestedCells, BackGroundVariable, LpCellAddress);
  }
  return ReturnVal;
} /* End of RamTst_RWWDescend */
/***********************************************************************************************************************
** Function Name         : RamTst_RWWAscend
**
** Service ID            : NA
**
** Description           : Function for read, invert and re-invert each bit in
**                         ascending order.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CheckVariable
**                         Totalbits
**                         LpCellAddress
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : None
**
** Function(s) invoked   : RamTst_ReadDescend
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_041
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
            RamTst_RWWAscend(VAR(uint8, AUTOMATIC) CheckVariable, VAR(uint32, AUTOMATIC) Totalbits, 
                             volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress)             /* PRQA S 3432 # JV-01 */
{
  /* Index of the cells */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Cellnumber;
  /* Bit to be tested in the cell */
  VAR(uint32, AUTOMATIC) Bitnumber;
  /* Bit numbering */
  VAR(uint32, AUTOMATIC) Index;
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells;
  /* Initialize the tested cells with value 0 */
  VAR(RamTst_TestDataType, AUTOMATIC) BackGroundVariable;
  /* Initialize the value to ReturnVal */
  ReturnVal = E_OK;
  /* Initialize the value to BackGroundVariable */
  BackGroundVariable = RAMTST_ZERO;
  /* Read, check and invert each bit in ascending order (LSB to MSB) */
  for (Index = RAMTST_ZERO; (Index < Totalbits) && (E_OK == ReturnVal); Index++)
  {
    Cellnumber = (RamTst_NumberOfTestedCellsType)(Index >> RAMTST_CELL_DIVIDER);
    Bitnumber = (uint32)(Index & (RAM_TEST_DATA_TYPE - RAMTST_ONE));
    if (((*(LpCellAddress + Cellnumber)) & ((uint32)(RAMTST_ONE) << Bitnumber)) ==                                      /* PRQA S 0488 # JV-01 */
        ((RamTst_TestDataType)(CheckVariable) << Bitnumber))
    {
      /* Invert the Testbit  */
      RAMTST_INVERT_BITX(*(LpCellAddress + Cellnumber), Bitnumber, RamTst_TestDataType);                                /* PRQA S 0488, 3464 # JV-01, JV-01 */
      /* re-Invert the Testbit  */
      RAMTST_INVERT_BITX(*(LpCellAddress + Cellnumber), Bitnumber, RamTst_TestDataType);                                /* PRQA S 0488, 3464 # JV-01, JV-01 */
    }
    else
    {
      ReturnVal = E_NOT_OK;
    }
  }
  if (E_OK == ReturnVal)
  {
    TestedCells = (RamTst_NumberOfTestedCellsType)(Totalbits >> RAMTST_CELL_DIVIDER);
    ReturnVal = RamTst_ReadDescend(TestedCells, BackGroundVariable, LpCellAddress);
  }
  return ReturnVal;
} /* End of RamTst_RWWAscend */
/***********************************************************************************************************************
** Function Name         : RamTst_WRWAscend
**
** Service ID            : NA
**
** Description           : Function for invert, read and re-invert each bit in
**                         ascending order.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CheckVariable
**                         Totalbits
**                         LpCellAddress
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : None
**
** Function(s) invoked   : RamTst_ReadDescend
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_043
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
            RamTst_WRWAscend(VAR(uint8, AUTOMATIC) CheckVariable, VAR(uint32, AUTOMATIC) Totalbits,
                             volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress)             /* PRQA S 3432 # JV-01 */
{
  /* Index of the cells */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Cellnumber;
  /* bit to be tested in the cell */
  VAR(uint32, AUTOMATIC) Bitnumber;
  /* bit numbering */
  VAR(uint32, AUTOMATIC) Index;
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells;
  /* Initialize the tested cells with value ~0 */
  VAR(RamTst_TestDataType, AUTOMATIC) BackGroundVariable;
  /* Initialize the value to ReturnVal */
  ReturnVal = E_OK;
  /* Initialize the value to BackGroundVariable */
  BackGroundVariable = ~(RamTst_TestDataType)(RAMTST_ZERO);
  CheckVariable = CheckVariable ^ RAMTST_ONE;                                                                           /* PRQA S 1338 # JV-01 */
  /* Read, check and invert each bit in ascending order (LSB to MSB) */
  for (Index = RAMTST_ZERO; (Index < Totalbits) && (E_OK == ReturnVal); Index++)
  {
    Cellnumber = (RamTst_NumberOfTestedCellsType)(Index >> RAMTST_CELL_DIVIDER);
    Bitnumber = (uint32)(Index & (RAM_TEST_DATA_TYPE - RAMTST_ONE));
    /* Invert the Testbit  */
    RAMTST_INVERT_BITX(*(LpCellAddress + Cellnumber), Bitnumber, RamTst_TestDataType);                                  /* PRQA S 0488, 3464 # JV-01, JV-01 */
    if (((*(LpCellAddress + Cellnumber)) & ((uint32)(RAMTST_ONE) << Bitnumber)) ==                                      /* PRQA S 0488 # JV-01 */
        ((RamTst_TestDataType)(CheckVariable) << Bitnumber))
    {
      /* re-Invert the Testbit  */
      RAMTST_INVERT_BITX(*(LpCellAddress + Cellnumber), Bitnumber, RamTst_TestDataType);                                /* PRQA S 0488, 3464 # JV-01, JV-01 */
    }
    else
    {
      ReturnVal = E_NOT_OK;
    }
  }
  if (E_OK == ReturnVal)
  {
    TestedCells = (RamTst_NumberOfTestedCellsType)(Totalbits >> RAMTST_CELL_DIVIDER);
    ReturnVal = RamTst_ReadDescend(TestedCells, BackGroundVariable, LpCellAddress);
  }
  return ReturnVal;
} /* End of RamTst_WRWAscend */
/***********************************************************************************************************************
** Function Name         : RamTst_WRWDescend
**
** Service ID            : NA
**
** Description           : Function for invert, read and re-invert each bit in
**                         descending order.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : CheckVariable
**                         Totalbits
**                         LpCellAddress
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : Std_ReturnType
**
** Preconditions         : The function RamTst_Init shall be called first
**                         before calling this function.
**
** Global Variables Used : None
**
** Function(s) invoked   : RamTst_ReadAscend
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_042
***********************************************************************************************************************/
STATIC FUNC(Std_ReturnType, RAMTST_PRIVATE_CODE)
            RamTst_WRWDescend(VAR(uint8, AUTOMATIC) CheckVariable, VAR(uint32, AUTOMATIC) Totalbits,
                              volatile P2VAR(RamTst_TestDataType, AUTOMATIC, RAMTST_VAR_FAST) LpCellAddress)            /* PRQA S 3432 # JV-01 */
{
  /* Index of the 0cells */
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) Cellnumber;
  /* Bit to be tested in the cell */
  VAR(uint32, AUTOMATIC) Bitnumber;
  /* Bit numbering */
  VAR(uint32, AUTOMATIC) Index;
  VAR(Std_ReturnType, AUTOMATIC) ReturnVal;
  VAR(RamTst_NumberOfTestedCellsType, AUTOMATIC) TestedCells;
  /* Initialize the tested cells with value 0 */
  VAR(RamTst_TestDataType, AUTOMATIC) BackGroundVariable;
  /* Initialize the value to ReturnVal */
  ReturnVal = E_OK;
  /* Initialize the value to BackGroundVariable */
  BackGroundVariable = RAMTST_ZERO;
  CheckVariable = CheckVariable ^ RAMTST_ONE;                                                                           /* PRQA S 1338 # JV-01 */
  /* Read, check and invert each bit in ascending order (LSB to MSB) */
  for (Index = Totalbits; (Index > (uint32)RAMTST_ZERO) && (E_OK == ReturnVal); Index--)
  {
    Cellnumber = (RamTst_NumberOfTestedCellsType)((Index - (uint32)RAMTST_ONE) >> RAMTST_CELL_DIVIDER);                 /* PRQA S 3383 # JV-01 */
    Bitnumber = (uint32)((Index - (uint32)RAMTST_ONE) & (RAM_TEST_DATA_TYPE - RAMTST_ONE));                             /* PRQA S 3383 # JV-01 */
    /* Invert the Testbit  */
    RAMTST_INVERT_BITX(*(LpCellAddress + Cellnumber), Bitnumber, RamTst_TestDataType);                                  /* PRQA S 0488, 3464 # JV-01, JV-01 */
    if (((*(LpCellAddress + Cellnumber)) & ((uint32)(RAMTST_ONE) << Bitnumber)) ==                                      /* PRQA S 0488 # JV-01 */
        ((RamTst_TestDataType)(CheckVariable) << Bitnumber))
    {
      /* re-Invert the Testbit  */
      RAMTST_INVERT_BITX(*(LpCellAddress + Cellnumber), Bitnumber, RamTst_TestDataType);                                /* PRQA S 0488, 3464 # JV-01, JV-01 */
    }
    else
    {
      ReturnVal = E_NOT_OK;
    }
  }
  if (E_OK == ReturnVal)
  {
    TestedCells = (RamTst_NumberOfTestedCellsType)(Totalbits >> RAMTST_CELL_DIVIDER);
    ReturnVal = RamTst_ReadAscend(TestedCells, BackGroundVariable, LpCellAddress);
  }
  return ReturnVal;
} /* End of RamTst_WRWDescend */
#endif /* End of (STD_ON == RAMTST_ABRAHAM_TEST_SELECTED) */
/***********************************************************************************************************************
** Function Name         : RamTst_GetCoreIndex
**
** Service ID            : NA
**
** Description           : This service returns the index of core ID
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Non Reentrant
**
** Input Parameters      : None
**
** InOut Parameters      : None
**
** Output Parameters     : None
**
** Return parameter      : LucCoreIndex
**
** Preconditions         : None
**
** Global Variables Used : RamTst_GaaGetCoreId2Index
**
** Function(s) invoked   : GetCoreID
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_044
***********************************************************************************************************************/
STATIC FUNC(uint8, RAMTST_PRIVATE_CODE) RamTst_GetCoreIndex (void)
{
  uint8 LucCoreIndex;
  #if (RAMTST_MULTI_CORE_SUPPORT == STD_ON)
  uint8 LucCoreId;
  /* Get Core id for code branching */
  LucCoreId = (uint8)GetCoreID();
  /* Covert Core Id to Core Index */
  LucCoreIndex = RamTst_GaaGetCoreId2Index[LucCoreId];
  #else
  /* if Multicore is not configude, defauld coreid is 0x00
     To optimize implementation */
  LucCoreIndex = 0x00U;
  #endif /* RAMTST_MULTI_CORE_SUPPORT == STD_ON */
  return LucCoreIndex;
}

#define RAMTST_STOP_SEC_PRIVATE_CODE
#include "RamTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */
#define RAMTST_START_SEC_PUBLIC_CODE
#include "RamTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */
#if (RAMTST_GET_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
** Function Name         : RamTst_GetVersionInfo
**
** Service ID            : 0x0A
**
** Description           : This service returns the version information of this
**                         module.
**
** Sync/Async            : Synchronous
**
** Reentrancy            : Reentrant
**
** Input Parameters      : VersionInfo
**
** InOut Parameters      : None
**
** Output Parameters     : VersionInfo
**
** Return parameter      : None
**
** Preconditions         : None
**
** Global Variables Used : None
**
** Function(s) invoked   : Det_ReportError
**
** Registers Used        : None
**
** Reference ID          : RAMTST_DUD_ACT_010
** Reference ID          : RAMTST_DUD_ACT_010_ERR001
***********************************************************************************************************************/
/* RAMTST Version Information Check */
FUNC(void, RAMTST_PUBLIC_CODE) 
     RamTst_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, RAMTST_APPL_DATA) VersionInfo)                         /* PRQA S 3432, 1503 # JV-01, JV-01 */
{
  #if (RAMTST_DEV_ERROR_DETECT == STD_ON)
  /* Report to DET, if VersionInfo pointer is equal to Null */
  if (NULL_PTR == VersionInfo)
  {
    /* Report to DET  */
    (void)Det_ReportError(RAMTST_MODULE_ID, RAMTST_INSTANCE_ID, RAMTST_GET_VERSIONINFO_SVCID, RAMTST_E_PARAM_POINTER);
  }
  else
  #endif /*#if (RAMTST_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Copy the vendor Id */
    (VersionInfo)->vendorID = (uint16)RAMTST_VENDOR_ID;
    /* Copy the module Id */
    (VersionInfo)->moduleID = (uint16)RAMTST_MODULE_ID;
    /* Copy Software Major Version */
    (VersionInfo)->sw_major_version = RAMTST_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    (VersionInfo)->sw_minor_version = RAMTST_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    (VersionInfo)->sw_patch_version = RAMTST_SW_PATCH_VERSION;
  }
}
#endif
/* End of RamTst Section Code */
#define RAMTST_STOP_SEC_PUBLIC_CODE
#include "RamTst_MemMap.h"                                                                                              /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
