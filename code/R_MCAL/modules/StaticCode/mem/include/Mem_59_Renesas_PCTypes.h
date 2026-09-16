/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Mem_59_Renesas_PCTypes.h                                                                            */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2024-2025 Renesas Electronics Corporation. All rights reserved.                                                */
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
**                                              Revision Control History                                              **
***********************************************************************************************************************/
/*
 * 1.1.0:  30/06/2025  : Update SW-VERSION for RH850/Ver22.01.00(D) U2Ax release
 * 1.0.3:  25/04/2025  : Update SW-VERSION for RH850/U2Ax MCAL Ver22.00.03 Release
 *                       Remove macro MEM_59_RENESAS_STATUS_1_BIT_ERROR_MASK and MEM_59_RENESAS_CLEAR_1_BIT_ERROR
 * 1.0.2:  31/03/2025  : Update define for MEM_59_RENESAS_CLEAR_1_BIT_ERROR and MEM_59_RENESAS_STATUS_1_BIT_ERROR_MASK
 *                       Add macro MEM_59_RENESAS_START_ADDRESS and MEM_59_RENESAS_END_ADDRESS
 * 1.0.1:  28/02/2025  : Update SW-VERSION for RH850/U2Cx MCAL Ver22.01.00/Ver22.01.00.D Release
 * 1.0.0:  31/12/2024  : Update SW-VERSION for Ver22.02.00/Ver22.02.00.D Final Release 
 *                       As part of ARDAACL-51748, update precondition for MEM_59_RENESAS_STATUS_1_BIT_ERROR_MASK. 
 *                       As part of ARDAACL-51152, remane macro from MEM_59_RENESAS_OPBT0_ADDRESS_AREA0 to 
 *                       MEM_59_RENESAS_OPBT0_ADDRESS_FRONT_SIDE and from MEM_59_RENESAS_OPBT0_ADDRESS_AREA1 
 *                       to MEM_59_RENESAS_OPBT0_ADDRESS_BACK_SIDE
 * 0.0.2:  31/10/2024  : Support commonize
 * 0.0.1:  30/08/2024  : Initial Version
 */
/**********************************************************************************************************************/
#ifndef MEM_59_RENESAS_PCTYPES_H
#define MEM_59_RENESAS_PCTYPES_H
/***********************************************************************************************************************
**                                                  Include Section                                                   **
***********************************************************************************************************************/
/* Included for Type definitions */
#include "Std_Types.h"
#include "r_rfd_common.h"
#include "Mem_59_Renesas_Cfg.h"
/***********************************************************************************************************************
**                                                Version Information                                                 **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define MEM_59_RENESAS_PCTYPES_AR_RELEASE_MAJOR_VERSION       MEM_59_RENESAS_AR_RELEASE_MAJOR_VERSION
#define MEM_59_RENESAS_PCTYPES_AR_RELEASE_MINOR_VERSION       MEM_59_RENESAS_AR_RELEASE_MINOR_VERSION
#define MEM_59_RENESAS_PCTYPES_AR_RELEASE_REVISION_VERSION    MEM_59_RENESAS_AR_RELEASE_REVISION_VERSION
/* File version information */
#define MEM_59_RENESAS_PCTYPES_SW_MAJOR_VERSION               MEM_59_RENESAS_SW_MAJOR_VERSION
#define MEM_59_RENESAS_PCTYPES_SW_MINOR_VERSION               MEM_59_RENESAS_SW_MINOR_VERSION

/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                                   Macro Defines                                                    **
***********************************************************************************************************************/
/* Macros to avoid direct numbers */
#define MEM_59_RENESAS_ZERO               ((uint8)0)
#define MEM_59_RENESAS_ONE                ((uint8)1)
#define MEM_59_RENESAS_TWO                ((uint8)2)
#define MEM_59_RENESAS_THREE              ((uint8)3)
#define MEM_59_RENESAS_FOUR               ((uint8)4)
#define MEM_59_RENESAS_EIGHT              ((uint8)8)
#define MEM_59_RENESAS_FOURTEEN           ((uint16)14)
#define MEM_59_RENESAS_SIXTEEN            ((uint8)16)
#define MEM_59_RENESAS_TWENTY_TWO         ((uint32)22)
#define MEM_59_RENESAS_TWENTY_FOUR        ((uint8)24)
#define MEM_59_RENESAS_THIRTY_TWO         ((uint32)32)

#define MEM_59_RENESAS_FACI_ONE           1

/* Macros for boolean variables */
#define MEM_59_RENESAS_FALSE              ((boolean)0)
#define MEM_59_RENESAS_TRUE               ((boolean)1)

/* Macros for module status */
#define MEM_59_RENESAS_INITIALIZED        (uint8)1
#define MEM_59_RENESAS_UNINITIALIZED      (uint8)0

/* Macros for HW IP */
#define MEM_59_RENESAS_HW_IP_FPSYS        0

/* Macros for Flash protection Support */
#define MEM_59_RENESAS_SUPPORTED              (0)
#define MEM_59_RENESAS_NOT_SUPPORTED          (1)

#define MEM_59_RENESAS_DFECCCTL_RESET_VAL ((uint32)0x00000000UL)
#define MEM_59_RENESAS_DFTSTCTL_RESET_VAL ((uint32)0x00000000UL)

#define MEM_59_RENESAS_CFCECCCTL_RESET_VAL ((uint32)0)
#define MEM_59_RENESAS_CFSERINF_RESET_VAL  ((uint8)0)

#if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED)
/* Macro to enable flash memory software protection */
#define MEM_59_RENESAS_FLASH_PROTECTION_ON  ((uint32)0)
/* Macro to disable flash memory software protection */
#define MEM_59_RENESAS_FLASH_PROTECTION_OFF ((uint32)1)
#endif /* End of #if (MEM_59_RENESAS_FHVE_REGS == MEM_59_RENESAS_SUPPORTED) */

#define MEM_59_RENESAS_FCU_MODE_CHECKCOUNT                    ((uint32)0x00000002uL)

/* DFERSTR */
#define MEM_59_RENESAS_FCU_REGVAL_DFERSTR_NOERR               ((uint32)0x00000000uL)
#define MEM_59_RENESAS_FCU_REGBIT_DFERSTR_SEDF                ((uint32)0x00000001uL)
#define MEM_59_RENESAS_FCU_REGBIT_DFERSTR_DEDF                ((uint32)0x00000002uL)

/* DFERSTC */
#define MEM_59_RENESAS_FCU_REGBIT_DFERSTC_ERRCLR              ((uint32)0x00000001uL)

/* DFSERSTR */
#define MEM_59_RENESAS_FCU_REGVAL_DFSERSTR_NOERR              ((uint32)0x00000000uL)
#define MEM_59_RENESAS_FCU_REGBIT_DFSERSTR                    ((uint32)0x0000000FuL)
/* DFDERSTR */
#define MEM_59_RENESAS_FCU_REGVAL_DFDERSTR_NOERR              ((uint32)0x00000000uL)
#define MEM_59_RENESAS_FCU_REGBIT_DFDERSTR                    ((uint32)0x00000001uL)
/*DFSERSTC*/
#define MEM_59_RENESAS_FCU_REGBIT_DFSERSTC_ERRCLR             ((uint32)0x0000000Fu)
/*DFDERSTC*/
#define MEM_59_RENESAS_FCU_REGBIT_DFDERSTC_ERRCLR             ((uint32)0x00000001u)
/* DFERRINT */
#define MEM_59_RENESAS_FCU_REGVAL_DFERRINT_NOINT              ((uint8)0x00u)
/* CFERRINT */
#define MEM_59_RENESAS_FCU_REGVAL_CFERRINT_NOINT              ((uint8)0x00u)

/* DFKCPROT */
#define MEM_59_RENESAS_FCU_REGVAL_DFKCPROT_ENABLE             ((uint32)0xA5A5A501uL)
#define MEM_59_RENESAS_FCU_REGVAL_DFKCPROT_DISABLE            ((uint32)0xA5A5A500uL)

/* IDST for DataFlash ID */
#define MEM_59_RENESAS_DFIDIN_RESETVALUE                      ((uint32)0xFFFFFFFFuL)

/* Security Option Bytes */
#define MEM_59_RENESAS_S_OPBT4_DPROT                          ((uint32)0x00000001uL)

/* Data Flash Size macros */
#define MEM_59_RENESAS_FCU_BLOCK_SIZE_40NM                    (64u)
#define MEM_59_RENESAS_FCU_BLOCK_SIZE_28NM                    (4096u)
#define MEM_59_RENESAS_FCU_WRITE_SIZE                         (0x00000004uL)
#define MEM_59_RENESAS_FCU_WRITE_SIZE_32BYTE                  (32uL)
#define MEM_59_RENESAS_FCU_WRITE_SIZE_128BYTE                 (128uL)
#define MEM_59_RENESAS_FCU_MAX_WRITE_BUFFER_SIZE              ((uint32)(MEM_59_RENESAS_FCU_WRITE_SIZE_128BYTE \
                                                                                      / MEM_59_RENESAS_FCU_WRITE_SIZE))

#define MEM_59_RENESAS_FCU_ZERO                               ((uint32)0x00000000uL)
#define MEM_59_RENESAS_FCU_ONE                                ((uint32)0x00000001uL)

#define MEM_59_RENESAS_TIMEOUT_INIT_VALUE                     ((uint32)(0x00000100uL))

#define MEM_59_RENESAS_READ_ONCESIZE                          ((uint32)32uL)

/* FACI FREQUENCY */
#define MEM_59_RENESAS_FACI_FREQENCY                          ((uint16)0xFFFFu)

/* FACI Number */
#define MEM_59_RENESAS_FACI_0                                 ((uint16)0x0000u)
#define MEM_59_RENESAS_FACI_1                                 ((uint16)0x0001u)

/* RFD Error Code */
#define MEM_59_RENESAS_RFD_ERROR_BIT                          (R_RFD_ERR_CMD_LOCK | R_RFD_ERR_NO_CMD_LOCK)

/* Blank Check Flag */
#define MEM_59_RENESAS_DATA_BLANK_STATE                       ((uint32)0x0000807FuL)
#define MEM_59_RENESAS_CODE_BLANK_STATE                       ((uint32)0x000087FFuL)

#define MEM_59_RENESAS_DFIDNUM                           (8u)
#define MEM_59_RENESAS_DFECCCTL2DFERSTR                  (2u)
#define MEM_59_RENESAS_DFERSTC2DFERRINT                  (8u)
#define MEM_59_RENESAS_DFERRINT2DFTSTCTL                 (216u)
#define MEM_59_RENESAS_DFTSTCTL2DFKCPROT                 (2u)
#define MEM_59_RENESAS_DFSERSTC2DFSERSTC                 (3u)

/* Define register for code flash */
#define MEM_59_RENESAS_CFERRINT2CFSSTCLR       12u
#define MEM_59_RENESAS_CFOVFCLR2CFSERSTR       3u
#define MEM_59_RENESAS_CFOVFSTR2CFSERINF       3u

/* Define Software protection of code flash P/E mode entry */
#define MEM_59_RENESAS_SFWE_UNPROTECT                    ((uint8)0x01u)
#define MEM_59_RENESAS_SFWE_PROTECT                      ((uint8)0x00u)

/* Define macro for register CF_DSTCLR */
#define MEM_59_RENESAS_CLEAR_2_BITS_ERROR                ((uint32)0x00000001u)

/* Define macro for register CF_DERSTR */
#define MEM_59_RENESAS_STATUS_2_BITS_ERROR_MASK          ((uint32)0x00000002u)

/* Define macro for config area address */
#define MEM_59_RENESAS_FRONT_SIDE                        ((uint8)0x00u)
#define MEM_59_RENESAS_BACK_SIDE                         ((uint8)0x01u)

/* Define macro for mask value */
#define MEM_59_RENESAS_MASK_16_BIT                        ((uint32)0x0000FFFFu)
#define MEM_59_RENESAS_MASK_8_BIT                         ((uint32)0x000000FFu)

/* Define macro for start/end of block/area */
#define MEM_59_RENESAS_START_ADDRESS                      (0)
#define MEM_59_RENESAS_END_ADDRESS                        (1)

/***********************************************************************************************************************
**                                                  Macro Functions                                                   **
***********************************************************************************************************************/
#define MEM_59_RENESAS_DF_READ16(Address)                     (*((volatile uint16 *)(Address)))

#define MEM_59_RENESAS_DF_READ8(Address)                      (*((volatile uint8 *)(Address)))

#define MEM_59_RENESAS_DF_WRITE8(Address, Data)               ((*((volatile uint8 *)(Address))) = (Data))

#define MEM_59_RENESAS_DF_WRITE16(Address, Data)              ((*((volatile uint16 *)(Address))) = (Data))

#define MEM_59_RENESAS_DF_READ32(Address)                     (*((volatile uint32 *)(Address)))                         /* PRQA S 3472 # JV-01 */

#define MEM_59_RENESAS_DF_WRITE32(Address, Data)              ((*((volatile uint32 *)(Address))) = (Data))              /* PRQA S 3472 # JV-01 */

#define MEM_59_RENESAS_CF_WRITE32(Address, Data)              ((*((volatile uint32 *)(Address))) = (Data))              /* PRQA S 3472 # JV-01 */

#define MEM_59_RENESAS_CF_WRITE16(Address, Data)              ((*((volatile uint16 *)(Address))) = (Data))

#define MEM_59_RENESAS_CF_WRITE8(Address, Data)               ((*((volatile uint8 *)(Address))) = (Data))

#define MEM_59_RENESAS_CF_READ32(Address)                     (*((volatile uint32 *)(Address)))                         /* PRQA S 3472 # JV-01 */

#define MEM_59_RENESAS_READ32(Address)                        (*((volatile uint32 *)(Address)))                         /* PRQA S 3472 # JV-01 */

#define MEM_59_RENESAS_WRITE8(Address, Data)                  ((*((volatile uint8 *)(Address))) = (Data))               /* PRQA S 3472 # JV-01 */

#define MEM_59_RENESAS_WRITE32(Address, Data)                 ((*((volatile uint32 *)(Address))) = (Data))              /* PRQA S 3472 # JV-01 */

#define MEM_59_RENESAS_REG_WRITE(REG, VAL)                    ((REG) = (VAL))                                           /* PRQA S 3472 # JV-01 */

#define MEM_59_RENESAS_DUMMY_READ_32(Address)                 (*((volatile uint32 *)(Address)))                         /* PRQA S 3472 # JV-01 */
/***********************************************************************************************************************
**                                      SchM Critical Section Protection Macros                                       **
***********************************************************************************************************************/
#define MEM_59_RENESAS_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Mem_59_Renesas_##Exclusive_Area()              /* PRQA S 0342 # JV-01 */
#define MEM_59_RENESAS_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Mem_59_Renesas_##Exclusive_Area()               /* PRQA S 0342 # JV-01 */
/***********************************************************************************************************************
**                                                  Hardware specific Service                                         **
***********************************************************************************************************************/
/* Define Id of Read Option byte service */
#define MEM_59_RENESAS_READ_OPTION_BYTES                       0x0UL

/* Define Option byte ID */
#define MEM_59_RENESAS_TOTAL_OPBT                              17UL

/* Define unit address  */
#define MEM_59_RENESAS_UNIT_REGISTER_ADDRESS                   0x04UL

/* Return value when service is not supported  */
#define E_MEM_59_RENESAS_SERVICE_NOT_AVAIL                     0x02u

/* Min data length(bytes) of Option Byte  */
#define MEM_59_RENESAS_MIN_DATA_LENGTH_OPBT                    0x04UL

/* Address of option byte from front side  */
#define MEM_59_RENESAS_OPBT0_ADDRESS_FRONT_SIDE                (uint32)(MEM_59_RENESAS_CSAF_BASE_ADDRESS + 0x3A0UL)

/* Address of option byte from back side  */
#define MEM_59_RENESAS_OPBT0_ADDRESS_BACK_SIDE                 (uint32)(MEM_59_RENESAS_CSAB_BASE_ADDRESS + 0x3A0UL)

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
**                                                 Global Data Types                                                  **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                                Extern declarations for Global Arrays Of Structures                                 **
***********************************************************************************************************************/

#endif /* MEM_59_RENESAS_PCTYPES_H  */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
