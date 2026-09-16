#ifndef _USER_SPIIF_H_
#define _USER_SPIIF_H_

/*******************************************************************************
|    Other Header File Inclusion
|******************************************************************************/
#include "Spi.h"

/*******************************************************************************
|    Macro Definition
|******************************************************************************/
/*******************************************************************************
**                          Defines                                           **
*******************************************************************************/
/* Number of check points */
#define SPI_CHECK_POINTS   20U

/* Number of SpiChannels */
#define SPI_CHANNEL_CNT    8U

/* Data length of SpiChannels */
#define SPI_DATA_BYTES_8   8U
#define SPI_DATA_BYTES_16  16U
#define SPI_DATA_BYTES_64  64U

/* Number of handlers */
#define SPI_HW_NUM         2
#define SPI_SEQUENCE_NUM   2
#define SPI_JOB_NUM        2

/* Index of handlers */
#define SPI_JOB_0          0
#define SPI_JOB_1          1
#define SPI_SEQUENCE_0     0
#define SPI_SEQUENCE_1     1

/* Handler name of SpiChannels */
#define Spi_SpiChannel0     SpiConf_SpiChannel_MasterCH0
#define Spi_SpiChannel1     SpiConf_SpiChannel_SlaveCH0

/* Handler name of SpiSequences */
#define Spi_SpiSequence0    SpiConf_SpiSequence_SpiSequence_MasterCH0
#define Spi_SpiSequence1    SpiConf_SpiSequence_SpiSequence_SlaveCH0

/* Handler name of SpiJobs */
#define Spi_SpiJob0         SpiConf_SpiJob_SpiJob_MasterCH0
#define Spi_SpiJob1         SpiConf_SpiJob_SpiJob_SlaveCH0

/*******************************************************************************
**                  PEG & PBG: Function safety register definition            **
*******************************************************************************/
/* Registers base adrress */
#define GUARD_PE0CL0_temp    0xFFC6C000
#define GUARD_PE1CL0_temp    0xFFC6C100
#define PBGERRSLV40_temp     0xFFC75400
#define PBG40_temp           0xFFC75300
#define PBGERRSLV50_temp     0xFFC7B000
#define PBG52_temp           0xFFC7A500

/* PEGKCPROT */
#define PEGKCPROT0      (*(volatile uint32*)GUARD_PE0CL0_temp)
#define PEGKCPROT1      (*(volatile uint32*)GUARD_PE1CL0_temp)

/* PEGPROTm */
#define PEGPROT0(m)     (*(volatile uint32*)(GUARD_PE0CL0_temp + 0x40UL + m * 0x10UL))
#define PEGPROT1(m)     (*(volatile uint32*)(GUARD_PE1CL0_temp + 0x40UL + m * 0x10UL))

/* PEGSPIDm */
#define PEGSPID0(m)     (*(volatile uint32*)(GUARD_PE0CL0_temp + 0x44UL + m * 0x10UL))
#define PEGSPID1(m)     (*(volatile uint32*)(GUARD_PE1CL0_temp + 0x44UL + m * 0x10UL))

/* PBGKCPROTn */
#define PBGKCPROT40      (*(volatile uint32*)(PBGERRSLV40_temp + 0x18UL))
#define PBGKCPROT52      (*(volatile uint32*)(PBGERRSLV50_temp + 0x18UL))

/* PBGnPROT0_m */
#define PBG40PROT0(m)   (*(volatile uint32*)(PBG40_temp + m * 0x08UL))
#define PBG52PROT0(m)   (*(volatile uint32*)(PBG52_temp + m * 0x08UL))

/*******************************************************************************
|    typedef
|******************************************************************************/

/*******************************************************************************
|    variables Declaration  
|******************************************************************************/

/*******************************************************************************
|    Global Function Prototypes
|******************************************************************************/

void SpiIf_Init(void);
void SpiIf_Sample_Init(void);
void SpiIf_Sample_test(void);
void SpiIf_timer_task(void);

#endif
