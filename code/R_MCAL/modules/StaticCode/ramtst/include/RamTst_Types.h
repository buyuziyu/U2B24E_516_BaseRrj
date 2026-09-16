/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = RamTst_Types.h                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains macros, RamTst type definitions, structure data types                                           */
/* and API function prototypes of RamTst Driver                                                                       */
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
 * 1.4.1:   30/06/2025  : Update SW-VERSION
 * 1.3.1:   31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E 
 * 1.3.0:   28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.2.0:   31/12/2024  : Update SW-Version for Ver22.02.00/Ver22.02.00.D U2Bx Final release
 * 1.1.2:   31/10/2024  : Update SW-VERSION to 1.1.2
 * 1.1.1:   30/08/2024  : As part of QAC 9.5.0 support, following changes are made:
 *                        1. Remove QAC message 1536
 * 1.0.1:   17/10/2022  : Remove macro RAMTST_WORD_ZERO due to redundant
 *                        Add QAC message header 1536
 * 1.0.0:   23/07/2023  : Update RamTst_AlgorithmType, RamTst_BlockConfigType, RamTst_AlgConfigType, RamTst_ConfigType
 *                        RamTst_GlobalAccessPointType
 *          19/05/2023  : Initial Version
 */
/**********************************************************************************************************************/
#ifndef RAMTST_LTTYPES_H
#define RAMTST_LTTYPES_H
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
#define RAMTST_LTTYPES_AR_RELEASE_MAJOR_VERSION    RAMTST_AR_RELEASE_MAJOR_VERSION
#define RAMTST_LTTYPES_AR_RELEASE_MINOR_VERSION    RAMTST_AR_RELEASE_MINOR_VERSION
#define RAMTST_LTTYPES_AR_RELEASE_REVISION_VERSION RAMTST_AR_RELEASE_REVISION_VERSION
#define RAMTST_LTTYPES_SW_MAJOR_VERSION            RAMTST_SW_MAJOR_VERSION
#define RAMTST_LTTYPES_SW_MINOR_VERSION            RAMTST_SW_MINOR_VERSION
/***********************************************************************************************************************
**                                           Macros to avoid direct numbers                                           **
***********************************************************************************************************************/
#define RAMTST_ZERO                              0u
#define RAMTST_ONE                               1u
#define RAMTST_TWO                               2u
#define RAMTST_THREE                             3u
#define RAMTST_EIGHT                             8u
#define RAMTST_CRC_INIT_VALUE                    (uint16)0xFFFFu
#define RAMTST_CRC_TABLE_LENGTH                  256u
#define RAMTST_TRUE                              (uint8)1u
#define RAMTST_FALSE                             (uint8)0u
/***********************************************************************************************************************
**                                              Driver  ECC mask Macros                                               **
***********************************************************************************************************************/
#define RAMTST_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
/***********************************************************************************************************************
**                                                  type definitions                                                  **
***********************************************************************************************************************/
/*
 *  Defines the Block_TestType.
 */
typedef enum ETag_RamTst_Block_TestType
{
  RAMTST_DESTRUCTIVE,
  RAMTST_NON_DESTRUCTIVE
} RamTst_Block_TestType;

/* RamTst_ExecutionStatusType
** Defines the execution status of the RAM Test.
*/
typedef enum ETag_RamTst_ExecutionStatusType
{
  RAMTST_EXECUTION_UNINIT,
  RAMTST_EXECUTION_STOPPED,
  RAMTST_EXECUTION_RUNNING,
  RAMTST_EXECUTION_SUSPENDED
} RamTst_ExecutionStatusType;

/* RamTst_TestResultType
** Defines the Test Result status of the RAM Test.
*/
typedef enum ETag_RamTst_TestResultType
{
  RAMTST_RESULT_NOT_TESTED,
  RAMTST_RESULT_OK,
  RAMTST_RESULT_NOT_OK,
  RAMTST_RESULT_UNDEFINED
} RamTst_TestResultType;

/* RamTst_AlgorithmType
** Defines the Algorithm that selected for the RAM Test.
*/
typedef enum ETag_RamTst_AlgorithmType
{
  RAMTST_ALGORITHM_UNDEFINED,
  RAMTST_CHECKERBOARD_TEST,
  RAMTST_MARCH_TEST,
  RAMTST_WALK_PATH_TEST,
  RAMTST_GALPAT_TEST,
  RAMTST_TRANSP_GALPAT_TEST,
  RAMTST_ABRAHAM_TEST
} RamTst_AlgorithmType;

/*  RamTst_AlgParamsIdType
 *   Data type used to identify a set of configuration parameters for a test
 *   algorithm.
 */
typedef VAR(uint8, AUTOMATIC) RamTst_AlgParamsIdType;

/* RamTst_NumberOfTestedCellsType
** Data type of number of tested RAM cells.
*/
typedef VAR(uint32, AUTOMATIC) RamTst_NumberOfTestedCellsType;

/* RamTst_NumberOfBlocksType.
** Data type of number of blocks
*/
typedef VAR(uint16, AUTOMATIC) RamTst_NumberOfBlocksType;

/* RamTst_NotificationType
** Defines the notification function pointer for the group.
*/
typedef P2FUNC(void, RAMTST_APPL_CODE, RamTst_NotificationType)(void);                                                  /* PRQA S 3432 # JV-01 */
/* VAR type */
typedef VAR(uint32, AUTOMATIC) RamTst_TestDataType;

/* RamTst_BlockConfigType
** Data structure containing the set of configuration parameters for
** RAM Test Blocks.
*/
typedef struct STag_RamTst_BlockConfigType                                                                              /* PRQA S 3630 # JV-01 */
{
  /* Numeric ID of the Block */
  VAR(RamTst_NumberOfBlocksType, TYPEDEF) RamTstBlockId;
  /* End Address of the Block */
  VAR(uint32, TYPEDEF) RamTstEndAddress;
  /* Pattern to be filled into memory cell after destructive test of block */
  VAR(uint32, TYPEDEF) RamTstFillPattern;
  /* Start Address of the Block */
  VAR(uint32, TYPEDEF) RamTstStartAddress;
  /* RAM Test type of Block (Destructive or non destructive RAM Test) */
  VAR(RamTst_Block_TestType, TYPEDEF) RamTstTestPolicy;
} RamTst_BlockConfigType;

/** RamTst_AlgConfigType
**  Data structure containing the set of configuration parameters for each RAM
**  Test Algorithm.
*/
typedef struct STag_RamTst_AlgConfigType                                                                                /* PRQA S 3630 # JV-01 */
{
  /* Pointer to RAMTST Block Configuration */
  P2CONST(RamTst_BlockConfigType, RAMTST_VAR, TYPEDEF)
  LpRamTstBlockConfig;
  /* Numeric ID of the Algorithm */
  VAR(RamTst_AlgorithmType, TYPEDEF) RamTstAlgorithm;
  
  /* Absolute maximum value for number of cells */
  VAR(RamTst_NumberOfTestedCellsType, TYPEDEF)
  RamTstExtNumberOfTestedCells;
  /*
   *  maximum number of cells that can be tested in one cycle of
   *  background test
   */
  VAR(RamTst_NumberOfTestedCellsType, TYPEDEF)
  RamTstMaxNumberOfTestedCells;
  /* Number of Blocks configured for the Algorithm */
  VAR(RamTst_NumberOfBlocksType, TYPEDEF) RamTstNumberOfBlocks;
  /* Number Tested cells per cyclic call */
  VAR(RamTst_NumberOfTestedCellsType, TYPEDEF) RamTstNumberOfTestedCells;
} RamTst_AlgConfigType;


/** RamTst_ConfigType
**  Data structure containing the set of configuration parameters.
**  required for initializing the RAMTST Module
*/
typedef struct STag_RamTst_ConfigType
{
  /* Pointer to RAMTST Algorithm Configuration */
  P2CONST(RamTst_AlgConfigType, RAMTST_VAR, TYPEDEF) LpRamTstAlgConfig;
  /* Minimum no: of tested cells for one cycle of a background test */
  VAR(uint32, TYPEDEF) RamTstMinNumberOfTestedCells;
  /* Pointer to test completed notification function */
  VAR(RamTst_NotificationType, RAMTST_APPL_CODE) RamTstCompletedNotification;
  /* Pointer to error notification function */
  VAR(RamTst_NotificationType, RAMTST_APPL_CODE) RamTstErrorNotification;
} RamTst_ConfigType;

typedef struct STag_RamTst_GlobalAccessPointType
{
  /* Number of block ID in each core */
  volatile RamTst_NumberOfBlocksType *pNumBlockId;
  /* BlockID in Alg */
  volatile RamTst_NumberOfBlocksType *pBlock;
  /* Number of test cell (cell size)*/
  volatile RamTst_NumberOfTestedCellsType *pNumTestedCell;
  /* Address of cell  */
  volatile P2VAR(RamTst_TestDataType *, AUTOMATIC, RAMTST_VAR_FAST) pCellAddress;                                       /* PRQA S 3432 # JV-01 */
  /* ID of algorithms */
  volatile RamTst_AlgParamsIdType *pAlgParamsId;
  /* Status overall of algorithms */
  volatile RamTst_TestResultType *pOverallTestResult;
  /* Status of drvier Ramtst */
  volatile RamTst_ExecutionStatusType *pExecutionStatus;
  /* Record algorithms test */
  volatile RamTst_AlgorithmType *pAlgTest;
  /* Fill pattern of block parameter */
  volatile uint32 *pFillPattern;
  /* Address of buffer for save data */
  volatile RamTst_TestDataType *pTestBufferAddress;
  /* Result of block ID of algorithms */
  volatile RamTst_TestResultType *pTestResultBuffer;
} RamTst_GlobalAccessPointType;

#endif 
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
