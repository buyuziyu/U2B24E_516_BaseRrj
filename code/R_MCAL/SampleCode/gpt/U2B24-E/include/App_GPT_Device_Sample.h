/*============================================================================*/
/* Project      = RH850/U2Bx,U2Cx MCAL Ver21.00.00.D                          */
/* Module       = App_GPT_Device_Sample.h                                     */
/*============================================================================*/
/*                                  COPYRIGHT                                 */
/*============================================================================*/
/* (c) 2024, 2025 Renesas Electronics Corporation. All rights reserved.       */
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
/*              Devices:        U2B24-E                                       */
/*============================================================================*/

/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 *  2.3.1  31/03/2025  : Update register address for EIC86
 *                       Add BEID address to map interupt to PE6
 *  2.3.0  28/02/2025  : As part of GTM HWIP support, following changes are made
 *                       Add EIC, Standby Controller register for GTM
 *  2.2.0  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D
 *                       Final Release
 *  2.1.2  31/10/2024  : Update SW-VERSION for U2Bx Beta2 release
 *  2.0.3  29/04/2024  : Initial Version
 */
/******************************************************************************/
#ifndef APP_GPT_DEVICE_SAMPLE_H
#define APP_GPT_DEVICE_SAMPLE_H


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define NUMBER_ICR_COUNT    149

/*
 * Register Definitions for PBUS Guards Register (PBG0B)
 */
#define FSGD0BPROT0         (*((volatile uint32 *)0xFFC4C000UL))

/* Standby Controller setting */
#define MSR_TAUD            (*((volatile uint32 *)0xFF981130UL))
#define MSR_TAUJ_AWO        (*((volatile uint32 *)0xFF988E20UL))
#define MSR_OSTM            (*((volatile uint32 *)0xFF981180UL))
#define MSR_ATU             (*((volatile uint32 *)0xFF9811B0UL))
#define MSRKCPROT           (*((volatile uint32 *)0xFF981710UL))
#define GTM0CMUCLKEN        (*((volatile uint32 *)0xff600080UL))
#define MSR_GTM             (*((volatile uint32 *)0xff981020UL))

/* clock setting */
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
#define CKS_CLEANC          (*((volatile unsigned long *)0xFF980100UL)) /* CLK_SYS_CLEAN Selector Control Register */
#define CKS_CLEANS          (*((volatile unsigned long *)0xFF980108UL)) /* CLK_SYS_CLEAN Selector Status Register */
#define CLKD_PLLC           (*((volatile unsigned long *)0xFF980120UL)) /* CLK_PLLO Divider Control Register */
#define CLKD_PLLS           (*((volatile unsigned long *)0xFF980128UL)) /* CLK_PLLO Divider Status Register */
#define CKSC_WDTC           (*((volatile unsigned long *)0xFF980300UL)) /* CLK_WDT Selector Control Register */
#define CKSC_WDTS           (*((volatile unsigned long *)0xFF980308UL)) /* CLK_WDT Selector Status Register */
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
#define CLKKCPROT1          (*((volatile unsigned long *)0xFF980700UL)) /* Clock Controller Register Key Code Protection
                                                                                                           Register 1 */
#define CLKKCPROT2          (*((volatile unsigned long *)0xFF980710UL)) /* Clock Controller Register Key Code Protection
                                                                                                           Register 2 */
#define CLKKCPROT3          (*((volatile unsigned long *)0xFF980720UL)) /* Clock Controller Register Key Code Protection
                                                                                                           Register 3 */

/* intrrupt setting */
#define EIC10               (*((volatile uint16 *)0xFFFC4014UL)) /* INTTAUD0I0 */
#define EIC11               (*((volatile uint16 *)0xFFFC4016UL)) /* INTTAUD0I2 */
#define EIC12               (*((volatile uint16 *)0xFFFC4018UL)) /* INTTAUD0I4 */
#define EIC13               (*((volatile uint16 *)0xFFFC401AUL)) /* INTTAUD0I6 */
#define EIC23               (*((volatile uint16 *)0xFFFC402EUL)) /* INTTAUD0I8 */
#define EIC24               (*((volatile uint16 *)0xFFFC4030UL)) /* INTTAUD0I10 */
#define EIC25               (*((volatile uint16 *)0xFFFC4032UL)) /* INTTAUD0I12 */
#define EIC26               (*((volatile uint16 *)0xFFFC4034UL)) /* INTTAUD0I14 */
#define EIC360              (*((volatile uint16 *)0xFFF802D0UL)) /* INTOSTM0TINT */
#define EIC361              (*((volatile uint16 *)0xFFF802D2UL)) /* INTOSTM1TINT */
#define EIC841              (*((volatile uint16 *)0xFFF80692UL)) /* INTOSTM2TINT */
#define EIC842              (*((volatile uint16 *)0xFFF80694UL)) /* INTOSTM3TINT */
#define EIC968              (*((volatile uint16 *)0xFFF80790UL)) /* INTOSTM4TINT */
#define EIC969              (*((volatile uint16 *)0xFFF80792UL)) /* INTOSTM5TINT */
#define EIC960              (*((volatile uint16 *)0xFFF80780UL)) /* INTTAUJ2I0 */
#define EIC961              (*((volatile uint16 *)0xFFF80782UL)) /* INTTAUJ2I1 */
#define EIC962              (*((volatile uint16 *)0xFFF80784UL)) /* INTTAUJ2I2 */
#define EIC963              (*((volatile uint16 *)0xFFF80786UL)) /* INTTAUJ2I3 */
#define EIC964              (*((volatile uint16 *)0xFFF80788UL)) /* INTTAUJ3I0 */
#define EIC965              (*((volatile uint16 *)0xFFF8078AUL)) /* INTTAUJ3I1 */
#define EIC966              (*((volatile uint16 *)0xFFF8078CUL)) /* INTTAUJ3I2 */
#define EIC967              (*((volatile uint16 *)0xFFF8078EUL)) /* INTTAUJ3I3 */
#define EIC320              (*((volatile uint16 *)0xFFF80280UL)) /* INTTAUD0I1 */
#define EIC321              (*((volatile uint16 *)0xFFF80282UL)) /* INTTAUD0I3 */
#define EIC322              (*((volatile uint16 *)0xFFF80284UL)) /* INTTAUD0I5 */
#define EIC323              (*((volatile uint16 *)0xFFF80286UL)) /* INTTAUD0I7 */
#define EIC324              (*((volatile uint16 *)0xFFF80288UL)) /* INTTAUD0I9 */
#define EIC325              (*((volatile uint16 *)0xFFF8028AUL)) /* INTTAUD0I11 */
#define EIC326              (*((volatile uint16 *)0xFFF8028CUL)) /* INTTAUD0I13 */
#define EIC327              (*((volatile uint16 *)0xFFF8028EUL)) /* INTTAUD0I15 */
#define EIC328              (*((volatile uint16 *)0xFFF80290UL)) /* INTTAUD1I0 */
#define EIC329              (*((volatile uint16 *)0xFFF80292UL)) /* INTTAUD1I1 */
#define EIC330              (*((volatile uint16 *)0xFFF80294UL)) /* INTTAUD1I2 */
#define EIC331              (*((volatile uint16 *)0xFFF80296UL)) /* INTTAUD1I3 */
#define EIC332              (*((volatile uint16 *)0xFFF80298UL)) /* INTTAUD1I4 */
#define EIC333              (*((volatile uint16 *)0xFFF8029AUL)) /* INTTAUD1I5 */
#define EIC334              (*((volatile uint16 *)0xFFF8029CUL)) /* INTTAUD1I6 */
#define EIC335              (*((volatile uint16 *)0xFFF8029EUL)) /* INTTAUD1I7 */
#define EIC336              (*((volatile uint16 *)0xFFF802A0UL)) /* INTTAUD1I8 */
#define EIC337              (*((volatile uint16 *)0xFFF802A2UL)) /* INTTAUD1I9 */
#define EIC338              (*((volatile uint16 *)0xFFF802A4UL)) /* INTTAUD1I10 */
#define EIC339              (*((volatile uint16 *)0xFFF802A6UL)) /* INTTAUD1I11 */
#define EIC340              (*((volatile uint16 *)0xFFF802A8UL)) /* INTTAUD1I12 */
#define EIC341              (*((volatile uint16 *)0xFFF802AAUL)) /* INTTAUD1I13 */
#define EIC342              (*((volatile uint16 *)0xFFF802ACUL)) /* INTTAUD1I14 */
#define EIC343              (*((volatile uint16 *)0xFFF802AEUL)) /* INTTAUD1I15 */
#define EIC344              (*((volatile uint16 *)0xFFF802B0UL)) /* INTTAUD2I0 */
#define EIC345              (*((volatile uint16 *)0xFFF802B2UL)) /* INTTAUD2I1 */
#define EIC346              (*((volatile uint16 *)0xFFF802B4UL)) /* INTTAUD2I2 */
#define EIC347              (*((volatile uint16 *)0xFFF802B6UL)) /* INTTAUD2I3 */
#define EIC348              (*((volatile uint16 *)0xFFF802B8UL)) /* INTTAUD2I4 */
#define EIC349              (*((volatile uint16 *)0xFFF802BAUL)) /* INTTAUD2I5 */
#define EIC350              (*((volatile uint16 *)0xFFF802BCUL)) /* INTTAUD2I6 */
#define EIC351              (*((volatile uint16 *)0xFFF802BEUL)) /* INTTAUD2I7 */
#define EIC352              (*((volatile uint16 *)0xFFF802C0UL)) /* INTTAUD2I8 */
#define EIC353              (*((volatile uint16 *)0xFFF802C2UL)) /* INTTAUD2I9 */
#define EIC354              (*((volatile uint16 *)0xFFF802C4UL)) /* INTTAUD2I10 */
#define EIC355              (*((volatile uint16 *)0xFFF802C6UL)) /* INTTAUD2I11 */
#define EIC356              (*((volatile uint16 *)0xFFF802C8UL)) /* INTTAUD2I12 */
#define EIC357              (*((volatile uint16 *)0xFFF802CAUL)) /* INTTAUD2I13 */
#define EIC358              (*((volatile uint16 *)0xFFF802CCUL)) /* INTTAUD2I14 */
#define EIC359              (*((volatile uint16 *)0xFFF802CEUL)) /* INTTAUD2I15 */
/* TAUD3 - Interrupt selection bit 001*/
#define EIC379              (*((volatile uint16 *)0xfff802f6UL)) /* INTTAUD3I0 */
#define EIC380              (*((volatile uint16 *)0xfff802f8UL)) /* INTTAUD3I1 */
#define EIC381              (*((volatile uint16 *)0xfff802faUL)) /* INTTAUD3I2 */
#define EIC382              (*((volatile uint16 *)0xfff802fcUL)) /* INTTAUD3I3 */
#define EIC383              (*((volatile uint16 *)0xfff802feUL)) /* INTTAUD3I4 */
#define EIC384              (*((volatile uint16 *)0xfff80300UL)) /* INTTAUD3I5 */
#define EIC385              (*((volatile uint16 *)0xfff80302UL)) /* INTTAUD3I6 */
#define EIC386              (*((volatile uint16 *)0xfff80304UL)) /* INTTAUD3I7 */
#define EIC387              (*((volatile uint16 *)0xfff80306UL)) /* INTTAUD3I8 */
#define EIC388              (*((volatile uint16 *)0xfff80308UL)) /* INTTAUD3I9 */
#define EIC389              (*((volatile uint16 *)0xfff8030aUL)) /* INTTAUD3I10 */
#define EIC390              (*((volatile uint16 *)0xfff8030cUL)) /* INTTAUD3I11 */
#define EIC391              (*((volatile uint16 *)0xfff8030eUL)) /* INTTAUD3I12 */
#define EIC392              (*((volatile uint16 *)0xfff80310UL)) /* INTTAUD3I13 */
#define EIC393              (*((volatile uint16 *)0xfff80312UL)) /* INTTAUD3I14 */
#define EIC394              (*((volatile uint16 *)0xfff80314UL)) /* INTTAUD3I15 */

/* TAUD3 - Interrupt selection bit 010*/
#define EIC505              (*((volatile uint16 *)0xFFF803F2UL)) /* INTTAUD3I0 */
#define EIC506              (*((volatile uint16 *)0xFFF803F4UL)) /* INTTAUD3I1 */
#define EIC507              (*((volatile uint16 *)0xFFF803F6UL)) /* INTTAUD3I2 */
#define EIC508              (*((volatile uint16 *)0xFFF803F8UL)) /* INTTAUD3I3 */
#define EIC509              (*((volatile uint16 *)0xFFF803FAUL)) /* INTTAUD3I4 */
#define EIC510              (*((volatile uint16 *)0xFFF803FCUL)) /* INTTAUD3I5 */
#define EIC511              (*((volatile uint16 *)0xFFF803FEUL)) /* INTTAUD3I6 */
#define EIC512              (*((volatile uint16 *)0xFFF80400UL)) /* INTTAUD3I7 */
#define EIC513              (*((volatile uint16 *)0xFFF80402UL)) /* INTTAUD3I8 */
#define EIC514              (*((volatile uint16 *)0xFFF80404UL)) /* INTTAUD3I9 */
#define EIC515              (*((volatile uint16 *)0xFFF80406UL)) /* INTTAUD3I10 */
#define EIC516              (*((volatile uint16 *)0xFFF80408UL)) /* INTTAUD3I11 */
#define EIC517              (*((volatile uint16 *)0xFFF8040AUL)) /* INTTAUD3I12 */
#define EIC518              (*((volatile uint16 *)0xFFF8040CUL)) /* INTTAUD3I13 */
#define EIC519              (*((volatile uint16 *)0xFFF8040EUL)) /* INTTAUD3I14 */
#define EIC520              (*((volatile uint16 *)0xFFF80410UL)) /* INTTAUD3I15 */

/* TAUD3 - Interrupt selection bit 100*/
#define EIC793              (*((volatile uint16 *)0xfff80632UL)) /* INTTAUD3I0 */
#define EIC794              (*((volatile uint16 *)0xfff80634UL)) /* INTTAUD3I1 */
#define EIC795              (*((volatile uint16 *)0xfff80636UL)) /* INTTAUD3I2 */
#define EIC796              (*((volatile uint16 *)0xfff80638UL)) /* INTTAUD3I3 */
#define EIC797              (*((volatile uint16 *)0xfff8063aUL)) /* INTTAUD3I4 */
#define EIC798              (*((volatile uint16 *)0xfff8063cUL)) /* INTTAUD3I5 */
#define EIC799              (*((volatile uint16 *)0xfff8063eUL)) /* INTTAUD3I6 */
#define EIC800              (*((volatile uint16 *)0xfff80640UL)) /* INTTAUD3I7 */
#define EIC801              (*((volatile uint16 *)0xfff80642UL)) /* INTTAUD3I8 */
#define EIC802              (*((volatile uint16 *)0xfff80644UL)) /* INTTAUD3I9 */
#define EIC803              (*((volatile uint16 *)0xfff80646UL)) /* INTTAUD3I10 */
#define EIC804              (*((volatile uint16 *)0xfff80648UL)) /* INTTAUD3I11 */
#define EIC817              (*((volatile uint16 *)0xfff80662UL)) /* INTTAUD3I12 */
#define EIC818              (*((volatile uint16 *)0xfff80664UL)) /* INTTAUD3I13 */
#define EIC819              (*((volatile uint16 *)0xfff80666UL)) /* INTTAUD3I14 */
#define EIC820              (*((volatile uint16 *)0xfff80668UL)) /* INTTAUD3I15 */

#define EIC104              (*((volatile uint16 *)0xFFF800D0UL)) /* INTATU6C000 */
#define EIC105              (*((volatile uint16 *)0xFFF800D2UL)) /* INTATU6C001 */
#define EIC106              (*((volatile uint16 *)0xFFF800D4UL)) /* INTATU6C002 */
#define EIC107              (*((volatile uint16 *)0xFFF800D6UL)) /* INTATU6C003 */
#define EIC108              (*((volatile uint16 *)0xFFF800D8UL)) /* INTATU6C010 */
#define EIC109              (*((volatile uint16 *)0xFFF800DAUL)) /* INTATU6C011 */
#define EIC110              (*((volatile uint16 *)0xFFF800DCUL)) /* INTATU6C012 */
#define EIC111              (*((volatile uint16 *)0xFFF800DEUL)) /* INTATU6C013 */
#define EIC112              (*((volatile uint16 *)0xFFF800E0UL)) /* INTATU6C020 */
#define EIC113              (*((volatile uint16 *)0xFFF800E2UL)) /* INTATU6C021 */
#define EIC114              (*((volatile uint16 *)0xFFF800E4UL)) /* INTATU6C022 */
#define EIC115              (*((volatile uint16 *)0xFFF800E6UL)) /* INTATU6C023 */
#define EIC116              (*((volatile uint16 *)0xFFF800E8UL)) /* INTATU6C030 */
#define EIC117              (*((volatile uint16 *)0xFFF800EAUL)) /* INTATU6C031 */
#define EIC118              (*((volatile uint16 *)0xFFF800ECUL)) /* INTATU6C032 */
#define EIC119              (*((volatile uint16 *)0xFFF800EEUL)) /* INTATU6C033 */
#define EIC120              (*((volatile uint16 *)0xFFF800F0UL)) /* INTATU6C040 */
#define EIC121              (*((volatile uint16 *)0xFFF800F2UL)) /* INTATU6C041 */
#define EIC122              (*((volatile uint16 *)0xFFF800F4UL)) /* INTATU6C042 */
#define EIC123              (*((volatile uint16 *)0xFFF800F6UL)) /* INTATU6C043 */
#define EIC124              (*((volatile uint16 *)0xFFF800F8UL)) /* INTATU6C050 */
#define EIC125              (*((volatile uint16 *)0xFFF800FAUL)) /* INTATU6C051 */
#define EIC126              (*((volatile uint16 *)0xFFF800FCUL)) /* INTATU6C052 */
#define EIC127              (*((volatile uint16 *)0xFFF800FEUL)) /* INTATU6C053 */
#define EIC128              (*((volatile uint16 *)0xFFF80100UL)) /* INTATU6C060 */
#define EIC129              (*((volatile uint16 *)0xFFF80102UL)) /* INTATU6C061 */
#define EIC130              (*((volatile uint16 *)0xFFF80104UL)) /* INTATU6C062 */
#define EIC131              (*((volatile uint16 *)0xFFF80106UL)) /* INTATU6C063 */
#define EIC132              (*((volatile uint16 *)0xFFF80108UL)) /* INTATU6C070 */
#define EIC133              (*((volatile uint16 *)0xFFF8010AUL)) /* INTATU6C071 */
#define EIC134              (*((volatile uint16 *)0xFFF8010CUL)) /* INTATU6C072 */
#define EIC135              (*((volatile uint16 *)0xFFF8010EUL)) /* INTATU6C073 */
#define EIC136              (*((volatile uint16 *)0xFFF80110UL)) /* INTATU6C080 */
#define EIC137              (*((volatile uint16 *)0xFFF80112UL)) /* INTATU6C081 */
#define EIC138              (*((volatile uint16 *)0xFFF80114UL)) /* INTATU6C082 */
#define EIC139              (*((volatile uint16 *)0xFFF80116UL)) /* INTATU6C083 */
#define EIC140              (*((volatile uint16 *)0xFFF80118UL)) /* INTATU6C090 */
#define EIC141              (*((volatile uint16 *)0xFFF8011AUL)) /* INTATU6C091 */
#define EIC142              (*((volatile uint16 *)0xFFF8011CUL)) /* INTATU6C092 */
#define EIC143              (*((volatile uint16 *)0xFFF8011EUL)) /* INTATU6C093 */
#define EIC144              (*((volatile uint16 *)0xFFF80120UL)) /* INTATU6C100 */
#define EIC145              (*((volatile uint16 *)0xFFF80122UL)) /* INTATU6C101 */
#define EIC146              (*((volatile uint16 *)0xFFF80124UL)) /* INTATU6C102 */
#define EIC147              (*((volatile uint16 *)0xFFF80126UL)) /* INTATU6C103 */
#define EIC148              (*((volatile uint16 *)0xFFF80128UL)) /* INTATU6C110 */
#define EIC149              (*((volatile uint16 *)0xFFF8012AUL)) /* INTATU6C111 */
#define EIC150              (*((volatile uint16 *)0xFFF8012CUL)) /* INTATU6C112 */
#define EIC151              (*((volatile uint16 *)0xFFF8012EUL)) /* INTATU6C113 */
#define EIC152              (*((volatile uint16 *)0xFFF80130UL)) /* INTATU6C120 */
#define EIC153              (*((volatile uint16 *)0xFFF80132UL)) /* INTATU6C121 */
#define EIC154              (*((volatile uint16 *)0xFFF80134UL)) /* INTATU6C122 */
#define EIC155              (*((volatile uint16 *)0xFFF80136UL)) /* INTATU6C123 */
#define EIC156              (*((volatile uint16 *)0xFFF80138UL)) /* INTATU6C130 */
#define EIC157              (*((volatile uint16 *)0xFFF8013AUL)) /* INTATU6C131 */
#define EIC158              (*((volatile uint16 *)0xFFF8013CUL)) /* INTATU6C132 */
#define EIC159              (*((volatile uint16 *)0xFFF8013EUL)) /* INTATU6C133 */
#define EIC160              (*((volatile uint16 *)0xFFF80140UL)) /* INTATU6C140 */
#define EIC161              (*((volatile uint16 *)0xFFF80142UL)) /* INTATU6C141 */
#define EIC162              (*((volatile uint16 *)0xFFF80144UL)) /* INTATU6C142 */
#define EIC163              (*((volatile uint16 *)0xFFF80146UL)) /* INTATU6C143 */
#define EIC164              (*((volatile uint16 *)0xFFF80148UL)) /* INTATU6D000 */
#define EIC165              (*((volatile uint16 *)0xFFF8014AUL)) /* INTATU6D001 */
#define EIC166              (*((volatile uint16 *)0xFFF8014CUL)) /* INTATU6D002 */
#define EIC167              (*((volatile uint16 *)0xFFF8014EUL)) /* INTATU6D003 */
#define EIC168              (*((volatile uint16 *)0xFFF80150UL)) /* INTATU6D010 */
#define EIC169              (*((volatile uint16 *)0xFFF80152UL)) /* INTATU6D011 */
#define EIC170              (*((volatile uint16 *)0xFFF80154UL)) /* INTATU6D012 */
#define EIC171              (*((volatile uint16 *)0xFFF80156UL)) /* INTATU6D013 */
#define EIC172              (*((volatile uint16 *)0xFFF80158UL)) /* INTATU6D020 */
#define EIC173              (*((volatile uint16 *)0xFFF8015AUL)) /* INTATU6D021 */
#define EIC174              (*((volatile uint16 *)0xFFF8015CUL)) /* INTATU6D022 */
#define EIC175              (*((volatile uint16 *)0xFFF8015EUL)) /* INTATU6D023 */
#define EIC176              (*((volatile uint16 *)0xFFF80160UL)) /* INTATU6D030 */
#define EIC177              (*((volatile uint16 *)0xFFF80162UL)) /* INTATU6D031 */
#define EIC178              (*((volatile uint16 *)0xFFF80164UL)) /* INTATU6D032 */
#define EIC179              (*((volatile uint16 *)0xFFF80166UL)) /* INTATU6D033 */
#define EIC180              (*((volatile uint16 *)0xFFF80168UL)) /* INTATU6D040 */
#define EIC181              (*((volatile uint16 *)0xFFF8016AUL)) /* INTATU6D041 */
#define EIC182              (*((volatile uint16 *)0xFFF8016CUL)) /* INTATU6D042 */
#define EIC183              (*((volatile uint16 *)0xFFF8016EUL)) /* INTATU6D043 */
#define EIC184              (*((volatile uint16 *)0xFFF80170UL)) /* INTATU6D050 */
#define EIC185              (*((volatile uint16 *)0xFFF80172UL)) /* INTATU6D051 */
#define EIC186              (*((volatile uint16 *)0xFFF80174UL)) /* INTATU6D052 */
#define EIC187              (*((volatile uint16 *)0xFFF80176UL)) /* INTATU6D053 */
#define EIC188              (*((volatile uint16 *)0xFFF80178UL)) /* INTATU6D060 */
#define EIC189              (*((volatile uint16 *)0xFFF8017AUL)) /* INTATU6D061 */
#define EIC190              (*((volatile uint16 *)0xFFF8017CUL)) /* INTATU6D062 */
#define EIC191              (*((volatile uint16 *)0xFFF8017EUL)) /* INTATU6D063 */
#define EIC192              (*((volatile uint16 *)0xFFF80180UL)) /* INTATU6D070 */
#define EIC193              (*((volatile uint16 *)0xFFF80182UL)) /* INTATU6D071 */
#define EIC194              (*((volatile uint16 *)0xFFF80184UL)) /* INTATU6D072 */
#define EIC195              (*((volatile uint16 *)0xFFF80186UL)) /* INTATU6D073 */
#define EIC196              (*((volatile uint16 *)0xFFF80188UL)) /* INTATU6D080 */
#define EIC197              (*((volatile uint16 *)0xFFF8018AUL)) /* INTATU6D081 */
#define EIC198              (*((volatile uint16 *)0xFFF8018CUL)) /* INTATU6D082 */
#define EIC199              (*((volatile uint16 *)0xFFF8018EUL)) /* INTATU6D083 */
#define EIC200              (*((volatile uint16 *)0xFFF80190UL)) /* INTATU6D090 */
#define EIC201              (*((volatile uint16 *)0xFFF80192UL)) /* INTATU6D091 */
#define EIC202              (*((volatile uint16 *)0xFFF80194UL)) /* INTATU6D092 */
#define EIC203              (*((volatile uint16 *)0xFFF80196UL)) /* INTATU6D093 */
#define EIC204              (*((volatile uint16 *)0xFFF80198UL)) /* INTATU6D100 */
#define EIC205              (*((volatile uint16 *)0xFFF8019AUL)) /* INTATU6D101 */
#define EIC206              (*((volatile uint16 *)0xFFF8019CUL)) /* INTATU6D102 */
#define EIC207              (*((volatile uint16 *)0xFFF8019EUL)) /* INTATU6D103 */
#define EIC208              (*((volatile uint16 *)0xFFF801A0UL)) /* INTATU6D110 */
#define EIC209              (*((volatile uint16 *)0xFFF801A2UL)) /* INTATU6D111 */
#define EIC210              (*((volatile uint16 *)0xFFF801A4UL)) /* INTATU6D112 */
#define EIC211              (*((volatile uint16 *)0xFFF801A6UL)) /* INTATU6D113 */
#define EIC272              (*((volatile uint16 *)0xFFF80220UL)) /* INTATU6G000 */
#define EIC273              (*((volatile uint16 *)0xFFF80222UL)) /* INTATU6G010 */
#define EIC274              (*((volatile uint16 *)0xFFF80224UL)) /* INTATU6G020 */
#define EIC275              (*((volatile uint16 *)0xFFF80226UL)) /* INTATU6G030 */
#define EIC276              (*((volatile uint16 *)0xFFF80228UL)) /* INTATU6G040 */
#define EIC277              (*((volatile uint16 *)0xFFF8022AUL)) /* INTATU6G050 */
#define EIC278              (*((volatile uint16 *)0xFFF8022CUL)) /* INTATU6G060 */
#define EIC279              (*((volatile uint16 *)0xFFF8022EUL)) /* INTATU6G070 */
#define EIC280              (*((volatile uint16 *)0xFFF80230UL)) /* INTATU6G080 */
#define EIC281              (*((volatile uint16 *)0xFFF80232UL)) /* INTATU6G090 */
#define EIC282              (*((volatile uint16 *)0xFFF80234UL)) /* INTATU6G100 */
#define EIC283              (*((volatile uint16 *)0xFFF80236UL)) /* INTATU6G110 */
#define EIC284              (*((volatile uint16 *)0xFFF80238UL)) /* INTATU6G120 */
#define EIC285              (*((volatile uint16 *)0xFFF8023AUL)) /* INTATU6G130 */
#define EIC86               (*((volatile uint16 *)0xfff800acUL)) /* INTGTM0IOS000 */
#define EIC102              (*((volatile uint16 *)0xfff800ccUL)) /* INTGTM0IOS100 */

//EIDB: EI Level Interrupt Bind Register
#define INTC2_EIBD360       *(uint32*)(0xFFF825A0UL)
#define INTC2_EIBD361       *(uint32*)(0xFFF825A4UL)
#define INTC2_EIBD841       *(uint32*)(0xfff82d24UL)
#define INTC2_EIBD960       *(uint32*)(0xFFF82F00UL)
#define INTC2_EIBD505       *(uint32*)(0xfff827e4UL)
#define INTC2_EIBD86        *(uint32*)(0xfff82158UL)
#define INTC2_EIBD102       *(uint32*)(0xfff82198UL)
#define INTC2_EIBD379       *(uint32*)(0xfff825ecUL)
#define INTC2_EIBD793       *(uint32*)(0xfff82c64UL)
#define INTC2_EIBD320       *(uint32*)(0xfff82500UL)

/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
#endif /* APP_GPT_DEVICE_SAMPLE_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
