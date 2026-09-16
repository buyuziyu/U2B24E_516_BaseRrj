/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = FlsTst_Types.h                                                                                      */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2023-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
 * 1.4.1:  30/06/2025  : Update SW-VERSION
 * 1.3.1:  31/03/2025  : Update SW-VERSION for RH850/Ver22.00.02 U2Bx-E
 * 1.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Relase   
 * 1.1.2:  31/10/2024  : As part of QAC 9.5.0 support, following changes are made:
 *                       1. Remove QAC message 1536
 * 1.1.0:  22/02/2024  : Update SW-VERSION to 1.1.0
 * 1.0.1:  18/10/2023  : Add QAC message 1536
 *         09/08/2023  : add FlsTst_GblCurrentTestFail to FlsTst_GVarProperties struct
 * 1.0.0:  17/03/2023  : Initial Version.
 */
/**********************************************************************************************************************/

#ifndef FLSTST_TYPES_H
#define FLSTST_TYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define FLSTST_TYPES_AR_RELEASE_MAJOR_VERSION    FLSTST_AR_RELEASE_MAJOR_VERSION
#define FLSTST_TYPES_AR_RELEASE_MINOR_VERSION    FLSTST_AR_RELEASE_MINOR_VERSION
#define FLSTST_TYPES_AR_RELEASE_REVISION_VERSION FLSTST_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define FLSTST_TYPES_SW_MAJOR_VERSION            FLSTST_SW_MAJOR_VERSION
#define FLSTST_TYPES_SW_MINOR_VERSION            FLSTST_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0750)    : A union type specifier has been defined.                                                     */
/* Rule                : MISRA C:2012 Rule-19.2, CWE Rule CWE-843                                                     */
/* JV-01 Justification : This union type is used to convert CRC value and there is no issue with this usage           */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* Type specifies the identification (ID) for a Flash block to be tested in
 * foreground mode
 */
typedef uint8 FlsTst_BlockIdFgndType;

/* State value returned by the API service FlsTst_GetCurrentState() */
typedef enum ETag_FlsTst_StateType
{
  FLSTST_UNINIT = 0, /* The Flash Test is not initialized or not usable */
  FLSTST_INIT,       /* The Flash Test is initialized and ready to be started */
  FLSTST_RUNNING,    /* The Flash Test is currently running */
  FLSTST_ABORTED,    /* The Flash Test is aborted */
  FLSTST_SUSPENDED   /* The Flash Test is waiting to be resumed or is waiting to start foreground mode test */
} FlsTst_StateType;

/* Return type of API service FlsTst_GetResultFgnd() */
typedef enum ETag_FlsTst_TestResultFgndType
{
  FLSTST_NOT_TESTED = 0,  /* There is no result available */
  FLSTST_OK,              /* The last Flash Test has been tested with OK result */
  FLSTST_NOT_OK           /* The last Flash Test has been tested with NOT_OK result */
} FlsTst_TestResultFgndType;

/* Common test result for foregorund and background test */
typedef enum ETag_FlsTst_TestResultType
{
  FLSTST_RESULT_NOT_TESTED = 0,  /* There is no result available */
  FLSTST_RESULT_OK,              /* The last Flash Test has been tested with OK result */
  FLSTST_RESULT_NOT_OK           /* The last Flash Test has been tested with NOT_OK result */
} FlsTst_TestResultType;

/* This type shall specify the CRC algorithm that can be selected */
typedef enum ETag_FlsTst_TestAlgorithmType
{
  FLSTST_8BIT_2F = 0,
  FLSTST_8BIT_SAE_J1850,
  FLSTST_15BIT_CRC15CAN,
  FLSTST_16BIT_CCITT16,
  FLSTST_16BIT_BAICHEVA00,
  FLSTST_16BIT_ARC,
  FLSTST_32BIT_CRC32,
  FLSTST_32BIT_CRC32_REVPOLY,
  FLSTST_32BIT_CRC32C,
  FLSTST_32BIT_CRC32P4,
  FLSTST_64BIT_CRC64ECMA
} FlsTst_TestAlgorithmType;

/* State of background test */
typedef enum ETag_FlsTst_BgndStateType
{
  FLSTST_BGND_CHECK_INIT = 0,   /* Initialized state */
  FLSTST_BGND_CHECK_INPROGRESS, /* Inprogress state */
  FLSTST_BGND_CHECK_COMPLETE    /* Complete state */
} FlsTst_BgndStateType;

/* Return type of API service FlsTst_GetTestResultBgnd () */
typedef struct STag_FlsTst_TestResultBgndType                                                                           
{
  /* Current value of FlsTstTestIntervalId, which is incremented by each new start of an test interval */
  uint32 ulTestIntervalId;
  /* Last background test result */
  FlsTst_TestResultType enTestResultBgnd;
} FlsTst_TestResultBgndType;

/* Specific error information monitored in the Flash test module */
typedef struct STag_FlsTst_ErrorDetailsType                                                                             
{
  /* ECC test result for Global area */
  uint8 ucCFGlobalEccStatus;
  /* ECC test result for Bank area */
  uint8 ucCFBankEccStatus;
  /* ECC test failed address for Global area during the ECC circuitry test */
  uint32 ulCFGlobalEccFaultAddress;
  /* ECC test failed address for Bank area during the ECC circuitry test */
  uint32 ulCFBankEccFaultAddress;
} FlsTst_ErrorDetailsType;

/* Test signature in foreground mode in the Flash test module */
typedef struct STag_FlsTst_TestSignatureFgndType                                                                        
{
  /* Signature value in case of CRC8, CRC16, CRC32 or lower bytes of CRC64 */ 
  uint32 ulSignatureValue; 
  /* Higher byte of signature value in case of CRC64 */
  uint32 ulSignatureValue_H;
} FlsTst_TestSignatureFgndType;

/* Test signature in background mode in the Flash test module */
typedef struct STag_FlsTst_TestSignatureBgndType                                                                        
{
  /* Last test interval id of the background test */
  uint32 ulTestIntervalId;
  /* Signature value in case of CRC8, CRC16, CRC32 or lower bytes of CRC64 */ 
  uint32 ulSignatureValue; 
  /* Higher byte of signature value in case of CRC64 */
  uint32 ulSignatureValue_H;
} FlsTst_TestSignatureBgndType;

/* This type shall hold all the global variables used in the module */
typedef struct STag_FlsTst_GVarProperties                                                                               
{
  /* Variable to store the calculated CRC value */
  uint32 FlsTst_GulCalculatedCrc;
  /* Variable to store the higher bytes of calculated CRC64 value */
  uint32 FlsTst_GulCalculatedCrc_H;
  /* Variable to store the test block start address */
  uint32 FlsTst_GulReadAddress;
  /* Variable to store the index of the test block based on priority */
  uint32 FlsTst_GulBgndConfigIndex;
  /* Variable to store the internal background check state */
  FlsTst_BgndStateType FlsTst_GenBgndCheckState;
  /* Number of byte of CRC result */
  uint8 FlsTst_GucByteToProcess;
  /* Flag to indicate overall status of current test is not ok */
  #if (FLSTST_TEST_RESULT_SIGNATURE != STD_ON)
  boolean FlsTst_GblCurrentTestFail;
  #endif
} FlsTst_GVarProperties;

/* This type shall specify implementation specific block in the Flash test module */
typedef struct STag_FlsTstBlock_ConfigType                                                                              /* PRQA S 3630 # JV-01 */
{
  /* Foreground Test: Index identifies block to be tested by FlsTst_StartFgnd
   * Background Test: The scheduling for background test shall follow an order
   * defined by this index
   */
  uint32 ulFlsTstBlockIndex;
  /* Start Address of the Flash block */
  uint32 ulFlsTstBlockBaseAddress;
  /* Flash test block size */
  uint32 ulFlsTstBlockSize;
  /* Address of the signature reference value of the Flash test block */
  uint32 ulFlsTstSignatureAddress;
  /* Test algorithm for foreground mode and background mode */
  FlsTst_TestAlgorithmType enFlsTstTestAlgorithm;
  /* To indicate address dependent CRC */
  uint8 ucFlsTstAddressDepdntCrc;
} FlsTstBlock_ConfigType;

/* This type of external data structure shall contain the initialization data for the Flash Test */
typedef struct STag_FlsTst_ConfigType                                                                                   
{
  /* Database start value */
  uint32 ulStartOfDbToc;
  #if (FLSTST_TEST_COMPLETED_NOTIFICATION_SUPPORTED == STD_ON)
  /* Pointer to test complete callback notification  */
  P2FUNC(void, FLSTST_APPL_CODE, pTestCompleteNotifyFunc)(void);                                                        /* PRQA S 3432 # JV-01 */
  #endif
  /* Pointer to FlsTstBlockBgndConfigType configuration */
  P2CONST(FlsTstBlock_ConfigType, AUTOMATIC, FLSTST_CONFIG_CONST) pFlsTstBgndBlkConfig;
  /* Pointer to FlsTstBlockFgndConfigType configuration */
  P2CONST(FlsTstBlock_ConfigType, AUTOMATIC, FLSTST_CONFIG_CONST) pFlsTstFgndBlkConfig;
  /* Number of test blocks available for the background test */
  uint32 ulFlsTstMaxBgndBlkNo;
  /* Number of test blocks available for the foreground test */
  uint32 ulFlsTstMaxFgndBlkNo;
} FlsTst_ConfigType;

/* This type shall specify the storage of CRC value */
typedef union UTag_FlsTst_CrcConvert                                                                                    
{                                                                                                                       /* PRQA S 0750 # JV-01 */
  /* To get CRC32 value*/
  uint32 ulCrc32Data;
  /* To get CRC16 value*/
  uint16 usCrc16Data;
  /* To get CRC8 value*/
  uint8 ucCrc8Data;
  /* To store crc value */
  uint8 ucCrcData4[4];
} FlsTst_CrcConvert;

#endif /* FLSTST_TYPES_H */

/***********************************************************************************************************************
**                                                    End Of File                                                     **
***********************************************************************************************************************/

