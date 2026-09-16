/*============================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                         */
/* Module       = App_LIN_Device_Sample.h                                     */
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.        */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains macros/function prototypes/variables required for       */
/* source application file.                                                   */
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
/*              Devices:        X2x                                           */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.0:  30/06/2025  : Remove the SW-VERSION from header of file
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03
 *                       Release
 * 2.3.1:  31/03/2025  : Support core G4KH for U2Bx-E device
 *                       Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02
 *                       Release
 * 2.3.0:  31/01/2025  : Update SW-VERSION for Ver22.00.06 U2C2 Beta release and
 *                       Ver22.01.00(D) U2C4 Final Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : Update SW-VERSION
 * 2.1.1:  25/06/2024  : Initial Version
 */
/******************************************************************************/
#ifndef APP_LIN_DEVICE_SAMPLE_H
#define APP_LIN_DEVICE_SAMPLE_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Lin.h" /* Lin header */

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
/* RLIN3 Registers */
#define RLIN30_BASE         (0xFFC7C000UL)                              /* Lin Registers Base Address */
#define RLIN30_LST          (*((volatile uint8*)(RLIN30_BASE + 0x0012UL)))

/* Port Registers */
#define PORT_BASE           (0xFFD90000UL)                              /* Port Registers Base Address */
#define PKCPROT             (*((volatile uint32 *)0xFFD92F40UL))        /* Port Keycode Register */
#define PWE                 (*((volatile uint32 *)0xFFD92F44UL))        /* Port Write Enable Register */

/* Clock Registers */
#define PLLE                (*((volatile unsigned long *)0xFF980000UL)) /* PLL Enable Register */
#define PLLS                (*((volatile unsigned long *)0xFF980004UL)) /* PLL Status Register */
#define PLLSTPM             (*((volatile unsigned long *)0xFF98000CUL)) /* PLL Stop Mask Register */
#define MOSCE               (*((volatile unsigned long *)0xFF988000UL)) /* MainOSC Enable Register */
#define MOSCS               (*((volatile unsigned long *)0xFF988004UL)) /* MainOSC Status Register */
#define MOSCC               (*((volatile unsigned long *)0xFF988008UL)) /* MainOSC Control Register */
#define MOSCSTPM            (*((volatile unsigned long *)0xFF98800CUL)) /* MainOSC Stop Mask Register */
#define MOSCAS              (*((volatile unsigned long *)0xFF988014UL)) /* MainOSC ADET Status Register */
#define MOSCAGC             (*((volatile unsigned long *)0xFF988018UL)) /* MainOSC Auto Gain Control Register */
#define MOSCAGCS            (*((volatile unsigned long *)0xFF98801CUL)) /* MainOSC Auto Gain Control Status Register */
#define HSOSCS              (*((volatile unsigned long *)0xFF988100UL)) /* HSIntOSC Status Register */
#define HSOSCSTPM           (*((volatile unsigned long *)0xFF988104UL)) /* HSIntOSC Stop Mask Register */
#define HSOSCUT             (*((volatile unsigned long *)0xFF988108UL)) /* HSIntOSC User Trimming Register */
#define CKSC_CPUC           (*((volatile unsigned long *)0xFF980100UL)) /* CLK_CPU Selector Control Register */
#define CKSC_CPUS           (*((volatile unsigned long *)0xFF980108UL)) /* CLK_CPU Selector Status Register */
#define CLKD_PLLC           (*((volatile unsigned long *)0xFF980120UL)) /* CLK_PLLO Divider Control Register */
#define CLKD_PLLS           (*((volatile unsigned long *)0xFF980128UL)) /* CLK_PLLO Divider Status Register */
#define CKSC_WDTC           (*((volatile unsigned long *)0xFF980130UL)) /* CLK_WDT Selector Control Register */
#define CKSC_WDTS           (*((volatile unsigned long *)0xFF980138UL)) /* CLK_WDT Selector Status Register */
#define CKSC_RLINC          (*((volatile unsigned long *)0xFF980140UL)) /* CLK_RLIN Selector Control Register */
#define CKSC_RLINS          (*((volatile unsigned long *)0xFF980148UL)) /* CLK_RLIN Selector Status Register */
#define CKSC_RCANC          (*((volatile unsigned long *)0xFF980150UL)) /* CLK_RCANOSC Selector Control Register */
#define CKSC_RCANS          (*((volatile unsigned long *)0xFF980158UL)) /* CLK_RCANOSC Selector Status Register */
#define CKSC_ADCC           (*((volatile unsigned long *)0xFF980160UL)) /* CLK_ADC Selector Control Register */
#define CKSC_ADCS           (*((volatile unsigned long *)0xFF980168UL)) /* CLK_ADC Selector Status Register */
#define CKSC_MSPIC          (*((volatile unsigned long *)0xFF980170UL)) /* CLK_MSPI Selector Control Register */
#define CKSC_MSPIS          (*((volatile unsigned long *)0xFF980178UL)) /* CLK_MSPI Selector Status Register */
#define CKSC_AWDTC          (*((volatile unsigned long *)0xFF988200UL)) /* CLKA_WDT Selector Control Register */
#define CKSC_AWDTS          (*((volatile unsigned long *)0xFF988208UL)) /* CLKA_WDT Selector Status Register */
#define CKSC_ATAUJC         (*((volatile unsigned long *)0xFF988210UL)) /* CLKA_TAUJ Selector Control Register */
#define CKSC_ATAUJS         (*((volatile unsigned long *)0xFF988218UL)) /* CLKA_TAUJ Selector Status Register */
#define CKSC_ARTCAC         (*((volatile unsigned long *)0xFF988220UL)) /* CLKA_RTCA Selector Control Register */
#define CKSC_ARTCAS         (*((volatile unsigned long *)0xFF988228UL)) /* CLKA_RTCA Selector Status Register */
#define CKSC_AADCC          (*((volatile unsigned long *)0xFF988230UL)) /* CLKA_ADC Selector Control Register */
#define CKSC_AADCS          (*((volatile unsigned long *)0xFF988238UL)) /* CLKA_ADC Selector Status Register */
#define CLKD_AADCC          (*((volatile unsigned long *)0xFF988240UL)) /* CLKA_ADC Divider Control Register */
#define CLKD_AADCS          (*((volatile unsigned long *)0xFF988248UL)) /* CLKA_ADC Divider Status Register */
#define CKSC_FOUT0C         (*((volatile unsigned long *)0xFF988250UL)) /* FOUT0 Clock Selector Control Register */
#define CKSC_FOUT0S         (*((volatile unsigned long *)0xFF988258UL)) /* FOUT0 Clock Selector Status Register */
#define CLKD_FOUT0C         (*((volatile unsigned long *)0xFF988260UL)) /* FOUT0 Clock Divider Control Register */
#define CLKD_FOUT0S         (*((volatile unsigned long *)0xFF988268UL)) /* FOUT0 Clock Divider Status Register */
#define CKSC_FOUT1C         (*((volatile unsigned long *)0xFF988270UL)) /* FOUT1 Clock Selector Control Register */
#define CKSC_FOUT1S         (*((volatile unsigned long *)0xFF988278UL)) /* FOUT1 Clock Selector Status Register */
#define CLKD_FOUT1C         (*((volatile unsigned long *)0xFF988280UL)) /* FOUT1 Clock Divider Control Register */
#define CLKD_FOUT1S         (*((volatile unsigned long *)0xFF988288UL)) /* FOUT1 Clock Divider Status Register */
#define CLKKCPROT1          (*((volatile unsigned long *)0xFF980700UL)) /* Clock Controller Register Key Code Protection Register 1 */
#define CLKKCPROT2          (*((volatile unsigned long *)0xFF980710UL)) /* Clock Controller Register Key Code Protection Register 2 */
#define CLKKCPROT3          (*((volatile unsigned long *)0xFF980720UL)) /* Clock Controller Register Key Code Protection Register 3 */

#define CKS_CLEANC          (*((volatile unsigned long *)0xFF980100UL)) /* CLK_CLEAN Selector Control Register */
#define CKS_CLEANS          (*((volatile unsigned long *)0xFF980108UL)) /* CLK_CLEAN Selector Status Register */
#define CKS_SSCGC           (*((volatile unsigned long *)0xFF980110UL)) /* CLK_SSCG Selector Control Register */
#define CKS_SSCGS           (*((volatile unsigned long *)0xFF980114UL)) /* CLK_SSCG Selector Status Register */
#define CKS_SSCG1C          (*((volatile unsigned long *)0xFF980118UL)) /* CLK_SSCG1 Selector Control Register */
#define CKS_SSCG1S          (*((volatile unsigned long *)0xFF98011CUL)) /* CLK_SSCG1 Selector Status Register */
#define CKS_RLINC           (*((volatile unsigned long *)0xFF980140UL)) /* CLK_CANFD_C/CLK_CANFD_XIN Selector Control Register */
#define CKS_RCANS           (*((volatile unsigned long *)0xFF980158UL)) /* CLK_CANFD_C/CLK_CANFD_XIN Selector Status Register */

#define CKD_PLLC            (*((volatile unsigned long *)0xFF980120UL)) /* CLK_PLLO Divider Control Register */
#define CKD_SSCGC           (*((volatile unsigned long *)0xFF980130UL)) /* CLK_SSCGO Divider Control Register */
#define CKD_SSCG1C          (*((volatile unsigned long *)0xFF980138UL)) /* CLK_SSCG1O Divider Control Register */
#define CKD_PLLS            (*((volatile unsigned long *)0xFF980128UL)) /* CLK_PLLO Divider Status Register */
#define CKD_SSCGS           (*((volatile unsigned long *)0xFF980134UL)) /* CLK_SSCGO Divider Status Register */
#define CKD_SSCG1S          (*((volatile unsigned long *)0xFF98013CUL)) /* CLK_SSCG1O Divider Status Register */
/* EIC Registers */
/* RLIN30 */
#define EIC621              (*((volatile uint16 *)0xFFF804DAUL))
#define EIC622              (*((volatile uint16 *)0xFFF804DCUL))
#define EIC623              (*((volatile uint16 *)0xFFF804DEUL))
/* RLIN31 */
#define EIC626              (*((volatile uint16 *)0xFFF804E4UL))
#define EIC627              (*((volatile uint16 *)0xFFF804E6UL))
#define EIC628              (*((volatile uint16 *)0xFFF804E8UL))
/* RLIN32 */
#define EIC631              (*((volatile uint16 *)0xFFF804EEUL))
#define EIC632              (*((volatile uint16 *)0xFFF804F0UL))
#define EIC633              (*((volatile uint16 *)0xFFF804F2UL))
/* RLIN33 */
#define EIC636              (*((volatile uint16 *)0xFFF804F8UL))
#define EIC637              (*((volatile uint16 *)0xFFF804FAUL))
#define EIC638              (*((volatile uint16 *)0xFFF804FCUL))
/* RLIN34 */
#define EIC641              (*((volatile uint16 *)0xFFF80502UL))
#define EIC642              (*((volatile uint16 *)0xFFF80504UL))
#define EIC643              (*((volatile uint16 *)0xFFF80506UL))
/* RLIN35 */
#define EIC645              (*((volatile uint16 *)0xFFF8050AUL))
#define EIC646              (*((volatile uint16 *)0xFFF8050CUL))
#define EIC647              (*((volatile uint16 *)0xFFF8050EUL))
/* RLIN36 */
#define EIC993              (*((volatile uint16 *)0xFFF807C2UL))
#define EIC994              (*((volatile uint16 *)0xFFF807C4UL))
#define EIC995              (*((volatile uint16 *)0xFFF807C6UL))
/* RLIN37 */
#define EIC997              (*((volatile uint16 *)0xFFF807CAUL))
#define EIC998              (*((volatile uint16 *)0xFFF807CCUL))
#define EIC999              (*((volatile uint16 *)0xFFF807CEUL))
/* RLIN38 */
#define EIC321              (*((volatile uint16 *)0xFFF80282UL))
#define EIC322              (*((volatile uint16 *)0xFFF80284UL))
#define EIC323              (*((volatile uint16 *)0xFFF80286UL))
/* RLIN39 */
#define EIC329              (*((volatile uint16 *)0xFFF80292UL))
#define EIC330              (*((volatile uint16 *)0xFFF80294UL))
#define EIC331              (*((volatile uint16 *)0xFFF80296UL))
/* RLIN310 */
#define EIC333              (*((volatile uint16 *)0xFFF8029AUL))
#define EIC334              (*((volatile uint16 *)0xFFF8029CUL))
#define EIC335              (*((volatile uint16 *)0xFFF8029EUL))
/* RLIN311 */
#define EIC345              (*((volatile uint16 *)0xFFF802B2UL))
#define EIC346              (*((volatile uint16 *)0xFFF802B4UL))
#define EIC347              (*((volatile uint16 *)0xFFF802B6UL))
/* RLIN312 */
#define EIC349              (*((volatile uint16 *)0xFFF802BAUL))
#define EIC350              (*((volatile uint16 *)0xFFF802BCUL))
#define EIC351              (*((volatile uint16 *)0xFFF802BEUL))
/* RLIN313 */
#define EIC388              (*((volatile uint16 *)0xFFF80308UL))
#define EIC389              (*((volatile uint16 *)0xFFF8030AUL))
#define EIC390              (*((volatile uint16 *)0xFFF8030CUL))
/* RLIN314 */
#define EIC392              (*((volatile uint16 *)0xFFF80310UL))
#define EIC393              (*((volatile uint16 *)0xFFF80312UL))
#define EIC394              (*((volatile uint16 *)0xFFF80314UL))
/* RLIN315 */
#define EIC522              (*((volatile uint16 *)0xFFF80414UL))
#define EIC523              (*((volatile uint16 *)0xFFF80416UL))
#define EIC524              (*((volatile uint16 *)0xFFF80418UL))
/* RLIN316 */
#define EIC526              (*((volatile uint16 *)0xFFF8041CUL))
#define EIC527              (*((volatile uint16 *)0xFFF8041EUL))
#define EIC528              (*((volatile uint16 *)0xFFF80420UL))
/* RLIN317 */
#define EIC530              (*((volatile uint16 *)0xFFF80424UL))
#define EIC531              (*((volatile uint16 *)0xFFF80426UL))
#define EIC532              (*((volatile uint16 *)0xFFF80428UL))
/* RLIN318 */
#define EIC546              (*((volatile uint16 *)0xFFF80444UL))
#define EIC547              (*((volatile uint16 *)0xFFF80446UL))
#define EIC548              (*((volatile uint16 *)0xFFF80448UL))
/* RLIN319 */
#define EIC550              (*((volatile uint16 *)0xFFF8044CUL))
#define EIC551              (*((volatile uint16 *)0xFFF8044EUL))
#define EIC552              (*((volatile uint16 *)0xFFF80450UL))
/* RLIN320 */
#define EIC554              (*((volatile uint16 *)0xFFF80454UL))
#define EIC555              (*((volatile uint16 *)0xFFF80456UL))
#define EIC556              (*((volatile uint16 *)0xFFF80458UL))
/* RLIN321 */
#define EIC558              (*((volatile uint16 *)0xFFF8045CUL))
#define EIC559              (*((volatile uint16 *)0xFFF8045EUL))
#define EIC560              (*((volatile uint16 *)0xFFF80460UL))
/* RLIN322 */
#define EIC565              (*((volatile uint16 *)0xFFF8046AUL))
#define EIC566              (*((volatile uint16 *)0xFFF8046CUL))
#define EIC567              (*((volatile uint16 *)0xFFF8046EUL))
/* RLIN323 */
#define EIC649              (*((volatile uint16 *)0xFFF80512UL))
#define EIC650              (*((volatile uint16 *)0xFFF80514UL))
#define EIC651              (*((volatile uint16 *)0xFFF80516UL))
/* RLIN38 */
#define EIC360_ADDR         0xFFF802D0UL
#define EIC360              (*((volatile uint16 *)EIC360_ADDR))
/* TAUD0I0 */
#define EIC10_ADDR          0xFFFC4014UL
#define EIC10               (*((volatile uint16 *)EIC10_ADDR))

/* Interrupt Control Register of 1msec Timer */
#define LIN_ICOSTM0         EIC360
#define LIN_ICTAUD0         EIC10

/* Standby Controller Registers */
#define MSR_RLIN3           (*((volatile uint32 *)0xFF981060UL))
#define MSR_OSTM            (*((volatile uint32 *)0xFF981180UL))
#define MSR_TAUD            (*((volatile uint32 *)0xFF981130UL))
#define MSRKCPROT           (*((volatile uint32 *)0xFF981710UL))

/* RLIN3 Status Register */
#define LIN_RLN30LST        (*((volatile uint8 *)0xFFC7C012UL))
#define LIN_RLN30LEST       (*((volatile uint8 *)0xFFC7C013UL))

/* OS Timer Registers (OSTM0) */
#define LIN_OSTM0CMP        (*((volatile uint32 *)0xFFBF0000UL))
#define LIN_OSTM0CNT        (*((volatile uint32 *)0xFFBF0004UL))
#define LIN_OSTM0TO         (*((volatile uint8 *)0xFFBF0008UL))
#define LIN_OSTM0TOE        (*((volatile uint8 *)0xFFBF000CUL))
#define LIN_OSTM0TE         (*((volatile uint8 *)0xFFBF0010UL))
#define LIN_OSTM0TS         (*((volatile uint8 *)0xFFBF0014UL))
#define LIN_OSTM0TT         (*((volatile uint8 *)0xFFBF0018UL))
#define LIN_OSTM0CTL        (*((volatile uint8 *)0xFFBF0020UL))

/* TAUD Registers (TAUD0) */
#define LIN_TAUD0TT         (*((volatile uint16 *)0xFFBF41C8UL))
#define LIN_TAUD0TPS        (*((volatile uint16 *)0xFFBF4240UL))
#define LIN_TAUD0CDR0       (*((volatile uint16 *)0xFFBF4000UL))
#define LIN_TAUD0CMOR0      (*((volatile uint16 *)0xFFBF4200UL))
#define LIN_TAUD0TS         (*((volatile uint16 *)0xFFBF41C4UL))

/* Setting Values */
#define LIN_ENABLE_INTERRUPT    (uint16)0x0047
#define RLIN3_MSR_ACTIVE        (0x80000000UL)
#define OSTM0_MSR_ACTIVE        (0x800003FEUL)
#define TAUD0_MSR_ACTIVE        (0x80000006UL)
#define DISABLE_WRITE_KEY_CODE  (0xA5A5A500UL)
#define ENABLE_WRITE_KEY_CODE   (0xA5A5A501UL)

/* Option Values */
#define NON_RLININTCNTLREG      STD_ON
#define USE_LIN_OSTM

#define APP_RESF            *((volatile uint32*)0xFF988500UL)

/* SW Reset */
#define APP_MCU_RESF_BIT_POS    0x8

#define APP_MCU_RST_FLAG_VALUE  0x1

/* This macro is used checking reset flag */
#define GET_BIT(REG, BIT) (((REG) >> BIT) & 0x1)

/*Define maximum PE number*/
#if defined(RUN_PE1)
#define PEID_MAX_VALUE              0x00000001
#elif defined(RUN_PE2)
#define PEID_MAX_VALUE              0x00000002
#elif defined(RUN_PE3)
#define PEID_MAX_VALUE              0x00000003
#elif defined(RUN_PE4)
#define PEID_MAX_VALUE              0x00000004
#elif defined(RUN_PE5)
#define PEID_MAX_VALUE              0x00000005
#elif defined(RUN_PE6)
#define PEID_MAX_VALUE              0x00000006
#endif
#define EIBD_BASE_ADDR       ((volatile uint32 *)(0xFFF82000UL))

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* Controller Port(s) Initialization */
extern void Port_Init(void);
/* System Initialization */
extern void Mcu_Init(void);
/* Clock Initialization */
extern void Clock_Init(void);
/* Wathdog Initialization */
extern void Wdg_Init(void);
/* OS Timer Start/Stop */
extern void App_Lin_Start_Timer0(void);
extern void App_Lin_Stop_Timer0(void);
/* Timer ISR */
extern void Timer0_Interrupt(void);

/* MCU Reset */
extern void Mcu_Reset(void);

#if (LIN_MULTI_CORE_SUPPORT == STD_ON) || defined(RUN_OTHER_PE)
extern void Guard_Enable_PE(void);
extern void BoundIntToPEMax(void);
#endif /* #if (LIN_MULTI_CORE_SUPPORT == STD_ON) */
#endif /* APP_LIN_DEVICE_SAMPLE_H */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
