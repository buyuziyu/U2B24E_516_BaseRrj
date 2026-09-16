/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Dio_LTTypes.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2019-2025 Renesas Electronics Corporation. All rights reserved.                                                */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains the type definitions of Post Build time Parameters                                              */
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
**                                             Revision Control History                                               **
***********************************************************************************************************************/
/*
 * 2.4.1:  19/06/2025  : Remove SW-VERSION in header file
 * 2.4.0:  30/06/2025  : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax Release
 * 2.3.0:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 2.2.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D U2Bx Final Release
 * 2.1.2:  31/10/2024  : As part of ARDAACL-50434, ARDAACL-50430, following changes are made
 *                       Update memory mapping from DIO_START/STOP_SEC_CONST_UNSPECIFIED 
 *                       to DIO_START/STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED in definition 
 *                       of Dio_GaaPortGroup, Dio_GaaPortChannel
 * 2.1.1:  11/06/2024  : As part of ARDAACL-34989, following changes are made
 *                       Remove QAC msg 1534, 1536
 *                       As part of ARDAACL-37399, following changes are made
 *                       Add Analog register to comment of pPortAddress and UTag_Dio_PortDataType
 * 2.1.0:  29/02/2024  : Update SW-VERSION to 2.1.0
 * 2.0.1:  22/10/2023  : Remove un-used macro: DIO_TRUE, DIO_FALSE and DIO_MSB_MASK and Add QAC msg 1534, 1536
 *         12/10/2023  : Update SW-VERSION 2.0.1
 * 2.0.0:  18/07/2023  : Support Multi-core DIO type III
 *         15/05/2023  : Updated SW-VERSION
 * 1.4.3   12/04/2022  : Corrected define from DIO_LTTYPES_AR_RELEASE_PATCH_VERSION to
 *                       DIO_LTTYPES_AR_RELEASE_REVISION_VERSION
 * 1.4.2:  07/04/2022  : Removed un-used DIO_INITIALIZED and DIO_UNINITIALIZED macros
 * 1.4.1:  08/10/2021  : Updated SW-VERSION 
 * 1.3.1:  02/07/2021  : Add QAC message 9.5.0
 *                       Format source code to 120 characters
 *                       Improve Violation tag (remove START/END)
 *         06/05/2021  : Composition of type: <Component name>_<Type name>Type
 *                       Follow Name_Type_002.
 * 1.2.0:  26/08/2020  : Release
 * 1.1.1:  26/08/2020  : Update revision history
 * 1.1.0:  19/06/2020  : Release
 * 1.0.1:  19/03/2020  : Add Justification for QAC MISRA-C:2012
 * 1.0.0:  09/09/2019  : Initial Version
 */
/**********************************************************************************************************************/
#ifndef DIO_LTTYPES_H
#define DIO_LTTYPES_H

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Standard AUTOSAR types */
#include "Std_Types.h"

#include "Dio.h"

#if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
#include "SchM_Dio.h"
#endif

#if (DIO_MULTI_CORE_SUPPORT == STD_ON)
#include "Os.h"
#endif
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define DIO_LTTYPES_AR_RELEASE_MAJOR_VERSION DIO_AR_RELEASE_MAJOR_VERSION
#define DIO_LTTYPES_AR_RELEASE_MINOR_VERSION DIO_AR_RELEASE_MINOR_VERSION
#define DIO_LTTYPES_AR_RELEASE_REVISION_VERSION DIO_AR_RELEASE_REVISION_VERSION

/* Module Software version information */
#define DIO_LTTYPES_SW_MAJOR_VERSION         DIO_SW_MAJOR_VERSION
#define DIO_LTTYPES_SW_MINOR_VERSION         DIO_SW_MINOR_VERSION

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:0342)    : Using the glue operator '##'.                                                                */
/* Rule                : CERTCCM PRE05, MISRA C:2012 Rule-20.10                                                       */
/* JV-01 Justification : This can be accepted, due to the implementation is following AUTOSAR standard rule for SchM  */
/*                       module's name.                                                                               */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0750)    : A union type specifier has been defined.                                                     */
/* Rule                : MISRA C:2012 Rule-19.2, CWE Rule CWE-843                                                     */
/* JV-01 Justification : This union type is used for register accessing and there is no issue with this usage.        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Global Symbols                                                   **
***********************************************************************************************************************/
/* General defines */
#define DIO_NORMALPORT                       (Dio_PortType)2
#define DIO_JTAGPORT                         (Dio_PortType)1
#define DIO_LOW_LEVEL_OUTPUT                 (uint16)0x0000
#define DIO_OUTPUT_MODE_PIN_EXISTENCE_CHECK  (uint16)0x0000
#define DIO_PORT_REGISTER_DEFAULT_VALUE      (uint16)0x0000 

#define DIO_ONE                               0x01U         

/***********************************************************************************************************************
**                                      SchM Critical Section Protection Macros                                       **
***********************************************************************************************************************/
#if (DIO_CRITICAL_SECTION_PROTECTION == STD_ON)
#define DIO_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Dio_##Exclusive_Area()                                    /* PRQA S 0342 # JV-01 */
#define DIO_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Dio_##Exclusive_Area()                                     /* PRQA S 0342 # JV-01 */
#endif
/***********************************************************************************************************************
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/
/* Structure for Dio Port Group */
typedef struct STag_Dio_PortGroupType
{
  /* Address of the PSR/JPSR/APSR register */
  P2VAR(volatile uint32, TYPEDEF, REGSPACE) pPortAddress;
  /* Port type of JTAG port/Normal(Numeric) port */
  uint8 ucPortType;
  /* Usable pin position, represented as value 0 in low-order 16bit.
     When usable pin is 0-6, this parameter is 0xFFFFFF80. */
  uint32 ulModeMask;
  /* Number of Port Group of register */
  uint32 ulPortGroupNum;

  #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare the variable to store list of configured core ID for the group */
  uint8 ucGroupCoreIndex;
  #endif
} Dio_PortGroupType;

/* Structure for Dio Channel */
typedef struct STag_Dio_PortChannelType
{
  /* Bit position of the Channel */
  uint16 usMask;
  /* PortGroup Index in the array Dio_GaaPortGroup[] */
  uint8 ucPortIndex;

  #if (DIO_MULTI_CORE_SUPPORT == STD_ON)
  /* Declare the variable to store list of configured core ID for the group */
  uint8 ucChannelCoreIndex;
  #endif

} Dio_PortChannelType;

/* Union for accessing 32 bit PSR/APSR register */
typedef union UTag_Dio_PortDataType
{                                                                                                                       /* PRQA S 0750 # JV-01 */
  uint32 ulLongWord;
  struct
  {
    uint16 usLSWord;
    uint16 usMSWord;
  } Tst_WordValueType;
} Dio_PortDataType;


/***********************************************************************************************************************
**                                        Extern declarations for Global Data                                         **
***********************************************************************************************************************/
#define DIO_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Dio_MemMap.h"
extern CONST(Dio_PortGroupType, DIO_CONFIG_DATA) Dio_GaaPortGroup[];                                                    /* PRQA S 3684 # JV-01 */
extern CONST(Dio_PortChannelType, DIO_CONFIG_DATA) Dio_GaaPortChannel[];                                                /* PRQA S 3684 # JV-01 */

#define DIO_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "Dio_MemMap.h"

/***********************************************************************************************************************
**                                                Function Prototypes                                                 **
***********************************************************************************************************************/

#endif
/* DIO_LTTTYPES_H */

/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
