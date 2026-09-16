/*===========================================================================*/
/* Module       = u2b10.ld                                                    */
/* SW-VERSION   = CN1.0                                                      */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* (c) 2018-2020 Renesas Electronics Corporation. All rights reserved.       */
/*===========================================================================*/
/* Purpose:     Template of common linker directive file                     */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/
/* Environment:                                                              */
/*              Device:         u2b10                                         */
/*              IDE:            GHS Multi for V800  V7.1.6/2018.1.5          */
/*===========================================================================*/

MEMORY
{
  iROM_A      : ORIGIN = 0x00000000  ,  LENGTH = 3072k       /* Code flash of BankA */
  iROM_A_TOP  : ORIGIN = .           ,  LENGTH = 0           
  iROM_B      : ORIGIN = 0x00300000  ,  LENGTH = 3072k       /* Code flash of BankB */
  iROM_B_TOP  : ORIGIN = .           ,  LENGTH = 0           
  iROM_C      : ORIGIN = 0x00600000  ,  LENGTH = 2048k       /* Code flash of BankC */
  iROM_C_TOP  : ORIGIN = .           ,  LENGTH = 0           
  iROM_D      : ORIGIN = 0x00800000  ,  LENGTH = 2048k       /* Code flash of BankD */
  iROM_D_TOP  : ORIGIN = .           ,  LENGTH = 0           

  iRAM_3      : ORIGIN = 0xFD600000  ,  LENGTH = 64k         /* Local RAM of PE3 */
  iRAM_3_TOP  : ORIGIN = .           ,  LENGTH = 0           
  iRAM_2      : ORIGIN = 0xFD800000  ,  LENGTH = 64k         /* Local RAM of PE2 */
  iRAM_2_TOP  : ORIGIN = .           ,  LENGTH = 0           
  iRAM_1      : ORIGIN = 0xFDA00000  ,  LENGTH = 64k         /* Local RAM of PE1 */
  iRAM_1_TOP  : ORIGIN = .           ,  LENGTH = 0           
  iRAM_0      : ORIGIN = 0xFDC00000  ,  LENGTH = 64k         /* Local RAM of PE0 */
  iRAM_0_TOP  : ORIGIN = .           ,  LENGTH = 0           
  iRAM_S      : ORIGIN = 0xFDE00000  ,  LENGTH = 64k         /* Local RAM of self */
  iRAM_S_TOP  : ORIGIN = .           ,  LENGTH = 0           

  cRAM_00     : ORIGIN = 0xFE000000  ,  LENGTH = 352k        /* Cluster RAM 0 */
  cRAM_00_TOP : ORIGIN = .           ,  LENGTH = 0           
  cRAM_0R     : ORIGIN = 0xFE058000  ,  LENGTH = 32k         /* Cluster RAM 1 */
  cRAM_0R_TOP : ORIGIN = .           ,  LENGTH = 0           
  cRAM_01     : ORIGIN = 0xFE060000  ,  LENGTH = 128k        /* Cluster RAM 2 */
  cRAM_01_TOP : ORIGIN = .           ,  LENGTH = 0           
  cRAM_1      : ORIGIN = 0xFE080000  ,  LENGTH = 384k        /* Cluster RAM 3(Retention RAM) */
  cRAM_1_TOP  : ORIGIN = .           ,  LENGTH = 0           
  cRAM_1_R    : ORIGIN = 0xFE0E0000  ,  LENGTH = 128k        /* Cluster RAM 3(Retention RAM) */
  cRAM_1_R_TOP: ORIGIN = .           ,  LENGTH = 0           

  CSA_BS      : ORIGIN = 0xFF321000  ,  LENGTH = 4K          
  
}

SECTIONS
{
  .intvect_PE0                            align(16)        0x00000000     :>iROM_A      /*start of interrupt vector. This section contains RESET and exception table for PE0 */
  .inttable_PE0                           align(0x200)                    :>.           
  .inttable_PE0_end                                                       :>.           
  .intvect_PE1                            align(16)        0x00002000     :>.           /*start of interrupt vector. This section contains exception table for PE1 */
  .inttable_PE1                           align(0x200)                    :>.           
  .inttable_PE1_end                                                       :>.           
  .intvect_PE2                            align(16)        0x00004000     :>.           /*start of interrupt vector. This section contains exception table for PE2 */
  .inttable_PE2                           align(0x200)                    :>.           
  .inttable_PE2_end                                                       :>.           
  .intvect_PE3                            align(16)        0x00006000     :>.           /*start of interrupt vector. This section contains exception table for PE3 */
  .inttable_PE3                           align(0x200)                    :>.           
  .inttable_PE3_end                                                       :>.           
  .intvect_PE4                            align(16)        0x00008000     :>.           /*start of interrupt vector. This section contains exception table for PE2 */
  .inttable_PE4                           align(0x200)                    :>.           
  .inttable_PE4_end                                                       :>.           
  .intvect_PE5                            align(16)        0x0000A000     :>.           /*start of interrupt vector. This section contains exception table for PE3 */
  .inttable_PE5                           align(0x200)                    :>.           
  .inttable_PE5_end                                                       :>.           


  /* program code area */
  .text                                   align(200)       0x0000C000     :>.           
  
  .rosbase                                align(4)                        :>.           /* initialize textpointer TP for SDA addressing */
  .rosdata                                align(4)                        :>.           /*constant datas in SDA area */
  
  /* MCAL Memmap Area */
  .CONST_ROM_1BIT                                                         :>.           
  .CONST_ROM_8BIT                                                         :>.           
  .CONST_ROM_16BIT                                                        :>.           
  .CONST_ROM_32BIT                                                        :>.           
  .CONST_ROM_UNSPECIFIED                                                  :>.           
  .CONST_ROM_PTR                                                          :>.           
  .CONST_FAR_ROM_1BIT                                                     :>.           
  .CONST_FAR_ROM_8BIT                                                     :>.           
  .CONST_FAR_ROM_16BIT                                                    :>.           
  .CONST_FAR_ROM_32BIT                                                    :>.           
  .CONST_FAR_ROM_UNSPECIFIED                                              :>.           
  
  /* MCAL Driver code area *****/
  .DIO_PUBLIC_CODE_ROM                                                    :>.           
  .DIO_PRIVATE_CODE_ROM                                                   :>.           
  .DIO_APPL_CODE_ROM                                                      :>.           
  .GPT_PUBLIC_CODE_ROM                                                    :>.           
  .GPT_PRIVATE_CODE_ROM                                                   :>.           
  .GPT_APPL_CODE_ROM                                                      :>.           
  .GPT_FAST_CODE_ROM                                                      :>.           
  .OCU_PUBLIC_CODE_ROM                                                    :>.           
  .OCU_PRIVATE_CODE_ROM                                                   :>.           
  .OCU_APPL_CODE_ROM                                                      :>.           
  .OCU_FAST_CODE_ROM                                                      :>.           
  .ICU_PUBLIC_CODE_ROM                                                    :>.           
  .ICU_PRIVATE_CODE_ROM                                                   :>.           
  .ICU_APPL_CODE_ROM                                                      :>.           
  .ICU_FAST_CODE_ROM                                                      :>.           
  .PORT_PUBLIC_CODE_ROM                                                   :>.           
  .PORT_PRIVATE_CODE_ROM                                                  :>.           
  .PORT_APPL_CODE_ROM                                                     :>.           
  .PWM_PUBLIC_CODE_ROM                                                    :>.           
  .PWM_PRIVATE_CODE_ROM                                                   :>.           
  .PWM_APPL_CODE_ROM                                                      :>.           
  .PWM_FAST_CODE_ROM                                                      :>.           
  .SPI_PUBLIC_CODE_ROM                                                    :>.           
  .SPI_PRIVATE_CODE_ROM                                                   :>.           
  .SPI_APPL_CODE_ROM                                                      :>.           
  .SPI_FAST_CODE_ROM                                                      :>.           
  .WDG_PUBLIC_CODE_ROM                                                    :>.           
  .WDG_PRIVATE_CODE_ROM                                                   :>.           
  .WDG_FAST_CODE_ROM                                                      :>.           
  .CAN_PUBLIC_CODE_ROM                                                    :>.           
  .CAN_PRIVATE_CODE_ROM                                                   :>.           
  .CAN_CALLOUT_CODE_ROM                                                   :>.           
  .CAN_FAST_CODE_ROM                                                      :>.           
  .ADC_PUBLIC_CODE_ROM                                                    :>.           
  .ADC_PRIVATE_CODE_ROM                                                   :>.           
  .ADC_APPL_CODE_ROM                                                      :>.           
  .ADC_FAST_CODE_ROM                                                      :>.           
  .LIN_PUBLIC_CODE_ROM                                                    :>.           
  .LIN_PRIVATE_CODE_ROM                                                   :>.           
  .LIN_APPL_CODE_ROM                                                      :>.           
  .LIN_FAST_CODE_ROM                                                      :>.           
  .FR_59_RENESAS_PUBLIC_CODE_ROM                                          :>.           
  .FR_59_RENESAS_PRIVATE_CODE_ROM                                         :>.           
  .FR_59_RENESAS_APPL_CODE_ROM                                            :>.           
  .MCU_PUBLIC_CODE_ROM                                                    :>.           
  .MCU_PRIVATE_CODE_ROM                                                   :>.           
  .MCU_APPL_CODE_ROM                                                      :>.           
  .MCU_FAST_CODE_ROM                                                      :>.           
  .MCU_CODE_RRAM_INTVEC                   align(4)                        :>.           
  .MCU_CR_CODE_RRAM                       align(4)                        :>.           
  .MCU_CR_CODE_ROM                        align(4)                        :>.           
  .FLS_PUBLIC_CODE_ROM                                                    :>.           
  .FEE_PUBLIC_CODE_ROM                                                    :>.           
  .FLS_PRIVATE_CODE_ROM                                                   :>.           
  .FEE_PRIVATE_CODE_ROM                                                   :>.           
  .FLS_APPL_CODE_ROM                                                      :>.           
  .FLS_FAST_CODE_ROM                                                      :>.           
  .MEM_59_RENESAS_PUBLIC_CODE_ROM                                         :>.           
  .MEM_59_RENESAS_PRIVATE_CODE_ROM                                        :>.           
  .MEM_59_RENESAS_APPL_CODE_ROM                                           :>.           
  .MEM_59_RENESAS_FAST_CODE_ROM                                           :>.           
  .ETH_PUBLIC_CODE_ROM                                                    :>.           
  .ETH_PRIVATE_CODE_ROM                                                   :>.           
  .ETH_FAST_CODE_ROM                                                      :>.           
  .FLSTST_PUBLIC_CODE_ROM                                                 :>.           
  .FLSTST_PRIVATE_CODE_ROM                                                :>.           
  .FLSTST_APPL_CODE_ROM                                                   :>.           
  .FLSTST_CRCSIG_STORE                                                    :>.           
  .FLSTST_CRCSIG_STORE_20x401640          align(2)                        :>.           
  .RAMTST_PUBLIC_CODE_ROM                                                 :>.           
  .RAMTST_PRIVATE_CODE_ROM                                                :>.           
  .RAMTST_APPL_CODE_ROM                                                   :>.           
  .MEMACC_PUBLIC_CODE_ROM                                                 :>.           
  .MEMACC_PRIVATE_CODE_ROM                                                :>.           
  .MEMACC_APPL_CODE_ROM                                                   :>.           
  .MEMACC_FAST_CODE_ROM                                                   :>.           
  
  
  .ROM.RAM_1BIT                           ROM(.RAM_1BIT)                  :>.           
  .ROM.RAM_8BIT                           ROM(.RAM_8BIT)                  :>.           
  .ROM.RAM_16BIT                          ROM(.RAM_16BIT)                 :>.           
  .ROM.RAM_32BIT                          ROM(.RAM_32BIT)                 :>.           
  .ROM.RAM_UNSPECIFIED                    ROM(.RAM_UNSPECIFIED)           :>.           
  .ROM.RAM_INIT_PTR                       ROM(.RAM_INIT_PTR)              :>.           
  .ROM.FAST_RAM_1BIT                      ROM(.FAST_RAM_1BIT)             :>.           
  .ROM.FAST_RAM_8BIT                      ROM(.FAST_RAM_8BIT)             :>.           
  .ROM.FAST_RAM_16BIT                     ROM(.FAST_RAM_16BIT)            :>.           
  .ROM.FAST_RAM_32BIT                     ROM(.FAST_RAM_32BIT)            :>.           
  .ROM.FAST_RAM_UNSPECIFIED               ROM(.FAST_RAM_UNSPECIFIED)      :>.           
  .ROM.FAST_RAM_INIT_PTR                  ROM(.FAST_RAM_INIT_PTR)         :>.           
  
  
  .ROM.RAM_1BIT_CORE0                     ROM(.RAM_1BIT_CORE0)            :>.           
  .ROM.RAM_8BIT_CORE0                     ROM(.RAM_8BIT_CORE0)            :>.           
  .ROM.RAM_16BIT_CORE0                    ROM(.RAM_16BIT_CORE0)           :>.           
  .ROM.RAM_32BIT_CORE0                    ROM(.RAM_32BIT_CORE0)           :>.           
  .ROM.RAM_UNSPECIFIED_CORE0              ROM(.RAM_UNSPECIFIED_CORE0)     :>.           
  .ROM.RAM_INIT_PTR_CORE0                 ROM(.RAM_INIT_PTR_CORE0)        :>.           
  .ROM.FAST_RAM_1BIT_CORE0                ROM(.FAST_RAM_1BIT_CORE0)       :>.           
  .ROM.FAST_RAM_8BIT_CORE0                ROM(.FAST_RAM_8BIT_CORE0)       :>.           
  .ROM.FAST_RAM_16BIT_CORE0               ROM(.FAST_RAM_16BIT_CORE0)      :>.           
  .ROM.FAST_RAM_32BIT_CORE0               ROM(.FAST_RAM_32BIT_CORE0)      :>.           
  .ROM.FAST_RAM_UNSPECIFIED_CORE0         ROM(.FAST_RAM_UNSPECIFIED_CORE0) :>.           
  .ROM.FAST_RAM_INIT_PTR_CORE0            ROM(.FAST_RAM_INIT_PTR_CORE0)   :>.           
  
  
  .ROM.RAM_1BIT_CORE1                     ROM(.RAM_1BIT_CORE1)            :>.           
  .ROM.RAM_8BIT_CORE1                     ROM(.RAM_8BIT_CORE1)            :>.           
  .ROM.RAM_16BIT_CORE1                    ROM(.RAM_16BIT_CORE1)           :>.           
  .ROM.RAM_32BIT_CORE1                    ROM(.RAM_32BIT_CORE1)           :>.           
  .ROM.RAM_UNSPECIFIED_CORE1              ROM(.RAM_UNSPECIFIED_CORE1)     :>.           
  .ROM.RAM_INIT_PTR_CORE1                 ROM(.RAM_INIT_PTR_CORE1)        :>.           
  .ROM.FAST_RAM_1BIT_CORE1                ROM(.FAST_RAM_1BIT_CORE1)       :>.           
  .ROM.FAST_RAM_8BIT_CORE1                ROM(.FAST_RAM_8BIT_CORE1)       :>.           
  .ROM.FAST_RAM_16BIT_CORE1               ROM(.FAST_RAM_16BIT_CORE1)      :>.           
  .ROM.FAST_RAM_32BIT_CORE1               ROM(.FAST_RAM_32BIT_CORE1)      :>.           
  .ROM.FAST_RAM_UNSPECIFIED_CORE1         ROM(.FAST_RAM_UNSPECIFIED_CORE1) :>.           
  .ROM.FAST_RAM_INIT_PTR_CORE1            ROM(.FAST_RAM_INIT_PTR_CORE1)   :>.           
  
  .romdata                                ROM(.data)                      :>iROM_B      /*constant data to initialize variables (copied to RAM at startup)*/
  .romsdata                               ROM(.sdata)                     :>.           /*constant data to initialize variables in SDA area (copied to RAM at startup)*/
  .romtdata                               ROM(.tdata)                     :>.           /*constant data to initialize variables in TDA area (copied to RAM at startup)*/
  
  .robase                                 align(4)                        :>.           /*initialize textpointer TP for SDA addressing */
  .rodata                                 align(4)                        :>.           /*constant datas in normal area */
  
  
  /* MCAL Driver Database area */
  .DIO_CFG_DATA_1BIT                                                      :>.           
  .DIO_CFG_DATA_8BIT                                                      :>.           
  .DIO_CFG_DATA_16BIT                     align(4)                        :>.           
  .DIO_CFG_DATA_32BIT                     align(4)                        :>.           
  .DIO_CFG_DATA_UNSPECIFIED               align(4)                        :>.           
  .GPT_CFG_DATA_1BIT                                                      :>.           
  .GPT_CFG_DATA_8BIT                                                      :>.           
  .GPT_CFG_DATA_16BIT                     align(4)                        :>.           
  .GPT_CFG_DATA_32BIT                     align(4)                        :>.           
  .GPT_CFG_DATA_UNSPECIFIED               align(4)                        :>.           
  .OCU_CFG_DATA_UNSPECIFIED               align(4)                        :>.           
  .ICU_CFG_DATA_1BIT                                                      :>.           
  .ICU_CFG_DATA_8BIT                                                      :>.           
  .ICU_CFG_DATA_16BIT                     align(4)                        :>.           
  .ICU_CFG_DATA_32BIT                     align(4)                        :>.           
  .ICU_CFG_DATA_UNSPECIFIED               align(4)                        :>.           
  .PORT_CFG_DATA_1BIT                                                     :>.           
  .PORT_CFG_DATA_8BIT                                                     :>.           
  .PORT_CFG_DATA_16BIT                    align(4)                        :>.           
  .PORT_CFG_DATA_32BIT                    align(4)                        :>.           
  .PORT_CFG_DATA_UNSPECIFIED              align(4)                        :>.           
  .PWM_CFG_DATA_1BIT                                                      :>.           
  .PWM_CFG_DATA_8BIT                                                      :>.           
  .PWM_CFG_DATA_16BIT                     align(4)                        :>.           
  .PWM_CFG_DATA_32BIT                     align(4)                        :>.           
  .PWM_CFG_DATA_UNSPECIFIED               align(4)                        :>.           
  .SPI_CFG_DATA_1BIT                                                      :>.           
  .SPI_CFG_DATA_8BIT                                                      :>.           
  .SPI_CFG_DATA_16BIT                     align(4)                        :>.           
  .SPI_CFG_DATA_32BIT                     align(4)                        :>.           
  .SPI_CFG_DATA_UNSPECIFIED               align(4)                        :>.           
  .WDG_CFG_DATA_UNSPECIFIED               align(4)                        :>.           
  .FLS_CFG_DATA_UNSPECIFIED               align(4)                        :>.           
  .MEM_59_RENESAS_CFG_DATA_UNSPECIFIED    align(4)                        :>.           
  .FEE_CFG_DATA_UNSPECIFIED               align(4)                        :>.           
  .CAN_CFG_DATA_1BIT                                                      :>.           
  .CAN_CFG_DATA_8BIT                                                      :>.           
  .CAN_CFG_DATA_16BIT                     align(4)                        :>.           
  .CAN_CFG_DATA_32BIT                     align(4)                        :>.           
  .CAN_CFG_DATA_UNSPECIFIED               align(4)                        :>.           
  .LIN_CFG_DATA_1BIT                                                      :>.           
  .LIN_CFG_DATA_8BIT                                                      :>.           
  .LIN_CFG_DATA_16BIT                     align(4)                        :>.           
  .LIN_CFG_DATA_32BIT                     align(4)                        :>.           
  .LIN_CFG_DATA_UNSPECIFIED               align(4)                        :>.           
  .FR_59_RENESAS_CFG_DATA_UNSPECIFIED     align(4)                        :>.           
  .ADC_CFG_DATA_1BIT                                                      :>.           
  .ADC_CFG_DATA_POSTBUILD_8BIT                                            :>.           
  .ADC_CFG_DATA_POSTBUILD_16BIT           align(4)                        :>.           
  .ADC_CFG_DATA_POSTBUILD_32BIT           align(4)                        :>.           
  .ADC_CFG_DATA_POSTBUILD_UNSPECIFIED     align(4)                        :>.           
  .ADC_CFG_DATA_POSTBUILD_PTR             align(4)                        :>.           
  .MCU_CFG_DATA_1BIT                                                      :>.           
  .MCU_CFG_DATA_8BIT                                                      :>.           
  .MCU_CFG_DATA_16BIT                     align(4)                        :>.           
  .MCU_CFG_DATA_32BIT                     align(4)                        :>.           
  .MCU_CFG_DATA_UNSPECIFIED               align(4)                        :>.           
  .ETH_CFG_DATA_UNSPECIFIED               align(4)                        :>.           
  .FLSTST_CFG_DATA_1BIT                                                   :>.           
  .FLSTST_CFG_DATA_8BIT                                                   :>.           
  .FLSTST_CFG_DATA_16BIT                  align(4)                        :>.           
  .FLSTST_CFG_DATA_32BIT                  align(4)                        :>.           
  .FLSTST_CFG_DATA_UNSPECIFIED            align(4)                        :>.           
  .RAMTST_CFG_DATA_1BIT                                                   :>.           
  .RAMTST_CFG_DATA_8BIT                                                   :>.           
  .RAMTST_CFG_DATA_16BIT                  align(4)                        :>.           
  .RAMTST_CFG_DATA_32BIT                  align(4)                        :>.           
  .RAMTST_CFG_DATA_UNSPECIFIED            align(4)                        :>.           
  .MEMACC_CFG_DBTOC_UNSPECIFIED           align(4)                        :>.           
  .MEMACC_CFG_DATA_1BIT                                                   :>.           
  .MEMACC_CFG_DATA_8BIT                                                   :>.           
  .MEMACC_CFG_DATA_16BIT                  align(4)                        :>.           
  .MEMACC_CFG_DATA_32BIT                  align(4)                        :>.           
  .MEMACC_CFG_DATA_UNSPECIFIED            align(4)                        :>.           
  
  /* RFD28F */
  .R_RFD_ROSDATA_VERSION_COMMON           align(4)                        :>.           /* RFD Version information (For rosdata attribute) */
  .R_RFD_RODATA_VERSION_COMMON            align(4)                        :>.           /* RFD Version information (For rodata attribute) */
  .R_RFD_ROSDATA_VERSION_CF               align(4)                        :>.           /* RFD Version information (For rosdata attribute) */
  .R_RFD_RODATA_VERSION_CF                align(4)                        :>.           /* RFD Version information (For rodata attribute) */
  .R_RFD_ROSDATA_VERSION_DF               align(4)                        :>.           /* RFD Version information (For rosdata attribute) */
  .R_RFD_RODATA_VERSION_DF                align(4)                        :>.           /* RFD Version information (For rodata attribute) */
  .R_RFD_ROSDATA_EXTRA                    align(4)                        :>.           /* RFD const data for HW Property (For rosdata attribute) */
  .R_RFD_RODATA_EXTRA                     align(4)                        :>.           /* RFD const data for HW Property (For rodata attribute) */
  .R_RFD_CODE_COMMON                      align(4)                        :>.           /* RFD Code area for Common Flash Component located in ROM */
  .R_RFD_CODE_COMMON_RAM_NO_BGO           align(4)                        :>.           /* RFD Code area for Common Flash Component located in ROM */
  .R_RFD_CODE_USEROWN_COMMON              align(4)                        :>.           /* RFD Code area for Common Flash Component located in ROM */
  .R_RFD_CODE_DF                          align(4)                        :>.           /* RFD Code area for Data Flash Component located in ROM */
  .R_RFD_CODE_CF                          align(4)                        :>.           /* RFD Code area for Code Flash Component located in ROM */
  .R_RFD_CODE_CF_RAM_NO_BGO               align(4)                        :>.           /* RFD Code area for Code Flash Component located in ROM */
  .R_RFD_CODE_EXTRA                       align(4)                        :>.           /* RFD Code area for Code Flash Component located in ROM */
  .R_RFD_CODE_EX_PROT                     align(4)                        :>.           /* RFD area for prevent ECC error */
  
  .fixaddr                                align(4)                        :>.           /*ghs internal (compiler) */
  .fixtype                                align(4)                        :>.           /*ghs internal (compiler) */
  .secinfo                                align(4)                        :>.           /*ghs internal (runtime library) */
  .syscall                                align(4)                        :>.           /*ghs internal (linker) */
  
  
  
  
  
  /* Start of cluster RAM area (cRAM_00) */
  .data                                   align(4)                        :>cRAM_00     /* initialized data */
  .zdata                                  align(4)                        :>.           /* initialized data in ZDA area */
  .sldata                                 align(4)                        :>.           /* initialized data in LSDA area */
  .sdata                                  align(4)                        :>.           /* initialized data in SDA area */
  .bss                                    align(4)                        :>.           /* zero initialized data */
  .zbss                                   align(4)                        :>.           /* zero initialized data in ZDA area */
  .slbss                                  align(4)                        :>.           /* zero initialized data in LSDA area */
  .sbss                                   align(4)                        :>.           /* zero initialized data in SDA area */
  .sdabase                                align(4)                        :>.           /* initialize global pointer GP for SDA addressing */
  .ramtext                                align(128)       MAX_SIZE(0x2000):>.           /* initialized and zero-initialized data in TDA area */
  .tdata                                  align(4)         MAX_SIZE(0x0100):>.           /* initialized and zero-initialized data in TDA area */
  .exec                                   align(128)                      :>.           
  .mev_address                            align(32)                       :>.           /* Mutual Exclusive Variable is used for Sync flags between multi core */
  .SpinlockStatus                         pad(0x00FF)                     :>.           /* initialized data */
  .R_RFD_SBSS                             align(4)                        :>.           /* Data without initialization value */
  .R_RFD_BSS                              align(4)                        :>.           /* Data without initialization value */
  .top_of_RAM00                           align(4)                        :>cRAM_00_TOP 
  
  /* Start of cluster RAM area 01 (cRAM_01) */
  .stack                                  align(0x6000)    0xFE060000     :>cRAM_01     /* definition of stack size */
  .stack_end                                                              :>.           /* definition of stack size */
  .stack1_PE1                             align(0x6000)    0xFE066000     :>.           /* definition of stack size */
  .stack1_PE1_end                                                         :>.           /* definition of stack size */
  .stack1_PE2                             align(0x6000)    0xFE06C000     :>.           /* definition of stack size */
  .stack1_PE2_end                                                         :>.           /* definition of stack size */
  .heap_FreeRTOS                          align(0x6000)    0xFE072000     :>.           /* definition of stack size */
  .heap_FreeRTOS_end                                                      :>.           /* definition of stack size */
  .heapbase                               pad(addr(cRAM_01_TOP)-addr(.heapbase)) align(4) NOCLEAR:>.           /* definition of heap size */
  .top_of_RAM01                           align(4)                        :>cRAM_01_TOP 
  
  
  .RAM_1BIT_CORE0                         NOCLEAR                         :>cRAM_1      /* initialized data */
  .RAM_8BIT_CORE0                         NOCLEAR                         :>.           /* initialized data in SDA area */
  .RAM_16BIT_CORE0                        NOCLEAR          align(4)       :>.           /* initialized data in SDA area */
  .RAM_32BIT_CORE0                        NOCLEAR          align(4)       :>.           /* initialized data in SDA area */
  .RAM_UNSPECIFIED_CORE0                  NOCLEAR          align(4)       :>.           /* initialized data in SDA area */
  .RAM_INIT_PTR_CORE0                     NOCLEAR          align(4)       :>.           /* initialized data in SDA area */
  .FAST_RAM_1BIT_CORE0                    NOCLEAR                         :>.           /* initialized data in SDA area */
  .FAST_RAM_8BIT_CORE0                    NOCLEAR                         :>.           /* initialized data in SDA area */
  .FAST_RAM_16BIT_CORE0                   NOCLEAR          align(4)       :>.           /* initialized data in SDA area */
  .FAST_RAM_32BIT_CORE0                   NOCLEAR          align(4)       :>.           /* initialized data in SDA area */
  .FAST_RAM_UNSPECIFIED_CORE0             NOCLEAR          align(4)       :>.           /* initialized data in SDA area */
  .FAST_RAM_INIT_PTR_CORE0                NOCLEAR          align(4)       :>.           /* initialized data in SDA area */
  
  /* Uninitialized data in SDA area */
  .NOINIT_RAM_1BIT_CORE0                  NOCLEAR                         :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_8BIT_CORE0                  NOCLEAR                         :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_16BIT_CORE0                 NOCLEAR          align(4)       :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_32BIT_CORE0                 NOCLEAR          align(4)       :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_UNSPECIFIED_CORE0           NOCLEAR          align(4)       :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_PTR_CORE0                   NOCLEAR          align(4)       :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_64BIT_CORE0                 NOCLEAR          align(8)       :>.           /* no initialized data in SDA area */
  .MEMACC_CFG_RAM_UNSPECIFIED             NOCLEAR                         :>.           /* no initialized data in SDA area */
  
  /* Initialized data in SDA area */
  .RAM_1BIT                               align(4)         NOCLEAR        :>.           /* initialized data in SDA area */
  .RAM_8BIT                               align(4)         NOCLEAR        :>.           /* initialized data in SDA area */
  .RAM_16BIT                              align(4)         NOCLEAR        :>.           /* initialized data in SDA area */
  .RAM_32BIT                              align(4)         NOCLEAR        :>.           /* initialized data in SDA area */
  .RAM_UNSPECIFIED                        align(4)         NOCLEAR        :>.           /* initialized data in SDA area */
  .RAM_INIT_PTR                           align(4)         NOCLEAR        :>.           /* initialized data in SDA area */
  .FAST_RAM_1BIT                          align(4)         NOCLEAR        :>.           /* initialized data in SDA area */
  .FAST_RAM_8BIT                          align(4)         NOCLEAR        :>.           /* initialized data in SDA area */
  .FAST_RAM_16BIT                         align(4)         NOCLEAR        :>.           /* initialized data in SDA area */
  .FAST_RAM_32BIT                         align(4)         NOCLEAR        :>.           /* initialized data in SDA area */
  .FAST_RAM_UNSPECIFIED                   align(4)         NOCLEAR        :>.           /* initialized data in SDA area */
  .FAST_RAM_INIT_PTR                      align(4)         NOCLEAR        :>.           /* initialized data in SDA area */
  .RAM_1BIT_CORE1                         NOCLEAR                         :>.           
  .RAM_8BIT_CORE1                         NOCLEAR                         :>.           
  .RAM_16BIT_CORE1                        NOCLEAR          align(4)       :>.           
  .RAM_32BIT_CORE1                        NOCLEAR          align(4)       :>.           
  .RAM_UNSPECIFIED_CORE1                  NOCLEAR          align(4)       :>.           
  .RAM_INIT_PTR_CORE1                     NOCLEAR          align(4)       :>.           
  .FAST_RAM_1BIT_CORE1                    NOCLEAR                         :>.           
  .FAST_RAM_8BIT_CORE1                    NOCLEAR                         :>.           
  .FAST_RAM_16BIT_CORE1                   NOCLEAR          align(4)       :>.           
  .FAST_RAM_32BIT_CORE1                   NOCLEAR          align(4)       :>.           
  .FAST_RAM_UNSPECIFIED_CORE1             NOCLEAR          align(4)       :>.           
  .FAST_RAM_INIT_PTR_CORE1                NOCLEAR          align(4)       :>.           
  
  /* Uninitialized data in SDA area */
  .NOINIT_RAM_1BIT                        align(4)         NOCLEAR        :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_8BIT                        align(4)         NOCLEAR        :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_16BIT                       align(4)         NOCLEAR        :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_32BIT                       align(4)         NOCLEAR        :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_UNSPECIFIED                 align(4)         NOCLEAR        :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_PTR                         align(4)         NOCLEAR        :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_64BIT                       align(8)         NOCLEAR        :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_1BIT_CORE1                  NOCLEAR                         :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_8BIT_CORE1                  NOCLEAR                         :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_16BIT_CORE1                 NOCLEAR          align(4)       :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_32BIT_CORE1                 NOCLEAR          align(4)       :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_UNSPECIFIED_CORE1           NOCLEAR          align(4)       :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_PTR_CORE1                   NOCLEAR          align(4)       :>.           /* no initialized data in SDA area */
  .NOINIT_RAM_64BIT_CORE1                 NOCLEAR          align(8)       :>.           /* no initialized data in SDA area */
  
  /* MCAL Driver Configuration PE0 internal RAM area */
  /* Uninitialized data in SDA area */
  .DIO_CFG_RAM_UNSPECIFIED_CORE0          NOCLEAR                         :>.           
  .GPT_CFG_RAM_UNSPECIFIED_CORE0          NOCLEAR                         :>.           
  .ICU_CFG_RAM_UNSPECIFIED_CORE0          NOCLEAR                         :>.           
  .PWM_CFG_RAM_UNSPECIFIED_CORE0          NOCLEAR                         :>.           
  .SPI_CFG_RAM_UNSPECIFIED_CORE0          NOCLEAR                         :>.           
  .CAN_CFG_RAM_UNSPECIFIED_CORE0          NOCLEAR                         :>.           
  .ADC_CFG_RAM_UNSPECIFIED_CORE0          NOCLEAR                         :>.           
  .LIN_CFG_RAM_UNSPECIFIED_CORE0          NOCLEAR                         :>.           
  .MCU_CFG_RAM_UNSPECIFIED_CORE0          NOCLEAR                         :>.           
  .PORT_CFG_RAM_UNSPECIFIED_CORE0         NOCLEAR                         :>.           
  .FLSTST_CFG_RAM_UNSPECIFIED_CORE0       NOCLEAR                         :>.           
  .FR_59_RENESAS_CFG_RAM_UNSPECIFIED_CORE0NOCLEAR                         :>.           
  .FR_59_RENESAS_VAR_POWER_ON_INIT_CORE0  NOCLEAR                         :>.           
  .FLS_BUFFER_CODE_RAM_CORE0              align(4)                        :>.           /* Temporary Buffer */
  .FLS_USER_BUFFER_CODE_RAM_CORE0         align(4)                        :>.           /* Application Buffer */
  
  /* MCAL Driver Configuration PE1 internal RAM area */
  /* Uninitialized data in SDA area */
  .DIO_CFG_RAM_UNSPECIFIED_CORE1          NOCLEAR                         :>.           
  .GPT_CFG_RAM_UNSPECIFIED_CORE1          NOCLEAR                         :>.           
  .ICU_CFG_RAM_UNSPECIFIED_CORE1          NOCLEAR                         :>.           
  .PWM_CFG_RAM_UNSPECIFIED_CORE1          NOCLEAR                         :>.           
  .SPI_CFG_RAM_UNSPECIFIED_CORE1          NOCLEAR                         :>.           
  .CAN_CFG_RAM_UNSPECIFIED_CORE1          NOCLEAR                         :>.           
  .ADC_CFG_RAM_UNSPECIFIED_CORE1          NOCLEAR                         :>.           
  .LIN_CFG_RAM_UNSPECIFIED_CORE1          NOCLEAR                         :>.           
  .MCU_CFG_RAM_UNSPECIFIED_CORE1          NOCLEAR                         :>.           
  .FLS_BUFFER_CODE_RAM_CORE1              align(4)                        :>.           /* Temporary Buffer */
  .FLS_USER_BUFFER_CODE_RAM_CORE1         align(4)                        :>.           /* Application Buffer */
  .FLSTST_CFG_RAM_UNSPECIFIED_CORE1       NOCLEAR                         :>.           
  .RAMTST_CFG_RAM_UNSPECIFIED_CORE1       NOCLEAR                         :>.           
  .FR_59_RENESAS_CFG_RAM_UNSPECIFIED_CORE1NOCLEAR                         :>.           
  .FR_59_RENESAS_VAR_POWER_ON_INIT_CORE1  NOCLEAR                         :>.           
  
  /* MCAL Driver Configuration cluster Ram area *****/ 
  /* Uninitialized data in SDA area */
  .DIO_CFG_RAM_UNSPECIFIED                NOCLEAR                         :>.           
  .GPT_CFG_RAM_UNSPECIFIED                NOCLEAR                         :>.           
  .ICU_CFG_RAM_UNSPECIFIED                NOCLEAR                         :>.           
  .PWM_CFG_RAM_UNSPECIFIED                NOCLEAR                         :>.           
  .SPI_CFG_RAM_UNSPECIFIED                NOCLEAR                         :>.           
  .CAN_CFG_RAM_UNSPECIFIED                NOCLEAR                         :>.           
  .ADC_CFG_RAM_UNSPECIFIED                NOCLEAR                         :>.           
  .LIN_CFG_RAM_UNSPECIFIED                NOCLEAR                         :>.           
  .MCU_CFG_RAM_UNSPECIFIED                NOCLEAR                         :>.           
  .PORT_CFG_RAM_UNSPECIFIED               NOCLEAR                         :>.           
  .FLSTST_CFG_RAM_UNSPECIFIED             NOCLEAR                         :>.           
  .RAMTST_CFG_RAM_UNSPECIFIED             NOCLEAR                         :>.           
  .FR_59_RENESAS_CFG_RAM_UNSPECIFIED      NOCLEAR                         :>.           
  .FR_59_RENESAS_VAR_POWER_ON_INIT        NOCLEAR                         :>.           
  .FLS_BUFFER_CODE_RAM                    align(4)                        :>.           /* Temporary Buffer  */
  .FLS_USER_BUFFER_CODE_RAM               align(4)                        :>.           /* Application Buffer  */
  .MEM_59_RENESAS_BUFFER_CODE_RAM         align(4)                        :>.           /* Temporary Buffer  */
  .MEM_59_RENESAS_USER_BUFFER_CODE_RAM    align(4)                        :>.           /* Application Buffer  */
  .MCU_CFG_BURAM_UNSPECIFIED                                              :>.           
  
  .ETH_PORT_RAM_0                         align(32)                       :>.           
  .ETH_PORT_RAM_1                         align(32)                       :>.           
  .ETH_PORT_RAM_2                         align(32)                       :>.           
  .top_of_RAM1                            align(4)                        :>cRAM_1_TOP  
  
  /* Start of internal retention RAM area (cRAM_1_R) */
  .rcode                                  align(4)         pad(0x2000)    :>cRAM_1_R    /* definition RRAM of code size */
  .rdata                                  align(4)                        :>.           /* user defined segment for initialized data located in retention RAM */
  .rbss                                   align(4)                        :>.           /* user defined segment for zero initialized data located in retention RAM */
  .rsbss                                  align(4)                        :>.           /* user defined segment for zero initialized data located in retention RAM */
  .rstack                                 align(4)         pad(0x0800)    :>.           /* definition RRAM of stack size */
  .top_of_RAM_R                           align(4)                        :>cRAM_1_R_TOP
  
  /* -----------------------------------------------------------------------------------------*/
  /* Start of internal ROM area (DFLASH)                                                      */
  /* -----------------------------------------------------------------------------------------*/
  CSA_SECTION                             align(4)         0xFF321380     :>CSA_BS      


  /*  Symbols for compiler references */
  ___ghs_romstart       = MEMADDR(iROM_A);
  ___ghs_romend         = MEMENDADDR(iROM_D_TOP);

  ___ghs_ramstart       = MEMADDR(iRAM_0);
  ___ghs_ramend         = MEMENDADDR(iRAM_0_TOP);

  ___ghs_ram1start      = MEMADDR(iRAM_1);
  ___ghs_ram1end        = MEMENDADDR(iRAM_1_TOP);

  ___ghs_ram2start      = MEMADDR(iRAM_2);
  ___ghs_ram2end        = MEMENDADDR(iRAM_2_TOP);

  ___ghs_cram0start     = MEMADDR(cRAM_00);
  ___ghs_cram0end       = MEMENDADDR(cRAM_1_R_TOP);
}

/*===========================================================================*/
/*      End of File                                                          */
/*===========================================================================*/
