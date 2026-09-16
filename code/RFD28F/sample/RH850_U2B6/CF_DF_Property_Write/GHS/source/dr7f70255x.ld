/**********************************************************************************************************************
    Program Name    : Renesas Flash Driver (RFD28F)
    
    File Name       : dr7f70254x_f.ld
    Program Version : V1.00
    File Revision   : $Rev: 1334 $
    File Date       : $Date: 2019-11-26 18:30:27 +0900#$
    Device(s)       : RV28 Flash based RH850 microcontroller
    Description     : Linker Directive file
**********************************************************************************************************************/

/**********************************************************************************************************************
    DISCLAIMER
    This software is supplied by Renesas Electronics Corporation and is only  intended for use with
    Renesas products. No other uses are authorized. This software is owned by Renesas Electronics
    Corporation and is protected under all applicable laws, including copyright laws.
    THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE,
    WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
    TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR
    ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR
    CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
    BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
    Renesas reserves the right, without notice, to make changes to this software and to discontinue the
    availability of this software. By using this software, you agree to the additional terms and conditions
    found by accessing the  following link:
    http://www.renesas.com/disclaimer
    
    Copyright (C) 2018-2023 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/

/**********************************************************************************************************************
 *  Device Information
 *    - R7F70255x (RH850/U2B6)
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Memory Information
 *********************************************************************************************************************/

MEMORY
{
  CFBankA_VECTOR : ORIGIN = 0x00000000, LENGTH = 0x00001000  /* CF BankA VECTOR */
  CFBankA        : ORIGIN = 0x00001000, LENGTH = 0x002FF000  /* CF BankA        */
  CFBankB_VECTOR : ORIGIN = 0x00300000, LENGTH = 0x00001000  /* CF BankB VECTOR */
  CFBankB        : ORIGIN = 0x00301000, LENGTH = 0x002FF000  /* CF BankB        */

  
  DF_AREA0       : ORIGIN = 0xFF200000, LENGTH = 0x00010000  /* DF Area0        */
  DF_AREA1       : ORIGIN = 0xFF210000, LENGTH = 0x00010000  /* DF Area1        */
  DF_AREA2       : ORIGIN = 0xFF220000, LENGTH = 0x00010000  /* DF Area2        */

  RAM_LOCAL_CPU3 : ORIGIN = 0xFD600000, LENGTH = 0x00010000  /* Local RAM CPU3  */
  RAM_LOCAL_CPU2 : ORIGIN = 0xFD800000, LENGTH = 0x00010000  /* Local RAM CPU2  */
  RAM_LOCAL_CPU1 : ORIGIN = 0xFDA00000, LENGTH = 0x00010000  /* Local RAM CPU1  */
  RAM_LOCAL_CPU0 : ORIGIN = 0xFDC00000, LENGTH = 0x00010000  /* Local RAM CPU0  */
  RAM_LOCAL_SELF : ORIGIN = 0xFDE00000, LENGTH = 0x00010000  /* Local RAM SELF  */
  RAM_CLUSTER    : ORIGIN = 0xFE000000, LENGTH = 0x00200000  /* CLUSTER RAM     */
}

/**********************************************************************************************************************
 *   Section Information
 *********************************************************************************************************************/

SECTIONS
{
/**********************************************************************************************************************
 *  Code Flash area (CFBankA)
 *********************************************************************************************************************/
  
  .intvect                                      :>CFBankA_VECTOR /* Start of interrupt vector                        */
  .intvect_end                      align(512)  :>.              /* End of interrupt vector                          */
  
  .rozdata                                      :>CFBankA /* Constant datas in ZDA area                              */
  .robase                           align(4)    :>.       /* Initialize textpointer TP for SDA addressing            */
  .rosdata                          align(4)    :>.       /* Constant datas in SDA area                              */
  .rodata                           align(4)    :>.       /* Constant datas in normal area                           */
  
  .R_RFD_ROSDATA_VERSION_COMMON     align(4)    :>.       /* RFD Version information (For rosdata attribute)         */
  .R_RFD_RODATA_VERSION_COMMON      align(4)    :>.       /* RFD Version information (For rodata attribute)          */
  .R_RFD_ROSDATA_VERSION_CF         align(4)    :>.       /* RFD Version information (For rosdata attribute)         */
  .R_RFD_RODATA_VERSION_CF          align(4)    :>.       /* RFD Version information (For rodata attribute)          */
  .R_RFD_ROSDATA_VERSION_DF         align(4)    :>.       /* RFD Version information (For rosdata attribute)         */
  .R_RFD_RODATA_VERSION_DF          align(4)    :>.       /* RFD Version information (For rodata attribute)          */
  
  .R_RFD_ROSDATA_EXTRA              align(4)    :>.       /* RFD const data for HW Property (For rosdata attribute)  */
  .R_RFD_RODATA_EXTRA               align(4)    :>.       /* RFD const data for HW Property (For rodata attribute)   */
  
  .startup                          align(4)    :>.       /* Section for startup                                     */
  
  .text                             align(4)    :>.       /* Program code area                                       */
  
  .R_RFD_CODE_COMMON                align(4)    :>.       /* RFD Code area for Common Flash Component located in ROM */
  .R_RFD_CODE_COMMON_RAM_NO_BGO     align(4)    :>.       /* RFD Code area for Common Flash Component located in ROM */
  .R_RFD_CODE_USEROWN_COMMON        align(4)    :>.       /* RFD Code area for Common Flash Component located in ROM */
  
  .R_RFD_CODE_DF                    align(4)    :>.       /* RFD Code area for Data Flash Component located in ROM   */
  
  .R_RFD_CODE_CF                    align(4)    :>.       /* RFD Code area for Code Flash Component located in ROM   */
  .R_RFD_CODE_CF_RAM_NO_BGO         align(4)    :>.       /* RFD Code area for Code Flash Component located in ROM   */
  
  .R_RFD_CODE_EXTRA                 align(4)    :>.       /* RFD Code area for Code Flash Component located in ROM   */
  
  .R_RFD_CODE_EX_PROT               align(4)    :>.       /* RFD area for prevent ECC error                          */
  
  .fixaddr                          align(4)    :>.       /* GHS internal (compiler)                                 */
  .fixtype                          align(4)    :>.       /* GHS internal (compiler)                                 */
  .secinfo                          align(4)    :>.       /* GHS internal (runtime library)                          */
  .syscall                          align(4)    :>.       /* GHS internal (linker)                                   */
  
  .romdata  ROM(.data)                          :>.       /* Constant data to initialize variables                   */
  .romzdata ROM(.zdata)                         :>.       /* Constant data to initialize variables in ZDA area       */
  .romsdata ROM(.sdata)                         :>.       /* Constant data to initialize variables in SDA area       */
  .romtdata ROM(.tdata)                         :>.       /* Constant data to initialize variables in TDA area       */
  
/**********************************************************************************************************************
 *  Internal RAM area (RAM_LOCAL_CPU0)
 *********************************************************************************************************************/
  
  .sdabase                          align(4)    :>RAM_LOCAL_CPU0 /* Initialize globalpointer GP for SDA addressing   */
  .sdata                            align(4)    :>.              /* Initialized data in SDA area                     */
  .sbss                             align(4)    :>.              /* Zero initialized data in SDA area                */
  .R_RFD_SBSS                       align(4)    :>.              /* Data without initialization value                */
  .bss                              align(4)    :>.              /* Zero initialized data                            */
  .R_RFD_BSS                        align(4)    :>.              /* Data without initialization value                */
  .data                             align(4)    :>.              /* Initialized data                                 */
  
  .zdata                            align(4)    :>.              /* Initialized data in ZDA area                     */
  .zbss                             align(4)    :>.              /* Zero initialized data in ZDA area                */
  
  .tdata                            align(4)    :>.              /* Initialized data in Tiny data area               */
  
/**********************************************************************************************************************
 *  RFD data in RAM and program code on RAM (RAM_LOCAL_CPU0)
 *********************************************************************************************************************/
  
  .stack                            align(4) pad(0x3000)    :>.  /* Definition of stack size                         */
  
/**********************************************************************************************************************
 *  RAM Start Address & Size
 *********************************************************************************************************************/
  
  __ghs_local_ram_cpu0_start = MEMADDR(RAM_LOCAL_CPU0);
  __ghs_local_ram_cpu0_end   = MEMENDADDR(RAM_LOCAL_CPU0);
  __ghs_local_ram_cpu1_start = MEMADDR(RAM_LOCAL_CPU1);
  __ghs_local_ram_cpu1_end   = MEMENDADDR(RAM_LOCAL_CPU1);
  __ghs_local_ram_cpu2_start = MEMADDR(RAM_LOCAL_CPU2);
  __ghs_local_ram_cpu2_end   = MEMENDADDR(RAM_LOCAL_CPU2);
  __ghs_local_ram_cpu3_start = MEMADDR(RAM_LOCAL_CPU3);
  __ghs_local_ram_cpu3_end   = MEMENDADDR(RAM_LOCAL_CPU3);
  __ghs_cluster_ram_start    = MEMADDR(RAM_CLUSTER);
  __ghs_cluster_ram_end      = MEMENDADDR(RAM_CLUSTER);
  
}

