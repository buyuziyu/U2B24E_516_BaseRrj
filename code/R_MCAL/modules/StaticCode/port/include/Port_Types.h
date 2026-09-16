/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Port_Types.h                                                                                        */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2020 - 2025 Renesas Electronics Corporation. All rights reserved.                                              */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Private functions declarations.                                                                                    */
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
 *                   : add ucPortKernelCoreId into Port_ConfigType
 *                   : add usInputPortValue into Port_ConfigType
 *                   : Remove Msg 1536, 1534
 * 2.0.1: 19/10/2023 : Add Msg 1536
 *        18/10/2023 : Update SW-VERSION to 2.0.1
 * 1.4.3: 12/04/2022 : Update SW-VERSION to 1.4.3
 * 1.4.1: 07/10/2021 : Update SW-VERSION to 1.4.1
 * 1.3.1: 02/07/2021 : Format source code to 120 characters
 * 1.2.0: 28/07/2020 : Release.
 * 1.1.0: 19/06/2020 : Release.
 * 1.0.0: 09/01/2020 : Initial Version
 */
/**********************************************************************************************************************/
#ifndef PORT_TYPES_H
#define PORT_TYPES_H

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define PORT_TYPES_AR_RELEASE_MAJOR_VERSION    PORT_AR_RELEASE_MAJOR_VERSION
#define PORT_TYPES_AR_RELEASE_MINOR_VERSION    PORT_AR_RELEASE_MINOR_VERSION
#define PORT_TYPES_AR_RELEASE_REVISION_VERSION PORT_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define PORT_TYPES_SW_MAJOR_VERSION            PORT_SW_MAJOR_VERSION        
#define PORT_TYPES_SW_MINOR_VERSION            PORT_SW_MINOR_VERSION        

/* General defines */
#define PORT_DBTOC_VALUE    (((uint32)PORT_VENDOR_ID_VALUE << 22U) | ((uint32)PORT_MODULE_ID_VALUE << 14U) | \
                              ((uint32)PORT_SW_MAJOR_VERSION_VALUE << 8U) | ((uint32)PORT_SW_MINOR_VERSION_VALUE << 3U))

/* Number of PORT Type */
#define PORT_TYPE_NUM      (uint16)0x0003U
#define PORT_CHG_DIRECTION (uint16)0x0001U
#define PORT_CHG_DIO_ALT   (uint16)0x0002U
#define PORT_CHG_MODE      (uint16)0x0004U

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/* Port Configuration */
typedef struct STag_Port_ConfigType
{
  /* Database start value - 0x0EDF0400 */ /* Req Update */
  uint32 ulStartOfDbToc;

  /* Used Pins Number */
  uint32 ulUsePinNumber;
  #if (PORT_GROUP_INPUT_AVAILABLE == STD_ON)
  /* Data for Group Input Port */
  uint16 usInputPortValue;
  #endif
  #if (PORT_MULTI_CORE_SUPPORT == STD_ON)
  /* Define kernel core ID */
  uint8 ucPortKernelCoreId;
  #endif
  /* Pin Configuration */
  P2CONST(void, TYPEDEF, PORT_CONFIG_CONST) pPortPinConfig;

  /* Digital Noise Filter Information */
  P2CONST(void, TYPEDEF, PORT_CONFIG_CONST) pPortDNFConfig;

  /* PORT Configuration */
  P2CONST(void, TYPEDEF, PORT_CONFIG_CONST) pPortConfig[PORT_TYPE_NUM];
} Port_ConfigType;

#endif /* PORT_TYPES_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
