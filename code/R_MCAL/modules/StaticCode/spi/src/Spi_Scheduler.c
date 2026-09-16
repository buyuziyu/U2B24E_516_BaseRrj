/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Spi_Scheduler.c                                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* Copyright(c) 2020-2025 Renesas Electronics Corporation.                                                            */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains Low level driver function definitions of the SPI Driver                                         */
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
 * 2.3.1:  31/03/2025  : Add new QAC msg: 3834 and remove QAC msg: 3383 to support QAC 11.6.0
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.3:  31/10/2024  : Update SW-VERSION up to 2.1.3
 * 2.1.2:  30/09/2024  : Update SW-VERSION up to 2.1.2
 *                     : Remove QAC messages (2:0857), (2:2934), (2:2814), (2:2824), (1:1532), (2:2844)
 *                       to fix redundant QAC messages
 *                     : Add new QAC messages 2877
 *                     : Increase SW-VERSION up to 2.0.3
 *                       In function Spi_StartTransmission, Spi_CancelSequence: Change SPI_MAX_QUEUE to 
 *                       Spi_GpConfigPtr->ucNoOfQueues
 * 2.1.0:  27/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.2:  14/12/2023  : Update SW-VERSION to 2.0.2
 * 2.0.1:  23/10/2023  : Updated the condition check cancel request to set the canceled flag in Spi_CheckSeqFinish
 *                       Update SW-VERSION to 2.0.1
 *                       Update QAC message 3415 support Amendment 2  
 * 2.0.0:  25/07/2023  : Update Exclusive_Area of SPI_ENTER_CRITICAL_SECTION/SPI_EXIT_CRITICAL_SECTION
 *         19/06/2023  : Added SPI_LEVEL_DELIVERED == SPI_LEVEL_1 in functions Spi_ProcessJob, Spi_TurnOffHWUnit.
 * 1.5.0:  07/04/2023  : Update
 *                       Spi_MaskSequenceInterrupts: Remove all internal function in Function invoked
 *                       Spi_CancelSequence, Spi_CheckSeqFinish: Remove Spi_GpConfigPtr in Global variable field
 *                       Spi_PopFromQueue: Change the Return parameter to boolean in description field
 * 1.4.3:  20/05/2022  : Remove else do nothing
 *                       Add QAC message
 * 1.3.2:  06/09/2021  : Update QAC contents
 *         04/09/2021  : Replace the inclusion of Spi_MemMap.h with Spi_Mapping.h
 *                       Update precondition for calling SPI_DEM_REPORT_ERROR
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END) 
 *         19/05/2021  : Update QAC contents.
 * 1.2.0:  30/07/2020  : Release
 *         28/07/2020  : Add QAC 9.3.1 comment.
 * 1.1.0:  19/06/2020  : Release
 * 1.0.2:  15/06/2020  : 1. Remove HW Unit activation in Spi_StartTransmission
 *                       2. Clear HW Unit and activate next HW Unit for next job in, de-activate HW unit for last job
 *                          of the queue in Spi_ProcessSequence.
 *                       3. Spi_CancelSequence, Spi_CheckSeqFinish: Remove loops for checking if the same hw unit is
 *                          used with other sequences in the queue.
 * 1.0.1:  22/05/2020  : Update QAC message and MISRA-C Rule violation.
 * 1.0.0:  24/03/2020  : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
#include "Spi.h"
#include "Spi_Ram.h"
#include "Spi_Scheduler.h"
#include "Dem.h"

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define SPI_SCHEDULER_C_AR_RELEASE_MAJOR_VERSION    SPI_AR_RELEASE_MAJOR_VERSION_VALUE
#define SPI_SCHEDULER_C_AR_RELEASE_MINOR_VERSION    SPI_AR_RELEASE_MINOR_VERSION_VALUE
#define SPI_SCHEDULER_C_AR_RELEASE_REVISION_VERSION SPI_AR_RELEASE_REVISION_VERSION_VALUE

/* File version information */
#define SPI_SCHEDULER_C_SW_MAJOR_VERSION            SPI_SW_MAJOR_VERSION_VALUE
#define SPI_SCHEDULER_C_SW_MINOR_VERSION            SPI_SW_MINOR_VERSION_VALUE

/***********************************************************************************************************************
**                                                   Version Check                                                    **
***********************************************************************************************************************/
#if (SPI_SCHEDULER_AR_RELEASE_MAJOR_VERSION != SPI_SCHEDULER_C_AR_RELEASE_MAJOR_VERSION)
#error "Spi_Scheduler.c : Mismatch in Release Major Version"
#endif

#if (SPI_SCHEDULER_AR_RELEASE_MINOR_VERSION != SPI_SCHEDULER_C_AR_RELEASE_MINOR_VERSION)
#error "Spi_Scheduler.c : Mismatch in Release Minor Version"
#endif

#if (SPI_SCHEDULER_AR_RELEASE_REVISION_VERSION != SPI_SCHEDULER_C_AR_RELEASE_REVISION_VERSION)
#error "Spi_Scheduler.c : Mismatch in Release Revision Version"
#endif

#if (SPI_SCHEDULER_SW_MAJOR_VERSION != SPI_SCHEDULER_C_SW_MAJOR_VERSION)
#error "Spi_Scheduler.c : Mismatch in Software Major Version"
#endif

#if (SPI_SCHEDULER_SW_MINOR_VERSION != SPI_SCHEDULER_C_SW_MINOR_VERSION)
#error "Spi_Scheduler.c : Mismatch in Software Minor Version"
#endif

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3218)    : File scope static, '%s', is only accessed in one function.                                   */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.9, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : By moving the array into the function, the stack size used will be more, hence this is       */
/*                       defined outside.                                                                             */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3383)    : Cannot identify wraparound guard for unsigned arithmetic expression.                         */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : It can still result in values that are out of range for the intended use, as intuitive       */
/*                       "invariants" may not hold                                                                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:3384)    : Cannot identify wraparound guard for dependent unsigned arithmetic expression.               */
/* Rule                : CERTCCM INT30                                                                                */
/* JV-01 Justification : In order to effectively guard against overflow and wraparound at all stages, the expression  */
/*                       should be split up into individual dynamic operations, with their own guards where applicable*/
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3387)    : A full expression containing an increment (++) or decrement (--) operator should have no     */
/*                       potential side effects other than that caused by the increment or decrement operator.        */
/* Rule                : MISRA C:2012 Rule-13.3                                                                       */
/* JV-01 Justification : An increment/decrement is created a side affect. In this case it's accessing a volatile      */
/*                       object. This can be accepted.                                                                */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (7:0404)    : More than one read access to volatile objects between sequence points.                       */
/* Rule                : CERTCCM EXP10, EXP30, MISRA C:2012 Rule-1.3, Rule-13.2, CWE Rule CWE-682, CWE-758, CWE-737   */
/* JV-01 Justification : This is to get element in array of struct, volatile of counter variable of 'for' loop is     */
/*                       used to ensure no optimization. It is accepted                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1505)    : The function '%1s' is only referenced in the translation unit where it is defined.           */
/* Rule                : CERTCCM DCL19, MISRA C:2012 Rule-8.7, CWE Rule CWE-398, CWE-569                              */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3678)    : The object referenced by '%1s' is not modified through it, so '%1s' could be declared with   */
/*                       type '%2s'.                                                                                  */
/* Rule                : MISRA C:2012 Rule-8.13                                                                       */
/* JV-01 Justification : This is accepted. It just an advise for  improve safety by reducing the possibility that     */
/*                       the referenced data is unintentionally modified through an unexpected alias and improves     */
/*                       clarity by indicating that the referenced data is not intended to be modified through this   */
/*                       alias or those depending on it                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:1339)    : Evaluating the address of the parameter '%s'.                                                */
/* Rule                : MISRA C:2012 Rule-17.8                                                                       */
/* JV-01 Justification : This is accepted, there is no issue at this LOC with current implementation                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2995)    : The result of this logical operation is always 'true'.                                       */
/* Rule                : MISRA C:2012 Rule-2.2, CWE Rule CWE-561, CWE-633                                             */
/* JV-01 Justification : Depending on device configuration, there is case where the 'if' will return 'false'.         */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:2983)    : This assignment is redundant. The value of this object is never subsequently used.           */
/* Rule                : CERTCCM MSC07, MSC13, MISRA C:2012 Rule-2.2, CWE Rule CWE-14, CWE-398, CWE-561, CWE-563      */
/*                       CWE-569, CWE-633                                                                             */
/* JV-01 Justification : The value is to increment the pointer to the next item.                                      */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3416)    : Logical operation performed on expression with persistent side effects.                      */
/* Rule                : CERTCCM EXP45, CWE Rule CWE-398, CWE-569, CWE-737                                            */
/* JV-01 Justification : Logical operation accesses volatile object which is a register access. All register          */
/*                       addresses are generated with volatile qualifier. There is no impact on the functionality     */
/*                       due to this conditional check for mode change.                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:2004)    : No concluding 'else' exists in this 'if'-'else'-'if' statement.                              */
/* Rule                : CERTCCM EXP02, MISRA C:2012 Rule-15.7, CWE Rule CWE-398, CWE-569                             */
/* JV-01 Justification : The "else"statement with empty content is removed to improve readability.                    */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (3:3415)    : Right hand operand of '&&' or '||' is an expression with possible side effects.              */
/* Rule                : CERTCCM EXP02, MISRA C:2012 Rule-13.5, CWE Rule CWE-398, CWE-768, CWE-569                    */
/* JV-01 Justification : Although it is a volatile object, it is not a direct access to the HW register, and          */
/*                       there is no side effect.                                                                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (6:2877)    : This loop will never be executed more than once.                                             */
/* Rule                : CERTCCM MSC07, MISRA C:2012 Dir-4.1, CWE Rule CWE-670                                        */
/* JV-01 Justification : This loop will only be executed at least once, depends on user configuration.                */
/*       Verification  : This is Hardware Specification, X2x only provides 1 Unit. So it is not having any impact.    */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                    Global Data                                                     **
***********************************************************************************************************************/
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))

#define SPI_START_SEC_CONST_8
#include "Spi_MemMap.h"

/* Lookup table to get the highest bit position */
STATIC CONST(uint8, SPI_CONST) Spi_GaaPriorityTable[] =                                                                 /* PRQA S 3218 # JV-01 */
{
  0U, /* 0x00(unavailable) */
  0U, /* 0x01: 00000001 */
  1U, /* 0x02: 00000010 */
  1U, /* 0x03: 00000011 */
  2U, /* 0x04: 00000100 */
  2U, /* 0x05: 00000101 */
  2U, /* 0x06: 00000110 */
  2U, /* 0x07: 00000111 */
  3U, /* 0x08: 00001000 */
  3U, /* 0x09: 00001001 */
  3U, /* 0x0A: 00001010 */
  3U, /* 0x0B: 00001011 */
  3U, /* 0x0C: 00001100 */
  3U, /* 0x0D: 00001101 */
  3U, /* 0x0E: 00001110 */
  3U  /* 0x0F: 00001111 */
};

#define SPI_STOP_SEC_CONST_8
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

/***********************************************************************************************************************
**                                                Function Definitions                                                **
***********************************************************************************************************************/
#define SPI_START_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))

/* Prototype of functions which are used in this file only */
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_PushToQueue(const uint32 LulQueueIndex, const uint32 LulSeqIndex);

STATIC FUNC(boolean, SPI_PRIVATE_CODE)
    Spi_PopFromQueue(const uint32 LulQueueIndex, CONSTP2VAR(uint32, AUTOMATIC, AUTOMATIC) LpSeqIndex,                   /* PRQA S 3432 # JV-01 */
                     CONSTP2VAR(uint32, AUTOMATIC, AUTOMATIC) LpJobIndex);                                              /* PRQA S 3432 # JV-01 */

STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_InvokeNotifications(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpPrevJobConfig,
                            CONSTP2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpPrevSeqConfig,
                            const boolean LblSeqFinished
                            #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
                            ,
                            CONSTP2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpNextSeqConfig,
                            const boolean LblSeqAlreadyStarted
                            #endif
    );

STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_ProcessJob(const uint32 LulJobIndex);

STATIC FUNC(boolean, SPI_PRIVATE_CODE) Spi_CheckSeqFinish(const uint32 LulQueueIndex, const uint32 LulSeqIndex);

#if ((SPI_FORCE_CANCEL_API == STD_ON) && ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)))
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MaskSequenceInterrupts(CONSTP2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSeqConfig,
                               const boolean LblMask);
#endif

#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))

/***********************************************************************************************************************
** Function Name       : Spi_PushToQueue
**
** Service ID          : Not Applicable
**
** Description         : This function pushes a Sequence to a Queue structure
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant for different Queue. Non-Reentrant for same Queue
**
** Input Parameters    : LulQueueIndex - Index of a Queue
**                       LulSeqIndex   - Sequence ID
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : Queue must be initialized
**
** Global Variable     : Spi_GaaQueue, Spi_GpFirstSeq, Spi_GpFirstJob, Spi_GaaSeqStatus
**
** Function Invoked    : None
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_030, SPI_DUD_ACT_030_GBL001, SPI_DUD_ACT_030_GBL002, SPI_DUD_ACT_030_GBL003,
** Reference ID        : SPI_DUD_ACT_030_GBL004, SPI_DUD_ACT_030_GBL005
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_PushToQueue(const uint32 LulQueueIndex, const uint32 LulSeqIndex)
{
  volatile P2VAR(Spi_QueueType, AUTOMATIC, SPI_VAR_NO_INIT) LpQueue;                                                    /* PRQA S 3432 # JV-01 */
  P2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSeqConfig;
  P2CONST(Spi_SubSeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSubSeqConfig;
  uint32 LulHighestJobIndex;
  uint32 LulPriority;
  uint32 LulMaxPriority;
  uint32 LulMinPriority;
  Spi_SequenceType LucLastSeq;

  LpQueue = &Spi_GaaQueue[LulQueueIndex];
  LpSeqConfig = &Spi_GpFirstSeq[LulSeqIndex];
  LpSubSeqConfig = &LpSeqConfig->aaSubSeqs[LulQueueIndex];
  /* Get index of the Job which has the highest priority */
  LulHighestJobIndex = LpSubSeqConfig->pJobList[0U];
  /* Get the highest priority among remaining Jobs */
  LulMaxPriority = Spi_GpFirstJob[LulHighestJobIndex].ucJobPriority;
  #if (SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
  if (SPI_TRUE == LpSeqConfig->blInterruptible)
  {
    LulMinPriority = Spi_GpFirstJob[LpSubSeqConfig->pJobList[LpSubSeqConfig->usNoOfJobs - 1U]].ucJobPriority;           /* PRQA S 3383 # JV-01 */
  }
  else
  #endif
  {
    /* If the Sequence is non-interruptible, enqueue the first Job only */
    LulMinPriority = LulMaxPriority;
  }
  /* Add this Sequence to the end of each priority list */
  for (LulPriority = LulMinPriority; LulPriority <= LulMaxPriority; LulPriority++)                                      /* PRQA S 2877 # JV-01 */
  {
    /* If Seq has Job which has this priority, add it to the end of the list */
    if (0UL != (LpSubSeqConfig->ucUsingPriorities & (1UL << LulPriority)))
    {
      if (0UL == (LpQueue->ucExists & (1UL << LulPriority)))
      {
        /* If the list is empty, add this Sequence to the Top of the list */
        LpQueue->aaTop[LulPriority] = (Spi_SequenceType)LulSeqIndex;
        LpQueue->ucExists = (uint8)(LpQueue->ucExists | (1UL << LulPriority));
      }
      else
      {
        /* If the list isn't empty, add this Sequence to the end of the list */
        LucLastSeq = LpQueue->aaTail[LulPriority];
        Spi_GaaSeqStatus[LucLastSeq].aaSubSeqs[LulQueueIndex].aaNext[LulPriority] = (Spi_SequenceType)LulSeqIndex;
        Spi_GaaSeqStatus[LulSeqIndex].aaSubSeqs[LulQueueIndex].aaPrev[LulPriority] = (Spi_SequenceType)LucLastSeq;
      }
      LpQueue->aaTail[LulPriority] = (Spi_SequenceType)LulSeqIndex;
    } /* else No action required */
  }
  /* Initialize number of Jobs remain in the Queue */
  Spi_GaaSeqStatus[LulSeqIndex].aaSubSeqs[LulQueueIndex].usRemainJobCount = LpSubSeqConfig->usNoOfJobs;
}

/***********************************************************************************************************************
** Function Name       : Spi_PopFromQueue
**
** Service ID          : Not Applicable
**
** Description         : This function pops a Job which should be performed next from a Queue.
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant for different Queue. Non-Reentrant for same Queue
**
** Input Parameters    : LulQueueIndex - Index of a Queue
**
** Output Parameters   : LpSeqIndex    - Pointer to receive Sequence ID
**                       LpJobIndex    - Pointer to receive Job ID
**
** Return parameter    : boolean
**
** Preconditions       : Queue must be initialized
**
** Global Variable     : Spi_GaaQueue, Spi_GpFirstSeq, Spi_GaaPriorityTable, Spi_GpFirstJob, Spi_GaaSeqStatus
**
** Function Invoked    : None
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_031, SPI_DUD_ACT_031_GBL001, SPI_DUD_ACT_031_GBL002, SPI_DUD_ACT_031_GBL003,
** Reference ID        : SPI_DUD_ACT_031_GBL004
***********************************************************************************************************************/
STATIC FUNC(boolean, SPI_PRIVATE_CODE)
    Spi_PopFromQueue(const uint32 LulQueueIndex, CONSTP2VAR(uint32, AUTOMATIC, AUTOMATIC) LpSeqIndex,                   /* PRQA S 3432 # JV-01 */
                     CONSTP2VAR(uint32, AUTOMATIC, AUTOMATIC) LpJobIndex)                                               /* PRQA S 3432 # JV-01 */
{
  volatile P2VAR(Spi_QueueType, AUTOMATIC, SPI_VAR_NO_INIT) LpQueue;                                                    /* PRQA S 3432 # JV-01 */
  volatile P2VAR(Spi_SubSeqStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpSubSeqStat;                                        /* PRQA S 3432 # JV-01 */
  P2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSeqConfig;
  P2CONST(Spi_SubSeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSubSeqConfig;
  boolean LblIsAvailable;
  uint32 LulPriority;
  boolean LblRemove;

  LpQueue = &Spi_GaaQueue[LulQueueIndex];
  if (0U == LpQueue->ucExists)
  {
    /* There is no Job in this Queue */
    LblIsAvailable = SPI_FALSE;
  }
  else
  {
    LblIsAvailable = SPI_TRUE;
    if ((SPI_INVALID_SEQUENCE == LpQueue->ucOngoingSeqIndex)                                                            /* PRQA S 0404 # JV-01 */
    #if (SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
        || (SPI_TRUE == Spi_GpFirstSeq[LpQueue->ucOngoingSeqIndex].blInterruptible)                                     /* PRQA S 3416, 3415 # JV-01, JV-01 */
    #endif
    )
    {
      /* If no Seq is on-going or interruptible Seq is on-going,
      use a seq that is in the top of the highest priority list */
      LulPriority = Spi_GaaPriorityTable[LpQueue->ucExists];
      *LpSeqIndex = LpQueue->aaTop[LulPriority];
      LpQueue->ucOngoingSeqIndex = (Spi_SequenceType)*LpSeqIndex;
      LpSeqConfig = &Spi_GpFirstSeq[*LpSeqIndex];
      LpSubSeqConfig = &LpSeqConfig->aaSubSeqs[LulQueueIndex];
    }
    else
    {
      /* If non-interruptible Seq is on-going, continue the current Seq */
      *LpSeqIndex = LpQueue->ucOngoingSeqIndex;
      LpSeqConfig = &Spi_GpFirstSeq[*LpSeqIndex];
      LpSubSeqConfig = &LpSeqConfig->aaSubSeqs[LulQueueIndex];
      LulPriority = Spi_GpFirstJob[LpSubSeqConfig->pJobList[0U]].ucJobPriority;
    }
    LpSubSeqStat = &Spi_GaaSeqStatus[*LpSeqIndex].aaSubSeqs[LulQueueIndex];

    *LpJobIndex = LpSubSeqConfig->pJobList[LpSubSeqConfig->usNoOfJobs - LpSubSeqStat->usRemainJobCount];

    LpSubSeqStat->usRemainJobCount--;                                                                                   /* PRQA S 3384, 3387 # JV-01, JV-01 */
    /* Check whether all jobs in this sequence are completed */
    if (0U == LpSubSeqStat->usRemainJobCount)
    {
      /* If there is no remaining Job in this Sequence, remove it */
      LblRemove = SPI_TRUE;
    }
    else
    {
      /*
       * If this sequence is interruptible and the next Job has different priority,
       * remove this sequence from this priority list.
       */
      #if (SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
      if ((SPI_TRUE == LpSeqConfig->blInterruptible) &&                                                                 /* PRQA S 0404 # JV-01 */
          (Spi_GpFirstJob[*LpJobIndex].ucJobPriority !=                                                                 /* PRQA S 3416, 3415 # JV-01, JV-01 */
           Spi_GpFirstJob[LpSubSeqConfig->pJobList[LpSubSeqConfig->usNoOfJobs - LpSubSeqStat->usRemainJobCount]]        /* PRQA S 3416, 3415 # JV-01, JV-01 */
               .ucJobPriority))
      {
        LblRemove = SPI_TRUE;
      }
      else
      #endif
      {
        LblRemove = SPI_FALSE;
      }
    }
    if (SPI_TRUE == LblRemove)
    {
      /* Remove Sequence from this priority list */
      if (LpQueue->aaTail[LulPriority] == LpQueue->aaTop[LulPriority])                                                  /* PRQA S 0404 # JV-01 */
      {
        /* If there is no sequence in this list, clear exist flag */
        LpQueue->ucExists = (uint8)(LpQueue->ucExists & ~(1UL << LulPriority));
      }
      else
      {
        /* Update top pointer to the next Sequence */
        LpQueue->aaTop[LulPriority] = LpSubSeqStat->aaNext[LulPriority];
      }
      /* Since Sequence finished, set on-going Sequence as invalid. */
      LpQueue->ucOngoingSeqIndex = SPI_INVALID_SEQUENCE;
    } /* else No action required */
  }

  return LblIsAvailable;
}

/***********************************************************************************************************************
** Function Name       : Spi_RemoveFromQueue
**
** Service ID          : Not Applicable
**
** Description         : This function removes a Sequence from a Queue.
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant for different Queue. Non-Reentrant for same Queue
**
** Input Parameters    : LulQueueIndex - Index of a Queue
**                       LulSeqIndex   - Sequence ID
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : Specified Sequence must be enqueued.
**
** Global Variable     : Spi_GaaQueue, Spi_GpFirstSeq, Spi_GaaSeqStatus, Spi_GpFirstJob
**
** Function Invoked    : None
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_032, SPI_DUD_ACT_032_GBL001, SPI_DUD_ACT_032_GBL002, SPI_DUD_ACT_032_GBL003,
** Reference ID        : SPI_DUD_ACT_032_GBL004, SPI_DUD_ACT_032_GBL005
***********************************************************************************************************************/
FUNC(void, SPI_PRIVATE_CODE) Spi_RemoveFromQueue(const uint32 LulQueueIndex, const uint32 LulSeqIndex)                  /* PRQA S 1505 # JV-01 */
{
  volatile P2VAR(Spi_QueueType, AUTOMATIC, SPI_VAR_NO_INIT) LpQueue;                                                    /* PRQA S 3432 # JV-01 */
  P2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSeqConfig;
  P2CONST(Spi_SubSeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSubSeqConfig;
  volatile P2VAR(Spi_SubSeqStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpSubSeqStat;                                        /* PRQA S 3432, 3678 # JV-01, JV-01 */
  uint32 LulPriority;
  uint32 LulMaxPriority;
  uint32 LulMinPriority;

  LpQueue = &Spi_GaaQueue[LulQueueIndex];
  LpSeqConfig = &Spi_GpFirstSeq[LulSeqIndex];
  LpSubSeqConfig = &LpSeqConfig->aaSubSeqs[LulQueueIndex];
  LpSubSeqStat = &Spi_GaaSeqStatus[LulSeqIndex].aaSubSeqs[LulQueueIndex];
  /* Get the highest priority among remaining Jobs */
  #if (SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON)
  if (SPI_TRUE == LpSeqConfig->blInterruptible)
  {
    LulMaxPriority =                                                                                                    /* PRQA S 0404 # JV-01 */
        Spi_GpFirstJob[LpSubSeqConfig->pJobList[LpSubSeqConfig->usNoOfJobs - LpSubSeqStat->usRemainJobCount]]
            .ucJobPriority;
    LulMinPriority = Spi_GpFirstJob[LpSubSeqConfig->pJobList[LpSubSeqConfig->usNoOfJobs - 1U]].ucJobPriority;           /* PRQA S 3383 # JV-01 */
  }
  else
  #endif
  {
    LulMaxPriority = Spi_GpFirstJob[LpSubSeqConfig->pJobList[0U]].ucJobPriority;
    LulMinPriority = LulMaxPriority;
  }

  /* Remove the Sequence from all priority lists */
  for (LulPriority = LulMinPriority; LulPriority <= LulMaxPriority; LulPriority++)                                      /* PRQA S 2877 # JV-01 */
  {
    /* If Seq has Job which has this priority, remove it from the list */
    if (0UL != (LpSubSeqConfig->ucUsingPriorities & (1UL << LulPriority)))
    {
      if (LpQueue->aaTop[LulPriority] == LpQueue->aaTail[LulPriority])                                                  /* PRQA S 0404 # JV-01 */
      {
        /* If this is the last sequence in the list, clear existence flag */
        LpQueue->ucExists = (uint8)(LpQueue->ucExists & ~(1UL << LulPriority));
      }
      else if (LpQueue->aaTop[LulPriority] == LulSeqIndex)
      {
        /* If this is the top sequence in the list, update top pointer */
        LpQueue->aaTop[LulPriority] = LpSubSeqStat->aaNext[LulPriority];
      }
      else if (LpQueue->aaTail[LulPriority] == LulSeqIndex)
      {
        /* If this is the tail sequence in the list, update tail pointer */
        LpQueue->aaTail[LulPriority] = LpSubSeqStat->aaPrev[LulPriority];
      }
      else
      {
        /*
         * If this is the intermediate sequence in the list, update previous and next sequence's pointers.
         */
        Spi_GaaSeqStatus[LpSubSeqStat->aaPrev[LulPriority]].aaSubSeqs[LulQueueIndex].aaNext[LulPriority] =              /* PRQA S 0404 # JV-01 */
            LpSubSeqStat->aaNext[LulPriority];
        Spi_GaaSeqStatus[LpSubSeqStat->aaNext[LulPriority]].aaSubSeqs[LulQueueIndex].aaPrev[LulPriority] =              /* PRQA S 0404 # JV-01 */
            LpSubSeqStat->aaPrev[LulPriority];
      }
    } /* else No action required */
  }
  /* If the on-going Sequence is removed, invalidate it */
  if (LpQueue->ucOngoingSeqIndex == LulSeqIndex)
  {
    LpQueue->ucOngoingSeqIndex = SPI_INVALID_SEQUENCE;
  } /* else No action required */
}

/***********************************************************************************************************************
** Function Name       : Spi_StartTransmission
**
** Service ID          : Not Applicable
**
** Description         : This function pushes a Sequence and starts it if HWUnit is idle
**
** Sync/Async          : Asynchronous
**
** Re-entrancy         : Reentrant for different Sequence. Non-Reentrant for same Sequence
**
**
** Input Parameters    : LulSeqIndex - Sequence ID
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : Spi Driver must be initialized
**
** Global Variable     : Spi_GpFirstSeq, Spi_GaaSeqStatus, Spi_GaaJobStatus, Spi_GulAllQueueSts, Spi_GpFirstJob,
**                       Spi_GaaHWStatus, Spi_GulActiveHWUnits, Spi_GpConfigPtr
**
** Function Invoked    : Spi_PushToQueue, Spi_PopFromQueue, Spi_ProcessJob, SPI_ENTER_CRITICAL_SECTION, 
**                       SPI_EXIT_CRITICAL_SECTION, pSeqStartNotification
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_036, SPI_DUD_ACT_036_CRT001, SPI_DUD_ACT_036_CRT002, SPI_DUD_ACT_036_GBL001,
** Reference ID        : SPI_DUD_ACT_036_GBL002, SPI_DUD_ACT_036_GBL005, SPI_DUD_ACT_036_GBL006, SPI_DUD_ACT_036_GBL007,
** Reference ID        : SPI_DUD_ACT_036_GBL008, SPI_DUD_ACT_036_GBL009, SPI_DUD_ACT_036_GBL010, SPI_DUD_ACT_036_GBL011,
** Reference ID        : SPI_DUD_ACT_036_GBL012
***********************************************************************************************************************/
FUNC(void, SPI_PRIVATE_CODE) Spi_StartTransmission(uint32 LulSeqIndex)
{
  boolean LblNeedToInitiate;
  uint32 LulJobListIndex;
  uint32 LulJobIndex;
  uint32 LulQueueIndex;
  P2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSeqConfig;
  P2CONST(Spi_SubSeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSubSeqConfig;
  volatile P2VAR(Spi_SeqStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpSeqStat;                                              /* PRQA S 3432 # JV-01 */
  P2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig;
  #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
  boolean LblSeqStartRequired;
  #endif

  /* Initialize start job flag */
  LblNeedToInitiate = SPI_FALSE;

  LpSeqConfig = &Spi_GpFirstSeq[LulSeqIndex];
  LpSeqStat = &Spi_GaaSeqStatus[LulSeqIndex];

  /* Initialize Sequence Status */
  LpSeqStat->blFailed = SPI_FALSE;

  #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
  /* Initialize already global started flag for SeqStartNotification */
  LpSeqStat->blStarted = SPI_FALSE;
  /* Initialize seq start require flag for SeqStartNotification */
  LblSeqStartRequired = SPI_TRUE;
  #endif /* End of (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON) */

  #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
  /* Set active bits for each SubSequences. When this variable becomes 0, it means all SubSequences completed */
  LpSeqStat->ulActiveSubSequences = LpSeqConfig->ulUsingHWUnits << 1UL;
  #endif

  #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
  /* Initialize status of all jobs of the requested sequence to "QUEUED" */
  for (LulQueueIndex = 1UL; LulQueueIndex < (uint32)Spi_GpConfigPtr->ucNoOfQueues; LulQueueIndex++)                     /* PRQA S 3416 # JV-01 */
  #else
  LulQueueIndex = 0UL;
  #endif
  {
    LpSubSeqConfig = &LpSeqConfig->aaSubSeqs[LulQueueIndex];
    /* Update status of all jobs to SPI_JOB_QUEUED */
    for (LulJobListIndex = 0UL; LulJobListIndex < (uint32)LpSubSeqConfig->usNoOfJobs; LulJobListIndex++)
    {
      LulJobIndex = LpSubSeqConfig->pJobList[LulJobListIndex];
      Spi_GaaJobStatus[LulJobIndex].enResult = SPI_JOB_QUEUED;
    }
  }

  #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
  /* Initiate each SubSequences */
  for (LulQueueIndex = 1UL; LulQueueIndex < (uint32)Spi_GpConfigPtr->ucNoOfQueues; LulQueueIndex++)                     /* PRQA S 3416 # JV-01 */
  #else
  LulQueueIndex = 0UL;
  #endif
  {
    LpSubSeqConfig = &LpSeqConfig->aaSubSeqs[LulQueueIndex];
    if (0U < LpSubSeqConfig->usNoOfJobs)
    {
      /*
       * Check whether the Queue is running already.
       * Critical section is required to avoid racing condition with ISR.
       */
      SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
      #if (SPI_CANCEL_API == STD_ON) || (SPI_FORCE_CANCEL_API == STD_ON)
      /* Check whether the sequence is canceled before transmission started */
      if (SPI_SEQ_CANCELED != LpSeqStat->enResult)
      #endif
      {
        /* Push this sequence to the queue */
        Spi_PushToQueue(LulQueueIndex, LulSeqIndex);
        if (0UL == (Spi_GulAllQueueSts & (1UL << LulQueueIndex)))                                                       /* PRQA S 3416 # JV-01 */
        {
          /* If queue is not running, initiation is required */
          LblNeedToInitiate = SPI_TRUE;
          Spi_GulAllQueueSts |= (1UL << LulQueueIndex);
          /* Pop the first job */
          (void)Spi_PopFromQueue(LulQueueIndex, &LulSeqIndex, &LulJobIndex);                                            /* PRQA S 1339 # JV-01 */
          /* Sequence will be started by this function, so set started flag in this critical section */
          #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
          /* Sequence start notification is required at first job */
          LpSeqStat->blStarted = SPI_TRUE;
          #endif
          LpJobConfig = &Spi_GpFirstJob[LulJobIndex];
          /* Update HW status */
          Spi_GaaHWStatus[LpJobConfig->ucHWUnitIndex].ucOngoingSeqIndex = (Spi_SequenceType)LulSeqIndex;

          Spi_GaaHWStatus[LpJobConfig->ucHWUnitIndex].usOngoingJobIndex = (Spi_JobType)LulJobIndex;

          Spi_GulActiveHWUnits |= (1UL << LpJobConfig->ucHWUnitIndex) << SPI_ACTIVE_HW_BITS;
          #if (SPI_HW_STATUS_API == STD_ON)
          Spi_GaaHWStatus[LpJobConfig->ucHWUnitIndex].blActive = SPI_TRUE;
          #endif
          /* Update Job status */
          Spi_GaaJobStatus[LulJobIndex].enResult = SPI_JOB_PENDING;
        }
        else
        {
          /* If the Queue is already running, it will be started by ISR */
          LblNeedToInitiate = SPI_FALSE;
        }
      } /* if (SPI_SEQ_CANCELED != LpSeqStat->enResult) */
      #if (SPI_CANCEL_API == STD_ON) || (SPI_FORCE_CANCEL_API == STD_ON)
      else
      {
        /* If sequence is cancelled before start, do nothing */
      }
      #endif
      /* Exit critical section */
      SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
      /* Invoke SeqStartNotification if necessary */
      #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
      if ((SPI_TRUE == LblSeqStartRequired) && (SPI_TRUE == LpSeqStat->blStarted) &&                                    /* PRQA S 2995 # JV-01 */
          (NULL_PTR != LpSeqConfig->pSeqStartNotification))
      {
        /* Sequence start is not required more than once */
        LblSeqStartRequired = SPI_FALSE;                                                                                /* PRQA S 2983 # JV-01 */
        /* Invoke SeqStartNotification at the first job */
        LpSeqConfig->pSeqStartNotification();
      } /* else No action required */
      #endif
      /* If the initiation is required, run the first job */
      if (SPI_TRUE == LblNeedToInitiate)
      {
        /* Start transmission */
        Spi_ProcessJob(LulJobIndex);
      } /* if (SPI_TRUE == LblNeedToInitiate) */
    } /* if (0U < LpSubSeqConfig->usNoOfJobs) */
  } /* for (LulQueueIndex) */
}

/***********************************************************************************************************************
** Function Name       : Spi_ProcessSequence
**
** Service ID          : Not Applicable
**
** Description         : This function performs the scheduling above Job layer
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant for different HWUnit. Non-Reentrant for same HWUnit
**
** Input Parameters    : LulHWUnitIndex - Index of the HWUnit which the Sequence is currently going on.
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : Spi Driver must be initialized
**
** Global Variable     : Spi_GaaHWStatus, Spi_GpFirstJob, Spi_GulActiveHWUnits, Spi_GpFirstSeq, Spi_GaaSeqStatus,
**                       Spi_GaaJobStatus, Spi_GulAllQueueSts,
**
** Function Invoked    : SPI_DEM_REPORT_ERROR, Spi_PopFromQueue, Spi_ProcessJob,  Spi_InvokeNotifications,
**                       Spi_CheckSeqFinish, SPI_ENTER_CRITICAL_SECTION, SPI_EXIT_CRITICAL_SECTION
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_033, SPI_DUD_ACT_033_CRT001, SPI_DUD_ACT_033_CRT002, SPI_DUD_ACT_033_ERR001,
** Reference ID        : SPI_DUD_ACT_033_GBL001, SPI_DUD_ACT_033_GBL002, SPI_DUD_ACT_033_GBL003, SPI_DUD_ACT_033_GBL004,
** Reference ID        : SPI_DUD_ACT_033_GBL005, SPI_DUD_ACT_033_GBL006, SPI_DUD_ACT_033_GBL007, SPI_DUD_ACT_033_GBL008,
** Reference ID        : SPI_DUD_ACT_033_GBL009, SPI_DUD_ACT_033_GBL010
***********************************************************************************************************************/
FUNC(void, SPI_PRIVATE_CODE) Spi_ProcessSequence(const uint32 LulHWUnitIndex)
{
  P2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig;
  uint32 LulPrevJobIndex;
  uint32 LulPrevSeqIndex;
  uint32 LulJobIndex;
  uint32 LulSeqIndex;
  boolean LblAvailable;
  boolean LblSeqFinished;

  #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
  P2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSeqConfig;
  boolean LblSeqAlreadyStarted;
  #endif

  /* When parallel transmission is enabled, QueueIndex equals HwUnitIndex */
  #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
  const uint32 LulQueueIndex = LulHWUnitIndex + 1UL;                                                                    /* PRQA S 3383 # JV-01 */
  #else
  const uint32 LulQueueIndex = 0UL;
  #endif

  #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
  LpSeqConfig = NULL_PTR;
  LblSeqAlreadyStarted = SPI_FALSE;
  #endif

  LulPrevSeqIndex = Spi_GaaHWStatus[LulHWUnitIndex].ucOngoingSeqIndex;
  LulPrevJobIndex = Spi_GaaHWStatus[LulHWUnitIndex].usOngoingJobIndex;

  /* Check the Sequence is finished or aborted */
  LblSeqFinished = Spi_CheckSeqFinish(LulQueueIndex, LulPrevSeqIndex);

  /*
   * Critical section is required to avoid conflict with StartTransmission and ProcessSequence from other sequence
   */
  /* References: SPI_DUD_ACT_055_CRT001 */
  SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);

  /* Pop the next Job from the Queue */
  LblAvailable = Spi_PopFromQueue(LulQueueIndex, &LulSeqIndex, &LulJobIndex);
  if (SPI_TRUE == LblAvailable)
  {
    LpJobConfig = &Spi_GpFirstJob[LulJobIndex];
    #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
    LpSeqConfig = &Spi_GpFirstSeq[LulSeqIndex];
    LblSeqAlreadyStarted = Spi_GaaSeqStatus[LulSeqIndex].blStarted;
    Spi_GaaSeqStatus[LulSeqIndex].blStarted = SPI_TRUE;
    #endif
    #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_OFF)
    /* If the next Job is assigned to other HWUnit, clear HW associated with completed job, set other HWUnit activated.
     * If parallel transmission is enabled, a Queue is assigned to a HWUnit, so this operation is not necessary.
     */
    if (LpJobConfig->ucHWUnitIndex != LulHWUnitIndex)
    {
      /* Clear HW associated with completed job */
      Spi_GulActiveHWUnits &= ~((1UL << LulHWUnitIndex) << SPI_ACTIVE_HW_BITS);
      /* Active next unit */
      Spi_GulActiveHWUnits |= (1UL << LpJobConfig->ucHWUnitIndex) << SPI_ACTIVE_HW_BITS;
      #if (SPI_HW_STATUS_API == STD_ON)
      /* Clear HW associated with completed job */
      Spi_GaaHWStatus[LulHWUnitIndex].blActive = SPI_FALSE;
      /* Set other HWUnit activated */
      Spi_GaaHWStatus[LpJobConfig->ucHWUnitIndex].blActive = SPI_TRUE;
      #endif
    } /* else No action required */
    #endif /* #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_OFF) */
    /* Initialize next sequence and next job to transmit */
    Spi_GaaHWStatus[LpJobConfig->ucHWUnitIndex].ucOngoingSeqIndex = (Spi_SequenceType)LulSeqIndex;

    Spi_GaaHWStatus[LpJobConfig->ucHWUnitIndex].usOngoingJobIndex = (Spi_JobType)LulJobIndex;

    /* Update Job status */
    Spi_GaaJobStatus[LulJobIndex].enResult = SPI_JOB_PENDING;
  }
  else
  {
    /* If the Queue is empty, clear the active flag of this Queue */
    Spi_GulAllQueueSts &= ~(1UL << LulQueueIndex);
    /* De-active HW unit bit */
    Spi_GulActiveHWUnits &= ~((1UL << LulHWUnitIndex) << SPI_ACTIVE_HW_BITS);
    #if (SPI_HW_STATUS_API == STD_ON)
    /* Set HW unit status bit as False */
    Spi_GaaHWStatus[LulHWUnitIndex].blActive = SPI_FALSE;
    #endif
  }
  SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);

  /* Report PASS to DEM when Sequence finished successfully */
  #if (STD_ON == SPI_E_HARDWARE_ERROR_CONFIGURED)
  if (SPI_SEQ_OK == Spi_GaaSeqStatus[LulPrevSeqIndex].enResult)
  {
    SPI_DEM_REPORT_ERROR(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_PASSED);
  } /* else No action required */
  #endif

  /* Invoke JobEnd, SeqEnd, SeqStart notifications if necessary */
  Spi_InvokeNotifications(&Spi_GpFirstJob[LulPrevJobIndex], &Spi_GpFirstSeq[LulPrevSeqIndex], LblSeqFinished            /* PRQA S 0404 # JV-01 */
  #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
                          , LpSeqConfig, LblSeqAlreadyStarted
  #endif
  );

  /* If the Queue was not empty, transmit the popped Job */
  if (SPI_TRUE == LblAvailable)
  {
    /* Start Job */
    Spi_ProcessJob(LulJobIndex);
  } /* else No action required */
}

/***********************************************************************************************************************
** Function Name       : Spi_CancelSequence
**
** Service ID          : Not Applicable
**
** Description         : This function cancels on-going Sequence
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant among Sequences which don't share same HW
**                       Non-Reentrant among Sequence which share same HW
**
** Input Parameters    : LulSeqIndex    : Index of a Sequence which is canceled
**                       LblIsForceStop : Behavior when Job(s) are on-going:
**                       SPI_TRUE : Stop the HW immediately.
**                       SPI_FALSE: Set cancel request flag and a sequence will be canceled at the next Job end timing.
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : Spi Driver must be initialized
**
** Global Variable     : Spi_GpFirstSeq, Spi_GaaSeqStatus, Spi_GaaJobStatus, Spi_GpFirstJob, Spi_GpFirstHWUnit,
**                       Spi_GpHwConfig, Spi_GaaActiveSequence, Spi_GpConfigPtr
**
** Function Invoked    : Spi_RemoveFromQueue, Spi_CSIXForceStop, Spi_HSPIForceStop, Spi_MSPIForceStop,
**                       Spi_ProcessSequence, Spi_MaskSequenceInterrupts, Spi_InvokeNotifications,
**                       SPI_ENTER_CRITICAL_SECTION, SPI_EXIT_CRITICAL_SECTION
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_037, SPI_DUD_ACT_037_CRT001, SPI_DUD_ACT_037_CRT002, SPI_DUD_ACT_037_GBL001,
** Reference ID        : SPI_DUD_ACT_037_GBL002, SPI_DUD_ACT_037_GBL003, SPI_DUD_ACT_037_GBL004, SPI_DUD_ACT_037_GBL005,
** Reference ID        : SPI_DUD_ACT_037_GBL006, SPI_DUD_ACT_037_GBL007,
***********************************************************************************************************************/
#if ((SPI_CANCEL_API == STD_ON) || (SPI_FORCE_CANCEL_API == STD_ON))
FUNC(void, SPI_PRIVATE_CODE) Spi_CancelSequence(const uint32 LulSeqIndex, const boolean LblIsForceStop)
{
  #if (SPI_FORCE_CANCEL_API == STD_ON)
  uint32 LulHWUnitIndex;
  uint32 LulIndex;
  #endif
  P2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSeqConfig;
  P2CONST(Spi_SubSeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSubSeqConfig;
  volatile P2VAR(Spi_SubSeqStatusType, AUTOMATIC, SPI_VAR_NO_INIT) LpSubSeqStat;                                        /* PRQA S 3432, 3678 # JV-01, JV-01 */
  uint32 LulJobIndex;
  uint32 LulQueueIndex;
  uint32 LulRequireScheduling;
  boolean LblRequireSeqEndNotification;

  LulRequireScheduling = 0UL;
  LblRequireSeqEndNotification = SPI_FALSE;
  LpSeqConfig = &Spi_GpFirstSeq[LulSeqIndex];

  #if ((SPI_FORCE_CANCEL_API == STD_ON) && ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || \
  (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)))
  /* First, mask all interrupts which can be used by this Sequence to avoid any interruption occur during the stopping 
   * operation */
  if (SPI_TRUE == LblIsForceStop)
  {
    Spi_MaskSequenceInterrupts(LpSeqConfig, SPI_TRUE);
  } /* else No action required */
  #endif /* (SPI_FORCE_CANCEL_API == STD_ON) */

  /* RAM_DATA_PROTECTION is required to manipulate the statuses and Queues */
  SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
  if (SPI_SEQ_PENDING == Spi_GaaSeqStatus[LulSeqIndex].enResult)
  {
    #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
    /* Stop all concurrent transmissions of this Sequence */
    for (LulQueueIndex = 1UL; LulQueueIndex < (uint32)Spi_GpConfigPtr->ucNoOfQueues; LulQueueIndex++)                   /* PRQA S 3416 # JV-01 */
    {
      if (0UL == (Spi_GaaSeqStatus[LulSeqIndex].ulActiveSubSequences & (1UL << LulQueueIndex)))
      {
        /* This Sequence doesn't have Jobs on this Queue */
      }
      else
      {
    #else
    /*
     * If concurrent asynchronous transmission is disabled, SPI_MAX_QUEUE is always 1
     */
    LulQueueIndex = 0UL;
    #endif /* (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON) */
        LpSubSeqConfig = &LpSeqConfig->aaSubSeqs[LulQueueIndex];
        LpSubSeqStat = &Spi_GaaSeqStatus[LulSeqIndex].aaSubSeqs[LulQueueIndex];
        /*
         * Check whether this SubSequence is on-going on the HW now:
         * If this SubSequence is already started (NoOfJobs > RemainJobs) and
         * the latest Job (NoOfJobs - 1 - RemainJobs) is not finished
         */
        if (LpSubSeqConfig->usNoOfJobs > LpSubSeqStat->usRemainJobCount)
        {
          LulJobIndex = LpSubSeqConfig->pJobList[(LpSubSeqConfig->usNoOfJobs - 1U) - LpSubSeqStat->usRemainJobCount];   /* PRQA S 3384 # JV-01 */
          if (SPI_JOB_PENDING == Spi_GaaJobStatus[LulJobIndex].enResult)
          {
            #if (SPI_FORCE_CANCEL_API == STD_ON)
            /* If ForceStop is required, stop HW immediately */
            if (SPI_TRUE == LblIsForceStop)
            {
              /* If the Sequence is on-going now, stop the HW */
              LulHWUnitIndex = Spi_GpFirstJob[LulJobIndex].ucHWUnitIndex;
              LulIndex = (uint32)Spi_GpFirstHWUnit[LulHWUnitIndex].ucMacroIndex;
              /* Call HW dependent function force stop the HW operation */
              Spi_GpHwConfig[LulIndex].pHwDepFunc->pHwForceStop(LulHWUnitIndex);
              /* Set the result as FAILED for the force canceled Job */
              Spi_GaaJobStatus[LulJobIndex].enResult = SPI_JOB_FAILED;
              /* Set Canceled flag so that this sequence results CANCELED
                 even if this is the last Job in the Sequence */
              Spi_GaaSeqStatus[LulSeqIndex].blCanceled = SPI_TRUE;
            }
            else
            #endif /* (SPI_FORCE_CANCEL_API == STD_ON) */
            {
              #if (SPI_CANCEL_API == STD_ON)
              /*
               * Set CancelRequest flag, this flag is ignored if this is the last Job
               */
              Spi_GaaSeqStatus[LulSeqIndex].blCancelRequested = SPI_TRUE;
              #endif /* (SPI_CANCEL_API == STD_ON) */
            }
            /* Scheduling is required to complete canceling sequence */
            LulRequireScheduling |= (1UL << LulQueueIndex);
          }
          else if (SPI_JOB_QUEUED == Spi_GaaJobStatus[LulJobIndex].enResult)                                            /* PRQA S 2004 # JV-01 */
          {
            /* If the SubSequence is not on-going now, remove directly */
            Spi_RemoveFromQueue(LulQueueIndex, LulSeqIndex);
            #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
            /* Clear SubSequence Active flag */
            Spi_GaaSeqStatus[LulSeqIndex].ulActiveSubSequences &= ~(1UL << LulQueueIndex);
            #endif
          } /* else No action required */
        }
        else /* Sequence has not been started, remove all jobs in queue*/
        {
          /* Remove all jobs belonging to sequence */
          Spi_RemoveFromQueue(LulQueueIndex, LulSeqIndex);
          #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
          /* Clear SubSequence Active flag */
          Spi_GaaSeqStatus[LulSeqIndex].ulActiveSubSequences &= ~(1UL << LulQueueIndex);
          #endif
        }
    #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
      } /* if (0 != (ulActiveSubSequences & (1UL << LulQueueIndex)) */
    }   /* for (LulQueueIndex) */
    #endif
    if (0UL == LulRequireScheduling)
    {
      /* If all SubSequences were not on-going and removed directly, Spi_ProcessSequence is not invoked. */
      Spi_GaaSeqStatus[LulSeqIndex].enResult = SPI_SEQ_CANCELED; 
      /* So SeqEndNotification has to be invoked in this function */
      LblRequireSeqEndNotification = SPI_TRUE;
      /* Clear sequence active bit for checking job sharing */
      Spi_GaaActiveSequence[LulSeqIndex / (uint32)SPI_UINT32_BITS] &= ~(1UL << (LulSeqIndex & (SPI_UINT32_BITS - 1U)));
    } /* else No action required */
  } /* End of for (LulQueueIndex = SPI_ZERO; LulQueueIndex < (uint32)Spi_GpConfigPtr->ucNoOfQueues;LulQueueIndex++) */
  SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);

  #if ((SPI_FORCE_CANCEL_API == STD_ON) && ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || \
  (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)))
  /* Restore interrupt masks */
  if (SPI_TRUE == LblIsForceStop)
  {
    Spi_MaskSequenceInterrupts(LpSeqConfig, SPI_FALSE);
  } /* else No action required */
  #endif /* End of ((SPI_FORCE_CANCEL_API == STD_ON) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

  #if (SPI_FORCE_CANCEL_API == STD_ON)
  /* Invoke Scheduler for each HWUnit which ForceStop is performed on */
  if ((0UL != LulRequireScheduling) && (SPI_TRUE == LblIsForceStop))
  {
    #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
    /*
     * If concurrent asynchronous transmission is enabled, the same queue is the same HWUnit only, and the queue index
     * is the same as HWUnit index
     */
    for (LulHWUnitIndex = 0UL; LulHWUnitIndex < (uint32)Spi_GpConfigPtr->ucNoOfHWUnits; LulHWUnitIndex++)               /* PRQA S 3416 # JV-01 */
    {
      if (0UL != (LulRequireScheduling & (1UL << (LulHWUnitIndex + 1UL))))                                              /* PRQA S 3383 # JV-01 */
      {
    #endif
        Spi_ProcessSequence(LulHWUnitIndex);
    #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
      } /* else No action required */
    }
    #endif
  }
  else
  #endif /* (SPI_FORCE_CANCEL_API == STD_ON) */
  {
    /* If a seq is canceled before start, invoke the notification here */
    Spi_InvokeNotifications(NULL_PTR, LpSeqConfig, LblRequireSeqEndNotification
    #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
                            , NULL_PTR, SPI_FALSE
    #endif
    );
  }
}
#endif /* ((SPI_CANCEL_SPI == STD_ON) || (SPI_FORCE_CANCEL_API == STD_ON) */

#if ((SPI_FORCE_CANCEL_API == STD_ON) && ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)))
/***********************************************************************************************************************
** Function Name       : Spi_MaskSequenceInterrupts
**
** Service ID          : Not Applicable
**
** Description         : This function manipulates interrupt pendings of HWUnits which are used by the Sequence.
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant among Sequences which don't share same HW
**                       Non-Reentrant among Sequence which share same HW
**
** Input Parameters    : LpSeqConfig - Pointer to the Sequence config
**                       LblMask     - TRUE: set mask HW units
**                                   - FALSE: clear mask of HW units
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : Spi Driver must be initialized
**
** Global Variable     : Spi_GenAsyncMode, Spi_GulCancelingHWUnits, Spi_GpFirstHWUnit, Spi_GpHwConfig
**
** Function Invoked    : None
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_040, SPI_DUD_ACT_040_CRT001, SPI_DUD_ACT_040_CRT002, SPI_DUD_ACT_040_GBL001,
** Reference ID        : SPI_DUD_ACT_040_GBL002
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_MaskSequenceInterrupts(CONSTP2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSeqConfig,
                               const boolean LblMask)
{
  /* Interrupt protection is not necessary because even if any ISR happen during this loop,
     it will work and finish properly */

  if (SPI_POLLING_MODE == Spi_GenAsyncMode)                                                                             /* PRQA S 3416 # JV-01 */
  {
    /* Set/Clear cancel on-going bits for the target HWUnits to prevent these HWUnits from being polled */
    /* Interrupt disabling is required for:
       - Exclusive control for re-entrant call of Spi_ForceCancel
       - Prevent invoking of Spi_MainFunction_Handling */
    SPI_ENTER_CRITICAL_SECTION(SPI_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
    if (SPI_TRUE == LblMask)
    {
      Spi_GulCancelingHWUnits |= LpSeqConfig->ulUsingHWUnits;
    }
    else
    {
      Spi_GulCancelingHWUnits &= ~LpSeqConfig->ulUsingHWUnits;
    }
    SPI_EXIT_CRITICAL_SECTION(SPI_INTERRUPT_CONTROL_PROTECTION_GLOBAL);
  } /* else No action required */
}
#endif /* End of ((SPI_FORCE_CANCEL_API == STD_ON) && (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

/***********************************************************************************************************************
** Function Name       : Spi_InvokeNotifications
**
** Service ID          : Not Applicable
**
** Description         : This function invokes notification handlers
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant
**
** Input Parameters    : LpPrevJobConfig      - Pointer to Job configuration
**                       LpPrevSeqConfig      - Pointer to Seq configuration
**                       LblSeqFinished       - Whether the prev seq is finished
**                       LpNextSeqConfig      - Pointer to Seq configuration
**                       LblSeqAlreadyStarted - Whether the next Seq has been started already
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : Spi Driver must be initialized
**
** Global Variable     : None
**
** Function Invoked    : User call back functions(pJobEndNotification, pSeqStartNotification)
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_035
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE)
    Spi_InvokeNotifications(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpPrevJobConfig,
                            CONSTP2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpPrevSeqConfig,
                            const boolean LblSeqFinished
                            #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
                            , CONSTP2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpNextSeqConfig,
                            const boolean LblSeqAlreadyStarted
                            #endif
    )
{
  if ((NULL_PTR != LpPrevJobConfig) && (NULL_PTR != LpPrevJobConfig->pJobEndNotification))
  {
    /* Callback job end notification  */
    LpPrevJobConfig->pJobEndNotification();
  } /* else No action required */

  if ((SPI_TRUE == LblSeqFinished) && (NULL_PTR != LpPrevSeqConfig->pSeqEndNotification))
  {
    /* Callback Sequence end notification  */
    LpPrevSeqConfig->pSeqEndNotification();
  } /* else No action required */

  #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
  if ((SPI_FALSE == LblSeqAlreadyStarted) && (NULL_PTR != LpNextSeqConfig) &&
      (NULL_PTR != LpNextSeqConfig->pSeqStartNotification))
  {
    /* Callback sequence start notification  */
    LpNextSeqConfig->pSeqStartNotification();
  } /* else No action required */
  #endif
}

/***********************************************************************************************************************
** Function Name       : Spi_ProcessJob
**
** Service ID          : Not Applicable
**
** Description         : This function starts a Job
**
** Sync/Async          : Asynchronous
**
** Re-entrancy         : Reentrant for different Job. Non-Reentrant for same Job
**
** Input Parameters    : LulJobIndex - Index of the Job
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : Spi Driver must be initialized
**
** Global Variable     : Spi_GpFirstJob, Spi_GpFirstHWUnit, Spi_GpHwConfig, Spi_GenAsyncMode
**
** Function Invoked    : Spi_CSIXProcessJob, Spi_HSPIProcessJob, Spi_MSPIProcessJob, Spi_CSIXMaskInterrupts,
**                       pHwMaskInterrupts
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_034, SPI_DUD_ACT_034_GBL001, SPI_DUD_ACT_034_GBL002
***********************************************************************************************************************/
STATIC FUNC(void, SPI_PRIVATE_CODE) Spi_ProcessJob(const uint32 LulJobIndex)
{
  P2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig;
  uint32 LulIndex;

  LpJobConfig = &Spi_GpFirstJob[LulJobIndex];
  LulIndex = (uint32)Spi_GpFirstHWUnit[LpJobConfig->ucHWUnitIndex].ucMacroIndex;

  #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)
  if (SPI_INTERRUPT_MODE == Spi_GenAsyncMode)                                                                           /* PRQA S 3416 # JV-01 */
  #endif
  {
    /* Call HW dependent function to enable HW interrupts  */
    Spi_GpHwConfig[LulIndex].pHwDepFunc->pHwMaskInterrupts(LpJobConfig, SPI_FALSE);
  } /* else No action required */

  /* Call HW dependent function to start asynchronous job */
  Spi_GpHwConfig[LulIndex].pHwDepFunc->pHwProcessJob(SPI_TRUE, LpJobConfig);
}

/***********************************************************************************************************************
** Function Name       : Spi_CheckSeqFinish
**
** Service ID          : Not Applicable
**
** Description         : This function will handle when a Sequence finished or aborted
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant for different HWUnit. Non-Reentrant for same HWUnit
**
** Input Parameters    : LulQueueIndex - Queue index.
**                       LulSeqIndex - Sequence index.
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : boolean (SPI_TRUE/SPI_FALSE)
**
** Preconditions       : Spi Driver must be initialized
**
** Global Variable     : Spi_GaaSeqStatus, Spi_GaaActiveSequence
**
** Function Invoked    : Spi_RemoveFromQueue, SPI_ENTER_CRITICAL_SECTION, SPI_EXIT_CRITICAL_SECTION
**
** Reference ID        : SPI_DUD_ACT_101, SPI_DUD_ACT_101_CRT001, SPI_DUD_ACT_101_CRT002, SPI_DUD_ACT_101_GBL001
** Reference ID        : SPI_DUD_ACT_101_GBL002, SPI_DUD_ACT_101_GBL003, SPI_DUD_ACT_101_GBL004
***********************************************************************************************************************/
STATIC FUNC(boolean, SPI_PRIVATE_CODE) Spi_CheckSeqFinish(const uint32 LulQueueIndex, const uint32 LulSeqIndex)
/* References: SPI_DUD_ACT_088 */
{
  uint32 LulRemainJobs;
  boolean LblSeqFinished;
  Spi_SeqResultType LenLastSeqState;

  /* Initialize sequence finish status value as FALSE */
  LblSeqFinished = SPI_FALSE;

  /*
   * Critical section is required to avoid conflict  with StartTransmission and ProcessSequence from other HWUnits
   */
  SPI_ENTER_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);
  LulRemainJobs = Spi_GaaSeqStatus[LulSeqIndex].aaSubSeqs[LulQueueIndex].usRemainJobCount;
  /*
   * If Sequence finished or aborted, clear Sequence active bit and set Sequence result code.
   * If multiple events occur at same time, the priority order of the result is:
   * FAILED > CANCELED(by Spi_ForceCancel) > OK > CANCELED(by Spi_Cancel)
   */
  if ((0UL == LulRemainJobs) || (SPI_TRUE == Spi_GaaSeqStatus[LulSeqIndex].blFailed)
      #if (SPI_CANCEL_API == STD_ON)
      || (SPI_TRUE == Spi_GaaSeqStatus[LulSeqIndex].blCancelRequested)
      #endif
      #if (SPI_FORCE_CANCEL_API == STD_ON)
      || (SPI_TRUE == Spi_GaaSeqStatus[LulSeqIndex].blCanceled)
      #endif
  )
  {
    #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
    /* Clear SubSequence Active flag */
    Spi_GaaSeqStatus[LulSeqIndex].ulActiveSubSequences &= ~(1UL << LulQueueIndex);
    #endif

    /* If a SubSequence is aborted by some reason, remove remained Jobs */
    if (0UL != LulRemainJobs)
    {
      Spi_RemoveFromQueue(LulQueueIndex, LulSeqIndex);
      #if (SPI_CANCEL_API == STD_ON)
      /* If cancel is requested before finish, set the canceled flag */
      if (SPI_TRUE == Spi_GaaSeqStatus[LulSeqIndex].blCancelRequested)
      {
        Spi_GaaSeqStatus[LulSeqIndex].blCanceled = SPI_TRUE;
      } /* else No action required */
      #endif
    } /* else No action required */

    /* When all SubSequences finished, finish Sequence */
    #if (SPI_SUPPORT_CONCURRENT_ASYNC_TRANSMIT == STD_ON)
    if (0UL != Spi_GaaSeqStatus[LulSeqIndex].ulActiveSubSequences)
    {
      /* There are still active SubSequences, continue the Sequence */
    }
    else
    #endif
    {
      LblSeqFinished = SPI_TRUE;
      /* Clear Sequence active bit */
      Spi_GaaActiveSequence[LulSeqIndex / (uint32)SPI_UINT32_BITS] &= ~(1UL << (LulSeqIndex & (SPI_UINT32_BITS - 1U)));

      /* Update Sequence Result */
      if (SPI_TRUE == Spi_GaaSeqStatus[LulSeqIndex].blFailed)
      {
        LenLastSeqState = SPI_SEQ_FAILED;
      }
      #if ((SPI_CANCEL_API == STD_ON) || (SPI_FORCE_CANCEL_API == STD_ON))
      else if (SPI_TRUE == Spi_GaaSeqStatus[LulSeqIndex].blCanceled)
      {
        LenLastSeqState = SPI_SEQ_CANCELED;
      }
      #endif
      else
      {
        LenLastSeqState = SPI_SEQ_OK;
      }
      Spi_GaaSeqStatus[LulSeqIndex].enResult = LenLastSeqState;
    }
  } /* if (SubSequence finished) */
  /* Exit from Critical section */
  SPI_EXIT_CRITICAL_SECTION(SPI_RAM_DATA_PROTECTION_GLOBAL);

  /* Return sequence finish flag */
  return LblSeqFinished;
}
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL_1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2))
/***********************************************************************************************************************
** Function Name       : Spi_TransmitSyncSequence
**
** Service ID          : Not applicable
**
** Description         : This function transmits a Sequence synchronously
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant
**
** Input Parameters    : LulSeqIndex - Sequence ID
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : Std_ReturnType (E_OK/E_NOT_OK)
**
** Preconditions       : Spi_Init should have been invoked.
**
** Global Variable     : Spi_GpFirstSeq, Spi_GpFirstHWUnit, Spi_GpFirstJob, Spi_GaaJobStatus, Spi_GaaSeqStatus,
**                       Spi_GaaHWStatus, Spi_GpHwConfig
**
** Function invoked    : SPI_DEM_REPORT_ERROR, Spi_MSPITransmitSyncJob, Spi_CSIXTransmitSyncJob,
**                       Spi_HSPITransmitSyncJob, pSeqStartNotification, pSeqEndNotification
**
** Registers Used      : None
**
** Reference ID        : SPI_DUD_ACT_038, SPI_DUD_ACT_038_ERR001, SPI_DUD_ACT_038_GBL001, SPI_DUD_ACT_038_GBL002,
** Reference ID        : SPI_DUD_ACT_038_GBL003, SPI_DUD_ACT_038_GBL004, SPI_DUD_ACT_038_GBL005, SPI_DUD_ACT_038_GBL006,
** Reference ID        : SPI_DUD_ACT_038_GBL007, SPI_DUD_ACT_038_GBL008, SPI_DUD_ACT_038_GBL009, SPI_DUD_ACT_038_GBL010
***********************************************************************************************************************/
FUNC(Std_ReturnType, SPI_PRIVATE_CODE) Spi_TransmitSyncSequence(const uint32 LulSeqIndex)
{
  P2CONST(Spi_SeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSeqConfig;
  P2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig;
  P2CONST(Spi_SubSeqConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpSubSeqConfig;
  uint32 LulJobIndex;
  uint32 LulJobListIndex;
  uint32 LulIndex;
  Std_ReturnType LucResult;

  LpSeqConfig = &Spi_GpFirstSeq[LulSeqIndex];

  /* Update the sequence result as SPI_SEQ_PENDING */
  Spi_GaaSeqStatus[LulSeqIndex].enResult = SPI_SEQ_PENDING;

  /* Initialize failed-flag as false */
  Spi_GaaSeqStatus[LulSeqIndex].blFailed = SPI_FALSE;

  #if (SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON)
  /* Invoke the start sequence notification function */
  if (NULL_PTR != LpSeqConfig->pSeqStartNotification)
  {
    LpSeqConfig->pSeqStartNotification();
  } /* else No action required */
  #endif /* #if(SPI_SEQ_STARTNOTIFICATION_ENABLED == STD_ON) */

  /* Loop for each Job until any error occurs or all jobs end */
  LucResult = E_OK;

  /* Initiate each SubSequences */
  LpSubSeqConfig = &LpSeqConfig->aaSubSeqs[0UL];
  for (LulJobListIndex = 0U; ((E_OK == LucResult) && (LulJobListIndex < LpSubSeqConfig->usNoOfJobs)); LulJobListIndex++)
  {
    /* Transmit a Job */
    LulJobIndex = LpSubSeqConfig->pJobList[LulJobListIndex];
    LpJobConfig = &Spi_GpFirstJob[LulJobIndex];
    /* Update the Job result as SPI_JOB_PENDING */
    Spi_GaaJobStatus[LulJobIndex].enResult = SPI_JOB_PENDING;
    #if (SPI_HW_STATUS_API == STD_ON)
    /* Set HW status */
    Spi_GaaHWStatus[LpJobConfig->ucHWUnitIndex].blActive = SPI_TRUE;
    #endif
    Spi_GaaHWStatus[LpJobConfig->ucHWUnitIndex].ucOngoingSeqIndex = (Spi_SequenceType)LulSeqIndex;

    Spi_GaaHWStatus[LpJobConfig->ucHWUnitIndex].usOngoingJobIndex = (Spi_JobType)LulJobIndex;

    LulIndex = (uint32)Spi_GpFirstHWUnit[LpJobConfig->ucHWUnitIndex].ucMacroIndex;
    /* Call HW dependent function to start job synchronous transmission */
    LucResult = Spi_GpHwConfig[LulIndex].pHwDepFunc->pHwTransmitSyncJob(LpJobConfig);
    #if (SPI_HW_STATUS_API == STD_ON)
    /* If this was the last Job or the next Job is assigned to other HW, turn off IP */
    if ((E_NOT_OK == LucResult) || (LulJobListIndex == ((uint32)LpSubSeqConfig->usNoOfJobs - 1UL)) ||                   /* PRQA S 3384 # JV-01 */
        (Spi_GpFirstJob[LpSubSeqConfig->pJobList[LulJobListIndex + 1UL]].ucHWUnitIndex != LpJobConfig->ucHWUnitIndex))  /* PRQA S 3383, 3416, 3415 # JV-01, JV-01, JV-01 */
    {
      Spi_GaaHWStatus[LpJobConfig->ucHWUnitIndex].blActive = SPI_FALSE; 
    } /* else No action required */
    #endif
  } /* for (LulJobListIndex) */

  /* Set Sequence result code */
  if (E_OK == LucResult)
  {
    #if (STD_ON == SPI_E_HARDWARE_ERROR_CONFIGURED)
    SPI_DEM_REPORT_ERROR(SPI_E_HARDWARE_ERROR, DEM_EVENT_STATUS_PASSED);
    #endif
    Spi_GaaSeqStatus[LulSeqIndex].enResult = SPI_SEQ_OK;
  }
  else
  {
    Spi_GaaSeqStatus[LulSeqIndex].enResult = SPI_SEQ_FAILED;
  }

  #if (SPI_SYNC_SEQ_ENDNOTIFICATION_ENABLED == STD_ON)
  /* Check if the notification function is configured */
  if (NULL_PTR != LpSeqConfig->pSeqEndNotification)
  {
    /* Invoke the notification function */
    LpSeqConfig->pSeqEndNotification();
  } /* else No action required */
  #endif /* (SPI_SYNC_SEQ_ENDNOTIFICATION_ENABLED == STD_ON) */

  return LucResult;
}
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL_0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_2)) */

/***********************************************************************************************************************
** Function Name       : Spi_TurnOffHWUnit
**
** Service ID          : Not Applicable
**
** Description         : This function stop the clock or disable the HWUnit associated with the job.
**
** Sync/Async          : Synchronous
**
** Re-entrancy         : Reentrant
**
** Input Parameters    : LpJobConfig  - Pointer to the Job configuration
**
** InOut Parameters    : None
**
** Output Parameters   : None
**
** Return parameter    : None
**
** Preconditions       : Spi Driver must be initialized
**
** Global Variable     : Spi_GpFirstHWUnit, Spi_GpHwConfig, Spi_GenAsyncMode
**
** Function Invoked    : Spi_CSIXTurnOff, Spi_HSPITurnOff, Spi_MSPITurnOff
**
** Registers Used      : CSIXnCTL0, HSPInCKEN, MSPInCTL0
**
** Reference ID        : SPI_DUD_ACT_039, SPI_DUD_ACT_039_GBL001, SPI_DUD_ACT_039_GBL002
***********************************************************************************************************************/
FUNC(void, SPI_PRIVATE_CODE) Spi_TurnOffHWUnit(CONSTP2CONST(Spi_JobConfigType, AUTOMATIC, SPI_CONFIG_DATA) LpJobConfig)
{
  uint32 LulHWUnitIndex;
  uint32 LulIndex;
  P2CONST(Spi_HWUnitInfoType, AUTOMATIC, SPI_CONFIG_DATA) LpHWInfo;

  LulHWUnitIndex = LpJobConfig->ucHWUnitIndex;
  LpHWInfo = &Spi_GpFirstHWUnit[LulHWUnitIndex];
  LulIndex = (uint32)LpHWInfo->ucMacroIndex;

  /* Disable interrupts for completed job */
  #if (SPI_LEVEL_DELIVERED == SPI_LEVEL_2) || (SPI_LEVEL_DELIVERED == SPI_LEVEL_1)
  if (SPI_INTERRUPT_MODE == Spi_GenAsyncMode)                                                                           /* PRQA S 3416 # JV-01 */
  #endif
  {
    #if (SPI_LEVEL_DELIVERED != SPI_LEVEL_0)
    /* Call HW dependent function to disable HW interrupts  */
    Spi_GpHwConfig[LulIndex].pHwDepFunc->pHwMaskInterrupts(LpJobConfig, SPI_TRUE);
    #endif /* (SPI_LEVEL_DELIVERED != SPI_LEVEL_0) */
  } /* else No action required */

  /* Call HW dependent function to turn off HW unit */
  Spi_GpHwConfig[LulIndex].pHwDepFunc->pHwTurnOff((uint32)LpHWInfo->ucPhyUnitIndex);
}

#define SPI_STOP_SEC_PRIVATE_CODE
#include "Spi_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
