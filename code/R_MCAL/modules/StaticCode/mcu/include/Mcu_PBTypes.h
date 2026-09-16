/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2X MCAL Components                                                                 */
/* Module       = Mcu_PBTypes.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of API information.                                                                                      */
/*                                                                                                                    */
/*====================================================================================================================*/
/*                                                                                                                    */
/* Unless otherwise agreed upon in writing between your company and Renesas Electronics Corporation the following     */
/* shall apply!                                                                                                       */
/*                                                                                                                    */
/* Warranty Disclaimer                                                                                                */
/*                                                                                                                    */
/* There is no warranty of any kind whatsoever granted by Renesas. Any warranty is expressly disclaimed and excluded  */
/* by Renesas, either expressed or implied, including but not limited to those for non-infringement of intellectual   */
/* property, merchantability and/or fitness for the particular purpose.                                               */
/*                                                                                                                    */
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s) and/or */
/* the Application.                                                                                                   */
/*                                                                                                                    */
/* Each User is solely responsible for determining the appropriateness of using the Product(s) and assumes all risks  */
/* associated with its exercise of rights under this Agreement, including, but not limited to the risks and costs of  */
/* program errors, compliance with applicable laws, damage to or loss of data, programs or equipment, and             */
/* unavailability or interruption of operations.                                                                      */
/*                                                                                                                    */
/* Limitation of Liability                                                                                            */
/*                                                                                                                    */
/* In no event shall Renesas be liable to the User for any incidental, consequential, indirect, or punitive damage    */
/* (including but not limited to lost profits) regardless of whether such liability is based on breach of contract,   */
/* tort, strict liability, breach of warranties, failure of essential purpose or otherwise and even if advised of the */
/* possibility of such damages. Renesas shall not be liable for any services or products provided by third party      */
/* vendors, developers or consultants identified or referred to the User by Renesas in connection with the Product(s) */
/* and/or the Application.                                                                                            */
/*                                                                                                                    */
/*====================================================================================================================*/
/* Environment:                                                                                                       */
/*              Devices:        X2X                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 2.5.1:  30/06/2025   : Update SW-VERSION for U2Bx Ver22.02.00.001 Release
 * 2.5.0:  30/06/2025   : Update SW-VERSION for U2Ax Ver22.01.00(D) Release
 * 2.4.0:  31/05/2025   : Update SW-VERSION for U2Cx Ver21.01.01 Release
 * 2.3.2:  29/04/2025   : Update SW-VERSION for U2Ax Ver22.00.03 Release
 * 2.3.1:  31/03/2025   : Update SW-VERSION for U2BxE Ver22.00.02 Release
 * 2.3.0:  28/02/2025   : Update SW-VERSION for Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024   : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Release
 * 2.1.2:  31/10/2024   : Update SW-VERSION to 2.1.2
 * 2.1.1:  30/08/2024   : Update SW-VERSION to 2.1.1
 *                        As part of QAC 9.5.0 support, following changes are made:
 *                        - Remove redundant QAC message 1534
 * 2.0.1:  05/10/2023   : Change MCU_AR_R21_11_VERSION to MCU_AR_R22_11_VERSION support for R22-11
 * 2.0.0:  10/07/2023   : Remove redundant QAC message 3472
 *         20/04/2023   : Change MCU_AR_431_VERSION to MCU_AR_R21_11_VERSION support for R21-11
 * 1.4.5:  06/01/2023   : As new Mcu structure:
 *                        - Remove macros MCU_800MHZ, MCU_640MHZ, MCU_480MHZ, MCU_RESC_ECM_RESET_APP_RESET,
*                           MCU_RESC_ECM_RESET_SYS_RESET2, MCU_RESC_SWDT_RESET_APP_RESET,
*                           MCU_RESC_SWDT_RESET_SYS_RESET2, MCU_RESC_ECM_RESET_VALUE, MCU_RESC_ECM_RESET_VALUE,
*                           MCU_RESC_SWDT_RESET_VALUE, MCU_RESC_SWDT_RESET_VALUE, MCU_RESC_SET_VALUE,
*                           MCU_RESC_SET_VALUE, MCU_RST_DISABLE_REG_PROTECT_VALUE, MCU_RST_ENABLE_REG_PROTECT_VALUE,
*                           MCU_EVEN_ODD_MASK, MCU_STBC_DISABLE_REG_PROTECT_VALUE, MCU_STBC_ENABLE_REG_PROTECT_VALUE,
*                           MCU_STBC0STPT_TRANSITION_TO_STOP_VALUE, MCU_STBC0PSC_TRANSITION_TO_DEEPSTOP_VALUE,
*                           MCU_MODE_TRANSITION_WAIT_CNT_NUM, MCU_SW_RESET_ENABLE_VALUE, MCU_RESF_CLEAR
*                         - Add function-like macro MCU_REG_WRITE_PROTECTION, MCU_ADDR_WRITE32
 * 1.4.3:  23/06/2022   : Remove QAC Message 3472
 *         18/06/2022   : Add new macro MCU_SEVEN_WAKEUP, MCU_FOURTEEN_WAKEUP
 *         13/04/2022   : Update SW-VERSION to 1.4.3; remove macro MCU_EIGHTTEEN, MCU_LONG_WORD_THREE,
 *                        MCU_LONG_WORD_FOUR, MCU_LONG_WORD_FIVE, MCU_LONG_WORD_THIRTYTWO, MCU_EIC_REG_NUM_INTC1,
 *                        MCU_EIC_REG_NUM_INTC2, MCU_EIC_INTFLAG_CLR, MCU_DEEPSTOP_TRANSITION_WAIT, MCU_PRESF0,
 *                        MCU_SRES1F0, MCU_SRES1F1, MCU_SRES1F2, MCU_SRES2F0, MCU_SRES2F1, MCU_SRES2F2, MCU_ARESF0,
 *                        MCU_ARESF1, MCU_ARESF2, MCU_ICUMSRESF0, MCU_ICUMARESF0, MCU_WRITE_DATA, MCU_LSB_MASK,
 *                        MCU_MSB_MASK, MCU_LONG_WORD_LSB_MASK, MCU_OPBT11_ADDRESS
 * 1.3.2:  17/10/2021   : Add define for clock frequenccy
 *                        Add define for SBMD pin
 * 1.3.1:  06/07/2021   : Update value for macro MCU_OPBT11_CKDIVMD to get correct value
 *                        from bit 31 to bit 30 (CKDIVMD[1:0]) of OPBT11
*          02/07/2021   : Add QAC message 9.5.0
 *                        Format source code to 120 characters
 *                        Improve Violation tag (remove START/END)
 * 1.2.0:  17/07/2020   : Release
 * 1.1.0:  19/06/2020   : Release
 * 1.0.0:  10/01/2020   : Initial Version
 */
/**********************************************************************************************************************/
#ifndef MCU_PBTYPES_H
#define MCU_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Mcu type declarations */
#include "Mcu_Types.h"
/* Included for the macro declaration of READ ONLY */
#include "rh850_Types.h"

/* Included for the critical section macros */
#if (MCU_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_Mcu.h"
#endif

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MCU_PBTYPES_AR_RELEASE_MAJOR_VERSION    MCU_TYPES_AR_RELEASE_MAJOR_VERSION
#define MCU_PBTYPES_AR_RELEASE_MINOR_VERSION    MCU_TYPES_AR_RELEASE_MINOR_VERSION
#define MCU_PBTYPES_AR_RELEASE_REVISION_VERSION MCU_TYPES_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define MCU_PBTYPES_SW_MAJOR_VERSION            MCU_SW_MAJOR_VERSION
#define MCU_PBTYPES_SW_MINOR_VERSION            MCU_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : MISRA C:2012 Rule-20.10, CERTCCM PRE05                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3472)    : All toplevel uses of this function-like macro look like they could be replaced by            */
/*                       equivalent function calls.                                                                   */
/* Rule                : MISRA C:2012 Dir-4.9                                                                         */
/* JV-01 Justification : This message indicates that a candidate macro may be suitable for replacement by a           */
/*                       function, based on an actual call-site and the arguments passed to it there                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                      SchM Critical Section Protection Macros                                       **
***********************************************************************************************************************/

#if (MCU_CRITICAL_SECTION_PROTECTION == STD_ON)
  #define MCU_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Mcu_##Exclusive_Area()                                  /* PRQA S 0342 # JV-01 */
#else
  #define MCU_ENTER_CRITICAL_SECTION(Exclusive_Area)
#endif

#if (MCU_CRITICAL_SECTION_PROTECTION == STD_ON)
  #define MCU_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Mcu_##Exclusive_Area()                                   /* PRQA S 0342 # JV-01 */
#else
  #define MCU_EXIT_CRITICAL_SECTION(Exclusive_Area)
#endif

/***********************************************************************************************************************
**                                              DEM Report Error Macros                                               **
***********************************************************************************************************************/
#if (MCU_AR_VERSION == MCU_AR_422_VERSION)
  #define MCU_DEM_REPORT_ERROR(EventId, EventStatus) Dem_ReportErrorStatus(EventId, EventStatus)
#elif (MCU_AR_VERSION == MCU_AR_R22_11_VERSION)
  #define MCU_DEM_REPORT_ERROR(EventId, EventStatus) (void)Dem_SetEventStatus(EventId, EventStatus)
#endif
/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* Macros to avoid Magic numbers */
#define MCU_DBTOC_VALUE\
                                      (((uint32)MCU_VENDOR_ID_VALUE << 22U) | \
                                       ((uint32)MCU_MODULE_ID_VALUE << 14U) | \
                                       ((uint32)MCU_SW_MAJOR_VERSION << 8U) | \
                                       ((uint32)MCU_SW_MINOR_VERSION << 3U))

#define MCU_ZERO                     (uint8)0x00

#define MCU_ONE                      (uint8)0x01

#define MCU_TWO                      (uint8)0x02

#define MCU_THREE                    (uint8)0x03

#define MCU_FOUR                     (uint8)0x04

#define MCU_FIVE                     (uint8)0x05

#define MCU_SIX                      (uint8)0x06

#define MCU_SEVEN                    (uint8)0x07

#define MCU_EIGHT                    (uint8)0x08

#define MCU_NINE                     (uint8)0x09

#define MCU_TEN                      (uint8)0x0A

#define MCU_ELEVEN                   (uint8)0x0B

#define MCU_TWELVE                   (uint8)0x0C

#define MCU_THIRTEEN                 (uint8)0x0D

#define MCU_FOURTEEN                 (uint8)0x0E

#define MCU_FIFTEEN                  (uint8)0x0F

#define MCU_SIXTEEN                  (uint8)0x10

#define MCU_SEVENTEEN                (uint8)0x11

#define MCU_NINETEEN                 (uint8)0x13

#define MCU_TWENTY                   (uint8)0x14

#define MCU_TWENTYONE                (uint8)0x15

#define MCU_TWENTYTWO                (uint8)0x16

#define MCU_TWENTYTHREE              (uint8)0x17

#define MCU_TWENTYFOUR               (uint8)0x18

#define MCU_TWENTYFIVE               (uint8)0x19

#define MCU_TWENTYSIX                (uint8)0x1A

#define MCU_TWENTYSEVEN              (uint8)0x1B

#define MCU_TWENTYEIGHT              (uint8)0x1C

#define MCU_TWENTYNINE               (uint8)0x1D

#define MCU_THIRTY                   (uint8)0x1E

#define MCU_THIRTYONE                (uint8)0x1F

#define MCU_THIRTYTWO                (uint8)0x20

#define MCU_LONG_WORD_ZERO           (uint32)0x00000000UL

#define MCU_LONG_WORD_ONE            (uint32)0x00000001UL

#define MCU_LONG_WORD_TWO            (uint32)0x00000002UL

#define MCU_LONG_WORD_EIGHT          (uint32)0x00000008UL

#define MCU_LONG_WORD_SIXTEEN        (uint32)0x00000010UL

#define MCU_TRUE                     (boolean)0x01U

#define MCU_FALSE                    (boolean)0x00U

#define MCU_INITIALIZED              (boolean)0x01U

#define MCU_UNINITIALIZED            (boolean)0x00U

#define MCU_RESERVED                 (uint8)0x00U

/* Definition for Reset source check values */
#define MCU_ZERO_BIT                   (uint32)0x00000001UL
#define MCU_ONE_BIT                    (uint32)0x00000002UL
#define MCU_TWO_BIT                    (uint32)0x00000004UL
#define MCU_THREE_BIT                  (uint32)0x00000008UL
#define MCU_FOUR_BIT                   (uint32)0x00000010UL
#define MCU_FIVE_BIT                   (uint32)0x00000020UL
#define MCU_SIX_BIT                    (uint32)0x00000040UL
#define MCU_SEVEN_BIT                  (uint32)0x00000080UL
#define MCU_EIGHT_BIT                  (uint32)0x00000100UL
#define MCU_NINE_BIT                   (uint32)0x00000200UL
#define MCU_TEN_BIT                    (uint32)0x00000400UL
#define MCU_ELEVEN_BIT                 (uint32)0x00000800UL
#define MCU_TWELVE_BIT                 (uint32)0x00001000UL
#define MCU_THIRTEEN_BIT               (uint32)0x00002000UL
#define MCU_FOURTEEN_BIT               (uint32)0x00004000UL
#define MCU_FIFTEEN_BIT                (uint32)0x00008000UL
#define MCU_SIXTEEN_BIT                (uint32)0x00010000UL
#define MCU_SEVENTEEN_BIT              (uint32)0x00020000UL
#define MCU_EIGHTEEN_BIT               (uint32)0x00040000UL
#define MCU_NINETEEN_BIT               (uint32)0x00080000UL
#define MCU_TWENTY_BIT                 (uint32)0x00100000UL
#define MCU_TWENTYONE_BIT              (uint32)0x00200000UL
#define MCU_TWENTYTWO_BIT              (uint32)0x00400000UL
#define MCU_TWENTYTHREE_BIT            (uint32)0x00800000UL
#define MCU_TWENTYFOUR_BIT             (uint32)0x01000000UL
#define MCU_TWENTYFIVE_BIT             (uint32)0x02000000UL
#define MCU_TWENTYSIX_BIT              (uint32)0x04000000UL
#define MCU_TWENTYSEVEN_BIT            (uint32)0x08000000UL
#define MCU_TWENTYEIGHT_BIT            (uint32)0x10000000UL
#define MCU_TWENTYNINE_BIT             (uint32)0x20000000UL
#define MCU_THIRTY_BIT                 (uint32)0x40000000UL
#define MCU_THIRTYONE_BIT              (uint32)0x80000000UL

/* CLK_PLLO Divider Control Register */
#define MCU_OPBT11         (*((volatile uint32 *)0xFF320BCCUL))

/* OPBT11.CKDIVMD */
#define MCU_OPBT11_CKDIVMD MCU_OPBT11 >> (uint32)0x1E

#define MCU_ADDR_WRITE32(Address, Data) ((*((volatile uint32*)(Address))) = (Data))                                     /* PRQA S 3472 # JV-01 */

#define MCU_REG_WRITE_PROTECTION(PProReg, PDisVal, PEnaVal, PWriReg, WriVal) \
           MCU_ADDR_WRITE32(PProReg, PDisVal); \
           MCU_ADDR_WRITE32(PWriReg, WriVal); \
           MCU_ADDR_WRITE32(PProReg, PEnaVal)
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                        Extern declarations for Global Data                                         **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* MCU_PBTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
