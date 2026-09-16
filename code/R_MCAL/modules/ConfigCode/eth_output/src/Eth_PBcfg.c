/*====================================================================================================================*/
/* Project      = AUTOSAR Renesas X2x MCAL Components                                                                 */
/* Module       = Eth_PBcfg.c                                                                                         */
/*====================================================================================================================*/
/*                                  COPYRIGHT                                                                         */
/*====================================================================================================================*/
/* (c) 2023, 2024 Renesas Electronics Corporation. All rights reserved.                                               */
/*====================================================================================================================*/
/* Purpose:                                                                                                           */
/* This file contains post-build time parameters.                                                                     */
/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                                         */
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
/* Renesas shall not have any obligation to maintain, service or provide bug fixes for the supplied Product(s)        */
/* and/or the Application.                                                                                            */
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
/*              Devices:        R7F7025BxFABC                                                                         */
/*====================================================================================================================*/


/***********************************************************************************************************************
**                      Revision Control History                                                                      **
***********************************************************************************************************************/



/***********************************************************************************************************************
**                      Generation Tool Version                                                                       **
***********************************************************************************************************************/
/*                                                                                                                    */
/* TOOL VERSION:  EthU2Bx-E.dll version: 2.4.1, MCALConfGen.exe version: 2.3.0                                        */
/*                                                                                                                    */


/***********************************************************************************************************************
**                      Input File                                                                                    **
***********************************************************************************************************************/
/*
 * INPUT FILE:    C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\U2B24-E.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\modules\eth\generator\U2B24-E\R2211_eth_U2B24-E_BSWMDT.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Dem\xml\Dem_eth.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\Os\xml\Os_eth.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\X2x\common\generic\stubs\22_11\EcuC\xml\EcuC_eth.arxml
 *                C:\_WorkSpace\WorkFiles\9_MCAL\3_arxml\AUTOSAR_RH850_U2Bx-E_MCAL_Ver22.00.03\MCAL_RH850U2B24E_516_CodeGen\Translation.trxml
 * GENERATED ON:  10 Jul 2026 - 18:49:26
 */


/***********************************************************************************************************************
**                      Instance Index                                                                                **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Include Section                                                                               **
***********************************************************************************************************************/
#include "Eth.h"

#include "Eth_Ram.h"

#include "Eth_ETNE_Ram.h"


/***********************************************************************************************************************
**                      Coding Rule Violations                                                                        **
***********************************************************************************************************************/
/* Message (2:0315)    : [I] Implicit conversion from a pointer to object type to a pointer to void.                  */
/* Rule                : MISRA C:2012 Dir-1.1                                                                         */
/*                       REFERENCE - ISO-6.3.4 Semantics                                                              */
/* JV-01 Justification : Pointer to a void is a generic pointer type which can be use cast to any other pointer type. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (4:5087)    : Use of #include directive after code fragment.                                               */
/* Rule                : MISRA C:2012 Rule-20.1                                                                       */
/* JV-01 Justification : This is accepted, due to implementation for include memmap is following AUTOSAR rule.        */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0612)    : [L] Size of object '%s' exceeds 32767 bytes - program does not conform strictly to ISO:C90.  */
/* Rule                : MISRA-C:2012 Dir 1.1                                                                         */
/* JV-01 Justification : Size of global variable exceeds 32767 due to size of Tx buffer byte of Eth module.           */
/*       Verification  : There is no problem because it is an intended design considering the space-time tradeoff,    */
/*                       that is, scalability.                                                                        */
/**********************************************************************************************************************/
/* Message (1:1531)    : The object '%1s' is referenced in only one translation unit - but not the one in which it    */
/*                       is defined.                                                                                  */
/* Rule                : CERTCCM DCL15, DCL19, MISRA C:2012 Rule-8.7                                                  */
/* JV-01 Justification : Followed coding rules, the objects (global variable/const) is define in separated source     */
/*                       file, so this could be accepted                                                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1533)    : The object 'entity' is only referenced by function 'func'.                                   */
/* Rule                : MISRA C:2012 Rule-8.9                                                                        */
/* JV-01 Justification : This is accepted, due to the object is defined in seperated cource C file to followed        */
/*                       coding rule                                                                                  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3432)    : Simple macro argument expression is not parenthesized.                                       */
/* Rule                : MISRA C:2012 Rule-20.7                                                                       */
/* JV-01 Justification : Compiler keyword (macro) is defined and used followed AUTOSAR standard rule. It is accepted. */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:0306)    : [I] Cast between a pointer to object and an integral type.                                   */
/* Rule                : CERTCCM INT36, MISRA C:2012 Rule-11.4                                                        */
/*                       REFERENCE - ISO:C90-6.3.4  Semantics                                                         */
/* JV-01 Justification : This cast is essential to declare a pointer which points an I/O register.                    */
/*       Verification  : These pointers are const values and only used for I/O accesses, any problem doesn't occur.   */
/**********************************************************************************************************************/
/* Message (2:0686)    : Array has fewer initializers than its declared size. Default initialization is applied to    */
/*                       the remainder of the array elements.                                                         */
/* Rule                : MISRA C:2012 Rule-9.3, CWE Rule CWE-665, CWE-452                                             */
/* JV-01 Justification : This initialization to avoid passing address of uninitialized object. This can be accepted.  */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1504)    : The object '%1s' is only referenced in the translation unit where it is defined.             */
/* Rule                : CERTCCM DCL15, DCL19, MISRA C:2012 Rule-8.7                                                  */
/* JV-01 Justification : This is accepted, due to following coding rule, internal function can be defined in other C  */
/*                       source files                                                                                 */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (2:3408)    : %s' has external linkage and is being defined without any previous declaration.              */
/* Rule                : CERTCCM DCL07, MISRA C:2012 Rule-8.4                                                         */
/* JV-01 Justification : It is accepted, due to the declaration will be taken care by Os                              */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/
/* Message (1:1502)    : The object 'name' is defined but is not used within this project.                            */
/* Rule                : MISRA C:2012 Rule-2.8, CWE Rule CWE-398, CWE-569, CERTC Rule MSC13                           */
/* JV-01 Justification : Array is used in another part of driver code. There is no problem in use                     */
/*       Verification  : However, part of the code is verified manually and it is not having any impact.              */
/**********************************************************************************************************************/



/***********************************************************************************************************************
**                      Version Information                                                                           **
***********************************************************************************************************************/
/* AUTOSAR release version information */
#define ETH_PBCFG_C_AR_RELEASE_MAJOR_VERSION                                    4U
#define ETH_PBCFG_C_AR_RELEASE_MINOR_VERSION                                    8U
#define ETH_PBCFG_C_AR_RELEASE_REVISION_VERSION                                 0U
/* File version information */
#define ETH_PBCFG_C_SW_MAJOR_VERSION                                            2U
#define ETH_PBCFG_C_SW_MINOR_VERSION                                            4U

/***********************************************************************************************************************
**                      Version Check                                                                                 **
***********************************************************************************************************************/
#if (ETH_TYPES_AR_RELEASE_MAJOR_VERSION != \
      ETH_PBCFG_C_AR_RELEASE_MAJOR_VERSION)
#error "Eth_PBcfg.c : Mismatch in Release Major Version"
#endif
#if (ETH_TYPES_AR_RELEASE_MINOR_VERSION != \
      ETH_PBCFG_C_AR_RELEASE_MINOR_VERSION)
#error "Eth_PBcfg.c : Mismatch in Release Minor Version"
#endif
#if (ETH_TYPES_AR_RELEASE_REVISION_VERSION != \
      ETH_PBCFG_C_AR_RELEASE_REVISION_VERSION)
#error "Eth_PBcfg.c : Mismatch in Release Revision Version"
#endif
#if (ETH_TYPES_SW_MAJOR_VERSION != ETH_PBCFG_C_SW_MAJOR_VERSION)
      #error "Eth_PBcfg.c : Mismatch in Software Major Version"
#endif
#if (ETH_TYPES_SW_MINOR_VERSION != ETH_PBCFG_C_SW_MINOR_VERSION)
      #error "Eth_PBcfg.c : Mismatch in Software Minor Version"
#endif


/***********************************************************************************************************************
**                      Global Data Types                                                                             **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      Global Data                                                                                   **
***********************************************************************************************************************/
#define ETH_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"

STATIC VAR(Eth_TxBufferType, ETH_VAR_NO_INIT) Eth_GaaTxBufferMgr_0[ETH_TX_BUF_TOTAL_0];
STATIC VAR(Eth_TxBufferType, ETH_VAR_NO_INIT) Eth_GaaTxBufferMgr_1[ETH_TX_BUF_TOTAL_1];
#define ETH_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_PORT_BUFFER_0
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC VAR(uint8, ETH_VAR_NO_INIT) Eth_GaaMemPoolBuffer_0[0x0000EB40UL];                                                /* PRQA S 0612 # JV-01 */
#define ETH_STOP_SEC_VAR_PORT_BUFFER_0
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_PORT_BUFFER_1
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

STATIC VAR(uint8, ETH_VAR_NO_INIT) Eth_GaaMemPoolBuffer_1[0x0000EB40UL];                                                /* PRQA S 0612 # JV-01 */
#define ETH_STOP_SEC_VAR_PORT_BUFFER_1
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_PORT_BUFFER_2
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_PORT_BUFFER_2
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_VAR_PORT_BUFFER_3
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_STOP_SEC_VAR_PORT_BUFFER_3
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */

#define ETH_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


static CONST(Eth_EthConfigType, ETH_CONFIG_DATA) Eth_GaaEthConfiguration[] =
{
  /* Index: 0 - Eth_GaaEthConfiguration */
  {
    /* enEthSpeed */
    ETH_MAC_LAYER_SPEED_1G,

    /* enEthDuplex */
    ETH_FULL_DUPLEX,

    /* enInternalLoopBackMode */
    ETH_DISABLE,

    /* enEthPHYInterface */
    ETH_SGMII,

    /* enTxInterruptMode */
    ETH_DISABLE,

    /* enRxInterruptMode */
    ETH_DISABLE
  },
  /* Index: 1 - Eth_GaaEthConfiguration */
  {
    /* enEthSpeed */
    ETH_MAC_LAYER_SPEED_1G,

    /* enEthDuplex */
    ETH_FULL_DUPLEX,

    /* enInternalLoopBackMode */
    ETH_DISABLE,

    /* enEthPHYInterface */
    ETH_SGMII,

    /* enTxInterruptMode */
    ETH_DISABLE,

    /* enRxInterruptMode */
    ETH_DISABLE
  }
};

/* Structure for Tx Queue configuration of controller 0 */
static CONST(Eth_TxQueueType, ETH_CONFIG_DATA) Eth_GaaTxQueueConfig0[] =
{
  /* Index: 0 - Eth_GaaTxQueueConfig0 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x00UL,

    /* ulChainId */
    0UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    4095UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 1 - Eth_GaaTxQueueConfig0 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x01UL,

    /* ulChainId */
    1UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    4095UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 2 - Eth_GaaTxQueueConfig0 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x02UL,

    /* ulChainId */
    2UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    4095UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 3 - Eth_GaaTxQueueConfig0 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x03UL,

    /* ulChainId */
    3UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    4095UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 4 - Eth_GaaTxQueueConfig0 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x04UL,

    /* ulChainId */
    4UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    4095UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 5 - Eth_GaaTxQueueConfig0 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x05UL,

    /* ulChainId */
    5UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    4095UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 6 - Eth_GaaTxQueueConfig0 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x06UL,

    /* ulChainId */
    6UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    4095UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 7 - Eth_GaaTxQueueConfig0 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x07UL,

    /* ulChainId */
    7UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    4095UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  }
};

/* Structure for Tx Queue configuration of controller 1 */
static CONST(Eth_TxQueueType, ETH_CONFIG_DATA) Eth_GaaTxQueueConfig1[] =
{
  /* Index: 0 - Eth_GaaTxQueueConfig1 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x00UL,

    /* ulChainId */
    8UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    1518UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 1 - Eth_GaaTxQueueConfig1 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x01UL,

    /* ulChainId */
    10UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    1518UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 2 - Eth_GaaTxQueueConfig1 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x02UL,

    /* ulChainId */
    11UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    1518UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 3 - Eth_GaaTxQueueConfig1 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x03UL,

    /* ulChainId */
    12UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    1518UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 4 - Eth_GaaTxQueueConfig1 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x04UL,

    /* ulChainId */
    13UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    1518UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 5 - Eth_GaaTxQueueConfig1 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x05UL,

    /* ulChainId */
    14UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    1518UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 6 - Eth_GaaTxQueueConfig1 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x06UL,

    /* ulChainId */
    9UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    1518UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  },
  /* Index: 7 - Eth_GaaTxQueueConfig1 */
  {
    /* ulQueueBufs */
    8UL,

    /* ulQueueId */
    0x07UL,

    /* ulChainId */
    15UL,

    /* enFrameType */
    ETH_EXPRESS_FRAME,

    /* ulMaxFrameSize */
    1518UL,

    /* enInitGateState */
    ETH_TAS_CLOSE,

    /* ulCycleTime */
    0UL,

    /* Index: 7 - stCBSConfig */
    {
      /* enCE */
      0UL,

      /* ulCIV */
      0UL,

      /* ulCUL */
      0UL
    },
    /* Index: 8 - stPerQueRLConfig */
    {
      /* ulGWRLCiValue */
      0x00000000UL,

      /* ulGWRLULCiValue */
      0x00000000UL
    }
  }
};

/* Structure for Rx Queue configuration of controller 0 */
static CONST(Eth_RxQueueType, ETH_CONFIG_DATA) Eth_GaaRxQueueConfig0[] =
{
  /* Index: 0 - Eth_GaaRxQueueConfig0 */
  {
    /* ulQueueBufs */
    32UL,

    /* ulQueueId */
    0x00UL,

    /* ulChainId */
    0x19UL
  }
};

/* Structure for Rx Queue configuration of controller 1 */
static CONST(Eth_RxQueueType, ETH_CONFIG_DATA) Eth_GaaRxQueueConfig1[] =
{
  /* Index: 0 - Eth_GaaRxQueueConfig1 */
  {
    /* ulQueueBufs */
    32UL,

    /* ulQueueId */
    0x00UL,

    /* ulChainId */
    0x1AUL
  }
};

static CONST(Eth_ETNEConfigType, ETH_CONFIG_DATA) Eth_GaaHwUnitConfiguration[] =
{
  /* Index: 0 - Eth_GaaHwUnitConfiguration */
  {
    /* ulEthPortId */
    0UL,

    /* ulFwdVectorId */
    0x4UL,

    /* Index: 2 - aaFwdCsd */
    {
      /* 0 */
      25UL
    },
    /* ulGateLatency */
    0UL,

    /* ulGateJitter */
    0UL,

    /* Index: 5 - stFlowControlConfig */
    {
      /* enPauseFrame */
      ETH_DISABLE,

      /* ulRetransmissionTime */
      0UL,

      /* ulPauseTime */
      1UL,

      /* enPauseTimeZero */
      ETH_DISABLE,

      /* Index: 4 - stPauseLevelConfig */
      {
        /* ulPauseAssertionLevel */
        4096UL,

        /* ulPauseDeAssertionLevel */
        4096UL
      }
    },
    /* Index: 6 - stPFCConfig */
    {
      /* enPFCFrame */
      ETH_DISABLE,

      /* ulRetransmissionTime */
      0UL,

      /* ulPauseTime */
      1UL,

      /* enPauseTimeZero */
      ETH_DISABLE,

      /* Index: 4 - stPFCPauseLevelConfig */
      {
        /* Index: 0 - 0 */
        {
          /* ulPausePriority */
          0x00000001UL,

          /* ulPauseAssertionLevel */
          4096UL,

          /* ulPauseDeAssertionLevel */
          4096UL
        },
        /* Index: 1 - 1 */
        {
          /* ulPausePriority */
          0x00000001UL,

          /* ulPauseAssertionLevel */
          4096UL,

          /* ulPauseDeAssertionLevel */
          4096UL
        }
      }
    },
    /* Index: 7 - stQueueConfig */
    {
      /* pTxQueueConfig */
      &Eth_GaaTxQueueConfig0[0],

      /* pRxQueueConfig */
      &Eth_GaaRxQueueConfig0[0],

      /* ucNumberOfTxQueue */
      0x08U,

      /* ucNumberOfRxQueue */
      0x01U
    },
    /* Index: 8 - stRxConfig */
    {
      /* ulBcastThreshold */
      0x003FUL,

      /* ulMcastThreshold */
      0x003FUL,

      /* enBcastStormFilter */
      ETH_ENABLE,

      /* enMcastStormFilter */
      ETH_ENABLE,

      /* ulMaxFrameSize */
      1518UL
    },
    /* enTxFragment */
    ETH_FRAGMENT_64_BYTE,

    /* Index: 10 - stTASConfig */
    {
      /* enTasEnable */
      ETH_DISABLE,

      /* ulTxMiniLatency */
      0UL,

      /* ulTxJitter */
      0UL,

      /* pTasTable */
      NULL_PTR,

      /* ulNumberOfTasTable */
      0UL,

      /* Index: 5 - aaEntryNumber */
      {
        /* 0 */
        0U,

        /* 1 */
        0U,

        /* 2 */
        0U,

        /* 3 */
        0U,

        /* 4 */
        0U,

        /* 5 */
        0U,

        /* 6 */
        0U,

        /* 7 */
        0U
      }
    },
    /* Index: 11 - stTimeConfig */
    {
      /* enPSMCaptureTime */
      MDIO_CAPTURE_TIME_1_CLK_CYCLE,

      /* enPSMHoldTime */
      MDIO_HOLD_TIME_2_CLK_CYCLE,

      /* ulPSMClockSelection */
      0x13UL
    },
    /* enBypassMode */
    ETH_DISABLE
  },
  /* Index: 1 - Eth_GaaHwUnitConfiguration */
  {
    /* ulEthPortId */
    1UL,

    /* ulFwdVectorId */
    0x4UL,

    /* Index: 2 - aaFwdCsd */
    {
      /* 0 */
      26UL
    },
    /* ulGateLatency */
    0UL,

    /* ulGateJitter */
    0UL,

    /* Index: 5 - stFlowControlConfig */
    {
      /* enPauseFrame */
      ETH_DISABLE,

      /* ulRetransmissionTime */
      0UL,

      /* ulPauseTime */
      1UL,

      /* enPauseTimeZero */
      ETH_DISABLE,

      /* Index: 4 - stPauseLevelConfig */
      {
        /* ulPauseAssertionLevel */
        4096UL,

        /* ulPauseDeAssertionLevel */
        4096UL
      }
    },
    /* Index: 6 - stPFCConfig */
    {
      /* enPFCFrame */
      ETH_DISABLE,

      /* ulRetransmissionTime */
      0UL,

      /* ulPauseTime */
      1UL,

      /* enPauseTimeZero */
      ETH_DISABLE,

      /* Index: 4 - stPFCPauseLevelConfig */
      {
        /* Index: 0 - 0 */
        {
          /* ulPausePriority */
          0x00000001UL,

          /* ulPauseAssertionLevel */
          4096UL,

          /* ulPauseDeAssertionLevel */
          4096UL
        },
        /* Index: 1 - 1 */
        {
          /* ulPausePriority */
          0x00000001UL,

          /* ulPauseAssertionLevel */
          4096UL,

          /* ulPauseDeAssertionLevel */
          4096UL
        }
      }
    },
    /* Index: 7 - stQueueConfig */
    {
      /* pTxQueueConfig */
      &Eth_GaaTxQueueConfig1[0],

      /* pRxQueueConfig */
      &Eth_GaaRxQueueConfig1[0],

      /* ucNumberOfTxQueue */
      0x08U,

      /* ucNumberOfRxQueue */
      0x01U
    },
    /* Index: 8 - stRxConfig */
    {
      /* ulBcastThreshold */
      0x003FUL,

      /* ulMcastThreshold */
      0x003FUL,

      /* enBcastStormFilter */
      ETH_ENABLE,

      /* enMcastStormFilter */
      ETH_ENABLE,

      /* ulMaxFrameSize */
      1518UL
    },
    /* enTxFragment */
    ETH_FRAGMENT_64_BYTE,

    /* Index: 10 - stTASConfig */
    {
      /* enTasEnable */
      ETH_DISABLE,

      /* ulTxMiniLatency */
      0UL,

      /* ulTxJitter */
      0UL,

      /* pTasTable */
      NULL_PTR,

      /* ulNumberOfTasTable */
      0UL,

      /* Index: 5 - aaEntryNumber */
      {
        /* 0 */
        0U,

        /* 1 */
        0U,

        /* 2 */
        0U,

        /* 3 */
        0U,

        /* 4 */
        0U,

        /* 5 */
        0U,

        /* 6 */
        0U,

        /* 7 */
        0U
      }
    },
    /* Index: 11 - stTimeConfig */
    {
      /* enPSMCaptureTime */
      MDIO_CAPTURE_TIME_1_CLK_CYCLE,

      /* enPSMHoldTime */
      MDIO_HOLD_TIME_1_CLK_CYCLE,

      /* ulPSMClockSelection */
      0x3FUL
    },
    /* enBypassMode */
    ETH_DISABLE
  }
};


CONST(uint32, ETH_CONFIG_DATA) Eth_GaaTotalCtrlConfig[] =                                                               /* PRQA S 1504 # JV-01 */
{
  /* Core0 */
  0x01U,
  /* Core1 */
  0x01U
};

static CONST(Eth_CtrlConfigType, ETH_CONFIG_DATA) Eth_GaaCtrlConfiguration[] =
{
  /* Index: 0 - Eth_GaaCtrlConfiguration */
  {
    /* Index: 0 - aaEthMACAddr */
    {
      /* 0 */
      0x74U,

      /* 1 */
      0x90U,

      /* 2 */
      0x50U,

      /* 3 */
      0x00U,

      /* 4 */
      0x00U,

      /* 5 */
      0x00U
    },
    /* pEthConfig */
    &Eth_GaaEthConfiguration[0],

    /* pHwUnitConfig */
    &Eth_GaaHwUnitConfiguration[0],                                                                                     /* PRQA S 0315 # JV-01 */

    /* Index: 3 - stSWConfig */
    {
      /* Index: 0 - stTsnaRegValue */
      {
        /* ulEAVCCValue */
        0x00000000UL,

        /* ulEAVTCValue */
        0x00000000UL,

        /* ulEARTFCValue */
        0x00000000UL
      }
    }
  },
  /* Index: 1 - Eth_GaaCtrlConfiguration */
  {
    /* Index: 0 - aaEthMACAddr */
    {
      /* 0 */
      0x74U,

      /* 1 */
      0x90U,

      /* 2 */
      0x50U,

      /* 3 */
      0x00U,

      /* 4 */
      0x00U,

      /* 5 */
      0x00U
    },
    /* pEthConfig */
    &Eth_GaaEthConfiguration[1],

    /* pHwUnitConfig */
    &Eth_GaaHwUnitConfiguration[1],                                                                                     /* PRQA S 0315 # JV-01 */

    /* Index: 3 - stSWConfig */
    {
      /* Index: 0 - stTsnaRegValue */
      {
        /* ulEAVCCValue */
        0x00000000UL,

        /* ulEAVTCValue */
        0x00000000UL,

        /* ulEARTFCValue */
        0x00000000UL
      }
    }
  }
};

#define ETH_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ETH_START_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


VAR(Eth_StateType, ETH_VAR_INIT) Eth_GenDriverState[] =                                                                 /* PRQA S 1504 # JV-01 */
{
  /* 0 */
  ETH_STATE_UNINIT,
  /* 1 */
  ETH_STATE_UNINIT
};

#define ETH_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ETH_START_SEC_CONST_8
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


CONST(uint8, ETH_CONFIG_DATA) Eth_GaaGetCoreId2Index[] =                                                                /* PRQA S 1504 # JV-01 */
{
  0x00U,
  0x01U,
  0xFFU
};

#define ETH_STOP_SEC_CONST_8
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ETH_START_SEC_VAR_INIT_16
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventAccess[] =                                                                     /* PRQA S 1504 # JV-01 */
{
  /* ETH_E_ACCESS_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_ACCESS_1 */
  ETH_DEM_NOT_CONFIGURED
};

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventRxFramesLost[] =                                                               /* PRQA S 1504 # JV-01 */
{
  /* ETH_E_RX_FRAMES_LOST_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_RX_FRAMES_LOST_1 */
  ETH_DEM_NOT_CONFIGURED
};

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventCRC[] =                                                                        /* PRQA S 1504 # JV-01 */
{
  /* ETH_E_CRC_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_CRC_1 */
  ETH_DEM_NOT_CONFIGURED
};

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventUnderSizeFrame[] =                                                             /* PRQA S 1504 # JV-01 */
{
  /* ETH_E_UNDERSIZEFRAME_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_UNDERSIZEFRAME_1 */
  ETH_DEM_NOT_CONFIGURED
};

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventOverSizeFrame[] =                                                              /* PRQA S 1504 # JV-01 */
{
  /* ETH_E_OVERSIZEFRAME_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_OVERSIZEFRAME_1 */
  ETH_DEM_NOT_CONFIGURED
};

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventAlignment[] =                                                                  /* PRQA S 1504 # JV-01 */
{
  /* ETH_E_ALIGNMENT_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_ALIGNMENT_1 */
  ETH_DEM_NOT_CONFIGURED
};

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventSinglecollision[] =                                                            /* PRQA S 1504 # JV-01 */
{
  /* ETH_E_SINGLECOLLISION_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_SINGLECOLLISION_1 */
  ETH_DEM_NOT_CONFIGURED
};

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventMultiplecollision[] =                                                          /* PRQA S 1504 # JV-01 */
{
  /* ETH_E_MULTIPLECOLLISION_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_MULTIPLECOLLISION_1 */
  ETH_DEM_NOT_CONFIGURED
};

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventLatecollision[] =                                                              /* PRQA S 1504 # JV-01 */
{
  /* ETH_E_LATECOLLISION_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_LATECOLLISION_1 */
  ETH_DEM_NOT_CONFIGURED
};

#if (ETH_INTERRUPT_CONSISTENCY_CHECK == STD_ON)

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventIntInconsistent[] =                                                            /* PRQA S 1504 # JV-01 */
{
  /* ETH_E_INT_INCONSISTENT_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_INT_INCONSISTENT_1 */
  ETH_DEM_NOT_CONFIGURED
};

#endif

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventDmaError[] =                                                                   /* PRQA S 1504 # JV-01 */
{
  /* ETH_E_DMA_ERROR_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_DMA_ERROR_1 */
  ETH_DEM_NOT_CONFIGURED
};

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventEccError[] =                                                                   /* PRQA S 1504 # JV-01 */
{
  /* ETH_E_ECC_ERROR_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_ECC_ERROR_1 */
  ETH_DEM_NOT_CONFIGURED
};

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventTimerincFailed[] =                                                             /* PRQA S 1504, 1502, 3408 # JV-01, JV-01, JV-01 */
{
  /* ETH_E_TIMERINC_FAILED_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_TIMERINC_FAILED_1 */
  ETH_DEM_NOT_CONFIGURED
};

#endif

#if (ETH_GLOBAL_TIME_SUPPORT == STD_ON)

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventTimeroffsetFailed[] =                                                          /* PRQA S 1504, 1502, 3408 # JV-01, JV-01, JV-01 */
{
  /* ETH_E_TIMEROFFSET_FAILED_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_TIMEROFFSET_FAILED_1 */
  ETH_DEM_NOT_CONFIGURED
};

#endif

#if (ETH_UNINTENDED_INTERRUPT_CHECK == STD_ON)

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventUnintendedIntChk[] =                                                           /* PRQA S 1504 # JV-01 */
{
  /* ETH_E_INTERRUPT_CONTROLLER_FAILURE_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_INTERRUPT_CONTROLLER_FAILURE_1 */
  ETH_DEM_NOT_CONFIGURED
};

#endif

#if ((ETH_REGISTER_CHECK_INITTIME == STD_ON) || (ETH_REGISTER_CHECK_RUNTIME == STD_ON))

VAR(uint16, ETH_VAR_INIT) Eth_GaaDemEventRegisterCorruption[] =                                                         /* PRQA S 3408, 1504 # JV-01, JV-01 */
{
  /* ETH_E_REGISTER_CORRUPTION_0 */
  ETH_DEM_NOT_CONFIGURED,
  /* ETH_E_REGISTER_CORRUPTION_1 */
  ETH_DEM_NOT_CONFIGURED
};

#endif

#define ETH_STOP_SEC_VAR_INIT_16
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ETH_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


CONST(uint32, ETH_CONFIG_DATA) Eth_GaaTxBufferTotal[] =                                                                 /* PRQA S 1502 # JV-01 */
{
  /* 0 */
  ETH_TX_BUF_TOTAL_0,
  /* 1 */
  ETH_TX_BUF_TOTAL_1
};

CONST(uint32, ETH_CONFIG_DATA) Eth_GaaRamSize[] =                                                                       /* PRQA S 1533 # JV-01 */
{
  /* 0 */
  0x0000EB40UL,
  /* 1 */
  0x0000EB40UL
};

/* Structure for general configuration */
CONST(Eth_ConfigType, ETH_CONFIG_DATA) Eth_GaaConfiguration[] =                                                         /* PRQA S 1502 # JV-01 */
{
  /* Index: 0 - Eth_GaaConfiguration */
  {
    /* ulStartOfDbToc */
    0x0ED60220UL,

    /* pCtrlConfig */
    &Eth_GaaCtrlConfiguration[0],

    /* pDemEventAccess */
    &Eth_GaaDemEventAccess[0],

    /* pDemEventRxFramesLost */
    &Eth_GaaDemEventRxFramesLost[0],

    /* pDemEventCRC */
    &Eth_GaaDemEventCRC[0],

    /* pDemEventUnderSizeFrame */
    &Eth_GaaDemEventUnderSizeFrame[0],

    /* pDemEventOverSizeFrame */
    &Eth_GaaDemEventOverSizeFrame[0],

    /* pDemEventAlignment */
    &Eth_GaaDemEventAlignment[0],

    /* pDemEventSinglecollision */
    &Eth_GaaDemEventSinglecollision[0],

    /* pDemEventMultiplecollision */
    &Eth_GaaDemEventMultiplecollision[0],

    /* pDemEventLatecollision */
    &Eth_GaaDemEventLatecollision[0],

    /* pDemEventDmaError */
    &Eth_GaaDemEventDmaError[0],

    /* pDemEventEccError */
    &Eth_GaaDemEventEccError[0],

    /* pTotalCtrlConfig */
    &Eth_GaaTotalCtrlConfig[0],

    /* Index: 14 - ulCtrlConfigIdx */
    {
      /* Index: 0 - ulCtrlConfigIdx[0] */
      {
        0x00U,

        0xFFU
      },
      /* Index: 1 - ulCtrlConfigIdx[1] */
      {
        0x01U,

        0xFFU
      }
    },
    /* pDriverState */
    &Eth_GenDriverState[0],

    /* pCoreId2Index */
    &Eth_GaaGetCoreId2Index[0],

    /* Index: 17 - stGwcaRegValue */
    {
      /* ulGWVCCValue */
      0x00000000UL,

      /* ulGWVTCValue */
      0x00000000UL,

      /* ulGWTTFCValue */
      0x00000000UL,

      /* ulGWSCR0Value */
      0x00000000UL,

      /* ulGWGRLCValue */
      0x00000000UL,

      /* ulGWGRLULCValue */
      0x00000000UL
    },
    /* Index: 18 - stGlobalPauseConfiguration */
    {
      /* Index: 0 - 0 */
      {
        /* enGlobalPause */
        ETH_DISABLE,

        /* ulPauseAssertionLevel */
        4096UL,

        /* ulPauseDeAssertionLevel */
        4096UL
      },
      /* Index: 1 - 1 */
      {
        /* enGlobalPause */
        ETH_DISABLE,

        /* ulPauseAssertionLevel */
        4096UL,

        /* ulPauseDeAssertionLevel */
        4096UL
      }
    }
  }
};

CONST(volatile Eth_ETNE_RegType, ETH_CONFIG_DATA) Eth_GstETNE_Regs =                                                    /* PRQA S 1531, 1533 # JV-01, JV-01 */
{
  /* Index: 0 - pSGMII */
  {
    /* pSGMII[0] */
    (Eth_ETNE_SGMIIRegType *)0xFF978200UL,                                                                              /* PRQA S 0306 # JV-01 */

    /* pSGMII[1] */
    (Eth_ETNE_SGMIIRegType *)0xFF978600UL                                                                               /* PRQA S 0306 # JV-01 */
  }
};

CONST(volatile Eth_RSW2_IntRegType, ETH_CONFIG_DATA) Eth_RSW2_IntReg =                                                  /* PRQA S 1533, 1502 # JV-01, JV-01 */
{
  /* pEICReg */
  (Eth_ETNE_EICRegType *)0xFFF80588UL,                                                                                  /* PRQA S 0306 # JV-01 */
  /* pINTSMReg */
  (Eth_ETNE_INTSMRegType *)0xFF921000UL                                                                                 /* PRQA S 0306 # JV-01 */
};

#define ETH_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ETH_START_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


P2VAR(uint8, AUTOMATIC, ETH_VAR_INIT_PTR) Eth_GaaMemPoolBufferTable[] =                                                 /* PRQA S 3432, 1533 # JV-01, JV-01 */
{
  /* 0 */
  Eth_GaaMemPoolBuffer_0,
  /* 1 */
  Eth_GaaMemPoolBuffer_1
};

P2VAR(Eth_TxBufferType, AUTOMATIC, ETH_VAR_INIT_PTR) Eth_GaaTxBufferMgrTable[] =                                        /* PRQA S 3432 # JV-01 */
{
  /* 0 */
  Eth_GaaTxBufferMgr_0,
  /* 1 */
  Eth_GaaTxBufferMgr_1
};

#define ETH_STOP_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ETH_START_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


VAR(boolean, ETH_VAR_INIT) Eth_GaaTxRamInitState[] =                                                                    /* PRQA S 3408, 1502 # JV-01, JV-01 */
{
  /* 0 */
  ETH_FALSE,
  /* 1 */
  ETH_FALSE
};

#define ETH_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ETH_START_SEC_CONST_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


CONSTP2VAR(volatile Eth_ETNE_EICRegType, ETH_CONST, REGSPACE) Eth_GpETNE_EICRegs =                                      /* PRQA S 0306, 1502 # JV-01, JV-01 */
{
  /* Eth_GpETNE_EICRegs */
  (Eth_ETNE_EICRegType *)0xFFF80588UL                                                                                   /* PRQA S 0306, 1502 # JV-01, JV-01 */
};

#define ETH_STOP_SEC_CONST_32
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */



#define ETH_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


CONST(Eth_HWIPType, ETH_CONFIG_DATA) Eth_GaaHWIP[] =                                                                    /* PRQA S 1531 # JV-01 */
{
  /* Index: 0 - ucIndex */
  {
    /* ETNE */
    ETH_HWIP_ETNE
  },
  /* Index: 1 - ucIndex */
  {
    /* ETNE */
    ETH_HWIP_ETNE
  }
};

#define ETH_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


#define ETH_START_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */


P2CONST(Eth_HwFuncTableType, ETH_VAR_INIT, ETH_CONFIG_DATA) Eth_GaaHwFunc[] =                                           /* PRQA S 1531 # JV-01 */
{
  /* ETH_HWIP_ETNC */
  NULL_PTR,
  /* ETH_HWIP_ETNB */
  NULL_PTR,
  /* ETH_HWIP_ETND */
  NULL_PTR,
  /* ETH_HWIP_ETNE */
  &Eth_EtneFunc,
  /* ETH_HWIP_ETNF */
  NULL_PTR
};

#define ETH_STOP_SEC_VAR_INIT_PTR
#include "Eth_MemMap.h"                                                                                                 /* PRQA S 5087 # JV-01 */



/***********************************************************************************************************************
**                      Function Definitions                                                                          **
***********************************************************************************************************************/

/***********************************************************************************************************************
**                      End of File                                                                                   **
***********************************************************************************************************************/

