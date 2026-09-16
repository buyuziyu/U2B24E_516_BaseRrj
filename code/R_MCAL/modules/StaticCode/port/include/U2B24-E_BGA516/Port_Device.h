/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Port_Device.h                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024 - 2025 Renesas Electronics Corporation. All rights reserved.                                              */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* Specific device information.                                                                                       */
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
 * 2.4.1: 08/06/2025 : Remove the SW-VERSION from header of file
 * 2.3.1: 31/03/2025 : Update SW-VERSION for RH850/U2Bx-E MCAL Ver22.00.02 Release 
 * 2.1.2: 31/10/2024 : Update SW-VERSION to 2.1.2
 * 1.0.0: 03/05/2024 : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (2:3630)    : The implementation of this struct/union type should be hidden.                               */
/* Rule                : MISRA C:2012 Dir-4.8                                                                         */
/* JV-01 Justification : This is accepted. Redundant of struct or union type has no affect to driver operation.       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3684)    : Array declared with unknown size.                                                            */
/* Rule                : CERTCCM ARR02, MISRA C:2012 Rule-8.11                                                        */
/* JV-01 Justification : Arrays used are verified in the file which are only declarations and size is configuration   */
/*                       dependent.                                                                                   */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#ifndef PORT_DEVICE_H
#define PORT_DEVICE_H

/* PORT Device */

/* Port Valid / Invalid */
#define PORT_MAX_NUM           50U
/* Bits Number */
#define PORT_BIT_8             8U
#define PORT_BIT_16            16U

/* Port Offset Address */
#define PORT_OFFSET            0x00000040UL

/* Port Write Enable definition */
#define PORT_PWE_ALL_MASK      0x07FFFFFFUL
#define PORT_PWE_ENABLE_WRITE  0xA5A5A501UL
#define PORT_PWE_DISABLE_WRITE 0xA5A5A500UL

/* Error Control Module definition */
#define PORT_ECM_BASE          0xFFCCD000UL
#define PORT_OFFSET_ECMEMK     0x00000270UL
#define PORT_OFFSET_ECMESSTC   0x0000048CUL
#define PORT_OFFSET_ECMKCPROT  0x000004B4UL
#define PORT_ECM_MASK          (uint32)0x0F000000UL
#define PORT_ECM_ENABLE_WRITE  (uint32)0xA5A5A501UL
#define PORT_ECM_DISABLE_WRITE (uint32)0xA5A5A500UL

/* Digital Noise Filter definition */
#define PORT_DNFP01_BASE       0xFFED4000UL
#define PORT_DNFP01_SIZE       0x0100U
#define PORT_DNFP01_CH_SIZE    4U
#define PORT_DNFP02_BASE       0xFFED0000UL
#define PORT_DNFP02_SIZE       0x0100U
#define PORT_DNFP02_CH_SIZE    8U
#define PORT_DNFP03_BASE       0xFFED6000UL
#define PORT_DNFP03_SIZE       0x0100U
#define PORT_DNFP03_CH_SIZE    8U
#define PORT_DNFP02_CTL        0U
#define PORT_DNFP02_EDC        4U
#define PORT_DNFP02_ADD        0x00000000UL

/* Digital Noise Filter definition */
#define PORT_DNFP01_NUM        23U
#define PORT_DNFP01_CH_NUM     8U
#define PORT_DNFP02_NUM        30U
#define PORT_DNFP02_CH_NUM     1U
#define PORT_DNFP03_NUM        41U
#define PORT_DNFP03_CH_NUM     16U

/* Number of Registers */
#define PORT_REG_SET_NUM       31U
#define PORT_REG_SFS_NUM       4U
#define PORT_REG_OTHER         7U
#define PORT_REG_NUM           (PORT_REG_SET_NUM + PORT_REG_SFS_NUM)

/* Register Information */
typedef struct STag_Port_Reg_Info
{
  /* Valid / Invalid for each bit */
  uint16 usValid;
  /* Reset Value */
  uint16 usResetVal;
} Port_Reg_Info;

/* Port Information */
typedef struct STag_Port_Info                                                                                           /* PRQA S 3630 # JV-01 */
{
  /* Port Number */
  uint16 usPortNum;
  /* Register Information */
  Port_Reg_Info stRegInfo[PORT_REG_NUM];
  /* PWE Value */
  uint32 ulPweVal;
} Port_Info;

/* Port Type Information */
typedef struct STag_Port_Type_Info
{
  /* Number of Bit */
  uint8 ucBitNum;
  /* Number of Port */
  uint16 usPortNum;
  /* Base Address */
  uint32 ulBaseAddress;
  /* Address of Port Infromation */
  P2CONST(Port_Info, TYPEDEF, PORT_CONST) pPortInfo;
} Port_Type_Info;

/* DNF Information */
typedef struct STag_Port_DNF_Info
{
  uint16 usDNFP01_Valid[PORT_DNFP01_NUM];
  uint16 usDNFP02_Valid[PORT_DNFP02_NUM];
  uint16 usDNFP03_Valid[PORT_DNFP03_NUM];
  uint16 usDNFP02_Valid2;
} Port_DNF_Info;

#define PORT_START_SEC_CONST_32
#include "Port_MemMap.h"

extern CONST(uint32, PORT_CONST) Port_RegOffset[];                                                                      /* PRQA S 3684 # JV-01 */

#define PORT_STOP_SEC_CONST_32
#include "Port_MemMap.h"

#define PORT_START_SEC_CONST_UNSPECIFIED
#include "Port_MemMap.h"

extern CONST(Port_Type_Info, PORT_CONST) Port_TypeInformation[];                                                        /* PRQA S 3684 # JV-01 */

#define PORT_STOP_SEC_CONST_UNSPECIFIED
#include "Port_MemMap.h"

#define PORT_START_SEC_CONST_16
#include "Port_MemMap.h"

extern CONST(Port_DNF_Info, PORT_CONST) Port_DNF_Information;

#define PORT_STOP_SEC_CONST_16
#include "Port_MemMap.h"

#endif /* PORT_DEVICE_H */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
