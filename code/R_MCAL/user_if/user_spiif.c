/*******************************************************************************
|    Header File Inclusion
|******************************************************************************/
#include "user_spiif.h"
#include "r_cg_macrodriver.h"
#include "Dio.h"
#include "Spi_Cfg.h"
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
/* Variable used to store the status of SPI Driver */
Spi_StatusType App_GenStatus;

/* Variable used to store the Module Version Info */
Std_VersionInfoType App_GstVersionInfo;

/* Variable to check the result of API */
boolean App_GaaTestResult[SPI_CHECK_POINTS];

/* Variable to store the check point count */
uint8 App_GucCheckCount = 0;

/* Variable to store the result of APIs */
Std_ReturnType App_GenReturnValue;

/* Variable to store the result of sequence */
Spi_SeqResultType App_GaaSeqResult[SPI_SEQUENCE_NUM];

/* Variable to store the result of job */
Spi_JobResultType App_GaaJobResult[SPI_JOB_NUM];

/* Variable to store HW status */
Spi_StatusType LenHWStatus[SPI_HW_NUM];


/* Transmit data for SpiChannel0 */
uint8_t u8App_GaaTransmitData[6][SPI_DATA_BYTES_16] = 
{
    0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
    0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
    0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
    0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
    0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
    0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF,
};
    
uint16_t u16App_GaaTransmitData[8][SPI_DATA_BYTES_16] = 
{ 
    {0xC0D1, 0xC0D1, 0xC0D2, 0xC0D3, 0xC0D4, 0xC0D5, 0xC0D6, 0xC0D7, 0xC0D8, 0xC0D9, 0xC0DA, 0xC0DB, 0xC0DC, 0xC0DD, 0xC0DE, 0xC0DF},
    {0xC1D1, 0xC1D1, 0xC1D2, 0xC1D3, 0xC1D4, 0xC1D5, 0xC1D6, 0xC1D7, 0xC1D8, 0xC1D9, 0xC1DA, 0xC1DB, 0xC1DC, 0xC1DD, 0xC1DE, 0xC1DF},
    {0xC2D1, 0xC2D1, 0xC2D2, 0xC2D3, 0xC2D4, 0xC2D5, 0xC2D6, 0xC2D7, 0xC2D8, 0xC2D9, 0xC2DA, 0xC2DB, 0xC2DC, 0xC2DD, 0xC2DE, 0xC2DF},
    {0xC3D1, 0xC3D1, 0xC3D2, 0xC3D3, 0xC3D4, 0xC3D5, 0xC3D6, 0xC3D7, 0xC3D8, 0xC3D9, 0xC3DA, 0xC3DB, 0xC3DC, 0xC3DD, 0xC3DE, 0xC3DF},
    {0xC4D1, 0xC4D1, 0xC4D2, 0xC4D3, 0xC4D4, 0xC4D5, 0xC4D6, 0xC4D7, 0xC4D8, 0xC4D9, 0xC4DA, 0xC4DB, 0xC4DC, 0xC4DD, 0xC4DE, 0xC4DF},
    {0xC5D1, 0xC5D1, 0xC5D2, 0xC5D3, 0xC5D4, 0xC5D5, 0xC5D6, 0xC5D7, 0xC5D8, 0xC5D9, 0xC5DA, 0xC5DB, 0xC5DC, 0xC5DD, 0xC5DE, 0xC5DF},
    {0xC6D1, 0xC6D1, 0xC6D2, 0xC6D3, 0xC6D4, 0xC6D5, 0xC6D6, 0xC6D7, 0xC6D8, 0xC6D9, 0xC6DA, 0xC6DB, 0xC6DC, 0xC6DD, 0xC6DE, 0xC6DF},
    {0xC7D1, 0xC7D1, 0xC7D2, 0xC7D3, 0xC7D4, 0xC7D5, 0xC7D6, 0xC7D7, 0xC7D8, 0xC7D9, 0xC7DA, 0xC7DB, 0xC7DC, 0xC7DD, 0xC7DE, 0xC7DF},
};
uint32_t u32App_GaaTransmitData[8][SPI_DATA_BYTES_16] = 
{ 
    {0x00C000D1, 0x00C000D1, 0x00C000D2, 0x00C000D3, 0x00C000D4, 0x00C000D5, 0x00C000D6, 0x00C000D7, 0x00C000D8, 0x00C000D9, 0x00C000DA, 0x00C000DB, 0x00C000DC, 0x00C000DD, 0x00C000DE, 0x00C000DF},
    {0x00C100D1, 0x00C100D1, 0x00C100D2, 0x00C100D3, 0x00C100D4, 0x00C100D5, 0x00C100D6, 0x00C100D7, 0x00C100D8, 0x00C100D9, 0x00C100DA, 0x00C100DB, 0x00C100DC, 0x00C100DD, 0x00C100DE, 0x00C100DF},
    {0x00C200D1, 0x00C200D1, 0x00C200D2, 0x00C200D3, 0x00C200D4, 0x00C200D5, 0x00C200D6, 0x00C200D7, 0x00C200D8, 0x00C200D9, 0x00C200DA, 0x00C200DB, 0x00C200DC, 0x00C200DD, 0x00C200DE, 0x00C200DF},
    {0x00C300D1, 0x00C300D1, 0x00C300D2, 0x00C300D3, 0x00C300D4, 0x00C300D5, 0x00C300D6, 0x00C300D7, 0x00C300D8, 0x00C300D9, 0x00C300DA, 0x00C300DB, 0x00C300DC, 0x00C300DD, 0x00C300DE, 0x00C300DF},
    {0x00C400D1, 0x00C400D1, 0x00C400D2, 0x00C400D3, 0x00C400D4, 0x00C400D5, 0x00C400D6, 0x00C400D7, 0x00C400D8, 0x00C400D9, 0x00C400DA, 0x00C400DB, 0x00C400DC, 0x00C400DD, 0x00C400DE, 0x00C400DF},
    {0x00C500D1, 0x00C500D1, 0x00C500D2, 0x00C500D3, 0x00C500D4, 0x00C500D5, 0x00C500D6, 0x00C500D7, 0x00C500D8, 0x00C500D9, 0x00C500DA, 0x00C500DB, 0x00C500DC, 0x00C500DD, 0x00C500DE, 0x00C500DF},
    {0x00C600D1, 0x00C600D1, 0x00C600D2, 0x00C600D3, 0x00C600D4, 0x00C600D5, 0x00C600D6, 0x00C600D7, 0x00C600D8, 0x00C600D9, 0x00C600DA, 0x00C600DB, 0x00C600DC, 0x00C600DD, 0x00C600DE, 0x00C600DF},
    {0x00C700D1, 0x00C700D1, 0x00C700D2, 0x00C700D3, 0x00C700D4, 0x00C700D5, 0x00C700D6, 0x00C700D7, 0x00C700D8, 0x00C700D9, 0x00C700DA, 0x00C700DB, 0x00C700DC, 0x00C700DD, 0x00C700DE, 0x00C700DF},
};

/* Receive data for SpiChannel0 */
uint8_t     u08App_GaaMasterReceiveData[SPI_CHANNEL_CNT][SPI_DATA_BYTES_16];
uint16_t    u16App_GaaMasterReceiveData[SPI_CHANNEL_CNT][SPI_DATA_BYTES_16];
uint32_t    u32App_GaaMasterReceiveData[SPI_CHANNEL_CNT][SPI_DATA_BYTES_16];

uint8_t     u08App_GaaSlaveReceiveData[SPI_CHANNEL_CNT][SPI_DATA_BYTES_16];
uint16_t    u16App_GaaSlaveReceiveData[SPI_CHANNEL_CNT][SPI_DATA_BYTES_16];
uint32_t    u32App_GaaSlaveReceiveData[SPI_CHANNEL_CNT][SPI_DATA_BYTES_16];

uint32_t gu32_spitx_cnt = 0;
uint32_t gu32_spierr_cnt = 0;


/*******************************************************************************
|    code Declaration  
|******************************************************************************/
void SpiIf_MSPI0_DirectMemoryMode_SyncTransmit(void);
void SpiIf_MSPI2_FIFOMode_SyncTransmit(void);

void SpiIf_Master_AsyncTransmitWriteRead_IB(void);
void SpiIf_Slave_AsyncTransmitWriteRead_IB(void);

void SpiIf_Init(void)
{
    uint32_t i;

    // Spi_Init(Spi_Config);

}

void SpiIf_Sample_Init(void)
{
    // /* This service is for setting up the interrupt mode */
    // App_GenReturnValue = Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
    // /* This service is for setting up the polling mode */
    // //App_GenReturnValue = Spi_SetAsyncMode(SPI_POLLING_MODE);

    // memset(u16App_GaaMasterReceiveData,0,sizeof(u16App_GaaMasterReceiveData));
    // memset(u16App_GaaSlaveReceiveData,0,sizeof(u16App_GaaSlaveReceiveData));
}


void SpiIf_Sample_test(void)
{
//     gu32_spitx_cnt++;

//     /* This service is for setting up the interrupt mode */
//     App_GenReturnValue = Spi_SetAsyncMode(SPI_INTERRUPT_MODE);

//     /* Get result of the Jobs */
//     App_GaaJobResult[0] = Spi_GetJobResult(Spi_SpiJob0);

//     /* Get result of the specified sequences */
//     App_GaaSeqResult[0] = Spi_GetSequenceResult(Spi_SpiSequence0);

//     /* This service is for writing data to the internal and external buffers */
//     //App_GenReturnValue = Spi_WriteIB(Spi_SpiChannel0, App_GaaTransmitData00);
//     App_GenReturnValue = Spi_SetupEB(SpiConf_SpiChannel_MasterCH0,  u16App_GaaTransmitData,     u16App_GaaMasterReceiveData,    SPI_DATA_BYTES_16);

//     /* This service is for setting up transmission in master unit */
//     App_GenReturnValue = Spi_AsyncTransmit(Spi_SpiSequence0);

//     /* Wait for transmission completed */
//     // do
//     // {
//     //     App_GenStatus = Spi_GetStatus();
//     // }
//     // while (SPI_IDLE != App_GenStatus);

//     /* Get result of the Jobs */
//     App_GaaJobResult[0] = Spi_GetJobResult(Spi_SpiJob0);

//     /* Get result of the specified sequences */
//     App_GaaSeqResult[0] = Spi_GetSequenceResult(Spi_SpiSequence0);
}


void SpiIf_timer_task(void)
{
    //Spi_MainFunction_Handling();
}



/******************************************************************************
    user callback 
******************************************************************************/
FUNC(void, SPI_APPL_CODE) SpiJob0Notification_000(void)
{

}
FUNC(void, SPI_APPL_CODE) SpiJob0Notification_001(void)
{

}
FUNC(void, SPI_APPL_CODE) SpiSequence0EndNotification_000(void)
{

}
FUNC(void, SPI_APPL_CODE) SpiSequence0EndNotification_001(void)
{

}

FUNC(void, SPI_APPL_CODE) SlaveCH0_SeqStartNotification(void)
{
    // static uint8 u8Index = 0u;

    // /* This service is for writing data to the internal and external buffers */
    // App_GenReturnValue = Spi_WriteIB(Spi_SpiChannel1, &u8App_GaaTransmitData[u8Index][0]);

    // /* This service is for setting up transmission in slave unit */
    // App_GenReturnValue = Spi_AsyncTransmit(Spi_SpiSequence1);

    // u8Index++;
    // if(u8Index >= 6)
    // {
    //     u8Index = 0u;
    // }

}




