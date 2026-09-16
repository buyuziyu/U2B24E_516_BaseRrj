/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Lin_RLIN3_PBTypes.h                                                                                 */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of all Macros.                                                                                           */
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
/*              Devices:        X2x                                                                                   */
/*====================================================================================================================*/

/***********************************************************************************************************************
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 *
 * 2.4.1:  30/06/2025  : Remove the SW-VERSION from header of file
 *                       Remove QAC message 4641
 * 2.3.2:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 * 2.3.1:  31/03/2025  : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release 
 *                       Add new QAC message 4641
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00(D) U2Bx Final Release
 * 2.1.2:  31/10/2024  : As part of QAC 9.5.0 support, following changes are made:
 *                       1. Update SW-VERSION to 2.1.2
 *                       2. Remove redundant QAC message 1534 and 1536 
 * 2.0.1:  21/10/2023  : Add new QAC message 1534 and 1536 and remove redundant macro LIN_ERROR_INTERRUPT
 * 2.0.0:  18/07/2023  : Add new macro "LIN_INVALID_CORE"
 *         20/06/2023  : Add macro LIN_DATA1RX_DONE
 * 1.5.0:  06/04/2023  : Add macro for support AR21-11:
 *                       LIN_START_RESPONSE, LIN_NO_RESPONSE, LIN_MASTER_ENABLE_INTERRUPT, LIN_SLAVE_ENABLE_INTERRUPT,
 *                       LIN_ERROR_FREE, LIN_SYNC_ERROR, LIN_SYNC_CLEAR, LIN_IDPARITY_ERROR, LIN_IDPARITY_CLEAR,
 *                       LIN_RESPRE_ERROR, LIN_RESPRE_CLEAR, LIN_MASTER_ERROR_DETECTION, LIN_SLAVE_ERROR_DETECTION,
 *                       LIN_RLIN3_SLAVE_MODE
 * 1.4.3:  09/05/2022  : Remove un-used macro: LIN_PRESCALER_DIV1, LIN_PRESCALER_DIV2, LIN_PRESCALER_DIV4,
 *                       LIN_PRESCALER_DIV8, LIN_PRESCALER_DIV16, LIN_PRESCALER_DIV32, LIN_PRESCALER_DIV64,
 *                       LIN_PRESCALER_DIV128, LIN_RESET_WAKEUP, LIN_ERROR_CLEAR
 *         14/04/2022  : Update SW-VERSION to 1.4.3
 * 1.4.2:  04/03/2022  : Update SW-VERSION
 * 1.4.1:  30/12/2021  : Add macro LIN_FIVE
 * 1.3.2:  24/08/2021  : Add new macro LIN_EIC_PENDING_CLEAR
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0.
 *                       Format source code to 120 characters.
 *                       Improve Violation tag (remove START/END).
 * 1.2.0:  26/08/2020  : Release.
 * 1.1.0:  19/06/2020  : Release.
 * 1.0.2:  16/04/2020  : Modified #include heading files.
 * 1.0.1:  08/04/2020  : Add macros to select wakeup baud rate specification
 *                       LIN_SET_WAKEUP_BAUDRATE_SPEC_13 and LIN_SET_WAKEUP_BAUDRATE_SPEC_21.
 * 1.0.0:  12/03/2019  : Initial Version.
 *
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

#ifndef LIN_RLIN3_PBTYPES_H
#define LIN_RLIN3_PBTYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define LIN_RLIN3_PBTYPES_AR_RELEASE_MAJOR_VERSION    LIN_AR_RELEASE_MAJOR_VERSION
#define LIN_RLIN3_PBTYPES_AR_RELEASE_MINOR_VERSION    LIN_AR_RELEASE_MINOR_VERSION
#define LIN_RLIN3_PBTYPES_AR_RELEASE_REVISION_VERSION LIN_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define LIN_RLIN3_PBTYPES_SW_MAJOR_VERSION            LIN_SW_MAJOR_VERSION
#define LIN_RLIN3_PBTYPES_SW_MINOR_VERSION            LIN_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* LIN Driver initialization status */
#define LIN_UNINIT                                    (boolean)0x00
#define LIN_INIT                                      (boolean)0x01

#define LIN_TRUE                                      (boolean)0x01
#define LIN_FALSE                                     (boolean)0x00

#define LIN_ZERO                                      (uint8)0x00
#define LIN_ONE                                       (uint8)0x01
#define LIN_FOUR                                      (uint8)0x04
#define LIN_EIGHT                                     (uint8)0x08
#if (LIN_INTERRUPT_MUX_SUPPORT == STD_ON)
#define LIN_FIVE                                      (uint8)0x05
#endif /* #if (LIN_INTERRUPT_MUX_SUPPORT == STD_ON) */

#define LIN_SET_WAKEUP_BAUDRATE_SPEC_13               (uint8)0xFE
#define LIN_SET_WAKEUP_BAUDRATE_SPEC_21               (uint8)0x01

/* RLIN Frame Structure Codes */
#define LIN_RESET_VALUE                               (uint8)0x00
#define LIN_SET_VALUE                                 (uint8)0x01
#define LIN_SET_OPERATION_MODE                        (uint8)0x03
#define LIN_LOW_WIDTH                                 (uint8)0x40
#define LIN_FRAME_MODE                                (uint8)0xBF
#define LIN_SET_CLS_CHKSUM                            (uint8)0xDF
#define LIN_SET_ENH_CHKSUM                            (uint8)0x20
#define LIN_MASTER_DIRECTION                          (uint8)0x10
#define LIN_SLAVE_DIRECTION                           (uint8)0xEF
#define LIN_START_TRANSMIT                            (uint8)0x01
#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
#define LIN_START_RESPONSE                            (uint8)0x02
#define LIN_NO_RESPONSE                               (uint8)0x04
#endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
#define LIN_COPY_SLEEP_FRAME                          (uint8)0xFF

#define LIN_MASTER_ENABLE_INTERRUPT                   (uint8)0x07
#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
#define LIN_SLAVE_ENABLE_INTERRUPT                    (uint8)0x0F
#endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
#define LIN_SLEEP_COMMAND                             (uint8)0x3C

/* RLIN Status Codes */
#if (LIN_WAKEUP_SUPPORT == STD_ON)
#define LIN_WAKEUP                                    (uint8)0xFF
#endif /* #if (LIN_WAKEUP_SUPPORT == STD_ON) */
#define LIN_HEADER_COMPLETE                           (uint8)0x80
#define LIN_DATA1RX_COMPLETE                          (uint8)0x40
#define LIN_RESPONSE_COMPLETE                         (uint8)0x02
#define LIN_FRAME_COMPLETE                            (uint8)0x01
#define LIN_TRANSMIT_DONE                             (uint8)0x7E
#define LIN_HEADER_DONE                               (uint8)0x7F
#define LIN_RECEPTION_DONE                            (uint8)0xFD
#define LIN_DATA1RX_DONE                              (uint8)0xBF

#define LIN_CLR_SLEEP_REQUEST                         (uint8)0x00
#define LIN_SET_SLEEP_REQUEST                         (uint8)0x01

/* RLIN Error Codes */
#define LIN_ERROR_FREE                                (uint8)0x00
#define LIN_CHECKSUM_ERROR                            (uint8)0x20
#define LIN_CHECKSUM_CLEAR                            (uint8)0xDF
#define LIN_TIMEOUT_ERROR                             (uint8)0x04
#define LIN_TIMEOUT_CLEAR                             (uint8)0xFB
#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
#define LIN_SYNC_ERROR                                (uint8)0x10
#define LIN_SYNC_CLEAR                                (uint8)0xEF
#define LIN_IDPARITY_ERROR                            (uint8)0x40
#define LIN_IDPARITY_CLEAR                            (uint8)0xBF
#define LIN_RESPRE_ERROR                              (uint8)0x80
#define LIN_RESPRE_CLEAR                              (uint8)0x7F
#endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
#define LIN_BIT_ERROR                                 (uint8)0x01
#define LIN_BIT_CLEAR                                 (uint8)0xFE
#define LIN_PBUS_ERROR                                (uint8)0x02
#define LIN_PBUS_CLEAR                                (uint8)0xFD
#define LIN_FRAMING_ERROR                             (uint8)0x08
#define LIN_FRAMING_CLEAR                             (uint8)0xF7
#define LIN_MASTER_ERROR_DETECTION                    (uint8)0x0F
#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
#define LIN_SLAVE_ERROR_DETECTION                     (uint8)0x5D
#endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
#define LIN_ERROR_OCCURED                             (uint8)0x08

/* RLIN3 Register Values */
/* LMD[1:0] = 00: LIN master mode */
#define RLIN3_MASTER_MODE                             (uint8)0x3C
#if (LIN_SLAVE_MODE_SUPPORT == STD_ON)
/* LMD[1:0] = 11: LIN slave mode with fixed baud rate */
#define LIN_RLIN3_SLAVE_MODE                          (uint8)0x03
#endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
#define RLIN3_INTERRUPT_REG                           (uint8)0x10

/* RLIN3 EICn */
#define LIN_EIC_EIMK_MASK                             (uint8)0x80U
#define LIN_EIC_EIMK_MASK_CLEAR                       (uint8)0x7FU
#define LIN_EIC_PENDING_CLEAR                         (uint16)0xEFFFU

/* Multicore support */
#if (LIN_MULTI_CORE_SUPPORT == STD_ON)
#define LIN_INVALID_CORE                              (uint8)0xFF
#endif /* #if (LIN_SLAVE_MODE_SUPPORT == STD_ON) */
/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* Type of the RLIN3 modes */
typedef enum ETag_Lin_ModeType
{
  RLIN3_RESET_MODE = 0x00,
  RLIN3_OPERATION_MODE = 0x01,
  RLIN3_WAKEUP_MODE = 0x02
} Lin_ModeType;

/* Type of LIN interrupt schedule */
typedef enum ETag_Lin_InterruptScheduleType
{
  LIN_INTERRUPT_DIS = 0x00,
  LIN_INTERRUPT_EN = 0x01
} Lin_InterruptScheduleType;

/* Type of LIN wake-up */
typedef enum ETag_Lin_WakeupType
{
  LIN_SLAVE_ISSUE = 0x00,
  LIN_MASTER_ISSUE = 0x01
} Lin_WakeupType;

/***********************************************************************************************************************
**                                    MACROS FOR ENABLING AND DISABLING INTERRUPTS                                    **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif /* LIN_RLIN3_PBTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
