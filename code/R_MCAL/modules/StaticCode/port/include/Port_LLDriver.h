/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Port_LLDriver.h                                                                                     */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020 - 2025 Renesas Electronics Corporation. All rights reserved.                                              */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Provision of prototypes for internal functions.                                                                    */
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
 * 2.4.0: 30/06/2025 : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax Release
 * 2.3.2: 25/04/2025 : Update SW-VERSION for RH850/Ver22.00.03 U2Ax Release
 * 2.3.1: 28/02/2025 : Update SW-VERSION for RH850/Ver22.00.02 U2Ax Release
 * 2.3.0: 28/02/2025 : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release 
 * 2.2.0: 31/12/2024 : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D U2Bx Final Release
 * 2.1.2: 31/10/2024 : Update SW-VERSION to 2.1.2 for Ver22.01.02 U2Bx Beta2
 * 2.1.0: 28/02/2024 : Update SW-VERSION to 2.1.0
 *                   : Remove Msg 1536
 * 2.0.1: 19/10/2023 : Add Msg 1536
 *        16/10/2023 : Change name for macro DNFP02EDC16_AVAILABLE to PORT_DNFP02EDC16_AVAILABLE
 * 2.0.0: 06/08/2023 : Update CWE Rule CWE-398, CWE-569 for message 3432
 * 1.4.3: 12/04/2022 : Update SW-VERSION to 1.4.3
 * 1.4.1: 07/10/2021 : Update SW-VERSION to 1.4.1
 * 1.3.1: 02/07/2021 : Add QAC message 9.5.0
 *                     Format source code to 120 characters
 *                     Improve Violation tag (remove START/END)
 * 1.3.0: 09/11/2020 : Update Port_SwitchSetting16 to support PIBC setting.
 * 1.2.0: 28/07/2020 : Release.
 * 1.1.0: 19/06/2020 : Release.
 * 1.0.1: 21/04/2020 : Add function Port_SwitchSetting16, Port_SetMultiBReg.
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef PORT_LLDRIVER_H
#define PORT_LLDRIVER_H

/***********************************************************************************************************************
**                             To support different AUTOSAR releases in a single package                              **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR Release version information */
#define PORT_LLDRIVER_AR_RELEASE_MAJOR_VERSION    PORT_AR_RELEASE_MAJOR_VERSION
#define PORT_LLDRIVER_AR_RELEASE_MINOR_VERSION    PORT_AR_RELEASE_MINOR_VERSION
#define PORT_LLDRIVER_AR_RELEASE_REVISION_VERSION PORT_AR_RELEASE_REVISION_VERSION

/*  File version information */
#define PORT_LLDRIVER_SW_MAJOR_VERSION            PORT_SW_MAJOR_VERSION
#define PORT_LLDRIVER_SW_MINOR_VERSION            PORT_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7, CWE Rule CWE-398, CWE-569                                            */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Constant Data Type                                                 **
***********************************************************************************************************************/
/* Register Setting Information */
typedef struct STag_Port_RegSetInfoType
{
  /* Register Type */
  uint16 usSetRegType;
  /* SR Register Type */
  uint16 usSRRegType;
  /* Setting Mode */
  /*  b0:PORT INPUT */
  /*  b1:PORT OUTPUT */
  /*  b2:ALT SW INPUT */
  /*  b3:ALT SW OUTPUT */
  /*  b4:ALT DIRECT */
  uint16 usSetMode;
} Port_RegSetInfoType;

/* Mode Setting Information */
typedef struct STag_Port_ModeSetInfoType
{
  /* Mode Type */
  uint16 usModeType;
  /* PMC Mode */
  uint16 usMode;
  /* PM Input/Output */
  uint16 usInOut;
  /* PIPC Contorl */
  uint16 usControl;
  /* Setting Register */
  /*  b0:PMC, b1:PM, b2:PIC */
  uint16 usSetReg;
} Port_ModeSetInfoType;

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/
#define PORT_START_SEC_PRIVATE_CODE
#include "Port_MemMap.h"

extern FUNC(boolean, PORT_PRIVATE_CODE) Port_MaskECM(CONST(boolean, AUTOMATIC) LblMask);

extern FUNC(void, PORT_PRIVATE_CODE) Port_ClearECM(void);

extern FUNC(Std_ReturnType, PORT_PRIVATE_CODE) Port_InitConfig(CONST(boolean, AUTOMATIC) LblMode);

extern FUNC(Std_ReturnType, PORT_PRIVATE_CODE) Port_InitReg(CONST(uint16, AUTOMATIC) LusRegType,
                                                                                    CONST(boolean, AUTOMATIC) LblVal);
extern FUNC(Std_ReturnType, PORT_PRIVATE_CODE) Port_SetReg8(CONST(uint16, AUTOMATIC) LusPortType,
      CONST(uint16, AUTOMATIC) LusRegType, CONST(uint16, AUTOMATIC) LusPortNum, CONST(uint16, AUTOMATIC) LusSetValue);

extern FUNC(Std_ReturnType, PORT_PRIVATE_CODE) Port_SetReg16(CONST(uint16, AUTOMATIC) LusPortType,
      CONST(uint16, AUTOMATIC) LusRegType, CONST(uint16, AUTOMATIC) LusPortNum, CONST(uint16, AUTOMATIC) LusSetValue);


extern FUNC(Std_ReturnType, PORT_PRIVATE_CODE) Port_InitDNF(void);

extern FUNC(Std_ReturnType, PORT_PRIVATE_CODE) Port_SetDNF(volatile CONSTP2VAR(uint8, AUTOMATIC, REGSPACE) LpDNFP,      /* PRQA S 3432 # JV-01 */
                                                                                    CONST(uint8, AUTOMATIC) LucValue);
#if (PORT_DNFP02EDC16_AVAILABLE == STD_ON)
extern FUNC(Std_ReturnType, PORT_PRIVATE_CODE)
            Port_SetDNF16(volatile CONSTP2VAR(uint16, AUTOMATIC, REGSPACE) LpDNFP, CONST(uint16, AUTOMATIC) LusValue);  /* PRQA S 3432 # JV-01 */
#endif
extern FUNC(void, PORT_PRIVATE_CODE) Port_SetDioAltMode(CONST(Port_PinType, AUTOMATIC) LddPinNumber, uint8 LucPinMode,
                                                                                        CONST(uint8, AUTOMATIC) LucSID);
extern FUNC(void, PORT_PRIVATE_CODE) Port_SwitchSetting(CONST(uint16, AUTOMATIC) LusPortType,
                                    CONST(uint16, AUTOMATIC) LusPortLoc, CONST(uint16, AUTOMATIC) LusBitLoc, 
                                    Port_PinDirectionType LenDirection, uint8 LucPinMode);

extern FUNC(void, PORT_PRIVATE_CODE) Port_SwitchSetting16(CONST(uint16, AUTOMATIC) LusPortType,
                                              CONST(uint16, AUTOMATIC) LusPortLoc, CONST(uint16, AUTOMATIC) LusRefresh,
                                              CONST(uint16, AUTOMATIC) LusMode, CONST(uint16, AUTOMATIC) LusPIBC);

extern FUNC(void, PORT_PRIVATE_CODE) Port_ResetMode(CONST(uint16, AUTOMATIC) LusPortType,
                                              CONST(uint16, AUTOMATIC) LusPortLoc, CONST(uint16, AUTOMATIC) LusBitLoc);


extern FUNC(Std_ReturnType, PORT_PRIVATE_CODE) Port_SetMode(CONST(uint16, AUTOMATIC) LusPortType,
                              CONST(uint16, AUTOMATIC) LusPortLoc, CONST(uint16, AUTOMATIC) LusBitLoc, uint32 LulMode);


extern FUNC(uint32, PORT_PRIVATE_CODE) Port_GetDefaultValue(CONST(uint16, AUTOMATIC) LusPortType,
                                              CONST(uint16, AUTOMATIC) LusPortLoc, CONST(uint16, AUTOMATIC) LusBitLoc);


extern FUNC(uint16, PORT_PRIVATE_CODE) Port_SetBReg(CONST(uint8, AUTOMATIC) LucBitNum,
                                                volatile CONSTP2VAR(uint16, AUTOMATIC, REGSPACE) LpReg,                 /* PRQA S 3432 # JV-01 */
                                                CONST(uint16, AUTOMATIC) LusBitLoc, CONST(uint16, AUTOMATIC) LusValue);

extern FUNC(uint16, PORT_PRIVATE_CODE) Port_SetSRReg(volatile CONSTP2VAR(uint32, AUTOMATIC, REGSPACE) LpReg,            /* PRQA S 3432 # JV-01 */
                                                CONST(uint16, AUTOMATIC) LusBitLoc, CONST(uint16, AUTOMATIC) LusValue);


extern FUNC(void, PORT_PRIVATE_CODE) Port_SetPweMode(CONST(uint16, AUTOMATIC) LusPortType,
                                            CONST(uint16, AUTOMATIC) LusPortLoc, CONST(boolean, AUTOMATIC) LblPweMode);


extern FUNC(uint16, PORT_PRIVATE_CODE) Port_SetMultiBReg
                            (CONST(uint8, AUTOMATIC) LucBitNum, volatile CONSTP2VAR(uint16, AUTOMATIC, REGSPACE) LpReg, /* PRQA S 3432 # JV-01 */
                                                CONST(uint16, AUTOMATIC) LusBitLoc, CONST(uint16, AUTOMATIC) LusValue);
#define PORT_STOP_SEC_PRIVATE_CODE
#include "Port_MemMap.h"

#endif /* PORT_LLDRIVER_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
