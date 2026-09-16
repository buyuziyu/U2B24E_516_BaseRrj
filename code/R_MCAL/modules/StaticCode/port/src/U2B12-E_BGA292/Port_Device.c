/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Port_Device.c                                                                                       */
/*====================================================================================================================*/
/*                                                     COPYRIGHT                                                      */
/*====================================================================================================================*/
/* (c) 2025 Renesas Electronics Corporation. All rights reserved.                                                     */
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
 * 2.3.1: 31/03/2025 : Initial Version
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
**                                               Coding Rule Violations                                               **
***********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is done as per Memory Requirement, (MEMMAP003 - Specification of Memory Mapping).       */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1533)    : The object '%1s' is only referenced by function '%2s'.                                       */
/* Rule                : MISRA C:2012 Rule-8.9, CWE Rule CWE-398, CWE-569                                             */
/* JV-01 Justification : This is accepted, due to the object is defined in separated source C file to followed        */
/*                       coding rule                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/

#include "Port.h"
#include "Port_Device.h"
/* Register Offset Address */
#define PORT_START_SEC_CONST_32
#include "Port_MemMap.h"
CONST(uint32, PORT_CONST) Port_RegOffset[PORT_REG_NUM + PORT_REG_OTHER] =
{
    /* 0:PMC */
    0x00000014UL,
    /* 1:PM */
    0x00000010UL,
    /* 2:PIPC */
    0x00004008UL,
    /* 3:PIBC */
    0x00004000UL,
    /* 4:PFC */
    0x00000018UL,
    /* 5:PFCE */
    0x0000001CUL,
    /* 6:PFCAE */
    0x00000028UL,
    /* 7:PFCEAE */
    0x0000002CUL,
    /* 8:Reserve */
    0x00000000UL,
    /* 9:Reserve */
    0x00000000UL,
    /* 10:Reserve */
    0x00000000UL,
    /* 11:Reserve */
    0x00000000UL,
    /* 12:Reserve */
    0x00000000UL,
    /* 13:Reserve */
    0x00000000UL,
    /* 14:Reserve */
    0x00000000UL,
    /* 15:PULVSEL5 */
    0x00002F80UL,
    /* 16:PU */
    0x0000400CUL,
    /* 17:PD */
    0x00004010UL,
    /* 18:PIS */
    0x0000401CUL,
    /* 19:PISA */
    0x00004024UL,
    /* 20:PEIODC */
    0x00006008UL,
    /* 21:Reserve */
    0x00000000UL,
    /* 22:Reserve */
    0x00000000UL,
    /* 23:Reserve */
    0x00000000UL,
    /* 24:PODC */
    0x00004014UL,
    /* 25:PODCE */
    0x00004038UL,
    /* 26:PDSC */
    0x00004018UL,
    /* 27:PUCC */
    0x00004028UL,
    /* 28:PINV */
    0x00000030UL,
    /* 29:PBDC */
    0x00004004UL,
    /* 30:P */
    0x00000000UL,
    /* 31:PSFTSAE */
    0x00006018UL,
    /* 32:PSFTSE */
    0x00006014UL,
    /* 33:PSFTS */
    0x00006010UL,
    /* 34:PSFC */
    0x00006000UL,
    /* 35:PKCPROT */
    0x00002F40UL,
    /* 36:PWE */
    0x00002F44UL,
    /* 37:PSR */
    0x00000004UL,
    /* 38:PMSR */
    0x00000020UL,
    /* 39:PMCSR */
    0x00000024UL,
    /* 40:PNOT */
    0x00000008UL,
    /* 41:PPR */
    0x0000000CUL
};
#define PORT_STOP_SEC_CONST_32
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */

#define PORT_START_SEC_CONST_UNSPECIFIED
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
/* PORT Information */
STATIC CONST(Port_Info, PORT_CONST) Port_Information[] = 
{
    /* Index:00 - PORT 00 */
    {
        /* usPortNum */
        0x0000U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x1FFFU, 0x0000U},
            /* PM */
            {0x1FFFU, 0xFFFFU},
            /* PIPC */
            {0x1FFFU, 0x0000U},
            /* PIBC */
            {0x1FFFU, 0x0000U},
            /* PFC */
            {0x1FFFU, 0x0000U},
            /* PFCE */
            {0x1FFFU, 0x0000U},
            /* PFCAE */
            {0x1FFFU, 0x0000U},
            /* PFCEAE */
            {0x1FFFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x1FFFU, 0x0000U},
            /* PD */
            {0x1FFFU, 0x0000U},
            /* PIS */
            {0x1FFFU, 0x0000U},
            /* PISA */
            {0x1FFFU, 0x0000U},
            /* PEIODC */
            {0x1FFFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x1FFFU, 0x0000U},
            /* PODCE */
            {0x1FFFU, 0x0000U},
            /* PDSC */
            {0x1FFFU, 0x0000U},
            /* PUCC */
            {0x1FFFU, 0x0000U},
            /* PINV */
            {0x1FFFU, 0x0000U},
            /* PBDC */
            {0x1FFFU, 0x0000U},
            /* P */
            {0x1FFFU, 0x0000U},
            /* PSFTSAE */
            {0x1FFFU, 0x0000U},
            /* PSFTSE */
            {0x1FFFU, 0x0000U},
            /* PSFTS */
            {0x1FFFU, 0x0000U},
            /* PSFC */
            {0x1FFFU, 0x0000U},
        },
        /* ulPweVal */
        0x00000001UL
    },
    /* Index:01 - PORT 01 */
    {
        /* usPortNum */
        0x0001U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x0080U, 0x0000U},
            /* PM */
            {0x0080U, 0xFFFFU},
            /* PIPC */
            {0x0080U, 0x0000U},
            /* PIBC */
            {0x0080U, 0x0000U},
            /* PFC */
            {0x0080U, 0x0000U},
            /* PFCE */
            {0x0080U, 0x0000U},
            /* PFCAE */
            {0x0080U, 0x0000U},
            /* PFCEAE */
            {0x0080U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0080U, 0x0000U},
            /* PD */
            {0x0080U, 0x0000U},
            /* PIS */
            {0x0080U, 0x0000U},
            /* PISA */
            {0x0080U, 0x0000U},
            /* PEIODC */
            {0x0080U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0080U, 0x0000U},
            /* PODCE */
            {0x0080U, 0x0000U},
            /* PDSC */
            {0x0080U, 0x0000U},
            /* PUCC */
            {0x0080U, 0x0000U},
            /* PINV */
            {0x0080U, 0x0000U},
            /* PBDC */
            {0x0080U, 0x0000U},
            /* P */
            {0x0080U, 0x0000U},
            /* PSFTSAE */
            {0x0080U, 0x0000U},
            /* PSFTSE */
            {0x0080U, 0x0000U},
            /* PSFTS */
            {0x0080U, 0x0000U},
            /* PSFC */
            {0x0080U, 0x0000U},
        },
        /* ulPweVal */
        0x00000002UL
    },
    /* Index:02 - PORT 02 */
    {
        /* usPortNum */
        0x0002U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x11FFU, 0x0000U},
            /* PM */
            {0x11FFU, 0xFFFFU},
            /* PIPC */
            {0x11FFU, 0x0000U},
            /* PIBC */
            {0x11FFU, 0x0000U},
            /* PFC */
            {0x11FFU, 0x0000U},
            /* PFCE */
            {0x11FFU, 0x0000U},
            /* PFCAE */
            {0x11FFU, 0x0000U},
            /* PFCEAE */
            {0x11FFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x11FFU, 0x0000U},
            /* PD */
            {0x11FFU, 0x0000U},
            /* PIS */
            {0x11FFU, 0x0000U},
            /* PISA */
            {0x11FFU, 0x0000U},
            /* PEIODC */
            {0x11FFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x11FFU, 0x0000U},
            /* PODCE */
            {0x11FFU, 0x0000U},
            /* PDSC */
            {0x11FFU, 0x0000U},
            /* PUCC */
            {0x11FFU, 0x0000U},
            /* PINV */
            {0x11FFU, 0x0000U},
            /* PBDC */
            {0x11FFU, 0x0000U},
            /* P */
            {0x11FFU, 0x0000U},
            /* PSFTSAE */
            {0x11FFU, 0x0000U},
            /* PSFTSE */
            {0x11FFU, 0x0000U},
            /* PSFTS */
            {0x11FFU, 0x0000U},
            /* PSFC */
            {0x11FFU, 0x0000U},
        },
        /* ulPweVal */
        0x00000004UL
    },
    /* Index:03 - PORT 03 */
    {
        /* usPortNum */
        0x0003U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x000DU, 0x0000U},
            /* PM */
            {0x000DU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0x000DU, 0x0000U},
            /* PFC */
            {0x000DU, 0x0000U},
            /* PFCE */
            {0x0000U, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x000DU, 0x0000U},
            /* PD */
            {0x000DU, 0x0000U},
            /* PIS */
            {0x000DU, 0x0000U},
            /* PISA */
            {0x000DU, 0x0000U},
            /* PEIODC */
            {0x000DU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x000DU, 0x0000U},
            /* PODCE */
            {0x000DU, 0x0000U},
            /* PDSC */
            {0x000DU, 0x0000U},
            /* PUCC */
            {0x000DU, 0x0000U},
            /* PINV */
            {0x000DU, 0x0000U},
            /* PBDC */
            {0x000DU, 0x0000U},
            /* P */
            {0x000DU, 0x0000U},
            /* PSFTSAE */
            {0x000DU, 0x0000U},
            /* PSFTSE */
            {0x000DU, 0x0000U},
            /* PSFTS */
            {0x000DU, 0x0000U},
            /* PSFC */
            {0x000DU, 0x0000U},
        },
        /* ulPweVal */
        0x00000008UL
    },
    /* Index:04 - PORT 10 */
    {
        /* usPortNum */
        0x000aU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x01FFU, 0x0000U},
            /* PM */
            {0x01FFU, 0xFFFFU},
            /* PIPC */
            {0x01FFU, 0x0000U},
            /* PIBC */
            {0x01FFU, 0x0000U},
            /* PFC */
            {0x01FFU, 0x0000U},
            /* PFCE */
            {0x01FFU, 0x0000U},
            /* PFCAE */
            {0x01FFU, 0x0000U},
            /* PFCEAE */
            {0x01FFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x01FFU, 0x0000U},
            /* PD */
            {0x01FFU, 0x0000U},
            /* PIS */
            {0x01FFU, 0x0000U},
            /* PISA */
            {0x01FFU, 0x0000U},
            /* PEIODC */
            {0x01FFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x01FFU, 0x0000U},
            /* PODCE */
            {0x01FFU, 0x0000U},
            /* PDSC */
            {0x01FFU, 0x0000U},
            /* PUCC */
            {0x01FFU, 0x0000U},
            /* PINV */
            {0x01FFU, 0x0000U},
            /* PBDC */
            {0x01FFU, 0x0000U},
            /* P */
            {0x01FFU, 0x0000U},
            /* PSFTSAE */
            {0x01FFU, 0x0000U},
            /* PSFTSE */
            {0x01FFU, 0x0000U},
            /* PSFTS */
            {0x01FFU, 0x0000U},
            /* PSFC */
            {0x01FFU, 0x0000U},
        },
        /* ulPweVal */
        0x00000010UL
    },
    /* Index:05 - PORT 11 */
    {
        /* usPortNum */
        0x000bU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0xFFFFU, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0xFFFFU, 0x0000U},
            /* PFCEAE */
            {0xFFFFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0xFFFFU, 0x0000U},
            /* PD */
            {0xFFFFU, 0x0000U},
            /* PIS */
            {0xFFFFU, 0x0000U},
            /* PISA */
            {0xFFFFU, 0x0000U},
            /* PEIODC */
            {0xFFFFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0xFFFFU, 0x0000U},
            /* PODCE */
            {0xFFFFU, 0x0000U},
            /* PDSC */
            {0xFFFFU, 0x0000U},
            /* PUCC */
            {0xFFFFU, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0xFFFFU, 0x0000U},
            /* PSFTSE */
            {0xFFFFU, 0x0000U},
            /* PSFTS */
            {0xFFFFU, 0x0000U},
            /* PSFC */
            {0xFFFFU, 0x0000U},
        },
        /* ulPweVal */
        0x00000020UL
    },
    /* Index:06 - PORT 12 */
    {
        /* usPortNum */
        0x000cU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x0003U, 0x0000U},
            /* PM */
            {0x0003U, 0xFFFFU},
            /* PIPC */
            {0x0003U, 0x0000U},
            /* PIBC */
            {0x0003U, 0x0000U},
            /* PFC */
            {0x0003U, 0x0000U},
            /* PFCE */
            {0x0003U, 0x0000U},
            /* PFCAE */
            {0x0003U, 0x0000U},
            /* PFCEAE */
            {0x0003U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0003U, 0x0000U},
            /* PD */
            {0x0003U, 0x0000U},
            /* PIS */
            {0x0003U, 0x0000U},
            /* PISA */
            {0x0003U, 0x0000U},
            /* PEIODC */
            {0x0003U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0003U, 0x0000U},
            /* PODCE */
            {0x0003U, 0x0000U},
            /* PDSC */
            {0x0003U, 0x0000U},
            /* PUCC */
            {0x0003U, 0x0000U},
            /* PINV */
            {0x0003U, 0x0000U},
            /* PBDC */
            {0x0003U, 0x0000U},
            /* P */
            {0x0003U, 0x0000U},
            /* PSFTSAE */
            {0x0003U, 0x0000U},
            /* PSFTSE */
            {0x0003U, 0x0000U},
            /* PSFTS */
            {0x0003U, 0x0000U},
            /* PSFC */
            {0x0003U, 0x0000U},
        },
        /* ulPweVal */
        0x00000040UL
    },
    /* Index:07 - PORT 13 */
    {
        /* usPortNum */
        0x000dU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x000FU, 0x0000U},
            /* PM */
            {0x000FU, 0xFFFFU},
            /* PIPC */
            {0x000FU, 0x0000U},
            /* PIBC */
            {0x000FU, 0x0000U},
            /* PFC */
            {0x000FU, 0x0000U},
            /* PFCE */
            {0x000FU, 0x0000U},
            /* PFCAE */
            {0x000FU, 0x0000U},
            /* PFCEAE */
            {0x000FU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x000FU, 0x0000U},
            /* PD */
            {0x000FU, 0x0000U},
            /* PIS */
            {0x000FU, 0x0000U},
            /* PISA */
            {0x000FU, 0x0000U},
            /* PEIODC */
            {0x000FU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x000FU, 0x0000U},
            /* PODCE */
            {0x000FU, 0x0000U},
            /* PDSC */
            {0x000FU, 0x0000U},
            /* PUCC */
            {0x000FU, 0x0000U},
            /* PINV */
            {0x000FU, 0x0000U},
            /* PBDC */
            {0x000FU, 0x0000U},
            /* P */
            {0x000FU, 0x0000U},
            /* PSFTSAE */
            {0x000FU, 0x0000U},
            /* PSFTSE */
            {0x000FU, 0x0000U},
            /* PSFTS */
            {0x000FU, 0x0000U},
            /* PSFC */
            {0x000FU, 0x0000U},
        },
        /* ulPweVal */
        0x00000080UL
    },
    /* Index:08 - PORT 14 */
    {
        /* usPortNum */
        0x000eU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x07ECU, 0x0000U},
            /* PM */
            {0x07ECU, 0xFFFFU},
            /* PIPC */
            {0x07ECU, 0x0000U},
            /* PIBC */
            {0x07ECU, 0x0000U},
            /* PFC */
            {0x07ECU, 0x0000U},
            /* PFCE */
            {0x07ECU, 0x0000U},
            /* PFCAE */
            {0x07ECU, 0x0000U},
            /* PFCEAE */
            {0x07ECU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x07ECU, 0x0000U},
            /* PD */
            {0x07ECU, 0x0000U},
            /* PIS */
            {0x07ECU, 0x0000U},
            /* PISA */
            {0x07ECU, 0x0000U},
            /* PEIODC */
            {0x07ECU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x07ECU, 0x0000U},
            /* PODCE */
            {0x07ECU, 0x0000U},
            /* PDSC */
            {0x07ECU, 0x0000U},
            /* PUCC */
            {0x07ECU, 0x0000U},
            /* PINV */
            {0x07ECU, 0x0000U},
            /* PBDC */
            {0x07ECU, 0x0000U},
            /* P */
            {0x07ECU, 0x0000U},
            /* PSFTSAE */
            {0x07ECU, 0x0000U},
            /* PSFTSE */
            {0x07ECU, 0x0000U},
            /* PSFTS */
            {0x07ECU, 0x0000U},
            /* PSFC */
            {0x07ECU, 0x0000U},
        },
        /* ulPweVal */
        0x00000100UL
    },
    /* Index:09 - PORT 15 */
    {
        /* usPortNum */
        0x000fU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xC3FFU, 0x0000U},
            /* PM */
            {0xC3FFU, 0xFFFFU},
            /* PIPC */
            {0xC25FU, 0x0000U},
            /* PIBC */
            {0xC3FFU, 0x0000U},
            /* PFC */
            {0xC3FFU, 0x0000U},
            /* PFCE */
            {0xC3FFU, 0x0000U},
            /* PFCAE */
            {0xC3FFU, 0x0000U},
            /* PFCEAE */
            {0xC3FFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0xC3FFU, 0x0000U},
            /* PD */
            {0xC3FFU, 0x0000U},
            /* PIS */
            {0xC3FFU, 0x0000U},
            /* PISA */
            {0xC3FFU, 0x0000U},
            /* PEIODC */
            {0xC3FFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0xC3FFU, 0x0000U},
            /* PODCE */
            {0xC3FFU, 0x0000U},
            /* PDSC */
            {0xC3FFU, 0x0000U},
            /* PUCC */
            {0xC3FFU, 0x0000U},
            /* PINV */
            {0xC3FFU, 0x0000U},
            /* PBDC */
            {0xC3FFU, 0x0000U},
            /* P */
            {0xC3FFU, 0x0000U},
            /* PSFTSAE */
            {0xC3FFU, 0x0000U},
            /* PSFTSE */
            {0xC3FFU, 0x0000U},
            /* PSFTS */
            {0xC3FFU, 0x0000U},
            /* PSFC */
            {0xC3FFU, 0x0000U},
        },
        /* ulPweVal */
        0x00000200UL
    },
    /* Index:10 - PORT 20 */
    {
        /* usPortNum */
        0x0014U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x7FC9U, 0x0000U},
            /* PM */
            {0x7FC9U, 0xFFFFU},
            /* PIPC */
            {0x7FC9U, 0x0000U},
            /* PIBC */
            {0x7FC9U, 0x0000U},
            /* PFC */
            {0x7FC9U, 0x0000U},
            /* PFCE */
            {0x7FC9U, 0x0000U},
            /* PFCAE */
            {0x7FC9U, 0x0000U},
            /* PFCEAE */
            {0x7FC9U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x7FC9U, 0x0000U},
            /* PD */
            {0x7FC9U, 0x0000U},
            /* PIS */
            {0x7FC9U, 0x0000U},
            /* PISA */
            {0x7FC9U, 0x0000U},
            /* PEIODC */
            {0x7FC9U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x7FC9U, 0x0000U},
            /* PODCE */
            {0x7FC9U, 0x0000U},
            /* PDSC */
            {0x7FC9U, 0x0000U},
            /* PUCC */
            {0x7FC9U, 0x0000U},
            /* PINV */
            {0x7FC9U, 0x0000U},
            /* PBDC */
            {0x7FC9U, 0x0000U},
            /* P */
            {0x7FC9U, 0x0000U},
            /* PSFTSAE */
            {0x7FC9U, 0x0000U},
            /* PSFTSE */
            {0x7FC9U, 0x0000U},
            /* PSFTS */
            {0x7FC9U, 0x0000U},
            /* PSFC */
            {0x7FC9U, 0x0000U},
        },
        /* ulPweVal */
        0x00000800UL
    },
    /* Index:11 - PORT 21 */
    {
        /* usPortNum */
        0x0015U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x003FU, 0x0000U},
            /* PM */
            {0x003FU, 0xFFFFU},
            /* PIPC */
            {0x003FU, 0x0000U},
            /* PIBC */
            {0x003FU, 0x0000U},
            /* PFC */
            {0x003FU, 0x0000U},
            /* PFCE */
            {0x003FU, 0x0000U},
            /* PFCAE */
            {0x003FU, 0x0000U},
            /* PFCEAE */
            {0x003FU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x003FU, 0x0000U},
            /* PD */
            {0x003FU, 0x0000U},
            /* PIS */
            {0x003FU, 0x0000U},
            /* PISA */
            {0x003FU, 0x0000U},
            /* PEIODC */
            {0x003FU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x003FU, 0x0000U},
            /* PODCE */
            {0x003FU, 0x0000U},
            /* PDSC */
            {0x003FU, 0x0000U},
            /* PUCC */
            {0x003FU, 0x0000U},
            /* PINV */
            {0x003FU, 0x0000U},
            /* PBDC */
            {0x003FU, 0x0000U},
            /* P */
            {0x003FU, 0x0000U},
            /* PSFTSAE */
            {0x003FU, 0x0000U},
            /* PSFTSE */
            {0x003FU, 0x0000U},
            /* PSFTS */
            {0x003FU, 0x0000U},
            /* PSFC */
            {0x003FU, 0x0000U},
        },
        /* ulPweVal */
        0x00001000UL
    },
    /* Index:12 - PORT 22 */
    {
        /* usPortNum */
        0x0016U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x0FFFU, 0x0000U},
            /* PM */
            {0x0FFFU, 0xFFFFU},
            /* PIPC */
            {0x0FFFU, 0x0000U},
            /* PIBC */
            {0x0FFFU, 0x0000U},
            /* PFC */
            {0x0FFFU, 0x0000U},
            /* PFCE */
            {0x0FFFU, 0x0000U},
            /* PFCAE */
            {0x0FFFU, 0x0000U},
            /* PFCEAE */
            {0x0FFFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0FFFU, 0x0000U},
            /* PD */
            {0x0FFFU, 0x0000U},
            /* PIS */
            {0x0FFFU, 0x0000U},
            /* PISA */
            {0x0FFFU, 0x0000U},
            /* PEIODC */
            {0x0FFFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0FFFU, 0x0000U},
            /* PODCE */
            {0x0FFFU, 0x0000U},
            /* PDSC */
            {0x0FFFU, 0x0000U},
            /* PUCC */
            {0x0FFFU, 0x0000U},
            /* PINV */
            {0x0FFFU, 0x0000U},
            /* PBDC */
            {0x0FFFU, 0x0000U},
            /* P */
            {0x0FFFU, 0x0000U},
            /* PSFTSAE */
            {0x0FFFU, 0x0000U},
            /* PSFTSE */
            {0x0FFFU, 0x0000U},
            /* PSFTS */
            {0x0FFFU, 0x0000U},
            /* PSFC */
            {0x0FFFU, 0x0000U},
        },
        /* ulPweVal */
        0x00002000UL
    },
    /* Index:13 - PORT 23 */
    {
        /* usPortNum */
        0x0017U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x00DFU, 0x0000U},
            /* PM */
            {0x00DFU, 0xFFFFU},
            /* PIPC */
            {0x00DFU, 0x0000U},
            /* PIBC */
            {0x00DFU, 0x0000U},
            /* PFC */
            {0x00DFU, 0x0000U},
            /* PFCE */
            {0x00DFU, 0x0000U},
            /* PFCAE */
            {0x00DFU, 0x0000U},
            /* PFCEAE */
            {0x00DFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x00DFU, 0x0000U},
            /* PD */
            {0x00DFU, 0x0000U},
            /* PIS */
            {0x00DFU, 0x0000U},
            /* PISA */
            {0x00DFU, 0x0000U},
            /* PEIODC */
            {0x00DFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x00DFU, 0x0000U},
            /* PODCE */
            {0x00DFU, 0x0000U},
            /* PDSC */
            {0x00DFU, 0x0000U},
            /* PUCC */
            {0x00DFU, 0x0000U},
            /* PINV */
            {0x00DFU, 0x0000U},
            /* PBDC */
            {0x00DFU, 0x0000U},
            /* P */
            {0x00DFU, 0x0000U},
            /* PSFTSAE */
            {0x00DFU, 0x0000U},
            /* PSFTSE */
            {0x00DFU, 0x0000U},
            /* PSFTS */
            {0x00DFU, 0x0000U},
            /* PSFC */
            {0x00DFU, 0x0000U},
        },
        /* ulPweVal */
        0x00004000UL
    },
    /* Index:14 - PORT 27 */
    {
        /* usPortNum */
        0x001bU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x0001U, 0x0000U},
            /* PM */
            {0x0001U, 0xFFFEU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0x0001U, 0x0000U},
            /* PFC */
            {0x0000U, 0x0000U},
            /* PFCE */
            {0x0000U, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0001U, 0x0000U},
            /* PD */
            {0x0001U, 0x0000U},
            /* PIS */
            {0x0001U, 0x0000U},
            /* PISA */
            {0x0001U, 0x0000U},
            /* PEIODC */
            {0x0001U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0001U, 0x0000U},
            /* PODCE */
            {0x0001U, 0x0000U},
            /* PDSC */
            {0x0001U, 0x0001U},
            /* PUCC */
            {0x0001U, 0x0001U},
            /* PINV */
            {0x0001U, 0x0000U},
            /* PBDC */
            {0x0001U, 0x0000U},
            /* P */
            {0x0001U, 0x0000U},
            /* PSFTSAE */
            {0x0001U, 0x0000U},
            /* PSFTSE */
            {0x0001U, 0x0000U},
            /* PSFTS */
            {0x0001U, 0x0000U},
            /* PSFC */
            {0x0001U, 0x0000U},
        },
        /* ulPweVal */
        0x00040000UL
    },
    /* Index:15 - PORT 28 */
    {
        /* usPortNum */
        0x001cU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x0002U, 0x0000U},
            /* PM */
            {0x0002U, 0xFFFDU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0x0002U, 0x0000U},
            /* PFC */
            {0x0000U, 0x0000U},
            /* PFCE */
            {0x0000U, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0002U, 0x0000U},
            /* PD */
            {0x0002U, 0x0000U},
            /* PIS */
            {0x0002U, 0x0000U},
            /* PISA */
            {0x0002U, 0x0000U},
            /* PEIODC */
            {0x0002U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0002U, 0x0000U},
            /* PODCE */
            {0x0002U, 0x0000U},
            /* PDSC */
            {0x0002U, 0x0002U},
            /* PUCC */
            {0x0002U, 0x0002U},
            /* PINV */
            {0x0002U, 0x0000U},
            /* PBDC */
            {0x0002U, 0x0000U},
            /* P */
            {0x0002U, 0x0000U},
            /* PSFTSAE */
            {0x0002U, 0x0000U},
            /* PSFTSE */
            {0x0002U, 0x0000U},
            /* PSFTS */
            {0x0002U, 0x0000U},
            /* PSFC */
            {0x0002U, 0x0000U},
        },
        /* ulPweVal */
        0x00080000UL
    },
    /* Index:16 - PORT 32 */
    {
        /* usPortNum */
        0x0020U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x00ECU, 0x0000U},
            /* PM */
            {0x00ECU, 0xFFFFU},
            /* PIPC */
            {0x00ECU, 0x0000U},
            /* PIBC */
            {0x00ECU, 0x0000U},
            /* PFC */
            {0x00ECU, 0x0000U},
            /* PFCE */
            {0x00ECU, 0x0000U},
            /* PFCAE */
            {0x00ECU, 0x0000U},
            /* PFCEAE */
            {0x00ECU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x00ECU, 0x0000U},
            /* PD */
            {0x00ECU, 0x0000U},
            /* PIS */
            {0x00ECU, 0x0000U},
            /* PISA */
            {0x00ECU, 0x0000U},
            /* PEIODC */
            {0x00ECU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x00ECU, 0x0000U},
            /* PODCE */
            {0x00ECU, 0x0000U},
            /* PDSC */
            {0x00ECU, 0x0000U},
            /* PUCC */
            {0x00ECU, 0x0000U},
            /* PINV */
            {0x00ECU, 0x0000U},
            /* PBDC */
            {0x00ECU, 0x0000U},
            /* P */
            {0x00ECU, 0x0000U},
            /* PSFTSAE */
            {0x00ECU, 0x0000U},
            /* PSFTSE */
            {0x00ECU, 0x0000U},
            /* PSFTS */
            {0x00ECU, 0x0000U},
            /* PSFC */
            {0x00ECU, 0x0000U},
        },
        /* ulPweVal */
        0x00400000UL
    },
    /* Index:17 - PORT 33 */
    {
        /* usPortNum */
        0x0021U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0xFFFFU, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0xFFFFU, 0x0000U},
            /* PFCEAE */
            {0xFFFFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0xFFFFU, 0x0000U},
            /* PD */
            {0xFFFFU, 0x0000U},
            /* PIS */
            {0xFFFFU, 0x0000U},
            /* PISA */
            {0xFFFFU, 0x0000U},
            /* PEIODC */
            {0xFFFFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0xFFFFU, 0x0000U},
            /* PODCE */
            {0xFFFFU, 0x0000U},
            /* PDSC */
            {0xFFFFU, 0x0000U},
            /* PUCC */
            {0xFFFFU, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0xFFFFU, 0x0000U},
            /* PSFTSE */
            {0xFFFFU, 0x0000U},
            /* PSFTS */
            {0xFFFFU, 0x0000U},
            /* PSFC */
            {0xFFFFU, 0x0000U},
        },
        /* ulPweVal */
        0x00800000UL
    },
    /* Index:18 - PORT 34 */
    {
        /* usPortNum */
        0x0022U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x6034U, 0x0000U},
            /* PM */
            {0x403EU, 0xFFFFU},
            /* PIPC */
            {0x0034U, 0x0000U},
            /* PIBC */
            {0x603EU, 0x0000U},
            /* PFC */
            {0x4034U, 0x0000U},
            /* PFCE */
            {0x0034U, 0x0000U},
            /* PFCAE */
            {0x0034U, 0x0000U},
            /* PFCEAE */
            {0x0034U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x603EU, 0x0000U},
            /* PD */
            {0x603EU, 0x0000U},
            /* PIS */
            {0x603EU, 0x0000U},
            /* PISA */
            {0x603EU, 0x0000U},
            /* PEIODC */
            {0x603EU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x603EU, 0x0000U},
            /* PODCE */
            {0x603EU, 0x0000U},
            /* PDSC */
            {0x603EU, 0x0000U},
            /* PUCC */
            {0x603EU, 0x0000U},
            /* PINV */
            {0x603EU, 0x0000U},
            /* PBDC */
            {0x603EU, 0x0000U},
            /* P */
            {0x603EU, 0x0000U},
            /* PSFTSAE */
            {0x603EU, 0x0000U},
            /* PSFTSE */
            {0x603EU, 0x0000U},
            /* PSFTS */
            {0x603EU, 0x0000U},
            /* PSFC */
            {0x603EU, 0x0000U},
        },
        /* ulPweVal */
        0x01000000UL
    },
    /* Index:19 - PORT 36 */
    {
        /* usPortNum */
        0x0024U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFC00U, 0x0000U},
            /* PM */
            {0x7400U, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFC00U, 0x0000U},
            /* PFC */
            {0x0000U, 0x0000U},
            /* PFCE */
            {0x0000U, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0xFC00U, 0x0000U},
            /* PD */
            {0xFC00U, 0x0000U},
            /* PIS */
            {0xFC00U, 0x0000U},
            /* PISA */
            {0xFC00U, 0x0000U},
            /* PEIODC */
            {0xFC00U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0xFC00U, 0x0000U},
            /* PODCE */
            {0xFC00U, 0x0000U},
            /* PDSC */
            {0xFC00U, 0x0000U},
            /* PUCC */
            {0xFC00U, 0x0000U},
            /* PINV */
            {0xFC00U, 0x0000U},
            /* PBDC */
            {0xFC00U, 0x0000U},
            /* P */
            {0xFC00U, 0x0000U},
            /* PSFTSAE */
            {0xFC00U, 0x0000U},
            /* PSFTSE */
            {0xFC00U, 0x0000U},
            /* PSFTS */
            {0xFC00U, 0x0000U},
            /* PSFC */
            {0xFC00U, 0x0000U},
        },
        /* ulPweVal */
        0x02000000UL
    },
    /* Index:20 - PORT 37 */
    {
        /* usPortNum */
        0x0025U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:21 - PORT 38 */
    {
        /* usPortNum */
        0x0026U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:22 - PORT 39 */
    {
        /* usPortNum */
        0x0027U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0x0000U, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:23 - PORT 40 */
    {
        /* usPortNum */
        0x0028U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFBFFU, 0x0000U},
            /* PM */
            {0xFBFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFBFFU, 0x0000U},
            /* PFC */
            {0x8370U, 0x0000U},
            /* PFCE */
            {0x8100U, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0xFBFFU, 0x0000U},
            /* PD */
            {0xFBFFU, 0x0000U},
            /* PIS */
            {0xFBFFU, 0x0000U},
            /* PISA */
            {0xFBFFU, 0x0000U},
            /* PEIODC */
            {0xFBFFU, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0xFBFFU, 0x0000U},
            /* PODCE */
            {0xFBFFU, 0x0000U},
            /* PDSC */
            {0xFBFFU, 0x0000U},
            /* PUCC */
            {0xFBFFU, 0x0000U},
            /* PINV */
            {0xFBFFU, 0x0000U},
            /* PBDC */
            {0xFBFFU, 0x0000U},
            /* P */
            {0xFBFFU, 0x0000U},
            /* PSFTSAE */
            {0xFBFFU, 0x0000U},
            /* PSFTSE */
            {0xFBFFU, 0x0000U},
            /* PSFTS */
            {0xFBFFU, 0x0000U},
            /* PSFC */
            {0xFBFFU, 0x0000U},
        },
        /* ulPweVal */
        0x04000000UL
    },
    /* Index:24 - PORT 41 */
    {
        /* usPortNum */
        0x0029U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x0000U, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0x0000U, 0x0000U},
            /* PFCE */
            {0x0000U, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:25 - PORT 42 */
    {
        /* usPortNum */
        0x002aU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x0000U, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0x0000U, 0x0000U},
            /* PFCE */
            {0x0000U, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:26 - PORT 43 */
    {
        /* usPortNum */
        0x002bU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x0000U, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0x0000U, 0x0000U},
            /* PFCE */
            {0x0000U, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:27 - PORT 44 */
    {
        /* usPortNum */
        0x002cU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0x0000U, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0x0000U, 0x0000U},
            /* PFCE */
            {0x0000U, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:28 - PORT 45 */
    {
        /* usPortNum */
        0x002dU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:29 - PORT 46 */
    {
        /* usPortNum */
        0x002eU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:30 - PORT 47 */
    {
        /* usPortNum */
        0x002fU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:31 - PORT 48 */
    {
        /* usPortNum */
        0x0030U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:32 - PORT 57 */
    {
        /* usPortNum */
        0x0039U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:33 - PORT 58 */
    {
        /* usPortNum */
        0x003aU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:34 - PORT 59 */
    {
        /* usPortNum */
        0x003bU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:35 - PORT 60 */
    {
        /* usPortNum */
        0x003cU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    }
};

/* JPORT Information */
STATIC CONST(Port_Info, PORT_CONST) JPort_Information[] =
{
  /* Index:00 - JPORT 00 */
  {
    /* usPortNum */
    0x0000U,
    /* Port_Reg_info */
    /*  usValid,  usResetVal */
    {
      #if (PORT_JTAG_DEBUGGING == STD_ON)
      /* PMC */
      { 0x0000U,  0x0000U },
      /* PM */
      { 0x0000U,  0x00FFU },
      /* PIPC */
      { 0x0000U,  0x0000U },
      /* PIBC */
      { 0x0000U,  0x0005U },
      /* PFC */
      { 0x0000U,  0x0000U },
      /* PFCE */
      { 0x0000U,  0x0000U },
      /* PFCAE */
      { 0x0000U,  0x0000U },
      /* PFCEAE */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* PU */
      { 0x0000U,  0x0005U },
      /* PD */
      { 0x0000U,  0x0000U },
      /* PIS */
      { 0x0000U,  0x0000U },
      /* PISA */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* PODC */
      { 0x0000U,  0x0000U },
      /* PODCE */
      { 0x0000U,  0x0000U },
      /* PDSC */
      { 0x0000U,  0x0000U },
      /* PUCC */
      { 0x0000U,  0x0000U },
      /* PINV */
      { 0x0000U,  0x0000U },
      /* PBDC */
      { 0x0000U,  0x0000U },
      /* P */
      { 0x0000U,  0x0000U },
      /* PSFTSAE */
      { 0x0000U,  0x0000U },
      /* PSFTSE */
      { 0x0000U,  0x0000U },
      /* PSFTS */
      { 0x0000U,  0x0000U },
      /* PSFC */
      { 0x0000U,  0x0000U }
      #else
      /* PMC */
      { 0x0027U,  0x0000U },
      /* PM */
      { 0x002FU,  0x00FFU },
      /* PIPC */
      { 0x0027U,  0x0000U },
      /* PIBC */
      { 0x002FU,  0x0005U },
      /* PFC */
      { 0x0020U,  0x0000U },
      /* PFCE */
      { 0x0020U,  0x0000U },
      /* PFCAE */
      { 0x0020U,  0x0000U },
      /* PFCEAE */
      { 0x0020U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* PU */
      { 0x002FU,  0x0005U },
      /* PD */
      { 0x002FU,  0x0000U },
      /* PIS */
      { 0x002FU,  0x0000U },
      /* PISA */
      { 0x002FU,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* Reserve */
      { 0x0000U,  0x0000U },
      /* PODC */
      { 0x002FU,  0x0000U },
      /* PODCE */
      { 0x002FU,  0x0000U },
      /* PDSC */
      { 0x002FU,  0x0000U },
      /* PUCC */
      { 0x002FU,  0x0000U },
      /* PINV */
      { 0x002FU,  0x0000U },
      /* PBDC */
      { 0x002FU,  0x0000U },
      /* P */
      { 0x002FU,  0x0000U },
      /* PSFTSAE */
      { 0x0000U,  0x0000U },
      /* PSFTSE */
      { 0x0000U,  0x0000U },
      /* PSFTS */
      { 0x0000U,  0x0000U },
      /* PSFC */
      { 0x0000U,  0x0000U }
      #endif
    },
    /* ulPweVal */
    0x00000000UL
  }
};


/* APORT Information */
STATIC CONST(Port_Info, PORT_CONST) APort_Information[] = 
{
   /* Index:00 - PORT 57 */
    {
        /* usPortNum */
        0x0007U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:01 - PORT 58 */
    {
        /* usPortNum */
        0x0008U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:02 - PORT 59 */
    {
        /* usPortNum */
        0x0009U,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    },
    /* Index:03 - PORT 60 */
    {
        /* usPortNum */
        0x000aU,
        /* Port_Reg_info */
        /*  usValid,  usResetVal */
        {
            /* PMC */
            {0xFFFFU, 0x0000U},
            /* PM */
            {0xFFFFU, 0xFFFFU},
            /* PIPC */
            {0x0000U, 0x0000U},
            /* PIBC */
            {0xFFFFU, 0x0000U},
            /* PFC */
            {0xFFFFU, 0x0000U},
            /* PFCE */
            {0xFFFFU, 0x0000U},
            /* PFCAE */
            {0x0000U, 0x0000U},
            /* PFCEAE */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PU */
            {0x0000U, 0x0000U},
            /* PD */
            {0x0000U, 0x0000U},
            /* PIS */
            {0x0000U, 0x0000U},
            /* PISA */
            {0x0000U, 0x0000U},
            /* PEIODC */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* Reserve */
            {0x0000U, 0x0000U},
            /* PODC */
            {0x0000U, 0x0000U},
            /* PODCE */
            {0x0000U, 0x0000U},
            /* PDSC */
            {0x0000U, 0x0000U},
            /* PUCC */
            {0x0000U, 0x0000U},
            /* PINV */
            {0xFFFFU, 0x0000U},
            /* PBDC */
            {0xFFFFU, 0x0000U},
            /* P */
            {0xFFFFU, 0x0000U},
            /* PSFTSAE */
            {0x0000U, 0x0000U},
            /* PSFTSE */
            {0x0000U, 0x0000U},
            /* PSFTS */
            {0x0000U, 0x0000U},
            /* PSFC */
            {0x0000U, 0x0000U},
        },
        /* ulPweVal */
        0x00000000UL
    }
};

/* Port ID Information */
CONST(Port_Type_Info, PORT_CONST) Port_TypeInformation[PORT_TYPE_NUM] = 
{
    /* JPORT */
    {
        /* Number of Bit */
        PORT_BIT_8,
        /* Number of Port */
        1U,
        /* Base Address */
        0xFFDA0000UL,
        /* Address of Port Information */
        &JPort_Information[0]
    },
    /* PORT */
    {
        /* Number of Bit */
        PORT_BIT_16,
        /* Number of Port */
        36U,
        /* Base Address */
        0xFFD90000UL,
        /* Address of Port Information */
        &Port_Information[0]
    },
    /* APORT */
    {
        /* Number of Bit */
        PORT_BIT_16,
        /* Number of Port */
        4U,
        /* Base Address */
        0xFFD90C80UL,
        /* Address of Port Information */
        &APort_Information[0]
    }
};
#define PORT_STOP_SEC_CONST_UNSPECIFIED
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */

#define PORT_START_SEC_CONST_16
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
CONST(Port_DNF_Info, PORT_CONST) Port_DNF_Information =                                                                 /* PRQA S 1533 # JV-01 */
{
    {
        /* DNF01 valid */
        0x0003U, //RLIN3
        0x0003U, //RSCAN
        0x0001U, //FLXA
        0x00FFU, //RSENT
        0x00FFU, //RSENT1
        0x00FFU, //RSENT2
        0x003FU, //RSENT3
        0x0003U, //PSI5
        0x0000U, //Reserve
        0x0000U, //Reserve
        0x00FFU, //IRQ0
        0x00FFU, //IRQ1
        0x00FFU, //IRQ2
        0x00FFU, //IRQ3
        0x00FFU, //IRQ4
        0x007FU, //IRQ5
        0x0000U, //Reserve
        0x0000U, //Reserve
        0x0000U, //TAUJ2
        0x0000U, //Reserve
        0x0001U, //ESR0IRQ
        0x0001U, //ESR0NMI
        0x0001U  //ESR1NMI
    },
    {
        /* DNF02 valid */
        0x0001U, //PortFilterRLIN3
        0x0001U, //PortFilterRSCAN
        0x0001U, //PortFilterFLXA
        0x0001U, //PortFilterRSENT
        0x0001U, //PortFilterRSENT1
        0x0001U, //PortFilterPSI5
        0x0000U, //PortFilterTAPA
        0x0001U, //PortFilterADCK0
        0x0001U, //PortFilterADCK1
        0x0001U, //PortFilterADCK2
        0x0000U, //Reserve
        0x0000U, //Reserve
        0x0001U, //PortFilterRHSB
        0x0000U, //Reserve
        0x0000U, //Reserve
        0x0000U, //Reserve
        0x0000U, //Reserve
        0x0000U, //Reserve
        0x0000U, //Reserve
        0x0001U, //PortFilterECM
        0x0000U, //Reserve
        0x0000U, //Reserve
        0x0001U, //PortFilterTAUJ2
        0x0000U, //Reserve
        0x0000U, //Reserve
        0x0000U, //Reserve
        0x0000U, //Reserve
        0x0001U, //PortFilterESR0IRQ
        0x0001U, //PortFilterESR0NMI
        0x0001U  //PortFilterESR1NMI
    },
    {
        /* DNFP03 valid */
        0x1FFFU,// P00
        0x0080U,// P01
        0x11FFU,// P02
        0x000DU,// P03
        0x0000U,// Reserve
        0x0000U,// Reserve
        0x0000U,// Reserve
        0x0000U,// Reserve
        0x0000U,// Reserve
        0x0000U,// Reserve
        0x01FFU,// P10
        0xFFFFU,// P11
        0x0003U,// P12
        0x000FU,// P13
        0x07ECU,// P14
        0xC3FFU,// P15
        0x0000U,// Reserve
        0x0000U,// Reserve
        0x0000U,// Reserve
        0x0000U,// Reserve
        0x7FC9U,// P20
        0x003FU,// P21
        0x0FFFU,// P22
        0x00DFU,// P23
        0x0000U,// Reserve
        0x0000U,// Reserve
        0x0000U,// Reserve
        0x0001U,// P27
        0x0002U,// P28
        0x0000U,// Reserve
        0x0000U,// Reserve
        0x0000U,// Reserve
        0x00ECU,// P32
        0xFFFFU,// P33
        0x403EU,// P34
        0x0000U,// Reserve
        0x7400U,// P36
        0x0000U,// Reserve
        0x0000U,// Reserve
        0x0000U,// Reserve
        0xFBFFU // P40
    },
    /* DNFP02_2 valid */
    0x0000U
};
#define PORT_STOP_SEC_CONST_16
#include "Port_MemMap.h"                                                                                                /* PRQA S 5087 # JV-01 */
/***********************************************************************************************************************
**                                                    End of File                                                     **
***********************************************************************************************************************/
