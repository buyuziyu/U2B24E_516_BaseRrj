/*============================================================================*/
/* Project      = RH850/X2x MCAL PF Development                               */
/* Module       = Interrupt_VectorTable_PE0.c                                 */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.             */
/*============================================================================*/
/* Purpose:                                                                   */
/* This file contains interrupt vector table                                  */
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
/*              Devices:        U2Bx-E                                        */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 * 2.4.1:  30/06/2025  : Update ISR for ETH
 *                     : Update GTM ISR for PWM
 * 2.3.2:  29/04/2025  : Update GTM ISR for PWM
 *         31/03/2025  : Update ISR for ETH
 *                     : Remove PWM TAUJ3 interrupt
 * 2.3.0:  31/01/2025  : As part of support GTM timer HWIP
 *                       + Add ICU interrupt for GTM TIM
 *                       + Add PWM interrupt for GTM TOM/ATOM
 *                       As part of HWM 0.5 support
 *                       + Add ISR for FLXA
 *                       + Add ISR for ETH
 * 2.2.0:  31/12/2024  : Update SW version
 *                       for Ver22.02.00/Ver22.02.00.D Final Release
 * 2.1.1:  31/07/2024  : Remove defines ATU for PWM
 *         21/06/2024  : Update ISR for CANXL
 *         15/05/2024  : Update interrupt for CAN module
 *                       Update interrupt for GPT module
 * 1.0.0:  02/04/2024  : Initial Version
 */
/******************************************************************************/
// #define ADC_MODULE_SAMPLE
// #define PWM_MODULE_SAMPLE
// #define ETH_MODULE_SAMPLE
// #define FR_MODULE_SAMPLE
#define GPT_MODULE_SAMPLE
// #define ICU_MODULE_SAMPLE
// #define MCU_MODULE_SAMPLE
// #define SPI_MODULE_SAMPLE
// #define WDG_MODULE_SAMPLE
// #define CAN_MODULE_SAMPLE
// #define LIN_MODULE_SAMPLE
// #define FLS_MODULE_SAMPLE
// #define GLOBAL_MODULE_SAMPLE
/*****************************************************************************/
/*                Module Specific header file inclusions                     */
/*****************************************************************************/
#ifdef ADC_MODULE_SAMPLE
#include "Adc.h"
#include "Adc_Irq.h"
#include "App_ADC_Device_Sample.h"
#endif

#ifdef PWM_MODULE_SAMPLE
#include "Pwm.h"
#include "App_PWM_Device_Sample.h"
#if (PWM_TAUD_UNIT_USED == STD_ON)
#include "Pwm_TAUD_Irq.h"
#endif
#if (PWM_TAUJ_UNIT_USED == STD_ON)
#include "Pwm_TAUJ_Irq.h"
#endif
#if (PWM_GTM_UNIT_USED == STD_ON)
#include "Pwm_GTM_Irq.h"
#endif
#endif  /* PWM_MODULE_SAMPLE */

#ifdef ETH_MODULE_SAMPLE
#include "Eth.h"
#if (ETH_MACRO_ETNF == STD_ON) 
#include "Eth_ETNF_Irq.h"
#endif
#if (ETH_MACRO_ETNE == STD_ON) 
#include "Eth_ETNE_Irq.h"
#endif
#endif /* ETH_MODULE_SAMPLE */

#ifdef FR_MODULE_SAMPLE
#include "App_Fr_Device_Sample.h"
#endif  /* FR_MODULE_SAMPLE */

#ifdef GPT_MODULE_SAMPLE
#include "Gpt.h"
#if(GPT_TIMER_IP_OSTM == STD_ON)
#include "Gpt_OSTM_Irq.h"
#endif
#if(GPT_TIMER_IP_TAUD == STD_ON)
#include "Gpt_TAUD_Irq.h"
#endif
#if(GPT_TIMER_IP_TAUJ == STD_ON)
#include "Gpt_TAUJ_Irq.h"
#endif
#if(GPT_TIMER_IP_GTM == STD_ON)
#include "Gpt_GTM_Irq.h"
#endif
#endif  /* GPT_MODULE_SAMPLE */

#ifdef OCU_MODULE_SAMPLE
#include "Ocu.h"
#if(OCU_TIMER_IP_TAUD == STD_ON)
#include "Ocu_TAUD_Irq.h"
#endif
#if(OCU_TIMER_IP_TAUJ == STD_ON)
#include "Ocu_TAUJ_Irq.h"
#endif
#if (STD_ON == OCU_TIMER_IP_GTM)
#include "Ocu_GTM_Irq.h"
#endif
#endif  /* OCU_MODULE_SAMPLE */

#ifdef ICU_MODULE_SAMPLE
#include "Icu.h"

#if(ICU_TAUJ_UNIT_USED == STD_ON)
#include "Icu_TAUJ_Irq.h"
#endif

#if(ICU_TAUD_UNIT_USED == STD_ON)
#include "Icu_TAUD_Irq.h"
#endif
#include "Icu_PIN_Irq.h"

#if(ICU_GTM_TIMER_UNIT_USED == STD_ON)
#include "Icu_GTM_Irq.h"
#endif
#endif /* ICU_MODULE_SAMPLE */

#ifdef MCU_MODULE_SAMPLE
#include "Mcu.h"
#include "Mcu_ECM_Irq.h"
#endif  /* MCU_MODULE_SAMPLE */

#ifdef SPI_MODULE_SAMPLE
#if defined (SPI_USE_MULTICORE)
#include "App_Spi_Common_Sample_0.h"
#else
#include "App_Spi_Common_Sample.h"
#endif
#include "Spi.h"
#include "Spi_MSPI_Irq.h"
#include "Spi_sDMAC_Irq.h"
#include "Os.h"
#endif /* SPI_MODULE_SAMPLE */

#ifdef WDG_MODULE_SAMPLE
#include "App_WDG_Common_Sample.h"
#include "Wdg.h"
#include "Wdg_WDTB_Irq.h"
#include "Wdg_Ram.h"
#include "Os.h"
#endif /* WDG_MODULE_SAMPLE */

#ifdef CAN_MODULE_SAMPLE
#include "Can.h"
#include "App_Can_Common_Sample.h"
#include "App_Can_Common_Sample_0.h"
#include "Can_Irq.h"
#endif /* CAN_MODULE_SAMPLE */

#ifdef LIN_MODULE_SAMPLE
#include "Lin.h"
#include "Lin_RLIN3_Irq.h"
#include "App_LIN_Device_Sample.h"
#endif  /* LIN_MODULE_SAMPLE */

#ifdef FLS_MODULE_SAMPLE
#include "Fls.h"
#include "Fls_Irq.h"
#endif  /* FLS_MODULE_SAMPLE */

#ifdef REENTRANCE_TESTING
#include "MCU_IT_Test_Common.h"
#endif

#ifdef USE_LIB_MCU_STRESSTEST
#include "Lib_Mcu_StressTest.h"
#endif

#ifdef MCU_TEST_OUTPUT
#include "MCU_IT_Test_Specific.h"
#endif
/*****************************************************************************/
/*                         ISR Definition                                    */
/*****************************************************************************/
#pragma ghs interrupt
static __interrupt void Dummy(void)
{
  while(1);
}


void FEINT_PE0(void)
{
#if defined (WDG_MODULE_SAMPLE)
#if (WDG_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT1 interrupt mapping */
#else
#if (WDG_ERR_FE_LEVEL_INTERRUPT_MODE == STD_ON)
   WDG_ERROR_ISR();
#endif
#endif

#elif defined(MCU_MODULE_SAMPLE)
#if ((MCU_FEINT_ISR_API == STD_ON) && (MCU_ECM_OPERATION == STD_ON))
  /* FEINT */
  MCU_FEINT_ISR();
#endif
#else
  Dummy();
#endif
}

#ifdef MCU_MODULE_SAMPLE
#if (MCU_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#if ((MCU_EIINT_EIC8_ISR_API == STD_ON) && (MCU_ECM_OPERATION == STD_ON))
    #if defined MCU_ISR_CONSISTENCY
        #if defined MCU_FE_ISR_CONSISTENCY
            #define INT_VECTOR_PE0_008              MCU_FEINT_ISR
        #else
            #define INT_VECTOR_PE0_008              MCU_ECM_EIC9_ISR
        #endif
    #else
        #define INT_VECTOR_PE0_008              MCU_ECM_EIC8_ISR
    #endif
#endif

#if ((MCU_EIINT_EIC9_ISR_API == STD_ON) && (MCU_ECM_OPERATION == STD_ON))
#ifdef MCU_ISR_CONSISTENCY
#define INT_VECTOR_PE0_009 MCU_ECM_EIC8_ISR /* 009 */
#else
#define INT_VECTOR_PE0_009 MCU_ECM_EIC9_ISR /* 009 */
#endif
#endif
#endif

// Define for test case re-entrant
#ifdef REENTRANCE_TESTING
#define INT_VECTOR_PE0_199 OSTM_Reentrance_Test_Isr
#endif
// Define for test case timming
#ifdef MCU_TEST_OUTPUT
#define INT_VECTOR_PE0_372 MCU_TEST_READ_TICK
#endif


#ifdef USE_LIB_MCU_STRESSTEST
#define INT_VECTOR_PE0_199 Lib_Mcu_StressTest_Isr /* 199 */
#endif

#endif  /* MCU_MODULE_SAMPLE */

#ifdef WDG_MODULE_SAMPLE
#if (WDG_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT1 interrupt mapping */
#else
#if ((WDG_WDTBA_CONFIGURED == STD_ON) && (WDG_WDTBA_CORE_CONFIGURED == 0x00))
#define INT_VECTOR_PE0_981 WDG_TRIGGERFUNCTION_ISR /* 981 */
#else
#define INT_VECTOR_PE0_022 WDG_TRIGGERFUNCTION_ISR /* 022 */
#endif
#endif
#endif  /* End of WDG_MODULE_SAMPLE */

#ifdef FLS_MODULE_SAMPLE
#if (FLS_INTERRUPT_MODE == STD_ON)
#define INT_VECTOR_PE0_035 FLS_FLENDNM0_ISR /* 035 */

#endif /* FLS_INTERRUPT_MODE == STD_ON */
#endif  /* FLS_MODULE_SAMPLE */

#ifdef LIN_MODULE_SAMPLE
#if (LIN_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#ifdef USE_LIN_OSTM
#define INT_VECTOR_PE0_360 Timer0_Interrupt /* 199 */
#else
#define INT_VECTOR_PE0_010 Timer0_Interrupt /* 010 */
#endif
#if (LIN_CHANNEL0_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_621 LIN_CHANNEL0_TX_ISR  /* 621 */
#define INT_VECTOR_PE0_622 LIN_CHANNEL0_RX_ISR  /* 622 */
#define INT_VECTOR_PE0_623 LIN_CHANNEL0_ERR_ISR /* 623 */
#endif
#if (LIN_CHANNEL1_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_626 LIN_CHANNEL1_TX_ISR  /* 626 */
#define INT_VECTOR_PE0_627 LIN_CHANNEL1_RX_ISR  /* 627 */
#define INT_VECTOR_PE0_628 LIN_CHANNEL1_ERR_ISR /* 628 */
#endif
#if (LIN_CHANNEL2_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_631 LIN_CHANNEL2_TX_ISR  /* 631 */
#define INT_VECTOR_PE0_632 LIN_CHANNEL2_RX_ISR  /* 632 */
#define INT_VECTOR_PE0_633 LIN_CHANNEL2_ERR_ISR /* 633 */
#endif
#if (LIN_CHANNEL3_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_636 LIN_CHANNEL3_TX_ISR  /* 429 */
#define INT_VECTOR_PE0_637 LIN_CHANNEL3_RX_ISR  /* 430 */
#define INT_VECTOR_PE0_638 LIN_CHANNEL3_ERR_ISR /* 431 */
#endif
#if (LIN_CHANNEL4_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_641 LIN_CHANNEL4_TX_ISR  /* 433 */
#define INT_VECTOR_PE0_642 LIN_CHANNEL4_RX_ISR  /* 434 */
#define INT_VECTOR_PE0_643 LIN_CHANNEL4_ERR_ISR /* 435 */
#endif
#if (LIN_CHANNEL5_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_645 LIN_CHANNEL5_TX_ISR  /* 437 */
#define INT_VECTOR_PE0_646 LIN_CHANNEL5_RX_ISR  /* 438 */
#define INT_VECTOR_PE0_647 LIN_CHANNEL5_ERR_ISR /* 439 */
#endif
#if (LIN_CHANNEL6_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_993 LIN_CHANNEL6_TX_ISR  /* 441 */
#define INT_VECTOR_PE0_994 LIN_CHANNEL6_RX_ISR  /* 442 */
#define INT_VECTOR_PE0_995 LIN_CHANNEL6_ERR_ISR /* 443 */
#endif
#if (LIN_CHANNEL7_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_997 LIN_CHANNEL7_TX_ISR  /* 997 */
#define INT_VECTOR_PE0_998 LIN_CHANNEL7_RX_ISR  /* 998 */
#define INT_VECTOR_PE0_999 LIN_CHANNEL7_ERR_ISR /* 999 */
#endif
#if (LIN_CHANNEL8_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_530 LIN_CHANNEL8_TX_ISR  /* 530 */
#define INT_VECTOR_PE0_531 LIN_CHANNEL8_RX_ISR  /* 531 */
#define INT_VECTOR_PE0_532 LIN_CHANNEL8_ERR_ISR /* 532 */
#endif
#if (LIN_CHANNEL9_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_546 LIN_CHANNEL9_TX_ISR  /* 546 */
#define INT_VECTOR_PE0_547 LIN_CHANNEL9_RX_ISR  /* 547 */
#define INT_VECTOR_PE0_548 LIN_CHANNEL9_ERR_ISR /* 548 */
#endif
#if (LIN_CHANNEL10_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_550 LIN_CHANNEL10_TX_ISR  /* 550 */
#define INT_VECTOR_PE0_551 LIN_CHANNEL10_RX_ISR  /* 551 */
#define INT_VECTOR_PE0_552 LIN_CHANNEL10_ERR_ISR /* 552 */
#endif
#if (LIN_CHANNEL11_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_554 LIN_CHANNEL11_TX_ISR  /* 554 */
#define INT_VECTOR_PE0_555 LIN_CHANNEL11_RX_ISR  /* 555 */
#define INT_VECTOR_PE0_556 LIN_CHANNEL11_ERR_ISR /* 556 */
#endif
#if (LIN_CHANNEL12_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_558 LIN_CHANNEL12_TX_ISR  /* 558  */
#define INT_VECTOR_PE0_559 LIN_CHANNEL12_RX_ISR  /* 559  */
#define INT_VECTOR_PE0_560 LIN_CHANNEL12_ERR_ISR /* 560  */
#endif
#if (LIN_CHANNEL13_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_565 LIN_CHANNEL13_TX_ISR  /* 565 */
#define INT_VECTOR_PE0_566 LIN_CHANNEL13_RX_ISR  /* 566 */
#define INT_VECTOR_PE0_567 LIN_CHANNEL13_ERR_ISR /* 567 */
#endif
#if (LIN_CHANNEL14_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_569 LIN_CHANNEL14_TX_ISR  /* 569 */
#define INT_VECTOR_PE0_570 LIN_CHANNEL14_RX_ISR  /* 570 */
#define INT_VECTOR_PE0_571 LIN_CHANNEL14_ERR_ISR /* 571 */
#endif
#if (LIN_CHANNEL15_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_573 LIN_CHANNEL15_TX_ISR  /* 573 */
#define INT_VECTOR_PE0_574 LIN_CHANNEL15_RX_ISR  /* 574 */
#define INT_VECTOR_PE0_575 LIN_CHANNEL15_ERR_ISR /* 575 */
#endif
#if (LIN_CHANNEL16_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_734 LIN_CHANNEL16_TX_ISR  /* 734 */
#define INT_VECTOR_PE0_735 LIN_CHANNEL16_RX_ISR  /* 735 */
#define INT_VECTOR_PE0_736 LIN_CHANNEL16_ERR_ISR /* 736 */
#endif
#if (LIN_CHANNEL17_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_738 LIN_CHANNEL17_TX_ISR  /* 738 */
#define INT_VECTOR_PE0_739 LIN_CHANNEL17_RX_ISR  /* 739 */
#define INT_VECTOR_PE0_740 LIN_CHANNEL17_ERR_ISR /* 740 */
#endif
#if (LIN_CHANNEL18_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_766 LIN_CHANNEL18_TX_ISR  /* 766 */
#define INT_VECTOR_PE0_767 LIN_CHANNEL18_RX_ISR  /* 767 */
#define INT_VECTOR_PE0_768 LIN_CHANNEL18_ERR_ISR /* 768 */
#endif
#if (LIN_CHANNEL19_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_770 LIN_CHANNEL19_TX_ISR  /* 770 */
#define INT_VECTOR_PE0_771 LIN_CHANNEL19_RX_ISR  /* 771 */
#define INT_VECTOR_PE0_772 LIN_CHANNEL19_ERR_ISR /* 772 */
#endif
#if (LIN_CHANNEL20_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_774 LIN_CHANNEL20_TX_ISR  /* 774 */
#define INT_VECTOR_PE0_775 LIN_CHANNEL20_RX_ISR  /* 775 */
#define INT_VECTOR_PE0_776 LIN_CHANNEL20_ERR_ISR /* 776 */
#endif
#if (LIN_CHANNEL21_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_778 LIN_CHANNEL21_TX_ISR  /* 778 */
#define INT_VECTOR_PE0_779 LIN_CHANNEL21_RX_ISR  /* 779 */
#define INT_VECTOR_PE0_780 LIN_CHANNEL21_ERR_ISR /* 780 */
#endif
#if (LIN_CHANNEL22_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_782 LIN_CHANNEL22_TX_ISR  /* 782 */
#define INT_VECTOR_PE0_783 LIN_CHANNEL22_RX_ISR  /* 783 */
#define INT_VECTOR_PE0_784 LIN_CHANNEL22_ERR_ISR /* 784 */
#endif
#if (LIN_CHANNEL23_CONFIGURED == STD_ON)
#define INT_VECTOR_PE0_649 LIN_CHANNEL23_TX_ISR  /* 649 */
#define INT_VECTOR_PE0_650 LIN_CHANNEL23_RX_ISR  /* 650 */
#define INT_VECTOR_PE0_651 LIN_CHANNEL23_ERR_ISR /* 651 */
#endif
#endif /* #if (LIn_ISR_CATEGORY_2 == STD_ON) */
#endif  /* LIN_MODULE_SAMPLE */

#ifdef SPI_MODULE_SAMPLE
// #define INT_VECTOR_PE0_010 Timer_Task           /* 010 */
#if (SPI_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
/* Defines the CAT1 interrupt mapping */
#if (SPI_DMA0_00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_070 SPI_DMA0_00_ISR      /* 070 */
#endif
#if (SPI_DMA0_01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_071 SPI_DMA0_01_ISR      /* 071 */
#endif
#if (SPI_DMA0_02_ISR_API == STD_ON)
#define INT_VECTOR_PE0_072 SPI_DMA0_02_ISR      /* 072 */
#endif
#if (SPI_DMA0_03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_073 SPI_DMA0_03_ISR      /* 073 */
#endif
#if (SPI_DMA0_04_ISR_API == STD_ON)
#define INT_VECTOR_PE0_074 SPI_DMA0_04_ISR      /* 074 */
#endif
#if (SPI_DMA0_05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_075 SPI_DMA0_05_ISR      /* 075 */
#endif
#if (SPI_DMA0_06_ISR_API == STD_ON)
#define INT_VECTOR_PE0_076 SPI_DMA0_06_ISR      /* 076 */
#endif
#if (SPI_DMA0_07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_077 SPI_DMA0_07_ISR      /* 077 */
#endif
#if (SPI_DMA0_08_ISR_API == STD_ON)
#define INT_VECTOR_PE0_078 SPI_DMA0_08_ISR      /* 078 */
#endif
#if (SPI_DMA0_09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_079 SPI_DMA0_09_ISR      /* 079 */
#endif
#if (SPI_DMA0_10_ISR_API == STD_ON)
#define INT_VECTOR_PE0_080 SPI_DMA0_10_ISR      /* 080 */
#endif
#if (SPI_DMA0_11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_081 SPI_DMA0_11_ISR      /* 081 */
#endif
#if (SPI_DMA0_12_ISR_API == STD_ON)
#define INT_VECTOR_PE0_082 SPI_DMA0_12_ISR      /* 082 */
#endif
#if (SPI_DMA0_13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_083 SPI_DMA0_13_ISR      /* 083 */
#endif
#if (SPI_DMA0_14_ISR_API == STD_ON)
#define INT_VECTOR_PE0_084 SPI_DMA0_14_ISR      /* 084 */
#endif
#if (SPI_DMA0_15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_085 SPI_DMA0_15_ISR      /* 085 */
#endif
#if (SPI_DMA1_00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_825 SPI_DMA1_00_ISR      /* 825 */
#endif
#if (SPI_DMA1_01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_826 SPI_DMA1_01_ISR      /* 826 */
#endif
#if (SPI_DMA1_02_ISR_API == STD_ON)
#define INT_VECTOR_PE0_827 SPI_DMA1_02_ISR      /* 827 */
#endif
#if (SPI_DMA1_03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_828 SPI_DMA1_03_ISR      /* 828 */
#endif
#if (SPI_DMA1_04_ISR_API == STD_ON)
#define INT_VECTOR_PE0_829 SPI_DMA1_04_ISR      /* 829 */
#endif
#if (SPI_DMA1_05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_830 SPI_DMA1_05_ISR      /* 830 */
#endif
#if (SPI_DMA1_06_ISR_API == STD_ON)
#define INT_VECTOR_PE0_831 SPI_DMA1_06_ISR      /* 831 */
#endif
#if (SPI_DMA1_07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_832 SPI_DMA1_07_ISR      /* 832 */
#endif
#if (SPI_DMA1_08_ISR_API == STD_ON)
#define INT_VECTOR_PE0_833 SPI_DMA1_08_ISR      /* 833 */
#endif
#if (SPI_DMA1_09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_834 SPI_DMA1_09_ISR      /* 834 */
#endif
#if (SPI_DMA1_10_ISR_API == STD_ON)
#define INT_VECTOR_PE0_835 SPI_DMA1_10_ISR      /* 835 */
#endif
#if (SPI_DMA1_11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_836 SPI_DMA1_11_ISR      /* 836 */
#endif
#if (SPI_DMA1_12_ISR_API == STD_ON)
#define INT_VECTOR_PE0_837 SPI_DMA1_12_ISR      /* 837 */
#endif
#if (SPI_DMA1_13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_838 SPI_DMA1_13_ISR      /* 838 */
#endif
#if (SPI_DMA1_14_ISR_API == STD_ON)
#define INT_VECTOR_PE0_839 SPI_DMA1_14_ISR      /* 839 */
#endif
#if (SPI_DMA1_15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_840 SPI_DMA1_15_ISR      /* 840 */
#endif
#if defined (SPI_USE_MULTICORE)
#define INT_VECTOR_PE0_010 Timer_Task_0         /* 010 */
#else
#define INT_VECTOR_PE0_010 Timer_Task           /* 010 */
#endif
#if (SPI_MSPI0_TX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_576 SPI_MSPI0_TX_ISR     /* 576 */
#endif
#if (SPI_MSPI0_RX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_577 SPI_MSPI0_RX_ISR     /* 577 */
#endif
#if (SPI_MSPI0_FE_ISR_API == STD_ON)
#define INT_VECTOR_PE0_578 SPI_MSPI0_FE_ISR     /* 578 */
#endif
#if (SPI_MSPI1_TX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_580 SPI_MSPI1_TX_ISR     /* 580 */
#endif
#if (SPI_MSPI1_RX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_581 SPI_MSPI1_RX_ISR     /* 581 */
#endif
#if (SPI_MSPI1_FE_ISR_API == STD_ON)
#define INT_VECTOR_PE0_582 SPI_MSPI1_FE_ISR     /* 582 */
#endif
#if (SPI_MSPI2_TX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_584 SPI_MSPI2_TX_ISR     /* 584 */
#endif
#if (SPI_MSPI2_RX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_585 SPI_MSPI2_RX_ISR     /* 585 */
#endif
#if (SPI_MSPI2_FE_ISR_API == STD_ON)
#define INT_VECTOR_PE0_586 SPI_MSPI2_FE_ISR     /* 586 */
#endif
#if (SPI_MSPI3_TX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_588 SPI_MSPI3_TX_ISR     /* 588 */
#endif
#if (SPI_MSPI3_RX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_589 SPI_MSPI3_RX_ISR     /* 589 */
#endif
#if (SPI_MSPI3_FE_ISR_API == STD_ON)
#define INT_VECTOR_PE0_590 SPI_MSPI3_FE_ISR     /* 590 */
#endif
#if (SPI_MSPI4_TX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_592 SPI_MSPI4_TX_ISR     /* 592 */
#endif
#if (SPI_MSPI4_RX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_593 SPI_MSPI4_RX_ISR     /* 593 */
#endif
#if (SPI_MSPI4_FE_ISR_API == STD_ON)
#define INT_VECTOR_PE0_594 SPI_MSPI4_FE_ISR     /* 594 */
#endif
#if (SPI_MSPI5_TX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_596 SPI_MSPI5_TX_ISR     /* 596 */
#endif
#if (SPI_MSPI5_RX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_597 SPI_MSPI5_RX_ISR     /* 597 */
#endif
#if (SPI_MSPI5_FE_ISR_API == STD_ON)
#define INT_VECTOR_PE0_598 SPI_MSPI5_FE_ISR     /* 598 */
#endif
#if (SPI_MSPI6_TX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_600 SPI_MSPI6_TX_ISR     /* 600 */
#endif
#if (SPI_MSPI6_RX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_601 SPI_MSPI6_RX_ISR     /* 601 */
#endif
#if (SPI_MSPI6_FE_ISR_API == STD_ON)
#define INT_VECTOR_PE0_602 SPI_MSPI6_FE_ISR     /* 602 */
#endif
#if (SPI_MSPI7_TX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_851 SPI_MSPI7_TX_ISR     /* 851 */
#endif
#if (SPI_MSPI7_RX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_852 SPI_MSPI7_RX_ISR     /* 852 */
#endif
#if (SPI_MSPI7_FE_ISR_API == STD_ON)
#define INT_VECTOR_PE0_853 SPI_MSPI7_FE_ISR     /* 853 */
#endif
#if (SPI_MSPI8_TX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_855 SPI_MSPI8_TX_ISR     /* 855 */
#endif
#if (SPI_MSPI8_RX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_856 SPI_MSPI8_RX_ISR     /* 856 */
#endif
#if (SPI_MSPI8_FE_ISR_API == STD_ON)
#define INT_VECTOR_PE0_857 SPI_MSPI8_FE_ISR     /* 857 */
#endif
#if (SPI_MSPI9_TX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_859 SPI_MSPI9_TX_ISR     /* 859 */
#endif
#if (SPI_MSPI9_RX_ISR_API == STD_ON)
#define INT_VECTOR_PE0_860 SPI_MSPI9_RX_ISR     /* 860 */
#endif
#if (SPI_MSPI9_FE_ISR_API == STD_ON)
#define INT_VECTOR_PE0_861 SPI_MSPI9_FE_ISR     /* 861 */
#endif
#endif /* End of (SPI_ISR_CATEGORY_2 == STD_ON) */
#endif  /* SPI_MODULE_SAMPLE */

#ifdef ADC_MODULE_SAMPLE
#if (ADC_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
/* Defines the CAT1 interrupt mapping */
#ifdef ADC_SAMPLEAPP_OSTM                  /* Use OSTM0 interrupt for task timing */
#define INT_VECTOR_PE0_360 Timer0_Interrupt /* 360 */
#endif /* ADC_SAMPLEAPP_OSTM */
#if (ADC_ENABLE_PARITY_ERR_INT == STD_ON)
#define INT_VECTOR_PE0_008 ADC_PARITY_ERR_ISR /* 008 */
#endif
#if (ADC_DMA0_ISR_CH00_API == STD_ON)
#define INT_VECTOR_PE0_070 ADC_DMA0_CH00_ISR /* 070 */
#endif
#if (ADC_DMA0_ISR_CH01_API == STD_ON)
#define INT_VECTOR_PE0_071 ADC_DMA0_CH01_ISR /* 071 */
#endif
#if (ADC_DMA0_ISR_CH02_API == STD_ON)
#define INT_VECTOR_PE0_072 ADC_DMA0_CH02_ISR /* 072 */
#endif
#if (ADC_DMA0_ISR_CH03_API == STD_ON)
#define INT_VECTOR_PE0_073 ADC_DMA0_CH03_ISR /* 073 */
#endif
#if (ADC_DMA0_ISR_CH04_API == STD_ON)
#define INT_VECTOR_PE0_074 ADC_DMA0_CH04_ISR /* 074 */
#endif
#if (ADC_DMA0_ISR_CH05_API == STD_ON)
#define INT_VECTOR_PE0_075 ADC_DMA0_CH05_ISR /* 075 */
#endif
#if (ADC_DMA0_ISR_CH06_API == STD_ON)
#define INT_VECTOR_PE0_076 ADC_DMA0_CH06_ISR /* 076 */
#endif
#if (ADC_DMA0_ISR_CH07_API == STD_ON)
#define INT_VECTOR_PE0_077 ADC_DMA0_CH07_ISR /* 077 */
#endif
#if (ADC_DMA0_ISR_CH08_API == STD_ON)
#define INT_VECTOR_PE0_078 ADC_DMA0_CH08_ISR /* 078 */
#endif
#if (ADC_DMA0_ISR_CH09_API == STD_ON)
#define INT_VECTOR_PE0_079 ADC_DMA0_CH09_ISR /* 079 */
#endif
#if (ADC_DMA0_ISR_CH10_API == STD_ON)
#define INT_VECTOR_PE0_080 ADC_DMA0_CH10_ISR /* 080 */
#endif
#if (ADC_DMA0_ISR_CH11_API == STD_ON)
#define INT_VECTOR_PE0_081 ADC_DMA0_CH11_ISR /* 081 */
#endif
#if (ADC_DMA0_ISR_CH12_API == STD_ON)
#define INT_VECTOR_PE0_082 ADC_DMA0_CH12_ISR /* 082 */
#endif
#if (ADC_DMA0_ISR_CH13_API == STD_ON)
#define INT_VECTOR_PE0_083 ADC_DMA0_CH13_ISR /* 083 */
#endif
#if (ADC_DMA0_ISR_CH14_API == STD_ON)
#define INT_VECTOR_PE0_084 ADC_DMA0_CH14_ISR /* 084 */
#endif
#if (ADC_DMA0_ISR_CH15_API == STD_ON)
#define INT_VECTOR_PE0_085 ADC_DMA0_CH15_ISR /* 085 */
#endif
#if (ADC_DMA1_ISR_CH00_API == STD_ON)
#define INT_VECTOR_PE0_825 ADC_DMA1_CH00_ISR /* 825 */
#endif
#if (ADC_DMA1_ISR_CH01_API == STD_ON)
#define INT_VECTOR_PE0_826 ADC_DMA1_CH01_ISR /* 826 */
#endif
#if (ADC_DMA1_ISR_CH02_API == STD_ON)
#define INT_VECTOR_PE0_827 ADC_DMA1_CH02_ISR /* 827 */
#endif
#if (ADC_DMA1_ISR_CH03_API == STD_ON)
#define INT_VECTOR_PE0_828 ADC_DMA1_CH03_ISR /* 828 */
#endif
#if (ADC_DMA1_ISR_CH04_API == STD_ON)
#define INT_VECTOR_PE0_829 ADC_DMA1_CH04_ISR /* 829 */
#endif
#if (ADC_DMA1_ISR_CH05_API == STD_ON)
#define INT_VECTOR_PE0_830 ADC_DMA1_CH05_ISR /* 830 */
#endif
#if (ADC_DMA1_ISR_CH06_API == STD_ON)
#define INT_VECTOR_PE0_831 ADC_DMA1_CH06_ISR /* 831 */
#endif
#if (ADC_DMA1_ISR_CH07_API == STD_ON)
#define INT_VECTOR_PE0_832 ADC_DMA1_CH07_ISR /* 832 */
#endif
#if (ADC_DMA1_ISR_CH08_API == STD_ON)
#define INT_VECTOR_PE0_833 ADC_DMA1_CH08_ISR /* 833 */
#endif
#if (ADC_DMA1_ISR_CH09_API == STD_ON)
#define INT_VECTOR_PE0_834 ADC_DMA1_CH09_ISR /* 834 */
#endif
#if (ADC_DMA1_ISR_CH10_API == STD_ON)
#define INT_VECTOR_PE0_835 ADC_DMA1_CH10_ISR /* 835 */
#endif
#if (ADC_DMA1_ISR_CH11_API == STD_ON)
#define INT_VECTOR_PE0_836 ADC_DMA1_CH11_ISR /* 836 */
#endif
#if (ADC_DMA1_ISR_CH12_API == STD_ON)
#define INT_VECTOR_PE0_837 ADC_DMA1_CH12_ISR /* 837 */
#endif
#if (ADC_DMA1_ISR_CH13_API == STD_ON)
#define INT_VECTOR_PE0_838 ADC_DMA1_CH13_ISR /* 838 */
#endif
#if (ADC_DMA1_ISR_CH14_API == STD_ON)
#define INT_VECTOR_PE0_839 ADC_DMA1_CH14_ISR /* 839 */
#endif
#if (ADC_DMA1_ISR_CH15_API == STD_ON)
#define INT_VECTOR_PE0_840 ADC_DMA1_CH15_ISR /* 840 */
#endif
#if (ADC0_SG0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_441 ADC0_SG0_ISR /* 441 */
#endif
#if (ADC0_SG1_ISR_API == STD_ON)
#define INT_VECTOR_PE0_442 ADC0_SG1_ISR /* 442 */
#endif
#if (ADC0_SG2_ISR_API == STD_ON)
#define INT_VECTOR_PE0_443 ADC0_SG2_ISR /* 443 */
#endif
#if (ADC0_SG3_ISR_API == STD_ON)
#define INT_VECTOR_PE0_444 ADC0_SG3_ISR /* 444 */
#endif
#if (ADC0_SG4_ISR_API == STD_ON)
#define INT_VECTOR_PE0_445 ADC0_SG4_ISR /* 445 */
#endif
#if (ADC1_SG0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_451 ADC1_SG0_ISR /* 451 */
#endif
#if (ADC1_SG1_ISR_API == STD_ON)
#define INT_VECTOR_PE0_452 ADC1_SG1_ISR /* 452 */
#endif
#if (ADC1_SG2_ISR_API == STD_ON)
#define INT_VECTOR_PE0_453 ADC1_SG2_ISR /* 453 */
#endif
#if (ADC1_SG3_ISR_API == STD_ON)
#define INT_VECTOR_PE0_454 ADC1_SG3_ISR /* 454 */
#endif
#if (ADC1_SG4_ISR_API == STD_ON)
#define INT_VECTOR_PE0_455 ADC1_SG4_ISR /* 455 */
#endif
#if (ADC2_SG0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_446 ADC2_SG0_ISR /* 446 */
#endif
#if (ADC2_SG1_ISR_API == STD_ON)
#define INT_VECTOR_PE0_447 ADC2_SG1_ISR /* 447 */
#endif
#if (ADC2_SG2_ISR_API == STD_ON)
#define INT_VECTOR_PE0_448 ADC2_SG2_ISR /* 448 */
#endif
#if (ADC2_SG3_ISR_API == STD_ON)
#define INT_VECTOR_PE0_449 ADC2_SG3_ISR /* 449 */
#endif
#if (ADC2_SG4_ISR_API == STD_ON)
#define INT_VECTOR_PE0_450 ADC2_SG4_ISR /* 450 */
#endif
#if (ADC3_SG0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_456 ADC3_SG0_ISR /* 456 */
#endif
#if (ADC3_SG1_ISR_API == STD_ON)
#define INT_VECTOR_PE0_457 ADC3_SG1_ISR /* 457 */
#endif
#if (ADC3_SG2_ISR_API == STD_ON)
#define INT_VECTOR_PE0_458 ADC3_SG2_ISR /* 458 */
#endif
#if (ADC3_SG3_ISR_API == STD_ON)
#define INT_VECTOR_PE0_459 ADC3_SG3_ISR /* 459 */
#endif
#if (ADC3_SG4_ISR_API == STD_ON)
#define INT_VECTOR_PE0_460 ADC3_SG4_ISR /* 460 */
#endif
#if (ADC_ENABLE_ERR_INT == STD_ON)
#define INT_VECTOR_PE0_461 ADC0_ERR_ISR /* 461 */
#define INT_VECTOR_PE0_463 ADC1_ERR_ISR /* 463 */
#define INT_VECTOR_PE0_462 ADC2_ERR_ISR /* 462 */
#define INT_VECTOR_PE0_464 ADC3_ERR_ISR /* 464 */
#endif
#endif  /* (ADC_ISR_CATEGORY_2 == STD_ON) */
#endif  /* ADC_MODULE_SAMPLE */

#ifdef ICU_MODULE_SAMPLE
#if (ICU_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT1 interrupt mapping */
#else
  
#ifdef ICU_SAMPLEAPP_OSTM                  /* Use OSTM0 interrupt for sample app task timing */
extern void Timer0_Interrupt(void);
#define INT_VECTOR_PE0_360 Timer0_Interrupt /* 360 */
#endif  

/* IRQ */
#if (ICU_EXT_INTP_CH00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_765 EXT_INTP_CH00_ISR /* 765 */
#endif
#if (ICU_EXT_INTP_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_766 EXT_INTP_CH01_ISR /* 766 */
#endif
#if (ICU_EXT_INTP_CH02_ISR_API == STD_ON)
#define INT_VECTOR_PE0_767 EXT_INTP_CH02_ISR /* 767 */
#endif
#if (ICU_EXT_INTP_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_768 EXT_INTP_CH03_ISR /* 768 */
#endif
#if (ICU_EXT_INTP_CH04_ISR_API == STD_ON)
#define INT_VECTOR_PE0_769 EXT_INTP_CH04_ISR /* 769 */
#endif
#if (ICU_EXT_INTP_CH05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_770 EXT_INTP_CH05_ISR /* 770 */
#endif
#if (ICU_EXT_INTP_CH06_ISR_API == STD_ON)
#define INT_VECTOR_PE0_771 EXT_INTP_CH06_ISR /* 771 */
#endif
#if (ICU_EXT_INTP_CH07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_772 EXT_INTP_CH07_ISR /* 772 */
#endif
#if (ICU_EXT_INTP_CH08_ISR_API == STD_ON)
#define INT_VECTOR_PE0_773 EXT_INTP_CH08_ISR /* 773 */
#endif
#if (ICU_EXT_INTP_CH09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_774 EXT_INTP_CH09_ISR /* 774 */
#endif
#if (ICU_EXT_INTP_CH10_ISR_API == STD_ON)
#define INT_VECTOR_PE0_775 EXT_INTP_CH10_ISR /* 775 */
#endif
#if (ICU_EXT_INTP_CH11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_776 EXT_INTP_CH11_ISR /* 776 */
#endif
#if (ICU_EXT_INTP_CH12_ISR_API == STD_ON)
#define INT_VECTOR_PE0_777 EXT_INTP_CH12_ISR /* 777 */
#endif
#if (ICU_EXT_INTP_CH13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_778 EXT_INTP_CH13_ISR /* 778 */
#endif
#if (ICU_EXT_INTP_CH14_ISR_API == STD_ON)
#define INT_VECTOR_PE0_779 EXT_INTP_CH14_ISR /* 779 */
#endif
#if (ICU_EXT_INTP_CH15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_780 EXT_INTP_CH15_ISR /* 780 */
#endif
#if (ICU_EXT_INTP_CH16_ISR_API == STD_ON)
#define INT_VECTOR_PE0_781 EXT_INTP_CH16_ISR /* 781 */
#endif
#if (ICU_EXT_INTP_CH17_ISR_API == STD_ON)
#define INT_VECTOR_PE0_782 EXT_INTP_CH17_ISR /* 782 */
#endif
#if (ICU_EXT_INTP_CH18_ISR_API == STD_ON)
#define INT_VECTOR_PE0_783 EXT_INTP_CH18_ISR /* 783 */
#endif
#if (ICU_EXT_INTP_CH19_ISR_API == STD_ON)
#define INT_VECTOR_PE0_784 EXT_INTP_CH19_ISR /* 784 */
#endif
#if (ICU_EXT_INTP_CH20_ISR_API == STD_ON)
#define INT_VECTOR_PE0_785 EXT_INTP_CH20_ISR /* 785 */
#endif
#if (ICU_EXT_INTP_CH21_ISR_API == STD_ON)
#define INT_VECTOR_PE0_786 EXT_INTP_CH21_ISR /* 786 */
#endif
#if (ICU_EXT_INTP_CH22_ISR_API == STD_ON)
#define INT_VECTOR_PE0_787 EXT_INTP_CH22_ISR /* 787 */
#endif
#if (ICU_EXT_INTP_CH23_ISR_API == STD_ON)
#define INT_VECTOR_PE0_788 EXT_INTP_CH23_ISR /* 788 */
#endif
#if (ICU_EXT_INTP_CH24_ISR_API == STD_ON)
#define INT_VECTOR_PE0_789 EXT_INTP_CH24_ISR /* 789 */
#endif
#if (ICU_EXT_INTP_CH25_ISR_API == STD_ON)
#define INT_VECTOR_PE0_790 EXT_INTP_CH25_ISR /* 790 */
#endif
#if (ICU_EXT_INTP_CH26_ISR_API == STD_ON)
#define INT_VECTOR_PE0_791 EXT_INTP_CH26_ISR /* 791 */
#endif
#if (ICU_EXT_INTP_CH27_ISR_API == STD_ON)
#define INT_VECTOR_PE0_792 EXT_INTP_CH27_ISR /* 792 */
#endif
#if (ICU_EXT_INTP_CH28_ISR_API == STD_ON)
#define INT_VECTOR_PE0_793 EXT_INTP_CH28_ISR /* 793 */
#endif
#if (ICU_EXT_INTP_CH29_ISR_API == STD_ON)
#define INT_VECTOR_PE0_794 EXT_INTP_CH29_ISR /* 794 */
#endif
#if (ICU_EXT_INTP_CH30_ISR_API == STD_ON)
#define INT_VECTOR_PE0_795 EXT_INTP_CH30_ISR /* 795 */
#endif
#if (ICU_EXT_INTP_CH31_ISR_API == STD_ON)
#define INT_VECTOR_PE0_796 EXT_INTP_CH31_ISR /* 796 */
#endif
#if (ICU_EXT_INTP_CH32_ISR_API == STD_ON)
#define INT_VECTOR_PE0_797 EXT_INTP_CH32_ISR /* 797 */
#endif
#if (ICU_EXT_INTP_CH33_ISR_API == STD_ON)
#define INT_VECTOR_PE0_798 EXT_INTP_CH33_ISR /* 798 */
#endif
#if (ICU_EXT_INTP_CH34_ISR_API == STD_ON)
#define INT_VECTOR_PE0_799 EXT_INTP_CH34_ISR /* 799 */
#endif
#if (ICU_EXT_INTP_CH35_ISR_API == STD_ON)
#define INT_VECTOR_PE0_800 EXT_INTP_CH35_ISR /* 800 */
#endif
#if (ICU_EXT_INTP_CH36_ISR_API == STD_ON)
#define INT_VECTOR_PE0_801 EXT_INTP_CH36_ISR /* 801 */
#endif
#if (ICU_EXT_INTP_CH37_ISR_API == STD_ON)
#define INT_VECTOR_PE0_802 EXT_INTP_CH37_ISR /* 802 */
#endif
#if (ICU_EXT_INTP_CH38_ISR_API == STD_ON)
#define INT_VECTOR_PE0_803 EXT_INTP_CH38_ISR /* 803 */
#endif
#if (ICU_EXT_INTP_CH39_ISR_API == STD_ON)
#define INT_VECTOR_PE0_804 EXT_INTP_CH39_ISR /* 804 */
#endif
#if (ICU_EXT_INTP_CH40_ISR_API == STD_ON)
#define INT_VECTOR_PE0_817 EXT_INTP_CH40_ISR /* 817 */
#endif
#if (ICU_EXT_INTP_CH41_ISR_API == STD_ON)
#define INT_VECTOR_PE0_818 EXT_INTP_CH41_ISR /* 818 */
#endif
#if (ICU_EXT_INTP_CH42_ISR_API == STD_ON)
#define INT_VECTOR_PE0_819 EXT_INTP_CH42_ISR /* 819 */
#endif
#if (ICU_EXT_INTP_CH43_ISR_API == STD_ON)
#define INT_VECTOR_PE0_820 EXT_INTP_CH43_ISR /* 820 */
#endif

#if (ICU_TAUD0_CH00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_010 TAUD0_CH00_ISR /* 10 */
#endif
#if (ICU_TAUD0_CH02_ISR_API == STD_ON)
#define INT_VECTOR_PE0_011 TAUD0_CH02_ISR /* 11 */
#endif
#if (ICU_TAUD0_CH04_ISR_API == STD_ON)
#define INT_VECTOR_PE0_012 TAUD0_CH04_ISR /* 12 */
#endif
#if (ICU_TAUD0_CH06_ISR_API == STD_ON)
#define INT_VECTOR_PE0_013 TAUD0_CH06_ISR /* 13 */
#endif
#if (ICU_TAUD0_CH08_ISR_API == STD_ON)
#define INT_VECTOR_PE0_023 TAUD0_CH08_ISR /* 23 */
#endif
#if (ICU_TAUD0_CH10_ISR_API == STD_ON)
#define INT_VECTOR_PE0_024 TAUD0_CH10_ISR /* 24 */
#endif
#if (ICU_TAUD0_CH12_ISR_API == STD_ON)
#define INT_VECTOR_PE0_025 TAUD0_CH12_ISR /* 25 */
#endif
#if (ICU_TAUD0_CH14_ISR_API == STD_ON)
#define INT_VECTOR_PE0_026 TAUD0_CH14_ISR /* 26 */
#endif
#if (ICU_TAUD0_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_320 TAUD0_CH01_ISR /* 320 */
#endif
#if (ICU_TAUD0_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_321 TAUD0_CH03_ISR /* 321 */
#endif
#if (ICU_TAUD0_CH05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_322 TAUD0_CH05_ISR /* 322 */
#endif
#if (ICU_TAUD0_CH07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_323 TAUD0_CH07_ISR /* 323 */
#endif
#if (ICU_TAUD0_CH09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_324 TAUD0_CH09_ISR /* 324 */
#endif
#if (ICU_TAUD0_CH11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_325 TAUD0_CH11_ISR /* 325 */
#endif
#if (ICU_TAUD0_CH13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_326 TAUD0_CH13_ISR /* 326 */
#endif
#if (ICU_TAUD0_CH15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_327 TAUD0_CH15_ISR /* 327 */
#endif

#if (ICU_TAUD1_CH00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_328 TAUD1_CH00_ISR /* 328 */
#endif
#if (ICU_TAUD1_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_329 TAUD1_CH01_ISR /* 329 */
#endif
#if (ICU_TAUD1_CH02_ISR_API == STD_ON)
#define INT_VECTOR_PE0_330 TAUD1_CH02_ISR /* 330 */
#endif
#if (ICU_TAUD1_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_331 TAUD1_CH03_ISR /* 331 */
#endif
#if (ICU_TAUD1_CH04_ISR_API == STD_ON)
#define INT_VECTOR_PE0_332 TAUD1_CH04_ISR /* 332 */
#endif
#if (ICU_TAUD1_CH05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_333 TAUD1_CH05_ISR /* 333 */
#endif
#if (ICU_TAUD1_CH06_ISR_API == STD_ON)
#define INT_VECTOR_PE0_334 TAUD1_CH06_ISR /* 334 */
#endif
#if (ICU_TAUD1_CH07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_335 TAUD1_CH07_ISR /* 335 */
#endif
#if (ICU_TAUD1_CH08_ISR_API == STD_ON)
#define INT_VECTOR_PE0_336 TAUD1_CH08_ISR /* 336 */
#endif
#if (ICU_TAUD1_CH09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_337 TAUD1_CH09_ISR /* 337 */
#endif
#if (ICU_TAUD1_CH10_ISR_API == STD_ON)
#define INT_VECTOR_PE0_338 TAUD1_CH10_ISR /* 338 */
#endif
#if (ICU_TAUD1_CH11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_339 TAUD1_CH11_ISR /* 339 */
#endif
#if (ICU_TAUD1_CH12_ISR_API == STD_ON)
#define INT_VECTOR_PE0_340 TAUD1_CH12_ISR /* 340 */
#endif
#if (ICU_TAUD1_CH13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_341 TAUD1_CH13_ISR /* 341 */
#endif
#if (ICU_TAUD1_CH14_ISR_API == STD_ON)
#define INT_VECTOR_PE0_342 TAUD1_CH14_ISR /* 342 */
#endif
#if (ICU_TAUD1_CH15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_343 TAUD1_CH15_ISR /* 343 */
#endif

#if (ICU_TAUD2_CH00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_344 TAUD2_CH00_ISR /* 344 */
#endif
#if (ICU_TAUD2_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_345 TAUD2_CH01_ISR /* 345 */
#endif
#if (ICU_TAUD2_CH02_ISR_API == STD_ON)
#define INT_VECTOR_PE0_346 TAUD2_CH02_ISR /* 346 */
#endif
#if (ICU_TAUD2_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_347 TAUD2_CH03_ISR /* 347 */
#endif
#if (ICU_TAUD2_CH04_ISR_API == STD_ON)
#define INT_VECTOR_PE0_348 TAUD2_CH04_ISR /* 348 */
#endif
#if (ICU_TAUD2_CH05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_349 TAUD2_CH05_ISR /* 349 */
#endif
#if (ICU_TAUD2_CH06_ISR_API == STD_ON)
#define INT_VECTOR_PE0_350 TAUD2_CH06_ISR /* 350 */
#endif
#if (ICU_TAUD2_CH07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_351 TAUD2_CH07_ISR /* 351 */
#endif
#if (ICU_TAUD2_CH08_ISR_API == STD_ON)
#define INT_VECTOR_PE0_352 TAUD2_CH08_ISR /* 352 */
#endif
#if (ICU_TAUD2_CH09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_353 TAUD2_CH09_ISR /* 353 */
#endif
#if (ICU_TAUD2_CH10_ISR_API == STD_ON)
#define INT_VECTOR_PE0_354 TAUD2_CH10_ISR /* 354 */
#endif
#if (ICU_TAUD2_CH11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_355 TAUD2_CH11_ISR /* 355 */
#endif
#if (ICU_TAUD2_CH12_ISR_API == STD_ON)
#define INT_VECTOR_PE0_356 TAUD2_CH12_ISR /* 356 */
#endif
#if (ICU_TAUD2_CH13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_357 TAUD2_CH13_ISR /* 357 */
#endif
#if (ICU_TAUD2_CH14_ISR_API == STD_ON)
#define INT_VECTOR_PE0_358 TAUD2_CH14_ISR /* 358 */
#endif
#if (ICU_TAUD2_CH15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_359 TAUD2_CH15_ISR /* 359 */
#endif

#if (ICU_TAUD3_CH00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_379 TAUD3_CH00_ISR /* 379 */
#define INT_VECTOR_PE0_505 TAUD3_CH00_ISR /* 505 */
  #ifndef INT_VECTOR_PE0_793
  #define INT_VECTOR_PE0_793 TAUD3_CH00_ISR /* 793 */
  #endif
#endif
#if (ICU_TAUD3_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_380 TAUD3_CH01_ISR /* 380 */
#define INT_VECTOR_PE0_506 TAUD3_CH01_ISR /* 506 */
  #ifndef INT_VECTOR_PE0_794
  #define INT_VECTOR_PE0_794 TAUD3_CH01_ISR /* 794 */
  #endif
#endif
#if (ICU_TAUD3_CH02_ISR_API == STD_ON)
#define INT_VECTOR_PE0_381 TAUD3_CH02_ISR /* 381 */
#define INT_VECTOR_PE0_507 TAUD3_CH02_ISR /* 507 */
  #ifndef INT_VECTOR_PE0_795
  #define INT_VECTOR_PE0_795 TAUD3_CH02_ISR /* 795 */
  #endif
#endif
#if (ICU_TAUD3_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_382 TAUD3_CH03_ISR /* 382 */
#define INT_VECTOR_PE0_508 TAUD3_CH03_ISR /* 508 */
  #ifndef INT_VECTOR_PE0_796
  #define INT_VECTOR_PE0_796 TAUD3_CH03_ISR /* 796 */
  #endif
#endif
#if (ICU_TAUD3_CH04_ISR_API == STD_ON)
#define INT_VECTOR_PE0_383 TAUD3_CH04_ISR /* 383 */
#define INT_VECTOR_PE0_509 TAUD3_CH04_ISR /* 509 */
  #ifndef INT_VECTOR_PE0_797
  #define INT_VECTOR_PE0_797 TAUD3_CH04_ISR /* 797 */
  #endif
#endif
#if (ICU_TAUD3_CH05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_384 TAUD3_CH05_ISR /* 384 */
#define INT_VECTOR_PE0_510 TAUD3_CH05_ISR /* 510 */
  #ifndef INT_VECTOR_PE0_798
  #define INT_VECTOR_PE0_798 TAUD3_CH05_ISR /* 798 */
  #endif
#endif
#if (ICU_TAUD3_CH06_ISR_API == STD_ON)
#define INT_VECTOR_PE0_385 TAUD3_CH06_ISR /* 385 */
#define INT_VECTOR_PE0_511 TAUD3_CH06_ISR /* 511 */
  #ifndef INT_VECTOR_PE0_799
  #define INT_VECTOR_PE0_799 TAUD3_CH06_ISR /* 799 */
  #endif
#endif
#if (ICU_TAUD3_CH07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_386 TAUD3_CH07_ISR /* 386 */
#define INT_VECTOR_PE0_512 TAUD3_CH07_ISR /* 512 */
  #ifndef INT_VECTOR_PE0_800
  #define INT_VECTOR_PE0_800 TAUD3_CH07_ISR /* 800 */
  #endif
#endif
#if (ICU_TAUD3_CH08_ISR_API == STD_ON)
#define INT_VECTOR_PE0_387 TAUD3_CH08_ISR /* 387 */
#define INT_VECTOR_PE0_513 TAUD3_CH08_ISR /* 513 */
  #ifndef INT_VECTOR_PE0_801
  #define INT_VECTOR_PE0_801 TAUD3_CH08_ISR /* 801 */
  #endif
#endif
#if (ICU_TAUD3_CH09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_388 TAUD3_CH09_ISR /* 388 */
#define INT_VECTOR_PE0_514 TAUD3_CH09_ISR /* 514 */
  #ifndef INT_VECTOR_PE0_802
  #define INT_VECTOR_PE0_802 TAUD3_CH09_ISR /* 802 */
  #endif
#endif
#if (ICU_TAUD3_CH10_ISR_API == STD_ON)
#define INT_VECTOR_PE0_389 TAUD3_CH10_ISR /* 389 */
#define INT_VECTOR_PE0_515 TAUD3_CH10_ISR /* 515 */
  #ifndef INT_VECTOR_PE0_803
  #define INT_VECTOR_PE0_803 TAUD3_CH10_ISR /* 803 */
  #endif
#endif
#if (ICU_TAUD3_CH11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_390 TAUD3_CH11_ISR /* 390 */
#define INT_VECTOR_PE0_516 TAUD3_CH11_ISR /* 516 */
  #ifndef INT_VECTOR_PE0_804
  #define INT_VECTOR_PE0_804 TAUD3_CH11_ISR /* 804 */
  #endif
#endif
#if (ICU_TAUD3_CH12_ISR_API == STD_ON)
#define INT_VECTOR_PE0_391 TAUD3_CH12_ISR /* 391 */
#define INT_VECTOR_PE0_517 TAUD3_CH12_ISR /* 517 */
  #ifndef INT_VECTOR_PE0_817
  #define INT_VECTOR_PE0_817 TAUD3_CH12_ISR /* 817 */
  #endif
#endif
#if (ICU_TAUD3_CH13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_392 TAUD3_CH13_ISR /* 392 */
#define INT_VECTOR_PE0_518 TAUD3_CH13_ISR /* 518 */
  #ifndef INT_VECTOR_PE0_818
  #define INT_VECTOR_PE0_818 TAUD3_CH13_ISR /* 818 */
  #endif
#endif
#if (ICU_TAUD3_CH14_ISR_API == STD_ON)
#define INT_VECTOR_PE0_393 TAUD3_CH14_ISR /* 393 */
#define INT_VECTOR_PE0_519 TAUD3_CH14_ISR /* 519 */
  #ifndef INT_VECTOR_PE0_819
  #define INT_VECTOR_PE0_819 TAUD3_CH14_ISR /* 819 */
  #endif
#endif
#if (ICU_TAUD3_CH15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_394 TAUD3_CH15_ISR /* 394 */
#define INT_VECTOR_PE0_520 TAUD3_CH15_ISR /* 520 */
  #ifndef INT_VECTOR_PE0_820
  #define INT_VECTOR_PE0_820 TAUD3_CH15_ISR /* 820 */
  #endif
#endif

#if (ICU_TAUJ2_CH00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_960 TAUJ2_CH00_ISR /* 960 */
#endif
#if (ICU_TAUJ2_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_961 TAUJ2_CH01_ISR /* 961 */
#endif
#if (ICU_TAUJ2_CH02_ISR_API == STD_ON)
#define INT_VECTOR_PE0_962 TAUJ2_CH02_ISR /* 962 */
#endif
#if (ICU_TAUJ2_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_963 TAUJ2_CH03_ISR /* 963 */
#endif

/* ICU GTM */
#if (ICU_GTM_TIM0_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_086      GTM_TIM0_CH0_ISR
#endif

#if (ICU_GTM_TIM0_CH1_ISR_API == STD_ON)
#define INT_VECTOR_PE0_087      GTM_TIM0_CH1_ISR
#endif

#if (ICU_GTM_TIM0_CH2_ISR_API == STD_ON)
#define INT_VECTOR_PE0_088      GTM_TIM0_CH2_ISR
#endif

#if (ICU_GTM_TIM0_CH3_ISR_API == STD_ON)
#define INT_VECTOR_PE0_089      GTM_TIM0_CH3_ISR
#endif

#if (ICU_GTM_TIM0_CH4_ISR_API == STD_ON)
#define INT_VECTOR_PE0_090      GTM_TIM0_CH4_ISR
#endif

#if (ICU_GTM_TIM0_CH5_ISR_API == STD_ON)
#define INT_VECTOR_PE0_091      GTM_TIM0_CH5_ISR
#endif

#if (ICU_GTM_TIM0_CH6_ISR_API == STD_ON)
#define INT_VECTOR_PE0_092      GTM_TIM0_CH6_ISR
#endif

#if (ICU_GTM_TIM0_CH7_ISR_API == STD_ON)
#define INT_VECTOR_PE0_093      GTM_TIM0_CH7_ISR
#endif

#if (ICU_GTM_TIM1_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_102      GTM_TIM1_CH0_ISR
#endif

#if (ICU_GTM_TIM1_CH1_ISR_API == STD_ON)
#define INT_VECTOR_PE0_103      GTM_TIM1_CH1_ISR
#endif

#if (ICU_GTM_TIM1_CH2_ISR_API == STD_ON)
#define INT_VECTOR_PE0_104      GTM_TIM1_CH2_ISR
#endif

#if (ICU_GTM_TIM1_CH3_ISR_API == STD_ON)
#define INT_VECTOR_PE0_105      GTM_TIM1_CH3_ISR
#endif

#if (ICU_GTM_TIM1_CH4_ISR_API == STD_ON)
#define INT_VECTOR_PE0_106      GTM_TIM1_CH4_ISR
#endif

#if (ICU_GTM_TIM1_CH5_ISR_API == STD_ON)
#define INT_VECTOR_PE0_107      GTM_TIM1_CH5_ISR
#endif

#if (ICU_GTM_TIM1_CH6_ISR_API == STD_ON)
#define INT_VECTOR_PE0_108      GTM_TIM1_CH6_ISR
#endif

#if (ICU_GTM_TIM1_CH7_ISR_API == STD_ON)
#define INT_VECTOR_PE0_109      GTM_TIM1_CH7_ISR
#endif

#if (ICU_GTM_TIM2_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_118      GTM_TIM2_CH0_ISR
#endif

#if (ICU_GTM_TIM2_CH1_ISR_API == STD_ON)
#define INT_VECTOR_PE0_119      GTM_TIM2_CH1_ISR
#endif

#if (ICU_GTM_TIM2_CH2_ISR_API == STD_ON)
#define INT_VECTOR_PE0_120      GTM_TIM2_CH2_ISR
#endif

#if (ICU_GTM_TIM2_CH3_ISR_API == STD_ON)
#define INT_VECTOR_PE0_121      GTM_TIM2_CH3_ISR
#endif

#if (ICU_GTM_TIM2_CH4_ISR_API == STD_ON)
#define INT_VECTOR_PE0_122      GTM_TIM2_CH4_ISR
#endif

#if (ICU_GTM_TIM2_CH5_ISR_API == STD_ON)
#define INT_VECTOR_PE0_123      GTM_TIM2_CH5_ISR
#endif

#if (ICU_GTM_TIM2_CH6_ISR_API == STD_ON)
#define INT_VECTOR_PE0_124      GTM_TIM2_CH6_ISR
#endif

#if (ICU_GTM_TIM2_CH7_ISR_API == STD_ON)
#define INT_VECTOR_PE0_125      GTM_TIM2_CH7_ISR
#endif

#if (ICU_GTM_TIM3_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_134      GTM_TIM3_CH0_ISR
#endif

#if (ICU_GTM_TIM3_CH1_ISR_API == STD_ON)
#define INT_VECTOR_PE0_135      GTM_TIM3_CH1_ISR
#endif

#if (ICU_GTM_TIM3_CH2_ISR_API == STD_ON)
#define INT_VECTOR_PE0_136      GTM_TIM3_CH2_ISR
#endif

#if (ICU_GTM_TIM3_CH3_ISR_API == STD_ON)
#define INT_VECTOR_PE0_137      GTM_TIM3_CH3_ISR
#endif

#if (ICU_GTM_TIM3_CH4_ISR_API == STD_ON)
#define INT_VECTOR_PE0_138      GTM_TIM3_CH4_ISR
#endif

#if (ICU_GTM_TIM3_CH5_ISR_API == STD_ON)
#define INT_VECTOR_PE0_139      GTM_TIM3_CH5_ISR
#endif

#if (ICU_GTM_TIM3_CH6_ISR_API == STD_ON)
#define INT_VECTOR_PE0_140      GTM_TIM3_CH6_ISR
#endif

#if (ICU_GTM_TIM3_CH7_ISR_API == STD_ON)
#define INT_VECTOR_PE0_141      GTM_TIM3_CH7_ISR
#endif

#if (ICU_GTM_TIM4_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_150      GTM_TIM4_CH0_ISR
#endif

#if (ICU_GTM_TIM4_CH1_ISR_API == STD_ON)
#define INT_VECTOR_PE0_151      GTM_TIM4_CH1_ISR
#endif

#if (ICU_GTM_TIM4_CH2_ISR_API == STD_ON)
#define INT_VECTOR_PE0_152      GTM_TIM4_CH2_ISR
#endif

#if (ICU_GTM_TIM4_CH3_ISR_API == STD_ON)
#define INT_VECTOR_PE0_153      GTM_TIM4_CH3_ISR
#endif

#if (ICU_GTM_TIM4_CH4_ISR_API == STD_ON)
#define INT_VECTOR_PE0_154      GTM_TIM4_CH4_ISR
#endif

#if (ICU_GTM_TIM4_CH5_ISR_API == STD_ON)
#define INT_VECTOR_PE0_155      GTM_TIM4_CH5_ISR
#endif

#if (ICU_GTM_TIM4_CH6_ISR_API == STD_ON)
#define INT_VECTOR_PE0_156      GTM_TIM4_CH6_ISR
#endif

#if (ICU_GTM_TIM4_CH7_ISR_API == STD_ON)
#define INT_VECTOR_PE0_157      GTM_TIM4_CH7_ISR
#endif

#if (ICU_GTM_TIM5_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_166      GTM_TIM5_CH0_ISR
#endif

#if (ICU_GTM_TIM5_CH1_ISR_API == STD_ON)
#define INT_VECTOR_PE0_167      GTM_TIM5_CH1_ISR
#endif

#if (ICU_GTM_TIM5_CH2_ISR_API == STD_ON)
#define INT_VECTOR_PE0_168      GTM_TIM5_CH2_ISR
#endif

#if (ICU_GTM_TIM5_CH3_ISR_API == STD_ON)
#define INT_VECTOR_PE0_169      GTM_TIM5_CH3_ISR
#endif

#if (ICU_GTM_TIM5_CH4_ISR_API == STD_ON)
#define INT_VECTOR_PE0_170      GTM_TIM5_CH4_ISR
#endif

#if (ICU_GTM_TIM5_CH5_ISR_API == STD_ON)
#define INT_VECTOR_PE0_171      GTM_TIM5_CH5_ISR
#endif

#if (ICU_GTM_TIM5_CH6_ISR_API == STD_ON)
#define INT_VECTOR_PE0_172      GTM_TIM5_CH6_ISR
#endif

#if (ICU_GTM_TIM5_CH7_ISR_API == STD_ON)
#define INT_VECTOR_PE0_173      GTM_TIM5_CH7_ISR
#endif

#if (ICU_GTM_TIM6_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_182      GTM_TIM6_CH0_ISR
#endif

#if (ICU_GTM_TIM6_CH1_ISR_API == STD_ON)
#define INT_VECTOR_PE0_183      GTM_TIM6_CH1_ISR
#endif

#if (ICU_GTM_TIM6_CH2_ISR_API == STD_ON)
#define INT_VECTOR_PE0_184      GTM_TIM6_CH2_ISR
#endif

#if (ICU_GTM_TIM6_CH3_ISR_API == STD_ON)
#define INT_VECTOR_PE0_185      GTM_TIM6_CH3_ISR
#endif

#if (ICU_GTM_TIM6_CH4_ISR_API == STD_ON)
#define INT_VECTOR_PE0_186      GTM_TIM6_CH4_ISR
#endif

#if (ICU_GTM_TIM6_CH5_ISR_API == STD_ON)
#define INT_VECTOR_PE0_187      GTM_TIM6_CH5_ISR
#endif

#if (ICU_GTM_TIM6_CH6_ISR_API == STD_ON)
#define INT_VECTOR_PE0_188      GTM_TIM6_CH6_ISR
#endif

#if (ICU_GTM_TIM6_CH7_ISR_API == STD_ON)
#define INT_VECTOR_PE0_189      GTM_TIM6_CH7_ISR
#endif

#endif /* End of ICU_ISR_CATEGORY_2 is STD_OFF */
#endif /* ICU_MODULE_SAMPLE */

#ifdef PWM_MODULE_SAMPLE
  #if (PWM_ISR_CATEGORY_2 == STD_ON)
  #else      
  #if (PWM_GTM_UNIT_USED == STD_ON)
  #if (PWM_ATOM0_CH00_ISR_API == STD_ON) || (PWM_ATOM0_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_086 GTM_ATOM0_IRQ0_ISR /* 086 */
    #endif
    #if (PWM_ATOM0_CH02_ISR_API == STD_ON) || (PWM_ATOM0_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_088 GTM_ATOM0_IRQ1_ISR /* 088 */
    #endif
    #if (PWM_ATOM0_CH04_ISR_API == STD_ON) || (PWM_ATOM0_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_090 GTM_ATOM0_IRQ2_ISR /* 090 */
    #endif
    #if (PWM_ATOM0_CH06_ISR_API == STD_ON) || (PWM_ATOM0_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_092 GTM_ATOM0_IRQ3_ISR /* 092 */
    #endif
  #if (PWM_ATOM1_CH00_ISR_API == STD_ON) || (PWM_ATOM1_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_102 GTM_ATOM1_IRQ0_ISR /* 102 */
    #endif
    #if (PWM_ATOM1_CH02_ISR_API == STD_ON) || (PWM_ATOM1_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_104 GTM_ATOM1_IRQ1_ISR /* 104 */
    #endif
    #if (PWM_ATOM1_CH04_ISR_API == STD_ON) || (PWM_ATOM1_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_106 GTM_ATOM1_IRQ2_ISR /* 106 */
    #endif
    #if (PWM_ATOM1_CH06_ISR_API == STD_ON) || (PWM_ATOM1_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_108 GTM_ATOM1_IRQ3_ISR /* 108 */
    #endif
	#if (PWM_ATOM2_CH00_ISR_API == STD_ON) || (PWM_ATOM2_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_118 GTM_ATOM2_IRQ0_ISR /* 118 */
    #endif
    #if (PWM_ATOM2_CH02_ISR_API == STD_ON) || (PWM_ATOM2_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_120 GTM_ATOM2_IRQ1_ISR /* 120 */
    #endif
    #if (PWM_ATOM2_CH04_ISR_API == STD_ON) || (PWM_ATOM2_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_122 GTM_ATOM2_IRQ2_ISR /* 122 */
    #endif
    #if (PWM_ATOM2_CH06_ISR_API == STD_ON) || (PWM_ATOM2_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_124 GTM_ATOM2_IRQ3_ISR /* 124 */
    #endif
	#if (PWM_ATOM3_CH00_ISR_API == STD_ON) || (PWM_ATOM3_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_134 GTM_ATOM3_IRQ0_ISR /* 134 */
    #endif
    #if (PWM_ATOM3_CH02_ISR_API == STD_ON) || (PWM_ATOM3_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_136 GTM_ATOM3_IRQ1_ISR /* 136 */
    #endif
    #if (PWM_ATOM3_CH04_ISR_API == STD_ON) || (PWM_ATOM3_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_138 GTM_ATOM3_IRQ2_ISR /* 138 */
    #endif
    #if (PWM_ATOM3_CH06_ISR_API == STD_ON) || (PWM_ATOM3_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_140 GTM_ATOM3_IRQ3_ISR /* 140 */
    #endif
	#if (PWM_ATOM4_CH00_ISR_API == STD_ON) || (PWM_ATOM4_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_150 GTM_ATOM4_IRQ0_ISR /* 150 */
    #endif
    #if (PWM_ATOM4_CH02_ISR_API == STD_ON) || (PWM_ATOM4_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_152 GTM_ATOM4_IRQ1_ISR /* 152 */
    #endif
    #if (PWM_ATOM4_CH04_ISR_API == STD_ON) || (PWM_ATOM4_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_154 GTM_ATOM4_IRQ2_ISR /* 154 */
    #endif
    #if (PWM_ATOM4_CH06_ISR_API == STD_ON) || (PWM_ATOM4_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_156 GTM_ATOM4_IRQ3_ISR /* 156 */
    #endif
	#if (PWM_ATOM5_CH00_ISR_API == STD_ON) || (PWM_ATOM5_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_166 GTM_ATOM5_IRQ0_ISR /* 166 */
    #endif
    #if (PWM_ATOM5_CH02_ISR_API == STD_ON) || (PWM_ATOM5_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_168 GTM_ATOM5_IRQ1_ISR /* 168 */
    #endif
    #if (PWM_ATOM5_CH04_ISR_API == STD_ON) || (PWM_ATOM5_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_170 GTM_ATOM5_IRQ2_ISR /* 170 */
    #endif
    #if (PWM_ATOM5_CH06_ISR_API == STD_ON) || (PWM_ATOM5_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_172 GTM_ATOM5_IRQ3_ISR /* 172 */
    #endif
	#if (PWM_ATOM6_CH00_ISR_API == STD_ON) || (PWM_ATOM6_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_182 GTM_ATOM6_IRQ0_ISR /* 182 */
    #endif
    #if (PWM_ATOM6_CH02_ISR_API == STD_ON) || (PWM_ATOM6_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_184 GTM_ATOM6_IRQ1_ISR /* 184 */
    #endif
    #if (PWM_ATOM6_CH04_ISR_API == STD_ON) || (PWM_ATOM6_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_186 GTM_ATOM6_IRQ2_ISR /* 186 */
    #endif
    #if (PWM_ATOM6_CH06_ISR_API == STD_ON) ||(PWM_ATOM6_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_188 GTM_ATOM6_IRQ3_ISR /* 188 */
    #endif
	#if (PWM_ATOM7_CH00_ISR_API == STD_ON) || (PWM_ATOM7_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_198 GTM_ATOM7_IRQ0_ISR /* 198 */
    #endif
    #if (PWM_ATOM7_CH02_ISR_API == STD_ON) || (PWM_ATOM7_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_200 GTM_ATOM7_IRQ1_ISR /* 200 */
    #endif
    #if (PWM_ATOM7_CH04_ISR_API == STD_ON) || (PWM_ATOM7_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_202 GTM_ATOM7_IRQ2_ISR /* 202 */
    #endif
    #if (PWM_ATOM7_CH06_ISR_API == STD_ON) || (PWM_ATOM7_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_204 GTM_ATOM7_IRQ3_ISR /* 204 */
    #endif
	#if (PWM_ATOM8_CH00_ISR_API == STD_ON) || (PWM_ATOM8_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_214 GTM_ATOM8_IRQ0_ISR /* 214 */
    #endif
    #if (PWM_ATOM8_CH02_ISR_API == STD_ON) || (PWM_ATOM8_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_216 GTM_ATOM8_IRQ1_ISR /* 216 */
    #endif
    #if (PWM_ATOM8_CH04_ISR_API == STD_ON) || (PWM_ATOM8_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_218 GTM_ATOM8_IRQ2_ISR /* 218 */
    #endif
    #if (PWM_ATOM8_CH06_ISR_API == STD_ON) || (PWM_ATOM8_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_220 GTM_ATOM8_IRQ3_ISR /* 220 */
    #endif
	#if (PWM_ATOM9_CH00_ISR_API == STD_ON) || (PWM_ATOM9_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_254 GTM_ATOM9_IRQ0_ISR /* 254 */
    #endif
    #if (PWM_ATOM9_CH02_ISR_API == STD_ON) || (PWM_ATOM9_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_256 GTM_ATOM9_IRQ1_ISR /* 256 */
    #endif
    #if (PWM_ATOM9_CH04_ISR_API == STD_ON) || (PWM_ATOM9_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_258 GTM_ATOM9_IRQ2_ISR /* 258 */
    #endif
    #if (PWM_ATOM9_CH06_ISR_API == STD_ON) || (PWM_ATOM9_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_260 GTM_ATOM9_IRQ3_ISR /* 260 */
    #endif
	
	#if (PWM_TOM0_CH00_ISR_API == STD_ON) || (PWM_TOM0_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_087 GTM_TOM0_IRQ0_ISR /* 087 */
    #endif
    #if (PWM_TOM0_CH02_ISR_API == STD_ON) || (PWM_TOM0_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_089 GTM_TOM0_IRQ1_ISR /* 089 */
    #endif
    #if (PWM_TOM0_CH04_ISR_API == STD_ON) || (PWM_TOM0_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_091 GTM_TOM0_IRQ2_ISR /* 091 */
    #endif
    #if (PWM_TOM0_CH06_ISR_API == STD_ON) || (PWM_TOM0_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_093 GTM_TOM0_IRQ3_ISR /* 093 */
    #endif
	#if (PWM_TOM0_CH08_ISR_API == STD_ON) || (PWM_TOM0_CH09_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_095 GTM_TOM0_IRQ4_ISR /* 095 */
    #endif
    #if (PWM_TOM0_CH10_ISR_API == STD_ON) || (PWM_TOM0_CH11_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_097 GTM_TOM0_IRQ5_ISR /* 097 */
    #endif
    #if (PWM_TOM0_CH12_ISR_API == STD_ON) || (PWM_TOM0_CH13_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_099 GTM_TOM0_IRQ6_ISR /* 099 */
    #endif
    #if (PWM_TOM0_CH14_ISR_API == STD_ON) || (PWM_TOM0_CH15_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_101 GTM_TOM0_IRQ7_ISR /* 101 */
    #endif
	#if (PWM_TOM1_CH00_ISR_API == STD_ON) || (PWM_TOM1_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_103 GTM_TOM1_IRQ0_ISR /* 103 */
    #endif
    #if (PWM_TOM1_CH02_ISR_API == STD_ON) || (PWM_TOM1_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_105 GTM_TOM1_IRQ1_ISR /* 105 */
    #endif
    #if (PWM_TOM1_CH04_ISR_API == STD_ON) || (PWM_TOM1_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_107 GTM_TOM1_IRQ2_ISR /* 107 */
    #endif
    #if (PWM_TOM1_CH06_ISR_API == STD_ON) || (PWM_TOM1_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_109 GTM_TOM1_IRQ3_ISR /* 109 */
    #endif
	#if (PWM_TOM1_CH08_ISR_API == STD_ON) || (PWM_TOM1_CH09_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_111 GTM_TOM1_IRQ4_ISR /* 111 */
    #endif
    #if (PWM_TOM1_CH10_ISR_API == STD_ON) || (PWM_TOM1_CH11_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_113 GTM_TOM1_IRQ5_ISR /* 113 */
    #endif
    #if (PWM_TOM1_CH12_ISR_API == STD_ON) || (PWM_TOM1_CH13_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_115 GTM_TOM1_IRQ6_ISR /* 115 */
    #endif
    #if (PWM_TOM1_CH14_ISR_API == STD_ON) || (PWM_TOM1_CH15_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_117 GTM_TOM1_IRQ7_ISR /* 117 */
    #endif
	#if (PWM_TOM2_CH00_ISR_API == STD_ON) || (PWM_TOM2_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_119 GTM_TOM2_IRQ0_ISR /* 119 */
    #endif
    #if (PWM_TOM2_CH02_ISR_API == STD_ON) || (PWM_TOM2_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_121 GTM_TOM2_IRQ1_ISR /* 121 */
    #endif
    #if (PWM_TOM2_CH04_ISR_API == STD_ON) || (PWM_TOM2_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_123 GTM_TOM2_IRQ2_ISR /* 123 */
    #endif
    #if (PWM_TOM2_CH06_ISR_API == STD_ON) || (PWM_TOM2_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_125 GTM_TOM2_IRQ3_ISR /* 125 */
    #endif
	#if (PWM_TOM2_CH08_ISR_API == STD_ON) || (PWM_TOM2_CH09_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_127 GTM_TOM2_IRQ4_ISR /* 127 */
    #endif
    #if (PWM_TOM2_CH10_ISR_API == STD_ON) || (PWM_TOM2_CH11_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_129 GTM_TOM2_IRQ5_ISR /* 129 */
    #endif
    #if (PWM_TOM2_CH12_ISR_API == STD_ON) || (PWM_TOM2_CH13_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_131 GTM_TOM2_IRQ6_ISR /* 131 */
    #endif
    #if (PWM_TOM2_CH14_ISR_API == STD_ON) || (PWM_TOM2_CH15_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_133 GTM_TOM2_IRQ7_ISR /* 133 */
    #endif
	#if (PWM_TOM3_CH00_ISR_API == STD_ON) || (PWM_TOM3_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_135 GTM_TOM3_IRQ0_ISR /* 135 */
    #endif
    #if (PWM_TOM3_CH02_ISR_API == STD_ON) || (PWM_TOM3_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_137 GTM_TOM3_IRQ1_ISR /* 137 */
    #endif
    #if (PWM_TOM3_CH04_ISR_API == STD_ON) || (PWM_TOM3_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_139 GTM_TOM3_IRQ2_ISR /* 139 */
    #endif
    #if (PWM_TOM3_CH06_ISR_API == STD_ON) || (PWM_TOM3_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_141 GTM_TOM3_IRQ3_ISR /* 141 */
    #endif
	#if (PWM_TOM3_CH08_ISR_API == STD_ON) || (PWM_TOM3_CH09_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_143 GTM_TOM3_IRQ4_ISR /* 143 */
    #endif
    #if (PWM_TOM3_CH10_ISR_API == STD_ON) || (PWM_TOM3_CH11_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_145 GTM_TOM3_IRQ5_ISR /* 145 */
    #endif
    #if (PWM_TOM3_CH12_ISR_API == STD_ON) || (PWM_TOM3_CH13_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_147 GTM_TOM3_IRQ6_ISR /* 147 */
    #endif
    #if (PWM_TOM3_CH14_ISR_API == STD_ON) || (PWM_TOM3_CH15_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_149 GTM_TOM3_IRQ7_ISR /* 149 */
    #endif
	#if (PWM_TOM4_CH00_ISR_API == STD_ON) || (PWM_TOM4_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_151 GTM_TOM4_IRQ0_ISR /* 151 */
    #endif
    #if (PWM_TOM4_CH02_ISR_API == STD_ON) || (PWM_TOM4_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_153 GTM_TOM4_IRQ1_ISR /* 153 */
    #endif
    #if (PWM_TOM4_CH04_ISR_API == STD_ON) || (PWM_TOM4_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_155 GTM_TOM4_IRQ2_ISR /* 155 */
    #endif
    #if (PWM_TOM4_CH06_ISR_API == STD_ON) || (PWM_TOM4_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_157 GTM_TOM4_IRQ3_ISR /* 157 */
    #endif
	#if (PWM_TOM4_CH08_ISR_API == STD_ON) || (PWM_TOM4_CH09_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_159 GTM_TOM4_IRQ4_ISR /* 159 */
    #endif
    #if (PWM_TOM4_CH10_ISR_API == STD_ON) || (PWM_TOM4_CH11_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_161 GTM_TOM4_IRQ5_ISR /* 161 */
    #endif
    #if (PWM_TOM4_CH12_ISR_API == STD_ON) || (PWM_TOM4_CH13_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_163 GTM_TOM4_IRQ6_ISR /* 163 */
    #endif
    #if (PWM_TOM4_CH14_ISR_API == STD_ON) || (PWM_TOM4_CH15_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_165 GTM_TOM4_IRQ7_ISR /* 165 */
    #endif
  #endif  /* PWM_GTM_UNIT_USED == STD_ON  */
  #endif /*CATEGORY_2*/
#endif  /* PWM_MODULE_SAMPLE */

#ifdef PWM_MODULE_SAMPLE
#if (PWM_ISR_CATEGORY_2 == STD_ON)
#else
/* Defines the CAT1 interrupt mapping */
	#ifdef PWM_SAMPLEAPP_OSTM                  /* Use OSTM0 interrupt for task timing */
    #define INT_VECTOR_PE0_360 Timer0_Interrupt /* 360 */
    #endif
  #if (PWM_TAUD_UNIT_USED == STD_ON)
    #if (PWM_TAUD0_CH00_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_010  TAUD0_CH00_ISR
    #endif
    #if (PWM_TAUD0_CH01_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_320  TAUD0_CH01_ISR
    #endif
    #if (PWM_TAUD0_CH02_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_011  TAUD0_CH02_ISR
    #endif
    #if (PWM_TAUD0_CH03_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_321  TAUD0_CH03_ISR
    #endif
    #if (PWM_TAUD0_CH04_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_012  TAUD0_CH04_ISR
    #endif
    #if (PWM_TAUD0_CH05_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_322  TAUD0_CH05_ISR
    #endif
    #if (PWM_TAUD0_CH06_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_013  TAUD0_CH06_ISR
    #endif
    #if (PWM_TAUD0_CH07_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_323  TAUD0_CH07_ISR
    #endif
    #if (PWM_TAUD0_CH08_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_023  TAUD0_CH08_ISR
    #endif
    #if (PWM_TAUD0_CH09_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_324  TAUD0_CH09_ISR
    #endif
    #if (PWM_TAUD0_CH10_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_024  TAUD0_CH10_ISR
    #endif
    #if (PWM_TAUD0_CH11_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_325  TAUD0_CH11_ISR
    #endif
    #if (PWM_TAUD0_CH12_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_025  TAUD0_CH12_ISR
    #endif
    #if (PWM_TAUD0_CH13_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_326  TAUD0_CH13_ISR
    #endif
    #if (PWM_TAUD0_CH14_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_026  TAUD0_CH14_ISR
    #endif
    #if (PWM_TAUD0_CH15_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_327  TAUD0_CH15_ISR
    #endif
    #if (PWM_TAUD1_CH00_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_328  TAUD1_CH00_ISR
    #endif
    #if (PWM_TAUD1_CH01_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_329  TAUD1_CH01_ISR
    #endif
    #if (PWM_TAUD1_CH02_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_330  TAUD1_CH02_ISR
    #endif
    #if (PWM_TAUD1_CH03_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_331  TAUD1_CH03_ISR
    #endif
    #if (PWM_TAUD1_CH04_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_332  TAUD1_CH04_ISR
    #endif
    #if (PWM_TAUD1_CH05_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_333  TAUD1_CH05_ISR
    #endif
    #if (PWM_TAUD1_CH06_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_334  TAUD1_CH06_ISR
    #endif
    #if (PWM_TAUD1_CH07_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_335  TAUD1_CH07_ISR
    #endif
    #if (PWM_TAUD1_CH08_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_336  TAUD1_CH08_ISR
    #endif
    #if (PWM_TAUD1_CH09_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_337  TAUD1_CH09_ISR
    #endif
    #if (PWM_TAUD1_CH10_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_338  TAUD1_CH10_ISR
    #endif
    #if (PWM_TAUD1_CH11_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_339  TAUD1_CH11_ISR
    #endif
    #if (PWM_TAUD1_CH12_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_340  TAUD1_CH12_ISR
    #endif
    #if (PWM_TAUD1_CH13_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_341  TAUD1_CH13_ISR
    #endif
    #if (PWM_TAUD1_CH14_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_342  TAUD1_CH14_ISR
    #endif
    #if (PWM_TAUD1_CH15_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_343  TAUD1_CH15_ISR
    #endif
    #if (PWM_TAUD2_CH00_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_344  TAUD2_CH00_ISR
    #endif
    #if (PWM_TAUD2_CH01_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_345  TAUD2_CH01_ISR
    #endif
    #if (PWM_TAUD2_CH02_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_346  TAUD2_CH02_ISR
    #endif
    #if (PWM_TAUD2_CH03_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_347  TAUD2_CH03_ISR
    #endif
    #if (PWM_TAUD2_CH04_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_348  TAUD2_CH04_ISR
    #endif
    #if (PWM_TAUD2_CH05_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_349  TAUD2_CH05_ISR
    #endif
    #if (PWM_TAUD2_CH06_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_350  TAUD2_CH06_ISR
    #endif
    #if (PWM_TAUD2_CH07_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_351  TAUD2_CH07_ISR
    #endif
    #if (PWM_TAUD2_CH08_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_352  TAUD2_CH08_ISR
    #endif
    #if (PWM_TAUD2_CH09_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_353  TAUD2_CH09_ISR
    #endif
    #if (PWM_TAUD2_CH10_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_354  TAUD2_CH10_ISR
    #endif
    #if (PWM_TAUD2_CH11_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_355  TAUD2_CH11_ISR
    #endif
    #if (PWM_TAUD2_CH12_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_356  TAUD2_CH12_ISR
    #endif
    #if (PWM_TAUD2_CH13_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_357  TAUD2_CH13_ISR
    #endif
    #if (PWM_TAUD2_CH14_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_358  TAUD2_CH14_ISR
    #endif
    #if (PWM_TAUD2_CH15_ISR_API == STD_ON)  
    #define INT_VECTOR_PE0_359  TAUD2_CH15_ISR
    #endif /* (PWM_TAUD_UNIT_USED == STD_ON) */
    
    
    #if (PWM_TAUD3_CH00_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_379 TAUD3_CH00_ISR /* 379 */
    #define INT_VECTOR_PE0_505 TAUD3_CH00_ISR /* 505 */
    #define INT_VECTOR_PE0_793 TAUD3_CH00_ISR /* 793 */
    #endif
    #if (PWM_TAUD3_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_380 TAUD3_CH01_ISR /* 380 */
    #define INT_VECTOR_PE0_506 TAUD3_CH01_ISR /* 506 */
    #define INT_VECTOR_PE0_794 TAUD3_CH01_ISR /* 794 */
    #endif
    #if (PWM_TAUD3_CH02_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_381 TAUD3_CH02_ISR /* 381 */
    #define INT_VECTOR_PE0_507 TAUD3_CH02_ISR /* 507 */
    #define INT_VECTOR_PE0_795 TAUD3_CH02_ISR /* 795 */
    #endif
    #if (PWM_TAUD3_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_382 TAUD3_CH03_ISR /* 382 */
    #define INT_VECTOR_PE0_508 TAUD3_CH03_ISR /* 508 */
    #define INT_VECTOR_PE0_796 TAUD3_CH03_ISR /* 796 */
    #endif
    #if (PWM_TAUD3_CH04_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_383 TAUD3_CH04_ISR /* 383 */
    #define INT_VECTOR_PE0_509 TAUD3_CH04_ISR /* 509 */
    #define INT_VECTOR_PE0_797 TAUD3_CH04_ISR /* 797 */
    #endif
    #if (PWM_TAUD3_CH05_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_384 TAUD3_CH05_ISR /* 384 */
    #define INT_VECTOR_PE0_510 TAUD3_CH05_ISR /* 510 */
    #define INT_VECTOR_PE0_798 TAUD3_CH05_ISR /* 798 */
    #endif
    #if (PWM_TAUD3_CH06_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_385 TAUD3_CH06_ISR /* 385 */
    #define INT_VECTOR_PE0_511 TAUD3_CH06_ISR /* 511 */
    #define INT_VECTOR_PE0_799 TAUD3_CH06_ISR /* 799 */
    #endif
    #if (PWM_TAUD3_CH07_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_386 TAUD3_CH07_ISR /* 386 */
    #define INT_VECTOR_PE0_512 TAUD3_CH07_ISR /* 512 */
    #define INT_VECTOR_PE0_800 TAUD3_CH07_ISR /* 800 */
    #endif
    #if (PWM_TAUD3_CH08_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_387 TAUD3_CH08_ISR /* 387 */
    #define INT_VECTOR_PE0_513 TAUD3_CH08_ISR /* 513 */
    #define INT_VECTOR_PE0_801 TAUD3_CH08_ISR /* 801 */
    #endif
    #if (PWM_TAUD3_CH09_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_388 TAUD3_CH09_ISR /* 388 */
    #define INT_VECTOR_PE0_514 TAUD3_CH09_ISR /* 514 */
    #define INT_VECTOR_PE0_802 TAUD3_CH09_ISR /* 802 */
    #endif
    #if (PWM_TAUD3_CH10_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_389 TAUD3_CH10_ISR /* 389 */
    #define INT_VECTOR_PE0_515 TAUD3_CH10_ISR /* 515 */
    #define INT_VECTOR_PE0_803 TAUD3_CH10_ISR /* 803 */
    #endif
    #if (PWM_TAUD3_CH11_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_390 TAUD3_CH11_ISR /* 390 */
    #define INT_VECTOR_PE0_516 TAUD3_CH11_ISR /* 516 */
    #define INT_VECTOR_PE0_804 TAUD3_CH11_ISR /* 804 */
    #endif
    #if (PWM_TAUD3_CH12_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_391 TAUD3_CH12_ISR /* 391 */
    #define INT_VECTOR_PE0_517 TAUD3_CH12_ISR /* 517 */
    #define INT_VECTOR_PE0_817 TAUD3_CH12_ISR /* 817 */
    #endif
    #if (PWM_TAUD3_CH13_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_392 TAUD3_CH13_ISR /* 392 */
    #define INT_VECTOR_PE0_518 TAUD3_CH13_ISR /* 518 */
    #define INT_VECTOR_PE0_818 TAUD3_CH13_ISR /* 818 */
    #endif
    #if (PWM_TAUD3_CH14_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_393 TAUD3_CH14_ISR /* 393 */
    #define INT_VECTOR_PE0_519 TAUD3_CH14_ISR /* 519 */
    #define INT_VECTOR_PE0_819 TAUD3_CH14_ISR /* 819 */
    #endif
    #if (PWM_TAUD3_CH15_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_394 TAUD3_CH15_ISR /* 394 */
    #define INT_VECTOR_PE0_520 TAUD3_CH15_ISR /* 520 */
    #define INT_VECTOR_PE0_820 TAUD3_CH15_ISR /* 820 */
    #endif
    
    
  #endif
  #endif
#endif

#ifdef PWM_MODULE_SAMPLE
  #if (PWM_ISR_CATEGORY_2 == STD_ON)
  #else      
  #if (PWM_TAUJ_UNIT_USED == STD_ON)
    #if (PWM_TAUJ2_CH00_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_960  TAUJ2_CH00_ISR
    #endif
    #if (PWM_TAUJ2_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_961  TAUJ2_CH01_ISR
    #endif
    #if (PWM_TAUJ2_CH02_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_962  TAUJ2_CH02_ISR
    #endif
    #if (PWM_TAUJ2_CH03_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_963  TAUJ2_CH03_ISR
    #endif
  #endif /* (PWM_TAUJ_UNIT_USED == STD_ON) */
  #endif /*CATEGORY_2*/
  #endif  /* PWM_MODULE_SAMPLE */

#ifdef CAN_MODULE_SAMPLE
#if (CAN_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#define INT_VECTOR_PE0_010 Timer_Task /* 010 */
#if (CAN_RSCAN0_RXFIFO_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_653 CAN_RSCAN0_RXFIFO_ISR /* 653 */
#endif
#if (CAN_RSCAN1_RXFIFO_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_655 CAN_RSCAN1_RXFIFO_ISR /* 655 */
#endif
#if (CAN_RSCAN2_RXFIFO_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_657 CAN_RSCAN2_RXFIFO_ISR /* 657 */
#endif
#if (CAN_CONTROLLER0_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_658 CAN_CONTROLLER0_ERROR_ISR /* 658 */
#endif
#if (CAN_CONTROLLER0_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_659 CAN_CONTROLLER0_RX_ISR /* 659 */
#endif
#if (CAN_CONTROLLER0_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_660 CAN_CONTROLLER0_TX_ISR /* 660 */
#endif
#if (CAN_CONTROLLER1_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_664 CAN_CONTROLLER1_ERROR_ISR /* 664 */
#endif
#if (CAN_CONTROLLER1_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_665 CAN_CONTROLLER1_RX_ISR /* 665 */
#endif
#if (CAN_CONTROLLER1_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_666 CAN_CONTROLLER1_TX_ISR /* 666 */
#endif
#if (CAN_CONTROLLER2_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_670 CAN_CONTROLLER2_ERROR_ISR /* 670 */
#endif
#if (CAN_CONTROLLER2_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_671 CAN_CONTROLLER2_RX_ISR /* 671 */
#endif
#if (CAN_CONTROLLER2_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_672 CAN_CONTROLLER2_TX_ISR /* 672 */
#endif
#if (CAN_CONTROLLER3_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_676 CAN_CONTROLLER3_ERROR_ISR /* 676 */
#endif
#if (CAN_CONTROLLER3_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_677 CAN_CONTROLLER3_RX_ISR /* 677 */
#endif
#if (CAN_CONTROLLER3_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_678 CAN_CONTROLLER3_TX_ISR /* 678 */
#endif
#if (CAN_CONTROLLER4_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_682 CAN_CONTROLLER4_ERROR_ISR /* 682 */
#endif
#if (CAN_CONTROLLER4_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_683 CAN_CONTROLLER4_RX_ISR /* 683 */
#endif
#if (CAN_CONTROLLER4_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_684 CAN_CONTROLLER4_TX_ISR /* 684 */
#endif
#if (CAN_CONTROLLER5_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_688 CAN_CONTROLLER5_ERROR_ISR /* 688 */
#endif
#if (CAN_CONTROLLER5_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_689 CAN_CONTROLLER5_RX_ISR /* 689 */
#endif
#if (CAN_CONTROLLER5_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_690 CAN_CONTROLLER5_TX_ISR /* 690 */
#endif
#if (CAN_CONTROLLER6_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_694 CAN_CONTROLLER6_ERROR_ISR /* 694 */
#endif
#if (CAN_CONTROLLER6_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_695 CAN_CONTROLLER6_RX_ISR /* 695 */
#endif
#if (CAN_CONTROLLER6_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_696 CAN_CONTROLLER6_TX_ISR /* 696 */
#endif
#if (CAN_CONTROLLER7_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_700 CAN_CONTROLLER7_ERROR_ISR /* 700 */
#endif
#if (CAN_CONTROLLER7_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_701 CAN_CONTROLLER7_RX_ISR /* 701 */
#endif
#if (CAN_CONTROLLER7_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_702 CAN_CONTROLLER7_TX_ISR /* 702 */
#endif
#if (CAN_CONTROLLER8_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_1005 CAN_CONTROLLER8_ERROR_ISR /* 1005 */
#endif
#if (CAN_CONTROLLER8_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_1006 CAN_CONTROLLER8_RX_ISR /* 1006 */
#endif
#if (CAN_CONTROLLER8_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_1007 CAN_CONTROLLER8_TX_ISR /* 1007 */
#endif
#if (CAN_CONTROLLER9_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_1011 CAN_CONTROLLER9_ERROR_ISR /* 1011 */
#endif
#if (CAN_CONTROLLER9_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_1012 CAN_CONTROLLER9_RX_ISR /* 1012 */
#endif
#if (CAN_CONTROLLER9_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_1013 CAN_CONTROLLER9_TX_ISR /* 1013 */
#endif
#if (CAN_CONTROLLER10_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_576 CAN_CONTROLLER10_ERROR_ISR /* 576 */
#endif
#if (CAN_CONTROLLER10_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_577 CAN_CONTROLLER10_RX_ISR /* 577 */
#endif
#if (CAN_CONTROLLER10_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_578 CAN_CONTROLLER10_TX_ISR /* 578 */
#endif
#if (CAN_CONTROLLER11_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_582 CAN_CONTROLLER11_ERROR_ISR /* 582 */
#endif
#if (CAN_CONTROLLER11_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_583 CAN_CONTROLLER11_RX_ISR /* 583 */
#endif
#if (CAN_CONTROLLER11_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_584 CAN_CONTROLLER11_TX_ISR /* 584 */
#endif
#if (CAN_CONTROLLER12_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_588 CAN_CONTROLLER12_ERROR_ISR /* 588*/
#endif
#if (CAN_CONTROLLER12_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_589 CAN_CONTROLLER12_RX_ISR /* 589 */
#endif
#if (CAN_CONTROLLER12_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_590 CAN_CONTROLLER12_TX_ISR /* 590 */
#endif
#if (CAN_CONTROLLER13_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_594 CAN_CONTROLLER13_ERROR_ISR /* 594 */
#endif
#if (CAN_CONTROLLER13_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_595 CAN_CONTROLLER13_RX_ISR /* 595 */
#endif
#if (CAN_CONTROLLER13_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_596 CAN_CONTROLLER13_TX_ISR /* 596 */
#endif
#if (CAN_CONTROLLER14_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_600 CAN_CONTROLLER14_ERROR_ISR /* 600 */
#endif
#if (CAN_CONTROLLER14_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_601 CAN_CONTROLLER14_RX_ISR /* 601 */
#endif
#if (CAN_CONTROLLER14_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_602 CAN_CONTROLLER14_TX_ISR /* 602 */
#endif
#if (CAN_CONTROLLER15_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_606 CAN_CONTROLLER15_ERROR_ISR /* 606 */
#endif
#if (CAN_CONTROLLER15_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_607 CAN_CONTROLLER15_RX_ISR /* 607 */
#endif
#if (CAN_CONTROLLER15_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_608 CAN_CONTROLLER15_TX_ISR /* 608 */
#endif
#if (CAN_CONTROLLER16_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_612 CAN_CONTROLLER16_ERROR_ISR /* 612 */
#endif
#if (CAN_CONTROLLER16_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_613 CAN_CONTROLLER16_RX_ISR /* 613 */
#endif
#if (CAN_CONTROLLER16_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_614 CAN_CONTROLLER16_TX_ISR /* 614 */
#endif
#if (CAN_CONTROLLER17_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_722 CAN_CONTROLLER17_ERROR_ISR /* 722 */
#endif
#if (CAN_CONTROLLER17_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_723 CAN_CONTROLLER17_RX_ISR /* 723 */
#endif
#if (CAN_CONTROLLER17_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_724 CAN_CONTROLLER17_TX_ISR /* 724 */
#endif
#if (CAN_CONTROLLER18_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_851 CAN_CONTROLLER18_ERROR_ISR /* 851 */
#endif
#if (CAN_CONTROLLER18_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_852 CAN_CONTROLLER18_RX_ISR /* 852 */
#endif
#if (CAN_CONTROLLER18_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_853 CAN_CONTROLLER18_TX_ISR /* 853 */
#endif
#if (CAN_CONTROLLER19_ERROR_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_863 CAN_CONTROLLER19_ERROR_ISR /* 863 */
#endif
#if (CAN_CONTROLLER19_RX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_864 CAN_CONTROLLER19_RX_ISR /* 864 */
#endif
#if (CAN_CONTROLLER19_TX_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_865 CAN_CONTROLLER19_TX_ISR /* 865 */
#endif

#if (CAN_WAKEUP_SUPPORT == STD_ON)
#if (CAN_CONTROLLER0_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_765 CAN_CONTROLLER0_WAKEUP_ISR /* 765 */
#endif
#if (CAN_CONTROLLER1_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_766 CAN_CONTROLLER1_WAKEUP_ISR /* 766 */
#endif
#if (CAN_CONTROLLER2_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_767 CAN_CONTROLLER2_WAKEUP_ISR /* 767 */
#endif
#if (CAN_CONTROLLER3_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_768 CAN_CONTROLLER3_WAKEUP_ISR /* 768 */
#endif
#if (CAN_CONTROLLER4_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_769 CAN_CONTROLLER4_WAKEUP_ISR /* 769 */
#endif
#if (CAN_CONTROLLER5_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_770 CAN_CONTROLLER5_WAKEUP_ISR /* 770 */
#endif
#if (CAN_CONTROLLER6_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_771 CAN_CONTROLLER6_WAKEUP_ISR /* 771 */
#endif
#if (CAN_CONTROLLER7_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_772 CAN_CONTROLLER7_WAKEUP_ISR /* 772 */
#endif
#if (CAN_CONTROLLER8_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_773 CAN_CONTROLLER8_WAKEUP_ISR /* 773 */
#endif
#if (CAN_CONTROLLER9_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_774 CAN_CONTROLLER9_WAKEUP_ISR /* 774 */
#endif
#if (CAN_CONTROLLER10_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_775 CAN_CONTROLLER10_WAKEUP_ISR /* 775 */
#endif
#if (CAN_CONTROLLER11_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_776 CAN_CONTROLLER11_WAKEUP_ISR /* 776 */
#endif
#if (CAN_CONTROLLER12_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_777 CAN_CONTROLLER12_WAKEUP_ISR /* 777 */
#endif
#if (CAN_CONTROLLER13_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_778 CAN_CONTROLLER13_WAKEUP_ISR /* 778 */
#endif
#if (CAN_CONTROLLER14_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_779 CAN_CONTROLLER14_WAKEUP_ISR /* 779 */
#endif
#if (CAN_CONTROLLER15_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_780 CAN_CONTROLLER15_WAKEUP_ISR /* 780 */
#endif
#if (CAN_CONTROLLER16_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_781 CAN_CONTROLLER16_WAKEUP_ISR /* 781 */
#endif
#if (CAN_CONTROLLER17_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_782 CAN_CONTROLLER17_WAKEUP_ISR /* 782 */
#endif
#if (CAN_CONTROLLER18_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_783 CAN_CONTROLLER18_WAKEUP_ISR /* 783 */
#endif
#if (CAN_CONTROLLER19_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_784 CAN_CONTROLLER19_WAKEUP_ISR /* 784 */
#endif
#endif  /* (CAN_WAKEUP_SUPPORT == STD_ON) */

#if (CAN_CANXL_SUPPORTED == STD_ON)

#if (CAN_CANXL_CONTROLLER0_FUNC_ISR == STD_ON)
#define INT_VECTOR_PE0_1017 CANXL_CONTROLLER0_FUNC_ISR /* 1017 */
#endif

#if (CAN_CANXL_CONTROLLER1_FUNC_ISR == STD_ON)
#define INT_VECTOR_PE0_1020 CANXL_CONTROLLER1_FUNC_ISR /* 1020 */
#endif

#if (CAN_CANXL_CONTROLLER0_ERROR_ISR == STD_ON)
#define INT_VECTOR_PE0_1018 CANXL_CONTROLLER0_ERR_ISR /* 1018 */
#endif

#if (CAN_CANXL_CONTROLLER1_ERROR_ISR == STD_ON)
#define INT_VECTOR_PE0_1021 CANXL_CONTROLLER1_ERR_ISR /* 1021 */
#endif

#if (CAN_WAKEUP_SUPPORT == STD_ON)
#if (CANXL_CONTROLLER0_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_36 CANXL_CONTROLLER0_WAKEUP_ISR /* 218 */
#endif
#if (CANXL_CONTROLLER1_WAKEUP_INTERRUPT == STD_ON)
#define INT_VECTOR_PE0_1023 CANXL_CONTROLLER1_WAKEUP_ISR /* 219 */
#endif
#endif

#endif

#endif  /* (CAN_ISR_CATEGORY_2 == STD_ON) */
#endif  /* CAN_MODULE_SAMPLE */

#ifdef ETH_MODULE_SAMPLE
#if (ETH_MACRO_ETNE == STD_ON)
/* TSN R-Switch */

#if (ETH_GWCA0_DATA_ISR == STD_ON)
#if (ETH_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#define INT_VECTOR_PE0_708 ETH_GWCA0DISISR    /* 708 */
#endif
#endif

#if (ETH_GWCA0_TSDATA_ISR == STD_ON)
#if (ETH_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#define INT_VECTOR_PE0_709 ETH_GWCA0TSDISISR  /* 709 */
#endif
#endif

#if (ETH_GWCA0_ERR_ISR == STD_ON)
#if (ETH_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#define INT_VECTOR_PE0_710 ETH_GWCA0ERRISR    /* 711 */
#endif
#endif

#if (ETH_COMA_ERR_ISR == STD_ON)
#if (ETH_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#define INT_VECTOR_PE0_711 ETH_COMAERRISR     /* 712 */
#endif
#endif

#if (ETH_ETHA0_ERR_ISR == STD_ON)
#if (ETH_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#define INT_VECTOR_PE0_712 ETH_ETHA0ERRISR    /* 713 */
#endif
#endif

#if ((ETH_ETHA1_ERR_ISR == STD_ON))
#if (ETH_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#define INT_VECTOR_PE0_713 ETH_ETHA1ERRISR    /* 714 */
#endif
#endif

#if (ETH_SGMII_ISR == STD_ON)
#if defined (ETH_PORT0)
#if (ETH_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#define INT_VECTOR_PE0_714 ETH_ETHA0SGMIIISR    /* 715 */
#endif
#endif

#if defined (ETH_PORT1)
#if (ETH_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#define INT_VECTOR_PE0_715 ETH_ETHA1SGMIIISR    /* 716 */
#endif
#endif
#endif
#endif /*end of if (ETH_MACRO_ETNE == STD_ON) */

#if (ETH_MACRO_ETNF == STD_ON)
/* AVB T1s */
/* AVB interrupt mapping */ 
#if (ETH_AVB0_DATA_ISR == STD_ON)
#if (ETH_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#define INT_VECTOR_PE0_964 ETH_AVB0DATAISR     /* 964 */
#endif
#endif

#if (ETH_AVB0_ERR_ISR == STD_ON)
#if (ETH_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#define INT_VECTOR_PE0_965 ETH_AVB0ERRISR      /* 965 */
#endif
#endif

#if (ETH_AVB0_MNG_ISR == STD_ON)
#if (ETH_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
#define INT_VECTOR_PE0_966 ETH_AVB0MNGISR      /* 966 */
#endif
#endif
#endif /*end of if (ETH_MACRO_ETNF == STD_ON) */
#endif /*end of ifdef ETH_MODULE_SAMPLE */

#ifdef FR_MODULE_SAMPLE
#define INT_VECTOR_PE0_724 INTFLX0TIM0 /* 724 */
#define INT_VECTOR_PE0_726 INTFLX0TIM2 /* 726 */

#define INT_VECTOR_PE0_921 INTFLX1TIM0 /* 921 */
#define INT_VECTOR_PE0_932 INTFLX1TIM0 /* 932 */

#define INT_VECTOR_PE0_923 INTFLX1TIM2 /* 923 */
#define INT_VECTOR_PE0_934 INTFLX1TIM2 /* 934 */

#endif

#ifdef OCU_MODULE_SAMPLE
#if (OCU_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
/* Defines the CAT1 interrupt mapping */
#ifdef OCU_SAMPLEAPP_OSTM                  /* Use OSTM0 interrupt for task timing */
extern void Timer0_Interrupt(void);
#define INT_VECTOR_PE0_360 Timer0_Interrupt /* 360 */
#endif
#if (OCU_TAUD0_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_320 TAUD0_CH01_ISR /* 320 */
#endif
#if (OCU_TAUD0_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_321 TAUD0_CH03_ISR /* 321 */
#endif
#if (OCU_TAUD0_CH05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_322 TAUD0_CH05_ISR /* 322 */
#endif
#if (OCU_TAUD0_CH07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_323 TAUD0_CH07_ISR /* 323 */
#endif
#if (OCU_TAUD0_CH09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_324 TAUD0_CH09_ISR /* 324 */
#endif
#if (OCU_TAUD0_CH11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_325 TAUD0_CH11_ISR /* 325 */
#endif
#if (OCU_TAUD0_CH13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_326 TAUD0_CH13_ISR /* 326 */
#endif
#if (OCU_TAUD0_CH15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_327 TAUD0_CH15_ISR /* 327 */
#endif
#if (OCU_TAUD1_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_329 TAUD1_CH01_ISR /* 329 */
#endif
#if (OCU_TAUD1_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_331 TAUD1_CH03_ISR /* 331 */
#endif
#if (OCU_TAUD1_CH05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_333 TAUD1_CH05_ISR /* 333 */
#endif
#if (OCU_TAUD1_CH07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_335 TAUD1_CH07_ISR /* 335 */
#endif
#if (OCU_TAUD1_CH09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_337 TAUD1_CH09_ISR /* 337 */
#endif
#if (OCU_TAUD1_CH11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_339 TAUD1_CH11_ISR /* 339 */
#endif
#if (OCU_TAUD1_CH13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_341 TAUD1_CH13_ISR /* 341 */
#endif
#if (OCU_TAUD1_CH15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_343 TAUD1_CH15_ISR /* 343 */
#endif
#if (OCU_TAUD2_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_345 TAUD2_CH01_ISR /* 345 */
#endif
#if (OCU_TAUD2_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_347 TAUD2_CH03_ISR /* 347 */
#endif
#if (OCU_TAUD2_CH05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_349 TAUD2_CH05_ISR /* 349 */
#endif
#if (OCU_TAUD2_CH07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_351 TAUD2_CH07_ISR /* 351 */
#endif
#if (OCU_TAUD2_CH09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_353 TAUD2_CH09_ISR /* 353 */
#endif
#if (OCU_TAUD2_CH11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_355 TAUD2_CH11_ISR /* 355 */
#endif
#if (OCU_TAUD2_CH13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_357 TAUD2_CH13_ISR /* 357 */
#endif
#if (OCU_TAUD2_CH15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_359 TAUD2_CH15_ISR /* 359 */
#endif
#if (OCU_TAUD3_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_506 TAUD3_CH01_ISR /* 506 */
#define INT_VECTOR_PE0_380 TAUD3_CH01_ISR /* 380 */
#define INT_VECTOR_PE0_794 TAUD3_CH01_ISR /* 794 */
#endif
#if (OCU_TAUD3_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_508 TAUD3_CH03_ISR /* 508 */
#define INT_VECTOR_PE0_382 TAUD3_CH03_ISR /* 382 */
#define INT_VECTOR_PE0_796 TAUD3_CH03_ISR /* 796 */
#endif
#if (OCU_TAUD3_CH05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_510 TAUD3_CH05_ISR /* 510 */
#define INT_VECTOR_PE0_384 TAUD3_CH05_ISR /* 384 */
#define INT_VECTOR_PE0_798 TAUD3_CH05_ISR /* 798 */
#endif
#if (OCU_TAUD3_CH07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_512 TAUD3_CH07_ISR /* 512 */
#define INT_VECTOR_PE0_386 TAUD3_CH07_ISR /* 386 */
#define INT_VECTOR_PE0_800 TAUD3_CH07_ISR /* 800 */
#endif
#if (OCU_TAUD3_CH09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_514 TAUD3_CH09_ISR /* 514 */
#define INT_VECTOR_PE0_388 TAUD3_CH09_ISR /* 388 */
#define INT_VECTOR_PE0_802 TAUD3_CH09_ISR /* 802 */
#endif
#if (OCU_TAUD3_CH11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_516 TAUD3_CH11_ISR /* 516 */
#define INT_VECTOR_PE0_390 TAUD3_CH11_ISR /* 390 */
#define INT_VECTOR_PE0_804 TAUD3_CH11_ISR /* 804 */
#endif
#if (OCU_TAUD3_CH13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_518 TAUD3_CH13_ISR /* 518 */
#define INT_VECTOR_PE0_392 TAUD3_CH13_ISR /* 392 */
#define INT_VECTOR_PE0_818 TAUD3_CH13_ISR /* 818 */
#endif
#if (OCU_TAUD3_CH15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_520 TAUD3_CH15_ISR /* 520 */
#define INT_VECTOR_PE0_394 TAUD3_CH15_ISR /* 394 */
#define INT_VECTOR_PE0_820 TAUD3_CH15_ISR /* 820 */
#endif
#if (OCU_TAUJ2_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_961 TAUJ2_CH01_ISR /* 961 */
#endif
#if (OCU_TAUJ2_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_963 TAUJ2_CH03_ISR /* 963 */
#endif
#if (OCU_TAUJ3_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_965 TAUJ3_CH01_ISR /* 965 */
#endif
#if (OCU_TAUJ3_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_967 TAUJ3_CH03_ISR /* 967 */
#endif

#endif  /* OCU_ISR_CATEGORY_2 */
#endif  /* OCU_MODULE_SAMPLE */

#ifdef OCU_MODULE_SAMPLE
  #if (OCU_ISR_CATEGORY_2 == STD_ON)
  #else      
  #if (OCU_TIMER_IP_GTM == STD_ON)
    #if (OCU_ATOM0_CH00_ISR_API == STD_ON) || (OCU_ATOM0_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_086 GTM_ATOM0_IRQ0_ISR /* 086 */
    #endif
    #if (OCU_TOM0_CH00_ISR_API == STD_ON) || (OCU_TOM0_CH01_ISR_API == STD_ON)
    #define INT_VECTOR_PE0_087 GTM_TOM0_IRQ0_ISR /* 087 */
    #endif
  #endif  /* OCU_TIMER_IP_GTM == STD_ON  */
  #endif /*CATEGORY_2*/
#endif  /* OCU_MODULE_SAMPLE */


#ifdef GPT_MODULE_SAMPLE
#if (GPT_ISR_CATEGORY_2 == STD_ON)
/* Defines the CAT2 interrupt mapping */
#else
/* Defines the CAT1 interrupt mapping */
#if (GPT_TAUD0_CH00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_010 TAUD0_CH00_ISR /* 010 */
#endif
#if (GPT_TAUD0_CH02_ISR_API == STD_ON)
#define INT_VECTOR_PE0_011 TAUD0_CH02_ISR /* 011 */
#endif
#if (GPT_TAUD0_CH04_ISR_API == STD_ON)
#define INT_VECTOR_PE0_012 TAUD0_CH04_ISR /* 012 */
#endif
#if (GPT_TAUD0_CH06_ISR_API == STD_ON)
#define INT_VECTOR_PE0_013 TAUD0_CH06_ISR /* 013 */
#endif
#if (GPT_TAUD0_CH08_ISR_API == STD_ON)
#define INT_VECTOR_PE0_023 TAUD0_CH08_ISR /* 023 */
#endif
#if (GPT_TAUD0_CH10_ISR_API == STD_ON)
#define INT_VECTOR_PE0_024 TAUD0_CH10_ISR /* 024 */
#endif
#if (GPT_TAUD0_CH12_ISR_API == STD_ON)
#define INT_VECTOR_PE0_025 TAUD0_CH12_ISR /* 025 */
#endif
#if (GPT_TAUD0_CH14_ISR_API == STD_ON)
#define INT_VECTOR_PE0_026 TAUD0_CH14_ISR /* 026 */
#endif
#if (GPT_OSTM00_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_360 OSTM00_CH0_ISR /* 360 */
#endif
#if (GPT_OSTM01_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_361 OSTM01_CH0_ISR /* 361 */
#endif
#if (GPT_OSTM02_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_841 OSTM02_CH0_ISR /* 841 */
#endif
#if (GPT_OSTM03_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_842 OSTM03_CH0_ISR /* 842 */
#endif
#if (GPT_OSTM04_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_968 OSTM04_CH0_ISR /* 968 */
#endif
#if (GPT_OSTM05_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_969 OSTM05_CH0_ISR /* 969 */
#endif
#if (GPT_OSTM06_CH0_ISR_API == STD_ON)
#define INT_VECTOR_PE0_396 OSTM06_CH0_ISR /* 396 */
#endif
#if (GPT_TAUD0_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_320 TAUD0_CH01_ISR /* 320 */
#endif
#if (GPT_TAUD0_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_321 TAUD0_CH03_ISR /* 321 */
#endif
#if (GPT_TAUD0_CH05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_322 TAUD0_CH05_ISR /* 322 */
#endif
#if (GPT_TAUD0_CH07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_323 TAUD0_CH07_ISR /* 323 */
#endif
#if (GPT_TAUD0_CH09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_324 TAUD0_CH09_ISR /* 324 */
#endif
#if (GPT_TAUD0_CH11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_325 TAUD0_CH11_ISR /* 325 */
#endif
#if (GPT_TAUD0_CH13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_326 TAUD0_CH13_ISR /* 326 */
#endif
#if (GPT_TAUD0_CH15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_327 TAUD0_CH15_ISR /* 327 */
#endif
#if (GPT_TAUD1_CH00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_328 TAUD1_CH00_ISR /* 328 */
#endif
#if (GPT_TAUD1_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_329 TAUD1_CH01_ISR /* 329 */
#endif
#if (GPT_TAUD1_CH02_ISR_API == STD_ON)
#define INT_VECTOR_PE0_330 TAUD1_CH02_ISR /* 330 */
#endif
#if (GPT_TAUD1_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_331 TAUD1_CH03_ISR /* 331 */
#endif
#if (GPT_TAUD1_CH04_ISR_API == STD_ON)
#define INT_VECTOR_PE0_332 TAUD1_CH04_ISR /* 332 */
#endif
#if (GPT_TAUD1_CH05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_333 TAUD1_CH05_ISR /* 333 */
#endif
#if (GPT_TAUD1_CH06_ISR_API == STD_ON)
#define INT_VECTOR_PE0_334 TAUD1_CH06_ISR /* 334 */
#endif
#if (GPT_TAUD1_CH07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_335 TAUD1_CH07_ISR /* 335 */
#endif
#if (GPT_TAUD1_CH08_ISR_API == STD_ON)
#define INT_VECTOR_PE0_336 TAUD1_CH08_ISR /* 336 */
#endif
#if (GPT_TAUD1_CH09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_337 TAUD1_CH09_ISR /* 337 */
#endif
#if (GPT_TAUD1_CH10_ISR_API == STD_ON)
#define INT_VECTOR_PE0_338 TAUD1_CH10_ISR /* 338 */
#endif
#if (GPT_TAUD1_CH11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_339 TAUD1_CH11_ISR /* 339 */
#endif
#if (GPT_TAUD1_CH12_ISR_API == STD_ON)
#define INT_VECTOR_PE0_340 TAUD1_CH12_ISR /* 340 */
#endif
#if (GPT_TAUD1_CH13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_341 TAUD1_CH13_ISR /* 341 */
#endif
#if (GPT_TAUD1_CH14_ISR_API == STD_ON)
#define INT_VECTOR_PE0_342 TAUD1_CH14_ISR /* 342 */
#endif
#if (GPT_TAUD1_CH15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_343 TAUD1_CH15_ISR /* 343 */
#endif
#if (GPT_TAUD2_CH00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_344 TAUD2_CH00_ISR /* 344 */
#endif
#if (GPT_TAUD2_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_345 TAUD2_CH01_ISR /* 345 */
#endif
#if (GPT_TAUD2_CH02_ISR_API == STD_ON)
#define INT_VECTOR_PE0_346 TAUD2_CH02_ISR /* 346 */
#endif
#if (GPT_TAUD2_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_347 TAUD2_CH03_ISR /* 347 */
#endif
#if (GPT_TAUD2_CH04_ISR_API == STD_ON)
#define INT_VECTOR_PE0_348 TAUD2_CH04_ISR /* 348 */
#endif
#if (GPT_TAUD2_CH05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_349 TAUD2_CH05_ISR /* 349 */
#endif
#if (GPT_TAUD2_CH06_ISR_API == STD_ON)
#define INT_VECTOR_PE0_350 TAUD2_CH06_ISR /* 350 */
#endif
#if (GPT_TAUD2_CH07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_351 TAUD2_CH07_ISR /* 351 */
#endif
#if (GPT_TAUD2_CH08_ISR_API == STD_ON)
#define INT_VECTOR_PE0_352 TAUD2_CH08_ISR /* 352 */
#endif
#if (GPT_TAUD2_CH09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_353 TAUD2_CH09_ISR /* 353 */
#endif
#if (GPT_TAUD2_CH10_ISR_API == STD_ON)
#define INT_VECTOR_PE0_354 TAUD2_CH10_ISR /* 354 */
#endif
#if (GPT_TAUD2_CH11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_355 TAUD2_CH11_ISR /* 355 */
#endif
#if (GPT_TAUD2_CH12_ISR_API == STD_ON)
#define INT_VECTOR_PE0_356 TAUD2_CH12_ISR /* 356 */
#endif
#if (GPT_TAUD2_CH13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_357 TAUD2_CH13_ISR /* 357 */
#endif
#if (GPT_TAUD2_CH14_ISR_API == STD_ON)
#define INT_VECTOR_PE0_358 TAUD2_CH14_ISR /* 358 */
#endif
#if (GPT_TAUD2_CH15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_359 TAUD2_CH15_ISR /* 359 */
#endif
#if (GPT_TAUD3_CH00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_505 TAUD3_CH00_ISR /* 505 */
#define INT_VECTOR_PE0_379 TAUD3_CH00_ISR /* 379 */
#define INT_VECTOR_PE0_793 TAUD3_CH00_ISR /* 793 */
#endif
#if (GPT_TAUD3_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_506 TAUD3_CH01_ISR /* 506 */
#define INT_VECTOR_PE0_380 TAUD3_CH01_ISR /* 380 */
#define INT_VECTOR_PE0_794 TAUD3_CH01_ISR /* 794 */
#endif
#if (GPT_TAUD3_CH02_ISR_API == STD_ON)
#define INT_VECTOR_PE0_507 TAUD3_CH02_ISR /* 507 */
#define INT_VECTOR_PE0_381 TAUD3_CH02_ISR /* 381 */
#define INT_VECTOR_PE0_795 TAUD3_CH02_ISR /* 795 */
#endif
#if (GPT_TAUD3_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_508 TAUD3_CH03_ISR /* 508 */
#define INT_VECTOR_PE0_382 TAUD3_CH03_ISR /* 382 */
#define INT_VECTOR_PE0_796 TAUD3_CH03_ISR /* 796 */
#endif
#if (GPT_TAUD3_CH04_ISR_API == STD_ON)
#define INT_VECTOR_PE0_509 TAUD3_CH04_ISR /* 509 */
#define INT_VECTOR_PE0_383 TAUD3_CH04_ISR /* 383 */
#define INT_VECTOR_PE0_797 TAUD3_CH04_ISR /* 797 */
#endif
#if (GPT_TAUD3_CH05_ISR_API == STD_ON)
#define INT_VECTOR_PE0_510 TAUD3_CH05_ISR /* 510 */
#define INT_VECTOR_PE0_384 TAUD3_CH05_ISR /* 384 */
#define INT_VECTOR_PE0_798 TAUD3_CH05_ISR /* 798 */
#endif
#if (GPT_TAUD3_CH06_ISR_API == STD_ON)
#define INT_VECTOR_PE0_511 TAUD3_CH06_ISR /* 511 */
#define INT_VECTOR_PE0_385 TAUD3_CH06_ISR /* 385 */
#define INT_VECTOR_PE0_799 TAUD3_CH06_ISR /* 799 */
#endif
#if (GPT_TAUD3_CH07_ISR_API == STD_ON)
#define INT_VECTOR_PE0_512 TAUD3_CH07_ISR /* 512 */
#define INT_VECTOR_PE0_386 TAUD3_CH07_ISR /* 386 */
#define INT_VECTOR_PE0_800 TAUD3_CH07_ISR /* 800 */
#endif
#if (GPT_TAUD3_CH08_ISR_API == STD_ON)
#define INT_VECTOR_PE0_513 TAUD3_CH08_ISR /* 513 */
#define INT_VECTOR_PE0_387 TAUD3_CH08_ISR /* 387 */
#define INT_VECTOR_PE0_801 TAUD3_CH08_ISR /* 801 */
#endif
#if (GPT_TAUD3_CH09_ISR_API == STD_ON)
#define INT_VECTOR_PE0_514 TAUD3_CH09_ISR /* 514 */
#define INT_VECTOR_PE0_388 TAUD3_CH09_ISR /* 388 */
#define INT_VECTOR_PE0_802 TAUD3_CH09_ISR /* 802 */
#endif
#if (GPT_TAUD3_CH10_ISR_API == STD_ON)
#define INT_VECTOR_PE0_515 TAUD3_CH10_ISR /* 515 */
#define INT_VECTOR_PE0_389 TAUD3_CH10_ISR /* 389 */
#define INT_VECTOR_PE0_803 TAUD3_CH10_ISR /* 803 */
#endif
#if (GPT_TAUD3_CH11_ISR_API == STD_ON)
#define INT_VECTOR_PE0_516 TAUD3_CH11_ISR /* 516 */
#define INT_VECTOR_PE0_390 TAUD3_CH11_ISR /* 390 */
#define INT_VECTOR_PE0_804 TAUD3_CH11_ISR /* 804 */
#endif
#if (GPT_TAUD3_CH12_ISR_API == STD_ON)
#define INT_VECTOR_PE0_517 TAUD3_CH12_ISR /* 517 */
#define INT_VECTOR_PE0_391 TAUD3_CH12_ISR /* 391 */
#define INT_VECTOR_PE0_817 TAUD3_CH12_ISR /* 817 */
#endif
#if (GPT_TAUD3_CH13_ISR_API == STD_ON)
#define INT_VECTOR_PE0_518 TAUD3_CH13_ISR /* 518 */
#define INT_VECTOR_PE0_392 TAUD3_CH13_ISR /* 392 */
#define INT_VECTOR_PE0_818 TAUD3_CH13_ISR /* 818 */
#endif
#if (GPT_TAUD3_CH14_ISR_API == STD_ON)
#define INT_VECTOR_PE0_519 TAUD3_CH14_ISR /* 519 */
#define INT_VECTOR_PE0_393 TAUD3_CH14_ISR /* 393 */
#define INT_VECTOR_PE0_819 TAUD3_CH14_ISR /* 819 */
#endif
#if (GPT_TAUD3_CH15_ISR_API == STD_ON)
#define INT_VECTOR_PE0_520 TAUD3_CH15_ISR /* 520 */
#define INT_VECTOR_PE0_394 TAUD3_CH15_ISR /* 394 */
#define INT_VECTOR_PE0_820 TAUD3_CH15_ISR /* 820 */
#endif
#if (GPT_TAUJ2_CH00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_960 TAUJ2_CH00_ISR /* 960 */
#endif
#if (GPT_TAUJ2_CH01_ISR_API == STD_ON)
#define INT_VECTOR_PE0_961 TAUJ2_CH01_ISR /* 961 */
#endif
#if (GPT_TAUJ2_CH02_ISR_API == STD_ON)
#define INT_VECTOR_PE0_962 TAUJ2_CH02_ISR /* 962 */
#endif
#if (GPT_TAUJ2_CH03_ISR_API == STD_ON)
#define INT_VECTOR_PE0_963 TAUJ2_CH03_ISR /* 963 */
#endif
#if (GPT_TAUJ3_CH00_ISR_API == STD_ON)
#define INT_VECTOR_PE0_964 TAUJ3_CH00_ISR /* 964 */
#endif
#if ((GPT_TOM0_CH00_ISR_API == STD_ON) || (GPT_TOM0_CH01_ISR_API == STD_ON))
#define INT_VECTOR_PE0_086 GTM_TOM0_IRQ0_ISR /* 086 */
#endif
#if ((GPT_ATOM1_CH00_ISR_API == STD_ON) || (GPT_ATOM1_CH01_ISR_API == STD_ON))
#define INT_VECTOR_PE0_102 GTM_ATOM1_IRQ0_ISR /* 102 */
#endif
#endif  /* GPT_ISR_CATEGORY_2 */
#endif  /* GPT_MODULE_SAMPLE */


#pragma ghs section data=".inttable_PE0"
void (*IntVectors[])(void) = {
#ifdef INT_VECTOR_PE0_000
  INT_VECTOR_PE0_000, /* 000 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_001
  INT_VECTOR_PE0_001, /* 001 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_002
  INT_VECTOR_PE0_002, /* 002 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_003
  INT_VECTOR_PE0_003, /* 003 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_004
  INT_VECTOR_PE0_004, /* 004 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_005
  INT_VECTOR_PE0_005, /* 005 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_006
  INT_VECTOR_PE0_006, /* 006 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_007
  INT_VECTOR_PE0_007, /* 007 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_008
  INT_VECTOR_PE0_008, /* 008 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_009
  INT_VECTOR_PE0_009, /* 009 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_010
  INT_VECTOR_PE0_010, /* 010 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_011
  INT_VECTOR_PE0_011, /* 011 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_012
  INT_VECTOR_PE0_012, /* 012 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_013
  INT_VECTOR_PE0_013, /* 013 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_014
  INT_VECTOR_PE0_014, /* 014 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_015
  INT_VECTOR_PE0_015, /* 015 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_016
  INT_VECTOR_PE0_016, /* 016 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_017
  INT_VECTOR_PE0_017, /* 017 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_018
  INT_VECTOR_PE0_018, /* 018 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_019
  INT_VECTOR_PE0_019, /* 019 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_020
  INT_VECTOR_PE0_020, /* 020 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_021
  INT_VECTOR_PE0_021, /* 021 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_022
  INT_VECTOR_PE0_022, /* 022 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_023
  INT_VECTOR_PE0_023, /* 023 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_024
  INT_VECTOR_PE0_024, /* 024 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_025
  INT_VECTOR_PE0_025, /* 025 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_026
  INT_VECTOR_PE0_026, /* 026 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_027
  INT_VECTOR_PE0_027, /* 027 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_028
  INT_VECTOR_PE0_028, /* 028 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_029
  INT_VECTOR_PE0_029, /* 029 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_030
  INT_VECTOR_PE0_030, /* 030 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_031
  INT_VECTOR_PE0_031, /* 031 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_032
  INT_VECTOR_PE0_032, /* 032 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_033
  INT_VECTOR_PE0_033, /* 033 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_034
  INT_VECTOR_PE0_034, /* 034 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_035
  INT_VECTOR_PE0_035, /* 035 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_036
  INT_VECTOR_PE0_036, /* 036 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_037
  INT_VECTOR_PE0_037, /* 037 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_038
  INT_VECTOR_PE0_038, /* 038 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_039
  INT_VECTOR_PE0_039, /* 039 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_040
  INT_VECTOR_PE0_040, /* 040 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_041
  INT_VECTOR_PE0_041, /* 041 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_042
  INT_VECTOR_PE0_042, /* 042 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_043
  INT_VECTOR_PE0_043, /* 043 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_044
  INT_VECTOR_PE0_044, /* 044 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_045
  INT_VECTOR_PE0_045, /* 045 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_046
  INT_VECTOR_PE0_046, /* 046 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_047
  INT_VECTOR_PE0_047, /* 047 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_048
  INT_VECTOR_PE0_048, /* 048 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_049
  INT_VECTOR_PE0_049, /* 049 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_050
  INT_VECTOR_PE0_050, /* 050 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_051
  INT_VECTOR_PE0_051, /* 051 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_052
  INT_VECTOR_PE0_052, /* 052 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_053
  INT_VECTOR_PE0_053, /* 053 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_054
  INT_VECTOR_PE0_054, /* 054 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_055
  INT_VECTOR_PE0_055, /* 055 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_056
  INT_VECTOR_PE0_056, /* 056 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_057
  INT_VECTOR_PE0_057, /* 057 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_058
  INT_VECTOR_PE0_058, /* 058 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_059
  INT_VECTOR_PE0_059, /* 059 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_060
  INT_VECTOR_PE0_060, /* 060 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_061
  INT_VECTOR_PE0_061, /* 061 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_062
  INT_VECTOR_PE0_062, /* 062 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_063
  INT_VECTOR_PE0_063, /* 063 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_064
  INT_VECTOR_PE0_064, /* 064 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_065
  INT_VECTOR_PE0_065, /* 065 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_066
  INT_VECTOR_PE0_066, /* 066 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_067
  INT_VECTOR_PE0_067, /* 067 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_068
  INT_VECTOR_PE0_068, /* 068 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_069
  INT_VECTOR_PE0_069, /* 069 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_070
  INT_VECTOR_PE0_070, /* 070 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_071
  INT_VECTOR_PE0_071, /* 071 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_072
  INT_VECTOR_PE0_072, /* 072 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_073
  INT_VECTOR_PE0_073, /* 073 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_074
  INT_VECTOR_PE0_074, /* 074 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_075
  INT_VECTOR_PE0_075, /* 075 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_076
  INT_VECTOR_PE0_076, /* 076 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_077
  INT_VECTOR_PE0_077, /* 077 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_078
  INT_VECTOR_PE0_078, /* 078 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_079
  INT_VECTOR_PE0_079, /* 079 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_080
  INT_VECTOR_PE0_080, /* 080 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_081
  INT_VECTOR_PE0_081, /* 081 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_082
  INT_VECTOR_PE0_082, /* 082 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_083
  INT_VECTOR_PE0_083, /* 083 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_084
  INT_VECTOR_PE0_084, /* 084 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_085
  INT_VECTOR_PE0_085, /* 085 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_086
  INT_VECTOR_PE0_086, /* 086 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_087
  INT_VECTOR_PE0_087, /* 087 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_088
  INT_VECTOR_PE0_088, /* 088 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_089
  INT_VECTOR_PE0_089, /* 089 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_090
  INT_VECTOR_PE0_090, /* 090 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_091
  INT_VECTOR_PE0_091, /* 091 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_092
  INT_VECTOR_PE0_092, /* 092 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_093
  INT_VECTOR_PE0_093, /* 093 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_094
  INT_VECTOR_PE0_094, /* 094 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_095
  INT_VECTOR_PE0_095, /* 095 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_096
  INT_VECTOR_PE0_096, /* 096 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_097
  INT_VECTOR_PE0_097, /* 097 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_098
  INT_VECTOR_PE0_098, /* 098 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_099
  INT_VECTOR_PE0_099, /* 099 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_100
  INT_VECTOR_PE0_100, /* 100 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_101
  INT_VECTOR_PE0_101, /* 101 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_102
  INT_VECTOR_PE0_102, /* 102 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_103
  INT_VECTOR_PE0_103, /* 103 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_104
  INT_VECTOR_PE0_104, /* 104 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_105
  INT_VECTOR_PE0_105, /* 105 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_106
  INT_VECTOR_PE0_106, /* 106 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_107
  INT_VECTOR_PE0_107, /* 107 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_108
  INT_VECTOR_PE0_108, /* 108 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_109
  INT_VECTOR_PE0_109, /* 109 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_110
  INT_VECTOR_PE0_110, /* 110 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_111
  INT_VECTOR_PE0_111, /* 111 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_112
  INT_VECTOR_PE0_112, /* 112 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_113
  INT_VECTOR_PE0_113, /* 113 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_114
  INT_VECTOR_PE0_114, /* 114 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_115
  INT_VECTOR_PE0_115, /* 115 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_116
  INT_VECTOR_PE0_116, /* 116 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_117
  INT_VECTOR_PE0_117, /* 117 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_118
  INT_VECTOR_PE0_118, /* 118 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_119
  INT_VECTOR_PE0_119, /* 119 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_120
  INT_VECTOR_PE0_120, /* 120 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_121
  INT_VECTOR_PE0_121, /* 121 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_122
  INT_VECTOR_PE0_122, /* 122 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_123
  INT_VECTOR_PE0_123, /* 123 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_124
  INT_VECTOR_PE0_124, /* 124 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_125
  INT_VECTOR_PE0_125, /* 125 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_126
  INT_VECTOR_PE0_126, /* 126 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_127
  INT_VECTOR_PE0_127, /* 127 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_128
  INT_VECTOR_PE0_128, /* 128 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_129
  INT_VECTOR_PE0_129, /* 129 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_130
  INT_VECTOR_PE0_130, /* 130 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_131
  INT_VECTOR_PE0_131, /* 131 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_132
  INT_VECTOR_PE0_132, /* 132 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_133
  INT_VECTOR_PE0_133, /* 133 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_134
  INT_VECTOR_PE0_134, /* 134 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_135
  INT_VECTOR_PE0_135, /* 135 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_136
  INT_VECTOR_PE0_136, /* 136 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_137
  INT_VECTOR_PE0_137, /* 137 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_138
  INT_VECTOR_PE0_138, /* 138 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_139
  INT_VECTOR_PE0_139, /* 139 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_140
  INT_VECTOR_PE0_140, /* 140 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_141
  INT_VECTOR_PE0_141, /* 141 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_142
  INT_VECTOR_PE0_142, /* 142 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_143
  INT_VECTOR_PE0_143, /* 143 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_144
  INT_VECTOR_PE0_144, /* 144 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_145
  INT_VECTOR_PE0_145, /* 145 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_146
  INT_VECTOR_PE0_146, /* 146 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_147
  INT_VECTOR_PE0_147, /* 147 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_148
  INT_VECTOR_PE0_148, /* 148 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_149
  INT_VECTOR_PE0_149, /* 149 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_150
  INT_VECTOR_PE0_150, /* 150 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_151
  INT_VECTOR_PE0_151, /* 151 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_152
  INT_VECTOR_PE0_152, /* 152 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_153
  INT_VECTOR_PE0_153, /* 153 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_154
  INT_VECTOR_PE0_154, /* 154 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_155
  INT_VECTOR_PE0_155, /* 155 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_156
  INT_VECTOR_PE0_156, /* 156 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_157
  INT_VECTOR_PE0_157, /* 157 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_158
  INT_VECTOR_PE0_158, /* 158 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_159
  INT_VECTOR_PE0_159, /* 159 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_160
  INT_VECTOR_PE0_160, /* 160 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_161
  INT_VECTOR_PE0_161, /* 161 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_162
  INT_VECTOR_PE0_162, /* 162 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_163
  INT_VECTOR_PE0_163, /* 163 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_164
  INT_VECTOR_PE0_164, /* 164 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_165
  INT_VECTOR_PE0_165, /* 165 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_166
  INT_VECTOR_PE0_166, /* 166 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_167
  INT_VECTOR_PE0_167, /* 167 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_168
  INT_VECTOR_PE0_168, /* 168 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_169
  INT_VECTOR_PE0_169, /* 169 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_170
  INT_VECTOR_PE0_170, /* 170 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_171
  INT_VECTOR_PE0_171, /* 171 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_172
  INT_VECTOR_PE0_172, /* 172 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_173
  INT_VECTOR_PE0_173, /* 173 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_174
  INT_VECTOR_PE0_174, /* 174 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_175
  INT_VECTOR_PE0_175, /* 175 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_176
  INT_VECTOR_PE0_176, /* 176 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_177
  INT_VECTOR_PE0_177, /* 177 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_178
  INT_VECTOR_PE0_178, /* 178 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_179
  INT_VECTOR_PE0_179, /* 179 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_180
  INT_VECTOR_PE0_180, /* 180 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_181
  INT_VECTOR_PE0_181, /* 181 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_182
  INT_VECTOR_PE0_182, /* 182 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_183
  INT_VECTOR_PE0_183, /* 183 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_184
  INT_VECTOR_PE0_184, /* 184 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_185
  INT_VECTOR_PE0_185, /* 185 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_186
  INT_VECTOR_PE0_186, /* 186 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_187
  INT_VECTOR_PE0_187, /* 187 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_188
  INT_VECTOR_PE0_188, /* 188 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_189
  INT_VECTOR_PE0_189, /* 189 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_190
  INT_VECTOR_PE0_190, /* 190 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_191
  INT_VECTOR_PE0_191, /* 191 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_192
  INT_VECTOR_PE0_192, /* 192 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_193
  INT_VECTOR_PE0_193, /* 193 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_194
  INT_VECTOR_PE0_194, /* 194 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_195
  INT_VECTOR_PE0_195, /* 195 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_196
  INT_VECTOR_PE0_196, /* 196 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_197
  INT_VECTOR_PE0_197, /* 197 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_198
  INT_VECTOR_PE0_198, /* 198 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_199
  INT_VECTOR_PE0_199, /* 199 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_200
  INT_VECTOR_PE0_200, /* 200 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_201
  INT_VECTOR_PE0_201, /* 201 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_202
  INT_VECTOR_PE0_202, /* 202 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_203
  INT_VECTOR_PE0_203, /* 203 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_204
  INT_VECTOR_PE0_204, /* 204 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_205
  INT_VECTOR_PE0_205, /* 205 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_206
  INT_VECTOR_PE0_206, /* 206 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_207
  INT_VECTOR_PE0_207, /* 207 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_208
  INT_VECTOR_PE0_208, /* 208 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_209
  INT_VECTOR_PE0_209, /* 209 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_210
  INT_VECTOR_PE0_210, /* 210 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_211
  INT_VECTOR_PE0_211, /* 211 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_212
  INT_VECTOR_PE0_212, /* 212 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_213
  INT_VECTOR_PE0_213, /* 213 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_214
  INT_VECTOR_PE0_214, /* 214 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_215
  INT_VECTOR_PE0_215, /* 215 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_216
  INT_VECTOR_PE0_216, /* 216 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_217
  INT_VECTOR_PE0_217, /* 217 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_218
  INT_VECTOR_PE0_218, /* 218 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_219
  INT_VECTOR_PE0_219, /* 219 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_220
  INT_VECTOR_PE0_220, /* 220 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_221
  INT_VECTOR_PE0_221, /* 221 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_222
  INT_VECTOR_PE0_222, /* 222 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_223
  INT_VECTOR_PE0_223, /* 223 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_224
  INT_VECTOR_PE0_224, /* 224 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_225
  INT_VECTOR_PE0_225, /* 225 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_226
  INT_VECTOR_PE0_226, /* 226 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_227
  INT_VECTOR_PE0_227, /* 227 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_228
  INT_VECTOR_PE0_228, /* 228 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_229
  INT_VECTOR_PE0_229, /* 229 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_230
  INT_VECTOR_PE0_230, /* 230 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_231
  INT_VECTOR_PE0_231, /* 231 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_232
  INT_VECTOR_PE0_232, /* 232 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_233
  INT_VECTOR_PE0_233, /* 233 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_234
  INT_VECTOR_PE0_234, /* 234 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_235
  INT_VECTOR_PE0_235, /* 235 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_236
  INT_VECTOR_PE0_236, /* 236 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_237
  INT_VECTOR_PE0_237, /* 237 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_238
  INT_VECTOR_PE0_238, /* 238 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_239
  INT_VECTOR_PE0_239, /* 239 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_240
  INT_VECTOR_PE0_240, /* 240 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_241
  INT_VECTOR_PE0_241, /* 241 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_242
  INT_VECTOR_PE0_242, /* 242 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_243
  INT_VECTOR_PE0_243, /* 243 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_244
  INT_VECTOR_PE0_244, /* 244 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_245
  INT_VECTOR_PE0_245, /* 245 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_246
  INT_VECTOR_PE0_246, /* 246 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_247
  INT_VECTOR_PE0_247, /* 247 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_248
  INT_VECTOR_PE0_248, /* 248 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_249
  INT_VECTOR_PE0_249, /* 249 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_250
  INT_VECTOR_PE0_250, /* 250 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_251
  INT_VECTOR_PE0_251, /* 251 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_252
  INT_VECTOR_PE0_252, /* 252 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_253
  INT_VECTOR_PE0_253, /* 253 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_254
  INT_VECTOR_PE0_254, /* 254 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_255
  INT_VECTOR_PE0_255, /* 255 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_256
  INT_VECTOR_PE0_256, /* 256 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_257
  INT_VECTOR_PE0_257, /* 257 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_258
  INT_VECTOR_PE0_258, /* 258 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_259
  INT_VECTOR_PE0_259, /* 259 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_260
  INT_VECTOR_PE0_260, /* 260 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_261
  INT_VECTOR_PE0_261, /* 261 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_262
  INT_VECTOR_PE0_262, /* 262 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_263
  INT_VECTOR_PE0_263, /* 263 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_264
  INT_VECTOR_PE0_264, /* 264 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_265
  INT_VECTOR_PE0_265, /* 265 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_266
  INT_VECTOR_PE0_266, /* 266 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_267
  INT_VECTOR_PE0_267, /* 267 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_268
  INT_VECTOR_PE0_268, /* 268 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_269
  INT_VECTOR_PE0_269, /* 269 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_270
  INT_VECTOR_PE0_270, /* 270 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_271
  INT_VECTOR_PE0_271, /* 271 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_272
  INT_VECTOR_PE0_272, /* 272 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_273
  INT_VECTOR_PE0_273, /* 273 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_274
  INT_VECTOR_PE0_274, /* 274 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_275
  INT_VECTOR_PE0_275, /* 275 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_276
  INT_VECTOR_PE0_276, /* 276 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_277
  INT_VECTOR_PE0_277, /* 277 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_278
  INT_VECTOR_PE0_278, /* 278 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_279
  INT_VECTOR_PE0_279, /* 279 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_280
  INT_VECTOR_PE0_280, /* 280 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_281
  INT_VECTOR_PE0_281, /* 281 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_282
  INT_VECTOR_PE0_282, /* 282 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_283
  INT_VECTOR_PE0_283, /* 283 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_284
  INT_VECTOR_PE0_284, /* 284 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_285
  INT_VECTOR_PE0_285, /* 285 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_286
  INT_VECTOR_PE0_286, /* 286 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_287
  INT_VECTOR_PE0_287, /* 287 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_288
  INT_VECTOR_PE0_288, /* 288 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_289
  INT_VECTOR_PE0_289, /* 289 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_290
  INT_VECTOR_PE0_290, /* 290 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_291
  INT_VECTOR_PE0_291, /* 291 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_292
  INT_VECTOR_PE0_292, /* 292 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_293
  INT_VECTOR_PE0_293, /* 293 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_294
  INT_VECTOR_PE0_294, /* 294 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_295
  INT_VECTOR_PE0_295, /* 295 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_296
  INT_VECTOR_PE0_296, /* 296 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_297
  INT_VECTOR_PE0_297, /* 297 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_298
  INT_VECTOR_PE0_298, /* 298 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_299
  INT_VECTOR_PE0_299, /* 299 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_300
  INT_VECTOR_PE0_300, /* 300 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_301
  INT_VECTOR_PE0_301, /* 301 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_302
  INT_VECTOR_PE0_302, /* 302 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_303
  INT_VECTOR_PE0_303, /* 303 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_304
  INT_VECTOR_PE0_304, /* 304 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_305
  INT_VECTOR_PE0_305, /* 305 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_306
  INT_VECTOR_PE0_306, /* 306 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_307
  INT_VECTOR_PE0_307, /* 307 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_308
  INT_VECTOR_PE0_308, /* 308 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_309
  INT_VECTOR_PE0_309, /* 309 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_310
  INT_VECTOR_PE0_310, /* 310 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_311
  INT_VECTOR_PE0_311, /* 311 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_312
  INT_VECTOR_PE0_312, /* 312 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_313
  INT_VECTOR_PE0_313, /* 313 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_314
  INT_VECTOR_PE0_314, /* 314 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_315
  INT_VECTOR_PE0_315, /* 315 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_316
  INT_VECTOR_PE0_316, /* 316 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_317
  INT_VECTOR_PE0_317, /* 317 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_318
  INT_VECTOR_PE0_318, /* 318 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_319
  INT_VECTOR_PE0_319, /* 319 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_320
  INT_VECTOR_PE0_320, /* 320 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_321
  INT_VECTOR_PE0_321, /* 321 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_322
  INT_VECTOR_PE0_322, /* 322 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_323
  INT_VECTOR_PE0_323, /* 323 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_324
  INT_VECTOR_PE0_324, /* 324 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_325
  INT_VECTOR_PE0_325, /* 325 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_326
  INT_VECTOR_PE0_326, /* 326 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_327
  INT_VECTOR_PE0_327, /* 327 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_328
  INT_VECTOR_PE0_328, /* 328 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_329
  INT_VECTOR_PE0_329, /* 329 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_330
  INT_VECTOR_PE0_330, /* 330 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_331
  INT_VECTOR_PE0_331, /* 331 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_332
  INT_VECTOR_PE0_332, /* 332 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_333
  INT_VECTOR_PE0_333, /* 333 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_334
  INT_VECTOR_PE0_334, /* 334 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_335
  INT_VECTOR_PE0_335, /* 335 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_336
  INT_VECTOR_PE0_336, /* 336 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_337
  INT_VECTOR_PE0_337, /* 337 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_338
  INT_VECTOR_PE0_338, /* 338 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_339
  INT_VECTOR_PE0_339, /* 339 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_340
  INT_VECTOR_PE0_340, /* 340 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_341
  INT_VECTOR_PE0_341, /* 341 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_342
  INT_VECTOR_PE0_342, /* 342 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_343
  INT_VECTOR_PE0_343, /* 343 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_344
  INT_VECTOR_PE0_344, /* 344 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_345
  INT_VECTOR_PE0_345, /* 345 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_346
  INT_VECTOR_PE0_346, /* 346 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_347
  INT_VECTOR_PE0_347, /* 347 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_348
  INT_VECTOR_PE0_348, /* 348 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_349
  INT_VECTOR_PE0_349, /* 349 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_350
  INT_VECTOR_PE0_350, /* 350 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_351
  INT_VECTOR_PE0_351, /* 351 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_352
  INT_VECTOR_PE0_352, /* 352 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_353
  INT_VECTOR_PE0_353, /* 353 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_354
  INT_VECTOR_PE0_354, /* 354 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_355
  INT_VECTOR_PE0_355, /* 355 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_356
  INT_VECTOR_PE0_356, /* 356 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_357
  INT_VECTOR_PE0_357, /* 357 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_358
  INT_VECTOR_PE0_358, /* 358 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_359
  INT_VECTOR_PE0_359, /* 359 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_360
  INT_VECTOR_PE0_360, /* 360 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_361
  INT_VECTOR_PE0_361, /* 361 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_362
  INT_VECTOR_PE0_362, /* 362 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_363
  INT_VECTOR_PE0_363, /* 363 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_364
  INT_VECTOR_PE0_364, /* 364 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_365
  INT_VECTOR_PE0_365, /* 365 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_366
  INT_VECTOR_PE0_366, /* 366 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_367
  INT_VECTOR_PE0_367, /* 367 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_368
  INT_VECTOR_PE0_368, /* 368 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_369
  INT_VECTOR_PE0_369, /* 369 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_370
  INT_VECTOR_PE0_370, /* 370 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_371
  INT_VECTOR_PE0_371, /* 371 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_372
  INT_VECTOR_PE0_372, /* 372 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_373
  INT_VECTOR_PE0_373, /* 373 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_374
  INT_VECTOR_PE0_374, /* 374 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_375
  INT_VECTOR_PE0_375, /* 375 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_376
  INT_VECTOR_PE0_376, /* 376 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_377
  INT_VECTOR_PE0_377, /* 377 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_378
  INT_VECTOR_PE0_378, /* 378 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_379
  INT_VECTOR_PE0_379, /* 379 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_380
  INT_VECTOR_PE0_380, /* 380 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_381
  INT_VECTOR_PE0_381, /* 381 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_382
  INT_VECTOR_PE0_382, /* 382 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_383
  INT_VECTOR_PE0_383, /* 383 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_384
  INT_VECTOR_PE0_384, /* 384 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_385
  INT_VECTOR_PE0_385, /* 385 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_386
  INT_VECTOR_PE0_386, /* 386 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_387
  INT_VECTOR_PE0_387, /* 387 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_388
  INT_VECTOR_PE0_388, /* 388 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_389
  INT_VECTOR_PE0_389, /* 389 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_390
  INT_VECTOR_PE0_390, /* 390 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_391
  INT_VECTOR_PE0_391, /* 391 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_392
  INT_VECTOR_PE0_392, /* 392 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_393
  INT_VECTOR_PE0_393, /* 393 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_394
  INT_VECTOR_PE0_394, /* 394 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_395
  INT_VECTOR_PE0_395, /* 395 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_396
  INT_VECTOR_PE0_396, /* 396 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_397
  INT_VECTOR_PE0_397, /* 397 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_398
  INT_VECTOR_PE0_398, /* 398 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_399
  INT_VECTOR_PE0_399, /* 399 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_400
  INT_VECTOR_PE0_400, /* 400 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_401
  INT_VECTOR_PE0_401, /* 401 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_402
  INT_VECTOR_PE0_402, /* 402 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_403
  INT_VECTOR_PE0_403, /* 403 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_404
  INT_VECTOR_PE0_404, /* 404 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_405
  INT_VECTOR_PE0_405, /* 405 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_406
  INT_VECTOR_PE0_406, /* 406 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_407
  INT_VECTOR_PE0_407, /* 407 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_408
  INT_VECTOR_PE0_408, /* 408 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_409
  INT_VECTOR_PE0_409, /* 409 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_410
  INT_VECTOR_PE0_410, /* 410 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_411
  INT_VECTOR_PE0_411, /* 411 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_412
  INT_VECTOR_PE0_412, /* 412 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_413
  INT_VECTOR_PE0_413, /* 413 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_414
  INT_VECTOR_PE0_414, /* 414 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_415
  INT_VECTOR_PE0_415, /* 415 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_416
  INT_VECTOR_PE0_416, /* 416 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_417
  INT_VECTOR_PE0_417, /* 417 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_418
  INT_VECTOR_PE0_418, /* 418 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_419
  INT_VECTOR_PE0_419, /* 419 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_420
  INT_VECTOR_PE0_420, /* 420 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_421
  INT_VECTOR_PE0_421, /* 421 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_422
  INT_VECTOR_PE0_422, /* 422 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_423
  INT_VECTOR_PE0_423, /* 423 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_424
  INT_VECTOR_PE0_424, /* 424 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_425
  INT_VECTOR_PE0_425, /* 425 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_426
  INT_VECTOR_PE0_426, /* 426 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_427
  INT_VECTOR_PE0_427, /* 427 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_428
  INT_VECTOR_PE0_428, /* 428 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_429
  INT_VECTOR_PE0_429, /* 429 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_430
  INT_VECTOR_PE0_430, /* 430 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_431
  INT_VECTOR_PE0_431, /* 431 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_432
  INT_VECTOR_PE0_432, /* 432 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_433
  INT_VECTOR_PE0_433, /* 433 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_434
  INT_VECTOR_PE0_434, /* 434 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_435
  INT_VECTOR_PE0_435, /* 435 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_436
  INT_VECTOR_PE0_436, /* 436 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_437
  INT_VECTOR_PE0_437, /* 437 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_438
  INT_VECTOR_PE0_438, /* 438 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_439
  INT_VECTOR_PE0_439, /* 439 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_440
  INT_VECTOR_PE0_440, /* 440 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_441
  INT_VECTOR_PE0_441, /* 441 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_442
  INT_VECTOR_PE0_442, /* 442 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_443
  INT_VECTOR_PE0_443, /* 443 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_444
  INT_VECTOR_PE0_444, /* 444 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_445
  INT_VECTOR_PE0_445, /* 445 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_446
  INT_VECTOR_PE0_446, /* 446 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_447
  INT_VECTOR_PE0_447, /* 447 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_448
  INT_VECTOR_PE0_448, /* 448 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_449
  INT_VECTOR_PE0_449, /* 449 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_450
  INT_VECTOR_PE0_450, /* 450 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_451
  INT_VECTOR_PE0_451, /* 451 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_452
  INT_VECTOR_PE0_452, /* 452 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_453
  INT_VECTOR_PE0_453, /* 453 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_454
  INT_VECTOR_PE0_454, /* 454 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_455
  INT_VECTOR_PE0_455, /* 455 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_456
  INT_VECTOR_PE0_456, /* 456 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_457
  INT_VECTOR_PE0_457, /* 457 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_458
  INT_VECTOR_PE0_458, /* 458 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_459
  INT_VECTOR_PE0_459, /* 459 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_460
  INT_VECTOR_PE0_460, /* 460 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_461
  INT_VECTOR_PE0_461, /* 461 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_462
  INT_VECTOR_PE0_462, /* 462 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_463
  INT_VECTOR_PE0_463, /* 463 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_464
  INT_VECTOR_PE0_464, /* 464 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_465
  INT_VECTOR_PE0_465, /* 465 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_466
  INT_VECTOR_PE0_466, /* 466 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_467
  INT_VECTOR_PE0_467, /* 467 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_468
  INT_VECTOR_PE0_468, /* 468 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_469
  INT_VECTOR_PE0_469, /* 469 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_470
  INT_VECTOR_PE0_470, /* 470 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_471
  INT_VECTOR_PE0_471, /* 471 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_472
  INT_VECTOR_PE0_472, /* 472 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_473
  INT_VECTOR_PE0_473, /* 473 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_474
  INT_VECTOR_PE0_474, /* 474 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_475
  INT_VECTOR_PE0_475, /* 475 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_476
  INT_VECTOR_PE0_476, /* 476 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_477
  INT_VECTOR_PE0_477, /* 477 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_478
  INT_VECTOR_PE0_478, /* 478 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_479
  INT_VECTOR_PE0_479, /* 479 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_480
  INT_VECTOR_PE0_480, /* 480 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_481
  INT_VECTOR_PE0_481, /* 481 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_482
  INT_VECTOR_PE0_482, /* 482 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_483
  INT_VECTOR_PE0_483, /* 483 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_484
  INT_VECTOR_PE0_484, /* 484 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_485
  INT_VECTOR_PE0_485, /* 485 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_486
  INT_VECTOR_PE0_486, /* 486 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_487
  INT_VECTOR_PE0_487, /* 487 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_488
  INT_VECTOR_PE0_488, /* 488 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_489
  INT_VECTOR_PE0_489, /* 489 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_490
  INT_VECTOR_PE0_490, /* 490 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_491
  INT_VECTOR_PE0_491, /* 491 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_492
  INT_VECTOR_PE0_492, /* 492 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_493
  INT_VECTOR_PE0_493, /* 493 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_494
  INT_VECTOR_PE0_494, /* 494 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_495
  INT_VECTOR_PE0_495, /* 495 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_496
  INT_VECTOR_PE0_496, /* 496 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_497
  INT_VECTOR_PE0_497, /* 497 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_498
  INT_VECTOR_PE0_498, /* 498 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_499
  INT_VECTOR_PE0_499, /* 499 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_500
  INT_VECTOR_PE0_500, /* 500 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_501
  INT_VECTOR_PE0_501, /* 501 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_502
  INT_VECTOR_PE0_502, /* 502 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_503
  INT_VECTOR_PE0_503, /* 503 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_504
  INT_VECTOR_PE0_504, /* 504 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_505
  INT_VECTOR_PE0_505, /* 505 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_506
  INT_VECTOR_PE0_506, /* 506 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_507
  INT_VECTOR_PE0_507, /* 507 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_508
  INT_VECTOR_PE0_508, /* 508 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_509
  INT_VECTOR_PE0_509, /* 509 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_510
  INT_VECTOR_PE0_510, /* 510 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_511
  INT_VECTOR_PE0_511, /* 511 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_512
  INT_VECTOR_PE0_512, /* 512 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_513
  INT_VECTOR_PE0_513, /* 513 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_514
  INT_VECTOR_PE0_514, /* 514 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_515
  INT_VECTOR_PE0_515, /* 515 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_516
  INT_VECTOR_PE0_516, /* 516 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_517
  INT_VECTOR_PE0_517, /* 517 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_518
  INT_VECTOR_PE0_518, /* 518 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_519
  INT_VECTOR_PE0_519, /* 519 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_520
  INT_VECTOR_PE0_520, /* 520 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_521
  INT_VECTOR_PE0_521, /* 521 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_522
  INT_VECTOR_PE0_522, /* 522 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_523
  INT_VECTOR_PE0_523, /* 523 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_524
  INT_VECTOR_PE0_524, /* 524 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_525
  INT_VECTOR_PE0_525, /* 525 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_526
  INT_VECTOR_PE0_526, /* 526 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_527
  INT_VECTOR_PE0_527, /* 527 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_528
  INT_VECTOR_PE0_528, /* 528 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_529
  INT_VECTOR_PE0_529, /* 529 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_530
  INT_VECTOR_PE0_530, /* 530 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_531
  INT_VECTOR_PE0_531, /* 531 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_532
  INT_VECTOR_PE0_532, /* 532 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_533
  INT_VECTOR_PE0_533, /* 533 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_534
  INT_VECTOR_PE0_534, /* 534 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_535
  INT_VECTOR_PE0_535, /* 535 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_536
  INT_VECTOR_PE0_536, /* 536 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_537
  INT_VECTOR_PE0_537, /* 537 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_538
  INT_VECTOR_PE0_538, /* 538 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_539
  INT_VECTOR_PE0_539, /* 539 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_540
  INT_VECTOR_PE0_540, /* 540 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_541
  INT_VECTOR_PE0_541, /* 541 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_542
  INT_VECTOR_PE0_542, /* 542 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_543
  INT_VECTOR_PE0_543, /* 543 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_544
  INT_VECTOR_PE0_544, /* 544 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_545
  INT_VECTOR_PE0_545, /* 545 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_546
  INT_VECTOR_PE0_546, /* 546 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_547
  INT_VECTOR_PE0_547, /* 547 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_548
  INT_VECTOR_PE0_548, /* 548 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_549
  INT_VECTOR_PE0_549, /* 549 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_550
  INT_VECTOR_PE0_550, /* 550 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_551
  INT_VECTOR_PE0_551, /* 551 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_552
  INT_VECTOR_PE0_552, /* 552 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_553
  INT_VECTOR_PE0_553, /* 553 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_554
  INT_VECTOR_PE0_554, /* 554 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_555
  INT_VECTOR_PE0_555, /* 555 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_556
  INT_VECTOR_PE0_556, /* 556 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_557
  INT_VECTOR_PE0_557, /* 557 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_558
  INT_VECTOR_PE0_558, /* 558 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_559
  INT_VECTOR_PE0_559, /* 559 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_560
  INT_VECTOR_PE0_560, /* 560 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_561
  INT_VECTOR_PE0_561, /* 561 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_562
  INT_VECTOR_PE0_562, /* 562 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_563
  INT_VECTOR_PE0_563, /* 563 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_564
  INT_VECTOR_PE0_564, /* 564 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_565
  INT_VECTOR_PE0_565, /* 565 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_566
  INT_VECTOR_PE0_566, /* 566 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_567
  INT_VECTOR_PE0_567, /* 567 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_568
  INT_VECTOR_PE0_568, /* 568 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_569
  INT_VECTOR_PE0_569, /* 569 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_570
  INT_VECTOR_PE0_570, /* 570 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_571
  INT_VECTOR_PE0_571, /* 571 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_572
  INT_VECTOR_PE0_572, /* 572 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_573
  INT_VECTOR_PE0_573, /* 573 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_574
  INT_VECTOR_PE0_574, /* 574 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_575
  INT_VECTOR_PE0_575, /* 575 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_576
  INT_VECTOR_PE0_576, /* 576 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_577
  INT_VECTOR_PE0_577, /* 577 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_578
  INT_VECTOR_PE0_578, /* 578 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_579
  INT_VECTOR_PE0_579, /* 579 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_580
  INT_VECTOR_PE0_580, /* 580 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_581
  INT_VECTOR_PE0_581, /* 581 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_582
  INT_VECTOR_PE0_582, /* 582 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_583
  INT_VECTOR_PE0_583, /* 583 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_584
  INT_VECTOR_PE0_584, /* 584 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_585
  INT_VECTOR_PE0_585, /* 585 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_586
  INT_VECTOR_PE0_586, /* 586 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_587
  INT_VECTOR_PE0_587, /* 587 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_588
  INT_VECTOR_PE0_588, /* 588 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_589
  INT_VECTOR_PE0_589, /* 589 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_590
  INT_VECTOR_PE0_590, /* 590 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_591
  INT_VECTOR_PE0_591, /* 591 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_592
  INT_VECTOR_PE0_592, /* 592 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_593
  INT_VECTOR_PE0_593, /* 593 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_594
  INT_VECTOR_PE0_594, /* 594 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_595
  INT_VECTOR_PE0_595, /* 595 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_596
  INT_VECTOR_PE0_596, /* 596 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_597
  INT_VECTOR_PE0_597, /* 597 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_598
  INT_VECTOR_PE0_598, /* 598 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_599
  INT_VECTOR_PE0_599, /* 599 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_600
  INT_VECTOR_PE0_600, /* 600 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_601
  INT_VECTOR_PE0_601, /* 601 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_602
  INT_VECTOR_PE0_602, /* 602 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_603
  INT_VECTOR_PE0_603, /* 603 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_604
  INT_VECTOR_PE0_604, /* 604 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_605
  INT_VECTOR_PE0_605, /* 605 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_606
  INT_VECTOR_PE0_606, /* 606 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_607
  INT_VECTOR_PE0_607, /* 607 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_608
  INT_VECTOR_PE0_608, /* 608 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_609
  INT_VECTOR_PE0_609, /* 609 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_610
  INT_VECTOR_PE0_610, /* 610 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_611
  INT_VECTOR_PE0_611, /* 611 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_612
  INT_VECTOR_PE0_612, /* 612 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_613
  INT_VECTOR_PE0_613, /* 613 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_614
  INT_VECTOR_PE0_614, /* 614 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_615
  INT_VECTOR_PE0_615, /* 615 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_616
  INT_VECTOR_PE0_616, /* 616 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_617
  INT_VECTOR_PE0_617, /* 617 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_618
  INT_VECTOR_PE0_618, /* 618 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_619
  INT_VECTOR_PE0_619, /* 619 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_620
  INT_VECTOR_PE0_620, /* 620 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_621
  INT_VECTOR_PE0_621, /* 621 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_622
  INT_VECTOR_PE0_622, /* 622 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_623
  INT_VECTOR_PE0_623, /* 623 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_624
  INT_VECTOR_PE0_624, /* 624 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_625
  INT_VECTOR_PE0_625, /* 625 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_626
  INT_VECTOR_PE0_626, /* 626 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_627
  INT_VECTOR_PE0_627, /* 627 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_628
  INT_VECTOR_PE0_628, /* 628 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_629
  INT_VECTOR_PE0_629, /* 629 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_630
  INT_VECTOR_PE0_630, /* 630 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_631
  INT_VECTOR_PE0_631, /* 631 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_632
  INT_VECTOR_PE0_632, /* 632 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_633
  INT_VECTOR_PE0_633, /* 633 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_634
  INT_VECTOR_PE0_634, /* 634 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_635
  INT_VECTOR_PE0_635, /* 635 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_636
  INT_VECTOR_PE0_636, /* 636 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_637
  INT_VECTOR_PE0_637, /* 637 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_638
  INT_VECTOR_PE0_638, /* 638 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_639
  INT_VECTOR_PE0_639, /* 639 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_640
  INT_VECTOR_PE0_640, /* 640 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_641
  INT_VECTOR_PE0_641, /* 641 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_642
  INT_VECTOR_PE0_642, /* 642 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_643
  INT_VECTOR_PE0_643, /* 643 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_644
  INT_VECTOR_PE0_644, /* 644 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_645
  INT_VECTOR_PE0_645, /* 645 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_646
  INT_VECTOR_PE0_646, /* 646 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_647
  INT_VECTOR_PE0_647, /* 647 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_648
  INT_VECTOR_PE0_648, /* 648 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_649
  INT_VECTOR_PE0_649, /* 649 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_650
  INT_VECTOR_PE0_650, /* 650 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_651
  INT_VECTOR_PE0_651, /* 651 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_652
  INT_VECTOR_PE0_652, /* 652 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_653
  INT_VECTOR_PE0_653, /* 653 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_654
  INT_VECTOR_PE0_654, /* 654 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_655
  INT_VECTOR_PE0_655, /* 655 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_656
  INT_VECTOR_PE0_656, /* 656 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_657
  INT_VECTOR_PE0_657, /* 657 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_658
  INT_VECTOR_PE0_658, /* 658 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_659
  INT_VECTOR_PE0_659, /* 659 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_660
  INT_VECTOR_PE0_660, /* 660 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_661
  INT_VECTOR_PE0_661, /* 661 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_662
  INT_VECTOR_PE0_662, /* 662 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_663
  INT_VECTOR_PE0_663, /* 663 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_664
  INT_VECTOR_PE0_664, /* 664 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_665
  INT_VECTOR_PE0_665, /* 665 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_666
  INT_VECTOR_PE0_666, /* 666 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_667
  INT_VECTOR_PE0_667, /* 667 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_668
  INT_VECTOR_PE0_668, /* 668 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_669
  INT_VECTOR_PE0_669, /* 669 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_670
  INT_VECTOR_PE0_670, /* 670 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_671
  INT_VECTOR_PE0_671, /* 671 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_672
  INT_VECTOR_PE0_672, /* 672 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_673
  INT_VECTOR_PE0_673, /* 673 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_674
  INT_VECTOR_PE0_674, /* 674 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_675
  INT_VECTOR_PE0_675, /* 675 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_676
  INT_VECTOR_PE0_676, /* 676 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_677
  INT_VECTOR_PE0_677, /* 677 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_678
  INT_VECTOR_PE0_678, /* 678 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_679
  INT_VECTOR_PE0_679, /* 679 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_680
  INT_VECTOR_PE0_680, /* 680 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_681
  INT_VECTOR_PE0_681, /* 681 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_682
  INT_VECTOR_PE0_682, /* 682 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_683
  INT_VECTOR_PE0_683, /* 683 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_684
  INT_VECTOR_PE0_684, /* 684 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_685
  INT_VECTOR_PE0_685, /* 685 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_686
  INT_VECTOR_PE0_686, /* 686 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_687
  INT_VECTOR_PE0_687, /* 687 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_688
  INT_VECTOR_PE0_688, /* 688 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_689
  INT_VECTOR_PE0_689, /* 689 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_690
  INT_VECTOR_PE0_690, /* 690 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_691
  INT_VECTOR_PE0_691, /* 691 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_692
  INT_VECTOR_PE0_692, /* 692 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_693
  INT_VECTOR_PE0_693, /* 693 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_694
  INT_VECTOR_PE0_694, /* 694 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_695
  INT_VECTOR_PE0_695, /* 695 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_696
  INT_VECTOR_PE0_696, /* 696 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_697
  INT_VECTOR_PE0_697, /* 697 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_698
  INT_VECTOR_PE0_698, /* 698 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_699
  INT_VECTOR_PE0_699, /* 699 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_700
  INT_VECTOR_PE0_700, /* 700 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_701
  INT_VECTOR_PE0_701, /* 701 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_702
  INT_VECTOR_PE0_702, /* 702 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_703
  INT_VECTOR_PE0_703, /* 703 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_704
  INT_VECTOR_PE0_704, /* 704 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_705
  INT_VECTOR_PE0_705, /* 705 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_706
  INT_VECTOR_PE0_706, /* 706 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_707
  INT_VECTOR_PE0_707, /* 707 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_708
  INT_VECTOR_PE0_708, /* 708 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_709
  INT_VECTOR_PE0_709, /* 709 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_710
  INT_VECTOR_PE0_710, /* 710 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_711
  INT_VECTOR_PE0_711, /* 711 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_712
  INT_VECTOR_PE0_712, /* 712 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_713
  INT_VECTOR_PE0_713, /* 713 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_714
  INT_VECTOR_PE0_714, /* 714 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_715
  INT_VECTOR_PE0_715, /* 715 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_716
  INT_VECTOR_PE0_716, /* 716 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_717
  INT_VECTOR_PE0_717, /* 717 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_718
  INT_VECTOR_PE0_718, /* 718 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_719
  INT_VECTOR_PE0_719, /* 719 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_720
  INT_VECTOR_PE0_720, /* 720 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_721
  INT_VECTOR_PE0_721, /* 721 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_722
  INT_VECTOR_PE0_722, /* 722 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_723
  INT_VECTOR_PE0_723, /* 723 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_724
  INT_VECTOR_PE0_724, /* 724 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_725
  INT_VECTOR_PE0_725, /* 725 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_726
  INT_VECTOR_PE0_726, /* 726 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_727
  INT_VECTOR_PE0_727, /* 727 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_728
  INT_VECTOR_PE0_728, /* 728 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_729
  INT_VECTOR_PE0_729, /* 729 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_730
  INT_VECTOR_PE0_730, /* 730 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_731
  INT_VECTOR_PE0_731, /* 731 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_732
  INT_VECTOR_PE0_732, /* 732 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_733
  INT_VECTOR_PE0_733, /* 733 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_734
  INT_VECTOR_PE0_734, /* 734 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_735
  INT_VECTOR_PE0_735, /* 735 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_736
  INT_VECTOR_PE0_736, /* 736 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_737
  INT_VECTOR_PE0_737, /* 737 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_738
  INT_VECTOR_PE0_738, /* 738 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_739
  INT_VECTOR_PE0_739, /* 739 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_740
  INT_VECTOR_PE0_740, /* 740 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_741
  INT_VECTOR_PE0_741, /* 741 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_742
  INT_VECTOR_PE0_742, /* 742 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_743
  INT_VECTOR_PE0_743, /* 743 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_744
  INT_VECTOR_PE0_744, /* 744 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_745
  INT_VECTOR_PE0_745, /* 745 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_746
  INT_VECTOR_PE0_746, /* 746 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_747
  INT_VECTOR_PE0_747, /* 747 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_748
  INT_VECTOR_PE0_748, /* 748 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_749
  INT_VECTOR_PE0_749, /* 749 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_750
  INT_VECTOR_PE0_750, /* 750 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_751
  INT_VECTOR_PE0_751, /* 751 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_752
  INT_VECTOR_PE0_752, /* 752 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_753
  INT_VECTOR_PE0_753, /* 753 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_754
  INT_VECTOR_PE0_754, /* 754 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_755
  INT_VECTOR_PE0_755, /* 755 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_756
  INT_VECTOR_PE0_756, /* 756 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_757
  INT_VECTOR_PE0_757, /* 757 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_758
  INT_VECTOR_PE0_758, /* 758 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_759
  INT_VECTOR_PE0_759, /* 759 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_760
  INT_VECTOR_PE0_760, /* 760 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_761
  INT_VECTOR_PE0_761, /* 761 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_762
  INT_VECTOR_PE0_762, /* 762 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_763
  INT_VECTOR_PE0_763, /* 763 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_764
  INT_VECTOR_PE0_764, /* 764 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_765
  INT_VECTOR_PE0_765, /* 765 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_766
  INT_VECTOR_PE0_766, /* 766 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_767
  INT_VECTOR_PE0_767, /* 767 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_768
  INT_VECTOR_PE0_768, /* 768 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_769
  INT_VECTOR_PE0_769, /* 769 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_770
  INT_VECTOR_PE0_770, /* 770 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_771
  INT_VECTOR_PE0_771, /* 771 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_772
  INT_VECTOR_PE0_772, /* 772 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_773
  INT_VECTOR_PE0_773, /* 773 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_774
  INT_VECTOR_PE0_774, /* 774 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_775
  INT_VECTOR_PE0_775, /* 775 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_776
  INT_VECTOR_PE0_776, /* 776 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_777
  INT_VECTOR_PE0_777, /* 777 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_778
  INT_VECTOR_PE0_778, /* 778 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_779
  INT_VECTOR_PE0_779, /* 779 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_780
  INT_VECTOR_PE0_780, /* 780 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_781
  INT_VECTOR_PE0_781, /* 781 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_782
  INT_VECTOR_PE0_782, /* 782 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_783
  INT_VECTOR_PE0_783, /* 783 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_784
  INT_VECTOR_PE0_784, /* 784 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_785
  INT_VECTOR_PE0_785, /* 785 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_786
  INT_VECTOR_PE0_786, /* 786 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_787
  INT_VECTOR_PE0_787, /* 787 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_788
  INT_VECTOR_PE0_788, /* 788 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_789
  INT_VECTOR_PE0_789, /* 789 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_790
  INT_VECTOR_PE0_790, /* 790 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_791
  INT_VECTOR_PE0_791, /* 791 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_792
  INT_VECTOR_PE0_792, /* 792 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_793
  INT_VECTOR_PE0_793, /* 793 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_794
  INT_VECTOR_PE0_794, /* 794 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_795
  INT_VECTOR_PE0_795, /* 795 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_796
  INT_VECTOR_PE0_796, /* 796 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_797
  INT_VECTOR_PE0_797, /* 797 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_798
  INT_VECTOR_PE0_798, /* 798 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_799
  INT_VECTOR_PE0_799, /* 799 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_800
  INT_VECTOR_PE0_800, /* 800 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_801
  INT_VECTOR_PE0_801, /* 801 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_802
  INT_VECTOR_PE0_802, /* 802 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_803
  INT_VECTOR_PE0_803, /* 803 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_804
  INT_VECTOR_PE0_804, /* 804 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_805
  INT_VECTOR_PE0_805, /* 805 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_806
  INT_VECTOR_PE0_806, /* 806 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_807
  INT_VECTOR_PE0_807, /* 807 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_808
  INT_VECTOR_PE0_808, /* 808 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_809
  INT_VECTOR_PE0_809, /* 809 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_810
  INT_VECTOR_PE0_810, /* 810 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_811
  INT_VECTOR_PE0_811, /* 811 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_812
  INT_VECTOR_PE0_812, /* 812 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_813
  INT_VECTOR_PE0_813, /* 813 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_814
  INT_VECTOR_PE0_814, /* 814 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_815
  INT_VECTOR_PE0_815, /* 815 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_816
  INT_VECTOR_PE0_816, /* 816 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_817
  INT_VECTOR_PE0_817, /* 817 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_818
  INT_VECTOR_PE0_818, /* 818 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_819
  INT_VECTOR_PE0_819, /* 819 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_820
  INT_VECTOR_PE0_820, /* 820 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_821
  INT_VECTOR_PE0_821, /* 821 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_822
  INT_VECTOR_PE0_822, /* 822 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_823
  INT_VECTOR_PE0_823, /* 823 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_824
  INT_VECTOR_PE0_824, /* 824 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_825
  INT_VECTOR_PE0_825, /* 825 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_826
  INT_VECTOR_PE0_826, /* 826 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_827
  INT_VECTOR_PE0_827, /* 827 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_828
  INT_VECTOR_PE0_828, /* 828 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_829
  INT_VECTOR_PE0_829, /* 829 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_830
  INT_VECTOR_PE0_830, /* 830 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_831
  INT_VECTOR_PE0_831, /* 831 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_832
  INT_VECTOR_PE0_832, /* 832 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_833
  INT_VECTOR_PE0_833, /* 833 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_834
  INT_VECTOR_PE0_834, /* 834 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_835
  INT_VECTOR_PE0_835, /* 835 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_836
  INT_VECTOR_PE0_836, /* 836 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_837
  INT_VECTOR_PE0_837, /* 837 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_838
  INT_VECTOR_PE0_838, /* 838 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_839
  INT_VECTOR_PE0_839, /* 839 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_840
  INT_VECTOR_PE0_840, /* 840 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_841
  INT_VECTOR_PE0_841, /* 841 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_842
  INT_VECTOR_PE0_842, /* 842 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_843
  INT_VECTOR_PE0_843, /* 843 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_844
  INT_VECTOR_PE0_844, /* 844 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_845
  INT_VECTOR_PE0_845, /* 845 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_846
  INT_VECTOR_PE0_846, /* 846 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_847
  INT_VECTOR_PE0_847, /* 847 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_848
  INT_VECTOR_PE0_848, /* 848 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_849
  INT_VECTOR_PE0_849, /* 849 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_850
  INT_VECTOR_PE0_850, /* 850 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_851
  INT_VECTOR_PE0_851, /* 851 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_852
  INT_VECTOR_PE0_852, /* 852 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_853
  INT_VECTOR_PE0_853, /* 853 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_854
  INT_VECTOR_PE0_854, /* 854 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_855
  INT_VECTOR_PE0_855, /* 855 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_856
  INT_VECTOR_PE0_856, /* 856 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_857
  INT_VECTOR_PE0_857, /* 857 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_858
  INT_VECTOR_PE0_858, /* 858 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_859
  INT_VECTOR_PE0_859, /* 859 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_860
  INT_VECTOR_PE0_860, /* 860 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_861
  INT_VECTOR_PE0_861, /* 861 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_862
  INT_VECTOR_PE0_862, /* 862 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_863
  INT_VECTOR_PE0_863, /* 863 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_864
  INT_VECTOR_PE0_864, /* 864 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_865
  INT_VECTOR_PE0_865, /* 865 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_866
  INT_VECTOR_PE0_866, /* 866 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_867
  INT_VECTOR_PE0_867, /* 867 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_868
  INT_VECTOR_PE0_868, /* 868 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_869
  INT_VECTOR_PE0_869, /* 869 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_870
  INT_VECTOR_PE0_870, /* 870 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_871
  INT_VECTOR_PE0_871, /* 871 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_872
  INT_VECTOR_PE0_872, /* 872 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_873
  INT_VECTOR_PE0_873, /* 873 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_874
  INT_VECTOR_PE0_874, /* 874 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_875
  INT_VECTOR_PE0_875, /* 875 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_876
  INT_VECTOR_PE0_876, /* 876 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_877
  INT_VECTOR_PE0_877, /* 877 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_878
  INT_VECTOR_PE0_878, /* 878 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_879
  INT_VECTOR_PE0_879, /* 879 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_880
  INT_VECTOR_PE0_880, /* 880 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_881
  INT_VECTOR_PE0_881, /* 881 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_882
  INT_VECTOR_PE0_882, /* 882 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_883
  INT_VECTOR_PE0_883, /* 883 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_884
  INT_VECTOR_PE0_884, /* 884 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_885
  INT_VECTOR_PE0_885, /* 885 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_886
  INT_VECTOR_PE0_886, /* 886 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_887
  INT_VECTOR_PE0_887, /* 887 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_888
  INT_VECTOR_PE0_888, /* 888 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_889
  INT_VECTOR_PE0_889, /* 889 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_890
  INT_VECTOR_PE0_890, /* 890 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_891
  INT_VECTOR_PE0_891, /* 891 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_892
  INT_VECTOR_PE0_892, /* 892 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_893
  INT_VECTOR_PE0_893, /* 893 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_894
  INT_VECTOR_PE0_894, /* 894 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_895
  INT_VECTOR_PE0_895, /* 895 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_896
  INT_VECTOR_PE0_896, /* 896 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_897
  INT_VECTOR_PE0_897, /* 897 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_898
  INT_VECTOR_PE0_898, /* 898 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_899
  INT_VECTOR_PE0_899, /* 899 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_900
  INT_VECTOR_PE0_900, /* 900 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_901
  INT_VECTOR_PE0_901, /* 901 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_902
  INT_VECTOR_PE0_902, /* 902 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_903
  INT_VECTOR_PE0_903, /* 903 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_904
  INT_VECTOR_PE0_904, /* 904 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_905
  INT_VECTOR_PE0_905, /* 905 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_906
  INT_VECTOR_PE0_906, /* 906 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_907
  INT_VECTOR_PE0_907, /* 907 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_908
  INT_VECTOR_PE0_908, /* 908 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_909
  INT_VECTOR_PE0_909, /* 909 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_910
  INT_VECTOR_PE0_910, /* 910 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_911
  INT_VECTOR_PE0_911, /* 911 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_912
  INT_VECTOR_PE0_912, /* 912 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_913
  INT_VECTOR_PE0_913, /* 913 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_914
  INT_VECTOR_PE0_914, /* 914 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_915
  INT_VECTOR_PE0_915, /* 915 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_916
  INT_VECTOR_PE0_916, /* 916 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_917
  INT_VECTOR_PE0_917, /* 917 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_918
  INT_VECTOR_PE0_918, /* 918 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_919
  INT_VECTOR_PE0_919, /* 919 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_920
  INT_VECTOR_PE0_920, /* 920 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_921
  INT_VECTOR_PE0_921, /* 921 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_922
  INT_VECTOR_PE0_922, /* 922 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_923
  INT_VECTOR_PE0_923, /* 923 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_924
  INT_VECTOR_PE0_924, /* 924 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_925
  INT_VECTOR_PE0_925, /* 925 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_926
  INT_VECTOR_PE0_926, /* 926 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_927
  INT_VECTOR_PE0_927, /* 927 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_928
  INT_VECTOR_PE0_928, /* 928 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_929
  INT_VECTOR_PE0_929, /* 929 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_930
  INT_VECTOR_PE0_930, /* 930 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_931
  INT_VECTOR_PE0_931, /* 931 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_932
  INT_VECTOR_PE0_932, /* 932 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_933
  INT_VECTOR_PE0_933, /* 933 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_934
  INT_VECTOR_PE0_934, /* 934 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_935
  INT_VECTOR_PE0_935, /* 935 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_936
  INT_VECTOR_PE0_936, /* 936 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_937
  INT_VECTOR_PE0_937, /* 937 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_938
  INT_VECTOR_PE0_938, /* 938 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_939
  INT_VECTOR_PE0_939, /* 939 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_940
  INT_VECTOR_PE0_940, /* 940 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_941
  INT_VECTOR_PE0_941, /* 941 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_942
  INT_VECTOR_PE0_942, /* 942 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_943
  INT_VECTOR_PE0_943, /* 943 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_944
  INT_VECTOR_PE0_944, /* 944 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_945
  INT_VECTOR_PE0_945, /* 945 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_946
  INT_VECTOR_PE0_946, /* 946 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_947
  INT_VECTOR_PE0_947, /* 947 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_948
  INT_VECTOR_PE0_948, /* 948 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_949
  INT_VECTOR_PE0_949, /* 949 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_950
  INT_VECTOR_PE0_950, /* 950 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_951
  INT_VECTOR_PE0_951, /* 951 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_952
  INT_VECTOR_PE0_952, /* 952 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_953
  INT_VECTOR_PE0_953, /* 953 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_954
  INT_VECTOR_PE0_954, /* 954 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_955
  INT_VECTOR_PE0_955, /* 955 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_956
  INT_VECTOR_PE0_956, /* 956 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_957
  INT_VECTOR_PE0_957, /* 957 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_958
  INT_VECTOR_PE0_958, /* 958 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_959
  INT_VECTOR_PE0_959, /* 959 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_960
  INT_VECTOR_PE0_960, /* 960 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_961
  INT_VECTOR_PE0_961, /* 961 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_962
  INT_VECTOR_PE0_962, /* 962 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_963
  INT_VECTOR_PE0_963, /* 963 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_964
  INT_VECTOR_PE0_964, /* 964 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_965
  INT_VECTOR_PE0_965, /* 965 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_966
  INT_VECTOR_PE0_966, /* 966 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_967
  INT_VECTOR_PE0_967, /* 967 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_968
  INT_VECTOR_PE0_968, /* 968 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_969
  INT_VECTOR_PE0_969, /* 969 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_970
  INT_VECTOR_PE0_970, /* 970 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_971
  INT_VECTOR_PE0_971, /* 971 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_972
  INT_VECTOR_PE0_972, /* 972 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_973
  INT_VECTOR_PE0_973, /* 973 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_974
  INT_VECTOR_PE0_974, /* 974 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_975
  INT_VECTOR_PE0_975, /* 975 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_976
  INT_VECTOR_PE0_976, /* 976 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_977
  INT_VECTOR_PE0_977, /* 977 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_978
  INT_VECTOR_PE0_978, /* 978 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_979
  INT_VECTOR_PE0_979, /* 979 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_980
  INT_VECTOR_PE0_980, /* 980 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_981
  INT_VECTOR_PE0_981, /* 981 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_982
  INT_VECTOR_PE0_982, /* 982 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_983
  INT_VECTOR_PE0_983, /* 983 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_984
  INT_VECTOR_PE0_984, /* 984 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_985
  INT_VECTOR_PE0_985, /* 985 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_986
  INT_VECTOR_PE0_986, /* 986 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_987
  INT_VECTOR_PE0_987, /* 987 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_988
  INT_VECTOR_PE0_988, /* 988 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_989
  INT_VECTOR_PE0_989, /* 989 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_990
  INT_VECTOR_PE0_990, /* 990 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_991
  INT_VECTOR_PE0_991, /* 991 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_992
  INT_VECTOR_PE0_992, /* 992 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_993
  INT_VECTOR_PE0_993, /* 993 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_994
  INT_VECTOR_PE0_994, /* 994 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_995
  INT_VECTOR_PE0_995, /* 995 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_996
  INT_VECTOR_PE0_996, /* 996 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_997
  INT_VECTOR_PE0_997, /* 997 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_998
  INT_VECTOR_PE0_998, /* 998 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_999
  INT_VECTOR_PE0_999, /* 999 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1000
  INT_VECTOR_PE0_1000, /* 1000 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1001
  INT_VECTOR_PE0_1001, /* 1001 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1002
  INT_VECTOR_PE0_1002, /* 1002 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1003
  INT_VECTOR_PE0_1003, /* 1003 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1004
  INT_VECTOR_PE0_1004, /* 1004 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1005
  INT_VECTOR_PE0_1005, /* 1005 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1006
  INT_VECTOR_PE0_1006, /* 1006 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1007
  INT_VECTOR_PE0_1007, /* 1007 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1008
  INT_VECTOR_PE0_1008, /* 1008 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1009
  INT_VECTOR_PE0_1009, /* 1009 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1010
  INT_VECTOR_PE0_1010, /* 1010 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1011
  INT_VECTOR_PE0_1011, /* 1011 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1012
  INT_VECTOR_PE0_1012, /* 1012 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1013
  INT_VECTOR_PE0_1013, /* 1013 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1014
  INT_VECTOR_PE0_1014, /* 1014 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1015
  INT_VECTOR_PE0_1015, /* 1015 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1016
  INT_VECTOR_PE0_1016, /* 1016 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1017
  INT_VECTOR_PE0_1017, /* 1017 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1018
  INT_VECTOR_PE0_1018, /* 1018 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1019
  INT_VECTOR_PE0_1019, /* 1019 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1020
  INT_VECTOR_PE0_1020, /* 1020 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1021
  INT_VECTOR_PE0_1021, /* 1021 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1022
  INT_VECTOR_PE0_1022, /* 1022 */
#else
  Dummy,
#endif
#ifdef INT_VECTOR_PE0_1023
  INT_VECTOR_PE0_1023, /* 1023 */
#else
  Dummy,
#endif
};
#pragma ghs section data=default

/******************************************************************************
**                          End of File                                      **
*******************************************************************************/
