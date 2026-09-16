// /*******************************************************************************
// |    Header File Inclusion
// |******************************************************************************/
// #include "user_flsif.h"
// #include "Dio.h"
// /*******************************************************************************
// |    Macro Definition
// |******************************************************************************/
// #define   APP_BUFFER_SIZE    0x0300u
// #define   APP_BUFF_LENGTH    0x3000u

// #define   FLS_SAMPLE_LEN_4KB    0x1000u
// #define   FLS_SAMPLE_LEN_8KB    0x2000u

// #define   FLS_SAMPLE_ADDR1      0x4000u
// #define   FLS_SAMPLE_ADDR1_MA1 (FLS_SAMPLE_ADDR1+FLS_SAMPLE_ONE)
// #define   FLS_SAMPLE_ADDR1_MA2 (FLS_SAMPLE_ADDR1+FLS_SAMPLE_THREE)
// #define   FLS_SAMPLE_LEN1       APP_BUFFER_SIZE
// #define   FLS_SAMPLE_LEN1_MA1  (FLS_SAMPLE_LEN1-FLS_SAMPLE_TWO)
// #define   FLS_SAMPLE_LEN1_MA2  (FLS_SAMPLE_LEN1-FLS_SAMPLE_THREE)

// #define   FLS_SAMPLE_ADDR2      0x4300u
// #define   FLS_SAMPLE_LEN2       0x0200u

// #define   FLS_SAMPLE_ADDR3      0x4400u
// #define   FLS_SAMPLE_ADDR3_MA1 (FLS_SAMPLE_ADDR3+FLS_SAMPLE_ONE)
// #define   FLS_SAMPLE_LEN3       0x0200u

// #define   FLS_SAMPLE_ADDR4      0x2000u
// #define   FLS_SAMPLE_LEN4       APP_BUFF_LENGTH

// #define   FLS_DELAY_TIME        0x000111FFuL

// /*******************************************************************************
// |    Typedef Definition
// |******************************************************************************/

// /*******************************************************************************
// |    variables Declaration  
// |******************************************************************************/
// uint8 GaaAppBufferForWriteA[APP_BUFFER_SIZE];
// uint8 GaaAppBufferForWriteB[APP_BUFFER_SIZE];
// uint8 GaaAppBufferForRead[APP_BUFFER_SIZE];

// uint8 GaaBufferArray[APP_BUFF_LENGTH];
// uint8 GaaBufferArrayA[APP_BUFF_LENGTH];

// Std_ReturnType GddReturnValue;

// uint8 *GpData;
// uint16 GusLoopVar;

// volatile boolean GblTestResult;
// volatile uint8 GucTestNo;
// /* loop counter for Fls_MainFunction */
// volatile MemIf_JobResultType GddJobResultType;

// volatile MemIf_JobResultType GddCancelResultType;
// MemIf_StatusType GddStatus;
// volatile MemIf_StatusType GddStatusType;

// uint32 GulDelayCounter = FLS_SAMPLE_ZERO;

// /*******************************************************************************
// |    code Declaration  
// |******************************************************************************/
// extern void Fls_MainFunction(void);

// void Delay(void)
// {
//   GulDelayCounter = FLS_SAMPLE_ZERO;
//   while (GulDelayCounter < FLS_DELAY_TIME)
//   {
//     GulDelayCounter++;
//   }
//   return;
// }

// void TestBufferClear(void)
// {
//   uint16 LusLoopCount;
//   for (LusLoopCount = FLS_SAMPLE_ZERO; LusLoopCount < APP_BUFFER_SIZE; \
//                                                                 LusLoopCount++)
//   {
//     if ( FLS_SAMPLE_ZERO == ( LusLoopCount & FLS_SAMPLE_TWO ) )
//     {
//       GaaAppBufferForWriteA[LusLoopCount]     = 0xAAu;
//     }
//     else
//     {
//       GaaAppBufferForWriteA[LusLoopCount]     = 0x55u;
//     }
    
//     GaaAppBufferForWriteB[LusLoopCount]       = (uint8)LusLoopCount;
//     GaaAppBufferForRead[LusLoopCount]         = 0u;
//   }

//   for (LusLoopCount = FLS_SAMPLE_ZERO; LusLoopCount < APP_BUFF_LENGTH; \
//                                                                 LusLoopCount++)
//   {
//     GaaBufferArray[LusLoopCount]  = (uint8)LusLoopCount;
//     GaaBufferArrayA[LusLoopCount] = 0u;
//   }
//   return;
// }

// void FlsIf_Init(void)
// {
//     Fls_Init(Fls_Config);
// }

// void FlsIf_Sample_test(void)
// {
//   GddJobResultType = MEMIF_JOB_CANCELED;

//   GddCancelResultType = MEMIF_JOB_CANCELED;
//   GddStatus = MEMIF_UNINIT;
//   GddStatusType = MEMIF_UNINIT;
//   GblTestResult = FLS_SAMPLE_TRUE;

//   DISABLE_INTERRUPT();

//   /***************************/
//   /* Request Erase Operation */
//   /***************************/
//   if ( FLS_SAMPLE_TRUE == GblTestResult )
//   {
//     GucTestNo  = FLS_SAMPLE_ZERO;
//     TestBufferClear();

//     // Dio_WriteChannel(DioConf_DioChannel_UserChannel_05_02,0);

//     /* Erase 4KB Data Flash starting from address FLS_SAMPLE_ADDR1 */
//     GddReturnValue = Fls_Erase(FLS_SAMPLE_ADDR1, FLS_SAMPLE_LEN_4KB);
//     if (E_OK == GddReturnValue)
//     {
//       #if (FLS_GET_STATUS_API == STD_ON)
//       while (Fls_GetStatus() != MEMIF_IDLE)
//       {
//         Fls_MainFunction();
//         Delay();
//       }
//       #endif /* #if (FLS_GET_STATUS_API == STD_ON) */

//       #if (FLS_GET_JOB_RESULT_API == STD_ON)
//       /* It will return the result of the last job  */
//       GddJobResultType = Fls_GetJobResult();
//       #endif /* #if (FLS_GET_JOB_RESULT_API == STD_ON) */

//       #if (FLS_GET_STATUS_API == STD_ON)
//       /* It will return the result of the last job  */
//       GddStatusType = Fls_GetStatus();
//       #endif /* #if (FLS_GET_STATUS_API == STD_ON) */

//       #if ((FLS_GET_JOB_RESULT_API == STD_ON) && (FLS_GET_STATUS_API == STD_ON))
//       if ((MEMIF_IDLE == GddStatusType) && (MEMIF_JOB_OK == GddJobResultType))
//       {
//         ;
//       }
//       else
//       {
//         GblTestResult = FLS_SAMPLE_FALSE;
//       }
//       #endif /* #if ((FLS_GET_JOB_RESULT_API == STD_ON) &&
//                                              (FLS_GET_STATUS_API == STD_ON)) */
//     }
//     else
//     {
//       GblTestResult = FLS_SAMPLE_FALSE;
//     }
//   }

//   // Dio_WriteChannel(DioConf_DioChannel_UserChannel_05_02,1);

//   /***************************/
//   /* Request Write Operation */
//   /***************************/
//   if ( FLS_SAMPLE_TRUE == GblTestResult )
//   {
//     GucTestNo  = FLS_SAMPLE_ONE;
//     TestBufferClear();

//     // Dio_WriteChannel(DioConf_DioChannel_UserChannel_05_02,0);

//     /* Write 768B to address FLS_SAMPLE_ADDR1 */
//     GddReturnValue = Fls_Write(FLS_SAMPLE_ADDR1, \
//                               (const uint8 *)&GaaAppBufferForWriteB[0], 
//                                                         4);
//     if (E_OK == GddReturnValue)
//     {
//       #if (FLS_GET_STATUS_API == STD_ON)
//       while (Fls_GetStatus() != MEMIF_IDLE)
//       {
//         Fls_MainFunction();
//         Delay();
//       }
//       #endif /* #if (FLS_GET_STATUS_API == STD_ON) */

//       // Dio_WriteChannel(DioConf_DioChannel_UserChannel_05_02,1);

//       #if (FLS_GET_JOB_RESULT_API == STD_ON)
//       /* It will return the result of the last job  */
//       GddJobResultType = Fls_GetJobResult();
//       #endif /* #if (FLS_GET_JOB_RESULT_API == STD_ON) */

//       #if (FLS_GET_STATUS_API == STD_ON)
//       /* It will return the result of the last job  */
//       GddStatusType = Fls_GetStatus();
//       #endif /* #if (FLS_GET_STATUS_API == STD_ON) */

//       #if ((FLS_GET_JOB_RESULT_API == STD_ON) && (FLS_GET_STATUS_API == STD_ON))
//       if ((MEMIF_IDLE == GddStatusType) && (MEMIF_JOB_OK == GddJobResultType))
//       {
        
//         GpData = (uint8*)(FLS_DF_BASE_ADDRESS + FLS_SAMPLE_ADDR1);
//         for (GusLoopVar = 0; GusLoopVar < FLS_SAMPLE_LEN1; GusLoopVar++)
//         {
//           /* compare application buffer with memory content */
//           if (*(GpData + GusLoopVar) != GaaAppBufferForWriteB[GusLoopVar])
//           {
//             GblTestResult = FLS_SAMPLE_FALSE;
//             break;
//           }
//           else
//           {
//             /* No Action Required */
//           }
//         }
//       }
//       else
//       {
//         GblTestResult = FLS_SAMPLE_FALSE;
//       }
//       #endif /* #if ((FLS_GET_JOB_RESULT_API == STD_ON) &&
//                                              (FLS_GET_STATUS_API == STD_ON)) */
//     }
//     else
//     {
//       GblTestResult = FLS_SAMPLE_FALSE;
//     }
//   }
//   /**************************/
//   /* Request Read Operation */
//   /**************************/
//   if ( FLS_SAMPLE_TRUE == GblTestResult )
//   {
//     GucTestNo  = FLS_SAMPLE_TWO;
//     TestBufferClear();
//     /* Read 768B from address FLS_SAMPLE_ADDR1 */
//     GddReturnValue = Fls_Read(FLS_SAMPLE_ADDR1, \
//                              (uint8 *)&GaaAppBufferForRead[0], FLS_SAMPLE_LEN1);
//     if (E_OK == GddReturnValue)
//     {
//       #if (FLS_GET_STATUS_API == STD_ON)
//       while (Fls_GetStatus() != MEMIF_IDLE)
//       {
//         Delay();
//         Fls_MainFunction();
//       }
//       #endif /* #if (FLS_GET_STATUS_API == STD_ON) */

//       #if (FLS_GET_JOB_RESULT_API == STD_ON)
//       /* It will return the result of the last job  */
//       GddJobResultType = Fls_GetJobResult();
//       #endif /* #if (FLS_GET_JOB_RESULT_API == STD_ON) */

//       #if (FLS_GET_STATUS_API == STD_ON)
//       /* It will return the result of the last job  */
//       GddStatusType = Fls_GetStatus();
//       #endif /* #if (FLS_GET_STATUS_API == STD_ON) */
//       #if ((FLS_GET_JOB_RESULT_API == STD_ON) && (FLS_GET_STATUS_API == STD_ON))
//       if ((MEMIF_IDLE == GddStatusType) && (MEMIF_JOB_OK == GddJobResultType))
//       {
//          GpData = (uint8*)(FLS_DF_BASE_ADDRESS + FLS_SAMPLE_ADDR1);
//          for (GusLoopVar = 0; GusLoopVar < FLS_SAMPLE_LEN1; GusLoopVar++)
//          {
//             /* compare application buffer with memory content */
//             if (*(GpData + GusLoopVar) != GaaAppBufferForRead[GusLoopVar])
//             {
//               GblTestResult = FLS_SAMPLE_FALSE;
//               break;
//             }
//             else
//             {
//               /* No Action Required */
//             }
//          }
//       }
//       else
//       {
//         GblTestResult = FLS_SAMPLE_FALSE;
//       }
//       #endif /* #if ((FLS_GET_JOB_RESULT_API == STD_ON) &&
//                                              (FLS_GET_STATUS_API == STD_ON)) */
//     }
//     else
//     {
//       GblTestResult = FLS_SAMPLE_FALSE;
//     }
//   }

//   Fls_DeInit();

// }

// FUNC(void, FLS_APPL_CODE) JobOkNotification(void)
// {

// }

// FUNC(void, FLS_APPL_CODE) JobErrorNotification(void)
// {

// }

// FUNC(void, FLS_APPL_CODE) EccSedNotification(uint32 ErrAddress)
// {

// }

// FUNC(void, FLS_APPL_CODE) EccDedNotification(uint32 ErrAddress)
// {

// }

