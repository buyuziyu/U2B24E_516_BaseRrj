/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = App_MCU_PostBuildVariant_Sample.h                           */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* Header file information for application.                                   */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Unless otherwise agreed upon in writing between your company and           */
/* Renesas Electronics Corporation the following shall apply!                 */
/*                                                                            */
/* Warranty Disclaimer                                                        */
/*                                                                            */
/* There is no warranty of any kind whatsoever granted by Renesas. Any        */
/* warranty is expressly disclaimed and excluded by Renesas, either expressed */
/* or implied, including but not limited to those for non-infringement of     */
/* intellectual property, merchantability and/or fitness for the particular   */
/* purpose.                                                                   */
/*                                                                            */
/* Renesas shall not have any obligation to maintain, service or provide bug  */
/* fixes for the supplied Product(s) and/or the Application.                  */
/*                                                                            */
/* Each User is solely responsible for determining the appropriateness of     */
/* using the Product(s) and assumes all risks associated with its exercise    */
/* of rights under this Agreement, including, but not limited to the risks    */
/* and costs of program errors, compliance with applicable laws, damage to    */
/* or loss of data, programs or equipment, and unavailability or              */
/* interruption of operations.                                                */
/*                                                                            */
/* Limitation of Liability                                                    */
/*                                                                            */
/* In no event shall Renesas be liable to the User for any incidental,        */
/* consequential, indirect, or punitive damage (including but not limited     */
/* to lost profits) regardless of whether such liability is based on breach   */
/* of contract, tort, strict liability, breach of warranties, failure of      */
/* essential purpose or otherwise and even if advised of the possibility of   */
/* such damages. Renesas shall not be liable for any services or products     */
/* provided by third party vendors, developers or consultants identified or   */
/* referred to the User by Renesas in connection with the Product(s) and/or   */
/* the Application.                                                           */
/*                                                                            */
/*============================================================================*/
/* Environment:                                                               */
/*              Devices:        U2B6-E                                        */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.5.0:  30/06/2025  : Update SW-VERSION to 2.5.0
 * 2.4.0:  31/05/2025  : Update SW-VERSION to 2.4.0
 * 2.3.2:  29/04/2025  : Update SW-VERSION to 2.3.2
 * 2.3.1:  31/03/2025  : Update SW-VERSION to 2.3.1
 * 2.3.0:  28/02/2025  : Update SW-VERSION to 2.3.0
 *                       Add macro MCU_MSR_KCPROT, MCU_SWMRESS_GTM, MCU_MSR_GTM
 * 2.2.0:  31/12/2024  : Update SW-VERSION to 2.2.0
 * 2.1.2:  31/10/2024  : Update SW-VERSION to 2.1.2
 * 2.1.1:  30/08/2024  : Update SW-VERSION to 2.1.1
 *         19/05/2024  : Initial Version
 */
/******************************************************************************/
#ifndef APP_MCU_DEVICE_SAMPLE_H
#define APP_MCU_DEVICE_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Mcu.h"
#include "Mcu_PBTypes.h"

/*******************************************************************************
**                      Version Information                                  **
*******************************************************************************/
/*
 * AUTOSAR specification version information
 */

/*
 * File version information
 */

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define MCU_LRAM_SETTING_0 \
                    McuRamSectorSettingConf_McuRamSectorSettingConf
                    
#define MCU_LRAM_SETTING_1 \
                    McuRamSectorSettingConf_McuRamSectorSettingConf_001
                    
#define MCU_LRAM_SELF_SETTING \
                    McuRamSectorSettingConf_McuRamSectorSettingConf_002
  
#define MCU_CRAM_SETTING \
                    McuRamSectorSettingConf_McuRamSectorSettingConf_003

#define MCU_MCUCLOCKSETTINGCONFIG \
                  McuConf_McuClockSettingConfig_McuClockSettingConfig
                  
#define MCU_MODE_SETTING_0 \
                  McuConf_McuModeSettingConf_McuModeSettingConf
                  
#define MCU_MODE_SETTING_1 \
                  McuConf_McuModeSettingConf_McuModeSettingConf_001
                  
#define MCU_INTC1_SELF_BASE                0xFFFC0000UL

#define MCU_ICR_REG_NUM                   2
#define MCU_ICR_REG_ADDR                  (MCU_INTC1_SELF_BASE + (8 * 2))

#define MCU_ICR_VECTOR_TABLEREF_VALUE     0x0040
#define MCU_ICR_MASK_VALUE                0x0080
#define MCU_ICR_PRIORITY                  0x0007

#define MCU_EIC_REG_VALUE (MCU_ICR_VECTOR_TABLEREF_VALUE | MCU_ICR_MASK_VALUE | MCU_ICR_PRIORITY)

/* PCR01_7 Register Address (0xFF610000 + 0x2000 + 1 * 0x40 + 7 * 4 ) */
#define MCU_PCR_REG_ADDR                  (0xFF61205C)

#define MCU_PCR_PINV_BIT_POSITION        30
#define MCU_PCR_PODC_BIT_POSITION        28
#define MCU_PCR_PODCE_BIT_POSITION       27
#define MCU_PCR_PUCC_BIT_POSITION        25
#define MCU_PCR_PDSC_BIT_POSITION        24
#define MCU_PCR_PISA_BIT_POSITION        21
#define MCU_PCR_PIS_BIT_POSITION         20
#define MCU_PCR_PU_BIT_POSITION          19
#define MCU_PCR_PD_BIT_POSITION          18
#define MCU_PCR_PBDC_BIT_POSITION        17
#define MCU_PCR_PIBC_BIT_POSITION        16
#define MCU_PCR_PSFSOE_BIT_POSITION      15
#define MCU_PCR_PSFSD_BIT_POSITION       14
#define MCU_PCR_PSFSC_BIT_POSITION       13
#define MCU_PCR_P_BIT_POSITION           12
#define MCU_PCR_PPR_BIT_POSITION          8
#define MCU_PCR_PMC_BIT_POSITION          6
#define MCU_PCR_PIPC_BIT_POSITION         5
#define MCU_PCR_PM_BIT_POSITION           4
#define MCU_PCR_PFCEAE_BIT_POSITION       3
#define MCU_PCR_PFCAE_BIT_POSITION        2
#define MCU_PCR_PFCE_BIT_POSITION         1
#define MCU_PCR_PFC_BIT_POSITION          0

#define MCU_PCR_ALT6_OUT_PMC              1
#define MCU_PCR_ALT6_OUT_PIPC             0
#define MCU_PCR_ALT6_OUT_PM               0
#define MCU_PCR_ALT6_OUT_PFCEAE           0
#define MCU_PCR_ALT6_OUT_PFCAE            1
#define MCU_PCR_ALT6_OUT_PFCE             0
#define MCU_PCR_ALT6_OUT_PFC              1

#define MCU_PCR_ALTERNATE_VALUE_MASK \
          ( (1 << MCU_PCR_PMC_BIT_POSITION) | \
            (1 << MCU_PCR_PIPC_BIT_POSITION) | \
            (1 << MCU_PCR_PM_BIT_POSITION) | \
            (1 << MCU_PCR_PFCEAE_BIT_POSITION) | \
            (1 << MCU_PCR_PFCAE_BIT_POSITION) | \
            (1 << MCU_PCR_PFCE_BIT_POSITION) | \
            (1 << MCU_PCR_PFC_BIT_POSITION) )

#define MCU_PCR_ALTERNATE_VALUE_6_OUT \
          ( (MCU_PCR_ALT6_OUT_PMC    << MCU_PCR_PMC_BIT_POSITION) | \
            (MCU_PCR_ALT6_OUT_PIPC   << MCU_PCR_PIPC_BIT_POSITION) | \
            (MCU_PCR_ALT6_OUT_PM     << MCU_PCR_PM_BIT_POSITION) | \
            (MCU_PCR_ALT6_OUT_PFCEAE << MCU_PCR_PFCEAE_BIT_POSITION) | \
            (MCU_PCR_ALT6_OUT_PFCAE  << MCU_PCR_PFCAE_BIT_POSITION) | \
            (MCU_PCR_ALT6_OUT_PFCE   << MCU_PCR_PFCE_BIT_POSITION) | \
            (MCU_PCR_ALT6_OUT_PFC    << MCU_PCR_PFC_BIT_POSITION) )

#define MCU_PKCPROT                  *((volatile uint32 *)0xffd92f40UL)
#define MCU_PWE                      *((volatile uint32 *)0xffd92f44UL)

#define MCU_PORT_DISABLE_WRITE_ACCESS_VALUE 0xA5A5A500UL
#define MCU_PORT_ENABLE_WRITE_ACCESS_VALUE  0xA5A5A501UL
#define MCU_PWE_ENABLE_WRITE_ACCESS_VALUE   0x003B7FFFUL

#define MCU_ECMKCPROT                *((volatile uint32 *)0xffccd4b4ul)

#define MCU_ECM_DISABLE_WRITE_ACCESS_VALUE 0xA5A5A500UL
#define MCU_ECM_ENABLE_WRITE_ACCESS_VALUE  0xA5A5A501UL

#define MCU_ECMPE0                   *((volatile uint32 *)0xffccd4b8ul)
#define MCU_ECMPE0_ADDRESS                                0xffccd4b8ul

#define MCU_ECM_ECMESSTCn_ADDRESS                         0xffccd478ul

#define MCU_ECMPEM                   *((volatile uint32 *)0xffccd740ul)

/* Reset reason Register Address*/
#define MCU_RESF                     *((volatile uint32 *)0xff988500UL)
#define MCU_POWER_ON_RESET_VALUE     0x00000001UL
#define MCU_EXTERNAL_RESET_VALUE     0x00000004UL

/* Standby Controller - STBC */
#define MCU_MSRKCPROT                0xFF981710UL
#define MCU_MSR_TAUJ_AWO             0xFF988E20UL

/* TAUJ2 */
#define MCU_TAUJ2TPS                 0xffe80090UL
#define MCU_TAUJ2CMOR0               0xffe80080UL
#define MCU_TAUJ2TS                  0xffe80054UL
#define MCU_TAUJ2CDR0                0xffe80000UL
#define MCU_TAUJ2TOE                 0xffe80060UL

/* Interrupt */
#define MCU_INTC2_BASE               0xFFF80000UL
#define INTC2_ADDR_EIC(isr_num)      (MCU_INTC2_BASE + 0x0000 + 0x2 * isr_num)

/* Wake up Register Address */
#define MCU_WUFMON                   *((volatile uint32 *)0xFF98E1A0UL)
#define MCU_WUF0_A0                  *((volatile uint32 *)0xFF98E000UL)
#define MCU_WUF0_A1                  *((volatile uint32 *)0xFF98E010UL)
#define MCU_WUF0_A2                  *((volatile uint32 *)0xFF98E020UL)
#define MCU_WUF1_A0                  *((volatile uint32 *)0xFF98E120UL)
#define MCU_WUF1_A1                  *((volatile uint32 *)0xFF98E130UL)
#define MCU_WUF1_A2                  *((volatile uint32 *)0xFF98E140UL)
#define MCU_WUF0_I0                  *((volatile uint32 *)0xFF98E200UL)
#define MCU_WUF0_I1                  *((volatile uint32 *)0xFF98E210UL)
#define MCU_WUF0_I2                  *((volatile uint32 *)0xFF98E220UL)
#define MCU_WUF0_I3                  *((volatile uint32 *)0xFF98E230UL)
#define MCU_WUF1_I0                  *((volatile uint32 *)0xFF98E320UL)
#define MCU_WUF1_I1                  *((volatile uint32 *)0xFF98E330UL)
#define MCU_WUF1_I2                  *((volatile uint32 *)0xFF98E340UL)
#define MCU_WUF1_I3                  *((volatile uint32 *)0xFF98E350UL)

/* I/O Buffer Hold Control Register Address */
#define MCU_IOHOLD0                  *((volatile uint32 *)0xFF988D00UL)
#define MCU_IOHOLD1                  *((volatile uint32 *)0xFF988D04UL)

/* Function set value to register Address */
#define READ_REG(ADDR, BIT_NUM)          *((volatile uint ## BIT_NUM *)ADDR)
#define WRITE_REG(ADDR, BIT_NUM, VAL)    *((volatile uint ## BIT_NUM *)ADDR) = VAL

#define MCU_P32                      *((volatile uint16 *)0xffd90800UL)
#define MCU_PMC32                    *((volatile uint16 *)0xffd90814UL)
#define MCU_PM32                     *((volatile uint16 *)0xffd90810UL)
#define MCU_PIPC32                   *((volatile uint16 *)0xffd94808UL)
#define MCU_PBDC32                   *((volatile uint16 *)0xffd94804UL)
#define MCU_PFCEAE32                 *((volatile uint16 *)0xffd9082cUL)
#define MCU_PFCAE32                  *((volatile uint16 *)0xffd90828UL)
#define MCU_PFCE32                   *((volatile uint16 *)0xffd9081cUL)
#define MCU_PFC32                    *((volatile uint16 *)0xffd90818UL)
#define MCU_PNOT32                   *((volatile uint16 *)0xffd90808UL)

#define MCU_P33                      *((volatile uint16 *)0xffd90840UL)
#define MCU_PMC33                    *((volatile uint16 *)0xffd90854UL)
#define MCU_PM33                     *((volatile uint16 *)0xffd90850UL)
#define MCU_PIPC33                   *((volatile uint16 *)0xffd94848UL)
#define MCU_PBDC33                   *((volatile uint16 *)0xffd94844UL)
#define MCU_PFCEAE33                 *((volatile uint16 *)0xffd9086cUL)
#define MCU_PFCAE33                  *((volatile uint16 *)0xffd90868UL)
#define MCU_PFCE33                   *((volatile uint16 *)0xffd9085cUL)
#define MCU_PFC33                    *((volatile uint16 *)0xffd90858UL)

#define MCU_P11                      *((volatile uint16 *)0xffd902c0UL)
#define MCU_PMC11                    *((volatile uint16 *)0xffd902d4UL)
#define MCU_PM11                     *((volatile uint16 *)0xffd902d0UL)
#define MCU_PIPC11                   *((volatile uint16 *)0xffd942c8UL)
#define MCU_PBDC11                   *((volatile uint16 *)0xffd942c4UL)

/* IRQxx/FCLACTLx_IRQ_x for Wakeup */
#define MCU_FCLACTL0_IRQ_1           *((volatile uint16 *)0xffed4b00UL)
#define MCU_FCLACTL4_IRQ_2           *((volatile uint16 *)0xffed4c10UL)

/* PE Guard Register */
#define PBGERRSLV20                0xFFDE1000
#define PBGERRSLV50                0xffc7b000  
#define PBGERRSLV00                0xffc6b000                     
#define PBGKCPROT(BusGroup)                     (*(volatile uint32*)(PBGERRSLV##BusGroup + 0x18))
#define PBG20                              0xFFDE0B00
#define PBG21                              0xffde0c00
#define PBG22                              0xffde0d00
#define PBG50                              0xffc7a300
#define PBG00                              0xffc6b080
#define PBG01                              0xffc6b100
#define PBGCKPROT0(BusGroup,BusChannel)         (*(volatile uint32*)(PBG##BusGroup + BusChannel*0x08))
#define PBGCKPROT1(BusGroup,BusChannel)         (*(volatile uint32*)(PBG##BusGroup + 0x04 + BusChannel*0x08))

#define CLKKCPROT1        (*((volatile unsigned long *)0xFF980700UL)) /* Clock Controller Register Key Code Protection Register 1 */

#define MCU_MSR_KCPROT               *((volatile uint32 *)0xff981710UL)
#define MCU_SWMRESS_GTM              *((volatile uint32 *)0xff980924UL)
#define MCU_MSR_GTM                  *((volatile uint32 *)0xff981020UL)
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
void Port_Init(void);
void Wdg_Init(void);
void Reg_Init(void);
void External_Interrupt_Enable(void);

void Mcu_EcmNotification(uint16 EcmErrorNum);

#endif /* APP_MCU_DEVICE_SAMPLE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
