/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_Scheduler.h                                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the external declarations of global SPI Driver functions                                        */
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
 * 2.5.1:  30/06/2025  : Remove SW-VERSION in file header
 * 2.5.0:  30/06/2025  : Update SW-VERSION for RH850/Ver21.01.00(D) U2Ax release
 * 2.4.0:  31/05/2025  : Update SW-VERSION for RH850/Ver21.01.01 U2Cx release
 * 2.3.2:  30/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 * 2.1.1:  28/08/2024  : Support AR2211: update macro file definition,
 *                     : Remove QAC messages (2:0841) to fix redundant QAC messages
 *                     : Increase SW-VERSION up to 2.0.3
 *                     : Remove QAC message 1534, 1535, 1536
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  22/10/2023  : Update QAC message 1534, 1536 support Amendment 2
 *                       Update SW-VERSION to 2.0.1
 * 2.0.0:  28/08/2023  : Remove SPI_INSTANCE_INDEX
 *         25/07/2023  : Update from "Spi_Mapping.h to "Spi_MemMap.h".
 * 1.4.2:  02/03/2022  : Merge QAC
 * 1.3.2:  06/09/2021  : Update QAC contents
 *         30/08/2021  : Update header file macro to call file multiple times
 *                       Update to include Spi_Mapping.h instead of Spi_MemMap.h
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END) 
 * 1.2.0:  30/07/2020  : Release
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:1039)    : Treating array of length one as potentially flexible member.                                 */
/* Rule                : CERTCCM DCL38, MISRA C:2012 Dir-1.1, Rule-1.2                                                */
/* JV-01 Justification : Use array of length as the final member has no problem by manual reviewing.                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#ifndef SPI_SCHEDULER_H
#define SPI_SCHEDULER_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define SPI_SCHEDULER_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION
#define SPI_SCHEDULER_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION
#define SPI_SCHEDULER_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION
/* File version information */
#define SPI_SCHEDULER_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION
#define SPI_SCHEDULER_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Invalid Sequence index. Valid range is 0..254. */
#define SPI_INVALID_SEQUENCE                      ((Spi_SequenceType)255U)

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* Status variables for each SubSequence  */
typedef struct STag_Spi_SubSeqStatusType
{
  /* Remain Job count in this Queue */
  uint16 usRemainJobCount;
  /* List connectors in this Queue */
  Spi_SequenceType aaNext[SPI_MAX_PRIORITY + 1U];
  Spi_SequenceType aaPrev[SPI_MAX_PRIORITY + 1U];
} Spi_SubSeqStatusType;

/* Status for each Sequence */
typedef struct STag_Spi_SeqStatusType
{
  /* Sequence result status */
  Spi_SeqResultType enResult;
  /* Whether any SubSequence failed */
  boolean blFailed;
  #if (SPI_LEVEL_DELIVERED != SPI_LEVEL_0)
  #if (SPI_CANCEL_API == STD_ON)
  /* Whether cancel is requested */
  boolean blCancelRequested;
  #endif
  #if ((SPI_CANCEL_API == STD_ON) || (SPI_FORCE_CANCEL_API == STD_ON))
  /* Whether any SubSequence has been canceled */
  boolean blCanceled;
  #endif
  #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
  /* Whether any SubSequence has been started */
  boolean blStarted;
  #endif
  #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
  /* Active bit array for each SubSequence */
  uint32 ulActiveSubSequences;
  #endif
  /* Status for each Queue */
  Spi_SubSeqStatusType aaSubSeqs[SPI_MAX_QUEUE];                                                                        /* PRQA S 1039 # JV-01 */
  #endif /* (SPI_LEVEL_DELIVERED != SPI_LEVEL_0) */
} Spi_SeqStatusType;

/* Status for each Job */
typedef struct STag_Spi_JobStatusType
{
  /* Job result status */
  Spi_JobResultType enResult;
} Spi_JobStatusType;

/* Structure of Queue */
typedef struct STag_Spi_QueueType
{
  /* Existence flags for each priority */
  uint8 ucExists;
  /* The index of ongoing sequence */
  Spi_SequenceType ucOngoingSeqIndex;
  /* List connectors of the top job for each priority */
  Spi_SequenceType aaTop[SPI_MAX_PRIORITY + 1U];
  /* List connectors of the tail job for each priority */
  Spi_SequenceType aaTail[SPI_MAX_PRIORITY + 1U];
} Spi_QueueType;

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define SPI_START_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))

extern FUNC(void, SPI_PRIVATE_CODE) Spi_StartTransmission(uint32 LulSeqIndex);

extern FUNC(void, SPI_PRIVATE_CODE) Spi_ProcessSequence(const uint32 LulHWUnitIndex);

#if ((SPI_CANCEL_API == STD_ON) || (SPI_FORCE_CANCEL_API == STD_ON))
extern FUNC(void, SPI_PRIVATE_CODE) Spi_CancelSequence(const uint32 LulSeqIndex, const boolean LblIsForceStop);
#endif

extern FUNC(void, SPI_PRIVATE_CODE) Spi_RemoveFromQueue(const uint32 LulQueueIndex, const uint32 LulSeqIndex);

#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))

extern FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_TransmitSyncSequence(const uint32 LulSeqIndex);

#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

extern FUNC(void, SPI_PRIVATE_CODE)
    Spi_TurnOffHWUnit(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig);

#define SPI_STOP_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"

#endif /* SPI_SCHEDULER_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
