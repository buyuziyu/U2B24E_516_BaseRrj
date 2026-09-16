/*******************************************************************************
|    Header File Inclusion
|******************************************************************************/
#include "r_sys.h"
#include "user_linif.h"
#include <string.h>

/*******************************************************************************
|    Macro Definition
|******************************************************************************/

/*******************************************************************************
|    Typedef Definition
|******************************************************************************/

/*******************************************************************************
|    variables Declaration  
|******************************************************************************/
/* Lin_SendResponse APIs */
Lin_PduType GddPduInfo;
/* Global variable to use in Lin_GetStatus API for function return type */
Lin_StatusType GenStatusType;
/* Global variable for 1msec timer counter */
uint8 Guc1msecCount;
/* Global variable for 5msec timer counter */
uint8 Guc5msecCount;
/* Global pointer used in Lin_GetStatus API as output parameter */
uint8 **GpRxDataPtr;
/* Global pointer used by GpRxDataPtr */
uint8 *GpLinSduPtr;

/* Global data used as input parameter in Lin_SendResponse API */
uint8 Lin_GaaDataArray0[LIN_DATA_SIZE] = {(uint8)0x01U, (uint8)0x02U, (uint8)0x03U, (uint8)0x04U, (uint8)0x05U, (uint8)0x06U, (uint8)0x07U, (uint8)0x08U};
/* Global data used by GpLinSduPtr for a default value */
uint8 Lin_GaaDataArray1[LIN_DATA_SIZE] = {(uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU, (uint8)0xFFU};
/* Global variable to store RLIN3 status */
uint8 GucRLN31ST = 0;
uint8 GucRLN31LEST = 0;

/*******************************************************************************
|    code Declaration  
|******************************************************************************/

void LinIf_Init(void)
{
//     Lin_Init(Lin_Config);

//     Lin_WakeupInternal(LIN_CHANNEL_0);

//     /* Initialise Global variable for 1msec timer counter to 0 */
//     Guc1msecCount = LIN_COUNT_INITIAL_VALUE;
//     /* Initialise Global variable for 5msec timer counter to 0 */
//     Guc5msecCount = LIN_COUNT_INITIAL_VALUE;
//     /* Initialise GpLinSduPtr to application buffer */
//     GpLinSduPtr = &Lin_GaaDataArray1[0];
//     /* Initialise GpRxDataPtr to GpLinSduPtr */
//     GpRxDataPtr = &GpLinSduPtr;
}


void LinIf_Sample_test(void)
{
//     Guc5msecCount = LIN_COUNT_INITIAL_VALUE;

//     GucRLN31ST = 0;
//     GucRLN31LEST = 0;

//     /* Set the LIN PDU parameters for transmitting the LIN Frame */
//     GddPduInfo.Pid = (uint8)LIN_SEND_PID;
//     GddPduInfo.Cs = LIN_CLASSIC_CS;
//     GddPduInfo.Drc = LIN_MASTER_RESPONSE;
//     GddPduInfo.Dl = LIN_DATA_SIZE;
//     GddPduInfo.SduPtr = Lin_GaaDataArray0;
//     Lin_SendFrame(LIN_CHANNEL_0, &GddPduInfo);
//     /* Read Status Registers */
//     while (0 == GucRLN31ST )
//     {
//         GucRLN31ST = LIN_RLN31LST;
//         // if (0 == GucRLN31LEST)
//         {
//             GucRLN31LEST = LIN_RLN31LEST;
//         }
//     }
//     /* Wait for the maximum transfer delay for the frame to be transmitted */
//     while (Guc5msecCount < LIN_MAX_TIMEOUT_COUNT)
//     {
//         /* No operation. Counter is incremented in timer interrupt handler. */
//     }
//     /* Initialize 5msec Counter */
//     Guc5msecCount = LIN_COUNT_INITIAL_VALUE;


    // /* Set the LIN PDU parameters for receive the the LIN response */
    // GddPduInfo.Pid = (uint8)LIN_RESP_PID;
    // GddPduInfo.Cs = LIN_CLASSIC_CS;
    // GddPduInfo.Drc = LIN_SLAVE_RESPONSE;
    // GddPduInfo.Dl = LIN_DATA_SIZE ;
    // GddPduInfo.SduPtr = Lin_GaaDataArray1;
    // /* Functionality related to R4.2 */
    // /* Following API is invoked to transmit the header and receive the response
    // * as part of a LIN Frame on the addressed LIN Channel
    // */
    // Lin_SendFrame(LIN_CHANNEL_0, &GddPduInfo);
    // /* Wait for the maximum transfer delay for the frame to be transmitted */
    // while (Guc5msecCount < LIN_MAX_TIMEOUT_COUNT)
    // {
    //     /* No operation. Counter is incremented in timer interrupt handler. */
    // }
    // /* Initialize 5msec Counter */
    // Guc5msecCount = LIN_COUNT_INITIAL_VALUE;
}


void Appl_Scheduler_Task(void)
{
    // /* Following API is invoked to get the status of the LIN Driver */
    // GenStatusType = Lin_GetStatus(LIN_CHANNEL_0, GpRxDataPtr);
    // if(LIN_RX_OK==GenStatusType)
    // {
    //     memcpy(Lin_GaaDataArray1,*GpRxDataPtr,sizeof(Lin_GaaDataArray1));
    // }

    // /* Increment 5msec count */
    // Guc5msecCount++;
}

void IinIf_timer_task(void)
{
    // /* Increment Guc1msecCount by 1 */
    // Guc1msecCount++;
    // /* Wait for the maximum transfer delay for the frame to be transmitted */
    // if (LIN_WAIT_5MS == Guc1msecCount)
    // {
    //     /* Invoke Task */
    //     Appl_Scheduler_Task();

    //     /* Re-initialise Guc1msecCount to 0 */
    //     Guc1msecCount = LIN_COUNT_INITIAL_VALUE;
    // }
    // else
    // {
    //     /* No action required */
    // }
}

